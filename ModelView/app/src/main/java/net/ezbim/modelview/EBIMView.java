package net.ezbim.modelview;

import android.app.ActivityManager;
import android.content.Context;
import android.content.res.Configuration;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.os.SystemClock;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.SurfaceHolder;
import android.widget.AbsListView;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;


/**
 * Created by dev on 16/1/27.
 */
public class EBIMView extends GLSurfaceView implements GestureDetector.OnGestureListener, ScaleGestureDetector.OnScaleGestureListener, GestureDetector.OnDoubleTapListener{

    private static final String TAG = "EBIMView";
    private static final boolean DEBUG = true;
    private static final boolean LOG_EGL = true;
    private static final int MODEL_HIDE_LEVEL = 6;
    private static int GLES_VERSION = 2;
    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;
    private int viewHeigh;
    private int viewWidth;
    private String checkHisValue;
    private static final int MSG_RENDER = 0x0001;
    private Handler mHandler;
    private boolean firstScroll = true;
    private singleTapUpListener mSingleTapUpListener;

    public void openRender(){
        if(mHandler == null) {
            final ExecutorService cachedThreadPool = Executors.newCachedThreadPool();
            final List<Callable<Object>> threadCallers = new ArrayList<Callable<Object>>();
            threadCallers.add(new Callable<Object>() {
                @Override
                public Object call() throws Exception {
                    if(ModelView.needRenderNow()) {
                        requestRender();
                    }else{
                        firstScroll = true;
                    }
                    return null;
                }
            });
            threadCallers.add(new Callable<Object>() {
                @Override
                public Object call() throws Exception {
                    SystemClock.sleep(33);
                    return null;
                }
            });
            HandlerThread handlerThread = new HandlerThread("RenderThread");
            handlerThread.start();
            mHandler = new Handler(handlerThread.getLooper()) {
                @Override
                public void handleMessage(Message msg) {
                        synchronized (this) {
                            try {
                                cachedThreadPool.invokeAll(threadCallers);
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                            mHandler.sendEmptyMessage(MSG_RENDER);
                        }
                    }
            };
        }else if(!mHandler.hasMessages(MSG_RENDER)){
            mHandler.sendEmptyMessage(MSG_RENDER);
        }
    }

    public void closeRender(){
        if(mHandler!=null && mHandler.hasMessages(MSG_RENDER)){
            mHandler.removeMessages(MSG_RENDER);
        }
    }


    public int getViewHeigh() {
        return viewHeigh;
    }

    public int getViewWidth() {
        return viewWidth;
    }

    public EBIMView(Context context) {
        super(context);
        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 3.0 or later backwards-compatible versions.
        init(context, false, 16, 8);
    }

    public EBIMView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context, false, 16, 8);
        Log.d(TAG,"init EBIMView");
    }



    private void init(Context context, boolean translucent, int depth, int stencil) {
        if(LOG_EGL) {
            setDebugFlags(GLSurfaceView.DEBUG_LOG_GL_CALLS);
        }
        gestureDetector = new GestureDetector(context, this);
        scaleGestureDetector = new ScaleGestureDetector(context, this);
        ActivityManager activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        int reqGlEsVersion = activityManager.getDeviceConfigurationInfo().reqGlEsVersion;
        if (reqGlEsVersion == 0x00030000 || reqGlEsVersion == 0x00030001) {
            GLES_VERSION = 3;
            Log.e("GLES_VERSION", "3");
        }
        /* By default, GLSurfaceView() creates a RGB_565 opaque surface.
         * If we want a translucent one, we should change the surface's
	     * format here, using PixelFormat.TRANSLUCENT for GL Surfaces
	     * is interpreted as any 32-bit surface with alpha by SurfaceFlinger.
	     */
        if (translucent) {
            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        }

	    /* Setup the context factory for 2.0 rendering.
	     * See ContextFactory class definition below
	     */
        setEGLContextFactory(new ContextFactory());

	    /* We need to choose an EGLConfig that matches the format of
	     * our surface exactly. This is going to be done in our
	     * custom config chooser. See ConfigChooser class definition
	     * below.
	     */
        setEGLConfigChooser(translucent ?
                new ConfigChooser(8, 8, 8, 8, depth, stencil) :
                new ConfigChooser(5, 6, 5, 0, depth, stencil));
        setPreserveEGLContextOnPause(true);
    }

    private static class ContextFactory implements EGLContextFactory {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            Log.e(TAG, "creating OpenGL ES " + GLES_VERSION + " context");
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, GLES_VERSION, EGL10.EGL_NONE};
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            return context;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
        }
    }

    private static class ConfigChooser implements EGLConfigChooser {

        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }

        /* This EGL config specification is used to specify 1.x rendering.
         * We use a minimum size of 4 bits for red/green/blue, but will
         * perform actual matching in chooseConfig() below.
         */
        private static int EGL_OPENGL_ES_BIT = 4;
        private static int[] s_configAttribs2 =
                {
                        EGL10.EGL_RED_SIZE, 4,
                        EGL10.EGL_GREEN_SIZE, 4,
                        EGL10.EGL_BLUE_SIZE, 4,
                        EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
                        EGL10.EGL_NONE
                };

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

	        /* Get the number of minimally matching EGL configurations
	         */
            int[] num_config = new int[1];
            egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

            int numConfigs = num_config[0];

            if (numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }

	        /* Allocate then read the array of minimally matching EGL configs
	         */
            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

            if (DEBUG) {
                printConfigs(egl, display, configs);
            }
	        /* Now return the "best" one
	         */
            return chooseConfig(egl, display, configs);
        }

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
                                      EGLConfig[] configs) {
            for (EGLConfig config : configs) {
                int d = findConfigAttrib(egl, display, config,
                        EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config,
                        EGL10.EGL_STENCIL_SIZE, 0);

                // We need at least mDepthSize and mStencilSize bits
                if (d < mDepthSize || s < mStencilSize)
                    continue;

                // We want an *exact* match for red/green/blue/alpha
                int r = findConfigAttrib(egl, display, config,
                        EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config,
                        EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config,
                        EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config,
                        EGL10.EGL_ALPHA_SIZE, 0);

                if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
                    return config;
            }
            return null;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
                                     EGLConfig config, int attribute, int defaultValue) {

            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        }

        private void printConfigs(EGL10 egl, EGLDisplay display,
                                  EGLConfig[] configs) {
            int numConfigs = configs.length;
            Log.w(TAG, String.format("%d configurations", numConfigs));
            for (int i = 0; i < numConfigs; i++) {
                Log.w(TAG, String.format("Configuration %d:\n", i));
                printConfig(egl, display, configs[i]);
            }
        }

        private void printConfig(EGL10 egl, EGLDisplay display,
                                 EGLConfig config) {
            int[] attributes = {
                    EGL10.EGL_BUFFER_SIZE,
                    EGL10.EGL_ALPHA_SIZE,
                    EGL10.EGL_BLUE_SIZE,
                    EGL10.EGL_GREEN_SIZE,
                    EGL10.EGL_RED_SIZE,
                    EGL10.EGL_DEPTH_SIZE,
                    EGL10.EGL_STENCIL_SIZE,
                    EGL10.EGL_CONFIG_CAVEAT,
                    EGL10.EGL_CONFIG_ID,
                    EGL10.EGL_LEVEL,
                    EGL10.EGL_MAX_PBUFFER_HEIGHT,
                    EGL10.EGL_MAX_PBUFFER_PIXELS,
                    EGL10.EGL_MAX_PBUFFER_WIDTH,
                    EGL10.EGL_NATIVE_RENDERABLE,
                    EGL10.EGL_NATIVE_VISUAL_ID,
                    EGL10.EGL_NATIVE_VISUAL_TYPE,
                    0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
                    EGL10.EGL_SAMPLES,
                    EGL10.EGL_SAMPLE_BUFFERS,
                    EGL10.EGL_SURFACE_TYPE,
                    EGL10.EGL_TRANSPARENT_TYPE,
                    EGL10.EGL_TRANSPARENT_RED_VALUE,
                    EGL10.EGL_TRANSPARENT_GREEN_VALUE,
                    EGL10.EGL_TRANSPARENT_BLUE_VALUE,
                    0x3039, //EGL10.EGL_BIND_TO_TEXTURE_RGB,
                    0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
                    0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
                    0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
                    EGL10.EGL_LUMINANCE_SIZE,
                    EGL10.EGL_ALPHA_MASK_SIZE,
                    EGL10.EGL_COLOR_BUFFER_TYPE,
                    EGL10.EGL_RENDERABLE_TYPE,
                    0x3042 // EGL10.EGL_CONFORMANT
            };
            String[] names = {
                    "EGL_BUFFER_SIZE",
                    "EGL_ALPHA_SIZE",
                    "EGL_BLUE_SIZE",
                    "EGL_GREEN_SIZE",
                    "EGL_RED_SIZE",
                    "EGL_DEPTH_SIZE",
                    "EGL_STENCIL_SIZE",
                    "EGL_CONFIG_CAVEAT",
                    "EGL_CONFIG_ID",
                    "EGL_LEVEL",
                    "EGL_MAX_PBUFFER_HEIGHT",
                    "EGL_MAX_PBUFFER_PIXELS",
                    "EGL_MAX_PBUFFER_WIDTH",
                    "EGL_NATIVE_RENDERABLE",
                    "EGL_NATIVE_VISUAL_ID",
                    "EGL_NATIVE_VISUAL_TYPE",
                    "EGL_PRESERVED_RESOURCES",
                    "EGL_SAMPLES",
                    "EGL_SAMPLE_BUFFERS",
                    "EGL_SURFACE_TYPE",
                    "EGL_TRANSPARENT_TYPE",
                    "EGL_TRANSPARENT_RED_VALUE",
                    "EGL_TRANSPARENT_GREEN_VALUE",
                    "EGL_TRANSPARENT_BLUE_VALUE",
                    "EGL_BIND_TO_TEXTURE_RGB",
                    "EGL_BIND_TO_TEXTURE_RGBA",
                    "EGL_MIN_SWAP_INTERVAL",
                    "EGL_MAX_SWAP_INTERVAL",
                    "EGL_LUMINANCE_SIZE",
                    "EGL_ALPHA_MASK_SIZE",
                    "EGL_COLOR_BUFFER_TYPE",
                    "EGL_RENDERABLE_TYPE",
                    "EGL_CONFORMANT"
            };
            int[] value = new int[1];
            for (int i = 0; i < attributes.length; i++) {
                int attribute = attributes[i];
                String name = names[i];
                if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
                    Log.w(TAG, String.format("  %s: %d\n", name, value[0]));
                } else {
                    // Log.w(TAG, String.format("  %s: failed\n", name));
                    while (egl.eglGetError() != EGL10.EGL_SUCCESS) ;
                }
            }
        }

        // Subclasses can adjust these values:
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.e(TAG, "surfaceCreated");
        super.surfaceCreated(holder);
    }


    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        Log.e(TAG, "surfaceChanged");
        super.surfaceChanged(holder, format, w, h);
    }

    @Override
    public void onResume() {
//        ModelView.rotationBegin(6);
        Log.e(TAG,"onResume");
        super.onResume();
    }

    @Override
    public void onPause() {
        Log.e(TAG,"onPause");
        super.onPause();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.e(TAG, "surfaceDestroyed");
        super.surfaceDestroyed(holder);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (gestureDetector.onTouchEvent(event)) {
            return true;
        }
        return scaleGestureDetector.onTouchEvent(event);
    }

    //初始化时获得高度跟宽度
    @Override
    public void onWindowFocusChanged(boolean hasWindowFocus) {
        viewHeigh = this.getHeight();
        viewWidth = this.getWidth();
        super.onWindowFocusChanged(hasWindowFocus);
    }

    //在横竖屏切换时重新获得高跟宽
    @Override
    protected void onConfigurationChanged(Configuration newConfig) {
        viewHeigh = this.getHeight();
        viewWidth = this.getWidth();
        super.onConfigurationChanged(newConfig);
    }

    //初始化45度角
    public void godEyes(){
        ModelView.mouseMoveEvent(0.5f, -0.5f);
        ModelView.updateSeveralTimes();
    }

    /**
     * 手势操作
     */
    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        //滑动
        if(firstScroll){
//            Log.e(TAG,"I AM FIRST");
            ModelView.rotationBegin(MODEL_HIDE_LEVEL);
            firstScroll = false;
        }
        if (e2.getPointerCount() == 1) {
            float finalX = -distanceX / viewWidth;
            float finalY = distanceY / viewHeigh;
            ModelView.mouseMoveEvent(finalX, finalY);
            ModelView.updateSeveralTimes();
//            Log.d(TAG, "onScroll distanceX:" + distanceX + " distanceY:" + distanceY);
            return true;
        }
        if (e2.getPointerCount() >= 3) {
            float finalX = -distanceX / viewWidth;
            float finalY = distanceY / viewHeigh;
            ModelView.onPanModel(0, finalX, finalY);
            ModelView.updateSeveralTimes();
//            Log.d(TAG, "onPan distanceX:" + distanceX + " distanceY:" + distanceY);
            return true;
        }
        return false;
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        //单点
//        Log.e(TAG, "onSingleTapUp start"+SystemClock.currentThreadTimeMillis());
        float floatX = e.getX(0);
        float floatY = e.getY(0);
        double dx = floatX / (viewWidth / 2) - 1;
        double dy = 1 - floatY / (viewHeigh / 2);
        String checkValue = ModelView.clickSelection(dx, dy);
        Log.e(TAG,checkValue);
        if (checkHisValue != null && !"".equals(checkHisValue)) {
            ModelView.setFrameIgnore(true);
            ModelView.unHighlight(checkHisValue);
        }
        if (checkValue != null && !"".equals(checkValue)) {
            checkHisValue = checkValue;
            Log.e(TAG, "setFrameIgnore start == "+SystemClock.currentThreadTimeMillis());
            ModelView.setFrameIgnore(true);
            Log.e(TAG, "setFrameIgnore end == " + SystemClock.currentThreadTimeMillis());
            ModelView.highlight(checkHisValue);
            Log.e(TAG, "highlight end == " + SystemClock.currentThreadTimeMillis());
            mSingleTapUpListener.IsSingelTagUp(checkValue);
        }
//        Log.e(TAG, "onSingleTapUp end == "+SystemClock.currentThreadTimeMillis());
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {
        Log.d(TAG, "onShowPress");
    }

    @Override
    public void onLongPress(MotionEvent e) {
        //长按，长按后震动30ms
        Log.d(TAG, "onLongPress");
    }

    //非常快速的滑动
    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        Log.d(TAG, "onFling");
        return false;
    }

    //按下
    @Override
    public boolean onDown(MotionEvent e) {
        Log.d(TAG, "onDown");
        return false;
    }


    @Override
    public boolean onSingleTapConfirmed(MotionEvent e) {
        Log.d(TAG, "onSingleTapConfirmed");
        return false;
    }

    @Override
    public boolean onDoubleTap(MotionEvent e) {
        Log.d(TAG, "onDoubleTap");
        return false;
    }

    @Override
    public boolean onDoubleTapEvent(MotionEvent e) {
        Log.d(TAG, "onDoubleTapEvent");
        return false;
    }

    /**
     * 缩放
     */
    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        //差值
        float maxscale = (float) Math.sqrt(viewHeigh * viewWidth);
        float span = (detector.getPreviousSpan() - detector.getCurrentSpan()) / maxscale;
//        Log.d(TAG, "onScale(p:" + detector.getPreviousSpan() + " c:" + detector.getCurrentSpan() + " 比值:" + (detector.getCurrentSpan() - detector.getPreviousSpan()) / maxscale + ")");
        ModelView.zoomModel(1, 0, span);
        ModelView.updateSeveralTimes();
        return true;
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector detector) {
        Log.d(TAG, "onScaleBegin");
        ModelView.rotationBegin(MODEL_HIDE_LEVEL);
        return true;
    }

    @Override
    public void onScaleEnd(ScaleGestureDetector detector) {
        Log.d(TAG, "onScaleEnd");
    }

    public interface singleTapUpListener{
        public void IsSingelTagUp(String singleValue);
    }

    public void setSingleTapUpListener(singleTapUpListener mSingleTapUpListener){
        this.mSingleTapUpListener = mSingleTapUpListener;
    }
}

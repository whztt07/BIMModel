package net.ezbim.modelview;

import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.util.Log;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by hdk on 2016/1/28.
 */
public class EBIMRenderer implements GLSurfaceView.Renderer {
    private static final String TAG = "EBIMRenderer";

    private ModelViewListener modelViewListener;
    private int width;
    private int height;
    private boolean isinit;
    private boolean isreload;


    public void setIsreload(boolean isreload) {
        this.isreload = isreload;
    }


    public EBIMRenderer(int width, int height, ModelViewListener modelViewListener) {
        this.width = width;
        this.height = height;
        this.modelViewListener = modelViewListener;
    }


    public void setIsinit(boolean isinit) {
        this.isinit = isinit;
    }

    public void onDrawFrame(GL10 gl) {
//        BLog.e(TAG, SystemClock.currentThreadTimeMillis() + "");
        ModelView.step();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (isinit) {
            ModelView.init(width, height);
            isinit = false;
            modelViewListener.onInitFinished();
            Log.e(TAG, "onInitFinished");
        }
        if (isreload) {
            isreload = false;
            modelViewListener.onModelReload();
            Log.e(TAG, "onModelReload");
        }
        ModelView.updateSeveralTimes();
//        BLog.e(TAG, "onSurfaceChanged");
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Do nothing
        Log.e(TAG, "onSurfaceCreated");
    }

    public interface ModelViewListener {
        void onInitFinished();
        void onModelReload();
    }
}

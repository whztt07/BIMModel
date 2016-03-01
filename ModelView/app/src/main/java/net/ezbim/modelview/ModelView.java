package net.ezbim.modelview;

import java.util.ArrayList;
import java.util.HashMap;

public class ModelView {

    public ModelView() {
    }

    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("modelView");
    }

    public static native void init(int width, int height);

    public static native void step();

    public static native int loadObject(String address);//

    public static native void loadObject(String address, String name);

    public static native void loadTest();

    public static native void mouseButtonPressEvent(float x, float y, int button);

    public static native void mouseButtonReleaseEvent(float x, float y, int button);

    public static native void mouseMoveEvent(float x, float y);

    public static native void keyboardDown(int key);

    public static native void keyboardUp(int key);

    public static native void updateSeveralTimes();

    public static native void loadIVE(String address);

    public static native ArrayList<String> getFloorNames();

    public static native void zoomModel(double eventTimeDelta, float x, float y);

    public static native void onHome();

    public static native void onPanModel(double eventTimeDelta, float x, float y);

    public static native int preProcessBIMFile(String address, boolean byFloor);//true按层分

    public static native void startRendering();

    public static native void loadByFloor(ArrayList<String> arrayList);

    public static native void unloadByFloor(ArrayList<String> arrayList);

    public static native void loadByFloorName(String floorName);

    public static native void unLoadByFloorName(String floorName);

    public static native void unLoadAll();

    public static native void rotationBegin(int hideLevel);//取值范围为1-10 越大减少的越小。在滑动前只执行一次。

    public static native void setFrameIgnore(boolean isIgnore);//设置Frame时是否延时绘制，在点击时使用不进行延时绘制。

    public static native HashMap<String, ArrayList<String>> getViewportCameraView();//获得视口参数

    public static native void zoomToViewPortCenter(HashMap<String, ArrayList<String>> viewMap);//还原视口参数

    public static native void setSkyBox(String imgPath);//设置天空盒

    public static native void updateSkyBox();

    public static native String clickSelection(double doubleX, double doubleY);//返回被选中的构件ID或者组ID或者为“”空字符（不是NULL）

    public static native void highlight(String entityID);//高亮指定ID的构件或者组

    public static native void unHighlight(String entityID);//取消指定ID的高亮

    public static native boolean needRenderNow();

//    public static native void exitModelView();//退出ModelView，清理ModelView在JNI的引用。如果需要重新调用，需要重新initModelView

    public static native void hiddenEntity(String entityId); //隐藏某个构件

    public static native void hiddenOtherEntities(String entityId);//只显示当前的构件，隐藏其他构件

    public static native void unHiddenEntity(String entityId);//取消隐藏某个构件

    public static native void unHiddenOtherEntities(String entityId);//取消（只显示当前的构件，隐藏其他构件）的状态

}

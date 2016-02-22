#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <iostream>
#include <assert.h>

#include "EBIMModel.hpp"
#define JNIREG_CLASS "net/ezbim/modelview/ModelView"

EBIMModel ebimModel;


extern "C" {
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_init(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_step(JNIEnv * env, jobject obj);
    JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_loadObject(JNIEnv * env, jobject obj, jstring address);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonPressEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonReleaseEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseMoveEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardDown(JNIEnv * env, jobject obj, jint key);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardUp(JNIEnv * env, jobject obj, jint key);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSeveralTimes(JNIEnv * env, jobject obj);
//    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadTest(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadIVE(JNIEnv * env, jobject obj,jstring address);
    JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getFloorNames(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomModel(JNIEnv * env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onHome(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onPanModel(JNIEnv * env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y);
    JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_preProcessBIMFile(JNIEnv * env, jobject obj, jstring address,jboolean btFloor);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_startRendering(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloor(JNIEnv * env, jobject obj,jobjectArray jlist);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unloadByFloor(JNIEnv * env, jobject obj,jobjectArray jlist);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloorName(JNIEnv * env, jobject obj,jstring floorName);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadByFloorName(JNIEnv * env, jobject obj,jstring floorName);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadAll(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_rotationBegin(JNIEnv * env, jobject obj,jint hideLevel);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setFrameIgnore(JNIEnv * env, jobject obj,jboolean isIgnore);
    JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getViewportCameraView(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToViewPortCenter(JNIEnv * env, jobject obj,jobject viewMap);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setSkyBox(JNIEnv * env, jobject obj,jstring imgPath);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSkyBox(JNIEnv * env, jobject obj);
    JNIEXPORT jstring JNICALL Java_net_ezbim_modelview_ModelView_clickSelection(JNIEnv * env, jobject obj,jdouble doubleX,jdouble doubleY);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_highlight(JNIEnv * env, jobject obj,jstring entity);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHighlight(JNIEnv * env, jobject obj,jstring entity);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHighLightCurSelect(JNIEnv * env, jobject obj);
    JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM * vm, void * reserved);
};

JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM * vm, void * reserved) {

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_init(JNIEnv * env, jobject obj, jint width, jint height){
    ebimModel.initWithView(0,0,width,height);
    ebimModel.startRendering();
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_step(JNIEnv * env, jobject obj){
    ebimModel.frame();
}
JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_loadObject(JNIEnv * env, jobject obj, jstring address){
    //Import Strings from JNI
    const char *nativeAddress = env->GetStringUTFChars(address,JNI_FALSE);
    int result = ebimModel.setModelData(std::string(nativeAddress));
    //Release Strings to JNI
    env->ReleaseStringUTFChars(address, nativeAddress);
    return (jint)result;
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonPressEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button){
    ebimModel.mouseButtonPressEvent(x,y,button);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonReleaseEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button){
    ebimModel.mouseButtonReleaseEvent(x,y,button);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseMoveEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y){
    ebimModel.mouseMoveEvent(x,y);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardDown(JNIEnv * env, jobject obj, jint key){
    ebimModel.keyboardDown(key);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardUp(JNIEnv * env, jobject obj, jint key){
    ebimModel.keyboardUp(key);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSeveralTimes(JNIEnv * env, jobject obj){
    ebimModel.updateSeveralTimes();
}
//JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadTest(JNIEnv * env, jobject obj){
//    ebimModel.loadTest();
//}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadIVE(JNIEnv * env, jobject obj,jstring address){
    //Import Strings from JNI
    const char *nativeAddress = env->GetStringUTFChars(address,JNI_FALSE);
    ebimModel.loadIVE(std::string(nativeAddress));
    //Release Strings to JNI
    env->ReleaseStringUTFChars(address, nativeAddress);
}

JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getFloorNames(JNIEnv *env, jobject obj){
    std::vector<std::string> results = ebimModel.getFloorNames();
    jclass list_cls = env->FindClass("java/util/ArrayList");//获得ArrayList类引用
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V"); //获得得构造函数Id,注意第二个参数为<init>，网上有些资料写着为空或者<init></init>是错的。
    jobject list_obj = env->NewObject(list_cls ,list_costruct,""); //创建一个Arraylist集合对象
    jmethodID list_add  = env->GetMethodID(list_cls,"add","(Ljava/lang/Object;)Z");//或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    for(unsigned int i = 0; i < results.size(); i++)
    {
        std::string value = results[i];
        //stdString 转 jstring
        jstring jvalue = env->NewStringUTF(value.c_str());
        env->CallBooleanMethod(list_obj , list_add ,jvalue); //执行Arraylist类实例的add方法
    }
    return list_obj;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomModel(JNIEnv *env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y){
    ebimModel.zoomModel(eventTimeDelta,x,y);
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onHome(JNIEnv *env, jobject obj){
    ebimModel.onHome();
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onPanModel(JNIEnv *env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y){
    ebimModel.onPanModel(eventTimeDelta,x,y);
}

JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_preProcessBIMFile(JNIEnv *env, jobject obj, jstring address,jboolean btFloor){
    const char *nativeAddress = env->GetStringUTFChars(address,JNI_FALSE);
    int result = ebimModel.preProcessBIMFile(std::string(nativeAddress),(bool)btFloor);
    env->ReleaseStringUTFChars(address, nativeAddress);
    //int 转 jint
    return (jint)result;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_startRendering(JNIEnv *env, jobject obj){
    ebimModel.startRendering();
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloor(JNIEnv *env, jobject obj,jobjectArray jlist){
    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V");
    jobject list_obj = env->NewObject(list_cls ,list_costruct,"");
    jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
    jobjectArray array = (jobjectArray)env->CallObjectMethod(jlist, list_toarray);
    std::vector<std::string> sVector;
    for(unsigned int i = 0; i< env->GetArrayLength(array); i++) {
        jstring strObj = (jstring)env->GetObjectArrayElement(array, i);
        const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
        sVector.push_back(std::string(chr));
        env->ReleaseStringUTFChars(strObj, chr);
    }
    ebimModel.loadByFloor(sVector);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unloadByFloor(JNIEnv *env, jobject obj,jobjectArray jlist){
    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V");
    jobject list_obj = env->NewObject(list_cls ,list_costruct,"");
    jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
//    jobject list_obj = env->NewObject(list_cls ,list_toarray,"");
    jobjectArray array = (jobjectArray)env->CallObjectMethod(jlist, list_toarray);
    std::vector<std::string> sVector;
    for(unsigned int i = 0; i< env->GetArrayLength(array); i++) {
        jstring strObj = (jstring)env->GetObjectArrayElement(array, i);
        const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
        sVector.push_back(std::string(chr));
        env->ReleaseStringUTFChars(strObj, chr);
    }
    ebimModel.unloadByFloor(sVector);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloorName(JNIEnv *env, jobject obj,jstring floorName){
    const char *nativeAddress = env->GetStringUTFChars(floorName,JNI_FALSE);
    ebimModel.loadByFloorName(std::string(nativeAddress));
    env->ReleaseStringUTFChars(floorName, nativeAddress);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadByFloorName(JNIEnv *env, jobject obj,jstring floorName){
    const char *nativeAddress = env->GetStringUTFChars(floorName,JNI_FALSE);
    ebimModel.unLoadByFloorName(std::string(nativeAddress));
    env->ReleaseStringUTFChars(floorName, nativeAddress);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadAll(JNIEnv *env, jobject obj){
    ebimModel.unLoadAll();
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_rotationBegin(JNIEnv *env, jobject obj,jint hideLevel){
    ebimModel.rotationBegin((int)hideLevel);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setFrameIgnore(JNIEnv * env, jobject obj,jboolean isIgnore){
    ebimModel.setFrameIgnore(isIgnore);
}
JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getViewportCameraView(JNIEnv *env,jobject obj) {
    std::map<int, std::vector<double>> viewportMap = ebimModel.getViewportCameraView();
    //hashmap
    jclass hashmap_clazz = env->FindClass("java/util/HashMap");
    jmethodID hashmap_costruct = env->GetMethodID(hashmap_clazz, "<init>", "()V");
    jobject hashmap_obj = env->NewObject(hashmap_clazz, hashmap_costruct);
    jmethodID hashmap_put = env->GetMethodID(hashmap_clazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    //ArrayList
    jclass class_arraylist=env->FindClass("java/util/ArrayList");
    jmethodID arraylist_construct_method=env->GetMethodID(class_arraylist, "<init>","()V");
    jobject obj_arraylist =env->NewObject(class_arraylist, arraylist_construct_method, "");
    jobject obj_arraylist2 =env->NewObject(class_arraylist, arraylist_construct_method, "");
    jobject obj_arraylist3 =env->NewObject(class_arraylist, arraylist_construct_method, "");
    jmethodID arraylist_add_method= env->GetMethodID(class_arraylist,"add","(Ljava/lang/Object;)Z");
//    jmethodID arraylist_clear_method= env->GetMethodID(class_arraylist,"clear","()V");

    std::map<int, std::vector<double>>::iterator centerIterator = viewportMap.find(1);
    std::map<int, std::vector<double>>::iterator rotIterator = viewportMap.find(2);
    std::map<int, std::vector<double>>::iterator distanceIterator = viewportMap.find(3);
    std::vector<double> centerVector = centerIterator->second;
    std::vector<double> rotVector = rotIterator->second;
    std::vector<double> distanceVector = distanceIterator->second;

    for(unsigned int i = 0; i<3;i++){
        std::stringstream ss;
        double doubleValue = centerVector[i];
        ss << doubleValue;
        jstring jstring1 = env->NewStringUTF(ss.str().c_str());
        env->CallBooleanMethod(obj_arraylist, arraylist_add_method, jstring1);
    }
    env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("center"), obj_arraylist);
//    env->CallVoidMethod(obj_arraylist, arraylist_clear_method);
    for(unsigned int i = 0; i<16;i++){
        std::stringstream ss;
        double doubleValue = rotVector[i];
        ss << doubleValue;
        jstring jstring1 = env->NewStringUTF(ss.str().c_str());
        env->CallBooleanMethod(obj_arraylist2, arraylist_add_method, jstring1);
    }
    env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("rot"), obj_arraylist2);
//    env->CallVoidMethod(obj_arraylist, arraylist_clear_method);
    std::stringstream ss;
    double doubleValue = distanceVector[0];
    ss << doubleValue;
    jstring jstring1 = env->NewStringUTF(ss.str().c_str());
    env->CallBooleanMethod(obj_arraylist3, arraylist_add_method, jstring1);
    env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("distance"), obj_arraylist3);
//    env->DeleteLocalRef(obj_arraylist);
    return hashmap_obj;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToViewPortCenter(JNIEnv *env, jobject obj,jobject viewMap){
    jclass hashmap_clazz = env->FindClass("java/util/HashMap");
    jmethodID list_get = env->GetMethodID(hashmap_clazz, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jobject centerObject = env->CallObjectMethod(viewMap,list_get,env->NewStringUTF("center"));
    jobject rotObject = env->CallObjectMethod(viewMap,list_get,env->NewStringUTF("rot"));
    jobject distanceObject = env->CallObjectMethod(viewMap,list_get,env->NewStringUTF("distance"));

    std::vector<double> centerVector;
    std::vector<double> rotVector;

    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V");
    jobject list_obj = env->NewObject(list_cls ,list_costruct,"");
    jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");

    jobjectArray centerArray = (jobjectArray)env->CallObjectMethod(centerObject, list_toarray);
    for(unsigned int i = 0; i< 3; i++) {
        jstring strObj = (jstring)env->GetObjectArrayElement(centerArray, i);
        const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
        centerVector.push_back(std::atof(chr));
//        centerVector.push_back(strObj);
    }

    jobjectArray rotArray = (jobjectArray)env->CallObjectMethod(rotObject, list_toarray);
    for(unsigned int i = 0; i< 16; i++) {
        jstring strObj = (jstring)env->GetObjectArrayElement(rotArray, i);
        const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
        rotVector.push_back(std::atof(chr));
//        rotVector.push_back(strObj);
    }
    jobjectArray distanceArray = (jobjectArray)env->CallObjectMethod(distanceObject, list_toarray);
    jstring strObj = (jstring)env->GetObjectArrayElement(distanceArray, 0);
    const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
    double distanceValue = std::atof(chr);
//    double distanceValue = (jdouble)env->GetObjectArrayElement(distanceArray, 0);
    ebimModel.zoomToViewPortCenter(centerVector,distanceValue,rotVector);
}


JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setSkyBox(JNIEnv *env, jobject obj,jstring imgPath){
    const char *nativeAddress = env->GetStringUTFChars(imgPath,JNI_FALSE);
    ebimModel.setSkyBox(std::string(nativeAddress));
    env->ReleaseStringUTFChars(imgPath, nativeAddress);
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSkyBox(JNIEnv * env, jobject obj){
    ebimModel.updateSkyBox();
}

JNIEXPORT jstring JNICALL Java_net_ezbim_modelview_ModelView_clickSelection(JNIEnv * env, jobject obj,jdouble doubleX,jdouble doubleY){
    std::string checkValue =  ebimModel.clickSelection(doubleX,doubleY);
    if(!checkValue.empty()){
        return env->NewStringUTF(checkValue.c_str());
    }
    jstring nullString = env->NewStringUTF("");
    return nullString;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_highlight(JNIEnv * env, jobject obj,jstring entity){
    const char *nativeAddress = env->GetStringUTFChars(entity,JNI_FALSE);
    ebimModel.highlight(std::string(nativeAddress));
    env->ReleaseStringUTFChars(entity, nativeAddress);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHighlight(JNIEnv * env, jobject obj,jstring entity){
    const char *nativeAddress = env->GetStringUTFChars(entity,JNI_FALSE);
    ebimModel.unHighlight(std::string(nativeAddress));
    env->ReleaseStringUTFChars(entity, nativeAddress);
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHighLightCurSelect(JNIEnv * env, jobject obj){
    ebimModel.unHighLightCurSelect();
}
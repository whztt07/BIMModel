#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <iostream>
#include <assert.h>

#include "EBIMModel.hpp"
#define JNIREG_CLASS "net/ezbim/modelview/ModelView"

EBIMModel* pEbimModel;

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
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadTest(JNIEnv * env, jobject obj);
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
    JNIEXPORT jboolean JNICALL Java_net_ezbim_modelview_ModelView_needRenderNow(JNIEnv * env, jobject obj);
    JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM * vm, void * reserved);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_exitModelView(JNIEnv * env, jobject obj);
//    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_cleanModelView(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_hiddenEntity(JNIEnv * env, jobject obj,jstring entityId);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_hiddenOtherEntities(JNIEnv * env, jobject obj,jstring entityId);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHiddenEntity(JNIEnv * env, jobject obj,jstring entityId);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHiddenOtherEntities(JNIEnv * env, jobject obj,jstring entityId);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_resizeView(JNIEnv * env, jobject obj,jint x,jint y,jint width,jint height);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToEntity(JNIEnv * env, jobject obj,jstring entityId);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToEntities(JNIEnv * env, jobject obj,jobjectArray entities);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unTransParentAll(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToViewPortsPosition(JNIEnv * env, jobject obj,jobject viewMap);
    JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getEntityInfo(JNIEnv * env, jobject obj,jstring entityId);
};

JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM * vm, void * reserved) {
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_exitModelView(JNIEnv * env, jobject obj){
    delete pEbimModel;
}
//
//JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_cleanModelView(JNIEnv * env, jobject obj){
//    if(ebimModel.valid()) {
//        ebimModel.deleteEBIMModel();
//    }
//}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_init(JNIEnv * env, jobject obj, jint width, jint height){
    pEbimModel = new EBIMModel();
    pEbimModel->initWithView(0,0,(int)width,(int)height);
    pEbimModel->startRendering();
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_step(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->frame();
    }
}
JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_loadObject(JNIEnv * env, jobject obj, jstring address){
    if(pEbimModel->valid()) {
        //Import Strings from JNI
        const char *nativeAddress = env->GetStringUTFChars(address, JNI_FALSE);
        int result = pEbimModel->setModelData(std::string(nativeAddress));
        //Release Strings to JNI
        env->ReleaseStringUTFChars(address, nativeAddress);
        return (jint) result;
    } else{
        return 1000;
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonPressEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button){
    if(pEbimModel->valid()) {
        pEbimModel->mouseButtonPressEvent((float)x, (float)y, (int)button);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseButtonReleaseEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint button){
    if(pEbimModel->valid()) {
        pEbimModel->mouseButtonReleaseEvent((float)x, (float)y, (int)button);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_mouseMoveEvent(JNIEnv * env, jobject obj, jfloat x, jfloat y){
    if(pEbimModel->valid()) {
        pEbimModel->mouseMoveEvent((float)x, (float)y);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardDown(JNIEnv * env, jobject obj, jint key){
    if(pEbimModel->valid()) {
        pEbimModel->keyboardDown((int)key);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_keyboardUp(JNIEnv * env, jobject obj, jint key){
    if(pEbimModel->valid()) {
        pEbimModel->keyboardUp((int)key);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSeveralTimes(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->updateSeveralTimes();
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadTest(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->loadTest();
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadIVE(JNIEnv * env, jobject obj,jstring address){
    if(pEbimModel->valid()) {
        //Import Strings from JNI
        const char *nativeAddress = env->GetStringUTFChars(address, JNI_FALSE);
        pEbimModel->loadIVE(std::string(nativeAddress));
        //Release Strings to JNI
        env->ReleaseStringUTFChars(address, nativeAddress);
    }
}

JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getFloorNames(JNIEnv *env, jobject obj){
    jclass list_cls = env->FindClass("java/util/ArrayList");//获得ArrayList类引用
    jmethodID list_costruct = env->GetMethodID(list_cls, "<init>",
                                               "()V"); //获得得构造函数Id,注意第二个参数为<init>，网上有些资料写着为空或者<init></init>是错的。
    jobject list_obj = env->NewObject(list_cls, list_costruct, ""); //创建一个Arraylist集合对象
    if(pEbimModel->valid()) {
        std::vector <std::string> results = pEbimModel->getFloorNames();
        jmethodID list_add = env->GetMethodID(list_cls, "add",
                                              "(Ljava/lang/Object;)Z");//或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
        for (unsigned int i = 0; i < results.size(); i++) {
            std::string value = results[i];
            //stdString 转 jstring
            jstring jvalue = env->NewStringUTF(value.c_str());
            env->CallBooleanMethod(list_obj, list_add, jvalue); //执行Arraylist类实例的add方法
        }
    }
    return list_obj;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomModel(JNIEnv *env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y){
    if(pEbimModel->valid()) {
        pEbimModel->zoomModel(eventTimeDelta, x, y);
    }
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onHome(JNIEnv *env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->onHome();
    }
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_onPanModel(JNIEnv *env, jobject obj,jdouble eventTimeDelta,jfloat x, jfloat y){
    if(pEbimModel->valid()) {
        pEbimModel->onPanModel(eventTimeDelta, x, y);
    }
}

JNIEXPORT jint JNICALL Java_net_ezbim_modelview_ModelView_preProcessBIMFile(JNIEnv *env, jobject obj, jstring address,jboolean btFloor){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(address, JNI_FALSE);
        int result = pEbimModel->preProcessBIMFile(std::string(nativeAddress), (bool) btFloor);
        env->ReleaseStringUTFChars(address, nativeAddress);
        //int 转 jint
        return (jint) result;
    }else{
        return 1000;
    }
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_startRendering(JNIEnv *env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->startRendering();
    }
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloor(JNIEnv *env, jobject obj,jobjectArray jlist){
    if(pEbimModel->valid()) {
        jclass list_cls = env->FindClass("java/util/ArrayList");
        jmethodID list_costruct = env->GetMethodID(list_cls, "<init>", "()V");
        jobject list_obj = env->NewObject(list_cls, list_costruct, "");
        jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
        jobjectArray array = (jobjectArray) env->CallObjectMethod(jlist, list_toarray);
        std::vector <std::string> sVector;
        for (unsigned int i = 0; i < env->GetArrayLength(array); i++) {
            jstring strObj = (jstring) env->GetObjectArrayElement(array, i);
            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
            sVector.push_back(std::string(chr));
            env->ReleaseStringUTFChars(strObj, chr);
        }
        pEbimModel->loadByFloor(sVector);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unloadByFloor(JNIEnv *env, jobject obj,jobjectArray jlist){
    if(pEbimModel->valid()) {
        jclass list_cls = env->FindClass("java/util/ArrayList");
        jmethodID list_costruct = env->GetMethodID(list_cls, "<init>", "()V");
        jobject list_obj = env->NewObject(list_cls, list_costruct, "");
        jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
//    jobject list_obj = env->NewObject(list_cls ,list_toarray,"");
        jobjectArray array = (jobjectArray) env->CallObjectMethod(jlist, list_toarray);
        std::vector <std::string> sVector;
        for (unsigned int i = 0; i < env->GetArrayLength(array); i++) {
            jstring strObj = (jstring) env->GetObjectArrayElement(array, i);
            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
            sVector.push_back(std::string(chr));
            env->ReleaseStringUTFChars(strObj, chr);
        }
        pEbimModel->unloadByFloor(sVector);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_loadByFloorName(JNIEnv *env, jobject obj,jstring floorName){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(floorName, JNI_FALSE);
        pEbimModel->loadByFloorName(std::string(nativeAddress));
        env->ReleaseStringUTFChars(floorName, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadByFloorName(JNIEnv *env, jobject obj,jstring floorName){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(floorName, JNI_FALSE);
        pEbimModel->unLoadByFloorName(std::string(nativeAddress));
        env->ReleaseStringUTFChars(floorName, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unLoadAll(JNIEnv *env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->unLoadAll();
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_rotationBegin(JNIEnv *env, jobject obj,jint hideLevel){
    if(pEbimModel->valid()) {
        pEbimModel->rotationBegin((int) hideLevel);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setFrameIgnore(JNIEnv * env, jobject obj,jboolean isIgnore){
    if(pEbimModel->valid()) {
        pEbimModel->setFrameIgnore(isIgnore);
    }
}
JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getViewportCameraView(JNIEnv *env,jobject obj) {
    //hashmap
    jclass hashmap_clazz = env->FindClass("java/util/HashMap");
    jmethodID hashmap_costruct = env->GetMethodID(hashmap_clazz, "<init>", "()V");
    jobject hashmap_obj = env->NewObject(hashmap_clazz, hashmap_costruct);
    if(pEbimModel->valid()) {
        jmethodID hashmap_put = env->GetMethodID(hashmap_clazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
        //ArrayList
        jclass class_arraylist = env->FindClass("java/util/ArrayList");
        jmethodID arraylist_construct_method = env->GetMethodID(class_arraylist, "<init>", "()V");
        jobject obj_arraylist = env->NewObject(class_arraylist, arraylist_construct_method, "");
        jobject obj_arraylist2 = env->NewObject(class_arraylist, arraylist_construct_method, "");
        jobject obj_arraylist3 = env->NewObject(class_arraylist, arraylist_construct_method, "");
        jmethodID arraylist_add_method = env->GetMethodID(class_arraylist, "add", "(Ljava/lang/Object;)Z");
//    jmethodID arraylist_clear_method= env->GetMethodID(class_arraylist,"clear","()V");
        std::map <int, std::vector<double>> viewportMap = pEbimModel->getViewportCameraView();
        std::map < int, std::vector < double >> ::iterator
        centerIterator = viewportMap.find(1);
        std::map < int, std::vector < double >> ::iterator
        rotIterator = viewportMap.find(2);
        std::map < int, std::vector < double >> ::iterator
        distanceIterator = viewportMap.find(3);
        std::vector <double> centerVector = centerIterator->second;
        std::vector <double> rotVector = rotIterator->second;
        std::vector <double> distanceVector = distanceIterator->second;

        for (unsigned int i = 0; i < 3; i++) {
            std::stringstream ss;
            double doubleValue = centerVector[i];
            ss << doubleValue;
            jstring jstring1 = env->NewStringUTF(ss.str().c_str());
            env->CallBooleanMethod(obj_arraylist, arraylist_add_method, jstring1);
        }
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("center"), obj_arraylist);
//    env->CallVoidMethod(obj_arraylist, arraylist_clear_method);
        for (unsigned int i = 0; i < 16; i++) {
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
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("distance"),
                              obj_arraylist3);
//    env->DeleteLocalRef(obj_arraylist);
    }
    return hashmap_obj;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToViewPortCenter(JNIEnv *env, jobject obj,jobject viewMap){
    if(pEbimModel->valid()) {
        jclass hashmap_clazz = env->FindClass("java/util/HashMap");
        jmethodID list_get = env->GetMethodID(hashmap_clazz, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
        jobject centerObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("center"));
        jobject rotObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("rot"));
        jobject distanceObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("distance"));

        std::vector <double> centerVector;
        std::vector <double> rotVector;

        jclass list_cls = env->FindClass("java/util/ArrayList");
        jmethodID list_costruct = env->GetMethodID(list_cls, "<init>", "()V");
        jobject list_obj = env->NewObject(list_cls, list_costruct, "");
        jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");

        jobjectArray centerArray = (jobjectArray) env->CallObjectMethod(centerObject, list_toarray);
        for (unsigned int i = 0; i < 3; i++) {
            jstring strObj = (jstring) env->GetObjectArrayElement(centerArray, i);
            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
            centerVector.push_back(std::atof(chr));
//        centerVector.push_back(strObj);
        }

        jobjectArray rotArray = (jobjectArray) env->CallObjectMethod(rotObject, list_toarray);
        for (unsigned int i = 0; i < 16; i++) {
            jstring strObj = (jstring) env->GetObjectArrayElement(rotArray, i);
            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
            rotVector.push_back(std::atof(chr));
//        rotVector.push_back(strObj);
        }
        jobjectArray distanceArray = (jobjectArray) env->CallObjectMethod(distanceObject,
                                                                          list_toarray);
        jstring strObj = (jstring) env->GetObjectArrayElement(distanceArray, 0);
        const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
        double distanceValue = std::atof(chr);
//    double distanceValue = (jdouble)env->GetObjectArrayElement(distanceArray, 0);
        pEbimModel->zoomToViewPortCenter(centerVector, distanceValue, rotVector);
    }
}


JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_setSkyBox(JNIEnv *env, jobject obj,jstring imgPath){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(imgPath, JNI_FALSE);
        pEbimModel->setSkyBox(std::string(nativeAddress));
        env->ReleaseStringUTFChars(imgPath, nativeAddress);
    }
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_updateSkyBox(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->updateSkyBox();
    }
}

JNIEXPORT jstring JNICALL Java_net_ezbim_modelview_ModelView_clickSelection(JNIEnv * env, jobject obj,jdouble doubleX,jdouble doubleY){
    if(pEbimModel->valid()) {
        std::string checkValue = pEbimModel->clickSelection(doubleX, doubleY);
        if (!checkValue.empty()) {
            return env->NewStringUTF(checkValue.c_str());
        }
    }
    jstring nullString = env->NewStringUTF("");
    return nullString;
}

JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_highlight(JNIEnv * env, jobject obj,jstring entity){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entity, JNI_FALSE);
        pEbimModel->highlight(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entity, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHighlight(JNIEnv * env, jobject obj,jstring entity){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entity, JNI_FALSE);
        pEbimModel->unHighlight(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entity, nativeAddress);
    }
}
JNIEXPORT jboolean JNICALL Java_net_ezbim_modelview_ModelView_needRenderNow(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()){
        return pEbimModel->needRenderNow();
    }
    return false;
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_hiddenEntity(JNIEnv * env, jobject obj,jstring entityId){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        pEbimModel->hiddenEntity(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_hiddenOtherEntities(JNIEnv * env, jobject obj,jstring entityId){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        pEbimModel->hiddenOtherEntities(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHiddenEntity(JNIEnv * env, jobject obj,jstring entityId){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        pEbimModel->unHiddenEntity(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unHiddenOtherEntities(JNIEnv * env, jobject obj,jstring entityId){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        pEbimModel->unHiddenOtherEntities(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_resizeView(JNIEnv * env, jobject obj,jint x,jint y,jint width,jint height){
    if(pEbimModel->valid()) {
        pEbimModel->resizeView((int)x,(int)y,(int)width,(int)height);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToEntity(JNIEnv * env, jobject obj,jstring entityId){
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        pEbimModel->zoomToEntity(std::string(nativeAddress));
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToEntities(JNIEnv * env, jobject obj,jobject entities){
    if(pEbimModel->valid()) {
        jclass list_cls = env->FindClass("java/util/ArrayList");
        jmethodID list_costruct = env->GetMethodID(list_cls, "<init>", "()V");
        jobject list_obj = env->NewObject(list_cls, list_costruct, "");
        jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
        jobjectArray array = (jobjectArray) env->CallObjectMethod(entities, list_toarray);
        std::vector <std::string> sVector;
        for (unsigned int i = 0; i < env->GetArrayLength(array); i++) {
            jstring strObj = (jstring) env->GetObjectArrayElement(array, i);
            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
            sVector.push_back(std::string(chr));
            env->ReleaseStringUTFChars(strObj, chr);
        }
        pEbimModel->zoomToEntities(sVector);
    }
}
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_unTransParentAll(JNIEnv * env, jobject obj){
    if(pEbimModel->valid()) {
        pEbimModel->unTransParentAll();
    }
}
//老的视口参数还原
JNIEXPORT void JNICALL Java_net_ezbim_modelview_ModelView_zoomToViewPortsPosition(JNIEnv * env, jobject obj,jobject viewMap){
    if(pEbimModel->valid()) {
//        jclass hashmap_clazz = env->FindClass("java/util/HashMap");
//        jmethodID list_get = env->GetMethodID(hashmap_clazz, "get","(Ljava/lang/Object;)Ljava/lang/Object;");
//        jobject centerObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("center"));
//        jobject rotObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("rot"));
//        jobject distanceObject = env->CallObjectMethod(viewMap, list_get, env->NewStringUTF("distance"));
//        std::vector <double> centerVector;
//        std::vector <double> rotVector;
//        jclass list_cls = env->FindClass("java/util/ArrayList");
//        jmethodID list_costruct = env->GetMethodID(list_cls, "<init>", "()V");
//        jobject list_obj = env->NewObject(list_cls, list_costruct, "");
//        jmethodID list_toarray = env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
//        jobjectArray centerArray = (jobjectArray) env->CallObjectMethod(centerObject, list_toarray);
//        for (unsigned int i = 0; i < 3; i++) {
//            jstring strObj = (jstring) env->GetObjectArrayElement(centerArray, i);
//            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
//            centerVector.push_back(std::atof(chr));
//        }
//
//        jobjectArray rotArray = (jobjectArray) env->CallObjectMethod(rotObject, list_toarray);
//        for (unsigned int i = 0; i < 16; i++) {
//            jstring strObj = (jstring) env->GetObjectArrayElement(rotArray, i);
//            const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
//            rotVector.push_back(std::atof(chr));
//        }
//        jobjectArray distanceArray = (jobjectArray) env->CallObjectMethod(distanceObject,list_toarray);
//        jstring strObj = (jstring) env->GetObjectArrayElement(distanceArray, 0);
//        const char *chr = env->GetStringUTFChars(strObj, JNI_FALSE);
//        double distanceValue = std::atof(chr);
//        pEbimModel->zoomToViewPortCenter(centerVector, distanceValue, rotVector);
    }
}
JNIEXPORT jobject JNICALL Java_net_ezbim_modelview_ModelView_getEntityInfo(JNIEnv * env, jobject obj,jstring entityId){
    //hashmap
    jclass hashmap_clazz = env->FindClass("java/util/HashMap");
    jmethodID hashmap_costruct = env->GetMethodID(hashmap_clazz, "<init>", "()V");
    jobject hashmap_obj = env->NewObject(hashmap_clazz, hashmap_costruct);
    if(pEbimModel->valid()) {
        const char *nativeAddress = env->GetStringUTFChars(entityId, JNI_FALSE);
        jmethodID hashmap_put = env->GetMethodID(hashmap_clazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
        std::map<std::string,std::string> entityInfoMap = pEbimModel->getEntity(std::string(nativeAddress));
        std::map<std::string, std::map<std::string, std::string>> entityPropertiesMap = pEbimModel->getEntityProperties(std::string(nativeAddress));
        std::string floorString = entityInfoMap.find("floor")->second;
        std::string domainString = entityInfoMap.find("domain")->second;
        std::string categoryString = entityInfoMap.find("category")->second;
        std::string nameString = entityInfoMap.find("name")->second;
        std::string revitIdString = entityInfoMap.find("revitId")->second;
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("floor"), env->NewStringUTF(floorString.c_str()));
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("domain"), env->NewStringUTF(domainString.c_str()));
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("category"), env->NewStringUTF(categoryString.c_str()));
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("name"), env->NewStringUTF(nameString.c_str()));
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("revitId"), env->NewStringUTF(revitIdString.c_str()));
        std::map<std::string, std::map<std::string, std::string>> ::iterator it;
        jobject proMap_obj = env->NewObject(hashmap_clazz, hashmap_costruct);
        for(it=entityPropertiesMap.begin();it!=entityPropertiesMap.end();it++){
            jobject valueMap_obj = env->NewObject(hashmap_clazz, hashmap_costruct);
            std::map<std::string, std::string> valueMap = it->second;
            std::map<std::string, std::string>::iterator iter;
            for(iter=valueMap.begin();iter!=valueMap.end();iter++){
                env->CallObjectMethod(valueMap_obj, hashmap_put,env->NewStringUTF((iter->first).c_str()),env->NewStringUTF((iter->second).c_str()));
            }
            env->CallObjectMethod(proMap_obj, hashmap_put,env->NewStringUTF((it->first).c_str()),valueMap_obj);
        }
        env->CallObjectMethod(hashmap_obj, hashmap_put, env->NewStringUTF("properties"),proMap_obj);
        env->ReleaseStringUTFChars(entityId, nativeAddress);
    }
    return hashmap_obj;
}
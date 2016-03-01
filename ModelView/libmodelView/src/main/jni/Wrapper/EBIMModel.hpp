//
// Created by dev on 15/12/30.
//

#ifndef BIMMODELTEST_EBIMMODEL_H
#define BIMMODELTEST_EBIMMODEL_H

//Android log
#include <android/log.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

//Standard libraries
#include <string>
#include <sstream>
#include <map>
#include "IModelViewer.h"
#include "ModelViewer.h"
#include "IYZProjectCore.h"
#include "IYZComponentCore.h"
#include "YZPrerequire.h"
#include "IYZModelCore.h"
#include "IYZTemplateCore.h"
#include "jni.h"

#include "OsgAndroidNotifyHandler.hpp"

#include <osgDB/Registry>
USE_OSGPLUGIN(ive)
//USE_OSGPLUGIN(tga)
//USE_OSGPLUGIN(jpeg)

#define  LOG_TAG    "EBIMLIB"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


struct YZOpenBIMState
{
    int YZERROR = 0;
    int YZSUCCESS = 1 << 0;
    int DATABASE_VERSION_HIGH = 1 << 1;
    int DATABASE_VERSION_LOW = 1 << 2;
};

class EBIMModel{

public:
    EBIMModel();
    ~EBIMModel();
//    void deleteEBIMModel();
    void resizeView(int x,int y,int width,int height);
    OsgAndroidNotifyHandler *_notifyHandler;
    bimWorld::IModelViewer* modelViewer;
    bool valid();
    //初始化界面
    void initWithView(int x,int y,int width,int height);
    //加载模型数据
    int setModelData(std::string path);
    bool needRenderNow();
    void loadTest();
    void loadIVE(std::string path);
    std::vector<std::string> getFloorNames();
    void loadByFloor(std::vector<std::string> floorNames);
    void unloadByFloor(std::vector<std::string> floorNames);
    void loadByFloorName(std::string floorName);
    void unLoadByFloorName(std::string floorName);
    void unLoadAll();
//  pragma mark - 模型操作
    void setViewerMode();
    void startRendering();
    void updateSeveralTimes();
    void frame();
    int preProcessBIMFile(std::string path, bool byFloor);
    //Events
    void mouseButtonPressEvent(float x,float y,int button);
    void mouseButtonReleaseEvent(float x,float y,int button);
    void mouseMoveEvent(float x,float y);
    void keyboardDown(int key);
    void keyboardUp(int key);
    void zoomModel(double eventTimeDelta, float dx, float dy);
    void onHome();
    void onPanModel(double eventTimeDelta, float dx, float dy);
    //开始旋转
    void rotationBegin(int hideLevel);
    void setFrameIgnore(bool isIgnore);
////天空盒
    void setSkyBox(std::string imgPath);
    void updateSkyBox();

    std::string clickSelection(double x,double y);

// 获取视口参数
    std::map<int,std::vector<double>>  getViewportCameraView();
    //pragma mark - 视口截图
    std::map<int,std::vector<double>>  glToUIImage();

// 定位到视口
    void zoomToViewPortCenter(std::vector<double> center,double distance,std::vector<double> rot);

//构件 定位
    void zoomToEntities(std::vector<std::string> entityArray);
    bool zoomToEntity(std::string entityId);
//位置 定位
    void zoomToViewPortsPosition(std::vector<std::string> viewPortsPosition,std::vector<std::string> viewPortsTarget, std::vector<std::string> viewPortsUpVector,std::vector<std::string> viewPortsmatrix);
    //定位前先全透明
    void transparentAll();
//取消透明，定位后会透明，定位还原
    void unTransParentAll();
//楼层
    void modelSHFloor(std::string floorName,bool hidden);

    std::vector<std::string> getDomainNames(); // 专业
    std::vector<std::string> getCategoryNames(std::string domain); // 类别
    std::vector<std::string> getEntityTypeNames(std::string domain ,std::string category); // 构件类型
    std::map<std::string,std::string> getEntity(std::string uuid);
    std::map<std::string, std::map<std::string, std::string>> getEntityProperties(std::string uuid);
//专业
    void modelSHDomain(std::string domainName,bool hidden,bool child);
//专业->大类
    void modelSHCategory(std::string categoryName,std::string domainName,bool hidden,bool child);
//专业->大类->小类
    void modelSHEntityType(std::string entityTypeName,std::string categoryName,std::string domain,bool hidden,bool child);

//高亮
    void highlight(std::string entityId);
//取消高亮
    void unHighlight(std::string entityId);
    //构件 隐藏
    void hiddenEntity(std::string entityId);
//构件 显示
    void hiddenOtherEntities(std::string entityId);
//取消隐藏 被隐藏
    void unHiddenEntity(std::string entityId);
//取消隐藏 被显示
    void unHiddenOtherEntities(std::string entityId);

private:
    std::string entityIdBySelect;

};

#endif //BIMMODELTEST_EBIMMODEL_H
//
// Created by dev on 15/12/30.
//

#include "EBIMModel.hpp"
#include <string>

EBIMModel::EBIMModel() {
    modelViewer = NULL;
}

EBIMModel::~EBIMModel() {
    LOGE("EBIMMODEL DELETE");
}

//void deleteEBIMModel(){
//    delete modelViewer;
//}

bool EBIMModel::valid(){
    if(modelViewer == NULL){
        return false;
    }
    return true;
}

//初始化界面
//return 0  =   failed
//return 1  =   success
void EBIMModel::initWithView(int x,int y,int width,int height){
    _notifyHandler = new OsgAndroidNotifyHandler();
    _notifyHandler->setTag("Osg Viewer");
    osg::setNotifyHandler(_notifyHandler);
    osg::notify(osg::ALWAYS)<<"OSG Notify Testing"<<std::endl;
    modelViewer = new bimWorld::ModelViewer(x,y,width,height);
    modelViewer->CameraManipulator()->bindMouseEvent(bimWorld::RIGHT_MOUSE_BUTTON, bimWorld::onRotateCamera);
    bimWorld::CategoryNode floor(YZ::YZ_FLOOR);
    bimWorld::CategoryNode major(YZ::YZ_DOMAIN);
    bimWorld::CategoryNode categories(YZ::YZ_CATEGORY);
    bimWorld::CategoryNode name(YZ::YZ_TEMPLATE_NAME);
    std::vector<bimWorld::CategoryNode> children;
    categories.addParent(major);
    name.addParent(categories);
    children.push_back(name);
    children.push_back(floor);
    modelViewer->ModelLoader()->setGraphStructure(children);
    bimWorld::ISelectionController* selectionController = modelViewer->SelectionController();
    selectionController->registSelectEvent([this](const std::vector<std::string> &items) {
        if (items.size() > 0) {
            std::string entity = items[0];
            if (YZ::isModelGroup(entity)) {
                entityIdBySelect = entity;
            } else {
                std::string groupId = YZ::getComponentOutmostGroup(entity);
                if (groupId.empty()) {
                    entityIdBySelect = entity;
                } else {
                    entityIdBySelect = groupId;
                }
            }
            //
        }
    },modelViewer,"modelViewer");
}

//加载模型数据
//return 0  =   failed
//return 1  =   success
//return 2  =   version low
//return 3  =   version height
int EBIMModel::setModelData(std::string path){
    LOGE(("setModelData::"+path).c_str());
    modelViewer->ModelLoader()->unLoadAll();
    int ret = modelViewer->ModelLoader()->connectDAL(path);
    if(ret == YZ::YZSUCCESS){
        return 1;
    }
    if (ret == YZ::YZERROR) {
        return 0;
    }
    if (ret == YZ::DATABASE_VERSION_HIGH) {
        return 2;
    }
    if (ret == YZ::DATABASE_VERSION_LOW) {
        return 3;
    }else{
        return 5;
    }
    std::vector<std::string> floorNames;
    YZ::getFloorName(floorNames);
//    modelViewer->ModelLoader()->loadFloorsFromDAL(floorNames);
    modelViewer->ModelLoader()->loadSingleFloorFromDAL(floorNames[0]);
//    modelViewer->ModelLoader()->loadSingleFloorFromDAL(floorNames[1]);
//    modelViewer->RenderingThread()->updateSeveralTimes();
}

bool EBIMModel::needRenderNow(){
    return modelViewer->RenderingThread()->isRendering();
}

//设置view的操作模式
void EBIMModel::setViewerMode(){

}
//开始渲染
void EBIMModel::startRendering(){
    modelViewer->RenderingThread()->startRendering();
}
//刷新模型视图
void EBIMModel::updateSeveralTimes(){
    modelViewer->RenderingThread()->updateSeveralTimes();
}
//根据控件帧率触发的绘制事件
void EBIMModel::frame(){
//    modelViewer->RenderingThread()->updateSeveralTimes();
    modelViewer->RenderingThread()->loop();
}
//Events
void EBIMModel::mouseButtonPressEvent(float x,float y,int button){
    modelViewer->EventHandlers()->onMousePress(x,y,4);
}
void EBIMModel::mouseButtonReleaseEvent(float x,float y,int button){
    modelViewer->EventHandlers()->onMouseRelease(x,y,4);
}
void EBIMModel::mouseMoveEvent(float x,float y){
//    modelViewer->EventHandlers()->onMouseMove(x,y);
//    modelViewer->CameraManipulator()->onRotateCamera(x,y);
    modelViewer->CameraOperation()->onRotateCamera(0,x,y);
}
void EBIMModel::keyboardDown(int key){
    modelViewer->EventHandlers()->onKeyPress(key);
}
void EBIMModel::keyboardUp(int key){
    modelViewer->EventHandlers()->onKeyRelease(key);
}

void EBIMModel::loadTest(){
    modelViewer->ModelLoader()->loadBox();
}

void EBIMModel::loadIVE(std::string path) {
    modelViewer->ModelLoader()->load(path.c_str());
}

std::vector<std::string> EBIMModel::getFloorNames(){
    std::vector<std::string> floorNames;
    YZ::getFloorName(floorNames);
    return floorNames;
}
void EBIMModel::loadByFloor(std::vector<std::string> floorNames){
    modelViewer->ModelLoader()->loadFloorsFromDAL(floorNames);
    modelViewer->RenderingThread()->updateSeveralTimes();
}
void EBIMModel::unloadByFloor(std::vector<std::string> floorNames){
    modelViewer->ModelLoader()->unloadFloorsFromDAL(floorNames);
    modelViewer->RenderingThread()->updateSeveralTimes();
}
void EBIMModel::loadByFloorName(std::string floorName){
    modelViewer->ModelLoader()->loadSingleFloorFromDAL(floorName);
    modelViewer->RenderingThread()->updateSeveralTimes();
}
void EBIMModel::unLoadByFloorName(std::string floorName){
    modelViewer->ModelLoader()->unloadSingleFloorFromDAL(floorName);
    modelViewer->RenderingThread()->updateSeveralTimes();
}
void EBIMModel::unLoadAll(){
    modelViewer->ModelLoader()->unLoadAll();
}

void EBIMModel::zoomModel(double eventTimeDelta, float dx, float dy){
    modelViewer->CameraOperation()->onZoomModel(eventTimeDelta,dx,dy);
}

void EBIMModel::onHome(){
    modelViewer->CameraOperation()->onHome();
}

void EBIMModel::onPanModel(double eventTimeDelta, float dx, float dy){
    modelViewer->CameraOperation()->onPanModel(eventTimeDelta,dx,dy);
}

void EBIMModel::rotationBegin(int hideLevel){
    modelViewer->FixedFrameRate()->hide(hideLevel);
}

void EBIMModel::setFrameIgnore(bool isIgnore) {
    modelViewer->FixedFrameRate()->setIgnoreFrame(true);
}

void EBIMModel::setSkyBox(std::string imgPath){
    modelViewer->BackgroundSetting()->setSkyBox(imgPath);
}

void EBIMModel::updateSkyBox(){
    modelViewer->BackgroundSetting()->updateSkyBoxRadius();
}

//		YZERROR = 0,//处理失败
//      YZSUCCESS = 1,//处理成功
//      DATABASE_VERSION_HIGH = 2,//打开数据库文件版本过高
//      DATABASE_VERSION_LOW = 3,//打开数据库版本过低
//      FILE_LOST = 4//文件缺失
//      5 其他
int EBIMModel::preProcessBIMFile(std::string path,bool byFloor){
    YZ::ResultState resultState = YZ::PreProcessBIMFile(path,byFloor);
    YZ::CloseBIMFile();
    if(YZ::YZERROR == resultState){
        return 0;
    }else if(YZ::YZSUCCESS == resultState){
        return 1;
    }else if(YZ::DATABASE_VERSION_HIGH == resultState){
        return 2;
    }else if(YZ::DATABASE_VERSION_LOW == resultState){
        return 3;
    }else {
        return 5;
    }
}

std::map<int,std::vector<double>>  EBIMModel::getViewportCameraView(){
    std::map<int,std::vector<double>> viewPortMap;
    bimWorld::BIMCameraView cameraView;
    bool isGetModelRight = modelViewer->CameraSetting()->getBIMCameraView(cameraView);
    if (false == isGetModelRight) {
        return viewPortMap;
    }
    std::vector<double> centerVector;
    std::vector<double> rotVector;
    std::vector<double> distanceVector;
    double distanceValue = 0;
    for (int i = 0; i < 16; i++) {
        rotVector.push_back(cameraView.rot[i]);
    }
    for (int i = 0;i < 3;i++) {
       centerVector.push_back(cameraView.center[i]);
    }
    distanceVector.push_back(cameraView.distance);
    viewPortMap.insert(std::make_pair(1,centerVector));
    viewPortMap.insert(std::make_pair(2,rotVector));
    viewPortMap.insert(std::make_pair(3,distanceVector));
    return viewPortMap;
}

void EBIMModel::zoomToViewPortCenter(std::vector<double> center,double distance,std::vector<double> rot){
    bimWorld::BIMCameraView camera;
    for (int i = 0; i < 3; i++) {
        camera.center[i] = center[i];
    }
    for (int i = 0; i< 16; i++) {
        camera.rot[i] = rot[i];
    }
    camera.distance = distance;
    modelViewer->CameraSetting()->setBIMCameraView(camera);
}

std::string EBIMModel::clickSelection(double x,double y) {
//    modelViewer->CameraManipulator()->orbitPick(x, y);
    bool isCheck = modelViewer->CameraOperation()->orbitPick(x,y);
    //需要保证orbitPick这个方法在执行完毕以后，registSelectEvent里回调的方法一定被执行到！
    if(isCheck && !entityIdBySelect.empty()){
        return entityIdBySelect;
    }
    return "";
}



//高亮
void EBIMModel::highlight(std::string entityId){
    if (YZ::isModelGroup(entityId)){
    std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            modelViewer->NodeControl()->highlightWithTopGroup(entities[0]);
        }
    }
    // entity
    std::string groupId = YZ::getComponentOutmostGroup(entityId);
    if (groupId.empty()){
        modelViewer->NodeControl()->highlight(entityId);
    } else {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(groupId, entities)) {
        modelViewer->NodeControl()->highlightWithTopGroup(entities[0]);
        }
    }
}

void EBIMModel::unHighlight(std::string entityId){
    bimWorld::INodeEntityController* nodeEntityController =  modelViewer->NodeControl();
    if (YZ::isModelGroup(entityId)) {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            modelViewer->NodeControl()->unHighlightWithTopGroup(entities[0]);
        }
    }
    // entity
    auto groupId = YZ::getComponentOutmostGroup(entityId);
    if (groupId.empty()) {
        modelViewer->NodeControl()->unHighlight(entityId);
    } else {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(groupId, entities)) {
            modelViewer->NodeControl()->unHighlightWithTopGroup(entities[0]);
        }
    }
}

//构件 隐藏
void EBIMModel::hiddenEntity(std::string entityId){
    if (YZ::isModelGroup(entityId)) {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            int entitiesLen = entities.size();
            for (int i = 0; i<entitiesLen;i++) {
                std::string item = entities[i];
                modelViewer->NodeControl()->hide(item);
            }
        }
    } else {
        modelViewer->NodeControl()->hide(entityId);
    }
    modelViewer->RenderingThread()->updateSeveralTimes();
}
//构件显示
void EBIMModel::hiddenOtherEntities(std::string entityId){
    if (YZ::isModelGroup(entityId)) {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            modelViewer->NodeControl()->hideOthers(entities);
        }
    } else {
        modelViewer->NodeControl()->hideOthers(entityId);
    }
    modelViewer->RenderingThread()->updateSeveralTimes();
}
//取消隐藏 被隐藏
void EBIMModel::unHiddenEntity(std::string entityId){
    if (YZ::isModelGroup(entityId)) {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            int entitiesLen = entities.size();
            for (int i = 0; i< entitiesLen; i++) {
                std::string item = entities[i];
                modelViewer->NodeControl()->unHide(item);
            }
        }
    } else {
        modelViewer->NodeControl()->unHide(entityId);
    }
    modelViewer->RenderingThread()->updateSeveralTimes();
}
//取消隐藏 被显示
void EBIMModel::unHiddenOtherEntities(std::string entityId){
    if (YZ::isModelGroup(entityId)) {
        std::vector<std::string> entities;
        if (YZ::getGroupRelComponent(entityId, entities)) {
            modelViewer->NodeControl()->unHideOthers(entities);
        }
    } else {
        modelViewer->NodeControl()->unHideOthers(entityId);
    }
    modelViewer->RenderingThread()->updateSeveralTimes();
}
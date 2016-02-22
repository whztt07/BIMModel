#ifndef __YZICOMPONENTMGR_H__
#define __YZICOMPONENTMGR_H__
/*
	实体构件数据管理接口类
*/
#include "YZComponent.h"

namespace YZ
{
	class IComponentMgr
	{
	public:
		typedef std::map<std::string, osg::ref_ptr<Component> > MapComponent;

		//创建实体构件并加入当前管理，创建失败返回false，已经存在该ID返回该构件指针comp和false
		virtual bool createComponent(const std::string& uniqueID, CategoryType categoryType, ComponentType compType, Component*& comp) = 0;

		//创建实体构件，不加入当前管理
		virtual Component* newComponent(const std::string& uniqueID, CategoryType categoryType, ComponentType compType) = 0;

		//添加实体构件到当前管理，如果有重复ID，不添加返回false
		virtual bool addComponent(Component* comp, bool autoID = false) = 0;

		//获取所有实体构件
		virtual const MapComponent& getComponent(void) = 0;

		//通过id获取实体构件，如果没有返回为空
		virtual Component* getComponentByID(int ID) = 0;
		virtual Component* getComponentByUniqueID(const std::string& uniqueID) = 0;

		//删除实体构件，成功返回true，没有找到返回false
		virtual bool removeComponentByID(int ID) = 0;
		virtual bool removeComponentByUniqueID(const std::string& uniqueID) = 0;

		//根据楼层卸载构件相关资源
		//virtual bool removeComponentByFloor(int id) = 0;

		//预同步实体构件数据
		//virtual void preSyncComponent(void) = 0;

		//同步实体构件数据
		virtual void syncComponent(IModelMgr* mgr) = 0;

		//清空实体构件
		virtual void clearComponent(void) = 0;

		//获取当前实体构件关联的模板构件数字id集合
		//virtual std::vector<int> getComponentTemplateID() = 0;

		/*模型组相关接口*/
		//
		virtual bool createModelGroup(const std::string& uniqueID, Component*& comp) = 0;

		virtual Component* newModelGroup(const std::string& uniqueID) = 0;

		virtual bool addModelGroup(Component* comp, bool autoID = false) = 0;

		virtual const MapComponent& getModelGroup(void) = 0;

		virtual Component* getModelGroupByID(int ID) = 0;
		virtual Component* getModelGroupByUniqueID(const std::string& uniqueID) = 0;

		virtual bool removeModelGroupByID(int ID) = 0;
		virtual bool removeModelGroupByUniqueID(const std::string& uniqueID) = 0;

		//同步模型组数据
		virtual void syncModelGroup(IModelMgr* mgr) = 0;

		virtual void clearModelGroup(void) = 0;

		//释放数据
		virtual void free(void) = 0;
	};
}
#endif
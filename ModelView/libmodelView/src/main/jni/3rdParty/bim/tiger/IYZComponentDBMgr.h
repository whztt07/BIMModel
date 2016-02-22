#ifndef __YZIComponentDBMgr_H__
#define __YZIComponentDBMgr_H__
/*
实体构件数据库管理接口类
*/
#include "Tiger.h"
#include "IYZParameterList.h"

namespace YZ
{
	class IComponentDBMgr
	{
	public:
		//释放数据
		virtual void free(void) = 0;

		//保存实体构件
		virtual bool saveComponent(void) = 0;

		//保存模型组构件
		virtual bool saveModelGroup(void) = 0;

		//更新实体构件
		virtual bool updateComponent(void) = 0;

		//
		virtual bool clearComponent(void) = 0;

		//
		virtual bool clearModelGroup(void) = 0;

		/*
		主数据库
		*/
		//读取实体构件
		virtual bool loadComponent(void) = 0;

		//根据楼层id读取实体构件
		virtual bool loadComponentByFloor(int id) = 0;

		//读取模型组构件
		virtual bool loadModelGroup(void) = 0;

		//根据楼层id读取实体构件guid
		virtual bool getComponentByFloor(int id, std::vector<std::string>& component) = 0;

		/*
		属性数据库
		*/
		//根据构件id读取所有属性
		virtual bool loadParameterByComponent(const std::string& id) = 0;

		//获取所有属性组名称列表
		virtual bool getParameterGroup(std::vector<std::string>& result) = 0;

		//获取符合专业，类型，名称条件的构件id
		virtual bool getComponentByProperty(int domain, int category, std::string& name, std::vector<std::string>& component) = 0;

		//根据关键字key，在相应的类型type中查找符合条件的 实体构件集合
		//目前type只实现了MODEL_COMPONENT_NAME
		virtual bool getComponentByKeySearch(const std::string& key, ModelDataType type, std::vector<std::string>& component) = 0;
	};
}
#endif
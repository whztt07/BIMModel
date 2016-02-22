#ifndef __YZIMODELMGR_H__
#define __YZIMODELMGR_H__
/*
	模型数据管理接口类
*/
#include "Dragon.h"

namespace YZ
{
 	class IProjectMgr;
	class ITemplateMgr;
	class IComponentMgr;
	class IComputeMgr;
	class IParameterList;

	class IModelMgr
	{
	public:
		//获取工程数据管理指针
		virtual IProjectMgr* getProjectMgr(void) = 0;

		//获取模板构件数据管理指针
		virtual ITemplateMgr* getTemplateMgr(void) = 0;

		//获取实体构件数据管理指针
		virtual IComponentMgr* getComponentMgr(void) = 0;

		//获取计算数据管理指针
		virtual IComputeMgr* getComputeMgr(void) = 0;

		//同步所有数据（从数据库加载的ID数据中 获取可直接使用的指针数据）
		//从数据库加载完数据后调用一次，其他情况下调用没有意义而且增加时间开销
		virtual void synchronize(void) = 0;

		virtual void free(void) = 0;
	};
}
#endif
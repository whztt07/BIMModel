#ifndef __YZGEOMETRYELEMENT_H__
#define __YZGEOMETRYELEMENT_H__
/*
几何实体构件
*/
#include "YZComponent.h"

#define VESRION_GEOMETRY_COMP 1

namespace YZ
{
	class MODEL_API GeometryComp : public Component
	{
	public:
		friend class ComponentMgr;

		//virtual std::string getStrValue(std::string strKey);
		virtual void sync(IModelMgr* mgr);
		//virtual void unsync(void);

		GeometryComp();
		GeometryComp(const std::string& id, CategoryType type);
		virtual ~GeometryComp(void);

	protected:
		//同步几何数据
		virtual void syncOsgGeometry(IModelMgr* mgr){}

		//按照半径进行排序
		//void syncSortByRadius(IModelMgr* mgr);

	protected:
		//static
		//int m_templateID;//所属模板构件

		//dynamic
		//Template* m_template;
	};
}
#endif
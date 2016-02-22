#ifndef __YZGROUPELEMENT_H__
#define __YZGROUPELEMENT_H__
/*
模型组构件
*/
#include "YZRelationComp.h"
#define VESRION_GROUP_ELEMENT 1
namespace YZ
{
	class MODEL_API GroupElement : public RelationComp
	{
	public:
		friend class ComponentMgr;

		virtual const char* className() const{ return "GroupElement"; }
		//virtual void sync(IModelMgr* mgr);

// 		void addRelComponent(Component* comp);
// 		void deleteRelComponent(Component* comp);
// 		const std::unordered_map <int, Component*>& getRelComponent(void) const;

		GroupElement();
		GroupElement(const std::string& id, CategoryType type);
		virtual ~GroupElement(void);
	};
}
#endif
#ifndef __YZSTOREY_H__
#define __YZSTOREY_H__
/*
楼层构件，一个工程只提供一个楼层标准
*/
#include "YZElement.h"
#include "YZGroupElement.h"

#define VESRION_STOREY 1

namespace YZ
{
	class MODEL_API Storey : public Element
	{
	public:
		friend class ProjectMgr;

		//
		void setElevation(float elevation);
		float getElevation(void);

		float getTopElevation(void);

		void setHeight(float height);
		float getHeight(void);

		//楼层下的模型组构件
		void addRelModelGroup(GroupElement* comp);
		void delRelModelGroup(GroupElement* comp);
		const std::vector <GroupElement*>& getRelModelGroup(void) const;
		void clearRelModelGroup(void);

		Storey(void);
		Storey(const std::string& uniqueID);
		virtual ~Storey(void);

	protected:
		float m_elevation;//底标高
		//float m_topElevation;//顶标高
		float m_height;//楼层高度

		//楼层包含的模型组构件
		std::vector<GroupElement*> m_relModelGroup;
	};
}
#endif
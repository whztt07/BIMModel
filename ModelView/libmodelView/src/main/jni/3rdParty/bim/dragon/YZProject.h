#ifndef __YZPROJECT_H__
#define __YZPROJECT_H__
/*
数据来源工程信息
*/
#include "YZElement.h"
#include "YZProjectType.h"

#define VESRION_PROJECT 1

namespace YZ
{
	class MODEL_API Project : public Element
	{
	public:
		friend class ProjectMgr;

		//类型
		void setType(ProjectType type);
		ProjectType getType(void) const;

		//信息
		void setInfo(const std::string& info);
		const std::string& getInfo(void) const;

		Project(void);
		Project(const std::string& uniqueID, ProjectType type);
		virtual ~Project(void);

	protected:
		ProjectType m_type;
		std::string m_info;
	};
}
#endif
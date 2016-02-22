#ifndef __YZITemplateDBMgr_H__
#define __YZITemplateDBMgr_H__
/*
模板构件数据库管理接口类
*/
#include "Tiger.h"

namespace YZ
{
	class ITemplateDBMgr
	{
	public:
		//保存模板构件到数据库
		virtual bool saveTemplate(void) = 0;

		//更新模板构件数据
		virtual bool updateTemplate(void) = 0;

		//读取模板构件
		virtual bool loadTemplate(void) = 0;

		//
		virtual bool clearTemplate(void) = 0;

		//根据模板构件id读取
		virtual bool loadTemplateByIds(const std::vector<int>& ids) = 0;

		//根据构件楼层获取模板构件id
		virtual bool loadTemplateIdByFloor(int id, std::vector<int>& ids) = 0;

		//
		//virtual bool loadTemplateProperty(std::string tempId) = 0;

		//释放数据
		virtual void free(void) = 0;
	};
}
#endif
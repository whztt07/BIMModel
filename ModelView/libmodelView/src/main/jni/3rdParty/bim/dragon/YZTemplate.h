#ifndef __YZTEMPLATE_H__
#define __YZTEMPLATE_H__
/*
模板构件，这里的类型是译筑软件内部定义的模板类型
*/
#include "YZProduct.h"
#include "YZComponent.h"
#define VESRION_TEMPLATE 1
namespace YZ
{
	enum TemplateType
	{
		Template_Unknown = 0,
		//几何构件
		Template_General = 1,
		//引用块
		Template_Blocky = 2,
		//模型组
		Template_Group = 3
	};

	class MODEL_API Template : public Product
	{
	public:
		friend class TemplateMgr;

		virtual std::string getStrValue(std::string strKey);

		//virtual void presync(void);
		virtual void sync(IModelMgr* mgr);

		Template();
		Template(const std::string& id, CategoryType type);
		virtual ~Template(void);

	protected:
		//dynamic
		TemplateType m_yzType;
	};
}
#endif
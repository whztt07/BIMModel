#ifndef __YZELEMENT_H__
#define __YZELEMENT_H__
/*
构件基类，这里的类型是需要在软件中以OSG形式展现的数据，包括需要显示的或者需要构建节点的
*/
#include "Dragon.h"
#include <osg/Group>
#include <osg/Geode>
#define VESRION_ELEMENT 1
namespace YZ
{
	class IModelMgr;
	class IParameterList;
	class Component;

	class MODEL_API Element : public osg::Group
	{
	public:
		//根据类型获取内容
		virtual std::string getStrValue(std::string strKey);

		//预加载数据，数据生成
		//virtual void presync(void);

		//加载数据时 从ID到指针同步
		virtual void sync(IModelMgr* mgr);
		//卸载数据时 指针数据取消关联
		virtual void unsync(void){}

		bool needUpdate(void);

		//ID，唯一标识符
		void setUniqueID(const std::string& id);
		const std::string& getUniqueID(void) const;

		//ID，整数ID，工程唯一
		void setID(int id);
		int getID(void) const;

		//名称
		void setYZName(const std::string& name);
		std::string getYZName(void) const;

		//属性
		IParameterList* getParameterList(void);

		//
		void addRelComponent(Component* comp);
 		void delRelComponent(Component* comp);
		const std::vector <Component*>& getRelComponent(void) const;
		void clearRelComponent(void);

		Element(void);//默认构造函数在读取数据库时使用，其填充数据不需要逻辑
		Element(const std::string& uniqueID);//管理类使用的构造函数
		virtual ~Element(void);

	protected:
		//static
		std::string m_UniqueID;//构件字符串ID
		int m_ID;//构件数字ID
		std::string m_name;//构件名称

		//dynamic
		IParameterList* m_parameterList;//当前构件的属性列表
		bool m_needUpdate;//构件是否需要刷新同步数据

		//与当前构件相关联的实体构件，弱指针
		//具体含义根据具体的Element类型而定
		std::vector<Component*> m_relComponent;
	};
}
#endif
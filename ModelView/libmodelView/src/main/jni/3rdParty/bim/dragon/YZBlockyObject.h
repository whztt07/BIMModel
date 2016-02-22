#ifndef __YZBLOCKYOBJECT_H__
#define __YZBLOCKYOBJECT_H__
/*
块状构件，在插入位置布置块几何
*/
#include "YZTemplate.h"
#define VESRION_BLOCKY_OBJECT 2
namespace YZ
{
	class MODEL_API BlockyObject : public Template
	{
	public:
		friend class TemplateMgr;

		virtual const char* className() const{ return "BlockyObject"; }
		//virtual void presync(void);
		virtual void sync(IModelMgr* mgr);

		//块几何
		//void setBlock(osg::Geode* blck);
		osg::Geode* getBlock(void) const;

		//块引用ID
		//void setBlockRefID(int ref);
		//int getBlockRefID(void) const;

		//块引用
		//void setBlockDef(BlockRef* blk);
		//BlockRef* getBlockDef(void) const;

		BlockyObject(void);
		BlockyObject(const std::string& uniqueID, CategoryType type);
		virtual ~BlockyObject(void);

	protected:
		//osg::ref_ptr<GeometryItem> m_geometry;//几何
		osg::ref_ptr<osg::Geode> m_geometry;//几何
		//int m_blockRefID;//块引用ID
		//BlockRef* m_blockRef;//块引用临时指针，不负责释放
	};
}
#endif
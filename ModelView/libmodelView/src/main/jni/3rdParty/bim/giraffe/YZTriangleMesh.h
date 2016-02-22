#ifndef __YZTriangleMesh_H__
#define __YZTriangleMesh_H__
/*
三角面片实体
根据多个面索引值来确定实体，面索引值三个为一组表示一个三角面片，索引值是紧密相连的
*/
#include "YZMeshSolid.h"

#define VESRION_TRIANGLE_MESH 2

namespace YZ
{
	class GEOMETRY_API TriangleMesh : public MeshSolid
	{
	public:
		TriangleMesh(void);
		TriangleMesh(const TriangleMesh& geometry, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		virtual ~TriangleMesh(void);

		//virtual void drawImplementation(osg::RenderInfo& renderInfo) const;
		virtual GeometryItemType type(void) const{ return GIT_Solid_TriangleMesh; }
		virtual void sync(void);
		//virtual void presync(void);

		//
		void add_mesh(const std::vector<int>& meshs);

		int mesh_count(void) const;
		const std::vector<int>& get_mesh(int index) const;

		//将数据集成进osgGeometry
		void osg_integrate(osg::Geometry* osg);

		//将数据以DrawArray的形式集成进osgGeometry
		void osg_integrate_array(osg::Geometry* osg);

		//void drawTriangle(osg::RenderInfo& renderInfo) const;

		//virtual GeometryItem* _clone(void) const;
		//virtual void reset(void);

		//点数目是否相同
		//virtual bool is_legal(void) const;

		//面索引数目
		//uInt face_count(void) const;

	protected:
		//这里一个std::vector<int>代表一个完整的面或者一部分几何或者一个完整几何
		//根据需要自己定义
		std::vector<std::vector<int> > m_meshs;
	};
}
#endif // __YZTriangleMesh_H__
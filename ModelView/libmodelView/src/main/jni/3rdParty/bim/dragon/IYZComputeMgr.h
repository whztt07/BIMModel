#ifndef __YZICOMPUTEMGR_H__
#define __YZICOMPUTEMGR_H__
/*
�������ݹ���ӿ���
*/

#include "Dragon.h"

namespace YZ
{
	struct GCompRadius
	{
		GCompRadius()
			:m_radius(-1), m_id(-1)
		{}

		GCompRadius(float radius, int id)
			:m_radius(radius), m_id(id)
		{}

		float m_radius;
		int m_id;
	};

	class IComputeMgr
	{
	public:
		//�������
		virtual void clearModel(void) = 0;

		//
		virtual void setGeometryCompRadiusSorted(bool sorted) = 0;
		virtual bool isGeometryCompRadiusSorted(void) = 0;

		//���һ�����ι����뾶���ݽ�������
		virtual void sortGeometryCompRadius(float dRadius, int id) = 0;

		//��ȡ���ݼ��ι����뾶�������еļ���
		virtual const std::vector<GCompRadius>& getAscendingGeometryCompRadius(void) = 0;

		//�������õ�����
		virtual void addAscendingGeometryCompRaidus(const GCompRadius& result) = 0;

		//�ͷ�����
		virtual void free(void) = 0;
	};
}
#endif
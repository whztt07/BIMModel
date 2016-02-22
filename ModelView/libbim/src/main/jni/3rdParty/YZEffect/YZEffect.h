#ifndef __YZ_EFFECT_H__
#define __YZ_EFFECT_H__

#include "config.h"
#include "IEffects.h"
#include "InteractionDefine.h"
#include "MaterialSetting.h"
//#include "Slice.h"

namespace bimWorld
{
	class YIZHU_EXPORT YZEffect : public IEffects
	{
	public:
		YZEffect();
		~YZEffect();

		SHARED_PROPERTY(bimWorld::MaterialSetting, _MaterialSetting, m_materialSetting, this);
//		SHARED_PROPERTY(bimWorld::Slice, _Slice, m_slice, this);

		IMPLEMENT_INTERFACE(bimWorld::IMaterialSetting, _MaterialSetting, MaterialSetting);
		//IMPLEMENT_INTERFACE(bimWorld::ISlice, _Slice, Slice);

	private:

	};
}

#endif // __YZ_EFFECT_H__

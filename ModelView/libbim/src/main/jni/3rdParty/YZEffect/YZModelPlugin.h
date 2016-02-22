#ifndef __YZ_MODEL_PLUGIN_H__
#define __YZ_MODEL_PLUGIN_H__

namespace bimWorld
{
	template <class T>
	class YZModelPlugin
	{
	public:
		YZModelPlugin(T* host)
		{
			if (!host)
			{
				delete this;
				return;
			}
			m_host = host;
		}
	protected:
		T* m_host;
	};
}

#endif // __YZ_MODEL_PLUGIN_H__
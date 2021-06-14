#ifndef _NOCOPY_H_
#define _NOCOPY_H_

namespace cth
{
	class NoCopy
	{
	public: 
		inline NoCopy(){}
		NoCopy(const NoCopy&);
		NoCopy& operator=(const NoCopy&); 
	};
}
#endif
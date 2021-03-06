#ifndef DebugDelete_h
#define DebugDelete_h

#include <iosteream>


class DebugDelete{
	public:
		DebugDelete(std::ostream &s=std::cerr):os(s) { }
		template<typename T> operator(T *p) const { os<<"deleting ..."<<std::endl; delete p; }
	private:
		std::ostream &os;
};



#endif

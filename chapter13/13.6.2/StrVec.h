#ifndef ex_13_39_h
#define ex_13_39_h
#include <string>
#include <memory>
#include <initializer_list>

using std::string;

class StrVec{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) { }
		StrVec(std::initializer_list<string>);
		StrVec(const StrVec&);//
		StrVec& operator=(const StrVec&);//
		~StrVec();//
		StrVec(StrVec&&)noexcept;
		StrVec& operator=(StrVec&&)noexcept;

		void push_back(const string&);//
		size_t size() const { return first_free-elements; }
		size_t capacity() const { return cap-elements; }
		void reserve(size_t);//
		void resize(size_t);//
		string *begin() const { return elements; }
		string *end() const { return first_free; }
	private:
		std::allocator<string> alloc;
		void chk_n_alloc(){	if(size() == capacity()) reallocate(); }
		std::pair<string*,string*> alloc_n_copy(const string*,const string*);//
		void free();//
		void reallocate();//
		string *elements;
		string *first_free;
		string *cap;
};

void StrVec::push_back(const string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}
std::pair<string*,string*> StrVec::alloc_n_copy(const string *b,const string *e)
{
	auto data=alloc.allocate(e-b);
	return { data,uninitialized_copy(b,e,data) };
}
void StrVec::free()
{
	if(elements)
	{
		for(auto p=elements;p!=first_free;p++)
		{
			alloc.destroy(p);
		}
		alloc.deallocate(elements,cap-elements);
	}
}
StrVec::StrVec(const StrVec& s)
{
	auto newdata=alloc_n_copy(s.begin(),s.end());
	elements=newdata.first;
	first_free=newdata.second;
	cap=first_free;
}
StrVec::StrVec(std::initializer_list<string> il)
{
	auto newdata=alloc_n_copy(il.begin(),il.end());
	elements=newdata.first;
	first_free=cap=newdata.second;
}
StrVec::~StrVec()
{ 
	free();
}
StrVec& StrVec::operator=(const StrVec& s)
{ 
	auto newdata=alloc_n_copy(s.begin(),s.end());
	elements=newdata.first;
	first_free=cap=newdata.second;
	return *this;
}
void StrVec::reallocate()
{
	auto newcapacity= size() ? 2*size() : 1;
	auto newdata=alloc.allocate(newcapacity);
	auto dest=newdata;
	auto elem=elements;
	for(size_t i=0;i!=size();++i)
	{
		alloc.construct(dest++,std::move(*elem++));
	}
	free();
	elements=newdata;
	first_free=dest;
	cap=newcapacity+elements;
}
void StrVec::reserve(size_t n)
{
	while(capacity()<=n)
	{
		reallocate();
	}
}
void StrVec::resize(size_t n)
{
	if(n<size())
	{
		auto p=n+elements;
		for(;p!=first_free;++p)
		{
			alloc.destroy(p);
		}
	}
	else if(n<capacity())
	{
		size_t num=n-size();
		for(int i=0;i<num;++i)
		{
			push_back(string());
		}
	}
	else
	{
		reserve(n);
		size_t num=n-size();
		for(int i=0;i<num;++i)
		{
			push_back(string());
		}
	}
}

StrVec::StrVec(StrVec &&rhs) noexcept :elements(rhs.elements),first_free(rhs.first_free),cap(rhs.cap)
{
	rhs.elements=rhs.first_free=rhs.cap=nullptr;
}
StrVec& operator=(StrVec &&rhs) noexcept
{
	if(this!=&rhs)
	{
		free();
		elements=rhs.element;
		first_free=rhs.first_free;
		cap=rhs.cap;
		rhs.elements=rhs.first_free=rhs.cap=nullptr;
	}
	return *this;
}

#endif

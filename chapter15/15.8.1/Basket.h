#ifndef Basket_h
#define Basket_h
#include <memory>

class Basket{
	public:
		void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
		double total_receipt(std::ostream&) const;
	private:
		static bool compare(const std::shared_ptr<Quote> &lhs,const std::shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
		std::map<std::shared_ptr<Quote>,decltype(compare)*> items{compare};
};

double Basket::total_receipt(std::ostream &os) const 
{
	double sum =0.0;
	for(auto iter=items.cbegin();iter!=items.cend();iter=items.upper_bound(*iter))
	{
		sum += print_total(os,**iter,items.count(*iter));
	}
	os<<"Total Sale: "<<sum<<std::endl;
}

#endif

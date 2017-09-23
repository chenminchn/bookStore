// testProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include<iostream>
#include<fstream>
//#include<vector>
#include<string>

using namespace std;

class Salesdata{
public:
	friend istream& Read(istream &is, Salesdata &item);
	friend ostream& Print(ostream &os, Salesdata &item);
	string isbn(){ return bookNo; }
	Salesdata Combine(Salesdata &item);
private:
	string bookNo;
	unsigned units_sold = 0;
	/*double sellingprice = 0.0;
	double saleprice = 0.0;
	double discount = 0.0;*/
};

istream& Read(istream &is, Salesdata &trans){
	//从istream流中读入对象
	is >> trans.bookNo >> trans.units_sold;
	return is;
}

Salesdata Salesdata::Combine(Salesdata &item){
	this->units_sold = item.units_sold;
	/*this->sellingprice*/
	return *this;
}

ostream& Print(ostream &os, Salesdata &item){
	os << item.bookNo << " " << item.units_sold;
	return os;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		cerr << "请输入正确的文件名" << endl;
		return -1;
	}
	ifstream in(argv[1]);//?
	if (!in){
		cout << "无法打开输入文件" << endl;
		return -1;
	}

	//ostream os(cout);
	Salesdata total;
	if (Read(in, total)){
		Salesdata trans;
		while (Read(in, trans)){//IO流不能作为参数传递
			if (total.isbn() == trans.isbn()){
				total.Combine(trans);
			}
			else{
				Print(cout, total) << endl;
				total = trans;
			}
		}
		Print(cout, total) << endl;
	}
	else{
		cout << "没有数据" << endl;
		return -1;
	}
}
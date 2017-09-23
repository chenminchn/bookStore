// testProject.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��istream���ж������
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
		cerr << "��������ȷ���ļ���" << endl;
		return -1;
	}
	ifstream in(argv[1]);//?
	if (!in){
		cout << "�޷��������ļ�" << endl;
		return -1;
	}

	//ostream os(cout);
	Salesdata total;
	if (Read(in, total)){
		Salesdata trans;
		while (Read(in, trans)){//IO��������Ϊ��������
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
		cout << "û������" << endl;
		return -1;
	}
}
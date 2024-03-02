#include "pch.h"
#include "Goods.h"
#pragma warning(disable:4996)

bool sortName(Goods a, Goods b)
{
	return a.name < b.name;
}
bool sortName2(Goods a, Goods b)
{
	return a.name > b.name;
}
bool sortPrice(Goods a, Goods b)
{
	return a.price * (1 - a.discount) < b.price * (1 - b.discount);
}
bool sortPrice2(Goods a, Goods b)
{
	return a.price * (1 - a.discount) > b.price * (1 - b.discount);
}

void Goods::Edit(CString _name, CString _ID, double _price, double _discount, int _stock, CString _type)
{
	name = _name, ID = _ID, type = _type;
	price = _price, discount = _discount, stock = _stock;
}

void GoodsList::ReadFile()
{
	FILE* file = fopen(_GOODS_LIST_FILE, "r+");
	Goods temp;
	char tempName[100] = "\0", tempID[30] = "\0", tempType[100] = "\0";
	if (!file) {
		return;
	}
	while (!feof(file))
	{
		fscanf(file, "%s%s%s%lf%lf%d", tempName, tempID,tempType, &temp.price, &temp.discount, &temp.stock);
		temp.name = tempName;
		temp.ID = tempID;
		temp.type = tempType;
		content.push_back(temp);
		length++;
	}
	fclose(file);
}

void GoodsList::WriteFile(int receipt,CString username) 
{
	FILE* file;
	if (receipt)
		file = fopen(_RECEIPT_FILE, "w+");
	else
		file = fopen(_GOODS_LIST_FILE, "w+");
	string tempsName, tempsID, tempsType;
	Goods temp;
	
	if (!file)
		return ;
	if (receipt) 
		fprintf(file, "Name\tPrice\tQuantity\n\n");

	int tempLength = length;
	double total = 0;
	for (list<Goods>::iterator it = content.begin(); tempLength > 0; it++)
	{
		tempsName = CStringA(it->name), tempsID = CStringA(it->ID), tempsType = CStringA(it->type);
		if (receipt) {
			int length = tempsName.length(), lineNum = length / 6, remainLength = length % 6;
			int i = 0;
			for (; i < lineNum - (remainLength == 0); i++)
				fprintf(file, "%s\n", tempsName.substr(i * 6, 6).c_str());
			if (remainLength >= 4 || remainLength == 0)
				fprintf(file, "%s\t", tempsName.substr(i * 6).c_str());
			else
				fprintf(file, "%s\t\t", tempsName.substr(i * 6).c_str());
			fprintf(file, "%.2lf\t%d\n\n", it->price, it->stock);
			total += it->price * it->stock;
		}
		else {
			fprintf(file, "\n%s %s %s", tempsName.c_str(), tempsID.c_str(), tempsType.c_str());
			fprintf(file, "\n%lf %lf %d", it->price, it->discount, it->stock);
		}
		tempLength--;
	}
	if (receipt) {
		fprintf(file, "\nTotal: %.3lf", total);
		fprintf(file, "\n\nUser: %S", username);
	}
	fclose(file);
}

void GoodsList::Delete(list<Goods>::iterator item)
{
	content.erase(item);
	length--;
}

void GoodsList::Add(CString name, CString ID, double price, int stock, CString type)
{
	Goods newGoods;
	newGoods.Edit(name, ID, price, 0.0, stock, type);
	content.push_back(newGoods);
	length++;
}

void GoodsList::Sort(CString accrod)
{
	if (accrod == TEXT("��������"))
		content.sort(sortName);
	if (accrod == TEXT("���ƽ���"))
		content.sort(sortName2);
	if (accrod == TEXT("�۸�����"))
		content.sort(sortPrice);
	if (accrod == TEXT("�۸���"))
		content.sort(sortPrice2);
}

int GoodsList::GetLength()
{
	return length;
}

list<Goods>::iterator GoodsList::Find(CString _name)
{
	list<Goods>::iterator it = content.begin();
	int tempLength = length;
	while (1)
	{
		if (tempLength == 0)
			return content.end();
		if (it->name == _name)
			return it;
		it++, tempLength--;
	}
}

list<Goods>::iterator GoodsList::FindID(CString _ID)
{
	list<Goods>::iterator it = content.begin();
	int tempLength = length;
	while (1)
	{
		if (tempLength == 0)
			return content.end();
		if (it->ID == _ID)
			return it;
		it++, tempLength--;
	}
}

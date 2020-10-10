#include <iostream>
#include <string>
using namespace std;
/*
* 一个借阅记录bean ， 把通过图书Id 和用户Id把图书和用户联系起来
* 
* 并且借阅记录不能够自己手动增加，由系统自己产生，所以此方法中没有 get和set方法
*/
#pragma once
class BorrowRecord
{
public:
	BorrowRecord();
	~BorrowRecord();
public:
	int m_nBorrowId;					//借阅ID
	int m_nBookId;					//图书ID
	int m_nUserId;					//用户ID
	string m_tBorrowDate;				//借阅时间
	string m_tShouldReturnDate;		//应还时间
	string m_tReturnDate;				//实际归还时间
	int m_nContinue;					//续借次数
};



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <winsock.h>
#include <mysql.h> 
#include <iostream>
#include <vector>
#include "User.h"
#include "Book.h"
#include "TimeUtil.h"
#include "BorrowRecord.h"
#pragma once
class DBUtil
{
public:
	DBUtil();
	~DBUtil();
	bool OpenDB();
	bool CloseDB();
	User ReadUser(string strUserName, string strUserPWD);
	bool AddBook(Book book);
	bool SelectAllBook(vector<Book> &books);//把选择的数据保存到引用变量 books中供外界进行访问，
	bool SelectBookByName(string strBookName, vector<Book> &books);
	bool SelectBookById(int nBookId, Book &book);
	bool DeleteBookById(int nBookId);
	bool AddBorrowRecord(BorrowRecord borrowRecord);
	bool UpdateBook(Book book);//更新图书的剩余数量 lefted --   借书    （这个是刚开始写的)
	bool UpdateBookNum(Book book);//更新图书的数量  lefted  ++ -- 都可以  [推荐使用这个]
	bool ExtendBorrowRecord(int nRecordId);
	bool SelectBorrowRecordByRecordId(BorrowRecord &borrowRecord,int nRecordId);
	bool FinishBorrowRecord(int nRecordId, int nBookId);
	bool SelectAllBorrowRecord(vector<BorrowRecord> &borrowRecords);
	bool SelectBorrowRecordByUserId(vector<BorrowRecord> &borrowRecords, int nUserId, int nType);
	User SelectUserById(int nUserId);
	bool AddUser(User user);
	bool SelectAllUser(vector<User> &users);
	bool SelectHotBooks(vector<Book> &books);//显示热榜图书
public:
	string szUsername;			//用户名
	string szPswd;				//密码
	string szHost;				//主机名
	string szDatabase;			//数据库名
	int nPort;					//端口号  
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	MYSQL_FIELD *fd;
	bool isOpen;
	TimeUtil timeUtil;
};


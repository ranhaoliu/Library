#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
#include <time.h>
#include "User.h"
#include "Book.h"
#include "TimeUtil.h"
#include "DBUtil.h"
using namespace std;
/*继承自User
* 显示菜单
* 增加书
* 显示所有书
* 查询书
* 删除书
* 显示所有借阅记录
* 增加用户
* 显示所有用户
*/
#pragma once
class Manager:public User
{
public:
	Manager();
	~Manager();
	void ShowMenu();
	bool AddBook();
	bool DisplayAllBook();
	bool QueryBook(string strBookName);
	bool DeleteBook(int nBookId);
	bool DiaplayAllBorrowRecord();
	bool AddUser();
	bool DisplayAllUser();
	TimeUtil m_timeUtil;
	DBUtil m_dbUtil;
};


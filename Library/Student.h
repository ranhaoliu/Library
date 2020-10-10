#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
#include <time.h>
#include "User.h"
#include "Book.h"
#include "TimeUtil.h"
#include "DBUtil.h"
#include "User.h"
#include "BorrowRecord.h"
using namespace std;
/*      继承自User
显示菜单
* 查书
* 借书
* 还书
* 查看借阅的数
* 续借
*/
class Student:public User
{
public:
	Student();
	~Student();
	void ShowMenu();
	bool QueryBook(string strBookName);
	bool BorrowBook(int nBookId);
	bool ReturnBook();
	bool ShowMyBorrowRecord();
	bool RenewBook();
	bool HotListBook();//显示热榜图书
public:
	TimeUtil m_timeUtil;
	DBUtil m_dbUtil;
};


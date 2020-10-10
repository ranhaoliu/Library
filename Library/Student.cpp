#include "Student.h"

Student::Student()
{
}


Student::~Student()
{
}

void Student::ShowMenu()
{
	system("cls");
	cout << "==========================欢迎使用图书馆后台管理系统：==========================" << endl;
	cout << "                              1.查询图书" << endl;
	cout << "                              2.借阅图书" << endl;
	cout << "                              3.归还图书" << endl;
	cout << "                              4.借阅记录" << endl;
	cout << "                              5.续借图书" << endl;
	cout << "                              6.热榜图书" << endl;
	cout << "                              0.退出登录" << endl;
}
//显示热榜图书
bool Student::HotListBook() {
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

//	m_dbUtil.SelectAllBook(books); //把这一行变成查询热榜图书，热榜图书按照借阅的数量来参考
	m_dbUtil.SelectHotBooks(books);
	vector<Book>::iterator vecIter;
	cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookID() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetAuthor() << "  " << setw(14) << vecIter->GetPub() << "  " << setw(14) << vecIter->GetInDate() << "  " << setw(8) << vecIter->GetTotalNum() << "  " << setw(3) << vecIter->GetLeftNum() << endl;
	}
	cin.get();
	cin.get();
	return true;

}

//根据书名查询书籍
bool Student::QueryBook(string strBookName)
{
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectBookByName(strBookName, books);
	vector<Book>::iterator vecIter;
	if (books.size()>0) {
		cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	}else {
		cout << "图书馆里没有此书，请联系图书管理员.....(按Enter 键继续)" << endl;
	}
	
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookID() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetAuthor() << "  " << setw(14) << vecIter->GetPub() << "  " << setw(14) << vecIter->GetInDate() << "  " << setw(8) << vecIter->GetTotalNum() << "  " << setw(3) << vecIter->GetLeftNum() << endl;
	}
	cout << "请按Enter 键继续 ...." << endl;
	cin.get();
	cin.get();
	return true;
}

//根据图书ID借阅书籍
bool Student::BorrowBook(int nBookId)
{
	Book book;
	book.SetBookID(-1);
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	m_dbUtil.SelectBookById(nBookId, book);
	if (book.GetBookID() != -1)
	{
		cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
		cout << setiosflags(ios::left) << setw(4) << book.GetBookID() << "  " << setw(14) << book.GetBookName() << "  " << setw(10) << book.GetAuthor() << "  " << setw(14) << book.GetPub() << "  " << setw(14) << book.GetInDate() << "  " << setw(8) << book.GetTotalNum() << "  " << setw(3) << book.GetLeftNum() << endl;
		if (book.GetLeftNum() == 0)
		{
			cout << "该书籍已全部借出，暂时无法借阅!" << endl;
			cin.get();
			cin.get();
			return false;
		}
		//询问是否借阅
		char chIsBorrow = 'a';
		cout << "借阅这本书吗?n/y" << endl;
		cin.get();
		cin >> chIsBorrow;
		while (true)
		{
			if (chIsBorrow == 'y' || chIsBorrow == 'Y')
			{
				//借阅
				BorrowRecord borrowRecord;
				borrowRecord.m_nBookId = book.GetBookID();
				borrowRecord.m_nUserId = m_nID;
				time_t tTemp = time(NULL);
				char szTime[16] = {0};
				m_timeUtil.TimeToString(tTemp, szTime);
				borrowRecord.m_tBorrowDate = szTime;
				borrowRecord.m_tShouldReturnDate = m_timeUtil.AddMonth(tTemp);
				borrowRecord.m_tReturnDate = "";
				borrowRecord.m_nContinue = 0;
				m_dbUtil.AddBorrowRecord(borrowRecord);
				m_dbUtil.UpdateBook(book);//更新剩余库存
				break;
			}
			else if (chIsBorrow == 'n' || chIsBorrow == 'N')
			{
				cout << "已取消借阅！";
				break;
			}
			else
			{
				cout << "输入有误,请重新输入:";
				cin.get();
				cin >> chIsBorrow;
			}
		}
	}
	else
	{
		cout << "该图书馆里没有该 Id 为 " << nBookId << " 的图书....（按Enter 键继续）" << endl;
	}
	cout << "请按Enter 键继续 ...." << endl;
	cin.get();
	cin.get();
	return true;
}

//归还书籍
bool Student::ReturnBook()
{
	Book book;
	User user;
	book.SetBookID(-1);
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	//展示还未归还的图书记录
	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 1);
	if (borrowRecords.size() <=0) {
		cout << "您没有要归还的图书 ...(请按Enter 键继续)" << endl;
		cin.get();
		cin.get();
		return false;
	}
	cout << "已下是没有归还的图书" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cout << "请选择要归还图书的记录ID..... (想要退出归还请输入 -1)" << endl;

	//选择要还哪本书
	int nRecordId;
	cin >> nRecordId;
//	if (nRecordId == -1) {
				
	//}
	bool bIsFind = true;
	while (bIsFind)
	{
		for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
		{
			if (nRecordId == vecIter->m_nBorrowId)
			{
				bIsFind = false;
				break;
			}
		}
		if (vecIter == borrowRecords.end())
		{
			cout << "您所输入的ID不在记录中，请重新输入(退出还书请输入-1):";
			cin >> nRecordId;
			if (nRecordId == -1) {
				return false;
			}
		}
	}

	m_dbUtil.FinishBorrowRecord(vecIter->m_nBorrowId, vecIter->m_nBookId);
	//更新剩余图书 归还的书 +1
	int leftnum = book.GetLeftNum() + 1;//归还的书的数量加1
	book.SetLeftNum(leftnum);
	m_dbUtil.UpdateBookNum(book);
	cout << "还书成功!" << endl;
	cout << "请按Enter 键继续 ...." << endl;
	cin.get();
	cin.get();
	return true;
}

//展示个人借阅记录
bool Student::ShowMyBorrowRecord()
{
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 2);
	User user;
	Book book;
	cout << "以下是您的所有借阅记录:" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cout << "请按Enter 键继续 ...." << endl;
	cin.get();
	cin.get();
	return true;
}

//续借图书，没有还的书才能进行续借，这里续借指的是把归还日期往后推一个月

bool Student::RenewBook()
{
	Book book;
	User user;
	book.SetBookID(-1);
	vector<BorrowRecord> borrowRecords;//为啥它的大小总是等于 0
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	//展示还未归还的图书记录
	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 1);
	cout <<"借阅记录的大小： "<< borrowRecords.size() << endl;
	
	if (borrowRecords.size() <= 0) {
		cout << "您没有已经借阅的图书,不能进行续借，请前往借阅....(请按Enter键继续)" << endl;
		cin.get();
		cin.get();
		return false;
	}
	cout << "以下是没有归还的图书" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cout << "请选择续借图书的记录ID,(退出请输入 -1)" << endl;

	//选择要续借哪本书
	int nRecordId;
	cin >> nRecordId;
	if (nRecordId == -1) {
		return false;//
	}
	bool bIsNotFind = true;
	bool bCanContinue = false;
	while (bIsNotFind)
	{
		for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
		{
			if (nRecordId == vecIter->m_nBorrowId)
			{
				bIsNotFind = false;
				if (vecIter->m_nContinue > 0)
				{
					bCanContinue = false;
				}
				else
				{
					bCanContinue = true;
				}

				break;
			}
		}
		if (vecIter == borrowRecords.end())
		{
			cout << "您所输入的ID不在记录中，请重新输入:";
			cin >> nRecordId;
			if (nRecordId == -1) {
				return false;//
			}
		}
	}

	if (true == bCanContinue)
	{
		m_dbUtil.ExtendBorrowRecord(nRecordId);// 更新那个 续借标志位,并且要还书时间往后推迟一个月
		cout << "续借成功!" << endl;
	}
	else
	{
		cout << "此书籍已经续借过一次，无法再次续借" << endl;
	}
	cout << "请按Enter 键继续 ...." << endl;
	cin.get();
	cin.get();
	return true;

}
#include <iostream>
#include <string>
using namespace std;
/*
* һ�����ļ�¼bean �� ��ͨ��ͼ��Id ���û�Id��ͼ����û���ϵ����
* 
* ���ҽ��ļ�¼���ܹ��Լ��ֶ����ӣ���ϵͳ�Լ����������Դ˷�����û�� get��set����
*/
#pragma once
class BorrowRecord
{
public:
	BorrowRecord();
	~BorrowRecord();
public:
	int m_nBorrowId;					//����ID
	int m_nBookId;					//ͼ��ID
	int m_nUserId;					//�û�ID
	string m_tBorrowDate;				//����ʱ��
	string m_tShouldReturnDate;		//Ӧ��ʱ��
	string m_tReturnDate;				//ʵ�ʹ黹ʱ��
	int m_nContinue;					//�������
};


#ifndef __LOG_H__
#define __LOG_H__

#if _MSC_VER > 1000
#   pragma once
#endif

#include <string>
#include <iostream>
#include <fstream>

#include "MQ_Defines.h"
#include "MQ_Lockable.h"

using namespace std;

/*
 * ��־������   
*/
typedef	enum
{
	LOG_NONE,    // ����ӡ
	LOG_CRIT,    // �����쳣�Ĺؼ�������Щ�쳣���ܻᵼ�±�����ϵͳ���ȶ���Σ��
	LOG_ERROR,   // �߼����󣬵��¹���û����ȷʵ�ֵ�ҵ���߼�����
	LOG_WARNING, // �澯�����ܻᵼ���߼��������ʾ�����ǲ�Ӱ����������ִ��
	LOG_INFO,    // ��Ϣ��ҵ���߼��Ĺؼ�������Ϣ
	LOG_DEBUG,   // ������Ϣ�����ڷ����ų��������Ϣ

} LEVEL;

/*
   ͨ�õ�CLog��־��ӡ�ࣺ

   1.�������ƴ�ӡ��־�ļ���
   2.�������ý���־��ӡ���ļ�������̨��Visual Stdio���Դ���
   3.���Զ�����־�Ļ�����Ϣ�У������ڡ�ʱ�䡢���뼶��ʱ�䡢����ID���߳�ID��
   4.����������־�ļ���������������������������������һ���µ���־�ļ�
   
*/

class MQ_OS_EXPORT CLog
{

public:

	typedef enum
	{
	   NONE,
	   STDIO, // ��ӡ������̨
	   FILE,  // ��ӡ���ļ�
	   VSDEBUGWINDOW, // ��ӡ��Visual Stdio���Դ��� 
	   
	} TYPE;

	typedef enum{
	
		COL_DATE = 0x1,      // �Ƿ��ӡ����
		COL_TIME = 0x2,      // �Ƿ��ӡʱ��
		COL_MICROSEC = 0x4,  // �Ƿ��ӡ����
		COL_PROC = 0x8,      // �Ƿ��ӡ����ID
		COL_THREAD = 0x16,   // �Ƿ��ӡ�߳�ID
                             // �Ƿ��ӡ
	
	} ColumnSetting;

	const static char SettingOpenChar = '[';
    const static char SettingCloseChar = ']';
	const static int MAX_LINE_LENGTH = 8192;
	static const char _descriptions[][32];
	static const int _descriptions_length[];

public:
	CLog(void);
	virtual ~CLog(void);

	static CLog* getInstance();
    void release();

	static void initialize(TYPE t, LEVEL l, int maxline,const string& filepath,const string& appname);
	static void initialize(TYPE t, LEVEL l, int maxline,unsigned columnsetting,const string& filepath,const string& appname);

	void print_LOG_NONE(const char *format, ...);
	void print_LOG_CRIT(const char *format, ...);
	void print_LOG_ERROR(const char *format, ...);
	void print_LOG_WARNING(const char *format, ...);
	void print_LOG_INFO(const char *format, ...);
	void print_LOG_DEBUG(const char *format, ...);

	void promft_LOG_NONE(const char* pmft,const char *format, ...);
	void promft_LOG_CRIT(const char* pmft,const char *format, ...);
	void promft_LOG_ERROR(const char* pmft,const char *format, ...);
	void promft_LOG_WARNING(const char* pmft,const char *format, ...);
	void promft_LOG_INFO(const char* pmft,const char *format, ...);
	void promft_LOG_DEBUG(const char* pmft,const char *format, ...);

private:

    void newLogFile(const string& path,const string& appname);
	void closeLogFile();

	void printLog(LEVEL lvl,const char* promft,const char* format_str,va_list& marker);

	static CLog* mpInstance;
	static Mutex mMutexInst;

	static int mMaxLine;
	int mCurrentLines;

	static LEVEL mLimitLevel;
	static TYPE  mType;
	static string  mFilePath;
	static string  mFileName;
	static unsigned mFlag;

	int mFileCount;
	std::ostream* mpLogger;
	std::string mCurrentFileName;
	
   
	Mutex mMutexWriting;
};


#define MQ_LOG(level,x)  do{ CLog::getInstance()->print_##level x ;}while(0)

#define DebugLog(x)   MQ_LOG(LOG_DEBUG,x)
#define ErrLog(x)     MQ_LOG(LOG_ERROR,x)
#define InfoLog(x)    MQ_LOG(LOG_INFO,x)
#define CritLog(x)    MQ_LOG(LOG_CRIT,x)
#define WarningLog(x) MQ_LOG(LOG_WARNING,x)

#endif //



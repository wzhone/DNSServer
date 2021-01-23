#pragma once
#include "common.h"



//Queries
enum class QuerType8 :uint8_t
{
	A = 0x01,
	NS = 0x02,
	CNAME = 0x05,
	SOA = 0x06,
	PTR = 0x0c,
	MX = 0x0f,
	TXT = 0x10,
	AXFR = 0xfc,
	ANY = 0xff
};

enum class QuerType :uint32_t
{
	A		= 0x01000100,  //a host address
	NS		= 0x01000200,  //an authoritative name server
	CNAME	= 0x01000500,  //the canonical name for an alias
	SOA		= 0x01000600,  //marks the start of a zone of authority
	PTR		= 0x01000c00,  //domain name pointer
	MX		= 0x01000f00,  //mail exchange
	TXT		= 0x01001000,  //text strings
	AXFR	= 0x0100fc00,  //A request for a transfer of an entire zone
	ANY		= 0x0100ff00,  //A request for all records

	/* no use
	
	MF		= 0x01000400,  //a mail forwarder (Obsolete - use MX)
	MD	= 0x01000300,  //a mail destination (Obsolete - use MX)
	MB	= 0x01000700,  //a mailbox domain name (EXPERIMENTAL)
	MG	= 0x01000800,  //a mail group member (EXPERIMENTAL)
	MR	= 0x01000900,  //a mail rename domain name (EXPERIMENTAL)
	NULL	= 0x01000a00,  //null RR (EXPERIMENTAL)
	MAILB	= 0x0100fd00,  //A request for mailbox-related records (MB, MG or MR)
	MAILA	= 0x0100fe00,  //A request for mail agent RRs (Obsolete - see MX)

	*/

	/* not support
	
	WKS		= 0x01000b00,  //well known service description
	HINFO	= 0x01000d00,  //host information
	MINFO	= 0x01000e00,  //mailbox or mail list information

	*/
};


//see page 13 of RFC1035 for details
//enum QuerClass :uint16_t { 
//	QC_IN = 1,
//	QC_CS = 2,
//	QC_CH = 3,
//	QC_HS = 4
//};

std::string domain2queryname(std::string);
std::string queryname2domain(std::string);



struct Q_options {
	uint16_t Type;
	uint16_t Class;
};


enum Headflag :uint16_t {
	Q = 0x8000,
	R = 0x0000,

	RD = 0x100,
	RA = 0x80,

};

//DNS Header
const int DnsHeaderSize = 12;

struct DNSHeader {
	uint16_t id = 0;			//�Ự��ʶ ��ʶӦ���ĵ���Ӧ����,���������ĺ����Ӧ��Ӧ���ģ����ֶε�ֵ����ͬ��
	uint16_t flags = 0;			//��־
	uint16_t n_questions = 0;	//������
	uint16_t n_answer = 0;		//�ش� ��Դ��¼��
	uint16_t n_auth = 0;		//��Ȩ ��Դ��¼��
	uint16_t n_addit = 0;		//���� ��Դ��¼��
};

//FLAG QR
#define SETFLAGQUERY(flags)  ((flags) &= 0x7FFFU)
#define SETFLAGANSWER(flags)  ((flags) |= 0x8000U)
#define GETFLAGANSWER(flags)  ((flags) >> 15)


//FLAG opcode 
#define SETFLAGOPSTANDARD(flags)  ((flags) &= 0x87FFU)	//��׼��ѯ
#define SETFLAGOPREVERSE(flags)  SETFLAGOPSTANDARD((flags));((flags) |= 0x0800U) //�����ѯ
#define SETFLAGOPSTATUS(flags)  SETFLAGOPSTANDARD((flags));((flags) |= 0x1000U)	//������״̬����
#define GETFLAGOP(flags) (((flags)&0x7800U)>>11)	 //��ȡOPCODE

//FLAG AA  ��Ȩ�ش�(Authoritative Answer)
#define SETFLAGAA(flags)  ((flags) |= 0x0400U)
#define UNSETFLAGAA(flags)  ((flags) &= 0xFBFFU)
#define GETFLAGAA(flags)  (((flags) &= 0x0400U) >> 10)

//FLAG TC  �ɽضϵ�(Truncated)
#define SETFLAGTC(flags)  ((flags) |= 0x0200U)
#define UNSETFLAGTC(flags)  ((flags) &= 0xFDFFU)
#define GETFLAGTC(flags)  (((flags) &= 0x0200U) >> 9)

//FLAG RD  �����ݹ�(Recursion Desired)
#define SETFLAGRD(flags)  ((flags) |= 0x0100U)
#define UNSETFLAGRD(flags)  ((flags) &= 0xFEFFU)
#define GETFLAGRD(flags)  (((flags) &= 0x0100U) >> 8)

//FLAG RCODE Response Code
#define SETFLAGRCODEOK(flags)  ((flags) &= 0xFFF0U)
#define SETFLAGRCODEWRONG(flags)  ((flags)=((((flags)>>4)<<4) | 0xFFF3U))
#define GETFLAGRCOD(flags)  ((flags) &= 0x000FU)

//DNSHeader to BigEnding

//Header2BigEndian
#define Header2BigEndian(header)\
(header).id = htons((header).id);\
(header).flags = htons((header).flags);\
(header).n_questions = htons((header).n_questions);\
(header).n_answer = htons((header).n_answer);\
(header).n_auth = htons((header).n_auth);\
(header).n_addit = htons((header).n_addit);\

#define Header2LittleEndian(header)\
(header).id = ntohs((header).id);\
(header).flags = ntohs((header).flags);\
(header).n_questions = ntohs((header).n_questions);\
(header).n_answer = ntohs((header).n_answer);\
(header).n_auth = ntohs((header).n_auth);\
(header).n_addit = ntohs((header).n_addit);\



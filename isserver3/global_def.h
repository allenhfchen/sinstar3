#pragma once

#define CISIZE_BASE		164		//����������Ϣ������

#define MAX_SENTLEN		50		//�����󳤶�
#define MAX_WORDLEN		30		//������󳤶�
#define MAX_COMPLEN		20		//ϵͳ֧�ֵ�����볤

#define RATE_USERDEF	0xFF	//�Զ������ʹ�õĴ�Ƶ
#define RATE_FORECAST	0xFE	//����Ԥ��õ��Ĵ�ʹ�õĴ�Ƶ
#define RATE_GBK		0xFD	//GBK flag
#define RATE_USERCMD	0xFC	//Command ID
#define RATE_MIXSP		0xFB	//��ƴ����
#define RATE_WILD		0xFA	//���ܼ���ѯ���
#define RATE_ASSOCIATE	0xF9	//��������

enum{
	SENDER_SINSTSR3	= 100,
	SENDER_SKINMANAGER,
};


enum{
	EVENT_BASE = EVT_EXTERNAL_BEGIN,
	EVENT_DRAGMOVE,
	EVENT_SETSKIN,
	EVENT_SVRNOTIFY,
};

namespace SOUI
{
	class EventSvrNotify : public TplEventArgs<EventSvrNotify>
	{
		SOUI_CLASS_NAME(EventSvrNotify,L"on_svr_notify")
	public:
		EventSvrNotify(SObject *pSender):TplEventArgs<EventSvrNotify>(pSender){}
		enum{EventID=EVENT_SVRNOTIFY};
		WPARAM wp;
		LPARAM lp;
	};

	class EventSetSkin : public TplEventArgs<EventSetSkin>
	{
		SOUI_CLASS_NAME(EventSetSkin,L"on_set_skin")
	public:
		EventSetSkin(SObject *pSender):TplEventArgs<EventSetSkin>(pSender){}
		enum{EventID=EVENT_SETSKIN};
	};

}

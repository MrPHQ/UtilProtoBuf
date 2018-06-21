#ifndef __UTIL_PROTOBUF_PROTO__
#define __UTIL_PROTOBUF_PROTO__

#include <UtilProtoBuf\include\UtilProtoBuf.h>

namespace UTIL_PROTOBUF
{

	/**
	@brief ��Ϣ����.
	*/

	class UTIL_PROTOBUF_CPPAPI CProtoMessage
	{
	public:
		CProtoMessage();
		/**
		@brief ���캯��.
		\param pMsgName
			��Ϣ��������.
		*/
		CProtoMessage(const char* pMsgName);
		~CProtoMessage();

	public:
		/**
		@brief ����Ϣ.
		\param pMsgName
			��Ϣ��������.
		*/
		int OpenMsg(const char* pMsgName);

		/**
		@brief.
		*/
		void Close();

		/**
		@brief.
		*/
		bool IsOpen() const;

		/**
		@brief. ����
		*/
		int Clear() const;

		/**
		@brief. �ӻ�����������Ϣ����
			������.
		\param pDataBuff
			���ݻ�����
		\param iDataLen
			���ݳ���
		*/
		int Parse(const void* pDataBuff, int iDataLen);

		/**
		@brief. ���л���Ϣ������洢�ڸ������ֽ�������
		\param pDataBuff
			������
		\param iDataLen
			��������С
		\param pBuffLen
			�����ڲ����ݴ�С.
		\return
			�������л���ĳ���
		*/
		int SerializeToArray(void* pDataBuff, int iDataLen, int* pBuffLen);

		/**
		@brief. ��ȡ����
		\param pName
			��Ϣ�ֶ�����
		*/
		int32 GetInt32(const char* pName) const;
		int64 GetInt64(const char* pName) const;
		uint32 GetUInt32(const char* pName) const;
		uint64 GetUInt64(const char* pName) const;
		float GetFloat(const char* pName) const;
		double GetDouble(const char* pName) const;
		bool GetBool(const char* pName) const;
		string GetString(const char* pName) const;
		int GetStringEx(const char* pName, char* buff, int len) const;

		/**
		@brief. д����
		\param pName
			��Ϣ�ֶ�����
		*/
		int SetInt32(const char* pName, int32 value) const;
		int SetInt64(const char* pName, int64 value) const;
		int SetUInt32(const char* pName, uint32 value) const;
		int SetUInt64(const char* pName, uint64 value) const;
		int SetFloat(const char* pName, float value) const;
		int SetDouble(const char* pName, double value) const;
		int SetBool(const char* pName, bool value) const;
		int SetString(const char* pName, const string& value) const;
		int SetStringEx(const char* pName, const void* value, int len) const;
	private:
		std::pair<const Reflection*, const FieldDescriptor*> GetRef(const char* pName) const;
	private:
		/**< .*/
		Descriptor* m_pDescriptor;
		/**< .*/
		Message* m_pMessage;
	};

}
#endif
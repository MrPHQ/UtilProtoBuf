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
		/**
		@brief ���캯��.
		\param bNested
			Ƕ����Ϣ.
		*/
		CProtoMessage(bool bNested);
		~CProtoMessage();

	public:
		/**
		@brief ����Ϣ.
		\param pMsgName
			��Ϣ��������.
		*/
		int OpenMsg(const char* pMsgName);

		/**
		@brief ��ȡǶ����Ϣ.
		\param pFieldName
			��Ϣ��������.
		\return CProtoMessage*
			����ָ��,�ⲿ�ͷ�.
		*/
		CProtoMessage* GetNestedMsg(const char* pFieldName);
		int GetNestedMsgEx(const char* pFieldName, CProtoMessage&);

		/**
		@brief �����ظ��ֶ�(����)����.
			���������ֶ�(����)������.������سɹ�,��ֱ�ӶԶ������ø�ֵ.
			ע��: �ⲿ�ظ�ʹ��ͬһ������,��ʹ��ǰ��Ҫ���� Close, �ͷ���һ����Դ.
		\param pFieldName
			��Ϣ��������.
		\return CProtoMessage&
			���������ֶ�(����)������
		*/
		int AddRepeatedMsg(const char* pFieldName, CProtoMessage&);

		/**
		@brief ��ȡ�ظ��ֶ�(����)����.
			���������ֶ�(����)������.������سɹ�,��ֱ�Ӷ�ȡ�������õ�ֵ.
		\param pFieldName
			��Ϣ��������.
		\param iIndex
			�����±�.
		\return CProtoMessage&
			���������ֶ�(����)������
		*/
		int GetRepeatedMsg(const char* pFieldName, int iIndex, CProtoMessage&);

		/**
		@brief ��ȡ�ظ��ֶ�(����)��С.
		\param pFieldName
			��Ϣ��������.
		*/
		int GetRepeatedSize(const char* pFieldName);

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
		\param pFieldName
			��Ϣ�ֶ�����
		*/
		int32 GetInt32(const char* pFieldName) const;
		int64 GetInt64(const char* pFieldName) const;
		uint32 GetUInt32(const char* pFieldName) const;
		uint64 GetUInt64(const char* pFieldName) const;
		float GetFloat(const char* pFieldName) const;
		double GetDouble(const char* pFieldName) const;
		bool GetBool(const char* pFieldName) const;
		string GetString(const char* pFieldName) const;
		int GetStringEx(const char* pFieldName, char* buff, int len) const;
		int GetEnum(const char* pFieldName) const;

		int32 GetRepeatedInt32(const char* pFieldName, int index) const;
		int64 GetRepeatedInt64(const char* pFieldName, int index) const;
		uint32 GetRepeatedUInt32(const char* pFieldName, int index) const;
		uint64 GetRepeatedUInt64(const char* pFieldName, int index) const;
		float GetRepeatedFloat(const char* pFieldName, int index) const;
		double GetRepeatedDouble(const char* pFieldName, int index) const;
		bool GetRepeatedBool(const char* pFieldName, int index) const;
		string GetRepeatedString(const char* pFieldName, int index) const;
		int GetRepeatedStringEx(const char* pFieldName, int index, char* buff, int len) const;
		int GetRepeatedEnum(const char* pFieldName, int index) const;

		/**
		@brief. д����
		\param pName
			��Ϣ�ֶ�����
		*/
		int SetInt32(const char* pFieldName, int32 value) const;
		int SetInt64(const char* pFieldName, int64 value) const;
		int SetUInt32(const char* pFieldName, uint32 value) const;
		int SetUInt64(const char* pFieldName, uint64 value) const;
		int SetFloat(const char* pFieldName, float value) const;
		int SetDouble(const char* pFieldName, double value) const;
		int SetBool(const char* pFieldName, bool value) const;
		int SetString(const char* pFieldName, const string& value) const;
		int SetStringEx(const char* pFieldName, const void* value, int len) const;
		int SetEnum(const char* pFieldName, int32 value) const;

		int SetRepeatedInt32(const char* pFieldName, int index, int32 value) const;
		int SetRepeatedInt64(const char* pFieldName, int index, int64 value) const;
		int SetRepeatedUInt32(const char* pFieldName, int index, uint32 value) const;
		int SetRepeatedUInt64(const char* pFieldName, int index, uint64 value) const;
		int SetRepeatedFloat(const char* pFieldName, int index, float value) const;
		int SetRepeatedDouble(const char* pFieldName, int index, double value) const;
		int SetRepeatedBool(const char* pFieldName, int index, bool value) const;
		int SetRepeatedString(const char* pFieldName, int index, const string& value) const;
		int SetRepeatedStringEx(const char* pFieldName, int index, const void* value, int len) const;
		int SetRepeatedEnum(const char* pFieldName, int index, int32 value) const;
	private:
		std::pair<const Reflection*, const FieldDescriptor*> GetRef(const char* pFieldName) const;
		bool MatchFieldType(FieldDescriptor::Type nFieldType, const FieldDescriptor*) const;
	private:
		/**< .*/
		Descriptor* m_pDescriptor;
		/**< .*/
		Message* m_pMessage;
		/**< Ƕ����Ϣ���� .*/
		BOOL m_bNested;
	};
}
#endif
#ifndef __UTIL_PROTOBUF_PROTO__
#define __UTIL_PROTOBUF_PROTO__

#include <UtilProtoBuf\include\UtilProtoBuf.h>

namespace UTIL_PROTOBUF
{

	/**
	@brief 消息类型.
	*/

	class UTIL_PROTOBUF_CPPAPI CProtoMessage
	{
	public:
		CProtoMessage();
		/**
		@brief 构造函数.
		\param pMsgName
			消息类型名称.
		*/
		CProtoMessage(const char* pMsgName);
		/**
		@brief 构造函数.
		\param bNested
			嵌套消息.
		*/
		CProtoMessage(bool bNested);
		~CProtoMessage();

	public:
		/**
		@brief 打开消息.
		\param pMsgName
			消息类型名称.
		*/
		int OpenMsg(const char* pMsgName);

		/**
		@brief 获取嵌套消息.
		\param pFieldName
			消息类型名称.
		*/
		CProtoMessage* GetNestedMsg(const char* pFieldName);

		/**
		@brief.
		*/
		void Close();

		/**
		@brief.
		*/
		bool IsOpen() const;

		/**
		@brief. 清理
		*/
		int Clear() const;

		/**
		@brief. 从缓存区解析消息内容
			反序列.
		\param pDataBuff
			数据缓存区
		\param iDataLen
			数据长度
		*/
		int Parse(const void* pDataBuff, int iDataLen);

		/**
		@brief. 序列化消息并将其存储在给定的字节数组中
		\param pDataBuff
			缓存区
		\param iDataLen
			缓存区大小
		\param pBuffLen
			返回内部数据大小.
		\return
			返回序列化后的长度
		*/
		int SerializeToArray(void* pDataBuff, int iDataLen, int* pBuffLen);

		/**
		@brief. 读取数据
		\param pFieldName
			消息字段名称
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

		/**
		@brief. 写数据
		\param pName
			消息字段名称
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
	private:
		std::pair<const Reflection*, const FieldDescriptor*> GetRef(const char* pFieldName) const;
		bool MatchFieldType(FieldDescriptor::Type nFieldType, const FieldDescriptor*) const;
	private:
		/**< .*/
		Descriptor* m_pDescriptor;
		/**< .*/
		Message* m_pMessage;
		/**< 嵌套消息类型 .*/
		BOOL m_bNested;
	};
}
#endif
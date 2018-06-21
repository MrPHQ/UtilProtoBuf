#include "../UtilProtoBuf/stdafx.h"
#include "../include/ProtoBuf.h"
#include "../include/ProtoFileMgr.h"

namespace UTIL_PROTOBUF
{
	CProtoMessage::CProtoMessage()
		:m_pDescriptor(nullptr),
		m_pMessage(nullptr)
	{
	}

	CProtoMessage::CProtoMessage(const char* pMsgName)
		: m_pDescriptor(nullptr),
		m_pMessage(nullptr)
	{
		OpenMsg(pMsgName);
	}

	CProtoMessage::~CProtoMessage()
	{
		Close();
	}

	int CProtoMessage::OpenMsg(const char* pMsgName)
	{
		if (nullptr == pMsgName || strlen(pMsgName) <= 0){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		Close();
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		const DescriptorPool* pool = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDescriptorPool();
		if (nullptr == pool || nullptr == pMsgFactory){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		m_pDescriptor = (Descriptor*)pool->FindMessageTypeByName(pMsgName);
		if (nullptr == m_pDescriptor){
			return UTIL_PROTOBUF_ERROR_NOT_FIND_MSG;
		}
		const Message *pMessage = pMsgFactory->GetPrototype(m_pDescriptor);
		if (nullptr == pMessage){
			return UTIL_PROTOBUF_ERROR_NOT_FIND_MSG;
		}
		m_pMessage = pMessage->New();
		if (nullptr == m_pMessage){
			return UTIL_PROTOBUF_ERROR_MEMORY;
		}
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	void CProtoMessage::Close()
	{
		if (nullptr != m_pMessage){
			m_pMessage->Clear();
			delete m_pMessage;
			m_pMessage = nullptr;
		}
		m_pDescriptor = nullptr;
	}

	bool CProtoMessage::IsOpen() const
	{
		return m_pMessage != nullptr && m_pDescriptor != nullptr;
	}

	int CProtoMessage::Clear() const
	{
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		m_pMessage->Clear();
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::Parse(const void* pDataBuff, int iDataLen)
	{
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		bool bRet = m_pMessage->ParseFromArray(pDataBuff, iDataLen);
		return bRet ? UTIL_PROTOBUF_ERROR_SUCCESS : UTIL_PROTOBUF_ERROR_FAIL;
	}

	int CProtoMessage::SerializeToArray(void* pDataBuff, int iDataLen, int* pBuffLen)
	{
		if (!IsOpen()){
			return 0;
		}
		BYTE buff[1024];
		int length = m_pMessage->ByteSize();
		if (nullptr != pBuffLen){
			*pBuffLen = length;
		}
		if (length > iDataLen){
			return 0;
		}
		bool ret = m_pMessage->SerializeToArray(pDataBuff, iDataLen);
		return ret ? length : 0;
	}

	int32 CProtoMessage::GetInt32(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		return ref.first->GetInt32(*m_pMessage, ref.second);
	}

	int64 CProtoMessage::GetInt64(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		return ref.first->GetInt64(*m_pMessage, ref.second);
	}
	uint32 CProtoMessage::GetUInt32(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		return ref.first->GetUInt32(*m_pMessage, ref.second);
	}
	uint64 CProtoMessage::GetUInt64(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		return ref.first->GetUInt64(*m_pMessage, ref.second);
	}
	float CProtoMessage::GetFloat(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0.0;
		}
		return ref.first->GetFloat(*m_pMessage, ref.second);
	}
	double CProtoMessage::GetDouble(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0.0;
		}
		return ref.first->GetDouble(*m_pMessage, ref.second);
	}
	bool CProtoMessage::GetBool(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return false;
		}
		return ref.first->GetBool(*m_pMessage, ref.second);
	}
	string CProtoMessage::GetString(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return "";
		}
		return ref.first->GetString(*m_pMessage, ref.second);
	}

	int CProtoMessage::GetStringEx(const char* pName, char* buff, int len) const
	{
		if (buff == nullptr){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		std::string str = GetString(pName);
		memcpy(buff, str.data(), min(len, str.length()));
		return min(len, str.length());
	}

	int CProtoMessage::SetInt32(const char* pName, int32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetInt32(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetInt64(const char* pName, int64 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetInt64(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetUInt32(const char* pName, uint32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetUInt32(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetUInt64(const char* pName, uint64 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetUInt64(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetFloat(const char* pName, float value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetFloat(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetDouble(const char* pName, double value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetDouble(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetBool(const char* pName, bool value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetBool(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetString(const char* pName, const string& value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		ref.first->SetString(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetStringEx(const char* pName, const void* value, int len) const
	{
		if (nullptr == value){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		std::string str((const char*)value, len);
		return SetString(pName, str);
	}

	std::pair<const Reflection*, const FieldDescriptor*> CProtoMessage::GetRef(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ret;
		ret.first = nullptr;
		ret.second = nullptr;

		if (!IsOpen()){
			return ret;
		}
		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pName);
		ret.first = reflection;
		ret.second = field;
		return ret;
	}
}
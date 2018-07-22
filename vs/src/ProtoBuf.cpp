#include "../UtilProtoBuf/stdafx.h"
#include "../include/ProtoBuf.h"
#include "../include/ProtoFileMgr.h"

namespace UTIL_PROTOBUF
{
	CProtoMessage::CProtoMessage()
		:m_pDescriptor(nullptr),
		m_pMessage(nullptr),
		m_bNested(FALSE)
	{
	}

	CProtoMessage::CProtoMessage(const char* pMsgName)
		: m_pDescriptor(nullptr),
		m_pMessage(nullptr),
		m_bNested(FALSE)
	{
		OpenMsg(pMsgName);
	}

	CProtoMessage::CProtoMessage(bool bNested)
		: m_pDescriptor(nullptr),
		m_pMessage(nullptr),
		m_bNested(bNested ? TRUE:FALSE)
	{

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

	CProtoMessage* CProtoMessage::GetNestedMsg(const char* pFieldName)
	{
		if (nullptr == pFieldName){
			return nullptr;
		}
		if (!IsOpen()){
			return nullptr;
		}
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		if (nullptr == pMsgFactory){
			return nullptr;
		}

		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pFieldName);
		if (nullptr == field){
			return nullptr;
		}
		Message* pMsg = reflection->MutableMessage(m_pMessage, field, pMsgFactory);
		if (nullptr == pMsg){
			return nullptr;
		}
		CProtoMessage* pObj = new CProtoMessage(TRUE);
		if (nullptr == pObj){
			return nullptr;
		}
		pObj->m_pDescriptor = (Descriptor*)field->message_type();
		pObj->m_pMessage = pMsg;
		return pObj;
	}

	int CProtoMessage::GetNestedMsgEx(const char* pFieldName, CProtoMessage& msg)
	{
		if (nullptr == pFieldName){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		if (nullptr == pMsgFactory){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}

		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pFieldName);
		if (nullptr == field){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		Message* pMsg = reflection->MutableMessage(m_pMessage, field, pMsgFactory);
		if (nullptr == pMsg){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		msg.m_pDescriptor = (Descriptor*)field->message_type();
		msg.m_pMessage = pMsg;
		msg.m_bNested = TRUE;
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::AddRepeatedMsg(const char* pFieldName, CProtoMessage& msg)
	{
		if (nullptr == pFieldName){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		if (nullptr == pMsgFactory){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}

		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pFieldName);
		if (nullptr == field){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (field->label() != FieldDescriptor::LABEL_REPEATED)
		{
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		if (FieldDescriptor::TYPE_MESSAGE != field->type()){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		const MutableRepeatedFieldRef<Message> mrf_message = reflection->GetMutableRepeatedFieldRef<Message>(m_pMessage, field);
		Message* pMsg = mrf_message.NewMessage();
		if (nullptr == pMsg){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		int Index = mrf_message.size();
		mrf_message.Add(*pMsg);
		delete pMsg;
		if (Index == mrf_message.size())
		{
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		const Message& refm = mrf_message.Get(Index, nullptr/*scratch_space.get()*/);
		msg.m_pDescriptor = (Descriptor*)field->message_type();
		msg.m_pMessage = (Message*)&refm;
		msg.m_bNested = TRUE;
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::GetRepeatedMsg(const char* pFieldName, int iIndex, CProtoMessage& msg)
	{
		if (nullptr == pFieldName){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		if (nullptr == pMsgFactory){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}

		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pFieldName);
		if (nullptr == field){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (field->label() != FieldDescriptor::LABEL_REPEATED)
		{
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		if (FieldDescriptor::TYPE_MESSAGE != field->type()){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		const MutableRepeatedFieldRef<Message> mrf_message = reflection->GetMutableRepeatedFieldRef<Message>(m_pMessage, field);
		int iSize = mrf_message.size();
		if (iIndex >= iSize)
		{
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		const Message& m = mrf_message.Get(iIndex, nullptr/*scratch_space.get()*/);
		msg.m_pDescriptor = (Descriptor*)field->message_type();
		msg.m_pMessage = (Message*)&m;
		msg.m_bNested = TRUE;
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::GetRepeatedSize(const char* pFieldName)
	{
		if (nullptr == pFieldName){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (!IsOpen()){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		DynamicMessageFactory* pMsgFactory = UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->GetDynamicMessageFactory();
		if (nullptr == pMsgFactory){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}

		const Reflection *reflection = m_pMessage->GetReflection();
		const FieldDescriptor *field = NULL;
		field = m_pDescriptor->FindFieldByName(pFieldName);
		if (nullptr == field){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (field->label() != FieldDescriptor::LABEL_REPEATED)
		{
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		int iSize = 0;
		if (FieldDescriptor::TYPE_MESSAGE == field->type()){
			const MutableRepeatedFieldRef<Message> mrf_message = reflection->GetMutableRepeatedFieldRef<Message>(m_pMessage, field);
			iSize = mrf_message.size();
		}
		else{
			iSize = reflection->FieldSize(*m_pMessage, field);
		}
		return iSize;
	}

	void CProtoMessage::Close()
	{
		if (!m_bNested){
			if (nullptr != m_pMessage){
				m_pMessage->Clear();
				delete m_pMessage;
				m_pMessage = nullptr;
			}
		}
		m_pMessage = nullptr;
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
		size_t length = m_pMessage->ByteSizeLong();
		if (nullptr != pBuffLen){
			*pBuffLen = length;
		}
		if (length > iDataLen){
			return 0;
		}
		bool ret = m_pMessage->SerializeToArray(pDataBuff, iDataLen);
		return ret ? (int)length : 0;
	}

	int32 CProtoMessage::GetInt32(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT32, ref.second) && 
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED32, ref.second) && 
			!MatchFieldType(FieldDescriptor::TYPE_SINT32, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_INT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT64, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_FIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_UINT32, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_UINT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_FIXED64, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_FLOAT, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_DOUBLE, ref.second)){
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
		if (!MatchFieldType(FieldDescriptor::TYPE_BOOL, ref.second)){
			return 0.0;
		}
		return ref.first->GetBool(*m_pMessage, ref.second);
	}
	string CProtoMessage::GetString(const char* pName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return "";
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_STRING, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_BYTES, ref.second)){
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

	int CProtoMessage::GetEnum(const char* pFieldName) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_ENUM, ref.second)){
			return 0;
		}
		return ref.first->GetEnumValue(*m_pMessage, ref.second);
	}

	google::protobuf::int32 CProtoMessage::GetRepeatedInt32(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT32, ref.second)){
			return 0;
		}
		return ref.first->GetRepeatedInt32(*m_pMessage, ref.second, index);
	}

	google::protobuf::int64 CProtoMessage::GetRepeatedInt64(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT64, ref.second)){
			return 0;
		}
		return ref.first->GetRepeatedInt64(*m_pMessage, ref.second, index);
	}

	google::protobuf::uint32 CProtoMessage::GetRepeatedUInt32(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_FIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_UINT32, ref.second)){
			return 0;
		}
		return ref.first->GetRepeatedUInt32(*m_pMessage, ref.second, index);
	}

	google::protobuf::uint64 CProtoMessage::GetRepeatedUInt64(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_UINT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_FIXED64, ref.second)){
			return 0;
		}
		return ref.first->GetRepeatedUInt64(*m_pMessage, ref.second, index);
	}

	float CProtoMessage::GetRepeatedFloat(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0.0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_FLOAT, ref.second)){
			return 0.0;
		}
		return ref.first->GetRepeatedFloat(*m_pMessage, ref.second, index);
	}

	double CProtoMessage::GetRepeatedDouble(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0.0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_DOUBLE, ref.second)){
			return 0.0;
		}
		return ref.first->GetRepeatedDouble(*m_pMessage, ref.second, index);
	}

	bool CProtoMessage::GetRepeatedBool(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return false;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_BOOL, ref.second)){
			return 0.0;
		}
		return ref.first->GetRepeatedBool(*m_pMessage, ref.second, index);
	}

	google::protobuf::string CProtoMessage::GetRepeatedString(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return "";
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_STRING, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_BYTES, ref.second)){
			return "";
		}
		return ref.first->GetRepeatedString(*m_pMessage, ref.second, index);
	}

	int CProtoMessage::GetRepeatedStringEx(const char* pFieldName, int index, char* buff, int len) const
	{
		if (buff == nullptr){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		std::string str = GetRepeatedString(pFieldName, index);
		memcpy(buff, str.data(), min(len, str.length()));
		return min(len, str.length());
	}

	int CProtoMessage::GetRepeatedEnum(const char* pFieldName, int index) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return 0;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_ENUM, ref.second)){
			return 0;
		}
		return ref.first->GetRepeatedEnumValue(*m_pMessage, ref.second, index);
	}

	int CProtoMessage::SetInt32(const char* pName, int32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT32, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_INT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT64, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_FIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_UINT32, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_UINT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_FIXED64, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_FLOAT, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_DOUBLE, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_BOOL, ref.second)){
			return 0;
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
		if (!MatchFieldType(FieldDescriptor::TYPE_STRING, ref.second) && 
			!MatchFieldType(FieldDescriptor::TYPE_BYTES, ref.second)){
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
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

	int CProtoMessage::SetEnum(const char* pName, int32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_ENUM, ref.second)){
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		ref.first->SetEnumValue(m_pMessage, ref.second, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedInt32(const char* pFieldName, int index, int32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT32, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedInt32(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedInt64(const char* pFieldName, int index, int64 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_INT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SFIXED64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_SINT64, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedInt64(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedUInt32(const char* pFieldName, int index, uint32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_FIXED32, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_UINT32, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedUInt32(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedUInt64(const char* pFieldName, int index, uint64 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_UINT64, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_FIXED64, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedUInt64(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedFloat(const char* pFieldName, int index, float value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_FLOAT, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedFloat(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedDouble(const char* pFieldName, int index, double value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_DOUBLE, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedDouble(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedBool(const char* pFieldName, int index, bool value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_BOOL, ref.second)){
			return 0;
		}
		ref.first->SetRepeatedBool(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedString(const char* pFieldName, int index, const string& value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_STRING, ref.second) &&
			!MatchFieldType(FieldDescriptor::TYPE_BYTES, ref.second)){
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		ref.first->SetRepeatedString(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
	}

	int CProtoMessage::SetRepeatedStringEx(const char* pFieldName, int index, const void* value, int len) const
	{
		if (nullptr == value){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		std::string str((const char*)value, len);
		return SetRepeatedString(pFieldName, index, str);
	}

	int CProtoMessage::SetRepeatedEnum(const char* pFieldName, int index, int32 value) const
	{
		std::pair<const Reflection*, const FieldDescriptor*> ref = GetRef(pFieldName);
		if (nullptr == ref.first || nullptr == ref.second){
			return UTIL_PROTOBUF_ERROR_FAIL;
		}
		if (!MatchFieldType(FieldDescriptor::TYPE_ENUM, ref.second)){
			return UTIL_PROTOBUF_ERROR_FIELD_TYPE;
		}
		ref.first->SetRepeatedEnumValue(m_pMessage, ref.second, index, value);
		return UTIL_PROTOBUF_ERROR_SUCCESS;
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

	bool CProtoMessage::MatchFieldType(FieldDescriptor::Type nFieldType, const FieldDescriptor* field) const
	{
		if (nullptr == field){
			return false;
		}
		if (nFieldType != field->type()){
			return false;
		}
		return true;
	}
}
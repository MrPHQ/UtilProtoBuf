#ifndef __UTIL_PROTOBUF__
#define __UTIL_PROTOBUF__

#ifdef UTIL_PROTOBUF_EXPORTS
#define UTIL_PROTOBUF_CAPI extern "C" __declspec(dllexport)
#else
#define UTIL_PROTOBUF_CAPI extern "C" __declspec(dllimport)	
#endif

#ifdef UTIL_PROTOBUF_EXPORTS
#define UTIL_PROTOBUF_CPPAPI __declspec(dllexport)
#else
#define UTIL_PROTOBUF_CPPAPI __declspec(dllimport)	
#endif

#include <utils\utils.h>
#include <utils\Singleton.h>
using namespace UTILS::API;

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

#include <UtilProtoBuf\include\UtilProtoBufDef.h>
using namespace UTIL_PROTOBUF;
#endif
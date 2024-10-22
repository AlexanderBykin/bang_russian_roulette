// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseAuth.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MessageResponseAuth.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_MessageResponseAuth_2eproto() {
  delete MessageResponseAuth::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_MessageResponseAuth_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_MessageResponseAuth_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  MessageResponseAuth::default_instance_ = new MessageResponseAuth();
  MessageResponseAuth::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MessageResponseAuth_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_MessageResponseAuth_2eproto_once_);
void protobuf_AddDesc_MessageResponseAuth_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_MessageResponseAuth_2eproto_once_,
                 &protobuf_AddDesc_MessageResponseAuth_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MessageResponseAuth_2eproto {
  StaticDescriptorInitializer_MessageResponseAuth_2eproto() {
    protobuf_AddDesc_MessageResponseAuth_2eproto();
  }
} static_descriptor_initializer_MessageResponseAuth_2eproto_;
#endif

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

static ::std::string* MutableUnknownFieldsForMessageResponseAuth(
    MessageResponseAuth* ptr) {
  return ptr->mutable_unknown_fields();
}

bool MessageResponseAuth_eAuthErrorType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetNone;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetBadUID;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetUsedUID;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetNeedVerify;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetBadVerify;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetBlocked;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetNoPassOrVerify;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetNotAllRequiredFields;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::aetPasswordChanged;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::eAuthErrorType_MIN;
const MessageResponseAuth_eAuthErrorType MessageResponseAuth::eAuthErrorType_MAX;
const int MessageResponseAuth::eAuthErrorType_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MessageResponseAuth::kErrorTypeFieldNumber;
const int MessageResponseAuth::kPlayerIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MessageResponseAuth::MessageResponseAuth()
  : ::google::protobuf::MessageLite(), _arena_ptr_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageResponseAuth)
}

void MessageResponseAuth::InitAsDefaultInstance() {
}

MessageResponseAuth::MessageResponseAuth(const MessageResponseAuth& from)
  : ::google::protobuf::MessageLite(),
    _arena_ptr_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageResponseAuth)
}

void MessageResponseAuth::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  _unknown_fields_.UnsafeSetDefault(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  errortype_ = 1;
  playerid_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageResponseAuth::~MessageResponseAuth() {
  // @@protoc_insertion_point(destructor:MessageResponseAuth)
  SharedDtor();
}

void MessageResponseAuth::SharedDtor() {
  _unknown_fields_.DestroyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void MessageResponseAuth::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const MessageResponseAuth& MessageResponseAuth::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_MessageResponseAuth_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_MessageResponseAuth_2eproto();
#endif
  return *default_instance_;
}

MessageResponseAuth* MessageResponseAuth::default_instance_ = NULL;

MessageResponseAuth* MessageResponseAuth::New(::google::protobuf::Arena* arena) const {
  MessageResponseAuth* n = new MessageResponseAuth;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MessageResponseAuth::Clear() {
// @@protoc_insertion_point(message_clear_start:MessageResponseAuth)
  if (_has_bits_[0 / 32] & 3u) {
    errortype_ = 1;
    playerid_ = GOOGLE_LONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  _unknown_fields_.ClearToEmptyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool MessageResponseAuth::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
      ::google::protobuf::internal::NewPermanentCallback(
          &MutableUnknownFieldsForMessageResponseAuth, this));
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string, false);
  // @@protoc_insertion_point(parse_start:MessageResponseAuth)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .MessageResponseAuth.eAuthErrorType errorType = 1 [default = aetNone];
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MessageResponseAuth_eAuthErrorType_IsValid(value)) {
            set_errortype(static_cast< ::MessageResponseAuth_eAuthErrorType >(value));
          } else {
            unknown_fields_stream.WriteVarint32(8);
            unknown_fields_stream.WriteVarint32(value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_playerId;
        break;
      }

      // optional int64 playerId = 2;
      case 2: {
        if (tag == 16) {
         parse_playerId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &playerid_)));
          set_has_playerid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MessageResponseAuth)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageResponseAuth)
  return false;
#undef DO_
}

void MessageResponseAuth::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageResponseAuth)
  // required .MessageResponseAuth.eAuthErrorType errorType = 1 [default = aetNone];
  if (has_errortype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->errortype(), output);
  }

  // optional int64 playerId = 2;
  if (has_playerid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->playerid(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   static_cast<int>(unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:MessageResponseAuth)
}

int MessageResponseAuth::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:MessageResponseAuth)
  int total_size = 0;

  // required .MessageResponseAuth.eAuthErrorType errorType = 1 [default = aetNone];
  if (has_errortype()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->errortype());
  }
  // optional int64 playerId = 2;
  if (has_playerid()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->playerid());
  }

  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageResponseAuth::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const MessageResponseAuth*>(&from));
}

void MessageResponseAuth::MergeFrom(const MessageResponseAuth& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MessageResponseAuth)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_errortype()) {
      set_errortype(from.errortype());
    }
    if (from.has_playerid()) {
      set_playerid(from.playerid());
    }
  }
  if (!from.unknown_fields().empty()) {
    mutable_unknown_fields()->append(from.unknown_fields());
  }
}

void MessageResponseAuth::CopyFrom(const MessageResponseAuth& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MessageResponseAuth)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageResponseAuth::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void MessageResponseAuth::Swap(MessageResponseAuth* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MessageResponseAuth::InternalSwap(MessageResponseAuth* other) {
  std::swap(errortype_, other->errortype_);
  std::swap(playerid_, other->playerid_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _unknown_fields_.Swap(&other->_unknown_fields_);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string MessageResponseAuth::GetTypeName() const {
  return "MessageResponseAuth";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseAuth

// required .MessageResponseAuth.eAuthErrorType errorType = 1 [default = aetNone];
bool MessageResponseAuth::has_errortype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void MessageResponseAuth::set_has_errortype() {
  _has_bits_[0] |= 0x00000001u;
}
void MessageResponseAuth::clear_has_errortype() {
  _has_bits_[0] &= ~0x00000001u;
}
void MessageResponseAuth::clear_errortype() {
  errortype_ = 1;
  clear_has_errortype();
}
 ::MessageResponseAuth_eAuthErrorType MessageResponseAuth::errortype() const {
  // @@protoc_insertion_point(field_get:MessageResponseAuth.errorType)
  return static_cast< ::MessageResponseAuth_eAuthErrorType >(errortype_);
}
 void MessageResponseAuth::set_errortype(::MessageResponseAuth_eAuthErrorType value) {
  assert(::MessageResponseAuth_eAuthErrorType_IsValid(value));
  set_has_errortype();
  errortype_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseAuth.errorType)
}

// optional int64 playerId = 2;
bool MessageResponseAuth::has_playerid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void MessageResponseAuth::set_has_playerid() {
  _has_bits_[0] |= 0x00000002u;
}
void MessageResponseAuth::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000002u;
}
void MessageResponseAuth::clear_playerid() {
  playerid_ = GOOGLE_LONGLONG(0);
  clear_has_playerid();
}
 ::google::protobuf::int64 MessageResponseAuth::playerid() const {
  // @@protoc_insertion_point(field_get:MessageResponseAuth.playerId)
  return playerid_;
}
 void MessageResponseAuth::set_playerid(::google::protobuf::int64 value) {
  set_has_playerid();
  playerid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseAuth.playerId)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

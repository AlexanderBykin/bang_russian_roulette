// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseRotateDrum.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MessageResponseRotateDrum.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_MessageResponseRotateDrum_2eproto() {
  delete MessageResponseRotateDrum::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_MessageResponseRotateDrum_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_MessageResponseRotateDrum_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  MessageResponseRotateDrum::default_instance_ = new MessageResponseRotateDrum();
  MessageResponseRotateDrum::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MessageResponseRotateDrum_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_MessageResponseRotateDrum_2eproto_once_);
void protobuf_AddDesc_MessageResponseRotateDrum_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_MessageResponseRotateDrum_2eproto_once_,
                 &protobuf_AddDesc_MessageResponseRotateDrum_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MessageResponseRotateDrum_2eproto {
  StaticDescriptorInitializer_MessageResponseRotateDrum_2eproto() {
    protobuf_AddDesc_MessageResponseRotateDrum_2eproto();
  }
} static_descriptor_initializer_MessageResponseRotateDrum_2eproto_;
#endif

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

static ::std::string* MutableUnknownFieldsForMessageResponseRotateDrum(
    MessageResponseRotateDrum* ptr) {
  return ptr->mutable_unknown_fields();
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MessageResponseRotateDrum::kRoomIdFieldNumber;
const int MessageResponseRotateDrum::kPlayerIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MessageResponseRotateDrum::MessageResponseRotateDrum()
  : ::google::protobuf::MessageLite(), _arena_ptr_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageResponseRotateDrum)
}

void MessageResponseRotateDrum::InitAsDefaultInstance() {
}

MessageResponseRotateDrum::MessageResponseRotateDrum(const MessageResponseRotateDrum& from)
  : ::google::protobuf::MessageLite(),
    _arena_ptr_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageResponseRotateDrum)
}

void MessageResponseRotateDrum::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  _unknown_fields_.UnsafeSetDefault(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  roomid_ = GOOGLE_LONGLONG(0);
  playerid_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageResponseRotateDrum::~MessageResponseRotateDrum() {
  // @@protoc_insertion_point(destructor:MessageResponseRotateDrum)
  SharedDtor();
}

void MessageResponseRotateDrum::SharedDtor() {
  _unknown_fields_.DestroyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void MessageResponseRotateDrum::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const MessageResponseRotateDrum& MessageResponseRotateDrum::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_MessageResponseRotateDrum_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_MessageResponseRotateDrum_2eproto();
#endif
  return *default_instance_;
}

MessageResponseRotateDrum* MessageResponseRotateDrum::default_instance_ = NULL;

MessageResponseRotateDrum* MessageResponseRotateDrum::New(::google::protobuf::Arena* arena) const {
  MessageResponseRotateDrum* n = new MessageResponseRotateDrum;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MessageResponseRotateDrum::Clear() {
// @@protoc_insertion_point(message_clear_start:MessageResponseRotateDrum)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(MessageResponseRotateDrum, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<MessageResponseRotateDrum*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(roomid_, playerid_);

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  _unknown_fields_.ClearToEmptyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool MessageResponseRotateDrum::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
      ::google::protobuf::internal::NewPermanentCallback(
          &MutableUnknownFieldsForMessageResponseRotateDrum, this));
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string, false);
  // @@protoc_insertion_point(parse_start:MessageResponseRotateDrum)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 roomId = 1 [default = 0];
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &roomid_)));
          set_has_roomid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_playerId;
        break;
      }

      // required int64 playerId = 2 [default = 0];
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
  // @@protoc_insertion_point(parse_success:MessageResponseRotateDrum)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageResponseRotateDrum)
  return false;
#undef DO_
}

void MessageResponseRotateDrum::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageResponseRotateDrum)
  // required int64 roomId = 1 [default = 0];
  if (has_roomid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->roomid(), output);
  }

  // required int64 playerId = 2 [default = 0];
  if (has_playerid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->playerid(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   static_cast<int>(unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:MessageResponseRotateDrum)
}

int MessageResponseRotateDrum::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:MessageResponseRotateDrum)
  int total_size = 0;

  if (has_roomid()) {
    // required int64 roomId = 1 [default = 0];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->roomid());
  }

  if (has_playerid()) {
    // required int64 playerId = 2 [default = 0];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->playerid());
  }

  return total_size;
}
int MessageResponseRotateDrum::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:MessageResponseRotateDrum)
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int64 roomId = 1 [default = 0];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->roomid());

    // required int64 playerId = 2 [default = 0];
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->playerid());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageResponseRotateDrum::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const MessageResponseRotateDrum*>(&from));
}

void MessageResponseRotateDrum::MergeFrom(const MessageResponseRotateDrum& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MessageResponseRotateDrum)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_roomid()) {
      set_roomid(from.roomid());
    }
    if (from.has_playerid()) {
      set_playerid(from.playerid());
    }
  }
  if (!from.unknown_fields().empty()) {
    mutable_unknown_fields()->append(from.unknown_fields());
  }
}

void MessageResponseRotateDrum::CopyFrom(const MessageResponseRotateDrum& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MessageResponseRotateDrum)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageResponseRotateDrum::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void MessageResponseRotateDrum::Swap(MessageResponseRotateDrum* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MessageResponseRotateDrum::InternalSwap(MessageResponseRotateDrum* other) {
  std::swap(roomid_, other->roomid_);
  std::swap(playerid_, other->playerid_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _unknown_fields_.Swap(&other->_unknown_fields_);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string MessageResponseRotateDrum::GetTypeName() const {
  return "MessageResponseRotateDrum";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseRotateDrum

// required int64 roomId = 1 [default = 0];
bool MessageResponseRotateDrum::has_roomid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void MessageResponseRotateDrum::set_has_roomid() {
  _has_bits_[0] |= 0x00000001u;
}
void MessageResponseRotateDrum::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000001u;
}
void MessageResponseRotateDrum::clear_roomid() {
  roomid_ = GOOGLE_LONGLONG(0);
  clear_has_roomid();
}
 ::google::protobuf::int64 MessageResponseRotateDrum::roomid() const {
  // @@protoc_insertion_point(field_get:MessageResponseRotateDrum.roomId)
  return roomid_;
}
 void MessageResponseRotateDrum::set_roomid(::google::protobuf::int64 value) {
  set_has_roomid();
  roomid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseRotateDrum.roomId)
}

// required int64 playerId = 2 [default = 0];
bool MessageResponseRotateDrum::has_playerid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void MessageResponseRotateDrum::set_has_playerid() {
  _has_bits_[0] |= 0x00000002u;
}
void MessageResponseRotateDrum::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000002u;
}
void MessageResponseRotateDrum::clear_playerid() {
  playerid_ = GOOGLE_LONGLONG(0);
  clear_has_playerid();
}
 ::google::protobuf::int64 MessageResponseRotateDrum::playerid() const {
  // @@protoc_insertion_point(field_get:MessageResponseRotateDrum.playerId)
  return playerid_;
}
 void MessageResponseRotateDrum::set_playerid(::google::protobuf::int64 value) {
  set_has_playerid();
  playerid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseRotateDrum.playerId)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
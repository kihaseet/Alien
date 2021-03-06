// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client.proto

#ifndef PROTOBUF_client_2eproto__INCLUDED
#define PROTOBUF_client_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "types.pb.h"  // IWYU pragma: export
// @@protoc_insertion_point(includes)

namespace Xenophobia {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_client_2eproto();
void protobuf_AssignDesc_client_2eproto();
void protobuf_ShutdownFile_client_2eproto();

class ClientMessage;
class DoAction;
class RegisterName;
class RegisterRole;

enum ClientMessageType {
  CMT_REGISTER_NAME = 0,
  CMT_REGISTER_ROLE = 1,
  CMT_DISCONNECT = 2,
  CMT_DO_ACTION = 3,
  ClientMessageType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ClientMessageType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ClientMessageType_IsValid(int value);
const ClientMessageType ClientMessageType_MIN = CMT_REGISTER_NAME;
const ClientMessageType ClientMessageType_MAX = CMT_DO_ACTION;
const int ClientMessageType_ARRAYSIZE = ClientMessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ClientMessageType_descriptor();
inline const ::std::string& ClientMessageType_Name(ClientMessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ClientMessageType_descriptor(), value);
}
inline bool ClientMessageType_Parse(
    const ::std::string& name, ClientMessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ClientMessageType>(
    ClientMessageType_descriptor(), name, value);
}
// ===================================================================

class RegisterName : public ::google::protobuf::Message {
 public:
  RegisterName();
  virtual ~RegisterName();

  RegisterName(const RegisterName& from);

  inline RegisterName& operator=(const RegisterName& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RegisterName& default_instance();

  void Swap(RegisterName* other);

  // implements Message ----------------------------------------------

  inline RegisterName* New() const { return New(NULL); }

  RegisterName* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RegisterName& from);
  void MergeFrom(const RegisterName& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(RegisterName* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:Xenophobia.RegisterName)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();

  void InitAsDefaultInstance();
  static RegisterName* default_instance_;
};
// -------------------------------------------------------------------

class RegisterRole : public ::google::protobuf::Message {
 public:
  RegisterRole();
  virtual ~RegisterRole();

  RegisterRole(const RegisterRole& from);

  inline RegisterRole& operator=(const RegisterRole& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RegisterRole& default_instance();

  void Swap(RegisterRole* other);

  // implements Message ----------------------------------------------

  inline RegisterRole* New() const { return New(NULL); }

  RegisterRole* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RegisterRole& from);
  void MergeFrom(const RegisterRole& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(RegisterRole* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .types.Role role = 1;
  void clear_role();
  static const int kRoleFieldNumber = 1;
  ::types::Role role() const;
  void set_role(::types::Role value);

  // @@protoc_insertion_point(class_scope:Xenophobia.RegisterRole)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  int role_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();

  void InitAsDefaultInstance();
  static RegisterRole* default_instance_;
};
// -------------------------------------------------------------------

class DoAction : public ::google::protobuf::Message {
 public:
  DoAction();
  virtual ~DoAction();

  DoAction(const DoAction& from);

  inline DoAction& operator=(const DoAction& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DoAction& default_instance();

  void Swap(DoAction* other);

  // implements Message ----------------------------------------------

  inline DoAction* New() const { return New(NULL); }

  DoAction* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DoAction& from);
  void MergeFrom(const DoAction& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(DoAction* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .types.Action action = 1;
  void clear_action();
  static const int kActionFieldNumber = 1;
  ::types::Action action() const;
  void set_action(::types::Action value);

  // optional .types.Item item = 2;
  void clear_item();
  static const int kItemFieldNumber = 2;
  ::types::Item item() const;
  void set_item(::types::Item value);

  // repeated .types.ITarget targets = 3;
  int targets_size() const;
  void clear_targets();
  static const int kTargetsFieldNumber = 3;
  const ::types::ITarget& targets(int index) const;
  ::types::ITarget* mutable_targets(int index);
  ::types::ITarget* add_targets();
  ::google::protobuf::RepeatedPtrField< ::types::ITarget >*
      mutable_targets();
  const ::google::protobuf::RepeatedPtrField< ::types::ITarget >&
      targets() const;

  // @@protoc_insertion_point(class_scope:Xenophobia.DoAction)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  int action_;
  int item_;
  ::google::protobuf::RepeatedPtrField< ::types::ITarget > targets_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();

  void InitAsDefaultInstance();
  static DoAction* default_instance_;
};
// -------------------------------------------------------------------

class ClientMessage : public ::google::protobuf::Message {
 public:
  ClientMessage();
  virtual ~ClientMessage();

  ClientMessage(const ClientMessage& from);

  inline ClientMessage& operator=(const ClientMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientMessage& default_instance();

  void Swap(ClientMessage* other);

  // implements Message ----------------------------------------------

  inline ClientMessage* New() const { return New(NULL); }

  ClientMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientMessage& from);
  void MergeFrom(const ClientMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ClientMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .Xenophobia.ClientMessageType type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::Xenophobia::ClientMessageType type() const;
  void set_type(::Xenophobia::ClientMessageType value);

  // optional .Xenophobia.RegisterName reg_name = 2;
  bool has_reg_name() const;
  void clear_reg_name();
  static const int kRegNameFieldNumber = 2;
  const ::Xenophobia::RegisterName& reg_name() const;
  ::Xenophobia::RegisterName* mutable_reg_name();
  ::Xenophobia::RegisterName* release_reg_name();
  void set_allocated_reg_name(::Xenophobia::RegisterName* reg_name);

  // optional .Xenophobia.RegisterRole reg_role = 3;
  bool has_reg_role() const;
  void clear_reg_role();
  static const int kRegRoleFieldNumber = 3;
  const ::Xenophobia::RegisterRole& reg_role() const;
  ::Xenophobia::RegisterRole* mutable_reg_role();
  ::Xenophobia::RegisterRole* release_reg_role();
  void set_allocated_reg_role(::Xenophobia::RegisterRole* reg_role);

  // optional .Xenophobia.DoAction do_action = 4;
  bool has_do_action() const;
  void clear_do_action();
  static const int kDoActionFieldNumber = 4;
  const ::Xenophobia::DoAction& do_action() const;
  ::Xenophobia::DoAction* mutable_do_action();
  ::Xenophobia::DoAction* release_do_action();
  void set_allocated_do_action(::Xenophobia::DoAction* do_action);

  // @@protoc_insertion_point(class_scope:Xenophobia.ClientMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::Xenophobia::RegisterName* reg_name_;
  ::Xenophobia::RegisterRole* reg_role_;
  ::Xenophobia::DoAction* do_action_;
  int type_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();

  void InitAsDefaultInstance();
  static ClientMessage* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// RegisterName

// optional string name = 1;
inline void RegisterName::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RegisterName::name() const {
  // @@protoc_insertion_point(field_get:Xenophobia.RegisterName.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RegisterName::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Xenophobia.RegisterName.name)
}
inline void RegisterName::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Xenophobia.RegisterName.name)
}
inline void RegisterName::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Xenophobia.RegisterName.name)
}
inline ::std::string* RegisterName::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:Xenophobia.RegisterName.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RegisterName::release_name() {
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RegisterName::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Xenophobia.RegisterName.name)
}

// -------------------------------------------------------------------

// RegisterRole

// optional .types.Role role = 1;
inline void RegisterRole::clear_role() {
  role_ = 0;
}
inline ::types::Role RegisterRole::role() const {
  // @@protoc_insertion_point(field_get:Xenophobia.RegisterRole.role)
  return static_cast< ::types::Role >(role_);
}
inline void RegisterRole::set_role(::types::Role value) {
  
  role_ = value;
  // @@protoc_insertion_point(field_set:Xenophobia.RegisterRole.role)
}

// -------------------------------------------------------------------

// DoAction

// optional .types.Action action = 1;
inline void DoAction::clear_action() {
  action_ = 0;
}
inline ::types::Action DoAction::action() const {
  // @@protoc_insertion_point(field_get:Xenophobia.DoAction.action)
  return static_cast< ::types::Action >(action_);
}
inline void DoAction::set_action(::types::Action value) {
  
  action_ = value;
  // @@protoc_insertion_point(field_set:Xenophobia.DoAction.action)
}

// optional .types.Item item = 2;
inline void DoAction::clear_item() {
  item_ = 0;
}
inline ::types::Item DoAction::item() const {
  // @@protoc_insertion_point(field_get:Xenophobia.DoAction.item)
  return static_cast< ::types::Item >(item_);
}
inline void DoAction::set_item(::types::Item value) {
  
  item_ = value;
  // @@protoc_insertion_point(field_set:Xenophobia.DoAction.item)
}

// repeated .types.ITarget targets = 3;
inline int DoAction::targets_size() const {
  return targets_.size();
}
inline void DoAction::clear_targets() {
  targets_.Clear();
}
inline const ::types::ITarget& DoAction::targets(int index) const {
  // @@protoc_insertion_point(field_get:Xenophobia.DoAction.targets)
  return targets_.Get(index);
}
inline ::types::ITarget* DoAction::mutable_targets(int index) {
  // @@protoc_insertion_point(field_mutable:Xenophobia.DoAction.targets)
  return targets_.Mutable(index);
}
inline ::types::ITarget* DoAction::add_targets() {
  // @@protoc_insertion_point(field_add:Xenophobia.DoAction.targets)
  return targets_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::types::ITarget >*
DoAction::mutable_targets() {
  // @@protoc_insertion_point(field_mutable_list:Xenophobia.DoAction.targets)
  return &targets_;
}
inline const ::google::protobuf::RepeatedPtrField< ::types::ITarget >&
DoAction::targets() const {
  // @@protoc_insertion_point(field_list:Xenophobia.DoAction.targets)
  return targets_;
}

// -------------------------------------------------------------------

// ClientMessage

// optional .Xenophobia.ClientMessageType type = 1;
inline void ClientMessage::clear_type() {
  type_ = 0;
}
inline ::Xenophobia::ClientMessageType ClientMessage::type() const {
  // @@protoc_insertion_point(field_get:Xenophobia.ClientMessage.type)
  return static_cast< ::Xenophobia::ClientMessageType >(type_);
}
inline void ClientMessage::set_type(::Xenophobia::ClientMessageType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:Xenophobia.ClientMessage.type)
}

// optional .Xenophobia.RegisterName reg_name = 2;
inline bool ClientMessage::has_reg_name() const {
  return !_is_default_instance_ && reg_name_ != NULL;
}
inline void ClientMessage::clear_reg_name() {
  if (GetArenaNoVirtual() == NULL && reg_name_ != NULL) delete reg_name_;
  reg_name_ = NULL;
}
inline const ::Xenophobia::RegisterName& ClientMessage::reg_name() const {
  // @@protoc_insertion_point(field_get:Xenophobia.ClientMessage.reg_name)
  return reg_name_ != NULL ? *reg_name_ : *default_instance_->reg_name_;
}
inline ::Xenophobia::RegisterName* ClientMessage::mutable_reg_name() {
  
  if (reg_name_ == NULL) {
    reg_name_ = new ::Xenophobia::RegisterName;
  }
  // @@protoc_insertion_point(field_mutable:Xenophobia.ClientMessage.reg_name)
  return reg_name_;
}
inline ::Xenophobia::RegisterName* ClientMessage::release_reg_name() {
  
  ::Xenophobia::RegisterName* temp = reg_name_;
  reg_name_ = NULL;
  return temp;
}
inline void ClientMessage::set_allocated_reg_name(::Xenophobia::RegisterName* reg_name) {
  delete reg_name_;
  reg_name_ = reg_name;
  if (reg_name) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:Xenophobia.ClientMessage.reg_name)
}

// optional .Xenophobia.RegisterRole reg_role = 3;
inline bool ClientMessage::has_reg_role() const {
  return !_is_default_instance_ && reg_role_ != NULL;
}
inline void ClientMessage::clear_reg_role() {
  if (GetArenaNoVirtual() == NULL && reg_role_ != NULL) delete reg_role_;
  reg_role_ = NULL;
}
inline const ::Xenophobia::RegisterRole& ClientMessage::reg_role() const {
  // @@protoc_insertion_point(field_get:Xenophobia.ClientMessage.reg_role)
  return reg_role_ != NULL ? *reg_role_ : *default_instance_->reg_role_;
}
inline ::Xenophobia::RegisterRole* ClientMessage::mutable_reg_role() {
  
  if (reg_role_ == NULL) {
    reg_role_ = new ::Xenophobia::RegisterRole;
  }
  // @@protoc_insertion_point(field_mutable:Xenophobia.ClientMessage.reg_role)
  return reg_role_;
}
inline ::Xenophobia::RegisterRole* ClientMessage::release_reg_role() {
  
  ::Xenophobia::RegisterRole* temp = reg_role_;
  reg_role_ = NULL;
  return temp;
}
inline void ClientMessage::set_allocated_reg_role(::Xenophobia::RegisterRole* reg_role) {
  delete reg_role_;
  reg_role_ = reg_role;
  if (reg_role) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:Xenophobia.ClientMessage.reg_role)
}

// optional .Xenophobia.DoAction do_action = 4;
inline bool ClientMessage::has_do_action() const {
  return !_is_default_instance_ && do_action_ != NULL;
}
inline void ClientMessage::clear_do_action() {
  if (GetArenaNoVirtual() == NULL && do_action_ != NULL) delete do_action_;
  do_action_ = NULL;
}
inline const ::Xenophobia::DoAction& ClientMessage::do_action() const {
  // @@protoc_insertion_point(field_get:Xenophobia.ClientMessage.do_action)
  return do_action_ != NULL ? *do_action_ : *default_instance_->do_action_;
}
inline ::Xenophobia::DoAction* ClientMessage::mutable_do_action() {
  
  if (do_action_ == NULL) {
    do_action_ = new ::Xenophobia::DoAction;
  }
  // @@protoc_insertion_point(field_mutable:Xenophobia.ClientMessage.do_action)
  return do_action_;
}
inline ::Xenophobia::DoAction* ClientMessage::release_do_action() {
  
  ::Xenophobia::DoAction* temp = do_action_;
  do_action_ = NULL;
  return temp;
}
inline void ClientMessage::set_allocated_do_action(::Xenophobia::DoAction* do_action) {
  delete do_action_;
  do_action_ = do_action;
  if (do_action) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:Xenophobia.ClientMessage.do_action)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Xenophobia

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::Xenophobia::ClientMessageType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Xenophobia::ClientMessageType>() {
  return ::Xenophobia::ClientMessageType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_2eproto__INCLUDED

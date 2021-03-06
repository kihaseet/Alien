// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: types.proto

#ifndef PROTOBUF_types_2eproto__INCLUDED
#define PROTOBUF_types_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace types {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_types_2eproto();
void protobuf_AssignDesc_types_2eproto();
void protobuf_ShutdownFile_types_2eproto();

class Event;
class ITarget;

enum Role {
  PASSENGER = 0,
  CAPTAIN = 1,
  DOCTOR = 2,
  GUNMEN = 3,
  ENGINEER = 4,
  SCIENTIST = 5,
  SIGNALMEN = 6,
  ASSISTANT = 101,
  DEP_DOCTOR = 102,
  DEP_GUNMEN = 103,
  DEP_ENGINEER = 104,
  DEP_SCIENTIST = 105,
  DEP_SIGNALMEN = 106,
  Role_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Role_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Role_IsValid(int value);
const Role Role_MIN = PASSENGER;
const Role Role_MAX = DEP_SIGNALMEN;
const int Role_ARRAYSIZE = Role_MAX + 1;

const ::google::protobuf::EnumDescriptor* Role_descriptor();
inline const ::std::string& Role_Name(Role value) {
  return ::google::protobuf::internal::NameOfEnum(
    Role_descriptor(), value);
}
inline bool Role_Parse(
    const ::std::string& name, Role* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Role>(
    Role_descriptor(), name, value);
}
enum Action {
  USE_ITEM = 0,
  USE_ULT = 1,
  USE_BADGE = 2,
  ATTACK = 3,
  INFECT = 4,
  VOTE = 5,
  UNVOTE = 6,
  WAIT = 7,
  UP = 8,
  DOWN = 9,
  Action_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Action_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Action_IsValid(int value);
const Action Action_MIN = USE_ITEM;
const Action Action_MAX = DOWN;
const int Action_ARRAYSIZE = Action_MAX + 1;

const ::google::protobuf::EnumDescriptor* Action_descriptor();
inline const ::std::string& Action_Name(Action value) {
  return ::google::protobuf::internal::NameOfEnum(
    Action_descriptor(), value);
}
inline bool Action_Parse(
    const ::std::string& name, Action* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Action>(
    Action_descriptor(), name, value);
}
enum Item {
  BADGE = 0,
  ROTATION = 1,
  BLASTER = 2,
  INJECTOR = 3,
  NOTEBOOK = 4,
  BATTERY = 5,
  SCANNER = 6,
  MOP = 7,
  FETUS = 8,
  Item_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Item_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Item_IsValid(int value);
const Item Item_MIN = BADGE;
const Item Item_MAX = FETUS;
const int Item_ARRAYSIZE = Item_MAX + 1;

const ::google::protobuf::EnumDescriptor* Item_descriptor();
inline const ::std::string& Item_Name(Item value) {
  return ::google::protobuf::internal::NameOfEnum(
    Item_descriptor(), value);
}
inline bool Item_Parse(
    const ::std::string& name, Item* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Item>(
    Item_descriptor(), name, value);
}
enum PlayerStatus {
  PS_UP = 0,
  PS_DOWN = 1,
  PS_DEAD = 2,
  PlayerStatus_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  PlayerStatus_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool PlayerStatus_IsValid(int value);
const PlayerStatus PlayerStatus_MIN = PS_UP;
const PlayerStatus PlayerStatus_MAX = PS_DEAD;
const int PlayerStatus_ARRAYSIZE = PlayerStatus_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerStatus_descriptor();
inline const ::std::string& PlayerStatus_Name(PlayerStatus value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerStatus_descriptor(), value);
}
inline bool PlayerStatus_Parse(
    const ::std::string& name, PlayerStatus* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerStatus>(
    PlayerStatus_descriptor(), name, value);
}
enum EventType {
  ET_USE_ITEM = 0,
  ET_USE_ULT = 1,
  ET_USE_BADGE = 2,
  ET_GET_ROLE = 3,
  ET_DEL_ROLE = 4,
  ET_INGAME_MESSAGE = 5,
  ET_GET_DUTY = 6,
  ET_CONNECT = 7,
  ET_DISCONNECT = 8,
  ET_DIED = 9,
  ET_DOWN = 10,
  ET_UP = 11,
  ET_VOTE = 12,
  ET_UNVOTE = 13,
  EventType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  EventType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool EventType_IsValid(int value);
const EventType EventType_MIN = ET_USE_ITEM;
const EventType EventType_MAX = ET_UNVOTE;
const int EventType_ARRAYSIZE = EventType_MAX + 1;

const ::google::protobuf::EnumDescriptor* EventType_descriptor();
inline const ::std::string& EventType_Name(EventType value) {
  return ::google::protobuf::internal::NameOfEnum(
    EventType_descriptor(), value);
}
inline bool EventType_Parse(
    const ::std::string& name, EventType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<EventType>(
    EventType_descriptor(), name, value);
}
enum VotingType {
  FOR_ALIEN = 0,
  FOR_CAPTAIN = 1,
  FOR_DOCTOR = 2,
  FOR_GUNMEN = 3,
  FOR_ENGINEER = 4,
  FOR_SCIENTIST = 5,
  FOR_SIGNALMEN = 6,
  VotingType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  VotingType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool VotingType_IsValid(int value);
const VotingType VotingType_MIN = FOR_ALIEN;
const VotingType VotingType_MAX = FOR_SIGNALMEN;
const int VotingType_ARRAYSIZE = VotingType_MAX + 1;

const ::google::protobuf::EnumDescriptor* VotingType_descriptor();
inline const ::std::string& VotingType_Name(VotingType value) {
  return ::google::protobuf::internal::NameOfEnum(
    VotingType_descriptor(), value);
}
inline bool VotingType_Parse(
    const ::std::string& name, VotingType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<VotingType>(
    VotingType_descriptor(), name, value);
}
enum TargetType {
  TAT_NAME = 0,
  TAT_ITEM = 1,
  TAT_ROLE = 2,
  TargetType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  TargetType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool TargetType_IsValid(int value);
const TargetType TargetType_MIN = TAT_NAME;
const TargetType TargetType_MAX = TAT_ROLE;
const int TargetType_ARRAYSIZE = TargetType_MAX + 1;

const ::google::protobuf::EnumDescriptor* TargetType_descriptor();
inline const ::std::string& TargetType_Name(TargetType value) {
  return ::google::protobuf::internal::NameOfEnum(
    TargetType_descriptor(), value);
}
inline bool TargetType_Parse(
    const ::std::string& name, TargetType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TargetType>(
    TargetType_descriptor(), name, value);
}
// ===================================================================

class ITarget : public ::google::protobuf::Message {
 public:
  ITarget();
  virtual ~ITarget();

  ITarget(const ITarget& from);

  inline ITarget& operator=(const ITarget& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ITarget& default_instance();

  void Swap(ITarget* other);

  // implements Message ----------------------------------------------

  inline ITarget* New() const { return New(NULL); }

  ITarget* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ITarget& from);
  void MergeFrom(const ITarget& from);
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
  void InternalSwap(ITarget* other);
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

  // optional .types.TargetType type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::types::TargetType type() const;
  void set_type(::types::TargetType value);

  // optional string name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional .types.Item item = 3;
  void clear_item();
  static const int kItemFieldNumber = 3;
  ::types::Item item() const;
  void set_item(::types::Item value);

  // optional .types.Role role = 4;
  void clear_role();
  static const int kRoleFieldNumber = 4;
  ::types::Role role() const;
  void set_role(::types::Role value);

  // @@protoc_insertion_point(class_scope:types.ITarget)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  int type_;
  int item_;
  int role_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_types_2eproto();
  friend void protobuf_AssignDesc_types_2eproto();
  friend void protobuf_ShutdownFile_types_2eproto();

  void InitAsDefaultInstance();
  static ITarget* default_instance_;
};
// -------------------------------------------------------------------

class Event : public ::google::protobuf::Message {
 public:
  Event();
  virtual ~Event();

  Event(const Event& from);

  inline Event& operator=(const Event& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Event& default_instance();

  void Swap(Event* other);

  // implements Message ----------------------------------------------

  inline Event* New() const { return New(NULL); }

  Event* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Event& from);
  void MergeFrom(const Event& from);
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
  void InternalSwap(Event* other);
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

  // optional .types.EventType event = 1;
  void clear_event();
  static const int kEventFieldNumber = 1;
  ::types::EventType event() const;
  void set_event(::types::EventType value);

  // optional .types.ITarget event_who = 2;
  bool has_event_who() const;
  void clear_event_who();
  static const int kEventWhoFieldNumber = 2;
  const ::types::ITarget& event_who() const;
  ::types::ITarget* mutable_event_who();
  ::types::ITarget* release_event_who();
  void set_allocated_event_who(::types::ITarget* event_who);

  // optional .types.ITarget event_object = 3;
  bool has_event_object() const;
  void clear_event_object();
  static const int kEventObjectFieldNumber = 3;
  const ::types::ITarget& event_object() const;
  ::types::ITarget* mutable_event_object();
  ::types::ITarget* release_event_object();
  void set_allocated_event_object(::types::ITarget* event_object);

  // repeated .types.ITarget event_target = 4;
  int event_target_size() const;
  void clear_event_target();
  static const int kEventTargetFieldNumber = 4;
  const ::types::ITarget& event_target(int index) const;
  ::types::ITarget* mutable_event_target(int index);
  ::types::ITarget* add_event_target();
  ::google::protobuf::RepeatedPtrField< ::types::ITarget >*
      mutable_event_target();
  const ::google::protobuf::RepeatedPtrField< ::types::ITarget >&
      event_target() const;

  // optional string payload = 5;
  void clear_payload();
  static const int kPayloadFieldNumber = 5;
  const ::std::string& payload() const;
  void set_payload(const ::std::string& value);
  void set_payload(const char* value);
  void set_payload(const char* value, size_t size);
  ::std::string* mutable_payload();
  ::std::string* release_payload();
  void set_allocated_payload(::std::string* payload);

  // @@protoc_insertion_point(class_scope:types.Event)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::types::ITarget* event_who_;
  ::types::ITarget* event_object_;
  ::google::protobuf::RepeatedPtrField< ::types::ITarget > event_target_;
  ::google::protobuf::internal::ArenaStringPtr payload_;
  int event_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_types_2eproto();
  friend void protobuf_AssignDesc_types_2eproto();
  friend void protobuf_ShutdownFile_types_2eproto();

  void InitAsDefaultInstance();
  static Event* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ITarget

// optional .types.TargetType type = 1;
inline void ITarget::clear_type() {
  type_ = 0;
}
inline ::types::TargetType ITarget::type() const {
  // @@protoc_insertion_point(field_get:types.ITarget.type)
  return static_cast< ::types::TargetType >(type_);
}
inline void ITarget::set_type(::types::TargetType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:types.ITarget.type)
}

// optional string name = 2;
inline void ITarget::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ITarget::name() const {
  // @@protoc_insertion_point(field_get:types.ITarget.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ITarget::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:types.ITarget.name)
}
inline void ITarget::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:types.ITarget.name)
}
inline void ITarget::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:types.ITarget.name)
}
inline ::std::string* ITarget::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:types.ITarget.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ITarget::release_name() {
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ITarget::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:types.ITarget.name)
}

// optional .types.Item item = 3;
inline void ITarget::clear_item() {
  item_ = 0;
}
inline ::types::Item ITarget::item() const {
  // @@protoc_insertion_point(field_get:types.ITarget.item)
  return static_cast< ::types::Item >(item_);
}
inline void ITarget::set_item(::types::Item value) {
  
  item_ = value;
  // @@protoc_insertion_point(field_set:types.ITarget.item)
}

// optional .types.Role role = 4;
inline void ITarget::clear_role() {
  role_ = 0;
}
inline ::types::Role ITarget::role() const {
  // @@protoc_insertion_point(field_get:types.ITarget.role)
  return static_cast< ::types::Role >(role_);
}
inline void ITarget::set_role(::types::Role value) {
  
  role_ = value;
  // @@protoc_insertion_point(field_set:types.ITarget.role)
}

// -------------------------------------------------------------------

// Event

// optional .types.EventType event = 1;
inline void Event::clear_event() {
  event_ = 0;
}
inline ::types::EventType Event::event() const {
  // @@protoc_insertion_point(field_get:types.Event.event)
  return static_cast< ::types::EventType >(event_);
}
inline void Event::set_event(::types::EventType value) {
  
  event_ = value;
  // @@protoc_insertion_point(field_set:types.Event.event)
}

// optional .types.ITarget event_who = 2;
inline bool Event::has_event_who() const {
  return !_is_default_instance_ && event_who_ != NULL;
}
inline void Event::clear_event_who() {
  if (GetArenaNoVirtual() == NULL && event_who_ != NULL) delete event_who_;
  event_who_ = NULL;
}
inline const ::types::ITarget& Event::event_who() const {
  // @@protoc_insertion_point(field_get:types.Event.event_who)
  return event_who_ != NULL ? *event_who_ : *default_instance_->event_who_;
}
inline ::types::ITarget* Event::mutable_event_who() {
  
  if (event_who_ == NULL) {
    event_who_ = new ::types::ITarget;
  }
  // @@protoc_insertion_point(field_mutable:types.Event.event_who)
  return event_who_;
}
inline ::types::ITarget* Event::release_event_who() {
  
  ::types::ITarget* temp = event_who_;
  event_who_ = NULL;
  return temp;
}
inline void Event::set_allocated_event_who(::types::ITarget* event_who) {
  delete event_who_;
  event_who_ = event_who;
  if (event_who) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:types.Event.event_who)
}

// optional .types.ITarget event_object = 3;
inline bool Event::has_event_object() const {
  return !_is_default_instance_ && event_object_ != NULL;
}
inline void Event::clear_event_object() {
  if (GetArenaNoVirtual() == NULL && event_object_ != NULL) delete event_object_;
  event_object_ = NULL;
}
inline const ::types::ITarget& Event::event_object() const {
  // @@protoc_insertion_point(field_get:types.Event.event_object)
  return event_object_ != NULL ? *event_object_ : *default_instance_->event_object_;
}
inline ::types::ITarget* Event::mutable_event_object() {
  
  if (event_object_ == NULL) {
    event_object_ = new ::types::ITarget;
  }
  // @@protoc_insertion_point(field_mutable:types.Event.event_object)
  return event_object_;
}
inline ::types::ITarget* Event::release_event_object() {
  
  ::types::ITarget* temp = event_object_;
  event_object_ = NULL;
  return temp;
}
inline void Event::set_allocated_event_object(::types::ITarget* event_object) {
  delete event_object_;
  event_object_ = event_object;
  if (event_object) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:types.Event.event_object)
}

// repeated .types.ITarget event_target = 4;
inline int Event::event_target_size() const {
  return event_target_.size();
}
inline void Event::clear_event_target() {
  event_target_.Clear();
}
inline const ::types::ITarget& Event::event_target(int index) const {
  // @@protoc_insertion_point(field_get:types.Event.event_target)
  return event_target_.Get(index);
}
inline ::types::ITarget* Event::mutable_event_target(int index) {
  // @@protoc_insertion_point(field_mutable:types.Event.event_target)
  return event_target_.Mutable(index);
}
inline ::types::ITarget* Event::add_event_target() {
  // @@protoc_insertion_point(field_add:types.Event.event_target)
  return event_target_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::types::ITarget >*
Event::mutable_event_target() {
  // @@protoc_insertion_point(field_mutable_list:types.Event.event_target)
  return &event_target_;
}
inline const ::google::protobuf::RepeatedPtrField< ::types::ITarget >&
Event::event_target() const {
  // @@protoc_insertion_point(field_list:types.Event.event_target)
  return event_target_;
}

// optional string payload = 5;
inline void Event::clear_payload() {
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Event::payload() const {
  // @@protoc_insertion_point(field_get:types.Event.payload)
  return payload_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Event::set_payload(const ::std::string& value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:types.Event.payload)
}
inline void Event::set_payload(const char* value) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:types.Event.payload)
}
inline void Event::set_payload(const char* value, size_t size) {
  
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:types.Event.payload)
}
inline ::std::string* Event::mutable_payload() {
  
  // @@protoc_insertion_point(field_mutable:types.Event.payload)
  return payload_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Event::release_payload() {
  
  return payload_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Event::set_allocated_payload(::std::string* payload) {
  if (payload != NULL) {
    
  } else {
    
  }
  payload_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:types.Event.payload)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace types

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::types::Role> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::Role>() {
  return ::types::Role_descriptor();
}
template <> struct is_proto_enum< ::types::Action> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::Action>() {
  return ::types::Action_descriptor();
}
template <> struct is_proto_enum< ::types::Item> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::Item>() {
  return ::types::Item_descriptor();
}
template <> struct is_proto_enum< ::types::PlayerStatus> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::PlayerStatus>() {
  return ::types::PlayerStatus_descriptor();
}
template <> struct is_proto_enum< ::types::EventType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::EventType>() {
  return ::types::EventType_descriptor();
}
template <> struct is_proto_enum< ::types::VotingType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::VotingType>() {
  return ::types::VotingType_descriptor();
}
template <> struct is_proto_enum< ::types::TargetType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::types::TargetType>() {
  return ::types::TargetType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_types_2eproto__INCLUDED

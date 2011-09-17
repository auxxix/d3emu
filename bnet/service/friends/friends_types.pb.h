// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: service/friends/friends_types.proto

#ifndef PROTOBUF_service_2ffriends_2ffriends_5ftypes_2eproto__INCLUDED
#define PROTOBUF_service_2ffriends_2ffriends_5ftypes_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "lib/protocol/attribute.pb.h"
#include "lib/protocol/entity.pb.h"
#include "lib/protocol/invitation.pb.h"
// @@protoc_insertion_point(includes)

namespace bnet {
namespace protocol {
namespace friends {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
void protobuf_AssignDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
void protobuf_ShutdownFile_service_2ffriends_2ffriends_5ftypes_2eproto();

class Friend;
class FriendInvitation;

// ===================================================================

class Friend : public ::google::protobuf::Message {
 public:
  Friend();
  virtual ~Friend();
  
  Friend(const Friend& from);
  
  inline Friend& operator=(const Friend& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Friend& default_instance();
  
  void Swap(Friend* other);
  
  // implements Message ----------------------------------------------
  
  Friend* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Friend& from);
  void MergeFrom(const Friend& from);
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
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required .bnet.protocol.EntityId id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline const ::bnet::protocol::EntityId& id() const;
  inline ::bnet::protocol::EntityId* mutable_id();
  
  // repeated .bnet.protocol.attribute.Attribute attribute = 2;
  inline int attribute_size() const;
  inline void clear_attribute();
  static const int kAttributeFieldNumber = 2;
  inline const ::bnet::protocol::attribute::Attribute& attribute(int index) const;
  inline ::bnet::protocol::attribute::Attribute* mutable_attribute(int index);
  inline ::bnet::protocol::attribute::Attribute* add_attribute();
  inline const ::google::protobuf::RepeatedPtrField< ::bnet::protocol::attribute::Attribute >&
      attribute() const;
  inline ::google::protobuf::RepeatedPtrField< ::bnet::protocol::attribute::Attribute >*
      mutable_attribute();
  
  // @@protoc_insertion_point(class_scope:bnet.protocol.friends.Friend)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::bnet::protocol::EntityId* id_;
  ::google::protobuf::RepeatedPtrField< ::bnet::protocol::attribute::Attribute > attribute_;
  friend void  protobuf_AddDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
  friend void protobuf_AssignDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
  friend void protobuf_ShutdownFile_service_2ffriends_2ffriends_5ftypes_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Friend* default_instance_;
};
// -------------------------------------------------------------------

class FriendInvitation : public ::google::protobuf::Message {
 public:
  FriendInvitation();
  virtual ~FriendInvitation();
  
  FriendInvitation(const FriendInvitation& from);
  
  inline FriendInvitation& operator=(const FriendInvitation& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const FriendInvitation& default_instance();
  
  void Swap(FriendInvitation* other);
  
  // implements Message ----------------------------------------------
  
  FriendInvitation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FriendInvitation& from);
  void MergeFrom(const FriendInvitation& from);
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
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional bool first_received = 1 [default = false];
  inline bool has_first_received() const;
  inline void clear_first_received();
  static const int kFirstReceivedFieldNumber = 1;
  inline bool first_received() const;
  inline void set_first_received(bool value);
  
  static const int kFriendInvitationFieldNumber = 103;
  static ::google::protobuf::internal::ExtensionIdentifier< ::bnet::protocol::invitation::Invitation,
      ::google::protobuf::internal::MessageTypeTraits< ::bnet::protocol::friends::FriendInvitation >, 11, false >
    friend_invitation;
  // @@protoc_insertion_point(class_scope:bnet.protocol.friends.FriendInvitation)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  bool first_received_;
  friend void  protobuf_AddDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
  friend void protobuf_AssignDesc_service_2ffriends_2ffriends_5ftypes_2eproto();
  friend void protobuf_ShutdownFile_service_2ffriends_2ffriends_5ftypes_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static FriendInvitation* default_instance_;
};
// ===================================================================


// ===================================================================

// Friend

// required .bnet.protocol.EntityId id = 1;
inline bool Friend::has_id() const {
  return _has_bit(0);
}
inline void Friend::clear_id() {
  if (id_ != NULL) id_->::bnet::protocol::EntityId::Clear();
  _clear_bit(0);
}
inline const ::bnet::protocol::EntityId& Friend::id() const {
  return id_ != NULL ? *id_ : *default_instance_->id_;
}
inline ::bnet::protocol::EntityId* Friend::mutable_id() {
  _set_bit(0);
  if (id_ == NULL) id_ = new ::bnet::protocol::EntityId;
  return id_;
}

// repeated .bnet.protocol.attribute.Attribute attribute = 2;
inline int Friend::attribute_size() const {
  return attribute_.size();
}
inline void Friend::clear_attribute() {
  attribute_.Clear();
}
inline const ::bnet::protocol::attribute::Attribute& Friend::attribute(int index) const {
  return attribute_.Get(index);
}
inline ::bnet::protocol::attribute::Attribute* Friend::mutable_attribute(int index) {
  return attribute_.Mutable(index);
}
inline ::bnet::protocol::attribute::Attribute* Friend::add_attribute() {
  return attribute_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::bnet::protocol::attribute::Attribute >&
Friend::attribute() const {
  return attribute_;
}
inline ::google::protobuf::RepeatedPtrField< ::bnet::protocol::attribute::Attribute >*
Friend::mutable_attribute() {
  return &attribute_;
}

// -------------------------------------------------------------------

// FriendInvitation

// optional bool first_received = 1 [default = false];
inline bool FriendInvitation::has_first_received() const {
  return _has_bit(0);
}
inline void FriendInvitation::clear_first_received() {
  first_received_ = false;
  _clear_bit(0);
}
inline bool FriendInvitation::first_received() const {
  return first_received_;
}
inline void FriendInvitation::set_first_received(bool value) {
  _set_bit(0);
  first_received_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace friends
}  // namespace protocol
}  // namespace bnet

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_service_2ffriends_2ffriends_5ftypes_2eproto__INCLUDED
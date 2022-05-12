// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: logproducerconfig.proto

#ifndef PROTOBUF_logproducerconfig_2eproto__INCLUDED
#define PROTOBUF_logproducerconfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace cls_config {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_logproducerconfig_2eproto();
void protobuf_AssignDesc_logproducerconfig_2eproto();
void protobuf_ShutdownFile_logproducerconfig_2eproto();

class LogProducerConfig;

// ===================================================================

class LogProducerConfig : public ::google::protobuf::Message {
 public:
  LogProducerConfig();
  virtual ~LogProducerConfig();

  LogProducerConfig(const LogProducerConfig& from);

  inline LogProducerConfig& operator=(const LogProducerConfig& from) {
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
  static const LogProducerConfig& default_instance();

  void Swap(LogProducerConfig* other);

  // implements Message ----------------------------------------------

  LogProducerConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LogProducerConfig& from);
  void MergeFrom(const LogProducerConfig& from);
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

  // optional uint64 TotalSizeLnBytes = 1 [default = 104857600];
  inline bool has_totalsizelnbytes() const;
  inline void clear_totalsizelnbytes();
  static const int kTotalSizeLnBytesFieldNumber = 1;
  inline ::google::protobuf::uint64 totalsizelnbytes() const;
  inline void set_totalsizelnbytes(::google::protobuf::uint64 value);

  // optional uint64 MaxSendWorkerCount = 2 [default = 50];
  inline bool has_maxsendworkercount() const;
  inline void clear_maxsendworkercount();
  static const int kMaxSendWorkerCountFieldNumber = 2;
  inline ::google::protobuf::uint64 maxsendworkercount() const;
  inline void set_maxsendworkercount(::google::protobuf::uint64 value);

  // optional uint64 MaxBlockSec = 3 [default = 60];
  inline bool has_maxblocksec() const;
  inline void clear_maxblocksec();
  static const int kMaxBlockSecFieldNumber = 3;
  inline ::google::protobuf::uint64 maxblocksec() const;
  inline void set_maxblocksec(::google::protobuf::uint64 value);

  // optional uint64 MaxBatchSize = 4 [default = 524288];
  inline bool has_maxbatchsize() const;
  inline void clear_maxbatchsize();
  static const int kMaxBatchSizeFieldNumber = 4;
  inline ::google::protobuf::uint64 maxbatchsize() const;
  inline void set_maxbatchsize(::google::protobuf::uint64 value);

  // optional uint64 LingerMs = 5 [default = 2000];
  inline bool has_lingerms() const;
  inline void clear_lingerms();
  static const int kLingerMsFieldNumber = 5;
  inline ::google::protobuf::uint64 lingerms() const;
  inline void set_lingerms(::google::protobuf::uint64 value);

  // optional uint64 Retries = 6 [default = 10];
  inline bool has_retries() const;
  inline void clear_retries();
  static const int kRetriesFieldNumber = 6;
  inline ::google::protobuf::uint64 retries() const;
  inline void set_retries(::google::protobuf::uint64 value);

  // optional uint64 BaseRetryBackoffMs = 7 [default = 100];
  inline bool has_baseretrybackoffms() const;
  inline void clear_baseretrybackoffms();
  static const int kBaseRetryBackoffMsFieldNumber = 7;
  inline ::google::protobuf::uint64 baseretrybackoffms() const;
  inline void set_baseretrybackoffms(::google::protobuf::uint64 value);

  // optional uint64 MaxRetryBackoffMs = 8 [default = 50000];
  inline bool has_maxretrybackoffms() const;
  inline void clear_maxretrybackoffms();
  static const int kMaxRetryBackoffMsFieldNumber = 8;
  inline ::google::protobuf::uint64 maxretrybackoffms() const;
  inline void set_maxretrybackoffms(::google::protobuf::uint64 value);

  // optional bool compressflag = 9 [default = true];
  inline bool has_compressflag() const;
  inline void clear_compressflag();
  static const int kCompressflagFieldNumber = 9;
  inline bool compressflag() const;
  inline void set_compressflag(bool value);

  // optional string source = 10;
  inline bool has_source() const;
  inline void clear_source();
  static const int kSourceFieldNumber = 10;
  inline const ::std::string& source() const;
  inline void set_source(const ::std::string& value);
  inline void set_source(const char* value);
  inline void set_source(const char* value, size_t size);
  inline ::std::string* mutable_source();
  inline ::std::string* release_source();
  inline void set_allocated_source(::std::string* source);

  // optional uint64 SockTimeout = 11 [default = 30];
  inline bool has_socktimeout() const;
  inline void clear_socktimeout();
  static const int kSockTimeoutFieldNumber = 11;
  inline ::google::protobuf::uint64 socktimeout() const;
  inline void set_socktimeout(::google::protobuf::uint64 value);

  // optional uint64 ConnectTimeout = 12 [default = 5];
  inline bool has_connecttimeout() const;
  inline void clear_connecttimeout();
  static const int kConnectTimeoutFieldNumber = 12;
  inline ::google::protobuf::uint64 connecttimeout() const;
  inline void set_connecttimeout(::google::protobuf::uint64 value);

  // required string Endpoint = 13;
  inline bool has_endpoint() const;
  inline void clear_endpoint();
  static const int kEndpointFieldNumber = 13;
  inline const ::std::string& endpoint() const;
  inline void set_endpoint(const ::std::string& value);
  inline void set_endpoint(const char* value);
  inline void set_endpoint(const char* value, size_t size);
  inline ::std::string* mutable_endpoint();
  inline ::std::string* release_endpoint();
  inline void set_allocated_endpoint(::std::string* endpoint);

  // required string AccesKeyId = 14;
  inline bool has_acceskeyid() const;
  inline void clear_acceskeyid();
  static const int kAccesKeyIdFieldNumber = 14;
  inline const ::std::string& acceskeyid() const;
  inline void set_acceskeyid(const ::std::string& value);
  inline void set_acceskeyid(const char* value);
  inline void set_acceskeyid(const char* value, size_t size);
  inline ::std::string* mutable_acceskeyid();
  inline ::std::string* release_acceskeyid();
  inline void set_allocated_acceskeyid(::std::string* acceskeyid);

  // required string AccessKeySecret = 15;
  inline bool has_accesskeysecret() const;
  inline void clear_accesskeysecret();
  static const int kAccessKeySecretFieldNumber = 15;
  inline const ::std::string& accesskeysecret() const;
  inline void set_accesskeysecret(const ::std::string& value);
  inline void set_accesskeysecret(const char* value);
  inline void set_accesskeysecret(const char* value, size_t size);
  inline ::std::string* mutable_accesskeysecret();
  inline ::std::string* release_accesskeysecret();
  inline void set_allocated_accesskeysecret(::std::string* accesskeysecret);

  // @@protoc_insertion_point(class_scope:cls_config.LogProducerConfig)
 private:
  inline void set_has_totalsizelnbytes();
  inline void clear_has_totalsizelnbytes();
  inline void set_has_maxsendworkercount();
  inline void clear_has_maxsendworkercount();
  inline void set_has_maxblocksec();
  inline void clear_has_maxblocksec();
  inline void set_has_maxbatchsize();
  inline void clear_has_maxbatchsize();
  inline void set_has_lingerms();
  inline void clear_has_lingerms();
  inline void set_has_retries();
  inline void clear_has_retries();
  inline void set_has_baseretrybackoffms();
  inline void clear_has_baseretrybackoffms();
  inline void set_has_maxretrybackoffms();
  inline void clear_has_maxretrybackoffms();
  inline void set_has_compressflag();
  inline void clear_has_compressflag();
  inline void set_has_source();
  inline void clear_has_source();
  inline void set_has_socktimeout();
  inline void clear_has_socktimeout();
  inline void set_has_connecttimeout();
  inline void clear_has_connecttimeout();
  inline void set_has_endpoint();
  inline void clear_has_endpoint();
  inline void set_has_acceskeyid();
  inline void clear_has_acceskeyid();
  inline void set_has_accesskeysecret();
  inline void clear_has_accesskeysecret();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 totalsizelnbytes_;
  ::google::protobuf::uint64 maxsendworkercount_;
  ::google::protobuf::uint64 maxblocksec_;
  ::google::protobuf::uint64 maxbatchsize_;
  ::google::protobuf::uint64 lingerms_;
  ::google::protobuf::uint64 retries_;
  ::google::protobuf::uint64 baseretrybackoffms_;
  ::google::protobuf::uint64 maxretrybackoffms_;
  ::std::string* source_;
  ::google::protobuf::uint64 socktimeout_;
  ::google::protobuf::uint64 connecttimeout_;
  ::std::string* endpoint_;
  ::std::string* acceskeyid_;
  ::std::string* accesskeysecret_;
  bool compressflag_;
  friend void  protobuf_AddDesc_logproducerconfig_2eproto();
  friend void protobuf_AssignDesc_logproducerconfig_2eproto();
  friend void protobuf_ShutdownFile_logproducerconfig_2eproto();

  void InitAsDefaultInstance();
  static LogProducerConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// LogProducerConfig

// optional uint64 TotalSizeLnBytes = 1 [default = 104857600];
inline bool LogProducerConfig::has_totalsizelnbytes() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LogProducerConfig::set_has_totalsizelnbytes() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LogProducerConfig::clear_has_totalsizelnbytes() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LogProducerConfig::clear_totalsizelnbytes() {
  totalsizelnbytes_ = GOOGLE_ULONGLONG(104857600);
  clear_has_totalsizelnbytes();
}
inline ::google::protobuf::uint64 LogProducerConfig::totalsizelnbytes() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.TotalSizeLnBytes)
  return totalsizelnbytes_;
}
inline void LogProducerConfig::set_totalsizelnbytes(::google::protobuf::uint64 value) {
  set_has_totalsizelnbytes();
  totalsizelnbytes_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.TotalSizeLnBytes)
}

// optional uint64 MaxSendWorkerCount = 2 [default = 50];
inline bool LogProducerConfig::has_maxsendworkercount() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LogProducerConfig::set_has_maxsendworkercount() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LogProducerConfig::clear_has_maxsendworkercount() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LogProducerConfig::clear_maxsendworkercount() {
  maxsendworkercount_ = GOOGLE_ULONGLONG(50);
  clear_has_maxsendworkercount();
}
inline ::google::protobuf::uint64 LogProducerConfig::maxsendworkercount() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.MaxSendWorkerCount)
  return maxsendworkercount_;
}
inline void LogProducerConfig::set_maxsendworkercount(::google::protobuf::uint64 value) {
  set_has_maxsendworkercount();
  maxsendworkercount_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.MaxSendWorkerCount)
}

// optional uint64 MaxBlockSec = 3 [default = 60];
inline bool LogProducerConfig::has_maxblocksec() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LogProducerConfig::set_has_maxblocksec() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LogProducerConfig::clear_has_maxblocksec() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LogProducerConfig::clear_maxblocksec() {
  maxblocksec_ = GOOGLE_ULONGLONG(60);
  clear_has_maxblocksec();
}
inline ::google::protobuf::uint64 LogProducerConfig::maxblocksec() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.MaxBlockSec)
  return maxblocksec_;
}
inline void LogProducerConfig::set_maxblocksec(::google::protobuf::uint64 value) {
  set_has_maxblocksec();
  maxblocksec_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.MaxBlockSec)
}

// optional uint64 MaxBatchSize = 4 [default = 524288];
inline bool LogProducerConfig::has_maxbatchsize() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void LogProducerConfig::set_has_maxbatchsize() {
  _has_bits_[0] |= 0x00000008u;
}
inline void LogProducerConfig::clear_has_maxbatchsize() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void LogProducerConfig::clear_maxbatchsize() {
  maxbatchsize_ = GOOGLE_ULONGLONG(524288);
  clear_has_maxbatchsize();
}
inline ::google::protobuf::uint64 LogProducerConfig::maxbatchsize() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.MaxBatchSize)
  return maxbatchsize_;
}
inline void LogProducerConfig::set_maxbatchsize(::google::protobuf::uint64 value) {
  set_has_maxbatchsize();
  maxbatchsize_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.MaxBatchSize)
}

// optional uint64 LingerMs = 5 [default = 2000];
inline bool LogProducerConfig::has_lingerms() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void LogProducerConfig::set_has_lingerms() {
  _has_bits_[0] |= 0x00000010u;
}
inline void LogProducerConfig::clear_has_lingerms() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void LogProducerConfig::clear_lingerms() {
  lingerms_ = GOOGLE_ULONGLONG(2000);
  clear_has_lingerms();
}
inline ::google::protobuf::uint64 LogProducerConfig::lingerms() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.LingerMs)
  return lingerms_;
}
inline void LogProducerConfig::set_lingerms(::google::protobuf::uint64 value) {
  set_has_lingerms();
  lingerms_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.LingerMs)
}

// optional uint64 Retries = 6 [default = 10];
inline bool LogProducerConfig::has_retries() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void LogProducerConfig::set_has_retries() {
  _has_bits_[0] |= 0x00000020u;
}
inline void LogProducerConfig::clear_has_retries() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void LogProducerConfig::clear_retries() {
  retries_ = GOOGLE_ULONGLONG(10);
  clear_has_retries();
}
inline ::google::protobuf::uint64 LogProducerConfig::retries() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.Retries)
  return retries_;
}
inline void LogProducerConfig::set_retries(::google::protobuf::uint64 value) {
  set_has_retries();
  retries_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.Retries)
}

// optional uint64 BaseRetryBackoffMs = 7 [default = 100];
inline bool LogProducerConfig::has_baseretrybackoffms() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void LogProducerConfig::set_has_baseretrybackoffms() {
  _has_bits_[0] |= 0x00000040u;
}
inline void LogProducerConfig::clear_has_baseretrybackoffms() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void LogProducerConfig::clear_baseretrybackoffms() {
  baseretrybackoffms_ = GOOGLE_ULONGLONG(100);
  clear_has_baseretrybackoffms();
}
inline ::google::protobuf::uint64 LogProducerConfig::baseretrybackoffms() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.BaseRetryBackoffMs)
  return baseretrybackoffms_;
}
inline void LogProducerConfig::set_baseretrybackoffms(::google::protobuf::uint64 value) {
  set_has_baseretrybackoffms();
  baseretrybackoffms_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.BaseRetryBackoffMs)
}

// optional uint64 MaxRetryBackoffMs = 8 [default = 50000];
inline bool LogProducerConfig::has_maxretrybackoffms() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void LogProducerConfig::set_has_maxretrybackoffms() {
  _has_bits_[0] |= 0x00000080u;
}
inline void LogProducerConfig::clear_has_maxretrybackoffms() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void LogProducerConfig::clear_maxretrybackoffms() {
  maxretrybackoffms_ = GOOGLE_ULONGLONG(50000);
  clear_has_maxretrybackoffms();
}
inline ::google::protobuf::uint64 LogProducerConfig::maxretrybackoffms() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.MaxRetryBackoffMs)
  return maxretrybackoffms_;
}
inline void LogProducerConfig::set_maxretrybackoffms(::google::protobuf::uint64 value) {
  set_has_maxretrybackoffms();
  maxretrybackoffms_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.MaxRetryBackoffMs)
}

// optional bool compressflag = 9 [default = true];
inline bool LogProducerConfig::has_compressflag() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void LogProducerConfig::set_has_compressflag() {
  _has_bits_[0] |= 0x00000100u;
}
inline void LogProducerConfig::clear_has_compressflag() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void LogProducerConfig::clear_compressflag() {
  compressflag_ = true;
  clear_has_compressflag();
}
inline bool LogProducerConfig::compressflag() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.compressflag)
  return compressflag_;
}
inline void LogProducerConfig::set_compressflag(bool value) {
  set_has_compressflag();
  compressflag_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.compressflag)
}

// optional string source = 10;
inline bool LogProducerConfig::has_source() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void LogProducerConfig::set_has_source() {
  _has_bits_[0] |= 0x00000200u;
}
inline void LogProducerConfig::clear_has_source() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void LogProducerConfig::clear_source() {
  if (source_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    source_->clear();
  }
  clear_has_source();
}
inline const ::std::string& LogProducerConfig::source() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.source)
  return *source_;
}
inline void LogProducerConfig::set_source(const ::std::string& value) {
  set_has_source();
  if (source_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    source_ = new ::std::string;
  }
  source_->assign(value);
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.source)
}
inline void LogProducerConfig::set_source(const char* value) {
  set_has_source();
  if (source_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    source_ = new ::std::string;
  }
  source_->assign(value);
  // @@protoc_insertion_point(field_set_char:cls_config.LogProducerConfig.source)
}
inline void LogProducerConfig::set_source(const char* value, size_t size) {
  set_has_source();
  if (source_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    source_ = new ::std::string;
  }
  source_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:cls_config.LogProducerConfig.source)
}
inline ::std::string* LogProducerConfig::mutable_source() {
  set_has_source();
  if (source_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    source_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:cls_config.LogProducerConfig.source)
  return source_;
}
inline ::std::string* LogProducerConfig::release_source() {
  clear_has_source();
  if (source_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = source_;
    source_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void LogProducerConfig::set_allocated_source(::std::string* source) {
  if (source_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete source_;
  }
  if (source) {
    set_has_source();
    source_ = source;
  } else {
    clear_has_source();
    source_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:cls_config.LogProducerConfig.source)
}

// optional uint64 SockTimeout = 11 [default = 30];
inline bool LogProducerConfig::has_socktimeout() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void LogProducerConfig::set_has_socktimeout() {
  _has_bits_[0] |= 0x00000400u;
}
inline void LogProducerConfig::clear_has_socktimeout() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void LogProducerConfig::clear_socktimeout() {
  socktimeout_ = GOOGLE_ULONGLONG(30);
  clear_has_socktimeout();
}
inline ::google::protobuf::uint64 LogProducerConfig::socktimeout() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.SockTimeout)
  return socktimeout_;
}
inline void LogProducerConfig::set_socktimeout(::google::protobuf::uint64 value) {
  set_has_socktimeout();
  socktimeout_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.SockTimeout)
}

// optional uint64 ConnectTimeout = 12 [default = 5];
inline bool LogProducerConfig::has_connecttimeout() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void LogProducerConfig::set_has_connecttimeout() {
  _has_bits_[0] |= 0x00000800u;
}
inline void LogProducerConfig::clear_has_connecttimeout() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void LogProducerConfig::clear_connecttimeout() {
  connecttimeout_ = GOOGLE_ULONGLONG(5);
  clear_has_connecttimeout();
}
inline ::google::protobuf::uint64 LogProducerConfig::connecttimeout() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.ConnectTimeout)
  return connecttimeout_;
}
inline void LogProducerConfig::set_connecttimeout(::google::protobuf::uint64 value) {
  set_has_connecttimeout();
  connecttimeout_ = value;
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.ConnectTimeout)
}

// required string Endpoint = 13;
inline bool LogProducerConfig::has_endpoint() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void LogProducerConfig::set_has_endpoint() {
  _has_bits_[0] |= 0x00001000u;
}
inline void LogProducerConfig::clear_has_endpoint() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void LogProducerConfig::clear_endpoint() {
  if (endpoint_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    endpoint_->clear();
  }
  clear_has_endpoint();
}
inline const ::std::string& LogProducerConfig::endpoint() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.Endpoint)
  return *endpoint_;
}
inline void LogProducerConfig::set_endpoint(const ::std::string& value) {
  set_has_endpoint();
  if (endpoint_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    endpoint_ = new ::std::string;
  }
  endpoint_->assign(value);
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.Endpoint)
}
inline void LogProducerConfig::set_endpoint(const char* value) {
  set_has_endpoint();
  if (endpoint_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    endpoint_ = new ::std::string;
  }
  endpoint_->assign(value);
  // @@protoc_insertion_point(field_set_char:cls_config.LogProducerConfig.Endpoint)
}
inline void LogProducerConfig::set_endpoint(const char* value, size_t size) {
  set_has_endpoint();
  if (endpoint_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    endpoint_ = new ::std::string;
  }
  endpoint_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:cls_config.LogProducerConfig.Endpoint)
}
inline ::std::string* LogProducerConfig::mutable_endpoint() {
  set_has_endpoint();
  if (endpoint_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    endpoint_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:cls_config.LogProducerConfig.Endpoint)
  return endpoint_;
}
inline ::std::string* LogProducerConfig::release_endpoint() {
  clear_has_endpoint();
  if (endpoint_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = endpoint_;
    endpoint_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void LogProducerConfig::set_allocated_endpoint(::std::string* endpoint) {
  if (endpoint_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete endpoint_;
  }
  if (endpoint) {
    set_has_endpoint();
    endpoint_ = endpoint;
  } else {
    clear_has_endpoint();
    endpoint_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:cls_config.LogProducerConfig.Endpoint)
}

// required string AccesKeyId = 14;
inline bool LogProducerConfig::has_acceskeyid() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void LogProducerConfig::set_has_acceskeyid() {
  _has_bits_[0] |= 0x00002000u;
}
inline void LogProducerConfig::clear_has_acceskeyid() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void LogProducerConfig::clear_acceskeyid() {
  if (acceskeyid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    acceskeyid_->clear();
  }
  clear_has_acceskeyid();
}
inline const ::std::string& LogProducerConfig::acceskeyid() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.AccesKeyId)
  return *acceskeyid_;
}
inline void LogProducerConfig::set_acceskeyid(const ::std::string& value) {
  set_has_acceskeyid();
  if (acceskeyid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    acceskeyid_ = new ::std::string;
  }
  acceskeyid_->assign(value);
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.AccesKeyId)
}
inline void LogProducerConfig::set_acceskeyid(const char* value) {
  set_has_acceskeyid();
  if (acceskeyid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    acceskeyid_ = new ::std::string;
  }
  acceskeyid_->assign(value);
  // @@protoc_insertion_point(field_set_char:cls_config.LogProducerConfig.AccesKeyId)
}
inline void LogProducerConfig::set_acceskeyid(const char* value, size_t size) {
  set_has_acceskeyid();
  if (acceskeyid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    acceskeyid_ = new ::std::string;
  }
  acceskeyid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:cls_config.LogProducerConfig.AccesKeyId)
}
inline ::std::string* LogProducerConfig::mutable_acceskeyid() {
  set_has_acceskeyid();
  if (acceskeyid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    acceskeyid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:cls_config.LogProducerConfig.AccesKeyId)
  return acceskeyid_;
}
inline ::std::string* LogProducerConfig::release_acceskeyid() {
  clear_has_acceskeyid();
  if (acceskeyid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = acceskeyid_;
    acceskeyid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void LogProducerConfig::set_allocated_acceskeyid(::std::string* acceskeyid) {
  if (acceskeyid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete acceskeyid_;
  }
  if (acceskeyid) {
    set_has_acceskeyid();
    acceskeyid_ = acceskeyid;
  } else {
    clear_has_acceskeyid();
    acceskeyid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:cls_config.LogProducerConfig.AccesKeyId)
}

// required string AccessKeySecret = 15;
inline bool LogProducerConfig::has_accesskeysecret() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void LogProducerConfig::set_has_accesskeysecret() {
  _has_bits_[0] |= 0x00004000u;
}
inline void LogProducerConfig::clear_has_accesskeysecret() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void LogProducerConfig::clear_accesskeysecret() {
  if (accesskeysecret_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesskeysecret_->clear();
  }
  clear_has_accesskeysecret();
}
inline const ::std::string& LogProducerConfig::accesskeysecret() const {
  // @@protoc_insertion_point(field_get:cls_config.LogProducerConfig.AccessKeySecret)
  return *accesskeysecret_;
}
inline void LogProducerConfig::set_accesskeysecret(const ::std::string& value) {
  set_has_accesskeysecret();
  if (accesskeysecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesskeysecret_ = new ::std::string;
  }
  accesskeysecret_->assign(value);
  // @@protoc_insertion_point(field_set:cls_config.LogProducerConfig.AccessKeySecret)
}
inline void LogProducerConfig::set_accesskeysecret(const char* value) {
  set_has_accesskeysecret();
  if (accesskeysecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesskeysecret_ = new ::std::string;
  }
  accesskeysecret_->assign(value);
  // @@protoc_insertion_point(field_set_char:cls_config.LogProducerConfig.AccessKeySecret)
}
inline void LogProducerConfig::set_accesskeysecret(const char* value, size_t size) {
  set_has_accesskeysecret();
  if (accesskeysecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesskeysecret_ = new ::std::string;
  }
  accesskeysecret_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:cls_config.LogProducerConfig.AccessKeySecret)
}
inline ::std::string* LogProducerConfig::mutable_accesskeysecret() {
  set_has_accesskeysecret();
  if (accesskeysecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesskeysecret_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:cls_config.LogProducerConfig.AccessKeySecret)
  return accesskeysecret_;
}
inline ::std::string* LogProducerConfig::release_accesskeysecret() {
  clear_has_accesskeysecret();
  if (accesskeysecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = accesskeysecret_;
    accesskeysecret_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void LogProducerConfig::set_allocated_accesskeysecret(::std::string* accesskeysecret) {
  if (accesskeysecret_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete accesskeysecret_;
  }
  if (accesskeysecret) {
    set_has_accesskeysecret();
    accesskeysecret_ = accesskeysecret;
  } else {
    clear_has_accesskeysecret();
    accesskeysecret_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:cls_config.LogProducerConfig.AccessKeySecret)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace cls_config

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_logproducerconfig_2eproto__INCLUDED
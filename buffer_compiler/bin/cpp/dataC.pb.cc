// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dataC.proto

#include "dataC.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace c {
constexpr IoTData::IoTData(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : mid_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , idur_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , iend_(int64_t{0})
  , pavg_(0)
  , ein_(0)
  , eout_(0){}
struct IoTDataDefaultTypeInternal {
  constexpr IoTDataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~IoTDataDefaultTypeInternal() {}
  union {
    IoTData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT IoTDataDefaultTypeInternal _IoTData_default_instance_;
constexpr EnclaveOutput::EnclaveOutput(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_()
  , enclave_output_hello_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct EnclaveOutputDefaultTypeInternal {
  constexpr EnclaveOutputDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~EnclaveOutputDefaultTypeInternal() {}
  union {
    EnclaveOutput _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT EnclaveOutputDefaultTypeInternal _EnclaveOutput_default_instance_;
}  // namespace c
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_dataC_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_dataC_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_dataC_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_dataC_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::c::IoTData, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::c::IoTData, mid_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, idur_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, iend_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, pavg_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, ein_),
  PROTOBUF_FIELD_OFFSET(::c::IoTData, eout_),
  0,
  1,
  2,
  3,
  4,
  5,
  PROTOBUF_FIELD_OFFSET(::c::EnclaveOutput, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::c::EnclaveOutput, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::c::EnclaveOutput, enclave_output_hello_),
  PROTOBUF_FIELD_OFFSET(::c::EnclaveOutput, data_),
  0,
  ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 11, sizeof(::c::IoTData)},
  { 17, 24, sizeof(::c::EnclaveOutput)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::c::_IoTData_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::c::_EnclaveOutput_default_instance_),
};

const char descriptor_table_protodef_dataC_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013dataC.proto\022\001c\"[\n\007IoTData\022\013\n\003MId\030\001 \001(\t"
  "\022\014\n\004IDur\030\002 \001(\t\022\014\n\004IEnd\030\003 \001(\003\022\014\n\004PAvg\030\004 \001"
  "(\001\022\013\n\003EIn\030\005 \001(\001\022\014\n\004EOut\030\006 \001(\001\"I\n\rEnclave"
  "Output\022\035\n\024enclave_output_hello\030\227\? \001(\t\022\031\n"
  "\004data\030\230\? \003(\0132\n.c.IoTData"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_dataC_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_dataC_2eproto = {
  false, false, 184, descriptor_table_protodef_dataC_2eproto, "dataC.proto", 
  &descriptor_table_dataC_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_dataC_2eproto::offsets,
  file_level_metadata_dataC_2eproto, file_level_enum_descriptors_dataC_2eproto, file_level_service_descriptors_dataC_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_dataC_2eproto_getter() {
  return &descriptor_table_dataC_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_dataC_2eproto(&descriptor_table_dataC_2eproto);
namespace c {

// ===================================================================

class IoTData::_Internal {
 public:
  using HasBits = decltype(std::declval<IoTData>()._has_bits_);
  static void set_has_mid(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_idur(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_iend(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_pavg(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_ein(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_eout(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
};

IoTData::IoTData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:c.IoTData)
}
IoTData::IoTData(const IoTData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  mid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_mid()) {
    mid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_mid(), 
      GetArenaForAllocation());
  }
  idur_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_idur()) {
    idur_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_idur(), 
      GetArenaForAllocation());
  }
  ::memcpy(&iend_, &from.iend_,
    static_cast<size_t>(reinterpret_cast<char*>(&eout_) -
    reinterpret_cast<char*>(&iend_)) + sizeof(eout_));
  // @@protoc_insertion_point(copy_constructor:c.IoTData)
}

inline void IoTData::SharedCtor() {
mid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
idur_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&iend_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&eout_) -
    reinterpret_cast<char*>(&iend_)) + sizeof(eout_));
}

IoTData::~IoTData() {
  // @@protoc_insertion_point(destructor:c.IoTData)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void IoTData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  mid_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  idur_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void IoTData::ArenaDtor(void* object) {
  IoTData* _this = reinterpret_cast< IoTData* >(object);
  (void)_this;
}
void IoTData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void IoTData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void IoTData::Clear() {
// @@protoc_insertion_point(message_clear_start:c.IoTData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      mid_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      idur_.ClearNonDefaultToEmpty();
    }
  }
  if (cached_has_bits & 0x0000003cu) {
    ::memset(&iend_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&eout_) -
        reinterpret_cast<char*>(&iend_)) + sizeof(eout_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* IoTData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional string MId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_mid();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "c.IoTData.MId");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string IDur = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_idur();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "c.IoTData.IDur");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional int64 IEnd = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_iend(&has_bits);
          iend_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional double PAvg = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 33)) {
          _Internal::set_has_pavg(&has_bits);
          pavg_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // optional double EIn = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 41)) {
          _Internal::set_has_ein(&has_bits);
          ein_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // optional double EOut = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 49)) {
          _Internal::set_has_eout(&has_bits);
          eout_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* IoTData::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:c.IoTData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string MId = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_mid().data(), static_cast<int>(this->_internal_mid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "c.IoTData.MId");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_mid(), target);
  }

  // optional string IDur = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_idur().data(), static_cast<int>(this->_internal_idur().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "c.IoTData.IDur");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_idur(), target);
  }

  // optional int64 IEnd = 3;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(3, this->_internal_iend(), target);
  }

  // optional double PAvg = 4;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(4, this->_internal_pavg(), target);
  }

  // optional double EIn = 5;
  if (cached_has_bits & 0x00000010u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(5, this->_internal_ein(), target);
  }

  // optional double EOut = 6;
  if (cached_has_bits & 0x00000020u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(6, this->_internal_eout(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:c.IoTData)
  return target;
}

size_t IoTData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:c.IoTData)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    // optional string MId = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_mid());
    }

    // optional string IDur = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_idur());
    }

    // optional int64 IEnd = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->_internal_iend());
    }

    // optional double PAvg = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 8;
    }

    // optional double EIn = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 + 8;
    }

    // optional double EOut = 6;
    if (cached_has_bits & 0x00000020u) {
      total_size += 1 + 8;
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData IoTData::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    IoTData::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*IoTData::GetClassData() const { return &_class_data_; }

void IoTData::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<IoTData *>(to)->MergeFrom(
      static_cast<const IoTData &>(from));
}


void IoTData::MergeFrom(const IoTData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:c.IoTData)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_mid(from._internal_mid());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_set_idur(from._internal_idur());
    }
    if (cached_has_bits & 0x00000004u) {
      iend_ = from.iend_;
    }
    if (cached_has_bits & 0x00000008u) {
      pavg_ = from.pavg_;
    }
    if (cached_has_bits & 0x00000010u) {
      ein_ = from.ein_;
    }
    if (cached_has_bits & 0x00000020u) {
      eout_ = from.eout_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void IoTData::CopyFrom(const IoTData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:c.IoTData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool IoTData::IsInitialized() const {
  return true;
}

void IoTData::InternalSwap(IoTData* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &mid_, GetArenaForAllocation(),
      &other->mid_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &idur_, GetArenaForAllocation(),
      &other->idur_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(IoTData, eout_)
      + sizeof(IoTData::eout_)
      - PROTOBUF_FIELD_OFFSET(IoTData, iend_)>(
          reinterpret_cast<char*>(&iend_),
          reinterpret_cast<char*>(&other->iend_));
}

::PROTOBUF_NAMESPACE_ID::Metadata IoTData::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_dataC_2eproto_getter, &descriptor_table_dataC_2eproto_once,
      file_level_metadata_dataC_2eproto[0]);
}

// ===================================================================

class EnclaveOutput::_Internal {
 public:
  using HasBits = decltype(std::declval<EnclaveOutput>()._has_bits_);
  static void set_has_enclave_output_hello(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

EnclaveOutput::EnclaveOutput(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  data_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:c.EnclaveOutput)
}
EnclaveOutput::EnclaveOutput(const EnclaveOutput& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      data_(from.data_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  enclave_output_hello_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_enclave_output_hello()) {
    enclave_output_hello_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_enclave_output_hello(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:c.EnclaveOutput)
}

inline void EnclaveOutput::SharedCtor() {
enclave_output_hello_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

EnclaveOutput::~EnclaveOutput() {
  // @@protoc_insertion_point(destructor:c.EnclaveOutput)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void EnclaveOutput::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  enclave_output_hello_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void EnclaveOutput::ArenaDtor(void* object) {
  EnclaveOutput* _this = reinterpret_cast< EnclaveOutput* >(object);
  (void)_this;
}
void EnclaveOutput::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void EnclaveOutput::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void EnclaveOutput::Clear() {
// @@protoc_insertion_point(message_clear_start:c.EnclaveOutput)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    enclave_output_hello_.ClearNonDefaultToEmpty();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* EnclaveOutput::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional string enclave_output_hello = 8087;
      case 8087:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 186)) {
          auto str = _internal_mutable_enclave_output_hello();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "c.EnclaveOutput.enclave_output_hello");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .c.IoTData data = 8088;
      case 8088:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 194)) {
          ptr = ctx->ParseMessage(_internal_add_data(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* EnclaveOutput::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:c.EnclaveOutput)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string enclave_output_hello = 8087;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_enclave_output_hello().data(), static_cast<int>(this->_internal_enclave_output_hello().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "c.EnclaveOutput.enclave_output_hello");
    target = stream->WriteStringMaybeAliased(
        8087, this->_internal_enclave_output_hello(), target);
  }

  // repeated .c.IoTData data = 8088;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_data_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(8088, this->_internal_data(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:c.EnclaveOutput)
  return target;
}

size_t EnclaveOutput::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:c.EnclaveOutput)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .c.IoTData data = 8088;
  total_size += 3UL * this->_internal_data_size();
  for (const auto& msg : this->data_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // optional string enclave_output_hello = 8087;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 3 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_enclave_output_hello());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData EnclaveOutput::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    EnclaveOutput::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*EnclaveOutput::GetClassData() const { return &_class_data_; }

void EnclaveOutput::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<EnclaveOutput *>(to)->MergeFrom(
      static_cast<const EnclaveOutput &>(from));
}


void EnclaveOutput::MergeFrom(const EnclaveOutput& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:c.EnclaveOutput)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  data_.MergeFrom(from.data_);
  if (from._internal_has_enclave_output_hello()) {
    _internal_set_enclave_output_hello(from._internal_enclave_output_hello());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void EnclaveOutput::CopyFrom(const EnclaveOutput& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:c.EnclaveOutput)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EnclaveOutput::IsInitialized() const {
  return true;
}

void EnclaveOutput::InternalSwap(EnclaveOutput* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  data_.InternalSwap(&other->data_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &enclave_output_hello_, GetArenaForAllocation(),
      &other->enclave_output_hello_, other->GetArenaForAllocation()
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata EnclaveOutput::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_dataC_2eproto_getter, &descriptor_table_dataC_2eproto_once,
      file_level_metadata_dataC_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace c
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::c::IoTData* Arena::CreateMaybeMessage< ::c::IoTData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::c::IoTData >(arena);
}
template<> PROTOBUF_NOINLINE ::c::EnclaveOutput* Arena::CreateMaybeMessage< ::c::EnclaveOutput >(Arena* arena) {
  return Arena::CreateMessageInternal< ::c::EnclaveOutput >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
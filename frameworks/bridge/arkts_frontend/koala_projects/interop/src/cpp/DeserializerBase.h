/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _DESERIALIZER_BASE_H_
#define _DESERIALIZER_BASE_H_

#include <stdint.h>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <charconv>

#include "interop-types.h"
#include "interop-logging.h"
#include "koala-types.h"

void holdManagedCallbackResource(InteropInt32);
void releaseManagedCallbackResource(InteropInt32);

#ifdef __arm__
#define KOALA_NO_UNALIGNED_ACCESS 1
#endif

inline const char *tagName(InteropTag tag)
{
  switch (tag)
  {
  case InteropTag::INTEROP_TAG_UNDEFINED:
    return "UNDEFINED";
  case InteropTag::INTEROP_TAG_INT32:
    return "INT32";
  case InteropTag::INTEROP_TAG_FLOAT32:
    return "FLOAT32";
  case InteropTag::INTEROP_TAG_LENGTH:
    return "LENGTH";
  case InteropTag::INTEROP_TAG_RESOURCE:
    return "RESOURCE";
  case InteropTag::INTEROP_TAG_STRING:
    return "STRING";
  case InteropTag::INTEROP_TAG_OBJECT:
    return "OBJECT";
  }
  INTEROP_FATAL("Fatal error");
}

inline const char *tagNameExact(InteropTag tag)
{
  switch (tag)
  {
  case InteropTag::INTEROP_TAG_UNDEFINED:
    return "INTEROP_TAG_UNDEFINED";
  case InteropTag::INTEROP_TAG_INT32:
    return "INTEROP_TAG_INT32";
  case InteropTag::INTEROP_TAG_FLOAT32:
    return "INTEROP_TAG_FLOAT32";
  case InteropTag::INTEROP_TAG_LENGTH:
    return "INTEROP_TAG_LENGTH";
  case InteropTag::INTEROP_TAG_RESOURCE:
    return "INTEROP_TAG_RESOURCE";
  case InteropTag::INTEROP_TAG_STRING:
    return "INTEROP_TAG_STRING";
  case InteropTag::INTEROP_TAG_OBJECT:
    return "INTEROP_TAG_OBJECT";
  }
  INTEROP_FATAL("Fatal error");
}

inline InteropFunction makeArkFunctionFromId(InteropInt32 id) {
  InteropFunction result;
  result.id = id;
  return result;
}

inline const char *getUnitName(int value)
{
  switch (value)
  {
  case 0:
    return "px";
  case 1:
    return "vp";
  case 2:
    return "fp";
  case 3:
    return "%";
  case 4:
    return "lpx";
  default:
    return "<unknown>";
  }
}

inline void parseDimension(const InteropString &string, InteropLength *result)
{
  char *suffixPtr = nullptr;
  float value = std::strtof(string.chars, &suffixPtr);

  if (!suffixPtr || suffixPtr == string.chars)
  {
    // not a numeric value
    result->unit = -1;
    return;
  }
  result->value = value;
  if (suffixPtr[0] == '\0' || (suffixPtr[0] == 'v' && suffixPtr[1] == 'p'))
  {
    result->unit = 1;
  }
  else if (suffixPtr[0] == '%')
  {
    result->unit = 3;
  }
  else if (suffixPtr[0] == 'p' && suffixPtr[1] == 'x')
  {
    result->unit = 0;
  }
  else if (suffixPtr[0] == 'l' && suffixPtr[1] == 'p' && suffixPtr[2] == 'x')
  {
    result->unit = 4;
  }
  else if (suffixPtr[0] == 'f' && suffixPtr[1] == 'p')
  {
    result->unit = 2;
  }
  else
  {
    result->unit = -1;
  }
}

template <typename T>
inline void convertor(T value) = delete;

// TODO: restore full printing!
template <typename T>
inline void WriteToString(std::string *result, T value) = delete;

template <>
inline void WriteToString(std::string *result, const InteropEmpty &value)
{
  result->append("{");
  result->append(".dummy=" + std::to_string(value.dummy));
  result->append("}");
}

struct Error
{
  std::string message;
  Error(const std::string &message) : message(message) {}
};

template <>
inline void WriteToString(std::string *result, InteropTag value)
{
  result->append(".tag=");
  result->append(tagName(value));
}

template <>
inline void WriteToString(std::string *result, InteropNativePointer value)
{
  result->append("0x" + std::to_string((uint64_t)value));
}

template <>
inline void WriteToString(std::string *result, InteropNodeHandle value)
{
  result->append("0x" + std::to_string((uint64_t)value));
}

template <>
inline void WriteToString(std::string *result, InteropFunction value)
{
  result->append("{");
  result->append(".id=" + std::to_string(value.id));
  result->append("}");
}

template <>
inline void WriteToString(std::string *result, const InteropFunction* value)
{
  result->append("{");
  result->append(".id=" + std::to_string(value->id));
  result->append("}");
}

template <>
inline void WriteToString(std::string *result, const InteropMaterialized *value)
{
  char hex[20];
  std::snprintf(hex, sizeof(hex), "0x%llx", (long long)value->ptr);
  result->append("\"");
  result->append("Materialized ");
  result->append(hex);
  result->append("\"");
}

// TODO: generate!
template<>
inline void WriteToString(std::string *result, const InteropCallbackResource *value)
{
  result->append("{");
  result->append(".resourceId=" + std::to_string(value->resourceId));
  result->append(", .hold=0");
  result->append(", .release=0");
  result->append("}");
}

class DeserializerBase;

template <>
inline void WriteToString(std::string *result, InteropUndefined value)
{
  result->append("{}");
}
template <>
inline void WriteToString(std::string *result, const InteropUndefined *value)
{
  result->append("{}");
}
template <>
inline void WriteToString(std::string *result, InteropVoid value)
{
  result->append("{}");
}
template <>
inline void WriteToString(std::string *result, const InteropVoid *value)
{
  result->append("{}");
}
template <>
inline void WriteToString(std::string *result, const InteropCustomObject *value)
{
  if (strcmp(value->kind, "NativeErrorFunction") == 0)
  {
    result->append("() => {} /* TBD: Function*/");
    return;
  }
  result->append("{");
  result->append(".kind=\"");
  result->append(value->kind);
  result->append("\"}");
}
template <>
inline void WriteToString(std::string *result, const InteropObject *value)
{
  result->append("{");
  result->append(".resource=");
  WriteToString(result, &(value->resource));
  result->append("}");
}
template <>
inline void WriteToString(std::string *result, const InteropObject value)
{
  WriteToString(result, &value);
}

struct CustomDeserializer
{
  virtual ~CustomDeserializer() {}
  virtual bool supports(const std::string &kind) { return false; }
  virtual InteropCustomObject deserialize(DeserializerBase *deserializer, const std::string &kind)
  {
    InteropCustomObject result;
    strcpy(result.kind, "error");
    return result;
  }
  CustomDeserializer *next = nullptr;
};

class DeserializerBase
{
protected:
  uint8_t *data;
  int32_t length;
  int32_t position;
  std::vector<void *> toClean;

  static CustomDeserializer *customDeserializers;

public:
  DeserializerBase(KSerializerBuffer data, int32_t length)
      : data(reinterpret_cast<uint8_t*>(data)), length(length), position(0) {}

  DeserializerBase(uint8_t* data, int32_t length)
      : data(data), length(length), position(0) {}

  ~DeserializerBase()
  {
    for (auto data : toClean)
    {
      free(data);
    }
  }

  static void registerCustomDeserializer(CustomDeserializer *deserializer)
  {
    if (DeserializerBase::customDeserializers == nullptr)
    {
      DeserializerBase::customDeserializers = deserializer;
    }
    else
    {
      auto *current = DeserializerBase::customDeserializers;
      while (current->next != nullptr)
        current = current->next;
      current->next = deserializer;
    }
  }

  template <typename T, typename E>
  void resizeArray(T *array, int32_t length)
  {
    void *value = nullptr;
    if (length > 0)
    {
      value = malloc(length * sizeof(E));
      if (value) {
        memset(value, 0, length * sizeof(E));
      }
      toClean.push_back(value);
    }
    array->length = length;
    array->array = reinterpret_cast<E *>(value);
  }

  template <typename T, typename K, typename V>
  void resizeMap(T *map, int32_t length)
  {
    void *keys = nullptr;
    void *values = nullptr;
    if (length > 0)
    {
      keys = malloc(length * sizeof(K));
      if (keys) {
          memset(keys, 0, length * sizeof(K));
      }
      toClean.push_back(keys);

      values = malloc(length * sizeof(V));
      if (values) {
          memset(values, 0, length * sizeof(V));
      }
      toClean.push_back(values);
    }
    map->size = length;
    map->keys = reinterpret_cast<K *>(keys);
    map->values = reinterpret_cast<V *>(values);
  }

  int32_t currentPosition() const { return this->position; }

  void check(int32_t count)
  {
    if (position + count > length) {
        fprintf(stderr, "Incorrect serialized data, check for %d, buffer %d position %d\n", count, length, position);
        assert(false);
        abort();
    }
  }

  InteropCustomObject readCustomObject(std::string kind)
  {
    auto *current = DeserializerBase::customDeserializers;
    while (current)
    {
      if (current->supports(kind))
        return current->deserialize(this, kind);
      current = current->next;
    }
    LOGE("Unsupported custom deserialization for %s\n", kind.c_str());
    auto tag = readTag();
    if (tag == INTEROP_TAG_UNDEFINED) LOGE("Undefined interop tag");
    // Skip undefined tag!.
    InteropCustomObject result;
    strcpy(result.kind, "Error");
    strcat(result.kind, kind.c_str());
    return result;
  }

  InteropCallbackResource readCallbackResource() {
    InteropCallbackResource result = {};
    result.resourceId = readInt32();
    result.hold = reinterpret_cast<void(*)(InteropInt32)>(readPointerOrDefault(reinterpret_cast<void*>(holdManagedCallbackResource)));
    result.release = reinterpret_cast<void(*)(InteropInt32)>(readPointerOrDefault(reinterpret_cast<void*>(releaseManagedCallbackResource)));
    return result;
  }

  InteropObject readObject() {
    InteropObject obj;
    obj.resource = readCallbackResource();
    return obj;
  }

  int8_t readInt8()
  {
    check(1);
    int8_t value = *(data + position);
    position += 1;
    return value;
  }
  InteropTag readTag()
  {
    return (InteropTag)readInt8();
  }
  InteropBoolean readBoolean()
  {
    check(1);
    int8_t value = *(data + position);
    position += 1;
    return value;
  }
  InteropInt32 readInt32()
  {
    check(4);
#ifdef KOALA_NO_UNALIGNED_ACCESS
    InteropInt32 value;
    memcpy(&value, data + position, 4);
#else
    auto value = *(InteropInt32 *)(data + position);
#endif
    position += 4;
    return value;
  }
  InteropInt64 readInt64()
  {
    check(8);
#ifdef KOALA_NO_UNALIGNED_ACCESS
    InteropInt64 value;
    memcpy(&value, data + position, 4);
#else
    auto value = *(InteropInt64 *)(data + position);
#endif
    position += 8;
    return value;
  }
  InteropUInt64 readUInt64()
  {
    check(8);
#ifdef KOALA_NO_UNALIGNED_ACCESS
    InteropInt64 value;
    memcpy(&value, data + position, 4);
#else
    auto value = *(InteropUInt64 *)(data + position);
#endif
    position += 8;
    return value;
  }
  InteropFloat32 readFloat32()
  {
    check(4);
#ifdef KOALA_NO_UNALIGNED_ACCESS
    InteropFloat32 value;
    memcpy(&value, data + position, 4);
#else
    auto value = *(InteropFloat32 *)(data + position);
#endif
    position += 4;
    return value;
  }
  InteropNativePointer readPointer()
  {
    check(8);
#ifdef KOALA_NO_UNALIGNED_ACCESS
    int64_t value = 0;
    memcpy(&value, data + position, 8);
#else
    int64_t value = *(int64_t *)(data + position);
#endif
    position += 8;
    return reinterpret_cast<InteropNativePointer>(static_cast<uintptr_t>(value));
  }
  InteropNativePointer readPointerOrDefault(InteropNativePointer defaultValue)
  {
    const InteropNativePointer value = this->readPointer();
    return value ? value : defaultValue;
  }
  InteropNumber readNumber()
  {
    check(5);
    InteropNumber result;
    result.tag = readTag();
    if (result.tag == InteropTag::INTEROP_TAG_INT32)
    {
      result.i32 = readInt32();
    }
    else if (result.tag == InteropTag::INTEROP_TAG_FLOAT32)
    {
      result.f32 = readFloat32();
    }
    else
    {
      INTEROP_FATAL("Fatal error");
    }
    return result;
  }
  InteropBuffer readBuffer()
  {
    InteropCallbackResource resource = readCallbackResource();
    InteropNativePointer data = readPointer();
    InteropInt64 length = readInt64();
    return InteropBuffer { resource, (void*)data, length };
  }

  // TODO: produce them with prefix in generator.
  InteropLength readLength()
  {
    InteropLength result = {};
    result.unit = 1;
    result.type = readInt8();
    switch (result.type)
    {
    case INTEROP_RUNTIME_OBJECT:
    {
      result.resource = readInt32();
      break;
    }
    case INTEROP_RUNTIME_STRING:
    {
      InteropString string = readString();
      parseDimension(string, &result);
      break;
    }
    case INTEROP_RUNTIME_NUMBER:
    {
      result.value = readFloat32();
      break;
    }
    default:
    {
      INTEROP_FATAL("Fatal error");
    }
    }
    return result;
  }

  InteropString readString()
  {
    InteropString result;
    InteropInt32 length = readInt32();
    check(length);
    // We refer to string data in-place.
    result.chars = (const char *)(data + position);
    result.length = length - 1;
    this->position += length;
    return result;
  }

  InteropFunction readFunction()
  {
    InteropFunction result;
    result.id = readInt32();
    return result;
  }

  InteropMaterialized readMaterialized()
  {
    InteropMaterialized result;
    result.ptr = readPointer();
    return result;
  }

  InteropUndefined readUndefined()
  {
    return InteropUndefined();
  }
};
template <>
inline void WriteToString(std::string *result, InteropBoolean value)
{
  result->append(value ? "true" : "false");
}
template <>
inline void WriteToString(std::string *result, InteropInt32 value)
{
  result->append(std::to_string(value));
}
template <>
inline void WriteToString(std::string *result, const InteropInt32* value)
{
  result->append(std::to_string(*value));
}
template <>
inline void WriteToString(std::string *result, InteropUInt64 value)
{
  result->append(std::to_string(value));
}
template <>
inline void WriteToString(std::string *result, InteropInt64 value)
{
  result->append(std::to_string(value));
}
template <>
inline void WriteToString(std::string *result, InteropUInt32 value)
{
  result->append(std::to_string(value));
}
template <>
inline void WriteToString(std::string *result, InteropFloat32 value)
{
#if (defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && (__MAC_OS_X_VERSION_MAX_ALLOWED < 130300L))
  // to_chars() is not available on older macOS.
  char buf[20];
  snprintf(buf, sizeof buf, "%f", value);
  result->append(buf);
#else
  std::string storage;
  storage.resize(20);
  // We use to_chars() to avoid locale issues.
  auto rc = std::to_chars(storage.data(), storage.data() + storage.size(), value);
  storage.resize(rc.ptr - storage.data());
  result->append(storage);
#endif
}
template <>
inline void WriteToString(std::string* result, const InteropBuffer* value) {
  result->append("{.data=nullptr, .length=");
  result->append(std::to_string(value->length));
  result->append("}");
}
template <>
inline void WriteToString(std::string* result, InteropBuffer value) {
  result->append("{.data=nullptr, .length=");
  result->append(std::to_string(value.length));
  result->append("}");
}
template <>
inline void WriteToString(std::string *result, const InteropString *value)
{
  result->append("{");
  if (value->chars) {
    result->append(".chars=\"");
    result->append(value->chars);
    result->append("\"");
  } else {
    result->append(".chars=\"\"");
  }
  result->append(", .length=");
  WriteToString(result, value->length);
  result->append("}");
}

template <>
inline void WriteToString(std::string *result, const InteropNumber *value)
{
  result->append("{.tag=" + std::to_string(value->tag) + ", ");

  if (value->tag == INTEROP_TAG_FLOAT32)
  {
    std::string valueString;
    result->append(".f32=");
    WriteToString(result, value->f32);
  } else {
    result->append(".i32=" + std::to_string(value->i32));
  }

  result->append("}");
}

template <>
inline void WriteToString(std::string *result, const InteropLength *value)
{
  result->append("{");
  result->append(".type=" + std::to_string(value->type));
  result->append(", .value=");
  WriteToString(result, value->value);
  result->append(", .unit=" + std::to_string(value->unit));
  result->append(", .resource=" + std::to_string(value->resource));
  result->append("}");
}

#endif // _DESERIALIZER_BASE_H_

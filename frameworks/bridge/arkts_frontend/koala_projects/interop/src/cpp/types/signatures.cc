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

#include "stdio.h"
#include <cstring>
#include <vector>

#include "signatures.h"
#include "interop-types.h"

// For types with the same name on ets and jni
#define KOALA_INTEROP_TYPEDEF(func, lang, CPP_TYPE, SIG_TYPE, CODE_TYPE) \
  if (std::strcmp(func, "sigType") == 0) if (type == CPP_TYPE) return SIG_TYPE; \
  if (std::strcmp(func, "codeType") == 0) if (type == CPP_TYPE) return CODE_TYPE;

// For types with distinct names on ets and jni
#define KOALA_INTEROP_TYPEDEF_LS(func, lang, CPP_TYPE, ETS_SIG_TYPE, ETS_CODE_TYPE, JNI_SIG_TYPE, JNI_CODE_TYPE) \
  if (std::strcmp(func, "sigType") == 0 && std::strcmp(lang, "ets") == 0) if (type == CPP_TYPE) return ETS_SIG_TYPE; \
  if (std::strcmp(func, "codeType") == 0 && std::strcmp(lang, "ets") == 0) if (type == CPP_TYPE) return ETS_CODE_TYPE; \
  if (std::strcmp(func, "sigType") == 0 && std::strcmp(lang, "jni") == 0) if (type == CPP_TYPE) return JNI_SIG_TYPE; \
  if (std::strcmp(func, "codeType") == 0 && std::strcmp(lang, "jni") == 0) if (type == CPP_TYPE) return JNI_CODE_TYPE;

#define KOALA_INTEROP_TYPEDEFS(func, lang) \
  KOALA_INTEROP_TYPEDEF(func, lang, "void", "V", "void") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KBoolean", "Z", "boolean") \
  KOALA_INTEROP_TYPEDEF(func, lang, "OH_Boolean", "Z", "boolean") \
  KOALA_INTEROP_TYPEDEF(func, lang, "Ark_Boolean", "Z", "boolean") \
  KOALA_INTEROP_TYPEDEF(func, lang, "int32_t", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "uint32_t", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "int", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KInt", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KUInt", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KLong", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "OH_Int32", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "OH_Int64", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "Ark_Int32", "I", "int") \
  KOALA_INTEROP_TYPEDEF(func, lang, "Ark_Int64", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KNativePointer", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KSerializerBuffer", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "Ark_NativePointer", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "OH_NativePointer", "J", "long") \
  KOALA_INTEROP_TYPEDEF(func, lang, "float", "F", "float") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KFloat", "F", "float") \
  KOALA_INTEROP_TYPEDEF(func, lang, "Ark_Float32", "F", "float") \
  KOALA_INTEROP_TYPEDEF(func, lang, "double", "D", "double") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KDouble", "D", "double") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KInteropNumber", "D", "double") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KVMObjectHandle", "Ljava/lang/Object;", "Object") \
  KOALA_INTEROP_TYPEDEF(func, lang, "uint8_t*", "[B", "byte[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KByte*", "[B", "byte[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KInteropBuffer", "[B", "byte[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KShort*", "[S", "short[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KUShort*", "[S", "short[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "int32_t*", "[I", "int[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KInt*", "[I", "int[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KNativePointerArray", "[J", "long[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KInteropReturnBuffer", "[B", "byte[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "float*", "[F", "float[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KFloatArray", "[F", "float[]") \
  KOALA_INTEROP_TYPEDEF(func, lang, "KFloat*", "[F", "float[]") \
  KOALA_INTEROP_TYPEDEF_LS(func, lang, "KStringPtr", "Lstd/core/String;", "String", "Ljava/lang/String;", "String") \
  KOALA_INTEROP_TYPEDEF_LS(func, lang, "KStringArray", "[Lstd/core/String;", "String[]", "[Ljava/lang/String;", "String[]") \
  KOALA_INTEROP_TYPEDEF_LS(func, lang, "KLength", "Lstd/core/String;", "String", "Ljava/lang/String;", "String")

std::string sigType(const std::string &type) {
#if KOALA_USE_PANDA_VM
    KOALA_INTEROP_TYPEDEFS("sigType", "ets")
#elif KOALA_USE_JAVA_VM
    KOALA_INTEROP_TYPEDEFS("sigType", "jni")
#endif
    INTEROP_FATAL("Unhandled type: %s\n", type.c_str());
    return type;
}

std::string codeType(const std::string &type) {
#if KOALA_USE_PANDA_VM
    KOALA_INTEROP_TYPEDEFS("codeType", "ets")
#elif KOALA_USE_JAVA_VM
    KOALA_INTEROP_TYPEDEFS("codeType", "jni")
#endif
    INTEROP_FATAL("Unhandled type: %s\n", type.c_str());
    return "";
}

std::string convertType(const char* name, const char* koalaType) {
    std::string result;
    size_t current = 0, last = 0;
    std::string input(koalaType);
    std::vector<std::string> tokens;
    while ((current = input.find('|', last)) != std::string::npos)
    {
        auto token = input.substr(last, current - last);
        tokens.push_back(token);
        last = current + 1;
    }
    tokens.push_back(input.substr(last, input.length() - last));

#if KOALA_USE_PANDA_VM

    for (int i = 1; i < (int)tokens.size(); i++)
    {
        result.append(sigType(tokens[i]));
    }
    result.append(":");
    result.append(sigType(tokens[0]));

#elif KOALA_USE_JAVA_VM

    result.append("(");
    for (int i = 1; i < (int)tokens.size(); i++)
    {
        result.append(sigType(tokens[i]));
    }
    result.append(")");
    result.append(sigType(tokens[0]));

#endif

#ifdef KOALA_BUILD_FOR_SIGNATURES
    #ifdef KOALA_USE_PANDA_VM
        std::string params;
        for (int i = 1; i < (int)tokens.size(); i++)
        {
            params.append("arg");
            params.append(std::to_string(i));
            params.append(": ");
            params.append(codeType(tokens[i]));
            if (i < (int)(tokens.size() - 1))
                params.append(", ");
        }
        fprintf(stderr, "  static native %s(%s): %s;\n", name, params.c_str(), codeType(tokens[0]).c_str());
    #elif KOALA_USE_JAVA_VM
        std::string params;
        for (int i = 1; i < (int)tokens.size(); i++)
        {
            params.append(codeType(tokens[i]));
            params.append(" arg");
            params.append(std::to_string(i));
            if (i < (int)(tokens.size() - 1))
                params.append(", ");
        }
        fprintf(stderr, "  public static native %s %s(%s);\n", codeType(tokens[0]).c_str(), name, params.c_str());
    #endif
#endif

    return result;
}

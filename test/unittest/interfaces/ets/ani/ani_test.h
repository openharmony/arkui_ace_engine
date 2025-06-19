/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ANI_H__
#define __ANI_H__

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#define ANI_VERSION_1 1
typedef size_t ani_size;
typedef int32_t ani_enum_item;
typedef int32_t ani_int;
typedef double ani_double;
typedef std::string ani_string;
typedef int32_t ani_namespace;
typedef struct {
    const char *name;
    const char *signature;
    const void *pointer;
} ani_native_function;

typedef enum {
    ANI_OK,
    ANI_ERROR,
} ani_status;

#define ANI_EXPORT __attribute__((visibility("default")))
typedef struct AniEnv {
    ani_status FindNamespace(const char *namespace_descriptor, ani_namespace *result)
    {
        return ANI_OK;
    }
    ani_status Namespace_BindNativeFunctions(ani_namespace ns, const ani_native_function *functions,
                                             ani_size nr_functions)
    {
        return ANI_OK;
    }
    ani_status EnumItem_GetValue_Int(ani_enum_item enum_item, ani_int *result)
    {
        return ANI_OK;
    }
    ani_status String_GetUTF8Size(ani_string string, ani_size *result)
    {
        return ANI_OK;
    }
    ani_status String_GetUTF8(ani_string string, char *utf8_buffer, ani_size utf8_buffer_size, ani_size *result)
    {
        return ANI_OK;
    }
} ani_env;
typedef struct AniVm {
    ani_status GetEnv(uint32_t version, ani_env **result)
    {
        return ANI_OK;
    }
} ani_vm;

#endif  // __ANI_H__

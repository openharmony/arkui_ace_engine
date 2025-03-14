/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <iostream>
#include <array>
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <string>
#include "frameworks/base/geometry/matrix4.h"

namespace {
class Matrix4_Obj {
    public:
    OHOS::Ace::Matrix4 matrix4x4;
};
} // namespace

static ani_object Matrix4_Identity([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object)
{
    static const char *className = "L@ohos/matrix4/matrix4;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        ani_object nullobj = nullptr;
        return nullobj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        std::cerr << "get ctor Failed'" << className << "'" << std::endl;
        ani_object nullobj = nullptr;
        return nullobj;
    }

    auto matrix4Object = new Matrix4_Obj();
    matrix4Object->matrix4x4 = OHOS::Ace::Matrix4::CreateIdentity();

    ani_object matrix4_object;
    if (ANI_OK != env->Object_New(cls, ctor, &matrix4_object, reinterpret_cast<ani_long>(matrix4Object))) {
        std::cerr << "New matrix4 object Fail" << std::endl;
        ani_object nullobj = nullptr;
        return nullobj;
    }
    return matrix4_object;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        std::cerr << "Unsupported ANI_VERSION_1" << std::endl;
        return ANI_ERROR;
    }

    static const char *className = "L@ohos/matrix4/matrix4;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"Matrix4_Identity", nullptr, reinterpret_cast<void *>(Matrix4_Identity)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
    std::cerr << "Cannot bind native methods to '" << className << "'" << std::endl;
        return ANI_ERROR;
    };

    *result = ANI_VERSION_1;
    return ANI_OK;
}
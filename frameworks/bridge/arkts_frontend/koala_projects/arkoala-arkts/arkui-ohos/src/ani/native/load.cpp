/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "load.h"

#include <dlfcn.h>

namespace OHOS::Ace::Ani {
namespace {
const char* LIBACE_MODULE = "libace_compatible.z.so";
} // namespace

using GetArkUIModifiersFunc = const ArkUIAniModifiers* (*)();

const ArkUIAniModifiers* GetNodeAniModifier()
{
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<GetArkUIModifiersFunc>(dlsym(handle, ARKUI_ANI_MODIFIER_FUNCTION_NAME));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }

    const auto* modifier = entry();
    return modifier;
}

} // namespace OHOS::Ace::Ani
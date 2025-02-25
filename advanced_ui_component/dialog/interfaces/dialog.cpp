/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/utils/macros.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_node_api.h"

extern const char _binary_dialog_abc_start[];
extern const char _binary_dialog_abc_end[];

extern const char _binary_dialog_v16_abc_start[];
extern const char _binary_dialog_v16_abc_end[];

namespace OHOS::Ace::Napi {

// Napi get abc code function
extern "C" ACE_FORCE_EXPORT void NAPI_arkui_advanced_Dialog_GetABCCode(
    const char** buf, int* buflen)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        if (buf != nullptr) {
            *buf = _binary_dialog_v16_abc_start;
        }
        if (buflen != nullptr) {
            *buflen = _binary_dialog_v16_abc_end - _binary_dialog_v16_abc_start;
        }
    } else {
        if (buf != nullptr) {
            *buf = _binary_dialog_abc_start;
        }
        if (buflen != nullptr) {
            *buflen = _binary_dialog_abc_end - _binary_dialog_abc_start;
        }
    }
}

/*
 * Module define
 */
static napi_module DialogModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_modname = "arkui.advanced.Dialog",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

/*
 * Module registerfunction
 */
extern "C" __attribute__((constructor)) void DialogRegisterModule(void)
{
    napi_module_register(&DialogModule);
}

} // namespace OHOS::Ace::Napi
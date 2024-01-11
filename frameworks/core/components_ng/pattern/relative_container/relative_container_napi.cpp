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

#include "core/components_ng/pattern/relative_container/relative_container_napi.h"

#include "base/utils/utils.h"
#include "core/components_ng/common_napi_utils/common_napi_utils.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"

extern const char _binary_arkui_relative_container_js_start[];
extern const char _binary_arkui_relative_container_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_arkui_relative_container_js_end[];
extern const char _binary_arkui_relative_container_abc_end[];
#else
extern const char* _binary_arkui_relative_container_js_end;
extern const char* _binary_arkui_relative_container_abc_end;
#endif

namespace OHOS::Ace {
namespace {
static constexpr const size_t MAX_ARG_NUM = 10;
static constexpr const int ARG_NUM_1 = 1;
} // namespace
napi_value Create(napi_env env, napi_callback_info info)
{
    NG::RelativeContainerModelNG::Create();
    return CommonNapiUtils::CreateNull(env);
}

napi_value Init(napi_env env, napi_value exports)
{
    static napi_property_descriptor desc[] = { DECLARE_NAPI_FUNCTION("create", Create) };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}
} // namespace OHOS::Ace

extern "C" __attribute__((visibility("default"))) void NAPI_arkui_relative_container_GetJSCode(
    const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_relative_container_js_start;
    }

    if (bufLen != nullptr) {
        *bufLen = _binary_arkui_relative_container_js_end - _binary_arkui_relative_container_js_start;
    }
}

// arkui_relative_container JS register
extern "C" __attribute__((visibility("default"))) void NAPI_arkui_relative_container_GetABCCode(
    const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_relative_container_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_relative_container_abc_end - _binary_arkui_relative_container_abc_start;
    }
}

static napi_module_with_js modules = {
    .nm_filename = "arkui/librelative_container.z.so/arkui_relative_container.js",
    .nm_version = 1,
    .nm_flags = 0,
    .nm_register_func = OHOS::Ace::Init,
    .nm_modname = "arkui.relativeContainer",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_arkui_relative_container_GetABCCode,
    .nm_get_js_code = NAPI_arkui_relative_container_GetJSCode,
};
extern "C" __attribute__((constructor)) void RegisterModule()
{
    napi_module_with_js_register(&modules);
}

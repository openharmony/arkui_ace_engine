/*
 * Copyright (c) 2022 Shenzhen Kaihong Digital Industry Development Co., Ltd.
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

#include <string>

#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
static napi_value JSRegisterFont(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    napi_value familyNameNApi = nullptr;
    napi_value familySrcNApi = nullptr;
    std::string familyName;
    std::string familySrc;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "familyName", &familyNameNApi);
        napi_get_named_property(env, argv, "familySrc", &familySrcNApi);
    } else {
        return nullptr;
    }
    napi_typeof(env, familyNameNApi, &valueType);
    if (valueType == napi_string) {
        size_t nameLen = 0;
        napi_get_value_string_utf8(env, familySrcNApi, nullptr, 0, &nameLen);
        std::unique_ptr<char[]> name = std::make_unique<char[]>(nameLen + 1);
        napi_get_value_string_utf8(env, familyNameNApi, name.get(), nameLen + 1, &nameLen);
        familyName = name.get();
    } else {
        LOGE("The parameter type of familyName is incorrect.");
        return nullptr;
    }

    napi_typeof(env, familySrcNApi, &valueType);
    if (valueType == napi_string) {
        size_t srcLen = 0;
        napi_get_value_string_utf8(env, familySrcNApi, nullptr, 0, &srcLen);
        std::unique_ptr<char[]> src = std::make_unique<char[]>(srcLen + 1);
        napi_get_value_string_utf8(env, familySrcNApi, src.get(), srcLen + 1, &srcLen);
        familySrc = src.get();
    } else {
        LOGE("The parameter type of familySrc is incorrect.");
        return nullptr;
    }

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        return nullptr;
    }
    delegate->RegisterFont(familyName, familySrc);
    return nullptr;
}

static napi_value FontExport(napi_env env, napi_value exports)
{
    napi_property_descriptor fontDesc[] = {
        DECLARE_NAPI_FUNCTION("registerFont", JSRegisterFont),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(fontDesc) / sizeof(fontDesc[0]), fontDesc));
    return exports;
}

static napi_module fontModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = FontExport,
    .nm_modname = "font",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void FontRegister()
{
    napi_module_register(&fontModule);
}
} // namespace OHOS::Ace::Napi

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


#include "interfaces/napi/kits/utils/napi_utils.h"

#include "core/common/ace_engine.h"
#include "frameworks/core/common/window_free_container.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {
static napi_value JSCreateContainerWithoutWindow(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    napi_value result = nullptr;

    napi_value thisVal = nullptr;
    std::size_t argc = 1;
    napi_value argv = nullptr;
    void *context = nullptr;

    napi_open_handle_scope(env, &scope);

    napi_get_cb_info(env, info, &argc, &argv, &thisVal, nullptr);
    if (argc != 1) {
        LOGE("Wrong arg count.");
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return result;
    }

#ifndef PREVIEW
    // There is no napi context in previewer, no need to check ..
    if (napi_unwrap(env, argv, &context) != napi_ok || !context) {
        NapiThrow(env, "Invalid parameter type of context.", ERROR_CODE_PARAM_INVALID);
        return result;
    }
#endif

    auto container = OHOS::Ace::Platform::WindowFreeContainer::CreateWindowFreeContainer(env, context);
    if (!container) {
        NapiThrow(env, "Create container without window failed.", ERROR_CODE_INTERNAL_ERROR);
        return result;
    }

    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, result);
    result = frontend->GetContextValue();

    napi_close_handle_scope(env, scope);
    return result;
}

static napi_value JSDestroyContainerWithoutWindow(napi_env, napi_callback_info info)
{
    napi_value result = nullptr;
    OHOS::Ace::Platform::WindowFreeContainer::DestroyWindowFreeContainer();

    return result;
}

static napi_value containerUtilsExport(napi_env env, napi_value exports)
{
    napi_property_descriptor containerUtilsDesc[] = {
        DECLARE_NAPI_FUNCTION("createContainerWithoutWindow", JSCreateContainerWithoutWindow),
        DECLARE_NAPI_FUNCTION("destroyContainerWithoutWindow", JSDestroyContainerWithoutWindow),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(containerUtilsDesc) / sizeof(containerUtilsDesc[0]),
        containerUtilsDesc));

    return exports;
}

static napi_module containerUtilsModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = containerUtilsExport,
    .nm_modname = "arkui.containerUtils",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ContainerUtilsRegister()
{
    napi_module_register(&containerUtilsModule);
}

} // namespace OHOS::Ace::Napi

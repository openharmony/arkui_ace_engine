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

#include "js_component_snapshot.h"

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_common.h"
#include "node_api_types.h"
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif

#include "node_api.h"

#include "bridge/common/utils/utils.h"
#include "core/common/ace_engine.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {
namespace {
struct SnapshotAsyncCtx {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    std::shared_ptr<Media::PixelMap> pixmap = nullptr;
    int32_t errCode = -1;
    int32_t instanceId = -1;
};

void OnComplete(SnapshotAsyncCtx* asyncCtx, std::function<void()> finishCallback)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        LOGW("container is null. %{public}d", asyncCtx->instanceId);
        if (finishCallback) {
            finishCallback();
        }
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGW("taskExecutor is null.");
        if (finishCallback) {
            finishCallback();
        }
        return;
    }
    taskExecutor->PostTask(
        [asyncCtx, finishCallback]() {
            std::unique_ptr<SnapshotAsyncCtx> ctx(asyncCtx);
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(ctx->env, &scope);

            // callback result format: [Error, PixelMap]
            napi_value result[JsComponentSnapshot::ARGC_MAX] = { nullptr };
            napi_get_undefined(ctx->env, &result[0]);
            napi_get_undefined(ctx->env, &result[1]);

            if (ctx->errCode == Framework::ERROR_CODE_NO_ERROR) {
#ifdef PIXEL_MAP_SUPPORTED
                // convert pixelMap to napi value
                result[1] = Media::PixelMapNapi::CreatePixelMap(ctx->env, ctx->pixmap);
#endif
            }
            napi_create_int32(ctx->env, ctx->errCode, &result[0]);

            if (ctx->deferred) {
                // promise
                if (ctx->errCode == Framework::ERROR_CODE_NO_ERROR) {
                    napi_resolve_deferred(ctx->env, ctx->deferred, result[1]);
                } else {
                    napi_reject_deferred(ctx->env, ctx->deferred, result[0]);
                }
            } else {
                // callback
                napi_value ret = nullptr;
                napi_value napiCallback = nullptr;
                napi_get_reference_value(ctx->env, ctx->callbackRef, &napiCallback);
                napi_call_function(ctx->env, nullptr, napiCallback, JsComponentSnapshot::ARGC_MAX, result, &ret);
                napi_delete_reference(ctx->env, ctx->callbackRef);
            }

            napi_close_handle_scope(ctx->env, scope);
            if (finishCallback) {
                finishCallback();
            }
        },
        TaskExecutor::TaskType::JS);
}
} // namespace

JsComponentSnapshot::JsComponentSnapshot(napi_env env, napi_callback_info info) : env_(env), argc_(ARGC_MAX)
{
    napi_value thisVar = nullptr;
    void* data = nullptr;

    // get arguments from JS
    napi_get_cb_info(env, info, &argc_, argv_, &thisVar, &data);
}

bool JsComponentSnapshot::CheckArgs(napi_valuetype firstArgType)

{
    size_t minArgc = 1;
    std::string errorMsg;
    if (argc_ < minArgc) {
        errorMsg = "The number of parameters must be greater than or equal to 1.";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, Framework::ERROR_CODE_PARAM_INVALID);

        return false;
    }
    if (argc_ > ARGC_MAX) {
        errorMsg = "The largest number of parameters is 2.";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, Framework::ERROR_CODE_PARAM_INVALID);
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[0], &type);
    if (type != firstArgType) {
        errorMsg = "parameter id is not of type string";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, Framework::ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (argc_ == ARGC_MAX) {
        napi_typeof(env_, argv_[1], &type);
        if (type != napi_function) {
            errorMsg = "parameter callback is not of type function";
            LOGE("%{public}s", errorMsg.c_str());
            NapiThrow(env_, errorMsg, Framework::ERROR_CODE_PARAM_INVALID);
            return false;
        }
    }
    return true;
}

auto JsComponentSnapshot::CreateCallback(napi_value* result)
{
    auto* asyncCtx = new SnapshotAsyncCtx;
    // parse JsCallback
    if (argc_ == ARGC_MAX) {
        napi_create_reference(env_, argv_[1], 1, &asyncCtx->callbackRef);
    }
    // init promise
    if (!asyncCtx->callbackRef) {
        napi_create_promise(env_, &asyncCtx->deferred, result);
    } else {
        napi_get_undefined(env_, result);
    }

    asyncCtx->env = env_;
    asyncCtx->instanceId = Container::CurrentId();

    return [asyncCtx](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode, std::function<void()> finishCallback) {
        asyncCtx->pixmap = std::move(pixmap);
        asyncCtx->errCode = errCode;
        OnComplete(asyncCtx, finishCallback);
    };
}

napi_value JsComponentSnapshot::GetArgv(int32_t idx)
{
    if (idx >= ARGC_MAX) {
        return nullptr;
    }
    return argv_[idx];
}

static napi_value JSSnapshotGet(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_value result = nullptr;

    if (!helper.CheckArgs(napi_valuetype::napi_string)) {
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // parse id
    std::string componentId;
    napi_valuetype valueType = napi_null;
    GetNapiString(env, helper.GetArgv(0), componentId, valueType);

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        NapiThrow(env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    delegate->GetSnapshot(componentId, helper.CreateCallback(&result));

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSSnapshotFromBuilder(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);
    if (!helper.CheckArgs(napi_valuetype::napi_function)) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        NapiThrow(env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    // create builder closure
    auto builder = [build = helper.GetArgv(0), env] { napi_call_function(env, nullptr, build, 0, nullptr, nullptr); };
    napi_value result = nullptr;
    delegate->CreateSnapshot(builder, helper.CreateCallback(&result), true);

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value ComponentSnapshotExport(napi_env env, napi_value exports)
{
    napi_property_descriptor snapshotDesc[] = {
        DECLARE_NAPI_FUNCTION("get", JSSnapshotGet),
        DECLARE_NAPI_FUNCTION("createFromBuilder", JSSnapshotFromBuilder),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(snapshotDesc) / sizeof(snapshotDesc[0]), snapshotDesc));

    return exports;
}

static napi_module snapshotModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = ComponentSnapshotExport,
    .nm_modname = "arkui.componentSnapshot",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ComponentSnapshotRegister()
{
    napi_module_register(&snapshotModule);
}
} // namespace OHOS::Ace::Napi

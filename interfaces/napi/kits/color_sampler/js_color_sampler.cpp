/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "js_color_sampler.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/render/adapter/color_sampler.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr uint64_t DEFAULT_INTERVAL_MS = 500;
constexpr uint64_t MIN_INTERVAL_MS = 180;
constexpr uint32_t DEFAULT_NOTIFY_THRESHOLD = 10;
constexpr uint32_t MIN_NOTIFY_THRESHOLD = 0;
constexpr uint32_t MAX_NOTIFY_THRESHOLD = 255;

constexpr uint32_t COLOR_CHANNEL_MASK = 0xFF;
constexpr uint32_t ALPHA_SHIFT = 24;
constexpr uint32_t RED_SHIFT = 16;
constexpr uint32_t GREEN_SHIFT = 8;

struct ColorPickerAsyncCtx {
    napi_env env = nullptr;
    napi_ref callbackRef = nullptr;
    uint32_t color = 0;
    int32_t errCode = -1;
    int32_t instanceId = -1;
};

// Key format: "instanceId:componentId"
// Map to track active color picker contexts by instanceId and componentId
// No mutex needed - JS is single-threaded
std::unordered_map<std::string, std::shared_ptr<ColorPickerAsyncCtx>> g_ctxs;

std::string MakeContextKey(int32_t instanceId, const std::string& componentId)
{
    return std::to_string(instanceId) + ":" + componentId;
}

napi_value CreateJsNumber(napi_env env, uint32_t value)
{
    napi_value result = nullptr;
    napi_create_uint32(env, value, &result);
    return result;
}

void OnColorPickerComplete(std::shared_ptr<ColorPickerAsyncCtx> asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        LOGW("container is null. %{public}d", asyncCtx->instanceId);
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGW("taskExecutor is null.");
        return;
    }
    std::weak_ptr<ColorPickerAsyncCtx> weakCtx = asyncCtx;
    taskExecutor->PostTask(
        [weakCtx]() {
            auto ctx = weakCtx.lock();
            if (!ctx) {
                return;
            }
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(ctx->env, &scope);

            // callback result format: [Error, Color]
            napi_value result[2] = { nullptr };
            napi_get_undefined(ctx->env, &result[0]);
            napi_get_undefined(ctx->env, &result[1]);

            if (ctx->errCode == ERROR_CODE_NO_ERROR) {
                // create a JS object for color components { alpha, red, green, blue }
                napi_value colorObj = nullptr;
                napi_status status = napi_create_object(ctx->env, &colorObj);
                if (status == napi_ok && colorObj != nullptr) {
                    uint32_t color = ctx->color;
                    uint32_t alpha = (color >> ALPHA_SHIFT) & COLOR_CHANNEL_MASK;
                    uint32_t red = (color >> RED_SHIFT) & COLOR_CHANNEL_MASK;
                    uint32_t green = (color >> GREEN_SHIFT) & COLOR_CHANNEL_MASK;
                    uint32_t blue = color & COLOR_CHANNEL_MASK;
                    napi_set_named_property(ctx->env, colorObj, "alpha", CreateJsNumber(ctx->env, alpha));
                    napi_set_named_property(ctx->env, colorObj, "red", CreateJsNumber(ctx->env, red));
                    napi_set_named_property(ctx->env, colorObj, "green", CreateJsNumber(ctx->env, green));
                    napi_set_named_property(ctx->env, colorObj, "blue", CreateJsNumber(ctx->env, blue));
                    result[1] = colorObj;
                }
            }

            napi_create_int32(ctx->env, ctx->errCode, &result[0]);

            if (ctx->callbackRef) {
                napi_value ret = nullptr;
                napi_value napiCallback = nullptr;
                napi_get_reference_value(ctx->env, ctx->callbackRef, &napiCallback);
                napi_call_function(ctx->env, nullptr, napiCallback, 2, result, &ret);
                // Don't delete the reference - it will be deleted on unregister
            }

            napi_close_handle_scope(ctx->env, scope);
        },
        TaskExecutor::TaskType::JS, "ArkUIColorPickerComplete");
}
} // namespace

JsColorSampler::JsColorSampler(napi_env env, napi_callback_info info) : env_(env), argc_(ARGC_MAX)
{
    napi_value thisVar = nullptr;
    void* data = nullptr;

    // get arguments from JS
    napi_get_cb_info(env, info, &argc_, argv_, &thisVar, &data);
}

bool JsColorSampler::CheckArgs(napi_valuetype firstArgType, size_t minArgc)
{
    std::string errorMsg;
    if (argc_ < minArgc) {
        errorMsg = "The number of parameters must be greater than or equal to " + std::to_string(minArgc) + ".";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (argc_ > ARGC_MAX) {
        errorMsg = "The largest number of parameters is " + std::to_string(ARGC_MAX) + ".";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[0], &type);
    if (type != firstArgType) {
        errorMsg = "parameter node is not of correct type";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return true;
}

napi_value JsColorSampler::GetArgv(int32_t idx)
{
    if (idx >= ARGC_MAX) {
        return nullptr;
    }
    return argv_[idx];
}

bool JsColorSampler::ParseInterval(int32_t idx, uint64_t& interval)
{
    if (static_cast<int32_t>(argc_) <= idx) {
        return false;
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[idx], &type);
    if (type != napi_number) {
        return false;
    }

    int64_t value = 0;
    napi_get_value_int64(env_, argv_[idx], &value);
    if (value < 0) {
        return false;
    }
    interval = static_cast<uint64_t>(value);
    return true;
}

bool JsColorSampler::ParseColorPickOptions(int32_t idx, uint64_t& interval, uint32_t& notifyThreshold)
{
    // Set defaults
    interval = DEFAULT_INTERVAL_MS;
    notifyThreshold = DEFAULT_NOTIFY_THRESHOLD;

    if (static_cast<int32_t>(argc_) <= idx) {
        return true; // Options are optional, use defaults
    }

    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[idx], &type);
    if (type == napi_undefined || type == napi_null) {
        return true; // Use defaults
    }

    if (type != napi_object) {
        return false; // Invalid type
    }

    napi_value options = argv_[idx];

    // Parse interval
    napi_value intervalValue = nullptr;
    napi_get_named_property(env_, options, "interval", &intervalValue);
    if (intervalValue != nullptr) {
        napi_valuetype intervalType = napi_undefined;
        napi_typeof(env_, intervalValue, &intervalType);
        if (intervalType == napi_number) {
            int64_t value = 0;
            napi_get_value_int64(env_, intervalValue, &value);
            if (value >= static_cast<int64_t>(MIN_INTERVAL_MS)) {
                interval = static_cast<uint64_t>(value);
            }
        }
    }

    // Parse notifyThreshold
    napi_value thresholdValue = nullptr;
    napi_get_named_property(env_, options, "notifyThreshold", &thresholdValue);
    if (thresholdValue != nullptr) {
        napi_valuetype thresholdType = napi_undefined;
        napi_typeof(env_, thresholdValue, &thresholdType);
        if (thresholdType == napi_number) {
            int32_t value = 0;
            napi_get_value_int32(env_, thresholdValue, &value);
            if (value >= static_cast<int32_t>(MIN_NOTIFY_THRESHOLD) &&
                value <= static_cast<int32_t>(MAX_NOTIFY_THRESHOLD)) {
                notifyThreshold = static_cast<uint32_t>(value);
            }
        }
    }

    return true;
}

auto JsColorSampler::CreateCallback(const std::string& componentId, napi_ref* callbackRef, int32_t instanceId)
{
    auto asyncCtx = std::make_shared<ColorPickerAsyncCtx>();
    asyncCtx->env = env_;
    asyncCtx->instanceId = instanceId;
    asyncCtx->callbackRef = *callbackRef;

    // Store the context for cleanup on unregister
    // No mutex needed - JS is single-threaded
    std::string contextKey = MakeContextKey(instanceId, componentId);
    if (g_ctxs[contextKey] != nullptr) {
        TAG_LOGD(AceLogTag::ACE_COLOR_SAMPLER,
            "Overwriting existing ColorPicker context for instanceId: %{public}d, componentId: %{public}s", instanceId,
            componentId.c_str());
        napi_delete_reference(g_ctxs[contextKey]->env, g_ctxs[contextKey]->callbackRef);
    }
    g_ctxs[contextKey] = asyncCtx;
    std::weak_ptr<ColorPickerAsyncCtx> weakCtx = asyncCtx;
    return [weakCtx](uint32_t color, int32_t errCode) {
        auto asyncCtx = weakCtx.lock();
        if (!asyncCtx) {
            return;
        }
        asyncCtx->color = color;
        asyncCtx->errCode = errCode;
        OnColorPickerComplete(asyncCtx);
    };
}

static napi_value JSColorSamplerRegister(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsColorSampler helper(env, info);

    napi_value result = nullptr;
    napi_get_undefined(env, &result);

    constexpr size_t MIN_ARGC = 3;
    if (!helper.CheckArgs(napi_valuetype::napi_object, MIN_ARGC)) {
        TAG_LOGW(AceLogTag::ACE_COLOR_SAMPLER, "Parsing the first argument failed, not of object type.");
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // Parse UIContext from first argument and extract instanceId
    int32_t instanceId = GetUIContextInstanceId(env, helper.GetArgv(0));
    if (instanceId <= 0) {
        NapiThrow(env, "Invalid UIContext", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // Parse nodeId from second argument
    std::string componentId;
    napi_valuetype valueType = napi_null;
    GetNapiString(env, helper.GetArgv(1), componentId, valueType);

    // Parse callback from third argument (required)
    napi_ref callbackRef = nullptr;
    if (helper.GetArgv(2) != nullptr) {
        napi_valuetype type = napi_undefined;
        napi_typeof(env, helper.GetArgv(2), &type);
        if (type == napi_function) {
            napi_create_reference(env, helper.GetArgv(2), 1, &callbackRef);
        }
    }

    if (!callbackRef) {
        NapiThrow(env, "Callback is required", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // Parse options from fourth argument (optional)
    uint64_t interval = DEFAULT_INTERVAL_MS;
    uint32_t notifyThreshold = DEFAULT_NOTIFY_THRESHOLD;
    if (!helper.ParseColorPickOptions(3, interval, notifyThreshold)) {
        NapiThrow(env, "Invalid options parameter", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    ContainerScope instanceScope(instanceId);

    bool success = NG::ColorSampler::RegisterColorSampler(
        componentId, interval, helper.CreateCallback(componentId, &callbackRef, instanceId), notifyThreshold);
    if (!success) {
        NapiThrow(env, "Failed to register color sampler", ERROR_CODE_INTERNAL_ERROR);
    }

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSColorSamplerUnregister(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsColorSampler helper(env, info);

    napi_value result = nullptr;
    napi_get_undefined(env, &result);

    if (!helper.CheckArgs(napi_valuetype::napi_object, 2)) {
        TAG_LOGW(AceLogTag::ACE_COLOR_SAMPLER, "Parsing the first argument failed, not of object type.");
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // Parse UIContext from first argument and extract instanceId
    int32_t instanceId = GetUIContextInstanceId(env, helper.GetArgv(0));
    if (instanceId <= 0) {
        NapiThrow(env, "Invalid UIContext", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    ContainerScope instanceScope(instanceId);

    // Parse nodeId from second argument
    std::string componentId;
    napi_valuetype valueType = napi_null;
    GetNapiString(env, helper.GetArgv(1), componentId, valueType);

    bool success = NG::ColorSampler::UnregisterColorSampler(componentId);

    // Clean up the stored context
    if (success) {
        std::string contextKey = MakeContextKey(instanceId, componentId);
        auto it = g_ctxs.find(contextKey);
        if (it != g_ctxs.end()) {
            auto asyncCtx = it->second;
            if (asyncCtx && asyncCtx->callbackRef) {
                napi_delete_reference(asyncCtx->env, asyncCtx->callbackRef);
            }
            g_ctxs.erase(it);
        }
    } else {
        NapiThrow(env, "Failed to unregister color picker", ERROR_CODE_INTERNAL_ERROR);
    }

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value ColorSamplerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor colorSamplerDesc[] = {
        DECLARE_NAPI_FUNCTION("register", JSColorSamplerRegister),
        DECLARE_NAPI_FUNCTION("unregister", JSColorSamplerUnregister),
    };
    NAPI_CALL(env,
        napi_define_properties(env, exports, sizeof(colorSamplerDesc) / sizeof(colorSamplerDesc[0]), colorSamplerDesc));

    return exports;
}

static napi_module colorSamplerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = ColorSamplerExport,
    .nm_modname = "arkui.colorSampler",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ColorSamplerRegister()
{
    napi_module_register(&colorSamplerModule);
}
} // namespace OHOS::Ace::Napi

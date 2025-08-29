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
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif

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
constexpr int32_t GETWITHRANGE_ISSTARTRECT_NUMBER = 2;
constexpr int32_t GETWITHRANGE_ARGV_VALUE = 4;
constexpr int32_t GETWITHRANGE_OPTIONS_NUMBER = 3;

void OnComplete(SnapshotAsyncCtx* asyncCtx, std::function<void()> finishCallback)
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
    taskExecutor->PostTask(
        [asyncCtx, finishCallback]() {
            std::unique_ptr<SnapshotAsyncCtx> ctx(asyncCtx);
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(ctx->env, &scope);

            // callback result format: [Error, PixelMap]
            napi_value result[2] = { nullptr };
            napi_get_undefined(ctx->env, &result[0]);
            napi_get_undefined(ctx->env, &result[1]);

            if (ctx->errCode == ERROR_CODE_NO_ERROR) {
#ifdef PIXEL_MAP_SUPPORTED
                // convert pixelMap to napi value
                result[1] = Media::PixelMapNapi::CreatePixelMap(ctx->env, ctx->pixmap);
#endif
            }
            napi_create_int32(ctx->env, ctx->errCode, &result[0]);

            if (ctx->deferred) {
                // promise
                if (ctx->errCode == ERROR_CODE_NO_ERROR) {
                    napi_resolve_deferred(ctx->env, ctx->deferred, result[1]);
                } else {
                    napi_reject_deferred(ctx->env, ctx->deferred, result[0]);
                }
            } else {
                // callback
                napi_value ret = nullptr;
                napi_value napiCallback = nullptr;
                napi_get_reference_value(ctx->env, ctx->callbackRef, &napiCallback);
                napi_call_function(ctx->env, nullptr, napiCallback, 2, result, &ret);
                napi_delete_reference(ctx->env, ctx->callbackRef);
            }

            napi_close_handle_scope(ctx->env, scope);
            if (finishCallback) {
                finishCallback();
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIComponentSnapshotComplete");
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
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);

        return false;
    }
    if (argc_ > ARGC_MAX) {
        errorMsg = "The largest number of parameters is 2.";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[0], &type);
    if (type != firstArgType) {
        errorMsg = "parameter id is not of type string";
        LOGE("%{public}s", errorMsg.c_str());
        NapiThrow(env_, errorMsg, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return true;
}

auto JsComponentSnapshot::CreateCallback(napi_value* result)
{
    auto* asyncCtx = new SnapshotAsyncCtx;
    napi_valuetype type = napi_undefined;
    // parse JsCallback
    if (argc_ >= 2) {
        napi_typeof(env_, argv_[1], &type);
        if (type == napi_function) {
            napi_create_reference(env_, argv_[1], 1, &asyncCtx->callbackRef);
        }
    }
    // init promise
    if (!asyncCtx->callbackRef) {
        napi_create_promise(env_, &asyncCtx->deferred, result);
    } else {
        napi_get_undefined(env_, result);
    }

    asyncCtx->env = env_;
    asyncCtx->instanceId = Container::CurrentIdSafely();

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

void JsComponentSnapshot::ParseParamForBuilder(NG::SnapshotParam& param)
{
    // parse second param for builder interface
    if (argc_ >= 2) {
        napi_valuetype type = napi_undefined;
        napi_typeof(env_, argv_[1], &type);
        if (type != napi_function) {
            ParseParam(1, param);
        }
    }
    // parse third param for builder interface
    if (argc_ >= 3) {
        ParseParam(2, param);
    }
    // parse fourth param for builder interface
    if (argc_ >= 4) {
        ParseParam(3, param);
    }
    // parse fifth param for builder interface
    if (argc_ == 5) {
        ParseParam(4, param);
    }
}

void JsComponentSnapshot::ParseParamForGet(NG::SnapshotOptions& options)
{
    // parse options param for Promise
    if (argc_ >= 2) {
        napi_valuetype type = napi_undefined;
        napi_typeof(env_, argv_[1], &type);
        if (type != napi_function) {
            ParseOptions(1, options);
        }
    }
    // parse options param for Callback
    if (argc_ == 3) {
        ParseOptions(2, options);
    }
    if (argc_ == GETWITHRANGE_ARGV_VALUE) {
        ParseOptions(GETWITHRANGE_OPTIONS_NUMBER, options);
    }
}

void JsComponentSnapshot::ParseParam(int32_t idx, NG::SnapshotParam& param)
{
    if (static_cast<int32_t>(argc_) <= idx) {
        return;
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[idx], &type);
    // parse delay param
    if (type == napi_number) {
        int32_t delayTime = 0;
        napi_get_value_int32(env_, argv_[idx], &delayTime);
        if (delayTime >= 0) {
            param.delay = delayTime;
        }
    }
    // parse checkImageStatus param
    if (type == napi_boolean) {
        bool checkImageStatus = 0;
        napi_get_value_bool(env_, argv_[idx], &checkImageStatus);
        param.checkImageStatus = checkImageStatus;
    }
    // parse SnapshotOptions param
    if (type == napi_object) {
        NG::SnapshotOptions options;
        ParseOptions(idx, options);
        param.options = options;
    }
}

void JsComponentSnapshot::ParseOptions(int32_t idx, NG::SnapshotOptions& options)
{
    if (static_cast<int32_t>(argc_) <= idx) {
        return;
    }
    napi_valuetype type = napi_undefined;
    napi_typeof(env_, argv_[idx], &type);
    if (type != napi_object) {
        return;
    }

    bool result = false;
    napi_has_named_property(env_, argv_[idx], "scale", &result);
    if (result) {
        napi_value scaleNapi = nullptr;
        napi_get_named_property(env_, argv_[idx], "scale", &scaleNapi);
        double scale = 0.0;
        napi_get_value_double(env_, scaleNapi, &scale);
        if (GreatNotEqual(scale, 0.0)) {
            options.scale = static_cast<float>(scale);
        }
    }

    result = false;
    napi_has_named_property(env_, argv_[idx], "waitUntilRenderFinished", &result);
    if (result) {
        napi_value waitUntilRenderFinishedNapi = nullptr;
        napi_get_named_property(env_, argv_[idx], "waitUntilRenderFinished", &waitUntilRenderFinishedNapi);
        bool waitUntilRenderFinished = false;
        napi_get_value_bool(env_, waitUntilRenderFinishedNapi, &waitUntilRenderFinished);
        options.waitUntilRenderFinished = waitUntilRenderFinished;
    }

    result = false;
    napi_has_named_property(env_, argv_[idx], "region", &result);
    if (!result) {
        options.regionMode = NG::SnapshotRegionMode::NO_REGION;
        return;
    }
    napi_value regionObject = nullptr;
    napi_get_named_property(env_, argv_[idx], "region", &regionObject);
    if (!regionObject) {
        options.regionMode = NG::SnapshotRegionMode::NO_REGION;
        return;
    }

    options.regionMode = NG::SnapshotRegionMode::COMMON;
    if (ParseLocalizedRegion(&regionObject, options)) {
        options.regionMode = NG::SnapshotRegionMode::LOCALIZED;
    } else {
        ParseRegion(&regionObject, options);
    }
}

bool JsComponentSnapshot::ParseRegion(napi_value* regionObject, NG::SnapshotOptions& options)
{
    bool getReigonResult = false;
    options.snapshotRegion = NG::LocalizedSnapshotRegion {};
    napi_has_named_property(env_, *regionObject, "left", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"left\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value leftPxNapi;
    napi_get_named_property(env_, *regionObject, "left", &leftPxNapi);
    napi_get_value_double(env_, leftPxNapi, &options.snapshotRegion.start);

    napi_has_named_property(env_, *regionObject, "right", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"right\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value rightPxNapi;
    napi_get_named_property(env_, *regionObject, "right", &rightPxNapi);
    napi_get_value_double(env_, rightPxNapi, &options.snapshotRegion.end);

    napi_has_named_property(env_, *regionObject, "top", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value topPxNapi;
    napi_get_named_property(env_, *regionObject, "top", &topPxNapi);
    napi_get_value_double(env_, topPxNapi, &options.snapshotRegion.top);

    napi_has_named_property(env_, *regionObject, "bottom", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value bottomPxNapi;
    napi_get_named_property(env_, *regionObject, "bottom", &bottomPxNapi);
    napi_get_value_double(env_, bottomPxNapi, &options.snapshotRegion.bottom);
    return true;
}

bool JsComponentSnapshot::ParseLocalizedRegion(napi_value* regionObject, NG::SnapshotOptions& options)
{
    options.snapshotRegion = NG::LocalizedSnapshotRegion {};
    bool getReigonResult = false;
    napi_has_named_property(env_, *regionObject, "start", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"start\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value startPxNapi;
    napi_get_named_property(env_, *regionObject, "start", &startPxNapi);
    napi_get_value_double(env_, startPxNapi, &options.snapshotRegion.start);

    napi_has_named_property(env_, *regionObject, "end", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"end\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value endPxNapi;
    napi_get_named_property(env_, *regionObject, "end", &endPxNapi);
    napi_get_value_double(env_, endPxNapi, &options.snapshotRegion.end);

    napi_has_named_property(env_, *regionObject, "top", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value topPxNapi;
    napi_get_named_property(env_, *regionObject, "top", &topPxNapi);
    napi_get_value_double(env_, topPxNapi, &options.snapshotRegion.top);

    napi_has_named_property(env_, *regionObject, "bottom", &getReigonResult);
    if (!getReigonResult) {
        LOGE("The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    napi_value bottomPxNapi;
    napi_get_named_property(env_, *regionObject, "bottom", &bottomPxNapi);
    napi_get_value_double(env_, bottomPxNapi, &options.snapshotRegion.bottom);
    return true;
}

static napi_value JSSnapshotGet(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_value result = nullptr;

    if (!helper.CheckArgs(napi_valuetype::napi_string)) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of string type.");
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // parse id
    std::string componentId;
    napi_valuetype valueType = napi_null;
    GetNapiString(env, helper.GetArgv(0), componentId, valueType);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't get delegate of ace_engine. param: " SEC_PLD(%{public}s),
            SEC_PARAM(componentId.c_str()));
        auto callback = helper.CreateCallback(&result);
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    NG::SnapshotOptions options;
    helper.ParseParamForGet(options);

    delegate->GetSnapshot(componentId, helper.CreateCallback(&result), options);

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
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of function type.");
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value result = nullptr;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Can't get delegate of ace_engine. ");
        auto callback = helper.CreateCallback(&result);
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    // create builder closure
    auto builder = [build = helper.GetArgv(0), env] { napi_call_function(env, nullptr, build, 0, nullptr, nullptr); };

    NG::SnapshotParam param;
    helper.ParseParamForBuilder(param);

    delegate->CreateSnapshot(builder, helper.CreateCallback(&result), true, param);

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSSnapshotGetSync(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_value result = nullptr;

    if (!helper.CheckArgs(napi_valuetype::napi_string)) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of string type.");
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    // parse id
    std::string componentId;
    napi_valuetype valueType = napi_null;
    GetNapiString(env, helper.GetArgv(0), componentId, valueType);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't get delegate of ace_engine. param: " SEC_PLD(%{public}s),
            SEC_PARAM(componentId.c_str()));
        NapiThrow(env, "Delegate is null", ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    NG::SnapshotOptions options;
    helper.ParseParamForGet(options);

    auto pair = delegate->GetSyncSnapshot(componentId,  options);
    
    switch (pair.first) {
        case ERROR_CODE_NO_ERROR :
#ifdef PIXEL_MAP_SUPPORTED
            result = Media::PixelMapNapi::CreatePixelMap(env, pair.second);
#endif
            break;
        case ERROR_CODE_INTERNAL_ERROR :
            napi_get_null(env, &result);
            NapiThrow(env, "Internal error!", ERROR_CODE_INTERNAL_ERROR);
            break;
        case ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT :
            napi_get_null(env, &result);
            NapiThrow(env, "ComponentSnapshot timeout!", ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT);
            break;
        case ERROR_CODE_PARAM_INVALID :
            napi_get_null(env, &result);
            NapiThrow(env, "Snapshot region is invalid or out of range!", ERROR_CODE_PARAM_INVALID);
            break;
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSSnapshotGetWithUniqueId(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_value result = nullptr;

    napi_valuetype type = napi_undefined;
    napi_typeof(env, helper.GetArgv(0), &type);
    if (type != napi_valuetype::napi_number) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of number type.");
        NapiThrow(env, "parameter uniqueId is not of type number", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    // parse uniqueId
    int32_t uniqueId;
    napi_get_value_int32(env, helper.GetArgv(0), &uniqueId);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't get delegate of ace_engine. param: %{public}d",
            uniqueId);
        auto callback = helper.CreateCallback(&result);
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    NG::SnapshotOptions options;
    helper.ParseParamForGet(options);

    delegate->GetSnapshotByUniqueId(uniqueId, helper.CreateCallback(&result), options);

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSSnapshotGetSyncWithUniqueId(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_value result = nullptr;

    napi_valuetype type = napi_undefined;
    napi_typeof(env, helper.GetArgv(0), &type);
    if (type != napi_valuetype::napi_number) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of number type.");
        NapiThrow(env, "parameter uniqueId is not of type number", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    // parse uniqueId
    int32_t uniqueId;
    napi_get_value_int32(env, helper.GetArgv(0), &uniqueId);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't get delegate of ace_engine. param: %{public}d", uniqueId);
        NapiThrow(env, "Delegate is null", ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    NG::SnapshotOptions options;
    helper.ParseParamForGet(options);

    auto pair = delegate->GetSyncSnapshotByUniqueId(uniqueId,  options);
    
    switch (pair.first) {
        case ERROR_CODE_NO_ERROR :
#ifdef PIXEL_MAP_SUPPORTED
            result = Media::PixelMapNapi::CreatePixelMap(env, pair.second);
#endif
            break;
        case ERROR_CODE_INTERNAL_ERROR :
            napi_get_null(env, &result);
            NapiThrow(env, "Internal error!", ERROR_CODE_INTERNAL_ERROR);
            break;
        case ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT :
            napi_get_null(env, &result);
            NapiThrow(env, "ComponentSnapshot timeout!", ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT);
            break;
        case ERROR_CODE_PARAM_INVALID :
            napi_get_null(env, &result);
            NapiThrow(env, "Snapshot region is invalid or out of range!", ERROR_CODE_PARAM_INVALID);
            break;
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSSnapshotFromComponent(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);
    if (!helper.CheckArgs(napi_valuetype::napi_object)) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing the first argument failed, not of object type.");
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value result = nullptr;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Can't get delegate of ace_engine. ");
        NapiThrow(env, "Delegate is null", ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value frameNodePtr = nullptr;
    auto componentResult = napi_get_named_property(env, helper.GetArgv(0), "nodePtr_", &frameNodePtr);
    if (componentResult != napi_ok) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    void* nativePtr = nullptr;
    componentResult = napi_get_value_external(env, frameNodePtr, &nativePtr);
    if (componentResult != napi_ok) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    if (!nativePtr) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    WeakPtr<NG::UINode> nodeWk;
    auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
    nodeWk = AceType::WeakClaim(uiNodePtr);
    
    NG::SnapshotParam param;
    helper.ParseParamForBuilder(param);

    delegate->CreateSnapshotFromComponent(nodeWk.Upgrade(), helper.CreateCallback(&result), false, param);

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

bool JudgeRangeType(napi_env env, napi_callback_info info, int32_t argNum)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_valuetype type = napi_undefined;
    napi_value argv = helper.GetArgv(argNum);
    if (argv == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return false;
    }
    napi_typeof(env, argv, &type);
    if (type != napi_valuetype::napi_number && type != napi_valuetype::napi_string) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing argument failed, not of number or string type.");
        NapiThrow(env, "parameter uniqueId is not of type number or string", ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return false;
    }
    napi_close_escapable_handle_scope(env, scope);
    return true;
}

bool JudgeRectValue(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    napi_valuetype type = napi_undefined;
    napi_value argv = helper.GetArgv(GETWITHRANGE_ISSTARTRECT_NUMBER);
    if (argv == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return true;
    }
    napi_typeof(env, argv, &type);
    bool isRect = true;
    if (type == napi_valuetype::napi_boolean) {
        napi_get_value_bool(env, argv, &isRect);
    }
    napi_close_escapable_handle_scope(env, scope);
    return isRect;
}

NG::NodeIdentity GetNodeIdentity(napi_env env, napi_callback_info info, int32_t index)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    JsComponentSnapshot helper(env, info);

    NG::NodeIdentity nodeIdentity;
    napi_valuetype type = napi_undefined;
    napi_value argv = helper.GetArgv(index);
    if (argv == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nodeIdentity;
    }
    napi_typeof(env, argv, &type);
    if (type == napi_valuetype::napi_number) {
        napi_get_value_int32(env, argv, &nodeIdentity.second);
    } else {
        napi_valuetype valueType = napi_null;
        GetNapiString(env, argv, nodeIdentity.first, valueType);
    }
    napi_close_escapable_handle_scope(env, scope);
    return nodeIdentity;
}

static napi_value JSSnapshotGetWithRange(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    JsComponentSnapshot helper(env, info);
    napi_value result = nullptr;

    if (!JudgeRangeType(env, info, 0) || !JudgeRangeType(env, info, 1)) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Parsing argument failed, not of number or string type.");
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    auto startID = GetNodeIdentity(env, info, 0);
    auto endID = GetNodeIdentity(env, info, 1);
    bool isStartRect = JudgeRectValue(env, info);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Can't get delegate of ace_engine. ");
        NapiThrow(env, "Delegate is null", ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    NG::SnapshotOptions options;
    helper.ParseParamForGet(options);
    delegate->GetSnapshotWithRange(startID, endID, isStartRect, helper.CreateCallback(&result), options);

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value ComponentSnapshotExport(napi_env env, napi_value exports)
{
    napi_property_descriptor snapshotDesc[] = {
        DECLARE_NAPI_FUNCTION("get", JSSnapshotGet),
        DECLARE_NAPI_FUNCTION("createFromBuilder", JSSnapshotFromBuilder),
        DECLARE_NAPI_FUNCTION("getSync", JSSnapshotGetSync),
        DECLARE_NAPI_FUNCTION("getWithUniqueId", JSSnapshotGetWithUniqueId),
        DECLARE_NAPI_FUNCTION("getSyncWithUniqueId", JSSnapshotGetSyncWithUniqueId),
        DECLARE_NAPI_FUNCTION("createFromComponent", JSSnapshotFromComponent),
        DECLARE_NAPI_FUNCTION("getWithRange", JSSnapshotGetWithRange),
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

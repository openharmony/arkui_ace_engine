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
#include "componentSnapshot_module.h"

#include "load.h"
#include "log/log.h"
#include "base/error/error_code.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine.h"
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map_taihe_ani.h"
#endif

namespace OHOS::Ace::Ani {
constexpr int32_t CALLBACK_PARAM_LENGTH = 2;
ani_object WrapStsError(ani_env* env, const std::string& msg)
{
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = ANI_ERROR;
    if (env == nullptr) {
        return nullptr;
    }

    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg)) != ANI_OK) {
        return nullptr;
    }

    ani_ref undefRef;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        return nullptr;
    }

    if ((status = env->FindClass("Lescompat/Error;", &cls)) != ANI_OK) {
        return nullptr;
    }
    if ((status = env->Class_FindMethod(cls, "<ctor>", "Lstd/core/String;Lescompat/ErrorOptions;:V", &method)) !=
        ANI_OK) {
        return nullptr;
    }

    if ((status = env->Object_New(cls, method, &obj, aniMsg, undefRef)) != ANI_OK) {
        return nullptr;
    }
    return obj;
}

static ani_ref CreateStsError(ani_env* env, ani_int code, const std::string& msg)
{
    ani_class cls;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("L@ohos/base/BusinessError;", &cls)) != ANI_OK) {
        return nullptr;
    }
    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", "DLescompat/Error;:V", &ctor)) != ANI_OK) {
        return nullptr;
    }
    ani_object error = WrapStsError(env, msg);
    if (error == nullptr) {
        return nullptr;
    }
    ani_object obj = nullptr;
    ani_double dCode(code);
    if ((status = env->Object_New(cls, ctor, &obj, dCode, error)) != ANI_OK) {
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(obj);
}

static bool GetOptionsScale(ani_env* env, ani_object options, float& value)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(options, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_class optionsClass;
    if (ANI_OK != env->FindClass("L@ohos/arkui/componentSnapshot/componentSnapshot/SnapshotOptions;", &optionsClass)) {
        return false;
    }
    ani_boolean isOptions;
    if (ANI_OK != env->Object_InstanceOf(options, optionsClass, &isOptions)) {
        return false;
    }
    if (!isOptions) {
        return false;
    }

    ani_ref propertyRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "scale", &propertyRef)) {
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (isPropertyUndefined) {
        return false;
    }
    ani_double aniValue;
    if (ANI_OK !=
        env->Object_CallMethodByName_Double(static_cast<ani_object>(propertyRef), "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<double>(aniValue);
    return true;
}

static bool GetOptionsWaitUntilRenderFinished(ani_env* env, ani_object options, bool& value)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(options, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }

    ani_class optionsClass;
    if (ANI_OK != env->FindClass("L@ohos/arkui/componentSnapshot/componentSnapshot/SnapshotOptions;", &optionsClass)) {
        return false;
    }
    ani_boolean isOptions;
    if (ANI_OK != env->Object_InstanceOf(options, optionsClass, &isOptions)) {
        return false;
    }
    if (!isOptions) {
        return false;
    }

    ani_ref propertyRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "waitUntilRenderFinished", &propertyRef)) {
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (isPropertyUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK !=
        env->Object_CallMethodByName_Boolean(static_cast<ani_object>(propertyRef), "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

static bool ParseRegionProperty(ani_env* env, ani_object regionObject, const char* regionType, ani_double& aniValue)
{
    ani_ref propertyRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(regionObject, regionType, &propertyRef)) {
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (!isPropertyUndefined) {
        return false;
    }

    if (ANI_OK !=
        env->Object_CallMethodByName_Double(static_cast<ani_object>(propertyRef), "unboxed", nullptr, &aniValue)) {
        return false;
    }
    return true;
}

static bool ParseLocalizedRegion(ani_env* env, ani_object regionObject, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    snapShotOptions.snapshotRegion = OHOS::Ace::NG::LocalizedSnapshotRegion {};
    ani_boolean isUndefined;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_double startANIValue;
    if (!ParseRegionProperty(env, regionObject, "start", startANIValue)) {
        HILOGE("AceComponentSnapshot, The \"start\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(startANIValue);

    ani_double endANIValue;
    if (!ParseRegionProperty(env, regionObject, "end", endANIValue)) {
        HILOGE("AceComponentSnapshot, The \"end\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(endANIValue);

    ani_double topANIValue;
    if (!ParseRegionProperty(env, regionObject, "top", topANIValue)) {
        HILOGE("AceComponentSnapshot, The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (!ParseRegionProperty(env, regionObject, "bottom", bottomANIValue)) {
        HILOGE("AceComponentSnapshot, The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool ParseRegion(ani_env* env, ani_object regionObject, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    snapShotOptions.snapshotRegion = OHOS::Ace::NG::LocalizedSnapshotRegion {};
    ani_boolean isUndefined;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_double leftANIValue;
    if (!ParseRegionProperty(env, regionObject, "left", leftANIValue)) {
        HILOGE("AceComponentSnapshot, The \"left\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(leftANIValue);

    ani_double rightANIValue;
    if (!ParseRegionProperty(env, regionObject, "right", rightANIValue)) {
        HILOGE("AceComponentSnapshot, The \"right\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(rightANIValue);

    ani_double topANIValue;
    if (!ParseRegionProperty(env, regionObject, "top", topANIValue)) {
        HILOGE("AceComponentSnapshot, The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (!ParseRegionProperty(env, regionObject, "bottom", bottomANIValue)) {
        HILOGE("AceComponentSnapshot, The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool GetOptionsRegion(ani_env* env, ani_object options, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_ref regionObject;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "region", &regionObject)) {
        snapShotOptions.regionMode = OHOS::Ace::NG::SnapshotRegionMode::NO_REGION;
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(regionObject, &isPropertyUndefined);
    if (!isPropertyUndefined) {
        snapShotOptions.regionMode = OHOS::Ace::NG::SnapshotRegionMode::NO_REGION;
        return false;
    }

    snapShotOptions.regionMode = OHOS::Ace::NG::SnapshotRegionMode::COMMON;
    if (ParseLocalizedRegion(env, static_cast<ani_object>(regionObject), snapShotOptions)) {
        snapShotOptions.regionMode = OHOS::Ace::NG::SnapshotRegionMode::LOCALIZED;
    } else {
        ParseRegion(env, static_cast<ani_object>(regionObject), snapShotOptions);
    }
    return true;
}

static bool GetAniIntValue(ani_env* env, ani_object object, int32_t& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_int aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Int(object, "toInt", ":i", &aniValue)) {
        return false;
    }
    value = static_cast<int32_t>(aniValue);
    return true;
}

static bool GetCheckImageStatus(ani_env* env, ani_object object, bool& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(object, "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

struct SnapshotAsyncCtx {
    ani_env* env = nullptr;
    ani_resolver deferred = nullptr;
    ani_object callbackRef = nullptr;
    ani_object destroyCallbackRef = nullptr;
    std::shared_ptr<OHOS::Media::PixelMap> pixmap = nullptr;
    int32_t errCode = -1;
    int32_t instanceId = -1;
};

void TriggerJsCallback(SnapshotAsyncCtx* asyncCtx)
{
    std::unique_ptr<SnapshotAsyncCtx> ctx(asyncCtx);
    ani_boolean errorExists;
    ctx->env->ExistUnhandledError(&errorExists);

    // callback result format: [Error, PixelMap]
    std::vector<ani_ref> resultRef(CALLBACK_PARAM_LENGTH);
    ctx->env->GetUndefined(&resultRef[0]);
    ctx->env->GetUndefined(&resultRef[1]);

    if (ctx->errCode == OHOS::Ace::ERROR_CODE_NO_ERROR) {
#ifdef PIXEL_MAP_SUPPORTED
        ani_object pixmapItem = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(ctx->env, ctx->pixmap);
        if (pixmapItem) {
            resultRef[1] = pixmapItem;
        }
#endif
    }
    ani_status status = ANI_OK;
    resultRef[0] = CreateStsError(ctx->env, ctx->errCode, "");
    if (ctx->deferred) {
        // promise
        if (ctx->errCode == OHOS::Ace::ERROR_CODE_NO_ERROR) {
            if ((status = ctx->env->PromiseResolver_Resolve(ctx->deferred, resultRef[1])) != ANI_OK) {
                HILOGE("AceComponentSnapshot PromiseResolver_Resolve Failed!");
            }
        } else {
            if ((status = ctx->env->PromiseResolver_Reject(ctx->deferred, static_cast<ani_error>(resultRef[0]))) !=
                ANI_OK) {
                HILOGE("AceComponentSnapshot PromiseResolver_Reject Failed!");
            }
        }
    } else if (ctx->callbackRef) {
        // callback
        ani_ref fnReturnVal;
        if ((status = ctx->env->FunctionalObject_Call(static_cast<ani_fn_object>(ctx->callbackRef), resultRef.size(),
                                                        resultRef.data(), &fnReturnVal)) != ANI_OK) {
            HILOGE("ACE_COMPONENT_SNAPSHOT FunctionalObject_Call Failed!");
        };
        ctx->env->GlobalReference_Delete(ctx->callbackRef);
    } else {
        HILOGE("AceComponentSnapshot Internal error!");
    }
    if (asyncCtx->destroyCallbackRef) {
        std::vector<ani_ref> resultRef;
        ani_ref fnReturnVal;
        ani_status status = ANI_OK;
        if ((status = asyncCtx->env->FunctionalObject_Call(static_cast<ani_fn_object>(asyncCtx->destroyCallbackRef),
                 resultRef.size(), resultRef.data(), &fnReturnVal)) != ANI_OK) {
            HILOGE("ACE_COMPONENT_SNAPSHOT FunctionalObject_Call Failed!");
        };
        ctx->env->GlobalReference_Delete(ctx->destroyCallbackRef);
    }
}

void OnComplete(SnapshotAsyncCtx* asyncCtx, std::function<void()> finishCallback)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        HILOGE("AceComponentSnapshot get node ani modifier failed!");
        return;
    }
    auto container = modifier->getComponentSnapshotAniModifier()->getContainer(asyncCtx->instanceId);
    if (!container) {
        HILOGE("AceComponentSnapshot container is null. %{public}d", asyncCtx->instanceId);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        HILOGE("AceComponentSnapshot taskExecutor is null.");
        return;
    }
    taskExecutor->PostTask(
        [asyncCtx, finishCallback]() {
            TriggerJsCallback(asyncCtx);
            if (finishCallback) {
                finishCallback();
            }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIComponentSnapshotComplete");
}

auto CreateCallbackFunc(ani_env* env, ani_object callback, ani_object destroyCallback, ani_object& result)
{
    auto* asyncCtx = new SnapshotAsyncCtx;
    if (callback) {
        ani_ref objectGRef;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &objectGRef);
        asyncCtx->callbackRef = reinterpret_cast<ani_object>(objectGRef);
    }
    if (!asyncCtx->callbackRef) {
        env->Promise_New(&asyncCtx->deferred, &result);
    }
    if (destroyCallback) {
        ani_ref objectGRef;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(destroyCallback), &objectGRef);
        asyncCtx->destroyCallbackRef = reinterpret_cast<ani_object>(objectGRef);
    }

    asyncCtx->env = env;
    const auto* modifier = GetNodeAniModifier();
    if (modifier) {
        asyncCtx->instanceId = modifier->getComponentSnapshotAniModifier()->getCurrentIdSafely();
    }

    return [asyncCtx](
               std::shared_ptr<OHOS::Media::PixelMap> pixmap, int32_t errCode, std::function<void()> finishCallback) {
        asyncCtx->pixmap = std::move(pixmap);
        asyncCtx->errCode = errCode;
        OnComplete(asyncCtx, finishCallback);
    };
}

void CreateFromBuilderWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object callbackObj, ani_object delay, ani_object checkImageStatus,
    ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return;
    }
    OHOS::Ace::NG::SnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);

    ani_object result = {};
    auto callback = CreateCallbackFunc(env, callbackObj, destroyCallbackObj, result);

    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, callback, param);
}

ani_object CreateFromBuilderWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object delay, ani_object checkImageStatus, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return nullptr;
    }
    OHOS::Ace::NG::SnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);

    ani_object result = {};
    auto callback = CreateCallbackFunc(env, nullptr, destroyCallbackObj, result);

    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, callback, param);
    return result;
}

ani_object CreateFromComponentWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object delay, ani_object checkImageStatus, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return nullptr;
    }
    OHOS::Ace::NG::SnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);
    
    ani_object result = {};
    auto callback = CreateCallbackFunc(env, nullptr, destroyCallbackObj, result);

    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromComponent(arkNode, callback, param);
    return result;
}
} // namespace OHOS::Ace::Ani

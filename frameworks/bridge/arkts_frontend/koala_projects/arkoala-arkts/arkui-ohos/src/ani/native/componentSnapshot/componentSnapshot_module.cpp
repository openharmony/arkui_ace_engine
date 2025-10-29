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
#include "utils/ani_utils.h"

#include "base/error/error_code.h"
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map_taihe_ani.h"
#endif

namespace OHOS::Ace::Ani {
constexpr int32_t CALLBACK_PARAM_LENGTH = 2;

static bool GetOptionsScale(ani_env* env, ani_object options, float& value)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(options, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_class optionsClass;
    if (ANI_OK != env->FindClass("@ohos.arkui.componentSnapshot.componentSnapshot.SnapshotOptions", &optionsClass)) {
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
    value = (value <= 0) ? DEFAULT_SNAPSHOT_SCALE : value;
    return true;
}

static bool GetOptionsWaitUntilRenderFinished(ani_env* env, ani_object options, bool& value)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(options, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }

    ani_class optionsClass;
    if (ANI_OK != env->FindClass("@ohos.arkui.componentSnapshot.componentSnapshot.SnapshotOptions", &optionsClass)) {
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

static bool ParseLocalizedRegion(ani_env* env, ani_object regionObject, ArkUIComponentSnapshotOptions& snapShotOptions)
{
    CHECK_NULL_RETURN(env, false);
    snapShotOptions.snapshotRegion = ArkUILocalizedSnapshotRegion {};
    ani_boolean isUndefined;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_double startANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "start", &startANIValue)) {
        HILOGE("AceComponentSnapshot, The \"start\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(startANIValue);

    ani_double endANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "end", &endANIValue)) {
        HILOGE("AceComponentSnapshot, The \"end\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(endANIValue);

    ani_double topANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "top", &topANIValue)) {
        HILOGE("AceComponentSnapshot, The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "bottom", &bottomANIValue)) {
        HILOGE("AceComponentSnapshot, The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool ParseRegion(ani_env* env, ani_object regionObject, ArkUIComponentSnapshotOptions& snapShotOptions)
{
    CHECK_NULL_RETURN(env, false);
    snapShotOptions.snapshotRegion = ArkUILocalizedSnapshotRegion {};
    ani_boolean isUndefined;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_double leftANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "left", &leftANIValue)) {
        HILOGE("AceComponentSnapshot, The \"left\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(leftANIValue);

    ani_double rightANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "right", &rightANIValue)) {
        HILOGE("AceComponentSnapshot, The \"right\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(rightANIValue);

    ani_double topANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "top", &topANIValue)) {
        HILOGE("AceComponentSnapshot, The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, "bottom", &bottomANIValue)) {
        HILOGE("AceComponentSnapshot, The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool GetOptionsRegion(ani_env* env, ani_object options, ArkUIComponentSnapshotOptions& snapShotOptions)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_ref regionObject;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "region", &regionObject)) {
        snapShotOptions.regionMode = ArkUISnapshotRegionMode::NO_REGION;
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(regionObject, &isPropertyUndefined);
    if (isPropertyUndefined) {
        snapShotOptions.regionMode = ArkUISnapshotRegionMode::NO_REGION;
        return false;
    }

    snapShotOptions.regionMode = ArkUISnapshotRegionMode::COMMON;
    if (ParseLocalizedRegion(env, static_cast<ani_object>(regionObject), snapShotOptions)) {
        snapShotOptions.regionMode = ArkUISnapshotRegionMode::LOCALIZED;
    } else {
        ParseRegion(env, static_cast<ani_object>(regionObject), snapShotOptions);
    }
    return true;
}

static bool GetAniIntValue(ani_env* env, ani_object object, int32_t& value)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_int aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Int(object, "toInt", ":i", &aniValue)) {
        return false;
    }
    value = static_cast<int32_t>(aniValue);
    value = (value < 0) ? DEFAULT_DELAY_TIME : value;
    return true;
}

static bool GetCheckImageStatus(ani_env* env, ani_object object, bool& value)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(object, "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

void TriggerJsCallback(std::shared_ptr<ArkUIComponentSnapshotAsync> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);

    // callback result format: [Error, PixelMap]
    std::vector<ani_ref> resultRef(CALLBACK_PARAM_LENGTH);
    asyncCtx->env->GetUndefined(&resultRef[0]);
    asyncCtx->env->GetUndefined(&resultRef[1]);

    if (asyncCtx->errCode == OHOS::Ace::ERROR_CODE_NO_ERROR) {
#ifdef PIXEL_MAP_SUPPORTED
        std::shared_ptr<OHOS::Media::PixelMap> pixmap =
            std::static_pointer_cast<OHOS::Media::PixelMap>(asyncCtx->pixelMap);
        ani_object pixmapItem = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(asyncCtx->env, pixmap);
        if (pixmapItem) {
            resultRef[1] = pixmapItem;
        }
#endif
    }
    ani_status status = ANI_OK;
    ani_ref businessError = AniUtils::CreateBusinessError(asyncCtx->env, "", asyncCtx->errCode);
    if (businessError) {
        resultRef[0] = businessError;
    }
    if (asyncCtx->deferred) {
        // promise
        if (asyncCtx->errCode == OHOS::Ace::ERROR_CODE_NO_ERROR) {
            if ((status = asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, resultRef[1])) != ANI_OK) {
                HILOGE("AceComponentSnapshot PromiseResolver_Resolve Failed!");
            }
        } else {
            if ((status = asyncCtx->env->PromiseResolver_Reject(
                asyncCtx->deferred, static_cast<ani_error>(resultRef[0]))) != ANI_OK) {
                HILOGE("AceComponentSnapshot PromiseResolver_Reject Failed!");
            }
        }
    } else if (asyncCtx->callbackRef) {
        // callback
        ani_ref fnReturnVal;
        if ((status = asyncCtx->env->FunctionalObject_Call(static_cast<ani_fn_object>(asyncCtx->callbackRef),
            resultRef.size(), resultRef.data(), &fnReturnVal)) != ANI_OK) {
            HILOGE("ACE_COMPONENT_SNAPSHOT FunctionalObject_Call Failed!");
        };
        asyncCtx->env->GlobalReference_Delete(asyncCtx->callbackRef);
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
        asyncCtx->env->GlobalReference_Delete(asyncCtx->destroyCallbackRef);
    }
}

void CreateCallbackFunc(ani_env* env, ArkUIComponentSnapshotAsync& asyncCtx, ani_object callback,
    ani_object destroyCallback, ani_object& result)
{
    asyncCtx.env = env;
    if (callback) {
        ani_ref objectGRef;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &objectGRef);
        asyncCtx.callbackRef = reinterpret_cast<ani_object>(objectGRef);
    }
    if (!asyncCtx.callbackRef) {
        env->Promise_New(&asyncCtx.deferred, &result);
    }
    if (destroyCallback) {
        ani_ref objectGRef;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(destroyCallback), &objectGRef);
        asyncCtx.destroyCallbackRef = reinterpret_cast<ani_object>(objectGRef);
    }
    auto jsCallback = [=](std::shared_ptr<ArkUIComponentSnapshotAsync> snapShotAsyncCtx) {
        TriggerJsCallback(snapShotAsyncCtx);
    };
    asyncCtx.callBackJsFunction = jsCallback;
}

void CreateFromBuilderWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object callbackObj, ani_object delay, ani_object checkImageStatus,
    ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return;
    }
    ArkUISnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);
    
    ani_object result = {};
    ArkUIComponentSnapshotAsync asyncCtx;
    CreateCallbackFunc(env, asyncCtx, callbackObj, destroyCallbackObj, result);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, asyncCtx, param);
}

ani_object CreateFromBuilderWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object delay, ani_object checkImageStatus, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return nullptr;
    }
    ArkUISnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);

    ani_object result = {};
    ArkUIComponentSnapshotAsync asyncCtx;
    CreateCallbackFunc(env, asyncCtx, nullptr, destroyCallbackObj, result);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, asyncCtx, param);
    return result;
}

ani_object CreateFromComponentWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object delay, ani_object checkImageStatus, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return nullptr;
    }
    ArkUISnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);
    GetOptionsRegion(env, options, param.options);

    ani_object result = {};
    ArkUIComponentSnapshotAsync asyncCtx;
    CreateCallbackFunc(env, asyncCtx, nullptr, destroyCallbackObj, result);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromComponent(arkNode, asyncCtx, param);
    return result;
}
} // namespace OHOS::Ace::Ani

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

#include <ani.h>
#include <ani_signature_builder.h>
#include <cstdint>
#include <sstream>
#include <sys/stat.h>
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map_taihe_ani.h"
#endif

#include "core/common/ace_engine.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/base/log/log_wrapper.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/components_ng/base/view_stack_model.h"
#include "frameworks/core/components_ng/render/adapter/component_snapshot.h"

using namespace arkts::ani_signature;
class pixelMap;
constexpr int32_t CALLBACK_PARAM_LENGTH = 2;
namespace {
ani_object WrapStsError(ani_env* env, const std::string& msg)
{
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = ANI_ERROR;
    if (env == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "null env");
        return nullptr;
    }

    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "String_NewUTF8 failed %{public}d", status);
        return nullptr;
    }

    ani_ref undefRef;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "GetUndefined failed %{public}d", status);
        return nullptr;
    }

    if ((status = env->FindClass("escompat.Error", &cls)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "FindClass failed %{public}d", status);
        return nullptr;
    }
    if ((status = env->Class_FindMethod(cls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &method)) !=
        ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Class_FindMethod failed %{public}d", status);
        return nullptr;
    }

    if ((status = env->Object_New(cls, method, &obj, aniMsg, undefRef)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Object_New failed %{public}d", status);
        return nullptr;
    }
    return obj;
}

static ani_ref CreateStsError(ani_env* env, ani_int code, const std::string& msg)
{
    ani_class cls;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("@ohos.base.BusinessError", &cls)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "FindClass failed %{public}d", status);
    }
    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", "iC{escompat.Error}:", &ctor)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Class_FindMethod failed %{public}d", status);
    }
    ani_object error = WrapStsError(env, msg);
    if (error == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "error nulll");
        return nullptr;
    }
    ani_object obj = nullptr;
    if ((status = env->Object_New(cls, ctor, &obj, code, error)) != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Object_New failed %{public}d", status);
    }
    return reinterpret_cast<ani_ref>(obj);
}

void AniThrowError(ani_env* env, ani_int code, const std::string& msg)
{
    CHECK_NULL_VOID(env);
    auto errObj = CreateStsError(env, code, msg);
    if (errObj == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,  "Get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(static_cast<ani_error>(errObj))) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Throw ani error object failed!");
        return;
    }
}

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);

    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

struct SnapshotAsyncCtx {
    ani_env* env = nullptr;
    ani_resolver deferred = nullptr;
    ani_object callbackRef = nullptr;
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
        } else {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "PixelMapTaiheAni CreatePixelMap failed!");
        }
#endif
    }
    ani_status status = ANI_OK;
    resultRef[0] = CreateStsError(ctx->env, ctx->errCode, "");
    if (ctx->deferred) {
        // promise
        if (ctx->errCode == OHOS::Ace::ERROR_CODE_NO_ERROR) {
            if ((status = ctx->env->PromiseResolver_Resolve(ctx->deferred, resultRef[1])) != ANI_OK) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "PromiseResolver_Resolve Failed!");
            }
        } else {
            if ((status = ctx->env->PromiseResolver_Reject(ctx->deferred, static_cast<ani_error>(resultRef[0]))) !=
                ANI_OK) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "PromiseResolver_Reject Failed!");
            }
        }
    } else if (ctx->callbackRef) {
        // callback
        ani_ref fnReturnVal;
        if ((status = ctx->env->FunctionalObject_Call(static_cast<ani_fn_object>(ctx->callbackRef), resultRef.size(),
                                                        resultRef.data(), &fnReturnVal)) != ANI_OK) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "FunctionalObject_Call Failed!");
        };
        ctx->env->GlobalReference_Delete(ctx->callbackRef);
    } else {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error!");
    }
}

void OnComplete(SnapshotAsyncCtx* asyncCtx, std::function<void()> finishCallback)
{
    auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "container is null. %{public}d", asyncCtx->instanceId);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "taskExecutor is null.");
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
} // namespace

bool IsFunctionObjectWith2Param(ani_env* env, ani_ref obj)
{
    ani_class funcClass;
    if (ANI_OK != env->FindClass("std.core.Function2", &funcClass)) {
        return false;
    }
    ani_boolean result;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(obj), funcClass, &result)) {
        return false;
    }
    if (!result) {
        return false;
    }
    return static_cast<bool>(result);
}

auto CreateCallbackFunc(ani_env* env, ani_object callback, ani_object& result)
{
    auto* asyncCtx = new SnapshotAsyncCtx;
    if (callback) {
        ani_ref objectGRef;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &objectGRef);
        asyncCtx->callbackRef = reinterpret_cast<ani_object>(objectGRef);;
    }
    if (!asyncCtx->callbackRef) {
        if (ANI_OK != env->Promise_New(&asyncCtx->deferred, &result)) {
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "create promise object failed!");
        }
    }
    asyncCtx->env = env;
    asyncCtx->instanceId = OHOS::Ace::Container::CurrentIdSafely();

    return [asyncCtx](
               std::shared_ptr<OHOS::Media::PixelMap> pixmap, int32_t errCode, std::function<void()> finishCallback) {
        asyncCtx->pixmap = std::move(pixmap);
        asyncCtx->errCode = errCode;
        OnComplete(asyncCtx, finishCallback);
    };
}

static bool GetOptionsScale(ani_env* env, ani_object options, float& value)
{
    ani_boolean isUndefined = true;
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

    ani_boolean isPropertyUndefined = true;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (isPropertyUndefined) {
        return false;
    }
    ani_double aniValue = 0.0;
    if (ANI_OK !=
        env->Object_CallMethodByName_Double(static_cast<ani_object>(propertyRef), "toDouble", ":d", &aniValue)) {
        return false;
    }
    if (OHOS::Ace::GreatNotEqual(aniValue, 0.0)) {
        value = static_cast<double>(aniValue);
    }
    return true;
}

static bool GetOptionsWaitUntilRenderFinished(ani_env* env, ani_object options, bool& value)
{
    ani_boolean isUndefined = true;
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

    ani_boolean isPropertyUndefined = true;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (isPropertyUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK !=
        env->Object_CallMethodByName_Boolean(static_cast<ani_object>(propertyRef), "toBoolean", ":z", &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

static bool ParseRegionProperty(ani_env* env, ani_object regionObject, const char* regionType, ani_double& aniValue)
{
    if (ANI_OK != env->Object_GetPropertyByName_Double(regionObject, regionType, &aniValue)) {
        return false;
    }
    return true;
}

static bool ParseLocalizedRegion(ani_env* env, ani_object regionObject, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    snapShotOptions.snapshotRegion = OHOS::Ace::NG::LocalizedSnapshotRegion {};
    ani_boolean isUndefined = true;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_double startANIValue;
    if (!ParseRegionProperty(env, regionObject, "start", startANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"start\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(startANIValue);

    ani_double endANIValue;
    if (!ParseRegionProperty(env, regionObject, "end", endANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"end\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(endANIValue);

    ani_double topANIValue;
    if (!ParseRegionProperty(env, regionObject, "top", topANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (!ParseRegionProperty(env, regionObject, "bottom", bottomANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool ParseRegion(ani_env* env, ani_object regionObject, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    snapShotOptions.snapshotRegion = OHOS::Ace::NG::LocalizedSnapshotRegion {};
    ani_boolean isUndefined = true;
    env->Reference_IsUndefined(regionObject, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_double leftANIValue;
    if (!ParseRegionProperty(env, regionObject, "left", leftANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"left\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.start = static_cast<double>(leftANIValue);

    ani_double rightANIValue;
    if (!ParseRegionProperty(env, regionObject, "right", rightANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"right\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.end = static_cast<double>(rightANIValue);

    ani_double topANIValue;
    if (!ParseRegionProperty(env, regionObject, "top", topANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"top\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.top = static_cast<double>(topANIValue);

    ani_double bottomANIValue;
    if (!ParseRegionProperty(env, regionObject, "bottom", bottomANIValue)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "The \"bottom\" attribute cannot be obtained from the parameter.");
        return false;
    }
    snapShotOptions.snapshotRegion.bottom = static_cast<double>(bottomANIValue);
    return true;
}

static bool GetOptionsRegion(ani_env* env, ani_object options, OHOS::Ace::NG::SnapshotOptions& snapShotOptions)
{
    ani_boolean isUndefined = true;
    env->Reference_IsUndefined(options, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_ref regionObject;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "region", &regionObject)) {
        snapShotOptions.regionMode = OHOS::Ace::NG::SnapshotRegionMode::NO_REGION;
        return false;
    }

    ani_boolean isPropertyUndefined = true;
    env->Reference_IsUndefined(regionObject, &isPropertyUndefined);
    if (isPropertyUndefined) {
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

static void GetSnapshot(const std::string& componentId, OHOS::Ace::NG::ComponentSnapshot::JsCallback&& callback,
    const OHOS::Ace::NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    OHOS::Ace::NG::ComponentSnapshot::Get(componentId, std::move(callback), options);
#endif
}

static void ANI_GetWithCallback([[maybe_unused]] ani_env* env,
    ani_string componentId, ani_object callbackObj, ani_object options)
{
    OHOS::Ace::NG::SnapshotOptions snapshotOptions;
    GetOptionsScale(env, options, snapshotOptions.scale);
    GetOptionsWaitUntilRenderFinished(env, options, snapshotOptions.waitUntilRenderFinished);
    GetOptionsRegion(env, options, snapshotOptions);

    ani_object result = {};
    auto componentIdStr = ANIUtils_ANIStringToStdString(env, componentId);

    GetSnapshot(componentIdStr, CreateCallbackFunc(env, callbackObj, result), snapshotOptions);
}

static ani_object ANI_GetWithPromise([[maybe_unused]] ani_env* env, ani_string componentId, ani_object options)
{
    OHOS::Ace::NG::SnapshotOptions snapshotOptions;
    GetOptionsScale(env, options, snapshotOptions.scale);
    GetOptionsWaitUntilRenderFinished(env, options, snapshotOptions.waitUntilRenderFinished);
    GetOptionsRegion(env, options, snapshotOptions);

    ani_object result = {};
    auto componentIdStr = ANIUtils_ANIStringToStdString(env, componentId);

    GetSnapshot(componentIdStr, CreateCallbackFunc(env, nullptr, result), snapshotOptions);
    return result;
}

std::pair<int32_t, std::shared_ptr<OHOS::Media::PixelMap>> GetSyncSnapshot(
    const std::string& componentId, const OHOS::Ace::NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    return OHOS::Ace::NG::ComponentSnapshot::GetSync(componentId, options);
#endif
    return { OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, nullptr };
}

static ani_object ANI_GetSync([[maybe_unused]] ani_env* env, ani_string componentId, ani_object options)
{
    OHOS::Ace::NG::SnapshotOptions snapshotOptions;
    GetOptionsScale(env, options, snapshotOptions.scale);
    GetOptionsWaitUntilRenderFinished(env, options, snapshotOptions.waitUntilRenderFinished);
    GetOptionsRegion(env, options, snapshotOptions);

    auto componentIdStr = ANIUtils_ANIStringToStdString(env, componentId);
    auto pair = GetSyncSnapshot(componentIdStr, snapshotOptions);

    ani_object pixelMap = nullptr;

    switch (pair.first) {
        case OHOS::Ace::ERROR_CODE_NO_ERROR:
#ifdef PIXEL_MAP_SUPPORTED
            pixelMap = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pair.second);
            if (!pixelMap) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "PixelMapTaiheAni CreatePixelMap failed!");
            }
#endif
            break;
        case OHOS::Ace::ERROR_CODE_INTERNAL_ERROR:
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error!");
            AniThrowError(env, pair.first, "Internal error!");
            break;
        case OHOS::Ace::ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT:
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "ComponentSnapshot timeout!");
            AniThrowError(env, pair.first, "ComponentSnapshot timeout!");
            break;
        default:
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Unkonw error coed!");
            break;
    }
    return pixelMap;
}
void GetSnapshotByUniqueId(int32_t uniqueId,
    std::function<void(std::shared_ptr<OHOS::Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
    const OHOS::Ace::NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    OHOS::Ace::NG::ComponentSnapshot::GetByUniqueId(uniqueId, std::move(callback), options);
#endif
}

static ani_object ANI_GetWithUniqueId([[maybe_unused]] ani_env* env, ani_double id, ani_object options)
{
    int32_t uniqueId = static_cast<int32_t>(id);
    OHOS::Ace::NG::SnapshotOptions snapshotOptions;
    GetOptionsScale(env, options, snapshotOptions.scale);
    GetOptionsWaitUntilRenderFinished(env, options, snapshotOptions.waitUntilRenderFinished);
    GetOptionsRegion(env, options, snapshotOptions);

    ani_object result = {};
    GetSnapshotByUniqueId(uniqueId, CreateCallbackFunc(env, nullptr, result), snapshotOptions);
    return result;
}

std::pair<int32_t, std::shared_ptr<OHOS::Media::PixelMap>> GetSyncSnapshotByUniqueId(
    int32_t uniqueId, const OHOS::Ace::NG::SnapshotOptions& options)
{
#ifdef ENABLE_ROSEN_BACKEND
    return OHOS::Ace::NG::ComponentSnapshot::GetSyncByUniqueId(uniqueId, options);
#endif
    return { OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, nullptr };
}

static ani_object ANI_GetSyncWithUniqueId([[maybe_unused]] ani_env* env, ani_double id, ani_object options)
{
    int32_t uniqueId = static_cast<int32_t>(id);
    OHOS::Ace::NG::SnapshotOptions snapshotOptions;
    GetOptionsScale(env, options, snapshotOptions.scale);
    GetOptionsWaitUntilRenderFinished(env, options, snapshotOptions.waitUntilRenderFinished);
    GetOptionsRegion(env, options, snapshotOptions);

    auto pair = GetSyncSnapshotByUniqueId(uniqueId, snapshotOptions);

    ani_object pixelMap = nullptr;
    switch (pair.first) {
        case OHOS::Ace::ERROR_CODE_NO_ERROR:
#ifdef PIXEL_MAP_SUPPORTED
            pixelMap = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pair.second);
            if (!pixelMap) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "PixelMapTaiheAni CreatePixelMap failed!");
            }
#endif
            break;
        case OHOS::Ace::ERROR_CODE_INTERNAL_ERROR:
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error!");
            AniThrowError(env, pair.first, "Internal error!");
            break;
        case OHOS::Ace::ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT:
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "ComponentSnapshot timeout!");
            AniThrowError(env, pair.first, "ComponentSnapshot timeout!");
            break;
    }
    return pixelMap;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    Namespace myNamespace = Builder::BuildNamespace("@ohos.arkui.componentSnapshot.componentSnapshot");
    std::string namespaceDescriptor = myNamespace.Descriptor();
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(namespaceDescriptor.c_str(), &ns)) {
        return ANI_ERROR;
    }

    SignatureBuilder get_SignatureBuilder {};
    get_SignatureBuilder
        .AddClass("std.core.String")
        .AddClass("std.core.Function2")
        .AddClass("@ohos.arkui.componentSnapshot.componentSnapshot.SnapshotOptions");
    std::string get_SignatureStr = get_SignatureBuilder.BuildSignatureDescriptor();

    std::string getWithPromise_SignatureStr =
        "C{std.core.String}C{@ohos.arkui.componentSnapshot.componentSnapshot.SnapshotOptions}:"
        "X{C{std.core.Null}C{std.core.Promise}}";
    std::array methods = {
        ani_native_function { "get", get_SignatureStr.c_str(), reinterpret_cast<void*>(ANI_GetWithCallback) },
        ani_native_function { "get", getWithPromise_SignatureStr.c_str(), reinterpret_cast<void*>(ANI_GetWithPromise) },
        ani_native_function { "getSync", nullptr, reinterpret_cast<void*>(ANI_GetSync) },
        ani_native_function { "getWithUniqueId", nullptr, reinterpret_cast<void*>(ANI_GetWithUniqueId) },
        ani_native_function { "getSyncWithUniqueId", nullptr, reinterpret_cast<void*>(ANI_GetSyncWithUniqueId) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "ANI BindNativeFunctions failed!");
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}

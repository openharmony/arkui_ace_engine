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
#include "log.h"
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

static bool GetAniIntValue(ani_env* env, ani_object object, int32_t& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_int aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Int(object, "intValue", nullptr, &aniValue)) {
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
    } else {
        HILOGE("AceComponentSnapshot Internal error!");
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
        asyncCtx->callbackRef = callback;
    }
    if (!asyncCtx->callbackRef) {
        if (ANI_OK != env->Promise_New(&asyncCtx->deferred, &result)) {
        }
    } else {
    }

    asyncCtx->env = env;
    asyncCtx->destroyCallbackRef = destroyCallback;
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
    ani_object destroyCallbackObj, ani_object callbackObj, ani_object delay, ani_object checkImageStatus)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return;
    }
    OHOS::Ace::NG::SnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);

    ani_object result = {};
    auto callback = CreateCallbackFunc(env, callbackObj, destroyCallbackObj, result);

    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, callback, param);
}

ani_object CreateFromBuilderWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long builderPtr,
    ani_object destroyCallbackObj, ani_object delay, ani_object checkImageStatus)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getComponentSnapshotAniModifier() || !env) {
        return nullptr;
    }
    OHOS::Ace::NG::SnapshotParam param;
    GetAniIntValue(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    ani_object result = {};
    auto callback = CreateCallbackFunc(env, nullptr, destroyCallbackObj, result);

    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(builderPtr);
    modifier->getComponentSnapshotAniModifier()->createFromBuilder(arkNode, callback, param);
    return result;
}
} // namespace OHOS::Ace::Ani

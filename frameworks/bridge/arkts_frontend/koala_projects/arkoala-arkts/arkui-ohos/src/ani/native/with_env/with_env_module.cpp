/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "with_env/with_env_module.h"

#include <any>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "base/utils/utils.h"
#include "load.h"
#include "log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t LOCAL_SCOPE_SIZE = 16;
constexpr ani_size KEY_VALUE_ARGC = 2;

ani_ref GetUndefinedRef(ani_env* env)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef = nullptr;
    if (env->GetUndefined(&undefinedRef) != ANI_OK) {
        return nullptr;
    }
    return undefinedRef;
}

ani_status AttachAniEnv(ani_vm* vm, ani_env** env)
{
    CHECK_NULL_RETURN(vm, ANI_ERROR);
    ani_options aniOpt { 0, nullptr };
    auto status = vm->AttachCurrentThread(&aniOpt, ANI_VERSION_1, env);
    if (status != ANI_OK) {
        vm->GetEnv(ANI_VERSION_1, env);
    }
    return status;
}

class ScopedAniEnv {
public:
    explicit ScopedAniEnv(ani_vm* vm) : vm_(vm)
    {
        status_ = AttachAniEnv(vm_, &env_);
    }

    ~ScopedAniEnv()
    {
        if (vm_ && status_ == ANI_OK) {
            vm_->DetachCurrentThread();
        }
    }

    ani_env* Get() const
    {
        return env_;
    }

private:
    ani_vm* vm_ = nullptr;
    ani_env* env_ = nullptr;
    ani_status status_ = ANI_ERROR;
};

class ScopedLocalScope {
public:
    explicit ScopedLocalScope(ani_env* env) : env_(env)
    {
        active_ = env_ && env_->CreateLocalScope(LOCAL_SCOPE_SIZE) == ANI_OK;
    }

    ~ScopedLocalScope()
    {
        if (active_) {
            env_->DestroyLocalScope();
        }
    }

    bool IsActive() const
    {
        return active_;
    }

private:
    ani_env* env_ = nullptr;
    bool active_ = false;
};

class AniGlobalRefHolder {
public:
    static std::shared_ptr<AniGlobalRefHolder> Create(ani_env* env, ani_ref ref)
    {
        CHECK_NULL_RETURN(env, nullptr);
        CHECK_NULL_RETURN(ref, nullptr);
        ani_vm* vm = nullptr;
        if (env->GetVM(&vm) != ANI_OK || !vm) {
            return nullptr;
        }
        ani_ref globalRef = nullptr;
        if (env->GlobalReference_Create(ref, &globalRef) != ANI_OK || !globalRef) {
            return nullptr;
        }
        return std::make_shared<AniGlobalRefHolder>(vm, globalRef);
    }

    AniGlobalRefHolder(ani_vm* vm, ani_ref ref) : vm_(vm), ref_(ref) {}

    ~AniGlobalRefHolder()
    {
        CHECK_NULL_VOID(vm_);
        CHECK_NULL_VOID(ref_);
        ScopedAniEnv scopedEnv(vm_);
        auto* env = scopedEnv.Get();
        CHECK_NULL_VOID(env);
        env->GlobalReference_Delete(ref_);
        ref_ = nullptr;
    }

    ani_ref Get() const
    {
        return ref_;
    }

private:
    ani_vm* vm_ = nullptr;
    ani_ref ref_ = nullptr;
};

const ArkUIAniWithEnvModifier* GetWithEnvModifier()
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    CHECK_NULL_RETURN(modifier->getArkUIAniWithEnvModifier, nullptr);
    return modifier->getArkUIAniWithEnvModifier();
}

ArkUINodeHandle ToNodeHandle(ani_long ptr)
{
    return reinterpret_cast<ArkUINodeHandle>(ptr);
}

std::string KeyToString(ani_env* env, ani_string key)
{
    return AniUtils::ANIStringToStdString(env, key);
}

ani_ref ConvertQueryResultToAniRef(ani_env* env, const ArkUIAniEnvironmentQueryResult& result)
{
    CHECK_NULL_RETURN(env, nullptr);
    switch (result.type) {
        case ARKUI_ANI_ENV_VALUE_TYPE_NUMBER: {
            auto numberObj = AniUtils::CreateDoubleObject(env, result.numberValue);
            return numberObj ? reinterpret_cast<ani_ref>(numberObj) : GetUndefinedRef(env);
        }
        case ARKUI_ANI_ENV_VALUE_TYPE_CUSTOM: {
            auto holder = std::any_cast<std::shared_ptr<AniGlobalRefHolder>>(&result.customValue);
            if (!holder || !(*holder)) {
                return GetUndefinedRef(env);
            }
            return (*holder)->Get();
        }
        case ARKUI_ANI_ENV_VALUE_TYPE_NONE:
        default:
            return GetUndefinedRef(env);
    }
}

void CallEnvUpdateCallback(const std::shared_ptr<AniGlobalRefHolder>& callback, ani_vm* vm, const std::string& key,
    const std::optional<ArkUIAniEnvironmentQueryResult>& value, const char* warning)
{
    CHECK_NULL_VOID(callback);
    ScopedAniEnv scopedEnv(vm);
    auto* env = scopedEnv.Get();
    CHECK_NULL_VOID(env);
    ScopedLocalScope localScope(env);
    CHECK_NULL_VOID(localScope.IsActive());

    auto keyInt = AniUtils::StdStringToANIInt(env, key);
    CHECK_NULL_VOID(keyInt);
    ani_object keyIntObj = AniUtils::CreateInt32(env, static_cast<int32_t>(keyInt.value()));
    CHECK_NULL_VOID(keyIntObj);
    ani_ref params[2] = { reinterpret_cast<ani_ref>(keyIntObj), nullptr };
    ani_size argc = 1;
    if (value) {
        params[1] = ConvertQueryResultToAniRef(env, *value);
        CHECK_NULL_VOID(params[1]);
        argc = KEY_VALUE_ARGC;
    }
    ani_ref result = nullptr;
    if (env->FunctionalObject_Call(static_cast<ani_fn_object>(callback->Get()), argc, params, &result) != ANI_OK) {
        HILOGW("%{public}s", warning);
    }
}

void CallCustomEnvUpdateCallback(const std::shared_ptr<AniGlobalRefHolder>& callback, ani_vm* vm,
    const std::string& key, const std::optional<ArkUIAniEnvironmentQueryResult>& value)
{
    CallEnvUpdateCallback(callback, vm, key, value, "WithEnv custom environment update callback failed");
}

void CallSystemEnvUpdateCallback(const std::shared_ptr<AniGlobalRefHolder>& callback, ani_vm* vm,
    const std::string& key, const std::optional<ArkUIAniEnvironmentQueryResult>& value)
{
    CallEnvUpdateCallback(callback, vm, key, value, "WithEnv system environment update callback failed");
}
} // namespace

ani_long WithEnvConstruct([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id)
{
    ani_long nativeObj {};
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_RETURN(withEnvModifier, nativeObj);
    CHECK_NULL_RETURN(withEnvModifier->construct, nativeObj);
    auto* node = withEnvModifier->construct(id);
    return reinterpret_cast<ani_long>(node);
}

void WithEnvRemoveSystemEnvProperty(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_string key)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->removeSystemEnvProperty);
    withEnvModifier->removeSystemEnvProperty(ToNodeHandle(ptr), KeyToString(env, key));
}

void WithEnvSetSystemEnvProperty(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_string key, ani_double value)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->setSystemEnvProperty);
    withEnvModifier->setSystemEnvProperty(ToNodeHandle(ptr), KeyToString(env, key), value);
}

void WithEnvSetCustomEnvProperty(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int key, ani_ref value)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->setCustomEnvProperty);
    auto holder = AniGlobalRefHolder::Create(env, value);
    CHECK_NULL_VOID(holder);
    withEnvModifier->setCustomEnvProperty(ToNodeHandle(ptr), std::to_string(key), std::any(holder));
}

void WithEnvRemoveCustomEnvProperty(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int key)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->removeCustomEnvProperty);
    withEnvModifier->removeCustomEnvProperty(ToNodeHandle(ptr), std::to_string(key));
}

ani_ref CustomNodeFindCustomEnvValueByKey(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int key)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_RETURN(withEnvModifier, GetUndefinedRef(env));
    CHECK_NULL_RETURN(withEnvModifier->findCustomEnvValueByKey, GetUndefinedRef(env));
    ArkUIAniEnvironmentQueryResult result;
    if (!withEnvModifier->findCustomEnvValueByKey(ToNodeHandle(ptr), std::to_string(key), result)) {
        return GetUndefinedRef(env);
    }
    return ConvertQueryResultToAniRef(env, result);
}

ani_ref CustomNodeFindSystemEnvValueByKey(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_string key)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_RETURN(withEnvModifier, GetUndefinedRef(env));
    CHECK_NULL_RETURN(withEnvModifier->findSystemEnvValueByKey, GetUndefinedRef(env));
    ArkUIAniEnvironmentQueryResult result;
    if (!withEnvModifier->findSystemEnvValueByKey(ToNodeHandle(ptr), KeyToString(env, key), result)) {
        return GetUndefinedRef(env);
    }
    return ConvertQueryResultToAniRef(env, result);
}

void CustomNodeRegisterOnCustomEnvUpdate(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_fn_object callback)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->setOnCustomEnvUpdate);
    ani_vm* vm = nullptr;
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(env->GetVM(&vm) == ANI_OK);
    CHECK_NULL_VOID(vm);
    auto callbackHolder = AniGlobalRefHolder::Create(env, reinterpret_cast<ani_ref>(callback));
    CHECK_NULL_VOID(callbackHolder);
    withEnvModifier->setOnCustomEnvUpdate(ToNodeHandle(ptr),
        [callbackHolder, vm](
            const std::string& key, const std::optional<ArkUIAniEnvironmentQueryResult>& value) {
            CallCustomEnvUpdateCallback(callbackHolder, vm, key, value);
        });
}

void CustomNodeRegisterOnSystemEnvUpdate(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_fn_object callback)
{
    const auto* withEnvModifier = GetWithEnvModifier();
    CHECK_NULL_VOID(withEnvModifier);
    CHECK_NULL_VOID(withEnvModifier->setOnSystemEnvUpdate);
    ani_vm* vm = nullptr;
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(env->GetVM(&vm) == ANI_OK);
    CHECK_NULL_VOID(vm);
    auto callbackHolder = AniGlobalRefHolder::Create(env, reinterpret_cast<ani_ref>(callback));
    CHECK_NULL_VOID(callbackHolder);
    withEnvModifier->setOnSystemEnvUpdate(ToNodeHandle(ptr),
        [callbackHolder, vm](
            const std::string& key, const std::optional<ArkUIAniEnvironmentQueryResult>& value) {
            CallSystemEnvUpdateCallback(callbackHolder, vm, key, value);
        });
}
} // namespace OHOS::Ace::Ani

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
#include "parallelize_ui_module.h"

#include <vector>

#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t SPECIFIED_CAPACITY = 16;
} // namespace

ani_long ParallelizeUIAdapterNodeConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }

    ani_long node = modifier->getParallelizeUIModifier()->constructAdapterNode(id);
    return node;
}

void ParallelizeUIReset(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(frameNode);

    modifier->getParallelizeUIModifier()->reset(frameNode);
}

void ConvertGetCountCallbackFun(
    ani_vm* vm, std::function<int32_t()>& callback, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    callback = [vm, callbackAni]() -> int32_t {
        CHECK_NULL_RETURN(vm, 0);
        CHECK_NULL_RETURN(callbackAni, 0);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_RETURN(env, 0);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return 0;
        }
        std::vector<ani_ref> args = {};
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
        ani_int aniValue = 0;
        if (ANI_OK != env->Object_CallMethodByName_Int((ani_object)ret, "toInt", ":i", &aniValue)) {
            env->DestroyLocalScope();
            return 0;
        }
        env->DestroyLocalScope();
        return aniValue;
    };
}

void ConvertGetFrameNodeCallbackFun(ani_vm* vm, std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>& callback,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    callback = [vm, callbackAni](int32_t index, int32_t needBuild, int32_t isCache) -> ArkUINodeHandle {
        CHECK_NULL_RETURN(vm, nullptr);
        CHECK_NULL_RETURN(callbackAni, nullptr);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_RETURN(env, nullptr);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return nullptr;
        }
        auto indexAni = AniUtils::CreateInt32(env, index);
        auto needBuildAni = AniUtils::CreateInt32(env, needBuild);
        auto isCacheAni = AniUtils::CreateInt32(env, isCache);
        std::vector<ani_ref> args = { indexAni, needBuildAni, isCacheAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }

        ani_long aniValue;
        if (ANI_OK != env->Object_CallMethodByName_Long((ani_object)ret, "unboxed", ":l", &aniValue)) {
            env->DestroyLocalScope();
            return nullptr;
        }
        env->DestroyLocalScope();
        return reinterpret_cast<ArkUINodeHandle>(aniValue);
    };
}

void ParallelizeUIRegisterCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr,
    ani_fn_object getCountCallback, ani_fn_object getFrameNodeCallback)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !env) {
        return;
    }
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(frameNode);

    auto getCountCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, getCountCallback);
    auto getFrameNodeCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, getFrameNodeCallback);

    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::function<int32_t()> getCountCallbackFun = nullptr;
    std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)> getFrameNodeCallbackFun = nullptr;

    ConvertGetCountCallbackFun(vm, getCountCallbackFun, getCountCallbackAni);
    ConvertGetFrameNodeCallbackFun(vm, getFrameNodeCallbackFun, getFrameNodeCallbackAni);

    modifier->getParallelizeUIModifier()->registerCallback(
        frameNode, std::move(getCountCallbackFun), std::move(getFrameNodeCallbackFun));
}

} // namespace OHOS::Ace::Ani

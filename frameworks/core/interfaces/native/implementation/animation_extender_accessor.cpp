/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "base/utils/time_util.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
    constexpr uint32_t DEFAULT_DURATION = 1000; // ms
    constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
}
namespace AnimationExtenderAccessor {
void DestroyPeerImpl(Ark_AnimationExtender peer)
{
}
Ark_AnimationExtender CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetClipRectImpl(Ark_NativePointer peer,
                     const Ark_Float32 left,
                     const Ark_Float32 top,
                     const Ark_Float32 right,
                     const Ark_Float32 bottom)
{
}
void OpenImplicitAnimationImpl(Ark_NativePointer peer,
                               const Ark_AnimateParam* param)
{
}
void CloseImplicitAnimationImpl(Ark_NativePointer node)
{
}
void OpenImplicitAnimationImpl(const Ark_AnimateParam* param)
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto scopeDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_VOID(scopeDelegate);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto timeInterval = (GetMicroTickCount() - pipelineContextBase->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        timeInterval > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
    AnimationOption option = Converter::Convert<AnimationOption>(*param);
    Validator::ValidateAnimationOption(option, pipelineContextBase->IsFormRender());
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
            option.GetDuration() > (DEFAULT_DURATION - timeInterval)) {
        option.SetDuration(DEFAULT_DURATION - timeInterval);
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - timeInterval));
    }
    auto onFinish = Converter::OptConvert<Callback_Void>(param->onFinish);
    std::function<void()> onFinishEvent = [arkCallback = CallbackHelper(*onFinish), currentId]() mutable {
        ContainerScope scope(currentId);
        arkCallback.Invoke();
    };
    option.SetOnFinishEvent(onFinishEvent);
    if (SystemProperties::GetRosenBackendEnabled()) {
        option.SetAllowRunningAsynchronously(true);
    }
    ViewContextModelNG::openAnimationInternal(option);
}

void CloseImplicitAnimationImpl()
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto scopeDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_VOID(scopeDelegate);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto timeInterval = (GetMicroTickCount() - pipelineContextBase->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        timeInterval > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
    AnimationOption option;
    ViewContextModelNG::closeAnimationInternal(option, true);
}
void StartDoubleAnimationImpl(Ark_NativePointer node,
                              const Ark_DoubleAnimationParam* param)
{
}
void AnimationTranslateImpl(Ark_NativePointer node,
                            const Ark_TranslateOptions* options)
{
}
} // AnimationExtenderAccessor
const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
{
    static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
        AnimationExtenderAccessor::DestroyPeerImpl,
        AnimationExtenderAccessor::CtorImpl,
        AnimationExtenderAccessor::GetFinalizerImpl,
        AnimationExtenderAccessor::SetClipRectImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationImpl,
        AnimationExtenderAccessor::StartDoubleAnimationImpl,
        AnimationExtenderAccessor::AnimationTranslateImpl,
    };
    return &AnimationExtenderAccessorImpl;
}

struct AnimationExtenderPeer {
    virtual ~AnimationExtenderPeer() = default;
};
}

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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
    constexpr uint32_t DEFAULT_DURATION = 1000; // ms
    constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
}
namespace AnimationExtenderAccessor {
void SetClipRectImpl(Ark_NativePointer node,
                     Ark_Float32 x,
                     Ark_Float32 y,
                     Ark_Float32 width,
                     Ark_Float32 height)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->ClipWithRRect(RectF(x, y, width, height), RadiusF(EdgeF(0.0f, 0.0f)));
}

void OpenImplicitAnimationImpl(const Ark_AnimateParam* param)
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
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
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
            option.GetDuration() > (DEFAULT_DURATION - timeInterval)) {
        option.SetDuration(DEFAULT_DURATION - timeInterval);
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - timeInterval));
    }
    auto onFinish = Converter::OptConvert<Callback_Void>(param->onFinish);
    std::function<void()> onFinishEvent = [arkCallback = CallbackHelper(*onFinish), currentId]() mutable {
        ContainerScope scope(currentId);
        arkCallback.InvokeSync();
    };
    option.SetOnFinishEvent(onFinishEvent);
    if (SystemProperties::GetRosenBackendEnabled()) {
        option.SetAllowRunningAsynchronously(true);
    }
    ViewContextModel::GetInstance()->openAnimation(option);
}

void CloseImplicitAnimationImpl()
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
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
    ViewContextModel::GetInstance()->closeAnimation(option, true);
}

void StartDoubleAnimationImpl(Ark_NativePointer node,
                              const Ark_DoubleAnimationParam* param)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(param);
}
void AnimationTranslateImpl(Ark_NativePointer node,
                            const Ark_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    TranslateOptions options = Converter::Convert<TranslateOptions>(*value);

    if (options.x.Unit() == DimensionUnit::PERCENT) {
        options.x = Dimension(options.x.Value() * frameNode->GetGeometryNode()->GetMarginFrameOffset().GetX(),
                              DimensionUnit::PX);
    }

    if (options.y.Unit() == DimensionUnit::PERCENT) {
        options.x = Dimension(options.y.Value() * frameNode->GetGeometryNode()->GetMarginFrameOffset().GetY(),
                              DimensionUnit::PX);
    }

    ViewAbstract::SetTranslate(frameNode, options);
}
} // AnimationExtenderAccessor

const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
{
    static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
        AnimationExtenderAccessor::SetClipRectImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationImpl,
        AnimationExtenderAccessor::StartDoubleAnimationImpl,
        AnimationExtenderAccessor::AnimationTranslateImpl,
    };
    return &AnimationExtenderAccessorImpl;
}

}

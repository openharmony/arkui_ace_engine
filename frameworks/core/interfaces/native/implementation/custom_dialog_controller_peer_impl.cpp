/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/implementation/custom_dialog_controller_peer_impl.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components/theme/shadow_theme.h"

namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
}

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<KeyboardAvoidMode>& dst, const Ark_KeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_KEYBOARD_AVOID_MODE_DEFAULT: dst = KeyboardAvoidMode::DEFAULT; break;
        case ARK_KEYBOARD_AVOID_MODE_NONE: dst = KeyboardAvoidMode::NONE; break;
        default: LOGE("Unexpected enum value in Ark_KeyboardAvoidMode: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
void CustomDialogControllerPeerImpl::SetOwnerView(Ark_NativePointer node)
{
    CHECK_NULL_VOID(node);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto weakNode = AceType::WeakClaim(frameNode);
    CHECK_NULL_VOID(!weakNode.Invalid());
    ownerView_ = weakNode;
}

void CustomDialogControllerPeerImpl::SetBuilder(CustomNodeBuilder builder, Ark_NativePointer node)
{
    CHECK_NULL_VOID(node);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    builder_ = [callback = CallbackHelper(builder), frameNode]() -> RefPtr<UINode> {
        auto refNode = AceType::Claim(frameNode);
        CHECK_NULL_RETURN(refNode, nullptr);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        pipelineContext->UpdateCurrentActiveNode(refNode);
        return callback.BuildSync(reinterpret_cast<Ark_NativePointer>(frameNode));
    };
}

void CustomDialogControllerPeerImpl::SetOnCancel(Opt_Callback_Void cancel, Ark_NativePointer node)
{
    CHECK_NULL_VOID(node);
    auto cancelOpt = Converter::OptConvert<Callback_Void>(cancel);
    CHECK_NULL_VOID(cancelOpt);
    dialogProperties_.onCancel = [callback = CallbackHelper(cancelOpt.value()), node]() {
        auto refNode = AceType::Claim(reinterpret_cast<FrameNode*>(node));
        CHECK_NULL_VOID(refNode);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(refNode);
        callback.Invoke();
    };
}

void CustomDialogControllerPeerImpl::SetAutoCancel(Opt_Boolean autoCancel)
{
    auto result = Converter::OptConvert<bool>(autoCancel);
    if (result) {
        dialogProperties_.autoCancel = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetDialogAlignment(Opt_DialogAlignment alignment)
{
    auto result = Converter::OptConvert<DialogAlignment>(alignment);
    if (result) {
        dialogProperties_.alignment = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetOffset(Opt_Offset offset)
{
    auto result = Converter::OptConvert<DimensionOffset>(offset);
    if (result) {
        dialogProperties_.offset = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetCustomStyle(Opt_Boolean customStyle)
{
    auto result = Converter::OptConvert<bool>(customStyle);
    if (result) {
        dialogProperties_.customStyle = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetGridCount(Opt_Number gridCount)
{
    auto result = Converter::OptConvert<int32_t>(gridCount);
    if (result) {
        dialogProperties_.gridCount = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetMaskColor(Opt_ResourceColor maskColor)
{
    dialogProperties_.maskColor = Converter::OptConvert<Color>(maskColor);
}

void CustomDialogControllerPeerImpl::SetMaskRect(Opt_Rectangle maskRect)
{
    dialogProperties_.maskRect = Converter::OptConvert<DimensionRect>(maskRect);
}

void CustomDialogControllerPeerImpl::SetOpenAnimation(Opt_AnimateParam openAnimation)
{
    auto result = Converter::OptConvert<Converter::AnimateParam>(openAnimation);
    if (result) {
        AnimationOption option;
        option.SetDuration(result.value().duration.value_or(DEFAULT_ANIMATION_DURATION));
        option.SetDelay(result.value().delay.value_or(0));
        option.SetIteration(result.value().iterations.value_or(1));
        float tempo = result.value().tempo.value_or(1.0f);
        if (tempo < 0) {
            tempo = 1.0f;
        } else if (tempo == 0) {
            tempo = 1000.0f;
        }
        option.SetTempo(tempo);
        option.SetAnimationDirection(result.value().direction.value_or(AnimationDirection::NORMAL));
        option.SetFinishCallbackType(result.value().finishCallbackType.value_or(FinishCallbackType::REMOVED));
        option.SetCurve(result.value().curve.value_or(Curves::EASE_IN_OUT));
        dialogProperties_.openAnimation = option;
    } else {
        dialogProperties_.openAnimation = std::nullopt;
    }
}

void CustomDialogControllerPeerImpl::SetCloseAnimation(Opt_AnimateParam closeAnimation)
{
    auto result = Converter::OptConvert<Converter::AnimateParam>(closeAnimation);
    if (result) {
        AnimationOption option;
        option.SetDuration(result.value().duration.value_or(DEFAULT_ANIMATION_DURATION));
        option.SetDelay(result.value().delay.value_or(0));
        option.SetIteration(result.value().iterations.value_or(1));
        float tempo = result.value().tempo.value_or(1.0f);
        if (tempo < 0) {
            tempo = 1.0f;
        } else if (tempo == 0) {
            tempo = 1000.0f;
        }
        option.SetTempo(tempo);
        option.SetAnimationDirection(result.value().direction.value_or(AnimationDirection::NORMAL));
        option.SetFinishCallbackType(result.value().finishCallbackType.value_or(FinishCallbackType::REMOVED));
        option.SetCurve(result.value().curve.value_or(Curves::EASE_IN_OUT));
        dialogProperties_.closeAnimation = option;
    } else {
        dialogProperties_.closeAnimation = std::nullopt;
    }
}

void CustomDialogControllerPeerImpl::SetShowInSubWindow(Opt_Boolean showInSubWindow)
{
    auto result = Converter::OptConvert<bool>(showInSubWindow);
    if (result) {
        dialogProperties_.isShowInSubWindow = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetBackgroundColor(Opt_ResourceColor backgroundColor)
{
    dialogProperties_.backgroundColor = Converter::OptConvert<Color>(backgroundColor);
}

void CustomDialogControllerPeerImpl::SetCornerRadius(Opt_Union_Dimension_BorderRadiuses cornerRadius)
{
    dialogProperties_.borderRadius = Converter::OptConvert<BorderRadiusProperty>(cornerRadius);
}

void CustomDialogControllerPeerImpl::SetIsModal(Opt_Boolean isModal)
{
    auto result = Converter::OptConvert<bool>(isModal);
    if (result) {
        dialogProperties_.isModal = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetDismiss(Opt_Callback_DismissDialogAction_Void onWillDismiss)
{
    AddOnWillDismiss(dialogProperties_, onWillDismiss);
}

void CustomDialogControllerPeerImpl::SetWidth(Opt_Length width)
{
    auto result = Converter::OptConvert<Dimension>(width);
    Validator::ValidateNonNegative(result);
    if (result) {
        dialogProperties_.width = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetHeight(Opt_Length height)
{
    auto result = Converter::OptConvert<Dimension>(height);
    Validator::ValidateNonNegative(result);
    if (result) {
        dialogProperties_.height = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetBorderWidth(Opt_Union_Dimension_EdgeWidths borderWidth)
{
    dialogProperties_.borderWidth = Converter::OptConvert<BorderWidthProperty>(borderWidth);
}

void CustomDialogControllerPeerImpl::SetBorderColor(Opt_Union_ResourceColor_EdgeColors borderColor)
{
    dialogProperties_.borderColor = Converter::OptConvert<BorderColorProperty>(borderColor);
}

void CustomDialogControllerPeerImpl::SetBorderStyle(Opt_Union_BorderStyle_EdgeStyles borderStyle)
{
    dialogProperties_.borderStyle = Converter::OptConvert<BorderStyleProperty>(borderStyle);
}

void CustomDialogControllerPeerImpl::SetShadow(Opt_Union_ShadowOptions_ShadowStyle shadow)
{
    dialogProperties_.shadow = Converter::OptConvert<Shadow>(shadow);
}

void CustomDialogControllerPeerImpl::SetBlurStyle(Opt_BlurStyle backgroundBlurStyle)
{
    auto result = Converter::OptConvert<BlurStyle>(backgroundBlurStyle);
    dialogProperties_.backgroundBlurStyle = result ?
        std::optional<int32_t>(static_cast<int32_t>(result.value())) : std::nullopt;
}

void CustomDialogControllerPeerImpl::SetKeyboardAvoidMode(Opt_KeyboardAvoidMode keyboardAvoidMode)
{
    auto result = Converter::OptConvert<KeyboardAvoidMode>(keyboardAvoidMode);
    if (result) {
        dialogProperties_.keyboardAvoidMode = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetEnableHoverMode(Opt_Boolean enableHoverMode)
{
    auto result = Converter::OptConvert<bool>(enableHoverMode);
    if (result) {
        dialogProperties_.enableHoverMode = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetHoverModeArea(Opt_HoverModeAreaType hoverModeArea)
{
    dialogProperties_.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(hoverModeArea);
}

DialogProperties CustomDialogControllerPeerImpl::GetDialogProperties() const
{
    return dialogProperties_;
}

void CustomDialogControllerPeerImpl::OpenDialog()
{
    ContainerScope scope(instanceId_);
    if (dialogProperties_.windowScene.Invalid()) {
        const auto windowScene = GetWindowScene();
        if (windowScene) {
            dialogProperties_.isSceneBoardDialog = true;
            dialogProperties_.windowScene = windowScene;
        }
    }
    dialogProperties_.isSysBlurStyle = true;
    // need check
    // CustomDialogControllerModelNG::SetOpenDialog(dialogProperties_, dialogs_, WeakClaim(this), std::move(builder_));
}

void CustomDialogControllerPeerImpl::CloseDialog()
{
    ContainerScope scope(instanceId_);
    // need check
    // CustomDialogControllerModelNG::SetCloseDialog(dialogProperties_, dialogs_, WeakClaim(this));
}

RefPtr<UINode> CustomDialogControllerPeerImpl::GetWindowScene() const
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto viewNode = ownerView_.Upgrade();
    CHECK_NULL_RETURN(viewNode, nullptr);
    auto parentCustom = AceType::DynamicCast<NG::CustomNode>(viewNode);
    CHECK_NULL_RETURN(parentCustom, nullptr);
    auto parent = parentCustom->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    return parent;
}

} // namespace OHOS::Ace::NG::GeneratedModifier

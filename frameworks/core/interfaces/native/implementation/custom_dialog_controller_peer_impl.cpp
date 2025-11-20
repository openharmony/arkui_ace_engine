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
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_static.h"
#include "core/components/theme/shadow_theme.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<KeyboardAvoidMode>& dst, const Ark_arkui_component_common_KeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_ARKUI_COMPONENT_COMMON_KEYBOARD_AVOID_MODE_DEFAULT: dst = KeyboardAvoidMode::DEFAULT; break;
        case ARK_ARKUI_COMPONENT_COMMON_KEYBOARD_AVOID_MODE_NONE: dst = KeyboardAvoidMode::NONE; break;
        default: LOGE("Unexpected enum value in Ark_arkui_component_common_KeyboardAvoidMode: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
constexpr float DEFAULT_AVOID_DISTANCE = 16.0f;
constexpr double NUM_DOUBLE_100 = 100.;

std::optional<Dimension> OptConvertFromOptNumStrRes(const Opt_Dimension value)
{
    std::optional<Dimension> convValue = std::nullopt;
    if (value.tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes<Ark_Dimension, Ark_Number>(value.value);
    }
    return convValue;
}

std::optional<DimensionOffset> ConvertDimensionOffsetFromOptOffset(Opt_Offset offset)
{
    if (offset.tag == INTEROP_TAG_UNDEFINED) {
        return std::nullopt;
    }
    auto optDx = Converter::OptConvertFromArkLength(offset.value.dx, DimensionUnit::VP);
    auto optDy = Converter::OptConvertFromArkLength(offset.value.dy, DimensionUnit::VP);
    return DimensionOffset(
        optDx.has_value() ? optDx.value() : Dimension(), optDy.has_value() ? optDy.value() : Dimension());
}

std::optional<BorderRadiusProperty> ConvertBorderRadiusPropertyFromOptBorderRadius(
    Opt_Union_Dimension_BorderRadiuses cornerRadius)
{
    std::optional<BorderRadiusProperty> optValue = std::nullopt;
    Converter::VisitUnion(
        cornerRadius,
        [&optValue](const Ark_Dimension& src) {
            BorderRadiusProperty borderRadius;
            auto radius = Converter::OptConvertFromArkNumStrRes<Ark_Dimension, Ark_Number>(src);
            borderRadius.radiusTopLeft = radius;
            Validator::ValidateNonNegative(borderRadius.radiusTopLeft);
            borderRadius.radiusTopRight = radius;
            Validator::ValidateNonNegative(borderRadius.radiusTopRight);
            borderRadius.radiusBottomLeft = radius;
            Validator::ValidateNonNegative(borderRadius.radiusBottomLeft);
            borderRadius.radiusBottomRight = radius;
            Validator::ValidateNonNegative(borderRadius.radiusBottomRight);
            optValue = borderRadius;
        },
        [&optValue](const Ark_BorderRadiuses& src) {
            BorderRadiusProperty borderRadius;
            borderRadius.radiusTopLeft =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.topLeft, DimensionUnit::VP);
            Validator::ValidateNonNegative(borderRadius.radiusTopLeft);
            borderRadius.radiusTopRight =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.topRight, DimensionUnit::VP);
            Validator::ValidateNonNegative(borderRadius.radiusTopRight);
            borderRadius.radiusBottomLeft =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.bottomLeft, DimensionUnit::VP);
            Validator::ValidateNonNegative(borderRadius.radiusBottomLeft);
            borderRadius.radiusBottomRight =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.bottomRight, DimensionUnit::VP);
            Validator::ValidateNonNegative(borderRadius.radiusBottomRight);
            borderRadius.multiValued = true;
            optValue = borderRadius;
        },
        [] {});
    return optValue;
}

std::optional<DimensionRect> ConvertDimensionRectFromOptRectangle(const Opt_Rectangle& rect)
{
    if (rect.tag == INTEROP_TAG_UNDEFINED) {
        return std::nullopt;
    }
    std::optional<DimensionRect> optValue = std::nullopt;

    DimensionRect dst;
    dst.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    dst.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));

    auto src = rect.value;
    if (auto dim = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.width, DimensionUnit::VP); dim) {
        if (dim.has_value()) {
            if (dim.value().IsNegative()) {
                dst.SetWidth(Dimension(NUM_DOUBLE_100, DimensionUnit::PERCENT));
            } else {
                dst.SetWidth(*dim);
            }
        }
    }
    if (auto dim = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.height, DimensionUnit::VP); dim) {
        if (dim.has_value()) {
            if (dim.value().IsNegative()) {
                dst.SetHeight(Dimension(NUM_DOUBLE_100, DimensionUnit::PERCENT));
            } else {
                dst.SetHeight(*dim);
            }
        }
    }
    auto offset = dst.GetOffset();
    if (auto dim = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.x, DimensionUnit::VP); dim) {
        offset.SetX(*dim);
    }
    if (auto dim = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.y, DimensionUnit::VP); dim) {
        offset.SetY(*dim);
    }
    dst.SetOffset(offset);

    optValue = dst;
    return optValue;
}

std::optional<BorderWidthProperty> ConvertBorderWidthPropertyFromOptEdgeWidths(
    Opt_Union_Dimension_EdgeWidths borderWidth)
{
    std::optional<BorderWidthProperty> optValue = std::nullopt;
    Converter::VisitUnion(
        borderWidth,
        [&optValue](const Ark_Dimension& src) {
            BorderWidthProperty widthProperty;
            auto width = Converter::OptConvertFromArkNumStrRes<Ark_Dimension, Ark_Number>(src);
            widthProperty.topDimen = width;
            Validator::ValidateNonNegative(widthProperty.topDimen);
            widthProperty.leftDimen = width;
            Validator::ValidateNonNegative(widthProperty.leftDimen);
            widthProperty.bottomDimen = width;
            Validator::ValidateNonNegative(widthProperty.bottomDimen);
            widthProperty.rightDimen = width;
            Validator::ValidateNonNegative(widthProperty.rightDimen);
            optValue = widthProperty;
        },
        [&optValue](const Ark_EdgeWidths& src) {
            BorderWidthProperty widthProperty;
            widthProperty.topDimen =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.top, DimensionUnit::VP);
            Validator::ValidateNonNegative(widthProperty.topDimen);
            widthProperty.leftDimen =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.left, DimensionUnit::VP);
            Validator::ValidateNonNegative(widthProperty.leftDimen);
            widthProperty.bottomDimen =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.bottom, DimensionUnit::VP);
            Validator::ValidateNonNegative(widthProperty.bottomDimen);
            widthProperty.rightDimen =
                Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.right, DimensionUnit::VP);
            Validator::ValidateNonNegative(widthProperty.rightDimen);
            widthProperty.multiValued = true;
            optValue = widthProperty;
        },
        [] {});
    return optValue;
}
} // namespace

void CustomDialogControllerPeerImpl::SetOwnerView(Ark_NativePointer node)
{
    CHECK_NULL_VOID(node);
    if (!ownerView_.Invalid()) {
        return;
    }
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto weakNode = AceType::WeakClaim(frameNode);
    CHECK_NULL_VOID(!weakNode.Invalid());
    ownerView_ = weakNode;
    auto pipeline = frameNode->GetContext();
    if (pipeline) {
        SetInstanceId(pipeline->GetInstanceId());
    }
}

void CustomDialogControllerPeerImpl::SetBuilder(
    Ark_Union_CustomNodeBuilder_ExtendableComponent value, const RefPtr<CustomDialogControllerPeer>& peer)
{
    Converter::VisitUnion(value,
        [&peer, this](const CustomNodeBuilder& builder) {
            builder_ = [
                callback = CallbackHelper(builder), weakPeer = AceType::WeakClaim(AceType::RawPtr(peer))]() -> void {
                auto controllerPeer = weakPeer.Upgrade();
                CHECK_NULL_VOID(controllerPeer);
                auto weakNode = controllerPeer->GetOwnerViewNode();
                auto frameNode = weakNode.Upgrade();
                CHECK_NULL_VOID(frameNode);
                auto pipelineContext = frameNode->GetContext();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(frameNode);
                callback.BuildAsync([weakPeer](const RefPtr<UINode>& uiNode) {
                    auto controller = weakPeer.Upgrade();
                    CHECK_NULL_VOID(controller);
                    auto builderFunc = [uiNode]() -> RefPtr<UINode> {
                        return uiNode;
                    };
                    CustomDialogControllerModelStatic::SetOpenDialog(
                        controller->dialogProperties_, controller->dialogs_, weakPeer, std::move(builderFunc));
                }, reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode)));
            };
        },
        [](const Ark_ExtendableComponent& src) {
            LOGE("CustomDialogControllerPeerImpl::SetBuilder for Ark_ExtendableComponent is not implemented");
        },
        [] {});
}
void CustomDialogControllerPeerImpl::SetBuilderExtender(
    CustomNodeBuilder builder, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    builder_ = [callback = CallbackHelper(builder), weakPeer = AceType::WeakClaim(AceType::RawPtr(peer))]() -> void {
        auto controllerPeer = weakPeer.Upgrade();
        CHECK_NULL_VOID(controllerPeer);
        auto weakNode = controllerPeer->GetOwnerViewNode();
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(frameNode);
        callback.BuildAsync([weakPeer](const RefPtr<UINode>& uiNode) {
            auto controller = weakPeer.Upgrade();
            CHECK_NULL_VOID(controller);
            auto builderFunc = [uiNode]() -> RefPtr<UINode> {
                return uiNode;
            };
            CustomDialogControllerModelStatic::SetOpenDialog(
                controller->dialogProperties_, controller->dialogs_, weakPeer, std::move(builderFunc));
        }, reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode)));
    };
}
void CustomDialogControllerPeerImpl::SetOnCancel(
    Opt_Callback_Void cancel, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto cancelOpt = TransformCallbackToFunctionVoid(cancel, peer);
    CHECK_NULL_VOID(cancelOpt);
    dialogProperties_.onCancel = cancelOpt;
}
void CustomDialogControllerPeerImpl::SetOnCancelExtender(
    Opt_Callback_Void cancel, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto cancelOpt = TransformCallbackToFunctionVoidExtender(cancel, peer);
    CHECK_NULL_VOID(cancelOpt);
    dialogProperties_.onCancel = cancelOpt;
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
    auto result = ConvertDimensionOffsetFromOptOffset(offset);
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

Opt_Boolean CustomDialogControllerPeerImpl::GetCustomStyle()
{
    return Converter::ArkValue<Opt_Boolean>(dialogProperties_.customStyle);
}

void CustomDialogControllerPeerImpl::SetGridCount(std::optional<int32_t> gridCount)
{
    if (gridCount) {
        dialogProperties_.gridCount = gridCount.value();
    }
}

void CustomDialogControllerPeerImpl::SetMaskColor(Opt_ResourceColor maskColor)
{
    dialogProperties_.maskColor = Converter::OptConvert<Color>(maskColor);
}

void CustomDialogControllerPeerImpl::SetMaskRect(Opt_Rectangle maskRect)
{
    dialogProperties_.maskRect = ConvertDimensionRectFromOptRectangle(maskRect);
}

void CustomDialogControllerPeerImpl::SetOpenAnimation(Opt_AnimateParam openAnimation)
{
    auto result = Converter::OptConvert<AnimationOption>(openAnimation);
    if (result.has_value()) {
        auto option = result.value();
        option.SetDuration(
            Converter::OptConvert<int32_t>(openAnimation.value.duration).value_or(DEFAULT_ANIMATION_DURATION));
        auto onFinish = Converter::OptConvert<Callback_Void>(openAnimation.value.onFinish);
        if (onFinish.has_value()) {
            std::function<void()> onFinishEvent = [
                arkCallback = CallbackHelper(*onFinish), currentId = Container::CurrentIdSafely()]() mutable {
                ContainerScope scope(currentId);
                arkCallback.InvokeSync();
            };
            option.SetOnFinishEvent(onFinishEvent);
        }
        dialogProperties_.openAnimation = option;
    } else {
        dialogProperties_.openAnimation = std::nullopt;
    }
}

void CustomDialogControllerPeerImpl::SetCloseAnimation(Opt_AnimateParam closeAnimation)
{
    auto result = Converter::OptConvert<AnimationOption>(closeAnimation);
    if (result.has_value()) {
        auto option = result.value();
        option.SetDuration(
            Converter::OptConvert<int32_t>(closeAnimation.value.duration).value_or(DEFAULT_ANIMATION_DURATION));
        auto onFinish = Converter::OptConvert<Callback_Void>(closeAnimation.value.onFinish);
        if (onFinish.has_value()) {
            std::function<void()> onFinishEvent = [
                arkCallback = CallbackHelper(*onFinish), currentId = Container::CurrentIdSafely()]() mutable {
                ContainerScope scope(currentId);
                arkCallback.InvokeSync();
            };
            option.SetOnFinishEvent(onFinishEvent);
        }
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
    dialogProperties_.borderRadius = ConvertBorderRadiusPropertyFromOptBorderRadius(cornerRadius);
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

void CustomDialogControllerPeerImpl::SetDismiss(Opt_synthetic_Callback_DismissDialogAction_Void onWillDismiss)
{
    AddOnWillDismiss(dialogProperties_, onWillDismiss);
}

void CustomDialogControllerPeerImpl::SetWidth(Opt_Dimension width)
{
    auto optWidth = OptConvertFromOptNumStrRes(width);
    Validator::ValidateNonNegative(optWidth);
    if (optWidth) {
        dialogProperties_.width = *optWidth;
    }
}

void CustomDialogControllerPeerImpl::SetHeight(Opt_Dimension height)
{
    auto optHeight = OptConvertFromOptNumStrRes(height);
    Validator::ValidateNonNegative(optHeight);
    if (optHeight) {
        dialogProperties_.height = *optHeight;
    }
}

void CustomDialogControllerPeerImpl::SetBorderWidth(Opt_Union_Dimension_EdgeWidths borderWidth)
{
    dialogProperties_.borderWidth = ConvertBorderWidthPropertyFromOptEdgeWidths(borderWidth);
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

void CustomDialogControllerPeerImpl::SetKeyboardAvoidMode(
    Opt_arkui_component_common_KeyboardAvoidMode keyboardAvoidMode)
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

void CustomDialogControllerPeerImpl::SetBackgroundBlurStyleOptions(
    Opt_BackgroundBlurStyleOptions backgroundBlurStyleOptions)
{
    dialogProperties_.blurStyleOption = Converter::OptConvert<BlurStyleOption>(backgroundBlurStyleOptions);
}

void CustomDialogControllerPeerImpl::SetBackgroundEffect(Opt_BackgroundEffectOptions backgroundEffect)
{
    dialogProperties_.effectOption = Converter::OptConvert<EffectOption>(backgroundEffect);
}

void CustomDialogControllerPeerImpl::SetOnDidAppear(
    Opt_VoidCallback onDidAppear, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoid(onDidAppear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onDidAppear = callback;
}

void CustomDialogControllerPeerImpl::SetOnDidDisappear(
    Opt_VoidCallback onDidDisappear, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoid(onDidDisappear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onDidDisappear = callback;
}

void CustomDialogControllerPeerImpl::SetOnWillAppear(
    Opt_VoidCallback onWillAppear, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoid(onWillAppear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onWillAppear = callback;
}

void CustomDialogControllerPeerImpl::SetOnWillDisappear(
    Opt_VoidCallback onWillDisappear, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoid(onWillDisappear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onWillDisappear = callback;
}
void CustomDialogControllerPeerImpl::SetOnDidAppearExtender(
    Opt_Callback_Void onDidAppear, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoidExtender(onDidAppear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onDidAppear = callback;
}

void CustomDialogControllerPeerImpl::SetOnDidDisappearExtender(
    Opt_Callback_Void onDidDisappear, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoidExtender(onDidDisappear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onDidDisappear = callback;
}

void CustomDialogControllerPeerImpl::SetOnWillAppearExtender(
    Opt_Callback_Void onWillAppear, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoidExtender(onWillAppear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onWillAppear = callback;
}

void CustomDialogControllerPeerImpl::SetOnWillDisappearExtender(
    Opt_Callback_Void onWillDisappear, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto callback = TransformCallbackToFunctionVoidExtender(onWillDisappear, peer);
    CHECK_NULL_VOID(callback);
    dialogProperties_.onWillDisappear = callback;
}
void CustomDialogControllerPeerImpl::SetKeyboardAvoidDistance(Opt_LengthMetrics keyboardAvoidDistance)
{
    auto result = Converter::OptConvert<Dimension>(keyboardAvoidDistance);
    if (result.has_value()) {
        if (result.value().IsNonNegative() && result.value().Unit() != OHOS::Ace::DimensionUnit::PERCENT) {
            dialogProperties_.keyboardAvoidDistance = result;
        } else {
            Dimension avoidDistanceDimension(DEFAULT_AVOID_DISTANCE, OHOS::Ace::DimensionUnit::VP);
            dialogProperties_.keyboardAvoidDistance = avoidDistanceDimension;
        }
    }
}

void CustomDialogControllerPeerImpl::SetLevelMode(Opt_Boolean showInSubWindow, Opt_LevelMode levelMode)
{
    auto result = Converter::OptConvert<LevelMode>(levelMode);
    auto isShowInSubwindow = Converter::OptConvert<bool>(showInSubWindow);
    if (result.has_value() && !isShowInSubwindow.value_or(false)) {
        dialogProperties_.dialogLevelMode = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetLevelUniqueId(std::optional<int32_t> levelUniqueId)
{
    if (levelUniqueId.has_value()) {
        dialogProperties_.dialogLevelUniqueId = levelUniqueId.value();
    }
}

void CustomDialogControllerPeerImpl::SetImersiveMode(Opt_ImmersiveMode immersiveMode)
{
    auto result = Converter::OptConvert<ImmersiveMode>(immersiveMode);
    if (result.has_value()) {
        dialogProperties_.dialogImmersiveMode = result.value();
    }
}

void CustomDialogControllerPeerImpl::SetLevelOrder(Opt_LevelOrder levelOrder)
{
    // the levelOrder is accessor in C-API v.132
    auto result = Converter::OptConvert<double>(levelOrder);
    dialogProperties_.levelOrder = result.value_or(NG::LevelOrder::ORDER_DEFAULT);
}

void CustomDialogControllerPeerImpl::SetLevelOrderExtender(Opt_LevelOrderExtender levelOrderExtender)
{
    auto result = Converter::OptConvert<double>(levelOrderExtender);
    dialogProperties_.levelOrder = result.value_or(NG::LevelOrder::ORDER_DEFAULT);
}

void CustomDialogControllerPeerImpl::SetFocusable(Opt_Boolean focusable)
{
    auto result = Converter::OptConvert<bool>(focusable);
    if (result.has_value()) {
        dialogProperties_.focusable = result.value();
    }
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
    builder_();
}

void CustomDialogControllerPeerImpl::CloseDialog()
{
    ContainerScope scope(instanceId_);
    CustomDialogControllerModelStatic::SetCloseDialog(dialogProperties_, dialogs_, WeakClaim(this));
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

std::function<void()> CustomDialogControllerPeerImpl::TransformCallbackToFunctionVoid(
    Opt_Callback_Void callback, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callbackOpt = Converter::OptConvert<Callback_Void>(callback);
    CHECK_NULL_RETURN(callbackOpt, nullptr);
    return [callbackFunc = CallbackHelper(callbackOpt.value()), weak = AceType::WeakClaim(AceType::RawPtr(peer))]() {
        auto controllerPeer = weak.Upgrade();
        CHECK_NULL_VOID(controllerPeer);
        auto weakNode = controllerPeer->GetOwnerViewNode();
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(frameNode);
        callbackFunc.InvokeSync();
    };
}
std::function<void()> CustomDialogControllerPeerImpl::TransformCallbackToFunctionVoid(
    Opt_VoidCallback callback, const RefPtr<CustomDialogControllerPeer>& peer)
{
    auto callbackOpt = Converter::OptConvert<VoidCallback>(callback);
    CHECK_NULL_RETURN(callbackOpt, nullptr);
    return [callbackFunc = CallbackHelper(callbackOpt.value()), weak = AceType::WeakClaim(AceType::RawPtr(peer))]() {
        auto controllerPeer = weak.Upgrade();
        CHECK_NULL_VOID(controllerPeer);
        auto weakNode = controllerPeer->GetOwnerViewNode();
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(frameNode);
        callbackFunc.InvokeSync();
    };
}
std::function<void()> CustomDialogControllerPeerImpl::TransformCallbackToFunctionVoidExtender(
    Opt_Callback_Void callback, const RefPtr<CustomDialogControllerExtenderPeer>& peer)
{
    auto callbackOpt = Converter::OptConvert<Callback_Void>(callback);
    CHECK_NULL_RETURN(callbackOpt, nullptr);
    return [callbackFunc = CallbackHelper(callbackOpt.value()), weak = AceType::WeakClaim(AceType::RawPtr(peer))]() {
        auto controllerPeer = weak.Upgrade();
        CHECK_NULL_VOID(controllerPeer);
        auto weakNode = controllerPeer->GetOwnerViewNode();
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(frameNode);
        callbackFunc.InvokeSync();
    };
}
} // namespace OHOS::Ace::NG::GeneratedModifier

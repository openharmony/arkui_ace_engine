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

#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "core/interfaces/native/utility/promise_helper.h"

using namespace OHOS::Ace::NG::Converter;
namespace OHOS::Ace::NG {
constexpr int32_t INVALID_ID = -1;
constexpr uint32_t MENU_OUTLINE_COLOR = 0x19FFFFFF;
std::unordered_map<int32_t, std::string> UICONTEXT_ERROR_MAP = {
    { ERROR_CODE_TARGET_ID_NOT_EXIST, "The targetId does not exist." },
    { ERROR_CODE_TARGET_NOT_ON_MAIN_TREE, "The node of targetId is not on the component tree." },
    { ERROR_CODE_TARGET_NOT_PAGE_CHILD,
        "The node of targetId is not a child of the page node or NavDestination node." },
    { ERROR_CODE_INTERNAL_ERROR, "Internal error." },
    { ERROR_CODE_PARAM_INVALID, "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;"
        "2. Incorrect parameter types; 3. Parameter verification failed." },
    { ERROR_CODE_DIALOG_CONTENT_ERROR, "The ComponentContent is incorrect." },
    { ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST, "The ComponentContent already exists." },
    { ERROR_CODE_DIALOG_CONTENT_NOT_FOUND, "The ComponentContent cannot be found." },
    { ERROR_CODE_TARGET_INFO_NOT_EXIST, "The targetId does not exist." },
    { ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE, "The node of targetId is not on the component tree." }
};

void ReturnPromise(const Callback_Opt_Array_String_Void* promiseValue, int32_t errorCode)
{
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(promiseValue);
    if (errorCode == ERROR_CODE_NO_ERROR) {
        promise->Resolve();
    } else {
        auto codeValue = std::to_string(errorCode);
        auto codeInfo = UICONTEXT_ERROR_MAP[errorCode];
        StringArray ErrorList = { codeValue, codeInfo };
        promise->Reject(ErrorList);
    }
}

int32_t ParseTargetInfo(const Ark_TargetInfo* targetInfo, int32_t& targetId)
{
    auto targetInfoID = targetInfo->id;
    auto targetInfoComponentId = targetInfo->componentId;
    int result = ERROR_CODE_NO_ERROR;
    Converter::VisitUnion(targetInfoID,
        [&targetId](const Ark_Int32& value) {
            targetId = Converter::Convert<int32_t>(value);
        },
        [&targetId, targetInfoComponentId, &result](const Ark_String& value) {
            auto targetIdString = Converter::Convert<std::string>(value);
            auto targetComponentId = Converter::OptConvert<int32_t>(targetInfoComponentId);
            if (targetComponentId.has_value()) {
                auto componentId = targetComponentId.value();
                auto targetComponentIdNode =
                    ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(componentId);
                if (!targetComponentIdNode) {
                    result = ERROR_CODE_TARGET_INFO_NOT_EXIST;
                    return;
                }
                if (targetComponentIdNode->GetInspectorId().value_or("") == targetIdString) {
                    targetId = targetComponentIdNode->GetId();
                    return;
                }
                auto targetNode = NG::FrameNode::FindChildByName(targetComponentIdNode, targetIdString);
                if (!targetNode) {
                    result = ERROR_CODE_TARGET_INFO_NOT_EXIST;
                    return;
                }
                targetId = targetNode->GetId();
            } else {
                auto targetNode = ElementRegister::GetInstance()->GetAttachedFrameNodeById(targetIdString);
                if (!targetNode) {
                    result = ERROR_CODE_TARGET_INFO_NOT_EXIST;
                    return;
                }
                targetId = targetNode->GetId();
            }
        }, []() {});
    if (targetId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return result;
}

auto g_bindMenuOptionsParamCallbacks = [](
    const auto& menuOptions, MenuParam& menuParam, WeakPtr<FrameNode> weakNode) {
    auto onAppearValue = OptConvert<Callback_Void>(menuOptions.onAppear);
    if (onAppearValue) {
        auto onAppear = [arkCallback = CallbackHelper(onAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onAppear = std::move(onAppear);
    }
    auto onDisappearValue = OptConvert<Callback_Void>(menuOptions.onDisappear);
    if (onDisappearValue) {
        auto onDisappear = [arkCallback = CallbackHelper(onDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    auto aboutToAppearValue = OptConvert<Callback_Void>(menuOptions.aboutToAppear);
    if (aboutToAppearValue) {
        auto aboutToAppear = [arkCallback = CallbackHelper(aboutToAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.aboutToAppear = std::move(aboutToAppear);
    }
    auto aboutToDisAppearValue = OptConvert<Callback_Void>(menuOptions.aboutToDisappear);
    if (aboutToDisAppearValue) {
        auto aboutToDisappear = [arkCallback = CallbackHelper(aboutToDisAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.aboutToDisappear = std::move(aboutToDisappear);
    }
    auto onDidAppearValue = OptConvert<VoidCallback>(menuOptions.onDidAppear);
    if (onDidAppearValue) {
        auto onDidAppear = [arkCallback = CallbackHelper(onDidAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onDidAppear = std::move(onDidAppear);
    }
    auto onDidDisappearValue = OptConvert<VoidCallback>(menuOptions.onDidDisappear);
    if (onDidDisappearValue) {
        auto onDidDisappear = [arkCallback = CallbackHelper(onDidDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onDidDisappear = std::move(onDidDisappear);
    }
    auto onWillAppearValue = OptConvert<VoidCallback>(menuOptions.onWillAppear);
    if (onWillAppearValue) {
        auto onWillAppear = [arkCallback = CallbackHelper(onWillAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onWillAppear = std::move(onWillAppear);
    }
    auto onWillDisappearValue = OptConvert<VoidCallback>(menuOptions.onWillDisappear);
    if (onWillDisappearValue) {
        auto onWillDisappear = [arkCallback = CallbackHelper(onWillDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        menuParam.onWillDisappear = std::move(onWillDisappear);
    }
};

auto g_parseLayoutRegionMargin = [](const auto& menuOptions, MenuParam& menuParam) {
    auto layoutRegionMargin = OptConvert<PaddingProperty>(menuOptions.layoutRegionMargin);
    if (layoutRegionMargin->left.has_value() && !layoutRegionMargin->left.value().IsValid()) {
        layoutRegionMargin->left = std::nullopt;
    }
    if (layoutRegionMargin->right.has_value() && !layoutRegionMargin->right.value().IsValid()) {
        layoutRegionMargin->right = std::nullopt;
    }
    if (layoutRegionMargin->top.has_value() && !layoutRegionMargin->top.value().IsValid()) {
        layoutRegionMargin->top = std::nullopt;
    }
    if (layoutRegionMargin->bottom.has_value() && !layoutRegionMargin->bottom.value().IsValid()) {
        layoutRegionMargin->bottom = std::nullopt;
    }
    layoutRegionMargin->start = layoutRegionMargin->left;
    layoutRegionMargin->end = layoutRegionMargin->right;
    menuParam.layoutRegionMargin = layoutRegionMargin;
};

auto g_parsePreviewAnimationOptions = [](const auto& menuOptions, MenuParam& menuParam) {
    if (menuOptions.previewAnimationOptions.tag != INTEROP_TAG_UNDEFINED) {
        auto previewAnimationOptions =
            Converter::OptConvert<MenuPreviewAnimationOptions>(menuOptions.previewAnimationOptions.value.scale);
        if (previewAnimationOptions.has_value()) {
            menuParam.previewAnimationOptions = previewAnimationOptions.value();
        }
    }
};

auto g_setMenuOutlineWidthMultiValued = [](auto& dimen, const auto& dimenOpt) {
    CHECK_EQUAL_VOID(dimenOpt.has_value(), false);
    auto dimenValue = dimenOpt.value();
    CHECK_EQUAL_VOID(dimenValue.IsNonNegative(), false);
    if (dimenValue.Unit() == DimensionUnit::PERCENT) {
        dimenValue.Reset();
    }
    dimen = dimenValue;
};

auto g_bindMenuOptionsParam = [](const auto& menuOptions, MenuParam& menuParam) {
    auto offsetVal =
        OptConvert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(menuOptions.offset);
    if (offsetVal) {
        menuParam.positionOffset.SetX(offsetVal.value().first->ConvertToPx());
        menuParam.positionOffset.SetY(offsetVal.value().second->ConvertToPx());
    }
    menuParam.enableHoverMode = OptConvert<bool>(menuOptions.enableHoverMode);
    menuParam.backgroundColor = OptConvert<Color>(menuOptions.backgroundColor);
    auto backgroundBlurStyle = OptConvert<BlurStyle>(menuOptions.backgroundBlurStyle);
    menuParam.backgroundBlurStyle =
        backgroundBlurStyle ? std::optional<int32_t>(static_cast<int32_t>(backgroundBlurStyle.value())) : std::nullopt;
    auto transitionOpt = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(menuOptions.transition);
    menuParam.transition = transitionOpt.value_or(menuParam.transition);
    menuParam.hasTransitionEffect = transitionOpt.has_value();
    menuParam.enableArrow = OptConvert<bool>(menuOptions.enableArrow);
    menuParam.arrowOffset = OptConvert<CalcDimension>(menuOptions.arrowOffset);
    menuParam.placement = OptConvert<Placement>(menuOptions.placement);
    if (!menuParam.placement.has_value()) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
    auto borderRadius = OptConvert<BorderRadiusProperty>(menuOptions.borderRadius);
    if (borderRadius.has_value() && (borderRadius.value().radiusTopLeft.has_value()
        || borderRadius.value().radiusTopRight.has_value()
        || borderRadius.value().radiusBottomLeft.has_value()
        || borderRadius.value().radiusBottomRight.has_value())) {
        menuParam.borderRadius = borderRadius;
    }
    Converter::VisitUnion(
        menuOptions.preview,
        [&menuParam](const Ark_MenuPreviewMode& value) {
            auto mode = Converter::OptConvert<MenuPreviewMode>(value);
            if (mode && mode.value() == MenuPreviewMode::IMAGE) {
                menuParam.previewMode = MenuPreviewMode::IMAGE;
            }
        },
        [](const CustomNodeBuilder& value) {}, []() {});
    menuParam.previewBorderRadius = OptConvert<BorderRadiusProperty>(menuOptions.previewBorderRadius);
    g_parseLayoutRegionMargin(menuOptions, menuParam);
    menuParam.hapticFeedbackMode =
        OptConvert<HapticFeedbackMode>(menuOptions.hapticFeedbackMode).value_or(menuParam.hapticFeedbackMode);
    Converter::VisitUnion(menuOptions.mask,
        [&menuParam](const Ark_Boolean& mask) {
            menuParam.maskEnable = OptConvert<bool>(mask);
        },
        [&menuParam](const Ark_MenuMaskType& mask) {
            menuParam.maskEnable = true;
            if (!menuParam.maskType.has_value()) {
                menuParam.maskType.emplace();
            }
            menuParam.maskType.value().maskColor = OptConvert<Color>(mask.color);
            menuParam.maskType.value().maskBackGroundBlurStyle = OptConvert<BlurStyle>(mask.backgroundBlurStyle);
        },
        []() {});
    menuParam.modalMode = OptConvert<ModalMode>(menuOptions.modalMode);
    auto anchorPositionOpt =
        OptConvert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(menuOptions.anchorPosition);
    if (anchorPositionOpt.has_value()) {
        auto dx = anchorPositionOpt.value().first;
        auto dy = anchorPositionOpt.value().second;
        if (dx && dy) {
            menuParam.anchorPosition = { dx.value().ConvertToPx(), dy.value().ConvertToPx() };
        }
        if (menuParam.anchorPosition.has_value()) {
            if (LessNotEqual(menuParam.anchorPosition->GetX(), 0.0f) &&
                LessNotEqual(menuParam.anchorPosition->GetY(), 0.0f)) {
                menuParam.placement = Placement::BOTTOM_LEFT;
                menuParam.anchorPosition.reset();
            }
        }
    }
    menuParam.previewScaleMode = OptConvert<PreviewScaleMode>(menuOptions.previewScaleMode);
    menuParam.availableLayoutAreaMode = OptConvert<AvailableLayoutAreaMode>(menuOptions.availableLayoutArea);
    BorderColorProperty outlineColor;
    auto outlineColorOpt = OptConvert<BorderColorProperty>(menuOptions.outlineColor);
    if (outlineColorOpt.has_value()) {
        outlineColor = outlineColorOpt.value();
        if (outlineColor.multiValued) {
            Color defaultColor = Color::TRANSPARENT;
            outlineColor.leftColor = outlineColor.leftColor.value_or(defaultColor);
            outlineColor.rightColor = outlineColor.rightColor.value_or(defaultColor);
            outlineColor.topColor = outlineColor.topColor.value_or(defaultColor);
            outlineColor.bottomColor = outlineColor.bottomColor.value_or(defaultColor);
        }
    } else {
        auto defaultColor = Color(MENU_OUTLINE_COLOR);
        outlineColor.SetColor(defaultColor);
    }
    menuParam.outlineColor = outlineColor;
    BorderWidthProperty outlineWidth;
    Dimension defaultOutlineWidth = Dimension { -1 };
    auto outlineWidthOpt = OptConvert<BorderWidthProperty>(menuOptions.outlineWidth);
    if (outlineWidthOpt.has_value()) {
        auto outlineWidthValue = outlineWidthOpt.value();
        if (outlineWidthValue.multiValued) {
            g_setMenuOutlineWidthMultiValued(outlineWidth.leftDimen, outlineWidthValue.leftDimen);
            g_setMenuOutlineWidthMultiValued(outlineWidth.rightDimen, outlineWidthValue.rightDimen);
            g_setMenuOutlineWidthMultiValued(outlineWidth.topDimen, outlineWidthValue.topDimen);
            g_setMenuOutlineWidthMultiValued(outlineWidth.bottomDimen, outlineWidthValue.bottomDimen);
        } else {
            auto borderWidth = outlineWidthValue.topDimen.value_or(defaultOutlineWidth);
            if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
                outlineWidth.SetBorderWidth(defaultOutlineWidth);
            } else {
                outlineWidth.SetBorderWidth(borderWidth);
            }
        }
    } else {
        outlineWidth.SetBorderWidth(defaultOutlineWidth);
    }
    menuParam.outlineWidth = outlineWidth;
    menuParam.effectOption = OptConvert<EffectOption>(menuOptions.backgroundEffect);
    menuParam.blurStyleOption = OptConvert<BlurStyleOption>(menuOptions.backgroundBlurStyleOptions);
    menuParam.keyboardAvoidMode = OptConvert<MenuKeyboardAvoidMode>(menuOptions.keyboardAvoidMode);
    menuParam.minKeyboardAvoidDistance = OptConvert<Dimension>(menuOptions.minKeyboardAvoidDistance);
    g_parsePreviewAnimationOptions(menuOptions, menuParam);
};

auto g_onWillDismissPopup = [](
    const Opt_Union_Boolean_Callback_DismissPopupAction_Void& param, RefPtr<PopupParam>& popupParam) {
    CHECK_NULL_VOID(popupParam);
    Converter::VisitUnion(param,
        [&popupParam](const Ark_Boolean& value) {
            popupParam->SetInteractiveDismiss(Converter::Convert<bool>(value));
            popupParam->SetOnWillDismiss(nullptr);
        },
        [&popupParam](const Callback_DismissPopupAction_Void& value) {
            auto callback = [arkCallback = CallbackHelper(value)](int32_t reason) {
            };
            popupParam->SetOnWillDismiss(std::move(callback));
            popupParam->SetInteractiveDismiss(true);
        },
        []() {});
};

auto g_setPopupDefaultBlurStyle = [](RefPtr<PopupParam>& popupParam) {
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    auto blurStyle = static_cast<BlurStyle>(popupTheme->GetPopupBackgroundBlurStyle());
    popupParam->SetBlurStyle(blurStyle);
};

auto g_getShadowFromTheme = [](ShadowStyle shadowStyle, Shadow& shadow) -> bool {
    auto colorMode = Container::CurrentColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
};

auto g_getPopupDefaultShadow = []() -> ShadowStyle {
    auto shadowStyle = ShadowStyle::OuterDefaultMD;
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, shadowStyle);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, shadowStyle);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, shadowStyle);
    return popupTheme->GetPopupShadowStyle();
};

void updatePopupCommonParamPart1(const Ark_PopupCommonOptions& src, RefPtr<PopupParam>& popupParam)
{
    auto placementOpt = OptConvert<Placement>(src.placement);
    if (placementOpt.has_value()) {
        popupParam->SetPlacement(placementOpt.value());
        popupParam->SetHasPlacement(true);
    }
    auto popupBackgroundColor = Converter::OptConvert<Color>(src.popupColor);
    if (popupBackgroundColor.has_value()) {
        popupParam->SetBackgroundColor(popupBackgroundColor.value());
    }
    popupParam->SetEnableArrow(Converter::OptConvert<bool>(src.enableArrow).value_or(popupParam->EnableArrow()));
    auto autoCancel = Converter::OptConvert<bool>(src.autoCancel);
    if (autoCancel.has_value()) {
        popupParam->SetHasAction(!autoCancel.value());
    }
    auto arkOnStateChange = Converter::OptConvert<PopupStateChangeCallback>(src.onStateChange);
    if (arkOnStateChange.has_value()) {
        auto onStateChangeCallback = [arkCallback = CallbackHelper(arkOnStateChange.value())](
            const std::string& param) {
            auto json = JsonUtil::ParseJsonString(param);
            json->Put("isVisible", param.c_str());
            Ark_PopupStateChangeParam event;
            event.isVisible = Converter::ArkValue<Ark_Boolean>(json->GetBool("isVisible", false));
            arkCallback.Invoke(event);
        };
        popupParam->SetOnStateChange(std::move(onStateChangeCallback));
    }
    bool showInSubBoolean = Converter::OptConvert<bool>(src.showInSubWindow).value_or(popupParam->IsShowInSubWindow());
#if defined(PREVIEW)
    showInSubBoolean = false;
#endif
    popupParam->SetShowInSubWindow(showInSubBoolean);
    Converter::VisitUnion(src.mask,
        [&popupParam](const Ark_Boolean& mask) {
            popupParam->SetBlockEvent(Converter::Convert<bool>(mask));
        },
        [&popupParam](const Ark_PopupMaskType& mask) {
            auto popupMaskColor = Converter::OptConvert<Color>(mask.color);
            if (popupMaskColor.has_value()) {
                popupParam->SetMaskColor(popupMaskColor.value());
            }
        },
        []() {});
    auto targetSpaceOpt = Converter::OptConvert<CalcDimension>(src.targetSpace);
    if (targetSpaceOpt.has_value()) {
        popupParam->SetTargetSpace(targetSpaceOpt.value());
    }
    auto offsetOpt = Converter::OptConvert<Dimension>(src.arrowOffset);
    auto pointPositionOpt = Converter::OptConvert<Dimension>(src.arrowPointPosition);
    if (pointPositionOpt.has_value()) {
        popupParam->SetArrowOffset(pointPositionOpt.value());
    } else if (offsetOpt.has_value()) {
        popupParam->SetArrowOffset(offsetOpt.value());
    }
    auto avoidTargetOpt = OptConvert<AvoidanceMode>(src.avoidTarget);
    if (avoidTargetOpt.has_value()) {
        popupParam->SetAvoidTarget(avoidTargetOpt.value());
    }
    auto outlineWidthOpt = Converter::OptConvert<CalcDimension>(src.outlineWidth);
    Validator::ValidateNonNegative(outlineWidthOpt);
    Validator::ValidateNonPercent(outlineWidthOpt);
    if (outlineWidthOpt.has_value()) {
        popupParam->SetOutlineWidth(outlineWidthOpt.value());
    }
    auto borderWidthOpt = Converter::OptConvert<CalcDimension>(src.borderWidth);
    Validator::ValidateNonNegative(borderWidthOpt);
    Validator::ValidateNonPercent(borderWidthOpt);
    if (borderWidthOpt.has_value()) {
        popupParam->SetInnerBorderWidth(borderWidthOpt.value());
    }
    auto outlineLinearGradientOpt = Converter::OptConvert<PopupLinearGradientProperties>(src.outlineLinearGradient);
    if (outlineLinearGradientOpt.has_value()) {
        popupParam->SetOutlineLinearGradient(outlineLinearGradientOpt.value());
    }
    auto borderLinearGradientOpt = Converter::OptConvert<PopupLinearGradientProperties>(src.borderLinearGradient);
    if (borderLinearGradientOpt.has_value()) {
        popupParam->SetInnerBorderLinearGradient(borderLinearGradientOpt.value());
    }
}

void updatePopupCommonParamPart2(const Ark_PopupCommonOptions& src, RefPtr<PopupParam>& popupParam)
{
    auto offsetVal = src.offset.value;
    auto x = Converter::OptConvert<Dimension>(offsetVal.x);
    auto y = Converter::OptConvert<Dimension>(offsetVal.y);
    if (x.has_value() && y.has_value()) {
        Offset popupOffset;
        popupOffset.SetX(x.value().ConvertToPx());
        popupOffset.SetY(y.value().ConvertToPx());
        popupParam->SetTargetOffset(popupOffset);
    }
    auto widthOpt = Converter::OptConvert<CalcDimension>(src.width);
    Validator::ValidateNonNegative(widthOpt);
    if (widthOpt.has_value()) {
        popupParam->SetChildWidth(widthOpt.value());
    }
    auto arrowWidthOpt = Converter::OptConvert<CalcDimension>(src.arrowWidth);
    Validator::ValidatePositive(arrowWidthOpt);
    Validator::ValidateNonPercent(arrowWidthOpt);
    if (arrowWidthOpt.has_value()) {
        popupParam->SetArrowWidth(arrowWidthOpt.value());
    }
    auto arrowHeightOpt = Converter::OptConvert<CalcDimension>(src.arrowHeight);
    Validator::ValidatePositive(arrowHeightOpt);
    Validator::ValidateNonPercent(arrowHeightOpt);
    if (arrowHeightOpt.has_value()) {
        popupParam->SetArrowHeight(arrowHeightOpt.value());
    }
    auto radiusOpt = Converter::OptConvert<CalcDimension>(src.radius);
    Validator::ValidateNonNegative(radiusOpt);
    if (radiusOpt.has_value()) {
        popupParam->SetRadius(radiusOpt.value());
    }
    auto shadowOpt = Converter::OptConvert<Shadow>(src.shadow);
    if (shadowOpt.has_value()) {
        popupParam->SetShadow(shadowOpt.value());
        if (src.shadow.value.selector == 1) {
            popupParam->SetIsShadowStyle(true);
        }
    } else {
        auto defaultPopupShadowStyle = g_getPopupDefaultShadow();
        Shadow shadow;
        g_getShadowFromTheme(defaultPopupShadowStyle, shadow);
        popupParam->SetShadow(shadow);
        popupParam->SetIsShadowStyle(true);
    }
    auto popupBackgroundBlurStyleOpt = Converter::OptConvert<BlurStyle>(src.backgroundBlurStyle);
    if (popupBackgroundBlurStyleOpt.has_value()) {
        popupParam->SetBlurStyle(popupBackgroundBlurStyleOpt.value());
    } else {
        g_setPopupDefaultBlurStyle(popupParam);
    }
    popupParam->SetFocusable(Converter::OptConvert<bool>(src.focusable).value_or(popupParam->GetFocusable()));
    auto popupTransitionEffectsOpt = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(src.transition);
    if (popupTransitionEffectsOpt.has_value()) {
        popupParam->SetHasTransition(true);
        popupParam->SetTransitionEffects(popupTransitionEffectsOpt.value());
    }
    g_onWillDismissPopup(src.onWillDismiss, popupParam);
    popupParam->SetEnableHoverMode(Converter::OptConvert<bool>(src.enableHoverMode)
        .value_or(popupParam->EnableHoverMode()));
    popupParam->SetFollowTransformOfTarget(Converter::OptConvert<bool>(src.followTransformOfTarget)
        .value_or(popupParam->IsFollowTransformOfTarget()));
}

void updatePopupCommonParam(const Ark_PopupCommonOptions& src, RefPtr<PopupParam>& popupParam)
{
    CHECK_NULL_VOID(popupParam);
    updatePopupCommonParamPart1(src, popupParam);
    updatePopupCommonParamPart2(src, popupParam);
}

} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {

template<>
RefPtr<PopupParam> Convert(const Ark_PopupCommonOptions& src)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    updatePopupCommonParam(src, popupParam);
    return popupParam;
}

template<>
MenuParam Convert(const Ark_MenuOptions& src)
{
    MenuParam menuParam;
    g_bindMenuOptionsParam(src, menuParam);
    return menuParam;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PromptActionExtenderAccessor {
void OpenPopupImpl(Ark_VMContext vmContext,
                   Ark_AsyncWorkerPtr asyncWorker,
                   Ark_NativePointer content,
                   const Ark_TargetInfo* target,
                   const Opt_PopupCommonOptions* options,
                   const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    CHECK_NULL_VOID(popupParam);
    popupParam = Converter::Convert<RefPtr<PopupParam>>(options->value);
    popupParam->SetIsShow(true);
    popupParam->SetUseCustomComponent(true);
    int targetId = INVALID_ID;
    auto result = ParseTargetInfo(target, targetId);
    if (result == ERROR_CODE_NO_ERROR) {
        popupParam->SetTargetId(std::to_string(targetId));
    } else {
        ReturnPromise(outputArgumentForReturningPromise, result);
        return;
    }
    result = ViewAbstractModelStatic::OpenPopup(popupParam, frameNode);
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
void UpdatePopupImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_NativePointer content,
                    const Ark_PopupCommonOptions* options,
                    const Opt_Boolean* partialUpdate,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    auto oldParam = AceType::MakeRefPtr<PopupParam>();
    auto result = ViewAbstractModelStatic::GetPopupParam(oldParam, frameNode);
    if (result == ERROR_CODE_NO_ERROR) {
        auto isPartialUpdate = Converter::OptConvert<bool>(*partialUpdate);
        if (isPartialUpdate.has_value()) {
            if (isPartialUpdate.value()) {
                popupParam = oldParam;
                popupParam->SetIsPartialUpdate(isPartialUpdate.value());
            } else {
                popupParam->SetTargetId(oldParam->GetTargetId());
                popupParam->SetIsPartialUpdate(false);
            }
        } else {
            ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_PARAM_INVALID);
            return;
        }
    } else {
        ReturnPromise(outputArgumentForReturningPromise, result);
        return;
    }
    auto isShowInSubWindow = oldParam->IsShowInSubWindow();
    auto focusable = oldParam->GetFocusable();
    popupParam->SetIsShow(true);
    popupParam->SetUseCustomComponent(true);
    updatePopupCommonParam(*options, popupParam);
    popupParam->SetShowInSubWindow(isShowInSubWindow);
    popupParam->SetFocusable(focusable);
    result = ViewAbstractModelStatic::UpdatePopup(popupParam, frameNode);
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
void ClosePopupImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_NativePointer content,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto result = ViewAbstractModelStatic::ClosePopup(frameNode);
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
void OpenMenuImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  Ark_NativePointer content,
                  const Ark_TargetInfo* target,
                  const Opt_MenuOptions* options,
                  const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    MenuParam menuParam = Converter::Convert<MenuParam>(options->value);
    g_bindMenuOptionsParamCallbacks(options->value, menuParam, AceType::WeakClaim(frameNode.GetRawPtr()));
    auto pipelineContext = frameNode->GetContext();
    if (!pipelineContext) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto theme = pipelineContext->GetTheme<SelectTheme>();
    if (!theme) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    menuParam.isShowInSubWindow =
        Converter::OptConvert<bool>(options->value.showInSubWindow).value_or(theme->GetExpandDisplay());
    int targetId = INVALID_ID;
    auto result = ParseTargetInfo(target, targetId);
    if (result == ERROR_CODE_NO_ERROR) {
        frameNode->MarkModifyDone();
        result = ViewAbstractModelStatic::OpenMenu(menuParam, frameNode, targetId);
    }
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
void UpdateMenuImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_NativePointer content,
                    const Ark_MenuOptions* options,
                    const Opt_Boolean* partialUpdate,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto context = frameNode->GetContext();
    if (!context) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    ContainerScope scope(context->GetInstanceId());
    auto isPartialUpdate = Converter::OptConvert<bool>(*partialUpdate);
    if (!isPartialUpdate.has_value()) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_PARAM_INVALID);
        return;
    }
    MenuParam menuParamOpen;
    auto result = ViewAbstractModelStatic::GetMenuParam(menuParamOpen, frameNode);
    if (result != ERROR_CODE_NO_ERROR && result != ERROR_CODE_INTERNAL_ERROR) {
        ReturnPromise(outputArgumentForReturningPromise, result);
        return;
    }
    MenuParam menuParam;
    if (isPartialUpdate.value()) {
        menuParam = menuParamOpen;
    }
    g_bindMenuOptionsParam(*options, menuParam);
    // Updating these parameters is not supported
    menuParam.isShowInSubWindow = menuParamOpen.isShowInSubWindow;
    menuParam.previewMode = menuParamOpen.previewMode;
    result = ViewAbstractModelStatic::UpdateMenu(menuParam, frameNode);
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
void CloseMenuImpl(Ark_VMContext vmContext,
                   Ark_AsyncWorkerPtr asyncWorker,
                   Ark_NativePointer content,
                   const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        ReturnPromise(outputArgumentForReturningPromise, ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    auto result = ViewAbstractModelStatic::CloseMenu(frameNode);
    if (result == ERROR_CODE_INTERNAL_ERROR) {
        result = ERROR_CODE_NO_ERROR;
    }
    ReturnPromise(outputArgumentForReturningPromise, result);
}
} // PromptActionExtenderAccessor
const GENERATED_ArkUIPromptActionExtenderAccessor* GetPromptActionExtenderAccessor()
{
    static const GENERATED_ArkUIPromptActionExtenderAccessor PromptActionExtenderAccessorImpl {
        PromptActionExtenderAccessor::OpenPopupImpl,
        PromptActionExtenderAccessor::UpdatePopupImpl,
        PromptActionExtenderAccessor::ClosePopupImpl,
        PromptActionExtenderAccessor::OpenMenuImpl,
        PromptActionExtenderAccessor::UpdateMenuImpl,
        PromptActionExtenderAccessor::CloseMenuImpl,
    };
    return &PromptActionExtenderAccessorImpl;
}
}

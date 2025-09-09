/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/dialog/dialog_view.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> DialogView::CreateDialogNode(
    const DialogProperties& param, const RefPtr<UINode>& customNode = nullptr)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return CreateDialogNode(nodeId, param, customNode);
}

void SetDialogTransitionEffects(
    const RefPtr<FrameNode>& dialog, const DialogProperties& param, RefPtr<DialogPattern> pattern)
{
    auto dialogContext = dialog->GetRenderContext();
    if (param.maskTransitionEffect != nullptr || param.dialogTransitionEffect != nullptr) {
        dialogContext->UpdateBackgroundColor(Color(0x00000000));
        if (param.dialogTransitionEffect != nullptr) {
            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetChildByIndex(0));
            CHECK_NULL_VOID(contentNode);
            contentNode->GetRenderContext()->UpdateChainedTransition(param.dialogTransitionEffect);
        }
        if (param.maskTransitionEffect != nullptr) {
            auto maskNode = AceType::DynamicCast<FrameNode>(dialog->GetChildByIndex(1));
            CHECK_NULL_VOID(maskNode);
            maskNode->GetRenderContext()->UpdateChainedTransition(param.maskTransitionEffect);
        }
    } else if (param.transitionEffect != nullptr) {
        dialogContext->UpdateChainedTransition(param.transitionEffect);
    }
    if (param.transitionEffect == nullptr && param.dialogTransitionEffect == nullptr &&
        param.maskTransitionEffect == nullptr) {
        // set open and close animation
        pattern->SetOpenAnimation(param.openAnimation);
        pattern->SetCloseAnimation(param.closeAnimation);
    }
}

void UpdateAndAddMaskColorCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    CHECK_NULL_VOID(dialogProps.hasCustomMaskColor);
    if (dialogProps.maskColor.has_value()) {
        Color maskColor = dialogProps.maskColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, maskColor, dialog->GetTag());

        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto dialogContext = dialog->GetRenderContext();
            CHECK_NULL_VOID(dialogContext);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color maskColor;
            bool state = ResourceParseUtils::ParseResColor(resObj, maskColor);
            maskColor = state ? maskColor : dialogTheme->GetMaskColorEnd();

            auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
            CHECK_NULL_VOID(dialogLayoutProp);
            // is app subwindow
            auto isSubWindow = dialogLayoutProp->GetShowInSubWindowValue(false) && !pattern->IsUIExtensionSubWindow();
            auto isModal = dialogLayoutProp->GetIsModal().value_or(true);
            auto isSceneBoardDialog = dialogLayoutProp->GetIsSceneBoardDialog().value_or(false);
            // app subwindow dialog's mask is on top of the main window
            // No need to update app subwindow dialog's background color.
            if ((!isSubWindow && isModal) || isSceneBoardDialog) {
                dialogContext->UpdateBackgroundColor(maskColor);
            }
            dialog->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            dialog->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.maskcolor", resObj, std::move(updateFunc));
        
        auto dialogContext = dialog->GetRenderContext();
        CHECK_NULL_VOID(dialogContext);
        auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
        CHECK_NULL_VOID(dialogLayoutProp);
        auto isSubWindow = dialogLayoutProp->GetShowInSubWindowValue(false) && !pattern->IsUIExtensionSubWindow();
        auto isModal = dialogLayoutProp->GetIsModal().value_or(true);
        auto isSceneBoardDialog = dialogLayoutProp->GetIsSceneBoardDialog().value_or(false);
        // if the current mode is dark color mode，update property immediately.
        if ((!isSubWindow && isModal) || isSceneBoardDialog) {
            dialogContext->UpdateBackgroundColor(maskColor);
        }
    }
}

void UpdateAndAddShadowCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    CHECK_NULL_VOID(dialogProps.hasCustomShadowColor);
    if (dialogProps.shadow.has_value()) {
        Shadow shadow = dialogProps.shadow.value();
        Color shadowColor = shadow.GetColor();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, shadowColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);

            Color shadowColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, shadowColor);
            shadowColor = state ? shadowColor : Color::BLACK;

            auto dialogProps = pattern->GetDialogProperties();
            auto shadow = dialogProps.shadow.value();
            shadow.SetColor(shadowColor);
            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            contentRenderContext->UpdateBackShadow(shadow);
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.shadow.color", resObj, std::move(updateFunc));
        
        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        shadow.SetColor(shadowColor);
        contentRenderContext->UpdateBackShadow(shadow);
    }
}

void UpdateAndAddBackgroundColorCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    CHECK_NULL_VOID(dialogProps.hasCustomBackgroundColor);
    if (dialogProps.backgroundColor.has_value()) {
        Color backgroundColor = dialogProps.backgroundColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, backgroundColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color backgroundColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, backgroundColor);
            backgroundColor = state ? backgroundColor : dialogTheme->GetBackgroundColor();

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            contentRenderContext->UpdateBackgroundColor(backgroundColor);
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.backgroundColor", resObj, std::move(updateFunc));
        
        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        contentRenderContext->UpdateBackgroundColor(backgroundColor);
    }
}

void UpdateAndAddBorderTopColorCallback(RefPtr<FrameNode> dialog, BorderColorProperty borderColor)
{
    if (borderColor.topColor.has_value()) {
        Color topBorderColor = borderColor.topColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, topBorderColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color topBorderColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, topBorderColor);
            topBorderColor = state ? topBorderColor : dialogTheme->GetBackgroundBorderColor();

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            
            auto currentBorderColor = contentRenderContext->GetBorderColor();
            CHECK_NULL_VOID(currentBorderColor.has_value());
            currentBorderColor->topColor = topBorderColor;
            contentRenderContext->UpdateBorderColor(currentBorderColor.value());
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.borderColor.topColor", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        auto currentBorderColor = contentRenderContext->GetBorderColor();
        CHECK_NULL_VOID(currentBorderColor.has_value());
        currentBorderColor->topColor = topBorderColor;
        contentRenderContext->UpdateBorderColor(currentBorderColor.value());
    }
}
void UpdateAndAddBorderBottomColorCallback(RefPtr<FrameNode> dialog, BorderColorProperty borderColor)
{
    if (borderColor.bottomColor.has_value()) {
        Color bottomBorderColor = borderColor.bottomColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, bottomBorderColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color bottomBorderColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, bottomBorderColor);
            bottomBorderColor = state ? bottomBorderColor : dialogTheme->GetBackgroundBorderColor();

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            
            auto currentBorderColor = contentRenderContext->GetBorderColor();
            CHECK_NULL_VOID(currentBorderColor.has_value());
            currentBorderColor->bottomColor = bottomBorderColor;
            contentRenderContext->UpdateBorderColor(currentBorderColor.value());
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.borderColor.bottomColor", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto currentBorderColor = contentRenderContext->GetBorderColor();
        CHECK_NULL_VOID(currentBorderColor.has_value());
        currentBorderColor->bottomColor = bottomBorderColor;
        contentRenderContext->UpdateBorderColor(currentBorderColor.value());
    }
}
void UpdateAndAddBorderLeftColorCallback(RefPtr<FrameNode> dialog, BorderColorProperty borderColor)
{
    if (borderColor.leftColor.has_value()) {
        Color leftBorderColor = borderColor.leftColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, leftBorderColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color leftBorderColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, leftBorderColor);
            leftBorderColor = state ? leftBorderColor : dialogTheme->GetBackgroundBorderColor();

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            
            auto currentBorderColor = contentRenderContext->GetBorderColor();
            CHECK_NULL_VOID(currentBorderColor.has_value());
            currentBorderColor->leftColor = leftBorderColor;
            contentRenderContext->UpdateBorderColor(currentBorderColor.value());
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.borderColor.leftColor", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto currentBorderColor = contentRenderContext->GetBorderColor();
        CHECK_NULL_VOID(currentBorderColor.has_value());
        currentBorderColor->leftColor = leftBorderColor;
        contentRenderContext->UpdateBorderColor(currentBorderColor.value());
    }
}
void UpdateAndAddBorderRightColorCallback(RefPtr<FrameNode> dialog, BorderColorProperty borderColor)
{
    if (borderColor.rightColor.has_value()) {
        Color rightBorderColor = borderColor.rightColor.value();
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, rightBorderColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            auto pipelineContext = dialog->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
            CHECK_NULL_VOID(dialogTheme);

            Color rightBorderColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, rightBorderColor);
            rightBorderColor = state ? rightBorderColor : dialogTheme->GetBackgroundBorderColor();

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            auto currentBorderColor = contentRenderContext->GetBorderColor();
            CHECK_NULL_VOID(currentBorderColor.has_value());
            currentBorderColor->rightColor = rightBorderColor;
            contentRenderContext->UpdateBorderColor(currentBorderColor.value());
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.borderColor.rightColor", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto currentBorderColor = contentRenderContext->GetBorderColor();
        CHECK_NULL_VOID(currentBorderColor.has_value());
        currentBorderColor->rightColor = rightBorderColor;
        contentRenderContext->UpdateBorderColor(currentBorderColor.value());
    }
}

void UpdateAndAddBorderColorCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    CHECK_NULL_VOID(dialogProps.hasCustomBorderColor);
    if (dialogProps.borderColor.has_value()) {
        BorderColorProperty borderColor = dialogProps.borderColor.value();
        UpdateAndAddBorderTopColorCallback(dialog, borderColor);
        UpdateAndAddBorderBottomColorCallback(dialog, borderColor);
        UpdateAndAddBorderLeftColorCallback(dialog, borderColor);
        UpdateAndAddBorderRightColorCallback(dialog, borderColor);
    }
}

void UpdateAndAddBlurStyleOptionCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    if (dialogProps.blurStyleOption.has_value()) {
        BlurStyleOption blurStyleOption = dialogProps.blurStyleOption.value();
        Color inactiveColor = blurStyleOption.inactiveColor;
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, inactiveColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                              const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);

            Color inactiveColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, inactiveColor);
            inactiveColor = state ? inactiveColor : Color::TRANSPARENT;

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            auto currentBackBlurStyle = contentRenderContext->GetBackBlurStyle();
            CHECK_NULL_VOID(currentBackBlurStyle.has_value());
            currentBackBlurStyle->inactiveColor = inactiveColor;
            contentRenderContext->UpdateBackBlurStyle(currentBackBlurStyle);
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.blurStyleOption.inactiveColor", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        blurStyleOption.inactiveColor = inactiveColor;
        contentRenderContext->UpdateBackBlurStyle(blurStyleOption);
    }
}

void UpdateAndAddEffectOptionColorCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    if (dialogProps.effectOption.has_value()) {
        EffectOption effectOption = dialogProps.effectOption.value();

        Color color = effectOption.color;
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                                   const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);

            Color color;
            auto state = ResourceParseUtils::ParseResColor(resObj, color);
            color = state ? color : Color::TRANSPARENT;

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            auto effectOption = contentRenderContext->GetBackgroundEffect();
            effectOption->color = color;
            contentRenderContext->UpdateBackgroundEffect(effectOption);
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.effectOption.color", resObj, std::move(updateFunc));

        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto currentEffectOption = contentRenderContext->GetBackgroundEffect();
        CHECK_NULL_VOID(currentEffectOption.has_value());
        currentEffectOption->color = color;
        contentRenderContext->UpdateBackgroundEffect(currentEffectOption);
    }
}

void UpdateAndAddEffectOptionCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    UpdateAndAddEffectOptionColorCallback(dialog, dialogProps);
    if (dialogProps.effectOption.has_value()) {
        EffectOption effectOption = dialogProps.effectOption.value();
        
        Color inactiveColor = effectOption.inactiveColor;
        RefPtr<ResourceObject> resObj;
        ResourceParseUtils::CompleteResourceObjectFromColor(resObj, inactiveColor, dialog->GetTag());
        auto updateFunc = [dialogWeak = AceType::WeakClaim(AceType::RawPtr(dialog))](
                                           const RefPtr<ResourceObject>& resObj) {
            auto dialog = dialogWeak.Upgrade();
            CHECK_NULL_VOID(dialog);

            Color inactiveColor;
            auto state = ResourceParseUtils::ParseResColor(resObj, inactiveColor);
            inactiveColor = state ? inactiveColor : Color::TRANSPARENT;

            auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
            CHECK_NULL_VOID(contentNode);
            auto contentRenderContext = contentNode->GetRenderContext();
            CHECK_NULL_VOID(contentRenderContext);
            auto effectOption = contentRenderContext->GetBackgroundEffect();
            effectOption->inactiveColor = inactiveColor;
            contentRenderContext->UpdateBackgroundEffect(effectOption);
            contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            contentNode->MarkModifyDone();
        };
        auto pattern = dialog->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->AddResObj("dialog.effectOption.inactiveColor", resObj, std::move(updateFunc));
        
        auto contentNode = AceType::DynamicCast<FrameNode>(dialog->GetFirstChild());
        CHECK_NULL_VOID(contentNode);
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto currentEffectOption = contentRenderContext->GetBackgroundEffect();
        CHECK_NULL_VOID(currentEffectOption.has_value());
        currentEffectOption->inactiveColor = inactiveColor;
        contentRenderContext->UpdateBackgroundEffect(currentEffectOption);
    }
}
void AddColorModeChangeCallback(RefPtr<FrameNode> dialog, const DialogProperties& dialogProps)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    UpdateAndAddMaskColorCallback(dialog, dialogProps);

    UpdateAndAddShadowCallback(dialog, dialogProps);

    if (dialogProps.customStyle) {
        return;
    }

    UpdateAndAddBackgroundColorCallback(dialog, dialogProps);

    UpdateAndAddBorderColorCallback(dialog, dialogProps);

    UpdateAndAddBlurStyleOptionCallback(dialog, dialogProps);

    UpdateAndAddEffectOptionCallback(dialog, dialogProps);
}

RefPtr<FrameNode> DialogView::CreateDialogNode(
    const int32_t nodeId, const DialogProperties& param, const RefPtr<UINode>& customNode = nullptr)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);

    std::string tag = GetDialogTag(param);
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(tag, nodeId,
        AceType::MakeRefPtr<DialogPattern>(dialogTheme, customNode));

    if (customNode) {
        customNode->Build(nullptr);
    }

    // update layout and render props
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
    CHECK_NULL_RETURN(dialogLayoutProp, dialog);
    DialogAlignment align = static_cast<DialogAlignment>(dialogTheme->GetAlignDialog());
    if (param.alignment == DialogAlignment::DEFAULT && align == DialogAlignment::CENTER) {
        dialogLayoutProp->UpdateDialogAlignment(align);
    } else {
        dialogLayoutProp->UpdateDialogAlignment(param.alignment);
    }
    dialogLayoutProp->UpdateDialogOffset(param.offset);
    dialogLayoutProp->UpdateUseCustomStyle(param.customStyle);
    dialogLayoutProp->UpdateAutoCancel(param.autoCancel);
    dialogLayoutProp->UpdateShowInSubWindow(param.isShowInSubWindow);
    dialogLayoutProp->UpdateDialogButtonDirection(param.buttonDirection);
    dialogLayoutProp->UpdateIsModal(param.isModal);
    dialogLayoutProp->UpdateIsSceneBoardDialog(param.isSceneBoardDialog);
    if (param.width.has_value() && NonNegative(param.width.value().Value())) {
        dialogLayoutProp->UpdateWidth(param.width.value());
    } else {
        dialogLayoutProp->UpdateGridCount(param.gridCount);
    }
    if (param.height.has_value() && NonNegative(param.height.value().Value())) {
        dialogLayoutProp->UpdateHeight(param.height.value());
    }
    if (param.enableHoverMode.has_value()) {
        dialogLayoutProp->UpdateEnableHoverMode(param.enableHoverMode.value());
    }
    if (param.hoverModeArea.has_value()) {
        dialogLayoutProp->UpdateHoverModeArea(param.hoverModeArea.value());
    }
    // create gray background
    auto dialogContext = dialog->GetRenderContext();
    CHECK_NULL_RETURN(dialogContext, dialog);
    auto pattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(pattern, dialog);
    pattern->SetDialogProperties(param);
    auto isSubwindow = dialogLayoutProp->GetShowInSubWindowValue(false) && !pattern->IsUIExtensionSubWindow();
    if (isSubwindow || !dialogLayoutProp->GetIsModal().value_or(true)) {
        dialogContext->UpdateBackgroundColor(Color(0x00000000));
    } else {
        dialogContext->UpdateBackgroundColor(param.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
    }
    if (dialogLayoutProp->GetIsSceneBoardDialog().value_or(false)) {
        dialogContext->UpdateBackgroundColor(param.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
    }
    SetDialogAccessibilityHoverConsume(dialog);
    // set onCancel callback
    auto hub = dialog->GetEventHub<DialogEventHub>();
    CHECK_NULL_RETURN(hub, dialog);
    hub->SetOnCancel(param.onCancel);
    hub->SetOnSuccess(param.onSuccess);

    pattern->BuildChild(param);
    pattern->SetOnWillDismiss(param.onWillDismiss);
    pattern->SetOnWillDismissByNDK(param.onWillDismissCallByNDK);
    pattern->SetOnWillDismissRelease(param.onWillDismissRelease);

    SetDialogTransitionEffects(dialog, param, pattern);

    AddColorModeChangeCallback(dialog, param);
    dialog->MarkModifyDone();
    return dialog;
}

std::string DialogView::GetDialogTag(const DialogProperties& param)
{
    std::string tag;
    switch (param.type) {
        case DialogType::ALERT_DIALOG: {
            tag = V2::ALERT_DIALOG_ETS_TAG;
            break;
        }
        case DialogType::ACTION_SHEET: {
            tag = V2::ACTION_SHEET_DIALOG_ETS_TAG;
            break;
        }
        default:
            tag = V2::DIALOG_ETS_TAG;
            break;
    }
    return tag;
}

void DialogView::SetDialogAccessibilityHoverConsume(const RefPtr<FrameNode>& dialog)
{
    auto dialogAccessibilityProperty = dialog->GetAccessibilityProperty<DialogAccessibilityProperty>();
    CHECK_NULL_VOID(dialogAccessibilityProperty);
    dialogAccessibilityProperty->SetAccessibilityHoverConsume(
        [weak = AceType::WeakClaim(AceType::RawPtr(dialog))](const NG::PointF& point) {
            auto dialogNode = weak.Upgrade();
            CHECK_NULL_RETURN(dialogNode, true);
            auto dialogLayoutProp = dialogNode->GetLayoutProperty<DialogLayoutProperty>();
            CHECK_NULL_RETURN(dialogLayoutProp, true);
            auto pattern = dialogNode->GetPattern<DialogPattern>();
            CHECK_NULL_RETURN(pattern, true);
            if (!dialogLayoutProp->GetIsModal().value_or(true) ||
                (dialogLayoutProp->GetShowInSubWindowValue(false) && !pattern->IsUIExtensionSubWindow())) {
                return false;
            }
            return true;
        });
}

} // namespace OHOS::Ace::NG

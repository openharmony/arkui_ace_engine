/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/pipeline/pipeline_base.h"

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
    if (dialogLayoutProp->GetShowInSubWindowValue(false) || !dialogLayoutProp->GetIsModal().value_or(true)) {
        dialogContext->UpdateBackgroundColor(Color(0x00000000));
    } else {
        dialogContext->UpdateBackgroundColor(param.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
    }
    if (dialogLayoutProp->GetIsSceneBoardDialog().value_or(false)) {
        dialogContext->UpdateBackgroundColor(param.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
    }
    SetDialogAccessibilityHoverConsume(dialog);
    // set onCancel callback
    auto hub = dialog->GetOrCreateEventHub<DialogEventHub>();
    CHECK_NULL_RETURN(hub, dialog);
    hub->SetOnCancel(param.onCancel);
    hub->SetOnSuccess(param.onSuccess);
    pattern->BuildChild(param);
    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObj(dialog, param);
    }
    pattern->SetOnWillDismiss(param.onWillDismiss);
    pattern->SetOnWillDismissByNDK(param.onWillDismissCallByNDK);

    SetDialogTransitionEffects(dialog, param, pattern);

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

void DialogView::SetMaskColorWithResourceObj(const RefPtr<FrameNode>& frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.maskColor";
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            return;
        }
        pattern->UpdateDialogColor(result, DialogResourceType::MASK_COLOR);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetWidthWithResourceObj(const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.width";
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(node))](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto dialogContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(dialogContext);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVpNG(resObj, result)) {
            return;
        }
        pattern->UpdateLayoutContent(result, DialogResourceType::WIDTH);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetHeightWithResourceObj(const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(node && resObj);
    auto pattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.height";
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(node))](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVpNG(resObj, result)) {
            return;
        }
        pattern->UpdateLayoutContent(result, DialogResourceType::HEIGHT);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetOffsetWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.offset";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        DimensionOffset& offsetValue = const_cast<DimensionOffset&>(param.offset);
        offsetValue.ReloadResources();
        auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(frameNode->GetLayoutProperty());
        CHECK_NULL_VOID(dialogLayoutProp);
        dialogLayoutProp->UpdateDialogOffset(offsetValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetShadowWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.shadow";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.shadow.has_value()) {
            return;
        }
        Shadow& shadowValue = const_cast<Shadow&>(param.shadow.value());
        shadowValue.ReloadResources();
        pattern->UpdateBackShadow(shadowValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetEffectWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.effectOption";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.effectOption.has_value()) {
            return;
        }
        EffectOption& optionValue = const_cast<EffectOption&>(param.effectOption.value());
        optionValue.ReloadResources();
        pattern->UpdateEffect(optionValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetBackgroundColorWithResourceObj(const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(node);
    std::string key = "dialog.backgroundColor";
    auto pattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(pattern);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(node)), key](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            return;
        }
        pattern->UpdateDialogColor(result, DialogResourceType::BACKGROUND_COLOR);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetBlurStyleWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.blurStyle";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.blurStyleOption.has_value()) {
            return;
        }
        BlurStyleOption& optionValue = const_cast<BlurStyleOption&>(param.blurStyleOption.value());
        optionValue.ReloadResources();
        pattern->UpdateBlurStyle(optionValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetMaskRectWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.maskRect";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.maskRect.has_value()) {
            return;
        }
        DimensionRect& maskRectValue = const_cast<DimensionRect&>(param.maskRect.value());
        maskRectValue.ReloadResources();
        auto width = maskRectValue.GetWidth();
        auto height = maskRectValue.GetHeight();
        if (width.IsValid() && height.IsValid()) {
            pattern->UpdateMaskRect(maskRectValue);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetBorderWidthWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.borderWidth";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.borderWidth.has_value()) {
            return;
        }
        NG::BorderWidthProperty& borderWidthValue = const_cast<NG::BorderWidthProperty&>(param.borderWidth.value());
        borderWidthValue.ReloadResources();
        pattern->UpdateBorderWidth(borderWidthValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetBorderColorWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.borderColor";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.borderColor.has_value()) {
            return;
        }
        NG::BorderColorProperty& borderColorValue = const_cast<NG::BorderColorProperty&>(param.borderColor.value());
        borderColorValue.ReloadResources();
        pattern->UpdateBorderColor(borderColorValue);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::SetCornerRadiusWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::string key = "dialog.cornerRadius";
    pattern->RemoveResObj(key);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [param, weak = AceType::WeakClaim(AceType::RawPtr(node))](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (!param.borderRadius.has_value()) {
            return;
        }
        NG::BorderRadiusProperty& cornerRadiusVal = const_cast<NG::BorderRadiusProperty&>(param.borderRadius.value());
        cornerRadiusVal.ReloadResources();
        pattern->UpdateCornerRadius(cornerRadiusVal);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void DialogView::CreateWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param)
{
    CHECK_NULL_VOID(node);
    SetBackgroundColorWithResourceObj(node, param.resourceBgColorObj);
    SetMaskColorWithResourceObj(node, param.resourceMaskColorObj);
    SetWidthWithResourceObj(node, param.resourceWidthObj);
    SetHeightWithResourceObj(node, param.resourceHeightObj);
    SetOffsetWithResourceObj(node, param);
    SetShadowWithResourceObj(node, param);
    SetEffectWithResourceObj(node, param);
    SetBlurStyleWithResourceObj(node, param);
    SetMaskRectWithResourceObj(node, param);
    SetBorderWidthWithResourceObj(node, param);
    SetBorderColorWithResourceObj(node, param);
    SetCornerRadiusWithResourceObj(node, param);
}
} // namespace OHOS::Ace::NG

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
    dialogLayoutProp->UpdateEnableHoverMode(param.enableHoverMode);
    if (param.width.has_value() && NonNegative(param.width.value().Value())) {
        dialogLayoutProp->UpdateWidth(param.width.value());
    } else {
        dialogLayoutProp->UpdateGridCount(param.gridCount);
    }
    if (param.height.has_value() && NonNegative(param.height.value().Value())) {
        dialogLayoutProp->UpdateHeight(param.height.value());
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
    auto hub = dialog->GetEventHub<DialogEventHub>();
    CHECK_NULL_RETURN(hub, dialog);
    hub->SetOnCancel(param.onCancel);
    hub->SetOnSuccess(param.onSuccess);

    pattern->BuildChild(param);
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

} // namespace OHOS::Ace::NG

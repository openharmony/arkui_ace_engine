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

#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/device_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {

const char SEPARATE[] = " ";

} // namespace

RefPtr<FrameNode> DialogView::CreateDialogNode(const DialogProperties& param)
{
    auto dialogNode = DialogView::CreateDialogWithType(param.type);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_RETURN(dialogLayoutProp, dialogNode);
    dialogLayoutProp->UpdateDialogAlignment(param.alignment);
    dialogLayoutProp->UpdateDialogOffset(param.offset);
    dialogLayoutProp->UpdateGridCount(param.gridCount);
    auto dialogRenderProp = dialogNode->GetPaintProperty<DialogRenderProperty>();
    CHECK_NULL_RETURN(dialogRenderProp, dialogNode);
    dialogRenderProp->UpdateAutoCancel(param.autoCancel);
    dialogRenderProp->UpdateUseCustomStyle(param.customStyle);
    auto dialogContext = dialogNode->GetRenderContext();
    CHECK_NULL_RETURN(dialogContext, dialogNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, dialogNode);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, dialogNode);
    auto dialogTheme = themeManager->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, dialogNode);
    dialogContext->UpdateBackgroundColor(dialogTheme->GetMaskColorEnd());
    // data used for inspector
    std::string data;
    BuildChild(dialogNode, param, data, dialogTheme, themeManager);
    BuildButtons(themeManager, dialogNode, param.buttons, dialogTheme, data);
    dialogNode->MarkModifyDone();
    // TODO: build animation.
    // TODO: menu event not completed.
    return dialogNode;
}

RefPtr<FrameNode> DialogView::CreateDialogWithType(DialogType type)
{
    RefPtr<FrameNode> dialog;
    // Create different dialog according to type.
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    switch (type) {
        case DialogType::ALERT_DIALOG: {
            // Alert dialog need to be completed.
            break;
        }
        case DialogType::ACTION_SHEET: {
            // Action sheet need to be completed.
            break;
        }
        default:
            dialog = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>());
            break;
    }
    return dialog;
}

void DialogView::BuildChild(const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProperties,
    std::string& data, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<ThemeManager>& themeManager)
{
    bool isCustom = dialogProperties.customStyle;
    if (isCustom) {
        // TODO: custom dialog not completed
        return;
    }
    auto deviceType = SystemProperties::GetDeviceType();
    // Make Title node
    auto title = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(title->GetLayoutProperty());
    CHECK_NULL_VOID(titleProp);
    titleProp->UpdateMaxLines(dialogTheme->GetTitleMaxLines());
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(dialogTheme->GetTitleTextStyle().GetFontSize());
    titleProp->UpdateAdaptMinFontSize(dialogTheme->GetTitleMinFontSize());
    titleProp->UpdateContent(dialogProperties.title);
    data += dialogProperties.title + SEPARATE;
    PaddingProperty titlePadding;
    auto paddingInTheme = (dialogProperties.content.empty() && dialogProperties.buttons.empty())
                              ? dialogTheme->GetTitleDefaultPadding()
                              : dialogTheme->GetTitleAdjustPadding();
    titlePadding.left = CalcLength(paddingInTheme.Left());
    titlePadding.right = CalcLength(paddingInTheme.Right());
    titlePadding.top = CalcLength(paddingInTheme.Top());
    titlePadding.bottom = CalcLength(paddingInTheme.Bottom());
    titleProp->UpdatePadding(titlePadding);
    // Make Content node
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto contentProp = AceType::DynamicCast<TextLayoutProperty>(contentNode->GetLayoutProperty());
    CHECK_NULL_VOID(contentProp);
    if (deviceType == DeviceType::WATCH) {
        // TODO: prefer size not completed.
        contentProp->UpdateTextAlign(TextAlign::CENTER);
    }
    contentProp->UpdateContent(dialogProperties.content);
    data += dialogProperties.content + SEPARATE;
    Edge contentPaddingInTheme;
    if (!dialogProperties.title.empty()) {
        contentPaddingInTheme =
            dialogProperties.buttons.empty() ? dialogTheme->GetDefaultPadding() : dialogTheme->GetAdjustPadding();
    } else {
        contentPaddingInTheme = dialogProperties.buttons.empty() ? dialogTheme->GetContentDefaultPadding()
                                                                 : dialogTheme->GetContentAdjustPadding();
    }
    PaddingProperty contentPadding;
    contentPadding.left = CalcLength(contentPaddingInTheme.Left());
    contentPadding.right = CalcLength(contentPaddingInTheme.Right());
    contentPadding.top = CalcLength(contentPaddingInTheme.Top());
    contentPadding.bottom = CalcLength(contentPaddingInTheme.Bottom());
    // Make scroll node
    auto contentScroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    if (deviceType == DeviceType::WATCH) {
        contentProp->UpdatePadding(contentPadding);
    } else {
        auto scrollProp = contentScroll->GetLayoutProperty();
        scrollProp->UpdatePadding(contentPadding);
        // TODO: shrink need to be completed
        scrollProp->UpdateFlexShrink(1.0);
    }
    // Make Menu node if hasMenu
    if (dialogProperties.isMenu) {
        // TODO: make menu node
        LOGD("Menu is not Completed");
    } else {
        // TODO: build button
        LOGD("button is not completed.");
    }
    // TODO: need to check if Focusable is need in DialogView
    // TODO: need to check if FocusCollaboration is need in DialogView
    // Make dialog Content Column
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto contentRenderContext = contentColumn->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    auto columnProp = AceType::DynamicCast<LinearLayoutProperty>(contentColumn->GetLayoutProperty());
    CHECK_NULL_VOID(columnProp);
    contentRenderContext->UpdateBackgroundColor(dialogTheme->GetBackgroundColor());
    // content is full screen in Watch mode
    if (deviceType == DeviceType::WATCH) {
        columnProp->UpdateMeasureType(MeasureType::MATCH_PARENT);
    } else {
        columnProp->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    }
    // TODO: Content box need animation
    // TODO: need to check TextDirection.
    // Begin to composite FrameNodes
    contentColumn->AddChild(title);
    contentColumn->AddChild(contentScroll);
    contentScroll->AddChild(contentNode);
    dialog->AddChild(contentColumn);
}

void DialogView::BuildButtons(const RefPtr<ThemeManager>& themeManager, const RefPtr<FrameNode>& dialog,
    const std::vector<ButtonInfo>& buttons, const RefPtr<DialogTheme>& dialogTheme, std::string& data)
{
    // TODO: Frame Node Create logic may be moved to this function.
    LOGI("build buttons");
}

} // namespace OHOS::Ace::NG
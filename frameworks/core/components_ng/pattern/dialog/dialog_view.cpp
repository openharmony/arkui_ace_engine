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
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
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

RefPtr<FrameNode> DialogView::CreateDialogNode(
    const DialogProperties& param, const RefPtr<UINode>& customNode = nullptr)
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
    BuildChild(dialogNode, param, data, dialogTheme, customNode);

    BuildButtons(param.buttons, dialogTheme, dialogNode);
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
            dialog =
                FrameNode::CreateFrameNode(V2::ALERTDIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>());
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
    std::string& data, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<UINode>& customNode = nullptr)
{
    LOGI("build dialog child");
    // append customNode
    if (customNode) {
        if (!AceType::InstanceOf<CustomNode>(customNode)) {
            LOGE("dialogNode's child isn't FrameNode");
        }
        auto contentNode = AceType::DynamicCast<FrameNode>(customNode->GetChildAtIndex(0));
        auto contentRenderContext = contentNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        contentRenderContext->UpdateBackgroundColor(dialogTheme->GetBackgroundColor());
        customNode->MountToParent(dialog);
        LOGD("customNode tag = %s mounted to dialog", customNode->GetTag().c_str());
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
    LOGD("content = %s", dialogProperties.content.c_str());
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
    // NOT SHOWing inside scroll, need to fix scroll
    contentColumn->AddChild(contentNode);

    // Make Menu node if hasMenu
    if (dialogProperties.isMenu) {
        // TODO: make menu node
        LOGD("Menu is not Completed");
    } else {
        auto buttonContainer = BuildButtons(dialogProperties.buttons, dialogTheme, dialog);
        CHECK_NULL_VOID(buttonContainer);
        buttonContainer->MountToParent(contentColumn);
    }

    dialog->AddChild(contentColumn);
}

// alert dialog buttons
RefPtr<FrameNode> DialogView::BuildButtons(
    const std::vector<ButtonInfo>& buttons, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode>& dialog)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> container;
    if (buttons.size() == 1) { // the button in dialog is one.
        container = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    } else if (buttons.size() == 2) { // the button in dialog is two.
        container = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        auto layoutProps = container->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    } else { // the button in dialog is more than two.
        // TODO: use wrap pattern
    }
    CHECK_NULL_RETURN(container, nullptr);
    // set action's padding
    PaddingProperty actionPadding;
    auto padding = dialogTheme->GetActionsPadding();
    actionPadding.left = CalcLength(padding.Left());
    actionPadding.right = CalcLength(padding.Right());
    actionPadding.top = CalcLength(padding.Top());
    actionPadding.bottom = CalcLength(padding.Bottom());
    container->GetLayoutProperty()->UpdatePadding(actionPadding);

    for (auto&& params : buttons) {
        ButtonView::CreateWithLabel(params.text);
        if (!params.textColor.empty()) {
            ButtonView::SetTextColor(Color::FromString(params.textColor));
        }
        auto buttonNode = ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_RETURN(buttonNode, nullptr);

        // bind click event
        auto buttonFrame = AceType::DynamicCast<FrameNode>(buttonNode);
        auto hub = buttonFrame->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(hub, nullptr);
        hub->AddClickEvent(params.action);

        // to close dialog when clicked inside button rect
        auto closeCallback = [dialog](GestureEvent& /*info*/) {
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(context);
            auto overlayManager = context->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);

            overlayManager->CloseDialog(dialog);
        };
        hub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(closeCallback));

        // update background color
        if (params.isBgColorSetted) {
            auto renderContext = buttonFrame->GetRenderContext();
            renderContext->UpdateBackgroundColor(params.bgColor);
        }

        buttonNode->MountToParent(container);
    }
    return container;
}

} // namespace OHOS::Ace::NG
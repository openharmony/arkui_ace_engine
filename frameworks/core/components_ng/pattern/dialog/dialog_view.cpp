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
#include "base/memory/referenced.h"
#include "base/utils/device_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_view.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {

const char SEPARATE[] = " ";

constexpr Dimension SHEET_IMAGE_SIZE = 40.0_vp;
constexpr Dimension SHEET_IMAGE_PADDING = 16.0_vp;
constexpr Dimension SHEET_DIVIDER_WIDTH = 1.0_px;
constexpr Dimension SHEET_LIST_PADDING = 24.0_vp;

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
    dialogLayoutProp->UpdateUseCustom(param.useCustom);
    auto dialogRenderProp = dialogNode->GetPaintProperty<DialogRenderProperty>();
    CHECK_NULL_RETURN(dialogRenderProp, dialogNode);
    dialogRenderProp->UpdateAutoCancel(param.autoCancel);
    dialogRenderProp->UpdateUseCustomStyle(param.customStyle);
    auto dialogContext = dialogNode->GetRenderContext();
    CHECK_NULL_RETURN(dialogContext, dialogNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, dialogNode);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, dialogNode);
    dialogContext->UpdateBackgroundColor(dialogTheme->GetMaskColorEnd());
    // data used for inspector
    std::string data;
    BuildChild(dialogNode, param, data, dialogTheme, customNode);
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
            dialog = FrameNode::CreateFrameNode(
                V2::ACTIONSHEETDIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>());
            break;
        }
        default:
            dialog = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>());
            break;
    }
    return dialog;
}

// set render context properties of content frame
void UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const RefPtr<DialogTheme>& theme)
{
    auto contentRenderContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    contentRenderContext->UpdateBackgroundColor(theme->GetBackgroundColor());

    BorderRadiusProperty radius;
    radius.SetRadius(theme->GetRadius().GetX());
    contentRenderContext->UpdateBorderRadius(radius);
}

void DialogView::BuildChild(const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProperties,
    std::string& data, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<UINode>& customNode = nullptr)
{
    LOGI("build dialog child");
    // append customNode
    if (customNode) {
        if (!AceType::InstanceOf<CustomNode>(customNode)) {
            LOGE("dialogNode's child isn't FrameNode");
            return;
        }
        auto contentNode = AceType::DynamicCast<FrameNode>(customNode->GetChildAtIndex(0));
        UpdateContentRenderContext(contentNode, dialogTheme);
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
    UpdateContentRenderContext(contentColumn, dialogTheme);

    auto columnProp = AceType::DynamicCast<LinearLayoutProperty>(contentColumn->GetLayoutProperty());
    CHECK_NULL_VOID(columnProp);
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

    // build ActionSheet child
    if (dialogProperties.type == DialogType::ACTION_SHEET) {
        auto sheetContainer = BuildSheet(dialogProperties.sheetsInfo, dialogTheme, dialog);
        CHECK_NULL_VOID(sheetContainer);
        sheetContainer->MarkModifyDone();
        sheetContainer->MountToParent(contentColumn);
    }

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

// to close dialog when clicked
void BindCloseCallBack(const RefPtr<GestureEventHub> hub, const RefPtr<FrameNode>& dialog)
{
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
}

RefPtr<UINode> CreateButton(const ButtonInfo& params, const RefPtr<FrameNode>& dialog)
{
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
    BindCloseCallBack(hub, dialog);

    // update background color
    if (params.isBgColorSetted) {
        auto renderContext = buttonFrame->GetRenderContext();
        renderContext->UpdateBackgroundColor(params.bgColor);
    }
    return buttonNode;
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
        auto buttonNode = CreateButton(params, dialog);
        buttonNode->MountToParent(container);
    }
    return container;
}

RefPtr<FrameNode> BuildSheetItem(
    const ActionSheetInfo& item, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode>& dialog)
{
    // ListItem -> Row -> title + icon
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> itemNode =
        FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, Id, AceType::MakeRefPtr<ListItemPattern>(nullptr));
    CHECK_NULL_RETURN(itemNode, nullptr);

    // update sheet row flex align
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto itemRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, rowId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(itemRow, nullptr);
    auto layoutProps = itemRow->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    // mount icon
    if (!item.icon.empty()) {
        auto iconId = ElementRegister::GetInstance()->MakeUniqueId();
        auto imageSrc = ImageSourceInfo(item.icon, SHEET_IMAGE_SIZE, SHEET_IMAGE_SIZE);
        auto iconNode =
            FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, iconId, AceType::MakeRefPtr<ImagePattern>(imageSrc));
        CHECK_NULL_RETURN(iconNode, nullptr);
        // add image padding
        CalcLength padding(SHEET_IMAGE_PADDING.ConvertToPx());
        PaddingProperty imagePadding = {
            .left = padding,
            .right = padding,
            .top = padding,
            .bottom = padding,
        };
        iconNode->GetLayoutProperty()->UpdatePadding(imagePadding);

        iconNode->MountToParent(itemRow);
    }

    // mount title
    if (!item.title.empty()) {
        auto titleId = ElementRegister::GetInstance()->MakeUniqueId();
        auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleId, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(titleNode, nullptr);
        // update text style
        auto style = dialogTheme->GetContentTextStyle();
        auto props = titleNode->GetLayoutProperty<TextLayoutProperty>();
        props->UpdateContent(item.title);
        props->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        props->UpdateAdaptMaxFontSize(style.GetFontSize());
        props->UpdateAdaptMinFontSize(dialogTheme->GetTitleMinFontSize());
        props->UpdateMaxLines(style.GetMaxLines());

        titleNode->MountToParent(itemRow);
    }
    // set sheetItem action
    auto hub = itemRow->GetOrCreateGestureEventHub();
    hub->AddClickEvent(item.action);
    // close dialog when clicked
    BindCloseCallBack(hub, dialog);

    itemRow->MountToParent(itemNode);
    return itemNode;
}

RefPtr<FrameNode> DialogView::BuildSheet(
    const std::vector<ActionSheetInfo>& sheets, const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode> dialog)
{
    LOGI("start building action sheet items");
    auto listId = ElementRegister::GetInstance()->MakeUniqueId();
    auto list = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, listId, AceType::MakeRefPtr<ListPattern>());
    CHECK_NULL_RETURN(list, nullptr);

    // set sheet padding
    CalcLength padding(SHEET_LIST_PADDING.ConvertToPx());
    PaddingProperty sheetPadding = {
        .left = padding,
        .right = padding,
        .top = padding,
        .bottom = padding,
    };
    auto listFrame = AceType::DynamicCast<FrameNode>(list);
    listFrame->GetLayoutProperty()->UpdatePadding(sheetPadding);

    for (auto&& item : sheets) {
        auto itemNode = BuildSheetItem(item, dialogTheme, dialog);
        CHECK_NULL_RETURN(itemNode, nullptr);
        list->AddChild(itemNode);
    }

    // set list divider
    auto divider = V2::ItemDivider {
        .strokeWidth = SHEET_DIVIDER_WIDTH,
        .color = Color::GRAY,
    };
    auto props = list->GetLayoutProperty<ListLayoutProperty>();
    props->UpdateDivider(divider);
    props->UpdateListDirection(Axis::VERTICAL);
    return list;
}

} // namespace OHOS::Ace::NG
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

#include "core/components_ng/pattern/dialog/dialog_pattern.h"

#include <climits>
#include <cstdint>

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr Dimension SHEET_IMAGE_PADDING = 16.0_vp;
constexpr Dimension SHEET_DIVIDER_WIDTH = 1.0_px;
constexpr Dimension SHEET_LIST_PADDING = 24.0_vp;
const CalcLength SHEET_IMAGE_SIZE(40.0_vp);

RefPtr<FrameNode> CreateButtonText(const std::string& text, const std::string& color)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->SetInternal();
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textProps = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, nullptr);
    textProps->UpdateContent(text);
    if (!color.empty()) {
        textProps->UpdateTextColor(Color::FromString(color));
    } else {
        textProps->UpdateTextColor(Color::BLUE);
    }
    textNode->SetInternal();
    return textNode;
}

} // namespace

void DialogPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitTouchEvent(gestureHub);
}

void DialogPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent);
}

void DialogPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    if (touchType == TouchType::UP) {
        HandleTouchUp(clickPos);
    }
}

void DialogPattern::HandleTouchUp(const Offset& clickPosition)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dialogRenderProp = host->GetPaintProperty<DialogRenderProperty>();
    CHECK_NULL_VOID(dialogRenderProp);
    auto autoCancel = dialogRenderProp->GetAutoCancel().value_or(true);
    if (autoCancel) {
        auto content = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(content);
        auto contentRect = content->GetGeometryNode()->GetFrameRect();
        // close dialog if clicked outside content rect
        if (!contentRect.IsInRegion(PointF(clickPosition.GetX(), clickPosition.GetY()))) {
            PopDialog(-1);
        }
    }
}

void DialogPattern::PopDialog(int32_t buttonIdx = -1)
{
    LOGI("DialogPattern::PopDialog from click");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto hub = host->GetEventHub<DialogEventHub>();
    if (buttonIdx != -1) {
        hub->FireSuccessEvent(buttonIdx);
    } else {
        // trigger onCancel callback
        hub->FireCancelEvent();
    }

    overlayManager->CloseDialog(host);
}

// set render context properties of content frame
void DialogPattern::UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const RefPtr<DialogTheme>& theme)
{
    auto contentRenderContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    contentRenderContext->UpdateBackgroundColor(theme->GetBackgroundColor());

    BorderRadiusProperty radius;
    radius.SetRadius(theme->GetRadius().GetX());
    contentRenderContext->UpdateBorderRadius(radius);
}

void DialogPattern::BuildChild(const DialogProperties& dialogProperties)
{
    LOGI("build dialog child");
    // append customNode
    if (customNode_) {
        // wrap custom node to set background color and round corner
        auto contentWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
        CHECK_NULL_VOID(contentWrapper);
        UpdateContentRenderContext(contentWrapper, dialogTheme_);
        customNode_->MountToParent(contentWrapper);
        auto dialog = GetHost();
        contentWrapper->MountToParent(dialog);
        return;
    }

    // Make dialog Content Column
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(contentColumn);

    auto title = BuildTitle(dialogProperties);
    CHECK_NULL_VOID(title);
    contentColumn->AddChild(title);

    auto content = BuildContent(dialogProperties);
    CHECK_NULL_VOID(content);
    contentColumn->AddChild(content);
    UpdateContentRenderContext(contentColumn, dialogTheme_);

    auto columnProp = AceType::DynamicCast<LinearLayoutProperty>(contentColumn->GetLayoutProperty());
    CHECK_NULL_VOID(columnProp);
    // content is full screen in Watch mode
    auto deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::WATCH) {
        columnProp->UpdateMeasureType(MeasureType::MATCH_PARENT);
    } else {
        columnProp->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    }

    // build ActionSheet child
    if (dialogProperties.type == DialogType::ACTION_SHEET && !dialogProperties.sheetsInfo.empty()) {
        auto sheetContainer = BuildSheet(dialogProperties.sheetsInfo);
        CHECK_NULL_VOID(sheetContainer);
        sheetContainer->MountToParent(contentColumn);
        sheetContainer->MarkModifyDone();
    }

    // Make Menu node if hasMenu
    if (dialogProperties.isMenu) {
        auto menu = BuildMenu(dialogProperties.buttons);
        CHECK_NULL_VOID(menu);
        menu->MountToParent(contentColumn);
    } else {
        // build buttons
        if (!dialogProperties.buttons.empty()) {
            auto buttonContainer = BuildButtons(dialogProperties.buttons);
            CHECK_NULL_VOID(buttonContainer);
            buttonContainer->MountToParent(contentColumn);
        }
    }

    auto dialog = GetHost();
    contentColumn->MountToParent(dialog);
}

RefPtr<FrameNode> DialogPattern::BuildTitle(const DialogProperties& dialogProperties)
{
    // Make Title node
    auto title = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(title->GetLayoutProperty());
    CHECK_NULL_RETURN(titleProp, nullptr);
    titleProp->UpdateMaxLines(dialogTheme_->GetTitleMaxLines());
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(dialogTheme_->GetTitleTextStyle().GetFontSize());
    titleProp->UpdateAdaptMinFontSize(dialogTheme_->GetTitleMinFontSize());
    titleProp->UpdateContent(dialogProperties.title);
    PaddingProperty titlePadding;
    auto paddingInTheme = (dialogProperties.content.empty() && dialogProperties.buttons.empty())
                              ? dialogTheme_->GetTitleDefaultPadding()
                              : dialogTheme_->GetTitleAdjustPadding();
    titlePadding.left = CalcLength(paddingInTheme.Left());
    titlePadding.right = CalcLength(paddingInTheme.Right());
    titlePadding.top = CalcLength(paddingInTheme.Top());
    titlePadding.bottom = CalcLength(paddingInTheme.Bottom());
    titleProp->UpdatePadding(titlePadding);

    // XTS inspector value
    title_ = dialogProperties.title;

    // actionSheet title needs to align flex start
    if (dialogProperties.type == DialogType::ACTION_SHEET) {
        auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(row, nullptr);
        auto rowProps = row->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(rowProps, nullptr);
        rowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
        rowProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        title->MountToParent(row);
        return row;
    }

    return title;
}

RefPtr<FrameNode> DialogPattern::BuildContent(const DialogProperties& dialogProperties)
{
    // Make Content node
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto contentProp = AceType::DynamicCast<TextLayoutProperty>(contentNode->GetLayoutProperty());
    CHECK_NULL_RETURN(contentProp, nullptr);
    auto deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::WATCH) {
        // TODO: prefer size not completed.
        contentProp->UpdateTextAlign(TextAlign::CENTER);
    }
    contentProp->UpdateContent(dialogProperties.content);
    LOGD("content = %s", dialogProperties.content.c_str());
    // update padding
    Edge contentPaddingInTheme;
    if (!dialogProperties.title.empty()) {
        contentPaddingInTheme =
            dialogProperties.buttons.empty() ? dialogTheme_->GetDefaultPadding() : dialogTheme_->GetAdjustPadding();
    } else {
        contentPaddingInTheme = dialogProperties.buttons.empty() ? dialogTheme_->GetContentDefaultPadding()
                                                                 : dialogTheme_->GetContentAdjustPadding();
    }
    PaddingProperty contentPadding;
    contentPadding.left = CalcLength(contentPaddingInTheme.Left());
    contentPadding.right = CalcLength(contentPaddingInTheme.Right());
    contentPadding.top = CalcLength(contentPaddingInTheme.Top());
    contentPadding.bottom = CalcLength(contentPaddingInTheme.Bottom());
    contentProp->UpdatePadding(contentPadding);

    // XTS inspector value
    message_ = dialogProperties.content;
    return contentNode;
}

// to close dialog when clicked, use button index in Prompt to trigger success callback
void DialogPattern::BindCloseCallBack(const RefPtr<GestureEventHub>& hub, int32_t buttonIdx)
{
    auto host = GetHost();
    auto closeCallback = [weak = WeakClaim(RawPtr(host)), buttonIdx](GestureEvent& /*info*/) {
        auto dialog = weak.Upgrade();
        CHECK_NULL_VOID(dialog);
        dialog->GetPattern<DialogPattern>()->PopDialog(buttonIdx);
    };

    hub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(closeCallback));
}

RefPtr<FrameNode> DialogPattern::CreateButton(const ButtonInfo& params, int32_t index)
{
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(buttonNode, nullptr);
    // append text inside button
    auto textNode = CreateButtonText(params.text, params.textColor);
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->MountToParent(buttonNode);

    auto hub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(hub, nullptr);
    // bind click event
    if (params.action) {
        hub->AddClickEvent(params.action);
    }

    // to close dialog when clicked inside button rect
    BindCloseCallBack(hub, index);

    // update background color
    if (params.isBgColorSetted) {
        auto renderContext = buttonNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);
        renderContext->UpdateBackgroundColor(params.bgColor);
    }
    buttonNode->SetInternal();
    return buttonNode;
}

// alert dialog buttons
RefPtr<FrameNode> DialogPattern::BuildButtons(const std::vector<ButtonInfo>& buttons)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> container;
    if (buttons.size() == 1) {
        container = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    } else {
        container = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        auto layoutProps = container->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    }

    CHECK_NULL_RETURN(container, nullptr);
    // set action's padding
    PaddingProperty actionPadding;
    auto padding = dialogTheme_->GetActionsPadding();
    actionPadding.left = CalcLength(padding.Left());
    actionPadding.right = CalcLength(padding.Right());
    actionPadding.top = CalcLength(padding.Top());
    actionPadding.bottom = CalcLength(padding.Bottom());
    container->GetLayoutProperty()->UpdatePadding(actionPadding);

    for (size_t i = 0; i < buttons.size(); ++i) {
        auto buttonNode = CreateButton(buttons[i], i);
        CHECK_NULL_RETURN(buttonNode, nullptr);
        buttonNode->MountToParent(container);
        buttonNode->MarkModifyDone();
    }
    return container;
}

RefPtr<FrameNode> DialogPattern::BuildSheetItem(const ActionSheetInfo& item)
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
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    // mount icon
    if (!item.icon.empty()) {
        auto iconId = ElementRegister::GetInstance()->MakeUniqueId();
        auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, iconId, AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_RETURN(iconNode, nullptr);
        // add image padding
        CalcLength padding(SHEET_IMAGE_PADDING.ConvertToPx());
        PaddingProperty imagePadding = {
            .left = padding,
            .right = padding,
            .top = padding,
            .bottom = padding,
        };
        auto iconProps = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        iconProps->UpdatePadding(imagePadding);
        LOGD("item icon src = %s", item.icon.c_str());
        auto imageSrc = ImageSourceInfo(item.icon);
        iconProps->UpdateImageSourceInfo(imageSrc);
        iconProps->UpdateUserDefinedIdealSize(CalcSize(SHEET_IMAGE_SIZE, SHEET_IMAGE_SIZE));
        iconNode->MountToParent(itemRow);
        iconNode->MarkModifyDone();
    }

    // mount title
    if (!item.title.empty()) {
        auto titleId = ElementRegister::GetInstance()->MakeUniqueId();
        auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleId, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(titleNode, nullptr);
        // update text style
        auto style = dialogTheme_->GetContentTextStyle();
        auto props = titleNode->GetLayoutProperty<TextLayoutProperty>();
        props->UpdateContent(item.title);
        props->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        props->UpdateAdaptMaxFontSize(style.GetFontSize());
        props->UpdateAdaptMinFontSize(dialogTheme_->GetTitleMinFontSize());
        props->UpdateMaxLines(style.GetMaxLines());

        titleNode->MountToParent(itemRow);
    }
    // set sheetItem action
    auto hub = itemRow->GetOrCreateGestureEventHub();
    if (item.action) {
        hub->AddClickEvent(item.action);
    }
    // close dialog when clicked
    BindCloseCallBack(hub, -1);

    itemRow->MountToParent(itemNode);
    return itemNode;
}

RefPtr<FrameNode> DialogPattern::BuildSheet(const std::vector<ActionSheetInfo>& sheets)
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
        auto itemNode = BuildSheetItem(item);
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

RefPtr<FrameNode> DialogPattern::BuildMenu(const std::vector<ButtonInfo>& buttons)
{
    auto menu = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(true));
    // column -> button
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto button = CreateButton(buttons[i], i);
        CHECK_NULL_RETURN(button, nullptr);
        auto props = DynamicCast<FrameNode>(button)->GetLayoutProperty();
        props->UpdateFlexGrow(1);
        props->UpdateFlexShrink(1);

        button->MountToParent(menu);
    }
    return menu;
}

// XTS inspector
void DialogPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetTag() == V2::ALERT_DIALOG_ETS_TAG || host->GetTag() == V2::ACTION_SHEET_DIALOG_ETS_TAG) {
        json->Put("title", title_.c_str());
        json->Put("message", message_.c_str());
    }
}

} // namespace OHOS::Ace::NG
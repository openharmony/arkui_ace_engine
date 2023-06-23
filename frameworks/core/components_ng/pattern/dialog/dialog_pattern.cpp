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
#include <cstring>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_type.h"
#include "core/common/container.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
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
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_view.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t SHEET_INFO_IDX = -2;
constexpr Dimension SHEET_IMAGE_MARGIN = 16.0_vp;
constexpr Dimension SHEET_DIVIDER_WIDTH = 1.0_px;
constexpr Dimension SHEET_LIST_PADDING = 24.0_vp;
constexpr Dimension DIALOG_BUTTON_TEXT_SIZE = 16.0_fp;
constexpr Color DEFAULT_BUTTON_COLOR = Color(0xff007dff);
const CalcLength SHEET_IMAGE_SIZE(40.0_vp);
constexpr int32_t TWO_BUTTON_MODE = 2;
constexpr char DIALOG_BUTTONS_CONTAINER_ID[] = "__container__";
constexpr char DIALOG_DIVIDER_ID[] = "Dialog_Divider";
constexpr char DIALOG_BUTTON0_ID[] = "Button0";
constexpr char DIALOG_BUTTON1_ID[] = "Button1";

} // namespace

void DialogPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (!onClick_) {
        InitClickEvent(gestureHub);
    }
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    RegisterOnKeyEvent(focusHub);
}

void DialogPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    GestureEventFunc task = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleClick(info);
    };
    onClick_ = MakeRefPtr<ClickEvent>(std::move(task));
    gestureHub->AddClickEvent(onClick_);
}

void DialogPattern::HandleClick(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto props = host->GetLayoutProperty<DialogLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto globalOffset = host->GetPaintRectOffset();
    auto autoCancel = props->GetAutoCancel().value_or(true);
    if (autoCancel) {
        auto content = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(content);
        auto contentRect = content->GetGeometryNode()->GetFrameRect();
        // close dialog if clicked outside content rect
        auto&& clickPosition = info.GetGlobalLocation();
        if (!contentRect.IsInRegion(
            PointF(clickPosition.GetX() - globalOffset.GetX(), clickPosition.GetY() - globalOffset.GetY()))) {
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
    if (host->IsRemoving()) {
        LOGI("Dialog already in close animation, no need to fire event again.");
        return;
    }

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
void DialogPattern::UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode)
{
    auto contentRenderContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    contentRenderContext->UpdateBackgroundColor(dialogTheme_->GetBackgroundColor());

    BorderRadiusProperty radius;
    radius.SetRadius(dialogTheme_->GetRadius().GetX());
    contentRenderContext->UpdateBorderRadius(radius);
    contentRenderContext->SetClipToBounds(true);
}

RefPtr<FrameNode> DialogPattern::CreateDialogScroll(const DialogProperties& dialogProps)
{
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    CHECK_NULL_RETURN(scroll, nullptr);
    auto props = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    props->UpdateAxis(Axis::VERTICAL);
    props->UpdateAlignment(Alignment::CENTER_LEFT);
    // If title not exist, set scroll align center so that text align center.
    if (dialogProps.title.empty() || SystemProperties::GetDeviceType() == DeviceType::WATCH) {
        props->UpdateAlignSelf(FlexAlign::CENTER);
    } else {
        props->UpdateAlignSelf(FlexAlign::FLEX_START);
    }
    return scroll;
}

void DialogPattern::BuildChild(const DialogProperties& props)
{
    LOGI("build dialog child");
    // append customNode
    if (customNode_) {
        // wrap custom node to set background color and round corner
        auto contentWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
        CHECK_NULL_VOID(contentWrapper);
        if (!props.customStyle) {
            UpdateContentRenderContext(contentWrapper);
        }
        customNode_->MountToParent(contentWrapper);
        auto dialog = GetHost();
        contentWrapper->MountToParent(dialog);
        return;
    }

    // Make dialog Content Column
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(contentColumn);

    if (!props.title.empty()) {
        auto title = BuildTitle(props);
        CHECK_NULL_VOID(title);
        contentColumn->AddChild(title);
    }

    if (!props.content.empty()) {
        auto content = BuildContent(props);
        CHECK_NULL_VOID(content);
        // create a scroll
        auto scroll = CreateDialogScroll(props);
        CHECK_NULL_VOID(scroll);
        content->MountToParent(scroll);
        scroll->MountToParent(contentColumn);
        scroll->MarkModifyDone();
    }

    if (!props.customStyle) {
        UpdateContentRenderContext(contentColumn);
    }

    auto columnProp = AceType::DynamicCast<LinearLayoutProperty>(contentColumn->GetLayoutProperty());
    CHECK_NULL_VOID(columnProp);
    // content is full screen in Watch mode
    auto deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::WATCH) {
        columnProp->UpdateMeasureType(MeasureType::MATCH_PARENT);
    } else {
        columnProp->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    }

    // build ActionSheet child
    if (props.type == DialogType::ACTION_SHEET && !props.sheetsInfo.empty()) {
        auto sheetContainer = BuildSheet(props.sheetsInfo);
        CHECK_NULL_VOID(sheetContainer);
        sheetContainer->MountToParent(contentColumn);
        // scrollable
        sheetContainer->MarkModifyDone();
    }

    // Make Menu node if hasMenu (actionMenu)
    if (props.isMenu) {
        auto menu = BuildMenu(props.buttons);
        CHECK_NULL_VOID(menu);
        menu->MountToParent(contentColumn);
    } else {
        // build buttons
        if (!props.buttons.empty()) {
            auto buttonContainer = BuildButtons(props.buttons);
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
    auto titleStyle = dialogTheme_->GetTitleTextStyle();
    titleProp->UpdateFontSize(titleStyle.GetFontSize());
    titleProp->UpdateTextColor(titleStyle.GetTextColor());
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

    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto rowProps = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProps, nullptr);
    rowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    rowProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    title->MountToParent(row);
    title->MarkModifyDone();
    return row;
}

RefPtr<FrameNode> DialogPattern::BuildContent(const DialogProperties& props)
{
    // Make Content node
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto contentProp = AceType::DynamicCast<TextLayoutProperty>(contentNode->GetLayoutProperty());
    CHECK_NULL_RETURN(contentProp, nullptr);
    // textAlign always align start. When text line count 1 and title doesn't exist, set text center position.
    contentProp->UpdateTextAlign(TextAlign::START);
    contentProp->UpdateContent(props.content);
    auto contentStyle = dialogTheme_->GetContentTextStyle();
    contentProp->UpdateFontSize(contentStyle.GetFontSize());
    contentProp->UpdateTextColor(contentStyle.GetTextColor());
    LOGD("content = %s", props.content.c_str());
    // update padding
    Edge contentPaddingInTheme;
    if (!props.title.empty()) {
        contentPaddingInTheme =
            props.buttons.empty() ? dialogTheme_->GetDefaultPadding() : dialogTheme_->GetAdjustPadding();
    } else {
        contentPaddingInTheme =
            props.buttons.empty() ? dialogTheme_->GetContentDefaultPadding() : dialogTheme_->GetContentAdjustPadding();
    }
    PaddingProperty contentPadding;
    contentPadding.left = CalcLength(contentPaddingInTheme.Left());
    contentPadding.right = CalcLength(contentPaddingInTheme.Right());
    contentPadding.top = CalcLength(contentPaddingInTheme.Top());
    contentPadding.bottom = CalcLength(contentPaddingInTheme.Bottom());
    contentProp->UpdatePadding(contentPadding);

    // XTS inspector value
    message_ = props.content;
    contentNode->MarkModifyDone();
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

void DialogPattern::AnalysisLayoutPropertyOfButton(RefPtr<OHOS::Ace::NG::FrameNode> buttonNode,
    RefPtr<OHOS::Ace::NG::LayoutProperty> layoutProps, bool useRelativeLayout, int index)
{
    if (useRelativeLayout) {
        std::map<AlignDirection, AlignRule> alignRules;
        if (index == 0) {
            alignRules[AlignDirection::LEFT] =
                AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .horizontal = HorizontalAlign::START } };
            alignRules[AlignDirection::RIGHT] =
                AlignRule { DIALOG_DIVIDER_ID, { .horizontal = HorizontalAlign::START } };
            alignRules[AlignDirection::CENTER] =
                AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .vertical = VerticalAlign::CENTER } };
            layoutProps->UpdateAlignRules(alignRules);
            buttonNode->UpdateInspectorId(DIALOG_BUTTON0_ID);
        } else {
            alignRules[AlignDirection::RIGHT] =
                AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .horizontal = HorizontalAlign::END } };
            alignRules[AlignDirection::LEFT] = AlignRule { DIALOG_DIVIDER_ID, { .horizontal = HorizontalAlign::END } };
            alignRules[AlignDirection::CENTER] =
                AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .vertical = VerticalAlign::CENTER } };
            layoutProps->UpdateAlignRules(alignRules);
            buttonNode->UpdateInspectorId(DIALOG_BUTTON1_ID);
        }
    } else {
        layoutProps->UpdateFlexGrow(1.0);
        layoutProps->UpdateFlexShrink(1.0);
    }
}

RefPtr<FrameNode> DialogPattern::CreateButton(
    const ButtonInfo& params, int32_t index, bool isCancel, bool useRelativeLayout)
{
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(buttonNode, nullptr);
    UpdateDialogButtonProperty(buttonNode);
    // append text inside button
    auto textNode = CreateButtonText(params.text, params.textColor);
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->MountToParent(buttonNode);
    textNode->MarkModifyDone();

    auto hub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(hub, nullptr);
    // bind click event
    if (params.action) {
        hub->AddClickEvent(params.action);
    }

    // to close dialog when clicked inside button rect
    if (!isCancel) {
        BindCloseCallBack(hub, index);
    } else {
        BindCloseCallBack(hub, -1);
    }

    // register Register keyboard event
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    auto onKeyEvent = [focusHub](const KeyEvent& event) -> bool {
        if (event.action != KeyAction::DOWN) {
            return false;
        }
        if (event.code == KeyCode::KEY_ENTER) {
            focusHub->OnClick(event);
            return true;
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    // add scale animation
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_RETURN(inputHub, nullptr);
    inputHub->SetHoverEffect(HoverEffectType::SCALE);

    // update background color
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    if (params.isBgColorSetted) {
        renderContext->UpdateBackgroundColor(params.bgColor);
    } else {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }

    // set flex grow to fill horizontal space
    auto layoutProps = buttonNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    AnalysisLayoutPropertyOfButton(buttonNode, layoutProps, useRelativeLayout, index);

    // set button default height
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme->GetHeight())));

    return buttonNode;
}

void DialogPattern::UpdateDialogButtonProperty(RefPtr<FrameNode>& buttonNode)
{
    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    PaddingProperty buttonPadding;
    buttonPadding.left = CalcLength(SHEET_LIST_PADDING);
    buttonPadding.right = CalcLength(SHEET_LIST_PADDING);
    buttonProp->UpdatePadding(buttonPadding);
}

RefPtr<FrameNode> DialogPattern::CreateDivider(const Dimension dividerLength, const Dimension dividerWidth)
{
    auto dividerNode = FrameNode::CreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    CHECK_NULL_RETURN(dividerNode, nullptr);
    auto dividerProps = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerProps, nullptr);
    dividerProps->UpdateVertical(true);
    dividerProps->UpdateStrokeWidth(dividerWidth);
    dividerProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(dividerLength)));

    // add divider margin
    MarginProperty margin = {
        .left = CalcLength(4.0_vp),
        .right = CalcLength(4.0_vp),
    };
    dividerProps->UpdateMargin(margin);

    std::map<AlignDirection, AlignRule> alignRules;
    alignRules[AlignDirection::MIDDLE] =
        AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .horizontal = HorizontalAlign::CENTER } };
    alignRules[AlignDirection::CENTER] =
        AlignRule { DIALOG_BUTTONS_CONTAINER_ID, { .vertical = VerticalAlign::CENTER } };
    dividerProps->UpdateAlignRules(alignRules);
    dividerNode->UpdateInspectorId(DIALOG_DIVIDER_ID);
    return dividerNode;
}

// alert dialog buttons
RefPtr<FrameNode> DialogPattern::BuildButtons(const std::vector<ButtonInfo>& buttons)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> container;
    if (buttons.size() == TWO_BUTTON_MODE) {
        container = FrameNode::CreateFrameNode(
            V2::RELATIVE_CONTAINER_ETS_TAG, Id, AceType::MakeRefPtr<RelativeContainerPattern>());
        CHECK_NULL_RETURN(container, nullptr);
        container->UpdateInspectorId(DIALOG_BUTTONS_CONTAINER_ID);
        auto buttonPipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(buttonPipeline, nullptr);
        auto buttonTheme = buttonPipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, nullptr);
        MeasureProperty layoutConstraint;
        auto padding = dialogTheme_->GetActionsPadding();
        layoutConstraint.UpdateMaxSizeWithCheck(
            CalcSize(std::nullopt, CalcLength(padding.Top() + padding.Bottom() + buttonTheme->GetHeight())));
        container->UpdateLayoutConstraint(layoutConstraint);
    } else {
        // if more than 2 buttons, use vertical layout
        container = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto layoutProps = container->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateCrossAxisAlign(FlexAlign::STRETCH);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
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

    AddButtonAndDivider(buttons, container);

    return container;
}

void DialogPattern::AddButtonAndDivider(
    const std::vector<ButtonInfo>& buttons, RefPtr<OHOS::Ace::NG::FrameNode> container)
{
    auto dividerLength = dialogTheme_->GetDividerLength();
    auto dividerWidth = dialogTheme_->GetDividerBetweenButtonWidth_();
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons.size() == TWO_BUTTON_MODE) {
            auto buttonNode = CreateButton(buttons[i], i, false, true);
            CHECK_NULL_VOID(buttonNode);
            buttonNode->MountToParent(container);
            buttonNode->MarkModifyDone();
            container->AddChild(buttonNode);
            if (i == 0) {
                auto dividerNode = CreateDivider(dividerLength, dividerWidth);
                container->AddChild(dividerNode);
            }
        } else {
            auto buttonNode = CreateButton(buttons[i], i);
            CHECK_NULL_VOID(buttonNode);
            buttonNode->MountToParent(container);
            buttonNode->MarkModifyDone();
        }
    }
}

RefPtr<FrameNode> DialogPattern::CreateButtonText(const std::string& text, const std::string& colorStr)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textProps = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, nullptr);
    textProps->UpdateContent(text);
    textProps->UpdateMaxLines(1);
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    Dimension buttonTextSize =
        dialogTheme_->GetButtonTextSize().IsValid() ? dialogTheme_->GetButtonTextSize() : DIALOG_BUTTON_TEXT_SIZE;
    textProps->UpdateFontSize(buttonTextSize);
    // update text color
    Color color;
    if (Color::ParseColorString(colorStr, color)) {
        textProps->UpdateTextColor(color);
    } else {
        textProps->UpdateTextColor(DEFAULT_BUTTON_COLOR);
    }
    return textNode;
}

RefPtr<FrameNode> DialogPattern::BuildSheetItem(const ActionSheetInfo& item)
{
    // ListItem -> Row -> title + icon
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> itemNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, Id, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
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
        // add image margin
        MarginProperty margin = {
            .left = CalcLength(SHEET_IMAGE_MARGIN),
            .right = CalcLength(SHEET_IMAGE_MARGIN),
            .top = CalcLength(SHEET_IMAGE_MARGIN),
            .bottom = CalcLength(SHEET_IMAGE_MARGIN),
        };
        auto iconProps = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        iconProps->UpdateMargin(margin);
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
        titleNode->MarkModifyDone();
    }
    // set sheetItem action
    auto hub = itemRow->GetOrCreateGestureEventHub();
    if (item.action) {
        hub->AddClickEvent(item.action);
    }
    // close dialog when clicked
    BindCloseCallBack(hub, SHEET_INFO_IDX);

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
        RefPtr<FrameNode> button;
        if (i != (buttons.size() - 1)) {
            button = CreateButton(buttons[i], i);
        } else {
            button = CreateButton(buttons[i], i, true);
        }
        CHECK_NULL_RETURN(button, nullptr);
        auto props = DynamicCast<FrameNode>(button)->GetLayoutProperty();
        props->UpdateFlexGrow(1);
        props->UpdateFlexShrink(1);

        button->MountToParent(menu);
        button->MarkModifyDone();
    }
    auto menuProps = menu->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(menuProps, nullptr);
    menuProps->UpdateCrossAxisAlign(FlexAlign::STRETCH);
    menuProps->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    return menu;
}

void DialogPattern::RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool DialogPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    return false;
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

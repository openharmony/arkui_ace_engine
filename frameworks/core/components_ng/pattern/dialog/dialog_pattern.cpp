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
#include "core/components_ng/pattern/list/list_paint_property.h"
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
constexpr int32_t ONE_BUTTON_MODE = 1;
constexpr int32_t START_CHILD_INDEX = 0;
constexpr uint32_t DIALOG_TITLE_MAXLINES = 1;
constexpr Dimension DIALOG_ONE_TITLE_ALL_HEIGHT = 56.0_vp;
constexpr Dimension DIALOG_TITLE_CONTENT_HEIGHT = 35.0_px;
constexpr int32_t DIALOG_TITLE_AVE_BY_2 = 2;
constexpr Dimension DIALOG_CONTENT_PADDING_TOP = 0.0_vp;
constexpr Dimension DIALOG_SUBTITLE_PADDING_LEFT = 24.0_vp;
constexpr Dimension DIALOG_SUBTITLE_PADDING_RIGHT = 24.0_vp;
constexpr Dimension DIALOG_TWO_TITLE_ZERO_SPACE = 0.0_vp;
constexpr Dimension DIALOG_TWO_TITLE_SPACE = 16.0_vp;
constexpr float BUTTON_TEXT_OPACITY = 0.6f; // [Button Component Defect]
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
        CHECK_NULL_VOID(pattern);
        pattern->HandleClick(info);
    };
    onClick_ = MakeRefPtr<ClickEvent>(std::move(task));
    gestureHub->AddClickEvent(onClick_);
}

void DialogPattern::HandleClick(const GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::KEYBOARD) {
        return;
    }
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
void DialogPattern::UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const DialogProperties& props)
{
    auto contentRenderContext = contentNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    contentRenderContext->UpdateBackgroundColor(props.backgroundColor.value_or(dialogTheme_->GetBackgroundColor()));

    if (props.borderRadius.has_value()) {
        contentRenderContext->UpdateBorderRadius(props.borderRadius.value());
    } else {
        BorderRadiusProperty radius;
        radius.SetRadius(dialogTheme_->GetRadius().GetX());
        contentRenderContext->UpdateBorderRadius(radius);
    }
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
    if ((dialogProps.title.empty() && dialogProps.subtitle.empty()) ||
        SystemProperties::GetDeviceType() == DeviceType::WATCH) {
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
            UpdateContentRenderContext(contentWrapper, props);
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

    if (!props.title.empty() || !props.subtitle.empty()) {
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
        UpdateContentRenderContext(contentColumn, props);
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
            auto buttonContainer = BuildButtons(props.buttons, props.buttonDirection);
            CHECK_NULL_VOID(buttonContainer);
            buttonContainer->MountToParent(contentColumn);
        }
    }

    auto dialog = GetHost();
    contentColumn->MountToParent(dialog);
}

RefPtr<FrameNode> DialogPattern::BuildMainTitle(const DialogProperties& dialogProperties)
{
    auto title = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(title->GetLayoutProperty());
    CHECK_NULL_RETURN(titleProp, nullptr);
    titleProp->UpdateMaxLines(DIALOG_TITLE_MAXLINES);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(dialogTheme_->GetTitleTextStyle().GetFontSize());
    titleProp->UpdateAdaptMinFontSize(dialogTheme_->GetTitleTextStyle().GetFontSize());
    std::string titleContent = dialogProperties.title.empty() ? dialogProperties.subtitle : dialogProperties.title;
    titleProp->UpdateContent(titleContent);
    auto titleStyle = dialogTheme_->GetTitleTextStyle();
    titleProp->UpdateFontSize(titleStyle.GetFontSize());
    titleProp->UpdateFontWeight(titleStyle.GetFontWeight());
    titleProp->UpdateTextColor(titleStyle.GetTextColor());
    PaddingProperty titlePadding;
    auto paddingInTheme = (dialogProperties.content.empty() && dialogProperties.buttons.empty())
                              ? dialogTheme_->GetTitleDefaultPadding()
                              : dialogTheme_->GetTitleAdjustPadding();
    titlePadding.left = CalcLength(paddingInTheme.Left());
    titlePadding.right = CalcLength(paddingInTheme.Right());
    if (!dialogProperties.title.empty() && !dialogProperties.subtitle.empty()) {
        titlePadding.top = CalcLength(DIALOG_TWO_TITLE_SPACE);
        titlePadding.bottom = CalcLength(DIALOG_TWO_TITLE_ZERO_SPACE);
    } else {
        titlePadding.top = CalcLength(
            (DIALOG_ONE_TITLE_ALL_HEIGHT - Dimension(DIALOG_TITLE_CONTENT_HEIGHT.ConvertToVp(), DimensionUnit::VP)) /
            DIALOG_TITLE_AVE_BY_2);
        titlePadding.bottom = CalcLength(
            (DIALOG_ONE_TITLE_ALL_HEIGHT - Dimension(DIALOG_TITLE_CONTENT_HEIGHT.ConvertToVp(), DimensionUnit::VP)) /
            DIALOG_TITLE_AVE_BY_2);
    }
    titleProp->UpdatePadding(titlePadding);

    // XTS inspector value
    title_ = dialogProperties.title;
    subtitle_ = dialogProperties.subtitle;

    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleRow, nullptr);
    auto titleRowProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(titleRowProps, nullptr);
    titleRowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    titleRowProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    title->MountToParent(titleRow);
    title->MarkModifyDone();
    return titleRow;
}

RefPtr<FrameNode> DialogPattern::BuildSubTitle(const DialogProperties& dialogProperties)
{
    auto subtitle = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(subtitle->GetLayoutProperty());
    CHECK_NULL_RETURN(titleProp, nullptr);
    auto titleStyle = dialogTheme_->GetSubTitleTextStyle();
    titleProp->UpdateMaxLines(DIALOG_TITLE_MAXLINES);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(titleStyle.GetFontSize());
    titleProp->UpdateAdaptMinFontSize(titleStyle.GetFontSize());
    titleProp->UpdateContent(dialogProperties.subtitle);
    titleProp->UpdateFontSize(titleStyle.GetFontSize());
    titleProp->UpdateTextColor(titleStyle.GetTextColor());
    PaddingProperty titlePadding;
    titlePadding.left = CalcLength(DIALOG_SUBTITLE_PADDING_LEFT);
    titlePadding.right = CalcLength(DIALOG_SUBTITLE_PADDING_RIGHT);
    titlePadding.top = CalcLength(DIALOG_TWO_TITLE_ZERO_SPACE);
    titlePadding.bottom = CalcLength(DIALOG_TWO_TITLE_SPACE);
    titleProp->UpdatePadding(titlePadding);

    // XTS inspector value
    subtitle_ = dialogProperties.subtitle;

    auto subtitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(subtitleRow, nullptr);
    auto subtitleRowProps = subtitleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(subtitleRowProps, nullptr);
    subtitleRowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    subtitleRowProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    subtitle->MountToParent(subtitleRow);
    subtitle->MarkModifyDone();
    return subtitleRow;
}

RefPtr<FrameNode> DialogPattern::BuildTitle(const DialogProperties& dialogProperties)
{
    auto titleRow = BuildMainTitle(dialogProperties);
    if (!dialogProperties.title.empty() && !dialogProperties.subtitle.empty()) {
        auto titleColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
        CHECK_NULL_RETURN(titleColumn, nullptr);
        auto columnProps = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(columnProps, nullptr);
        columnProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
        columnProps->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        auto subtitleRow = BuildSubTitle(dialogProperties);
        titleColumn->AddChild(titleRow);
        titleColumn->AddChild(subtitleRow);
        return titleColumn;
    }
    return titleRow;
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
    PaddingProperty contentPadding;
    if (!props.title.empty() || !props.subtitle.empty()) {
        contentPaddingInTheme =
            props.buttons.empty() ? dialogTheme_->GetDefaultPadding() : dialogTheme_->GetAdjustPadding();
        contentPadding.top = CalcLength(DIALOG_CONTENT_PADDING_TOP);
    } else {
        contentPaddingInTheme =
            props.buttons.empty() ? dialogTheme_->GetContentDefaultPadding() : dialogTheme_->GetContentAdjustPadding();
        contentPadding.top = CalcLength(contentPaddingInTheme.Top());
    }
    contentPadding.left = CalcLength(contentPaddingInTheme.Left());
    contentPadding.right = CalcLength(contentPaddingInTheme.Right());
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

void DialogPattern::ParseButtonFontColorAndBgColor(
    const ButtonInfo& params, std::string& textColor, std::optional<Color>& bgColor)
{
    // Parse Button Style
    if (params.dlgButtonStyle.has_value()) {
        switch (params.dlgButtonStyle.value()) {
            case DialogButtonStyle::DEFAULT:
                textColor = dialogTheme_->GetButtonDefaultFontColor().ColorToString();
                bgColor = dialogTheme_->GetButtonDefaultBgColor();
                break;
            case DialogButtonStyle::HIGHTLIGHT:
                textColor = dialogTheme_->GetButtonHighlightFontColor().ColorToString();
                bgColor = dialogTheme_->GetButtonHighlightBgColor();
                break;
            default:
                break;
        }
    }

    // font color and background color
    if (!params.textColor.empty()) {
        textColor = params.textColor;
    }
    if (params.isBgColorSetted) {
        bgColor = params.bgColor;
    }

    // Parse default focus
    if (textColor.empty()) {
        if (params.defaultFocus && isFirstDefaultFocus_) {
            textColor = dialogTheme_->GetButtonHighlightFontColor().ColorToString();
        } else {
            textColor = dialogTheme_->GetButtonDefaultFontColor().ColorToString();
        }
    }
    if (!bgColor.has_value()) {
        if (params.defaultFocus && isFirstDefaultFocus_) {
            bgColor = dialogTheme_->GetButtonHighlightBgColor();
            isFirstDefaultFocus_ = false;
        } else {
            bgColor = dialogTheme_->GetButtonDefaultBgColor();
        }
    }
}

RefPtr<FrameNode> DialogPattern::CreateButton(
    const ButtonInfo& params, int32_t index, bool isCancel, bool isVertical, int32_t length)
{
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(buttonNode, nullptr);
    UpdateDialogButtonProperty(buttonNode, index, isVertical, length);

    // parse button text color and background color
    std::string textColor;
    std::optional<Color> bgColor;
    ParseButtonFontColorAndBgColor(params, textColor, bgColor);

    // append text inside button
    auto textNode = CreateButtonText(params.text, textColor);
    CHECK_NULL_RETURN(textNode, nullptr);
    SetButtonTextOpacity(textNode, params.enabled);
    textNode->MountToParent(buttonNode);
    textNode->MarkModifyDone();

    SetButtonEnabled(buttonNode, params.enabled);

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

    // add scale animation
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_RETURN(inputHub, nullptr);
    inputHub->SetHoverEffect(HoverEffectType::NONE);

    // update background color
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(bgColor.value());

    // set button default height
    auto layoutProps = buttonNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme->GetHeight())));

    return buttonNode;
}

void DialogPattern::UpdateDialogButtonProperty(
    RefPtr<FrameNode>& buttonNode, int32_t index, bool isVertical, int32_t length)
{
    // update button padding
    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    PaddingProperty buttonPadding;
    buttonPadding.left = CalcLength(SHEET_LIST_PADDING);
    buttonPadding.right = CalcLength(SHEET_LIST_PADDING);
    buttonProp->UpdatePadding(buttonPadding);

    if (!isVertical) {
        // set flex grow to fill horizontal space
        buttonProp->UpdateLayoutWeight(1);
        buttonProp->UpdateFlexGrow(1.0);
        buttonProp->UpdateFlexShrink(1.0);
    } else if (isVertical && index != (length - 1)) {
        // update button space in vertical
        auto buttonSpace = dialogTheme_->GetMutiButtonPaddingVertical();
        MarginProperty margin = {
            .bottom = CalcLength(buttonSpace),
        };
        buttonProp->UpdateMargin(margin);
    }
}

RefPtr<FrameNode> DialogPattern::CreateDivider(
    const Dimension& dividerLength, const Dimension& dividerWidth, const Color& color, const Dimension& space)
{
    auto dividerNode = FrameNode::CreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    CHECK_NULL_RETURN(dividerNode, nullptr);
    auto dividerProps = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerProps, nullptr);
    dividerProps->UpdateVertical(true);
    dividerProps->UpdateStrokeWidth(dividerWidth);
    dividerProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(dividerLength)));
    auto dividerPaintProps = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerPaintProps, nullptr);
    dividerPaintProps->UpdateDividerColor(color);

    // add divider margin
    MarginProperty margin = {
        .left = CalcLength((space - dividerWidth) / 2),
        .right = CalcLength((space - dividerWidth) / 2),
    };
    dividerProps->UpdateMargin(margin);
    return dividerNode;
}

// alert dialog buttons
RefPtr<FrameNode> DialogPattern::BuildButtons(
    const std::vector<ButtonInfo>& buttons, const DialogButtonDirection& direction)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<FrameNode> container;
    bool isVertical;
    if (direction == DialogButtonDirection::HORIZONTAL ||
        (direction == DialogButtonDirection::AUTO && buttons.size() == TWO_BUTTON_MODE)) {
        // use horizontal layout
        isVertical = false;
        container = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(container, nullptr);
        auto layoutProps = container->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    } else {
        // use vertical layout
        isVertical = true;
        container = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, Id, AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto layoutProps = container->GetLayoutProperty<LinearLayoutProperty>();
        layoutProps->UpdateCrossAxisAlign(FlexAlign::STRETCH);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    }
    CHECK_NULL_RETURN(container, nullptr);
    // set action's padding
    PaddingProperty actionPadding;
    if (buttons.size() == ONE_BUTTON_MODE || isVertical) {
        actionPadding.left = CalcLength(dialogTheme_->GetSingleButtonPaddingStart());
        actionPadding.right = CalcLength(dialogTheme_->GetSingleButtonPaddingEnd());
    } else {
        actionPadding.left = CalcLength(dialogTheme_->GetMutiButtonPaddingStart());
        actionPadding.right = CalcLength(dialogTheme_->GetMutiButtonPaddingEnd());
    }
    auto padding = dialogTheme_->GetActionsPadding();
    actionPadding.top = CalcLength(padding.Top());
    actionPadding.bottom = CalcLength(dialogTheme_->GetButtonPaddingBottom());
    container->GetLayoutProperty()->UpdatePadding(actionPadding);

    AddButtonAndDivider(buttons, container, isVertical);
    container->MarkModifyDone();

    return container;
}

void DialogPattern::AddButtonAndDivider(
    const std::vector<ButtonInfo>& buttons, const RefPtr<NG::FrameNode>& container, bool isVertical)
{
    auto dividerLength = dialogTheme_->GetDividerLength();
    auto dividerWidth = dialogTheme_->GetDividerBetweenButtonWidth_();
    auto dividerColor = dialogTheme_->GetDividerColor();
    auto buttonSpace = dialogTheme_->GetMutiButtonPaddingHorizontal();
    auto length = buttons.size();
    for (size_t i = 0; i < length; ++i) {
        if (i != 0 && !isVertical) {
            auto dividerNode = CreateDivider(
                dividerLength, dividerWidth, dividerColor, buttonSpace);
            CHECK_NULL_VOID(dividerNode);
            container->AddChild(dividerNode);
        }
        auto buttonNode = CreateButton(buttons[i], i, false, isVertical, length);
        CHECK_NULL_VOID(buttonNode);
        auto buttonPattern = buttonNode->GetPattern<ButtonPattern>();
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->SetSkipColorConfigurationUpdate();
        buttonNode->MountToParent(container);
        buttonNode->MarkModifyDone();
    }
}

RefPtr<FrameNode> DialogPattern::CreateButtonText(const std::string& text, const std::string& colorStr)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->GetOrCreateFocusHub()->SetFocusable(true);
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
        auto iconNode = BuildSheetInfoIcon(item.icon);
        iconNode->MountToParent(itemRow);
        iconNode->MarkModifyDone();
    }

    // mount title
    if (!item.title.empty()) {
        auto titleNode = BuildSheetInfoTitle(item.title);
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

RefPtr<FrameNode> DialogPattern::BuildSheetInfoTitle(const std::string& title)
{
    auto titleId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(titleNode, nullptr);
    // update text style
    auto style = dialogTheme_->GetContentTextStyle();
    auto props = titleNode->GetLayoutProperty<TextLayoutProperty>();
    props->UpdateContent(title);
    props->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    props->UpdateAdaptMaxFontSize(style.GetFontSize());
    props->UpdateAdaptMinFontSize(dialogTheme_->GetTitleMinFontSize());
    props->UpdateMaxLines(style.GetMaxLines());
    props->UpdateFlexGrow(1.0f);
    props->UpdateFlexShrink(1.0f);
    return titleNode;
}

RefPtr<FrameNode> DialogPattern::BuildSheetInfoIcon(const std::string& icon)
{
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
    LOGD("item icon src = %s", icon.c_str());
    auto imageSrc = ImageSourceInfo(icon);
    iconProps->UpdateImageSourceInfo(imageSrc);
    iconProps->UpdateUserDefinedIdealSize(CalcSize(SHEET_IMAGE_SIZE, SHEET_IMAGE_SIZE));
    return iconNode;
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
    list->GetLayoutProperty()->UpdatePadding(sheetPadding);
    list->GetPaintProperty<ListPaintProperty>()->UpdateBarDisplayMode(DisplayMode::OFF);

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
    menuNode_ = menu;
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
        CHECK_NULL_RETURN(pattern, false);
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
        json->Put("subtitle", subtitle_.c_str());
        json->Put("message", message_.c_str());
    }
}

void DialogPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!GetDialogProperties().customStyle) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto dialogTheme = context->GetTheme<DialogTheme>();
        CHECK_NULL_VOID(dialogTheme);
        auto col = DynamicCast<FrameNode>(host->GetChildAtIndex(START_CHILD_INDEX));
        CHECK_NULL_VOID(col);
        auto colContext = col->GetContext();
        CHECK_NULL_VOID(colContext);
        auto colRenderContext = col->GetRenderContext();
        CHECK_NULL_VOID(colRenderContext);
        colRenderContext->UpdateBackgroundColor(dialogTheme->GetBackgroundColor());
    }
    CHECK_NULL_VOID(menuNode_);
    for (const auto& buttonNode : menuNode_->GetChildren()) {
        if (buttonNode->GetTag() != V2::BUTTON_ETS_TAG) {
            continue;
        }
        auto buttonFrameNode = DynamicCast<FrameNode>(buttonNode);
        CHECK_NULL_VOID(buttonFrameNode);
        auto pattern = buttonFrameNode->GetPattern<ButtonPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSkipColorConfigurationUpdate();
    }
    OnModifyDone();
    host->MarkDirtyNode();
}

void DialogPattern::SetButtonTextOpacity(const RefPtr<FrameNode>& textNode, bool enabled)
{
    auto textNodeRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textNodeRenderContext);
    // [Button Component Defect] Button text color is no set while disabled status.
    if (!enabled) {
        textNodeRenderContext->UpdateOpacity(BUTTON_TEXT_OPACITY);
    }
}

void DialogPattern::SetButtonEnabled(const RefPtr<FrameNode>& buttonNode, bool enabled)
{
    // set Enabled and Focusable
    auto buttonButtonEvent = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonButtonEvent);
    buttonButtonEvent->SetEnabled(enabled);
    buttonNode->GetOrCreateFocusHub()->SetFocusable(enabled);
}
} // namespace OHOS::Ace::NG

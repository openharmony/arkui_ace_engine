/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"

#include <utility>

#include "base/geometry/dimension.h"
#include "base/i18n/date_time_sequence.h"
#include "base/memory/ace_type.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t MARGIN_HALF = 2;
const int32_t NEXT_BUTTON_INDEX = 2;
const int32_t DIVIDER_ROWS_THREE = 3;
constexpr double MONTHDAYS_WIDTH_PERCENT_ONE = 0.4285;
constexpr double TIME_WIDTH_PERCENT_ONE = 0.5714;
constexpr double MONTHDAYS_WIDTH_PERCENT_TWO = 0.3636;
constexpr double TIME_WIDTH_PERCENT_TWO = 0.6363;
constexpr Dimension BUTTON_BOTTOM_TOP_MARGIN = 10.0_vp;
constexpr Dimension LUNARSWITCH_HEIGHT = 48.0_vp;
constexpr Dimension CHECKBOX_SIZE = 24.0_vp;
constexpr Dimension TITLE_HEIGHT = 40.0_vp;
constexpr Dimension TITLE_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension TITLE_PADDING_HORIZONTAL = 16.0_vp;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr int32_t RATIO_SEVEN = 7;
constexpr int32_t RATIO_FOUR = 4;
constexpr int32_t RATIO_THREE = 3;
constexpr int32_t RATIO_TWO = 2;
constexpr int32_t RATIO_ONE = 1;
constexpr int32_t RATIO_ZERO = 0;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
constexpr size_t CANCEL_BUTTON_INDEX = 1;
constexpr int32_t NODE_ZERO = 0;
constexpr int32_t FIRST_STACK  = 0;
constexpr int32_t SECOND_STACK = 1;
constexpr int32_t FIRST_PAGE  = 0;
constexpr int32_t SECOND_PAGE = 1;
} // namespace
bool DatePickerDialogView::switchFlag_ = false;
bool DatePickerDialogView::switchTimePickerFlag_ = false;
bool DatePickerDialogView::switchDatePickerFlag_ = false;
bool DatePickerDialogView::isShowTime_ = false;
bool DatePickerDialogView::isUserSetFont_ = false;
bool DatePickerDialogView::isEnableHapticFeedback_ = true;
DatePickerMode DatePickerDialogView::datePickerMode_ = DatePickerMode::DATE;
Dimension DatePickerDialogView::selectedTextStyleFont_ = 40.0_fp;
Dimension DatePickerDialogView::normalTextStyleFont_ = 32.0_fp;
Dimension DatePickerDialogView::disappearTextStyleFont_ = 28.0_fp;

RefPtr<FrameNode> DatePickerDialogView::Show(const DialogProperties& dialogProperties,
    const DatePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[DatePickerDialogView]");
    GetUserSettingLimit();
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto pickerStack = CreateStackNode();
    auto dateNode = CreateAndMountDateNode(settingData, pickerStack);
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    DateTimeSequence sequence;
    auto language = AceApplicationInfo::GetInstance().GetLanguage();
    OrderResult orderResult = sequence.GetDateOrder(language);
    if (language == "ug") {
        pickerPattern->SetDateOrder("y-d-M");
    } else {
        auto dateOrder = orderResult.dateOrder;
        pickerPattern->SetDateOrder(dateOrder);
    }
    pickerPattern->SetIsShowInDialog(true);
    pickerPattern->SetShowLunarSwitch(settingData.lunarswitch);
    pickerPattern->SetTextProperties(settingData.properties);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        isEnableHapticFeedback_ = settingData.isEnableHapticFeedback;
        pickerPattern->SetEnableHapticFeedback(isEnableHapticFeedback_);
        pickerPattern->ColumnPatternInitHapticController();
    }

    auto buttonTitleNode = CreateAndMountButtonTitleNode(dateNode, contentColumn);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);

    std::function<void(bool)> lunarChangeEvent = CreateLunarChangeEvent(dateNode);
    RefPtr<FrameNode> acceptNode = dateNode;
    RefPtr<FrameNode> timePickerNode = dateNode;
    if (settingData.showTime) {
        switchFlag_ = false;
        switchTimePickerFlag_ = false;
        auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(pickerRow, nullptr);

        auto monthDaysNode = CreateAndMountMonthDaysNode(settingData, dateNode, pickerRow, std::move(lunarChangeEvent));
        CHECK_NULL_RETURN(monthDaysNode, nullptr);
        auto timeNode = CreateAndMountTimeNode(settingData, monthDaysNode, pickerRow);
        CHECK_NULL_RETURN(timeNode, nullptr);
        timePickerNode = timeNode;
        isShowTime_ = true;
        pickerRow->MountToParent(pickerStack);

        CreateTitleIconNode(buttonTitleNode);
        SetTitleMouseHoverEvent(buttonTitleNode);
        buttonTitleNode->MarkModifyDone();
        auto titleSwitchEvent = CreateAndSetDialogSwitchEvent(pickerStack, contentColumn, settingData);
        CreateAndAddTitleClickEvent(titleSwitchEvent, buttonTitleNode);
        acceptNode = monthDaysNode;
    } else {
        isShowTime_ = false;
    }
    dateNode->MarkModifyDone();

    ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_RETURN(acceptNode, nullptr);
    auto monthDaysPattern = acceptNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(monthDaysPattern, nullptr);
    monthDaysPattern->ShowTitle(monthDaysPattern->GetTitleId());
    auto stackLayoutProperty = pickerStack->GetLayoutProperty();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(NG::CalcLength(Dimension(1, DimensionUnit::PERCENT)), std::nullopt));
    UpdateContentPadding(pickerStack);
    pickerStack->MountToParent(contentColumn);
    // build lunarswitch Node
    if (settingData.lunarswitch) {
        CreateLunarswitchNode(contentColumn, dateNode, std::move(lunarChangeEvent), settingData.isLunar,
            settingData.checkboxSettingData);
    }
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    dialogPattern->SetIsPickerDialog(true);
    // build dialog accept and cancel button
    if (NeedAdaptForAging()) {
        BuildDialogAcceptAndCancelButtonForAging(buttonInfos, settingData, timePickerNode, acceptNode, dateNode,
                                                 dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
    } else {
        BuildDialogAcceptAndCancelButton(
            buttonInfos, settingData, acceptNode, dateNode, dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
    }
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateLunarSwitchTextNode()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(pickerTheme->GetLunarSwitchText());
    textLayoutProperty->UpdateFontSize(ConvertFontScaleValue(pickerTheme->GetLunarSwitchTextSize()));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetLunarSwitchTextColor());
    textNode->MarkModifyDone();
    return textNode;
}

void DatePickerDialogView::SetTimeNodeColumnWeight(
    const RefPtr<FrameNode>& timeNode, const DatePickerSettingData& settingData)
{
    auto timeLayoutProperty = timeNode->GetLayoutProperty();
    CHECK_NULL_VOID(timeLayoutProperty);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        timeLayoutProperty->UpdateLayoutWeight(settingData.useMilitary ? RATIO_FOUR : RATIO_SEVEN);
        for (const auto& child : timeNode->GetChildren()) {
            auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
            CHECK_NULL_VOID(frameNodeChild);
            auto timeColumnLayoutProperty = frameNodeChild->GetLayoutProperty();
            CHECK_NULL_VOID(timeColumnLayoutProperty);
            timeColumnLayoutProperty->UpdateLayoutWeight(RATIO_TWO);
        }
        if (!settingData.useMilitary) {
            auto child = timeNode->GetFirstChild();
            CHECK_NULL_VOID(child);
            auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
            CHECK_NULL_VOID(frameNodeChild);
            auto timeColumnLayoutProperty = frameNodeChild->GetLayoutProperty();
            CHECK_NULL_VOID(timeColumnLayoutProperty);
            timeColumnLayoutProperty->UpdateLayoutWeight(RATIO_THREE);
        }
    } else {
        timeLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(Dimension(settingData.useMilitary ? TIME_WIDTH_PERCENT_ONE : TIME_WIDTH_PERCENT_TWO,
                DimensionUnit::PERCENT)),
            std::nullopt));
    }
}

RefPtr<FrameNode> DatePickerDialogView::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> DatePickerDialogView::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> DatePickerDialogView::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> DatePickerDialogView::CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    auto titleRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleRow, nullptr);
    UpdateTitleRowLayoutProps(titleRow);

    auto buttonTitleNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, pickerPattern->GetButtonTitleId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);
    auto titleButtonRow = CreateTitleButtonRowNode();
    CHECK_NULL_RETURN(titleButtonRow, nullptr);
    auto textTitleNodeId = pickerPattern->GetTitleId();
    auto textTitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textTitleNodeId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textTitleNode, nullptr);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(u"");
    textLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    textLayoutProperty->UpdateTextColor(pickerTheme->GetTitleStyle().GetTextColor());
    textLayoutProperty->UpdateFontSize(ConvertTitleFontScaleValue(pickerTheme->GetTitleStyle().GetFontSize()));
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetTitleStyle().GetFontWeight());
    textLayoutProperty->UpdateTextOverflow(pickerTheme->GetTitleStyle().GetTextOverflow());
    textLayoutProperty->UpdateMaxLines(pickerTheme->GetTitleStyle().GetMaxLines());
    textLayoutProperty->UpdateFlexShrink(1.0);
    auto buttonTitleRenderContext = buttonTitleNode->GetRenderContext();
    CHECK_NULL_RETURN(buttonTitleRenderContext, nullptr);
    buttonTitleRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
        margin.top = CalcLength(dialogTheme->GetDividerHeight() / MARGIN_HALF);
        margin.bottom = CalcLength(dialogTheme->GetDividerHeight() / MARGIN_HALF);
        buttonTitleNode->GetLayoutProperty()->UpdateMargin(margin);
    } else {
        buttonTitleNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(TITLE_BUTTON_HEIGHT)));
        titleButtonRow->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(TITLE_BUTTON_HEIGHT)));
    }
    textTitleNode->MountToParent(titleButtonRow);
    titleButtonRow->MountToParent(buttonTitleNode);
    buttonTitleNode->MountToParent(titleRow);
    titleRow->SetNeedCallChildrenUpdate(false);
    return titleRow;
}

void DatePickerDialogView::UpdateTitleRowLayoutProps(const RefPtr<FrameNode>& titleRow)
{
    auto layoutProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
}

RefPtr<FrameNode> DatePickerDialogView::CreateTitleButtonRowNode()
{
    auto titleButtonRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleButtonRow, nullptr);
    auto bottonRowlayoutProps = titleButtonRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(bottonRowlayoutProps, nullptr);
    bottonRowlayoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    bottonRowlayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    bottonRowlayoutProps->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    return titleButtonRow;
}

void DatePickerDialogView::CreateTitleIconNode(const RefPtr<FrameNode>& titleNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto spinnerNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(spinnerNode);
    ImageSourceInfo imageSourceInfo;
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SPINNER);
    imageSourceInfo.SetSrc(iconPath);
    imageSourceInfo.SetFillColor(pickerTheme->GetTitleStyle().GetTextColor());
    auto spinnerRenderProperty = spinnerNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(spinnerRenderProperty);
    spinnerRenderProperty->UpdateSvgFillColor(pickerTheme->GetTitleStyle().GetTextColor());

    auto spinnerLayoutProperty = spinnerNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(spinnerLayoutProperty);
    spinnerLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    CalcSize idealSize = { CalcLength(pickerTheme->GetTitleStyle().GetFontSize()),
        CalcLength(pickerTheme->GetTitleStyle().GetFontSize()) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    spinnerLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
    spinnerNode->MarkModifyDone();
    auto buttonNode = AceType::DynamicCast<FrameNode>(titleNode->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto buttonRowNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    CHECK_NULL_VOID(buttonRowNode);
    spinnerNode->MountToParent(buttonRowNode);
}

RefPtr<FrameNode> DatePickerDialogView::CreateDividerNode(const RefPtr<FrameNode>& dateNode, bool isCreateDivider)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);

    int32_t dividerNodeId = 0;
    if (isCreateDivider) {
        dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    } else {
        dividerNodeId = pickerPattern->GetDividerId();
    }

    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    CHECK_NULL_RETURN(dividerNode, nullptr);

    auto dividerPaintProps = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerPaintProps, nullptr);
    dividerPaintProps->UpdateDividerColor(dialogTheme->GetDividerColor());

    auto dividerLayoutProps = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerLayoutProps, nullptr);
    dividerLayoutProps->UpdateVertical(true);
    dividerLayoutProps->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, nullptr);
        auto dividerWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(dividerWrapper, nullptr);
        auto layoutProps = dividerWrapper->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(dialogTheme->GetActionsPadding().Bottom()), CalcLength(buttonTheme->GetHeight())));
        dividerNode->MountToParent(dividerWrapper);
        return dividerWrapper;
    }
    return dividerNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateButtonNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto dateAcceptEvent = dialogEvent["dateAcceptId"];
    auto cancelEvent = dialogCancelEvent["cancelId"];
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    contentRow->SetNeedCallChildrenUpdate(false);
    SetDialogDateAcceptEvent(dateNode, std::move(dateAcceptEvent));

    auto buttonCancelNode = CreateCancelNode(cancelEvent, datePickerNode, buttonInfos);
    auto buttonConfirmNode = CreateConfirmNode(dateNode, datePickerNode, acceptEvent, buttonInfos);

    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);

    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    datePickerPattern->SetContentRowNode(contentRow);

    return contentRow;
}

std::function<void()> DatePickerDialogView::CreateAndSetTimePickerSwitchEvent(
    const RefPtr<FrameNode>& monthAndDayPickerNode, const RefPtr<FrameNode>& timePickerNode,
    const RefPtr<FrameNode>& contentRow)
{
    auto timePickerSwitchEvent = [weakTimePickerNode = AceType::WeakClaim(AceType::RawPtr(timePickerNode)),
                                     weakMonthAndDayPickerNode =
                                         AceType::WeakClaim(AceType::RawPtr(monthAndDayPickerNode)),
                                     weakcontentRow = AceType::WeakClaim(AceType::RawPtr(contentRow))]() {
        auto timePickerNode = weakTimePickerNode.Upgrade();
        CHECK_NULL_VOID(timePickerNode);
        auto monthAndDayPickerNode = weakMonthAndDayPickerNode.Upgrade();
        CHECK_NULL_VOID(monthAndDayPickerNode);
        auto contentRow = weakcontentRow.Upgrade();
        CHECK_NULL_VOID(contentRow);
        SwitchTimePickerPage(monthAndDayPickerNode, timePickerNode, contentRow);
    };

    return timePickerSwitchEvent;
}

void DatePickerDialogView::SwitchTimePickerPage(const RefPtr<FrameNode> &monthAndDayPickerNode,
    const RefPtr<FrameNode> &timePickerNode, const RefPtr<FrameNode> &contentRow)
{
    auto monthAndDayLayoutProperty = monthAndDayPickerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(monthAndDayLayoutProperty);
    monthAndDayLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    monthAndDayLayoutProperty->UpdateLayoutWeight(switchTimePickerFlag_ ? RATIO_FOUR : 0);
    monthAndDayPickerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    SwitchFocusStatus(timePickerNode, monthAndDayPickerNode);
    UpdateTimePickerChildrenStatus(timePickerNode);
    auto buttonCancelNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(0));
    CHECK_NULL_VOID(buttonCancelNode);
    auto cancelButtonLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    buttonCancelNode->MarkDirtyNode();
    auto cancelNextDividerNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(1));
    CHECK_NULL_VOID(cancelNextDividerNode);
    auto cancelNextLayoutProperty = cancelNextDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelNextLayoutProperty);
    cancelNextLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    cancelNextDividerNode->MarkDirtyNode();
    auto buttonConfirmNode = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
    CHECK_NULL_VOID(buttonConfirmNode);
    auto confirmButtonLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(confirmButtonLayoutProperty);
    confirmButtonLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    buttonConfirmNode->MarkDirtyNode();
    auto nextConfirmDividerNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(DIVIDER_ROWS_THREE));
    CHECK_NULL_VOID(nextConfirmDividerNode);
    auto nextConfirmLayoutProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(nextConfirmLayoutProperty);
    nextConfirmLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    nextConfirmDividerNode->MarkDirtyNode();
    switchTimePickerFlag_ = !switchTimePickerFlag_;
}

void DatePickerDialogView::SwitchFocusStatus(
    const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& monthAndDayPickerNode)
{
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerPattern);
    auto monthAndDayPickerPattern = monthAndDayPickerNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(monthAndDayPickerPattern);
    if (switchTimePickerFlag_) {
        timePickerPattern->SetFocusDisable();
        monthAndDayPickerPattern->SetFocusEnable();
    } else {
        timePickerPattern->SetFocusEnable();
        monthAndDayPickerPattern->SetFocusDisable();
    }
}

void DatePickerDialogView::SwitchDatePickerPage(const RefPtr<FrameNode>& dateNode, bool isSwitchByTitle)
{
    for (uint32_t index = 0; index < dateNode->GetChildren().size(); index++) {
        auto dateStackNode = AceType::DynamicCast<FrameNode>(dateNode->GetChildAtIndex(index));
        CHECK_NULL_VOID(dateStackNode);
        auto layoutProperty = dateStackNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        for (uint32_t k = 0; k < dateStackNode->GetChildren().size(); k++) {
            auto dateChildNode = AceType::DynamicCast<FrameNode>(dateStackNode->GetChildAtIndex(k));
            CHECK_NULL_VOID(dateChildNode);
            auto dateChildNodeLayoutProperty = dateChildNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(dateChildNodeLayoutProperty);
            UpdateDateNodeVisibilityAndWeight(layoutProperty, dateChildNodeLayoutProperty, isSwitchByTitle, index);
            dateChildNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
    }

    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    if (!isShowTime_ && datePickerMode_ == DatePickerMode::YEAR_AND_MONTH) {
        datePickerPattern->SetCurrentFocusKeyID(FIRST_STACK);
    } else if (!isShowTime_ && datePickerMode_ == DatePickerMode::MONTH_AND_DAY) {
        datePickerPattern->SetCurrentFocusKeyID(SECOND_STACK);
    } else {
        datePickerPattern->SetCurrentFocusKeyID(switchDatePickerFlag_ ? SECOND_STACK : FIRST_STACK);
    }
    datePickerPattern->SetCurrentPage((switchDatePickerFlag_ && !isSwitchByTitle) ? SECOND_PAGE : FIRST_PAGE);

    switchDatePickerFlag_ = !switchDatePickerFlag_;
    dateNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void DatePickerDialogView::UpdateDateNodeVisibilityAndWeight(const RefPtr<LayoutProperty>& layoutProperty,
    const RefPtr<LayoutProperty>& dateChildNodeLayoutProperty, bool isSwitchByTitle, uint32_t index)
{
    if (!switchDatePickerFlag_ || isSwitchByTitle) {
        if (!isShowTime_ && datePickerMode_ != DatePickerMode::DATE) {
            return;
        }
        dateChildNodeLayoutProperty->UpdateVisibility((index == NODE_ZERO) ? VisibleType::VISIBLE : VisibleType::GONE);
        switchDatePickerFlag_ = false;
        layoutProperty->UpdateLayoutWeight((index == NODE_ZERO) ? RATIO_TWO : RATIO_ZERO);
    } else {
        dateChildNodeLayoutProperty->UpdateVisibility((index == NODE_ZERO) ? VisibleType::GONE : VisibleType::VISIBLE);
        layoutProperty->UpdateLayoutWeight((index == NODE_ZERO) ? RATIO_ZERO : RATIO_ONE);
    }
}

void DatePickerDialogView::UpdateTimePickerChildrenStatus(const RefPtr<FrameNode>& timePickerNode)
{
    auto layoutProperty = timePickerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    layoutProperty->UpdateLayoutWeight(switchTimePickerFlag_ ? 0 : RATIO_SEVEN);
    for (uint32_t i = 0; i < timePickerNode->GetChildren().size(); i++) {
        auto childStackNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(childStackNode);
        auto layoutProperty = childStackNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        for (uint32_t j = 0; j < childStackNode->GetChildren().size(); j++) {
            auto childNode = AceType::DynamicCast<FrameNode>(childStackNode->GetChildAtIndex(j));
            CHECK_NULL_VOID(childNode);
            auto childLayoutProperty = childNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(childLayoutProperty);
            childLayoutProperty->UpdateVisibility(switchTimePickerFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
            layoutProperty->UpdateLayoutWeight(switchTimePickerFlag_ ? 0 : RATIO_TWO);
            childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
    }
}

void DatePickerDialogView::HideContentChildrenButton(const RefPtr<FrameNode>& contentRow)
{
    CHECK_NULL_VOID(contentRow);
    for (const auto& child : contentRow->GetChildren()) {
        auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
        CHECK_NULL_VOID(frameNodeChild);
        auto layoutProperty = frameNodeChild->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::GONE);
    }
}

void DatePickerDialogView::SwitchContentRowButton(const RefPtr<FrameNode>& contentRow, bool useMilitary)
{
    if (!NeedAdaptForAging()) {
        return;
    }
    HideContentChildrenButton(contentRow);
    auto nextButton = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(2));
    CHECK_NULL_VOID(nextButton);
    auto nextButtonLayoutProperty = nextButton->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(nextButtonLayoutProperty);
    auto textNextPrevNode = AceType::DynamicCast<FrameNode>(nextButton->GetFirstChild());
    CHECK_NULL_VOID(textNextPrevNode);
    auto textLayoutProperty = textNextPrevNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (!switchFlag_) {
        if (isShowTime_ || datePickerMode_ == DatePickerMode::DATE) {
            nextButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            textLayoutProperty->UpdateContent(GetDialogAgingButtonText(true));
        } else {
            nextButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
            auto cancelButton = AceType::DynamicCast<FrameNode>(contentRow->GetFirstChild());
            auto cancelRst = UpdateButtonVisibility(cancelButton);
            CHECK_NULL_VOID(cancelRst);
            auto confirmButton = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
            auto confirmRst = UpdateButtonVisibility(confirmButton);
            CHECK_NULL_VOID(confirmRst);
        }
        UpdateNextButtonMargin(nextButtonLayoutProperty);
        textNextPrevNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        auto cancelButton = AceType::DynamicCast<FrameNode>(contentRow->GetFirstChild());
        auto cancelRst = UpdateButtonVisibility(cancelButton);
        CHECK_NULL_VOID(cancelRst);
        auto divideNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(1));
        auto divideRst = UpdateButtonVisibility(divideNode);
        CHECK_NULL_VOID(divideRst);
        nextButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        textLayoutProperty->UpdateContent(GetDialogAgingButtonText(true));
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        auto dialogTheme = pipeline->GetTheme<DialogTheme>();
        CHECK_NULL_VOID(dialogTheme);
        UpdateConfirmButtonMargin(nextButtonLayoutProperty, dialogTheme);
        textNextPrevNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    contentRow->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void DatePickerDialogView::ShowContentRowButton(const RefPtr<FrameNode>& contentRow, bool isFirstPage)
{
    auto initRst = InitContentRowVisibility(contentRow);
    CHECK_NULL_VOID(initRst);
    if (isFirstPage) {
        auto buttonCancelNode = AceType::DynamicCast<FrameNode>(contentRow->GetFirstChild());
        auto cancelRst = UpdateButtonVisibility(buttonCancelNode);
        CHECK_NULL_VOID(cancelRst);
        auto divideNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(1));
        CHECK_NULL_VOID(divideNode);
        auto divideLayoutProperty = divideNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(divideLayoutProperty);
        auto nextButton = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(NEXT_BUTTON_INDEX));
        CHECK_NULL_VOID(nextButton);
        auto nextButtonLayoutProperty = nextButton->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(nextButtonLayoutProperty);
        auto textNextPrevNode = AceType::DynamicCast<FrameNode>(nextButton->GetFirstChild());
        CHECK_NULL_VOID(textNextPrevNode);
        auto textLayoutProperty = textNextPrevNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (isShowTime_ || datePickerMode_ == DatePickerMode::DATE) {
            divideLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            nextButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            textLayoutProperty->UpdateContent(GetDialogAgingButtonText(true));
            textLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        } else {
            divideLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            nextButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
            textLayoutProperty->UpdateVisibility(VisibleType::GONE);
            auto confirmButton = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
            auto result = UpdateButtonVisibility(confirmButton);
            CHECK_NULL_VOID(result);
        }
        textNextPrevNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        auto nextButton = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(NEXT_BUTTON_INDEX));
        auto nextButtonRst = UpdateButtonVisibility(nextButton);
        CHECK_NULL_VOID(nextButtonRst);
        auto divideNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(DIVIDER_ROWS_THREE));
        auto divideRst = UpdateButtonVisibility(divideNode);
        CHECK_NULL_VOID(divideRst);
        auto confirmButton = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
        UpdateButtonVisibility(confirmButton);
    }
}

RefPtr<FrameNode> DatePickerDialogView::CreateButtonNodeForAging(const DatePickerSettingData& settingData,
    const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& monthAndDayNode,
    const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto dateAcceptEvent = dialogEvent["dateAcceptId"];
    auto cancelEvent = dialogCancelEvent["cancelId"];
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        MarginProperty margin;
        margin.top = CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON);
        layoutProps->UpdateMargin(margin);
    }

    contentRow->SetNeedCallChildrenUpdate(false);
    SetDialogDateAcceptEvent(monthAndDayNode, std::move(dateAcceptEvent));

    auto buttonCancelNode = CreateCancelNode(cancelEvent, datePickerNode, buttonInfos);
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto buttonConfirmNode = CreateConfirmNode(monthAndDayNode, datePickerNode, acceptEvent, buttonInfos);
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);
    auto cancelNextDividerNode = CreateDividerNode(datePickerNode, true);
    CHECK_NULL_RETURN(cancelNextDividerNode, nullptr);
    auto nextConfirmDividerNode = CreateDividerNode(datePickerNode, true);
    CHECK_NULL_RETURN(nextConfirmDividerNode, nullptr);

    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);

    RefPtr<FrameNode> buttonNextPreNode = nullptr;

    auto timePickerSwitchEvent =
        CreateAndSetTimePickerSwitchEvent(monthAndDayNode, timePickerNode, contentRow);
    buttonNextPreNode = CreateNextPrevButtonNode(
        timePickerSwitchEvent, datePickerNode, buttonInfos, contentRow);
    CHECK_NULL_RETURN(buttonNextPreNode, nullptr);
    contentRow->AddChild(buttonNextPreNode, 1);
    contentRow->AddChild(cancelNextDividerNode, 1);
    contentRow->AddChild(nextConfirmDividerNode, DIVIDER_ROWS_THREE);

    auto layoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    auto nextConfirmDividerProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(nextConfirmDividerProperty, nullptr);
    nextConfirmDividerProperty->UpdateVisibility(VisibleType::GONE);

    auto datePickerPattern = monthAndDayNode->GetPattern<DatePickerPattern>();
    datePickerPattern->SetContentRowNode(contentRow);

    return contentRow;
}

bool DatePickerDialogView::InitContentRowVisibility(const RefPtr<FrameNode>& contentRow)
{
    for (const auto& child : contentRow->GetChildren()) {
        auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(child);
        CHECK_NULL_RETURN(frameNodeChild, false);
        auto layoutProperty = frameNodeChild->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::GONE);
    }
    return true;
}

bool DatePickerDialogView::UpdateButtonVisibility(const RefPtr<FrameNode>& buttonNode)
{
    CHECK_NULL_RETURN(buttonNode, false);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, false);
    buttonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    return true;
}

RefPtr<FrameNode> DatePickerDialogView::CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& datePickerNode, DialogEvent& acceptEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();

    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);
    CHECK_NULL_RETURN(textConfirmNode, nullptr);
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    UpdateConfirmButtonTextLayoutProperty(textLayoutProperty, pickerTheme);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonConfirmEventHub = buttonConfirmNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonConfirmEventHub, nullptr);
    buttonConfirmEventHub->SetStateEffect(true);

    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonConfirmLayoutProperty, nullptr);
    UpdateButtonLayoutProperty(buttonConfirmLayoutProperty, pickerTheme);
    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, ACCEPT_BUTTON_INDEX, buttonConfirmLayoutProperty, buttonConfirmRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonConfirmNode, true);
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    CHECK_NULL_RETURN(dateNode, nullptr);
    SetDialogAcceptEvent(dateNode, std::move(acceptEvent));
    auto clickCallback = [weak = WeakPtr<FrameNode>(dateNode)](const GestureEvent& /* info */) {
        auto dateNode = weak.Upgrade();
        CHECK_NULL_VOID(dateNode);
        auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto datePickerEventHub = pickerPattern->GetOrCreateEventHub<DatePickerEventHub>();
        CHECK_NULL_VOID(datePickerEventHub);
        datePickerEventHub->FireDialogAcceptEvent(pickerPattern->GetSelectedObject(true));
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonConfirmNode->MarkModifyDone();
    return buttonConfirmNode;
}

void DatePickerDialogView::UpdateConfirmButtonTextLayoutProperty(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(GetDialogNormalButtonText(true));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
}

void DatePickerDialogView::UpdateCancelButtonTextLayoutProperty(
    const RefPtr<TextLayoutProperty>& textCancelLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(textCancelLayoutProperty);
    textCancelLayoutProperty->UpdateContent(GetDialogNormalButtonText(false));
    textCancelLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textCancelLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textCancelLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textCancelLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
}

void DatePickerDialogView::UpdateButtonLayoutProperty(
    const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateLabel(GetDialogNormalButtonText(true));
    buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }

    buttonConfirmLayoutProperty->UpdateFlexShrink(1.0);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    UpdateConfirmButtonMargin(buttonConfirmLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

void DatePickerDialogView::UpdateConfirmButtonMargin(
    const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, true, ModuleDialogType::DATEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, false, ModuleDialogType::DATEPICKER_DIALOG);
    }
    buttonConfirmLayoutProperty->UpdateMargin(margin);
}

void DatePickerDialogView::UpdateCancelButtonMargin(
    const RefPtr<ButtonLayoutProperty>& buttonCancelLayoutProperty, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, true, ModuleDialogType::DATEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, false,
            ModuleDialogType::DATEPICKER_DIALOG);
    }
    buttonCancelLayoutProperty->UpdateMargin(margin);
}

void DatePickerDialogView::UpdateNextButtonMargin(const RefPtr<ButtonLayoutProperty>& buttonNextLayoutProperty)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.right = CalcLength(dialogTheme->GetDividerPadding().Left());
        margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        margin.top = CalcLength(BUTTON_BOTTOM_TOP_MARGIN);
        margin.bottom = CalcLength(BUTTON_BOTTOM_TOP_MARGIN);
    } else {
        margin.right = CalcLength(TITLE_PADDING_HORIZONTAL);
        margin.left = CalcLength(TITLE_PADDING_HORIZONTAL);
        margin.top = CalcLength(TITLE_PADDING_HORIZONTAL);
        margin.bottom = CalcLength(TITLE_PADDING_HORIZONTAL);
    }
    buttonNextLayoutProperty->UpdateMargin(margin);
}

void DatePickerDialogView::UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].type.has_value()) {
        buttonLayoutProperty->UpdateType(buttonInfos[index].type.value());
    }
    UpdateButtonStyleAndRole(buttonInfos, index, buttonLayoutProperty, buttonRenderContext, buttonTheme);
    if (buttonInfos[index].fontSize.has_value()) {
        buttonLayoutProperty->UpdateFontSize(ConvertFontScaleValue(buttonInfos[index].fontSize.value()));
    }
    if (buttonInfos[index].fontColor.has_value()) {
        buttonLayoutProperty->UpdateFontColor(buttonInfos[index].fontColor.value());
    }
    if (buttonInfos[index].fontWeight.has_value()) {
        buttonLayoutProperty->UpdateFontWeight(buttonInfos[index].fontWeight.value());
    }
    if (buttonInfos[index].fontStyle.has_value()) {
        buttonLayoutProperty->UpdateFontStyle(buttonInfos[index].fontStyle.value());
    }
    if (buttonInfos[index].fontFamily.has_value()) {
        buttonLayoutProperty->UpdateFontFamily(buttonInfos[index].fontFamily.value());
    }
    if (buttonInfos[index].borderRadius.has_value()) {
        buttonLayoutProperty->UpdateBorderRadius(buttonInfos[index].borderRadius.value());
    }
    if (buttonInfos[index].backgroundColor.has_value()) {
        buttonRenderContext->UpdateBackgroundColor(buttonInfos[index].backgroundColor.value());
    }
}

void DatePickerDialogView::UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
    const RefPtr<ButtonTheme>& buttonTheme)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].role.has_value()) {
        buttonLayoutProperty->UpdateButtonRole(buttonInfos[index].role.value());
        ButtonStyleMode buttonStyleMode;
        if (buttonInfos[index].buttonStyle.has_value()) {
            buttonStyleMode = buttonInfos[index].buttonStyle.value();
        } else {
            buttonStyleMode = buttonLayoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        }
        auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonInfos[index].role.value());
        auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonInfos[index].role.value());
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
    if (buttonInfos[index].buttonStyle.has_value()) {
        buttonLayoutProperty->UpdateButtonStyle(buttonInfos[index].buttonStyle.value());
        ButtonRole buttonRole = buttonLayoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        auto bgColor = buttonTheme->GetBgColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        auto textColor = buttonTheme->GetTextColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
}

RefPtr<FrameNode> DatePickerDialogView::CreateDateNode(int32_t dateNodeId,
    std::map<std::string, PickerDate> datePickerProperty, const PickerTextProperties& properties, bool isLunar,
    bool showTime)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DATE_PICKER_ETS_TAG, dateNodeId);
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, dateNodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    CHECK_NULL_RETURN(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, nullptr);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    datePickerPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    datePickerPattern->SetIsShowInDialog(true);
    if (showTime) {
        CreateSingleDateNode(dateNode, showCount);
    } else {
        CreateNormalDateNode(dateNode, showCount);
    }

    PickerDate parseStartDate;
    PickerDate parseEndDate;
    PickerDate parseSelectedDate = PickerDate::Current();
    SetShowLunar(dateNode, isLunar);
    SetDateTextProperties(dateNode, properties);
    auto iterStart = datePickerProperty.find("start");
    if (iterStart != datePickerProperty.end()) {
        parseStartDate = iterStart->second;
        SetStartDate(dateNode, parseStartDate);
    }
    auto iterEnd = datePickerProperty.find("end");
    if (iterEnd != datePickerProperty.end()) {
        parseEndDate = iterEnd->second;
        SetEndDate(dateNode, parseEndDate);
    }
    auto iterSelected = datePickerProperty.find("selected");
    if (iterSelected != datePickerProperty.end()) {
        parseSelectedDate = iterSelected->second;
    }
    SetSelectedDate(dateNode, parseSelectedDate);
    return dateNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateColumnNode(int32_t nodeId, uint32_t showCount, bool isDate)
{
    RefPtr<FrameNode> columnNode;
    if (isDate) {
        columnNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    } else {
        columnNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    }
    CHECK_NULL_RETURN(columnNode, nullptr);
    columnNode->Clean();
    for (uint32_t index = 0; index < showCount; index++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MountToParent(columnNode);
    }
    columnNode->MarkModifyDone();
    return columnNode;
}

void DatePickerDialogView::CreateNormalDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount)
{
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetShowMonthDaysFlag(false);

    auto yearColumnNode = CreateColumnNode(datePickerPattern->GetYearId(), showCount);
    auto monthColumnNode = CreateColumnNode(datePickerPattern->GetMonthId(), showCount);
    auto dayColumnNode = CreateColumnNode(datePickerPattern->GetDayId(), showCount);
    CHECK_NULL_VOID(yearColumnNode);
    CHECK_NULL_VOID(monthColumnNode);
    CHECK_NULL_VOID(dayColumnNode);
    datePickerPattern->SetColumn(yearColumnNode);
    datePickerPattern->SetColumn(monthColumnNode);
    datePickerPattern->SetColumn(dayColumnNode);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (isShowTime_ || datePickerMode_ == DatePickerMode::DATE) {
            MountColumnNodeToPicker(yearColumnNode, dateNode, RATIO_THREE);
            MountColumnNodeToPicker(monthColumnNode, dateNode, RATIO_TWO);
            MountColumnNodeToPicker(dayColumnNode, dateNode, RATIO_TWO);
        } else {
            MountColumnNodeToPicker(yearColumnNode, dateNode);
            MountColumnNodeToPicker(monthColumnNode, dateNode);
            MountColumnNodeToPicker(dayColumnNode, dateNode);
        }
    } else {
        MountColumnNodeToPicker(yearColumnNode, dateNode);
        MountColumnNodeToPicker(monthColumnNode, dateNode);
        MountColumnNodeToPicker(dayColumnNode, dateNode);
    }
}

void DatePickerDialogView::CreateSingleDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount)
{
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetShowMonthDaysFlag(true);

    auto monthDaysColumnNode = CreateColumnNode(datePickerPattern->GetMonthDaysId(), showCount);
    auto yearColumnNode = CreateColumnNode(datePickerPattern->GetYearId(), showCount);
    CHECK_NULL_VOID(monthDaysColumnNode);
    CHECK_NULL_VOID(yearColumnNode);
    datePickerPattern->SetColumn(monthDaysColumnNode);
    datePickerPattern->SetColumn(yearColumnNode);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        MountColumnNodeToPicker(monthDaysColumnNode, dateNode, RATIO_FOUR);
    } else {
        MountColumnNodeToPicker(monthDaysColumnNode, dateNode);
    }

    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            datePickerPattern->SetEnableHapticFeedback(isEnableHapticFeedback_);
            datePickerPattern->ColumnPatternInitHapticController(monthDaysColumnNode);
        }
        auto stackYearNode = CreateStackNode();
        auto blendYearNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackYearNode);
        yearColumnNode->MountToParent(blendYearNode);
        blendYearNode->MountToParent(stackYearNode);
        auto layoutProperty = stackYearNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto blendYearNodeLayoutProperty = blendYearNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(blendYearNodeLayoutProperty);
            blendYearNodeLayoutProperty->UpdateVisibility(VisibleType::GONE);
            auto buttonYearNodeLayoutProperty = buttonYearNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(buttonYearNodeLayoutProperty);
            buttonYearNodeLayoutProperty->UpdateVisibility(VisibleType::GONE);
        } else {
            layoutProperty->UpdateVisibility(VisibleType::GONE);
        }
        layoutProperty->UpdateLayoutWeight(0);
        stackYearNode->MountToParent(dateNode);
    }
}

RefPtr<FrameNode> DatePickerDialogView::CreateTimeNode(
    std::map<std::string, PickerTime> timePickerProperty, const PickerTextProperties& properties, bool useMilitaryTime)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TIME_PICKER_ETS_TAG, nodeId);
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    CHECK_NULL_RETURN(timePickerNode, nullptr);
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetIsShowInDialog(true);
    timePickerRowPattern->SetIsShowInDatePickerDialog(true);
    timePickerRowPattern->SetIsEnableHaptic(isEnableHapticFeedback_);

    auto hasHourNode = timePickerRowPattern->HasHourNode();
    auto hasMinuteNode = timePickerRowPattern->HasMinuteNode();

    auto hourColumnNode = CreateColumnNode(timePickerRowPattern->GetHourId(), showCount, false);
    auto minuteColumnNode = CreateColumnNode(timePickerRowPattern->GetMinuteId(), showCount, false);
    CHECK_NULL_RETURN(hourColumnNode, nullptr);
    CHECK_NULL_RETURN(minuteColumnNode, nullptr);
    timePickerRowPattern->SetColumn(hourColumnNode);
    timePickerRowPattern->SetColumn(minuteColumnNode);

    if (!hasHourNode) {
        MountColumnNodeToPicker(hourColumnNode, timePickerNode);
    }
    if (!hasMinuteNode) {
        MountColumnNodeToPicker(minuteColumnNode, timePickerNode);
    }
    auto it = timePickerProperty.find("selected");
    if (it != timePickerProperty.end()) {
        auto selectedTime = it->second;
        timePickerRowPattern->SetSelectedTime(selectedTime);
    }
    timePickerRowPattern->SetHour24(useMilitaryTime);

    SetTimeTextProperties(timePickerNode, properties);
    return timePickerNode;
}

void DatePickerDialogView::MountColumnNodeToPicker(
    const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& pickerNode, uint32_t columnWeight)
{
    auto stackNode = CreateStackNode();
    auto blendNode = CreateColumnNode();
    auto buttonNode = CreateButtonNode();
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    layoutProperty->UpdateLayoutWeight(columnWeight);
    stackNode->MountToParent(pickerNode);
}

RefPtr<FrameNode> DatePickerDialogView::CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
    const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textCancelLayoutProperty, nullptr);
    UpdateCancelButtonTextLayoutProperty(textCancelLayoutProperty, pickerTheme);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    datePickerPattern->SetCancelNode(buttonCancelNode);
    textCancelNode->MountToParent(buttonCancelNode);
    auto eventCancelHub = buttonCancelNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventCancelHub, nullptr);
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));

    auto buttonCancelEventHub = buttonCancelNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonCancelEventHub, nullptr);
    buttonCancelEventHub->SetStateEffect(true);

    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonCancelLayoutProperty->UpdateLabel(GetDialogNormalButtonText(false));
    buttonCancelLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (buttonCancelNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        buttonCancelLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonCancelLayoutProperty->UpdateFlexShrink(1.0);
    UpdateCancelButtonMargin(buttonCancelLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }

    auto buttonCancelRenderContext = buttonCancelNode->GetRenderContext();
    buttonCancelRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonCancelLayoutProperty, buttonCancelRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonCancelNode, false);
    buttonCancelNode->MarkModifyDone();
    return buttonCancelNode;
}

void DatePickerDialogView::UpdateCheckboxPaintProperty(const RefPtr<CheckBoxPaintProperty>& checkboxPaintProps,
    bool isLunar, const CheckboxSettingData& checkboxSettingData)
{
    checkboxPaintProps->UpdateCheckBoxSelect(isLunar);
    if (checkboxSettingData.selectedColor.has_value()) {
        checkboxPaintProps->UpdateCheckBoxSelectedColor(checkboxSettingData.selectedColor.value());
    }
    if (checkboxSettingData.unselectedColor.has_value()) {
        checkboxPaintProps->UpdateCheckBoxUnSelectedColor(checkboxSettingData.unselectedColor.value());
    }
    if (checkboxSettingData.strokeColor.has_value()) {
        checkboxPaintProps->UpdateCheckBoxCheckMarkColor(checkboxSettingData.strokeColor.value());
    }
}

void DatePickerDialogView::CreateLunarswitchNode(const RefPtr<FrameNode>& contentColumn,
    const RefPtr<FrameNode>& dateNode, std::function<void(const bool)>&& changeEvent, bool isLunar,
    const CheckboxSettingData& checkboxSettingData)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto contentRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(contentRow);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        MarginProperty margin;
        margin.bottom = CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON);
        layoutProps->UpdateMargin(margin);
    }
    layoutProps->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(LUNARSWITCH_HEIGHT)));

    auto checkbox = FrameNode::CreateFrameNode(
        V2::CHECK_BOX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<CheckBoxPattern>());
    CHECK_NULL_VOID(checkbox);
    auto eventHub = checkbox->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(changeEvent));
    auto checkboxPaintProps = checkbox->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(checkboxPaintProps);
    UpdateCheckboxPaintProperty(checkboxPaintProps, isLunar, checkboxSettingData);
    auto checkboxPattern = checkbox->GetPattern<CheckBoxPattern>();
    checkboxPattern->SaveCheckboxSettingData(checkboxSettingData);
    auto checkboxLayoutProps = checkbox->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(checkboxLayoutProps);
    MarginProperty marginCheckbox;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    marginCheckbox.left = isRtl ? CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON)
                                : CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
    marginCheckbox.right = isRtl ? CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE)
                                 : CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON);
    checkboxLayoutProps->UpdateMargin(marginCheckbox);
    checkboxLayoutProps->UpdateUserDefinedIdealSize(CalcSize(CalcLength(CHECKBOX_SIZE), CalcLength(CHECKBOX_SIZE)));
    checkbox->MarkModifyDone();
    checkbox->MountToParent(contentRow);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetLunarSwitchCheckbox(checkbox);

    auto textNode = CreateLunarSwitchTextNode();
    CHECK_NULL_VOID(textNode);
    textNode->MountToParent(contentRow);
    datePickerPattern->SetLunarSwitchTextNode(textNode);

    contentRow->MountToParent(contentColumn);
}

void DatePickerDialogView::SetStartDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value)
{
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateStartDate(datePickerPattern->GetStartDateLunar());
}

void DatePickerDialogView::SetEndDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value)
{
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateEndDate(datePickerPattern->GetEndDateLunar());
}

void DatePickerDialogView::SetSelectedDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value)
{
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateSelectedDate(datePickerPattern->GetSelectDate());
}

void DatePickerDialogView::SetMode(const RefPtr<FrameNode>& frameNode, const DatePickerMode& mode)
{
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetMode(mode);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateMode(mode);
}

void DatePickerDialogView::SetShowLunar(const RefPtr<FrameNode>& frameNode, bool lunar)
{
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    pickerProperty->UpdateLunar(lunar);
}

void DatePickerDialogView::SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogChange(std::move(onChange));
}

void DatePickerDialogView::SetDialogDateChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogDateChange(std::move(onChange));
}

void DatePickerDialogView::SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogAcceptEvent(std::move(onChange));
}

void DatePickerDialogView::SetDialogDateAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogDateAcceptEvent(std::move(onChange));
}

void DatePickerDialogView::SetDialogSwitchEvent(std::function<bool()> switchEvent, const RefPtr<FrameNode>& pickerStack)
{
    CHECK_NULL_VOID(pickerStack);
    auto pipeline = pickerStack->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManger = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManger);
    overlayManger->SetBackPressEvent(switchEvent);
}

void DatePickerDialogView::SetDateTextProperties(
    const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);

    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateDisappearFontSize(
            ConvertFontScaleValue(properties.disappearTextStyle_.fontSize.value(), disappearTextStyleFont_, true));
    } else {
        pickerProperty->UpdateDisappearFontSize(ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    pickerProperty->UpdateDisappearColor(
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    pickerProperty->UpdateDisappearWeight(
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));
    pickerProperty->UpdateDisappearFontFamily(
        properties.disappearTextStyle_.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    pickerProperty->UpdateDisappearFontStyle(
        properties.disappearTextStyle_.fontStyle.value_or(disappearStyle.GetFontStyle()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateFontSize(
            ConvertFontScaleValue(properties.normalTextStyle_.fontSize.value(), normalTextStyleFont_, true));
    } else {
        pickerProperty->UpdateFontSize(ConvertFontScaleValue(normalStyle.GetFontSize()));
    }
    pickerProperty->UpdateColor(properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    pickerProperty->UpdateWeight(properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));
    pickerProperty->UpdateFontFamily(properties.normalTextStyle_.fontFamily.value_or(normalStyle.GetFontFamilies()));
    pickerProperty->UpdateFontStyle(properties.normalTextStyle_.fontStyle.value_or(normalStyle.GetFontStyle()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateSelectedFontSize(
            ConvertFontScaleValue(properties.selectedTextStyle_.fontSize.value(), selectedTextStyleFont_, true));
    } else {
        pickerProperty->UpdateSelectedFontSize(ConvertFontScaleValue(selectedStyle.GetFontSize()));
    }
    pickerProperty->UpdateSelectedColor(properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    pickerProperty->UpdateSelectedWeight(
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
    pickerProperty->UpdateSelectedFontFamily(
        properties.selectedTextStyle_.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    pickerProperty->UpdateSelectedFontStyle(
        properties.selectedTextStyle_.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void DatePickerDialogView::SetTimeTextProperties(
    const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);

    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateDisappearFontSize(
            ConvertFontScaleValue(properties.disappearTextStyle_.fontSize.value(), disappearTextStyleFont_, true));
    } else {
        pickerProperty->UpdateDisappearFontSize(ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    pickerProperty->UpdateDisappearColor(
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    pickerProperty->UpdateDisappearWeight(
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateFontSize(
            ConvertFontScaleValue(properties.normalTextStyle_.fontSize.value(), normalTextStyleFont_, true));
    } else {
        pickerProperty->UpdateFontSize(ConvertFontScaleValue(normalStyle.GetFontSize()));
    }
    pickerProperty->UpdateColor(properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    pickerProperty->UpdateWeight(properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateSelectedFontSize(
            ConvertFontScaleValue(properties.selectedTextStyle_.fontSize.value(), selectedTextStyleFont_, true));
    } else {
        pickerProperty->UpdateSelectedFontSize(ConvertFontScaleValue(selectedStyle.GetFontSize()));
    }
    pickerProperty->UpdateSelectedColor(properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    pickerProperty->UpdateSelectedWeight(
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
}

void DatePickerDialogView::SetTitleMouseHoverEvent(const RefPtr<FrameNode>& titleRow)
{
    auto titleButtonNode = AceType::DynamicCast<FrameNode>(titleRow->GetFirstChild());
    CHECK_NULL_VOID(titleButtonNode);
    auto eventHub = titleButtonNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto mouseTask = [weak = WeakPtr<FrameNode>(titleButtonNode)](bool isHover) {
        auto titleButtonNode = weak.Upgrade();
        CHECK_NULL_VOID(titleButtonNode);
        HandleMouseEvent(titleButtonNode, isHover);
    };
    auto mouseEvent = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask));
    CHECK_NULL_VOID(mouseEvent);
    inputHub->AddOnHoverEvent(mouseEvent);
}

void DatePickerDialogView::HandleMouseEvent(const RefPtr<FrameNode>& titleButton, bool isHover)
{
    if (isHover) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_VOID(theme);
        PlayHoverAnimation(titleButton, theme->GetHoverColor());
    } else {
        PlayHoverAnimation(titleButton, Color::TRANSPARENT);
    }
}

void DatePickerDialogView::PlayHoverAnimation(const RefPtr<FrameNode>& titleButton, const Color& color)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = WeakPtr<FrameNode>(titleButton), color]() {
        auto titleButton = weak.Upgrade();
        auto buttonTitleNode = AceType::DynamicCast<FrameNode>(titleButton);
        CHECK_NULL_VOID(buttonTitleNode);
        auto buttonTitleRenderContext = buttonTitleNode->GetRenderContext();
        buttonTitleRenderContext->UpdateBackgroundColor(color);
        buttonTitleNode->MarkDirtyNode();
    });
}

RefPtr<FrameNode> DatePickerDialogView::CreateAndMountDateNode(
    const DatePickerSettingData& settingData, const RefPtr<FrameNode>& pickerStack)
{
    auto dateNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    datePickerMode_ = settingData.mode;
    auto dateNode =
        CreateDateNode(dateNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    SetMode(dateNode, settingData.mode);
    ViewStackProcessor::GetInstance()->Push(dateNode);
    dateNode->MountToParent(pickerStack);
    return dateNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateAndMountButtonTitleNode(
    const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& contentColumn)
{
    // create title node and bind title text id to date picker, then mark picker node modify done
    auto buttonTitleNode = CreateTitleButtonNode(dateNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);

    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto layoutProps = buttonTitleNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        PaddingProperty padding;
        padding.left = CalcLength(TITLE_PADDING_HORIZONTAL);
        padding.right = CalcLength(TITLE_PADDING_HORIZONTAL);
        layoutProps->UpdatePadding(padding);
        MarginProperty margin;
        margin.top = CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON);
        margin.bottom = CalcLength(PICKER_MARGIN_FROM_TITLE_AND_BUTTON);
        layoutProps->UpdateMargin(margin);
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(TITLE_HEIGHT)));
    }

    buttonTitleNode->MountToParent(contentColumn);
    return buttonTitleNode;
}

std::function<void(bool)> DatePickerDialogView::CreateLunarChangeEvent(const RefPtr<FrameNode>& dateNode)
{
    return [weak = AceType::WeakClaim(AceType::RawPtr(dateNode))](bool selected) {
        auto datePicker = weak.Upgrade();
        CHECK_NULL_VOID(datePicker);
        auto datePickerPattern = datePicker->GetPattern<DatePickerPattern>();
        CHECK_NULL_VOID(datePickerPattern);
        SetSelectedDate(datePicker, datePickerPattern->GetCurrentDate());
        auto layoutProp = datePicker->GetLayoutProperty<DataPickerRowLayoutProperty>();
        CHECK_NULL_VOID(layoutProp);
        layoutProp->UpdateLunar(selected);
        datePicker->MarkModifyDone();
    };
}

RefPtr<FrameNode> DatePickerDialogView::CreateAndMountMonthDaysNode(const DatePickerSettingData& settingData,
    const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& pickerRow, std::function<void(bool)>&& lunarChangeEvent)
{
    auto layoutProperty = dateNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    auto monthDaysNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto monthDaysNode = CreateDateNode(
        monthDaysNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    lunarChangeEvent = [monthDaysNodeWeak = AceType::WeakClaim(AceType::RawPtr(monthDaysNode)),
                           dateNodeWeak = AceType::WeakClaim(AceType::RawPtr(dateNode))](bool selected) {
        auto monthDaysNode = monthDaysNodeWeak.Upgrade();
        auto dateNode = dateNodeWeak.Upgrade();
        CHECK_NULL_VOID(monthDaysNode);
        CHECK_NULL_VOID(dateNode);
        auto result = SetSelectedDateAndFocus(monthDaysNode, dateNode);
        CHECK_NULL_VOID(result);
        SetShowLunar(monthDaysNode, selected);
        SetShowLunar(dateNode, selected);
        monthDaysNode->MarkModifyDone();
        dateNode->MarkModifyDone();
    };
    auto monthDaysPickerPattern = monthDaysNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(monthDaysPickerPattern, nullptr);
    monthDaysPickerPattern->SetTextProperties(settingData.properties);
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    monthDaysPickerPattern->SetTitleId(pickerPattern->GetTitleId());
    monthDaysPickerPattern->SetShowTimeFlag(true);
    monthDaysPickerPattern->SetShowLunarSwitch(settingData.lunarswitch);
    pickerPattern->SetShowTimeFlag(true);
    auto monthDaysLayoutProperty = monthDaysNode->GetLayoutProperty();
    CHECK_NULL_RETURN(monthDaysLayoutProperty, nullptr);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        monthDaysLayoutProperty->UpdateLayoutWeight(settingData.useMilitary ? RATIO_THREE : RATIO_FOUR);
    } else {
        monthDaysLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(
                Dimension(settingData.useMilitary ? MONTHDAYS_WIDTH_PERCENT_ONE : MONTHDAYS_WIDTH_PERCENT_TWO,
                DimensionUnit::PERCENT)), std::nullopt));
    }
    monthDaysNode->MarkModifyDone();
    monthDaysNode->MountToParent(pickerRow);
    return monthDaysNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateAndMountTimeNode(const DatePickerSettingData& settingData,
    const RefPtr<FrameNode>& monthDaysNode, const RefPtr<FrameNode>& pickerRow)
{
    auto timeNode = CreateTimeNode(settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    auto timePickerEventHub = timeNode->GetOrCreateEventHub<TimePickerEventHub>();
    CHECK_NULL_RETURN(timePickerEventHub, nullptr);
    auto timePickerRowPattern = timeNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetTextProperties(settingData.properties);
    timePickerRowPattern->SetShowLunarSwitch(settingData.lunarswitch);
    auto timePickerLayout = timeNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(timePickerLayout, nullptr);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ZeroPrefixType hourOptions = settingData.dateTimeOptions.hourType;
        ZeroPrefixType minuteOptions = settingData.dateTimeOptions.minuteType;
        if ((timePickerRowPattern->GetPrefixHour() != hourOptions) ||
            (timePickerRowPattern->GetPrefixMinute() != minuteOptions)) {
            timePickerRowPattern->SetDateTimeOptionUpdate(true);
        }
        timePickerRowPattern->SetPrefixHour(hourOptions);
        timePickerRowPattern->SetPrefixMinute(minuteOptions);
        timePickerLayout->UpdatePrefixHour(static_cast<int32_t>(hourOptions));
        timePickerLayout->UpdatePrefixMinute(static_cast<int32_t>(minuteOptions));
    }
    auto onChangeCallback = [weak = WeakPtr<FrameNode>(monthDaysNode)]() {
        auto monthDaysNode = weak.Upgrade();
        CHECK_NULL_VOID(monthDaysNode);
        auto pickerPattern = monthDaysNode->GetPattern<DatePickerPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto str = pickerPattern->GetSelectedObject(true);
        auto datePickerEventHub = pickerPattern->GetOrCreateEventHub<DatePickerEventHub>();
        CHECK_NULL_VOID(datePickerEventHub);
        datePickerEventHub->FireDialogChangeEvent(str);
    };
    timePickerEventHub->SetOnChangeForDatePicker(std::move(onChangeCallback));
    timeNode->MarkModifyDone();
    SetTimeNodeColumnWeight(timeNode, settingData);
    timeNode->MountToParent(pickerRow);
    if (NeedAdaptForAging()) {
        timePickerLayout->UpdateVisibility(VisibleType::GONE);
    }
    return timeNode;
}

bool DatePickerDialogView::SetSelectedDateAndFocus(const RefPtr<FrameNode>& monthDaysNode,
    const RefPtr<FrameNode>& dateNode)
{
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, false);
    auto monthDaysPattern = monthDaysNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(monthDaysPattern, false);
    PickerDate selectedDate = PickerDate::Current();
    if (switchFlag_) {
        selectedDate = datePickerPattern->GetCurrentDate();
        monthDaysPattern->SetFocusDisable();
        datePickerPattern->SetFocusEnable();
    } else {
        selectedDate = monthDaysPattern->GetCurrentDate();
        monthDaysPattern->SetFocusEnable();
        datePickerPattern->SetFocusDisable();
    }
    SetSelectedDate(dateNode, selectedDate);
    SetSelectedDate(monthDaysNode, selectedDate);
    return true;
}

std::function<void()> DatePickerDialogView::CreateAndSetDialogSwitchEvent(const RefPtr<FrameNode>& pickerStack,
    const RefPtr<FrameNode>& contentColumn, const DatePickerSettingData& settingData)
{
    RefPtr<DateTimeAnimationController> animationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    auto titleSwitchEvent = [weakContentColumn = AceType::WeakClaim(AceType::RawPtr(contentColumn)),
                                weakPickerStack = AceType::WeakClaim(AceType::RawPtr(pickerStack)),
                                animationController,
                                useMilitary = settingData.useMilitary]() {
        auto contentColumn = weakContentColumn.Upgrade();
        CHECK_NULL_VOID(contentColumn);
        auto pickerStack = weakPickerStack.Upgrade();
        CHECK_NULL_VOID(pickerStack);
        // switch picker page.
        SwitchPickerPage(pickerStack, contentColumn, animationController, useMilitary);
    };
    auto switchEvent = [func = titleSwitchEvent]() {
        if (switchFlag_) {
            func();
            return true;
        }
        return false;
    };
    SetDialogSwitchEvent(switchEvent, pickerStack);
    return titleSwitchEvent;
}

void DatePickerDialogView::SwitchPickerPage(const RefPtr<FrameNode>& pickerStack,
    const RefPtr<FrameNode>& contentColumn, const RefPtr<DateTimeAnimationController>& animationController,
    bool useMilitary)
{
    auto pickerRow = pickerStack->GetLastChild();
    CHECK_NULL_VOID(pickerRow);
    auto dateNode = AceType::DynamicCast<FrameNode>(pickerStack->GetChildAtIndex(0));
    CHECK_NULL_VOID(dateNode);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto monthDaysNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timeNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(timeNode);
    auto timePickerPattern = timeNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerPattern);
    auto monthDaysPickerPattern = monthDaysNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(monthDaysPickerPattern);
    PickerDate selectedDate =
        switchFlag_ ? datePickerPattern->GetCurrentDate() : monthDaysPickerPattern->GetCurrentDate();
    SetSelectedDate(switchFlag_ ? monthDaysNode : dateNode, selectedDate);
    animationController->SetDatePickerButtonHide(false);
    auto contentRow = AceType::DynamicCast<FrameNode>(contentColumn->GetLastChild());
    if (switchFlag_) {
        if (NeedAdaptForAging()) {
            switchTimePickerFlag_ = true;
            SwitchTimePickerPage(monthDaysNode, timeNode, contentRow);
        } else {
            timePickerPattern->SetFocusEnable();
        }
        datePickerPattern->SetFocusDisable();
        datePickerPattern->ColumnPatternStopHaptic();
        monthDaysPickerPattern->SetFocusEnable();
        monthDaysNode->MarkModifyDone();
    } else {
        monthDaysPickerPattern->SetFocusDisable();
        monthDaysPickerPattern->ColumnPatternStopHaptic();
        timePickerPattern->SetFocusDisable();
        timePickerPattern->ColumnPatternStopHaptic();
        datePickerPattern->SetFocusEnable();
        if (NeedAdaptForAging()) {
            SwitchDatePickerPage(dateNode, true);
            animationController->SetDatePickerButtonHide(true);
        }
        dateNode->MarkModifyDone();
    }
    SwitchContentRowButton(contentRow, useMilitary);
    SetAnimationProperty(pickerStack, contentColumn, animationController);
    switchFlag_ = !switchFlag_;
    animationController->Play(switchFlag_);
    ToggleTitleDisplay(datePickerPattern, monthDaysPickerPattern);
}

void DatePickerDialogView::ToggleTitleDisplay(
    RefPtr<DatePickerPattern>& datePickerPattern, RefPtr<DatePickerPattern>& monthDaysPickerPattern)
{
    if (!switchFlag_) {
        monthDaysPickerPattern->ShowTitle(monthDaysPickerPattern->GetTitleId());
    } else {
        datePickerPattern->ShowTitle(datePickerPattern->GetTitleId());
    }
}

void DatePickerDialogView::SetAnimationProperty(const RefPtr<FrameNode>& pickerStack,
    const RefPtr<FrameNode>& contentColumn, const RefPtr<DateTimeAnimationController>& animationController)
{
    auto pickerRow = pickerStack->GetLastChild();
    CHECK_NULL_VOID(pickerRow);
    auto dateNode = AceType::DynamicCast<FrameNode>(pickerStack->GetChildAtIndex(0));
    CHECK_NULL_VOID(dateNode);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto monthDaysNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timeNode = AceType::DynamicCast<FrameNode>(pickerRow->GetChildAtIndex(1));
    CHECK_NULL_VOID(monthDaysNode);
    CHECK_NULL_VOID(timeNode);
    auto titleRow = AceType::DynamicCast<FrameNode>(contentColumn->GetChildAtIndex(0));
    CHECK_NULL_VOID(titleRow);
    auto titleButtonNode = AceType::DynamicCast<FrameNode>(titleRow->GetFirstChild());
    CHECK_NULL_VOID(titleButtonNode);
    auto titleButtonRowNode = AceType::DynamicCast<FrameNode>(titleButtonNode->GetFirstChild());
    CHECK_NULL_VOID(titleButtonRowNode);
    auto spinnerNode = AceType::DynamicCast<FrameNode>(titleButtonRowNode->GetLastChild());
    CHECK_NULL_VOID(spinnerNode);
    auto contentRow = AceType::DynamicCast<FrameNode>(contentColumn->GetLastChild());
    CHECK_NULL_VOID(contentRow);
    animationController->SetButtonIcon(spinnerNode);
    animationController->SetMonthDays(monthDaysNode);
    animationController->SetDatePicker(dateNode);
    animationController->SetTimePicker(timeNode);
    animationController->SetButtonRow(contentRow);
}

void DatePickerDialogView::CreateAndAddTitleClickEvent(
    std::function<void()>& titleSwitchEvent, const RefPtr<FrameNode>& buttonTitleNode)
{
    auto titleClickEvent = [func = std::move(titleSwitchEvent)](const GestureEvent& /* info */) { func(); };
    auto titleButtonNode = AceType::DynamicCast<FrameNode>(buttonTitleNode->GetFirstChild());
    CHECK_NULL_VOID(titleButtonNode);
    auto titleEventHub = titleButtonNode->GetOrCreateGestureEventHub();
    auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(titleClickEvent));
    titleEventHub->AddClickEvent(onClick);
}

void DatePickerDialogView::BuildDialogAcceptAndCancelButton(const std::vector<ButtonInfo>& buttonInfos,
    const DatePickerSettingData& settingData, const RefPtr<FrameNode>& acceptNode, const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& dialogNode, const RefPtr<FrameNode>& contentColumn,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto changeEvent = dialogEvent["changeId"];
    DialogEvent dateChangeEvent = GetDateChangeEvent(dialogNode, dialogEvent);
    if (settingData.showTime) {
        auto changeEventSame = changeEvent;
        auto dateChangeEventSame = dateChangeEvent;
        SetDialogChange(acceptNode, std::move(changeEventSame));
        SetDialogDateChange(acceptNode, std::move(dateChangeEventSame));
    }
    SetDialogChange(dateNode, std::move(changeEvent));
    SetDialogDateChange(dateNode, std::move(dateChangeEvent));
    auto contentRow = CreateButtonNode(acceptNode, dateNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    CHECK_NULL_VOID(contentRow);
    auto closeDiaglogEvent = CloseDialogEvent(dateNode, dialogNode);
    auto event = [func = std::move(closeDiaglogEvent)](const GestureEvent& /* info */) {
        func();
    };
    for (const auto& child : contentRow->GetChildren()) {
        auto firstChild = AceType::DynamicCast<FrameNode>(child);
        auto gesturHub = firstChild->GetOrCreateGestureEventHub();
        auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(event);
        gesturHub->AddClickEvent(onClick);
    }
    contentRow->AddChild(CreateDividerNode(dateNode), 1);
    contentRow->MountToParent(contentColumn);
}

std::function<void()> DatePickerDialogView::CloseDialogEvent(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& dialogNode)
{
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    auto event = [weak = WeakPtr<FrameNode>(dialogNode),
        weakDatePickerPattern = WeakPtr<DatePickerPattern>(datePickerPattern)]() {
        auto dialogNode = weak.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->SetIsPickerDialog(false);
        auto datePickerPattern = weakDatePickerPattern.Upgrade();
        CHECK_NULL_VOID(datePickerPattern);

        if (datePickerPattern->GetIsShowInDialog()) {
            auto pipeline = dialogNode->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->CloseDialog(dialogNode);
            datePickerPattern->SetIsShowInDialog(false);
        }
    };
    datePickerPattern->updateFontConfigurationEvent(event);
    return event;
}

void DatePickerDialogView::BuildDialogAcceptAndCancelButtonForAging(const std::vector<ButtonInfo>& buttonInfos,
    const DatePickerSettingData& settingData, const RefPtr<FrameNode>& timePickerNode,
    const RefPtr<FrameNode>& acceptNode, const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& dialogNode,
    const RefPtr<FrameNode>& contentColumn, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto changeEvent = dialogEvent["changeId"];
    DialogEvent dateChangeEvent = GetDateChangeEvent(dialogNode, dialogEvent);
    if (settingData.showTime) {
        auto changeEventSame = changeEvent;
        auto dateChangeEventSame = dateChangeEvent;
        SetDialogChange(acceptNode, std::move(changeEventSame));
        SetDialogDateChange(acceptNode, std::move(dateChangeEventSame));
    }
    SetDialogChange(dateNode, std::move(changeEvent));
    SetDialogDateChange(dateNode, std::move(dateChangeEvent));
    auto contentRow = CreateButtonNodeForAging(settingData, timePickerNode, acceptNode,
        dateNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    if (!isShowTime_) {
        SwitchDatePickerPage(dateNode, true);
        ShowContentRowButton(contentRow, true);
    }
    CHECK_NULL_VOID(contentRow);
    auto closeDialogEvent = CloseDialogEvent(dateNode, dialogNode);
    auto event = [func = std::move(closeDialogEvent)](const GestureEvent& /* info */) {
        func();
    };
    auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(event);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(0));
    CHECK_NULL_VOID(cancelButtonNode);
    auto cancelButtonGestureHub = cancelButtonNode->GetOrCreateGestureEventHub();
    cancelButtonGestureHub->AddClickEvent(onClick);
    auto confirmButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
    CHECK_NULL_VOID(confirmButtonNode);
    auto confirmButtonGestureHub = confirmButtonNode->GetOrCreateGestureEventHub();
    confirmButtonGestureHub->AddClickEvent(onClick);
    contentRow->MountToParent(contentColumn);
}

void DatePickerDialogView::UpdateContentPadding(const RefPtr<FrameNode>& contentColumn)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        PaddingProperty contentPadding;
        contentPadding.left = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
        contentPadding.right = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
        contentColumn->GetLayoutProperty()->UpdatePadding(contentPadding);
    }
}

void DatePickerDialogView::UpdateButtonDefaultFocus(
    const std::vector<ButtonInfo>& buttonInfos, const RefPtr<FrameNode>& buttonNode, bool isConfirm)
{
    bool setDefaultFocus = false;
    if (buttonInfos.size() > CANCEL_BUTTON_INDEX) {
        if (buttonInfos[ACCEPT_BUTTON_INDEX].isPrimary && buttonInfos[CANCEL_BUTTON_INDEX].isPrimary) {
            return;
        }
        auto index = isConfirm ? ACCEPT_BUTTON_INDEX : CANCEL_BUTTON_INDEX;
        if (buttonInfos[index].isPrimary) {
            setDefaultFocus = true;
        }
    } else if (buttonInfos.size() == CANCEL_BUTTON_INDEX) {
        bool isAcceptButtonPrimary = (buttonInfos[0].isAcceptButton && isConfirm && buttonInfos[0].isPrimary);
        bool isCancelButtonPrimary = (!buttonInfos[0].isAcceptButton && !isConfirm && buttonInfos[0].isPrimary);
        if (isAcceptButtonPrimary || isCancelButtonPrimary) {
            setDefaultFocus = true;
        }
    }
    if (setDefaultFocus && buttonNode) {
        auto focusHub = buttonNode->GetOrCreateFocusHub();
        if (focusHub) {
            focusHub->SetIsDefaultFocus(true);
        }
    }
}

RefPtr<FrameNode> DatePickerDialogView::CreateNextPrevButtonNode(std::function<void()>& switchEvent,
    const RefPtr<FrameNode>& dateNode, const std::vector<ButtonInfo>& buttonInfos, const RefPtr<FrameNode>& contentRow)
{
    CHECK_NULL_RETURN(dateNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto nextPrevButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(nextPrevButtonNode, nullptr);
    auto textNextPrevNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNextPrevNode, nullptr);
    auto textLayoutProperty = textNextPrevNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, nullptr);
    datePickerPattern->SetNextPrevButtonNode(nextPrevButtonNode);
    textLayoutProperty->UpdateContent(GetDialogAgingButtonText(true));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    textNextPrevNode->MountToParent(nextPrevButtonNode);
    auto nextPrevEventHub = nextPrevButtonNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(nextPrevEventHub, nullptr);
    nextPrevEventHub->SetStateEffect(true);
    auto buttonNextPrevLayoutProperty = nextPrevButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonNextPrevLayoutProperty->UpdateLabel(GetDialogAgingButtonText(true));
    buttonNextPrevLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (nextPrevButtonNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        buttonNextPrevLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonNextPrevLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonNextPrevLayoutProperty->UpdateFlexShrink(1.0);
    UpdateConfirmButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, nullptr);
        buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
    auto eventNextPrevmHub = nextPrevButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventNextPrevmHub, nullptr);
    auto onClickCallback = CreateNextPrevClickEvent(textNextPrevNode, nextPrevButtonNode, dialogTheme, dateNode,
        switchEvent, contentRow);
    eventNextPrevmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(onClickCallback));
    auto buttonNextPrevRenderContext = nextPrevButtonNode->GetRenderContext();
    buttonNextPrevRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonNextPrevLayoutProperty, buttonNextPrevRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, nextPrevButtonNode, false);
    nextPrevButtonNode->MarkModifyDone();
    return nextPrevButtonNode;
}

std::function<void(const GestureEvent&)> DatePickerDialogView::CreateNextPrevClickEvent(
    const RefPtr<FrameNode>& textNextPrevNode, const RefPtr<FrameNode>& nextPrevButtonNode,
    const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode>& dateNode,
    std::function<void()>& switchEvent, const RefPtr<FrameNode>& contentRow)
{
    auto onClickCallback = [textWeak = WeakPtr<FrameNode>(textNextPrevNode),
                            nextPrevButtonNodeWeak = WeakPtr<FrameNode>(nextPrevButtonNode),
                            dialogThemeWeak = WeakPtr<DialogTheme>(dialogTheme),
                               dateWeak = WeakPtr<FrameNode>(dateNode),
                               func = std::move(switchEvent),
                               contentWeak = WeakPtr<FrameNode>(contentRow)](const GestureEvent& /* info */) {
        auto dateNode = dateWeak.Upgrade();
        CHECK_NULL_VOID(dateNode);
        auto textNode = textWeak.Upgrade();
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto contentRow = contentWeak.Upgrade();
        CHECK_NULL_VOID(contentRow);
        auto nextPrevButtonNode = nextPrevButtonNodeWeak.Upgrade();
        CHECK_NULL_VOID(nextPrevButtonNode);
        auto dialogTheme = dialogThemeWeak.Upgrade();
        CHECK_NULL_VOID(dialogTheme);
        auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
        CHECK_NULL_VOID(datePickerPattern);
        auto buttonNextPrevLayoutProperty
                                = nextPrevButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
        if (!switchFlag_ && isShowTime_) {
            func();
        } else {
            SwitchDatePickerPage(dateNode);
        }
        if (textLayoutProperty->GetContent() == UtfUtils::Str8ToStr16(GetDialogAgingButtonText(true))) {
            if (!isShowTime_) {
                ShowContentRowButton(contentRow, false);
            }
            UpdateCancelButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
            textLayoutProperty->UpdateContent(GetDialogAgingButtonText(false));
            datePickerPattern->SetIsNext(false);
        } else {
            if (!isShowTime_) {
                ShowContentRowButton(contentRow, true);
            }
            UpdateConfirmButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
            textLayoutProperty->UpdateContent(GetDialogAgingButtonText(true));
        }
        if (switchFlag_ && isShowTime_) {
            UpdateNextButtonMargin(buttonNextPrevLayoutProperty);
        }
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    };
    return onClickCallback;
}

bool DatePickerDialogView::GetIsUserSetTextProperties(const PickerTextProperties& properties)
{
    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        isUserSetFont_ = true;
        return true;
    }

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        isUserSetFont_ = true;
        return true;
    }

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        isUserSetFont_ = true;
        return true;
    }
    isUserSetFont_ = false;
    return false;
}

bool DatePickerDialogView::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        Dimension(pipeline->GetRootHeight()).ConvertToVp() > pickerTheme->GetDeviceHeightLimit() &&
        (follow && (GreatOrEqual(maxAppFontScale, pickerTheme->GetMaxOneFontScale())))) {
        return true;
    }
    return false;
}

const Dimension DatePickerDialogView::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    auto adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(),
        pickerTheme->GetMaxTwoFontScale());
    return fontSizeValue * adjustedScale;
}

const Dimension DatePickerDialogView::ConvertFontScaleValue(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);
    float fontSizeScale = pipeline->GetFontScale();
    Dimension fontSizeValueResult = fontSizeValue;
    Dimension fontSizeValueResultVp(fontSizeLimit.Value(), DimensionUnit::VP);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();

    if (fontSizeValue.Unit() == DimensionUnit::VP) {
        return isUserSetFont ? std::min(fontSizeValueResultVp, fontSizeValue) : fontSizeValue;
    }
    if (pipeline->IsFollowSystem() && (!NearZero(maxAppFontScale))) {
        fontSizeScale = std::min(fontSizeScale, maxAppFontScale);
    }
    if (NeedAdaptForAging()) {
        if (isUserSetFont) {
            if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontSizeScale,
                fontSizeLimit.ConvertToPx()) && (fontSizeScale != 0.0f)) {
                fontSizeValueResult = fontSizeLimit / fontSizeScale;
            } else {
                fontSizeValueResult = fontSizeValue;
            }
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxThirdFontScale())) {
                fontSizeScale = pickerTheme->GetMaxTwoFontScale() / pickerTheme->GetMaxThirdFontScale();
                fontSizeValueResult = fontSizeValue * fontSizeScale;
            }
        }
    } else {
        if (isUserSetFont) {
            fontSizeValueResult = ConvertFontSizeLimit(fontSizeValueResult, fontSizeLimit, isUserSetFont);
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxOneFontScale()) &&
                 (!NearZero(fontSizeScale))) {
                fontSizeValueResult = fontSizeValueResult / fontSizeScale;
            }
        }
    }
    return fontSizeValueResult;
}

const Dimension DatePickerDialogView::ConvertFontSizeLimit(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    if (isUserSetFont == false) {
        return fontSizeValue;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto fontScale = pipeline->GetFontScale();
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    if (pipeline->IsFollowSystem() && (!NearZero(maxAppFontScale))) {
        fontScale = std::min(fontScale, maxAppFontScale);
    }
    Dimension fontSizeValueResult = fontSizeValue;
    if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontScale, fontSizeLimit.ConvertToPx())) {
        if (!NearZero(fontScale)) {
            fontSizeValueResult = fontSizeLimit / fontScale;
        }
    }
    return fontSizeValueResult;
}

const Dimension DatePickerDialogView::ConvertTitleFontScaleValue(const Dimension& fontSizeValue)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);
    auto fontScale = pipeline->GetFontScale();
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    if (pipeline->IsFollowSystem() && (!NearZero(maxAppFontScale))) {
        fontScale = std::min(fontScale, maxAppFontScale);
    }
    if (NearZero(fontScale)) {
        return fontSizeValue;
    }
    if (NeedAdaptForAging()) {
        if (fontSizeValue.Unit() == DimensionUnit::VP) {
            return (fontSizeValue * pickerTheme->GetTitleFontScaleLimit());
        } else {
            if (GreatOrEqualCustomPrecision(fontScale, pickerTheme->GetTitleFontScaleLimit()) &&
             (fontScale != 0.0f)) {
                auto fontSizeScale = pickerTheme->GetTitleFontScaleLimit() / fontScale;
                return (fontSizeValue * fontSizeScale);
            }
        }
    } else {
        if (GreatOrEqualCustomPrecision(fontScale, pickerTheme->GetMaxOneFontScale()) &&
            fontSizeValue.Unit() != DimensionUnit::VP && (fontScale != 0.0f)) {
            return (fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

void DatePickerDialogView::GetUserSettingLimit()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    selectedTextStyleFont_ = pickerTheme->GetUseSetSelectedTextStyle();
    normalTextStyleFont_ = pickerTheme->GetUserSetNormalTextStyle();
    disappearTextStyleFont_ = pickerTheme->GetUserSetDisappearTextStyle();
}

DialogEvent DatePickerDialogView::GetDateChangeEvent(const RefPtr<FrameNode>& frameNode,
    const std::map<std::string, NG::DialogEvent>& dialogEvent)
{
    auto dateChangeIter = dialogEvent.find("dateChangeId");
    DialogEvent dateChangeEvent = dateChangeIter == dialogEvent.end() ? nullptr : dateChangeIter->second;
    dateChangeEvent = [weak = WeakPtr<FrameNode>(frameNode), dateChangeEvent](const std::string& info) -> void {
        auto uiNode = weak.Upgrade();
        if (uiNode != nullptr) {
            DatePickerPattern::ReportDateChangeEvent(uiNode->GetId(), "DatePickerDialog", "onDateChange", info);
        }
        CHECK_NULL_VOID(dateChangeEvent);
        dateChangeEvent(info);
    };
    return dateChangeEvent;
}

std::string DatePickerDialogView::GetDialogAgingButtonText(bool isNext)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, "");
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, "");
    auto buttonText = isNext ? pickerTheme->GetNextText() : pickerTheme->GetPrevText();
    return buttonText;
}

std::string DatePickerDialogView::GetDialogNormalButtonText(bool isConfirm)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, "");
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, "");
    auto buttonText = isConfirm ? dialogTheme->GetConfirmText() : dialogTheme->GetCancelText();
    return buttonText;
}
} // namespace OHOS::Ace::NG

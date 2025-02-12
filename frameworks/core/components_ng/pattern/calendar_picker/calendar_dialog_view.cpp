/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"

#include <utility>

#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SWIPER_MONTHS_COUNT = 3;
constexpr int32_t CURRENT_MONTH_INDEX = 1;
constexpr int32_t DAYS_OF_WEEK = 7;
constexpr Dimension DIALOG_WIDTH = 336.0_vp;
constexpr Dimension CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT = 4.0_vp;
constexpr float WEEK_SPACE = 20.0f;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
constexpr size_t CANCEL_BUTTON_INDEX = 1;
constexpr size_t CANCEL_BUTTON_FONT_COLOR_INDEX = 0;
constexpr size_t CANCEL_BUTTON_BACKGROUND_COLOR_INDEX = 1;
constexpr size_t ACCEPT_BUTTON_FONT_COLOR_INDEX = 2;
constexpr size_t ACCEPT_BUTTON_BACKGROUND_COLOR_INDEX = 3;
} // namespace

DeviceOrientation CalendarDialogView::previousOrientation_ { DeviceOrientation::PORTRAIT };

RefPtr<FrameNode> CalendarDialogView::Show(const DialogProperties& dialogProperties,
    const CalendarSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CalendarDialogPattern>());
    OperationsToPattern(contentColumn, settingData, dialogProperties, buttonInfos);
    auto layoutProperty = contentColumn->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto textDirection = layoutProperty->GetLayoutDirection();
    if (settingData.entryNode.Upgrade() != nullptr) {
        auto entryNode = settingData.entryNode.Upgrade();
        textDirection = entryNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
        layoutProperty->UpdateLayoutDirection(textDirection);
    }

    auto calendarNode = CreateCalendarNode(contentColumn, settingData, dialogEvent);
    CHECK_NULL_RETURN(calendarNode, nullptr);
    auto calendarLayoutProperty = calendarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(calendarLayoutProperty, nullptr);
    calendarLayoutProperty->UpdateLayoutDirection(textDirection);

    auto weekFrameNode = CreateWeekNode(calendarNode);
    CHECK_NULL_RETURN(weekFrameNode, nullptr);

    auto titleNode = CreateTitleNode(calendarNode, contentColumn);
    CHECK_NULL_RETURN(titleNode, nullptr);
    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_RETURN(titleLayoutProperty, nullptr);
    titleLayoutProperty->UpdateLayoutDirection(textDirection);

    auto scrollFrameNode = CreateScrollNode();
    CHECK_NULL_RETURN(weekFrameNode, nullptr);

    calendarNode->MountToParent(scrollFrameNode);
    titleNode->MountToParent(contentColumn);
    weekFrameNode->MountToParent(contentColumn);
    scrollFrameNode->MountToParent(contentColumn);

    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogLayoutProperty = dialogNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dialogLayoutProperty, nullptr);
    auto calendarTextDirection = calendarLayoutProperty->GetNonAutoLayoutDirection();
    auto dialogTextDirection = dialogLayoutProperty->GetNonAutoLayoutDirection();
    SetWeekTextDirection(dialogTextDirection, calendarTextDirection, weekFrameNode);
    dialogLayoutProperty->UpdateLayoutDirection(textDirection);
    CreateChildNode(contentColumn, dialogNode, dialogProperties);
    if (!settingData.entryNode.Upgrade()) {
        auto contentRow =
            CreateOptionsNode(dialogNode, calendarNode, dialogEvent, std::move(dialogCancelEvent), buttonInfos);
        contentRow->MountToParent(contentColumn);
        UpdateDialogDefaultFocus(contentRow, contentColumn);
    }

    contentColumn->MarkModifyDone();
    calendarNode->MarkModifyDone();
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

void CalendarDialogView::SetWeekTextDirection(const TextDirection& dialogDirection,
    const TextDirection& calendarDirection, const RefPtr<FrameNode>& weekNode)
{
    std::vector<std::string> weekNumbers = Localization::GetInstance()->GetWeekdays(true);
    for (int32_t column = 0; column < DAYS_OF_WEEK; column++) {
        auto textWeekNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textWeekNode);
        int32_t weekId = 0;
        if (calendarDirection == TextDirection::RTL
            && dialogDirection != TextDirection::RTL) {
            weekId = (DAYS_OF_WEEK - 1) - (column % DAYS_OF_WEEK);
        } else {
            weekId = column % DAYS_OF_WEEK;
        }
        if (weekId < 0) {
            continue;
        }
        std::string weekContent { weekNumbers[weekId] };
        auto textLayoutProperty = textWeekNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(weekContent);
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        textWeekNode->MountToParent(weekNode);
    }
}

void CalendarDialogView::CreateChildNode(const RefPtr<FrameNode>& contentColumn,
    const RefPtr<FrameNode>& dialogNode, const DialogProperties& dialogProperties)
{
    auto layoutProperty = contentColumn->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = dialogNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    RefPtr<DialogTheme> dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    PaddingProperty padding;
    padding.top = CalcLength(theme->GetCalendarTitleRowTopPadding());
    padding.bottom = CalcLength(theme->GetCalendarTitleRowTopPadding() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT);
    layoutProperty->UpdatePadding(padding);
    auto childNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto renderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (dialogProperties.customStyle) {
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(DIALOG_WIDTH), std::nullopt));
        BorderRadiusProperty radius;
        radius.SetRadius(theme->GetDialogBorderRadius());
        renderContext->UpdateBorderRadius(radius);
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (shadowTheme) {
            auto colorMode = SystemProperties::GetColorMode();
            renderContext->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultSM, colorMode));
        }
    }
    UpdateBackgroundStyle(renderContext, dialogProperties, theme, childNode);
}

void CalendarDialogView::OperationsToPattern(
    const RefPtr<FrameNode>& frameNode, const CalendarSettingData& settingData,
    const DialogProperties& dialogProperties, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pattern = frameNode->GetPattern<CalendarDialogPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEntryNode(settingData.entryNode);
    pattern->SetDialogOffset(OffsetF(dialogProperties.offset.GetX().Value(), dialogProperties.offset.GetY().Value()));
    pattern->SetCurrentButtonInfo(buttonInfos);
    pattern->SetCurrentSettingData(settingData);
    SetPreviousOrientation();
    pattern->InitSurfaceChangedCallback();
    DisableResetOptionButtonColor(pattern, buttonInfos);
}

void CalendarDialogView::DisableResetOptionButtonColor(
    const RefPtr<CalendarDialogPattern>& calendarDialogPattern, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_VOID(calendarDialogPattern);
    size_t fontColorIndex = 0;
    size_t backgoundColorIndex = 0;
    for (size_t index = 0; index < buttonInfos.size(); index++) {
        if (index == 0) {
            fontColorIndex = ACCEPT_BUTTON_FONT_COLOR_INDEX;
            backgoundColorIndex = ACCEPT_BUTTON_BACKGROUND_COLOR_INDEX;
        } else {
            fontColorIndex = CANCEL_BUTTON_FONT_COLOR_INDEX;
            backgoundColorIndex = CANCEL_BUTTON_BACKGROUND_COLOR_INDEX;
        }

        if (buttonInfos[index].role.has_value() || buttonInfos[index].buttonStyle.has_value() ||
            buttonInfos[index].fontColor.has_value()) {
            calendarDialogPattern->SetOptionsButtonUpdateColorFlags(fontColorIndex, false);
        }

        if (buttonInfos[index].role.has_value() || buttonInfos[index].buttonStyle.has_value() ||
            buttonInfos[index].backgroundColor.has_value()) {
            calendarDialogPattern->SetOptionsButtonUpdateColorFlags(backgoundColorIndex, false);
        }
    }
}

void CalendarDialogView::SetTitleIdealSize(
    const RefPtr<CalendarTheme>& theme, const RefPtr<LinearLayoutProperty>& layoutProps)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto fontSizeScale = pipeline->GetFontScale();
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme->GetCalendarTitleRowHeight())));
    } else if (fontSizeScale >= theme->GetCalendarPickerLargerScale()) {
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(std::nullopt, CalcLength(theme->GetCalendarTitleLargerRowHeight())));
    } else {
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(std::nullopt, CalcLength(theme->GetCalendarTitleLargeRowHeight())));
    }
}

void AddButtonAccessAbility(RefPtr<FrameNode>& leftYearArrowNode, RefPtr<FrameNode>& leftDayArrowNode,
    RefPtr<FrameNode>& rightDayArrowNode, RefPtr<FrameNode>& rightYearArrowNode, RefPtr<CalendarTheme> theme)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(leftYearArrowNode);
    auto leftYearProperty = leftYearArrowNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(leftYearProperty);
    leftYearProperty->SetAccessibilityText(theme->GetCalendarTheme().preYear);
    CHECK_NULL_VOID(leftDayArrowNode);
    auto leftDayProperty = leftDayArrowNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(leftDayProperty);
    leftDayProperty->SetAccessibilityText(theme->GetCalendarTheme().preMonth);
    CHECK_NULL_VOID(rightDayArrowNode);
    auto rightDayProperty = rightDayArrowNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(rightDayProperty);
    rightDayProperty->SetAccessibilityText(theme->GetCalendarTheme().nextMonth);
    CHECK_NULL_VOID(rightYearArrowNode);
    auto rightYearProperty = rightYearArrowNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(rightYearProperty);
    rightYearProperty->SetAccessibilityText(theme->GetCalendarTheme().nextYear);
}

RefPtr<FrameNode> CalendarDialogView::CreateTitleNode(const RefPtr<FrameNode>& calendarNode,
    const RefPtr<FrameNode>& calendarDialogNode)
{
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleRow, nullptr);
    auto layoutProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    auto pipelineContext = calendarNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::AUTO);
    layoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    MarginProperty margin;
    margin.left = CalcLength(theme->GetCalendarTitleRowLeftRightPadding());
    margin.right = CalcLength(theme->GetCalendarTitleRowLeftRightPadding());
    layoutProps->UpdateMargin(margin);
    SetTitleIdealSize(theme, layoutProps);

    // left year arrow
    auto leftYearArrowNode =
        CreateTitleImageNode(calendarNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG);
    leftYearArrowNode->MountToParent(titleRow);

    // left day arrow
    auto leftDayArrowNode = CreateTitleImageNode(calendarNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
    leftDayArrowNode->MountToParent(titleRow);

    // text
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_RETURN(calendarPattern, nullptr);
    auto textTitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, calendarPattern->GetTitleId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textTitleNode, nullptr);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    UpdateTextLayoutProperty(textLayoutProperty, theme);
    textTitleNode->MarkModifyDone();
    textTitleNode->MountToParent(titleRow);

    // right day arrow
    auto rightDayArrowNode =
        CreateTitleImageNode(calendarNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
    rightDayArrowNode->MountToParent(titleRow);

    // right year arrow
    auto rightYearArrowNode =
        CreateTitleImageNode(calendarNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG);
    rightYearArrowNode->MountToParent(titleRow);
    AddButtonAccessAbility(leftYearArrowNode, leftDayArrowNode, rightDayArrowNode, rightYearArrowNode, theme);

    auto pattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetTitleNode(textTitleNode);
    return titleRow;
}

RefPtr<FrameNode> CalendarDialogView::CreateWeekNode(const RefPtr<FrameNode>& calendarNode)
{
    auto weekFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(weekFrameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto weekLayoutProperty = weekFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(weekLayoutProperty, nullptr);
    auto swiperNode = calendarNode->GetChildren().front();
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto monthFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    CHECK_NULL_RETURN(monthFrameNode, nullptr);
    auto calendarPaintProperty = monthFrameNode->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_RETURN(calendarPaintProperty, nullptr);
    MarginProperty margin;
    margin.top = CalcLength(theme->GetDistanceBetweenTitleAndDate().ConvertToPx() + WEEK_SPACE);
    weekLayoutProperty->UpdateMargin(margin);
    return weekFrameNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateTitleImageNode(
    const RefPtr<FrameNode>& calendarNode, const InternalResource::ResourceId& resourceId)
{
    auto pipelineContext = calendarNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    CalcSize idealSize = { CalcLength(theme->GetEntryArrowWidth()), CalcLength(theme->GetEntryArrowWidth()) };
    MeasureProperty layoutConstraint = { .selfIdealSize = idealSize };
    BorderRadiusProperty borderRadius;
    Dimension radius =
        Dimension((theme->GetCalendarImageWidthHeight().Value()) / 2, (theme->GetCalendarImageWidthHeight()).Unit());
    borderRadius.SetRadius(radius);

    // Create button node
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetCalendarImageWidthHeight()), CalcLength(theme->GetCalendarImageWidthHeight())));
    auto buttonRenderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(buttonRenderContext, nullptr);
    buttonRenderContext->UpdateBorderRadius(borderRadius);
    MarginProperty margin;
    if (resourceId == InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG) {
        margin.right = CalcLength(theme->GetCalendarTitleImagePadding());
    } else if (resourceId == InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG) {
        margin.left = CalcLength(theme->GetCalendarTitleImagePadding());
    }
    buttonLayoutProperty->UpdateMargin(margin);

    // Create image node
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto imageRenderContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageRenderContext, nullptr);
    imageRenderContext->UpdateBorderRadius(borderRadius);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(resourceId, theme->GetEntryArrowColor());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
    imageNode->SetDraggable(false);
    imageNode->MarkModifyDone();
    imageNode->MountToParent(buttonNode);

    buttonNode->MarkModifyDone();
    return buttonNode;
}

void CalendarDialogView::SetCalendarIdealSize(const RefPtr<CalendarTheme>& theme,
    const RefPtr<LayoutProperty>& calendarLayoutProperty, const Dimension& weekHeight)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto fontSizeScale = pipeline->GetFontScale();
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        calendarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
            CalcLength(theme->GetCalendarContainerHeight() + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT - weekHeight)));
    } else if (fontSizeScale >= theme->GetCalendarPickerLargerScale()) {
        calendarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
            CalcLength(theme->GetCalendarLargerContainerHeight()
            + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT - weekHeight)));
    } else {
        calendarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
            CalcLength(theme->GetCalendarLargeContainerHeight()
            + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT - weekHeight)));
    }
}

RefPtr<FrameNode> CalendarDialogView::CreateCalendarNode(const RefPtr<FrameNode>& calendarDialogNode,
    const CalendarSettingData& settingData, const std::map<std::string, NG::DialogEvent>& dialogEvent)
{
    int32_t calendarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto calendarNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, calendarNodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    CHECK_NULL_RETURN(calendarNode, nullptr);

    auto textDirection = calendarNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (settingData.entryNode.Upgrade() != nullptr) {
        auto entryNode = settingData.entryNode.Upgrade();
        textDirection = entryNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    }

    auto swiperNode = CreateCalendarSwiperNode();
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateLayoutDirection(textDirection);
    swiperNode->MountToParent(calendarNode);

    InitOnRequestDataEvent(calendarDialogNode, calendarNode);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_RETURN(calendarPattern, nullptr);
    PickerDate date = settingData.selectedDate;
    calendarPattern->SetSelectedDay(date);
    CalendarMonth currentMonth { .year = date.GetYear(), .month = date.GetMonth() };
    UpdateCalendarMonthData(calendarDialogNode, calendarNode, currentMonth);
    calendarPattern->SetStartDate(settingData.startDate);
    calendarPattern->SetEndDate(settingData.endDate);
    calendarPattern->SetMarkToday(settingData.markToday);
    calendarPattern->SetDisabledDateRange(settingData.disabledDateRange);

    CalendarDay calendarDay;
    PickerDate today = PickerDate::Current();
    calendarDay.month.year = static_cast<int32_t>(today.GetYear());
    calendarDay.month.month = static_cast<int32_t>(today.GetMonth());
    calendarDay.day = static_cast<int32_t>(today.GetDay());
    calendarPattern->SetCalendarDay(calendarDay);

    DialogEvent changeEvent = GetChangeEvent(settingData, calendarDialogNode, dialogEvent); // do not check nullptr
    for (int32_t i = 0; i < SWIPER_MONTHS_COUNT; i++) {
        auto monthFrameNode = CreateCalendarMonthNode(calendarNodeId, settingData, changeEvent);
        auto monthLayoutProperty = monthFrameNode->GetLayoutProperty();
        CHECK_NULL_RETURN(monthLayoutProperty, nullptr);
        if (i == CURRENT_MONTH_INDEX) {
            auto currentPattern = monthFrameNode->GetPattern<CalendarMonthPattern>();
            CHECK_NULL_RETURN(currentPattern, nullptr);
            currentPattern->SetIsFirstEnter(true);
        }
        monthLayoutProperty->UpdateLayoutDirection(textDirection);
        monthFrameNode->MountToParent(swiperNode);
        monthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    InitCalendarProperty(calendarNode);
    swiperNode->MarkModifyDone();
    return calendarNode;
}

void CalendarDialogView::InitCalendarProperty(const RefPtr<FrameNode>& calendarNode)
{
    auto pipelineContext = calendarNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto calendarLayoutProperty = calendarNode->GetLayoutProperty();
    CHECK_NULL_VOID(calendarLayoutProperty);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    MarginProperty margin = {
        .left = CalcLength(theme->GetDistanceBetweenContainterAndDate() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT),
        .right = CalcLength(theme->GetDistanceBetweenContainterAndDate() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT)
    };
    calendarLayoutProperty->UpdateMargin(margin);
    auto swiperNode = calendarNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto calendarMonthNode = swiperNode->GetChildAtIndex(CURRENT_MONTH_INDEX);
    CHECK_NULL_VOID(calendarMonthNode);
    auto calendarMonthFrameNode = AceType::DynamicCast<FrameNode>(calendarMonthNode);
    CHECK_NULL_VOID(calendarMonthFrameNode);
    auto calendarPaintProperty = calendarMonthFrameNode->GetPaintProperty<CalendarPaintProperty>();
    auto gregorianDayHeight = calendarPaintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                    ? theme->GetCalendarTheme().gregorianCalendarHeight
                    : calendarPaintProperty->GetGregorianCalendarHeightValue({});
    auto monthPattern = calendarMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(monthPattern);
    if (monthPattern->IsLargeSize(theme)) {
        gregorianDayHeight = monthPattern->GetDaySize(theme);
    }
    SetCalendarIdealSize(theme, calendarLayoutProperty, gregorianDayHeight);
}

RefPtr<FrameNode> CalendarDialogView::CreateScrollNode()
{
    auto scrollNode = FrameNode::GetOrCreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    CHECK_NULL_RETURN(scrollNode, nullptr);
    auto props = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateScrollEnabled(true);
    props->UpdateAxis(Axis::VERTICAL);
    props->UpdateAlignment(Alignment::TOP_CENTER);
    scrollNode->MarkModifyDone();
    return scrollNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateCalendarSwiperNode()
{
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_MONTH_INDEX);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    swiperLayoutProperty->UpdateLoop(true);
    swiperLayoutProperty->UpdateDisableSwipe(false);
    return swiperNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateCalendarMonthNode(int32_t calendarNodeId,
    const CalendarSettingData& settingData, const DialogEvent& changeEvent)
{
    auto monthFrameNode = FrameNode::GetOrCreateFrameNode(V2::CALENDAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    CHECK_NULL_RETURN(monthFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(monthFrameNode);
    SetCalendarPaintProperties(settingData);
    ViewStackProcessor::GetInstance()->Finish();
    auto monthPattern = monthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_RETURN(monthPattern, nullptr);
    monthPattern->SetCalendarDialogFlag(true);
    auto calendarEventHub = monthPattern->GetEventHub<CalendarEventHub>();
    CHECK_NULL_RETURN(calendarEventHub, nullptr);
    auto selectedChangeEvent = [calendarNodeId, changeEvent, settingData](const std::string& callbackInfo) {
        OnSelectedChangeEvent(calendarNodeId, callbackInfo, std::move(changeEvent), settingData);
    };
    calendarEventHub->SetSelectedChangeEvent(std::move(selectedChangeEvent));

    auto monthLayoutProperty = monthFrameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(monthLayoutProperty, nullptr);
    auto pipelineContext = monthFrameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    monthLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1, DimensionUnit::PERCENT),
        CalcLength(theme->GetCalendarContainerHeight() + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT)));
    return monthFrameNode;
}

void CalendarDialogView::UpdateCalendarMonthData(const RefPtr<FrameNode>& calendarDialogNode,
    const RefPtr<FrameNode>& calendarNode, const CalendarMonth& currentMonth)
{
    CHECK_NULL_VOID(calendarNode);
    CHECK_NULL_VOID(calendarDialogNode);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    auto calendarDialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    CHECK_NULL_VOID(calendarDialogPattern);

    CalendarData calendarData;
    calendarDialogPattern->GetCalendarMonthData(currentMonth.year, currentMonth.month, calendarData.currentData);
    calendarPattern->SetCurrentMonthData(calendarData.currentData);
    calendarDialogPattern->GetCalendarMonthData(calendarDialogPattern->GetLastMonth(currentMonth).year,
        calendarDialogPattern->GetLastMonth(currentMonth).month, calendarData.preData);
    calendarPattern->SetPreMonthData(calendarData.preData);
    calendarDialogPattern->GetCalendarMonthData(calendarDialogPattern->GetNextMonth(currentMonth).year,
        calendarDialogPattern->GetNextMonth(currentMonth).month, calendarData.nextData);
    calendarPattern->SetNextMonthData(calendarData.nextData);
}

void CalendarDialogView::SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogChange(std::move(onChange));
}

void CalendarDialogView::SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onAccept)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogAcceptEvent(std::move(onAccept));
}

RefPtr<FrameNode> CalendarDialogView::CreateButtonNode(bool isConfirm, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(calendarTheme, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(
        Localization::GetInstance()->GetEntryLetters(isConfirm ? "common.ok" : "common.cancel"));

    auto fontSizeScale = pipeline->GetFontScale();
    auto fontSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    if (fontSizeScale < calendarTheme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        textLayoutProperty->UpdateFontSize(fontSize);
    } else {
        fontSizeScale = fontSizeScale > calendarTheme->GetCalendarPickerLargeScale()
                            ? calendarTheme->GetCalendarPickerLargeScale()
                            : fontSizeScale;
        textLayoutProperty->UpdateFontSize(fontSize * fontSizeScale);
    }

    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    textNode->MountToParent(buttonNode);

    UpdateButtonLayoutProperty(buttonNode, isConfirm, buttonInfos, pipeline);
    auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->SetStateEffect(true);

    auto buttonRenderContext = buttonNode->GetRenderContext();
    auto defaultBGColor =
        calendarTheme->GetIsButtonTransparent() ? Color::TRANSPARENT : calendarTheme->GetDialogButtonBackgroundColor();
    buttonRenderContext->UpdateBackgroundColor(defaultBGColor);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    auto index = isConfirm ? ACCEPT_BUTTON_INDEX : CANCEL_BUTTON_INDEX;
    UpdateButtonStyles(buttonInfos, index, buttonLayoutProperty, buttonRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonNode, isConfirm);
    buttonNode->MarkModifyDone();
    return buttonNode;
}

void CalendarDialogView::UpdateButtonLayoutProperty(const RefPtr<FrameNode>& buttonNode, bool isConfirm,
    const std::vector<ButtonInfo>& buttonInfos, const RefPtr<PipelineContext>& pipeline)
{
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto calendarTheme = pipeline->GetTheme<CalendarTheme>();
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto index = isConfirm ? ACCEPT_BUTTON_INDEX : CANCEL_BUTTON_INDEX;
    if (index < buttonInfos.size() &&
        (buttonInfos[index].role.has_value() || buttonInfos[index].buttonStyle.has_value() ||
            buttonInfos[index].fontSize.has_value() || buttonInfos[index].fontColor.has_value() ||
            buttonInfos[index].fontWeight.has_value() || buttonInfos[index].fontStyle.has_value() ||
            buttonInfos[index].fontFamily.has_value())) {
        buttonLayoutProperty->UpdateLabel(
            Localization::GetInstance()->GetEntryLetters(isConfirm ? "common.ok" : "common.cancel"));
    }
    buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        buttonLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }

    buttonLayoutProperty->UpdateFlexShrink(1.0);
    CalcLength width;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        width = CalcLength(1.0, DimensionUnit::PERCENT);
    } else {
        width = CalcLength(pickerTheme->GetButtonWidth());
    }

    auto fontSizeScale = pipeline->GetFontScale();
    if (fontSizeScale >= calendarTheme->GetCalendarPickerLargerScale() &&
        (!(GetPreviousOrientation() == SystemProperties::GetDeviceOrientation())
                ? Dimension(pipeline->GetRootWidth()).ConvertToVp() >= deviceHeightLimit
                : Dimension(pipeline->GetRootHeight()).ConvertToVp() >= deviceHeightLimit)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(width, CalcLength(calendarTheme->GetCalendarActionLargeRowHeight())));
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(width, CalcLength(calendarTheme->GetCalendarActionRowHeight())));
    }
}

void CalendarDialogView::UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].type.has_value()) {
        buttonLayoutProperty->UpdateType(buttonInfos[index].type.value());
    }
    UpdateButtonStyleAndRole(buttonInfos, index, buttonLayoutProperty, buttonRenderContext, buttonTheme);
    if (buttonInfos[index].fontSize.has_value()) {
        buttonLayoutProperty->UpdateFontSize(buttonInfos[index].fontSize.value());
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

void CalendarDialogView::UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
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

RefPtr<FrameNode> CalendarDialogView::CreateConfirmNode(
    const RefPtr<FrameNode>& calendarNode, DialogEvent& acceptEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_RETURN(calendarNode, nullptr);
    auto buttonConfirmNode = CreateButtonNode(true, buttonInfos);

    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    SetDialogAcceptEvent(calendarNode, std::move(acceptEvent));
    auto clickCallback = [weak = WeakPtr<FrameNode>(calendarNode)](const GestureEvent& /* info */) {
        auto calendarNode = weak.Upgrade();
        CHECK_NULL_VOID(calendarNode);
        auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
        CHECK_NULL_VOID(calendarPattern);
        auto str = calendarPattern->GetSelectDate();
        auto calendarEventHub = calendarNode->GetEventHub<CalendarEventHub>();
        CHECK_NULL_VOID(calendarEventHub);
        calendarEventHub->FireDialogAcceptEvent(str);
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(clickCallback)));

    return buttonConfirmNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateCancelNode(
    const NG::DialogGestureEvent& cancelEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    auto buttonCancelNode = CreateButtonNode(false, buttonInfos);

    auto eventCancelHub = buttonCancelNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventCancelHub, nullptr);
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));

    return buttonCancelNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateDividerNode()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    RefPtr<CalendarTheme> theme = pipeline->GetTheme<CalendarTheme>();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_RETURN(dividerRenderContext, nullptr);
    dividerRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerLayoutProperty, nullptr);
    dividerLayoutProperty->UpdateVertical(true);
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerRenderProperty, nullptr);
    dividerRenderProperty->UpdateDividerColor(
        theme->GetIsDividerTransparent() ? Color::TRANSPARENT : theme->GetDialogDividerColor());

    dividerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(theme->GetEntryArrowWidth())));

    dividerNode->MarkModifyDone();

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto dividerWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(dividerWrapper, nullptr);
        auto layoutProps = dividerWrapper->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        layoutProps->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(dialogTheme->GetActionsPadding().Bottom()), CalcLength(theme->GetCalendarActionRowHeight())));
        dividerNode->MountToParent(dividerWrapper);
        return dividerWrapper;
    }
    return dividerNode;
}

RefPtr<FrameNode> CalendarDialogView::CreateOptionsNode(
    const RefPtr<FrameNode>& dialogNode, const RefPtr<FrameNode>& dateNode,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto pipelineContext = contentRow->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    UpdateOptionLayoutProps(contentRow, pipelineContext);

    auto cancelIter = dialogCancelEvent.find("cancelId");
    DialogGestureEvent cancelEvent = nullptr;
    if (cancelIter != dialogCancelEvent.end()) {
        cancelEvent = cancelIter->second;
    }
    auto buttonCancelNode = CreateCancelNode(cancelEvent, buttonInfos);
    auto acceptIter = dialogEvent.find("acceptId");
    DialogEvent acceptEvent = (acceptIter != dialogEvent.end()) ? acceptIter->second : nullptr;
    auto buttonConfirmNode = CreateConfirmNode(dateNode, acceptEvent, buttonInfos);

    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);
    UpdateDefaultFocusByButtonInfo(contentRow, buttonConfirmNode, buttonCancelNode);

    auto event = [weakDialogNode = WeakPtr<FrameNode>(dialogNode),
                 weakPipelineContext = WeakPtr<PipelineContext>(pipelineContext)](const GestureEvent& /* info */) {
        auto dialogNode = weakDialogNode.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto pipelineContext = weakPipelineContext.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        auto overlayManager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->CloseDialog(dialogNode);
    };
    for (const auto& child : contentRow->GetChildren()) {
        auto firstChild = AceType::DynamicCast<FrameNode>(child);
        auto gesturHub = firstChild->GetOrCreateGestureEventHub();
        auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(event);
        gesturHub->AddClickEvent(onClick);
    }
    contentRow->AddChild(CreateDividerNode(), 1);
    return contentRow;
}

void CalendarDialogView::UpdateOptionLayoutProps(
    const RefPtr<FrameNode>& contentRow, const RefPtr<PipelineContext>& pipelineContext)
{
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.top = CalcLength(theme->GetCalendarActionRowTopPadding() - CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT);
    } else {
        margin.top = CalcLength(theme->GetCalendarActionRowTopPadding() + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT);
    }
    margin.left = CalcLength(theme->GetCalendarActionRowBottomLeftRightPadding());
    margin.right = CalcLength(theme->GetCalendarActionRowBottomLeftRightPadding());
    margin.bottom = CalcLength(theme->GetCalendarTitleRowTopPadding() + CALENDAR_DISTANCE_ADJUST_FOCUSED_EVENT);
    layoutProps->UpdateMargin(margin);
    layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme->GetCalendarActionRowHeight())));
}

void CalendarDialogView::SetCalendarPaintProperties(const CalendarSettingData& settingData)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto fontSizeScale = pipelineContext->GetFontScale();
    Dimension defaultDayRadius;
    auto fontSize = theme->GetCalendarDayFontSize();
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayHeight, theme->GetCalendarPickerDayWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayWidth, theme->GetCalendarPickerDayWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayFontSize, fontSize);
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekHeight, theme->GetCalendarPickerDayWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekWidth, theme->GetCalendarPickerDayWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, fontSize);
        defaultDayRadius = theme->GetCalendarDayRadius();
    } else {
        fontSizeScale = fontSizeScale > theme->GetCalendarPickerLargerScale() ? theme->GetCalendarPickerLargerScale()
                                                                              : fontSizeScale;
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayHeight, theme->GetCalendarPickerDayLargeWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayWidth, theme->GetCalendarPickerDayLargeWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayFontSize, fontSize * fontSizeScale);
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekHeight, theme->GetCalendarPickerDayLargeWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekWidth, theme->GetCalendarPickerDayLargeWidthOrHeight());
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, fontSize * fontSizeScale);
        defaultDayRadius = theme->GetCalendarPickerDayLargeWidthOrHeight() / 2;
    }

    if (AceApplicationInfo::GetInstance().GetLanguage() != "zh") {
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, theme->GetCalendarSmallDayFontSize());
    }

    if (settingData.dayRadius.has_value() && NonNegative(settingData.dayRadius.value().ConvertToPx()) &&
        LessOrEqual(settingData.dayRadius.value().ConvertToPx(), defaultDayRadius.ConvertToPx())) {
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayRadius, settingData.dayRadius.value());
    } else {
        ACE_UPDATE_PAINT_PROPERTY(CalendarPaintProperty, DayRadius, defaultDayRadius);
    }
}

void CalendarDialogView::InitOnRequestDataEvent(
    const RefPtr<FrameNode>& calendarDialogNode, const RefPtr<FrameNode>& calendarNode)
{
    auto callback = [calendarDialogNodeWeak = WeakPtr<FrameNode>(calendarDialogNode),
                    calendarNodeWeak = WeakPtr<FrameNode>(calendarNode)](const std::string& info) {
        auto calendarNode = calendarNodeWeak.Upgrade();
        CHECK_NULL_VOID(calendarNode);
        auto calendarDialogNode = calendarDialogNodeWeak.Upgrade();
        CHECK_NULL_VOID(calendarDialogNode);
        auto jsonInfo = JsonUtil::ParseJsonString(info);
        CalendarMonth currentMonth { .year = jsonInfo->GetInt("year"), .month = jsonInfo->GetInt("month") };
        UpdateCalendarMonthData(calendarDialogNode, calendarNode, currentMonth);

        calendarNode->MarkModifyDone();
        calendarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    };
    auto eventHub = calendarNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestDataEvent(std::move(callback));
}

void CalendarDialogView::OnSelectedChangeEvent(int32_t calendarNodeId, const std::string& callbackInfo,
    const DialogEvent& onChange, const CalendarSettingData& settingData)
{
    auto calendarNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, calendarNodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    CHECK_NULL_VOID(calendarNode);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    auto currentMonthData = calendarPattern->GetCurrentMonthData();
    auto jsonInfo = JsonUtil::ParseJsonString(callbackInfo);
    CalendarMonth selectedMonth { .year = jsonInfo->GetInt("year"), .month = jsonInfo->GetInt("month") };
    if (currentMonthData.year != selectedMonth.year || currentMonthData.month != selectedMonth.month) {
        return;
    }

    if (onChange) {
        onChange(callbackInfo);
    }
    PickerDate selectedDay(selectedMonth.year, selectedMonth.month, jsonInfo->GetInt("day"));
    calendarPattern->SetSelectedDay(selectedDay);
    calendarNode->MarkModifyDone();

    auto entryNode = settingData.entryNode.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto eventHub = entryNode->GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateOnChangeEvent(callbackInfo);
}

void CalendarDialogView::UpdateBackgroundStyle(const RefPtr<RenderContext>& renderContext,
    const DialogProperties& dialogProperties, const RefPtr<CalendarTheme>& calendarTheme,
    const RefPtr<FrameNode>& dialogNode)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && renderContext->IsUniRenderEnabled()) {
        CHECK_NULL_VOID(calendarTheme);
        auto contentRenderContext = dialogNode->GetRenderContext();
        CHECK_NULL_VOID(contentRenderContext);
        auto pipeLineContext = dialogNode->GetContext();
        CHECK_NULL_VOID(pipeLineContext);
        BlurStyleOption styleOption;
        if (dialogProperties.blurStyleOption.has_value()) {
            styleOption = dialogProperties.blurStyleOption.value();
            if (styleOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
                pipeLineContext->AddWindowFocusChangedCallback(dialogNode->GetId());
            } else {
                pipeLineContext->RemoveWindowFocusChangedCallback(dialogNode->GetId());
            }
        }
        styleOption.blurStyle = static_cast<BlurStyle>(
            dialogProperties.backgroundBlurStyle.value_or(calendarTheme->GetCalendarPickerDialogBlurStyle()));
        if (dialogProperties.blurStyleOption.has_value() && contentRenderContext->GetBackgroundEffect().has_value()) {
            contentRenderContext->UpdateBackgroundEffect(std::nullopt);
        }
        renderContext->UpdateBackBlurStyle(styleOption);
        if (dialogProperties.effectOption.has_value()) {
            if (dialogProperties.effectOption->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
                pipeLineContext->AddWindowFocusChangedCallback(dialogNode->GetId());
            } else {
                pipeLineContext->RemoveWindowFocusChangedCallback(dialogNode->GetId());
            }
            if (contentRenderContext->GetBackBlurStyle().has_value()) {
                contentRenderContext->UpdateBackBlurStyle(std::nullopt);
            }
            contentRenderContext->UpdateBackgroundEffect(dialogProperties.effectOption.value());
        }
        renderContext->UpdateBackgroundColor(dialogProperties.backgroundColor.value_or(Color::TRANSPARENT));
    }
}

void CalendarDialogView::UpdateButtonDefaultFocus(const std::vector<ButtonInfo>& buttonInfos,
    const RefPtr<FrameNode>& buttonNode, bool isConfirm)
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

void CalendarDialogView::UpdateDialogDefaultFocus(const RefPtr<FrameNode>& contentRow,
    const RefPtr<FrameNode>& contentColumn)
{
    auto contentRowFocusHub = contentRow->GetOrCreateFocusHub();
    CHECK_NULL_VOID(contentRowFocusHub);
    if (contentRowFocusHub->IsDefaultFocus()) {
        auto contentColumnFocusHub = contentColumn->GetOrCreateFocusHub();
        CHECK_NULL_VOID(contentColumnFocusHub);
        contentColumnFocusHub->SetIsDefaultFocus(true);
    }
}

void CalendarDialogView::UpdateDefaultFocusByButtonInfo(const RefPtr<FrameNode>& optionsNode,
    const RefPtr<FrameNode>& accept, const RefPtr<FrameNode>& cancel)
{
    auto acceptFocusHub = accept->GetOrCreateFocusHub();
    CHECK_NULL_VOID(acceptFocusHub);
    auto cancelFocusHub = cancel->GetOrCreateFocusHub();
    CHECK_NULL_VOID(cancelFocusHub);
    if (acceptFocusHub->IsDefaultFocus() || cancelFocusHub->IsDefaultFocus()) {
        auto optionsNodeFocusHub = optionsNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(optionsNodeFocusHub);
        optionsNodeFocusHub->SetIsDefaultFocus(true);
    }
}

void CalendarDialogView::UpdateIdealSize(const RefPtr<CalendarTheme>& calendarTheme,
    const RefPtr<LinearLayoutProperty>& layoutProps, const RefPtr<LayoutProperty>& calendarLayoutProperty,
    const RefPtr<FrameNode>& calendarNode)
{
    SetTitleIdealSize(calendarTheme, layoutProps);
    auto swiperNode = calendarNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto calendarMonthNode = swiperNode->GetChildAtIndex(CURRENT_MONTH_INDEX);
    CHECK_NULL_VOID(calendarMonthNode);
    auto calendarMonthFrameNode = AceType::DynamicCast<FrameNode>(calendarMonthNode);
    CHECK_NULL_VOID(calendarMonthFrameNode);
    auto calendarPaintProperty = calendarMonthFrameNode->GetPaintProperty<CalendarPaintProperty>();
    auto gregorianDayHeight = calendarPaintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                    ? calendarTheme->GetCalendarTheme().gregorianCalendarHeight
                    : calendarPaintProperty->GetGregorianCalendarHeightValue({});
    auto monthPattern = calendarMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(monthPattern);
    if (monthPattern->IsLargeSize(calendarTheme)) {
        gregorianDayHeight = monthPattern->GetDaySize(calendarTheme);
    }
    SetCalendarIdealSize(calendarTheme, calendarLayoutProperty, gregorianDayHeight);
}

void CalendarDialogView::UpdatePaintProperties(
    const RefPtr<FrameNode>& monthFrameNode, const CalendarSettingData& settingData)
{
    auto pipelineContext = monthFrameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto fontSizeScale = pipelineContext->GetFontScale();
    Dimension defaultDayRadius;
    auto fontSize = theme->GetCalendarDayFontSize();
    if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, DayHeight, theme->GetCalendarPickerDayWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, DayWidth, theme->GetCalendarPickerDayWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, DayFontSize, fontSize, monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, WeekHeight, theme->GetCalendarPickerDayWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, WeekWidth, theme->GetCalendarPickerDayWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, fontSize, monthFrameNode);
        defaultDayRadius = theme->GetCalendarDayRadius();
    } else {
        fontSizeScale = fontSizeScale > theme->GetCalendarPickerLargerScale() ? theme->GetCalendarPickerLargerScale()
                                                                              : fontSizeScale;
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, DayHeight, theme->GetCalendarPickerDayLargeWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, DayWidth, theme->GetCalendarPickerDayLargeWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, DayFontSize, fontSize * fontSizeScale, monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, WeekHeight, theme->GetCalendarPickerDayLargeWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, WeekWidth, theme->GetCalendarPickerDayLargeWidthOrHeight(), monthFrameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, fontSize * fontSizeScale, monthFrameNode);
        defaultDayRadius = theme->GetCalendarPickerDayLargeWidthOrHeight() / 2;
    }

    if (AceApplicationInfo::GetInstance().GetLanguage() != "zh") {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CalendarPaintProperty, WeekFontSize, theme->GetCalendarSmallDayFontSize(), monthFrameNode);
    }

    if (settingData.dayRadius.has_value() && NonNegative(settingData.dayRadius.value().ConvertToPx()) &&
        LessOrEqual(settingData.dayRadius.value().ConvertToPx(), defaultDayRadius.ConvertToPx())) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, DayRadius, settingData.dayRadius.value(), monthFrameNode);
    } else {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, DayRadius, defaultDayRadius, monthFrameNode);
    }
}

void CalendarDialogView::UpdateButtons(
    const RefPtr<FrameNode>& buttonNode, size_t buttonIndex, std::vector<ButtonInfo>& buttonInfos)
{
    auto pipelineContext = buttonNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    auto pickerTheme = pipelineContext->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto fontSizeScale = pipelineContext->GetFontScale();
    auto fontSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    if (fontSizeScale < calendarTheme->GetCalendarPickerLargeScale() || CheckOrientationChange()) {
        textLayoutProperty->UpdateFontSize(fontSize);
    } else {
        fontSizeScale = fontSizeScale > calendarTheme->GetCalendarPickerLargeScale()
                            ? calendarTheme->GetCalendarPickerLargeScale()
                            : fontSizeScale;
        textLayoutProperty->UpdateFontSize(fontSize * fontSizeScale);
    }

    CalendarDialogView::UpdateButtonLayoutProperty(buttonNode, buttonIndex, buttonInfos, pipelineContext);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    CalendarDialogView::UpdateButtonStyles(
        buttonInfos, buttonIndex, buttonLayoutProperty, buttonNode->GetRenderContext());
    buttonNode->MarkModifyDone();
}

DialogEvent CalendarDialogView::GetChangeEvent(const CalendarSettingData& settingData,
    const RefPtr<FrameNode>& frameNode, const std::map<std::string, NG::DialogEvent>& dialogEvent)
{
    auto changeIter = dialogEvent.find("changeId");
    DialogEvent changeEvent = changeIter == dialogEvent.end() ? nullptr : changeIter->second;
    CHECK_NULL_RETURN(!settingData.entryNode.Upgrade(), changeEvent);
    changeEvent = [weak = WeakPtr<FrameNode>(frameNode), changeEvent](const std::string& info) -> void {
        ReportChangeEvent(weak.Upgrade(), "CalendarPickerDialog", "onChange", info);
        CHECK_NULL_VOID(changeEvent);
        changeEvent(info);
    };
    return changeEvent;
}

bool CalendarDialogView::CanReportChangeEvent(PickerDate& pickerDate, const PickerDate& newPickerDate)
{
    auto year = newPickerDate.GetYear();
    auto month = newPickerDate.GetMonth();
    auto day = newPickerDate.GetDay();
    if ((pickerDate.GetYear() == year) && (pickerDate.GetMonth() == month) && (pickerDate.GetDay() == day)) {
        return false;
    }
    pickerDate.SetYear(year);
    pickerDate.SetMonth(month);
    pickerDate.SetDay(day);
    return true;
}

bool CalendarDialogView::GetReportChangeEventDate(PickerDate& pickerDate, const std::string& eventData)
{
    auto dataJson = JsonUtil::ParseJsonString(eventData);
    CHECK_NULL_RETURN(dataJson, false);
    pickerDate.SetYear(dataJson->GetUInt("year"));
    pickerDate.SetMonth(dataJson->GetUInt("month"));
    pickerDate.SetDay(dataJson->GetUInt("day"));
    return true;
}

bool CalendarDialogView::ReportChangeEvent(const RefPtr<FrameNode>& frameNode, const std::string& compName,
    const std::string& eventName, const std::string& eventData)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto wrapperNode = frameNode->GetParent();
    CHECK_NULL_RETURN(wrapperNode, false);
    auto dialogNode = wrapperNode->GetParent();
    CHECK_NULL_RETURN(dialogNode, false);
    auto pattern = frameNode->GetPattern<CalendarDialogPattern>();
    CHECK_NULL_RETURN(pattern, false);
    PickerDate pickerDate;
    CHECK_NULL_RETURN(GetReportChangeEventDate(pickerDate, eventData), false);
    CHECK_NULL_RETURN(pattern->CanReportChangeEvent(pickerDate), false);
    return ReportChangeEvent(dialogNode->GetId(), compName, eventName, pickerDate);
}

bool CalendarDialogView::ReportChangeEvent(int32_t nodeId, const std::string& compName,
    const std::string& eventName, const PickerDate& pickerDate)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    auto value = InspectorJsonUtil::Create();
    CHECK_NULL_RETURN(value, false);
    value->Put(compName.c_str(), eventName.c_str());
    value->Put("year", pickerDate.GetYear());
    value->Put("month", pickerDate.GetMonth());
    value->Put("day", pickerDate.GetDay());
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(nodeId, "event", value);
#endif
    return true;
}

void CalendarDialogView::UpdateTextLayoutProperty(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    RefPtr<CalendarTheme>& theme)
{
    textLayoutProperty->UpdateContent(u"");
    MarginProperty textMargin;
    textMargin.left = CalcLength(theme->GetCalendarTitleTextPadding());
    textMargin.right = CalcLength(theme->GetCalendarTitleTextPadding());
    textLayoutProperty->UpdateMargin(textMargin);
    textLayoutProperty->UpdateFontSize(theme->GetCalendarTitleFontSize());
    textLayoutProperty->UpdateTextColor(theme->GetCalendarTitleFontColor());
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateLayoutWeight(1);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
}
} // namespace OHOS::Ace::NG

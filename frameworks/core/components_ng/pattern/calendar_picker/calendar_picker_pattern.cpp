/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"

#include <algorithm>

#include "base/i18n/localization.h"
#include "base/utils/utf_helper.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t YEAR_INDEX = 0;
constexpr int32_t FIRST_SLASH = 1;
constexpr int32_t MONTH_INDEX = 2;
constexpr int32_t SECOND_SLASH = 3;
constexpr int32_t DAY_INDEX = 4;
constexpr int32_t YEAR_LENTH = 4;
constexpr int32_t ADD_BUTTON_INDEX = 0;
constexpr int32_t SUB_BUTTON_INDEX = 1;
constexpr int32_t DATE_NODE_COUNT = 3;
constexpr uint32_t MIN_YEAR = 1;
constexpr uint32_t MAX_YEAR = 5000;
constexpr uint32_t DELAY_TIME = 2000;
constexpr uint32_t MAX_MONTH = 12;
constexpr Dimension DIALOG_HEIGHT = 348.0_vp;
constexpr Dimension DIALOG_WIDTH = 336.0_vp;
constexpr double DISABLE_ALPHA = 0.4;
} // namespace
void CalendarPickerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitDateIndex();
    InitClickEvent();
    InitOnKeyEvent();
    InitOnHoverEvent();
    HandleEnable();
    FlushTextStyle();
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    UpdateEntryButtonColor();
    UpdateEntryButtonBorderWidth();
    UpdateAccessibilityText();
}

void CalendarPickerPattern::UpdateAccessibilityText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    int32_t hoverIndexs[] = { yearIndex_, FIRST_SLASH, monthIndex_, SECOND_SLASH, dayIndex_ };
    std::string message;
    for (auto index : hoverIndexs) {
        auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index));
        CHECK_NULL_VOID(textFrameNode);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        message += UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u""));
    }
    auto textAccessibilityProperty = contentNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    textAccessibilityProperty->SetAccessibilityText(message);
}

void CalendarPickerPattern::InitDateIndex()
{
    std::vector<std::string> outOrder;
    bool result = Localization::GetInstance()->GetDateOrder(outOrder);
    if (!result || outOrder.size() < DATE_NODE_COUNT) {
        yearIndex_ = YEAR_INDEX;
        monthIndex_ = MONTH_INDEX;
        dayIndex_ = DAY_INDEX;
    } else {
        size_t index = 0;
        for (size_t i = 0; i < outOrder.size(); ++i) {
            if (outOrder[i] == "year") {
                yearIndex_ = static_cast<int32_t>(i + index);
            }

            if (outOrder[i] == "month") {
                monthIndex_ = static_cast<int32_t>(i + index);
            }

            if (outOrder[i] == "day") {
                dayIndex_ = static_cast<int32_t>(i + index);
            }

            index++;
        }
    }
}

void CalendarPickerPattern::UpdateEntryButtonColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = host->GetLastChild();
    CHECK_NULL_VOID(buttonFlexNode);

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    int32_t buttonIndex = 0;
    for (const auto& child : buttonFlexNode->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto buttonNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(buttonNode);
            BorderColorProperty borderColor;
            borderColor.SetColor(theme->GetEntryBorderColor());
            buttonNode->GetRenderContext()->UpdateBorderColor(borderColor);
            buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
            buttonNode->MarkModifyDone();

            auto image = buttonNode->GetChildren().front();
            CHECK_NULL_VOID(image);
            auto imageNode = AceType::DynamicCast<FrameNode>(image);
            auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(imageLayoutProperty);
            auto imageInfo = imageLayoutProperty->GetImageSourceInfo();
            CHECK_NULL_VOID(imageInfo);
            auto buttonColor = theme->GetEntryArrowColor();
            if (!IsAddOrSubButtonEnable(buttonIndex)) {
                buttonColor = buttonColor.ChangeOpacity(DISABLE_ALPHA);
            }
            imageInfo->SetFillColor(buttonColor);
            buttonIndex++;
            imageLayoutProperty->UpdateImageSourceInfo(imageInfo.value());
            imageNode->MarkModifyDone();
        }
    }
}

void CalendarPickerPattern::UpdateEntryButtonBorderWidth()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = host->GetLastChild();
    CHECK_NULL_VOID(buttonFlexNode);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto addButtonNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(ADD_BUTTON_INDEX));
    CHECK_NULL_VOID(addButtonNode);
    auto subButtonNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(SUB_BUTTON_INDEX));
    CHECK_NULL_VOID(subButtonNode);

    auto textDirection = host->GetLayoutProperty()->GetNonAutoLayoutDirection();
    BorderWidthProperty addBorderWidth;
    BorderWidthProperty subBorderWidth;
    if (textDirection == TextDirection::RTL) {
        addBorderWidth.rightDimen = theme->GetEntryBorderWidth();
        subBorderWidth.rightDimen = theme->GetEntryBorderWidth();
        addBorderWidth.leftDimen = 0.0_vp;
        subBorderWidth.leftDimen = 0.0_vp;
    } else {
        addBorderWidth.rightDimen = 0.0_vp;
        subBorderWidth.rightDimen = 0.0_vp;
        addBorderWidth.leftDimen = theme->GetEntryBorderWidth();
        subBorderWidth.leftDimen = theme->GetEntryBorderWidth();
    }
    addButtonNode->GetLayoutProperty()->UpdateBorderWidth(addBorderWidth);
    subButtonNode->GetLayoutProperty()->UpdateBorderWidth(subBorderWidth);
    addButtonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    subButtonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void CalendarPickerPattern::UpdateEdgeAlign()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();

    auto rtlAlignType = align_;
    auto rtlX = offset_.GetX().Value();
    if (textDirection == TextDirection::RTL) {
        switch (align_) {
            case CalendarEdgeAlign::EDGE_ALIGN_START:
                rtlAlignType = CalendarEdgeAlign::EDGE_ALIGN_END;
                break;
            case CalendarEdgeAlign::EDGE_ALIGN_END:
                rtlAlignType = CalendarEdgeAlign::EDGE_ALIGN_START;
                break;
            default:
                break;
        }
        rtlX = -offset_.GetX().Value();
    }

    layoutProperty->UpdateDialogAlignType(rtlAlignType);
    layoutProperty->UpdateDialogOffset(DimensionOffset(Dimension(rtlX), offset_.GetY()));
}

bool CalendarPickerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool /* skipMeasure */, bool /* skipLayout */)
{
    if (!IsDialogShow()) {
        return true;
    }

    auto eventHub = GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    eventHub->FireLayoutChangeEvent();
    return true;
}

void CalendarPickerPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info.GetGlobalLocation());
    };
    clickListener_ = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void CalendarPickerPattern::HandleHoverEvent(bool state, const Offset& globalLocation)
{
    bool yearState = false, monthState = false, dayState = false, addState = false, subState = false;
    if (state) {
        auto currSelectdDate = calendarData_.selectedDate;
        switch (CheckRegion(globalLocation)) {
            case CalendarPickerSelectedType::YEAR:
                yearState = true;
                break;
            case CalendarPickerSelectedType::MONTH:
                monthState = true;
                break;
            case CalendarPickerSelectedType::DAY:
                dayState = true;
                break;
            case CalendarPickerSelectedType::ADDBTN:
                NextDateBySelectedType(currSelectdDate);
                if (PickerDate::IsDateInRange(currSelectdDate, calendarData_.startDate, calendarData_.endDate)) {
                    addState = true;
                }
                break;
            case CalendarPickerSelectedType::SUBBTN:
                PrevDateBySelectedType(currSelectdDate);
                if (PickerDate::IsDateInRange(currSelectdDate, calendarData_.startDate, calendarData_.endDate)) {
                    subState = true;
                }
                break;
            default:
                break;
        }
    }
    HandleTextHoverEvent(yearState, yearIndex_);
    HandleTextHoverEvent(monthState, monthIndex_);
    HandleTextHoverEvent(dayState, dayIndex_);
    HandleButtonHoverEvent(addState, ADD_BUTTON_INDEX);
    HandleButtonHoverEvent(subState, SUB_BUTTON_INDEX);
}

void CalendarPickerPattern::HandleTouchEvent(bool isPressed, const Offset& globalLocation)
{
    bool addState = false, subState = false;
    if (isPressed) {
        auto currSelectdDate = calendarData_.selectedDate;
        switch (CheckRegion(globalLocation)) {
            case CalendarPickerSelectedType::ADDBTN:
                NextDateBySelectedType(currSelectdDate);
                if (PickerDate::IsDateInRange(currSelectdDate, calendarData_.startDate, calendarData_.endDate)) {
                    addState = true;
                }
                break;
            case CalendarPickerSelectedType::SUBBTN:
                PrevDateBySelectedType(currSelectdDate);
                if (PickerDate::IsDateInRange(currSelectdDate, calendarData_.startDate, calendarData_.endDate)) {
                    subState = true;
                }
                break;
            default:
                break;
        }
    }
    HandleButtonTouchEvent(addState, ADD_BUTTON_INDEX);
    HandleButtonTouchEvent(subState, SUB_BUTTON_INDEX);
}

void CalendarPickerPattern::InitOnHoverEvent()
{
    if (hoverListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    int32_t hoverIndexs[] = { yearIndex_, monthIndex_, dayIndex_ };
    for (auto index : hoverIndexs) {
        auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index));
        CHECK_NULL_VOID(textFrameNode);
        auto inputHub = textFrameNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto hoverCallback = [weak = WeakClaim(this), index](bool state) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleTextHoverEvent(state, index);
        };
        hoverListener_ = AceType::MakeRefPtr<InputEvent>(std::move(hoverCallback));
        inputHub->AddOnHoverEvent(hoverListener_);
    }
}

void CalendarPickerPattern::HandleClickEvent(const Offset& globalLocation)
{
    switch (CheckRegion(globalLocation)) {
        case CalendarPickerSelectedType::YEAR:
            ShowDialog();
            SetSelectedType(CalendarPickerSelectedType::YEAR);
            return;
        case CalendarPickerSelectedType::MONTH:
            ShowDialog();
            SetSelectedType(CalendarPickerSelectedType::MONTH);
            return;
        case CalendarPickerSelectedType::DAY:
            ShowDialog();
            SetSelectedType(CalendarPickerSelectedType::DAY);
            return;
        case CalendarPickerSelectedType::ADDBTN:
            HandleAddButtonClick();
            return;
        case CalendarPickerSelectedType::SUBBTN:
            HandleSubButtonClick();
            return;
        default:
            SetSelectedType(CalendarPickerSelectedType::OTHER);
            break;
    }

    if (!IsDialogShow()) {
        ShowDialog();
    }
}

void CalendarPickerPattern::ResetTextState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(yearIndex_)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(FIRST_SLASH)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(monthIndex_)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(SECOND_SLASH)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(dayIndex_)));
}

void CalendarPickerPattern::ResetTextStateByNode(const RefPtr<FrameNode>& textFrameNode)
{
    CHECK_NULL_VOID(textFrameNode);
    textFrameNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    textFrameNode->GetRenderContext()->UpdateForegroundColor(
        layoutProperty->GetColor().value_or(calendarTheme->GetEntryFontColor()));
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

CalendarPickerSelectedType CalendarPickerPattern::CheckRegion(const Offset& globalLocation)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, CalendarPickerSelectedType::OTHER);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(contentNode, CalendarPickerSelectedType::OTHER);

    auto location = PointF(globalLocation.GetX(), globalLocation.GetY());
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(yearIndex_)), location)) {
        return CalendarPickerSelectedType::YEAR;
    }
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(monthIndex_)), location)) {
        return CalendarPickerSelectedType::MONTH;
    }
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(dayIndex_)), location)) {
        return CalendarPickerSelectedType::DAY;
    }

    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_RETURN(buttonFlexNode, CalendarPickerSelectedType::OTHER);
    if (IsInNodeRegion(DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(ADD_BUTTON_INDEX)), location)) {
        return CalendarPickerSelectedType::ADDBTN;
    }
    if (IsInNodeRegion(DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(SUB_BUTTON_INDEX)), location)) {
        return CalendarPickerSelectedType::SUBBTN;
    }
    return CalendarPickerSelectedType::OTHER;
}

bool CalendarPickerPattern::IsInNodeRegion(const RefPtr<FrameNode>& node, const PointF& point)
{
    CHECK_NULL_RETURN(node, false);
    auto rect = node->GetTransformRectRelativeToWindow();
    return rect.IsInRegion(point);
}

void CalendarPickerPattern::FireChangeEvents(const std::string& info)
{
    auto eventHub = GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateInputChangeEvent(info);
    eventHub->UpdateOnChangeEvent(info);
    eventHub->UpdateChangeEvent(info);
}

void CalendarPickerPattern::ShowDialog()
{
    if (IsDialogShow()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto changeId = [weak = WeakClaim(this)](const std::string& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetDate(info);
    };
    auto acceptId = [weak = WeakClaim(this)](const std::string& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetDialogShow(false);
    };
    dialogEvent["changeId"] = changeId;
    dialogEvent["acceptId"] = acceptId;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelId = [weak = WeakClaim(this)](const GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetDialogShow(false);
    };
    dialogCancelEvent["cancelId"] = cancelId;
    calendarData_.entryNode = AceType::DynamicCast<FrameNode>(host);
    DialogProperties properties;
    InitDialogProperties(properties);
    overlayManager->ShowCalendarDialog(properties, calendarData_, dialogEvent, dialogCancelEvent);
    SetDialogShow(true);
}

void CalendarPickerPattern::InitOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->SetIsFocusOnTouch(true);
    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(std::move(keyTask));

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(std::move(blurTask));
}

void CalendarPickerPattern::HandleBlurEvent()
{
    if (IsDialogShow()) {
        return;
    }
    selected_ = CalendarPickerSelectedType::OTHER;
    ResetTextState();
}

bool CalendarPickerPattern::HandleKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN && (event.code != KeyCode::KEY_TAB || !isFirtFocus_)) {
        return false;
    }
    if (event.IsNumberKey()) {
        return HandleNumberKeyEvent(event);
    }
    return HandleFocusEvent(event);
}

bool CalendarPickerPattern::HandleFocusEvent(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    switch (event.code) {
        case KeyCode::KEY_TAB: {
            ResetTextState();
            if (isFirtFocus_) {
                selected_ = CalendarPickerSelectedType::YEAR;
                HandleTextFocusEvent(yearIndex_);
                if (!IsDialogShow()) {
                    ShowDialog();
                }
                isFirtFocus_ = false;
                return true;
            }
            if (selected_ != CalendarPickerSelectedType::OTHER) {
                selected_ = CalendarPickerSelectedType::OTHER;
                isFirtFocus_ = true;
                return HandleBlurEvent(event);
            }
            return false;
        }
        case KeyCode::KEY_DPAD_LEFT: {
            if (selected_ == CalendarPickerSelectedType::DAY) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::MONTH;
                HandleTextFocusEvent(monthIndex_);
            } else if (selected_ == CalendarPickerSelectedType::MONTH) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::YEAR;
                HandleTextFocusEvent(yearIndex_);
            }
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            if (selected_ == CalendarPickerSelectedType::YEAR) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::MONTH;
                HandleTextFocusEvent(monthIndex_);
            } else if (selected_ == CalendarPickerSelectedType::MONTH) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::DAY;
                HandleTextFocusEvent(dayIndex_);
            }
            return true;
        }
        case KeyCode::KEY_DPAD_UP: {
            if (!isFirtFocus_ || selected_ != CalendarPickerSelectedType::OTHER) {
                HandleAddButtonClick();
            }
            return true;
        }
        case KeyCode::KEY_DPAD_DOWN: {
            if (!isFirtFocus_ || selected_ != CalendarPickerSelectedType::OTHER) {
                HandleSubButtonClick();
            }
            return true;
        }
        case KeyCode::KEY_MOVE_HOME: {
            ResetTextState();
            selected_ = CalendarPickerSelectedType::YEAR;
            HandleTextFocusEvent(yearIndex_);
            return true;
        }
        case KeyCode::KEY_MOVE_END: {
            ResetTextState();
            selected_ = CalendarPickerSelectedType::DAY;
            HandleTextFocusEvent(dayIndex_);
            return true;
        }
        case KeyCode::KEY_SPACE:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_ENTER: {
            if (!IsDialogShow()) {
                ShowDialog();
            }
            return true;
        }
        default:
            break;
    }
    return false;
}

bool CalendarPickerPattern::HandleBlurEvent(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(contentNode, false);
    auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(yearIndex_));
    CHECK_NULL_RETURN(textFrameNode, false);
    auto focusHub = textFrameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->HandleEvent(event);
}

bool CalendarPickerPattern::HandleYearKeyWaitingEvent(
    const uint32_t number, const std::function<void()>& task, const std::function<void()>& zeroStartTask)
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    if (yearPrefixZeroCount_ > 0 && yearPrefixZeroCount_ < YEAR_LENTH - 1 && number == 0 &&
        yearEnterCount_ == yearPrefixZeroCount_ + 1) {
        yearPrefixZeroCount_++;
        PostTaskToUI(std::move(zeroStartTask), "ArkUICalendarPickerYearKeyWaitingZeroStart");
        return true;
    } else if (yearPrefixZeroCount_ >= YEAR_LENTH - 1 && number == 0) {
        yearPrefixZeroCount_ = 0;
        yearEnterCount_ = 0;
        isKeyWaiting_ = false;
        return false;
    }

    auto newYear = json->GetUInt("year") * 10 + number;

    if (yearPrefixZeroCount_ > 0 && yearEnterCount_ == yearPrefixZeroCount_ + 1) {
        newYear = number;
    }
    if (yearEnterCount_ < YEAR_LENTH) {
        json->Replace("year", static_cast<int32_t>(newYear));
        SetDate(json->ToString());
        PostTaskToUI(std::move(task), "ArkUICalendarPickerYearKeyWaitingChange");
        return true;
    }
    newYear = std::max(newYear, MIN_YEAR);
    newYear = std::min(newYear, MAX_YEAR);
    json->Replace("year", static_cast<int32_t>(newYear));
    auto maxDay = PickerDate::GetMaxDay(newYear, json->GetUInt("month"));
    if (json->GetUInt("day") > maxDay) {
        json->Replace("day", static_cast<int32_t>(maxDay));
    }
    SetDate(json->ToString());
    FireChangeEvents(json->ToString());
    if (yearEnterCount_ >= YEAR_LENTH) {
        yearPrefixZeroCount_ = 0;
        yearEnterCount_ = 0;
    }
    isKeyWaiting_ = false;
    return true;
}

bool CalendarPickerPattern::HandleYearKeyEvent(uint32_t number)
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    auto taskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };
    auto zeroStartTaskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };
    if (yearEnterCount_ < YEAR_LENTH) {
        yearEnterCount_++;
    } else {
        return false;
    }
    if (isKeyWaiting_) {
        return HandleYearKeyWaitingEvent(number, taskCallback, zeroStartTaskCallback);
    } else {
        if (number == 0) {
            yearPrefixZeroCount_++;
            PostTaskToUI(std::move(zeroStartTaskCallback), "ArkUICalendarPickerYearZeroStart");
            isKeyWaiting_ = true;
        } else {
            json->Replace("year", static_cast<int32_t>(number));
            SetDate(json->ToString());
            PostTaskToUI(std::move(taskCallback), "ArkUICalendarPickerYearChange");
            isKeyWaiting_ = true;
        }
    }
    return true;
}

bool CalendarPickerPattern::HandleMonthKeyEvent(uint32_t number)
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    auto taskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };
    auto zeroStartTaskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };

    if (isKeyWaiting_) {
        if (monthPrefixZeroCount_ == 1 && number == 0) {
            monthPrefixZeroCount_ = 0;
            isKeyWaiting_ = false;
            return false;
        }

        auto newMonth = json->GetUInt("month") * 10 + number;

        if (monthPrefixZeroCount_ == 1) {
            newMonth = number;
        }
        if (newMonth < 1 || newMonth > MAX_MONTH) {
            return true;
        }
        json->Replace("month", static_cast<int32_t>(newMonth));
        auto maxDay = PickerDate::GetMaxDay(json->GetUInt("year"), newMonth);
        if (json->GetUInt("day") > maxDay) {
            json->Replace("day", static_cast<int32_t>(maxDay));
        }
        SetDate(json->ToString());
        FireChangeEvents(json->ToString());
        isKeyWaiting_ = false;
        monthPrefixZeroCount_ = 0;
    } else {
        if (number == 0) {
            monthPrefixZeroCount_++;
            PostTaskToUI(std::move(zeroStartTaskCallback), "ArkUICalendarPickerMonthZeroStart");
            isKeyWaiting_ = true;
        } else {
            json->Replace("month", static_cast<int32_t>(number));
            SetDate(json->ToString());

            PostTaskToUI(std::move(taskCallback), "ArkUICalendarPickerMonthChange");
            isKeyWaiting_ = true;
        }
    }

    return true;
}

bool CalendarPickerPattern::HandleDayKeyEvent(uint32_t number)
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    auto taskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };
    auto zeroStartTaskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };

    if (isKeyWaiting_) {
        if (dayPrefixZeroCount_ == 1 && number == 0) {
            dayPrefixZeroCount_ = 0;
            isKeyWaiting_ = false;
            return false;
        }

        auto newDay = json->GetUInt("day") * 10 + number;

        if (dayPrefixZeroCount_ == 1) {
            newDay = number;
        }
        if (newDay <= PickerDate::GetMaxDay(json->GetUInt("year"), json->GetUInt("month"))) {
            json->Replace("day", static_cast<int32_t>(newDay));
            SetDate(json->ToString());
            FireChangeEvents(json->ToString());
            isKeyWaiting_ = false;
            dayPrefixZeroCount_ = 0;
        }
    } else {
        if (number == 0) {
            dayPrefixZeroCount_++;
            PostTaskToUI(std::move(zeroStartTaskCallback), "ArkUICalendarPickerDayZeroStart");
            isKeyWaiting_ = true;
        } else {
            json->Replace("day", static_cast<int32_t>(number));
            SetDate(json->ToString());

            PostTaskToUI(std::move(taskCallback), "ArkUICalendarPickerDayChange");
            isKeyWaiting_ = true;
        }
    }

    return true;
}

bool CalendarPickerPattern::HandleNumberKeyEvent(const KeyEvent& event)
{
    if (!event.IsNumberKey()) {
        return false;
    }

    uint32_t number = 0;
    if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
        number = static_cast<uint32_t>(event.code) - static_cast<uint32_t>(KeyCode::KEY_0);
    }
    if (KeyCode::KEY_NUMPAD_0 <= event.code && event.code <= KeyCode::KEY_NUMPAD_9) {
        number = static_cast<uint32_t>(event.code) - static_cast<uint32_t>(KeyCode::KEY_NUMPAD_0);
    }

    switch (GetSelectedType()) {
        case CalendarPickerSelectedType::YEAR:
            return HandleYearKeyEvent(number);
        case CalendarPickerSelectedType::MONTH:
            return HandleMonthKeyEvent(number);
        case CalendarPickerSelectedType::DAY:
            return HandleDayKeyEvent(number);
        default:
            break;
    }
    return false;
}

void CalendarPickerPattern::PostTaskToUI(const std::function<void()>& task, const std::string& name)
{
    CHECK_NULL_VOID(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskCount_++;
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, DELAY_TIME, name);
}

void CalendarPickerPattern::HandleTaskCallback()
{
    taskCount_--;
    if (taskCount_ > 0) {
        return;
    } else if (taskCount_ < 0) {
        taskCount_ = 0;
    }
    if (!isKeyWaiting_) {
        return;
    }

    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    auto newYear = json->GetUInt("year");
    newYear = std::max(newYear, MIN_YEAR);
    newYear = std::min(newYear, MAX_YEAR);
    json->Replace("year", static_cast<int32_t>(newYear));
    auto maxDay = PickerDate::GetMaxDay(newYear, json->GetUInt("month"));
    if (json->GetUInt("day") > maxDay) {
        json->Replace("day", static_cast<int32_t>(maxDay));
    }
    SetDate(json->ToString());
    FireChangeEvents(json->ToString());
    yearEnterCount_ = 0;
    yearPrefixZeroCount_ = 0;
    monthPrefixZeroCount_ = 0;
    dayPrefixZeroCount_ = 0;
    isKeyWaiting_ = false;
}

void CalendarPickerPattern::HandleZeroStartTaskCallback()
{
    taskCount_--;
    if (taskCount_ > 0) {
        return;
    } else if (taskCount_ < 0) {
        taskCount_ = 0;
    }
    if (!isKeyWaiting_) {
        return;
    }

    yearEnterCount_ = 0;
    yearPrefixZeroCount_ = 0;
    monthPrefixZeroCount_ = 0;
    dayPrefixZeroCount_ = 0;
    isKeyWaiting_ = false;
}

void CalendarPickerPattern::HandleTextFocusEvent(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(textFrameNode);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    textFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetSelectBackgroundColor());
    textFrameNode->GetRenderContext()->UpdateForegroundColor(Color::WHITE);
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushAddAndSubButton();
}

void CalendarPickerPattern::HandleTextHoverEvent(bool state, int32_t index)
{
    if ((GetSelectedType() == CalendarPickerSelectedType::YEAR && index == yearIndex_) ||
        (GetSelectedType() == CalendarPickerSelectedType::MONTH && index == monthIndex_) ||
        (GetSelectedType() == CalendarPickerSelectedType::DAY && index == dayIndex_)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(textFrameNode);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (state) {
        textFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetBackgroundHoverColor());
    } else {
        textFrameNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
        auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        textFrameNode->GetRenderContext()->UpdateForegroundColor(
            layoutProperty->GetColor().value_or(theme->GetEntryFontColor()));
    }
}

void CalendarPickerPattern::FlushAddAndSubButton()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_VOID(buttonFlexNode);

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    int32_t buttonIndex = 0;
    for (const auto& child : buttonFlexNode->GetChildren()) {
        CHECK_NULL_VOID(child);
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        auto image = buttonNode->GetChildren().front();
        CHECK_NULL_VOID(image);
        auto imageNode = AceType::DynamicCast<FrameNode>(image);
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageInfo = imageLayoutProperty->GetImageSourceInfo();
        auto buttonColor = theme->GetEntryArrowColor();
        if (!IsAddOrSubButtonEnable(buttonIndex)) {
            buttonColor = buttonColor.ChangeOpacity(DISABLE_ALPHA);
        }
        imageInfo->SetFillColor(buttonColor);
        imageLayoutProperty->UpdateImageSourceInfo(imageInfo.value());
        imageNode->MarkModifyDone();
        buttonIndex++;
    }
}

bool CalendarPickerPattern::IsAddOrSubButtonEnable(int32_t buttonIndex)
{
    PickerDate dateObj = calendarData_.selectedDate;
    if (buttonIndex == ADD_BUTTON_INDEX) {
        NextDateBySelectedType(dateObj);
    }
    if (buttonIndex == SUB_BUTTON_INDEX) {
        PrevDateBySelectedType(dateObj);
    }
    return PickerDate::IsDateInRange(dateObj, calendarData_.startDate, calendarData_.endDate);
}

void CalendarPickerPattern::HandleButtonHoverEvent(bool state, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_VOID(buttonFlexNode);
    auto buttonFrameNode = DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(buttonFrameNode);
    buttonFrameNode->GetRenderContext()->AnimateHoverEffectBoard(state);
}

void CalendarPickerPattern::HandleButtonTouchEvent(bool isPressed, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_VOID(buttonFlexNode);
    auto buttonFrameNode = DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(buttonFrameNode);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (isPressed) {
        buttonFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetBackgroundPressColor());
    } else {
        buttonFrameNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    }
}

void CalendarPickerPattern::NextDateBySelectedType(PickerDate& dateObj)
{
    switch (GetSelectedType()) {
        case CalendarPickerSelectedType::YEAR: {
            dateObj.SetYear(dateObj.GetYear() == MAX_YEAR ? MIN_YEAR : dateObj.GetYear() + 1);
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay()) {
                dateObj.SetDay(maxDay);
            }
            break;
        }
        case CalendarPickerSelectedType::MONTH: {
            dateObj.SetMonth(dateObj.GetMonth() % MAX_MONTH + 1);
            if (dateObj.GetMonth() == 1) {
                dateObj.SetYear(dateObj.GetYear() == MAX_YEAR ? MIN_YEAR : dateObj.GetYear() + 1);
            }
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay()) {
                dateObj.SetDay(maxDay);
            }
            break;
        }
        case CalendarPickerSelectedType::DAY:
        default: {
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay > dateObj.GetDay()) {
                dateObj.SetDay(dateObj.GetDay() + 1);
                break;
            }
            dateObj.SetDay(1);
            if (dateObj.GetMonth() < MAX_MONTH) {
                dateObj.SetMonth(dateObj.GetMonth() + 1);
                break;
            }
            dateObj.SetMonth(1);
            dateObj.SetYear(dateObj.GetYear() == MAX_YEAR ? MIN_YEAR : dateObj.GetYear() + 1);
            break;
        }
    }
}

void CalendarPickerPattern::PrevDateBySelectedType(PickerDate& dateObj)
{
    switch (GetSelectedType()) {
        case CalendarPickerSelectedType::YEAR: {
            auto getYear = dateObj.GetYear();
            dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : (getYear > 0 ? getYear - 1 : 0));
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay())
                dateObj.SetDay(maxDay);
            break;
        }
        case CalendarPickerSelectedType::MONTH: {
            auto getMonth = dateObj.GetMonth();
            auto newMonth = getMonth > 0 ? getMonth - 1 : 0;
            if (newMonth == 0) {
                dateObj.SetMonth(MAX_MONTH);
                auto getYear = dateObj.GetYear();
                dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : (getYear > 0 ? getYear - 1 : 0));
            } else {
                dateObj.SetMonth(newMonth);
            }
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay())
                dateObj.SetDay(maxDay);
            break;
        }
        case CalendarPickerSelectedType::DAY:
        default: {
            if (dateObj.GetDay() > 1) {
                dateObj.SetDay(dateObj.GetDay() - 1);
                break;
            }
            if (dateObj.GetMonth() == 1) {
                dateObj.SetMonth(MAX_MONTH);
                auto getYear = dateObj.GetYear();
                dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : (getYear > 0 ? getYear - 1 : 0));
            } else {
                auto getMonth = dateObj.GetMonth();
                dateObj.SetMonth(getMonth > 0 ? getMonth - 1 : 0);
            }
            dateObj.SetDay(PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth()));
            break;
        }
    }
}

void CalendarPickerPattern::HandleAddButtonClick()
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    PickerDate dateObj = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
    NextDateBySelectedType(dateObj);
    if (PickerDate::IsDateInRange(dateObj, calendarData_.startDate, calendarData_.endDate)) {
        if (GetSelectedType() != CalendarPickerSelectedType::YEAR &&
            GetSelectedType() != CalendarPickerSelectedType::MONTH) {
            SetSelectedType(CalendarPickerSelectedType::DAY);
        }
        SetDate(dateObj.ToString(true));
        FireChangeEvents(dateObj.ToString(true));
        FlushAddAndSubButton();
    }
}

void CalendarPickerPattern::HandleSubButtonClick()
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    PickerDate dateObj = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
    PrevDateBySelectedType(dateObj);
    if (PickerDate::IsDateInRange(dateObj, calendarData_.startDate, calendarData_.endDate)) {
        if (GetSelectedType() != CalendarPickerSelectedType::YEAR &&
            GetSelectedType() != CalendarPickerSelectedType::MONTH) {
            SetSelectedType(CalendarPickerSelectedType::DAY);
        }
        SetDate(dateObj.ToString(true));
        FireChangeEvents(dateObj.ToString(true));
        FlushAddAndSubButton();
    }
}

void CalendarPickerPattern::HandleEnable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : DISABLE_ALPHA * originalOpacity);
}

OffsetF CalendarPickerPattern::CalculateDialogOffset()
{
    UpdateEdgeAlign();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, OffsetF());
    float x = 0.0f;
    float y = 0.0f;
    auto hostOffset = host->GetOffsetRelativeToWindow();
    auto hostSize = host->GetGeometryNode()->GetFrameSize();

    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, OffsetF());

    float dialogHeight = pipelineContext->GetRootHeight();
    if (IsContainerModal()) {
        auto rootNode = pipelineContext->GetRootElement();
        CHECK_NULL_RETURN(rootNode, OffsetF());
        auto containerNode = AceType::DynamicCast<FrameNode>(rootNode->GetChildren().front());
        CHECK_NULL_RETURN(containerNode, OffsetF());
        auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
        CHECK_NULL_RETURN(containerPattern, OffsetF());
        auto titleHeight = containerPattern->GetContainerModalTitleHeight();
        dialogHeight -= titleHeight;
        hostOffset -= OffsetF(0, titleHeight);
    }

    auto hostRect = RectF(hostOffset, hostSize);
    if (hostRect.Bottom() + (DIALOG_HEIGHT).ConvertToPx() > dialogHeight) {
        y = std::max(static_cast<float>(hostRect.Top() - (DIALOG_HEIGHT).ConvertToPx()), 0.0f);
    } else {
        y = hostRect.Bottom() + (theme->GetDialogMargin()).ConvertToPx();
    }

    CalendarEdgeAlign align = layoutProperty->GetDialogAlignType().value_or(CalendarEdgeAlign::EDGE_ALIGN_END);
    if (align == CalendarEdgeAlign::EDGE_ALIGN_START) {
        x = std::min(
            hostRect.Left(), static_cast<float>(pipelineContext->GetRootWidth() - (DIALOG_WIDTH).ConvertToPx()));
    } else if (align == CalendarEdgeAlign::EDGE_ALIGN_CENTER) {
        auto hostCenterX = (hostRect.Left() + hostRect.Right()) / 2;
        x = std::max(0.0f, static_cast<float>(hostCenterX - (DIALOG_WIDTH).ConvertToPx() / 2));
        x = std::min(x, static_cast<float>(pipelineContext->GetRootWidth() - (DIALOG_WIDTH).ConvertToPx()));
    } else {
        x = std::max(0.0f, static_cast<float>(hostRect.Right() - (DIALOG_WIDTH).ConvertToPx()));
    }

    auto offset = layoutProperty->GetDialogOffset().value_or(DimensionOffset());

    return OffsetF(x + offset.GetX().ConvertToPx(), y + offset.GetY().ConvertToPx());
}

void CalendarPickerPattern::InitDialogProperties(DialogProperties& properties)
{
    properties.customStyle = true;
    properties.maskColor = Color(0);
    properties.offset = DimensionOffset(CalculateDialogOffset());
    properties.alignment = DialogAlignment::TOP_START;
    auto cancelId = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetDialogShow(false);
    };
    properties.onCancel = cancelId;
}

void CalendarPickerPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (type != WindowSizeChangeReason::ROTATION && type != WindowSizeChangeReason::DRAG) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void CalendarPickerPattern::OnColorConfigurationUpdate()
{
    if (IsDialogShow()) {
        return;
    }
    selected_ = CalendarPickerSelectedType::OTHER;
    ResetTextState();
}

std::string CalendarPickerPattern::GetEntryDateInfo()
{
    if (!HasContentNode()) {
        return "";
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(contentNode, "");
    auto json = JsonUtil::Create(true);
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(yearIndex_));
    CHECK_NULL_RETURN(yearNode, "");
    auto textLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("year",
        StringUtils::StringToInt(UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u"1970"))));

    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(monthIndex_));
    CHECK_NULL_RETURN(monthNode, "");
    textLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("month",
        StringUtils::StringToInt(UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u"01"))));

    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(dayIndex_));
    CHECK_NULL_RETURN(dayNode, "");
    textLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("day",
        StringUtils::StringToInt(UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u"01"))));

    return json->ToString();
}

void CalendarPickerPattern::SetDate(const std::string& info)
{
    if (!HasContentNode()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    auto json = JsonUtil::ParseJsonString(info);
    auto selectedDate = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
    calendarData_.selectedDate =
        PickerDate::AdjustDateToRange(selectedDate, calendarData_.startDate, calendarData_.endDate);
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(yearIndex_));
    CHECK_NULL_VOID(yearNode);
    auto textLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto yearNum = json->GetUInt("year");
    auto yearStr = std::to_string(yearNum);
    yearStr = (yearNum < 1000 ? "0" : "") + yearStr;
    yearStr = (yearNum < 100 ? "0" : "") + yearStr;
    yearStr = (yearNum < 10 ? "0" : "") + yearStr;
    textLayoutProperty->UpdateContent(yearStr);
    yearNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(monthIndex_));
    CHECK_NULL_VOID(monthNode);
    textLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto monthString = (json->GetUInt("month") < 10 ? "0" : "") + std::to_string(json->GetUInt("month"));
    textLayoutProperty->UpdateContent(monthString);
    monthNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(dayIndex_));
    CHECK_NULL_VOID(dayNode);
    textLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto dayString = (json->GetUInt("day") < 10 ? "0" : "") + std::to_string(json->GetUInt("day"));
    textLayoutProperty->UpdateContent(dayString);
    dayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    UpdateAccessibilityText();
}

void CalendarPickerPattern::FlushTextStyle()
{
    if (!HasContentNode()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    int32_t len = static_cast<int32_t>(contentNode->GetChildren().size());
    for (int32_t i = 0; i < len; i++) {
        auto textNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);

        if (selected_ != CalendarPickerSelectedType::YEAR && selected_ != CalendarPickerSelectedType::MONTH &&
            selected_ != CalendarPickerSelectedType::DAY && layoutProperty->HasColor()) {
            ResetTextStateByNode(textNode);
        } else {
            SetSelectedType(selected_);
        }
        if (layoutProperty->HasFontSize()) {
            textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
        }
        if (layoutProperty->HasWeight()) {
            textLayoutProperty->UpdateFontWeight(layoutProperty->GetWeight().value());
        }
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void CalendarPickerPattern::SetSelectedType(CalendarPickerSelectedType type)
{
    selected_ = type;
    switch (selected_) {
        case CalendarPickerSelectedType::YEAR:
            ResetTextState();
            HandleTextFocusEvent(yearIndex_);
            break;
        case CalendarPickerSelectedType::MONTH:
            ResetTextState();
            HandleTextFocusEvent(monthIndex_);
            break;
        case CalendarPickerSelectedType::DAY:
            ResetTextState();
            HandleTextFocusEvent(dayIndex_);
            break;
        default:
            break;
    }
}

bool CalendarPickerPattern::IsContainerModal()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto windowManager = pipelineContext->GetWindowManager();
    return pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
}
} // namespace OHOS::Ace::NG

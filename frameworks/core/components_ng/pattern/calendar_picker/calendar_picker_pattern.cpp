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

#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t YEAR_INDEX = 0;
constexpr int32_t MONTH_INDEX = 2;
constexpr int32_t DAY_INDEX = 4;
constexpr int32_t ADD_BUTTON_INDEX = 0;
constexpr int32_t SUB_BUTTON_INDEX = 1;
constexpr uint32_t MIN_YEAR = 1;
constexpr uint32_t MAX_YEAR = 5000;
constexpr uint32_t DELAY_TIME = 2000;
constexpr uint32_t MAX_MONTH = 12;
constexpr Dimension DIALOG_HEIGHT = 348.0_vp;
constexpr Dimension DIALOG_WIDTH = 336.0_vp;
} // namespace
void CalendarPickerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitClickEvent();
    InitOnKeyEvent();
    InitOnHoverEvent();
    FlushTextStyle();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    UpdateEntryButtonColor();
}

void CalendarPickerPattern::UpdateEntryButtonColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFlexNode = host->GetLastChild();
    CHECK_NULL_VOID(buttonFlexNode);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    for (const auto& child : buttonFlexNode->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto buttonNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(buttonNode);
            buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
            buttonNode->MarkModifyDone();

            auto image = buttonNode->GetChildren().front();
            CHECK_NULL_VOID(image);
            auto imageNode = AceType::DynamicCast<FrameNode>(image);
            auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(imageLayoutProperty);
            auto imageInfo = imageLayoutProperty->GetImageSourceInfo();
            imageInfo->SetFillColor(theme->GetEntryArrowColor());
            imageLayoutProperty->UpdateImageSourceInfo(imageInfo.value());
            imageNode->MarkModifyDone();
        }
    }
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
                addState = true;
                break;
            case CalendarPickerSelectedType::SUBBTN:
                subState = true;
                break;
            default:
                break;
        }
    }
    HandleTextHoverEvent(yearState, YEAR_INDEX);
    HandleTextHoverEvent(monthState, MONTH_INDEX);
    HandleTextHoverEvent(dayState, DAY_INDEX);
    HandleButtonHoverEvent(addState, ADD_BUTTON_INDEX);
    HandleButtonHoverEvent(subState, SUB_BUTTON_INDEX);
}

void CalendarPickerPattern::HandleTouchEvent(bool isPressed, const Offset& globalLocation)
{
    bool addState = false, subState = false;
    if (isPressed) {
        switch (CheckRegion(globalLocation)) {
            case CalendarPickerSelectedType::ADDBTN:
                addState = true;
                break;
            case CalendarPickerSelectedType::SUBBTN:
                subState = true;
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
    int32_t hoverIndexs[] = { YEAR_INDEX, MONTH_INDEX, DAY_INDEX };
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
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(YEAR_INDEX)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(MONTH_INDEX)));
    ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(DAY_INDEX)));
}

void CalendarPickerPattern::ResetTextStateByNode(const RefPtr<FrameNode>& textFrameNode)
{
    CHECK_NULL_VOID(textFrameNode);
    textFrameNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    textLayoutProperty->UpdateTextColor(layoutProperty->GetColor().value_or(calendarTheme->GetEntryFontColor()));
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

CalendarPickerSelectedType CalendarPickerPattern::CheckRegion(const Offset& globalLocation)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, CalendarPickerSelectedType::OTHER);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(contentNode, CalendarPickerSelectedType::OTHER);

    auto location = PointF(globalLocation.GetX(), globalLocation.GetY());
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(YEAR_INDEX)), location)) {
        return CalendarPickerSelectedType::YEAR;
    }
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(MONTH_INDEX)), location)) {
        return CalendarPickerSelectedType::MONTH;
    }
    if (IsInNodeRegion(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(DAY_INDEX)), location)) {
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
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto rect = geometryNode->GetFrameRect();
    rect.SetOffset(node->GetPaintRectOffset());
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
    auto pipeline = PipelineContext::GetCurrentContext();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
        CHECK_NULL_VOID_NOLOG(pattern);
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
                HandleTextFocusEvent(YEAR_INDEX);
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
                HandleTextFocusEvent(MONTH_INDEX);
            } else if (selected_ == CalendarPickerSelectedType::MONTH) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::YEAR;
                HandleTextFocusEvent(YEAR_INDEX);
            }
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            if (selected_ == CalendarPickerSelectedType::YEAR) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::MONTH;
                HandleTextFocusEvent(MONTH_INDEX);
            } else if (selected_ == CalendarPickerSelectedType::MONTH) {
                ResetTextState();
                selected_ = CalendarPickerSelectedType::DAY;
                HandleTextFocusEvent(DAY_INDEX);
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
            HandleTextFocusEvent(YEAR_INDEX);
            return true;
        }
        case KeyCode::KEY_MOVE_END: {
            ResetTextState();
            selected_ = CalendarPickerSelectedType::DAY;
            HandleTextFocusEvent(DAY_INDEX);
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
    auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(YEAR_INDEX));
    CHECK_NULL_RETURN(textFrameNode, false);
    auto focusHub = textFrameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->HandleKeyEvent(event);
}

bool CalendarPickerPattern::HandleYearKeyEvent(uint32_t number)
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    auto taskCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTaskCallback();
    };

    if (isKeyWaiting_) {
        if (json->GetUInt("year") >= 1000) {
            isKeyWaiting_ = false;
            return true;
        }

        auto newYear = json->GetUInt("year") * 10 + number;
        if (newYear < 1 || newYear > 9999) {
            return true;
        }
        if (newYear < 1000) {
            json->Replace("year", static_cast<int32_t>(newYear));
            SetDate(json->ToString());
            PostTaskToUI(std::move(taskCallback));
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
        isKeyWaiting_ = false;
    } else {
        if (number == 0) {
            return false;
        } else {
            json->Replace("year", static_cast<int32_t>(number));
            SetDate(json->ToString());
            PostTaskToUI(std::move(taskCallback));
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

    if (isKeyWaiting_) {
        if (json->GetUInt("month") >= 10) {
            isKeyWaiting_ = false;
            return false;
        }

        auto newMonth = json->GetUInt("month") * 10 + number;
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
    } else {
        if (number == 0) {
            return false;
        } else {
            json->Replace("month", static_cast<int32_t>(number));
            SetDate(json->ToString());

            PostTaskToUI(std::move(taskCallback));
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

    if (isKeyWaiting_) {
        if (json->GetUInt("day") >= 10) {
            isKeyWaiting_ = false;
            return false;
        }

        auto newDay = json->GetUInt("day") * 10 + number;
        if (newDay <= PickerDate::GetMaxDay(json->GetUInt("year"), json->GetUInt("month"))) {
            json->Replace("day", static_cast<int32_t>(newDay));
            SetDate(json->ToString());
            FireChangeEvents(json->ToString());
            isKeyWaiting_ = false;
        }
    } else {
        if (number == 0) {
            return false;
        } else {
            json->Replace("day", static_cast<int32_t>(number));
            SetDate(json->ToString());

            PostTaskToUI(std::move(taskCallback));
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

void CalendarPickerPattern::PostTaskToUI(const std::function<void()>& task)
{
    CHECK_NULL_VOID(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskCount_++;
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, DELAY_TIME);
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    textFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetSelectBackgroundColor());
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(Color::WHITE);
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CalendarPickerPattern::HandleTextHoverEvent(bool state, int32_t index)
{
    if ((GetSelectedType() == CalendarPickerSelectedType::YEAR && index == YEAR_INDEX) ||
        (GetSelectedType() == CalendarPickerSelectedType::MONTH && index == MONTH_INDEX) ||
        (GetSelectedType() == CalendarPickerSelectedType::DAY && index == DAY_INDEX)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    auto textFrameNode = DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(textFrameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (state) {
        textFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetBackgroundHoverColor());
    } else {
        ResetTextStateByNode(DynamicCast<FrameNode>(contentNode->GetChildAtIndex(index)));
    }
    textFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (isPressed) {
        buttonFrameNode->GetRenderContext()->UpdateBackgroundColor(theme->GetBackgroundPressColor());
    } else {
        buttonFrameNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    }
}

void CalendarPickerPattern::HandleAddButtonClick()
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    PickerDate dateObj = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
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
            SetSelectedType(CalendarPickerSelectedType::DAY);
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
    SetDate(dateObj.ToString(true));
    FireChangeEvents(dateObj.ToString(true));
}

void CalendarPickerPattern::HandleSubButtonClick()
{
    auto json = JsonUtil::ParseJsonString(GetEntryDateInfo());
    PickerDate dateObj = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
    switch (GetSelectedType()) {
        case CalendarPickerSelectedType::YEAR: {
            dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : dateObj.GetYear() - 1);
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay()) {
                dateObj.SetDay(maxDay);
            }
            break;
        }
        case CalendarPickerSelectedType::MONTH: {
            auto newMonth = dateObj.GetMonth() - 1;
            if (newMonth == 0) {
                dateObj.SetMonth(MAX_MONTH);
                dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : dateObj.GetYear() - 1);
            } else {
                dateObj.SetMonth(newMonth);
            }
            auto maxDay = PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth());
            if (maxDay < dateObj.GetDay()) {
                dateObj.SetDay(maxDay);
            }
            break;
        }
        case CalendarPickerSelectedType::DAY:
        default: {
            SetSelectedType(CalendarPickerSelectedType::DAY);
            if (dateObj.GetDay() > 1) {
                dateObj.SetDay(dateObj.GetDay() - 1);
                break;
            }
            if (dateObj.GetMonth() == 1) {
                dateObj.SetMonth(MAX_MONTH);
                dateObj.SetYear(dateObj.GetYear() == MIN_YEAR ? MAX_YEAR : dateObj.GetYear() - 1);
            } else {
                dateObj.SetMonth(dateObj.GetMonth() - 1);
            }
            dateObj.SetDay(PickerDate::GetMaxDay(dateObj.GetYear(), dateObj.GetMonth()));
            break;
        }
    }
    SetDate(dateObj.ToString(true));
    FireChangeEvents(dateObj.ToString(true));
}

OffsetF CalendarPickerPattern::CalculateDialogOffset()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, OffsetF());
    float x = 0.0f;
    float y = 0.0f;
    auto hostRect = host->GetTransformRectRelativeToWindow();
    hostRect.SetOffset(host->GetPaintRectOffsetToPage());
    auto hostTop = hostRect.Top();
    auto hostBottom = hostRect.Bottom();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();

    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, OffsetF());

    if (!IsContainerModal() && hostTop + (DIALOG_HEIGHT).ConvertToPx() > windowGlobalRect.Height()) {
        y = std::max(static_cast<float>(hostTop - (DIALOG_HEIGHT).ConvertToPx()), 0.0f);
    } else {
        y = hostBottom + (theme->GetDialogMargin()).ConvertToPx();
    }

    CalendarEdgeAlign align = layoutProperty->GetDialogAlignType().value_or(CalendarEdgeAlign::EDGE_ALIGN_END);
    if (align == CalendarEdgeAlign::EDGE_ALIGN_START) {
        x = std::min(hostRect.Left(), static_cast<float>(windowGlobalRect.Width() - (DIALOG_WIDTH).ConvertToPx()));
    } else if (align == CalendarEdgeAlign::EDGE_ALIGN_CENTER) {
        auto hostCenterX = (hostRect.Left() + hostRect.Right()) / 2;
        x = std::max(0.0f, static_cast<float>(hostCenterX - (DIALOG_WIDTH).ConvertToPx() / 2));
        x = std::min(x, static_cast<float>(windowGlobalRect.Width() - (DIALOG_WIDTH).ConvertToPx()));
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
    if (type != WindowSizeChangeReason::ROTATION) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetFirstChild());
    CHECK_NULL_RETURN(yearNode, "");
    auto textLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("year", StringUtils::StringToInt(textLayoutProperty->GetContent().value_or("1970")));

    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(MONTH_INDEX));
    CHECK_NULL_RETURN(monthNode, "");
    textLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("month", StringUtils::StringToInt(textLayoutProperty->GetContent().value_or("01")));

    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetLastChild());
    CHECK_NULL_RETURN(dayNode, "");
    textLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    json->Put("day", StringUtils::StringToInt(textLayoutProperty->GetContent().value_or("01")));

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

    calendarData_.selectedDate = PickerDate(json->GetUInt("year"), json->GetUInt("month"), json->GetUInt("day"));
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetFirstChild());
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

    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(MONTH_INDEX));
    CHECK_NULL_VOID(monthNode);
    textLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto monthString = (json->GetUInt("month") < 10 ? "0" : "") + std::to_string(json->GetUInt("month"));
    textLayoutProperty->UpdateContent(monthString);
    monthNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetLastChild());
    CHECK_NULL_VOID(dayNode);
    textLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto dayString = (json->GetUInt("day") < 10 ? "0" : "") + std::to_string(json->GetUInt("day"));
    textLayoutProperty->UpdateContent(dayString);
    dayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
            textLayoutProperty->UpdateTextColor(layoutProperty->GetColor().value());
        } else {
            SetSelectedType(selected_);
        }
        if (layoutProperty->HasFontSize()) {
            textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
        }
        if (layoutProperty->HasWeight()) {
            textLayoutProperty->UpdateFontWeight(layoutProperty->GetWeight().value());
        }
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void CalendarPickerPattern::SetSelectedType(CalendarPickerSelectedType type)
{
    selected_ = type;
    switch (selected_) {
        case CalendarPickerSelectedType::YEAR:
            ResetTextState();
            HandleTextFocusEvent(YEAR_INDEX);
            break;
        case CalendarPickerSelectedType::MONTH:
            ResetTextState();
            HandleTextFocusEvent(MONTH_INDEX);
            break;
        case CalendarPickerSelectedType::DAY:
            ResetTextState();
            HandleTextFocusEvent(DAY_INDEX);
            break;
        default:
            break;
    }
}

bool CalendarPickerPattern::IsContainerModal()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto windowManager = pipelineContext->GetWindowManager();
    return pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
}
} // namespace OHOS::Ace::NG

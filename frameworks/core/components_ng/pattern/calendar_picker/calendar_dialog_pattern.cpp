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

#include "core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h"

#include "base/i18n/localization.h"
#include "base/utils/date_util.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TITLE_NODE_INDEX = 0;
constexpr int32_t CALENDAR_NODE_INDEX = 2;
constexpr int32_t OPTIONS_NODE_INDEX = 3;
constexpr int32_t TITLE_LAST_YEAR_BUTTON_NODE_INDEX = 0;
constexpr int32_t TITLE_LAST_MONTH_BUTTON_NODE_INDEX = 1;
constexpr int32_t TITLE_TEXT_NODE_INDEX = 2;
constexpr int32_t TITLE_NEXT_MONTH_BUTTON_NODE_INDEX = 3;
constexpr int32_t TITLE_NEXT_YEAR_BUTTON_NODE_INDEX = 4;
constexpr int32_t OPTIONS_DIVIDER_NODE_INDEX = 1;
constexpr int32_t SWIPER_CHILDREN_SIZE = 3;
constexpr int32_t WEEK_DAYS = 7;
constexpr int32_t MAX_MONTH = 12;
constexpr int32_t MIN_YEAR = 1;
constexpr int32_t MAX_YEAR = 5000;
constexpr size_t CANCEL_BUTTON_FONT_COLOR_INDEX = 0;
constexpr size_t CANCEL_BUTTON_BACKGROUND_COLOR_INDEX = 1;
constexpr size_t ACCEPT_BUTTON_FONT_COLOR_INDEX = 2;
constexpr size_t ACCEPT_BUTTON_BACKGROUND_COLOR_INDEX = 3;
constexpr size_t OPTION_CANCEL_BUTTON_INDEX = 0;
constexpr size_t OPTION_ACCEPT_BUTTON_INDEX = 1;
} // namespace
void CalendarDialogPattern::OnModifyDone()
{
    LinearLayoutPattern::OnModifyDone();
    UpdateCalendarLayout();

    InitClickEvent();
    InitOnKeyEvent();
    InitOnTouchEvent();
    InitHoverEvent();
    InitTitleArrowsEvent();
    InitEntryChangeEvent();

    UpdateTitleArrowsImage();
    UpdateOptionsButton();
    UpdateDialogBackgroundColor();
    UpdateTitleArrowsColor();
    UpdateOptionsButtonColor();
}

void CalendarDialogPattern::UpdateCalendarLayout()
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto textDirection = entryNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarNode);
    const auto& calendarLayoutProperty = calendarNode->GetLayoutProperty();
    CHECK_NULL_VOID(calendarLayoutProperty);
    calendarLayoutProperty->UpdateLayoutDirection(textDirection);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(hostNode);
    auto title = host->GetChildAtIndex(TITLE_NODE_INDEX);
    CHECK_NULL_VOID(title);
    auto titleNode = AceType::DynamicCast<FrameNode>(title);
    CHECK_NULL_VOID(titleNode);
    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_VOID(titleLayoutProperty);
    titleLayoutProperty->UpdateLayoutDirection(textDirection);
}
void CalendarDialogPattern::UpdateDialogBackgroundColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto wrapperNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(wrapperNode);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    auto contentRenderContext = wrapperNode->GetRenderContext();
    CHECK_NULL_VOID(contentRenderContext);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        contentRenderContext->UpdateBackgroundColor(theme->GetDialogBackgroundColor());
    }
}

void CalendarDialogPattern::UpdateTitleArrowsColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto title = host->GetChildAtIndex(TITLE_NODE_INDEX);
    CHECK_NULL_VOID(title);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    for (const auto& child : title->GetChildren()) {
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
            CHECK_NULL_VOID(imageInfo);
            imageInfo->SetFillColor(theme->GetEntryArrowColor());
            imageLayoutProperty->UpdateImageSourceInfo(imageInfo.value());
            imageNode->MarkModifyDone();
        }
    }
}

void CalendarDialogPattern::UpdateTitleArrowsImage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto title = host->GetChildAtIndex(TITLE_NODE_INDEX);
    CHECK_NULL_VOID(title);
    auto titleNode = AceType::DynamicCast<FrameNode>(title);
    CHECK_NULL_VOID(titleNode);
    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_VOID(titleLayoutProperty);
    auto textDirection = titleLayoutProperty->GetNonAutoLayoutDirection();

    auto lastYearNode = AceType::DynamicCast<FrameNode>(title->GetChildAtIndex(TITLE_LAST_YEAR_BUTTON_NODE_INDEX));
    CHECK_NULL_VOID(lastYearNode);
    auto lastMonthNode = AceType::DynamicCast<FrameNode>(title->GetChildAtIndex(TITLE_LAST_MONTH_BUTTON_NODE_INDEX));
    CHECK_NULL_VOID(lastMonthNode);
    auto nextMonthNode = AceType::DynamicCast<FrameNode>(title->GetChildAtIndex(TITLE_NEXT_MONTH_BUTTON_NODE_INDEX));
    CHECK_NULL_VOID(nextMonthNode);
    auto nextYearNode = AceType::DynamicCast<FrameNode>(title->GetChildAtIndex(TITLE_NEXT_YEAR_BUTTON_NODE_INDEX));
    CHECK_NULL_VOID(nextYearNode);

    if (textDirection == TextDirection::RTL) {
        UpdateImage(lastYearNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG);
        UpdateImage(lastMonthNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
        UpdateImage(nextMonthNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
        UpdateImage(nextYearNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG);
    } else {
        UpdateImage(lastYearNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG);
        UpdateImage(lastMonthNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
        UpdateImage(nextMonthNode, InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
        UpdateImage(nextYearNode, InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG);
    }
}

void CalendarDialogPattern::UpdateImage(
    const RefPtr<FrameNode>& buttonNode, const InternalResource::ResourceId& resourceId)
{
    auto image = buttonNode->GetChildren().front();
    CHECK_NULL_VOID(image);
    auto imageNode = AceType::DynamicCast<FrameNode>(image);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(resourceId);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageNode->MarkModifyDone();
}

void CalendarDialogPattern::UpdateOptionsButton()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto options = host->GetChildAtIndex(OPTIONS_NODE_INDEX);
    CHECK_NULL_VOID(options);

    size_t buttonIndex = OPTION_CANCEL_BUTTON_INDEX;
    for (const auto& child : options->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto button = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(button);
            auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
            CHECK_NULL_VOID(buttonLayoutProperty);
            if (buttonIndex == OPTION_ACCEPT_BUTTON_INDEX) {
                buttonLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.ok"));
            } else {
                buttonLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.cancel"));
            }
            button->MarkDirtyNode();
            buttonIndex++;
        }
    }
}

void CalendarDialogPattern::UpdateOptionsButtonColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto options = host->GetChildAtIndex(OPTIONS_NODE_INDEX);
    CHECK_NULL_VOID(options);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    size_t buttonIndex = OPTION_CANCEL_BUTTON_INDEX;
    for (const auto& child : options->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::BUTTON_ETS_TAG) {
            auto button = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(button);
            bool cancelNotUpdateBGColor =
                buttonIndex == OPTION_CANCEL_BUTTON_INDEX && !updateColorFlags[CANCEL_BUTTON_BACKGROUND_COLOR_INDEX];
            bool acceptNotUpdateBGColor =
                buttonIndex == OPTION_ACCEPT_BUTTON_INDEX && !updateColorFlags[ACCEPT_BUTTON_BACKGROUND_COLOR_INDEX];
            if (!(cancelNotUpdateBGColor || acceptNotUpdateBGColor)) {
                auto defaultBGColor = calendarTheme->GetIsButtonTransparent()
                                          ? Color::TRANSPARENT
                                          : calendarTheme->GetDialogButtonBackgroundColor();
                button->GetRenderContext()->UpdateBackgroundColor(defaultBGColor);
            }
            button->MarkModifyDone();

            auto text = button->GetChildren().front();
            CHECK_NULL_VOID(text);
            auto textNode = AceType::DynamicCast<FrameNode>(text);
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            bool cancelNotUpdateFontColor =
                buttonIndex == OPTION_CANCEL_BUTTON_INDEX && !updateColorFlags[CANCEL_BUTTON_FONT_COLOR_INDEX];
            bool acceptNotUpdateFontColor =
                buttonIndex == OPTION_ACCEPT_BUTTON_INDEX && !updateColorFlags[ACCEPT_BUTTON_FONT_COLOR_INDEX];
            if (!(cancelNotUpdateFontColor || acceptNotUpdateFontColor)) {
                textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
            }
            textNode->MarkModifyDone();

            buttonIndex++;
        }
    }
}

void CalendarDialogPattern::SetOptionsButtonUpdateColorFlags(size_t index, bool isUpdate)
{
    if (index >= updateColorFlags.size()) {
        return;
    }

    updateColorFlags[index] = isUpdate;
}

void CalendarDialogPattern::InitHoverEvent()
{
    CHECK_NULL_VOID(!hoverListener_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto mouseCallback = [weak = WeakClaim(this)](const MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->GetHoverState());
        pattern->HandleEntryNodeHoverEvent(
            pattern->IsInEntryRegion(info.GetGlobalLocation()), info.GetGlobalLocation());
    };
    inputHub->SetMouseEvent(std::move(mouseCallback));

    auto hoverCallback = [weak = WeakClaim(this)](bool state) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetHoverState(state);
        if (!state) {
            Offset location;
            pattern->HandleEntryNodeHoverEvent(false, location);
        }
    };
    hoverListener_ = MakeRefPtr<InputEvent>(std::move(hoverCallback));
    inputHub->AddOnHoverEvent(hoverListener_);
}

bool CalendarDialogPattern::IsInEntryRegion(const Offset& globalLocation)
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_RETURN(entryNode, false);
    return entryNode->GetTransformRectRelativeToWindow().IsInRegion(
        PointF(globalLocation.GetX(), globalLocation.GetY()));
}

void CalendarDialogPattern::HandleEntryNodeHoverEvent(bool state, const Offset& globalLocation)
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto pattern = entryNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->HandleHoverEvent(state, globalLocation);
}

void CalendarDialogPattern::HandleEntryNodeTouchEvent(bool isPressed, const Offset& globalLocation)
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    if (IsInEntryRegion(globalLocation)) {
        auto pattern = entryNode->GetPattern<CalendarPickerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(isPressed, globalLocation);
    }
}

void CalendarDialogPattern::InitClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };
    auto onClick = AceType::MakeRefPtr<ClickEvent>(clickCallback);
    gesture->AddClickEvent(onClick);
}

void CalendarDialogPattern::HandleClickEvent(const GestureEvent& info)
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    if (IsInEntryRegion(info.GetGlobalLocation())) {
        auto pattern = entryNode->GetPattern<CalendarPickerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info.GetGlobalLocation());
    }
}

void CalendarDialogPattern::InitOnTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->HandleEntryNodeTouchEvent(true, info.GetTouches().front().GetGlobalLocation());
            if (!pattern->isFocused_) {
                return;
            }
            pattern->isFocused_ = false;
            pattern->isCalendarFirstFocused_ = false;
            pattern->ClearCalendarFocusedState();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            pattern->HandleEntryNodeTouchEvent(false, info.GetTouches().front().GetGlobalLocation());
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void CalendarDialogPattern::InitOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (event.IsNumberKey() && event.action == KeyAction::DOWN) {
            auto entryNode = pattern->entryNode_.Upgrade();
            CHECK_NULL_RETURN(entryNode, false);
            auto entryPattern = entryNode->GetPattern<CalendarPickerPattern>();
            CHECK_NULL_RETURN(entryPattern, false);
            entryPattern->HandleNumberKeyEvent(event);
        }
        if (pattern->isFocused_ && !pattern->isCalendarFirstFocused_ &&
            pattern->focusAreaID_ == CALENDAR_NODE_INDEX) {
            pattern->isCalendarFirstFocused_ = true;
            pattern->FocusedLastFocusedDay();
            return true;
        }
        if (pattern->isFocused_ && event.action == KeyAction::DOWN) {
            return pattern->HandleKeyEvent(event);
        }
        if (!pattern->isFocused_ && !pattern->hasTabKeyDown_ && event.action == KeyAction::DOWN) {
            pattern->OnEnterKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isFocused_ = false;
        pattern->isCalendarFirstFocused_ = false;
        pattern->ClearCalendarFocusedState();
    };
    focusHub->SetOnBlurInternal(std::move(blurTask));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void CalendarDialogPattern::InitEntryChangeEvent()
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto eventHub = entryNode->GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto callback = [weak = WeakClaim(this)](const std::string& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleEntryChange(info);
    };
    eventHub->SetInputChangeEvent(std::move(callback));
    auto layoutChangeEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleEntryLayoutChange();
    };
    eventHub->SetLayoutChangeEvent(layoutChangeEvent);
}

bool CalendarDialogPattern::HandleKeyEvent(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    if (event.code == KeyCode::KEY_TAB) {
        return HandleTabKeyEvent(event);
    }
    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        return HandleCalendarNodeKeyEvent(event);
    }
    if (focusAreaID_ != TITLE_NODE_INDEX && focusAreaID_ != OPTIONS_NODE_INDEX) {
        return false;
    }

    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN(calendarNode, false);
    auto textDirection = calendarNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    switch (event.code) {
        case KeyCode::KEY_DPAD_LEFT: {
            if (textDirection == TextDirection::RTL) {
                if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX - 1) ||
                    (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX - 1)) {
                    focusAreaChildID_++;
                }
                focusAreaChildID_++;
                auto childSize = static_cast<int32_t>(host->GetChildAtIndex(focusAreaID_)->GetChildren().size());
                if (focusAreaChildID_ > childSize - 1) {
                    focusAreaChildID_ = childSize - 1;
                }
            } else {
                if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX + 1) ||
                    (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX + 1)) {
                    focusAreaChildID_--;
                }
                focusAreaChildID_--;
                if (focusAreaChildID_ < 0) {
                    focusAreaChildID_ = 0;
                }
            }

            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            if (textDirection == TextDirection::RTL) {
                if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX + 1) ||
                    (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX + 1)) {
                    focusAreaChildID_--;
                }

                focusAreaChildID_--;
                if (focusAreaChildID_ < 0) {
                    focusAreaChildID_ = 0;
                }
            } else {
                if ((focusAreaID_ == TITLE_NODE_INDEX && focusAreaChildID_ == TITLE_TEXT_NODE_INDEX - 1) ||
                    (focusAreaID_ == OPTIONS_NODE_INDEX && focusAreaChildID_ == OPTIONS_DIVIDER_NODE_INDEX - 1)) {
                    focusAreaChildID_++;
                }

                focusAreaChildID_++;
                auto childSize = static_cast<int32_t>(host->GetChildAtIndex(focusAreaID_)->GetChildren().size());
                if (focusAreaChildID_ > childSize - 1) {
                    focusAreaChildID_ = childSize - 1;
                }
            }

            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_MOVE_HOME: {
            focusAreaChildID_ = 0;
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_MOVE_END: {
            focusAreaChildID_ = static_cast<int32_t>(host->GetChildAtIndex(focusAreaID_)->GetChildren().size()) - 1;
            PaintFocusState();
            ChangeEntryState();
            return true;
        }
        case KeyCode::KEY_SPACE:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_ENTER: {
            return ActClick(focusAreaID_, focusAreaChildID_);
        }
        default:
            break;
    }
    return false;
}

bool CalendarDialogPattern::HandleCalendarNodeKeyEvent(const KeyEvent& event)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_RETURN(swiperController, false);
    swiperController->FinishAnimation();
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_RETURN(calendarPattern, false);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN(calendarNode, false);
    auto textDirection = calendarNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    int32_t focusedDayIndex = GetIndexByFocusedDay();

    switch (event.code) {
        case KeyCode::KEY_DPAD_LEFT: {
            if (textDirection == TextDirection::RTL) {
                focusedDayIndex++;
            } else {
                focusedDayIndex--;
            }

            PaintMonthFocusState(focusedDayIndex);
            return true;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            if (textDirection == TextDirection::RTL) {
                focusedDayIndex--;
            } else {
                focusedDayIndex++;
            }

            PaintMonthFocusState(focusedDayIndex);
            return true;
        }
        case KeyCode::KEY_DPAD_UP: {
            focusedDayIndex -= WEEK_DAYS;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_DPAD_DOWN: {
            focusedDayIndex += WEEK_DAYS;
            if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
                focusedDay_ = currentMonthData.days[focusedDayIndex];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_MOVE_HOME: {
            auto it = std::find_if(currentMonthData.days.begin(), currentMonthData.days.end(),
                [currentMonthData](const CalendarDay& day) {
                    return day.month.year == currentMonthData.year && day.month.month == currentMonthData.month;
                });
            if (it != currentMonthData.days.end()) {
                focusedDay_ = currentMonthData.days[it->index];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_MOVE_END: {
            auto it = std::find_if(currentMonthData.days.rbegin(), currentMonthData.days.rend(),
                [currentMonthData](const CalendarDay& day) {
                    return day.month.year == currentMonthData.year && day.month.month == currentMonthData.month;
                });
            if (it != currentMonthData.days.rend()) {
                focusedDay_ = currentMonthData.days[it->index];
                PaintCurrentMonthFocusState();
                return true;
            }
            break;
        }
        case KeyCode::KEY_SPACE:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_ENTER: {
            PickerDate selectedDay(focusedDay_.month.year, focusedDay_.month.month, focusedDay_.day);
            calendarPattern->SetSelectedDay(selectedDay);
            auto calendarFrameNode = GetCalendarFrameNode();
            CHECK_NULL_RETURN(calendarFrameNode, false);
            calendarFrameNode->MarkModifyDone();
            FireChangeByKeyEvent(selectedDay);
            return true;
        }
        default:
            break;
    }
    return false;
}

void CalendarDialogPattern::PaintMonthFocusState(int32_t focusedDayIndex)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    if (IsIndexInCurrentMonth(focusedDayIndex, currentMonthData)) {
        focusedDay_ = currentMonthData.days[focusedDayIndex];
        PaintCurrentMonthFocusState();
    } else {
        PaintNonCurrentMonthFocusState(focusedDayIndex);
    }
}

bool CalendarDialogPattern::IsIndexInCurrentMonth(int32_t focusedDayIndex, const ObtainedMonth& currentMonthData)
{
    return focusedDayIndex >= 0 && focusedDayIndex < static_cast<int32_t>(currentMonthData.days.size()) &&
           currentMonthData.days[focusedDayIndex].month.year == currentMonthData.year &&
           currentMonthData.days[focusedDayIndex].month.month == currentMonthData.month;
}

bool CalendarDialogPattern::HandleTabKeyEvent(const KeyEvent& event)
{
    hasTabKeyDown_ = true;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto childSize = static_cast<int32_t>(host->GetChildren().size()) - 1;
    if (event.IsShiftWith(KeyCode::KEY_TAB)) {
        focusAreaIDWithoutWeek_ = (focusAreaIDWithoutWeek_ + childSize - 1) % childSize;
    } else {
        focusAreaIDWithoutWeek_ = (focusAreaIDWithoutWeek_ + 1) % childSize;
    }

    if (focusAreaIDWithoutWeek_ == TITLE_NODE_INDEX) {
        focusAreaID_ = focusAreaIDWithoutWeek_;
    } else {
        focusAreaID_ = focusAreaIDWithoutWeek_ + 1;
    }

    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        isCalendarFirstFocused_ = true;
        FocusedLastFocusedDay();
    } else {
        ClearCalendarFocusedState();
        focusAreaChildID_ = 0;
        PaintFocusState();
    }
    ChangeEntryState();
    return true;
}

void CalendarDialogPattern::FocusedLastFocusedDay()
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    if (focusedDay_.day < 0) {
        PickerDate selectedDay = calendarPattern->GetSelectedDay();
        focusedDay_.month.year = static_cast<int32_t>(selectedDay.GetYear());
        focusedDay_.month.month = static_cast<int32_t>(selectedDay.GetMonth());
        focusedDay_.day = static_cast<int32_t>(selectedDay.GetDay());
    }

    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    if (currentMonthData.year == focusedDay_.month.year && currentMonthData.month == focusedDay_.month.month) {
        PaintCurrentMonthFocusState();
        return;
    }
    ObtainedMonth monthData;
    GetCalendarMonthData(focusedDay_.month.year, focusedDay_.month.month, monthData);
    auto isPrev = currentMonthData.year > focusedDay_.month.year ||
        (currentMonthData.year == focusedDay_.month.year && currentMonthData.month > focusedDay_.month.month);
    auto it = std::find_if(monthData.days.begin(), monthData.days.end(),
        [this](CalendarDay day) {
            return day.day == focusedDay_.day && day.month == focusedDay_.month;
        });
    if (it != monthData.days.end()) {
        focusedDay_ = *it;
        it->isKeyFocused = true;
        calendarPattern->SetDialogClickEventState(true);
        UpdateSwiperNode(monthData, isPrev);
    }
}

void CalendarDialogPattern::UpdateSwiperNode(const ObtainedMonth& monthData, bool isPrev)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    int32_t currentIndex = swiperPattern->GetCurrentIndex();
    int32_t targetIndex = (currentIndex + SWIPER_CHILDREN_SIZE + (isPrev ? -1 : 1)) % SWIPER_CHILDREN_SIZE;

    auto swiperNode = GetSwiperFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto monthFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(targetIndex));
    CHECK_NULL_VOID(monthFrameNode);
    auto monthPattern = monthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(monthPattern);

    if (isPrev) {
        monthPattern->SetMonthData(monthData, MonthState::PRE_MONTH);
        calendarPattern->SetPreMonthData(monthData);
    } else {
        monthPattern->SetMonthData(monthData, MonthState::NEXT_MONTH);
        calendarPattern->SetNextMonthData(monthData);
    }

    monthFrameNode->MarkModifyDone();
    monthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (isPrev) {
        swiperPattern->ShowPrevious();
    } else {
        swiperPattern->ShowNext();
    }
}

void CalendarDialogPattern::UpdateSwiperNodeFocusedDay(const CalendarDay& focusedDay, bool isPrev)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth targetMonthData = isPrev ? calendarPattern->GetPreMonthData() : calendarPattern->GetNextMonthData();
    if (focusedDay.month.year != targetMonthData.year || focusedDay.month.month != targetMonthData.month) {
        return;
    }

    auto it = std::find_if(targetMonthData.days.begin(), targetMonthData.days.end(),
        [focusedDay](CalendarDay day) {
            return day.day == focusedDay.day && day.month == focusedDay.month;
        });
    if (it != targetMonthData.days.end()) {
        focusedDay_ = *it;
        it->isKeyFocused = true;
        auto swiperPattern = GetSwiperPattern();
        CHECK_NULL_VOID(swiperPattern);
        if (isPrev) {
            calendarPattern->SetPreMonthData(targetMonthData);
            swiperPattern->ShowPrevious();
        } else {
            calendarPattern->SetNextMonthData(targetMonthData);
            swiperPattern->ShowNext();
        }
    }
}

bool CalendarDialogPattern::ActClick(int32_t focusAreaID, int32_t focusAreaChildID)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusArea = host->GetChildAtIndex(focusAreaID);
    CHECK_NULL_RETURN(focusArea, false);
    auto child = focusArea->GetChildAtIndex(focusAreaChildID);
    CHECK_NULL_RETURN(child, false);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
    CHECK_NULL_RETURN(childFrameNode, false);
    auto gestureEventHub = childFrameNode->GetOrCreateGestureEventHub();
    return gestureEventHub->ActClick();
}

void CalendarDialogPattern::PaintCurrentMonthFocusState()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarFrameNode);
    auto calendarPattern = calendarFrameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    for (auto& day : currentMonthData.days) {
        day.isKeyFocused = currentMonthData.year == focusedDay_.month.year &&
            currentMonthData.month == focusedDay_.month.month &&
            day.month == focusedDay_.month && day.day == focusedDay_.day;
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);
    calendarFrameNode->MarkModifyDone();
}

void CalendarDialogPattern::PaintNonCurrentMonthFocusState(int32_t focusedDayIndex)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);

    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    ObtainedMonth preMonthData = calendarPattern->GetPreMonthData();
    ObtainedMonth nextMonthData = calendarPattern->GetNextMonthData();

    for (auto& day : currentMonthData.days) {
        day.isKeyFocused = false;
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);
    calendarPattern->SetDialogClickEventState(true);
    if (focusedDayIndex == -1) {
        focusedDay_ = preMonthData.days[preMonthData.days.size() ? preMonthData.days.size() - 1 : 0];
        preMonthData.days[preMonthData.days.size() ? preMonthData.days.size() - 1 : 0].isKeyFocused = true;
        calendarPattern->SetPreMonthData(preMonthData);
        swiperPattern->ShowPrevious();
        return;
    } else if (focusedDayIndex == static_cast<int32_t>(currentMonthData.days.size())) {
        focusedDay_ = nextMonthData.days[0];
        nextMonthData.days[0].isKeyFocused = true;
        calendarPattern->SetNextMonthData(nextMonthData);
        swiperPattern->ShowNext();
        return;
    }
    UpdateNonCurrentMonthFocusedDay(focusedDayIndex);
}

void CalendarDialogPattern::UpdateNonCurrentMonthFocusedDay(int32_t focusedDayIndex)
{
    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);

    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    ObtainedMonth preMonthData = calendarPattern->GetPreMonthData();
    ObtainedMonth nextMonthData = calendarPattern->GetNextMonthData();

    if (focusedDayIndex < 0 || focusedDayIndex >= static_cast<int32_t>(currentMonthData.days.size())) {
        return;
    }

    CalendarDay focusedDay = currentMonthData.days[focusedDayIndex];
    if (focusedDay.month.year == preMonthData.year && focusedDay.month.month == preMonthData.month) {
        return UpdateSwiperNodeFocusedDay(focusedDay, true);
    }

    if (focusedDay.month.year == nextMonthData.year && focusedDay.month.month == nextMonthData.month) {
        return UpdateSwiperNodeFocusedDay(focusedDay, false);
    }
}

void CalendarDialogPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CalendarDialogPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    isFocused_ = true;
    if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        paintRect.SetRect(RectF());
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusArea = DynamicCast<FrameNode>(host->GetChildAtIndex(focusAreaID_));
    CHECK_NULL_VOID(focusArea);
    auto focusGeometryNode = focusArea->GetGeometryNode();
    CHECK_NULL_VOID(focusGeometryNode);
    auto focusAreaOffset = focusGeometryNode->GetFrameOffset();
    auto child = DynamicCast<FrameNode>(focusArea->GetChildAtIndex(focusAreaChildID_));
    CHECK_NULL_VOID(child);
    auto childOffset = child->GetGeometryNode()->GetFrameOffset() + focusAreaOffset;
    auto childSize = child->GetGeometryNode()->GetFrameSize();
    paintRect.SetRect(RectF(childOffset, childSize));
    auto renderContext = child->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto radius = renderContext->GetBorderRadius();
    if (radius.has_value()) {
        if (radius->radiusTopLeft.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
                static_cast<float>(radius->radiusTopLeft->ConvertToPx()),
                static_cast<float>(radius->radiusTopLeft->ConvertToPx()));
        }
        if (radius->radiusTopRight.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
                static_cast<float>(radius->radiusTopRight->ConvertToPx()),
                static_cast<float>(radius->radiusTopRight->ConvertToPx()));
        }
        if (radius->radiusBottomLeft.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
                static_cast<float>(radius->radiusBottomLeft->ConvertToPx()),
                static_cast<float>(radius->radiusBottomLeft->ConvertToPx()));
        }
        if (radius->radiusBottomRight.has_value()) {
            paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
                static_cast<float>(radius->radiusBottomRight->ConvertToPx()),
                static_cast<float>(radius->radiusBottomRight->ConvertToPx()));
        }
    }
    ChangeEntryState();
}

void CalendarDialogPattern::ClearCalendarFocusedState()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarFrameNode);
    auto calendarPattern = calendarFrameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentMonthData = calendarPattern->GetCurrentMonthData();
    for (auto& day : currentMonthData.days) {
        day.isKeyFocused = false;
    }
    calendarPattern->SetCurrentMonthData(currentMonthData);
    calendarFrameNode->MarkModifyDone();
}

void CalendarDialogPattern::ChangeEntryState()
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto enrtyPattern = entryNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(enrtyPattern);
    if (focusAreaID_ == TITLE_NODE_INDEX) {
        if (focusAreaChildID_ == TITLE_LAST_YEAR_BUTTON_NODE_INDEX ||
            focusAreaChildID_ == TITLE_NEXT_YEAR_BUTTON_NODE_INDEX) {
            enrtyPattern->SetSelectedType(CalendarPickerSelectedType::YEAR);
        } else if (focusAreaChildID_ == TITLE_LAST_MONTH_BUTTON_NODE_INDEX ||
                   focusAreaChildID_ == TITLE_NEXT_MONTH_BUTTON_NODE_INDEX) {
            enrtyPattern->SetSelectedType(CalendarPickerSelectedType::MONTH);
        }
    } else if (focusAreaID_ == CALENDAR_NODE_INDEX) {
        enrtyPattern->SetSelectedType(CalendarPickerSelectedType::DAY);
    }
}

void CalendarDialogPattern::InitTitleArrowsEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto title = host->GetChildAtIndex(TITLE_NODE_INDEX);
    CHECK_NULL_VOID(title);
    for (const auto& child : title->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() == V2::TEXT_ETS_TAG) {
            continue;
        }
        int32_t childIndex = title->GetChildIndex(child);
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(buttonNode);
        auto event = [childIndex, wp = WeakClaim(this)](GestureEvent& /* info */) {
            auto pattern = wp.Upgrade();
            if (pattern) {
                pattern->HandleTitleArrowsClickEvent(childIndex);
            }
        };

        auto buttonNodeId = buttonNode->GetId();
        if (clickEvents_.find(buttonNodeId) == clickEvents_.end()) {
            auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(event));
            clickEvents_[buttonNodeId] = clickEvent;
            gestureHub->AddClickEvent(clickEvent);
        }
    }
}

void CalendarDialogPattern::HandleTitleArrowsClickEvent(int32_t nodeIndex)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->GetSwiperController()->FinishAnimation();

    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    ObtainedMonth currentObtainedMonth = calendarPattern->GetCurrentMonthData();
    CalendarMonth currentMonth { .year = currentObtainedMonth.year, .month = currentObtainedMonth.month };

    calendarPattern->SetDialogClickEventState(true);
    switch (nodeIndex) {
        case TITLE_LAST_YEAR_BUTTON_NODE_INDEX: {
            currentMonth.year = currentMonth.year == MIN_YEAR ? MAX_YEAR : currentMonth.year - 1;
            ObtainedMonth monthData;
            GetCalendarMonthData(currentMonth.year, currentMonth.month, monthData);
            UpdateSwiperNode(monthData, true);
            break;
        }
        case TITLE_LAST_MONTH_BUTTON_NODE_INDEX: {
            swiperPattern->ShowPrevious();
            break;
        }
        case TITLE_NEXT_MONTH_BUTTON_NODE_INDEX: {
            swiperPattern->ShowNext();
            break;
        }
        case TITLE_NEXT_YEAR_BUTTON_NODE_INDEX: {
            currentMonth.year = currentMonth.year == MAX_YEAR ? MIN_YEAR : currentMonth.year + 1;
            ObtainedMonth monthData;
            GetCalendarMonthData(currentMonth.year, currentMonth.month, monthData);
            UpdateSwiperNode(monthData, false);
            break;
        }
        default:
            break;
    }
}

void CalendarDialogPattern::GetCalendarMonthData(int32_t year, int32_t month, ObtainedMonth& calendarMonthData)
{
    calendarMonthData.year = year;
    calendarMonthData.month = month;
    calendarMonthData.firstDayIndex = 0;

    CalendarMonth currentMonth { .year = year, .month = month };

    int32_t currentMonthMaxDay = static_cast<int32_t>(PickerDate::GetMaxDay(year, month));
    int32_t preMonthMaxDay =
        static_cast<int32_t>(PickerDate::GetMaxDay(GetLastMonth(currentMonth).year, GetLastMonth(currentMonth).month));
    int32_t preMonthDaysCount = (Date::CalculateWeekDay(year, month, 1) + 1) % WEEK_DAYS;
    int32_t nextMonthDaysCount = 6 - ((Date::CalculateWeekDay(year, month, currentMonthMaxDay) + 1) % WEEK_DAYS);

    int32_t index = 0;
    for (int32_t i = 0; i < preMonthDaysCount; i++, index++) {
        calendarMonthData.days.emplace_back(CalendarDay { .index = index,
            .day = preMonthMaxDay - preMonthDaysCount + index + 1,
            .month = GetLastMonth(currentMonth) });
    }

    for (int32_t i = 0; i < currentMonthMaxDay; i++, index++) {
        calendarMonthData.days.emplace_back(CalendarDay { .index = index, .day = i + 1, .month = currentMonth });
    }

    for (int32_t i = 0; i < nextMonthDaysCount; i++, index++) {
        calendarMonthData.days.emplace_back(
            CalendarDay { .index = index, .day = i + 1, .month = GetNextMonth(currentMonth) });
    }

    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    PickerDate selectedDay = calendarPattern->GetSelectedDay();
    for (size_t i = 0; i < calendarMonthData.days.size(); i++) {
        calendarMonthData.days[i].isKeyFocused = isFocused_
                                                     ? ((focusedDay_.month.year == calendarMonthData.year) &&
                                                           (focusedDay_.month.month == calendarMonthData.month) &&
                                                           (focusedDay_.month == calendarMonthData.days[i].month) &&
                                                           (focusedDay_.day == calendarMonthData.days[i].day))
                                                     : false;
        calendarMonthData.days[i].isSelected =
            (selectedDay.GetYear() == static_cast<uint32_t>(calendarMonthData.year)) &&
            (selectedDay.GetMonth() == static_cast<uint32_t>(calendarMonthData.month)) &&
            (selectedDay.GetYear() == static_cast<uint32_t>(calendarMonthData.days[i].month.year)) &&
            (selectedDay.GetMonth() == static_cast<uint32_t>(calendarMonthData.days[i].month.month)) &&
            (selectedDay.GetDay() == static_cast<uint32_t>(calendarMonthData.days[i].day));
    }
}

void CalendarDialogPattern::AddHotZoneRect()
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto rect = entryNode->GetPaintRectWithTransform();
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(
        Dimension(rect.Width()), Dimension(rect.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(
        Dimension(rect.Left() - dialogOffset_.GetX()), Dimension(rect.Top() - dialogOffset_.GetY())));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    DimensionRect hotZoneRegionHost;
    hotZoneRegionHost.SetSize(DimensionSize(
        Dimension(geometryNode->GetFrameRect().Width()), Dimension(geometryNode->GetFrameRect().Height())));

    host->AddHotZoneRect(hotZoneRegion);
    host->AddHotZoneRect(hotZoneRegionHost);
}

void CalendarDialogPattern::FireChangeByKeyEvent(PickerDate& selectedDay)
{
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(calendarNode->GetFirstChild());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto monthNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperPattern->GetCurrentIndex()));
    CHECK_NULL_VOID(monthNode);
    auto eventHub = monthNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateSelectedChangeEvent(selectedDay.ToString(true));
}

CalendarMonth CalendarDialogPattern::GetNextMonth(const CalendarMonth& calendarMonth)
{
    CalendarMonth nextMonth = calendarMonth;
    if (calendarMonth.month + 1 > MAX_MONTH) {
        nextMonth.month = 1;
        nextMonth.year = nextMonth.year == MAX_YEAR ? MIN_YEAR : nextMonth.year + 1;
    } else {
        ++nextMonth.month;
    }
    return nextMonth;
}

CalendarMonth CalendarDialogPattern::GetLastMonth(const CalendarMonth& calendarMonth)
{
    CalendarMonth lastMonth = calendarMonth;
    if (calendarMonth.month - 1 <= 0) {
        lastMonth.month = MAX_MONTH;
        lastMonth.year = lastMonth.year == MIN_YEAR ? MAX_YEAR : lastMonth.year - 1;
    } else {
        --lastMonth.month;
    }
    return lastMonth;
}

int32_t CalendarDialogPattern::GetIndexByFocusedDay()
{
    ObtainedMonth monthData;
    GetCalendarMonthData(focusedDay_.month.year, focusedDay_.month.month, monthData);
    auto it = std::find_if(monthData.days.begin(), monthData.days.end(),
        [this](CalendarDay day) {
            return day.day == focusedDay_.day && day.month == focusedDay_.month;
        });
    if (it != monthData.days.end()) {
        return it->index;
    }
    return -1;
}

void CalendarDialogPattern::HandleEntryLayoutChange()
{
    auto entryNode = entryNode_.Upgrade();
    CHECK_NULL_VOID(entryNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto wrapperNode = host->GetParent();
    CHECK_NULL_VOID(wrapperNode);
    auto dialogNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetParent());
    CHECK_NULL_VOID(dialogNode);
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->AddAfterRenderTask([weak = WeakClaim(this), entryNode, dialogNode]() {
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            auto pattern = entryNode->GetPattern<CalendarPickerPattern>();
            CHECK_NULL_VOID(pattern);
            node->dialogOffset_ = pattern->CalculateDialogOffset();
            auto dialogLayoutProp = dialogNode->GetLayoutProperty<DialogLayoutProperty>();
            CHECK_NULL_VOID(dialogLayoutProp);
            dialogLayoutProp->UpdateDialogOffset(DimensionOffset(node->dialogOffset_));
            dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        });
    }
    isFirstAddhotZoneRect_ = false;
}

void CalendarDialogPattern::HandleEntryChange(const std::string& info)
{
    auto calendarNode = GetCalendarFrameNode();
    CHECK_NULL_VOID(calendarNode);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);

    auto calendarJson = JsonUtil::ParseJsonString(calendarPattern->GetSelectDate());
    auto entryJson = JsonUtil::ParseJsonString(info);
    auto entryYear = entryJson->GetUInt("year");
    auto entryMonth = entryJson->GetUInt("month");
    auto entryDay = entryJson->GetUInt("day");

    PickerDate selectedDay = PickerDate(entryYear, entryMonth, entryDay);
    if (entryYear != calendarJson->GetUInt("year") || entryMonth != calendarJson->GetUInt("month")) {
        CalendarData calendarData;
        CalendarMonth calendarMonth { .year = entryYear, .month = entryMonth };

        GetCalendarMonthData(entryYear, entryMonth, calendarData.currentData);
        calendarPattern->SetCurrentMonthData(calendarData.currentData);
        GetCalendarMonthData(
            GetLastMonth(calendarMonth).year, GetLastMonth(calendarMonth).month, calendarData.preData);
        calendarPattern->SetPreMonthData(calendarData.preData);
        GetCalendarMonthData(
            GetNextMonth(calendarMonth).year, GetNextMonth(calendarMonth).month, calendarData.nextData);
        calendarPattern->SetNextMonthData(calendarData.nextData);
    }

    calendarPattern->SetSelectedDay(selectedDay);
    calendarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    calendarNode->MarkModifyDone();
}

RefPtr<FrameNode> CalendarDialogPattern::GetCalendarFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto scrollNode = host->GetChildAtIndex(CALENDAR_NODE_INDEX);
    CHECK_NULL_RETURN(scrollNode, nullptr);
    auto calendarNode = scrollNode->GetChildren().front();
    return AceType::DynamicCast<FrameNode>(calendarNode);
}

RefPtr<CalendarPattern> CalendarDialogPattern::GetCalendarPattern()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN(calendarFrameNode, nullptr);
    return calendarFrameNode->GetPattern<CalendarPattern>();
}

RefPtr<FrameNode> CalendarDialogPattern::GetSwiperFrameNode()
{
    auto calendarFrameNode = GetCalendarFrameNode();
    CHECK_NULL_RETURN(calendarFrameNode, nullptr);
    if (calendarFrameNode->GetChildren().empty()) {
        return nullptr;
    }
    auto swiperNode = calendarFrameNode->GetChildren().front();
    CHECK_NULL_RETURN(swiperNode, nullptr);
    return AceType::DynamicCast<FrameNode>(swiperNode);
}

RefPtr<SwiperPattern> CalendarDialogPattern::GetSwiperPattern()
{
    auto swiperFrameNode = GetSwiperFrameNode();
    CHECK_NULL_RETURN(swiperFrameNode, nullptr);
    return swiperFrameNode->GetPattern<SwiperPattern>();
}

void CalendarDialogPattern::OnEnterKeyEvent(const KeyEvent& event)
{
    bool checkKeyCode = (event.code == KeyCode::KEY_ENTER || event.code == KeyCode::KEY_NUMPAD_ENTER ||
        event.code == KeyCode::KEY_SPACE);
    if (!checkKeyCode) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto options = host->GetChildAtIndex(OPTIONS_NODE_INDEX);
    CHECK_NULL_VOID(options);

    for (const auto& child : options->GetChildren()) {
        CHECK_NULL_VOID(child);
        if (child->GetTag() != V2::BUTTON_ETS_TAG) {
            continue;
        }
        auto button = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(button);
        auto focusHub = button->GetOrCreateFocusHub();
        if (focusHub && focusHub->IsDefaultFocus()) {
            auto gesture = button->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gesture);
            gesture->ActClick();
        }
    }
}

void CalendarDialogPattern::OnLanguageConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollNode = host->GetChildAtIndex(CALENDAR_NODE_INDEX);
    CHECK_NULL_VOID(scrollNode);
    auto calendarNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildren().front());
    CHECK_NULL_VOID(calendarNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(calendarNode->GetFirstChild());
    CHECK_NULL_VOID(swiperNode);

    for (auto&& child : swiperNode->GetChildren()) {
        auto monthFrameNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(monthFrameNode);
        auto pipelineContext = GetContext();
        CHECK_NULL_VOID(pipelineContext);
        RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
        CHECK_NULL_VOID(theme);

        auto fontSizeScale = pipelineContext->GetFontScale();
        auto fontSize = theme->GetCalendarDayFontSize();
        if (AceApplicationInfo::GetInstance().GetLanguage() != "zh") {
            ACE_UPDATE_NODE_PAINT_PROPERTY(
                CalendarPaintProperty, WeekFontSize, theme->GetCalendarSmallDayFontSize(), monthFrameNode);
        } else {
            if (fontSizeScale < theme->GetCalendarPickerLargeScale() || CalendarDialogView::CheckOrientationChange()) {
                ACE_UPDATE_NODE_PAINT_PROPERTY(CalendarPaintProperty, WeekFontSize, fontSize, monthFrameNode);
            } else {
                fontSizeScale = fontSizeScale > theme->GetCalendarPickerLargerScale()
                                    ? theme->GetCalendarPickerLargerScale()
                                    : fontSizeScale;
                ACE_UPDATE_NODE_PAINT_PROPERTY(
                    CalendarPaintProperty, WeekFontSize, fontSize * fontSizeScale, monthFrameNode);
            }
        }
        monthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void CalendarDialogPattern::InitSurfaceChangedCallback()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipelineContext->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void CalendarDialogPattern::HandleSurfaceChanged(
    int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    if (newWidth == prevWidth && newHeight == prevHeight) {
        return;
    }

    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    UpdateCaretInfoToController();
}

void CalendarDialogPattern::UpdateCaretInfoToController()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto titleNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(TITLE_NODE_INDEX));
    CHECK_NULL_VOID(titleNode);
    auto layoutProps = titleNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    auto scrollNode = host->GetChildAtIndex(CALENDAR_NODE_INDEX);
    CHECK_NULL_VOID(calendarTheme);
    auto calendarNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildren().front());
    CHECK_NULL_VOID(calendarNode);
    auto calendarLayoutProperty = calendarNode->GetLayoutProperty();
    CHECK_NULL_VOID(calendarLayoutProperty);
    CalendarDialogView::UpdateIdealSize(calendarTheme, layoutProps, calendarLayoutProperty, calendarNode);

    auto swiperNode = AceType::DynamicCast<FrameNode>(calendarNode->GetFirstChild());
    CHECK_NULL_VOID(swiperNode);
    for (auto&& child : swiperNode->GetChildren()) {
        auto monthFrameNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(monthFrameNode);
        auto monthPattern = monthFrameNode->GetPattern<CalendarMonthPattern>();
        CHECK_NULL_VOID(monthPattern);
        CalendarDialogView::UpdatePaintProperties(monthFrameNode, currentSettingData_);
        monthPattern->UpdateColRowSpace();
        monthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    if (host->GetTotalChildCount() > OPTIONS_NODE_INDEX) {
        auto contentRow = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(OPTIONS_NODE_INDEX));
        CHECK_NULL_VOID(contentRow);
        size_t buttonIndex = OPTION_CANCEL_BUTTON_INDEX;
        for (auto&& child : contentRow->GetChildren()) {
            auto buttonNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(buttonNode);
            CalendarDialogView::UpdateButtons(buttonNode, buttonIndex, currentButtonInfos_);
            buttonIndex++;
        }
    }

    auto calendarPattern = GetCalendarPattern();
    CHECK_NULL_VOID(calendarPattern);
    calendarPattern->UpdateTitleNode();

    auto wrapperNode = host->GetParent();
    CHECK_NULL_VOID(wrapperNode);
    auto dialogNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetParent());
    CHECK_NULL_VOID(dialogNode);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    CalendarDialogView::SetPreviousOrientation();
}

void CalendarDialogPattern::OnColorConfigurationUpdate()
{
    auto titleNode = titleNode_.Upgrade();
    CHECK_NULL_VOID(titleNode);
    auto pipelineContext = titleNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    
    textLayoutProperty->UpdateTextColor(theme->GetCalendarTitleFontColor());
}
} // namespace OHOS::Ace::NG

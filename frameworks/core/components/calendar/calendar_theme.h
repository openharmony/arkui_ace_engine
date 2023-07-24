/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {

constexpr Color DEFAULT_DAY_COLOR = Color(0xE1181819);
constexpr Color DEFAULT_NON_CURRENT_MONTH_DAY_COLOR = Color(0x4B181819);
constexpr Color DEFAULT_WEEKEND_DAY_COLOR = Color(0x7D181819);
constexpr Color DEFAULT_WEEKEND_LUNAR_COLOR = Color(0x7D181819);
constexpr Color DEFAULT_NON_CURRENT_MONTH_LUNAR_COLOR = Color(0x75181819);
constexpr Color DEFAULT_LUNAR_COLOR = Color(0x96181819);
constexpr Color DEFAULT_CALENDAR_WEEK_COLOR = Color(0xffa0a1a5);
constexpr Color DEFAULT_CALENDAR_DAY_COLOR = Color(0xffeaebed);
constexpr Color DEFAULT_CALENDAR_LUNAR_COLOR = Color(0xffa0a1a5);
constexpr Color DEFAULT_CALENDAR_WEEKEND_DAY_COLOR = Color(0xff808080);
constexpr Color DEFAULT_CALENDAR_WEEKEND_LUNAR_COLOR = Color(0xff808080);
constexpr Color DEFAULT_CALENDAR_TODAY_DAY_FOCUS_COLOR = Color(0xffffffff);
constexpr Color DEFAULT_CALENDAR_TODAY_LUNAR_FOCUS_COLOR = Color(0xffffffff);
constexpr Color DEFAULT_CALENDAR_TODAY_DAY_UNFOCUS_COLOR = Color(0xff0a59f7);
constexpr Color DEFAULT_CALENDAR_TODAY_LUNAR_UNFOCUS_COLOR = Color(0xff0a59f7);
constexpr Color DEFAULT_CALENDAR_WORK_MARK_COLOR = Color(0xffe84026);
constexpr Color DEFAULT_CALENDAR_OFF_MARK_COLOR = Color(0xff0a59f7);
constexpr Color DEFAULT_CALENDAR_NONCURRENT_MONTH_WORK_MARK_COLOR = Color(0x33e84026);
constexpr Color DEFAULT_CALENDAR_NONCURRENT_MONTH_OFF_MARK_COLOR = Color(0x330a59f7);
constexpr Color DEFAULT_CALENDAR_NONCURRENT_MONTH_DAY_COLOR = Color(0xff555e6b);
constexpr Color DEFAULT_CALENDAR_NONCURRENT_MONTH_LUNAR_COLOR = Color(0xff555e6b);
constexpr Color DEFAULT_CALENDAR_FOCUS_AREA_BACKGROUND_COLOR = Color(0xff5ea1ff);
constexpr Color DEFAULT_CALENDAR_BLUR_AREA_BACKGROUND_COLOR = Color(0xffffffff);
} // namespace

struct CalendarThemeStructure {
    std::string dayFontWeight = "500";
    std::string lunarDayFontWeight = "500";
    std::string workStateFontWeight = "500";
    Color weekColor;
    Color dayColor;
    Color lunarColor;
    Color weekendDayColor;
    Color weekendLunarColor;
    Color todayColor;
    Color todayLunarColor;
    Color nonCurrentMonthDayColor;
    Color nonCurrentMonthLunarColor;
    Color workDayMarkColor;
    Color offDayMarkColor;
    Color nonCurrentMonthWorkDayMarkColor;
    Color nonCurrentMonthOffDayMarkColor;
    Color focusedDayColor;
    Color focusedLunarColor;
    Color focusedAreaBackgroundColor;
    Color blurAreaBackgroundColor;
    Color titleTextColor;
    Color touchColor;
    Color markLunarColor;
    Color clickEffectColor;
    Color simpleWorkTextColor;
    Color simpleOffTextColor;
    Dimension weekFontSize;
    Dimension dayFontSize;
    Dimension lunarDayFontSize;
    Dimension workDayMarkSize;
    Dimension offDayMarkSize;
    Dimension focusedAreaRadius;
    Dimension topPadding;
    Dimension workStateWidth;
    Dimension workStateHorizontalMovingDistance;
    Dimension workStateVerticalMovingDistance;
    Dimension colSpace;
    Dimension weekHeight;
    Dimension dayHeight;
    Dimension weekWidth;
    Dimension dayWidth;
    Dimension weekAndDayRowSpace;
    Dimension dailyFiveRowSpace;
    Dimension dailySixRowSpace;
    Dimension gregorianCalendarHeight;
    Dimension lunarHeight;
    Dimension arrowHeight;
    Dimension arrowWidth;
    Dimension buttonWidth;
    Dimension buttonHeight;
    Dimension titleFontSize;
    Dimension workStateOffset;
    Dimension dayYAxisOffset;
    Dimension lunarDayYAxisOffset;
    Dimension underscoreXAxisOffset;
    Dimension underscoreYAxisOffset;
    Dimension scheduleMarkerXAxisOffset;
    Dimension scheduleMarkerYAxisOffset;
    Dimension underscoreWidth;
    Dimension underscoreLength;
    Dimension scheduleMarkerRadius;
    Dimension touchCircleStrokeWidth;
    Dimension boundaryRowOffset;
    Dimension boundaryColOffset;
};

class CalendarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CalendarTheme, Theme);

public:
    ~CalendarTheme() override = default;
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<CalendarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<CalendarTheme> theme = AceType::Claim(new CalendarTheme());
            if (!themeConstants) {
                return theme;
            }
            theme = AceType::Claim(new CalendarTheme());
            theme->calendarTheme_.weekFontSize = themeConstants->GetDimension(THEME_CALENDAR_WEEK_FONT_SIZE);
            theme->calendarTheme_.dayFontSize = themeConstants->GetDimension(THEME_CALENDAR_DAY_FONT_SIZE);
            theme->calendarTheme_.lunarDayFontSize = themeConstants->GetDimension(THEME_CALENDAR_LUNAR_FONT_SIZE);
            theme->calendarTheme_.weekColor = themeConstants->GetColor(THEME_CALENDAR_WEEK_COLOR);
            theme->calendarTheme_.dayColor = themeConstants->GetColor(THEME_CALENDAR_DAY_COLOR);
            theme->calendarTheme_.lunarColor = themeConstants->GetColor(THEME_CALENDAR_LUNAR_COLOR);
            theme->calendarTheme_.weekendDayColor = themeConstants->GetColor(THEME_CALENDAR_WEEKEND_DAY_COLOR);
            theme->calendarTheme_.weekendLunarColor = themeConstants->GetColor(THEME_CALENDAR_WEEKEND_LUNAR_COLOR);
            theme->calendarTheme_.todayColor = themeConstants->GetColor(THEME_CALENDAR_TODAY_DAY_COLOR);
            theme->calendarTheme_.todayLunarColor = themeConstants->GetColor(THEME_CALENDAR_TODAY_LUNAR_COLOR);
            theme->calendarTheme_.nonCurrentMonthDayColor =
                themeConstants->GetColor(THEME_CALENDAR_NON_CURRENT_MONTH_DAY_COLOR);
            theme->calendarTheme_.nonCurrentMonthLunarColor =
                themeConstants->GetColor(THEME_CALENDAR_NON_CURRENT_MONTH_LUNAR_COLOR);
            theme->calendarTheme_.workDayMarkSize =
                themeConstants->GetDimension(THEME_CALENDAR_WORK_DAY_MARK_FONT_SIZE);
            theme->calendarTheme_.offDayMarkSize = themeConstants->GetDimension(THEME_CALENDAR_OFF_DAY_MARK_FONT_SIZE);
            theme->calendarTheme_.workDayMarkColor = themeConstants->GetColor(THEME_CALENDAR_WORK_DAY_MARK_COLOR);
            theme->calendarTheme_.offDayMarkColor = themeConstants->GetColor(THEME_CALENDAR_OFF_DAY_MARK_COLOR);
            theme->calendarTheme_.nonCurrentMonthWorkDayMarkColor =
                themeConstants->GetColor(THEME_CALENDAR_NOT_CURRENT_MONTH_WORK_DAY_MARK_COLOR);
            theme->calendarTheme_.nonCurrentMonthOffDayMarkColor =
                themeConstants->GetColor(THEME_CALENDAR_NOT_CURRENT_MONTH_OFF_DAY_MARK_COLOR);
            theme->calendarTheme_.focusedDayColor = themeConstants->GetColor(THEME_CALENDAR_FOCUSED_DAY_COLOR);
            theme->calendarTheme_.focusedLunarColor = themeConstants->GetColor(THEME_CALENDAR_FOCUSED_LUNAR_COLOR);
            theme->calendarTheme_.focusedAreaRadius = themeConstants->GetDimension(THEME_CALENDAR_FOCUSED_AREA_RADIUS);
            theme->calendarTheme_.focusedAreaBackgroundColor =
                themeConstants->GetColor(THEME_CALENDAR_FOCUSED_AREA_BACKGROUND_COLOR);
            theme->calendarTheme_.topPadding = themeConstants->GetDimension(THEME_CALENDAR_TOP_PADDING);
            theme->calendarTheme_.workStateWidth = themeConstants->GetDimension(THEME_CALENDAR_WORK_STATE_WIDTH);
            theme->calendarTheme_.workStateHorizontalMovingDistance =
                themeConstants->GetDimension(THEME_CALENDAR_WORK_STATE_HORIZONTAL_MOVING_DISTANCE);
            theme->calendarTheme_.workStateVerticalMovingDistance =
                themeConstants->GetDimension(THEME_CALENDAR_WORK_STATE_VERTICAL_MOVING_DISTANCE);
            theme->calendarTheme_.colSpace = themeConstants->GetDimension(THEME_CALENDAR_COL_SPACE);
            theme->calendarTheme_.weekHeight = themeConstants->GetDimension(THEME_CALENDAR_WEEK_HEIGHT);
            theme->calendarTheme_.dayHeight = themeConstants->GetDimension(THEME_CALENDAR_DAY_HEIGHT);
            theme->calendarTheme_.weekWidth = themeConstants->GetDimension(THEME_CALENDAR_WEEK_WIDTH);
            theme->calendarTheme_.dayWidth = themeConstants->GetDimension(THEME_CALENDAR_DAY_WIDTH);
            theme->calendarTheme_.weekAndDayRowSpace =
                themeConstants->GetDimension(THEME_CALENDAR_WEEK_AND_DAY_ROW_SPACE);
            theme->calendarTheme_.dailyFiveRowSpace = themeConstants->GetDimension(THEME_CALENDAR_DAILY_FIVE_ROW_SPACE);
            theme->calendarTheme_.dailySixRowSpace = themeConstants->GetDimension(THEME_CALENDAR_DAILY_SIX_ROW_SPACE);
            theme->calendarTheme_.gregorianCalendarHeight =
                themeConstants->GetDimension(THEME_CALENDAR_GREGORIAN_CALENDAR_HEIGHT);
            theme->calendarTheme_.blurAreaBackgroundColor =
                themeConstants->GetColor(THEME_CALENDAR_BLUR_AREA_BACKGROUND_COLOR);
            theme->calendarTheme_.dayFontWeight = themeConstants->GetString(THEME_CALENDAR_DAY_FONT_WIGHT);
            theme->calendarTheme_.lunarDayFontWeight = themeConstants->GetString(THEME_CALENDAR_LUNAR_DAY_FONT_WIGHT);
            theme->calendarTheme_.workStateFontWeight = themeConstants->GetString(THEME_CALENDAR_WORK_STATE_FONT_WIGHT);
            theme->calendarTheme_.workStateOffset =
                themeConstants->GetDimension(THEME_CALENDAR_WORK_STATE_CENTER_ADJUSTMENT);
            theme->calendarTheme_.dayYAxisOffset = themeConstants->GetDimension(THEME_CALENDAR_DAY_YAXIS_OFFSET);
            theme->calendarTheme_.lunarDayYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_LUNAR_DAY_YAXIS_OFFSET);
            theme->calendarTheme_.underscoreXAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_XAXIS_OFFSET);
            theme->calendarTheme_.underscoreYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_YAXIS_OFFSET);
            theme->calendarTheme_.scheduleMarkerXAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_XAXIS_OFFSET);
            theme->calendarTheme_.scheduleMarkerYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_YAXIS_OFFSET);
            theme->calendarTheme_.touchCircleStrokeWidth =
                themeConstants->GetDimension(THEME_CALENDAR_TOUCH_CIRCLE_STROKE_WIDTH);
            theme->calendarTheme_.lunarHeight = themeConstants->GetDimension(THEME_CALENDAR_LUNAR_HEIGHT);
            theme->calendarTheme_.underscoreWidth = themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_WIDTH);
            theme->calendarTheme_.underscoreLength = themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_LENGTH);
            theme->calendarTheme_.scheduleMarkerRadius =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_RADIUS);

            theme->cardCalendarTheme_.titleTextColor = themeConstants->GetColor(THEME_CARD_CALENDAR_TITLE_TEXT_COLOR);
            theme->cardCalendarTheme_.arrowHeight = themeConstants->GetDimension(THEME_CARD_CALENDAR_ARROW_HEIGHT);
            theme->cardCalendarTheme_.arrowWidth = themeConstants->GetDimension(THEME_CARD_CALENDAR_ARROW_WIDTH);
            theme->cardCalendarTheme_.buttonHeight = themeConstants->GetDimension(THEME_CARD_CALENDAR_BUTTON_HEIGHT);
            theme->cardCalendarTheme_.buttonWidth = themeConstants->GetDimension(THEME_CARD_CALENDAR_BUTTON_WIDTH);
            theme->cardCalendarTheme_.titleFontSize = themeConstants->GetDimension(THEME_CARD_CALENDAR_TITLE_FONT_SIZE);
            theme->cardCalendarTheme_.weekColor = themeConstants->GetColor(THEME_CARD_CALENDAR_WEEK_COLOR);
            theme->cardCalendarTheme_.dayColor = themeConstants->GetColor(THEME_CARD_CALENDAR_DAY_COLOR);
            theme->cardCalendarTheme_.weekendDayColor = themeConstants->GetColor(THEME_CARD_CALENDAR_WEEKEND_DAY_COLOR);
            theme->cardCalendarTheme_.nonCurrentMonthDayColor =
                themeConstants->GetColor(THEME_CARD_CALENDAR_NON_CURRENT_MONTH_DAY_COLOR);
            theme->cardCalendarTheme_.focusedAreaBackgroundColor =
                themeConstants->GetColor(THEME_CARD_CALENDAR_FOCUS_AREA_BACKGROUND_COLOR);
            theme->cardCalendarTheme_.focusedDayColor = themeConstants->GetColor(THEME_CARD_CALENDAR_FOCUS_DAY_COLOR);
            theme->cardCalendarTheme_.touchColor = themeConstants->GetColor(THEME_CARD_CALENDAR_TOUCH_COLOR);
            theme->cardCalendarTheme_.topPadding = themeConstants->GetDimension(THEME_CARD_CALENDAR_TOP_PADDING);
            theme->cardCalendarTheme_.weekHeight = themeConstants->GetDimension(THEME_CARD_CALENDAR_WEEK_HEIGHT);
            theme->cardCalendarTheme_.dayHeight = themeConstants->GetDimension(THEME_CARD_CALENDAR_DAY_HEIGHT);
            theme->cardCalendarTheme_.weekWidth = themeConstants->GetDimension(THEME_CARD_CALENDAR_WEEK_WIDTH);
            theme->cardCalendarTheme_.dayWidth = themeConstants->GetDimension(THEME_CARD_CALENDAR_DAY_WIDTH);
            theme->cardCalendarTheme_.focusedAreaRadius =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_FOCUS_AREA_RADIUS);
            theme->cardCalendarTheme_.weekFontSize = themeConstants->GetDimension(THEME_CARD_CALENDAR_WEEK_FONT_SIZE);
            theme->cardCalendarTheme_.dayFontSize = themeConstants->GetDimension(THEME_CARD_CALENDAR_DAY_FONT_SIZE);
            theme->cardCalendarTheme_.lunarColor = themeConstants->GetColor(THEME_CARD_CALENDAR_LUNAR_COLOR);
            theme->cardCalendarTheme_.weekendLunarColor =
                themeConstants->GetColor(THEME_CARD_CALENDAR_WEEKEND_LUNAR_COLOR);
            theme->cardCalendarTheme_.nonCurrentMonthLunarColor =
                themeConstants->GetColor(THEME_CARD_CALENDAR_NON_CURRENT_MONTH_LUNAR_COLOR);
            theme->cardCalendarTheme_.gregorianCalendarHeight =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_GREGORIAN_CALENDAR_HEIGHT);
            theme->cardCalendarTheme_.lunarDayFontSize =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_LUNAR_FONT_SIZE);
            theme->cardCalendarTheme_.workDayMarkColor =
                themeConstants->GetColor(THEME_CARD_CALENDAR_WORK_DAY_MARK_COLOR);
            theme->cardCalendarTheme_.weekAndDayRowSpace =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_WEEK_AND_DAY_ROW_SPACE);
            theme->cardCalendarTheme_.dailyFiveRowSpace =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_DAILY_FIVE_ROW_SPACE);
            theme->cardCalendarTheme_.dayYAxisOffset = themeConstants->GetDimension(THEME_CALENDAR_DAY_YAXIS_OFFSET);
            theme->cardCalendarTheme_.lunarDayYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_LUNAR_DAY_YAXIS_OFFSET);
            theme->cardCalendarTheme_.underscoreXAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_XAXIS_OFFSET);
            theme->cardCalendarTheme_.underscoreYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_YAXIS_OFFSET);
            theme->cardCalendarTheme_.scheduleMarkerXAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_XAXIS_OFFSET);
            theme->cardCalendarTheme_.scheduleMarkerYAxisOffset =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_YAXIS_OFFSET);
            theme->cardCalendarTheme_.lunarHeight = themeConstants->GetDimension(THEME_CALENDAR_LUNAR_HEIGHT);
            theme->cardCalendarTheme_.underscoreWidth = themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_WIDTH);
            theme->cardCalendarTheme_.underscoreLength = themeConstants->GetDimension(THEME_CALENDAR_UNDERSCORE_LENGTH);
            theme->cardCalendarTheme_.scheduleMarkerRadius =
                themeConstants->GetDimension(THEME_CALENDAR_SCHEDULE_MARKER_RADIUS);
            theme->cardCalendarTheme_.boundaryColOffset =
                themeConstants->GetDimension(THEME_CARD_CALENDAR_BOUNDARY_COL_OFFSET);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }
    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<CalendarTheme>& theme) const
        {
            if (!themeStyle) {
                LOGW("Calendar parse pattern failed, themeStyle is invalid.");
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_CALENDAR, nullptr);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
            // Card theme
            theme->cardCalendarTheme_.focusedAreaBackgroundColor =
                pattern->GetAttr<Color>("card_area_bg_color_focused", Color::BLUE);
            theme->cardCalendarTheme_.dayColor =
                pattern->GetAttr<Color>("card_day_color", DEFAULT_DAY_COLOR);
            theme->cardCalendarTheme_.weekColor =
                pattern->GetAttr<Color>("card_week_color", Color::BLACK);
            theme->cardCalendarTheme_.nonCurrentMonthDayColor =
                pattern->GetAttr<Color>("card_uncurrent_month_day_color", DEFAULT_NON_CURRENT_MONTH_DAY_COLOR);
            theme->cardCalendarTheme_.weekendDayColor =
                pattern->GetAttr<Color>("card_weekend_color", DEFAULT_WEEKEND_DAY_COLOR);
            theme->cardCalendarTheme_.weekendLunarColor =
                pattern->GetAttr<Color>("card_weekend_lunar_color", DEFAULT_WEEKEND_LUNAR_COLOR);
            theme->cardCalendarTheme_.nonCurrentMonthLunarColor =
                pattern->GetAttr<Color>("card_uncurrent_month_lunar_color", DEFAULT_NON_CURRENT_MONTH_LUNAR_COLOR);
            theme->cardCalendarTheme_.todayColor =
                pattern->GetAttr<Color>("card_today_color", Color::WHITE);
            theme->cardCalendarTheme_.todayLunarColor =
                pattern->GetAttr<Color>("card_today_lunar_color", Color::WHITE);
            theme->cardCalendarTheme_.lunarColor =
                pattern->GetAttr<Color>("card_lunar_color", DEFAULT_LUNAR_COLOR);
            theme->cardCalendarTheme_.markLunarColor =
                pattern->GetAttr<Color>("card_mark_lunar_color", Color::BLUE);
            theme->cardCalendarTheme_.titleTextColor =
                pattern->GetAttr<Color>("card_title_text_color", Color::BLACK);
            theme->cardCalendarTheme_.clickEffectColor =
                pattern->GetAttr<Color>("card_switch_button_bg_color_clicked", Color::TRANSPARENT);

            // Normal theme
            theme->calendarTheme_.dayColor =
                pattern->GetAttr<Color>(CALENDAR_DAY_COLOR, DEFAULT_CALENDAR_DAY_COLOR);
            theme->calendarTheme_.weekColor =
                pattern->GetAttr<Color>(CALENDAR_WEEK_COLOR, DEFAULT_CALENDAR_WEEK_COLOR);
            theme->calendarTheme_.lunarColor =
                pattern->GetAttr<Color>(CALENDAR_LUNAR_COLOR, DEFAULT_CALENDAR_LUNAR_COLOR);
            theme->calendarTheme_.weekendDayColor =
                pattern->GetAttr<Color>(CALENDAR_WEEKEND_DAY_COLOR, DEFAULT_CALENDAR_WEEKEND_DAY_COLOR);
            theme->calendarTheme_.weekendLunarColor =
                pattern->GetAttr<Color>(CALENDAR_WEEKEND_LUNAR_COLOR, DEFAULT_CALENDAR_WEEKEND_LUNAR_COLOR);
            theme->calendarTheme_.focusedDayColor =
                pattern->GetAttr<Color>(CALENDAR_TODAY_DAY_FOCUS_COLOR, DEFAULT_CALENDAR_TODAY_DAY_FOCUS_COLOR);
            theme->calendarTheme_.focusedLunarColor =
                pattern->GetAttr<Color>(CALENDAR_TODAY_LUNAR_FOCUS_COLOR, DEFAULT_CALENDAR_TODAY_LUNAR_FOCUS_COLOR);
            theme->calendarTheme_.todayColor =
                pattern->GetAttr<Color>(CALENDAR_TODAY_DAY_UNFOCUS_COLOR, DEFAULT_CALENDAR_TODAY_DAY_UNFOCUS_COLOR);
            theme->calendarTheme_.todayLunarColor =
                pattern->GetAttr<Color>(CALENDAR_TODAY_LUNAR_UNFOCUS_COLOR, DEFAULT_CALENDAR_TODAY_LUNAR_UNFOCUS_COLOR);
            theme->calendarTheme_.workDayMarkColor =
                pattern->GetAttr<Color>(CALENDAR_WORK_MARK_COLOR, DEFAULT_CALENDAR_WORK_MARK_COLOR);
            theme->calendarTheme_.offDayMarkColor =
                pattern->GetAttr<Color>(CALENDAR_OFF_MARK_COLOR, DEFAULT_CALENDAR_OFF_MARK_COLOR);
            theme->calendarTheme_.nonCurrentMonthWorkDayMarkColor = pattern->GetAttr<Color>(
                CALENDAR_NONCURRENT_MONTH_WORK_MARK_COLOR, DEFAULT_CALENDAR_NONCURRENT_MONTH_WORK_MARK_COLOR);
            theme->calendarTheme_.nonCurrentMonthOffDayMarkColor = pattern->GetAttr<Color>(
                CALENDAR_NONCURRENT_MONTH_OFF_MARK_COLOR, DEFAULT_CALENDAR_NONCURRENT_MONTH_OFF_MARK_COLOR);
            theme->calendarTheme_.nonCurrentMonthDayColor = pattern->GetAttr<Color>(
                CALENDAR_NONCURRENT_MONTH_DAY_COLOR, DEFAULT_CALENDAR_NONCURRENT_MONTH_DAY_COLOR);
            theme->calendarTheme_.nonCurrentMonthLunarColor = pattern->GetAttr<Color>(
                CALENDAR_NONCURRENT_MONTH_LUNAR_COLOR, DEFAULT_CALENDAR_NONCURRENT_MONTH_LUNAR_COLOR);
            theme->calendarTheme_.focusedAreaBackgroundColor = pattern->GetAttr<Color>(
                CALENDAR_FOCUS_AREA_BACKGROUND_COLOR, DEFAULT_CALENDAR_FOCUS_AREA_BACKGROUND_COLOR);
            theme->calendarTheme_.blurAreaBackgroundColor = pattern->GetAttr<Color>(
                CALENDAR_BLUR_AREA_BACKGROUND_COLOR, DEFAULT_CALENDAR_BLUR_AREA_BACKGROUND_COLOR);
            // calendar picker
            theme->entryBorderColor_ = pattern->GetAttr<Color>("calendar_picker_entry_border_color", Color());
            theme->entryArrowColor_ = pattern->GetAttr<Color>("calendar_picker_entry_arrow_color", Color());
            theme->selectBackgroundColor_ = pattern->GetAttr<Color>(
                "calendar_picker_select_background_color", Color());
            theme->dialogBackgroundColor_ = pattern->GetAttr<Color>(
                "calendar_picker_dialog_background_color", Color());
            theme->calendarTitleFontColor_ = pattern->GetAttr<Color>("calendar_picker_title_font_color", Color());
            Color currentMonthColor = pattern->GetAttr<Color>("calendar_picker_title_font_color", Color());
            theme->textCurrentMonthColor_ = currentMonthColor.BlendOpacity(
                pattern->GetAttr<double>("calendar_picker_attribute_alpha_content_primary", 0.0));
            theme->textNonCurrentMonthColor_ = currentMonthColor.BlendOpacity(
                pattern->GetAttr<double>("calendar_picker_attribute_alpha_content_tertiary", 0.0));
            theme->textSelectedDayColor_ = pattern->GetAttr<Color>(
                "calendar_picker_text_selected_day_color", Color());
            theme->textCurrentDayColor_ = pattern->GetAttr<Color>("calendar_picker_text_current_day_color", Color());
            theme->backgroundKeyFocusedColor_ = pattern->GetAttr<Color>(
                "calendar_picker_background_key_focused_color", Color());
            Color backgroundSelectedTodayColor = pattern->GetAttr<Color>(
                "calendar_picker_background_selected_focused_color", Color());
            theme->backgroundSelectedTodayColor_ = backgroundSelectedTodayColor;
            theme->backgroundSelectedNotTodayColor_ = backgroundSelectedTodayColor.BlendOpacity(
                pattern->GetAttr<double>("calendar_picker_attribute_alpha_highlight_bg", 0.0));
            theme->backgroundHoverColor_ = pattern->GetAttr<Color>("calendar_picker_background_hover_color", Color());
            theme->backgroundPressColor_ = pattern->GetAttr<Color>("calendar_picker_background_press_color", Color());
            theme->entryFontColor_ = pattern->GetAttr<Color>("calendar_picker_entry_font_color", Color());
            theme->dialogDividerColor_ = pattern->GetAttr<Color>("calendar_picker_dialog_divider_color", Color());
            theme->entryHeight_ = pattern->GetAttr<Dimension>("calendar_picker_entry_height", 0.0_vp);
            theme->entryBorderWidth_ = pattern->GetAttr<Dimension>("calendar_picker_entry_border_width", 0.0_vp);
            theme->entryBorderRadius_ = pattern->GetAttr<Dimension>("calendar_picker_entry_border_radius", 0.0_vp);
            theme->entryButtonWidth_ = pattern->GetAttr<Dimension>("calendar_picker_entry_button_width", 0.0_vp);
            theme->entryArrowHeight_ = pattern->GetAttr<Dimension>("calendar_picker_entry_arrow_height", 0.0_vp);
            theme->entryArrowwidth_ = pattern->GetAttr<Dimension>("calendar_picker_entry_arrow_width", 0.0_vp);
            theme->entryDateLeftRightMargin_ = pattern->GetAttr<Dimension>(
                "calendar_picker_entry_date_left_right_margin", 0.0_vp);
            theme->entryDateTopBottomMargin_ = pattern->GetAttr<Dimension>(
                "calendar_picker_entry_date_top_bottom_margin", 0.0_vp);
            theme->dialogMargin_ = pattern->GetAttr<Dimension>("calendar_picker_dialog_margin", 0.0_vp);
            theme->calendarPickerDayWidthOrHeight_ = pattern->GetAttr<Dimension>(
                "calendar_picker_day_width_height", 0.0_vp);
            theme->calendarDayFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_day_font_size", 0.0_vp);
            theme->distanceBetweenContainterAndDate_ = pattern->GetAttr<Dimension>(
                "calendar_picker_distance_between_container_and_date", 0.0_vp);
            theme->distanceBetweenTitleAndDate_ = pattern->GetAttr<Dimension>(
                "calendar_picker_distance_between_title_and_date", 0.0_vp);
            theme->dalendarContainerHeight_ = pattern->GetAttr<Dimension>("calendar_picker_container_height", 0.0_vp);
            theme->calendarTitleFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_title_font_size", 0.0_vp);
            theme->calendarTitleRowHeight_ = pattern->GetAttr<Dimension>("calendar_picker_title_row_height", 0.0_vp);
            theme->calendarTitleRowTopPadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_title_row_top_padding", 0.0_vp);
            theme->calendarTitleRowLeftRightPadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_title_row_left_right_padding", 0.0_vp);
            theme->calendarTitleTextPadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_title_text_padding", 0.0_vp);
            theme->calendarTitleImagePadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_title_image_padding", 0.0_vp);
            theme->calendarImageWidthHeight_ = pattern->GetAttr<Dimension>(
                "calendar_picker_image_width_height", 0.0_vp);
            theme->calendarActionRowTopPadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_action_row_top_padding", 0.0_vp);
            theme->calendarActionRowBottomLeftRightPadding_ = pattern->GetAttr<Dimension>(
                "calendar_picker_action_row_bottom_left_right_padding", 0.0_vp);
            theme->calendarActionRowHeight_ = pattern->GetAttr<Dimension>("calendar_picker_action_row_height", 0.0_vp);
            theme->calendarDayRadius_ = pattern->GetAttr<Dimension>("calendar_picker_day_radius", 0.0_vp);
            theme->calendarDayKeyFocusedWidth_ = pattern->GetAttr<Dimension>("calendar_day_key_focused_width", 0.0_vp);
            theme->calendarDayKeyFocusedPenWidth_ = pattern->GetAttr<Dimension>(
                "calendar_day_key_focused_pen_width", 0.0_vp);
            theme->entryFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_entry_font_size", 0.0_fp);
            theme->dialogBorderRadius_ = pattern->GetAttr<Dimension>("calendar_picker_dialog_border_radius", 0.0_vp);
        }
    };

    CalendarThemeStructure& GetCalendarTheme()
    {
        return calendarTheme_;
    }

    CalendarThemeStructure& GetCardCalendarTheme()
    {
        return cardCalendarTheme_;
    }

    const Dimension& GetEntryHeight() const
    {
        return entryHeight_;
    }

    const Dimension& GetEntryBorderWidth() const
    {
        return entryBorderWidth_;
    }

    const Color& GetEntryBorderColor() const
    {
        return entryBorderColor_;
    }

    const Dimension& GetEntryBorderRadius() const
    {
        return entryBorderRadius_;
    }

    const Dimension& GetEntryButtonWidth() const
    {
        return entryButtonWidth_;
    }

    const Dimension& GetEntryDateTopBottomMargin() const
    {
        return entryDateTopBottomMargin_;
    }

    const Dimension& GetEntryDateLeftRightMargin() const
    {
        return entryDateLeftRightMargin_;
    }

    const Dimension& GetEntryArrowWidth() const
    {
        return entryArrowwidth_;
    }

    const Dimension& GetEntryArrowHeight() const
    {
        return entryArrowHeight_;
    }

    const Color& GetEntryArrowColor() const
    {
        return entryArrowColor_;
    }

    const Dimension& GetDialogMargin() const
    {
        return dialogMargin_;
    }

    const Color& GetSelectBackgroundColor() const
    {
        return selectBackgroundColor_;
    }

    const Dimension& GetCalendarPickerDayWidthOrHeight() const
    {
        return calendarPickerDayWidthOrHeight_;
    }

    const Dimension& GetCalendarDayFontSize() const
    {
        return calendarDayFontSize_;
    }

    const Dimension& GetDistanceBetweenContainterAndDate() const
    {
        return distanceBetweenContainterAndDate_;
    }

    const Dimension& GetDistanceBetweenTitleAndDate() const
    {
        return distanceBetweenTitleAndDate_;
    }

    const Dimension& GetCalendarContainerHeight() const
    {
        return dalendarContainerHeight_;
    }

    const Dimension& GetCalendarTitleFontSize() const
    {
        return calendarTitleFontSize_;
    }

    const Dimension& GetCalendarTitleRowHeight() const
    {
        return calendarTitleRowHeight_;
    }

    const Dimension& GetCalendarTitleRowTopPadding() const
    {
        return calendarTitleRowTopPadding_;
    }

    const Dimension& GetCalendarTitleRowLeftRightPadding() const
    {
        return calendarTitleRowLeftRightPadding_;
    }

    const Dimension& GetCalendarTitleTextPadding() const
    {
        return calendarTitleTextPadding_;
    }

    const Dimension& GetCalendarTitleImagePadding() const
    {
        return calendarTitleImagePadding_;
    }

    const Dimension& GetCalendarImageWidthHeight() const
    {
        return calendarImageWidthHeight_;
    }

    const Dimension& GetCalendarActionRowTopPadding() const
    {
        return calendarActionRowTopPadding_;
    }

    const Dimension& GetCalendarActionRowBottomLeftRightPadding() const
    {
        return calendarActionRowBottomLeftRightPadding_;
    }

    const Dimension& GetCalendarActionRowHeight() const
    {
        return calendarActionRowHeight_;
    }

    const Dimension& GetCalendarDayRadius() const
    {
        return calendarDayRadius_;
    }

    const Dimension& GetCalendarDayKeyFocusedWidth() const
    {
        return calendarDayKeyFocusedWidth_;
    }

    const Dimension& GetCalendarDayKeyFocusedPenWidth() const
    {
        return calendarDayKeyFocusedPenWidth_;
    }

    const Dimension& GetEntryFontSize() const
    {
        return entryFontSize_;
    }

    const Dimension& GetDialogBorderRadius() const
    {
        return dialogBorderRadius_;
    }

    const Color& GetDialogBackgroundColor() const
    {
        return dialogBackgroundColor_;
    }

    const Color& GetCalendarTitleFontColor() const
    {
        return calendarTitleFontColor_;
    }

    const Color& GetTextCurrentMonthColor() const
    {
        return textCurrentMonthColor_;
    }

    const Color& GetTextNonCurrentMonthColor() const
    {
        return textNonCurrentMonthColor_;
    }

    const Color& GetTextSelectedDayColor() const
    {
        return textSelectedDayColor_;
    }

    const Color& GetTextCurrentDayColor() const
    {
        return textCurrentDayColor_;
    }

    const Color& GetBackgroundKeyFocusedColor() const
    {
        return backgroundKeyFocusedColor_;
    }

    const Color& GetBackgroundSelectedTodayColor() const
    {
        return backgroundSelectedTodayColor_;
    }

    const Color& GetBackgroundSelectedNotTodayColor() const
    {
        return backgroundSelectedNotTodayColor_;
    }

    const Color& GetBackgroundHoverColor() const
    {
        return backgroundHoverColor_;
    }

    const Color& GetBackgroundPressColor() const
    {
        return backgroundPressColor_;
    }

    const Color& GetEntryFontColor() const
    {
        return entryFontColor_;
    }

    const Color& GetDialogDividerColor() const
    {
        return dialogDividerColor_;
    }
protected:
    CalendarTheme() = default;

private:
    CalendarThemeStructure calendarTheme_;
    CalendarThemeStructure cardCalendarTheme_;
    Color entryBorderColor_;
    Color entryArrowColor_;
    Color selectBackgroundColor_;
    Color dialogBackgroundColor_;
    Color calendarTitleFontColor_;
    Color textCurrentMonthColor_;
    Color textNonCurrentMonthColor_;
    Color textSelectedDayColor_;
    Color textCurrentDayColor_;
    Color backgroundKeyFocusedColor_;
    Color backgroundSelectedTodayColor_;
    Color backgroundSelectedNotTodayColor_;
    Color backgroundHoverColor_;
    Color backgroundPressColor_;
    Color entryFontColor_;
    Color dialogDividerColor_;
    Dimension entryHeight_;
    Dimension entryBorderWidth_;
    Dimension entryBorderRadius_;
    Dimension entryButtonWidth_;
    Dimension entryArrowHeight_;
    Dimension entryArrowwidth_;
    Dimension entryDateLeftRightMargin_;
    Dimension entryDateTopBottomMargin_;
    Dimension dialogMargin_;
    Dimension calendarPickerDayWidthOrHeight_;
    Dimension calendarDayFontSize_;
    Dimension distanceBetweenContainterAndDate_;
    Dimension distanceBetweenTitleAndDate_;
    Dimension dalendarContainerHeight_;
    Dimension calendarTitleFontSize_;
    Dimension calendarTitleRowHeight_;
    Dimension calendarTitleRowTopPadding_;
    Dimension calendarTitleRowLeftRightPadding_;
    Dimension calendarTitleTextPadding_;
    Dimension calendarTitleImagePadding_;
    Dimension calendarImageWidthHeight_;
    Dimension calendarActionRowTopPadding_;
    Dimension calendarActionRowBottomLeftRightPadding_;
    Dimension calendarActionRowHeight_;
    Dimension calendarDayRadius_;
    Dimension calendarDayKeyFocusedWidth_;
    Dimension calendarDayKeyFocusedPenWidth_;
    Dimension entryFontSize_;
    Dimension dialogBorderRadius_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_H

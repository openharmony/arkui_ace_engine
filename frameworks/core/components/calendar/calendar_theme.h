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
    std::string monday;
    std::string tuesday;
    std::string wednesday;
    std::string thursday;
    std::string friday;
    std::string saturday;
    std::string sunday;
    std::string nextYear;
    std::string nextMonth;
    std::string preYear;
    std::string preMonth;
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
            ParseNewPattern(themeConstants, theme);
            ParsePattern(themeConstants, theme);
            return theme;
        }
    private:
        void ParseCardTheme(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
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
        }

        void ParseNormalTheme(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
            // Normal theme
            theme->calendarTheme_.dayColor = pattern->GetAttr<Color>(CALENDAR_DAY_COLOR, DEFAULT_CALENDAR_DAY_COLOR);
            theme->calendarTheme_.weekColor = pattern->GetAttr<Color>(CALENDAR_WEEK_COLOR, DEFAULT_CALENDAR_WEEK_COLOR);
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
            theme->calendarTheme_.monday = pattern->GetAttr<std::string>("calendar_picker_mon", "");
            theme->calendarTheme_.tuesday = pattern->GetAttr<std::string>("calendar_picker_tue", "");
            theme->calendarTheme_.wednesday = pattern->GetAttr<std::string>("calendar_picker_wed", "");
            theme->calendarTheme_.thursday = pattern->GetAttr<std::string>("calendar_picker_thu", "");
            theme->calendarTheme_.friday = pattern->GetAttr<std::string>("calendar_picker_fri", "");
            theme->calendarTheme_.saturday = pattern->GetAttr<std::string>("calendar_picker_sat", "");
            theme->calendarTheme_.sunday = pattern->GetAttr<std::string>("calendar_picker_sun", "");
            theme->calendarTheme_.nextYear = pattern->GetAttr<std::string>("general_next_year", "");
            theme->calendarTheme_.nextMonth = pattern->GetAttr<std::string>("general_next_month", "");
            theme->calendarTheme_.preYear = pattern->GetAttr<std::string>("general_pre_year", "");
            theme->calendarTheme_.preMonth = pattern->GetAttr<std::string>("general_pre_month", "");
        }

        void ParseCalenderPickerFirstPart(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
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
            theme->dialogButtonBackgroundColor_ = pattern->GetAttr<Color>(
                "calendar_picker_dialog_button_bg_color", Color());
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
        }
        void ParseCalenderPickerSecondPart(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
            theme->entryDateLeftRightMargin_ = pattern->GetAttr<Dimension>(
                "calendar_picker_entry_date_left_right_margin", 0.0_vp);
            theme->entryDateTopBottomMargin_ = pattern->GetAttr<Dimension>(
                "calendar_picker_entry_date_top_bottom_margin", 0.0_vp);
            theme->dialogMargin_ = pattern->GetAttr<Dimension>("calendar_picker_dialog_margin", 0.0_vp);
            theme->calendarPickerDayWidthOrHeight_ = pattern->GetAttr<Dimension>(
                "calendar_picker_day_width_height", 0.0_vp);
            theme->calendarPickerDayLargeWidthOrHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_day_large_width_height", 40.0_vp);
            theme->calendarDayFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_day_font_size", 0.0_vp);
            theme->calendarSmallWeekFontSize_ =
                pattern->GetAttr<Dimension>("calendar_picker_small_day_font_size", 14.0_vp);
            theme->distanceBetweenContainterAndDate_ = pattern->GetAttr<Dimension>(
                "calendar_picker_distance_between_container_and_date", 0.0_vp);
            theme->distanceBetweenTitleAndDate_ = pattern->GetAttr<Dimension>(
                "calendar_picker_distance_between_title_and_date", 0.0_vp);
            theme->dalendarContainerHeight_ = pattern->GetAttr<Dimension>("calendar_picker_container_height", 0.0_vp);
            theme->calendarLargeContainerHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_large_container_height", 316.0_vp);
            theme->calendarLargerContainerHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_larger_container_height", 337.0_vp);
            theme->calendarTitleFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_title_font_size", 0.0_vp);
            theme->calendarTitleRowHeight_ = pattern->GetAttr<Dimension>("calendar_picker_title_row_height", 0.0_vp);
            theme->calendarTitleLargeRowHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_title_large_row_height", 94.0_vp);
            theme->calendarTitleLargerRowHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_title_larger_row_height", 106.0_vp);
        }

        void ParseCalenderPickerThirdPart(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
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
            theme->calendarActionLargeRowHeight_ =
                pattern->GetAttr<Dimension>("calendar_picker_action_large_row_height", 48.0_vp);
            theme->calendarDayRadius_ = pattern->GetAttr<Dimension>("calendar_picker_day_radius", 0.0_vp);
            theme->calendarDayKeyFocusedWidth_ = pattern->GetAttr<Dimension>("calendar_day_key_focused_width", 0.0_vp);
            theme->calendarLargeDayKeyFocusedWidth_ =
                pattern->GetAttr<Dimension>("calendar_large_day_key_focused_width", 44.0_vp);
            theme->calendarDayKeyFocusedPenWidth_ = pattern->GetAttr<Dimension>(
                "calendar_day_key_focused_pen_width", 0.0_vp);
            theme->entryFontSize_ = pattern->GetAttr<Dimension>("calendar_picker_entry_font_size", 0.0_fp);
            theme->dialogBorderRadius_ = pattern->GetAttr<Dimension>("calendar_picker_dialog_border_radius", 0.0_vp);
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
            // Card theme
            ParseCardTheme(themeConstants, theme);
            // Normal theme
            ParseNormalTheme(themeConstants, theme);
            // calendar picker
            ParseCalenderPickerFirstPart(themeConstants, theme);
            ParseCalenderPickerSecondPart(themeConstants, theme);
            ParseCalenderPickerThirdPart(themeConstants, theme);
        }

        void ParseCalendarThemePattern(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            CHECK_NULL_VOID(pattern);
            theme->calendarTheme_.weekFontSize = pattern->GetAttr<Dimension>("calendar_week_font_size", 14.0_fp);
            theme->calendarTheme_.dayFontSize = pattern->GetAttr<Dimension>("calendar_day_font_size", 18.0_fp);
            theme->calendarTheme_.lunarDayFontSize = pattern->GetAttr<Dimension>("calendar_lunar_font_size", 12.0_fp);
            theme->calendarTheme_.workDayMarkSize =
                pattern->GetAttr<Dimension>("calendar_work_day_mark_font_size", 10.0_fp);
            theme->calendarTheme_.offDayMarkSize =
                pattern->GetAttr<Dimension>("calendar_off_day_mark_font_size", 10.0_fp);
            theme->calendarTheme_.focusedAreaRadius =
                pattern->GetAttr<Dimension>("calendar_focused_area_radius", 24.0_vp);
            theme->calendarTheme_.topPadding = pattern->GetAttr<Dimension>("top_padding", 16.0_vp);
            theme->calendarTheme_.workStateWidth = pattern->GetAttr<Dimension>("work_state_width", 16.0_vp);
            theme->calendarTheme_.workStateHorizontalMovingDistance =
                pattern->GetAttr<Dimension>("work_state_horizontal_moving_distance", 2.0_vp);
            theme->calendarTheme_.workStateVerticalMovingDistance =
                pattern->GetAttr<Dimension>("work_state_vertical_moving_distance", 16.0_vp);
            theme->calendarTheme_.colSpace = pattern->GetAttr<Dimension>("column_space", 39.0_vp);
            theme->calendarTheme_.weekHeight = pattern->GetAttr<Dimension>("week_height", 19.0_vp);
            theme->calendarTheme_.dayHeight = pattern->GetAttr<Dimension>("day_height", 41.0_vp);
            theme->calendarTheme_.weekWidth = pattern->GetAttr<Dimension>("week_width", 48.0_vp);
            theme->calendarTheme_.dayWidth = pattern->GetAttr<Dimension>("day_width", 48.0_vp);
            theme->calendarTheme_.weekAndDayRowSpace = pattern->GetAttr<Dimension>("week_and_day_space", 12.0_vp);
            theme->calendarTheme_.dailyFiveRowSpace = pattern->GetAttr<Dimension>("five_row_space", 20.0_vp);
            theme->calendarTheme_.dailySixRowSpace = pattern->GetAttr<Dimension>("six_row_space", 10.0_vp);
            theme->calendarTheme_.gregorianCalendarHeight = pattern->GetAttr<Dimension>("gregorian_height", 25.0_vp);
            theme->calendarTheme_.dayFontWeight = pattern->GetAttr<std::string>("day_font_weight", "500");
            theme->calendarTheme_.lunarDayFontWeight = pattern->GetAttr<std::string>("lunar_day_font_weight", "500");
            theme->calendarTheme_.workStateFontWeight = pattern->GetAttr<std::string>("work_state_font_weight", "400");
            theme->calendarTheme_.workStateOffset =
                pattern->GetAttr<Dimension>("work_state_center_adjustment", 0.0_vp);
            theme->calendarTheme_.dayYAxisOffset = pattern->GetAttr<Dimension>("day_yaxis_offset", 4.0_vp);
            theme->calendarTheme_.lunarDayYAxisOffset = pattern->GetAttr<Dimension>("lunar_day_yaxis_offset", 23.0_vp);
            theme->calendarTheme_.underscoreXAxisOffset =
                pattern->GetAttr<Dimension>("underscore_xaxis_offset", 12.0_vp);
            theme->calendarTheme_.underscoreYAxisOffset =
                pattern->GetAttr<Dimension>("underscore_yaxis_offset", 36.0_vp);
            theme->calendarTheme_.scheduleMarkerXAxisOffset =
                pattern->GetAttr<Dimension>("schedule_marker_xaxis_offset", 22.0_vp);
            theme->calendarTheme_.scheduleMarkerYAxisOffset =
                pattern->GetAttr<Dimension>("schedule_marker_yaxis_offset", 40.0_vp);
            theme->calendarTheme_.touchCircleStrokeWidth =
                pattern->GetAttr<Dimension>("touch_circle_stroke_width", 1.0_vp);
            theme->calendarTheme_.lunarHeight = pattern->GetAttr<Dimension>("lunar_height", 14.0_vp);
            theme->calendarTheme_.underscoreWidth = pattern->GetAttr<Dimension>("underscore_width", 1.0_vp);
            theme->calendarTheme_.underscoreLength = pattern->GetAttr<Dimension>("underscore_length", 20.0_vp);
            theme->calendarTheme_.scheduleMarkerRadius =
                pattern->GetAttr<Dimension>("schedule_marker_radius", 2.0_vp);
        }

        void ParseCardCalendarThemePattern(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            CHECK_NULL_VOID(pattern);
            theme->cardCalendarTheme_.arrowHeight = pattern->GetAttr<Dimension>("arrow_height", 16.0_vp);
            theme->cardCalendarTheme_.arrowWidth = pattern->GetAttr<Dimension>("arrow_width", 16.0_vp);
            theme->cardCalendarTheme_.buttonHeight =
                pattern->GetAttr<Dimension>("card_calendar_button_height", 32.0_vp);
            theme->cardCalendarTheme_.buttonWidth =
                pattern->GetAttr<Dimension>("card_calendar_button_width", 32.0_vp);
            theme->cardCalendarTheme_.titleFontSize =
                pattern->GetAttr<Dimension>("card_calendar_title_font_size", 16.0_vp);
            theme->cardCalendarTheme_.focusedDayColor =
                pattern->GetAttr<Color>("today_day_focus_color", Color(0xFFFFFFFF));
            theme->cardCalendarTheme_.touchColor = pattern->GetAttr<Color>("calendar_touch_color", Color(0x320A59F7));
            theme->cardCalendarTheme_.topPadding = pattern->GetAttr<Dimension>("card_calendar_top_padding", 0.0_vp);
            theme->cardCalendarTheme_.weekHeight = pattern->GetAttr<Dimension>("card_calendar_week_height", 14.0_vp);
            theme->cardCalendarTheme_.dayHeight = pattern->GetAttr<Dimension>("card_calendar_day_height", 44.0_vp);
            theme->cardCalendarTheme_.weekWidth = pattern->GetAttr<Dimension>("card_calendar_week_width", 44.0_vp);
            theme->cardCalendarTheme_.dayWidth = pattern->GetAttr<Dimension>("card_calendar_day_width", 44.0_vp);
            theme->cardCalendarTheme_.focusedAreaRadius =
                pattern->GetAttr<Dimension>("card_calendar_focus_area_radius", 22.0_vp);
            theme->cardCalendarTheme_.weekFontSize =
                pattern->GetAttr<Dimension>("card_calendar_week_font_size", 10.0_fp);
            theme->cardCalendarTheme_.dayFontSize =
                pattern->GetAttr<Dimension>("card_calendar_day_font_size", 16.0_vp);
            theme->cardCalendarTheme_.gregorianCalendarHeight =
                pattern->GetAttr<Dimension>("card_calendar_gregorian_height", 24.0_vp);
            theme->cardCalendarTheme_.lunarDayFontSize =
                pattern->GetAttr<Dimension>("card_calendar_lunar_font_size", 10.0_vp);
            theme->cardCalendarTheme_.workDayMarkColor = pattern->GetAttr<Color>("work_mark_color", Color(0xffe83f26));
            theme->cardCalendarTheme_.weekAndDayRowSpace =
                pattern->GetAttr<Dimension>("card_calendar_week_day_row_space", 4.0_vp);
            theme->cardCalendarTheme_.dailyFiveRowSpace =
                pattern->GetAttr<Dimension>("card_calendar_daily_five_row_space", 10.0_vp);
            theme->cardCalendarTheme_.dayYAxisOffset = pattern->GetAttr<Dimension>("day_yaxis_offset", 4.0_vp);
            theme->cardCalendarTheme_.lunarDayYAxisOffset =
                pattern->GetAttr<Dimension>("lunar_day_yaxis_offset", 23.0_vp);
            theme->cardCalendarTheme_.underscoreXAxisOffset =
                pattern->GetAttr<Dimension>("underscore_xaxis_offset", 12.0_vp);
            theme->cardCalendarTheme_.underscoreYAxisOffset =
                pattern->GetAttr<Dimension>("underscore_yaxis_offset", 36.0_vp);
            theme->cardCalendarTheme_.scheduleMarkerXAxisOffset =
                pattern->GetAttr<Dimension>("schedule_marker_xaxis_offset", 22.0_vp);
            theme->cardCalendarTheme_.scheduleMarkerYAxisOffset =
                pattern->GetAttr<Dimension>("schedule_marker_yaxis_offset", 40.0_vp);
        }

        void ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CalendarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CALENDAR);
            if (!pattern) {
                LOGW("find pattern of calendar fail");
                return;
            }
            ParseCalendarThemePattern(themeConstants, theme);
            ParseCardCalendarThemePattern(themeConstants, theme);
            theme->cardCalendarTheme_.lunarHeight = pattern->GetAttr<Dimension>("lunar_height", 14.0_vp);
            theme->cardCalendarTheme_.underscoreWidth = pattern->GetAttr<Dimension>("underscore_width", 1.0_vp);
            theme->cardCalendarTheme_.underscoreLength = pattern->GetAttr<Dimension>("underscore_length", 20.0_vp);
            theme->cardCalendarTheme_.scheduleMarkerRadius =
                pattern->GetAttr<Dimension>("schedule_marker_radius", 2.0_vp);
            theme->cardCalendarTheme_.boundaryColOffset =
                pattern->GetAttr<Dimension>("boundary_col_offset", 50.0_vp);
            std::string isButtonTransparent =
                pattern->GetAttr<std::string>("calendar_picker_dialog_button_transparent", "true");
            theme->isButtonTransparent_ = (isButtonTransparent == "true");
            std::string isDividerTransparent =
                pattern->GetAttr<std::string>("calendar_picker_dialog_divider_transparent", "false");
            theme->isDividerTransparent_ = (isDividerTransparent == "true");
            theme->calendarPickerLargeScale_ = pattern->GetAttr<double>("calendar_picker_large_scale", 1.75);
            theme->calendarPickerLargerScale_ = pattern->GetAttr<double>("calendar_picker_larger_scale", 2.0);
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

    const Dimension& GetCalendarPickerDayLargeWidthOrHeight() const
    {
        return calendarPickerDayLargeWidthOrHeight_;
    }

    const Dimension& GetCalendarDayFontSize() const
    {
        return calendarDayFontSize_;
    }

    const Dimension& GetCalendarSmallDayFontSize() const
    {
        return calendarSmallWeekFontSize_;
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

    const Dimension& GetCalendarLargeContainerHeight() const
    {
        return calendarLargeContainerHeight_;
    }

    const Dimension& GetCalendarLargerContainerHeight() const
    {
        return calendarLargerContainerHeight_;
    }

    const Dimension& GetCalendarTitleFontSize() const
    {
        return calendarTitleFontSize_;
    }

    const Dimension& GetCalendarTitleRowHeight() const
    {
        return calendarTitleRowHeight_;
    }

    const Dimension& GetCalendarTitleLargeRowHeight() const
    {
        return calendarTitleLargeRowHeight_;
    }

    const Dimension& GetCalendarTitleLargerRowHeight() const
    {
        return calendarTitleLargerRowHeight_;
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

    const Dimension& GetCalendarActionLargeRowHeight() const
    {
        return calendarActionLargeRowHeight_;
    }

    const Dimension& GetCalendarDayRadius() const
    {
        return calendarDayRadius_;
    }

    const Dimension& GetCalendarDayKeyFocusedWidth() const
    {
        return calendarDayKeyFocusedWidth_;
    }

    const Dimension& GetCalendarLargeDayKeyFocusedWidth() const
    {
        return calendarLargeDayKeyFocusedWidth_;
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

    const Color& GetDialogButtonBackgroundColor() const
    {
        return dialogButtonBackgroundColor_;
    }
    
    bool GetIsButtonTransparent() const
    {
        return isButtonTransparent_;
    }

    bool GetIsDividerTransparent() const
    {
        return isDividerTransparent_;
    }
    
    double GetCalendarPickerLargeScale() const
    {
        return calendarPickerLargeScale_;
    }

    double GetCalendarPickerLargerScale() const
    {
        return calendarPickerLargerScale_;
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
    Color dialogButtonBackgroundColor_;
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
    Dimension calendarPickerDayLargeWidthOrHeight_;
    Dimension calendarDayFontSize_;
    Dimension calendarSmallWeekFontSize_;
    Dimension distanceBetweenContainterAndDate_;
    Dimension distanceBetweenTitleAndDate_;
    Dimension dalendarContainerHeight_;
    Dimension calendarLargeContainerHeight_;
    Dimension calendarLargerContainerHeight_;
    Dimension calendarTitleFontSize_;
    Dimension calendarTitleRowHeight_;
    Dimension calendarTitleLargeRowHeight_;
    Dimension calendarTitleLargerRowHeight_;
    Dimension calendarTitleRowTopPadding_;
    Dimension calendarTitleRowLeftRightPadding_;
    Dimension calendarTitleTextPadding_;
    Dimension calendarTitleImagePadding_;
    Dimension calendarImageWidthHeight_;
    Dimension calendarActionRowTopPadding_;
    Dimension calendarActionRowBottomLeftRightPadding_;
    Dimension calendarActionRowHeight_;
    Dimension calendarActionLargeRowHeight_;
    Dimension calendarDayRadius_;
    Dimension calendarDayKeyFocusedWidth_;
    Dimension calendarLargeDayKeyFocusedWidth_;
    Dimension calendarDayKeyFocusedPenWidth_;
    Dimension entryFontSize_;
    Dimension dialogBorderRadius_;
    bool isButtonTransparent_ = true;
    bool isDividerTransparent_ = false;
    double calendarPickerLargeScale_ = 0.0;
    double calendarPickerLargerScale_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_H

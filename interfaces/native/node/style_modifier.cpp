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
#include "style_modifier.h"

#include <cstdlib>

#include "frame_information.h"
#include "node_model.h"
#include "node_transition.h"
#include "waterflow_section_option.h"
#include "progress_option.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"

namespace OHOS::Ace::NodeModel {
namespace {
const std::regex COLOR_WITH_MAGIC("#[0-9A-Fa-f]{8}");
const std::regex BRACKETS("\\(.*?\\)");
const std::regex FLOAT_MAGIC("^[0-9]+(\\.[0-9]+)?$");
const std::regex SIZE_TYPE_MAGIC("([0-9]+)([a-z]+)");
const char *COLORING_STRATEGY = "invert";
const char *COLOR_MARKERS = "color";
constexpr char PARAMS_SEPARATOR_LEVEL1 = ';';
constexpr int UNIT_PX = 0;
constexpr int UNIT_VP = 1;
constexpr int UNIT_FP = 2;
constexpr int UNIT_PERCENT = 3;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int NUM_15 = 15;
constexpr int NUM_16 = 16;
constexpr int NUM_23 = 23;
constexpr int NUM_29 = 29;
constexpr int NUM_31 = 31;
constexpr int NUM_59 = 59;
constexpr int NUM_100 = 100;
constexpr int NUM_400 = 400;
const int ALLOW_SIZE_1(1);
const int ALLOW_SIZE_2(2);
const int ALLOW_SIZE_3(3);
const int ALLOW_SIZE_4(4);
const int ALLOW_SIZE_5(5);
const int ALLOW_SIZE_7(7);
const int ALLOW_SIZE_8(8);
const int ALLOW_SIZE_16(16);
const int ALLOW_SIZE_10(10);

constexpr int DEFAULT_SIZE_18 = 18;
constexpr int DEFAULT_SIZE_24 = 24;
constexpr int DEFAULT_SIZE_50 = 50;
constexpr int COLOR_STRATEGY_STYLE = 1;
constexpr int COLOR_STYLE = 2;
constexpr int DISPLAY_ARROW_FALSE = 0;
constexpr int DISPLAY_ARROW_TRUE = 1;
constexpr int32_t X_INDEX = 0;
constexpr int32_t Y_INDEX = 1;
constexpr int32_t Z_INDEX = 2;
constexpr int32_t CENTER_X_INDEX = 0;
constexpr int32_t CENTER_Y_INDEX = 1;
constexpr int32_t CENTER_Z_INDEX = 2;
constexpr int32_t CENTER_X_PERCENT_INDEX = 3;
constexpr int32_t CENTER_Y_PERCENT_INDEX = 4;
constexpr int32_t CENTER_Z_PERCENT_INDEX = 5;
constexpr int32_t ROTATE_PERSPECTIVE_INDEX = 4;
constexpr int32_t ROTATE_ANGLE_INDEX = 3;
constexpr uint32_t ARRAY_SIZE = 3;
constexpr int32_t BACKGROUND_IMAGE_WIDTH_INDEX = 0;
constexpr int32_t BACKGROUND_IMAGE_HEIGHT_INDEX = 1;
constexpr float DEFAULT_OPACITY = 1.0f;

constexpr int32_t BLUR_STYLE_INDEX = 0;
constexpr int32_t COLOR_MODE_INDEX = 1;
constexpr int32_t ADAPTIVE_COLOR_INDEX = 2;
constexpr int32_t SCALE_INDEX = 3;
constexpr int32_t GRAY_SCALE_START = 4;
constexpr int32_t GRAY_SCALE_END = 5;
constexpr float MAX_GRAYSCALE = 127.0f;
constexpr int32_t DECORATION_COLOR_INDEX = 1;
constexpr int32_t DECORATION_STYLE_INDEX = 2;
constexpr int32_t PROGRESS_TYPE_LINEAR = 1;
constexpr int32_t PROGRESS_TYPE_RING = 2;
constexpr int32_t PROGRESS_TYPE_SCALE = 3;
constexpr int32_t PROGRESS_TYPE_MOON = 7;
constexpr int32_t PROGRESS_TYPE_CAPSULE = 9;
const std::vector<int32_t> PROGRESS_TYPE_ARRAY = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING, PROGRESS_TYPE_MOON,
    PROGRESS_TYPE_SCALE, PROGRESS_TYPE_CAPSULE};
constexpr int32_t OBJECT_FIT_FILL = 0;
constexpr int32_t OBJECT_FIT_CONTAIN = 1;
constexpr int32_t OBJECT_FIT_COVER = 2;
constexpr int32_t OBJECT_FIT_AUTO = 3;
constexpr int32_t OBJECT_FIT_NONE = 5;
constexpr int32_t OBJECT_FIT_SCALE_DOWN = 6;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_TOP_START = 7;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_TOP = 8;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_TOP_END = 9;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_START = 10;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_CENTER = 11;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_END = 12;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_BOTTOM_START = 13;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_BOTTOM = 14;
constexpr int32_t OBJECT_FIT_NONE_ALIGN_BOTTOM_END = 15;
const std::vector<int32_t> OBJECT_FIT_ARRAY = { OBJECT_FIT_CONTAIN, OBJECT_FIT_COVER, OBJECT_FIT_AUTO,
    OBJECT_FIT_FILL, OBJECT_FIT_SCALE_DOWN, OBJECT_FIT_NONE,
    OBJECT_FIT_NONE_ALIGN_TOP_START, OBJECT_FIT_NONE_ALIGN_TOP, OBJECT_FIT_NONE_ALIGN_TOP_END,
    OBJECT_FIT_NONE_ALIGN_START, OBJECT_FIT_NONE_ALIGN_CENTER, OBJECT_FIT_NONE_ALIGN_END,
    OBJECT_FIT_NONE_ALIGN_BOTTOM_START, OBJECT_FIT_NONE_ALIGN_BOTTOM, OBJECT_FIT_NONE_ALIGN_BOTTOM_END };
constexpr int32_t IMAGE_SPAN_ALIGNMENT_BASELINE = 4;
constexpr int32_t IMAGE_SPAN_ALIGNMENT_BOTTOM = 3;
constexpr int32_t IMAGE_SPAN_ALIGNMENT_CENTER = 2;
constexpr int32_t IMAGE_SPAN_ALIGNMENT_TOP = 1;
const std::vector<int32_t> IMAGE_SPAN_ALIGNMENT_ARRAY = { IMAGE_SPAN_ALIGNMENT_BASELINE, IMAGE_SPAN_ALIGNMENT_BOTTOM,
    IMAGE_SPAN_ALIGNMENT_CENTER, IMAGE_SPAN_ALIGNMENT_TOP };
const std::vector<std::string> CURVE_ARRAY = { "linear", "ease", "ease-in", "ease-out", "ease-in-out",
    "fast-out-slow-in", "linear-out-slow-in", "fast-out-linear-in", "extreme-deceleration", "sharp", "rhythm", "smooth",
    "friction" };
const std::vector<std::string> FONT_STYLES = { "normal", "italic" };
const std::vector<std::string> LENGTH_METRIC_UNIT = { "px", "vp", "fp" };
std::unordered_map<int32_t, bool> SPAN_ATTRIBUTES_MAP = {
    { static_cast<int32_t>(NODE_SPAN_CONTENT), true },
    { static_cast<int32_t>(NODE_TEXT_DECORATION), true },
    { static_cast<int32_t>(NODE_FONT_COLOR), true },
    { static_cast<int32_t>(NODE_FONT_SIZE), true },
    { static_cast<int32_t>(NODE_FONT_STYLE), true },
    { static_cast<int32_t>(NODE_FONT_WEIGHT), true },
    { static_cast<int32_t>(NODE_TEXT_LINE_HEIGHT), true },
    { static_cast<int32_t>(NODE_TEXT_CASE), true },
    { static_cast<int32_t>(NODE_TEXT_LETTER_SPACING), true },
    { static_cast<int32_t>(NODE_FONT_FAMILY), true },
    { static_cast<int32_t>(NODE_TEXT_TEXT_SHADOW), true },
    { static_cast<int32_t>(NODE_SPAN_TEXT_BACKGROUND_STYLE), true },
    { static_cast<int32_t>(NODE_SPAN_BASELINE_OFFSET), true },
};
constexpr int32_t ANIMATION_DURATION_INDEX = 0;
constexpr int32_t ANIMATION_CURVE_INDEX = 1;
constexpr int32_t ANIMATION_DELAY_INDEX = 2;
constexpr int32_t ANIMATION_INTERATION_INDEX = 3;
constexpr int32_t ANIMATION_PLAY_MODE_INDEX = 4;
constexpr int32_t ANIMATION_TEMPO_INDEX = 5;
constexpr int32_t ANIMATION_PLAY_MODE_REVERSE_VALUE = 2;
constexpr int32_t ANIMATION_PLAY_MODE_ALTERNATE_VALUE = 1;
constexpr int32_t OPACITY_ANIMATION_BASE = 1;
constexpr int32_t MOVE_ANIMATION_BASE = 1;
constexpr int32_t ROTATE_ANIMATION_BASE = 5;
constexpr int32_t SCALE_ANIMATION_BASE = 3;
constexpr int32_t TRANSLATE_ANIMATION_BASE = 3;
constexpr int32_t DEFAULT_DURATION = 1000;
constexpr int32_t TWO = 2;
constexpr float ZERO_F = 0.0f;
constexpr float HUNDRED = 100.0f;
constexpr float SLIDER_STEP_MIN_F = 0.01f;
constexpr float HALF = 0.5f;
constexpr float DEFAULT_HINT_RADIUS = 16.0f;
constexpr float DEFAULT_SCROLL_FADING_EDGE_LENGTH = 32.0f;
constexpr int32_t REQUIRED_ONE_PARAM = 1;
constexpr int32_t REQUIRED_TWO_PARAM = 2;
constexpr int32_t REQUIRED_THREE_PARAM = 3;
constexpr int32_t REQUIRED_FOUR_PARAM = 4;
constexpr int32_t REQUIRED_FIVE_PARAM = 5;
constexpr int32_t REQUIRED_SEVEN_PARAM = 7;
constexpr int32_t REQUIRED_TWENTY_PARAM = 20;
constexpr int32_t MAX_ATTRIBUTE_ITEM_LEN = 20;
std::string g_stringValue;
ArkUI_NumberValue g_numberValues[MAX_ATTRIBUTE_ITEM_LEN] = { 0 };
ArkUI_AttributeItem g_attributeItem = { g_numberValues, MAX_ATTRIBUTE_ITEM_LEN, nullptr, nullptr };

constexpr uint32_t DEFAULT_COLOR = 0xFF000000; // Black
constexpr uint32_t DEFAULT_FIll_COLOR = 0x00000000;
constexpr int32_t DEFAULT_X = 0;
constexpr int32_t DEFAULT_Y = 0;

constexpr int32_t DEFAULT_TRUE = 1;
constexpr int32_t DEFAULT_FALSE = 0;

constexpr int32_t RETURN_SIZE_ONE = 1;
constexpr int32_t EDGE_TYPE_INDEX = 0;
constexpr int32_t EDGE_OFFSET_X_INDEX = 1;
constexpr int32_t EDGE_OFFSET_Y_INDEX = 2;
constexpr int32_t SELECTED_YEAR_INDEX = 0;
constexpr int32_t SELECTED_MONTH_INDEX = 1;
constexpr int32_t SELECTED_DAY_INDEX = 2;
constexpr int32_t DATEPICKER_START_TIME = 1970;
constexpr int32_t DATEPICKER_END_TIME = 2100;
constexpr int32_t CALENDAR_PICKER_FONT_COLOR_INDEX = 0;
constexpr int32_t CALENDAR_PICKER_FONT_SIZE_INDEX = 1;
constexpr int32_t CALENDAR_PICKER_FONT_WEIGHT_INDEX = 2;
constexpr int32_t IMAGE_SIZE_TYPE_CONTAIN_INDEX = 0;
constexpr int32_t IMAGE_SIZE_TYPE_COVER_INDEX = 1;
constexpr int32_t IMAGE_SIZE_TYPE_AUTO_INDEX = 2;
constexpr int32_t ERROR_CODE = -1;
constexpr int32_t OUTLINE_LEFT_WIDTH_INDEX = 0;
constexpr int32_t OUTLINE_TOP_WIDTH_INDEX = 1;
constexpr int32_t OUTLINE_RIGHT_WIDTH_INDEX = 2;
constexpr int32_t OUTLINE_BOTTOM_WIDTH_INDEX = 3;
constexpr uint32_t CONVERT_CONTENT_TYPE = 5;
constexpr uint32_t DEFAULT_PICKER_STYLE_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_PICKER_SELECTED_COLOR = 0xFF007DFF;
const std::string EMPTY_STR = "";
const std::vector<std::string> ACCESSIBILITY_LEVEL_VECTOR = { "auto", "yes", "no", "no-hide-descendants" };
std::map<std::string, int32_t> ACCESSIBILITY_LEVEL_MAP = { { "auto", 0 }, { "yes", 1 }, { "no", 2 },
    { "no-hide-descendants", 3 } };

std::unordered_map<uint32_t, std::string> ACCESSIBILITY_ROLE_CONVERT_PROPERTY_MAP = {
    { static_cast<uint32_t>(ARKUI_NODE_CUSTOM), "Custom" },
    { static_cast<uint32_t>(ARKUI_NODE_TEXT), "Text" },
    { static_cast<uint32_t>(ARKUI_NODE_SPAN), "Span" },
    { static_cast<uint32_t>(ARKUI_NODE_IMAGE_SPAN), "ImageSpan" },
    { static_cast<uint32_t>(ARKUI_NODE_IMAGE), "Image" },
    { static_cast<uint32_t>(ARKUI_NODE_TOGGLE), "Toggle" },
    { static_cast<uint32_t>(ARKUI_NODE_LOADING_PROGRESS), "LoadingProgress" },
    { static_cast<uint32_t>(ARKUI_NODE_TEXT_INPUT), "TextInput" },
    { static_cast<uint32_t>(ARKUI_NODE_TEXT_AREA), "TextArea" },
    { static_cast<uint32_t>(ARKUI_NODE_BUTTON), "Button" },
    { static_cast<uint32_t>(ARKUI_NODE_PROGRESS), "Progress" },
    { static_cast<uint32_t>(ARKUI_NODE_CHECKBOX), "Checkbox" },
    { static_cast<uint32_t>(ARKUI_NODE_XCOMPONENT), "Xcomponent" },
    { static_cast<uint32_t>(ARKUI_NODE_DATE_PICKER), "DatePicker" },
    { static_cast<uint32_t>(ARKUI_NODE_TIME_PICKER), "TimePicker" },
    { static_cast<uint32_t>(ARKUI_NODE_TEXT_PICKER), "TextPicker" },
    { static_cast<uint32_t>(ARKUI_NODE_CALENDAR_PICKER), "CalendarPicker" },
    { static_cast<uint32_t>(ARKUI_NODE_SLIDER), "Slider" },
    { static_cast<uint32_t>(ARKUI_NODE_RADIO), "Radio" },
    { static_cast<uint32_t>(ARKUI_NODE_STACK), "Stack" },
    { static_cast<uint32_t>(ARKUI_NODE_CHECKBOX_GROUP), "CheckboxGroup" },
    { static_cast<uint32_t>(ARKUI_NODE_SWIPER), "Swiper" },
    { static_cast<uint32_t>(ARKUI_NODE_SCROLL), "Scroll" },
    { static_cast<uint32_t>(ARKUI_NODE_LIST), "List" },
    { static_cast<uint32_t>(ARKUI_NODE_LIST_ITEM), "ListItem" },
    { static_cast<uint32_t>(ARKUI_NODE_LIST_ITEM_GROUP), "ListItemGroup" },
    { static_cast<uint32_t>(ARKUI_NODE_COLUMN), "Column" },
    { static_cast<uint32_t>(ARKUI_NODE_ROW), "Row" },
    { static_cast<uint32_t>(ARKUI_NODE_FLEX), "Flex" },
    { static_cast<uint32_t>(ARKUI_NODE_REFRESH), "Refresh" },
    { static_cast<uint32_t>(ARKUI_NODE_WATER_FLOW), "WaterFlow" },
    { static_cast<uint32_t>(ARKUI_NODE_FLOW_ITEM), "FlowItem" },
    { static_cast<uint32_t>(ARKUI_NODE_RELATIVE_CONTAINER), "RelativeContainer" },
    { static_cast<uint32_t>(ARKUI_NODE_GRID), "Grid" },
    { static_cast<uint32_t>(ARKUI_NODE_GRID_ITEM), "GridItem" },
    { static_cast<uint32_t>(ARKUI_NODE_CUSTOM_SPAN), "CustomSpan" },
};

std::unordered_map<std::string, uint32_t> ACCESSIBILITY_ROLE_CONVERT_NATIVE_MAP = {
    { "Custom", static_cast<uint32_t>(ARKUI_NODE_CUSTOM) },
    { "Text", static_cast<uint32_t>(ARKUI_NODE_TEXT) },
    { "Span", static_cast<uint32_t>(ARKUI_NODE_SPAN) },
    { "ImageSpan", static_cast<uint32_t>(ARKUI_NODE_IMAGE_SPAN) },
    { "Image", static_cast<uint32_t>(ARKUI_NODE_IMAGE) },
    { "Toggle", static_cast<uint32_t>(ARKUI_NODE_TOGGLE) },
    { "LoadingProgress", static_cast<uint32_t>(ARKUI_NODE_LOADING_PROGRESS) },
    { "TextInput", static_cast<uint32_t>(ARKUI_NODE_TEXT_INPUT) },
    { "TextArea", static_cast<uint32_t>(ARKUI_NODE_TEXT_AREA) },
    { "Button", static_cast<uint32_t>(ARKUI_NODE_BUTTON) },
    { "Progress", static_cast<uint32_t>(ARKUI_NODE_PROGRESS) },
    { "Checkbox", static_cast<uint32_t>(ARKUI_NODE_CHECKBOX) },
    { "Xcomponent", static_cast<uint32_t>(ARKUI_NODE_XCOMPONENT) },
    { "DatePicker", static_cast<uint32_t>(ARKUI_NODE_DATE_PICKER) },
    { "TimePicker", static_cast<uint32_t>(ARKUI_NODE_TIME_PICKER) },
    { "TextPicker", static_cast<uint32_t>(ARKUI_NODE_TEXT_PICKER) },
    { "CalendarPicker", static_cast<uint32_t>(ARKUI_NODE_CALENDAR_PICKER) },
    { "Slider", static_cast<uint32_t>(ARKUI_NODE_SLIDER) },
    { "Radio", static_cast<uint32_t>(ARKUI_NODE_RADIO) },
    { "Stack", static_cast<uint32_t>(ARKUI_NODE_STACK) },
    { "CheckboxGroup", static_cast<uint32_t>(ARKUI_NODE_CHECKBOX_GROUP) },
    { "Swiper", static_cast<uint32_t>(ARKUI_NODE_SWIPER) },
    { "Scroll", static_cast<uint32_t>(ARKUI_NODE_SCROLL) },
    { "List", static_cast<uint32_t>(ARKUI_NODE_LIST) },
    { "ListItem", static_cast<uint32_t>(ARKUI_NODE_LIST_ITEM) },
    { "ListItemGroup", static_cast<uint32_t>(ARKUI_NODE_LIST_ITEM_GROUP) },
    { "Column", static_cast<uint32_t>(ARKUI_NODE_COLUMN) },
    { "Row", static_cast<uint32_t>(ARKUI_NODE_ROW) },
    { "Flex", static_cast<uint32_t>(ARKUI_NODE_FLEX) },
    { "Refresh", static_cast<uint32_t>(ARKUI_NODE_REFRESH) },
    { "WaterFlow", static_cast<uint32_t>(ARKUI_NODE_WATER_FLOW) },
    { "FlowItem", static_cast<uint32_t>(ARKUI_NODE_FLOW_ITEM) },
    { "RelativeContainer", static_cast<uint32_t>(ARKUI_NODE_RELATIVE_CONTAINER) },
    { "Grid", static_cast<uint32_t>(ARKUI_NODE_GRID) },
    { "GridItem", static_cast<uint32_t>(ARKUI_NODE_GRID_ITEM) },
    { "CustomSpan", static_cast<uint32_t>(ARKUI_NODE_CUSTOM_SPAN) },
};

void ResetAttributeItem()
{
    for (int i = 0; i < MAX_ATTRIBUTE_ITEM_LEN; ++i) {
        g_numberValues[i].i32 = 0;
    }
    g_attributeItem.size = 0;
    g_attributeItem.string = nullptr;
    g_attributeItem.object = nullptr;
}
uint32_t StringToColorInt(const char* string, uint32_t defaultValue = 0)
{
    std::smatch matches;
    std::string colorStr(string);
    if (std::regex_match(colorStr, matches, COLOR_WITH_MAGIC)) {
        colorStr.erase(0, 1);
        constexpr int colorNumFormat = 16;
        errno = 0;
        char* end = nullptr;
        unsigned long int value = strtoul(colorStr.c_str(), &end, colorNumFormat);
        if (errno == ERANGE) {
            LOGE("%{public}s is out of range.", colorStr.c_str());
        }
        if (value == 0 && end == colorStr.c_str()) {
            LOGW("input %{public}s can not covert to number, use default color：0x00000000" , colorStr.c_str());
        }
    
        return value;
    }
    return defaultValue;
}

int32_t GetDefaultUnit(ArkUI_NodeHandle nodePtr, int32_t defaultUnit)
{
    if (nodePtr->lengthMetricUnit == ARKUI_LENGTH_METRIC_UNIT_DEFAULT) {
        return defaultUnit;
    }
    return static_cast<int32_t>(nodePtr->lengthMetricUnit);
}

int StringToInt(const char* string, int defaultValue = 0)
{
    char* end;
    auto value = std::strtol(string, &end, 10);
    if (end == string || errno == ERANGE || (value < INT_MIN || value > INT_MAX)) {
        return defaultValue;
    }
    return value;
}

int StringToEnumInt(const char* value, const std::vector<std::string>& vec, int defaultValue)
{
    std::string input(value);
    auto it = std::find_if(vec.begin(), vec.end(), [&input](const std::string& str) { return str == input; });
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    }
    return defaultValue;
}

std::string CurveToString(int curve)
{
    std::string curveStr = "linear";
    switch (curve) {
        case ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR:
            curveStr = "linear";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE:
            curveStr = "ease";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN:
            curveStr = "ease-in";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_OUT:
            curveStr = "ease-out";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN_OUT:
            curveStr = "ease-in-out";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_SLOW_IN:
            curveStr = "fast-out-slow-in";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR_OUT_SLOW_IN:
            curveStr = "linear-out-slow-in";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_LINEAR_IN:
            curveStr = "fast-out-linear-in";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_EXTREME_DECELERATION:
            curveStr = "extreme-deceleration";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_SHARP:
            curveStr = "sharp";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_RHYTHM:
            curveStr = "rhythm";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_SMOOTH:
            curveStr = "smooth";
            break;
        case ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION:
            curveStr = "friction";
            break;
        default:
            break;
    }
    return curveStr;
}

std::string ShapeToString(int shape)
{
    std::string shapeStr = "rect";
    switch (shape) {
        case NUM_0:
            shapeStr = "rect";
            break;
        case NUM_1:
            shapeStr = "circle";
            break;
        case NUM_2:
            shapeStr = "ellipse";
            break;
        case NUM_3:
            shapeStr = "path";
            break;
        case NUM_4:
            shapeStr = "progress";
            break;
        default:
            break;
    }
    return shapeStr;
}

int32_t ConvertBlurStyle(int32_t originBlurStyle)
{
    if (originBlurStyle < static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE)) {
        return originBlurStyle + 1;
    } else if (originBlurStyle == static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE)) {
        return 0;
    }
    return originBlurStyle;
}

int32_t UnConvertBlurStyle(int32_t blurStyle)
{
    if (blurStyle == 0) {
        return static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE);
    } else if (blurStyle <= static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE)) {
        return blurStyle - 1;
    }
    return blurStyle;
}

int32_t ConvertAnimationDirection(int32_t animationPlayMode)
{
    if (animationPlayMode == static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_REVERSE)) {
        return ANIMATION_PLAY_MODE_REVERSE_VALUE;
    } else if (animationPlayMode == static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_ALTERNATE)) {
        return ANIMATION_PLAY_MODE_ALTERNATE_VALUE;
    }
    return animationPlayMode;
}

int32_t UnConvertAnimationDirection(int32_t animationPlayMode)
{
    if (animationPlayMode == static_cast<int32_t>(ANIMATION_PLAY_MODE_REVERSE_VALUE)) {
        return static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_REVERSE);
    } else if (animationPlayMode == static_cast<int32_t>(ANIMATION_PLAY_MODE_ALTERNATE_VALUE)) {
        return static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_ALTERNATE);
    }
    return animationPlayMode;
}

std::string ConvertAccessibilityRole(uint32_t nodeTypeInt)
{
    std::string nodeTypeString = EMPTY_STR;
    auto it = ACCESSIBILITY_ROLE_CONVERT_PROPERTY_MAP.find(nodeTypeInt);
    if (it != ACCESSIBILITY_ROLE_CONVERT_PROPERTY_MAP.end()) {
        return ACCESSIBILITY_ROLE_CONVERT_PROPERTY_MAP[nodeTypeInt];
    }
    return nodeTypeString;
}

int32_t UnConvertAccessibilityRole(const std::string& nodeTypeString)
{
    int32_t nodeTypeInt = ERROR_CODE;
    auto it = ACCESSIBILITY_ROLE_CONVERT_NATIVE_MAP.find(nodeTypeString);
    if (it != ACCESSIBILITY_ROLE_CONVERT_NATIVE_MAP.end()) {
        return static_cast<int32_t>(ACCESSIBILITY_ROLE_CONVERT_NATIVE_MAP[nodeTypeString]);
    }
    return nodeTypeInt;
}

bool IsLeapYear(uint32_t year)
{
    return (year % NUM_4 == 0 && year % NUM_100 != 0) || (year % NUM_400 == 0);
}

bool IsValidDate(uint32_t year, uint32_t month, uint32_t day)
{
    if (year <= 0) {
        return false;
    }
    if (month < NUM_1 || month > NUM_12) {
        return false;
    }
    uint32_t daysInMonth[] = { 31, IsLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }
    return true;
}

int32_t CheckAttributeItemArray(const ArkUI_AttributeItem* item, int32_t requiredAtLeastSize)
{
    CHECK_NULL_RETURN(item, -1);
    if (item->size < requiredAtLeastSize) {
        return -1;
    }
    return item->size;
}

bool CheckAttributeIsBool(int32_t value)
{
    if (value == DEFAULT_FALSE || value == DEFAULT_TRUE) {
        return true;
    }
    return false;
}

bool CheckAttributeIsAlignment(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_Alignment::ARKUI_ALIGNMENT_TOP_START);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_Alignment::ARKUI_ALIGNMENT_BOTTOM_END);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsFontWeight(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_FontWeight::ARKUI_FONT_WEIGHT_W100);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_FontWeight::ARKUI_FONT_WEIGHT_REGULAR);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsFontStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_FontStyle::ARKUI_FONT_STYLE_ITALIC);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsTextHeightAdaptivePolicy(int32_t value)
{
    int32_t minEnumValue =
        static_cast<int32_t>(ArkUI_TextHeightAdaptivePolicy::ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_TextHeightAdaptivePolicy::ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsCopyOptions(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_CopyOptions::ARKUI_COPY_OPTIONS_NONE);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_CopyOptions::ARKUI_COPY_OPTIONS_CROSS_DEVICE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsAnimationCurve(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsScrollNestedMode(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_ScrollNestedMode::ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_ScrollNestedMode::ARKUI_SCROLL_NESTED_MODE_PARALLEL);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderStyle::ARKUI_SLIDER_STYLE_OUT_SET);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderStyle::ARKUI_SLIDER_STYLE_NONE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderBlockStyle(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderBlockStyle::ARKUI_SLIDER_BLOCK_STYLE_DEFAULT);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderBlockStyle::ARKUI_SLIDER_BLOCK_STYLE_SHAPE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsSliderDirection(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_SliderDirection::ARKUI_SLIDER_DIRECTION_VERTICAL);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_SliderDirection::ARKUI_SLIDER_DIRECTION_HORIZONTAL);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsDatePickerMode(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (item->size == 0) {
        return false;
    }
    int32_t value = item->value[0].i32;
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_DatePickerMode::ARKUI_DATEPICKER_MODE_DATE);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_DatePickerMode::ARKUI_DATEPICKER_MONTH_AND_DAY);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsCheckboxShape(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_CheckboxShape::ArkUI_CHECKBOX_SHAPE_CIRCLE);
    int32_t maxEnumValue = static_cast<int32_t>(ArkUI_CheckboxShape::ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsListItemAlign(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_ListItemAlignment::ARKUI_LIST_ITEM_ALIGNMENT_START);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_ListItemAlignment::ARKUI_LIST_ITEM_ALIGNMENT_END);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsAccessibilityLevel(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_AccessibilityMode::ARKUI_ACCESSIBILITY_MODE_AUTO);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_AccessibilityMode::ARKUI_ACCESSIBILITY_MODE_DISABLED_FOR_DESCENDANTS);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsChainStyle(int32_t value)
{
    int32_t minEnumValue =
        static_cast<int32_t>(ArkUI_RelativeLayoutChainStyle::ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_RelativeLayoutChainStyle::ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_PACKED);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeIsAxis(int32_t value)
{
    int32_t minEnumValue = static_cast<int32_t>(ArkUI_Axis::ARKUI_AXIS_VERTICAL);
    int32_t maxEnumValue =
        static_cast<int32_t>(ArkUI_Axis::ARKUI_AXIS_HORIZONTAL);
    return value >= minEnumValue && value <= maxEnumValue;
}

bool CheckAttributeString(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (!item->string) {
        return false;
    }
    return true;
}

bool CheckAttributeObject(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (!item->object) {
        return false;
    }
    return true;
}

bool CheckAttributeObjectAndSize(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (!item->object || item->size == 0) {
        return false;
    }
    return true;
}

bool ParseImages(const ArkUI_AttributeItem* item, ArkUIImageFrameInfo* imageInfos, ArkUI_NodeHandle node)
{
    auto images = reinterpret_cast<ArkUI_ImageAnimatorFrameInfo**>(item->object);
    if (!images) {
        return false;
    }
    for (int32_t i = 0; i < item->size; i++) {
        CHECK_NULL_RETURN(images[i], false);
        if (images[i]->drawableDescriptor) {
            if (images[i]->drawableDescriptor->drawableDescriptor) {
                imageInfos[i].drawable = images[i]->drawableDescriptor->drawableDescriptor.get();
            } else if (images[i]->drawableDescriptor->resource) {
                imageInfos[i].src = images[i]->drawableDescriptor->resource->src.c_str();
            }
        } else {
            imageInfos[i].src = images[i]->src.c_str();
        }
        imageInfos[i].width = images[i]->width.value_or(0);
        imageInfos[i].height = images[i]->height.value_or(0);
        imageInfos[i].top = images[i]->top.value_or(0);
        imageInfos[i].left = images[i]->left.value_or(0);
        imageInfos[i].unit = GetDefaultUnit(node, UNIT_PX);
        imageInfos[i].duration = images[i]->duration.value_or(0);
    }
    node->imageFrameInfos = images;
    return true;
}

bool CheckAttributeIndicator(const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, false);
    if (item->value[0].i32 != ARKUI_SWIPER_INDICATOR_TYPE_DOT &&
        item->value[0].i32 != ARKUI_SWIPER_INDICATOR_TYPE_DIGIT) {
        return false;
    }
    if (!item->object) {
        return false;
    }
    return true;
}

bool CheckAnimation(const ArkUI_AttributeItem* item, int32_t size, int32_t animationIndexBase)
{
    CHECK_NULL_RETURN(item, false);
    const int32_t animationCurveIndex = animationIndexBase + ANIMATION_CURVE_INDEX;
    if (animationCurveIndex < size &&
        (item->value[animationCurveIndex].i32 < 0 ||
            item->value[animationCurveIndex].i32 > static_cast<int32_t>(ARKUI_CURVE_FRICTION))) {
        return false;
    }
    const int32_t playModeIndex = animationIndexBase + ANIMATION_PLAY_MODE_INDEX;
    if (playModeIndex < size &&
        (item->value[playModeIndex].i32 < 0 ||
            item->value[playModeIndex].i32 > static_cast<int32_t>(ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE))) {
        return false;
    }
    const int32_t animationTempoIndex = animationIndexBase + ANIMATION_TEMPO_INDEX;
    if (animationTempoIndex < size && LessNotEqual(item->value[animationTempoIndex].f32, 0.0f)) {
        return false;
    }
    return true;
}

void ParseAnimation(const ArkUI_AttributeItem* item, int32_t actualSize, ArkUIAnimationOptionType& animationOption,
    const int animationIndexBase)
{
    const int32_t animationDurationIndex = animationIndexBase + ANIMATION_DURATION_INDEX;
    int32_t duration = DEFAULT_DURATION;
    if (animationDurationIndex < actualSize) {
        duration = item->value[animationDurationIndex].i32;
    }
    const int32_t animationCurveIndex = animationIndexBase + ANIMATION_CURVE_INDEX;
    int32_t curve = 0;
    if (animationCurveIndex < actualSize &&
        item->value[animationCurveIndex].i32 < static_cast<int32_t>(CURVE_ARRAY.size())) {
        curve = item->value[animationCurveIndex].i32;
    }
    const int32_t animationDelayIndex = animationIndexBase + ANIMATION_DELAY_INDEX;
    int32_t delay = 0;
    if (animationDelayIndex < actualSize) {
        delay = item->value[animationDelayIndex].i32;
    }
    const int32_t animationIterationsIndex = animationIndexBase + ANIMATION_INTERATION_INDEX;
    int32_t iterations = 1;
    if (animationIterationsIndex < actualSize) {
        iterations = item->value[animationIterationsIndex].i32;
    }
    const int32_t animationPlayModeIndex = animationIndexBase + ANIMATION_PLAY_MODE_INDEX;
    int32_t direction = 0;
    if (animationPlayModeIndex < actualSize) {
        direction = ConvertAnimationDirection(item->value[animationPlayModeIndex].i32);
    }
    const int32_t animationTempoIndex = animationIndexBase + ANIMATION_TEMPO_INDEX;
    float tempo = 1.0f;
    if (animationTempoIndex < actualSize) {
        tempo = item->value[animationTempoIndex].f32;
    }
    animationOption.duration = duration;
    animationOption.curve = curve;
    animationOption.delay = delay;
    animationOption.iteration = iterations;
    animationOption.playMode = direction;
    animationOption.tempo = tempo;
}

void ResetAnimation(ArkUIAnimationOptionType& animationOption)
{
    animationOption.duration = DEFAULT_DURATION;
    animationOption.curve = 0;
    animationOption.delay = 0;
    animationOption.iteration = 1;
    animationOption.playMode = 0;
    animationOption.tempo = 1.0f;
}

// Common Attributes functions
int32_t SetWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetWidth(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWidth(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getWidth(node->uiNodeHandle, GetDefaultUnit(node, UNIT_VP));
    if (LessNotEqual(g_numberValues[0].f32, 0.0f)) {
        return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetHeight(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetHeight(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetHeight(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getHeight(node->uiNodeHandle, GetDefaultUnit(node, UNIT_VP));
    if (LessNotEqual(g_numberValues[0].f32, 0.0f)) {
        return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->setButtonBackgroundColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputBackgroundColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBackgroundColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonBackgroundColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputBackgroundColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaBackgroundColor(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundColor(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetBackgroundColor(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].u32 = modifier->getBackgroundColor(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetBackgroundImage(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if ((!item->string && !item->object) || (item->string && item->object)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->size == NUM_1 &&
        (item->value[NUM_0].i32 < 0 || item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_IMAGE_REPEAT_XY))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    std::string bundle;
    std::string module;
    int repeat = item->size == NUM_1 ? item->value[NUM_0].i32 : ARKUI_IMAGE_REPEAT_NONE;
    if (item->string) {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImage(
            node->uiNodeHandle, item->string, bundle.c_str(), module.c_str(), repeat);
    } else {
        auto drawableDescriptor = reinterpret_cast<ArkUI_DrawableDescriptor*>(item->object);
        if (!drawableDescriptor->drawableDescriptor) {
            return ERROR_CODE_PARAM_INVALID;
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImagePixelMap(
            node->uiNodeHandle, drawableDescriptor->drawableDescriptor.get(), repeat);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImage(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImage(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBackgroundImage(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIBackgroundImage options;
    fullImpl->getNodeModifiers()->getCommonModifier()->getBackgroundImage(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.repeat;
    g_attributeItem.string = options.src;
    return &g_attributeItem;
}

int32_t SetPadding(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != NUM_1 && item->size != NUM_4) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int topIndex = NUM_0;
    int rightIndex = item->size == NUM_1 ? NUM_0 : NUM_1;
    int bottomIndex = item->size == NUM_1 ? NUM_0 : NUM_2;
    int leftIndex = item->size == NUM_1 ? NUM_0 : NUM_3;
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    struct ArkUISizeType top = { item->value[topIndex].f32, unit };
    struct ArkUISizeType right = { item->value[rightIndex].f32, unit };
    struct ArkUISizeType bottom = { item->value[bottomIndex].f32, unit };
    struct ArkUISizeType left = { item->value[leftIndex].f32, unit };
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPadding(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPadding(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setPadding(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetPadding(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPadding(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetPadding(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetPadding(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 paddings[NUM_4];
    ArkUI_Int32 length = 0;
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaPadding(
            node->uiNodeHandle, &paddings, length, unit);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->getPadding(node->uiNodeHandle, &paddings, length, unit);
    }
    g_numberValues[NUM_0].f32 = paddings[NUM_0];
    g_numberValues[NUM_1].f32 = paddings[NUM_1];
    g_numberValues[NUM_2].f32 = paddings[NUM_2];
    g_numberValues[NUM_3].f32 = paddings[NUM_3];
    return &g_attributeItem;
}

int32_t SetKey(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setKey(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetKey(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetKey(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetKey(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_attributeItem.string = modifier->getKey(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetEnabled(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setEnabled(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetEnabled(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetEnabled(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetEnabled(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getEnabled(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetMargin(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item || (item->size != NUM_4 && item->size != NUM_1)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUISizeType top, right, bottom, left;
    top.value = right.value = bottom.value = left.value = NUM_0;
    top.unit = right.unit = bottom.unit = left.unit = GetDefaultUnit(node, UNIT_VP);
    if (item->size == NUM_1) {
        top.value = right.value = bottom.value = left.value = item->value[NUM_0].f32;
    } else if (item->size == NUM_4) {
        top.value = item->value[NUM_0].f32;
        right.value = item->value[NUM_1].f32;
        bottom.value = item->value[NUM_2].f32;
        left.value = item->value[NUM_3].f32;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMargin(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMargin(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setMargin(node->uiNodeHandle, &top, &right, &bottom, &left);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputMargin(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaMargin(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetMargin(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetMargin(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 margins[NUM_4];
    ArkUI_Int32 length = 0;
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputMargin(
            node->uiNodeHandle, &margins, length, unit);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaMargin(
            node->uiNodeHandle, &margins, length, unit);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->getMargin(node->uiNodeHandle, &margins, length, unit);
    }
    g_numberValues[NUM_0].f32 = margins[NUM_0];
    g_numberValues[NUM_1].f32 = margins[NUM_1];
    g_numberValues[NUM_2].f32 = margins[NUM_2];
    g_numberValues[NUM_3].f32 = margins[NUM_3];
    return &g_attributeItem;
}

int32_t SetTranslate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_THREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[item->size];
    ArkUI_Int32 units[item->size];
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].f32;
        units[i] = unit;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslate(node->uiNodeHandle, values, units, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetTranslate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetTranslate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTranslate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 translate[NUM_3];
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->getTranslate(node->uiNodeHandle, &translate, unit);
    g_numberValues[NUM_0].f32 = translate[NUM_0];
    g_numberValues[NUM_1].f32 = translate[NUM_1];
    g_numberValues[NUM_2].f32 = translate[NUM_2];
    return &g_attributeItem;
}

int32_t SetScale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto fullImpl = GetFullImpl();

    if (item->size != NUM_5 && item->size != NUM_2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Float32 values[item->size];
    for (int i = 0; i < item->size; i++) {
        values[i] = item->value[i].f32;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Int32 units[NUM_2] = { unit, unit };
    fullImpl->getNodeModifiers()->getCommonModifier()->setScale(node->uiNodeHandle, values, item->size, units, NUM_2);
    return ERROR_CODE_NO_ERROR;
}

void ResetScale(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetScale(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScale(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIScaleType scaleType = { 0.0f, 0.0f };
    fullImpl->getNodeModifiers()->getCommonModifier()->getScale(node->uiNodeHandle, &scaleType);
    g_numberValues[NUM_0].f32 = scaleType.xValue;
    g_numberValues[NUM_1].f32 = scaleType.yValue;
    g_attributeItem.size = NUM_2;
    return &g_attributeItem;
}

int32_t SetRotate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].f32;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateWithoutTransformCenter(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetRotate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetRotate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRotate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIRotateType rotateType = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    fullImpl->getNodeModifiers()->getCommonModifier()->getRotate(node->uiNodeHandle, &rotateType);
    g_numberValues[NUM_0].f32 = rotateType.xCoordinate;
    g_numberValues[NUM_1].f32 = rotateType.yCoordinate;
    g_numberValues[NUM_2].f32 = rotateType.zCoordinate;
    g_numberValues[NUM_3].f32 = rotateType.angle;
    g_numberValues[NUM_4].f32 = rotateType.sightDistance;
    g_attributeItem.size = NUM_5;
    return &g_attributeItem;
}

int32_t SetBrightness(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto brightness = item->value[NUM_0].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBrightness(node->uiNodeHandle, brightness);
    return ERROR_CODE_NO_ERROR;
}

void ResetBrightness(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBrightness(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBrightness(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getCommonModifier()->getBrightness(node->uiNodeHandle);
    g_attributeItem.size = NUM_1;
    return &g_attributeItem;
}

int32_t SetSaturate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, DEFAULT_SIZE_50, item->value[NUM_0].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto saturate = item->value[NUM_0].f32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setSaturate(node->uiNodeHandle, saturate);
    return ERROR_CODE_NO_ERROR;
}

void ResetSaturate(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetSaturate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSaturate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getCommonModifier()->getSaturate(node->uiNodeHandle);
    g_attributeItem.size = NUM_1;
    return &g_attributeItem;
}

int32_t SetBlur(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float64 blur = item->value[NUM_0].f32;
    BlurOption blurOption;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlur(
        node->uiNodeHandle, blur, blurOption.grayscale.data(), blurOption.grayscale.size());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetBlur(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getBlur(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetBlur(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBlur(node->uiNodeHandle);
}

int32_t SetLinearGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size < NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    //save direction value in node;
    node->linearGradientDirection = item->value[NUM_1].i32;
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUIInt32orFloat32 colors[size * NUM_3];
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0].u32 = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1].i32 = true;
        colors[i * NUM_3 + NUM_2].f32 = colorStop->stops[i] < 0 ? 0 : colorStop->stops[i];
    }

    auto isCustomDirection = item->value[NUM_1].i32 == static_cast<ArkUI_Int32>(ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM);
    ArkUIInt32orFloat32 values[NUM_4] = {
        {.i32 = static_cast<ArkUI_Int32>(isCustomDirection)}, //angleHasValue
        {.f32 = item->value[NUM_0].f32}, //angleValue
        {.i32 = item->value[NUM_1].i32}, //directionValue
        {.i32 = item->value[NUM_2].i32}  //repeating
    };

    fullImpl->getNodeModifiers()->getCommonModifier()->setLinearGradient(
        node->uiNodeHandle, values, NUM_4, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetLinearGradient(ArkUI_NodeHandle node)
{
    //default size 3
    ArkUI_Float32 values[NUM_3];
    //default size 10
    ArkUI_Uint32 colors[NUM_10];
    //default size 10
    ArkUI_Float32 stops[NUM_10];
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getLinearGradient(
        node->uiNodeHandle, &values, &colors, &stops);
    //angle
    g_numberValues[0].f32 = values[0];
    //direction
    g_numberValues[1].i32 = node->linearGradientDirection > -1 ? node->linearGradientDirection : values[1];
    //repeated
    g_numberValues[2].i32 = values[2];
    //size
    g_attributeItem.size = NUM_3;
    if (resultValue < NUM_1) {
        return &g_attributeItem;
    }

    static ArkUI_ColorStop colorStop;
    static uint32_t gradientColors[NUM_10];
    static float gradientStops[NUM_10];
    for (int i = 0; i < resultValue; i++) {
        gradientColors[i] = colors[i];
        gradientStops[i] = stops[i] / 100.0f; //百分比转换为小数
    }
    colorStop.colors = gradientColors;
    colorStop.stops = gradientStops;
    colorStop.size = resultValue;
    g_attributeItem.object = &colorStop;
    return &g_attributeItem;
}

void ResetLinearGradient(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetLinearGradient(node->uiNodeHandle);
}

int32_t SetAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_8, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlign(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAlign(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAlign(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetAlign(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlign(node->uiNodeHandle);
}

int32_t SetOpacity(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacity(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetOpacity(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOpacity(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetOpacity(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getOpacity(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetBorderWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    float widthVals[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    int widthUnits[ALLOW_SIZE_4] = { unit, unit, unit, unit };

    if (item->size == 1) {
        if (LessNotEqual(item->value[0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = item->value[0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                widthVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderWidth(
            node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderWidth(
            node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaBorderWidth(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderWidth(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetBorderWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderWidth[NUM_4];
    auto unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderWidth(node->uiNodeHandle, &borderWidth, unit);
    g_numberValues[NUM_0].f32 = borderWidth[NUM_0];
    g_numberValues[NUM_1].f32 = borderWidth[NUM_1];
    g_numberValues[NUM_2].f32 = borderWidth[NUM_2];
    g_numberValues[NUM_3].f32 = borderWidth[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderRadius(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float radiusVals[ALLOW_SIZE_4] = { NUM_1, NUM_1, NUM_1, NUM_1 };
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    int radiusUnits[ALLOW_SIZE_4] = { unit, unit, unit, unit };

    if (item->size == 1) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[NUM_0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                radiusVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_IMAGE) {
        fullImpl->getNodeModifiers()->getImageModifier()->setImageBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    } else if (node->type == ARKUI_NODE_IMAGE_SPAN) {
        fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderRadius(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_IMAGE) {
        fullImpl->getNodeModifiers()->getImageModifier()->resetImageBorderRadius(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaBorderRadius(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_IMAGE_SPAN) {
        fullImpl->getNodeModifiers()->getImageSpanModifier()->resetImageSpanBorderRadius(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderRadius(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetBorderRadius(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderRadius[NUM_4];
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderRadius(node->uiNodeHandle, &borderRadius, unit);
    g_numberValues[NUM_0].f32 = borderRadius[NUM_0];
    g_numberValues[NUM_1].f32 = borderRadius[NUM_1];
    g_numberValues[NUM_2].f32 = borderRadius[NUM_2];
    g_numberValues[NUM_3].f32 = borderRadius[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderWidthPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float widthVals[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    int widthUnits[ALLOW_SIZE_4] = { UNIT_PERCENT, UNIT_PERCENT, UNIT_PERCENT, UNIT_PERCENT };

    if (item->size == 1) {
        if (LessNotEqual(item->value[0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            widthVals[i] = item->value[0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                widthVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderWidth(
            node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderWidth(
            node->uiNodeHandle, widthVals, widthUnits, ALLOW_SIZE_4);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderWidthPercent(ArkUI_NodeHandle node)
{
    ResetBorderWidth(node);
}

const ArkUI_AttributeItem* GetBorderWidthPercent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderWidth[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderWidth(node->uiNodeHandle, &borderWidth, UNIT_PERCENT);
    g_numberValues[NUM_0].f32 = borderWidth[NUM_0];
    g_numberValues[NUM_1].f32 = borderWidth[NUM_1];
    g_numberValues[NUM_2].f32 = borderWidth[NUM_2];
    g_numberValues[NUM_3].f32 = borderWidth[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderRadiusPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float radiusVals[ALLOW_SIZE_4] = { NUM_1, NUM_1, NUM_1, NUM_1 };
    int radiusUnits[ALLOW_SIZE_4] = { UNIT_PERCENT, UNIT_PERCENT, UNIT_PERCENT, UNIT_PERCENT };

    if (item->size == 1) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[NUM_0].f32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                radiusVals[i] = item->value[i].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_IMAGE) {
        fullImpl->getNodeModifiers()->getImageModifier()->setImageBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderRadius(
            node->uiNodeHandle, radiusVals, radiusUnits, ALLOW_SIZE_4);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderRadiusPercent(ArkUI_NodeHandle node)
{
    ResetBorderRadius(node);
}

const ArkUI_AttributeItem* GetBorderRadiusPercent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 borderRadius[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderRadius(node->uiNodeHandle, &borderRadius, UNIT_PERCENT);
    g_numberValues[NUM_0].f32 = borderRadius[NUM_0];
    g_numberValues[NUM_1].f32 = borderRadius[NUM_1];
    g_numberValues[NUM_2].f32 = borderRadius[NUM_2];
    g_numberValues[NUM_3].f32 = borderRadius[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    uint32_t colors[ALLOW_SIZE_4] = { DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR };
    if (item->size == 1) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[i] = item->value[0].u32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[i] = item->value[i].u32;
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderColor(
            node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderColor(
            node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaBorderColor(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderColor(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetBorderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Uint32 colors[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderColor(node->uiNodeHandle, &colors);
    g_numberValues[NUM_0].u32 = colors[NUM_0];
    g_numberValues[NUM_1].u32 = colors[NUM_1];
    g_numberValues[NUM_2].u32 = colors[NUM_2];
    g_numberValues[NUM_3].u32 = colors[NUM_3];
    return &g_attributeItem;
}

int32_t SetBorderStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int styles[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    if (item->size == 1) {
        if (item->value[0].i32 < ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID ||
            item->value[0].i32 > ArkUI_BorderStyle::ARKUI_BORDER_STYLE_DOTTED) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            styles[i] = item->value[0].i32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (item->value[i].i32 < ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID ||
                item->value[i].i32 > ArkUI_BorderStyle::ARKUI_BORDER_STYLE_DOTTED) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                styles[i] = item->value[i].i32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderStyle(
            node->uiNodeHandle, styles, ALLOW_SIZE_4);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setBorderStyle(node->uiNodeHandle, styles, ALLOW_SIZE_4);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBorderStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaBorderStyle(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetBorderStyle(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetBorderStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 styles[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getBorderStyle(node->uiNodeHandle, &styles);
    g_numberValues[NUM_0].i32 = styles[NUM_0];
    g_numberValues[NUM_1].i32 = styles[NUM_1];
    g_numberValues[NUM_2].i32 = styles[NUM_2];
    g_numberValues[NUM_3].i32 = styles[NUM_3];
    return &g_attributeItem;
}

int32_t SetZIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setZIndex(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetZIndex(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetZIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetZIndex(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getZIndex(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetVisibility(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_Visibility::ARKUI_VISIBILITY_VISIBLE ||
        item->value[0].i32 > ArkUI_Visibility::ARKUI_VISIBILITY_NONE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setVisibility(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetVisibility(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetVisibility(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetVisibility(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getVisibility(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetClip(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setClip(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetClip(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClip(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetClip(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getClip(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetClipShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_3, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    if (item->value[0].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_PATH) {
        if (item->string == nullptr) {
            return ERROR_CODE_PARAM_INVALID;
        }
        ArkUI_Float32 pathAttributes[NUM_2];
        if (LessNotEqual(item->value[NUM_1].f32, 0.0f) || LessNotEqual(item->value[NUM_2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            pathAttributes[NUM_0] = item->value[NUM_1].f32;
            pathAttributes[NUM_1] = item->value[NUM_2].f32;
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setClipPath(
            node->uiNodeHandle, "path", &pathAttributes, item->string, unit);
    } else {
        ArkUI_Float32 attributes[item->size - NUM_1];
        for (int i = NUM_1; i < item->size; i++) {
            if (LessNotEqual(item->value[i].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                attributes[i - NUM_1] = item->value[i].f32;
            }
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setClipShape(
            node->uiNodeHandle, ShapeToString(item->value[0].i32).c_str(), attributes, item->size - NUM_1, unit);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetClipShape(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClip(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetClipShape(ArkUI_NodeHandle node)
{
    ArkUIClipShapeOptions options;
    auto unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getClipShape(node->uiNodeHandle, &options, unit);
    int type = options.type;
    if (type == static_cast<ArkUI_Int32>(BasicShapeType::RECT)) {
        g_numberValues[NUM_0].i32 = static_cast<ArkUI_Int32>(ArkUI_ClipType::ARKUI_CLIP_TYPE_RECTANGLE);
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
        g_numberValues[NUM_3].f32 = options.radiusWidth;
        g_numberValues[NUM_4].f32 = options.radiusHeight;
        g_numberValues[NUM_5].f32 = options.topLeftRadius;
        g_numberValues[NUM_6].f32 = options.bottomLeftRadius;
        g_numberValues[NUM_7].f32 = options.topRightRadius;
        g_numberValues[NUM_8].f32 = options.bottomRightRadius;
    } else if (type == static_cast<ArkUI_Int32>(BasicShapeType::CIRCLE)) {
        g_numberValues[NUM_0].i32 = static_cast<ArkUI_Int32>(ArkUI_ClipType::ARKUI_CLIP_TYPE_CIRCLE);
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
    } else if (type == static_cast<ArkUI_Int32>(BasicShapeType::ELLIPSE)) {
        g_numberValues[NUM_0].i32 = static_cast<ArkUI_Int32>(ArkUI_ClipType::ARKUI_CLIP_TYPE_ELLIPSE);
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
    } else if (type == static_cast<ArkUI_Int32>(BasicShapeType::PATH)) {
        g_numberValues[NUM_0].i32 = static_cast<ArkUI_Int32>(ArkUI_ClipType::ARKUI_CLIP_TYPE_PATH);
        g_numberValues[NUM_1].f32 = options.width;
        g_numberValues[NUM_2].f32 = options.height;
        g_attributeItem.string = options.commands;
    } else {
        return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetTransform(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    float transforms[ALLOW_SIZE_16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    for (int i = 0; i < item->size; ++i) {
        transforms[i] = item->value[i].f32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransform(node->uiNodeHandle, transforms, ALLOW_SIZE_16);
    return ERROR_CODE_NO_ERROR;
}

void ResetTransform(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetTransform(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTransform(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[NUM_16];
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getTransform(node->uiNodeHandle, &values);
    for (int i = 0; i < NUM_16; i++) {
        g_numberValues[i].f32 = values[i];
    }
    return &g_attributeItem;
}

int32_t SetHitTestBehavior(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_HitTestMode::ARKUI_HIT_TEST_MODE_DEFAULT ||
        item->value[0].i32 > ArkUI_HitTestMode::ARKUI_HIT_TEST_MODE_NONE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setHitTestBehavior(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetHitTestBehavior(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetHitTestBehavior(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetHitTestBehavior(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getHitTestBehavior(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetPosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 && item->size != ALLOW_SIZE_2) {
        return ERROR_CODE_PARAM_INVALID;
    }

    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->setPosition(
        node->uiNodeHandle, item->value[0].f32, unit, item->value[1].f32, unit);
    return ERROR_CODE_NO_ERROR;
}

void ResetPosition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetPosition(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetPosition(ArkUI_NodeHandle node)
{
    ArkUIPositionOptions options;
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getPosition(node->uiNodeHandle, &options, unit);
    g_numberValues[NUM_0].f32 = options.x;
    g_numberValues[NUM_1].f32 = options.y;
    return &g_attributeItem;
}

int32_t SetShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS ||
        item->value[0].i32 > ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUIInt32orFloat32 shadows[NUM_1] = { {.i32 = ArkUI_ShadowStyle::ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS} };
    shadows[NUM_0].i32 = item->value[0].i32;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackShadow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetShadow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getShadow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetCustomShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUIInt32orFloat32 shadows[ALLOW_SIZE_7] = { 0, { .i32 = NUM_2 }, 0, 0, { .i32 = 0 }, { .u32 = 0 }, { .i32 = 0 } };
    int length = item->size;
    if (length > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_0].f32 = item->value[NUM_0].f32; // radius
    }
    if (length > NUM_2) {
        shadows[NUM_2].f32 = item->value[NUM_2].f32; // OffsetX
    }
    if (length > NUM_3) {
        shadows[NUM_3].f32 = item->value[NUM_3].f32; // OffsetY
    }
    if (length > NUM_4) {
        if (!InRegion(NUM_0, NUM_1, item->value[NUM_4].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_4].i32 = item->value[NUM_4].i32;
    }
    if (length > NUM_5) {
        if (item->value[NUM_1].i32) {
            if (!InRegion(NUM_0, NUM_2, item->value[NUM_5].i32)) {
                return ERROR_CODE_PARAM_INVALID;
            }
            shadows[NUM_1].i32 = COLOR_STRATEGY_STYLE;
            shadows[NUM_5].i32 = item->value[NUM_5].i32;
        } else {
            shadows[NUM_1].i32 = COLOR_STYLE;
            shadows[NUM_5].u32 = item->value[NUM_5].u32;
        }
    }
    if (length > NUM_6) {
        shadows[NUM_6].i32 = item->value[NUM_6].i32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackShadow(node->uiNodeHandle, shadows, ALLOW_SIZE_7);
    return ERROR_CODE_NO_ERROR;
}

void ResetCustomShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackShadow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetCustomShadow(ArkUI_NodeHandle node)
{
    ArkUICustomShadowOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getCustomShadow(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].f32 = options.radius;
    g_numberValues[NUM_1].i32 = options.colorStrategy;
    g_numberValues[NUM_2].f32 = options.offsetX;
    g_numberValues[NUM_3].f32 = options.offsetY;
    g_numberValues[NUM_4].i32 = options.shadowType;
    g_numberValues[NUM_5].u32 = options.color;
    g_numberValues[NUM_6].i32 = options.fill;
    return &g_attributeItem;
}

int32_t SetFocusable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusable(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetFocusable(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getFocusable(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetFocusable(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFocusable(node->uiNodeHandle);
}

int32_t SetAccessibilityGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityGroup(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityGroup(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityGroup(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetAccessibilityGroup(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityGroup(node->uiNodeHandle);
}

int32_t SetAccessibilityText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityText(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityText(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityText(node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetAccessibilityText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityText(node->uiNodeHandle);
}

int32_t SetAccessibilityLevel(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsAccessibilityLevel(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    auto levelString = ACCESSIBILITY_LEVEL_VECTOR[item->value[0].i32];
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityLevel(node->uiNodeHandle, levelString.c_str());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityLevel(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityLevel(
        node->uiNodeHandle);
    std::string levelString(resultValue);
    g_numberValues[0].i32 = ACCESSIBILITY_LEVEL_MAP[levelString];
    return &g_attributeItem;
}

void ResetAccessibilityLevel(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityLevel(node->uiNodeHandle);
}

int32_t SetAccessibilityDescription(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityDescription(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityDescription(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getAccessibilityDescription(node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetAccessibilityDescription(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityDescription(node->uiNodeHandle);
}

int32_t SetAccessibilityActions(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].u32 > 0b11111) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityActions(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetAccessibilityActions(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityActions(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetAccessibilityActions(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getCommonModifier()->getAccessibilityActions(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetAccessibilityRole(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::string nodeTypeString = ConvertAccessibilityRole(item->value[0].u32);
    if (nodeTypeString == EMPTY_STR) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityRole(
        node->uiNodeHandle, nodeTypeString.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetAccessibilityRole(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityRole(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetAccessibilityRole(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::string nodeTypeString = fullImpl->getNodeModifiers()->getCommonModifier()->getAccessibilityRole(
        node->uiNodeHandle);
    g_numberValues[0].u32 = static_cast<uint32_t>(UnConvertAccessibilityRole(nodeTypeString));
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetDefaultFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDefaultFocus(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetDefaultFocus(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getDefaultFocus(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetDefaultFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetDefaultFocus(node->uiNodeHandle);
}

int32_t SetResponseRegion(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size % NUM_4 > 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    std::vector<float> valuesArray;
    std::vector<int> unitsArray;

    for (int i = 0; i < item->size; i++) {
        int remainder = i % NUM_4;
        valuesArray.push_back(remainder > 1 ? (item->value[i].f32) / HUNDRED : item->value[i].f32);
        // unit 1 3
        unitsArray.push_back(remainder > 1 ? NUM_3 : NUM_1);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setResponseRegion(
        node->uiNodeHandle, valuesArray.data(), unitsArray.data(), valuesArray.size());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetResponseRegion(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[32];
    auto valueSize =
        GetFullImpl()->getNodeModifiers()->getCommonModifier()->getResponseRegion(node->uiNodeHandle, &values);
    for (int i = 0; i < valueSize; i++) {
        g_numberValues[i].f32 = values[i];
    }
    
    g_attributeItem.size = valueSize;
    return &g_attributeItem;
}

void ResetResponseRegion(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetResponseRegion(node->uiNodeHandle);
}

int32_t SetOverlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    ArkUI_Float32 values[ALLOW_SIZE_10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    if (item->size > 0) {
        values[0] = 1;
        if (!CheckAttributeIsAlignment(item->value[0].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        values[1] = item->value[0].i32;
    }

    if (item->size > 1) {
        values[2] = 1;
        values[3] = item->value[1].f32;
        values[NUM_4] = GetDefaultUnit(node, UNIT_VP);
    }

    if (item->size > 2) {
        values[5] = 1;
        values[6] = item->value[2].f32;
        values[NUM_7] = GetDefaultUnit(node, UNIT_VP);
    }
    values[8] = item->size > 0 ? 1 : 0;
    values[9] = item->size > 1 ? 1 : 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->setOverlay(
        node->uiNodeHandle, item->string, values, ALLOW_SIZE_10);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetOverlay(ArkUI_NodeHandle node)
{
    ArkUIOverlayOptions options;
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    auto contentStr = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getOverlay(
        node->uiNodeHandle, &options, unit);
    g_attributeItem.string = contentStr;
    int index = 0;
    //index 0 : align
    g_numberValues[index++].i32 = options.align;
    //index 1 : offset x
    g_numberValues[index++].f32 = options.x;
    //index 2 : offset y
    g_numberValues[index++].f32 = options.y;
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetOverlay(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOverlay(node->uiNodeHandle);
}

int32_t SetBackgroundImagePosition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 values[] = { item->value[NUM_0].f32, item->value[NUM_1].f32 };
    int32_t unit = GetDefaultUnit(node, UNIT_PX);
    ArkUI_Int32 units[] = { unit, unit };

    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImagePosition(
        node->uiNodeHandle, values, units, false, NUM_2);
    return ERROR_CODE_NO_ERROR;
}

void ResetBackgroundImagePosition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImagePosition(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBackgroundImagePosition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    ArkUIPositionOptions positionOption = { 0.0f, 0.0f };
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_PX);
    fullImpl->getNodeModifiers()->getCommonModifier()->getBackgroundImagePosition(node->uiNodeHandle,
        &positionOption, unit);
    g_numberValues[NUM_0].f32 = positionOption.x;
    g_numberValues[NUM_1].f32 = positionOption.y;
    g_attributeItem.size = NUM_2;
    return &g_attributeItem;
}

int32_t SetSweepGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUIInt32orFloat32 colors[size * NUM_3];
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0].u32 = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1].i32 = true;
        colors[i * NUM_3 + NUM_2].f32 = colorStop->stops[i];
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUIInt32orFloat32 values[NUM_13] = {
        {.i32 = static_cast<ArkUI_Int32>(false)},
        {.f32 = static_cast<ArkUI_Float32>(DEFAULT_X)},
        {.i32 = static_cast<ArkUI_Int32>(unit)},
        {.i32 = static_cast<ArkUI_Int32>(false)},
        {.f32 = static_cast<ArkUI_Float32>(DEFAULT_Y)},
        {.i32 = static_cast<ArkUI_Int32>(unit)},
        {.i32 = static_cast<ArkUI_Int32>(false)},
        {.f32 = static_cast<ArkUI_Float32>(NUM_0)},
        {.i32 = static_cast<ArkUI_Int32>(false)},
        {.f32 = static_cast<ArkUI_Float32>(NUM_0)},
        {.i32 = static_cast<ArkUI_Int32>(false)},
        {.f32 = static_cast<ArkUI_Float32>(NUM_0)},
        {.i32 = static_cast<ArkUI_Int32>(false)}};

    if (item->size > NUM_0) {
        values[NUM_0].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_1].f32 = item->value[NUM_0].f32;
    }

    if (item->size > NUM_1) {
        values[NUM_3].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_4].f32 = item->value[NUM_1].f32;
    }

    if (item->size > NUM_2) {
        values[NUM_6].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_7].f32 = item->value[NUM_2].f32;
    }

    if (item->size > NUM_3) {
        values[NUM_8].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_9].f32 = item->value[NUM_3].f32;
    }

    if (item->size > NUM_4) {
        values[NUM_10].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_11].f32 = item->value[NUM_4].f32;
    }

    values[NUM_12].i32 = item->size > NUM_5 ? item->value[NUM_5].i32 : static_cast<ArkUI_Int32>(true);

    fullImpl->getNodeModifiers()->getCommonModifier()->setSweepGradient(
        node->uiNodeHandle, values, NUM_13, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetSweepGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSweepGradient(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSweepGradient(ArkUI_NodeHandle node)
{
    //default size 6
    ArkUI_Float32 values[NUM_6];
    //default size 10
    ArkUI_Uint32 colors[NUM_10];
    //default size 10
    ArkUI_Float32 stops[NUM_10];
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getSweepGradient(
        node->uiNodeHandle, &values, &colors, &stops, unit);
    //centerX
    g_numberValues[NUM_0].f32 = values[NUM_0];
    //centerY
    g_numberValues[NUM_1].f32 = values[NUM_1];
    //startAngle
    g_numberValues[NUM_2].f32 = values[NUM_2];
    //endAngle
    g_numberValues[NUM_3].f32 = values[NUM_3];
    //rotation
    g_numberValues[NUM_4].f32 = values[NUM_4];
    //repeating
    g_numberValues[NUM_5].i32 = values[NUM_5];
    //size
    g_attributeItem.size = NUM_6;
    if (resultValue < NUM_1) {
        return &g_attributeItem;
    }

    static ArkUI_ColorStop colorStop;
    static uint32_t gradientColors[NUM_10];
    static float gradientStops[NUM_10];
    for (int i = 0; i < resultValue; i++) {
        gradientColors[i] = colors[i];
        gradientStops[i] = stops[i] / 100.0f; //百分比转换为小数
    }
    colorStop.colors = gradientColors;
    colorStop.stops = gradientStops;
    colorStop.size = resultValue;
    g_attributeItem.object = &colorStop;
    return &g_attributeItem;
}

int32_t SetRadialGradient(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    const ArkUI_ColorStop* colorStop = reinterpret_cast<ArkUI_ColorStop*>(item->object);
    int size = colorStop->size;
    ArkUIInt32orFloat32 colors[size * NUM_3];
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    for (int i = 0; i < size; i++) {
        colors[i * NUM_3 + NUM_0].u32 = colorStop->colors[i];
        colors[i * NUM_3 + NUM_1].i32 = true;
        colors[i * NUM_3 + NUM_2].f32 = colorStop->stops[i];
    }

    ArkUIInt32orFloat32 values[NUM_10] = {
        {.i32 = static_cast<ArkUI_Int32>(false) },
        {.f32 = static_cast<ArkUI_Float32>(DEFAULT_X) },
        {.i32 = static_cast<ArkUI_Float32>(unit) },
        {.i32 = static_cast<ArkUI_Int32>(false) },
        {.f32 = static_cast<ArkUI_Float32>(DEFAULT_Y) },
        {.i32 = static_cast<ArkUI_Float32>(unit) },
        {.i32 = static_cast<ArkUI_Int32>(false) },
        {.f32 = static_cast<ArkUI_Float32>(NUM_0) },
        {.i32 = static_cast<ArkUI_Float32>(unit) },
        {.i32 = static_cast<ArkUI_Int32>(false) }
    };

    if (item->size > NUM_0) {
        values[NUM_0].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_1].f32 = item->value[NUM_0].f32;
    }

    if (item->size > NUM_1) {
        values[NUM_3].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_4].f32 = item->value[NUM_1].f32;
    }

    if (item->size > NUM_2) {
        values[NUM_6].i32 = static_cast<ArkUI_Int32>(true);
        values[NUM_7].f32 = item->value[NUM_2].f32;
    }

    values[NUM_9].i32 = item->size > NUM_3 ? item->value[NUM_3].i32 : static_cast<ArkUI_Int32>(false);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRadialGradient(
        node->uiNodeHandle, values, NUM_10, colors, size * NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadialGradient(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetRadialGradient(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadialGradient(ArkUI_NodeHandle node)
{
    //default size 4
    ArkUI_Float32 values[NUM_4];
    //default size 10
    ArkUI_Uint32 colors[NUM_10];
    //default size 10
    ArkUI_Float32 stops[NUM_10];

    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getRadialGradient(
        node->uiNodeHandle, &values, &colors, &stops, unit);
    //centerX
    g_numberValues[NUM_0].f32 = values[NUM_0];
    //centerY
    g_numberValues[NUM_1].f32 = values[NUM_1];
    //radius
    g_numberValues[NUM_2].f32 = values[NUM_2];
    //repeating
    g_numberValues[NUM_3].i32 = values[NUM_3];
    //size
    g_attributeItem.size = NUM_3;
    if (resultValue < NUM_1) {
        return &g_attributeItem;
    }

    static ArkUI_ColorStop colorStop;
    static uint32_t gradientColors[NUM_10];
    static float gradientStops[NUM_10];
    for (int i = 0; i < resultValue; i++) {
        gradientColors[i] = colors[i];
        gradientStops[i] = stops[i] / 100.0f; //百分比转换为小数
    }
    colorStop.colors = gradientColors;
    colorStop.stops = gradientStops;
    colorStop.size = resultValue;
    g_attributeItem.object = &colorStop;
    return &g_attributeItem;
}

int32_t SetMask(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size < NUM_4) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    if (item->value[NUM_3].i32 == ArkUI_MaskType::ARKUI_MASK_TYPE_PATH) {
        if (item->string == nullptr) {
            return ERROR_CODE_PARAM_INVALID;
        }
        auto fill = item->size > NUM_0 ? item->value[0].u32 : DEFAULT_FIll_COLOR;
        auto stroke = item->size > NUM_1 ? item->value[NUM_1].u32 : DEFAULT_FIll_COLOR;
        float strokeWidth = item->size > NUM_2 ? item->value[NUM_2].f32 : NUM_0;
        ArkUI_Float32 pathAttributes[NUM_2];
        if (item->size < NUM_5 || LessNotEqual(item->value[NUM_4].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        pathAttributes[NUM_0] = item->value[NUM_4].f32; // path width
        if (item->size < NUM_6 || LessNotEqual(item->value[NUM_5].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        pathAttributes[NUM_1] = item->value[NUM_5].f32; // path height
        fullImpl->getNodeModifiers()->getCommonModifier()->setMaskPath(
            node->uiNodeHandle, "path", fill, stroke, strokeWidth, &pathAttributes, item->string, unit);
    } else if (item->value[0].i32 == ArkUI_MaskType::ARKUI_MASK_TYPE_PROGRESS) {
        ArkUI_Float32 progressAttributes[NUM_2];
        if (LessNotEqual(item->value[NUM_1].f32, 0.0f) || LessNotEqual(item->value[NUM_2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        progressAttributes[NUM_0] = item->value[NUM_1].f32; // value
        progressAttributes[NUM_1] = item->value[NUM_2].f32; // total
        uint32_t color = item->value[NUM_3].u32;
        fullImpl->getNodeModifiers()->getCommonModifier()->setProgressMask(
            node->uiNodeHandle, progressAttributes, color);
    } else {
        if (item->size < NUM_6) {
            return ERROR_CODE_PARAM_INVALID;
        }
        auto fill = item->size > NUM_0 ? item->value[0].u32 : DEFAULT_FIll_COLOR;
        auto stroke = item->size > NUM_1 ? item->value[NUM_1].u32 : DEFAULT_FIll_COLOR;
        float strokeWidth = item->size > NUM_2 ? item->value[NUM_2].f32 : NUM_0;
        auto index = item->size - NUM_4 < 0 ? 0 : item->size - NUM_4;
        ArkUI_Float32 attributes[index];
        for (int i = 0; i < index; i++) {
            if (LessNotEqual(item->value[i + NUM_4].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                attributes[i] = item->value[i + NUM_4].f32;
            }
        }
        fullImpl->getNodeModifiers()->getCommonModifier()->setMaskShape(node->uiNodeHandle,
            ShapeToString(item->value[NUM_3].i32).c_str(), fill, stroke, strokeWidth, attributes, item->size - NUM_4,
            unit);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetMask(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetMask(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetMask(ArkUI_NodeHandle node)
{
    ArkUIMaskOptions options;
    auto unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getMask(node->uiNodeHandle, &options, unit);
    CHECK_NULL_RETURN(&options, nullptr);
    if (options.type == static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_PROGRESS)) {
        g_numberValues[NUM_0].i32 = options.type;
        g_numberValues[NUM_1].f32 = options.value;
        g_numberValues[NUM_2].f32 = options.maxValue;
        g_numberValues[NUM_3].u32 = options.color;
        return &g_attributeItem;
    }
    switch (static_cast<BasicShapeType>(options.type)) {
        case BasicShapeType::RECT:
            g_numberValues[NUM_0].u32 = options.fill;
            g_numberValues[NUM_1].u32 = options.strokeColor;
            g_numberValues[NUM_2].f32 = options.strokeWidth;
            g_numberValues[NUM_3].i32 = static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_RECTANGLE);
            g_numberValues[NUM_4].f32 = options.width;
            g_numberValues[NUM_5].f32 = options.height;
            g_numberValues[NUM_6].f32 = options.radiusWidth;
            g_numberValues[NUM_7].f32 = options.radiusHeight;
            g_numberValues[NUM_8].f32 = options.topLeftRadius;
            g_numberValues[NUM_9].f32 = options.bottomLeftRadius;
            g_numberValues[NUM_10].f32 = options.topRightRadius;
            g_numberValues[NUM_11].f32 = options.bottomRightRadius;
            break;
        case BasicShapeType::CIRCLE:
            g_numberValues[NUM_0].u32 = options.fill;
            g_numberValues[NUM_1].u32 = options.strokeColor;
            g_numberValues[NUM_2].f32 = options.strokeWidth;
            g_numberValues[NUM_3].i32 = static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_CIRCLE);
            g_numberValues[NUM_4].f32 = options.width;
            g_numberValues[NUM_5].f32 = options.height;
            break;
        case BasicShapeType::ELLIPSE:
            g_numberValues[NUM_0].u32 = options.fill;
            g_numberValues[NUM_1].u32 = options.strokeColor;
            g_numberValues[NUM_2].f32 = options.strokeWidth;
            g_numberValues[NUM_3].i32 = static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_ELLIPSE);
            g_numberValues[NUM_4].f32 = options.width;
            g_numberValues[NUM_5].f32 = options.height;
            break;
        case BasicShapeType::PATH:
            g_numberValues[NUM_0].u32 = options.fill;
            g_numberValues[NUM_1].u32 = options.strokeColor;
            g_numberValues[NUM_2].f32 = options.strokeWidth;
            g_numberValues[NUM_3].i32 = static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_PATH);
            g_numberValues[NUM_4].f32 = options.width;
            g_numberValues[NUM_5].f32 = options.height;
            g_attributeItem.string = options.commands;
            break;
        default:
            return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetBlendMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_29, item->value[NUM_0].i32) || !InRegion(NUM_0, NUM_1, item->value[NUM_1].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    int blendMode = item->value[0].i32;
    int blendApplyType = NUM_0;
    if (item->size > NUM_1) {
        blendApplyType = item->value[1].i32;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBlendMode(node->uiNodeHandle, blendMode, blendApplyType);
    return ERROR_CODE_NO_ERROR;
}

void ResetBlendMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBlendMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBlendMode(ArkUI_NodeHandle node)
{
    ArkUIBlendModeOptions options;
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getBlendMode(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.blendMode;
    g_numberValues[NUM_1].i32 = options.blendApplyType;
    return &g_attributeItem;
}

int32_t SetDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_Direction::ARKUI_DIRECTION_LTR ||
        item->value[0].i32 > ArkUI_Direction::ARKUI_DIRECTION_AUTO) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDirection(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDirection(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetDirection(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDirection(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getDirection(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetAlignSelf(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_ItemAlignment::ARKUI_ITEM_ALIGNMENT_AUTO ||
        item->value[0].i32 > ArkUI_ItemAlignment::ARKUI_ITEM_ALIGNMENT_BASELINE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlignSelf(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignSelf(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlignSelf(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetAlignSelf(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getAlignSelf(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexGrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexGrow(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexGrow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexGrow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexGrow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexGrow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexShrink(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexShrink(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexShrink(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexShrink(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexShrink(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexShrink(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetFlexBasis(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    struct ArkUIStringAndFloat basis = { item->value[0].f32, nullptr };
    fullImpl->getNodeModifiers()->getCommonModifier()->setFlexBasis(node->uiNodeHandle, &basis);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexBasis(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFlexBasis(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexBasis(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getFlexBasis(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetConstraintSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || item->size != ALLOW_SIZE_4) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 constraintSize[ALLOW_SIZE_4] = { 0.0f, FLT_MAX, 0.0f, FLT_MAX };
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Int32 units[ALLOW_SIZE_4] = { unit, unit, unit, unit };

    for (int i = 0; i < ALLOW_SIZE_4; ++i) {
        if (LessNotEqual(item->value[i].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            constraintSize[i] = item->value[i].f32;
        }
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setConstraintSize(node->uiNodeHandle, constraintSize, units);
    return ERROR_CODE_NO_ERROR;
}

void ResetConstraintSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetConstraintSize(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetConstraintSize(ArkUI_NodeHandle node)
{
    ArkUIConstraintSizeOptions options;
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getConstraintSize(node->uiNodeHandle, &options, unit);
    g_numberValues[NUM_0].f32 = options.minWidth;
    g_numberValues[NUM_1].f32 = options.maxWidth;
    g_numberValues[NUM_2].f32 = options.minHeight;
    g_numberValues[NUM_3].f32 = options.maxHeight;
    return &g_attributeItem;
}

int32_t SetGrayscale(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setGrayscale(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetGrayscale(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetGrayscale(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGrayscale(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getGrayScale(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetInvert(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Float32 invert[] = { item->value[0].f32 };
    fullImpl->getNodeModifiers()->getCommonModifier()->setInvert(node->uiNodeHandle, invert, NUM_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetInvert(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetInvert(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetInvert(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getInvert(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSepia(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setSepia(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSepia(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSepia(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSepia(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getSepia(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetContrast(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatOrEqual(item->value[0].f32, 10.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setContrast(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetContrast(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetContrast(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetContrast(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getContrast(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetForegroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    bool isColor = true;
    if (item->string) {
        if (std::strcmp(item->string, COLORING_STRATEGY) == 0) {
            isColor = false;
            fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
                node->uiNodeHandle, isColor, static_cast<uint32_t>(ForegroundColorStrategy::INVERT));
            return ERROR_CODE_NO_ERROR;
        }
        if (std::strcmp(item->string, COLOR_MARKERS) == 0 && item->size > 0) {
            isColor = true;
            fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
                node->uiNodeHandle, isColor, item->value[0].u32);
            return ERROR_CODE_NO_ERROR;
        }
    }
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_INVERT ||
        item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_AVERAGE ||
        item->value[0].i32 == ArkUI_ColorStrategy::ARKUI_COLOR_STRATEGY_PRIMARY) {
        isColor = false;
        fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
            node->uiNodeHandle, isColor, item->value[0].i32);
    } else {
        isColor = true;
        fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundColor(
            node->uiNodeHandle, isColor, item->value[0].u32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetForegroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetForegroundColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetForegroundColor(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].u32 = modifier->getForegroundColor(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetNeedFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->setNeedFocus(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetNeedFocus(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getNeedFocus(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetAspectRatio(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAspectRatio(node->uiNodeHandle, item->value[NUM_0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetAspectRatio(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAspectRatio(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetAspectRatio(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getAspectRatio(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetLayoutWeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setLayoutWeight(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLayoutWeight(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetLayoutWeight(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetLayoutWeight(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].u32 = static_cast<uint32_t>(modifier->getLayoutWeight(node->uiNodeHandle));
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetDisplayPriority(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDisplayPriority(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDisplayPriority(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setDisplayPriority(node->uiNodeHandle, 0);
}

const ArkUI_AttributeItem* GetDisplayPriority(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    if (!modifier) {
        return nullptr;
    }
    g_numberValues[0].u32 = static_cast<uint32_t>(modifier->getDisplayPriority(node->uiNodeHandle));
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetOutlineWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setOutlineWidthFloat(node->uiNodeHandle,
        item->value[OUTLINE_LEFT_WIDTH_INDEX].f32, item->value[OUTLINE_TOP_WIDTH_INDEX].f32,
        item->value[OUTLINE_RIGHT_WIDTH_INDEX].f32, item->value[OUTLINE_BOTTOM_WIDTH_INDEX].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetOutlineWidth(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setOutlineWidthFloat(node->uiNodeHandle,
        0.0f, 0.0f, 0.0f, 0.0f);
}

const ArkUI_AttributeItem* GetOutlineWidth(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    if (!modifier) {
        return nullptr;
    }
    std::array<float, REQUIRED_FOUR_PARAM> outlineWidthArray;
    modifier->getOutlineWidthFloat(node->uiNodeHandle, &outlineWidthArray[0], REQUIRED_FOUR_PARAM);
    g_numberValues[OUTLINE_LEFT_WIDTH_INDEX].f32 = outlineWidthArray[OUTLINE_LEFT_WIDTH_INDEX];
    g_numberValues[OUTLINE_TOP_WIDTH_INDEX].f32 = outlineWidthArray[OUTLINE_TOP_WIDTH_INDEX];
    g_numberValues[OUTLINE_RIGHT_WIDTH_INDEX].f32 = outlineWidthArray[OUTLINE_RIGHT_WIDTH_INDEX];
    g_numberValues[OUTLINE_BOTTOM_WIDTH_INDEX].f32 = outlineWidthArray[OUTLINE_BOTTOM_WIDTH_INDEX];
    g_attributeItem.size = REQUIRED_FOUR_PARAM;
    return &g_attributeItem;
}

int32_t SetGeometryTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIGeometryTransitionOptions options;
    ArkUI_Bool follow = false;
    if (item->size == 1) {
        follow = item->value[0].i32;
    }
    options.follow = follow;
    options.hierarchyStrategy = static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE);

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setGeometryTransition(node->uiNodeHandle, item->string,
        &options);
    return ERROR_CODE_NO_ERROR;
}

void ResetGeometryTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetGeometryTransition(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGeometryTransition(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    if (!modifier) {
        return nullptr;
    }
    ArkUIGeometryTransitionOptions options;
    g_attributeItem.string = modifier->getGeometryTransition(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.follow;
    g_numberValues[NUM_1].i32 = options.hierarchyStrategy;
    return &g_attributeItem;
}

int32_t SetChainMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0 || !CheckAttributeIsAxis(item->value[0].i32) ||
        !CheckAttributeIsChainStyle(item->value[1].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    //index 0 direction  index 1 style
    fullImpl->getNodeModifiers()->getCommonModifier()->setChainStyle(
        node->uiNodeHandle, item->value[0].i32, item->value[1].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetChainMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetChainStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetChainMode(ArkUI_NodeHandle node)
{
    //size = 2; direction and style
    ArkUI_Int32 values[ALLOW_SIZE_2];
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getChainStyle(node->uiNodeHandle, &values);
    //index 0 direction
    g_numberValues[0].i32 = values[0];
    //index 1 style
    g_numberValues[1].i32 = values[1];
    g_attributeItem.size = ALLOW_SIZE_2;
    
    return &g_attributeItem;
}

int32_t SetWidthPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setWidth(
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_PERCENT, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetWidthPercent(ArkUI_NodeHandle node)
{
    ResetWidth(node);
}

const ArkUI_AttributeItem* GetWidthPercent(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getWidth(node->uiNodeHandle, UNIT_PERCENT);
    if (LessNotEqual(g_numberValues[0].f32, 0.0f)) {
        return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetHeightPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setHeight(
        node->uiNodeHandle, item->value[NUM_0].f32, UNIT_PERCENT, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetHeightPercent(ArkUI_NodeHandle node)
{
    ResetHeight(node);
}

const ArkUI_AttributeItem* GetHeightPercent(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].f32 = modifier->getHeight(node->uiNodeHandle, UNIT_PERCENT);
    if (LessNotEqual(g_numberValues[0].f32, 0.0f)) {
        return nullptr;
    }
    return &g_attributeItem;
}

int32_t SetPaddingPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != NUM_1 && item->size != NUM_4) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int topIndex = NUM_0;
    int rightIndex = item->size == NUM_1 ? NUM_0 : NUM_1;
    int bottomIndex = item->size == NUM_1 ? NUM_0 : NUM_2;
    int leftIndex = item->size == NUM_1 ? NUM_0 : NUM_3;
    struct ArkUISizeType top = { item->value[topIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType right = { item->value[rightIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType bottom = { item->value[bottomIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType left = { item->value[leftIndex].f32, UNIT_PERCENT };
    fullImpl->getNodeModifiers()->getCommonModifier()->setPadding(node->uiNodeHandle, &top, &right, &bottom, &left);
    return ERROR_CODE_NO_ERROR;
}

void ResetPaddingPercent(ArkUI_NodeHandle node)
{
    ResetPadding(node);
}

const ArkUI_AttributeItem* GetPaddingPercent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 paddings[NUM_4];
    ArkUI_Int32 length = 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->getPadding(node->uiNodeHandle, &paddings, length, UNIT_PERCENT);
    g_numberValues[NUM_0].f32 = paddings[NUM_0];
    g_numberValues[NUM_1].f32 = paddings[NUM_1];
    g_numberValues[NUM_2].f32 = paddings[NUM_2];
    g_numberValues[NUM_3].f32 = paddings[NUM_3];
    return &g_attributeItem;
}

int32_t SetMarginPercent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item || (item->size != NUM_4 && item->size != NUM_1)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int topIndex = NUM_0;
    int rightIndex = item->size == NUM_1 ? NUM_0 : NUM_1;
    int bottomIndex = item->size == NUM_1 ? NUM_0 : NUM_2;
    int leftIndex = item->size == NUM_1 ? NUM_0 : NUM_3;
    struct ArkUISizeType top = { item->value[topIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType right = { item->value[rightIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType bottom = { item->value[bottomIndex].f32, UNIT_PERCENT };
    struct ArkUISizeType left = { item->value[leftIndex].f32, UNIT_PERCENT };
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMargin(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMargin(
            node->uiNodeHandle, &top, &right, &bottom, &left);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setMargin(node->uiNodeHandle, &top, &right, &bottom, &left);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetMarginPercent(ArkUI_NodeHandle node)
{
    ResetMargin(node);
}

const ArkUI_AttributeItem* GetMarginPercent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 margins[NUM_4];
    ArkUI_Int32 length = 0;
    fullImpl->getNodeModifiers()->getCommonModifier()->getMargin(node->uiNodeHandle, &margins, length, UNIT_PERCENT);
    g_numberValues[NUM_0].f32 = margins[NUM_0];
    g_numberValues[NUM_1].f32 = margins[NUM_1];
    g_numberValues[NUM_3].f32 = margins[NUM_3];
    return &g_attributeItem;
}

int32_t SetRenderFit(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 ||
        item->value[NUM_0].i32 < ArkUI_RenderFit::ARKUI_RENDER_FIT_CENTER ||
        item->value[NUM_0].i32 > ArkUI_RenderFit::ARKUI_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_XCOMPONENT) {
        fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentRenderFit(node->uiNodeHandle, item->value[NUM_0].i32);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->setRenderFit(node->uiNodeHandle, item->value[NUM_0].i32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetRenderFit(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_XCOMPONENT) {
        fullImpl->getNodeModifiers()->getXComponentModifier()->resetXComponentRenderFit(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getCommonModifier()->resetRenderFit(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetRenderFit(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getCommonModifier();
    g_numberValues[0].i32 = modifier->getRenderFit(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetOutlineColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    uint32_t colors[ALLOW_SIZE_8] = { DEFAULT_TRUE, DEFAULT_COLOR, DEFAULT_TRUE, DEFAULT_COLOR,
        DEFAULT_TRUE, DEFAULT_COLOR, DEFAULT_TRUE, DEFAULT_COLOR };
    if (item->size == 1) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[NUM_2 * i + NUM_1] = item->value[0].u32;
        }
    } else if (item->size == ALLOW_SIZE_4) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            colors[NUM_2 * i + NUM_1] = item->value[i].u32;
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getCommonModifier()->setOutlineColor(
        node->uiNodeHandle, colors, ALLOW_SIZE_8);
    return ERROR_CODE_NO_ERROR;
}

void ResetOutlineColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOutlineColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetOutlineColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Uint32 colors[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getOutlineColor(node->uiNodeHandle, &colors);
    g_numberValues[NUM_0].u32 = colors[NUM_0];
    g_numberValues[NUM_1].u32 = colors[NUM_1];
    g_numberValues[NUM_2].u32 = colors[NUM_2];
    g_numberValues[NUM_3].u32 = colors[NUM_3];
    return &g_attributeItem;
}

int32_t SetSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size <= NUM_0 || item->size > NUM_2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Float32 size[NUM_2] = { ZERO_F, ZERO_F };
    for (auto i = 0; i < item->size; ++i) {
        size[i] = item->value[i].f32;
    }
    ArkUI_Int32 unit[NUM_2];
    unit[NUM_0] = GetDefaultUnit(node, UNIT_VP);
    unit[NUM_1] = GetDefaultUnit(node, UNIT_VP);
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    // 1 for vp. check in DimensionUnit.
    fullImpl->getNodeModifiers()->getCommonModifier()->setSize(
        node->uiNodeHandle, size, unit, nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetSize(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 size[NUM_2];
    fullImpl->getNodeModifiers()->getCommonModifier()->getSize(
        node->uiNodeHandle, &size, GetDefaultUnit(node, UNIT_VP));
    g_numberValues[NUM_0].f32 = size[NUM_0];
    g_numberValues[NUM_1].f32 = size[NUM_1];
    return &g_attributeItem;
}

int32_t SetRenderGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setRenderGroup(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetRenderGroup(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetRenderGroup(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRenderGroup(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getRenderGroup(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetColorBlend(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != NUM_1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setColorBlend(
        node->uiNodeHandle, item->value[NUM_0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetColorBlend(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetColorBlend(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetColorBlend(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getColorBlend(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

int32_t SetExpandSafeArea(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Uint32 safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    ArkUI_Uint32 safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    if (item->size > 0 && item->value[0].u32 > 0) {
        if (item->value[0].u32 > NUM_7) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            safeAreaType = item->value[0].u32;
        }
    } else {
        safeAreaType = NG::SAFE_AREA_TYPE_ALL;
    }
    if (item->size > NUM_1 && item->value[1].u32 > 0) {
        if (item->value[1].u32 > NUM_15) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            safeAreaEdge = item->value[1].u32;
        }
    } else {
        safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
    }
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->setExpandSafeArea(
        node->uiNodeHandle, safeAreaType, safeAreaEdge);
    return ERROR_CODE_NO_ERROR;
}

void ResetExpandSafeArea(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetExpandSafeArea(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetExpandSafeArea(ArkUI_NodeHandle node)
{
    ArkUI_Uint32 values[NUM_2];
    GetFullImpl()->getNodeModifiers()->getCommonModifier()->getExpandSafeArea(node->uiNodeHandle, &values);
    g_numberValues[NUM_0].u32 = values[NUM_0];
    g_numberValues[NUM_1].u32 = values[NUM_1];
    return &g_attributeItem;
}

int32_t SetTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto fullImpl = GetFullImpl();
    node->transitionOption = item->object;
    auto effectOption = reinterpret_cast<ArkUI_TransitionEffect*>(item->object);
    auto toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(effectOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransition(node->uiNodeHandle, toEffectOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetFocusBox(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_FP);
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusBoxStyle(
        node->uiNodeHandle, item->value[0].f32, unit, item->value[1].f32, unit, item->value[2].u32, NUM_7);
    return ERROR_CODE_NO_ERROR;
}

void ResetFocusBox(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFocusBoxStyle(node->uiNodeHandle);
}

int32_t SetClickDistance(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setClickDistance(
        node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetClickDistance(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetClickDistance(node->uiNodeHandle);
}

int32_t SetTabStop(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        fullImpl->getNodeModifiers()->getCommonModifier()->setTabStop(node->uiNodeHandle, false);
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTabStop(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetTabStop(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetTabStop(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTabStop(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getTabStop(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTransition(ArkUI_NodeHandle node)
{
    g_attributeItem.object = node->transitionOption;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetUniqueID(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getNodeUniqueId(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

// Text
int32_t SetFontColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontColor(
                node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontColor(node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontColor(node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_BUTTON:
            fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontColor(
                node->uiNodeHandle, item->value[0].u32);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontColor(
                node->uiNodeHandle, item->value[0].u32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanFontColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonFontColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontColor(node->uiNodeHandle);
    }
}

int32_t SetFontWeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0 ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontWeight(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontWeight(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontWeight(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_BUTTON:
            fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontWeightEnum(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontWeight(
                node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontWeight(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontWeight(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontWeight(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanFontWeight(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonFontWeight(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontWeight(node->uiNodeHandle);
    }
}

int32_t SetImmutableFontWeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0 ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setImmutableFontWeight(node->uiNodeHandle, item->value[0].i32);
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_PARAM_INVALID;
}

int32_t SetFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_FP);
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        struct ArkUILengthType fontSize = { nullptr, item->value[0].f32, unit };
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontSize(node->uiNodeHandle, &fontSize);
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setFontSize(node->uiNodeHandle, item->value[0].f32, unit);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontSize(
            node->uiNodeHandle, item->value[0].f32, unit);
    } else if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontSize(node->uiNodeHandle,
            item->value[0].f32, unit);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        struct ArkUIResourceLength fontSize = { item->value[0].f32, unit, nullptr };
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontSize(node->uiNodeHandle, &fontSize);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_BUTTON) {
        fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontSize(node->uiNodeHandle);
    }
}

int32_t SetFontStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0 ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontStyle(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setFontStyle(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontStyle(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontStyle(
                node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetFontStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetFontStyle(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontStyle(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanFontStyle(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontStyle(node->uiNodeHandle);
    }
}

int32_t SetTextInputPlaceholder(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputPlaceholder(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputPlaceholder(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetTextInputPlaceholder(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(node->uiNodeHandle, "");
}

int32_t SetTextInputText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputText(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputText(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetTextInputText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextString(node->uiNodeHandle, "");
}

int32_t SetCaretColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaCaretColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCaretColor(ArkUI_NodeHandle node)
{
    uint32_t resultValue = DEFAULT_COLOR;
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputCaretColor(
            node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaCaretColor(
            node->uiNodeHandle);
    }
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCaretColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaCaretColor(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetCaretStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaret(
        node->uiNodeHandle, item->value[NUM_0].f32, unit);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCaretStyle(ArkUI_NodeHandle node)
{
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputCaretStyle(
        node->uiNodeHandle, unit);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetCaretStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCaretStyle(node->uiNodeHandle);
}

int32_t SetShowUnderline(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetShowUnderline(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputShowUnderline(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetShowUnderline(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(node->uiNodeHandle);
}

int32_t SetMaxLength(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMaxLength(
            node->uiNodeHandle, item->value[NUM_0].i32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMaxLength(
            node->uiNodeHandle, item->value[NUM_0].i32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetMaxLength(ArkUI_NodeHandle node)
{
    float resultValue = NUM_0;
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputMaxLength(
            node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaMaxLength(
            node->uiNodeHandle);
    }
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetMaxLength(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLength(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetEnterKeyType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < static_cast<int32_t>(ARKUI_ENTER_KEY_TYPE_GO) ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_ENTER_KEY_TYPE_NEW_LINE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetEnterKeyType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputEnterKeyType(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetEnterKeyType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(node->uiNodeHandle);
}

int32_t SetPlaceholderColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderColor(
            node->uiNodeHandle, item->value[NUM_0].u32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetPlaceholderColor(ArkUI_NodeHandle node)
{
    uint32_t resultValue = DEFAULT_COLOR;
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputPlaceholderColor(
            node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaPlaceholderColor(
            node->uiNodeHandle);
    }
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetPlaceholderColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetTextInputPlaceholderFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    struct ArkUIResourceLength size = { 16.0, GetDefaultUnit(node, UNIT_FP) };
    int weight = ARKUI_FONT_WEIGHT_NORMAL;
    int style = ARKUI_FONT_STYLE_NORMAL;
    if (item->size > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        size.value = item->value[NUM_0].f32;
    }
    if (item->size > NUM_1) {
        if (item->value[NUM_1].i32 < 0 || item->value[NUM_1].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        style = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        if (item->value[NUM_2].i32 < 0 || item->value[NUM_2].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        weight = item->value[NUM_2].i32;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPlaceholderFontEnum(
        node->uiNodeHandle, &size, weight, item->string, style);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputPlaceholderFont(ArkUI_NodeHandle node)
{
    ArkUITextFont font;
    font.fontSizeUnit = GetDefaultUnit(node, UNIT_FP);
    GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputPlaceholderFont(
        node->uiNodeHandle, &font);
    int index = 0;
    g_numberValues[index++].f32 = font.fontSize;
    g_numberValues[index++].i32 = font.fontStyle;
    g_numberValues[index++].i32 = font.fontWeight;
    g_attributeItem.size = index;
    g_attributeItem.string = font.fontFamilies;
    return &g_attributeItem;
}

void ResetTextInputPlaceholderFont(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderFont(node->uiNodeHandle);
}

int32_t SetEnableKeyboardOnFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetEnableKeyboardOnFocus(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputRequestKeyboardOnFocus(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetEnableKeyboardOnFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnableKeyboardOnFocus(node->uiNodeHandle);
}

int32_t SetTextInputType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[NUM_0].i32 < static_cast<int32_t>(ARKUI_TEXTINPUT_TYPE_NORMAL) ||
        item->value[NUM_0].i32 > static_cast<int32_t>(ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputType(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputType(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetTextInputType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputType(node->uiNodeHandle);
}

int32_t SetSelectedBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSelectedBackgroundColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputSelectedBackgroundColor(
        node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSelectedBackgroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(node->uiNodeHandle);
}

int32_t SetShowPasswordIcon(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetShowPasswordIcon(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputShowPasswordIcon(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetShowPasswordIcon(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(node->uiNodeHandle);
}

int32_t StopTextInputEditing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_0].i32 == 0) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->stopTextInputTextEditing(node->uiNodeHandle);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputEditing(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputEditing(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetTextInputCancelButton(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(static_cast<int32_t>(ARKUI_CANCELBUTTON_STYLE_CONSTANT),
        static_cast<int32_t>(ARKUI_CANCELBUTTON_STYLE_INPUT), item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    struct ArkUISizeType size = { -1.0f, GetDefaultUnit(node, UNIT_VP) };
    auto* fullImpl = GetFullImpl();
    if (item->size > NUM_1) {
        size.value = item->value[NUM_1].f32;
    } else {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCancelSymbolIcon(node->uiNodeHandle,
        item->value[NUM_0].i32, nullptr);
        return ERROR_CODE_NO_ERROR;
    }
    uint32_t color = DEFAULT_COLOR;
    if (item->size > NUM_2) {
        color = item->value[NUM_2].u32;
    }
    std::string str = "";
    if (item->string) {
        str.assign(item->string);
    }
    
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCancelButton(node->uiNodeHandle,
        item->value[NUM_0].i32, &size, color, str.c_str());
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputCancelButton(ArkUI_NodeHandle node)
{
    int index = 0;
    g_numberValues[index++].i32 =
        GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputCancelButtonStyle(node->uiNodeHandle);
    g_numberValues[index++].f32 =
        GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputCancelIconSize(
            node->uiNodeHandle, GetDefaultUnit(node, UNIT_VP));
    g_numberValues[index++].u32 =
        GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputTextCancelIconColor(node->uiNodeHandle);
    g_attributeItem.size = index;
    g_attributeItem.string =
        GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputTextCancelIconSrc(node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetTextInputCancelButton(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCancelButton(node->uiNodeHandle);
}

int32_t SetTextInputTextSelection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[NUM_0].i32 > item->value[NUM_1].i32) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextSelection(
        node->uiNodeHandle, item->value[NUM_0].i32, item->value[NUM_1].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputTextSelection(ArkUI_NodeHandle node)
{
    g_numberValues[0].i32 = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputTextSelectionIndex(
        node->uiNodeHandle, false);
    g_numberValues[1].i32 = GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputTextSelectionIndex(
        node->uiNodeHandle, true);
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

void ResetTextInputTextSelection(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextSelection(node->uiNodeHandle, NUM_0, NUM_0);
}

int32_t SetTextInputSelectionMenuHidden(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectionMenuHidden(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputSelectionMenuHidden(ArkUI_NodeHandle node)
{
    g_numberValues[0].i32 =
        GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputSelectionMenuHidden(node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetTextInputSelectionMenuHidden(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuHidden(node->uiNodeHandle);
}

int32_t SetTextInputUnderlineColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Uint32 values[NUM_4];
    values[NUM_0] = item->value[NUM_0].u32;
    values[NUM_1] = item->value[NUM_1].u32;
    values[NUM_2] = item->value[NUM_2].u32;
    values[NUM_3] = item->value[NUM_3].u32;
    ArkUI_Bool hasValues[NUM_4] = { 1, 1, 1, 1 };
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputUserUnderlineColor(
        node->uiNodeHandle, values, hasValues, NUM_4);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputUnderlineColor(ArkUI_NodeHandle node)
{
    ArkUI_Uint32 values[NUM_4];
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputUserUnderlineColor(node->uiNodeHandle, &values);
    g_numberValues[NUM_0].u32 = values[NUM_0];
    g_numberValues[NUM_1].u32 = values[NUM_1];
    g_numberValues[NUM_2].u32 = values[NUM_2];
    g_numberValues[NUM_3].u32 = values[NUM_3];
    g_attributeItem.size = NUM_4;
    return &g_attributeItem;
}

void ResetTextInputUnderlineColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputUserUnderlineColor(node->uiNodeHandle);
}

int32_t SetTextInputEnableAutoFill(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnableAutoFill(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputEnableAutoFill(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputEnableAutoFill(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputEnableAutoFill(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFill(node->uiNodeHandle);
}

int32_t SetEnablePreviewText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputEnablePreviewText(
                node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaEnablePreviewText(
                node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetEnablePreviewText(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
                getTextInputEnablePreviewText(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextAreaModifier()->
                getTextAreaEnablePreviewText(node->uiNodeHandle);
            break;
        default:
            break;
    }
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetEnablePreviewText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputEnablePreviewText(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaEnablePreviewText(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetTextInputContentType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // The enum values of native_type.h are different from those of text_content_type.h. Convert the enum values.
    auto value = static_cast<uint32_t>(item->value[0].i32);
    if (value >= static_cast<uint32_t>(ARKUI_TEXTINPUT_CONTENT_TYPE_NICKNAME)
        && value <= static_cast<uint32_t>(ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS)) {
        value += CONVERT_CONTENT_TYPE;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputContentType(
        node->uiNodeHandle, value);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputContentType(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto value = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputContentType(
        node->uiNodeHandle);
    if (value >= static_cast<int32_t>(
                     static_cast<uint32_t>(ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS) + CONVERT_CONTENT_TYPE) &&
        value <= static_cast<int32_t>(
                     static_cast<uint32_t>(ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS) + CONVERT_CONTENT_TYPE)) {
        value -= CONVERT_CONTENT_TYPE;
    }
    g_numberValues[0].i32 = value;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputContentType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputContentType(node->uiNodeHandle);
}

int32_t SetTextInputPasswordRules(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputPasswordRules(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputPasswordRules(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_attributeItem.string = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputPasswordRules(
        node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetTextInputPasswordRules(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputPasswordRules(node->uiNodeHandle);
}

int32_t SetTextInputSelectAll(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputSelectAll(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputSelectAll(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[NUM_0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputSelectAll(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputSelectAll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputSelectAll(node->uiNodeHandle);
}

int32_t SetTextInputCaretOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCaretPosition(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}


const ArkUI_AttributeItem* GetTextInputCaretOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[NUM_0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputCaretIndex(
        node->uiNodeHandle);
    ArkUI_Float32 values[NUM_2];
    fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputCaretOffset(node->uiNodeHandle, &values);
    g_numberValues[NUM_1].f32 = values[NUM_0];
    g_numberValues[NUM_2].f32 = values[NUM_1];
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

void ResetTextInputCaretOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCaretPosition(node->uiNodeHandle);
}

int32_t SetInputFilter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputInputFilter(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetInputFilter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_attributeItem.string = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputInputFilter(
        node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetInputFilter(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputInputFilter(node->uiNodeHandle);
}

int32_t SetTextInputStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputStyle(
        node->uiNodeHandle, static_cast<int32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputStyle(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextInputContentRect(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[NUM_4];
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputContentRect(node->uiNodeHandle, &values);
    g_numberValues[NUM_0].f32 = values[NUM_0];
    g_numberValues[NUM_1].f32 = values[NUM_1];
    g_numberValues[NUM_2].f32 = values[NUM_2];
    g_numberValues[NUM_3].f32 = values[NUM_3];
    g_attributeItem.size = REQUIRED_FOUR_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextInputContentLineCount(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[NUM_0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputContentLinesNum(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetInputCustomKeyboard(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto customKeyboard = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    auto supportAvoidance = false;
    if (item->size > 0) {
        supportAvoidance = static_cast<bool>(item->value[0].i32);
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboard(
        node->uiNodeHandle, customKeyboard->uiNodeHandle, supportAvoidance);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetInputCustomKeyboard(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto* value = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputCustomKeyboard(
        node->uiNodeHandle);
    void* attachNode = fullImpl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        g_attributeItem.object = reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    g_numberValues[NUM_0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
        getTextInputCustomKeyboardOption(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetInputCustomKeyboard(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputCustomKeyboard(node->uiNodeHandle);
}

int32_t SetTextInputWordBreak(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputWordBreak(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputWordBreak(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputWordBreak(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputWordBreak(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(node->uiNodeHandle);
}

int32_t SetTextInputShowKeyBoardOnFocus(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputShowKeyBoardOnFocus(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputShowKeyBoardOnFocus(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 =
        fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputShowKeyBoardOnFocus(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputShowKeyBoardOnFocus(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputShowKeyBoardOnFocus(node->uiNodeHandle);
}

int32_t SetTextInputNumberOfLines(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputNumberOfLines(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextInputHalfLeading(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputHalfLeading(
            node->uiNodeHandle, false);
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputHalfLeading(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextInputNumberOfLines(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputNumberOfLines(
        node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextInputNumberOfLines(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputNumberOfLines(node->uiNodeHandle);
}

void ResetTextInputHalfLeading(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputHalfLeading(node->uiNodeHandle);
}

int32_t SetBlurOnSubmit(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, NUM_1);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextInputModifier()->setBlurOnSubmit(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetBlurOnSubmit(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setBlurOnSubmit(node->uiNodeHandle, true);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setBlurOnSubmit(node->uiNodeHandle, false);
            break;
        default:
            break;
    }
}

const ArkUI_AttributeItem* GetBlurOnSubmit(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].i32 =
        fullImpl->getNodeModifiers()->getTextInputModifier()->getBlurOnSubmit(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}
// Stack Attribute functions
int32_t SetAlignContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_8, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getStackModifier()->setAlignContent(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAlignContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto alignContent = fullImpl->getNodeModifiers()->getStackModifier()->getAlignContent(node->uiNodeHandle);
    g_numberValues[0].i32 = alignContent;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetAlignContent(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getStackModifier()->resetAlignContent(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollFriction(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowFriction(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollFriction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessOrEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto friction = item->value[NUM_0].f32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListFriction(node->uiNodeHandle, friction);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFriction(node->uiNodeHandle, friction);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowFriction(node->uiNodeHandle, friction);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollFriction(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollFriction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowFriction(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollSnap(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[32];
    auto size =
        GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollSnap(node->uiNodeHandle, &values);

    //size index
    g_numberValues[NUM_0].i32 = values[NUM_0];
    g_numberValues[NUM_1].i32 = values[NUM_1];
    g_numberValues[NUM_2].i32 = values[NUM_2];
    for (auto i = NUM_3; i < size; i++) {
        g_numberValues[i].f32 = values[i];
    }
    g_attributeItem.size = size;
    return &g_attributeItem;
}

int32_t SetScrollScrollSnap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[NUM_0].i32) ||
        !InRegion(NUM_0, NUM_1, item->value[NUM_1].i32) || !InRegion(NUM_0, NUM_1, item->value[NUM_2].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto snapAlign = item->value[NUM_0].i32;
    auto enableSnapToStart = item->value[NUM_1].i32;
    auto enableSnapToEnd = item->value[NUM_2].i32;

    ArkUI_Float32 paginations[item->size - NUM_3];
    ArkUI_Int32 paginationParams[item->size + NUM_1];
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    for (int i = 0; i < item->size - NUM_3; ++i) {
        if (LessNotEqual(item->value[i + NUM_3].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        paginations[i] = item->value[i + NUM_3].f32;
        paginationParams[i] = unit;
    }

    paginationParams[item->size - NUM_3 + NUM_0] = snapAlign;
    paginationParams[item->size - NUM_3 + NUM_1] = enableSnapToStart;
    paginationParams[item->size - NUM_3 + NUM_2] = enableSnapToEnd;
    paginationParams[item->size] = (item->size - NUM_3 > 1) ? true : false;

    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollSnap(
        node->uiNodeHandle, paginations, item->size - NUM_3, paginationParams, item->size + NUM_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollSnap(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollSnap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollScrollBar(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowScrollBar(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_2, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBar(node->uiNodeHandle, attrVal);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBar(node->uiNodeHandle, attrVal);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBar(node->uiNodeHandle, attrVal);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollBar(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBar(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBar(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollBarWidth(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowScrollBarWidth(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBarWidth(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].f32;
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    if (node->type == ARKUI_NODE_LIST) {
        auto width = std::to_string(attrVal) + LENGTH_METRIC_UNIT[unit];
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarWidth(node->uiNodeHandle, width.c_str());
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarWidth(node->uiNodeHandle, attrVal, unit);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        auto width = std::to_string(attrVal) + LENGTH_METRIC_UNIT[unit];
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarWidth(
            node->uiNodeHandle, width.c_str());
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollBarWidth(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarWidth(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollBarColor(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].u32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].u32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        g_numberValues[0].u32 =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowScrollBarColor(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollScrollBarColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto color = item->value[NUM_0].u32;
    if (node->type == ARKUI_NODE_LIST) {
        auto value = Color(color).ColorToString();
        fullImpl->getNodeModifiers()->getListModifier()->setListScrollBarColor(node->uiNodeHandle, value.c_str());
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollBarColor(node->uiNodeHandle, color);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        auto value = Color(color).ColorToString();
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarColor(
            node->uiNodeHandle, value.c_str());
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollBarColor(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollBarColor(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollScrollable(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollScrollable(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetScrollScrollable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollScrollable(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollScrollable(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollScrollable(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollEdgeEffect(ArkUI_NodeHandle node)
{
    ArkUI_Int32 values[2];
    if (node->type == ARKUI_NODE_LIST) {
        auto valueSize =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getListEdgeEffect(node->uiNodeHandle, &values);
        for (int i = 0; i < valueSize; i++) {
            g_numberValues[i].i32 = values[i];
        }
        g_attributeItem.size = valueSize;
    } else if (node->type == ARKUI_NODE_SCROLL) {
        auto valueSize =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEdgeEffect(node->uiNodeHandle, &values);
        for (int i = 0; i < valueSize; i++) {
            g_numberValues[i].i32 = values[i];
        }
        g_attributeItem.size = valueSize;
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        auto valueSize =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getEdgeEffect(node->uiNodeHandle, &values);
        for (int i = 0; i < valueSize; i++) {
            g_numberValues[i].i32 = values[i];
        }
        g_attributeItem.size = valueSize;
    }
    return &g_attributeItem;
}

int32_t SetScrollEdgeEffect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_2, item->value[0].i32) ||
        (item->size > NUM_1 && !InRegion(NUM_0, NUM_1, item->value[1].i32)) ||
        (item->size > NUM_2 && !InRegion(NUM_1, NUM_3, item->value[2].i32))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[NUM_0].i32;
    bool alwaysEnabled = false;
    auto effectEdge = NUM_0;
    if (item->size > NUM_1) {
        alwaysEnabled = item->value[NUM_1].i32;
    } else if (node->type == ARKUI_NODE_SCROLL) {
        alwaysEnabled = true;
    }
    if (item->size > NUM_2) {
        effectEdge = item->value[NUM_2].i32;
    }
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListEdgeEffect(
            node->uiNodeHandle, attrVal, alwaysEnabled, effectEdge);
    } else if (node->type == ARKUI_NODE_GRID) {
        fullImpl->getNodeModifiers()->getGridModifier()->setEdgeEffect(
            node->uiNodeHandle, attrVal, alwaysEnabled, effectEdge);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdgeEffect(
            node->uiNodeHandle, attrVal, alwaysEnabled, effectEdge);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setEdgeEffect(
            node->uiNodeHandle, attrVal, alwaysEnabled, effectEdge);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEdgeEffect(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetListEdgeEffect(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_GRID) {
        fullImpl->getNodeModifiers()->getGridModifier()->resetEdgeEffect(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEdgeEffect(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetEdgeEffect(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetScrollEnableScrollInteraction(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_LIST) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getListModifier()->getEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getScrollModifier()->getEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        g_numberValues[0].i32 =
            GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowEnableScrollInteraction(
                node->uiNodeHandle);
    }
    return &g_attributeItem;
}

int32_t SetScrollEnableScrollInteraction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    bool enableScrollInteraction = item->value[NUM_0].i32;
    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setEnableScrollInteraction(
            node->uiNodeHandle, enableScrollInteraction);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setEnableScrollInteraction(
            node->uiNodeHandle, enableScrollInteraction);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowEnableScrollInteraction(
            node->uiNodeHandle, enableScrollInteraction);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEnableScrollInteraction(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->resetEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SCROLL) {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetEnableScrollInteraction(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowEnableScrollInteraction(node->uiNodeHandle);
    }
}

int32_t SetScrollNestedScroll(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // The size must be greater than 2 and check value is Nested Mode
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0 || !CheckAttributeIsScrollNestedMode(item->value[0].i32) ||
        !CheckAttributeIsScrollNestedMode(item->value[1].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int first = item->value[NUM_0].i32;
    int second = item->value[NUM_1].i32;
    if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowNestedScroll(
            node->uiNodeHandle, first, second);
    } else if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setListNestedScroll(node->uiNodeHandle, first, second);
    } else {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollNestedScroll(node->uiNodeHandle, first, second);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollNestedScroll(ArkUI_NodeHandle node)
{
    ArkUI_Int32 values[2];
    if (node->type == ARKUI_NODE_WATER_FLOW) {
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowNestedScroll(
            node->uiNodeHandle, &values);
    } else if (node->type == ARKUI_NODE_LIST) {
        GetFullImpl()->getNodeModifiers()->getListModifier()->getListNestedScroll(node->uiNodeHandle, &values);
    } else {
        GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollNestedScroll(node->uiNodeHandle, &values);
    }
    //size index
    g_numberValues[0].i32 = values[0];
    g_numberValues[1].i32 = values[1];
    g_attributeItem.size = ALLOW_SIZE_2;
    return &g_attributeItem;
}

void ResetScrollNestedScroll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowNestedScroll(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_LIST) {
        GetFullImpl()->getNodeModifiers()->getListModifier()->resetListNestedScroll(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollNestedScroll(node->uiNodeHandle);
    }
}

int32_t SetScrollTo(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int32_t defaultUnit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Float32 values[ALLOW_SIZE_8] = { 0.0, defaultUnit, 0.0, defaultUnit, DEFAULT_DURATION, 1, 0.0, 0.0 };
    values[0] = item->value[0].f32;
    values[1] = defaultUnit;
    values[2] = item->value[1].f32;
    values[NUM_3] = defaultUnit;
    if (item->size > 2) {
        values[NUM_4] = static_cast<ArkUI_Float32>(item->value[NUM_2].i32);
    }
    // check size
    if (item->size > NUM_3 && CheckAttributeIsAnimationCurve(item->value[NUM_3].i32)) {
        values[NUM_5] = static_cast<ArkUI_Float32>(item->value[NUM_3].i32);
    }
    if (item->size > 4) {
        values[NUM_6] = static_cast<ArkUI_Float32>(item->value[NUM_4].i32);
    }
    if (item->size > NUM_5) {
        values[NUM_7] = static_cast<ArkUI_Float32>(item->value[NUM_5].i32);
    }
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollTo(node->uiNodeHandle, &values);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollOffset(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[2];
    GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollOffset(node->uiNodeHandle, &values);
    //size index
    g_numberValues[0].f32 = values[0];
    g_numberValues[1].f32 = values[1];
    g_attributeItem.size = ALLOW_SIZE_2;
    return &g_attributeItem;
}

void ResetScrollTo(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollTo(node->uiNodeHandle);
}

int32_t SetScrollEdge(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEdge(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollEdge(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEdge(node->uiNodeHandle);
    //size index
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetScrollEdge(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEdge(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollEnablePaging(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollEnablePaging(node->uiNodeHandle);
    //ScrollPagingStatus::VALID is true and VALID value is 2, others is false
    g_numberValues[0].i32 = value == NUM_2 ? true : false;
    return &g_attributeItem;
}

int32_t SetScrollEnablePaging(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollEnablePaging(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetScrollEnablePaging(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollEnablePaging(node->uiNodeHandle);
}

int32_t SetScrollPage(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 values[ALLOW_SIZE_2] = { NUM_0, DEFAULT_FALSE };
    values[NUM_0] = item->value[NUM_0].i32;
    if (item->size > NUM_1 && InRegion(NUM_0, NUM_1, item->value[NUM_1].i32)) {
        values[NUM_1] = item->value[NUM_1].i32;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollPage(node->uiNodeHandle, values[NUM_0], values[NUM_1]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScrollBy(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    DimensionUnit unit = static_cast<DimensionUnit>(GetDefaultUnit(node, UNIT_VP));
    if (unit != DimensionUnit::VP && unit != DimensionUnit::PX) {
        return ERROR_CODE_PARAM_INVALID;
    }
    double x = item->value[NUM_0].f32;
    double y = item->value[NUM_1].f32;
    if (unit == DimensionUnit::VP) {
        x = OHOS::Ace::NodeModel::GetFullImpl()->getBasicAPI()->convertLengthMetricsUnit(
            x, static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_VP), static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_PX));
        y = OHOS::Ace::NodeModel::GetFullImpl()->getBasicAPI()->convertLengthMetricsUnit(
            y, static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_VP), static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_PX));
    }
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_SCROLL || node->type == ARKUI_NODE_WATER_FLOW) {
        fullImpl->getNodeModifiers()->getScrollModifier()->setScrollBy(node->uiNodeHandle, x, y);
    } else if (node->type == ARKUI_NODE_LIST) {
        fullImpl->getNodeModifiers()->getListModifier()->setScrollBy(node->uiNodeHandle, x, y);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScrollFling(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    DimensionUnit unit = static_cast<DimensionUnit>(GetDefaultUnit(node, UNIT_VP));
    if (unit != DimensionUnit::VP && unit != DimensionUnit::PX) {
        return ERROR_CODE_PARAM_INVALID;
    }
    double value = item->value[NUM_0].f32;
    if (unit == DimensionUnit::VP) {
        value = OHOS::Ace::NodeModel::GetFullImpl()->getBasicAPI()->convertLengthMetricsUnit(value,
            static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_VP), static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_PX));
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFling(node->uiNodeHandle, value);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScrollFadingEdge(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    bool fadingEdge = item->value[NUM_0].i32;
    float fadingEdgeLengthValue = DEFAULT_SCROLL_FADING_EDGE_LENGTH;
    int32_t unit = UNIT_VP;
    if (fadingEdge && item->size > NUM_1 && GreatNotEqual(item->value[NUM_1].f32, 0.f)) {
        fadingEdgeLengthValue = item->value[NUM_1].f32;
        unit = GetDefaultUnit(node, UNIT_VP);
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->setScrollFadingEdge(node->uiNodeHandle,
        fadingEdge, fadingEdgeLengthValue, unit);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollFadingEdge(ArkUI_NodeHandle node)
{
    ArkUIInt32orFloat32 values[NUM_2];
    GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollFadingEdge(node->uiNodeHandle, &values);
    g_numberValues[NUM_0].i32 = values[NUM_0].i32;
    g_numberValues[NUM_1].f32 = values[NUM_1].f32;
    return &g_attributeItem;
}

void ResetScrollFadingEdge(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getScrollModifier()->resetScrollFadingEdge(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetScrollContentSize(ArkUI_NodeHandle node)
{
    ArkUI_Float32 values[NUM_2];
    GetFullImpl()->getNodeModifiers()->getScrollModifier()->getScrollContentSize(node->uiNodeHandle, &values);
    g_numberValues[NUM_0].f32 = values[NUM_0];
    g_numberValues[NUM_1].f32 = values[NUM_1];
    return &g_attributeItem;
}

void ResetFlingSpeedLimit(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getScrollableModifier()->resetFlingSpeedLimit(node->uiNodeHandle);
}

int32_t SetFlingSpeedLimit(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getScrollableModifier()->setFlingSpeedLimit(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetFlingSpeedLimit(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollableModifier()->getFlingSpeedLimit(node->uiNodeHandle);
    g_numberValues[0].f32 = value;
    return &g_attributeItem;
}

void ResetScrollContentClip(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getScrollableModifier()->resetContentClip(node->uiNodeHandle);
}

int32_t SetScrollContentClip(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getScrollableModifier()->setContentClip(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetScrollContentClip(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getScrollableModifier()->getContentClip(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetListDirection(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getListDirection(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[0].i32;
    fullImpl->getNodeModifiers()->getListModifier()->setListDirection(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetListDirection(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetListDirection(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListSticky(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getSticky(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListSticky(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_3, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto attrVal = item->value[0].i32;
    fullImpl->getNodeModifiers()->getListModifier()->setSticky(node->uiNodeHandle, attrVal);
    return ERROR_CODE_NO_ERROR;
}

void ResetListSticky(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetSticky(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListSpace(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getListModifier()->getListSpace(node->uiNodeHandle);
    g_numberValues[0].f32 = value;
    return &g_attributeItem;
}

int32_t SetListSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->setListSpace(node->uiNodeHandle, item->value[NUM_0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListSpace(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetListSpace(node->uiNodeHandle);
}

int32_t SetListNodeAdapter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* nodeAdapter = reinterpret_cast<ArkUINodeAdapterHandle>(item->object);
    return GetFullImpl()->getNodeModifiers()->getListModifier()->setNodeAdapter(node->uiNodeHandle, nodeAdapter);
}

void ResetListNodeAdapter(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetNodeAdapter(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListNodeAdapter(ArkUI_NodeHandle node)
{
    ArkUINodeAdapterHandle adapter =
        GetFullImpl()->getNodeModifiers()->getListModifier()->getNodeAdapter(node->uiNodeHandle);
    g_attributeItem.object = reinterpret_cast<void*>(adapter);
    return &g_attributeItem;
}

int32_t SetListCachedCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getListModifier()->setCachedCount(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListCachedCount(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetCachedCount(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListCachedCount(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getListModifier()->getCachedCount(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListAlignListItem(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1 || !CheckAttributeIsListItemAlign(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getListModifier()->setAlignListItem(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListAlignListItem(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListModifier()->resetAlignListItem(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListAlignListItem(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getListModifier()->getAlignListItem(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListChildrenMainSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* listChildrenMainSize = reinterpret_cast<ArkUIListChildrenMainSize>(item->object);
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getListModifier()->setListChildrenMainSize(
        node->uiNodeHandle, listChildrenMainSize, unit);
    return ERROR_CODE_NO_ERROR;
}

void ResetListChildrenMainSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListModifier()->resetListChildrenMainSize(node->uiNodeHandle);
}

int32_t SetListScrollToIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 values[ALLOW_SIZE_3] = { NUM_0, DEFAULT_FALSE, ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_NONE };
    values[NUM_0] = item->value[NUM_0].i32;
    if (item->size > NUM_1 && InRegion(NUM_0, NUM_1, item->value[NUM_1].i32)) {
        values[NUM_1] = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2 && InRegion(NUM_0, NUM_3, item->value[NUM_2].i32)) {
        values[NUM_2] = item->value[NUM_2].i32;
    }
    if (values[NUM_2] == ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_NONE) {
        values[NUM_2] = ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_START;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListModifier()->setScrollToIndex(
        node->uiNodeHandle, values[NUM_0], values[NUM_1], values[NUM_2]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetListInitialIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getListModifier()->setInitialIndex(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetListInitialIndex(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getListModifier()->resetInitialIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListInitialIndex(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getListModifier()->getInitialIndex(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetListDivider(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_1].f32, NUM_0) ||
        LessNotEqual(item->value[NUM_2].f32, NUM_0) || LessNotEqual(item->value[NUM_3].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto color = item->value[NUM_0].u32;
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Float32 values[NUM_3] = { item->value[NUM_1].f32, item->value[NUM_2].f32, item->value[NUM_3].f32 };
    ArkUI_Int32 units[NUM_3] = { unit, unit, unit };

    fullImpl->getNodeModifiers()->getListModifier()->listSetDivider(node->uiNodeHandle, color, values, units, NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetListDivider(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListModifier()->listResetDivider(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListDivider(ArkUI_NodeHandle node)
{
    ArkUIdividerOptions option;
    GetFullImpl()->getNodeModifiers()->getListModifier()->getlistDivider(
        node->uiNodeHandle, &option, GetDefaultUnit(node, UNIT_VP));
    //size index
    g_numberValues[NUM_0].u32 = option.color;
    g_numberValues[NUM_1].f32 = option.strokeWidth;
    g_numberValues[NUM_2].f32 = option.startMargin;
    g_numberValues[NUM_3].f32 = option.endMargin;
    g_attributeItem.size = ALLOW_SIZE_4;
    return &g_attributeItem;
}

// TextArea
int32_t SetTextAreaPlaceholderFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    struct ArkUIResourceLength size = { 16.0, GetDefaultUnit(node, UNIT_FP) };
    int weight = ARKUI_FONT_WEIGHT_NORMAL;
    int style = ARKUI_FONT_STYLE_NORMAL;
    if (item->size > NUM_0) {
        if (LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        size.value = item->value[NUM_0].f32;
    }
    if (item->size > NUM_1) {
        if (item->value[NUM_1].i32 < 0 || item->value[NUM_1].i32 > static_cast<int32_t>(ARKUI_FONT_STYLE_ITALIC)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        style = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        if (item->value[NUM_2].i32 < 0 || item->value[NUM_2].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        weight = item->value[NUM_2].i32;
    }
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderFontEnum(
        node->uiNodeHandle, &size, weight, item->string, style);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaPlaceholderFont(ArkUI_NodeHandle node)
{
    ArkUITextFont font;
    font.fontSizeUnit = GetDefaultUnit(node, UNIT_FP);
    GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaPlaceholderFont(
        node->uiNodeHandle, &font);
    int index = 0;
    g_numberValues[index++].f32 = font.fontSize;
    g_numberValues[index++].i32 = font.fontStyle;
    g_numberValues[index++].i32 = font.fontWeight;
    g_attributeItem.size = index;
    g_attributeItem.string = font.fontFamilies;
    return &g_attributeItem;
}

void ResetTextAreaPlaceholderFont(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderFont(node->uiNodeHandle);
}

int32_t SetTextAreaPlaceholder(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaPlaceholder(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaPlaceholder(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetTextAreaPlaceholder(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(node->uiNodeHandle, "");
}

int32_t SetTextAreaText(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    ArkUI_CharPtr itemString = item->string;
    if (!itemString) {
        itemString = "";
    }
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextString(
        node->uiNodeHandle, itemString);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaText(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaText(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetTextAreaText(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextString(node->uiNodeHandle, "");
}

int32_t StopTextAreaEditing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (item->value[NUM_0].i32 == 0) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->stopTextAreaTextEditing(node->uiNodeHandle);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaEditing(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaEditing(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetTextAreaType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_5, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaType(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaType(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetTextAreaType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaType(node->uiNodeHandle);
}

int32_t SetTextAreaShowCounter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUI_Bool open = false;
    ArkUI_Int32 thresholdPercentage = -1;
    ArkUI_Bool highlightBorder = true;
    if (item->size > NUM_0) {
        if (!InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        open = item->value[NUM_0].i32;
    }
    if (item->size > NUM_1) {
        if (!InRegion(NUM_1, NUM_100, static_cast<ArkUI_Int32>(item->value[NUM_1].f32))) {
            return ERROR_CODE_PARAM_INVALID;
        }
        thresholdPercentage = static_cast<ArkUI_Int32>(item->value[NUM_1].f32);
    }
    if (item->size > NUM_2) {
        if (!InRegion(NUM_0, NUM_1, item->value[NUM_2].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        highlightBorder = item->value[NUM_2].i32;
    }

    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaShowCounterOptions(
        node->uiNodeHandle, open, thresholdPercentage, highlightBorder);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextAreaShowCounter(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaShowCounterOptions(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextAreaShowCounter(ArkUI_NodeHandle node)
{
    ArkUIShowCountOptions options;
    auto modifier = GetFullImpl()->getNodeModifiers()->getTextAreaModifier();
    modifier->getTextAreaShowCounterOptions(node->uiNodeHandle, &options);
    // open
    g_numberValues[NUM_0].i32 = options.open;
    // thresholdPercentage
    g_numberValues[NUM_1].f32 = options.thresholdPercentage;
    // highlightBorder
    g_numberValues[NUM_2].i32 = options.highlightBorder;
    return &g_attributeItem;
}

int32_t SetTextAreaSelectionMenuHidden(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaSelectionMenuHidden(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextAreaSelectionMenuHidden(ArkUI_NodeHandle node)
{
    g_numberValues[0].i32 =
        GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaSelectionMenuHidden(node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetTextAreaSelectionMenuHidden(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaSelectionMenuHidden(node->uiNodeHandle);
}

// button
int32_t SetButtonLabel(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item == nullptr || item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getButtonModifier()->setButtonLabel(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetButtonLabel(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getButtonModifier()->getButtonLabel(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetButtonLabel(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonLabel(node->uiNodeHandle);
}

int32_t SetButtonType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (LessNotEqual(actualSize, 0) ||
        !InRegion(ARKUI_BUTTON_TYPE_NORMAL, ARKUI_BUTTON_TYPE_CIRCLE, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getButtonModifier()->setButtonType(node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetButtonType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getButtonModifier()->getButtonType(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetButtonType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getButtonModifier()->resetButtonType(node->uiNodeHandle);
}

int32_t SetProgressValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressValue(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetProgressValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getProgressModifier()->getProgressValue(
        node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetProgressValue(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressValue(node->uiNodeHandle);
}

int32_t SetProgressTotal(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressTotal(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetProgressTotal(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getProgressModifier()->getProgressTotal(
        node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetProgressTotal(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressValue(node->uiNodeHandle);
}

int32_t SetProgressColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetProgressColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getProgressModifier()->getProgressColor(
        node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetProgressColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressColor(node->uiNodeHandle);
}

int32_t SetProgressType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(static_cast<int32_t>(ARKUI_PROGRESS_TYPE_LINEAR),
        static_cast<int32_t>(ARKUI_PROGRESS_TYPE_CAPSULE), item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressType(node->uiNodeHandle,
        PROGRESS_TYPE_ARRAY[item->value[NUM_0].i32]);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetProgressType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getProgressModifier()->getProgressType(
        node->uiNodeHandle);
    auto it = std::find(PROGRESS_TYPE_ARRAY.begin(), PROGRESS_TYPE_ARRAY.end(), resultValue);
    if (it != PROGRESS_TYPE_ARRAY.end()) {
        g_numberValues[0].i32 = std::distance(PROGRESS_TYPE_ARRAY.begin(), it);
    }
    return &g_attributeItem;
}

void ResetProgressType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressType(node->uiNodeHandle);
}

int32_t SetProgressLinearStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    node->progressLinearStyle = item->object;

    auto* fullImpl = GetFullImpl();
    auto resultValue = fullImpl->getNodeModifiers()->getProgressModifier()->getProgressType(node->uiNodeHandle);
    if (item->size < 0 || item->object == nullptr || PROGRESS_TYPE_LINEAR != resultValue) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* option = reinterpret_cast<ArkUI_ProgressLinearStyleOption*>(item->object);
    if (option == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUIProgressStyle progressStyle;
    progressStyle.enableScanEffect = option->scanEffectEnable;
    progressStyle.enableSmoothEffect = option->smoothEffectEnable;
    progressStyle.strokeWidthValue = option->strokeWidth;
    progressStyle.strokeWidthUnit = static_cast<uint8_t>(DimensionUnit::VP);
    progressStyle.strokeRadiusValue = option->strokeRadius;
    progressStyle.strokeRadiusUnit = static_cast<uint8_t>(DimensionUnit::VP);

    fullImpl->getNodeModifiers()->getProgressModifier()->setProgressStyle(node->uiNodeHandle, &progressStyle);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetProgressLinearStyle(ArkUI_NodeHandle node)
{
    g_attributeItem.object = node->progressLinearStyle;
    return &g_attributeItem;
}

void ResetProgressLinearStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getProgressModifier()->resetProgressStyle(node->uiNodeHandle);
}

int32_t SetXComponentId(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (item == nullptr || !item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentId(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetXComponentId(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getXComponentModifier()->getXComponentId(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

int32_t SetXComponentType(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || (item->value[NUM_0].i32 != static_cast<int32_t>(ARKUI_XCOMPONENT_TYPE_SURFACE) && 
        item->value[NUM_0].i32 != static_cast<int32_t>(ARKUI_XCOMPONENT_TYPE_TEXTURE))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentType(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetXComponentType(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getXComponentModifier()->getXComponentType(
        node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetXComponentType(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentType(
        node->uiNodeHandle, ARKUI_XCOMPONENT_TYPE_SURFACE);
}

int32_t SetXComponentSurfaceSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentSurfaceSize(
        node->uiNodeHandle, item->value[0].u32, item->value[1].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetXComponentSurfaceSize(ArkUI_NodeHandle node)
{
    int index = 0;
    g_numberValues[index++].u32 =
        GetFullImpl()->getNodeModifiers()->getXComponentModifier()->getXComponentSurfaceWidth(node->uiNodeHandle);
    g_numberValues[index++].u32 =
        GetFullImpl()->getNodeModifiers()->getXComponentModifier()->getXComponentSurfaceHeight(node->uiNodeHandle);
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetXComponentSurfaceSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getXComponentModifier()->setXComponentSurfaceSize(node->uiNodeHandle, 0, 0);
}

int32_t SetBaseLineOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->setSpanBaselineOffset(node->uiNodeHandle,
            item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    } else {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextBaselineOffset(node->uiNodeHandle,
            item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetBaselineOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanBaselineOffset(node->uiNodeHandle);
    } else {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextBaselineOffset(node->uiNodeHandle);
    }
}

int32_t SetTextShadow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size < NUM_5) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    std::vector<struct ArkUITextShadowStruct> shadows;
    struct ArkUITextShadowStruct shadow = { item->value[0].f32, item->value[1].i32, item->value[2].u32,
        item->value[3].f32, item->value[4].f32 };
    shadows.emplace_back(shadow);
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextShadow(node->uiNodeHandle, &shadows[0], shadows.size());
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->setTextShadow(node->uiNodeHandle, &shadows[0], shadows.size());
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetTextShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextShadow(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->resetTextShadow(node->uiNodeHandle);
    }
}

int32_t SetTextMinFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextMinFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputAdaptMinFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaAdaptMinFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextMinFontSize(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_TEXT) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextModifier()->getTextMinFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputAdaptMinFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaAdaptMinFontSize(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

void ResetTextMinFontSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextMinFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputAdaptMinFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMinFontSize(node->uiNodeHandle);
    }
}

int32_t SetTextMaxFontSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextMaxFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputAdaptMaxFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaAdaptMaxFontSize(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextMaxFontSize(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_TEXT) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextModifier()->getTextMaxFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextInputModifier()->getTextInputAdaptMaxFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        g_numberValues[0].f32 =
            GetFullImpl()->getNodeModifiers()->getTextAreaModifier()->getTextAreaAdaptMaxFontSize(node->uiNodeHandle);
    }
    return &g_attributeItem;
}

void ResetTextMaxFontSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextMaxFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputAdaptMaxFontSize(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMaxFontSize(node->uiNodeHandle);
    }
}

int32_t SetTextFont(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    // size
    double size = item->value[0].f32;
    // weight
    int weight = 10; // default
    if (item->size > 1) {
        if (!CheckAttributeIsFontWeight(item->value[1].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        weight = item->value[1].i32;
    }
    // style
    int style = 0;
    if (item->size > 2) {
        // get value 2 is font style
        if (!CheckAttributeIsFontStyle(item->value[2].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        style = item->value[NUM_2].i32;
    }
    // family
    std::vector<std::string> familyArray;
    if (item->string != nullptr) {
        std::string value(item->string);
        StringUtils::StringSplitter(value, ',', familyArray);
    }

    ArkUIFontWithOptionsStruct fontStruct;
    fontStruct.fontSizeNumber = size;
    fontStruct.fontSizeUnit = GetDefaultUnit(node, UNIT_FP);
    fontStruct.fontWeight = weight;
    if (familyArray.size() > 0) {
        std::vector<const char*> fontFamilies;
        for (const auto& element : familyArray) {
            fontFamilies.push_back(element.c_str());
        }
        fontStruct.fontFamilies = fontFamilies.data();
    }
    fontStruct.fontStyle = style;
    ArkUIFontWithOptionsStruct* fontInfo = &fontStruct;
    fullImpl->getNodeModifiers()->getTextModifier()->setTextFont(node->uiNodeHandle, fontInfo);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextFont(ArkUI_NodeHandle node)
{
    ArkUITextFont font;
    font.fontSizeUnit = GetDefaultUnit(node, UNIT_FP);
    GetFullImpl()->getNodeModifiers()->getTextModifier()->getFont(node->uiNodeHandle, &font);
    int index = 0;
    g_numberValues[index++].f32 = font.fontSize;
    g_numberValues[index++].i32 = font.fontWeight;
    g_numberValues[index++].i32 = font.fontStyle;
    g_attributeItem.size = index;
    g_attributeItem.string = font.fontFamilies;
    return &g_attributeItem;
}

void ResetTextFont(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextFont(node->uiNodeHandle);
}

int32_t SetTextHeightAdaptivePolicy(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsTextHeightAdaptivePolicy(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextHeightAdaptivePolicy(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextHeightAdaptivePolicy(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getTextModifier()->getHeightAdaptivePolicy(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetTextHeightAdaptivePolicy(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextHeightAdaptivePolicy(node->uiNodeHandle);
}

// Toggle Attributes functions
int32_t SetToggleSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSelectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleSelectedColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSelectedColor(node->uiNodeHandle);
}

int32_t SetToggleSwitchPointColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleSwitchPointColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleSwitchPointColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleSwitchPointColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleSwitchPointColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleSwitchPointColor(node->uiNodeHandle);
}

int32_t SetToggleValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleIsOn(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleValue(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleIsOn(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleValue(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleIsOn(node->uiNodeHandle);
}

int32_t SetToggleUnselectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getToggleModifier()->setToggleUnselectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetToggleUnselectedColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getToggleModifier()->getToggleUnselectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetToggleUnselectedColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getToggleModifier()->resetToggleUnselectedColor(node->uiNodeHandle);
}

// LoadingProgress Attributes functions
const ArkUI_AttributeItem* GetLoadingProgressColor(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getLoadingProgressModifier();

    g_numberValues[0].u32 = modifier->getColor(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetLoadingProgressColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    // already check in entry point.
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setColor(node->uiNodeHandle, item->value[NUM_0].u32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLoadingProgressColor(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->resetColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetLoadingProgressEnableLoading(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getLoadingProgressModifier();

    g_numberValues[0].i32 = modifier->getEnableLoading(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetLoadingProgressEnableLoading(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->setEnableLoading(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLoadingProgressEnableLoading(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getLoadingProgressModifier()->resetEnableLoading(node->uiNodeHandle);
}

// Swiper Attributes functions
int32_t SetSwiperLoop(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperLoop(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperLoop(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperLoop(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperLoop(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperLoop(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperAutoPlay(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(node->uiNodeHandle, item->value[0].i32);

    bool stopWhenTouched = true;
    if (item->size > NUM_1 && InRegion(NUM_0, NUM_1, item->value[1].i32)) {
        stopWhenTouched = static_cast<bool>(item->value[1].i32);
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperStopWhenTouched(node->uiNodeHandle, stopWhenTouched);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperAutoPlay(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(node->uiNodeHandle);
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperStopWhenTouched(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperAutoPlay(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperAutoPlay(node->uiNodeHandle);
    g_numberValues[1].i32 = modifier->getSwiperStopWhenTouched(node->uiNodeHandle);
    g_attributeItem.size = 2;
    return &g_attributeItem;
}

int32_t SetSwiperShowIndicator(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::vector<std::string> IndicatorProps = { "boolean", "true" };
    IndicatorProps[NUM_1] = std::to_string(item->value[0].i32);
    std::stringstream ss;
    for (const auto& str : IndicatorProps) {
        ss << str << "|";
    }
    std::string result;
    ss >> result;
    if (!result.empty()) {
        result.pop_back(); // 删除最后一个字符
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndicator(node->uiNodeHandle, result.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperShowIndicator(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIndicator(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperShowIndicator(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperShowIndicator(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperInterval(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperInterval(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].f32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperInterval(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperInterval(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperInterval(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperInterval(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperVertical(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperVertical(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperVertical(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperVertical(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperVertical(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperVertical(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDuration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDuration(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDuration(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDuration(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDuration(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperDuration(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperCurve(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR ||
        item->value[0].i32 > ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperCurve(
        node->uiNodeHandle, CurveToString(item->value[0].i32).c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperCurve(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperCurve(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperCurve(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperCurve(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperItemSpace(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperItemSpace(
        node->uiNodeHandle, item->value[0].f32, NUM_1);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperItemSpace(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperItemSpace(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperItemSpace(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].f32 = modifier->getSwiperItemSpace(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndex(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperIndex(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperIndex(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperIndex(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDisplayCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::string type = "number";
    std::string displayCount = std::to_string(item->value[0].i32);
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
        node->uiNodeHandle, displayCount.c_str(), type.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDisplayCount(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDisplayCount(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperDisplayCount(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperDisableSwipe(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperDisableSwipe(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperDisableSwipe(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperDisableSwipe(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperShowDisplayArrow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_2, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    double defaultBackgroundColor = StringToColorInt("#00000000", 0);
    double defaultArrowColor = StringToColorInt("#FF182431", 0);
    double displayArrow[ALLOW_SIZE_8] = { 1, 0, 0, DEFAULT_SIZE_24, defaultBackgroundColor, DEFAULT_SIZE_18,
        defaultArrowColor, 0 };
    if (item->value[0].i32 == ArkUI_SwiperArrow::ARKUI_SWIPER_ARROW_SHOW_ON_HOVER) {
        displayArrow[NUM_0] = DISPLAY_ARROW_TRUE;
        displayArrow[NUM_7] = DISPLAY_ARROW_TRUE;
    } else {
        displayArrow[NUM_0] = item->value[0].i32;
        displayArrow[NUM_7] = DISPLAY_ARROW_FALSE;
    }
    std::stringstream ss;
    for (const auto& str : displayArrow) {
        ss << str << "|";
    }
    std::string result;
    ss >> result;
    if (!result.empty()) {
        result.pop_back(); // 删除最后一个字符
    }
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperDisplayArrow(node->uiNodeHandle, result.c_str());
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperShowDisplayArrow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperDisplayArrow(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperShowDisplayArrow(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperShowDisplayArrow(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperEffectMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < ArkUI_EdgeEffect::ARKUI_EDGE_EFFECT_SPRING ||
        item->value[0].i32 > ArkUI_EdgeEffect::ARKUI_EDGE_EFFECT_NONE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperEffectMode(
        node->uiNodeHandle, static_cast<ArkUI_Int32>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperEffectMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperEffectMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperEffectMode(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSwiperModifier();
    g_numberValues[0].i32 = modifier->getSwiperEffectMode(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetSwiperNodeAdapter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* nodeAdapter = reinterpret_cast<ArkUINodeAdapterHandle>(item->object);
    return GetFullImpl()->getNodeModifiers()->getSwiperModifier()->setNodeAdapter(node->uiNodeHandle, nodeAdapter);
}

void ResetSwiperNodeAdapter(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getSwiperModifier()->resetNodeAdapter(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperNodeAdapter(ArkUI_NodeHandle node)
{
    ArkUINodeAdapterHandle adapter =
        GetFullImpl()->getNodeModifiers()->getSwiperModifier()->getNodeAdapter(node->uiNodeHandle);
    g_attributeItem.object = reinterpret_cast<void*>(adapter);
    return &g_attributeItem;
}

int32_t SetSwiperCachedCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size < 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSwiperModifier()->setSwiperCachedCount(
        node->uiNodeHandle, item->value[0].i32);

    ArkUI_Bool isShown = DEFAULT_FALSE;
    if (item->size == 2 && InRegion(DEFAULT_FALSE, DEFAULT_TRUE, item->value[1].i32)) {
        isShown = item->value[1].i32;
    }
    GetFullImpl()->getNodeModifiers()->getSwiperModifier()->setSwiperIsShown(node->uiNodeHandle, isShown);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperCachedCount(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperCachedCount(node->uiNodeHandle);
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIsShown(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperCachedCount(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getSwiperModifier()->getCachedCount(node->uiNodeHandle);
    ArkUI_Int32 isShown =
        GetFullImpl()->getNodeModifiers()->getSwiperModifier()->getSwiperCachedIsShown(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    g_numberValues[1].i32 = isShown;
    return &g_attributeItem;
}

int32_t SetSwiperNestedScroll(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 values[ALLOW_SIZE_1] = {0};
    values[0] = item->value[0].i32;

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperNestedScroll(node->uiNodeHandle, &values);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperNestedScroll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperNestedScroll(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 value = fullImpl->getNodeModifiers()->getSwiperModifier()->getSwiperNestedScroll(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetSwiperToIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 values[ALLOW_SIZE_2] = { 0, DEFAULT_FALSE };
    values[0] = item->value[0].i32;
    if (item->size > 1 && InRegion(NUM_0, NUM_1, item->value[1].i32)) {
        values[1] = item->value[1].i32;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperToIndex(node->uiNodeHandle, &values);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetSwiperPrevMargin(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Bool ignoreBlank = DEFAULT_FALSE;
    if (actualSize > NUM_1 && InRegion(DEFAULT_FALSE, DEFAULT_TRUE, item->value[1].i32)) {
        ignoreBlank = item->value[1].i32;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperPrevMargin(
        node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_VP), ignoreBlank);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperPrevMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperPrevMargin(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperPrevMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUISwiperMarginOptions options;
    fullImpl->getNodeModifiers()->getSwiperModifier()->getSwiperPrevMargin(node->uiNodeHandle, unit, &options);
    g_numberValues[0].f32 = options.margin;
    g_numberValues[1].i32 = options.ignoreBlank;
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

int32_t SetSwiperNextMargin(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Bool ignoreBlank = DEFAULT_FALSE;
    if (actualSize > NUM_1 && InRegion(DEFAULT_FALSE, DEFAULT_TRUE, item->value[1].i32)) {
        ignoreBlank = item->value[1].i32;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperNextMargin(
        node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_VP), ignoreBlank);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperNextMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperNextMargin(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperNextMargin(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUISwiperMarginOptions options;
    fullImpl->getNodeModifiers()->getSwiperModifier()->getSwiperNextMargin(node->uiNodeHandle, unit, &options);
    g_numberValues[0].f32 = options.margin;
    g_numberValues[1].i32 = options.ignoreBlank;
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

int32_t SetSwiperIndicator(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAttributeIndicator(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_SwiperIndicator* indicator = reinterpret_cast<ArkUI_SwiperIndicator*>(item->object);
    CHECK_NULL_RETURN(indicator, ERROR_CODE_PARAM_INVALID);
    node->swiperIndicator = indicator;
    ArkUISwiperIndicator indicatorProp;
    indicatorProp.dimUnit = GetDefaultUnit(node, UNIT_VP);
    indicatorProp.dimLeft = ArkUIOptionalFloat { indicator->dimLeft.isSet, indicator->dimLeft.value };
    indicatorProp.dimTop = ArkUIOptionalFloat { indicator->dimTop.isSet, indicator->dimTop.value };
    indicatorProp.dimRight = ArkUIOptionalFloat { indicator->dimRight.isSet, indicator->dimRight.value };
    indicatorProp.dimBottom = ArkUIOptionalFloat { indicator->dimBottom.isSet, indicator->dimBottom.value };
    if (indicator->type == ARKUI_SWIPER_INDICATOR_TYPE_DOT) {
        indicatorProp.type = ArkUISwiperIndicatorType::DOT;
        indicatorProp.itemWidth = ArkUIOptionalFloat { indicator->itemWidth.isSet, indicator->itemWidth.value };
        indicatorProp.itemHeight = ArkUIOptionalFloat { indicator->itemHeight.isSet, indicator->itemHeight.value };
        indicatorProp.selectedItemWidth =
            ArkUIOptionalFloat { indicator->selectedItemWidth.isSet, indicator->selectedItemWidth.value };
        indicatorProp.selectedItemHeight =
            ArkUIOptionalFloat { indicator->selectedItemHeight.isSet, indicator->selectedItemHeight.value };
        indicatorProp.maskValue = ArkUIOptionalInt { indicator->maskValue.isSet, indicator->maskValue.value };
        indicatorProp.colorValue = ArkUIOptionalUint { indicator->colorValue.isSet, indicator->colorValue.value };
        indicatorProp.selectedColorValue =
            ArkUIOptionalUint { indicator->selectedColorValue.isSet, indicator->selectedColorValue.value };
        indicatorProp.maxDisplayCount =
        ArkUIOptionalInt { indicator->maxDisplayCount.isSet, indicator->maxDisplayCount.value };
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperIndicatorStyle(node->uiNodeHandle, &indicatorProp);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperIndicator(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperIndicator(node->uiNodeHandle);
    node->swiperIndicator = nullptr;
}

const ArkUI_AttributeItem* GetSwiperIndicator(ArkUI_NodeHandle node)
{
    ArkUI_SwiperIndicator* indicator = reinterpret_cast<ArkUI_SwiperIndicator*>(node->swiperIndicator);
    if (!indicator) {
        return &g_attributeItem;
    }
    auto* fullImpl = GetFullImpl();
    ArkUISwiperIndicator props;
    fullImpl->getNodeModifiers()->getSwiperModifier()->getSwiperIndicator(node->uiNodeHandle, &props);
    indicator->dimLeft.value = props.dimLeft.value;
    indicator->dimTop.value = props.dimTop.value;
    indicator->dimRight.value = props.dimRight.value;
    indicator->dimBottom.value = props.dimBottom.value;
    if (props.type == ArkUISwiperIndicatorType::DOT) {
        indicator->itemWidth.value = props.itemWidth.value;
        indicator->itemHeight.value = props.itemHeight.value;
        indicator->selectedItemWidth.value = props.selectedItemWidth.value;
        indicator->selectedItemHeight.value = props.selectedItemHeight.value;
        indicator->maskValue.value = props.maskValue.value;
        indicator->colorValue.value = props.colorValue.value;
        indicator->selectedColorValue.value = props.selectedColorValue.value;
        indicator->maxDisplayCount.value = props.maxDisplayCount.value;
    } else {
        indicator = nullptr;
    }

    g_numberValues[0].i32 = static_cast<int32_t>(props.type);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    g_attributeItem.object = indicator;
    return &g_attributeItem;
}

int32_t SetSwiperIndicatorInteractive(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setIndicatorInteractive(node->uiNodeHandle,
        static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperIndicatorInteractive(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetIndicatorInteractive(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperIndicatorInteractive(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getSwiperModifier()->
        getIndicatorInteractive(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetSwiperPageFlipMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->setSwiperPageFlipMode(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetSwiperPageFlipMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSwiperModifier()->resetSwiperPageFlipMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetSwiperPageFlipMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Int32 value = fullImpl->getNodeModifiers()->getSwiperModifier()->getSwiperPageFlipMode(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetTextFontFamily(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    std::string value(item->string);
    std::vector<std::string> fontFamilies;
    StringUtils::StringSplitter(value, ',', fontFamilies);
    auto families = std::make_unique<char*[]>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
    }

    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontFamily(
            node->uiNodeHandle, const_cast<const char**>(families.get()), fontFamilies.size());
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextFontFamily(
            node->uiNodeHandle, const_cast<const char**>(families.get()), fontFamilies.size());
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->setSpanFontFamily(
            node->uiNodeHandle, const_cast<const char**>(families.get()), fontFamilies.size());
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontFamily(node->uiNodeHandle, item->string);
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextFontFamily(ArkUI_NodeHandle node)
{
    if (node->type == ARKUI_NODE_SPAN) {
        auto resultValue = GetFullImpl()->getNodeModifiers()->getSpanModifier()->getSpanFontFamily(node->uiNodeHandle);
        g_attributeItem.string = resultValue;
    } else {
        auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getFontFamily(node->uiNodeHandle);
        g_attributeItem.string = resultValue;
    }
    g_attributeItem.size = 0;
    return &g_attributeItem;
}

void ResetTextFontFamily(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT_INPUT) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextFontFamily(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontFamily(node->uiNodeHandle);
    }
}

void ResetTextCopyOption(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->resetTextCopyOption(node->uiNodeHandle);
    }
}

int32_t SetTextCopyOption(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == NUM_0 || !CheckAttributeIsCopyOptions(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextCopyOption(node->uiNodeHandle, item->value[0].i32);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextCopyOption(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getTextModifier()->getCopyOption(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetBaseLineOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_SPAN) {
        g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getSpanModifier()->getSpanBaselineOffset(
            node->uiNodeHandle);
    } else {
        g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextBaselineOffset(
            node->uiNodeHandle);
    }
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextShadow(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUITextShadowStruct shadowArray[NUM_1];
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->getTextShadows(node->uiNodeHandle, &shadowArray[0], NUM_1);
    } else if (node->type == ARKUI_NODE_SPAN) {
        fullImpl->getNodeModifiers()->getSpanModifier()->getTextShadows(node->uiNodeHandle, &shadowArray[0], NUM_1);
    }
    g_numberValues[NUM_0].f32 = shadowArray[0].radius;
    g_numberValues[NUM_1].i32 = static_cast<int32_t>(shadowArray[0].type);
    g_numberValues[NUM_2].u32 = shadowArray[0].color;
    g_numberValues[NUM_3].f32 = shadowArray[0].offsetX;
    g_numberValues[NUM_4].f32 = shadowArray[0].offsetY;
    g_attributeItem.size = REQUIRED_FIVE_PARAM;
    return &g_attributeItem;
}

// ListItemGroup
int32_t SetListItemGroupHeader(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto headerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetHeader(
        node->uiNodeHandle, headerNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetListItemGroupFooter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto footerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetFooter(
        node->uiNodeHandle, footerNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetListItemGroupDivider(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_1].f32, NUM_0) || LessNotEqual(item->value[NUM_2].f32, NUM_0) ||
        LessNotEqual(item->value[NUM_3].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto color = item->value[NUM_0].u32;
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Float32 values[NUM_3] = { item->value[NUM_1].f32, item->value[NUM_2].f32, item->value[NUM_3].f32 };
    ArkUI_Int32 units[NUM_3] = { unit, unit, unit };

    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupSetDivider(
        node->uiNodeHandle, color, values, units, NUM_3);
    return ERROR_CODE_NO_ERROR;
}

void ResetListItemGroupDivider(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->listItemGroupResetDivider(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetListItemGroupDivider(ArkUI_NodeHandle node)
{
    ArkUIdividerOptions option;
    GetFullImpl()->getNodeModifiers()->getListItemGroupModifier()->getlistItemGroupDivider(
        node->uiNodeHandle, &option, GetDefaultUnit(node, UNIT_VP));
    g_numberValues[NUM_0].u32 = option.color;
    g_numberValues[NUM_1].f32 = option.strokeWidth;
    g_numberValues[NUM_2].f32 = option.startMargin;
    g_numberValues[NUM_3].f32 = option.endMargin;
    g_attributeItem.size = ALLOW_SIZE_4;
    return &g_attributeItem;
}

int32_t SetListItemGroupChildrenMainSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* listChildrenMainSize = reinterpret_cast<ArkUIListChildrenMainSize>(item->object);
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getListItemGroupModifier()->setListItemGroupChildrenMainSize(
        node->uiNodeHandle, listChildrenMainSize, unit);
    return ERROR_CODE_NO_ERROR;
}

void ResetListItemGroupChildrenMainSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListItemGroupModifier()->resetListItemGroupChildrenMainSize(node->uiNodeHandle);
}

int32_t SetListItemSwiperAction(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* listItemSwipeActionOption = reinterpret_cast<ArkUIListItemSwipeActionOptionHandle>(item->object);
    GetFullImpl()->getNodeModifiers()->getListItemModifier()->setListItemSwipeAction(
        node->uiNodeHandle, listItemSwipeActionOption);
    return ERROR_CODE_NO_ERROR;
}

void ResetListItemSwiperAction(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getListItemModifier()->resetListItemSwipeAction(node->uiNodeHandle);
}
// datepicker

const ArkUI_AttributeItem* GetDatePickerLunar(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getLunar(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetDatePickerLunar(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setLunar(node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerLunar(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetLunar(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerStart(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getStartDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerStart(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str(), DATEPICKER_START_TIME);
    auto month = StringToInt(date[NUM_1].c_str(), NUM_1);
    auto day = StringToInt(date[NUM_2].c_str(), NUM_1);
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setStartDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerStart(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetStartDate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerEnd(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getEndDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerEnd(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str(), DATEPICKER_END_TIME);
    auto month = StringToInt(date[NUM_1].c_str(), NUM_12);
    auto day = StringToInt(date[NUM_2].c_str(), NUM_31);
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setEndDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerEnd(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetEndDate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerSelected(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getSelectedDate(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "date is invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    auto year = StringToInt(date[NUM_0].c_str());
    auto month = StringToInt(date[NUM_1].c_str());
    auto day = StringToInt(date[NUM_2].c_str());
    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedDate(node->uiNodeHandle, year, month, day);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerSelected(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetSelectedDate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerMode(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getDatePickerModifier() && node) {
        auto resultValue = fullImpl->getNodeModifiers()->getDatePickerModifier()->getDatePickerMode(node->uiNodeHandle);
        g_numberValues[0].i32 = resultValue;
    }    
    return &g_attributeItem;
}

int32_t SetDatePickerMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!CheckAttributeIsDatePickerMode(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getDatePickerModifier() && node) {
        fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerMode(node->uiNodeHandle, item->value[0].i32);
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerMode(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getDatePickerModifier() && node) {
        fullImpl->getNodeModifiers()->getDatePickerModifier()->resetDatePickerMode(node->uiNodeHandle);
    }
}

const ArkUI_AttributeItem* GetDatePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getDisappearTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetDisappearTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getDatePickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetDatePickerTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetDatePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getDatePickerModifier()->getSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetDatePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_SELECTED_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(
        node->uiNodeHandle, fontInfo.c_str(), color, style);

    return ERROR_CODE_NO_ERROR;
}

void ResetDatePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(node->uiNodeHandle);
}

// timepicker
const ArkUI_AttributeItem* GetTimePickerSelected(ArkUI_NodeHandle node)
{
    auto value = GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerSelected(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> time;
    StringUtils::StringSplitter(item->string, '-', time);
    if (time.size() != NUM_2) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto hour = StringToInt(time[NUM_0].c_str());
    auto minute = StringToInt(time[NUM_1].c_str());
    if (!InRegion(NUM_0, NUM_23, hour) || !InRegion(NUM_0, NUM_59, minute)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelected(node->uiNodeHandle, hour, minute);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerSelected(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerSelected(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTimePickerUseMilitaryTime(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerUseMilitaryTime(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetTimePickerUseMilitaryTime(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerUseMilitaryTime(
        node->uiNodeHandle, item->value[NUM_0].i32);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerUseMilitaryTime(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerUseMilitaryTime(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTimePickerEnableCascade(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerEnableCascade(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetTimePickerEnableCascade(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerEnableCascade(
        node->uiNodeHandle, item->value[NUM_0].i32);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerEnableCascade(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerEnableCascade(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTimePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerDisappearTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerDisappearTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTimePickerTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTimePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTimepickerModifier()->getTimepickerSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTimePickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_SELECTED_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];
    fullImpl->getNodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTimePickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTimepickerModifier()->resetTimepickerSelectedTextStyle(node->uiNodeHandle);
}

// TextPicker
const ArkUI_AttributeItem* GetTextPickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerDisappearTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerDisappearTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerDisappearTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerDisappearTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextPickerTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_STYLE_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextPickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedTextStyle(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerSelectedTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    std::vector<std::string> params;
    StringUtils::StringSplitter(item->string, PARAMS_SEPARATOR_LEVEL1, params);
    if (params.size() != NUM_5) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "params are invalid");
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_Uint32 color = StringToColorInt(params[NUM_0].c_str(), DEFAULT_PICKER_SELECTED_COLOR);
    int size = StringToInt(params[NUM_1].c_str(), ERROR_CODE);
    if (size == ERROR_CODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto style = StringToEnumInt(params[NUM_4].c_str(), FONT_STYLES, NUM_0);
    std::string fontInfo = params[NUM_1] + '|' + params[NUM_2] + '|' + params[NUM_3];

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(
        node->uiNodeHandle, color, fontInfo.c_str(), style);

    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerSelectedTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedTextStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextPickerSelectedIndex(ArkUI_NodeHandle node)
{
    int32_t size = GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedSize(
        node->uiNodeHandle);
    ArkUI_Uint32 values[size];
    GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedIndex(
        node->uiNodeHandle, values, size);
    for (int i = 0; i < size; ++i) {
        g_numberValues[i].i32 = static_cast<int32_t>(values[i]);
    }
    return &g_attributeItem;
}

int32_t SetTextPickerSelectedIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Uint32 values[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].i32;
    }
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerSelectedIndex(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextPickerRange(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto value =
        fullImpl->getNodeModifiers()->getTextPickerModifier()->getTextPickerRangeStr(node->uiNodeHandle);
    g_numberValues[0].i32 =
        fullImpl->getNodeModifiers()->getTextPickerModifier()->getTextPickerSingleRange(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerRange(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(static_cast<int32_t>(ARKUI_TEXTPICKER_RANGETYPE_SINGLE),
        static_cast<int32_t>(ARKUI_TEXTPICKER_RANGETYPE_MULTI), item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    bool isSingleRange = false;
    auto fullImpl = GetFullImpl();
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    isSingleRange = item->value[NUM_0].i32 == static_cast<int32_t>(ARKUI_TEXTPICKER_RANGETYPE_SINGLE);
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerRangeStr(
        node->uiNodeHandle, item->string, isSingleRange, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerRange(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerRangeStr(node->uiNodeHandle, "", true, NUM_0);
}

const ArkUI_AttributeItem* GetTextPickerValue(ArkUI_NodeHandle node)
{
    auto value =
        GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerValue(node->uiNodeHandle);
    g_attributeItem.string = value;
    return &g_attributeItem;
}

int32_t SetTextPickerValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerValue(
        node->uiNodeHandle, item->string);
    
    return ERROR_CODE_NO_ERROR;
}

void ResetTextPickerValue(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerValue(node->uiNodeHandle, "");
}

const ArkUI_AttributeItem* GetTextPickerSelected(ArkUI_NodeHandle node)
{
    int32_t size = GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedSize(
        node->uiNodeHandle);
    ArkUI_Uint32 values[size];
    GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerSelectedIndex(
        node->uiNodeHandle, values, size);
    for (int i = 0; i < size; ++i) {
        g_numberValues[i].u32 = values[i];
    }
    return &g_attributeItem;
}

int32_t SetTextPickerSelected(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].u32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    ArkUI_Uint32 values[item->size];
    for (int i = 0; i < item->size; ++i) {
        values[i] = item->value[i].u32;
    }
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextPickerCanLoop(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerCanLoop(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextPickerCanLoop(ArkUI_NodeHandle node)
{
    int32_t result = GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerCanLoop(
        node->uiNodeHandle);
    g_numberValues[0].i32 = result;
    return &g_attributeItem;
}

void ResetTextPickerCanLoop(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerCanLoop(node->uiNodeHandle);
}

int32_t SetTextPickerDefaultPickerItemHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getTextPickerModifier()->setTextPickerDefaultPickerItemHeight(
        node->uiNodeHandle, item->value[0].f32, unit);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextPickerDefaultPickerItemHeight(ArkUI_NodeHandle node)
{
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    float result = GetFullImpl()->getNodeModifiers()->getTextPickerModifier()->getTextPickerDefaultPickerItemHeight(
        node->uiNodeHandle, unit);
    g_numberValues[0].f32 = result;
    return &g_attributeItem;
}

void ResetTextPickerDefaultPickerItemHeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextPickerModifier()->resetTextPickerDefaultPickerItemHeight(node->uiNodeHandle);
}

// Row&Column
int32_t SetAlignItems(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !InRegion(NUM_0, NUM_2, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->setColumnAlignItems(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->setRowAlignItems(
                node->uiNodeHandle, item->value[0].i32 + NUM_1);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignItems(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->resetColumnAlignItems(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->resetRowAlignItems(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

const ArkUI_AttributeItem* GetAlignItems(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getColumnModifier()->getColumnAlignItems(node->uiNodeHandle) - NUM_1;
            break;
        case ARKUI_NODE_ROW:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getRowModifier()->getRowAlignItems(node->uiNodeHandle) - NUM_1;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

int32_t SetJustifyContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !InRegion(NUM_1, NUM_8, item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->setColumnJustifyContent(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->setRowJustifyContent(
                node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

void ResetJustifyContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            fullImpl->getNodeModifiers()->getColumnModifier()->resetColumnJustifyContent(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            fullImpl->getNodeModifiers()->getRowModifier()->resetRowJustifyContent(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

const ArkUI_AttributeItem* GetJustifyContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_COLUMN:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getColumnModifier()->getColumnJustifyContent(node->uiNodeHandle);
            break;
        case ARKUI_NODE_ROW:
            g_numberValues[0].i32 =
                fullImpl->getNodeModifiers()->getRowModifier()->getRowJustifyContent(node->uiNodeHandle);
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

// Flex
int32_t SetFlexOptions(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    int options[NUM_5] = { 0, 0, 0, 1, 0 };
    if (item->size > NUM_0) {
        if (!InRegion(NUM_0, NUM_3, item->value[NUM_0].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        options[NUM_0] = item->value[NUM_0].i32;
    }
    if (item->size > NUM_1) {
        if (!InRegion(NUM_0, NUM_2, item->value[NUM_1].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        options[NUM_1] = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2) {
        if (!InRegion(NUM_1, NUM_8, item->value[NUM_2].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        options[NUM_2] = item->value[NUM_2].i32;
    }
    if (item->size > NUM_3) {
        if (!InRegion(NUM_0, NUM_5, item->value[NUM_3].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        options[NUM_3] = item->value[NUM_3].i32;
    }
    if (item->size > NUM_4) {
        if (!InRegion(NUM_1, NUM_8, item->value[NUM_4].i32)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        options[NUM_4] = item->value[NUM_4].i32;
    }
    fullImpl->getNodeModifiers()->getFlexModifier()->setFlexOptions(node->uiNodeHandle, options, NUM_5);
    return ERROR_CODE_NO_ERROR;
}

void ResetFlexOptions(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getFlexModifier()->resetFlexOptions(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFlexOptions(ArkUI_NodeHandle node)
{
    ArkUIFlexOptions options;
    GetFullImpl()->getNodeModifiers()->getFlexModifier()->getFlexOptions(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].i32 = options.direction;
    g_numberValues[NUM_1].i32 = options.wrap;
    g_numberValues[NUM_2].i32 = options.justifyContent;
    g_numberValues[NUM_3].i32 = options.alignItems;
    g_numberValues[NUM_4].i32 = options.alignContent;
    return &g_attributeItem;
}

int32_t SetBackgroundImageSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[BACKGROUND_IMAGE_WIDTH_INDEX].f32, 0.0f) ||
        LessNotEqual(item->value[BACKGROUND_IMAGE_HEIGHT_INDEX].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImageSizeWithUnit(node->uiNodeHandle,
        item->value[BACKGROUND_IMAGE_WIDTH_INDEX].f32, item->value[BACKGROUND_IMAGE_HEIGHT_INDEX].f32,
        GetDefaultUnit(node, UNIT_VP));
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBackgroundImageSizeType(ArkUI_ImageSize nativeImageSizeType)
{
    switch (nativeImageSizeType) {
        case ARKUI_IMAGE_SIZE_AUTO:
            return IMAGE_SIZE_TYPE_AUTO_INDEX;
        case ARKUI_IMAGE_SIZE_COVER:
            return IMAGE_SIZE_TYPE_COVER_INDEX;
        case ARKUI_IMAGE_SIZE_CONTAIN:
            return IMAGE_SIZE_TYPE_CONTAIN_INDEX;
        default:
            break;
    }
    return IMAGE_SIZE_TYPE_AUTO_INDEX;
}

int32_t SetBackgroundImageSizeWithStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || item->value[0].i32 < 0 ||
        item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_SIZE_CONTAIN)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto imageSizeType = GetBackgroundImageSizeType(static_cast<ArkUI_ImageSize>(item->value[0].i32));
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundImageSize(
        node->uiNodeHandle, 0.0f, 0.0f, imageSizeType, imageSizeType);
    return ERROR_CODE_NO_ERROR;
}

bool CheckBackgroundBlurStyleInput(const ArkUI_AttributeItem* item, int32_t size)
{
    CHECK_NULL_RETURN(item, false);
    if (BLUR_STYLE_INDEX < size &&
        (item->value[BLUR_STYLE_INDEX].i32 < 0 ||
            item->value[BLUR_STYLE_INDEX].i32 > static_cast<int32_t>(ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK))) {
        return false;
    }
    if (COLOR_MODE_INDEX < size &&
        (item->value[COLOR_MODE_INDEX].i32 < 0 ||
            item->value[COLOR_MODE_INDEX].i32 > static_cast<int32_t>(ARKUI_COLOR_MODE_DARK))) {
        return false;
    }
    if (ADAPTIVE_COLOR_INDEX < size &&
        (item->value[ADAPTIVE_COLOR_INDEX].i32 < 0 ||
            item->value[ADAPTIVE_COLOR_INDEX].i32 > static_cast<int32_t>(ARKUI_ADAPTIVE_COLOR_AVERAGE))) {
        return false;
    }
    if (SCALE_INDEX < size &&
        (LessNotEqual(item->value[SCALE_INDEX].f32, 0.0f) || GreatNotEqual(item->value[SCALE_INDEX].f32, 1.0f))) {
        return false;
    }
    if (GRAY_SCALE_START < size &&
        (LessNotEqual(item->value[GRAY_SCALE_START].f32, 0.0f) ||
        GreatNotEqual(item->value[GRAY_SCALE_START].f32, MAX_GRAYSCALE))) {
        return false;
    }
    if (GRAY_SCALE_END < size &&
        (LessNotEqual(item->value[GRAY_SCALE_END].f32, 0.0f) ||
        GreatNotEqual(item->value[GRAY_SCALE_END].f32, MAX_GRAYSCALE))) {
        return false;
    }
    return true;
}

int32_t SetBackgroundBlurStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto isInputValid = CheckBackgroundBlurStyleInput(item, actualSize);
    if (!isInputValid) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t blurStyle = ARKUI_BLUR_STYLE_THIN;
    if (BLUR_STYLE_INDEX < actualSize) {
        blurStyle = ConvertBlurStyle(item->value[BLUR_STYLE_INDEX].i32);
    }
    int32_t colorMode = ARKUI_COLOR_MODE_SYSTEM;
    if (COLOR_MODE_INDEX < actualSize) {
        colorMode = item->value[COLOR_MODE_INDEX].i32;
    }
    int32_t adaptiveColor = ARKUI_ADAPTIVE_COLOR_DEFAULT;
    if (ADAPTIVE_COLOR_INDEX < actualSize) {
        adaptiveColor = item->value[ADAPTIVE_COLOR_INDEX].i32;
    }
    float scale = 1.0f;
    if (SCALE_INDEX < actualSize) {
        scale = item->value[SCALE_INDEX].f32;
    }
    uint32_t grayScaleStart = 0;
    if (GRAY_SCALE_START < actualSize) {
        if (GreatOrEqual(item->value[GRAY_SCALE_START].f32, 0.0f)) {
            grayScaleStart = static_cast<uint32_t>(item->value[GRAY_SCALE_START].f32);
        } else {
            return ERROR_CODE_PARAM_INVALID;
        }
    }
    uint32_t grayScaleEnd = 0;
    if (GRAY_SCALE_END < actualSize) {
        if (GreatOrEqual(item->value[GRAY_SCALE_END].f32, 0.0f)
            && GreatOrEqual(item->value[GRAY_SCALE_END].f32, item->value[GRAY_SCALE_START].f32)) {
            grayScaleEnd = static_cast<uint32_t>(item->value[GRAY_SCALE_END].f32);
        } else {
            return ERROR_CODE_PARAM_INVALID;
        }
    }
    int32_t intArray[NUM_5];
    intArray[NUM_0] = blurStyle;
    intArray[NUM_1] = colorMode;
    intArray[NUM_2] = adaptiveColor;
    std::vector<float> greyVector(NUM_2);
    greyVector[NUM_0] = grayScaleStart;
    greyVector[NUM_1] = grayScaleEnd;
    bool isValidColor = false;
    Color inactiveColor = Color::TRANSPARENT;
    fullImpl->getNodeModifiers()->getCommonModifier()->setBackgroundBlurStyle(
        node->uiNodeHandle, &intArray, scale, &greyVector[0], NUM_2, isValidColor, inactiveColor.GetValue());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetForegroundBlurStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !CheckBackgroundBlurStyleInput(item, actualSize)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t blurStyle = ARKUI_BLUR_STYLE_THIN;
    if (BLUR_STYLE_INDEX < actualSize) {
        blurStyle = ConvertBlurStyle(item->value[BLUR_STYLE_INDEX].i32);
    }
    int32_t colorMode = ARKUI_COLOR_MODE_SYSTEM;
    if (COLOR_MODE_INDEX < actualSize) {
        colorMode = item->value[COLOR_MODE_INDEX].i32;
    }
    int32_t adaptiveColor = ARKUI_ADAPTIVE_COLOR_DEFAULT;
    if (ADAPTIVE_COLOR_INDEX < actualSize) {
        adaptiveColor = item->value[ADAPTIVE_COLOR_INDEX].i32;
    }
    float scale = 1.0f;
    if (SCALE_INDEX < actualSize) {
        scale = item->value[SCALE_INDEX].f32;
    }
    float grayScaleStart = 0;
    if (GRAY_SCALE_START < actualSize) {
        grayScaleStart = item->value[GRAY_SCALE_START].f32;
    }
    float grayScaleEnd = 0;
    if (GRAY_SCALE_END < actualSize) {
        grayScaleEnd = item->value[GRAY_SCALE_END].f32;
    }
    int32_t intArray[NUM_3];
    intArray[NUM_0] = blurStyle;
    intArray[NUM_1] = colorMode;
    intArray[NUM_2] = adaptiveColor;
    BlurOption blurOption = {{grayScaleStart, grayScaleEnd}};
    
    fullImpl->getNodeModifiers()->getCommonModifier()->setForegroundBlurStyle(
        node->uiNodeHandle, &intArray, scale, blurOption.grayscale.data(), blurOption.grayscale.size());
    return ERROR_CODE_NO_ERROR;
}

void ResetForegroundBlurStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetForegroundBlurStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetForegroundBlurStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto foregroundBlurStyle =
        fullImpl->getNodeModifiers()->getCommonModifier()->getForegroundBlurStyle(node->uiNodeHandle);
    g_numberValues[BLUR_STYLE_INDEX].i32 = UnConvertBlurStyle(foregroundBlurStyle.blurStyle);
    g_numberValues[COLOR_MODE_INDEX].i32 = foregroundBlurStyle.colorMode;
    g_numberValues[ADAPTIVE_COLOR_INDEX].i32 = foregroundBlurStyle.adaptiveColor;
    g_numberValues[SCALE_INDEX].f32 = foregroundBlurStyle.scale;
    g_numberValues[GRAY_SCALE_START].f32 = foregroundBlurStyle.grayScaleStart;
    g_numberValues[GRAY_SCALE_END].f32 = foregroundBlurStyle.grayScaleEnd;
    g_attributeItem.size = NUM_6;
    return &g_attributeItem;
}

int32_t SetLayoutRect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FOUR_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[2].i32 < 0) { // 2:index of width
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[3].i32 < 0) { // 3:index of height
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 intArray[NUM_4];
    intArray[0] = item->value[0].i32;
    intArray[1] = item->value[1].i32;
    intArray[2] = item->value[2].i32; // 2:index of width
    intArray[3] = item->value[3].i32; // 3:index of height
    fullImpl->getNodeModifiers()->getCommonModifier()->setLayoutRect(node->uiNodeHandle, &intArray);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetLayoutRect(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    ArkUI_Int32 intArray[NUM_4];
    fullImpl->getNodeModifiers()->getCommonModifier()->getLayoutRect(node->uiNodeHandle, &intArray);
    g_numberValues[0].i32 = intArray[0];
    g_numberValues[1].i32 = intArray[1];
    g_numberValues[2].i32 = intArray[2]; // 2:index of width
    g_numberValues[3].i32 = intArray[3]; // 3:index of height
    g_attributeItem.size = NUM_4;
    return &g_attributeItem;
}

void ResetLayoutRect(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetLayoutRect(node->uiNodeHandle);
}

int32_t SetFocusOnTouch(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setFocusOnTouch(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetFocusOnTouch(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetFocusOnTouch(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFocusOnTouch(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCommonModifier()->getFocusOnTouch(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetAccessibilityID(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    ArkUI_Int32 value = fullImpl->getNodeModifiers()->getCommonModifier()->getAccessibilityID(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    g_attributeItem.size = NUM_1;
    return &g_attributeItem;
}

int32_t SetAccessibilityState(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    ArkUI_AccessibilityState* statePtr = reinterpret_cast<ArkUI_AccessibilityState*>(item->object);
    CHECK_NULL_RETURN(statePtr, ERROR_CODE_PARAM_INVALID);
    if (statePtr->isDisabled.isSet && !InRegion(NUM_0, NUM_1, statePtr->isDisabled.value)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (statePtr->isSelected.isSet && !InRegion(NUM_0, NUM_1, statePtr->isSelected.value)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (statePtr->checkedType.isSet && !InRegion(NUM_0, NUM_1, statePtr->checkedType.value)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIAccessibilityState uiState;
    uiState.isDisabled = ArkUIOptionalInt { statePtr->isDisabled.isSet, statePtr->isDisabled.value };
    uiState.isSelected = ArkUIOptionalInt { statePtr->isSelected.isSet, statePtr->isSelected.value };
    uiState.checkedType = ArkUIOptionalInt { statePtr->checkedType.isSet, statePtr->checkedType.value };
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityState(node->uiNodeHandle, uiState);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityState(ArkUI_NodeHandle node)
{
    static ArkUI_AccessibilityState state;
    ArkUIAccessibilityState uiState;
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->getAccessibilityState(node->uiNodeHandle, uiState);
    state.isDisabled = ArkUI_OptionalInt { uiState.isDisabled.isSet, uiState.isDisabled.value };
    state.isSelected = ArkUI_OptionalInt { uiState.isSelected.isSet, uiState.isSelected.value };
    state.checkedType = ArkUI_OptionalInt { uiState.checkedType.isSet, uiState.checkedType.value };
    g_attributeItem.object = &state;
    g_attributeItem.size = NUM_0;
    return &g_attributeItem;
}

void ResetAccessibilityState(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityState(node->uiNodeHandle);
}

int32_t SetAccessibilityValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    ArkUI_AccessibilityValue* valuePtr = reinterpret_cast<ArkUI_AccessibilityValue*>(item->object);
    CHECK_NULL_RETURN(valuePtr, ERROR_CODE_PARAM_INVALID);
    if (valuePtr->current.isSet && ((!valuePtr->min.isSet) || (!valuePtr->max.isSet))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (valuePtr->max.value < valuePtr->min.value) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if ((valuePtr->current.value < valuePtr->min.value) || (valuePtr->current.value > valuePtr->max.value)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIAccessibilityValue uiValue;
    uiValue.min = ArkUIOptionalInt { valuePtr->min.isSet, valuePtr->min.value };
    uiValue.max = ArkUIOptionalInt { valuePtr->max.isSet, valuePtr->max.value };
    uiValue.current = ArkUIOptionalInt { valuePtr->current.isSet, valuePtr->current.value };
    uiValue.rangeMin = ArkUIOptionalInt { valuePtr->rangeMin.isSet, valuePtr->rangeMin.value };
    uiValue.rangeMax = ArkUIOptionalInt { valuePtr->rangeMax.isSet, valuePtr->rangeMax.value };
    uiValue.rangeCurrent = ArkUIOptionalInt { valuePtr->rangeCurrent.isSet, valuePtr->rangeCurrent.value };
    uiValue.text = ArkUIOptionalCharPtr { valuePtr->text.isSet, valuePtr->text.value };
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->setAccessibilityValue(node->uiNodeHandle, uiValue);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAccessibilityValue(ArkUI_NodeHandle node)
{
    static ArkUI_AccessibilityValue value;
    ArkUIAccessibilityValue uiValue;
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->getAccessibilityValue(node->uiNodeHandle, uiValue);
    value.min = ArkUI_OptionalInt { uiValue.min.isSet, uiValue.min.value };
    value.max = ArkUI_OptionalInt { uiValue.max.isSet, uiValue.max.value };
    value.current = ArkUI_OptionalInt { uiValue.current.isSet, uiValue.current.value };
    value.rangeMin = ArkUI_OptionalInt { uiValue.rangeMin.isSet, uiValue.rangeMin.value };
    value.rangeMax = ArkUI_OptionalInt { uiValue.rangeMax.isSet, uiValue.rangeMax.value };
    value.rangeCurrent = ArkUI_OptionalInt { uiValue.rangeCurrent.isSet, uiValue.rangeCurrent.value };
    value.text = ArkUI_OptionalCharPtr { uiValue.text.isSet, uiValue.text.value };
    g_attributeItem.object = &value;
    g_attributeItem.size = NUM_0;
    return &g_attributeItem;
}

void ResetAccessibilityValue(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAccessibilityValue(node->uiNodeHandle);
}

void ResetAreaChangeRatio(ArkUI_NodeHandle node)
{
    if (node->areaChangeRadio) {
        delete[] node->areaChangeRadio->value;
        delete node->areaChangeRadio;
    }
    node->areaChangeRadio = nullptr;
}

int32_t SetAreaChangeRatio(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 radioLength = item->size;
    ArkUI_NumberValue* radioList = new ArkUI_NumberValue[radioLength];
    for (int i = 0; i < radioLength; ++i) {
        if (LessNotEqual(item->value[i].f32, 0.0f) || GreatNotEqual(item->value[i].f32, 1.0f)) {
            delete[] radioList;
            return ERROR_CODE_PARAM_INVALID;
        }
        radioList[i].f32 = item->value[i].f32;
    }
    if (node->areaChangeRadio) {
        ResetAreaChangeRatio(node);
    }
    node->areaChangeRadio = new ArkUI_AttributeItem { .value = radioList, .size = radioLength};
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetAreaChangeRatio(ArkUI_NodeHandle node)
{
    return node->areaChangeRadio;
}

bool CheckTransformCenter(const ArkUI_AttributeItem* item, int32_t size)
{
    CHECK_NULL_RETURN(item, false);
    if (CENTER_X_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_X_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_X_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    if (CENTER_Y_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_Y_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_Y_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    if (CENTER_Z_PERCENT_INDEX < size && (LessNotEqual(item->value[CENTER_Z_PERCENT_INDEX].f32, 0.0f) ||
                                             GreatNotEqual(item->value[CENTER_Z_PERCENT_INDEX].f32, 1.0f))) {
        return false;
    }
    return true;
}

int32_t SetTransformCenter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, 0);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto isTransformCenterValid = CheckTransformCenter(item, actualSize);
    if (!isTransformCenterValid) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    CalcDimension centerX(HALF, DimensionUnit::PERCENT);
    if (CENTER_X_INDEX < actualSize) {
        centerX.SetValue(item->value[CENTER_X_INDEX].f32);
        centerX.SetUnit(static_cast<DimensionUnit>(unit));
    }
    CalcDimension centerY(HALF, DimensionUnit::PERCENT);
    if (CENTER_Y_INDEX < actualSize) {
        centerY.SetValue(item->value[CENTER_Y_INDEX].f32);
        centerY.SetUnit(static_cast<DimensionUnit>(unit));
    }
    CalcDimension centerZ(0, static_cast<DimensionUnit>(unit));
    if (CENTER_Z_INDEX < actualSize) {
        centerZ.SetValue(item->value[CENTER_Z_INDEX].f32);
    }
    if (CENTER_X_PERCENT_INDEX < actualSize) {
        centerX.SetValue(item->value[CENTER_X_PERCENT_INDEX].f32);
        centerX.SetUnit(DimensionUnit::PERCENT);
    }
    if (CENTER_Y_PERCENT_INDEX < actualSize) {
        centerY.SetValue(item->value[CENTER_Y_PERCENT_INDEX].f32);
        centerY.SetUnit(DimensionUnit::PERCENT);
    }
    if (CENTER_Z_PERCENT_INDEX < actualSize) {
        centerZ.SetValue(item->value[CENTER_Z_PERCENT_INDEX].f32);
        centerZ.SetUnit(DimensionUnit::PERCENT);
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransitionCenter(node->uiNodeHandle, centerX.Value(),
        static_cast<int32_t>(centerX.Unit()), centerY.Value(), static_cast<int32_t>(centerY.Unit()), centerZ.Value(),
        static_cast<int32_t>(centerZ.Unit()));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetOpacityTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_THREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, OPACITY_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    float opacity = DEFAULT_OPACITY;
    if (actualSize > 0) {
        opacity = item->value[0].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, OPACITY_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, opacity, &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetRotateTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_SEVEN_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, ROTATE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::array<float, ARRAY_SIZE> rotateArray;
    for (int32_t i = 0; i < actualSize && i < rotateArray.size(); i++) {
        rotateArray[i] = item->value[i].f32;
    }
    float angle = 0.0f;
    if (ROTATE_ANGLE_INDEX < actualSize) {
        angle = item->value[ROTATE_ANGLE_INDEX].f32;
    }
    float perspective = 0.0f;
    if (ROTATE_PERSPECTIVE_INDEX < actualSize) {
        perspective = item->value[ROTATE_PERSPECTIVE_INDEX].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, ROTATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(
        node->uiNodeHandle, &rotateArray[0], ARRAY_SIZE, perspective, angle, &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScaleTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, SCALE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    for (size_t i = 0; i < static_cast<uint32_t>(actualSize) && i < scaleFloatArray.size(); i++) {
        scaleFloatArray[i] = item->value[i].f32;
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, SCALE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTranslateTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_FIVE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, TRANSLATE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    CalcDimension xDimension(0, static_cast<DimensionUnit>(unit));
    if (X_INDEX < actualSize) {
        xDimension.SetValue(item->value[X_INDEX].f32);
    }
    CalcDimension yDimension(0, static_cast<DimensionUnit>(unit));
    if (Y_INDEX < actualSize) {
        yDimension.SetValue(item->value[Y_INDEX].f32);
    }
    CalcDimension zDimension(0, static_cast<DimensionUnit>(unit));
    if (Z_INDEX < actualSize) {
        zDimension.SetValue(item->value[Z_INDEX].f32);
    }
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, TRANSLATE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, xDimension.Value(),
        static_cast<int32_t>(xDimension.Unit()), yDimension.Value(), static_cast<int32_t>(yDimension.Unit()),
        zDimension.Value(), static_cast<int32_t>(zDimension.Unit()), &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMoveTransition(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_THREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!CheckAnimation(item, actualSize, MOVE_ANIMATION_BASE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int edgeType = ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START;
    if (!InRegion(NUM_0, NUM_3, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    edgeType = item->value[NUM_0].i32;
    ArkUIAnimationOptionType animationOption;
    ParseAnimation(item, actualSize, animationOption, MOVE_ANIMATION_BASE);
    fullImpl->getNodeModifiers()->getCommonModifier()->setMoveTransition(
        node->uiNodeHandle, edgeType, &animationOption);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    CalcDimension xDimension(0, static_cast<DimensionUnit>(unit));
    xDimension.SetValue(item->value[NUM_0].f32);
    CalcDimension yDimension(0, static_cast<DimensionUnit>(unit));
    yDimension.SetValue(item->value[NUM_1].f32);
    std::array<float, TWO> offsetValue = { xDimension.Value(), yDimension.Value() };
    std::array<int32_t, TWO> offsetUnit = { static_cast<int32_t>(xDimension.Unit()),
        static_cast<int32_t>(yDimension.Unit()) };
    fullImpl->getNodeModifiers()->getCommonModifier()->setOffset(node->uiNodeHandle, &offsetValue[0], &offsetUnit[0]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMarkAnchor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWO_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    CalcDimension xDimension(0, static_cast<DimensionUnit>(unit));
    xDimension.SetValue(item->value[NUM_0].f32);
    CalcDimension yDimension(0, static_cast<DimensionUnit>(unit));
    yDimension.SetValue(item->value[NUM_1].f32);
    fullImpl->getNodeModifiers()->getCommonModifier()->setMarkAnchor(node->uiNodeHandle, xDimension.Value(),
        unit, yDimension.Value(), unit);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAlignRules(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    node->alignRuleOption = item->object;

    if (item->size < 0 || item->object == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    auto* option = reinterpret_cast<ArkUI_AlignmentRuleOption*>(item->object);
    char* anchors[NUM_6];
    ArkUI_Int32 aligns[NUM_6];
    if (option->left.hasValue) {
        // 0 -> left
        anchors[0] = const_cast<char*>(option->left.anchor.c_str());
        aligns[0] = option->left.align + NUM_1;
    }
    if (option->middle.hasValue) {
        // 1 -> middle
        anchors[1] = const_cast<char*>(option->middle.anchor.c_str());
        aligns[1] = option->middle.align + NUM_1;
    }
    if (option->right.hasValue) {
        // 2 -> right
        anchors[2] = const_cast<char*>(option->right.anchor.c_str());
        aligns[2] = option->right.align + NUM_1;
    }
    if (option->top.hasValue) {
        // 3 -> top
        anchors[3] = const_cast<char*>(option->top.anchor.c_str());
        aligns[3] = option->top.align + NUM_1;
    }
    if (option->center.hasValue) {
        // 4 -> center
        anchors[4] = const_cast<char*>(option->center.anchor.c_str());
        aligns[4] = option->center.align + NUM_1;
    }
    if (option->bottom.hasValue) {
        // 5 -> bottom
        anchors[5] = const_cast<char*>(option->bottom.anchor.c_str());
        aligns[5] = option->bottom.align + NUM_1;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAlignRules(node->uiNodeHandle, anchors, aligns, NUM_6);
    fullImpl->getNodeModifiers()->getCommonModifier()->setBias(
        node->uiNodeHandle, option->biasHorizontal, option->biasVertical);
    return ERROR_CODE_NO_ERROR;
}

void ResetAlignRules(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAlignRules(node->uiNodeHandle);
    node->alignRuleOption = nullptr;
}

int32_t SetTextContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLineHeight(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_FP);
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextLineHeight(
                node->uiNodeHandle, item->value[0].f32, unit);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLineHeight(
                node->uiNodeHandle, item->value[0].f32, unit);
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputLineHeight(
                node->uiNodeHandle, item->value[0].f32, unit);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaLineHeight(
                node->uiNodeHandle, item->value[0].f32, unit);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetDecoration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (DECORATION_STYLE_INDEX < actualSize && (item->value[DECORATION_STYLE_INDEX].i32 < 0 ||
        item->value[DECORATION_STYLE_INDEX].i32 > static_cast<int32_t>(ARKUI_TEXT_DECORATION_STYLE_WAVY))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t decoration = item->value[0].i32;
    auto decorationColor = Color::BLACK.GetValue();
    if (DECORATION_COLOR_INDEX < actualSize) {
        decorationColor = item->value[DECORATION_COLOR_INDEX].u32;
    }
    int32_t decorationStyle = 0;
    if (DECORATION_STYLE_INDEX < actualSize) {
        decorationStyle = item->value[DECORATION_STYLE_INDEX].i32;
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanDecoration(
                node->uiNodeHandle, decoration, decorationColor, decorationStyle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextDecoration(
                node->uiNodeHandle, decoration, decorationColor, decorationStyle);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextCase(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_CASE_UPPER)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanTextCase(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextCase(node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLetterSpacing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIStringAndFloat letterSpacingValue = { item->value[0].f32, nullptr };
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->setSpanLetterSpacing(
                node->uiNodeHandle, &letterSpacingValue);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextLetterSpacing(
                node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputLetterSpacing(
                node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaLetterSpacing(
                node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMaxLines(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextMaxLines(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputMaxLines(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaMaxLines(
                node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_ALIGNMENT_JUSTIFY)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputTextAlign(
                node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextAlign(node->uiNodeHandle, item->value[0].i32);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaTextAlign(
                node->uiNodeHandle, item->value[0].i32);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextOverflow(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_TEXT_OVERFLOW_MARQUEE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setTextOverflow(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextIndent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setTextIndent(node->uiNodeHandle,
        item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    return ERROR_CODE_NO_ERROR;
}

void ResetTextIndent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextIndent(node->uiNodeHandle,
        0.0f, UNIT_FP);
}

int32_t SetTextWordBreak(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setWordBreak(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextWordBreak(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextWordBreak(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextWordBreak(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetWordBreak(node->uiNodeHandle);
}

int32_t SetTextSelectedBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextSelectedBackgroundColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextSelectedBackgroundColor(ArkUI_NodeHandle node)
{
    g_numberValues[0].u32 = GetFullImpl()->getNodeModifiers()->getTextModifier()->getTextSelectedBackgroundColor(
        node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetTextSelectedBackgroundColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextSelectedBackgroundColor(node->uiNodeHandle);
}

int32_t SetTextEllipsisMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setEllipsisMode(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLineSpacing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == ARKUI_NODE_TEXT) {
        fullImpl->getNodeModifiers()->getTextModifier()->setTextLineSpacing(
            node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTextContentWithStyledString(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = GetFullImpl();
    auto* styledString = reinterpret_cast<ArkUI_StyledString*>(item->object);
    fullImpl->getNodeModifiers()->getTextModifier()->setTextContentWithStyledString(node->uiNodeHandle, styledString);
    return ERROR_CODE_NO_ERROR;
}

void ResetTextContentWithStyledString(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextContentWithStyledString(node->uiNodeHandle);
}

int32_t SetHalfLeading(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || !InRegion(NUM_0, NUM_1, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setTextHalfLeading(
        node->uiNodeHandle, item->value[NUM_0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetHalfLeading(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextHalfLeading(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetHalfLeading(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextHalfLeading(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetTextEllipsisMode(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextEllipsisMode(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetLineSpacing(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    if (node->type == ARKUI_NODE_TEXT) {
        g_numberValues[NUM_0].f32 =
            fullImpl->getNodeModifiers()->getTextModifier()->getTextLineSpacing(node->uiNodeHandle);
        g_attributeItem.size = REQUIRED_ONE_PARAM;
    }
    return &g_attributeItem;
}

void ResetTextEllipsisMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetEllipsisMode(node->uiNodeHandle);
}

void ResetLineSpacing(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLineSpacing(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetTextEnableDateDetector(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setEnableDataDetector(
        node->uiNodeHandle, static_cast<uint32_t>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextEnableDateDetector(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getEnableDataDetector(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

void ResetTextEnableDateDetector(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetEnableDataDetector(node->uiNodeHandle);
}

int32_t SetTextDataDetectorConfig(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    ArkUI_Uint32 values[item->size];
    for (int i = 0; i < item->size; i++) {
        values[i] = item->value[i].i32;
    }
    fullImpl->getNodeModifiers()->getTextModifier()->setTextDataDetectorConfig(
        node->uiNodeHandle, values, item->size);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetTextDataDetectorConfig(ArkUI_NodeHandle node)
{
    ArkUI_Int32 values[32];
    auto* fullImpl = GetFullImpl();
    auto size = fullImpl->getNodeModifiers()->getTextModifier()->getTextDataDetectorConfig(
        node->uiNodeHandle, &values);
    for (auto i = 0; i < size; i++) {
        g_numberValues[i].i32 = values[i];
    }
    g_attributeItem.size = size;
    return &g_attributeItem;
}

void ResetTextDataDetectorConfig(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextDataDetectorConfig(node->uiNodeHandle);
}

int32_t SetFontFeature(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->string == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputFontFeature(
                node->uiNodeHandle, item->string);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->setTextFontFeature(node->uiNodeHandle, item->string);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontFeature(
                node->uiNodeHandle, item->string);
            break;
        default:
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetFontFeature(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    ArkUI_CharPtr feature = nullptr;
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            feature = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputFontFeature(node->uiNodeHandle);
            g_attributeItem.string = (feature != nullptr ? feature : EMPTY_STR.c_str());
            break;
        case ARKUI_NODE_TEXT:
            feature = fullImpl->getNodeModifiers()->getTextModifier()->getTextFontFeature(node->uiNodeHandle);
            g_attributeItem.string = (feature != nullptr ? feature : EMPTY_STR.c_str());
            break;
        case ARKUI_NODE_TEXT_AREA:
            feature = fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaFontFeature(node->uiNodeHandle);
            g_attributeItem.string = (feature != nullptr ? feature : EMPTY_STR.c_str());
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

void ResetFontFeature(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputFontFeature(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextFontFeature(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaFontFeature(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

int32_t SetSpanContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetSpanTextBackgroundStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    float radiusVals[ALLOW_SIZE_4] = { 0, 0, 0, 0 };
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    int radiusUnits[ALLOW_SIZE_4] = { unit, unit, unit, unit };

    if (item->size == ALLOW_SIZE_2) {
        if (LessNotEqual(item->value[NUM_1].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            radiusVals[i] = item->value[1].f32;
        }
    } else if (item->size == ALLOW_SIZE_5) {
        for (int i = 0; i < ALLOW_SIZE_4; ++i) {
            if (LessNotEqual(item->value[i + NUM_1].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                radiusVals[i] = item->value[i + NUM_1].f32;
            }
        }
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }

    fullImpl->getNodeModifiers()->getSpanModifier()->setSpanTextBackgroundStyle(
        node->uiNodeHandle, item->value[NUM_0].u32, radiusVals, radiusUnits, NUM_4);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetVerticalAlign(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_SPAN_ALIGNMENT_TOP)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(
        node->uiNodeHandle, IMAGE_SPAN_ALIGNMENT_ARRAY[item->value[0].i32]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetPixelMapSrc(ArkUI_NodeHandle node, const std::shared_ptr<Napi::DrawableDescriptor>& descriptor)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setPixelMap(node->uiNodeHandle, descriptor.get());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetPixelMapArraySrc(ArkUI_NodeHandle node, const std::shared_ptr<Napi::AnimatedDrawableDescriptor>& descriptor)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setPixelMapArray(node->uiNodeHandle, descriptor.get());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetResourceSrc(ArkUI_NodeHandle node, const std::shared_ptr<ArkUI_Resource>& resource)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setResourceSrc(node->uiNodeHandle, resource.get());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetImageSrc(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    bool isString = CheckAttributeString(item);
    bool isObject = CheckAttributeObject(item);
    if ((isString && isObject) || (!isString && !isObject)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (isString) {
        auto* fullImpl = GetFullImpl();
        fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, item->string);
        return ERROR_CODE_NO_ERROR;
    }

    auto drawableDescriptor = reinterpret_cast<ArkUI_DrawableDescriptor*>(item->object);
    if (!drawableDescriptor) {
        return ERROR_CODE_PARAM_INVALID;
    }
    node->drawableDescriptor = drawableDescriptor;
    if (!drawableDescriptor->drawableDescriptor && !drawableDescriptor->resource &&
        !drawableDescriptor->animatedDrawableDescriptor) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (drawableDescriptor->drawableDescriptor) {
        return SetPixelMapSrc(node, drawableDescriptor->drawableDescriptor);
    } else if (drawableDescriptor->animatedDrawableDescriptor) {
        return SetPixelMapArraySrc(node, drawableDescriptor->animatedDrawableDescriptor);
    } else {
        return SetResourceSrc(node, drawableDescriptor->resource);
    }
}

int32_t SetImageSpanSrc(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (CheckAttributeString(item)) {
        fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, item->string);
        return ERROR_CODE_NO_ERROR;
    } else {
        return SetImageSrc(node, item);
    }
}

int32_t SetImageSpanBaselineOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageSpanModifier()->setImageSpanBaselineOffset(
        node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_FP));
    return ERROR_CODE_NO_ERROR;
}

void ResetImageSpanBaselineOffset(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageSpanModifier()->
        resetImageSpanBaselineOffset(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageSpanBaselineOffset(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_FP);
    g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getImageSpanModifier()->
        getImageSpanBaselineOffset(node->uiNodeHandle, unit);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetObjectFit(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 >
        static_cast<int32_t>(ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM_END)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setObjectFit(
        node->uiNodeHandle, OBJECT_FIT_ARRAY[item->value[0].i32]);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetInterpolation(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_INTERPOLATION_HIGH)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setImageInterpolation(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetObjectRepeat(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_REPEAT_XY)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setObjectRepeat(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetColorFilter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_TWENTY_PARAM);
    bool isObject = CheckAttributeObject(item);
    if ((actualSize < 0 && !isObject) || (actualSize > 0 && isObject)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (isObject) {
        fullImpl->getNodeModifiers()->getImageModifier()->setDrawingColorFilter(node->uiNodeHandle, item->object);
        return ERROR_CODE_NO_ERROR;
    }
    std::vector<float> colorFloatArray;
    for (size_t i = 0; i < static_cast<uint32_t>(actualSize) && i < REQUIRED_TWENTY_PARAM; i++) {
        colorFloatArray.emplace_back(item->value[i].f32);
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setColorFilter(
        node->uiNodeHandle, &colorFloatArray[0], colorFloatArray.size());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAutoResize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setAutoResize(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetAlt(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item || (!item->string && !item->object)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    auto drawableDescriptor = reinterpret_cast<ArkUI_DrawableDescriptor*>(item->object);
    ArkUIImageSourceInfo imageInfo;
    imageInfo.url = item->string;
    node->altDrawableDescriptor = drawableDescriptor;
    if (drawableDescriptor && drawableDescriptor->resource) {
        imageInfo.resource = drawableDescriptor->resource.get();
    } else if (drawableDescriptor && drawableDescriptor->drawableDescriptor) {
        imageInfo.pixelMap = drawableDescriptor->drawableDescriptor.get();
    } else {
        node->altDrawableDescriptor = nullptr;
        if (!item->string) {
            return ERROR_CODE_PARAM_INVALID;
        }
    }
    imageInfo.pixelMapArray = nullptr;
    fullImpl->getNodeModifiers()->getImageModifier()->setAltSourceInfo(node->uiNodeHandle, &imageInfo);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetResizable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, NUM_4);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setImageResizable(
        node->uiNodeHandle, item->value[NUM_0].f32, item->value[NUM_1].f32,
        item->value[NUM_2].f32, item->value[NUM_3].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetResizable(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setImageResizable(
        node->uiNodeHandle, 0.0f, 0.0f,
        0.0f, 0.0f);
}

const ArkUI_AttributeItem* GetResizable(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    std::array<float, NUM_4> resizableArray;
    fullImpl->getNodeModifiers()->getImageModifier()->getImageResizable(
        node->uiNodeHandle, &resizableArray[0], NUM_4);
    g_numberValues[NUM_0].f32 = resizableArray[NUM_0];
    g_numberValues[NUM_1].f32 = resizableArray[NUM_1];
    g_numberValues[NUM_2].f32 = resizableArray[NUM_2];
    g_numberValues[NUM_3].f32 = resizableArray[NUM_3];
    g_attributeItem.size = NUM_4;
    return &g_attributeItem;
}

int32_t SetImageDraggable(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setImageDraggable(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

int32_t SetRenderMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < 0 || item->value[0].i32 > static_cast<int32_t>(ARKUI_IMAGE_RENDER_MODE_TEMPLATE)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getImageModifier()->setRenderMode(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetRenderMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetRenderMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRenderMode(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getImageModifier()->getRenderMode(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetFitOriginalSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < DEFAULT_FALSE || item->value[0].i32 > DEFAULT_TRUE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setFitOriginalSize(
        node->uiNodeHandle, static_cast<bool>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetFitOriginalSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetFitOriginalSize(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFitOriginalSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getImageModifier()->getFitOriginalSize(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetFillColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setFillColor(
        node->uiNodeHandle, static_cast<ArkUI_Uint32>(item->value[0].u32));
    return ERROR_CODE_NO_ERROR;
}

void ResetFillColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetFillColor(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetFillColor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getImageModifier()->getFillColor(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetHintRadius(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setHintRadius(
        node->uiNodeHandle, item->value[0].f32, GetDefaultUnit(node, UNIT_VP));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetHintRadius(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].f32 =
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getHintRadius(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetSelectedDate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_THREE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!IsValidDate(item->value[SELECTED_YEAR_INDEX].u32,
        item->value[SELECTED_MONTH_INDEX].u32, item->value[SELECTED_DAY_INDEX].u32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    uint32_t selectedYear = item->value[SELECTED_YEAR_INDEX].u32;
    uint32_t selectedMonth = item->value[SELECTED_MONTH_INDEX].u32;
    uint32_t selectedDay = item->value[SELECTED_DAY_INDEX].u32;
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setSelectDate(
        node->uiNodeHandle, selectedYear, selectedMonth, selectedDay);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSelectedDate(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto selectedDate = fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getSelectedDate(node->uiNodeHandle);
    g_numberValues[SELECTED_YEAR_INDEX].u32 = selectedDate.year;
    g_numberValues[SELECTED_MONTH_INDEX].u32 = selectedDate.month;
    g_numberValues[SELECTED_DAY_INDEX].u32 = selectedDate.day;
    g_attributeItem.size = REQUIRED_THREE_PARAM;
    return &g_attributeItem;
}

int32_t SetCalendarPickerStartDate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto startYear = StringToInt(date[NUM_0].c_str());
    auto startMonth = StringToInt(date[NUM_1].c_str());
    auto startDay = StringToInt(date[NUM_2].c_str());
    if (startYear > 0 && startMonth > 0 && startDay > 0) {
        startYear = static_cast<uint32_t>(startYear);
        startMonth = static_cast<uint32_t>(startMonth);
        startDay = static_cast<uint32_t>(startDay);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!IsValidDate(startYear, startMonth, startDay)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setStartDate(
            node->uiNodeHandle, startYear, startMonth, startDay);
    } else {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCalendarPickerStartDate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        auto startDate = fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getStartDate(node->uiNodeHandle);
        g_attributeItem.string = startDate;
    }
    return &g_attributeItem;
}

int32_t SetCalendarPickerEndDate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->string) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::vector<std::string> date;
    StringUtils::StringSplitter(item->string, '-', date);
    if (date.size() != NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto endYear = StringToInt(date[NUM_0].c_str());
    auto endMonth = StringToInt(date[NUM_1].c_str());
    auto endDay = StringToInt(date[NUM_2].c_str());
    if (endYear > 0 && endMonth > 0 && endDay > 0) {
        endYear = static_cast<uint32_t>(endYear);
        endMonth = static_cast<uint32_t>(endMonth);
        endDay = static_cast<uint32_t>(endDay);
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!IsValidDate(endYear, endMonth, endDay)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setEndDate(
            node->uiNodeHandle, endYear, endMonth, endDay);
    } else {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCalendarPickerEndDate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        auto endDate = fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getEndDate(node->uiNodeHandle);
        g_attributeItem.string = endDate;
    }
    return &g_attributeItem;
}

int32_t SetEdgeAlignment(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (EDGE_TYPE_INDEX < actualSize &&
        (item->value[EDGE_TYPE_INDEX].i32 < static_cast<int32_t>(ARKUI_CALENDAR_ALIGNMENT_START) ||
            item->value[EDGE_TYPE_INDEX].i32 > static_cast<int32_t>(ARKUI_CALENDAR_ALIGNMENT_END))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int32_t defaultAlignment = 0;
    if (EDGE_TYPE_INDEX < actualSize) {
        defaultAlignment = item->value[EDGE_TYPE_INDEX].i32;
    }
    std::vector<float> sizeArray;
    float xOffset = 0.0f;
    if (EDGE_OFFSET_X_INDEX < actualSize) {
        xOffset = item->value[EDGE_OFFSET_X_INDEX].f32;
    }
    sizeArray.emplace_back(xOffset);
    float yOffset = 0.0f;
    if (EDGE_OFFSET_Y_INDEX < actualSize) {
        yOffset = item->value[EDGE_OFFSET_Y_INDEX].f32;
    }
    sizeArray.emplace_back(yOffset);
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    std::vector<int32_t> unitArray = { unit, unit };
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setEdgeAlign(
        node->uiNodeHandle, &sizeArray[0], &unitArray[0], static_cast<int32_t>(sizeArray.size()), defaultAlignment);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetEdgeAlignment(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto edgeAlign = fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getEdgeAlign(node->uiNodeHandle);
    g_numberValues[EDGE_TYPE_INDEX].i32 = edgeAlign.alignType;
    g_numberValues[EDGE_OFFSET_X_INDEX].f32 = edgeAlign.offsetX;
    g_numberValues[EDGE_OFFSET_Y_INDEX].f32 = edgeAlign.offsetY;
    g_attributeItem.size = REQUIRED_THREE_PARAM;
    return &g_attributeItem;
}

int32_t SetCalendarPickerTextStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    auto actualSize = CheckAttributeItemArray(item, 0);
    if (actualSize < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (CALENDAR_PICKER_FONT_SIZE_INDEX < actualSize &&
        LessNotEqual(item->value[CALENDAR_PICKER_FONT_SIZE_INDEX].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (CALENDAR_PICKER_FONT_WEIGHT_INDEX < actualSize &&
        (item->value[CALENDAR_PICKER_FONT_WEIGHT_INDEX].i32 < 0 ||
            item->value[CALENDAR_PICKER_FONT_WEIGHT_INDEX].i32 > static_cast<int32_t>(ARKUI_FONT_WEIGHT_REGULAR))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    uint32_t fontColor = Color::BLACK.GetValue();
    if (CALENDAR_PICKER_FONT_COLOR_INDEX < actualSize) {
        fontColor = item->value[CALENDAR_PICKER_FONT_COLOR_INDEX].u32;
    }
    float fontSize = 0.0f;
    std::vector<float> fontSizeArray;
    if (CALENDAR_PICKER_FONT_SIZE_INDEX < actualSize) {
        fontSize = item->value[CALENDAR_PICKER_FONT_SIZE_INDEX].f32;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    fontSizeArray.emplace_back(fontSize);
    fontSizeArray.emplace_back(static_cast<float>(unit));
    int32_t fontWeight = 0;
    if (CALENDAR_PICKER_FONT_WEIGHT_INDEX < actualSize) {
        fontWeight = item->value[CALENDAR_PICKER_FONT_WEIGHT_INDEX].i32;
    }
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setTextStyleWithWeightEnum(
        node->uiNodeHandle, fontColor, fontSize, unit, fontWeight);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCalendarPickerTextStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto textStyle =
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->getCalendarPickerTextStyle(node->uiNodeHandle);
    g_numberValues[CALENDAR_PICKER_FONT_COLOR_INDEX].u32 = textStyle.fontColor;
    g_numberValues[CALENDAR_PICKER_FONT_SIZE_INDEX].f32 = textStyle.fontSize;
    g_numberValues[CALENDAR_PICKER_FONT_WEIGHT_INDEX].i32 = textStyle.fontWeight;
    g_attributeItem.size = REQUIRED_THREE_PARAM;
    return &g_attributeItem;
}

void ResetHintRadius(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->setHintRadius(
        node->uiNodeHandle, DEFAULT_HINT_RADIUS, UNIT_VP);
}

void ResetSelectedDate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->resetSelectDate(node->uiNodeHandle);
}

void ResetCalendarPickerStartDate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->resetStartDate(node->uiNodeHandle);
    }
}

void ResetCalendarPickerEndDate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    if (fullImpl && fullImpl->getNodeModifiers() && fullImpl->getNodeModifiers()->getCalendarPickerModifier()) {
        fullImpl->getNodeModifiers()->getCalendarPickerModifier()->resetEndDate(node->uiNodeHandle);
    }
}

void ResetEdgeAlignment(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->resetEdgeAlign(node->uiNodeHandle);
}

void ResetCalendarPickerTextStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCalendarPickerModifier()->resetTextStyle(node->uiNodeHandle);
}

void ResetBackgroundImageSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundImageSize(node->uiNodeHandle);
}

void ResetBackgroundImageSizeWithStyle(ArkUI_NodeHandle node)
{
    ResetBackgroundImageSize(node);
}

void ResetBackgroundBlurStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetBackgroundBlurStyle(node->uiNodeHandle);
}

void ResetTransformCenter(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    CalcDimension centerX(HALF, DimensionUnit::PERCENT);
    CalcDimension centerY(HALF, DimensionUnit::PERCENT);
    CalcDimension centerZ(0, DimensionUnit::VP);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTransitionCenter(node->uiNodeHandle, centerX.Value(),
        static_cast<int32_t>(centerX.Unit()), centerY.Value(), static_cast<int32_t>(centerY.Unit()), centerZ.Value(),
        static_cast<int32_t>(centerZ.Unit()));
}

void ResetOpacityTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setOpacityTransition(
        node->uiNodeHandle, DEFAULT_OPACITY, &animationOption);
}

void ResetRotateTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> rotateArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setRotateTransition(
        node->uiNodeHandle, &rotateArray[0], ARRAY_SIZE, 0.0f, 0.0f, &animationOption);
}

void ResetScaleTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
}

void ResetTranslateTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    std::array<float, ARRAY_SIZE> scaleFloatArray;
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setScaleTransition(
        node->uiNodeHandle, &scaleFloatArray[0], scaleFloatArray.size(), &animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setTranslateTransition(node->uiNodeHandle, 0.0f,
        UNIT_VP, 0.0f, UNIT_VP, 0.0f,
        UNIT_VP, &animationOption);
}

void ResetMoveTransition(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    ArkUIAnimationOptionType animationOption;
    ResetAnimation(animationOption);
    fullImpl->getNodeModifiers()->getCommonModifier()->setMoveTransition(
        node->uiNodeHandle, ARKUI_TRANSITION_EDGE_TOP, &animationOption);
}

void ResetOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetOffset(node->uiNodeHandle);
}

void ResetMarkAnchor(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->resetMarkAnchor(node->uiNodeHandle);
}

void ResetTextContent(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->setContent(node->uiNodeHandle, "");
}

void ResetLineHeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLineHeight(node->uiNodeHandle);
            break;
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanLineHeight(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputLineHeight(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaLineHeight(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetDecoration(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanDecoration(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextDecoration(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetTextCase(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanTextCase(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextCase(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetLetterSpacing(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanLetterSpacing(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextLetterSpacing(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputLetterSpacing(
                node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaLetterSpacing(
                node->uiNodeHandle);
        default:
            break;
    }
}

void ResetMaxLines(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextMaxLines(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLines(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetTextAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT_INPUT:
            fullImpl->getNodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT:
            fullImpl->getNodeModifiers()->getTextModifier()->resetTextAlign(node->uiNodeHandle);
            break;
        case ARKUI_NODE_TEXT_AREA:
            fullImpl->getNodeModifiers()->getTextAreaModifier()->resetTextAreaTextAlign(node->uiNodeHandle);
            break;
        default:
            break;
    }
}

void ResetTextOverflow(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextModifier()->resetTextOverflow(node->uiNodeHandle);
}

void ResetSpanContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSpanModifier()->setContent(node->uiNodeHandle, "");
}

void ResetSpanTextBackgroundStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSpanModifier()->resetSpanTextBackgroundStyle(node->uiNodeHandle);
}

void ResetImageSpanSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->setSrc(node->uiNodeHandle, "");
}

void ResetVerticalAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageSpanModifier()->resetImageSpanVerticalAlign(
        node->uiNodeHandle);
}

void ResetImageSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetImageSrc(node->uiNodeHandle);
}

void ResetObjectFit(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectFit(node->uiNodeHandle);
}

void ResetInterpolation(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetImageInterpolation(node->uiNodeHandle);
}

void ResetObjectRepeat(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetObjectRepeat(node->uiNodeHandle);
}

void ResetColorFilter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetColorFilter(node->uiNodeHandle);
}

void ResetAutoResize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetAutoResize(node->uiNodeHandle);
}

void ResetAlt(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetAlt(node->uiNodeHandle);
}

void ResetImageDraggable(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageModifier()->resetImageDraggable(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetBackgroundImageSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto backGroundImageSize =
        fullImpl->getNodeModifiers()->getCommonModifier()->getBackgroundImageSize(
            node->uiNodeHandle, GetDefaultUnit(node, UNIT_VP));
    g_numberValues[BACKGROUND_IMAGE_WIDTH_INDEX].f32 = backGroundImageSize.xValue;
    g_numberValues[BACKGROUND_IMAGE_HEIGHT_INDEX].f32 = backGroundImageSize.yValue;
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetBackgroundImageSizeWithStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 =
        fullImpl->getNodeModifiers()->getCommonModifier()->getBackgroundImageSizeWithStyle(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetBackgroundBlurStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto backGroundBlurStyle =
        fullImpl->getNodeModifiers()->getCommonModifier()->getBackgroundBlurStyle(node->uiNodeHandle);
    g_numberValues[BLUR_STYLE_INDEX].i32 = UnConvertBlurStyle(backGroundBlurStyle.blurStyle);
    g_numberValues[COLOR_MODE_INDEX].i32 = backGroundBlurStyle.colorMode;
    g_numberValues[ADAPTIVE_COLOR_INDEX].i32 = backGroundBlurStyle.adaptiveColor;
    g_numberValues[SCALE_INDEX].f32 = backGroundBlurStyle.scale;
    g_numberValues[GRAY_SCALE_START].f32 = backGroundBlurStyle.grayScaleStart;
    g_numberValues[GRAY_SCALE_END].f32 = backGroundBlurStyle.grayScaleEnd;
    g_attributeItem.size = NUM_6;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTransformCenter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto transformCenter = fullImpl->getNodeModifiers()->getCommonModifier()->getTransformCenter(node->uiNodeHandle);
    g_numberValues[CENTER_X_INDEX].f32 = transformCenter.centerX;
    g_numberValues[CENTER_Y_INDEX].f32 = transformCenter.centerY;
    g_numberValues[CENTER_Z_INDEX].f32 = transformCenter.centerZ;
    g_attributeItem.size = REQUIRED_THREE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetOpacityTransition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto opacityTransition =
        fullImpl->getNodeModifiers()->getCommonModifier()->getOpacityTransition(node->uiNodeHandle);
    const int32_t animationDurationIndex = OPACITY_ANIMATION_BASE + ANIMATION_DURATION_INDEX;
    const int32_t animationCurveIndex = OPACITY_ANIMATION_BASE + ANIMATION_CURVE_INDEX;
    const int32_t animationDelayIndex = OPACITY_ANIMATION_BASE + ANIMATION_DELAY_INDEX;
    const int32_t animationIterationsIndex = OPACITY_ANIMATION_BASE + ANIMATION_INTERATION_INDEX;
    const int32_t animationPlayModeIndex = OPACITY_ANIMATION_BASE + ANIMATION_PLAY_MODE_INDEX;
    const int32_t animationTempoIndex = OPACITY_ANIMATION_BASE + ANIMATION_TEMPO_INDEX;
    g_numberValues[0].f32 = opacityTransition.opacity;
    g_numberValues[animationDurationIndex].i32 = opacityTransition.animation.duration;
    g_numberValues[animationCurveIndex].i32 = opacityTransition.animation.curve;
    g_numberValues[animationDelayIndex].i32 = opacityTransition.animation.delay;
    g_numberValues[animationIterationsIndex].i32 = opacityTransition.animation.iteration;
    g_numberValues[animationPlayModeIndex].i32 =UnConvertAnimationDirection(opacityTransition.animation.playMode);
    g_numberValues[animationTempoIndex].f32 = opacityTransition.animation.tempo;
    g_attributeItem.size = REQUIRED_SEVEN_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetRotateTransition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto rotateTransition = fullImpl->getNodeModifiers()->getCommonModifier()->getRotateTransition(node->uiNodeHandle);
    const int32_t animationDurationIndex = ROTATE_ANIMATION_BASE + ANIMATION_DURATION_INDEX;
    const int32_t animationCurveIndex = ROTATE_ANIMATION_BASE + ANIMATION_CURVE_INDEX;
    const int32_t animationDelayIndex = ROTATE_ANIMATION_BASE + ANIMATION_DELAY_INDEX;
    const int32_t animationIterationsIndex = ROTATE_ANIMATION_BASE + ANIMATION_INTERATION_INDEX;
    const int32_t animationPlayModeIndex = ROTATE_ANIMATION_BASE + ANIMATION_PLAY_MODE_INDEX;
    const int32_t animationTempoIndex = ROTATE_ANIMATION_BASE + ANIMATION_TEMPO_INDEX;
    g_numberValues[X_INDEX].f32 = rotateTransition.xRotation;
    g_numberValues[Y_INDEX].f32 = rotateTransition.yRotation;
    g_numberValues[Z_INDEX].f32 = rotateTransition.zRotation;
    g_numberValues[ROTATE_ANGLE_INDEX].f32 = rotateTransition.angle;
    g_numberValues[ROTATE_PERSPECTIVE_INDEX].f32 = rotateTransition.perspective;
    g_numberValues[animationDurationIndex].i32 = rotateTransition.animation.duration;
    g_numberValues[animationCurveIndex].i32 = rotateTransition.animation.curve;
    g_numberValues[animationDelayIndex].i32 = rotateTransition.animation.delay;
    g_numberValues[animationIterationsIndex].i32 = rotateTransition.animation.iteration;
    g_numberValues[animationPlayModeIndex].i32 = UnConvertAnimationDirection(rotateTransition.animation.playMode);
    g_numberValues[animationTempoIndex].f32 = rotateTransition.animation.tempo;
    g_attributeItem.size = NUM_11;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetScaleTransition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto scaleTransition = fullImpl->getNodeModifiers()->getCommonModifier()->getScaleTransition(node->uiNodeHandle);
    const int32_t animationDurationIndex = SCALE_ANIMATION_BASE + ANIMATION_DURATION_INDEX;
    const int32_t animationCurveIndex = SCALE_ANIMATION_BASE + ANIMATION_CURVE_INDEX;
    const int32_t animationDelayIndex = SCALE_ANIMATION_BASE + ANIMATION_DELAY_INDEX;
    const int32_t animationIterationsIndex = SCALE_ANIMATION_BASE + ANIMATION_INTERATION_INDEX;
    const int32_t animationPlayModeIndex = SCALE_ANIMATION_BASE + ANIMATION_PLAY_MODE_INDEX;
    const int32_t animationTempoIndex = SCALE_ANIMATION_BASE + ANIMATION_TEMPO_INDEX;
    g_numberValues[X_INDEX].f32 = scaleTransition.xScale;
    g_numberValues[Y_INDEX].f32 = scaleTransition.yScale;
    g_numberValues[Z_INDEX].f32 = scaleTransition.zScale;
    g_numberValues[animationDurationIndex].i32 = scaleTransition.animation.duration;
    g_numberValues[animationCurveIndex].i32 = scaleTransition.animation.curve;
    g_numberValues[animationDelayIndex].i32 = scaleTransition.animation.delay;
    g_numberValues[animationIterationsIndex].i32 = scaleTransition.animation.iteration;
    g_numberValues[animationPlayModeIndex].i32 = UnConvertAnimationDirection(scaleTransition.animation.playMode);
    g_numberValues[animationTempoIndex].f32 = scaleTransition.animation.tempo;
    g_attributeItem.size = NUM_9;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTranslateTransition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto translateTransition =
        fullImpl->getNodeModifiers()->getCommonModifier()->getTranslateTransition(node->uiNodeHandle);
    const int32_t animationDurationIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_DURATION_INDEX;
    const int32_t animationCurveIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_CURVE_INDEX;
    const int32_t animationDelayIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_DELAY_INDEX;
    const int32_t animationIterationsIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_INTERATION_INDEX;
    const int32_t animationPlayModeIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_PLAY_MODE_INDEX;
    const int32_t animationTempoIndex = TRANSLATE_ANIMATION_BASE + ANIMATION_TEMPO_INDEX;
    g_numberValues[X_INDEX].f32 = translateTransition.xTransition;
    g_numberValues[Y_INDEX].f32 = translateTransition.yTransition;
    g_numberValues[Z_INDEX].f32 = translateTransition.zTransition;
    g_numberValues[animationDurationIndex].i32 = translateTransition.animation.duration;
    g_numberValues[animationCurveIndex].i32 = translateTransition.animation.curve;
    g_numberValues[animationDelayIndex].i32 = translateTransition.animation.delay;
    g_numberValues[animationIterationsIndex].i32 = translateTransition.animation.iteration;
    g_numberValues[animationPlayModeIndex].i32 = UnConvertAnimationDirection(translateTransition.animation.playMode);
    g_numberValues[animationTempoIndex].f32 = translateTransition.animation.tempo;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetMoveTransition(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto moveTransition =
        fullImpl->getNodeModifiers()->getCommonModifier()->getMoveTransition(node->uiNodeHandle);
    const int32_t animationDurationIndex = MOVE_ANIMATION_BASE + ANIMATION_DURATION_INDEX;
    const int32_t animationCurveIndex = MOVE_ANIMATION_BASE + ANIMATION_CURVE_INDEX;
    const int32_t animationDelayIndex = MOVE_ANIMATION_BASE + ANIMATION_DELAY_INDEX;
    const int32_t animationIterationsIndex = MOVE_ANIMATION_BASE + ANIMATION_INTERATION_INDEX;
    const int32_t animationPlayModeIndex = MOVE_ANIMATION_BASE + ANIMATION_PLAY_MODE_INDEX;
    const int32_t animationTempoIndex = MOVE_ANIMATION_BASE + ANIMATION_TEMPO_INDEX;
    g_numberValues[0].i32 = moveTransition.edgeType;
    g_numberValues[animationDurationIndex].i32 = moveTransition.animation.duration;
    g_numberValues[animationCurveIndex].i32 = moveTransition.animation.curve;
    g_numberValues[animationDelayIndex].i32 = moveTransition.animation.delay;
    g_numberValues[animationIterationsIndex].i32 = moveTransition.animation.iteration;
    g_numberValues[animationPlayModeIndex].i32 = moveTransition.animation.playMode;
    g_numberValues[animationTempoIndex].f32 = moveTransition.animation.tempo;
    g_attributeItem.size = REQUIRED_SEVEN_PARAM;
    return &g_attributeItem;
}


const ArkUI_AttributeItem* GetOffset(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto offset = fullImpl->getNodeModifiers()->getCommonModifier()->getOffset(node->uiNodeHandle);
    g_numberValues[NUM_0].f32 = offset.xComponent;
    g_numberValues[NUM_1].f32 = offset.yComponent;
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetMarkAnchor(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto markAnchor = fullImpl->getNodeModifiers()->getCommonModifier()->getMarkAnchor(node->uiNodeHandle);
    g_numberValues[NUM_0].f32 = markAnchor.xCoordinate;
    g_numberValues[NUM_1].f32 = markAnchor.yCoordinate;
    g_attributeItem.size = REQUIRED_TWO_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetAlignRules(ArkUI_NodeHandle node)
{
    g_attributeItem.object = node->alignRuleOption;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto textContent = fullImpl->getNodeModifiers()->getTextModifier()->getTextContent(node->uiNodeHandle);
    g_attributeItem.string = (textContent != nullptr ? textContent : EMPTY_STR.c_str());
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetFontColor(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getTextModifier()->
                getFontColor(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_SPAN:
            g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getSpanModifier()->
                getSpanFontColor(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
                getTextInputFontColor(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_BUTTON:
            g_numberValues[0].u32 = fullImpl->getNodeModifiers()->getButtonModifier()->
                getButtonFontColor(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetFontSize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto unit = GetDefaultUnit(node, UNIT_FP);
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getTextModifier()->
                getFontSize(node->uiNodeHandle, unit);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_SPAN:
            g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getSpanModifier()->
                getSpanFontSize(node->uiNodeHandle, unit);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
                getTextInputFontSize(node->uiNodeHandle, unit);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_BUTTON:
            g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getButtonModifier()->
                getButtonFontSize(node->uiNodeHandle, unit);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetFontStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->
                getItalicFontStyle(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_SPAN:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getSpanModifier()->
                getSpanFontStyle(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
                getTextInputFontStyle(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetFontWeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getFontWeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_SPAN:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getSpanModifier()->
                getSpanFontWeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextInputModifier()->
                getTextInputFontWeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_BUTTON:
            g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getButtonModifier()->
                getButtonFontWeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetLineHeight(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextModifier()->getTextLineHeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_SPAN:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getSpanModifier()->getSpanLineHeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputLineHeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaLineHeight(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetDecoration(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN: {
            ArkUITextDecorationType spanDecorationType = { 0, Color::BLACK.GetValue()};
            fullImpl->getNodeModifiers()->getSpanModifier()->getSpanDecoration(node->uiNodeHandle, &spanDecorationType);
            g_numberValues[0].i32 = spanDecorationType.decorationType;
            g_numberValues[DECORATION_COLOR_INDEX].u32 = spanDecorationType.color;
            g_numberValues[DECORATION_STYLE_INDEX].i32 = spanDecorationType.style;
            g_attributeItem.size = NUM_3;
            break;
        }
        case ARKUI_NODE_TEXT: {
            ArkUITextDecorationType textDecorationType = { 0, Color::BLACK.GetValue()};
            fullImpl->getNodeModifiers()->getTextModifier()->getTextDecoration(node->uiNodeHandle, &textDecorationType);
            g_numberValues[0].i32 = textDecorationType.decorationType;
            g_numberValues[DECORATION_COLOR_INDEX].u32 = textDecorationType.color;
            g_numberValues[DECORATION_STYLE_INDEX].i32 = textDecorationType.style;
            g_attributeItem.size = NUM_3;
            break;
        }
        default:
            break;
    }

    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextCase(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            g_numberValues[NUM_0].i32 =
                fullImpl->getNodeModifiers()->getSpanModifier()->getSpanTextCase(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT:
            g_numberValues[NUM_0].i32 =
                fullImpl->getNodeModifiers()->getTextModifier()->getTextTextCase(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetLetterSpacing(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_SPAN:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getSpanModifier()->getSpanLetterSpacing(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextModifier()->getTextLetterSpacing(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputLetterSpacing(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[NUM_0].f32 =
                fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaLetterSpacing(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetMaxLines(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    switch (node->type) {
        case ARKUI_NODE_TEXT:
            g_numberValues[NUM_0].i32 =
                fullImpl->getNodeModifiers()->getTextModifier()->getTextMaxLines(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_INPUT:
            g_numberValues[NUM_0].i32 =
                fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputMaxLines(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        case ARKUI_NODE_TEXT_AREA:
            g_numberValues[NUM_0].i32 =
                fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaMaxLines(node->uiNodeHandle);
            g_attributeItem.size = REQUIRED_ONE_PARAM;
            break;
        default:
            break;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    int32_t textAlign = NUM_0;
    if (node->type == ARKUI_NODE_TEXT) {
        textAlign = fullImpl->getNodeModifiers()->getTextModifier()->getTextAlign(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
        textAlign = fullImpl->getNodeModifiers()->getTextInputModifier()->getTextInputTextAlign(node->uiNodeHandle);
    } else if (node->type == ARKUI_NODE_TEXT_AREA) {
        textAlign = fullImpl->getNodeModifiers()->getTextAreaModifier()->getTextAreaTextAlign(node->uiNodeHandle);
    }
    g_numberValues[0].i32 = textAlign;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextOverflow(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].i32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextTextOverflow(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetTextIndent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    g_numberValues[0].f32 = fullImpl->getNodeModifiers()->getTextModifier()->getTextTextIndent(node->uiNodeHandle);
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetSpanContent(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto content = fullImpl->getNodeModifiers()->getSpanModifier()->getSpanContent(node->uiNodeHandle);
    g_attributeItem.string = (content != nullptr ? content : EMPTY_STR.c_str());
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetSpanTextBackgroundStyle(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    ArkUITextBackgroundStyleOptions options;
    fullImpl->getNodeModifiers()->getSpanModifier()->getSpanTextBackgroundStyle(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].u32 = options.color;
    g_numberValues[NUM_1].f32 = options.topLeft;
    g_numberValues[NUM_2].f32 = options.topRight;
    g_numberValues[NUM_3].f32 = options.bottomLeft;
    g_numberValues[NUM_4].f32 = options.bottomRight;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetImageSpanSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto src = fullImpl->getNodeModifiers()->getImageModifier()->getImageSrc(node->uiNodeHandle);
    g_attributeItem.string = (src != nullptr ? src : EMPTY_STR.c_str());
    if (node->drawableDescriptor) {
        g_attributeItem.object = node->drawableDescriptor;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetVerticalAlign(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto verticalAlign =
        fullImpl->getNodeModifiers()->getImageSpanModifier()->getImageSpanVerticalAlign(node->uiNodeHandle);
    auto it = std::find(IMAGE_SPAN_ALIGNMENT_ARRAY.begin(), IMAGE_SPAN_ALIGNMENT_ARRAY.end(), verticalAlign);
    if (it != IMAGE_SPAN_ALIGNMENT_ARRAY.end()) {
        g_numberValues[0].i32 = std::distance(IMAGE_SPAN_ALIGNMENT_ARRAY.begin(), it);
        g_attributeItem.size = REQUIRED_ONE_PARAM;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetImageSrc(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto src = fullImpl->getNodeModifiers()->getImageModifier()->getImageSrc(node->uiNodeHandle);
    g_attributeItem.string = (src != nullptr ? src : EMPTY_STR.c_str());
    if (node->drawableDescriptor) {
        g_attributeItem.object = node->drawableDescriptor;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetObjectFit(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto resultValue = fullImpl->getNodeModifiers()->getImageModifier()->getObjectFit(node->uiNodeHandle);
    auto it = std::find(OBJECT_FIT_ARRAY.begin(), OBJECT_FIT_ARRAY.end(), resultValue);
    if (it != OBJECT_FIT_ARRAY.end()) {
        g_numberValues[0].i32 = std::distance(OBJECT_FIT_ARRAY.begin(), it);
    } else {
        g_numberValues[0].i32 = static_cast<int32_t>(ARKUI_OBJECT_FIT_COVER);
    }
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetInterpolation(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto interpolation = fullImpl->getNodeModifiers()->getImageModifier()->getImageInterpolation(node->uiNodeHandle);
    g_numberValues[0].i32 = interpolation;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetObjectRepeat(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto objectRepeat = fullImpl->getNodeModifiers()->getImageModifier()->getObjectRepeat(node->uiNodeHandle);
    g_numberValues[0].i32 = objectRepeat;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetColorFilter(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto colorFilter = fullImpl->getNodeModifiers()->getImageModifier()->getDrawingColorFilter(node->uiNodeHandle);
    if (colorFilter) {
        g_attributeItem.object = colorFilter;
        g_attributeItem.size = 0;
        return &g_attributeItem;
    }
    g_attributeItem.size = REQUIRED_TWENTY_PARAM;
    for (size_t i = 0; i < REQUIRED_TWENTY_PARAM; i++) {
        g_numberValues[i].f32 = 0;
    }
    ArkUIFilterColorType colorFilterType = { .filterArray = &g_numberValues[0].f32,
        .filterSize = REQUIRED_TWENTY_PARAM };
    fullImpl->getNodeModifiers()->getImageModifier()->getColorFilter(node->uiNodeHandle, &colorFilterType);
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetAutoResize(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto autoResize = fullImpl->getNodeModifiers()->getImageModifier()->getAutoResize(node->uiNodeHandle);
    g_numberValues[0].i32 = autoResize;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetAlt(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto src = fullImpl->getNodeModifiers()->getImageModifier()->getAlt(node->uiNodeHandle);
    g_attributeItem.string = (src != nullptr ? src : EMPTY_STR.c_str());
    if (node->altDrawableDescriptor) {
        g_attributeItem.object = node->altDrawableDescriptor;
    }
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetImageDraggable(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto draggable = fullImpl->getNodeModifiers()->getImageModifier()->getImageDraggable(node->uiNodeHandle);
    g_numberValues[0].i32 = draggable;
    g_attributeItem.size = REQUIRED_ONE_PARAM;
    return &g_attributeItem;
}

int32_t SetCheckboxSelect(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setSelect(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxSelect(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getSelect(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxSelect(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetSelect(node->uiNodeHandle);
}

int32_t SetCheckboxSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setSelectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxUnSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setUnSelectedColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxUnSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getUnSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxUnSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetUnSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxMark(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // defalut white
    int strokeColor = item->value[0].u32;
    double size = -1;
    if (item->size > 1) {
        //check 2 for size
        if (LessNotEqual(item->value[1].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        //set 2 for size
        size = item->value[1].f32;
    }
    // defalut 2
    double strokeWidth = 2;
    if (item->size > ALLOW_SIZE_2) {
        //check 2 for strokeWidth
        if (LessNotEqual(item->value[2].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        }
        //set 2 for strokeWidth
        strokeWidth = item->value[2].f32;
    }
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setMark(
        node->uiNodeHandle, strokeColor, size, unit, strokeWidth, unit);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxMark(ArkUI_NodeHandle node)
{
    auto strokeColor = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkColor(node->uiNodeHandle);
    auto size = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkSize(node->uiNodeHandle);
    auto strokeWidth = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckMarkWidth(node->uiNodeHandle);
    int index = 0;
    g_numberValues[index++].u32 = strokeColor;
    g_numberValues[index++].f32 = size;
    g_numberValues[index++].f32 = strokeWidth;
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetCheckboxMark(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetMark(node->uiNodeHandle);
}

int32_t SetCheckboxShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsCheckboxShape(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxShape(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxShape(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckboxShape(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxShape(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->resetCheckboxShape(node->uiNodeHandle);
}

int32_t SetCheckboxName(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxName(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxName(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckboxName(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxName(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxName(
        node->uiNodeHandle, "");
}

int32_t SetCheckboxGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxGroup(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroup(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->getCheckboxName(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroup(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxModifier()->setCheckboxGroup(
        node->uiNodeHandle, "");
}

int32_t SetCheckboxGroupName(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupName(
        node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupName(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupName(
        node->uiNodeHandle);
    g_attributeItem.string = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroupName(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupName(
        node->uiNodeHandle, "");
}

int32_t SetCheckboxGroupSelectAll(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSelectAll(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupSelectAll(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupSelectAll(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroupSelectAll(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectAll(node->uiNodeHandle);
}

int32_t SetCheckboxGroupSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSelectedColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroupSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxGroupUnSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupUnSelectedColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupUnSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupUnSelectedColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroupUnSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupUnSelectedColor(node->uiNodeHandle);
}

int32_t SetCheckboxGroupMark(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int strokeColor = item->value[0].u32;
    double size = -1;
    if (item->size > 1) {
        if (GreatOrEqual(item->value[1].f32, 0.0f)) {
            size = item->value[1].f32;
        }  
    }
    double strokeWidth = 2;
    if (item->size > ALLOW_SIZE_2) {
        if (GreatOrEqual(item->value[2].f32, 0.0f)) {
            strokeWidth = item->value[2].f32;
        }     
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupMark(
        node->uiNodeHandle, strokeColor, size, strokeWidth);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupMark(ArkUI_NodeHandle node)
{
    auto strokeColor = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupMarkColor(node->uiNodeHandle);
    auto size = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupMarkSize(node->uiNodeHandle);
    auto strokeWidth = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupMarkWidth(node->uiNodeHandle);
    int index = 0;
    g_numberValues[index++].u32 = strokeColor;
    g_numberValues[index++].f32 = size;
    g_numberValues[index++].f32 = strokeWidth;
    g_attributeItem.size = index;
    return &g_attributeItem;
}

void ResetCheckboxGroupMark(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupMark(node->uiNodeHandle);
}

int32_t SetCheckboxGroupShape(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size == 0 || !CheckAttributeIsCheckboxShape(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupStyle(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetCheckboxGroupShape(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->getCheckboxGroupStyle(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetCheckboxGroupShape(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupStyle(node->uiNodeHandle);
}

int32_t SetSliderBlockColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setBlockColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderBlockColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderBlockColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetBlockColor(node->uiNodeHandle);
}

int32_t SetSliderTrackColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setTrackBackgroundColor(
        node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderTrackColor(ArkUI_NodeHandle node)
{
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getSliderModifier()->getTrackBackgroundColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderTrackColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(node->uiNodeHandle);
}

int32_t SetSliderSelectedColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSelectColor(node->uiNodeHandle, item->value[0].u32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderSelectedColor(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSelectColor(node->uiNodeHandle);
    g_numberValues[0].u32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderSelectedColor(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSelectColor(node->uiNodeHandle);
}

int32_t SetSliderShowSteps(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setShowSteps(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderShowSteps(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getShowSteps(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderShowSteps(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetShowSteps(node->uiNodeHandle);
}

int32_t SetSliderBlockStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderBlockStyle(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int style = item->value[0].i32;

    if (style == NUM_1) {
        if (item->string == nullptr) {
            return ERROR_CODE_PARAM_INVALID;
        }
        // image
        std::string src(item->string);
        std::string bundle;
        std::string module;
        GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderBlockImage(
            node->uiNodeHandle, src.c_str(), bundle.c_str(), module.c_str());
    } else if (style == NUM_2) {
        auto* fullImpl = GetFullImpl();
        if (item->value[1].i32 == ArkUI_ClipType::ARKUI_CLIP_TYPE_PATH) {
            ArkUI_Float32 pathAttributes[NUM_2];
            if (LessNotEqual(item->value[NUM_2].f32, 0.0f) || LessNotEqual(item->value[NUM_3].f32, 0.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            } else {
                pathAttributes[NUM_0] = item->value[NUM_2].f32;
                pathAttributes[NUM_1] = item->value[NUM_3].f32;
            }

            fullImpl->getNodeModifiers()->getSliderModifier()->setSliderBlockPath(
                node->uiNodeHandle, "path", &pathAttributes, item->string);
        } else {
            ArkUI_Float32 attributes[item->size - NUM_2];
            for (int i = NUM_2; i < item->size; i++) {
                if (LessNotEqual(item->value[i].f32, 0.0f)) {
                    return ERROR_CODE_PARAM_INVALID;
                } else {
                    attributes[i - NUM_2] = item->value[i].f32;
                }
            }
            fullImpl->getNodeModifiers()->getSliderModifier()->setSliderBlockShape(
                node->uiNodeHandle, ShapeToString(item->value[1].i32).c_str(), attributes, item->size - NUM_2);
        }
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderBlockType(node->uiNodeHandle, style);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderBlockStyle(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockType(node->uiNodeHandle);
    //index 0 style
    g_numberValues[0].i32 = resultValue;
    switch (resultValue) {
        case NUM_1: {
            auto imageValue =
                GetFullImpl()->getNodeModifiers()->getSliderModifier()->getBlockImageValue(node->uiNodeHandle);
            g_attributeItem.string = imageValue;
            break;
        }
        case NUM_2: {
            ArkUI_Float32 values[NUM_5];
            auto pathCommands = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderBlockShape(
                node->uiNodeHandle, &values);
            //index 1 shapeType
            g_numberValues[1].i32 = values[0];
            //index 2 width
            g_numberValues[2].f32 = values[1];
            //index 3 height
            g_numberValues[3].f32 = values[2];
            g_attributeItem.size = NUM_3;
            ArkUI_ShapeType shapeType = static_cast<ArkUI_ShapeType>(values[0]);
            if (shapeType == ArkUI_ShapeType::ARKUI_SHAPE_TYPE_RECTANGLE) {
                //index 4 width
                g_numberValues[4].f32 = values[3];
                //index 5 height
                g_numberValues[5].f32 = values[4];
                g_attributeItem.size = NUM_6;
            } else if (shapeType == ArkUI_ShapeType::ARKUI_SHAPE_TYPE_PATH) {
                g_attributeItem.string = pathCommands;
            }
            break;
        }
        default:
            break;
    }

    return &g_attributeItem;
}

void ResetSliderBlockStyle(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockImage(node->uiNodeHandle);
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockShape(node->uiNodeHandle);
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderBlockType(node->uiNodeHandle);
}

int32_t SetSliderValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderValue(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderValue(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderValue(node->uiNodeHandle);
}

int32_t SetSliderMinValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setMinLabel(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderMinValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getMinLabel(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderMinValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetMinLabel(node->uiNodeHandle);
}

int32_t SetSliderMaxValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setMaxLabel(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderMaxValue(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getMaxLabel(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderMaxValue(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetMaxLabel(node->uiNodeHandle);
}

int32_t SetSliderStep(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || LessNotEqual(item->value[0].f32, SLIDER_STEP_MIN_F)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setStep(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderStep(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getStep(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderStep(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetStep(node->uiNodeHandle);
}

int32_t SetSliderDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderDirection(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setDirection(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderDirection(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getDirection(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderDirection(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetDirection(node->uiNodeHandle);
}

int32_t SetSliderReverse(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setReverse(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderReverse(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getReverse(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderReverse(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetReverse(node->uiNodeHandle);
}

int32_t SetSliderStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsSliderStyle(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->setSliderStyle(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderStyle(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getSliderModifier()->getSliderStyle(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

void ResetSliderStyle(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getSliderModifier()->resetSliderStyle(node->uiNodeHandle);
}

int32_t SetSliderTrackThickness(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (LessNotEqual(actualSize, 0) || LessOrEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSliderModifier()->setThickness(
        node->uiNodeHandle, item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP));
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderTrackThickness(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSliderModifier();
    g_numberValues[0].f32 = modifier->getThickness(node->uiNodeHandle, GetDefaultUnit(node, UNIT_VP));
    if (LessOrEqual(g_numberValues[0].f32, 0.0f)) {
        return nullptr;
    }
    return &g_attributeItem;
}

void ResetSliderTrackThickness(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSliderModifier()->resetThickness(node->uiNodeHandle);
}

int32_t SetSliderValidSlideRange(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item || std::isnan(item->value[NUM_0].f32) || std::isnan(item->value[NUM_1].f32)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSliderModifier()->setSliderValidSlideRange(
        node->uiNodeHandle, item->value[NUM_0].f32, item->value[NUM_1].f32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetSliderValidSlideRange(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getSliderModifier();
    ArkUISliderValidSlideRange validRange = modifier->getSliderValidSlideRange(node->uiNodeHandle);
    if (std::isnan(validRange.from) || std::isnan(validRange.to)) {
        return nullptr;
    }
    g_numberValues[NUM_0].f32 = validRange.from;
    g_numberValues[NUM_1].f32 = validRange.to;
    return &g_attributeItem;
}

void ResetSliderValidSlideRange(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getSliderModifier()->resetSliderValidSlideRange(node->uiNodeHandle);
}

int32_t SetRefreshRefreshing(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getRefreshModifier()->setRefreshing(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetRefreshRefreshing(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getRefreshModifier()->getRefreshing(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetRefreshContent(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto contentNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getRefreshModifier()->setRefreshContent(
        node->uiNodeHandle, contentNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

void ResetRefreshContent(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getRefreshModifier()->setRefreshContent(node->uiNodeHandle, nullptr);
}

int32_t SetRefreshPullDownRatio(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].f32, 0.0f) || GreatNotEqual(item->value[0].f32, 1.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRefreshModifier()->setPullDownRatio(node->uiNodeHandle, item->value[0].f32);
    return ERROR_CODE_NO_ERROR;
}

void ResetRefreshPullDownRatio(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRefreshModifier()->resetPullDownRatio(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRefreshPullDownRatio(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getRefreshModifier()->getPullDownRatio(node->uiNodeHandle);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

int32_t SetRefreshOffset(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessOrEqual(item->value[0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    fullImpl->getNodeModifiers()->getRefreshModifier()->setRefreshOffset(node->uiNodeHandle, item->value[0].f32, unit);
    return ERROR_CODE_NO_ERROR;
}

void ResetRefreshOffset(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRefreshModifier()->resetRefreshOffset(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRefreshOffset(ArkUI_NodeHandle node)
{
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    auto resultValue =
        GetFullImpl()->getNodeModifiers()->getRefreshModifier()->getRefreshOffset(node->uiNodeHandle, unit);
    g_numberValues[0].f32 = resultValue;
    return &g_attributeItem;
}

int32_t SetPullToRefresh(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getRefreshModifier()->setPullToRefresh(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetPullToRefresh(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRefreshModifier()->resetPullToRefresh(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetPullToRefresh(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getRefreshModifier()->getPullToRefresh(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}
// waterFlow attribute
int32_t SetLayoutDirection(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(NUM_0, NUM_3, item->value[NUM_0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setLayoutDirection(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetLayoutDirection(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetLayoutDirection(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetLayoutDirection(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getWaterFlowModifier();
    g_numberValues[0].i32 = modifier->getLayoutDirection(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetColumnsTemplate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setColumnsTemplate(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetColumnsTemplate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetColumnsTemplate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetColumnsTemplate(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto columnsTemplate = fullImpl->getNodeModifiers()->getWaterFlowModifier()->getColumnsTemplate(node->uiNodeHandle);
    g_attributeItem.string = columnsTemplate;
    return &g_attributeItem;
}

int32_t SetRowsTemplate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setRowsTemplate(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetRowsTemplate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setRowsTemplate(node->uiNodeHandle, "1fr");
}

const ArkUI_AttributeItem* GetRowsTemplate(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto rowsTemplate = fullImpl->getNodeModifiers()->getWaterFlowModifier()->getRowsTemplate(node->uiNodeHandle);
    g_attributeItem.string = rowsTemplate;
    return &g_attributeItem;
}

int32_t SetWaterFlowColumnsGap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setColumnsGap(
        node->uiNodeHandle, item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowColumnsGap(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetColumnsGap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowColumnsGap(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getWaterFlowModifier();
    g_numberValues[0].f32 = modifier->getColumnsGap(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetWaterFlowRowsGap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setRowsGap(
        node->uiNodeHandle, item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowRowsGap(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetRowsGap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowRowsGap(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getWaterFlowModifier();
    g_numberValues[0].f32 = modifier->getRowsGap(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetWaterFlowNodeAdapter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* nodeAdapter = reinterpret_cast<ArkUINodeAdapterHandle>(item->object);
    return GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->setNodeAdapter(node->uiNodeHandle, nodeAdapter);
}

void ResetWaterFlowNodeAdapter(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetNodeAdapter(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowNodeAdapter(ArkUI_NodeHandle node)
{
    ArkUINodeAdapterHandle adapter =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getNodeAdapter(node->uiNodeHandle);
    g_attributeItem.object = reinterpret_cast<void*>(adapter);
    return &g_attributeItem;
}

int32_t SetWaterFlowCachedCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->resetCachedCount(node->uiNodeHandle);
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->setCachedCount(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowCachedCount(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetCachedCount(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowCachedCount(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getCachedCount(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

int32_t SetWaterFlowFooter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!item->object) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto fullImpl = GetFullImpl();
    auto footerNodeHandle = reinterpret_cast<ArkUI_NodeHandle>(item->object);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setWaterflowFooter(
        node->uiNodeHandle, footerNodeHandle->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowFooter(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetWaterflowFooter(node->uiNodeHandle);
}

int32_t SetWaterFlowSectionOption(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* waterFlowSectionOption = reinterpret_cast<ArkUIWaterFlowSectionOption>(item->object);
    GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->setSectionOption(
        node->uiNodeHandle, item->value[0].i32, waterFlowSectionOption);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowSectionOption(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetSectionOption(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowSectionOption(ArkUI_NodeHandle node)
{
    static ArkUI_WaterFlowSectionOption options =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getSectionOption(node->uiNodeHandle);
    g_attributeItem.object = &options;
    return &g_attributeItem;
}

int32_t SetItemConstraintSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size != ALLOW_SIZE_4) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    ArkUI_Float32 constraintSize[ALLOW_SIZE_4] = { 0.0f, FLT_MAX, 0.0f, FLT_MAX };
    int32_t unit = GetDefaultUnit(node, UNIT_VP);
    ArkUI_Int32 units[ALLOW_SIZE_4] = { unit, unit, unit, unit };

    for (int i = 0; i < ALLOW_SIZE_4; ++i) {
        if (LessNotEqual(item->value[i].f32, 0.0f)) {
            return ERROR_CODE_PARAM_INVALID;
        } else {
            constraintSize[i] = item->value[i].f32;
        }
    }
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setItemMinWidth(
        node->uiNodeHandle, constraintSize[NUM_0], units[NUM_0], nullptr);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setItemMaxWidth(
        node->uiNodeHandle, constraintSize[NUM_1], units[NUM_1], nullptr);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setItemMinHeight(
        node->uiNodeHandle, constraintSize[NUM_2], units[NUM_2], nullptr);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setItemMaxHeight(
        node->uiNodeHandle, constraintSize[NUM_3], units[NUM_3], nullptr);
    return ERROR_CODE_NO_ERROR;
}

void ResetItemConstraintSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetItemMinWidth(node->uiNodeHandle);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetItemMaxWidth(node->uiNodeHandle);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetItemMinHeight(node->uiNodeHandle);
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->resetItemMaxHeight(node->uiNodeHandle);
}

int32_t SetWaterFlowLayoutMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->setWaterFlowLayoutMode(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetWaterFlowLayoutMode(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->resetWaterFlowLayoutMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetWaterFlowLayoutMode(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getWaterFlowLayoutMode(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetItemConstraintSize(ArkUI_NodeHandle node)
{
    ArkUI_Int32 unit = GetDefaultUnit(node, UNIT_VP);
    g_numberValues[NUM_0].f32 =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getItemMinWidth(node->uiNodeHandle, unit);
    g_numberValues[NUM_1].f32 =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getItemMaxWidth(node->uiNodeHandle, unit);
    g_numberValues[NUM_2].f32 =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getItemMinHeight(node->uiNodeHandle, unit);
    g_numberValues[NUM_3].f32 =
        GetFullImpl()->getNodeModifiers()->getWaterFlowModifier()->getItemMaxHeight(node->uiNodeHandle, unit);
    return &g_attributeItem;
}

int32_t SetRelativeContainerGuideLine(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    node->guidelineOption = item->object;
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto styles = reinterpret_cast<ArkUI_GuidelineOption*>(item->object);
    ArkUI_Int32 size = static_cast<ArkUI_Int32>(styles->styles.size());
    std::vector<ArkUIGuidelineStyle> guidelineStyle;
    for (int i = 0; i < size; ++i) {
        ArkUIGuidelineStyle style;
        style.id = styles->styles[i].id.c_str();
        style.direction = styles->styles[i].direction;
        style.hasStart = styles->styles[i].hasStart;
        style.start = styles->styles[i].start;
        style.end = styles->styles[i].end;
        style.hasEnd = styles->styles[i].hasEnd;
        guidelineStyle.push_back(style);
    }
    GetFullImpl()->getNodeModifiers()->getRelativeContainerModifier()->setGuideLine(
        node->uiNodeHandle, guidelineStyle.data(), size);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetRelativeContainerBarrier(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    node->barrierOption = item->object;
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);

    auto styles = reinterpret_cast<ArkUI_BarrierOption*>(item->object);
    ArkUI_Int32 size = static_cast<ArkUI_Int32>(styles->styles.size());

    std::vector<ArkUIBarrierStyle> barrierStyle(size);
    for (int i = 0; i < size; ++i) {
        barrierStyle[i].id = styles->styles[i].id.c_str();
        barrierStyle[i].direction = styles->styles[i].direction;
        barrierStyle[i].referencedIdSize = static_cast<ArkUI_Int32>(styles->styles[i].referencedId.size());
        barrierStyle[i].referencedId = new ArkUI_CharPtr[barrierStyle[i].referencedIdSize];
        for (int j = 0; j < barrierStyle[i].referencedIdSize; ++j) {
            barrierStyle[i].referencedId[j] = styles->styles[i].referencedId[j].c_str();
        }
    }

    GetFullImpl()->getNodeModifiers()->getRelativeContainerModifier()->setBarrier(
        node->uiNodeHandle, barrierStyle.data(), size);

    for (int i = 0; i < size; ++i) {
        delete[] barrierStyle[i].referencedId;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetRelativeContainerGuideLine(ArkUI_NodeHandle node)
{
    g_attributeItem.object = node->guidelineOption;
    return &g_attributeItem;
}

const ArkUI_AttributeItem* GetRelativeContainerBarrier(ArkUI_NodeHandle node)
{
    g_attributeItem.object = node->barrierOption;
    return &g_attributeItem;
}

void ResetRelativeContainerGuideLine(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRelativeContainerModifier()->resetGuideline(node->uiNodeHandle);
    node->guidelineOption = nullptr;
}

void ResetRelativeContainerBarrier(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRelativeContainerModifier()->resetBarrier(node->uiNodeHandle);
    node->barrierOption = nullptr;
}

int32_t SetWaterFlowScrollToIndex(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < NUM_0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 values[ALLOW_SIZE_3] = { NUM_0, DEFAULT_FALSE, ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_NONE };
    values[NUM_0] = item->value[NUM_0].i32;
    if (item->size > NUM_1 && InRegion(NUM_0, NUM_1, item->value[NUM_1].i32)) {
        values[NUM_1] = item->value[NUM_1].i32;
    }
    if (item->size > NUM_2 && InRegion(NUM_0, NUM_3, item->value[NUM_2].i32)) {
        values[NUM_2] = item->value[NUM_2].i32;
    }
    if (values[NUM_2] == ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_NONE) {
        values[NUM_2] = ArkUI_ScrollAlignment::ARKUI_SCROLL_ALIGNMENT_START;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getWaterFlowModifier()->setScrollToIndex(
        node->uiNodeHandle, values[NUM_0], values[NUM_1], values[NUM_2]);
    return ERROR_CODE_NO_ERROR;
}
// radio attribute
int32_t SetRadioChecked(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRadioModifier()->setRadioChecked(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadioChecked(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRadioModifier()->resetRadioChecked(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadioChecked(ArkUI_NodeHandle node)
{
    auto resultValue = GetFullImpl()->getNodeModifiers()->getRadioModifier()->getRadioChecked(node->uiNodeHandle);
    g_numberValues[0].i32 = resultValue;
    return &g_attributeItem;
}

int32_t SetRadioStyle(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    ArkUI_Uint32 radioStyle[ALLOW_SIZE_3] = { 0xFF007DFF, 0xFF182431, 0xFFFFFFF };
    // checkedBackgroundColor
    if (item->size > NUM_0) {
        radioStyle[NUM_0] = item->value[NUM_0].u32;
    }

    // uncheckedBorderColor
    if (item->size > NUM_1) {
        radioStyle[NUM_1] = item->value[NUM_1].u32;
    }

    // indicatorColor
    if (item->size > NUM_2) {
        radioStyle[NUM_2] = item->value[NUM_2].u32;
    }
    fullImpl->getNodeModifiers()->getRadioModifier()->setRadioStyle(
        node->uiNodeHandle, radioStyle[NUM_0], radioStyle[NUM_1], radioStyle[NUM_2]);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadioStyle(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRadioModifier()->resetRadioStyle(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadioStyle(ArkUI_NodeHandle node)
{
    ArkUIRadioStyleOption options;
    GetFullImpl()->getNodeModifiers()->getRadioModifier()->getRadioStyle(node->uiNodeHandle, &options);
    g_numberValues[NUM_0].u32 = options.checkedBackgroundColor;
    g_numberValues[NUM_1].u32 = options.uncheckedBorderColor;
    g_numberValues[NUM_2].u32 = options.indicatorColor;
    return &g_attributeItem;
}

int32_t SetRadioValue(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getRadioModifier()->setRadioValue(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadioValue(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRadioModifier()->resetRadioValue(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadioValue(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto value = fullImpl->getNodeModifiers()->getRadioModifier()->getRadioValue(node->uiNodeHandle);
    g_attributeItem.string = (value != nullptr ? value : EMPTY_STR.c_str());
    return &g_attributeItem;
}

int32_t SetRadioGroup(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getRadioModifier()->setRadioGroup(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetRadioGroup(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getRadioModifier()->resetRadioGroup(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetRadioGroup(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto value = fullImpl->getNodeModifiers()->getRadioModifier()->getRadioGroup(node->uiNodeHandle);
    g_attributeItem.string = (value != nullptr ? value : EMPTY_STR.c_str());
    return &g_attributeItem;
}

// imageAnimator attribute
int32_t SetImageAnimatorSrc(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (!CheckAttributeObjectAndSize(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIImageFrameInfo imageInfos[item->size];
    if (!ParseImages(item, imageInfos, node)) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setImageAnimatorSrc(
        node->uiNodeHandle, imageInfos, item->size);
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorSrc(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetImages(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorSrc(ArkUI_NodeHandle node)
{
    if (!node->imageFrameInfos) {
        g_attributeItem.size = 0;
    } else {
        auto* fullImpl = GetFullImpl();
        g_attributeItem.size = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getImagesSize(
            node->uiNodeHandle);
        g_attributeItem.object = reinterpret_cast<ArkUI_ImageAnimatorFrameInfo**>(node->imageFrameInfos);
    }
    return &g_attributeItem;
}

int32_t SetImageAnimatorState(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setState(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorState(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetState(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorState(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getState(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

int32_t SetImageAnimatorDuration(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setDuration(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorDuration(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetDuration(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorDuration(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getDuration(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

int32_t SetImageAnimatorReverse(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < DEFAULT_FALSE || item->value[0].i32 > DEFAULT_TRUE) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setReverse(
        node->uiNodeHandle, static_cast<ArkUI_Uint32>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorReverse(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetReverse(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorReverse(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getIsReverse(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

int32_t SetImageAnimatorFixedSize(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < DEFAULT_FALSE || item->value[0].i32 > DEFAULT_TRUE) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setFixedSize(
        node->uiNodeHandle, static_cast<ArkUI_Uint32>(item->value[0].i32));
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorFixedSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetFixedSize(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorFixedSize(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getFixedSize(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

int32_t SetImageAnimatorFillMode(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (item->value[0].i32 < NUM_0 || item->value[0].i32 > NUM_3) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setFillMode(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorFillMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetFillMode(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorFillMode(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getFillMode(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

int32_t SetImageAnimatorIterations(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    if (item->size == 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->setImageAnimatorIteration(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetImageAnimatorIterations(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorIteration(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetImageAnimatorIterations(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    int32_t value = fullImpl->getNodeModifiers()->getImageAnimatorModifier()->getIteration(node->uiNodeHandle);
    g_numberValues[NUM_0].i32 = value;
    g_attributeItem.size = RETURN_SIZE_ONE;
    return &g_attributeItem;
}

// grid attribute
int32_t SetGridColumnsTemplate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getGridModifier()->setGridColumnsTemplate(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetGridColumnsTemplate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getGridModifier()->resetGridColumnsTemplate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridColumnsTemplate(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto columnsTemplate = fullImpl->getNodeModifiers()->getGridModifier()->getGridColumnsTemplate(node->uiNodeHandle);
    g_attributeItem.string = columnsTemplate;
    return &g_attributeItem;
}

int32_t SetGridRowsTemplate(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (!CheckAttributeString(item)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getGridModifier()->setGridRowsTemplate(node->uiNodeHandle, item->string);
    return ERROR_CODE_NO_ERROR;
}

void ResetGridRowsTemplate(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getGridModifier()->resetGridRowsTemplate(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridRowsTemplate(ArkUI_NodeHandle node)
{
    auto fullImpl = GetFullImpl();
    auto rowsTemplate = fullImpl->getNodeModifiers()->getGridModifier()->getGridRowsTemplate(node->uiNodeHandle);
    g_attributeItem.string = rowsTemplate;
    return &g_attributeItem;
}

int32_t SetGridColumnsGap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUIResourceLength columnGap = { item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr };
    fullImpl->getNodeModifiers()->getGridModifier()->setGridColumnsGap(node->uiNodeHandle, &columnGap);
    return ERROR_CODE_NO_ERROR;
}

void ResetGridColumnsGap(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getGridModifier()->resetGridColumnsGap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridColumnsGap(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getGridModifier();
    g_numberValues[0].f32 = modifier->getGridColumnsGap(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetGridRowsGap(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
    if (actualSize < 0 || LessNotEqual(item->value[NUM_0].f32, 0.0f)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = GetFullImpl();
    ArkUIResourceLength rowGap = { item->value[NUM_0].f32, GetDefaultUnit(node, UNIT_VP), nullptr };
    fullImpl->getNodeModifiers()->getGridModifier()->setGridRowsGap(node->uiNodeHandle, &rowGap);
    return ERROR_CODE_NO_ERROR;
}

void ResetGridRowsGap(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getGridModifier()->resetGridRowsGap(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridRowsGap(ArkUI_NodeHandle node)
{
    auto modifier = GetFullImpl()->getNodeModifiers()->getGridModifier();
    g_numberValues[0].f32 = modifier->getGridRowsGap(node->uiNodeHandle);
    return &g_attributeItem;
}

int32_t SetGridNodeAdapter(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->object, ERROR_CODE_PARAM_INVALID);
    auto* nodeAdapter = reinterpret_cast<ArkUINodeAdapterHandle>(item->object);
    return GetFullImpl()->getNodeModifiers()->getGridModifier()->setNodeAdapter(node->uiNodeHandle, nodeAdapter);
}

void ResetGridNodeAdapter(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getGridModifier()->resetNodeAdapter(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridNodeAdapter(ArkUI_NodeHandle node)
{
    ArkUINodeAdapterHandle adapter =
        GetFullImpl()->getNodeModifiers()->getGridModifier()->getNodeAdapter(node->uiNodeHandle);
    g_attributeItem.object = reinterpret_cast<void*>(adapter);
    return &g_attributeItem;
}

int32_t SetGridCachedCount(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    CHECK_NULL_RETURN(item, ERROR_CODE_PARAM_INVALID);
    if (item->size != 1) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (LessNotEqual(item->value[0].i32, NUM_0)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    GetFullImpl()->getNodeModifiers()->getGridModifier()->setCachedCount(node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

void ResetGridCachedCount(ArkUI_NodeHandle node)
{
    // already check in entry point.
    auto* fullImpl = GetFullImpl();

    fullImpl->getNodeModifiers()->getGridModifier()->resetCachedCount(node->uiNodeHandle);
}

const ArkUI_AttributeItem* GetGridCachedCount(ArkUI_NodeHandle node)
{
    ArkUI_Int32 value = GetFullImpl()->getNodeModifiers()->getGridModifier()->getCachedCount(node->uiNodeHandle);
    g_numberValues[0].i32 = value;
    return &g_attributeItem;
}

bool CheckIfAttributeLegal(ArkUI_NodeHandle node, int32_t type)
{
    if (node->type == ARKUI_NODE_SPAN) {
        auto it = SPAN_ATTRIBUTES_MAP.find(type);
        return it != SPAN_ATTRIBUTES_MAP.end();
    }
    if (node->type == ARKUI_NODE_CUSTOM_SPAN) {
        return false;
    }
    return true;
}

using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
using Resetter = void(ArkUI_NodeHandle node);

int32_t SetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = {
        SetWidth,
        SetHeight,
        SetBackgroundColor,
        SetBackgroundImage,
        SetPadding,
        SetKey,
        SetEnabled,
        SetMargin,
        SetTranslate,
        SetScale,
        SetRotate,
        SetBrightness,
        SetSaturate,
        SetBlur,
        SetLinearGradient,
        SetAlign,
        SetOpacity,
        SetBorderWidth,
        SetBorderRadius,
        SetBorderColor,
        SetBorderStyle,
        SetZIndex,
        SetVisibility,
        SetClip,
        SetClipShape,
        SetTransform,
        SetHitTestBehavior,
        SetPosition,
        SetShadow,
        SetCustomShadow,
        SetBackgroundImageSize,
        SetBackgroundImageSizeWithStyle,
        SetBackgroundBlurStyle,
        SetTransformCenter,
        SetOpacityTransition,
        SetRotateTransition,
        SetScaleTransition,
        SetTranslateTransition,
        SetMoveTransition,
        SetFocusable,
        SetDefaultFocus,
        SetResponseRegion,
        SetOverlay,
        SetSweepGradient,
        SetRadialGradient,
        SetMask,
        SetBlendMode,
        SetDirection,
        SetConstraintSize,
        SetGrayscale,
        SetInvert,
        SetSepia,
        SetContrast,
        SetForegroundColor,
        SetOffset,
        SetMarkAnchor,
        SetBackgroundImagePosition,
        SetAlignRules,
        SetAlignSelf,
        SetFlexGrow,
        SetFlexShrink,
        SetFlexBasis,
        SetAccessibilityGroup,
        SetAccessibilityText,
        SetAccessibilityLevel,
        SetAccessibilityDescription,
        SetNeedFocus,
        SetAspectRatio,
        SetLayoutWeight,
        SetDisplayPriority,
        SetOutlineWidth,
        SetWidthPercent,
        SetHeightPercent,
        SetPaddingPercent,
        SetMarginPercent,
        SetGeometryTransition,
        SetChainMode,
        SetRenderFit,
        SetOutlineColor,
        SetSize,
        SetRenderGroup,
        SetColorBlend,
        SetForegroundBlurStyle,
        SetLayoutRect,
        SetFocusOnTouch,
        SetBorderWidthPercent,
        SetBorderRadiusPercent,
        nullptr,
        SetAccessibilityActions,
        SetAccessibilityRole,
        SetAccessibilityState,
        SetAccessibilityValue,
        SetExpandSafeArea,
        SetAreaChangeRatio,
        SetTransition,
        nullptr,
        SetFocusBox,
        SetClickDistance,
        SetTabStop,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = {
        GetWidth,
        GetHeight,
        GetBackgroundColor,
        GetBackgroundImage,
        GetPadding,
        GetKey,
        GetEnabled,
        GetMargin,
        GetTranslate,
        GetScale,
        GetRotate,
        GetBrightness,
        GetSaturate,
        GetBlur,
        GetLinearGradient,
        GetAlign,
        GetOpacity,
        GetBorderWidth,
        GetBorderRadius,
        GetBorderColor,
        GetBorderStyle,
        GetZIndex,
        GetVisibility,
        GetClip,
        GetClipShape,
        GetTransform,
        GetHitTestBehavior,
        GetPosition,
        GetShadow,
        GetCustomShadow,
        GetBackgroundImageSize,
        GetBackgroundImageSizeWithStyle,
        GetBackgroundBlurStyle,
        GetTransformCenter,
        GetOpacityTransition,
        GetRotateTransition,
        GetScaleTransition,
        GetTranslateTransition,
        GetMoveTransition,
        GetFocusable,
        GetDefaultFocus,
        GetResponseRegion,
        GetOverlay,
        GetSweepGradient,
        GetRadialGradient,
        GetMask,
        GetBlendMode,
        GetDirection,
        GetConstraintSize,
        GetGrayscale,
        GetInvert,
        GetSepia,
        GetContrast,
        GetForegroundColor,
        GetOffset,
        GetMarkAnchor,
        GetBackgroundImagePosition,
        GetAlignRules,
        GetAlignSelf,
        GetFlexGrow,
        GetFlexShrink,
        GetFlexBasis,
        GetAccessibilityGroup,
        GetAccessibilityText,
        GetAccessibilityLevel,
        GetAccessibilityDescription,
        GetNeedFocus,
        GetAspectRatio,
        GetLayoutWeight,
        GetDisplayPriority,
        GetOutlineWidth,
        GetWidthPercent,
        GetHeightPercent,
        GetPaddingPercent,
        GetMarginPercent,
        GetGeometryTransition,
        GetChainMode,
        GetRenderFit,
        GetOutlineColor,
        GetSize,
        GetRenderGroup,
        GetColorBlend,
        GetForegroundBlurStyle,
        GetLayoutRect,
        GetFocusOnTouch,
        GetBorderWidthPercent,
        GetBorderRadiusPercent,
        GetAccessibilityID,
        GetAccessibilityActions,
        GetAccessibilityRole,
        GetAccessibilityState,
        GetAccessibilityValue,
        GetExpandSafeArea,
        GetAreaChangeRatio,
        GetTransition,
        GetUniqueID,
        nullptr,
        nullptr,
        GetTabStop,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    if (!getters[subTypeId]) {
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetCommonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = {
        ResetWidth,
        ResetHeight,
        ResetBackgroundColor,
        ResetBackgroundImage,
        ResetPadding,
        ResetKey,
        ResetEnabled,
        ResetMargin,
        ResetTranslate,
        ResetScale,
        ResetRotate,
        ResetBrightness,
        ResetSaturate,
        ResetBlur,
        ResetLinearGradient,
        ResetAlign,
        ResetOpacity,
        ResetBorderWidth,
        ResetBorderRadius,
        ResetBorderColor,
        ResetBorderStyle,
        ResetZIndex,
        ResetVisibility,
        ResetClip,
        ResetClipShape,
        ResetTransform,
        ResetHitTestBehavior,
        ResetPosition,
        ResetShadow,
        ResetCustomShadow,
        ResetBackgroundImageSize,
        ResetBackgroundImageSizeWithStyle,
        ResetBackgroundBlurStyle,
        ResetTransformCenter,
        ResetOpacityTransition,
        ResetRotateTransition,
        ResetScaleTransition,
        ResetTranslateTransition,
        ResetMoveTransition,
        ResetFocusable,
        ResetDefaultFocus,
        ResetResponseRegion,
        ResetOverlay,
        ResetSweepGradient,
        ResetRadialGradient,
        ResetMask,
        ResetBlendMode,
        ResetDirection,
        ResetConstraintSize,
        ResetGrayscale,
        ResetInvert,
        ResetSepia,
        ResetContrast,
        ResetForegroundColor,
        ResetOffset,
        ResetMarkAnchor,
        ResetBackgroundImagePosition,
        ResetAlignRules,
        ResetAlignSelf,
        ResetFlexGrow,
        ResetFlexShrink,
        ResetFlexBasis,
        ResetAccessibilityGroup,
        ResetAccessibilityText,
        ResetAccessibilityLevel,
        ResetAccessibilityDescription,
        nullptr,
        ResetAspectRatio,
        ResetLayoutWeight,
        ResetDisplayPriority,
        ResetOutlineWidth,
        ResetWidthPercent,
        ResetHeightPercent,
        ResetPaddingPercent,
        ResetMarginPercent,
        ResetGeometryTransition,
        ResetChainMode,
        ResetRenderFit,
        ResetOutlineColor,
        ResetSize,
        ResetRenderGroup,
        ResetColorBlend,
        ResetForegroundBlurStyle,
        ResetLayoutRect,
        ResetFocusOnTouch,
        ResetBorderWidthPercent,
        ResetBorderRadiusPercent,
        nullptr,
        ResetAccessibilityActions,
        ResetAccessibilityRole,
        ResetAccessibilityState,
        ResetAccessibilityValue,
        ResetExpandSafeArea,
        ResetAreaChangeRatio,
        nullptr,
        nullptr,
        ResetFocusBox,
        ResetClickDistance,
        ResetTabStop,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "common node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        resetters[subTypeId](node);
    }
}

int32_t SetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetTextContent, SetFontColor, SetFontSize, SetFontStyle, SetFontWeight, SetLineHeight,
        SetDecoration, SetTextCase, SetLetterSpacing, SetMaxLines, SetTextAlign, SetTextOverflow, SetTextFontFamily,
        SetTextCopyOption, SetBaseLineOffset, SetTextShadow, SetTextMinFontSize, SetTextMaxFontSize, SetTextFont,
        SetTextHeightAdaptivePolicy, SetTextIndent, SetTextWordBreak, SetTextEllipsisMode, SetLineSpacing,
        SetFontFeature, SetTextEnableDateDetector, SetTextDataDetectorConfig, SetTextSelectedBackgroundColor,
        SetTextContentWithStyledString, SetHalfLeading, SetImmutableFontWeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetTextContent, GetFontColor, GetFontSize, GetFontStyle, GetFontWeight, GetLineHeight,
        GetDecoration, GetTextCase, GetLetterSpacing, GetMaxLines, GetTextAlign, GetTextOverflow, GetTextFontFamily,
        GetTextCopyOption, GetBaseLineOffset, GetTextShadow, GetTextMinFontSize, GetTextMaxFontSize, GetTextFont,
        GetTextHeightAdaptivePolicy, GetTextIndent, GetTextWordBreak, GetTextEllipsisMode, GetLineSpacing,
        GetFontFeature, GetTextEnableDateDetector, GetTextDataDetectorConfig, GetTextSelectedBackgroundColor, nullptr,
        GetHalfLeading, GetFontWeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*) || !getters[subTypeId]) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetTextAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTextContent, ResetFontColor, ResetFontSize, ResetFontStyle, ResetFontWeight,
        ResetLineHeight, ResetDecoration, ResetTextCase, ResetLetterSpacing, ResetMaxLines, ResetTextAlign,
        ResetTextOverflow, ResetTextFontFamily, ResetTextCopyOption, ResetBaselineOffset, ResetTextShadow,
        ResetTextMinFontSize, ResetTextMaxFontSize, ResetTextFont, ResetTextHeightAdaptivePolicy, ResetTextIndent,
        ResetTextWordBreak, ResetTextEllipsisMode, ResetLineSpacing, ResetFontFeature, ResetTextEnableDateDetector,
        ResetTextDataDetectorConfig, ResetTextSelectedBackgroundColor, ResetTextContentWithStyledString,
        ResetHalfLeading, ResetFontWeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "text node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetSpanContent, SetSpanTextBackgroundStyle, SetBaseLineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetSpanContent, GetSpanTextBackgroundStyle, GetBaseLineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetSpanContent, ResetSpanTextBackgroundStyle, ResetBaselineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetImageSpanSrc, SetVerticalAlign, SetAlt, SetImageSpanBaselineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetImageSpanSrc, GetVerticalAlign, GetAlt, GetImageSpanBaselineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetImageSpanAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetImageSpanSrc, ResetVerticalAlign, ResetAlt, ResetImageSpanBaselineOffset };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetImageSrc, SetObjectFit, SetInterpolation, SetObjectRepeat, SetColorFilter,
        SetAutoResize, SetAlt, SetImageDraggable, SetRenderMode, SetFitOriginalSize, SetFillColor, SetResizable };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetImageSrc, GetObjectFit, GetInterpolation, GetObjectRepeat, GetColorFilter,
        GetAutoResize, GetAlt, GetImageDraggable, GetRenderMode, GetFitOriginalSize, GetFillColor, GetResizable };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetImageAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetImageSrc, ResetObjectFit, ResetInterpolation, ResetObjectRepeat,
        ResetColorFilter, ResetAutoResize, ResetAlt, ResetImageDraggable, ResetRenderMode,
        ResetFitOriginalSize, ResetFillColor, ResetResizable};
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "image node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetToggleSelectedColor, SetToggleSwitchPointColor, SetToggleValue,
        SetToggleUnselectedColor };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetToggleSelectedColor, GetToggleSwitchPointColor, GetToggleValue,
        GetToggleUnselectedColor };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetToggleAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetToggleSelectedColor, ResetToggleSwitchPointColor, ResetToggleValue,
        ResetToggleUnselectedColor };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "toggle node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

int32_t SetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetLoadingProgressColor, SetLoadingProgressEnableLoading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetLoadingProgressColor, ResetLoadingProgressEnableLoading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetLoadingProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetLoadingProgressColor, GetLoadingProgressEnableLoading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

int32_t SetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetTextInputPlaceholder, SetTextInputText, SetCaretColor, SetCaretStyle,
        SetShowUnderline, SetMaxLength, SetEnterKeyType, SetPlaceholderColor, SetTextInputPlaceholderFont,
        SetEnableKeyboardOnFocus, SetTextInputType, SetSelectedBackgroundColor, SetShowPasswordIcon,
        StopTextInputEditing, SetTextInputCancelButton, SetTextInputTextSelection, SetTextInputUnderlineColor,
        SetTextInputEnableAutoFill, SetTextInputContentType, SetTextInputPasswordRules, SetTextInputSelectAll,
        SetInputFilter, SetTextInputStyle, SetTextInputCaretOffset, nullptr, nullptr,
        SetTextInputSelectionMenuHidden, SetBlurOnSubmit, SetInputCustomKeyboard, SetTextInputWordBreak,
        SetTextInputShowKeyBoardOnFocus, SetTextInputNumberOfLines, SetLetterSpacing, SetEnablePreviewText,
        SetTextInputHalfLeading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetTextInputPlaceholder, GetTextInputText, GetCaretColor, GetCaretStyle,
        GetShowUnderline, GetMaxLength, GetEnterKeyType, GetPlaceholderColor, GetTextInputPlaceholderFont,
        GetEnableKeyboardOnFocus, GetTextInputType, GetSelectedBackgroundColor, GetShowPasswordIcon, GetTextInputEditing,
        GetTextInputCancelButton, GetTextInputTextSelection, GetTextInputUnderlineColor, GetTextInputEnableAutoFill,
        GetTextInputContentType, GetTextInputPasswordRules, GetTextInputSelectAll, GetInputFilter,
        GetTextInputStyle, GetTextInputCaretOffset, GetTextInputContentRect, GetTextInputContentLineCount,
        GetTextInputSelectionMenuHidden, GetBlurOnSubmit, GetInputCustomKeyboard, GetTextInputWordBreak,
        GetTextInputShowKeyBoardOnFocus, GetTextInputNumberOfLines, GetLetterSpacing, GetEnablePreviewText };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetTextInputAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* setters[] = { ResetTextInputPlaceholder, ResetTextInputText, ResetCaretColor, ResetCaretStyle,
        ResetShowUnderline, ResetMaxLength, ResetEnterKeyType, ResetPlaceholderColor, ResetTextInputPlaceholderFont,
        ResetEnableKeyboardOnFocus, ResetTextInputType, ResetSelectedBackgroundColor, ResetShowPasswordIcon, nullptr,
        ResetTextInputCancelButton, ResetTextInputTextSelection, ResetTextInputUnderlineColor,
        ResetTextInputEnableAutoFill, ResetTextInputContentType, ResetTextInputPasswordRules, ResetTextInputSelectAll,
        ResetInputFilter, ResetTextInputStyle, ResetTextInputCaretOffset, nullptr, nullptr,
        ResetTextInputSelectionMenuHidden, ResetBlurOnSubmit, ResetInputCustomKeyboard, ResetTextInputWordBreak,
        ResetTextInputShowKeyBoardOnFocus, ResetTextInputNumberOfLines, ResetLetterSpacing, ResetEnablePreviewText,
        ResetTextInputHalfLeading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textinput node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetTextAreaPlaceholder, SetTextAreaText, SetMaxLength, SetPlaceholderColor,
        SetTextAreaPlaceholderFont, SetCaretColor, StopTextAreaEditing, SetTextAreaType, SetTextAreaShowCounter,
        SetTextAreaSelectionMenuHidden, SetBlurOnSubmit, SetInputFilter, SetSelectedBackgroundColor,
        SetEnterKeyType, SetEnableKeyboardOnFocus, SetTextInputCaretOffset, nullptr, nullptr,
        SetTextInputTextSelection, SetTextInputEnableAutoFill, SetTextInputContentType,
        SetTextInputShowKeyBoardOnFocus, SetTextInputNumberOfLines, SetLetterSpacing, SetEnablePreviewText,
        SetTextInputHalfLeading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetTextAreaPlaceholder, GetTextAreaText, GetMaxLength, GetPlaceholderColor,
        GetTextAreaPlaceholderFont, GetCaretColor, GetTextAreaEditing, GetTextAreaType, GetTextAreaShowCounter,
        GetTextAreaSelectionMenuHidden, GetBlurOnSubmit, GetInputFilter, GetSelectedBackgroundColor,
        GetEnterKeyType, GetEnableKeyboardOnFocus, GetTextInputCaretOffset, GetTextInputContentRect,
        GetTextInputContentLineCount, GetTextInputTextSelection, GetTextInputEnableAutoFill, GetTextInputContentType,
        GetTextInputShowKeyBoardOnFocus, GetTextInputNumberOfLines, GetLetterSpacing, GetEnablePreviewText };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea span node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    if (!getters[subTypeId]) {
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* setters[] = { ResetTextAreaPlaceholder, ResetTextAreaText, ResetMaxLength, ResetPlaceholderColor,
        ResetTextAreaPlaceholderFont, ResetCaretColor, nullptr, ResetTextAreaType, ResetTextAreaShowCounter,
        ResetTextAreaSelectionMenuHidden, ResetBlurOnSubmit, ResetInputFilter, ResetSelectedBackgroundColor,
        ResetEnterKeyType, ResetEnableKeyboardOnFocus, ResetTextInputCaretOffset, nullptr, nullptr,
        ResetTextInputTextSelection, ResetTextInputEnableAutoFill, ResetTextInputContentType,
        ResetTextInputShowKeyBoardOnFocus, ResetTextInputNumberOfLines, ResetLetterSpacing, ResetEnablePreviewText,
        ResetTextInputHalfLeading };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetButtonAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetButtonLabel, SetButtonType };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "button node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetButtonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetButtonLabel, GetButtonType };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "button node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetButtonAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetButtonLabel, ResetButtonType };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "button node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetProgressValue, SetProgressTotal, SetProgressColor, SetProgressType,
        SetProgressLinearStyle };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "progress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetProgressValue, GetProgressTotal, GetProgressColor, GetProgressType,
        GetProgressLinearStyle };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "progress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetProgressAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetProgressValue, ResetProgressTotal, ResetProgressColor, ResetProgressType,
        ResetProgressLinearStyle };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "progress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetCheckboxSelect, SetCheckboxSelectedColor, SetCheckboxUnSelectedColor,
        SetCheckboxMark, SetCheckboxShape, SetCheckboxName, SetCheckboxGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetCheckboxSelect, GetCheckboxSelectedColor, GetCheckboxUnSelectedColor,
        GetCheckboxMark, GetCheckboxShape, GetCheckboxName, GetCheckboxGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetCheckboxAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetCheckboxSelect, ResetCheckboxSelectedColor, ResetCheckboxUnSelectedColor,
        ResetCheckboxMark, ResetCheckboxShape, ResetCheckboxName, ResetCheckboxGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = {
        SetXComponentId,
        SetXComponentType,
        SetXComponentSurfaceSize,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "xcomponent node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetXComponentId, GetXComponentType, GetXComponentSurfaceSize, };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "xcomponent node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetXComponentAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* setters[] = { nullptr, ResetXComponentType, ResetXComponentSurfaceSize };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "xcomponent node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (setters[subTypeId]) {
        setters[subTypeId](node);
    }
}

int32_t SetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetDatePickerLunar, SetDatePickerStart, SetDatePickerEnd, SetDatePickerSelected,
        SetDatePickerDisappearTextStyle, SetDatePickerTextStyle, SetDatePickerSelectedTextStyle, SetDatePickerMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetDatePickerLunar, GetDatePickerStart, GetDatePickerEnd, GetDatePickerSelected,
        GetDatePickerDisappearTextStyle, GetDatePickerTextStyle, GetDatePickerSelectedTextStyle, GetDatePickerMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void ResetDatePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetDatePickerLunar, ResetDatePickerStart, ResetDatePickerEnd,
        ResetDatePickerSelected, ResetDatePickerDisappearTextStyle, ResetDatePickerTextStyle,
        ResetDatePickerSelectedTextStyle, ResetDatePickerMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "datepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetTimePickerSelected, SetTimePickerUseMilitaryTime,
        SetTimePickerDisappearTextStyle, SetTimePickerTextStyle, SetTimePickerSelectedTextStyle,
        nullptr, nullptr, SetTimePickerEnableCascade };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetTimePickerSelected, GetTimePickerUseMilitaryTime, GetTimePickerDisappearTextStyle,
        GetTimePickerTextStyle, GetTimePickerSelectedTextStyle, nullptr, nullptr, GetTimePickerEnableCascade };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void ResetTimePickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTimePickerSelected, ResetTimePickerUseMilitaryTime,
        ResetTimePickerDisappearTextStyle, ResetTimePickerTextStyle, ResetTimePickerSelectedTextStyle,
        nullptr, nullptr, ResetTimePickerEnableCascade };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetTextPickerRange, SetTextPickerSelected, SetTextPickerValue,
        SetTextPickerDisappearTextStyle, SetTextPickerTextStyle, SetTextPickerSelectedTextStyle,
        SetTextPickerSelectedIndex, SetTextPickerCanLoop, SetTextPickerDefaultPickerItemHeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textpicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetTextPickerRange, GetTextPickerSelected, GetTextPickerValue,
        GetTextPickerDisappearTextStyle, GetTextPickerTextStyle, GetTextPickerSelectedTextStyle,
        GetTextPickerSelectedIndex, GetTextPickerCanLoop, GetTextPickerDefaultPickerItemHeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void ResetTextPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetTextPickerRange, ResetTextPickerSelectedIndex, ResetTextPickerValue,
        ResetTextPickerDisappearTextStyle, ResetTextPickerTextStyle, ResetTextPickerSelectedTextStyle,
        ResetTextPickerSelectedIndex, ResetTextPickerCanLoop, ResetTextPickerDefaultPickerItemHeight };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "timepicker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetCalendarPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetHintRadius, SetSelectedDate, SetEdgeAlignment, SetCalendarPickerTextStyle,
        SetCalendarPickerStartDate, SetCalendarPickerEndDate };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "calendar picker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetCalendarPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetHintRadius, ResetSelectedDate, ResetEdgeAlignment,
        ResetCalendarPickerTextStyle, ResetCalendarPickerStartDate, ResetCalendarPickerEndDate };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "calendar picker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetCalendarPickerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetHintRadius, GetSelectedDate, GetEdgeAlignment, GetCalendarPickerTextStyle,
        GetCalendarPickerStartDate, GetCalendarPickerEndDate };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "calendar picker node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

int32_t SetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = {
        SetSliderBlockColor,
        SetSliderTrackColor,
        SetSliderSelectedColor,
        SetSliderShowSteps,
        SetSliderBlockStyle,
        SetSliderValue,
        SetSliderMinValue,
        SetSliderMaxValue,
        SetSliderStep,
        SetSliderDirection,
        SetSliderReverse,
        SetSliderStyle,
        SetSliderTrackThickness,
        SetSliderValidSlideRange,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = {
        GetSliderBlockColor,
        GetSliderTrackColor,
        GetSliderSelectedColor,
        GetSliderShowSteps,
        GetSliderBlockStyle,
        GetSliderValue,
        GetSliderMinValue,
        GetSliderMaxValue,
        GetSliderStep,
        GetSliderDirection,
        GetSliderReverse,
        GetSliderStyle,
        GetSliderTrackThickness,
        GetSliderValidSlideRange,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetSliderAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = {
        ResetSliderBlockColor,
        ResetSliderTrackColor,
        ResetSliderSelectedColor,
        ResetSliderShowSteps,
        ResetSliderBlockStyle,
        ResetSliderValue,
        ResetSliderMinValue,
        ResetSliderMaxValue,
        ResetSliderStep,
        ResetSliderDirection,
        ResetSliderReverse,
        ResetSliderStyle,
        ResetSliderTrackThickness,
        ResetSliderValidSlideRange,
    };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetRadioAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetRadioChecked, SetRadioStyle, SetRadioValue, SetRadioGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "radio node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetRadioAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetRadioChecked, GetRadioStyle, GetRadioValue, GetRadioGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "radio node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetRadioAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetRadioChecked, ResetRadioStyle, ResetRadioValue, ResetRadioGroup };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "radio node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetImageAnimatorAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetImageAnimatorSrc, SetImageAnimatorState, SetImageAnimatorDuration,
        SetImageAnimatorReverse, SetImageAnimatorFixedSize, SetImageAnimatorFillMode, SetImageAnimatorIterations };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "imageAnimator node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetImageAnimatorAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetImageAnimatorSrc, GetImageAnimatorState, GetImageAnimatorDuration,
        GetImageAnimatorReverse, GetImageAnimatorFixedSize, GetImageAnimatorFillMode, GetImageAnimatorIterations };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "imageAnimator node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetImageAnimatorAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* setters[] = { ResetImageAnimatorSrc, ResetImageAnimatorState, ResetImageAnimatorDuration,
        ResetImageAnimatorReverse, ResetImageAnimatorFixedSize, ResetImageAnimatorFillMode,
        ResetImageAnimatorIterations };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "imageAnimator node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node);
}

int32_t SetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetAlignContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetAlignContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}

void ResetStackAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* setters[] = { ResetAlignContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "stack node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    setters[subTypeId](node);
}

int32_t SetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetSwiperLoop, SetSwiperAutoPlay, SetSwiperShowIndicator, SetSwiperInterval,
        SetSwiperVertical, SetSwiperDuration, SetSwiperCurve, SetSwiperItemSpace, SetSwiperIndex, SetSwiperDisplayCount,
        SetSwiperDisableSwipe, SetSwiperShowDisplayArrow, SetSwiperEffectMode, SetSwiperNodeAdapter,
        SetSwiperCachedCount, SetSwiperPrevMargin, SetSwiperNextMargin, SetSwiperIndicator, SetSwiperNestedScroll,
        SetSwiperToIndex, SetSwiperIndicatorInteractive, SetSwiperPageFlipMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

void ResetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetSwiperLoop, ResetSwiperAutoPlay, ResetSwiperShowIndicator,
        ResetSwiperInterval, ResetSwiperVertical, ResetSwiperDuration, ResetSwiperCurve, ResetSwiperItemSpace,
        ResetSwiperIndex, ResetSwiperDisplayCount, ResetSwiperDisableSwipe, ResetSwiperShowDisplayArrow,
        ResetSwiperEffectMode, ResetSwiperNodeAdapter, ResetSwiperCachedCount, ResetSwiperPrevMargin,
        ResetSwiperNextMargin, ResetSwiperIndicator, ResetSwiperNestedScroll, nullptr, ResetSwiperIndicatorInteractive,
        ResetSwiperPageFlipMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetSwiperAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetSwiperLoop, GetSwiperAutoPlay, GetSwiperShowIndicator, GetSwiperInterval,
        GetSwiperVertical, GetSwiperDuration, GetSwiperCurve, GetSwiperItemSpace, GetSwiperIndex, GetSwiperDisplayCount,
        GetSwiperDisableSwipe, GetSwiperShowDisplayArrow, GetSwiperEffectMode, GetSwiperNodeAdapter,
        GetSwiperCachedCount, GetSwiperPrevMargin, GetSwiperNextMargin, GetSwiperIndicator, GetSwiperNestedScroll,
        nullptr, GetSwiperIndicatorInteractive, GetSwiperPageFlipMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "swiper node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetScrollScrollBar, SetScrollScrollBarWidth, SetScrollScrollBarColor,
        SetScrollScrollable, SetScrollEdgeEffect, SetScrollEnableScrollInteraction, SetScrollFriction,
        SetScrollScrollSnap, SetScrollNestedScroll, SetScrollTo, SetScrollEdge, SetScrollEnablePaging,
        SetScrollPage, SetScrollBy, SetScrollFling, SetScrollFadingEdge, nullptr, SetFlingSpeedLimit,
        SetScrollContentClip };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "scroll node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetScrollScrollBar, GetScrollScrollBarWidth, GetScrollScrollBarColor,
        GetScrollScrollable, GetScrollEdgeEffect, GetScrollEnableScrollInteraction, GetScrollFriction,
        GetScrollScrollSnap, GetScrollNestedScroll, GetScrollOffset, GetScrollEdge, GetScrollEnablePaging,
        nullptr, nullptr, nullptr, GetScrollFadingEdge, GetScrollContentSize, GetFlingSpeedLimit,
        GetScrollContentClip };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "slider node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetScrollAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetScrollScrollBar, ResetScrollScrollBarWidth, ResetScrollScrollBarColor,
        ResetScrollScrollable, ResetScrollEdgeEffect, ResetScrollEnableScrollInteraction, ResetScrollFriction,
        ResetScrollScrollSnap, ResetScrollNestedScroll, ResetScrollTo, ResetScrollEdge, ResetScrollEnablePaging,
        nullptr, nullptr, nullptr, ResetScrollFadingEdge, nullptr, ResetFlingSpeedLimit, ResetScrollContentClip };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = { SetListDirection, SetListSticky, SetListSpace, SetListNodeAdapter, SetListCachedCount,
        SetListScrollToIndex, SetListAlignListItem, SetListChildrenMainSize, SetListInitialIndex, SetListDivider };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

const ArkUI_AttributeItem* GetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetListDirection, GetListSticky, GetListSpace, GetListNodeAdapter, GetListCachedCount,
        nullptr, GetListAlignListItem, nullptr, GetListInitialIndex, GetListDivider };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "loadingprogress node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return &g_attributeItem;
    }
    return getters[subTypeId](node);
}

void ResetListAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetListDirection, ResetListSticky, ResetListSpace, ResetListNodeAdapter,
        ResetListCachedCount, nullptr, ResetListAlignListItem, ResetListChildrenMainSize, ResetListInitialIndex,
        ResetListDivider };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "list node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetListItemAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetListItemSwiperAction };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "listitem node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetListItemAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetListItemSwiperAction };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "listitem node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        return resetters[subTypeId](node);
    }
}

int32_t SetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetListItemGroupHeader, SetListItemGroupFooter, SetListItemGroupDivider,
        SetListItemGroupChildrenMainSize };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "listitemgroup node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { nullptr, nullptr, ResetListItemGroupDivider, ResetListItemGroupChildrenMainSize };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "ListItemGroup node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        return resetters[subTypeId](node);
    }
}

const ArkUI_AttributeItem* GetListItemGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { nullptr, nullptr, GetListItemGroupDivider, nullptr };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "ListItemGroup node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetAlignItems, SetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetAlignItems, ResetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetColumnAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetAlignItems, GetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "column node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetAlignItems, SetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetAlignItems, ResetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetRowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetAlignItems, GetJustifyContent };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "row node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetFlexOptions };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetFlexOptions };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetFlexAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetFlexOptions };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "flex node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetRefreshAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetRefreshRefreshing, SetRefreshContent, SetRefreshPullDownRatio, SetRefreshOffset,
        SetPullToRefresh };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "refresh node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetRefreshAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetRefreshRefreshing, nullptr, GetRefreshPullDownRatio, GetRefreshOffset,
        GetPullToRefresh };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "refresh node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    if (getters[subTypeId]) {
        return getters[subTypeId](node);
    }
    return nullptr;
}

void ResetRefreshAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { nullptr, ResetRefreshContent, ResetRefreshPullDownRatio, ResetRefreshOffset,
        ResetPullToRefresh };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "refresh node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        return resetters[subTypeId](node);
    }
}

int32_t SetWaterFlowAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetLayoutDirection, SetColumnsTemplate, SetRowsTemplate, SetWaterFlowColumnsGap,
        SetWaterFlowRowsGap, SetWaterFlowSectionOption, SetWaterFlowNodeAdapter, SetWaterFlowCachedCount,
        SetWaterFlowFooter, SetWaterFlowScrollToIndex, SetItemConstraintSize, SetWaterFlowLayoutMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "waterFlow node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetWaterFlowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetLayoutDirection, ResetColumnsTemplate, ResetRowsTemplate,
        ResetWaterFlowColumnsGap, ResetWaterFlowRowsGap, ResetWaterFlowSectionOption, ResetWaterFlowNodeAdapter,
        ResetWaterFlowCachedCount, ResetWaterFlowFooter, nullptr, ResetItemConstraintSize, ResetWaterFlowLayoutMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "waterFlow node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetWaterFlowAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetLayoutDirection, GetColumnsTemplate, GetRowsTemplate, GetWaterFlowColumnsGap,
        GetWaterFlowRowsGap, GetWaterFlowSectionOption, GetWaterFlowNodeAdapter, GetWaterFlowCachedCount, nullptr,
        nullptr, GetItemConstraintSize, GetWaterFlowLayoutMode };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "waterFlow node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

int32_t SetRelativeContainerAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetRelativeContainerGuideLine, SetRelativeContainerBarrier };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "RelativeContainer node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

int32_t SetGridAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetGridColumnsTemplate, SetGridRowsTemplate, SetGridColumnsGap, SetGridRowsGap,
        SetGridNodeAdapter, SetGridCachedCount };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Grid node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

void ResetRelativeContainerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetRelativeContainerGuideLine, ResetRelativeContainerBarrier };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "RelativeContainer node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

void ResetGridAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetGridColumnsTemplate, ResetGridRowsTemplate, ResetGridColumnsGap,
        ResetGridRowsGap, ResetGridNodeAdapter, ResetGridCachedCount };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Grid node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

const ArkUI_AttributeItem* GetRelativeContainerAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetRelativeContainerGuideLine, GetRelativeContainerBarrier };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "RelativeContainer node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

const ArkUI_AttributeItem* GetGridAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetGridColumnsTemplate, GetGridRowsTemplate, GetGridColumnsGap, GetGridRowsGap,
        GetGridNodeAdapter, GetGridCachedCount };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Grid node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}
} // namespace

int32_t SetCheckboxGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item)
{
    static Setter* setters[] = { SetCheckboxGroupName, SetCheckboxGroupSelectAll, SetCheckboxGroupSelectedColor,
        SetCheckboxGroupUnSelectedColor, SetCheckboxGroupMark, SetCheckboxGroupShape };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, item);
}

const ArkUI_AttributeItem* GetCheckboxGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = { GetCheckboxGroupName, GetCheckboxGroupSelectAll, GetCheckboxGroupSelectedColor,
        GetCheckboxGroupUnSelectedColor, GetCheckboxGroupMark, GetCheckboxGroupShape };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    g_attributeItem.size = RETURN_SIZE_ONE;
    return getters[subTypeId](node);
}

void ResetCheckboxGroupAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = { ResetCheckboxGroupName, ResetCheckboxGroupSelectAll,
        ResetCheckboxGroupSelectedColor, ResetCheckboxGroupUnSelectedColor, ResetCheckboxGroupMark,
        ResetCheckboxGroupShape };
    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Checkbox node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    return resetters[subTypeId](node);
}

int32_t SetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type, const ArkUI_AttributeItem* item)
{
    using AttributeSetterClass = int32_t(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* item);
    static AttributeSetterClass* setterClasses[] = { SetCommonAttribute, SetTextAttribute, SetSpanAttribute,
        SetImageSpanAttribute, SetImageAttribute, SetToggleAttribute, SetLoadingProgressAttribute,
        SetTextInputAttribute, SetTextAreaAttribute, SetButtonAttribute, SetProgressAttribute, SetCheckboxAttribute,
        SetXComponentAttribute, SetDatePickerAttribute, SetTimePickerAttribute, SetTextPickerAttribute,
        SetCalendarPickerAttribute, SetSliderAttribute, SetRadioAttribute, SetImageAnimatorAttribute, nullptr,
        SetCheckboxGroupAttribute, SetStackAttribute, SetSwiperAttribute,
        SetScrollAttribute, SetListAttribute, SetListItemAttribute, SetListItemGroupAttribute, SetColumnAttribute,
        SetRowAttribute, SetFlexAttribute, SetRefreshAttribute, SetWaterFlowAttribute, nullptr,
        SetRelativeContainerAttribute, SetGridAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((static_cast<uint32_t>(nodeSubTypeClass) >= sizeof(setterClasses) / sizeof(AttributeSetterClass*)) ||
        !CheckIfAttributeLegal(node, type) || !CheckIsCNode(node)) {
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    if (!setterClasses[nodeSubTypeClass]) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto result = setterClasses[nodeSubTypeClass](node, subTypeId, item);
    if (result == ERROR_CODE_NO_ERROR) {
        GetFullImpl()->getBasicAPI()->markDirty(node->uiNodeHandle, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    }
    return result;
}

const ArkUI_AttributeItem* GetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    ResetAttributeItem();
    using AttributeGetterClass = const ArkUI_AttributeItem*(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeGetterClass* getterClasses[] = { GetCommonAttribute, GetTextAttribute, GetSpanAttribute,
        GetImageSpanAttribute, GetImageAttribute, GetToggleAttribute, GetLoadingProgressAttribute,
        GetTextInputAttribute, GetTextAreaAttribute, GetButtonAttribute, GetProgressAttribute, GetCheckboxAttribute,
        GetXComponentAttribute, GetDatePickerAttribute, GetTimePickerAttribute, GetTextPickerAttribute,
        GetCalendarPickerAttribute, GetSliderAttribute, GetRadioAttribute, GetImageAnimatorAttribute, nullptr,
        GetCheckboxGroupAttribute, GetStackAttribute,
        GetSwiperAttribute, GetScrollAttribute, GetListAttribute, nullptr, GetListItemGroupAttribute,
        GetColumnAttribute, GetRowAttribute, GetFlexAttribute, GetRefreshAttribute, GetWaterFlowAttribute, nullptr,
        GetRelativeContainerAttribute, GetGridAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((static_cast<uint32_t>(nodeSubTypeClass) >= sizeof(getterClasses) / sizeof(AttributeGetterClass*)) ||
        !CheckIfAttributeLegal(node, type)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return nullptr;
    }
    if (!getterClasses[nodeSubTypeClass]) {
        return nullptr;
    }
    return getterClasses[nodeSubTypeClass](node, subTypeId);
}

int32_t ResetNodeAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType type)
{
    using AttributeResetterClass = void(ArkUI_NodeHandle node, int32_t subTypeId);
    static AttributeResetterClass* resetterClasses[] = { ResetCommonAttribute, ResetTextAttribute, ResetSpanAttribute,
        ResetImageSpanAttribute, ResetImageAttribute, ResetToggleAttribute, ResetLoadingProgressAttribute,
        ResetTextInputAttribute, ResetTextAreaAttribute, ResetButtonAttribute, ResetProgressAttribute,
        ResetCheckboxAttribute, ResetXComponentAttribute, ResetDatePickerAttribute, ResetTimePickerAttribute,
        ResetTextPickerAttribute, ResetCalendarPickerAttribute, ResetSliderAttribute, ResetRadioAttribute,
        ResetImageAnimatorAttribute, nullptr, ResetCheckboxGroupAttribute,
        ResetStackAttribute, ResetSwiperAttribute, ResetScrollAttribute, ResetListAttribute, ResetListItemAttribute,
        ResetListItemGroupAttribute, ResetColumnAttribute, ResetRowAttribute, ResetFlexAttribute, ResetRefreshAttribute,
        ResetWaterFlowAttribute, nullptr, ResetRelativeContainerAttribute, ResetGridAttribute };
    int32_t subTypeClass = type / MAX_NODE_SCOPE_NUM;
    int32_t subTypeId = type % MAX_NODE_SCOPE_NUM;
    int32_t nodeSubTypeClass =
        subTypeClass < MAX_NODE_SCOPE_NUM ? subTypeClass : (subTypeClass - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    if ((static_cast<uint32_t>(nodeSubTypeClass) >= sizeof(resetterClasses) / sizeof(AttributeResetterClass*)) ||
        !CheckIfAttributeLegal(node, type) || !CheckIsCNode(node)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node attribute: %{public}d NOT IMPLEMENT", type);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    if (!resetterClasses[nodeSubTypeClass]) {
        return ERROR_CODE_PARAM_INVALID;
    }
    resetterClasses[nodeSubTypeClass](node, subTypeId);
    GetFullImpl()->getBasicAPI()->markDirty(node->uiNodeHandle, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    return ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::NodeModel
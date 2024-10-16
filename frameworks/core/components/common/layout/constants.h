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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H

#include <cstdint>
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {

enum class LineCap {
    BUTT,
    ROUND,
    SQUARE,
};

enum class ButtonType {
    NORMAL,
    CAPSULE,
    CIRCLE,
    TEXT,
    ARC,
    DOWNLOAD,
    ICON,
    CUSTOM,
    ROUNDED_RECTANGLE,
};

enum class RectWidthStyle {
    TIGHT,
    MAX,
};

enum class RectHeightStyle {
    TIGHT,
    MAX,
    INCLUDE_LINE_SPACE_MIDDLE,
    INCLUDE_LINE_SPACE_TOP,
    INCLUDE_LINE_SPACE_BOTTOM,
    STRUT,
};

// Type of hover mode area.
enum class HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1,
};

enum class ButtonStyleMode { NORMAL, EMPHASIZE, TEXT };

enum class ControlSize { SMALL, NORMAL };

enum class ButtonRole { NORMAL, ERROR };

// Flex Styles
enum class FlexDirection {
    ROW = 0,
    COLUMN,
    ROW_REVERSE,
    COLUMN_REVERSE,
};

enum class FlexAlign {
    AUTO,

    // align to the start of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    FLEX_START,

    // align to the center of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    CENTER,

    // align to the end of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    FLEX_END,

    // stretch the cross size, only used in CrossAxisAlign.
    STRETCH,

    // adjust the cross position according to the textBaseline, only used in CrossAxisAlign.
    BASELINE,

    // align the children on both ends, only used in MainAxisAlign.
    SPACE_BETWEEN,

    // align the child with equivalent space, only used in MainAxisAlign.
    SPACE_AROUND,

    // align the child with space evenly, only used in MainAxisAlign.
    SPACE_EVENLY,

    // User-defined space, only used in MainAxisAlign.
    SPACE_CUSTOMIZATION,
};

enum class MainAxisSize {
    // default setting, fill the max size of the layout param. Only under MAX, mainAxisAlign and FlexItem are valid
    MAX,

    // make the size of row/column as large as its children's size.
    MIN,
};

enum class CrossAxisSize {
    // fill the max size of the layout param in cross size of row/column.
    MAX,

    // make the cross size of row/column as large as its children's size.
    MIN,
};

enum class FlexLayoutMode {
    // If children do not contains flex weight, use this mode. It is the default mode.
    FLEX_ITEM_MODE,

    // If all the children contains flex weight, use this mode.
    FLEX_WEIGHT_MODE,
};

// Box Style
enum class BoxFlex {
    // width and height do not extend to box's parent
    FLEX_NO,

    // width extends to box's parent, height does not extend to box's parent
    FLEX_X,

    // height extends to box's parent, width does not extend to box's parent
    FLEX_Y,

    // width and height extend to box's parent
    FLEX_XY,
};

enum class BoxSizing {
    // The width and height properties includes only the content. Border and padding are not included.
    CONTENT_BOX,

    // The width and height properties includes content, padding and border.
    BORDER_BOX,
};

// Stack Styles
enum class StackFit {
    // keep the child component's size as it is.
    KEEP,

    // keep the child component's size as the parent's.
    STRETCH,

    // use parent's layoutParam to layout the child
    INHERIT,

    // use first child's size as layoutPram max size.
    FIRST_CHILD,
};

enum class Overflow {
    // when the size overflows, clip the exceeding.
    CLIP,

    // when the size overflows, observe the exceeding.
    OBSERVABLE,

    // when the size overflows, scroll the exceeding.
    SCROLL,

    // force clip the exceeding.
    FORCE_CLIP,
};

enum class MainStackSize { MAX, MIN, NORMAL, LAST_CHILD_HEIGHT, MATCH_CHILDREN, MAX_X, MAX_Y };

enum class MainSwiperSize { MAX, MAX_X, MAX_Y, MIN, AUTO };

enum class PositionType {
    PTRELATIVE = 0,
    PTFIXED,
    PTABSOLUTE,
    PTOFFSET,        // percentage layout based on RELATIVE
    PTSEMI_RELATIVE, // absolute offset based on RELATIVE
};

enum class TextAlign {
    LEFT = 4,
    RIGHT = 5,
    CENTER = 1,
    /*
        render the text to fit the size of the text container by adding space
    */
    JUSTIFY = 3,
    /*
        align the text from the start of the text container

        For Direction.ltr, from left side
        For Direction.rtl, from right side
    */
    START = 0,
    /*
        align the text from the end of the text container

        For Direction.ltr, from right side
        For Direction.rtl, from left side
    */
    END = 2,
};

namespace StringUtils {
inline std::string ToString(const TextAlign& textAlign)
{
    static const LinearEnumMapNode<TextAlign, std::string> table[] = {
        { TextAlign::LEFT, "LEFT" },
        { TextAlign::RIGHT, "RIGHT" },
        { TextAlign::CENTER, "CENTER" },
        { TextAlign::JUSTIFY, "JUSTIFY" },
        { TextAlign::START, "START" },
        { TextAlign::END, "END" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textAlign);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class TextDataDetectType {
    PHONE_NUMBER = 0,
    URL,
    EMAIL,
    ADDRESS,
    DATE_TIME,
};

enum class LineBreakStrategy {
    GREEDY = 0,
    HIGH_QUALITY,
    BALANCED,
};

enum class WhiteSpace {
    NORMAL,
    PRE,
    PRE_WRAP,
    NOWRAP,
    PRE_LINE,
    INHERIT,
};

enum class TextOverflow {
    NONE,
    CLIP,
    ELLIPSIS,
    MARQUEE,
    DEFAULT,
};

enum class TextSelectableMode {
    SELECTABLE_UNFOCUSABLE = 0,
    SELECTABLE_FOCUSABLE,
    UNSELECTABLE,
};

namespace StringUtils {
inline std::string ToString(const TextOverflow& textOverflow)
{
    static const LinearEnumMapNode<TextOverflow, std::string> table[] = {
        { TextOverflow::NONE, "NONE" },
        { TextOverflow::CLIP, "CLIP" },
        { TextOverflow::ELLIPSIS, "ELLIPSIS" },
        { TextOverflow::MARQUEE, "MARQUEE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textOverflow);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

// overflow-x: visible|hidden|scroll|auto|no-display|no-content;
enum class TextFieldOverflowX {
    VISIBLE,
    HIDDEN,
    SCROLL,
    AUTO,
    NO_DISPLAY,
    NO_CONTENT,
};

enum class TextDirection {
    LTR,
    RTL,
    INHERIT,
    AUTO,
};

enum class TextDecoration {
    NONE,
    UNDERLINE,
    OVERLINE,
    LINE_THROUGH,
    INHERIT,
};

enum class TextDecorationStyle {
    SOLID,
    DOUBLE,
    DOTTED,
    DASHED,
    WAVY,
    INITIAL,
    INHERIT,
};

enum class TextHeightAdaptivePolicy {
    MAX_LINES_FIRST,
    MIN_FONT_SIZE_FIRST,
    LAYOUT_CONSTRAINT_FIRST,
};

enum class MarqueeDirection {
    LEFT,
    RIGHT,
};

enum class ImageRepeat {
    NO_REPEAT = 0,
    REPEAT_X,
    REPEAT_Y,
    REPEAT,
};

enum class ImageFit {
    FILL,
    CONTAIN,
    COVER,
    FITWIDTH,
    FITHEIGHT,
    NONE,
    SCALE_DOWN,
    TOP_LEFT,
    TOP,
    TOP_END,
    START,
    CENTER,
    END,
    BOTTOM_START,
    BOTTOM,
    BOTTOM_END,
    COVER_TOP_LEFT,
};

enum class DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT,
    STANDARD,
};

enum class AIImageQuality {
    NONE = 0,
    LOW,
    NORMAL,
    HIGH,
};

enum class ImageRenderMode {
    ORIGINAL = 0,
    TEMPLATE,
};

enum class ImageInterpolation {
    NONE = 0,
    LOW,
    MEDIUM,
    HIGH,
};

enum class EdgeEffect {
    SPRING = 0,
    FADE,
    NONE,
};

enum class BorderStyle {
    SOLID,
    DASHED,
    DOTTED,
    NONE,
};

enum class BorderImageRepeat {
    SPACE,
    STRETCH,
    REPEAT,
    ROUND,
};

enum class BorderImageDirection {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    START,
    END,
};

enum class TimePickerFormat {
    HOUR_MINUTE,
    HOUR_MINUTE_SECOND
};

enum class SrcType {
    UNSUPPORTED = -1,
    FILE = 0,
    ASSET,
    NETWORK,
    MEMORY,
    BASE64,
    INTERNAL, // internal cached file resource
    RESOURCE,
    DATA_ABILITY,
    DATA_ABILITY_DECODED,
    RESOURCE_ID, // default resource which src is internal resource id
    PIXMAP,
    ASTC,
};

enum class WrapAlignment {
    START,
    CENTER,
    END,
    SPACE_AROUND,
    SPACE_BETWEEN,
    STRETCH,
    SPACE_EVENLY,
    BASELINE,
};

enum class WrapDirection {
    HORIZONTAL,
    VERTICAL,
    HORIZONTAL_REVERSE,
    VERTICAL_REVERSE,
};

enum class FlexWrap {
    NO_WRAP,
    WRAP,
    WRAP_REVERSE,
};

enum class KeyDirection {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
};

enum class PixelRoundPolicy {
    FORCE_CEIL_START = 1,
    FORCE_FLOOR_START = 1 << 1,
    FORCE_CEIL_TOP = 1 << 2,
    FORCE_FLOOR_TOP = 1 << 3,
    FORCE_CEIL_END = 1 << 4,
    FORCE_FLOOR_END = 1 << 5,
    FORCE_CEIL_BOTTOM = 1 << 6,
    FORCE_FLOOR_BOTTOM = 1 << 7,
};

enum class PixelRoundCalcPolicy {
    NO_FORCE_ROUND = 0,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2,
};

const ImageRepeat IMAGE_REPEATS[] = {
    ImageRepeat::REPEAT,
    ImageRepeat::REPEAT_X,
    ImageRepeat::REPEAT_Y,
    ImageRepeat::NO_REPEAT,
};

enum class WindowModal : int32_t {
    NORMAL = 0,
    SEMI_MODAL = 1,
    SEMI_MODAL_FULL_SCREEN = 2,
    DIALOG_MODAL = 3,
    CONTAINER_MODAL = 4,
    FIRST_VALUE = NORMAL,
    LAST_VALUE = CONTAINER_MODAL,
};

enum class WindowMode : uint32_t {
    WINDOW_MODE_UNDEFINED = 0,
    WINDOW_MODE_FULLSCREEN = 1,
    WINDOW_MODE_SPLIT_PRIMARY = 100,
    WINDOW_MODE_SPLIT_SECONDARY,
    WINDOW_MODE_FLOATING,
    WINDOW_MODE_PIP
};

enum class WindowType : uint32_t {
    WINDOW_TYPE_UNDEFINED = 0,
    WINDOW_TYPE_APP_BASE = 1,
    WINDOW_TYPE_APP_END = 1003,
    WINDOW_TYPE_FLOAT = 2106,
};

enum class PanelType {
    MINI_BAR,
    FOLDABLE_BAR,
    TEMP_DISPLAY,
    CUSTOM,
};

enum class PanelMode {
    MINI,
    HALF,
    FULL,
    AUTO,
    CUSTOM,
};

enum class ColorScheme : int32_t {
    SCHEME_LIGHT = 0,
    SCHEME_TRANSPARENT = 1,
    SCHEME_DARK = 2,
    FIRST_VALUE = SCHEME_LIGHT,
    LAST_VALUE = SCHEME_DARK,
};

enum class RenderStatus : int32_t {
    UNKNOWN = -1,
    DEFAULT = 0,
    ACTIVITY = 1,
    FOCUS = 2,
    BLUR = 3,
    DISABLE = 4,
    WAITING = 5,
};

enum class BadgePosition {
    RIGHT_TOP,
    RIGHT,
    LEFT,
};

enum class QrcodeType {
    RECT,
    CIRCLE,
};

enum class AnimationCurve {
    FRICTION,
    STANDARD,
};

enum class WindowBlurStyle {
    STYLE_BACKGROUND_SMALL_LIGHT = 100,
    STYLE_BACKGROUND_MEDIUM_LIGHT = 101,
    STYLE_BACKGROUND_LARGE_LIGHT = 102,
    STYLE_BACKGROUND_XLARGE_LIGHT = 103,
    STYLE_BACKGROUND_SMALL_DARK = 104,
    STYLE_BACKGROUND_MEDIUM_DARK = 105,
    STYLE_BACKGROUND_LARGE_DARK = 106,
    STYLE_BACKGROUND_XLARGE_DARK = 107,
};

enum class DisplayType { NO_SETTING = 0, FLEX, GRID, NONE, BLOCK, INLINE, INLINE_BLOCK, INLINE_FLEX };

enum class VisibilityType {
    NO_SETTING = 0,
    VISIBLE,
    HIDDEN,
};

enum class RefreshType {
    AUTO,
    PULL_DOWN,
};

enum class TabBarMode {
    FIXED,
    SCROLLABLE,
    FIXED_START,
};

enum class TabAnimateMode {
    CONTENT_FIRST = 0,
    ACTION_FIRST,
    NO_ANIMATION,
    MAX_VALUE,
};

enum class ShowInNavigationBar {
    SHOW = 0,
    POPUP,
};

enum class HorizontalAlign {
    START = 1,
    CENTER,
    END,
};

enum class VerticalAlign {
    TOP = 1,
    CENTER,
    BOTTOM,
    BASELINE,
    NONE,
};

enum class SwiperDynamicSyncSceneType {
    GESTURE = 0,
    ANIMATE,
};

enum class MarqueeDynamicSyncSceneType {
    ANIMATE = 1,
};

namespace StringUtils {
inline std::string ToString(const VerticalAlign& verticalAlign)
{
    static const LinearEnumMapNode<VerticalAlign, std::string> table[] = {
        { VerticalAlign::TOP, "TOP" },
        { VerticalAlign::CENTER, "CENTER" },
        { VerticalAlign::BOTTOM, "BOTTOM" },
        { VerticalAlign::BASELINE, "BASELINE" },
        { VerticalAlign::NONE, "NONE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), verticalAlign);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class BarPosition {
    START,
    END,
};

enum class CalendarType {
    NORMAL = 0,
    SIMPLE,
};

enum class SideBarContainerType { EMBED, OVERLAY, AUTO };

enum class SideBarPosition { START, END };

enum class SideBarStatus {
    SHOW,
    HIDDEN,
    CHANGING,
    AUTO,
};

enum class HitTestMode {
    /**
     *  Both self and children respond to the hit test for touch events,
     *  but block hit test of the other nodes which is masked by this node.
     */
    HTMDEFAULT = 0,

    /**
     * Self respond to the hit test for touch events,
     * but block hit test of children and other nodes which is masked by this node.
     */
    HTMBLOCK,

    /**
     * Self and child respond to the hit test for touch events,
     * and allow hit test of other nodes which is masked by this node.
     */
    HTMTRANSPARENT,

    /**
     * Self not respond to the hit test for touch events,
     * but children respond to the hit test for touch events.
     */
    HTMNONE
};

enum class CopyOptions {
    None = 0,
    InApp,
    Local,
    Distributed,
};

enum class VisibleType {
    VISIBLE = 0,
    INVISIBLE,
    GONE,
};

enum class ShapeMode {
    /*
     * unspecified, follow theme.
     */
    DEFAULT = 0,
    /*
     * rect scrollbar.
     */
    RECT,
    /*
     * round scrollbar.
     */
    ROUND,
};

enum class DisplayMode {
    /*
     * do not display scrollbar.
     */
    OFF = 0,
    /*
     * display scrollbar on demand.
     */
    AUTO,
    /*
     * always display scrollbar.
     */
    ON,
};

enum class PositionMode {
    /*
     * display scrollbar on right.
     */
    RIGHT = 0,
    /*
     * display scrollbar on left.
     */
    LEFT,
    /*
     * display scrollbar on bottom.
     */
    BOTTOM,
};

enum class XComponentType {
    UNKNOWN = -1,
    SURFACE = 0,
    COMPONENT,
    TEXTURE,
    NODE,
};

enum class RenderMode { ASYNC_RENDER = 0, SYNC_RENDER };

inline constexpr uint32_t STATE_NORMAL = 0;
inline constexpr uint32_t STATE_PRESSED = 1;
inline constexpr uint32_t STATE_FOCUS = 1 << 1;
inline constexpr uint32_t STATE_CHECKED = 1 << 2;
inline constexpr uint32_t STATE_DISABLED = 1 << 3;
inline constexpr uint32_t STATE_WAITING = 1 << 4;
inline constexpr uint32_t STATE_HOVERED = 1 << 5;
inline constexpr uint32_t STATE_ACTIVE = 1 << 6;

enum class TabBarStyle {
    NOSTYLE = 0,
    SUBTABBATSTYLE,
    BOTTOMTABBATSTYLE,
};

enum class GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1,
};

enum class GestureTypeName {
    UNKNOWN = -1,
    TAP_GESTURE = 0,
    LONG_PRESS_GESTURE = 1,
    PAN_GESTURE = 2,
    PINCH_GESTURE = 3,
    SWIPE_GESTURE = 4,
    ROTATION_GESTURE = 5,
    DRAG = 6,
    CLICK = 7,
    BOXSELECT = 8,
    WEBSCROLL = 9,
    TEXTFIELD_BOXSELECT = 10
};

enum class ModifierKey {
    CTRL = 0,
    SHIFT = 1,
    ALT = 2,
};

enum class FunctionKey {
    ESC = 0,
    F1 = 1,
    F2 = 2,
    F3 = 3,
    F4 = 4,
    F5 = 5,
    F6 = 6,
    F7 = 7,
    F8 = 8,
    F9 = 9,
    F10 = 10,
    F11 = 11,
    F12 = 12,
    TAB = 13,
    DPAD_UP = 14,
    DPAD_DOWN = 15,
    DPAD_LEFT = 16,
    DPAD_RIGHT = 17,
};

enum class ObscuredReasons {
    PLACEHOLDER = 0,
};

enum class MaximizeMode : uint32_t {
    MODE_AVOID_SYSTEM_BAR,
    MODE_FULL_FILL,
    MODE_RECOVER,
};

enum class RenderFit : int32_t {
    CENTER = 0,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    RESIZE_FILL,
    RESIZE_CONTAIN,
    RESIZE_CONTAIN_TOP_LEFT,
    RESIZE_CONTAIN_BOTTOM_RIGHT,
    RESIZE_COVER,
    RESIZE_COVER_TOP_LEFT,
    RESIZE_COVER_BOTTOM_RIGHT,
};

enum class KeyBoardAvoidMode : int32_t {
    OFFSET = 0,
    RESIZE = 1,
    OFFSET_WITH_CARET = 2,
    RESIZE_WITH_CARET = 3,
};

enum class SwipeActionState : uint32_t {
    COLLAPSED = 0,
    EXPANDED,
    ACTIONING,
};
/**
 * souce is Rosen::Orientation
 */
enum class Orientation : uint32_t {
    BEGIN = 0,
    UNSPECIFIED = BEGIN,
    VERTICAL = 1,
    HORIZONTAL = 2,
    REVERSE_VERTICAL = 3,
    REVERSE_HORIZONTAL = 4,
    SENSOR = 5,
    SENSOR_VERTICAL = 6,
    SENSOR_HORIZONTAL = 7,
    AUTO_ROTATION_RESTRICTED = 8,
    AUTO_ROTATION_PORTRAIT_RESTRICTED = 9,
    AUTO_ROTATION_LANDSCAPE_RESTRICTED = 10,
    LOCKED = 11,
    END = LOCKED,
};

enum class NodeRenderType : uint32_t {
    RENDER_TYPE_DISPLAY = 0,
    RENDER_TYPE_TEXTURE,
};

enum class MarqueeUpdateStrategy : uint32_t {
    DEFAULT = 0,
    PRESERVE_POSITION,
};

enum class EdgeType {
    MARGIN,
    PADDING,
    SAFE_AREA_PADDING,
};

enum class SafeAreaSyncType : uint32_t {
    SYNC_TYPE_NONE = 0,
    SYNC_TYPE_KEYBOARD,
    SYNC_TYPE_AVOID_AREA,
    SYNC_TYPE_WINDOW_IGNORE
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H

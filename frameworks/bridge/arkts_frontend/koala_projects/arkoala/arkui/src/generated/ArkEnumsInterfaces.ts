/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
export enum CheckBoxShape {
    CIRCLE,
    ROUNDED_SQUARE = 1,
}
export enum Color {
    WHITE,
    White = WHITE,
    BLACK = 1,
    Black = BLACK,
    BLUE = 2,
    Blue = BLUE,
    BROWN = 3,
    Brown = BROWN,
    GRAY = 4,
    Gray = GRAY,
    GREEN = 5,
    Green = GREEN,
    GREY = 6,
    Grey = GREY,
    ORANGE = 7,
    Orange = ORANGE,
    PINK = 8,
    Pink = PINK,
    RED = 9,
    Red = RED,
    YELLOW = 10,
    Yellow = YELLOW,
    TRANSPARENT = 11,
    Transparent = TRANSPARENT,
}
export enum ColoringStrategy {
    INVERT = "invert",
    AVERAGE = "average",
    PRIMARY = "primary",
}
export enum ImageFit {
    CONTAIN,
    Contain = CONTAIN,
    COVER = 1,
    Cover = COVER,
    AUTO = 2,
    Auto = AUTO,
    FILL = 3,
    Fill = FILL,
    SCALE_DOWN = 4,
    ScaleDown = SCALE_DOWN,
    NONE = 5,
    None = NONE,
    TOP_START = 7,
    TOP = 8,
    TOP_END = 9,
    START = 10,
    CENTER = 11,
    END = 12,
    BOTTOM_START = 13,
    BOTTOM = 14,
    BOTTOM_END = 15,
}
export enum BorderStyle {
    DOTTED,
    Dotted = DOTTED,
    DASHED = 1,
    Dashed = DASHED,
    SOLID = 2,
    Solid = SOLID,
}
export enum LineJoinStyle {
    MITER,
    Miter = MITER,
    ROUND = 1,
    Round = ROUND,
    BEVEL = 2,
    Bevel = BEVEL,
}
export enum TouchType {
    DOWN,
    Down = DOWN,
    UP = 1,
    Up = UP,
    MOVE = 2,
    Move = MOVE,
    CANCEL = 3,
    Cancel = CANCEL,
}
export enum MouseButton {
    LEFT,
    Left = LEFT,
    RIGHT = 1,
    Right = RIGHT,
    MIDDLE = 2,
    Middle = MIDDLE,
    BACK = 3,
    Back = BACK,
    FORWARD = 4,
    Forward = FORWARD,
    NONE = 5,
    None = NONE,
}
export enum MouseAction {
    PRESS,
    Press = PRESS,
    RELEASE = 1,
    Release = RELEASE,
    MOVE = 2,
    Move = MOVE,
    HOVER = 3,
    Hover = HOVER,
}
export enum AnimationStatus {
    INITIAL,
    Initial = INITIAL,
    RUNNING = 1,
    Running = RUNNING,
    PAUSED = 2,
    Paused = PAUSED,
    STOPPED = 3,
    Stopped = STOPPED,
}
export enum Curve {
    LINEAR,
    Linear = LINEAR,
    EASE = 1,
    Ease = EASE,
    EASE_IN = 2,
    EaseIn = EASE_IN,
    EASE_OUT = 3,
    EaseOut = EASE_OUT,
    EASE_IN_OUT = 4,
    EaseInOut = EASE_IN_OUT,
    FAST_OUT_SLOW_IN = 5,
    FastOutSlowIn = FAST_OUT_SLOW_IN,
    LINEAR_OUT_SLOW_IN = 6,
    LinearOutSlowIn = LINEAR_OUT_SLOW_IN,
    FAST_OUT_LINEAR_IN = 7,
    FastOutLinearIn = FAST_OUT_LINEAR_IN,
    EXTREME_DECELERATION = 8,
    ExtremeDeceleration = EXTREME_DECELERATION,
    SHARP = 9,
    Sharp = SHARP,
    RHYTHM = 10,
    Rhythm = RHYTHM,
    SMOOTH = 11,
    Smooth = SMOOTH,
    FRICTION = 12,
    Friction = FRICTION,
}
export enum FillMode {
    NONE,
    None = NONE,
    FORWARDS = 1,
    Forwards = FORWARDS,
    BACKWARDS = 2,
    Backwards = BACKWARDS,
    BOTH = 3,
    Both = BOTH,
}
export enum PlayMode {
    NORMAL,
    Normal = NORMAL,
    REVERSE = 1,
    Reverse = REVERSE,
    ALTERNATE = 2,
    Alternate = ALTERNATE,
    ALTERNATE_REVERSE = 3,
    AlternateReverse = ALTERNATE_REVERSE,
}
export enum KeyType {
    DOWN,
    Down = DOWN,
    UP = 1,
    Up = UP,
}
export enum KeySource {
    UNKNOWN,
    Unknown = UNKNOWN,
    KEYBOARD = 1,
    Keyboard = KEYBOARD,
}
export enum Edge {
    TOP,
    Top = TOP,
    CENTER = 1,
    Center = CENTER,
    BOTTOM = 2,
    Bottom = BOTTOM,
    BASELINE = 3,
    Baseline = BASELINE,
    START = 4,
    Start = START,
    MIDDLE = 5,
    Middle = MIDDLE,
    END = 6,
    End = END,
}
export enum Week {
    MON,
    Mon = MON,
    TUE = 1,
    Tue = TUE,
    WED = 2,
    Wed = WED,
    THUR = 3,
    Thur = THUR,
    FRI = 4,
    Fri = FRI,
    SAT = 5,
    Sat = SAT,
    SUN = 6,
    Sun = SUN,
}
export enum Direction {
    LTR,
    Ltr = LTR,
    RTL = 1,
    Rtl = RTL,
    AUTO = 2,
    Auto = AUTO,
}
export enum BarState {
    OFF,
    Off = OFF,
    AUTO = 1,
    Auto = AUTO,
    ON = 2,
    On = ON,
}
export enum EdgeEffect {
    SPRING,
    Spring = SPRING,
    FADE = 1,
    Fade = FADE,
    NONE = 2,
    None = NONE,
}
export enum Alignment {
    TOP_START,
    TopStart = TOP_START,
    TOP = 1,
    Top = TOP,
    TOP_END = 2,
    TopEnd = TOP_END,
    START = 3,
    Start = START,
    CENTER = 4,
    Center = CENTER,
    END = 5,
    End = END,
    BOTTOM_START = 6,
    BottomStart = BOTTOM_START,
    BOTTOM = 7,
    Bottom = BOTTOM,
    BOTTOM_END = 8,
    BottomEnd = BOTTOM_END,
}
export enum TransitionType {
    ALL,
    All = ALL,
    INSERT = 1,
    Insert = INSERT,
    DELETE = 2,
    Delete = DELETE,
}
export enum RelateType {
    FILL,
    FIT = 1,
}
export enum Visibility {
    VISIBLE,
    Visible = VISIBLE,
    HIDDEN = 1,
    Hidden = HIDDEN,
    NONE = 2,
    None = NONE,
}
export enum LineCapStyle {
    BUTT,
    Butt = BUTT,
    ROUND = 1,
    Round = ROUND,
    SQUARE = 2,
    Square = SQUARE,
}
export enum Axis {
    VERTICAL,
    Vertical = VERTICAL,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
}
export enum HorizontalAlign {
    START,
    Start = START,
    CENTER = 1,
    Center = CENTER,
    END = 2,
    End = END,
}
export enum FlexAlign {
    START,
    Start = START,
    CENTER = 1,
    Center = CENTER,
    END = 2,
    End = END,
    SPACE_BETWEEN = 3,
    SpaceBetween = SPACE_BETWEEN,
    SPACE_AROUND = 4,
    SpaceAround = SPACE_AROUND,
    SPACE_EVENLY = 5,
    SpaceEvenly = SPACE_EVENLY,
}
export enum ItemAlign {
    AUTO,
    Auto = AUTO,
    START = 1,
    Start = START,
    CENTER = 2,
    Center = CENTER,
    END = 3,
    End = END,
    BASELINE = 4,
    Baseline = BASELINE,
    STRETCH = 5,
    Stretch = STRETCH,
}
export enum FlexDirection {
    ROW,
    Row = ROW,
    COLUMN = 1,
    Column = COLUMN,
    ROW_REVERSE = 2,
    RowReverse = ROW_REVERSE,
    COLUMN_REVERSE = 3,
    ColumnReverse = COLUMN_REVERSE,
}
export enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2,
}
export enum FlexWrap {
    NO_WRAP,
    NoWrap = NO_WRAP,
    WRAP = 1,
    Wrap = WRAP,
    WRAP_REVERSE = 2,
    WrapReverse = WRAP_REVERSE,
}
export enum VerticalAlign {
    TOP,
    Top = TOP,
    CENTER = 1,
    Center = CENTER,
    BOTTOM = 2,
    Bottom = BOTTOM,
}
export enum ImageRepeat {
    NO_REPEAT,
    NoRepeat = NO_REPEAT,
    X = 1,
    Y = 2,
    XY = 3,
}
export enum ImageSize {
    AUTO,
    Auto = AUTO,
    COVER = 1,
    Cover = COVER,
    CONTAIN = 2,
    Contain = CONTAIN,
    FILL = 3,
}
export enum GradientDirection {
    LEFT,
    Left = LEFT,
    TOP = 1,
    Top = TOP,
    RIGHT = 2,
    Right = RIGHT,
    BOTTOM = 3,
    Bottom = BOTTOM,
    LEFT_TOP = 4,
    LeftTop = LEFT_TOP,
    LEFT_BOTTOM = 5,
    LeftBottom = LEFT_BOTTOM,
    RIGHT_TOP = 6,
    RightTop = RIGHT_TOP,
    RIGHT_BOTTOM = 7,
    RightBottom = RIGHT_BOTTOM,
    NONE = 8,
    None = NONE,
}
export enum SharedTransitionEffectType {
    STATIC,
    Static = STATIC,
    EXCHANGE = 1,
    Exchange = EXCHANGE,
}
export enum FontStyle {
    NORMAL,
    Normal = NORMAL,
    ITALIC = 1,
    Italic = ITALIC,
}
export enum FontWeight {
    LIGHTER,
    Lighter = LIGHTER,
    NORMAL = 1,
    Normal = NORMAL,
    REGULAR = 2,
    Regular = REGULAR,
    MEDIUM = 3,
    Medium = MEDIUM,
    BOLD = 4,
    Bold = BOLD,
    BOLDER = 5,
    Bolder = BOLDER,
}
export enum TextAlign {
    CENTER,
    Center = CENTER,
    START = 1,
    Start = START,
    END = 2,
    End = END,
    JUSTIFY = 3,
}
export enum TextOverflow {
    NONE,
    None = NONE,
    CLIP = 1,
    Clip = CLIP,
    ELLIPSIS = 2,
    Ellipsis = ELLIPSIS,
    MARQUEE = 3,
}
export enum TextDecorationType {
    NONE,
    None = NONE,
    UNDERLINE = 1,
    Underline = UNDERLINE,
    OVERLINE = 2,
    Overline = OVERLINE,
    LINE_THROUGH = 3,
    LineThrough = LINE_THROUGH,
}
export enum TextCase {
    NORMAL,
    Normal = NORMAL,
    LOWER_CASE = 1,
    LowerCase = LOWER_CASE,
    UPPER_CASE = 2,
    UpperCase = UPPER_CASE,
}
export enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2,
}
export enum ResponseType {
    RIGHT_CLICK,
    RightClick = RIGHT_CLICK,
    LONG_PRESS = 1,
    LongPress = LONG_PRESS,
}
export enum HoverEffect {
    AUTO,
    Auto = AUTO,
    SCALE = 1,
    Scale = SCALE,
    HIGHLIGHT = 2,
    Highlight = HIGHLIGHT,
    NONE = 3,
    None = NONE,
}
export enum Placement {
    LEFT,
    Left = LEFT,
    RIGHT = 1,
    Right = RIGHT,
    TOP = 2,
    Top = TOP,
    BOTTOM = 3,
    Bottom = BOTTOM,
    TOP_LEFT = 4,
    TopLeft = TOP_LEFT,
    TOP_RIGHT = 5,
    TopRight = TOP_RIGHT,
    BOTTOM_LEFT = 6,
    BottomLeft = BOTTOM_LEFT,
    BOTTOM_RIGHT = 7,
    BottomRight = BOTTOM_RIGHT,
    LEFT_TOP = 8,
    LeftTop = LEFT_TOP,
    LEFT_BOTTOM = 9,
    LeftBottom = LEFT_BOTTOM,
    RIGHT_TOP = 10,
    RightTop = RIGHT_TOP,
    RIGHT_BOTTOM = 11,
    RightBottom = RIGHT_BOTTOM,
}
export enum ArrowPointPosition {
    START = "Start",
    CENTER = "Center",
    END = "End",
}
export enum CopyOptions {
    NONE,
    None = NONE,
    IN_APP = 1,
    InApp = IN_APP,
    LOCAL_DEVICE = 2,
    LocalDevice = LOCAL_DEVICE,
    CROSS_DEVICE = 3,
}
export enum HitTestMode {
    DEFAULT,
    Default = DEFAULT,
    BLOCK = 1,
    Block = BLOCK,
    TRANSPARENT = 2,
    Transparent = TRANSPARENT,
    NONE = 3,
    None = NONE,
}
export enum TitleHeight {
    MAIN_ONLY,
    MainOnly = MAIN_ONLY,
    MAIN_WITH_SUB = 1,
    MainWithSub = MAIN_WITH_SUB,
}
export enum ModifierKey {
    CTRL,
    SHIFT = 1,
    ALT = 2,
}
export enum FunctionKey {
    ESC,
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
}
export enum ImageSpanAlignment {
    BASELINE,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3,
}
export enum ObscuredReasons {
    PLACEHOLDER,
}
export enum TextContentStyle {
    DEFAULT,
    INLINE = 1,
}
export enum ClickEffectLevel {
    LIGHT,
    MIDDLE = 1,
    HEAVY = 2,
}
export enum XComponentType {
    SURFACE,
    COMPONENT = 1,
    TEXTURE = 2,
    NODE = 3,
}
export enum NestedScrollMode {
    SELF_ONLY,
    SELF_FIRST = 1,
    PARENT_FIRST = 2,
    PARALLEL = 3,
}
export enum ScrollSource {
    DRAG,
    FLING = 1,
    EDGE_EFFECT = 2,
    OTHER_USER_INPUT = 3,
    SCROLL_BAR = 4,
    SCROLL_BAR_FLING = 5,
    SCROLLER = 6,
    SCROLLER_ANIMATION = 7,
}
export enum RenderFit {
    CENTER,
    TOP = 1,
    BOTTOM = 2,
    LEFT = 3,
    RIGHT = 4,
    TOP_LEFT = 5,
    TOP_RIGHT = 6,
    BOTTOM_LEFT = 7,
    BOTTOM_RIGHT = 8,
    RESIZE_FILL = 9,
    RESIZE_CONTAIN = 10,
    RESIZE_CONTAIN_TOP_LEFT = 11,
    RESIZE_CONTAIN_BOTTOM_RIGHT = 12,
    RESIZE_COVER = 13,
    RESIZE_COVER_TOP_LEFT = 14,
    RESIZE_COVER_BOTTOM_RIGHT = 15,
}
export enum DialogButtonStyle {
    DEFAULT,
    HIGHLIGHT = 1,
}
export enum WordBreak {
    NORMAL,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
}
export enum LineBreakStrategy {
    GREEDY,
    HIGH_QUALITY = 1,
    BALANCED = 2,
}
export enum EllipsisMode {
    START,
    CENTER = 1,
    END = 2,
}
export type Nullable<T> = T | undefined;
export enum OptionWidthMode {
    FIT_CONTENT = "fit_content",
    FIT_TRIGGER = "fit_trigger",
}
export enum IlluminatedType {
    NONE,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5,
}
export enum FoldStatus {
    FOLD_STATUS_UNKNOWN,
    FOLD_STATUS_EXPANDED = 1,
    FOLD_STATUS_FOLDED = 2,
    FOLD_STATUS_HALF_FOLDED = 3,
}
export enum AppRotation {
    ROTATION_0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3,
}
export enum EmbeddedType {
    EMBEDDED_UI_EXTENSION,
}
export enum MarqueeUpdateStrategy {
    DEFAULT,
    PRESERVE_POSITION = 1,
}
export enum TextDecorationStyle {
    SOLID,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4,
}
export enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2,
}
export enum AccessibilityHoverType {
    HOVER_ENTER,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3,
}
export enum WidthBreakpoint {
    WIDTH_XS,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4,
}
export enum HeightBreakpoint {
    HEIGHT_SM,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2,
}

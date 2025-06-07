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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
export enum CheckBoxShape {
    CIRCLE = 0,
    ROUNDED_SQUARE = 1
}
export enum Color {
    WHITE = 0,
    White = 0,
    BLACK = 1,
    Black = 1,
    BLUE = 2,
    Blue = 2,
    BROWN = 3,
    Brown = 3,
    GRAY = 4,
    Gray = 4,
    GREEN = 5,
    Green = 5,
    GREY = 6,
    Grey = 6,
    ORANGE = 7,
    Orange = 7,
    PINK = 8,
    Pink = 8,
    RED = 9,
    Red = 9,
    YELLOW = 10,
    Yellow = 10,
    TRANSPARENT = 11,
    Transparent = 11
}
export enum ColoringStrategy {
    INVERT = "invert",
    AVERAGE = "average",
    PRIMARY = "primary"
}
export enum ImageFit {
    CONTAIN = 0,
    Contain = 0,
    COVER = 1,
    Cover = 1,
    AUTO = 2,
    Auto = 2,
    FILL = 3,
    Fill = 3,
    SCALE_DOWN = 4,
    ScaleDown = 4,
    NONE = 5,
    None = 5,
    TOP_START = 7,
    TOP = 8,
    TOP_END = 9,
    START = 10,
    CENTER = 11,
    END = 12,
    BOTTOM_START = 13,
    BOTTOM = 14,
    BOTTOM_END = 15,
    MATRIX = 16
}
export enum BorderStyle {
    DOTTED = 0,
    Dotted = 0,
    DASHED = 1,
    Dashed = 1,
    SOLID = 2,
    Solid = 2
}
export enum LineJoinStyle {
    MITER = 0,
    Miter = 0,
    ROUND = 1,
    Round = 1,
    BEVEL = 2,
    Bevel = 2
}
export enum TouchType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1,
    MOVE = 2,
    Move = 2,
    CANCEL = 3,
    Cancel = 3
}
export enum InteractionHand {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}
export enum MouseButton {
    LEFT = 1,
    Left = 1,
    RIGHT = 2,
    Right = 2,
    MIDDLE = 4,
    Middle = 4,
    BACK = 8,
    Back = 8,
    FORWARD = 16,
    Forward = 16,
    NONE = 0,
    None = 0
}
export enum MouseAction {
    PRESS = 1,
    Press = 1,
    RELEASE = 2,
    Release = 2,
    MOVE = 3,
    Move = 3,
    HOVER = 4,
    Hover = 4,
    CANCEL = 13
}
export enum AnimationStatus {
    INITIAL = 0,
    Initial = 0,
    RUNNING = 1,
    Running = 1,
    PAUSED = 2,
    Paused = 2,
    STOPPED = 3,
    Stopped = 3
}
export enum Curve {
    LINEAR = 0,
    Linear = 0,
    EASE = 1,
    Ease = 1,
    EASE_IN = 2,
    EaseIn = 2,
    EASE_OUT = 3,
    EaseOut = 3,
    EASE_IN_OUT = 4,
    EaseInOut = 4,
    FAST_OUT_SLOW_IN = 5,
    FastOutSlowIn = 5,
    LINEAR_OUT_SLOW_IN = 6,
    LinearOutSlowIn = 6,
    FAST_OUT_LINEAR_IN = 7,
    FastOutLinearIn = 7,
    EXTREME_DECELERATION = 8,
    ExtremeDeceleration = 8,
    SHARP = 9,
    Sharp = 9,
    RHYTHM = 10,
    Rhythm = 10,
    SMOOTH = 11,
    Smooth = 11,
    FRICTION = 12,
    Friction = 12
}
export enum FillMode {
    NONE = 0,
    None = 0,
    FORWARDS = 1,
    Forwards = 1,
    BACKWARDS = 2,
    Backwards = 2,
    BOTH = 3,
    Both = 3
}
export enum PlayMode {
    NORMAL = 0,
    Normal = 0,
    REVERSE = 1,
    Reverse = 1,
    ALTERNATE = 2,
    Alternate = 2,
    ALTERNATE_REVERSE = 3,
    AlternateReverse = 3
}
export enum KeyType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1
}
export enum KeySource {
    UNKNOWN = 0,
    Unknown = 0,
    KEYBOARD = 1,
    Keyboard = 1,
    JOYSTICK = 2
}
export enum Edge {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    BASELINE = 3,
    Baseline = 3,
    START = 4,
    Start = 4,
    MIDDLE = 5,
    Middle = 5,
    END = 6,
    End = 6
}
export enum Week {
    MON = 0,
    Mon = 0,
    TUE = 1,
    Tue = 1,
    WED = 2,
    Wed = 2,
    THUR = 3,
    Thur = 3,
    FRI = 4,
    Fri = 4,
    SAT = 5,
    Sat = 5,
    SUN = 6,
    Sun = 6
}
export enum Direction {
    LTR = 0,
    Ltr = 0,
    RTL = 1,
    Rtl = 1,
    AUTO = 2,
    Auto = 2
}
export enum BarState {
    OFF = 0,
    Off = 0,
    AUTO = 1,
    Auto = 1,
    ON = 2,
    On = 2
}
export enum EdgeEffect {
    SPRING = 0,
    Spring = 0,
    FADE = 1,
    Fade = 1,
    NONE = 2,
    None = 2
}
export enum Alignment {
    TOP_START = 0,
    TopStart = 0,
    TOP = 1,
    Top = 1,
    TOP_END = 2,
    TopEnd = 2,
    START = 3,
    Start = 3,
    CENTER = 4,
    Center = 4,
    END = 5,
    End = 5,
    BOTTOM_START = 6,
    BottomStart = 6,
    BOTTOM = 7,
    Bottom = 7,
    BOTTOM_END = 8,
    BottomEnd = 8
}
export enum TransitionType {
    ALL = 0,
    All = 0,
    INSERT = 1,
    Insert = 1,
    DELETE = 2,
    Delete = 2
}
export enum RelateType {
    FILL = 0,
    FIT = 1
}
export enum Visibility {
    VISIBLE = 0,
    Visible = 0,
    HIDDEN = 1,
    Hidden = 1,
    NONE = 2,
    None = 2
}
export enum LineCapStyle {
    BUTT = 0,
    Butt = 0,
    ROUND = 1,
    Round = 1,
    SQUARE = 2,
    Square = 2
}
export enum Axis {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1
}
export enum HorizontalAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2
}
export enum FlexAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
    SPACE_BETWEEN = 3,
    SpaceBetween = 3,
    SPACE_AROUND = 4,
    SpaceAround = 4,
    SPACE_EVENLY = 5,
    SpaceEvenly = 5
}
export enum ItemAlign {
    AUTO = 0,
    Auto = 0,
    START = 1,
    Start = 1,
    CENTER = 2,
    Center = 2,
    END = 3,
    End = 3,
    BASELINE = 4,
    Baseline = 4,
    STRETCH = 5,
    Stretch = 5
}
export enum FlexDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3
}
export enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND = 0,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2
}
export enum PixelRoundMode {
    PIXEL_ROUND_ON_LAYOUT_FINISH = 0,
    PIXEL_ROUND_AFTER_MEASURE = 1
}
export enum FlexWrap {
    NO_WRAP = 0,
    NoWrap = 0,
    WRAP = 1,
    Wrap = 1,
    WRAP_REVERSE = 2,
    WrapReverse = 2
}
export enum VerticalAlign {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2
}
export enum ImageRepeat {
    NO_REPEAT = 0,
    NoRepeat = 0,
    X = 1,
    Y = 2,
    XY = 3
}
export enum ImageSize {
    AUTO = 0,
    Auto = 0,
    COVER = 1,
    Cover = 1,
    CONTAIN = 2,
    Contain = 2,
    FILL = 3
}
export enum GradientDirection {
    LEFT = 0,
    Left = 0,
    TOP = 1,
    Top = 1,
    RIGHT = 2,
    Right = 2,
    BOTTOM = 3,
    Bottom = 3,
    LEFT_TOP = 4,
    LeftTop = 4,
    LEFT_BOTTOM = 5,
    LeftBottom = 5,
    RIGHT_TOP = 6,
    RightTop = 6,
    RIGHT_BOTTOM = 7,
    RightBottom = 7,
    NONE = 8,
    None = 8
}
export enum SharedTransitionEffectType {
    STATIC = 0,
    Static = 0,
    EXCHANGE = 1,
    Exchange = 1
}
export enum FontStyle {
    NORMAL = 0,
    Normal = 0,
    ITALIC = 1,
    Italic = 1
}
export enum FontWeight {
    LIGHTER = 0,
    Lighter = 0,
    NORMAL = 1,
    Normal = 1,
    REGULAR = 2,
    Regular = 2,
    MEDIUM = 3,
    Medium = 3,
    BOLD = 4,
    Bold = 4,
    BOLDER = 5,
    Bolder = 5
}
export enum TextAlign {
    CENTER = 0,
    Center = 0,
    START = 1,
    Start = 1,
    END = 2,
    End = 2,
    JUSTIFY = 3
}
export enum TextOverflow {
    NONE = 0,
    None = 0,
    CLIP = 1,
    Clip = 1,
    ELLIPSIS = 2,
    Ellipsis = 2,
    MARQUEE = 3
}
export enum TextDecorationType {
    NONE = 0,
    None = 0,
    UNDERLINE = 1,
    Underline = 1,
    OVERLINE = 2,
    Overline = 2,
    LINE_THROUGH = 3,
    LineThrough = 3
}
export enum TextCase {
    NORMAL = 0,
    Normal = 0,
    LOWER_CASE = 1,
    LowerCase = 1,
    UPPER_CASE = 2,
    UpperCase = 2
}
export enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST = 0,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2
}
export enum ResponseType {
    RIGHT_CLICK = 0,
    RightClick = 0,
    LONG_PRESS = 1,
    LongPress = 1
}
export enum HoverEffect {
    AUTO = 0,
    Auto = 0,
    SCALE = 1,
    Scale = 1,
    HIGHLIGHT = 2,
    Highlight = 2,
    NONE = 3,
    None = 3
}
export enum Placement {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    TOP_LEFT = 4,
    TopLeft = 4,
    TOP_RIGHT = 5,
    TopRight = 5,
    BOTTOM_LEFT = 6,
    BottomLeft = 6,
    BOTTOM_RIGHT = 7,
    BottomRight = 7,
    LEFT_TOP = 8,
    LeftTop = 8,
    LEFT_BOTTOM = 9,
    LeftBottom = 9,
    RIGHT_TOP = 10,
    RightTop = 10,
    RIGHT_BOTTOM = 11,
    RightBottom = 11
}
export enum ArrowPointPosition {
    START = "Start",
    CENTER = "Center",
    END = "End"
}
export enum CopyOptions {
    NONE = 0,
    None = 0,
    IN_APP = 1,
    InApp = 1,
    LOCAL_DEVICE = 2,
    LocalDevice = 2,
    CROSS_DEVICE = 3
}
export enum HitTestMode {
    DEFAULT = 0,
    Default = 0,
    BLOCK = 1,
    Block = 1,
    TRANSPARENT = 2,
    Transparent = 2,
    NONE = 3,
    None = 3
}
export enum TitleHeight {
    MAIN_ONLY = 0,
    MainOnly = 0,
    MAIN_WITH_SUB = 1,
    MainWithSub = 1
}
export enum ModifierKey {
    CTRL = 0,
    SHIFT = 1,
    ALT = 2
}
export enum FunctionKey {
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
    DPAD_RIGHT = 17
}
export enum ImageSpanAlignment {
    BASELINE = 0,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3
}
export enum ObscuredReasons {
    PLACEHOLDER = 0
}
export enum TextContentStyle {
    DEFAULT = 0,
    INLINE = 1
}
export enum ClickEffectLevel {
    LIGHT = 0,
    MIDDLE = 1,
    HEAVY = 2
}
export enum XComponentType {
    SURFACE = 0,
    COMPONENT = 1,
    TEXTURE = 2,
    NODE = 3
}
export enum NestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1,
    PARENT_FIRST = 2,
    PARALLEL = 3
}
export enum ScrollSource {
    DRAG = 0,
    FLING = 1,
    EDGE_EFFECT = 2,
    OTHER_USER_INPUT = 3,
    SCROLL_BAR = 4,
    SCROLL_BAR_FLING = 5,
    SCROLLER = 6,
    SCROLLER_ANIMATION = 7
}
export enum RenderFit {
    CENTER = 0,
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
    RESIZE_COVER_BOTTOM_RIGHT = 15
}
export enum DialogButtonStyle {
    DEFAULT = 0,
    HIGHLIGHT = 1
}
export enum WordBreak {
    NORMAL = 0,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
    HYPHENATION = 3
}
export enum LineBreakStrategy {
    GREEDY = 0,
    HIGH_QUALITY = 1,
    BALANCED = 2
}
export enum IlluminatedType {
    NONE = 0,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5
}
export enum EllipsisMode {
    START = 0,
    CENTER = 1,
    END = 2
}
export type Nullable<T> = T | undefined;
export enum OptionWidthMode {
    FIT_CONTENT = "fit_content",
    FIT_TRIGGER = "fit_trigger"
}
export enum FoldStatus {
    FOLD_STATUS_UNKNOWN = 0,
    FOLD_STATUS_EXPANDED = 1,
    FOLD_STATUS_FOLDED = 2,
    FOLD_STATUS_HALF_FOLDED = 3
}
export enum AppRotation {
    ROTATION_0 = 0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3
}
export enum EmbeddedType {
    EMBEDDED_UI_EXTENSION = 0
}
export enum MarqueeUpdateStrategy {
    DEFAULT = 0,
    PRESERVE_POSITION = 1
}
export enum TextDecorationStyle {
    SOLID = 0,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4
}
export enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE = 0,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2
}
export enum AccessibilityHoverType {
    HOVER_ENTER = 0,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3
}
export enum WidthBreakpoint {
    WIDTH_XS = 0,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4
}
export enum HeightBreakpoint {
    HEIGHT_SM = 0,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2
}
export enum AxisModel {
    ABS_X = 0,
    ABS_Y = 1,
    ABS_Z = 2,
    ABS_RZ = 3,
    ABS_GAS = 4,
    ABS_BRAKE = 5,
    ABS_HAT0X = 6,
    ABS_HAT0Y = 7
}
export enum PageFlipMode {
    CONTINUOUS = 0,
    SINGLE = 1
}
export enum CrownAction {
    BEGIN = 0,
    UPDATE = 1,
    END = 2
}
export enum CrownSensitivity {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
}
export enum AxisAction {
    NONE = 0,
    BEGIN = 1,
    UPDATE = 2,
    END = 3,
    CANCEL = 4
}
export enum FocusDrawLevel {
    SELF = 0,
    TOP = 1
}
export enum DividerMode {
    FLOATING_ABOVE_MENU = 0,
    EMBEDDED_IN_MENU = 1
}

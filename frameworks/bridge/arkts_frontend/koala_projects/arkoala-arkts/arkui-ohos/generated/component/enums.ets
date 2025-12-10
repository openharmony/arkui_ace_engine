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

import { int32, int64, float32 } from '@koalaui/common'
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr } from '@koalaui/interop'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { default as curves } from '@ohos.curves'
export enum CheckBoxShape {
    CIRCLE = 0,
    ROUNDED_SQUARE = 1
}
export enum Color {
    White = '#FFFFFFFF',
    Black = '#FF000000',
    Blue = '#FF0000FF',
    Brown = '#FFA52A2A',
    Gray = '#FF808080',
    Green = '#FF008000',
    Grey = '#FF808080',
    Orange = '#FFFFA500',
    Pink = '#FFFFC0CB',
    Red = '#FFFF0000',
    Yellow = '#FFFFFF00',
    Transparent = '#00000000',
    WHITE = '#FFFFFFFF',
    BLACK = '#FF000000',
    BLUE = '#FF0000FF',
    BROWN = '#FFA52A2A',
    GRAY = '#FF808080',
    GREEN = '#FF008000',
    GREY = '#FF808080',
    ORANGE = '#FFFFA500',
    PINK = '#FFFFC0CB',
    RED = '#FFFF0000',
    YELLOW = '#FFFFFF00',
    TRANSPARENT = '#00000000'
}
export enum ColoringStrategy {
    INVERT = 'invert',
    AVERAGE = 'average',
    PRIMARY = 'primary'
}
export enum ImageFit {
    Fill = 0,
    Contain = 1,
    Cover = 2,
    Auto = 3,
    None = 5,
    ScaleDown = 6,
    TOP_START = 7,
    TOP = 8,
    TOP_END = 9,
    START = 10,
    CENTER = 11,
    END = 12,
    BOTTOM_START = 13,
    BOTTOM = 14,
    BOTTOM_END = 15,
    MATRIX = 16,
    FILL = 0,
    CONTAIN = 1,
    COVER = 2,
    AUTO = 3,
    NONE = 5,
    SCALE_DOWN = 6,
    TOP_START_DUMMY = 7,
    TOP_DUMMY = 8,
    TOP_END_DUMMY = 9,
    START_DUMMY = 10,
    CENTER_DUMMY = 11,
    END_DUMMY = 12,
    BOTTOM_START_DUMMY = 13,
    BOTTOM_DUMMY = 14,
    BOTTOM_END_DUMMY = 15,
    MATRIX_DUMMY = 16
}
export enum BorderStyle {
    Dotted = 2,
    Dashed = 1,
    Solid = 0,
    DOTTED = 2,
    DASHED = 1,
    SOLID = 0
}
export enum LineJoinStyle {
    Miter = 0,
    Round = 1,
    Bevel = 2,
    MITER = 0,
    ROUND = 1,
    BEVEL = 2
}
export enum TouchType {
    Down = 0,
    Up = 1,
    Move = 2,
    Cancel = 3,
    HOVER_ENTER = 9,
    HOVER_MOVE = 10,
    HOVER_EXIT = 11,
    HOVER_CANCEL = 12,
    DOWN = 0,
    UP = 1,
    MOVE = 2,
    CANCEL = 3,
    HOVER_ENTER_DUMMY = 9,
    HOVER_MOVE_DUMMY = 10,
    HOVER_EXIT_DUMMY = 11,
    HOVER_CANCEL_DUMMY = 12
}
export enum InteractionHand {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}
export enum MouseButton {
    Left = 1,
    Right = 2,
    Middle = 4,
    Back = 8,
    Forward = 16,
    None = 0,
    LEFT = 1,
    RIGHT = 2,
    MIDDLE = 4,
    BACK = 8,
    FORWARD = 16,
    NONE = 0
}
export enum MouseAction {
    Press = 1,
    Release = 2,
    Move = 3,
    Hover = 4,
    ENTER_WINDOW = 4,
    LEAVE_WINDOW = 5,
    CANCEL = 13,
    PRESS = 1,
    RELEASE = 2,
    MOVE = 3,
    HOVER = 4,
    ENTER_WINDOW_DUMMY = 4,
    LEAVE_WINDOW_DUMMY = 5,
    CANCEL_DUMMY = 13
}
export enum AnimationStatus {
    Initial = 0,
    Running = 1,
    Paused = 2,
    Stopped = 3,
    INITIAL = 0,
    RUNNING = 1,
    PAUSED = 2,
    STOPPED = 3
}
export type Curve = curves.Curve;
export enum FillMode {
    None = 0,
    Forwards = 1,
    Backwards = 2,
    Both = 3,
    NONE = 0,
    FORWARDS = 1,
    BACKWARDS = 2,
    BOTH = 3
}
export enum PlayMode {
    Normal = 0,
    Reverse = 1,
    Alternate = 2,
    AlternateReverse = 3,
    NORMAL = 0,
    REVERSE = 1,
    ALTERNATE = 2,
    ALTERNATE_REVERSE = 3
}
export enum KeyType {
    Down = 0,
    Up = 1,
    DOWN = 0,
    UP = 1
}
export enum KeySource {
    Unknown = 0,
    Keyboard = 4,
    JOYSTICK = 5,
    UNKNOWN = 0,
    KEYBOARD = 4,
    JOYSTICK_DUMMY = 5
}
export enum Edge {
    Top = 0,
    Bottom = 2,
    Start = 4,
    End = 6,
    TOP = 0,
    BOTTOM = 2,
    START = 4,
    END = 6
}
export enum Week {
    Mon = 0,
    Tue = 1,
    Wed = 2,
    Thur = 3,
    Fri = 4,
    Sat = 5,
    Sun = 6,
    MON = 0,
    TUE = 1,
    WED = 2,
    THUR = 3,
    FRI = 4,
    SAT = 5,
    SUN = 6
}
export enum Direction {
    Ltr = 0,
    Rtl = 1,
    Auto = 2,
    LTR = 0,
    RTL = 1,
    AUTO = 2
}
export enum BarState {
    Off = 0,
    Auto = 1,
    On = 2,
    OFF = 0,
    AUTO = 1,
    ON = 2
}
export enum EdgeEffect {
    Spring = 0,
    Fade = 1,
    None = 2,
    SPRING = 0,
    FADE = 1,
    NONE = 2
}
export enum Alignment {
    TopStart = 0,
    Top = 1,
    TopEnd = 2,
    Start = 3,
    Center = 4,
    End = 5,
    BottomStart = 6,
    Bottom = 7,
    BottomEnd = 8,
    TOP_START = 0,
    TOP = 1,
    TOP_END = 2,
    START = 3,
    CENTER = 4,
    END = 5,
    BOTTOM_START = 6,
    BOTTOM = 7,
    BOTTOM_END = 8
}
export enum LocalizedAlignment {
    TOP_START = 'top_start',
    TOP = 'top',
    TOP_END = 'top_end',
    START = 'start',
    CENTER = 'center',
    END = 'end',
    BOTTOM_START = 'bottom_start',
    BOTTOM = 'bottom',
    BOTTOM_END = 'bottom_end'
}
export enum TransitionType {
    All = 0,
    Insert = 1,
    Delete = 2,
    ALL = 0,
    INSERT = 1,
    DELETE = 2
}
export enum RelateType {
    FILL = 0,
    FIT = 1
}
export enum Visibility {
    Visible = 0,
    Hidden = 1,
    None = 2,
    VISIBLE = 0,
    HIDDEN = 1,
    NONE = 2
}
export enum LineCapStyle {
    Butt = 0,
    Round = 1,
    Square = 2,
    BUTT = 0,
    ROUND = 1,
    SQUARE = 2
}
export enum Axis {
    Vertical = 0,
    Horizontal = 1,
    VERTICAL = 0,
    HORIZONTAL = 1
}
export enum HorizontalAlign {
    Start = 0,
    Center = 1,
    End = 2,
    START = 0,
    CENTER = 1,
    END = 2
}
export enum FlexAlign {
    Start = 0,
    Center = 1,
    End = 2,
    SpaceBetween = 3,
    SpaceAround = 4,
    SpaceEvenly = 5,
    START = 0,
    CENTER = 1,
    END = 2,
    SPACE_BETWEEN = 3,
    SPACE_AROUND = 4,
    SPACE_EVENLY = 5
}
export enum ItemAlign {
    Auto = 0,
    Start = 1,
    Center = 2,
    End = 3,
    Baseline = 4,
    Stretch = 5,
    AUTO = 0,
    START = 1,
    CENTER = 2,
    END = 3,
    BASELINE = 4,
    STRETCH = 5
}
export enum FlexDirection {
    Row = 0,
    Column = 1,
    RowReverse = 2,
    ColumnReverse = 3,
    ROW = 0,
    COLUMN = 1,
    ROW_REVERSE = 2,
    COLUMN_REVERSE = 3
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
    NoWrap = 0,
    Wrap = 1,
    WrapReverse = 2,
    NO_WRAP = 0,
    WRAP = 1,
    WRAP_REVERSE = 2
}
export enum VerticalAlign {
    Top = 0,
    Center = 1,
    Bottom = 2,
    TOP = 0,
    CENTER = 1,
    BOTTOM = 2
}
export enum ImageRepeat {
    NoRepeat = 0,
    X = 1,
    Y = 2,
    XY = 3,
    NO_REPEAT = 0,
    X_DUMMY = 1,
    Y_DUMMY = 2,
    XY_DUMMY = 3
}
export enum ImageSize {
    Auto = 2,
    Cover = 1,
    Contain = 0,
    FILL = 3,
    AUTO = 2,
    COVER = 1,
    CONTAIN = 0,
    FILL_DUMMY = 3
}
export enum GradientDirection {
    Left = 0,
    Top = 1,
    Right = 2,
    Bottom = 3,
    LeftTop = 4,
    LeftBottom = 5,
    RightTop = 6,
    RightBottom = 7,
    None = 8,
    LEFT = 0,
    TOP = 1,
    RIGHT = 2,
    BOTTOM = 3,
    LEFT_TOP = 4,
    LEFT_BOTTOM = 5,
    RIGHT_TOP = 6,
    RIGHT_BOTTOM = 7,
    NONE = 8
}
export enum SharedTransitionEffectType {
    Static = 0,
    Exchange = 1,
    STATIC = 0,
    EXCHANGE = 1
}
export enum FontStyle {
    Normal = 0,
    Italic = 1,
    NORMAL = 0,
    ITALIC = 1
}
export enum FontWeight {
    Lighter = 0,
    Normal = 1,
    Regular = 2,
    Medium = 3,
    Bold = 4,
    Bolder = 5,
    LIGHTER = 0,
    NORMAL = 1,
    REGULAR = 2,
    MEDIUM = 3,
    BOLD = 4,
    BOLDER = 5
}
export enum TextAlign {
    Center = 1,
    Start = 0,
    End = 2,
    JUSTIFY = 3,
    CENTER = 1,
    START = 0,
    END = 2,
    JUSTIFY_DUMMY = 3
}
export enum TextOverflow {
    None = 0,
    Clip = 1,
    Ellipsis = 2,
    MARQUEE = 3,
    NONE = 0,
    CLIP = 1,
    ELLIPSIS = 2,
    MARQUEE_DUMMY = 3
}
export enum TextDecorationType {
    None = 0,
    Underline = 1,
    Overline = 2,
    LineThrough = 3,
    NONE = 0,
    UNDERLINE = 1,
    OVERLINE = 2,
    LINE_THROUGH = 3
}
export enum TextCase {
    Normal = 0,
    LowerCase = 1,
    UpperCase = 2,
    NORMAL = 0,
    LOWER_CASE = 1,
    UPPER_CASE = 2
}
export enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST = 0,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2
}
export enum ResponseType {
    RightClick = 0,
    LongPress = 1,
    RIGHT_CLICK = 0,
    LONG_PRESS = 1
}
export enum HoverEffect {
    Auto = 0,
    Scale = 1,
    Highlight = 2,
    None = 3,
    AUTO = 0,
    SCALE = 1,
    HIGHLIGHT = 2,
    NONE = 3
}
export enum Placement {
    Left = 0,
    Right = 1,
    Top = 2,
    Bottom = 3,
    TopLeft = 4,
    TopRight = 5,
    BottomLeft = 6,
    BottomRight = 7,
    LeftTop = 8,
    LeftBottom = 9,
    RightTop = 10,
    RightBottom = 11,
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
    TOP_LEFT = 4,
    TOP_RIGHT = 5,
    BOTTOM_LEFT = 6,
    BOTTOM_RIGHT = 7,
    LEFT_TOP = 8,
    LEFT_BOTTOM = 9,
    RIGHT_TOP = 10,
    RIGHT_BOTTOM = 11
}
export enum ArrowPointPosition {
    START = 'Start',
    CENTER = 'Center',
    END = 'End'
}
export enum CopyOptions {
    None = 0,
    InApp = 1,
    LocalDevice = 2,
    NONE = 0,
    IN_APP = 1,
    LOCAL_DEVICE = 2
}
export enum HitTestMode {
    Default = 0,
    Block = 1,
    Transparent = 2,
    None = 3,
    BLOCK_HIERARCHY = 4,
    BLOCK_DESCENDANTS = 5,
    DEFAULT = 0,
    BLOCK = 1,
    TRANSPARENT = 2,
    NONE = 3,
    BLOCK_HIERARCHY_DUMMY = 4,
    BLOCK_DESCENDANTS_DUMMY = 5
}
export enum TitleHeight {
    MainOnly = 0,
    MainWithSub = 1,
    MAIN_ONLY = 0,
    MAIN_WITH_SUB = 1
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
    BASELINE = 4,
    BOTTOM = 3,
    CENTER = 2,
    TOP = 1,
    FOLLOW_PARAGRAPH = 5
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
    FIT_CONTENT = 'fit_content',
    FIT_TRIGGER = 'fit_trigger'
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
export enum EventQueryType {
    ON_CLICK = 0
}
export enum TipsAnchorType {
    TARGET = 0,
    CURSOR = 1
}
export enum DialogDisplayMode {
    CENTER_IN_WINDOW = 1,
    CENTER_IN_SCREEN = 0
}
export enum FocusWrapMode {
    DEFAULT = 0,
    WRAP_WITH_ARROW = 1
}
export enum AnimationPropertyType {
    ROTATION = 0,
    TRANSLATION = 1,
    SCALE = 2,
    OPACITY = 3
}
export enum ColorSpace {
    SRGB = 0,
    DISPLAY_P3 = 1
}
export enum AttributeModifierState {
    NORMAL = 0,
    PRESSED = 1,
    FOCUSED = 2,
    DISABLED = 3,
    SELECTED = 4,
    ALL = 5
}

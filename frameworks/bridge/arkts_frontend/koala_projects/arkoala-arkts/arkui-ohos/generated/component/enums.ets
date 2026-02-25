/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
    Transparent = '#00000000'
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
    MATRIX = 16
}
export enum BorderStyle {
    Dotted = 2,
    Dashed = 1,
    Solid = 0
}
export enum RenderStrategy {
    FAST = 0,
    OFFSCREEN = 1
}
export enum LineJoinStyle {
    Miter = 0,
    Round = 1,
    Bevel = 2
}
export enum TouchType {
    Down = 0,
    Up = 1,
    Move = 2,
    Cancel = 3,
    HOVER_ENTER = 9,
    HOVER_MOVE = 10,
    HOVER_EXIT = 11,
    HOVER_CANCEL = 12
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
    None = 0
}
export enum MouseAction {
    Press = 1,
    Release = 2,
    Move = 3,
    Hover = 4,
    ENTER_WINDOW = 4,
    LEAVE_WINDOW = 5,
    CANCEL = 13
}
export enum AnimationStatus {
    Initial = 0,
    Running = 1,
    Paused = 2,
    Stopped = 3
}
export type Curve = curves.Curve;
export enum FillMode {
    None = 0,
    Forwards = 1,
    Backwards = 2,
    Both = 3
}
export enum PlayMode {
    Normal = 0,
    Reverse = 1,
    Alternate = 2,
    AlternateReverse = 3
}
export enum KeyType {
    Down = 0,
    Up = 1
}
export enum KeySource {
    Unknown = 0,
    Keyboard = 4,
    JOYSTICK = 5
}
export enum Edge {
    Top = 0,
    Bottom = 2,
    Start = 4,
    End = 6
}
export enum Week {
    Mon = 0,
    Tue = 1,
    Wed = 2,
    Thur = 3,
    Fri = 4,
    Sat = 5,
    Sun = 6
}
export enum Direction {
    Ltr = 0,
    Rtl = 1,
    Auto = 2
}
export enum BarState {
    Off = 0,
    Auto = 1,
    On = 2
}
export enum EdgeEffect {
    Spring = 0,
    Fade = 1,
    None = 2
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
    BottomEnd = 8
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
    Delete = 2
}
export enum RelateType {
    FILL = 0,
    FIT = 1
}
export enum Visibility {
    Visible = 0,
    Hidden = 1,
    None = 2
}
export enum LineCapStyle {
    Butt = 0,
    Round = 1,
    Square = 2
}
export enum Axis {
    Vertical = 0,
    Horizontal = 1
}
export enum HorizontalAlign {
    Start = 0,
    Center = 1,
    End = 2
}
export enum FlexAlign {
    Start = 0,
    Center = 1,
    End = 2,
    SpaceBetween = 3,
    SpaceAround = 4,
    SpaceEvenly = 5
}
export enum ItemAlign {
    Auto = 0,
    Start = 1,
    Center = 2,
    End = 3,
    Baseline = 4,
    Stretch = 5
}
export enum FlexDirection {
    Row = 0,
    Column = 1,
    RowReverse = 2,
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
    NoWrap = 0,
    Wrap = 1,
    WrapReverse = 2
}
export enum VerticalAlign {
    Top = 0,
    Center = 1,
    Bottom = 2
}
export enum ImageRepeat {
    NoRepeat = 0,
    X = 1,
    Y = 2,
    XY = 3
}
export enum ImageSize {
    Auto = 2,
    Cover = 1,
    Contain = 0,
    FILL = 3
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
    None = 8
}
export enum SharedTransitionEffectType {
    Static = 0,
    Exchange = 1
}
export enum FontStyle {
    Normal = 0,
    Italic = 1
}
export enum FontWeight {
    Lighter = 0,
    Normal = 1,
    Regular = 2,
    Medium = 3,
    Bold = 4,
    Bolder = 5
}
export enum TextAlign {
    Center = 1,
    Start = 0,
    End = 2,
    JUSTIFY = 3,
    LEFT = 4,
    RIGHT = 5
}
export enum TextOverflow {
    None = 0,
    Clip = 1,
    Ellipsis = 2,
    MARQUEE = 3
}
export enum TextDecorationType {
    None = 0,
    Underline = 1,
    Overline = 2,
    LineThrough = 3
}
export enum TextCase {
    Normal = 0,
    LowerCase = 1,
    UpperCase = 2
}
export enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST = 0,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2
}
export enum ResponseType {
    RightClick = 0,
    LongPress = 1
}
export enum HoverEffect {
    None = 0,
    Scale = 2,
    Highlight = 3,
    Auto = 4
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
    RightBottom = 11
}
export enum ArrowPointPosition {
    START = 'Start',
    CENTER = 'Center',
    END = 'End'
}
export enum CopyOptions {
    None = 0,
    InApp = 1,
    LocalDevice = 2
}
export enum ResponseRegionSupportedTool {
    ALL = 0,
    FINGER = 1,
    PEN = 2,
    MOUSE = 3
}
export enum HitTestMode {
    Default = 0,
    Block = 1,
    Transparent = 2,
    None = 3,
    BLOCK_HIERARCHY = 4,
    BLOCK_DESCENDANTS = 5
}
export enum TitleHeight {
    MainOnly = 0,
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
    TEXTURE = 2
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
    END = 2,
    MULTILINE_START = 3,
    MULTILINE_CENTER = 4
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
    ABS_HAT0Y = 7,
    ABS_RX = 8,
    ABS_RY = 9,
    ABS_THROTTLE = 10,
    ABS_RUDDER = 11,
    ABS_WHEEL = 12,
    ABS_HAT1X = 13,
    ABS_HAT1Y = 14,
    ABS_HAT2X = 15,
    ABS_HAT2Y = 16,
    ABS_HAT3X = 17,
    ABS_HAT3Y = 18
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
    SCREEN_BASED = 0,
    WINDOW_BASED = 1
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
export enum AxisType {
    VERTICAL_AXIS = 0,
    HORIZONTAL_AXIS = 1,
    PINCH_AXIS = 2
}
export enum AttributeModifierState {
    NORMAL = 0,
    PRESSED = 1,
    FOCUSED = 2,
    DISABLED = 3,
    SELECTED = 4,
    ALL = 5
}
export enum PresetFillType {
    BREAKPOINT_DEFAULT = 0,
    BREAKPOINT_SM1MD2LG3 = 1,
    BREAKPOINT_SM2MD3LG5 = 2
}
export enum SystemProperties {
    BREAK_POINT = 'system.arkui.breakpoint',
    WINDOW_AVOID_AREA = 'system.window.avoidarea',
    WINDOW_AVOID_AREA_PX = 'system.window.avoidarea.px',
    WINDOW_SIZE = 'system.window.size',
    WINDOW_SIZE_PX = 'system.window.size.px'
}

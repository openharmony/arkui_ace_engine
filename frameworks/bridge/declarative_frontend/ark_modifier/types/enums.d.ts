/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
declare enum CheckBoxShape {
    CIRCLE = 0,
    ROUNDED_SQUARE = 1
}
declare enum Color {
    White,
    Black,
    Blue,
    Brown,
    Gray,
    Green,
    Grey,
    Orange,
    Pink,
    Red,
    Yellow,
    Transparent
}
declare enum ColoringStrategy {
    INVERT = 'invert',
    AVERAGE = 'average',
    PRIMARY = 'primary',
    CONTRAST = 'contrast'
}
declare enum ImageFit {
    Contain,
    Cover,
    Auto,
    Fill,
    ScaleDown,
    None,
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
declare enum BorderStyle {
    Dotted,
    Dashed,
    Solid
}
declare enum RenderStrategy {
    FAST = 0,
    OFFSCREEN = 1
}
declare enum LineJoinStyle {
    Miter,
    Round,
    Bevel
}
declare enum TouchType {
    Down,
    Up,
    Move,
    Cancel,
    HOVER_ENTER = 9,
    HOVER_MOVE = 10,
    HOVER_EXIT = 11,
    HOVER_CANCEL = 12
}
declare enum InteractionHand {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}
declare enum MouseButton {
    Left,
    Right,
    Middle,
    Back,
    Forward,
    None
}
declare enum MouseAction {
    Press,
    Release,
    Move,
    Hover,
    ENTER_WINDOW = 4,
    LEAVE_WINDOW = 5,
    CANCEL = 13
}
declare enum AnimationStatus {
    Initial,
    Running,
    Paused,
    Stopped
}
declare enum Curve {
    Linear,
    Ease,
    EaseIn,
    EaseOut,
    EaseInOut,
    FastOutSlowIn,
    LinearOutSlowIn,
    FastOutLinearIn,
    ExtremeDeceleration,
    Sharp,
    Rhythm,
    Smooth,
    Friction
}
declare enum FillMode {
    None,
    Forwards,
    Backwards,
    Both
}
declare enum PlayMode {
    Normal,
    Reverse,
    Alternate,
    AlternateReverse
}
declare enum KeyType {
    Down,
    Up
}
declare enum KeySource {
    Unknown,
    Keyboard,
    JOYSTICK
}
declare enum Edge {
    Top,
    Center,
    Bottom,
    Baseline,
    Start,
    Middle,
    End
}
declare enum Direction {
    Ltr,
    Rtl,
    Auto
}
declare enum BarState {
    Off,
    Auto,
    On
}
declare enum EdgeEffect {
    Spring,
    Fade,
    None
}
declare enum Alignment {
    TopStart,
    Top,
    TopEnd,
    Start,
    Center,
    End,
    BottomStart,
    Bottom,
    BottomEnd
}
declare enum LocalizedAlignment {
    TOP_START = "top_start",
    TOP = "top",
    TOP_END = "top_end",
    START = "start",
    CENTER = "center",
    END = "end",
    BOTTOM_START = "bottom_start",
    BOTTOM = "bottom",
    BOTTOM_END = "bottom_end"
}
declare enum TransitionType {
    All,
    Insert,
    Delete
}
declare enum Visibility {
    Visible,
    Hidden,
    None
}
declare enum LineCapStyle {
    Butt,
    Round,
    Square
}
declare enum Axis {
    Vertical,
    Horizontal
}
declare enum HorizontalAlign {
    Start,
    Center,
    End
}
declare enum FlexAlign {
    Start,
    Center,
    End,
    SpaceBetween,
    SpaceAround,
    SpaceEvenly
}
declare enum ItemAlign {
    Auto,
    Start,
    Center,
    End,
    Baseline,
    Stretch
}
declare enum FlexDirection {
    Row,
    Column,
    RowReverse,
    ColumnReverse
}
declare enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND = 0,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2
}
declare enum FlexWrap {
    NoWrap,
    Wrap,
    WrapReverse
}
declare enum VerticalAlign {
    Top,
    Center,
    Bottom
}
declare enum ImageRepeat {
    NoRepeat,
    X,
    Y,
    XY
}
declare enum ImageSize {
    Auto,
    Cover,
    Contain,
    FILL = 3
}
declare enum GradientDirection {
    Left,
    Top,
    Right,
    Bottom,
    LeftTop,
    LeftBottom,
    RightTop,
    RightBottom,
    None
}
declare enum SharedTransitionEffectType {
    Static,
    Exchange
}
declare enum FontStyle {
    Normal,
    Italic
}
declare enum FontWeight {
    Lighter,
    Normal,
    Regular,
    Medium,
    Bold,
    Bolder
}
declare enum TextAlign {
    Center,
    Start,
    End,
    JUSTIFY,
    LEFT = 4,
    RIGHT = 5
}
declare enum TextOverflow {
    None,
    Clip,
    Ellipsis,
    MARQUEE
}
declare enum TextDecorationType {
    None,
    Underline,
    Overline,
    LineThrough
}
declare enum TextCase {
    Normal,
    LowerCase,
    UpperCase
}
declare enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST,
    MIN_FONT_SIZE_FIRST,
    LAYOUT_CONSTRAINT_FIRST
}
declare enum ResponseType {
    RightClick,
    LongPress
}
declare enum HoverEffect {
    Auto,
    Scale,
    Highlight,
    None
}
declare enum Placement {
    Left,
    Right,
    Top,
    Bottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    LeftTop,
    LeftBottom,
    RightTop,
    RightBottom
}
declare enum ArrowPointPosition {
    START = 'Start',
    CENTER = 'Center',
    END = 'End'
}
declare enum CopyOptions {
    None = 0,
    InApp = 1,
    LocalDevice = 2,
    CROSS_DEVICE = 3
}
declare enum HitTestMode {
    Default,
    Block,
    Transparent,
    None,
    BLOCK_HIERARCHY,
    BLOCK_DESCENDANTS
}
declare enum TitleHeight {
    MainOnly,
    MainWithSub
}
declare enum ModifierKey {
    CTRL,
    SHIFT,
    ALT
}
declare enum FunctionKey {
    ESC,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    TAB,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT
}
declare enum ImageSpanAlignment {
    BASELINE,
    BOTTOM,
    CENTER,
    TOP,
    FOLLOW_PARAGRAPH
}
declare enum ObscuredReasons {
    PLACEHOLDER = 0
}
declare enum TextContentStyle {
    DEFAULT,
    INLINE
}
declare enum ClickEffectLevel {
    LIGHT,
    MIDDLE,
    HEAVY
}
declare enum NestedScrollMode {
    SELF_ONLY,
    SELF_FIRST,
    PARENT_FIRST,
    PARALLEL
}
declare enum ScrollSource {
    DRAG = 0,
    FLING,
    EDGE_EFFECT,
    OTHER_USER_INPUT,
    SCROLL_BAR,
    SCROLL_BAR_FLING,
    SCROLLER,
    SCROLLER_ANIMATION
}
declare enum RenderFit {
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
declare enum DialogButtonStyle {
    DEFAULT = 0,
    HIGHLIGHT = 1
}
declare enum WordBreak {
    NORMAL = 0,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
    HYPHENATION = 3
}
declare enum LineBreakStrategy {
    GREEDY = 0,
    HIGH_QUALITY = 1,
    BALANCED = 2
}
declare enum IlluminatedType {
    NONE = 0,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5
}
declare enum EllipsisMode {
    START = 0,
    CENTER = 1,
    END = 2,
    MULTILINE_START = 3,
    MULTILINE_CENTER = 4
}
declare enum OptionWidthMode {
    FIT_CONTENT = 'fit_content',
    FIT_TRIGGER = 'fit_trigger'
}
declare enum EmbeddedType {
    EMBEDDED_UI_EXTENSION = 0
}
declare enum MarqueeUpdateStrategy {
    DEFAULT = 0,
    PRESERVE_POSITION = 1
}
declare enum TextDecorationStyle {
    SOLID = 0,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4
}
declare enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE = 0,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2
}
declare enum AccessibilityHoverType {
    HOVER_ENTER = 0,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3
}
declare enum AxisModel {
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
declare enum FocusWrapMode {
    DEFAULT = 0,
    WRAP_WITH_ARROW = 1
}
declare enum PresetFillType {
    BREAKPOINT_DEFAULT = 0,
    BREAKPOINT_SM1MD2LG3 = 1,
    BREAKPOINT_SM2MD3LG5 = 2
}
declare enum CrownAction {
    BEGIN = 0,
    UPDATE = 1,
    END = 2
}
declare enum CrownSensitivity {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
}
declare enum PageFlipMode {
    CONTINUOUS = 0,
    SINGLE = 1
}
declare enum AxisAction {
    NONE = 0,
    BEGIN = 1,
    UPDATE = 2,
    END = 3,
    CANCEL = 4
}
declare enum FocusDrawLevel {
    SELF = 0,
    TOP = 1
}
declare enum DividerMode {
    FLOATING_ABOVE_MENU = 0,
    EMBEDDED_IN_MENU = 1
}
declare enum TipsAnchorType {
    TARGET,
    CURSOR
}
declare enum ResponseRegionSupportedTool {
    ALL = 0,
    FINGER = 1,
    PEN = 2,
    MOUSE = 3
}
declare enum AxisType {
    VERTICAL_AXIS = 0,
    HORIZONTAL_AXIS = 1,
    PINCH_AXIS = 2
}

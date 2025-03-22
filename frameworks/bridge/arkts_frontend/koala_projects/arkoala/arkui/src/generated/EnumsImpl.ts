import { int32, float32 } from "@koalaui/common"
export enum PointerStyle {
    DEFAULT,
    EAST = 1,
    WEST = 2,
    SOUTH = 3,
    NORTH = 4,
    WEST_EAST = 5,
    NORTH_SOUTH = 6,
    NORTH_EAST = 7,
    NORTH_WEST = 8,
    SOUTH_EAST = 9,
    SOUTH_WEST = 10,
    NORTH_EAST_SOUTH_WEST = 11,
    NORTH_WEST_SOUTH_EAST = 12,
    CROSS = 13,
    CURSOR_COPY = 14,
    CURSOR_FORBID = 15,
    COLOR_SUCKER = 16,
    HAND_GRABBING = 17,
    HAND_OPEN = 18,
    HAND_POINTING = 19,
    HELP = 20,
    MOVE = 21,
    RESIZE_LEFT_RIGHT = 22,
    RESIZE_UP_DOWN = 23,
    SCREENSHOT_CHOOSE = 24,
    SCREENSHOT_CURSOR = 25,
    TEXT_CURSOR = 26,
    ZOOM_IN = 27,
    ZOOM_OUT = 28,
    MIDDLE_BTN_EAST = 29,
    MIDDLE_BTN_WEST = 30,
    MIDDLE_BTN_SOUTH = 31,
    MIDDLE_BTN_NORTH = 32,
    MIDDLE_BTN_NORTH_SOUTH = 33,
    MIDDLE_BTN_NORTH_EAST = 34,
    MIDDLE_BTN_NORTH_WEST = 35,
    MIDDLE_BTN_SOUTH_EAST = 36,
    MIDDLE_BTN_SOUTH_WEST = 37,
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,
    HORIZONTAL_TEXT_CURSOR = 39,
    CURSOR_CROSS = 40,
    CURSOR_CIRCLE = 41,
    LOADING = 42,
    RUNNING = 43,
}
export enum RectWidthStyle {
    TIGHT,
    MAX = 1,
}
export enum Affinity {
    UPSTREAM = 0,
    DOWNSTREAM = 1
}
export enum RectHeightStyle {
    TIGHT,
    MAX = 1,
    INCLUDE_LINE_SPACE_MIDDLE = 2,
    INCLUDE_LINE_SPACE_TOP = 3,
    INCLUDE_LINE_SPACE_BOTTOM = 4,
    STRUT = 5,
}
export enum LengthUnit {
    PX,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4,
}
export enum PerfMonitorActionType {
    LAST_DOWN,
    LAST_UP = 1,
    FIRST_MOVE = 2,
}
export enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4,
}
export enum EffectDirection {
    DOWN,
    UP = 1,
}
export enum EffectScope {
    LAYER,
    WHOLE = 1,
}
export enum DialogAlignment {
    TOP,
    Top = TOP,
    CENTER = 1,
    Center = CENTER,
    BOTTOM = 2,
    Bottom = BOTTOM,
    DEFAULT = 3,
    Default = DEFAULT,
    TOP_START = 4,
    TopStart = TOP_START,
    TOP_END = 5,
    TopEnd = TOP_END,
    CENTER_START = 6,
    CenterStart = CENTER_START,
    CENTER_END = 7,
    CenterEnd = CENTER_END,
    BOTTOM_START = 8,
    BottomStart = BOTTOM_START,
    BOTTOM_END = 9,
    BottomEnd = BOTTOM_END,
}
export enum DialogButtonDirection {
    AUTO,
    HORIZONTAL = 1,
    VERTICAL = 2,
}
export enum IndexerAlign {
    LEFT,
    Left = LEFT,
    RIGHT = 1,
    Right = RIGHT,
    START = 2,
    END = 3,
}
export enum BadgePosition {
    RIGHT_TOP,
    RightTop = RIGHT_TOP,
    RIGHT = 1,
    Right = RIGHT,
    LEFT = 2,
    Left = LEFT,
}
export enum ButtonType {
    CAPSULE,
    Capsule = CAPSULE,
    CIRCLE = 1,
    Circle = CIRCLE,
    NORMAL = 2,
    Normal = NORMAL,
    ROUNDED_RECTANGLE = 3,
}
export enum ButtonStyleMode {
    NORMAL,
    EMPHASIZED = 1,
    TEXTUAL = 2,
}
export enum ButtonRole {
    NORMAL,
    ERROR = 1,
}
export enum ControlSize {
    SMALL = "small",
    NORMAL = "normal",
}
export enum CalendarAlign {
    START,
    CENTER = 1,
    END = 2,
}
export enum SelectStatus {
    ALL,
    All = ALL,
    PART = 1,
    Part = PART,
    NONE = 2,
    None = NONE,
}
export enum FinishCallbackType {
    REMOVED,
    LOGICALLY = 1,
}
export enum TouchTestStrategy {
    DEFAULT,
    FORWARD_COMPETITION = 1,
    FORWARD = 2,
}
export enum TransitionHierarchyStrategy {
    NONE,
    ADAPTIVE = 1,
}
export enum ChainStyle {
    SPREAD,
    SPREAD_INSIDE = 1,
    PACKED = 2,
}
export enum TransitionEdge {
    TOP,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
export enum EffectType {
    DEFAULT,
    WINDOW_EFFECT = 1,
}
export enum PreDragStatus {
    ACTION_DETECTING_STATUS,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6,
}
export enum SourceType {
    UNKNOWN,
    Unknown = UNKNOWN,
    MOUSE = 1,
    Mouse = MOUSE,
    TOUCH_SCREEN = 2,
    TouchScreen = TOUCH_SCREEN,
}
export enum SourceTool {
    UNKNOWN,
    Unknown = UNKNOWN,
    FINGER = 1,
    Finger = FINGER,
    PEN = 2,
    Pen = PEN,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5,
}
export enum RepeatMode {
    REPEAT,
    Repeat = REPEAT,
    STRETCH = 1,
    Stretch = STRETCH,
    ROUND = 2,
    Round = ROUND,
    SPACE = 3,
    Space = SPACE,
}
export enum BlurStyle {
    THIN,
    Thin = THIN,
    REGULAR = 1,
    Regular = REGULAR,
    THICK = 2,
    Thick = THICK,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12,
}
export enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2,
}
export enum ThemeColorMode {
    SYSTEM,
    LIGHT = 1,
    DARK = 2,
}
export enum AdaptiveColor {
    DEFAULT,
    AVERAGE = 1,
}
export enum ModalTransition {
    DEFAULT,
    NONE = 1,
    ALPHA = 2,
}
export enum ShadowType {
    COLOR,
    BLUR = 1,
}
export enum ShadowStyle {
    OUTER_DEFAULT_XS,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5,
}
export enum SafeAreaType {
    SYSTEM,
    CUTOUT = 1,
    KEYBOARD = 2,
}
export enum SafeAreaEdge {
    TOP,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
export enum LayoutSafeAreaType {
    SYSTEM,
}
export enum LayoutSafeAreaEdge {
    TOP,
    BOTTOM = 1,
}
export enum SheetSize {
    MEDIUM,
    LARGE = 1,
    FIT_CONTENT = 2,
}
export enum DragBehavior {
    COPY,
    MOVE = 1,
}
export enum DragResult {
    DRAG_SUCCESSFUL,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4,
}
export enum BlendMode {
    NONE,
    CLEAR = 1,
    SRC = 2,
    DST = 3,
    SRC_OVER = 4,
    DST_OVER = 5,
    SRC_IN = 6,
    DST_IN = 7,
    SRC_OUT = 8,
    DST_OUT = 9,
    SRC_ATOP = 10,
    DST_ATOP = 11,
    XOR = 12,
    PLUS = 13,
    MODULATE = 14,
    SCREEN = 15,
    OVERLAY = 16,
    DARKEN = 17,
    LIGHTEN = 18,
    COLOR_DODGE = 19,
    COLOR_BURN = 20,
    HARD_LIGHT = 21,
    SOFT_LIGHT = 22,
    DIFFERENCE = 23,
    EXCLUSION = 24,
    MULTIPLY = 25,
    HUE = 26,
    SATURATION = 27,
    COLOR = 28,
    LUMINOSITY = 29,
}
export enum BlendApplyType {
    FAST,
    OFFSCREEN = 1,
}
export enum SheetType {
    BOTTOM,
    CENTER = 1,
    POPUP = 2,
}
export enum SheetMode {
    OVERLAY,
    EMBEDDED = 1,
}
export enum ScrollSizeMode {
    FOLLOW_DETENT,
    CONTINUOUS = 1,
}
export enum SheetKeyboardAvoidMode {
    NONE,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3,
}
export enum DismissReason {
    PRESS_BACK,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3,
}
export enum MenuPreviewMode {
    NONE,
    IMAGE = 1,
}
export enum OutlineStyle {
    SOLID,
    DASHED = 1,
    DOTTED = 2,
}
export enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
}
export enum MenuPolicy {
    DEFAULT,
    HIDE = 1,
    SHOW = 2,
}
export enum ContentClipMode {
    CONTENT_ONLY,
    BOUNDARY = 1,
    SAFE_AREA = 2,
}
export enum KeyboardAvoidMode {
    DEFAULT,
    NONE = 1,
}
export enum HoverModeAreaType {
    TOP_SCREEN,
    BOTTOM_SCREEN = 1,
}
export enum ModelType {
    TEXTURE,
    SURFACE = 1,
}
export enum DataPanelType {
    LINE,
    Line = LINE,
    CIRCLE = 1,
    Circle = CIRCLE,
}
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
export enum FocusPriority {
    AUTO,
    PRIOR = 2000,
    PREVIOUS = 3000,
}
export enum FormDimension {
    DIMENSION_1_2,
    Dimension_1_2 = DIMENSION_1_2,
    DIMENSION_2_2 = 1,
    Dimension_2_2 = DIMENSION_2_2,
    DIMENSION_2_4 = 2,
    Dimension_2_4 = DIMENSION_2_4,
    DIMENSION_4_4 = 3,
    Dimension_4_4 = DIMENSION_4_4,
    DIMENSION_2_1 = 4,
    Dimension_2_1 = DIMENSION_2_1,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
}
export enum FormRenderingMode {
    FULL_COLOR,
    SINGLE_COLOR = 1,
}
export enum FormShape {
    RECT = 1,
    CIRCLE = 2,
}
export enum PanDirection {
    NONE,
    None = NONE,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
    LEFT = 2,
    Left = LEFT,
    RIGHT = 3,
    Right = RIGHT,
    VERTICAL = 4,
    Vertical = VERTICAL,
    UP = 5,
    Up = UP,
    DOWN = 6,
    Down = DOWN,
    ALL = 7,
    All = ALL,
}
export enum SwipeDirection {
    NONE,
    None = NONE,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
    VERTICAL = 2,
    Vertical = VERTICAL,
    ALL = 3,
    All = ALL,
}
export enum GestureMode {
    SEQUENCE,
    Sequence = SEQUENCE,
    PARALLEL = 1,
    Parallel = PARALLEL,
    EXCLUSIVE = 2,
    Exclusive = EXCLUSIVE,
}
export enum GestureMask {
    NORMAL,
    Normal = NORMAL,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = IGNORE_INTERNAL,
}
export enum GestureJudgeResult {
    CONTINUE,
    REJECT = 1,
}
export namespace GestureControl {
    export enum GestureType {
        TAP_GESTURE,
        LONG_PRESS_GESTURE = 1,
        PAN_GESTURE = 2,
        PINCH_GESTURE = 3,
        SWIPE_GESTURE = 4,
        ROTATION_GESTURE = 5,
        DRAG = 6,
        CLICK = 7,
    }
}
export enum GesturePriority {
    NORMAL,
    PRIORITY = 1,
}
export enum GestureRecognizerState {
    READY,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5,
}
export enum GridDirection {
    ROW,
    Row = ROW,
    COLUMN = 1,
    Column = COLUMN,
    ROW_REVERSE = 2,
    RowReverse = ROW_REVERSE,
    COLUMN_REVERSE = 3,
    ColumnReverse = COLUMN_REVERSE,
}
export enum GridItemAlignment {
    DEFAULT,
    STRETCH = 1,
}
export enum GridItemStyle {
    NONE,
    PLAIN = 1,
}
export enum SizeType {
    AUTO,
    Auto = AUTO,
    XS = 1,
    SM = 2,
    MD = 3,
    LG = 4,
}
export enum BreakpointsReference {
    WINDOW_SIZE,
    WindowSize = WINDOW_SIZE,
    COMPONENT_SIZE = 1,
    ComponentSize = COMPONENT_SIZE,
}
export enum GridRowDirection {
    ROW,
    Row = ROW,
    ROW_REVERSE = 1,
    RowReverse = ROW_REVERSE,
}
export enum ImageRenderMode {
    ORIGINAL,
    Original = ORIGINAL,
    TEMPLATE = 1,
    Template = TEMPLATE,
}
export enum ImageContent {
    EMPTY,
}
export enum DynamicRangeMode {
    HIGH,
    CONSTRAINT = 1,
    STANDARD = 2,
}
export enum ImageInterpolation {
    NONE,
    None = NONE,
    LOW = 1,
    Low = LOW,
    MEDIUM = 2,
    Medium = MEDIUM,
    HIGH = 3,
    High = HIGH,
}
export enum ImageAnalyzerType {
    SUBJECT,
    TEXT = 1,
    OBJECT_LOOKUP = 2,
}
export enum DataOperationType {
    ADD = "add",
    DELETE = "delete",
    EXCHANGE = "exchange",
    MOVE = "move",
    CHANGE = "change",
    RELOAD = "reload",
}
export enum ScrollState {
    IDLE,
    Idle = IDLE,
    SCROLL = 1,
    Scroll = SCROLL,
    FLING = 2,
    Fling = FLING,
}
export enum ListItemAlign {
    START,
    Start = START,
    CENTER = 1,
    Center = CENTER,
    END = 2,
    End = END,
}
export enum ListItemGroupArea {
    NONE,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3,
}
export enum StickyStyle {
    NONE,
    None = NONE,
    HEADER = 1,
    Header = HEADER,
    FOOTER = 2,
    Footer = FOOTER,
}
export enum ChainEdgeEffect {
    DEFAULT,
    STRETCH = 1,
}
export enum ScrollSnapAlign {
    NONE,
    START = 1,
    CENTER = 2,
    END = 3,
}
export enum Sticky {
    NONE,
    None = NONE,
    NORMAL = 1,
    Normal = NORMAL,
    OPACITY = 2,
    Opacity = OPACITY,
}
export enum EditMode {
    NONE,
    None = NONE,
    DELETABLE = 1,
    Deletable = DELETABLE,
    MOVABLE = 2,
    Movable = MOVABLE,
}
export enum SwipeEdgeEffect {
    SPRING,
    Spring = SPRING,
    NONE = 1,
    None = NONE,
}
export enum SwipeActionState {
    COLLAPSED,
    EXPANDED = 1,
    ACTIONING = 2,
}
export enum ListItemStyle {
    NONE,
    CARD = 1,
}
export enum ListItemGroupStyle {
    NONE,
    CARD = 1,
}
export enum LoadingProgressStyle {
    DEFAULT,
    Default = DEFAULT,
    CIRCULAR = 1,
    Circular = CIRCULAR,
    ORBITAL = 2,
    Orbital = ORBITAL,
}
export enum LocationIconStyle {
    FULL_FILLED,
    LINES = 1,
}
export enum LocationDescription {
    CURRENT_LOCATION,
    ADD_LOCATION = 1,
    SELECT_LOCATION = 2,
    SHARE_LOCATION = 3,
    SEND_LOCATION = 4,
    LOCATING = 5,
    LOCATION = 6,
    SEND_CURRENT_LOCATION = 7,
    RELOCATION = 8,
    PUNCH_IN = 9,
    CURRENT_POSITION = 10,
}
export enum LocationButtonOnClickResult {
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
export enum SubMenuExpandingMode {
    SIDE_EXPAND,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2,
}
export enum NavigationSystemTransitionType {
    DEFAULT,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3,
}
export enum NavDestinationMode {
    STANDARD,
    DIALOG = 1,
}
export enum NavRouteMode {
    PUSH_WITH_RECREATE,
    PUSH = 1,
    REPLACE = 2,
}
export enum NavigationMode {
    STACK,
    Stack = STACK,
    SPLIT = 1,
    Split = SPLIT,
    AUTO = 2,
    Auto = AUTO,
}
export enum NavBarPosition {
    START,
    Start = START,
    END = 1,
    End = END,
}
export enum NavigationTitleMode {
    FREE,
    Free = FREE,
    FULL = 1,
    Full = FULL,
    MINI = 2,
    Mini = MINI,
}
export enum LaunchMode {
    STANDARD,
    MOVE_TO_TOP_SINGLETON = 1,
    POP_TO_SINGLETON = 2,
    NEW_INSTANCE = 3,
}
export enum ToolbarItemStatus {
    NORMAL,
    DISABLED = 1,
    ACTIVE = 2,
}
export enum NavigationOperation {
    PUSH = 1,
    POP = 2,
    REPLACE = 3,
}
export enum BarStyle {
    STANDARD,
    STACK = 1,
    SAFE_AREA_PADDING = 2,
}
export enum NavigationType {
    PUSH,
    Push = PUSH,
    BACK = 1,
    Back = BACK,
    REPLACE = 2,
    Replace = REPLACE,
}
export enum RouteType {
    NONE,
    None = NONE,
    PUSH = 1,
    Push = PUSH,
    POP = 2,
    Pop = POP,
}
export enum SlideEffect {
    LEFT,
    Left = LEFT,
    RIGHT = 1,
    Right = RIGHT,
    TOP = 2,
    Top = TOP,
    BOTTOM = 3,
    Bottom = BOTTOM,
    START = 5,
    END = 6,
}
export enum PanelMode {
    MINI,
    Mini = MINI,
    HALF = 1,
    Half = HALF,
    FULL = 2,
    Full = FULL,
}
export enum PanelType {
    MINIBAR,
    Minibar = MINIBAR,
    FOLDABLE = 1,
    Foldable = FOLDABLE,
    TEMPORARY = 2,
    Temporary = TEMPORARY,
    CUSTOM = 3,
}
export enum PanelHeight {
    WRAP_CONTENT = "wrapContent",
}
export enum ParticleType {
    POINT = "point",
    IMAGE = "image",
}
export enum ParticleEmitterShape {
    RECTANGLE = "rectangle",
    CIRCLE = "circle",
    ELLIPSE = "ellipse",
}
export enum DistributionType {
    UNIFORM,
    GAUSSIAN = 1,
}
export enum ParticleUpdater {
    NONE = "none",
    RANDOM = "random",
    CURVE = "curve",
}
export enum DisturbanceFieldShape {
    RECT,
    CIRCLE = 1,
    ELLIPSE = 2,
}
export enum PasteIconStyle {
    LINES,
}
export enum PasteDescription {
    PASTE,
}
export enum PasteButtonOnClickResult {
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
export enum PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2,
}
export enum ProgressType {
    LINEAR,
    Linear = LINEAR,
    RING = 1,
    Ring = RING,
    ECLIPSE = 2,
    Eclipse = ECLIPSE,
    SCALE_RING = 3,
    ScaleRing = SCALE_RING,
    CAPSULE = 4,
    Capsule = CAPSULE,
}
export enum ProgressStatus {
    LOADING,
    PROGRESSING = 1,
}
export enum ProgressStyle {
    LINEAR,
    Linear = LINEAR,
    RING = 1,
    Ring = RING,
    ECLIPSE = 2,
    Eclipse = ECLIPSE,
    SCALE_RING = 3,
    ScaleRing = SCALE_RING,
    CAPSULE = 4,
    Capsule = CAPSULE,
}
export enum RadioIndicatorType {
    TICK,
    DOT = 1,
    CUSTOM = 2,
}
export enum RefreshStatus {
    INACTIVE,
    Inactive = INACTIVE,
    DRAG = 1,
    Drag = DRAG,
    OVER_DRAG = 2,
    OverDrag = OVER_DRAG,
    REFRESH = 3,
    Refresh = REFRESH,
    DONE = 4,
    Done = DONE,
}
export enum BarrierDirection {
    LEFT,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
}
export enum LocalizedBarrierDirection {
    START,
    END = 1,
    TOP = 2,
    BOTTOM = 3,
}
export enum RichEditorDeleteDirection {
    BACKWARD,
    FORWARD = 1,
}
export enum RichEditorSpanType {
    TEXT,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
}
export enum RichEditorResponseType {
    RIGHT_CLICK,
    LONG_PRESS = 1,
    SELECT = 2,
}
export enum SaveIconStyle {
    FULL_FILLED,
    LINES = 1,
    PICTURE = 2,
}
export enum SaveDescription {
    DOWNLOAD,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11,
}
export enum SaveButtonOnClickResult {
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
export enum ScrollDirection {
    VERTICAL,
    Vertical = VERTICAL,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
    FREE = 2,
    Free = FREE,
    NONE = 3,
    None = NONE,
}
export enum ScrollAlign {
    START,
    CENTER = 1,
    END = 2,
    AUTO = 3,
}
export enum ScrollBarDirection {
    VERTICAL,
    Vertical = VERTICAL,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
}
export enum CancelButtonStyle {
    CONSTANT,
    INVISIBLE = 1,
    INPUT = 2,
}
export enum SearchType {
    NORMAL,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
export enum SecurityComponentLayoutDirection {
    HORIZONTAL,
    VERTICAL = 1,
}
export enum ArrowPosition {
    END,
    START = 1,
}
export enum MenuAlignType {
    START,
    CENTER = 1,
    END = 2,
}
export enum SliderStyle {
    OUT_SET,
    OutSet = OUT_SET,
    IN_SET = 1,
    InSet = IN_SET,
    NONE = 2,
}
export enum SliderChangeMode {
    BEGIN,
    Begin = BEGIN,
    MOVING = 1,
    Moving = MOVING,
    END = 2,
    End = END,
    CLICK = 3,
    Click = CLICK,
}
export enum SliderInteraction {
    SLIDE_AND_CLICK,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2,
}
export enum SliderBlockType {
    DEFAULT,
    IMAGE = 1,
    SHAPE = 2,
}
export enum ColorMode {
    LIGHT,
    DARK = 1,
}
export enum LayoutDirection {
    LTR,
    RTL = 1,
    AUTO = 2,
    Auto = AUTO,
}
export enum ItemState {
    NORMAL,
    Normal = NORMAL,
    DISABLED = 1,
    Disabled = DISABLED,
    WAITING = 2,
    Waiting = WAITING,
    SKIP = 3,
    Skip = SKIP,
}
export enum SwiperDisplayMode {
    LEGACY_STRETCH,
    Stretch = LEGACY_STRETCH,
    LEGACY_AUTO_LINEAR = 1,
    AutoLinear = LEGACY_AUTO_LINEAR,
    STRETCH = 2,
    AUTO_LINEAR = 3,
}
export enum SwiperNestedScrollMode {
    SELF_ONLY,
    SELF_FIRST = 1,
}
export enum SymbolRenderingStrategy {
    SINGLE,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2,
}
export enum SymbolEffectStrategy {
    NONE,
    SCALE = 1,
    HIERARCHICAL = 2,
}
export enum EffectFillStyle {
    CUMULATIVE,
    ITERATIVE = 1,
}
export enum BarMode {
    SCROLLABLE,
    Scrollable = SCROLLABLE,
    FIXED = 1,
    Fixed = FIXED,
}
export enum AnimationMode {
    CONTENT_FIRST,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2,
}
export enum BarPosition {
    START,
    Start = START,
    END = 1,
    End = END,
}
export enum LayoutStyle {
    ALWAYS_CENTER,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2,
}
export enum SelectedMode {
    INDICATOR,
    BOARD = 1,
}
export enum LayoutMode {
    AUTO,
    VERTICAL = 1,
    HORIZONTAL = 2,
}
export enum TextSpanType {
    TEXT,
    IMAGE = 1,
    MIXED = 2,
}
export enum TextResponseType {
    RIGHT_CLICK,
    LONG_PRESS = 1,
    SELECT = 2,
}
export enum TextAreaType {
    NORMAL,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
export enum ContentType {
    USER_NAME,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25,
}
export enum TextDataDetectorType {
    PHONE_NUMBER,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4,
}
export enum TextDeleteDirection {
    BACKWARD,
    FORWARD = 1,
}
export enum MenuType {
    SELECTION_MENU,
    PREVIEW_MENU = 1,
}
export enum InputType {
    NORMAL,
    Normal = NORMAL,
    NUMBER = 1,
    Number = NUMBER,
    PHONE_NUMBER = 2,
    PhoneNumber = PHONE_NUMBER,
    EMAIL = 3,
    Email = EMAIL,
    PASSWORD = 4,
    Password = PASSWORD,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
export enum EnterKeyType {
    GO = 2,
    Go = GO,
    SEARCH = 3,
    Search = SEARCH,
    SEND = 4,
    Send = SEND,
    NEXT = 5,
    Next = NEXT,
    DONE = 6,
    Done = DONE,
    PREVIOUS = 7,
    NEW_LINE = 8,
}
export enum TextInputStyle {
    DEFAULT,
    Default = DEFAULT,
    INLINE = 1,
    Inline = INLINE,
}
export enum TimePickerFormat {
    HOUR_MINUTE,
    HOUR_MINUTE_SECOND = 1,
}
export enum ToggleType {
    CHECKBOX,
    Checkbox = CHECKBOX,
    SWITCH = 1,
    Switch = SWITCH,
    BUTTON = 2,
    Button = BUTTON,
}
export enum SeekMode {
    PREVIOUS_KEYFRAME,
    PreviousKeyframe = PREVIOUS_KEYFRAME,
    NEXT_KEYFRAME = 1,
    NextKeyframe = NEXT_KEYFRAME,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = CLOSEST_KEYFRAME,
    ACCURATE = 3,
    Accurate = ACCURATE,
}
export enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X,
    Speed_Forward_0_75_X = SPEED_FORWARD_0_75_X,
    SPEED_FORWARD_1_00_X = 1,
    Speed_Forward_1_00_X = SPEED_FORWARD_1_00_X,
    SPEED_FORWARD_1_25_X = 2,
    Speed_Forward_1_25_X = SPEED_FORWARD_1_25_X,
    SPEED_FORWARD_1_75_X = 3,
    Speed_Forward_1_75_X = SPEED_FORWARD_1_75_X,
    SPEED_FORWARD_2_00_X = 4,
    Speed_Forward_2_00_X = SPEED_FORWARD_2_00_X,
}
export enum MessageLevel {
    DEBUG,
    Debug = DEBUG,
    ERROR = 1,
    Error = ERROR,
    INFO = 2,
    Info = INFO,
    LOG = 3,
    Log = LOG,
    WARN = 4,
    Warn = WARN,
}
export enum MixedMode {
    ALL,
    All = ALL,
    COMPATIBLE = 1,
    Compatible = COMPATIBLE,
    NONE = 2,
    None = NONE,
}
export enum HitTestType {
    EDIT_TEXT,
    EditText = EDIT_TEXT,
    EMAIL = 1,
    Email = EMAIL,
    HTTP_ANCHOR = 2,
    HttpAnchor = HTTP_ANCHOR,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = HTTP_ANCHOR_IMG,
    IMG = 4,
    Img = IMG,
    MAP = 5,
    Map = MAP,
    PHONE = 6,
    Phone = PHONE,
    UNKNOWN = 7,
    Unknown = UNKNOWN,
}
export enum CacheMode {
    DEFAULT,
    Default = DEFAULT,
    NONE = 1,
    None = NONE,
    ONLINE = 2,
    Online = ONLINE,
    ONLY = 3,
    Only = ONLY,
}
export enum OverScrollMode {
    NEVER,
    ALWAYS = 1,
}
export enum WebDarkMode {
    OFF,
    Off = OFF,
    ON = 1,
    On = ON,
    AUTO = 2,
    Auto = AUTO,
}
export enum WebCaptureMode {
    HOME_SCREEN,
}
export enum ThreatType {
    THREAT_ILLEGAL,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3,
}
export enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION,
    ProcessAbnormalTermination = PROCESS_ABNORMAL_TERMINATION,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = PROCESS_WAS_KILLED,
    PROCESS_CRASHED = 2,
    ProcessCrashed = PROCESS_CRASHED,
    PROCESS_OOM = 3,
    ProcessOom = PROCESS_OOM,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = PROCESS_EXIT_UNKNOWN,
}
export enum SslError {
    INVALID,
    Invalid = INVALID,
    HOST_MISMATCH = 1,
    HostMismatch = HOST_MISMATCH,
    DATE_INVALID = 2,
    DateInvalid = DATE_INVALID,
    UNTRUSTED = 3,
    Untrusted = UNTRUSTED,
}
export enum FileSelectorMode {
    FILE_OPEN_MODE,
    FileOpenMode = FILE_OPEN_MODE,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = FILE_OPEN_MULTIPLE_MODE,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = FILE_OPEN_FOLDER_MODE,
    FILE_SAVE_MODE = 3,
    FileSaveMode = FILE_SAVE_MODE,
}
export enum WebLayoutMode {
    NONE,
    FIT_CONTENT = 1,
}
export enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT,
    NAVIGATION_COMMIT_TIMEOUT = 1,
}
export enum ProtectedResourceType {
    MIDI_SYSEX = "TYPE_MIDI_SYSEX",
    MidiSysex = MIDI_SYSEX,
    VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE",
    AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE",
    SENSOR = "TYPE_SENSOR",
}
export enum ContextMenuSourceType {
    NONE,
    None = NONE,
    MOUSE = 1,
    Mouse = MOUSE,
    LONG_PRESS = 2,
    LongPress = LONG_PRESS,
}
export enum ContextMenuMediaType {
    NONE,
    None = NONE,
    IMAGE = 1,
    Image = IMAGE,
}
export enum ContextMenuInputFieldType {
    NONE,
    None = NONE,
    PLAIN_TEXT = 1,
    PlainText = PLAIN_TEXT,
    PASSWORD = 2,
    Password = PASSWORD,
    NUMBER = 3,
    Number = NUMBER,
    TELEPHONE = 4,
    Telephone = TELEPHONE,
    OTHER = 5,
    Other = OTHER,
}
export enum NativeEmbedStatus {
    CREATE,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4,
}
export enum ContextMenuEditStateFlags {
    NONE,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 4,
    CAN_SELECT_ALL = 8,
}
export enum WebNavigationType {
    UNKNOWN,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5,
}
export enum RenderMode {
    ASYNC_RENDER,
    SYNC_RENDER = 1,
}
export enum ViewportFit {
    AUTO,
    CONTAINS = 1,
    COVER = 2,
}
export enum WebKeyboardAvoidMode {
    RESIZE_VISUAL,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2,
}
export enum WebElementType {
    IMAGE = 1,
}
export enum WebResponseType {
    LONG_PRESS = 1,
}
export enum SideBarContainerType {
    EMBED,
    Embed = EMBED,
    OVERLAY = 1,
    Overlay = OVERLAY,
    AUTO = 2,
}
export enum SideBarPosition {
    START,
    Start = START,
    END = 1,
    End = END,
}
export enum WaterFlowLayoutMode {
    ALWAYS_TOP_DOWN,
    SLIDING_WINDOW = 1,
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1,
}
export enum StyledStringKey {
    FONT,
    DECORATION = 1,
    BASELINE_OFFSET = 2,
    LETTER_SPACING = 3,
    TEXT_SHADOW = 4,
    LINE_HEIGHT = 5,
    BACKGROUND_COLOR = 6,
    URL = 7,
    GESTURE = 100,
    PARAGRAPH_STYLE = 200,
    IMAGE = 300,
    CUSTOM_SPAN = 400,
    USER_DATA = 500,
}
Object.assign(globalThis, {
    PointerStyle: PointerStyle,
    RectWidthStyle: RectWidthStyle,
    RectHeightStyle: RectHeightStyle,
    LengthUnit: LengthUnit,
    PerfMonitorActionType: PerfMonitorActionType,
    PerfMonitorSourceType: PerfMonitorSourceType,
    EffectDirection: EffectDirection,
    EffectScope: EffectScope,
    DialogAlignment: DialogAlignment,
    DialogButtonDirection: DialogButtonDirection,
    IndexerAlign: IndexerAlign,
    BadgePosition: BadgePosition,
    ButtonType: ButtonType,
    ButtonStyleMode: ButtonStyleMode,
    ButtonRole: ButtonRole,
    ControlSize: ControlSize,
    CalendarAlign: CalendarAlign,
    SelectStatus: SelectStatus,
    FinishCallbackType: FinishCallbackType,
    TouchTestStrategy: TouchTestStrategy,
    TransitionHierarchyStrategy: TransitionHierarchyStrategy,
    ChainStyle: ChainStyle,
    TransitionEdge: TransitionEdge,
    EffectType: EffectType,
    PreDragStatus: PreDragStatus,
    SourceType: SourceType,
    SourceTool: SourceTool,
    RepeatMode: RepeatMode,
    BlurStyle: BlurStyle,
    BlurStyleActivePolicy: BlurStyleActivePolicy,
    ThemeColorMode: ThemeColorMode,
    AdaptiveColor: AdaptiveColor,
    ModalTransition: ModalTransition,
    ShadowType: ShadowType,
    ShadowStyle: ShadowStyle,
    SafeAreaType: SafeAreaType,
    SafeAreaEdge: SafeAreaEdge,
    LayoutSafeAreaType: LayoutSafeAreaType,
    LayoutSafeAreaEdge: LayoutSafeAreaEdge,
    SheetSize: SheetSize,
    DragBehavior: DragBehavior,
    DragResult: DragResult,
    BlendMode: BlendMode,
    BlendApplyType: BlendApplyType,
    SheetType: SheetType,
    SheetMode: SheetMode,
    ScrollSizeMode: ScrollSizeMode,
    SheetKeyboardAvoidMode: SheetKeyboardAvoidMode,
    DismissReason: DismissReason,
    MenuPreviewMode: MenuPreviewMode,
    OutlineStyle: OutlineStyle,
    DragPreviewMode: DragPreviewMode,
    MenuPolicy: MenuPolicy,
    ContentClipMode: ContentClipMode,
    KeyboardAvoidMode: KeyboardAvoidMode,
    HoverModeAreaType: HoverModeAreaType,
    ModelType: ModelType,
    DataPanelType: DataPanelType,
    CheckBoxShape: CheckBoxShape,
    Color: Color,
    ColoringStrategy: ColoringStrategy,
    ImageFit: ImageFit,
    BorderStyle: BorderStyle,
    LineJoinStyle: LineJoinStyle,
    TouchType: TouchType,
    MouseButton: MouseButton,
    MouseAction: MouseAction,
    AnimationStatus: AnimationStatus,
    Curve: Curve,
    FillMode: FillMode,
    PlayMode: PlayMode,
    KeyType: KeyType,
    KeySource: KeySource,
    Edge: Edge,
    Week: Week,
    Direction: Direction,
    BarState: BarState,
    EdgeEffect: EdgeEffect,
    Alignment: Alignment,
    TransitionType: TransitionType,
    RelateType: RelateType,
    Visibility: Visibility,
    LineCapStyle: LineCapStyle,
    Axis: Axis,
    HorizontalAlign: HorizontalAlign,
    FlexAlign: FlexAlign,
    ItemAlign: ItemAlign,
    FlexDirection: FlexDirection,
    PixelRoundCalcPolicy: PixelRoundCalcPolicy,
    FlexWrap: FlexWrap,
    VerticalAlign: VerticalAlign,
    ImageRepeat: ImageRepeat,
    ImageSize: ImageSize,
    GradientDirection: GradientDirection,
    SharedTransitionEffectType: SharedTransitionEffectType,
    FontStyle: FontStyle,
    FontWeight: FontWeight,
    TextAlign: TextAlign,
    TextOverflow: TextOverflow,
    TextDecorationType: TextDecorationType,
    TextCase: TextCase,
    TextHeightAdaptivePolicy: TextHeightAdaptivePolicy,
    ResponseType: ResponseType,
    HoverEffect: HoverEffect,
    Placement: Placement,
    ArrowPointPosition: ArrowPointPosition,
    CopyOptions: CopyOptions,
    HitTestMode: HitTestMode,
    TitleHeight: TitleHeight,
    ModifierKey: ModifierKey,
    FunctionKey: FunctionKey,
    ImageSpanAlignment: ImageSpanAlignment,
    ObscuredReasons: ObscuredReasons,
    TextContentStyle: TextContentStyle,
    ClickEffectLevel: ClickEffectLevel,
    XComponentType: XComponentType,
    NestedScrollMode: NestedScrollMode,
    ScrollSource: ScrollSource,
    RenderFit: RenderFit,
    DialogButtonStyle: DialogButtonStyle,
    WordBreak: WordBreak,
    LineBreakStrategy: LineBreakStrategy,
    EllipsisMode: EllipsisMode,
    OptionWidthMode: OptionWidthMode,
    IlluminatedType: IlluminatedType,
    FoldStatus: FoldStatus,
    AppRotation: AppRotation,
    EmbeddedType: EmbeddedType,
    MarqueeUpdateStrategy: MarqueeUpdateStrategy,
    TextDecorationStyle: TextDecorationStyle,
    TextSelectableMode: TextSelectableMode,
    AccessibilityHoverType: AccessibilityHoverType,
    WidthBreakpoint: WidthBreakpoint,
    HeightBreakpoint: HeightBreakpoint,
    FocusPriority: FocusPriority,
    FormDimension: FormDimension,
    FormRenderingMode: FormRenderingMode,
    FormShape: FormShape,
    PanDirection: PanDirection,
    SwipeDirection: SwipeDirection,
    GestureMode: GestureMode,
    GestureMask: GestureMask,
    GestureJudgeResult: GestureJudgeResult,
    GestureControl: GestureControl,
    GesturePriority: GesturePriority,
    GestureRecognizerState: GestureRecognizerState,
    GridDirection: GridDirection,
    GridItemAlignment: GridItemAlignment,
    GridItemStyle: GridItemStyle,
    SizeType: SizeType,
    BreakpointsReference: BreakpointsReference,
    GridRowDirection: GridRowDirection,
    ImageRenderMode: ImageRenderMode,
    ImageContent: ImageContent,
    DynamicRangeMode: DynamicRangeMode,
    ImageInterpolation: ImageInterpolation,
    ImageAnalyzerType: ImageAnalyzerType,
    DataOperationType: DataOperationType,
    ScrollState: ScrollState,
    ListItemAlign: ListItemAlign,
    ListItemGroupArea: ListItemGroupArea,
    StickyStyle: StickyStyle,
    ChainEdgeEffect: ChainEdgeEffect,
    ScrollSnapAlign: ScrollSnapAlign,
    Sticky: Sticky,
    EditMode: EditMode,
    SwipeEdgeEffect: SwipeEdgeEffect,
    SwipeActionState: SwipeActionState,
    ListItemStyle: ListItemStyle,
    ListItemGroupStyle: ListItemGroupStyle,
    LoadingProgressStyle: LoadingProgressStyle,
    LocationIconStyle: LocationIconStyle,
    LocationDescription: LocationDescription,
    LocationButtonOnClickResult: LocationButtonOnClickResult,
    SubMenuExpandingMode: SubMenuExpandingMode,
    NavigationSystemTransitionType: NavigationSystemTransitionType,
    NavDestinationMode: NavDestinationMode,
    NavRouteMode: NavRouteMode,
    NavigationMode: NavigationMode,
    NavBarPosition: NavBarPosition,
    NavigationTitleMode: NavigationTitleMode,
    LaunchMode: LaunchMode,
    ToolbarItemStatus: ToolbarItemStatus,
    NavigationOperation: NavigationOperation,
    BarStyle: BarStyle,
    NavigationType: NavigationType,
    RouteType: RouteType,
    SlideEffect: SlideEffect,
    PanelMode: PanelMode,
    PanelType: PanelType,
    PanelHeight: PanelHeight,
    ParticleType: ParticleType,
    ParticleEmitterShape: ParticleEmitterShape,
    DistributionType: DistributionType,
    ParticleUpdater: ParticleUpdater,
    DisturbanceFieldShape: DisturbanceFieldShape,
    PasteIconStyle: PasteIconStyle,
    PasteDescription: PasteDescription,
    PasteButtonOnClickResult: PasteButtonOnClickResult,
    PatternLockChallengeResult: PatternLockChallengeResult,
    ProgressType: ProgressType,
    ProgressStatus: ProgressStatus,
    ProgressStyle: ProgressStyle,
    RadioIndicatorType: RadioIndicatorType,
    RefreshStatus: RefreshStatus,
    BarrierDirection: BarrierDirection,
    LocalizedBarrierDirection: LocalizedBarrierDirection,
    RichEditorDeleteDirection: RichEditorDeleteDirection,
    RichEditorSpanType: RichEditorSpanType,
    RichEditorResponseType: RichEditorResponseType,
    SaveIconStyle: SaveIconStyle,
    SaveDescription: SaveDescription,
    SaveButtonOnClickResult: SaveButtonOnClickResult,
    ScrollDirection: ScrollDirection,
    ScrollAlign: ScrollAlign,
    ScrollBarDirection: ScrollBarDirection,
    CancelButtonStyle: CancelButtonStyle,
    SearchType: SearchType,
    SecurityComponentLayoutDirection: SecurityComponentLayoutDirection,
    ArrowPosition: ArrowPosition,
    MenuAlignType: MenuAlignType,
    SliderStyle: SliderStyle,
    SliderChangeMode: SliderChangeMode,
    SliderInteraction: SliderInteraction,
    SliderBlockType: SliderBlockType,
    ColorMode: ColorMode,
    LayoutDirection: LayoutDirection,
    ItemState: ItemState,
    SwiperDisplayMode: SwiperDisplayMode,
    SwiperNestedScrollMode: SwiperNestedScrollMode,
    SymbolRenderingStrategy: SymbolRenderingStrategy,
    SymbolEffectStrategy: SymbolEffectStrategy,
    EffectFillStyle: EffectFillStyle,
    BarMode: BarMode,
    AnimationMode: AnimationMode,
    BarPosition: BarPosition,
    LayoutStyle: LayoutStyle,
    SelectedMode: SelectedMode,
    LayoutMode: LayoutMode,
    TextSpanType: TextSpanType,
    TextResponseType: TextResponseType,
    TextAreaType: TextAreaType,
    ContentType: ContentType,
    TextDataDetectorType: TextDataDetectorType,
    TextDeleteDirection: TextDeleteDirection,
    MenuType: MenuType,
    InputType: InputType,
    EnterKeyType: EnterKeyType,
    TextInputStyle: TextInputStyle,
    TimePickerFormat: TimePickerFormat,
    ToggleType: ToggleType,
    SeekMode: SeekMode,
    PlaybackSpeed: PlaybackSpeed,
    MessageLevel: MessageLevel,
    MixedMode: MixedMode,
    HitTestType: HitTestType,
    CacheMode: CacheMode,
    OverScrollMode: OverScrollMode,
    WebDarkMode: WebDarkMode,
    WebCaptureMode: WebCaptureMode,
    ThreatType: ThreatType,
    RenderExitReason: RenderExitReason,
    SslError: SslError,
    FileSelectorMode: FileSelectorMode,
    WebLayoutMode: WebLayoutMode,
    RenderProcessNotRespondingReason: RenderProcessNotRespondingReason,
    ProtectedResourceType: ProtectedResourceType,
    ContextMenuSourceType: ContextMenuSourceType,
    ContextMenuMediaType: ContextMenuMediaType,
    ContextMenuInputFieldType: ContextMenuInputFieldType,
    NativeEmbedStatus: NativeEmbedStatus,
    ContextMenuEditStateFlags: ContextMenuEditStateFlags,
    WebNavigationType: WebNavigationType,
    RenderMode: RenderMode,
    ViewportFit: ViewportFit,
    WebKeyboardAvoidMode: WebKeyboardAvoidMode,
    WebElementType: WebElementType,
    WebResponseType: WebResponseType,
    SideBarContainerType: SideBarContainerType,
    SideBarPosition: SideBarPosition,
    WaterFlowLayoutMode: WaterFlowLayoutMode,
    DpiFollowStrategy: DpiFollowStrategy,
    StyledStringKey: StyledStringKey,
})
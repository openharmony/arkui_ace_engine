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
declare type SpringLoadingContext = import('../api/@ohos.arkui.dragController').default.SpringLoadingContext;
declare type DragSpringLoadingConfiguration = import('../api/@ohos.arkui.dragController').default.DragSpringLoadingConfiguration;
declare interface ComponentOptions {
    freezeWhenInactive: boolean;
}
declare interface InputCounterOptions {
    thresholdPercentage?: number;
    highlightBorder?: boolean;
    counterTextColor?: ColorMetrics;
    counterTextOverflowColor?: ColorMetrics;
}
declare interface TextDecorationOptions {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
declare const Component: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);
declare const ComponentV2: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);
declare interface EntryOptions {
    routeName?: string;
    storage?: LocalStorage;
    useSharedStorage?: boolean;
}
declare const Entry: ClassDecorator & ((options?: LocalStorage | EntryOptions) => ClassDecorator);
declare const Observed: ClassDecorator;
declare const ObservedV2: ClassDecorator;
declare const Preview: ClassDecorator & ((value: PreviewParams) => ClassDecorator);
declare const Require: PropertyDecorator;
declare const BuilderParam: PropertyDecorator;
declare const Local: PropertyDecorator;
declare const Param: PropertyDecorator;
declare const Once: PropertyDecorator;
declare const Event: PropertyDecorator;
declare const State: PropertyDecorator;
declare const Track: PropertyDecorator;
declare const Trace: PropertyDecorator;
declare const Prop: PropertyDecorator;
declare const Link: PropertyDecorator;
declare const ObjectLink: PropertyDecorator;
declare interface ProvideOptions {
    allowOverride?: string;
}
declare const Provide: PropertyDecorator & ((value: string | ProvideOptions) => PropertyDecorator);
declare const Provider: (aliasName?: string) => PropertyDecorator;
declare type EnvDecorator = (value: SystemProperties) => PropertyDecorator;
declare const Env: EnvDecorator;
declare enum SystemProperties {
    BREAK_POINT = 'system.arkui.breakpoint',
    WINDOW_AVOID_AREA = 'system.window.avoidarea',
    WINDOW_AVOID_AREA_PX = 'system.window.avoidarea.px',
    WINDOW_SIZE = 'system.window.size',
    WINDOW_SIZE_PX = 'system.window.size.px'
}
;
declare const Consume: PropertyDecorator & ((value: string) => PropertyDecorator);
declare const Consumer: (aliasName?: string) => PropertyDecorator;
declare const Computed: MethodDecorator;
declare const StorageProp: (value: string) => PropertyDecorator;
declare const StorageLink: (value: string) => PropertyDecorator;
declare const Watch: (value: string) => PropertyDecorator;
declare const Builder: MethodDecorator;
declare const LocalBuilder: MethodDecorator;
declare const Styles: MethodDecorator;
declare const Extend: MethodDecorator & ((value: any) => MethodDecorator);
declare const AnimatableExtend: MethodDecorator & ((value: Object) => MethodDecorator);
declare const Monitor: MonitorDecorator;
declare type MonitorDecorator = (value: string, ...args: string[]) => MethodDecorator;
declare interface IMonitor {
    dirty: Array<string>;
    value<T>(path?: string): IMonitorValue<T> | undefined;
}
declare interface IMonitorValue<T> {
    before: T;
    now: T;
    path: string;
}
declare const SyncMonitor: MonitorDecorator;
declare interface AnimatableArithmetic<T> {
    plus(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    subtract(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    multiply(scale: number): AnimatableArithmetic<T>;
    equals(rhs: AnimatableArithmetic<T>): boolean;
}
declare const Concurrent: MethodDecorator;
declare const Sendable: ClassDecorator;
declare const CustomDialog: ClassDecorator;
declare const LocalStorageLink: (value: string) => PropertyDecorator;
declare const LocalStorageProp: (value: string) => PropertyDecorator;
declare function getContext(component?: Object): Context;
declare const Reusable: ClassDecorator;
declare const ReusableV2: ClassDecorator;
declare type ReuseIdCallback = () => string;
declare interface ReuseOptions {
    reuseId?: ReuseIdCallback;
}
declare type Context = import('../api/application/Context').default;
declare function postCardAction(component: Object, action: Object): void;
declare interface Configuration {
    readonly colorMode: string;
    readonly fontScale: number;
}
declare interface Rectangle {
    x?: Length;
    y?: Length;
    width?: Length;
    height?: Length;
}
declare interface ResponseRegion {
    tool?: ResponseRegionSupportedTool;
    x?: LengthMetrics;
    y?: LengthMetrics;
    width?: LengthMetrics | string;
    height?: LengthMetrics | string;
}
declare interface ExpectedFrameRateRange {
    min: number;
    max: number;
    expected: number;
}
declare function $r(value: string, ...params: any[]): Resource;
declare function $rawfile(value: string): Resource;
declare enum AccessibilitySamePageMode {
    SEMI_SILENT = 0,
    FULL_SILENT = 1
}
declare enum AccessibilityRoleType {
    ACTION_SHEET = 0,
    ALERT_DIALOG = 1,
    INDEXER_COMPONENT = 2,
    BADGE_COMPONENT = 3,
    BLANK = 4,
    BUTTON = 5,
    BACK_BUTTON = 6,
    SHEET_DRAG_BAR = 7,
    CALENDAR_PICKER = 8,
    CALENDAR = 9,
    CANVAS = 10,
    CANVAS_GRADIENT = 11,
    CANVAS_PATTERN = 12,
    CHECKBOX = 13,
    CHECKBOX_GROUP = 14,
    CIRCLE = 15,
    COLUMN_SPLIT = 16,
    COLUMN = 17,
    CANVAS_RENDERING_CONTEXT_2D = 18,
    CHART = 19,
    COUNTER = 20,
    CONTAINER_MODAL = 21,
    DATA_PANEL = 22,
    DATE_PICKER = 23,
    DIALOG = 24,
    DIVIDER = 25,
    DRAG_BAR = 26,
    EFFECT_COMPONENT = 27,
    ELLIPSE = 28,
    FLEX = 29,
    FLOW_ITEM = 30,
    FORM_COMPONENT = 31,
    FORM_LINK = 32,
    GAUGE = 33,
    GRID = 34,
    GRID_COL = 35,
    GRID_CONTAINER = 36,
    GRID_ITEM = 37,
    GRID_ROW = 38,
    HYPERLINK = 39,
    IMAGE = 40,
    IMAGE_ANIMATOR = 41,
    IMAGE_BITMAP = 42,
    IMAGE_DATA = 43,
    IMAGE_SPAN = 44,
    LABEL = 45,
    LINE = 46,
    LIST = 47,
    LIST_ITEM = 48,
    LIST_ITEM_GROUP = 49,
    LOADING_PROGRESS = 50,
    MARQUEE = 51,
    MATRIX2D = 52,
    MENU = 53,
    MENU_ITEM = 54,
    MENU_ITEM_GROUP = 55,
    NAV_DESTINATION = 56,
    NAV_ROUTER = 57,
    NAVIGATION = 58,
    NAVIGATION_BAR = 59,
    NAVIGATION_MENU = 60,
    NAVIGATOR = 61,
    OFFSCREEN_CANVAS = 62,
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    OPTION = 64,
    PANEL = 65,
    PAPER_PAGE = 66,
    PATH = 67,
    PATH2D = 68,
    PATTERN_LOCK = 69,
    PICKER = 70,
    PICKER_VIEW = 71,
    PLUGIN_COMPONENT = 72,
    POLYGON = 73,
    POLYLINE = 74,
    POPUP = 75,
    PROGRESS = 76,
    QRCODE = 77,
    RADIO = 78,
    RATING = 79,
    RECT = 80,
    REFRESH = 81,
    RELATIVE_CONTAINER = 82,
    REMOTE_WINDOW = 83,
    RICH_EDITOR = 84,
    RICH_TEXT = 85,
    ROLE_PAGER = 86,
    ROW = 87,
    ROW_SPLIT = 88,
    SCROLL = 89,
    SCROLL_BAR = 90,
    SEARCH = 91,
    SEARCH_FIELD = 92,
    SELECT = 93,
    SHAPE = 94,
    SIDEBAR_CONTAINER = 95,
    SLIDER = 96,
    SPAN = 97,
    STACK = 98,
    STEPPER = 99,
    STEPPER_ITEM = 100,
    SWIPER = 101,
    SWIPER_INDICATOR = 102,
    SWITCH = 103,
    SYMBOL_GLYPH = 104,
    TAB_CONTENT = 105,
    TAB_BAR = 106,
    TABS = 107,
    TEXT = 108,
    TEXT_CLOCK = 109,
    TEXT_ENTRY = 110,
    TEXT_INPUT = 111,
    TEXT_PICKER = 112,
    TEXT_TIMER = 113,
    TEXT_AREA = 114,
    TEXT_FIELD = 115,
    TIME_PICKER = 116,
    TITLE_BAR = 117,
    TOGGLER = 118,
    UI_EXTENSION_COMPONENT = 119,
    VIDEO = 120,
    WATER_FLOW = 121,
    WEB = 122,
    XCOMPONENT = 123,
    ROLE_NONE = 124
}
declare type AccessibilityFocusCallback = (isFocus: boolean) => void;
declare enum AccessibilityAction {
    UNDEFINED_ACTION = 0,
    ACCESSIBILITY_CLICK = 1
}
declare enum AccessibilityActionInterceptResult {
    ACTION_INTERCEPT = 0,
    ACTION_CONTINUE = 1,
    ACTION_RISE = 2
}
declare type AccessibilityActionInterceptCallback = (action: AccessibilityAction) => AccessibilityActionInterceptResult;
declare enum FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1
}
declare enum TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION = 1,
    FORWARD = 2
}
declare interface AnimateParam {
    duration?: number;
    tempo?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    iterations?: number;
    playMode?: PlayMode;
    onFinish?: () => void;
    finishCallbackType?: FinishCallbackType;
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
interface ICurve {
    interpolate(fraction: number): number;
}
declare interface MotionPathOptions {
    path: string;
    from?: number;
    to?: number;
    rotatable?: boolean;
}
declare interface sharedTransitionOptions {
    duration?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    motionPath?: MotionPathOptions;
    zIndex?: number;
    type?: SharedTransitionEffectType;
}
declare interface GeometryTransitionOptions {
    follow?: boolean;
    hierarchyStrategy?: TransitionHierarchyStrategy;
}
declare interface LinearGradientOptions {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[
        ResourceColor,
        number
    ]>;
    repeating?: boolean;
}
declare interface SweepGradientOptions {
    center: [
        Length,
        Length
    ];
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<[
        ResourceColor,
        number
    ]>;
    metricsColors?: Array<[
        ColorMetrics,
        number
    ]>;
    repeating?: boolean;
}
declare interface RadialGradientOptions {
    center: [
        Length,
        Length
    ];
    radius: Length;
    colors: Array<[
        ResourceColor,
        number
    ]>;
    repeating?: boolean;
}
declare enum TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE = 1
}
declare interface TranslateOptions {
    x?: number | string;
    y?: number | string;
    z?: number | string;
}
declare interface ScaleOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
}
declare interface VerticalAlignParam {
    anchor: string;
    align: VerticalAlign;
}
declare interface HorizontalAlignParam {
    anchor: string;
    align: HorizontalAlign;
}
declare interface AlignRuleOption {
    left?: HorizontalAlignParam;
    right?: HorizontalAlignParam;
    middle?: HorizontalAlignParam;
    top?: VerticalAlignParam;
    bottom?: VerticalAlignParam;
    center?: VerticalAlignParam;
    bias?: Bias;
}
declare interface LocalizedHorizontalAlignParam {
    anchor: string;
    align: HorizontalAlign;
}
declare interface LocalizedVerticalAlignParam {
    anchor: string;
    align: VerticalAlign;
}
declare interface LocalizedAlignRuleOptions {
    start?: LocalizedHorizontalAlignParam;
    end?: LocalizedHorizontalAlignParam;
    middle?: LocalizedHorizontalAlignParam;
    top?: LocalizedVerticalAlignParam;
    bottom?: LocalizedVerticalAlignParam;
    center?: LocalizedVerticalAlignParam;
    bias?: Bias;
}
declare enum ChainStyle {
    SPREAD,
    SPREAD_INSIDE,
    PACKED
}
declare interface RotateOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
    centerZ?: number;
    perspective?: number;
    angle: number | string;
}
declare interface RotateAngleOptions {
    angleX?: number | string;
    angleY?: number | string;
    angleZ?: number | string;
    centerX?: number | string;
    centerY?: number | string;
    centerZ?: number;
    perspective?: number;
}
declare interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
declare enum TransitionEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
declare type TransitionEffects = {
    identity: undefined;
    opacity: number;
    slideSwitch: undefined;
    move: TransitionEdge;
    translate: TranslateOptions;
    rotate: RotateOptions;
    scale: ScaleOptions;
    asymmetric: {
        appear: TransitionEffect;
        disappear: TransitionEffect;
    };
};
declare class DrawModifier {
    drawBehind?(drawContext: DrawContext): void;
    drawContent?(drawContext: DrawContext): void;
    drawFront?(drawContext: DrawContext): void;
}
declare class TransitionEffect<Type extends keyof TransitionEffects = keyof TransitionEffects, Effect extends TransitionEffects[Type] = TransitionEffects[Type]> {
    static readonly IDENTITY: TransitionEffect<"identity">;
    static readonly OPACITY: TransitionEffect<"opacity">;
    static readonly SLIDE: TransitionEffect<"asymmetric", {
        appear: TransitionEffect<"move", TransitionEdge>;
        disappear: TransitionEffect<"move", TransitionEdge>;
    }>;
    static readonly SLIDE_SWITCH: TransitionEffect<"slideSwitch">;
    static translate(options: TranslateOptions): TransitionEffect<"translate">;
    static rotate(options: RotateOptions): TransitionEffect<"rotate">;
    static scale(options: ScaleOptions): TransitionEffect<"scale">;
    static opacity(alpha: number): TransitionEffect<"opacity">;
    static move(edge: TransitionEdge): TransitionEffect<"move">;
    static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect<"asymmetric">;
    constructor(type: Type, effect: Effect);
}
interface PreviewParams {
    title?: string;
    width?: number;
    height?: number;
    locale?: string;
    colorMode?: string;
    deviceType?: string;
    dpi?: number;
    orientation?: string;
    roundScreen?: boolean;
}
declare interface ItemDragInfo {
    x: number;
    y: number;
}
declare enum EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1
}
declare enum PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6,
    PREPARING_FOR_DRAG_DETECTION = 7
}
declare interface DragItemInfo {
    pixelMap?: PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
declare function animateTo(value: AnimateParam, event: () => void): void;
declare function animateToImmediately(value: AnimateParam, event: () => void): void;
declare function vp2px(value: number): number;
declare function px2vp(value: number): number;
declare function fp2px(value: number): number;
declare function px2fp(value: number): number;
declare function lpx2px(value: number): number;
declare function px2lpx(value: number): number;
declare namespace focusControl {
    function requestFocus(value: string): boolean;
}
declare type PointerStyle = import('../api/@ohos.multimodalInput.pointer').default.PointerStyle;
declare namespace cursorControl {
    function setCursor(value: PointerStyle): void;
    function restoreDefault(): void;
}
declare interface EventTarget {
    area: Area;
    id?: string;
}
declare enum SourceType {
    Unknown,
    Mouse,
    TouchScreen,
    KEY = 4,
    JOYSTICK = 5
}
declare enum SourceTool {
    Unknown,
    Finger,
    Pen,
    MOUSE,
    TOUCHPAD,
    JOYSTICK
}
declare enum RepeatMode {
    Repeat,
    Stretch,
    Round,
    Space
}
declare enum BlurStyle {
    Thin,
    Regular,
    Thick,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12
}
declare enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2
}
declare enum ThemeColorMode {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2
}
declare enum AdaptiveColor {
    DEFAULT = 0,
    AVERAGE = 1
}
declare enum ModalTransition {
    DEFAULT = 0,
    NONE = 1,
    ALPHA = 2
}
declare interface BackgroundBlurStyleOptions extends BlurStyleOptions {
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
declare interface ForegroundBlurStyleOptions extends BlurStyleOptions {
}
declare interface BlurOptions {
    grayscale: [
        number,
        number
    ];
}
declare interface SystemAdaptiveOptions {
    disableSystemAdaptation?: boolean;
}
declare interface BlurStyleOptions {
    colorMode?: ThemeColorMode;
    adaptiveColor?: AdaptiveColor;
    scale?: number;
    blurOptions?: BlurOptions;
}
declare interface BackgroundEffectOptions {
    radius: number;
    saturation?: number;
    brightness?: number;
    color?: ResourceColor;
    adaptiveColor?: AdaptiveColor;
    blurOptions?: BlurOptions;
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
declare interface ForegroundEffectOptions {
    radius: number;
}
declare interface PickerTextStyle {
    color?: ResourceColor;
    font?: Font;
}
declare interface PickerDialogButtonStyle {
    type?: ButtonType;
    style?: ButtonStyleMode;
    role?: ButtonRole;
    fontSize?: Length;
    fontColor?: ResourceColor;
    fontWeight?: FontWeight | number | string;
    fontStyle?: FontStyle;
    fontFamily?: Resource | string;
    backgroundColor?: ResourceColor;
    borderRadius?: Length | BorderRadiuses;
    primary?: boolean;
}
declare enum ShadowType {
    COLOR = 0,
    BLUR = 1
}
declare interface ShadowOptions {
    radius: number | Resource;
    type?: ShadowType;
    color?: Color | string | Resource | ColoringStrategy;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
    fill?: boolean;
}
declare enum ShadowStyle {
    OUTER_DEFAULT_XS = 0,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5
}
declare interface MultiShadowOptions {
    radius?: number | Resource;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
}
declare enum SafeAreaType {
    SYSTEM = 0,
    CUTOUT = 1,
    KEYBOARD = 2
}
declare enum SafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
declare enum LayoutSafeAreaType {
    SYSTEM = 0
}
declare enum LayoutSafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3,
    VERTICAL = 4,
    HORIZONTAL = 5,
    ALL = 6
}
declare enum SheetSize {
    MEDIUM = 0,
    LARGE = 1,
    FIT_CONTENT = 2
}
declare interface BaseEvent {
    target: EventTarget;
    timestamp: number;
    source: SourceType;
    axisHorizontal?: number;
    axisVertical?: number;
    axisPinch?: number;
    pressure: number;
    tiltX: number;
    tiltY: number;
    rollAngle?: number;
    sourceTool: SourceTool;
    getModifierKeyState?(keys: Array<string>): boolean;
    deviceId?: number;
    targetDisplayId?: number;
}
declare interface BorderImageOption {
    slice?: Length | EdgeWidths | LocalizedEdgeWidths;
    repeat?: RepeatMode;
    source?: string | Resource | LinearGradient;
    width?: Length | EdgeWidths | LocalizedEdgeWidths;
    outset?: Length | EdgeWidths | LocalizedEdgeWidths;
    fill?: boolean;
}
declare class LayoutPolicy {
    static readonly matchParent: LayoutPolicy;
    static readonly wrapContent: LayoutPolicy;
    static readonly fixAtIdealSize: LayoutPolicy;
}
declare interface ClickEvent extends BaseEvent {
    globalDisplayX?: number;
    globalDisplayY?: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
    hand?: InteractionHand;
    preventDefault: () => void;
}
declare interface HoverEvent extends BaseEvent {
    x?: number;
    y?: number;
    windowX?: number;
    windowY?: number;
    displayX?: number;
    displayY?: number;
    globalDisplayX?: number;
    globalDisplayY?: number;
    stopPropagation: () => void;
}
declare interface MouseEvent extends BaseEvent {
    button: MouseButton;
    action: MouseAction;
    globalDisplayX?: number;
    globalDisplayY?: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
    stopPropagation: () => void;
    rawDeltaX?: number;
    rawDeltaY?: number;
    pressedButtons?: MouseButton[];
    eventHandleId?: number;
}
declare interface AccessibilityHoverEvent extends BaseEvent {
    type: AccessibilityHoverType;
    x: number;
    y: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    globalDisplayX?: number;
    globalDisplayY?: number;
}
declare interface TouchObject {
    type: TouchType;
    id: number;
    globalDisplayX?: number;
    globalDisplayY?: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
    hand?: InteractionHand;
    pressedTime?: number;
    pressure?: number;
    width?: number;
    height?: number;
}
declare interface HistoricalPoint {
    touchObject: TouchObject;
    size: number;
    force: number;
    timestamp: number;
}
declare interface TouchEvent extends BaseEvent {
    type: TouchType;
    touches: TouchObject[];
    changedTouches: TouchObject[];
    stopPropagation: () => void;
    getHistoricalPoints(): Array<HistoricalPoint>;
    preventDefault: () => void;
    eventHandleId?: number;
}
declare interface AxisEvent extends BaseEvent {
    action: AxisAction;
    globalDisplayX?: number;
    globalDisplayY?: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    x: number;
    y: number;
    scrollStep?: number;
    eventHandleId?: number;
    propagation: Callback<void>;
    getHorizontalAxisValue(): number;
    getVerticalAxisValue(): number;
    getPinchAxisScaleValue(): number;
    hasAxis(axisType: AxisType): boolean;
}
declare type SizeChangeCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
declare type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>, touchRecognizers?: Array<TouchRecognizer>) => GestureJudgeResult;
declare type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
declare type TransitionFinishCallback = (transitionIn: boolean) => void;
declare type OnNeedSoftkeyboardCallback = () => boolean;
declare type TouchTestDoneCallback = (event: BaseGestureEvent, recognizers: Array<GestureRecognizer>) => void;
declare type PixelMap = import('../api/@ohos.multimedia.image').default.PixelMap;
declare enum DragBehavior {
    COPY = 0,
    MOVE = 1
}
declare type UnifiedData = import('../api/@ohos.data.unifiedDataChannel').default.UnifiedData;
declare type Summary = import('../api/@ohos.data.unifiedDataChannel').default.Summary;
declare type UniformDataType = import('../api/@ohos.data.uniformTypeDescriptor').default.UniformDataType;
declare type DataSyncOptions = import('../api/@ohos.data.unifiedDataChannel').default.GetDataParams;
declare type DataLoadParams = import('../api/@ohos.data.unifiedDataChannel').default.DataLoadParams;
declare enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4
}
declare enum BlendMode {
    NONE = 0,
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
    LUMINOSITY = 29
}
declare enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1,
    OFFSCREEN_WITH_BACKGROUND = 2
}
declare interface DragEvent {
    getGlobalDisplayX(): number;
    getGlobalDisplayY(): number;
    getDisplayX(): number;
    getDisplayY(): number;
    getWindowX(): number;
    getWindowY(): number;
    getX(): number;
    getY(): number;
    dragBehavior: DragBehavior;
    useCustomDropAnimation: boolean;
    setData(unifiedData: UnifiedData): void;
    getData(): UnifiedData;
    getSummary(): Summary;
    setResult(dragResult: DragResult): void;
    getResult(): DragResult;
    getPreviewRect(): Rectangle;
    getVelocityX(): number;
    getVelocityY(): number;
    getVelocity(): number;
    getModifierKeyState?(keys: Array<string>): boolean;
    executeDropAnimation(customDropAnimation: Callback<void>): void;
    startDataLoading(options: DataSyncOptions): string;
    getDragSource(): string;
    isRemote(): boolean;
    getDisplayId(): number;
    setDataLoadParams(dataLoadParams: DataLoadParams): void;
    enableInternalDropAnimation(configuration: string): void;
}
declare type OnDragEventCallback = (event: DragEvent, extraParams?: string) => void;
declare interface DropOptions {
    disableDataPrefetch?: boolean;
}
declare type IntentionCode = import('../api/@ohos.multimodalInput.intentionCode').IntentionCode;
declare interface KeyEvent {
    type: KeyType;
    keyCode: number;
    keyText: string;
    keySource: KeySource;
    deviceId: number;
    metaKey: number;
    timestamp: number;
    stopPropagation: () => void;
    intentionCode: IntentionCode;
    getModifierKeyState?(keys: Array<string>): boolean;
    unicode?: number;
    isNumLockOn?: boolean;
    isCapsLockOn?: boolean;
    isScrollLockOn?: boolean;
}
declare interface FocusAxisEvent extends BaseEvent {
    axisMap: Map<AxisModel, number>;
    stopPropagation: Callback<void>;
}
declare interface CrownEvent {
    timestamp: number;
    angularVelocity: number;
    degree: number;
    action: CrownAction;
    stopPropagation: Callback<void>;
}
declare interface BindOptions {
    backgroundColor?: ResourceColor;
    onAppear?: () => void;
    onDisappear?: () => void;
    onWillAppear?: () => void;
    onWillDisappear?: () => void;
}
declare interface DismissContentCoverAction {
    dismiss: Callback<void>;
    reason: DismissReason;
}
declare interface ContentCoverOptions extends BindOptions {
    modalTransition?: ModalTransition;
    onWillDismiss?: Callback<DismissContentCoverAction>;
    transition?: TransitionEffect;
    enableSafeArea?: boolean;
}
declare interface SheetTitleOptions {
    title: ResourceStr;
    subtitle?: ResourceStr;
}
declare enum SheetType {
    BOTTOM = 0,
    CENTER = 1,
    POPUP = 2,
    SIDE = 3,
    CONTENT_COVER = 4
}
declare enum SheetMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
declare enum ScrollSizeMode {
    FOLLOW_DETENT = 0,
    CONTINUOUS = 1
}
declare enum SheetKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3,
    POPUP_SHEET = 4
}
declare interface SheetDismiss {
    dismiss: () => void;
}
declare interface DismissSheetAction {
    dismiss: Callback<void>;
    reason: DismissReason;
}
declare interface SpringBackAction {
    springBack: Callback<void>;
}
declare interface SheetOptions extends BindOptions {
    height?: SheetSize | Length;
    dragBar?: boolean;
    enableFloatingDragBar?: boolean;
    radiusRenderStrategy?: RenderStrategy;
    modalTransition?: ModalTransition;
    maskColor?: ResourceColor;
    detents?: [
        (SheetSize | Length),
        (SheetSize | Length)?,
        (SheetSize | Length)?
    ];
    blurStyle?: BlurStyle;
    showClose?: boolean | Resource;
    preferType?: SheetType;
    title?: SheetTitleOptions | CustomBuilder;
    shouldDismiss?: (sheetDismiss: SheetDismiss) => void;
    onWillDismiss?: Callback<DismissSheetAction>;
    onWillSpringBackWhenDismiss?: Callback<SpringBackAction>;
    enableOutsideInteractive?: boolean;
    width?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    onHeightDidChange?: Callback<number>;
    mode?: SheetMode;
    scrollSizeMode?: ScrollSizeMode;
    onDetentsDidChange?: Callback<number>;
    onWidthDidChange?: Callback<number>;
    onTypeDidChange?: Callback<SheetType>;
    uiContext?: UIContext;
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    offset?: Position;
    effectEdge?: number;
    radius?: LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses;
    detentSelection?: SheetSize | Length;
    showInSubWindow?: boolean;
    placement?: Placement;
    placementOnTarget?: boolean;
}
declare interface StateStyles {
    normal?: any;
    pressed?: any;
    disabled?: any;
    focused?: any;
    clicked?: any;
    selected?: object;
}
declare interface PopupMessageOptions {
    textColor?: ResourceColor;
    font?: Font;
}
declare enum DismissReason {
    PRESS_BACK = 0,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3,
    SLIDE = 4
}
declare interface DismissPopupAction {
    dismiss: Callback<void>;
    reason: DismissReason;
}
declare interface PopupBorderLinearGradient {
    direction?: GradientDirection;
    colors: Array<[
        ResourceColor,
        number
    ]>;
}
declare interface TipsOptions {
    appearingTime?: number;
    disappearingTime?: number;
    appearingTimeWithContinuousOperation?: number;
    disappearingTimeWithContinuousOperation?: number;
    enableArrow?: boolean;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    showAtAnchor?: TipsAnchorType;
}
declare interface PopupOptions {
    message: string;
    placementOnTop?: boolean;
    placement?: Placement;
    primaryButton?: {
        value: string;
        action: () => void;
    };
    secondaryButton?: {
        value: string;
        action: () => void;
    };
    onStateChange?: (event: {
        isVisible: boolean;
    }) => void;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | {
        color: ResourceColor;
    };
    messageOptions?: PopupMessageOptions;
    targetSpace?: Length;
    enableArrow?: boolean;
    offset?: Position;
    popupColor?: Color | string | Resource | number;
    autoCancel?: boolean;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    onWillDismiss?: boolean | Callback<DismissPopupAction>;
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
    keyboardAvoidMode?: KeyboardAvoidMode;
    avoidTarget?: AvoidanceMode;
    outlineWidth?: Dimension;
    borderWidth?: Dimension;
    outlineLinearGradient?: PopupBorderLinearGradient;
    borderLinearGradient?: PopupBorderLinearGradient;
    systemMaterial?: SystemUiMaterial;
}
declare interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    maskColor?: Color | string | Resource | number;
    popupColor?: Color | string | Resource | number;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: (event: {
        isVisible: boolean;
    }) => void;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | {
        color: ResourceColor;
    };
    targetSpace?: Length;
    offset?: Position;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    focusable?: boolean;
    transition?: TransitionEffect;
    onWillDismiss?: boolean | Callback<DismissPopupAction>;
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
    keyboardAvoidMode?: KeyboardAvoidMode;
    avoidTarget?: AvoidanceMode;
    outlineWidth?: Dimension;
    borderWidth?: Dimension;
    outlineLinearGradient?: PopupBorderLinearGradient;
    borderLinearGradient?: PopupBorderLinearGradient;
    systemMaterial?: SystemUiMaterial;
}
declare enum MenuPreviewMode {
    NONE = 0,
    IMAGE = 1
}
interface ContextMenuAnimationOptions {
    scale?: AnimationRange<number>;
    transition?: TransitionEffect;
    hoverScale?: AnimationRange<number>;
    hoverScaleInterruption?: boolean;
}
type BorderRadiusType = Length | BorderRadiuses | LocalizedBorderRadiuses;
declare enum HapticFeedbackMode {
    DISABLED = 0,
    ENABLED = 1,
    AUTO = 2
}
declare enum ModalMode {
    AUTO = 0,
    NONE = 1,
    TARGET_WINDOW = 2
}
declare interface MenuMaskType {
    color?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
}
declare enum PreviewScaleMode {
    AUTO = 0,
    CONSTANT = 1,
    MAINTAIN = 2
}
declare enum AvailableLayoutArea {
    SAFE_AREA = 0
}
declare class ContentTransitionEffect {
    static get IDENTITY(): ContentTransitionEffect;
    static get OPACITY(): ContentTransitionEffect;
}
declare enum MenuKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1
}
declare interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: MenuPreviewMode | CustomBuilder;
    previewBorderRadius?: BorderRadiusType;
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses;
    onAppear?: () => void;
    onDisappear?: () => void;
    aboutToAppear?: () => void;
    aboutToDisappear?: () => void;
    layoutRegionMargin?: Margin;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
    outlineColor?: ResourceColor | EdgeColors;
    outlineWidth?: Dimension | EdgeOutlineWidths;
    hapticFeedbackMode?: HapticFeedbackMode;
    mask?: boolean | MenuMaskType;
    modalMode?: ModalMode;
    onDidAppear?: Callback<void>;
    onDidDisappear?: Callback<void>;
    onWillAppear?: Callback<void>;
    onWillDisappear?: Callback<void>;
    previewScaleMode?: PreviewScaleMode;
    availableLayoutArea?: AvailableLayoutArea;
    anchorPosition?: Position;
    keyboardAvoidMode?: MenuKeyboardAvoidMode;
    minKeyboardAvoidDistance?: LengthMetrics;
    systemMaterial?: SystemUiMaterial;
}
declare interface MenuOptions extends ContextMenuOptions {
    title?: ResourceStr;
    showInSubWindow?: boolean;
}
declare class ProgressMask {
    constructor(value: number, total: number, color: ResourceColor);
}
declare class TouchTestInfo {
    windowX: number;
    windowY: number;
    parentX: number;
    parentY: number;
    x: number;
    y: number;
    rect: RectResult;
    id: string;
}
declare class TouchResult {
    strategy: TouchTestStrategy;
    id?: string;
}
declare interface PixelStretchEffectOptions {
    top?: Length;
    bottom?: Length;
    left?: Length;
    right?: Length;
}
declare interface ClickEffect {
    level: ClickEffectLevel;
    scale?: number;
}
declare interface FadingEdgeOptions {
    fadingEdgeLength?: LengthMetrics;
}
declare interface NestedScrollOptions {
    scrollForward: NestedScrollMode;
    scrollBackward: NestedScrollMode;
}
declare interface MenuElement {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    enabled?: boolean;
    action: () => void;
}
declare interface AttributeModifier<T> {
    applyNormalAttribute?(instance: T): void;
    applyPressedAttribute?(instance: T): void;
    applyFocusedAttribute?(instance: T): void;
    applyDisabledAttribute?(instance: T): void;
    applySelectedAttribute?(instance: T): void;
}
declare interface ContentModifier<T> {
    applyContent(): WrappedBuilder<[
        T
    ]>;
}
declare interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
}
declare enum OutlineStyle {
    SOLID = 0,
    DASHED = 1,
    DOTTED = 2
}
declare enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    ENABLE_MULTI_TILE_EFFECT = 6,
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7
}
declare enum DraggingSizeChangeEffect {
    DEFAULT = 0,
    SIZE_TRANSITION = 1,
    SIZE_CONTENT_TRANSITION = 2
}
declare enum MenuPolicy {
    DEFAULT = 0,
    HIDE = 1,
    SHOW = 2
}
declare interface DragPreviewOptions {
    mode?: DragPreviewMode | Array<DragPreviewMode>;
    modifier?: ImageModifier;
    numberBadge?: boolean | number;
    sizeChangeEffect?: DraggingSizeChangeEffect;
}
declare interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
    enableHapticFeedback?: boolean;
    enableEdgeAutoScroll?: boolean;
    isLiftingDisabled?: boolean;
}
declare interface PreviewConfiguration {
    onlyForLifting?: boolean;
    delayCreating?: boolean;
}
declare interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
declare type CircleShape = import('../api/@ohos.arkui.shape').CircleShape;
declare type EllipseShape = import('../api/@ohos.arkui.shape').EllipseShape;
declare type PathShape = import('../api/@ohos.arkui.shape').PathShape;
declare type RectShape = import('../api/@ohos.arkui.shape').RectShape;
declare type TipsMessageType = ResourceStr | StyledString;
declare type Matrix4Transit = import('../api/@ohos.matrix4').default.Matrix4Transit;
declare type SystemUiMaterial = import('../api/@ohos.arkui.uiMaterial').default.Material;
interface BackgroundImageOptions {
    syncLoad?: boolean;
    repeat?: ImageRepeat;
}
declare interface BackgroundOptions {
    align?: Alignment;
    ignoresLayoutSafeAreaEdges?: Array<LayoutSafeAreaEdge>;
}
declare class CommonMethod<T> {
    constructor();
    width(value: Length): T;
    width(widthValue: Length | LayoutPolicy): T;
    height(value: Length): T;
    height(heightValue: Length | LayoutPolicy): T;
    responseRegion(value: Array<Rectangle> | Rectangle): T;
    size(value: SizeOptions): T;
    padding(value: Padding | Length | LocalizedPadding): T;
    margin(value: Margin | Length | LocalizedMargin): T;
    backgroundColor(value: ResourceColor): T;
    backgroundColor(color: Optional<ResourceColor>): T;
    backgroundColor(color: Optional<ResourceColor | ColorMetrics>): T;
    border(value: BorderOptions): T;
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): T;
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): T;
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses, type?: RenderStrategy): T;
    onClick(event: (event: ClickEvent) => void): T;
    onClick(event: Callback<ClickEvent>, distanceThreshold: number): T;
    onHover(event: (isHover: boolean, event: HoverEvent) => void): T;
    hoverEffect(value: HoverEffect): T;
    onTouch(event: (event: TouchEvent) => void): T;
    onKeyEvent(event: (event: KeyEvent) => void): T;
    onKeyEvent(event: Callback<KeyEvent, boolean>): T;
    onAppear(event: () => void): T;
    onDisAppear(event: () => void): T;
    onAttach(callback: Callback<void>): T;
    onDetach(callback: Callback<void>): T;
    draggable(value: boolean): T;
    clip(value: boolean): T;
    clip(clip: Optional<boolean>): T;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): T;
    key(value: string): T;
    id(value: string): T;
    attributeModifier(modifier: AttributeModifier<T>): T;
}
declare class CommonAttribute extends CommonMethod<CommonAttribute> {
}
declare const CommonInstance: CommonAttribute;
declare const Common: any;
declare type Optional<T> = T | undefined;
declare type CustomBuilder = (() => any) | void;
declare interface OverlayOptions {
    align?: Alignment;
    offset?: OverlayOffset;
}
declare interface OverlayOffset {
    x?: number;
    y?: number;
}
declare type FractionStop = [
    number,
    number
];
declare class CommonShapeMethod<T> extends CommonMethod<T> {
    constructor();
    strokeWidth(value: Length): T;
}
declare interface LinearGradient {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[
        ResourceColor,
        number
    ]>;
    repeating?: boolean;
}
declare interface PixelRoundPolicy {
    start?: PixelRoundCalcPolicy;
    top?: PixelRoundCalcPolicy;
    end?: PixelRoundCalcPolicy;
    bottom?: PixelRoundCalcPolicy;
}
declare interface LinearGradientBlurOptions {
    fractionStops: FractionStop[];
    direction: GradientDirection;
}
declare interface MotionBlurAnchor {
    x: number;
    y: number;
}
declare interface MotionBlurOptions {
    radius: number;
    anchor: MotionBlurAnchor;
}
declare interface SizeResult {
    width: number;
    height: number;
}
declare type UIContext = import('../api/@ohos.arkui.UIContext').UIContext;
declare type DrawContext = import('../api/arkui/Graphics').DrawContext;
declare type VisualEffect = import('../api/@ohos.graphics.uiEffect').default.VisualEffect;
declare type Filter = import('../api/@ohos.graphics.uiEffect').default.Filter;
declare type Blender = import('../api/@ohos.graphics.uiEffect').default.Blender;
declare type ComponentContent<T = Object> = import('../api/arkui/ComponentContent').ComponentContent<T>;
declare type Theme = import('../api/@ohos.arkui.theme').Theme;
declare class View {
}
declare interface RectResult {
    x: number;
    y: number;
    width: number;
    height: number;
}
declare interface CaretOffset {
    index: number;
    x: number;
    y: number;
}
declare interface TextContentControllerOptions {
    offset?: number;
}
declare abstract class TextContentControllerBase {
    getCaretOffset(): CaretOffset;
    getTextContentRect(): RectResult;
    getTextContentLineCount(): number;
    addText(text: string, textOperationOptions?: TextContentControllerOptions): number;
    setStyledPlaceholder(styledString: StyledString): void;
    deleteText(range?: TextRange): void;
    getSelection(): TextRange;
    clearPreviewText(): void;
    getText(range?: TextRange): string;
    deleteBackward(): void;
    scrollToVisible(range?: TextRange): void;
}
declare enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2
}
declare class ScrollableCommonMethod<T> extends CommonMethod<T> {
    scrollBar(barState: BarState): T;
    scrollBarColor(color: Color | number | string): T;
    scrollBarColor(color: Color | number | string | Resource): T;
    scrollBarWidth(value: number | string): T;
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): T;
    nestedScroll(value: NestedScrollOptions): T;
    enableScrollInteraction(value: boolean): T;
    friction(value: number | Resource): T;
    onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): T;
    onWillStartDragging(handler: VoidCallback): T;
    onWillStopDragging(handler: OnWillStopDraggingCallback): T;
    onDidStopDragging(handler: OnDidStopDraggingCallback): T;
    onWillStartFling(handler: VoidCallback): T;
    onDidStopFling(handler: VoidCallback): T;
    onReachStart(event: () => void): T;
    onReachEnd(event: () => void): T;
    onScrollStart(event: () => void): T;
    onScrollStop(event: () => void): T;
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): T;
}
declare class ScrollResult {
    offsetRemain: number;
}
declare type OnWillScrollCallback = (scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => void | ScrollResult;
declare type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
declare type OnItemDragStartCallback = (event: ItemDragInfo, itemIndex: number) => CustomBuilder;
declare type OnGetPreviewBadgeCallback = () => boolean | number;
declare type OnWillStopDraggingCallback = (velocity: number) => void;
declare type OnDidStopDraggingCallback = (willFling: boolean) => void;
declare interface EdgeEffectOptions {
    alwaysEnabled: boolean;
    effectEdge?: number;
}
declare class ChildrenMainSize {
    constructor(childDefaultSize: number);
    set childDefaultSize(value: number);
    get childDefaultSize(): number;
}
declare interface EditModeOptions {
    enableGatherSelectedItemsAnimation?: boolean;
    onGetPreviewBadge?: OnGetPreviewBadgeCallback;
}
declare interface BackgroundBrightnessOptions {
    rate: number;
    lightUpDegree: number;
}
declare interface PointLightStyle {
    lightSource?: LightSource;
    illuminated?: IlluminatedType;
    bloom?: number;
}
declare interface LightSource {
    positionX: Dimension;
    positionY: Dimension;
    positionZ: Dimension;
    intensity: number;
    color?: ResourceColor;
}
declare function wrapBuilder<Args extends Object[]>(builder: (...args: Args) => void): WrappedBuilder<Args>;
declare type BuilderCallback = (...args: Args) => void;
declare function mutableBuilder<Args extends Object[]>(builder: BuilderCallback): MutableBuilder<Args>;
declare class WrappedBuilder<Args extends Object[]> {
    builder: (...args: Args) => void;
    constructor(builder: (...args: Args) => void);
}
declare class MutableBuilder<Args extends Object[]> extends WrappedBuilder<Args> {
}
declare interface Callback<T, V = void> {
    (data: T): V;
}
declare type HoverCallback = (isHover: boolean, event: HoverEvent) => void;
declare type AccessibilityCallback = (isHover: boolean, event: AccessibilityHoverEvent) => void;
declare type AccessibilityTransparentCallback = (event: TouchEvent) => void;
declare interface VisibleAreaEventOptions {
    ratios: Array<number>;
    expectedUpdateInterval?: number;
    measureFromViewport?: boolean;
}
declare type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: number) => void;
declare interface UIGestureEvent {
    addGesture<T>(gesture: GestureHandler<T>, priority?: GesturePriority, mask?: GestureMask): void;
    addParallelGesture<T>(gesture: GestureHandler<T>, mask?: GestureMask): void;
    removeGestureByTag(tag: string): void;
    clearGestures(): void;
}
declare interface GestureModifier {
    applyGesture(event: UIGestureEvent): void;
}
declare interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
declare interface FocusMovement {
    forward?: string;
    backward?: string;
    up?: string;
    down?: string;
    left?: string;
    right?: string;
}
declare enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1
}
declare enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1
}
declare interface DateRange {
    start?: Date;
    end?: Date;
}

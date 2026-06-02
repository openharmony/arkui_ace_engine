/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// Resource interface
declare interface Resource {
  bundleName: string;
  moduleName: string;
  id: number;
  params?: Array<string | number | Resource>;
  type?: number;
}

type ResourceColor = number | Color | string | Resource;

// ArkBackground class
// ArkBindMenu class
// ArkBorder class
// ArkSearchAutoCapitalization class
declare class ArkSearchAutoCapitalization {
  autoCapitalizationMode: AutoCapitalizationMode;
  isEqual(another: ArkSearchAutoCapitalization): boolean;
}

// ArkTextAreaAutoCapitalization class
declare class ArkTextAreaAutoCapitalization {
  autoCapitalizationMode: AutoCapitalizationMode;
  isEqual(another: ArkTextAreaAutoCapitalization): boolean;
}

// ArkTextInputAutoCapitalization class
declare class ArkTextInputAutoCapitalization {
  autoCapitalizationMode: AutoCapitalizationMode;
  isEqual(another: ArkTextInputAutoCapitalization): boolean;
}

// ArkTextInputType - using InputType enum
type ArkTextInputType = InputType;

// Length type - using intersection type to support optional properties
type Length = string | number | Resource | LengthMetrics;

// EdgeWidths interface - made more flexible to accept LocalizedEdgeWidths
declare interface EdgeWidths {
  top?: Length | LengthMetrics;
  right?: Length | LengthMetrics;
  bottom?: Length | LengthMetrics;
  left?: Length | LengthMetrics;
  start?: Length | LengthMetrics;
  end?: Length | LengthMetrics;
}

// LocalizedEdgeWidths interface
declare interface LocalizedEdgeWidths {
  top?: LengthMetrics;
  end?: LengthMetrics;
  bottom?: LengthMetrics;
  start?: LengthMetrics;
  left?: LengthMetrics;
  right?: LengthMetrics;
}

// ArkBorderRadiusOpts class
// LocalizedBorderRadius interface
declare interface LocalizedBorderRadius {
  topStart?: LengthMetrics;
  topEnd?: LengthMetrics;
  bottomStart?: LengthMetrics;
  bottomEnd?: LengthMetrics;
}

// RenderStrategy enum
declare enum RenderStrategy {
  NORMAL = 0,
  COMPONENT = 1
}

// BorderRadiuses interface
declare interface BorderRadiuses {
  topLeft?: Length;
  topRight?: Length;
  bottomLeft?: Length;
  bottomRight?: Length;
}

// Position interface
declare interface Position {
  x?: Length;
  y?: Length;
  top?: Dimension;
  left?: Dimension;
  bottom?: Dimension;
  right?: Dimension;
  start?: Dimension;
  end?: Dimension;
}

// Edges interface
declare interface Edges {
  top?: Dimension;
  left?: Dimension;
  bottom?: Dimension;
  right?: Dimension;
  start?: Dimension;
  end?: Dimension;
  x?: Length;
  y?: Length;
}

// LocalizedEdges interface
declare interface LocalizedEdges {
  top?: LengthMetrics;
  start?: LengthMetrics;
  bottom?: LengthMetrics;
  end?: LengthMetrics;
  left?: LengthMetrics;
  right?: LengthMetrics;
  x?: Length;
  y?: Length;
}

// GradientDirection enum
declare enum GradientDirection {
  LEFT = 0,
  TOP = 1,
  RIGHT = 2,
  BOTTOM = 3,
  LEFT_TOP = 4,
  LEFT_BOTTOM = 5,
  RIGHT_TOP = 6,
  RIGHT_BOTTOM = 7,
  NONE = 8,
  START = 9,
  END = 10
}

// ArkOverlay class
// EdgeColors interface
declare interface EdgeColors {
  top?: ResourceColor;
  right?: ResourceColor;
  bottom?: ResourceColor;
  left?: ResourceColor;
}

// LocalizedEdgeColors interface
declare interface LocalizedEdgeColors {
  top?: ResourceColor;
  end?: ResourceColor;
  bottom?: ResourceColor;
  start?: ResourceColor;
}

// Matrix4Transit type
type Matrix4Transit = any;

// BorderStyle enum
declare enum BorderStyle {
  DOTTED = 2,
  DASHED = 1,
  SOLID = 0
}

// EdgeStyles interface
declare interface EdgeStyles {
  top?: BorderStyle;
  right?: BorderStyle;
  bottom?: BorderStyle;
  left?: BorderStyle;
}

// ShadowOptions interface
declare interface ShadowOptions {
  radius?: number | Resource;
  type?: ShadowType;
  color?: Color | string | Resource | ColoringStrategy;
  offsetX?: number | Resource;
  offsetY?: number | Resource;
  fill?: boolean;
  shadowStyle?: number;
}

// ShadowType enum
declare enum ShadowType {
  COLOR = 0,
  BLUR = 1
}

// ArkShadowStyle class (used with new)
// ShadowStyle enum
declare enum ShadowStyle {
  OUTER_DEFAULT_XS = 0,
  OUTER_DEFAULT_SM = 1,
  OUTER_DEFAULT_MD = 2,
  OUTER_DEFAULT_LG = 3,
  OUTER_FLOATING_SM = 4,
  OUTER_FLOATING_MD = 5,
  OUTLINE_XS = 6,
  OUTLINE_SM = 7,
  OUTLINE_MD = 8,
  COSINE = 9
}

// ShadowValueWithStyle type - for use with ModifierWithKey to support shadowStyle property
declare type ShadowValueWithStyle = ShadowOptions | (ArkShadowStyle & { shadowStyle: number });

// ArkBlurOptions class
// BlurOptions interface
declare interface BlurOptions {
  low?: number;
  high?: number;
  threshold?: number;
  thresholdRange?: number;
  grayscale?: number;
  direction?: number;
  style?: number;
}

// InvertOptions interface
declare interface InvertOptions {
  low: number;
  high: number;
  threshold: number;
  thresholdRange: number;
}

// AutoCapitalizationMode enum
declare enum AutoCapitalizationMode {
  NONE = 0,
  WORDS = 1,
  SENTENCES = 2,
  CHARACTERS = 3
}

// InputType enum
declare enum InputType {
  NORMAL = 0,
  NUMBER = 2,
  PHONE_NUMBER = 3,
  EMAIL = 5,
  PASSWORD = 7,
  NUMBER_PASSWORD = 8,
  SCREEN_LOCK_PASSWORD = 9,
  USER_NAME = 10,
  NEW_PASSWORD = 11,
  NUMBER_DECIMAL = 12,
  URL = 13,
  ONE_TIME_CODE = 14
}

// LengthMetrics class
declare class LengthMetrics {
  unit: number;
  value: number;
}

declare interface PageInfo {}
declare interface NavigationInfo {}

type KNode = number | null;
// interface_sdk-js/api/@internal/component/ets/enums.d.ts
declare enum Color {
  White = 0,
  Black = 1,
  Blue = 2,
  Brown = 3,
  Gray = 4,
  Green = 5,
  Grey = 6,
  Orange = 7,
  Pink = 8,
  Red = 9,
  Yellow = 10,
  Transparent = 11
}

//interface_sdk-js/api/@internal/component/ets/common.d.ts
declare enum RepeatMode {
  Repeat,
  Stretch,
  Round,
  Space,
}
//interface_sdk-js/api/@internal/component/ets/common.d.ts
declare interface LinearGradient {
  angle?: number | string;
  direction?: GradientDirection;
  colors: Array<[ResourceColor, number]>;
  repeating?: boolean;
}
declare interface BorderImageOption {
  slice?: Length | EdgeWidths | LocalizedEdgeWidths,
  repeat?: RepeatMode,
  source?: string | Resource | LinearGradient,
  width?: Length | EdgeWidths | LocalizedEdgeWidths,
  outset?: Length | EdgeWidths | LocalizedEdgeWidths,
  fill?: boolean;
}

type Dimension = string | number | Resource;

declare interface OutlineRadiuses {
  topLeft?: Dimension;
  topRight?: Dimension;
  bottomLeft?: Dimension;
  bottomRight?: Dimension;
}

declare enum OutlineStyle {
  SOLID = 0,
  DASHED = 1,
  DOTTED = 2
}

declare interface EdgeOutlineStyles {
  top?: OutlineStyle;
  right?: OutlineStyle;
  bottom?: OutlineStyle;
  left?: OutlineStyle;
}

declare interface EdgeOutlineWidths {
  top?: Dimension;
  right?: Dimension;
  bottom?: Dimension;
  left?: Dimension;
}

declare interface OutlineOptions {
  width?: EdgeOutlineWidths | Dimension;
  color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
  radius?: OutlineRadiuses | Dimension;
  style?: EdgeOutlineStyles | OutlineStyle;
}

declare enum Alignment {
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

declare interface ResizableOptions {
  slice?: EdgeWidths;
  lattice?: any;
}

declare interface SizeOptions {
  width?: Length;
  height?: Length;
}

declare enum ImageSize {
  CONTAIN = 0,
  COVER = 1,
  AUTO = 2
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

declare interface RotateOptions {
  x?: number;
  y?: number;
  z?: number;
  angleX?: number | string;
  angleY?: number | string;
  angleZ?: number | string;
  centerX?: number | string;
  centerY?: number | string;
  centerZ?: number | string;
  angle?: number | string;
  perspective?: number;
}

declare interface RotateAngleOptions {
  x?: number;
  y?: number;
  z?: number;
  angleX?: number | string;
  angleY?: number | string;
  angleZ?: number | string;
  centerX?: number | string;
  centerY?: number | string;
  centerZ?: number | string;
  angle?: number | string;
  perspective?: number;
}

declare interface GeometryTransitionOptions {
  follow?: boolean;
  hierarchyStrategy?: number;
}

declare interface FractionStop {
  stop: number;
  color: ResourceColor;
}

type PixelMap = any;
type Blender = any;

// EffectType enum
declare enum EffectType {
  DEFAULT = 0,
  WINDOW_EFFECT = 1
}

// Pixel stretch effect options
declare interface PixelStretchEffectOptions {
  top?: Length;
  bottom?: Length;
  left?: Length;
  right?: Length;
}

// ArkUseEffect class
// SystemBarEffectModifier class (extends ModifierWithKey<object>)
declare class SystemBarEffectModifier {
  static identity: Symbol;
  stageValue?: object;
  value?: object;
  constructor(value: object);
  applyStage(node: KNode, component?: any): boolean;
  applyStageImmediately(node: KNode, component?: any): void;
  applyPeer(node: KNode, reset: boolean, component?: any): void;
  checkObjectDiff(): boolean;
}

// ColoringStrategy enum
declare enum ColoringStrategy {
  INVERT = 'invert',
  AVERAGE = 'average',
  PRIMARY = 'primary'
}

// ClickEvent interface
declare interface ClickEvent {
  displayX: number;
  displayY: number;
  windowX: number;
  windowY: number;
  x: number;
  y: number;
  timestamp: number;
  screenX: number;
  screenY: number;
  hand?: number;
  globalDisplayX?: number;
  globalDisplayY?: number;
  preventDefault(): void;
}

// DragEvent interface
declare interface DragEvent {
  dragBehavior: number;
  useCustomDropAnimation: boolean;
  getDisplayX(): number;
  getDisplayY(): number;
  getWindowX(): number;
  getWindowY(): number;
  getX(): number;
  getY(): number;
  getThumbnail(): PixelMap | undefined;
  setThumbnail(thumbnail: PixelMap): void;
  getData(): unifiedData.UnifiedData | undefined;
  setData(data: unifiedData.UnifiedData): void;
  setResult(result: unifiedData.UnifiedData): void;
  getDataLoadParams(): unifiedData.DataLoadParams | undefined;
  setDataLoadParams(params: unifiedData.DataLoadParams): void;
  enableInternalDropAnimation(configuration: string): void;
}

// CustomBuilder type
type CustomBuilder = () => void;

// DragItemInfo interface
declare interface DragItemInfo {
  pixelMap?: PixelMap;
  builder?: CustomBuilder;
  extraInfo?: string;
}

// DragSpringLoadingState
type DragSpringLoadingState = any;

// SpringLoadingDragInfos
type SpringLoadingDragInfos = any;

// ArkDragSpringLoadingConfiguration class
declare class ArkDragSpringLoadingConfiguration {
  stillTimeLimit: number | undefined;
  updateInterval: number | undefined;
  updateNotifyCount: number | undefined;
  updateToFinishInterval: number | undefined;
  isEqual(another: ArkDragSpringLoadingConfiguration): boolean;
}

// ArkSpringLoadingContext class
declare class ArkSpringLoadingContext {
  state: DragSpringLoadingState | undefined;
  currentNotifySequence: number | undefined;
  dragInfos: SpringLoadingDragInfos | undefined;
  currentConfig: ArkDragSpringLoadingConfiguration | undefined;
  abort: () => void;
  updateConfiguration: (config: ArkDragSpringLoadingConfiguration) => void;
}

// ArkDragSpringLoading class
// ArkOnDrop class
// TouchEvent interface
declare interface TouchEvent {
  type: number;
  touches: TouchList;
  changedTouches: TouchList;
  stopPropagation(): void;
  preventDefault(): void;
  getHistoricalPoints(): Array<any> | undefined;
}

// TouchObject interface
declare interface TouchObject {
  x: number;
  y: number;
  displayX: number;
  displayY: number;
  windowX: number;
  windowY: number;
  screenX: number;
  screenY: number;
  id: number;
}

// TouchList interface
declare interface TouchList extends Array<TouchObject> {}

// unifiedData namespace types
declare namespace unifiedData {
  class UnifiedData {}
  class DataLoadParams {}
}

// ===================== Missing type declarations =====================

// Function declarations
declare function getUINativeModule(): any;

// Utility types
type int32 = number;
type VoidCallback = () => void;
type Optional<T> = T | undefined;
type ResourceStr = string | Resource;
declare class BusinessError extends Error { code: number | string; constructor(code: number | string, message: string); }

// Enum declarations


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

declare enum BlendMode {
  NONE = 0, CLEAR = 1, SRC = 2, DST = 3, SRC_OVER = 4, DST_OVER = 5,
  SRC_IN = 6, DST_IN = 7, SRC_OUT = 8, DST_OUT = 9, SRC_ATOP = 10, DST_ATOP = 11,
  XOR = 12, PLUS = 13, MODULATE = 14, SCREEN = 15, OVERLAY = 16, DARKEN = 17,
  LIGHTEN = 18, COLOR_DODGE = 19, COLOR_BURN = 20, HARD_LIGHT = 21, SOFT_LIGHT = 22,
  DIFFERENCE = 23, EXCLUSION = 24, MULTIPLY = 25, HUE = 26, SATURATION = 27,
  COLOR = 28, LUMINOSITY = 29
}

declare enum BlendApplyType { FAST = 0, OFFSCREEN = 1 }

declare enum Axis { Vertical, Horizontal }
declare enum Direction { Ltr, Rtl, Auto }
declare enum HorizontalAlign { Start, Center, End }
declare enum VerticalAlign { Top, Center, Bottom }
declare enum ItemAlign { Auto, Start, Center, End, Baseline, Stretch }
declare enum Visibility { Visible, Hidden, None }
declare enum ImageRepeat { NoRepeat, X, Y, XY }
declare enum ChainStyle { SPREAD, SPREAD_INSIDE, PACKED }
declare enum ModalTransition { DEFAULT = 0, NONE = 1, ALPHA = 2 }
declare enum BlurStyleActivePolicy { FOLLOWS_WINDOW_ACTIVE_STATE = 0, ALWAYS_ACTIVE = 1, ALWAYS_INACTIVE = 2 }
declare enum ThemeColorMode { SYSTEM = 0, LIGHT = 1, DARK = 2 }
declare enum AdaptiveColor { DEFAULT = 0, AVERAGE = 1 }
declare enum SafeAreaType { SYSTEM = 0, CUTOUT = 1, KEYBOARD = 2 }
declare enum SafeAreaEdge { TOP = 0, BOTTOM = 1, START = 2, END = 3 }
declare enum LayoutSafeAreaType { SYSTEM = 0 }
declare enum LayoutSafeAreaEdge { TOP = 0, BOTTOM = 1, START = 2, END = 3, VERTICAL = 4, HORIZONTAL = 5, ALL = 6 }
declare enum HoverEffect { Auto, Scale, Highlight, None }
declare enum HitTestMode { Default, Block, Transparent, None, BLOCK_HIERARCHY, BLOCK_DESCENDANTS }
declare enum ResponseType { RightClick, LongPress }
declare enum RenderFit {
  CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4,
  TOP_LEFT = 5, TOP_RIGHT = 6, BOTTOM_LEFT = 7, BOTTOM_RIGHT = 8,
  RESIZE_FILL = 9, RESIZE_CONTAIN = 10, RESIZE_CONTAIN_TOP_LEFT = 11,
  RESIZE_CONTAIN_BOTTOM_RIGHT = 12, RESIZE_COVER = 13,
  RESIZE_COVER_TOP_LEFT = 14, RESIZE_COVER_BOTTOM_RIGHT = 15
}
declare enum ObscuredReasons { PLACEHOLDER = 0 }
declare enum FunctionKey {
  ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, TAB,
  DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT
}
declare enum ModifierKey { CTRL, SHIFT, ALT }
declare enum PreDragStatus {
  ACTION_DETECTING_STATUS = 0, READY_TO_TRIGGER_DRAG_ACTION = 1,
  PREVIEW_LIFT_STARTED = 2, PREVIEW_LIFT_FINISHED = 3,
  PREVIEW_LANDING_STARTED = 4, PREVIEW_LANDING_FINISHED = 5,
  ACTION_CANCELED_BEFORE_DRAG = 6, PREPARING_FOR_DRAG_DETECTION = 7
}
declare enum ScrollState { Idle, Scroll, Fling }
declare enum ScrollSource {
  DRAG = 0, FLING, EDGE_EFFECT, OTHER_USER_INPUT, SCROLL_BAR,
  SCROLL_BAR_FLING, SCROLLER, SCROLLER_ANIMATION
}
declare enum FocusDrawLevel { SELF = 0, TOP = 1 }
declare enum FocusPriority { AUTO = 0, PRIOR = 2000, PREVIOUS = 3000 }
declare enum LocalizedAlignment {
  TOP_START = "top_start", TOP = "top", TOP_END = "top_end",
  START = "start", CENTER = "center", END = "end",
  BOTTOM_START = "bottom_start", BOTTOM = "bottom", BOTTOM_END = "bottom_end"
}
declare enum GestureMask { Normal, IgnoreInternal }
declare enum GesturePriority { NORMAL = 0, PRIORITY = 1, PARALLEL = 2 }
declare enum GestureJudgeResult { CONTINUE = 0, REJECT = 1 }
declare enum GestureMode { Sequence, Parallel, Exclusive }
declare enum PanDirection { None, Horizontal, Left, Right, Vertical, Up, Down, All }
declare enum SwipeDirection { None, Horizontal, Vertical, All }
declare enum AccessibilitySamePageMode { SEMI_SILENT = 0, FULL_SILENT = 1 }
declare enum AccessibilityRoleType {
  ACTION_SHEET = 0, ALERT_DIALOG = 1, INDEXER_COMPONENT = 2, BADGE_COMPONENT = 3,
  BLANK = 4, BUTTON = 5, BACK_BUTTON = 6, SHEET_DRAG_BAR = 7, CALENDAR_PICKER = 8,
  CALENDAR = 9, CANVAS = 10, CANVAS_GRADIENT = 11, CANVAS_PATTERN = 12, CHECKBOX = 13,
  CHECKBOX_GROUP = 14, CIRCLE = 15, COLUMN_SPLIT = 16, COLUMN = 17,
  CANVAS_RENDERING_CONTEXT_2D = 18, CHART = 19, COUNTER = 20, CONTAINER_MODAL = 21,
  DATA_PANEL = 22, DATE_PICKER = 23, DIALOG = 24, DIVIDER = 25, DRAG_BAR = 26,
  EFFECT_COMPONENT = 27, ELLIPSE = 28, FLEX = 29, FLOW_ITEM = 30, FORM_COMPONENT = 31,
  FORM_LINK = 32, GAUGE = 33, GRID = 34, GRID_COL = 35, GRID_CONTAINER = 36,
  GRID_ITEM = 37, GRID_ROW = 38, HYPERLINK = 39, IMAGE = 40, IMAGE_ANIMATOR = 41,
  IMAGE_BITMAP = 42, IMAGE_DATA = 43, IMAGE_SPAN = 44, LABEL = 45, LINE = 46,
  LIST = 47, LIST_ITEM = 48, LIST_ITEM_GROUP = 49, LOADING_PROGRESS = 50, MARQUEE = 51,
  MATRIX2D = 52, MENU = 53, MENU_ITEM = 54, MENU_ITEM_GROUP = 55, NAV_DESTINATION = 56,
  NAV_ROUTER = 57, NAVIGATION = 58, NAVIGATION_BAR = 59, NAVIGATION_MENU = 60,
  NAVIGATOR = 61, OFFSCREEN_CANVAS = 62, OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
  OPTION = 64, PANEL = 65, PAPER_PAGE = 66, PATH = 67, PATH2D = 68, PATTERN_LOCK = 69,
  PICKER = 70, PICKER_VIEW = 71, PLUGIN_COMPONENT = 72, POLYGON = 73, POLYLINE = 74,
  POPUP = 75, PROGRESS = 76, QRCODE = 77, RADIO = 78, RATING = 79, RECT = 80,
  REFRESH = 81, RELATIVE_CONTAINER = 82, REMOTE_WINDOW = 83, RICH_EDITOR = 84,
  RICH_TEXT = 85, ROLE_PAGER = 86, ROW = 87, ROW_SPLIT = 88, SCROLL = 89,
  SCROLL_BAR = 90, SEARCH = 91, SEARCH_FIELD = 92, SELECT = 93, SHAPE = 94,
  SIDEBAR_CONTAINER = 95, SLIDER = 96, SPAN = 97, STACK = 98, STEPPER = 99,
  STEPPER_ITEM = 100, SWIPER = 101, SWIPER_INDICATOR = 102, SWITCH = 103,
  SYMBOL_GLYPH = 104, TAB_CONTENT = 105, TAB_BAR = 106, TABS = 107, TEXT = 108,
  TEXT_CLOCK = 109, TEXT_ENTRY = 110, TEXT_INPUT = 111, TEXT_PICKER = 112,
  TEXT_TIMER = 113, TEXT_AREA = 114, TEXT_FIELD = 115, TIME_PICKER = 116,
  TITLE_BAR = 117, TOGGLER = 118, UI_EXTENSION_COMPONENT = 119, VIDEO = 120,
  WATER_FLOW = 121, WEB = 122, XCOMPONENT = 123, ROLE_NONE = 124
}

// Interface declarations
declare interface Rectangle { x?: Length; y?: Length; width?: Length; height?: Length; }
declare interface Area { width: Length; height: Length; position: Position; globalPosition: Position; }
declare interface OffsetResult { xOffset: number; yOffset: number; }
declare interface Callback<T, V = void> { (data: T): V; }

declare interface AnimateParam {
  duration?: number; tempo?: number; curve?: Curve | string | ICurve;
  delay?: number; iterations?: number; playMode?: PlayMode;
  onFinish?: () => void;
}
interface ICurve { interpolate(fraction: number): number; }
declare enum Curve {
  Linear, Ease, EaseIn, EaseOut, EaseInOut, FastOutSlowIn,
  LinearOutSlowIn, FastOutLinearIn, ExtremeDeceleration, Sharp, Rhythm, Smooth, Friction
}
declare enum PlayMode { Normal, Reverse, Alternate, AlternateReverse }
declare enum TransitionType { All, Insert, Delete }

declare interface TransitionOptions {
  type?: TransitionType; opacity?: number;
  translate?: TranslateOptions; scale?: ScaleOptions; rotate?: RotateOptions;
}

declare class TransitionEffect {
  static translate(options: TranslateOptions): TransitionEffect;
  static rotate(options: RotateOptions): TransitionEffect;
  static scale(options: ScaleOptions): TransitionEffect;
  static opacity(alpha: number): TransitionEffect;
  static move(edge: TransitionEdge): TransitionEffect;
  static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect;
  animation(value: AnimateParam): TransitionEffect;
  combine(transitionEffect: TransitionEffect): TransitionEffect;
}
declare enum TransitionEdge { TOP = 0, BOTTOM = 1, START = 2, END = 3 }

declare interface MotionPathOptions { path: string; from?: number; to?: number; rotatable?: boolean; }
declare interface MotionBlurOptions { radius: number; anchor: { x: number; y: number }; }
declare interface sharedTransitionOptions {
  duration?: number; curve?: Curve | string | ICurve; delay?: number;
  motionPath?: MotionPathOptions; zIndex?: number; type?: SharedTransitionEffectType;
}
declare enum SharedTransitionEffectType { Static, Exchange }

declare interface ConstraintSizeOptions { minWidth?: Length; maxWidth?: Length; minHeight?: Length; maxHeight?: Length; }
declare interface SizeChangeCallback { (oldValue: SizeOptions, newValue: SizeOptions): void; }

declare interface AlignRuleOption {
  left?: { anchor: string; align: HorizontalAlign }; right?: { anchor: string; align: HorizontalAlign };
  middle?: { anchor: string; align: HorizontalAlign }; top?: { anchor: string; align: VerticalAlign };
  bottom?: { anchor: string; align: VerticalAlign }; center?: { anchor: string; align: VerticalAlign };
  bias?: { horizontal?: number; vertical?: number };
}

declare type Padding = any;
declare interface LocalizedPadding { top?: LengthMetrics; end?: LengthMetrics; bottom?: LengthMetrics; start?: LengthMetrics; }
declare type Margin = Padding;
declare type LocalizedMargin = LocalizedPadding;
declare interface LocalizedPosition { start?: LengthMetrics; top?: LengthMetrics; }

declare interface LocalizedBorderRadiuses { topStart?: LengthMetrics; topEnd?: LengthMetrics; bottomStart?: LengthMetrics; bottomEnd?: LengthMetrics; }

declare interface BorderOptions {
  width?: EdgeWidths | Length | LocalizedEdgeWidths; color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
  radius?: BorderRadiuses | Length | LocalizedBorderRadiuses; style?: EdgeStyles | BorderStyle;
  dashGap?: EdgeWidths | Length | LocalizedEdgeWidths;
  dashWidth?: EdgeWidths | Length | LocalizedEdgeWidths;
}
declare interface BackgroundOptions { align?: Alignment; ignoresLayoutSafeAreaEdges?: Array<LayoutSafeAreaEdge>; }
declare interface BackgroundImageOptions { syncLoad?: boolean; repeat?: ImageRepeat; }
declare interface BackgroundBlurStyleOptions extends BlurStyleOptions { policy?: BlurStyleActivePolicy; inactiveColor?: ResourceColor; type?: number; }
declare interface ForegroundBlurStyleOptions extends BlurStyleOptions { }
declare interface BlurStyleOptions { colorMode?: ThemeColorMode; adaptiveColor?: AdaptiveColor; scale?: number; blurOptions?: BlurOptions; }
declare interface SystemAdaptiveOptions { disableSystemAdaptation?: boolean; }
declare interface BackgroundEffectOptions {
  radius: number; saturation?: number; brightness?: number; color?: ResourceColor;
  adaptiveColor?: AdaptiveColor; blurOptions?: BlurOptions; policy?: BlurStyleActivePolicy;
  inactiveColor?: ResourceColor; type?: number; disableSystemAdaptation?: boolean;
}
declare interface ForegroundEffectOptions { radius: number; }
declare interface BackgroundBrightnessOptions { rate: number; lightUpDegree: number; }
declare interface LinearGradientBlurOptions { fractionStops: FractionStop[]; direction: GradientDirection; }
declare interface PixelRoundPolicy { start?: number; top?: number; end?: number; bottom?: number; }
declare interface ClickEffect { level: number; scale?: number; }
declare interface ChainWeightOptions { horizontal?: number; vertical?: number; }

declare interface AttributeModifier<T> {
  attribute?: T; modifierState?: number; isAttributeUpdater?: boolean;
  applyNormalAttribute?(instance: T): void;
  applyPressedAttribute?(instance: T): void;
  applyFocusedAttribute?(instance: T): void;
  applyDisabledAttribute?(instance: T): void;
  applySelectedAttribute?(instance: T): void;
  applyHoveredAttribute?(instance: T): void;
  initializeModifier?(attribute: T): void;
  onComponentChanged?(after: T): void;
}

declare class CommonMethod<T> {
  width(value: Length): T; height(value: Length): T;
  padding(value: Padding | Length | LocalizedPadding): T;
  margin(value: Margin | Length | LocalizedMargin): T;
  background(content: CustomBuilder | ResourceColor, options?: BackgroundOptions): T;
  backgroundColor(value: ResourceColor): T;
  backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): T;
  backgroundImage(src: ResourceStr | PixelMap, options?: BackgroundImageOptions): T;
  backgroundImageSize(value: SizeOptions | ImageSize): T;
  backgroundImagePosition(value: Position | Alignment): T;
  backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): T;
  backgroundEffect(options: BackgroundEffectOptions): T;
  foregroundEffect(options: ForegroundEffectOptions): T;
  visualEffect(effect: VisualEffect): T;
  backgroundFilter(filter: Filter): T;
  foregroundFilter(filter: Filter): T;
  foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): T;
  opacity(value: number | Resource): T;
  border(value: BorderOptions): T;
  borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses, type?: RenderStrategy): T;
  outline(value: OutlineOptions): T;
  onClick(event: (event: ClickEvent) => void): T;
  onHover(event: (isHover: boolean, event: HoverEvent) => void): T;
  onMouse(event: (event: MouseEvent) => void): T;
  onTouch(event: (event: TouchEvent) => void): T;
  onKeyEvent(event: (event: KeyEvent) => void): T;
  focusable(value: boolean): T;
  tabStop(isTabStop: boolean): T;
  onFocus(event: () => void): T;
  onBlur(event: () => void): T;
  tabIndex(index: number): T;
  defaultFocus(value: boolean): T;
  groupDefaultFocus(value: boolean): T;
  focusOnTouch(value: boolean): T;
  focusBox(style: FocusBoxStyle): T;
  focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): T;
  focusScopePriority(scopeId: string, priority?: FocusPriority): T;
  animation(value: AnimateParam): T;
  transition(value: TransitionOptions | TransitionEffect): T;
  gesture(gesture: GestureType, mask?: GestureMask): T;
  priorityGesture(gesture: GestureType, mask?: GestureMask): T;
  parallelGesture(gesture: GestureType, mask?: GestureMask): T;
  blur(value: number, options?: BlurOptions): T;
  linearGradientBlur(value: number, options: LinearGradientBlurOptions): T;
  motionBlur(value: MotionBlurOptions): T;
  brightness(value: number): T;
  contrast(value: number): T;
  grayscale(value: number): T;
  saturate(value: number): T;
  sepia(value: number): T;
  invert(value: number | InvertOptions): T;
  hueRotate(value: number | string): T;
  useEffect(useEffect: boolean, effectType?: EffectType): T;
  backdropBlur(value: number, options?: BlurOptions): T;
  renderGroup(value: boolean): T;
  translate(value: TranslateOptions): T;
  scale(value: ScaleOptions): T;
  rotate(value: RotateOptions): T;
  onAppear(event: () => void): T;
  onDisAppear(event: () => void): T;
  onAreaChange(event: (oldValue: Area, newValue: Area) => void): T;
  visibility(value: Visibility): T;
  alignSelf(value: ItemAlign): T;
  zIndex(value: number): T;
  sharedTransition(id: string, options?: sharedTransitionOptions): T;
  direction(value: Direction): T;
  align(value: Alignment): T;
  position(value: Position | Edges | LocalizedEdges): T;
  markAnchor(value: Position | LocalizedPosition): T;
  offset(value: Position | Edges | LocalizedEdges): T;
  enabled(value: boolean): T;
  alignRules(value: AlignRuleOption): T;
  chainMode(direction: Axis, style: ChainStyle): T;
  aspectRatio(value: number): T;
  clickEffect(value: ClickEffect | null): T;
  overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number } }): T;
  shadow(value: ShadowOptions | ShadowStyle): T;
  blendMode(value: BlendMode, type?: BlendApplyType): T;
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): T;
  mask(value: ProgressMask | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): T;
  key(value: string): T;
  id(value: string): T;
  geometryTransition(id: string, options?: GeometryTransitionOptions): T;
  bindTips(message: TipsMessageType, options?: TipsOptions): T;
  bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): T;
  bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): T;
  bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): T;
  bindContentCover(isShow: boolean, builder: CustomBuilder, options?: ContentCoverOptions): T;
  bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): T;
  stateStyles(value: StateStyles): T;
  restoreId(value: number): T;
  onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): T;
  onVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): T;
  linearGradient(value: any): T;
  sweepGradient(value: any): T;
  radialGradient(value: any): T;
  motionPath(value: MotionPathOptions): T;
  colorBlend(value: Color | string | Resource): T;
  systemBarEffect(): T;
  useShadowBatching(value: boolean): T;
  backgroundImageResizable(value: ResizableOptions): T;
  pixelRound(value: PixelRoundPolicy): T;
  obscured(reasons: Array<ObscuredReasons>): T;
  renderFit(fitMode: RenderFit): T;
  attributeModifier(modifier: AttributeModifier<T>): T;
  gestureModifier(modifier: GestureModifier): T;
  backgroundBrightness(params: BackgroundBrightnessOptions): T;
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): T;
  onGestureRecognizerJudgeBegin(callback: GestureRecognizerJudgeBeginCallback): T;
  monopolizeEvents(monopolize: boolean): T;
  onTouchIntercept(callback: Callback<TouchEvent, HitTestMode>): T;
  onSizeChange(event: SizeChangeCallback): T;
  accessibilityFocusDrawLevel(drawLevel: FocusDrawLevel): T;
  onTouchTestDone(callback: TouchTestDoneCallback): T;
  onDragSpringLoading(callback: Callback<any> | null, configuration?: any): T;
  expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): T;
  ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): T;
  keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): T;
  customProperty(name: string, value: Optional<Object>): T;
  allowDrop(value: Array<UniformDataType> | null | Array<string>): T;
  draggable(value: boolean): T;
  dragPreview(value: CustomBuilder | DragItemInfo | string, config?: PreviewConfiguration): T;
  dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): T;
  onPreDrag(callback: Callback<PreDragStatus>): T;
  onDragStart(event: (event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): T;
  onDragEnter(event: (event: DragEvent, extraParams?: string) => void): T;
  onDragMove(event: (event: DragEvent, extraParams?: string) => void): T;
  onDragLeave(event: (event: DragEvent, extraParams?: string) => void): T;
  onDrop(event: (event: DragEvent, extraParams?: string) => void): T;
  onDragEnd(event: (event: DragEvent, extraParams?: string) => void): T;
  layoutWeight(value: number | string): T;
  chainWeight(chainWeight: ChainWeightOptions): T;
  safeAreaPadding(paddingValue: Padding | LengthMetrics | LocalizedPadding): T;
  responseRegion(value: Array<Rectangle> | Rectangle): T;
  hitTestBehavior(value: HitTestMode): T;
  onChildTouchTest(event: (value: Array<TouchTestInfo>) => TouchResult): T;
  hoverEffect(value: HoverEffect): T;
  flexGrow(value: number): T;
  flexShrink(value: number): T;
  flexBasis(value: number | string): T;
  displayPriority(value: number): T;
  freeze(value: boolean): T;
  sphericalEffect(value: number): T;
  lightUpEffect(value: number): T;
  pixelStretchEffect(options: PixelStretchEffectOptions): T;
  reuseId(id: string): T;
  allowForceDark(value: boolean): T;
  accessibilityGroup(value: boolean): T;
  accessibilityText(value: string | Resource): T;
  accessibilityRole(role: AccessibilityRoleType): T;
  accessibilityLevel(value: string): T;
  accessibilityDescription(value: string | Resource): T;
  onAttach(callback: Callback<void>): T;
  onDetach(callback: Callback<void>): T;
}

declare class CommonAttribute extends CommonMethod<CommonAttribute> { }
declare type VisualEffect = any;
declare type Filter = any;
declare type UniformDataType = string;
declare type BrightnessOptions = any;
declare type SystemUiMaterial = any;
declare type ProgressMask = any;
declare type TipsMessageType = ResourceStr | any;
declare type OnScrollVisibleContentChangeCallback = (start: any, end: any) => void;

declare class ViewStackProcessor { static GetElmtIdToAccountFor(): void; }
declare class JsPointerClass { invalid(): boolean; }
declare class ModifierJS { [key: string]: Function & { new (...args: any[]): any }; }

declare interface FocusBoxStyle { margin?: any; strokeColor?: any; strokeWidth?: any; }
declare interface FocusMovement { forward?: string; backward?: string; up?: string; down?: string; left?: string; right?: string; }

declare interface KeyEvent {
  type: number; keyCode: number; keyText: string; keySource: number; deviceId: number;
  metaKey: number; timestamp: number; stopPropagation: () => void; unicode?: number;
}
declare interface HoverEvent {
  x?: number; y?: number; windowX?: number; windowY?: number;
  displayX?: number; displayY?: number; stopPropagation: () => void;
}
declare interface HoverMoveEvent extends HoverEvent {}
declare interface MouseEvent {
  button: number; action: number; displayX: number; displayY: number;
  windowX: number; windowY: number; screenX: number; screenY: number;
  x: number; y: number; stopPropagation: () => void;
}
declare interface AxisEvent {
  action: number; displayX: number; displayY: number;
  windowX: number; windowY: number; x: number; y: number;
}
declare interface FocusAxisEvent { axisMap: Map<any, number>; stopPropagation: Callback<void>; }

declare interface StateStyles { normal?: any; pressed?: any; disabled?: any; focused?: any; clicked?: any; selected?: object; }

declare interface PopupOptions {
  message: string; placementOnTop?: boolean; placement?: Placement;
  primaryButton?: { value: string; action: () => void };
  secondaryButton?: { value: string; action: () => void };
  onStateChange?: (event: { isVisible: boolean }) => void;
  arrowOffset?: Length; showInSubWindow?: boolean;
}
declare enum Placement { Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight, LeftTop, LeftBottom, RightTop, RightBottom }

declare interface CustomPopupOptions {
  builder: CustomBuilder; placement?: Placement;
  popupColor?: Color | string | Resource | number;
  enableArrow?: boolean; autoCancel?: boolean;
}
declare interface TipsOptions {
  appearingTime?: number; disappearingTime?: number;
  appearingTimeWithContinuousOperation?: number;
  disappearingTimeWithContinuousOperation?: number;
  enableArrow?: boolean; arrowPointPosition?: any;
  arrowWidth?: Dimension; arrowHeight?: Dimension; showAtAnchor?: any;
}
declare interface MenuElement { value: ResourceStr; icon?: ResourceStr; enabled?: boolean; action: () => void; }
declare interface MenuOptions extends ContextMenuOptions { title?: ResourceStr; showInSubWindow?: boolean; }
declare interface ContextMenuOptions {
  offset?: Position; placement?: Placement; enableArrow?: boolean;
  arrowOffset?: Length; preview?: any; previewBorderRadius?: any;
  borderRadius?: any; onAppear?: () => void; onDisappear?: () => void;
}
declare interface ContentCoverOptions {
  modalTransition?: ModalTransition; transition?: TransitionEffect;
  enableSafeArea?: boolean;
}
declare interface SheetOptions extends BindOptions {
  height?: any; dragBar?: boolean; modalTransition?: ModalTransition;
  maskColor?: ResourceColor; preferType?: any; mode?: any;
}
declare interface BindOptions {
  backgroundColor?: ResourceColor; onAppear?: () => void;
  onDisappear?: () => void; onWillAppear?: () => void; onWillDisappear?: () => void;
}

declare interface DragPreviewOptions { mode?: any; modifier?: any; numberBadge?: boolean | number; sizeChangeEffect?: any; }
declare interface DragInteractionOptions {
  isMultiSelectionEnabled?: boolean; defaultAnimationBeforeLifting?: boolean;
  enableHapticFeedback?: boolean; enableEdgeAutoScroll?: boolean; isLiftingDisabled?: boolean;
}
declare interface PreviewConfiguration { onlyForLifting?: boolean; delayCreating?: boolean; }
declare interface DropOptions { disableDataPrefetch?: boolean; }

declare interface VisibleAreaEventOptions { ratios: Array<number>; expectedUpdateInterval?: number; measureFromViewport?: boolean; }
declare type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: number) => void;

declare type TouchTestDoneCallback = (event: BaseGestureEvent, recognizers: Array<GestureRecognizer>) => void;
declare type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>) => GestureJudgeResult;
declare type AccessibilityFocusCallback = (isFocus: boolean) => void;
declare type AccessibilityActionInterceptCallback = (action: any) => any;
declare type AccessibilityTransparentCallback = (event: TouchEvent) => void;

// Gesture types
declare interface GestureInfo { tag?: string; type: any; isSystemGesture: boolean; }
interface BaseGestureEvent { fingerList: any[]; }
interface GestureEvent extends BaseGestureEvent { repeat: boolean; offsetX: number; offsetY: number; angle: number; speed: number; scale: number; }
declare type GestureType = TapGestureInterface | LongPressGestureInterface | PanGestureInterface | PinchGestureInterface | SwipeGestureInterface | RotationGestureInterface | GestureGroupInterface;
interface TapGestureInterface { (value?: any): TapGestureInterface; onAction(event: (event: GestureEvent) => void): TapGestureInterface; tag(tag: string): TapGestureInterface; }
interface LongPressGestureInterface { (value?: any): LongPressGestureInterface; onAction(event: (event: GestureEvent) => void): LongPressGestureInterface; onActionEnd(event: (event: GestureEvent) => void): LongPressGestureInterface; onActionCancel(event: () => void): LongPressGestureInterface; tag(tag: string): LongPressGestureInterface; }
interface PanGestureInterface { (value?: any): PanGestureInterface; onActionStart(event: (event: GestureEvent) => void): PanGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): PanGestureInterface; onActionEnd(event: (event: GestureEvent) => void): PanGestureInterface; onActionCancel(event: () => void): PanGestureInterface; tag(tag: string): PanGestureInterface; }
interface SwipeGestureInterface { (value?: any): SwipeGestureInterface; onAction(event: (event: GestureEvent) => void): SwipeGestureInterface; tag(tag: string): SwipeGestureInterface; }
interface PinchGestureInterface { (value?: any): PinchGestureInterface; onActionStart(event: (event: GestureEvent) => void): PinchGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): PinchGestureInterface; onActionEnd(event: (event: GestureEvent) => void): PinchGestureInterface; onActionCancel(event: () => void): PinchGestureInterface; tag(tag: string): PinchGestureInterface; }
interface RotationGestureInterface { (value?: any): RotationGestureInterface; onActionStart(event: (event: GestureEvent) => void): RotationGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): RotationGestureInterface; onActionEnd(event: (event: GestureEvent) => void): RotationGestureInterface; onActionCancel(event: () => void): RotationGestureInterface; tag(tag: string): RotationGestureInterface; }
interface GestureGroupInterface { (mode: GestureMode, ...gesture: GestureType[]): GestureGroupInterface; onCancel(event: () => void): GestureGroupInterface; }
declare interface GestureModifier { applyGesture(event: UIGestureEvent): void; }
declare interface UIGestureEvent {
  addGesture<T>(gesture: any, priority?: GesturePriority, mask?: GestureMask): void;
  addParallelGesture<T>(gesture: any, mask?: GestureMask): void;
  removeGestureByTag(tag: string): void; clearGestures(): void;
}
declare class GestureRecognizer { getTag(): string; getType(): any; isBuiltIn(): boolean; setEnabled(isEnabled: boolean): void; isEnabled(): boolean; }
declare class TouchRecognizer { getEventTargetInfo(): any; cancelTouch(): void; }
declare class TouchTestInfo { windowX: number; windowY: number; parentX: number; parentY: number; x: number; y: number; id: string; }
declare class TouchResult { strategy: number; id?: string; }


// Shape attribute classes
declare class CommonShapeMethod<T> { stroke(value: ResourceColor): T; fill(value: ResourceColor): T; strokeWidth(value: Length): T; antiAlias(value: boolean): T; }
declare class CircleAttribute extends CommonShapeMethod<CircleAttribute> { }
declare class EllipseAttribute extends CommonShapeMethod<EllipseAttribute> { }
declare class PathAttribute extends CommonShapeMethod<PathAttribute> { }
declare class RectAttribute extends CommonShapeMethod<RectAttribute> { }
type CircleShape = any; type EllipseShape = any; type PathShape = any; type RectShape = any;

// Ark* internal types
// SourceTool enum (used in ArkGesture.ts)
declare enum SourceTool { Unknown, Finger, Pen, MOUSE, TOUCHPAD, JOYSTICK }

// Gesture handler options (used in ArkGesture.ts)
interface BaseHandlerOptions { isFingerCountLimited?: boolean; }
interface TapGestureHandlerOptions extends BaseHandlerOptions { count?: number; fingers?: number; distanceThreshold?: number; }
interface LongPressGestureHandlerOptions extends BaseHandlerOptions { fingers?: number; repeat?: boolean; duration?: number; allowableMovement?: number; }
interface PanGestureHandlerOptions extends BaseHandlerOptions { fingers?: number; direction?: PanDirection; distance?: number; distanceMap?: Map<SourceTool, number>; }
interface SwipeGestureHandlerOptions extends BaseHandlerOptions { fingers?: number; direction?: SwipeDirection; speed?: number; }
interface PinchGestureHandlerOptions extends BaseHandlerOptions { fingers?: number; distance?: number; }
interface RotationGestureHandlerOptions extends BaseHandlerOptions { fingers?: number; angle?: number; }
interface GestureGroupGestureHandlerOptions { mode: GestureMode; gestures: any[]; }

// Enums for ArkSymbolSpan.ts
declare enum FontWeight { Lighter, Normal, Regular, Medium, Bold, Bolder }
declare enum SymbolRenderingStrategy { SINGLE = 0, MULTIPLE_COLOR = 1, MULTIPLE_OPACITY = 2 }
declare enum SymbolEffectStrategy { NONE = 0, SCALE = 1, HIERARCHICAL = 2 }

// GestureHandler, TapGestureHandler, LongPressGestureHandler, PanGestureHandler,
// SwipeGestureHandler, PinchGestureHandler, RotationGestureHandler, GestureGroupHandler
// are defined in src/ArkGesture.ts - removed to avoid duplicate declarations

// ===================== Missing type declarations for ArkTextArea =====================

// Enums
declare enum FontStyle { Normal, Italic }
declare enum TextAlign { START, CENTER, END }
declare enum TextOverflow { None, Clip, Ellipsis, Marquee }
declare enum TextDecorationType { None, Underline, Overline, LineThrough }
declare enum TextDecorationStyle { SOLID, DOUBLE, DOTTED, DASHED, WAVY }
declare enum TextDirection { LTR, RTL, Auto }
declare enum TextContentStyle { DEFAULT, INLINE }
declare enum TextHeightAdaptivePolicy { MAX_LINES, MIN_FONT_SIZE, FONT_SIZE_ADJUST }
declare enum BarState { Off, Auto, On }
declare enum EllipsisMode { HEAD, MIDDLE, TAIL }
declare enum CopyOptions { None, InApp, LocalDevice, CrossDevice }
declare enum WordBreak { NORMAL, BREAK_ALL, BREAK_WORD }
declare enum LineBreakStrategy { GREEDY, HIGH_QUALITY, BALANCED }
declare enum EnterKeyType { GO, SEARCH, SEND, NEXT, DONE }
declare enum ContentType { USER_NAME, PASSWORD, NEW_PASSWORD, NUMBER_PASSWORD, NUMBER }
declare enum TextAreaType { NORMAL = 0, NUMBER = 2, PHONE_NUMBER = 3, EMAIL = 5, URL = 13, ONE_TIME_CODE = 14 }

// Interfaces and types used as parameters
declare interface Font { size?: number | string | Resource; weight?: number | string | FontWeight; family?: string | Resource; style?: FontStyle }
declare interface FontFeature { fontFeature: string }
declare interface CaretStyle { width?: number | string | Resource; color?: ResourceColor; cursorColor?: ResourceColor; cursorWidth?: number | string | Resource; cursorStyle?: number }
declare interface ChangeValueInfo { value: string; previewText?: string }
declare interface InsertValue { insertValue: string; previewText?: string }
declare interface DeleteValue { deleteValue: string; previewText?: string }
declare interface PasteEvent { pasteEvent: string }
declare interface SubmitEvent { eventNumber: number }
declare interface EditMenuOptions { creation?: any; response?: any }
declare interface TextAreaOptions { placeholder?: string | Resource; text?: string | Resource; controller?: any }
declare interface InputCounterOptions { highlightBorder?: boolean; thresholdPercentage?: number; counterTextColor?: ResourceColor; counterTextOverflowColor?: ResourceColor; direction?: number; borderStyle?: any }
declare interface MaxLinesOptions { value?: number; overflowMode?: number }
declare interface LineSpacingOptions { value?: number | string | Resource; onlyBetweenLines?: boolean }
declare interface ColorMetrics { color: ResourceColor }
declare interface IMEClient { attach?: any; detach?: any }

// Ark* internal types for TextArea
declare class ArkTextAreaFilter { value?: ResourceStr; error?: (value: string) => void; filter?: any; isEqual(another: ArkTextAreaFilter): boolean }
// Additional types
type SelectedDragPreviewStyle = any
type ComponentContent = any
declare interface TextAttribute {}

// ArkTextComponent and ArkImageComponent are defined in ArkText.ts / ArkImage.ts

// Missing types for ArkColumn
declare interface PointLightStyle {
  lightSource?: { positionX?: Dimension; positionY?: Dimension; positionZ?: Dimension; intensity?: number; color?: ResourceColor };
  illuminated?: number;
  bloom?: number;
}
declare enum FlexAlign { Start, Center, End, SpaceBetween, SpaceAround, SpaceEvenly }

// Missing types for ArkDivider
declare enum LineCapStyle { BUTT = 0, ROUND = 1, SQUARE = 2 }

// Missing types for ArkFlex
declare enum FlexDirection { Row, Column, RowReverse, ColumnReverse }
declare enum FlexWrap { NoWrap, Wrap, WrapReverse }
declare interface FlexSpaceOptions { main?: LengthMetrics; cross?: LengthMetrics }

// Missing types for ArkGridRow
declare interface GridRowColumnOption { xs?: number; sm?: number; md?: number; lg?: number; xl?: number; xxl?: number }
declare interface GutterOption { x?: number | GridRowColumnOption; y?: number | GridRowColumnOption }
declare interface BreakPoints { value?: Array<string>; reference?: number }

// Missing types for ArkScrollable
declare enum ContentClipMode { CLIP = 0, REVEAL = 1, NO_CLIP = 2 }
declare enum EdgeEffect { Spring, Fade, None }
declare interface EdgeEffectOptions { alwaysEnabled?: boolean; effectEdge?: number }
declare interface FadingEdgeOptions { fadingEdgeLength?: Dimension }
declare interface ScrollBarMargin { start?: Length; end?: Length }
// Missing types for ArkGrid
declare interface GridAttribute {}
declare interface ComputedBarAttribute {}
declare interface ItemDragInfo { x: number; y: number }
declare interface EditModeOptions {}
declare interface Scroller {}
declare enum GridDirection { Row = 0, Column = 1, RowReverse = 2, ColumnReverse = 3 }
declare enum GridItemAlignment { START = 0, CENTER = 1, END = 2 }
declare enum ItemFillPolicy { NONE = 0, TOP_LEFT = 1, FIXED_SPAN = 2 }
declare enum FocusWrapMode { DEFAULT = 0, INWARD = 1, FORWARD = 2 }
declare interface NestedScrollOptions { scrollForward?: number; scrollBackward?: number }
declare class GridLayoutOptions {
  regularSize?: Array<number>; irregularIndexes?: Array<number>;
  onGetIrregularSizeByIndex?: (index: number) => any;
  onGetRectByIndex?: (index: number) => any;
  onGetStartIndexByOffset?: (offset: number) => number;
  onGetStartIndexByIndex?: (index: number) => number;
}

// Missing types for ArkGridCol
declare interface GridColColumnOption { xs?: number; sm?: number; md?: number; lg?: number; xl?: number; xxl?: number }

// Missing types for ArkImage
declare enum ImageFit { Contain, Cover, Auto, Fill, ScaleDown, None }
declare enum ImageInterpolation { None, Low, Medium, High }
declare enum ImageRenderMode { Original, Template }
declare enum DynamicRangeMode { HIGH = 0, STANDARD = 1, RESTRICTED = 2 }
declare enum ImageRotateOrientation { AUTO = 0, RESPECT_EXIF = 1, IGNORE_EXIF = 2 }
declare type ImageRotateOrientaion = any
declare type AIImageQuality = any
declare type ResolutionQuality = any
declare enum ContentTransitionEffect { NONE = 0, FADE_IN = 1 }
declare type ColorFilter = any
declare type DrawingColorFilter = any
declare type DrawableDescriptor = any
declare type ImageContent = any

// Missing types for ArkImageAnimator
declare interface ImageFrameInfo { src?: string | Resource; width?: number; height?: number; top?: number; left?: number; duration?: number }
declare enum AnimationStatus { Initial, Running, Paused, Stopped }
declare enum FillMode { None, Forwards }

// Missing types for ArkImageSpan
declare interface TextBackgroundStyle { color?: ResourceColor; radius?: BorderRadiuses }
declare enum ImageSpanAlignment { TOP = 0, CENTER = 1, BOTTOM = 2, BASELINE = 3 }

// Missing types for ArkLinearIndicator
declare type LinearIndicatorStyle = any
declare type OnLinearIndicatorChangeCallback = any

// Missing types for ArkSpan
declare type ResponseRegion = any
declare interface FontConfigs { fontWeightConfigs?: FontWeightConfigs }
declare interface FontWeightConfigs { enableVariableFontWeight?: boolean; enableDeviceFontWeightCategory?: boolean }
declare enum TextCase { NORMAL = 0, LOWER_CASE = 1, UPPER_CASE = 2 }

// Missing types for ArkText
declare interface TextDataDetectorConfigParam {
  types?: any; onDetectResultUpdate?: (result: any) => void;
  color?: ResourceColor; enablePreviewMenu?: boolean;
  decoration?: { type?: TextDecorationType; color?: ResourceColor; style?: TextDecorationStyle };
}
declare interface MarqueeOptions {
  start?: boolean; fromStart?: boolean; step?: number; loop?: boolean | number;
  delay?: number; fadeout?: number; marqueeStartPolicy?: number; marqueeUpdatePolicy?: number; spacing?: number;
}
declare interface TextOptions {}
declare enum TextContentAlign { START = 0, CENTER = 1, END = 2, JUSTIFY = 3 }
declare enum TextSelectableMode { NONE = 0, SELECTABLE_ON = 1, SELECTABLE_OFF = 2 }
declare enum TextVerticalAlign { TOP = 0, CENTER = 1, BOTTOM = 2, BASELINE = 3 }
declare enum MarqueeState { RUNNING = 0, PAUSED = 1, FINISHED = 2, START_PENDING = 3, PAUSE_PENDING = 4, FINISH_PENDING = 5 }
declare enum IncrementalUpdatePolicy { NONE = 0, INCREMENTAL = 1, FULL = 2 }

// Missing types for ArkTextArea (additional)
declare enum JoinStyle { MITER = 0, ROUND = 1, BEVEL = 2 }

// Missing types for ArkTextInput
declare type KeyboardAppearance = string
declare interface UnderlineColor { normal?: ResourceColor; typing?: ResourceColor; error?: ResourceColor; disable?: ResourceColor }
declare interface PasswordIcon { onIconSrc?: string | Resource; offIconSrc?: string | Resource }
declare type CancelButtonStyle = string
declare type IconOptions = any
declare type TextInputController = any
declare type TextInputStyle = number

// Missing types for ArkVideo
declare type FullscreenInfo = any
declare type PreparedInfo = any
declare type PlaybackInfo = any
declare type ErrorCallback = any
declare type ImageAnalyzerConfig = any

// Missing types for ArkClassDefine.ts
declare type StyledString = any
declare type MenuAlignType = any
declare type Offset = any
declare type ScrollDirectionalLockType = any
declare type ScrollableBarModeOptions = any
declare type DividerStyle = any
declare type BarGridColumnOptions = any
declare type TabsCacheMode = any
declare type NestedScrollMode = any
declare type MaxLinesMode = any
declare class DotIndicator {}
declare class DigitIndicator {}
declare type ArrowStyle = any
declare type SwiperAutoFill = any
declare type PlaceholderStyle = any
declare type ScrollSnapAlign = any
declare type SymbolEffect = any
declare type TextDataDetectorType = any
declare type DragPreviewMode = any
declare type DraggingSizeChangeEffect = any
declare type GuideLinePosition = any
declare type BarrierDirection = any
declare type NavigationCommonTitle = any
declare type NavigationCustomTitle = any
declare type NavigationTitleOptions = any
declare type NavigationMenuItem = any
declare type NavigationMenuOptions = any
declare type ToolbarItem = any
declare type NavigationToolbarOptions = any

// Missing types for ArkParticle
declare type DisturbanceFieldOptions = any
declare type EmitterProperty = any
declare type RippleFieldOptions = any
declare type VelocityFieldOptions = any


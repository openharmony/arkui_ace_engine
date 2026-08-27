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
declare interface Resource {
  bundleName: string;
  moduleName: string;
  id: number;
  params?: Array<string | number | Resource>;
  type?: number;
}
type ResourceColor = number | Color | string | Resource;
type Length = string | number | Resource | LengthMetrics;
declare interface EdgeWidths {
  top?: Length | LengthMetrics;
  right?: Length | LengthMetrics;
  bottom?: Length | LengthMetrics;
  left?: Length | LengthMetrics;
  start?: Length | LengthMetrics;
  end?: Length | LengthMetrics;
}
declare interface LocalizedEdgeWidths {
  top?: LengthMetrics;
  end?: LengthMetrics;
  bottom?: LengthMetrics;
  start?: LengthMetrics;
  left?: LengthMetrics;
  right?: LengthMetrics;
}
declare interface LocalizedBorderRadius {
  topStart?: LengthMetrics;
  topEnd?: LengthMetrics;
  bottomStart?: LengthMetrics;
  bottomEnd?: LengthMetrics;
}
declare enum RenderStrategy {
  NORMAL = 0,
  COMPONENT = 1,
}
declare interface BorderRadiuses {
  topLeft?: Length;
  topRight?: Length;
  bottomLeft?: Length;
  bottomRight?: Length;
}
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
  END = 10,
}
declare interface EdgeColors {
  top?: ResourceColor;
  right?: ResourceColor;
  bottom?: ResourceColor;
  left?: ResourceColor;
}
declare interface LocalizedEdgeColors {
  top?: ResourceColor;
  end?: ResourceColor;
  bottom?: ResourceColor;
  start?: ResourceColor;
}
declare type Matrix4Transit = any;
declare enum BorderStyle {
  DOTTED = 2,
  DASHED = 1,
  SOLID = 0,
}
declare interface EdgeStyles {
  top?: BorderStyle;
  right?: BorderStyle;
  bottom?: BorderStyle;
  left?: BorderStyle;
}
declare interface ShadowOptions {
  radius?: number | Resource;
  type?: ShadowType;
  color?: Color | string | Resource | ColoringStrategy;
  offsetX?: number | Resource;
  offsetY?: number | Resource;
  fill?: boolean;
  shadowStyle?: number;
}
declare enum ShadowType {
  COLOR = 0,
  BLUR = 1,
}
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
  COSINE = 9,
}
declare interface BlurOptions {
  low?: number;
  high?: number;
  threshold?: number;
  thresholdRange?: number;
  grayscale?: number;
  direction?: number;
  style?: number;
}
declare interface InvertOptions {
  low: number;
  high: number;
  threshold: number;
  thresholdRange: number;
}
declare class LengthMetrics {
  unit: number;
  value: number;
}
declare interface NavigationInfo {}
type KNode = number | null;
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
  Transparent = 11,
}
declare enum RepeatMode {
  Repeat,
  Stretch,
  Round,
  Space,
}
declare interface LinearGradient {
  angle?: number | string;
  direction?: GradientDirection;
  colors: Array<[ResourceColor, number]>;
  repeating?: boolean;
}
declare interface BorderImageOption {
  slice?: Length | EdgeWidths | LocalizedEdgeWidths;
  repeat?: RepeatMode;
  source?: string | Resource | LinearGradient;
  width?: Length | EdgeWidths | LocalizedEdgeWidths;
  outset?: Length | EdgeWidths | LocalizedEdgeWidths;
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
  DOTTED = 2,
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
  BOTTOM_END = 8,
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
  AUTO = 2,
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
declare type PixelMap = any;
declare type Blender = any;
declare enum EffectType {
  DEFAULT = 0,
  WINDOW_EFFECT = 1,
}
declare interface PixelStretchEffectOptions {
  top?: Length;
  bottom?: Length;
  left?: Length;
  right?: Length;
}
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
declare enum ColoringStrategy {
  INVERT = 'invert',
  AVERAGE = 'average',
  PRIMARY = 'primary',
}
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
type CustomBuilder = () => void;
declare interface DragItemInfo {
  pixelMap?: PixelMap;
  builder?: CustomBuilder;
  extraInfo?: string;
}
declare interface TouchEvent {
  type: number;
  touches: TouchList;
  changedTouches: TouchList;
  stopPropagation(): void;
  preventDefault(): void;
  getHistoricalPoints(): Array<any> | undefined;
}
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
declare interface TouchList extends Array<TouchObject> {}
declare namespace unifiedData {
  class UnifiedData {}
  class DataLoadParams {}
}
declare function getUINativeModule(): any;
type int32 = number;
type VoidCallback = () => void;
type Optional<T> = T | undefined;
type ResourceStr = string | Resource;
declare class BusinessError extends Error {
  code: number | string;
  constructor(code: number | string, message: string);
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
  COMPONENT_ULTRA_THICK = 12,
}
declare enum BlendMode {
  NONE = 0, CLEAR = 1, SRC = 2, DST = 3, SRC_OVER = 4, DST_OVER = 5,
  SRC_IN = 6, DST_IN = 7, SRC_OUT = 8, DST_OUT = 9, SRC_ATOP = 10, DST_ATOP = 11,
  XOR = 12, PLUS = 13, MODULATE = 14, SCREEN = 15, OVERLAY = 16, DARKEN = 17,
  LIGHTEN = 18, COLOR_DODGE = 19, COLOR_BURN = 20, HARD_LIGHT = 21, SOFT_LIGHT = 22,
  DIFFERENCE = 23, EXCLUSION = 24, MULTIPLY = 25, HUE = 26, SATURATION = 27,
  COLOR = 28, LUMINOSITY = 29
}
declare enum BlendApplyType {
  FAST = 0,
  OFFSCREEN = 1,
}
declare enum Axis {
  Vertical,
  Horizontal,
}
declare enum Direction {
  Ltr,
  Rtl,
  Auto,
}
declare enum HorizontalAlign {
  Start,
  Center,
  End,
}
declare enum VerticalAlign {
  Top,
  Center,
  Bottom,
}
declare enum ItemAlign { Auto, Start, Center, End, Baseline, Stretch }
declare enum Visibility {
  Visible,
  Hidden,
  None,
}
declare enum ImageRepeat {
  NoRepeat,
  X,
  Y,
  XY,
}
declare enum ChainStyle {
  SPREAD,
  SPREAD_INSIDE,
  PACKED,
}
declare enum ModalTransition {
  DEFAULT = 0,
  NONE = 1,
  ALPHA = 2,
}
declare enum BlurStyleActivePolicy {
  FOLLOWS_WINDOW_ACTIVE_STATE = 0,
  ALWAYS_ACTIVE = 1,
  ALWAYS_INACTIVE = 2,
}
declare enum ThemeColorMode {
  SYSTEM = 0,
  LIGHT = 1,
  DARK = 2,
}
declare enum AdaptiveColor {
  DEFAULT = 0,
  AVERAGE = 1,
}
declare enum SafeAreaType {
  SYSTEM = 0,
  CUTOUT = 1,
  KEYBOARD = 2,
}
declare enum SafeAreaEdge {
  TOP = 0,
  BOTTOM = 1,
  START = 2,
  END = 3,
}
declare enum LayoutSafeAreaEdge { TOP = 0, BOTTOM = 1, START = 2, END = 3, VERTICAL = 4, HORIZONTAL = 5, ALL = 6 }
declare enum HoverEffect {
  Auto,
  Scale,
  Highlight,
  None,
}
declare enum HitTestMode { Default, Block, Transparent, None, BLOCK_HIERARCHY, BLOCK_DESCENDANTS }
declare enum ResponseType {
  RightClick,
  LongPress,
}
declare enum RenderFit {
  CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4,
  TOP_LEFT = 5, TOP_RIGHT = 6, BOTTOM_LEFT = 7, BOTTOM_RIGHT = 8,
  RESIZE_FILL = 9, RESIZE_CONTAIN = 10, RESIZE_CONTAIN_TOP_LEFT = 11,
  RESIZE_CONTAIN_BOTTOM_RIGHT = 12, RESIZE_COVER = 13,
  RESIZE_COVER_TOP_LEFT = 14, RESIZE_COVER_BOTTOM_RIGHT = 15
}
declare enum ObscuredReasons {
  PLACEHOLDER = 0,
}
declare enum FunctionKey {
  ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, TAB,
  DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT
}
declare enum ModifierKey {
  CTRL,
  SHIFT,
  ALT,
}
declare enum PreDragStatus {
  ACTION_DETECTING_STATUS = 0,
  READY_TO_TRIGGER_DRAG_ACTION = 1,
  PREVIEW_LIFT_STARTED = 2,
  PREVIEW_LIFT_FINISHED = 3,
  PREVIEW_LANDING_STARTED = 4,
  PREVIEW_LANDING_FINISHED = 5,
  ACTION_CANCELED_BEFORE_DRAG = 6,
  PREPARING_FOR_DRAG_DETECTION = 7,
}
declare enum ScrollState {
  Idle,
  Scroll,
  Fling,
}
declare enum ScrollSource {
  DRAG = 0,
  FLING,
  EDGE_EFFECT,
  OTHER_USER_INPUT,
  SCROLL_BAR,
  SCROLL_BAR_FLING,
  SCROLLER,
  SCROLLER_ANIMATION,
}
declare enum FocusDrawLevel {
  SELF = 0,
  TOP = 1,
}
declare enum LocalizedAlignment {
  TOP_START = 'top_start',
  TOP = 'top',
  TOP_END = 'top_end',
  START = 'start',
  CENTER = 'center',
  END = 'end',
  BOTTOM_START = 'bottom_start',
  BOTTOM = 'bottom',
  BOTTOM_END = 'bottom_end',
}
declare enum GestureMask {
  Normal,
  IgnoreInternal,
}
declare enum GesturePriority {
  NORMAL = 0,
  PRIORITY = 1,
  PARALLEL = 2,
}
declare enum GestureJudgeResult {
  CONTINUE = 0,
  REJECT = 1,
}
declare enum GestureMode {
  Sequence,
  Parallel,
  Exclusive,
}
declare enum PanDirection { None, Horizontal, Left, Right, Vertical, Up, Down, All }
declare enum SwipeDirection {
  None,
  Horizontal,
  Vertical,
  All,
}
declare enum AccessibilitySamePageMode {
  SEMI_SILENT = 0,
  FULL_SILENT = 1,
}
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
declare interface Rectangle {
  x?: Length;
  y?: Length;
  width?: Length;
  height?: Length;
}
declare interface Area {
  width: Length;
  height: Length;
  position: Position;
  globalPosition: Position;
}
declare interface OffsetResult {
  xOffset: number;
  yOffset: number;
}
declare interface Callback<T, V = void> {
  (data: T): V;
}
declare interface AnimateParam {
  duration?: number;
  tempo?: number;
  curve?: Curve | string | ICurve;
  delay?: number;
  iterations?: number;
  playMode?: PlayMode;
  onFinish?: () => void;
}
declare interface ICurve {
  interpolate(fraction: number): number;
}
declare enum Curve {
  Linear, Ease, EaseIn, EaseOut, EaseInOut, FastOutSlowIn,
  LinearOutSlowIn, FastOutLinearIn, ExtremeDeceleration, Sharp, Rhythm, Smooth, Friction
}
declare enum PlayMode {
  Normal,
  Reverse,
  Alternate,
  AlternateReverse,
}
declare enum TransitionType {
  All,
  Insert,
  Delete,
}
declare interface TransitionOptions {
  type?: TransitionType;
  opacity?: number;
  translate?: TranslateOptions;
  scale?: ScaleOptions;
  rotate?: RotateOptions;
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
declare enum TransitionEdge {
  TOP = 0,
  BOTTOM = 1,
  START = 2,
  END = 3,
}
declare interface MotionPathOptions {
  path: string;
  from?: number;
  to?: number;
  rotatable?: boolean;
}
declare interface MotionBlurOptions {
  radius: number;
  anchor: { x: number; y: number };
}
declare interface sharedTransitionOptions {
  duration?: number;
  curve?: Curve | string | ICurve;
  delay?: number;
  motionPath?: MotionPathOptions;
  zIndex?: number;
  type?: SharedTransitionEffectType;
}
declare enum SharedTransitionEffectType {
  Static,
  Exchange,
}
declare interface ConstraintSizeOptions {
  minWidth?: Length;
  maxWidth?: Length;
  minHeight?: Length;
  maxHeight?: Length;
}
declare interface SizeChangeCallback {
  (oldValue: SizeOptions, newValue: SizeOptions): void;
}
declare interface AlignRuleOption {
  left?: { anchor: string; align: HorizontalAlign };
  right?: { anchor: string; align: HorizontalAlign };
  middle?: { anchor: string; align: HorizontalAlign };
  top?: { anchor: string; align: VerticalAlign };
  bottom?: { anchor: string; align: VerticalAlign };
  center?: { anchor: string; align: VerticalAlign };
  bias?: { horizontal?: number; vertical?: number };
}
declare type Padding = any;
declare interface LocalizedPadding {
  top?: LengthMetrics;
  end?: LengthMetrics;
  bottom?: LengthMetrics;
  start?: LengthMetrics;
}
declare type Margin = Padding;
declare type LocalizedMargin = LocalizedPadding;
declare interface LocalizedPosition {
  start?: LengthMetrics;
  top?: LengthMetrics;
}
declare interface LocalizedBorderRadiuses {
  topStart?: LengthMetrics;
  topEnd?: LengthMetrics;
  bottomStart?: LengthMetrics;
  bottomEnd?: LengthMetrics;
}
declare interface BorderOptions {
  width?: EdgeWidths | Length | LocalizedEdgeWidths;
  color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
  radius?: BorderRadiuses | Length | LocalizedBorderRadiuses;
  style?: EdgeStyles | BorderStyle;
  dashGap?: EdgeWidths | Length | LocalizedEdgeWidths;
  dashWidth?: EdgeWidths | Length | LocalizedEdgeWidths;
}
declare interface BackgroundOptions {
  align?: Alignment;
  ignoresLayoutSafeAreaEdges?: Array<LayoutSafeAreaEdge>;
}
declare interface BackgroundImageOptions {
  syncLoad?: boolean;
  repeat?: ImageRepeat;
}
declare interface BackgroundBlurStyleOptions extends BlurStyleOptions {
  policy?: BlurStyleActivePolicy;
  inactiveColor?: ResourceColor;
  type?: number;
}
declare interface ForegroundBlurStyleOptions extends BlurStyleOptions {}
declare interface BlurStyleOptions {
  colorMode?: ThemeColorMode;
  adaptiveColor?: AdaptiveColor;
  scale?: number;
  blurOptions?: BlurOptions;
}
declare interface SystemAdaptiveOptions {
  disableSystemAdaptation?: boolean;
}
declare interface BackgroundEffectOptions {
  radius: number; saturation?: number; brightness?: number; color?: ResourceColor;
  adaptiveColor?: AdaptiveColor; blurOptions?: BlurOptions; policy?: BlurStyleActivePolicy;
  inactiveColor?: ResourceColor; type?: number; disableSystemAdaptation?: boolean;
}
declare interface ForegroundEffectOptions {
  radius: number;
}
declare interface BackgroundBrightnessOptions {
  rate: number;
  lightUpDegree: number;
}
declare interface LinearGradientBlurOptions {
  fractionStops: FractionStop[];
  direction: GradientDirection;
}
declare interface PixelRoundPolicy {
  start?: number;
  top?: number;
  end?: number;
  bottom?: number;
}
declare interface ClickEffect {
  level: number;
  scale?: number;
}
declare interface ChainWeightOptions {
  horizontal?: number;
  vertical?: number;
}
declare interface AttributeModifier<T> {
  attribute?: T;
  modifierState?: number;
  isAttributeUpdater?: boolean;
  applyNormalAttribute?(instance: T): void;
  applyPressedAttribute?(instance: T): void;
  applyFocusedAttribute?(instance: T): void;
  applyDisabledAttribute?(instance: T): void;
  applySelectedAttribute?(instance: T): void;
  applyHoveredAttribute?(instance: T): void;
  initializeModifier?(attribute: T): void;
  onComponentChanged?(after: T): void;
}
declare class CommonAttribute {}
declare interface CommonConfiguration<T> {
  enabled: boolean;
  contentModifier: ContentModifier<T>;
}
declare type VisualEffect = any;
declare class WrappedBuilder<Args extends Object[]> {
  builder: (...args: Args) => void;
  constructor(builder: (...args: Args) => void);
}
declare type BuilderNode<T = any> = any;
declare interface ContentModifier<T> {
  applyContent(): WrappedBuilder<[T]>;
}
declare type UIContext = any;
declare type FrameNode = any;
declare interface DividerStyleOptions {
  strokeWidth?: LengthMetrics;
  color?: ResourceColor;
  startMargin?: LengthMetrics;
  endMargin?: LengthMetrics;
  mode?: any;
}
declare enum Edge {
  Top,
  Center,
  Bottom,
  Baseline,
  Start,
  Middle,
  End,
}
declare type ESObject = any;
declare type NavDestinationActiveReason = any;
declare type NavDestinationAttribute = any;
declare interface NavDestinationContext {
  pathInfo: any;
  pathStack: any;
  navDestinationId?: string;
  mode?: any;
  getConfigInRouteMap(): any | undefined;
}
declare type NavDestinationInactiveReason = any;
declare interface NestedScrollInfo {
  parent: Scroller;
  child: Scroller;
}
declare interface OffsetOptions {
  xOffset?: Dimension;
  yOffset?: Dimension;
}
declare type ScrollAttribute = any;
declare enum ScrollDirection {
  Vertical,
  Horizontal,
  Free,
  None,
  FREE = 4,
}
declare interface ScrollSnapOptions {
  snapAlign: ScrollSnapAlign;
  snapPagination?: Dimension | Array<Dimension>;
  enableSnapToStart?: boolean;
  enableSnapToEnd?: boolean;
}
declare type SystemBarStyle = any;
declare enum VisibilityChangeReason {
  TRANSITION = 0,
  CONTENT_COVER = 1,
  APP_STATE = 2,
}
declare class NavDestinationOnNewParamModifier extends ModifierWithKey<any> {
  static identity: symbol;
}
declare type Filter = any;
declare type UniformDataType = string;
declare type BrightnessOptions = any;
declare type SystemUiMaterial = any;
declare class ProgressMask {
  constructor(value: number, total: number, color: ResourceColor);
  updateProgress(value: number): void;
  updateColor(value: ResourceColor): void;
  enableBreathingAnimation(value: boolean): void;
}
declare type TipsMessageType = ResourceStr | any;
declare type OnScrollVisibleContentChangeCallback = (start: any, end: any) => void;
declare class ViewStackProcessor {
  static GetElmtIdToAccountFor(): void;
}
declare class JsPointerClass {
  invalid(): boolean;
}
declare class ModifierJS {
  [key: string]: Function & { new (...args: any[]): any };
}
declare interface FocusBoxStyle {
  margin?: any;
  strokeColor?: any;
  strokeWidth?: any;
}
declare interface FocusMovement { forward?: string; backward?: string; up?: string; down?: string; left?: string; right?: string; }
declare interface KeyEvent {
  type: number; keyCode: number; keyText: string; keySource: number; deviceId: number;
  metaKey: number; timestamp: number; stopPropagation: () => void; unicode?: number;
}
declare interface HoverEvent {
  x?: number;
  y?: number;
  windowX?: number;
  windowY?: number;
  displayX?: number;
  displayY?: number;
  stopPropagation: () => void;
}
declare interface HoverMoveEvent extends HoverEvent {}
declare interface MouseEvent {
  button: number; action: number; displayX: number; displayY: number;
  windowX: number; windowY: number; screenX: number; screenY: number;
  x: number; y: number; stopPropagation: () => void;
}
declare interface AxisEvent {
  action: number;
  displayX: number;
  displayY: number;
  windowX: number;
  windowY: number;
  x: number;
  y: number;
}
declare interface FocusAxisEvent {
  axisMap: Map<any, number>;
  stopPropagation: Callback<void>;
}
declare interface StateStyles { normal?: any; pressed?: any; disabled?: any; focused?: any; clicked?: any; selected?: object; }
declare interface PopupOptions {
  message: string;
  placementOnTop?: boolean;
  placement?: Placement;
  primaryButton?: { value: string; action: () => void };
  secondaryButton?: { value: string; action: () => void };
  onStateChange?: (event: { isVisible: boolean }) => void;
  arrowOffset?: Length;
  showInSubWindow?: boolean;
}
declare enum Placement { Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight, LeftTop, LeftBottom, RightTop, RightBottom }
declare interface CustomPopupOptions {
  builder: CustomBuilder;
  placement?: Placement;
  popupColor?: Color | string | Resource | number;
  enableArrow?: boolean;
  autoCancel?: boolean;
}
declare interface TipsOptions {
  appearingTime?: number;
  disappearingTime?: number;
  appearingTimeWithContinuousOperation?: number;
  disappearingTimeWithContinuousOperation?: number;
  enableArrow?: boolean;
  arrowPointPosition?: any;
  arrowWidth?: Dimension;
  arrowHeight?: Dimension;
  showAtAnchor?: any;
}
declare interface MenuElement {
  value: ResourceStr;
  icon?: ResourceStr;
  enabled?: boolean;
  action: () => void;
}
declare interface MenuOptions extends ContextMenuOptions {
  title?: ResourceStr;
  showInSubWindow?: boolean;
}
declare interface ContextMenuOptions {
  offset?: Position;
  placement?: Placement;
  enableArrow?: boolean;
  arrowOffset?: Length;
  preview?: any;
  previewBorderRadius?: any;
  borderRadius?: any;
  onAppear?: () => void;
  onDisappear?: () => void;
}
declare interface ContentCoverOptions {
  modalTransition?: ModalTransition;
  transition?: TransitionEffect;
  enableSafeArea?: boolean;
}
declare interface SheetOptions extends BindOptions {
  height?: any;
  dragBar?: boolean;
  modalTransition?: ModalTransition;
  maskColor?: ResourceColor;
  preferType?: any;
  mode?: any;
}
declare interface BindOptions {
  backgroundColor?: ResourceColor;
  onAppear?: () => void;
  onDisappear?: () => void;
  onWillAppear?: () => void;
  onWillDisappear?: () => void;
}
declare interface DragPreviewOptions {
  mode?: any;
  modifier?: any;
  numberBadge?: boolean | number;
  sizeChangeEffect?: any;
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
declare interface DropOptions {
  disableDataPrefetch?: boolean;
}
declare interface VisibleAreaEventOptions {
  ratios: Array<number>;
  expectedUpdateInterval?: number;
  measureFromViewport?: boolean;
}
declare type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: number) => void;
declare type TouchTestDoneCallback = (event: BaseGestureEvent, recognizers: Array<GestureRecognizer>) => void;
declare type GestureRecognizerJudgeBeginCallback = (
  event: BaseGestureEvent,
  current: GestureRecognizer,
  recognizers: Array<GestureRecognizer>
) => GestureJudgeResult;
declare type AccessibilityFocusCallback = (isFocus: boolean) => void;
declare type AccessibilityActionInterceptCallback = (action: any) => any;
declare type AccessibilityTransparentCallback = (event: TouchEvent) => void;
declare interface GestureInfo {
  tag?: string;
  type: any;
  isSystemGesture: boolean;
}
interface BaseGestureEvent {
  fingerList: any[];
}
interface GestureEvent extends BaseGestureEvent { repeat: boolean; offsetX: number; offsetY: number; angle: number; speed: number; scale: number; }
declare type GestureType =
  | TapGestureInterface
  | LongPressGestureInterface
  | PanGestureInterface
  | PinchGestureInterface
  | SwipeGestureInterface
  | RotationGestureInterface
  | GestureGroupInterface;
interface TapGestureInterface {
  (value?: any): TapGestureInterface;
  onAction(event: (event: GestureEvent) => void): TapGestureInterface;
  tag(tag: string): TapGestureInterface;
}
interface LongPressGestureInterface {
  (value?: any): LongPressGestureInterface;
  onAction(event: (event: GestureEvent) => void): LongPressGestureInterface;
  onActionEnd(event: (event: GestureEvent) => void): LongPressGestureInterface;
  onActionCancel(event: () => void): LongPressGestureInterface;
  tag(tag: string): LongPressGestureInterface;
}
interface PanGestureInterface { (value?: any): PanGestureInterface; onActionStart(event: (event: GestureEvent) => void): PanGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): PanGestureInterface; onActionEnd(event: (event: GestureEvent) => void): PanGestureInterface; onActionCancel(event: () => void): PanGestureInterface; tag(tag: string): PanGestureInterface; }
interface SwipeGestureInterface {
  (value?: any): SwipeGestureInterface;
  onAction(event: (event: GestureEvent) => void): SwipeGestureInterface;
  tag(tag: string): SwipeGestureInterface;
}
interface PinchGestureInterface { (value?: any): PinchGestureInterface; onActionStart(event: (event: GestureEvent) => void): PinchGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): PinchGestureInterface; onActionEnd(event: (event: GestureEvent) => void): PinchGestureInterface; onActionCancel(event: () => void): PinchGestureInterface; tag(tag: string): PinchGestureInterface; }
interface RotationGestureInterface { (value?: any): RotationGestureInterface; onActionStart(event: (event: GestureEvent) => void): RotationGestureInterface; onActionUpdate(event: (event: GestureEvent) => void): RotationGestureInterface; onActionEnd(event: (event: GestureEvent) => void): RotationGestureInterface; onActionCancel(event: () => void): RotationGestureInterface; tag(tag: string): RotationGestureInterface; }
interface GestureGroupInterface {
  (mode: GestureMode, ...gesture: GestureType[]): GestureGroupInterface;
  onCancel(event: () => void): GestureGroupInterface;
}
declare interface GestureModifier {
  applyGesture(event: UIGestureEvent): void;
}
declare interface UIGestureEvent {
  addGesture<T>(gesture: any, priority?: GesturePriority, mask?: GestureMask): void;
  addParallelGesture<T>(gesture: any, mask?: GestureMask): void;
  removeGestureByTag(tag: string): void;
  clearGestures(): void;
}
declare class GestureRecognizer {
  getTag(): string;
  getType(): any;
  isBuiltIn(): boolean;
  setEnabled(isEnabled: boolean): void;
  isEnabled(): boolean;
}
declare class TouchRecognizer {
  getEventTargetInfo(): any;
  cancelTouch(): void;
}
declare class TouchTestInfo { windowX: number; windowY: number; parentX: number; parentY: number; x: number; y: number; id: string; }
declare class TouchResult {
  strategy: number;
  id?: string;
}
declare class CommonShapeMethod<T> {
  stroke(value: ResourceColor): T;
  fill(value: ResourceColor): T;
  strokeWidth(value: Length): T;
  antiAlias(value: boolean): T;
}
declare class CircleAttribute extends CommonShapeMethod<CircleAttribute> {}
declare class EllipseAttribute extends CommonShapeMethod<EllipseAttribute> {}
declare class PathAttribute extends CommonShapeMethod<PathAttribute> {}
declare class RectAttribute extends CommonShapeMethod<RectAttribute> {}
declare type CircleShape = any;
declare type EllipseShape = any;
declare type PathShape = any;
declare type RectShape = any;
declare enum SourceTool { Unknown, Finger, Pen, MOUSE, TOUCHPAD, JOYSTICK }
interface BaseHandlerOptions {
  isFingerCountLimited?: boolean;
}
interface TapGestureHandlerOptions extends BaseHandlerOptions {
  count?: number;
  fingers?: number;
  distanceThreshold?: number;
}
interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
  fingers?: number;
  repeat?: boolean;
  duration?: number;
  allowableMovement?: number;
}
interface PanGestureHandlerOptions extends BaseHandlerOptions {
  fingers?: number;
  direction?: PanDirection;
  distance?: number;
  distanceMap?: Map<SourceTool, number>;
}
interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
  fingers?: number;
  direction?: SwipeDirection;
  speed?: number;
}
interface PinchGestureHandlerOptions extends BaseHandlerOptions {
  fingers?: number;
  distance?: number;
}
interface RotationGestureHandlerOptions extends BaseHandlerOptions {
  fingers?: number;
  angle?: number;
}
interface GestureGroupGestureHandlerOptions {
  mode: GestureMode;
  gestures: any[];
}
declare enum FontWeight {
  Lighter,
  Normal,
  Regular,
  Medium,
  Bold,
  Bolder,
}
declare enum SymbolRenderingStrategy {
  SINGLE = 0,
  MULTIPLE_COLOR = 1,
  MULTIPLE_OPACITY = 2,
}
declare enum SymbolEffectStrategy {
  NONE = 0,
  SCALE = 1,
  HIERARCHICAL = 2,
}
declare enum FontStyle {
  Normal,
  Italic,
}
declare enum TextAlign {
  START,
  CENTER,
  END,
}
declare enum TextOverflow {
  None,
  Clip,
  Ellipsis,
  Marquee,
}
declare enum TextDecorationType {
  None,
  Underline,
  Overline,
  LineThrough,
}
declare enum TextDecorationStyle {
  SOLID,
  DOUBLE,
  DOTTED,
  DASHED,
  WAVY,
}
declare enum TextDirection {
  LTR,
  RTL,
  Auto,
}
declare enum TextHeightAdaptivePolicy {
  MAX_LINES,
  MIN_FONT_SIZE,
  FONT_SIZE_ADJUST,
}
declare enum BarState {
  Off,
  Auto,
  On,
}
declare enum EllipsisMode {
  HEAD,
  MIDDLE,
  TAIL,
}
declare enum CopyOptions {
  None,
  InApp,
  LocalDevice,
  CrossDevice,
}
declare enum WordBreak {
  NORMAL,
  BREAK_ALL,
  BREAK_WORD,
}
declare enum LineBreakStrategy {
  GREEDY,
  HIGH_QUALITY,
  BALANCED,
}
declare enum EnterKeyType {
  GO,
  SEARCH,
  SEND,
  NEXT,
  DONE,
}
declare interface Font {
  size?: number | string | Resource;
  weight?: number | string | FontWeight;
  family?: string | Resource;
  style?: FontStyle;
}
declare interface FontFeature {
  fontFeature: string;
}
declare interface CaretStyle {
  width?: number | string | Resource;
  color?: ResourceColor;
  cursorColor?: ResourceColor;
  cursorWidth?: number | string | Resource;
  cursorStyle?: number;
}
declare interface ChangeValueInfo {
  value: string;
  previewText?: string;
}
declare interface InsertValue {
  insertValue: string;
  previewText?: string;
}
declare interface DeleteValue {
  deleteValue: string;
  previewText?: string;
}
declare interface PasteEvent {
  pasteEvent: string;
}
declare interface SubmitEvent {
  eventNumber: number;
}
declare interface EditMenuOptions {
  creation?: any;
  response?: any;
}
declare interface InputCounterOptions {
  highlightBorder?: boolean;
  thresholdPercentage?: number;
  counterTextColor?: ResourceColor;
  counterTextOverflowColor?: ResourceColor;
  direction?: number;
  borderStyle?: any;
}
declare interface LineSpacingOptions {
  value?: number | string | Resource;
  onlyBetweenLines?: boolean;
}
declare interface ColorMetrics {
  color: ResourceColor;
}
declare interface IMEClient {
  attach?: any;
  detach?: any;
}
declare interface SelectedDragPreviewStyle {
  color?: ResourceColor;
}
declare type ComponentContent<T = Object> = any;
declare interface TextAttribute {}
declare interface PointLightStyle {
  lightSource?: {
    positionX?: Dimension;
    positionY?: Dimension;
    positionZ?: Dimension;
    intensity?: number;
    color?: ResourceColor;
  };
  illuminated?: number;
  bloom?: number;
}
declare enum FlexAlign {
  Start,
  Center,
  End,
  SpaceBetween,
  SpaceAround,
  SpaceEvenly,
}
declare enum FlexDirection {
  Row,
  Column,
  RowReverse,
  ColumnReverse,
}
declare enum FlexWrap {
  NoWrap,
  Wrap,
  WrapReverse,
}
declare interface FlexSpaceOptions {
  main?: LengthMetrics;
  cross?: LengthMetrics;
}
declare enum ContentClipMode {
  CLIP = 0,
  REVEAL = 1,
  NO_CLIP = 2,
}
declare enum EdgeEffect {
  Spring,
  Fade,
  None,
}
declare interface EdgeEffectOptions {
  alwaysEnabled?: boolean;
  effectEdge?: number;
}
declare interface FadingEdgeOptions {
  fadingEdgeLength?: Dimension;
}
declare interface ScrollBarMargin {
  start?: Length;
  end?: Length;
}
declare interface ItemDragInfo {
  x: number;
  y: number;
}
declare interface EditModeOptions {}
declare interface Scroller {}
declare enum FocusWrapMode {
  DEFAULT = 0,
  INWARD = 1,
  FORWARD = 2,
}
declare interface NestedScrollOptions {
  scrollForward?: number;
  scrollBackward?: number;
}
declare enum ImageFit {
  Contain,
  Cover,
  Auto,
  Fill,
  ScaleDown,
  None,
}
declare enum ImageInterpolation {
  None,
  Low,
  Medium,
  High,
}
declare enum ImageRenderMode {
  Original,
  Template,
}
declare enum DynamicRangeMode {
  HIGH = 0,
  STANDARD = 1,
  RESTRICTED = 2,
}
declare enum ImageRotateOrientation {
  AUTO = 0,
  RESPECT_EXIF = 1,
  IGNORE_EXIF = 2,
}
declare type ImageRotateOrientaion = any;
declare type AIImageQuality = any;
declare type ResolutionQuality = any;
declare enum ContentTransitionEffect {
  NONE = 0,
  FADE_IN = 1,
}
declare class ColorFilter {
  constructor(value: number[]);
}
declare type DrawingColorFilter = any;
declare type DrawableDescriptor = any;
declare enum ImageContent {
  EMPTY = 0,
}
declare interface TextBackgroundStyle {
  color?: ResourceColor;
  radius?: BorderRadiuses;
}
declare type LinearIndicatorStyle = any;
declare type OnLinearIndicatorChangeCallback = any;
declare interface ResponseRegion {
  tool?: any;
  x?: LengthMetrics;
  y?: LengthMetrics;
  width?: LengthMetrics | string;
  height?: LengthMetrics | string;
}
declare interface FontConfigs {
  fontWeightConfigs?: FontWeightConfigs;
}
declare interface FontWeightConfigs {
  enableVariableFontWeight?: boolean;
  enableDeviceFontWeightCategory?: boolean;
}
declare enum TextCase {
  NORMAL = 0,
  LOWER_CASE = 1,
  UPPER_CASE = 2,
}
declare interface MarqueeOptions {
  start?: boolean;
  fromStart?: boolean;
  step?: number;
  loop?: boolean | number;
  src?: string;
  delay?: number;
  fadeout?: number;
  marqueeStartPolicy?: number;
  marqueeUpdatePolicy?: number;
  spacing?: number;
}
declare interface TextOptions {}
declare enum TextContentAlign {
  START = 0,
  CENTER = 1,
  END = 2,
  JUSTIFY = 3,
}
declare enum TextSelectableMode {
  NONE = 0,
  SELECTABLE_ON = 1,
  SELECTABLE_OFF = 2,
}
declare enum TextVerticalAlign {
  TOP = 0,
  CENTER = 1,
  BOTTOM = 2,
  BASELINE = 3,
}
declare enum MarqueeState {
  RUNNING = 0,
  PAUSED = 1,
  FINISHED = 2,
  START_PENDING = 3,
  PAUSE_PENDING = 4,
  FINISH_PENDING = 5,
}
declare enum IncrementalUpdatePolicy {
  NONE = 0,
  INCREMENTAL = 1,
  FULL = 2,
}
declare enum JoinStyle {
  MITER = 0,
  ROUND = 1,
  BEVEL = 2,
}
declare type CancelButtonStyle = string;
declare interface IconOptions {
  size?: Length;
  color?: ResourceColor;
  src?: ResourceStr;
}
declare type ErrorCallback = any;
declare class StyledString {
  constructor(value: string | any | any, styles?: Array<any>);
  readonly length: number;
  getString(): string;
  getStyles(start: number, length: number, styledKey?: any): Array<any>;
  equals(other: StyledString): boolean;
  subStyledString(start: number, length?: number): StyledString;
  static fromHtml(html: string): Promise<StyledString>;
  static toHtml(styledString: StyledString): string;
  static marshalling(styledString: StyledString, callback: any): ArrayBuffer;
  static unmarshalling(buffer: ArrayBuffer, callback: any): Promise<StyledString>;
  static marshalling(styledString: StyledString): ArrayBuffer;
  static unmarshalling(buffer: ArrayBuffer): Promise<StyledString>;
}
declare enum MenuAlignType {
  START,
  CENTER,
  END,
}
declare type Offset = {
  dx: Length;
  dy: Length;
};
declare enum ScrollDirectionalLockType {
  ALL = 0,
  NESTED_SCROLL = 1,
}
declare interface ScrollableBarModeOptions {
  margin?: Dimension;
  nonScrollableLayoutStyle?: any;
}
declare interface DividerStyle {
  strokeWidth: Length;
  color?: ResourceColor;
  startMargin?: Length;
  endMargin?: Length;
}
declare interface BarGridColumnOptions {
  sm?: number;
  md?: number;
  lg?: number;
  margin?: Dimension;
  gutter?: Dimension;
}
declare enum TabsCacheMode {
  CACHE_BOTH_SIDE = 0,
  CACHE_LATEST_SWITCHED = 1,
}
declare enum TabBarStyle {
  BOTTOM = 0,
  SIDEBAR = 1,
  SIDEBAR_ADAPTABLE = 2,
}
declare type TabsSidebarSearchFilterCallback = (tabIndex: number, text: string) => boolean;
declare interface TabsSidebarSearchableOptions {
  searchText?: ResourceStr;
  placeholder?: ResourceStr;
  searchCallback?: (text: string) => void;
  searchFilter?: TabsSidebarSearchFilterCallback;
}
declare enum TabBarDisplayMode {
  BOTTOM_TABBAR = 0,
  SIDEBAR = 1,
}
declare enum TabVisibility {
  VISIBLE = 0,
  HIDDEN = 1,
}
declare interface TabContentDefaultVisibility {
  visibility?: TabVisibility;
  displayMode?: TabBarDisplayMode;
}
declare interface TabsBreakpointType<T> {
  sm?: T;
  md?: T;
  lg?: T;
}
declare enum NestedScrollMode {
  SELF_ONLY,
  SELF_FIRST,
  PARENT_FIRST,
  PARALLEL,
}
declare enum MaxLinesMode {
  CLIP = 0,
  SCROLL = 1,
}
declare class DotIndicator {}
declare class DigitIndicator {}
declare interface ArrowStyle {
  showBackground?: boolean;
  isSidebarMiddle?: boolean;
  backgroundSize?: Length;
  backgroundColor?: ResourceColor;
  arrowSize?: Length;
  arrowColor?: ResourceColor;
}
declare interface SwiperAutoFill {
  minSize: any;
}
declare type ItemFillPolicy = any;
declare interface PlaceholderStyle {
  font?: Font;
  fontColor?: ResourceColor;
}
declare enum ScrollSnapAlign {
  NONE = 0,
  START = 1,
  CENTER = 2,
  END = 3,
}
declare class SymbolEffect {}
declare enum TextDataDetectorType {
  PHONE_NUMBER = 0,
  URL = 1,
  EMAIL = 2,
  ADDRESS = 3,
  DATE_TIME = 4,
}
declare enum DragPreviewMode {
  AUTO = 1,
  DISABLE_SCALE = 2,
  ENABLE_DEFAULT_SHADOW = 3,
  ENABLE_DEFAULT_RADIUS = 4,
  ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
  ENABLE_MULTI_TILE_EFFECT = 6,
  ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7,
}
declare enum DraggingSizeChangeEffect {
  DEFAULT = 0,
  SIZE_TRANSITION = 1,
  SIZE_CONTENT_TRANSITION = 2,
}
declare interface GuideLinePosition {
  start?: Dimension;
  end?: Dimension;
}
declare enum BarrierDirection {
  LEFT,
  RIGHT,
  TOP,
  BOTTOM,
}
declare interface NavigationCommonTitle {
  main: string | Resource;
  sub: string | Resource;
}
declare interface NavigationCustomTitle {
  builder: CustomBuilder;
  height: any | Length;
}
declare interface NavigationTitleOptions {
  backgroundColor?: ResourceColor;
  backgroundBlurStyle?: BlurStyle;
  backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
  backgroundEffect?: BackgroundEffectOptions;
  barStyle?: any;
  paddingStart?: LengthMetrics;
  paddingEnd?: LengthMetrics;
  mainTitleModifier?: any;
  subTitleModifier?: any;
  enableHoverMode?: boolean;
  scrollEffectOptions?: any;
  systemMaterial?: any;
}
declare interface NavigationMenuItem {
  value: string | Resource;
  icon?: string | Resource;
  symbolIcon?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
}
declare interface NavigationMenuOptions {
  moreButtonOptions?: any;
}
declare interface ToolbarItem {
  value: ResourceStr;
  icon?: ResourceStr;
  symbolIcon?: SymbolGlyphModifier;
  action?: () => void;
  status?: any;
  activeIcon?: ResourceStr;
  activeSymbolIcon?: SymbolGlyphModifier;
}
declare interface NavigationToolbarOptions {
  backgroundColor?: ResourceColor;
  backgroundBlurStyle?: BlurStyle;
  backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
  backgroundEffect?: BackgroundEffectOptions;
  moreButtonOptions?: any;
  barStyle?: any;
  hideItemValue?: boolean;
}
declare interface IndicatorIconInfo {
  index: number;
  icon: ResourceStr | SymbolGlyphModifier;
}
declare interface DisturbanceFieldOptions {
  strength?: number;
  shape?: any;
  size?: any;
  position?: any;
  feather?: number;
  noiseScale?: number;
  noiseFrequency?: number;
  noiseAmplitude?: number;
}
declare interface EmitterProperty {
  index: number;
  emitRate?: number;
  position?: any;
  size?: any;
  annulusRegion?: any;
}
declare interface RippleFieldOptions {
  amplitude?: number;
  wavelength?: number;
  waveSpeed?: number;
  attenuation?: number;
  center?: any;
  region?: any;
}
declare interface VelocityFieldOptions {
  velocity?: any;
  region?: any;
}
declare interface AISessionEvent {
  aiSessionType: any;
  onCreateAISession: any;
  onExecuteAIAction: any;
  onDestroyAISession: any;
}
declare interface ASTCResource {
  sources: Array<string>;
  column: number;
}
declare enum CacheMode {
  Default = 0,
  None = 1,
  Online = 2,
  Only = 3,
}
declare type callback = any;
declare interface ChainAnimationOptions {
  minSpace: Length;
  maxSpace: Length;
  conductivity?: number;
  intensity?: number;
  edgeEffect?: any;
  stiffness?: number;
  damping?: number;
}
declare class ChildrenMainSize {
  constructor(childDefaultSize: number);
  set childDefaultSize(value: number);
  get childDefaultSize(): number;
  splice(start: number, deleteCount?: number, childrenSize?: Array<number>): void;
  update(index: number, childSize: number): void;
}
declare class ClientAuthenticationHandler {
  constructor();
  confirm(priKeyFile: string, certChainFile: string): void;
  confirm(authUri: string): void;
  confirm(identity: string, credentialTypeOrCertChainFile: any | string): void;
  cancel(): void;
  ignore(): void;
}
declare type CommonModifier = any;
declare const CommonModifier: any;
declare type Component3DAttribute = any;
declare class ConsoleMessage {
  constructor(message: string, sourceId: string, lineNumber: number, messageLevel: any);
  constructor();
  getMessage(): string;
  getSourceId(): string;
  getLineNumber(): number;
  getMessageLevel(): any;
  getSource(): any;
}
declare class ContainerSpanAttribute {
  textBackgroundStyle(style: TextBackgroundStyle): ContainerSpanAttribute;
  attributeModifier(modifier: AttributeModifier<ContainerSpanAttribute>): ContainerSpanAttribute;
}
declare class ControllerHandler {
  constructor();
  setWebController(controller: any): void;
}
declare enum CrownSensitivity {
  LOW = 0,
  MEDIUM = 1,
  HIGH = 2,
}
declare class DataResubmissionHandler {
  constructor();
  resend(): void;
  cancel(): void;
}
declare type DatePickerAttribute = any;
declare interface DatePickerResult {
  year?: number;
  month?: number;
  day?: number;
}
declare enum EditMode {
  None,
  Deletable,
  Movable,
}
declare type EffectComponentAttribute = any;
declare type EmbeddedComponentAttribute = any;
declare interface EmbedOptions {
  supportDefaultIntrinsicSize?: boolean;
  supportCssDisplayChange?: boolean;
}
declare class FileSelectorParam {
  constructor();
  getTitle(): string;
  getMode(): any;
  getAcceptType(): Array<string>;
  isCapture(): boolean;
  getMimeTypes(): Array<string>;
  getSuggestedName(): string;
  getDefaultPath(): string;
  getDescriptions(): Array<string>;
  isAcceptAllOptionExcluded(): boolean;
  getAcceptableFileTypes(): Array<Array<any>>;
}
declare type FileSelectorResult = any;
declare type FormComponentAttribute = any;
declare enum FormDimension {
  Dimension_1_2 = 0,
  Dimension_2_2 = 1,
  Dimension_2_4 = 2,
  Dimension_4_4 = 3,
  Dimension_2_1 = 4,
  DIMENSION_1_1 = 6,
  DIMENSION_6_4 = 7,
  DIMENSION_2_3 = 8,
  DIMENSION_3_3 = 9,
}
declare type FormLinkAttribute = any;
declare class FullScreenExitHandler {
  constructor();
  exitFullScreen(): void;
}
declare enum GestureFocusMode {
  DEFAULT = 0,
  GESTURE_TAP_AND_LONG_PRESS = 1,
}
declare class HttpAuthHandler {
  constructor();
  confirm(userName: string, password: string): boolean;
  cancel(): void;
  isHttpAuthInfoSaved(): boolean;
}
declare type ImageAttribute = any;
declare type IsolatedComponentAttribute = any;
declare interface JavaScriptProxy {
  object: object;
  name: string;
  methodList: Array<string>;
  controller: any | any;
  asyncMethodList?: Array<string>;
  permission?: string;
}
declare class JsGeolocation {
  constructor();
  invoke(origin: string, allow: boolean, retain: boolean): void;
}
declare class JsResult {
  constructor();
  handleCancel(): void;
  handleConfirm(): void;
  handlePromptConfirm(result: string): void;
}
declare type LazyColumnLayoutAttribute = any;
declare type LengthConstrain = {
  minLength: Length;
  maxLength: Length;
};
declare type ListAttribute = any;
declare interface ListBackPressBehavior {
  closeSwipeAction?: boolean;
}
declare enum ListItemAlign {
  Start,
  Center,
  End,
}
declare type ListItemAttribute = any;
declare type ListItemGroupAttribute = any;
declare enum ListItemGroupStyle {
  NONE = 0,
  CARD = 1,
}
declare enum ListItemStyle {
  NONE = 0,
  CARD = 1,
}
declare enum ListItemSwipeActionDirection {
  START = 0,
  END = 1,
}
declare enum MixedMode {
  All = 0,
  Compatible = 1,
  None = 2,
}
declare type ModifierJs = any;
declare interface NativeEmbedDataInfo {
  status?: any;
  surfaceId?: string;
  embedId?: string;
  info?: any;
}
declare interface NativeEmbedMouseInfo {
  embedId?: string;
  mouseEvent?: MouseEvent;
  result?: any;
}
declare interface NativeEmbedParamDataInfo {
  embedId: string;
  objectAttributeId?: string;
  paramItems?: Array<any>;
}
declare interface NativeEmbedTouchInfo {
  embedId?: string;
  touchEvent?: TouchEvent;
  result?: any;
}
declare interface NativeMediaPlayerConfig {
  enable: boolean;
  shouldOverlay: boolean;
}
declare interface NavContentInfo {
  name?: string;
  index: number;
  mode?: any;
  param?: Object;
  navDestinationId?: string;
}
declare interface NavigationAnimatedTransition {
  onTransitionEnd?: (success: boolean) => void;
  timeout?: number;
  isInteractive?: boolean;
  transition: (transitionProxy: any) => void;
}
declare type NavigationAttribute = any;
declare interface NavigationConfiguration {
  stackSizeLimit?: any;
}
declare enum NavigationMode {
  Stack,
  Split,
  Auto,
  AUTO_WITH_ASPECT_RATIO,
}
declare enum NavigationOperation {
  PUSH = 1,
  POP = 2,
  REPLACE = 3,
}
declare enum NavigationPolicy {
  NEW_POPUP = 0,
  NEW_WINDOW = 1,
  NEW_BACKGROUND_TAB = 2,
  NEW_FOREGROUND_TAB = 3,
}
declare enum NavigationTitleMode {
  Free = 0,
  Full,
  Mini,
}
declare enum NavigationType {
  Push,
  Back,
  Replace,
}
declare type NavigatorAttribute = any;
declare enum NavRouteMode {
  PUSH_WITH_RECREATE,
  PUSH,
  REPLACE,
}
declare type NavRouterAttribute = any;
declare interface NestedScrollOptionsExt {
  scrollUp?: NestedScrollMode;
  scrollDown?: NestedScrollMode;
  scrollRight?: NestedScrollMode;
  scrollLeft?: NestedScrollMode;
}
declare type OnCameraCaptureStateChangeCallback = (event: any) => void;
declare type OnContextMenuHideCallback = () => void;
declare type OnDetectBlankScreenCallback = (event: any) => void;
declare type OnFirstScreenPaintCallback = (firstScreenPaint: any) => void;
declare type OnMicrophoneCaptureStateChangeCallback = (event: any) => void;
declare type OnNavigationEntryCommittedCallback = (loadCommittedDetails: any) => void;
declare type OnOverrideUrlLoadingCallback = (webResourceRequest: WebResourceRequest) => boolean;
declare type OnPickerCallback = any;
declare type OnRenderProcessNotRespondingCallback = (data: any) => void;
declare type OnRenderProcessRespondingCallback = () => void;
declare type OnSafeBrowsingCheckResultCallback = (threatType: any) => void;
declare interface OnSslErrorEventReceiveEvent {
  handler: SslErrorHandler;
  error: SslError;
  certChainData?: Array<Uint8Array>;
}
declare type OnTextSelectionChangeCallback = (selectionStart: number, selectionEnd: number) => void;
declare type OnViewportFitChangedCallback = (viewportFit: any) => void;
declare enum OverScrollMode {
  NEVER = 0,
  ALWAYS = 1,
}
declare type PanelAttribute = any;
declare enum PanelHeight {
  WRAP_CONTENT = 'wrapContent',
}
declare enum PanelMode {
  Mini,
  Half,
  Full,
}
declare enum PanelType {
  Minibar = 0,
  Foldable = 1,
  Temporary = 2,
  CUSTOM = 3,
}
declare type PermissionRequest = any;
declare type PickerIndicatorStyle = any;
declare interface PickerTextStyle {
  color?: ResourceColor;
  font?: Font;
}
declare type PluginComponentAttribute = any;
declare type RemoteWindowAttribute = any;
declare enum RenderExitReason {
  ProcessAbnormalTermination = 0,
  ProcessWasKilled = 1,
  ProcessCrashed = 2,
  ProcessOom = 3,
  ProcessExitUnknown = 4,
}
declare type RichTextAttribute = any;
declare type ScreenCaptureHandler = any;
declare interface ScriptItem {
  script: string;
  scriptRules: Array<string>;
  urlRegexRules?: Array<any>;
}
declare type ScrollBarAttribute = any;
declare enum ScrollSnapAnimationSpeed {
  NORMAL = 0,
  SLOW = 1,
}
declare enum SslError {
  Invalid = 0,
  HostMismatch = 1,
  DateInvalid = 2,
  Untrusted = 3,
}
declare class SslErrorHandler {
  constructor();
  handleConfirm(): void;
  handleCancel(): void;
  handleCancel(abortLoading: boolean): void;
}
declare enum Sticky {
  None,
  Normal,
  Opacity,
}
declare enum StickyStyle {
  None = 0,
  Header = 1,
  Footer = 2,
  BOTH = 3,
}
declare interface SwipeActionOptions {
  start?: CustomBuilder | any;
  end?: CustomBuilder | any;
  edgeEffect?: any;
  onOffsetChange?: (offset: number) => void;
}
declare interface TerminationInfo {
  code: number;
  want?: any;
}
declare type UIExtensionComponentAttribute = any;
declare type UIPickerComponentAttribute = any;
declare type WebAttribute = any;
declare type WebContextMenuParam = any;
declare type WebContextMenuResult = any;
declare enum WebDarkMode {
  Off = 0,
  On = 1,
  Auto = 2,
}
declare enum WebKeyboardAppearanceMode {
  NONE_IMMERSIVE = 0,
  IMMERSIVE = 1,
  LIGHT_IMMERSIVE = 2,
  DARK_IMMERSIVE = 3,
}
declare enum WebKeyboardAvoidMode {
  RESIZE_VISUAL = 0,
  RESIZE_CONTENT = 1,
  OVERLAYS_CONTENT = 2,
  RETURN_TO_UICONTEXT = 3,
}
declare enum WebLayoutMode {
  NONE = 0,
  FIT_CONTENT = 1,
}
declare interface WebMediaOptions {
  resumeInterval?: number;
  audioExclusive?: boolean;
  audioSessionType?: any;
}
declare class WebResourceError {
  constructor();
  getErrorInfo(): string;
  getErrorCode(): number;
  getCustomErrorCode(): number;
}
declare class WebResourceRequest {
  constructor();
  getRequestHeader(): Array<any>;
  getRequestUrl(): string;
  isRequestGesture(): boolean;
  isMainFrame(): boolean;
  isRedirect(): boolean;
  getRequestMethod(): string;
}
declare class WebResourceResponse {
  constructor();
  getResponseData(): string;
  getResponseDataEx(): string | number | ArrayBuffer | Resource | undefined;
  getResponseEncoding(): string;
  getResponseMimeType(): string;
  getReasonMessage(): string;
  getResponseHeader(): Array<any>;
  getResponseCode(): number;
  setResponseData(data: string | number | Resource | ArrayBuffer): void;
  setResponseEncoding(encoding: string): void;
  setResponseMimeType(mimeType: string): void;
  setReasonMessage(reason: string): void;
  setResponseHeader(header: Array<any>): void;
  setResponseCode(code: number): void;
  setResponseIsReady(IsReady: boolean): void;
  getResponseIsReady(): boolean;
}
declare enum WebRotateEffect {
  TOPLEFT_EFFECT = 0,
  RESIZE_COVER_EFFECT = 1,
}
declare interface WindowFeatures {
  height: number;
  width: number;
  x: number;
  y: number;
}
declare type AlphabetIndexerAttribute = any;
declare type ArkPrefixOrSuffix = any;
declare const ArkPrefixOrSuffix: any;
declare type ArkSliderStepOptions = any;
declare const ArkSliderStepOptions: any;
declare type ArkSliderTips = any;
declare const ArkSliderTips: any;
declare interface ButtonStyle {
  left?: number;
  top?: number;
  width?: number;
  height?: number;
  icons?: any;
}
declare enum CalendarAlign {
  START = 0,
  CENTER = 1,
  END = 2,
}
declare type CalendarPickerAttribute = any;
declare type CheckboxAttribute = any;
declare interface CheckBoxConfiguration extends CommonConfiguration<CheckBoxConfiguration> {
  name: string;
  selected: boolean;
  triggerChange: Callback<boolean>;
}
declare type CheckboxGroupAttribute = any;
declare interface CheckBoxGroupConfiguration extends CommonConfiguration<CheckBoxGroupConfiguration> {
  name: string;
  status: any;
  triggerChange: Callback<boolean>;
}
declare const CheckBoxGroupConfiguration: any;
declare interface CheckboxGroupOptions {
  group?: string;
}
declare interface CheckboxOptions {
  name?: string;
  group?: string;
  indicatorBuilder?: CustomBuilder;
}
declare enum CheckBoxShape {
  CIRCLE = 0,
  ROUNDED_SQUARE = 1,
}
declare class ColorMetricsLinearGradient {
  constructor(colorStops: any[]);
}
declare type ColumnSplitAttribute = any;
declare type ColumnSplitDividerStyle = any;
declare interface CopyEvent {
  preventDefault?: Callback<void>;
}
declare interface CutEvent {
  preventDefault?: Callback<void>;
}
declare type DateTimeOptions = any;
declare type FlowItemAttribute = any;
declare type FolderStackAttribute = any;
declare enum FoldStatus {
  FOLD_STATUS_UNKNOWN = 0,
  FOLD_STATUS_EXPANDED = 1,
  FOLD_STATUS_FOLDED = 2,
  FOLD_STATUS_HALF_FOLDED = 3,
}
declare interface HoverEventParam {
  foldStatus: FoldStatus;
  isHoverMode: boolean;
  appRotation: any;
  windowStatusType: any;
}
declare type HyperlinkAttribute = any;
declare enum IndexerAlign {
  Left,
  Right,
  START,
  END,
}
declare enum ItemState {
  Normal,
  Disabled,
  Waiting,
  Skip,
}
declare type LazyVWaterFlowLayoutAttribute = any;
declare interface MarkStyle {
  strokeColor?: ResourceColor;
  size?: Length;
  strokeWidth?: Length;
}
declare type MarqueeAttribute = any;
declare enum MarqueeUpdateStrategy {
  DEFAULT = 0,
  PRESERVE_POSITION = 1,
}
declare type MenuAttribute = any;
declare type MenuItemAttribute = any;
declare type MenuItemGroupAttribute = any;
declare type OnCheckboxChangeCallback = (value: boolean) => void;
declare type OnCheckboxGroupChangeCallback = (value: any) => void;
declare type OnDidChangeCallback = (rangeBefore: TextRange, rangeAfter: TextRange) => void;
declare type QRCodeAttribute = any;
declare type RadioAttribute = any;
declare interface RadioConfiguration extends CommonConfiguration<RadioConfiguration> {
  value: string;
  checked: boolean;
  triggerChange: Callback<boolean>;
}
declare interface RadioOptions {
  group: string;
  value: string;
  indicatorType?: any;
  indicatorBuilder?: CustomBuilder;
}
declare interface RadioStyle {
  checkedBackgroundColor?: ResourceColor;
  uncheckedBorderColor?: ResourceColor;
  indicatorColor?: ResourceColor;
}
declare type RatingAttribute = any;
declare interface RatingOptions {
  rating?: number;
  indicator?: boolean;
}
declare interface RatingConfiguration extends CommonConfiguration<RatingConfiguration> {
  rating: number;
  indicator: boolean;
  stars: number;
  stepSize: number;
  triggerChange: Callback<number>;
}
declare type RichEditorAttribute = any;
declare interface RichEditorChangeValue {
  rangeBefore: TextRange;
  replacedSpans: Array<RichEditorTextSpanResult>;
  replacedImageSpans: Array<any>;
  replacedSymbolSpans: Array<RichEditorTextSpanResult>;
  changeReason?: any;
}
declare interface RichEditorDeleteValue {
  offset: number;
  direction: any;
  length: number;
  richEditorDeleteSpans: Array<RichEditorTextSpanResult | any>;
}
declare interface RichEditorInsertValue {
  insertOffset: number;
  insertValue: string;
  previewText?: string;
}
declare interface RichEditorRange {
  start?: number;
  end?: number;
}
declare interface RichEditorSelection {
  selection: [number, number];
  spans: Array<RichEditorTextSpanResult | any>;
}
declare enum RichEditorSpanType {
  TEXT = 0,
  IMAGE = 1,
  MIXED = 2,
  BUILDER = 3,
  DEFAULT = 4,
}
declare interface RichEditorTextSpanResult {
  spanPosition: any;
  value: string;
  textStyle: any;
  offsetInSpan: [number, number];
  symbolSpanStyle?: any;
  valueResource?: Resource;
  paragraphStyle?: any;
  previewText?: string;
  urlStyle?: any;
}
declare type RowSplitAttribute = any;
declare type SearchAttribute = any;
declare type SearchButtonOptions = any;
declare type SearchController = any;
declare enum SearchType {
  NORMAL = 0,
  NUMBER = 2,
  PHONE_NUMBER = 3,
  EMAIL = 5,
  NUMBER_DECIMAL = 12,
  URL = 13,
  ONE_TIME_CODE = 14,
}
declare interface SelectionMenuOptions {
  onAppear?: any;
  onDisappear?: Callback<void>;
  menuType?: any;
  onMenuShow?: any;
  onMenuHide?: any;
  previewMenuOptions?: any;
}
declare class ShaderStyle {}
declare type SideBarContainerAttribute = any;
declare enum SideBarPosition {
  Start,
  End,
}
declare type SliderAttribute = any;
declare interface SliderBlockStyle {
  type: any;
  image?: ResourceStr;
  shape?: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute;
}
declare enum SliderChangeMode {
  Begin,
  Moving,
  End,
  Click,
}
declare interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
  value: number;
  min: number;
  max: number;
  step: number;
  triggerChange: any;
}
declare type SliderCustomContentOptions = any;
declare enum SliderInteraction {
  SLIDE_AND_CLICK = 0,
  SLIDE_ONLY = 1,
  SLIDE_AND_CLICK_UP = 2,
}
declare interface SliderOptions {
  value?: number;
  min?: number;
  max?: number;
  step?: number;
  style?: any;
  direction?: Axis;
  reverse?: boolean;
}
declare interface SliderShowStepOptions {
  stepsAccessibility?: Map<number, any>;
}
declare type StepperAttribute = any;
declare type StepperItemAttribute = any;
declare enum SubMenuExpandingMode {
  SIDE_EXPAND = 0,
  EMBEDDED_EXPAND = 1,
  STACK_EXPAND = 2,
}
declare type SubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
declare type SymbolGlyphAttribute = any;
declare type SymbolGlyphModifier = any;
declare const SymbolGlyphModifier: any;
declare type SymbolShadow = any;
declare interface TextRange {
  start?: number;
  end?: number;
}
declare type TimePickerAttribute = any;
declare interface TimePickerResult {
  hour: number;
  minute: number;
  second: number;
}
declare enum UndoStyle {
  CLEAR_STYLE = 0,
  KEEP_STYLE = 1,
}
declare type ValidSlideRange = any;
declare type WaterFlowAttribute = any;
declare enum WaterFlowLayoutMode {
  ALWAYS_TOP_DOWN = 0,
  SLIDING_WINDOW = 1,
}
declare class WaterFlowSections {
  constructor();
  splice(start: number, deleteCount?: number, sections?: Array<any>): boolean;
  push(section: any): boolean;
  update(sectionIndex: number, section: any): boolean;
  values(): Array<any>;
  length(): number;
}

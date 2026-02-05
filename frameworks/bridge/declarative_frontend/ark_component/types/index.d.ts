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

type ArkComponent = any;

// Resource interface
declare interface Resource {
  bundleName: string;
  moduleName: string;
  id: number;
  params?: Array<string | number | Resource>;
  type?: number;
}

type ResourceColor = Color | number | string | Resource;

// ArkBackground class
declare class ArkBackground {
  content: ResourceColor | undefined;
  align?: Alignment | undefined;
  ignoresLayoutSafeAreaEdges?: Array<number> | undefined;
  isEqual(another: ArkBackground): boolean;
}

// ArkBindMenu class
declare class ArkBindMenu {
  content: Array<any> | CustomBuilder | undefined;
  options: any | undefined;
  isEqual(another: ArkBindMenu): boolean;
}

// ArkBorder class
declare class ArkBorder {
  arkWidth: any;
  arkColor: any;
  arkRadius: any;
  arkStyle: any;
  arkDashGap: any;
  arkDashWidth: any;
  isEqual(another: ArkBorder): boolean;
  checkObjectDiff(another: ArkBorder): boolean;
}

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
type Length = (string | number | Resource | LengthMetrics) & { direction?: number; style?: number };

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
declare class ArkBorderRadiusOpts {
  value: Length | BorderRadiuses | LocalizedBorderRadius;
  type: RenderStrategy;
  isEqual(another: ArkBorderRadiusOpts): boolean;
}

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
declare class ArkOverlay {
  value: string | CustomBuilder | undefined;
  align: number | undefined;
  offsetX: number | undefined;
  offsetY: number | undefined;
  hasOptions: boolean | undefined;
  hasOffset: boolean | undefined;
  isEqual(another: ArkOverlay): boolean;
  checkObjectDiff(another: ArkOverlay): boolean;
}

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

// ArkShadowStyle enum
declare enum ArkShadowStyle {
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
declare class ArkBlurOptions {
  value: number;
  options?: BlurOptions;
}

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

declare class ArkForegroundBlurStyle {
  blurStyle: number | undefined;
  colorMode: number | undefined;
  adaptiveColor: number | undefined;
  scale: number | undefined;
  blurOptions?: BlurOptions;
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

declare class ArkLinearGradientBlur {
  blurRadius: number | undefined;
  fractionStops?: FractionStop[];
  direction: number | undefined;
  isEqual(another: ArkLinearGradientBlur): boolean;
}

declare class ArkBackgroundImage {
  src: string | undefined | Resource | PixelMap;
  repeat: number | undefined | object;
}

declare class ArkBackgroundBlurStyle {
  blurStyle: number | undefined;
  colorMode: number | undefined;
  adaptiveColor: number | undefined;
  scale: number | undefined;
  blurOptions?: BlurOptions;
  policy?: number;
  inactiveColor?: ResourceColor;
  type?: number;
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

declare class ArkGeometryTransition {
  id: string | undefined;
  options: GeometryTransitionOptions | undefined;
}

declare interface GeometryTransitionOptions {
  follow?: boolean;
  hierarchyStrategy?: number;
}

declare class ArkBlendMode {
  blendMode: number | Blender;
  blendApplyType: number;
}

declare interface FractionStop {
  stop: number;
  color: ResourceColor;
}

type PixelMap = any;
type Blender = any;
type EffectType = any;

// Pixel stretch effect options
declare interface PixelStretchEffectOptions {
  top?: Length;
  bottom?: Length;
  left?: Length;
  right?: Length;
}

// ArkUseEffect class
declare class ArkUseEffect {
  useEffect: boolean;
  effectType: EffectType;
  isEqual(another: ArkUseEffect): boolean;
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
declare class ArkDragSpringLoading {
  callback: (context: ArkSpringLoadingContext) => void;
  configuration: ArkDragSpringLoadingConfiguration | undefined;
  isEqual(another: ArkDragSpringLoading): boolean;
}

// ArkOnDrop class
declare class ArkOnDrop {
  event: (event?: DragEvent, extraParams?: string) => void;
  disableDataPrefetch: boolean | undefined;
  isEqual(another: ArkOnDrop): boolean;
}

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

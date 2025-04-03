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
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { TextDecorationType, TextDecorationStyle, Curve, PlayMode, SharedTransitionEffectType, HorizontalAlign, VerticalAlign, TransitionType, FontWeight, FontStyle, Color, ColoringStrategy, TouchType, BorderStyle, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, HitTestMode, ImageSize, Alignment, HoverEffect, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, LineCapStyle, LineJoinStyle, PixelRoundCalcPolicy, BarState, EdgeEffect, IlluminatedType, ScrollSource } from "./ArkEnumsInterfaces"
import { ResourceColor, Length, Bias, Area, Font, BorderRadiuses, EdgeWidths, LocalizedEdgeWidths, SizeOptions, ResourceStr, Dimension, EdgeColors, LocalizedEdgeColors, EdgeStyles, Position, LocalizedBorderRadiuses, Margin, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, LocalizedMargin, BorderOptions, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, EdgeWidth } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ICurve } from "./ArkICurveMaterialized"
import { Callback_Void, Literal_String_anchor_HorizontalAlign_align, Literal_String_anchor_VerticalAlign_align, Literal_TransitionEffect_appear_disappear, Tuple_Number_Number, Callback_DismissContentCoverAction_Void, Type_SheetOptions_detents, Callback_SheetDismiss_Void, Callback_DismissSheetAction_Void, Callback_SpringBackAction_Void, Callback_Number_Void, Callback_SheetType_Void, Literal_String_value_Callback_Void_action, Callback_Literal_Boolean_isVisible_Void, Literal_Boolean_isVisible, Literal_ResourceColor_color, Callback_DismissPopupAction_Void, AnimationRange_Number, Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Number_Number_Void } from "./SyntheticDeclarations"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./ArkButtonInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { GestureRecognizer } from "./ArkGestureRecognizerMaterialized"
import { GestureJudgeResult, GestureInfo, GestureType, GestureMask, GestureHandler, GesturePriority } from "./ArkGestureInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { ScrollState } from "./ArkListInterfaces"
import { AccessibilityHoverEvent } from "./ArkAccessibilityHoverEventMaterialized"
import { SymbolGlyphModifier } from "../handwritten/modifiers/ArkSymbolGlyphModifier"
export { SymbolGlyphModifier } from "../handwritten/modifiers/ArkSymbolGlyphModifier"
export interface ComponentOptions {
    freezeWhenInactive: boolean;
}
export interface InputCounterOptions {
    thresholdPercentage?: number;
    highlightBorder?: boolean;
}
export interface TextDecorationOptions {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
export interface ProvideOptions {
    allowOverride?: string;
}
export interface AnimatableArithmetic<T> {
}
declare function getContext(arg0: Object): Context
export interface Context {
    _ContextStub: string;
}
declare function postCardAction(arg0: Object, arg1: Object): void
export interface Configuration {
    colorMode: string;
    fontScale: number;
}
export interface Rectangle {
    x?: Length;
    y?: Length;
    width?: Length;
    height?: Length;
}
export interface ExpectedFrameRateRange {
    min: number;
    max: number;
    expected: number;
}
declare function dollar_r(arg0: string, arg1: Array<object>): Resource
declare function dollar_rawfile(arg0: string): Resource
export enum FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1
}
export enum TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION = 1,
    FORWARD = 2
}
export interface AnimateParam {
    duration?: number;
    tempo?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    iterations?: number;
    playMode?: PlayMode;
    onFinish?: (() => void);
    finishCallbackType?: FinishCallbackType;
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
export interface MotionPathOptions {
    path: string;
    from?: number;
    to?: number;
    rotatable?: boolean;
}
export interface sharedTransitionOptions {
    duration?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    motionPath?: MotionPathOptions;
    zIndex?: number;
    type?: SharedTransitionEffectType;
}
export interface GeometryTransitionOptions {
    follow?: boolean;
    hierarchyStrategy?: TransitionHierarchyStrategy;
}
export enum TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE = 1
}
export interface TranslateOptions {
    x?: number | string;
    y?: number | string;
    z?: number | string;
}
export interface ScaleOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
}
export interface AlignRuleOption {
    left?: Literal_String_anchor_HorizontalAlign_align;
    right?: Literal_String_anchor_HorizontalAlign_align;
    middle?: Literal_String_anchor_HorizontalAlign_align;
    top?: Literal_String_anchor_VerticalAlign_align;
    bottom?: Literal_String_anchor_VerticalAlign_align;
    center?: Literal_String_anchor_VerticalAlign_align;
    bias?: Bias;
}
export interface LocalizedHorizontalAlignParam {
    anchor: string;
    align: HorizontalAlign;
}
export interface LocalizedVerticalAlignParam {
    anchor: string;
    align: VerticalAlign;
}
export interface LocalizedAlignRuleOptions {
    start?: LocalizedHorizontalAlignParam;
    end?: LocalizedHorizontalAlignParam;
    middle?: LocalizedHorizontalAlignParam;
    top?: LocalizedVerticalAlignParam;
    bottom?: LocalizedVerticalAlignParam;
    center?: LocalizedVerticalAlignParam;
    bias?: Bias;
}
export enum ChainStyle {
    SPREAD = 0,
    SPREAD_INSIDE = 1,
    PACKED = 2
}
export interface RotateOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
    centerZ?: number;
    perspective?: number;
    angle: number | string;
}
export interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
export enum TransitionEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export interface TransitionEffects {
    identity: undefined;
    opacity: number;
    slideSwitch: undefined;
    move: TransitionEdge;
    translate: TranslateOptions;
    rotate: RotateOptions;
    scale: ScaleOptions;
    asymmetric: Literal_TransitionEffect_appear_disappear;
}
export interface PreviewParams {
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
export interface ItemDragInfo {
    x: number;
    y: number;
}
export enum EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1
}
export enum PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6
}
export interface DragItemInfo {
    pixelMap?: PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
declare function animateTo(arg0: AnimateParam, arg1: (() => void)): void
declare function animateToImmediately(arg0: AnimateParam, arg1: (() => void)): void
declare function vp2px(arg0: number): number
declare function px2vp(arg0: number): number
declare function fp2px(arg0: number): number
declare function px2fp(arg0: number): number
declare function lpx2px(arg0: number): number
declare function px2lpx(arg0: number): number
export interface EventTarget {
    area: Area;
}
export enum SourceType {
    UNKNOWN = 0,
    Unknown = 0,
    MOUSE = 1,
    Mouse = 1,
    TOUCH_SCREEN = 2,
    TouchScreen = 2
}
export enum SourceTool {
    UNKNOWN = 0,
    Unknown = 0,
    FINGER = 1,
    Finger = 1,
    PEN = 2,
    Pen = 2,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5
}
export enum RepeatMode {
    REPEAT = 0,
    Repeat = 0,
    STRETCH = 1,
    Stretch = 1,
    ROUND = 2,
    Round = 2,
    SPACE = 3,
    Space = 3
}
export enum BlurStyle {
    THIN = 0,
    Thin = 0,
    REGULAR = 1,
    Regular = 1,
    THICK = 2,
    Thick = 2,
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
export enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2
}
export enum ThemeColorMode {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2
}
export enum AdaptiveColor {
    DEFAULT = 0,
    AVERAGE = 1
}
export enum ModalTransition {
    DEFAULT = 0,
    NONE = 1,
    ALPHA = 2
}
export interface BackgroundBlurStyleOptions extends BlurStyleOptions {
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
export interface ForegroundBlurStyleOptions extends BlurStyleOptions {
}
export interface BlurOptions {
    grayscale: [ number, number ];
}
export interface BlurStyleOptions {
    colorMode?: ThemeColorMode;
    adaptiveColor?: AdaptiveColor;
    scale?: number;
    blurOptions?: BlurOptions;
}
export interface BackgroundEffectOptions {
    radius: number;
    saturation?: number;
    brightness?: number;
    color?: ResourceColor;
    adaptiveColor?: AdaptiveColor;
    blurOptions?: BlurOptions;
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
export interface ForegroundEffectOptions {
    radius: number;
}
export interface PickerTextStyle {
    color?: ResourceColor;
    font?: Font;
}
export interface PickerDialogButtonStyle {
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
export enum ShadowType {
    COLOR = 0,
    BLUR = 1
}
export interface ShadowOptions {
    radius: number | Resource;
    type?: ShadowType;
    color?: Color | string | Resource | ColoringStrategy;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
    fill?: boolean;
}
export enum ShadowStyle {
    OUTER_DEFAULT_XS = 0,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5
}
export interface MultiShadowOptions {
    radius?: number | Resource;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
}
export enum SafeAreaType {
    SYSTEM = 0,
    CUTOUT = 1,
    KEYBOARD = 2
}
export enum SafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export enum LayoutSafeAreaType {
    SYSTEM = 0
}
export enum LayoutSafeAreaEdge {
    TOP = 0,
    BOTTOM = 1
}
export enum SheetSize {
    MEDIUM = 0,
    LARGE = 1,
    FIT_CONTENT = 2
}
export interface BorderImageOption {
    slice?: Length | EdgeWidths | LocalizedEdgeWidths;
    repeat?: RepeatMode;
    source?: string | Resource | LinearGradient_common;
    width?: Length | EdgeWidths | LocalizedEdgeWidths;
    outset?: Length | EdgeWidths | LocalizedEdgeWidths;
    fill?: boolean;
}
export interface TouchObject {
    type: TouchType;
    id: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
}
export interface HistoricalPoint {
    touchObject: TouchObject;
    size: number;
    force: number;
    timestamp: number;
}
export type SizeChangeCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
export type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>) => GestureJudgeResult;
export type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
export type TransitionFinishCallback = (transitionIn: boolean) => void;
export enum DragBehavior {
    COPY = 0,
    MOVE = 1
}
export interface Summary {
    _SummaryStub: string;
}
export interface UniformDataType {
    _UniformDataTypeStub: string;
}
export enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4
}
export enum BlendMode {
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
export enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1
}
export interface IntentionCode {
    _IntentionCodeStub: string;
}
export interface BindOptions {
    backgroundColor?: ResourceColor;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
}
export interface DismissContentCoverAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface ContentCoverOptions extends BindOptions {
    modalTransition?: ModalTransition;
    onWillDismiss?: ((parameter: DismissContentCoverAction) => void);
    transition?: TransitionEffect;
}
export interface SheetTitleOptions {
    title: ResourceStr;
    subtitle?: ResourceStr;
}
export enum SheetType {
    BOTTOM = 0,
    CENTER = 1,
    POPUP = 2
}
export enum SheetMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
export enum ScrollSizeMode {
    FOLLOW_DETENT = 0,
    CONTINUOUS = 1
}
export enum SheetKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3
}
export interface SheetDismiss {
    dismiss: (() => void);
}
export interface DismissSheetAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface SpringBackAction {
    springBack: (() => void);
}
export interface SheetOptions extends BindOptions {
    height?: SheetSize | Length;
    dragBar?: boolean;
    maskColor?: ResourceColor;
    detents?: [ SheetSize | Length, SheetSize | Length | undefined, SheetSize | Length | undefined ];
    blurStyle?: BlurStyle;
    showClose?: boolean | Resource;
    preferType?: SheetType;
    title?: SheetTitleOptions | CustomBuilder;
    shouldDismiss?: ((sheetDismiss: SheetDismiss) => void);
    onWillDismiss?: ((parameter: DismissSheetAction) => void);
    onWillSpringBackWhenDismiss?: ((parameter: SpringBackAction) => void);
    enableOutsideInteractive?: boolean;
    width?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    onHeightDidChange?: ((index: number) => void);
    mode?: SheetMode;
    scrollSizeMode?: ScrollSizeMode;
    onDetentsDidChange?: ((index: number) => void);
    onWidthDidChange?: ((index: number) => void);
    onTypeDidChange?: ((parameter: SheetType) => void);
    uiContext?: UIContext;
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
}
export interface StateStyles {
    normal?: object;
    pressed?: object;
    disabled?: object;
    focused?: object;
    clicked?: object;
    selected?: Object;
}
export interface PopupMessageOptions {
    textColor?: ResourceColor;
    font?: Font;
}
export enum DismissReason {
    PRESS_BACK = 0,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3
}
export interface DismissPopupAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface PopupOptions {
    message: string;
    placementOnTop?: boolean;
    placement?: Placement;
    primaryButton?: Literal_String_value_Callback_Void_action;
    secondaryButton?: Literal_String_value_Callback_Void_action;
    onStateChange?: ((event: Literal_Boolean_isVisible) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | Literal_ResourceColor_color;
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
    onWillDismiss?: boolean | ((parameter: DismissPopupAction) => void);
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
export interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    maskColor?: Color | string | Resource | number;
    popupColor?: Color | string | Resource | number;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: ((event: Literal_Boolean_isVisible) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | Literal_ResourceColor_color;
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
    onWillDismiss?: boolean | ((parameter: DismissPopupAction) => void);
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
export enum MenuPreviewMode {
    NONE = 0,
    IMAGE = 1
}
export type AnimationRange<T> = [
    T,
    T
]
export interface ContextMenuAnimationOptions {
    scale?: [ number, number ];
    transition?: TransitionEffect;
    hoverScale?: [ number, number ];
}
export interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: MenuPreviewMode | CustomBuilder;
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    aboutToAppear?: (() => void);
    aboutToDisappear?: (() => void);
    layoutRegionMargin?: Margin;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
}
export interface MenuOptions extends ContextMenuOptions {
    title?: ResourceStr;
    showInSubWindow?: boolean;
}
export interface TouchTestInfo {
    windowX: number;
    windowY: number;
    parentX: number;
    parentY: number;
    x: number;
    y: number;
    rect: RectResult;
    id: string;
}
export interface TouchResult {
    strategy: TouchTestStrategy;
    id?: string;
}
export interface PixelStretchEffectOptions {
    top?: Length;
    bottom?: Length;
    left?: Length;
    right?: Length;
}
export interface ClickEffect {
    level: ClickEffectLevel;
    scale?: number;
}
export interface FadingEdgeOptions {
    fadingEdgeLength?: LengthMetrics;
}
export interface NestedScrollOptions {
    scrollForward: NestedScrollMode;
    scrollBackward: NestedScrollMode;
}
export interface MenuElement {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    enabled?: boolean;
    action: (() => void);
}
export interface ContentModifier<T> {
    stub: string;
}
export interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
}
export enum OutlineStyle {
    SOLID = 0,
    DASHED = 1,
    DOTTED = 2
}
export enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4
}
export enum MenuPolicy {
    DEFAULT = 0,
    HIDE = 1,
    SHOW = 2
}
export interface ImageModifier {
    _ImageModifierStub: string;
}
export interface DragPreviewOptions {
    mode?: DragPreviewMode | Array<DragPreviewMode>;
    modifier?: ImageModifier;
    numberBadge?: boolean | number;
}
export interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
}
export interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
export interface CommonMethod<T> {
    width(value: Length | undefined): T;
    height(value: Length | undefined): T;
}
export interface CommonAttribute extends CommonMethod<CommonAttribute> {
}
export type CommonInterface = () => CommonAttribute;
export type CustomBuilder = 
/** @memo */
() => void;
export interface OverlayOptions {
    align?: Alignment;
    offset?: OverlayOffset;
}
export interface OverlayOffset {
    x?: number;
    y?: number;
}
export type FractionStop = [
    number,
    number
]
export interface CommonShapeMethod<T> extends CommonMethod<T> {
    stroke: ResourceColor;
    fill: ResourceColor;
    strokeDashOffset: number | string;
    strokeLineCap: LineCapStyle;
    strokeLineJoin: LineJoinStyle;
    strokeMiterLimit: number | string;
    strokeOpacity: number | string | Resource;
    fillOpacity: number | string | Resource;
    strokeWidth: Length;
    antiAlias: boolean;
    strokeDashArray: Array<Length>;
}
export interface LinearGradient_common {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export interface PixelRoundPolicy {
    start?: PixelRoundCalcPolicy;
    top?: PixelRoundCalcPolicy;
    end?: PixelRoundCalcPolicy;
    bottom?: PixelRoundCalcPolicy;
}
export interface LinearGradientBlurOptions {
    fractionStops: Array<FractionStop>;
    direction: GradientDirection;
}
export interface MotionBlurAnchor {
    x: number;
    y: number;
}
export interface MotionBlurOptions {
    radius: number;
    anchor: MotionBlurAnchor;
}
export interface LayoutBorderInfo {
    borderWidth: EdgeWidths;
    margin: Margin;
    padding: Padding;
}
export interface LayoutInfo {
    position: Position;
    constraint: ConstraintSizeOptions;
}
export interface LayoutChild {
    stub: string;
}
export interface GeometryInfo extends SizeResult {
    borderWidth: EdgeWidth;
    margin: Margin;
    padding: Padding;
}
export interface Layoutable {
    stub: string;
}
export interface SizeResult {
    width: number;
    height: number;
}
export interface MeasureResult extends SizeResult {
}
export interface NavDestinationInfo {
    _NavDestinationInfoStub: string;
}
export interface NavigationInfo {
    _NavigationInfoStub: string;
}
export interface RouterPageInfo {
    _RouterPageInfoStub: string;
}
export interface UIContext {
    _UIContextStub: string;
}
export interface DrawContext {
    _DrawContextStub: string;
}
export interface VisualEffect {
    _VisualEffectStub: string;
}
export interface Filter {
    _FilterStub: string;
}
export interface Blender {
    _BlenderStub: string;
}
export interface ComponentContent {
    _ComponentContentStub: string;
}
export interface Theme {
    _ThemeStub: string;
}
export interface RectResult {
    x: number;
    y: number;
    width: number;
    height: number;
}
export interface CaretOffset {
    index: number;
    x: number;
    y: number;
}
export enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2
}
export interface ScrollableCommonMethod<T> extends CommonMethod<T> {
    scrollBar: BarState;
    scrollBarColor: Color | number | string;
    scrollBarWidth: number | string;
    nestedScroll: NestedScrollOptions;
    enableScrollInteraction: boolean;
    friction: number | Resource;
    onScroll: ((first: number,last: number) => void);
    onReachStart: (() => void);
    onReachEnd: (() => void);
    onScrollStart: (() => void);
    onScrollStop: (() => void);
    flingSpeedLimit: number;
    clipContent: ContentClipMode | RectShape;
}
export interface ScrollResult {
    offsetRemain: number;
}
export type OnWillScrollCallback = (scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => ScrollResult;
export type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
export type OnMoveHandler = (from: number, to: number) => void;
export interface DynamicNode<T> {
}
export interface EdgeEffectOptions {
    alwaysEnabled: boolean;
}
export interface BackgroundBrightnessOptions {
    rate: number;
    lightUpDegree: number;
}
export interface PointLightStyle {
    lightSource?: LightSource;
    illuminated?: IlluminatedType;
    bloom?: number;
}
export interface LightSource {
    positionX: Dimension;
    positionY: Dimension;
    positionZ: Dimension;
    intensity: number;
    color?: ResourceColor;
}
export interface KeyframeAnimateParam {
    delay?: number;
    iterations?: number;
    onFinish?: (() => void);
}
export interface KeyframeState {
    duration: number;
    curve?: Curve | string | ICurve;
    event: (() => void);
}
export type Callback<T,V = void> = (data: T) => V;
export type HoverCallback = (isHover: boolean, event: HoverEvent) => void;
export type AccessibilityCallback = (isHover: boolean, event: AccessibilityHoverEvent) => void;
export interface VisibleAreaEventOptions {
    ratios: Array<number>;
    expectedUpdateInterval?: number;
}
export type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: number) => void;
export interface UIGestureEvent {
}
export interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
export enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1
}
export enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1
}

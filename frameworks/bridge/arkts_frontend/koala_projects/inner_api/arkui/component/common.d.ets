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
/**
 * @file
 * @kit ArkUI
 */
import { memo_stable } from '@koalaui.runtime.annotations';
import { Resource } from 'global.resource';
import { CircleShape, EllipseShape, PathShape, RectShape } from '@ohos.arkui.shape';
import { LengthMetrics } from 'arkui.Graphics';
import { FocusBoxStyle, FocusPriority } from 'arkui.component.focus';
import { ComponentContent } from 'arkui.ComponentContent';
import { ResizableOptions } from 'arkui.component.image';
import {
    Area,
    ResourceColor,
    Dimension,
    ResourceStr,
    Length,
    EdgeColors,
    LocalizedEdgeColors,
    BorderRadiuses,
    EdgeWidths,
    LocalizedEdgeWidths,
    SizeOptions,
    EdgeStyles,
    Position,
    LocalizedBorderRadiuses,
    ChainWeightOptions,
    Padding,
    LocalizedPadding,
    BorderOptions,
    OutlineOptions,
    EdgeOutlineStyles,
    EdgeOutlineWidths,
    OutlineRadiuses,
    Edges,
    LocalizedEdges,
    LocalizedPosition,
    AccessibilityOptions,
    ConstraintSizeOptions,
} from 'arkui.component.units';
import { BaseGestureEvent, GestureJudgeResult, GestureInfo, GestureType, GestureMask } from 'arkui.component.gesture';
import {
    BorderStyle,
    Color,
    ColoringStrategy,
    HitTestMode,
    Alignment,
    ImageRepeat,
    ImageSize,
    HoverEffect,
    Visibility,
    ItemAlign,
    Direction,
    Axis,
    FunctionKey,
    ModifierKey,
    ObscuredReasons,
    RenderFit,
    ResponseType,
    FocusDrawLevel,
    TransitionType,
} from 'arkui.component.enums';
import { CustomBuilder } from 'arkui.component.builder';
import { PeerNode } from 'arkui.PeerNode';
import { ComponentBase } from 'arkui.ComponentBase';
import {
    LayoutPolicy,
    CrownEvent,
    FocusAxisEvent,
    AxisEvent,
    FocusMovement,
    OnDragEventCallback,
    DropOptions,
    PreviewConfiguration,
    LinearGradientOptions,
    SweepGradientOptions,
    RadialGradientOptions,
    AccessibilitySamePageMode,
    AccessibilityRoleType,
    AccessibilityFocusCallback,
    ReuseOptions,
    BackgroundImageOptions,
    SystemAdaptiveOptions,
    TipsMessageType,
    TipsOptions,
    DrawModifier,
    Rectangle,
    TouchTestInfo,
    TouchResult,
    PixelRoundPolicy,
    BackgroundEffectOptions,
    BorderImageOption,
    OutlineStyle,
    ClickEvent,
    HoverEvent,
    AccessibilityCallback,
    MouseEvent,
    TouchEvent,
    KeyEvent,
    AnimateParam,
    ForegroundEffectOptions,
    TransitionEffect,
    TransitionFinishCallback,
    MotionBlurOptions,
    InvertOptions,
    EffectType,
    TranslateOptions,
    ScaleOptions,
    RotateOptions,
    AlignRuleOption,
    LocalizedAlignRuleOptions,
    PreDragStatus,
    GestureModifier,
    BackgroundBrightnessOptions,
    ClickEffect,
    DragEvent,
    DragItemInfo,
    MotionPathOptions,
    ShadowOptions,
    ShadowStyle,
    ProgressMask,
    GeometryTransitionOptions,
    StateStyles,
    PixelStretchEffectOptions,
    GestureRecognizerJudgeBeginCallback,
    ShouldBuiltInRecognizerParallelWithCallback,
    SizeChangeCallback,
    SafeAreaType,
    BlurStyle,
    BackgroundBlurStyleOptions,
    BlurOptions,
    LinearGradientBlurOptions,
    sharedTransitionOptions,
    ChainStyle,
    DragPreviewOptions,
    DragInteractionOptions,
    OverlayOptions,
    BlendApplyType,
    PopupOptions,
    CustomPopupOptions,
    MenuElement,
    MenuOptions,
    ContextMenuOptions,
    ModalTransition,
    ContentCoverOptions,
    SheetOptions,
    VisibleAreaChangeCallback,
    VisibleAreaEventOptions,
    SafeAreaEdge,
    ForegroundBlurStyleOptions,
    AttributeModifier,
    UIGestureEvent,
} from 'arkui.component.common';
import uiEffect from '@ohos.graphics.uiEffect';
import image from '@ohos.multimedia.image';
import uniformTypeDescriptor from '@ohos.data.uniformTypeDescriptor';
import drawing from '@ohos.graphics.drawing';

type KPointer = LockGrantedCallback;
type int32 = int;

type PixelMap = image.PixelMap;
type UniformDataType = uniformTypeDescriptor.UniformDataType;
type BlendMode = drawing.BlendMode;
type VisualEffect = uiEffect.VisualEffect;
type Filter = uiEffect.Filter;
type BrightnessBlender = uiEffect.BrightnessBlender;

export interface Literal_Alignment_align {
    align?: Alignment;
}

export interface Literal_Number_offset_span {
    span: number;
    offset: number;
}

export interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}

export interface Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs {
    xs?: number | Literal_Number_offset_span;
    sm?: number | Literal_Number_offset_span;
    md?: number | Literal_Number_offset_span;
    lg?: number | Literal_Number_offset_span;
}

export interface TransformationMatrix {
    matrix4x4: Array<number>;
}

export interface CommonMethod {
    width(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    height(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    drawModifier(value: DrawModifier | undefined): this;
    responseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    size(value: SizeOptions | undefined): this;
    constraintSize(value: ConstraintSizeOptions | undefined): this;
    touchable(value: boolean | undefined): this;
    hitTestBehavior(value: HitTestMode | undefined): this;
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this;
    layoutWeight(value: number | string | undefined): this;
    chainWeight(value: ChainWeightOptions | undefined): this;
    padding(value: Padding | Length | LocalizedPadding | undefined): this;
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this;
    margin(value: Padding | Length | LocalizedPadding | undefined): this;
    backgroundColor(value: ResourceColor | undefined): this;
    pixelRound(value: PixelRoundPolicy | undefined): this;
    backgroundImageSize(value: SizeOptions | ImageSize | undefined): this;
    backgroundImagePosition(value: Position | Alignment | undefined): this;
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this;
    backgroundImageResizable(value: ResizableOptions | undefined): this;
    foregroundEffect(value: ForegroundEffectOptions | undefined): this;
    visualEffect(value: VisualEffect | undefined): this;
    backgroundFilter(value: Filter | undefined): this;
    foregroundFilter(value: Filter | undefined): this;
    compositingFilter(value: Filter | undefined): this;
    opacity(value: number | Resource | undefined): this;
    border(value: BorderOptions | undefined): this;
    borderStyle(value: BorderStyle | EdgeStyles | undefined): this;
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this;
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this;
    borderImage(value: BorderImageOption | undefined): this;
    outline(value: OutlineOptions | undefined): this;
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this;
    outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this;
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    outlineRadius(value: Dimension | OutlineRadiuses | undefined): this;
    foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this;
    onClick(event: ((event: ClickEvent) => void) | undefined): this;
    onHover(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): this;
    onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this;
    onAccessibilityHover(value: AccessibilityCallback | undefined): this;
    hoverEffect(value: HoverEffect | undefined): this;
    onMouse(value: ((event: MouseEvent) => void) | undefined): this;
    onTouch(value: ((event: TouchEvent) => void) | undefined): this;
    onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this;
    onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this;
    onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this;
    onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this;
    focusable(value: boolean | undefined): this;
    nextFocus(value: FocusMovement | undefined): this;
    tabStop(value: boolean | undefined): this;
    onFocus(value: (() => void) | undefined): this;
    onBlur(value: (() => void) | undefined): this;
    tabIndex(value: number | undefined): this;
    defaultFocus(value: boolean | undefined): this;
    groupDefaultFocus(value: boolean | undefined): this;
    focusOnTouch(value: boolean | undefined): this;
    focusBox(value: FocusBoxStyle | undefined): this;
    animationStart(value: AnimateParam | undefined): this;
    animationStop(value: AnimateParam | undefined): this;
    transition(
        effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined,
        onFinish?: TransitionFinishCallback
    ): this;
    motionBlur(value: MotionBlurOptions | undefined): this;
    brightness(value: number | undefined): this;
    contrast(value: number | undefined): this;
    grayscale(value: number | undefined): this;
    colorBlend(value: Color | string | Resource | undefined): this;
    saturate(value: number | undefined): this;
    sepia(value: number | undefined): this;
    invert(value: number | InvertOptions | undefined): this;
    hueRotate(value: number | string | undefined): this;
    useShadowBatching(value: boolean | undefined): this;
    useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this;
    renderGroup(value: boolean | undefined): this;
    freeze(value: boolean | undefined): this;
    translate(value: TranslateOptions | undefined): this;
    scale(value: ScaleOptions | undefined): this;
    gridSpan(value: number | undefined): this;
    gridOffset(value: number | undefined): this;
    rotate(value: RotateOptions | undefined): this;
    transform(value: TransformationMatrix | undefined | Object | undefined): this;
    onAppear(value: (() => void) | undefined): this;
    onDisAppear(value: (() => void) | undefined): this;
    onAttach(value: (() => void) | undefined): this;
    onDetach(value: (() => void) | undefined): this;
    onAreaChange(value: ((oldValue: Area, newValue: Area) => void) | undefined): this;
    visibility(value: Visibility | undefined): this;
    flexGrow(value: number | undefined): this;
    flexShrink(value: number | undefined): this;
    flexBasis(value: number | string | undefined): this;
    alignSelf(value: ItemAlign | undefined): this;
    displayPriority(value: number | undefined): this;
    zIndex(value: number | undefined): this;
    direction(value: Direction | undefined): this;
    align(value: Alignment | undefined): this;
    position(value: Position | Edges | LocalizedEdges | undefined): this;
    markAnchor(value: Position | LocalizedPosition | undefined): this;
    offset(value: Position | Edges | LocalizedEdges | undefined): this;
    enabled(value: boolean | undefined): this;
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this;
    alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this;
    aspectRatio(value: number | undefined): this;
    clickEffect(value: ClickEffect | undefined): this;
    onDragStart(value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this;
    onDragEnter(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    onDragMove(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    onDragLeave(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    onDrop(
        eventCallback: ((event: DragEvent, extraParams?: string) => void) | undefined | OnDragEventCallback | undefined,
        dropOptions?: DropOptions
    ): this;
    onDragEnd(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    allowDrop(value: Array<UniformDataType> | Array<string> | undefined): this;
    draggable(value: boolean | undefined): this;
    dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this;
    onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this;
    linearGradient(value: LinearGradientOptions | undefined): this;
    sweepGradient(value: SweepGradientOptions | undefined): this;
    radialGradient(value: RadialGradientOptions | undefined): this;
    motionPath(value: MotionPathOptions | undefined): this;
    shadow(value: ShadowOptions | ShadowStyle | undefined): this;
    clip(value: boolean | undefined): this;
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    mask(value: ProgressMask | undefined): this;
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    key(value: string | undefined): this;
    id(value: string | undefined): this;
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this;
    stateStyles(value: StateStyles | undefined): this;
    restoreId(value: number | undefined): this;
    sphericalEffect(value: number | undefined): this;
    lightUpEffect(value: number | undefined): this;
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this;
    accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this;
    accessibilityText(value: string | undefined | Resource | undefined): this;
    accessibilityNextFocusId(value: string | undefined): this;
    accessibilityDefaultFocus(value: boolean | undefined): this;
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this;
    accessibilityScrollTriggerable(value: boolean | undefined): this;
    accessibilityRole(value: AccessibilityRoleType | undefined): this;
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this;
    accessibilityTextHint(value: string | undefined): this;
    accessibilityDescription(value: string | undefined | Resource | undefined): this;
    accessibilityLevel(value: string | undefined): this;
    accessibilityVirtualNode(value: CustomBuilder | undefined): this;
    accessibilityChecked(value: boolean | undefined): this;
    accessibilitySelected(value: boolean | undefined): this;
    obscured(value: Array<ObscuredReasons> | undefined): this;
    reuseId(value: string | undefined): this;
    reuse(value: ReuseOptions | undefined): this;
    renderFit(value: RenderFit | undefined): this;
    gestureModifier(value: GestureModifier | undefined): this;
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this;
    onGestureJudgeBegin(
        value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined
    ): this;
    onGestureRecognizerJudgeBegin(
        callback_: GestureRecognizerJudgeBeginCallback | undefined,
        exposeInnerGesture?: boolean
    ): this;
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this;
    monopolizeEvents(value: boolean | undefined): this;
    onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this;
    onSizeChange(value: SizeChangeCallback | undefined): this;
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this;
    customProperty(name: string | undefined, value: Object | undefined): this;
    expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this;
    background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this;
    backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this;
    backgroundBlurStyle(
        style: BlurStyle | undefined,
        options?: BackgroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    foregroundBlurStyle(
        style: BlurStyle | undefined,
        options?: ForegroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this;
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this;
    gesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this;
    systemBarEffect(): this;
    backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this;
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this;
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this;
    overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this;
    blendMode(value: BlendMode | undefined, type?: BlendApplyType): this;
    advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this;
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this;
    bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this;
    bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this;
    bindContextMenu(
        content: CustomBuilder | undefined,
        responseType: ResponseType | undefined,
        options?: ContextMenuOptions | undefined
    ): this;
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder | undefined, type?: ContentCoverOptions): this;
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this;
    onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this;
    onVisibleAreaApproximateChange(
        options: VisibleAreaEventOptions | undefined,
        event: VisibleAreaChangeCallback | undefined
    ): this;
    keyboardShortcut(
        value: string | FunctionKey | undefined,
        keys: Array<ModifierKey> | undefined,
        action?: () => void
    ): this;
}

export declare class ArkCommonMethodPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string, flags: int32);
    public static create(component: ComponentBase | undefined, flags: int32): ArkCommonMethodPeer;
    public width0Attribute(value: Length | undefined): void;
    public width1Attribute(value: Length | LayoutPolicy | undefined): void;
    public height0Attribute(value: Length | undefined): void;
    public height1Attribute(value: Length | LayoutPolicy | undefined): void;
    public drawModifierAttribute(value: DrawModifier | undefined): void;
    public responseRegionAttribute(value: Array<Rectangle> | Rectangle | undefined): void;
    public mouseResponseRegionAttribute(value: Array<Rectangle> | Rectangle | undefined): void;
    public sizeAttribute(value: SizeOptions | undefined): void;
    public constraintSizeAttribute(value: ConstraintSizeOptions | undefined): void;
    public touchableAttribute(value: boolean | undefined): void;
    public hitTestBehaviorAttribute(value: HitTestMode | undefined): void;
    public onChildTouchTestAttribute(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): void;
    public layoutWeightAttribute(value: number | string | undefined): void;
    public chainWeightAttribute(value: ChainWeightOptions | undefined): void;
    public paddingAttribute(value: Padding | Length | LocalizedPadding | undefined): void;
    public safeAreaPaddingAttribute(value: Padding | LengthMetrics | LocalizedPadding | undefined): void;
    public marginAttribute(value: Padding | Length | LocalizedPadding | undefined): void;
    public backgroundColor0Attribute(value: ResourceColor | undefined): void;
    public backgroundColor1Attribute(value: ResourceColor | undefined): void;
    public pixelRoundAttribute(value: PixelRoundPolicy | undefined): void;
    public backgroundImageSizeAttribute(value: SizeOptions | ImageSize | undefined): void;
    public backgroundImagePositionAttribute(value: Position | Alignment | undefined): void;
    public backgroundEffect0Attribute(value: BackgroundEffectOptions | undefined): void;
    public backgroundEffect1Attribute(
        options: BackgroundEffectOptions | undefined,
        sysOptions?: SystemAdaptiveOptions
    ): void;
    public backgroundImageResizableAttribute(value: ResizableOptions | undefined): void;
    public foregroundEffectAttribute(value: ForegroundEffectOptions | undefined): void;
    public visualEffectAttribute(value: VisualEffect | undefined): void;
    public backgroundFilterAttribute(value: Filter | undefined): void;
    public foregroundFilterAttribute(value: Filter | undefined): void;
    public compositingFilterAttribute(value: Filter | undefined): void;
    public opacity0Attribute(value: number | Resource | undefined): void;
    public opacity1Attribute(value: number | Resource | undefined): void;
    public borderAttribute(value: BorderOptions | undefined): void;
    public borderStyleAttribute(value: BorderStyle | EdgeStyles | undefined): void;
    public borderWidthAttribute(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): void;
    public borderColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void;
    public borderRadiusAttribute(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): void;
    public borderImageAttribute(value: BorderImageOption | undefined): void;
    public outline0Attribute(value: OutlineOptions | undefined): void;
    public outline1Attribute(value: OutlineOptions | undefined): void;
    public outlineStyle0Attribute(value: OutlineStyle | EdgeOutlineStyles | undefined): void;
    public outlineStyle1Attribute(value: OutlineStyle | EdgeOutlineStyles | undefined): void;
    public outlineWidth0Attribute(value: Dimension | EdgeOutlineWidths | undefined): void;
    public outlineWidth1Attribute(value: Dimension | EdgeOutlineWidths | undefined): void;
    public outlineColor0Attribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void;
    public outlineColor1Attribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void;
    public outlineRadius0Attribute(value: Dimension | OutlineRadiuses | undefined): void;
    public outlineRadius1Attribute(value: Dimension | OutlineRadiuses | undefined): void;
    public foregroundColor0Attribute(value: ResourceColor | ColoringStrategy | undefined): void;
    public onClick0Attribute(value: ((event: ClickEvent) => void) | undefined): void;
    public onClick1Attribute(
        event: ((event: ClickEvent) => void) | undefined,
        distanceThreshold: number | undefined
    ): void;
    public onHoverAttribute(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): void;
    public onHoverMoveAttribute(value: ((parameter: HoverEvent) => void) | undefined): void;
    public onAccessibilityHoverAttribute(value: AccessibilityCallback | undefined): void;
    public hoverEffectAttribute(value: HoverEffect | undefined): void;
    public onMouseAttribute(value: ((event: MouseEvent) => void) | undefined): void;
    public onTouchAttribute(value: ((event: TouchEvent) => void) | undefined): void;
    public onKeyEvent0Attribute(value: ((event: KeyEvent) => void) | undefined): void;
    public onKeyEvent1Attribute(value: ((parameter: KeyEvent) => boolean) | undefined): void;
    public onDigitalCrownAttribute(value: ((parameter: CrownEvent) => void) | undefined): void;
    public onKeyPreImeAttribute(value: ((parameter: KeyEvent) => boolean) | undefined): void;
    public onKeyEventDispatchAttribute(value: ((parameter: KeyEvent) => boolean) | undefined): void;
    public onFocusAxisEventAttribute(value: ((parameter: FocusAxisEvent) => void) | undefined): void;
    public onAxisEventAttribute(value: ((parameter: AxisEvent) => void) | undefined): void;
    public focusableAttribute(value: boolean | undefined): void;
    public nextFocusAttribute(value: FocusMovement | undefined): void;
    public tabStopAttribute(value: boolean | undefined): void;
    public onFocusAttribute(value: (() => void) | undefined): void;
    public onBlurAttribute(value: (() => void) | undefined): void;
    public tabIndexAttribute(value: number | undefined): void;
    public defaultFocusAttribute(value: boolean | undefined): void;
    public groupDefaultFocusAttribute(value: boolean | undefined): void;
    public focusOnTouchAttribute(value: boolean | undefined): void;
    public focusBoxAttribute(value: FocusBoxStyle | undefined): void;
    public animationAttribute(value: AnimateParam | undefined): void;
    public transition0Attribute(value: TransitionOptions | TransitionEffect | undefined): void;
    public transition1Attribute(
        effect: TransitionEffect | undefined,
        onFinish: TransitionFinishCallback | undefined
    ): void;
    public motionBlur0Attribute(value: MotionBlurOptions | undefined): void;
    public motionBlur1Attribute(value: MotionBlurOptions | undefined): void;
    public brightness0Attribute(value: number | undefined): void;
    public brightness1Attribute(value: number | undefined): void;
    public contrast0Attribute(value: number | undefined): void;
    public contrast1Attribute(value: number | undefined): void;
    public grayscale0Attribute(value: number | undefined): void;
    public grayscale1Attribute(value: number | undefined): void;
    public colorBlend0Attribute(value: Color | string | Resource | undefined): void;
    public colorBlend1Attribute(value: Color | string | Resource | undefined): void;
    public saturate0Attribute(value: number | undefined): void;
    public saturate1Attribute(value: number | undefined): void;
    public sepia0Attribute(value: number | undefined): void;
    public invert0Attribute(value: number | InvertOptions | undefined): void;
    public hueRotate0Attribute(value: number | string | undefined): void;
    public hueRotate1Attribute(value: number | string | undefined): void;
    public useShadowBatching0Attribute(value: boolean | undefined): void;
    public useShadowBatching1Attribute(value: boolean | undefined): void;
    public useEffect0Attribute(value: boolean | undefined): void;
    public useEffect1Attribute(useEffect: boolean | undefined, effectType: EffectType | undefined): void;
    public renderGroup0Attribute(value: boolean | undefined): void;
    public freeze0Attribute(value: boolean | undefined): void;
    public translate0Attribute(value: TranslateOptions | undefined): void;
    public translate1Attribute(value: TranslateOptions | undefined): void;
    public scale0Attribute(value: ScaleOptions | undefined): void;
    public scale1Attribute(value: ScaleOptions | undefined): void;
    public gridSpanAttribute(value: number | undefined): void;
    public gridOffsetAttribute(value: number | undefined): void;
    public rotate0Attribute(value: RotateOptions | undefined): void;
    public transform0Attribute(value: TransformationMatrix | undefined): void;
    public transform1Attribute(value: Object | undefined): void;
    public onAppearAttribute(value: (() => void) | undefined): void;
    public onDisAppearAttribute(value: (() => void) | undefined): void;
    public onAttachAttribute(value: (() => void) | undefined): void;
    public onDetachAttribute(value: (() => void) | undefined): void;
    public onAreaChangeAttribute(value: ((oldValue: Area, newValue: Area) => void) | undefined): void;
    public visibilityAttribute(value: Visibility | undefined): void;
    public flexGrowAttribute(value: number | undefined): void;
    public flexShrinkAttribute(value: number | undefined): void;
    public flexBasisAttribute(value: number | string | undefined): void;
    public alignSelfAttribute(value: ItemAlign | undefined): void;
    public displayPriorityAttribute(value: number | undefined): void;
    public zIndexAttribute(value: number | undefined): void;
    public directionAttribute(value: Direction | undefined): void;
    public alignAttribute(value: Alignment | undefined): void;
    public positionAttribute(value: Position | Edges | LocalizedEdges | undefined): void;
    public markAnchorAttribute(value: Position | LocalizedPosition | undefined): void;
    public offsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void;
    public enabledAttribute(value: boolean | undefined): void;
    public useSizeTypeAttribute(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): void;
    public alignRules0Attribute(value: AlignRuleOption | LocalizedAlignRuleOptions | undefined): void;
    public alignRules1Attribute(value: LocalizedAlignRuleOptions | undefined): void;
    public aspectRatioAttribute(value: number | undefined): void;
    public clickEffect0Attribute(value: ClickEffect | undefined): void;
    public clickEffect1Attribute(value: ClickEffect | undefined): void;
    public onDragStartAttribute(
        value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    ): void;
    public onDragEnterAttribute(value: ((event: DragEvent, extraParams?: string) => void) | undefined): void;
    public onDragMoveAttribute(value: ((event: DragEvent, extraParams?: string) => void) | undefined): void;
    public onDragLeaveAttribute(value: ((event: DragEvent, extraParams?: string) => void) | undefined): void;
    public onDrop0Attribute(value: ((event: DragEvent, extraParams?: string) => void) | undefined): void;
    public onDrop1Attribute(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions): void;
    public onDragEndAttribute(value: ((event: DragEvent, extraParams?: string) => void) | undefined): void;
    public allowDropAttribute(value: Array<UniformDataType> | Array<string> | undefined): void;
    public draggableAttribute(value: boolean | undefined): void;
    public dragPreview0Attribute(value: CustomBuilder | DragItemInfo | string | undefined): void;
    public dragPreview1Attribute(
        preview: CustomBuilder | DragItemInfo | string | undefined,
        config?: PreviewConfiguration
    ): void;
    public onPreDragAttribute(value: ((parameter: PreDragStatus) => void) | undefined): void;
    public linearGradient0Attribute(value: LinearGradientOptions | undefined): void;
    public linearGradient1Attribute(value: LinearGradientOptions | undefined): void;
    public sweepGradient0Attribute(value: SweepGradientOptions | undefined): void;
    public sweepGradient1Attribute(value: SweepGradientOptions | undefined): void;
    public radialGradient0Attribute(value: RadialGradientOptions | undefined): void;
    public radialGradient1Attribute(value: RadialGradientOptions | undefined): void;
    public motionPathAttribute(value: MotionPathOptions | undefined): void;
    public shadow0Attribute(value: ShadowOptions | ShadowStyle | undefined): void;
    public shadow1Attribute(value: ShadowOptions | ShadowStyle | undefined): void;
    public clip0Attribute(value: boolean | undefined): void;
    public clip1Attribute(value: boolean | undefined): void;
    public clip2Attribute(value: boolean | undefined): void;
    public clipShape0Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void;
    public clipShape1Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void;
    public mask0Attribute(value: ProgressMask | undefined): void;
    public mask1Attribute(value: ProgressMask | undefined): void;
    public mask2Attribute(value: ProgressMask | undefined): void;
    public maskShape0Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void;
    public maskShape1Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void;
    public keyAttribute(value: string | undefined): void;
    public idAttribute(value: string | undefined): void;
    public geometryTransition0Attribute(value: string | undefined): void;
    public geometryTransition1Attribute(id: string | undefined, options?: GeometryTransitionOptions): void;
    public stateStylesAttribute(value: StateStyles | undefined): void;
    public restoreIdAttribute(value: number | undefined): void;
    public sphericalEffect0Attribute(value: number | undefined): void;
    public sphericalEffect1Attribute(value: number | undefined): void;
    public lightUpEffect0Attribute(value: number | undefined): void;
    public lightUpEffect1Attribute(value: number | undefined): void;
    public pixelStretchEffect0Attribute(value: PixelStretchEffectOptions | undefined): void;
    public pixelStretchEffect1Attribute(value: PixelStretchEffectOptions | undefined): void;
    public accessibilityGroup0Attribute(value: boolean | undefined): void;
    public accessibilityGroup1Attribute(
        isGroup: boolean | undefined,
        accessibilityOptions: AccessibilityOptions | undefined
    ): void;
    public accessibilityText0Attribute(value: string | undefined): void;
    public accessibilityText1Attribute(value: Resource | undefined): void;
    public accessibilityNextFocusIdAttribute(value: string | undefined): void;
    public accessibilityDefaultFocusAttribute(value: boolean | undefined): void;
    public accessibilityUseSamePageAttribute(value: AccessibilitySamePageMode | undefined): void;
    public accessibilityScrollTriggerableAttribute(value: boolean | undefined): void;
    public accessibilityRoleAttribute(value: AccessibilityRoleType | undefined): void;
    public onAccessibilityFocusAttribute(value: AccessibilityFocusCallback | undefined): void;
    public accessibilityTextHintAttribute(value: string | undefined): void;
    public accessibilityDescription0Attribute(value: string | undefined): void;
    public accessibilityDescription1Attribute(value: Resource | undefined): void;
    public accessibilityLevelAttribute(value: string | undefined): void;
    public accessibilityVirtualNodeAttribute(value: CustomBuilder | undefined): void;
    public accessibilityCheckedAttribute(value: boolean | undefined): void;
    public accessibilitySelectedAttribute(value: boolean | undefined): void;
    public obscuredAttribute(value: Array<ObscuredReasons> | undefined): void;
    public reuseIdAttribute(value: string | undefined): void;
    public reuseAttribute(value: ReuseOptions | undefined): void;
    public renderFit0Attribute(value: RenderFit | undefined): void;
    public renderFit1Attribute(value: RenderFit | undefined): void;
    public gestureModifierAttribute(value: GestureModifier | undefined): void;
    public backgroundBrightness0Attribute(value: BackgroundBrightnessOptions | undefined): void;
    public backgroundBrightness1Attribute(value: BackgroundBrightnessOptions | undefined): void;
    public onGestureJudgeBeginAttribute(
        value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined
    ): void;
    public onGestureRecognizerJudgeBegin0Attribute(value: GestureRecognizerJudgeBeginCallback | undefined): void;
    public onGestureRecognizerJudgeBegin1Attribute(
        callback_: GestureRecognizerJudgeBeginCallback | undefined,
        exposeInnerGesture: boolean | undefined
    ): void;
    public shouldBuiltInRecognizerParallelWithAttribute(
        value: ShouldBuiltInRecognizerParallelWithCallback | undefined
    ): void;
    public monopolizeEventsAttribute(value: boolean | undefined): void;
    public onTouchInterceptAttribute(value: ((parameter: TouchEvent) => HitTestMode) | undefined): void;
    public onSizeChangeAttribute(value: SizeChangeCallback | undefined): void;
    public accessibilityFocusDrawLevelAttribute(value: FocusDrawLevel | undefined): void;
    public customPropertyAttribute(name: string | undefined, value: Object | undefined): void;
    public expandSafeAreaAttribute(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): void;
    public backgroundAttribute(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): void;
    public backgroundImage0Attribute(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat): void;
    public backgroundImage1Attribute(src: ResourceStr | PixelMap | undefined, options?: BackgroundImageOptions): void;
    public backgroundBlurStyle1Attribute(
        style: BlurStyle | undefined,
        options?: BackgroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): void;
    public foregroundBlurStyle0Attribute(value: BlurStyle | undefined, options?: ForegroundBlurStyleOptions): void;
    public foregroundBlurStyle1Attribute(
        style: BlurStyle | undefined,
        options?: ForegroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): void;
    public focusScopeId0Attribute(id: string | undefined, isGroup?: boolean): void;
    public focusScopeId1Attribute(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): void;
    public focusScopePriorityAttribute(scopeId: string | undefined, priority?: FocusPriority): void;
    public blur0Attribute(value: number | undefined, options?: BlurOptions): void;
    public blur1Attribute(
        blurRadius: number | undefined,
        options?: BlurOptions,
        sysOptions?: SystemAdaptiveOptions
    ): void;
    public linearGradientBlur0Attribute(
        value: number | undefined,
        options: LinearGradientBlurOptions | undefined
    ): void;
    public linearGradientBlur1Attribute(
        blurRadius: number | undefined,
        options: LinearGradientBlurOptions | undefined
    ): void;
    public systemBarEffectAttribute(): void;
    public backdropBlur0Attribute(value: number | undefined, options?: BlurOptions): void;
    public backdropBlur1Attribute(
        radius: number | undefined,
        options?: BlurOptions,
        sysOptions?: SystemAdaptiveOptions
    ): void;
    public sharedTransitionAttribute(id: string | undefined, options?: sharedTransitionOptions): void;
    public chainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void;
    public dragPreviewOptionsAttribute(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): void;
    public overlayAttribute(
        value: string | CustomBuilder | ComponentContent | undefined,
        options?: OverlayOptions
    ): void;
    public blendMode0Attribute(value: BlendMode | undefined, type?: BlendApplyType): void;
    public blendMode1Attribute(mode: BlendMode | undefined, type?: BlendApplyType): void;
    public advancedBlendModeAttribute(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): void;
    public bindTipsAttribute(message: TipsMessageType | undefined, options?: TipsOptions): void;
    public bindPopupAttribute(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): void;
    public bindMenu0Attribute(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): void;
    public bindMenu1Attribute(
        isShow: boolean | undefined,
        content: Array<MenuElement> | CustomBuilder | undefined,
        options?: MenuOptions
    ): void;
    public bindContextMenu0Attribute(
        content: CustomBuilder | undefined,
        responseType: ResponseType | undefined,
        options?: ContextMenuOptions
    ): void;
    public bindContextMenu1Attribute(
        isShown: boolean | undefined,
        content: CustomBuilder | undefined,
        options?: ContextMenuOptions
    ): void;
    public bindContentCover0Attribute(
        isShow: boolean | undefined,
        builder: CustomBuilder | undefined,
        type?: ModalTransition
    ): void;
    public bindContentCover1Attribute(
        isShow: boolean | undefined,
        builder: CustomBuilder | undefined,
        options?: ContentCoverOptions
    ): void;
    public bindSheetAttribute(
        isShow: boolean | undefined,
        builder: CustomBuilder | undefined,
        options?: SheetOptions
    ): void;
    public onVisibleAreaChangeAttribute(
        ratios: Array<number> | undefined,
        event: VisibleAreaChangeCallback | undefined
    ): void;
    public onVisibleAreaApproximateChangeAttribute(
        options: VisibleAreaEventOptions | undefined,
        event: VisibleAreaChangeCallback | undefined
    ): void;
    public keyboardShortcutAttribute(
        value: string | FunctionKey | undefined,
        keys: Array<ModifierKey> | undefined,
        action?: () => void
    ): void;
}

@memo_stable() export declare class ArkCommonMethodComponent extends ComponentBase implements CommonMethod {
    public initAttributeSet<T>(modifier: AttributeModifier<T>): void;
    public getPeer(): ArkCommonMethodPeer;
    public getOrCreateGestureEvent(): UIGestureEvent;
    public width(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    public height(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    public drawModifier(value: DrawModifier | undefined): this;
    public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    public size(value: SizeOptions | undefined): this;
    public constraintSize(value: ConstraintSizeOptions | undefined): this;
    public touchable(value: boolean | undefined): this;
    public hitTestBehavior(value: HitTestMode | undefined): this;
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this;
    public layoutWeight(value: number | string | undefined): this;
    public chainWeight(value: ChainWeightOptions | undefined): this;
    public padding(value: Padding | Length | LocalizedPadding | undefined): this;
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this;
    public margin(value: Padding | Length | LocalizedPadding | undefined): this;
    public backgroundColor(value: ResourceColor | undefined): this;
    public pixelRound(value: PixelRoundPolicy | undefined): this;
    public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this;
    public backgroundImagePosition(value: Position | Alignment | undefined): this;
    public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this;
    public backgroundImageResizable(value: ResizableOptions | undefined): this;
    public foregroundEffect(value: ForegroundEffectOptions | undefined): this;
    public visualEffect(value: VisualEffect | undefined): this;
    public backgroundFilter(value: Filter | undefined): this;
    public foregroundFilter(value: Filter | undefined): this;
    public compositingFilter(value: Filter | undefined): this;
    public opacity(value: number | Resource | undefined): this;
    public border(value: BorderOptions | undefined): this;
    public borderStyle(value: BorderStyle | EdgeStyles | undefined): this;
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this;
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this;
    public borderImage(value: BorderImageOption | undefined): this;
    public outline(value: OutlineOptions | undefined): this;
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this;
    public outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this;
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    public outlineRadius(value: Dimension | OutlineRadiuses | undefined): this;
    public foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this;
    public onClick(event: ((event: ClickEvent) => void) | undefined): this;
    public onHover(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): this;
    public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this;
    public onAccessibilityHover(value: AccessibilityCallback | undefined): this;
    public hoverEffect(value: HoverEffect | undefined): this;
    public onMouse(value: ((event: MouseEvent) => void) | undefined): this;
    public onTouch(value: ((event: TouchEvent) => void) | undefined): this;
    public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this;
    public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this;
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this;
    public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this;
    public focusable(value: boolean | undefined): this;
    public nextFocus(value: FocusMovement | undefined): this;
    public tabStop(value: boolean | undefined): this;
    public onFocus(value: (() => void) | undefined): this;
    public onBlur(value: (() => void) | undefined): this;
    public tabIndex(value: number | undefined): this;
    public defaultFocus(value: boolean | undefined): this;
    public groupDefaultFocus(value: boolean | undefined): this;
    public focusOnTouch(value: boolean | undefined): this;
    public focusBox(value: FocusBoxStyle | undefined): this;
    public animationStart(value: AnimateParam | undefined): this;
    public animationStop(value: AnimateParam | undefined): this;
    public transition(
        effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined,
        onFinish?: TransitionFinishCallback
    ): this;
    public motionBlur(value: MotionBlurOptions | undefined): this;
    public brightness(value: number | undefined): this;
    public contrast(value: number | undefined): this;
    public grayscale(value: number | undefined): this;
    public colorBlend(value: Color | string | Resource | undefined): this;
    public saturate(value: number | undefined): this;
    public sepia(value: number | undefined): this;
    public invert(value: number | InvertOptions | undefined): this;
    public hueRotate(value: number | string | undefined): this;
    public useShadowBatching(value: boolean | undefined): this;
    public useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this;
    public renderGroup(value: boolean | undefined): this;
    public freeze(value: boolean | undefined): this;
    public translate(value: TranslateOptions | undefined): this;
    public scale(value: ScaleOptions | undefined): this;
    public gridSpan(value: number | undefined): this;
    public gridOffset(value: number | undefined): this;
    public rotate(value: RotateOptions | undefined): this;
    public transform(value: TransformationMatrix | undefined | Object | undefined): this;
    public onAppear(value: (() => void) | undefined): this;
    public onDisAppear(value: (() => void) | undefined): this;
    public onAttach(value: (() => void) | undefined): this;
    public onDetach(value: (() => void) | undefined): this;
    public onAreaChange(value: ((oldValue: Area, newValue: Area) => void) | undefined): this;
    public visibility(value: Visibility | undefined): this;
    public flexGrow(value: number | undefined): this;
    public flexShrink(value: number | undefined): this;
    public flexBasis(value: number | string | undefined): this;
    public alignSelf(value: ItemAlign | undefined): this;
    public displayPriority(value: number | undefined): this;
    public zIndex(value: number | undefined): this;
    public direction(value: Direction | undefined): this;
    public align(value: Alignment | undefined): this;
    public position(value: Position | Edges | LocalizedEdges | undefined): this;
    public markAnchor(value: Position | LocalizedPosition | undefined): this;
    public offset(value: Position | Edges | LocalizedEdges | undefined): this;
    public enabled(value: boolean | undefined): this;
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this;
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this;
    public aspectRatio(value: number | undefined): this;
    public clickEffect(value: ClickEffect | undefined): this;
    public onDragStart(
        value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    ): this;
    public onDragEnter(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDragMove(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDragLeave(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDrop(
        eventCallback: ((event: DragEvent, extraParams?: string) => void) | undefined | OnDragEventCallback | undefined,
        dropOptions?: DropOptions
    ): this;
    public onDragEnd(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public allowDrop(value: Array<UniformDataType> | Array<string> | undefined): this;
    public draggable(value: boolean | undefined): this;
    public dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this;
    public onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this;
    public linearGradient(value: LinearGradientOptions | undefined): this;
    public sweepGradient(value: SweepGradientOptions | undefined): this;
    public radialGradient(value: RadialGradientOptions | undefined): this;
    public motionPath(value: MotionPathOptions | undefined): this;
    public shadow(value: ShadowOptions | ShadowStyle | undefined): this;
    public clip(value: boolean | undefined): this;
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    public mask(value: ProgressMask | undefined): this;
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    public key(value: string | undefined): this;
    public id(value: string | undefined): this;
    public geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this;
    public stateStyles(value: StateStyles | undefined): this;
    public restoreId(value: number | undefined): this;
    public sphericalEffect(value: number | undefined): this;
    public lightUpEffect(value: number | undefined): this;
    public pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this;
    public accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this;
    public accessibilityText(value: string | undefined | Resource | undefined): this;
    public accessibilityNextFocusId(value: string | undefined): this;
    public accessibilityDefaultFocus(value: boolean | undefined): this;
    public accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this;
    public accessibilityScrollTriggerable(value: boolean | undefined): this;
    public accessibilityRole(value: AccessibilityRoleType | undefined): this;
    public onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this;
    public accessibilityTextHint(value: string | undefined): this;
    public accessibilityDescription(value: string | undefined | Resource | undefined): this;
    public accessibilityLevel(value: string | undefined): this;
    public accessibilityVirtualNode(value: CustomBuilder | undefined): this;
    public accessibilityChecked(value: boolean | undefined): this;
    public accessibilitySelected(value: boolean | undefined): this;
    public obscured(value: Array<ObscuredReasons> | undefined): this;
    public reuseId(value: string | undefined): this;
    public reuse(value: ReuseOptions | undefined): this;
    public renderFit(value: RenderFit | undefined): this;
    public gestureModifier(value: GestureModifier | undefined): this;
    public backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this;
    public onGestureJudgeBegin(
        value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined
    ): this;
    public onGestureRecognizerJudgeBegin(
        callback_: GestureRecognizerJudgeBeginCallback | undefined,
        exposeInnerGesture?: boolean
    ): this;
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this;
    public monopolizeEvents(value: boolean | undefined): this;
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this;
    public onSizeChange(value: SizeChangeCallback | undefined): this;
    public accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this;
    public customProperty(name: string | undefined, value: Object | undefined): this;
    public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this;
    public background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this;
    public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this;
    public backgroundBlurStyle(
        style: BlurStyle | undefined,
        options?: BackgroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    public foregroundBlurStyle(
        style: BlurStyle | undefined,
        options?: ForegroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this;
    public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this;
    public gesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    public linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this;
    public systemBarEffect(): this;
    public backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    public sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this;
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this;
    public dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this;
    public overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this;
    public blendMode(value: BlendMode | undefined, type?: BlendApplyType): this;
    public advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this;
    public bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this;
    public bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this;
    public bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this;
    public bindContextMenu(
        content: CustomBuilder | undefined,
        responseType: ResponseType | undefined,
        options?: ContextMenuOptions | undefined
    ): this;
    public bindContentCover(
        isShow: boolean | undefined,
        builder: CustomBuilder | undefined,
        type?: ContentCoverOptions
    ): this;
    public bindSheet(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this;
    public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this;
    public onVisibleAreaApproximateChange(
        options: VisibleAreaEventOptions | undefined,
        event: VisibleAreaChangeCallback | undefined
    ): this;
    public keyboardShortcut(
        value: string | FunctionKey | undefined,
        keys: Array<ModifierKey> | undefined,
        action?: () => void
    ): this;
    public applyModifierByState<T>(isAttributeUpdater: boolean, modifier: AttributeModifier<T>): void;
    public applyAttributesFinish(): void;
}

export declare class ArkCommonMethodStyle implements CommonMethod {
    public width_value?: Length | undefined;
    public height_value?: Length | undefined;
    public drawModifier_value?: DrawModifier | undefined;
    public responseRegion_value?: Array<Rectangle> | Rectangle | undefined;
    public mouseResponseRegion_value?: Array<Rectangle> | Rectangle | undefined;
    public size_value?: SizeOptions | undefined;
    public constraintSize_value?: ConstraintSizeOptions | undefined;
    public touchable_value?: boolean | undefined;
    public hitTestBehavior_value?: HitTestMode | undefined;
    public onChildTouchTest_value?: ((value: Array<TouchTestInfo>) => TouchResult) | undefined;
    public layoutWeight_value?: number | string | undefined;
    public chainWeight_value?: ChainWeightOptions | undefined;
    public padding_value?: Padding | Length | LocalizedPadding | undefined;
    public safeAreaPadding_value?: Padding | LengthMetrics | LocalizedPadding | undefined;
    public margin_value?: Padding | Length | LocalizedPadding | undefined;
    public backgroundColor_value?: ResourceColor | undefined;
    public pixelRound_value?: PixelRoundPolicy | undefined;
    public backgroundImageSize_value?: SizeOptions | ImageSize | undefined;
    public backgroundImagePosition_value?: Position | Alignment | undefined;
    public backgroundEffect_value?: BackgroundEffectOptions | undefined;
    public backgroundImageResizable_value?: ResizableOptions | undefined;
    public foregroundEffect_value?: ForegroundEffectOptions | undefined;
    public visualEffect_value?: VisualEffect | undefined;
    public backgroundFilter_value?: Filter | undefined;
    public foregroundFilter_value?: Filter | undefined;
    public compositingFilter_value?: Filter | undefined;
    public opacity_value?: number | Resource | undefined;
    public border_value?: BorderOptions | undefined;
    public borderStyle_value?: BorderStyle | EdgeStyles | undefined;
    public borderWidth_value?: Length | EdgeWidths | LocalizedEdgeWidths | undefined;
    public borderColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined;
    public borderRadius_value?: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined;
    public borderImage_value?: BorderImageOption | undefined;
    public outline_value?: OutlineOptions | undefined;
    public outlineStyle_value?: OutlineStyle | EdgeOutlineStyles | undefined;
    public outlineWidth_value?: Dimension | EdgeOutlineWidths | undefined;
    public outlineColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined;
    public outlineRadius_value?: Dimension | OutlineRadiuses | undefined;
    public foregroundColor_value?: ResourceColor | ColoringStrategy | undefined;
    public onClick_value?: ((event: ClickEvent) => void) | undefined;
    public onHover_value?: ((isHover: boolean, event: HoverEvent) => void) | undefined;
    public onHoverMove_value?: ((parameter: HoverEvent) => void) | undefined;
    public onAccessibilityHover_value?: AccessibilityCallback | undefined;
    public hoverEffect_value?: HoverEffect | undefined;
    public onMouse_value?: ((event: MouseEvent) => void) | undefined;
    public onTouch_value?: ((event: TouchEvent) => void) | undefined;
    public onKeyEvent_value?: ((event: KeyEvent) => void) | undefined;
    public onDigitalCrown_value?: ((parameter: CrownEvent) => void) | undefined;
    public onKeyPreIme_value?: ((parameter: KeyEvent) => boolean) | undefined;
    public onKeyEventDispatch_value?: ((parameter: KeyEvent) => boolean) | undefined;
    public onFocusAxisEvent_value?: ((parameter: FocusAxisEvent) => void) | undefined;
    public onAxisEvent_value?: ((parameter: AxisEvent) => void) | undefined;
    public focusable_value?: boolean | undefined;
    public nextFocus_value?: FocusMovement | undefined;
    public tabStop_value?: boolean | undefined;
    public onFocus_value?: (() => void) | undefined;
    public onBlur_value?: (() => void) | undefined;
    public tabIndex_value?: number | undefined;
    public defaultFocus_value?: boolean | undefined;
    public groupDefaultFocus_value?: boolean | undefined;
    public focusOnTouch_value?: boolean | undefined;
    public focusBox_value?: FocusBoxStyle | undefined;
    public animation_value?: AnimateParam | undefined;
    public transition_value?: TransitionOptions | TransitionEffect | undefined;
    public motionBlur_value?: MotionBlurOptions | undefined;
    public brightness_value?: number | undefined;
    public contrast_value?: number | undefined;
    public grayscale_value?: number | undefined;
    public colorBlend_value?: Color | string | Resource | undefined;
    public saturate_value?: number | undefined;
    public sepia_value?: number | undefined;
    public invert_value?: number | InvertOptions | undefined;
    public hueRotate_value?: number | string | undefined;
    public useShadowBatching_value?: boolean | undefined;
    public useEffect_value?: boolean | undefined;
    public renderGroup_value?: boolean | undefined;
    public freeze_value?: boolean | undefined;
    public translate_value?: TranslateOptions | undefined;
    public scale_value?: ScaleOptions | undefined;
    public gridSpan_value?: number | undefined;
    public gridOffset_value?: number | undefined;
    public rotate_value?: RotateOptions | undefined;
    public transform_value?: TransformationMatrix | undefined;
    public onAppear_value?: (() => void) | undefined;
    public onDisAppear_value?: (() => void) | undefined;
    public onAttach_value?: (() => void) | undefined;
    public onDetach_value?: (() => void) | undefined;
    public onAreaChange_value?: ((oldValue: Area, newValue: Area) => void) | undefined;
    public visibility_value?: Visibility | undefined;
    public flexGrow_value?: number | undefined;
    public flexShrink_value?: number | undefined;
    public flexBasis_value?: number | string | undefined;
    public alignSelf_value?: ItemAlign | undefined;
    public displayPriority_value?: number | undefined;
    public zIndex_value?: number | undefined;
    public direction_value?: Direction | undefined;
    public align_value?: Alignment | undefined;
    public position_value?: Position | Edges | LocalizedEdges | undefined;
    public markAnchor_value?: Position | LocalizedPosition | undefined;
    public offset_value?: Position | Edges | LocalizedEdges | undefined;
    public enabled_value?: boolean | undefined;
    public useSizeType_value?: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined;
    public alignRules_value?: AlignRuleOption | LocalizedAlignRuleOptions | undefined;
    public aspectRatio_value?: number | undefined;
    public clickEffect_value?: ClickEffect | undefined;
    public onDragStart_value?: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined;
    public onDragEnter_value?: ((event: DragEvent, extraParams?: string) => void) | undefined;
    public onDragMove_value?: ((event: DragEvent, extraParams?: string) => void) | undefined;
    public onDragLeave_value?: ((event: DragEvent, extraParams?: string) => void) | undefined;
    public onDrop_value?: ((event: DragEvent, extraParams?: string) => void) | undefined;
    public onDragEnd_value?: ((event: DragEvent, extraParams?: string) => void) | undefined;
    public allowDrop_value?: Array<UniformDataType> | Array<string> | undefined;
    public draggable_value?: boolean | undefined;
    public dragPreview_value?: CustomBuilder | DragItemInfo | string | undefined;
    public onPreDrag_value?: ((parameter: PreDragStatus) => void) | undefined;
    public linearGradient_value?: LinearGradientOptions | undefined;
    public sweepGradient_value?: SweepGradientOptions | undefined;
    public radialGradient_value?: RadialGradientOptions | undefined;
    public motionPath_value?: MotionPathOptions | undefined;
    public shadow_value?: ShadowOptions | ShadowStyle | undefined;
    public clip_value?: boolean | undefined;
    public clipShape_value?: CircleShape | EllipseShape | PathShape | RectShape | undefined;
    public mask_value?: ProgressMask | undefined;
    public maskShape_value?: CircleShape | EllipseShape | PathShape | RectShape | undefined;
    public key_value?: string | undefined;
    public id_value?: string | undefined;
    public geometryTransition_value?: string | undefined;
    public stateStyles_value?: StateStyles | undefined;
    public restoreId_value?: number | undefined;
    public sphericalEffect_value?: number | undefined;
    public lightUpEffect_value?: number | undefined;
    public pixelStretchEffect_value?: PixelStretchEffectOptions | undefined;
    public accessibilityGroup_value?: boolean | undefined;
    public accessibilityText_value?: string | undefined;
    public accessibilityNextFocusId_value?: string | undefined;
    public accessibilityDefaultFocus_value?: boolean | undefined;
    public accessibilityUseSamePage_value?: AccessibilitySamePageMode | undefined;
    public accessibilityScrollTriggerable_value?: boolean | undefined;
    public accessibilityRole_value?: AccessibilityRoleType | undefined;
    public onAccessibilityFocus_value?: AccessibilityFocusCallback | undefined;
    public accessibilityTextHint_value?: string | undefined;
    public accessibilityDescription_value?: string | undefined;
    public accessibilityLevel_value?: string | undefined;
    public accessibilityVirtualNode_value?: CustomBuilder | undefined;
    public accessibilityChecked_value?: boolean | undefined;
    public accessibilitySelected_value?: boolean | undefined;
    public obscured_value?: Array<ObscuredReasons> | undefined;
    public reuseId_value?: string | undefined;
    public reuse_value?: ReuseOptions | undefined;
    public renderFit_value?: RenderFit | undefined;
    public gestureModifier_value?: GestureModifier | undefined;
    public backgroundBrightness_value?: BackgroundBrightnessOptions | undefined;
    public onGestureJudgeBegin_value?:
        ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)
        | undefined;
    public onGestureRecognizerJudgeBegin_value?: GestureRecognizerJudgeBeginCallback | undefined;
    public shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback | undefined;
    public monopolizeEvents_value?: boolean | undefined;
    public onTouchIntercept_value?: ((parameter: TouchEvent) => HitTestMode) | undefined;
    public onSizeChange_value?: SizeChangeCallback | undefined;
    public accessibilityFocusDrawLevel_value?: FocusDrawLevel | undefined;
    public width(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    public height(value: Length | undefined | Length | LayoutPolicy | undefined): this;
    public drawModifier(value: DrawModifier | undefined): this;
    public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    public size(value: SizeOptions | undefined): this;
    public constraintSize(value: ConstraintSizeOptions | undefined): this;
    public touchable(value: boolean | undefined): this;
    public hitTestBehavior(value: HitTestMode | undefined): this;
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this;
    public layoutWeight(value: number | string | undefined): this;
    public chainWeight(value: ChainWeightOptions | undefined): this;
    public padding(value: Padding | Length | LocalizedPadding | undefined): this;
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this;
    public margin(value: Padding | Length | LocalizedPadding | undefined): this;
    public backgroundColor(value: ResourceColor | undefined): this;
    public pixelRound(value: PixelRoundPolicy | undefined): this;
    public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this;
    public backgroundImagePosition(value: Position | Alignment | undefined): this;
    public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this;
    public backgroundImageResizable(value: ResizableOptions | undefined): this;
    public foregroundEffect(value: ForegroundEffectOptions | undefined): this;
    public visualEffect(value: VisualEffect | undefined): this;
    public backgroundFilter(value: Filter | undefined): this;
    public foregroundFilter(value: Filter | undefined): this;
    public compositingFilter(value: Filter | undefined): this;
    public opacity(value: number | Resource | undefined): this;
    public border(value: BorderOptions | undefined): this;
    public borderStyle(value: BorderStyle | EdgeStyles | undefined): this;
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this;
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this;
    public borderImage(value: BorderImageOption | undefined): this;
    public outline(value: OutlineOptions | undefined): this;
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this;
    public outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this;
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    public outlineRadius(value: Dimension | OutlineRadiuses | undefined): this;
    public foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this;
    public onClick(event: ((event: ClickEvent) => void) | undefined): this;
    public onHover(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): this;
    public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this;
    public onAccessibilityHover(value: AccessibilityCallback | undefined): this;
    public hoverEffect(value: HoverEffect | undefined): this;
    public onMouse(value: ((event: MouseEvent) => void) | undefined): this;
    public onTouch(value: ((event: TouchEvent) => void) | undefined): this;
    public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this;
    public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this;
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this;
    public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this;
    public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this;
    public focusable(value: boolean | undefined): this;
    public nextFocus(value: FocusMovement | undefined): this;
    public tabStop(value: boolean | undefined): this;
    public onFocus(value: (() => void) | undefined): this;
    public onBlur(value: (() => void) | undefined): this;
    public tabIndex(value: number | undefined): this;
    public defaultFocus(value: boolean | undefined): this;
    public groupDefaultFocus(value: boolean | undefined): this;
    public focusOnTouch(value: boolean | undefined): this;
    public focusBox(value: FocusBoxStyle | undefined): this;
    public animationStart(value: AnimateParam | undefined): this;
    public animationStop(value: AnimateParam | undefined): this;
    public animation(value: AnimateParam | undefined): this;
    public transition(
        effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined,
        onFinish?: TransitionFinishCallback
    ): this;
    public motionBlur(value: MotionBlurOptions | undefined): this;
    public brightness(value: number | undefined): this;
    public contrast(value: number | undefined): this;
    public grayscale(value: number | undefined): this;
    public colorBlend(value: Color | string | Resource | undefined): this;
    public saturate(value: number | undefined): this;
    public sepia(value: number | undefined): this;
    public invert(value: number | InvertOptions | undefined): this;
    public hueRotate(value: number | string | undefined): this;
    public useShadowBatching(value: boolean | undefined): this;
    public useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this;
    public renderGroup(value: boolean | undefined): this;
    public freeze(value: boolean | undefined): this;
    public translate(value: TranslateOptions | undefined): this;
    public scale(value: ScaleOptions | undefined): this;
    public gridSpan(value: number | undefined): this;
    public gridOffset(value: number | undefined): this;
    public rotate(value: RotateOptions | undefined): this;
    public transform(value: TransformationMatrix | undefined | Object | undefined): this;
    public onAppear(value: (() => void) | undefined): this;
    public onDisAppear(value: (() => void) | undefined): this;
    public onAttach(value: (() => void) | undefined): this;
    public onDetach(value: (() => void) | undefined): this;
    public onAreaChange(value: ((oldValue: Area, newValue: Area) => void) | undefined): this;
    public visibility(value: Visibility | undefined): this;
    public flexGrow(value: number | undefined): this;
    public flexShrink(value: number | undefined): this;
    public flexBasis(value: number | string | undefined): this;
    public alignSelf(value: ItemAlign | undefined): this;
    public displayPriority(value: number | undefined): this;
    public zIndex(value: number | undefined): this;
    public direction(value: Direction | undefined): this;
    public align(value: Alignment | undefined): this;
    public position(value: Position | Edges | LocalizedEdges | undefined): this;
    public markAnchor(value: Position | LocalizedPosition | undefined): this;
    public offset(value: Position | Edges | LocalizedEdges | undefined): this;
    public enabled(value: boolean | undefined): this;
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this;
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this;
    public aspectRatio(value: number | undefined): this;
    public clickEffect(value: ClickEffect | undefined): this;
    public onDragStart(
        value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    ): this;
    public onDragEnter(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDragMove(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDragLeave(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public onDrop(
        eventCallback: ((event: DragEvent, extraParams?: string) => void) | undefined | OnDragEventCallback | undefined,
        dropOptions?: DropOptions
    ): this;
    public onDragEnd(value: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    public allowDrop(value: Array<UniformDataType> | Array<string> | undefined): this;
    public draggable(value: boolean | undefined): this;
    public dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this;
    public onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this;
    public linearGradient(value: LinearGradientOptions | undefined): this;
    public sweepGradient(value: SweepGradientOptions | undefined): this;
    public radialGradient(value: RadialGradientOptions | undefined): this;
    public motionPath(value: MotionPathOptions | undefined): this;
    public shadow(value: ShadowOptions | ShadowStyle | undefined): this;
    public clip(value: boolean | undefined): this;
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    public mask(value: ProgressMask | undefined): this;
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    public key(value: string | undefined): this;
    public id(value: string | undefined): this;
    public geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this;
    public stateStyles(value: StateStyles | undefined): this;
    public restoreId(value: number | undefined): this;
    public sphericalEffect(value: number | undefined): this;
    public lightUpEffect(value: number | undefined): this;
    public pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this;
    public accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this;
    public accessibilityText(value: string | undefined | Resource | undefined): this;
    public accessibilityNextFocusId(value: string | undefined): this;
    public accessibilityDefaultFocus(value: boolean | undefined): this;
    public accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this;
    public accessibilityScrollTriggerable(value: boolean | undefined): this;
    public accessibilityRole(value: AccessibilityRoleType | undefined): this;
    public onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this;
    public accessibilityTextHint(value: string | undefined): this;
    public accessibilityDescription(value: string | undefined | Resource | undefined): this;
    public accessibilityLevel(value: string | undefined): this;
    public accessibilityVirtualNode(value: CustomBuilder | undefined): this;
    public accessibilityChecked(value: boolean | undefined): this;
    public accessibilitySelected(value: boolean | undefined): this;
    public obscured(value: Array<ObscuredReasons> | undefined): this;
    public reuseId(value: string | undefined): this;
    public reuse(value: ReuseOptions | undefined): this;
    public renderFit(value: RenderFit | undefined): this;
    public gestureModifier(value: GestureModifier | undefined): this;
    public backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this;
    public onGestureJudgeBegin(
        value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined
    ): this;
    public onGestureRecognizerJudgeBegin(
        callback_: GestureRecognizerJudgeBeginCallback | undefined,
        exposeInnerGesture?: boolean
    ): this;
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this;
    public monopolizeEvents(value: boolean | undefined): this;
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this;
    public onSizeChange(value: SizeChangeCallback | undefined): this;
    public accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this;
    public customProperty(name: string | undefined, value: Object | undefined): this;
    public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this;
    public background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this;
    public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this;
    public backgroundBlurStyle(
        style: BlurStyle | undefined,
        options?: BackgroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    public foregroundBlurStyle(
        style: BlurStyle | undefined,
        options?: ForegroundBlurStyleOptions,
        sysOptions?: SystemAdaptiveOptions
    ): this;
    public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this;
    public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this;
    public gesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this;
    public blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    public linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this;
    public systemBarEffect(): this;
    public backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    public sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this;
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this;
    public dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this;
    public overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this;
    public blendMode(value: BlendMode | undefined, type?: BlendApplyType): this;
    public advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this;
    public bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this;
    public bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this;
    public bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this;
    public bindContextMenu(
        content: CustomBuilder | undefined,
        responseType: ResponseType | undefined,
        options?: ContextMenuOptions | undefined
    ): this;
    public bindContentCover(
        isShow: boolean | undefined,
        builder: CustomBuilder | undefined,
        type?: ModalTransition | ContentCoverOptions
    ): this;
    public bindSheet(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this;
    public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this;
    public onVisibleAreaApproximateChange(
        options: VisibleAreaEventOptions | undefined,
        event: VisibleAreaChangeCallback | undefined
    ): this;
    public keyboardShortcut(
        value: string | FunctionKey | undefined,
        keys: Array<ModifierKey> | undefined,
        action?: () => void
    ): this;
}

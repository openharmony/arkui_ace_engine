/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ComponentBase } from "../../ComponentBase";
import { AccessibilityCallback, AccessibilityOptions, AlignRuleOption, Alignment, AnimateParam, Area, Axis, BackgroundBlurStyleOptions, BackgroundBrightnessOptions, BackgroundEffectOptions, BaseGestureEvent, BlendApplyType, BlendMode, Blender, BlurOptions, BlurStyle, BorderImageOption, BorderOptions, BorderRadiuses, BorderStyle, ChainStyle, ChainWeightOptions, CircleShape, ClickEffect, ClickEvent, Color, ColoringStrategy, CommonAttribute, CommonMethod, ComponentContent, ConstraintSizeOptions, ContentCoverOptions, ContextMenuOptions, CustomBuilder, CustomPopupOptions, Dimension, Direction, DragEvent, DragInteractionOptions, DragItemInfo, DragPreviewOptions, DrawModifier, EdgeColors, EdgeOutlineStyles, EdgeOutlineWidths, EdgeStyles, EdgeWidths, Edges, EffectType, EllipseShape, Filter, FocusBoxStyle, FocusPriority, ForegroundBlurStyleOptions, ForegroundEffectOptions, FunctionKey, GeometryTransitionOptions, GestureInfo, GestureJudgeResult, GestureMask, GestureModifier, GestureRecognizerJudgeBeginCallback, GestureType, HitTestMode, HoverEffect, HoverEvent, ImageRepeat, ImageSize, InvertOptions, ItemAlign, KeyEvent, Length, LinearGradientBlurOptions, Literal_Alignment_align, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, LocalizedAlignRuleOptions, LocalizedBorderRadiuses, LocalizedEdgeColors, LocalizedEdgeWidths, LocalizedEdges, LocalizedPadding, LocalizedPosition, MenuElement, MenuOptions, ModalTransition, ModifierKey, MotionBlurOptions, MotionPathOptions, MouseEvent, ObscuredReasons, OutlineOptions, OutlineRadiuses, OutlineStyle, OverlayOptions, Padding, PathShape, PixelMap, PixelRoundPolicy, PixelStretchEffectOptions, PopupOptions, Position, PreDragStatus, ProgressMask, RectShape, Rectangle, RenderFit, ResizableOptions, ResourceColor, ResourceStr, ResponseType, RotateOptions, SafeAreaEdge, SafeAreaType, ScaleOptions, ShadowOptions, ShadowStyle, SheetOptions, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SizeOptions, StateStyles, TouchEvent, TouchResult, TouchTestInfo, TransitionEffect, TransitionFinishCallback, TransitionOptions, TranslateOptions, Type_CommonMethod_linearGradient_value, Type_CommonMethod_radialGradient_value, Type_CommonMethod_sweepGradient_value, UniformDataType, Visibility, VisibleAreaChangeCallback, VisualEffect, sharedTransitionOptions } from "../../generated";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { AttributeModifier } from "../../generated"; 
import { InteropNativeModule } from "@koalaui/interop"
import { Resource } from "global/resource";
import { LengthMetrics } from "../../Graphics"
/** @memo:stable */
export class ArkBaseNode extends ComponentBase implements CommonAttribute {
   
    constructParam(...param: Object[]): this {
        return this;
    }
   
    getPeer(): ArkCommonMethodPeer {
        return this.peer as ArkCommonMethodPeer;
    }
    /** @memo */
    setCommonOptions(): this {
        return this;
    }
    /** @memo */
    drawModifier(value?: DrawModifier | undefined): this {
        return this;
    }
    /** @memo */
    responseRegion(value: Rectangle | Array<Rectangle>): this {
        return this;
    }
    /** @memo */
    mouseResponseRegion(value: Rectangle | Array<Rectangle>): this {
        return this;
    }
    /** @memo */
    size(value: SizeOptions): this {
        return this;
    }
    /** @memo */
    constraintSize(value: ConstraintSizeOptions): this {
        return this;
    }
    /** @memo */
    touchable(value: boolean): this {
        return this;
    }
    /** @memo */
    hitTestBehavior(value: HitTestMode): this {
        return this;
    }
    /** @memo */
    onChildTouchTest(value: (value: Array<TouchTestInfo>) => TouchResult): this {
        return this;
    }
    /** @memo */
    layoutWeight(value: string | number): this {
        return this;
    }
    /** @memo */
    chainWeight(value: ChainWeightOptions): this {
        return this;
    }
    /** @memo */
    padding(value: Length | Padding | LocalizedPadding): this {
        return this;
    }
    /** @memo */
    safeAreaPadding(value: Padding | LocalizedPadding | LengthMetrics): this {
        return this;
    }
    /** @memo */
    margin(value: Length | Padding | LocalizedPadding): this {
        return this;
    }
    /** @memo */
    pixelRound(value: PixelRoundPolicy): this {
        return this;
    }
    /** @memo */
    backgroundImageSize(value: SizeOptions | ImageSize): this {
        return this;
    }
    /** @memo */
    backgroundImagePosition(value: Position | Alignment): this {
        return this;
    }
    /** @memo */
    backgroundEffect(value: BackgroundEffectOptions): this {
        return this;
    }
    /** @memo */
    backgroundImageResizable(value: ResizableOptions): this {
        return this;
    }
    /** @memo */
    foregroundEffect(value: ForegroundEffectOptions): this {
        return this;
    }
    /** @memo */
    visualEffect(value: VisualEffect): this {
        return this;
    }
    /** @memo */
    backgroundFilter(value: Filter): this {
        return this;
    }
    /** @memo */
    foregroundFilter(value: Filter): this {
        return this;
    }
    /** @memo */
    compositingFilter(value: Filter): this {
        return this;
    }
    /** @memo */
    opacity(value: number | Resource): this {
        return this;
    }
    /** @memo */
    border(value: BorderOptions): this {
        return this;
    }
    /** @memo */
    borderStyle(value: BorderStyle | EdgeStyles): this {
        return this;
    }
    /** @memo */
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this {
        return this;
    }
    /** @memo */
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        return this;
    }
    /** @memo */
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
        return this;
    }
    /** @memo */
    borderImage(value: BorderImageOption): this {
        return this;
    }
    /** @memo */
    outline(value: OutlineOptions): this {

        return this;
    }
    /** @memo */
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
        return this;
    }
    /** @memo */
    outlineWidth(value: Dimension | EdgeOutlineWidths): this {
        return this;
    }
    /** @memo */
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        return this;
    }
    /** @memo */
    outlineRadius(value: Dimension | OutlineRadiuses): this {
        return this;
    }
    /** @memo */
    foregroundColor(value: ResourceColor | ColoringStrategy): this {
        return this;
    }
    /** @memo */
    onClick(event: (event: ClickEvent) => void, distanceThreshold?: number | undefined): this {
        this.getPeer().onClick0Attribute(event);
        return this;
    }
    /** @memo */
    onHover(value: (isHover: boolean, event: HoverEvent) => void): this {
        return this;
    }
    /** @memo */
    onAccessibilityHover(value: AccessibilityCallback): this {
        return this;
    }
    /** @memo */
    hoverEffect(value: HoverEffect): this {
        return this;
    }
    /** @memo */
    onMouse(value: (event: MouseEvent) => void): this {
        return this;
    }
    /** @memo */
    onTouch(value: (event: TouchEvent) => void): this {
        return this;
    }
    /** @memo */
    onKeyEvent(value: (event: KeyEvent) => void): this {
        return this;
    }
    /** @memo */
    onKeyPreIme(value: (parameter: KeyEvent) => boolean): this {
        return this;
    }
    /** @memo */
    focusable(value: boolean): this {
        return this;
    }
    /** @memo */
    onFocus(value: () => void): this {
        return this;
    }
    /** @memo */
    onBlur(value: () => void): this {
        return this;
    }
    /** @memo */
    tabIndex(value: number): this {
        return this;
    }
    /** @memo */
    defaultFocus(value: boolean): this {
        return this;
    }
    /** @memo */
    groupDefaultFocus(value: boolean): this {
        return this;
    }
    /** @memo */
    focusOnTouch(value: boolean): this {
        return this;
    }
    /** @memo */
    focusBox(value: FocusBoxStyle): this {
        return this;
    }
    /** @memo */
    animation(value: AnimateParam): this {
        return this;
    }
    /** @memo */
    transition(effect: TransitionOptions | TransitionEffect, onFinish?: TransitionFinishCallback | undefined): this {
        return this;
    }
    /** @memo */
    motionBlur(value: MotionBlurOptions): this {
        return this;
    }
    /** @memo */
    brightness(value: number): this {
        return this;
    }
    /** @memo */
    contrast(value: number): this {
        return this;
    }
    /** @memo */
    grayscale(value: number): this {
        return this;
    }
    /** @memo */
    colorBlend(value: string | Color | Resource): this {
        return this;
    }
    /** @memo */
    saturate(value: number): this {
        return this;
    }
    /** @memo */
    sepia(value: number): this {
        return this;
    }
    /** @memo */
    invert(value: number | InvertOptions): this {
        return this;
    }
    /** @memo */
    hueRotate(value: string | number): this {
        return this;
    }
    /** @memo */
    useShadowBatching(value: boolean): this {
        return this;
    }
    /** @memo */
    useEffect(useEffect: boolean, effectType?: EffectType | undefined): this {
        return this;
    }
    /** @memo */
    renderGroup(value: boolean): this {
        return this;
    }
    /** @memo */
    freeze(value: boolean): this {
        return this;
    }
    /** @memo */
    translate(value: TranslateOptions): this {
        return this;
    }
    /** @memo */
    scale(value: ScaleOptions): this {
        return this;
    }
    /** @memo */
    gridSpan(value: number): this {
        return this;
    }
    /** @memo */
    gridOffset(value: number): this {
        return this;
    }
    /** @memo */
    rotate(value: RotateOptions): this {
        return this;
    }
    /** @memo */
    transform(value: Object): this {
        return this;
    }
    /** @memo */
    onAppear(value: () => void): this {
        return this;
    }
    /** @memo */
    onDisAppear(value: () => void): this {
        return this;
    }
    /** @memo */
    onAttach(value: () => void): this {
        return this;
    }
    /** @memo */
    onDetach(value: () => void): this {
        return this;
    }
    /** @memo */
    onAreaChange(value: (oldValue: Area, newValue: Area) => void): this {
        return this;
    }
    /** @memo */
    visibility(value: Visibility): this {
        return this;
    }
    /** @memo */
    flexGrow(value: number): this {
        return this;
    }
    /** @memo */
    flexShrink(value: number): this {
        return this;
    }
    /** @memo */
    flexBasis(value: string | number): this {
        return this;
    }
    /** @memo */
    alignSelf(value: ItemAlign): this {
        return this;
    }
    /** @memo */
    displayPriority(value: number): this {
        return this;
    }
    /** @memo */
    zIndex(value: number): this {
        this.getPeer().zIndexAttribute(value);
        return this;
    }
    /** @memo */
    direction(value: Direction): this {
        return this;
    }
    /** @memo */
    align(value: Alignment): this {
        return this;
    }
    /** @memo */
    position(value: Position | Edges | LocalizedEdges): this {
        return this;
    }
    /** @memo */
    markAnchor(value: Position | LocalizedPosition): this {
        return this;
    }
    /** @memo */
    offset(value: Position | Edges | LocalizedEdges): this {
        return this;
    }
    /** @memo */
    enabled(value: boolean): this {
        return this;
    }
    /** @memo */
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this {
        return this;
    }
    /** @memo */
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this {
        return this;
    }
    /** @memo */
    aspectRatio(value: number): this {
        return this;
    }
    /** @memo */
    clickEffect(value?: ClickEffect | undefined): this {
        return this;
    }
    /** @memo */
    onDragStart(value: (event: DragEvent, extraParams?: string | undefined) => CustomBuilder | DragItemInfo): this {
        return this;
    }
    /** @memo */
    onDragEnter(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
    /** @memo */
    onDragMove(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
    /** @memo */
    onDragLeave(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
    /** @memo */
    onDrop(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
    /** @memo */
    onDragEnd(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
    /** @memo */
    allowDrop(value?: Array<UniformDataType> | undefined): this {
        return this;
    }
    /** @memo */
    draggable(value: boolean): this {
        return this;
    }
    /** @memo */
    dragPreview(value: string | CustomBuilder | DragItemInfo): this {
        return this;
    }
    /** @memo */
    onPreDrag(value: (parameter: PreDragStatus) => void): this {
        return this;
    }
    /** @memo */
    linearGradient(value: Type_CommonMethod_linearGradient_value): this {
        return this;
    }
    /** @memo */
    sweepGradient(value: Type_CommonMethod_sweepGradient_value): this {
        return this;
    }
    /** @memo */
    radialGradient(value: Type_CommonMethod_radialGradient_value): this {
        return this;
    }
    /** @memo */
    motionPath(value: MotionPathOptions): this {
        return this;
    }
    /** @memo */
    shadow(value: ShadowOptions | ShadowStyle): this {
        return this;
    }
    /** @memo */
    clip(value?: boolean | undefined): this {
        return this;
    }
    /** @memo */
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        return this;
    }
    /** @memo */
    mask(value?: ProgressMask | undefined): this {
        return this;
    }
    /** @memo */
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        return this;
    }
    /** @memo */
    key(value: string): this {
        return this;
    }
    /** @memo */
    id(value: string): this {
        return this;
    }
    /** @memo */
    geometryTransition(id: string, options?: GeometryTransitionOptions | undefined): this {
        return this;
    }
    /** @memo */
    stateStyles(value: StateStyles): this {
        return this;
    }
    /** @memo */
    restoreId(value: number): this {
        return this;
    }
    /** @memo */
    sphericalEffect(value: number): this {
        return this;
    }
    /** @memo */
    lightUpEffect(value: number): this {
        return this;
    }
    /** @memo */
    pixelStretchEffect(value: PixelStretchEffectOptions): this {
        return this;
    }
    /** @memo */
    accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions | undefined): this {
        return this;
    }
    /** @memo */
    accessibilityText(value: string | Resource): this {
        return this;
    }
    /** @memo */
    accessibilityTextHint(value: string): this {
        return this;
    }
    /** @memo */
    accessibilityDescription(value: string | Resource): this {
        return this;
    }
    /** @memo */
    accessibilityLevel(value: string): this {
        return this;
    }
    /** @memo */
    accessibilityVirtualNode(value: CustomBuilder): this {
        return this;
    }
    /** @memo */
    accessibilityChecked(value: boolean): this {
        return this;
    }
    /** @memo */
    accessibilitySelected(value: boolean): this {
        return this;
    }
    /** @memo */
    obscured(value: Array<ObscuredReasons>): this {
        return this;
    }
    /** @memo */
    reuseId(value: string): this {
        return this;
    }
    /** @memo */
    renderFit(value: RenderFit): this {
        return this;
    }
    /** @memo */
    gestureModifier(value: GestureModifier): this {
        return this;
    }
    /** @memo */
    backgroundBrightness(value: BackgroundBrightnessOptions): this {
        return this;
    }
    /** @memo */
    onGestureJudgeBegin(value: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        return this;
    }
    /** @memo */
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean | undefined): this {
        return this;
    }
    /** @memo */
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this {
        return this;
    }
    /** @memo */
    monopolizeEvents(value: boolean): this {
        return this;
    }
    /** @memo */
    onTouchIntercept(value: (parameter: TouchEvent) => HitTestMode): this {
        return this;
    }
    /** @memo */
    onSizeChange(value: SizeChangeCallback): this {
        return this;
    }
    /** @memo */
    customProperty(name: string, value?: Object | undefined): this {
        return this;
    }
    /** @memo */
    expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
        return this;
    }
    /** @memo */
    background(builder: CustomBuilder, options?: Literal_Alignment_align | undefined): this {
        return this;
    }
    /** @memo */
    backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat | undefined): this {
        return this;
    }
    /** @memo */
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions | undefined): this {
        return this;
    }
    /** @memo */
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions | undefined): this {
        return this;
    }
    /** @memo */
    focusScopeId(id: string, isGroup?: boolean | undefined, arrowStepOut?: boolean | undefined): this {
        return this;
    }
    /** @memo */
    focusScopePriority(scopeId: string, priority?: FocusPriority | undefined): this {
        return this;
    }
    /** @memo */
    gesture(gesture: GestureType, mask?: GestureMask | undefined): this {
        return this;
    }
    /** @memo */
    priorityGesture(gesture: GestureType, mask?: GestureMask | undefined): this {
        return this;
    }
    /** @memo */
    parallelGesture(gesture: GestureType, mask?: GestureMask | undefined): this {
        return this;
    }
    /** @memo */
    blur(value: number, options?: BlurOptions | undefined): this {
        return this;
    }
    /** @memo */
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
        return this;
    }
    /** @memo */
    systemBarEffect(): this {
        return this;
    }
    /** @memo */
    backdropBlur(value: number, options?: BlurOptions | undefined): this {
        return this;
    }
    /** @memo */
    sharedTransition(id: string, options?: sharedTransitionOptions | undefined): this {
        return this;
    }
    /** @memo */
    chainMode(direction: Axis, style: ChainStyle): this {
        return this;
    }
    /** @memo */
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions | undefined): this {
        return this;
    }
    /** @memo */
    overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions | undefined): this {
        return this;
    }
    /** @memo */
    blendMode(value: BlendMode, type?: BlendApplyType | undefined): this {
        return this;
    }
    /** @memo */
    advancedBlendMode(effect: BlendMode | Blender, type?: BlendApplyType | undefined): this {
        return this;
    }
    /** @memo */
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        return this;
    }
    /** @memo */
    bindMenu(content: CustomBuilder | Array<MenuElement>, options?: MenuOptions | undefined): this {
        return this;
    }
    /** @memo */
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions | undefined): this {
        return this;
    }
    /** @memo */
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions | undefined): this {
        return this;
    }
    /** @memo */
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions | undefined): this {
        return this;
    }
    /** @memo */
    onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this {
        return this;
    }
    /** @memo */
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void) | undefined): this {
        return this;
    }
    /** @memo */
    width(value: Length | undefined): this {
        if (value != null) {
            this.getPeer().widthAttribute(value as Length);
        }
        return this;
    }
    /** @memo */
    height(value: Length | undefined): this {
        if (value != null) {
            this.getPeer().heightAttribute(value as Length);
        }
        return this;
    }
    /** @memo */
    backgroundColor(value: ResourceColor | undefined): this {
        if (value != null) {
            this.getPeer().backgroundColorAttribute( value as ResourceColor );
        }
        return this;
    }
    /** @memo */
    attributeModifier<CommonAttribute>(modifier:AttributeModifier<CommonAttribute>): this {
        return this;
    }
}
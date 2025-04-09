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

import { VoidCallback, VP, Length, ResourceColor, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ICurve } from "./common"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, EdgeEffect, Curve } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { IndicatorComponentController } from "./indicatorcomponent"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ArkSwiperComponent } from "./../generated/ArkSwiper"
import { ArkSwiperPeer } from "./../generated/peers/ArkSwiperPeer"
import { Font } from "./units"

export class Indicator<T> {
    _left?: Length | undefined;
    _top?: Length | undefined;
    _right?: Length | undefined;
    _bottom?: Length | undefined;
    _start?: LengthMetrics | undefined;
    _end?: LengthMetrics | undefined;
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator();
    }
    static digit(): DigitIndicator {
        return new DigitIndicator();
    }
    left(value: Length): this {
        this._left = value;
        return this;
    }
    top(value: Length): this {
        this._top = value;
        return this;
    }
    right(value: Length): this {
        this._right = value;
        return this;
    }
    bottom(value: Length): this {
        this._bottom = value;
        return this;
    }
    start(value: LengthMetrics): this {
        this._start = value;
        return this;
    }
    end(value: LengthMetrics): this {
        this._end = value;
        return this;
    }
}

export class DigitIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _fontColor?: ResourceColor | undefined
    _selectedFontColor?: ResourceColor | undefined
    _digitFont?: Font | undefined
    _selectedDigitFont?: Font | undefined
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
    fontColor(value: ResourceColor): this {
        this._fontColor = value
        return this
    }
    selectedFontColor(value: ResourceColor): this {
        this._selectedFontColor = value
        return this
    }
    digitFont(value: Font): this {
        this._digitFont = value
        return this
    }
    selectedDigitFont(value: Font): this {
        this._selectedDigitFont = value
        return this
    }
}

export class DotIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _itemWidth?: Length | undefined
    _itemHeight?: Length | undefined
    _selectedItemWidth?: Length | undefined
    _selectedItemHeight?: Length | undefined
    _mask?: boolean | undefined
    _color?: ResourceColor | undefined
    _selectedColor?: ResourceColor | undefined
    _maxDisplayCount?: number | undefined
    constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
    itemWidth(value: Length): this {
        this._itemWidth = value
        return this
    }
    itemHeight(value: Length): this {
        this._itemHeight = value
        return this
    }
    selectedItemWidth(value: Length): this {
        this._selectedItemWidth = value
        return this
    }
    selectedItemHeight(value: Length): this {
        this._selectedItemHeight = value
        return this
    }
    mask(value: boolean): this {
        this._mask = value
        return this
    }
    color(value: ResourceColor): this {
        this._color = value
        return this
    }
    selectedColor(value: ResourceColor): this {
        this._selectedColor = value
        return this
    }
    maxDisplayCount(maxDisplayCount: number): this {
        this._maxDisplayCount = maxDisplayCount
        return this
    }
}

export class SwiperControllerInternal {
    public static fromPtr(ptr: KPointer): SwiperController {
        const obj : SwiperController = new SwiperController()
        obj.peer = new Finalizable(ptr, SwiperController.getFinalizer())
        return obj
    }
}
export class SwiperController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_swipercontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwiperController.ctor_swipercontroller()
        this.peer = new Finalizable(ctorPtr, SwiperController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperController_getFinalizer()
    }
    public showNext(): undefined {
        return this.showNext_serialize()
    }
    public showPrevious(): undefined {
        return this.showPrevious_serialize()
    }
    public changeIndex(index: number, useAnimation?: boolean): undefined {
        const index_casted = index as (number)
        const useAnimation_casted = useAnimation as (boolean | undefined)
        return this.changeIndex_serialize(index_casted, useAnimation_casted)
    }
    public finishAnimation(callback_?: VoidCallback): undefined {
        const callback__casted = callback_ as (VoidCallback | undefined)
        return this.finishAnimation_serialize(callback__casted)
    }
    private showNext_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_showNext(this.peer!.ptr)
        return retval
    }
    private showPrevious_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._SwiperController_showPrevious(this.peer!.ptr)
        return retval
    }
    private changeIndex_serialize(index: number, useAnimation?: boolean): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let useAnimation_type : int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type as int32)
        if ((RuntimeType.UNDEFINED) != (useAnimation_type)) {
            const useAnimation_value  = useAnimation!
            thisSerializer.writeBoolean(useAnimation_value)
        }
        const retval  = ArkUIGeneratedNativeModule._SwiperController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private finishAnimation_serialize(callback_?: VoidCallback): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        const retval  = ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export interface SwiperContentTransitionProxy {
    selectedIndex: number
    index: number
    position: number
    mainAxisLength: number
    finishTransition(): void
}
export class SwiperContentTransitionProxyInternal implements MaterializedBase,SwiperContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get selectedIndex(): number {
        return this.getSelectedIndex()
    }
    set selectedIndex(selectedIndex: number) {
        this.setSelectedIndex(selectedIndex)
    }
    get index(): number {
        return this.getIndex()
    }
    set index(index: number) {
        this.setIndex(index)
    }
    get position(): number {
        return this.getPosition()
    }
    set position(position: number) {
        this.setPosition(position)
    }
    get mainAxisLength(): number {
        return this.getMainAxisLength()
    }
    set mainAxisLength(mainAxisLength: number) {
        this.setMainAxisLength(mainAxisLength)
    }
    static ctor_swipercontenttransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwiperContentTransitionProxyInternal.ctor_swipercontenttransitionproxy()
        this.peer = new Finalizable(ctorPtr, SwiperContentTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getSelectedIndex(): number {
        return this.getSelectedIndex_serialize()
    }
    private setSelectedIndex(selectedIndex: number): void {
        const selectedIndex_casted = selectedIndex as (number)
        this.setSelectedIndex_serialize(selectedIndex_casted)
        return
    }
    private getIndex(): number {
        return this.getIndex_serialize()
    }
    private setIndex(index: number): void {
        const index_casted = index as (number)
        this.setIndex_serialize(index_casted)
        return
    }
    private getPosition(): number {
        return this.getPosition_serialize()
    }
    private setPosition(position: number): void {
        const position_casted = position as (number)
        this.setPosition_serialize(position_casted)
        return
    }
    private getMainAxisLength(): number {
        return this.getMainAxisLength_serialize()
    }
    private setMainAxisLength(mainAxisLength: number): void {
        const mainAxisLength_casted = mainAxisLength as (number)
        this.setMainAxisLength_serialize(mainAxisLength_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getSelectedIndex_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getSelectedIndex(this.peer!.ptr)
        return retval
    }
    private setSelectedIndex_serialize(selectedIndex: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setSelectedIndex(this.peer!.ptr, selectedIndex)
    }
    private getIndex_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getIndex(this.peer!.ptr)
        return retval
    }
    private setIndex_serialize(index: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setIndex(this.peer!.ptr, index)
    }
    private getPosition_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getPosition(this.peer!.ptr)
        return retval
    }
    private setPosition_serialize(position: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setPosition(this.peer!.ptr, position)
    }
    private getMainAxisLength_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_getMainAxisLength(this.peer!.ptr)
        return retval
    }
    private setMainAxisLength_serialize(mainAxisLength: number): void {
        ArkUIGeneratedNativeModule._SwiperContentTransitionProxy_setMainAxisLength(this.peer!.ptr, mainAxisLength)
    }
    public static fromPtr(ptr: KPointer): SwiperContentTransitionProxyInternal {
        const obj : SwiperContentTransitionProxyInternal = new SwiperContentTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, SwiperContentTransitionProxyInternal.getFinalizer())
        return obj
    }
}
export interface SwiperAutoFill {
    minSize: VP;
}
export interface ArrowStyle {
    showBackground?: boolean;
    isSidebarMiddle?: boolean;
    backgroundSize?: Length;
    backgroundColor?: ResourceColor;
    arrowSize?: Length;
    arrowColor?: ResourceColor;
}
export enum SwiperDisplayMode {
    LEGACY_STRETCH = 0,
    Stretch = 0,
    LEGACY_AUTO_LINEAR = 1,
    AutoLinear = 1,
    STRETCH = 2,
    AUTO_LINEAR = 3
}
export interface IndicatorStyle {
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
}
export interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1
}
export type OnSwiperAnimationStartCallback = (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperAnimationEndCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperGestureSwipeCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export type Callback_SwiperContentTransitionProxy_Void = (parameter: SwiperContentTransitionProxy) => void;
export interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: SwiperContentTransitionProxy) => void);
}
export type ContentDidScrollCallback = (selectedIndex: number, index: number, position: number, mainAxisLength: number) => void;
/** @memo:stable */
export interface SwiperAttribute extends CommonMethod {
    /** @memo */
    setSwiperOptions(controller?: SwiperController): this
    /** @memo */
    index(value: number): this
    /** @memo */
    autoPlay(value: boolean): this
    /** @memo */
    interval(value: number): this
    /** @memo */
    indicator(value: DotIndicator | DigitIndicator | boolean | IndicatorComponentController): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    duration(value: number): this
    /** @memo */
    vertical(value: boolean): this
    /** @memo */
    itemSpace(value: number | string): this
    /** @memo */
    displayMode(value: SwiperDisplayMode): this
    /** @memo */
    cachedCount(value: number): this
    /** @memo */
    effectMode(value: EdgeEffect): this
    /** @memo */
    disableSwipe(value: boolean): this
    /** @memo */
    curve(value: Curve | string | ICurve): this
    /** @memo */
    onChange(value: ((index: number) => void)): this
    /** @memo */
    indicatorStyle(value?: IndicatorStyle): this
    /** @memo */
    onAnimationStart(value: OnSwiperAnimationStartCallback): this
    /** @memo */
    onAnimationEnd(value: OnSwiperAnimationEndCallback): this
    /** @memo */
    onGestureSwipe(value: OnSwiperGestureSwipeCallback): this
    /** @memo */
    nestedScroll(value: SwiperNestedScrollMode): this
    /** @memo */
    customContentTransition(value: SwiperContentAnimatedTransition): this
    /** @memo */
    onContentDidScroll(value: ContentDidScrollCallback): this
    /** @memo */
    indicatorInteractive(value: boolean): this
    /** @memo */
    displayArrow(value: ArrowStyle | boolean, isHoverShow?: boolean): this
    /** @memo */
    displayCount(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): this
    /** @memo */
    prevMargin(value: Length, ignoreBlank?: boolean): this
    /** @memo */
    nextMargin(value: Length, ignoreBlank?: boolean): this
    /** @memo */
    _onChangeEvent_index(callback: ((index: number) => void)): void
}
/** @memo */
export function Swiper(
  /** @memo */
  style: ((attributes: SwiperAttribute) => void) | undefined,
  controller?: SwiperController | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkSwiperComponent()
    })
    NodeAttach<ArkSwiperPeer>((): ArkSwiperPeer => ArkSwiperPeer.create(receiver), (_: ArkSwiperPeer) => {
        receiver.setSwiperOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

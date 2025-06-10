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

import { TranslateOptions, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Length, ResourceColor, Dimension, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, EdgeEffect } from "./enums"
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
import { Callback_Number_Void } from "./alphabetIndexer"
import { ArkTabsComponent } from "./../generated/ArkTabs"
import { ArkTabsPeer } from "./../generated/peers/ArkTabsPeer"
export class TabsControllerInternal {
    public static fromPtr(ptr: KPointer): TabsController {
        const obj : TabsController = new TabsController()
        obj.peer = new Finalizable(ptr, TabsController.getFinalizer())
        return obj
    }
}
export class TabsController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_tabscontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabsController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabsController.ctor_tabscontroller()
        this.peer = new Finalizable(ctorPtr, TabsController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabsController_getFinalizer()
    }
    public changeIndex(value: number): void {
        const value_casted = value as (number)
        this.changeIndex_serialize(value_casted)
        return
    }
    public preloadItems(indices?: Array<number>): Promise<void> {
        const indices_casted = indices as (Array<number> | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    public setTabBarTranslate(translate: TranslateOptions): void {
        const translate_casted = translate as (TranslateOptions)
        this.setTabBarTranslate_serialize(translate_casted)
        return
    }
    public setTabBarOpacity(opacity: number): void {
        const opacity_casted = opacity as (number)
        this.setTabBarOpacity_serialize(opacity_casted)
        return
    }
    private changeIndex_serialize(value: number): void {
        ArkUIGeneratedNativeModule._TabsController_changeIndex(this.peer!.ptr, value)
    }
    private preloadItems_serialize(indices?: Array<number>): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8(indices_type as int32)
        if ((RuntimeType.UNDEFINED) != (indices_type)) {
            const indices_value  = indices!
            thisSerializer.writeInt32(indices_value.length as int32)
            for (let i = 0; i < indices_value.length; i++) {
                const indices_value_element : number = indices_value[i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._TabsController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setTabBarTranslate_serialize(translate: TranslateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(translate)
        ArkUIGeneratedNativeModule._TabsController_setTabBarTranslate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setTabBarOpacity_serialize(opacity: number): void {
        ArkUIGeneratedNativeModule._TabsController_setTabBarOpacity(this.peer!.ptr, opacity)
    }
}
export interface TabContentTransitionProxy {
    from: number
    to: number
    finishTransition(): void
}
export class TabContentTransitionProxyInternal implements MaterializedBase,TabContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): number {
        return this.getFrom()
    }
    set from(from: number) {
        this.setFrom(from)
    }
    get to(): number {
        return this.getTo()
    }
    set to(to: number) {
        this.setTo(to)
    }
    static ctor_tabcontenttransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabContentTransitionProxyInternal.ctor_tabcontenttransitionproxy()
        this.peer = new Finalizable(ctorPtr, TabContentTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getFrom(): number {
        return this.getFrom_serialize()
    }
    private setFrom(from: number): void {
        const from_casted = from as (number)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): number {
        return this.getTo_serialize()
    }
    private setTo(to: number): void {
        const to_casted = to as (number)
        this.setTo_serialize(to_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getFrom_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFrom(this.peer!.ptr)
        return retval
    }
    private setFrom_serialize(from: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setFrom(this.peer!.ptr, from)
    }
    private getTo_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getTo(this.peer!.ptr)
        return retval
    }
    private setTo_serialize(to: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setTo(this.peer!.ptr, to)
    }
    public static fromPtr(ptr: KPointer): TabContentTransitionProxyInternal {
        const obj : TabContentTransitionProxyInternal = new TabContentTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, TabContentTransitionProxyInternal.getFinalizer())
        return obj
    }
}
export enum BarMode {
    SCROLLABLE = 0,
    Scrollable = 0,
    FIXED = 1,
    Fixed = 1
}
export enum AnimationMode {
    CONTENT_FIRST = 0,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2
}
export enum BarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum LayoutStyle {
    ALWAYS_CENTER = 0,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2
}
export interface TabsOptions {
    barPosition?: BarPosition;
    index?: number;
    controller?: TabsController;
}
export interface DividerStyle {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export interface TabsAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export interface BarGridColumnOptions {
    sm?: number;
    md?: number;
    lg?: number;
    margin?: Dimension;
    gutter?: Dimension;
}
export interface ScrollableBarModeOptions {
    margin?: Dimension;
    nonScrollableLayoutStyle?: LayoutStyle;
}
export type OnTabsAnimationStartCallback = (index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => void;
export type OnTabsAnimationEndCallback = (index: number, extraInfo: TabsAnimationEvent) => void;
export type OnTabsGestureSwipeCallback = (index: number, extraInfo: TabsAnimationEvent) => void;
export type TabsCustomContentTransitionCallback = (from: number, to: number) => TabContentAnimatedTransition | undefined;
export type OnTabsContentWillChangeCallback = (currentIndex: number, comingIndex: number) => boolean;
export type Callback_TabContentTransitionProxy_Void = (parameter: TabContentTransitionProxy) => void;
export interface TabContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: TabContentTransitionProxy) => void);
}
/** @memo:stable */
export interface TabsAttribute extends CommonMethod {
    /** @memo */
    setTabsOptions(options?: TabsOptions): this
    /** @memo */
    vertical(value: boolean): this
    /** @memo */
    barPosition(value: BarPosition): this
    /** @memo */
    scrollable(value: boolean): this
    /** @memo */
    barMode(value: BarMode, options?: ScrollableBarModeOptions): this
    /** @memo */
    barWidth(value: Length): this
    /** @memo */
    barHeight(value: Length): this
    /** @memo */
    animationDuration(value: number): this
    /** @memo */
    animationMode(value?: AnimationMode): this
    /** @memo */
    edgeEffect(value?: EdgeEffect): this
    /** @memo */
    onChange(value: ((index: number) => void)): this
    /** @memo */
    onTabBarClick(value: ((index: number) => void)): this
    /** @memo */
    onAnimationStart(value: OnTabsAnimationStartCallback): this
    /** @memo */
    onAnimationEnd(value: OnTabsAnimationEndCallback): this
    /** @memo */
    onGestureSwipe(value: OnTabsGestureSwipeCallback): this
    /** @memo */
    fadingEdge(value: boolean): this
    /** @memo */
    divider(value?: DividerStyle): this
    /** @memo */
    barOverlap(value: boolean): this
    /** @memo */
    barBackgroundColor(value: ResourceColor): this
    /** @memo */
    barGridAlign(value: BarGridColumnOptions): this
    /** @memo */
    customContentTransition(value: TabsCustomContentTransitionCallback): this
    /** @memo */
    barBackgroundBlurStyle(style: BlurStyle, options?: BackgroundBlurStyleOptions): this
    /** @memo */
    barBackgroundEffect(value: BackgroundEffectOptions): this
    /** @memo */
    onContentWillChange(value: OnTabsContentWillChangeCallback): this
    /** @memo */
    barModeScrollable(options: ScrollableBarModeOptions): this
    /** @memo */
    _onChangeEvent_index(callback: ((index: number) => void)): void
}
/** @memo */
export function Tabs(
  /** @memo */
  style: ((attributes: TabsAttribute) => void) | undefined,
  options?: TabsOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTabsComponent()
    })
    NodeAttach<ArkTabsPeer>((): ArkTabsPeer => ArkTabsPeer.create(receiver), (_: ArkTabsPeer) => {
        receiver.setTabsOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ICurve } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, EdgeEffect, Curve } from "./../../component/enums"
import { LengthMetrics } from "../../Graphics"
import { ResizableOptions } from "./../../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { AttributeModifier } from "./../../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface } from "./../../component/gesture"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { DotIndicator, DigitIndicator, SwiperDisplayMode, IndicatorStyle, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ArrowStyle, SwiperAttribute, SwiperAutoFill, SwiperController } from "./../../component/swiper"
import { IndicatorComponentController } from "./../../component/indicatorcomponent"
import { Callback_Number_Void } from "./../../component/alphabetIndexer"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkSwiperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSwiperPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Swiper_construct(peerId, flags)
        const _peer  = new ArkSwiperPeer(_peerPtr, peerId, "Swiper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSwiperOptionsAttribute(controller?: SwiperController): void {
        const thisSerializer : Serializer = Serializer.hold()
        let controller_type : int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value  = controller!
            thisSerializer.writeSwiperController(controller_value)
        }
        ArkUIGeneratedNativeModule._SwiperInterface_setSwiperOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_index(this.peer.ptr, value)
    }
    autoPlayAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_autoPlay(this.peer.ptr, value ? 1 : 0)
    }
    intervalAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_interval(this.peer.ptr, value)
    }
    indicator0Attribute(value: DotIndicator | DigitIndicator | boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDotIndicator(value))) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as DotIndicator
            thisSerializer.writeDotIndicator(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isDigitIndicator(value))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as DigitIndicator
            thisSerializer.writeDigitIndicator(value_1)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as boolean
            thisSerializer.writeBoolean(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicator1Attribute(value: IndicatorComponentController): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator1(this.peer.ptr, toPeerPtr(value))
    }
    loopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_loop(this.peer.ptr, value ? 1 : 0)
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_duration(this.peer.ptr, value)
    }
    verticalAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_vertical(this.peer.ptr, value ? 1 : 0)
    }
    itemSpaceAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_itemSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayModeAttribute(value: SwiperDisplayMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_displayMode(this.peer.ptr, value.valueOf())
    }
    cachedCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_cachedCount(this.peer.ptr, value)
    }
    effectModeAttribute(value: EdgeEffect): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_effectMode(this.peer.ptr, value.valueOf())
    }
    disableSwipeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_disableSwipe(this.peer.ptr, value ? 1 : 0)
    }
    curveAttribute(value: Curve | string | ICurve): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isCurve(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Curve
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as ICurve
            thisSerializer.writeICurve(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_curve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorStyleAttribute(value?: IndicatorStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeIndicatorStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnSwiperAnimationStartCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnSwiperAnimationEndCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: SwiperNestedScrollMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_nestedScroll(this.peer.ptr, value.valueOf())
    }
    customContentTransitionAttribute(value: SwiperContentAnimatedTransition): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSwiperContentAnimatedTransition(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentDidScrollAttribute(value: ContentDidScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorInteractiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorInteractive(this.peer.ptr, value ? 1 : 0)
    }
    displayArrowAttribute(value: ArrowStyle | boolean, isHoverShow?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ArrowStyle
            thisSerializer.writeArrowStyle(value_0)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as boolean
            thisSerializer.writeBoolean(value_1)
        }
        let isHoverShow_type : int32 = RuntimeType.UNDEFINED
        isHoverShow_type = runtimeType(isHoverShow)
        thisSerializer.writeInt8(isHoverShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isHoverShow_type)) {
            const isHoverShow_value  = isHoverShow!
            thisSerializer.writeBoolean(isHoverShow_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayArrow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayCountAttribute(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as SwiperAutoFill
            thisSerializer.writeSwiperAutoFill(value_2)
        }
        let swipeByGroup_type : int32 = RuntimeType.UNDEFINED
        swipeByGroup_type = runtimeType(swipeByGroup)
        thisSerializer.writeInt8(swipeByGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (swipeByGroup_type)) {
            const swipeByGroup_value  = swipeByGroup!
            thisSerializer.writeBoolean(swipeByGroup_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    prevMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type as int32)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_prevMargin(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nextMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let ignoreBlank_type : int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type as int32)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value  = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_nextMargin(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SwiperAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkSwiperAttributes extends ArkCommonMethodAttributes {
    index?: number
    autoPlay?: boolean
    interval?: number
    indicator?: DotIndicator | DigitIndicator | boolean
    loop?: boolean
    duration?: number
    vertical?: boolean
    itemSpace?: number | string
    displayMode?: SwiperDisplayMode
    cachedCount?: number
    effectMode?: EdgeEffect
    disableSwipe?: boolean
    curve?: Curve | string | ICurve
    onChange?: ((index: number) => void)
    indicatorStyle?: IndicatorStyle
    onAnimationStart?: OnSwiperAnimationStartCallback
    onAnimationEnd?: OnSwiperAnimationEndCallback
    onGestureSwipe?: OnSwiperGestureSwipeCallback
    nestedScroll?: SwiperNestedScrollMode
    customContentTransition?: SwiperContentAnimatedTransition
    onContentDidScroll?: ContentDidScrollCallback
    indicatorInteractive?: boolean
}

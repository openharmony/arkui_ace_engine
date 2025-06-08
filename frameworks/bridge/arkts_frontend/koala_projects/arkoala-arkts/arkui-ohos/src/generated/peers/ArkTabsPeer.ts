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
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, EdgeEffect } from "./../../component/enums"
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
import { BarPosition, BarMode, AnimationMode, OnTabsAnimationStartCallback, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, DividerStyle, BarGridColumnOptions, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, ScrollableBarModeOptions, TabsAttribute, TabsOptions } from "./../../component/tabs"
import { Callback_Number_Void } from "./../../component/alphabetIndexer"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkTabsPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTabsPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Tabs_construct(peerId, flags)
        const _peer  = new ArkTabsPeer(_peerPtr, peerId, "Tabs", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabsOptionsAttribute(options?: TabsOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTabsOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsInterface_setTabsOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TabsAttribute_vertical(this.peer.ptr, value ? 1 : 0)
    }
    barPositionAttribute(value: BarPosition): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barPosition(this.peer.ptr, value.valueOf())
    }
    scrollableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TabsAttribute_scrollable(this.peer.ptr, value ? 1 : 0)
    }
    barMode0Attribute(value: BarMode): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barMode0(this.peer.ptr, value.valueOf())
    }
    barMode1Attribute(value: BarMode, options?: ScrollableBarModeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollableBarModeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barMode1(this.peer.ptr, value.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barWidthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barWidth(this.peer.ptr, value)
    }
    barHeightAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barHeight(this.peer.ptr, value)
    }
    animationDurationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TabsAttribute_animationDuration(this.peer.ptr, value)
    }
    animationModeAttribute(value?: AnimationMode): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AnimationMode)
            thisSerializer.writeInt32(value_value.valueOf())
        }
        ArkUIGeneratedNativeModule._TabsAttribute_animationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value?: EdgeEffect): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(value_value.valueOf())
        }
        ArkUIGeneratedNativeModule._TabsAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTabBarClickAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onTabBarClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnTabsAnimationStartCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnTabsAnimationEndCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnTabsGestureSwipeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fadingEdgeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TabsAttribute_fadingEdge(this.peer.ptr, value ? 1 : 0)
    }
    dividerAttribute(value?: DividerStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barOverlapAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barOverlap(this.peer.ptr, value ? 1 : 0)
    }
    barBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barGridAlignAttribute(value: BarGridColumnOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBarGridColumnOptions(value)
        ArkUIGeneratedNativeModule._TabsAttribute_barGridAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customContentTransitionAttribute(value: TabsCustomContentTransitionCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundBlurStyle0Attribute(value: BlurStyle): void {
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle0(this.peer.ptr, value.valueOf())
    }
    barBackgroundBlurStyle1Attribute(style: BlurStyle, options: BackgroundBlurStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBackgroundBlurStyleOptions(options)
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle1(this.peer.ptr, style.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundEffectAttribute(value: BackgroundEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBackgroundEffectOptions(value)
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentWillChangeAttribute(value: OnTabsContentWillChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TabsAttribute_onContentWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barModeScrollableAttribute(options: ScrollableBarModeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollableBarModeOptions(options)
        ArkUIGeneratedNativeModule._TabsAttribute_barModeScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TabsAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkTabsAttributes extends ArkCommonMethodAttributes {
    vertical?: boolean
    barPosition?: BarPosition
    scrollable?: boolean
    barMode?: BarMode
    barWidth?: Length
    barHeight?: Length
    animationDuration?: number
    animationMode?: AnimationMode | undefined
    edgeEffect?: EdgeEffect | undefined
    onChange?: ((index: number) => void)
    onTabBarClick?: ((index: number) => void)
    onAnimationStart?: OnTabsAnimationStartCallback
    onAnimationEnd?: OnTabsAnimationEndCallback
    onGestureSwipe?: OnTabsGestureSwipeCallback
    fadingEdge?: boolean
    divider?: DividerStyle | undefined
    barOverlap?: boolean
    barBackgroundColor?: ResourceColor
    barGridAlign?: BarGridColumnOptions
    customContentTransition?: TabsCustomContentTransitionCallback
    barBackgroundBlurStyle?: BlurStyle
    barBackgroundEffect?: BackgroundEffectOptions
    onContentWillChange?: OnTabsContentWillChangeCallback
}

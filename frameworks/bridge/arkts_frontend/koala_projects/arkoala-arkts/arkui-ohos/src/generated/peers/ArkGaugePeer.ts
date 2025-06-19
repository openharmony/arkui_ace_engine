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
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../../component/enums"
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
import { LinearGradient } from "./../../component/dataPanel"
import { Tuple_Union_ResourceColor_LinearGradient_Number, GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration, GaugeOptions, GaugeAttribute } from "./../../component/gauge"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkGaugePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGaugePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Gauge_construct(peerId, flags)
        const _peer  = new ArkGaugePeer(_peerPtr, peerId, "Gauge", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGaugeOptionsAttribute(options: GaugeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeOptions(options)
        ArkUIGeneratedNativeModule._GaugeInterface_setGaugeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_value(this.peer.ptr, value)
    }
    startAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_startAngle(this.peer.ptr, value)
    }
    endAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_endAngle(this.peer.ptr, value)
    }
    colorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((TypeChecker.isColor(value)) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceColor
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (TypeChecker.isColor(value_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as Color
                thisSerializer.writeInt32(value_0_0.valueOf())
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as string
                thisSerializer.writeString(value_0_2)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_0_3  = value_0 as Resource
                thisSerializer.writeResource(value_0_3)
            }
        }
        else if (TypeChecker.isLinearGradient(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as LinearGradient
            thisSerializer.writeLinearGradient(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value))) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Array<[ ResourceColor | LinearGradient, number ]>
            thisSerializer.writeInt32(value_2.length as int32)
            for (let i = 0; i < value_2.length; i++) {
                const value_2_element : [ ResourceColor | LinearGradient, number ] = value_2[i]
                const value_2_element_0  = value_2_element[0]
                let value_2_element_0_type : int32 = RuntimeType.UNDEFINED
                value_2_element_0_type = runtimeType(value_2_element_0)
                if ((TypeChecker.isColor(value_2_element_0)) || (RuntimeType.NUMBER == value_2_element_0_type) || (RuntimeType.STRING == value_2_element_0_type) || (RuntimeType.OBJECT == value_2_element_0_type)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_2_element_0_0  = value_2_element_0 as ResourceColor
                    let value_2_element_0_0_type : int32 = RuntimeType.UNDEFINED
                    value_2_element_0_0_type = runtimeType(value_2_element_0_0)
                    if (TypeChecker.isColor(value_2_element_0_0)) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_2_element_0_0_0  = value_2_element_0_0 as Color
                        thisSerializer.writeInt32(value_2_element_0_0_0.valueOf())
                    }
                    else if (RuntimeType.NUMBER == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_2_element_0_0_1  = value_2_element_0_0 as number
                        thisSerializer.writeNumber(value_2_element_0_0_1)
                    }
                    else if (RuntimeType.STRING == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(2 as int32)
                        const value_2_element_0_0_2  = value_2_element_0_0 as string
                        thisSerializer.writeString(value_2_element_0_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(3 as int32)
                        const value_2_element_0_0_3  = value_2_element_0_0 as Resource
                        thisSerializer.writeResource(value_2_element_0_0_3)
                    }
                }
                else if (TypeChecker.isLinearGradient(value_2_element_0)) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_2_element_0_1  = value_2_element_0 as LinearGradient
                    thisSerializer.writeLinearGradient(value_2_element_0_1)
                }
                const value_2_element_1  = value_2_element[1]
                thisSerializer.writeNumber(value_2_element_1)
            }
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_colors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_strokeWidth(this.peer.ptr, value)
    }
    descriptionAttribute(value: CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._GaugeAttribute_description(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: GaugeShadowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeShadowOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorAttribute(value: GaugeIndicatorOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeIndicatorOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_indicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier<object>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("ContentModifier", value)
        ArkUIGeneratedNativeModule._GaugeAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkGaugeAttributes extends ArkCommonMethodAttributes {
    value?: number
    startAngle?: number
    endAngle?: number
    colors?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>
    strokeWidth?: Length
    description?: CustomBuilder
    trackShadow?: GaugeShadowOptions
    indicator?: GaugeIndicatorOptions
    privacySensitive?: boolean | undefined
    contentModifier?: ContentModifier<object>
}

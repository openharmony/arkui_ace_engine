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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "./../../ComponentBase"
import { PeerNode } from "./../../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PickerTextStyle } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_String_Number_Void, Type_TextPickerAttribute_onChange_callback, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void } from "./../SyntheticDeclarations"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { DividerOptions, TextPickerOptions, TextPickerAttribute } from "./../ArkTextPickerInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkTextPickerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextPicker_construct(peerId, flags)
        const _peer  = new ArkTextPickerPeer(_peerPtr, peerId, "TextPicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextPickerOptionsAttribute(options?: TextPickerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextPickerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultPickerItemHeightAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._TextPickerAttribute_defaultPickerItemHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    canLoopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextPickerAttribute_canLoop(this.peer.ptr, value ? 1 : 0)
    }
    disappearTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_disappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_textStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAcceptAttribute(value: ((value: string,index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onAccept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: string | Array<string>,index: number | Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextPickerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedIndexAttribute(value: number | Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Array<number>
            thisSerializer.writeInt32(value_1.length as int32)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element : number = value_1[i]
                thisSerializer.writeNumber(value_1_element)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value?: DividerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gradientHeightAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._TextPickerAttribute_gradientHeight(this.peer.ptr, value)
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((value: string | Array<string>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkTextPickerAttributes extends ArkCommonMethodAttributes {
    defaultPickerItemHeight?: number | string
    canLoop?: boolean
    disappearTextStyle?: PickerTextStyle
    textStyle?: PickerTextStyle
    selectedTextStyle?: PickerTextStyle
    onAccept?: ((value: string,index: number) => void)
    onCancel?: (() => void)
    onChange?: ((value: string | Array<string>,index: number | Array<number>) => void)
    selectedIndex?: number | Array<number>
    divider?: DividerOptions | undefined
    gradientHeight?: Dimension
}

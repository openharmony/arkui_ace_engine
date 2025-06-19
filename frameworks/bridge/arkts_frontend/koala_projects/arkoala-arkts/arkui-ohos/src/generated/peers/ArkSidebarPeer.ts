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
import { ButtonStyle, SideBarPosition, SideBarContainerType, SideBarContainerAttribute } from "./../../component/sidebar"
import { Callback_Boolean_Void } from "./../../component/checkbox"
import { DividerStyle } from "./../../component/tabs"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkSideBarContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSideBarContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SideBarContainer_construct(peerId, flags)
        const _peer  = new ArkSideBarContainerPeer(_peerPtr, peerId, "SideBarContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSideBarContainerOptionsAttribute(type?: SideBarContainerType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as SideBarContainerType)
            thisSerializer.writeInt32(type_value.valueOf())
        }
        ArkUIGeneratedNativeModule._SideBarContainerInterface_setSideBarContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showSideBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showSideBar(this.peer.ptr, value ? 1 : 0)
    }
    controlButtonAttribute(value: ButtonStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeButtonStyle(value)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_controlButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showControlButtonAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_showControlButton(this.peer.ptr, value ? 1 : 0)
    }
    onChangeAttribute(value: ((parameter: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth0(this.peer.ptr, value)
    }
    sideBarWidth1Attribute(value: Length): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarWidth1(this.peer.ptr, value)
    }
    minSideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth0(this.peer.ptr, value)
    }
    minSideBarWidth1Attribute(value: Length): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minSideBarWidth1(this.peer.ptr, value)
    }
    maxSideBarWidth0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth0(this.peer.ptr, value)
    }
    maxSideBarWidth1Attribute(value: Length): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_maxSideBarWidth1(this.peer.ptr, value)
    }
    autoHideAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_autoHide(this.peer.ptr, value ? 1 : 0)
    }
    sideBarPositionAttribute(value: SideBarPosition): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_sideBarPosition(this.peer.ptr, value.valueOf())
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
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SideBarContainerAttribute_minContentWidth(this.peer.ptr, value)
    }
    _onChangeEvent_showSideBarAttribute(callback: ((parameter: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SideBarContainerAttribute__onChangeEvent_showSideBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkSideBarContainerAttributes extends ArkCommonMethodAttributes {
    showSideBar?: boolean
    controlButton?: ButtonStyle
    showControlButton?: boolean
    onChange?: ((parameter: boolean) => void)
    sideBarWidth?: number
    minSideBarWidth?: number
    maxSideBarWidth?: number
    autoHide?: boolean
    sideBarPosition?: SideBarPosition
    divider?: DividerStyle | undefined
    minContentWidth?: Dimension
}

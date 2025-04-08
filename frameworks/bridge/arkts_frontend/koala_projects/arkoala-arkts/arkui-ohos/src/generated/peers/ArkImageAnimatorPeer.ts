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
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, AnimationStatus, FillMode } from "./../../component/enums"
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
import { ImageFrameInfo, ImageAnimatorAttribute } from "./../../component/imageAnimator"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkImageAnimatorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageAnimatorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageAnimator_construct(peerId, flags)
        const _peer  = new ArkImageAnimatorPeer(_peerPtr, peerId, "ImageAnimator", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageAnimatorOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ImageAnimatorInterface_setImageAnimatorOptions(this.peer.ptr)
    }
    imagesAttribute(value: Array<ImageFrameInfo>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ImageFrameInfo = value[i]
            thisSerializer.writeImageFrameInfo(value_element)
        }
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_images(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stateAttribute(value: AnimationStatus): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_state(this.peer.ptr, value.valueOf())
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_duration(this.peer.ptr, value)
    }
    reverseAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_reverse(this.peer.ptr, value ? 1 : 0)
    }
    fixedSizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fixedSize(this.peer.ptr, value ? 1 : 0)
    }
    preDecodeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_preDecode(this.peer.ptr, value)
    }
    fillModeAttribute(value: FillMode): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_fillMode(this.peer.ptr, value.valueOf())
    }
    iterationsAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_iterations(this.peer.ptr, value)
    }
    onStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRepeatAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAnimatorAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkImageAnimatorAttributes extends ArkCommonMethodAttributes {
    images?: Array<ImageFrameInfo>
    state?: AnimationStatus
    duration?: number
    reverse?: boolean
    fixedSize?: boolean
    preDecode?: number
    fillMode?: FillMode
    iterations?: number
    onStart?: (() => void)
    onPause?: (() => void)
    onRepeat?: (() => void)
    onCancel?: (() => void)
    onFinish?: (() => void)
}

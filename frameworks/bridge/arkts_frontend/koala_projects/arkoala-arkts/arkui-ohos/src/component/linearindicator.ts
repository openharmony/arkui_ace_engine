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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"
import { ColorMetrics } from "./../generated/ArkColorMetricsMaterialized"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
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
import { ArkLinearIndicatorComponent } from "./../generated/ArkLinearindicator"
import { ArkLinearIndicatorPeer } from "./../generated/peers/ArkLinearindicatorPeer"
export class LinearIndicatorControllerInternal {
    public static fromPtr(ptr: KPointer): LinearIndicatorController {
        const obj : LinearIndicatorController = new LinearIndicatorController()
        obj.peer = new Finalizable(ptr, LinearIndicatorController.getFinalizer())
        return obj
    }
}
export class LinearIndicatorController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_linearindicatorcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LinearIndicatorController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = LinearIndicatorController.ctor_linearindicatorcontroller()
        this.peer = new Finalizable(ctorPtr, LinearIndicatorController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LinearIndicatorController_getFinalizer()
    }
    public setProgress(index: number, progress: number): void {
        const index_casted = index as (number)
        const progress_casted = progress as (number)
        this.setProgress_serialize(index_casted, progress_casted)
        return
    }
    public start(options?: LinearIndicatorStartOptions): void {
        const options_casted = options as (LinearIndicatorStartOptions | undefined)
        this.start_serialize(options_casted)
        return
    }
    public pause(): void {
        this.pause_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    private setProgress_serialize(index: number, progress: number): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_setProgress(this.peer!.ptr, index, progress)
    }
    private start_serialize(options?: LinearIndicatorStartOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeLinearIndicatorStartOptions(options_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorController_start(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_pause(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_stop(this.peer!.ptr)
    }
}
export interface LinearIndicatorStartOptions {
    interval?: number;
    duration?: number;
}
export interface LinearIndicatorStyle {
    space?: LengthMetrics;
    strokeWidth?: LengthMetrics;
    strokeRadius?: LengthMetrics;
    trackBackgroundColor?: ColorMetrics;
    trackColor?: ColorMetrics;
}
export type OnLinearIndicatorChangeCallback = (index: number, progress: number) => void;
/** @memo:stable */
export interface LinearIndicatorAttribute extends CommonMethod {
    /** @memo */
    setLinearIndicatorOptions(count?: number, controller?: LinearIndicatorController): this
    /** @memo */
    indicatorStyle(value?: LinearIndicatorStyle): this
    /** @memo */
    indicatorLoop(value?: boolean): this
    /** @memo */
    onChange(value?: OnLinearIndicatorChangeCallback): this
}
/** @memo */
export function LinearIndicator(
  /** @memo */
  style: ((attributes: LinearIndicatorAttribute) => void) | undefined,
  count?: number | undefined, controller?: LinearIndicatorController | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkLinearIndicatorComponent()
    })
    NodeAttach<ArkLinearIndicatorPeer>((): ArkLinearIndicatorPeer => ArkLinearIndicatorPeer.create(receiver), (_: ArkLinearIndicatorPeer) => {
        receiver.setLinearIndicatorOptions(count,controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

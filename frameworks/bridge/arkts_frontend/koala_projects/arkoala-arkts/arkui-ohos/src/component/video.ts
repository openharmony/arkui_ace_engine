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
import { Resource } from "global/resource";
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { ImageAIOptions, ImageAnalyzerConfig } from "./imageCommon"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { ArkVideoComponent } from "./../generated/ArkVideo"
import { ArkVideoPeer } from "./../generated/peers/ArkVideoPeer"
export class VideoControllerInternal {
    public static fromPtr(ptr: KPointer): VideoController {
        const obj : VideoController = new VideoController()
        obj.peer = new Finalizable(ptr, VideoController.getFinalizer())
        return obj
    }
}
export class VideoController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_videocontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VideoController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = VideoController.ctor_videocontroller()
        this.peer = new Finalizable(ctorPtr, VideoController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VideoController_getFinalizer()
    }
    public start(): undefined {
        return this.start_serialize()
    }
    public pause(): undefined {
        return this.pause_serialize()
    }
    public stop(): undefined {
        return this.stop_serialize()
    }
    public setCurrentTime(value: number, seekMode?: SeekMode): undefined {
        const value_type = runtimeType(value)
        const seekMode_type = runtimeType(seekMode)
        if (RuntimeType.UNDEFINED == seekMode_type) {
            const value_casted = value as (number)
            return this.setCurrentTime0_serialize(value_casted)
        }
        if (TypeChecker.isSeekMode(seekMode)) {
            const value_casted = value as (number)
            const seekMode_casted = seekMode as (SeekMode)
            return this.setCurrentTime1_serialize(value_casted, seekMode_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public requestFullscreen(value: boolean): undefined {
        const value_casted = value as (boolean)
        return this.requestFullscreen_serialize(value_casted)
    }
    public exitFullscreen(): undefined {
        return this.exitFullscreen_serialize()
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_start(this.peer!.ptr)
        return retval
    }
    private pause_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_pause(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_stop(this.peer!.ptr)
        return retval
    }
    private setCurrentTime0_serialize(value: number): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime0(this.peer!.ptr, value)
        return retval
    }
    private requestFullscreen_serialize(value: boolean): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
        return retval
    }
    private exitFullscreen_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
        return retval
    }
    private setCurrentTime1_serialize(value: number, seekMode: SeekMode): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime1(this.peer!.ptr, value, seekMode.valueOf())
        return retval
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_reset(this.peer!.ptr)
    }
}
export enum SeekMode {
    PREVIOUS_KEYFRAME = 0,
    PreviousKeyframe = 0,
    NEXT_KEYFRAME = 1,
    NextKeyframe = 1,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = 2,
    ACCURATE = 3,
    Accurate = 3
}
export enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X = 0,
    Speed_Forward_0_75_X = 0,
    SPEED_FORWARD_1_00_X = 1,
    Speed_Forward_1_00_X = 1,
    SPEED_FORWARD_1_25_X = 2,
    Speed_Forward_1_25_X = 2,
    SPEED_FORWARD_1_75_X = 3,
    Speed_Forward_1_75_X = 3,
    SPEED_FORWARD_2_00_X = 4,
    Speed_Forward_2_00_X = 4
}
export interface FullscreenInfo {
    fullscreen: boolean;
}
export interface PreparedInfo {
    duration: number;
}
export interface PlaybackInfo {
    time: number;
}
export interface VideoOptions {
    src?: string | Resource;
    currentProgressRate?: number | string | PlaybackSpeed;
    previewUri?: string | PixelMap | Resource;
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
}
export type Callback_FullscreenInfo_Void = (parameter: FullscreenInfo) => void;
export type Callback_PreparedInfo_Void = (parameter: PreparedInfo) => void;
export type Callback_PlaybackInfo_Void = (parameter: PlaybackInfo) => void;
/** @memo:stable */
export interface VideoAttribute extends CommonMethod {
    /** @memo */
    setVideoOptions(value: VideoOptions): this
    /** @memo */
    muted(value: boolean): this
    /** @memo */
    autoPlay(value: boolean): this
    /** @memo */
    controls(value: boolean): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    objectFit(value: ImageFit): this
    /** @memo */
    onStart(value: VoidCallback): this
    /** @memo */
    onPause(value: VoidCallback): this
    /** @memo */
    onFinish(value: VoidCallback): this
    /** @memo */
    onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this
    /** @memo */
    onPrepared(value: ((parameter: PreparedInfo) => void)): this
    /** @memo */
    onSeeking(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onSeeked(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onUpdate(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onError(value: (() => void)): this
    /** @memo */
    onStop(value: (() => void)): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    analyzerConfig(value: ImageAnalyzerConfig): this
}
/** @memo */
export function Video(
  /** @memo */
  style: ((attributes: VideoAttribute) => void) | undefined,
  value: VideoOptions, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkVideoComponent()
    })
    NodeAttach<ArkVideoPeer>((): ArkVideoPeer => ArkVideoPeer.create(receiver), (_: ArkVideoPeer) => {
        receiver.setVideoOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

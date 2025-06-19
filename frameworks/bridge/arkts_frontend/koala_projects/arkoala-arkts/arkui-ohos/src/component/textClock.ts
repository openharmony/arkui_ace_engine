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
import { CommonConfiguration, ContentModifier, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontStyle, FontWeight } from "./enums"
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
import { DateTimeOptions } from "./timePicker"
import { ArkTextClockComponent } from "./../generated/ArkTextClock"
import { ArkTextClockPeer } from "./../generated/peers/ArkTextClockPeer"
export class TextClockControllerInternal {
    public static fromPtr(ptr: KPointer): TextClockController {
        const obj : TextClockController = new TextClockController()
        obj.peer = new Finalizable(ptr, TextClockController.getFinalizer())
        return obj
    }
}
export class TextClockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textclockcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextClockController.ctor_textclockcontroller()
        this.peer = new Finalizable(ctorPtr, TextClockController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextClockController_getFinalizer()
    }
    public start(): undefined {
        return this.start_serialize()
    }
    public stop(): undefined {
        return this.stop_serialize()
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_start(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_stop(this.peer!.ptr)
        return retval
    }
}
export interface TextClockConfiguration extends CommonConfiguration<TextClockConfiguration> {
    timeZoneOffset: number;
    started: boolean;
    timeValue: number;
}
export interface TextClockOptions {
    timeZoneOffset?: number;
    controller?: TextClockController;
}
/** @memo:stable */
export interface TextClockAttribute extends CommonMethod {
    /** @memo */
    setTextClockOptions(options?: TextClockOptions): this
    /** @memo */
    format(value: string): this
    /** @memo */
    onDateChange(value: ((index: number) => void)): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: Length): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontFamily(value: ResourceStr): this
    /** @memo */
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    contentModifier(value: ContentModifier<object>): this
    /** @memo */
    dateTimeOptions(value?: DateTimeOptions): this
}
/** @memo */
export function TextClock(
  /** @memo */
  style: ((attributes: TextClockAttribute) => void) | undefined,
  options?: TextClockOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTextClockComponent()
    })
    NodeAttach<ArkTextClockPeer>((): ArkTextClockPeer => ArkTextClockPeer.create(receiver), (_: ArkTextClockPeer) => {
        receiver.setTextClockOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

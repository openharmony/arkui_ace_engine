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
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
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
import { DotIndicator, DigitIndicator } from "./swiper"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ArkIndicatorComponentComponent } from "./../generated/ArkIndicatorcomponent"
import { ArkIndicatorComponentPeer } from "./../generated/peers/ArkIndicatorcomponentPeer"
export class IndicatorComponentControllerInternal {
    public static fromPtr(ptr: KPointer): IndicatorComponentController {
        const obj : IndicatorComponentController = new IndicatorComponentController()
        obj.peer = new Finalizable(ptr, IndicatorComponentController.getFinalizer())
        return obj
    }
}
export class IndicatorComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_indicatorcomponentcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._IndicatorComponentController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = IndicatorComponentController.ctor_indicatorcomponentcontroller()
        this.peer = new Finalizable(ctorPtr, IndicatorComponentController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._IndicatorComponentController_getFinalizer()
    }
    public showNext(): void {
        this.showNext_serialize()
        return
    }
    public showPrevious(): void {
        this.showPrevious_serialize()
        return
    }
    public changeIndex(index: number, useAnimation?: boolean): void {
        const index_casted = index as (number)
        const useAnimation_casted = useAnimation as (boolean | undefined)
        this.changeIndex_serialize(index_casted, useAnimation_casted)
        return
    }
    private showNext_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showNext(this.peer!.ptr)
    }
    private showPrevious_serialize(): void {
        ArkUIGeneratedNativeModule._IndicatorComponentController_showPrevious(this.peer!.ptr)
    }
    private changeIndex_serialize(index: number, useAnimation?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let useAnimation_type : int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type as int32)
        if ((RuntimeType.UNDEFINED) != (useAnimation_type)) {
            const useAnimation_value  = useAnimation!
            thisSerializer.writeBoolean(useAnimation_value)
        }
        ArkUIGeneratedNativeModule._IndicatorComponentController_changeIndex(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
/** @memo:stable */
export interface IndicatorComponentAttribute extends CommonMethod {
    /** @memo */
    setIndicatorComponentOptions(controller?: IndicatorComponentController): this
    /** @memo */
    initialIndex(value: number): this
    /** @memo */
    count(value: number): this
    /** @memo */
    style(value: DotIndicator | DigitIndicator): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    vertical(value: boolean): this
    /** @memo */
    onChange(value: ((index: number) => void)): this
}
/** @memo */
export function IndicatorComponent(
  /** @memo */
  style: ((attributes: IndicatorComponentAttribute) => void) | undefined,
  controller?: IndicatorComponentController | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkIndicatorComponentComponent()
    })
    NodeAttach<ArkIndicatorComponentPeer>((): ArkIndicatorComponentPeer => ArkIndicatorComponentPeer.create(receiver), (_: ArkIndicatorComponentPeer) => {
        receiver.setIndicatorComponentOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

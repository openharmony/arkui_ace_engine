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
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, AnimationStatus, Curve, FillMode, PlayMode } from "./enums"
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
import { ArkAnimatorComponent } from "./../generated/ArkAnimator"
import { ArkAnimatorPeer } from "./../generated/peers/ArkAnimatorPeer"
export class SpringPropInternal {
    public static fromPtr(ptr: KPointer): SpringProp {
        const obj : SpringProp = new SpringProp(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, SpringProp.getFinalizer())
        return obj
    }
}
export class SpringProp implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_springprop(mass: number, stiffness: number, damping: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringProp_ctor(mass, stiffness, damping)
        return retval
    }
    constructor(mass?: number, stiffness?: number, damping?: number) {
        if (((mass) !== (undefined)) || ((stiffness) !== (undefined)) || ((damping) !== (undefined)))
        {
            const ctorPtr : KPointer = SpringProp.ctor_springprop((mass)!, (stiffness)!, (damping)!)
            this.peer = new Finalizable(ctorPtr, SpringProp.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringProp_getFinalizer()
    }
}
export class SpringMotionInternal {
    public static fromPtr(ptr: KPointer): SpringMotion {
        const obj : SpringMotion = new SpringMotion(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, SpringMotion.getFinalizer())
        return obj
    }
}
export class SpringMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_springmotion(start: number, end: number, velocity: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SpringMotion_ctor(start, end, velocity, toPeerPtr(prop))
        return retval
    }
    constructor(start?: number, end?: number, velocity?: number, prop?: SpringProp) {
        if (((start) !== (undefined)) || ((end) !== (undefined)) || ((velocity) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr : KPointer = SpringMotion.ctor_springmotion((start)!, (end)!, (velocity)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, SpringMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SpringMotion_getFinalizer()
    }
}
export class FrictionMotionInternal {
    public static fromPtr(ptr: KPointer): FrictionMotion {
        const obj : FrictionMotion = new FrictionMotion(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, FrictionMotion.getFinalizer())
        return obj
    }
}
export class FrictionMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_frictionmotion(friction: number, position: number, velocity: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrictionMotion_ctor(friction, position, velocity)
        return retval
    }
    constructor(friction?: number, position?: number, velocity?: number) {
        if (((friction) !== (undefined)) || ((position) !== (undefined)) || ((velocity) !== (undefined)))
        {
            const ctorPtr : KPointer = FrictionMotion.ctor_frictionmotion((friction)!, (position)!, (velocity)!)
            this.peer = new Finalizable(ctorPtr, FrictionMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrictionMotion_getFinalizer()
    }
}
export class ScrollMotionInternal {
    public static fromPtr(ptr: KPointer): ScrollMotion {
        const obj : ScrollMotion = new ScrollMotion(undefined, undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ScrollMotion.getFinalizer())
        return obj
    }
}
export class ScrollMotion implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scrollmotion(position: number, velocity: number, min: number, max: number, prop: SpringProp): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScrollMotion_ctor(position, velocity, min, max, toPeerPtr(prop))
        return retval
    }
    constructor(position?: number, velocity?: number, min?: number, max?: number, prop?: SpringProp) {
        if (((position) !== (undefined)) || ((velocity) !== (undefined)) || ((min) !== (undefined)) || ((max) !== (undefined)) || ((prop) !== (undefined)))
        {
            const ctorPtr : KPointer = ScrollMotion.ctor_scrollmotion((position)!, (velocity)!, (min)!, (max)!, (prop)!)
            this.peer = new Finalizable(ctorPtr, ScrollMotion.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollMotion_getFinalizer()
    }
}
/** @memo:stable */
export interface AnimatorAttribute extends CommonMethod {
    /** @memo */
    setAnimatorOptions(value: string): this
    /** @memo */
    state(value: AnimationStatus): this
    /** @memo */
    duration(value: number): this
    /** @memo */
    curve(value: Curve): this
    /** @memo */
    delay(value: number): this
    /** @memo */
    fillMode(value: FillMode): this
    /** @memo */
    iterations(value: number): this
    /** @memo */
    playMode(value: PlayMode): this
    /** @memo */
    motion(value: SpringMotion): this
    /** @memo */
    onStart(value: (() => void)): this
    /** @memo */
    onPause(value: (() => void)): this
    /** @memo */
    onRepeat(value: (() => void)): this
    /** @memo */
    onCancel(value: (() => void)): this
    /** @memo */
    onFinish(value: (() => void)): this
    /** @memo */
    onFrame(value: ((index: number) => void)): this
}
/** @memo */
export function Animator(
  /** @memo */
  style: ((attributes: AnimatorAttribute) => void) | undefined,
  value: string, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkAnimatorComponent()
    })
    NodeAttach<ArkAnimatorPeer>((): ArkAnimatorPeer => ArkAnimatorPeer.create(receiver), (_: ArkAnimatorPeer) => {
        receiver.setAnimatorOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

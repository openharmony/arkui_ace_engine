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

import { SymbolEffect, EffectScope, EffectDirection } from "./../generated/ArkArkuiExternalInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global/resource";
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontWeight } from "./enums"
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
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { ArkSymbolGlyphComponent } from "./../generated/ArkSymbolglyph"
import { ArkSymbolGlyphPeer } from "./../generated/peers/ArkSymbolglyphPeer"
export class HierarchicalSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): HierarchicalSymbolEffect {
        const obj : HierarchicalSymbolEffect = new HierarchicalSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, HierarchicalSymbolEffect.getFinalizer())
        return obj
    }
}
export class HierarchicalSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get fillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle()
    }
    set fillStyle(fillStyle: EffectFillStyle | undefined) {
        const fillStyle_NonNull  = (fillStyle as EffectFillStyle)
        this.setFillStyle(fillStyle_NonNull)
    }
    static ctor_hierarchicalsymboleffect(fillStyle?: EffectFillStyle): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        thisSerializer.writeInt8(fillStyle_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillStyle_type)) {
            const fillStyle_value  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(fillStyle_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(fillStyle?: EffectFillStyle) {
        const ctorPtr : KPointer = HierarchicalSymbolEffect.ctor_hierarchicalsymboleffect((fillStyle)!)
        this.peer = new Finalizable(ctorPtr, HierarchicalSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFinalizer()
    }
    private getFillStyle(): EffectFillStyle {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: EffectFillStyle): void {
        const fillStyle_casted = fillStyle as (EffectFillStyle)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getFillStyle_serialize(): EffectFillStyle {
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFillStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setFillStyle_serialize(fillStyle: EffectFillStyle): void {
        ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_setFillStyle(this.peer!.ptr, fillStyle.valueOf())
    }
}
export class AppearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): AppearSymbolEffect {
        const obj : AppearSymbolEffect = new AppearSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, AppearSymbolEffect.getFinalizer())
        return obj
    }
}
export class AppearSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_appearsymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(scope_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        const ctorPtr : KPointer = AppearSymbolEffect.ctor_appearsymboleffect((scope)!)
        this.peer = new Finalizable(ctorPtr, AppearSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AppearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope {
        const retval  = ArkUIGeneratedNativeModule._AppearSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._AppearSymbolEffect_setScope(this.peer!.ptr, scope.valueOf())
    }
}
export class DisappearSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): DisappearSymbolEffect {
        const obj : DisappearSymbolEffect = new DisappearSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, DisappearSymbolEffect.getFinalizer())
        return obj
    }
}
export class DisappearSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_disappearsymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(scope_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        const ctorPtr : KPointer = DisappearSymbolEffect.ctor_disappearsymboleffect((scope)!)
        this.peer = new Finalizable(ctorPtr, DisappearSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DisappearSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope {
        const retval  = ArkUIGeneratedNativeModule._DisappearSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._DisappearSymbolEffect_setScope(this.peer!.ptr, scope.valueOf())
    }
}
export class BounceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): BounceSymbolEffect {
        const obj : BounceSymbolEffect = new BounceSymbolEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, BounceSymbolEffect.getFinalizer())
        return obj
    }
}
export class BounceSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    get direction(): EffectDirection | undefined {
        return this.getDirection()
    }
    set direction(direction: EffectDirection | undefined) {
        const direction_NonNull  = (direction as EffectDirection)
        this.setDirection(direction_NonNull)
    }
    static ctor_bouncesymboleffect(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(scope_value.valueOf())
        }
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value  = (direction as EffectDirection)
            thisSerializer.writeInt32(direction_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope, direction?: EffectDirection) {
        const ctorPtr : KPointer = BounceSymbolEffect.ctor_bouncesymboleffect((scope)!, (direction)!)
        this.peer = new Finalizable(ctorPtr, BounceSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BounceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getDirection(): EffectDirection {
        return this.getDirection_serialize()
    }
    private setDirection(direction: EffectDirection): void {
        const direction_casted = direction as (EffectDirection)
        this.setDirection_serialize(direction_casted)
        return
    }
    private getScope_serialize(): EffectScope {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setScope(this.peer!.ptr, scope.valueOf())
    }
    private getDirection_serialize(): EffectDirection {
        const retval  = ArkUIGeneratedNativeModule._BounceSymbolEffect_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: EffectDirection): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setDirection(this.peer!.ptr, direction.valueOf())
    }
}
export enum SymbolRenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2
}
export enum SymbolEffectStrategy {
    NONE = 0,
    SCALE = 1,
    HIERARCHICAL = 2
}
export enum EffectFillStyle {
    CUMULATIVE = 0,
    ITERATIVE = 1
}
export interface PulseSymbolEffect extends SymbolEffect {
}
/** @memo:stable */
export interface SymbolGlyphAttribute extends CommonMethod {
    /** @memo */
    setSymbolGlyphOptions(value?: Resource): this
    /** @memo */
    fontSize(value: number | string | Resource): this
    /** @memo */
    fontColor(value: Array<ResourceColor>): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    effectStrategy(value: SymbolEffectStrategy): this
    /** @memo */
    renderingStrategy(value: SymbolRenderingStrategy): this
    /** @memo */
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | undefined | number | undefined): this
}
/** @memo */
export function SymbolGlyph(
  /** @memo */
  style: ((attributes: SymbolGlyphAttribute) => void) | undefined,
  value?: Resource | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkSymbolGlyphComponent()
    })
    NodeAttach<ArkSymbolGlyphPeer>((): ArkSymbolGlyphPeer => ArkSymbolGlyphPeer.create(receiver), (_: ArkSymbolGlyphPeer) => {
        receiver.setSymbolGlyphOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

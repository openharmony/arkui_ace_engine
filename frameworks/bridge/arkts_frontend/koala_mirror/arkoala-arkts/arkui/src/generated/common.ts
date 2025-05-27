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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { DrawContext, LengthMetrics, Edges } from "./arkui-graphics"
import { UnifiedData, UnifiedDataInternal, ComponentContent, UIContext, Context, PointerStyle, ContextInternal } from "./arkui-custom"
import { Summary, IntentionCode, EdgeStyles, CircleShape, EllipseShape, PathShape, RectShape, ImageModifier, SymbolGlyphModifier } from "./arkui-external"
import { KeyType, KeySource, Color, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, Curve, SharedTransitionEffectType, Placement, ArrowPointPosition, LineCapStyle, LineJoinStyle, BarState, EdgeEffect, PlayMode, HorizontalAlign, VerticalAlign, TransitionType, FontWeight, TouchType, ClickEffectLevel, NestedScrollMode, PixelRoundCalcPolicy, IlluminatedType, MouseButton, MouseAction, AccessibilityHoverType } from "./enums"
import { Callback_Void } from "./ability_component"
import { ResourceColor, ConstraintSizeOptions, DirectionalEdgesT, SizeOptions, Length, ChainWeightOptions, Padding, LocalizedPadding, Position, BorderOptions, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Bias, Font } from "./units"
import { Resource } from "./resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ResizableOptions } from "./image"
import { VisualEffect, Filter, BrightnessBlender } from "./arkui-uieffect"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { TransformationMatrix } from "./arkui-common"
import { UniformDataType } from "./arkui-uniformtypedescriptor"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface, GestureInterface, TapGestureParameters, Callback_GestureEvent_Void, GestureEvent, Literal_Number_duration_fingers_Boolean_repeat, Literal_Number_distance_fingers_PanDirection_direction, PanDirection, PanGestureOptions, Literal_Number_distance_fingers, Literal_Number_fingers_speed_SwipeDirection_direction, SwipeDirection, Literal_Number_angle_fingers, GestureMode, FingerInfo, GestureControl, GestureRecognizerState, EventTargetInfo, GestureHandler, GesturePriority } from "./gesture"
import { PixelMap } from "./arkui-pixelmap"
import { BlendMode } from "./arkui-drawing"
import { Tuple_Number_Number, Tuple_Number_Number_Number } from "./arkui-synthetics"
import { Callback_Number_Void } from "./alphabet_indexer"
import { Callback_Number_Number_Void } from "./grid"
import { TextDecorationType, TextDecorationStyle, FontStyle } from "./arkui-graphics-text"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./button"
import { AnimationRange_Number } from "./type-replacements"
import { ScrollState } from "./list"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { GlobalScope } from "./GlobalScope"
export interface ICurve {
    interpolate(fraction: number): number
}
export class ICurveInternal implements MaterializedBase,ICurve {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_icurve(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ICurve_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ICurveInternal.ctor_icurve()
        this.peer = new Finalizable(ctorPtr, ICurveInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ICurve_getFinalizer()
    }
    public interpolate(fraction: number): number {
        const fraction_casted = fraction as (number)
        return this.interpolate_serialize(fraction_casted)
    }
    private interpolate_serialize(fraction: number): number {
        const retval  = ArkUIGeneratedNativeModule._ICurve_interpolate(this.peer!.ptr, fraction)
        return retval
    }
    public static fromPtr(ptr: KPointer): ICurveInternal {
        const obj : ICurveInternal = new ICurveInternal()
        obj.peer = new Finalizable(ptr, ICurveInternal.getFinalizer())
        return obj
    }
}
export class DrawModifierInternal {
    public static fromPtr(ptr: KPointer): DrawModifier {
        const obj : DrawModifier = new DrawModifier()
        obj.peer = new Finalizable(ptr, DrawModifier.getFinalizer())
        return obj
    }
}
export class DrawModifier implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawmodifier(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawModifier_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = DrawModifier.ctor_drawmodifier()
        this.peer = new Finalizable(ctorPtr, DrawModifier.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawModifier_getFinalizer()
    }
    public drawBehind(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawBehind_serialize(drawContext_casted)
        return
    }
    public drawContent(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawContent_serialize(drawContext_casted)
        return
    }
    public drawFront(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawFront_serialize(drawContext_casted)
        return
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private drawBehind_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawBehind(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private drawContent_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawContent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private drawFront_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawFront(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._DrawModifier_invalidate(this.peer!.ptr)
    }
}
export class TransitionEffectInternal {
    public static fromPtr(ptr: KPointer): TransitionEffect {
        const obj : TransitionEffect = new TransitionEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, TransitionEffect.getFinalizer())
        return obj
    }
}
export class TransitionEffect implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static get IDENTITY(): TransitionEffect {
        return TransitionEffect.getIDENTITY()
    }
    static get OPACITY(): TransitionEffect {
        return TransitionEffect.getOPACITY()
    }
    static get SLIDE(): TransitionEffect {
        return TransitionEffect.getSLIDE()
    }
    static get SLIDE_SWITCH(): TransitionEffect {
        return TransitionEffect.getSLIDE_SWITCH()
    }
    static ctor_transitioneffect(type: string, effect: TransitionEffects): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        const effect_identity  = effect.identity
        const effect_opacity  = effect.opacity
        thisSerializer.writeNumber(effect_opacity)
        const effect_slideSwitch  = effect.slideSwitch
        const effect_move  = effect.move
        thisSerializer.writeInt32(TypeChecker.TransitionEdge_ToNumeric(effect_move))
        const effect_translate  = effect.translate
        thisSerializer.writeTranslateOptions(effect_translate)
        const effect_rotate  = effect.rotate
        thisSerializer.writeRotateOptions(effect_rotate)
        const effect_scale  = effect.scale
        thisSerializer.writeScaleOptions(effect_scale)
        const effect_asymmetric  = effect.asymmetric
        const effect_asymmetric_appear  = effect_asymmetric.appear
        thisSerializer.writeTransitionEffect(effect_asymmetric_appear)
        const effect_asymmetric_disappear  = effect_asymmetric.disappear
        thisSerializer.writeTransitionEffect(effect_asymmetric_disappear)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_ctor(type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(type?: string, effect?: TransitionEffects) {
        if (((type) !== (undefined)) || ((effect) !== (undefined)))
        {
            const ctorPtr : KPointer = TransitionEffect.ctor_transitioneffect((type)!, (effect)!)
            this.peer = new Finalizable(ctorPtr, TransitionEffect.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TransitionEffect_getFinalizer()
    }
    public static translate(options: TranslateOptions): TransitionEffect {
        const options_casted = options as (TranslateOptions)
        return TransitionEffect.translate_serialize(options_casted)
    }
    public static rotate(options: RotateOptions): TransitionEffect {
        const options_casted = options as (RotateOptions)
        return TransitionEffect.rotate_serialize(options_casted)
    }
    public static scale(options: ScaleOptions): TransitionEffect {
        const options_casted = options as (ScaleOptions)
        return TransitionEffect.scale_serialize(options_casted)
    }
    public static opacity(alpha: number): TransitionEffect {
        const alpha_casted = alpha as (number)
        return TransitionEffect.opacity_serialize(alpha_casted)
    }
    public static move(edge: TransitionEdge): TransitionEffect {
        const edge_casted = edge as (TransitionEdge)
        return TransitionEffect.move_serialize(edge_casted)
    }
    public static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect {
        const appear_casted = appear as (TransitionEffect)
        const disappear_casted = disappear as (TransitionEffect)
        return TransitionEffect.asymmetric_serialize(appear_casted, disappear_casted)
    }
    public animation(value: AnimateParam): TransitionEffect {
        const value_casted = value as (AnimateParam)
        return this.animation_serialize(value_casted)
    }
    public combine(transitionEffect: TransitionEffect): TransitionEffect {
        const transitionEffect_casted = transitionEffect as (TransitionEffect)
        return this.combine_serialize(transitionEffect_casted)
    }
    private static getIDENTITY(): TransitionEffect {
        return TransitionEffect.getIDENTITY_serialize()
    }
    private static getOPACITY(): TransitionEffect {
        return TransitionEffect.getOPACITY_serialize()
    }
    private static getSLIDE(): TransitionEffect {
        return TransitionEffect.getSLIDE_serialize()
    }
    private static getSLIDE_SWITCH(): TransitionEffect {
        return TransitionEffect.getSLIDE_SWITCH_serialize()
    }
    private static translate_serialize(options: TranslateOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_translate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static rotate_serialize(options: RotateOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRotateOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_rotate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static scale_serialize(options: ScaleOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScaleOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_scale(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static opacity_serialize(alpha: number): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_opacity(alpha)
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static move_serialize(edge: TransitionEdge): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_move(TypeChecker.TransitionEdge_ToNumeric(edge))
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static asymmetric_serialize(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_asymmetric(toPeerPtr(appear), toPeerPtr(disappear))
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private animation_serialize(value: AnimateParam): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_animation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private combine_serialize(transitionEffect: TransitionEffect): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_combine(this.peer!.ptr, toPeerPtr(transitionEffect))
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getIDENTITY_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getIDENTITY()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getOPACITY_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getOPACITY()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getSLIDE_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getSLIDE()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getSLIDE_SWITCH_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getSLIDE_SWITCH()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
}
export interface BaseEvent {
    target: EventTarget
    timestamp: int64
    source: SourceType
    axisHorizontal?: number | undefined
    axisVertical?: number | undefined
    pressure: number
    tiltX: number
    tiltY: number
    sourceTool: SourceTool
    deviceId?: number | undefined
    getModifierKeyState(keys: Array<string>): boolean
}
export class BaseEventInternal implements MaterializedBase,BaseEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get target(): EventTarget {
        throw new Error("Not implemented")
    }
    set target(target: EventTarget) {
        this.setTarget(target)
    }
    get timestamp(): int64 {
        return this.getTimestamp()
    }
    set timestamp(timestamp: int64) {
        this.setTimestamp(timestamp)
    }
    get source(): SourceType {
        return this.getSource()
    }
    set source(source: SourceType) {
        this.setSource(source)
    }
    get axisHorizontal(): number | undefined {
        return this.getAxisHorizontal()
    }
    set axisHorizontal(axisHorizontal: number | undefined) {
        const axisHorizontal_NonNull  = (axisHorizontal as number)
        this.setAxisHorizontal(axisHorizontal_NonNull)
    }
    get axisVertical(): number | undefined {
        return this.getAxisVertical()
    }
    set axisVertical(axisVertical: number | undefined) {
        const axisVertical_NonNull  = (axisVertical as number)
        this.setAxisVertical(axisVertical_NonNull)
    }
    get pressure(): number {
        return this.getPressure()
    }
    set pressure(pressure: number) {
        this.setPressure(pressure)
    }
    get tiltX(): number {
        return this.getTiltX()
    }
    set tiltX(tiltX: number) {
        this.setTiltX(tiltX)
    }
    get tiltY(): number {
        return this.getTiltY()
    }
    set tiltY(tiltY: number) {
        this.setTiltY(tiltY)
    }
    get sourceTool(): SourceTool {
        return this.getSourceTool()
    }
    set sourceTool(sourceTool: SourceTool) {
        this.setSourceTool(sourceTool)
    }
    get deviceId(): number | undefined {
        return this.getDeviceId()
    }
    set deviceId(deviceId: number | undefined) {
        const deviceId_NonNull  = (deviceId as number)
        this.setDeviceId(deviceId_NonNull)
    }
    static ctor_baseevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = BaseEventInternal.ctor_baseevent()
        this.peer = new Finalizable(ctorPtr, BaseEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseEvent_getFinalizer()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private getTarget(): EventTarget {
        return this.getTarget_serialize()
    }
    private setTarget(target: EventTarget): void {
        const target_casted = target as (EventTarget)
        this.setTarget_serialize(target_casted)
        return
    }
    private getTimestamp(): int64 {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: int64): void {
        const timestamp_casted = timestamp as (int64)
        this.setTimestamp_serialize(timestamp_casted)
        return
    }
    private getSource(): SourceType {
        return this.getSource_serialize()
    }
    private setSource(source: SourceType): void {
        const source_casted = source as (SourceType)
        this.setSource_serialize(source_casted)
        return
    }
    private getAxisHorizontal(): number | undefined {
        return this.getAxisHorizontal_serialize()
    }
    private setAxisHorizontal(axisHorizontal: number): void {
        const axisHorizontal_casted = axisHorizontal as (number)
        this.setAxisHorizontal_serialize(axisHorizontal_casted)
        return
    }
    private getAxisVertical(): number | undefined {
        return this.getAxisVertical_serialize()
    }
    private setAxisVertical(axisVertical: number): void {
        const axisVertical_casted = axisVertical as (number)
        this.setAxisVertical_serialize(axisVertical_casted)
        return
    }
    private getPressure(): number {
        return this.getPressure_serialize()
    }
    private setPressure(pressure: number): void {
        const pressure_casted = pressure as (number)
        this.setPressure_serialize(pressure_casted)
        return
    }
    private getTiltX(): number {
        return this.getTiltX_serialize()
    }
    private setTiltX(tiltX: number): void {
        const tiltX_casted = tiltX as (number)
        this.setTiltX_serialize(tiltX_casted)
        return
    }
    private getTiltY(): number {
        return this.getTiltY_serialize()
    }
    private setTiltY(tiltY: number): void {
        const tiltY_casted = tiltY as (number)
        this.setTiltY_serialize(tiltY_casted)
        return
    }
    private getSourceTool(): SourceTool {
        return this.getSourceTool_serialize()
    }
    private setSourceTool(sourceTool: SourceTool): void {
        const sourceTool_casted = sourceTool as (SourceTool)
        this.setSourceTool_serialize(sourceTool_casted)
        return
    }
    private getDeviceId(): number | undefined {
        return this.getDeviceId_serialize()
    }
    private setDeviceId(deviceId: number): void {
        const deviceId_casted = deviceId as (number)
        this.setDeviceId_serialize(deviceId_casted)
        return
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getTarget_serialize(): EventTarget {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTarget(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : EventTarget = retvalDeserializer.readEventTarget()
        return returnResult
    }
    private setTarget_serialize(target: EventTarget): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEventTarget(target)
        ArkUIGeneratedNativeModule._BaseEvent_setTarget(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTimestamp_serialize(): int64 {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: int64): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTimestamp(this.peer!.ptr, timestamp)
    }
    private getSource_serialize(): SourceType {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getSource(this.peer!.ptr)
        return TypeChecker.SourceType_FromNumeric(retval)
    }
    private setSource_serialize(source: SourceType): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSource(this.peer!.ptr, TypeChecker.SourceType_ToNumeric(source))
    }
    private getAxisHorizontal_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisHorizontal(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setAxisHorizontal_serialize(axisHorizontal: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisHorizontal(this.peer!.ptr, axisHorizontal)
    }
    private getAxisVertical_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisVertical(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setAxisVertical_serialize(axisVertical: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisVertical(this.peer!.ptr, axisVertical)
    }
    private getPressure_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getPressure(this.peer!.ptr)
        return retval
    }
    private setPressure_serialize(pressure: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setPressure(this.peer!.ptr, pressure)
    }
    private getTiltX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTiltX(this.peer!.ptr)
        return retval
    }
    private setTiltX_serialize(tiltX: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTiltX(this.peer!.ptr, tiltX)
    }
    private getTiltY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTiltY(this.peer!.ptr)
        return retval
    }
    private setTiltY_serialize(tiltY: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTiltY(this.peer!.ptr, tiltY)
    }
    private getSourceTool_serialize(): SourceTool {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getSourceTool(this.peer!.ptr)
        return TypeChecker.SourceTool_FromNumeric(retval)
    }
    private setSourceTool_serialize(sourceTool: SourceTool): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSourceTool(this.peer!.ptr, TypeChecker.SourceTool_ToNumeric(sourceTool))
    }
    private getDeviceId_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getDeviceId(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDeviceId_serialize(deviceId: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setDeviceId(this.peer!.ptr, deviceId)
    }
    public static fromPtr(ptr: KPointer): BaseEventInternal {
        const obj : BaseEventInternal = new BaseEventInternal()
        obj.peer = new Finalizable(ptr, BaseEventInternal.getFinalizer())
        return obj
    }
}
export interface PixelMapMock {
    release(): void
}
export class PixelMapMockInternal implements MaterializedBase,PixelMapMock {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pixelmapmock(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PixelMapMock_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PixelMapMockInternal.ctor_pixelmapmock()
        this.peer = new Finalizable(ctorPtr, PixelMapMockInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PixelMapMock_getFinalizer()
    }
    public release(): void {
        this.release_serialize()
        return
    }
    private release_serialize(): void {
        ArkUIGeneratedNativeModule._PixelMapMock_release(this.peer!.ptr)
    }
    public static fromPtr(ptr: KPointer): PixelMapMockInternal {
        const obj : PixelMapMockInternal = new PixelMapMockInternal()
        obj.peer = new Finalizable(ptr, PixelMapMockInternal.getFinalizer())
        return obj
    }
}
export interface DragEvent {
    dragBehavior: DragBehavior
    useCustomDropAnimation: boolean
    getDisplayX(): number
    getDisplayY(): number
    getWindowX(): number
    getWindowY(): number
    getX(): number
    getY(): number
    setData(unifiedData: UnifiedData): void
    getData(): UnifiedData
    getSummary(): Summary
    setResult(dragResult: DragResult): void
    getResult(): DragResult
    getPreviewRect(): Rectangle
    getVelocityX(): number
    getVelocityY(): number
    getVelocity(): number
    getModifierKeyState(keys: Array<string>): boolean
}
export class DragEventInternal implements MaterializedBase,DragEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get dragBehavior(): DragBehavior {
        return this.getDragBehavior()
    }
    set dragBehavior(dragBehavior: DragBehavior) {
        this.setDragBehavior(dragBehavior)
    }
    get useCustomDropAnimation(): boolean {
        return this.getUseCustomDropAnimation()
    }
    set useCustomDropAnimation(useCustomDropAnimation: boolean) {
        this.setUseCustomDropAnimation(useCustomDropAnimation)
    }
    static ctor_dragevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = DragEventInternal.ctor_dragevent()
        this.peer = new Finalizable(ctorPtr, DragEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DragEvent_getFinalizer()
    }
    public getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    public getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    public getWindowX(): number {
        return this.getWindowX_serialize()
    }
    public getWindowY(): number {
        return this.getWindowY_serialize()
    }
    public getX(): number {
        return this.getX_serialize()
    }
    public getY(): number {
        return this.getY_serialize()
    }
    public setData(unifiedData: UnifiedData): void {
        const unifiedData_casted = unifiedData as (UnifiedData)
        this.setData_serialize(unifiedData_casted)
        return
    }
    public getData(): UnifiedData {
        return this.getData_serialize()
    }
    public getSummary(): Summary {
        return this.getSummary_serialize()
    }
    public setResult(dragResult: DragResult): void {
        const dragResult_casted = dragResult as (DragResult)
        this.setResult_serialize(dragResult_casted)
        return
    }
    public getResult(): DragResult {
        return this.getResult_serialize()
    }
    public getPreviewRect(): Rectangle {
        return this.getPreviewRect_serialize()
    }
    public getVelocityX(): number {
        return this.getVelocityX_serialize()
    }
    public getVelocityY(): number {
        return this.getVelocityY_serialize()
    }
    public getVelocity(): number {
        return this.getVelocity_serialize()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private getDragBehavior(): DragBehavior {
        return this.getDragBehavior_serialize()
    }
    private setDragBehavior(dragBehavior: DragBehavior): void {
        const dragBehavior_casted = dragBehavior as (DragBehavior)
        this.setDragBehavior_serialize(dragBehavior_casted)
        return
    }
    private getUseCustomDropAnimation(): boolean {
        return this.getUseCustomDropAnimation_serialize()
    }
    private setUseCustomDropAnimation(useCustomDropAnimation: boolean): void {
        const useCustomDropAnimation_casted = useCustomDropAnimation as (boolean)
        this.setUseCustomDropAnimation_serialize(useCustomDropAnimation_casted)
        return
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getX(this.peer!.ptr)
        return retval
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getY(this.peer!.ptr)
        return retval
    }
    private setData_serialize(unifiedData: UnifiedData): void {
        ArkUIGeneratedNativeModule._DragEvent_setData(this.peer!.ptr, toPeerPtr(unifiedData))
    }
    private getData_serialize(): UnifiedData {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getData(this.peer!.ptr)
        const obj : UnifiedData = UnifiedDataInternal.fromPtr(retval)
        return obj
    }
    private getSummary_serialize(): Summary {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getSummary(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : Summary = retvalDeserializer.readSummary()
        return returnResult
    }
    private setResult_serialize(dragResult: DragResult): void {
        ArkUIGeneratedNativeModule._DragEvent_setResult(this.peer!.ptr, TypeChecker.DragResult_ToNumeric(dragResult))
    }
    private getResult_serialize(): DragResult {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getResult(this.peer!.ptr)
        return TypeChecker.DragResult_FromNumeric(retval)
    }
    private getPreviewRect_serialize(): Rectangle {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getPreviewRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : Rectangle = retvalDeserializer.readRectangle()
        return returnResult
    }
    private getVelocityX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private getVelocityY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private getVelocity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getDragBehavior_serialize(): DragBehavior {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getDragBehavior(this.peer!.ptr)
        return TypeChecker.DragBehavior_FromNumeric(retval)
    }
    private setDragBehavior_serialize(dragBehavior: DragBehavior): void {
        ArkUIGeneratedNativeModule._DragEvent_setDragBehavior(this.peer!.ptr, TypeChecker.DragBehavior_ToNumeric(dragBehavior))
    }
    private getUseCustomDropAnimation_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getUseCustomDropAnimation(this.peer!.ptr)
        return retval
    }
    private setUseCustomDropAnimation_serialize(useCustomDropAnimation: boolean): void {
        ArkUIGeneratedNativeModule._DragEvent_setUseCustomDropAnimation(this.peer!.ptr, useCustomDropAnimation ? 1 : 0)
    }
    public static fromPtr(ptr: KPointer): DragEventInternal {
        const obj : DragEventInternal = new DragEventInternal()
        obj.peer = new Finalizable(ptr, DragEventInternal.getFinalizer())
        return obj
    }
}
export interface KeyEvent {
    type: KeyType
    keyCode: number
    keyText: string
    keySource: KeySource
    deviceId: number
    metaKey: number
    timestamp: int64
    stopPropagation: (() => void)
    intentionCode: IntentionCode
    unicode?: number | undefined
    getModifierKeyState(keys: Array<string>): boolean
}
export class KeyEventInternal implements MaterializedBase,KeyEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get type(): KeyType {
        return this.getType()
    }
    set type(type: KeyType) {
        this.setType(type)
    }
    get keyCode(): number {
        return this.getKeyCode()
    }
    set keyCode(keyCode: number) {
        this.setKeyCode(keyCode)
    }
    get keyText(): string {
        return this.getKeyText()
    }
    set keyText(keyText: string) {
        this.setKeyText(keyText)
    }
    get keySource(): KeySource {
        return this.getKeySource()
    }
    set keySource(keySource: KeySource) {
        this.setKeySource(keySource)
    }
    get deviceId(): number {
        return this.getDeviceId()
    }
    set deviceId(deviceId: number) {
        this.setDeviceId(deviceId)
    }
    get metaKey(): number {
        return this.getMetaKey()
    }
    set metaKey(metaKey: number) {
        this.setMetaKey(metaKey)
    }
    get timestamp(): int64 {
        return this.getTimestamp()
    }
    set timestamp(timestamp: int64) {
        this.setTimestamp(timestamp)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    get intentionCode(): IntentionCode {
        return this.getIntentionCode()
    }
    set intentionCode(intentionCode: IntentionCode) {
        this.setIntentionCode(intentionCode)
    }
    get unicode(): number | undefined {
        return this.getUnicode()
    }
    set unicode(unicode: number | undefined) {
        const unicode_NonNull  = (unicode as number)
        this.setUnicode(unicode_NonNull)
    }
    static ctor_keyevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = KeyEventInternal.ctor_keyevent()
        this.peer = new Finalizable(ctorPtr, KeyEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._KeyEvent_getFinalizer()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private getType(): KeyType {
        return this.getType_serialize()
    }
    private setType(type: KeyType): void {
        const type_casted = type as (KeyType)
        this.setType_serialize(type_casted)
        return
    }
    private getKeyCode(): number {
        return this.getKeyCode_serialize()
    }
    private setKeyCode(keyCode: number): void {
        const keyCode_casted = keyCode as (number)
        this.setKeyCode_serialize(keyCode_casted)
        return
    }
    private getKeyText(): string {
        return this.getKeyText_serialize()
    }
    private setKeyText(keyText: string): void {
        const keyText_casted = keyText as (string)
        this.setKeyText_serialize(keyText_casted)
        return
    }
    private getKeySource(): KeySource {
        return this.getKeySource_serialize()
    }
    private setKeySource(keySource: KeySource): void {
        const keySource_casted = keySource as (KeySource)
        this.setKeySource_serialize(keySource_casted)
        return
    }
    private getDeviceId(): number {
        return this.getDeviceId_serialize()
    }
    private setDeviceId(deviceId: number): void {
        const deviceId_casted = deviceId as (number)
        this.setDeviceId_serialize(deviceId_casted)
        return
    }
    private getMetaKey(): number {
        return this.getMetaKey_serialize()
    }
    private setMetaKey(metaKey: number): void {
        const metaKey_casted = metaKey as (number)
        this.setMetaKey_serialize(metaKey_casted)
        return
    }
    private getTimestamp(): int64 {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: int64): void {
        const timestamp_casted = timestamp as (int64)
        this.setTimestamp_serialize(timestamp_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getIntentionCode(): IntentionCode {
        return this.getIntentionCode_serialize()
    }
    private setIntentionCode(intentionCode: IntentionCode): void {
        const intentionCode_casted = intentionCode as (IntentionCode)
        this.setIntentionCode_serialize(intentionCode_casted)
        return
    }
    private getUnicode(): number | undefined {
        return this.getUnicode_serialize()
    }
    private setUnicode(unicode: number): void {
        const unicode_casted = unicode as (number)
        this.setUnicode_serialize(unicode_casted)
        return
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getType_serialize(): KeyType {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getType(this.peer!.ptr)
        return TypeChecker.KeyType_FromNumeric(retval)
    }
    private setType_serialize(type: KeyType): void {
        ArkUIGeneratedNativeModule._KeyEvent_setType(this.peer!.ptr, TypeChecker.KeyType_ToNumeric(type))
    }
    private getKeyCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeyCode(this.peer!.ptr)
        return retval
    }
    private setKeyCode_serialize(keyCode: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeyCode(this.peer!.ptr, keyCode)
    }
    private getKeyText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeyText(this.peer!.ptr)
        return retval
    }
    private setKeyText_serialize(keyText: string): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeyText(this.peer!.ptr, keyText)
    }
    private getKeySource_serialize(): KeySource {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeySource(this.peer!.ptr)
        return TypeChecker.KeySource_FromNumeric(retval)
    }
    private setKeySource_serialize(keySource: KeySource): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeySource(this.peer!.ptr, TypeChecker.KeySource_ToNumeric(keySource))
    }
    private getDeviceId_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getDeviceId(this.peer!.ptr)
        return retval
    }
    private setDeviceId_serialize(deviceId: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setDeviceId(this.peer!.ptr, deviceId)
    }
    private getMetaKey_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getMetaKey(this.peer!.ptr)
        return retval
    }
    private setMetaKey_serialize(metaKey: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setMetaKey(this.peer!.ptr, metaKey)
    }
    private getTimestamp_serialize(): int64 {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: int64): void {
        ArkUIGeneratedNativeModule._KeyEvent_setTimestamp(this.peer!.ptr, timestamp)
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._KeyEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIntentionCode_serialize(): IntentionCode {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getIntentionCode(this.peer!.ptr)
        return TypeChecker.IntentionCode_FromNumeric(retval)
    }
    private setIntentionCode_serialize(intentionCode: IntentionCode): void {
        ArkUIGeneratedNativeModule._KeyEvent_setIntentionCode(this.peer!.ptr, TypeChecker.IntentionCode_ToNumeric(intentionCode))
    }
    private getUnicode_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getUnicode(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setUnicode_serialize(unicode: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setUnicode(this.peer!.ptr, unicode)
    }
    public static fromPtr(ptr: KPointer): KeyEventInternal {
        const obj : KeyEventInternal = new KeyEventInternal()
        obj.peer = new Finalizable(ptr, KeyEventInternal.getFinalizer())
        return obj
    }
}
export class ProgressMaskInternal {
    public static fromPtr(ptr: KPointer): ProgressMask {
        const obj : ProgressMask = new ProgressMask(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ProgressMask.getFinalizer())
        return obj
    }
}
export class ProgressMask implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_progressmask(value: number, total: number, color: ResourceColor): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0 as int32)
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1 as int32)
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2 as int32)
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3 as int32)
            const color_3  = color as Resource
            thisSerializer.writeResource(color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._ProgressMask_ctor(value, total, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: number, total?: number, color?: ResourceColor) {
        if (((value) !== (undefined)) || ((total) !== (undefined)) || ((color) !== (undefined)))
        {
            const ctorPtr : KPointer = ProgressMask.ctor_progressmask((value)!, (total)!, (color)!)
            this.peer = new Finalizable(ctorPtr, ProgressMask.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ProgressMask_getFinalizer()
    }
    public updateProgress(value: number): void {
        const value_casted = value as (number)
        this.updateProgress_serialize(value_casted)
        return
    }
    public updateColor(value: ResourceColor): void {
        const value_casted = value as (ResourceColor)
        this.updateColor_serialize(value_casted)
        return
    }
    public enableBreathingAnimation(value: boolean): void {
        const value_casted = value as (boolean)
        this.enableBreathingAnimation_serialize(value_casted)
        return
    }
    private updateProgress_serialize(value: number): void {
        ArkUIGeneratedNativeModule._ProgressMask_updateProgress(this.peer!.ptr, value)
    }
    private updateColor_serialize(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ProgressMask_updateColor(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private enableBreathingAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._ProgressMask_enableBreathingAnimation(this.peer!.ptr, value ? 1 : 0)
    }
}
export interface Measurable {
    measure(constraint: ConstraintSizeOptions): MeasureResult
    getMargin(): DirectionalEdgesT
    getPadding(): DirectionalEdgesT
    getBorderWidth(): DirectionalEdgesT
}
export class MeasurableInternal implements MaterializedBase,Measurable {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_measurable(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Measurable_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = MeasurableInternal.ctor_measurable()
        this.peer = new Finalizable(ctorPtr, MeasurableInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Measurable_getFinalizer()
    }
    public measure(constraint: ConstraintSizeOptions): MeasureResult {
        const constraint_casted = constraint as (ConstraintSizeOptions)
        return this.measure_serialize(constraint_casted)
    }
    public getMargin(): DirectionalEdgesT {
        return this.getMargin_serialize()
    }
    public getPadding(): DirectionalEdgesT {
        return this.getPadding_serialize()
    }
    public getBorderWidth(): DirectionalEdgesT {
        return this.getBorderWidth_serialize()
    }
    private measure_serialize(constraint: ConstraintSizeOptions): MeasureResult {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(constraint)
        const retval  = ArkUIGeneratedNativeModule._Measurable_measure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : MeasureResult = retvalDeserializer.readMeasureResult()
        return returnResult
    }
    private getMargin_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getMargin(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getPadding_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getPadding(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getBorderWidth_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getBorderWidth(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    public static fromPtr(ptr: KPointer): MeasurableInternal {
        const obj : MeasurableInternal = new MeasurableInternal()
        obj.peer = new Finalizable(ptr, MeasurableInternal.getFinalizer())
        return obj
    }
}
export class ViewInternal {
    public static fromPtr(ptr: KPointer): View {
        const obj : View = new View()
        obj.peer = new Finalizable(ptr, View.getFinalizer())
        return obj
    }
}
export class View implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_view(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._View_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = View.ctor_view()
        this.peer = new Finalizable(ctorPtr, View.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._View_getFinalizer()
    }
    public create(value: KPointer): KPointer {
        const value_casted = value as (KPointer)
        return this.create_serialize(value_casted)
    }
    private create_serialize(value: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._View_create(this.peer!.ptr, value)
        return retval
    }
}
export class TextContentControllerBaseInternal {
    public static fromPtr(ptr: KPointer): TextContentControllerBase {
        const obj : TextContentControllerBase = new TextContentControllerBase()
        obj.peer = new Finalizable(ptr, TextContentControllerBase.getFinalizer())
        return obj
    }
}
export class TextContentControllerBase implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textcontentcontrollerbase(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextContentControllerBase.ctor_textcontentcontrollerbase()
        this.peer = new Finalizable(ctorPtr, TextContentControllerBase.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextContentControllerBase_getFinalizer()
    }
    public getCaretOffset(): CaretOffset {
        return this.getCaretOffset_serialize()
    }
    public getTextContentRect(): RectResult {
        return this.getTextContentRect_serialize()
    }
    public getTextContentLineCount(): number {
        return this.getTextContentLineCount_serialize()
    }
    private getCaretOffset_serialize(): CaretOffset {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getCaretOffset(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : CaretOffset = retvalDeserializer.readCaretOffset()
        return returnResult
    }
    private getTextContentRect_serialize(): RectResult {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private getTextContentLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentLineCount(this.peer!.ptr)
        return retval
    }
}
export class ChildrenMainSizeInternal {
    public static fromPtr(ptr: KPointer): ChildrenMainSize {
        const obj : ChildrenMainSize = new ChildrenMainSize(undefined)
        obj.peer = new Finalizable(ptr, ChildrenMainSize.getFinalizer())
        return obj
    }
}
export class ChildrenMainSize implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get childDefaultSize(): number {
        return this.getChildDefaultSize()
    }
    set childDefaultSize(childDefaultSize: number) {
        this.setChildDefaultSize(childDefaultSize)
    }
    static ctor_childrenmainsize(childDefaultSize: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ChildrenMainSize_ctor(childDefaultSize)
        return retval
    }
    constructor(childDefaultSize?: number) {
        if ((childDefaultSize) !== (undefined))
        {
            const ctorPtr : KPointer = ChildrenMainSize.ctor_childrenmainsize((childDefaultSize)!)
            this.peer = new Finalizable(ctorPtr, ChildrenMainSize.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ChildrenMainSize_getFinalizer()
    }
    public splice(start: number, deleteCount?: number, childrenSize?: Array<number>): void {
        const start_casted = start as (number)
        const deleteCount_casted = deleteCount as (number | undefined)
        const childrenSize_casted = childrenSize as (Array<number> | undefined)
        this.splice_serialize(start_casted, deleteCount_casted, childrenSize_casted)
        return
    }
    public update(index: number, childSize: number): void {
        const index_casted = index as (number)
        const childSize_casted = childSize as (number)
        this.update_serialize(index_casted, childSize_casted)
        return
    }
    private getChildDefaultSize(): number {
        return this.getChildDefaultSize_serialize()
    }
    private setChildDefaultSize(childDefaultSize: number): void {
        const childDefaultSize_casted = childDefaultSize as (number)
        this.setChildDefaultSize_serialize(childDefaultSize_casted)
        return
    }
    private splice_serialize(start: number, deleteCount?: number, childrenSize?: Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let deleteCount_type : int32 = RuntimeType.UNDEFINED
        deleteCount_type = runtimeType(deleteCount)
        thisSerializer.writeInt8(deleteCount_type as int32)
        if ((RuntimeType.UNDEFINED) != (deleteCount_type)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let childrenSize_type : int32 = RuntimeType.UNDEFINED
        childrenSize_type = runtimeType(childrenSize)
        thisSerializer.writeInt8(childrenSize_type as int32)
        if ((RuntimeType.UNDEFINED) != (childrenSize_type)) {
            const childrenSize_value  = childrenSize!
            thisSerializer.writeInt32(childrenSize_value.length as int32)
            for (let i = 0; i < childrenSize_value.length; i++) {
                const childrenSize_value_element : number = childrenSize_value[i]
                thisSerializer.writeNumber(childrenSize_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ChildrenMainSize_splice(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private update_serialize(index: number, childSize: number): void {
        ArkUIGeneratedNativeModule._ChildrenMainSize_update(this.peer!.ptr, index, childSize)
    }
    private getChildDefaultSize_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ChildrenMainSize_getChildDefaultSize(this.peer!.ptr)
        return retval
    }
    private setChildDefaultSize_serialize(childDefaultSize: number): void {
        ArkUIGeneratedNativeModule._ChildrenMainSize_setChildDefaultSize(this.peer!.ptr, childDefaultSize)
    }
}
export interface UICommonEvent {
    setOnClick(callback_: ((event: ClickEvent) => void) | undefined): void
    setOnTouch(callback_: ((event: TouchEvent) => void) | undefined): void
    setOnAppear(callback_: (() => void) | undefined): void
    setOnDisappear(callback_: (() => void) | undefined): void
    setOnKeyEvent(callback_: ((event: KeyEvent) => void) | undefined): void
    setOnFocus(callback_: (() => void) | undefined): void
    setOnBlur(callback_: (() => void) | undefined): void
    setOnHover(callback_: HoverCallback | undefined): void
    setOnMouse(callback_: ((event: MouseEvent) => void) | undefined): void
    setOnSizeChange(callback_: SizeChangeCallback | undefined): void
    setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): void
}
export class UICommonEventInternal implements MaterializedBase,UICommonEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uicommonevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UICommonEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UICommonEventInternal.ctor_uicommonevent()
        this.peer = new Finalizable(ctorPtr, UICommonEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UICommonEvent_getFinalizer()
    }
    public setOnClick(callback_: ((event: ClickEvent) => void) | undefined): void {
        const callback__casted = callback_ as (((event: ClickEvent) => void) | undefined)
        this.setOnClick_serialize(callback__casted)
        return
    }
    public setOnTouch(callback_: ((event: TouchEvent) => void) | undefined): void {
        const callback__casted = callback_ as (((event: TouchEvent) => void) | undefined)
        this.setOnTouch_serialize(callback__casted)
        return
    }
    public setOnAppear(callback_: (() => void) | undefined): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnAppear_serialize(callback__casted)
        return
    }
    public setOnDisappear(callback_: (() => void) | undefined): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnDisappear_serialize(callback__casted)
        return
    }
    public setOnKeyEvent(callback_: ((event: KeyEvent) => void) | undefined): void {
        const callback__casted = callback_ as (((event: KeyEvent) => void) | undefined)
        this.setOnKeyEvent_serialize(callback__casted)
        return
    }
    public setOnFocus(callback_: (() => void) | undefined): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnFocus_serialize(callback__casted)
        return
    }
    public setOnBlur(callback_: (() => void) | undefined): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnBlur_serialize(callback__casted)
        return
    }
    public setOnHover(callback_: HoverCallback | undefined): void {
        const callback__casted = callback_ as (HoverCallback | undefined)
        this.setOnHover_serialize(callback__casted)
        return
    }
    public setOnMouse(callback_: ((event: MouseEvent) => void) | undefined): void {
        const callback__casted = callback_ as (((event: MouseEvent) => void) | undefined)
        this.setOnMouse_serialize(callback__casted)
        return
    }
    public setOnSizeChange(callback_: SizeChangeCallback | undefined): void {
        const callback__casted = callback_ as (SizeChangeCallback | undefined)
        this.setOnSizeChange_serialize(callback__casted)
        return
    }
    public setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): void {
        const options_casted = options as (VisibleAreaEventOptions)
        const event_casted = event as (VisibleAreaChangeCallback | undefined)
        this.setOnVisibleAreaApproximateChange_serialize(options_casted, event_casted)
        return
    }
    private setOnClick_serialize(callback_: ((event: ClickEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnClick(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnTouch_serialize(callback_: ((event: TouchEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnTouch(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnAppear_serialize(callback_: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnAppear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnDisappear_serialize(callback_: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnDisappear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnKeyEvent_serialize(callback_: ((event: KeyEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnKeyEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnFocus_serialize(callback_: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnFocus(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnBlur_serialize(callback_: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnBlur(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnHover_serialize(callback_: HoverCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnHover(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnMouse_serialize(callback_: ((event: MouseEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnMouse(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnSizeChange_serialize(callback_: SizeChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnSizeChange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnVisibleAreaApproximateChange_serialize(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVisibleAreaEventOptions(options)
        let event_type : int32 = RuntimeType.UNDEFINED
        event_type = runtimeType(event)
        thisSerializer.writeInt8(event_type as int32)
        if ((RuntimeType.UNDEFINED) != (event_type)) {
            const event_value  = event!
            thisSerializer.holdAndWriteCallback(event_value)
        }
        ArkUIGeneratedNativeModule._UICommonEvent_setOnVisibleAreaApproximateChange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UICommonEventInternal {
        const obj : UICommonEventInternal = new UICommonEventInternal()
        obj.peer = new Finalizable(ptr, UICommonEventInternal.getFinalizer())
        return obj
    }
}
export interface GestureModifier {
    applyGesture(event: UIGestureEvent): void
}
export class GestureModifierInternal implements MaterializedBase,GestureModifier {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturemodifier(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureModifier_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = GestureModifierInternal.ctor_gesturemodifier()
        this.peer = new Finalizable(ctorPtr, GestureModifierInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureModifier_getFinalizer()
    }
    public applyGesture(event: UIGestureEvent): void {
        const event_casted = event as (UIGestureEvent)
        this.applyGesture_serialize(event_casted)
        return
    }
    private applyGesture_serialize(event: UIGestureEvent): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeUIGestureEvent(event)
        ArkUIGeneratedNativeModule._GestureModifier_applyGesture(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): GestureModifierInternal {
        const obj : GestureModifierInternal = new GestureModifierInternal()
        obj.peer = new Finalizable(ptr, GestureModifierInternal.getFinalizer())
        return obj
    }
}
export class ArkCommonMethodPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CommonMethod_construct(peerId, flags)
        const _peer  = new ArkCommonMethodPeer(_peerPtr, peerId, "CommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    widthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_width(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_height(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    drawModifierAttribute(value: DrawModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDrawModifier(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_drawModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    responseRegionAttribute(value: Array<Rectangle> | Rectangle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_Rectangle(value))) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Array<Rectangle>
            thisSerializer.writeInt32(value_0.length as int32)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element : Rectangle = value_0[i]
                thisSerializer.writeRectangle(value_0_element)
            }
        }
        else if (TypeChecker.isRectangle(value, false, false, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Rectangle
            thisSerializer.writeRectangle(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_responseRegion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mouseResponseRegionAttribute(value: Array<Rectangle> | Rectangle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_Rectangle(value))) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Array<Rectangle>
            thisSerializer.writeInt32(value_0.length as int32)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element : Rectangle = value_0[i]
                thisSerializer.writeRectangle(value_0_element)
            }
        }
        else if (TypeChecker.isRectangle(value, false, false, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Rectangle
            thisSerializer.writeRectangle(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mouseResponseRegion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_constraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    touchableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_touchable(this.peer.ptr, value ? 1 : 0)
    }
    hitTestBehaviorAttribute(value: HitTestMode): void {
        ArkUIGeneratedNativeModule._CommonMethod_hitTestBehavior(this.peer.ptr, TypeChecker.HitTestMode_ToNumeric(value))
    }
    onChildTouchTestAttribute(value: ((value: Array<TouchTestInfo>) => TouchResult)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onChildTouchTest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutWeightAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_layoutWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainWeightAttribute(value: ChainWeightOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeChainWeightOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_chainWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Length | LocalizedPadding): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPadding(value, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Padding
            const value_0_top  = value_0.top
            let value_0_top_type : int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value  = value_0_top!
                let value_0_top_value_type : int32 = RuntimeType.UNDEFINED
                value_0_top_value_type = runtimeType(value_0_top_value)
                if (RuntimeType.STRING == value_0_top_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_top_value_0  = value_0_top_value as string
                    thisSerializer.writeString(value_0_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_top_value_1  = value_0_top_value as number
                    thisSerializer.writeNumber(value_0_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_top_value_2  = value_0_top_value as Resource
                    thisSerializer.writeResource(value_0_top_value_2)
                }
            }
            const value_0_right  = value_0.right
            let value_0_right_type : int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value  = value_0_right!
                let value_0_right_value_type : int32 = RuntimeType.UNDEFINED
                value_0_right_value_type = runtimeType(value_0_right_value)
                if (RuntimeType.STRING == value_0_right_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_right_value_0  = value_0_right_value as string
                    thisSerializer.writeString(value_0_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_right_value_1  = value_0_right_value as number
                    thisSerializer.writeNumber(value_0_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_right_value_2  = value_0_right_value as Resource
                    thisSerializer.writeResource(value_0_right_value_2)
                }
            }
            const value_0_bottom  = value_0.bottom
            let value_0_bottom_type : int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value  = value_0_bottom!
                let value_0_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_0_bottom_value_type = runtimeType(value_0_bottom_value)
                if (RuntimeType.STRING == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_bottom_value_0  = value_0_bottom_value as string
                    thisSerializer.writeString(value_0_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_bottom_value_1  = value_0_bottom_value as number
                    thisSerializer.writeNumber(value_0_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_bottom_value_2  = value_0_bottom_value as Resource
                    thisSerializer.writeResource(value_0_bottom_value_2)
                }
            }
            const value_0_left  = value_0.left
            let value_0_left_type : int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value  = value_0_left!
                let value_0_left_value_type : int32 = RuntimeType.UNDEFINED
                value_0_left_value_type = runtimeType(value_0_left_value)
                if (RuntimeType.STRING == value_0_left_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_left_value_0  = value_0_left_value as string
                    thisSerializer.writeString(value_0_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_left_value_1  = value_0_left_value as number
                    thisSerializer.writeNumber(value_0_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_left_value_2  = value_0_left_value as Resource
                    thisSerializer.writeResource(value_0_left_value_2)
                }
            }
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Length
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.NUMBER == value_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_1  = value_1 as number
                thisSerializer.writeNumber(value_1_1)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_1_2  = value_1 as Resource
                thisSerializer.writeResource(value_1_2)
            }
        }
        else if (TypeChecker.isLocalizedPadding(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedPadding
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    safeAreaPaddingAttribute(value: Padding | LengthMetrics | LocalizedPadding): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPadding(value, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Padding
            const value_0_top  = value_0.top
            let value_0_top_type : int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value  = value_0_top!
                let value_0_top_value_type : int32 = RuntimeType.UNDEFINED
                value_0_top_value_type = runtimeType(value_0_top_value)
                if (RuntimeType.STRING == value_0_top_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_top_value_0  = value_0_top_value as string
                    thisSerializer.writeString(value_0_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_top_value_1  = value_0_top_value as number
                    thisSerializer.writeNumber(value_0_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_top_value_2  = value_0_top_value as Resource
                    thisSerializer.writeResource(value_0_top_value_2)
                }
            }
            const value_0_right  = value_0.right
            let value_0_right_type : int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value  = value_0_right!
                let value_0_right_value_type : int32 = RuntimeType.UNDEFINED
                value_0_right_value_type = runtimeType(value_0_right_value)
                if (RuntimeType.STRING == value_0_right_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_right_value_0  = value_0_right_value as string
                    thisSerializer.writeString(value_0_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_right_value_1  = value_0_right_value as number
                    thisSerializer.writeNumber(value_0_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_right_value_2  = value_0_right_value as Resource
                    thisSerializer.writeResource(value_0_right_value_2)
                }
            }
            const value_0_bottom  = value_0.bottom
            let value_0_bottom_type : int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value  = value_0_bottom!
                let value_0_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_0_bottom_value_type = runtimeType(value_0_bottom_value)
                if (RuntimeType.STRING == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_bottom_value_0  = value_0_bottom_value as string
                    thisSerializer.writeString(value_0_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_bottom_value_1  = value_0_bottom_value as number
                    thisSerializer.writeNumber(value_0_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_bottom_value_2  = value_0_bottom_value as Resource
                    thisSerializer.writeResource(value_0_bottom_value_2)
                }
            }
            const value_0_left  = value_0.left
            let value_0_left_type : int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value  = value_0_left!
                let value_0_left_value_type : int32 = RuntimeType.UNDEFINED
                value_0_left_value_type = runtimeType(value_0_left_value)
                if (RuntimeType.STRING == value_0_left_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_left_value_0  = value_0_left_value as string
                    thisSerializer.writeString(value_0_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_left_value_1  = value_0_left_value as number
                    thisSerializer.writeNumber(value_0_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_left_value_2  = value_0_left_value as Resource
                    thisSerializer.writeResource(value_0_left_value_2)
                }
            }
        }
        else if (TypeChecker.isLengthMetrics(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as LengthMetrics
            thisSerializer.writeLengthMetrics(value_1)
        }
        else if (TypeChecker.isLocalizedPadding(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedPadding
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_safeAreaPadding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    marginAttribute(value: Padding | Length | LocalizedPadding): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isPadding(value, true, false, true, false))) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Padding
            const value_0_top  = value_0.top
            let value_0_top_type : int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value  = value_0_top!
                let value_0_top_value_type : int32 = RuntimeType.UNDEFINED
                value_0_top_value_type = runtimeType(value_0_top_value)
                if (RuntimeType.STRING == value_0_top_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_top_value_0  = value_0_top_value as string
                    thisSerializer.writeString(value_0_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_top_value_1  = value_0_top_value as number
                    thisSerializer.writeNumber(value_0_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_top_value_2  = value_0_top_value as Resource
                    thisSerializer.writeResource(value_0_top_value_2)
                }
            }
            const value_0_right  = value_0.right
            let value_0_right_type : int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value  = value_0_right!
                let value_0_right_value_type : int32 = RuntimeType.UNDEFINED
                value_0_right_value_type = runtimeType(value_0_right_value)
                if (RuntimeType.STRING == value_0_right_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_right_value_0  = value_0_right_value as string
                    thisSerializer.writeString(value_0_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_right_value_1  = value_0_right_value as number
                    thisSerializer.writeNumber(value_0_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_right_value_2  = value_0_right_value as Resource
                    thisSerializer.writeResource(value_0_right_value_2)
                }
            }
            const value_0_bottom  = value_0.bottom
            let value_0_bottom_type : int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value  = value_0_bottom!
                let value_0_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_0_bottom_value_type = runtimeType(value_0_bottom_value)
                if (RuntimeType.STRING == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_bottom_value_0  = value_0_bottom_value as string
                    thisSerializer.writeString(value_0_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_bottom_value_1  = value_0_bottom_value as number
                    thisSerializer.writeNumber(value_0_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_bottom_value_2  = value_0_bottom_value as Resource
                    thisSerializer.writeResource(value_0_bottom_value_2)
                }
            }
            const value_0_left  = value_0.left
            let value_0_left_type : int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value  = value_0_left!
                let value_0_left_value_type : int32 = RuntimeType.UNDEFINED
                value_0_left_value_type = runtimeType(value_0_left_value)
                if (RuntimeType.STRING == value_0_left_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_0_left_value_0  = value_0_left_value as string
                    thisSerializer.writeString(value_0_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_0_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_0_left_value_1  = value_0_left_value as number
                    thisSerializer.writeNumber(value_0_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_0_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_0_left_value_2  = value_0_left_value as Resource
                    thisSerializer.writeResource(value_0_left_value_2)
                }
            }
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Length
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.NUMBER == value_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_1  = value_1 as number
                thisSerializer.writeNumber(value_1_1)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_1_2  = value_1 as Resource
                thisSerializer.writeResource(value_1_2)
            }
        }
        else if (TypeChecker.isLocalizedPadding(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedPadding
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_margin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pixelRoundAttribute(value: PixelRoundPolicy): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePixelRoundPolicy(value)
        ArkUIGeneratedNativeModule._CommonMethod_pixelRound(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageSizeAttribute(value: SizeOptions | ImageSize): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as SizeOptions
            thisSerializer.writeSizeOptions(value_0)
        }
        else if (TypeChecker.isImageSize(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ImageSize
            thisSerializer.writeInt32(TypeChecker.ImageSize_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImagePositionAttribute(value: Position | Alignment): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isAlignment(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Alignment
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImagePosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundEffectAttribute(value: BackgroundEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBackgroundEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageResizableAttribute(value: ResizableOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResizableOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageResizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundEffectAttribute(value: ForegroundEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeForegroundEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_foregroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visualEffectAttribute(value: VisualEffect): void {
        ArkUIGeneratedNativeModule._CommonMethod_visualEffect(this.peer.ptr, toPeerPtr(value))
    }
    backgroundFilterAttribute(value: Filter): void {
        ArkUIGeneratedNativeModule._CommonMethod_backgroundFilter(this.peer.ptr, toPeerPtr(value))
    }
    foregroundFilterAttribute(value: Filter): void {
        ArkUIGeneratedNativeModule._CommonMethod_foregroundFilter(this.peer.ptr, toPeerPtr(value))
    }
    compositingFilterAttribute(value: Filter): void {
        ArkUIGeneratedNativeModule._CommonMethod_compositingFilter(this.peer.ptr, toPeerPtr(value))
    }
    opacityAttribute(value: number | Resource): void {
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
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_opacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderAttribute(value: BorderOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBorderOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_border(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle | EdgeStyles): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isBorderStyle(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as BorderStyle
            thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_0))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeStyles
            thisSerializer.writeEdgeStyles(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderWidthAttribute(value: Length | EdgeWidths | LocalizedEdgeWidths): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Length
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isEdgeWidths(value, true, false, true, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeWidths
            const value_1_top  = value_1.top
            let value_1_top_type : int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value  = value_1_top!
                let value_1_top_value_type : int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_top_value_0  = value_1_top_value as string
                    thisSerializer.writeString(value_1_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_top_value_1  = value_1_top_value as number
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_top_value_2  = value_1_top_value as Resource
                    thisSerializer.writeResource(value_1_top_value_2)
                }
            }
            const value_1_right  = value_1.right
            let value_1_right_type : int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value  = value_1_right!
                let value_1_right_value_type : int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_right_value_0  = value_1_right_value as string
                    thisSerializer.writeString(value_1_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_right_value_1  = value_1_right_value as number
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_right_value_2  = value_1_right_value as Resource
                    thisSerializer.writeResource(value_1_right_value_2)
                }
            }
            const value_1_bottom  = value_1.bottom
            let value_1_bottom_type : int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value  = value_1_bottom!
                let value_1_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottom_value_0  = value_1_bottom_value as string
                    thisSerializer.writeString(value_1_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottom_value_1  = value_1_bottom_value as number
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottom_value_2  = value_1_bottom_value as Resource
                    thisSerializer.writeResource(value_1_bottom_value_2)
                }
            }
            const value_1_left  = value_1.left
            let value_1_left_type : int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value  = value_1_left!
                let value_1_left_value_type : int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_left_value_0  = value_1_left_value as string
                    thisSerializer.writeString(value_1_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_left_value_1  = value_1_left_value as number
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_left_value_2  = value_1_left_value as Resource
                    thisSerializer.writeResource(value_1_left_value_2)
                }
            }
        }
        else if (TypeChecker.isLocalizedEdgeWidths(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdgeWidths
            thisSerializer.writeLocalizedEdgeWidths(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors): void {
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
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0_0))
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
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isEdgeColors(value, true, false, true, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeColors
            const value_1_top  = value_1.top
            let value_1_top_type : int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value  = value_1_top!
                let value_1_top_value_type : int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (TypeChecker.isColor(value_1_top_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_top_value_0  = value_1_top_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_top_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_top_value_1  = value_1_top_value as number
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_top_value_2  = value_1_top_value as string
                    thisSerializer.writeString(value_1_top_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_top_value_3  = value_1_top_value as Resource
                    thisSerializer.writeResource(value_1_top_value_3)
                }
            }
            const value_1_right  = value_1.right
            let value_1_right_type : int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value  = value_1_right!
                let value_1_right_value_type : int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (TypeChecker.isColor(value_1_right_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_right_value_0  = value_1_right_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_right_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_right_value_1  = value_1_right_value as number
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_right_value_2  = value_1_right_value as string
                    thisSerializer.writeString(value_1_right_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_right_value_3  = value_1_right_value as Resource
                    thisSerializer.writeResource(value_1_right_value_3)
                }
            }
            const value_1_bottom  = value_1.bottom
            let value_1_bottom_type : int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value  = value_1_bottom!
                let value_1_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (TypeChecker.isColor(value_1_bottom_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottom_value_0  = value_1_bottom_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_bottom_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottom_value_1  = value_1_bottom_value as number
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottom_value_2  = value_1_bottom_value as string
                    thisSerializer.writeString(value_1_bottom_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_bottom_value_3  = value_1_bottom_value as Resource
                    thisSerializer.writeResource(value_1_bottom_value_3)
                }
            }
            const value_1_left  = value_1.left
            let value_1_left_type : int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value  = value_1_left!
                let value_1_left_value_type : int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (TypeChecker.isColor(value_1_left_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_left_value_0  = value_1_left_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_left_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_left_value_1  = value_1_left_value as number
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_left_value_2  = value_1_left_value as string
                    thisSerializer.writeString(value_1_left_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_left_value_3  = value_1_left_value as Resource
                    thisSerializer.writeResource(value_1_left_value_3)
                }
            }
        }
        else if (TypeChecker.isLocalizedEdgeColors(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdgeColors
            thisSerializer.writeLocalizedEdgeColors(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Length | BorderRadiuses | LocalizedBorderRadiuses): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Length
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isBorderRadiuses(value, false, false, false, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as BorderRadiuses
            const value_1_topLeft  = value_1.topLeft
            let value_1_topLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_topLeft_type = runtimeType(value_1_topLeft)
            thisSerializer.writeInt8(value_1_topLeft_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_topLeft_type)) {
                const value_1_topLeft_value  = value_1_topLeft!
                let value_1_topLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topLeft_value_type = runtimeType(value_1_topLeft_value)
                if (RuntimeType.STRING == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_topLeft_value_0  = value_1_topLeft_value as string
                    thisSerializer.writeString(value_1_topLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_topLeft_value_1  = value_1_topLeft_value as number
                    thisSerializer.writeNumber(value_1_topLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_topLeft_value_2  = value_1_topLeft_value as Resource
                    thisSerializer.writeResource(value_1_topLeft_value_2)
                }
            }
            const value_1_topRight  = value_1.topRight
            let value_1_topRight_type : int32 = RuntimeType.UNDEFINED
            value_1_topRight_type = runtimeType(value_1_topRight)
            thisSerializer.writeInt8(value_1_topRight_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_topRight_type)) {
                const value_1_topRight_value  = value_1_topRight!
                let value_1_topRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topRight_value_type = runtimeType(value_1_topRight_value)
                if (RuntimeType.STRING == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_topRight_value_0  = value_1_topRight_value as string
                    thisSerializer.writeString(value_1_topRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_topRight_value_1  = value_1_topRight_value as number
                    thisSerializer.writeNumber(value_1_topRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_topRight_value_2  = value_1_topRight_value as Resource
                    thisSerializer.writeResource(value_1_topRight_value_2)
                }
            }
            const value_1_bottomLeft  = value_1.bottomLeft
            let value_1_bottomLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomLeft_type = runtimeType(value_1_bottomLeft)
            thisSerializer.writeInt8(value_1_bottomLeft_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomLeft_type)) {
                const value_1_bottomLeft_value  = value_1_bottomLeft!
                let value_1_bottomLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomLeft_value_type = runtimeType(value_1_bottomLeft_value)
                if (RuntimeType.STRING == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottomLeft_value_0  = value_1_bottomLeft_value as string
                    thisSerializer.writeString(value_1_bottomLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottomLeft_value_1  = value_1_bottomLeft_value as number
                    thisSerializer.writeNumber(value_1_bottomLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottomLeft_value_2  = value_1_bottomLeft_value as Resource
                    thisSerializer.writeResource(value_1_bottomLeft_value_2)
                }
            }
            const value_1_bottomRight  = value_1.bottomRight
            let value_1_bottomRight_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomRight_type = runtimeType(value_1_bottomRight)
            thisSerializer.writeInt8(value_1_bottomRight_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomRight_type)) {
                const value_1_bottomRight_value  = value_1_bottomRight!
                let value_1_bottomRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomRight_value_type = runtimeType(value_1_bottomRight_value)
                if (RuntimeType.STRING == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottomRight_value_0  = value_1_bottomRight_value as string
                    thisSerializer.writeString(value_1_bottomRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottomRight_value_1  = value_1_bottomRight_value as number
                    thisSerializer.writeNumber(value_1_bottomRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottomRight_value_2  = value_1_bottomRight_value as Resource
                    thisSerializer.writeResource(value_1_bottomRight_value_2)
                }
            }
        }
        else if (TypeChecker.isLocalizedBorderRadiuses(value, false, false, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedBorderRadiuses
            thisSerializer.writeLocalizedBorderRadiuses(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderImageAttribute(value: BorderImageOption): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBorderImageOption(value)
        ArkUIGeneratedNativeModule._CommonMethod_borderImage(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineAttribute(value: OutlineOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeOutlineOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_outline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineStyleAttribute(value: OutlineStyle | EdgeOutlineStyles): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isOutlineStyle(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as OutlineStyle
            thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_0))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeOutlineStyles
            const value_1_top  = value_1.top
            let value_1_top_type : int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value  = (value_1_top as OutlineStyle)
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_1_top_value))
            }
            const value_1_right  = value_1.right
            let value_1_right_type : int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value  = (value_1_right as OutlineStyle)
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_1_right_value))
            }
            const value_1_bottom  = value_1.bottom
            let value_1_bottom_type : int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value  = (value_1_bottom as OutlineStyle)
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_1_bottom_value))
            }
            const value_1_left  = value_1.left
            let value_1_left_type : int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value  = (value_1_left as OutlineStyle)
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_1_left_value))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineWidthAttribute(value: Dimension | EdgeOutlineWidths): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Dimension
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isEdgeOutlineWidths(value, false, false, false, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeOutlineWidths
            const value_1_top  = value_1.top
            let value_1_top_type : int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value  = value_1_top!
                let value_1_top_value_type : int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_top_value_0  = value_1_top_value as string
                    thisSerializer.writeString(value_1_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_top_value_1  = value_1_top_value as number
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_top_value_2  = value_1_top_value as Resource
                    thisSerializer.writeResource(value_1_top_value_2)
                }
            }
            const value_1_right  = value_1.right
            let value_1_right_type : int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value  = value_1_right!
                let value_1_right_value_type : int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_right_value_0  = value_1_right_value as string
                    thisSerializer.writeString(value_1_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_right_value_1  = value_1_right_value as number
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_right_value_2  = value_1_right_value as Resource
                    thisSerializer.writeResource(value_1_right_value_2)
                }
            }
            const value_1_bottom  = value_1.bottom
            let value_1_bottom_type : int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value  = value_1_bottom!
                let value_1_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottom_value_0  = value_1_bottom_value as string
                    thisSerializer.writeString(value_1_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottom_value_1  = value_1_bottom_value as number
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottom_value_2  = value_1_bottom_value as Resource
                    thisSerializer.writeResource(value_1_bottom_value_2)
                }
            }
            const value_1_left  = value_1.left
            let value_1_left_type : int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value  = value_1_left!
                let value_1_left_value_type : int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_left_value_0  = value_1_left_value as string
                    thisSerializer.writeString(value_1_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_left_value_1  = value_1_left_value as number
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_left_value_2  = value_1_left_value as Resource
                    thisSerializer.writeResource(value_1_left_value_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors): void {
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
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0_0))
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
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isEdgeColors(value, true, false, true, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EdgeColors
            const value_1_top  = value_1.top
            let value_1_top_type : int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value  = value_1_top!
                let value_1_top_value_type : int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (TypeChecker.isColor(value_1_top_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_top_value_0  = value_1_top_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_top_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_top_value_1  = value_1_top_value as number
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_top_value_2  = value_1_top_value as string
                    thisSerializer.writeString(value_1_top_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_top_value_3  = value_1_top_value as Resource
                    thisSerializer.writeResource(value_1_top_value_3)
                }
            }
            const value_1_right  = value_1.right
            let value_1_right_type : int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value  = value_1_right!
                let value_1_right_value_type : int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (TypeChecker.isColor(value_1_right_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_right_value_0  = value_1_right_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_right_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_right_value_1  = value_1_right_value as number
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_right_value_2  = value_1_right_value as string
                    thisSerializer.writeString(value_1_right_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_right_value_3  = value_1_right_value as Resource
                    thisSerializer.writeResource(value_1_right_value_3)
                }
            }
            const value_1_bottom  = value_1.bottom
            let value_1_bottom_type : int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value  = value_1_bottom!
                let value_1_bottom_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (TypeChecker.isColor(value_1_bottom_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottom_value_0  = value_1_bottom_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_bottom_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottom_value_1  = value_1_bottom_value as number
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottom_value_2  = value_1_bottom_value as string
                    thisSerializer.writeString(value_1_bottom_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_bottom_value_3  = value_1_bottom_value as Resource
                    thisSerializer.writeResource(value_1_bottom_value_3)
                }
            }
            const value_1_left  = value_1.left
            let value_1_left_type : int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value  = value_1_left!
                let value_1_left_value_type : int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (TypeChecker.isColor(value_1_left_value)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_left_value_0  = value_1_left_value as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_1_left_value_0))
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_left_value_1  = value_1_left_value as number
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_left_value_2  = value_1_left_value as string
                    thisSerializer.writeString(value_1_left_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_1_left_value_3  = value_1_left_value as Resource
                    thisSerializer.writeResource(value_1_left_value_3)
                }
            }
        }
        else if (TypeChecker.isLocalizedEdgeColors(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdgeColors
            thisSerializer.writeLocalizedEdgeColors(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineRadiusAttribute(value: Dimension | OutlineRadiuses): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Dimension
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isOutlineRadiuses(value, false, false, false, false))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as OutlineRadiuses
            const value_1_topLeft  = value_1.topLeft
            let value_1_topLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_topLeft_type = runtimeType(value_1_topLeft)
            thisSerializer.writeInt8(value_1_topLeft_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_topLeft_type)) {
                const value_1_topLeft_value  = value_1_topLeft!
                let value_1_topLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topLeft_value_type = runtimeType(value_1_topLeft_value)
                if (RuntimeType.STRING == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_topLeft_value_0  = value_1_topLeft_value as string
                    thisSerializer.writeString(value_1_topLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_topLeft_value_1  = value_1_topLeft_value as number
                    thisSerializer.writeNumber(value_1_topLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_topLeft_value_2  = value_1_topLeft_value as Resource
                    thisSerializer.writeResource(value_1_topLeft_value_2)
                }
            }
            const value_1_topRight  = value_1.topRight
            let value_1_topRight_type : int32 = RuntimeType.UNDEFINED
            value_1_topRight_type = runtimeType(value_1_topRight)
            thisSerializer.writeInt8(value_1_topRight_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_topRight_type)) {
                const value_1_topRight_value  = value_1_topRight!
                let value_1_topRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topRight_value_type = runtimeType(value_1_topRight_value)
                if (RuntimeType.STRING == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_topRight_value_0  = value_1_topRight_value as string
                    thisSerializer.writeString(value_1_topRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_topRight_value_1  = value_1_topRight_value as number
                    thisSerializer.writeNumber(value_1_topRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_topRight_value_2  = value_1_topRight_value as Resource
                    thisSerializer.writeResource(value_1_topRight_value_2)
                }
            }
            const value_1_bottomLeft  = value_1.bottomLeft
            let value_1_bottomLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomLeft_type = runtimeType(value_1_bottomLeft)
            thisSerializer.writeInt8(value_1_bottomLeft_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomLeft_type)) {
                const value_1_bottomLeft_value  = value_1_bottomLeft!
                let value_1_bottomLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomLeft_value_type = runtimeType(value_1_bottomLeft_value)
                if (RuntimeType.STRING == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottomLeft_value_0  = value_1_bottomLeft_value as string
                    thisSerializer.writeString(value_1_bottomLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottomLeft_value_1  = value_1_bottomLeft_value as number
                    thisSerializer.writeNumber(value_1_bottomLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottomLeft_value_2  = value_1_bottomLeft_value as Resource
                    thisSerializer.writeResource(value_1_bottomLeft_value_2)
                }
            }
            const value_1_bottomRight  = value_1.bottomRight
            let value_1_bottomRight_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomRight_type = runtimeType(value_1_bottomRight)
            thisSerializer.writeInt8(value_1_bottomRight_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomRight_type)) {
                const value_1_bottomRight_value  = value_1_bottomRight!
                let value_1_bottomRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomRight_value_type = runtimeType(value_1_bottomRight_value)
                if (RuntimeType.STRING == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_1_bottomRight_value_0  = value_1_bottomRight_value as string
                    thisSerializer.writeString(value_1_bottomRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_1_bottomRight_value_1  = value_1_bottomRight_value as number
                    thisSerializer.writeNumber(value_1_bottomRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_1_bottomRight_value_2  = value_1_bottomRight_value as Resource
                    thisSerializer.writeResource(value_1_bottomRight_value_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundColorAttribute(value: ResourceColor | ColoringStrategy): void {
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
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0_0))
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
        else if (TypeChecker.isColoringStrategy(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ColoringStrategy
            thisSerializer.writeInt32(TypeChecker.ColoringStrategy_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick0Attribute(value: ((event: ClickEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onClick0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick1Attribute(event: ((event: ClickEvent) => void), distanceThreshold: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._CommonMethod_onClick1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), distanceThreshold)
        thisSerializer.release()
    }
    onHoverAttribute(value: ((isHover: boolean,event: HoverEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onHover(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAccessibilityHoverAttribute(value: AccessibilityCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAccessibilityHover(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hoverEffectAttribute(value: HoverEffect): void {
        ArkUIGeneratedNativeModule._CommonMethod_hoverEffect(this.peer.ptr, TypeChecker.HoverEffect_ToNumeric(value))
    }
    onMouseAttribute(value: ((event: MouseEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onMouse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchAttribute(value: ((event: TouchEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onTouch(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyEventAttribute(value: ((event: KeyEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyPreImeAttribute(value: ((parameter: KeyEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onKeyPreIme(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_focusable(this.peer.ptr, value ? 1 : 0)
    }
    onFocusAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBlurAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onBlur(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tabIndexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_tabIndex(this.peer.ptr, value)
    }
    defaultFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_defaultFocus(this.peer.ptr, value ? 1 : 0)
    }
    groupDefaultFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_groupDefaultFocus(this.peer.ptr, value ? 1 : 0)
    }
    focusOnTouchAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_focusOnTouch(this.peer.ptr, value ? 1 : 0)
    }
    focusBoxAttribute(value: FocusBoxStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFocusBoxStyle(value)
        ArkUIGeneratedNativeModule._CommonMethod_focusBox(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationAttribute(value: AnimateParam): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        ArkUIGeneratedNativeModule._CommonMethod_animation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transition0Attribute(value: TransitionOptions | TransitionEffect): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isTransitionOptions(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as TransitionOptions
            thisSerializer.writeTransitionOptions(value_0)
        }
        else if (TypeChecker.isTransitionEffect(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as TransitionEffect
            thisSerializer.writeTransitionEffect(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transition1Attribute(effect: TransitionEffect, onFinish: TransitionFinishCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let onFinish_type : int32 = RuntimeType.UNDEFINED
        onFinish_type = runtimeType(onFinish)
        thisSerializer.writeInt8(onFinish_type as int32)
        if ((RuntimeType.UNDEFINED) != (onFinish_type)) {
            const onFinish_value  = onFinish!
            thisSerializer.holdAndWriteCallback(onFinish_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition1(this.peer.ptr, toPeerPtr(effect), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionBlurAttribute(value: MotionBlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMotionBlurOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_motionBlur(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    brightnessAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_brightness(this.peer.ptr, value)
    }
    contrastAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_contrast(this.peer.ptr, value)
    }
    grayscaleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_grayscale(this.peer.ptr, value)
    }
    colorBlendAttribute(value: Color | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_colorBlend(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    saturateAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_saturate(this.peer.ptr, value)
    }
    sepiaAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_sepia(this.peer.ptr, value)
    }
    invertAttribute(value: number | InvertOptions): void {
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
            const value_1  = value as InvertOptions
            thisSerializer.writeInvertOptions(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_invert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hueRotateAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_hueRotate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useShadowBatchingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_useShadowBatching(this.peer.ptr, value ? 1 : 0)
    }
    useEffect0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_useEffect0(this.peer.ptr, value ? 1 : 0)
    }
    useEffect1Attribute(useEffect: boolean, effectType: EffectType): void {
        ArkUIGeneratedNativeModule._CommonMethod_useEffect1(this.peer.ptr, useEffect ? 1 : 0, TypeChecker.EffectType_ToNumeric(effectType))
    }
    renderGroupAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_renderGroup(this.peer.ptr, value ? 1 : 0)
    }
    freezeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_freeze(this.peer.ptr, value ? 1 : 0)
    }
    translateAttribute(value: TranslateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_translate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scaleAttribute(value: ScaleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScaleOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_scale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gridSpanAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_gridSpan(this.peer.ptr, value)
    }
    gridOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_gridOffset(this.peer.ptr, value)
    }
    rotateAttribute(value: RotateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRotateOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_rotate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transformAttribute(value: TransformationMatrix): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTransformationMatrix(value)
        ArkUIGeneratedNativeModule._CommonMethod_transform(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAppearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDisAppearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDisAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAttachAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDetachAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDetach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAreaChangeAttribute(value: ((oldValue: Area,newValue: Area) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAreaChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visibilityAttribute(value: Visibility): void {
        ArkUIGeneratedNativeModule._CommonMethod_visibility(this.peer.ptr, TypeChecker.Visibility_ToNumeric(value))
    }
    flexGrowAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_flexGrow(this.peer.ptr, value)
    }
    flexShrinkAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_flexShrink(this.peer.ptr, value)
    }
    flexBasisAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_flexBasis(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignSelfAttribute(value: ItemAlign): void {
        ArkUIGeneratedNativeModule._CommonMethod_alignSelf(this.peer.ptr, TypeChecker.ItemAlign_ToNumeric(value))
    }
    displayPriorityAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_displayPriority(this.peer.ptr, value)
    }
    zIndexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_zIndex(this.peer.ptr, value)
    }
    directionAttribute(value: Direction): void {
        ArkUIGeneratedNativeModule._CommonMethod_direction(this.peer.ptr, TypeChecker.Direction_ToNumeric(value))
    }
    alignAttribute(value: Alignment): void {
        ArkUIGeneratedNativeModule._CommonMethod_align(this.peer.ptr, TypeChecker.Alignment_ToNumeric(value))
    }
    positionAttribute(value: Position | Edges | LocalizedEdges): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPosition(value, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Edges
            thisSerializer.writeEdges(value_1)
        }
        else if (TypeChecker.isLocalizedEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdges
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_position(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position | LocalizedPosition): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPosition(value, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isLocalizedPosition(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as LocalizedPosition
            thisSerializer.writeLocalizedPosition(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_markAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPosition(value, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Position
            thisSerializer.writePosition(value_0)
        }
        else if (TypeChecker.isEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Edges
            thisSerializer.writeEdges(value_1)
        }
        else if (TypeChecker.isLocalizedEdges(value, true, false, true, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as LocalizedEdges
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enabledAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_enabled(this.peer.ptr, value ? 1 : 0)
    }
    useSizeTypeAttribute(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_xs  = value.xs
        let value_xs_type : int32 = RuntimeType.UNDEFINED
        value_xs_type = runtimeType(value_xs)
        thisSerializer.writeInt8(value_xs_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_xs_type)) {
            const value_xs_value  = value_xs!
            let value_xs_value_type : int32 = RuntimeType.UNDEFINED
            value_xs_value_type = runtimeType(value_xs_value)
            if (RuntimeType.NUMBER == value_xs_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_xs_value_0  = value_xs_value as number
                thisSerializer.writeNumber(value_xs_value_0)
            }
            else if (RuntimeType.OBJECT == value_xs_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_xs_value_1  = value_xs_value as Literal_Number_offset_span
                const value_xs_value_1_span  = value_xs_value_1.span
                thisSerializer.writeNumber(value_xs_value_1_span)
                const value_xs_value_1_offset  = value_xs_value_1.offset
                thisSerializer.writeNumber(value_xs_value_1_offset)
            }
        }
        const value_sm  = value.sm
        let value_sm_type : int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        thisSerializer.writeInt8(value_sm_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_sm_type)) {
            const value_sm_value  = value_sm!
            let value_sm_value_type : int32 = RuntimeType.UNDEFINED
            value_sm_value_type = runtimeType(value_sm_value)
            if (RuntimeType.NUMBER == value_sm_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_sm_value_0  = value_sm_value as number
                thisSerializer.writeNumber(value_sm_value_0)
            }
            else if (RuntimeType.OBJECT == value_sm_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_sm_value_1  = value_sm_value as Literal_Number_offset_span
                const value_sm_value_1_span  = value_sm_value_1.span
                thisSerializer.writeNumber(value_sm_value_1_span)
                const value_sm_value_1_offset  = value_sm_value_1.offset
                thisSerializer.writeNumber(value_sm_value_1_offset)
            }
        }
        const value_md  = value.md
        let value_md_type : int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        thisSerializer.writeInt8(value_md_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_md_type)) {
            const value_md_value  = value_md!
            let value_md_value_type : int32 = RuntimeType.UNDEFINED
            value_md_value_type = runtimeType(value_md_value)
            if (RuntimeType.NUMBER == value_md_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_md_value_0  = value_md_value as number
                thisSerializer.writeNumber(value_md_value_0)
            }
            else if (RuntimeType.OBJECT == value_md_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_md_value_1  = value_md_value as Literal_Number_offset_span
                const value_md_value_1_span  = value_md_value_1.span
                thisSerializer.writeNumber(value_md_value_1_span)
                const value_md_value_1_offset  = value_md_value_1.offset
                thisSerializer.writeNumber(value_md_value_1_offset)
            }
        }
        const value_lg  = value.lg
        let value_lg_type : int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        thisSerializer.writeInt8(value_lg_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_lg_type)) {
            const value_lg_value  = value_lg!
            let value_lg_value_type : int32 = RuntimeType.UNDEFINED
            value_lg_value_type = runtimeType(value_lg_value)
            if (RuntimeType.NUMBER == value_lg_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_lg_value_0  = value_lg_value as number
                thisSerializer.writeNumber(value_lg_value_0)
            }
            else if (RuntimeType.OBJECT == value_lg_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_lg_value_1  = value_lg_value as Literal_Number_offset_span
                const value_lg_value_1_span  = value_lg_value_1.span
                thisSerializer.writeNumber(value_lg_value_1_span)
                const value_lg_value_1_offset  = value_lg_value_1.offset
                thisSerializer.writeNumber(value_lg_value_1_offset)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_useSizeType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules0Attribute(value: AlignRuleOption): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAlignRuleOption(value)
        ArkUIGeneratedNativeModule._CommonMethod_alignRules0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules1Attribute(value: LocalizedAlignRuleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeLocalizedAlignRuleOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_alignRules1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aspectRatioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_aspectRatio(this.peer.ptr, value)
    }
    clickEffectAttribute(value: ClickEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeClickEffect(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clickEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragStartAttribute(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEnterAttribute(value: ((event: DragEvent,extraParams?: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragMoveAttribute(value: ((event: DragEvent,extraParams?: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragLeaveAttribute(value: ((event: DragEvent,extraParams?: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDropAttribute(value: ((event: DragEvent,extraParams?: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEndAttribute(value: ((event: DragEvent,extraParams?: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    allowDropAttribute(value: Array<UniformDataType> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : UniformDataType = value_value[i]
                thisSerializer.writeInt32(TypeChecker.UniformDataType_ToNumeric(value_value_element))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_allowDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_draggable(this.peer.ptr, value ? 1 : 0)
    }
    dragPreviewAttribute(value: CustomBuilder | DragItemInfo | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_0))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as DragItemInfo
            thisSerializer.writeDragItemInfo(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreview(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreDragAttribute(value: ((parameter: PreDragStatus) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onPreDrag(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientAttribute(value: Type_CommonMethod_linearGradient_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_angle  = value.angle
        let value_angle_type : int32 = RuntimeType.UNDEFINED
        value_angle_type = runtimeType(value_angle)
        thisSerializer.writeInt8(value_angle_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_angle_type)) {
            const value_angle_value  = value_angle!
            let value_angle_value_type : int32 = RuntimeType.UNDEFINED
            value_angle_value_type = runtimeType(value_angle_value)
            if (RuntimeType.NUMBER == value_angle_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_angle_value_0  = value_angle_value as number
                thisSerializer.writeNumber(value_angle_value_0)
            }
            else if (RuntimeType.STRING == value_angle_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_angle_value_1  = value_angle_value as string
                thisSerializer.writeString(value_angle_value_1)
            }
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        thisSerializer.writeInt8(value_direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value  = (value_direction as GradientDirection)
            thisSerializer.writeInt32(TypeChecker.GradientDirection_ToNumeric(value_direction_value))
        }
        const value_colors  = value.colors
        thisSerializer.writeInt32(value_colors.length as int32)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element : [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0  = value_colors_element[0]
            let value_colors_element_0_type : int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (TypeChecker.isColor(value_colors_element_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_colors_element_0_0  = value_colors_element_0 as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_colors_element_0_0))
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_colors_element_0_1  = value_colors_element_0 as number
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_colors_element_0_2  = value_colors_element_0 as string
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_colors_element_0_3  = value_colors_element_0 as Resource
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1  = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating  = value.repeating
        let value_repeating_type : int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value  = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradient(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sweepGradientAttribute(value: Type_CommonMethod_sweepGradient_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_center  = value.center
        const value_center_0  = value_center[0]
        let value_center_0_type : int32 = RuntimeType.UNDEFINED
        value_center_0_type = runtimeType(value_center_0)
        if (RuntimeType.STRING == value_center_0_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_center_0_0  = value_center_0 as string
            thisSerializer.writeString(value_center_0_0)
        }
        else if (RuntimeType.NUMBER == value_center_0_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_center_0_1  = value_center_0 as number
            thisSerializer.writeNumber(value_center_0_1)
        }
        else if (RuntimeType.OBJECT == value_center_0_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_center_0_2  = value_center_0 as Resource
            thisSerializer.writeResource(value_center_0_2)
        }
        const value_center_1  = value_center[1]
        let value_center_1_type : int32 = RuntimeType.UNDEFINED
        value_center_1_type = runtimeType(value_center_1)
        if (RuntimeType.STRING == value_center_1_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_center_1_0  = value_center_1 as string
            thisSerializer.writeString(value_center_1_0)
        }
        else if (RuntimeType.NUMBER == value_center_1_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_center_1_1  = value_center_1 as number
            thisSerializer.writeNumber(value_center_1_1)
        }
        else if (RuntimeType.OBJECT == value_center_1_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_center_1_2  = value_center_1 as Resource
            thisSerializer.writeResource(value_center_1_2)
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        thisSerializer.writeInt8(value_start_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            let value_start_value_type : int32 = RuntimeType.UNDEFINED
            value_start_value_type = runtimeType(value_start_value)
            if (RuntimeType.NUMBER == value_start_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_start_value_0  = value_start_value as number
                thisSerializer.writeNumber(value_start_value_0)
            }
            else if (RuntimeType.STRING == value_start_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_start_value_1  = value_start_value as string
                thisSerializer.writeString(value_start_value_1)
            }
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        thisSerializer.writeInt8(value_end_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            let value_end_value_type : int32 = RuntimeType.UNDEFINED
            value_end_value_type = runtimeType(value_end_value)
            if (RuntimeType.NUMBER == value_end_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_end_value_0  = value_end_value as number
                thisSerializer.writeNumber(value_end_value_0)
            }
            else if (RuntimeType.STRING == value_end_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_end_value_1  = value_end_value as string
                thisSerializer.writeString(value_end_value_1)
            }
        }
        const value_rotation  = value.rotation
        let value_rotation_type : int32 = RuntimeType.UNDEFINED
        value_rotation_type = runtimeType(value_rotation)
        thisSerializer.writeInt8(value_rotation_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_rotation_type)) {
            const value_rotation_value  = value_rotation!
            let value_rotation_value_type : int32 = RuntimeType.UNDEFINED
            value_rotation_value_type = runtimeType(value_rotation_value)
            if (RuntimeType.NUMBER == value_rotation_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_rotation_value_0  = value_rotation_value as number
                thisSerializer.writeNumber(value_rotation_value_0)
            }
            else if (RuntimeType.STRING == value_rotation_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_rotation_value_1  = value_rotation_value as string
                thisSerializer.writeString(value_rotation_value_1)
            }
        }
        const value_colors  = value.colors
        thisSerializer.writeInt32(value_colors.length as int32)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element : [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0  = value_colors_element[0]
            let value_colors_element_0_type : int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (TypeChecker.isColor(value_colors_element_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_colors_element_0_0  = value_colors_element_0 as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_colors_element_0_0))
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_colors_element_0_1  = value_colors_element_0 as number
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_colors_element_0_2  = value_colors_element_0 as string
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_colors_element_0_3  = value_colors_element_0 as Resource
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1  = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating  = value.repeating
        let value_repeating_type : int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value  = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sweepGradient(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radialGradientAttribute(value: Type_CommonMethod_radialGradient_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_center  = value.center
        const value_center_0  = value_center[0]
        let value_center_0_type : int32 = RuntimeType.UNDEFINED
        value_center_0_type = runtimeType(value_center_0)
        if (RuntimeType.STRING == value_center_0_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_center_0_0  = value_center_0 as string
            thisSerializer.writeString(value_center_0_0)
        }
        else if (RuntimeType.NUMBER == value_center_0_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_center_0_1  = value_center_0 as number
            thisSerializer.writeNumber(value_center_0_1)
        }
        else if (RuntimeType.OBJECT == value_center_0_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_center_0_2  = value_center_0 as Resource
            thisSerializer.writeResource(value_center_0_2)
        }
        const value_center_1  = value_center[1]
        let value_center_1_type : int32 = RuntimeType.UNDEFINED
        value_center_1_type = runtimeType(value_center_1)
        if (RuntimeType.STRING == value_center_1_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_center_1_0  = value_center_1 as string
            thisSerializer.writeString(value_center_1_0)
        }
        else if (RuntimeType.NUMBER == value_center_1_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_center_1_1  = value_center_1 as number
            thisSerializer.writeNumber(value_center_1_1)
        }
        else if (RuntimeType.OBJECT == value_center_1_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_center_1_2  = value_center_1 as Resource
            thisSerializer.writeResource(value_center_1_2)
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        if (RuntimeType.NUMBER == value_radius_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_radius_0  = value_radius as number
            thisSerializer.writeNumber(value_radius_0)
        }
        else if (RuntimeType.STRING == value_radius_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_radius_1  = value_radius as string
            thisSerializer.writeString(value_radius_1)
        }
        const value_colors  = value.colors
        thisSerializer.writeInt32(value_colors.length as int32)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element : [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0  = value_colors_element[0]
            let value_colors_element_0_type : int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (TypeChecker.isColor(value_colors_element_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_colors_element_0_0  = value_colors_element_0 as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_colors_element_0_0))
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_colors_element_0_1  = value_colors_element_0 as number
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_colors_element_0_2  = value_colors_element_0 as string
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_colors_element_0_3  = value_colors_element_0 as Resource
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1  = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating  = value.repeating
        let value_repeating_type : int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value  = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_radialGradient(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionPathAttribute(value: MotionPathOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMotionPathOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_motionPath(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shadowAttribute(value: ShadowOptions | ShadowStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ShadowOptions
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (TypeChecker.isShadowStyle(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ShadowStyle
            thisSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._CommonMethod_shadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clip0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clip0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clip1Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clip1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clipShapeAttribute(value: CircleShape | EllipseShape | PathShape | RectShape): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isCircleShape(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as CircleShape
            thisSerializer.writeCircleShape(value_0)
        }
        else if (TypeChecker.isEllipseShape(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EllipseShape
            thisSerializer.writeEllipseShape(value_1)
        }
        else if (TypeChecker.isPathShape(value)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as PathShape
            thisSerializer.writePathShape(value_2)
        }
        else if (TypeChecker.isRectShape(value)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as RectShape
            thisSerializer.writeRectShape(value_3)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clipShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mask0Attribute(value: ProgressMask | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeProgressMask(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mask0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mask1Attribute(value: ProgressMask | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeProgressMask(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mask1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maskShapeAttribute(value: CircleShape | EllipseShape | PathShape | RectShape): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isCircleShape(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as CircleShape
            thisSerializer.writeCircleShape(value_0)
        }
        else if (TypeChecker.isEllipseShape(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as EllipseShape
            thisSerializer.writeEllipseShape(value_1)
        }
        else if (TypeChecker.isPathShape(value)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as PathShape
            thisSerializer.writePathShape(value_2)
        }
        else if (TypeChecker.isRectShape(value)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as RectShape
            thisSerializer.writeRectShape(value_3)
        }
        ArkUIGeneratedNativeModule._CommonMethod_maskShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_key(this.peer.ptr, value)
    }
    idAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_id(this.peer.ptr, value)
    }
    geometryTransition0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition0(this.peer.ptr, value)
    }
    geometryTransition1Attribute(id: string, options?: GeometryTransitionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeGeometryTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition1(this.peer.ptr, id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stateStylesAttribute(value: StateStyles): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeStateStyles(value)
        ArkUIGeneratedNativeModule._CommonMethod_stateStyles(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    restoreIdAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_restoreId(this.peer.ptr, value)
    }
    sphericalEffectAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_sphericalEffect(this.peer.ptr, value)
    }
    lightUpEffectAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_lightUpEffect(this.peer.ptr, value)
    }
    pixelStretchEffectAttribute(value: PixelStretchEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePixelStretchEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_pixelStretchEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityGroup0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup0(this.peer.ptr, value ? 1 : 0)
    }
    accessibilityGroup1Attribute(isGroup: boolean, accessibilityOptions: AccessibilityOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAccessibilityOptions(accessibilityOptions)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup1(this.peer.ptr, isGroup ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityText0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText0(this.peer.ptr, value)
    }
    accessibilityText1Attribute(value: Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityTextHintAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityTextHint(this.peer.ptr, value)
    }
    accessibilityDescription0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription0(this.peer.ptr, value)
    }
    accessibilityDescription1Attribute(value: Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityLevelAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityLevel(this.peer.ptr, value)
    }
    accessibilityVirtualNodeAttribute(value: CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityVirtualNode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityCheckedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityChecked(this.peer.ptr, value ? 1 : 0)
    }
    accessibilitySelectedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilitySelected(this.peer.ptr, value ? 1 : 0)
    }
    obscuredAttribute(value: Array<ObscuredReasons>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ObscuredReasons = value[i]
            thisSerializer.writeInt32(TypeChecker.ObscuredReasons_ToNumeric(value_element))
        }
        ArkUIGeneratedNativeModule._CommonMethod_obscured(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reuseIdAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_reuseId(this.peer.ptr, value)
    }
    renderFitAttribute(value: RenderFit): void {
        ArkUIGeneratedNativeModule._CommonMethod_renderFit(this.peer.ptr, TypeChecker.RenderFit_ToNumeric(value))
    }
    gestureModifierAttribute(value: GestureModifier): void {
        ArkUIGeneratedNativeModule._CommonMethod_gestureModifier(this.peer.ptr, toPeerPtr(value))
    }
    backgroundBrightnessAttribute(value: BackgroundBrightnessOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBackgroundBrightnessOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureJudgeBeginAttribute(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureJudgeBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin0Attribute(value: GestureRecognizerJudgeBeginCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin1Attribute(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), exposeInnerGesture ? 1 : 0)
        thisSerializer.release()
    }
    shouldBuiltInRecognizerParallelWithAttribute(value: ShouldBuiltInRecognizerParallelWithCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_shouldBuiltInRecognizerParallelWith(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    monopolizeEventsAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_monopolizeEvents(this.peer.ptr, value ? 1 : 0)
    }
    onTouchInterceptAttribute(value: ((parameter: TouchEvent) => HitTestMode)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onTouchIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSizeChangeAttribute(value: SizeChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onSizeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customPropertyAttribute(name: string, value: Object | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_customProperty(this.peer.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    expandSafeAreaAttribute(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type as int32)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value  = types!
            thisSerializer.writeInt32(types_value.length as int32)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element : SafeAreaType = types_value[i]
                thisSerializer.writeInt32(TypeChecker.SafeAreaType_ToNumeric(types_value_element))
            }
        }
        let edges_type : int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type as int32)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value  = edges!
            thisSerializer.writeInt32(edges_value.length as int32)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element : SafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(TypeChecker.SafeAreaEdge_ToNumeric(edges_value_element))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_expandSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundAttribute(builder: CustomBuilder, options?: Literal_Alignment_align): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            const options_value_align  = options_value.align
            let options_value_align_type : int32 = RuntimeType.UNDEFINED
            options_value_align_type = runtimeType(options_value_align)
            thisSerializer.writeInt8(options_value_align_type as int32)
            if ((RuntimeType.UNDEFINED) != (options_value_align_type)) {
                const options_value_align_value  = (options_value_align as Alignment)
                thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(options_value_align_value))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_background(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageAttribute(src: ResourceStr | PixelMap, repeat?: ImageRepeat): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as ResourceStr
            let src_0_type : int32 = RuntimeType.UNDEFINED
            src_0_type = runtimeType(src_0)
            if (RuntimeType.STRING == src_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_0_0  = src_0 as string
                thisSerializer.writeString(src_0_0)
            }
            else if (RuntimeType.OBJECT == src_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_0_1  = src_0 as Resource
                thisSerializer.writeResource(src_0_1)
            }
        }
        else if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as PixelMap
            thisSerializer.writePixelMap(src_1)
        }
        let repeat_type : int32 = RuntimeType.UNDEFINED
        repeat_type = runtimeType(repeat)
        thisSerializer.writeInt8(repeat_type as int32)
        if ((RuntimeType.UNDEFINED) != (repeat_type)) {
            const repeat_value  = (repeat as ImageRepeat)
            thisSerializer.writeInt32(TypeChecker.ImageRepeat_ToNumeric(repeat_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImage(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBlurStyleAttribute(value: BlurStyle, options?: BackgroundBlurStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBlurStyle(this.peer.ptr, TypeChecker.BlurStyle_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundBlurStyleAttribute(value: BlurStyle, options?: ForegroundBlurStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeForegroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundBlurStyle(this.peer.ptr, TypeChecker.BlurStyle_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId0Attribute(id: string, isGroup?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isGroup_type : int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value  = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId0(this.peer.ptr, id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId1Attribute(id: string, isGroup?: boolean, arrowStepOut?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isGroup_type : int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value  = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        let arrowStepOut_type : int32 = RuntimeType.UNDEFINED
        arrowStepOut_type = runtimeType(arrowStepOut)
        thisSerializer.writeInt8(arrowStepOut_type as int32)
        if ((RuntimeType.UNDEFINED) != (arrowStepOut_type)) {
            const arrowStepOut_value  = arrowStepOut!
            thisSerializer.writeBoolean(arrowStepOut_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId1(this.peer.ptr, id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopePriorityAttribute(scopeId: string, priority?: FocusPriority): void {
        const thisSerializer : Serializer = Serializer.hold()
        let priority_type : int32 = RuntimeType.UNDEFINED
        priority_type = runtimeType(priority)
        thisSerializer.writeInt8(priority_type as int32)
        if ((RuntimeType.UNDEFINED) != (priority_type)) {
            const priority_value  = (priority as FocusPriority)
            thisSerializer.writeInt32(TypeChecker.FocusPriority_ToNumeric(priority_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopePriority(this.peer.ptr, scopeId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer : Serializer = Serializer.hold()
        let gesture_type : int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if (TypeChecker.isTapGestureInterface(gesture)) {
            thisSerializer.writeInt8(0 as int32)
            const gesture_0  = gesture as TapGestureInterface
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if (TypeChecker.isLongPressGestureInterface(gesture)) {
            thisSerializer.writeInt8(1 as int32)
            const gesture_1  = gesture as LongPressGestureInterface
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if (TypeChecker.isPanGestureInterface(gesture)) {
            thisSerializer.writeInt8(2 as int32)
            const gesture_2  = gesture as PanGestureInterface
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if (TypeChecker.isPinchGestureInterface(gesture)) {
            thisSerializer.writeInt8(3 as int32)
            const gesture_3  = gesture as PinchGestureInterface
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if (TypeChecker.isSwipeGestureInterface(gesture)) {
            thisSerializer.writeInt8(4 as int32)
            const gesture_4  = gesture as SwipeGestureInterface
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if (TypeChecker.isRotationGestureInterface(gesture)) {
            thisSerializer.writeInt8(5 as int32)
            const gesture_5  = gesture as RotationGestureInterface
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if (TypeChecker.isGestureGroupInterface(gesture)) {
            thisSerializer.writeInt8(6 as int32)
            const gesture_6  = gesture as GestureGroupInterface
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type : int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type as int32)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value  = (mask as GestureMask)
            thisSerializer.writeInt32(TypeChecker.GestureMask_ToNumeric(mask_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_gesture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    priorityGestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer : Serializer = Serializer.hold()
        let gesture_type : int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if (TypeChecker.isTapGestureInterface(gesture)) {
            thisSerializer.writeInt8(0 as int32)
            const gesture_0  = gesture as TapGestureInterface
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if (TypeChecker.isLongPressGestureInterface(gesture)) {
            thisSerializer.writeInt8(1 as int32)
            const gesture_1  = gesture as LongPressGestureInterface
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if (TypeChecker.isPanGestureInterface(gesture)) {
            thisSerializer.writeInt8(2 as int32)
            const gesture_2  = gesture as PanGestureInterface
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if (TypeChecker.isPinchGestureInterface(gesture)) {
            thisSerializer.writeInt8(3 as int32)
            const gesture_3  = gesture as PinchGestureInterface
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if (TypeChecker.isSwipeGestureInterface(gesture)) {
            thisSerializer.writeInt8(4 as int32)
            const gesture_4  = gesture as SwipeGestureInterface
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if (TypeChecker.isRotationGestureInterface(gesture)) {
            thisSerializer.writeInt8(5 as int32)
            const gesture_5  = gesture as RotationGestureInterface
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if (TypeChecker.isGestureGroupInterface(gesture)) {
            thisSerializer.writeInt8(6 as int32)
            const gesture_6  = gesture as GestureGroupInterface
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type : int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type as int32)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value  = (mask as GestureMask)
            thisSerializer.writeInt32(TypeChecker.GestureMask_ToNumeric(mask_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_priorityGesture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    parallelGestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer : Serializer = Serializer.hold()
        let gesture_type : int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if (TypeChecker.isTapGestureInterface(gesture)) {
            thisSerializer.writeInt8(0 as int32)
            const gesture_0  = gesture as TapGestureInterface
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if (TypeChecker.isLongPressGestureInterface(gesture)) {
            thisSerializer.writeInt8(1 as int32)
            const gesture_1  = gesture as LongPressGestureInterface
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if (TypeChecker.isPanGestureInterface(gesture)) {
            thisSerializer.writeInt8(2 as int32)
            const gesture_2  = gesture as PanGestureInterface
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if (TypeChecker.isPinchGestureInterface(gesture)) {
            thisSerializer.writeInt8(3 as int32)
            const gesture_3  = gesture as PinchGestureInterface
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if (TypeChecker.isSwipeGestureInterface(gesture)) {
            thisSerializer.writeInt8(4 as int32)
            const gesture_4  = gesture as SwipeGestureInterface
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if (TypeChecker.isRotationGestureInterface(gesture)) {
            thisSerializer.writeInt8(5 as int32)
            const gesture_5  = gesture as RotationGestureInterface
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if (TypeChecker.isGestureGroupInterface(gesture)) {
            thisSerializer.writeInt8(6 as int32)
            const gesture_6  = gesture as GestureGroupInterface
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type : int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type as int32)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value  = (mask as GestureMask)
            thisSerializer.writeInt32(TypeChecker.GestureMask_ToNumeric(mask_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_parallelGesture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blurAttribute(value: number, options?: BlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_blur(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientBlurAttribute(value: number, options: LinearGradientBlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeLinearGradientBlurOptions(options)
        ArkUIGeneratedNativeModule._CommonMethod_linearGradientBlur(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarEffectAttribute(): void {
        ArkUIGeneratedNativeModule._CommonMethod_systemBarEffect(this.peer.ptr)
    }
    backdropBlurAttribute(value: number, options?: BlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backdropBlur(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sharedTransitionAttribute(id: string, options?: sharedTransitionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writesharedTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sharedTransition(this.peer.ptr, id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainModeAttribute(direction: Axis, style: ChainStyle): void {
        ArkUIGeneratedNativeModule._CommonMethod_chainMode(this.peer.ptr, TypeChecker.Axis_ToNumeric(direction), TypeChecker.ChainStyle_ToNumeric(style))
    }
    dragPreviewOptionsAttribute(value: DragPreviewOptions, options?: DragInteractionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDragPreviewOptions(value)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeDragInteractionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreviewOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    overlayAttribute(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as ComponentContent
            thisSerializer.writeComponentContent(value_2)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeOverlayOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_overlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blendModeAttribute(value: BlendMode, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(TypeChecker.BlendApplyType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_blendMode(this.peer.ptr, TypeChecker.BlendMode_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    advancedBlendModeAttribute(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let effect_type : int32 = RuntimeType.UNDEFINED
        effect_type = runtimeType(effect)
        if (TypeChecker.isBlendMode(effect)) {
            thisSerializer.writeInt8(0 as int32)
            const effect_0  = effect as BlendMode
            thisSerializer.writeInt32(TypeChecker.BlendMode_ToNumeric(effect_0))
        }
        else if (RuntimeType.OBJECT == effect_type) {
            thisSerializer.writeInt8(1 as int32)
            const effect_1  = effect as BrightnessBlender
            thisSerializer.writeBrightnessBlender(effect_1)
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(TypeChecker.BlendApplyType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_advancedBlendMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindPopupAttribute(show: boolean, popup: PopupOptions | CustomPopupOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let popup_type : int32 = RuntimeType.UNDEFINED
        popup_type = runtimeType(popup)
        if (TypeChecker.isPopupOptions(popup, false, false, true, false, false, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true)) {
            thisSerializer.writeInt8(0 as int32)
            const popup_0  = popup as PopupOptions
            thisSerializer.writePopupOptions(popup_0)
        }
        else if (TypeChecker.isCustomPopupOptions(popup, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true)) {
            thisSerializer.writeInt8(1 as int32)
            const popup_1  = popup as CustomPopupOptions
            thisSerializer.writeCustomPopupOptions(popup_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindPopup(this.peer.ptr, show ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindMenu0Attribute(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        if (RuntimeType.OBJECT == content_type) {
            thisSerializer.writeInt8(0 as int32)
            const content_0  = content as Array<MenuElement>
            thisSerializer.writeInt32(content_0.length as int32)
            for (let i = 0; i < content_0.length; i++) {
                const content_0_element : MenuElement = content_0[i]
                thisSerializer.writeMenuElement(content_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == content_type) {
            thisSerializer.writeInt8(1 as int32)
            const content_1  = content as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_1))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindMenu0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindMenu1Attribute(isShow: boolean, content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        if (RuntimeType.OBJECT == content_type) {
            thisSerializer.writeInt8(0 as int32)
            const content_0  = content as Array<MenuElement>
            thisSerializer.writeInt32(content_0.length as int32)
            for (let i = 0; i < content_0.length; i++) {
                const content_0_element : MenuElement = content_0[i]
                thisSerializer.writeMenuElement(content_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == content_type) {
            thisSerializer.writeInt8(1 as int32)
            const content_1  = content as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_1))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindMenu1(this.peer.ptr, isShow ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContextMenu0Attribute(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.ResponseType_ToNumeric(responseType))
        thisSerializer.release()
    }
    bindContextMenu1Attribute(isShown: boolean, content: CustomBuilder, options?: ContextMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu1(this.peer.ptr, isShown ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContentCover0Attribute(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as ModalTransition)
            thisSerializer.writeInt32(TypeChecker.ModalTransition_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContentCover0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContentCover1Attribute(isShow: boolean | undefined, builder: CustomBuilder, options?: ContentCoverOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContentCoverOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContentCover1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSheetAttribute(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSheetOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindSheet(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onVisibleAreaChangeAttribute(ratios: Array<number>, event: VisibleAreaChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(ratios.length as int32)
        for (let i = 0; i < ratios.length; i++) {
            const ratios_element : number = ratios[i]
            thisSerializer.writeNumber(ratios_element)
        }
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._CommonMethod_onVisibleAreaChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardShortcutAttribute(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isFunctionKey(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FunctionKey
            thisSerializer.writeInt32(TypeChecker.FunctionKey_ToNumeric(value_1))
        }
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : ModifierKey = keys[i]
            thisSerializer.writeInt32(TypeChecker.ModifierKey_ToNumeric(keys_element))
        }
        let action_type : int32 = RuntimeType.UNDEFINED
        action_type = runtimeType(action)
        thisSerializer.writeInt8(action_type as int32)
        if ((RuntimeType.UNDEFINED) != (action_type)) {
            const action_value  = action!
            thisSerializer.holdAndWriteCallback(action_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_keyboardShortcut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkCommonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Common_construct(peerId, flags)
        const _peer  = new ArkCommonPeer(_peerPtr, peerId, "Common", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCommonOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._CommonInterface_setCommonOptions(this.peer.ptr)
    }
}
export class ArkCommonShapeMethodPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonShapeMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CommonShapeMethod_construct(peerId, flags)
        const _peer  = new ArkCommonShapeMethodPeer(_peerPtr, peerId, "CommonShapeMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    strokeAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_stroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_fill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineCap(this.peer.ptr, TypeChecker.LineCapStyle_ToNumeric(value))
    }
    strokeLineJoinAttribute(value: LineJoinStyle): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineJoin(this.peer.ptr, TypeChecker.LineJoinStyle_ToNumeric(value))
    }
    strokeMiterLimitAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource): void {
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
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource): void {
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
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_fillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    antiAliasAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_antiAlias(this.peer.ptr, value ? 1 : 0)
    }
    strokeDashArrayAttribute(value: Array<Length>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : Length = value[i]
            let value_element_type : int32 = RuntimeType.UNDEFINED
            value_element_type = runtimeType(value_element)
            if (RuntimeType.STRING == value_element_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_element_0  = value_element as string
                thisSerializer.writeString(value_element_0)
            }
            else if (RuntimeType.NUMBER == value_element_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_element_1  = value_element as number
                thisSerializer.writeNumber(value_element_1)
            }
            else if (RuntimeType.OBJECT == value_element_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_element_2  = value_element as Resource
                thisSerializer.writeResource(value_element_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkScrollableCommonMethodPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollableCommonMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ScrollableCommonMethod_construct(peerId, flags)
        const _peer  = new ArkScrollableCommonMethodPeer(_peerPtr, peerId, "ScrollableCommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBar(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    scrollBarColorAttribute(value: Color | number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
    }
    frictionAttribute(value: number | Resource): void {
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
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    flingSpeedLimitAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_flingSpeedLimit(this.peer.ptr, value)
    }
    clipContentAttribute(value: ContentClipMode | RectShape): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isContentClipMode(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ContentClipMode
            thisSerializer.writeInt32(TypeChecker.ContentClipMode_ToNumeric(value_0))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as RectShape
            thisSerializer.writeRectShape(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_clipContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_edgeEffect(this.peer.ptr, TypeChecker.EdgeEffect_ToNumeric(edgeEffect), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fadingEdgeAttribute(enabled: boolean | undefined, options?: FadingEdgeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let enabled_type : int32 = RuntimeType.UNDEFINED
        enabled_type = runtimeType(enabled)
        thisSerializer.writeInt8(enabled_type as int32)
        if ((RuntimeType.UNDEFINED) != (enabled_type)) {
            const enabled_value  = enabled!
            thisSerializer.writeBoolean(enabled_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeFadingEdgeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_fadingEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ComponentOptions {
    freezeWhenInactive: boolean;
}
export interface InputCounterOptions {
    thresholdPercentage?: number;
    highlightBorder?: boolean;
}
export interface TextDecorationOptions {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
export interface ProvideOptions {
    allowOverride?: string;
}
export interface AnimatableArithmetic<T> {
}
export interface Configuration {
    readonly colorMode: string;
    readonly fontScale: number;
}
export interface Rectangle {
    x?: Length;
    y?: Length;
    width?: Length;
    height?: Length;
}
export interface ExpectedFrameRateRange {
    min: number;
    max: number;
    expected: number;
}
export enum FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1
}
export enum TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION = 1,
    FORWARD = 2
}
export interface AnimateParam {
    duration?: number;
    tempo?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    iterations?: number;
    playMode?: PlayMode;
    onFinish?: (() => void);
    finishCallbackType?: FinishCallbackType;
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
export interface MotionPathOptions {
    path: string;
    from?: number;
    to?: number;
    rotatable?: boolean;
}
export interface sharedTransitionOptions {
    duration?: number;
    curve?: Curve | string | ICurve;
    delay?: number;
    motionPath?: MotionPathOptions;
    zIndex?: number;
    type?: SharedTransitionEffectType;
}
export interface GeometryTransitionOptions {
    follow?: boolean;
    hierarchyStrategy?: TransitionHierarchyStrategy;
}
export enum TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE = 1
}
export interface TranslateOptions {
    x?: number | string;
    y?: number | string;
    z?: number | string;
}
export interface ScaleOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
}
export interface Literal_String_anchor_HorizontalAlign_align {
    anchor: string;
    align: HorizontalAlign;
}
export interface Literal_String_anchor_VerticalAlign_align {
    anchor: string;
    align: VerticalAlign;
}
export interface AlignRuleOption {
    left?: Literal_String_anchor_HorizontalAlign_align;
    right?: Literal_String_anchor_HorizontalAlign_align;
    middle?: Literal_String_anchor_HorizontalAlign_align;
    top?: Literal_String_anchor_VerticalAlign_align;
    bottom?: Literal_String_anchor_VerticalAlign_align;
    center?: Literal_String_anchor_VerticalAlign_align;
    bias?: Bias;
}
export interface LocalizedHorizontalAlignParam {
    anchor: string;
    align: HorizontalAlign;
}
export interface LocalizedVerticalAlignParam {
    anchor: string;
    align: VerticalAlign;
}
export interface LocalizedAlignRuleOptions {
    start?: LocalizedHorizontalAlignParam;
    end?: LocalizedHorizontalAlignParam;
    middle?: LocalizedHorizontalAlignParam;
    top?: LocalizedVerticalAlignParam;
    bottom?: LocalizedVerticalAlignParam;
    center?: LocalizedVerticalAlignParam;
    bias?: Bias;
}
export enum ChainStyle {
    SPREAD = 0,
    SPREAD_INSIDE = 1,
    PACKED = 2
}
export interface RotateOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number | string;
    centerY?: number | string;
    centerZ?: number;
    perspective?: number;
    angle: number | string;
}
export interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
export enum TransitionEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export interface Literal_TransitionEffect_appear_disappear {
    appear: TransitionEffect;
    disappear: TransitionEffect;
}
export interface TransitionEffects {
    identity: undefined;
    opacity: number;
    slideSwitch: undefined;
    move: TransitionEdge;
    translate: TranslateOptions;
    rotate: RotateOptions;
    scale: ScaleOptions;
    asymmetric: Literal_TransitionEffect_appear_disappear;
}
export interface PreviewParams {
    title?: string;
    width?: number;
    height?: number;
    locale?: string;
    colorMode?: string;
    deviceType?: string;
    dpi?: number;
    orientation?: string;
    roundScreen?: boolean;
}
export interface ItemDragInfo {
    x: number;
    y: number;
}
export enum EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1
}
export enum PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6
}
export interface DragItemInfo {
    pixelMap?: PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
export interface EventTarget {
    area: Area;
}
export enum SourceType {
    UNKNOWN = 0,
    Unknown = 0,
    MOUSE = 1,
    Mouse = 1,
    TOUCH_SCREEN = 2,
    TouchScreen = 2
}
export enum SourceTool {
    UNKNOWN = 0,
    Unknown = 0,
    FINGER = 1,
    Finger = 1,
    PEN = 2,
    Pen = 2,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5
}
export enum RepeatMode {
    REPEAT = 0,
    Repeat = 0,
    STRETCH = 1,
    Stretch = 1,
    ROUND = 2,
    Round = 2,
    SPACE = 3,
    Space = 3
}
export enum BlurStyle {
    THIN = 0,
    Thin = 0,
    REGULAR = 1,
    Regular = 1,
    THICK = 2,
    Thick = 2,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12
}
export enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2
}
export enum ThemeColorMode {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2
}
export enum AdaptiveColor {
    DEFAULT = 0,
    AVERAGE = 1
}
export enum ModalTransition {
    DEFAULT = 0,
    NONE = 1,
    ALPHA = 2
}
export interface BackgroundBlurStyleOptions extends BlurStyleOptions {
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
export interface ForegroundBlurStyleOptions extends BlurStyleOptions {
}
export interface BlurOptions {
    grayscale: [ number, number ];
}
export interface BlurStyleOptions {
    colorMode?: ThemeColorMode;
    adaptiveColor?: AdaptiveColor;
    scale?: number;
    blurOptions?: BlurOptions;
}
export interface BackgroundEffectOptions {
    radius: number;
    saturation?: number;
    brightness?: number;
    color?: ResourceColor;
    adaptiveColor?: AdaptiveColor;
    blurOptions?: BlurOptions;
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
export interface ForegroundEffectOptions {
    radius: number;
}
export interface PickerTextStyle {
    color?: ResourceColor;
    font?: Font;
}
export interface PickerDialogButtonStyle {
    type?: ButtonType;
    style?: ButtonStyleMode;
    role?: ButtonRole;
    fontSize?: Length;
    fontColor?: ResourceColor;
    fontWeight?: FontWeight | number | string;
    fontStyle?: FontStyle;
    fontFamily?: Resource | string;
    backgroundColor?: ResourceColor;
    borderRadius?: Length | BorderRadiuses;
    primary?: boolean;
}
export enum ShadowType {
    COLOR = 0,
    BLUR = 1
}
export interface ShadowOptions {
    radius: number | Resource;
    type?: ShadowType;
    color?: Color | string | Resource | ColoringStrategy;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
    fill?: boolean;
}
export enum ShadowStyle {
    OUTER_DEFAULT_XS = 0,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5
}
export interface MultiShadowOptions {
    radius?: number | Resource;
    offsetX?: number | Resource;
    offsetY?: number | Resource;
}
export enum SafeAreaType {
    SYSTEM = 0,
    CUTOUT = 1,
    KEYBOARD = 2
}
export enum SafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export enum LayoutSafeAreaType {
    SYSTEM = 0
}
export enum LayoutSafeAreaEdge {
    TOP = 0,
    BOTTOM = 1
}
export enum SheetSize {
    MEDIUM = 0,
    LARGE = 1,
    FIT_CONTENT = 2
}
export interface BorderImageOption {
    slice?: Length | EdgeWidths | LocalizedEdgeWidths;
    repeat?: RepeatMode;
    source?: string | Resource | LinearGradient_common;
    width?: Length | EdgeWidths | LocalizedEdgeWidths;
    outset?: Length | EdgeWidths | LocalizedEdgeWidths;
    fill?: boolean;
}
export interface TouchObject {
    type: TouchType;
    id: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
}
export interface HistoricalPoint {
    touchObject: TouchObject;
    size: number;
    force: number;
    timestamp: int64;
}
export type SizeChangeCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
export type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>) => GestureJudgeResult;
export type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
export type TransitionFinishCallback = (transitionIn: boolean) => void;
export enum DragBehavior {
    COPY = 0,
    MOVE = 1
}
export enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4
}
export enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1
}
export interface BindOptions {
    backgroundColor?: ResourceColor;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
}
export interface DismissContentCoverAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export type Callback_DismissContentCoverAction_Void = (parameter: DismissContentCoverAction) => void;
export interface ContentCoverOptions extends BindOptions {
    modalTransition?: ModalTransition;
    onWillDismiss?: ((parameter: DismissContentCoverAction) => void);
    transition?: TransitionEffect;
}
export interface SheetTitleOptions {
    title: ResourceStr;
    subtitle?: ResourceStr;
}
export enum SheetType {
    BOTTOM = 0,
    CENTER = 1,
    POPUP = 2
}
export enum SheetMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
export enum ScrollSizeMode {
    FOLLOW_DETENT = 0,
    CONTINUOUS = 1
}
export enum SheetKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3
}
export interface SheetDismiss {
    dismiss: (() => void);
}
export interface DismissSheetAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface SpringBackAction {
    springBack: (() => void);
}
export type Type_SheetOptions_detents = [
    SheetSize | Length,
    SheetSize | Length | undefined,
    SheetSize | Length | undefined
]
export type Callback_SheetDismiss_Void = (sheetDismiss: SheetDismiss) => void;
export type Callback_DismissSheetAction_Void = (parameter: DismissSheetAction) => void;
export type Callback_SpringBackAction_Void = (parameter: SpringBackAction) => void;
export type Callback_SheetType_Void = (parameter: SheetType) => void;
export interface SheetOptions extends BindOptions {
    height?: SheetSize | Length;
    dragBar?: boolean;
    maskColor?: ResourceColor;
    detents?: [ SheetSize | Length, SheetSize | Length | undefined, SheetSize | Length | undefined ];
    blurStyle?: BlurStyle;
    showClose?: boolean | Resource;
    preferType?: SheetType;
    title?: SheetTitleOptions | CustomBuilder;
    shouldDismiss?: ((sheetDismiss: SheetDismiss) => void);
    onWillDismiss?: ((parameter: DismissSheetAction) => void);
    onWillSpringBackWhenDismiss?: ((parameter: SpringBackAction) => void);
    enableOutsideInteractive?: boolean;
    width?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    onHeightDidChange?: ((index: number) => void);
    mode?: SheetMode;
    scrollSizeMode?: ScrollSizeMode;
    onDetentsDidChange?: ((index: number) => void);
    onWidthDidChange?: ((index: number) => void);
    onTypeDidChange?: ((parameter: SheetType) => void);
    uiContext?: UIContext;
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
}
export interface StateStyles {
    normal?: object;
    pressed?: object;
    disabled?: object;
    focused?: object;
    clicked?: object;
    selected?: Object;
}
export interface PopupMessageOptions {
    textColor?: ResourceColor;
    font?: Font;
}
export enum DismissReason {
    PRESS_BACK = 0,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3
}
export interface DismissPopupAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface Literal_String_value_Callback_Void_action {
    value: string;
    action: (() => void);
}
export interface Literal_Boolean_isVisible {
    isVisible: boolean;
}
export type Callback_Literal_Boolean_isVisible_Void = (event: Literal_Boolean_isVisible) => void;
export interface Literal_ResourceColor_color {
    color: ResourceColor;
}
export type Callback_DismissPopupAction_Void = (parameter: DismissPopupAction) => void;
export interface PopupOptions {
    message: string;
    placementOnTop?: boolean;
    placement?: Placement;
    primaryButton?: Literal_String_value_Callback_Void_action;
    secondaryButton?: Literal_String_value_Callback_Void_action;
    onStateChange?: ((event: Literal_Boolean_isVisible) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | Literal_ResourceColor_color;
    messageOptions?: PopupMessageOptions;
    targetSpace?: Length;
    enableArrow?: boolean;
    offset?: Position;
    popupColor?: Color | string | Resource | number;
    autoCancel?: boolean;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    onWillDismiss?: boolean | ((parameter: DismissPopupAction) => void);
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
export interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    maskColor?: Color | string | Resource | number;
    popupColor?: Color | string | Resource | number;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: ((event: Literal_Boolean_isVisible) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | Literal_ResourceColor_color;
    targetSpace?: Length;
    offset?: Position;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    focusable?: boolean;
    transition?: TransitionEffect;
    onWillDismiss?: boolean | ((parameter: DismissPopupAction) => void);
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
export enum MenuPreviewMode {
    NONE = 0,
    IMAGE = 1
}
export type AnimationRange<T> = [
    T,
    T
]
export interface ContextMenuAnimationOptions {
    scale?: [ number, number ];
    transition?: TransitionEffect;
    hoverScale?: [ number, number ];
}
export interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: MenuPreviewMode | CustomBuilder;
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    aboutToAppear?: (() => void);
    aboutToDisappear?: (() => void);
    layoutRegionMargin?: Padding;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
}
export interface MenuOptions extends ContextMenuOptions {
    title?: ResourceStr;
    showInSubWindow?: boolean;
}
export interface TouchTestInfo {
    windowX: number;
    windowY: number;
    parentX: number;
    parentY: number;
    x: number;
    y: number;
    rect: RectResult;
    id: string;
}
export interface TouchResult {
    strategy: TouchTestStrategy;
    id?: string;
}
export interface PixelStretchEffectOptions {
    top?: Length;
    bottom?: Length;
    left?: Length;
    right?: Length;
}
export interface ClickEffect {
    level: ClickEffectLevel;
    scale?: number;
}
export interface FadingEdgeOptions {
    fadingEdgeLength?: LengthMetrics;
}
export interface NestedScrollOptions {
    scrollForward: NestedScrollMode;
    scrollBackward: NestedScrollMode;
}
export interface MenuElement {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    enabled?: boolean;
    action: (() => void);
}
export enum OutlineStyle {
    SOLID = 0,
    DASHED = 1,
    DOTTED = 2
}
export enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4
}
export enum MenuPolicy {
    DEFAULT = 0,
    HIDE = 1,
    SHOW = 2
}
export interface DragPreviewOptions {
    mode?: DragPreviewMode | Array<DragPreviewMode>;
    modifier?: ImageModifier;
    numberBadge?: boolean | number;
}
export interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
}
export interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
export type Callback_Array_TouchTestInfo_TouchResult = (value: Array<TouchTestInfo>) => TouchResult;
export type Callback_ClickEvent_Void = (event: ClickEvent) => void;
export type Callback_Boolean_HoverEvent_Void = (isHover: boolean, event: HoverEvent) => void;
export type Callback_MouseEvent_Void = (event: MouseEvent) => void;
export type Callback_TouchEvent_Void = (event: TouchEvent) => void;
export type Callback_KeyEvent_Void = (event: KeyEvent) => void;
export type Callback_KeyEvent_Boolean = (parameter: KeyEvent) => boolean;
export type Callback_Area_Area_Void = (oldValue: Area, newValue: Area) => void;
export interface Literal_Number_offset_span {
    span: number;
    offset: number;
}
export interface Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs {
    xs?: number | Literal_Number_offset_span;
    sm?: number | Literal_Number_offset_span;
    md?: number | Literal_Number_offset_span;
    lg?: number | Literal_Number_offset_span;
}
export type Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo = (event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo;
export type Callback_DragEvent_String_Void = (event: DragEvent, extraParams?: string) => void;
export type Callback_PreDragStatus_Void = (parameter: PreDragStatus) => void;
export type Tuple_ResourceColor_Number = [
    ResourceColor,
    number
]
export interface Type_CommonMethod_linearGradient_value {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export type Tuple_Length_Length = [
    Length,
    Length
]
export interface Type_CommonMethod_sweepGradient_value {
    center: [ Length, Length ];
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export interface Type_CommonMethod_radialGradient_value {
    center: [ Length, Length ];
    radius: number | string;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export type Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult = (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult;
export type Callback_TouchEvent_HitTestMode = (parameter: TouchEvent) => HitTestMode;
export interface Literal_Alignment_align {
    align?: Alignment;
}
export interface CommonMethod {
    width(value: Length): this
    height(value: Length): this
    drawModifier(value: DrawModifier | undefined): this
    responseRegion(value: Array<Rectangle> | Rectangle): this
    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this
    size(value: SizeOptions): this
    constraintSize(value: ConstraintSizeOptions): this
    touchable(value: boolean): this
    hitTestBehavior(value: HitTestMode): this
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult)): this
    layoutWeight(value: number | string): this
    chainWeight(value: ChainWeightOptions): this
    padding(value: Padding | Length | LocalizedPadding): this
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this
    margin(value: Padding | Length | LocalizedPadding): this
    backgroundColor(value: ResourceColor): this
    pixelRound(value: PixelRoundPolicy): this
    backgroundImageSize(value: SizeOptions | ImageSize): this
    backgroundImagePosition(value: Position | Alignment): this
    backgroundEffect(value: BackgroundEffectOptions): this
    backgroundImageResizable(value: ResizableOptions): this
    foregroundEffect(value: ForegroundEffectOptions): this
    visualEffect(value: VisualEffect): this
    backgroundFilter(value: Filter): this
    foregroundFilter(value: Filter): this
    compositingFilter(value: Filter): this
    opacity(value: number | Resource): this
    border(value: BorderOptions): this
    borderStyle(value: BorderStyle | EdgeStyles): this
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this
    borderImage(value: BorderImageOption): this
    outline(value: OutlineOptions): this
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this
    outlineWidth(value: Dimension | EdgeOutlineWidths): this
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this
    outlineRadius(value: Dimension | OutlineRadiuses): this
    foregroundColor(value: ResourceColor | ColoringStrategy): this
    onClick(event: ((event: ClickEvent) => void), distanceThreshold?: number): this
    onHover(value: ((isHover: boolean,event: HoverEvent) => void)): this
    onAccessibilityHover(value: AccessibilityCallback): this
    hoverEffect(value: HoverEffect): this
    onMouse(value: ((event: MouseEvent) => void)): this
    onTouch(value: ((event: TouchEvent) => void)): this
    onKeyEvent(value: ((event: KeyEvent) => void)): this
    onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): this
    focusable(value: boolean): this
    onFocus(value: (() => void)): this
    onBlur(value: (() => void)): this
    tabIndex(value: number): this
    defaultFocus(value: boolean): this
    groupDefaultFocus(value: boolean): this
    focusOnTouch(value: boolean): this
    focusBox(value: FocusBoxStyle): this
    animation(value: AnimateParam): this
    transition(effect: TransitionOptions | TransitionEffect | TransitionEffect, onFinish?: TransitionFinishCallback): this
    motionBlur(value: MotionBlurOptions): this
    brightness(value: number): this
    contrast(value: number): this
    grayscale(value: number): this
    colorBlend(value: Color | string | Resource): this
    saturate(value: number): this
    sepia(value: number): this
    invert(value: number | InvertOptions): this
    hueRotate(value: number | string): this
    useShadowBatching(value: boolean): this
    useEffect(useEffect: boolean, effectType?: EffectType): this
    renderGroup(value: boolean): this
    freeze(value: boolean): this
    translate(value: TranslateOptions): this
    scale(value: ScaleOptions): this
    gridSpan(value: number): this
    gridOffset(value: number): this
    rotate(value: RotateOptions): this
    transform(value: TransformationMatrix): this
    onAppear(value: (() => void)): this
    onDisAppear(value: (() => void)): this
    onAttach(value: (() => void)): this
    onDetach(value: (() => void)): this
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void)): this
    visibility(value: Visibility): this
    flexGrow(value: number): this
    flexShrink(value: number): this
    flexBasis(value: number | string): this
    alignSelf(value: ItemAlign): this
    displayPriority(value: number): this
    zIndex(value: number): this
    direction(value: Direction): this
    align(value: Alignment): this
    position(value: Position | Edges | LocalizedEdges): this
    markAnchor(value: Position | LocalizedPosition): this
    offset(value: Position | Edges | LocalizedEdges): this
    enabled(value: boolean): this
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this
    aspectRatio(value: number): this
    clickEffect(value: ClickEffect | undefined): this
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)): this
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void)): this
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void)): this
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void)): this
    onDrop(value: ((event: DragEvent,extraParams?: string) => void)): this
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void)): this
    allowDrop(value: Array<UniformDataType> | undefined): this
    draggable(value: boolean): this
    dragPreview(value: CustomBuilder | DragItemInfo | string): this
    onPreDrag(value: ((parameter: PreDragStatus) => void)): this
    linearGradient(value: Type_CommonMethod_linearGradient_value): this
    sweepGradient(value: Type_CommonMethod_sweepGradient_value): this
    radialGradient(value: Type_CommonMethod_radialGradient_value): this
    motionPath(value: MotionPathOptions): this
    shadow(value: ShadowOptions | ShadowStyle): this
    clip(value: boolean | undefined): this
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this
    mask(value: ProgressMask | undefined): this
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this
    key(value: string): this
    id(value: string): this
    geometryTransition(id: string, options?: GeometryTransitionOptions): this
    stateStyles(value: StateStyles): this
    restoreId(value: number): this
    sphericalEffect(value: number): this
    lightUpEffect(value: number): this
    pixelStretchEffect(value: PixelStretchEffectOptions): this
    accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions): this
    accessibilityText(value: string | Resource): this
    accessibilityTextHint(value: string): this
    accessibilityDescription(value: string | Resource): this
    accessibilityLevel(value: string): this
    accessibilityVirtualNode(value: CustomBuilder): this
    accessibilityChecked(value: boolean): this
    accessibilitySelected(value: boolean): this
    obscured(value: Array<ObscuredReasons>): this
    reuseId(value: string): this
    renderFit(value: RenderFit): this
    gestureModifier(value: GestureModifier): this
    backgroundBrightness(value: BackgroundBrightnessOptions): this
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)): this
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean): this
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this
    monopolizeEvents(value: boolean): this
    onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): this
    onSizeChange(value: SizeChangeCallback): this
    customProperty(name: string, value: Object | undefined): this
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this
    background(builder: CustomBuilder, options?: Literal_Alignment_align): this
    backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): this
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this
    focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this
    focusScopePriority(scopeId: string, priority?: FocusPriority): this
    gesture(gesture: GestureType, mask?: GestureMask): this
    priorityGesture(gesture: GestureType, mask?: GestureMask): this
    parallelGesture(gesture: GestureType, mask?: GestureMask): this
    blur(value: number, options?: BlurOptions): this
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this
    systemBarEffect(): this
    backdropBlur(value: number, options?: BlurOptions): this
    sharedTransition(id: string, options?: sharedTransitionOptions): this
    chainMode(direction: Axis, style: ChainStyle): this
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this
    overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): this
    blendMode(value: BlendMode, type?: BlendApplyType): this
    advancedBlendMode(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): this
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this
    bindMenu(isShow: Array<MenuElement> | CustomBuilder | boolean, content?: MenuOptions | Array<MenuElement> | CustomBuilder, options?: MenuOptions): this
    bindContextMenu(content: CustomBuilder | boolean, responseType: ResponseType | CustomBuilder, options?: ContextMenuOptions): this
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this
    onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this
    attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this
}
export interface UICommonMethod extends UICommonBase {
    /** @memo */
    width(value: Length): this
    /** @memo */
    height(value: Length): this
    /** @memo */
    drawModifier(value: DrawModifier | undefined): this
    /** @memo */
    responseRegion(value: Array<Rectangle> | Rectangle): this
    /** @memo */
    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this
    /** @memo */
    size(value: SizeOptions): this
    /** @memo */
    constraintSize(value: ConstraintSizeOptions): this
    /** @memo */
    touchable(value: boolean): this
    /** @memo */
    hitTestBehavior(value: HitTestMode): this
    /** @memo */
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult)): this
    /** @memo */
    layoutWeight(value: number | string): this
    /** @memo */
    chainWeight(value: ChainWeightOptions): this
    /** @memo */
    padding(value: Padding | Length | LocalizedPadding): this
    /** @memo */
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this
    /** @memo */
    margin(value: Padding | Length | LocalizedPadding): this
    /** @memo */
    backgroundColor(value: ResourceColor): this
    /** @memo */
    pixelRound(value: PixelRoundPolicy): this
    /** @memo */
    backgroundImageSize(value: SizeOptions | ImageSize): this
    /** @memo */
    backgroundImagePosition(value: Position | Alignment): this
    /** @memo */
    backgroundEffect(value: BackgroundEffectOptions): this
    /** @memo */
    backgroundImageResizable(value: ResizableOptions): this
    /** @memo */
    foregroundEffect(value: ForegroundEffectOptions): this
    /** @memo */
    visualEffect(value: VisualEffect): this
    /** @memo */
    backgroundFilter(value: Filter): this
    /** @memo */
    foregroundFilter(value: Filter): this
    /** @memo */
    compositingFilter(value: Filter): this
    /** @memo */
    opacity(value: number | Resource): this
    /** @memo */
    border(value: BorderOptions): this
    /** @memo */
    borderStyle(value: BorderStyle | EdgeStyles): this
    /** @memo */
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this
    /** @memo */
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this
    /** @memo */
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this
    /** @memo */
    borderImage(value: BorderImageOption): this
    /** @memo */
    outline(value: OutlineOptions): this
    /** @memo */
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this
    /** @memo */
    outlineWidth(value: Dimension | EdgeOutlineWidths): this
    /** @memo */
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this
    /** @memo */
    outlineRadius(value: Dimension | OutlineRadiuses): this
    /** @memo */
    foregroundColor(value: ResourceColor | ColoringStrategy): this
    /** @memo */
    onClick(event: ((event: ClickEvent) => void), distanceThreshold?: number): this
    /** @memo */
    onHover(value: ((isHover: boolean,event: HoverEvent) => void)): this
    /** @memo */
    onAccessibilityHover(value: AccessibilityCallback): this
    /** @memo */
    hoverEffect(value: HoverEffect): this
    /** @memo */
    onMouse(value: ((event: MouseEvent) => void)): this
    /** @memo */
    onTouch(value: ((event: TouchEvent) => void)): this
    /** @memo */
    onKeyEvent(value: ((event: KeyEvent) => void)): this
    /** @memo */
    onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): this
    /** @memo */
    focusable(value: boolean): this
    /** @memo */
    onFocus(value: (() => void)): this
    /** @memo */
    onBlur(value: (() => void)): this
    /** @memo */
    tabIndex(value: number): this
    /** @memo */
    defaultFocus(value: boolean): this
    /** @memo */
    groupDefaultFocus(value: boolean): this
    /** @memo */
    focusOnTouch(value: boolean): this
    /** @memo */
    focusBox(value: FocusBoxStyle): this
    /** @memo */
    animation(value: AnimateParam): this
    /** @memo */
    transition(effect: TransitionOptions | TransitionEffect | TransitionEffect, onFinish?: TransitionFinishCallback): this
    /** @memo */
    motionBlur(value: MotionBlurOptions): this
    /** @memo */
    brightness(value: number): this
    /** @memo */
    contrast(value: number): this
    /** @memo */
    grayscale(value: number): this
    /** @memo */
    colorBlend(value: Color | string | Resource): this
    /** @memo */
    saturate(value: number): this
    /** @memo */
    sepia(value: number): this
    /** @memo */
    invert(value: number | InvertOptions): this
    /** @memo */
    hueRotate(value: number | string): this
    /** @memo */
    useShadowBatching(value: boolean): this
    /** @memo */
    useEffect(useEffect: boolean, effectType?: EffectType): this
    /** @memo */
    renderGroup(value: boolean): this
    /** @memo */
    freeze(value: boolean): this
    /** @memo */
    translate(value: TranslateOptions): this
    /** @memo */
    scale(value: ScaleOptions): this
    /** @memo */
    gridSpan(value: number): this
    /** @memo */
    gridOffset(value: number): this
    /** @memo */
    rotate(value: RotateOptions): this
    /** @memo */
    transform(value: TransformationMatrix): this
    /** @memo */
    onAppear(value: (() => void)): this
    /** @memo */
    onDisAppear(value: (() => void)): this
    /** @memo */
    onAttach(value: (() => void)): this
    /** @memo */
    onDetach(value: (() => void)): this
    /** @memo */
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void)): this
    /** @memo */
    visibility(value: Visibility): this
    /** @memo */
    flexGrow(value: number): this
    /** @memo */
    flexShrink(value: number): this
    /** @memo */
    flexBasis(value: number | string): this
    /** @memo */
    alignSelf(value: ItemAlign): this
    /** @memo */
    displayPriority(value: number): this
    /** @memo */
    zIndex(value: number): this
    /** @memo */
    direction(value: Direction): this
    /** @memo */
    align(value: Alignment): this
    /** @memo */
    position(value: Position | Edges | LocalizedEdges): this
    /** @memo */
    markAnchor(value: Position | LocalizedPosition): this
    /** @memo */
    offset(value: Position | Edges | LocalizedEdges): this
    /** @memo */
    enabled(value: boolean): this
    /** @memo */
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this
    /** @memo */
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this
    /** @memo */
    aspectRatio(value: number): this
    /** @memo */
    clickEffect(value: ClickEffect | undefined): this
    /** @memo */
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)): this
    /** @memo */
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void)): this
    /** @memo */
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void)): this
    /** @memo */
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void)): this
    /** @memo */
    onDrop(value: ((event: DragEvent,extraParams?: string) => void)): this
    /** @memo */
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void)): this
    /** @memo */
    allowDrop(value: Array<UniformDataType> | undefined): this
    /** @memo */
    draggable(value: boolean): this
    /** @memo */
    dragPreview(value: CustomBuilder | DragItemInfo | string): this
    /** @memo */
    onPreDrag(value: ((parameter: PreDragStatus) => void)): this
    /** @memo */
    linearGradient(value: Type_CommonMethod_linearGradient_value): this
    /** @memo */
    sweepGradient(value: Type_CommonMethod_sweepGradient_value): this
    /** @memo */
    radialGradient(value: Type_CommonMethod_radialGradient_value): this
    /** @memo */
    motionPath(value: MotionPathOptions): this
    /** @memo */
    shadow(value: ShadowOptions | ShadowStyle): this
    /** @memo */
    clip(value: boolean | undefined): this
    /** @memo */
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this
    /** @memo */
    mask(value: ProgressMask | undefined): this
    /** @memo */
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this
    /** @memo */
    key(value: string): this
    /** @memo */
    id(value: string): this
    /** @memo */
    geometryTransition(id: string, options?: GeometryTransitionOptions): this
    /** @memo */
    stateStyles(value: StateStyles): this
    /** @memo */
    restoreId(value: number): this
    /** @memo */
    sphericalEffect(value: number): this
    /** @memo */
    lightUpEffect(value: number): this
    /** @memo */
    pixelStretchEffect(value: PixelStretchEffectOptions): this
    /** @memo */
    accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions): this
    /** @memo */
    accessibilityText(value: string | Resource): this
    /** @memo */
    accessibilityTextHint(value: string): this
    /** @memo */
    accessibilityDescription(value: string | Resource): this
    /** @memo */
    accessibilityLevel(value: string): this
    /** @memo */
    accessibilityVirtualNode(value: CustomBuilder): this
    /** @memo */
    accessibilityChecked(value: boolean): this
    /** @memo */
    accessibilitySelected(value: boolean): this
    /** @memo */
    obscured(value: Array<ObscuredReasons>): this
    /** @memo */
    reuseId(value: string): this
    /** @memo */
    renderFit(value: RenderFit): this
    /** @memo */
    gestureModifier(value: GestureModifier): this
    /** @memo */
    backgroundBrightness(value: BackgroundBrightnessOptions): this
    /** @memo */
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)): this
    /** @memo */
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean): this
    /** @memo */
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this
    /** @memo */
    monopolizeEvents(value: boolean): this
    /** @memo */
    onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): this
    /** @memo */
    onSizeChange(value: SizeChangeCallback): this
    /** @memo */
    customProperty(name: string, value: Object | undefined): this
    /** @memo */
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this
    /** @memo */
    background(builder: CustomBuilder, options?: Literal_Alignment_align): this
    /** @memo */
    backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): this
    /** @memo */
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this
    /** @memo */
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this
    /** @memo */
    focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this
    /** @memo */
    focusScopePriority(scopeId: string, priority?: FocusPriority): this
    /** @memo */
    gesture(gesture: GestureType, mask?: GestureMask): this
    /** @memo */
    priorityGesture(gesture: GestureType, mask?: GestureMask): this
    /** @memo */
    parallelGesture(gesture: GestureType, mask?: GestureMask): this
    /** @memo */
    blur(value: number, options?: BlurOptions): this
    /** @memo */
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this
    /** @memo */
    systemBarEffect(): this
    /** @memo */
    backdropBlur(value: number, options?: BlurOptions): this
    /** @memo */
    sharedTransition(id: string, options?: sharedTransitionOptions): this
    /** @memo */
    chainMode(direction: Axis, style: ChainStyle): this
    /** @memo */
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this
    /** @memo */
    overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): this
    /** @memo */
    blendMode(value: BlendMode, type?: BlendApplyType): this
    /** @memo */
    advancedBlendMode(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): this
    /** @memo */
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this
    /** @memo */
    bindMenu(isShow: Array<MenuElement> | CustomBuilder | boolean, content?: MenuOptions | Array<MenuElement> | CustomBuilder, options?: MenuOptions): this
    /** @memo */
    bindContextMenu(content: CustomBuilder | boolean, responseType: ResponseType | CustomBuilder, options?: ContextMenuOptions): this
    /** @memo */
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this
    /** @memo */
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this
    /** @memo */
    onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this
    /** @memo */
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this
    /** @memo */
    attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCommonMethodStyle implements CommonMethod {
    width_value?: Length
    height_value?: Length
    drawModifier_value?: DrawModifier | undefined
    responseRegion_value?: Array<Rectangle> | Rectangle
    mouseResponseRegion_value?: Array<Rectangle> | Rectangle
    size_value?: SizeOptions
    constraintSize_value?: ConstraintSizeOptions
    touchable_value?: boolean
    hitTestBehavior_value?: HitTestMode
    onChildTouchTest_value?: ((value: Array<TouchTestInfo>) => TouchResult)
    layoutWeight_value?: number | string
    chainWeight_value?: ChainWeightOptions
    padding_value?: Padding | Length | LocalizedPadding
    safeAreaPadding_value?: Padding | LengthMetrics | LocalizedPadding
    margin_value?: Padding | Length | LocalizedPadding
    backgroundColor_value?: ResourceColor
    pixelRound_value?: PixelRoundPolicy
    backgroundImageSize_value?: SizeOptions | ImageSize
    backgroundImagePosition_value?: Position | Alignment
    backgroundEffect_value?: BackgroundEffectOptions
    backgroundImageResizable_value?: ResizableOptions
    foregroundEffect_value?: ForegroundEffectOptions
    visualEffect_value?: VisualEffect
    backgroundFilter_value?: Filter
    foregroundFilter_value?: Filter
    compositingFilter_value?: Filter
    opacity_value?: number | Resource
    border_value?: BorderOptions
    borderStyle_value?: BorderStyle | EdgeStyles
    borderWidth_value?: Length | EdgeWidths | LocalizedEdgeWidths
    borderColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors
    borderRadius_value?: Length | BorderRadiuses | LocalizedBorderRadiuses
    borderImage_value?: BorderImageOption
    outline_value?: OutlineOptions
    outlineStyle_value?: OutlineStyle | EdgeOutlineStyles
    outlineWidth_value?: Dimension | EdgeOutlineWidths
    outlineColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors
    outlineRadius_value?: Dimension | OutlineRadiuses
    foregroundColor_value?: ResourceColor | ColoringStrategy
    onClick_value?: ((event: ClickEvent) => void)
    onHover_value?: ((isHover: boolean,event: HoverEvent) => void)
    onAccessibilityHover_value?: AccessibilityCallback
    hoverEffect_value?: HoverEffect
    onMouse_value?: ((event: MouseEvent) => void)
    onTouch_value?: ((event: TouchEvent) => void)
    onKeyEvent_value?: ((event: KeyEvent) => void)
    onKeyPreIme_value?: ((parameter: KeyEvent) => boolean)
    focusable_value?: boolean
    onFocus_value?: (() => void)
    onBlur_value?: (() => void)
    tabIndex_value?: number
    defaultFocus_value?: boolean
    groupDefaultFocus_value?: boolean
    focusOnTouch_value?: boolean
    focusBox_value?: FocusBoxStyle
    animation_value?: AnimateParam
    transition_value?: TransitionOptions | TransitionEffect
    motionBlur_value?: MotionBlurOptions
    brightness_value?: number
    contrast_value?: number
    grayscale_value?: number
    colorBlend_value?: Color | string | Resource
    saturate_value?: number
    sepia_value?: number
    invert_value?: number | InvertOptions
    hueRotate_value?: number | string
    useShadowBatching_value?: boolean
    useEffect_value?: boolean
    renderGroup_value?: boolean
    freeze_value?: boolean
    translate_value?: TranslateOptions
    scale_value?: ScaleOptions
    gridSpan_value?: number
    gridOffset_value?: number
    rotate_value?: RotateOptions
    transform_value?: TransformationMatrix
    onAppear_value?: (() => void)
    onDisAppear_value?: (() => void)
    onAttach_value?: (() => void)
    onDetach_value?: (() => void)
    onAreaChange_value?: ((oldValue: Area,newValue: Area) => void)
    visibility_value?: Visibility
    flexGrow_value?: number
    flexShrink_value?: number
    flexBasis_value?: number | string
    alignSelf_value?: ItemAlign
    displayPriority_value?: number
    zIndex_value?: number
    direction_value?: Direction
    align_value?: Alignment
    position_value?: Position | Edges | LocalizedEdges
    markAnchor_value?: Position | LocalizedPosition
    offset_value?: Position | Edges | LocalizedEdges
    enabled_value?: boolean
    useSizeType_value?: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs
    alignRules_value?: AlignRuleOption
    aspectRatio_value?: number
    clickEffect_value?: ClickEffect | undefined
    onDragStart_value?: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)
    onDragEnter_value?: ((event: DragEvent,extraParams?: string) => void)
    onDragMove_value?: ((event: DragEvent,extraParams?: string) => void)
    onDragLeave_value?: ((event: DragEvent,extraParams?: string) => void)
    onDrop_value?: ((event: DragEvent,extraParams?: string) => void)
    onDragEnd_value?: ((event: DragEvent,extraParams?: string) => void)
    allowDrop_value?: Array<UniformDataType> | undefined
    draggable_value?: boolean
    dragPreview_value?: CustomBuilder | DragItemInfo | string
    onPreDrag_value?: ((parameter: PreDragStatus) => void)
    linearGradient_value?: Type_CommonMethod_linearGradient_value
    sweepGradient_value?: Type_CommonMethod_sweepGradient_value
    radialGradient_value?: Type_CommonMethod_radialGradient_value
    motionPath_value?: MotionPathOptions
    shadow_value?: ShadowOptions | ShadowStyle
    clip_value?: boolean | undefined
    clipShape_value?: CircleShape | EllipseShape | PathShape | RectShape
    mask_value?: ProgressMask | undefined
    maskShape_value?: CircleShape | EllipseShape | PathShape | RectShape
    key_value?: string
    id_value?: string
    geometryTransition_value?: string
    stateStyles_value?: StateStyles
    restoreId_value?: number
    sphericalEffect_value?: number
    lightUpEffect_value?: number
    pixelStretchEffect_value?: PixelStretchEffectOptions
    accessibilityGroup_value?: boolean
    accessibilityText_value?: string
    accessibilityTextHint_value?: string
    accessibilityDescription_value?: string
    accessibilityLevel_value?: string
    accessibilityVirtualNode_value?: CustomBuilder
    accessibilityChecked_value?: boolean
    accessibilitySelected_value?: boolean
    obscured_value?: Array<ObscuredReasons>
    reuseId_value?: string
    renderFit_value?: RenderFit
    gestureModifier_value?: GestureModifier
    backgroundBrightness_value?: BackgroundBrightnessOptions
    onGestureJudgeBegin_value?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)
    onGestureRecognizerJudgeBegin_value?: GestureRecognizerJudgeBeginCallback
    shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback
    monopolizeEvents_value?: boolean
    onTouchIntercept_value?: ((parameter: TouchEvent) => HitTestMode)
    onSizeChange_value?: SizeChangeCallback
    public width(value: Length): this {
        return this
    }
    public height(value: Length): this {
        return this
    }
    public drawModifier(value: DrawModifier | undefined): this {
        return this
    }
    public responseRegion(value: Array<Rectangle> | Rectangle): this {
        return this
    }
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
        return this
    }
    public size(value: SizeOptions): this {
        return this
    }
    public constraintSize(value: ConstraintSizeOptions): this {
        return this
    }
    public touchable(value: boolean): this {
        return this
    }
    public hitTestBehavior(value: HitTestMode): this {
        return this
    }
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult)): this {
        return this
    }
    public layoutWeight(value: number | string): this {
        return this
    }
    public chainWeight(value: ChainWeightOptions): this {
        return this
    }
    public padding(value: Padding | Length | LocalizedPadding): this {
        return this
    }
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this {
        return this
    }
    public margin(value: Padding | Length | LocalizedPadding): this {
        return this
    }
    public backgroundColor(value: ResourceColor): this {
        return this
    }
    public pixelRound(value: PixelRoundPolicy): this {
        return this
    }
    public backgroundImageSize(value: SizeOptions | ImageSize): this {
        return this
    }
    public backgroundImagePosition(value: Position | Alignment): this {
        return this
    }
    public backgroundEffect(value: BackgroundEffectOptions): this {
        return this
    }
    public backgroundImageResizable(value: ResizableOptions): this {
        return this
    }
    public foregroundEffect(value: ForegroundEffectOptions): this {
        return this
    }
    public visualEffect(value: VisualEffect): this {
        return this
    }
    public backgroundFilter(value: Filter): this {
        return this
    }
    public foregroundFilter(value: Filter): this {
        return this
    }
    public compositingFilter(value: Filter): this {
        return this
    }
    public opacity(value: number | Resource): this {
        return this
    }
    public border(value: BorderOptions): this {
        return this
    }
    public borderStyle(value: BorderStyle | EdgeStyles): this {
        return this
    }
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this {
        return this
    }
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        return this
    }
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
        return this
    }
    public borderImage(value: BorderImageOption): this {
        return this
    }
    public outline(value: OutlineOptions): this {
        return this
    }
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
        return this
    }
    public outlineWidth(value: Dimension | EdgeOutlineWidths): this {
        return this
    }
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        return this
    }
    public outlineRadius(value: Dimension | OutlineRadiuses): this {
        return this
    }
    public foregroundColor(value: ResourceColor | ColoringStrategy): this {
        return this
    }
    public onClick(event: ((event: ClickEvent) => void), distanceThreshold?: number): this {
        return this
    }
    public onHover(value: ((isHover: boolean,event: HoverEvent) => void)): this {
        return this
    }
    public onAccessibilityHover(value: AccessibilityCallback): this {
        return this
    }
    public hoverEffect(value: HoverEffect): this {
        return this
    }
    public onMouse(value: ((event: MouseEvent) => void)): this {
        return this
    }
    public onTouch(value: ((event: TouchEvent) => void)): this {
        return this
    }
    public onKeyEvent(value: ((event: KeyEvent) => void)): this {
        return this
    }
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): this {
        return this
    }
    public focusable(value: boolean): this {
        return this
    }
    public onFocus(value: (() => void)): this {
        return this
    }
    public onBlur(value: (() => void)): this {
        return this
    }
    public tabIndex(value: number): this {
        return this
    }
    public defaultFocus(value: boolean): this {
        return this
    }
    public groupDefaultFocus(value: boolean): this {
        return this
    }
    public focusOnTouch(value: boolean): this {
        return this
    }
    public focusBox(value: FocusBoxStyle): this {
        return this
    }
    public animation(value: AnimateParam): this {
        return this
    }
    public transition(effect: TransitionOptions | TransitionEffect | TransitionEffect, onFinish?: TransitionFinishCallback): this {
        return this
    }
    public motionBlur(value: MotionBlurOptions): this {
        return this
    }
    public brightness(value: number): this {
        return this
    }
    public contrast(value: number): this {
        return this
    }
    public grayscale(value: number): this {
        return this
    }
    public colorBlend(value: Color | string | Resource): this {
        return this
    }
    public saturate(value: number): this {
        return this
    }
    public sepia(value: number): this {
        return this
    }
    public invert(value: number | InvertOptions): this {
        return this
    }
    public hueRotate(value: number | string): this {
        return this
    }
    public useShadowBatching(value: boolean): this {
        return this
    }
    public useEffect(useEffect: boolean, effectType?: EffectType): this {
        return this
    }
    public renderGroup(value: boolean): this {
        return this
    }
    public freeze(value: boolean): this {
        return this
    }
    public translate(value: TranslateOptions): this {
        return this
    }
    public scale(value: ScaleOptions): this {
        return this
    }
    public gridSpan(value: number): this {
        return this
    }
    public gridOffset(value: number): this {
        return this
    }
    public rotate(value: RotateOptions): this {
        return this
    }
    public transform(value: TransformationMatrix): this {
        return this
    }
    public onAppear(value: (() => void)): this {
        return this
    }
    public onDisAppear(value: (() => void)): this {
        return this
    }
    public onAttach(value: (() => void)): this {
        return this
    }
    public onDetach(value: (() => void)): this {
        return this
    }
    public onAreaChange(value: ((oldValue: Area,newValue: Area) => void)): this {
        return this
    }
    public visibility(value: Visibility): this {
        return this
    }
    public flexGrow(value: number): this {
        return this
    }
    public flexShrink(value: number): this {
        return this
    }
    public flexBasis(value: number | string): this {
        return this
    }
    public alignSelf(value: ItemAlign): this {
        return this
    }
    public displayPriority(value: number): this {
        return this
    }
    public zIndex(value: number): this {
        return this
    }
    public direction(value: Direction): this {
        return this
    }
    public align(value: Alignment): this {
        return this
    }
    public position(value: Position | Edges | LocalizedEdges): this {
        return this
    }
    public markAnchor(value: Position | LocalizedPosition): this {
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges): this {
        return this
    }
    public enabled(value: boolean): this {
        return this
    }
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this {
        return this
    }
    public alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this {
        return this
    }
    public aspectRatio(value: number): this {
        return this
    }
    public clickEffect(value: ClickEffect | undefined): this {
        return this
    }
    public onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)): this {
        return this
    }
    public onDragEnter(value: ((event: DragEvent,extraParams?: string) => void)): this {
        return this
    }
    public onDragMove(value: ((event: DragEvent,extraParams?: string) => void)): this {
        return this
    }
    public onDragLeave(value: ((event: DragEvent,extraParams?: string) => void)): this {
        return this
    }
    public onDrop(value: ((event: DragEvent,extraParams?: string) => void)): this {
        return this
    }
    public onDragEnd(value: ((event: DragEvent,extraParams?: string) => void)): this {
        return this
    }
    public allowDrop(value: Array<UniformDataType> | undefined): this {
        return this
    }
    public draggable(value: boolean): this {
        return this
    }
    public dragPreview(value: CustomBuilder | DragItemInfo | string): this {
        return this
    }
    public onPreDrag(value: ((parameter: PreDragStatus) => void)): this {
        return this
    }
    public linearGradient(value: Type_CommonMethod_linearGradient_value): this {
        return this
    }
    public sweepGradient(value: Type_CommonMethod_sweepGradient_value): this {
        return this
    }
    public radialGradient(value: Type_CommonMethod_radialGradient_value): this {
        return this
    }
    public motionPath(value: MotionPathOptions): this {
        return this
    }
    public shadow(value: ShadowOptions | ShadowStyle): this {
        return this
    }
    public clip(value: boolean | undefined): this {
        return this
    }
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        return this
    }
    public mask(value: ProgressMask | undefined): this {
        return this
    }
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        return this
    }
    public key(value: string): this {
        return this
    }
    public id(value: string): this {
        return this
    }
    public geometryTransition(id: string, options?: GeometryTransitionOptions): this {
        return this
    }
    public stateStyles(value: StateStyles): this {
        return this
    }
    public restoreId(value: number): this {
        return this
    }
    public sphericalEffect(value: number): this {
        return this
    }
    public lightUpEffect(value: number): this {
        return this
    }
    public pixelStretchEffect(value: PixelStretchEffectOptions): this {
        return this
    }
    public accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions): this {
        return this
    }
    public accessibilityText(value: string | Resource): this {
        return this
    }
    public accessibilityTextHint(value: string): this {
        return this
    }
    public accessibilityDescription(value: string | Resource): this {
        return this
    }
    public accessibilityLevel(value: string): this {
        return this
    }
    public accessibilityVirtualNode(value: CustomBuilder): this {
        return this
    }
    public accessibilityChecked(value: boolean): this {
        return this
    }
    public accessibilitySelected(value: boolean): this {
        return this
    }
    public obscured(value: Array<ObscuredReasons>): this {
        return this
    }
    public reuseId(value: string): this {
        return this
    }
    public renderFit(value: RenderFit): this {
        return this
    }
    public gestureModifier(value: GestureModifier): this {
        return this
    }
    public backgroundBrightness(value: BackgroundBrightnessOptions): this {
        return this
    }
    public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)): this {
        return this
    }
    public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean): this {
        return this
    }
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this {
        return this
    }
    public monopolizeEvents(value: boolean): this {
        return this
    }
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): this {
        return this
    }
    public onSizeChange(value: SizeChangeCallback): this {
        return this
    }
    public customProperty(name: string, value: Object | undefined): this {
        return this
    }
    public expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        return this
    }
    public background(builder: CustomBuilder, options?: Literal_Alignment_align): this {
        return this
    }
    public backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): this {
        return this
    }
    public backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        return this
    }
    public foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
        return this
    }
    public focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this {
        return this
    }
    public focusScopePriority(scopeId: string, priority?: FocusPriority): this {
        return this
    }
    public gesture(gesture: GestureType, mask?: GestureMask): this {
        return this
    }
    public priorityGesture(gesture: GestureType, mask?: GestureMask): this {
        return this
    }
    public parallelGesture(gesture: GestureType, mask?: GestureMask): this {
        return this
    }
    public blur(value: number, options?: BlurOptions): this {
        return this
    }
    public linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
        return this
    }
    public systemBarEffect(): this {
        return this
    }
    public backdropBlur(value: number, options?: BlurOptions): this {
        return this
    }
    public sharedTransition(id: string, options?: sharedTransitionOptions): this {
        return this
    }
    public chainMode(direction: Axis, style: ChainStyle): this {
        return this
    }
    public dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this {
        return this
    }
    public overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): this {
        return this
    }
    public blendMode(value: BlendMode, type?: BlendApplyType): this {
        return this
    }
    public advancedBlendMode(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): this {
        return this
    }
    public bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        return this
    }
    public bindMenu(isShow: Array<MenuElement> | CustomBuilder | boolean, content?: MenuOptions | Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
        return this
    }
    public bindContextMenu(content: CustomBuilder | boolean, responseType: ResponseType | CustomBuilder, options?: ContextMenuOptions): this {
        return this
    }
    public bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
        return this
    }
    public bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this {
        return this
    }
    public onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this {
        return this
    }
    public keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: UICommonMethod): void {
    }
}
export interface CommonAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<CommonAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICommonAttribute extends UICommonMethod {
    /** @memo */
    attributeModifier(value: AttributeModifier<CommonAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCommonStyle extends ArkCommonMethodStyle implements CommonAttribute {
    public attributeModifier(value: AttributeModifier<CommonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export type CustomBuilder = 
/** @memo */
() => void;
export interface OverlayOptions {
    align?: Alignment;
    offset?: OverlayOffset;
}
export interface OverlayOffset {
    x?: number;
    y?: number;
}
export type FractionStop = [
    number,
    number
]
export interface CommonShapeMethod extends CommonMethod {
    stroke(value: ResourceColor): this
    fill(value: ResourceColor): this
    strokeDashOffset(value: number | string): this
    strokeLineCap(value: LineCapStyle): this
    strokeLineJoin(value: LineJoinStyle): this
    strokeMiterLimit(value: number | string): this
    strokeOpacity(value: number | string | Resource): this
    fillOpacity(value: number | string | Resource): this
    strokeWidth(value: Length): this
    antiAlias(value: boolean): this
    strokeDashArray(value: Array<Length>): this
    attributeModifier(value: AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICommonShapeMethod extends UICommonMethod {
    /** @memo */
    stroke(value: ResourceColor): this
    /** @memo */
    fill(value: ResourceColor): this
    /** @memo */
    strokeDashOffset(value: number | string): this
    /** @memo */
    strokeLineCap(value: LineCapStyle): this
    /** @memo */
    strokeLineJoin(value: LineJoinStyle): this
    /** @memo */
    strokeMiterLimit(value: number | string): this
    /** @memo */
    strokeOpacity(value: number | string | Resource): this
    /** @memo */
    fillOpacity(value: number | string | Resource): this
    /** @memo */
    strokeWidth(value: Length): this
    /** @memo */
    antiAlias(value: boolean): this
    /** @memo */
    strokeDashArray(value: Array<Length>): this
    /** @memo */
    attributeModifier(value: AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCommonShapeMethodStyle extends ArkCommonMethodStyle implements CommonShapeMethod {
    stroke_value?: ResourceColor
    fill_value?: ResourceColor
    strokeDashOffset_value?: number | string
    strokeLineCap_value?: LineCapStyle
    strokeLineJoin_value?: LineJoinStyle
    strokeMiterLimit_value?: number | string
    strokeOpacity_value?: number | string | Resource
    fillOpacity_value?: number | string | Resource
    strokeWidth_value?: Length
    antiAlias_value?: boolean
    strokeDashArray_value?: Array<Length>
    public stroke(value: ResourceColor): this {
        return this
    }
    public fill(value: ResourceColor): this {
        return this
    }
    public strokeDashOffset(value: number | string): this {
        return this
    }
    public strokeLineCap(value: LineCapStyle): this {
        return this
    }
    public strokeLineJoin(value: LineJoinStyle): this {
        return this
    }
    public strokeMiterLimit(value: number | string): this {
        return this
    }
    public strokeOpacity(value: number | string | Resource): this {
        return this
    }
    public fillOpacity(value: number | string | Resource): this {
        return this
    }
    public strokeWidth(value: Length): this {
        return this
    }
    public antiAlias(value: boolean): this {
        return this
    }
    public strokeDashArray(value: Array<Length>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface LinearGradient_common {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export interface PixelRoundPolicy {
    start?: PixelRoundCalcPolicy;
    top?: PixelRoundCalcPolicy;
    end?: PixelRoundCalcPolicy;
    bottom?: PixelRoundCalcPolicy;
}
export interface LinearGradientBlurOptions {
    fractionStops: Array<FractionStop>;
    direction: GradientDirection;
}
export interface MotionBlurAnchor {
    x: number;
    y: number;
}
export interface MotionBlurOptions {
    radius: number;
    anchor: MotionBlurAnchor;
}
export interface LayoutBorderInfo {
    borderWidth: EdgeWidths;
    margin: Padding;
    padding: Padding;
}
export interface LayoutInfo {
    position: Position;
    constraint: ConstraintSizeOptions;
}
export interface LayoutChild {
    stub: string;
}
export interface GeometryInfo extends SizeResult {
    borderWidth: EdgeWidths;
    margin: Padding;
    padding: Padding;
}
export interface Layoutable {
    stub: string;
}
export interface SizeResult {
    width: number;
    height: number;
}
export interface MeasureResult extends SizeResult {
}
export interface NavDestinationInfo {
    _NavDestinationInfoStub: string;
}
export interface NavigationInfo {
    _NavigationInfoStub: string;
}
export interface RouterPageInfo {
    _RouterPageInfoStub: string;
}
export interface Theme {
    _ThemeStub: string;
}
export interface Literal_Empty {
}
export interface RectResult {
    x: number;
    y: number;
    width: number;
    height: number;
}
export interface CaretOffset {
    index: number;
    x: number;
    y: number;
}
export enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2
}
export interface ScrollableCommonMethod extends CommonMethod {
    scrollBar(value: BarState): this
    scrollBarColor(value: Color | number | string): this
    scrollBarWidth(value: number | string): this
    nestedScroll(value: NestedScrollOptions): this
    enableScrollInteraction(value: boolean): this
    friction(value: number | Resource): this
    onScroll(value: ((first: number,last: number) => void)): this
    onReachStart(value: (() => void)): this
    onReachEnd(value: (() => void)): this
    onScrollStart(value: (() => void)): this
    onScrollStop(value: (() => void)): this
    flingSpeedLimit(value: number): this
    clipContent(value: ContentClipMode | RectShape): this
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this
    attributeModifier(value: AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIScrollableCommonMethod extends UICommonMethod {
    /** @memo */
    scrollBar(value: BarState): this
    /** @memo */
    scrollBarColor(value: Color | number | string): this
    /** @memo */
    scrollBarWidth(value: number | string): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onReachStart(value: (() => void)): this
    /** @memo */
    onReachEnd(value: (() => void)): this
    /** @memo */
    onScrollStart(value: (() => void)): this
    /** @memo */
    onScrollStop(value: (() => void)): this
    /** @memo */
    flingSpeedLimit(value: number): this
    /** @memo */
    clipContent(value: ContentClipMode | RectShape): this
    /** @memo */
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this
    /** @memo */
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this
    /** @memo */
    attributeModifier(value: AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkScrollableCommonMethodStyle extends ArkCommonMethodStyle implements ScrollableCommonMethod {
    public scrollBar(value: BarState): this {
        return this
    }
    public scrollBarColor(value: Color | number | string): this {
        return this
    }
    public scrollBarWidth(value: number | string): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions): this {
        return this
    }
    public enableScrollInteraction(value: boolean): this {
        return this
    }
    public friction(value: number | Resource): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void)): this {
        return this
    }
    public onReachStart(value: (() => void)): this {
        return this
    }
    public onReachEnd(value: (() => void)): this {
        return this
    }
    public onScrollStart(value: (() => void)): this {
        return this
    }
    public onScrollStop(value: (() => void)): this {
        return this
    }
    public flingSpeedLimit(value: number): this {
        return this
    }
    public clipContent(value: ContentClipMode | RectShape): this {
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        return this
    }
    public fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface ScrollResult {
    offsetRemain: number;
}
export interface OnWillScrollCallback {
    stub: string;
}
export type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
export type OnMoveHandler = (from: number, to: number) => void;
export interface DynamicNode<T> {
}
export interface EdgeEffectOptions {
    alwaysEnabled: boolean;
}
export interface BackgroundBrightnessOptions {
    rate: number;
    lightUpDegree: number;
}
export interface PointLightStyle {
    lightSource?: LightSource;
    illuminated?: IlluminatedType;
    bloom?: number;
}
export interface LightSource {
    positionX: Dimension;
    positionY: Dimension;
    positionZ: Dimension;
    intensity: number;
    color?: ResourceColor;
}
export interface KeyframeAnimateParam {
    delay?: number;
    iterations?: number;
    onFinish?: (() => void);
}
export interface KeyframeState {
    duration: number;
    curve?: Curve | string | ICurve;
    event: (() => void);
}
export type Callback<T,V = void> = (data: T) => V;
export type HoverCallback = (isHover: boolean, event: HoverEvent) => void;
export type AccessibilityCallback = (isHover: boolean, event: AccessibilityHoverEvent) => void;
export interface VisibleAreaEventOptions {
    ratios: Array<number>;
    expectedUpdateInterval?: number;
}
export type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: number) => void;
export interface UIGestureEvent {
}
export interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
export enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1
}
export enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1
}
/** @memo:stable */
export class ArkCommonMethodComponent extends ComponentBase implements UICommonMethod {
    getPeer(): ArkCommonMethodPeer {
        return (this.peer as ArkCommonMethodPeer)
    }
    /** @memo */
    public width(value: Length): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length)
            this.getPeer()?.widthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public height(value: Length): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length)
            this.getPeer()?.heightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public drawModifier(value: DrawModifier | undefined): this {
        if (this.checkPriority("drawModifier")) {
            const value_casted = value as (DrawModifier | undefined)
            this.getPeer()?.drawModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public responseRegion(value: Array<Rectangle> | Rectangle): this {
        if (this.checkPriority("responseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle)
            this.getPeer()?.responseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
        if (this.checkPriority("mouseResponseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle)
            this.getPeer()?.mouseResponseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public constraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public touchable(value: boolean): this {
        if (this.checkPriority("touchable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.touchableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hitTestBehavior(value: HitTestMode): this {
        if (this.checkPriority("hitTestBehavior")) {
            const value_casted = value as (HitTestMode)
            this.getPeer()?.hitTestBehaviorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult)): this {
        if (this.checkPriority("onChildTouchTest")) {
            const value_casted = value as (((value: Array<TouchTestInfo>) => TouchResult))
            this.getPeer()?.onChildTouchTestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutWeight(value: number | string): this {
        if (this.checkPriority("layoutWeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.layoutWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainWeight(value: ChainWeightOptions): this {
        if (this.checkPriority("chainWeight")) {
            const value_casted = value as (ChainWeightOptions)
            this.getPeer()?.chainWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public padding(value: Padding | Length | LocalizedPadding): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Length | LocalizedPadding)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this {
        if (this.checkPriority("safeAreaPadding")) {
            const value_casted = value as (Padding | LengthMetrics | LocalizedPadding)
            this.getPeer()?.safeAreaPaddingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public margin(value: Padding | Length | LocalizedPadding): this {
        if (this.checkPriority("margin")) {
            const value_casted = value as (Padding | Length | LocalizedPadding)
            this.getPeer()?.marginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pixelRound(value: PixelRoundPolicy): this {
        if (this.checkPriority("pixelRound")) {
            const value_casted = value as (PixelRoundPolicy)
            this.getPeer()?.pixelRoundAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImageSize(value: SizeOptions | ImageSize): this {
        if (this.checkPriority("backgroundImageSize")) {
            const value_casted = value as (SizeOptions | ImageSize)
            this.getPeer()?.backgroundImageSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImagePosition(value: Position | Alignment): this {
        if (this.checkPriority("backgroundImagePosition")) {
            const value_casted = value as (Position | Alignment)
            this.getPeer()?.backgroundImagePositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundEffect(value: BackgroundEffectOptions): this {
        if (this.checkPriority("backgroundEffect")) {
            const value_casted = value as (BackgroundEffectOptions)
            this.getPeer()?.backgroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImageResizable(value: ResizableOptions): this {
        if (this.checkPriority("backgroundImageResizable")) {
            const value_casted = value as (ResizableOptions)
            this.getPeer()?.backgroundImageResizableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundEffect(value: ForegroundEffectOptions): this {
        if (this.checkPriority("foregroundEffect")) {
            const value_casted = value as (ForegroundEffectOptions)
            this.getPeer()?.foregroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public visualEffect(value: VisualEffect): this {
        if (this.checkPriority("visualEffect")) {
            const value_casted = value as (VisualEffect)
            this.getPeer()?.visualEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundFilter(value: Filter): this {
        if (this.checkPriority("backgroundFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.backgroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundFilter(value: Filter): this {
        if (this.checkPriority("foregroundFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.foregroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public compositingFilter(value: Filter): this {
        if (this.checkPriority("compositingFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.compositingFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public opacity(value: number | Resource): this {
        if (this.checkPriority("opacity")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.opacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public border(value: BorderOptions): this {
        if (this.checkPriority("border")) {
            const value_casted = value as (BorderOptions)
            this.getPeer()?.borderAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderStyle(value: BorderStyle | EdgeStyles): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | EdgeStyles)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Length | EdgeWidths | LocalizedEdgeWidths)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Length | BorderRadiuses | LocalizedBorderRadiuses)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderImage(value: BorderImageOption): this {
        if (this.checkPriority("borderImage")) {
            const value_casted = value as (BorderImageOption)
            this.getPeer()?.borderImageAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outline(value: OutlineOptions): this {
        if (this.checkPriority("outline")) {
            const value_casted = value as (OutlineOptions)
            this.getPeer()?.outlineAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
        if (this.checkPriority("outlineStyle")) {
            const value_casted = value as (OutlineStyle | EdgeOutlineStyles)
            this.getPeer()?.outlineStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineWidth(value: Dimension | EdgeOutlineWidths): this {
        if (this.checkPriority("outlineWidth")) {
            const value_casted = value as (Dimension | EdgeOutlineWidths)
            this.getPeer()?.outlineWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        if (this.checkPriority("outlineColor")) {
            const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors)
            this.getPeer()?.outlineColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineRadius(value: Dimension | OutlineRadiuses): this {
        if (this.checkPriority("outlineRadius")) {
            const value_casted = value as (Dimension | OutlineRadiuses)
            this.getPeer()?.outlineRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundColor(value: ResourceColor | ColoringStrategy): this {
        if (this.checkPriority("foregroundColor")) {
            const value_casted = value as (ResourceColor | ColoringStrategy)
            this.getPeer()?.foregroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onClick(event: ((event: ClickEvent) => void), distanceThreshold?: number): this {
        if (this.checkPriority("onClick")) {
            const event_type = runtimeType(event)
            const distanceThreshold_type = runtimeType(distanceThreshold)
            const value_casted = event as (((event: ClickEvent) => void))
            this.getPeer()?.onClick0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHover(value: ((isHover: boolean,event: HoverEvent) => void)): this {
        if (this.checkPriority("onHover")) {
            const value_casted = value as (((isHover: boolean,event: HoverEvent) => void))
            this.getPeer()?.onHoverAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAccessibilityHover(value: AccessibilityCallback): this {
        if (this.checkPriority("onAccessibilityHover")) {
            const value_casted = value as (AccessibilityCallback)
            this.getPeer()?.onAccessibilityHoverAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hoverEffect(value: HoverEffect): this {
        if (this.checkPriority("hoverEffect")) {
            const value_casted = value as (HoverEffect)
            this.getPeer()?.hoverEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onMouse(value: ((event: MouseEvent) => void)): this {
        if (this.checkPriority("onMouse")) {
            const value_casted = value as (((event: MouseEvent) => void))
            this.getPeer()?.onMouseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTouch(value: ((event: TouchEvent) => void)): this {
        if (this.checkPriority("onTouch")) {
            const value_casted = value as (((event: TouchEvent) => void))
            this.getPeer()?.onTouchAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onKeyEvent(value: ((event: KeyEvent) => void)): this {
        if (this.checkPriority("onKeyEvent")) {
            const value_casted = value as (((event: KeyEvent) => void))
            this.getPeer()?.onKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): this {
        if (this.checkPriority("onKeyPreIme")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean))
            this.getPeer()?.onKeyPreImeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusable(value: boolean): this {
        if (this.checkPriority("focusable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.focusableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFocus(value: (() => void)): this {
        if (this.checkPriority("onFocus")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBlur(value: (() => void)): this {
        if (this.checkPriority("onBlur")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onBlurAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public tabIndex(value: number): this {
        if (this.checkPriority("tabIndex")) {
            const value_casted = value as (number)
            this.getPeer()?.tabIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultFocus(value: boolean): this {
        if (this.checkPriority("defaultFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.defaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public groupDefaultFocus(value: boolean): this {
        if (this.checkPriority("groupDefaultFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.groupDefaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusOnTouch(value: boolean): this {
        if (this.checkPriority("focusOnTouch")) {
            const value_casted = value as (boolean)
            this.getPeer()?.focusOnTouchAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusBox(value: FocusBoxStyle): this {
        if (this.checkPriority("focusBox")) {
            const value_casted = value as (FocusBoxStyle)
            this.getPeer()?.focusBoxAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public animation(value: AnimateParam): this {
        if (this.checkPriority("animation")) {
            const value_casted = value as (AnimateParam)
            this.getPeer()?.animationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public transition(effect: TransitionOptions | TransitionEffect | TransitionEffect, onFinish?: TransitionFinishCallback): this {
        if (this.checkPriority("transition")) {
            const effect_type = runtimeType(effect)
            const onFinish_type = runtimeType(onFinish)
            if (((TypeChecker.isTransitionOptions(effect, false, false, false, false, false)) || (TypeChecker.isTransitionEffect(effect))) && (RuntimeType.UNDEFINED == onFinish_type)) {
                const value_casted = effect as (TransitionOptions | TransitionEffect)
                this.getPeer()?.transition0Attribute(value_casted)
                return this
            }
            if ((TypeChecker.isTransitionEffect(effect)) && ((RuntimeType.FUNCTION == onFinish_type) || (RuntimeType.UNDEFINED == onFinish_type))) {
                const effect_casted = effect as (TransitionEffect)
                const onFinish_casted = onFinish as (TransitionFinishCallback | undefined)
                this.getPeer()?.transition1Attribute(effect_casted, onFinish_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public motionBlur(value: MotionBlurOptions): this {
        if (this.checkPriority("motionBlur")) {
            const value_casted = value as (MotionBlurOptions)
            this.getPeer()?.motionBlurAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public brightness(value: number): this {
        if (this.checkPriority("brightness")) {
            const value_casted = value as (number)
            this.getPeer()?.brightnessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contrast(value: number): this {
        if (this.checkPriority("contrast")) {
            const value_casted = value as (number)
            this.getPeer()?.contrastAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public grayscale(value: number): this {
        if (this.checkPriority("grayscale")) {
            const value_casted = value as (number)
            this.getPeer()?.grayscaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colorBlend(value: Color | string | Resource): this {
        if (this.checkPriority("colorBlend")) {
            const value_casted = value as (Color | string | Resource)
            this.getPeer()?.colorBlendAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public saturate(value: number): this {
        if (this.checkPriority("saturate")) {
            const value_casted = value as (number)
            this.getPeer()?.saturateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sepia(value: number): this {
        if (this.checkPriority("sepia")) {
            const value_casted = value as (number)
            this.getPeer()?.sepiaAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public invert(value: number | InvertOptions): this {
        if (this.checkPriority("invert")) {
            const value_casted = value as (number | InvertOptions)
            this.getPeer()?.invertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hueRotate(value: number | string): this {
        if (this.checkPriority("hueRotate")) {
            const value_casted = value as (number | string)
            this.getPeer()?.hueRotateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useShadowBatching(value: boolean): this {
        if (this.checkPriority("useShadowBatching")) {
            const value_casted = value as (boolean)
            this.getPeer()?.useShadowBatchingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useEffect(useEffect: boolean, effectType?: EffectType): this {
        if (this.checkPriority("useEffect")) {
            const useEffect_type = runtimeType(useEffect)
            const effectType_type = runtimeType(effectType)
            if (RuntimeType.UNDEFINED == effectType_type) {
                const value_casted = useEffect as (boolean)
                this.getPeer()?.useEffect0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isEffectType(effectType)) {
                const useEffect_casted = useEffect as (boolean)
                const effectType_casted = effectType as (EffectType)
                this.getPeer()?.useEffect1Attribute(useEffect_casted, effectType_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public renderGroup(value: boolean): this {
        if (this.checkPriority("renderGroup")) {
            const value_casted = value as (boolean)
            this.getPeer()?.renderGroupAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public freeze(value: boolean): this {
        if (this.checkPriority("freeze")) {
            const value_casted = value as (boolean)
            this.getPeer()?.freezeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public translate(value: TranslateOptions): this {
        if (this.checkPriority("translate")) {
            const value_casted = value as (TranslateOptions)
            this.getPeer()?.translateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scale(value: ScaleOptions): this {
        if (this.checkPriority("scale")) {
            const value_casted = value as (ScaleOptions)
            this.getPeer()?.scaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gridSpan(value: number): this {
        if (this.checkPriority("gridSpan")) {
            const value_casted = value as (number)
            this.getPeer()?.gridSpanAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gridOffset(value: number): this {
        if (this.checkPriority("gridOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.gridOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rotate(value: RotateOptions): this {
        if (this.checkPriority("rotate")) {
            const value_casted = value as (RotateOptions)
            this.getPeer()?.rotateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public transform(value: TransformationMatrix): this {
        if (this.checkPriority("transform")) {
            const value_casted = value as (TransformationMatrix)
            this.getPeer()?.transformAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAppear(value: (() => void)): this {
        if (this.checkPriority("onAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDisAppear(value: (() => void)): this {
        if (this.checkPriority("onDisAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDisAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAttach(value: (() => void)): this {
        if (this.checkPriority("onAttach")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onAttachAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDetach(value: (() => void)): this {
        if (this.checkPriority("onDetach")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDetachAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAreaChange(value: ((oldValue: Area,newValue: Area) => void)): this {
        if (this.checkPriority("onAreaChange")) {
            const value_casted = value as (((oldValue: Area,newValue: Area) => void))
            this.getPeer()?.onAreaChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public visibility(value: Visibility): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexGrow(value: number): this {
        if (this.checkPriority("flexGrow")) {
            const value_casted = value as (number)
            this.getPeer()?.flexGrowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexShrink(value: number): this {
        if (this.checkPriority("flexShrink")) {
            const value_casted = value as (number)
            this.getPeer()?.flexShrinkAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexBasis(value: number | string): this {
        if (this.checkPriority("flexBasis")) {
            const value_casted = value as (number | string)
            this.getPeer()?.flexBasisAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignSelf(value: ItemAlign): this {
        if (this.checkPriority("alignSelf")) {
            const value_casted = value as (ItemAlign)
            this.getPeer()?.alignSelfAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public displayPriority(value: number): this {
        if (this.checkPriority("displayPriority")) {
            const value_casted = value as (number)
            this.getPeer()?.displayPriorityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public zIndex(value: number): this {
        if (this.checkPriority("zIndex")) {
            const value_casted = value as (number)
            this.getPeer()?.zIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public direction(value: Direction): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Direction)
            this.getPeer()?.directionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public align(value: Alignment): this {
        if (this.checkPriority("align")) {
            const value_casted = value as (Alignment)
            this.getPeer()?.alignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public position(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public markAnchor(value: Position | LocalizedPosition): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | LocalizedPosition)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public offset(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enabled(value: boolean): this {
        if (this.checkPriority("enabled")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enabledAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this {
        if (this.checkPriority("useSizeType")) {
            const value_casted = value as (Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs)
            this.getPeer()?.useSizeTypeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this {
        if (this.checkPriority("alignRules")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isAlignRuleOption(value, false, false, true, true, true, true, true)) {
                const value_casted = value as (AlignRuleOption)
                this.getPeer()?.alignRules0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isLocalizedAlignRuleOptions(value, false, false, true, true, true, true, true)) {
                const value_casted = value as (LocalizedAlignRuleOptions)
                this.getPeer()?.alignRules1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public aspectRatio(value: number): this {
        if (this.checkPriority("aspectRatio")) {
            const value_casted = value as (number)
            this.getPeer()?.aspectRatioAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clickEffect(value: ClickEffect | undefined): this {
        if (this.checkPriority("clickEffect")) {
            const value_casted = value as (ClickEffect | undefined)
            this.getPeer()?.clickEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)): this {
        if (this.checkPriority("onDragStart")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo))
            this.getPeer()?.onDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragEnter(value: ((event: DragEvent,extraParams?: string) => void)): this {
        if (this.checkPriority("onDragEnter")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void))
            this.getPeer()?.onDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragMove(value: ((event: DragEvent,extraParams?: string) => void)): this {
        if (this.checkPriority("onDragMove")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void))
            this.getPeer()?.onDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragLeave(value: ((event: DragEvent,extraParams?: string) => void)): this {
        if (this.checkPriority("onDragLeave")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void))
            this.getPeer()?.onDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDrop(value: ((event: DragEvent,extraParams?: string) => void)): this {
        if (this.checkPriority("onDrop")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void))
            this.getPeer()?.onDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragEnd(value: ((event: DragEvent,extraParams?: string) => void)): this {
        if (this.checkPriority("onDragEnd")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void))
            this.getPeer()?.onDragEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public allowDrop(value: Array<UniformDataType> | undefined): this {
        if (this.checkPriority("allowDrop")) {
            const value_casted = value as (Array<UniformDataType> | undefined)
            this.getPeer()?.allowDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dragPreview(value: CustomBuilder | DragItemInfo | string): this {
        if (this.checkPriority("dragPreview")) {
            const value_casted = value as (CustomBuilder | DragItemInfo | string)
            this.getPeer()?.dragPreviewAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPreDrag(value: ((parameter: PreDragStatus) => void)): this {
        if (this.checkPriority("onPreDrag")) {
            const value_casted = value as (((parameter: PreDragStatus) => void))
            this.getPeer()?.onPreDragAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public linearGradient(value: Type_CommonMethod_linearGradient_value): this {
        if (this.checkPriority("linearGradient")) {
            const value_casted = value as (Type_CommonMethod_linearGradient_value)
            this.getPeer()?.linearGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sweepGradient(value: Type_CommonMethod_sweepGradient_value): this {
        if (this.checkPriority("sweepGradient")) {
            const value_casted = value as (Type_CommonMethod_sweepGradient_value)
            this.getPeer()?.sweepGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public radialGradient(value: Type_CommonMethod_radialGradient_value): this {
        if (this.checkPriority("radialGradient")) {
            const value_casted = value as (Type_CommonMethod_radialGradient_value)
            this.getPeer()?.radialGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public motionPath(value: MotionPathOptions): this {
        if (this.checkPriority("motionPath")) {
            const value_casted = value as (MotionPathOptions)
            this.getPeer()?.motionPathAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shadow(value: ShadowOptions | ShadowStyle): this {
        if (this.checkPriority("shadow")) {
            const value_casted = value as (ShadowOptions | ShadowStyle)
            this.getPeer()?.shadowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clip(value: boolean | undefined): this {
        if (this.checkPriority("clip")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.clip0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.clip1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        if (this.checkPriority("clipShape")) {
            const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape)
            this.getPeer()?.clipShapeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mask(value: ProgressMask | undefined): this {
        if (this.checkPriority("mask")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ProgressMask | undefined)
                this.getPeer()?.mask0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ProgressMask | undefined)
                this.getPeer()?.mask1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        if (this.checkPriority("maskShape")) {
            const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape)
            this.getPeer()?.maskShapeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public key(value: string): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public id(value: string): this {
        if (this.checkPriority("id")) {
            const value_casted = value as (string)
            this.getPeer()?.idAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public geometryTransition(id: string, options?: GeometryTransitionOptions): this {
        if (this.checkPriority("geometryTransition")) {
            const id_type = runtimeType(id)
            const options_type = runtimeType(options)
            const value_casted = id as (string)
            this.getPeer()?.geometryTransition0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public stateStyles(value: StateStyles): this {
        if (this.checkPriority("stateStyles")) {
            const value_casted = value as (StateStyles)
            this.getPeer()?.stateStylesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public restoreId(value: number): this {
        if (this.checkPriority("restoreId")) {
            const value_casted = value as (number)
            this.getPeer()?.restoreIdAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sphericalEffect(value: number): this {
        if (this.checkPriority("sphericalEffect")) {
            const value_casted = value as (number)
            this.getPeer()?.sphericalEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lightUpEffect(value: number): this {
        if (this.checkPriority("lightUpEffect")) {
            const value_casted = value as (number)
            this.getPeer()?.lightUpEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pixelStretchEffect(value: PixelStretchEffectOptions): this {
        if (this.checkPriority("pixelStretchEffect")) {
            const value_casted = value as (PixelStretchEffectOptions)
            this.getPeer()?.pixelStretchEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions): this {
        if (this.checkPriority("accessibilityGroup")) {
            const isGroup_type = runtimeType(isGroup)
            const accessibilityOptions_type = runtimeType(accessibilityOptions)
            const value_casted = isGroup as (boolean)
            this.getPeer()?.accessibilityGroup0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityText(value: string | Resource): this {
        if (this.checkPriority("accessibilityText")) {
            const value_type = runtimeType(value)
            if (RuntimeType.STRING == value_type) {
                const value_casted = value as (string)
                this.getPeer()?.accessibilityText0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Resource)
                this.getPeer()?.accessibilityText1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public accessibilityTextHint(value: string): this {
        if (this.checkPriority("accessibilityTextHint")) {
            const value_casted = value as (string)
            this.getPeer()?.accessibilityTextHintAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityDescription(value: string | Resource): this {
        if (this.checkPriority("accessibilityDescription")) {
            const value_type = runtimeType(value)
            if (RuntimeType.STRING == value_type) {
                const value_casted = value as (string)
                this.getPeer()?.accessibilityDescription0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Resource)
                this.getPeer()?.accessibilityDescription1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public accessibilityLevel(value: string): this {
        if (this.checkPriority("accessibilityLevel")) {
            const value_casted = value as (string)
            this.getPeer()?.accessibilityLevelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityVirtualNode(value: CustomBuilder): this {
        if (this.checkPriority("accessibilityVirtualNode")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.accessibilityVirtualNodeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityChecked(value: boolean): this {
        if (this.checkPriority("accessibilityChecked")) {
            const value_casted = value as (boolean)
            this.getPeer()?.accessibilityCheckedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilitySelected(value: boolean): this {
        if (this.checkPriority("accessibilitySelected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.accessibilitySelectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public obscured(value: Array<ObscuredReasons>): this {
        if (this.checkPriority("obscured")) {
            const value_casted = value as (Array<ObscuredReasons>)
            this.getPeer()?.obscuredAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public reuseId(value: string): this {
        if (this.checkPriority("reuseId")) {
            const value_casted = value as (string)
            this.getPeer()?.reuseIdAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderFit(value: RenderFit): this {
        if (this.checkPriority("renderFit")) {
            const value_casted = value as (RenderFit)
            this.getPeer()?.renderFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gestureModifier(value: GestureModifier): this {
        if (this.checkPriority("gestureModifier")) {
            const value_casted = value as (GestureModifier)
            this.getPeer()?.gestureModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundBrightness(value: BackgroundBrightnessOptions): this {
        if (this.checkPriority("backgroundBrightness")) {
            const value_casted = value as (BackgroundBrightnessOptions)
            this.getPeer()?.backgroundBrightnessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)): this {
        if (this.checkPriority("onGestureJudgeBegin")) {
            const value_casted = value as (((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult))
            this.getPeer()?.onGestureJudgeBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean): this {
        if (this.checkPriority("onGestureRecognizerJudgeBegin")) {
            const callback__type = runtimeType(callback_)
            const exposeInnerGesture_type = runtimeType(exposeInnerGesture)
            const value_casted = callback_ as (GestureRecognizerJudgeBeginCallback)
            this.getPeer()?.onGestureRecognizerJudgeBegin0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this {
        if (this.checkPriority("shouldBuiltInRecognizerParallelWith")) {
            const value_casted = value as (ShouldBuiltInRecognizerParallelWithCallback)
            this.getPeer()?.shouldBuiltInRecognizerParallelWithAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public monopolizeEvents(value: boolean): this {
        if (this.checkPriority("monopolizeEvents")) {
            const value_casted = value as (boolean)
            this.getPeer()?.monopolizeEventsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): this {
        if (this.checkPriority("onTouchIntercept")) {
            const value_casted = value as (((parameter: TouchEvent) => HitTestMode))
            this.getPeer()?.onTouchInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSizeChange(value: SizeChangeCallback): this {
        if (this.checkPriority("onSizeChange")) {
            const value_casted = value as (SizeChangeCallback)
            this.getPeer()?.onSizeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customProperty(name: string, value: Object | undefined): this {
        if (this.checkPriority("customProperty")) {
            const name_casted = name as (string)
            const value_casted = value as (Object | undefined)
            this.getPeer()?.customPropertyAttribute(name_casted, value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        if (this.checkPriority("expandSafeArea")) {
            const types_casted = types as (Array<SafeAreaType> | undefined)
            const edges_casted = edges as (Array<SafeAreaEdge> | undefined)
            this.getPeer()?.expandSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    /** @memo */
    public background(builder: CustomBuilder, options?: Literal_Alignment_align): this {
        if (this.checkPriority("background")) {
            const builder_casted = builder as (CustomBuilder)
            const options_casted = options as (Literal_Alignment_align | undefined)
            this.getPeer()?.backgroundAttribute(builder_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): this {
        if (this.checkPriority("backgroundImage")) {
            const src_casted = src as (ResourceStr | PixelMap)
            const repeat_casted = repeat as (ImageRepeat | undefined)
            this.getPeer()?.backgroundImageAttribute(src_casted, repeat_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        if (this.checkPriority("backgroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            const options_casted = options as (BackgroundBlurStyleOptions | undefined)
            this.getPeer()?.backgroundBlurStyleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
        if (this.checkPriority("foregroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            const options_casted = options as (ForegroundBlurStyleOptions | undefined)
            this.getPeer()?.foregroundBlurStyleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this {
        if (this.checkPriority("focusScopeId")) {
            const id_type = runtimeType(id)
            const isGroup_type = runtimeType(isGroup)
            const arrowStepOut_type = runtimeType(arrowStepOut)
            const id_casted = id as (string)
            const isGroup_casted = isGroup as (boolean | undefined)
            this.getPeer()?.focusScopeId0Attribute(id_casted, isGroup_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusScopePriority(scopeId: string, priority?: FocusPriority): this {
        if (this.checkPriority("focusScopePriority")) {
            const scopeId_casted = scopeId as (string)
            const priority_casted = priority as (FocusPriority | undefined)
            this.getPeer()?.focusScopePriorityAttribute(scopeId_casted, priority_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("gesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.gestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public priorityGesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("priorityGesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.priorityGestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public parallelGesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("parallelGesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.parallelGestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blur(value: number, options?: BlurOptions): this {
        if (this.checkPriority("blur")) {
            const value_casted = value as (number)
            const options_casted = options as (BlurOptions | undefined)
            this.getPeer()?.blurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
        if (this.checkPriority("linearGradientBlur")) {
            const value_casted = value as (number)
            const options_casted = options as (LinearGradientBlurOptions)
            this.getPeer()?.linearGradientBlurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemBarEffect(): this {
        if (this.checkPriority("systemBarEffect")) {
            this.getPeer()?.systemBarEffectAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public backdropBlur(value: number, options?: BlurOptions): this {
        if (this.checkPriority("backdropBlur")) {
            const value_casted = value as (number)
            const options_casted = options as (BlurOptions | undefined)
            this.getPeer()?.backdropBlurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sharedTransition(id: string, options?: sharedTransitionOptions): this {
        if (this.checkPriority("sharedTransition")) {
            const id_casted = id as (string)
            const options_casted = options as (sharedTransitionOptions | undefined)
            this.getPeer()?.sharedTransitionAttribute(id_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainMode(direction: Axis, style: ChainStyle): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis)
            const style_casted = style as (ChainStyle)
            this.getPeer()?.chainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this {
        if (this.checkPriority("dragPreviewOptions")) {
            const value_casted = value as (DragPreviewOptions)
            const options_casted = options as (DragInteractionOptions | undefined)
            this.getPeer()?.dragPreviewOptionsAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): this {
        if (this.checkPriority("overlay")) {
            const value_casted = value as (string | CustomBuilder | ComponentContent)
            const options_casted = options as (OverlayOptions | undefined)
            this.getPeer()?.overlayAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blendMode(value: BlendMode, type?: BlendApplyType): this {
        if (this.checkPriority("blendMode")) {
            const value_casted = value as (BlendMode)
            const type_casted = type as (BlendApplyType | undefined)
            this.getPeer()?.blendModeAttribute(value_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public advancedBlendMode(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): this {
        if (this.checkPriority("advancedBlendMode")) {
            const effect_casted = effect as (BlendMode | BrightnessBlender)
            const type_casted = type as (BlendApplyType | undefined)
            this.getPeer()?.advancedBlendModeAttribute(effect_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        if (this.checkPriority("bindPopup")) {
            const show_casted = show as (boolean)
            const popup_casted = popup as (PopupOptions | CustomPopupOptions)
            this.getPeer()?.bindPopupAttribute(show_casted, popup_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindMenu(isShow: Array<MenuElement> | CustomBuilder | boolean, content?: MenuOptions | Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
        if (this.checkPriority("bindMenu")) {
            const isShow_type = runtimeType(isShow)
            const content_type = runtimeType(content)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == isShow_type) || (RuntimeType.FUNCTION == isShow_type)) && ((RuntimeType.OBJECT == content_type) || (RuntimeType.UNDEFINED == content_type))) {
                const content_casted = isShow as (Array<MenuElement> | CustomBuilder)
                const options_casted = content as (MenuOptions | undefined)
                this.getPeer()?.bindMenu0Attribute(content_casted, options_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == isShow_type) && ((RuntimeType.OBJECT == content_type) || (RuntimeType.FUNCTION == content_type))) {
                const isShow_casted = isShow as (boolean)
                const content_casted = content as (Array<MenuElement> | CustomBuilder)
                const options_casted = options as (MenuOptions | undefined)
                this.getPeer()?.bindMenu1Attribute(isShow_casted, content_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindContextMenu(content: CustomBuilder | boolean, responseType: ResponseType | CustomBuilder, options?: ContextMenuOptions): this {
        if (this.checkPriority("bindContextMenu")) {
            const content_type = runtimeType(content)
            const responseType_type = runtimeType(responseType)
            const options_type = runtimeType(options)
            if ((RuntimeType.FUNCTION == content_type) && (TypeChecker.isResponseType(responseType))) {
                const content_casted = content as (CustomBuilder)
                const responseType_casted = responseType as (ResponseType)
                const options_casted = options as (ContextMenuOptions | undefined)
                this.getPeer()?.bindContextMenu0Attribute(content_casted, responseType_casted, options_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == content_type) && (RuntimeType.FUNCTION == responseType_type)) {
                const isShown_casted = content as (boolean)
                const content_casted = responseType as (CustomBuilder)
                const options_casted = options as (ContextMenuOptions | undefined)
                this.getPeer()?.bindContextMenu1Attribute(isShown_casted, content_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
        if (this.checkPriority("bindContentCover")) {
            const isShow_type = runtimeType(isShow)
            const builder_type = runtimeType(builder)
            const type_type = runtimeType(type)
            if (((RuntimeType.BOOLEAN == isShow_type) || (RuntimeType.UNDEFINED == isShow_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.OBJECT == type_type))) {
                const isShow_casted = isShow as (boolean | undefined)
                const builder_casted = builder as (CustomBuilder)
                const type_casted = type as (ModalTransition | undefined)
                this.getPeer()?.bindContentCover0Attribute(isShow_casted, builder_casted, type_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == isShow_type) || (RuntimeType.UNDEFINED == isShow_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.UNDEFINED == type_type))) {
                const isShow_casted = isShow as (boolean | undefined)
                const builder_casted = builder as (CustomBuilder)
                const options_casted = type as (ContentCoverOptions | undefined)
                this.getPeer()?.bindContentCover1Attribute(isShow_casted, builder_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this {
        if (this.checkPriority("bindSheet")) {
            const isShow_casted = isShow as (boolean | undefined)
            const builder_casted = builder as (CustomBuilder)
            const options_casted = options as (SheetOptions | undefined)
            this.getPeer()?.bindSheetAttribute(isShow_casted, builder_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this {
        if (this.checkPriority("onVisibleAreaChange")) {
            const ratios_casted = ratios as (Array<number>)
            const event_casted = event as (VisibleAreaChangeCallback)
            this.getPeer()?.onVisibleAreaChangeAttribute(ratios_casted, event_casted)
            return this
        }
        return this
    }
    /** @memo */
    public keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this {
        if (this.checkPriority("keyboardShortcut")) {
            const value_casted = value as (string | FunctionKey)
            const keys_casted = keys as (Array<ModifierKey>)
            const action_casted = action as ((() => void) | undefined)
            this.getPeer()?.keyboardShortcutAttribute(value_casted, keys_casted, action_casted)
            return this
        }
        return this
    }
    _modifier?: AttributeModifier<CommonMethod> | undefined
    /** @memo */
    public attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkCommonComponent extends ArkCommonMethodComponent implements UICommonAttribute {
    getPeer(): ArkCommonPeer {
        return (this.peer as ArkCommonPeer)
    }
    /** @memo */
    public setCommonOptions(): this {
        if (this.checkPriority("setCommonOptions")) {
            this.getPeer()?.setCommonOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<CommonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkCommon(
    /** @memo */
    style: ((attributes: UICommonAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    
): void {
    const receiver = remember(() => {
        return new ArkCommonComponent()
    })
    NodeAttach<ArkCommonPeer>((): ArkCommonPeer => ArkCommonPeer.create(receiver), (_: ArkCommonPeer) => {
        receiver.setCommonOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
/** @memo:stable */
export class ArkCommonShapeMethodComponent extends ArkCommonMethodComponent implements UICommonShapeMethod {
    getPeer(): ArkCommonShapeMethodPeer {
        return (this.peer as ArkCommonShapeMethodPeer)
    }
    /** @memo */
    public stroke(value: ResourceColor): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.strokeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fill(value: ResourceColor): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeDashOffset(value: number | string): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeLineCap(value: LineCapStyle): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle)
            this.getPeer()?.strokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeLineJoin(value: LineJoinStyle): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle)
            this.getPeer()?.strokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeMiterLimit(value: number | string): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeOpacity(value: number | string | Resource): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.strokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillOpacity(value: number | string | Resource): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeWidth(value: Length): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public antiAlias(value: boolean): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean)
            this.getPeer()?.antiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeDashArray(value: Array<Length>): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length>)
            this.getPeer()?.strokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkScrollableCommonMethodComponent extends ArkCommonMethodComponent implements UIScrollableCommonMethod {
    getPeer(): ArkScrollableCommonMethodPeer {
        return (this.peer as ArkScrollableCommonMethodPeer)
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarColor(value: Color | number | string): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarWidth(value: number | string): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: (() => void)): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: (() => void)): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flingSpeedLimit(value: number): this {
        if (this.checkPriority("flingSpeedLimit")) {
            const value_casted = value as (number)
            this.getPeer()?.flingSpeedLimitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clipContent(value: ContentClipMode | RectShape): this {
        if (this.checkPriority("clipContent")) {
            const value_casted = value as (ContentClipMode | RectShape)
            this.getPeer()?.clipContentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (this.checkPriority("fadingEdge")) {
            const enabled_casted = enabled as (boolean | undefined)
            const options_casted = options as (FadingEdgeOptions | undefined)
            this.getPeer()?.fadingEdgeAttribute(enabled_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function getContext(component?: Object | undefined): Context {
    return GlobalScope.getContext(component)
}
export function postCardAction(component: Object, action: Object): void {
    GlobalScope.postCardAction(component, action)
}
export function dollar_r(value: string, params: Array<object>): Resource {
    return GlobalScope.dollar_r(value, params)
}
export function dollar_rawfile(value: string): Resource {
    return GlobalScope.dollar_rawfile(value)
}
export function animateTo(value: AnimateParam, event: (() => void)): void {
    GlobalScope.animateTo(value, event)
}
export function animateToImmediately(value: AnimateParam, event: (() => void)): void {
    GlobalScope.animateToImmediately(value, event)
}
export function vp2px(value: number): number {
    return GlobalScope.vp2px(value)
}
export function px2vp(value: number): number {
    return GlobalScope.px2vp(value)
}
export function fp2px(value: number): number {
    return GlobalScope.fp2px(value)
}
export function px2fp(value: number): number {
    return GlobalScope.px2fp(value)
}
export function lpx2px(value: number): number {
    return GlobalScope.lpx2px(value)
}
export function px2lpx(value: number): number {
    return GlobalScope.px2lpx(value)
}
export interface ClickEvent {
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    screenX: number
    screenY: number
    x: number
    y: number
    preventDefault: (() => void)
}
export class ClickEventInternal extends BaseEventInternal implements MaterializedBase,ClickEvent {
    get displayX(): number {
        return this.getDisplayX()
    }
    set displayX(displayX: number) {
        this.setDisplayX(displayX)
    }
    get displayY(): number {
        return this.getDisplayY()
    }
    set displayY(displayY: number) {
        this.setDisplayY(displayY)
    }
    get windowX(): number {
        return this.getWindowX()
    }
    set windowX(windowX: number) {
        this.setWindowX(windowX)
    }
    get windowY(): number {
        return this.getWindowY()
    }
    set windowY(windowY: number) {
        this.setWindowY(windowY)
    }
    get screenX(): number {
        return this.getScreenX()
    }
    set screenX(screenX: number) {
        this.setScreenX(screenX)
    }
    get screenY(): number {
        return this.getScreenY()
    }
    set screenY(screenY: number) {
        this.setScreenY(screenY)
    }
    get x(): number {
        return this.getX()
    }
    set x(x: number) {
        this.setX(x)
    }
    get y(): number {
        return this.getY()
    }
    set y(y: number) {
        this.setY(y)
    }
    get preventDefault(): (() => void) {
        throw new Error("Not implemented")
    }
    set preventDefault(preventDefault: (() => void)) {
        this.setPreventDefault(preventDefault)
    }
    static ctor_clickevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = ClickEventInternal.ctor_clickevent()
        this.peer = new Finalizable(ctorPtr, ClickEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ClickEvent_getFinalizer()
    }
    private getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this.setDisplayY_serialize(displayY_casted)
        return
    }
    private getWindowX(): number {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this.setWindowY_serialize(windowY_casted)
        return
    }
    private getScreenX(): number {
        return this.getScreenX_serialize()
    }
    private setScreenX(screenX: number): void {
        const screenX_casted = screenX as (number)
        this.setScreenX_serialize(screenX_casted)
        return
    }
    private getScreenY(): number {
        return this.getScreenY_serialize()
    }
    private setScreenY(screenY: number): void {
        const screenY_casted = screenY as (number)
        this.setScreenY_serialize(screenY_casted)
        return
    }
    private getX(): number {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this.setX_serialize(x_casted)
        return
    }
    private getY(): number {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this.setY_serialize(y_casted)
        return
    }
    private getPreventDefault(): (() => void) {
        return this.getPreventDefault_serialize()
    }
    private setPreventDefault(preventDefault: (() => void)): void {
        const preventDefault_casted = preventDefault as ((() => void))
        this.setPreventDefault_serialize(preventDefault_casted)
        return
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getScreenX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getScreenX(this.peer!.ptr)
        return retval
    }
    private setScreenX_serialize(screenX: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setScreenX(this.peer!.ptr, screenX)
    }
    private getScreenY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getScreenY(this.peer!.ptr)
        return retval
    }
    private setScreenY_serialize(screenY: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setScreenY(this.peer!.ptr, screenY)
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._ClickEvent_setY(this.peer!.ptr, y)
    }
    private getPreventDefault_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getPreventDefault(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setPreventDefault_serialize(preventDefault: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(preventDefault)
        ArkUIGeneratedNativeModule._ClickEvent_setPreventDefault(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): ClickEventInternal {
        const obj : ClickEventInternal = new ClickEventInternal()
        obj.peer = new Finalizable(ptr, ClickEventInternal.getFinalizer())
        return obj
    }
}
export interface HoverEvent {
    stopPropagation: (() => void)
}
export class HoverEventInternal extends BaseEventInternal implements MaterializedBase,HoverEvent {
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    static ctor_hoverevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = HoverEventInternal.ctor_hoverevent()
        this.peer = new Finalizable(ctorPtr, HoverEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HoverEvent_getFinalizer()
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._HoverEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): HoverEventInternal {
        const obj : HoverEventInternal = new HoverEventInternal()
        obj.peer = new Finalizable(ptr, HoverEventInternal.getFinalizer())
        return obj
    }
}
export interface MouseEvent {
    button: MouseButton
    action: MouseAction
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    screenX: number
    screenY: number
    x: number
    y: number
    stopPropagation: (() => void)
}
export class MouseEventInternal extends BaseEventInternal implements MaterializedBase,MouseEvent {
    get button(): MouseButton {
        return this.getButton()
    }
    set button(button: MouseButton) {
        this.setButton(button)
    }
    get action(): MouseAction {
        return this.getAction()
    }
    set action(action: MouseAction) {
        this.setAction(action)
    }
    get displayX(): number {
        return this.getDisplayX()
    }
    set displayX(displayX: number) {
        this.setDisplayX(displayX)
    }
    get displayY(): number {
        return this.getDisplayY()
    }
    set displayY(displayY: number) {
        this.setDisplayY(displayY)
    }
    get windowX(): number {
        return this.getWindowX()
    }
    set windowX(windowX: number) {
        this.setWindowX(windowX)
    }
    get windowY(): number {
        return this.getWindowY()
    }
    set windowY(windowY: number) {
        this.setWindowY(windowY)
    }
    get screenX(): number {
        return this.getScreenX()
    }
    set screenX(screenX: number) {
        this.setScreenX(screenX)
    }
    get screenY(): number {
        return this.getScreenY()
    }
    set screenY(screenY: number) {
        this.setScreenY(screenY)
    }
    get x(): number {
        return this.getX()
    }
    set x(x: number) {
        this.setX(x)
    }
    get y(): number {
        return this.getY()
    }
    set y(y: number) {
        this.setY(y)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    static ctor_mouseevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = MouseEventInternal.ctor_mouseevent()
        this.peer = new Finalizable(ctorPtr, MouseEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MouseEvent_getFinalizer()
    }
    private getButton(): MouseButton {
        return this.getButton_serialize()
    }
    private setButton(button: MouseButton): void {
        const button_casted = button as (MouseButton)
        this.setButton_serialize(button_casted)
        return
    }
    private getAction(): MouseAction {
        return this.getAction_serialize()
    }
    private setAction(action: MouseAction): void {
        const action_casted = action as (MouseAction)
        this.setAction_serialize(action_casted)
        return
    }
    private getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this.setDisplayY_serialize(displayY_casted)
        return
    }
    private getWindowX(): number {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this.setWindowY_serialize(windowY_casted)
        return
    }
    private getScreenX(): number {
        return this.getScreenX_serialize()
    }
    private setScreenX(screenX: number): void {
        const screenX_casted = screenX as (number)
        this.setScreenX_serialize(screenX_casted)
        return
    }
    private getScreenY(): number {
        return this.getScreenY_serialize()
    }
    private setScreenY(screenY: number): void {
        const screenY_casted = screenY as (number)
        this.setScreenY_serialize(screenY_casted)
        return
    }
    private getX(): number {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this.setX_serialize(x_casted)
        return
    }
    private getY(): number {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this.setY_serialize(y_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getButton_serialize(): MouseButton {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getButton(this.peer!.ptr)
        return TypeChecker.MouseButton_FromNumeric(retval)
    }
    private setButton_serialize(button: MouseButton): void {
        ArkUIGeneratedNativeModule._MouseEvent_setButton(this.peer!.ptr, TypeChecker.MouseButton_ToNumeric(button))
    }
    private getAction_serialize(): MouseAction {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getAction(this.peer!.ptr)
        return TypeChecker.MouseAction_FromNumeric(retval)
    }
    private setAction_serialize(action: MouseAction): void {
        ArkUIGeneratedNativeModule._MouseEvent_setAction(this.peer!.ptr, TypeChecker.MouseAction_ToNumeric(action))
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getScreenX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getScreenX(this.peer!.ptr)
        return retval
    }
    private setScreenX_serialize(screenX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setScreenX(this.peer!.ptr, screenX)
    }
    private getScreenY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getScreenY(this.peer!.ptr)
        return retval
    }
    private setScreenY_serialize(screenY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setScreenY(this.peer!.ptr, screenY)
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setY(this.peer!.ptr, y)
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._MouseEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): MouseEventInternal {
        const obj : MouseEventInternal = new MouseEventInternal()
        obj.peer = new Finalizable(ptr, MouseEventInternal.getFinalizer())
        return obj
    }
}
export interface AccessibilityHoverEvent {
    type: AccessibilityHoverType
    x: number
    y: number
    displayX: number
    displayY: number
    windowX: number
    windowY: number
}
export class AccessibilityHoverEventInternal extends BaseEventInternal implements MaterializedBase,AccessibilityHoverEvent {
    get type(): AccessibilityHoverType {
        return this.getType()
    }
    set type(type: AccessibilityHoverType) {
        this.setType(type)
    }
    get x(): number {
        return this.getX()
    }
    set x(x: number) {
        this.setX(x)
    }
    get y(): number {
        return this.getY()
    }
    set y(y: number) {
        this.setY(y)
    }
    get displayX(): number {
        return this.getDisplayX()
    }
    set displayX(displayX: number) {
        this.setDisplayX(displayX)
    }
    get displayY(): number {
        return this.getDisplayY()
    }
    set displayY(displayY: number) {
        this.setDisplayY(displayY)
    }
    get windowX(): number {
        return this.getWindowX()
    }
    set windowX(windowX: number) {
        this.setWindowX(windowX)
    }
    get windowY(): number {
        return this.getWindowY()
    }
    set windowY(windowY: number) {
        this.setWindowY(windowY)
    }
    static ctor_accessibilityhoverevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = AccessibilityHoverEventInternal.ctor_accessibilityhoverevent()
        this.peer = new Finalizable(ctorPtr, AccessibilityHoverEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getFinalizer()
    }
    private getType(): AccessibilityHoverType {
        return this.getType_serialize()
    }
    private setType(type: AccessibilityHoverType): void {
        const type_casted = type as (AccessibilityHoverType)
        this.setType_serialize(type_casted)
        return
    }
    private getX(): number {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this.setX_serialize(x_casted)
        return
    }
    private getY(): number {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this.setY_serialize(y_casted)
        return
    }
    private getDisplayX(): number {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this.setDisplayY_serialize(displayY_casted)
        return
    }
    private getWindowX(): number {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this.setWindowY_serialize(windowY_casted)
        return
    }
    private getType_serialize(): AccessibilityHoverType {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getType(this.peer!.ptr)
        return TypeChecker.AccessibilityHoverType_FromNumeric(retval)
    }
    private setType_serialize(type: AccessibilityHoverType): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setType(this.peer!.ptr, TypeChecker.AccessibilityHoverType_ToNumeric(type))
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setY(this.peer!.ptr, y)
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AccessibilityHoverEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setWindowY(this.peer!.ptr, windowY)
    }
    public static fromPtr(ptr: KPointer): AccessibilityHoverEventInternal {
        const obj : AccessibilityHoverEventInternal = new AccessibilityHoverEventInternal()
        obj.peer = new Finalizable(ptr, AccessibilityHoverEventInternal.getFinalizer())
        return obj
    }
}
export interface TouchEvent {
    type: TouchType
    touches: Array<TouchObject>
    changedTouches: Array<TouchObject>
    stopPropagation: (() => void)
    preventDefault: (() => void)
    getHistoricalPoints(): Array<HistoricalPoint>
}
export class TouchEventInternal extends BaseEventInternal implements MaterializedBase,TouchEvent {
    get type(): TouchType {
        return this.getType()
    }
    set type(type: TouchType) {
        this.setType(type)
    }
    get touches(): Array<TouchObject> {
        throw new Error("Not implemented")
    }
    set touches(touches: Array<TouchObject>) {
        this.setTouches(touches)
    }
    get changedTouches(): Array<TouchObject> {
        throw new Error("Not implemented")
    }
    set changedTouches(changedTouches: Array<TouchObject>) {
        this.setChangedTouches(changedTouches)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    get preventDefault(): (() => void) {
        throw new Error("Not implemented")
    }
    set preventDefault(preventDefault: (() => void)) {
        this.setPreventDefault(preventDefault)
    }
    static ctor_touchevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TouchEventInternal.ctor_touchevent()
        this.peer = new Finalizable(ctorPtr, TouchEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TouchEvent_getFinalizer()
    }
    public getHistoricalPoints(): Array<HistoricalPoint> {
        return this.getHistoricalPoints_serialize()
    }
    private getType(): TouchType {
        return this.getType_serialize()
    }
    private setType(type: TouchType): void {
        const type_casted = type as (TouchType)
        this.setType_serialize(type_casted)
        return
    }
    private getTouches(): Array<TouchObject> {
        return this.getTouches_serialize()
    }
    private setTouches(touches: Array<TouchObject>): void {
        const touches_casted = touches as (Array<TouchObject>)
        this.setTouches_serialize(touches_casted)
        return
    }
    private getChangedTouches(): Array<TouchObject> {
        return this.getChangedTouches_serialize()
    }
    private setChangedTouches(changedTouches: Array<TouchObject>): void {
        const changedTouches_casted = changedTouches as (Array<TouchObject>)
        this.setChangedTouches_serialize(changedTouches_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getPreventDefault(): (() => void) {
        return this.getPreventDefault_serialize()
    }
    private setPreventDefault(preventDefault: (() => void)): void {
        const preventDefault_casted = preventDefault as ((() => void))
        this.setPreventDefault_serialize(preventDefault_casted)
        return
    }
    private getHistoricalPoints_serialize(): Array<HistoricalPoint> {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getHistoricalPoints(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<HistoricalPoint> = new Array<HistoricalPoint>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHistoricalPoint()
        }
        const returnResult : Array<HistoricalPoint> = buffer
        return returnResult
    }
    private getType_serialize(): TouchType {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getType(this.peer!.ptr)
        return TypeChecker.TouchType_FromNumeric(retval)
    }
    private setType_serialize(type: TouchType): void {
        ArkUIGeneratedNativeModule._TouchEvent_setType(this.peer!.ptr, TypeChecker.TouchType_ToNumeric(type))
    }
    private getTouches_serialize(): Array<TouchObject> {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getTouches(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<TouchObject> = new Array<TouchObject>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTouchObject()
        }
        const returnResult : Array<TouchObject> = buffer
        return returnResult
    }
    private setTouches_serialize(touches: Array<TouchObject>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(touches.length as int32)
        for (let i = 0; i < touches.length; i++) {
            const touches_element : TouchObject = touches[i]
            thisSerializer.writeTouchObject(touches_element)
        }
        ArkUIGeneratedNativeModule._TouchEvent_setTouches(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getChangedTouches_serialize(): Array<TouchObject> {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getChangedTouches(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<TouchObject> = new Array<TouchObject>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTouchObject()
        }
        const returnResult : Array<TouchObject> = buffer
        return returnResult
    }
    private setChangedTouches_serialize(changedTouches: Array<TouchObject>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(changedTouches.length as int32)
        for (let i = 0; i < changedTouches.length; i++) {
            const changedTouches_element : TouchObject = changedTouches[i]
            thisSerializer.writeTouchObject(changedTouches_element)
        }
        ArkUIGeneratedNativeModule._TouchEvent_setChangedTouches(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._TouchEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPreventDefault_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getPreventDefault(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setPreventDefault_serialize(preventDefault: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(preventDefault)
        ArkUIGeneratedNativeModule._TouchEvent_setPreventDefault(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): TouchEventInternal {
        const obj : TouchEventInternal = new TouchEventInternal()
        obj.peer = new Finalizable(ptr, TouchEventInternal.getFinalizer())
        return obj
    }
}
export namespace cursorControl {
    export function setCursor(value: PointerStyle): void {
        GlobalScope.cursorControl_setCursor(value)
    }
    export function restoreDefault(): void {
        GlobalScope.cursorControl_restoreDefault()
    }
}
export namespace focusControl {
    export function requestFocus(value: string): boolean {
        return GlobalScope.focusControl_requestFocus(value)
    }
}

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
import { Callback_Void } from "./abilityComponent"
import { MouseButton, MouseAction, AccessibilityHoverType, TouchType, KeyType, KeySource, Color, TextDecorationType, TextDecorationStyle, Curve, PlayMode, SharedTransitionEffectType, HorizontalAlign, VerticalAlign, TransitionType, FontWeight, FontStyle, ColoringStrategy, BorderStyle, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, GradientDirection, HitTestMode, Alignment, ImageSize, HoverEffect, Visibility, ItemAlign, Direction, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, LineCapStyle, LineJoinStyle, PixelRoundCalcPolicy, BarState, EdgeEffect, IlluminatedType } from "./enums"
import { UnifiedData, UnifiedDataInternal } from "./../generated/ArkUnifiedDataMaterialized"
import { ResourceColor, ConstraintSizeOptions, DirectionalEdgesT, Length, Bias, Area, Font, BorderRadiuses, EdgeWidths, LocalizedEdgeWidths, SizeOptions, ResourceStr, Dimension, EdgeColors, LocalizedEdgeColors, EdgeStyles, Position, LocalizedBorderRadiuses, Margin, ChainWeightOptions, Padding, LocalizedPadding, LocalizedMargin, BorderOptions, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, EdgeWidth } from "./units"
import { Resource } from "global/resource";
import { NodeAttach, remember } from "@koalaui/runtime"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { PointerStyle } from "./../generated/ArkArkuiCustomInterfaces"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./button"
import { BaseGestureEvent, GestureRecognizer, GestureJudgeResult, GestureInfo, GestureType, GestureMask, GestureHandler, GesturePriority } from "./gesture"
import { Callback_Number_Void } from "./alphabetIndexer"
import { AnimationRange_Number } from "./../generated/SyntheticDeclarations"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { ArkCommonComponent } from "./../generated/ArkCommon"
import { ArkCommonPeer } from "./../generated/peers/ArkCommonPeer"
import { Callback_Number_Number_Void } from "./grid"
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./scroll"
import { ScrollState } from "./list"
import { GlobalScope } from "./../generated/peers/GlobalScope"
import { _animateTo } from "../handwritten"
export  { CommonModifier } from "../ohos.arkui.modifier"

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
        thisSerializer.writeInt32(effect_move.valueOf())
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
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_move(edge.valueOf())
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
    timestamp: number
    source: SourceType
    axisHorizontal?: number
    axisVertical?: number
    pressure: number
    tiltX: number
    tiltY: number
    sourceTool: SourceTool
    deviceId?: number
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
    get timestamp(): number {
        return this.getTimestamp()
    }
    set timestamp(timestamp: number) {
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
    private getTimestamp(): number {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: number): void {
        const timestamp_casted = timestamp as (number)
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
    private getAxisHorizontal(): number {
        return this.getAxisHorizontal_serialize()
    }
    private setAxisHorizontal(axisHorizontal: number): void {
        const axisHorizontal_casted = axisHorizontal as (number)
        this.setAxisHorizontal_serialize(axisHorizontal_casted)
        return
    }
    private getAxisVertical(): number {
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
    private getDeviceId(): number {
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
    private getTimestamp_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTimestamp(this.peer!.ptr, timestamp)
    }
    private getSource_serialize(): SourceType {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getSource(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setSource_serialize(source: SourceType): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSource(this.peer!.ptr, source.valueOf())
    }
    private getAxisHorizontal_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisHorizontal(this.peer!.ptr)
        return retval
    }
    private setAxisHorizontal_serialize(axisHorizontal: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisHorizontal(this.peer!.ptr, axisHorizontal)
    }
    private getAxisVertical_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisVertical(this.peer!.ptr)
        return retval
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setSourceTool_serialize(sourceTool: SourceTool): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSourceTool(this.peer!.ptr, sourceTool.valueOf())
    }
    private getDeviceId_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getDeviceId(this.peer!.ptr)
        return retval
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setButton_serialize(button: MouseButton): void {
        ArkUIGeneratedNativeModule._MouseEvent_setButton(this.peer!.ptr, button.valueOf())
    }
    private getAction_serialize(): MouseAction {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getAction(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setAction_serialize(action: MouseAction): void {
        ArkUIGeneratedNativeModule._MouseEvent_setAction(this.peer!.ptr, action.valueOf())
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: AccessibilityHoverType): void {
        ArkUIGeneratedNativeModule._AccessibilityHoverEvent_setType(this.peer!.ptr, type.valueOf())
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: TouchType): void {
        ArkUIGeneratedNativeModule._TouchEvent_setType(this.peer!.ptr, type.valueOf())
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
        ArkUIGeneratedNativeModule._DragEvent_setResult(this.peer!.ptr, dragResult.valueOf())
    }
    private getResult_serialize(): DragResult {
        const retval  = ArkUIGeneratedNativeModule._DragEvent_getResult(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setDragBehavior_serialize(dragBehavior: DragBehavior): void {
        ArkUIGeneratedNativeModule._DragEvent_setDragBehavior(this.peer!.ptr, dragBehavior.valueOf())
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
    timestamp: number
    stopPropagation: (() => void)
    intentionCode: IntentionCode
    unicode?: number
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
    get timestamp(): number {
        return this.getTimestamp()
    }
    set timestamp(timestamp: number) {
        this.setTimestamp(timestamp)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    get intentionCode(): IntentionCode {
        throw new Error("Not implemented")
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
    private getTimestamp(): number {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: number): void {
        const timestamp_casted = timestamp as (number)
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
    private getUnicode(): number {
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: KeyType): void {
        ArkUIGeneratedNativeModule._KeyEvent_setType(this.peer!.ptr, type.valueOf())
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
        throw new Error("Object deserialization is not implemented.")
    }
    private setKeySource_serialize(keySource: KeySource): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeySource(this.peer!.ptr, keySource.valueOf())
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
    private getTimestamp_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: number): void {
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : IntentionCode = retvalDeserializer.readIntentionCode()
        return returnResult
    }
    private setIntentionCode_serialize(intentionCode: IntentionCode): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeIntentionCode(intentionCode)
        ArkUIGeneratedNativeModule._KeyEvent_setIntentionCode(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getUnicode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getUnicode(this.peer!.ptr)
        return retval
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
            thisSerializer.writeInt32(color_0.valueOf())
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
            thisSerializer.writeInt32(value_0.valueOf())
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
    public create(value: object): object {
        const value_casted = value as (object)
        return this.create_serialize(value_casted)
    }
    private create_serialize(value: object): object {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Any", value)
        const retval  = ArkUIGeneratedNativeModule._View_create(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    setOnClick(callback_?: ((event: ClickEvent) => void)): void
    setOnTouch(callback_?: ((event: TouchEvent) => void)): void
    setOnAppear(callback_?: (() => void)): void
    setOnDisappear(callback_?: (() => void)): void
    setOnKeyEvent(callback_?: ((event: KeyEvent) => void)): void
    setOnFocus(callback_?: (() => void)): void
    setOnBlur(callback_?: (() => void)): void
    setOnHover(callback_?: HoverCallback): void
    setOnMouse(callback_?: ((event: MouseEvent) => void)): void
    setOnSizeChange(callback_?: SizeChangeCallback): void
    setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void
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
    public setOnClick(callback_?: ((event: ClickEvent) => void)): void {
        const callback__casted = callback_ as (((event: ClickEvent) => void) | undefined)
        this.setOnClick_serialize(callback__casted)
        return
    }
    public setOnTouch(callback_?: ((event: TouchEvent) => void)): void {
        const callback__casted = callback_ as (((event: TouchEvent) => void) | undefined)
        this.setOnTouch_serialize(callback__casted)
        return
    }
    public setOnAppear(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnAppear_serialize(callback__casted)
        return
    }
    public setOnDisappear(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnDisappear_serialize(callback__casted)
        return
    }
    public setOnKeyEvent(callback_?: ((event: KeyEvent) => void)): void {
        const callback__casted = callback_ as (((event: KeyEvent) => void) | undefined)
        this.setOnKeyEvent_serialize(callback__casted)
        return
    }
    public setOnFocus(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnFocus_serialize(callback__casted)
        return
    }
    public setOnBlur(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.setOnBlur_serialize(callback__casted)
        return
    }
    public setOnHover(callback_?: HoverCallback): void {
        const callback__casted = callback_ as (HoverCallback | undefined)
        this.setOnHover_serialize(callback__casted)
        return
    }
    public setOnMouse(callback_?: ((event: MouseEvent) => void)): void {
        const callback__casted = callback_ as (((event: MouseEvent) => void) | undefined)
        this.setOnMouse_serialize(callback__casted)
        return
    }
    public setOnSizeChange(callback_?: SizeChangeCallback): void {
        const callback__casted = callback_ as (SizeChangeCallback | undefined)
        this.setOnSizeChange_serialize(callback__casted)
        return
    }
    public setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void {
        const options_casted = options as (VisibleAreaEventOptions)
        const event_casted = event as (VisibleAreaChangeCallback | undefined)
        this.setOnVisibleAreaApproximateChange_serialize(options_casted, event_casted)
        return
    }
    private setOnClick_serialize(callback_?: ((event: ClickEvent) => void)): void {
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
    private setOnTouch_serialize(callback_?: ((event: TouchEvent) => void)): void {
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
    private setOnAppear_serialize(callback_?: (() => void)): void {
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
    private setOnDisappear_serialize(callback_?: (() => void)): void {
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
    private setOnKeyEvent_serialize(callback_?: ((event: KeyEvent) => void)): void {
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
    private setOnFocus_serialize(callback_?: (() => void)): void {
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
    private setOnBlur_serialize(callback_?: (() => void)): void {
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
    private setOnHover_serialize(callback_?: HoverCallback): void {
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
    private setOnMouse_serialize(callback_?: ((event: MouseEvent) => void)): void {
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
    private setOnSizeChange_serialize(callback_?: SizeChangeCallback): void {
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
    private setOnVisibleAreaApproximateChange_serialize(options: VisibleAreaEventOptions, event?: VisibleAreaChangeCallback): void {
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
// declare function getContext(arg0: Object): Context
export interface Context {
    _ContextStub: string;
}
// declare function postCardAction(arg0: Object, arg1: Object): void
export interface Configuration {
    colorMode: string;
    fontScale: number;
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
// declare function dollar_r(arg0: string, arg1: Array<object>): Resource
// declare function dollar_rawfile(arg0: string): Resource
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
// declare function animateTo(arg0: AnimateParam, arg1: (() => void)): void
// declare function animateToImmediately(arg0: AnimateParam, arg1: (() => void)): void
// declare function vp2px(arg0: number): number
// declare function px2vp(arg0: number): number
// declare function fp2px(arg0: number): number
// declare function px2fp(arg0: number): number
// declare function lpx2px(arg0: number): number
// declare function px2lpx(arg0: number): number
declare function requestFocus(arg0: string): boolean
declare function setCursor(arg0: PointerStyle): void
declare function restoreDefault(): void
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
export type Tuple_Number_Number = [
    number,
    number
]
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
    timestamp: number;
}
export type SizeChangeCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
export type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>) => GestureJudgeResult;
export type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
export type TransitionFinishCallback = (transitionIn: boolean) => void;
export enum DragBehavior {
    COPY = 0,
    MOVE = 1
}
export interface Summary {
    _SummaryStub: string;
}
export interface UniformDataType {
    _UniformDataTypeStub: string;
}
export enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4
}
export enum BlendMode {
    NONE = 0,
    CLEAR = 1,
    SRC = 2,
    DST = 3,
    SRC_OVER = 4,
    DST_OVER = 5,
    SRC_IN = 6,
    DST_IN = 7,
    SRC_OUT = 8,
    DST_OUT = 9,
    SRC_ATOP = 10,
    DST_ATOP = 11,
    XOR = 12,
    PLUS = 13,
    MODULATE = 14,
    SCREEN = 15,
    OVERLAY = 16,
    DARKEN = 17,
    LIGHTEN = 18,
    COLOR_DODGE = 19,
    COLOR_BURN = 20,
    HARD_LIGHT = 21,
    SOFT_LIGHT = 22,
    DIFFERENCE = 23,
    EXCLUSION = 24,
    MULTIPLY = 25,
    HUE = 26,
    SATURATION = 27,
    COLOR = 28,
    LUMINOSITY = 29
}
export enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1
}
export interface IntentionCode {
    _IntentionCodeStub: string;
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
    layoutRegionMargin?: Margin;
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
export interface ContentModifier<T> {
    stub: string;
}
export interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
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
export interface ImageModifier {
    _ImageModifierStub: string;
}
export interface SymbolGlyphModifier {
    _SymbolGlyphModifierStub: string;
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
export type CustomBuilder = 
/** @memo */
() => void;
export type CommonInteface = (...pamra:Object[])=>CommonAttribute
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
    margin: Margin;
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
    borderWidth: EdgeWidth;
    margin: Margin;
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
export interface UIContext {
    _UIContextStub: string;
}
export interface DrawContext {
    _DrawContextStub: string;
}
export interface VisualEffect {
    _VisualEffectStub: string;
}
export interface Filter {
    _FilterStub: string;
}
export interface Blender {
    _BlenderStub: string;
}
export interface ComponentContent {
    _ComponentContentStub: string;
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
export interface ScrollResult {
    offsetRemain: number;
}
export interface OnWillScrollCallback {
    stub: string;
}
export type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
export type OnMoveHandler = (from: number, to: number) => void;
export interface DynamicNode {
    onMove(handler: OnMoveHandler | undefined): DynamicNode
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
    _animateTo(value, event)
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
export namespace cursorControl {
    export function setCursor(value: PointerStyle): void {
        GlobalScope.cursorControl_setCursor(value)
    }
}
export namespace cursorControl {
    export function restoreDefault(): void {
        GlobalScope.cursorControl_restoreDefault()
    }
}
export namespace focusControl {
    export function requestFocus(value: string): boolean {
        return GlobalScope.focusControl_requestFocus(value)
    }
}

/** @memo:stable */
export interface CommonMethod {

    /** @memo */
    width(value: Length): this
    /** @memo */
    height(value: Length): this
    /** @memo */
    drawModifier(value?: DrawModifier): this
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
    margin(value: Margin | Length | LocalizedMargin): this
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
    transform(value: Object): this
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
    clickEffect(value?: ClickEffect): this
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
    allowDrop(value?: Array<UniformDataType>): this
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
    clip(value?: boolean): this
    /** @memo */
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this
    /** @memo */
    mask(value?: ProgressMask): this
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
    customProperty(name: string, value?: Object): this
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
    advancedBlendMode(effect: BlendMode | Blender, type?: BlendApplyType): this
    /** @memo */
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this
    /** @memo */
    bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this
    /** @memo */
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this
    /** @memo */
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | undefined | ContentCoverOptions | undefined): this
    /** @memo */
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this
    /** @memo */
    onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this
    /** @memo */
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this
    /** @memo */
    attributeModifier<T>(modifier:AttributeModifier<T>): this
}
/** @memo:stable */
export interface CommonShapeMethod extends CommonMethod {
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
}
/** @memo:stable */
export interface CommonAttribute extends CommonMethod {
    /** @memo */
    setCommonOptions(): this;
}

export interface AttributeModifier<T> {
    applyNormalAttribute(instance: T) : void;
    applyPressedAttribute(instance: T) : void;
    applyFocusedAttribute(instance: T) : void;
    applyDisabledAttribute(instance: T) : void;
    applySelectedAttribute(instance: T) : void;
}
/** @memo:stable */
export interface ScrollableCommonMethod extends CommonMethod {
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
    onWillScroll(value?: ScrollOnWillScrollCallback): this
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
    fadingEdge(enabled?: boolean, options?: FadingEdgeOptions): this
}

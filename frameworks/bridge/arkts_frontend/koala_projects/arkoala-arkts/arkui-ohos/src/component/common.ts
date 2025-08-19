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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, InteropNativeModule } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { DrawContext } from "./../Graphics"
import { LengthMetrics } from "../Graphics"
import { UnifiedData, UnifiedDataInternal, ComponentContent, Context, PointerStyle, ContextInternal, GestureOps, StateStylesOps } from "./arkui-custom"
import { UIContext } from "@ohos/arkui/UIContext"
import { Summary, IntentionCode, CircleShape, EllipseShape, PathShape, RectShape, SymbolGlyphModifier, ImageModifier } from "./arkui-external"
import { KeyType, KeySource, Color, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, Direction, ObscuredReasons, RenderFit, FocusDrawLevel, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, LineCapStyle, LineJoinStyle, BarState, CrownSensitivity, EdgeEffect, TextDecorationType, TextDecorationStyle, Curve, PlayMode, SharedTransitionEffectType, GradientDirection, HorizontalAlign, VerticalAlign, TransitionType, FontWeight, FontStyle, TouchType, InteractionHand, CrownAction, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, PixelRoundCalcPolicy, IlluminatedType, MouseButton, MouseAction, AccessibilityHoverType, AxisAction, AxisModel, ScrollSource } from "./enums"
import { ResourceColor, ConstraintSizeOptions, DirectionalEdgesT, SizeOptions, Length, ChainWeightOptions, Padding, LocalizedPadding, Position, BorderOptions, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Bias, Font, EdgeStyles, Edges } from "./units"
import { Resource } from "global.resource"
import { TextRange } from "./textCommon"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ResizableOptions } from "./image"
import { VisualEffect, Filter, BrightnessBlender } from "./arkui-uieffect"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { TransformationMatrix } from "./arkui-common"
import { UniformDataType } from "./arkui-uniformtypedescriptor"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface, GestureHandler, GesturePriority, Gesture, GestureGroup, GestureGroupHandler } from "./gesture"
import { PixelMap } from "./arkui-pixelmap"
import { StyledString } from "./styledString"
import { Callback_Number_Number_Void } from "./grid"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Tuple_Number_Number } from "./arkui-synthetics"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./button"
import { Callback_Number_Void } from "./alphabetIndexer"
import { AnimationRange_Number } from "./type-replacements"
import { ScrollState } from "./list"
import { _animateTo, _animationStart, _animationStop } from "./../handwritten/ArkAnimation"
import { GlobalScope } from "./GlobalScope"
import { ArkCommonAttributeSet, applyUIAttributes, applyUIAttributesUpdate } from "../handwritten/modifiers/ArkCommonModifier"
import { CommonModifier } from "../CommonModifier"
import { AttributeUpdater } from "../ohos.arkui.modifier"
import { ArkBaseNode } from "../handwritten/modifiers/ArkBaseNode"
import { hookStateStyleImpl } from "../handwritten/ArkStateStyle"
import { rememberMutableState } from '@koalaui/runtime'
import { hookDrawModifierInvalidateImpl, hookDrawModifierAttributeImpl } from "../handwritten/ArkDrawModifierImpl"
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
        return obj
    }
}
export class DrawModifier  {
    weakRefOfPeerNode ?: WeakRef<PeerNode>;
    constructor() {
    }
    public drawBehind(drawContext: DrawContext): void {
        return
    }
    public drawContent(drawContext: DrawContext): void {
        return
    }
    public drawFront(drawContext: DrawContext): void {
        return
    }
    public invalidate(): void {
        hookDrawModifierInvalidateImpl(this);
        return
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
    rollAngle?: number | undefined
    sourceTool: SourceTool
    deviceId?: number | undefined
    targetDisplayId?: number | undefined
    getModifierKeyState?: ((keys: Array<string>) => boolean)
}
export class BaseEventInternal implements MaterializedBase,BaseEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get target(): EventTarget {
        return this.getTarget();
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
    get rollAngle(): number | undefined {
        return this.getRollAngle()
    }
    set rollAngle(rollAngle: number | undefined) {
        const rollAngle_NonNull  = (rollAngle as number)
        this.setRollAngle(rollAngle_NonNull)
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
    get targetDisplayId(): number | undefined {
        return this.getTargetDisplayId()
    }
    set targetDisplayId(targetDisplayId: number | undefined) {
        const targetDisplayId_NonNull  = (targetDisplayId as number)
        this.setTargetDisplayId(targetDisplayId_NonNull)
    }
    get getModifierKeyState(): ((keys: Array<string>) => boolean) {
        return this.getGetModifierKeyState();
    }
    set getModifierKeyState(getModifierKeyState: ((keys: Array<string>) => boolean) | undefined) {
        // setter is not implemented
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
    private getGetModifierKeyState(): ((keys: Array<string>) => boolean) {
        return (keys: Array<string>): boolean => {
            const keys_casted = keys as (Array<string>)
            return this.getModifierKeyState_serialize(keys_casted)
        }
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
    private getRollAngle(): number | undefined {
        return this.getRollAngle_serialize()
    }
    private setRollAngle(rollAngle: number): void {
        const rollAngle_casted = rollAngle as (number)
        this.setRollAngle_serialize(rollAngle_casted)
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
    private getTargetDisplayId(): number | undefined {
        return this.getTargetDisplayId_serialize()
    }
    private setTargetDisplayId(targetDisplayId: number): void {
        const targetDisplayId_casted = targetDisplayId as (number)
        this.setTargetDisplayId_serialize(targetDisplayId_casted)
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTarget(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisHorizontal(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
    }
    private setAxisHorizontal_serialize(axisHorizontal: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisHorizontal(this.peer!.ptr, axisHorizontal)
    }
    private getAxisVertical_serialize(): number | undefined {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getAxisVertical(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
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
    private getRollAngle_serialize(): number | undefined {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getRollAngle(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
    }
    private setRollAngle_serialize(rollAngle: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setRollAngle(this.peer!.ptr, rollAngle)
    }
    private getSourceTool_serialize(): SourceTool {
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getSourceTool(this.peer!.ptr)
        return TypeChecker.SourceTool_FromNumeric(retval)
    }
    private setSourceTool_serialize(sourceTool: SourceTool): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSourceTool(this.peer!.ptr, TypeChecker.SourceTool_ToNumeric(sourceTool))
    }
    private getDeviceId_serialize(): number | undefined {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getDeviceId(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
    }
    private setDeviceId_serialize(deviceId: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setDeviceId(this.peer!.ptr, deviceId)
    }
    private getTargetDisplayId_serialize(): number | undefined {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._BaseEvent_getTargetDisplayId(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
    }
    private setTargetDisplayId_serialize(targetDisplayId: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTargetDisplayId(this.peer!.ptr, targetDisplayId)
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
    getModifierKeyState?: ((keys: Array<string>) => boolean)
    executeDropAnimation(customDropAnimation: (() => void)): void
    startDataLoading(options: DataSyncOptions): string
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
    get getModifierKeyState(): ((keys: Array<string>) => boolean) {
        return this.getGetModifierKeyState();
    }
    set getModifierKeyState(getModifierKeyState: ((keys: Array<string>) => boolean) | undefined) {
        // setter is not implemented
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
    public getGetModifierKeyState(): ((keys: Array<string>) => boolean) {
        return (keys: Array<string>): boolean => {
            const keys_casted = keys as (Array<string>)
            return this.getModifierKeyState_serialize(keys_casted)
        }
    }
    public executeDropAnimation(customDropAnimation: (() => void)): void {
        const customDropAnimation_casted = customDropAnimation as ((() => void))
        this.executeDropAnimation_serialize(customDropAnimation_casted)
        return
    }
    public startDataLoading(options: DataSyncOptions): string {
        const options_casted = options as (DataSyncOptions)
        return this.startDataLoading_serialize(options_casted)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
    private executeDropAnimation_serialize(customDropAnimation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(customDropAnimation)
        ArkUIGeneratedNativeModule._DragEvent_executeDropAnimation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private startDataLoading_serialize(options: DataSyncOptions): string {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDataSyncOptions(options)
        const retval  = ArkUIGeneratedNativeModule._DragEvent_startDataLoading(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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

export type CustomStyles =  (instance: CommonMethod) => void;
export interface StateStyles {
    normal?: CustomStyles;
    pressed?: CustomStyles;
    disabled?: CustomStyles;
    focused?: CustomStyles;
    clicked?: CustomStyles;
    selected?: CustomStyles;
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
        return this.getStopPropagation()
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
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._KeyEvent_getStopPropagation(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult = retvalDeserializer.readCallback_Void(true);
        return returnResult
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
    uniqueId?: number | undefined
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
    get uniqueId(): number | undefined {
        return this.getUniqueId()
    }
    set uniqueId(uniqueId: number | undefined) {
        const uniqueId_NonNull  = (uniqueId as number)
        this.setUniqueId(uniqueId_NonNull)
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
    private getUniqueId(): number | undefined {
        return this.getUniqueId_serialize()
    }
    private setUniqueId(uniqueId: number): void {
        const uniqueId_casted = uniqueId as (number)
        this.setUniqueId_serialize(uniqueId_casted)
        return
    }
    private measure_serialize(constraint: ConstraintSizeOptions): MeasureResult {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(constraint)
        const retval  = ArkUIGeneratedNativeModule._Measurable_measure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : MeasureResult = retvalDeserializer.readMeasureResult()
        return returnResult
    }
    private getMargin_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getMargin(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getPadding_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getPadding(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getBorderWidth_serialize(): DirectionalEdgesT {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getBorderWidth(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : DirectionalEdgesT = retvalDeserializer.readDirectionalEdgesT()
        return returnResult
    }
    private getUniqueId_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Measurable_getUniqueId(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setUniqueId_serialize(uniqueId: number): void {
        ArkUIGeneratedNativeModule._Measurable_setUniqueId(this.peer!.ptr, uniqueId)
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
    public addText(text: string, textOperationOptions?: TextContentControllerOptions): number {
        const text_casted = text as (string)
        const textOperationOptions_casted = textOperationOptions as (TextContentControllerOptions | undefined)
        return this.addText_serialize(text_casted, textOperationOptions_casted)
    }
    public deleteText(range?: TextRange): void {
        const range_casted = range as (TextRange | undefined)
        this.deleteText_serialize(range_casted)
        return
    }
    public getSelection(): TextRange {
        return this.getSelection_serialize()
    }
    public clearPreviewText(): void {
        this.clearPreviewText_serialize()
        return
    }
    public getText(range?: TextRange): string {
        const range_casted = range as (TextRange | undefined)
        return this.getText_serialize(range_casted)
    }
    private getCaretOffset_serialize(): CaretOffset {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getCaretOffset(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : CaretOffset = retvalDeserializer.readCaretOffset()
        return returnResult
    }
    private getTextContentRect_serialize(): RectResult {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentRect(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private getTextContentLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentLineCount(this.peer!.ptr)
        return retval
    }
    private addText_serialize(text: string, textOperationOptions?: TextContentControllerOptions): number {
        const thisSerializer : Serializer = Serializer.hold()
        let textOperationOptions_type : int32 = RuntimeType.UNDEFINED
        textOperationOptions_type = runtimeType(textOperationOptions)
        thisSerializer.writeInt8(textOperationOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (textOperationOptions_type)) {
            const textOperationOptions_value  = textOperationOptions!
            thisSerializer.writeTextContentControllerOptions(textOperationOptions_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_addText(this.peer!.ptr, text, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private deleteText_serialize(range?: TextRange): void {
        const thisSerializer : Serializer = Serializer.hold()
        let range_type : int32 = RuntimeType.UNDEFINED
        range_type = runtimeType(range)
        thisSerializer.writeInt8(range_type as int32)
        if ((RuntimeType.UNDEFINED) != (range_type)) {
            const range_value  = range!
            thisSerializer.writeTextRange(range_value)
        }
        ArkUIGeneratedNativeModule._TextContentControllerBase_deleteText(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSelection_serialize(): TextRange {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getSelection(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : TextRange = retvalDeserializer.readTextRange()
        return returnResult
    }
    private clearPreviewText_serialize(): void {
        ArkUIGeneratedNativeModule._TextContentControllerBase_clearPreviewText(this.peer!.ptr)
    }
    private getText_serialize(range?: TextRange): string {
        const thisSerializer : Serializer = Serializer.hold()
        let range_type : int32 = RuntimeType.UNDEFINED
        range_type = runtimeType(range)
        thisSerializer.writeInt8(range_type as int32)
        if ((RuntimeType.UNDEFINED) != (range_type)) {
            const range_value  = range!
            thisSerializer.writeTextRange(range_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getText(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    _attributeSet?: ArkCommonAttributeSet;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCommonMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CommonMethod_construct(peerId, flags)
        const _peer  = new ArkCommonMethodPeer(_peerPtr, peerId, "CommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    width0Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_width0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    width1Attribute(value: Length | LayoutPolicy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isLayoutPolicy(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LayoutPolicy
                thisSerializer.writeLayoutPolicy(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_width1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    height0Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_height0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    height1Attribute(value: Length | LayoutPolicy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isLayoutPolicy(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LayoutPolicy
                thisSerializer.writeLayoutPolicy(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_height1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    drawModifierAttribute(value: DrawModifier | undefined): void {
        hookDrawModifierAttributeImpl(this,value)
    }
    responseRegionAttribute(value: Array<Rectangle> | Rectangle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_Rectangle(value_value))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<Rectangle>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : Rectangle = value_value_0[i]
                    thisSerializer.writeRectangle(value_value_0_element)
                }
            }
            else if (TypeChecker.isRectangle(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Rectangle
                thisSerializer.writeRectangle(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_responseRegion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mouseResponseRegionAttribute(value: Array<Rectangle> | Rectangle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_Rectangle(value_value))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<Rectangle>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : Rectangle = value_value_0[i]
                    thisSerializer.writeRectangle(value_value_0_element)
                }
            }
            else if (TypeChecker.isRectangle(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Rectangle
                thisSerializer.writeRectangle(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_mouseResponseRegion(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeConstraintSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_constraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    touchableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_touchable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hitTestBehaviorAttribute(value: HitTestMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as HitTestMode)
            thisSerializer.writeInt32(TypeChecker.HitTestMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_hitTestBehavior(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChildTouchTestAttribute(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onChildTouchTest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutWeightAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_layoutWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainWeightAttribute(value: ChainWeightOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeChainWeightOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_chainWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Length | LocalizedPadding | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                const value_value_0_top  = value_value_0.top
                let value_value_0_top_type : int32 = RuntimeType.UNDEFINED
                value_value_0_top_type = runtimeType(value_value_0_top)
                thisSerializer.writeInt8(value_value_0_top_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_top_type)) {
                    const value_value_0_top_value  = value_value_0_top!
                    thisSerializer.writeLength(value_value_0_top_value)
                }
                const value_value_0_right  = value_value_0.right
                let value_value_0_right_type : int32 = RuntimeType.UNDEFINED
                value_value_0_right_type = runtimeType(value_value_0_right)
                thisSerializer.writeInt8(value_value_0_right_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_right_type)) {
                    const value_value_0_right_value  = value_value_0_right!
                    thisSerializer.writeLength(value_value_0_right_value)
                }
                const value_value_0_bottom  = value_value_0.bottom
                let value_value_0_bottom_type : int32 = RuntimeType.UNDEFINED
                value_value_0_bottom_type = runtimeType(value_value_0_bottom)
                thisSerializer.writeInt8(value_value_0_bottom_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_bottom_type)) {
                    const value_value_0_bottom_value  = value_value_0_bottom!
                    thisSerializer.writeLength(value_value_0_bottom_value)
                }
                const value_value_0_left  = value_value_0.left
                let value_value_0_left_type : int32 = RuntimeType.UNDEFINED
                value_value_0_left_type = runtimeType(value_value_0_left)
                thisSerializer.writeInt8(value_value_0_left_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_left_type)) {
                    const value_value_0_left_value  = value_value_0_left!
                    thisSerializer.writeLength(value_value_0_left_value)
                }
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Length
                thisSerializer.writeLength(value_value_1)
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedPadding
                thisSerializer.writeLocalizedPadding(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_padding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    safeAreaPaddingAttribute(value: Padding | LengthMetrics | LocalizedPadding | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                const value_value_0_top  = value_value_0.top
                let value_value_0_top_type : int32 = RuntimeType.UNDEFINED
                value_value_0_top_type = runtimeType(value_value_0_top)
                thisSerializer.writeInt8(value_value_0_top_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_top_type)) {
                    const value_value_0_top_value  = value_value_0_top!
                    thisSerializer.writeLength(value_value_0_top_value)
                }
                const value_value_0_right  = value_value_0.right
                let value_value_0_right_type : int32 = RuntimeType.UNDEFINED
                value_value_0_right_type = runtimeType(value_value_0_right)
                thisSerializer.writeInt8(value_value_0_right_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_right_type)) {
                    const value_value_0_right_value  = value_value_0_right!
                    thisSerializer.writeLength(value_value_0_right_value)
                }
                const value_value_0_bottom  = value_value_0.bottom
                let value_value_0_bottom_type : int32 = RuntimeType.UNDEFINED
                value_value_0_bottom_type = runtimeType(value_value_0_bottom)
                thisSerializer.writeInt8(value_value_0_bottom_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_bottom_type)) {
                    const value_value_0_bottom_value  = value_value_0_bottom!
                    thisSerializer.writeLength(value_value_0_bottom_value)
                }
                const value_value_0_left  = value_value_0.left
                let value_value_0_left_type : int32 = RuntimeType.UNDEFINED
                value_value_0_left_type = runtimeType(value_value_0_left)
                thisSerializer.writeInt8(value_value_0_left_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_left_type)) {
                    const value_value_0_left_value  = value_value_0_left!
                    thisSerializer.writeLength(value_value_0_left_value)
                }
            }
            else if (TypeChecker.isLengthMetrics(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LengthMetrics
                thisSerializer.writeLengthMetrics(value_value_1)
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedPadding
                thisSerializer.writeLocalizedPadding(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_safeAreaPadding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    marginAttribute(value: Padding | Length | LocalizedPadding | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                thisSerializer.writePadding(value_value_0)
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Length
                thisSerializer.writeLength(value_value_1)
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedPadding
                thisSerializer.writeLocalizedPadding(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_margin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColor0Attribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColor1Attribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pixelRoundAttribute(value: PixelRoundPolicy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePixelRoundPolicy(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_pixelRound(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageSizeAttribute(value: SizeOptions | ImageSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as SizeOptions
                thisSerializer.writeSizeOptions(value_value_0)
            }
            else if (TypeChecker.isImageSize(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ImageSize
                thisSerializer.writeInt32(TypeChecker.ImageSize_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImagePositionAttribute(value: Position | Alignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Position
                thisSerializer.writePosition(value_value_0)
            }
            else if (TypeChecker.isAlignment(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Alignment
                thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImagePosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundEffect0Attribute(value: BackgroundEffectOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBackgroundEffectOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundEffect1Attribute(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundEffectOptions(options_value)
        }
        let sysOptions_type : int32 = RuntimeType.UNDEFINED
        sysOptions_type = runtimeType(sysOptions)
        thisSerializer.writeInt8(sysOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sysOptions_type)) {
            const sysOptions_value  = sysOptions!
            thisSerializer.writeSystemAdaptiveOptions(sysOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageResizableAttribute(value: ResizableOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeResizableOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageResizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundEffectAttribute(value: ForegroundEffectOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeForegroundEffectOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visualEffectAttribute(value: VisualEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeVisualEffect(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_visualEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundFilterAttribute(value: Filter | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFilter(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundFilterAttribute(value: Filter | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFilter(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    compositingFilterAttribute(value: Filter | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFilter(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_compositingFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    opacity0Attribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_opacity0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    opacity1Attribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_opacity1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderAttribute(value: BorderOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBorderOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_border(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle | EdgeStyles | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isBorderStyle(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as BorderStyle
                thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeStyles
                thisSerializer.writeEdgeStyles(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderWidthAttribute(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeWidths
                thisSerializer.writeEdgeWidths(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeWidths
                thisSerializer.writeLocalizedEdgeWidths(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || ((RuntimeType.OBJECT == value_value_type)
                && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeColors
                thisSerializer.writeEdgeColors(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeColors
                thisSerializer.writeLocalizedEdgeColors(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as BorderRadiuses
                thisSerializer.writeBorderRadiuses(value_value_1)
            }
            else if (TypeChecker.isLocalizedBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedBorderRadiuses
                thisSerializer.writeLocalizedBorderRadiuses(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    borderImageAttribute(value: BorderImageOption | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBorderImageOption(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderImage(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outline0Attribute(value: OutlineOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeOutlineOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_outline0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outline1Attribute(value: OutlineOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeOutlineOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_outline1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineStyle0Attribute(value: OutlineStyle | EdgeOutlineStyles | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isOutlineStyle(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as OutlineStyle
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeOutlineStyles
                thisSerializer.writeEdgeOutlineStyles(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineStyle1Attribute(value: OutlineStyle | EdgeOutlineStyles | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isOutlineStyle(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as OutlineStyle
                thisSerializer.writeInt32(TypeChecker.OutlineStyle_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeOutlineStyles
                thisSerializer.writeEdgeOutlineStyles(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineWidth0Attribute(value: Dimension | EdgeOutlineWidths | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isEdgeOutlineWidths(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeOutlineWidths
                thisSerializer.writeEdgeOutlineWidths(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineWidth1Attribute(value: Dimension | EdgeOutlineWidths | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isEdgeOutlineWidths(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeOutlineWidths
                thisSerializer.writeEdgeOutlineWidths(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineColor0Attribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeColors
                thisSerializer.writeEdgeColors(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeColors
                thisSerializer.writeLocalizedEdgeColors(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineColor1Attribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeColors
                thisSerializer.writeEdgeColors(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeColors
                thisSerializer.writeLocalizedEdgeColors(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineRadius0Attribute(value: Dimension | OutlineRadiuses | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isOutlineRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as OutlineRadiuses
                thisSerializer.writeOutlineRadiuses(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineRadius0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineRadius1Attribute(value: Dimension | OutlineRadiuses | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isOutlineRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as OutlineRadiuses
                thisSerializer.writeOutlineRadiuses(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineRadius1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundColor0Attribute(value: ResourceColor | ColoringStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isColoringStrategy(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ColoringStrategy
                thisSerializer.writeInt32(TypeChecker.ColoringStrategy_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundColor1Attribute(value: ResourceColor | ColoringStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isColoringStrategy(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ColoringStrategy
                thisSerializer.writeInt32(TypeChecker.ColoringStrategy_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick0Attribute(value: ((event: ClickEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onClick0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick1Attribute(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let event_type : int32 = RuntimeType.UNDEFINED
        event_type = runtimeType(event)
        thisSerializer.writeInt8(event_type as int32)
        if ((RuntimeType.UNDEFINED) != (event_type)) {
            const event_value  = event!
            thisSerializer.holdAndWriteCallback(event_value)
        }
        let distanceThreshold_type : int32 = RuntimeType.UNDEFINED
        distanceThreshold_type = runtimeType(distanceThreshold)
        thisSerializer.writeInt8(distanceThreshold_type as int32)
        if ((RuntimeType.UNDEFINED) != (distanceThreshold_type)) {
            const distanceThreshold_value  = distanceThreshold!
            thisSerializer.writeNumber(distanceThreshold_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onClick1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHoverAttribute(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onHover(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHoverMoveAttribute(value: ((parameter: HoverEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onHoverMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAccessibilityHoverAttribute(value: AccessibilityCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAccessibilityHover(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hoverEffectAttribute(value: HoverEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as HoverEffect)
            thisSerializer.writeInt32(TypeChecker.HoverEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_hoverEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onMouseAttribute(value: ((event: MouseEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onMouse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchAttribute(value: ((event: TouchEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onTouch(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyEvent0Attribute(value: ((event: KeyEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onKeyEvent0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyEvent1Attribute(value: ((parameter: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onKeyEvent1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDigitalCrownAttribute(value: ((parameter: CrownEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDigitalCrown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyPreImeAttribute(value: ((parameter: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onKeyPreIme(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyEventDispatchAttribute(value: ((parameter: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onKeyEventDispatch(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFocusAxisEventAttribute(value: ((parameter: FocusAxisEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onFocusAxisEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAxisEventAttribute(value: ((parameter: AxisEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAxisEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nextFocusAttribute(value: FocusMovement | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFocusMovement(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_nextFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tabStopAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_tabStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFocusAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBlurAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onBlur(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tabIndexAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_tabIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_defaultFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    groupDefaultFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_groupDefaultFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusOnTouchAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusOnTouch(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusBoxAttribute(value: FocusBoxStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFocusBoxStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusBox(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationAttribute(value: AnimateParam | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeAnimateParam(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_animation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transition0Attribute(value: TransitionOptions | TransitionEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isTransitionOptions(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as TransitionOptions
                thisSerializer.writeTransitionOptions(value_value_0)
            }
            else if (TypeChecker.isTransitionEffect(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as TransitionEffect
                thisSerializer.writeTransitionEffect(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transition1Attribute(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let effect_type : int32 = RuntimeType.UNDEFINED
        effect_type = runtimeType(effect)
        thisSerializer.writeInt8(effect_type as int32)
        if ((RuntimeType.UNDEFINED) != (effect_type)) {
            const effect_value  = effect!
            thisSerializer.writeTransitionEffect(effect_value)
        }
        let onFinish_type : int32 = RuntimeType.UNDEFINED
        onFinish_type = runtimeType(onFinish)
        thisSerializer.writeInt8(onFinish_type as int32)
        if ((RuntimeType.UNDEFINED) != (onFinish_type)) {
            const onFinish_value  = onFinish!
            thisSerializer.holdAndWriteCallback(onFinish_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionBlur0Attribute(value: MotionBlurOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMotionBlurOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_motionBlur0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionBlur1Attribute(value: MotionBlurOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMotionBlurOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_motionBlur1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    brightness0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_brightness0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    brightness1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_brightness1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contrast0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_contrast0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contrast1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_contrast1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    grayscale0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_grayscale0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    grayscale1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_grayscale1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorBlend0Attribute(value: Color | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_colorBlend0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorBlend1Attribute(value: Color | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_colorBlend1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    saturate0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_saturate0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    saturate1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_saturate1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sepia0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sepia0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sepia1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sepia1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    invert0Attribute(value: number | InvertOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as InvertOptions
                thisSerializer.writeInvertOptions(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_invert0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    invert1Attribute(value: number | InvertOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as InvertOptions
                thisSerializer.writeInvertOptions(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_invert1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hueRotate0Attribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_hueRotate0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hueRotate1Attribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_hueRotate1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useShadowBatching0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_useShadowBatching0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useShadowBatching1Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_useShadowBatching1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useEffect0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_useEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useEffect1Attribute(useEffect: boolean | undefined, effectType: EffectType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let useEffect_type : int32 = RuntimeType.UNDEFINED
        useEffect_type = runtimeType(useEffect)
        thisSerializer.writeInt8(useEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (useEffect_type)) {
            const useEffect_value  = useEffect!
            thisSerializer.writeBoolean(useEffect_value)
        }
        let effectType_type : int32 = RuntimeType.UNDEFINED
        effectType_type = runtimeType(effectType)
        thisSerializer.writeInt8(effectType_type as int32)
        if ((RuntimeType.UNDEFINED) != (effectType_type)) {
            const effectType_value  = (effectType as EffectType)
            thisSerializer.writeInt32(TypeChecker.EffectType_ToNumeric(effectType_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_useEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useEffect2Attribute(useEffect: boolean | undefined, effectType?: EffectType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let useEffect_type : int32 = RuntimeType.UNDEFINED
        useEffect_type = runtimeType(useEffect)
        thisSerializer.writeInt8(useEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (useEffect_type)) {
            const useEffect_value  = useEffect!
            thisSerializer.writeBoolean(useEffect_value)
        }
        let effectType_type : int32 = RuntimeType.UNDEFINED
        effectType_type = runtimeType(effectType)
        thisSerializer.writeInt8(effectType_type as int32)
        if ((RuntimeType.UNDEFINED) != (effectType_type)) {
            const effectType_value  = (effectType as EffectType)
            thisSerializer.writeInt32(TypeChecker.EffectType_ToNumeric(effectType_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_useEffect2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderGroup0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_renderGroup0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderGroup1Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_renderGroup1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    freeze0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_freeze0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    freeze1Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_freeze1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    translate0Attribute(value: TranslateOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTranslateOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_translate0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    translate1Attribute(value: TranslateOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTranslateOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_translate1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scale0Attribute(value: ScaleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeScaleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_scale0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scale1Attribute(value: ScaleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeScaleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_scale1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gridSpanAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_gridSpan(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gridOffsetAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_gridOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rotate0Attribute(value: RotateOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRotateOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_rotate0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rotate1Attribute(value: RotateOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRotateOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_rotate1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transform0Attribute(value: TransformationMatrix | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTransformationMatrix(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transform0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transform1Attribute(value: Object | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transform1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAppearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDisAppearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDisAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAttachAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDetachAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDetach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAreaChangeAttribute(value: ((oldValue: Area,newValue: Area) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAreaChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visibilityAttribute(value: Visibility | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Visibility)
            thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_visibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    flexGrowAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_flexGrow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    flexShrinkAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_flexShrink(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    flexBasisAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_flexBasis(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignSelfAttribute(value: ItemAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ItemAlign)
            thisSerializer.writeInt32(TypeChecker.ItemAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_alignSelf(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    displayPriorityAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_displayPriority(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    zIndexAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_zIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    directionAttribute(value: Direction | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Direction)
            thisSerializer.writeInt32(TypeChecker.Direction_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_direction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignAttribute(value: Alignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_align(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    positionAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Position
                thisSerializer.writePosition(value_value_0)
            }
            else if (TypeChecker.isEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Edges
                thisSerializer.writeEdges(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdges
                thisSerializer.writeLocalizedEdges(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_position(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position | LocalizedPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Position
                thisSerializer.writePosition(value_value_0)
            }
            else if (TypeChecker.isLocalizedPosition(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LocalizedPosition
                thisSerializer.writeLocalizedPosition(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_markAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPosition(value_value, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Position
                thisSerializer.writePosition(value_value_0)
            }
            else if (TypeChecker.isEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Edges
                thisSerializer.writeEdges(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdges(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdges
                thisSerializer.writeLocalizedEdges(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_offset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enabledAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_enabled(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useSizeTypeAttribute(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_xs  = value_value.xs
            let value_value_xs_type : int32 = RuntimeType.UNDEFINED
            value_value_xs_type = runtimeType(value_value_xs)
            thisSerializer.writeInt8(value_value_xs_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_xs_type)) {
                const value_value_xs_value  = value_value_xs!
                let value_value_xs_value_type : int32 = RuntimeType.UNDEFINED
                value_value_xs_value_type = runtimeType(value_value_xs_value)
                if (RuntimeType.NUMBER == value_value_xs_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_xs_value_0  = value_value_xs_value as number
                    thisSerializer.writeNumber(value_value_xs_value_0)
                }
                else if (RuntimeType.OBJECT == value_value_xs_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_xs_value_1  = value_value_xs_value as Literal_Number_offset_span
                    const value_value_xs_value_1_span  = value_value_xs_value_1.span
                    thisSerializer.writeNumber(value_value_xs_value_1_span)
                    const value_value_xs_value_1_offset  = value_value_xs_value_1.offset
                    thisSerializer.writeNumber(value_value_xs_value_1_offset)
                }
            }
            const value_value_sm  = value_value.sm
            let value_value_sm_type : int32 = RuntimeType.UNDEFINED
            value_value_sm_type = runtimeType(value_value_sm)
            thisSerializer.writeInt8(value_value_sm_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_sm_type)) {
                const value_value_sm_value  = value_value_sm!
                let value_value_sm_value_type : int32 = RuntimeType.UNDEFINED
                value_value_sm_value_type = runtimeType(value_value_sm_value)
                if (RuntimeType.NUMBER == value_value_sm_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_sm_value_0  = value_value_sm_value as number
                    thisSerializer.writeNumber(value_value_sm_value_0)
                }
                else if (RuntimeType.OBJECT == value_value_sm_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_sm_value_1  = value_value_sm_value as Literal_Number_offset_span
                    const value_value_sm_value_1_span  = value_value_sm_value_1.span
                    thisSerializer.writeNumber(value_value_sm_value_1_span)
                    const value_value_sm_value_1_offset  = value_value_sm_value_1.offset
                    thisSerializer.writeNumber(value_value_sm_value_1_offset)
                }
            }
            const value_value_md  = value_value.md
            let value_value_md_type : int32 = RuntimeType.UNDEFINED
            value_value_md_type = runtimeType(value_value_md)
            thisSerializer.writeInt8(value_value_md_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_md_type)) {
                const value_value_md_value  = value_value_md!
                let value_value_md_value_type : int32 = RuntimeType.UNDEFINED
                value_value_md_value_type = runtimeType(value_value_md_value)
                if (RuntimeType.NUMBER == value_value_md_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_md_value_0  = value_value_md_value as number
                    thisSerializer.writeNumber(value_value_md_value_0)
                }
                else if (RuntimeType.OBJECT == value_value_md_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_md_value_1  = value_value_md_value as Literal_Number_offset_span
                    const value_value_md_value_1_span  = value_value_md_value_1.span
                    thisSerializer.writeNumber(value_value_md_value_1_span)
                    const value_value_md_value_1_offset  = value_value_md_value_1.offset
                    thisSerializer.writeNumber(value_value_md_value_1_offset)
                }
            }
            const value_value_lg  = value_value.lg
            let value_value_lg_type : int32 = RuntimeType.UNDEFINED
            value_value_lg_type = runtimeType(value_value_lg)
            thisSerializer.writeInt8(value_value_lg_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_lg_type)) {
                const value_value_lg_value  = value_value_lg!
                let value_value_lg_value_type : int32 = RuntimeType.UNDEFINED
                value_value_lg_value_type = runtimeType(value_value_lg_value)
                if (RuntimeType.NUMBER == value_value_lg_value_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_lg_value_0  = value_value_lg_value as number
                    thisSerializer.writeNumber(value_value_lg_value_0)
                }
                else if (RuntimeType.OBJECT == value_value_lg_value_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_lg_value_1  = value_value_lg_value as Literal_Number_offset_span
                    const value_value_lg_value_1_span  = value_value_lg_value_1.span
                    thisSerializer.writeNumber(value_value_lg_value_1_span)
                    const value_value_lg_value_1_offset  = value_value_lg_value_1.offset
                    thisSerializer.writeNumber(value_value_lg_value_1_offset)
                }
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_useSizeType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules0Attribute(value: AlignRuleOption | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeAlignRuleOption(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_alignRules0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules1Attribute(value: LocalizedAlignRuleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLocalizedAlignRuleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_alignRules1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aspectRatioAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_aspectRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clickEffect0Attribute(value: ClickEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeClickEffect(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clickEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clickEffect1Attribute(value: ClickEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeClickEffect(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clickEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragStartAttribute(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEnterAttribute(value: ((event: DragEvent,extraParams?: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragMoveAttribute(value: ((event: DragEvent,extraParams?: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragLeaveAttribute(value: ((event: DragEvent,extraParams?: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDrop0Attribute(value: ((event: DragEvent,extraParams?: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDrop0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDrop1Attribute(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let eventCallback_type : int32 = RuntimeType.UNDEFINED
        eventCallback_type = runtimeType(eventCallback)
        thisSerializer.writeInt8(eventCallback_type as int32)
        if ((RuntimeType.UNDEFINED) != (eventCallback_type)) {
            const eventCallback_value  = eventCallback!
            thisSerializer.holdAndWriteCallback(eventCallback_value)
        }
        let dropOptions_type : int32 = RuntimeType.UNDEFINED
        dropOptions_type = runtimeType(dropOptions)
        thisSerializer.writeInt8(dropOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (dropOptions_type)) {
            const dropOptions_value  = dropOptions!
            thisSerializer.writeDropOptions(dropOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onDrop1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEndAttribute(value: ((event: DragEvent,extraParams?: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
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
    draggableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_draggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dragPreview0Attribute(value: CustomBuilder | DragItemInfo | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as DragItemInfo
                thisSerializer.writeDragItemInfo(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreview0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dragPreview1Attribute(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): void {
        const thisSerializer : Serializer = Serializer.hold()
        let preview_type : int32 = RuntimeType.UNDEFINED
        preview_type = runtimeType(preview)
        thisSerializer.writeInt8(preview_type as int32)
        if ((RuntimeType.UNDEFINED) != (preview_type)) {
            const preview_value  = preview!
            let preview_value_type : int32 = RuntimeType.UNDEFINED
            preview_value_type = runtimeType(preview_value)
            if (RuntimeType.FUNCTION == preview_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const preview_value_0  = preview_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(preview_value_0))
            }
            else if (RuntimeType.OBJECT == preview_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const preview_value_1  = preview_value as DragItemInfo
                thisSerializer.writeDragItemInfo(preview_value_1)
            }
            else if (RuntimeType.STRING == preview_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const preview_value_2  = preview_value as string
                thisSerializer.writeString(preview_value_2)
            }
        }
        let config_type : int32 = RuntimeType.UNDEFINED
        config_type = runtimeType(config)
        thisSerializer.writeInt8(config_type as int32)
        if ((RuntimeType.UNDEFINED) != (config_type)) {
            const config_value  = config!
            thisSerializer.writePreviewConfiguration(config_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreview1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreDragAttribute(value: ((parameter: PreDragStatus) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onPreDrag(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradient0Attribute(value: LinearGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLinearGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradient0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradient1Attribute(value: LinearGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLinearGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradient1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sweepGradient0Attribute(value: SweepGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSweepGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sweepGradient0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sweepGradient1Attribute(value: SweepGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSweepGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sweepGradient1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radialGradient0Attribute(value: RadialGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRadialGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_radialGradient0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radialGradient1Attribute(value: RadialGradientOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRadialGradientOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_radialGradient1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    motionPathAttribute(value: MotionPathOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMotionPathOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_motionPath(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shadow0Attribute(value: ShadowOptions | ShadowStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ShadowOptions
                thisSerializer.writeShadowOptions(value_value_0)
            }
            else if (TypeChecker.isShadowStyle(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ShadowStyle
                thisSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_shadow0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shadow1Attribute(value: ShadowOptions | ShadowStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ShadowOptions
                thisSerializer.writeShadowOptions(value_value_0)
            }
            else if (TypeChecker.isShadowStyle(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ShadowStyle
                thisSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_shadow1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    clip2Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clip2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clipShape0Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCircleShape(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as CircleShape
                thisSerializer.writeCircleShape(value_value_0)
            }
            else if (TypeChecker.isEllipseShape(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EllipseShape
                thisSerializer.writeEllipseShape(value_value_1)
            }
            else if (TypeChecker.isPathShape(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as PathShape
                thisSerializer.writePathShape(value_value_2)
            }
            else if (TypeChecker.isRectShape(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as RectShape
                thisSerializer.writeRectShape(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_clipShape0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clipShape1Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCircleShape(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as CircleShape
                thisSerializer.writeCircleShape(value_value_0)
            }
            else if (TypeChecker.isEllipseShape(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EllipseShape
                thisSerializer.writeEllipseShape(value_value_1)
            }
            else if (TypeChecker.isPathShape(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as PathShape
                thisSerializer.writePathShape(value_value_2)
            }
            else if (TypeChecker.isRectShape(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as RectShape
                thisSerializer.writeRectShape(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_clipShape1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    mask2Attribute(value: ProgressMask | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeProgressMask(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mask2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maskShape0Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCircleShape(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as CircleShape
                thisSerializer.writeCircleShape(value_value_0)
            }
            else if (TypeChecker.isEllipseShape(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EllipseShape
                thisSerializer.writeEllipseShape(value_value_1)
            }
            else if (TypeChecker.isPathShape(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as PathShape
                thisSerializer.writePathShape(value_value_2)
            }
            else if (TypeChecker.isRectShape(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as RectShape
                thisSerializer.writeRectShape(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_maskShape0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maskShape1Attribute(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCircleShape(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as CircleShape
                thisSerializer.writeCircleShape(value_value_0)
            }
            else if (TypeChecker.isEllipseShape(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EllipseShape
                thisSerializer.writeEllipseShape(value_value_1)
            }
            else if (TypeChecker.isPathShape(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as PathShape
                thisSerializer.writePathShape(value_value_2)
            }
            else if (TypeChecker.isRectShape(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as RectShape
                thisSerializer.writeRectShape(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_maskShape1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_key(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    idAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_id(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    geometryTransition0Attribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    geometryTransition1Attribute(id: string | undefined, options?: GeometryTransitionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        thisSerializer.writeInt8(id_type as int32)
        if ((RuntimeType.UNDEFINED) != (id_type)) {
            const id_value  = id!
            thisSerializer.writeString(id_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeGeometryTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stateStylesAttribute(value: StateStyles | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeStateStyles(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_stateStyles(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    restoreIdAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_restoreId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sphericalEffect0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sphericalEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sphericalEffect1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sphericalEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lightUpEffect0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_lightUpEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lightUpEffect1Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_lightUpEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pixelStretchEffect0Attribute(value: PixelStretchEffectOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePixelStretchEffectOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_pixelStretchEffect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pixelStretchEffect1Attribute(value: PixelStretchEffectOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePixelStretchEffectOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_pixelStretchEffect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityGroup0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityGroup1Attribute(isGroup: boolean | undefined, accessibilityOptions: AccessibilityOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isGroup_type : int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value  = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        let accessibilityOptions_type : int32 = RuntimeType.UNDEFINED
        accessibilityOptions_type = runtimeType(accessibilityOptions)
        thisSerializer.writeInt8(accessibilityOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (accessibilityOptions_type)) {
            const accessibilityOptions_value  = accessibilityOptions!
            thisSerializer.writeAccessibilityOptions(accessibilityOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityText0Attribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityText1Attribute(value: Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeResource(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityNextFocusIdAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityNextFocusId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityDefaultFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDefaultFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityUseSamePageAttribute(value: AccessibilitySamePageMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AccessibilitySamePageMode)
            thisSerializer.writeInt32(TypeChecker.AccessibilitySamePageMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityUseSamePage(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityScrollTriggerableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityScrollTriggerable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityRoleAttribute(value: AccessibilityRoleType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AccessibilityRoleType)
            thisSerializer.writeInt32(TypeChecker.AccessibilityRoleType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityRole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAccessibilityFocusAttribute(value: AccessibilityFocusCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onAccessibilityFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityTextHintAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityTextHint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityDescription0Attribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityDescription1Attribute(value: Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeResource(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityLevelAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityLevel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityVirtualNodeAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityVirtualNode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityCheckedAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityChecked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilitySelectedAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilitySelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    obscuredAttribute(value: Array<ObscuredReasons> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ObscuredReasons = value_value[i]
                thisSerializer.writeInt32(TypeChecker.ObscuredReasons_ToNumeric(value_value_element))
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_obscured(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reuseIdAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_reuseId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reuseAttribute(value: ReuseOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeReuseOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_reuse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderFit0Attribute(value: RenderFit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as RenderFit)
            thisSerializer.writeInt32(TypeChecker.RenderFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_renderFit0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderFit1Attribute(value: RenderFit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as RenderFit)
            thisSerializer.writeInt32(TypeChecker.RenderFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_renderFit1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gestureModifierAttribute(value: GestureModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGestureModifier(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_gestureModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBrightness0Attribute(value: BackgroundBrightnessOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBackgroundBrightnessOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBrightness0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBrightness1Attribute(value: BackgroundBrightnessOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBackgroundBrightnessOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBrightness1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureJudgeBeginAttribute(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onGestureJudgeBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin0Attribute(value: GestureRecognizerJudgeBeginCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin1Attribute(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        let exposeInnerGesture_type : int32 = RuntimeType.UNDEFINED
        exposeInnerGesture_type = runtimeType(exposeInnerGesture)
        thisSerializer.writeInt8(exposeInnerGesture_type as int32)
        if ((RuntimeType.UNDEFINED) != (exposeInnerGesture_type)) {
            const exposeInnerGesture_value  = exposeInnerGesture!
            thisSerializer.writeBoolean(exposeInnerGesture_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shouldBuiltInRecognizerParallelWithAttribute(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_shouldBuiltInRecognizerParallelWith(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    monopolizeEventsAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_monopolizeEvents(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchInterceptAttribute(value: ((parameter: TouchEvent) => HitTestMode) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onTouchIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSizeChangeAttribute(value: SizeChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onSizeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityFocusDrawLevelAttribute(value: FocusDrawLevel | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FocusDrawLevel)
            thisSerializer.writeInt32(TypeChecker.FocusDrawLevel_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityFocusDrawLevel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customPropertyAttribute(name: string | undefined, value: Object | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let name_type : int32 = RuntimeType.UNDEFINED
        name_type = runtimeType(name)
        thisSerializer.writeInt8(name_type as int32)
        if ((RuntimeType.UNDEFINED) != (name_type)) {
            const name_value  = name!
            thisSerializer.writeString(name_value)
        }
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_customProperty(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    backgroundAttribute(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): void {
        const thisSerializer : Serializer = Serializer.hold()
        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
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
    backgroundImage0Attribute(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        thisSerializer.writeInt8(src_type as int32)
        if ((RuntimeType.UNDEFINED) != (src_type)) {
            const src_value  = src!
            let src_value_type : int32 = RuntimeType.UNDEFINED
            src_value_type = runtimeType(src_value)
            if ((RuntimeType.STRING == src_value_type) || (RuntimeType.OBJECT == src_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const src_value_0  = src_value as ResourceStr
                let src_value_0_type : int32 = RuntimeType.UNDEFINED
                src_value_0_type = runtimeType(src_value_0)
                if (RuntimeType.STRING == src_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const src_value_0_0  = src_value_0 as string
                    thisSerializer.writeString(src_value_0_0)
                }
                else if (RuntimeType.OBJECT == src_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const src_value_0_1  = src_value_0 as Resource
                    thisSerializer.writeResource(src_value_0_1)
                }
            }
            else if (TypeChecker.isPixelMap(src_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const src_value_1  = src_value as PixelMap
                thisSerializer.writePixelMap(src_value_1)
            }
        }
        let repeat_type : int32 = RuntimeType.UNDEFINED
        repeat_type = runtimeType(repeat)
        thisSerializer.writeInt8(repeat_type as int32)
        if ((RuntimeType.UNDEFINED) != (repeat_type)) {
            const repeat_value  = (repeat as ImageRepeat)
            thisSerializer.writeInt32(TypeChecker.ImageRepeat_ToNumeric(repeat_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImage0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImage1Attribute(src: ResourceStr | PixelMap | undefined, options?: BackgroundImageOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        thisSerializer.writeInt8(src_type as int32)
        if ((RuntimeType.UNDEFINED) != (src_type)) {
            const src_value  = src!
            let src_value_type : int32 = RuntimeType.UNDEFINED
            src_value_type = runtimeType(src_value)
            if ((RuntimeType.STRING == src_value_type) || (RuntimeType.OBJECT == src_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const src_value_0  = src_value as ResourceStr
                let src_value_0_type : int32 = RuntimeType.UNDEFINED
                src_value_0_type = runtimeType(src_value_0)
                if (RuntimeType.STRING == src_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const src_value_0_0  = src_value_0 as string
                    thisSerializer.writeString(src_value_0_0)
                }
                else if (RuntimeType.OBJECT == src_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const src_value_0_1  = src_value_0 as Resource
                    thisSerializer.writeResource(src_value_0_1)
                }
            }
            else if (TypeChecker.isPixelMap(src_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const src_value_1  = src_value as PixelMap
                thisSerializer.writePixelMap(src_value_1)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundImageOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImage1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBlurStyle0Attribute(value: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBlurStyle1Attribute(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        let sysOptions_type : int32 = RuntimeType.UNDEFINED
        sysOptions_type = runtimeType(sysOptions)
        thisSerializer.writeInt8(sysOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sysOptions_type)) {
            const sysOptions_value  = sysOptions!
            thisSerializer.writeSystemAdaptiveOptions(sysOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundBlurStyle0Attribute(value: BlurStyle | undefined, options?: ForegroundBlurStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeForegroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundBlurStyle1Attribute(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeForegroundBlurStyleOptions(options_value)
        }
        let sysOptions_type : int32 = RuntimeType.UNDEFINED
        sysOptions_type = runtimeType(sysOptions)
        thisSerializer.writeInt8(sysOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sysOptions_type)) {
            const sysOptions_value  = sysOptions!
            thisSerializer.writeSystemAdaptiveOptions(sysOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId0Attribute(id: string | undefined, isGroup?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        thisSerializer.writeInt8(id_type as int32)
        if ((RuntimeType.UNDEFINED) != (id_type)) {
            const id_value  = id!
            thisSerializer.writeString(id_value)
        }
        let isGroup_type : int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type as int32)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value  = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId1Attribute(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        thisSerializer.writeInt8(id_type as int32)
        if ((RuntimeType.UNDEFINED) != (id_type)) {
            const id_value  = id!
            thisSerializer.writeString(id_value)
        }
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
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopePriorityAttribute(scopeId: string | undefined, priority?: FocusPriority): void {
        const thisSerializer : Serializer = Serializer.hold()
        let scopeId_type : int32 = RuntimeType.UNDEFINED
        scopeId_type = runtimeType(scopeId)
        thisSerializer.writeInt8(scopeId_type as int32)
        if ((RuntimeType.UNDEFINED) != (scopeId_type)) {
            const scopeId_value  = scopeId!
            thisSerializer.writeString(scopeId_value)
        }
        let priority_type : int32 = RuntimeType.UNDEFINED
        priority_type = runtimeType(priority)
        thisSerializer.writeInt8(priority_type as int32)
        if ((RuntimeType.UNDEFINED) != (priority_type)) {
            const priority_value  = (priority as FocusPriority)
            thisSerializer.writeInt32(TypeChecker.FocusPriority_ToNumeric(priority_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopePriority(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blur0Attribute(value: number | undefined, options?: BlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_blur0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blur1Attribute(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let blurRadius_type : int32 = RuntimeType.UNDEFINED
        blurRadius_type = runtimeType(blurRadius)
        thisSerializer.writeInt8(blurRadius_type as int32)
        if ((RuntimeType.UNDEFINED) != (blurRadius_type)) {
            const blurRadius_value  = blurRadius!
            thisSerializer.writeNumber(blurRadius_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        let sysOptions_type : int32 = RuntimeType.UNDEFINED
        sysOptions_type = runtimeType(sysOptions)
        thisSerializer.writeInt8(sysOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sysOptions_type)) {
            const sysOptions_value  = sysOptions!
            thisSerializer.writeSystemAdaptiveOptions(sysOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_blur1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientBlur0Attribute(value: number | undefined, options: LinearGradientBlurOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeLinearGradientBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradientBlur0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientBlur1Attribute(blurRadius: number | undefined, options: LinearGradientBlurOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let blurRadius_type : int32 = RuntimeType.UNDEFINED
        blurRadius_type = runtimeType(blurRadius)
        thisSerializer.writeInt8(blurRadius_type as int32)
        if ((RuntimeType.UNDEFINED) != (blurRadius_type)) {
            const blurRadius_value  = blurRadius!
            thisSerializer.writeNumber(blurRadius_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeLinearGradientBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradientBlur1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarEffectAttribute(): void {
        ArkUIGeneratedNativeModule._CommonMethod_systemBarEffect(this.peer.ptr)
    }
    backdropBlur0Attribute(value: number | undefined, options?: BlurOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backdropBlur0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backdropBlur1Attribute(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let radius_type : int32 = RuntimeType.UNDEFINED
        radius_type = runtimeType(radius)
        thisSerializer.writeInt8(radius_type as int32)
        if ((RuntimeType.UNDEFINED) != (radius_type)) {
            const radius_value  = radius!
            thisSerializer.writeNumber(radius_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        let sysOptions_type : int32 = RuntimeType.UNDEFINED
        sysOptions_type = runtimeType(sysOptions)
        thisSerializer.writeInt8(sysOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sysOptions_type)) {
            const sysOptions_value  = sysOptions!
            thisSerializer.writeSystemAdaptiveOptions(sysOptions_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backdropBlur1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sharedTransitionAttribute(id: string | undefined, options?: sharedTransitionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        thisSerializer.writeInt8(id_type as int32)
        if ((RuntimeType.UNDEFINED) != (id_type)) {
            const id_value  = id!
            thisSerializer.writeString(id_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writesharedTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sharedTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let direction_type : int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value  = (direction as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(direction_value))
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as ChainStyle)
            thisSerializer.writeInt32(TypeChecker.ChainStyle_ToNumeric(style_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_chainMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dragPreviewOptionsAttribute(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDragPreviewOptions(value_value)
        }
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
    overlayAttribute(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as ComponentContent
                thisSerializer.writeComponentContent(value_value_2)
            }
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
    blendMode0Attribute(value: BlendMode | undefined, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlendMode)
            thisSerializer.writeInt32(TypeChecker.BlendMode_ToNumeric(value_value))
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(TypeChecker.BlendApplyType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_blendMode0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blendMode1Attribute(mode: BlendMode | undefined, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let mode_type : int32 = RuntimeType.UNDEFINED
        mode_type = runtimeType(mode)
        thisSerializer.writeInt8(mode_type as int32)
        if ((RuntimeType.UNDEFINED) != (mode_type)) {
            const mode_value  = (mode as BlendMode)
            thisSerializer.writeInt32(TypeChecker.BlendMode_ToNumeric(mode_value))
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(TypeChecker.BlendApplyType_ToNumeric(type_value))
        }
        ArkUIGeneratedNativeModule._CommonMethod_blendMode1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    advancedBlendModeAttribute(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let effect_type : int32 = RuntimeType.UNDEFINED
        effect_type = runtimeType(effect)
        thisSerializer.writeInt8(effect_type as int32)
        if ((RuntimeType.UNDEFINED) != (effect_type)) {
            const effect_value  = effect!
            let effect_value_type : int32 = RuntimeType.UNDEFINED
            effect_value_type = runtimeType(effect_value)
            if (TypeChecker.isBlendMode(effect_value)) {
                thisSerializer.writeInt8(0 as int32)
                const effect_value_0  = effect_value as BlendMode
                thisSerializer.writeInt32(TypeChecker.BlendMode_ToNumeric(effect_value_0))
            }
            else if (RuntimeType.OBJECT == effect_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const effect_value_1  = effect_value as BrightnessBlender
                thisSerializer.writeBrightnessBlender(effect_value_1)
            }
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
    bindTipsAttribute(message: TipsMessageType | undefined, options?: TipsOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let message_type : int32 = RuntimeType.UNDEFINED
        message_type = runtimeType(message)
        thisSerializer.writeInt8(message_type as int32)
        if ((RuntimeType.UNDEFINED) != (message_type)) {
            const message_value  = message!
            let message_value_type : int32 = RuntimeType.UNDEFINED
            message_value_type = runtimeType(message_value)
            if ((RuntimeType.STRING == message_value_type) || (RuntimeType.OBJECT == message_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const message_value_0  = message_value as ResourceStr
                let message_value_0_type : int32 = RuntimeType.UNDEFINED
                message_value_0_type = runtimeType(message_value_0)
                if (RuntimeType.STRING == message_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const message_value_0_0  = message_value_0 as string
                    thisSerializer.writeString(message_value_0_0)
                }
                else if (RuntimeType.OBJECT == message_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const message_value_0_1  = message_value_0 as Resource
                    thisSerializer.writeResource(message_value_0_1)
                }
            }
            else if (TypeChecker.isStyledString(message_value, false)) {
                thisSerializer.writeInt8(1 as int32)
                const message_value_1  = message_value as StyledString
                thisSerializer.writeStyledString(message_value_1)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTipsOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindTips(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindPopupAttribute(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8(show_type as int32)
        if ((RuntimeType.UNDEFINED) != (show_type)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        let popup_type : int32 = RuntimeType.UNDEFINED
        popup_type = runtimeType(popup)
        thisSerializer.writeInt8(popup_type as int32)
        if ((RuntimeType.UNDEFINED) != (popup_type)) {
            const popup_value  = popup!
            let popup_value_type : int32 = RuntimeType.UNDEFINED
            popup_value_type = runtimeType(popup_value)
            if (TypeChecker.isPopupOptions(popup_value, false, false, true, false, false, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true)) {
                thisSerializer.writeInt8(0 as int32)
                const popup_value_0  = popup_value as PopupOptions
                thisSerializer.writePopupOptions(popup_value_0)
            }
            else if (TypeChecker.isCustomPopupOptions(popup_value, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true)) {
                thisSerializer.writeInt8(1 as int32)
                const popup_value_1  = popup_value as CustomPopupOptions
                thisSerializer.writeCustomPopupOptions(popup_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindPopup(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindMenu0Attribute(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const content_value_0  = content_value as Array<MenuElement>
                thisSerializer.writeInt32(content_value_0.length as int32)
                for (let i = 0; i < content_value_0.length; i++) {
                    const content_value_0_element : MenuElement = content_value_0[i]
                    thisSerializer.writeMenuElement(content_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == content_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const content_value_1  = content_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value_1))
            }
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
    bindMenu1Attribute(isShow: boolean | undefined, content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const content_value_0  = content_value as Array<MenuElement>
                thisSerializer.writeInt32(content_value_0.length as int32)
                for (let i = 0; i < content_value_0.length; i++) {
                    const content_value_0_element : MenuElement = content_value_0[i]
                    thisSerializer.writeMenuElement(content_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == content_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const content_value_1  = content_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindMenu1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContextMenu0Attribute(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8(responseType_type as int32)
        if ((RuntimeType.UNDEFINED) != (responseType_type)) {
            const responseType_value  = (responseType as ResponseType)
            thisSerializer.writeInt32(TypeChecker.ResponseType_ToNumeric(responseType_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContextMenu1Attribute(isShown: boolean | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShown_type : int32 = RuntimeType.UNDEFINED
        isShown_type = runtimeType(isShown)
        thisSerializer.writeInt8(isShown_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShown_type)) {
            const isShown_value  = isShown!
            thisSerializer.writeBoolean(isShown_value)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContentCover0Attribute(isShow: boolean | undefined, builder: CustomBuilder | undefined, type?: ModalTransition): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
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
    bindContentCover1Attribute(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
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
    bindSheetAttribute(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let isShow_type : int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type as int32)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value  = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
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
    onVisibleAreaChangeAttribute(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let ratios_type : int32 = RuntimeType.UNDEFINED
        ratios_type = runtimeType(ratios)
        thisSerializer.writeInt8(ratios_type as int32)
        if ((RuntimeType.UNDEFINED) != (ratios_type)) {
            const ratios_value  = ratios!
            thisSerializer.writeInt32(ratios_value.length as int32)
            for (let i = 0; i < ratios_value.length; i++) {
                const ratios_value_element : number = ratios_value[i]
                thisSerializer.writeNumber(ratios_value_element)
            }
        }
        let event_type : int32 = RuntimeType.UNDEFINED
        event_type = runtimeType(event)
        thisSerializer.writeInt8(event_type as int32)
        if ((RuntimeType.UNDEFINED) != (event_type)) {
            const event_value  = event!
            thisSerializer.holdAndWriteCallback(event_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onVisibleAreaChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onVisibleAreaApproximateChangeAttribute(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeVisibleAreaEventOptions(options_value)
        }
        let event_type : int32 = RuntimeType.UNDEFINED
        event_type = runtimeType(event)
        thisSerializer.writeInt8(event_type as int32)
        if ((RuntimeType.UNDEFINED) != (event_type)) {
            const event_value  = event!
            thisSerializer.holdAndWriteCallback(event_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_onVisibleAreaApproximateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardShortcutAttribute(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isFunctionKey(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FunctionKey
                thisSerializer.writeInt32(TypeChecker.FunctionKey_ToNumeric(value_value_1))
            }
        }
        let keys_type : int32 = RuntimeType.UNDEFINED
        keys_type = runtimeType(keys)
        thisSerializer.writeInt8(keys_type as int32)
        if ((RuntimeType.UNDEFINED) != (keys_type)) {
            const keys_value  = keys!
            thisSerializer.writeInt32(keys_value.length as int32)
            for (let i = 0; i < keys_value.length; i++) {
                const keys_value_element : ModifierKey = keys_value[i]
                thisSerializer.writeInt32(TypeChecker.ModifierKey_ToNumeric(keys_value_element))
            }
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCommonPeer {
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCommonShapeMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CommonShapeMethod_construct(peerId, flags)
        const _peer  = new ArkCommonShapeMethodPeer(_peerPtr, peerId, "CommonShapeMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    strokeAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_stroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_fill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineJoinAttribute(value: LineJoinStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineJoinStyle)
            thisSerializer.writeInt32(TypeChecker.LineJoinStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeMiterLimitAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_fillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    antiAliasAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_antiAlias(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashArrayAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Length = value_value[i]
                thisSerializer.writeLength(value_value_element)
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkScrollableCommonMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ScrollableCommonMethod_construct(peerId, flags)
        const _peer  = new ArkScrollableCommonMethodPeer(_peerPtr, peerId, "ScrollableCommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    scrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNestedScrollOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    frictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    flingSpeedLimitAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_flingSpeedLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clipContentAttribute(value: ContentClipMode | RectShape | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isContentClipMode(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ContentClipMode
                thisSerializer.writeInt32(TypeChecker.ContentClipMode_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as RectShape
                thisSerializer.writeRectShape(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_clipContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    digitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_digitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backToTopAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_backToTop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let edgeEffect_type : int32 = RuntimeType.UNDEFINED
        edgeEffect_type = runtimeType(edgeEffect)
        thisSerializer.writeInt8(edgeEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (edgeEffect_type)) {
            const edgeEffect_value  = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(edgeEffect_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type ReuseIdCallback = () => string;
export interface ReuseOptions {
    reuseId?: ReuseIdCallback;
}
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
export enum AccessibilitySamePageMode {
    SEMI_SILENT = 0,
    FULL_SILENT = 1
}
export enum AccessibilityRoleType {
    ACTION_SHEET = 0,
    ALERT_DIALOG = 1,
    INDEXER_COMPONENT = 2,
    BADGE_COMPONENT = 3,
    BLANK = 4,
    BUTTON = 5,
    BACK_BUTTON = 6,
    SHEET_DRAG_BAR = 7,
    CALENDAR_PICKER = 8,
    CALENDAR = 9,
    CANVAS = 10,
    CANVAS_GRADIENT = 11,
    CANVAS_PATTERN = 12,
    CHECKBOX = 13,
    CHECKBOX_GROUP = 14,
    CIRCLE = 15,
    COLUMN_SPLIT = 16,
    COLUMN = 17,
    CANVAS_RENDERING_CONTEXT_2D = 18,
    CHART = 19,
    COUNTER = 20,
    CONTAINER_MODAL = 21,
    DATA_PANEL = 22,
    DATE_PICKER = 23,
    DIALOG = 24,
    DIVIDER = 25,
    DRAG_BAR = 26,
    EFFECT_COMPONENT = 27,
    ELLIPSE = 28,
    FLEX = 29,
    FLOW_ITEM = 30,
    FORM_COMPONENT = 31,
    FORM_LINK = 32,
    GAUGE = 33,
    GRID = 34,
    GRID_COL = 35,
    GRID_CONTAINER = 36,
    GRID_ITEM = 37,
    GRID_ROW = 38,
    HYPERLINK = 39,
    IMAGE = 40,
    IMAGE_ANIMATOR = 41,
    IMAGE_BITMAP = 42,
    IMAGE_DATA = 43,
    IMAGE_SPAN = 44,
    LABEL = 45,
    LINE = 46,
    LIST = 47,
    LIST_ITEM = 48,
    LIST_ITEM_GROUP = 49,
    LOADING_PROGRESS = 50,
    MARQUEE = 51,
    MATRIX2D = 52,
    MENU = 53,
    MENU_ITEM = 54,
    MENU_ITEM_GROUP = 55,
    NAV_DESTINATION = 56,
    NAV_ROUTER = 57,
    NAVIGATION = 58,
    NAVIGATION_BAR = 59,
    NAVIGATION_MENU = 60,
    NAVIGATOR = 61,
    OFFSCREEN_CANVAS = 62,
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    OPTION = 64,
    PANEL = 65,
    PAPER_PAGE = 66,
    PATH = 67,
    PATH2D = 68,
    PATTERN_LOCK = 69,
    PICKER = 70,
    PICKER_VIEW = 71,
    PLUGIN_COMPONENT = 72,
    POLYGON = 73,
    POLYLINE = 74,
    POPUP = 75,
    PROGRESS = 76,
    QRCODE = 77,
    RADIO = 78,
    RATING = 79,
    RECT = 80,
    REFRESH = 81,
    RELATIVE_CONTAINER = 82,
    REMOTE_WINDOW = 83,
    RICH_EDITOR = 84,
    RICH_TEXT = 85,
    ROLE_PAGER = 86,
    ROW = 87,
    ROW_SPLIT = 88,
    SCROLL = 89,
    SCROLL_BAR = 90,
    SEARCH = 91,
    SEARCH_FIELD = 92,
    SELECT = 93,
    SHAPE = 94,
    SIDEBAR_CONTAINER = 95,
    SLIDER = 96,
    SPAN = 97,
    STACK = 98,
    STEPPER = 99,
    STEPPER_ITEM = 100,
    SWIPER = 101,
    SWIPER_INDICATOR = 102,
    SWITCH = 103,
    SYMBOL_GLYPH = 104,
    TAB_CONTENT = 105,
    TAB_BAR = 106,
    TABS = 107,
    TEXT = 108,
    TEXT_CLOCK = 109,
    TEXT_ENTRY = 110,
    TEXT_INPUT = 111,
    TEXT_PICKER = 112,
    TEXT_TIMER = 113,
    TEXT_AREA = 114,
    TEXT_FIELD = 115,
    TIME_PICKER = 116,
    TITLE_BAR = 117,
    TOGGLER = 118,
    UI_EXTENSION_COMPONENT = 119,
    VIDEO = 120,
    WATER_FLOW = 121,
    WEB = 122,
    XCOMPONENT = 123,
    ROLE_NONE = 124
}
export type AccessibilityFocusCallback = (isFocus: boolean) => void;
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
export type Tuple_ResourceColor_Number = [
    ResourceColor,
    number
]
export interface LinearGradientOptions {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export type Tuple_Length_Length = [
    Length,
    Length
]
export interface SweepGradientOptions {
    center: [ Length, Length ];
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export interface RadialGradientOptions {
    center: [ Length, Length ];
    radius: Length;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
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
export interface HorizontalAlignOptions {
    anchor: string;
    align: HorizontalAlign;
}
export interface VerticalAlignOptions {
    anchor: string;
    align: VerticalAlign;
}
export interface AlignRuleOption {
    left?: HorizontalAlignOptions;
    right?: HorizontalAlignOptions;
    middle?: HorizontalAlignOptions;
    top?: VerticalAlignOptions;
    bottom?: VerticalAlignOptions;
    center?: VerticalAlignOptions;
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
    ACTION_CANCELED_BEFORE_DRAG = 6,
    PREPARING_FOR_DRAG_DETECTION = 7
}
export interface DragItemInfo {
    pixelMap?: PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
export interface EventTarget {
    area: Area;
    id?: string;
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
    MOUSE = 7,
    TOUCHPAD = 9,
    JOYSTICK = 10
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
export interface SystemAdaptiveOptions {
    disableSystemAdaptation?: boolean;
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
export interface LayoutPolicy {
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
    hand?: InteractionHand;
    pressedTime?: number;
    pressure?: number;
    width?: number;
    height?: number;
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
export interface DataSyncOptions {
    _DataSyncOptionsStub: string;
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
export type OnDragEventCallback = (event: DragEvent, extraParams?: string) => void;
export interface DropOptions {
    disableDataPrefetch?: boolean;
}
export interface CrownEvent {
    timestamp: int64;
    angularVelocity: number;
    degree: number;
    action: CrownAction;
    stopPropagation: (() => void);
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
export type SingleLengthDetent = [
    SheetSize | Length
]
export type DoubleLengthDetents = [
    SheetSize | Length,
    SheetSize | Length | undefined
]
export type TripleLengthDetents = [
    SheetSize | Length,
    SheetSize | Length | undefined,
    SheetSize | Length | undefined
]
export interface SheetOptions extends BindOptions {
    height?: SheetSize | Length;
    dragBar?: boolean;
    maskColor?: ResourceColor;
    detents?: SingleLengthDetent | DoubleLengthDetents | TripleLengthDetents;
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
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    offset?: Position;
    effectEdge?: number;
    radius?: LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses;
    detentSelection?: SheetSize | Length;
    showInSubWindow?: boolean;
    placement?: Placement;
    placementOnTarget?: boolean;
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
    dismiss: ((data: undefined) => void);
    reason: DismissReason;
}
export interface PopupStateChangeParam {
    isVisible: boolean;
}
export type PopupStateChangeCallback = (event: PopupStateChangeParam) => void;
export interface PopupMaskType {
    color: ResourceColor;
}
export type Callback_DismissPopupAction_Void = (parameter: DismissPopupAction) => void;
export interface PopupCommonOptions {
    placement?: Placement;
    popupColor?: ResourceColor;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | PopupMaskType;
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
export interface TipsOptions {
    appearingTime?: number;
    disappearingTime?: number;
    appearingTimeWithContinuousOperation?: number;
    disappearingTimeWithContinuousOperation?: number;
    enableArrow?: boolean;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
}

export interface PopupButton {
    value: string;
    action: ((data: undefined) => void);
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
export enum BlendMode {
    CLEAR = 0,
    SRC = 1,
    DST = 2,
    SRC_OVER = 3,
    DST_OVER = 4,
    SRC_IN = 5,
    DST_IN = 6,
    SRC_OUT = 7,
    DST_OUT = 8,
    SRC_ATOP = 9,
    DST_ATOP = 10,
    XOR = 11,
    PLUS = 12,
    MODULATE = 13,
    SCREEN = 14,
    OVERLAY = 15,
    DARKEN = 16,
    LIGHTEN = 17,
    COLOR_DODGE = 18,
    COLOR_BURN = 19,
    HARD_LIGHT = 20,
    SOFT_LIGHT = 21,
    DIFFERENCE = 22,
    EXCLUSION = 23,
    MULTIPLY = 24,
    HUE = 25,
    SATURATION = 26,
    COLOR = 27,
    LUMINOSITY = 28
}
export interface PopupOptions {
    message: string;
    placement?: Placement;
    primaryButton?: PopupButton;
    secondaryButton?: PopupButton;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | PopupMaskType;
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
    keyboardAvoidMode?: KeyboardAvoidMode;
}
export interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    popupColor?: Color | string | Resource | number;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: boolean | PopupMaskType;
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
    keyboardAvoidMode?: KeyboardAvoidMode;
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
export type BorderRadiusType = Length | BorderRadiuses | LocalizedBorderRadiuses;
export enum HapticFeedbackMode {
    DISABLED = 0,
    ENABLED = 1,
    AUTO = 2
}
export interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: MenuPreviewMode | CustomBuilder;
    previewBorderRadius?: BorderRadiusType;
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    aboutToAppear?: (() => void);
    aboutToDisappear?: (() => void);
    layoutRegionMargin?: Padding;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
    outlineColor?: ResourceColor | EdgeColors;
    outlineWidth?: Dimension | EdgeOutlineWidths;
    hapticFeedbackMode?: HapticFeedbackMode;
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
    ENABLE_DEFAULT_RADIUS = 4,
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    ENABLE_MULTI_TILE_EFFECT = 6,
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7
}
export enum DraggingSizeChangeEffect {
    DEFAULT = 0,
    SIZE_TRANSITION = 1,
    SIZE_CONTENT_TRANSITION = 2
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
    sizeChangeEffect?: DraggingSizeChangeEffect;
}
export interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
    enableEdgeAutoScroll?: boolean;
    enableHapticFeedback?: boolean;
    isLiftingDisabled?: boolean;
}
export interface PreviewConfiguration {
    onlyForLifting?: boolean;
    delayCreating?: boolean;
}
export interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
export interface DividerStyle {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export type TipsMessageType = ResourceStr | StyledString;
export interface BackgroundImageOptions {
    syncLoad?: boolean;
    repeat?: ImageRepeat;
}
export type Callback_Array_TouchTestInfo_TouchResult = (value: Array<TouchTestInfo>) => TouchResult;
export type Callback_ClickEvent_Void = (event: ClickEvent) => void;
export type Callback_Boolean_HoverEvent_Void = (isHover: boolean, event: HoverEvent) => void;
export type Callback_HoverEvent_Void = (parameter: HoverEvent) => void;
export type Callback_MouseEvent_Void = (event: MouseEvent) => void;
export type Callback_TouchEvent_Void = (event: TouchEvent) => void;
export type Callback_KeyEvent_Void = (event: KeyEvent) => void;
export type Callback_KeyEvent_Boolean = (parameter: KeyEvent) => boolean;
export type Callback_CrownEvent_Void = (parameter: CrownEvent) => void;
export type Callback_FocusAxisEvent_Void = (parameter: FocusAxisEvent) => void;
export type Callback_AxisEvent_Void = (parameter: AxisEvent) => void;
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
export type Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult = (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult;
export type Callback_TouchEvent_HitTestMode = (parameter: TouchEvent) => HitTestMode;
export interface Literal_Alignment_align {
    align?: Alignment;
}
export interface CommonMethod {
    width(value: Length | undefined | Length | LayoutPolicy | undefined): this
    height(value: Length | undefined | Length | LayoutPolicy | undefined): this
    drawModifier(value: DrawModifier | undefined): this
    responseRegion(value: Array<Rectangle> | Rectangle | undefined): this
    mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this
    size(value: SizeOptions | undefined): this
    constraintSize(value: ConstraintSizeOptions | undefined): this
    touchable(value: boolean | undefined): this
    hitTestBehavior(value: HitTestMode | undefined): this
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this
    layoutWeight(value: number | string | undefined): this
    chainWeight(value: ChainWeightOptions | undefined): this
    padding(value: Padding | Length | LocalizedPadding | undefined): this
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this
    margin(value: Padding | Length | LocalizedPadding | undefined): this
    backgroundColor(value: ResourceColor | undefined): this
    pixelRound(value: PixelRoundPolicy | undefined): this
    backgroundImageSize(value: SizeOptions | ImageSize | undefined): this
    backgroundImagePosition(value: Position | Alignment | undefined): this
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this
    backgroundImageResizable(value: ResizableOptions | undefined): this
    foregroundEffect(value: ForegroundEffectOptions | undefined): this
    visualEffect(value: VisualEffect | undefined): this
    backgroundFilter(value: Filter | undefined): this
    foregroundFilter(value: Filter | undefined): this
    compositingFilter(value: Filter | undefined): this
    opacity(value: number | Resource | undefined): this
    border(value: BorderOptions | undefined): this
    borderStyle(value: BorderStyle | EdgeStyles | undefined): this
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this
    borderImage(value: BorderImageOption | undefined): this
    outline(value: OutlineOptions | undefined): this
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this
    outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this
    outlineRadius(value: Dimension | OutlineRadiuses | undefined): this
    foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this
    onClick(event: ((event: ClickEvent) => void) | undefined): this
    onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this
    onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this
    onAccessibilityHover(value: AccessibilityCallback | undefined): this
    hoverEffect(value: HoverEffect | undefined): this
    onMouse(value: ((event: MouseEvent) => void) | undefined): this
    onTouch(value: ((event: TouchEvent) => void) | undefined): this
    onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this
    onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this
    onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this
    onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this
    onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this
    onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this
    focusable(value: boolean | undefined): this
    nextFocus(value: FocusMovement | undefined): this
    tabStop(value: boolean | undefined): this
    onFocus(value: (() => void) | undefined): this
    onBlur(value: (() => void) | undefined): this
    tabIndex(value: number | undefined): this
    defaultFocus(value: boolean | undefined): this
    groupDefaultFocus(value: boolean | undefined): this
    focusOnTouch(value: boolean | undefined): this
    focusBox(value: FocusBoxStyle | undefined): this
    animationStart(value: AnimateParam | undefined): this
    animationStop(value: AnimateParam | undefined):this
    transition(effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined, onFinish?: TransitionFinishCallback): this
    motionBlur(value: MotionBlurOptions | undefined): this
    brightness(value: number | undefined): this
    contrast(value: number | undefined): this
    grayscale(value: number | undefined): this
    colorBlend(value: Color | string | Resource | undefined): this
    saturate(value: number | undefined): this
    sepia(value: number | undefined): this
    invert(value: number | InvertOptions | undefined): this
    hueRotate(value: number | string | undefined): this
    useShadowBatching(value: boolean | undefined): this
    useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this
    renderGroup(value: boolean | undefined): this
    freeze(value: boolean | undefined): this
    translate(value: TranslateOptions | undefined): this
    scale(value: ScaleOptions | undefined): this
    gridSpan(value: number | undefined): this
    gridOffset(value: number | undefined): this
    rotate(value: RotateOptions | undefined): this
    transform(value: TransformationMatrix | undefined | Object | undefined): this
    onAppear(value: (() => void) | undefined): this
    onDisAppear(value: (() => void) | undefined): this
    onAttach(value: (() => void) | undefined): this
    onDetach(value: (() => void) | undefined): this
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this
    visibility(value: Visibility | undefined): this
    flexGrow(value: number | undefined): this
    flexShrink(value: number | undefined): this
    flexBasis(value: number | string | undefined): this
    alignSelf(value: ItemAlign | undefined): this
    displayPriority(value: number | undefined): this
    zIndex(value: number | undefined): this
    direction(value: Direction | undefined): this
    align(value: Alignment | undefined): this
    position(value: Position | Edges | LocalizedEdges | undefined): this
    markAnchor(value: Position | LocalizedPosition | undefined): this
    offset(value: Position | Edges | LocalizedEdges | undefined): this
    enabled(value: boolean | undefined): this
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this
    alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this
    aspectRatio(value: number | undefined): this
    clickEffect(value: ClickEffect | undefined): this
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this
    onDrop(eventCallback: ((event: DragEvent,extraParams?: string) => void) | undefined | OnDragEventCallback | undefined, dropOptions?: DropOptions): this
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this
    allowDrop(value: Array<UniformDataType> | undefined): this
    draggable(value: boolean | undefined): this
    dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this
    onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this
    linearGradient(value: LinearGradientOptions | undefined): this
    sweepGradient(value: SweepGradientOptions | undefined): this
    radialGradient(value: RadialGradientOptions | undefined): this
    motionPath(value: MotionPathOptions | undefined): this
    shadow(value: ShadowOptions | ShadowStyle | undefined): this
    clip(value: boolean | undefined): this
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this
    mask(value: ProgressMask | undefined): this
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this
    key(value: string | undefined): this
    id(value: string | undefined): this
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this
    stateStyles(value: StateStyles | undefined): this
    restoreId(value: number | undefined): this
    sphericalEffect(value: number | undefined): this
    lightUpEffect(value: number | undefined): this
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this
    accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this
    accessibilityText(value: string | undefined | Resource | undefined): this
    accessibilityNextFocusId(value: string | undefined): this
    accessibilityDefaultFocus(value: boolean | undefined): this
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this
    accessibilityScrollTriggerable(value: boolean | undefined): this
    accessibilityRole(value: AccessibilityRoleType | undefined): this
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this
    accessibilityTextHint(value: string | undefined): this
    accessibilityDescription(value: string | undefined | Resource | undefined): this
    accessibilityLevel(value: string | undefined): this
    accessibilityVirtualNode(value: CustomBuilder | undefined): this
    accessibilityChecked(value: boolean | undefined): this
    accessibilitySelected(value: boolean | undefined): this
    obscured(value: Array<ObscuredReasons> | undefined): this
    reuseId(value: string | undefined): this
    reuse(value: ReuseOptions | undefined): this
    renderFit(value: RenderFit | undefined): this
    gestureModifier(value: GestureModifier | undefined): this
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this
    monopolizeEvents(value: boolean | undefined): this
    onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this
    onSizeChange(value: SizeChangeCallback | undefined): this
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this
    customProperty(name: string | undefined, value: Object | undefined): this
    expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this
    background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this
    backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this
    backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this
    foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this
    focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this
    gesture(gesture: GestureType | undefined, mask?: GestureMask): this
    priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this
    parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this
    blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this
    linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this
    systemBarEffect(): this
    backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this
    overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this
    blendMode(value: BlendMode | undefined, type?: BlendApplyType): this
    advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this
    bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this
    bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this
    bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions | undefined): this
    bindContentCover(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, type?: ContentCoverOptions): this
    bindSheet(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, options?: SheetOptions): this
    onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this
    onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this
    keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this
    attributeModifier<T>(value: AttributeModifier<T>): this
}
export class ArkCommonMethodStyle implements CommonMethod {
    width_value?: Length | undefined
    height_value?: Length | undefined
    drawModifier_value?: DrawModifier | undefined
    responseRegion_value?: Array<Rectangle> | Rectangle | undefined
    mouseResponseRegion_value?: Array<Rectangle> | Rectangle | undefined
    size_value?: SizeOptions | undefined
    constraintSize_value?: ConstraintSizeOptions | undefined
    touchable_value?: boolean | undefined
    hitTestBehavior_value?: HitTestMode | undefined
    onChildTouchTest_value?: ((value: Array<TouchTestInfo>) => TouchResult) | undefined
    layoutWeight_value?: number | string | undefined
    chainWeight_value?: ChainWeightOptions | undefined
    padding_value?: Padding | Length | LocalizedPadding | undefined
    safeAreaPadding_value?: Padding | LengthMetrics | LocalizedPadding | undefined
    margin_value?: Padding | Length | LocalizedPadding | undefined
    backgroundColor_value?: ResourceColor | undefined
    pixelRound_value?: PixelRoundPolicy | undefined
    backgroundImageSize_value?: SizeOptions | ImageSize | undefined
    backgroundImagePosition_value?: Position | Alignment | undefined
    backgroundEffect_value?: BackgroundEffectOptions | undefined
    backgroundImageResizable_value?: ResizableOptions | undefined
    foregroundEffect_value?: ForegroundEffectOptions | undefined
    visualEffect_value?: VisualEffect | undefined
    backgroundFilter_value?: Filter | undefined
    foregroundFilter_value?: Filter | undefined
    compositingFilter_value?: Filter | undefined
    opacity_value?: number | Resource | undefined
    border_value?: BorderOptions | undefined
    borderStyle_value?: BorderStyle | EdgeStyles | undefined
    borderWidth_value?: Length | EdgeWidths | LocalizedEdgeWidths | undefined
    borderColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    borderRadius_value?: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined
    borderImage_value?: BorderImageOption | undefined
    outline_value?: OutlineOptions | undefined
    outlineStyle_value?: OutlineStyle | EdgeOutlineStyles | undefined
    outlineWidth_value?: Dimension | EdgeOutlineWidths | undefined
    outlineColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    outlineRadius_value?: Dimension | OutlineRadiuses | undefined
    foregroundColor_value?: ResourceColor | ColoringStrategy | undefined
    onClick_value?: ((event: ClickEvent) => void) | undefined
    onHover_value?: ((isHover: boolean,event: HoverEvent) => void) | undefined
    onHoverMove_value?: ((parameter: HoverEvent) => void) | undefined
    onAccessibilityHover_value?: AccessibilityCallback | undefined
    hoverEffect_value?: HoverEffect | undefined
    onMouse_value?: ((event: MouseEvent) => void) | undefined
    onTouch_value?: ((event: TouchEvent) => void) | undefined
    onKeyEvent_value?: ((event: KeyEvent) => void) | undefined
    onDigitalCrown_value?: ((parameter: CrownEvent) => void) | undefined
    onKeyPreIme_value?: ((parameter: KeyEvent) => boolean) | undefined
    onKeyEventDispatch_value?: ((parameter: KeyEvent) => boolean) | undefined
    onFocusAxisEvent_value?: ((parameter: FocusAxisEvent) => void) | undefined
    onAxisEvent_value?: ((parameter: AxisEvent) => void) | undefined
    focusable_value?: boolean | undefined
    nextFocus_value?: FocusMovement | undefined
    tabStop_value?: boolean | undefined
    onFocus_value?: (() => void) | undefined
    onBlur_value?: (() => void) | undefined
    tabIndex_value?: number | undefined
    defaultFocus_value?: boolean | undefined
    groupDefaultFocus_value?: boolean | undefined
    focusOnTouch_value?: boolean | undefined
    focusBox_value?: FocusBoxStyle | undefined
    animation_value?: AnimateParam | undefined
    transition_value?: TransitionOptions | TransitionEffect | undefined
    motionBlur_value?: MotionBlurOptions | undefined
    brightness_value?: number | undefined
    contrast_value?: number | undefined
    grayscale_value?: number | undefined
    colorBlend_value?: Color | string | Resource | undefined
    saturate_value?: number | undefined
    sepia_value?: number | undefined
    invert_value?: number | InvertOptions | undefined
    hueRotate_value?: number | string | undefined
    useShadowBatching_value?: boolean | undefined
    useEffect_value?: boolean | undefined
    renderGroup_value?: boolean | undefined
    freeze_value?: boolean | undefined
    translate_value?: TranslateOptions | undefined
    scale_value?: ScaleOptions | undefined
    gridSpan_value?: number | undefined
    gridOffset_value?: number | undefined
    rotate_value?: RotateOptions | undefined
    transform_value?: TransformationMatrix | undefined
    onAppear_value?: (() => void) | undefined
    onDisAppear_value?: (() => void) | undefined
    onAttach_value?: (() => void) | undefined
    onDetach_value?: (() => void) | undefined
    onAreaChange_value?: ((oldValue: Area,newValue: Area) => void) | undefined
    visibility_value?: Visibility | undefined
    flexGrow_value?: number | undefined
    flexShrink_value?: number | undefined
    flexBasis_value?: number | string | undefined
    alignSelf_value?: ItemAlign | undefined
    displayPriority_value?: number | undefined
    zIndex_value?: number | undefined
    direction_value?: Direction | undefined
    align_value?: Alignment | undefined
    position_value?: Position | Edges | LocalizedEdges | undefined
    markAnchor_value?: Position | LocalizedPosition | undefined
    offset_value?: Position | Edges | LocalizedEdges | undefined
    enabled_value?: boolean | undefined
    useSizeType_value?: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined
    alignRules_value?: AlignRuleOption | undefined
    aspectRatio_value?: number | undefined
    clickEffect_value?: ClickEffect | undefined
    onDragStart_value?: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    onDragEnter_value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    onDragMove_value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    onDragLeave_value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    onDrop_value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    onDragEnd_value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    allowDrop_value?: Array<UniformDataType> | undefined
    draggable_value?: boolean | undefined
    dragPreview_value?: CustomBuilder | DragItemInfo | string | undefined
    onPreDrag_value?: ((parameter: PreDragStatus) => void) | undefined
    linearGradient_value?: LinearGradientOptions | undefined
    sweepGradient_value?: SweepGradientOptions | undefined
    radialGradient_value?: RadialGradientOptions | undefined
    motionPath_value?: MotionPathOptions | undefined
    shadow_value?: ShadowOptions | ShadowStyle | undefined
    clip_value?: boolean | undefined
    clipShape_value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    mask_value?: ProgressMask | undefined
    maskShape_value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    key_value?: string | undefined
    id_value?: string | undefined
    geometryTransition_value?: string | undefined
    stateStyles_value?: StateStyles | undefined
    restoreId_value?: number | undefined
    sphericalEffect_value?: number | undefined
    lightUpEffect_value?: number | undefined
    pixelStretchEffect_value?: PixelStretchEffectOptions | undefined
    accessibilityGroup_value?: boolean | undefined
    accessibilityText_value?: string | undefined
    accessibilityNextFocusId_value?: string | undefined
    accessibilityDefaultFocus_value?: boolean | undefined
    accessibilityUseSamePage_value?: AccessibilitySamePageMode | undefined
    accessibilityScrollTriggerable_value?: boolean | undefined
    accessibilityRole_value?: AccessibilityRoleType | undefined
    onAccessibilityFocus_value?: AccessibilityFocusCallback | undefined
    accessibilityTextHint_value?: string | undefined
    accessibilityDescription_value?: string | undefined
    accessibilityLevel_value?: string | undefined
    accessibilityVirtualNode_value?: CustomBuilder | undefined
    accessibilityChecked_value?: boolean | undefined
    accessibilitySelected_value?: boolean | undefined
    obscured_value?: Array<ObscuredReasons> | undefined
    reuseId_value?: string | undefined
    reuse_value?: ReuseOptions | undefined
    renderFit_value?: RenderFit | undefined
    gestureModifier_value?: GestureModifier | undefined
    backgroundBrightness_value?: BackgroundBrightnessOptions | undefined
    onGestureJudgeBegin_value?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined
    onGestureRecognizerJudgeBegin_value?: GestureRecognizerJudgeBeginCallback | undefined
    shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback | undefined
    monopolizeEvents_value?: boolean | undefined
    onTouchIntercept_value?: ((parameter: TouchEvent) => HitTestMode) | undefined
    onSizeChange_value?: SizeChangeCallback | undefined
    accessibilityFocusDrawLevel_value?: FocusDrawLevel | undefined
    public width(value: Length | undefined | Length | LayoutPolicy | undefined): this {
        return this
    }
    public height(value: Length | undefined | Length | LayoutPolicy | undefined): this {
        return this
    }
    public drawModifier(value: DrawModifier | undefined): this {
        return this
    }
    public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        return this
    }
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        return this
    }
    public size(value: SizeOptions | undefined): this {
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        return this
    }
    public touchable(value: boolean | undefined): this {
        return this
    }
    public hitTestBehavior(value: HitTestMode | undefined): this {
        return this
    }
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
        return this
    }
    public layoutWeight(value: number | string | undefined): this {
        return this
    }
    public chainWeight(value: ChainWeightOptions | undefined): this {
        return this
    }
    public padding(value: Padding | Length | LocalizedPadding | undefined): this {
        return this
    }
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
        return this
    }
    public margin(value: Padding | Length | LocalizedPadding | undefined): this {
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public pixelRound(value: PixelRoundPolicy | undefined): this {
        return this
    }
    public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
        return this
    }
    public backgroundImagePosition(value: Position | Alignment | undefined): this {
        return this
    }
    public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
        return this
    }
    public backgroundImageResizable(value: ResizableOptions | undefined): this {
        return this
    }
    public foregroundEffect(value: ForegroundEffectOptions | undefined): this {
        return this
    }
    public visualEffect(value: VisualEffect | undefined): this {
        return this
    }
    public backgroundFilter(value: Filter | undefined): this {
        return this
    }
    public foregroundFilter(value: Filter | undefined): this {
        return this
    }
    public compositingFilter(value: Filter | undefined): this {
        return this
    }
    public opacity(value: number | Resource | undefined): this {
        return this
    }
    public border(value: BorderOptions | undefined): this {
        return this
    }
    public borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
        return this
    }
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
        return this
    }
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        return this
    }
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
        return this
    }
    public borderImage(value: BorderImageOption | undefined): this {
        return this
    }
    public outline(value: OutlineOptions | undefined): this {
        return this
    }
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
        return this
    }
    public outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
        return this
    }
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        return this
    }
    public outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
        return this
    }
    public foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
        return this
    }
    public onClick(event: ((event: ClickEvent) => void) | undefined): this {
        return this
    }
    public onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
        return this
    }
    public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
        return this
    }
    public onAccessibilityHover(value: AccessibilityCallback | undefined): this {
        return this
    }
    public hoverEffect(value: HoverEffect | undefined): this {
        return this
    }
    public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
        return this
    }
    public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
        return this
    }
    public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        return this
    }
    public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this {
        return this
    }
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        return this
    }
    public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        return this
    }
    public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
        return this
    }
    public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
        return this
    }
    public focusable(value: boolean | undefined): this {
        return this
    }
    public nextFocus(value: FocusMovement | undefined): this {
        return this
    }
    public tabStop(value: boolean | undefined): this {
        return this
    }
    public onFocus(value: (() => void) | undefined): this {
        return this
    }
    public onBlur(value: (() => void) | undefined): this {
        return this
    }
    public tabIndex(value: number | undefined): this {
        return this
    }
    public defaultFocus(value: boolean | undefined): this {
        return this
    }
    public groupDefaultFocus(value: boolean | undefined): this {
        return this
    }
    public focusOnTouch(value: boolean | undefined): this {
        return this
    }
    public focusBox(value: FocusBoxStyle | undefined): this {
        return this
    }
    public animationStart(value: AnimateParam | undefined): this {
        return this
    }
    public animationStop(value: AnimateParam | undefined): this {
        return this
    }
    public animation(value: AnimateParam | undefined): this {
        return this
    }
    public transition(effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined, onFinish?: TransitionFinishCallback): this {
        return this
    }
    public motionBlur(value: MotionBlurOptions | undefined): this {
        return this
    }
    public brightness(value: number | undefined): this {
        return this
    }
    public contrast(value: number | undefined): this {
        return this
    }
    public grayscale(value: number | undefined): this {
        return this
    }
    public colorBlend(value: Color | string | Resource | undefined): this {
        return this
    }
    public saturate(value: number | undefined): this {
        return this
    }
    public sepia(value: number | undefined): this {
        return this
    }
    public invert(value: number | InvertOptions | undefined): this {
        return this
    }
    public hueRotate(value: number | string | undefined): this {
        return this
    }
    public useShadowBatching(value: boolean | undefined): this {
        return this
    }
    public useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this {
        return this
    }
    public renderGroup(value: boolean | undefined): this {
        return this
    }
    public freeze(value: boolean | undefined): this {
        return this
    }
    public translate(value: TranslateOptions | undefined): this {
        return this
    }
    public scale(value: ScaleOptions | undefined): this {
        return this
    }
    public gridSpan(value: number | undefined): this {
        return this
    }
    public gridOffset(value: number | undefined): this {
        return this
    }
    public rotate(value: RotateOptions | undefined): this {
        return this
    }
    public transform(value: TransformationMatrix | undefined | Object | undefined): this {
        return this
    }
    public onAppear(value: (() => void) | undefined): this {
        return this
    }
    public onDisAppear(value: (() => void) | undefined): this {
        return this
    }
    public onAttach(value: (() => void) | undefined): this {
        return this
    }
    public onDetach(value: (() => void) | undefined): this {
        return this
    }
    public onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
        return this
    }
    public visibility(value: Visibility | undefined): this {
        return this
    }
    public flexGrow(value: number | undefined): this {
        return this
    }
    public flexShrink(value: number | undefined): this {
        return this
    }
    public flexBasis(value: number | string | undefined): this {
        return this
    }
    public alignSelf(value: ItemAlign | undefined): this {
        return this
    }
    public displayPriority(value: number | undefined): this {
        return this
    }
    public zIndex(value: number | undefined): this {
        return this
    }
    public direction(value: Direction | undefined): this {
        return this
    }
    public align(value: Alignment | undefined): this {
        return this
    }
    public position(value: Position | Edges | LocalizedEdges | undefined): this {
        return this
    }
    public markAnchor(value: Position | LocalizedPosition | undefined): this {
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        return this
    }
    public enabled(value: boolean | undefined): this {
        return this
    }
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this {
        return this
    }
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        return this
    }
    public aspectRatio(value: number | undefined): this {
        return this
    }
    public clickEffect(value: ClickEffect | undefined): this {
        return this
    }
    public onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
        return this
    }
    public onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        return this
    }
    public onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        return this
    }
    public onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        return this
    }
    public onDrop(eventCallback: ((event: DragEvent,extraParams?: string) => void) | undefined | OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
        return this
    }
    public onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        return this
    }
    public allowDrop(value: Array<UniformDataType> | undefined): this {
        return this
    }
    public draggable(value: boolean | undefined): this {
        return this
    }
    public dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
        return this
    }
    public onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this {
        return this
    }
    public linearGradient(value: LinearGradientOptions | undefined): this {
        return this
    }
    public sweepGradient(value: SweepGradientOptions | undefined): this {
        return this
    }
    public radialGradient(value: RadialGradientOptions | undefined): this {
        return this
    }
    public motionPath(value: MotionPathOptions | undefined): this {
        return this
    }
    public shadow(value: ShadowOptions | ShadowStyle | undefined): this {
        return this
    }
    public clip(value: boolean | undefined): this {
        return this
    }
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        return this
    }
    public mask(value: ProgressMask | undefined): this {
        return this
    }
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        return this
    }
    public key(value: string | undefined): this {
        return this
    }
    public id(value: string | undefined): this {
        return this
    }
    public geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
        return this
    }
    public stateStyles(value: StateStyles | undefined): this {
        return this
    }
    public restoreId(value: number | undefined): this {
        return this
    }
    public sphericalEffect(value: number | undefined): this {
        return this
    }
    public lightUpEffect(value: number | undefined): this {
        return this
    }
    public pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
        return this
    }
    public accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this {
        return this
    }
    public accessibilityText(value: string | undefined | Resource | undefined): this {
        return this
    }
    public accessibilityNextFocusId(value: string | undefined): this {
        return this
    }
    public accessibilityDefaultFocus(value: boolean | undefined): this {
        return this
    }
    public accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
        return this
    }
    public accessibilityScrollTriggerable(value: boolean | undefined): this {
        return this
    }
    public accessibilityRole(value: AccessibilityRoleType | undefined): this {
        return this
    }
    public onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
        return this
    }
    public accessibilityTextHint(value: string | undefined): this {
        return this
    }
    public accessibilityDescription(value: string | undefined | Resource | undefined): this {
        return this
    }
    public accessibilityLevel(value: string | undefined): this {
        return this
    }
    public accessibilityVirtualNode(value: CustomBuilder | undefined): this {
        return this
    }
    public accessibilityChecked(value: boolean | undefined): this {
        return this
    }
    public accessibilitySelected(value: boolean | undefined): this {
        return this
    }
    public obscured(value: Array<ObscuredReasons> | undefined): this {
        return this
    }
    public reuseId(value: string | undefined): this {
        return this
    }
    public reuse(value: ReuseOptions | undefined): this {
        return this
    }
    public renderFit(value: RenderFit | undefined): this {
        return this
    }
    public gestureModifier(value: GestureModifier | undefined): this {
        return this
    }
    public backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
        return this
    }
    public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
        return this
    }
    public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
        return this
    }
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
        return this
    }
    public monopolizeEvents(value: boolean | undefined): this {
        return this
    }
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this {
        return this
    }
    public onSizeChange(value: SizeChangeCallback | undefined): this {
        return this
    }
    public accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
        return this
    }
    public customProperty(name: string | undefined, value: Object | undefined): this {
        return this
    }
    public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
        return this
    }
    public background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this {
        return this
    }
    public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this {
        return this
    }
    public backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        return this
    }
    public foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        return this
    }
    public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
        return this
    }
    public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
        return this
    }
    public gesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        return this
    }
    public priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        return this
    }
    public parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        return this
    }
    public blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        return this
    }
    public linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
        return this
    }
    public systemBarEffect(): this {
        return this
    }
    public backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        return this
    }
    public sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        return this
    }
    public dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
        return this
    }
    public overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
        return this
    }
    public blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
        return this
    }
    public advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this {
        return this
    }
    public bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
        return this
    }
    public bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
        return this
    }
    public bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this {
        return this
    }
    public bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions | undefined): this {
        return this
    }
    public bindContentCover(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, type?: ModalTransition | ContentCoverOptions): this {
        return this
    }
    public bindSheet(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, options?: SheetOptions): this {
        return this
    }
    public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this {
        return this
    }
    public onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
        return this
    }
    public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
        return this
    }
    public attributeModifier<T>(value: AttributeModifier<T>): this {
        return this
    }
}
export type CommonAttribute = CommonMethod
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
    stroke(value: ResourceColor | undefined): this
    fill(value: ResourceColor | undefined): this
    strokeDashOffset(value: number | string | undefined): this
    strokeLineCap(value: LineCapStyle | undefined): this
    strokeLineJoin(value: LineJoinStyle | undefined): this
    strokeMiterLimit(value: number | string | undefined): this
    strokeOpacity(value: number | string | Resource | undefined): this
    fillOpacity(value: number | string | Resource | undefined): this
    strokeWidth(value: Length | undefined): this
    antiAlias(value: boolean | undefined): this
    strokeDashArray(value: Array<Length> | undefined): this
}
export class ArkCommonShapeMethodStyle extends ArkCommonMethodStyle implements CommonShapeMethod {
    stroke_value?: ResourceColor | undefined
    fill_value?: ResourceColor | undefined
    strokeDashOffset_value?: number | string | undefined
    strokeLineCap_value?: LineCapStyle | undefined
    strokeLineJoin_value?: LineJoinStyle | undefined
    strokeMiterLimit_value?: number | string | undefined
    strokeOpacity_value?: number | string | Resource | undefined
    fillOpacity_value?: number | string | Resource | undefined
    strokeWidth_value?: Length | undefined
    antiAlias_value?: boolean | undefined
    strokeDashArray_value?: Array<Length> | undefined
    public stroke(value: ResourceColor | undefined): this {
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        return this
    }
    public strokeDashOffset(value: number | string | undefined): this {
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        return this
    }
    public strokeMiterLimit(value: number | string | undefined): this {
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        return this
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
export interface PromptActionDialogController {
    _PromptActionDialogControllerStub: string;
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
export interface TextContentControllerOptions {
    offset?: number;
}
export enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2
}
export interface ScrollableCommonMethod extends CommonMethod {
    scrollBar(value: BarState | undefined): this
    scrollBarColor(value: Color | number | string | undefined): this
    scrollBarWidth(value: number | string | undefined): this
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    onScroll(value: ((first: number,last: number) => void) | undefined): this
    onReachStart(value: (() => void) | undefined): this
    onReachEnd(value: (() => void) | undefined): this
    onScrollStart(value: (() => void) | undefined): this
    onScrollStop(value: (() => void) | undefined): this
    flingSpeedLimit(value: number | undefined): this
    clipContent(value: ContentClipMode | RectShape | undefined): this
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this
    backToTop(value: boolean | undefined): this
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this
}
export class ArkScrollableCommonMethodStyle extends ArkCommonMethodStyle implements ScrollableCommonMethod {
    public scrollBar(value: BarState | undefined): this {
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    public friction(value: number | Resource | undefined): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onReachStart(value: (() => void) | undefined): this {
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
        return this
    }
    public onScrollStart(value: (() => void) | undefined): this {
        return this
    }
    public onScrollStop(value: (() => void) | undefined): this {
        return this
    }
    public flingSpeedLimit(value: number | undefined): this {
        return this
    }
    public clipContent(value: ContentClipMode | RectShape | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public backToTop(value: boolean | undefined): this {
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        return this
    }
    public fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        return this
    }
}
export interface ScrollResult {
    offsetRemain: number;
}
export type OnWillScrollCallback = (scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => ScrollResult;
export type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
export type OnMoveHandler = (from: number, to: number) => void;
export interface ItemDragEventHandler {
    onLongPress?: ((index: number) => void);
    onDragStart?: ((index: number) => void);
    onMoveThrough?: OnMoveHandler;
    onDrop?: ((index: number) => void);
}
export interface DynamicNode<T> {
}
export interface EdgeEffectOptions {
    alwaysEnabled: boolean;
    effectEdge?: number;
}
export enum EffectEdge {
    START = 1,
    END = 2
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
    expectedFrameRateRange?: ExpectedFrameRateRange;
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
export class UIGestureEvent {
    private peer?: PeerNode
    setPeer(peer?: PeerNode) {
        this.peer = peer
    }
    addGesture(gesture: GestureHandler, priority?: GesturePriority, mask?: GestureMask): void {
        if (gesture instanceof GestureGroupHandler) {
            let gestureGroup = gesture as GestureGroupHandler;
            gestureGroup.addGestureGroupToNode(priority ?? GesturePriority.NORMAL, this.peer, mask)
        } else if (gesture instanceof GestureHandler) {
            gesture.setGesture(priority ?? GesturePriority.NORMAL, this.peer, mask);
        }
    }
    addParallelGesture(gesture: GestureHandler, mask?: GestureMask): void {
        if (gesture instanceof GestureGroupHandler) {
            let gestureGroup = gesture as GestureGroupHandler;
            gestureGroup.addGestureGroupToNode(2, this.peer, mask)
        } else if (gesture instanceof GestureHandler) {
            gesture.setGesture(2, this.peer, mask);
        }
    }
    removeGestureByTag(tag: string): void {
        if (this.peer) {
            let peerNode = this.peer as PeerNode;
            GestureOps.removeGestureByTag(peerNode.peer.ptr, tag);
        }
    }
    clearGestures(): void {
        if (this.peer) {
            let peerNode = this.peer as PeerNode;
            GestureOps.clearGestures(peerNode.peer.ptr);
        }
    }
}
export interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
export interface FocusMovement {
    forward?: string;
    backward?: string;
    up?: string;
    down?: string;
    left?: string;
    right?: string;
}
export enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1
}
export enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1
}
export interface DateRange {
    start?: Date;
    end?: Date;
}
export class ArkCommonMethodComponent extends ComponentBase implements CommonMethod {

    protected _modifierHost: ArkBaseNode | undefined
    setModifierHost(value: ArkBaseNode): void {
        this._modifierHost = value
    }
    getModifierHost(): ArkBaseNode {
        if (this._modifierHost === undefined || this._modifierHost === null) {
            this._modifierHost = new ArkBaseNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost!
    }
    getAttributeSet(): ArkCommonAttributeSet  {
        return this.getPeer()._attributeSet as ArkCommonAttributeSet;
    }

    initAttributeSet<T>(modifier: AttributeModifier<T>): void {
        let isCommonModifier: boolean = modifier instanceof CommonModifier;
        if (isCommonModifier) {
            let commonModifier = modifier as object as CommonModifier;
            this.getPeer()._attributeSet = commonModifier.attributeSet;
        } else if (this.getPeer()._attributeSet == null) {
            this.getPeer()._attributeSet = new ArkCommonAttributeSet();
        }
    }
    getPeer(): ArkCommonMethodPeer {
        return (this.peer as ArkCommonMethodPeer)
    }
    getOrCreateGestureEvent(): UIGestureEvent {
        if (this.gestureEvent === undefined) {
            let gestureEvent = new UIGestureEvent();
            gestureEvent.setPeer(this.peer);
            this.setGestureEvent(gestureEvent);
        }
        return this.gestureEvent as UIGestureEvent;
    }
    public width(value: Length | undefined | Length | LayoutPolicy | undefined): this {
        if (this.checkPriority("width")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.width0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | LayoutPolicy | undefined)
                this.getPeer()?.width1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public height(value: Length | undefined | Length | LayoutPolicy | undefined): this {
        if (this.checkPriority("height")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.height0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | LayoutPolicy | undefined)
                this.getPeer()?.height1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public drawModifier(value: DrawModifier | undefined): this {
        if (this.checkPriority("drawModifier")) {
            const value_casted = value as (DrawModifier | undefined)
            this.getPeer()?.drawModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (this.checkPriority("responseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle | undefined)
            this.getPeer()?.responseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (this.checkPriority("mouseResponseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle | undefined)
            this.getPeer()?.mouseResponseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    public size(value: SizeOptions | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public touchable(value: boolean | undefined): this {
        if (this.checkPriority("touchable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.touchableAttribute(value_casted)
            return this
        }
        return this
    }
    public hitTestBehavior(value: HitTestMode | undefined): this {
        if (this.checkPriority("hitTestBehavior")) {
            const value_casted = value as (HitTestMode | undefined)
            this.getPeer()?.hitTestBehaviorAttribute(value_casted)
            return this
        }
        return this
    }
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
        if (this.checkPriority("onChildTouchTest")) {
            const value_casted = value as (((value: Array<TouchTestInfo>) => TouchResult) | undefined)
            this.getPeer()?.onChildTouchTestAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutWeight(value: number | string | undefined): this {
        if (this.checkPriority("layoutWeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.layoutWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public chainWeight(value: ChainWeightOptions | undefined): this {
        if (this.checkPriority("chainWeight")) {
            const value_casted = value as (ChainWeightOptions | undefined)
            this.getPeer()?.chainWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public padding(value: Padding | Length | LocalizedPadding | undefined): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Length | LocalizedPadding | undefined)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
        if (this.checkPriority("safeAreaPadding")) {
            const value_casted = value as (Padding | LengthMetrics | LocalizedPadding | undefined)
            this.getPeer()?.safeAreaPaddingAttribute(value_casted)
            return this
        }
        return this
    }
    public margin(value: Padding | Length | LocalizedPadding | undefined): this {
        if (this.checkPriority("margin")) {
            const value_casted = value as (Padding | Length | LocalizedPadding | undefined)
            this.getPeer()?.marginAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.backgroundColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.backgroundColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public pixelRound(value: PixelRoundPolicy | undefined): this {
        if (this.checkPriority("pixelRound")) {
            const value_casted = value as (PixelRoundPolicy | undefined)
            this.getPeer()?.pixelRoundAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
        if (this.checkPriority("backgroundImageSize")) {
            const value_casted = value as (SizeOptions | ImageSize | undefined)
            this.getPeer()?.backgroundImageSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundImagePosition(value: Position | Alignment | undefined): this {
        if (this.checkPriority("backgroundImagePosition")) {
            const value_casted = value as (Position | Alignment | undefined)
            this.getPeer()?.backgroundImagePositionAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
        if (this.checkPriority("backgroundEffect")) {
            const options_type = runtimeType(options)
            const sysOptions_type = runtimeType(sysOptions)
            if ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = options as (BackgroundEffectOptions | undefined)
                this.getPeer()?.backgroundEffect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
                const options_casted = options as (BackgroundEffectOptions | undefined)
                const sysOptions_casted = sysOptions as (SystemAdaptiveOptions)
                this.getPeer()?.backgroundEffect1Attribute(options_casted, sysOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public backgroundImageResizable(value: ResizableOptions | undefined): this {
        if (this.checkPriority("backgroundImageResizable")) {
            const value_casted = value as (ResizableOptions | undefined)
            this.getPeer()?.backgroundImageResizableAttribute(value_casted)
            return this
        }
        return this
    }
    public foregroundEffect(value: ForegroundEffectOptions | undefined): this {
        if (this.checkPriority("foregroundEffect")) {
            const value_casted = value as (ForegroundEffectOptions | undefined)
            this.getPeer()?.foregroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public visualEffect(value: VisualEffect | undefined): this {
        if (this.checkPriority("visualEffect")) {
            const value_casted = value as (VisualEffect | undefined)
            this.getPeer()?.visualEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundFilter(value: Filter | undefined): this {
        if (this.checkPriority("backgroundFilter")) {
            const value_casted = value as (Filter | undefined)
            this.getPeer()?.backgroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public foregroundFilter(value: Filter | undefined): this {
        if (this.checkPriority("foregroundFilter")) {
            const value_casted = value as (Filter | undefined)
            this.getPeer()?.foregroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public compositingFilter(value: Filter | undefined): this {
        if (this.checkPriority("compositingFilter")) {
            const value_casted = value as (Filter | undefined)
            this.getPeer()?.compositingFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public opacity(value: number | Resource | undefined): this {
        if (this.checkPriority("opacity")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Resource | undefined)
                this.getPeer()?.opacity0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Resource | undefined)
                this.getPeer()?.opacity1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public border(value: BorderOptions | undefined): this {
        if (this.checkPriority("border")) {
            const value_casted = value as (BorderOptions | undefined)
            this.getPeer()?.borderAttribute(value_casted)
            return this
        }
        return this
    }
    public borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | EdgeStyles | undefined)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Length | EdgeWidths | LocalizedEdgeWidths | undefined)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors | undefined)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Length | BorderRadiuses | LocalizedBorderRadiuses | undefined)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public borderImage(value: BorderImageOption | undefined): this {
        if (this.checkPriority("borderImage")) {
            const value_casted = value as (BorderImageOption | undefined)
            this.getPeer()?.borderImageAttribute(value_casted)
            return this
        }
        return this
    }
    public outline(value: OutlineOptions | undefined): this {
        if (this.checkPriority("outline")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OutlineOptions | undefined)
                this.getPeer()?.outline0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OutlineOptions | undefined)
                this.getPeer()?.outline1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
        if (this.checkPriority("outlineStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OutlineStyle | EdgeOutlineStyles | undefined)
                this.getPeer()?.outlineStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OutlineStyle | EdgeOutlineStyles | undefined)
                this.getPeer()?.outlineStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
        if (this.checkPriority("outlineWidth")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | EdgeOutlineWidths | undefined)
                this.getPeer()?.outlineWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | EdgeOutlineWidths | undefined)
                this.getPeer()?.outlineWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (this.checkPriority("outlineColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors | undefined)
                this.getPeer()?.outlineColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors | undefined)
                this.getPeer()?.outlineColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
        if (this.checkPriority("outlineRadius")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | OutlineRadiuses | undefined)
                this.getPeer()?.outlineRadius0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | OutlineRadiuses | undefined)
                this.getPeer()?.outlineRadius1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
        if (this.checkPriority("foregroundColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | ColoringStrategy | undefined)
                this.getPeer()?.foregroundColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | ColoringStrategy | undefined)
                this.getPeer()?.foregroundColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onClick(event: ((event: ClickEvent) => void) | undefined): this {
        if (this.checkPriority("onClick")) {
            const event_type = runtimeType(event)
            // const distanceThreshold_type = runtimeType(distanceThreshold)
            if (((RuntimeType.FUNCTION == event_type) || (RuntimeType.UNDEFINED == event_type))) {
                const value_casted = event as (((event: ClickEvent) => void) | undefined)
                this.getPeer()?.onClick0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
        if (this.checkPriority("onHover")) {
            const value_casted = value as (((isHover: boolean,event: HoverEvent) => void) | undefined)
            this.getPeer()?.onHoverAttribute(value_casted)
            return this
        }
        return this
    }
    public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
        if (this.checkPriority("onHoverMove")) {
            const value_casted = value as (((parameter: HoverEvent) => void) | undefined)
            this.getPeer()?.onHoverMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onAccessibilityHover(value: AccessibilityCallback | undefined): this {
        if (this.checkPriority("onAccessibilityHover")) {
            const value_casted = value as (AccessibilityCallback | undefined)
            this.getPeer()?.onAccessibilityHoverAttribute(value_casted)
            return this
        }
        return this
    }
    public hoverEffect(value: HoverEffect | undefined): this {
        if (this.checkPriority("hoverEffect")) {
            const value_casted = value as (HoverEffect | undefined)
            this.getPeer()?.hoverEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
        if (this.checkPriority("onMouse")) {
            const value_casted = value as (((event: MouseEvent) => void) | undefined)
            this.getPeer()?.onMouseAttribute(value_casted)
            return this
        }
        return this
    }
    public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
        if (this.checkPriority("onTouch")) {
            const value_casted = value as (((event: TouchEvent) => void) | undefined)
            this.getPeer()?.onTouchAttribute(value_casted)
            return this
        }
        return this
    }
    public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (this.checkPriority("onKeyEvent")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((parameter: KeyEvent) => boolean) | undefined)
                this.getPeer()?.onKeyEvent1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this {
        if (this.checkPriority("onDigitalCrown")) {
            const value_casted = value as (((parameter: CrownEvent) => void) | undefined)
            this.getPeer()?.onDigitalCrownAttribute(value_casted)
            return this
        }
        return this
    }
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        if (this.checkPriority("onKeyPreIme")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean) | undefined)
            this.getPeer()?.onKeyPreImeAttribute(value_casted)
            return this
        }
        return this
    }
    public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        if (this.checkPriority("onKeyEventDispatch")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean) | undefined)
            this.getPeer()?.onKeyEventDispatchAttribute(value_casted)
            return this
        }
        return this
    }
    public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
        if (this.checkPriority("onFocusAxisEvent")) {
            const value_casted = value as (((parameter: FocusAxisEvent) => void) | undefined)
            this.getPeer()?.onFocusAxisEventAttribute(value_casted)
            return this
        }
        return this
    }
    public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
        if (this.checkPriority("onAxisEvent")) {
            const value_casted = value as (((parameter: AxisEvent) => void) | undefined)
            this.getPeer()?.onAxisEventAttribute(value_casted)
            return this
        }
        return this
    }
    public focusable(value: boolean | undefined): this {
        if (this.checkPriority("focusable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.focusableAttribute(value_casted)
            return this
        }
        return this
    }
    public nextFocus(value: FocusMovement | undefined): this {
        if (this.checkPriority("nextFocus")) {
            const value_casted = value as (FocusMovement | undefined)
            this.getPeer()?.nextFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public tabStop(value: boolean | undefined): this {
        if (this.checkPriority("tabStop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.tabStopAttribute(value_casted)
            return this
        }
        return this
    }
    public onFocus(value: (() => void) | undefined): this {
        if (this.checkPriority("onFocus")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public onBlur(value: (() => void) | undefined): this {
        if (this.checkPriority("onBlur")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onBlurAttribute(value_casted)
            return this
        }
        return this
    }
    public tabIndex(value: number | undefined): this {
        if (this.checkPriority("tabIndex")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.tabIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultFocus(value: boolean | undefined): this {
        if (this.checkPriority("defaultFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.defaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public groupDefaultFocus(value: boolean | undefined): this {
        if (this.checkPriority("groupDefaultFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.groupDefaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public focusOnTouch(value: boolean | undefined): this {
        if (this.checkPriority("focusOnTouch")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.focusOnTouchAttribute(value_casted)
            return this
        }
        return this
    }
    public focusBox(value: FocusBoxStyle | undefined): this {
        if (this.checkPriority("focusBox")) {
            const value_casted = value as (FocusBoxStyle | undefined)
            this.getPeer()?.focusBoxAttribute(value_casted)
            return this
        }
        return this
    }
    public animationStart(value: AnimateParam | undefined): this {
        if (this.checkPriority("animationStart")) {
            const value_casted = value as (AnimateParam | undefined)
            _animationStart(value_casted, this.isFirstBuild);
            return this
        }
        return this
    }
    public animationStop(value: AnimateParam | undefined): this {
        if (this.checkPriority("animationStop")) {
            _animationStop(value, this.isFirstBuild, () => {
                this.isFirstBuild = false
            });
            return this
        }
        return this
    }
    public transition(effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined, onFinish?: TransitionFinishCallback): this {
        if (this.checkPriority("transition")) {
            const effect_type = runtimeType(effect)
            const onFinish_type = runtimeType(onFinish)
            if (((RuntimeType.OBJECT == effect_type) || (RuntimeType.OBJECT == effect_type) || (RuntimeType.UNDEFINED == effect_type)) && (RuntimeType.UNDEFINED == onFinish_type)) {
                const value_casted = effect as (TransitionOptions | TransitionEffect | undefined)
                this.getPeer()?.transition0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.OBJECT == effect_type) || (RuntimeType.UNDEFINED == effect_type)) && ((RuntimeType.FUNCTION == onFinish_type) || (RuntimeType.UNDEFINED == onFinish_type))) {
                const effect_casted = effect as (TransitionEffect | undefined)
                const onFinish_casted = onFinish as (TransitionFinishCallback | undefined)
                this.getPeer()?.transition1Attribute(effect_casted, onFinish_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public motionBlur(value: MotionBlurOptions | undefined): this {
        if (this.checkPriority("motionBlur")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (MotionBlurOptions | undefined)
                this.getPeer()?.motionBlur0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (MotionBlurOptions | undefined)
                this.getPeer()?.motionBlur1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public brightness(value: number | undefined): this {
        if (this.checkPriority("brightness")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.brightness0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.brightness1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public contrast(value: number | undefined): this {
        if (this.checkPriority("contrast")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.contrast0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.contrast1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public grayscale(value: number | undefined): this {
        if (this.checkPriority("grayscale")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.grayscale0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.grayscale1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public colorBlend(value: Color | string | Resource | undefined): this {
        if (this.checkPriority("colorBlend")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Color | string | Resource | undefined)
                this.getPeer()?.colorBlend0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Color | string | Resource | undefined)
                this.getPeer()?.colorBlend1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public saturate(value: number | undefined): this {
        if (this.checkPriority("saturate")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.saturate0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.saturate1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public sepia(value: number | undefined): this {
        if (this.checkPriority("sepia")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.sepia0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.sepia1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public invert(value: number | InvertOptions | undefined): this {
        if (this.checkPriority("invert")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | InvertOptions | undefined)
                this.getPeer()?.invert0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | InvertOptions | undefined)
                this.getPeer()?.invert1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hueRotate(value: number | string | undefined): this {
        if (this.checkPriority("hueRotate")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | string | undefined)
                this.getPeer()?.hueRotate0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | string | undefined)
                this.getPeer()?.hueRotate1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public useShadowBatching(value: boolean | undefined): this {
        if (this.checkPriority("useShadowBatching")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.useShadowBatching0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.useShadowBatching1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this {
        if (this.checkPriority("useEffect")) {
            const useEffect_type = runtimeType(useEffect)
            const effectType_type = runtimeType(effectType)
            if (((RuntimeType.BOOLEAN == useEffect_type) || (RuntimeType.UNDEFINED == useEffect_type)) && (RuntimeType.UNDEFINED == effectType_type)) {
                const value_casted = useEffect as (boolean | undefined)
                this.getPeer()?.useEffect0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == useEffect_type) || (RuntimeType.UNDEFINED == useEffect_type)) && ((RuntimeType.OBJECT == effectType_type) || (RuntimeType.OBJECT == effectType_type))) {
                const useEffect_casted = useEffect as (boolean | undefined)
                const effectType_casted = effectType as (EffectType | undefined)
                this.getPeer()?.useEffect1Attribute(useEffect_casted, effectType_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == useEffect_type) || (RuntimeType.UNDEFINED == useEffect_type)) && ((RuntimeType.OBJECT == effectType_type) || (RuntimeType.OBJECT == effectType_type))) {
                const useEffect_casted = useEffect as (boolean | undefined)
                const effectType_casted = effectType as (EffectType)
                this.getPeer()?.useEffect2Attribute(useEffect_casted, effectType_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public renderGroup(value: boolean | undefined): this {
        if (this.checkPriority("renderGroup")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.renderGroup0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.renderGroup1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public freeze(value: boolean | undefined): this {
        if (this.checkPriority("freeze")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.freeze0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.freeze1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public translate(value: TranslateOptions | undefined): this {
        if (this.checkPriority("translate")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TranslateOptions | undefined)
                this.getPeer()?.translate0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TranslateOptions | undefined)
                this.getPeer()?.translate1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public scale(value: ScaleOptions | undefined): this {
        if (this.checkPriority("scale")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ScaleOptions | undefined)
                this.getPeer()?.scale0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ScaleOptions | undefined)
                this.getPeer()?.scale1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public gridSpan(value: number | undefined): this {
        if (this.checkPriority("gridSpan")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.gridSpanAttribute(value_casted)
            return this
        }
        return this
    }
    public gridOffset(value: number | undefined): this {
        if (this.checkPriority("gridOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.gridOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public rotate(value: RotateOptions | undefined): this {
        if (this.checkPriority("rotate")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (RotateOptions | undefined)
                this.getPeer()?.rotate0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (RotateOptions | undefined)
                this.getPeer()?.rotate1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public transform(value: TransformationMatrix | undefined | Object | undefined): this {
        if (this.checkPriority("transform")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TransformationMatrix | undefined)
                this.getPeer()?.transform0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BIGINT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.MATERIALIZED == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.SYMBOL == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Object | undefined)
                this.getPeer()?.transform1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onAppear(value: (() => void) | undefined): this {
        if (this.checkPriority("onAppear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onAppearAttribute(value_casted)
            return this
        }
        return this
    }
    public onDisAppear(value: (() => void) | undefined): this {
        if (this.checkPriority("onDisAppear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onDisAppearAttribute(value_casted)
            return this
        }
        return this
    }
    public onAttach(value: (() => void) | undefined): this {
        if (this.checkPriority("onAttach")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onAttachAttribute(value_casted)
            return this
        }
        return this
    }
    public onDetach(value: (() => void) | undefined): this {
        if (this.checkPriority("onDetach")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onDetachAttribute(value_casted)
            return this
        }
        return this
    }
    public onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
        if (this.checkPriority("onAreaChange")) {
            const value_casted = value as (((oldValue: Area,newValue: Area) => void) | undefined)
            this.getPeer()?.onAreaChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public visibility(value: Visibility | undefined): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility | undefined)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    public flexGrow(value: number | undefined): this {
        if (this.checkPriority("flexGrow")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.flexGrowAttribute(value_casted)
            return this
        }
        return this
    }
    public flexShrink(value: number | undefined): this {
        if (this.checkPriority("flexShrink")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.flexShrinkAttribute(value_casted)
            return this
        }
        return this
    }
    public flexBasis(value: number | string | undefined): this {
        if (this.checkPriority("flexBasis")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.flexBasisAttribute(value_casted)
            return this
        }
        return this
    }
    public alignSelf(value: ItemAlign | undefined): this {
        if (this.checkPriority("alignSelf")) {
            const value_casted = value as (ItemAlign | undefined)
            this.getPeer()?.alignSelfAttribute(value_casted)
            return this
        }
        return this
    }
    public displayPriority(value: number | undefined): this {
        if (this.checkPriority("displayPriority")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.displayPriorityAttribute(value_casted)
            return this
        }
        return this
    }
    public zIndex(value: number | undefined): this {
        if (this.checkPriority("zIndex")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.zIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public direction(value: Direction | undefined): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Direction | undefined)
            this.getPeer()?.directionAttribute(value_casted)
            return this
        }
        return this
    }
    public align(value: Alignment | undefined): this {
        if (this.checkPriority("align")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.alignAttribute(value_casted)
            return this
        }
        return this
    }
    public position(value: Position | Edges | LocalizedEdges | undefined): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | Edges | LocalizedEdges | undefined)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    public markAnchor(value: Position | LocalizedPosition | undefined): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | LocalizedPosition | undefined)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges | undefined)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    public enabled(value: boolean | undefined): this {
        if (this.checkPriority("enabled")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enabledAttribute(value_casted)
            return this
        }
        return this
    }
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this {
        if (this.checkPriority("useSizeType")) {
            const value_casted = value as (Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined)
            this.getPeer()?.useSizeTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
        if (this.checkPriority("alignRules")) {
            const value_type = runtimeType(value)
            if (((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) && TypeChecker.isAlignRuleOption(value, false, false, false, false, false, false, false)) {
                const value_casted = value as (AlignRuleOption | undefined)
                this.getPeer()?.alignRules0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) && TypeChecker.isLocalizedAlignRuleOptions(value, false, false, false, false, false, false, false)) {
                const value_casted = value as (LocalizedAlignRuleOptions | undefined)
                this.getPeer()?.alignRules1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public aspectRatio(value: number | undefined): this {
        if (this.checkPriority("aspectRatio")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.aspectRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public clickEffect(value: ClickEffect | undefined): this {
        if (this.checkPriority("clickEffect")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ClickEffect | undefined)
                this.getPeer()?.clickEffect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ClickEffect | undefined)
                this.getPeer()?.clickEffect1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
        if (this.checkPriority("onDragStart")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined)
            this.getPeer()?.onDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (this.checkPriority("onDragEnter")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void) | undefined)
            this.getPeer()?.onDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    public onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (this.checkPriority("onDragMove")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void) | undefined)
            this.getPeer()?.onDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (this.checkPriority("onDragLeave")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void) | undefined)
            this.getPeer()?.onDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    public onDrop(eventCallback: ((event: DragEvent,extraParams?: string) => void) | undefined | OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
        if (this.checkPriority("onDrop")) {
            const eventCallback_type = runtimeType(eventCallback)
            const dropOptions_type = runtimeType(dropOptions)
            if ((RuntimeType.FUNCTION == eventCallback_type) || (RuntimeType.UNDEFINED == eventCallback_type)) {
                const value_casted = eventCallback as (((event: DragEvent,extraParams?: string) => void) | undefined)
                this.getPeer()?.onDrop0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == eventCallback_type) || (RuntimeType.UNDEFINED == eventCallback_type)) {
                const eventCallback_casted = eventCallback as (OnDragEventCallback | undefined)
                const dropOptions_casted = dropOptions as (DropOptions)
                this.getPeer()?.onDrop1Attribute(eventCallback_casted, dropOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (this.checkPriority("onDragEnd")) {
            const value_casted = value as (((event: DragEvent,extraParams?: string) => void) | undefined)
            this.getPeer()?.onDragEndAttribute(value_casted)
            return this
        }
        return this
    }
    public allowDrop(value: Array<UniformDataType> | undefined): this {
        if (this.checkPriority("allowDrop")) {
            const value_casted = value as (Array<UniformDataType> | undefined)
            this.getPeer()?.allowDropAttribute(value_casted)
            return this
        }
        return this
    }
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    public dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
        if (this.checkPriority("dragPreview")) {
            const preview_type = runtimeType(preview)
            const config_type = runtimeType(config)
            if ((RuntimeType.FUNCTION == preview_type) || (RuntimeType.OBJECT == preview_type) || (RuntimeType.STRING == preview_type) || (RuntimeType.UNDEFINED == preview_type)) {
                const value_casted = preview as (CustomBuilder | DragItemInfo | string | undefined)
                this.getPeer()?.dragPreview0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == preview_type) || (RuntimeType.OBJECT == preview_type) || (RuntimeType.STRING == preview_type) || (RuntimeType.UNDEFINED == preview_type)) {
                const preview_casted = preview as (CustomBuilder | DragItemInfo | string | undefined)
                const config_casted = config as (PreviewConfiguration)
                this.getPeer()?.dragPreview1Attribute(preview_casted, config_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this {
        if (this.checkPriority("onPreDrag")) {
            const value_casted = value as (((parameter: PreDragStatus) => void) | undefined)
            this.getPeer()?.onPreDragAttribute(value_casted)
            return this
        }
        return this
    }
    public linearGradient(value: LinearGradientOptions | undefined): this {
        if (this.checkPriority("linearGradient")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (LinearGradientOptions | undefined)
                this.getPeer()?.linearGradient0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (LinearGradientOptions | undefined)
                this.getPeer()?.linearGradient1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public sweepGradient(value: SweepGradientOptions | undefined): this {
        if (this.checkPriority("sweepGradient")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (SweepGradientOptions | undefined)
                this.getPeer()?.sweepGradient0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (SweepGradientOptions | undefined)
                this.getPeer()?.sweepGradient1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public radialGradient(value: RadialGradientOptions | undefined): this {
        if (this.checkPriority("radialGradient")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (RadialGradientOptions | undefined)
                this.getPeer()?.radialGradient0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (RadialGradientOptions | undefined)
                this.getPeer()?.radialGradient1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public motionPath(value: MotionPathOptions | undefined): this {
        if (this.checkPriority("motionPath")) {
            const value_casted = value as (MotionPathOptions | undefined)
            this.getPeer()?.motionPathAttribute(value_casted)
            return this
        }
        return this
    }
    public shadow(value: ShadowOptions | ShadowStyle | undefined): this {
        if (this.checkPriority("shadow")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ShadowOptions | ShadowStyle | undefined)
                this.getPeer()?.shadow0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ShadowOptions | ShadowStyle | undefined)
                this.getPeer()?.shadow1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
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
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.clip2Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (this.checkPriority("clipShape")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape | undefined)
                this.getPeer()?.clipShape0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape | undefined)
                this.getPeer()?.clipShape1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
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
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ProgressMask | undefined)
                this.getPeer()?.mask2Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (this.checkPriority("maskShape")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape | undefined)
                this.getPeer()?.maskShape0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape | undefined)
                this.getPeer()?.maskShape1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    public id(value: string | undefined): this {
        if (this.checkPriority("id")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.idAttribute(value_casted)
            return this
        }
        return this
    }
    public geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
        if (this.checkPriority("geometryTransition")) {
            const id_type = runtimeType(id)
            const options_type = runtimeType(options)
            if ((RuntimeType.STRING == id_type) || (RuntimeType.UNDEFINED == id_type)) {
                const value_casted = id as (string | undefined)
                this.getPeer()?.geometryTransition0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == id_type) || (RuntimeType.UNDEFINED == id_type)) {
                const id_casted = id as (string | undefined)
                const options_casted = options as (GeometryTransitionOptions)
                this.getPeer()?.geometryTransition1Attribute(id_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public stateStyles(value: StateStyles | undefined): this {
        if (this.checkPriority("stateStyles")) {
            const value_casted = value as (StateStyles | undefined)
            hookStateStyleImpl(this.getPeer(), value_casted)
            return this
        }
        return this
    }
    public restoreId(value: number | undefined): this {
        if (this.checkPriority("restoreId")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.restoreIdAttribute(value_casted)
            return this
        }
        return this
    }
    public sphericalEffect(value: number | undefined): this {
        if (this.checkPriority("sphericalEffect")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.sphericalEffect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.sphericalEffect1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public lightUpEffect(value: number | undefined): this {
        if (this.checkPriority("lightUpEffect")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.lightUpEffect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.lightUpEffect1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
        if (this.checkPriority("pixelStretchEffect")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PixelStretchEffectOptions | undefined)
                this.getPeer()?.pixelStretchEffect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PixelStretchEffectOptions | undefined)
                this.getPeer()?.pixelStretchEffect1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this {
        if (this.checkPriority("accessibilityGroup")) {
            const isGroup_type = runtimeType(isGroup)
            const accessibilityOptions_type = runtimeType(accessibilityOptions)
            if (((RuntimeType.BOOLEAN == isGroup_type) || (RuntimeType.UNDEFINED == isGroup_type)) && (RuntimeType.UNDEFINED == accessibilityOptions_type)) {
                const value_casted = isGroup as (boolean | undefined)
                this.getPeer()?.accessibilityGroup0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == isGroup_type) || (RuntimeType.UNDEFINED == isGroup_type)) && ((RuntimeType.OBJECT == accessibilityOptions_type) || (RuntimeType.UNDEFINED == accessibilityOptions_type))) {
                const isGroup_casted = isGroup as (boolean | undefined)
                const accessibilityOptions_casted = accessibilityOptions as (AccessibilityOptions | undefined)
                this.getPeer()?.accessibilityGroup1Attribute(isGroup_casted, accessibilityOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public accessibilityText(value: string | undefined | Resource | undefined): this {
        if (this.checkPriority("accessibilityText")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (string | undefined)
                this.getPeer()?.accessibilityText0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Resource | undefined)
                this.getPeer()?.accessibilityText1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public accessibilityNextFocusId(value: string | undefined): this {
        if (this.checkPriority("accessibilityNextFocusId")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.accessibilityNextFocusIdAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityDefaultFocus(value: boolean | undefined): this {
        if (this.checkPriority("accessibilityDefaultFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.accessibilityDefaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
        if (this.checkPriority("accessibilityUseSamePage")) {
            const value_casted = value as (AccessibilitySamePageMode | undefined)
            this.getPeer()?.accessibilityUseSamePageAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityScrollTriggerable(value: boolean | undefined): this {
        if (this.checkPriority("accessibilityScrollTriggerable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.accessibilityScrollTriggerableAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityRole(value: AccessibilityRoleType | undefined): this {
        if (this.checkPriority("accessibilityRole")) {
            const value_casted = value as (AccessibilityRoleType | undefined)
            this.getPeer()?.accessibilityRoleAttribute(value_casted)
            return this
        }
        return this
    }
    public onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
        if (this.checkPriority("onAccessibilityFocus")) {
            const value_casted = value as (AccessibilityFocusCallback | undefined)
            this.getPeer()?.onAccessibilityFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityTextHint(value: string | undefined): this {
        if (this.checkPriority("accessibilityTextHint")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.accessibilityTextHintAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityDescription(value: string | undefined | Resource | undefined): this {
        if (this.checkPriority("accessibilityDescription")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (string | undefined)
                this.getPeer()?.accessibilityDescription0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Resource | undefined)
                this.getPeer()?.accessibilityDescription1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public accessibilityLevel(value: string | undefined): this {
        if (this.checkPriority("accessibilityLevel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.accessibilityLevelAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityVirtualNode(value: CustomBuilder | undefined): this {
        if (this.checkPriority("accessibilityVirtualNode")) {
            const value_casted = value as (CustomBuilder | undefined)
            this.getPeer()?.accessibilityVirtualNodeAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityChecked(value: boolean | undefined): this {
        if (this.checkPriority("accessibilityChecked")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.accessibilityCheckedAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilitySelected(value: boolean | undefined): this {
        if (this.checkPriority("accessibilitySelected")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.accessibilitySelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public obscured(value: Array<ObscuredReasons> | undefined): this {
        if (this.checkPriority("obscured")) {
            const value_casted = value as (Array<ObscuredReasons> | undefined)
            this.getPeer()?.obscuredAttribute(value_casted)
            return this
        }
        return this
    }
    public reuseId(value: string | undefined): this {
        if (this.checkPriority("reuseId")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.reuseIdAttribute(value_casted)
            return this
        }
        return this
    }
    public reuse(value: ReuseOptions | undefined): this {
        if (this.checkPriority("reuse")) {
            const value_casted = value as (ReuseOptions | undefined)
            this.getPeer()?.reuseAttribute(value_casted)
            return this
        }
        return this
    }
    public renderFit(value: RenderFit | undefined): this {
        if (this.checkPriority("renderFit")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type)) {
                const value_casted = value as (RenderFit | undefined)
                this.getPeer()?.renderFit0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type)) {
                const value_casted = value as (RenderFit | undefined)
                this.getPeer()?.renderFit1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public gestureModifier(value: GestureModifier | undefined): this {
        if (this.checkPriority("gestureModifier")) {
            if (value === undefined) {
                return this;
            }
            const value_casted = value as GestureModifier
            let gestureEvent = this.getOrCreateGestureEvent();
            gestureEvent.clearGestures();
            value_casted.applyGesture(gestureEvent);
            return this
        }
        return this
    }
    public backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
        if (this.checkPriority("backgroundBrightness")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (BackgroundBrightnessOptions | undefined)
                this.getPeer()?.backgroundBrightness0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (BackgroundBrightnessOptions | undefined)
                this.getPeer()?.backgroundBrightness1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
        if (this.checkPriority("onGestureJudgeBegin")) {
            const value_casted = value as (((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined)
            this.getPeer()?.onGestureJudgeBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
        if (this.checkPriority("onGestureRecognizerJudgeBegin")) {
            const callback__type = runtimeType(callback_)
            const exposeInnerGesture_type = runtimeType(exposeInnerGesture)
            if (((RuntimeType.FUNCTION == callback__type) || (RuntimeType.UNDEFINED == callback__type)) && (RuntimeType.UNDEFINED == exposeInnerGesture_type)) {
                const value_casted = callback_ as (GestureRecognizerJudgeBeginCallback | undefined)
                this.getPeer()?.onGestureRecognizerJudgeBegin0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.FUNCTION == callback__type) || (RuntimeType.UNDEFINED == callback__type)) && ((RuntimeType.BOOLEAN == exposeInnerGesture_type) || (RuntimeType.UNDEFINED == exposeInnerGesture_type))) {
                const callback__casted = callback_ as (GestureRecognizerJudgeBeginCallback | undefined)
                const exposeInnerGesture_casted = exposeInnerGesture as (boolean | undefined)
                this.getPeer()?.onGestureRecognizerJudgeBegin1Attribute(callback__casted, exposeInnerGesture_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
        if (this.checkPriority("shouldBuiltInRecognizerParallelWith")) {
            const value_casted = value as (ShouldBuiltInRecognizerParallelWithCallback | undefined)
            this.getPeer()?.shouldBuiltInRecognizerParallelWithAttribute(value_casted)
            return this
        }
        return this
    }
    public monopolizeEvents(value: boolean | undefined): this {
        if (this.checkPriority("monopolizeEvents")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.monopolizeEventsAttribute(value_casted)
            return this
        }
        return this
    }
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this {
        if (this.checkPriority("onTouchIntercept")) {
            const value_casted = value as (((parameter: TouchEvent) => HitTestMode) | undefined)
            this.getPeer()?.onTouchInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    public onSizeChange(value: SizeChangeCallback | undefined): this {
        if (this.checkPriority("onSizeChange")) {
            const value_casted = value as (SizeChangeCallback | undefined)
            this.getPeer()?.onSizeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
        if (this.checkPriority("accessibilityFocusDrawLevel")) {
            const value_casted = value as (FocusDrawLevel | undefined)
            this.getPeer()?.accessibilityFocusDrawLevelAttribute(value_casted)
            return this
        }
        return this
    }
    public customProperty(name: string | undefined, value: Object | undefined): this {
        if (this.checkPriority("customProperty")) {
            const name_casted = name as (string | undefined)
            const value_casted = value as (Object | undefined)
            this.getPeer()?.customPropertyAttribute(name_casted, value_casted)
            return this
        }
        return this
    }
    public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
        if (this.checkPriority("expandSafeArea")) {
            const types_casted = types as (Array<SafeAreaType> | undefined)
            const edges_casted = edges as (Array<SafeAreaEdge> | undefined)
            this.getPeer()?.expandSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    public background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this {
        if (this.checkPriority("background")) {
            const builder_casted = builder as (CustomBuilder | undefined)
            const options_casted = options as (Literal_Alignment_align)
            this.getPeer()?.backgroundAttribute(builder_casted, options_casted)
            return this
        }
        return this
    }
    public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this {
        if (this.checkPriority("backgroundImage")) {
            const src_type = runtimeType(src)
            const repeat_type = runtimeType(repeat)
            if (((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.UNDEFINED == src_type)) && ((RuntimeType.NUMBER == repeat_type) || (RuntimeType.OBJECT == repeat_type))) {
                const src_casted = src as (ResourceStr | PixelMap | undefined)
                const repeat_casted = repeat as (ImageRepeat)
                this.getPeer()?.backgroundImage0Attribute(src_casted, repeat_casted)
                return this
            }
        }
        return this
    }
    public backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (this.checkPriority("backgroundBlurStyle")) {
            const style_type = runtimeType(style)
            const options_type = runtimeType(options)
            const sysOptions_type = runtimeType(sysOptions)
            if (((RuntimeType.NUMBER == style_type) || (RuntimeType.UNDEFINED == style_type))) {
                const value_casted = style as (BlurStyle | undefined)
                const options_casted = options as (BackgroundBlurStyleOptions | undefined)
                this.getPeer()?.backgroundBlurStyle0Attribute(value_casted, options_casted)
                return this
            }
            if ((RuntimeType.OBJECT == style_type) || (RuntimeType.OBJECT == style_type)) {
                const style_casted = style as (BlurStyle | undefined)
                const options_casted = options as (BackgroundBlurStyleOptions)
                const sysOptions_casted = sysOptions as (SystemAdaptiveOptions)
                this.getPeer()?.backgroundBlurStyle1Attribute(style_casted, options_casted, sysOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (this.checkPriority("foregroundBlurStyle")) {
            const style_type = runtimeType(style)
            const options_type = runtimeType(options)
            const sysOptions_type = runtimeType(sysOptions)
            if (((RuntimeType.NUMBER == style_type) || (RuntimeType.UNDEFINED == style_type))) {
                const value_casted = style as (BlurStyle | undefined)
                const options_casted = options as (ForegroundBlurStyleOptions | undefined)
                this.getPeer()?.foregroundBlurStyle0Attribute(value_casted, options_casted)
                return this
            }
            if ((RuntimeType.OBJECT == style_type) || (RuntimeType.OBJECT == style_type)) {
                const style_casted = style as (BlurStyle | undefined)
                const options_casted = options as (ForegroundBlurStyleOptions)
                const sysOptions_casted = sysOptions as (SystemAdaptiveOptions)
                this.getPeer()?.foregroundBlurStyle1Attribute(style_casted, options_casted, sysOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
        if (this.checkPriority("focusScopeId")) {
            const id_type = runtimeType(id)
            const isGroup_type = runtimeType(isGroup)
            const arrowStepOut_type = runtimeType(arrowStepOut)
            if ((RuntimeType.STRING == id_type) || (RuntimeType.UNDEFINED == id_type)) {
                const id_casted = id as (string | undefined)
                const isGroup_casted = isGroup as (boolean)
                const arrowStepOut_casted = arrowStepOut as (boolean)
                this.getPeer()?.focusScopeId1Attribute(id_casted, isGroup_casted, arrowStepOut_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
        if (this.checkPriority("focusScopePriority")) {
            const scopeId_casted = scopeId as (string | undefined)
            const priority_casted = priority as (FocusPriority)
            this.getPeer()?.focusScopePriorityAttribute(scopeId_casted, priority_casted)
            return this
        }
        return this
    }
    public gesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        if (this.checkPriority("gesture")) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.setGesture(0, this.getPeer(), mask);
                return this;
            } else {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureGroupToNode(0, this.getPeer(), mask)
            }
            return this
        }
        return this
    }
    public priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        if (this.checkPriority("priorityGesture")) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.setGesture(1, this.getPeer(), mask);
                return this;
            } else {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureGroupToNode(1, this.getPeer(), mask)
            }
            return this
        }
        return this
    }
    public parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        if (this.checkPriority("parallelGesture")) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.setGesture(2, this.getPeer(), mask);
                return this;
            } else {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureGroupToNode(2, this.getPeer(), mask)
            }
            return this
        }
        return this
    }
    public blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (this.checkPriority("blur")) {
            const blurRadius_type = runtimeType(blurRadius)
            const options_type = runtimeType(options)
            const sysOptions_type = runtimeType(sysOptions)
            if ((RuntimeType.NUMBER == blurRadius_type) || (RuntimeType.UNDEFINED == blurRadius_type)) {
                const value_casted = blurRadius as (number | undefined)
                const options_casted = options as (BlurOptions | undefined)
                this.getPeer()?.blur0Attribute(value_casted, options_casted)
                return this
            }
            if ((RuntimeType.NUMBER == blurRadius_type) || (RuntimeType.UNDEFINED == blurRadius_type)) {
                const blurRadius_casted = blurRadius as (number | undefined)
                const options_casted = options as (BlurOptions | undefined)
                const sysOptions_casted = sysOptions as (SystemAdaptiveOptions)
                this.getPeer()?.blur1Attribute(blurRadius_casted, options_casted, sysOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
        if (this.checkPriority("linearGradientBlur")) {
            const value_type = runtimeType(value)
            const options_type = runtimeType(options)
            if (((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const value_casted = value as (number | undefined)
                const options_casted = options as (LinearGradientBlurOptions | undefined)
                this.getPeer()?.linearGradientBlur0Attribute(value_casted, options_casted)
                return this
            }
            if (((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const blurRadius_casted = value as (number | undefined)
                const options_casted = options as (LinearGradientBlurOptions | undefined)
                this.getPeer()?.linearGradientBlur1Attribute(blurRadius_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public systemBarEffect(): this {
        if (this.checkPriority("systemBarEffect")) {
            this.getPeer()?.systemBarEffectAttribute()
            return this
        }
        return this
    }
    public backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (this.checkPriority("backdropBlur")) {
            const radius_type = runtimeType(radius)
            const options_type = runtimeType(options)
            const sysOptions_type = runtimeType(sysOptions)
            if ((RuntimeType.NUMBER == radius_type) || (RuntimeType.UNDEFINED == radius_type)) {
                const value_casted = radius as (number | undefined)
                const options_casted = options as (BlurOptions| undefined)
                this.getPeer()?.backdropBlur0Attribute(value_casted, options_casted)
                return this
            }
            if ((RuntimeType.NUMBER == radius_type) || (RuntimeType.UNDEFINED == radius_type)) {
                const radius_casted = radius as (number | undefined)
                const options_casted = options as (BlurOptions)
                const sysOptions_casted = sysOptions as (SystemAdaptiveOptions)
                this.getPeer()?.backdropBlur1Attribute(radius_casted, options_casted, sysOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
        if (this.checkPriority("sharedTransition")) {
            const id_casted = id as (string | undefined)
            const options_casted = options as (sharedTransitionOptions)
            this.getPeer()?.sharedTransitionAttribute(id_casted, options_casted)
            return this
        }
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis | undefined)
            const style_casted = style as (ChainStyle | undefined)
            this.getPeer()?.chainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    public dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
        if (this.checkPriority("dragPreviewOptions")) {
            const value_casted = value as (DragPreviewOptions | undefined)
            const options_casted = options as (DragInteractionOptions)
            this.getPeer()?.dragPreviewOptionsAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
        if (this.checkPriority("overlay")) {
            const value_casted = value as (string | CustomBuilder | ComponentContent | undefined)
            const options_casted = options as (OverlayOptions)
            this.getPeer()?.overlayAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
        if (this.checkPriority("blendMode")) {
            const value_type = runtimeType(value)
            const type_type = runtimeType(type)
            if (((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.OBJECT == type_type))) {
                const value_casted = value as (BlendMode | undefined)
                const type_casted = type as (BlendApplyType)
                this.getPeer()?.blendMode0Attribute(value_casted, type_casted)
                return this
            }
            if (((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.OBJECT == type_type))) {
                const mode_casted = value as (BlendMode | undefined)
                const type_casted = type as (BlendApplyType)
                this.getPeer()?.blendMode1Attribute(mode_casted, type_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this {
        if (this.checkPriority("advancedBlendMode")) {
            const effect_casted = effect as (BlendMode | BrightnessBlender | undefined)
            const type_casted = type as (BlendApplyType)
            this.getPeer()?.advancedBlendModeAttribute(effect_casted, type_casted)
            return this
        }
        return this
    }
    public bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
        if (this.checkPriority("bindTips")) {
            const message_casted = message as (TipsMessageType | undefined)
            const options_casted = options as (TipsOptions)
            this.getPeer()?.bindTipsAttribute(message_casted, options_casted)
            return this
        }
        return this
    }
    public bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
        if (this.checkPriority("bindPopup")) {
            const show_casted = show as (boolean | undefined)
            const popup_casted = popup as (PopupOptions | CustomPopupOptions | undefined)
            this.getPeer()?.bindPopupAttribute(show_casted, popup_casted)
            return this
        }
        return this
    }
    public bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this {
        if (this.checkPriority("bindMenu")) {
            const content_type = runtimeType(content)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == content_type) || (RuntimeType.FUNCTION == content_type)) || ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const content_casted = content as (Array<MenuElement> | CustomBuilder | undefined)
                const options_casted = options as (MenuOptions | undefined)
                this.getPeer()?.bindMenu0Attribute(content_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions | undefined): this {
        if (this.checkPriority("bindContextMenu")) {
            const content_type = runtimeType(content)
            const responseType_type = runtimeType(responseType)
            const options_type = runtimeType(options)
            if ((RuntimeType.FUNCTION == content_type) && (TypeChecker.isResponseType(responseType)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const content_casted = content as (CustomBuilder | undefined)
                const responseType_casted = responseType as (ResponseType | undefined)
                const options_casted = options as (ContextMenuOptions | undefined)
                this.getPeer()?.bindContextMenu0Attribute(content_casted, responseType_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public bindContentCover(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, type?: ContentCoverOptions): this {
        if (this.checkPriority("bindContentCover")) {
            const isShow_type = runtimeType(isShow)
            const builder_type = runtimeType(builder)
            const type_type = runtimeType(type)
            if (((RuntimeType.BOOLEAN == isShow_type) || (RuntimeType.UNDEFINED == isShow_type)) && ((RuntimeType.FUNCTION == builder_type) || (RuntimeType.UNDEFINED == builder_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.UNDEFINED == type_type))) {
                const isShow_casted = isShow as (boolean | undefined)
                const builder_casted = builder as (CustomBuilder | undefined)
                const options_casted = type as (ContentCoverOptions)
                this.getPeer()?.bindContentCover1Attribute(isShow_casted, builder_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public bindSheet(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, options?: SheetOptions): this {
        if (this.checkPriority("bindSheet")) {
            const isShow_casted = isShow as (boolean | undefined)
            const builder_casted = builder as (CustomBuilder | undefined)
            const options_casted = options as (SheetOptions)
            this.getPeer()?.bindSheetAttribute(isShow_casted, builder_casted, options_casted)
            return this
        }
        return this
    }
    public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (this.checkPriority("onVisibleAreaChange")) {
            const ratios_casted = ratios as (Array<number> | undefined)
            const event_casted = event as (VisibleAreaChangeCallback | undefined)
            this.getPeer()?.onVisibleAreaChangeAttribute(ratios_casted, event_casted)
            return this
        }
        return this
    }
    public onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (this.checkPriority("onVisibleAreaApproximateChange")) {
            const options_casted = options as (VisibleAreaEventOptions | undefined)
            const event_casted = event as (VisibleAreaChangeCallback | undefined)
            this.getPeer()?.onVisibleAreaApproximateChangeAttribute(options_casted, event_casted)
            return this
        }
        return this
    }
    public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
        if (this.checkPriority("keyboardShortcut")) {
            const value_casted = value as (string | FunctionKey | undefined)
            const keys_casted = keys as (Array<ModifierKey> | undefined)
            const action_casted = action as ((() => void))
            this.getPeer()?.keyboardShortcutAttribute(value_casted, keys_casted, action_casted)
            return this
        }
        return this
    }
    public attributeModifier<T>(modifier: AttributeModifier<T>): this {

        let peerNode = this.getPeer()
        this.initAttributeSet(modifier);
        let isAttributeUpdater: boolean = (modifier instanceof AttributeUpdater);
        if (isAttributeUpdater) {
            let attributeUpdater = modifier as object as AttributeUpdater<T, (...params: Object[]) => T>
            if (!attributeUpdater.peerNode_) {
                attributeUpdater.initializeModifier(peerNode._attributeSet as T);
            } else if (this.getPeer() !== attributeUpdater.peerNode_) {
                attributeUpdater.onComponentChanged(peerNode._attributeSet as T);
            }
            attributeUpdater.peerNode_ = this.getPeer();
            attributeUpdater.attribute = this.getModifierHost() as T
            attributeUpdater.updateConstructorParams = (...params: Object[]) => {
                let attribute = this.getModifierHost()! as T;
                this.getModifierHost()!.constructParam(...params);
                return attribute;
            };
        }
        this.applyModifierByState(isAttributeUpdater, modifier);
        return this;
    }
    public applyModifierByState<T>(isAttributeUpdater: boolean, modifier: AttributeModifier<T>): void {
    }

    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkCommonShapeMethodComponent extends ArkCommonMethodComponent implements CommonShapeMethod {
    getPeer(): ArkCommonShapeMethodPeer {
        return (this.peer as ArkCommonShapeMethodPeer)
    }
    public stroke(value: ResourceColor | undefined): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.strokeAttribute(value_casted)
            return this
        }
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fillAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashOffset(value: number | string | undefined): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.strokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle | undefined)
            this.getPeer()?.strokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle | undefined)
            this.getPeer()?.strokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeMiterLimit(value: number | string | undefined): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.strokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.strokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.fillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.antiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.strokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkScrollableCommonMethodComponent extends ArkCommonMethodComponent implements ScrollableCommonMethod {
    getPeer(): ArkScrollableCommonMethodPeer {
        return (this.peer as ArkScrollableCommonMethodPeer)
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string | undefined)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: number | Resource | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: (() => void) | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public flingSpeedLimit(value: number | undefined): this {
        if (this.checkPriority("flingSpeedLimit")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.flingSpeedLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (this.checkPriority("clipContent")) {
            const value_casted = value as (ContentClipMode | RectShape | undefined)
            this.getPeer()?.clipContentAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.digitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public backToTop(value: boolean | undefined): this {
        if (this.checkPriority("backToTop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.backToTopAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    public fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (this.checkPriority("fadingEdge")) {
            const enabled_casted = enabled as (boolean | undefined)
            const options_casted = options as (FadingEdgeOptions)
            this.getPeer()?.fadingEdgeAttribute(enabled_casted, options_casted)
            return this
        }
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
export interface ClickEvent {
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    screenX: number
    screenY: number
    x: number
    y: number
    hand?: InteractionHand | undefined
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
    get hand(): InteractionHand | undefined {
        return this.getHand()
    }
    set hand(hand: InteractionHand | undefined) {
        const hand_NonNull  = (hand as InteractionHand)
        this.setHand(hand_NonNull)
    }
    get preventDefault(): (() => void) {
        return this.getPreventDefault();
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
    private getHand(): InteractionHand | undefined {
        return this.getHand_serialize()
    }
    private setHand(hand: InteractionHand): void {
        const hand_casted = hand as (InteractionHand)
        this.setHand_serialize(hand_casted)
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
    private getHand_serialize(): InteractionHand | undefined {
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getHand(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setHand_serialize(hand: InteractionHand): void {
        ArkUIGeneratedNativeModule._ClickEvent_setHand(this.peer!.ptr, TypeChecker.InteractionHand_ToNumeric(hand))
    }
    private getPreventDefault_serialize(): (() => void) {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._ClickEvent_getPreventDefault(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult = retvalDeserializer.readCallback_Void(true);
        return returnResult;
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
    x?: number | undefined
    y?: number | undefined
    windowX?: number | undefined
    windowY?: number | undefined
    displayX?: number | undefined
    displayY?: number | undefined
    stopPropagation: (() => void)
}
export class HoverEventInternal extends BaseEventInternal implements MaterializedBase,HoverEvent {
    get x(): number | undefined {
        return this.getX()
    }
    set x(x: number | undefined) {
        const x_NonNull  = (x as number)
        this.setX(x_NonNull)
    }
    get y(): number | undefined {
        return this.getY()
    }
    set y(y: number | undefined) {
        const y_NonNull  = (y as number)
        this.setY(y_NonNull)
    }
    get windowX(): number | undefined {
        return this.getWindowX()
    }
    set windowX(windowX: number | undefined) {
        const windowX_NonNull  = (windowX as number)
        this.setWindowX(windowX_NonNull)
    }
    get windowY(): number | undefined {
        return this.getWindowY()
    }
    set windowY(windowY: number | undefined) {
        const windowY_NonNull  = (windowY as number)
        this.setWindowY(windowY_NonNull)
    }
    get displayX(): number | undefined {
        return this.getDisplayX()
    }
    set displayX(displayX: number | undefined) {
        const displayX_NonNull  = (displayX as number)
        this.setDisplayX(displayX_NonNull)
    }
    get displayY(): number | undefined {
        return this.getDisplayY()
    }
    set displayY(displayY: number | undefined) {
        const displayY_NonNull  = (displayY as number)
        this.setDisplayY(displayY_NonNull)
    }
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
    private getX(): number | undefined {
        return this.getX_serialize()
    }
    private setX(x: number): void {
        const x_casted = x as (number)
        this.setX_serialize(x_casted)
        return
    }
    private getY(): number | undefined {
        return this.getY_serialize()
    }
    private setY(y: number): void {
        const y_casted = y as (number)
        this.setY_serialize(y_casted)
        return
    }
    private getWindowX(): number | undefined {
        return this.getWindowX_serialize()
    }
    private setWindowX(windowX: number): void {
        const windowX_casted = windowX as (number)
        this.setWindowX_serialize(windowX_casted)
        return
    }
    private getWindowY(): number | undefined {
        return this.getWindowY_serialize()
    }
    private setWindowY(windowY: number): void {
        const windowY_casted = windowY as (number)
        this.setWindowY_serialize(windowY_casted)
        return
    }
    private getDisplayX(): number | undefined {
        return this.getDisplayX_serialize()
    }
    private setDisplayX(displayX: number): void {
        const displayX_casted = displayX as (number)
        this.setDisplayX_serialize(displayX_casted)
        return
    }
    private getDisplayY(): number | undefined {
        return this.getDisplayY_serialize()
    }
    private setDisplayY(displayY: number): void {
        const displayY_casted = displayY as (number)
        this.setDisplayY_serialize(displayY_casted)
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
    private getX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getX(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getY(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setY(this.peer!.ptr, y)
    }
    private getWindowX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getWindowX(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getWindowY(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getDisplayX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getDisplayX(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._HoverEvent_getDisplayY(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._HoverEvent_setDisplayY(this.peer!.ptr, displayY)
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
    rawDeltaX?: number | undefined
    rawDeltaY?: number | undefined
    pressedButtons?: Array<MouseButton> | undefined
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
    get rawDeltaX(): number | undefined {
        return this.getRawDeltaX()
    }
    set rawDeltaX(rawDeltaX: number | undefined) {
        const rawDeltaX_NonNull  = (rawDeltaX as number)
        this.setRawDeltaX(rawDeltaX_NonNull)
    }
    get rawDeltaY(): number | undefined {
        return this.getRawDeltaY()
    }
    set rawDeltaY(rawDeltaY: number | undefined) {
        const rawDeltaY_NonNull  = (rawDeltaY as number)
        this.setRawDeltaY(rawDeltaY_NonNull)
    }
    get pressedButtons(): Array<MouseButton> | undefined {
        throw new Error("Not implemented")
    }
    set pressedButtons(pressedButtons: Array<MouseButton> | undefined) {
        const pressedButtons_NonNull  = (pressedButtons as Array<MouseButton>)
        this.setPressedButtons(pressedButtons_NonNull)
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
    private getRawDeltaX(): number | undefined {
        return this.getRawDeltaX_serialize()
    }
    private setRawDeltaX(rawDeltaX: number): void {
        const rawDeltaX_casted = rawDeltaX as (number)
        this.setRawDeltaX_serialize(rawDeltaX_casted)
        return
    }
    private getRawDeltaY(): number | undefined {
        return this.getRawDeltaY_serialize()
    }
    private setRawDeltaY(rawDeltaY: number): void {
        const rawDeltaY_casted = rawDeltaY as (number)
        this.setRawDeltaY_serialize(rawDeltaY_casted)
        return
    }
    private getPressedButtons(): Array<MouseButton> | undefined {
        return this.getPressedButtons_serialize()
    }
    private setPressedButtons(pressedButtons: Array<MouseButton>): void {
        const pressedButtons_casted = pressedButtons as (Array<MouseButton>)
        this.setPressedButtons_serialize(pressedButtons_casted)
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
    private getRawDeltaX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getRawDeltaX(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setRawDeltaX_serialize(rawDeltaX: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setRawDeltaX(this.peer!.ptr, rawDeltaX)
    }
    private getRawDeltaY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getRawDeltaY(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setRawDeltaY_serialize(rawDeltaY: number): void {
        ArkUIGeneratedNativeModule._MouseEvent_setRawDeltaY(this.peer!.ptr, rawDeltaY)
    }
    private getPressedButtons_serialize(): Array<MouseButton> | undefined {
        const retval  = ArkUIGeneratedNativeModule._MouseEvent_getPressedButtons(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setPressedButtons_serialize(pressedButtons: Array<MouseButton>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(pressedButtons.length as int32)
        for (let i = 0; i < pressedButtons.length; i++) {
            const pressedButtons_element : MouseButton = pressedButtons[i]
            thisSerializer.writeInt32(TypeChecker.MouseButton_ToNumeric(pressedButtons_element))
        }
        ArkUIGeneratedNativeModule._MouseEvent_setPressedButtons(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface TouchEvent extends BaseEvent {
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
        return this.getTouches();
    }
    set touches(touches: Array<TouchObject>) {
        this.setTouches(touches)
    }
    get changedTouches(): Array<TouchObject> {
        return this.getChangedTouches()
    }
    set changedTouches(changedTouches: Array<TouchObject>) {
        this.setChangedTouches(changedTouches)
    }
    get stopPropagation(): (() => void) {
        return this.getStopPropagation();
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getHistoricalPoints(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getTouches(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getChangedTouches(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._TouchEvent_getStopPropagation(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        
        let returnResult = retvalDeserializer.readCallback_Void(true);
        return returnResult;
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
export interface AxisEvent extends BaseEvent {
    action: AxisAction
    displayX: number
    displayY: number
    windowX: number
    windowY: number
    x: number
    y: number
    scrollStep?: number | undefined
    propagation: (() => void)
    getHorizontalAxisValue(): number
    getVerticalAxisValue(): number
}
export class AxisEventInternal extends BaseEventInternal implements MaterializedBase,AxisEvent {
    get action(): AxisAction {
        return this.getAction()
    }
    set action(action: AxisAction) {
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
    get scrollStep(): number | undefined {
        return this.getScrollStep()
    }
    set scrollStep(scrollStep: number | undefined) {
        const scrollStep_NonNull  = (scrollStep as number)
        this.setScrollStep(scrollStep_NonNull)
    }
    get propagation(): (() => void) {
        return this.getPropagation()
    }
    set propagation(propagation: (() => void)) {
        this.setPropagation(propagation)
    }
    static ctor_axisevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = AxisEventInternal.ctor_axisevent()
        this.peer = new Finalizable(ctorPtr, AxisEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AxisEvent_getFinalizer()
    }
    public getHorizontalAxisValue(): number {
        return this.getHorizontalAxisValue_serialize()
    }
    public getVerticalAxisValue(): number {
        return this.getVerticalAxisValue_serialize()
    }
    private getAction(): AxisAction {
        return this.getAction_serialize()
    }
    private setAction(action: AxisAction): void {
        const action_casted = action as (AxisAction)
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
    private getScrollStep(): number | undefined {
        return this.getScrollStep_serialize()
    }
    private setScrollStep(scrollStep: number): void {
        const scrollStep_casted = scrollStep as (number)
        this.setScrollStep_serialize(scrollStep_casted)
        return
    }
    private getPropagation(): (() => void) {
        return this.getPropagation_serialize()
    }
    private setPropagation(propagation: (() => void)): void {
        const propagation_casted = propagation as ((() => void))
        this.setPropagation_serialize(propagation_casted)
        return
    }
    private getHorizontalAxisValue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getHorizontalAxisValue(this.peer!.ptr)
        return retval
    }
    private getVerticalAxisValue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getVerticalAxisValue(this.peer!.ptr)
        return retval
    }
    private getAction_serialize(): AxisAction {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getAction(this.peer!.ptr)
        return TypeChecker.AxisAction_FromNumeric(retval)
    }
    private setAction_serialize(action: AxisAction): void {
        ArkUIGeneratedNativeModule._AxisEvent_setAction(this.peer!.ptr, TypeChecker.AxisAction_ToNumeric(action))
    }
    private getDisplayX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getDisplayX(this.peer!.ptr)
        return retval
    }
    private setDisplayX_serialize(displayX: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setDisplayX(this.peer!.ptr, displayX)
    }
    private getDisplayY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getDisplayY(this.peer!.ptr)
        return retval
    }
    private setDisplayY_serialize(displayY: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setDisplayY(this.peer!.ptr, displayY)
    }
    private getWindowX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getWindowX(this.peer!.ptr)
        return retval
    }
    private setWindowX_serialize(windowX: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setWindowX(this.peer!.ptr, windowX)
    }
    private getWindowY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getWindowY(this.peer!.ptr)
        return retval
    }
    private setWindowY_serialize(windowY: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setWindowY(this.peer!.ptr, windowY)
    }
    private getX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getX(this.peer!.ptr)
        return retval
    }
    private setX_serialize(x: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setX(this.peer!.ptr, x)
    }
    private getY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getY(this.peer!.ptr)
        return retval
    }
    private setY_serialize(y: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setY(this.peer!.ptr, y)
    }
    private getScrollStep_serialize(): number | undefined {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getScrollStep(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        let returnResult : number | undefined
        const returnResult_runtimeType = (retvalDeserializer.readInt8() as int32)
        if ((RuntimeType.UNDEFINED) != (returnResult_runtimeType))
        {
            returnResult = (retvalDeserializer.readNumber() as number)
        }
        return returnResult
    }
    private setScrollStep_serialize(scrollStep: number): void {
        ArkUIGeneratedNativeModule._AxisEvent_setScrollStep(this.peer!.ptr, scrollStep)
    }
    private getPropagation_serialize(): (() => void) {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._AxisEvent_getPropagation(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        
        let returnResult = retvalDeserializer.readCallback_Void(true);
        return returnResult;
    }
    private setPropagation_serialize(propagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(propagation)
        ArkUIGeneratedNativeModule._AxisEvent_setPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): AxisEventInternal {
        const obj : AxisEventInternal = new AxisEventInternal()
        obj.peer = new Finalizable(ptr, AxisEventInternal.getFinalizer())
        return obj
    }
}
export interface FocusAxisEvent {
    axisMap: Map<AxisModel, number>
    stopPropagation: (() => void)
}
export class FocusAxisEventInternal extends BaseEventInternal implements MaterializedBase,FocusAxisEvent {
    get axisMap(): Map<AxisModel, number> {
        throw new Error("Not implemented")
    }
    set axisMap(axisMap: Map<AxisModel, number>) {
        this.setAxisMap(axisMap)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    static ctor_focusaxisevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FocusAxisEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = FocusAxisEventInternal.ctor_focusaxisevent()
        this.peer = new Finalizable(ctorPtr, FocusAxisEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FocusAxisEvent_getFinalizer()
    }
    private getAxisMap(): Map<AxisModel, number> {
        return this.getAxisMap_serialize()
    }
    private setAxisMap(axisMap: Map<AxisModel, number>): void {
        const axisMap_casted = axisMap as (Map<AxisModel, number>)
        this.setAxisMap_serialize(axisMap_casted)
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
    private getAxisMap_serialize(): Map<AxisModel, number> {
        const retval  = ArkUIGeneratedNativeModule._FocusAxisEvent_getAxisMap(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_size : int32 = retvalDeserializer.readInt32()
        let buffer : Map<AxisModel, number> = new Map<AxisModel, number>()
        // TODO: TS map resize
        for (let buffer_i = 0; buffer_i < buffer_size; buffer_i++) {
            const buffer_key : AxisModel = TypeChecker.AxisModel_FromNumeric(retvalDeserializer.readInt32())
            const buffer_value : number = (retvalDeserializer.readNumber() as number)
            buffer.set(buffer_key, buffer_value)
        }
        const returnResult : Map<AxisModel, number> = buffer
        return returnResult
    }
    private setAxisMap_serialize(axisMap: Map<AxisModel, number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(axisMap.size as int32 as int32)
        for (const pair of axisMap) {
            const axisMap_key = pair[0]
            const axisMap_value = pair[1]
            thisSerializer.writeInt32(TypeChecker.AxisModel_ToNumeric(axisMap_key))
            thisSerializer.writeNumber(axisMap_value)
        }
        ArkUIGeneratedNativeModule._FocusAxisEvent_setAxisMap(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._FocusAxisEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._FocusAxisEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): FocusAxisEventInternal {
        const obj : FocusAxisEventInternal = new FocusAxisEventInternal()
        obj.peer = new Finalizable(ptr, FocusAxisEventInternal.getFinalizer())
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

export interface AttributeModifier<T> {
    applyNormalAttribute(instance: T) : void;
    applyPressedAttribute(instance: T) : void;
    applyFocusedAttribute(instance: T) : void;
    applyDisabledAttribute(instance: T) : void;
    applySelectedAttribute(instance: T) : void;
}

export interface Type_CommonMethod_linearGradient_value {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
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
export interface Bindable<T> {
    readonly value: T;
    readonly onChange: (value: T) => void;
}
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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { SourceTool, BaseEvent, BaseEventInternal } from "./common"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { InteractionHand } from "./enums"
export class EventTargetInfoInternal {
    public static fromPtr(ptr: KPointer): EventTargetInfo {
        return new EventTargetInfo(ptr)
    }
}
export class EventTargetInfo implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, EventTargetInfo.getFinalizer())
    }
    constructor() {
        this(EventTargetInfo.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._EventTargetInfo_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._EventTargetInfo_getFinalizer()
    }
    public getId(): string {
        return this.getId_serialize()
    }
    private getId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._EventTargetInfo_getId(this.peer!.ptr)
        return retval
    }
}
export class GestureInternal {
    public static fromPtr(ptr: KPointer): Gesture {
        return new Gesture(ptr)
    }
}
export class Gesture implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Gesture.getFinalizer())
    }
    constructor() {
        this(Gesture.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Gesture_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Gesture_getFinalizer()
    }
    public tag(tag: string): this {
        const tag_casted = tag as (string)
        this.tag_serialize(tag_casted)
        return this
    }
    public allowedTypes(types: Array<SourceTool>): this {
        const types_casted = types as (Array<SourceTool>)
        this.allowedTypes_serialize(types_casted)
        return this
    }
    private tag_serialize(tag: string): this {
        ArkUIGeneratedNativeModule._Gesture_tag(this.peer!.ptr, tag)
        return this
    }
    private allowedTypes_serialize(types: Array<SourceTool>): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((types.length).toInt())
        for (let types_counter_i = 0; types_counter_i < types.length; types_counter_i++) {
            const types_element : SourceTool = types[types_counter_i]
            thisSerializer.writeInt32(TypeChecker.SourceTool_ToNumeric(types_element))
        }
        ArkUIGeneratedNativeModule._Gesture_allowedTypes(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
}
export class GestureRecognizerInternal {
    public static fromPtr(ptr: KPointer): GestureRecognizer {
        return new GestureRecognizer(ptr)
    }
}
export class GestureRecognizer implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, GestureRecognizer.getFinalizer())
    }
    constructor() {
        this(GestureRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureRecognizer_getFinalizer()
    }
    public getTag(): string {
        return this.getTag_serialize()
    }
    public getType(): GestureControl.GestureType {
        return this.getType_serialize()
    }
    public isBuiltIn(): boolean {
        return this.isBuiltIn_serialize()
    }
    public setEnabled(isEnabled: boolean): void {
        const isEnabled_casted = isEnabled as (boolean)
        this.setEnabled_serialize(isEnabled_casted)
        return
    }
    public isEnabled(): boolean {
        return this.isEnabled_serialize()
    }
    public getState(): GestureRecognizerState {
        return this.getState_serialize()
    }
    public getEventTargetInfo(): EventTargetInfo {
        return this.getEventTargetInfo_serialize()
    }
    public isValid(): boolean {
        return this.isValid_serialize()
    }
    public getFingerCount(): number {
        return this.getFingerCount_serialize()
    }
    public isFingerCountLimit(): boolean {
        return this.isFingerCountLimit_serialize()
    }
    private getTag_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getTag(this.peer!.ptr)
        return retval
    }
    private getType_serialize(): GestureControl.GestureType {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(this.peer!.ptr)
        return TypeChecker.GestureControl_GestureType_FromNumeric(retval)
    }
    private isBuiltIn_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isBuiltIn(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(isEnabled: boolean): void {
        ArkUIGeneratedNativeModule._GestureRecognizer_setEnabled(this.peer!.ptr, isEnabled ? 1 : 0)
    }
    private isEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isEnabled(this.peer!.ptr)
        return retval
    }
    private getState_serialize(): GestureRecognizerState {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getState(this.peer!.ptr)
        return TypeChecker.GestureRecognizerState_FromNumeric(retval)
    }
    private getEventTargetInfo_serialize(): EventTargetInfo {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getEventTargetInfo(this.peer!.ptr)
        const obj : EventTargetInfo = EventTargetInfoInternal.fromPtr(retval)
        return obj
    }
    private isValid_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isValid(this.peer!.ptr)
        return retval
    }
    private getFingerCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getFingerCount(this.peer!.ptr)
        return retval
    }
    private isFingerCountLimit_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isFingerCountLimit(this.peer!.ptr)
        return retval
    }
}
export class PanGestureOptionsInternal {
    public static fromPtr(ptr: KPointer): PanGestureOptions {
        return new PanGestureOptions(false, ptr)
    }
}
export class PanGestureOptions implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PanGestureOptions.getFinalizer())
    }
    constructor(value?: PanGestureHandlerOptions) {
        this(false, PanGestureOptions.construct(value))
    }
    static construct(value?: PanGestureHandlerOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PanGestureHandlerOptions_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureOptions_getFinalizer()
    }
    public setDirection(value: PanDirection): void {
        const value_casted = value as (PanDirection)
        this.setDirection_serialize(value_casted)
        return
    }
    public setDistance(value: number): void {
        const value_casted = value as (number)
        this.setDistance_serialize(value_casted)
        return
    }
    public setFingers(value: number): void {
        const value_casted = value as (number)
        this.setFingers_serialize(value_casted)
        return
    }
    public getDirection(): PanDirection {
        return this.getDirection_serialize()
    }
    public getDistance(): number {
        return this.getDistance_serialize()
    }
    private setDirection_serialize(value: PanDirection): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDirection(this.peer!.ptr, TypeChecker.PanDirection_ToNumeric(value))
    }
    private setDistance_serialize(value: number): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDistance(this.peer!.ptr, value)
    }
    private setFingers_serialize(value: number): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setFingers(this.peer!.ptr, value)
    }
    private getDirection_serialize(): PanDirection {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDirection(this.peer!.ptr)
        return TypeChecker.PanDirection_FromNumeric(retval)
    }
    private getDistance_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDistance(this.peer!.ptr)
        return retval
    }
}
export enum PanDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    LEFT = 2,
    Left = 2,
    RIGHT = 3,
    Right = 3,
    VERTICAL = 4,
    Vertical = 4,
    UP = 5,
    Up = 5,
    DOWN = 6,
    Down = 6,
    ALL = 7,
    All = 7
}
export enum SwipeDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    VERTICAL = 2,
    Vertical = 2,
    ALL = 3,
    All = 3
}
export enum GestureMode {
    SEQUENCE = 0,
    Sequence = 0,
    PARALLEL = 1,
    Parallel = 1,
    EXCLUSIVE = 2,
    Exclusive = 2
}
export enum GestureMask {
    NORMAL = 0,
    Normal = 0,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = 1
}
export enum GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1
}
export interface GestureInfo {
    tag?: string;
    type: GestureControl.GestureType;
    isSystemGesture: boolean;
}
export interface FingerInfo {
    id: number;
    globalX: number;
    globalY: number;
    localX: number;
    localY: number;
    displayX: number;
    displayY: number;
    hand?: InteractionHand;
}
export type GestureType = Gesture | object;
export interface BaseHandlerOptions {
    isFingerCountLimited?: boolean;
}
export interface TapGestureParameters extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
export interface GestureHandler {
}
export interface TapGestureHandlerOptions extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
}
export interface TapGestureHandler extends GestureHandler {
}
export interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface LongPressGestureHandler extends GestureHandler {
}
export interface PanGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface PanGestureHandler extends GestureHandler {
}
export interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export interface SwipeGestureHandler extends GestureHandler {
}
export interface PinchGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    distance?: number;
}
export interface PinchGestureHandler extends GestureHandler {
}
export interface RotationGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    angle?: number;
}
export interface RotationGestureHandler extends GestureHandler {
}
export interface GestureGroupGestureHandlerOptions {
    _stub: int32;
}
export enum GesturePriority {
    NORMAL = 0,
    PRIORITY = 1
}
export enum GestureRecognizerState {
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5
}
export class EventTargetInfo_serializer {
    public static write(buffer: SerializerBase, value: EventTargetInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): EventTargetInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return EventTargetInfoInternal.fromPtr(ptr)
    }
}
export class Gesture_serializer {
    public static write(buffer: SerializerBase, value: Gesture): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Gesture {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return GestureInternal.fromPtr(ptr)
    }
}
export class GestureRecognizer_serializer {
    public static write(buffer: SerializerBase, value: GestureRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): GestureRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return GestureRecognizerInternal.fromPtr(ptr)
    }
}
export class LongPressRecognizer_serializer {
    public static write(buffer: SerializerBase, value: LongPressRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LongPressRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LongPressRecognizerInternal.fromPtr(ptr)
    }
}
export class PanGestureOptions_serializer {
    public static write(buffer: SerializerBase, value: PanGestureOptions): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PanGestureOptions {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PanGestureOptionsInternal.fromPtr(ptr)
    }
}
export class PanRecognizer_serializer {
    public static write(buffer: SerializerBase, value: PanRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PanRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PanRecognizerInternal.fromPtr(ptr)
    }
}
export class PinchRecognizer_serializer {
    public static write(buffer: SerializerBase, value: PinchRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PinchRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PinchRecognizerInternal.fromPtr(ptr)
    }
}
export class RotationGesture_serializer {
    public static write(buffer: SerializerBase, value: RotationGesture): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RotationGesture {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RotationGestureInternal.fromPtr(ptr)
    }
}
export class RotationRecognizer_serializer {
    public static write(buffer: SerializerBase, value: RotationRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RotationRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RotationRecognizerInternal.fromPtr(ptr)
    }
}
export class ScrollableTargetInfo_serializer {
    public static write(buffer: SerializerBase, value: ScrollableTargetInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ScrollableTargetInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ScrollableTargetInfoInternal.fromPtr(ptr)
    }
}
export class SwipeGesture_serializer {
    public static write(buffer: SerializerBase, value: SwipeGesture): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SwipeGesture {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SwipeGestureInternal.fromPtr(ptr)
    }
}
export class SwipeRecognizer_serializer {
    public static write(buffer: SerializerBase, value: SwipeRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SwipeRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SwipeRecognizerInternal.fromPtr(ptr)
    }
}
export class TapRecognizer_serializer {
    public static write(buffer: SerializerBase, value: TapRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TapRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TapRecognizerInternal.fromPtr(ptr)
    }
}
export class FingerInfo_serializer {
    public static write(buffer: SerializerBase, value: FingerInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeNumber(value_id)
        const value_globalX  = value.globalX
        valueSerializer.writeNumber(value_globalX)
        const value_globalY  = value.globalY
        valueSerializer.writeNumber(value_globalY)
        const value_localX  = value.localX
        valueSerializer.writeNumber(value_localX)
        const value_localY  = value.localY
        valueSerializer.writeNumber(value_localY)
        const value_displayX  = value.displayX
        valueSerializer.writeNumber(value_displayX)
        const value_displayY  = value.displayY
        valueSerializer.writeNumber(value_displayY)
        const value_hand  = value.hand
        let value_hand_type : int32 = RuntimeType.UNDEFINED
        value_hand_type = runtimeType(value_hand)
        valueSerializer.writeInt8((value_hand_type).toChar())
        if ((value_hand_type) != (RuntimeType.UNDEFINED)) {
            const value_hand_value  = (value_hand as InteractionHand)
            valueSerializer.writeInt32(TypeChecker.InteractionHand_ToNumeric(value_hand_value))
        }
    }
    public static read(buffer: DeserializerBase): FingerInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : number = (valueDeserializer.readNumber() as number)
        const globalX_result : number = (valueDeserializer.readNumber() as number)
        const globalY_result : number = (valueDeserializer.readNumber() as number)
        const localX_result : number = (valueDeserializer.readNumber() as number)
        const localY_result : number = (valueDeserializer.readNumber() as number)
        const displayX_result : number = (valueDeserializer.readNumber() as number)
        const displayY_result : number = (valueDeserializer.readNumber() as number)
        const hand_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hand_buf : InteractionHand | undefined
        if ((hand_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hand_buf = TypeChecker.InteractionHand_FromNumeric(valueDeserializer.readInt32())
        }
        const hand_result : InteractionHand | undefined = hand_buf
        let value : FingerInfo = ({id: id_result, globalX: globalX_result, globalY: globalY_result, localX: localX_result, localY: localY_result, displayX: displayX_result, displayY: displayY_result, hand: hand_result} as FingerInfo)
        return value
    }
}
export class GestureInfo_serializer {
    public static write(buffer: SerializerBase, value: GestureInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_tag  = value.tag
        let value_tag_type : int32 = RuntimeType.UNDEFINED
        value_tag_type = runtimeType(value_tag)
        valueSerializer.writeInt8((value_tag_type).toChar())
        if ((value_tag_type) != (RuntimeType.UNDEFINED)) {
            const value_tag_value  = value_tag!
            valueSerializer.writeString(value_tag_value)
        }
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.GestureControl_GestureType_ToNumeric(value_type))
        const value_isSystemGesture  = value.isSystemGesture
        valueSerializer.writeBoolean(value_isSystemGesture)
    }
    public static read(buffer: DeserializerBase): GestureInfo {
        let valueDeserializer : DeserializerBase = buffer
        const tag_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let tag_buf : string | undefined
        if ((tag_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            tag_buf = (valueDeserializer.readString() as string)
        }
        const tag_result : string | undefined = tag_buf
        const type_result : GestureControl.GestureType = TypeChecker.GestureControl_GestureType_FromNumeric(valueDeserializer.readInt32())
        const isSystemGesture_result : boolean = valueDeserializer.readBoolean()
        let value : GestureInfo = ({tag: tag_result, type: type_result, isSystemGesture: isSystemGesture_result} as GestureInfo)
        return value
    }
}
export class LongPressGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: LongPressGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_repeat  = value.repeat
        let value_repeat_type : int32 = RuntimeType.UNDEFINED
        value_repeat_type = runtimeType(value_repeat)
        valueSerializer.writeInt8((value_repeat_type).toChar())
        if ((value_repeat_type) != (RuntimeType.UNDEFINED)) {
            const value_repeat_value  = value_repeat!
            valueSerializer.writeBoolean(value_repeat_value)
        }
        const value_duration  = value.duration
        let value_duration_type : int32 = RuntimeType.UNDEFINED
        value_duration_type = runtimeType(value_duration)
        valueSerializer.writeInt8((value_duration_type).toChar())
        if ((value_duration_type) != (RuntimeType.UNDEFINED)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
    }
    public static read(buffer: DeserializerBase): LongPressGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const repeat_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let repeat_buf : boolean | undefined
        if ((repeat_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            repeat_buf = valueDeserializer.readBoolean()
        }
        const repeat_result : boolean | undefined = repeat_buf
        const duration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let duration_buf : number | undefined
        if ((duration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        let value : LongPressGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimited_result, fingers: fingers_result, repeat: repeat_result, duration: duration_result} as LongPressGestureHandlerOptions)
        return value
    }
}
export class PanGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: PanGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as PanDirection)
            valueSerializer.writeInt32(TypeChecker.PanDirection_ToNumeric(value_direction_value))
        }
        const value_distance  = value.distance
        let value_distance_type : int32 = RuntimeType.UNDEFINED
        value_distance_type = runtimeType(value_distance)
        valueSerializer.writeInt8((value_distance_type).toChar())
        if ((value_distance_type) != (RuntimeType.UNDEFINED)) {
            const value_distance_value  = value_distance!
            valueSerializer.writeNumber(value_distance_value)
        }
    }
    public static read(buffer: DeserializerBase): PanGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : PanDirection | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.PanDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : PanDirection | undefined = direction_buf
        const distance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distance_buf : number | undefined
        if ((distance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            distance_buf = (valueDeserializer.readNumber() as number)
        }
        const distance_result : number | undefined = distance_buf
        let value : PanGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimited_result, fingers: fingers_result, direction: direction_result, distance: distance_result} as PanGestureHandlerOptions)
        return value
    }
}
export class PinchGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: PinchGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_distance  = value.distance
        let value_distance_type : int32 = RuntimeType.UNDEFINED
        value_distance_type = runtimeType(value_distance)
        valueSerializer.writeInt8((value_distance_type).toChar())
        if ((value_distance_type) != (RuntimeType.UNDEFINED)) {
            const value_distance_value  = value_distance!
            valueSerializer.writeNumber(value_distance_value)
        }
    }
    public static read(buffer: DeserializerBase): PinchGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const distance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distance_buf : number | undefined
        if ((distance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            distance_buf = (valueDeserializer.readNumber() as number)
        }
        const distance_result : number | undefined = distance_buf
        let value : PinchGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimited_result, fingers: fingers_result, distance: distance_result} as PinchGestureHandlerOptions)
        return value
    }
}
export class RotationGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: RotationGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_angle  = value.angle
        let value_angle_type : int32 = RuntimeType.UNDEFINED
        value_angle_type = runtimeType(value_angle)
        valueSerializer.writeInt8((value_angle_type).toChar())
        if ((value_angle_type) != (RuntimeType.UNDEFINED)) {
            const value_angle_value  = value_angle!
            valueSerializer.writeNumber(value_angle_value)
        }
    }
    public static read(buffer: DeserializerBase): RotationGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const angle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let angle_buf : number | undefined
        if ((angle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            angle_buf = (valueDeserializer.readNumber() as number)
        }
        const angle_result : number | undefined = angle_buf
        let value : RotationGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimited_result, fingers: fingers_result, angle: angle_result} as RotationGestureHandlerOptions)
        return value
    }
}
export class SwipeGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: SwipeGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as SwipeDirection)
            valueSerializer.writeInt32(TypeChecker.SwipeDirection_ToNumeric(value_direction_value))
        }
        const value_speed  = value.speed
        let value_speed_type : int32 = RuntimeType.UNDEFINED
        value_speed_type = runtimeType(value_speed)
        valueSerializer.writeInt8((value_speed_type).toChar())
        if ((value_speed_type) != (RuntimeType.UNDEFINED)) {
            const value_speed_value  = value_speed!
            valueSerializer.writeNumber(value_speed_value)
        }
    }
    public static read(buffer: DeserializerBase): SwipeGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : SwipeDirection | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.SwipeDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : SwipeDirection | undefined = direction_buf
        const speed_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let speed_buf : number | undefined
        if ((speed_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            speed_buf = (valueDeserializer.readNumber() as number)
        }
        const speed_result : number | undefined = speed_buf
        let value : SwipeGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimited_result, fingers: fingers_result, direction: direction_result, speed: speed_result} as SwipeGestureHandlerOptions)
        return value
    }
}
export class TapGestureParameters_serializer {
    public static write(buffer: SerializerBase, value: TapGestureParameters): void {
        let valueSerializer : SerializerBase = buffer
        const value_isFingerCountLimited  = value.isFingerCountLimited
        let value_isFingerCountLimited_type : int32 = RuntimeType.UNDEFINED
        value_isFingerCountLimited_type = runtimeType(value_isFingerCountLimited)
        valueSerializer.writeInt8((value_isFingerCountLimited_type).toChar())
        if ((value_isFingerCountLimited_type) != (RuntimeType.UNDEFINED)) {
            const value_isFingerCountLimited_value  = value_isFingerCountLimited!
            valueSerializer.writeBoolean(value_isFingerCountLimited_value)
        }
        const value_count  = value.count
        let value_count_type : int32 = RuntimeType.UNDEFINED
        value_count_type = runtimeType(value_count)
        valueSerializer.writeInt8((value_count_type).toChar())
        if ((value_count_type) != (RuntimeType.UNDEFINED)) {
            const value_count_value  = value_count!
            valueSerializer.writeNumber(value_count_value)
        }
        const value_fingers  = value.fingers
        let value_fingers_type : int32 = RuntimeType.UNDEFINED
        value_fingers_type = runtimeType(value_fingers)
        valueSerializer.writeInt8((value_fingers_type).toChar())
        if ((value_fingers_type) != (RuntimeType.UNDEFINED)) {
            const value_fingers_value  = value_fingers!
            valueSerializer.writeNumber(value_fingers_value)
        }
        const value_distanceThreshold  = value.distanceThreshold
        let value_distanceThreshold_type : int32 = RuntimeType.UNDEFINED
        value_distanceThreshold_type = runtimeType(value_distanceThreshold)
        valueSerializer.writeInt8((value_distanceThreshold_type).toChar())
        if ((value_distanceThreshold_type) != (RuntimeType.UNDEFINED)) {
            const value_distanceThreshold_value  = value_distanceThreshold!
            valueSerializer.writeNumber(value_distanceThreshold_value)
        }
    }
    public static read(buffer: DeserializerBase): TapGestureParameters {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimited_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isFingerCountLimited_buf : boolean | undefined
        if ((isFingerCountLimited_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isFingerCountLimited_buf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimited_result : boolean | undefined = isFingerCountLimited_buf
        const count_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let count_buf : number | undefined
        if ((count_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            count_buf = (valueDeserializer.readNumber() as number)
        }
        const count_result : number | undefined = count_buf
        const fingers_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingers_buf : number | undefined
        if ((fingers_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fingers_buf = (valueDeserializer.readNumber() as number)
        }
        const fingers_result : number | undefined = fingers_buf
        const distanceThreshold_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distanceThreshold_buf : number | undefined
        if ((distanceThreshold_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            distanceThreshold_buf = (valueDeserializer.readNumber() as number)
        }
        const distanceThreshold_result : number | undefined = distanceThreshold_buf
        let value : TapGestureParameters = ({isFingerCountLimited: isFingerCountLimited_result, count: count_result, fingers: fingers_result, distanceThreshold: distanceThreshold_result} as TapGestureParameters)
        return value
    }
}
export class GestureEvent_serializer {
    public static write(buffer: SerializerBase, value: GestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): GestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return GestureEventInternal.fromPtr(ptr)
    }
}
export class LongPressGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: LongPressGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LongPressGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LongPressGestureEventInternal.fromPtr(ptr)
    }
}
export class PanGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: PanGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PanGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PanGestureEventInternal.fromPtr(ptr)
    }
}
export class PinchGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: PinchGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PinchGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PinchGestureEventInternal.fromPtr(ptr)
    }
}
export class RotationGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: RotationGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RotationGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RotationGestureEventInternal.fromPtr(ptr)
    }
}
export class SwipeGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: SwipeGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SwipeGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SwipeGestureEventInternal.fromPtr(ptr)
    }
}
export class TapGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: TapGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TapGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TapGestureEventInternal.fromPtr(ptr)
    }
}
export class BaseGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: BaseGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaseGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BaseGestureEventInternal.fromPtr(ptr)
    }
}
export interface BaseGestureEvent {
    fingerList: Array<FingerInfo>
}
export class BaseGestureEventInternal extends BaseEventInternal implements MaterializedBase,BaseGestureEvent {
    get fingerList(): Array<FingerInfo> {
        return this.getFingerList()
    }
    set fingerList(fingerList: Array<FingerInfo>) {
        this.setFingerList(fingerList)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(BaseGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): BaseGestureEventInternal {
        return new BaseGestureEventInternal(ptr)
    }
    private getFingerList(): Array<FingerInfo> {
        return this.getFingerList_serialize()
    }
    private setFingerList(fingerList: Array<FingerInfo>): void {
        const fingerList_casted = fingerList as (Array<FingerInfo>)
        this.setFingerList_serialize(fingerList_casted)
        return
    }
    private getFingerList_serialize(): Array<FingerInfo> {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_getFingerList(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = FingerInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fingerList.length).toInt())
        for (let fingerList_counter_i = 0; fingerList_counter_i < fingerList.length; fingerList_counter_i++) {
            const fingerList_element : FingerInfo = fingerList[fingerList_counter_i]
            FingerInfo_serializer.write(thisSerializer, fingerList_element)
        }
        ArkUIGeneratedNativeModule._BaseGestureEvent_setFingerList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GestureEvent {
    repeat: boolean
    fingerList: Array<FingerInfo>
    offsetX: number
    offsetY: number
    angle: number
    speed: number
    scale: number
    pinchCenterX: number
    pinchCenterY: number
    velocityX: number
    velocityY: number
    velocity: number
}
export class GestureEventInternal extends BaseEventInternal implements MaterializedBase,GestureEvent {
    get repeat(): boolean {
        return this.getRepeat()
    }
    set repeat(repeat: boolean) {
        this.setRepeat(repeat)
    }
    get fingerList(): Array<FingerInfo> {
        return this.getFingerList()
    }
    set fingerList(fingerList: Array<FingerInfo>) {
        this.setFingerList(fingerList)
    }
    get offsetX(): number {
        return this.getOffsetX()
    }
    set offsetX(offsetX: number) {
        this.setOffsetX(offsetX)
    }
    get offsetY(): number {
        return this.getOffsetY()
    }
    set offsetY(offsetY: number) {
        this.setOffsetY(offsetY)
    }
    get angle(): number {
        return this.getAngle()
    }
    set angle(angle: number) {
        this.setAngle(angle)
    }
    get speed(): number {
        return this.getSpeed()
    }
    set speed(speed: number) {
        this.setSpeed(speed)
    }
    get scale(): number {
        return this.getScale()
    }
    set scale(scale: number) {
        this.setScale(scale)
    }
    get pinchCenterX(): number {
        return this.getPinchCenterX()
    }
    set pinchCenterX(pinchCenterX: number) {
        this.setPinchCenterX(pinchCenterX)
    }
    get pinchCenterY(): number {
        return this.getPinchCenterY()
    }
    set pinchCenterY(pinchCenterY: number) {
        this.setPinchCenterY(pinchCenterY)
    }
    get velocityX(): number {
        return this.getVelocityX()
    }
    set velocityX(velocityX: number) {
        this.setVelocityX(velocityX)
    }
    get velocityY(): number {
        return this.getVelocityY()
    }
    set velocityY(velocityY: number) {
        this.setVelocityY(velocityY)
    }
    get velocity(): number {
        return this.getVelocity()
    }
    set velocity(velocity: number) {
        this.setVelocity(velocity)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(GestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): GestureEventInternal {
        return new GestureEventInternal(ptr)
    }
    private getRepeat(): boolean {
        return this.getRepeat_serialize()
    }
    private setRepeat(repeat: boolean): void {
        const repeat_casted = repeat as (boolean)
        this.setRepeat_serialize(repeat_casted)
        return
    }
    private getFingerList(): Array<FingerInfo> {
        return this.getFingerList_serialize()
    }
    private setFingerList(fingerList: Array<FingerInfo>): void {
        const fingerList_casted = fingerList as (Array<FingerInfo>)
        this.setFingerList_serialize(fingerList_casted)
        return
    }
    private getOffsetX(): number {
        return this.getOffsetX_serialize()
    }
    private setOffsetX(offsetX: number): void {
        const offsetX_casted = offsetX as (number)
        this.setOffsetX_serialize(offsetX_casted)
        return
    }
    private getOffsetY(): number {
        return this.getOffsetY_serialize()
    }
    private setOffsetY(offsetY: number): void {
        const offsetY_casted = offsetY as (number)
        this.setOffsetY_serialize(offsetY_casted)
        return
    }
    private getAngle(): number {
        return this.getAngle_serialize()
    }
    private setAngle(angle: number): void {
        const angle_casted = angle as (number)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getSpeed(): number {
        return this.getSpeed_serialize()
    }
    private setSpeed(speed: number): void {
        const speed_casted = speed as (number)
        this.setSpeed_serialize(speed_casted)
        return
    }
    private getScale(): number {
        return this.getScale_serialize()
    }
    private setScale(scale: number): void {
        const scale_casted = scale as (number)
        this.setScale_serialize(scale_casted)
        return
    }
    private getPinchCenterX(): number {
        return this.getPinchCenterX_serialize()
    }
    private setPinchCenterX(pinchCenterX: number): void {
        const pinchCenterX_casted = pinchCenterX as (number)
        this.setPinchCenterX_serialize(pinchCenterX_casted)
        return
    }
    private getPinchCenterY(): number {
        return this.getPinchCenterY_serialize()
    }
    private setPinchCenterY(pinchCenterY: number): void {
        const pinchCenterY_casted = pinchCenterY as (number)
        this.setPinchCenterY_serialize(pinchCenterY_casted)
        return
    }
    private getVelocityX(): number {
        return this.getVelocityX_serialize()
    }
    private setVelocityX(velocityX: number): void {
        const velocityX_casted = velocityX as (number)
        this.setVelocityX_serialize(velocityX_casted)
        return
    }
    private getVelocityY(): number {
        return this.getVelocityY_serialize()
    }
    private setVelocityY(velocityY: number): void {
        const velocityY_casted = velocityY as (number)
        this.setVelocityY_serialize(velocityY_casted)
        return
    }
    private getVelocity(): number {
        return this.getVelocity_serialize()
    }
    private setVelocity(velocity: number): void {
        const velocity_casted = velocity as (number)
        this.setVelocity_serialize(velocity_casted)
        return
    }
    private getRepeat_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getRepeat(this.peer!.ptr)
        return retval
    }
    private setRepeat_serialize(repeat: boolean): void {
        ArkUIGeneratedNativeModule._GestureEvent_setRepeat(this.peer!.ptr, repeat ? 1 : 0)
    }
    private getFingerList_serialize(): Array<FingerInfo> {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getFingerList(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = FingerInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fingerList.length).toInt())
        for (let fingerList_counter_i = 0; fingerList_counter_i < fingerList.length; fingerList_counter_i++) {
            const fingerList_element : FingerInfo = fingerList[fingerList_counter_i]
            FingerInfo_serializer.write(thisSerializer, fingerList_element)
        }
        ArkUIGeneratedNativeModule._GestureEvent_setFingerList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOffsetX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getOffsetX(this.peer!.ptr)
        return retval
    }
    private setOffsetX_serialize(offsetX: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setOffsetX(this.peer!.ptr, offsetX)
    }
    private getOffsetY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getOffsetY(this.peer!.ptr)
        return retval
    }
    private setOffsetY_serialize(offsetY: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setOffsetY(this.peer!.ptr, offsetY)
    }
    private getAngle_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setAngle(this.peer!.ptr, angle)
    }
    private getSpeed_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getSpeed(this.peer!.ptr)
        return retval
    }
    private setSpeed_serialize(speed: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setSpeed(this.peer!.ptr, speed)
    }
    private getScale_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getScale(this.peer!.ptr)
        return retval
    }
    private setScale_serialize(scale: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setScale(this.peer!.ptr, scale)
    }
    private getPinchCenterX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getPinchCenterX(this.peer!.ptr)
        return retval
    }
    private setPinchCenterX_serialize(pinchCenterX: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setPinchCenterX(this.peer!.ptr, pinchCenterX)
    }
    private getPinchCenterY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getPinchCenterY(this.peer!.ptr)
        return retval
    }
    private setPinchCenterY_serialize(pinchCenterY: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setPinchCenterY(this.peer!.ptr, pinchCenterY)
    }
    private getVelocityX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private setVelocityX_serialize(velocityX: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocityX(this.peer!.ptr, velocityX)
    }
    private getVelocityY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private setVelocityY_serialize(velocityY: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocityY(this.peer!.ptr, velocityY)
    }
    private getVelocity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private setVelocity_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocity(this.peer!.ptr, velocity)
    }
}
export class LongPressRecognizerInternal {
    public static fromPtr(ptr: KPointer): LongPressRecognizer {
        return new LongPressRecognizer(ptr)
    }
}
export class LongPressRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(LongPressRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressRecognizer_getFinalizer()
    }
    public isRepeat(): boolean {
        return this.isRepeat_serialize()
    }
    public getDuration(): number {
        return this.getDuration_serialize()
    }
    private isRepeat_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_isRepeat(this.peer!.ptr)
        return retval
    }
    private getDuration_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_getDuration(this.peer!.ptr)
        return retval
    }
}
export class PanRecognizerInternal {
    public static fromPtr(ptr: KPointer): PanRecognizer {
        return new PanRecognizer(ptr)
    }
}
export class PanRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(PanRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanRecognizer_getFinalizer()
    }
    public getPanGestureOptions(): PanGestureOptions {
        return this.getPanGestureOptions_serialize()
    }
    private getPanGestureOptions_serialize(): PanGestureOptions {
        const retval  = ArkUIGeneratedNativeModule._PanRecognizer_getPanGestureOptions(this.peer!.ptr)
        const obj : PanGestureOptions = PanGestureOptionsInternal.fromPtr(retval)
        return obj
    }
}
export class PinchRecognizerInternal {
    public static fromPtr(ptr: KPointer): PinchRecognizer {
        return new PinchRecognizer(ptr)
    }
}
export class PinchRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(PinchRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchRecognizer_getFinalizer()
    }
    public getDistance(): number {
        return this.getDistance_serialize()
    }
    private getDistance_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PinchRecognizer_getDistance(this.peer!.ptr)
        return retval
    }
}
export class RotationGestureInternal {
    public static fromPtr(ptr: KPointer): RotationGesture {
        return new RotationGesture(ptr)
    }
}
export class RotationGesture extends Gesture implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(RotationGesture.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGesture_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGesture_getFinalizer()
    }
    private static $_instantiate_serialize(factory: (() => RotationGesture), value?: RotationGestureHandlerOptions): RotationGesture {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(factory)
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            RotationGestureHandlerOptions_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RotationGesture_$_instantiate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGesture = RotationGestureInternal.fromPtr(retval)
        return obj
    }
    public static $_instantiate(factory: (() => RotationGesture), value?: RotationGestureHandlerOptions): RotationGesture {
        const factory_casted = factory as ((() => RotationGesture))
        const value_casted = value as (RotationGestureHandlerOptions | undefined)
        return RotationGesture.$_instantiate_serialize(factory_casted, value_casted)
    }
    public onActionStart(event: ((value0: GestureEvent) => void)): this {
        const event_casted = event as (((value0: GestureEvent) => void))
        this.onActionStart_serialize(event_casted)
        return this
    }
    public onActionUpdate(event: ((value0: GestureEvent) => void)): this {
        const event_casted = event as (((value0: GestureEvent) => void))
        this.onActionUpdate_serialize(event_casted)
        return this
    }
    public onActionEnd(event: ((value0: GestureEvent) => void)): this {
        const event_casted = event as (((value0: GestureEvent) => void))
        this.onActionEnd_serialize(event_casted)
        return this
    }
    public onActionCancel(event: ((value0: GestureEvent) => void)): this {
        const event_casted = event as (((value0: GestureEvent) => void))
        this.onActionCancel_serialize(event_casted)
        return this
    }
    private onActionStart_serialize(event: ((value0: GestureEvent) => void)): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._RotationGesture_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
    private onActionUpdate_serialize(event: ((value0: GestureEvent) => void)): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._RotationGesture_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
    private onActionEnd_serialize(event: ((value0: GestureEvent) => void)): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._RotationGesture_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
    private onActionCancel_serialize(event: ((value0: GestureEvent) => void)): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._RotationGesture_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
}
export class RotationRecognizerInternal {
    public static fromPtr(ptr: KPointer): RotationRecognizer {
        return new RotationRecognizer(ptr)
    }
}
export class RotationRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(RotationRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationRecognizer_getFinalizer()
    }
    public getAngle(): number {
        return this.getAngle_serialize()
    }
    private getAngle_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RotationRecognizer_getAngle(this.peer!.ptr)
        return retval
    }
}
export class ScrollableTargetInfoInternal {
    public static fromPtr(ptr: KPointer): ScrollableTargetInfo {
        return new ScrollableTargetInfo(ptr)
    }
}
export class ScrollableTargetInfo extends EventTargetInfo implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(ScrollableTargetInfo.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScrollableTargetInfo_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollableTargetInfo_getFinalizer()
    }
    public isBegin(): boolean {
        return this.isBegin_serialize()
    }
    public isEnd(): boolean {
        return this.isEnd_serialize()
    }
    private isBegin_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._ScrollableTargetInfo_isBegin(this.peer!.ptr)
        return retval
    }
    private isEnd_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._ScrollableTargetInfo_isEnd(this.peer!.ptr)
        return retval
    }
}
export class SwipeGestureInternal {
    public static fromPtr(ptr: KPointer): SwipeGesture {
        return new SwipeGesture(ptr)
    }
}
export class SwipeGesture extends Gesture implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(SwipeGesture.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGesture_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGesture_getFinalizer()
    }
    private static $_instantiate_serialize(factory: (() => SwipeGesture), value?: SwipeGestureHandlerOptions): SwipeGesture {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(factory)
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SwipeGestureHandlerOptions_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._SwipeGesture_$_instantiate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SwipeGesture = SwipeGestureInternal.fromPtr(retval)
        return obj
    }
    public static $_instantiate(factory: (() => SwipeGesture), value?: SwipeGestureHandlerOptions): SwipeGesture {
        const factory_casted = factory as ((() => SwipeGesture))
        const value_casted = value as (SwipeGestureHandlerOptions | undefined)
        return SwipeGesture.$_instantiate_serialize(factory_casted, value_casted)
    }
    public onAction(event: ((value0: GestureEvent) => void)): this {
        const event_casted = event as (((value0: GestureEvent) => void))
        this.onAction_serialize(event_casted)
        return this
    }
    private onAction_serialize(event: ((value0: GestureEvent) => void)): this {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._SwipeGesture_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return this
    }
}
export class SwipeRecognizerInternal {
    public static fromPtr(ptr: KPointer): SwipeRecognizer {
        return new SwipeRecognizer(ptr)
    }
}
export class SwipeRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(SwipeRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeRecognizer_getFinalizer()
    }
    public getVelocityThreshold(): number {
        return this.getVelocityThreshold_serialize()
    }
    public getDirection(): SwipeDirection {
        return this.getDirection_serialize()
    }
    private getVelocityThreshold_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_getVelocityThreshold(this.peer!.ptr)
        return retval
    }
    private getDirection_serialize(): SwipeDirection {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_getDirection(this.peer!.ptr)
        return TypeChecker.SwipeDirection_FromNumeric(retval)
    }
}
export class TapRecognizerInternal {
    public static fromPtr(ptr: KPointer): TapRecognizer {
        return new TapRecognizer(ptr)
    }
}
export class TapRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(TapRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapRecognizer_getFinalizer()
    }
    public getTapCount(): number {
        return this.getTapCount_serialize()
    }
    private getTapCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TapRecognizer_getTapCount(this.peer!.ptr)
        return retval
    }
}
export interface LongPressGestureEvent {
    repeat: boolean
}
export class LongPressGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,LongPressGestureEvent {
    get repeat(): boolean {
        return this.getRepeat()
    }
    set repeat(repeat: boolean) {
        this.setRepeat(repeat)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(LongPressGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LongPressGestureEventInternal {
        return new LongPressGestureEventInternal(ptr)
    }
    private getRepeat(): boolean {
        return this.getRepeat_serialize()
    }
    private setRepeat(repeat: boolean): void {
        const repeat_casted = repeat as (boolean)
        this.setRepeat_serialize(repeat_casted)
        return
    }
    private getRepeat_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureEvent_getRepeat(this.peer!.ptr)
        return retval
    }
    private setRepeat_serialize(repeat: boolean): void {
        ArkUIGeneratedNativeModule._LongPressGestureEvent_setRepeat(this.peer!.ptr, repeat ? 1 : 0)
    }
}
export interface PanGestureEvent {
    offsetX: number
    offsetY: number
    velocityX: number
    velocityY: number
    velocity: number
}
export class PanGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,PanGestureEvent {
    get offsetX(): number {
        return this.getOffsetX()
    }
    set offsetX(offsetX: number) {
        this.setOffsetX(offsetX)
    }
    get offsetY(): number {
        return this.getOffsetY()
    }
    set offsetY(offsetY: number) {
        this.setOffsetY(offsetY)
    }
    get velocityX(): number {
        return this.getVelocityX()
    }
    set velocityX(velocityX: number) {
        this.setVelocityX(velocityX)
    }
    get velocityY(): number {
        return this.getVelocityY()
    }
    set velocityY(velocityY: number) {
        this.setVelocityY(velocityY)
    }
    get velocity(): number {
        return this.getVelocity()
    }
    set velocity(velocity: number) {
        this.setVelocity(velocity)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(PanGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PanGestureEventInternal {
        return new PanGestureEventInternal(ptr)
    }
    private getOffsetX(): number {
        return this.getOffsetX_serialize()
    }
    private setOffsetX(offsetX: number): void {
        const offsetX_casted = offsetX as (number)
        this.setOffsetX_serialize(offsetX_casted)
        return
    }
    private getOffsetY(): number {
        return this.getOffsetY_serialize()
    }
    private setOffsetY(offsetY: number): void {
        const offsetY_casted = offsetY as (number)
        this.setOffsetY_serialize(offsetY_casted)
        return
    }
    private getVelocityX(): number {
        return this.getVelocityX_serialize()
    }
    private setVelocityX(velocityX: number): void {
        const velocityX_casted = velocityX as (number)
        this.setVelocityX_serialize(velocityX_casted)
        return
    }
    private getVelocityY(): number {
        return this.getVelocityY_serialize()
    }
    private setVelocityY(velocityY: number): void {
        const velocityY_casted = velocityY as (number)
        this.setVelocityY_serialize(velocityY_casted)
        return
    }
    private getVelocity(): number {
        return this.getVelocity_serialize()
    }
    private setVelocity(velocity: number): void {
        const velocity_casted = velocity as (number)
        this.setVelocity_serialize(velocity_casted)
        return
    }
    private getOffsetX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetX(this.peer!.ptr)
        return retval
    }
    private setOffsetX_serialize(offsetX: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetX(this.peer!.ptr, offsetX)
    }
    private getOffsetY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetY(this.peer!.ptr)
        return retval
    }
    private setOffsetY_serialize(offsetY: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetY(this.peer!.ptr, offsetY)
    }
    private getVelocityX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private setVelocityX_serialize(velocityX: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityX(this.peer!.ptr, velocityX)
    }
    private getVelocityY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private setVelocityY_serialize(velocityY: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityY(this.peer!.ptr, velocityY)
    }
    private getVelocity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private setVelocity_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocity(this.peer!.ptr, velocity)
    }
}
export interface PinchGestureEvent {
    scale: number
    pinchCenterX: number
    pinchCenterY: number
}
export class PinchGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,PinchGestureEvent {
    get scale(): number {
        return this.getScale()
    }
    set scale(scale: number) {
        this.setScale(scale)
    }
    get pinchCenterX(): number {
        return this.getPinchCenterX()
    }
    set pinchCenterX(pinchCenterX: number) {
        this.setPinchCenterX(pinchCenterX)
    }
    get pinchCenterY(): number {
        return this.getPinchCenterY()
    }
    set pinchCenterY(pinchCenterY: number) {
        this.setPinchCenterY(pinchCenterY)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(PinchGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PinchGestureEventInternal {
        return new PinchGestureEventInternal(ptr)
    }
    private getScale(): number {
        return this.getScale_serialize()
    }
    private setScale(scale: number): void {
        const scale_casted = scale as (number)
        this.setScale_serialize(scale_casted)
        return
    }
    private getPinchCenterX(): number {
        return this.getPinchCenterX_serialize()
    }
    private setPinchCenterX(pinchCenterX: number): void {
        const pinchCenterX_casted = pinchCenterX as (number)
        this.setPinchCenterX_serialize(pinchCenterX_casted)
        return
    }
    private getPinchCenterY(): number {
        return this.getPinchCenterY_serialize()
    }
    private setPinchCenterY(pinchCenterY: number): void {
        const pinchCenterY_casted = pinchCenterY as (number)
        this.setPinchCenterY_serialize(pinchCenterY_casted)
        return
    }
    private getScale_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getScale(this.peer!.ptr)
        return retval
    }
    private setScale_serialize(scale: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setScale(this.peer!.ptr, scale)
    }
    private getPinchCenterX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterX(this.peer!.ptr)
        return retval
    }
    private setPinchCenterX_serialize(pinchCenterX: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterX(this.peer!.ptr, pinchCenterX)
    }
    private getPinchCenterY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterY(this.peer!.ptr)
        return retval
    }
    private setPinchCenterY_serialize(pinchCenterY: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterY(this.peer!.ptr, pinchCenterY)
    }
}
export interface RotationGestureEvent {
    angle: number
}
export class RotationGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,RotationGestureEvent {
    get angle(): number {
        return this.getAngle()
    }
    set angle(angle: number) {
        this.setAngle(angle)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(RotationGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): RotationGestureEventInternal {
        return new RotationGestureEventInternal(ptr)
    }
    private getAngle(): number {
        return this.getAngle_serialize()
    }
    private setAngle(angle: number): void {
        const angle_casted = angle as (number)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getAngle_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._RotationGestureEvent_setAngle(this.peer!.ptr, angle)
    }
}
export interface SwipeGestureEvent {
    angle: number
    speed: number
}
export class SwipeGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,SwipeGestureEvent {
    get angle(): number {
        return this.getAngle()
    }
    set angle(angle: number) {
        this.setAngle(angle)
    }
    get speed(): number {
        return this.getSpeed()
    }
    set speed(speed: number) {
        this.setSpeed(speed)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(SwipeGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): SwipeGestureEventInternal {
        return new SwipeGestureEventInternal(ptr)
    }
    private getAngle(): number {
        return this.getAngle_serialize()
    }
    private setAngle(angle: number): void {
        const angle_casted = angle as (number)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getSpeed(): number {
        return this.getSpeed_serialize()
    }
    private setSpeed(speed: number): void {
        const speed_casted = speed as (number)
        this.setSpeed_serialize(speed_casted)
        return
    }
    private getAngle_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setAngle(this.peer!.ptr, angle)
    }
    private getSpeed_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_getSpeed(this.peer!.ptr)
        return retval
    }
    private setSpeed_serialize(speed: number): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setSpeed(this.peer!.ptr, speed)
    }
}
export interface TapGestureEvent {
}
export class TapGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,TapGestureEvent {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(TapGestureEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureEventInternal {
        return new TapGestureEventInternal(ptr)
    }
}
export namespace GestureControl {
    export enum GestureType {
        TAP_GESTURE = 0,
        LONG_PRESS_GESTURE = 1,
        PAN_GESTURE = 2,
        PINCH_GESTURE = 3,
        SWIPE_GESTURE = 4,
        ROTATION_GESTURE = 5,
        DRAG = 6,
        CLICK = 7
    }
}

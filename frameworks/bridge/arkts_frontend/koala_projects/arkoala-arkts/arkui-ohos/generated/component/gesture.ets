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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { GestureControl, GestureHandler } from '#handwritten'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { InteractionHand } from './enums'
import { BaseEvent, BaseEventInternal } from './common'
// instructive change start
import { GlobalStateManager, MutableState } from '@koalaui/runtime'
// instructive change end
export class EventTargetInfoInternal {
    public static fromPtr(ptr: KPointer): EventTargetInfo {
        return new EventTargetInfo(MaterializedBaseTag.NOP, ptr)
    }
}
export class EventTargetInfo implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, EventTargetInfo.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, EventTargetInfo.construct())
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
}
export class GestureRecognizerInternal {
    public static fromPtr(ptr: KPointer): GestureRecognizer {
        return new GestureRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class GestureRecognizer implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, GestureRecognizer.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, GestureRecognizer.construct())
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
    public getFingerCount(): int32 {
        return this.getFingerCount_serialize()
    }
    public isFingerCountLimit(): boolean {
        return this.isFingerCountLimit_serialize()
    }
    public preventBegin(): void {
        this.preventBegin_serialize()
        return
    }
    private getTag_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getTag(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getType_serialize(): GestureControl.GestureType {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(this.peer!.ptr)
        return GestureControl.GestureType.fromValue(retval)
    }
    private isBuiltIn_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isBuiltIn(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(isEnabled: boolean): void {
        ArkUIGeneratedNativeModule._GestureRecognizer_setEnabled(this.peer!.ptr, isEnabled ? true : false)
    }
    private isEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isEnabled(this.peer!.ptr)
        return retval
    }
    private getState_serialize(): GestureRecognizerState {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getState(this.peer!.ptr)
        return GestureRecognizerState.fromValue(retval)
    }
    private getEventTargetInfo_serialize(): EventTargetInfo {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getEventTargetInfo(this.peer!.ptr)
        // instructive change start
        const isScorllableComponent = ArkUIGeneratedNativeModule._GestureOps_isScrollableComponent(retval)
        if (isScorllableComponent) {
            const scrollableTargetInfoObj : ScrollableTargetInfo = ScrollableTargetInfoInternal.fromPtr(retval)
            return scrollableTargetInfoObj
        }
        return EventTargetInfoInternal.fromPtr(retval)
        // instructive change end
    }
    private isValid_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isValid(this.peer!.ptr)
        return retval
    }
    private getFingerCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getFingerCount(this.peer!.ptr)
        return retval
    }
    private isFingerCountLimit_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isFingerCountLimit(this.peer!.ptr)
        return retval
    }
    private preventBegin_serialize(): void {
        ArkUIGeneratedNativeModule._GestureRecognizer_preventBegin(this.peer!.ptr)
    }
}
export class PanGestureOptionsInternal {
    public static fromPtr(ptr: KPointer): PanGestureOptions {
        return new PanGestureOptions(MaterializedBaseTag.NOP, ptr)
    }
}
export class PanGestureOptions implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    // instructive change start
    public optionState: MutableState<int32> | undefined
    // instructive change end
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PanGestureOptions.getFinalizer())
    }
    constructor(value?: PanGestureHandlerOptions) {
        this(MaterializedBaseTag.NOP, PanGestureOptions.construct(value))
        // instructive change start
        const manager = GlobalStateManager.instance
        this.optionState = manager.mutableState<int32>(0 as int32, true)
        // instructive change end
    }
    static construct(value?: PanGestureHandlerOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PanGestureHandlerOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureOptions_getFinalizer()
    }
    // instructive change start
    public getOptionState(): number {
        return this.optionState!.value
    }
    public setOptionState(): void {
        this.optionState!.value = this.optionState!.value % 100 + 1
    }
    // instructive change end
    public setDirection(value: PanDirection): void {
        const value_casted = value as (PanDirection)
        this.setDirection_serialize(value_casted)
        // instructive change start
        this.setOptionState()
        // instructive change end
        return
    }
    public setDistance(value: double): void {
        const value_casted = value as (double)
        this.setDistance_serialize(value_casted)
        // instructive change end
        this.setOptionState()
        // instructive change end
        return
    }
    public setFingers(value: int32): void {
        const value_casted = value as (int32)
        this.setFingers_serialize(value_casted)
        // instructive change start
        this.setOptionState()
        // instructive change end
        return
    }
    public getDirection(): PanDirection {
        return this.getDirection_serialize()
    }
    public getDistance(): double {
        return this.getDistance_serialize()
    }
    private setDirection_serialize(value: PanDirection): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDirection(this.peer!.ptr, value.valueOf())
    }
    private setDistance_serialize(value: double): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDistance(this.peer!.ptr, value)
    }
    private setFingers_serialize(value: int32): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setFingers(this.peer!.ptr, value)
    }
    private getDirection_serialize(): PanDirection {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDirection(this.peer!.ptr)
        return PanDirection.fromValue(retval)
    }
    private getDistance_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDistance(this.peer!.ptr)
        return retval
    }
}
export class TouchRecognizerInternal {
    public static fromPtr(ptr: KPointer): TouchRecognizer {
        return new TouchRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class TouchRecognizer implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TouchRecognizer.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TouchRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TouchRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TouchRecognizer_getFinalizer()
    }
    public getEventTargetInfo(): EventTargetInfo {
        return this.getEventTargetInfo_serialize()
    }
    public cancelTouch(): void {
        this.cancelTouch_serialize()
        return
    }
    private getEventTargetInfo_serialize(): EventTargetInfo {
        const retval  = ArkUIGeneratedNativeModule._TouchRecognizer_getEventTargetInfo(this.peer!.ptr)
        const obj : EventTargetInfo = EventTargetInfoInternal.fromPtr(retval)
        return obj
    }
    private cancelTouch_serialize(): void {
        ArkUIGeneratedNativeModule._TouchRecognizer_cancelTouch(this.peer!.ptr)
    }
}
export enum PanDirection {
    None = 0,
    Left = 1,
    Right = 2,
    Horizontal = 3,
    Up = 4,
    UP_LEFT = 5,
    UP_RIGHT = 6,
    UP_HORIZONTAL = 7,
    Down = 8,
    DOWN_LEFT = 9,
    DOWN_RIGHT = 10,
    DOWN_HORIZONTAL = 11,
    Vertical = 12,
    VERTICAL_LEFT = 13,
    VERTICAL_RIGHT = 14,
    All = 15,
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    HORIZONTAL = 3,
    UP = 4,
    UP_LEFT_DUMMY = 5,
    UP_RIGHT_DUMMY = 6,
    UP_HORIZONTAL_DUMMY = 7,
    DOWN = 8,
    DOWN_LEFT_DUMMY = 9,
    DOWN_RIGHT_DUMMY = 10,
    DOWN_HORIZONTAL_DUMMY = 11,
    VERTICAL = 12,
    VERTICAL_LEFT_DUMMY = 13,
    VERTICAL_RIGHT_DUMMY = 14,
    ALL = 15
}
export enum SwipeDirection {
    None = 0,
    Horizontal = 1,
    Vertical = 2,
    All = 3,
    NONE = 0,
    HORIZONTAL = 1,
    VERTICAL = 2,
    ALL = 3
}
export enum GestureMode {
    Sequence = 0,
    Parallel = 1,
    Exclusive = 2,
    SEQUENCE = 0,
    PARALLEL = 1,
    EXCLUSIVE = 2
}
export enum GestureMask {
    Normal = 0,
    IgnoreInternal = 1,
    NORMAL = 0,
    IGNORE_INTERNAL = 1
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
export interface EventLocationInfo {
    x: double;
    y: double;
    windowX: double;
    windowY: double;
    displayX: double;
    displayY: double;
}
export interface FingerInfo {
    id: int32;
    globalX: double;
    globalY: double;
    localX: double;
    localY: double;
    displayX: double;
    displayY: double;
    hand?: InteractionHand;
}
export interface BaseHandlerOptions {
    isFingerCountLimited?: boolean;
}
export interface TapGestureParameters extends BaseHandlerOptions {
    count?: int32;
    fingers?: int32;
    distanceThreshold?: double;
}
export interface TapGestureHandlerOptions extends BaseHandlerOptions {
    count?: int32;
    fingers?: int32;
}
export interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: int32;
    repeat?: boolean;
    duration?: int32;
}
export interface PanGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: int32;
    direction?: PanDirection;
    distance?: double;
}
export interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: int32;
    direction?: SwipeDirection;
    speed?: double;
}
export interface PinchGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: int32;
    distance?: double;
}
export interface RotationGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: int32;
    angle?: double;
}
export interface GestureGroupGestureHandlerOptions {
    mode: GestureMode;
    gestures: Array<GestureHandler>;
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
export class BaseGestureEvent_serializer {
    public static write(buffer: SerializerBase, value: BaseGestureEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaseGestureEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        // instructive change start
        let type = ArkUIGeneratedNativeModule._GestureOps_getGestureEventType(ptr)
        let recognizerType = GestureControl.GestureType.fromValue(type as int32)
        switch(recognizerType) {
            case GestureControl.GestureType.TAP_GESTURE:
                return TapGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.LONG_PRESS_GESTURE:
                return LongPressGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.PAN_GESTURE:
                return PanGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.PINCH_GESTURE:
                return PinchGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.SWIPE_GESTURE:
                return SwipeGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.ROTATION_GESTURE:
                return RotationGestureEventInternal.fromPtr(ptr)
            case GestureControl.GestureType.CLICK:
            case GestureControl.GestureType.DRAG:
            default:
                return BaseGestureEventInternal.fromPtr(ptr)
        }
        // instructive change end
    }
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
export class GestureRecognizer_serializer {
    public static write(buffer: SerializerBase, value: GestureRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): GestureRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        // instructive change start
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(ptr)
        let recognizerType =  GestureControl.GestureType.fromValue(retval)
        switch(recognizerType) {
            case GestureControl.GestureType.TAP_GESTURE:
                return TapRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.LONG_PRESS_GESTURE:
                return LongPressRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.PAN_GESTURE:
                return PanRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.PINCH_GESTURE:
                return PinchRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.SWIPE_GESTURE:
                return SwipeRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.ROTATION_GESTURE:
                return RotationRecognizerInternal.fromPtr(ptr)
            case GestureControl.GestureType.CLICK:
            case GestureControl.GestureType.DRAG:
            default:
                return GestureRecognizerInternal.fromPtr(ptr)
        }
        // instructive change end
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
export class TouchRecognizer_serializer {
    public static write(buffer: SerializerBase, value: TouchRecognizer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TouchRecognizer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TouchRecognizerInternal.fromPtr(ptr)
    }
}
export class EventLocationInfo_serializer {
    public static write(buffer: SerializerBase, value: EventLocationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeFloat64(valueHolderForY)
        const valueHolderForWindowX  = value.windowX
        valueSerializer.writeFloat64(valueHolderForWindowX)
        const valueHolderForWindowY  = value.windowY
        valueSerializer.writeFloat64(valueHolderForWindowY)
        const valueHolderForDisplayX  = value.displayX
        valueSerializer.writeFloat64(valueHolderForDisplayX)
        const valueHolderForDisplayY  = value.displayY
        valueSerializer.writeFloat64(valueHolderForDisplayY)
    }
    public static read(buffer: DeserializerBase): EventLocationInfo {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : double = valueDeserializer.readFloat64()
        const yTmpResult : double = valueDeserializer.readFloat64()
        const windowXTmpResult : double = valueDeserializer.readFloat64()
        const windowYTmpResult : double = valueDeserializer.readFloat64()
        const displayXTmpResult : double = valueDeserializer.readFloat64()
        const displayYTmpResult : double = valueDeserializer.readFloat64()
        let value : EventLocationInfo = ({x: xTmpResult, y: yTmpResult, windowX: windowXTmpResult, windowY: windowYTmpResult, displayX: displayXTmpResult, displayY: displayYTmpResult} as EventLocationInfo)
        return value
    }
}
export class FingerInfo_serializer {
    public static write(buffer: SerializerBase, value: FingerInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeInt32(valueHolderForId)
        const valueHolderForGlobalX  = value.globalX
        valueSerializer.writeFloat64(valueHolderForGlobalX)
        const valueHolderForGlobalY  = value.globalY
        valueSerializer.writeFloat64(valueHolderForGlobalY)
        const valueHolderForLocalX  = value.localX
        valueSerializer.writeFloat64(valueHolderForLocalX)
        const valueHolderForLocalY  = value.localY
        valueSerializer.writeFloat64(valueHolderForLocalY)
        const valueHolderForDisplayX  = value.displayX
        valueSerializer.writeFloat64(valueHolderForDisplayX)
        const valueHolderForDisplayY  = value.displayY
        valueSerializer.writeFloat64(valueHolderForDisplayY)
        const valueHolderForHand  = value.hand
        if (valueHolderForHand !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHandTmpValue  = (valueHolderForHand as InteractionHand)
            valueSerializer.writeInt32(valueHolderForHandTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FingerInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : int32 = valueDeserializer.readInt32()
        const globalXTmpResult : double = valueDeserializer.readFloat64()
        const globalYTmpResult : double = valueDeserializer.readFloat64()
        const localXTmpResult : double = valueDeserializer.readFloat64()
        const localYTmpResult : double = valueDeserializer.readFloat64()
        const displayXTmpResult : double = valueDeserializer.readFloat64()
        const displayYTmpResult : double = valueDeserializer.readFloat64()
        const handTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let handTmpBuf : InteractionHand | undefined = undefined
        if ((handTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            handTmpBuf = InteractionHand.fromValue(valueDeserializer.readInt32())
        }
        const handTmpResult : InteractionHand | undefined = handTmpBuf
        let value : FingerInfo = ({id: idTmpResult, globalX: globalXTmpResult, globalY: globalYTmpResult, localX: localXTmpResult, localY: localYTmpResult, displayX: displayXTmpResult, displayY: displayYTmpResult, hand: handTmpResult} as FingerInfo)
        return value
    }
}
export class GestureInfo_serializer {
    public static write(buffer: SerializerBase, value: GestureInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTag  = value.tag
        if (valueHolderForTag !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTagTmpValue  = valueHolderForTag!
            valueSerializer.writeString(valueHolderForTagTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForIsSystemGesture  = value.isSystemGesture
        valueSerializer.writeBoolean(valueHolderForIsSystemGesture)
    }
    public static read(buffer: DeserializerBase): GestureInfo {
        let valueDeserializer : DeserializerBase = buffer
        const tagTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let tagTmpBuf : string | undefined = undefined
        if ((tagTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            tagTmpBuf = (valueDeserializer.readString() as string)
        }
        const tagTmpResult : string | undefined = tagTmpBuf
        const typeTmpResult : GestureControl.GestureType = GestureControl.GestureType.fromValue(valueDeserializer.readInt32())
        const isSystemGestureTmpResult : boolean = valueDeserializer.readBoolean()
        let value : GestureInfo = ({tag: tagTmpResult, type: typeTmpResult, isSystemGesture: isSystemGestureTmpResult} as GestureInfo)
        return value
    }
}
export class PanGestureHandlerOptions_serializer {
    public static write(buffer: SerializerBase, value: PanGestureHandlerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIsFingerCountLimited  = value.isFingerCountLimited
        if (valueHolderForIsFingerCountLimited !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsFingerCountLimitedTmpValue  = valueHolderForIsFingerCountLimited!
            valueSerializer.writeBoolean(valueHolderForIsFingerCountLimitedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFingers  = value.fingers
        if (valueHolderForFingers !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFingersTmpValue  = valueHolderForFingers!
            valueSerializer.writeInt32(valueHolderForFingersTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as PanDirection)
            valueSerializer.writeInt32(valueHolderForDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDistance  = value.distance
        if (valueHolderForDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistanceTmpValue  = valueHolderForDistance!
            valueSerializer.writeFloat64(valueHolderForDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PanGestureHandlerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isFingerCountLimitedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isFingerCountLimitedTmpBuf : boolean | undefined = undefined
        if ((isFingerCountLimitedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isFingerCountLimitedTmpBuf = valueDeserializer.readBoolean()
        }
        const isFingerCountLimitedTmpResult : boolean | undefined = isFingerCountLimitedTmpBuf
        const fingersTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fingersTmpBuf : int32 | undefined = undefined
        if ((fingersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fingersTmpBuf = valueDeserializer.readInt32()
        }
        const fingersTmpResult : int32 | undefined = fingersTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let directionTmpBuf : PanDirection | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = PanDirection.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : PanDirection | undefined = directionTmpBuf
        const distanceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let distanceTmpBuf : double | undefined = undefined
        if ((distanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distanceTmpBuf = valueDeserializer.readFloat64()
        }
        const distanceTmpResult : double | undefined = distanceTmpBuf
        let value : PanGestureHandlerOptions = ({isFingerCountLimited: isFingerCountLimitedTmpResult, fingers: fingersTmpResult, direction: directionTmpResult, distance: distanceTmpResult} as PanGestureHandlerOptions)
        return value
    }
}
export interface BaseGestureEvent extends BaseEvent {
    fingerList: Array<FingerInfo>
    fingerInfos?: Array<FingerInfo> | undefined
}
export class BaseGestureEventInternal extends BaseEventInternal implements MaterializedBase,BaseGestureEvent {
    public fingerList: Array<FingerInfo>
    public fingerInfos?: Array<FingerInfo> | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.fingerList = this.getFingerList()
        this.fingerInfos = this.getFingerInfos()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, BaseGestureEventInternal.construct())
        this.fingerList = this.getFingerList()
        this.fingerInfos = this.getFingerInfos()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): BaseGestureEventInternal {
        return new BaseGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getFingerList(): Array<FingerInfo> {
        return this.getFingerList_serialize()
    }
    private setFingerList(fingerList: Array<FingerInfo>): void {
        const fingerList_casted = fingerList as (Array<FingerInfo>)
        this.setFingerList_serialize(fingerList_casted)
        return
    }
    private getFingerInfos(): Array<FingerInfo> | undefined {
        return this.getFingerInfos_serialize()
    }
    private setFingerInfos(fingerInfos: Array<FingerInfo> | undefined): void {
        const fingerInfos_casted = fingerInfos as (Array<FingerInfo> | undefined)
        this.setFingerInfos_serialize(fingerInfos_casted)
        return
    }
    private getFingerList_serialize(): Array<FingerInfo> {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_getFingerList(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = FingerInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fingerList.length).toInt())
        for (let fingerListCounterI = 0; fingerListCounterI < fingerList.length; fingerListCounterI++) {
            const fingerListTmpElement : FingerInfo = fingerList[fingerListCounterI]
            FingerInfo_serializer.write(thisSerializer, fingerListTmpElement)
        }
        ArkUIGeneratedNativeModule._BaseGestureEvent_setFingerList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFingerInfos_serialize(): Array<FingerInfo> | undefined {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_getFingerInfos(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<FingerInfo> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<FingerInfo> = new Array<FingerInfo>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = FingerInfo_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<FingerInfo> | undefined = buffer
        return returnResult
    }
    private setFingerInfos_serialize(fingerInfos: Array<FingerInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fingerInfos !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fingerInfosTmpValue  = fingerInfos!
            thisSerializer.writeInt32((fingerInfosTmpValue.length).toInt())
            for (let fingerInfosTmpValueCounterI = 0; fingerInfosTmpValueCounterI < fingerInfosTmpValue.length; fingerInfosTmpValueCounterI++) {
                const fingerInfosTmpValueTmpElement : FingerInfo = fingerInfosTmpValue[fingerInfosTmpValueCounterI]
                FingerInfo_serializer.write(thisSerializer, fingerInfosTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BaseGestureEvent_setFingerInfos(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GestureEvent extends BaseEvent {
    repeat: boolean
    fingerList: Array<FingerInfo>
    fingerInfos?: Array<FingerInfo> | undefined
    offsetX: double
    offsetY: double
    angle: double
    speed: double
    scale: double
    pinchCenterX: double
    pinchCenterY: double
    velocityX: double
    velocityY: double
    velocity: double
    tapLocation?: EventLocationInfo | undefined
}
export class GestureEventInternal extends BaseEventInternal implements MaterializedBase,GestureEvent {
    public repeat: boolean
    public fingerList: Array<FingerInfo>
    public fingerInfos?: Array<FingerInfo> | undefined
    public offsetX: double
    public offsetY: double
    public angle: double
    public speed: double
    public scale: double
    public pinchCenterX: double
    public pinchCenterY: double
    public velocityX: double
    public velocityY: double
    public velocity: double
    public tapLocation?: EventLocationInfo | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.repeat = this.getRepeat()
        this.fingerList = this.getFingerList()
        this.fingerInfos = this.getFingerInfos()
        this.offsetX = this.getOffsetX()
        this.offsetY = this.getOffsetY()
        this.angle = this.getAngle()
        this.speed = this.getSpeed()
        this.scale = this.getScale()
        this.pinchCenterX = this.getPinchCenterX()
        this.pinchCenterY = this.getPinchCenterY()
        this.velocityX = this.getVelocityX()
        this.velocityY = this.getVelocityY()
        this.velocity = this.getVelocity()
        this.tapLocation = this.getTapLocation()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, GestureEventInternal.construct())
        this.repeat = this.getRepeat()
        this.fingerList = this.getFingerList()
        this.fingerInfos = this.getFingerInfos()
        this.offsetX = this.getOffsetX()
        this.offsetY = this.getOffsetY()
        this.angle = this.getAngle()
        this.speed = this.getSpeed()
        this.scale = this.getScale()
        this.pinchCenterX = this.getPinchCenterX()
        this.pinchCenterY = this.getPinchCenterY()
        this.velocityX = this.getVelocityX()
        this.velocityY = this.getVelocityY()
        this.velocity = this.getVelocity()
        this.tapLocation = this.getTapLocation()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): GestureEventInternal {
        return new GestureEventInternal(MaterializedBaseTag.NOP, ptr)
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
    private getFingerInfos(): Array<FingerInfo> | undefined {
        return this.getFingerInfos_serialize()
    }
    private setFingerInfos(fingerInfos: Array<FingerInfo> | undefined): void {
        const fingerInfos_casted = fingerInfos as (Array<FingerInfo> | undefined)
        this.setFingerInfos_serialize(fingerInfos_casted)
        return
    }
    private getOffsetX(): double {
        return this.getOffsetX_serialize()
    }
    private setOffsetX(offsetX: double): void {
        const offsetX_casted = offsetX as (double)
        this.setOffsetX_serialize(offsetX_casted)
        return
    }
    private getOffsetY(): double {
        return this.getOffsetY_serialize()
    }
    private setOffsetY(offsetY: double): void {
        const offsetY_casted = offsetY as (double)
        this.setOffsetY_serialize(offsetY_casted)
        return
    }
    private getAngle(): double {
        return this.getAngle_serialize()
    }
    private setAngle(angle: double): void {
        const angle_casted = angle as (double)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getSpeed(): double {
        return this.getSpeed_serialize()
    }
    private setSpeed(speed: double): void {
        const speed_casted = speed as (double)
        this.setSpeed_serialize(speed_casted)
        return
    }
    private getScale(): double {
        return this.getScale_serialize()
    }
    private setScale(scale: double): void {
        const scale_casted = scale as (double)
        this.setScale_serialize(scale_casted)
        return
    }
    private getPinchCenterX(): double {
        return this.getPinchCenterX_serialize()
    }
    private setPinchCenterX(pinchCenterX: double): void {
        const pinchCenterX_casted = pinchCenterX as (double)
        this.setPinchCenterX_serialize(pinchCenterX_casted)
        return
    }
    private getPinchCenterY(): double {
        return this.getPinchCenterY_serialize()
    }
    private setPinchCenterY(pinchCenterY: double): void {
        const pinchCenterY_casted = pinchCenterY as (double)
        this.setPinchCenterY_serialize(pinchCenterY_casted)
        return
    }
    private getVelocityX(): double {
        return this.getVelocityX_serialize()
    }
    private setVelocityX(velocityX: double): void {
        const velocityX_casted = velocityX as (double)
        this.setVelocityX_serialize(velocityX_casted)
        return
    }
    private getVelocityY(): double {
        return this.getVelocityY_serialize()
    }
    private setVelocityY(velocityY: double): void {
        const velocityY_casted = velocityY as (double)
        this.setVelocityY_serialize(velocityY_casted)
        return
    }
    private getVelocity(): double {
        return this.getVelocity_serialize()
    }
    private setVelocity(velocity: double): void {
        const velocity_casted = velocity as (double)
        this.setVelocity_serialize(velocity_casted)
        return
    }
    private getTapLocation(): EventLocationInfo | undefined {
        return this.getTapLocation_serialize()
    }
    private setTapLocation(tapLocation: EventLocationInfo | undefined): void {
        const tapLocation_casted = tapLocation as (EventLocationInfo | undefined)
        this.setTapLocation_serialize(tapLocation_casted)
        return
    }
    private getRepeat_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getRepeat(this.peer!.ptr)
        return retval
    }
    private setRepeat_serialize(repeat: boolean): void {
        ArkUIGeneratedNativeModule._GestureEvent_setRepeat(this.peer!.ptr, repeat ? true : false)
    }
    private getFingerList_serialize(): Array<FingerInfo> {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getFingerList(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = FingerInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fingerList.length).toInt())
        for (let fingerListCounterI = 0; fingerListCounterI < fingerList.length; fingerListCounterI++) {
            const fingerListTmpElement : FingerInfo = fingerList[fingerListCounterI]
            FingerInfo_serializer.write(thisSerializer, fingerListTmpElement)
        }
        ArkUIGeneratedNativeModule._GestureEvent_setFingerList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFingerInfos_serialize(): Array<FingerInfo> | undefined {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getFingerInfos(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<FingerInfo> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<FingerInfo> = new Array<FingerInfo>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = FingerInfo_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<FingerInfo> | undefined = buffer
        return returnResult
    }
    private setFingerInfos_serialize(fingerInfos: Array<FingerInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fingerInfos !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fingerInfosTmpValue  = fingerInfos!
            thisSerializer.writeInt32((fingerInfosTmpValue.length).toInt())
            for (let fingerInfosTmpValueCounterI = 0; fingerInfosTmpValueCounterI < fingerInfosTmpValue.length; fingerInfosTmpValueCounterI++) {
                const fingerInfosTmpValueTmpElement : FingerInfo = fingerInfosTmpValue[fingerInfosTmpValueCounterI]
                FingerInfo_serializer.write(thisSerializer, fingerInfosTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GestureEvent_setFingerInfos(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOffsetX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getOffsetX(this.peer!.ptr)
        return retval
    }
    private setOffsetX_serialize(offsetX: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setOffsetX(this.peer!.ptr, offsetX)
    }
    private getOffsetY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getOffsetY(this.peer!.ptr)
        return retval
    }
    private setOffsetY_serialize(offsetY: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setOffsetY(this.peer!.ptr, offsetY)
    }
    private getAngle_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setAngle(this.peer!.ptr, angle)
    }
    private getSpeed_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getSpeed(this.peer!.ptr)
        return retval
    }
    private setSpeed_serialize(speed: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setSpeed(this.peer!.ptr, speed)
    }
    private getScale_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getScale(this.peer!.ptr)
        return retval
    }
    private setScale_serialize(scale: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setScale(this.peer!.ptr, scale)
    }
    private getPinchCenterX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getPinchCenterX(this.peer!.ptr)
        return retval
    }
    private setPinchCenterX_serialize(pinchCenterX: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setPinchCenterX(this.peer!.ptr, pinchCenterX)
    }
    private getPinchCenterY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getPinchCenterY(this.peer!.ptr)
        return retval
    }
    private setPinchCenterY_serialize(pinchCenterY: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setPinchCenterY(this.peer!.ptr, pinchCenterY)
    }
    private getVelocityX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private setVelocityX_serialize(velocityX: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocityX(this.peer!.ptr, velocityX)
    }
    private getVelocityY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private setVelocityY_serialize(velocityY: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocityY(this.peer!.ptr, velocityY)
    }
    private getVelocity_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private setVelocity_serialize(velocity: double): void {
        ArkUIGeneratedNativeModule._GestureEvent_setVelocity(this.peer!.ptr, velocity)
    }
    private getTapLocation_serialize(): EventLocationInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getTapLocation(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EventLocationInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EventLocationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : EventLocationInfo | undefined = buffer
        return returnResult
    }
    private setTapLocation_serialize(tapLocation: EventLocationInfo | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (tapLocation !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const tapLocationTmpValue  = tapLocation!
            EventLocationInfo_serializer.write(thisSerializer, tapLocationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GestureEvent_setTapLocation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class LongPressRecognizerInternal {
    public static fromPtr(ptr: KPointer): LongPressRecognizer {
        return new LongPressRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class LongPressRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, LongPressRecognizer.construct())
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
    public getDuration(): int32 {
        return this.getDuration_serialize()
    }
    private isRepeat_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_isRepeat(this.peer!.ptr)
        return retval
    }
    private getDuration_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_getDuration(this.peer!.ptr)
        return retval
    }
}
export class PanRecognizerInternal {
    public static fromPtr(ptr: KPointer): PanRecognizer {
        return new PanRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class PanRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PanRecognizer.construct())
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
        return new PinchRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class PinchRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PinchRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchRecognizer_getFinalizer()
    }
    public getDistance(): double {
        return this.getDistance_serialize()
    }
    private getDistance_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PinchRecognizer_getDistance(this.peer!.ptr)
        return retval
    }
}
export class RotationRecognizerInternal {
    public static fromPtr(ptr: KPointer): RotationRecognizer {
        return new RotationRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class RotationRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, RotationRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationRecognizer_getFinalizer()
    }
    public getAngle(): double {
        return this.getAngle_serialize()
    }
    private getAngle_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._RotationRecognizer_getAngle(this.peer!.ptr)
        return retval
    }
}
export class ScrollableTargetInfoInternal {
    public static fromPtr(ptr: KPointer): ScrollableTargetInfo {
        return new ScrollableTargetInfo(MaterializedBaseTag.NOP, ptr)
    }
}
export class ScrollableTargetInfo extends EventTargetInfo implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ScrollableTargetInfo.construct())
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
export class SwipeRecognizerInternal {
    public static fromPtr(ptr: KPointer): SwipeRecognizer {
        return new SwipeRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class SwipeRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, SwipeRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeRecognizer_getFinalizer()
    }
    public getVelocityThreshold(): double {
        return this.getVelocityThreshold_serialize()
    }
    public getDirection(): SwipeDirection {
        return this.getDirection_serialize()
    }
    private getVelocityThreshold_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_getVelocityThreshold(this.peer!.ptr)
        return retval
    }
    private getDirection_serialize(): SwipeDirection {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_getDirection(this.peer!.ptr)
        return SwipeDirection.fromValue(retval)
    }
}
export class TapRecognizerInternal {
    public static fromPtr(ptr: KPointer): TapRecognizer {
        return new TapRecognizer(MaterializedBaseTag.NOP, ptr)
    }
}
export class TapRecognizer extends GestureRecognizer implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TapRecognizer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapRecognizer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapRecognizer_getFinalizer()
    }
    public getTapCount(): int32 {
        return this.getTapCount_serialize()
    }
    private getTapCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._TapRecognizer_getTapCount(this.peer!.ptr)
        return retval
    }
}
export interface LongPressGestureEvent extends BaseGestureEvent {
    repeat: boolean
}
export class LongPressGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,LongPressGestureEvent {
    public repeat: boolean
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.repeat = this.getRepeat()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, LongPressGestureEventInternal.construct())
        this.repeat = this.getRepeat()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LongPressGestureEventInternal {
        return new LongPressGestureEventInternal(MaterializedBaseTag.NOP, ptr)
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
        ArkUIGeneratedNativeModule._LongPressGestureEvent_setRepeat(this.peer!.ptr, repeat ? true : false)
    }
}
export interface PanGestureEvent extends BaseGestureEvent {
    offsetX: double
    offsetY: double
    velocityX: double
    velocityY: double
    velocity: double
}
export class PanGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,PanGestureEvent {
    public offsetX: double
    public offsetY: double
    public velocityX: double
    public velocityY: double
    public velocity: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.offsetX = this.getOffsetX()
        this.offsetY = this.getOffsetY()
        this.velocityX = this.getVelocityX()
        this.velocityY = this.getVelocityY()
        this.velocity = this.getVelocity()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PanGestureEventInternal.construct())
        this.offsetX = this.getOffsetX()
        this.offsetY = this.getOffsetY()
        this.velocityX = this.getVelocityX()
        this.velocityY = this.getVelocityY()
        this.velocity = this.getVelocity()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PanGestureEventInternal {
        return new PanGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getOffsetX(): double {
        return this.getOffsetX_serialize()
    }
    private setOffsetX(offsetX: double): void {
        const offsetX_casted = offsetX as (double)
        this.setOffsetX_serialize(offsetX_casted)
        return
    }
    private getOffsetY(): double {
        return this.getOffsetY_serialize()
    }
    private setOffsetY(offsetY: double): void {
        const offsetY_casted = offsetY as (double)
        this.setOffsetY_serialize(offsetY_casted)
        return
    }
    private getVelocityX(): double {
        return this.getVelocityX_serialize()
    }
    private setVelocityX(velocityX: double): void {
        const velocityX_casted = velocityX as (double)
        this.setVelocityX_serialize(velocityX_casted)
        return
    }
    private getVelocityY(): double {
        return this.getVelocityY_serialize()
    }
    private setVelocityY(velocityY: double): void {
        const velocityY_casted = velocityY as (double)
        this.setVelocityY_serialize(velocityY_casted)
        return
    }
    private getVelocity(): double {
        return this.getVelocity_serialize()
    }
    private setVelocity(velocity: double): void {
        const velocity_casted = velocity as (double)
        this.setVelocity_serialize(velocity_casted)
        return
    }
    private getOffsetX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetX(this.peer!.ptr)
        return retval
    }
    private setOffsetX_serialize(offsetX: double): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetX(this.peer!.ptr, offsetX)
    }
    private getOffsetY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetY(this.peer!.ptr)
        return retval
    }
    private setOffsetY_serialize(offsetY: double): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetY(this.peer!.ptr, offsetY)
    }
    private getVelocityX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private setVelocityX_serialize(velocityX: double): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityX(this.peer!.ptr, velocityX)
    }
    private getVelocityY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private setVelocityY_serialize(velocityY: double): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityY(this.peer!.ptr, velocityY)
    }
    private getVelocity_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private setVelocity_serialize(velocity: double): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocity(this.peer!.ptr, velocity)
    }
}
export interface PinchGestureEvent extends BaseGestureEvent {
    scale: double
    pinchCenterX: double
    pinchCenterY: double
}
export class PinchGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,PinchGestureEvent {
    public scale: double
    public pinchCenterX: double
    public pinchCenterY: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.scale = this.getScale()
        this.pinchCenterX = this.getPinchCenterX()
        this.pinchCenterY = this.getPinchCenterY()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PinchGestureEventInternal.construct())
        this.scale = this.getScale()
        this.pinchCenterX = this.getPinchCenterX()
        this.pinchCenterY = this.getPinchCenterY()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PinchGestureEventInternal {
        return new PinchGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getScale(): double {
        return this.getScale_serialize()
    }
    private setScale(scale: double): void {
        const scale_casted = scale as (double)
        this.setScale_serialize(scale_casted)
        return
    }
    private getPinchCenterX(): double {
        return this.getPinchCenterX_serialize()
    }
    private setPinchCenterX(pinchCenterX: double): void {
        const pinchCenterX_casted = pinchCenterX as (double)
        this.setPinchCenterX_serialize(pinchCenterX_casted)
        return
    }
    private getPinchCenterY(): double {
        return this.getPinchCenterY_serialize()
    }
    private setPinchCenterY(pinchCenterY: double): void {
        const pinchCenterY_casted = pinchCenterY as (double)
        this.setPinchCenterY_serialize(pinchCenterY_casted)
        return
    }
    private getScale_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getScale(this.peer!.ptr)
        return retval
    }
    private setScale_serialize(scale: double): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setScale(this.peer!.ptr, scale)
    }
    private getPinchCenterX_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterX(this.peer!.ptr)
        return retval
    }
    private setPinchCenterX_serialize(pinchCenterX: double): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterX(this.peer!.ptr, pinchCenterX)
    }
    private getPinchCenterY_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterY(this.peer!.ptr)
        return retval
    }
    private setPinchCenterY_serialize(pinchCenterY: double): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterY(this.peer!.ptr, pinchCenterY)
    }
}
export interface RotationGestureEvent extends BaseGestureEvent {
    angle: double
}
export class RotationGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,RotationGestureEvent {
    public angle: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.angle = this.getAngle()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, RotationGestureEventInternal.construct())
        this.angle = this.getAngle()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): RotationGestureEventInternal {
        return new RotationGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getAngle(): double {
        return this.getAngle_serialize()
    }
    private setAngle(angle: double): void {
        const angle_casted = angle as (double)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getAngle_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: double): void {
        ArkUIGeneratedNativeModule._RotationGestureEvent_setAngle(this.peer!.ptr, angle)
    }
}
export interface SwipeGestureEvent extends BaseGestureEvent {
    angle: double
    speed: double
}
export class SwipeGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,SwipeGestureEvent {
    public angle: double
    public speed: double
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.angle = this.getAngle()
        this.speed = this.getSpeed()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, SwipeGestureEventInternal.construct())
        this.angle = this.getAngle()
        this.speed = this.getSpeed()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): SwipeGestureEventInternal {
        return new SwipeGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getAngle(): double {
        return this.getAngle_serialize()
    }
    private setAngle(angle: double): void {
        const angle_casted = angle as (double)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getSpeed(): double {
        return this.getSpeed_serialize()
    }
    private setSpeed(speed: double): void {
        const speed_casted = speed as (double)
        this.setSpeed_serialize(speed_casted)
        return
    }
    private getAngle_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: double): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setAngle(this.peer!.ptr, angle)
    }
    private getSpeed_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_getSpeed(this.peer!.ptr)
        return retval
    }
    private setSpeed_serialize(speed: double): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setSpeed(this.peer!.ptr, speed)
    }
}
export interface TapGestureEvent extends BaseGestureEvent {
    tapLocation?: EventLocationInfo | undefined
}
export class TapGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,TapGestureEvent {
    public tapLocation?: EventLocationInfo | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.tapLocation = this.getTapLocation()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TapGestureEventInternal.construct())
        this.tapLocation = this.getTapLocation()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapGestureEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureEventInternal {
        return new TapGestureEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    private getTapLocation(): EventLocationInfo | undefined {
        return this.getTapLocation_serialize()
    }
    private setTapLocation(tapLocation: EventLocationInfo | undefined): void {
        const tapLocation_casted = tapLocation as (EventLocationInfo | undefined)
        this.setTapLocation_serialize(tapLocation_casted)
        return
    }
    private getTapLocation_serialize(): EventLocationInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._TapGestureEvent_getTapLocation(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : EventLocationInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = EventLocationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : EventLocationInfo | undefined = buffer
        return returnResult
    }
    private setTapLocation_serialize(tapLocation: EventLocationInfo | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (tapLocation !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const tapLocationTmpValue  = tapLocation!
            EventLocationInfo_serializer.write(thisSerializer, tapLocationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TapGestureEvent_setTapLocation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

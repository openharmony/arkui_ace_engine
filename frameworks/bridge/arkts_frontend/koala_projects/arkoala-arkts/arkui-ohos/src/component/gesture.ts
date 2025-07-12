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

import { BaseEvent, BaseEventInternal, EventTarget, SourceType, SourceTool } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { Callback_Void } from "./abilityComponent"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface BaseGestureEvent {
    fingerList: Array<FingerInfo>
}
export class BaseGestureEventInternal extends BaseEventInternal implements MaterializedBase,BaseGestureEvent {
    get fingerList(): Array<FingerInfo> {
        throw new Error("Not implemented")
    }
    set fingerList(fingerList: Array<FingerInfo>) {
        this.setFingerList(fingerList)
    }
    static ctor_basegestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = BaseGestureEventInternal.ctor_basegestureevent()
        this.peer = new Finalizable(ctorPtr, BaseGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseGestureEvent_getFinalizer()
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readFingerInfo()
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(fingerList.length as int32)
        for (let i = 0; i < fingerList.length; i++) {
            const fingerList_element : FingerInfo = fingerList[i]
            thisSerializer.writeFingerInfo(fingerList_element)
        }
        ArkUIGeneratedNativeModule._BaseGestureEvent_setFingerList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): BaseGestureEventInternal {
        const obj : BaseGestureEventInternal = new BaseGestureEventInternal()
        obj.peer = new Finalizable(ptr, BaseGestureEventInternal.getFinalizer())
        return obj
    }
}
export interface TapGestureEvent {
}
export class TapGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,TapGestureEvent {
    static ctor_tapgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TapGestureEventInternal.ctor_tapgestureevent()
        this.peer = new Finalizable(ctorPtr, TapGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureEventInternal {
        const obj : TapGestureEventInternal = new TapGestureEventInternal()
        obj.peer = new Finalizable(ptr, TapGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_longpressgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = LongPressGestureEventInternal.ctor_longpressgestureevent()
        this.peer = new Finalizable(ctorPtr, LongPressGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): LongPressGestureEventInternal {
        const obj : LongPressGestureEventInternal = new LongPressGestureEventInternal()
        obj.peer = new Finalizable(ptr, LongPressGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_pangestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PanGestureEventInternal.ctor_pangestureevent()
        this.peer = new Finalizable(ctorPtr, PanGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): PanGestureEventInternal {
        const obj : PanGestureEventInternal = new PanGestureEventInternal()
        obj.peer = new Finalizable(ptr, PanGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_pinchgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PinchGestureEventInternal.ctor_pinchgestureevent()
        this.peer = new Finalizable(ctorPtr, PinchGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): PinchGestureEventInternal {
        const obj : PinchGestureEventInternal = new PinchGestureEventInternal()
        obj.peer = new Finalizable(ptr, PinchGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_rotationgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RotationGestureEventInternal.ctor_rotationgestureevent()
        this.peer = new Finalizable(ctorPtr, RotationGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): RotationGestureEventInternal {
        const obj : RotationGestureEventInternal = new RotationGestureEventInternal()
        obj.peer = new Finalizable(ptr, RotationGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_swipegestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SwipeGestureEventInternal.ctor_swipegestureevent()
        this.peer = new Finalizable(ctorPtr, SwipeGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): SwipeGestureEventInternal {
        const obj : SwipeGestureEventInternal = new SwipeGestureEventInternal()
        obj.peer = new Finalizable(ptr, SwipeGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_gestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = GestureEventInternal.ctor_gestureevent()
        this.peer = new Finalizable(ctorPtr, GestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureEvent_getFinalizer()
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<FingerInfo> = new Array<FingerInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readFingerInfo()
        }
        const returnResult : Array<FingerInfo> = buffer
        return returnResult
    }
    private setFingerList_serialize(fingerList: Array<FingerInfo>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(fingerList.length as int32)
        for (let i = 0; i < fingerList.length; i++) {
            const fingerList_element : FingerInfo = fingerList[i]
            thisSerializer.writeFingerInfo(fingerList_element)
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
    public static fromPtr(ptr: KPointer): GestureEventInternal {
        const obj : GestureEventInternal = new GestureEventInternal()
        obj.peer = new Finalizable(ptr, GestureEventInternal.getFinalizer())
        return obj
    }
}
export class ScrollableTargetInfoInternal {
    public static fromPtr(ptr: KPointer): ScrollableTargetInfo {
        const obj : ScrollableTargetInfo = new ScrollableTargetInfo()
        obj.peer = new Finalizable(ptr, ScrollableTargetInfo.getFinalizer())
        return obj
    }
}
export class ScrollableTargetInfo extends EventTargetInfo implements MaterializedBase {
    static ctor_scrollabletargetinfo(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScrollableTargetInfo_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = ScrollableTargetInfo.ctor_scrollabletargetinfo()
        this.peer = new Finalizable(ctorPtr, ScrollableTargetInfo.getFinalizer())
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
export class TapRecognizerInternal {
    public static fromPtr(ptr: KPointer): TapRecognizer {
        const obj : TapRecognizer = new TapRecognizer()
        obj.peer = new Finalizable(ptr, TapRecognizer.getFinalizer())
        return obj
    }
}
export class TapRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_taprecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TapRecognizer.ctor_taprecognizer()
        this.peer = new Finalizable(ctorPtr, TapRecognizer.getFinalizer())
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
export class LongPressRecognizerInternal {
    public static fromPtr(ptr: KPointer): LongPressRecognizer {
        const obj : LongPressRecognizer = new LongPressRecognizer()
        obj.peer = new Finalizable(ptr, LongPressRecognizer.getFinalizer())
        return obj
    }
}
export class LongPressRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_longpressrecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = LongPressRecognizer.ctor_longpressrecognizer()
        this.peer = new Finalizable(ctorPtr, LongPressRecognizer.getFinalizer())
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
export class SwipeRecognizerInternal {
    public static fromPtr(ptr: KPointer): SwipeRecognizer {
        const obj : SwipeRecognizer = new SwipeRecognizer()
        obj.peer = new Finalizable(ptr, SwipeRecognizer.getFinalizer())
        return obj
    }
}
export class SwipeRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_swiperecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SwipeRecognizer.ctor_swiperecognizer()
        this.peer = new Finalizable(ctorPtr, SwipeRecognizer.getFinalizer())
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
export class PinchRecognizerInternal {
    public static fromPtr(ptr: KPointer): PinchRecognizer {
        const obj : PinchRecognizer = new PinchRecognizer()
        obj.peer = new Finalizable(ptr, PinchRecognizer.getFinalizer())
        return obj
    }
}
export class PinchRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_pinchrecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PinchRecognizer.ctor_pinchrecognizer()
        this.peer = new Finalizable(ctorPtr, PinchRecognizer.getFinalizer())
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
export class RotationRecognizerInternal {
    public static fromPtr(ptr: KPointer): RotationRecognizer {
        const obj : RotationRecognizer = new RotationRecognizer()
        obj.peer = new Finalizable(ptr, RotationRecognizer.getFinalizer())
        return obj
    }
}
export class RotationRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_rotationrecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RotationRecognizer.ctor_rotationrecognizer()
        this.peer = new Finalizable(ctorPtr, RotationRecognizer.getFinalizer())
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
export class PanRecognizerInternal {
    public static fromPtr(ptr: KPointer): PanRecognizer {
        const obj : PanRecognizer = new PanRecognizer()
        obj.peer = new Finalizable(ptr, PanRecognizer.getFinalizer())
        return obj
    }
}
export class PanRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_panrecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PanRecognizer.ctor_panrecognizer()
        this.peer = new Finalizable(ctorPtr, PanRecognizer.getFinalizer())
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
export interface TapGestureEvent {
}
export class TapGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,TapGestureEvent {
    static ctor_tapgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TapGestureEventInternal.ctor_tapgestureevent()
        this.peer = new Finalizable(ctorPtr, TapGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureEventInternal {
        const obj : TapGestureEventInternal = new TapGestureEventInternal()
        obj.peer = new Finalizable(ptr, TapGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_longpressgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = LongPressGestureEventInternal.ctor_longpressgestureevent()
        this.peer = new Finalizable(ctorPtr, LongPressGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): LongPressGestureEventInternal {
        const obj : LongPressGestureEventInternal = new LongPressGestureEventInternal()
        obj.peer = new Finalizable(ptr, LongPressGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_pangestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PanGestureEventInternal.ctor_pangestureevent()
        this.peer = new Finalizable(ctorPtr, PanGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): PanGestureEventInternal {
        const obj : PanGestureEventInternal = new PanGestureEventInternal()
        obj.peer = new Finalizable(ptr, PanGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_pinchgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PinchGestureEventInternal.ctor_pinchgestureevent()
        this.peer = new Finalizable(ctorPtr, PinchGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): PinchGestureEventInternal {
        const obj : PinchGestureEventInternal = new PinchGestureEventInternal()
        obj.peer = new Finalizable(ptr, PinchGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_rotationgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RotationGestureEventInternal.ctor_rotationgestureevent()
        this.peer = new Finalizable(ctorPtr, RotationGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): RotationGestureEventInternal {
        const obj : RotationGestureEventInternal = new RotationGestureEventInternal()
        obj.peer = new Finalizable(ptr, RotationGestureEventInternal.getFinalizer())
        return obj
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
    static ctor_swipegestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SwipeGestureEventInternal.ctor_swipegestureevent()
        this.peer = new Finalizable(ctorPtr, SwipeGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureEvent_getFinalizer()
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
    public static fromPtr(ptr: KPointer): SwipeGestureEventInternal {
        const obj : SwipeGestureEventInternal = new SwipeGestureEventInternal()
        obj.peer = new Finalizable(ptr, SwipeGestureEventInternal.getFinalizer())
        return obj
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

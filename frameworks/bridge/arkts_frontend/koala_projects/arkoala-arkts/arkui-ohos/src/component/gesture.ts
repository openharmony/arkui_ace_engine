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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        throw new Error("Not implemented")
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
export interface TapGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): TapGestureInterface
}
export class TapGestureInterfaceInternal implements MaterializedBase,GestureInterface<TapGestureInterface>,TapGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_tapgestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TapGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TapGestureInterfaceInternal.ctor_tapgestureinterface()
        this.peer = new Finalizable(ctorPtr, TapGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureInterface_getFinalizer()
    }
    public onAction(event: ((event: GestureEvent) => void)): TapGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): TapGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._TapGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TapGestureInterface = TapGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): TapGestureInterfaceInternal {
        const obj : TapGestureInterfaceInternal = new TapGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, TapGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface LongPressGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionCancel(event: (() => void)): LongPressGestureInterface
}
export class LongPressGestureInterfaceInternal implements MaterializedBase,GestureInterface<LongPressGestureInterface>,LongPressGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_longpressgestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = LongPressGestureInterfaceInternal.ctor_longpressgestureinterface()
        this.peer = new Finalizable(ctorPtr, LongPressGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureInterface_getFinalizer()
    }
    public onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): LongPressGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): LongPressGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): LongPressGestureInterfaceInternal {
        const obj : LongPressGestureInterfaceInternal = new LongPressGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, LongPressGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export class PanGestureOptionsInternal {
    public static fromPtr(ptr: KPointer): PanGestureOptions {
        const obj : PanGestureOptions = new PanGestureOptions(undefined)
        obj.peer = new Finalizable(ptr, PanGestureOptions.getFinalizer())
        return obj
    }
}
export class PanGestureOptions implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pangestureoptions(value?: Literal_Number_distance_fingers_PanDirection_direction): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_fingers  = value_value.fingers
            let value_value_fingers_type : int32 = RuntimeType.UNDEFINED
            value_value_fingers_type = runtimeType(value_value_fingers)
            thisSerializer.writeInt8(value_value_fingers_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_fingers_type)) {
                const value_value_fingers_value  = value_value_fingers!
                thisSerializer.writeNumber(value_value_fingers_value)
            }
            const value_value_direction  = value_value.direction
            let value_value_direction_type : int32 = RuntimeType.UNDEFINED
            value_value_direction_type = runtimeType(value_value_direction)
            thisSerializer.writeInt8(value_value_direction_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_direction_type)) {
                const value_value_direction_value  = (value_value_direction as PanDirection)
                thisSerializer.writeInt32(value_value_direction_value.valueOf())
            }
            const value_value_distance  = value_value.distance
            let value_value_distance_type : int32 = RuntimeType.UNDEFINED
            value_value_distance_type = runtimeType(value_value_distance)
            thisSerializer.writeInt8(value_value_distance_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_distance_type)) {
                const value_value_distance_value  = value_value_distance!
                thisSerializer.writeNumber(value_value_distance_value)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_distance_fingers_PanDirection_direction) {
        const ctorPtr : KPointer = PanGestureOptions.ctor_pangestureoptions((value)!)
        this.peer = new Finalizable(ctorPtr, PanGestureOptions.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureOptions_getFinalizer()
    }
    public setDirection(value: PanDirection): undefined {
        const value_casted = value as (PanDirection)
        return this.setDirection_serialize(value_casted)
    }
    public setDistance(value: number): undefined {
        const value_casted = value as (number)
        return this.setDistance_serialize(value_casted)
    }
    public setFingers(value: number): undefined {
        const value_casted = value as (number)
        return this.setFingers_serialize(value_casted)
    }
    public getDirection(): PanDirection {
        return this.getDirection_serialize()
    }
    private setDirection_serialize(value: PanDirection): undefined {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_setDirection(this.peer!.ptr, value.valueOf())
        return retval
    }
    private setDistance_serialize(value: number): undefined {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_setDistance(this.peer!.ptr, value)
        return retval
    }
    private setFingers_serialize(value: number): undefined {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_setFingers(this.peer!.ptr, value)
        return retval
    }
    private getDirection_serialize(): PanDirection {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export interface PanGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionCancel(event: (() => void)): PanGestureInterface
}
export class PanGestureInterfaceInternal implements MaterializedBase,GestureInterface<PanGestureInterface>,PanGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pangestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PanGestureInterfaceInternal.ctor_pangestureinterface()
        this.peer = new Finalizable(ctorPtr, PanGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureInterface_getFinalizer()
    }
    public onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionStart_serialize(event_casted)
    }
    public onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionUpdate_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): PanGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): PanGestureInterfaceInternal {
        const obj : PanGestureInterfaceInternal = new PanGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, PanGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface SwipeGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): SwipeGestureInterface
}
export class SwipeGestureInterfaceInternal implements MaterializedBase,GestureInterface<SwipeGestureInterface>,SwipeGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_swipegestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwipeGestureInterfaceInternal.ctor_swipegestureinterface()
        this.peer = new Finalizable(ctorPtr, SwipeGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureInterface_getFinalizer()
    }
    public onAction(event: ((event: GestureEvent) => void)): SwipeGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): SwipeGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SwipeGestureInterface = SwipeGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): SwipeGestureInterfaceInternal {
        const obj : SwipeGestureInterfaceInternal = new SwipeGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, SwipeGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface PinchGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionCancel(event: (() => void)): PinchGestureInterface
}
export class PinchGestureInterfaceInternal implements MaterializedBase,GestureInterface<PinchGestureInterface>,PinchGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pinchgestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PinchGestureInterfaceInternal.ctor_pinchgestureinterface()
        this.peer = new Finalizable(ctorPtr, PinchGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureInterface_getFinalizer()
    }
    public onActionStart(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionStart_serialize(event_casted)
    }
    public onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionUpdate_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): PinchGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): PinchGestureInterfaceInternal {
        const obj : PinchGestureInterfaceInternal = new PinchGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, PinchGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface RotationGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionCancel(event: (() => void)): RotationGestureInterface
}
export class RotationGestureInterfaceInternal implements MaterializedBase,GestureInterface<RotationGestureInterface>,RotationGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_rotationgestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = RotationGestureInterfaceInternal.ctor_rotationgestureinterface()
        this.peer = new Finalizable(ctorPtr, RotationGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureInterface_getFinalizer()
    }
    public onActionStart(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionStart_serialize(event_casted)
    }
    public onActionUpdate(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionUpdate_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): RotationGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): RotationGestureInterfaceInternal {
        const obj : RotationGestureInterfaceInternal = new RotationGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, RotationGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface GestureGroupInterface {
    onCancel(event: (() => void)): GestureGroupInterface
}
export class GestureGroupInterfaceInternal implements MaterializedBase,GestureGroupInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturegroupinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureGroupInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = GestureGroupInterfaceInternal.ctor_gesturegroupinterface()
        this.peer = new Finalizable(ctorPtr, GestureGroupInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureGroupInterface_getFinalizer()
    }
    public onCancel(event: (() => void)): GestureGroupInterface {
        const event_casted = event as ((() => void))
        return this.onCancel_serialize(event_casted)
    }
    private onCancel_serialize(event: (() => void)): GestureGroupInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._GestureGroupInterface_onCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : GestureGroupInterface = GestureGroupInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): GestureGroupInterfaceInternal {
        const obj : GestureGroupInterfaceInternal = new GestureGroupInterfaceInternal()
        obj.peer = new Finalizable(ptr, GestureGroupInterfaceInternal.getFinalizer())
        return obj
    }
}

export class EventTargetInfoInternal {
    public static fromPtr(ptr: KPointer): EventTargetInfo {
        const obj : EventTargetInfo = new EventTargetInfo()
        obj.peer = new Finalizable(ptr, EventTargetInfo.getFinalizer())
        return obj
    }
}
export class EventTargetInfo implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_eventtargetinfo(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._EventTargetInfo_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = EventTargetInfo.ctor_eventtargetinfo()
        this.peer = new Finalizable(ctorPtr, EventTargetInfo.getFinalizer())
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
export class GestureRecognizerInternal {
    public static fromPtr(ptr: KPointer): GestureRecognizer {
        const obj : GestureRecognizer = new GestureRecognizer()
        obj.peer = new Finalizable(ptr, GestureRecognizer.getFinalizer())
        return obj
    }
}
export class GestureRecognizer implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturerecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = GestureRecognizer.ctor_gesturerecognizer()
        this.peer = new Finalizable(ctorPtr, GestureRecognizer.getFinalizer())
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
    private getTag_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getTag(this.peer!.ptr)
        return retval
    }
    private getType_serialize(): GestureControl.GestureType {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
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
        throw new Error("Object deserialization is not implemented.")
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
}
export type GestureType = TapGestureInterface | LongPressGestureInterface | PanGestureInterface | PinchGestureInterface | SwipeGestureInterface | RotationGestureInterface | GestureGroupInterface;
export interface GestureInterface<T> {
}
export interface TapGestureParameters {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
export type Callback_GestureEvent_Void = (event: GestureEvent) => void;
export interface Literal_Number_duration_fingers_Boolean_repeat {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface Literal_Number_distance_fingers_PanDirection_direction {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface Literal_Number_fingers_speed_SwipeDirection_direction {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export interface Literal_Number_distance_fingers {
    fingers?: number;
    distance?: number;
}
export interface Literal_Number_angle_fingers {
    fingers?: number;
    angle?: number;
}
export interface GestureHandler<T> {
}
export interface TapGestureHandlerOptions {
    count?: number;
    fingers?: number;
}
export interface TapGestureHandler extends GestureHandler<TapGestureHandler> {
}
export interface LongPressGestureHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface LongPressGestureHandler extends GestureHandler<LongPressGestureHandler> {
}
export interface PanGestureHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface PanGestureHandler extends GestureHandler<PanGestureHandler> {
}
export interface SwipeGestureHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export interface SwipeGestureHandler extends GestureHandler<SwipeGestureHandler> {
}
export interface PinchGestureHandlerOptions {
    fingers?: number;
    distance?: number;
}
export interface PinchGestureHandler extends GestureHandler<PinchGestureHandler> {
}
export interface RotationGestureHandlerOptions {
    fingers?: number;
    angle?: number;
}
export interface RotationGestureHandler extends GestureHandler<RotationGestureHandler> {
}
export interface GestureGroupGestureHandlerOptions {
    stub: string;
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

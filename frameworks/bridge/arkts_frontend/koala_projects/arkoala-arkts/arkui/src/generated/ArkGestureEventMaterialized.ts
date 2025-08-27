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

import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { FingerInfo } from "./ArkGestureInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
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

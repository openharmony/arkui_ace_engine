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

import { BaseGestureEvent, BaseGestureEventInternal } from "./ArkBaseGestureEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { FingerInfo } from "./ArkGestureInterfaces"
import { Area, Length, Position } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
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
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = PanGestureEventInternal.ctor_pangestureevent()
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
        this?.setOffsetX_serialize(offsetX_casted)
        return
    }
    private getOffsetY(): number {
        return this.getOffsetY_serialize()
    }
    private setOffsetY(offsetY: number): void {
        const offsetY_casted = offsetY as (number)
        this?.setOffsetY_serialize(offsetY_casted)
        return
    }
    private getVelocityX(): number {
        return this.getVelocityX_serialize()
    }
    private setVelocityX(velocityX: number): void {
        const velocityX_casted = velocityX as (number)
        this?.setVelocityX_serialize(velocityX_casted)
        return
    }
    private getVelocityY(): number {
        return this.getVelocityY_serialize()
    }
    private setVelocityY(velocityY: number): void {
        const velocityY_casted = velocityY as (number)
        this?.setVelocityY_serialize(velocityY_casted)
        return
    }
    private getVelocity(): number {
        return this.getVelocity_serialize()
    }
    private setVelocity(velocity: number): void {
        const velocity_casted = velocity as (number)
        this?.setVelocity_serialize(velocity_casted)
        return
    }
    private getOffsetX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetX(this.peer!.ptr)
        return retval
    }
    private setOffsetX_serialize(offsetX: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetX(this.peer!.ptr, offsetX)
    }
    private getOffsetY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_getOffsetY(this.peer!.ptr)
        return retval
    }
    private setOffsetY_serialize(offsetY: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setOffsetY(this.peer!.ptr, offsetY)
    }
    private getVelocityX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityX(this.peer!.ptr)
        return retval
    }
    private setVelocityX_serialize(velocityX: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityX(this.peer!.ptr, velocityX)
    }
    private getVelocityY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocityY(this.peer!.ptr)
        return retval
    }
    private setVelocityY_serialize(velocityY: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocityY(this.peer!.ptr, velocityY)
    }
    private getVelocity_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PanGestureEvent_getVelocity(this.peer!.ptr)
        return retval
    }
    private setVelocity_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._PanGestureEvent_setVelocity(this.peer!.ptr, velocity)
    }
    public static fromPtr(ptr: KPointer): PanGestureEventInternal {
        const obj: PanGestureEventInternal = new PanGestureEventInternal()
        obj.peer = new Finalizable(ptr, PanGestureEventInternal.getFinalizer())
        return obj
    }
}

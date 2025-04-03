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
        const retval = ArkUIGeneratedNativeModule._PinchGestureEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = PinchGestureEventInternal.ctor_pinchgestureevent()
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
        this?.setScale_serialize(scale_casted)
        return
    }
    private getPinchCenterX(): number {
        return this.getPinchCenterX_serialize()
    }
    private setPinchCenterX(pinchCenterX: number): void {
        const pinchCenterX_casted = pinchCenterX as (number)
        this?.setPinchCenterX_serialize(pinchCenterX_casted)
        return
    }
    private getPinchCenterY(): number {
        return this.getPinchCenterY_serialize()
    }
    private setPinchCenterY(pinchCenterY: number): void {
        const pinchCenterY_casted = pinchCenterY as (number)
        this?.setPinchCenterY_serialize(pinchCenterY_casted)
        return
    }
    private getScale_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PinchGestureEvent_getScale(this.peer!.ptr)
        return retval
    }
    private setScale_serialize(scale: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setScale(this.peer!.ptr, scale)
    }
    private getPinchCenterX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterX(this.peer!.ptr)
        return retval
    }
    private setPinchCenterX_serialize(pinchCenterX: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterX(this.peer!.ptr, pinchCenterX)
    }
    private getPinchCenterY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._PinchGestureEvent_getPinchCenterY(this.peer!.ptr)
        return retval
    }
    private setPinchCenterY_serialize(pinchCenterY: number): void {
        ArkUIGeneratedNativeModule._PinchGestureEvent_setPinchCenterY(this.peer!.ptr, pinchCenterY)
    }
    public static fromPtr(ptr: KPointer): PinchGestureEventInternal {
        const obj: PinchGestureEventInternal = new PinchGestureEventInternal()
        obj.peer = new Finalizable(ptr, PinchGestureEventInternal.getFinalizer())
        return obj
    }
}

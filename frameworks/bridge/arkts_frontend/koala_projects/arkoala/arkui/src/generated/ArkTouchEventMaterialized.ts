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
import { EventTarget, SourceType, SourceTool, TouchObject, HistoricalPoint } from "./ArkCommonInterfaces"
import { TouchType } from "./ArkEnumsInterfaces"
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
        const retval = ArkUIGeneratedNativeModule._TouchEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = TouchEventInternal.ctor_touchevent()
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
        this?.setType_serialize(type_casted)
        return
    }
    private getTouches(): Array<TouchObject> {
        return this.getTouches_serialize()
    }
    private setTouches(touches: Array<TouchObject>): void {
        const touches_casted = touches as (Array<TouchObject>)
        this?.setTouches_serialize(touches_casted)
        return
    }
    private getChangedTouches(): Array<TouchObject> {
        return this.getChangedTouches_serialize()
    }
    private setChangedTouches(changedTouches: Array<TouchObject>): void {
        const changedTouches_casted = changedTouches as (Array<TouchObject>)
        this?.setChangedTouches_serialize(changedTouches_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this?.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getPreventDefault(): (() => void) {
        return this.getPreventDefault_serialize()
    }
    private setPreventDefault(preventDefault: (() => void)): void {
        const preventDefault_casted = preventDefault as ((() => void))
        this?.setPreventDefault_serialize(preventDefault_casted)
        return
    }
    private getHistoricalPoints_serialize(): Array<HistoricalPoint> {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getHistoricalPoints(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<HistoricalPoint> = new Array<HistoricalPoint>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHistoricalPoint()
        }
        const returnResult: Array<HistoricalPoint> = buffer
        return returnResult
    }
    private getType_serialize(): TouchType {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: TouchType): void {
        ArkUIGeneratedNativeModule._TouchEvent_setType(this.peer!.ptr, type)
    }
    private getTouches_serialize(): Array<TouchObject> {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getTouches(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<TouchObject> = new Array<TouchObject>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTouchObject()
        }
        const returnResult: Array<TouchObject> = buffer
        return returnResult
    }
    private setTouches_serialize(touches: Array<TouchObject>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(touches.length)
        for (let i = 0; i < touches.length; i++) {
            const touches_element: TouchObject = touches[i]
            thisSerializer.writeTouchObject(touches_element)
        }
        ArkUIGeneratedNativeModule._TouchEvent_setTouches(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getChangedTouches_serialize(): Array<TouchObject> {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getChangedTouches(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<TouchObject> = new Array<TouchObject>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTouchObject()
        }
        const returnResult: Array<TouchObject> = buffer
        return returnResult
    }
    private setChangedTouches_serialize(changedTouches: Array<TouchObject>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(changedTouches.length)
        for (let i = 0; i < changedTouches.length; i++) {
            const changedTouches_element: TouchObject = changedTouches[i]
            thisSerializer.writeTouchObject(changedTouches_element)
        }
        ArkUIGeneratedNativeModule._TouchEvent_setChangedTouches(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._TouchEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPreventDefault_serialize(): (() => void) {
        const retval = ArkUIGeneratedNativeModule._TouchEvent_getPreventDefault(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setPreventDefault_serialize(preventDefault: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(preventDefault)
        ArkUIGeneratedNativeModule._TouchEvent_setPreventDefault(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): TouchEventInternal {
        const obj: TouchEventInternal = new TouchEventInternal()
        obj.peer = new Finalizable(ptr, TouchEventInternal.getFinalizer())
        return obj
    }
}

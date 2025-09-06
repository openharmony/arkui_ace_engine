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

import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
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
export interface BaseEvent {
    target: EventTarget
    timestamp: number
    source: SourceType
    axisHorizontal?: number
    axisVertical?: number
    axisPinch?: number
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
    get axisHorizontal(): number {
        return this.getAxisHorizontal()
    }
    set axisHorizontal(axisHorizontal: number) {
        const axisHorizontal_NonNull = (axisHorizontal as number)
        this.setAxisHorizontal(axisHorizontal_NonNull)
    }
    get axisVertical(): number {
        return this.getAxisVertical()
    }
    set axisVertical(axisVertical: number) {
        const axisVertical_NonNull = (axisVertical as number)
        this.setAxisVertical(axisVertical_NonNull)
    }
    get axisPinch(): number {
        return this.getAxisPinch()
    }
    set axisPinch(axisPinch: number) {
        const axisPinch_NonNull = (axisPinch as number)
        this.setAxisPinch(axisPinch_NonNull)
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
    get deviceId(): number {
        return this.getDeviceId()
    }
    set deviceId(deviceId: number) {
        const deviceId_NonNull = (deviceId as number)
        this.setDeviceId(deviceId_NonNull)
    }
    static ctor_baseevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = BaseEventInternal.ctor_baseevent()
        this.peer = new Finalizable(ctorPtr, BaseEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseEvent_getFinalizer()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private setTarget(target: EventTarget): void {
        const target_casted = target as (EventTarget)
        this?.setTarget_serialize(target_casted)
        return
    }
    private getTimestamp(): number {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: number): void {
        const timestamp_casted = timestamp as (number)
        this?.setTimestamp_serialize(timestamp_casted)
        return
    }
    private getSource(): SourceType {
        return this.getSource_serialize()
    }
    private setSource(source: SourceType): void {
        const source_casted = source as (SourceType)
        this?.setSource_serialize(source_casted)
        return
    }
    private getAxisHorizontal(): number {
        return this.getAxisHorizontal_serialize()
    }
    private setAxisHorizontal(axisHorizontal: number): void {
        const axisHorizontal_casted = axisHorizontal as (number)
        this?.setAxisHorizontal_serialize(axisHorizontal_casted)
        return
    }
    private getAxisVertical(): number {
        return this.getAxisVertical_serialize()
    }
    private setAxisVertical(axisVertical: number): void {
        const axisVertical_casted = axisVertical as (number)
        this?.setAxisVertical_serialize(axisVertical_casted)
        return
    }
    private getAxisPinch(): number {
        return this.getAxisPinch_serialize()
    }
    private setAxisPinch(axisPinch: number): void {
        const axisPinch_casted = axisPinch as (number)
        this?.setAxisPinch_serialize(axisPinch_casted)
        return
    }
    private getPressure(): number {
        return this.getPressure_serialize()
    }
    private setPressure(pressure: number): void {
        const pressure_casted = pressure as (number)
        this?.setPressure_serialize(pressure_casted)
        return
    }
    private getTiltX(): number {
        return this.getTiltX_serialize()
    }
    private setTiltX(tiltX: number): void {
        const tiltX_casted = tiltX as (number)
        this?.setTiltX_serialize(tiltX_casted)
        return
    }
    private getTiltY(): number {
        return this.getTiltY_serialize()
    }
    private setTiltY(tiltY: number): void {
        const tiltY_casted = tiltY as (number)
        this?.setTiltY_serialize(tiltY_casted)
        return
    }
    private getSourceTool(): SourceTool {
        return this.getSourceTool_serialize()
    }
    private setSourceTool(sourceTool: SourceTool): void {
        const sourceTool_casted = sourceTool as (SourceTool)
        this?.setSourceTool_serialize(sourceTool_casted)
        return
    }
    private getDeviceId(): number {
        return this.getDeviceId_serialize()
    }
    private setDeviceId(deviceId: number): void {
        const deviceId_casted = deviceId as (number)
        this?.setDeviceId_serialize(deviceId_casted)
        return
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length)
        for (let i = 0; i < keys.length; i++) {
            const keys_element: string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setTarget_serialize(target: EventTarget): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeEventTarget(target)
        ArkUIGeneratedNativeModule._BaseEvent_setTarget(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTimestamp_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTimestamp(this.peer!.ptr, timestamp)
    }
    private getSource_serialize(): SourceType {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getSource(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setSource_serialize(source: SourceType): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSource(this.peer!.ptr, source)
    }
    private getAxisHorizontal_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getAxisHorizontal(this.peer!.ptr)
        return retval
    }
    private setAxisHorizontal_serialize(axisHorizontal: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisHorizontal(this.peer!.ptr, axisHorizontal)
    }
    private getAxisVertical_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getAxisVertical(this.peer!.ptr)
        return retval
    }
    private setAxisVertical_serialize(axisVertical: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisVertical(this.peer!.ptr, axisVertical)
    }
    private getAxisPinch_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getAxisPinch(this.peer!.ptr)
        return retval
    }
    private setAxisPinch_serialize(axisPinch: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setAxisPinch(this.peer!.ptr, axisPinch)
    }
    private getPressure_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getPressure(this.peer!.ptr)
        return retval
    }
    private setPressure_serialize(pressure: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setPressure(this.peer!.ptr, pressure)
    }
    private getTiltX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getTiltX(this.peer!.ptr)
        return retval
    }
    private setTiltX_serialize(tiltX: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTiltX(this.peer!.ptr, tiltX)
    }
    private getTiltY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getTiltY(this.peer!.ptr)
        return retval
    }
    private setTiltY_serialize(tiltY: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setTiltY(this.peer!.ptr, tiltY)
    }
    private getSourceTool_serialize(): SourceTool {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getSourceTool(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setSourceTool_serialize(sourceTool: SourceTool): void {
        ArkUIGeneratedNativeModule._BaseEvent_setSourceTool(this.peer!.ptr, sourceTool)
    }
    private getDeviceId_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._BaseEvent_getDeviceId(this.peer!.ptr)
        return retval
    }
    private setDeviceId_serialize(deviceId: number): void {
        ArkUIGeneratedNativeModule._BaseEvent_setDeviceId(this.peer!.ptr, deviceId)
    }
    public static fromPtr(ptr: KPointer): BaseEventInternal {
        const obj: BaseEventInternal = new BaseEventInternal()
        obj.peer = new Finalizable(ptr, BaseEventInternal.getFinalizer())
        return obj
    }
}

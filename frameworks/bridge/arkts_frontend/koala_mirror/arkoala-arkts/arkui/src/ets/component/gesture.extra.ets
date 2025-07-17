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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Gesture_serializer, GestureMode, GestureType, Gesture, GestureInternal, LongPressGestureHandlerOptions, GestureEvent, GestureEventInternal, PanGestureOptions_serializer, PanGestureOptions, PanGestureOptionsInternal, PanGestureHandlerOptions, PinchGestureHandlerOptions, TapGestureParameters_serializer, TapGestureParameters, PanDirection } from "./gesture"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { SourceTool } from "./common"
export interface GestureGroupInterface {
    onCancel(event: (() => void)): GestureGroupInterface
}
export class GestureGroupInterfaceInternal implements MaterializedBase,GestureGroupInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, GestureGroupInterfaceInternal.getFinalizer())
    }
    constructor(mode: GestureMode, gesture: Array<GestureType>) {
        this(false, false, GestureGroupInterfaceInternal.construct(mode, gesture))
    }
    static construct(mode: GestureMode, gesture: Array<GestureType>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((gesture.length).toInt())
        for (let gesture_counter_i = 0; gesture_counter_i < gesture.length; gesture_counter_i++) {
            const gesture_element : GestureType = gesture[gesture_counter_i]
            let gesture_element_type : int32 = RuntimeType.UNDEFINED
            gesture_element_type = runtimeType(gesture_element)
            if (TypeChecker.isGesture(gesture_element)) {
                thisSerializer.writeInt8((0).toChar())
                const gesture_element_0  = gesture_element as Gesture
                Gesture_serializer.write(thisSerializer, gesture_element_0)
            }
            else if (RuntimeType.OBJECT == gesture_element_type) {
                thisSerializer.writeInt8((1).toChar())
                const gesture_element_1  = gesture_element as object
                thisSerializer.writeCustomObject("object", gesture_element_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._GestureGroupInterface_construct(TypeChecker.GestureMode_ToNumeric(mode), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureGroupInterface_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): GestureGroupInterfaceInternal {
        return new GestureGroupInterfaceInternal(false, false, ptr)
    }
    public onCancel(event: (() => void)): GestureGroupInterface {
        const event_casted = event as ((() => void))
        return this.onCancel_serialize(event_casted)
    }
    private onCancel_serialize(event: (() => void)): GestureGroupInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._GestureGroupInterface_onCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : GestureGroupInterface = GestureGroupInterfaceInternal.fromPtr(retval)
        return obj
    }
}
export interface LongPressGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionCancel(event: (() => void)): LongPressGestureInterface
    onActionCancel(event: ((event: GestureEvent) => void)): LongPressGestureInterface
}
export class LongPressGestureInterfaceInternal implements MaterializedBase,GestureInterface<LongPressGestureInterface>,LongPressGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LongPressGestureInterfaceInternal.getFinalizer())
    }
    constructor(value: LongPressGestureInterface_Invoke_Literal) {
        this(false, LongPressGestureInterfaceInternal.construct(value))
    }
    static construct(value: LongPressGestureInterface_Invoke_Literal): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        LongPressGestureInterface_Invoke_Literal_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureInterface_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LongPressGestureInterfaceInternal {
        return new LongPressGestureInterfaceInternal(false, ptr)
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
        return this.onActionCancel0_serialize(event_casted)
    }
    public onActionCancel(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionCancel1_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel0_serialize(event: (() => void)): LongPressGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
}
export interface PanGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionCancel(event: (() => void)): PanGestureInterface
    onActionCancel(event: ((event: GestureEvent) => void)): PanGestureInterface
}
export class PanGestureInterfaceInternal implements MaterializedBase,GestureInterface<PanGestureInterface>,PanGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PanGestureInterfaceInternal.getFinalizer())
    }
    constructor(value: PanGestureInterface_Invoke_Literal | PanGestureOptions) {
        this(false, PanGestureInterfaceInternal.construct(value))
    }
    static construct(value: PanGestureInterface_Invoke_Literal | PanGestureOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPanGestureInterface_Invoke_Literal(value, false, false, false)) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as PanGestureInterface_Invoke_Literal
            PanGestureInterface_Invoke_Literal_serializer.write(thisSerializer, value_0)
        }
        else if (TypeChecker.isPanGestureOptions(value)) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as PanGestureOptions
            PanGestureOptions_serializer.write(thisSerializer, value_1)
        }
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureInterface_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PanGestureInterfaceInternal {
        return new PanGestureInterfaceInternal(false, ptr)
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
        return this.onActionCancel0_serialize(event_casted)
    }
    public onActionCancel(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionCancel1_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel0_serialize(event: (() => void)): PanGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
}
export interface PinchGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureInterface
    onActionCancel(event: (() => void)): PinchGestureInterface
    onActionCancel(event: ((event: GestureEvent) => void)): PinchGestureInterface
}
export class PinchGestureInterfaceInternal implements MaterializedBase,GestureInterface<PinchGestureInterface>,PinchGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PinchGestureInterfaceInternal.getFinalizer())
    }
    constructor(value: PinchGestureInterface_Invoke_Literal) {
        this(false, PinchGestureInterfaceInternal.construct(value))
    }
    static construct(value: PinchGestureInterface_Invoke_Literal): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PinchGestureInterface_Invoke_Literal_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PinchGestureInterface_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PinchGestureInterfaceInternal {
        return new PinchGestureInterfaceInternal(false, ptr)
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
        return this.onActionCancel0_serialize(event_casted)
    }
    public onActionCancel(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionCancel1_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel0_serialize(event: (() => void)): PinchGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
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
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TapGestureInterfaceInternal.getFinalizer())
    }
    constructor(value: TapGestureParameters) {
        this(false, TapGestureInterfaceInternal.construct(value))
    }
    static construct(value: TapGestureParameters): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TapGestureParameters_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._TapGestureInterface_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureInterface_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureInterfaceInternal {
        return new TapGestureInterfaceInternal(false, ptr)
    }
    public onAction(event: ((event: GestureEvent) => void)): TapGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): TapGestureInterface {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._TapGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TapGestureInterface = TapGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
}
export interface GestureInterface<T = void> {
}
export interface LongPressGestureInterface_Invoke_Literal {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface PanGestureInterface_Invoke_Literal {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface PinchGestureInterface_Invoke_Literal {
    fingers?: number;
    distance?: number;
}
export class GestureGroupInterface_serializer {
    public static write(buffer: SerializerBase, value: GestureGroupInterface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): GestureGroupInterface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return GestureGroupInterfaceInternal.fromPtr(ptr)
    }
}
export class LongPressGestureInterface_serializer {
    public static write(buffer: SerializerBase, value: LongPressGestureInterface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LongPressGestureInterface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LongPressGestureInterfaceInternal.fromPtr(ptr)
    }
}
export class PanGestureInterface_serializer {
    public static write(buffer: SerializerBase, value: PanGestureInterface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PanGestureInterface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PanGestureInterfaceInternal.fromPtr(ptr)
    }
}
export class PinchGestureInterface_serializer {
    public static write(buffer: SerializerBase, value: PinchGestureInterface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PinchGestureInterface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PinchGestureInterfaceInternal.fromPtr(ptr)
    }
}
export class TapGestureInterface_serializer {
    public static write(buffer: SerializerBase, value: TapGestureInterface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TapGestureInterface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TapGestureInterfaceInternal.fromPtr(ptr)
    }
}
export class LongPressGestureInterface_Invoke_Literal_serializer {
    public static write(buffer: SerializerBase, value: LongPressGestureInterface_Invoke_Literal): void {
        let valueSerializer : SerializerBase = buffer
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
    public static read(buffer: DeserializerBase): LongPressGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
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
        let value : LongPressGestureInterface_Invoke_Literal = ({fingers: fingers_result, repeat: repeat_result, duration: duration_result} as LongPressGestureInterface_Invoke_Literal)
        return value
    }
}
export class PanGestureInterface_Invoke_Literal_serializer {
    public static write(buffer: SerializerBase, value: PanGestureInterface_Invoke_Literal): void {
        let valueSerializer : SerializerBase = buffer
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
    public static read(buffer: DeserializerBase): PanGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
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
        let value : PanGestureInterface_Invoke_Literal = ({fingers: fingers_result, direction: direction_result, distance: distance_result} as PanGestureInterface_Invoke_Literal)
        return value
    }
}
export class PinchGestureInterface_Invoke_Literal_serializer {
    public static write(buffer: SerializerBase, value: PinchGestureInterface_Invoke_Literal): void {
        let valueSerializer : SerializerBase = buffer
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
    public static read(buffer: DeserializerBase): PinchGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
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
        let value : PinchGestureInterface_Invoke_Literal = ({fingers: fingers_result, distance: distance_result} as PinchGestureInterface_Invoke_Literal)
        return value
    }
}

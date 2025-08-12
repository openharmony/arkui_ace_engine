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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Gesture_serializer, GestureMode, GestureType, Gesture, GestureInternal, LongPressGestureHandlerOptions, GestureEvent, GestureEventInternal, PanGestureOptions_serializer, PanGestureOptions, PanGestureOptionsInternal, PanGestureHandlerOptions, PinchGestureHandlerOptions, TapGestureParameters_serializer, TapGestureParameters, PanDirection } from "./gesture"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
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
        for (let gestureCounterI = 0; gestureCounterI < gesture.length; gestureCounterI++) {
            const gestureTmpElement : GestureType = gesture[gestureCounterI]
            if (gestureTmpElement instanceof Gesture) {
                thisSerializer.writeInt8((0).toChar())
                const gestureTmpElementForIdx0  = gestureTmpElement as Gesture
                Gesture_serializer.write(thisSerializer, gestureTmpElementForIdx0)
            } else if (gestureTmpElement instanceof object) {
                thisSerializer.writeInt8((1).toChar())
                const gestureTmpElementForIdx1  = gestureTmpElement as object
                thisSerializer.writeCustomObject('object', gestureTmpElementForIdx1)
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
        if (value instanceof PanGestureInterface_Invoke_Literal) {
            thisSerializer.writeInt8((0).toChar())
            const valueForIdx0  = value as PanGestureInterface_Invoke_Literal
            PanGestureInterface_Invoke_Literal_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof PanGestureOptions) {
            thisSerializer.writeInt8((1).toChar())
            const valueForIdx1  = value as PanGestureOptions
            PanGestureOptions_serializer.write(thisSerializer, valueForIdx1)
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
        const valueHolderForFingers  = value.fingers
        if (valueHolderForFingers !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFingersTmpValue  = valueHolderForFingers!
            valueSerializer.writeNumber(valueHolderForFingersTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRepeat  = value.repeat
        if (valueHolderForRepeat !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRepeatTmpValue  = valueHolderForRepeat!
            valueSerializer.writeBoolean(valueHolderForRepeatTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDuration  = value.duration
        if (valueHolderForDuration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDurationTmpValue  = valueHolderForDuration!
            valueSerializer.writeNumber(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LongPressGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
        const fingersTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingersTmpBuf : number | undefined
        if ((fingersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fingersTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fingersTmpResult : number | undefined = fingersTmpBuf
        const repeatTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let repeatTmpBuf : boolean | undefined
        if ((repeatTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            repeatTmpBuf = valueDeserializer.readBoolean()
        }
        const repeatTmpResult : boolean | undefined = repeatTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : number | undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const durationTmpResult : number | undefined = durationTmpBuf
        let value : LongPressGestureInterface_Invoke_Literal = ({fingers: fingersTmpResult, repeat: repeatTmpResult, duration: durationTmpResult} as LongPressGestureInterface_Invoke_Literal)
        return value
    }
}
export class PanGestureInterface_Invoke_Literal_serializer {
    public static write(buffer: SerializerBase, value: PanGestureInterface_Invoke_Literal): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFingers  = value.fingers
        if (valueHolderForFingers !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFingersTmpValue  = valueHolderForFingers!
            valueSerializer.writeNumber(valueHolderForFingersTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as PanDirection)
            valueSerializer.writeInt32(TypeChecker.PanDirection_ToNumeric(valueHolderForDirectionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDistance  = value.distance
        if (valueHolderForDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistanceTmpValue  = valueHolderForDistance!
            valueSerializer.writeNumber(valueHolderForDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PanGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
        const fingersTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingersTmpBuf : number | undefined
        if ((fingersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fingersTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fingersTmpResult : number | undefined = fingersTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : PanDirection | undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = TypeChecker.PanDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const directionTmpResult : PanDirection | undefined = directionTmpBuf
        const distanceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distanceTmpBuf : number | undefined
        if ((distanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distanceTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const distanceTmpResult : number | undefined = distanceTmpBuf
        let value : PanGestureInterface_Invoke_Literal = ({fingers: fingersTmpResult, direction: directionTmpResult, distance: distanceTmpResult} as PanGestureInterface_Invoke_Literal)
        return value
    }
}
export class PinchGestureInterface_Invoke_Literal_serializer {
    public static write(buffer: SerializerBase, value: PinchGestureInterface_Invoke_Literal): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFingers  = value.fingers
        if (valueHolderForFingers !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFingersTmpValue  = valueHolderForFingers!
            valueSerializer.writeNumber(valueHolderForFingersTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDistance  = value.distance
        if (valueHolderForDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistanceTmpValue  = valueHolderForDistance!
            valueSerializer.writeNumber(valueHolderForDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PinchGestureInterface_Invoke_Literal {
        let valueDeserializer : DeserializerBase = buffer
        const fingersTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fingersTmpBuf : number | undefined
        if ((fingersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fingersTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fingersTmpResult : number | undefined = fingersTmpBuf
        const distanceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distanceTmpBuf : number | undefined
        if ((distanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distanceTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const distanceTmpResult : number | undefined = distanceTmpBuf
        let value : PinchGestureInterface_Invoke_Literal = ({fingers: fingersTmpResult, distance: distanceTmpResult} as PinchGestureInterface_Invoke_Literal)
        return value
    }
}

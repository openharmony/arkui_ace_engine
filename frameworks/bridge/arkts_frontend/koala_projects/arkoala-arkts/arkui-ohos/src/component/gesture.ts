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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, nullptr, InteropNativeModule } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { InteractionHand } from "./enums"
import { SourceTool, BaseEvent, BaseEventInternal, Callback } from "./common"
import { GestureOps } from "./arkui-custom"
import { PeerNode } from "../PeerNode"
export interface TapGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): TapGestureInterface
}
export class TapGestureInterfaceInternal implements MaterializedBase,GestureInterface<TapGestureInterface>,TapGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_tapgestureinterface(value?: TapGestureParameters): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTapGestureParameters(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TapGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: TapGestureParameters) {
        const ctorPtr : KPointer = TapGestureInterfaceInternal.ctor_tapgestureinterface(value)
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
        const obj : TapGestureInterfaceInternal = new TapGestureInterfaceInternal(undefined)
        obj.peer = new Finalizable(ptr, TapGestureInterfaceInternal.getFinalizer())
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
    static ctor_longpressgestureinterface(value?: Literal_Number_duration_fingers_Boolean_repeat): KPointer {
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
            const value_value_repeat  = value_value.repeat
            let value_value_repeat_type : int32 = RuntimeType.UNDEFINED
            value_value_repeat_type = runtimeType(value_value_repeat)
            thisSerializer.writeInt8(value_value_repeat_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_repeat_type)) {
                const value_value_repeat_value  = value_value_repeat!
                thisSerializer.writeBoolean(value_value_repeat_value)
            }
            const value_value_duration  = value_value.duration
            let value_value_duration_type : int32 = RuntimeType.UNDEFINED
            value_value_duration_type = runtimeType(value_value_duration)
            thisSerializer.writeInt8(value_value_duration_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_duration_type)) {
                const value_value_duration_value  = value_value_duration!
                thisSerializer.writeNumber(value_value_duration_value)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_duration_fingers_Boolean_repeat) {
        const ctorPtr : KPointer = LongPressGestureInterfaceInternal.ctor_longpressgestureinterface(value)
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
    public onActionCancel(event: (() => void) | ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_type = runtimeType(event)
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as ((() => void))
            return this.onActionCancel0_serialize(event_casted)
        }
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as (((event: GestureEvent) => void))
            return this.onActionCancel1_serialize(event_casted)
        }
        throw new Error("Can not select appropriate overload")
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
    private onActionCancel0_serialize(event: (() => void)): LongPressGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): LongPressGestureInterfaceInternal {
        const obj : LongPressGestureInterfaceInternal = new LongPressGestureInterfaceInternal(undefined)
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
    static ctor_pangestureoptions(value?: PanGestureHandlerOptions): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writePanGestureHandlerOptions(value_value)
        }
        const retval = ArkUIGeneratedNativeModule._PanGestureOptions_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: PanGestureHandlerOptions) {
        const ctorPtr: KPointer = PanGestureOptions.ctor_pangestureoptions(value)
        this.peer = new Finalizable(ctorPtr, PanGestureOptions.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureOptions_getFinalizer()
    }
    public setDirection(value: PanDirection): void {
        const value_casted = value as (PanDirection)
        this.setDirection_serialize(value_casted)
    }
    public setDistance(value: number): void {
        const value_casted = value as (number)
        this.setDistance_serialize(value_casted)
    }
    public setFingers(value: number): void {
        const value_casted = value as (number)
        this.setFingers_serialize(value_casted)
    }
    public getDirection(): PanDirection {
        return this.getDirection_serialize()
    }
    public getDistance(): number {
        return this.getDistance_serialize()
    }
    private setDirection_serialize(value: PanDirection): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDirection(this.peer!.ptr, TypeChecker.PanDirection_ToNumeric(value))
    }
    private setDistance_serialize(value: number): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setDistance(this.peer!.ptr, value)
    }
    private setFingers_serialize(value: number): void {
        ArkUIGeneratedNativeModule._PanGestureOptions_setFingers(this.peer!.ptr, value)
    }
    private getDirection_serialize(): PanDirection {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDirection(this.peer!.ptr)
        return TypeChecker.PanDirection_FromNumeric(retval)
    }
    private getDistance_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDistance(this.peer!.ptr)
        return retval
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
    static ctor_pangestureinterface(value?: Literal_Number_distance_fingers_PanDirection_direction | PanGestureOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isLiteral_Number_distance_fingers_PanDirection_direction(value_value, false, false, false))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Literal_Number_distance_fingers_PanDirection_direction
                const value_value_0_fingers  = value_value_0.fingers
                let value_value_0_fingers_type : int32 = RuntimeType.UNDEFINED
                value_value_0_fingers_type = runtimeType(value_value_0_fingers)
                thisSerializer.writeInt8(value_value_0_fingers_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_fingers_type)) {
                    const value_value_0_fingers_value  = value_value_0_fingers!
                    thisSerializer.writeNumber(value_value_0_fingers_value)
                }
                const value_value_0_direction  = value_value_0.direction
                let value_value_0_direction_type : int32 = RuntimeType.UNDEFINED
                value_value_0_direction_type = runtimeType(value_value_0_direction)
                thisSerializer.writeInt8(value_value_0_direction_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_direction_type)) {
                    const value_value_0_direction_value  = (value_value_0_direction as PanDirection)
                    thisSerializer.writeInt32(TypeChecker.PanDirection_ToNumeric(value_value_0_direction_value))
                }
                const value_value_0_distance  = value_value_0.distance
                let value_value_0_distance_type : int32 = RuntimeType.UNDEFINED
                value_value_0_distance_type = runtimeType(value_value_0_distance)
                thisSerializer.writeInt8(value_value_0_distance_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_distance_type)) {
                    const value_value_0_distance_value  = value_value_0_distance!
                    thisSerializer.writeNumber(value_value_0_distance_value)
                }
            }
            else if (TypeChecker.isPanGestureOptions(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PanGestureOptions
                thisSerializer.writePanGestureOptions(value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_distance_fingers_PanDirection_direction | PanGestureOptions) {
        const ctorPtr : KPointer = PanGestureInterfaceInternal.ctor_pangestureinterface(value)
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
    public onActionCancel(event: (() => void) | ((event: GestureEvent) => void)): PanGestureInterface {
        const event_type = runtimeType(event)
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as ((() => void))
            return this.onActionCancel0_serialize(event_casted)
        }
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as (((event: GestureEvent) => void))
            return this.onActionCancel1_serialize(event_casted)
        }
        throw new Error("Can not select appropriate overload")
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
    private onActionCancel0_serialize(event: (() => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): PanGestureInterfaceInternal {
        const obj : PanGestureInterfaceInternal = new PanGestureInterfaceInternal(undefined)
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
    static ctor_swipegestureinterface(value?: Literal_Number_fingers_speed_SwipeDirection_direction): KPointer {
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
                const value_value_direction_value  = (value_value_direction as SwipeDirection)
                thisSerializer.writeInt32(TypeChecker.SwipeDirection_ToNumeric(value_value_direction_value))
            }
            const value_value_speed  = value_value.speed
            let value_value_speed_type : int32 = RuntimeType.UNDEFINED
            value_value_speed_type = runtimeType(value_value_speed)
            thisSerializer.writeInt8(value_value_speed_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_speed_type)) {
                const value_value_speed_value  = value_value_speed!
                thisSerializer.writeNumber(value_value_speed_value)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_fingers_speed_SwipeDirection_direction) {
        const ctorPtr : KPointer = SwipeGestureInterfaceInternal.ctor_swipegestureinterface(value)
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
        const obj : SwipeGestureInterfaceInternal = new SwipeGestureInterfaceInternal(undefined)
        obj.peer = new Finalizable(ptr, SwipeGestureInterfaceInternal.getFinalizer())
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
    static ctor_pinchgestureinterface(value?: Literal_Number_distance_fingers): KPointer {
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
            const value_value_distance  = value_value.distance
            let value_value_distance_type : int32 = RuntimeType.UNDEFINED
            value_value_distance_type = runtimeType(value_value_distance)
            thisSerializer.writeInt8(value_value_distance_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_distance_type)) {
                const value_value_distance_value  = value_value_distance!
                thisSerializer.writeNumber(value_value_distance_value)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_distance_fingers) {
        const ctorPtr : KPointer = PinchGestureInterfaceInternal.ctor_pinchgestureinterface(value)
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
    public onActionCancel(event: (() => void) | ((event: GestureEvent) => void)): PinchGestureInterface {
        const event_type = runtimeType(event)
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as ((() => void))
            return this.onActionCancel0_serialize(event_casted)
        }
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as (((event: GestureEvent) => void))
            return this.onActionCancel1_serialize(event_casted)
        }
        throw new Error("Can not select appropriate overload")
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
    private onActionCancel0_serialize(event: (() => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): PinchGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PinchGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PinchGestureInterface = PinchGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): PinchGestureInterfaceInternal {
        const obj : PinchGestureInterfaceInternal = new PinchGestureInterfaceInternal(undefined)
        obj.peer = new Finalizable(ptr, PinchGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
export interface RotationGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): RotationGestureInterface
    onActionCancel(event: (() => void)): RotationGestureInterface
    onActionCancel(event: ((event: GestureEvent) => void)): RotationGestureInterface
}
export class RotationGestureInterfaceInternal implements MaterializedBase,GestureInterface<RotationGestureInterface>,RotationGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_rotationgestureinterface(value?: Literal_Number_angle_fingers): KPointer {
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
            const value_value_angle  = value_value.angle
            let value_value_angle_type : int32 = RuntimeType.UNDEFINED
            value_value_angle_type = runtimeType(value_value_angle)
            thisSerializer.writeInt8(value_value_angle_type as int32)
            if ((RuntimeType.UNDEFINED) != (value_value_angle_type)) {
                const value_value_angle_value  = value_value_angle!
                thisSerializer.writeNumber(value_value_angle_value)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: Literal_Number_angle_fingers) {
        const ctorPtr : KPointer = RotationGestureInterfaceInternal.ctor_rotationgestureinterface(value)
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
    public onActionCancel(event: (() => void) | ((event: GestureEvent) => void)): RotationGestureInterface {
        const event_type = runtimeType(event)
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as ((() => void))
            return this.onActionCancel0_serialize(event_casted)
        }
        if (RuntimeType.FUNCTION == event_type) {
            const event_casted = event as (((event: GestureEvent) => void))
            return this.onActionCancel1_serialize(event_casted)
        }
        throw new Error("Can not select appropriate overload")
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
    private onActionCancel0_serialize(event: (() => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionCancel0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel1_serialize(event: ((event: GestureEvent) => void)): RotationGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._RotationGestureInterface_onActionCancel1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RotationGestureInterface = RotationGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): RotationGestureInterfaceInternal {
        const obj : RotationGestureInterfaceInternal = new RotationGestureInterfaceInternal(undefined)
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
    static ctor_gesturegroupinterface(mode: GestureMode, gesture: Array<GestureType>): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(gesture.length as int32)
        for (let i = 0; i < gesture.length; i++) {
            const gesture_element : GestureType = gesture[i]
            let gesture_element_type : int32 = RuntimeType.UNDEFINED
            gesture_element_type = runtimeType(gesture_element)
        }
        const retval  = ArkUIGeneratedNativeModule._GestureGroupInterface_ctor(TypeChecker.GestureMode_ToNumeric(mode), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(mode?: GestureMode, gesture?: Array<GestureType>) {
        if (((mode) !== (undefined)) || ((gesture) !== (undefined)))
        {
            const ctorPtr : KPointer = GestureGroupInterfaceInternal.ctor_gesturegroupinterface((mode)!, (gesture)!)
            this.peer = new Finalizable(ctorPtr, GestureGroupInterfaceInternal.getFinalizer())
        }
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
        const obj : GestureGroupInterfaceInternal = new GestureGroupInterfaceInternal(undefined, undefined)
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
    public getFingerCount(): number {
        return this.getFingerCount_serialize()
    }
    public isFingerCountLimit(): boolean {
        return this.isFingerCountLimit_serialize()
    }
    private getTag_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getTag(this.peer!.ptr)
        return retval
    }
    private getType_serialize(): GestureControl.GestureType {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(this.peer!.ptr)
        return TypeChecker.GestureControl_GestureType_FromNumeric(retval)
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
        return TypeChecker.GestureRecognizerState_FromNumeric(retval)
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
    private getFingerCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getFingerCount(this.peer!.ptr)
        return retval
    }
    private isFingerCountLimit_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isFingerCountLimit(this.peer!.ptr)
        return retval
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
    hand?: InteractionHand;
}
export type GestureType = Gesture | GestureGroup;
export interface GestureInterface<T> {
}
export interface BaseHandlerOptions {
    isFingerCountLimited?: boolean;
}
export interface TapGestureParameters extends BaseHandlerOptions {
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
export class GestureHandler {
    gestureTag: string | undefined;
    types: Array<SourceTool> | undefined;
    tag(tag: string): this {
        this.gestureTag = tag;
        return this;
    }
    allowedTypes(value: Array<SourceTool>): this {
        this.types = value;
        return this;
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void { }
    addGestureToGroup(group: KPointer): void { }
}
export interface TapGestureHandlerOptions extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
}
export class TapGestureHandler extends GestureHandler {
    finger?: number;
    count?: number;
    distanceThreshold?: number;
    isFingerCountLimited?: boolean;
    onActionCallback?: (event: GestureEvent) => void;
    pointer: KPointer = nullptr;
    constructor(options?: TapGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.count = options?.count;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: (event: GestureEvent) => void): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetTapGestureAttr(): void {
        this.pointer = GestureOps.createTapGesture(this.finger ?? 1, this.count ?? 1, this.distanceThreshold ?? Infinity, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (((event: GestureEvent) => void)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetTapGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetTapGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export class LongPressGestureHandler extends GestureHandler {
    finger?: number;
    duration?: number;
    repeat?: boolean;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: LongPressGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.duration = options?.duration;
        this.repeat = options?.repeat;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetLongPressGestureAttr(): void {
        this.pointer = GestureOps.createLongPressGesture(this.finger ?? 1, this.repeat ?? false, this.duration ?? 500, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetLongPressGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetLongPressGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface PanGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export class PanGestureHandler extends GestureHandler {
    finger?: number;
    direction?: PanDirection;
    distance?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PanGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.direction = options?.direction;
        this.distance = options?.distance;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPanGestureAttr(): void {
        this.pointer = GestureOps.createPanGesture(this.finger ?? 1, this.direction ?? PanDirection.ALL, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPanGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPanGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export class SwipeGestureHandler extends GestureHandler {
    finger?: number;
    direction?: SwipeDirection;
    speed?: number;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    constructor(options?: SwipeGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.direction = options?.direction;
        this.speed = options?.speed;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetSwipeGestureAttr(): void {
        this.pointer = GestureOps.createSwipeGesture(this.finger ?? 1, this.direction ?? SwipeDirection.ALL, this.speed ?? 100, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as ((Callback<GestureEvent>)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetSwipeGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetSwipeGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface PinchGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    distance?: number;
}
export class PinchGestureHandler extends GestureHandler {
    finger?: number;
    distance?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PinchGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.distance = options?.distance;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPinchGestureAttr(): void {
        this.pointer = GestureOps.createPinchGesture(this.finger ?? 2, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPinchGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPinchGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface RotationGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    angle?: number;
}
export class RotationGestureHandler extends GestureHandler {
    finger?: number;
    angle?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: RotationGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.angle = options?.angle;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetRotationGestureAttr(): void {
        this.pointer = GestureOps.createRotationGesture(this.finger ?? 2, this.angle ?? 1, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetRotationGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetRotationGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export interface GestureGroupGestureHandlerOptions {
    mode: GestureMode;
    gestures: GestureHandler[];
}
export class GestureGroupHandler extends GestureHandler {
    mode: GestureMode = GestureMode.SEQUENCE;
    gestures: GestureHandler[] = [];
    onCancelCallback?: () => void;
    pointer: KPointer = nullptr;
    constructor(options?: GestureGroupGestureHandlerOptions) {
        super();
        this.mode = options?.mode ?? GestureMode.SEQUENCE;
        if (options?.gestures !== undefined) {
            for (let gesture of (options?.gestures as GestureHandler[])) {
                this.gestures.push(gesture)
            }
        }
    }
    onCancel(event: () => void): this {
        this.onCancelCallback = event;
        return this;
    }
    createGestureGroup(): KPointer {
        this.pointer = GestureOps.createGestureGroup(this.mode);
        return this.pointer;
    }
    addGestureToGroup(group: KPointer): void {
        this.createGestureGroup();
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        GestureOps.addGestureToGroup(group, this.pointer);
    }
    addGestureGroupToNode(priority: number, node?: PeerNode, mask?: GestureMask): void {
        this.createGestureGroup();
        if (this.onCancelCallback !== undefined) {
            GestureOps.setOnCancel(this.pointer, this.onCancelCallback as (() => void));
        }
        for (let gesture of this.gestures) {
            if (gesture instanceof GestureGroupHandler) {
                let gestureGroup = gesture as GestureGroupHandler;
                gestureGroup.addGestureToGroup(this.pointer);
            } else if (gesture instanceof GestureHandler) {
                let singleGesture = gesture as GestureHandler;
                singleGesture.addGestureToGroup(this.pointer);
            }
        }
        if (node) {
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
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
export interface GestureEvent extends BaseEvent {
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
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._GestureEvent_getFingerList(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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

export class Gesture {
    gestureTag: string | undefined;
    types: Array<SourceTool> | undefined;
    tag(tag: string): this {
        this.gestureTag = tag;
        return this;
    }
    allowedTypes(value: Array<SourceTool>): this {
        this.types = value;
        return this;
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void { }
    addGestureToGroup(group: KPointer): void { }
}
export class TapGesture extends Gesture {
    finger?: number;
    count?: number;
    distanceThreshold?: number;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => TapGesture, value?: TapGestureParameters): TapGesture {
        const tap = factory();
        tap.finger = value?.fingers;
        tap.count = value?.count;
        tap.distanceThreshold = value?.distanceThreshold;
        tap.isFingerCountLimited = value?.isFingerCountLimited;
        return tap;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetTapGestureAttr(): void {
        this.pointer = GestureOps.createTapGesture(this.finger ?? 1, this.count ?? 1, this.distanceThreshold ?? Infinity, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetTapGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetTapGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class LongPressGesture extends Gesture {
    finger?: number;
    duration?: number;
    repeat?: boolean;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => LongPressGesture, value?: LongPressGestureHandlerOptions): LongPressGesture {
        const longPress = factory();
        longPress.finger = value?.fingers;
        longPress.duration = value?.duration;
        longPress.repeat = value?.repeat;
        longPress.isFingerCountLimited = value?.isFingerCountLimited;
        return longPress;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetLongPressGestureAttr(): void {
        this.pointer = GestureOps.createLongPressGesture(this.finger ?? 1, this.repeat ?? false, this.duration ?? 500, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetLongPressGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetLongPressGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PanGesture extends Gesture {
    finger?: number;
    direction?: PanDirection;
    distance?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    panGestureOptions?: PanGestureOptions;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => PanGesture, value?: PanGestureHandlerOptions | PanGestureOptions): PanGesture {
        const pan = factory();
        if (TypeChecker.isPanGestureHandlerOptions(value, false, false, false)) {
            let options = value as PanGestureHandlerOptions;
            pan.finger = options?.fingers;
            pan.direction = options?.direction;
            pan.distance = options?.distance;
            pan.isFingerCountLimited = options?.isFingerCountLimited;
        } else if (value !== undefined) {
            let panGestureOptions = value as PanGestureOptions;
            pan.panGestureOptions = panGestureOptions;
        }
        return pan;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPanGestureAttr(): void {
        if (this.panGestureOptions !== undefined) {
            this.pointer = GestureOps.createPanGestureWithPanGestureOptions(this.panGestureOptions!.getPeer()!.ptr);
        } else {
            this.pointer = GestureOps.createPanGesture(this.finger ?? 1, this.direction ?? PanDirection.ALL, this.distance ?? 5, this.isFingerCountLimited ?? false);
        }
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPanGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPanGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PinchGesture extends Gesture {
    finger?: number;
    distance?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => PinchGesture, value?: PinchGestureHandlerOptions): PinchGesture {
        const pinch = factory();
        pinch.finger = value?.fingers;
        pinch.distance = value?.distance;
        pinch.isFingerCountLimited = value?.isFingerCountLimited;
        return pinch;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPinchGestureAttr(): void {
        this.pointer = GestureOps.createPinchGesture(this.finger ?? 2, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPinchGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPinchGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class RotationGesture extends Gesture {
    finger?: number;
    angle?: number;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => RotationGesture, value?: RotationGestureHandlerOptions): RotationGesture {
        const rotation = factory();
        rotation.finger = value?.fingers;
        rotation.angle = value?.angle;
        rotation.isFingerCountLimited = value?.isFingerCountLimited;
        return rotation;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetRotationGestureAttr(): void {
        this.pointer = GestureOps.createRotationGesture(this.finger ?? 2, this.angle ?? 1, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetRotationGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetRotationGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class SwipeGesture extends Gesture {
    finger?: number;
    direction?: SwipeDirection;
    speed?: number;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => SwipeGesture, value?: SwipeGestureHandlerOptions): SwipeGesture {
        const swipe = factory();
        swipe.finger = value?.fingers;
        swipe.direction = value?.direction;
        swipe.speed = value?.speed;
        swipe.isFingerCountLimited = value?.isFingerCountLimited;
        return swipe;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetSwipeGestureAttr(): void {
        this.pointer = GestureOps.createSwipeGesture(this.finger ?? 1, this.direction ?? SwipeDirection.ALL, this.speed ?? 100, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as ((Callback<GestureEvent>)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetSwipeGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetSwipeGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class GestureGroup {
    mode: GestureMode = GestureMode.SEQUENCE;
    gestures: GestureType[] = [];
    onCancelCallback?: () => void;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => GestureGroup, mode: GestureMode, ...gestures: GestureType[]): GestureGroup {
        const group = factory();
        group.mode = mode;
        group.gestures = gestures;
        return group;
    }
    onCancel(event: () => void): this {
        this.onCancelCallback = event;
        return this;
    }
    createGestureGroup(): KPointer {
        this.pointer = GestureOps.createGestureGroup(this.mode);
        return this.pointer;
    }
    addGestureToGroup(group: KPointer): void {
        this.createGestureGroup();
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        GestureOps.addGestureToGroup(group, this.pointer);
    }
    addGestureGroupToNode(priority: number, node?: PeerNode, mask?: GestureMask): void {
        this.createGestureGroup();
        if (this.onCancelCallback !== undefined) {
            GestureOps.setOnCancel(this.pointer, this.onCancelCallback as (() => void));
        }
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        if (node) {
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
}

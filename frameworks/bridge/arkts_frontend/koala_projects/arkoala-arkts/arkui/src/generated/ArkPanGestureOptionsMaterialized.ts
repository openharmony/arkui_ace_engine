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

import { Literal_Number_distance_fingers_PanDirection_direction } from "./SyntheticDeclarations"
import { PanDirection } from "./ArkGestureInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
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

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

import { Position, ResourceColor, Length } from "./ArkUnitsInterfaces"
import { Color } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class CommonShapeInternal {
    public static fromPtr(ptr: KPointer): CommonShape {
        const obj: CommonShape = new CommonShape()
        obj.peer = new Finalizable(ptr, CommonShape.getFinalizer())
        return obj
    }
}
export class CommonShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_commonshape(): KPointer {
        const retval = ArkUIGeneratedNativeModule._CommonShape_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = CommonShape.ctor_commonshape()
        this.peer = new Finalizable(ctorPtr, CommonShape.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CommonShape_getFinalizer()
    }
    public offset(offset: Position): CommonShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): CommonShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): CommonShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    private offset_serialize(offset: Position): CommonShape {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePosition(offset)
        const retval = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer: Serializer = Serializer.hold()
        let color_type: int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (((RuntimeType.NUMBER) == (color_type)) && ((unsafeCast<int32>(color)) >= (0)) && ((unsafeCast<int32>(color)) <= (11))) {
            thisSerializer.writeInt8(0)
            const color_0 = unsafeCast<Color>(color)
            thisSerializer.writeInt32(color_0)
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1)
            const color_1 = unsafeCast<number>(color)
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2)
            const color_2 = unsafeCast<string>(color)
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3)
            const color_3 = unsafeCast<Resource>(color)
            thisSerializer.writeResource(color_3)
        }
        const retval = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CommonShape {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePosition(position)
        const retval = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}

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

import { ShapeSize } from "./ArkArkuiExternalInterfaces"
import { Position, ResourceColor, Length, SizeOptions } from "./../component/units"
import { Color } from "./../component/enums"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class CircleShapeInternal {
    public static fromPtr(ptr: KPointer): CircleShape {
        const obj : CircleShape = new CircleShape(undefined)
        obj.peer = new Finalizable(ptr, CircleShape.getFinalizer())
        return obj
    }
}
export class CircleShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_circleshape(options?: ShapeSize): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeShapeSize(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(options?: ShapeSize) {
        const ctorPtr : KPointer = CircleShape.ctor_circleshape((options)!)
        this.peer = new Finalizable(ctorPtr, CircleShape.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CircleShape_getFinalizer()
    }
    public offset(offset: Position): CircleShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): CircleShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): CircleShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    public width(width: Length): CircleShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): CircleShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): CircleShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    private offset_serialize(offset: Position): CircleShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(offset)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CircleShape {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0 as int32)
            const color_0  = color as Color
            thisSerializer.writeInt32(color_0.valueOf())
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1 as int32)
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2 as int32)
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3 as int32)
            const color_3  = color as Resource
            thisSerializer.writeResource(color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CircleShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(position)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): CircleShape {
        const retval  = ArkUIGeneratedNativeModule._CircleShape_width(this.peer!.ptr, width)
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): CircleShape {
        const retval  = ArkUIGeneratedNativeModule._CircleShape_height(this.peer!.ptr, height)
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): CircleShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(size)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
}

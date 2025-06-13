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
import { Position, ResourceColor, Length, SizeOptions } from "./ArkUnitsInterfaces"
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
export class EllipseShapeInternal {
    public static fromPtr(ptr: KPointer): EllipseShape {
        const obj: EllipseShape = new EllipseShape(undefined)
        obj.peer = new Finalizable(ptr, EllipseShape.getFinalizer())
        return obj
    }
}
export class EllipseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_ellipseshape(options?: ShapeSize): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeShapeSize(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._EllipseShape_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(options?: ShapeSize) {
        const ctorPtr: KPointer = EllipseShape.ctor_ellipseshape((options)!)
        this.peer = new Finalizable(ctorPtr, EllipseShape.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._EllipseShape_getFinalizer()
    }
    public offset(offset: Position): EllipseShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): EllipseShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): EllipseShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    public width(width: Length): EllipseShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): EllipseShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): EllipseShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    private offset_serialize(offset: Position): EllipseShape {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePosition(offset)
        const retval = ArkUIGeneratedNativeModule._EllipseShape_offset(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): EllipseShape {
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
        const retval = ArkUIGeneratedNativeModule._EllipseShape_fill(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): EllipseShape {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePosition(position)
        const retval = ArkUIGeneratedNativeModule._EllipseShape_position(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): EllipseShape {
        const retval = ArkUIGeneratedNativeModule._EllipseShape_width(this.peer!.ptr, width)
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): EllipseShape {
        const retval = ArkUIGeneratedNativeModule._EllipseShape_height(this.peer!.ptr, height)
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): EllipseShape {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(size)
        const retval = ArkUIGeneratedNativeModule._EllipseShape_size(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
}

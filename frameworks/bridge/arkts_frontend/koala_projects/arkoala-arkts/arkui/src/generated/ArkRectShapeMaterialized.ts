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

import { RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { Position, ResourceColor, Length, SizeOptions } from "./ArkUnitsInterfaces"
import { Color } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class RectShapeInternal {
    public static fromPtr(ptr: KPointer): RectShape {
        const obj : RectShape = new RectShape(undefined)
        obj.peer = new Finalizable(ptr, RectShape.getFinalizer())
        return obj
    }
}
export class RectShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_rectshape(options?: RectShapeOptions | RoundRectShapeOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isRectShapeOptions(options_value, false)) {
                thisSerializer.writeInt8(0 as int32)
                const options_value_0  = options_value as RectShapeOptions
                thisSerializer.writeRectShapeOptions(options_value_0)
            }
            else if (TypeChecker.isRoundRectShapeOptions(options_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const options_value_1  = options_value as RoundRectShapeOptions
                thisSerializer.writeRoundRectShapeOptions(options_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(options?: RectShapeOptions | RoundRectShapeOptions) {
        const ctorPtr : KPointer = RectShape.ctor_rectshape((options)!)
        this.peer = new Finalizable(ctorPtr, RectShape.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RectShape_getFinalizer()
    }
    public offset(offset: Position): RectShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): RectShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): RectShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    public width(width: Length): RectShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): RectShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): RectShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    public radiusWidth(rWidth: number | string): RectShape {
        const rWidth_casted = rWidth as (number | string)
        return this.radiusWidth_serialize(rWidth_casted)
    }
    public radiusHeight(rHeight: number | string): RectShape {
        const rHeight_casted = rHeight as (number | string)
        return this.radiusHeight_serialize(rHeight_casted)
    }
    public radius(radius: number | string | Array<number | string>): RectShape {
        const radius_casted = radius as (number | string | Array<number | string>)
        return this.radius_serialize(radius_casted)
    }
    private offset_serialize(offset: Position): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(offset)
        const retval  = ArkUIGeneratedNativeModule._RectShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): RectShape {
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
        const retval  = ArkUIGeneratedNativeModule._RectShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(position)
        const retval  = ArkUIGeneratedNativeModule._RectShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): RectShape {
        const retval  = ArkUIGeneratedNativeModule._RectShape_width(this.peer!.ptr, width)
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): RectShape {
        const retval  = ArkUIGeneratedNativeModule._RectShape_height(this.peer!.ptr, height)
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(size)
        const retval  = ArkUIGeneratedNativeModule._RectShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radiusWidth_serialize(rWidth: number | string): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        let rWidth_type : int32 = RuntimeType.UNDEFINED
        rWidth_type = runtimeType(rWidth)
        if (RuntimeType.NUMBER == rWidth_type) {
            thisSerializer.writeInt8(0 as int32)
            const rWidth_0  = rWidth as number
            thisSerializer.writeNumber(rWidth_0)
        }
        else if (RuntimeType.STRING == rWidth_type) {
            thisSerializer.writeInt8(1 as int32)
            const rWidth_1  = rWidth as string
            thisSerializer.writeString(rWidth_1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusWidth(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radiusHeight_serialize(rHeight: number | string): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        let rHeight_type : int32 = RuntimeType.UNDEFINED
        rHeight_type = runtimeType(rHeight)
        if (RuntimeType.NUMBER == rHeight_type) {
            thisSerializer.writeInt8(0 as int32)
            const rHeight_0  = rHeight as number
            thisSerializer.writeNumber(rHeight_0)
        }
        else if (RuntimeType.STRING == rHeight_type) {
            thisSerializer.writeInt8(1 as int32)
            const rHeight_1  = rHeight as string
            thisSerializer.writeString(rHeight_1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusHeight(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radius_serialize(radius: number | string | Array<number | string>): RectShape {
        const thisSerializer : Serializer = Serializer.hold()
        let radius_type : int32 = RuntimeType.UNDEFINED
        radius_type = runtimeType(radius)
        if (RuntimeType.NUMBER == radius_type) {
            thisSerializer.writeInt8(0 as int32)
            const radius_0  = radius as number
            thisSerializer.writeNumber(radius_0)
        }
        else if (RuntimeType.STRING == radius_type) {
            thisSerializer.writeInt8(1 as int32)
            const radius_1  = radius as string
            thisSerializer.writeString(radius_1)
        }
        else if (RuntimeType.OBJECT == radius_type) {
            thisSerializer.writeInt8(2 as int32)
            const radius_2  = radius as Array<number | string>
            thisSerializer.writeInt32(radius_2.length as int32)
            for (let i = 0; i < radius_2.length; i++) {
                const radius_2_element : number | string = radius_2[i]
                let radius_2_element_type : int32 = RuntimeType.UNDEFINED
                radius_2_element_type = runtimeType(radius_2_element)
                if (RuntimeType.NUMBER == radius_2_element_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const radius_2_element_0  = radius_2_element as number
                    thisSerializer.writeNumber(radius_2_element_0)
                }
                else if (RuntimeType.STRING == radius_2_element_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const radius_2_element_1  = radius_2_element as string
                    thisSerializer.writeString(radius_2_element_1)
                }
            }
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radius(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
}

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
import { Position_serializer, SizeOptions_serializer, Position, ResourceColor, Length, SizeOptions } from "./../component/units"
import { Resource_serializer, Resource } from "./resource"
import { Color } from "./../component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class CircleShapeInternal {
    public static fromPtr(ptr: KPointer): CircleShape {
        return new CircleShape(false, ptr)
    }
}
export class CircleShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CircleShape.getFinalizer())
    }
    constructor(options?: ShapeSize) {
        this(false, CircleShape.construct(options))
    }
    static construct(options?: ShapeSize): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ShapeSize_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let width_type : int32 = RuntimeType.UNDEFINED
        width_type = runtimeType(width)
        if (RuntimeType.STRING == width_type) {
            thisSerializer.writeInt8((0).toChar())
            const width_0  = width as string
            thisSerializer.writeString(width_0)
        }
        else if (RuntimeType.NUMBER == width_type) {
            thisSerializer.writeInt8((1).toChar())
            const width_1  = width as number
            thisSerializer.writeNumber(width_1)
        }
        else if (RuntimeType.OBJECT == width_type) {
            thisSerializer.writeInt8((2).toChar())
            const width_2  = width as Resource
            Resource_serializer.write(thisSerializer, width_2)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let height_type : int32 = RuntimeType.UNDEFINED
        height_type = runtimeType(height)
        if (RuntimeType.STRING == height_type) {
            thisSerializer.writeInt8((0).toChar())
            const height_0  = height as string
            thisSerializer.writeString(height_0)
        }
        else if (RuntimeType.NUMBER == height_type) {
            thisSerializer.writeInt8((1).toChar())
            const height_1  = height as number
            thisSerializer.writeNumber(height_1)
        }
        else if (RuntimeType.OBJECT == height_type) {
            thisSerializer.writeInt8((2).toChar())
            const height_2  = height as Resource
            Resource_serializer.write(thisSerializer, height_2)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval  = ArkUIGeneratedNativeModule._CircleShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
}
export class EllipseShapeInternal {
    public static fromPtr(ptr: KPointer): EllipseShape {
        return new EllipseShape(false, ptr)
    }
}
export class EllipseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, EllipseShape.getFinalizer())
    }
    constructor(options?: ShapeSize) {
        this(false, EllipseShape.construct(options))
    }
    static construct(options?: ShapeSize): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ShapeSize_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let width_type : int32 = RuntimeType.UNDEFINED
        width_type = runtimeType(width)
        if (RuntimeType.STRING == width_type) {
            thisSerializer.writeInt8((0).toChar())
            const width_0  = width as string
            thisSerializer.writeString(width_0)
        }
        else if (RuntimeType.NUMBER == width_type) {
            thisSerializer.writeInt8((1).toChar())
            const width_1  = width as number
            thisSerializer.writeNumber(width_1)
        }
        else if (RuntimeType.OBJECT == width_type) {
            thisSerializer.writeInt8((2).toChar())
            const width_2  = width as Resource
            Resource_serializer.write(thisSerializer, width_2)
        }
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let height_type : int32 = RuntimeType.UNDEFINED
        height_type = runtimeType(height)
        if (RuntimeType.STRING == height_type) {
            thisSerializer.writeInt8((0).toChar())
            const height_0  = height as string
            thisSerializer.writeString(height_0)
        }
        else if (RuntimeType.NUMBER == height_type) {
            thisSerializer.writeInt8((1).toChar())
            const height_1  = height as number
            thisSerializer.writeNumber(height_1)
        }
        else if (RuntimeType.OBJECT == height_type) {
            thisSerializer.writeInt8((2).toChar())
            const height_2  = height as Resource
            Resource_serializer.write(thisSerializer, height_2)
        }
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
}
export class PathShapeInternal {
    public static fromPtr(ptr: KPointer): PathShape {
        return new PathShape(false, ptr)
    }
}
export class PathShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PathShape.getFinalizer())
    }
    constructor(options?: PathShapeOptions) {
        this(false, PathShape.construct(options))
    }
    static construct(options?: PathShapeOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            PathShapeOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._PathShape_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PathShape_getFinalizer()
    }
    public offset(offset: Position): PathShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): PathShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): PathShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    public commands(commands: string): PathShape {
        const commands_casted = commands as (string)
        return this.commands_serialize(commands_casted)
    }
    private offset_serialize(offset: Position): PathShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._PathShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PathShape = PathShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): PathShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._PathShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PathShape = PathShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): PathShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._PathShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PathShape = PathShapeInternal.fromPtr(retval)
        return obj
    }
    private commands_serialize(commands: string): PathShape {
        const retval  = ArkUIGeneratedNativeModule._PathShape_commands(this.peer!.ptr, commands)
        const obj : PathShape = PathShapeInternal.fromPtr(retval)
        return obj
    }
}
export interface RectShape {
    offset(offset: Position): RectShape
    fill(color: ResourceColor): RectShape
    position(position: Position): RectShape
    width(width: Length): RectShape
    height(height: Length): RectShape
    size(size: SizeOptions): RectShape
    radiusWidth(rWidth: number | string): RectShape
    radiusHeight(rHeight: number | string): RectShape
    radius(radius: number | string | Array<number | string>): RectShape
}
export class RectShapeInternal implements MaterializedBase,RectShape {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RectShapeInternal.getFinalizer())
    }
    constructor(options?: RectShapeOptions | RoundRectShapeOptions) {
        this(false, RectShapeInternal.construct(options))
    }
    static construct(options?: RectShapeOptions | RoundRectShapeOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isRectShapeOptions(options_value, false)) {
                thisSerializer.writeInt8((0).toChar())
                const options_value_0  = options_value as RectShapeOptions
                RectShapeOptions_serializer.write(thisSerializer, options_value_0)
            }
            else if (TypeChecker.isRoundRectShapeOptions(options_value, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const options_value_1  = options_value as RoundRectShapeOptions
                RoundRectShapeOptions_serializer.write(thisSerializer, options_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RectShape_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): RectShapeInternal {
        return new RectShapeInternal(false, ptr)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._RectShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._RectShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private width_serialize(width: Length): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let width_type : int32 = RuntimeType.UNDEFINED
        width_type = runtimeType(width)
        if (RuntimeType.STRING == width_type) {
            thisSerializer.writeInt8((0).toChar())
            const width_0  = width as string
            thisSerializer.writeString(width_0)
        }
        else if (RuntimeType.NUMBER == width_type) {
            thisSerializer.writeInt8((1).toChar())
            const width_1  = width as number
            thisSerializer.writeNumber(width_1)
        }
        else if (RuntimeType.OBJECT == width_type) {
            thisSerializer.writeInt8((2).toChar())
            const width_2  = width as Resource
            Resource_serializer.write(thisSerializer, width_2)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let height_type : int32 = RuntimeType.UNDEFINED
        height_type = runtimeType(height)
        if (RuntimeType.STRING == height_type) {
            thisSerializer.writeInt8((0).toChar())
            const height_0  = height as string
            thisSerializer.writeString(height_0)
        }
        else if (RuntimeType.NUMBER == height_type) {
            thisSerializer.writeInt8((1).toChar())
            const height_1  = height as number
            thisSerializer.writeNumber(height_1)
        }
        else if (RuntimeType.OBJECT == height_type) {
            thisSerializer.writeInt8((2).toChar())
            const height_2  = height as Resource
            Resource_serializer.write(thisSerializer, height_2)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval  = ArkUIGeneratedNativeModule._RectShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radiusWidth_serialize(rWidth: number | string): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let rWidth_type : int32 = RuntimeType.UNDEFINED
        rWidth_type = runtimeType(rWidth)
        if (RuntimeType.NUMBER == rWidth_type) {
            thisSerializer.writeInt8((0).toChar())
            const rWidth_0  = rWidth as number
            thisSerializer.writeNumber(rWidth_0)
        }
        else if (RuntimeType.STRING == rWidth_type) {
            thisSerializer.writeInt8((1).toChar())
            const rWidth_1  = rWidth as string
            thisSerializer.writeString(rWidth_1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusWidth(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radiusHeight_serialize(rHeight: number | string): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let rHeight_type : int32 = RuntimeType.UNDEFINED
        rHeight_type = runtimeType(rHeight)
        if (RuntimeType.NUMBER == rHeight_type) {
            thisSerializer.writeInt8((0).toChar())
            const rHeight_0  = rHeight as number
            thisSerializer.writeNumber(rHeight_0)
        }
        else if (RuntimeType.STRING == rHeight_type) {
            thisSerializer.writeInt8((1).toChar())
            const rHeight_1  = rHeight as string
            thisSerializer.writeString(rHeight_1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusHeight(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radius_serialize(radius: number | string | Array<number | string>): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let radius_type : int32 = RuntimeType.UNDEFINED
        radius_type = runtimeType(radius)
        if (RuntimeType.NUMBER == radius_type) {
            thisSerializer.writeInt8((0).toChar())
            const radius_0  = radius as number
            thisSerializer.writeNumber(radius_0)
        }
        else if (RuntimeType.STRING == radius_type) {
            thisSerializer.writeInt8((1).toChar())
            const radius_1  = radius as string
            thisSerializer.writeString(radius_1)
        }
        else if (RuntimeType.OBJECT == radius_type) {
            thisSerializer.writeInt8((2).toChar())
            const radius_2  = radius as Array<number | string>
            thisSerializer.writeInt32((radius_2.length).toInt())
            for (let radius_2_counter_i = 0; radius_2_counter_i < radius_2.length; radius_2_counter_i++) {
                const radius_2_element : number | string = radius_2[radius_2_counter_i]
                let radius_2_element_type : int32 = RuntimeType.UNDEFINED
                radius_2_element_type = runtimeType(radius_2_element)
                if (RuntimeType.NUMBER == radius_2_element_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const radius_2_element_0  = radius_2_element as number
                    thisSerializer.writeNumber(radius_2_element_0)
                }
                else if (RuntimeType.STRING == radius_2_element_type) {
                    thisSerializer.writeInt8((1).toChar())
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
export interface PathShapeOptions {
    commands?: string;
}
export interface ShapeSize {
    width?: number | string;
    height?: number | string;
}
export interface RectShapeOptions extends ShapeSize {
    radius?: number | string | Array<number | string>;
}
export interface RoundRectShapeOptions extends ShapeSize {
    radiusWidth?: number | string;
    radiusHeight?: number | string;
}
export class CircleShape_serializer {
    public static write(buffer: SerializerBase, value: CircleShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CircleShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CircleShapeInternal.fromPtr(ptr)
    }
}
export class EllipseShape_serializer {
    public static write(buffer: SerializerBase, value: EllipseShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): EllipseShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return EllipseShapeInternal.fromPtr(ptr)
    }
}
export class PathShape_serializer {
    public static write(buffer: SerializerBase, value: PathShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PathShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PathShapeInternal.fromPtr(ptr)
    }
}
export class RectShape_serializer {
    public static write(buffer: SerializerBase, value: RectShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RectShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RectShapeInternal.fromPtr(ptr)
    }
}
export class PathShapeOptions_serializer {
    public static write(buffer: SerializerBase, value: PathShapeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_commands  = value.commands
        let value_commands_type : int32 = RuntimeType.UNDEFINED
        value_commands_type = runtimeType(value_commands)
        valueSerializer.writeInt8((value_commands_type).toChar())
        if ((value_commands_type) != (RuntimeType.UNDEFINED)) {
            const value_commands_value  = value_commands!
            valueSerializer.writeString(value_commands_value)
        }
    }
    public static read(buffer: DeserializerBase): PathShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const commands_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let commands_buf : string | undefined
        if ((commands_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            commands_buf = (valueDeserializer.readString() as string)
        }
        const commands_result : string | undefined = commands_buf
        let value : PathShapeOptions = ({commands: commands_result} as PathShapeOptions)
        return value
    }
}
export class RoundRectShapeOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundRectShapeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
        const value_radiusWidth  = value.radiusWidth
        let value_radiusWidth_type : int32 = RuntimeType.UNDEFINED
        value_radiusWidth_type = runtimeType(value_radiusWidth)
        valueSerializer.writeInt8((value_radiusWidth_type).toChar())
        if ((value_radiusWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_radiusWidth_value  = value_radiusWidth!
            let value_radiusWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_radiusWidth_value_type = runtimeType(value_radiusWidth_value)
            if (RuntimeType.NUMBER == value_radiusWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_radiusWidth_value_0  = value_radiusWidth_value as number
                valueSerializer.writeNumber(value_radiusWidth_value_0)
            }
            else if (RuntimeType.STRING == value_radiusWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_radiusWidth_value_1  = value_radiusWidth_value as string
                valueSerializer.writeString(value_radiusWidth_value_1)
            }
        }
        const value_radiusHeight  = value.radiusHeight
        let value_radiusHeight_type : int32 = RuntimeType.UNDEFINED
        value_radiusHeight_type = runtimeType(value_radiusHeight)
        valueSerializer.writeInt8((value_radiusHeight_type).toChar())
        if ((value_radiusHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_radiusHeight_value  = value_radiusHeight!
            let value_radiusHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_radiusHeight_value_type = runtimeType(value_radiusHeight_value)
            if (RuntimeType.NUMBER == value_radiusHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_radiusHeight_value_0  = value_radiusHeight_value as number
                valueSerializer.writeNumber(value_radiusHeight_value_0)
            }
            else if (RuntimeType.STRING == value_radiusHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_radiusHeight_value_1  = value_radiusHeight_value as string
                valueSerializer.writeString(value_radiusHeight_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RoundRectShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | string | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | string | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        const radiusWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusWidth_buf : number | string | undefined
        if ((radiusWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radiusWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let radiusWidth_buf_ : number | string | undefined
            if (radiusWidth_buf__selector == (0).toChar()) {
                radiusWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (radiusWidth_buf__selector == (1).toChar()) {
                radiusWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for radiusWidth_buf_ has to be chosen through deserialisation.")
            }
            radiusWidth_buf = (radiusWidth_buf_ as number | string)
        }
        const radiusWidth_result : number | string | undefined = radiusWidth_buf
        const radiusHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusHeight_buf : number | string | undefined
        if ((radiusHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radiusHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let radiusHeight_buf_ : number | string | undefined
            if (radiusHeight_buf__selector == (0).toChar()) {
                radiusHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (radiusHeight_buf__selector == (1).toChar()) {
                radiusHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for radiusHeight_buf_ has to be chosen through deserialisation.")
            }
            radiusHeight_buf = (radiusHeight_buf_ as number | string)
        }
        const radiusHeight_result : number | string | undefined = radiusHeight_buf
        let value : RoundRectShapeOptions = ({width: width_result, height: height_result, radiusWidth: radiusWidth_result, radiusHeight: radiusHeight_result} as RoundRectShapeOptions)
        return value
    }
}
export class ShapeSize_serializer {
    public static write(buffer: SerializerBase, value: ShapeSize): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ShapeSize {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | string | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | string | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        let value : ShapeSize = ({width: width_result, height: height_result} as ShapeSize)
        return value
    }
}
export class RectShapeOptions_serializer {
    public static write(buffer: SerializerBase, value: RectShapeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8((value_radius_type).toChar())
        if ((value_radius_type) != (RuntimeType.UNDEFINED)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if (RuntimeType.NUMBER == value_radius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as number
                valueSerializer.writeNumber(value_radius_value_0)
            }
            else if (RuntimeType.STRING == value_radius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as string
                valueSerializer.writeString(value_radius_value_1)
            }
            else if (RuntimeType.OBJECT == value_radius_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_radius_value_2  = value_radius_value as Array<number | string>
                valueSerializer.writeInt32((value_radius_value_2.length).toInt())
                for (let value_radius_value_2_counter_i = 0; value_radius_value_2_counter_i < value_radius_value_2.length; value_radius_value_2_counter_i++) {
                    const value_radius_value_2_element : number | string = value_radius_value_2[value_radius_value_2_counter_i]
                    let value_radius_value_2_element_type : int32 = RuntimeType.UNDEFINED
                    value_radius_value_2_element_type = runtimeType(value_radius_value_2_element)
                    if (RuntimeType.NUMBER == value_radius_value_2_element_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_radius_value_2_element_0  = value_radius_value_2_element as number
                        valueSerializer.writeNumber(value_radius_value_2_element_0)
                    }
                    else if (RuntimeType.STRING == value_radius_value_2_element_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_radius_value_2_element_1  = value_radius_value_2_element as string
                        valueSerializer.writeString(value_radius_value_2_element_1)
                    }
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): RectShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | string | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | string | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : number | string | Array<number | string> | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : number | string | Array<number | string> | undefined
            if (radius_buf__selector == (0).toChar()) {
                radius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (radius_buf__selector == (1).toChar()) {
                radius_buf_ = (valueDeserializer.readString() as string)
            }
            else if (radius_buf__selector == (2).toChar()) {
                const radius_buf__u_length : int32 = valueDeserializer.readInt32()
                let radius_buf__u : Array<number | string> = new Array<number | string>(radius_buf__u_length)
                for (let radius_buf__u_i = 0; radius_buf__u_i < radius_buf__u_length; radius_buf__u_i++) {
                    const radius_buf__u_buf_selector : int32 = valueDeserializer.readInt8()
                    let radius_buf__u_buf : number | string | undefined
                    if (radius_buf__u_buf_selector == (0).toChar()) {
                        radius_buf__u_buf = (valueDeserializer.readNumber() as number)
                    }
                    else if (radius_buf__u_buf_selector == (1).toChar()) {
                        radius_buf__u_buf = (valueDeserializer.readString() as string)
                    }
                    else {
                        throw new Error("One of the branches for radius_buf__u_buf has to be chosen through deserialisation.")
                    }
                    radius_buf__u[radius_buf__u_i] = (radius_buf__u_buf as number | string)
                }
                radius_buf_ = radius_buf__u
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as number | string | Array<number | string>)
        }
        const radius_result : number | string | Array<number | string> | undefined = radius_buf
        let value : RectShapeOptions = ({width: width_result, height: height_result, radius: radius_result} as RectShapeOptions)
        return value
    }
}

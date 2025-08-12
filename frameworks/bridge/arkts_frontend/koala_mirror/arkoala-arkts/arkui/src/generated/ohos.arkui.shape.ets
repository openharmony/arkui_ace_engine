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
import { Position_serializer, SizeOptions_serializer, Position, ResourceColor, Length, SizeOptions } from "./../component/units"
import { Resource_serializer, Resource } from "./resource"
import { Color } from "./../component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
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
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ShapeSize_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toChar())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(colorForIdx0))
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toChar())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toChar())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
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
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const widthForIdx0  = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const widthForIdx1  = width as number
            thisSerializer.writeNumber(widthForIdx1)
        } else if (width instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const widthForIdx2  = width as Resource
            Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._CircleShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CircleShape = CircleShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): CircleShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const heightForIdx0  = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const heightForIdx1  = height as number
            thisSerializer.writeNumber(heightForIdx1)
        } else if (height instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const heightForIdx2  = height as Resource
            Resource_serializer.write(thisSerializer, heightForIdx2)
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
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ShapeSize_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toChar())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(colorForIdx0))
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toChar())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toChar())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
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
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const widthForIdx0  = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const widthForIdx1  = width as number
            thisSerializer.writeNumber(widthForIdx1)
        } else if (width instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const widthForIdx2  = width as Resource
            Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._EllipseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : EllipseShape = EllipseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): EllipseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const heightForIdx0  = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const heightForIdx1  = height as number
            thisSerializer.writeNumber(heightForIdx1)
        } else if (height instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const heightForIdx2  = height as Resource
            Resource_serializer.write(thisSerializer, heightForIdx2)
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
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PathShapeOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toChar())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(colorForIdx0))
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toChar())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toChar())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
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
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            if (optionsTmpValue instanceof RectShapeOptions) {
                thisSerializer.writeInt8((0).toChar())
                const optionsTmpValueForIdx0  = optionsTmpValue as RectShapeOptions
                RectShapeOptions_serializer.write(thisSerializer, optionsTmpValueForIdx0)
            } else if (optionsTmpValue instanceof RoundRectShapeOptions) {
                thisSerializer.writeInt8((1).toChar())
                const optionsTmpValueForIdx1  = optionsTmpValue as RoundRectShapeOptions
                RoundRectShapeOptions_serializer.write(thisSerializer, optionsTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toChar())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(colorForIdx0))
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toChar())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toChar())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
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
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const widthForIdx0  = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const widthForIdx1  = width as number
            thisSerializer.writeNumber(widthForIdx1)
        } else if (width instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const widthForIdx2  = width as Resource
            Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const heightForIdx0  = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const heightForIdx1  = height as number
            thisSerializer.writeNumber(heightForIdx1)
        } else if (height instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const heightForIdx2  = height as Resource
            Resource_serializer.write(thisSerializer, heightForIdx2)
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
        if (rWidth instanceof number) {
            thisSerializer.writeInt8((0).toChar())
            const rWidthForIdx0  = rWidth as number
            thisSerializer.writeNumber(rWidthForIdx0)
        } else if (rWidth instanceof string) {
            thisSerializer.writeInt8((1).toChar())
            const rWidthForIdx1  = rWidth as string
            thisSerializer.writeString(rWidthForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusWidth(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radiusHeight_serialize(rHeight: number | string): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (rHeight instanceof number) {
            thisSerializer.writeInt8((0).toChar())
            const rHeightForIdx0  = rHeight as number
            thisSerializer.writeNumber(rHeightForIdx0)
        } else if (rHeight instanceof string) {
            thisSerializer.writeInt8((1).toChar())
            const rHeightForIdx1  = rHeight as string
            thisSerializer.writeString(rHeightForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._RectShape_radiusHeight(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : RectShape = RectShapeInternal.fromPtr(retval)
        return obj
    }
    private radius_serialize(radius: number | string | Array<number | string>): RectShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (radius instanceof number) {
            thisSerializer.writeInt8((0).toChar())
            const radiusForIdx0  = radius as number
            thisSerializer.writeNumber(radiusForIdx0)
        } else if (radius instanceof string) {
            thisSerializer.writeInt8((1).toChar())
            const radiusForIdx1  = radius as string
            thisSerializer.writeString(radiusForIdx1)
        } else if (TypeChecker.isArray_Union_Number_String(radius)) {
            thisSerializer.writeInt8((2).toChar())
            const radiusForIdx2  = radius as Array<number | string>
            thisSerializer.writeInt32((radiusForIdx2.length).toInt())
            for (let radiusForIdx2CounterI = 0; radiusForIdx2CounterI < radiusForIdx2.length; radiusForIdx2CounterI++) {
                const radiusForIdx2TmpElement : number | string = radiusForIdx2[radiusForIdx2CounterI]
                if (radiusForIdx2TmpElement instanceof number) {
                    thisSerializer.writeInt8((0).toChar())
                    const radiusForIdx2TmpElementForIdx0  = radiusForIdx2TmpElement as number
                    thisSerializer.writeNumber(radiusForIdx2TmpElementForIdx0)
                } else if (radiusForIdx2TmpElement instanceof string) {
                    thisSerializer.writeInt8((1).toChar())
                    const radiusForIdx2TmpElementForIdx1  = radiusForIdx2TmpElement as string
                    thisSerializer.writeString(radiusForIdx2TmpElementForIdx1)
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
        const valueHolderForCommands  = value.commands
        if (valueHolderForCommands !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCommandsTmpValue  = valueHolderForCommands!
            valueSerializer.writeString(valueHolderForCommandsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PathShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const commandsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let commandsTmpBuf : string | undefined
        if ((commandsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            commandsTmpBuf = (valueDeserializer.readString() as string)
        }
        const commandsTmpResult : string | undefined = commandsTmpBuf
        let value : PathShapeOptions = ({commands: commandsTmpResult} as PathShapeOptions)
        return value
    }
}
export class RoundRectShapeOptions_serializer {
    public static write(buffer: SerializerBase, value: RoundRectShapeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusWidth  = value.radiusWidth
        if (valueHolderForRadiusWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusWidthTmpValue  = valueHolderForRadiusWidth!
            if (valueHolderForRadiusWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusWidthTmpValueForIdx0  = valueHolderForRadiusWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForRadiusWidthTmpValueForIdx0)
            } else if (valueHolderForRadiusWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRadiusWidthTmpValueForIdx1  = valueHolderForRadiusWidthTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadiusHeight  = value.radiusHeight
        if (valueHolderForRadiusHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusHeightTmpValue  = valueHolderForRadiusHeight!
            if (valueHolderForRadiusHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusHeightTmpValueForIdx0  = valueHolderForRadiusHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForRadiusHeightTmpValueForIdx0)
            } else if (valueHolderForRadiusHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRadiusHeightTmpValueForIdx1  = valueHolderForRadiusHeightTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RoundRectShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | string | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : number | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as number | string)
        }
        const widthTmpResult : number | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | string | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : number | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as number | string)
        }
        const heightTmpResult : number | string | undefined = heightTmpBuf
        const radiusWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusWidthTmpBuf : number | string | undefined
        if ((radiusWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusWidthTmpBuf_ : number | string | undefined
            if (radiusWidthTmpBuf_UnionSelector == (0).toChar()) {
                radiusWidthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (radiusWidthTmpBuf_UnionSelector == (1).toChar()) {
                radiusWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for radiusWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusWidthTmpBuf = (radiusWidthTmpBuf_ as number | string)
        }
        const radiusWidthTmpResult : number | string | undefined = radiusWidthTmpBuf
        const radiusHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusHeightTmpBuf : number | string | undefined
        if ((radiusHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusHeightTmpBuf_ : number | string | undefined
            if (radiusHeightTmpBuf_UnionSelector == (0).toChar()) {
                radiusHeightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (radiusHeightTmpBuf_UnionSelector == (1).toChar()) {
                radiusHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for radiusHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusHeightTmpBuf = (radiusHeightTmpBuf_ as number | string)
        }
        const radiusHeightTmpResult : number | string | undefined = radiusHeightTmpBuf
        let value : RoundRectShapeOptions = ({width: widthTmpResult, height: heightTmpResult, radiusWidth: radiusWidthTmpResult, radiusHeight: radiusHeightTmpResult} as RoundRectShapeOptions)
        return value
    }
}
export class ShapeSize_serializer {
    public static write(buffer: SerializerBase, value: ShapeSize): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ShapeSize {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | string | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : number | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as number | string)
        }
        const widthTmpResult : number | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | string | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : number | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as number | string)
        }
        const heightTmpResult : number | string | undefined = heightTmpBuf
        let value : ShapeSize = ({width: widthTmpResult, height: heightTmpResult} as ShapeSize)
        return value
    }
}
export class RectShapeOptions_serializer {
    public static write(buffer: SerializerBase, value: RectShapeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as number
                valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx1)
            } else if (TypeChecker.isArray_Union_Number_String(valueHolderForRadiusTmpValue)) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForRadiusTmpValueForIdx2  = valueHolderForRadiusTmpValue as Array<number | string>
                valueSerializer.writeInt32((valueHolderForRadiusTmpValueForIdx2.length).toInt())
                for (let valueHolderForRadiusTmpValueForIdx2CounterI = 0; valueHolderForRadiusTmpValueForIdx2CounterI < valueHolderForRadiusTmpValueForIdx2.length; valueHolderForRadiusTmpValueForIdx2CounterI++) {
                    const valueHolderForRadiusTmpValueForIdx2TmpElement : number | string = valueHolderForRadiusTmpValueForIdx2[valueHolderForRadiusTmpValueForIdx2CounterI]
                    if (valueHolderForRadiusTmpValueForIdx2TmpElement instanceof number) {
                        valueSerializer.writeInt8((0).toChar())
                        const valueHolderForRadiusTmpValueForIdx2TmpElementForIdx0  = valueHolderForRadiusTmpValueForIdx2TmpElement as number
                        valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx2TmpElementForIdx0)
                    } else if (valueHolderForRadiusTmpValueForIdx2TmpElement instanceof string) {
                        valueSerializer.writeInt8((1).toChar())
                        const valueHolderForRadiusTmpValueForIdx2TmpElementForIdx1  = valueHolderForRadiusTmpValueForIdx2TmpElement as string
                        valueSerializer.writeString(valueHolderForRadiusTmpValueForIdx2TmpElementForIdx1)
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RectShapeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | string | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : number | string | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as number | string)
        }
        const widthTmpResult : number | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | string | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : number | string | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as number | string)
        }
        const heightTmpResult : number | string | undefined = heightTmpBuf
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : number | string | Array<number | string> | undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : number | string | Array<number | string> | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                radiusTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                radiusTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (radiusTmpBuf_UnionSelector == (2).toChar()) {
                const radiusTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let radiusTmpBuf_BufU : Array<number | string> = new Array<number | string>(radiusTmpBuf_BufULength)
                for (let radiusTmpBuf_BufUBufCounterI = 0; radiusTmpBuf_BufUBufCounterI < radiusTmpBuf_BufULength; radiusTmpBuf_BufUBufCounterI++) {
                    const radiusTmpBuf_BufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let radiusTmpBuf_BufUTempBuf : number | string | undefined
                    if (radiusTmpBuf_BufUTempBufUnionSelector == (0).toChar()) {
                        radiusTmpBuf_BufUTempBuf = (valueDeserializer.readNumber() as number)
                    } else if (radiusTmpBuf_BufUTempBufUnionSelector == (1).toChar()) {
                        radiusTmpBuf_BufUTempBuf = (valueDeserializer.readString() as string)
                    } else {
                        throw new Error("One of the branches for radiusTmpBuf_BufUTempBuf has to be chosen through deserialisation.")
                    }
                    radiusTmpBuf_BufU[radiusTmpBuf_BufUBufCounterI] = (radiusTmpBuf_BufUTempBuf as number | string)
                }
                radiusTmpBuf_ = radiusTmpBuf_BufU
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as number | string | Array<number | string>)
        }
        const radiusTmpResult : number | string | Array<number | string> | undefined = radiusTmpBuf
        let value : RectShapeOptions = ({width: widthTmpResult, height: heightTmpResult, radius: radiusTmpResult} as RectShapeOptions)
        return value
    }
}

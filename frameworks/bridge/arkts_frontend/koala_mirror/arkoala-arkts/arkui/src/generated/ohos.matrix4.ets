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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback, wrapCallback, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { common2D_Point_serializer, common2D } from "./ohos.graphics.common2D"
import { TranslateOptions_serializer, ScaleOptions_serializer, RotateOptions_serializer, TranslateOptions, ScaleOptions, RotateOptions } from "./../component/common"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class matrix4_Matrix4Transit_serializer {
    public static write(buffer: SerializerBase, value: matrix4.Matrix4Transit): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): matrix4.Matrix4Transit {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return matrix4.Matrix4TransitInternal.fromPtr(ptr)
    }
}
export class matrix4_PolyToPolyOptions_serializer {
    public static write(buffer: SerializerBase, value: matrix4.PolyToPolyOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_src  = value.src
        valueSerializer.writeInt32((value_src.length).toInt())
        for (let value_src_counter_i = 0; value_src_counter_i < value_src.length; value_src_counter_i++) {
            const value_src_element : common2D.Point = value_src[value_src_counter_i]
            common2D_Point_serializer.write(valueSerializer, value_src_element)
        }
        const value_srcIndex  = value.srcIndex
        let value_srcIndex_type : int32 = RuntimeType.UNDEFINED
        value_srcIndex_type = runtimeType(value_srcIndex)
        valueSerializer.writeInt8((value_srcIndex_type).toChar())
        if ((value_srcIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_srcIndex_value  = value_srcIndex!
            valueSerializer.writeNumber(value_srcIndex_value)
        }
        const value_dst  = value.dst
        valueSerializer.writeInt32((value_dst.length).toInt())
        for (let value_dst_counter_i = 0; value_dst_counter_i < value_dst.length; value_dst_counter_i++) {
            const value_dst_element : common2D.Point = value_dst[value_dst_counter_i]
            common2D_Point_serializer.write(valueSerializer, value_dst_element)
        }
        const value_dstIndex  = value.dstIndex
        let value_dstIndex_type : int32 = RuntimeType.UNDEFINED
        value_dstIndex_type = runtimeType(value_dstIndex)
        valueSerializer.writeInt8((value_dstIndex_type).toChar())
        if ((value_dstIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_dstIndex_value  = value_dstIndex!
            valueSerializer.writeNumber(value_dstIndex_value)
        }
        const value_pointCount  = value.pointCount
        let value_pointCount_type : int32 = RuntimeType.UNDEFINED
        value_pointCount_type = runtimeType(value_pointCount)
        valueSerializer.writeInt8((value_pointCount_type).toChar())
        if ((value_pointCount_type) != (RuntimeType.UNDEFINED)) {
            const value_pointCount_value  = value_pointCount!
            valueSerializer.writeNumber(value_pointCount_value)
        }
    }
    public static read(buffer: DeserializerBase): matrix4.PolyToPolyOptions {
        let valueDeserializer : DeserializerBase = buffer
        const src_buf_length : int32 = valueDeserializer.readInt32()
        let src_buf : Array<common2D.Point> = new Array<common2D.Point>(src_buf_length)
        for (let src_buf_i = 0; src_buf_i < src_buf_length; src_buf_i++) {
            src_buf[src_buf_i] = common2D_Point_serializer.read(valueDeserializer)
        }
        const src_result : Array<common2D.Point> = src_buf
        const srcIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcIndex_buf : number | undefined
        if ((srcIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            srcIndex_buf = (valueDeserializer.readNumber() as number)
        }
        const srcIndex_result : number | undefined = srcIndex_buf
        const dst_buf_length : int32 = valueDeserializer.readInt32()
        let dst_buf : Array<common2D.Point> = new Array<common2D.Point>(dst_buf_length)
        for (let dst_buf_i = 0; dst_buf_i < dst_buf_length; dst_buf_i++) {
            dst_buf[dst_buf_i] = common2D_Point_serializer.read(valueDeserializer)
        }
        const dst_result : Array<common2D.Point> = dst_buf
        const dstIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dstIndex_buf : number | undefined
        if ((dstIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dstIndex_buf = (valueDeserializer.readNumber() as number)
        }
        const dstIndex_result : number | undefined = dstIndex_buf
        const pointCount_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointCount_buf : number | undefined
        if ((pointCount_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            pointCount_buf = (valueDeserializer.readNumber() as number)
        }
        const pointCount_result : number | undefined = pointCount_buf
        let value : matrix4.PolyToPolyOptions = ({src: src_result, srcIndex: srcIndex_result, dst: dst_result, dstIndex: dstIndex_result, pointCount: pointCount_result} as matrix4.PolyToPolyOptions)
        return value
    }
}
export namespace matrix4 {
    export interface Matrix4Transit {
        copy(): Matrix4Transit
        invert(): Matrix4Transit
        combine(options: Matrix4Transit): Matrix4Transit
        translate(options: TranslateOptions): Matrix4Transit
        scale(options: ScaleOptions): Matrix4Transit
        skew(x: number, y: number): Matrix4Transit
        rotate(options: RotateOptions): Matrix4Transit
        transformPoint(options: [ number, number ]): [ number, number ]
        setPolyToPoly(options: PolyToPolyOptions): Matrix4Transit
    }
    export class Matrix4TransitInternal implements MaterializedBase,matrix4.Matrix4Transit {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Matrix4TransitInternal.getFinalizer())
        }
        constructor() {
            this(Matrix4TransitInternal.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_getFinalizer()
        }
        public static fromPtr(ptr: KPointer): Matrix4TransitInternal {
            return new Matrix4TransitInternal(ptr)
        }
        public copy(): Matrix4Transit {
            return this.copy_serialize()
        }
        public invert(): Matrix4Transit {
            return this.invert_serialize()
        }
        public combine(options: Matrix4Transit): Matrix4Transit {
            const options_casted = options as (Matrix4Transit)
            return this.combine_serialize(options_casted)
        }
        public translate(options: TranslateOptions): Matrix4Transit {
            const options_casted = options as (TranslateOptions)
            return this.translate_serialize(options_casted)
        }
        public scale(options: ScaleOptions): Matrix4Transit {
            const options_casted = options as (ScaleOptions)
            return this.scale_serialize(options_casted)
        }
        public skew(x: number, y: number): Matrix4Transit {
            const x_casted = x as (number)
            const y_casted = y as (number)
            return this.skew_serialize(x_casted, y_casted)
        }
        public rotate(options: RotateOptions): Matrix4Transit {
            const options_casted = options as (RotateOptions)
            return this.rotate_serialize(options_casted)
        }
        public transformPoint(options: [ number, number ]): [ number, number ] {
            const options_casted = options as ([ number, number ])
            return this.transformPoint_serialize(options_casted)
        }
        public setPolyToPoly(options: PolyToPolyOptions): Matrix4Transit {
            const options_casted = options as (PolyToPolyOptions)
            return this.setPolyToPoly_serialize(options_casted)
        }
        private copy_serialize(): Matrix4Transit {
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_copy(this.peer!.ptr)
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private invert_serialize(): Matrix4Transit {
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_invert(this.peer!.ptr)
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private combine_serialize(options: Matrix4Transit): Matrix4Transit {
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_combine(this.peer!.ptr, toPeerPtr(options))
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private translate_serialize(options: TranslateOptions): Matrix4Transit {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            TranslateOptions_serializer.write(thisSerializer, options)
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_translate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private scale_serialize(options: ScaleOptions): Matrix4Transit {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            ScaleOptions_serializer.write(thisSerializer, options)
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_scale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private skew_serialize(x: number, y: number): Matrix4Transit {
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_skew(this.peer!.ptr, x, y)
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private rotate_serialize(options: RotateOptions): Matrix4Transit {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            RotateOptions_serializer.write(thisSerializer, options)
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_rotate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
        private transformPoint_serialize(options: [ number, number ]): [ number, number ] {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            const options_0  = options[0]
            thisSerializer.writeNumber(options_0)
            const options_1  = options[1]
            thisSerializer.writeNumber(options_1)
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_transformPoint(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_value0 : number = (retvalDeserializer.readNumber() as number)
            const buffer_value1 : number = (retvalDeserializer.readNumber() as number)
            const returnResult : [ number, number ] = ([buffer_value0, buffer_value1] as [ number, number ])
            return returnResult
        }
        private setPolyToPoly_serialize(options: PolyToPolyOptions): Matrix4Transit {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            matrix4_PolyToPolyOptions_serializer.write(thisSerializer, options)
            const retval  = ArkUIGeneratedNativeModule._matrix4_Matrix4Transit_setPolyToPoly(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : Matrix4Transit = matrix4.Matrix4TransitInternal.fromPtr(retval)
            return obj
        }
    }
    export interface PolyToPolyOptions {
        src: Array<common2D.Point>;
        srcIndex?: number;
        dst: Array<common2D.Point>;
        dstIndex?: number;
        pointCount?: number;
    }
}

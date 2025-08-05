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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
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
        const valueHolderForSrc  = value.src
        valueSerializer.writeInt32((valueHolderForSrc.length).toInt())
        for (let valueHolderForSrcCounterI = 0; valueHolderForSrcCounterI < valueHolderForSrc.length; valueHolderForSrcCounterI++) {
            const valueHolderForSrcTmpElement : common2D.Point = valueHolderForSrc[valueHolderForSrcCounterI]
            common2D_Point_serializer.write(valueSerializer, valueHolderForSrcTmpElement)
        }
        const valueHolderForSrcIndex  = value.srcIndex
        if (valueHolderForSrcIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcIndexTmpValue  = valueHolderForSrcIndex!
            valueSerializer.writeNumber(valueHolderForSrcIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDst  = value.dst
        valueSerializer.writeInt32((valueHolderForDst.length).toInt())
        for (let valueHolderForDstCounterI = 0; valueHolderForDstCounterI < valueHolderForDst.length; valueHolderForDstCounterI++) {
            const valueHolderForDstTmpElement : common2D.Point = valueHolderForDst[valueHolderForDstCounterI]
            common2D_Point_serializer.write(valueSerializer, valueHolderForDstTmpElement)
        }
        const valueHolderForDstIndex  = value.dstIndex
        if (valueHolderForDstIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDstIndexTmpValue  = valueHolderForDstIndex!
            valueSerializer.writeNumber(valueHolderForDstIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPointCount  = value.pointCount
        if (valueHolderForPointCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPointCountTmpValue  = valueHolderForPointCount!
            valueSerializer.writeNumber(valueHolderForPointCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): matrix4.PolyToPolyOptions {
        let valueDeserializer : DeserializerBase = buffer
        const srcTmpBufLength : int32 = valueDeserializer.readInt32()
        let srcTmpBuf : Array<common2D.Point> = new Array<common2D.Point>(srcTmpBufLength)
        for (let srcTmpBufBufCounterI = 0; srcTmpBufBufCounterI < srcTmpBufLength; srcTmpBufBufCounterI++) {
            srcTmpBuf[srcTmpBufBufCounterI] = common2D_Point_serializer.read(valueDeserializer)
        }
        const srcTmpResult : Array<common2D.Point> = srcTmpBuf
        const srcIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcIndexTmpBuf : number | undefined
        if ((srcIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            srcIndexTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const srcIndexTmpResult : number | undefined = srcIndexTmpBuf
        const dstTmpBufLength : int32 = valueDeserializer.readInt32()
        let dstTmpBuf : Array<common2D.Point> = new Array<common2D.Point>(dstTmpBufLength)
        for (let dstTmpBufBufCounterI = 0; dstTmpBufBufCounterI < dstTmpBufLength; dstTmpBufBufCounterI++) {
            dstTmpBuf[dstTmpBufBufCounterI] = common2D_Point_serializer.read(valueDeserializer)
        }
        const dstTmpResult : Array<common2D.Point> = dstTmpBuf
        const dstIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dstIndexTmpBuf : number | undefined
        if ((dstIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dstIndexTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const dstIndexTmpResult : number | undefined = dstIndexTmpBuf
        const pointCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointCountTmpBuf : number | undefined
        if ((pointCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            pointCountTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const pointCountTmpResult : number | undefined = pointCountTmpBuf
        let value : matrix4.PolyToPolyOptions = ({src: srcTmpResult, srcIndex: srcIndexTmpResult, dst: dstTmpResult, dstIndex: dstIndexTmpResult, pointCount: pointCountTmpResult} as matrix4.PolyToPolyOptions)
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
    export class Matrix4TransitInternal implements MaterializedBase,Matrix4Transit {
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
            const bufferValue0 : number = (retvalDeserializer.readNumber() as number)
            const bufferValue1 : number = (retvalDeserializer.readNumber() as number)
            const returnResult : [ number, number ] = ([bufferValue0, bufferValue1] as [ number, number ])
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

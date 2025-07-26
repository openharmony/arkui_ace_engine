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

import { Tuple_Number_Number } from "./arkui-synthetics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Point } from "./point"
export interface Matrix4Transit {
    copy(): Matrix4Transit
    invert(): Matrix4Transit
    combine(options: Matrix4Transit): Matrix4Transit
    translate(options: TranslateOption): Matrix4Transit
    scale(options: ScaleOption): Matrix4Transit
    skew(x: number, y: number): Matrix4Transit
    rotate(options: RotateOption): Matrix4Transit
    transformPoint(options: [ number, number ]): [ number, number ]
    setPolyToPoly(options: PolyToPolyOptions): Matrix4Transit
}
export class Matrix4TransitInternal implements MaterializedBase,Matrix4Transit {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_matrix4transit(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = Matrix4TransitInternal.ctor_matrix4transit()
        this.peer = new Finalizable(ctorPtr, Matrix4TransitInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Matrix4Transit_getFinalizer()
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
    public translate(options: TranslateOption): Matrix4Transit {
        const options_casted = options as (TranslateOption)
        return this.translate_serialize(options_casted)
    }
    public scale(options: ScaleOption): Matrix4Transit {
        const options_casted = options as (ScaleOption)
        return this.scale_serialize(options_casted)
    }
    public skew(x: number, y: number): Matrix4Transit {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.skew_serialize(x_casted, y_casted)
    }
    public rotate(options: RotateOption): Matrix4Transit {
        const options_casted = options as (RotateOption)
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
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_copy(this.peer!.ptr)
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private invert_serialize(): Matrix4Transit {
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_invert(this.peer!.ptr)
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private combine_serialize(options: Matrix4Transit): Matrix4Transit {
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_combine(this.peer!.ptr, toPeerPtr(options))
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private translate_serialize(options: TranslateOption): Matrix4Transit {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOption(options)
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_translate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private scale_serialize(options: ScaleOption): Matrix4Transit {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScaleOption(options)
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_scale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private skew_serialize(x: number, y: number): Matrix4Transit {
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_skew(this.peer!.ptr, x, y)
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private rotate_serialize(options: RotateOption): Matrix4Transit {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRotateOption(options)
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_rotate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    private transformPoint_serialize(options: [ number, number ]): [ number, number ] {
        const thisSerializer : Serializer = Serializer.hold()
        const options_0  = options[0]
        thisSerializer.writeNumber(options_0)
        const options_1  = options[1]
        thisSerializer.writeNumber(options_1)
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_transformPoint(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_value0 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value1 : number = (retvalDeserializer.readNumber() as number)
        const returnResult : [ number, number ] = ([buffer_value0, buffer_value1] as [ number, number ])
        return returnResult
    }
    private setPolyToPoly_serialize(options: PolyToPolyOptions): Matrix4Transit {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePolyToPolyOptions(options)
        const retval  = ArkUIGeneratedNativeModule._Matrix4Transit_setPolyToPoly(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix4Transit = Matrix4TransitInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): Matrix4TransitInternal {
        const obj : Matrix4TransitInternal = new Matrix4TransitInternal()
        obj.peer = new Finalizable(ptr, Matrix4TransitInternal.getFinalizer())
        return obj
    }
}
export interface TranslateOption {
    x?: number;
    y?: number;
    z?: number;
}
export interface ScaleOption {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number;
    centerY?: number;
}
export interface RotateOption {
    x?: number;
    y?: number;
    z?: number;
    centerX?: number;
    centerY?: number;
    angle?: number;
}
export interface PolyToPolyOptions {
    src: Array<Point>;
    srcIndex?: number;
    dst: Array<Point>;
    dstIndex?: number;
    pointCount?: number;
}

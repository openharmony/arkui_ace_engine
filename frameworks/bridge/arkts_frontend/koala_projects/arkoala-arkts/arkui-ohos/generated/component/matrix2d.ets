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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { LengthMetricsUnit } from "arkui.Graphics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
export class Matrix2DInternal {
    public static fromPtr(ptr: KPointer): Matrix2D {
        return new Matrix2D(false, ptr)
    }
}
export class Matrix2D implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scaleX(): double | undefined {
        return this.getScaleX()
    }
    set scaleX(scaleX: double | undefined) {
        this.setScaleX(scaleX)
    }
    get scaleY(): double | undefined {
        return this.getScaleY()
    }
    set scaleY(scaleY: double | undefined) {
        this.setScaleY(scaleY)
    }
    get rotateX(): double | undefined {
        return this.getRotateX()
    }
    set rotateX(rotateX: double | undefined) {
        this.setRotateX(rotateX)
    }
    get rotateY(): double | undefined {
        return this.getRotateY()
    }
    set rotateY(rotateY: double | undefined) {
        this.setRotateY(rotateY)
    }
    get translateX(): double | undefined {
        return this.getTranslateX()
    }
    set translateX(translateX: double | undefined) {
        this.setTranslateX(translateX)
    }
    get translateY(): double | undefined {
        return this.getTranslateY()
    }
    set translateY(translateY: double | undefined) {
        this.setTranslateY(translateY)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Matrix2D.getFinalizer())
    }
    constructor(unit?: LengthMetricsUnit) {
        this(false, Matrix2D.construct(unit))
    }
    static construct(unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Matrix2D_getFinalizer()
    }
    public identity(): Matrix2D {
        return this.identity_serialize()
    }
    public invert(): Matrix2D {
        return this.invert_serialize()
    }
    public rotate(degree: double, rx?: double, ry?: double): Matrix2D {
        const degree_casted = degree as (double)
        const rx_casted = rx as (double | undefined)
        const ry_casted = ry as (double | undefined)
        return this.rotate_serialize(degree_casted, rx_casted, ry_casted)
    }
    public translate(tx?: double, ty?: double): Matrix2D {
        const tx_casted = tx as (double | undefined)
        const ty_casted = ty as (double | undefined)
        return this.translate_serialize(tx_casted, ty_casted)
    }
    public scale(sx?: double, sy?: double): Matrix2D {
        const sx_casted = sx as (double | undefined)
        const sy_casted = sy as (double | undefined)
        return this.scale_serialize(sx_casted, sy_casted)
    }
    private getScaleX(): double | undefined {
        return this.getScaleX_serialize()
    }
    private setScaleX(scaleX: double | undefined): void {
        const scaleX_casted = scaleX as (double | undefined)
        this.setScaleX_serialize(scaleX_casted)
        return
    }
    private getScaleY(): double | undefined {
        return this.getScaleY_serialize()
    }
    private setScaleY(scaleY: double | undefined): void {
        const scaleY_casted = scaleY as (double | undefined)
        this.setScaleY_serialize(scaleY_casted)
        return
    }
    private getRotateX(): double | undefined {
        return this.getRotateX_serialize()
    }
    private setRotateX(rotateX: double | undefined): void {
        const rotateX_casted = rotateX as (double | undefined)
        this.setRotateX_serialize(rotateX_casted)
        return
    }
    private getRotateY(): double | undefined {
        return this.getRotateY_serialize()
    }
    private setRotateY(rotateY: double | undefined): void {
        const rotateY_casted = rotateY as (double | undefined)
        this.setRotateY_serialize(rotateY_casted)
        return
    }
    private getTranslateX(): double | undefined {
        return this.getTranslateX_serialize()
    }
    private setTranslateX(translateX: double | undefined): void {
        const translateX_casted = translateX as (double | undefined)
        this.setTranslateX_serialize(translateX_casted)
        return
    }
    private getTranslateY(): double | undefined {
        return this.getTranslateY_serialize()
    }
    private setTranslateY(translateY: double | undefined): void {
        const translateY_casted = translateY as (double | undefined)
        this.setTranslateY_serialize(translateY_casted)
        return
    }
    identity_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_identity(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    invert_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_invert(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    rotate_serialize(degree: double, rx?: double, ry?: double): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (rx !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rxTmpValue  = rx!
            thisSerializer.writeFloat64(rxTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (ry !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const ryTmpValue  = ry!
            thisSerializer.writeFloat64(ryTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_rotate(this.peer!.ptr, degree, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    translate_serialize(tx?: double, ty?: double): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (tx !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const txTmpValue  = tx!
            thisSerializer.writeFloat64(txTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (ty !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const tyTmpValue  = ty!
            thisSerializer.writeFloat64(tyTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_translate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    scale_serialize(sx?: double, sy?: double): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (sx !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sxTmpValue  = sx!
            thisSerializer.writeFloat64(sxTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (sy !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const syTmpValue  = sy!
            thisSerializer.writeFloat64(syTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_scale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private getScaleX_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setScaleX_serialize(scaleX: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scaleX !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scaleXTmpValue  = scaleX!
            thisSerializer.writeFloat64(scaleXTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setScaleX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getScaleY_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setScaleY_serialize(scaleY: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scaleY !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scaleYTmpValue  = scaleY!
            thisSerializer.writeFloat64(scaleYTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setScaleY(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotateX_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setRotateX_serialize(rotateX: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (rotateX !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rotateXTmpValue  = rotateX!
            thisSerializer.writeFloat64(rotateXTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setRotateX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotateY_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setRotateY_serialize(rotateY: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (rotateY !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rotateYTmpValue  = rotateY!
            thisSerializer.writeFloat64(rotateYTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setRotateY(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslateX_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setTranslateX_serialize(translateX: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (translateX !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const translateXTmpValue  = translateX!
            thisSerializer.writeFloat64(translateXTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setTranslateX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslateY_serialize(): double | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : double | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readFloat64()
        }
        const returnResult : double | undefined = buffer
        return returnResult
    }
    private setTranslateY_serialize(translateY: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (translateY !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const translateYTmpValue  = translateY!
            thisSerializer.writeFloat64(translateYTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setTranslateY(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class Matrix2D_serializer {
    public static write(buffer: SerializerBase, value: Matrix2D): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Matrix2D {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return Matrix2DInternal.fromPtr(ptr)
    }
}

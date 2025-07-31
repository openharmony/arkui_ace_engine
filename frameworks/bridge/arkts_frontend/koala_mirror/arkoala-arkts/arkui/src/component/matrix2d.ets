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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { LengthMetricsUnit } from "./../generated/arkui.Graphics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
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
    get scaleX(): number | undefined {
        return this.getScaleX()
    }
    set scaleX(scaleX: number | undefined) {
        const scaleX_NonNull  = (scaleX as number | undefined)
        this.setScaleX(scaleX_NonNull)
    }
    get rotateY(): number | undefined {
        return this.getRotateY()
    }
    set rotateY(rotateY: number | undefined) {
        const rotateY_NonNull  = (rotateY as number | undefined)
        this.setRotateY(rotateY_NonNull)
    }
    get rotateX(): number | undefined {
        return this.getRotateX()
    }
    set rotateX(rotateX: number | undefined) {
        const rotateX_NonNull  = (rotateX as number | undefined)
        this.setRotateX(rotateX_NonNull)
    }
    get scaleY(): number | undefined {
        return this.getScaleY()
    }
    set scaleY(scaleY: number | undefined) {
        const scaleY_NonNull  = (scaleY as number | undefined)
        this.setScaleY(scaleY_NonNull)
    }
    get translateX(): number | undefined {
        return this.getTranslateX()
    }
    set translateX(translateX: number | undefined) {
        const translateX_NonNull  = (translateX as number | undefined)
        this.setTranslateX(translateX_NonNull)
    }
    get translateY(): number | undefined {
        return this.getTranslateY()
    }
    set translateY(translateY: number | undefined) {
        const translateY_NonNull  = (translateY as number | undefined)
        this.setTranslateY(translateY_NonNull)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Matrix2D.getFinalizer())
    }
    constructor() {
        this(false, Matrix2D.construct0())
    }
    constructor(unit: LengthMetricsUnit) {
        this(false, Matrix2D.construct1(unit))
    }
    static construct0(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_construct0()
        return retval
    }
    static construct1(unit: LengthMetricsUnit): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_construct1(TypeChecker.LengthMetricsUnit_ToNumeric(unit))
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
    public rotate(degree: number, rx?: number, ry?: number): Matrix2D {
        const degree_casted = degree as (number)
        const rx_casted = rx as (number | undefined)
        const ry_casted = ry as (number | undefined)
        return this.rotate_serialize(degree_casted, rx_casted, ry_casted)
    }
    public translate(tx?: number, ty?: number): Matrix2D {
        const tx_casted = tx as (number | undefined)
        const ty_casted = ty as (number | undefined)
        return this.translate_serialize(tx_casted, ty_casted)
    }
    public scale(sx?: number, sy?: number): Matrix2D {
        const sx_casted = sx as (number | undefined)
        const sy_casted = sy as (number | undefined)
        return this.scale_serialize(sx_casted, sy_casted)
    }
    private getScaleX(): number | undefined {
        return this.getScaleX_serialize()
    }
    private setScaleX(scaleX: number | undefined): void {
        const scaleX_casted = scaleX as (number | undefined)
        this.setScaleX_serialize(scaleX_casted)
        return
    }
    private getRotateY(): number | undefined {
        return this.getRotateY_serialize()
    }
    private setRotateY(rotateY: number | undefined): void {
        const rotateY_casted = rotateY as (number | undefined)
        this.setRotateY_serialize(rotateY_casted)
        return
    }
    private getRotateX(): number | undefined {
        return this.getRotateX_serialize()
    }
    private setRotateX(rotateX: number | undefined): void {
        const rotateX_casted = rotateX as (number | undefined)
        this.setRotateX_serialize(rotateX_casted)
        return
    }
    private getScaleY(): number | undefined {
        return this.getScaleY_serialize()
    }
    private setScaleY(scaleY: number | undefined): void {
        const scaleY_casted = scaleY as (number | undefined)
        this.setScaleY_serialize(scaleY_casted)
        return
    }
    private getTranslateX(): number | undefined {
        return this.getTranslateX_serialize()
    }
    private setTranslateX(translateX: number | undefined): void {
        const translateX_casted = translateX as (number | undefined)
        this.setTranslateX_serialize(translateX_casted)
        return
    }
    private getTranslateY(): number | undefined {
        return this.getTranslateY_serialize()
    }
    private setTranslateY(translateY: number | undefined): void {
        const translateY_casted = translateY as (number | undefined)
        this.setTranslateY_serialize(translateY_casted)
        return
    }
    private identity_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_identity(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private invert_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_invert(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private rotate_serialize(degree: number, rx?: number, ry?: number): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let rx_type : int32 = RuntimeType.UNDEFINED
        rx_type = runtimeType(rx)
        thisSerializer.writeInt8((rx_type).toChar())
        if ((rx_type) != (RuntimeType.UNDEFINED)) {
            const rx_value  = rx!
            thisSerializer.writeNumber(rx_value)
        }
        let ry_type : int32 = RuntimeType.UNDEFINED
        ry_type = runtimeType(ry)
        thisSerializer.writeInt8((ry_type).toChar())
        if ((ry_type) != (RuntimeType.UNDEFINED)) {
            const ry_value  = ry!
            thisSerializer.writeNumber(ry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_rotate(this.peer!.ptr, degree, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private translate_serialize(tx?: number, ty?: number): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let tx_type : int32 = RuntimeType.UNDEFINED
        tx_type = runtimeType(tx)
        thisSerializer.writeInt8((tx_type).toChar())
        if ((tx_type) != (RuntimeType.UNDEFINED)) {
            const tx_value  = tx!
            thisSerializer.writeNumber(tx_value)
        }
        let ty_type : int32 = RuntimeType.UNDEFINED
        ty_type = runtimeType(ty)
        thisSerializer.writeInt8((ty_type).toChar())
        if ((ty_type) != (RuntimeType.UNDEFINED)) {
            const ty_value  = ty!
            thisSerializer.writeNumber(ty_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_translate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private scale_serialize(sx?: number, sy?: number): Matrix2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let sx_type : int32 = RuntimeType.UNDEFINED
        sx_type = runtimeType(sx)
        thisSerializer.writeInt8((sx_type).toChar())
        if ((sx_type) != (RuntimeType.UNDEFINED)) {
            const sx_value  = sx!
            thisSerializer.writeNumber(sx_value)
        }
        let sy_type : int32 = RuntimeType.UNDEFINED
        sy_type = runtimeType(sy)
        thisSerializer.writeInt8((sy_type).toChar())
        if ((sy_type) != (RuntimeType.UNDEFINED)) {
            const sy_value  = sy!
            thisSerializer.writeNumber(sy_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_scale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private getScaleX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setScaleX_serialize(scaleX: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scaleX_type : int32 = RuntimeType.UNDEFINED
        scaleX_type = runtimeType(scaleX)
        thisSerializer.writeInt8((scaleX_type).toChar())
        if ((scaleX_type) != (RuntimeType.UNDEFINED)) {
            const scaleX_value  = scaleX!
            thisSerializer.writeNumber(scaleX_value)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setScaleX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotateY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setRotateY_serialize(rotateY: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let rotateY_type : int32 = RuntimeType.UNDEFINED
        rotateY_type = runtimeType(rotateY)
        thisSerializer.writeInt8((rotateY_type).toChar())
        if ((rotateY_type) != (RuntimeType.UNDEFINED)) {
            const rotateY_value  = rotateY!
            thisSerializer.writeNumber(rotateY_value)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setRotateY(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotateX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setRotateX_serialize(rotateX: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let rotateX_type : int32 = RuntimeType.UNDEFINED
        rotateX_type = runtimeType(rotateX)
        thisSerializer.writeInt8((rotateX_type).toChar())
        if ((rotateX_type) != (RuntimeType.UNDEFINED)) {
            const rotateX_value  = rotateX!
            thisSerializer.writeNumber(rotateX_value)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setRotateX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getScaleY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setScaleY_serialize(scaleY: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scaleY_type : int32 = RuntimeType.UNDEFINED
        scaleY_type = runtimeType(scaleY)
        thisSerializer.writeInt8((scaleY_type).toChar())
        if ((scaleY_type) != (RuntimeType.UNDEFINED)) {
            const scaleY_value  = scaleY!
            thisSerializer.writeNumber(scaleY_value)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setScaleY(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslateX_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateX(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setTranslateX_serialize(translateX: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let translateX_type : int32 = RuntimeType.UNDEFINED
        translateX_type = runtimeType(translateX)
        thisSerializer.writeInt8((translateX_type).toChar())
        if ((translateX_type) != (RuntimeType.UNDEFINED)) {
            const translateX_value  = translateX!
            thisSerializer.writeNumber(translateX_value)
        }
        ArkUIGeneratedNativeModule._Matrix2D_setTranslateX(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslateY_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateY(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : number | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : number | undefined = buffer
        return returnResult
    }
    private setTranslateY_serialize(translateY: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let translateY_type : int32 = RuntimeType.UNDEFINED
        translateY_type = runtimeType(translateY)
        thisSerializer.writeInt8((translateY_type).toChar())
        if ((translateY_type) != (RuntimeType.UNDEFINED)) {
            const translateY_value  = translateY!
            thisSerializer.writeNumber(translateY_value)
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

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

import { LengthMetricsUnit } from "../Graphics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
export class Matrix2DInternal {
    public static fromPtr(ptr: KPointer): Matrix2D {
        const obj : Matrix2D = new Matrix2D()
        obj.peer = new Finalizable(ptr, Matrix2D.getFinalizer())
        return obj
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
        const scaleX_NonNull  = (scaleX as number)
        this.setScaleX(scaleX_NonNull)
    }
    get rotateY(): number | undefined {
        return this.getRotateY()
    }
    set rotateY(rotateY: number | undefined) {
        const rotateY_NonNull  = (rotateY as number)
        this.setRotateY(rotateY_NonNull)
    }
    get rotateX(): number | undefined {
        return this.getRotateX()
    }
    set rotateX(rotateX: number | undefined) {
        const rotateX_NonNull  = (rotateX as number)
        this.setRotateX(rotateX_NonNull)
    }
    get scaleY(): number | undefined {
        return this.getScaleY()
    }
    set scaleY(scaleY: number | undefined) {
        const scaleY_NonNull  = (scaleY as number)
        this.setScaleY(scaleY_NonNull)
    }
    get translateX(): number | undefined {
        return this.getTranslateX()
    }
    set translateX(translateX: number | undefined) {
        const translateX_NonNull  = (translateX as number)
        this.setTranslateX(translateX_NonNull)
    }
    get translateY(): number | undefined {
        return this.getTranslateY()
    }
    set translateY(translateY: number | undefined) {
        const translateY_NonNull  = (translateY as number)
        this.setTranslateY(translateY_NonNull)
    }
    static ctor_matrix2d(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = Matrix2D.ctor_matrix2d()
        this.peer = new Finalizable(ctorPtr, Matrix2D.getFinalizer())
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
    public multiply(other?: Matrix2D): Matrix2D {
        const other_casted = other as (Matrix2D | undefined)
        return this.multiply_serialize(other_casted)
    }
    public rotate(degree?: number | undefined | number, rx?: number, ry?: number): Matrix2D {
        const degree_type = runtimeType(degree)
        const rx_type = runtimeType(rx)
        const ry_type = runtimeType(ry)
        if (((RuntimeType.NUMBER == degree_type) || (RuntimeType.UNDEFINED == degree_type)) && ((RuntimeType.NUMBER == rx_type) || (RuntimeType.UNDEFINED == rx_type)) && (RuntimeType.UNDEFINED == ry_type)) {
            const rx_casted = degree as (number | undefined)
            const ry_casted = rx as (number | undefined)
            return this.rotate0_serialize(rx_casted, ry_casted)
        }
        if ((RuntimeType.NUMBER == degree_type) && ((RuntimeType.NUMBER == rx_type) || (RuntimeType.UNDEFINED == rx_type)) && ((RuntimeType.NUMBER == ry_type) || (RuntimeType.UNDEFINED == ry_type))) {
            const degree_casted = degree as (number)
            const rx_casted = rx as (number | undefined)
            const ry_casted = ry as (number | undefined)
            return this.rotate1_serialize(degree_casted, rx_casted, ry_casted)
        }
        throw new Error("Can not select appropriate overload")
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
    private getScaleX(): number {
        return this.getScaleX_serialize()
    }
    private setScaleX(scaleX: number): void {
        const scaleX_casted = scaleX as (number)
        this.setScaleX_serialize(scaleX_casted)
        return
    }
    private getRotateY(): number {
        return this.getRotateY_serialize()
    }
    private setRotateY(rotateY: number): void {
        const rotateY_casted = rotateY as (number)
        this.setRotateY_serialize(rotateY_casted)
        return
    }
    private getRotateX(): number {
        return this.getRotateX_serialize()
    }
    private setRotateX(rotateX: number): void {
        const rotateX_casted = rotateX as (number)
        this.setRotateX_serialize(rotateX_casted)
        return
    }
    private getScaleY(): number {
        return this.getScaleY_serialize()
    }
    private setScaleY(scaleY: number): void {
        const scaleY_casted = scaleY as (number)
        this.setScaleY_serialize(scaleY_casted)
        return
    }
    private getTranslateX(): number {
        return this.getTranslateX_serialize()
    }
    private setTranslateX(translateX: number): void {
        const translateX_casted = translateX as (number)
        this.setTranslateX_serialize(translateX_casted)
        return
    }
    private getTranslateY(): number {
        return this.getTranslateY_serialize()
    }
    private setTranslateY(translateY: number): void {
        const translateY_casted = translateY as (number)
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
    private multiply_serialize(other?: Matrix2D): Matrix2D {
        const thisSerializer : Serializer = Serializer.hold()
        let other_type : int32 = RuntimeType.UNDEFINED
        other_type = runtimeType(other)
        thisSerializer.writeInt8(other_type as int32)
        if ((RuntimeType.UNDEFINED) != (other_type)) {
            const other_value  = other!
            thisSerializer.writeMatrix2D(other_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_multiply(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private rotate0_serialize(rx?: number, ry?: number): Matrix2D {
        const thisSerializer : Serializer = Serializer.hold()
        let rx_type : int32 = RuntimeType.UNDEFINED
        rx_type = runtimeType(rx)
        thisSerializer.writeInt8(rx_type as int32)
        if ((RuntimeType.UNDEFINED) != (rx_type)) {
            const rx_value  = rx!
            thisSerializer.writeNumber(rx_value)
        }
        let ry_type : int32 = RuntimeType.UNDEFINED
        ry_type = runtimeType(ry)
        thisSerializer.writeInt8(ry_type as int32)
        if ((RuntimeType.UNDEFINED) != (ry_type)) {
            const ry_value  = ry!
            thisSerializer.writeNumber(ry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_rotate0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private rotate1_serialize(degree: number, rx?: number, ry?: number): Matrix2D {
        const thisSerializer : Serializer = Serializer.hold()
        let rx_type : int32 = RuntimeType.UNDEFINED
        rx_type = runtimeType(rx)
        thisSerializer.writeInt8(rx_type as int32)
        if ((RuntimeType.UNDEFINED) != (rx_type)) {
            const rx_value  = rx!
            thisSerializer.writeNumber(rx_value)
        }
        let ry_type : int32 = RuntimeType.UNDEFINED
        ry_type = runtimeType(ry)
        thisSerializer.writeInt8(ry_type as int32)
        if ((RuntimeType.UNDEFINED) != (ry_type)) {
            const ry_value  = ry!
            thisSerializer.writeNumber(ry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_rotate1(this.peer!.ptr, degree, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private translate_serialize(tx?: number, ty?: number): Matrix2D {
        const thisSerializer : Serializer = Serializer.hold()
        let tx_type : int32 = RuntimeType.UNDEFINED
        tx_type = runtimeType(tx)
        thisSerializer.writeInt8(tx_type as int32)
        if ((RuntimeType.UNDEFINED) != (tx_type)) {
            const tx_value  = tx!
            thisSerializer.writeNumber(tx_value)
        }
        let ty_type : int32 = RuntimeType.UNDEFINED
        ty_type = runtimeType(ty)
        thisSerializer.writeInt8(ty_type as int32)
        if ((RuntimeType.UNDEFINED) != (ty_type)) {
            const ty_value  = ty!
            thisSerializer.writeNumber(ty_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_translate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private scale_serialize(sx?: number, sy?: number): Matrix2D {
        const thisSerializer : Serializer = Serializer.hold()
        let sx_type : int32 = RuntimeType.UNDEFINED
        sx_type = runtimeType(sx)
        thisSerializer.writeInt8(sx_type as int32)
        if ((RuntimeType.UNDEFINED) != (sx_type)) {
            const sx_value  = sx!
            thisSerializer.writeNumber(sx_value)
        }
        let sy_type : int32 = RuntimeType.UNDEFINED
        sy_type = runtimeType(sy)
        thisSerializer.writeInt8(sy_type as int32)
        if ((RuntimeType.UNDEFINED) != (sy_type)) {
            const sy_value  = sy!
            thisSerializer.writeNumber(sy_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_scale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private getScaleX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleX(this.peer!.ptr)
        return retval
    }
    private setScaleX_serialize(scaleX: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setScaleX(this.peer!.ptr, scaleX)
    }
    private getRotateY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateY(this.peer!.ptr)
        return retval
    }
    private setRotateY_serialize(rotateY: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setRotateY(this.peer!.ptr, rotateY)
    }
    private getRotateX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getRotateX(this.peer!.ptr)
        return retval
    }
    private setRotateX_serialize(rotateX: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setRotateX(this.peer!.ptr, rotateX)
    }
    private getScaleY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getScaleY(this.peer!.ptr)
        return retval
    }
    private setScaleY_serialize(scaleY: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setScaleY(this.peer!.ptr, scaleY)
    }
    private getTranslateX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateX(this.peer!.ptr)
        return retval
    }
    private setTranslateX_serialize(translateX: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setTranslateX(this.peer!.ptr, translateX)
    }
    private getTranslateY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._Matrix2D_getTranslateY(this.peer!.ptr)
        return retval
    }
    private setTranslateY_serialize(translateY: number): void {
        ArkUIGeneratedNativeModule._Matrix2D_setTranslateY(this.peer!.ptr, translateY)
    }
}

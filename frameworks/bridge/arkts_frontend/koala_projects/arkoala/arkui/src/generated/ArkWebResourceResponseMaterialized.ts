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

import { Resource } from "./ArkResourceInterfaces"
import { Header } from "./ArkWebInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class WebResourceResponseInternal {
    public static fromPtr(ptr: KPointer): WebResourceResponse {
        const obj: WebResourceResponse = new WebResourceResponse()
        obj.peer = new Finalizable(ptr, WebResourceResponse.getFinalizer())
        return obj
    }
}
export class WebResourceResponse implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourceresponse(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebResourceResponse.ctor_webresourceresponse()
        this.peer = new Finalizable(ctorPtr, WebResourceResponse.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceResponse_getFinalizer()
    }
    public getResponseData(): string {
        return this.getResponseData_serialize()
    }
    public getResponseDataEx(): string | number | ArrayBuffer | Resource | undefined {
        return this.getResponseDataEx_serialize()
    }
    public getResponseEncoding(): string {
        return this.getResponseEncoding_serialize()
    }
    public getResponseMimeType(): string {
        return this.getResponseMimeType_serialize()
    }
    public getReasonMessage(): string {
        return this.getReasonMessage_serialize()
    }
    public getResponseHeader(): Array<Header> {
        return this.getResponseHeader_serialize()
    }
    public getResponseCode(): number {
        return this.getResponseCode_serialize()
    }
    public setResponseData(data: string | number | Resource | ArrayBuffer): void {
        const data_casted = data as (string | number | Resource | ArrayBuffer)
        this?.setResponseData_serialize(data_casted)
        return
    }
    public setResponseEncoding(encoding: string): void {
        const encoding_casted = encoding as (string)
        this?.setResponseEncoding_serialize(encoding_casted)
        return
    }
    public setResponseMimeType(mimeType: string): void {
        const mimeType_casted = mimeType as (string)
        this?.setResponseMimeType_serialize(mimeType_casted)
        return
    }
    public setReasonMessage(reason: string): void {
        const reason_casted = reason as (string)
        this?.setReasonMessage_serialize(reason_casted)
        return
    }
    public setResponseHeader(header: Array<Header>): void {
        const header_casted = header as (Array<Header>)
        this?.setResponseHeader_serialize(header_casted)
        return
    }
    public setResponseCode(code: number): void {
        const code_casted = code as (number)
        this?.setResponseCode_serialize(code_casted)
        return
    }
    public setResponseIsReady(IsReady: boolean): void {
        const IsReady_casted = IsReady as (boolean)
        this?.setResponseIsReady_serialize(IsReady_casted)
        return
    }
    public getResponseIsReady(): boolean {
        return this.getResponseIsReady_serialize()
    }
    private getResponseData_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseData(this.peer!.ptr)
        return retval
    }
    private getResponseDataEx_serialize(): string | number | ArrayBuffer | Resource | undefined {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseDataEx(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getResponseEncoding_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseEncoding(this.peer!.ptr)
        return retval
    }
    private getResponseMimeType_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseMimeType(this.peer!.ptr)
        return retval
    }
    private getReasonMessage_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getReasonMessage(this.peer!.ptr)
        return retval
    }
    private getResponseHeader_serialize(): Array<Header> {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseHeader(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHeader()
        }
        const returnResult: Array<Header> = buffer
        return returnResult
    }
    private getResponseCode_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseCode(this.peer!.ptr)
        return retval
    }
    private setResponseData_serialize(data: string | number | Resource | ArrayBuffer): void {
        const thisSerializer: Serializer = Serializer.hold()
        let data_type: int32 = RuntimeType.UNDEFINED
        data_type = runtimeType(data)
        if (RuntimeType.STRING == data_type) {
            thisSerializer.writeInt8(0)
            const data_0 = unsafeCast<string>(data)
            thisSerializer.writeString(data_0)
        }
        else if (RuntimeType.NUMBER == data_type) {
            thisSerializer.writeInt8(1)
            const data_1 = unsafeCast<number>(data)
            thisSerializer.writeNumber(data_1)
        }
        else if (((RuntimeType.OBJECT) == (data_type)) && ((data!.hasOwnProperty("bundleName")))) {
            thisSerializer.writeInt8(2)
            const data_2 = unsafeCast<Resource>(data)
            thisSerializer.writeResource(data_2)
        }
        else if (data instanceof ArrayBuffer) {
            thisSerializer.writeInt8(3)
            const data_3 = unsafeCast<ArrayBuffer>(data)
            thisSerializer.writeBuffer(data_3)
        }
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseData(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setResponseEncoding_serialize(encoding: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseEncoding(this.peer!.ptr, encoding)
    }
    private setResponseMimeType_serialize(mimeType: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseMimeType(this.peer!.ptr, mimeType)
    }
    private setReasonMessage_serialize(reason: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setReasonMessage(this.peer!.ptr, reason)
    }
    private setResponseHeader_serialize(header: Array<Header>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(header.length)
        for (let i = 0; i < header.length; i++) {
            const header_element: Header = header[i]
            thisSerializer.writeHeader(header_element)
        }
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseHeader(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setResponseCode_serialize(code: number): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseCode(this.peer!.ptr, code)
    }
    private setResponseIsReady_serialize(IsReady: boolean): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseIsReady(this.peer!.ptr, +IsReady)
    }
    private getResponseIsReady_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseIsReady(this.peer!.ptr)
        return retval
    }
}

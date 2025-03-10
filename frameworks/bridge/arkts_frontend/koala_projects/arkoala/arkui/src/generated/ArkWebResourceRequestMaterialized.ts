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

import { Header } from "./ArkWebInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class WebResourceRequestInternal {
    public static fromPtr(ptr: KPointer): WebResourceRequest {
        const obj: WebResourceRequest = new WebResourceRequest()
        obj.peer = new Finalizable(ptr, WebResourceRequest.getFinalizer())
        return obj
    }
}
export class WebResourceRequest implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourcerequest(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebResourceRequest.ctor_webresourcerequest()
        this.peer = new Finalizable(ctorPtr, WebResourceRequest.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceRequest_getFinalizer()
    }
    public getRequestHeader(): Array<Header> {
        return this.getRequestHeader_serialize()
    }
    public getRequestUrl(): string {
        return this.getRequestUrl_serialize()
    }
    public isRequestGesture(): boolean {
        return this.isRequestGesture_serialize()
    }
    public isMainFrame(): boolean {
        return this.isMainFrame_serialize()
    }
    public isRedirect(): boolean {
        return this.isRedirect_serialize()
    }
    public getRequestMethod(): string {
        return this.getRequestMethod_serialize()
    }
    private getRequestHeader_serialize(): Array<Header> {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestHeader(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHeader()
        }
        const returnResult: Array<Header> = buffer
        return returnResult
    }
    private getRequestUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestUrl(this.peer!.ptr)
        return retval
    }
    private isRequestGesture_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isRequestGesture(this.peer!.ptr)
        return retval
    }
    private isMainFrame_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isMainFrame(this.peer!.ptr)
        return retval
    }
    private isRedirect_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isRedirect(this.peer!.ptr)
        return retval
    }
    private getRequestMethod_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestMethod(this.peer!.ptr)
        return retval
    }
}

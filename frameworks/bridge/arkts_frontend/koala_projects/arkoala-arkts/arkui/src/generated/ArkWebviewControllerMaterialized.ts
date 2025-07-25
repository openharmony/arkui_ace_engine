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
import { WebHeader } from "./ArkArkuiExternalInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class WebviewControllerInternal {
    public static fromPtr(ptr: KPointer): WebviewController {
        const obj : WebviewController = new WebviewController()
        obj.peer = new Finalizable(ptr, WebviewController.getFinalizer())
        return obj
    }
}
export class WebviewController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webviewcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebviewController_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = WebviewController.ctor_webviewcontroller()
        this.peer = new Finalizable(ctorPtr, WebviewController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebviewController_getFinalizer()
    }
    public static initializeWebEngine(): void {
        WebviewController.initializeWebEngine_serialize()
        return
    }
    public loadUrl(url: string | Resource, headers?: Array<WebHeader>): void {
        const url_casted = url as (string | Resource)
        const headers_casted = headers as (Array<WebHeader> | undefined)
        this.loadUrl_serialize(url_casted, headers_casted)
        return
    }
    private static initializeWebEngine_serialize(): void {
        ArkUIGeneratedNativeModule._WebviewController_initializeWebEngine()
    }
    private loadUrl_serialize(url: string | Resource, headers?: Array<WebHeader>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let url_type : int32 = RuntimeType.UNDEFINED
        url_type = runtimeType(url)
        if (RuntimeType.STRING == url_type) {
            thisSerializer.writeInt8(0 as int32)
            const url_0  = url as string
            thisSerializer.writeString(url_0)
        }
        else if (RuntimeType.OBJECT == url_type) {
            thisSerializer.writeInt8(1 as int32)
            const url_1  = url as Resource
            thisSerializer.writeResource(url_1)
        }
        let headers_type : int32 = RuntimeType.UNDEFINED
        headers_type = runtimeType(headers)
        thisSerializer.writeInt8(headers_type as int32)
        if ((RuntimeType.UNDEFINED) != (headers_type)) {
            const headers_value  = headers!
            thisSerializer.writeInt32(headers_value.length as int32)
            for (let i = 0; i < headers_value.length; i++) {
                const headers_value_element : WebHeader = headers_value[i]
                thisSerializer.writeWebHeader(headers_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebviewController_loadUrl(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

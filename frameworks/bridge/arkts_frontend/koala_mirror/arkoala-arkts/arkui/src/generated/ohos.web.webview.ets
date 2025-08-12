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
import { Resource_serializer, Resource } from "./resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class webview_WebHeader_serializer {
    public static write(buffer: SerializerBase, value: webview.WebHeader): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHeaderKey  = value.headerKey
        valueSerializer.writeString(valueHolderForHeaderKey)
        const valueHolderForHeaderValue  = value.headerValue
        valueSerializer.writeString(valueHolderForHeaderValue)
    }
    public static read(buffer: DeserializerBase): webview.WebHeader {
        let valueDeserializer : DeserializerBase = buffer
        const headerKeyTmpResult : string = (valueDeserializer.readString() as string)
        const headerValueTmpResult : string = (valueDeserializer.readString() as string)
        let value : webview.WebHeader = ({headerKey: headerKeyTmpResult, headerValue: headerValueTmpResult} as webview.WebHeader)
        return value
    }
}
export class webview_WebviewController_serializer {
    public static write(buffer: SerializerBase, value: webview.WebviewController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): webview.WebviewController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return webview.WebviewControllerInternal.fromPtr(ptr)
    }
}
export namespace webview {
    export class WebviewControllerInternal {
        public static fromPtr(ptr: KPointer): webview.WebviewController {
            return new webview.WebviewController(ptr)
        }
    }
    export class WebviewController implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, WebviewController.getFinalizer())
        }
        constructor() {
            this(WebviewController.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._webview_WebviewController_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._webview_WebviewController_getFinalizer()
        }
        private static initializeWebEngine_serialize(): void {
            ArkUIGeneratedNativeModule._webview_WebviewController_initializeWebEngine()
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
        private loadUrl_serialize(url: string | Resource, headers?: Array<WebHeader>): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            if (url instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const urlForIdx0  = url as string
                thisSerializer.writeString(urlForIdx0)
            } else if (url instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const urlForIdx1  = url as Resource
                Resource_serializer.write(thisSerializer, urlForIdx1)
            }
            if (headers !== undefined) {
                thisSerializer.writeInt8(RuntimeType.OBJECT)
                const headersTmpValue  = headers!
                thisSerializer.writeInt32((headersTmpValue.length).toInt())
                for (let headersTmpValueCounterI = 0; headersTmpValueCounterI < headersTmpValue.length; headersTmpValueCounterI++) {
                    const headersTmpValueTmpElement : WebHeader = headersTmpValue[headersTmpValueCounterI]
                    webview_WebHeader_serializer.write(thisSerializer, headersTmpValueTmpElement)
                }
            } else {
                thisSerializer.writeInt8(RuntimeType.UNDEFINED)
            }
            ArkUIGeneratedNativeModule._webview_WebviewController_loadUrl(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
    }
    export interface WebHeader {
        headerKey: string;
        headerValue: string;
    }
}

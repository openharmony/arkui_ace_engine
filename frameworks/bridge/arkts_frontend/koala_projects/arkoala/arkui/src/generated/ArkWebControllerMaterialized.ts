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
import { Header, HitTestType } from "./ArkWebInterfaces"
import { WebCookie, WebCookieInternal } from "./ArkWebCookieMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class WebControllerInternal {
    public static fromPtr(ptr: KPointer): WebController {
        const obj: WebController = new WebController()
        obj.peer = new Finalizable(ptr, WebController.getFinalizer())
        return obj
    }
}
export class WebController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebController.ctor_webcontroller()
        this.peer = new Finalizable(ctorPtr, WebController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebController_getFinalizer()
    }
    public onInactive(): void {
        this?.onInactive_serialize()
        return
    }
    public onActive(): void {
        this?.onActive_serialize()
        return
    }
    public zoom(factor: number): void {
        const factor_casted = factor as (number)
        this?.zoom_serialize(factor_casted)
        return
    }
    public clearHistory(): void {
        this?.clearHistory_serialize()
        return
    }
    public runJavaScript(options: { script: string, callback_?: ((breakpoints: string) => void) }): undefined {
        const options_casted = options as ({ script: string, callback_?: ((breakpoints: string) => void) })
        return this.runJavaScript_serialize(options_casted)
    }
    public loadData(options: { data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string }): undefined {
        const options_casted = options as ({ data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string })
        return this.loadData_serialize(options_casted)
    }
    public loadUrl(options: { url: string | Resource, headers?: Array<Header> }): undefined {
        const options_casted = options as ({ url: string | Resource, headers?: Array<Header> })
        return this.loadUrl_serialize(options_casted)
    }
    public refresh(): undefined {
        return this.refresh_serialize()
    }
    public stop(): undefined {
        return this.stop_serialize()
    }
    public registerJavaScriptProxy(options: { object_: Object, name: string, methodList: Array<string> }): undefined {
        const options_casted = options as ({ object_: Object, name: string, methodList: Array<string> })
        return this.registerJavaScriptProxy_serialize(options_casted)
    }
    public deleteJavaScriptRegister(name: string): undefined {
        const name_casted = name as (string)
        return this.deleteJavaScriptRegister_serialize(name_casted)
    }
    public getHitTest(): HitTestType {
        return this.getHitTest_serialize()
    }
    public requestFocus(): undefined {
        return this.requestFocus_serialize()
    }
    public accessBackward(): boolean {
        return this.accessBackward_serialize()
    }
    public accessForward(): boolean {
        return this.accessForward_serialize()
    }
    public accessStep(step: number): boolean {
        const step_casted = step as (number)
        return this.accessStep_serialize(step_casted)
    }
    public backward(): undefined {
        return this.backward_serialize()
    }
    public forward(): undefined {
        return this.forward_serialize()
    }
    public getCookieManager(): WebCookie {
        return this.getCookieManager_serialize()
    }
    private onInactive_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_onInactive(this.peer!.ptr)
    }
    private onActive_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_onActive(this.peer!.ptr)
    }
    private zoom_serialize(factor: number): void {
        ArkUIGeneratedNativeModule._WebController_zoom(this.peer!.ptr, factor)
    }
    private clearHistory_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_clearHistory(this.peer!.ptr)
    }
    private runJavaScript_serialize(options: { script: string, callback_?: ((breakpoints: string) => void) }): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        const options_script = options.script
        thisSerializer.writeString(options_script)
        const options_callback_ = options.callback_
        let options_callback__type: int32 = RuntimeType.UNDEFINED
        options_callback__type = runtimeType(options_callback_)
        thisSerializer.writeInt8(options_callback__type)
        if ((RuntimeType.UNDEFINED) != (options_callback__type)) {
            const options_callback__value = options_callback_!
            thisSerializer.holdAndWriteCallback(options_callback__value)
        }
        const retval = ArkUIGeneratedNativeModule._WebController_runJavaScript(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private loadData_serialize(options: { data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string }): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        const options_data = options.data
        thisSerializer.writeString(options_data)
        const options_mimeType = options.mimeType
        thisSerializer.writeString(options_mimeType)
        const options_encoding = options.encoding
        thisSerializer.writeString(options_encoding)
        const options_baseUrl = options.baseUrl
        let options_baseUrl_type: int32 = RuntimeType.UNDEFINED
        options_baseUrl_type = runtimeType(options_baseUrl)
        thisSerializer.writeInt8(options_baseUrl_type)
        if ((RuntimeType.UNDEFINED) != (options_baseUrl_type)) {
            const options_baseUrl_value = options_baseUrl!
            thisSerializer.writeString(options_baseUrl_value)
        }
        const options_historyUrl = options.historyUrl
        let options_historyUrl_type: int32 = RuntimeType.UNDEFINED
        options_historyUrl_type = runtimeType(options_historyUrl)
        thisSerializer.writeInt8(options_historyUrl_type)
        if ((RuntimeType.UNDEFINED) != (options_historyUrl_type)) {
            const options_historyUrl_value = options_historyUrl!
            thisSerializer.writeString(options_historyUrl_value)
        }
        const retval = ArkUIGeneratedNativeModule._WebController_loadData(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private loadUrl_serialize(options: { url: string | Resource, headers?: Array<Header> }): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        const options_url = options.url
        let options_url_type: int32 = RuntimeType.UNDEFINED
        options_url_type = runtimeType(options_url)
        if (RuntimeType.STRING == options_url_type) {
            thisSerializer.writeInt8(0)
            const options_url_0 = unsafeCast<string>(options_url)
            thisSerializer.writeString(options_url_0)
        }
        else if (RuntimeType.OBJECT == options_url_type) {
            thisSerializer.writeInt8(1)
            const options_url_1 = unsafeCast<Resource>(options_url)
            thisSerializer.writeResource(options_url_1)
        }
        const options_headers = options.headers
        let options_headers_type: int32 = RuntimeType.UNDEFINED
        options_headers_type = runtimeType(options_headers)
        thisSerializer.writeInt8(options_headers_type)
        if ((RuntimeType.UNDEFINED) != (options_headers_type)) {
            const options_headers_value = options_headers!
            thisSerializer.writeInt32(options_headers_value.length)
            for (let i = 0; i < options_headers_value.length; i++) {
                const options_headers_value_element: Header = options_headers_value[i]
                thisSerializer.writeHeader(options_headers_value_element)
            }
        }
        const retval = ArkUIGeneratedNativeModule._WebController_loadUrl(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private refresh_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_refresh(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_stop(this.peer!.ptr)
        return retval
    }
    private registerJavaScriptProxy_serialize(options: { object_: Object, name: string, methodList: Array<string> }): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        const options_object_ = options.object_
        thisSerializer.writeCustomObject("Object", options_object_)
        const options_name = options.name
        thisSerializer.writeString(options_name)
        const options_methodList = options.methodList
        thisSerializer.writeInt32(options_methodList.length)
        for (let i = 0; i < options_methodList.length; i++) {
            const options_methodList_element: string = options_methodList[i]
            thisSerializer.writeString(options_methodList_element)
        }
        const retval = ArkUIGeneratedNativeModule._WebController_registerJavaScriptProxy(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private deleteJavaScriptRegister_serialize(name: string): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_deleteJavaScriptRegister(this.peer!.ptr, name)
        return retval
    }
    private getHitTest_serialize(): HitTestType {
        const retval = ArkUIGeneratedNativeModule._WebController_getHitTest(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private requestFocus_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_requestFocus(this.peer!.ptr)
        return retval
    }
    private accessBackward_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebController_accessBackward(this.peer!.ptr)
        return retval
    }
    private accessForward_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebController_accessForward(this.peer!.ptr)
        return retval
    }
    private accessStep_serialize(step: number): boolean {
        const retval = ArkUIGeneratedNativeModule._WebController_accessStep(this.peer!.ptr, step)
        return retval
    }
    private backward_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_backward(this.peer!.ptr)
        return retval
    }
    private forward_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._WebController_forward(this.peer!.ptr)
        return retval
    }
    private getCookieManager_serialize(): WebCookie {
        const retval = ArkUIGeneratedNativeModule._WebController_getCookieManager(this.peer!.ptr)
        const obj: WebCookie = WebCookieInternal.fromPtr(retval)
        return obj
    }
}

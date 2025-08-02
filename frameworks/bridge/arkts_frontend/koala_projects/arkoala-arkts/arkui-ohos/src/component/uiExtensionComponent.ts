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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Want } from "./ohos.app.ability"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ErrorCallback } from "./ohos.base"
import { BusinessError } from "#external"
import { Callback_TerminationInfo_Void, TerminationInfo } from "./embeddedComponent"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent } from "./arkui-custom"

export interface UIExtensionProxy {
    send(data: Map<string, Object>): void
    sendSync(data: Map<string, Object>): Map<string, Object>
    onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void) | undefined): void
    offSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void) | undefined): void
}
export class UIExtensionProxyInternal implements MaterializedBase,UIExtensionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uiextensionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UIExtensionProxyInternal.ctor_uiextensionproxy()
        this.peer = new Finalizable(ctorPtr, UIExtensionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public send(data: Map<string, Object>): void {
        const data_casted = data as (Map<string, Object>)
        this.send_serialize(data_casted)
        return
    }
    public sendSync(data: Map<string, Object>): Map<string, Object> {
        const data_casted = data as (Map<string, Object>)
        return this.sendSync_serialize(data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    on(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    private send_serialize(data: Map<string, Object>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.holdAndWriteObject(data_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Map<string, Object>): Map<string, Object> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.holdAndWriteObject(data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_size : int32 = retvalDeserializer.readInt32()
        let buffer : Map<string, Object> = new Map<string, Object>()
        // TODO: TS map resize
        for (let buffer_i = 0; buffer_i < buffer_size; buffer_i++) {
            const buffer_key : string = (retvalDeserializer.readString() as string)
            const buffer_value : Object = (retvalDeserializer.readObject() as Object)
            buffer.set(buffer_key, buffer_value)
        }
        const returnResult : Map<string, Object> = buffer
        return returnResult
    }
    private onAsyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        const obj : UIExtensionProxyInternal = new UIExtensionProxyInternal()
        obj.peer = new Finalizable(ptr, UIExtensionProxyInternal.getFinalizer())
        return obj
    }
}
export class ArkUIExtensionComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkUIExtensionComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIExtensionComponent_construct(peerId, flags)
        const _peer  = new ArkUIExtensionComponentPeer(_peerPtr, peerId, "UIExtensionComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUIExtensionComponentOptionsAttribute(want: Want, options?: UIExtensionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWant(want)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeUIExtensionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentInterface_setUIExtensionComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRemoteReadyAttribute(value: ((parameter: UIExtensionProxy) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReceiveAttribute(value: ((parameter: Map<string, Object>) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onResultAttribute(value: ((parameter: Literal_Number_code__want) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReleaseAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onRelease(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTerminatedAttribute(value: ((parameter: TerminationInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDrawReadyAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onDrawReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export enum WindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}
export interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string, ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
    windowModeFollowStrategy?: WindowModeFollowStrategy;
}
export type Callback_UIExtensionProxy_Void = (parameter: UIExtensionProxy) => void;
export type UIExtensionComponentInterface = (want: Want, options?: UIExtensionOptions) => UIExtensionComponentAttribute;
export interface UIExtensionComponentAttribute extends CommonMethod {
    onRemoteReady(value: ((parameter: UIExtensionProxy) => void) | undefined): this
    onReceive(value: ((parameter: Map<string, Object>) => void) | undefined): this
    onResult(value: ((parameter: Literal_Number_code__want) => void) | undefined): this
    onRelease(value: ((index: number) => void) | undefined): this
    onError(value: ErrorCallback | undefined): this
    onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this
    onDrawReady(value: (() => void) | undefined): this
}
export class ArkUIExtensionComponentStyle extends ArkCommonMethodStyle implements UIExtensionComponentAttribute {
    onRemoteReady_value?: ((parameter: UIExtensionProxy) => void) | undefined
    onReceive_value?: ((parameter: Map<string, Object>) => void) | undefined
    onResult_value?: ((parameter: Literal_Number_code__want) => void) | undefined
    onRelease_value?: ((index: number) => void) | undefined
    onError_value?: ErrorCallback | undefined
    onTerminated_value?: ((parameter: TerminationInfo) => void) | undefined
    onDrawReady_value?: (() => void) | undefined
    public onRemoteReady(value: ((parameter: UIExtensionProxy) => void) | undefined): this {
        return this
    }
    public onReceive(value: ((parameter: Map<string, Object>) => void) | undefined): this {
        return this
    }
    public onResult(value: ((parameter: Literal_Number_code__want) => void) | undefined): this {
        return this
    }
    public onRelease(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        return this
    }
    public onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this {
        return this
    }
    public onDrawReady(value: (() => void) | undefined): this {
        return this
        }
}
export type Callback_Map_String_Object_Void = (parameter: Map<string, Object>) => void;
export interface Literal_Number_code__want {
    code: number;
    want?: Want;
}
export type Callback_Literal_Number_code__want_Void = (parameter: Literal_Number_code__want) => void;
export class ArkUIExtensionComponentComponent extends ArkCommonMethodComponent implements UIExtensionComponentAttribute {
    getPeer(): ArkUIExtensionComponentPeer {
        return (this.peer as ArkUIExtensionComponentPeer)
    }
    public setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        if (this.checkPriority("setUIExtensionComponentOptions")) {
            const want_casted = want as (Want)
            const options_casted = options as (UIExtensionOptions | undefined)
            this.getPeer()?.setUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            return this
        }
        return this
    }
    public onRemoteReady(value: ((parameter: UIExtensionProxy) => void) | undefined): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((parameter: UIExtensionProxy) => void) | undefined)
            this.getPeer()?.onRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((parameter: Map<string, Object>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((parameter: Map<string, Object>) => void) | undefined)
            this.getPeer()?.onReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onResult(value: ((parameter: Literal_Number_code__want) => void) | undefined): this {
        if (this.checkPriority("onResult")) {
            const value_casted = value as (((parameter: Literal_Number_code__want) => void) | undefined)
            this.getPeer()?.onResultAttribute(value_casted)
            return this
        }
        return this
    }
    public onRelease(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onRelease")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onReleaseAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((parameter: TerminationInfo) => void) | undefined)
            this.getPeer()?.onTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onDrawReady(value: (() => void) | undefined): this {
        if (this.checkPriority("onDrawReady")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onDrawReadyAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function UIExtensionComponent(
    /** @memo */
    style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
    want: Want, options?: UIExtensionOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (_: ArkUIExtensionComponentPeer) => {
        receiver.setUIExtensionComponentOptions(want,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

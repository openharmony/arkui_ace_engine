/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { Finalizable, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KLong, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, InteropNativeModule } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, TerminationInfo } from "./common"
import { AbilityWant, BusinessError, Callback } from '#external'
import { Callback_Number_Void } from "./alphabetIndexer"
import { ErrorCallback } from "./ohos.base"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent } from "./../ComponentContent"
import { ArkUIAniSecurityUiextensionModal, ArkUIAniUIExtensionOptions, ArkUIAniModule, ArkUIAniUiextensionProxyModal } from "arkui.ani"

export interface SecurityUIExtensionProxy {
    send(data: Record<string, Object>): void
    sendSync(data: Record<string, Object>): Record<string, Object>
    onAsyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void) | undefined): void
    offSyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void) | undefined): void
    on(type: 'syncReceiverRegister' | 'asyncReceiverRegister', callback_: ((parameter: SecurityUIExtensionProxy)=>void)) : void
    off(type: 'syncReceiverRegister' | 'asyncReceiverRegister', callback_: ((parameter: SecurityUIExtensionProxy)=>void)) : void
}
export class SecurityUIExtensionProxyInternal implements MaterializedBase,SecurityUIExtensionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uiextensionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SecurityUIExtensionProxyInternal.ctor_uiextensionproxy()
        this.peer = new Finalizable(ctorPtr, SecurityUIExtensionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_getFinalizer()
    }
    public send(data: Record<string, Object>): void {
        const data_casted = data as (Record<string, Object>)
        ArkUIAniUiextensionProxyModal._Send_Data(this.peer!.ptr, data);
        return
    }
    public sendSync(data: Record<string, Object>): Record<string, Object> {
        const data_casted = data as (Record<string, Object>)
        return ArkUIAniUiextensionProxyModal._Send_Data_Sync(this.peer!.ptr, data);
    }
    public onAsyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: SecurityUIExtensionProxy) => void))
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: SecurityUIExtensionProxy) => void))
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: SecurityUIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: SecurityUIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    on(type: string, callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        if (type == 'syncReceiverRegister') {
            this.onSyncReceiverRegister(callback_)
        } else if (type == 'asyncReceiverRegister') {
            this.onAsyncReceiverRegister(callback_)
        }
    }
    off(type: string, callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        if (type == 'syncReceiverRegister') {
            this.offSyncReceiverRegister(callback_)
        } else if (type == 'asyncReceiverRegister') {
            this.offAsyncReceiverRegister(callback_)
        }
    }

    private onAsyncReceiverRegister_serialize(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onsyncReceiverRegister_serialize(callback_: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ((parameter: SecurityUIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._SecurityUIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): SecurityUIExtensionProxyInternal {
        const obj : SecurityUIExtensionProxyInternal = new SecurityUIExtensionProxyInternal()
        obj.peer = new Finalizable(ptr, SecurityUIExtensionProxyInternal.getFinalizer())
        return obj
    }
}
class ArkSecurityUIExtensionCallbackHelp {
    onRemoteReady?: ((parameter: SecurityUIExtensionProxy) => void)
    onReceive?: ((param: Record<string, Object>) => void)
    onError?: ((e: BusinessError) => void)
    onTerminated?: ((parameter: TerminationInfo) => void)
    constructor() {
        this.onRemoteReady = undefined;
        this.onReceive = undefined;
        this.onError = undefined;
        this.onTerminated = undefined;
    }
}

export class ArkSecurityUIExtensionComponentPeer extends ArkCommonMethodPeer {
    _callbackHelp?: ArkSecurityUIExtensionCallbackHelp;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
        this.InitArkSecurityUIExtensionCallbackHelp();
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSecurityUIExtensionComponentPeer {
        InteropNativeModule._NativeLog("[AceSecurityUiExtensionComponent] create ArkUIExtensionComponentPeer start");
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._SecurityUIExtensionComponent_construct(peerId, flags)
        const _peer = new ArkSecurityUIExtensionComponentPeer(_peerPtr, peerId, "UIExtensionComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    InitArkSecurityUIExtensionCallbackHelp(): void {
        InteropNativeModule._NativeLog("[AceSecurityUiExtensionComponent] InitArkUIExtensionCallback Help entry");
        this._callbackHelp = new ArkSecurityUIExtensionCallbackHelp();
    }
    setSecurityUIExtensionComponentOptionsAttribute(want: AbilityWant, options?: SecurityUIExtensionOptions): void {
        InteropNativeModule._NativeLog("[AceSecurityUiExtensionComponent] setUIExtensionComponentOptionsAttribute entry");
        if (options != undefined) {
            let innerOption : ArkUIAniUIExtensionOptions = new ArkUIAniUIExtensionOptions();
            if (options.isTransferringCaller != undefined) {
                innerOption.isTransferringCaller = (options.isTransferringCaller) as boolean;
            }

            if (options.dpiFollowStrategy != undefined) {
                innerOption.dpiFollowStrategy = (options.dpiFollowStrategy as SecurityDpiFollowStrategy).valueOf();
            }
            ArkUIAniSecurityUiextensionModal._SecurityUIextension_Set_Option(this.peer.ptr, innerOption);
        }

        ArkUIAniSecurityUiextensionModal._SecurityUiextension_Set_Want(this.peer.ptr, want);
    }
    onRemoteReadyAttribute(value: ((parameter: SecurityUIExtensionProxy) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SecurityUIExtensionComponentAttribute_onRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReceiveAttribute(value: ((parameter: Record<string, Object>) => void) | undefined): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onReceive = value;
            ArkUIAniSecurityUiextensionModal._SecurityUIextension_Set_OnReciveCallback(this.peer.ptr, (param: Record<string, Object>) => {
                const onReceive = this._callbackHelp?.onReceive;
                if (onReceive !== undefined && onReceive !== null) {
                    const innerParam = param;
                    onReceive(innerParam);
                }
            });
        }
    }

    onErrorAttribute(value: ((e: BusinessError) => void) | undefined): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onError = value;
            ArkUIAniSecurityUiextensionModal._SecurityUiextension_Set_OnErrorCallback(
                this.peer.ptr, (code1: number, name1: string, message1: string) => {
                    const onError = this._callback_Help?.onError;
                    if (onError !== undefined && onError !== null) {
                        const param = {
                            code: code1,
                            name: name1,
                            message: message1
                        } as TerminationInfo
                        onError(param);
                    }
                });
        }
    }
    onTerminateAttribute(value: ((parameter: TerminationInfo) => void) | undefined): void {
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onTerminated = value;
            InteropNativeModule._NativeLog("[AceSecurityUiExtensionComponent] _SecurityUiextension_Set_OnTerminationCallback entry");
            ArkUIAniSecurityUiextensionModal._SecurityUiextension_Set_OnTerminationCallback(
                this.setSecurityUIExtensionComponentOptionsAttribute.prototype, (code1: number, want1 : AbilityWant) => {
                    const onTerminated = this._callbackHelp?.onTerminated;
                    if (onTerminated !== undefined && onTerminated !== null) {
                        const param = {
                            code: 1,
                            want: want1
                        } as BusinessError
                        onTerminated(param);
                    }
                });
        }
    }
}
export enum SecurityDpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export enum SecurityWindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}
export interface SecurityUIExtensionOptions {
    isTransferringCaller?: boolean;
    dpiFollowStrategy?: SecurityDpiFollowStrategy;
    windowModeFollowStrategy?: SecurityWindowModeFollowStrategy;
}
export type Callback_SecurityUIExtensionProxy_Void = (parameter: SecurityUIExtensionProxy) => void;
export type SecurityUIExtensionComponentInterface = (want: AbilityWant, options?: SecurityUIExtensionOptions) => SecurityUIExtensionComponentAttribute;
export interface SecurityUIExtensionComponentAttribute extends CommonMethod {
    onRemoteReady(value: ((parameter: SecurityUIExtensionProxy) => void) | undefined): this
    onReceive(value: ((parameter: Record<string, Object>) => void) | undefined): this
    onError(value: ((e:BusinessError) => void) | undefined): this
    onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this
}
export class ArkSecurityUIExtensionComponentStyle extends ArkCommonMethodStyle implements SecurityUIExtensionComponentAttribute {
    onRemoteReady_value?: ((parameter: SecurityUIExtensionProxy) => void) | undefined
    onReceive_value?: ((parameter: Record<string, Object>) => void) | undefined
    onError_value?: ((e: BusinessError) => void) | undefined
    onTerminated_value?: ((parameter: TerminationInfo) => void) | undefined

    public onRemoteReady(value: ((parameter: SecurityUIExtensionProxy) => void) | undefined): this {
        return this
    }
    public onReceive(value: ((parameter: Record<string, Object>) => void) | undefined): this {
        return this
    }
    public onError(value: ((e: BusinessError) => void) | undefined): this {
        return this
    }
    public onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this {
        return this
    }
}
export type Callback_Map_String_Object_Void = (parameter: Record<string, Object>) => void;
export interface Literal_Number_code__want {
    code: number;
    want?: AbilityWant;
}
export type Callback_Literal_Number_code__want_Void = (parameter: Literal_Number_code__want) => void;
export class ArkSecurityUIExtensionComponentComponent extends ArkCommonMethodComponent implements SecurityUIExtensionComponentAttribute {
    getPeer(): ArkSecurityUIExtensionComponentPeer {
        return (this.peer as ArkSecurityUIExtensionComponentPeer)
    }
    public setSecurityUIExtensionComponentOptions(want: AbilityWant, options?: SecurityUIExtensionOptions): this {
        if (this.checkPriority("setSecurityUIExtensionComponentOptions")) {
            const want_casted = want as (AbilityWant)
            const options_casted = options as (SecurityUIExtensionOptions | undefined)
            this.getPeer()?.setSecurityUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            return this
        }
        return this
    }
    public onRemoteReady(value: ((parameter: SecurityUIExtensionProxy) => void) | undefined): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((parameter: SecurityUIExtensionProxy) => void) | undefined)
            this.getPeer()?.onRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((parameter: Record<string, Object>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((parameter: Record<string, Object>) => void) | undefined)
            this.getPeer()?.onReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ((e: BusinessError) => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((e: BusinessError) => void) | undefined)
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
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function SecurityUIExtensionComponent(
    /** @memo */
    style: ((attributes: SecurityUIExtensionComponentAttribute) => void) | undefined,
    want: AbilityWant, options?: SecurityUIExtensionOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSecurityUIExtensionComponentComponent()
    })
    NodeAttach<ArkSecurityUIExtensionComponentPeer>((): ArkSecurityUIExtensionComponentPeer => ArkSecurityUIExtensionComponentPeer.create(receiver), (_: ArkSecurityUIExtensionComponentPeer) => {
        receiver.setSecurityUIExtensionComponentOptions(want,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
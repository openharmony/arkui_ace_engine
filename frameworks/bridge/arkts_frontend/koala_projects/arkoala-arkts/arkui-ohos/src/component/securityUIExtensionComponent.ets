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

import { ArkUIAniSecurityUiextensionModal, ArkUIAniUIExtensionOptions } from "arkui.ani"
import { KPointer, InteropNativeModule } from "@koalaui/interop"
import { RecordData } from "@ohos.base"
import { int32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent } from "./common"
import { ErrorCallback, BusinessError } from "@ohos.base"
import { AttributeModifier } from "#handwritten"
import { default as Want } from "@ohos.app.ability.Want"
import { ComponentContent } from "@arkui.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface SecurityUIExtensionProxy {
    send(data: Record<string, RecordData>): void
    sendSync(data: Record<string, RecordData>): Record<string, RecordData>
    onAsyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void) | undefined): void
    offSyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void) | undefined): void
}

export enum SecurityDpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}

export interface SecurityUIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    dpiFollowStrategy?: SecurityDpiFollowStrategy;
}

class ArkSecurityUIExtensionCallbackHelp {
    onRemoteReady?: ((parameter: SecurityUIExtensionProxy) => void)
    onReceive?: ((param: Record<string, RecordData>) => void)
    onError?: ((e: BusinessError) => void)
    onTerminated?: ((parameter: TerminationInfo) => void)
    constructor() {
        this.onRemoteReady = undefined
        this.onReceive = undefined
        this.onError = undefined
        this.onTerminated = undefined
    }
}

export class ArkSecurityUIExtensionComponentPeer extends ArkCommonMethodPeer {
    _callbackHelp?: ArkSecurityUIExtensionCallbackHelp;
    constructor(peerPtr: KPointer, id: int32, name: string = "", flag: int32 = 0) {
        super(peerPtr, id, name, flag);
        this.InitArkSecurityUIExtensionCallbackHelp();
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSecurityUIExtensionComponentPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniSecurityUiextensionModal._Uiextension_Security_Construct(peerId, flags)
        const _peer = new ArkSecurityUIExtensionComponentPeer(_peerPtr, peerId, 'SecurityUIExtensionComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    private InitArkSecurityUIExtensionCallbackHelp(): void {
        InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] InitArkUIExtensionCallbackHelp entry");
        this._callbackHelp = new ArkSecurityUIExtensionCallbackHelp();
    }
    setSecurityUIExtensionComponentOptionsAttribute(want: Want, options?: SecurityUIExtensionOptions): void {
        InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] setUIExtensionComponentOptionsAttribute entry");
        if (options !== undefined) {
            let innerOption : ArkUIAniUIExtensionOptions = new ArkUIAniUIExtensionOptions();
            if (options.isTransferringCaller !== undefined) {
                innerOption.isTransferringCaller = (options.isTransferringCaller) as boolean;
            }

            if (options.dpiFollowStrategy !== undefined) {
                innerOption.dpiFollowStrategy = (options.dpiFollowStrategy as SecurityDpiFollowStrategy).valueOf();
            }
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_Option(this.peer.ptr, innerOption);
        }

        ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_Want(this.peer.ptr, want);
    }
    setOnRemoteReadyAttribute(value: ((value0: SecurityUIExtensionProxy) => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnRemoteReadyCallback(this.peer.ptr, undefined)
            return
        }
        const help = this._callbackHelp
        if (help !== undefined && help !== null) {
            help.onRemoteReady = value
            InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] _Uiextension_Set_Security_OnRemoteReadyCallback entry")
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnRemoteReadyCallback(this.peer.ptr, (proxy: SecurityUIExtensionProxy) => {
                const onRemoteReady = this._callbackHelp?.onRemoteReady
                if (onRemoteReady !== undefined && onRemoteReady !== null) {
                    const innerParam = proxy
                    onRemoteReady(innerParam)
                }
            })
        }
    }
    setOnReceiveAttribute(value: ((value0: Record<string, RecordData>) => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnReciveCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onReceive = value;
            InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] _Uiextension_Set_Security_OnReciveCallback entry");
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnReciveCallback(this.peer.ptr, (param: Record<string, RecordData>) => {
                const onReceive = this._callbackHelp?.onReceive;
                if (onReceive !== undefined && onReceive !== null) {
                    const innerParam = param;
                    onReceive(innerParam);
                }
            });
        }
    }
    setOnErrorAttribute(value: ErrorCallback<BusinessError> | undefined): void {
        if (value === undefined) {
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnErrorCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onError = value;
            InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] _Uiextension_Set_Security_OnErrorCallback entry");
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnErrorCallback(
                this.peer.ptr, (code1: number, name1: string, message1: string) => {
                    const onError = this._callbackHelp?.onError;
                    if (onError !== undefined && onError !== null) {
                        const param = {
                            code: Double.toInt(code1),
                            name: name1,
                            message: message1
                        } as BusinessError
                        onError(param);
                    }
                });
        }
    }
    setOnTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnTerminationCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onTerminated = value;
            InteropNativeModule._NativeLog("[AceSecurityUiExtesionComponent] _Uiextension_Set_Security_OnTerminationCallback entry");
            ArkUIAniSecurityUiextensionModal._Uiextension_Set_Security_OnTerminationCallback(
                this.peer.ptr, (code1: number, want1: Want) => {
                    const onTerminated = this._callbackHelp?.onTerminated;
                    if (onTerminated !== undefined && onTerminated !== null) {
                        const param = {
                            code: Double.toInt(code1),
                            want: want1
                        } as TerminationInfo
                        onTerminated(param);
                    }
                });
        }
    }
}

export interface SecurityUIExtensionComponentAttribute extends CommonMethod {
    setSecurityUIExtensionComponentOptions(want: Want, options?: SecurityUIExtensionOptions): this
    onRemoteReady(value: ((value0: SecurityUIExtensionProxy) => void) | undefined): this
    onReceive(value: ((value0: Record<string, RecordData>) => void) | undefined): this
    onError(value: ErrorCallback<BusinessError> | undefined): this
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this
    attributeModifier(value: AttributeModifier<SecurityUIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSecurityUIExtensionComponentComponent extends ArkCommonMethodComponent implements SecurityUIExtensionComponentAttribute {
    getPeer(): ArkSecurityUIExtensionComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkSecurityUIExtensionComponentPeer)
    }
    public setSecurityUIExtensionComponentOptions(want: Want, options?: SecurityUIExtensionOptions): this {
        if (this.checkPriority("setSecurityUIExtensionComponentOptions")) {
            const want_casted = want as (Want)
            const options_casted = options as (SecurityUIExtensionOptions | undefined)
            this.getPeer()?.setSecurityUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            return this
        }
        return this
    }
    public onRemoteReady(value: ((value0: SecurityUIExtensionProxy) => void) | undefined): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((value0: SecurityUIExtensionProxy) => void) | undefined)
            this.getPeer()?.setOnRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onReceive(value: ((value0: Record<string, RecordData>) => void) | undefined): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (((value0: Record<string, RecordData>) => void) | undefined)
            this.getPeer()?.setOnReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback<BusinessError> | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback<BusinessError> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((value0: TerminationInfo) => void) | undefined)
            this.getPeer()?.setOnTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityUIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        super.applyAttributesFinish()
    }
}

@memo
export function SecurityUIExtensionComponentImpl(
    @memo
    style: ((attributes: SecurityUIExtensionComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void, 
): void {
    const receiver = remember<ArkSecurityUIExtensionComponentComponent>((): ArkSecurityUIExtensionComponentComponent => {
        return new ArkSecurityUIExtensionComponentComponent()
    })
    NodeAttach<ArkSecurityUIExtensionComponentPeer>(():
        ArkSecurityUIExtensionComponentPeer => ArkSecurityUIExtensionComponentPeer.create(receiver),
                                               (peer: ArkSecurityUIExtensionComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
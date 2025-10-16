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

import { KLong, KPointer, KInt, KBoolean, KStringPtr, InteropNativeModule } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo } from "./common"
import { BusinessError, Callback } from '#external'
import { default as Want } from "@ohos.app.ability.Want"
import { ErrorCallback, RecordData } from "@ohos.base"
import { UIExtensionOptions } from "./uiExtensionComponent.ets"
import { EmbeddedType } from "./enums"
import { ArkUIAniUiextensionModal, ArkUIAniUIExtensionOptions, ArkUIAniModule, ArkUIAniUiextensionProxyModal } from "arkui.ani"

class ArkUIExtensionCallbackHelp {
    onReceive?: ((param: Record<string, RecordData>) => void)
    onError?: ((e: BusinessError) => void)
    onTerminated?: ((parameter: TerminationInfo) => void)
    onDrawReady?: Callback<void>
    constructor() {
        this.onReceive = undefined
        this.onError = undefined
        this.onTerminated = undefined
        this.onDrawReady = undefined
    }
}
export class ArkUIExtensionComponentPeerBase extends ArkCommonMethodPeer {
    _callbackHelp?: ArkUIExtensionCallbackHelp;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flag: int32 = 0) {
        super(peerPtr, id, name, flag);
        this.InitArkUIExtensionCallbackHelp();
    }
    InitArkUIExtensionCallbackHelp(): void {
        InteropNativeModule._NativeLog("[AceUiExtesionComponent] InitArkUIExtensionCallbackHelp entry");
        this._callbackHelp = new ArkUIExtensionCallbackHelp();
        ArkUIAniUiextensionModal._Uiextension_Set_OnTerminationCallback(
            this.peer.ptr, (code1: number, want1 : Want) => {
                const onTerminated = this._callbackHelp?.onTerminated;
                if (onTerminated !== undefined && onTerminated !== null) {
                    const param = {
                        code: code1 as int,
                        want: want1
                    } as TerminationInfo
                    onTerminated(param);
                }
            }
        );
    }
    public setUIExtensionComponentOptionsAttribute(want: Want, options?: UIExtensionOptions): void {
        InteropNativeModule._NativeLog("[AceUiExtesionComponent] setUIExtensionComponentOptionsAttribute entry");
        if (options !== undefined) {
            let innerOption : ArkUIAniUIExtensionOptions = new ArkUIAniUIExtensionOptions();
            if (options.isTransferringCaller !== undefined) {
                innerOption.isTransferringCaller = (options.isTransferringCaller) as boolean;
            }

            if (options.dpiFollowStrategy !== undefined) {
                innerOption.dpiFollowStrategy = (options.dpiFollowStrategy as DpiFollowStrategy).valueOf();
            }

            if (options.windowModeFollowStrategy !== undefined) {
                innerOption.isWindowModeFollowHost = options.windowModeFollowStrategy === WindowModeFollowStrategy.FOLLOW_HOST_WINDOW_MODE;
            }
            if (options.placeholder !== undefined) {
                if (options.placeholder!.getNodePtr() !== null && options.placeholder!.getNodePtr() !== undefined) {
                    innerOption.initPlaceholder = options.placeholder!.getNodePtr() as KLong;
                }
            }
            if (options?.areaChangePlaceholder) {
                const value_areaChangePlaceholder_value = options.areaChangePlaceholder!
                for (const pairValue of value_areaChangePlaceholder_value) {
                    const placeholderNode = pairValue[1]!
                    if (pairValue[0] === 'ROTATION') {
                        innerOption.rotationPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                    } else if (pairValue[0] === 'FOLD_TO_EXPAND') {
                        innerOption.flodPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                    } else if (pairValue[0] === 'UNDEFINED') {
                        innerOption.undefinedPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                    }
                }
            }
            ArkUIAniUiextensionModal._Uiextension_Set_Option(this.peer.ptr, innerOption);
        }

        ArkUIAniUiextensionModal._Uiextension_Set_Want(this.peer.ptr, want);
    }
    public setEmbeddedComponentOptionsAttribute(loader: Want, type?: EmbeddedType): void {
        InteropNativeModule._NativeLog("[AceEmbeddedComponent] setEmbeddedComponentOptionsAttribute entry");
        ArkUIAniUiextensionModal._Uiextension_Set_Want(this.peer.ptr, loader);
    }
    public setOnReceiveAttribute(value: ((parameter: Record<string, RecordData>) => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniUiextensionModal._Uiextension_Set_OnReciveCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onReceive = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnReciveCallback(this.peer.ptr, (param: Record<string, RecordData>) => {
                const onReceive = this._callbackHelp?.onReceive;
                if (onReceive !== undefined && onReceive !== null) {
                    const innerParam = param;
                    onReceive(innerParam);
                }
            });
        }
    }
    public setOnErrorAttribute(value: ErrorCallback | undefined): void {
        if (value === undefined) {
            ArkUIAniUiextensionModal._Uiextension_Set_OnErrorCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onError = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnErrorCallback(
                this.peer.ptr, (code1: number, name1: string, message1: string) => {
                    const onError = this._callbackHelp?.onError;
                    if (onError !== undefined && onError !== null) {
                        const param = {
                            code: code1 as int,
                            name: name1,
                            message: message1
                        } as BusinessError
                        onError(param);
                    }
                });
        }
    }
    public setOnTerminatedAttribute(value: ((parameter: TerminationInfo) => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniUiextensionModal._Uiextension_Set_OnTerminationCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onTerminated = value;
        }
    }
    public setOnDrawReadyAttribute(value: (() => void) | undefined): void {
        if (value === undefined) {
            ArkUIAniUiextensionModal._Uiextension_Set_OnDrawReadyCallback(this.peer.ptr, undefined);
            return;
        }
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onDrawReady = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnDrawReadyCallback(
                this.peer.ptr, () => {
                    const onDrawReady = this._callbackHelp?.onDrawReady;
                    if (onDrawReady !== undefined && onDrawReady !== null) {
                        onDrawReady(undefined);
                    }
                });
        }
    }
}
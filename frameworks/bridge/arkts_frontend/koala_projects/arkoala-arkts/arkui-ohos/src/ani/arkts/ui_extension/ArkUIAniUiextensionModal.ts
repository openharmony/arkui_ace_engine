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

import { KLong, KInt, InteropNativeModule } from "@koalaui/interop"
import Want from "@ohos.app.ability.Want"
import { RecordData } from "@ohos.base"
import { ArkUIAniUiextensionLoadLibraryHelp } from "./ArkUIAniUiextensionLoadLibraryHelp"
import { SecurityUIExtensionProxy } from "#generated"
import { Finalizable, KPointer, MaterializedBase } from "@koalaui/interop"

export type ResultCallback = (code: number, want: Want) => void;
export type ReleaseCallback = (code: number) => void;
export type ErrorCallback = (code: number, name: string, message: string) => void;
export type RemoteReadyCallback = (proxy: SecurityUIExtensionProxy) => void;
export type ReciveCallback = (param: Record<string, RecordData>) => void;
export type TerminationCallback = (code: number, want: Want) => void;
export type DrawReadyCallback = () => void;

export enum UiextensionType {
    EmbeddedComponent = 0,
    UiextensionComponent = 1
}

export class ArkUIAniUIExtensionOptions {
    constructor() {
        this.isTransferringCaller = false;
        this.isWindowModeFollowHost = false;
        this.dpiFollowStrategy = 0;
        this.initPlaceholder = 0;
        this.undefinedPlaceholder = 0;
        this.rotationPlaceholder = 0;
        this.flodPlaceholder = 0;
    }

    isTransferringCaller: boolean;
    isWindowModeFollowHost: boolean;
    dpiFollowStrategy: KInt;
    initPlaceholder: KLong;
    undefinedPlaceholder: KLong;
    rotationPlaceholder: KLong;
    flodPlaceholder: KLong;
}

export class ArkUIAniUiextensionProxyModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Send_Data(ptr: KLong, value: Record<string, RecordData>) : void;
    native static _Send_Data_Sync(ptr: KLong, value: Record<string, RecordData>) : Record<string, RecordData>;
}

export class ArkUIAniUiextensionModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Uiextension_Construct(id: KInt, flag: KInt, type: UiextensionType): KLong;
    native static _Uiextension_Set_Option(nodePointer: KLong, option: ArkUIAniUIExtensionOptions): void;
    native static _Uiextension_Set_Want(nodePointer: KLong, want: Want): void;
    native static _Uiextension_Set_OnResultCallback(nodePointer: KLong, value?: ResultCallback) : void;
    native static _Uiextension_Set_OnErrorCallback(nodePointer: KLong, value?: ErrorCallback) : void;
    native static _Uiextension_Set_OnReciveCallback(nodePointer: KLong, value?: ReciveCallback) : void;
    native static _Uiextension_Set_OnTerminationCallback(nodePointer: KLong, value?: TerminationCallback) : void;
    native static _Uiextension_Set_OnReleaseCallback(nodePointer: KLong, value?: ReleaseCallback) : void;
    native static _Uiextension_Set_OnDrawReadyCallback(nodePointer: KLong, value?: DrawReadyCallback) : void;
}

export class ArkUIAniSecurityUiextensionModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }
    native static _Uiextension_Security_Construct(id: KInt, flags: KInt): KLong
    native static _Uiextension_Set_Security_Option(nodePointer: KLong, option: ArkUIAniUIExtensionOptions): void;
    native static _Uiextension_Set_Security_Want(nodePointer: KLong, want: Want): void;
    native static _Uiextension_Set_Security_OnResultCallback(nodePointer: KLong, value?: ResultCallback) : void;
    native static _Uiextension_Set_Security_OnErrorCallback(nodePointer: KLong, value?: ErrorCallback) : void;
    native static _Uiextension_Set_Security_OnRemoteReadyCallback(nodePointer: KLong, value?: RemoteReadyCallback) : void;
    native static _Uiextension_Set_Security_OnReciveCallback(nodePointer: KLong, value?: ReciveCallback) : void;
    native static _Uiextension_Set_Security_OnTerminationCallback(nodePointer: KLong, value?: TerminationCallback) : void;
    native static _Uiextension_Set_Security_OnReleaseCallback(nodePointer: KLong, value?: ReleaseCallback) : void;
    native static _Uiextension_Set_Security_OnDrawReadyCallback(nodePointer: KLong, value?: DrawReadyCallback) : void;
}

export class SecurityUIExtensionProxyImpl implements SecurityUIExtensionProxy {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Native_GetFinalizer(): KPointer
    native static _Native_SendData(ptr: KPointer, value: Record<string, RecordData>): void
    native static _Native_SendDataSync(ptr: KPointer, value: Record<string, RecordData>): Record<string, RecordData>

    asyncCallbacks = new Set<((value0: SecurityUIExtensionProxy) => void)>();
    syncCallbacks = new Set<((value0: SecurityUIExtensionProxy) => void)>();
    peer?: Finalizable | undefined = undefined
    public get Peer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        InteropNativeModule._NativeLog("[SecurityUIExtensionProxyImpl] construct" + peerPtr)
        this.peer = new Finalizable(peerPtr, SecurityUIExtensionProxyImpl._Native_GetFinalizer())
    }
    public send(data: Record<string, RecordData>): void {
        const data_casted = data as (Record<string, RecordData>)
        SecurityUIExtensionProxyImpl._Native_SendData(this.peer!.ptr, data_casted)
        return
    }
    public sendSync(data: Record<string, RecordData>): Record<string, RecordData> {
        const data_casted = data as (Record<string, RecordData>)
        return SecurityUIExtensionProxyImpl._Native_SendDataSync(this.peer!.ptr, data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void)): void {
        this.asyncCallbacks.add(callback_)
        return
    }
    public onSyncReceiverRegister(callback_: ((value0: SecurityUIExtensionProxy) => void)): void {
        this.syncCallbacks.add(callback_)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((value0: SecurityUIExtensionProxy) => void)): void {
        if (callback_ === undefined) {
            this.asyncCallbacks.clear()
        } else {
            this.asyncCallbacks.delete(callback_)
        }
        return
    }
    public offSyncReceiverRegister(callback_?: ((value0: SecurityUIExtensionProxy) => void)): void {
        if (callback_ === undefined) {
            this.syncCallbacks.clear()
        } else {
            this.syncCallbacks.delete(callback_)
        }
        return
    }
    public callback(sync: boolean): void {
        if (sync) {
            this.syncCallbacks.forEach((callback) => {
                callback(this)
            })
        } else {
            this.asyncCallbacks.forEach((callback) => {
                callback(this)
            })
        }  
    }
}
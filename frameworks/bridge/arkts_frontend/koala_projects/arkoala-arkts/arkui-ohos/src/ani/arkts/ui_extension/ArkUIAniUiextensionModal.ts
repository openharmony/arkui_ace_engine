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
import { ArkUIAniUiextensionLoadLibraryHelp } from "./ArkUIAniUiextensionLoadLibraryHelp"

export type ResultCallback = (code: number, want: Want) => void;
export type ReleaseCallback = (code: number) => void;
export type ErrorCallback = (code: number, name: string, message: string) => void;
export type ReciveCallback = (param: Record<string, Object>) => void;
export type TerminationCallback = (code: number, want: Want) => void;

export class ArkUIAniUIExtensionOptions {
    constructor() {
        this.isTransferringCaller = false;
        this.dpiFollowStrategy = 0;
    }

    isTransferringCaller: boolean;
    dpiFollowStrategy: KInt;
}

export class ArkUIAniUiextensionProxyModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Send_Data(ptr: KLong, value: Record<string, Object>) : void;
    native static _Send_Data_Sync(ptr: KLong, value: Record<string, Object>) : Record<string, Object>;
}

export class ArkUIAniUiextensionModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Uiextension_Set_Option(nodePointer: KLong, option: ArkUIAniUIExtensionOptions): void
    native static _Uiextension_Set_Want(nodePointer: KLong, want: Want): void
    native static _Uiextension_Set_OnResultCallback(nodePointer: KLong, value: ResultCallback) : void;
    native static _Uiextension_Set_OnErrorCallback(nodePointer: KLong, value: ErrorCallback) : void;
    native static _Uiextension_Set_OnReciveCallback(nodePointer: KLong, value: ReciveCallback) : void;
    native static _Uiextension_Set_OnTerminationCallback(nodePointer: KLong, value: TerminationCallback) : void;
    native static _Uiextension_Set_OnReleaseCallback(nodePointer: KLong, value: ReleaseCallback) : void;
}

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
import { ArkUIAniUiextensionLoadLibraryHelp } from "./ArkUIAniUiextensionLoadLibraryHelp"

export type DcErrorCallback = (code: number, name: string, message: string) => void;

export class ArkUIAniDynamicOptions {
    constructor() {
        this.entryPoint = '';
        this.workerId = 0;
        this.backgroundTransparent = false;
    }

    entryPoint: string;
    workerId: KInt;
    backgroundTransparent: boolean;
}

export class ArkUIAniDynamicModal {
    static {
        ArkUIAniUiextensionLoadLibraryHelp.LoadLibrary();
    }

    native static _Dynamic_Construct(id: KInt, flag: KInt): KLong;
    native static _Dynamic_Set_Option(nodePointer: KLong, option: ArkUIAniDynamicOptions): void;
    native static _Dynamic_Set_OnErrorCallback(nodePointer: KLong, value: DcErrorCallback) : void;
    native static _Dynamic_Set_IsReportFrameEvent(nodePointer: KLong, value: boolean) : void;
}

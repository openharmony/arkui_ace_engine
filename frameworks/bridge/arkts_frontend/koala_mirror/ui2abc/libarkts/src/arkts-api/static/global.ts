/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { throwError } from "../../utils"
import { KNativePointer, nullptr } from "@koalaui/interop"
import { initEs2panda, Es2pandaNativeModule, initGeneratedEs2panda } from "../../Es2pandaNativeModule"
import { Es2pandaNativeModule as GeneratedEs2pandaNativeModule } from "../../generated/Es2pandaNativeModule"
import { initInterop, InteropNativeModule } from "../../InteropNativeModule"
import { Context } from "../peers/Context"
import { Profiler } from "./profiler"
import { ArkTsConfig } from "../../generated"

export class global {
    public static filePath: string = "./plugins/input/main.ets"

    public static arktsconfig?: ArkTsConfig

    private static _config?: KNativePointer
    public static set config(config: KNativePointer) {
        global._config = config
    }
    public static get config(): KNativePointer {
        return global._config ?? throwError('Global.config not initialized')
    }
    public static configIsInitialized(): boolean {
        return global._config !== undefined && global._config !== nullptr
    }
    public static resetConfig(): void {
        global._config = undefined
    }

    // Improve: rename to contextPeer
    public static get context(): KNativePointer {
        return global.compilerContext?.peer ?? throwError('Global.context not initialized')
    }

    // Improve: rename to context when the pointer valued one is eliminated
    public static compilerContext: Context

    private static _es2panda: Es2pandaNativeModule | undefined = undefined
    public static get es2panda(): Es2pandaNativeModule {
        if (this._es2panda === undefined) {
            this._es2panda = initEs2panda()
        }
        return this._es2panda
    }

    private static _generatedEs2panda: GeneratedEs2pandaNativeModule | undefined = undefined
    public static get generatedEs2panda(): GeneratedEs2pandaNativeModule {
        if (this._generatedEs2panda === undefined) {
            this._generatedEs2panda = initGeneratedEs2panda()
        }
        return this._generatedEs2panda
    }

    private static _interop: InteropNativeModule | undefined = undefined
    public static get interop(): InteropNativeModule {
        if (this._interop === undefined) this._interop = initInterop()
        return this._interop

    }

    public static profiler = new Profiler()

    // Check node type values during node creation
    public static validatePeerTypes = false
}

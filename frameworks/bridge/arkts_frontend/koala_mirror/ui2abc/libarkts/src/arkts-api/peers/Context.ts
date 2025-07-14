/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { ArktsObject } from "./ArktsObject"
import { Program } from "../../generated"
import { global } from "../static/global"
import { passString, passStringArray } from "../utilities/private"
import { KNativePointer, nullptr } from "@koalaui/interop"
import { Config } from "./Config"

export class Context extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
    }

    static createFromString(
        source: string
    ): Context {
        if (!global.configIsInitialized()) {
            throw new Error(`Config not initialized`)
        }
        return new Context(
            global.es2panda._CreateContextFromString(
                global.config,
                passString(source),
                passString(global.filePath)
            )
        )
    }

    static createFromFile(filePath: string, configPath: string, stdlibPath: string, outputPath: string): Context | undefined {
        const config = Config.create([
            "",
            "--arktsconfig",
            configPath,
            '--extension',
            'ets',
            '--stdlib',
            stdlibPath,
            filePath,
            '--output',
            outputPath,
        ])
        return new Context(
            global.es2panda._CreateContextFromFile(
                config.peer,
                passString(filePath)
            )
        )
    }

    static createCacheFromFile(filePath: string, config: Config, globalContext: GlobalContext, isExternal: boolean) {
        return new Context(
            global.es2panda._CreateCacheContextFromFile(
                config.peer,
                passString(filePath),
                globalContext.peer,
                isExternal
            )
        )
    }


    destroy() {
        if (this.peer != nullptr) {
            global.es2panda._DestroyContext(this.peer)
            this.peer = nullptr
        }
    }

    get program(): Program {
        return new Program(global.es2panda._ContextProgram(this.peer));
    }
}

export class GlobalContext extends ArktsObject {
    static create(
        config: Config, externalFileList: string[]
    ): GlobalContext {
        return new GlobalContext(
            global.es2panda._CreateGlobalContext(
                config.peer,
                passStringArray(externalFileList),
                externalFileList.length,
                false
            )
        )
    }

    constructor(peer: KNativePointer) {
        super(peer)
    }

    destroy() {
        if (this.peer != nullptr) {
            global.es2panda._DestroyGlobalContext(this.peer)
            this.peer = nullptr
        }
    }
}

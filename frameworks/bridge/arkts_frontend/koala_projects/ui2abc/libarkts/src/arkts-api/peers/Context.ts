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
import { passString } from "../utilities/private"
import { KNativePointer } from "@koalaui/interop"
import { Config } from "./Config"
import * as fs from "fs"

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

    static createFromFile(filePath: string, configPath: string): Context | undefined {
        const config = Config.create([
            "",
            "--arktsconfig",
            configPath,
            '--extension',
            'ets',
            filePath
        ])
        return new Context(
            global.es2panda._CreateContextFromString(
                config.peer,
                passString(fs.readFileSync(filePath, 'utf-8')),
                passString(filePath)
            )
        )
    }

    get program(): Program {
        return new Program(global.es2panda._ContextProgram(this.peer));
    }
}
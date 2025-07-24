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
import { Program } from "./Program"
import { global } from "../static/global"
import { passString } from "../utilities/private"
import { KNativePointer } from "@koalaui/interop"

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

    get program(): Program {
        return new Program(global.es2panda._ContextProgram(this.peer));
    }
}
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
import { global } from "../static/global"
import { passStringArray } from "../utilities/private"
import { KNativePointer } from "@koalaui/interop"

export class Config extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
        // TODO: wait for getter from api
        this.path = ``
    }

    static create(
        input: readonly string[]
    ): Config {
        return new Config(
            global.es2panda._CreateConfig(input.length, passStringArray(input))
        )
    }

    static createDefault(): Config {
        if (global.configIsInitialized()) {
            console.warn(`Config already initialized`)
            return new Config(
                global.config
            )
        }
        return new Config(
            global.es2panda._CreateConfig(
                4,
                passStringArray(["", "--arktsconfig", "./arktsconfig.json", global.filePath])
            )
        )
    }

    readonly path: string
}
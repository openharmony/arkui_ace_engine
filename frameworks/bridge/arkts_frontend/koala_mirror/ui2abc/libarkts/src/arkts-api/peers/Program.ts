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
import { acceptNativeObjectArrayResult, unpackString } from "../utilities/private"
import { KNativePointer, nullptr } from "@koalaui/interop"
import { ETSModule } from "../../generated"

export class Program extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
    }

    get astNode(): ETSModule {
        let program = global.es2panda._ProgramAst(global.context, this.peer)
        if (program == nullptr) throw new Error(`astNode() cannt get AST`)
        return new ETSModule(program)
    }

    get externalSources(): ExternalSource[] {
        return acceptNativeObjectArrayResult<ExternalSource>(
            global.es2panda._ProgramExternalSources(global.context, this.peer),
            (instance: KNativePointer) => new ExternalSource(instance)
        )
    }

}

export class ExternalSource extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
    }

    getName(): string {
        return unpackString(global.es2panda._ExternalSourceName(this.peer))
    }

    get programs(): Program[] {
        return acceptNativeObjectArrayResult<Program>(
            global.es2panda._ExternalSourcePrograms(this.peer),
            (instance: KNativePointer) => new Program(instance)
        )
    }
}

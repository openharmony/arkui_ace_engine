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

import * as arkts from "@koalaui/libarkts"
import checkedTransformer from "./MemoTransformer"
import parsedTransformer from "./ParserTransformer"

interface PluginContext {
    getArkTSProgram(): arkts.Program
}

export function init() {
    const pluginContext = new arkts.PluginContextImpl()
    return {
        name: "memo",
        parsed(this: PluginContext) {
            console.log("[memo-plugin] Run parsed stage plugin")
            const transform = parsedTransformer()
            const prog = this.getArkTSProgram()
            const options: arkts.CompilationOptions = {
                isMainProgram: true,
                name: "memo",
                stage: arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
            }
            try {
                transform(prog, options, pluginContext)
            } catch(e) {
                console.trace(e)
                throw e
            }
        },
        checked(this: PluginContext) {
            console.log("[memo-plugin] Run checked stage plugin")
            const transform = checkedTransformer({ trace: !0 })
            const prog = this.getArkTSProgram()
            const options: arkts.CompilationOptions = {
                isMainProgram: true,
                name: "memo",
                stage: arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED
            }
            try {
                transform(prog, options, pluginContext)
            } catch(e) {
                console.trace(e)
                throw e
            }
        },
        clean() {
            console.log("[memo-plugin] Clean")
        }
    }
}

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
import checkedTransformer from "./checked-stage-plugin"
import parsedTransformer from "./parsed-stage-plugin"


interface ExternalPluginContext {
    getArkTSProgram(): arkts.Program
}

export function init() {
    let pluginContext = new arkts.PluginContextImpl()
    return {
        name: "ui",
        parsed(this: ExternalPluginContext) {
            console.log("[ui-plugin] Run parsed stage plugin")
            const transform = parsedTransformer()
            const prog = arkts.arktsGlobal.compilerContext.program
            const state = arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
            try {
                arkts.runTransformer(prog, state, false, transform, pluginContext)
            } catch(e) {
                console.trace(e)
                throw e
            }
        },
        checked(this: ExternalPluginContext) {
            console.log("[ui-plugin] Run checked stage plugin")
            const transform = checkedTransformer({ trace: !0 })
            const prog = arkts.arktsGlobal.compilerContext.program
            const state = arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED
            try {
                arkts.runTransformer(prog, state, false, transform, pluginContext)
                arkts.recheckSubtree(prog.ast)
            } catch(e) {
                console.trace(e)
                throw e
            }
        },
        clean() {
            console.log("[ui-plugin] Clean")
            pluginContext = new arkts.PluginContextImpl()
        }
    }
}

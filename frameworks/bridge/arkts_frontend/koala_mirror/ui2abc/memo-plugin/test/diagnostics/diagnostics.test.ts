/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { assert } from "chai"
import * as child from "child_process"
import * as path from "path"

function runCompiler(file: string) {
    return child.spawnSync("../../incremental/tools/panda/arkts/ui2abc", [
        "--arktsconfig", path.resolve(path.join("test", "arktsconfig-golden.json")),
        "--output", path.resolve(path.join("test/build/abc", file.replace(/\.ets$/, ".abc"))),
        path.join("test", "diagnostics", "input", file),
   ])
}

function diagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runCompiler(file)
        const out = result.stdout.toString() + "\n" + result.stderr.toString()
        if (!out.includes(message))
            console.error(out)
        assert.include(out, message)
    }).timeout(30000);
}

function noDiagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runCompiler(file)
        const out = result.stdout.toString() + "\n" + result.stderr.toString()
        if (out.includes(message))
            console.error(out)
        assert.notInclude(out, message)
    }).timeout(30000);
}

const isPandaIssue26911Fixed = false
if (isPandaIssue26911Fixed) {
    suite("Smoke", () => {
        diagnostics(
            "smoke",
            "smoke.ets",
            `SyntaxError: Unexpected token 'syntax'.`
        )
    })
}

suite("@memo function out of memo context", () => {
    diagnostics(
        "Global memo call",
        "global-memo-call.ets",
        `Calling @memo function foo from non-@memo context _$init$_`
    )
    diagnostics(
        "Memo in handler",
        "memo-in-handler.ets",
        `Calling @memo function foo from non-@memo anonymous context`
    )
    diagnostics(
        "Memo in inner function",
        "memo-in-inner-function.ets",
        `Calling @memo function foo from non-@memo anonymous context`
    )
    noDiagnostics(
        "Memo with @memo:entry",
        "memo-entry.ets",
        `Calling @memo function`
    )
    diagnostics(
        "Memo in non-memo stack",
        "no-memo-entry.ets",
        `Calling @memo function foo from non-@memo context bar`
    )
})

suite("Parameter with @memo initializer", () => {
    noDiagnostics(
        "Default non-memo argument",
        "default-non-memo-argument.ets",
        "Can not call @memo function at parameter default value expression. Parameter: x"
    )
    diagnostics(
        "Default memo argument",
        "default-memo-argument.ets",
        `Can not call @memo function at parameter default value expression. Parameter: x`
    )
    diagnostics(
        "Default complex memo argument",
        "default-complex-memo-argument.ets",
        "Can not call @memo function at parameter default value expression. Parameter: x"
    )
    diagnostics(
        "Default memo argument at arrow function definition",
        "arrow-default-memo-argument.ets",
        "Can not call @memo function at parameter default value expression. Parameter: x"
    )
    noDiagnostics(
        "Default non-memo argument at arrow function definition",
        "arrow-default-non-memo-argument.ets",
        "Can not call @memo function at parameter default value expression. Parameter: x"
    )
})

suite("@memo function missing return type", () => {
    diagnostics(
        "Function",
        "missing-type-function.ets",
        "@memo foo must have it's return type explicitly specified"
    )
    diagnostics(
        "Arrow function",
        "missing-type-arrow-function.ets",
        "@memo anonymous function must have it's return type explicitly specified"
    )
    diagnostics(
        "Method",
        "missing-type-method.ets",
        "@memo foo must have it's return type explicitly specified"
    )
    noDiagnostics(
        "Correct functions",
        "correctly-typed-functions.ets",
        "must have it's return type explicitly specified"
    )
})

suite("@memo function parameter reassignment", () => {
    diagnostics(
        "@memo function parameter reassignment",
        "memo-parameter-reassignment.ets",
        "@memo function parameter reassignment is forbidden: parameter yyy at function foo"
    )
    noDiagnostics(
        "non-@memo function parameter reassignment",
        "non-memo-parameter-reassignment.ets",
        "reassignment is forbidden"
    )
})
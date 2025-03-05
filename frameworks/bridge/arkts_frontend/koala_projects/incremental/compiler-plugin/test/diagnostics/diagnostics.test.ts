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

import { Assert as assert, suite, test } from "@koalaui/harness"
import * as child from "child_process"
import * as path from "path"

function runTsc(file: string) {
    let npx = process.platform === "win32" ? "npx.cmd" : "npx"
    return child.spawnSync(npx, ["ets-tsc", path.join('test', 'diagnostics', 'input', file)])
}

function diagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runTsc(file)
        console.log(result.stdout.toString())
        assert.include(result.stdout.toString(), message)
    }).timeout(30000);
}

function noDiagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runTsc(file)
        console.log(result.stdout.toString())
        assert.notInclude(result.stderr.toString(), message)
        assert.notInclude(result.stdout.toString(), message)
    }).timeout(30000);
}

suite("Memo in non-memo context", () => {
    diagnostics("Global memo",
        "global_memo.input.ts",
        'Calling a @memo function "foo" from a non-@memo context'
    )
    diagnostics("memo in handler",
        "memo_in_handler.input.ts",
        'Calling a @memo function "foo" from a non-@memo context'
    )
    diagnostics("memo in inner function",
        "memo_in_inner_function.input.ts",
        'Calling a @memo function "foo" from a non-@memo context'
    )
    noDiagnostics("memo with @memo:entry",
        "memo_entry.input.ts",
        'Calling a @memo function "foo" from a non-@memo context'
    )
    diagnostics("memo in non-memo stack",
        "no_memo_entry.input.ts",
        'Calling a @memo function "foo" from a non-@memo context'
    )
})

suite("Changing state in @memo", () => {
    noDiagnostics("BinaryCorrect",
        "BinaryCorrect.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    diagnostics("BinaryIncorrect",
        "BinaryIncorrect.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    noDiagnostics("BinaryNoChange",
        "BinaryNoChange.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    noDiagnostics("UnaryCorrect",
        "UnaryCorrect.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    diagnostics("UnaryIncorrect",
        "UnaryIncorrect.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    noDiagnostics("UnaryNoChange",
        "UnaryNoChange.ts",
        'Changing state "y" in @memo context is not allowed'
    )
    diagnostics("Assignment to parameters",
        "ParameterAssignment.ts",
        "Can not assign to memo function parameter: x"
    )
    noDiagnostics("Assignment to non-memo parameters",
        "NonmemoParameterAssignment.ts",
        "Can not assign to memo function parameter: x"
    )
})

suite("Function declaration with @memo initializer", () => {
    noDiagnostics("NonMemoArgument",
        "NonMemoArgument.ts",
        'Can not call @memo "bar" in parameter "x" default value expression'
    )
    diagnostics("MemoArgument",
        "MemoArgument.ts",
        'Can not call @memo "bar" in parameter "x" default value expression'
    )
    diagnostics("MemoComplexArgument",
        "MemoComplexArgument.ts",
        'Can not call @memo "bar" in parameter "x" default value expression'
    )
    diagnostics("MemoArgumentInArrow",
        "MemoArgumentInArrow.ts",
        'Can not call @memo "bar" in parameter "x" default value expression'
    )
    noDiagnostics("NonMemoArgumentInArrow",
        "NonMemoArgumentInArrow.ts",
        'Can not call @memo "bar" in parameter "x" default value expression'
    )
})


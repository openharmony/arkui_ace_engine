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

function runTsc(file: string) {
    return child.spawnSync("../../incremental/tools/panda/arkts/ui2abc", [
        "--arktsconfig", path.join("test", "arktsconfig-golden.json"),
        "--output", file,
        path.join('test', 'diagnostics', 'input', file),
   ])
}

function diagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runTsc(file)
        const out = result.stdout.toString() + "\n" + result.stderr.toString()
        if (!out.includes(message))
            console.error(out)
        assert.include(out, message)
    }).timeout(30000);
}

function noDiagnostics(name: string, file: string, message: string) {
    test(name, () => {
        const result = runTsc(file)
        const out = result.stdout.toString() + "\n" + result.stderr.toString()
        if (out.includes(message))
            console.error(out)
        assert.notInclude(out, message)
    }).timeout(30000);
}

suite("Smoke", () => {
    diagnostics("smoke",
        "smoke.input.ts",
        "SyntaxError: Unexpected token 'syntax'."
    )
})

suite("Memo in non-memo context", () => {
    diagnostics("global memo",
        "global_memo.input.ts",
        'Attempt to call @memo-method foo from non-@memo-method _$init$_'
    )
    diagnostics("memo in handler",
        "memo_in_handler.input.ts",
        'Attempt to call @memo-method foo from anonymous non-@memo-method'
    )
    diagnostics("memo in inner function",
        "memo_in_inner_function.input.ts",
        'Attempt to call @memo-method foo from anonymous non-@memo-method'
    )
    noDiagnostics("memo with @memo:entry",
        "memo_entry.input.ts",
        'Attempt to call @memo-method foo from'
    )
    diagnostics("memo in non-memo stack",
        "no_memo_entry.input.ts",
        'Attempt to call @memo-method foo from non-@memo-method bar'
    )
})

// suite("Shorthand @memo property assignment", () => {
//     diagnostics("shorthand assignment to @memo property",
//         "PropertyShorthandAssignment.ts",
//         "Can not shorthand assign to memo property: x"
//     )
//     noDiagnostics("shorthand assignment to non-memo property",
//         "NonmemoPropertyShorthandAssignment.ts",
//         "Can not shorthand assign to memo property: x"
//     )
// })

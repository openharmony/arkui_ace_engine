/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { global } from "../src/arkts-api/static/global"
import * as arkts from "../src/arkts-api"

import * as pth from "path"
import { assert } from "chai"
import { exec, execSync } from "child_process"

export { Es2pandaNativeModule } from "../src/Es2pandaNativeModule"
export { assert } from "chai"

export function alignText(text: string): string {
    const lines = text.replace(/\t/gy, '    ').split('\n')

    const shift =
        lines
        .map((str: string) => str.search(/\S/))
        .reduce(
            (prev: number, curr: number) => {
                if (prev === -1) {
                    return curr
                }
                if (curr === -1) {
                    return prev
                }
                return Math.min(prev, curr)
            }
        )
    return lines.map(str => str.slice((shift === -1) ? 0 : shift)).join('\n').trim()
}

export function basename(fileName: string) {
    return pth.basename(fileName).split('.')[0]
}

export function assertEqualsSource(sourceResult: string, sourceExpect: string, message?: string) {
    assert.equal(
        sourceResult.trim().split('\n').map((line: string) => line.trim()).join('\n'),
        sourceExpect.trim().split('\n').map((line: string) => line.trim()).join('\n'),
        message
    )
}

export function ARKTS_TEST_ASSERTION(node: arkts.ETSModule, source: string, state?: arkts.Es2pandaContextState) {
    const finalState: arkts.Es2pandaContextState = (() => {
        if (state !== undefined) {
            return state
        }
        if (process.env.STATE_CHECKED !== undefined) {
            return arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED
        }
        return arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
    })()
    arkts.proceedToState(finalState)

    const ast = node.dumpJson()
    const src = node.dumpSrc()
    const dump = node.dump()
    global.es2panda._DestroyContext(global.context)

    try {
        const script = arkts.createETSModuleFromSource(source, finalState)
        assertEqualsSource(src, script.dumpSrc(), 'Error on SOURCE comparison')
        assert.equal(ast, script.dumpJson(), 'Error on JSON comparison')
        assert.equal(dump, script.dump(), 'Error on DUMP comparison')
    } finally {
        global.es2panda._DestroyContext(global.context)
    }
}



export function cleanGenerated(): void {
    exec('npm run clean:generated')
}

export function fileToAbc(path: string, isModule?: boolean): void {
    const file = pth.basename(path).split('.')[0]

    execSync(`../../../incremental/tools/panda/node_modules/@panda/sdk/linux_host_tools/bin/es2panda ${path} --arktsconfig ./arktsconfig.json ${isModule ? '--ets-module' : ''}`)
    execSync('mkdir -p ./generated')
    execSync(`mv ./${file}.abc ./generated/${file}.abc`)
}

export function contextToAbc(): void {
    arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    // Improve: get name of file
    execSync('mkdir -p ./generated')
    execSync('mv ./main.abc ./generated/main.abc')
}

export function runAbc(path: string = './generated/main.abc', modules?: readonly string[]): void {
    const modulesStr: string = (modules === undefined) ? '' : (':' + modules.join(':'))

    exec(`../../incremental/tools/panda/node_modules/@panda/sdk/linux_host_tools/bin/ark --load-runtimes=ets --boot-panda-files=../../incremental/tools/panda/node_modules/@panda/sdk/ets/etsstdlib.abc${modulesStr} ${path} ETSGLOBAL::main`,
        (error: any, stdout: string, stderr: string) => {
            if (error !== null) {
                assert(false, `failed to run abc: ${error}`)
            }
            console.log(`stdout: ${stdout}`);
            console.log(`stderr: ${stderr}`);
        }
    )
}

export function assertEqualsBinaryOutput(output: string, ctx: Mocha.Context): void {
    if (process.env.TEST_BIN === undefined) {
        ctx.skip()
    }
    try {
        contextToAbc()
        exec(
            'npm run run:abc',
            (error: any, stdout: string, stderr: string) => {
                if (error !== null) {
                    assert(false, `failed to run abc: ${error}`)
                }
                const lines = stdout.trim().split('\n')
                assert(lines.length >= 2)
                assert.equal(lines[0], '> run:abc')
                assert.equal(stderr, '')
                if (lines.length === 2) {
                    assert.equal('', output.trim())
                } else {
                    assert.equal(lines.splice(2).join('\n').trim(), output.trim())
                }
            }
        )
    } finally {
        global.es2panda._DestroyContext(global.context)
    }
}

export function trimLines(value: string): string {
    return value.split('\n').map(it => it.trim()).join('\n')
}

export function equalTrimming(value1: string, value2: string, message: string) {
    return assert.equal(
        trimLines(value1),
        trimLines(value2),
        message
    )
}

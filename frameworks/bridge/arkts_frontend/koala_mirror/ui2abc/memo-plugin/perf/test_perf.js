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


const fs = require('fs')
const path = require('path')
const child_process = require('child_process')

const PANDA_SDK_PATH = path.join(__dirname, '../../../incremental/tools/panda/node_modules/@panda/sdk')
const ES2PANDA_JS_PATH = path.join(__dirname, '../../libarkts/lib/es2panda.js')

const CONFIG_NO_MEMO = path.join(__dirname, 'ui2abcconfig-no-memo.json')
const CONFIG_MEMO = path.join(__dirname, 'ui2abcconfig-memo.json')
const CONFIG_UNMEMOIZED = path.join(__dirname, 'ui2abcconfig-unmemoized.json')

const FILE_PATH = path.join(__dirname, 'input', 'main.ets')
const OUTPUT_PATH = path.join(__dirname, 'build', 'perf.abc')
const FILE_PATH_UNMEMOIZED = path.join(__dirname, 'input', 'unmemoized.ets')
const OUTPUT_PATH_UNMEMOIZED = path.join(__dirname, 'build', 'unmemoized-perf.abc')

function append(str) {
    fs.appendFileSync(FILE_PATH, str, 'utf-8')
}

function appendUnmemoized(str) {
    fs.appendFileSync(FILE_PATH_UNMEMOIZED, str, 'utf-8')
}

function writeImport() {
    append('import { memo } from "@koalaui/runtime/annotations"\n\n')
}

function writeImportUnmemoized() {
    appendUnmemoized('import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type } from "@koalaui/runtime"\n\n')
    appendUnmemoized('import { memo as memo } from "@koalaui/runtime/annotations"\n\n')
}

function writeFunction0(id = 0) {
    append(`@memo function memo_function${id}(): void {}\n\n`)
}

function writeFunction0Unmemoized(id = 0) {
    appendUnmemoized(`@memo function memo_function${id}(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {\n`),
    appendUnmemoized(`  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (123456789)), 0);\n`)
    appendUnmemoized(`  if (__memo_scope.unchanged) {\n`)
    appendUnmemoized(`    __memo_scope.cached;\n`)
    appendUnmemoized(`    return;\n`)
    appendUnmemoized(`  }\n`)
    appendUnmemoized(`  {\n`)
    appendUnmemoized(`    __memo_scope.recache();\n`)
    appendUnmemoized(`    return\n`)
    appendUnmemoized(`  }\n`)
    appendUnmemoized(`}\n\n`)
}

function writeFunction3(id = 0) {
    append(`@memo function memo_function_with_params${id}(p1: int, p2: string, @memo p3: () => void): void {}\n\n`)
}

function writeFunction3Unmemoized(id = 0) {
    appendUnmemoized(`@memo function memo_function_with_params${id}(__memo_context: __memo_context_type, __memo_id: __memo_id_type, p1: int, p2: string, @memo() p3: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): void {\n`),
    appendUnmemoized(`  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (987654321)), 3);\n`)
    appendUnmemoized(`  const __memo_parameter_p1 = __memo_scope.param(0, p1), __memo_parameter_p2 = __memo_scope.param(1, p2), __memo_parameter_p3 = __memo_scope.param(2, p3);\n`)
    appendUnmemoized(`  if (__memo_scope.unchanged) {\n`)
    appendUnmemoized(`    __memo_scope.cached;\n`)
    appendUnmemoized(`    return;\n`)
    appendUnmemoized(`  }\n`)
    appendUnmemoized(`  {\n`)
    appendUnmemoized(`    __memo_scope.recache();\n`)
    appendUnmemoized(`    return\n`)
    appendUnmemoized(`  }\n`)
    appendUnmemoized(`}\n\n`)
}

function writeFunctions(functions0 = 0, functions3 = 0) {
    for (let i = 0; i < functions0; i++) {
        writeFunction0(i)
    }
    for (let i = 0; i < functions3; i++) {
        writeFunction3(i)
    }
}

function writeFunctionsUnmemoized(functions0 = 0, functions3 = 0) {
    for (let i = 0; i < functions0; i++) {
        writeFunction0Unmemoized(i)
    }
    for (let i = 0; i < functions3; i++) {
        writeFunction3Unmemoized(i)
    }
}

function writeMethod0(id = 0) {
    append(`  @memo memo_method${id}(): void {}\n\n`)
}

function writeMethod0Unmemoized(id = 0) {
    appendUnmemoized(`  @memo() public memo_method${id}(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {\n`)
    appendUnmemoized(`    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (123456789)), 1);\n`)
    appendUnmemoized(`    const __memo_parameter_this = __memo_scope.param(0, this);\n`)
    appendUnmemoized(`    if (__memo_scope.unchanged) {\n`)
    appendUnmemoized(`      __memo_scope.cached;\n`)
    appendUnmemoized(`      return;\n`)
    appendUnmemoized(`    }\n`)
    appendUnmemoized(`    {\n`)
    appendUnmemoized(`      __memo_scope.recache();\n`)
    appendUnmemoized(`      return;\n`)
    appendUnmemoized(`    }\n`)
    appendUnmemoized(`  }\n\n`)
}

function writeMethod3(id = 0) {
    append(`  @memo memo_method_with_params${id}(p1: int, p2: string, @memo p3: () => void): void {}\n\n`)
}

function writeMethod3Unmemoized(id = 0) {
    appendUnmemoized(`  @memo() public memo_method_with_params${id}(__memo_context: __memo_context_type, __memo_id: __memo_id_type, p1: int, p2: string, @memo() p3: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): void {\n`)
    appendUnmemoized(`    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (987654321)), 4);\n`)
    appendUnmemoized(`    const __memo_parameter_this = __memo_scope.param(0, this), __memo_parameter_p1 = __memo_scope.param(1, p1), __memo_parameter_p2 = __memo_scope.param(2, p2), __memo_parameter_p3 = __memo_scope.param(3, p3);\n`)
    appendUnmemoized(`    if (__memo_scope.unchanged) {\n`)
    appendUnmemoized(`      __memo_scope.cached;\n`)
    appendUnmemoized(`      return;\n`)
    appendUnmemoized(`    }\n`)
    appendUnmemoized(`    {\n`)
    appendUnmemoized(`      __memo_scope.recache();\n`)
    appendUnmemoized(`      return;\n`)
    appendUnmemoized(`    }\n`)
    appendUnmemoized(`  }\n\n`)
}

function writeClass(methods0 = 0, methods3 = 0) {
    append(`class C {\n`)
    for (let i = 0; i < methods0; i++) {
        writeMethod0(i)
    }
    for (let i = 0; i < methods3; i++) {
        writeMethod3(i)
    }
    append('}\n\n')
}

function writeClassUnmemoized(methods0 = 0, methods3 = 0) {
    appendUnmemoized(`class C {\n`)
    for (let i = 0; i < methods0; i++) {
        writeMethod0Unmemoized(i)
    }
    for (let i = 0; i < methods3; i++) {
        writeMethod3Unmemoized(i)
    }
    appendUnmemoized('}\n\n')
}

function writeCallFunction0() {
    append('  memo_function0()\n')
}

function writeCallFunction0Unmemoized() {
    appendUnmemoized('  memo_function0(__memo_context, ((__memo_id) + (101010101)))\n')
}

function writeCallFunction3() {
    append('  memo_function_with_params0(1, "hello", (): void => { })\n')
}

function writeCallFunction3Unmemoized() {
    appendUnmemoized('  memo_function_with_params0(__memo_context, ((__memo_id) + (101010101)), 1, "hello", __memo_context.compute(((__memo_id) + (101010101)), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) => {\n')
    appendUnmemoized('    return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {\n')
    appendUnmemoized('      const __memo_scope = __memo_context.scope<void>(((__memo_id) + (777777777)), 0);\n')
    appendUnmemoized('      if (__memo_scope.unchanged) {\n')
    appendUnmemoized('        __memo_scope.cached;\n')
    appendUnmemoized('        return;\n')
    appendUnmemoized('      }\n')
    appendUnmemoized('      {\n')
    appendUnmemoized('        __memo_scope.recache();\n')
    appendUnmemoized('        return;\n')
    appendUnmemoized('      }\n')
    appendUnmemoized('    });\n')
    appendUnmemoized('  })));\n')
}

function writeMain(call0 = 0, call3 = 0) {
    append('@memo function main_entry(): void {\n')
    for (let i = 0; i < call0; i++) {
        writeCallFunction0(i)
    }
    for (let i = 0; i < call3; i++) {
        writeCallFunction3(i)
    }
    append('}\n')
}

function writeMainUnmemoized(call0 = 0, call3 = 0) {
    appendUnmemoized('@memo() function main_entry(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {\n')
    appendUnmemoized('const __memo_scope = __memo_context.scope<void>(((__memo_id) + (222222222)), 0);\n')
    appendUnmemoized('  if (__memo_scope.unchanged) {\n')
    appendUnmemoized('    __memo_scope.cached;\n')
    appendUnmemoized('    return;\n')
    appendUnmemoized('  }\n')
    for (let i = 0; i < call0; i++) {
        writeCallFunction0Unmemoized(i)
    }
    for (let i = 0; i < call3; i++) {
        writeCallFunction3Unmemoized(i)
    }
    appendUnmemoized('  {\n')
    appendUnmemoized('    __memo_scope.recache();\n')
    appendUnmemoized('    return;\n')
    appendUnmemoized('  }\n')
    appendUnmemoized('}\n')
}

function generateInput(difficulty) {
    fs.mkdirSync(path.dirname(FILE_PATH), { recursive: true })
    if (fs.existsSync(FILE_PATH)) {
        fs.rmSync(FILE_PATH)
    }

    const start = Date.now()

    writeImport()
    writeFunctions(difficulty, difficulty)
    writeClass(difficulty, difficulty)
    writeMain(difficulty, difficulty)

    const end = Date.now()

    console.log(`input file is generated in ${end - start}ms, size = ${fs.statSync(FILE_PATH).size} bytes\n`)
}

function generateInputUnmemoized(difficulty) {
    fs.mkdirSync(path.dirname(FILE_PATH_UNMEMOIZED), { recursive: true })
    if (fs.existsSync(FILE_PATH_UNMEMOIZED)) {
        fs.rmSync(FILE_PATH_UNMEMOIZED)
    }

    const start = Date.now()

    writeImportUnmemoized()
    writeFunctionsUnmemoized(difficulty, difficulty)
    writeClassUnmemoized(difficulty, difficulty)
    writeMainUnmemoized(difficulty, difficulty)

    const end = Date.now()

    console.log(`unmemoized input file is generated in ${end - start}ms, size = ${fs.statSync(FILE_PATH_UNMEMOIZED).size} bytes\n`)
}

function exec(cmd) {
    const start = Date.now()
    child_process.execSync(cmd, { stdio: "inherit" })
    const end = Date.now()

    console.log(`Time consumed: ${end - start}ms\n`)
}

function execNoMemo() {
    const cmd = `KOALA_WORKSPACE=1 PANDA_SDK_PATH=${PANDA_SDK_PATH} node ${ES2PANDA_JS_PATH} --ets-module --arktsconfig ${CONFIG_NO_MEMO} --output ${OUTPUT_PATH} --simultaneous --profile-memory ${FILE_PATH}`
    console.log(`Command used for non memo compilation:`)
    console.log(cmd)
    exec(cmd)
}

function execMemo() {
    const cmd = `KOALA_WORKSPACE=1 PANDA_SDK_PATH=${PANDA_SDK_PATH} node ${ES2PANDA_JS_PATH} --ets-module --arktsconfig ${CONFIG_MEMO} --output ${OUTPUT_PATH} --simultaneous --profile-memory ${FILE_PATH}`
    console.log(`Command used for memo compilation:`)
    console.log(cmd)
    exec(cmd)
}

function execUnmemoized() {
    const cmd = `KOALA_WORKSPACE=1 PANDA_SDK_PATH=${PANDA_SDK_PATH} node ${ES2PANDA_JS_PATH} --ets-module --arktsconfig ${CONFIG_UNMEMOIZED} --output ${OUTPUT_PATH_UNMEMOIZED} --simultaneous --profile-memory ${FILE_PATH_UNMEMOIZED}`
    console.log(`Command used for unmemoized compilation:`)
    console.log(cmd)
    exec(cmd)
}

generateInput(10000)
generateInputUnmemoized(10000)
execNoMemo()
execMemo()

// This is not quite correct, as runtime should be unmemoized as well for more correct comparasion 
execUnmemoized()

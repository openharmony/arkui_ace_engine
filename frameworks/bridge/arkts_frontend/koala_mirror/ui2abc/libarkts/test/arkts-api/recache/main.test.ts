/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import * as fs from "node:fs"
import * as util from "../../test-util"
import * as arkts from "../../../src"
import { execSync } from "node:child_process"
import { assert } from "chai"
import { compileWithCache } from "src/arkts-api/CompileWithCache"

class Visitor extends arkts.AbstractVisitor {
    visitor(node: arkts.AstNode) {
        if (arkts.isIdentifier(node)) {
            if (node.name.startsWith("I")) return arkts.factory.createIdentifier(node.name + "I")
        }
        return this.visitEachChild(node)
    }
}

function visitor(program: arkts.Program) {
    arkts.dumpProgramInfo(program)
    return new Visitor().visitor(program.ast)
}

const PANDA_PATH = `${__dirname}/../../../../../incremental/tools/panda/`

const FIRST = `${__dirname}/files/first.ets`
const SECOND = `${__dirname}/files/second.ets`
const THIRD = `${__dirname}/files/third.ets`

const FIRST_ABC = `${__dirname}/files/build/first.abc`
const SECOND_ABC = `${__dirname}/files/build/second.abc`

suite(util.basename(__filename), () => {
    test('compile with cache', () => {
        execSync(`rm -rf ${__dirname}/files/build`, { stdio: "inherit" })
        fs.mkdirSync(`${__dirname}/files/build`, { recursive: true })

        compileWithCache(
            `${__dirname}/arktsconfig.json`,
            [
                {
                    absoluteName: THIRD,
                    output: undefined,
                },
                {
                    absoluteName: SECOND,
                    output: SECOND_ABC,
                },
                {
                    absoluteName: FIRST,
                    output: FIRST_ABC,
                },
            ],
            [visitor],
            undefined
        )

        execSync(`${PANDA_PATH}/arkts/arkdisasm ${__dirname}/files/build/second.abc`, { stdio: "inherit" })
        assert(fs.readFileSync(`${__dirname}/files/build/second.abc`).includes('II'))

        execSync(`${PANDA_PATH}/arkts/arkdisasm ${__dirname}/files/build/first.abc`, { stdio: "inherit" })
        assert(fs.readFileSync(`${__dirname}/files/build/first.abc`).includes('II'))
    })
})

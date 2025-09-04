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

function shouldModify(name: string) {
    return name.match(/^I(_Parsed|_Checked)*$/)
}

class VisitorParsed extends arkts.AbstractVisitor {
    visitor(node: arkts.BlockStatement): arkts.BlockStatement
    visitor(node: arkts.AstNode) {
        if (arkts.isIdentifier(node)) {
            if (shouldModify(node.name)) return arkts.factory.createIdentifier(node.name + "_Parsed")
        }
        return this.visitEachChild(node)
    }
}

class VisitorChecked extends arkts.AbstractVisitor {
    visitor(node: arkts.BlockStatement): arkts.BlockStatement
    visitor(node: arkts.AstNode) {
        if (arkts.isIdentifier(node)) {
            if (shouldModify(node.name)) return arkts.factory.createIdentifier(node.name + "_Checked")
        }
        return this.visitEachChild(node)
    }
}

/**
 * Modifies identifiers matching I(_Parsed|_Checked)* regex by appending current state to them
 * Good for tracking pligin application to some program
 */
function visitor(program: arkts.Program, options: arkts.CompilationOptions) {
    arkts.dumpProgramInfo(program)
    if (options.stage == arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED) {
        program.setAst(new VisitorParsed().visitor(program.ast))
    }
    if (options.stage == arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED) {
        program.setAst(new VisitorChecked().visitor(program.ast))
    }
}

const PANDA_PATH = `${__dirname}/../../../../../incremental/tools/panda/`

const FIRST = `${__dirname}/files/first.ets`
const SECOND = `${__dirname}/files/second.ets`
const THIRD = `${__dirname}/files/third.ets`

const FIRST_ABC = `${__dirname}/files/build/first.abc`
const SECOND_ABC = `${__dirname}/files/build/second.abc`

suite(util.basename(__filename), () => {
    // TODO: with panda/sdk 34579 it segfaults
    test.skip('compile with cache', () => {
        execSync(`rm -rf ${__dirname}/files/build`, { stdio: "inherit" })
        fs.mkdirSync(`${__dirname}/files/build`, { recursive: true })

        arkts.compileWithCache(
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

        execSync(`${PANDA_PATH}/arkts/arkdisasm ${SECOND_ABC}`, { stdio: "inherit" })
        assert(fs.readFileSync(`${SECOND_ABC}.disasm`).includes('third.I_Parsed '))

        execSync(`${PANDA_PATH}/arkts/arkdisasm ${FIRST_ABC}`, { stdio: "inherit" })
        assert(fs.readFileSync(`${FIRST_ABC}.disasm`).includes('third.I_Parsed '))
    })
})

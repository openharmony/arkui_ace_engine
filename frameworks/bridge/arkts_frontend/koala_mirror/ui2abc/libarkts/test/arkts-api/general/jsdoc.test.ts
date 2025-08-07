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

import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"
import { assert } from "@koalaui/harness"
import {
    isMethodDefinition,
    isBlockStatement,
    isClassDeclaration,
    isFunctionDeclaration,
    isStatement,
    isTSTypeAliasDeclaration,
    isClassProperty,
    getJsDoc,
    isIdentifier
} from "../../../src/arkts-api"

suite(util.basename(__filename), () => {
    const comments: string[] = [
        '/** Regular function */' ,
        '/** Type T */',
        '/** Class A */',
        '/** Method */',
        '/** Return type */',
        '/** Property */',
    ]

    test("jsdoc", function() {
        const sample_in = `
        ${comments[0]}
        export function foo();
        ${comments[1]}
        type T = int;
        ${comments[2]}
        export class A {
            ${comments[3]}
            a_foo(): // colon here
                ${comments[4]}
                void {}
            ${comments[5]}
            private a_prop: number = 1
        }`

        let script = arkts.createETSModuleFromSource(
            sample_in,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        const jsdocs: (string | undefined)[] = []
        for (const stmt of script.statements) {
            jsdocs.push(getJsDoc(stmt))
           if (isClassDeclaration(stmt)) {
               const body = stmt.definition?.body ?? []
               for (const node of body) {
                   jsdocs.push(getJsDoc(node))

                   if (isMethodDefinition(node) && isIdentifier(node.key) &&
                       node.key.name === 'a_foo' && node.function?.returnTypeAnnotation) {
                       jsdocs.push(getJsDoc(node.function?.returnTypeAnnotation))
                   }
               }
            }
        }

        assert.equal(
            comments
                .concat('') // implicit ctor returns undefined
                .join(','),
            jsdocs
                .join(',')
        )
    })
})

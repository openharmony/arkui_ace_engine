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

import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

suite(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        function _() {};
        `

        const sample_out =
        `
        function _() {};
        console.log('out')
        `

        let script = arkts.createETSModuleFromSource(sample_in)

        script = arkts.updateETSModuleByStatements(
            script,
            [
                script.statements[0],
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createIdentifier(
                                'console'
                            ),
                            arkts.Identifier.create2Identifier(
                                'log'
                            ),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        [
                            arkts.factory.createStringLiteral(
                                'out'
                            )
                        ],
                        undefined,
                    )
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            sample_out
        )
    })
})

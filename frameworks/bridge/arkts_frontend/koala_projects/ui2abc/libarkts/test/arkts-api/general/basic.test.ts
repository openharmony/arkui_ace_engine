/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
        `

        let script = arkts.createETSModuleFromSource(sample_in)

        script = arkts.updateETSModuleByStatements(
            script,
            [
                arkts.factory.createExpressionStatement(
                    arkts.factory.createIdentifier(
                        'abc'
                    )
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            abc
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })
})

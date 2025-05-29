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

const tsNode = require("ts-node")
const path = require("path")
const { goldenSetup } = require("@koalaui/common/golden")

goldenSetup('.', '.')

unmemoized_suffix = process.env.UNMEMOIZED_SUFFIX
if (unmemoized_suffix == undefined) {
    unmemoized_suffix = ''
}

tsNode.register({
    files: true,
    // If uncommented, running tests doesn't perform type checks.
    // transpileOnly: true,
    project: path.resolve(`test`, `tsconfig${unmemoized_suffix}.json`),
    compiler: "@koalaui/ets-tsc"
})

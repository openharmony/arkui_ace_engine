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

import { testOhConf } from "./common.mjs"
import { ensureExists, ohConf } from "../ohconf.mjs"
import { copyResources } from "../ohos-app/bundle-resources.mjs"
import { lazy } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohConf(ohConfPath))

export function bundle(options) {
    LZ_OHCONF(options.ohConf)

    const resDst = ensureExists(LZ_OHCONF().value("resources", true), true)
    const tests = LZ_OHCONF().value("test", true)

    tests.forEach(test => {
        ensureExists(test)

        const conf = testOhConf(test)
        const resSrcRoot = conf.value('test_resources_root', true, false)
        if (resSrcRoot)
            ensureExists(resSrcRoot)

        const resSrc = conf.value('test_resources', true, false)
        if (resSrc) {
            ensureExists(resSrc)
            copyResources(resSrcRoot, resSrc, resDst)
        }
    })
}

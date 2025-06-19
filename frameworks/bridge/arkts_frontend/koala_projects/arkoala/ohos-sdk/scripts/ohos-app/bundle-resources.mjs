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

import path from "path"
import fs from "fs"
import { ensureExists, ohConf, ohProjectConf, PROJECT_MOD_APP, PROJECT_MOD_TEST } from "./../ohconf.mjs"
import { copyDirSync, lazy } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))
const LZ_RES_DST_ROOT = lazy(mod => {
    const path = LZ_OHCONF().path(mod + '_resources_dst')
    ensureExists(path, true)
    return path
})

export function copyResources(resSrcRoot, resSrc, resDst) {
    if (resSrcRoot) {
        ensureExists(resSrcRoot)
        const resRelPath = path.relative(resSrcRoot, resSrc)
        resDst = path.join(resDst, resRelPath)
        fs.mkdirSync(resDst, {recursive: true})
    }

    console.log(`> Copying resources from ${resSrc} to ${resDst}`)
    copyDirSync(resSrc, resDst, true)
}

function clean() {
    if (fs.existsSync(LZ_RES_DST_ROOT())) {
        console.log(`> Deleting ${LZ_RES_DST_ROOT()}`)
        fs.rmSync(LZ_RES_DST_ROOT(), {recursive: true})
    }
}

export function bundle(options) {
    LZ_OHCONF(options.ohConf)
    LZ_RES_DST_ROOT(options.mod)

    if (options.clean) {
        clean()
        return
    }

    const mod = options.mod

    if (mod === PROJECT_MOD_APP) {
        const resSrc = LZ_OHCONF().path(mod + "_resources_src")
        ensureExists(resSrc)
        const resSrcRoot = LZ_OHCONF().path(mod + '_resources_src_root', false)
        copyResources(resSrcRoot, resSrc, LZ_RES_DST_ROOT())
    }
    else if (mod === PROJECT_MOD_TEST) {
        const testOhConfJson = LZ_OHCONF().path('test_config')
        const resSrc = ensureExists(ohConf(testOhConfJson).value('resources', true))
        copyResources(undefined, resSrc, LZ_RES_DST_ROOT())
    }
}

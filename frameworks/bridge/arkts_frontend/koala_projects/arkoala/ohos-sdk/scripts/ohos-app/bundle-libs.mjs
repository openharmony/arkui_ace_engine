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

import fs from "fs"
import path from "path"
import { ensureExists, ohProjectConf } from "../ohconf.mjs"
import { lazy } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))

function copyLib(arch, libSrc) {
    ensureExists(libSrc)
    console.log(`> Copying '${libSrc}'`)
    const libsDst = LZ_OHCONF().path(`libs_${arch}_dst`)
    ensureExists(libsDst, true)
    fs.copyFileSync(libSrc, path.join(libsDst, path.basename(libSrc)))
}

function copyAllLibs(arch) {
    LZ_OHCONF().path(`libs_${arch}_src`).forEach(lib => {
        copyLib(arch, lib)
    })
}

function call(arch, func) {
    if (arch === "universal") {
        func("arm")
        func("arm64")
    } else {
        func(arch)
    }
}

export function bundle(options) {
    LZ_OHCONF(options.ohConf)

    if (options.runtime === "hzvm")
        call(options.arch, copyAllLibs)
}

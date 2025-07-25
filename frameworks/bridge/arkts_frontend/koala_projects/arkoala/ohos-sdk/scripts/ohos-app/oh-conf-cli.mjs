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

import { OH_CLI_OPT_KEYS, parseOhCliOptions } from "../ohos-sdk/oh-cli-opts.mjs"
import { ohConf } from "../ohconf.mjs"

const OH_CLI_OPTS = parseOhCliOptions([
    OH_CLI_OPT_KEYS.ohConf,
    OH_CLI_OPT_KEYS.pathKey,
    OH_CLI_OPT_KEYS.nameKey,
    OH_CLI_OPT_KEYS.sdkVersion
])

function main() {
    const ohconf = ohConf(OH_CLI_OPTS.ohConf)

    if (OH_CLI_OPTS.pathKey) {
        if (OH_CLI_OPTS.pathKey === "hdc")
            console.log(ohconf.hdcPath())
        else
            console.log(ohconf.path(OH_CLI_OPTS.pathKey))
    }
    else if (OH_CLI_OPTS.nameKey)
        console.log(ohconf.name(OH_CLI_OPTS.nameKey))
    else if (OH_CLI_OPTS.sdkVersion)
        console.log(ohconf.sdkVersion())
}

main()
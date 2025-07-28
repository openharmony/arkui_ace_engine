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
import { checkDevice, install, recvImages, recvLogs, run, uninstall } from "./exec-on-device.mjs"

const OH_CLI_OPTS = parseOhCliOptions([
    OH_CLI_OPT_KEYS.ohConf,
    OH_CLI_OPT_KEYS.install,
    OH_CLI_OPT_KEYS.uninstall,
    OH_CLI_OPT_KEYS.run,
    OH_CLI_OPT_KEYS.runTimeout,
    OH_CLI_OPT_KEYS.hdcExtraOpts,
    OH_CLI_OPT_KEYS.recvImages,
    OH_CLI_OPT_KEYS.recvLogs,
    OH_CLI_OPT_KEYS.listDevices,
    OH_CLI_OPT_KEYS.mod
])

await checkDevice(OH_CLI_OPTS)

if (OH_CLI_OPTS.install)
    await install(OH_CLI_OPTS)
if (OH_CLI_OPTS.uninstall)
    await uninstall(OH_CLI_OPTS)
if (OH_CLI_OPTS.run)
    await run(OH_CLI_OPTS)
if (OH_CLI_OPTS.runTimeout)
    await run(OH_CLI_OPTS)
if (OH_CLI_OPTS.recvImages)
    await recvImages(OH_CLI_OPTS)
if (OH_CLI_OPTS.recvLogs)
    await recvLogs(OH_CLI_OPTS)

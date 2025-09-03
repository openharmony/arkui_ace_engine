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

import { generic_package_archive_gitlab } from "../../arkoala/ohos-sdk/scripts/gitlab.mjs"
import minimist from "minimist";
import path from "path"

let args = minimist(process.argv.slice(2))

const version = args.version
const apiVersion = version.split('-')[0]
const outDir = path.join('prebuilt', 'node-addon-api-'+ version)

generic_package_archive_gitlab(
    'node-addon-api',
    apiVersion,
    'v' + version + '.tar.gz',
    outDir
)

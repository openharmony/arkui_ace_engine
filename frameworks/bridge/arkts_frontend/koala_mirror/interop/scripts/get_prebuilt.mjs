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

import { GitLab } from "../../tools/storage/gitlab/gitlab.mjs";
import minimist from "minimist";
import path from "path"

const gitlab = new GitLab()

let args = minimist(process.argv.slice(2))

const version = args.version
const buildType = args['build-type']
const machine = args.machine
const target = args.target

const nodeVersion = version.split('-')[0]
const buildName = buildType + '-' + target + '-' + machine
const outDir = path.join('prebuilt', version, buildName)

if (target === 'android') {
    gitlab.downloadRawArchive(
        'node-bin',
        nodeVersion,
        `node-${target}-${buildType}-${machine}-${version}.zip`,
        outDir
    )
} else {
    gitlab.downloadRawArchive(
        'node-bin',
        nodeVersion,
        `node-v${nodeVersion}-headers.tar.gz`,
        outDir,
        `node-v${nodeVersion}/`,
    )
    if (target === 'windows') {
        gitlab.downloadRawFile(
            'node-bin',
            nodeVersion,
            `win-${machine}.node.lib`,
            path.join(outDir, 'lib'),
            'node.lib'
        )
    }
}


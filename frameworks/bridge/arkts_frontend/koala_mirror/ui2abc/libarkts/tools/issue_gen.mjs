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

import * as fs from 'fs'
import * as path from 'path'

process.chdir(path.resolve('./'))

const issue_src = fs.readFileSync('../playground/src/playground.cc', { encoding: 'utf8', flag: 'r' })

const component_src =
`
### Component

Plugin API

`

const revision_src =
`
### Revision

"@panda/sdk": "1.5.0-dev.9184"

`

const reproduction_src =
`
### Reproduction

\`\`\`
${issue_src}
\`\`\`

`

// TODO:
const log = ``

const log_src =
`
### Log

\`\`\`
${log}
\`\`\`
`

console.log(
    component_src +
    revision_src +
    reproduction_src +
    log_src
)

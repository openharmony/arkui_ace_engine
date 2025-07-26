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

const binLinks = require('bin-links')
const readPackageJson = require('read-package-json-fast')

readPackageJson('./node_modules/typescript/package.json')
  .then(
    pkg => {
      binLinks({
        path: './node_modules/typescript',
        pkg: pkg,
        global: false,
        // true if it's the top level package being installed, false otherwise
        top: false,
        // Overwrite existing links!
        force: true,
      }).then(
        resp => console.log(".bin links set to the proper typescript")
      )
    }
  )

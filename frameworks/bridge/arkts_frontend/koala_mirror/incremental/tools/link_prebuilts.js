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

const fs = require('fs')
const path = require('path')
const os = require('os');
 
const dir = path.join(process.cwd(), '.runtime-prebuilt')
 
function install_pkg(file) {
 
    const absolutePrebuiltPath = path.resolve('.runtime-prebuilt/', file)
    const packageJsonPath = path.join(absolutePrebuiltPath, "package.json")

    if (!(fs.existsSync(packageJsonPath))) return 0
 
    const packageJson = fs.readFileSync(packageJsonPath, {encoding: 'utf-8'}).trim()
    const name = JSON.parse(packageJson).name
    packageDir = `node_modules/${name}`
 
    if (fs.existsSync(packageDir)) {
        fs.rmSync(packageDir, { recursive: true})
    }
 
    if (os.type() === 'Windows_NT') {
        fs.mkdirSync(packageDir, { recursive: true })
        fs.cpSync(absolutePrebuiltPath + "/", packageDir, { recursive: true, force: true })
    } else {
        fs.symlinkSync(absolutePrebuiltPath, packageDir, 'dir')
    }
 
}
 
if (fs.existsSync(dir)) {
    var files = fs.readdirSync(dir)
    files.forEach(file => {
        install_pkg(file)
    })
}
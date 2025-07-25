/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import * as path from 'path'
import * as fs from 'fs'
import { Assert as assert } from "@koalaui/harness"
import * as child from "child_process"

export function testFolder(folder: string) {
    suite(folder, () => {
        const golden = "./test/golden/" + folder
        const current = "./build/ts/" + folder
        const files = collectFiles(path.resolve(current))
        console.log(files)
        files.forEach(file => {
            test(file, () => {
                assertEqualFiles(
                    path.resolve(golden, file),
                    path.resolve(current, file)
                )
            })
        })
    })
}

export function testsForDirectories(goldenDir: string, otherDir: string) {
    const files = collectFiles(goldenDir)
    console.log(files)

    return files.map(file => () => test(file, () => {
        const golden = path.resolve(goldenDir, file)
        const other = path.resolve(otherDir, file)
        assertEqualFiles(golden, other)
    }))
}

export function assertGeneratedEqualsGolden(filename: string) {
    const goldenFile = path.resolve("./test/golden", filename)
    const generatedFile = path.resolve("./test/generated", filename)
    return assertEqualFiles(goldenFile, generatedFile)
}

function assertEqualFiles(goldenFilePath: string, otherFilePath: string) {
    const golden = fs.readFileSync(goldenFilePath, "utf-8")
    const other = fs.readFileSync(otherFilePath, "utf-8")

    // ignore all \r to fix testing on Windows
    return assert.equal(golden.replace(/\r/g, ""), other.replace(/\r/g, ""))
}

export function collectFiles(root: string): string[] {
    if (!fs.existsSync(root)) {
        throw new Error(`No such directory ${root}`)
    }

    let files: string[] = []

    function traverse(directory: string) {
        const dirents = fs.readdirSync(directory, { withFileTypes: true }) as fs.Dirent[]

        dirents.forEach(dirent => {
            const name = dirent.name
            const fullPath = path.resolve(directory, name)

            if (dirent.isFile()) {
                const relative = path.relative(root, fullPath)
                files.push(relative)
            }
            if (dirent.isDirectory()) {
                traverse(fullPath)
            }
        })
    }
    traverse(root)
    return files
}

export function copy(from: string, to: string, files: string[],
    sourceToEts: boolean = false, erasePath: boolean = false, etsFileExtension: boolean = false, makeModule: boolean = false): string[] {
 
    let newFiles: string[] = []
    files.forEach(file => {
        if (!file.endsWith('.ts') && !file.endsWith('.ets')) {
            return
        }

        const fromPath = path.join(from, file)

        let content = fileContent(fromPath, sourceToEts)
        if (makeModule) {
            content += ' export {}'
        }

        let writePath = file
        if (erasePath) {
            writePath = writePath.split(path.sep).pop()!
        }
        writePath = path.join(to, writePath)
        writePath = etsFileExtension ? writePath.replace(".ts", ".ets") : writePath

        if (!fs.existsSync(writePath)) {
            newFiles.push(file)
        }
        forceWriteFile(writePath, content)
    })
    return newFiles
}

function fileContent(fromPath: string, isEts: boolean) {
    if (!isEts) {
        return fs.readFileSync(fromPath)
    }
    const module = require(fromPath)
    if (module?.source === undefined) {
        throw new Error(`Failed to runtime import ${fromPath}`)
    }

    return module.source
}

function forceWriteFile(filePath: string, content: string) {
    const folders = filePath.split(path.sep).slice(0, -1)

    forceWriteFolders(folders)

    fs.writeFileSync(filePath, content)
}

function forceWriteFolders(folders: string | string[]) {
    if (typeof(folders) == "string") {
        folders = folders.split(path.sep)
    }

    if (folders.length == 0) {
        return
    }
    folders.reduce((last, folder) => {
        const folderPath = last + path.sep + folder
        if (!fs.existsSync(folderPath)) {
            fs.mkdirSync(folderPath)
        }
        return folderPath
    })
}

class DirectoriesManager {

    private readonly root = this.initRoot()

    private initRoot() {
        const initDir = process.env.INIT_CWD
        if (initDir === undefined) {
            throw new Error(`Launch only from npm run`)
        }
        return initDir
    }

    constructor() {
        if (!this.root.includes('ets-plugin')) {
            throw new Error(`
                Launch only from subdirectory of koala-ui/ets-plugin
            `.trim())
        }
        this.root = this.root.split('ets-plugin')[0] + 'ets-plugin' // sets root to .../something/ets-plugin

        const dirs = [this.testsDir, this.goldenSpecificationDir, this.testPagesDir]
        dirs.forEach((dir) => {
            if (!fs.existsSync(dir)) {
                forceWriteFolders(dir)
            }
        })
    }

    get testsDir() {
        return path.resolve(this.root, './test/spec')
    }

    get testPagesDir() {
        return path.resolve(this.root, './test/spec/test/pages')
    }

    get goldenSpecificationDir() {
        return path.resolve(this.root, './test/golden/specification/')
    }

    get generatedDir() {
        return path.resolve(this.root, './test/generated/specification/')
    }

    private get repoPath() {
        return path.resolve(this.root, './test/specification/ets2bundle/')
    }

    private get specOptionsPath() {
        return path.resolve(this.root, './test/specification/spec-options.json')
    }

    private get specOptions() {
        const options = fs.readFileSync(this.specOptionsPath).toString()
        return JSON.parse(options)
    }

    getOrDownloadSpecificationTestsDir() {
        const dir = path.resolve(this.repoPath, './compiler/test/utForPartialUpdate')
        this.downloadDeveloptoolsEts2Bundle(dir)
        return dir
    }

    getOrDownloadSpecificationPagesDir() {
        const dir = path.resolve(this.repoPath, './compiler/test/pages')
        this.downloadDeveloptoolsEts2Bundle(dir)
        return dir
    }

    private downloadDeveloptoolsEts2Bundle(dir: string) {
        if (fs.existsSync(dir)) {
            console.log(`Found ${dir}, no need to download or patch`)
            return
        }

        const cloneTo = path.resolve(this.root, './test/specification/')

        if (!fs.existsSync(this.repoPath)) {
            this.run(
                cloneTo,
                `git init ets2bundle || true`
            )

            this.run(
                this.repoPath,
                `git remote add origin https://gitee.com/openharmony/developtools_ace_ets2bundle.git || true`,
                `git fetch --depth 1 origin ${this.specOptions['revision']}`,
                `git reset --hard FETCH_HEAD`
            )
        }

        this.run(
            this.repoPath,
            `git apply ../patches/*.patch`
        )

        if (!fs.existsSync(dir)) {
            throw new Error(`Somehow ${dir} still doesn't exist after cloning repo. Check developtoolsEts2Bundle files layout`)
        }
    }

    private run(where: string, ...commands: string[]) {
        commands.forEach(cmd =>
            child.execSync(`cd ${where} && ${cmd}`, { stdio: 'inherit' })
        )
    }
}

export const directoriesManager = new DirectoriesManager()

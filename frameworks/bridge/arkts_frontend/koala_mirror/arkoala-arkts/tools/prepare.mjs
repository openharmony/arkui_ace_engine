/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { cpSync, mkdirSync, readdirSync, readFileSync, rmSync, statSync, writeFileSync } from "node:fs"
import { EOL } from "node:os"
import { dirname, join, relative, resolve } from "node:path"

function scan(dir) {
    return statSync(dir).isDirectory()
        ? readdirSync(dir).flatMap(d => scan(join(dir, d)))
        : [dir]
}

function scanEts(dir) {
    return scan(dir).filter(file => file.endsWith('.ets') || file.endsWith('.ts'))
}

function scanRelativeEts(dir) {
    return scanEts(dir).map(file => relative(dir, file))
}

function processLines(lines) {
    const importDict = new Map()
    const nonImport = []
    const pattern = /^import\s*{([^}]+)}\s*from\s*(["\'])(.*?)\2\s*;?\s*$/
    for (const line of lines) {
        const stripped = line.trim()
        const matched = pattern.exec(stripped)
        if (matched) {
            const [,symbolsStr, , module] = matched
            const symbols = symbolsStr.split(',').map(it => it.trim())
            if (!importDict.has(module)) {
                importDict.set(module, new Set())
            }
            symbols.forEach(sym => {
                importDict.get(module).add(sym)
            })
        } else {
            nonImport.push(line)
        }
    }
    return [importDict, nonImport]
}

function dumpImports(imports) {
    const importLines = []
    for (const [module, symbols] of Array.from(imports).sort()) {
        const sorted = Array.from(symbols).sort()
        importLines.push(`import {${sorted.join(', ')}} from "${module}"`)
    }

    return importLines
}

function applyChanges(f1, f2, root) {
    const lines1 = readFileSync(f1, "utf-8")
    const lines2 = readFileSync(f2, "utf-8")

    const [imports1, nonImport1] = processLines(lines1.split('\n'))
    const [imports2, nonImport2] = processLines(lines2.split('\n'))

    const mergedImports = new Map()
    const imports12 = [imports1, imports2]
    imports12.forEach(table => {
        table.forEach((set, name) => {
            if (!mergedImports.has(name)) {
                mergedImports.set(name, new Set())
            }
            set.forEach(imp => {
                mergedImports.get(name).add(imp)
            })
        })
    })

    const importLines = dumpImports(mergedImports)
    writeFileSync(
        f1,
        importLines
            .concat(nonImport1)
            .concat(nonImport2)
            .join(EOL),
        'utf-8'
    )
}

function copyAndAdjust(src, dst, root) {
    const lines1 = readFileSync(src, "utf-8")
    const [imports, nonImport] = processLines(lines1.split('\n'))

    const importLines = dumpImports(imports)
    mkdirSync(dirname(dst), { recursive: true })
    writeFileSync(
        dst,
        importLines
            .concat(nonImport)
            .join(EOL),
        'utf-8'
    )
}

function applyGenerated(source, generated) {
    const sourceFiles = new Set(scanRelativeEts(source))
    const generatedFiles = scanRelativeEts(generated)

    for (const generatedFile of generatedFiles) {
        if (sourceFiles.has(generatedFile)) {
            applyChanges(join(source, generatedFile), join(generated, generatedFile), source)
        } else {
            copyAndAdjust(join(generated, generatedFile), join(source, generatedFile), source)
        }
    }
}

function copySrcDir(source, destination) {
    rmSync(destination, { force: true, recursive: true })
    cpSync(source, destination, { recursive: true })
}

function main([arkoalaArktsPath]) {
    arkoalaArktsPath = resolve(arkoalaArktsPath)

    const arkuiPath = join(arkoalaArktsPath, 'arkui')
    const arkuiSrc = join(arkuiPath, 'src')
    const arkuiPreparedSrc = join(arkuiPath, 'prepared')
    copySrcDir(arkuiSrc, arkuiPreparedSrc)

    const arkuiGeneratedSrc = join(arkuiPath, 'generated')

    applyGenerated(arkuiPreparedSrc, arkuiGeneratedSrc)
}
main(process.argv.slice(2))

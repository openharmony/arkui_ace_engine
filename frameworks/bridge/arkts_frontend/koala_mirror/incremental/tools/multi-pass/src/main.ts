/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { program } from "commander"
import * as fs from "fs"
import * as path from "path"
import { minimatch } from 'minimatch'

let replacedLines = 0

const options = program
    .option('--input-dirs <path>', 'Path to input file(s), comma separated')
    .option('--output-dir <path>', 'Path to output')
    .option('--rules <path>', 'Path JSON file with rules')
    .option('--includes <path>', 'Which files to process, *.ts by default')
    .parse()
    .opts()

main(options.inputDirs, options.rules, options.outputDir, options.includes?.split(",") ?? ["**/*.ts"])

function findMatching(base: string, include: string[], exclude: string[]): string[] {
    return fs.readdirSync(base, { recursive: true, withFileTypes: true })
        .map(it => path.join(it.parentPath, it.name))
                .filter(it => include.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
        .filter(it => !exclude.some(value => minimatch(it, path.join(base, value), {matchBase: true})))
}

function main(inputDirs: string, rules: string, outputDir: string, include: string[]) {
    let config = JSON.parse(fs.readFileSync(rules, 'utf8')) as string[2][]
    let baseDir = path.resolve(inputDirs)
    let exclude: string[] = []
    const files = findMatching(baseDir, include, exclude)
    if (files.length == 0) {
        throw new Error(`No files matching include "${include.join(",")}" exclude "${exclude.join(",")}"`)
    }
    fs.mkdirSync(outputDir, { recursive: true })
    multiReplace(inputDirs, outputDir, config, files)
}

function multiReplace(inputDir: string, outputDir: string, config: string[2][], files: string[]) {
    console.log(`Replace per ${config.map(it => `${it[0]} => ${it[1]}`)} in ${files.join(", ")} out to ${outputDir}`)
    let base = path.resolve(inputDir)
    let regexps: [RegExp, string][] = config.map(it => [new RegExp(it[0]), it[1]])
    files.forEach(file => {
        const wholeFile = fs.readFileSync(file, 'utf-8').split(/\r?\n/)
        const result: string[] = []
        wholeFile.forEach(line =>  {
            result.push(processPerRules(line, regexps))
        })
        let rel = path.relative(base, file)
        let newDir = path.join(outputDir, path.dirname(rel))
        fs.mkdirSync(newDir, { recursive: true })
        fs.writeFileSync(path.join(newDir, path.basename(rel)), result.join("\n"))
    })
    console.log(`Replaced ${replacedLines} lines`)
}

function processPerRules(line: string, rules: [RegExp, string][]): string {
    let procesedLine = line
    rules.forEach(rule => {
        procesedLine = procesedLine.replace(rule[0], rule[1])
    })
    if (procesedLine != line) replacedLines++
    return procesedLine
}
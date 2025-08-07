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

import * as fs from "node:fs"
import * as path from "node:path"
import { options } from "./main"

export const SPLITTER = "=".repeat(80)
export const BANNER = "[fast-arktsc]"
export const PLUGIN_DEPENDENCIES = "dependencies"
export const PLUGIN_NAME = "name"
export const LAST_STAGE = "_proceed_to_binary"

export function relativeOrDot(from: string, to: string) {
    const result = path.relative(from, to)
    if (result == "") {
        return "."
    }
    return result
}

export function log(text: string) {
    console.log(`${BANNER} ${text}`)
}

export function error(text: string, exitCode: number = 1): never {
    console.log(`${BANNER} ${text}`)
    process.exit(exitCode)
}

export function section() {
    log(SPLITTER)
}

export function getConfigFullPath() {
    return path.resolve(process.cwd(), options.config)
}

export function getConfigFullDirname() {
    return path.dirname(getConfigFullPath())
}

function filterPathSectionToMap(from: string, name: string, object: any): Map<string, string> {
    return new Map(
        Object.entries(object).map(([k, v]: [string, unknown]) => {
            if (typeof v == "string") {
                return [k, path.resolve(from, v)]
            }
            if (Array.isArray(v)) {
                return [k, path.resolve(from, v[0])]
            }
            error(`unexpected value of ${name}.${k}: ${v}`)
        })
    )
}

function getDependencyConfigs(from: string, dependencies: Map<string, string>): Map<string, any> {
    return new Map(
        Array.from(dependencies).map(([k, v]: [string, string]) => {
            const location = path.resolve(from, v)
            if (!fs.existsSync(location) || !fs.statSync(location).isFile()) {
                error(`no config found at ${location} (for package ${k})`)
            }
            return [k, JSON.parse(fs.readFileSync(location, 'utf-8'))]
        })
    )
}

function resolvePath(name: string, dependency?: string, config?: any) {
    const plugins = config?.compilerOptions?.plugins
    if (!plugins || !dependency) {
        return undefined
    }
    const pluginsArray = Array.from(plugins) as any[]
    for (var i = 0; i < pluginsArray.length; i++) {
        if (`${pluginsArray[i].name}-${pluginsArray[i].stage}` == name) {
            if (i == 0) {
                return undefined
            }
            return path.resolve(path.dirname(dependency), config.compilerOptions.outDir ?? ".", `${pluginsArray[i - 1].name}-${pluginsArray[i - 1].stage}` )
        }
    }
    if (name == LAST_STAGE) {
        return path.resolve(path.dirname(dependency), config.compilerOptions.outDir ?? ".", `${pluginsArray[pluginsArray.length - 1].name}-${pluginsArray[pluginsArray.length - 1].stage}` )
    }
    return undefined
}

function resolvePaths(name: string, paths: Map<string, string>, dependencies: Map<string, string>, dependencyConfigs: Map<string, any>) {
    return new Map(
        Array.from(paths).map(([k, v]: [string, string]) => {
            return [k, resolvePath(name, dependencies.get(k), dependencyConfigs.get(k)) ?? v]
        })
    )
}

/**
 * Checks that compilation with the given ui2abcconfig is possible and creates temporary arktsconfigs
 * 
 * @param configPath path to ui2abc configuration file
 * @returns path to first es2panda configuration file and intermediate build directories
 */
export function resolveConfig(configPath: string, restartStages: boolean): [string, string[]] {
    section()

    const config = JSON.parse(fs.readFileSync(configPath, 'utf8'))
    const compilerOptions = config.compilerOptions ?? { }
    const configDirname = getConfigFullDirname()
    const baseUrl = path.resolve(getConfigFullDirname(), compilerOptions?.baseUrl ?? ".")
    const outDir = path.resolve(getConfigFullDirname(), compilerOptions?.outDir ?? ".")
    const packageRoot = path.resolve(configDirname, baseUrl)
    const paths = filterPathSectionToMap(packageRoot, "paths", compilerOptions.paths ?? { })
    const pluginNames = (compilerOptions.plugins ?? []).map((plugin: any) => `${plugin.name}-${plugin.stage}`)
    const dependencies = filterPathSectionToMap(configDirname, PLUGIN_DEPENDENCIES, config[PLUGIN_DEPENDENCIES] ?? { })
    const dependencyConfigs = getDependencyConfigs(configDirname, dependencies)

    const stages = restartStages ? pluginNames.length + 1 : 1 // the last stage is a binary generation
    log(`stages: ${stages}`)

    const computedPlugins = Array.from(compilerOptions.plugins ?? []).map((it: any, i) => {
        if (!it.transform) {
            error(`no transform specified for plugin ${i}`)
        }
        if (it.transform.startsWith(`.`)) {
            return {
                ...it,
                transform: path.join(relativeOrDot(outDir, getConfigFullDirname()), it.transform),
            }
        }
        return it
    })

    const outDirs = []

    for (var i = 0; i < stages; i++) {
        const name = i == pluginNames.length ? LAST_STAGE : pluginNames[i]
        log(`  stage #${i + 1}: ${name}`)
        const resolvedPaths = resolvePaths(name, paths, dependencies, dependencyConfigs)
        log(`  paths:`)
        for (const [k, v] of resolvedPaths) {
            const res = relativeOrDot(packageRoot, v)
            log(`    ${k}: ${k.endsWith('*') && !res.endsWith('*') ? `${res}/*` : res}`)
        }

        for (const [k, v] of resolvedPaths) {
            let ext = path.extname(v)
            let isResolvedToFile = ext === ".ts" || ext === ".ets"
            if (isResolvedToFile) {
                try {
                    isResolvedToFile = fs.statSync(v).isFile()
                } catch (_e) {
                    isResolvedToFile = false
                }
            }
            if (!isResolvedToFile && (k.startsWith('@') || k.startsWith('#')) && !v.endsWith('*') && !fs.existsSync(path.join(v, "index.ts")) && !fs.existsSync(path.join(v, "index.ets"))) {
                error(`File ${v}/index.[ts|ets] does not exists`)
            }
        }

        const newBaseUrl = i == 0 ? relativeOrDot(outDir, baseUrl) : `./${pluginNames[i - 1]}`
        const pathsInConfig = Array.from(resolvedPaths).flatMap(([k, v]) => {
            if (!path.relative(baseUrl, v).startsWith('..')) {
                const res = relativeOrDot(path.resolve(baseUrl), v)
                return [[k, [k.endsWith('*') && !res.endsWith('*') ? `${res}/*` : res]]]
            }
            const from = path.resolve(outDir ?? `.`, newBaseUrl)
            const res = relativeOrDot(from, v)
            if (k.endsWith('*') && res.endsWith('*')) {
                const replaceTrailStar = (str: string, replaceStr: string = '') => {
                    if (str.length == 0 || str.charAt(str.length - 1) !== '*')
                        return str
                    return str.slice(0, -1) + replaceStr
                }
                const rmLeadSlash = (str: string) => {
                    if (str.startsWith("/"))
                        str = str.length > 1 ? str.substring(1) : ""
                    return str
                }
                const pattern = path.resolve(from, replaceTrailStar(res))
                const parent = path.parse(pattern).dir

                const ret: [string, string[]][] = []
                const traverseDir = (dir: string, filter: (file: string) => boolean, apply: (file: string) => void) => {
                    const dirents = fs.readdirSync(dir, { withFileTypes: true })
                    for (const entry of dirents) {
                        const fullPath = path.join(dir, entry.name)
                        if (entry.isDirectory())
                            traverseDir(fullPath, filter, apply)
                        else if (filter(fullPath))
                            apply(fullPath)
                    }
                }
                traverseDir(parent, file => file.endsWith(".d.ets") && file.startsWith(pattern), file => {
                    let resolvedStar = rmLeadSlash(file.substring(pattern.length))
                    let resolvedK = replaceTrailStar(k, resolvedStar)
                    resolvedK = resolvedK.substring(0, resolvedK.length - ".d.ets".length)
                    const resolvedV = replaceTrailStar(res, resolvedStar)
                    ret.push([resolvedK, [resolvedV]])
                })
                return ret
            }
            return [[k, [k.endsWith('*') && !res.endsWith('*') ? `${res}/*` : res]]]
        })

        const arktsconfig = {
            compilerOptions: {
                package: compilerOptions.package ?? `.`,
                outDir: `.`,
                baseUrl: newBaseUrl,
                paths: Object.fromEntries(pathsInConfig),
                plugins: i == 0 ? computedPlugins : [] // es2panda.js will only use check plugins from the first config
            },
            include: config.include ? Array.from(config.include as string[]).map((it) => {
                return path.join(path.relative(outDir ?? `.`, configDirname), it)
            }) : []
        }

        if (config.exclude) { // compiler might crash is exclude section is []
            (arktsconfig as any).exclude = config.exclude ? Array.from(config.exclude as string[]).map((it) => {
                return path.join(path.relative(outDir, configDirname), it)
            }) : []
        }

        const emitPath = path.resolve(outDir ?? `.`, `arktsconfig-${name}.json`)
        log(`  config emitted to ${emitPath}`)
        fs.mkdirSync(path.dirname(emitPath), { recursive: true })
        fs.writeFileSync(emitPath, JSON.stringify(arktsconfig, null, 2))

        const intermediateOutDir = path.resolve(getConfigFullDirname(), outDir ?? `.`, name == LAST_STAGE ? `.` : name)
        fs.mkdirSync(intermediateOutDir, { recursive: true })
        outDirs.push(intermediateOutDir)
    }

    return [
        path.resolve(getConfigFullDirname(), outDir ?? `.`, `arktsconfig-${pluginNames.length == 0 ? LAST_STAGE : pluginNames[0]}.json`),
        outDirs
    ]
}


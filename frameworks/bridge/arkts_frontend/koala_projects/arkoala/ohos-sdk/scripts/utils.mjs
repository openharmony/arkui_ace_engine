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

import path from "path"
import fs from "fs"
import { spawn, spawnSync } from "child_process"

export function capitalize(str) {
    return str[0].toUpperCase() + str.slice(1)
}

export function relativePath(from, to, posix = true) {
    const relative = path.relative(from ,to)
    return relative === "" ? "." : posix ? posixPath(relative) : relative
}

export function posixPath(path) {
    if (!path) return path
    return process.platform === "win32" ? path.replace(/\\/g, "/") : path
}

export function winPath(path) {
    if (!path) return path

    path = path.replace(/\//g, "\\")
    if (/^[a-zA-Z]:.*$/.test(path)) {
        return path
    }
    if (/^\\[a-zA-Z]\\.*$/.test(path)) {
        path = path.substring(1)
        path = path.slice(0, 1) + ":" + path.slice(1)
    }
    return path
}

/**
 * Converts the {@code path} to the current platform format.
 */
export function platformPath(path) {
    return process.platform === "win32" ? winPath(path) : posixPath(path)
}

/**
 * Copies a directory recursively.
 *
 * @param srcDirPath the source dir path
 * @param dstDirPath the destination dir path
 * @param logException whether to log an exception if it's thrown
 * @return true if success, false otherwise
 */
export function copyDirSync(srcDirPath, dstDirPath, logException = false) {
    return copyOrMoveDirSync(srcDirPath, dstDirPath, false, () => true, logException)
}

/**
 * Copies a directory recursively with filter: (src, dst) => boolean
 *
 * @see copyDirSync
 */
export function copyDirFilterSync(srcDirPath, dstDirPath, filter,  logException = false) {
    return copyOrMoveDirSync(srcDirPath, dstDirPath, false, filter, logException)
}

/**
 * Moves a directory.
 *
 * @param srcDirPath the source dir path
 * @param dstDirPath the destination dir path
 * @param logException whether to log an exception if it's thrown
 * @return true if success, false otherwise
 */
export function moveDirSync(srcDirPath, dstDirPath, logException = false) {
    return copyOrMoveDirSync(srcDirPath, dstDirPath, true, () => true, logException)
}

/**
 * Moves a directory with filter: (src, dst) => boolean
 *
 * @see moveDirSync
 */
export function moveDirFilterSync(srcDirPath, dstDirPath, filter, logException = false) {
    return copyOrMoveDirSync(srcDirPath, dstDirPath, true, filter, logException)
}

function copyOrMoveDirSync(srcDirPath, dstDirPath, removeSrcDir, filter = (src, dst) => true, logException = false) {
    try {
        fs.mkdirSync(dstDirPath, { recursive: true })
        fs.cpSync(srcDirPath, dstDirPath, { recursive: true, force: true, filter: filter })
        if (removeSrcDir) fs.rmSync(srcDirPath, { recursive: true, force: true })
    } catch (e) {
        if (logException) console.log(e)
        return false
    }
    return true
}

/**
 * Check a directory for empty
 *
 * @param path the source dir path
 * @returns true if empty
 */
export function isEmptyDir(path) {
    return fs.readdirSync(path).length === 0
}

/**
 * Parses {@link jsonFilePath} and returns the parsed data object.
 */
export function parseJsonSync(jsonFilePath) {
    return JSON.parse(fs.readFileSync(jsonFilePath, 'utf8'))
}

// BEGIN "LAZY"

/**
 * Creates a new lazy pool which can be used to release lazy values added to it.
 */
export function createLazyPool() {
    const pool = {
        list: [],

        /**
         * Creates a new lazy value and adds it to this pool.
         */
        lazy: initializer => {
            const func = lazy(initializer)
            pool.add(func)
            return func
        },

        /**
         * Adds a lazy value to this pool.
         */
        add: lazyFunc => pool.list.push(lazyFunc),

        /**
         * Releases all the lazy values addded to this pool.
         *
         * @see releaseLazyValue
         */
        release: () => pool.list.forEach(lazyFunc => releaseLazyValue(lazyFunc))
    }
    return pool
}

const DEFAULT_LAZY_POOL = createLazyPool()

/**
 * Returns default lazy pool.
 *
 * @see lazy
 */
export function defaultLazyPool() {
    return DEFAULT_LAZY_POOL
}

/**
 * Creates a lazy value and adds it to the default lazy pool.
 *
 * Usage:
 *
 * const myValue = lazy(() => computeMyValue())
 * const useMyValue = myValue()             // computes and returns the value
 * const anotherUseMyValue = myValue()      // just returns the value
 *
 * const myValue2 = lazy(initArg => computeMyValue2(initArg))
 * const useMyValue2 = myValue2("alpha")    // inits, computes and returns the value
 * const anotherUseMyValue2 = myValue2()    // just returns the value
 *
 * @see defaultLazyPool
 */
export function lazy(initializer) {
    return lazyImpl(initializer)
}

/**
 * Creates a lazy value with async initializer.
 *
 * @see lazy
 */
export function lazyAsync(initializerAsync) {
    return lazyImplAsync(initializerAsync)
}

function lazyImpl(initializer) {
    const holder = {
        value: undefined,
        initialized: false,

        init: (arg = undefined) => {
            holder.value = initializer(arg)
            holder.initialized = true
        },
        get: (arg = undefined) => {
            if (!holder.initialized)
                holder.init(arg)
            return holder.value
        },
        release: () => {
            holder.value = undefined
            holder.initialized = false
        }
    }
    function LazyFunc(arg = undefined, __holderReceiver = undefined) {
        if (__holderReceiver) {
            __holderReceiver(holder)
            return undefined
        }
        return holder.get(arg)
    }
    DEFAULT_LAZY_POOL.add(LazyFunc)
    return LazyFunc
}

function lazyImplAsync(initializerAsync) {
    const holder = {
        value: undefined,
        initialized: false,

        initAsync: async (arg = undefined) => {
            return new Promise(resolve => {
                initializerAsync(arg).then(value => {
                    holder.initialized = true
                    holder.value = value
                    resolve(value)
                })
            })
        },
        getAsync: async (arg = undefined) => {
            if (!holder.initialized) {
                return new Promise(resolve => {
                    holder.initAsync(arg).then(value => resolve(value))
                })
            }
            return holder.value
        },
        release: () => {
            holder.value = undefined
            holder.initialized = false
        }
    }
    async function LazyFuncAsync(arg = undefined, __holderReceiver = undefined) {
        if (__holderReceiver) {
            __holderReceiver(holder)
            return undefined
        }
        return holder.getAsync(arg)
    }
    DEFAULT_LAZY_POOL.add(LazyFuncAsync)
    return LazyFuncAsync
}

/**
 * Forces the lazy value to re-initialize on the next read.
 */
export function releaseLazyValue(lazyFunc) {
    lazyFunc(undefined, holder => holder.release())
}

/**
 * Returns whether the lazy value has been initialized.
 */
export function lazyValueInitialized(lazyFunc) {
    let initialized = false
    lazyFunc(undefined, holder => initialized = holder.initialized)
    return initialized
}

// END "LAZY"

/**
 * Executes a command and returns a promise with its stdout as string.
 * @options { workdir, syncMode instantLogging, onExit: (stdout, stderr): void, onError: (err): void }
 */
export async function execCmd(cmd, cmdArgs, options) {
    options = {
        workdir: process.cwd(),
        instantLogging: false,
        shell: true,
        onExit: (stdout, stderr) => noop(stdout, stderr),
        onError: (err) => options.ignoreError ? noop() : new Error(`> '${cmd} ${cmdArgs.join(" ")}' failed: ${err}`),
        ignoreError: false,
        logCmdArgs: false,
        ...options
    }
    if (options.logCmdArgs) {
        console.log(`> [exec] ${cmd} ${cmdArgs?.join(" ")}`)
    }
    if (options.syncMode) {
        (() => {
            spawnSync(cmd, cmdArgs, {
                stdio: 'inherit',
                shell: options.shell,
                cwd: options.workdir
            })
        })()
        return Promise.resolve(undefined)
    }

    const promise = new Promise((resolve, reject) => {
        const proc = spawn(cmd, cmdArgs, {
            shell: options.shell,
            cwd: options.workdir
        })

        let stdout = ""
        let stderr = ""
        proc.stdout.on('data', data => {
            const dataStr = data.toString()
            stdout += dataStr
            if (options.instantLogging) process.stdout.write(dataStr)
        })
        proc.stderr.on('data', data => {
            const dataStr = data.toString()
            stderr += dataStr
            if (options.instantLogging) process.stderr.write(dataStr)
        })

        proc.on("exit", code => {
            options.onExit(stdout, stderr)
            if (code === 0 || options.ignoreError)
                resolve(stdout.trim())
            else if (code == null)
                reject(options.onError("code: undefined"))
            else
                reject(options.onError(`code: ${code}; stderr: ${stderr}`))
        })
        if (!options.ignoreError)
            proc.on("error", err => reject(options.onError(err)))
    })
    return options.ignoreError ? promise.catch(() => {}) : promise
}

/**
 * extract archives of zip and tgz format from the inPath
 * if no output path is specified, the current default directory is used
 */
export async function extract(inPath, outPath, stripPrefix) {
    return new Promise((resolve, reject) => {
        let options = {}
        if (stripPrefix) {
            if (!stripPrefix.endsWith("/")) stripPrefix += "/"
            options.map = file => {
                if (file.path.startsWith(stripPrefix)) file.path = file.path.slice(stripPrefix.length)
                return file
            }
        }
        if (!outPath) outPath = path.parse(inPath).dir

        import("decompress").then((module => {
            module.default(inPath, outPath, options).then(() => resolve()).catch(err => reject(err))
        }))
    })
}

export function splitLines(content) {
    return content.split(/\r?\n/)
}

export function splitFileLines(file) {
    const content = fs.readFileSync(file, { encoding: 'utf-8' })
    return splitLines(content)
}

export function noop(...args) {}

export function ensureEnvVarSet(envVarName, defaultValue, log = false) {
    if (!process.env[envVarName]) {
        process.env[envVarName] = defaultValue
    }
    if (log) console.log(`> ${envVarName}=` + process.env[envVarName])
}

export function assertExists(path, message) {
    if (!fs.existsSync(path)) {
        if (!message) message = "path not found"
        console.error(`> error: ${message}: ${path}`)
        process.exit(1)
    }
}

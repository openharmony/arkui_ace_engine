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
import { lazy, parseJsonSync, platformPath } from "./utils.mjs"
import { OH_SDK_COMPONENT, ohSdkInfo, platformName } from "./oh-sdk-utils.mjs"
import json5 from "json5"

export const DEFAULT_OHCONF_PATH = path.join(process.cwd(), ".ohconf.json")

export const PROJECT_MOD_APP = "app"
export const PROJECT_MOD_TEST = "test"

// env variable variants in priority order
const OH_SDK_PATH_NAMES = [
    "DEVECO_SDK_HOME",
    "HOS_SDK_HOME",
    "OHOS_SDK_PATH"
]

/**
 * Provides access to ".ohconf.json" data specified by {@link ohConfPath}.
 */
export function ohConf(ohConfPath = DEFAULT_OHCONF_PATH, failIfAbsent = true) {
    if (ohConfPath) {
        ohConfPath = path.resolve(ohConfPath)
    }
    if (!fs.existsSync(ohConfPath)) {
        if (failIfAbsent)
            throw new Error(`> Can't find '.ohconf.json' by path: '${ohConfPath}'`)
        ohConfPath = undefined
    }
    const ohConf = {
        /**
         * Returns this config's path.
         */
        config: ohConfPath,

        /**
         * Returns OpenHarmony SDK version defined in the config.
         *
         * @param failIfAbsent whether to fail if the version is not found
         */
        sdkVersion: (failIfAbsent = true) => {
            return ohConfValue(ohConfPath, "ohos_sdk_version", false, failIfAbsent)
        },

        /**
         * Returns OpenHarmony SDK path.
         *
         * @param failIfAbsent whether to fail if SDK is not found
         */
        sdkPath: (failIfAbsent = true) => {
            let result
            if (ohConf.config) {
                result = ohConf.value("ohos_sdk_path", true, failIfAbsent)
                if (fs.existsSync(result))
                    return result
            }
            for (const name of OH_SDK_PATH_NAMES) {
                result = platformPath(process.env[name])
                if (fs.existsSync(result))
                    return result
            }
            if (failIfAbsent)
                throw new Error(`> Can't find OpenHarmony SDK path in '.ohconf.json' '${ohConf.config}'`)
            return undefined
        },

        /**
         * Returns the path to the HDC tool in the OpenHarmony SDK.
         *
         * @param failIfAbsent whether to fail if HDC is not found
         */
        hdcPath: (failIfAbsent = true) => {
            const sdkPath = ohConf.sdkPath()
            const sdkInfo = ohSdkInfo(sdkPath, OH_SDK_COMPONENT.toolchains)
            const hdcName = "hdc"
            let hdc = path.join(sdkInfo.path, hdcName)
            hdc = platformName() === "windows" ? `${hdc}.exe` : hdc
            if (failIfAbsent && !fs.existsSync(hdc))
                throw new Error(`> Can't find HDC in '${sdkInfo.path}'`)
            return hdc
        },

        /**
         * Returns a value of the {@link key} in the ["path"] group.
         *
         * @param key a single string key, or an array of string keys
         * @param failIfAbsent whether to fail if the key is not found
         */
        path: (key, failIfAbsent = true) => {
            if (!ohConf.config) {
                if (failIfAbsent)
                    throw new Error(`> Can't find path for key: '${key}'`)
                return undefined
            }
            const keys = key.constructor === Array ? ["path", ...key] : ["path", key]
            return ohConfValue(ohConfPath, keys, true, failIfAbsent)
        },

        /**
         * Returns a value of the {@link key} in the ["name"] group.
         *
         * @param key a single string key, or an array of string keys
         * @param failIfAbsent whether to fail if the key is not found
         */
        name: (key, failIfAbsent = true) => {
            if (!ohConf.config) {
                if (failIfAbsent)
                    throw new Error(`> Can't find name for key: '${key}'`)
                return undefined
            }
            const keys = key.constructor === Array ? ["name", ...key] : ["name", key]
            return ohConfValue(ohConfPath, keys, false, failIfAbsent)
        },

        /**
         * Returns a value of the {@link key}.
         *
         * @param key a single string key, or an array of string keys
         * @param asPath whether to treat the value as path
         * @param failIfAbsent whether to fail if the key is not found
         */
        value: (key, asPath = false, failIfAbsent = true) => {
            return ohConfValue(ohConfPath, key, asPath, failIfAbsent)
        }
    }
    return ohConf
}

/**
 * Returns {@link ohConf} with default path.
 */
export function ohConfDefault(failIfAbsent = true) {
    return ohConf(DEFAULT_OHCONF_PATH, failIfAbsent)
}

function ohConfValue(ohConfPath, key, asPath = false, failIfAbsent = true) {
    if (!ohConfPath) {
        if (failIfAbsent)
            throw new Error(`> Can't find value for key: '${key}'`)
        return undefined
    }
    const parsePath = (pathValue) => {
        if (path.isAbsolute(pathValue)) return pathValue
        const root = path.resolve(path.dirname(ohConfPath))
        return path.normalize(path.join(root, pathValue))
    }
    const content = parseJsonSync(ohConfPath)
    let value = undefined

    if (key.constructor === Array) {
        try {
            value = content
            key.forEach(k => value = value[k])
        } catch (e) {
        }
    }
    else {
        value = content[key]
    }
    if (!value) {
        if (failIfAbsent)
            throw new Error(`> Can't find [${key}] in '.ohconf.json' '${ohConfPath}'`)
        return undefined
    }
    if (value.constructor === Array) {
        const arr = []
        value.forEach(v => arr.push(asPath ? parsePath(v) : v))
        return arr
    }
    if (value.startsWith("$ohconf:")) {
        const refOhConfPath = path.join(path.dirname(ohConfPath), value.substring("$ohconf:".length))
        return ohConfValue(refOhConfPath, key, asPath, failIfAbsent)
    }
    if (asPath) {
        return parsePath(value)
    }
    return value
}

/**
 * Supplements {@link ohConf} data with OH project settings.
 *
 * It's possible that ".ohconf.json" does not exist at all, in which case only OH project settings are taken into account.
 *
 * @param ohConfPath path to ".ohconf.json"
 * @param ohProjectRoot optional OH project root (defaults to "ohConfPath" dirname, or CWD)
 */
export function ohProjectConf(ohConfPath = DEFAULT_OHCONF_PATH, ohProjectRoot = undefined) {
    const _ohConf = ohConf(ohConfPath, false)
    if (!_ohConf.config) {
        if (!ohProjectRoot)
            ohProjectRoot = process.cwd()

        // rely on OH project settings only
        if (!fs.existsSync(path.join(ohProjectRoot, "build-profile.json5")) ||
            !fs.existsSync(path.join(ohProjectRoot, "AppScope/app.json5"))) {
            // throw new Error(`> No '.ohconf.json' found (try '--oh-conf' option) and the OpenHarmony project root is invalid: '${ohProjectRoot}'`)
            console.error(`> error: ArkUI project root is invalid: ${ohProjectRoot}`)
            process.exit(1)
        }
    }
    else if (!ohProjectRoot) {
        ohProjectRoot = path.dirname(_ohConf.config)
    }

    const lzModuleName = lazy(() => {
        const data = fs.readFileSync(path.join(ohProjectRoot, "build-profile.json5"), { encoding: 'utf8' })
        const content = json5.parse(data)
        return content["modules"][0]["name"]
    })

    const lzModulePath = lazy(() => {
        const data = fs.readFileSync(path.join(ohProjectRoot, "build-profile.json5"), { encoding: 'utf8' })
        const content = json5.parse(data)
        return content["modules"][0]["srcPath"]
    })

    const lzBundleName = lazy(() => {
        const data = fs.readFileSync(path.join(ohProjectRoot, "AppScope/app.json5"), { encoding: 'utf8' })
        const content = json5.parse(data)
        return content["app"]["bundleName"]
    })

    const lzAppAbilityName = lazy(() => {
        const data = fs.readFileSync(path.join(ohProjectRoot, `${lzModulePath()}/src/main/module.json5`), { encoding: 'utf8' })
        const content = json5.parse(data)
        return content["module"]["abilities"][0]["name"]
    })

    const lzTestAbilityName = lazy(() => {
        const data = fs.readFileSync(path.join(ohProjectRoot, `${lzModulePath()}/src/ohosTest/module.json5`), { encoding: 'utf8' })
        const content = json5.parse(data)
        return content["module"]["abilities"][0]["name"]
    })

    return {
        /**
         * OH project root
         */
        root: ohProjectRoot,

        /**
         * OH project main module name
         */
        moduleName: (mod = PROJECT_MOD_APP) => lzModuleName() + (mod === PROJECT_MOD_TEST ? "_test" : ""),

        /**
         * OH project main module src path (relative to the project root)
         */
        modulePath: () => lzModulePath(),

        /**
         * OH project bundle name
         */
        bundleName: () => lzBundleName(),

        /**
         * OH project main ability name
         *
         * @param mod project mode: "app", "test"
         */
        abilityName: (mod = PROJECT_MOD_APP) => {
            if (mod === PROJECT_MOD_APP)
                return lzAppAbilityName()
            if (mod === PROJECT_MOD_TEST)
                return lzTestAbilityName()
            return undefined
        },

        /**
         * OH project HAP file path
         *
         * @param mod project mode: "app", "test"
         */
        hapPath: (mod = PROJECT_MOD_APP) => {
            if (mod === PROJECT_MOD_APP)
                return path.join(ohProjectRoot,
                    `${lzModulePath()}/build/default/outputs/default/${lzModuleName()}-default-signed.hap`)
            if (mod === PROJECT_MOD_TEST)
                return path.join(ohProjectRoot,
                    `${lzModulePath()}/build/default/outputs/ohosTest/${lzModuleName()}-ohosTest-signed.hap`)
            return undefined
        },

        /**
         * @override
         */
        config: _ohConf.config,

        /**
         * @override
         */
        sdkVersion: (failIfAbsent = true) => {
            return _ohConf.sdkVersion(failIfAbsent)
        },

        /**
         * @override
         */
        sdkPath: (failIfAbsent = true) => {
            return _ohConf.sdkPath(failIfAbsent)
        },

        /**
         * @override
         */
        hdcPath: (failIfAbsent = true) => {
            return _ohConf.hdcPath(failIfAbsent)
        },

        /**
         * @override
         */
        path: (key, failIfAbsent = true) => {
            return _ohConf.path(key, failIfAbsent)
        },

        /**
         * @override
         */
        name: (key, failIfAbsent = true) => {
            return _ohConf.name(key, failIfAbsent)
        },

        /**
         * @override
         */
        value: (key, asPath = false, failIfAbsent = true) => {
            return _ohConf.value(key, asPath, failIfAbsent)
        }
    }
}

export function ensureExists(fileOrDirPath, create = false) {
    if (create)
        fs.mkdirSync(fileOrDirPath, { recursive: true })
    if (!fs.existsSync(fileOrDirPath))
        throw new Error(`> Can't find '${fileOrDirPath}'`)
    return fileOrDirPath
}

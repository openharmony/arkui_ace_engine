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
import chalk from "chalk"
import os from "os"
import { ohConfDefault } from "./ohconf.mjs"
import { copyDirSync, isEmptyDir, moveDirSync, parseJsonSync } from "./utils.mjs"
import { execSync } from "child_process"

/**
 * Current ETS API version.
 */
export const ETS_API_VERSION = 12

/**
 * Max OpenHarmony legacy SDK version.
 */
export const MAX_LEGACY_OHSDK_VERSION = {
    major: 5,
    minor: 0,
    patch: 0,
    revision: 24
}

/**
 * OpenHarmony SDK component.
 */
export const OH_SDK_COMPONENT = {
    ets: "ets",
    js: "js",
    native: "native",
    toolchains: "toolchains",
    previewer: "previewer"
}

const OH_UNI_PACKAGE_NAME = "oh-uni-package.json"

/**
 * Downloads command-line-tools archive from Nexus.
 *
 * @param {string} dstPath - Path to save the downloaded archive.
 */
export async function downloadCliTools(destination) {
    const packageName = "command-line-tools"
    const packageVersion = "5.0.3502"
    const fileName = `${packageName}.${packageVersion}.zip`
    const destPath = path.join(destination, packageName)

    log(`> Checking if command-line-tools ${packageVersion} needs to be downloaded...`)

    if (fs.existsSync(destPath)) {
        if (!isEmptyDir(destPath)) {
            log(`> command-line-tools directory already exists and is not empty. Skipping download.`)
            return
        }
        log(`> command-line-tools directory is empty. Proceeding with download...`)
    }

    const useOpenLab = !!parseInt(process.env.KOALA_BZ ?? "0")

    if (useOpenLab) {
        log("> Using OpenLab for package download.")
        const { generic_package_archive_openlab } = await import("./openlab.mjs")
        await generic_package_archive_openlab(
            packageName,
            packageVersion,
            fileName,
            destPath,
            null
        )
    } else {
        log("> Using GitLab for package download.")
        const { generic_package_archive_gitlab } = await import("./gitlab.mjs")
        await generic_package_archive_gitlab(
            packageName,
            packageVersion,
            fileName,
            destPath,
            null
        )
    }

    log(`> command-line-tools ${packageVersion} downloaded to ${destPath}`)

    try {
        log("> Setting permissions for command-line-tools...")

        const ohpmBinPath = path.join(destPath, "ohpm/bin");
        const hvigorBinPath = path.join(destPath, "hvigor/bin");

        if (fs.existsSync(ohpmBinPath)) {
            log(`> Setting permissions for ${ohpmBinPath}`);
            execSync(`chmod -R 755 ${ohpmBinPath}`, { stdio: "inherit" });
        }

        if (fs.existsSync(hvigorBinPath)) {
            log(`> Setting permissions for ${hvigorBinPath}`);
            execSync(`chmod -R 755 ${hvigorBinPath}`, { stdio: "inherit" });
        }

        log("> Permissions set successfully.");
    } catch (error) {
        log("> Error setting permissions:", error);
    }

    log("> CLI tools have been installed successfully")
}

/**
 * Downloads OpenHarmony SDK.
 *
 * @param dstPath path to download
 * @param sdkComponent optional SDK component to identify the SDK archive
 * @param sdkVersion SDK version, or default
 * @param logIfExists logs if SDK already exists at the provided {@link dstPath}
 */
export async function downloadOhSdk(
    dstPath,
    sdkVersion,
    sdkComponent = undefined,
    logIfExists = true
) {
    const sdkName = sdkComponent ? `SDK/${sdkComponent}` : "SDK"

    if (fs.existsSync(dstPath)) {
        let currentSdkInfo = ohSdkInfo(dstPath, OH_SDK_COMPONENT.ets, false)
        let currentSdkVersion = currentSdkInfo.version
        if (currentSdkVersion === sdkVersion) {
            if (logIfExists) log(`> OpenHarmony ${sdkName} ${currentSdkVersion} is found at ${dstPath}`)
            return false
        }
        let archSdk = path.normalize(path.join(dstPath, `../${path.basename(dstPath)}.${currentSdkVersion}`))

        if (currentSdkVersion != undefined) {
            let n = 1
            while (fs.existsSync(archSdk)) archSdk = `${archSdk}(${n++})`
                log(`> Saving current OpenHarmony ${sdkName} ${currentSdkVersion} to '${archSdk}'...`)
                if (!moveDirSync(dstPath, archSdk)) {
                    error(`> Failed to remove '${dstPath}'! Please do it manually.`)
                    return false
                }
        }
    }

    log(`> Downloading OpenHarmony ${sdkName} ${sdkVersion} to ${dstPath}...`)
    const packageVersion = ohSdkVersionToPackageVersion(sdkVersion)
    let packageName = sdkComponent ? "ohos-sdk-" + sdkComponent : "ohos-sdk"
    let fileName = sdkComponent ?
        `${packageName}-${sdkVersion}.zip` :
        `${packageName}-${sdkVersion}-${platformName()}.zip`

    if (!!parseInt(process.env.KOALA_BZ ?? "0")) {
        const { generic_package_archive_openlab } = await import("./openlab.mjs")
        await generic_package_archive_openlab(
            packageName,
            packageVersion,
            fileName,
            dstPath,
            null,
            // We patch ohos-sdk-ets directory,
            // so can't use symlink here.
            // It is lightweight anyways.
            sdkComponent === OH_SDK_COMPONENT.ets
        )
    } else {
        const { generic_package_archive_gitlab } = await import("./gitlab.mjs")
        await generic_package_archive_gitlab(
            packageName,
            packageVersion,
            fileName,
            dstPath,
            null,
            // We patch ohos-sdk-ets directory,
            // so can't use symlink here.
            // It is lightweight anyways.
            sdkComponent === OH_SDK_COMPONENT.ets
        )
    }
    return true
}

/**
 * Downloads OpenHarmony SDK ETS API to {@link dstPath}.
 */
export async function downloadOhSdkEtsApi(dstPath, version) {
    if (fs.existsSync(dstPath)) {
        if (version !== ohSdkVersion(dstPath, false)) {
            try {
                fs.rmSync(dstPath, {recursive: true, force: true})
            } catch (e) {
                error(`> Failed to remove '${dstPath}'! Please do it manually.`)
                return false
            }
        } else {
            log(`> OpenHarmony SDK API ${version} is found at ${dstPath}`)
            return
        }
    }
    const ohSdkFileName = "ohos-sdk." + process.pid
    let tmp = (!process.env.BUILD_DIR) ?
        path.resolve(path.join(os.tmpdir(), ohSdkFileName)) :
        path.resolve(path.join(process.env.BUILD_DIR, ohSdkFileName))


    try {
        log(`Getting ZIP to ${tmp}`)
        await downloadOhSdk(tmp, version, OH_SDK_COMPONENT.ets, false)
        const sdkInfo = ohSdkInfo(tmp, OH_SDK_COMPONENT.ets)

        log(`> Copying OpenHarmony SDK API ${version} to '${dstPath}'`)
        fs.mkdirSync(dstPath)
        const etsPath = sdkInfo.path
        const srcApi = path.join(etsPath, "api")
        const dstApi = path.join(dstPath, "api")
        if (copyDirSync(srcApi, dstApi, true)) {
            const ohUniPackagePath = path.join(etsPath, OH_UNI_PACKAGE_NAME)
            if (fs.existsSync(ohUniPackagePath)) {
                fs.copyFileSync(ohUniPackagePath, path.join(dstPath, OH_UNI_PACKAGE_NAME))
            }
        }
    } finally {
        fs.rmSync(tmp, { recursive: true, force: true })
    }
}

export async function downloadOhSdkPrebuiltEts(dstPath, version) {
    if (fs.existsSync(dstPath) && !isEmptyDir(dstPath)) return

    const packageVersion = version
    let packageName = "ohos-sdk-prebuilt"
    let fileName = `ets-${platformName()}-x64-${packageVersion}-Canary.zip`

    if (!!parseInt(process.env.KOALA_BZ ?? "0")) {
        const { generic_package_archive_openlab } = await import("./openlab.mjs")
        await generic_package_archive_openlab(
            packageName,
            packageVersion,
            fileName,
            dstPath,
            null
        )
    } else {
        const { generic_package_archive_gitlab } = await import("./gitlab.mjs")
        await generic_package_archive_gitlab(
            packageName,
            packageVersion,
            fileName,
            dstPath,
            null
        )
    }
}

/**
 * Returns OpenHarmony SDK info:
 * path: a path to the requested {@link OH_SDK_COMPONENT}
 * version: SDK version
 * legacy: whether the SDK version is legacy
 *
 * @see MAX_LEGACY_OHSDK_VERSION
 */
export function ohSdkInfo(sdkPath, sdkComponent = OH_SDK_COMPONENT.ets, failIfUnknown = true) {
    const openHarmonyNextNames = [
        "HarmonyOS-NEXT-DB1",
        "HarmonyOS-NEXT-DP1",
        "HarmonyOS-NEXT-DP2"
    ]
    openHarmonyNextNames.forEach(dirName => {
        const openHarmonyNextPath = path.join(sdkPath, dirName)
        if (fs.existsSync(openHarmonyNextPath)) {
            sdkPath = openHarmonyNextPath
            return
        }
    })

    const basePath = path.join(sdkPath, "openharmony")
    const hmsPath = path.join(sdkPath, "hms") // Maybe use

    let sdkBaseComponentPath = path.join(basePath, `${sdkComponent}`)
    let sdkHmsComponentPath = path.join(hmsPath, `${sdkComponent}`)
    let version = undefined

    version = ohSdkVersion(path.join(basePath, OH_SDK_COMPONENT.ets), false)

    return {
        path: sdkBaseComponentPath,
        hmsPath: sdkHmsComponentPath,
        version: version,
    }
}

function ohSdkVersion(sdkEtsPath, failIfUnknown = true) {
    const ohUniPackagePath = path.join(sdkEtsPath, OH_UNI_PACKAGE_NAME)
    if (!fs.existsSync(ohUniPackagePath)) {
        if (failIfUnknown)
            throw Error(`OpenHarmony SDK '${OH_UNI_PACKAGE_NAME}' is not found at: ${sdkEtsPath}`)
        return undefined
    }
    const data = parseJsonSync(ohUniPackagePath)
    return data["version"]
}

/**
 * Returns OpenHarmony SDK version object.
 */
export function parseOhSdkVersion(ohSdkVersion, failIfUnknown = true) {
    const match = ohSdkVersion.match(/^(\d+).(\d+).(\d+).(\d+)$/)
    if (match) {
        const version = match.splice(1)
        return {
            major: parseInt(version[0]),
            minor: parseInt(version[1]),
            revision: parseInt(version[2]),
            patch: parseInt(version[3])
        }
    }
    if (failIfUnknown)
        throw Error(`unknown OpenHarmony SDK version: ${ohSdkVersion}`)
    return undefined
}

/**
 * Transforms OpenHarmony SDK version to gitlab package version format.
 */
export function ohSdkVersionToPackageVersion(ohSdkVersion, failIfUnknown = true) {
    const version = parseOhSdkVersion(ohSdkVersion, failIfUnknown)
    return `${version.major}.${version.minor}.${version.revision}${version.patch}`
}

/**
 * Returns path to 'hdc' tool.
 */
export function hdc(failIfAbsent = true) {
    const sdkPath = ohConfDefault(false).sdkPath()
    const sdkInfo = ohSdkInfo(sdkPath, OH_SDK_COMPONENT.toolchains)
    const hdcName = "hdc"
    let hdc = path.join(sdkInfo.path, hdcName)
    hdc = platformName() === "windows" ? `${hdc}.exe` : hdc
    if (failIfAbsent && !fs.existsSync(hdc)) {
        console.error(`> hdc not found in '${sdkInfo.path}'`)
        process.exit(1)
    }
    return hdc
}

/**
 * Returns platform name.
 */
export function platformName() {
    switch (process.platform) {
        case "win32": return "windows"
        case "linux": return "linux"
        case "darwin": return "macos"
        default: throw Error("unsupported platform " + process.platform)
    }
}

function log(msg) {
    console.log(chalk.green(msg))
}

function error(msg) {
    console.error(chalk.red(msg))
}

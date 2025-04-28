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

import fs from "fs";
import path from "path";
import child_process from "child_process";

const originRuntime = "https://gitee.com/openharmony/arkcompiler_runtime_core"
const originFrontend = "https://gitee.com/openharmony/arkcompiler_ets_frontend"

console.log("Required packages and utilities:\n" +
    "Ubuntu: clang-14, lcov, libdwarf-dev, jinja2, cmake, ninja (apt install -y clang-14 lcov libdwarf-dev python3-pip cmake ninja-build && pip install jinja2-cli)")

const argv = new Map(process.argv.slice(2).map(it => it.split("=")))
const pandaSdkDir = argv.get("--panda-sdk-dir")
const arkCompilerDir = argv.get("--arkcompiler-build-dir")
const buildType = argv.get("--build-type") ?? "Release"
const rtGitRev = argv.get("--runtime-git-rev")
const feGitRev = argv.get("--frontend-git-rev")
const feGitPatches = argv.get("--frontend-git-patches")?.split(":") ?? []

if (arkCompilerDir === undefined) {
    console.log("--arkcompiler-build-dir argument is required")
    process.exit(1)
}
if (pandaSdkDir === undefined) {
    console.log("--panda-sdk-dir argument is required")
    process.exit(1)
}

const feDir = path.join(arkCompilerDir, "ets_frontend")
const rtDir = path.join(arkCompilerDir, "runtime_core")
const staticCoreDir = path.join(rtDir, "static_core")

makeDir(arkCompilerDir)

gitClone(originRuntime, rtDir)
if (rtGitRev !== undefined) {
    gitCheckout(rtDir, rtGitRev)
}
gitClone(originFrontend, feDir)
if (feGitRev !== undefined) {
    gitCheckout(feDir, feGitRev)
}
feGitPatches.forEach(it => {
    child_process.spawnSync("git", ["apply", path.resolve(it)],
        {stdio: "inherit", cwd: feDir})
})

makeSymlink(path.join(feDir, "ets2panda"), path.join(staticCoreDir, "tools/es2panda"))

const buildDir = path.join(staticCoreDir, "build")
makeDir(buildDir)

child_process.spawnSync("cmake", [
        `-B${buildDir}`,
        `-S${staticCoreDir}`,
        "-GNinja",
        `-DCMAKE_BUILD_TYPE=${buildType}`,
        `-DCMAKE_TOOLCHAIN_FILE=${path.join(staticCoreDir, "cmake/toolchain/host_clang_14.cmake")}`,
        "-DPANDA_ETS_INTEROP_JS=ON",
        "-DPANDA_WITH_JAVA=false",
        "-DPANDA_WITH_ECMASCRIPT=false",
        "-DPANDA_WITH_ACCORD=false",
        "-DPANDA_WITH_CANGJIE=false",
        "-DPANDA_WITH_ETS=true"
    ],
    {stdio: "inherit"}
)

child_process.spawnSync("ninja", [
        "-C",
        buildDir,
        "panda_bins"],
    {stdio: "inherit"}
)

makeDir(path.join(pandaSdkDir, "ets"))
makeSymlink(path.join(staticCoreDir, "plugins/ets/stdlib"), path.join(pandaSdkDir, "ets/stdlib"))
makeSymlink(path.join(buildDir, "plugins/ets/etsstdlib.abc"), path.join(pandaSdkDir, "ets/etsstdlib.abc"))
makeDir(path.join(pandaSdkDir, "linux_host_tools"))
makeSymlink(path.join(buildDir, "bin"), path.join(pandaSdkDir, "linux_host_tools/bin"))
makeSymlink(path.join(buildDir, "lib"), path.join(pandaSdkDir, "linux_host_tools/lib"))

console.log("Build completed successfully")

function makeDir(path) {
    if (!fs.existsSync(path)) {
        fs.mkdirSync(path, {recursive: true})
    }
}

function makeSymlink(target, dest) {
    if (fs.existsSync(dest)) {
        if (fs.lstatSync(dest).isDirectory()) {
            fs.rmdirSync(dest, { recursive: true, force: true })
        } else {
            fs.unlinkSync(dest)
        }
    }
    if (fs.lstatSync(target).isDirectory()) {
        fs.cpSync(target, dest, { recursive: true })
    } else {
        fs.symlinkSync(target, dest)
    }
}

function gitClone(repo, dir) {
    child_process.spawnSync("git", ["clone", repo, dir], {stdio: "inherit"})
}

function gitCheckout(repo, rev) {
    child_process.spawnSync("git", ["checkout", rev], {stdio: "inherit", cwd: repo})
}

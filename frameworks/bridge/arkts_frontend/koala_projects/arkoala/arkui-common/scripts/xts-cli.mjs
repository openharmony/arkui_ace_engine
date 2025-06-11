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
import os from "os"
import { zip } from "zip-a-folder"
import { Command } from "commander"
import { copyDirSync, createLazyPool, execCmd, lazy, parseJsonSync } from "../../ohos-sdk/scripts/utils.mjs"
import { fileURLToPath } from "url"
import { generic_package_upload_gitlab } from "../../../../sdk/scripts/gitlab/gitlab.mjs"
import {TEST_PROJECTS_DICT, TEST_SUITES} from "../../../../sdk/koala-cli/arkui-mp-xts/xts-test-projects.mjs"

const LZ_POOL = createLazyPool()

const SCRIPT_DIR = path.dirname(fileURLToPath(import.meta.url))
const KOALA_ROOT = path.join(SCRIPT_DIR, "../../../..")
const KOALA_SDK_ROOT = path.join(KOALA_ROOT, "sdk/koala-cli")
const XTS_PASS_LOG_ROOT = path.join(KOALA_ROOT, "koala-arkui/test/xts-pass-log")
const LZ_XTS_PASS_LOG_PATH = LZ_POOL.lazy(testProject => {
    const logName = testProject !== "" ? testProject : LZ_OPTIONS()["testSuite"]
    return path.join(XTS_PASS_LOG_ROOT, LZ_OPTIONS()["testSuite"], `${logName}.log`)
})

const LZ_OPTIONS = lazy(options => options)
const LZ_TEST_SUITE_REL_PATH = LZ_POOL.lazy(() =>`arkui/${LZ_OPTIONS()["testSuite"] || "ace_ets_layout_test"}`)
const LZ_TEST_PROJECT_REL_PATH = LZ_POOL.lazy(testProject => path.join(LZ_TEST_SUITE_REL_PATH(), testProject))
const LZ_TESTS_ROOT = LZ_POOL.lazy(() => path.join(LZ_OPTIONS()["xts"], LZ_TEST_SUITE_REL_PATH()))
const LZ_TEST_PROJECT_ENTRY = LZ_POOL.lazy(testProject => path.join(LZ_TESTS_ROOT(), testProject, "entry"))

const command = new Command("xts")

command.command("update-pass-log")
    .description(`Migrates 'xts' tests project, runs the tests and updates '${XTS_PASS_LOG_ROOT}' based on the results`)
    .option("-s, --test-suite <name>", "test suite name", "all")
    .option("-t, --test-project <name>", "test project name", "all")
    .option("--retry", "skip the migration step (assuming it's been done previously)")
    .option("-r, --xts <root>", "path to the 'xts_acts' repository root", process.cwd())
    .action(async (options) => {
        LZ_OPTIONS(options)
        await update()
    })

command.command("check-pass-log")
    .description("Checks the provided pass log for tests started to pass/fail")
    .requiredOption("-s, --test-suite <name>", "test suite name")
    .requiredOption("-t, --test-project <name>", "test project name")
    .option("-p, --passed <xts.pass.list>", "list tests started to pass")
    .option("-f, --failed <xts.pass.list>", "list tests started to fail")
    .option("-r, --xts <root>", "path to the 'xts_acts' repository root", process.cwd())
    .action(async (options) => {
        LZ_OPTIONS(options)
        await check()
    })

command.command("check-test-project-supported")
    .description("Checks if the 'xts' test project is currently supported")
    .requiredOption("-s, --test-suite <name>", "test suite name")
    .requiredOption("-t, --test-project <name>", "test project name")
    .option("-r, --xts <root>", "path to the 'xts_acts' repository root", process.cwd())
    .action(async (options) => {
        LZ_OPTIONS(options)
        await supported()
    })

command.command("upload-archive")
    .description("Uploads 'xts_acts' repository archive to gitlab")
    .option("-r, --xts <root>", "path to the 'xts_acts' repository root", process.cwd())
    .option("-v, --version <version>", "the archive version to assign", "1.0.0")
    .action(async (options) => {
        LZ_OPTIONS(options)
        await upload()
    })

command.command("list-suite-test-projects")
    .description("Lists project names of any supported 'xts_acts' suite")
    .option("-r, --xts <root>", "path to the 'xts_acts' repository root", process.cwd())
    .option("-s, --suite <suite>", "suite name", "ace_ets_layout_test")
    .option("-d, --delimiter <delimiter>", "delimiter used to combine the values", ",")
    .action(async (options) => {
        LZ_OPTIONS(options)
        await list_projects()
    })

command.command("list-test-suites")
    .description("Lists 'xts_acts' test suite names")
    .option("-d, --delimiter <delimiter>", "delimiter used to combine the values", ",")
    .action(async (options) => {
        LZ_OPTIONS(options)
        await list_suites()
    })

command.parse()

async function execCmdEx(msg, cmd, args, cwd = process.cwd(), silently = false) {
    if (msg) {
        console.log("\n> " + msg)
        console.log(`> command: ${cmd} ${args.join(" ")}`)
        console.log(`> cwd: ${cwd}\n`)
    }
    return await execCmd(cmd, args, {
        workdir: cwd,
        instantLogging: !silently,
        ignoreError: silently
    })
}

function currentPlatform() {
    let oses = {
        win32: "windows",
        darwin: "macos",
    }
    return oses[process.platform] || process.platform
}

async function update() {
    const testSuite = LZ_OPTIONS()["testSuite"]
    const testProject = LZ_OPTIONS()["testProject"]
    if (testSuite === "all")
        for await (const testSuite of TEST_SUITES) {
            LZ_OPTIONS()["testSuite"] = testSuite
            for await (const testProject of TEST_PROJECTS_DICT[testSuite]) {
                await updateTestProject(testProject)
                LZ_POOL.release()
            }
        }
    else if (testProject === "all")
        for await (const testProject of TEST_PROJECTS_DICT[testSuite]) {
            await updateTestProject(testProject)
            LZ_POOL.release()
        }
    else
        await updateTestProject(testProject)
}

async function updateTestProject(testProject) {
    const testProjectEntry = LZ_TEST_PROJECT_ENTRY(testProject)

    if (!isXtsRepo()) {
        errorExit(`invalid 'xts_acts' repository, folder not found: '${testProjectEntry}'`)
    }
    const testLogPath = path.join(testProjectEntry, "test.log")

    const testProjectOpt = testProject && testProject !== "" ? `--test-project ${testProject}` : ""

    if (!LZ_OPTIONS()["retry"]) {
        await execCmdEx(
            "Migrating...",
            "node",
            [
                KOALA_SDK_ROOT,
                "xts",
                `--suite-root ${LZ_OPTIONS()["testSuite"]}`,
                testProjectOpt,
                "--verbose",
                "--platforms", currentPlatform(),
                "--sdk-repo", KOALA_ROOT,
                "--force"
            ])
    }
    else {
        if (!isXtsRepo(true)) {
            errorExit("need to migrate 'xts_acts' repository")
        }
    }
    if (!supportedImpl(testProject)) {
        return
    }
    await execCmdEx(
        "Running tests...",
        "npm",
        [
            "run",
            "test:all:compact:pass-log:log-file"
        ],
        testProjectEntry,
        true)

    const logPath = LZ_XTS_PASS_LOG_PATH(testProject)
    console.log(`\nUpdating '${logPath}'...`)
    fs.mkdirSync(path.dirname(logPath), { recursive: true })
    fs.cpSync(testLogPath, logPath)
}

async function check() {
    const testProject = LZ_OPTIONS()["testProject"]
    const newXtsPassList = LZ_OPTIONS()["passed"] ?? LZ_OPTIONS()["failed"] ?? undefined
    if (!newXtsPassList) {
        console.error("> Error: either '--passed' or '--failed' option is missed")
        return
    }
    if (!fs.existsSync(newXtsPassList)) {
        console.error(`> Error: file not found: '${command.path}'`)
        return
    }
    const cmd = "diff"
    const args = [
        "-u",
        LZ_XTS_PASS_LOG_PATH(testProject),
        newXtsPassList
    ]
    const out = await execCmdEx(undefined, cmd, args, process.cwd(), true)
    const prefix = LZ_OPTIONS()["failed"] ? "\\-" : "\\+"

    out.split(/\r?\n/).forEach(line => {
        if (new RegExp(`^${prefix}[a-zA-Z]`).test(line)) {
            console.log(line.substring(1))
        }
    })
}

function supported(doExit = true) {
    process.exit(supportedImpl() ? 0 : -1)
}

function supportedImpl(testProject = LZ_OPTIONS()["testProject"]) {
    if (testProject === "all") {
        return true
    }
    const tsConfig = path.join(LZ_TEST_PROJECT_ENTRY(testProject), "src/main/ets/tsconfig.json")
    const testProjectRelPath = LZ_TEST_PROJECT_REL_PATH(testProject)
    if (!fs.existsSync(tsConfig)) {
        console.error(`error: '${testProjectRelPath}' should be migrated first!`)
        return false
    }
    const data = parseJsonSync(tsConfig)
    if (data["include"].length > 0) {
        console.log(`Info: '${testProjectRelPath}' is supported`)
        return true
    } else {
        console.log(`Warn: '${testProjectRelPath}' is not currently supported`)
        return false
    }
}

async function upload() {
    LZ_TEST_PROJECT_ENTRY(TEST_PROJECTS_DICT[TEST_SUITES[0]][0])
    const root = LZ_OPTIONS()["xts"]

    if (!isXtsRepo() || isXtsRepo(true)) {
        errorExit("need original (not yet migrated) 'xts_acts' repository")
    }
    const xtsTmp = path.join(os.tmpdir(), `xts.${process.pid}`)
    const xtsActs = path.join(xtsTmp, `xts_acts.${LZ_OPTIONS().version}`)
    const xtsActsZip = xtsActs + ".zip"

    console.log(`> Copying to... '${xtsActs}'`)
    TEST_SUITES.forEach(suite => {
        const src = path.join(root, "arkui", suite)
        const dst = path.join(xtsActs, "arkui", suite)
        copyDirSync(src, dst)
    })

    console.log(`> Archiving... '${xtsActsZip}'`)
    await zip(xtsActs, xtsActsZip)

    console.log("> Uploading 'xts_acts'...")
    await generic_package_upload_gitlab("xts_acts", LZ_OPTIONS().version, xtsActsZip)

    console.log(`> Deleting... '${xtsTmp}'`)
    fs.rmSync(xtsTmp, { recursive: true, force: true })
}

function list_suites() {
    console.log(TEST_SUITES.join(LZ_OPTIONS()["delimiter"]))
}

function list_projects() {
    console.log(TEST_PROJECTS_DICT[LZ_OPTIONS()["suite"]].join(LZ_OPTIONS()["delimiter"]))
}

function isXtsRepo(migrated = false) {
    if (!fs.existsSync(LZ_TEST_PROJECT_ENTRY())) {
        return false
    }
    return migrated ? fs.existsSync(path.join(LZ_TEST_PROJECT_ENTRY(), "main.test.ts")) : true
}

function errorExit(msg) {
    console.error("error: " + msg)
    process.exit(1)
}

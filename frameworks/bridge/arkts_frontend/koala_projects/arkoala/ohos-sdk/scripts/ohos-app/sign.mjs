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
import { EOL } from "os"
import { ensureExists, ohProjectConf } from "../ohconf.mjs"
import { OH_SDK_COMPONENT, ohSdkInfo } from "../oh-sdk-utils.mjs"
import { execCmd, lazy, parseJsonSync } from "../utils.mjs"
import { fileURLToPath } from "url"

const LZ_OHCONF = lazy(ohConfPath => ohProjectConf(ohConfPath))

const LZ_TOOLS_INFO = lazy(() => ohSdkInfo(LZ_OHCONF().sdkPath(), OH_SDK_COMPONENT.toolchains))
const LZ_TOOLS_LIB_PATH = lazy(() => ensureExists(path.join(LZ_TOOLS_INFO().path, "lib")))

const LZ_HAP_SIGN_TOOL = lazy(() => path.join(LZ_TOOLS_LIB_PATH(), "hap-sign-tool.jar"))

const LZ_KEYSTORE = lazy(() => path.join(LZ_TOOLS_LIB_PATH(), "OpenHarmony.p12"))
const LZ_SDK_PROFILE_CERT = lazy(() => path.join(LZ_TOOLS_LIB_PATH(), "OpenHarmonyProfileRelease.pem"))
const LZ_SDK_PROFILE_TEMPLATE = lazy(() => path.join(LZ_TOOLS_LIB_PATH(), "UnsgnedReleasedProfileTemplate.json"))

const LZ_OUTPUT = lazy(() => ensureExists(path.join(LZ_OHCONF().root, "generated/signature"), true))

const LZ_APP_BUNDLE_NAME = lazy(() => LZ_OHCONF().bundleName())
const LZ_APP_PROFILE_TEMPLATE = lazy(() => path.join(LZ_OUTPUT(), `${LZ_APP_BUNDLE_NAME()}.profile.json`))
const LZ_APP_SIGNED_PROFILE = lazy(() => path.join(LZ_OUTPUT(), `${LZ_APP_BUNDLE_NAME()}.p7b`))
// const LZ_APP_CERT = lazy(() => path.join(LZ_OUTPUT(), "KoalaApplicationRelease.pem"))
// from https://gitee.com/openharmony/developtools_hapsigner.git
const LZ_APP_CERT = lazy(() => path.join(CACERT_ROOT, "OpenHarmonyApplication.pem"))

const SIGN_ALG = "SHA256withECDSA"
const MODE = "localSign"
const PWD = "123456"

const SCRIPTS_DIR = path.dirname(fileURLToPath(import.meta.url))
const CACERT_ROOT = path.join(SCRIPTS_DIR, "../../cacert")
const SUB_CA = path.join(CACERT_ROOT, "subCA.cer")
const ROOT_CA = path.join(CACERT_ROOT, "rootCA.cer")

async function generateAppCert() {
    await execCmd("java", [
        "-jar",
        `"${LZ_HAP_SIGN_TOOL()}"`, '"generate-app-cert"',
        "-keyAlias", '"OpenHarmony Application Release"',
        "-signAlg", SIGN_ALG,
        "-issuer", '"C=CN, O=OpenHarmony, OU=OpenHarmony Team, CN=OpenHarmony Application CA"',
        "-issuerKeyAlias", '"OpenHarmony Application CA"',
        "-subject", '"C=CN, O=OpenHarmony, OU=OpenHarmony Team, CN=OpenHarmony Application Release"',
        "-keystoreFile", `"${LZ_KEYSTORE()}"`,
        "-subCaCertFile", `"${SUB_CA}"`,
        "-rootCaCertFile", `"${ROOT_CA}"`,
        "-outForm", "certChain",
        "-outFile", `"${LZ_APP_CERT()}"`,
        "-keyPwd", PWD,
        "-keystorePwd", PWD,
        "-issuerKeyPwd", PWD
    ], { instantLogging: true })
}

function copyProfileTemplate() {
    const data = parseJsonSync(LZ_SDK_PROFILE_TEMPLATE())
    data["bundle-info"]["bundle-name"] = LZ_APP_BUNDLE_NAME()

    const content = JSON.stringify(data, null, 4) + EOL
    fs.writeFileSync(LZ_APP_PROFILE_TEMPLATE(), content, { encoding: "utf-8" })
}

async function signProfile() {
    await execCmd("java", [
        "-jar",
        `"${LZ_HAP_SIGN_TOOL()}"`, '"sign-profile"',
        "-keyAlias", '"OpenHarmony Application Profile Release"',
        "-signAlg", SIGN_ALG,
        "-mode", MODE,
        "-profileCertFile", `"${LZ_SDK_PROFILE_CERT()}"`,
        "-inFile", `"${LZ_APP_PROFILE_TEMPLATE()}"`,
        "-keystoreFile", `"${LZ_KEYSTORE()}"`,
        "-outFile", `"${LZ_APP_SIGNED_PROFILE()}"`,
        "-keyPwd", PWD,
        "-keystorePwd", PWD
    ], { instantLogging: true })
}

async function signHap(signedHap, unsignedHap) {
    await execCmd("java", [
        "-jar",
        `"${LZ_HAP_SIGN_TOOL()}"`, "sign-app",
        "-keyAlias", '"OpenHarmony Application Release"',
        "-signAlg", SIGN_ALG,
        "-mode", MODE,
        "-appCertFile", `"${LZ_APP_CERT()}"`,
        "-profileFile", `"${LZ_APP_SIGNED_PROFILE()}"`,
        "-keystoreFile", `"${LZ_KEYSTORE()}"`,
        "-inFile", `"${unsignedHap}"`,
        "-outFile", `"${signedHap}"`,
        "-keyPwd", PWD,
        "-keystorePwd", PWD
    ], { instantLogging: true })
}

export async function sign(options) {
    LZ_OHCONF(options.ohConf)

    if (fs.existsSync(LZ_APP_CERT()) &&
        fs.existsSync(LZ_APP_SIGNED_PROFILE()) &&
        path.parse(LZ_APP_SIGNED_PROFILE()).name === LZ_APP_BUNDLE_NAME())
    {
        console.log("Previously generated certificates will be used to sign: " +
            `${LZ_APP_CERT()}, ${path.basename(LZ_APP_SIGNED_PROFILE())}\n`)
    } else {
        // Use stock OpenHarmonyApplication.pem
        // await generateAppCert()
        await copyProfileTemplate()
        await signProfile()
    }
    const hap = LZ_OHCONF().hapPath(options.mod)
    const unsignedHap = hap.replace(/signed/g, "unsigned")
    await signHap(hap, unsignedHap)
}

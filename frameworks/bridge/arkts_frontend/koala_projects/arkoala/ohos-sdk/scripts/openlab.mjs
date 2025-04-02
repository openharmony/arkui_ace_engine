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
import process from "process"
import { http_archive, http_file } from "./http-archive.mjs"
import { execCmd } from "./utils.mjs"

const KOALA_REPO = process.env.KOALA_REPO
const NEXUS_NPM_PASS = process.env.NEXUS_NPM_PASS
const OPENLAB_USERNAME = process.env.OPENLAB_USERNAME
const OPENLAB_PASSWORD = process.env.OPENLAB_PASSWORD

function getAuth() {
    if (NEXUS_NPM_PASS)
        return `Basic ${NEXUS_NPM_PASS}`

    if (OPENLAB_USERNAME === undefined) throw new Error(`Environment variable OPENLAB_USERNAME is not specified`)
    if (OPENLAB_PASSWORD === undefined) throw new Error(`Environment variable OPENLAB_PASSWORD is not specified`)
    const authStr = `${OPENLAB_USERNAME}:${OPENLAB_PASSWORD}`
    return `Basic ${btoa(authStr)}`
}

function getHeaders() {
    return {
        'Authorization': getAuth(),
    }
}

function get_koala_repo() {
    if (KOALA_REPO)
        return KOALA_REPO;
    return 'https://nexus.bz-openlab.ru:10443/repository/koala-raw/'
}

function get_generic_package_url(name, version, file) {
    const host = get_koala_repo();
    return host + name + '/' + version + '/' + file
}

export async function generic_package_file_openlab(packageName, packageVersion, fileName, outDir, outFile) {
    await http_file(
        get_generic_package_url(packageName, packageVersion, fileName),
        outDir,
        outFile,
        getHeaders()
    )
}

export async function generic_package_archive_openlab(packageName, packageVersion, fileName, outDir, stripPrefix=null, copy=false) {
    await http_archive(
        get_generic_package_url(packageName, packageVersion, fileName),
        outDir,
        stripPrefix,
        getHeaders(),
        copy
    )
}

export async function download_archive_from_url_openlab(url, outDir, stripPrefix=null) {
    await http_archive(
        url,
        outDir,
        stripPrefix,
        getHeaders()
    )
}

export async function generic_package_upload_openlab(packageName, packageVersion, filePath) {
    const fileName = path.basename(filePath)
    return execCmd("curl", [
        "--user", `\"${OPENLAB_USERNAME}:${OPENLAB_PASSWORD}\"`,
        "--upload-file", filePath,
        `https://nexus.bz-openlab.ru:10443/repository/koala-raw/${packageName}/${packageVersion}/${fileName}`
    ])
}

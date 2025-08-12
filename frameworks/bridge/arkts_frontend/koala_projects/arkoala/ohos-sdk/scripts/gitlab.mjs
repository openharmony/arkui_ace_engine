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

const GITLAB_USERNAME = process.env.GITLAB_USERNAME
const GITLAB_TOKEN = process.env.GITLAB_TOKEN

function getAuth() {
    if (GITLAB_USERNAME === undefined) throw new Error(`Environment variable GITLAB_USERNAME is not specified`)
    if (GITLAB_TOKEN === undefined) throw new Error(`Environment variable GITLAB_TOKEN is not specified`)
    return { user: GITLAB_USERNAME, token: GITLAB_TOKEN } 
}

function getHeaders() {
    const {user, token} = getAuth()
    const authStr = `${user}:${token}`
    const auth = `Basic ${btoa(authStr)}`
    return {
        'Authorization': auth
    }
}


function get_generic_package_url(name, version, file) {
    const api_host = 'https://rnd-gitlab-msc.huawei.com/api/v4/'
    const api_path = 'projects/3921/packages/generic/'
    return api_host + api_path + name + '/' + version + '/' + file
}

export async function generic_package_file_gitlab(packageName, packageVersion, fileName, outDir, outFile) {
    await http_file(
        get_generic_package_url(packageName, packageVersion, fileName),
        outDir,
        outFile,
        getHeaders()
    )
}

export async function generic_package_archive_gitlab(packageName, packageVersion, fileName, outDir, stripPrefix=null, copy=false) {
    await http_archive(
        get_generic_package_url(packageName, packageVersion, fileName),
        outDir,
        stripPrefix,
        getHeaders(),
        copy
    )
}

export async function download_archive_from_url_gitlab(url, outDir, stripPrefix=null) {
    await http_archive(
        url,
        outDir,
        stripPrefix,
        getHeaders()
    )
}

export async function generic_package_upload_gitlab(packageName, packageVersion, filePath) {
    const fileName = path.basename(filePath)
    return execCmd("curl", [
        "--insecure",
        "--header", `\"DEPLOY_TOKEN: ${DEPLOY_TOKEN}\"`,
        "--user", `\"koala-deploy:${KOALA_DEPLOY}\"`,
        "--upload-file", filePath,
        `https://rnd-gitlab-msc.huawei.com/api/v4/projects/3921/packages/generic/${packageName}/${packageVersion}/${fileName}`
    ])
}


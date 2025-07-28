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

// TODO: modify properly!
const path = require("path")
const baseMakeConfig = require('./webpack.config.base')
const OHOSCompilationHookPlugin = require('./webpack.ohos.import.plugin')

/**
 * export * as arkui from "@koalaui/arkoala-arkui";
 * export * as framework from "@koalaui/arkoala";
 * export * as runtime from "@koalaui/runtime";
 * which was defined in framework
 */
const renameMap = new Map([
    ["@koalaui/arkoala-arkui", "arkui"],
    ["@koalaui/arkoala", "framework"],
    ["@koalaui/runtime", "runtime"],
    ["@koalaui/arkoala-arkui/ohos.router", "router"]
])

// If the framework is separate or compiled into an app.
const splitMode = false

/**
 * @param {import("webpack").WebpackOptionsNormalized}  config
 * @returns {import("webpack").WebpackOptionsNormalized}
 */
const makeConfig = (config) => ({
    ...config,
    output: {
        filename: "index-app.js",
        publicPath: "/",
        path: path.resolve(__dirname, `lib/js`),
        chunkFormat: 'module',
        library: {
            type: "module",
        }
    },
    experiments: {
        outputModule: true,
    },
    externalsType: "module",
    externals: [
        function ({ context, request }, callback) {
            if (splitMode && renameMap.has(request)) {
                return callback(null, `__arkoala__.${renameMap.get(request)}`, 'var')
            }
            if (/@ohos(\.|\/).*/.test(request)) {
                return callback(null, request, "module")
            }
            callback()
        },
    ],
    plugins: [
        ...config.plugins,
        new OHOSCompilationHookPlugin({ assetName: 'index-app.js' })
    ],
})

module.exports = env => {
    const baseConfig = baseMakeConfig(env)
    return makeConfig(baseConfig)
}

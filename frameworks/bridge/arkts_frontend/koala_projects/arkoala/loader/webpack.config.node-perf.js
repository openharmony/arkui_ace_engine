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

const path = require("path")
const CopyPlugin = require("copy-webpack-plugin")
const DefinePlugin = require("webpack").DefinePlugin
const ProvidePlugin = require("webpack").ProvidePlugin
const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch }) => ({
    target: "node",
    entry: "./src/index.perf.ts",
    output: {
        filename: "js/arkoala-perf-node.js",
        publicPath: "/",
        path: path.resolve(__dirname, `lib`),
        // This is not a module, so we can have it as a single js file 
        // for node vs ark_js_vm comparison.
    },
    resolve: {
        extensions: [".ts", ".node", "..."],
    },

    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: "ts-loader",
                options: {
                    "projectReferences": true,
                    compiler: "@koalaui/ets-tsc"
                }
            },
            // Bundle already existing source maps for dependencies
            { test: /\.js$/, loader: "source-map-loader", enforce: "pre" },
        ]
    },

    plugins: [
        new DefinePlugin({
        }),
    ],

    mode: minimize ? "production" : "development",
    devtool: minimize ? false : "inline-source-map"
})

module.exports = env => {
    const oses = {
        'win32': 'windows',
        'darwin': 'macos',
    }

    const os = env.os || oses[process.platform] || process.platform
    const arch = (env.arch || process.arch)

    return makeConfig({os, arch})
}

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
const fs = require("fs")
const CopyPlugin = require("copy-webpack-plugin")
const TerserPlugin = require("terser-webpack-plugin")
const DefinePlugin = require("webpack").DefinePlugin
const ProvidePlugin = require("webpack").ProvidePlugin


const minimize = !process.env.WEBPACK_NO_MINIMIZE
const is_user_bridge = true

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch }) => ({
    target: "node",
    resolve: {
        extensions: [".ts", "..."],
        conditionNames: ["ark", "node", "main"],
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
    plugins:[
        new DefinePlugin({
            'LOAD_NATIVE': is_user_bridge ? `globalThis.requireNapi("ArkoalaNative", true)` :  `globalThis.requireNapi("arkoalanative_${os}_${arch}")`,
            'NATIVE_LIBRARY_NAME': is_user_bridge ? `"ArkoalaNative"` : `"arkoalanative_${os}_${arch}"`,
        }),
    ],
    mode: minimize ? "production" : "development",
    devtool: minimize ? false : "inline-source-map",

    optimization: {
        // ETS plugin fails on minified app.js, so limit line length
        minimizer: [
            new TerserPlugin({
                parallel: true,
                terserOptions: {
                    format: {
                        max_line_len: 4096,
                    }
                },
            }),
        ],
    },
    devtool: false
})

module.exports = env => {
    const oses = {
        'win32': 'windows',
        'darwin': 'macos',
    }

    const os = env.os || oses[process.platform] || process.platform
    const arch = os == "android" ? "generic" : (env.arch || process.arch)

    return makeConfig({os, arch})
}

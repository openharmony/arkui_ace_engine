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
const ReplaceSource = require("webpack").sources.ReplaceSource
const CopyPlugin = require("copy-webpack-plugin")
const TerserPlugin = require("terser-webpack-plugin")
const DefinePlugin = require("webpack").DefinePlugin
const ProvidePlugin = require("webpack").ProvidePlugin

const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch }) => ({
    target: "node",
    experiments: {
        outputModule: true,
    },
    output: {
        filename: "index-ark.js",
        publicPath: "/",
        path: path.resolve(__dirname, `lib/js`),
        chunkFormat: 'module',
        library: {
            type: "module",
        },
    },
    resolve: {
        extensions: [".ts", "..."],
        conditionNames: ["ark", "node", "main"],
    },
    // Do not bundle @koalaui/skoala-sys and its subpathes
    // TODO Map @koalaui/skoala-sys to target platform if needed
    externals: /@ohos\..*/,
    externalsType: "module",
    module: {
        rules: [
            { test: /\.ts$/, loader: "ts-loader" },
            // Bundle already existing source maps for dependencies
            { test: /\.js$/, loader: "source-map-loader", enforce: "pre" },
        ]
    },

    plugins: [
        new DefinePlugin({
            'LOAD_NATIVE': `globalThis.requireNapi("ArkoalaNative", true)`,
            'NATIVE_LIBRARY_NAME': `"ArkoalaNative"`,
        }),
        {
            apply(compiler) {
                compiler.hooks.compilation.tap('OHOSCompilationHook', (compilation) => {
                    // before minification
                    // Erase 'default' reference in accessing @ohos modules internals
                    compilation.hooks.processAssets.tap('OHOSPreprocessHook', (assets) => {
                        let source = assets["index-ark.js"]
                        let patched = new ReplaceSource(source)
                        let text = source.source()
                        // '_ohos_*.default.*' ==> '_ohos_*.'
                        for (const match of text.matchAll(/(_ohos_[\w_$]+?)\.default\./g)) {
                            patched.replace(match.index, match.index + match[0].length - 1, `${match[1]}\.`)
                        }
                        compilation.updateAsset("index-ark.js", patched)
                    })
                    // after minification
                    // Replace import * as <name> with import <name> for hvigor
                    compilation.hooks.afterProcessAssets.tap('OHOSImportReplaceHook', (assets) => {
                        let source = assets["index-ark.js"]
                        let patched = new ReplaceSource(source)
                        let text = source.source()
                        // 'import * as match_1 from"@ohos.blah.blah"' ==> '\nimport match_1 from "@ohos.blah.blah"'
                        for (const match of text.matchAll(/import\s*\*\s*as\s*([\w_$]+)\s*from(?=\s*"@ohos\.)/g)) {
                            patched.replace(match.index, match.index + match[0].length - 1, `\nimport ${match[1]} from `)
                        }
                        assets["index-ark.js"] = patched
                    })
                })
            }
        }
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

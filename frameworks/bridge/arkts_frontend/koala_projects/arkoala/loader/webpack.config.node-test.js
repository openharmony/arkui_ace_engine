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
const TsconfigPathsPlugin = require('tsconfig-paths-webpack-plugin')

const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch, tsconfig, unmemoized }) => ({
    target: "node",
    entry: `./${unmemoized}/src/index.ts`,
    output: {
        // For now override the unmemoized version as this is what
        // the loader.js expects
        // filename: `${unmemoized}index-node.js`,
        filename: `index-node.js`,
        publicPath: "/",
        path: path.resolve(__dirname, `lib/${unmemoized}/js`),
        libraryTarget: "commonjs2",
    },
    resolve: {
        extensions: [".ts", ".node", "..."],
        // Only use this facility for tsconfig-run-unmemoized.json
        plugins: (tsconfig == "tsconfig-run-unmemoized.json") ? [new TsconfigPathsPlugin({
            "configFile": tsconfig,
        })] : []
    },

    module: {
        rules: [
            {
                test: /\.tsx?$/,
                loader: "ts-loader",
                options: {
                    "projectReferences": true,
                    configFile: tsconfig,
                    compiler: "@koalaui/ets-tsc"
                }
            },
            { test: /\.node$/, loader: "node-loader",
                options: {
                    name: "[name].[ext]",
                }
            },
        ]
    },

    plugins: [
        new CopyPlugin({
            patterns: copyPluginPatterns(os, arch)
        }),
        new DefinePlugin({
            'LOAD_NATIVE': `require("./ArkoalaNative_${os}_${arch}.node")`,
            'NATIVE_LIBRARY_NAME': `"./ArkoalaNative_${os}_${arch}.node"`,
            "process.env.KOALAUI_SELF_PROFILE": "false",
        }),
    ],

    mode: minimize ? "production" : "development",
    devtool: minimize ? false : "inline-source-map"
})

function copyPluginPatterns(os, arch) {
    const patterns = []
    patterns.push({
        from: path.resolve(`./src/loader.js`),
        to: "."
    })
    patterns.push({
        from: path.resolve(`../framework/build/ArkoalaNative_${os}_${arch}.node`),
        to: "."
    })
    return patterns
}

module.exports = env => {
    const oses = {
        'win32': 'windows',
        'darwin': 'macos',
    }

    const os = env.os || oses[process.platform] || process.platform
    const arch = (env.arch || process.arch)

    const tsconfig = env.tsconfig || ""
    const unmemoized = env.unmemoized ? `${env.unmemoized}/` : ""

    console.log("Using tsconfig: ", tsconfig)

    return makeConfig({os, arch, tsconfig, unmemoized})
}

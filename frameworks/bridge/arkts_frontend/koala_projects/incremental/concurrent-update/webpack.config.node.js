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
const CircularDependencyPlugin = require("circular-dependency-plugin")
const DefinePlugin = require("webpack").DefinePlugin
const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch, tsconfig, unmemoized }) => ({
    target: "node",
    entry: `./${unmemoized}/src/index.ts`,
    output: {
        filename: `${unmemoized}js/app.js`,
        publicPath: "/",
        path: path.resolve(__dirname, "lib"),
        libraryTarget: "commonjs2",
    },
    resolve: {
        extensions: ['.ts', '...'],
        conditionNames: os === 'ios' ? ['ios', 'node', 'main'] : ['node', 'main']
    },
    // Do not bundle @koalaui/skoala-sys and its subpathes
    // TODO Map @koalaui/skoala-sys to target platform if needed
    externals: os === "android" ? /skoala-sys.*/ : /.*skoala-runtime.*/,
    externalsType: "node-commonjs",
    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: "ts-loader",
                options: {
                    "projectReferences": true,
                    configFile: tsconfig
                }
            },
            // Bundle already existing source maps for dependencies
            { test: /\.js$/, loader: "source-map-loader", enforce: "pre" },
            // Copy skoala-runtime node binary file (disabled since @koalaui/@koalaui/skoala-sys is not bundled)
            // { test: /\.node$/, loader: "node-loader" },
        ]
    },

    plugins: [
        new DefinePlugin({
            // see skoala-ts/components/renderer/node/NodeHostInterface.ts
            "process.env.KOALAUI_RESOURCE_ROOT": "require(\"path\").join(__dirname, '..')",
            // TODO pack for android
            "process.env.KOALAUI_RUNTIME_PACKAGE": os === "android" ? false : JSON.stringify((`@koalaui/skoala-runtime-node-${os}-${arch}`)),
            // Set to "true" to self profile.
            "process.env.KOALAUI_SELF_PROFILE": "false"
        }),
        new CircularDependencyPlugin({failOnError: true})
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
    const arch = env.arch || process.arch

    const tsconfig = env.tsconfig || ""
    const unmemoized = env.unmemoized ? `${env.unmemoized}/` : ""

    return makeConfig({os, arch, tsconfig, unmemoized})
}

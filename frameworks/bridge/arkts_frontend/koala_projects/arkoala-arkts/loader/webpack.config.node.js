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

const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch, isAni, tsconfig }) => ({
    target: "node",
    entry: `./src/loader.ts`,
    output: {
        filename: `index.js`,
        path: path.resolve(__dirname, `../build`),
        libraryTarget: "commonjs2",
    },
    resolve: {
        extensions: [".ts", ".node", "..."]
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
        ]
    },

    plugins: [
        new CopyPlugin({
            patterns: copyPluginPatterns(os, arch, isAni)
        }),
        new DefinePlugin({
            'LOAD_NATIVE': `require("./ArkoalaLoader.node")`
        })
    ],

    mode: minimize ? "production" : "development",
    devtool: minimize ? false : "inline-source-map"
})

function getExt(os) {
    switch (os) {
        case "linux": return "so"
        case "windows": return "dll"
        case "macos": return "dylib"
        default: return "so"
    }
}

function copyPluginPatterns(os, arch, isAni) {
    const patterns = []
    patterns.push({
        from: path.resolve(`../../arkoala/framework/native/build-node-host-vmloader/ArkoalaLoader.node`),
        to: "."
    })
    patterns.push({
        from: path.resolve(`../../arkoala/framework/native/build-node-host-vmloader/libvmloader.${ getExt(os) }`),
        to: "."
    })
    if (!isAni) {
        patterns.push({
            from: path.resolve(`../../arkoala/framework/native/build-panda-host/libArkoalaNative_${os}_${arch}_ark.${ getExt(os) }`),
            to: `./libArkoalaNative_ark.${ getExt(os) }`
        })
    } else {
        patterns.push({
            from: path.resolve(`../../arkoala/framework/native/build-panda-ani-host/libArkoalaNative_${os}_${arch}_ani.${ getExt(os) }`),
            to: `./libArkoalaNative_ani.${ getExt(os) }`
        })
    }
    patterns.push({
        from: path.resolve(`../../arkoala/framework/native/build-panda-host/libace_compatible_mock.${ getExt(os) }`),
        to: `./libace_compatible_mock.${ getExt(os) }`
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
    const isAni = env.isAni

    const tsconfig = env.tsconfig || ""

    return makeConfig({os, arch, isAni, tsconfig})
}

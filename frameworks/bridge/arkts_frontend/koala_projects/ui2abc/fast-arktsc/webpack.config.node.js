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
var webpack = require("webpack");

const minimize = !process.env.WEBPACK_NO_MINIMIZE

/** @returns {import("webpack").WebpackOptionsNormalized} */
const makeConfig = ({ os, arch, tsconfig }) => ({
    target: "node",
    entry: `./src/main.ts`,
    output: {
        filename: `index.js`,
        path: path.resolve(__dirname, `lib`),
        libraryTarget: "commonjs2",
    },
    resolve: {
        extensions: [".ts", ".node", "..."]
    },
    plugins: [
        new webpack.BannerPlugin({ banner: "#!/usr/bin/env node", raw: true })
    ],
    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: "ts-loader",
            },
        ]
    },

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

    const tsconfig = env.tsconfig || ""

    return makeConfig({os, arch, tsconfig})
}

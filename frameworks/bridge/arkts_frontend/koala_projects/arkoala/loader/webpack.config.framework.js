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
const baseMakeConfig = require('./webpack.config.base')
const OHOSCompilationHookPlugin = require('./webpack.ohos.import.plugin')


/**
 * @param {import("webpack").WebpackOptionsNormalized}  config
 * @returns {import("webpack").WebpackOptionsNormalized}
 */
const makeConfig = (config) => ({
    ...config,
    entry: "./src/index.framework.ts",
    output: {
        filename: "index-framework.js",
        publicPath: "/",
        path: path.resolve(__dirname, `lib/js`),
        library: "__arkoala__"
    },
    externals: /@ohos\..*/,
    plugins: [
        ...config.plugins,
        // may be removed later
        new OHOSCompilationHookPlugin({ assetName: 'index-framework.js' })
    ],
})

module.exports = env => {
    const baseConfig = baseMakeConfig(env)
    return makeConfig(baseConfig)
}
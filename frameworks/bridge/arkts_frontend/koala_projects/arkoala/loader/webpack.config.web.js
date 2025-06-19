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
const DefinePlugin = require("webpack").DefinePlugin
const ProvidePlugin = require("webpack").ProvidePlugin

/** @returns {import("webpack").WebpackOptionsNormalized} */
module.exports = {
    target: "web",
    entry: "./web/index.web.ts",
    output: {
        filename: "js/arkoala-web.js",
        publicPath: "/",
        path: path.resolve(__dirname, `dist`),
        library: "Koala",
    },
    resolve: {
        extensions: ['.ts', '...']
    },
    module: {
        rules: [
            {
                test: /\.ts$/,
                loader: "ts-loader",
                options: {
                    "projectReferences": true,
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

    mode: "development",
    devtool: "inline-source-map",

    devServer: {
        static: [
            {
                directory: path.join(__dirname, "www")
            },
            {
                directory: path.join(__dirname, "resources")
            },
            {
                directory: path.join(__dirname, "src/ets")
            },
        ],
        port: 9000,
        bonjour: false,
    }
}

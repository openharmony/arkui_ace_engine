/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import nodeResolve from "@rollup/plugin-node-resolve";
import typescript from "@rollup/plugin-typescript";
import commonjs from '@rollup/plugin-commonjs'
import terser from "@rollup/plugin-terser"

const ENABLE_SOURCE_MAPS = false;  // Enable for debugging

export default [
    buildPlugin({
        src: "./src/ParserTransformer.ts",
        dst: "./lib/ParserTransformer.js",
    }),
    buildPlugin({
        src: "./src/MemoTransformer.ts",
        dst: "./lib/MemoTransformer.js",
    }),
    buildPlugin({
        src: "./src/entry.ts",
        dst: "./lib/entry.js",
        minimize: false,
    }),
]

/** @return {import("rollup").RollupOptions} */
function buildPlugin({ src, dst, minimize = false }) {
    return {
        input: src,
        output: {
            file: dst,
            format: "commonjs",
            plugins: [
                minimize && terser({
                    sourceMap: ENABLE_SOURCE_MAPS,
                    format: {
                        max_line_len: 800
                    }
                }),
                replaceLibarktsImport()

            ],
            sourcemap: ENABLE_SOURCE_MAPS,
            banner: APACHE_LICENSE_HEADER(),
            sourcemap: ENABLE_SOURCE_MAPS
        },
        external: ["@koalaui/libarkts"],
        plugins: [
            commonjs(),
            typescript({
                outputToFilesystem: false,
                module: "esnext",
                sourceMap: ENABLE_SOURCE_MAPS,
                declarationMap: false,
                declaration: false,
                composite: false,
            }),
            nodeResolve({
                extensions: [".js", ".mjs", ".cjs", ".ts", ".cts", ".mts"]
            })
        ],
    }
}

function APACHE_LICENSE_HEADER() {
    return `
/**
* @license
* Copyright (c) ${new Date().getUTCFullYear()} Huawei Device Co., Ltd.
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

`
}

/** @returns {import("rollup").OutputPlugin} */
function replaceLibarktsImport() {
    const REQUIRE_PATTERN = `require('@koalaui/libarkts');`
    return {
        name: "replace-librkts-import",
        generateBundle(options, bundle) {
            for (const [fileName, asset] of Object.entries(bundle)) {
                if (!asset.code) continue
                if (fileName !== "entry.js") continue
                asset.code = asset.code.replace(REQUIRE_PATTERN, `require(process.env.LIBARKTS_PATH ?? "../../libarkts/lib/libarkts.js")`)
            }
        }
    }
}
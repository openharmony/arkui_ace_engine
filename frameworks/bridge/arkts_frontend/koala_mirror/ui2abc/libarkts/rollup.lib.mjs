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

const ENABLE_SOURCE_MAPS = false // Enable for debugging

/** @type {import("rollup").RollupOptions} */
export default makeConfig()

function makeConfig(input, output) {
    return {
        input: {
            'libarkts': "./src/index.ts",
            'libarkts-compat': "./src/wrapper-compat/index.ts"
        },
        output: {
            dir: "lib",
            format: "commonjs",
            plugins: [
                // terser()
            ],
            manualChunks: {
                'libarkts-common': ["./src/index.ts"],
                // Improve: maybe split scripts into smaller chunks
                // 'libarkts-api': ["./src/arkts-api/index.ts"],
                // 'libarkts-generated': ["./src/generated/index.ts"],
            },
            banner: APACHE_LICENSE_HEADER(),
            sourcemap: ENABLE_SOURCE_MAPS
        },
        plugins: [
            commonjs(),
            typescript({
                outputToFilesystem: false,
                outDir: "lib",
                module: "esnext",
                sourceMap: ENABLE_SOURCE_MAPS,
                declaration: true,
                declarationMap: false,
                declarationDir: "lib/types",
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

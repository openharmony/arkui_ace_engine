/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
import commonjs from "@rollup/plugin-commonjs";
import terser from '@rollup/plugin-terser';
import inject from '@rollup/plugin-inject';
import path from "node:path";
import replace from "@rollup/plugin-replace";


const DEBUG = true;
// const implementedPackages = [
//     'ohos.arkui.testing',
//     'ohos.matrix4',
//     'ohos.router',
//     'system.router'
// ]
//const implementedPackagesEntries = implementedPackages.map((name) => `@koalaui/arkoala-arkui/${name}`)

/** @type {import("rollup").RollupOptions[]} */
export default cliOptions => [{
    input: ["./bundle.mjs" /*, ...implementedPackagesEntries*/],
    output: {
        format: "module",
        chunkFileNames: "[name].js",
        entryFileNames: "[name].js",
        dir: "../app/arkoala",
        banner: chunk => LICENSE,
        plugins: [
            !DEBUG && terser({
                format: {
                    max_line_len: 1024,
                }
            }),
        ],
    },
    external: [
        "libArkoalaNative.so",
    ],
    plugins: [
        nodeResolve({
            exportConditions: ["ark", "node", "main"]
        }),
        // commonjs(),
        replace({
            preventAssignment: true,
            values: {
                __ARKOALA_HAR__: 'true',
                __ARCH__: cliOptions.arch
            }
        }),
        inject({
            LOAD_NATIVE: path.resolve("./load_native.mjs"),
            __LOAD_PAGE__: path.resolve("./load_page.mjs")
        }),
    ]
}]

const LICENSE = `
/**
 * @license
 * 
 * Copyright (c) 2021-${new Date().getFullYear()} Huawei Device Co., Ltd.
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

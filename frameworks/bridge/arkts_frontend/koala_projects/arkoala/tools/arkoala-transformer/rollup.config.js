const typescript = require("@rollup/plugin-typescript")
const nodeResolve = require("@rollup/plugin-node-resolve").default
const commonjs = require("@rollup/plugin-commonjs")
const replace = require("@rollup/plugin-replace")

/** @type { import("rollup").RollupOptions } */
module.exports = {
    input: "index.ts",
    output: {
        file: "arkoala-plugin.js",
        format: "commonjs",
        exports: "default",
    },
    external: ["typescript", "ohos-typescript", "@koalaui/ets-tsc", "@koalaui/ets-tsc"],
    plugins: [
        replace({
            values: {
                'ohos-typescript': 'typescript',
                "'@koalaui/ets-tsc'": '("typescript")' // even not try understand it temporary solution
            },
            delimiters: ['\\(', '\\)'],
            preventAssignment: true,
        }),
        typescript({
            module: "esnext"
        }),
        nodeResolve({
            
        }),
        commonjs(),
    ]
}
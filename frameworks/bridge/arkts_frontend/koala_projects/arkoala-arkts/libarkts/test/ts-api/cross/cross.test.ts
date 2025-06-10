import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    test("imported-function-call", function() {
        const sample_in =
        `
        import { X } from "./variable"
 
        export function main() {
            console.log(X)
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        util.cleanGenerated()
        util.fileToAbc(`./input/variable.sts`, true)
        util.contextToAbc()
        util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })

    test("rewrite-imported-function-call", function() {
        const sample_in =
        `
        import { X } from "./variable"
 
        export function main() {
            console.log(Y)
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        util.cleanGenerated()
        util.fileToAbc(`./input/variable.sts`, true)
        util.contextToAbc()
        util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })
})

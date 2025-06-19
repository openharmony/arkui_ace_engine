import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"
import { factory } from "../../../src/ts-api"

// TODO:
suite.skip(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        import { X } from "./variable"
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        // sourceFile = factory.updateSourceFile(
        //     sourceFile,
        //     [
        //         factory.createImportDeclaration(
        //             undefined,
        //             factory.createImportClause(
        //                 false,
        //                 undefined,
        //                 factory.createNamedImports(
        //                     [
        //                         factory.createImportSpecifier(
        //                             false,
        //                             undefined,
        //                             factory.createIdentifier("X")
        //                         )
        //                     ]
        //                 )
        //             ),
        //             factory.createStringLiteral("./variable"),
        //             undefined
        //         )
        //     ]
        // )

        // util.assertEqualsAfter(
        //     sourceFile,
        //     `
        //     import { X } from "./variable"
        //     `,
        //     ts.ContextState.ES2PANDA_STATE_PARSED
        // )
    })
})

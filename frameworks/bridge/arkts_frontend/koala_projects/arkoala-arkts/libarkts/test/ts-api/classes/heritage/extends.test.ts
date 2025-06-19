import * as util from "../../../test-util"
import * as ts from "../../../../src/ts-api"
import { factory } from "../../../../src/ts-api"

// TODO:
suite.skip(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        abstract class A {};
        abstract class C {};
        interface D {};
        class B extends A implements C, D {};
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        // sourceFile = factory.updateSourceFile(
        //     sourceFile,
        //     [
        //         factory.createClassDeclaration(
        //             [
        //                 factory.createToken(ts.SyntaxKind.AbstractKeyword)
        //             ],
        //             factory.createIdentifier("A"),
        //             undefined,
        //             undefined,
        //             []
        //         ),
        //         factory.createClassDeclaration(
        //             undefined,
        //             factory.createIdentifier("B"),
        //             undefined,
        //             [
        //                 factory.createHeritageClause(
        //                     ts.SyntaxKind.ExtendsKeyword,
        //                     [
        //                         factory.createExpressionWithTypeArguments(
        //                             factory.createIdentifier("A"),
        //                             undefined
        //                         )
        //                     ]
        //                 )
        //             ],
        //             []
        //         )
        //     ]
        // )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            abstract class A {};
            class B extends A {};
            `
        )
    })
})

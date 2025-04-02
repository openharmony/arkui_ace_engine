import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"
import { factory } from "../../../src/ts-api"

// TODO:
suite.skip(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        // sourceFile = factory.updateSourceFile(
        //     sourceFile,
        //     [
        //         factory.createClassDeclaration(
        //           [factory.createToken(ts.SyntaxKind.AbstractKeyword)],
        //           factory.createIdentifier("A"),
        //           undefined,
        //           undefined,
        //           [factory.createConstructorDeclaration(
        //             undefined,
        //             [factory.createParameterDeclaration(
        //               undefined,
        //               undefined,
        //               factory.createIdentifier("x"),
        //               undefined,
        //               factory.createTypeReferenceNode(
        //                 factory.createIdentifier("int"),
        //                 undefined
        //               ),
        //               undefined
        //             )],
        //             factory.createBlock(
        //               [],
        //               false
        //             )
        //           )]
        //         ),
        //         factory.createClassDeclaration(
        //           undefined,
        //           factory.createIdentifier("B"),
        //           undefined,
        //           [factory.createHeritageClause(
        //             ts.SyntaxKind.ExtendsKeyword,
        //             [factory.createExpressionWithTypeArguments(
        //               factory.createIdentifier("A"),
        //               undefined
        //             )]
        //           )],
        //           [factory.createConstructorDeclaration(
        //             undefined,
        //             [factory.createParameterDeclaration(
        //               undefined,
        //               undefined,
        //               factory.createIdentifier("x"),
        //               undefined,
        //               factory.createTypeReferenceNode(
        //                 factory.createIdentifier("int"),
        //                 undefined
        //               ),
        //               undefined
        //             )],
        //             factory.createBlock(
        //               [factory.createExpressionStatement(factory.createCallExpression(
        //                 factory.createSuper(),
        //                 undefined,
        //                 [factory.createIdentifier("x")]
        //               ))],
        //               true
        //             )
        //           )]
        //         )
        //       ]
        // )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            abstract class A {
                constructor(x: int) {}
            };

            class B extends A {
                constructor(x: int) {
                    super(x)
                }
            }
            `
        )
    })
})

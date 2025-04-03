import * as util from "../../../test-util"
import * as ts from "../../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    test("adding-lambda-param-to-signature", function() {
        // _Foo((instance: string) => {
        //     // empty
        // }, "label");

        const sample_in =
        `
        Foo("label")

        function Foo(text: string): void {
            console.log(text)
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const newName = "_Foo"
        const paramName = "instance"

        const firstStatement = sourceFile.statements[0]
        util.assert(ts.isExpressionStatement(firstStatement))
        const node = firstStatement.expression
        util.assert(ts.isCallExpression(node))

        const instanceLambdaBody = ts.factory.createBlock([])
        const lambdaParams = [
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier(paramName),
                undefined,
                ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                undefined
            )
        ]

        const lambda = ts.factory.createArrowFunction(
            undefined,
            undefined,
            lambdaParams,
            undefined,
            undefined,
            instanceLambdaBody
        )

        const result = ts.factory.updateCallExpression(
            node,
            ts.factory.createIdentifier(newName),
            undefined,
            [
                lambda,
                ...node.arguments
            ]
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                ts.factory.createExpressionStatement(result)
            ]
        )
        
        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            _Foo(((instance: string) => {}), "label")
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test("adding-body-to-lambda-param", function() {
        // _Foo((instance: string) => {
        //     instance.bar().qux();
        // }, "label1", "label2");

        const sample_in =
        `
        Foo(instance.bar().qux(), "label1", "label2")
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const newName = "_Foo"
        const paramName = "instance"

        const firstStatement = sourceFile.statements[0]
        util.assert(ts.isExpressionStatement(firstStatement))

        const node = firstStatement.expression
        util.assert(ts.isCallExpression(node))

        const instanceLambdaBody = ts.factory.createBlock([
            ts.factory.createExpressionStatement(
                node.arguments[0]
            )
        ])
        const lambdaParams = [
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier(paramName),
                undefined,
                ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                undefined
            )
        ]

        const lambda = ts.factory.createArrowFunction(
            undefined,
            undefined,
            lambdaParams,
            undefined,
            undefined,
            instanceLambdaBody
        )

        const result = ts.factory.updateCallExpression(
            node,
            ts.factory.createIdentifier(newName),
            undefined,
            [
                lambda,
                ...node.arguments.slice(1)
            ]
        )
        
        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                ts.factory.createExpressionStatement(result)
            ]
        )
        
        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            _Foo(((instance: string) => {
                instance.bar().qux();
            }), "label1", "label2")
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })
})

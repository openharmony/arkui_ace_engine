import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"

// tests for abc generation (now failing on CI)
suite.skip(util.basename(__filename), () => {
    test("updating-expression-statement", function() {
        const sample_in =
        `
        function foo(lambda: (instance: string) => string): void {
            console.log(lambda("ABC"))
        }

        foo((instance: string) => { return instance })
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const expressionStatement = sourceFile.statements[1]
        util.assert(ts.isExpressionStatement(expressionStatement))

        const newStatements = [
            sourceFile.statements[0],
            ts.factory.updateExpressionStatement(
                expressionStatement,
                expressionStatement.expression
            )
        ]

        ts.factory.updateSourceFile(sourceFile, newStatements)

        util.assertEqualsBinaryOutput('ABC', this)
    })

    test("updating-function-declaration", function() {
        const sample_in =
        `
        function foo(): void {
            console.log("A")
            return
        }

        foo()
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(funcDecl))

        const newStatements = [
            ts.factory.updateFunctionDeclaration(
                funcDecl,
                undefined,
                undefined,
                funcDecl.name,
                undefined,
                funcDecl.parameters,
                undefined,
                funcDecl.body,
            ),
            sourceFile.statements[1],
        ]

        ts.factory.updateSourceFile(sourceFile, newStatements)

        util.assertEqualsBinaryOutput('A', this)
    })

    test("updating-lambda-call", function() {
        const sample_in =
        `
        function foo(builder: () => void) {}
        foo(() => {})
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))
        const exprStatement = sourceFile.statements[1]
        util.assert(ts.isExpressionStatement(exprStatement))
        const callExpr = exprStatement.expression
        util.assert(ts.isCallExpression(callExpr))

        util.assert(ts.isArrowFunction(callExpr.arguments[0]))
        const lambdaArg =
        ts.factory.createArrowFunction(
            undefined,
            undefined,
            [],
            undefined,
            undefined,
            callExpr.arguments[0].body
        )

        util.assert(ts.isIdentifier(callExpr.expression))
        const newStatements = [
            sourceFile.statements[0],
            ts.factory.updateExpressionStatement(
                exprStatement,
                ts.factory.updateCallExpression(
                    callExpr,
                    ts.factory.createIdentifier('foo'),
                    undefined,
                    [
                        lambdaArg,
                    ]
                )
            )
        ]
        ts.factory.updateSourceFile(sourceFile, newStatements)

        util.assertEqualsBinaryOutput('', this)
    })

    test("changing-variable-annotation", function() {
        const sample_in =
        `
        class A {}

        let x: AB

        console.log("ok")
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const varDecl = sourceFile.statements[1]
        util.assert(ts.isVariableStatement(varDecl))

        const declList = varDecl.declarationList
        util.assert(ts.isVariableDeclarationList(declList))

        const x = declList.declarations[0]
        util.assert(ts.isVariableDeclaration(x))

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                sourceFile.statements[0],
                ts.factory.updateVariableStatement(
                    varDecl,
                    undefined,
                    // declList
                    ts.factory.createVariableDeclarationList(
                        [ts.factory.createVariableDeclaration(
                            ts.factory.createIdentifier("x"),
                            undefined,
                            ts.factory.createTypeReferenceNode(
                                ts.factory.createIdentifier("A")
                            ),
                            undefined
                        )],
                        undefined
                    )
                ),
                sourceFile.statements[2]
            ]
        )

        util.assertEqualsBinaryOutput('ok', this)
    })

    test.skip("function-expression", function() {
        const sample_in =
        `
        const foo = function() { console.log("abc"); };
        foo();
        `

        ts.factory.createSourceFile(sample_in)
        util.assertEqualsBinaryOutput('abc', this)
    })
})

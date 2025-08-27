import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

suite(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        `

        let script = arkts.EtsScript.createFromSource(sample_in)

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                arkts.factory.createImportDeclaration(
                    arkts.factory.createStringLiteral(
                        './variable'
                    ),
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_VALUE,
                    true
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("sample-2-rewrite", function() {
        const sample_in =
        `
        import { Y } from "./variable"
        `

        let script = arkts.EtsScript.createFromSource(sample_in)
        const importDeclaration = script.statements[0] as arkts.EtsImportDeclaration

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                arkts.factory.updateImportDeclaration(
                    importDeclaration,
                    importDeclaration.importSource,
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_VALUE,
                    importDeclaration.hasDecl
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("rewrite-imported-variable", function() {
        const sample_in =
        `
        import { Y } from "./variable"

        function main() {
            console.log(X)
        }
        `

        let script = arkts.EtsScript.createFromSource(sample_in)
        const importDeclaration = script.statements[0] as arkts.EtsImportDeclaration

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                arkts.factory.updateImportDeclaration(
                    importDeclaration,
                    importDeclaration.importSource,
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_VALUE,
                    importDeclaration.hasDecl
                ),
                script.statements[1]
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"

            function main() {
                console.log(X)
            }
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        // util.cleanGenerated()
        // util.fileToAbc(`./input/variable.sts`, true)
        // util.contextToAbc()
        // util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })

    test("rewrite-imported-function", function() {
        const sample_in =
        `
        import { f } from "./f"
        function main() {}
        `

        let script = arkts.EtsScript.createFromSource(sample_in)
        const functionDeclaration: arkts.FunctionDeclaration = script.statements[1] as arkts.FunctionDeclaration
        const scriptFunction: arkts.ScriptFunction = functionDeclaration.scriptFunction

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                script.statements[0],
                arkts.factory.updateFunctionDeclaration(
                    functionDeclaration,
                    arkts.factory.updateScriptFunction(
                        scriptFunction,
                        arkts.factory.createBlock(
                            [
                                arkts.factory.createExpressionStatement(
                                    arkts.CallExpression.create(
                                        arkts.factory.createIdentifier(
                                            'f'
                                        ),
                                        undefined,
                                        []
                                    )
                                )
                            ]
                        ),
                        scriptFunction.scriptFunctionFlags,
                        scriptFunction.modifiers,
                        false,
                        scriptFunction.ident,
                        [],
                        undefined,
                        undefined
                    ),
                    false
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { f } from "./f"
            function main() {
                f()
            }
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        // util.cleanGenerated()
        // util.fileToAbc(`./input/f.sts`, true)
        // util.contextToAbc()
        // util.runAbc(`./generated/main.abc`, ['./generated/f.abc'])
    })
})

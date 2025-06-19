import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    // TODO: doesn't running now, but compiles (config gets only one file)
    test("sample-1", function() {
        const sample_in =
        `
        import { TEST } from "./export"
        console.log(TEST)
        `

        // util.getDefaultSetup(sample_in)

        // util.generateBinAndRun()
    })

    test("sample-2", function() {
        const sample_in =
        `
        import { power as F } from "std/math"
        console.log(F(2, 10))
        `

        // util.getDefaultSetup(sample_in)

        // arkts.proceedToState(arkts.ContextState.ES2PANDA_STATE_CHECKED)

        // const classDecl = arkts.nodeByPeer(util.getStatement(1))
        // util.assert(arkts.isClassDeclaration(classDecl))
        
        // const method = classDecl.members[1]
        // util.assert(arkts.isMethodDeclaration(method))

        // const body = method.body!
        // util.assert(arkts.isBlock(body))

        // const exprStatement = body.statements[0]
        // util.assert(arkts.isExpressionStatement(exprStatement))

        // const callExpr = exprStatement.expression
        // util.assert(arkts.isCallExpression(callExpr))

        // const F = callExpr.arguments[0]
        // util.assert(arkts.isCallExpression(F))

        // const ident = F.expression
        // util.assert(arkts.isIdentifier(ident))

        // console.log(arkts.dumpJsonNode(ident))

        // const decl = arkts.getDecl(ident)
        // if (decl !== undefined) {
        //     console.log(arkts.dumpJsonNode(decl))
        // } else {
        //     console.log(decl)
        // }

        // util.generateBinAndRun()
    })
})

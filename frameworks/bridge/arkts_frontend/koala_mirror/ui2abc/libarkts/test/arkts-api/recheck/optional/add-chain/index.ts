import * as arkts from "../../../../../src/arkts-api"
import * as fs from 'fs'

class AddOptionalChain extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isVariableDeclarator(node) && arkts.isIdentifier(node.id) && node.id.name == "zzz") {
            return arkts.factory.updateVariableDeclarator(
                node,
                node.flag,
                node.id,
                arkts.factory.createChainExpression(
                    arkts.factory.createMemberExpression(

                        arkts.factory.createIdentifier("x"),
                        arkts.factory.createIdentifier("y"),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    )
                )

            )
        }
        return node
    }
}

export function addOptionalChain(program: arkts.Program) {
    const inserted = (new AddOptionalChain()).visitor(program.astNode)
    const result = (new arkts.ChainExpressionFilter()).visitor(inserted)
    return result
}

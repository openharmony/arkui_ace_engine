import * as arkts from "../../../../src/arkts-api"

class AddThisReference extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.ETSModule): arkts.ETSModule
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isScriptFunction(node) && node.id?.name == "no_this") {
            return arkts.factory.updateScriptFunction(
                node,
                arkts.factory.createBlockStatement(
                    [

                        arkts.factory.createExpressionStatement(
                            arkts.factory.createThisExpression()
                        ),
                        ...(arkts.isBlockStatement(node.body) ? node.body.statements : []),
                    ]
                ),
                node.typeParams,
                node.params,
                node.returnTypeAnnotation,
                node.hasReceiver,
                node.flags,
                node.modifierFlags,
                node.id,
                node.annotations
            )
        }
        return node
    }
}

export function addThisReference(program: arkts.Program) {
    return (new AddThisReference()).visitor(program.astNode)
}

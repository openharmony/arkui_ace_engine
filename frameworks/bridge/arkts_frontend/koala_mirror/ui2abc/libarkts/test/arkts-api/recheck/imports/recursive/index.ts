import * as arkts from "../../../../../src/arkts-api"

class InsertParameter extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.ETSModule): arkts.ETSModule
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isScriptFunction(node) &&
            (node.id?.name == "one" ||  node.id?.name == "two") ) {

            return arkts.factory.updateScriptFunction(
                node,
                node.body,
                node.typeParams,
                [
                    arkts.factory.createETSParameterExpression(
                        arkts.factory.createIdentifier("createdParam"),
                        false,
                        undefined,
                        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_BOOLEAN),
                        undefined
                    )
                ],
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

export function insertParameter(program: arkts.Program) {
    return (new InsertParameter()).visitor(program.astNode)
}

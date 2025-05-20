import * as arkts from "../../../../../src/arkts-api"

class InsertParameterToType extends arkts.AbstractVisitor {
    visitor(beforeChildren: arkts.ETSModule): arkts.ETSModule
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        if (arkts.isETSFunctionType(node)) {
            return arkts.factory.createETSFunctionType(
                node.typeParams,
                [
                    arkts.factory.createETSParameterExpression(
                        arkts.factory.createIdentifier("createdParam"),
                        false,
                        undefined,
                        arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_BOOLEAN),
                        undefined
                    ),
                    ...node.params
                ],
                node.returnType,
                node.isExtensionFunction,
                node.flags,
                node.annotations,
            )
        }
        return node
    }
}

export function insertParameterToType(program: arkts.Program) {
    return (new InsertParameterToType()).visitor(program.astNode)
}

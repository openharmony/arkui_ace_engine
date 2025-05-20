import * as arkts from "../../../../../src/arkts-api"

export function addVariableDeclaration(node: arkts.ClassDefinition) {
    return arkts.factory.updateClassDefinition(
        node,
        node.ident,
        node.typeParams,
        node.superTypeParams,
        node.implements,
        undefined,
        node.super,
        [
            ...node.body.map((node: arkts.AstNode) => {
                if (!arkts.isMethodDefinition(node)) {
                    return node
                }
                if (node.id?.name != "f") {
                    return node
                }
                if (!arkts.isFunctionExpression(node.value)) {
                    return node
                }
                const func = node.value.function
                if (!func || !arkts.isBlockStatement(func.body)) {
                    return node
                }
                return arkts.factory.updateMethodDefinition(
                    node,
                    node.kind,
                    node.key,
                    arkts.factory.updateFunctionExpression(
                        node.value,
                        node.id,
                        arkts.factory.updateScriptFunction(
                            func,
                            arkts.factory.updateBlockStatement(
                                func.body,
                                [
                                    arkts.factory.createVariableDeclaration(
                                        arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
                                        [
                                            arkts.factory.createVariableDeclarator(
                                                arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                                                arkts.factory.createIdentifier("x"),
                                                arkts.factory.createBinaryExpression(
                                                    arkts.factory.createNumberLiteral(1),
                                                    arkts.factory.createNumberLiteral(4),
                                                    arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS,
                                                ),
                                            ),
                                        ],
                                    ),
                                    ...func.body.statements,
                                ],
                            ),
                            func.typeParams,
                            func.params,
                            func.returnTypeAnnotation,
                            func.hasReceiver,
                            func.flags,
                            func.modifierFlags,
                            func.id,
                            func.annotations,
                        ),
                    ),
                    node.modifierFlags,
                    node.isComputed,
                    node.overloads,
                )
            })
        ],
        node.modifiers,
        node.modifierFlags
    )
}

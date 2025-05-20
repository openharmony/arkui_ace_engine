import * as arkts from "../../../../../src/arkts-api"

export function addClassMethod(node: arkts.ClassDefinition) {
    return arkts.factory.updateClassDefinition(
        node,
        node.ident,
        node.typeParams,
        node.superTypeParams,
        node.implements,
        undefined,
        node.super,
        [
            arkts.factory.createMethodDefinition(
                arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
                arkts.factory.createIdentifier("g"),
                arkts.factory.createFunctionExpression(
                    arkts.factory.createIdentifier("g"),
                    arkts.factory.createScriptFunction(
                        arkts.factory.createBlockStatement([
                            arkts.factory.createReturnStatement(
                                arkts.factory.createNumberLiteral(5)
                            )
                        ]),
                        undefined,
                        [],
                        arkts.factory.createETSPrimitiveType(
                            arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_DOUBLE,
                        ),
                        false,
                        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
                        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
                        arkts.factory.createIdentifier("g"),
                        undefined,
                    )
                ),
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
                false,
            ),
            ...node.body,
        ],
        node.modifiers,
        node.modifierFlags
    )
}

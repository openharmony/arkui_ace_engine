import * as arkts from "../../../../../src/arkts-api"

export function renameClass(node: arkts.ClassDefinition) {
    return arkts.factory.updateClassDefinition(
        node,
        node.ident ? arkts.factory.updateIdentifier(
            node.ident,
            "D"
        ) : undefined,
        node.typeParams,
        node.superTypeParams,
        node.implements,
        undefined,
        node.super,
        node.body,
        node.modifiers,
        node.modifierFlags
    )
}

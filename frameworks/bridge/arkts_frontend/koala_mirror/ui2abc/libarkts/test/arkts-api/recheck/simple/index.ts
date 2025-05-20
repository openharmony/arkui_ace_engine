import * as arkts from "../../../../src/arkts-api"

export function updateTopLevelClass(
    module: arkts.ETSModule,
    update: (node: arkts.ClassDefinition) => arkts.ClassDefinition
) {
    return arkts.updateETSModuleByStatements(
        module,
        [
            ...module.statements.map((node) => {
                if (!arkts.isClassDeclaration(node)) {
                    return node
                }
                if (!arkts.isClassDefinition(node.definition)) {
                    return node
                }
                if (node.definition.ident?.name == "C") {
                    return arkts.factory.updateClassDeclaration(
                        node,
                        update(node.definition)
                    )
                }
                return node
            })
        ]
    )
}

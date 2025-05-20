import * as arkts from "../../../../../src/arkts-api"

export function addUseImportSameFile(program: arkts.Program, options: arkts.CompilationOptions) {
    if (options.isMainProgram) {
        arkts.updateETSModuleByStatements(
            program.astNode,
            [
                ...program.astNode.statements,
                arkts.factory.createCallExpression(
                    arkts.factory.createIdentifier("testFunction"),
                    [],
                    undefined,
                    false,
                    false,
                    undefined
                )
            ]
        )
        arkts.factory.createETSImportDeclaration(
            arkts.factory.createStringLiteral(
                './library'
            ),
            [
                arkts.factory.createImportSpecifier(
                    arkts.factory.createIdentifier(
                        'testFunction'
                    ),
                    arkts.factory.createIdentifier(
                        'testFunction'
                    )
                )
            ],
            arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
            arkts.arktsGlobal.compilerContext.program,
            arkts.Es2pandaImportFlags.IMPORT_FLAGS_NONE
        )
    }
    return program
}

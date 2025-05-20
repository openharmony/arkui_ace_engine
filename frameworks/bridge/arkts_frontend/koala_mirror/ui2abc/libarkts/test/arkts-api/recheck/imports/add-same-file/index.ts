import * as arkts from "../../../../../src/arkts-api"

export function addImportSameFile(program: arkts.Program, options: arkts.CompilationOptions) {
    if (options.isMainProgram) {
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

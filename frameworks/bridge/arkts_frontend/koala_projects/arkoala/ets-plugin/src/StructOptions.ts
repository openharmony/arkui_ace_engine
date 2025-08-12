import * as ts from "@koalaui/ets-tsc"
import { sourceStructName } from "./ApiUtils"
import { adaptorClassName, isDefined, prependMemoComment, throwError } from "./utils"
import { PropertyTranslatorContext, classifyProperty } from "./PropertyTranslators"
import { Importer } from "./Importer"
import { ImportExport } from "./import-export";

export class OptionDescriptor {
    constructor(
        public name: ts.Identifier,
        public type: ts.TypeNode,
        public isBuilderParam: boolean = false
    ) {}
}

export class StructOptions {
    private importExport: ImportExport
    constructor(
        private context: PropertyTranslatorContext,
        private typechecker: ts.TypeChecker
    ) {
        this.importExport = new ImportExport(this.typechecker)
    }

    private implProperties(node: ts.StructDeclaration): OptionDescriptor[] {
        return node.members
            .map(it => classifyProperty(it, this.context))
            .filter(isDefined)
            .flatMap(it => it.implField())
    }

    private structOptionsName(node: ts.StructDeclaration | ts.Identifier) {
        return `${this.structName(node)}Options`
    }

    private structName(node: ts.StructDeclaration | ts.Identifier) {
        if (ts.isStructDeclaration(node)) {
            node = sourceStructName(node)
        }
        return ts.idText(node)
    }

    public createDeclaration(node: ts.StructDeclaration) {
        return ts.factory.createInterfaceDeclaration(
            [ts.factory.createToken(ts.SyntaxKind.ExportKeyword)],
            this.structOptionsName(node),
            [],
            [],
            this.implProperties(node)
                .map(descriptor => {
                    const property = ts.factory.createPropertySignature(
                        undefined,
                        ts.idText(descriptor.name),
                        ts.factory.createToken(ts.SyntaxKind.QuestionToken),
                        descriptor.type
                    )
                    if (descriptor.isBuilderParam) {
                        return prependMemoComment(property)
                    } else {
                        return property
                    }
                })
        )
    }

    public updatedInitializersValue(node: ts.StructDeclaration, instance: ts.Identifier) {
        return ts.factory.createObjectLiteralExpression(
            node.members
                .map(it => classifyProperty(it, this.context))
                .filter(isDefined)
                .flatMap(it => it.toInitialization(instance)),
            true
        )
    }

    public createTypeReference(node: ts.StructDeclaration | ts.Identifier) {
        if (ts.isStructDeclaration(node)) {
            node = sourceStructName(node)
        }

        return ts.factory.createTypeReferenceNode(
            this.structOptionsName(node)
        )
    }

    public addImport(node: ts.ImportDeclaration): ts.ImportDeclaration {
        /*
            TODO: only named imports supported for now
         */
        if (node.importClause === undefined) return node
        const namedImports = node.importClause.namedBindings
        if (namedImports === undefined) return node
        if (!ts.isNamedImports(namedImports)) return node

        const structOptionsImports = namedImports.elements
            .filter(it => {
                const real = this.importExport.findRealDeclaration(it.name)
                return real !== undefined && ts.isStructDeclaration(real)
            })
            .map(it =>
                ts.factory.createImportSpecifier(
                    false,
                    undefined,
                    ts.factory.createIdentifier(this.structOptionsName(it.name))
                )
            )

        return ts.factory.updateImportDeclaration(
            node,
            node.modifiers,
            ts.factory.updateImportClause(
                node.importClause,
                node.importClause.isTypeOnly,
                node.importClause.name,
                ts.factory.updateNamedImports(
                    namedImports,
                    namedImports.elements.concat(structOptionsImports)
                )
            ),
            node.moduleSpecifier,
            node.assertClause
        )
    }
}
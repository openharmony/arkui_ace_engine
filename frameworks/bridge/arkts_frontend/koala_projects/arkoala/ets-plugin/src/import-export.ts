/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import * as ts from '@koalaui/ets-tsc';
import { getDeclarationsByNode } from "./ApiUtils"


export class ImportExport {
    constructor(
        public typechecker: ts.TypeChecker,
    ) {}

    isRealDeclaration(declaration: ts.Declaration): boolean {
        if (ts.isImportSpecifier(declaration) ||
            ts.isExportSpecifier(declaration) ||
            ts.isImportClause(declaration)) return false
        return true
    }

    followDefaultImport(identifier: ts.Identifier, importClause: ts.ImportClause): ts.Declaration | undefined {
        const moduleSpecifier = importClause.parent.moduleSpecifier
        const importSym = this.typechecker.getSymbolAtLocation(moduleSpecifier)
        if (importSym === undefined) {
            // console.log(`Could not obtain import symbol for ${ts.idText(identifier)}`)
            return undefined
        }
        const exports = this.typechecker.getExportsOfModule(importSym)

        return arrayAt(exports?.[0]?.declarations, 0)
    }

    followModuleSpecifier(identifier: ts.Identifier, moduleSpecifier: ts.StringLiteral): ts.Declaration | undefined {
        const moduleSym = this.typechecker.getSymbolAtLocation(moduleSpecifier)
        if (moduleSym === undefined) {
            // TODO: The typechecker doesn't give us the symbol in this case
            // So be silent for now.
            if (moduleSpecifier.text.startsWith("#")) {
                return undefined
            }
            // console.log(`Could not obtain module symbol for ${ts.idText(identifier)}: ${moduleSpecifier.text} `)
            return undefined
        }
        const exports = this.typechecker.getExportsOfModule(moduleSym)

        const found = exports.find(sym => ts.symbolName(sym) == ts.idText(identifier))
        return arrayAt(found?.declarations, 0)
    }

    followImport(identifier: ts.Identifier, declaration: ts.ImportSpecifier): ts.Declaration | undefined {
        if (declaration.propertyName) {
            const real = getDeclarationsByNode(this.typechecker, declaration.propertyName)[0]
            if (real && this.isRealDeclaration(real)) {
                return real
            } else {
                // console.log(`TODO: unexpected declaration: ${real}`)
                return undefined
            }
        }

        const moduleSpecifier = declaration.parent.parent.parent.moduleSpecifier
        if (!ts.isStringLiteral(moduleSpecifier)) {
            // console.log("Expected module specifier literal, got: " + ts.SyntaxKind[moduleSpecifier.kind])
            return undefined
        }
        return this.followModuleSpecifier(identifier, moduleSpecifier)
    }

    followExport(identifier: ts.Identifier, exportDeclaration: ts.ExportSpecifier): ts.Declaration | undefined {
        const moduleSpecifier = exportDeclaration.parent.parent.moduleSpecifier
        const name = exportDeclaration.propertyName ? exportDeclaration.propertyName : identifier

        if (!moduleSpecifier) {
            if (!exportDeclaration.propertyName) {
                // This is
                // class X{}
                // export { X }
                // In this case X's declaration is the export directive,
                // so need a special way to get to the class declaration.
                return this.typechecker.getExportSpecifierLocalTargetSymbol(exportDeclaration)?.declarations?.[0]
            } else {
                // This is an export from its own module.
                return this.findRealDeclaration(exportDeclaration.propertyName)
            }
        }
        if (!ts.isStringLiteral(moduleSpecifier)) {
            console.log("Expected module specifier literal, got: " + ts.SyntaxKind[moduleSpecifier.kind])
            return undefined
        }

        return this.followModuleSpecifier(name, moduleSpecifier)
    }

    findRealDeclaration(identifier: ts.Identifier): ts.NamedDeclaration | undefined {
        const declarations = getDeclarationsByNode(this.typechecker, identifier)

        if (declarations.length > 1) {
            // TODO: shall we support overloads?
            // TODO: shall we allow a function and a namespace?
            // return error(`TODO: Multiple declarations for ${ts.idText(identifier)} not supported`)

            return undefined
        }

        let declaration: ts.Declaration | undefined = declarations[0]
        while (declaration !== undefined) {
            if (this.isRealDeclaration(declaration)) {
                return declaration
            } else if (ts.isImportSpecifier(declaration)) {
                declaration = this.followImport(identifier, declaration)
            } else if (ts.isExportSpecifier(declaration)) {
                declaration = this.followExport(identifier, declaration)
            } else if (ts.isImportClause(declaration)) {
                declaration = this.followDefaultImport(identifier, declaration)
            } else {
                console.log(`Ets plugin non-fatal: Expected a real declaration for ${ts.idText(identifier)}, but got ${declaration ? ts.SyntaxKind[declaration.kind] : undefined}`)
                return undefined
            }
        }

        return undefined
    }

    findRealMethodDeclaration(member: ts.MemberName): ts.Node | undefined {
        if (!ts.isIdentifier(member)) return undefined
        const declarations = getDeclarationsByNode(this.typechecker, member)
        return declarations[0]
    }
}

function arrayAt<T>(array: T[] | undefined, index: number): T | undefined {
    return array ? array[index >= 0 ? index : array.length + index] : undefined
}
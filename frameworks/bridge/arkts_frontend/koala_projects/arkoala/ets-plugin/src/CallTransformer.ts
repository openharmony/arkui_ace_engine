/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { getDeclarationsByNode, hasDecorator } from './ApiUtils'
import { asString, CallTable, findBuilderLambdaRedirect, isGlobalBuilder, hasLocalDeclaration, isBuiltinComponentName, CustomDialogDecorator, ComponentDecorator } from './utils'
import { Importer } from './Importer'
import { ImportExport } from './import-export'


export class CallTransformer extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private typechecker: ts.TypeChecker,
        private callTable: CallTable,
        private importer: Importer
    ) {
        super(sourceFile, ctx)
    }

    private importExport = new ImportExport(this.typechecker)

    refersToGlobalBuilder(call: ts.CallExpression): boolean {
        const callee = call.expression
        if (ts.isIdentifier(callee)) {
            const declarations = getDeclarationsByNode(this.typechecker, callee)
            if (declarations.length == 0) return false
            const firstDeclaration = declarations[0]
            if (ts.isFunctionDeclaration(firstDeclaration) &&
                isGlobalBuilder(firstDeclaration)
            ) return true
        }
        return false
    }

    getImportModuileSpecifier(node: ts.Identifier): ts.StringLiteral|undefined {
        const declarations = getDeclarationsByNode(this.typechecker, node)
        const declaration = declarations[0]
        if (!declaration) return undefined
        let importDeclaration = undefined
        if (ts.isImportSpecifier(declaration)) {
            importDeclaration = declaration.parent.parent.parent
        } else if (ts.isImportClause(declaration)) {
            importDeclaration = declaration.parent
        }
        if (!importDeclaration || !ts.isImportDeclaration(importDeclaration)) {
            return undefined
        }
        const moduleSpecifier = importDeclaration.moduleSpecifier
        if (!ts.isStringLiteral(moduleSpecifier)) return undefined
        return moduleSpecifier
    }

    isLegacyCall(node: ts.Identifier): boolean {
        if (!this.importer.isArkoala()) return false

        const moduleSpecifier = this.getImportModuileSpecifier(node)
        if (!moduleSpecifier) return false
        const moduleSym = this.typechecker.getSymbolAtLocation(moduleSpecifier)
        if (moduleSym === undefined) return false
        return moduleSym.escapedName.toString().includes("library") || // TODO: don't forget to erase for production
           (this.importer.moduleInfo?.(moduleSym.escapedName.toString())?.isLegacy ?? false)
    }

    isComponentStructCall(node: ts.Identifier): boolean {
        const declaration = this.importExport.findRealDeclaration(node)
        if (!declaration) return false
        return ts.isStructDeclaration(declaration) && hasDecorator(declaration, ComponentDecorator)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)

        /**
         * Function call is treated as ETS Component call when:
         *   - it is listed in ETS components
         *   - it is not user defined
         */
        if (ts.isCallExpression(node) && ts.isIdentifier(node.expression)) {
            const func = node.expression
            const name = ts.idText(func)
            if (isBuiltinComponentName(this.ctx, name)) {
                if (hasLocalDeclaration(this.typechecker, func)) {
                    return node
                }
                return ts.factory.createEtsComponentExpression(
                    node.expression,
                    node.arguments,
                    undefined
                )
            }

            const builderLambdaRedirect = findBuilderLambdaRedirect(this.typechecker, node)
            if (builderLambdaRedirect) {
                this.callTable.builderLambdas.set(node, builderLambdaRedirect)
            }

            if (this.refersToGlobalBuilder(node)) {
                this.callTable.globalBuilderCalls.add(node)
            }

            if (this.isLegacyCall(node.expression)) {
                this.callTable.legacyCalls.add(node)
            }

            if (this.isComponentStructCall(node.expression)) {
                this.callTable.structCalls.add(ts.getOriginalNode(node) as ts.CallExpression)
            }
        }

        return node
    }
}

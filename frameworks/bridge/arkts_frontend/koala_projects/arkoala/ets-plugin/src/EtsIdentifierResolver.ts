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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from './AbstractVisitor'
import { Importer } from './Importer'
import { isBuiltinComponentName } from './utils'

// Set of names that should not be imported.
// TODO: It should be externally configurable for different implementations.
const prohibited = new Set<string>([
    "CommonInstance",
    "CustomComponent",
    "console",
    "$r",
    "$rawfile",
])

export class EtsIdentifierResolver extends AbstractVisitor {
    constructor(
        sourceFile: ts.SourceFile,
        ctx: ts.TransformationContext,
        private typeChecker: ts.TypeChecker,
        private importer: Importer,
    ) {
        super(sourceFile, ctx)
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        if (ts.isIdentifier(node)) {
            const declarations = this.typeChecker.getSymbolAtLocation(node)?.getDeclarations()?.filter(isIndexFullDeclaration)
            if (declarations && declarations.length > 0) {
                // process identifiers automatically imported from index-full.d.ts
                const text = this.getAdaptorImport(node)
                if (text) this.importer.addAdaptorImport(text)
            }
        }
        return node
    }

    private getAdaptorImport(id: ts.Identifier) {
        if (isDecorator(id.parent)) return undefined
        const text = ts.idText(id)
        return prohibited.has(text) || isBuiltinComponentStuff(this.ctx, text)
            ? undefined
            : text
    }
}

function isDecorator(node: ts.Node) {
    return ts.isDecorator(
        ts.isCallExpression(node)
            ? node.parent // @Id(...)
            : node)
}

function isIndexFullDeclaration(declaration: ts.Declaration) {
    return isSourceFile(
        ts.isVariableDeclarationList(declaration.parent) && ts.isVariableStatement(declaration.parent.parent)
            ? declaration.parent.parent.parent // const variable is declared in the top-level list
            : declaration.parent,
        "index-full.d.ts")
}

function isSourceFile(node: ts.Node, name: string): boolean {
    return ts.isSourceFile(node) && node.fileName.endsWith(name)
}

function isBuiltinComponentStuff(ctx: ts.TransformationContext, name: string) {
    if (name.endsWith("Attribute")) return isBuiltinComponentName(ctx, name.substring(0, name.length - 9))
    if (name.endsWith("Interface")) return isBuiltinComponentName(ctx, name.substring(0, name.length - 9))
    if (name.endsWith("Instance")) return isBuiltinComponentName(ctx, name.substring(0, name.length - 8))
    return isBuiltinComponentName(ctx, name)
}

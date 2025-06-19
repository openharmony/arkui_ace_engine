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
import { AbstractVisitor } from "./AbstractVisitor";
import { Rewrite } from "./transformation-context";
import { createContextTypeImport, FunctionKind, hiddenParameters, skipParenthesizedType, Tracer } from "./util";

export class VariableTypeTransformer extends AbstractVisitor {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public rewrite: Rewrite,
        ctx: ts.TransformationContext
    ) {
        super(ctx)
    }

    private updateMemoType(node: undefined): undefined
    private updateMemoType(node: ts.TypeNode): ts.TypeNode
    private updateMemoType(node: ts.TypeNode | undefined): ts.TypeNode | undefined
    private updateMemoType(node: ts.TypeNode | undefined): ts.TypeNode | undefined {
        if (node === undefined) return undefined
        if (ts.isParenthesizedTypeNode(node)) return this.updateMemoType(skipParenthesizedType(node))
        if (ts.isFunctionTypeNode(node)) return this.updateFunctionType(node)
        if (this.isFunctionOrUndefinedType(node)) return this.transformFunctionOrUndefined(node)

        return node
    }

    private isParenthesisedFunctionTypeNode(node: ts.TypeNode): boolean {
        if (ts.isFunctionTypeNode(node)) return true
        return ts.isParenthesizedTypeNode(node) && ts.isFunctionTypeNode(node.type)
    }

    private updateFunctionType(node: ts.FunctionTypeNode): ts.FunctionTypeNode {
        const additionalParameters = hiddenParameters(this.rewrite)
        const newParameters = additionalParameters.concat(node.parameters)

        return ts.factory.updateFunctionTypeNode(
            node,
            node.typeParameters,
            ts.factory.createNodeArray(newParameters),
            node.type
        )
    }

    private isFunctionOrUndefinedType(node: ts.TypeNode): node is ts.UnionTypeNode {
        const type = skipParenthesizedType(node)
        if (!type) return false
        if (!ts.isUnionTypeNode(type)) return false

        return type.types.every(it =>
            this.isParenthesisedFunctionTypeNode(it) || it.kind === ts.SyntaxKind.UndefinedKeyword
        )

    }

    private transformFunctionOrUndefined(node: ts.UnionTypeNode): ts.UnionTypeNode {
        const newTypes = node.types.map(it =>
            it.kind == ts.SyntaxKind.UndefinedKeyword
                ? it
                : this.updateMemoType(it)
        )
        return ts.factory.updateUnionTypeNode(
            node,
            ts.factory.createNodeArray(newTypes)
        )
    }

    private transformParameterType(node: ts.ParameterDeclaration): ts.ParameterDeclaration {
        const newType = this.updateMemoType(node.type)
        if (newType === undefined) return node

        return ts.factory.updateParameterDeclaration(
            node,
            node.modifiers,
            node.dotDotDotToken,
            node.name,
            node.questionToken,
            newType,
            node.initializer
        )
    }

    private transformVariableType(node: ts.VariableDeclaration): ts.VariableDeclaration {
        const newType = this.updateMemoType(node.type)
        if (newType === undefined) return node

        return ts.factory.updateVariableDeclaration(
            node,
            node.name,
            node.exclamationToken,
            newType,
            node.initializer
        )
    }

    private transformPropertyType(node: ts.PropertyDeclaration): ts.PropertyDeclaration {
        const newType = this.updateMemoType(node.type)
        if (newType === undefined) return node

        return ts.factory.updatePropertyDeclaration(
            node,
            node.modifiers,
            node.name,
            node.questionToken ?? node.exclamationToken,
            newType,
            node.initializer
        )
    }

    private transformPropertySignatureType(node: ts.PropertySignature): ts.PropertySignature {
        const newType = this.updateMemoType(node.type)
        if (newType === undefined) return node

        return ts.factory.updatePropertySignature(
            node,
            node.modifiers,
            node.name,
            node.questionToken,
            newType
        )
    }

    private addTypeImports(node: ts.SourceFile, rewrite: Rewrite): ts.SourceFile {
        if (rewrite.importTypesFrom == undefined) return node

        //  const newStatements = [createContextTypeImport(rewrite.importTypesFrom)].concat(node.statements.slice())
        // The below is to place new import after all the other imports
        // We are working around an es2panda bug here.
        // Feel free to throw away it not reproducible anymore.
        const newImport = createContextTypeImport(rewrite.importTypesFrom)
        const firstNonImportIndex = node.statements.findIndex(it => !ts.isImportDeclaration(it))
        const newStatements = node.statements.slice()
        newStatements.splice(firstNonImportIndex, 0, newImport)

        return ts.factory.updateSourceFile(
            node,
            newStatements,
            node.isDeclarationFile,
            node.referencedFiles,
            node.typeReferenceDirectives,
            node.hasNoDefaultLib,
            node.libReferenceDirectives
        )
    }

    visitor(beforeChildren: ts.Node): ts.Node {
        const node = this.visitEachChild(beforeChildren)
        let transformed: ts.Node|undefined = undefined
        if (ts.isParameter(node)) {
            const kind = this.rewrite.variableTable.get(ts.getOriginalNode(node) as ts.ParameterDeclaration)
            if (kind == FunctionKind.MEMO) {
                transformed = this.transformParameterType(node)
            }
        } else if (ts.isVariableDeclaration(node)) {
            const kind = this.rewrite.variableTable.get(ts.getOriginalNode(node) as ts.VariableDeclaration)
            if (kind == FunctionKind.MEMO) {
                transformed = this.transformVariableType(node)
            }
        } else if (ts.isPropertyDeclaration(node)) {
            const kind = this.rewrite.variableTable.get(ts.getOriginalNode(node) as ts.PropertyDeclaration)
            if (kind == FunctionKind.MEMO) {
                transformed = this.transformPropertyType(node)
            }
        } else if (ts.isPropertySignature(node)) {
            const kind = this.rewrite.variableTable.get(ts.getOriginalNode(node) as ts.PropertySignature)
            if (kind == FunctionKind.MEMO) {
                transformed = this.transformPropertySignatureType(node)
            }
        } else if (ts.isSourceFile(node)) {
            transformed = this.addTypeImports(node, this.rewrite)
        }

        return transformed ?? node
    }
}
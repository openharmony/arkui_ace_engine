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

import { factory } from "./factory/nodeFactory"
import {
    Es2pandaClassDefinitionModifiers,
    Es2pandaModifierFlags,
    Es2pandaVariableDeclaratorFlag
} from "../generated/Es2pandaEnums"
import { AstNode } from "./peers/AstNode"
import { isBlockStatement, isConditionalExpression, isTSInterfaceBody, isTSInterfaceDeclaration, isClassDeclaration, isClassDefinition } from "../generated"
import {
    isEtsScript,
    isCallExpression,
    isFunctionDeclaration,
    isExpressionStatement,
    isStructDeclaration,
    isMethodDefinition,
    isScriptFunction,
    isEtsImportDeclaration,
    isMemberExpression,
    isIfStatement,
    isVariableDeclaration,
    isVariableDeclarator,
    isArrowFunctionExpression
} from "./factory/nodeTests"
import { classDefinitionFlags } from "./utilities/public"

type Visitor = (node: AstNode) => AstNode

export interface DoubleNode {
    originNode: AstNode;
    translatedNode: AstNode;
}

export class StructInfo {
    stateVariables: Set<DoubleNode> = new Set();
}

export class GlobalInfo {
    private _structCollection: Set<string>;
    private static instance: GlobalInfo;
    private _structMap: Map<string, StructInfo>;

    private constructor() {
        this._structCollection = new Set();
        this._structMap = new Map();
    }

    public static getInfoInstance(): GlobalInfo {
        if (!this.instance) {
            this.instance = new GlobalInfo();
        }
        return this.instance;
    }

    public add(str: string): void {
        this._structCollection.add(str);
    }

    public getStructCollection(): Set<string> {
        return this._structCollection;
    }

    public getStructInfo(structName: string): StructInfo {
        const structInfo = this._structMap.get(structName);
        if (!structInfo) {
            return new StructInfo();
        }
        return structInfo;
    }

    public setStructInfo(structName: string, info: StructInfo): void {
        this._structMap.set(structName, info);
    }
}

// TODO: rethink (remove as)
function nodeVisitor<T extends AstNode | undefined>(node: T, visitor: Visitor): T {
    if (node === undefined) {
        return node
    }
    return visitor(node) as T
}

// TODO: rethink (remove as)
function nodesVisitor<T extends AstNode, TIn extends readonly T[] | undefined>(nodes: TIn, visitor: Visitor): T[] | TIn {
    if (nodes === undefined) {
        return nodes
    }
    return nodes.map(node => visitor(node) as T)
}

export function visitEachChild(
    node: AstNode,
    visitor: Visitor
): AstNode {
    if (isEtsScript(node)) {
        return factory.updateEtsScript(
            node,
            nodesVisitor(node.statements, visitor)
        )
    }
    if (isCallExpression(node)) {
        return factory.updateCallExpression(
            node,
            nodeVisitor(node.expression, visitor),
            nodesVisitor(node.typeArguments, visitor),
            nodesVisitor(node.arguments, visitor),
            nodeVisitor(node.trailingBlock, visitor)
        )
    }
    if (isFunctionDeclaration(node)) {
        return factory.updateFunctionDeclaration(
            node,
            nodeVisitor(node.scriptFunction, visitor),
            node.isAnon,
            node.annotations,
        )
    }
    if (isBlockStatement(node)) {
        return factory.updateBlock(
            node,
            nodesVisitor(node.statements, visitor),
        )
    }
    if (isExpressionStatement(node)) {
        return factory.updateExpressionStatement(
            node,
            nodeVisitor(node.expression, visitor)
        )
    }
    if (isClassDeclaration(node)) {
        return factory.updateClassDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
    }
    if (isStructDeclaration(node)) {
        return factory.updateStructDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
    }
    if (isClassDefinition(node)) {
        // TODO: fix
        return factory.updateClassDefinition(
            node,
            node.ident,
            node.typeParams,
            node.superTypeParams,
            node.implements,
            undefined,
            node.super,
            nodesVisitor(node.body, visitor),
            node.modifiers,
            classDefinitionFlags(node)
        )
    }
    if (isMethodDefinition(node)) {
        // TODO: fix
        return factory.updateMethodDefinition(
            node,
            node.kind,
            node.name,
            factory.createFunctionExpression(
                // TODO: maybe fix
                nodeVisitor(node.scriptFunction, visitor)
            ),
            node.modifiers,
            false
        )
    }
    if (isScriptFunction(node)) {
        return factory.updateScriptFunction(
            node,
            nodeVisitor(node.body, visitor),
            node.scriptFunctionFlags,
            Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
            false,
            nodeVisitor(node.ident, visitor),
            nodesVisitor(node.parameters, visitor),
            nodeVisitor(node.typeParamsDecl, visitor),
            nodeVisitor(node.returnTypeAnnotation, visitor),
            node.annotations
        )
    }
    if (isEtsImportDeclaration(node)) {
        return factory.updateImportDeclaration(
            node,
            nodeVisitor(node.importSource, visitor),
            nodesVisitor(node.importSpecifiers, visitor),
            node.importKind,
            node.hasDecl
        )
    }
    if (isMemberExpression(node)) {
        return factory.updateMemberExpression(
            node,
            nodeVisitor(node.object, visitor),
            nodeVisitor(node.property, visitor),
            node.kind,
            node.computed,
            node.optional
        )
    }
    if (isTSInterfaceDeclaration(node)) {
        return factory.updateInterfaceDeclaration(
            node,
            nodesVisitor(node.extends, visitor),
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodeVisitor(node.body, visitor),
            node.isStatic,
            // TODO: how do I get it?
            true
        )
    }
    if (isTSInterfaceBody(node)) {
        return factory.updateInterfaceBody(
            node,
            nodesVisitor(node.body, visitor)
        )
    }
    if (isIfStatement(node)) {
        return factory.updateIfStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor),
        )
    }
    if (isConditionalExpression(node)) {
        return factory.updateConditionalExpression(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor),
        )
    }
    if (isVariableDeclaration(node)) {
        return factory.updateVariableDeclaration(
            node,
            0,
            node.declarationKind,
            nodesVisitor(node.declarators, visitor),
        )
    }
    if (isVariableDeclarator(node)) {
        return factory.updateVariableDeclarator(
            node,
            Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_UNKNOWN,
            nodeVisitor(node.name, visitor),
            nodeVisitor(node.initializer, visitor),
        )
    }
    if (isArrowFunctionExpression(node)) {
        return factory.updateArrowFunction(
            node,
            nodeVisitor(node.scriptFunction, visitor),
        )
    }
    // TODO
    return node
}

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
import { AstNode } from "./peers/AstNode"
import {
    isArrayExpression,
    isArrowFunctionExpression,
    isAssignmentExpression,
    isBlockExpression,
    isBlockStatement,
    isCallExpression,
    isChainExpression,
    isClassDeclaration,
    isClassDefinition,
    isConditionalExpression,
    isETSModule,
    isETSStructDeclaration,
    isETSTuple,
    isExpressionStatement,
    isFunctionDeclaration,
    isFunctionExpression,
    isIfStatement,
    isMemberExpression,
    isMethodDefinition,
    isObjectExpression,
    isReturnStatement,
    isScriptFunction,
    isTemplateLiteral,
    isTryStatement,
    isTSAsExpression,
    isTSInterfaceBody,
    isTSInterfaceDeclaration,
    isTSTypeAliasDeclaration,
    isVariableDeclaration,
    isVariableDeclarator,
    isClassProperty,
    isIdentifier,
    isETSParameterExpression,
    isETSUnionType,
    isETSFunctionType,
    isWhileStatement,
} from "../generated"
import { updateETSModuleByStatements } from "./utilities/public"
import { global } from "./static/global"
import { Es2pandaScriptFunctionFlags } from "../generated/Es2pandaEnums"

type Visitor = (node: AstNode, options?: object) => AstNode

export interface DoubleNode {
    originNode: AstNode;
    translatedNode: AstNode;
}

export class StructInfo {
    stateVariables: Set<DoubleNode> = new Set();
    initializeBody: AstNode[] = [];
    updateBody: AstNode[] = [];
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
    global.profiler.visitedNodes ++
    if (isETSModule(node)) {
        return updateETSModuleByStatements(
            node,
            nodesVisitor(node.statements, visitor)
        )
    }
    if (isCallExpression(node)) {
        return factory.updateCallExpression(
            node,
            nodeVisitor(node.callee, visitor),
            nodesVisitor(node.arguments, visitor),
            nodeVisitor(node.typeParams, visitor),
            node.isOptional,
            node.hasTrailingComma,
            nodeVisitor(node.trailingBlock, visitor)
        )
    }
    if (isFunctionDeclaration(node)) {
        return factory.updateFunctionDeclaration(
            node,
            nodeVisitor(node.function, visitor),
            nodesVisitor(node.annotations, visitor),
            node.isAnonymous,
        )
    }
    if (isBlockStatement(node)) {
        return factory.updateBlockStatement(
            node,
            nodesVisitor(node.statements, visitor),
        )
    }
    if (isBlockExpression(node)) {
        return factory.updateBlockExpression(
            node,
            nodesVisitor(node.statements, visitor),
        )
    }
    if (isChainExpression(node)) {
        return factory.updateChainExpression(
            node,
            nodeVisitor(node.expression, visitor),
        )
    }
    if (isExpressionStatement(node)) {
        return factory.updateExpressionStatement(
            node,
            nodeVisitor(node.expression, visitor)
        )
    }
    if (isETSStructDeclaration(node)) {
        return factory.updateETSStructDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
    }
    if (isClassDeclaration(node)) {
        const _node = factory.updateClassDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
        _node.modifierFlags = node.modifierFlags
        return _node
    }
    if (isClassDefinition(node)) {
        return factory.updateClassDefinition(
            node,
            nodeVisitor(node.ident, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodeVisitor(node.superTypeParams, visitor),
            nodesVisitor(node.implements, visitor),
            undefined, /* can not pass node.ctor here because of mismatching types */
            nodeVisitor(node.super, visitor),
            nodesVisitor(node.body, visitor),
            node.modifiers,
            node.modifierFlags
        )
    }
    if (isMethodDefinition(node)) {
        return factory.updateMethodDefinition(
            node,
            node.kind,
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.value, visitor),
            node.modifierFlags,
            node.isComputed,
            nodesVisitor(node.overloads, visitor)
        )
    }
    if (isScriptFunction(node)) {
        return factory.updateScriptFunction(
            node,
            nodeVisitor(node.body, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodesVisitor(node.params, visitor),
            nodeVisitor(node.returnTypeAnnotation, visitor),
            node.hasReceiver,
            node.flags,
            node.modifierFlags,
            nodeVisitor(node.id, visitor),
            nodesVisitor(node.annotations, visitor)
        )
    }
    if (isETSParameterExpression(node)) {
        if (node.isRestParameter) {
            /** there is no RestParameter node at .idl */
            return node
        }
        return factory.updateETSParameterExpression(
            node,
            nodeVisitor(node.ident, visitor),
            node.isOptional,
            nodeVisitor(node.initializer, visitor),
            nodeVisitor(node.typeAnnotation, visitor),
            nodesVisitor(node.annotations, visitor),
        )
    }
    if (isMemberExpression(node)) {
        return factory.updateMemberExpression(
            node,
            nodeVisitor(node.object, visitor),
            nodeVisitor(node.property, visitor),
            node.kind,
            node.isComputed,
            node.isOptional
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
            node.isFromExternal
        )
    }
    if (isTSInterfaceBody(node)) {
        return factory.updateTSInterfaceBody(
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
            node.kind,
            nodesVisitor(node.declarators, visitor),
            nodesVisitor(node.annotations, visitor)
        )
    }
    if (isVariableDeclarator(node)) {
        return factory.updateVariableDeclarator(
            node,
            node.flag,
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.init, visitor),
        )
    }
    if (isArrowFunctionExpression(node)) {
        return factory.updateArrowFunctionExpression(
            node,
            nodeVisitor(node.function, visitor),
            nodesVisitor(node.annotations, visitor)
        )
    }
    if (isReturnStatement(node)) {
        return factory.updateReturnStatement(
            node,
            nodeVisitor(node.argument, visitor)
        )
    }
    if (isTSAsExpression(node)) {
        return factory.updateTSAsExpression(
            node,
            nodeVisitor(node.expr, visitor),
            nodeVisitor(node.typeAnnotation, visitor),
            node.isConst
        )
    }
    if (isTemplateLiteral(node)) {
        return factory.updateTemplateLiteral(
            node,
            nodesVisitor(node.quasis, visitor),
            nodesVisitor(node.expressions, visitor),
            node.multilineString
        )
    }
    if (isTSTypeAliasDeclaration(node)) {
        return factory.updateTSTypeAliasDeclaration(
            node,
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodeVisitor(node.typeAnnotation, visitor),
            nodesVisitor(node.annotations, visitor),
        )
    }
    if (isTryStatement(node)) {
        return factory.updateTryStatement(
            node,
            nodeVisitor(node.block, visitor),
            nodesVisitor(node.catchClauses, visitor),
            nodeVisitor(node.finallyBlock, visitor),
            [],
            []
        )
    }
    if (isObjectExpression(node)) {
        return factory.updateObjectExpression(
            node,
            nodesVisitor(node.properties, visitor)
        )
    }
    if (isFunctionExpression(node)) {
        return factory.updateFunctionExpression(
            node,
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.function, visitor)
        )
    }
    if (isArrayExpression(node)) {
        return factory.updateArrayExpression(
            node,
            nodesVisitor(node.elements, visitor)
        )
    }
    if (isAssignmentExpression(node)) {
        return factory.updateAssignmentExpression(
            node,
            nodeVisitor(node.left, visitor),
            nodeVisitor(node.right, visitor),
            node.operatorType,
        )
    }
    if (isETSTuple(node)) {
        return factory.updateETSTuple(
            node,
            nodesVisitor(node.tupleTypeAnnotationsList, visitor)
        )
    }
    if (isETSUnionType(node)) {
        return factory.updateETSUnionType(
            node,
            nodesVisitor(node.types, visitor),
        )
    }
    if (isETSFunctionType(node)) {
        return factory.updateETSFunctionType(
            node,
            nodeVisitor(node.typeParams, visitor),
            nodesVisitor(node.params, visitor),
            nodeVisitor(node.returnType, visitor),
            false, // TODO: how to get it?
            Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW,
            nodesVisitor(node.annotations, visitor),
        )
    }
    if (isClassProperty(node)) {
        return factory.updateClassProperty(
            node,
            nodeVisitor(node.key, visitor),
            nodeVisitor(node.value, visitor),
            nodeVisitor(node.typeAnnotation, visitor),
            node.modifierFlags,
            node.isComputed
        )
    }
    if (isIdentifier(node)) {
        return factory.updateIdentifier(
            node,
            node.name,
            nodeVisitor(node.typeAnnotation, visitor)
        )
    }
    if (isWhileStatement(node)) {
        return factory.updateWhileStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.body, visitor),
        )
    }
    return node
}

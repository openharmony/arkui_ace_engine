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

import {
    isArrayExpression,
    isArrowFunctionExpression,
    isAssignmentExpression,
    isBinaryExpression,
    isBlockExpression,
    isBlockStatement,
    isCallExpression,
    isChainExpression,
    isClassDeclaration,
    isClassDefinition,
    isClassProperty,
    isConditionalExpression,
    isDoWhileStatement,
    isETSFunctionType,
    isETSImportDeclaration,
    isETSModule,
    isETSNewClassInstanceExpression,
    isETSParameterExpression,
    isETSStructDeclaration,
    isETSTuple,
    isETSTypeReference,
    isETSTypeReferencePart,
    isETSUnionType,
    isExpressionStatement,
    isForInStatement,
    isForOfStatement,
    isForUpdateStatement,
    isFunctionDeclaration,
    isFunctionExpression,
    isIdentifier,
    isIfStatement,
    isMemberExpression,
    isMethodDefinition,
    isObjectExpression,
    isProperty,
    isReturnStatement,
    isScriptFunction,
    isSwitchCaseStatement,
    isSwitchStatement,
    isTemplateLiteral,
    isTryStatement,
    isTSAsExpression,
    isTSInterfaceBody,
    isTSInterfaceDeclaration,
    isTSNonNullExpression,
    isTSTypeAliasDeclaration,
    isTSTypeParameterDeclaration,
    isTSTypeParameterInstantiation,
    isUpdateExpression,
    isVariableDeclaration,
    isVariableDeclarator,
    isWhileStatement
} from "../generated"
import { Es2pandaImportKinds } from "../generated/Es2pandaEnums"
import { factory } from "./factory/nodeFactory"
import { AstNode } from "./peers/AstNode"
import { global } from "./static/global"
import { updateETSModuleByStatements } from "./utilities/public"

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
        return factory.updateClassDeclaration(
            node,
            nodeVisitor(node.definition, visitor),
            node.modifierFlags,
        )
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
    if (isSwitchStatement(node)) {
        return factory.updateSwitchStatement(
            node,
            nodeVisitor(node.discriminant, visitor),
            nodesVisitor(node.cases, visitor)
        )
    }
    if (isSwitchCaseStatement(node)) {
        return factory.updateSwitchCaseStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodesVisitor(node.consequent, visitor)
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
            node.isFromExternal,
            node.modifierFlags,
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
            node.modifierFlags,
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
            node.flags,
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
            node.isComputed,
            node.annotations,
        )
    }
    if (isProperty(node)) {
        return factory.updateProperty(
            node,
            node.kind,
            nodeVisitor(node.key, visitor),
            nodeVisitor(node.value, visitor),
            node.isMethod,
            node.isComputed
        )
    }
    if (isBinaryExpression(node)) {
        return factory.updateBinaryExpression(
            node,
            nodeVisitor(node.left, visitor),
            nodeVisitor(node.right, visitor),
            node.operatorType)
    }
    if (isIdentifier(node)) {
        return factory.updateIdentifier(
            node,
            node.name,
            nodeVisitor(node.typeAnnotation, visitor)
        )
    }
    if (isETSNewClassInstanceExpression(node)) {
        return factory.updateETSNewClassInstanceExpression(
            node,
            nodeVisitor(node.typeRef, visitor),
            nodesVisitor(node.arguments, visitor)
        )
    }
    if (isWhileStatement(node)) {
        return factory.updateWhileStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.body, visitor),
        )
    }
    if (isDoWhileStatement(node)) {
        return factory.updateDoWhileStatement(
            node,
            nodeVisitor(node.body, visitor),
            nodeVisitor(node.test, visitor),
        )
    }
    if (isForUpdateStatement(node)) {
        return factory.updateForUpdateStatement(
            node,
            nodeVisitor(node.init, visitor),
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.update, visitor),
            nodeVisitor(node.body, visitor),
        )
    }
    if (isForInStatement(node)) {
        return factory.updateForInStatement(
            node,
            nodeVisitor(node.left, visitor),
            nodeVisitor(node.right, visitor),
            nodeVisitor(node.body, visitor),
        )
    }
    if (isForOfStatement(node)) {
        return factory.updateForOfStatement(
            node,
            nodeVisitor(node.left, visitor),
            nodeVisitor(node.right, visitor),
            nodeVisitor(node.body, visitor),
            node.isAwait
        )
    }
    if (isETSImportDeclaration(node)) {
        return factory.updateETSImportDeclaration(
            node,
            nodeVisitor(node.source, visitor),
            nodesVisitor(node.specifiers, visitor),
            Es2pandaImportKinds.IMPORT_KINDS_ALL
        )
    }
    if (isTSNonNullExpression(node)) {
        return factory.updateTSNonNullExpression(
            node,
            nodeVisitor(node.expr, visitor)
        )
    }
    if (isUpdateExpression(node)) {
        return factory.updateUpdateExpression(
            node,
            nodeVisitor(node.argument, visitor),
            node.operatorType,
            node.isPrefix
        )
    }
    if (isETSTypeReference(node)) {
        return factory.updateETSTypeReference(
            node,
            nodeVisitor(node.part, visitor),
        )
    }
    if (isETSTypeReferencePart(node)) {
        return factory.updateETSTypeReferencePart(
            node,
            nodeVisitor(node.name, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodeVisitor(node.previous, visitor),
        )
    }
    if (isTSTypeParameterInstantiation(node)) {
        return factory.updateTSTypeParameterInstantiation(
            node,
            nodesVisitor(node.params, visitor),
        )
    }
    if (isTSTypeParameterDeclaration(node)) {
        return factory.updateTSTypeParameterDeclaration(
            node,
            nodesVisitor(node.params, visitor),
            node.requiredParams,
        )
    }
    /** TODO: fix this case!
    if (isClassStaticBlock(node)) {
        return factory.updateClassStaticBlock(

        )
        nodeVisitor(node.function, visitor)
    } */
    return node
}

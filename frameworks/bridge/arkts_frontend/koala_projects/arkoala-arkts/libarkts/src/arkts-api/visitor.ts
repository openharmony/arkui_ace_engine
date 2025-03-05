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
    ArrowFunctionExpression,
    CallExpression,
    ClassDeclaration,
    ClassDefinition,
    EtsImportDeclaration,
    EtsScript,
    ExpressionStatement,
    FunctionDeclaration,
    IfStatement,
    MethodDefinition,
    ScriptFunction,
    StructDeclaration,
    VariableDeclaration,
    VariableDeclarator,
} from "./types"
import {
    Es2pandaClassDefinitionModifiers,
    Es2pandaModifierFlags,
    Es2pandaVariableDeclaratorFlag
} from "../generated/Es2pandaEnums"
import { AstNode } from "./peers/AstNode"
import { MemberExpression } from "./to-be-generated/MemberExpression"
import { BlockStatement, ConditionalExpression, TSInterfaceBody, TSInterfaceDeclaration } from "../generated"

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
    if (node instanceof EtsScript) {
        return factory.updateEtsScript(
            node,
            nodesVisitor(node.statements, visitor)
        )
    }
    if (node instanceof CallExpression) {
        return factory.updateCallExpression(
            node,
            nodeVisitor(node.expression, visitor),
            nodesVisitor(node.typeArguments, visitor),
            nodesVisitor(node.arguments, visitor),
            nodeVisitor(node.trailingBlock, visitor)
        )
    }
    if (node instanceof FunctionDeclaration) {
        return factory.updateFunctionDeclaration(
            node,
            nodeVisitor(node.scriptFunction, visitor),
            node.isAnon
        )
    }
    if (node instanceof BlockStatement) {
        return factory.updateBlock(
            node,
            nodesVisitor(node.statements, visitor),
        )
    }
    if (node instanceof ExpressionStatement) {
        return factory.updateExpressionStatement(
            node,
            nodeVisitor(node.expression, visitor)
        )
    }
    if (node instanceof ClassDeclaration) {
        return factory.updateClassDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
    }
    if (node instanceof StructDeclaration) {
        return factory.updateStructDeclaration(
            node,
            nodeVisitor(node.definition, visitor)
        )
    }
    if (node instanceof ClassDefinition) {
        // TODO: fix
        return factory.updateClassDefinition(
            node,
            nodeVisitor(node.name, visitor),
            nodesVisitor(node.members, visitor),
            // passModifiers(modifiers) | es2panda_ModifierFlags.MODIFIER_FLAGS_PUBLIC | es2panda_ModifierFlags.MODIFIER_FLAGS_STATIC,
            node.modifiers,
            // TODO: pass through modifiers
            // Passing NONE causes failure when proceeding to CHECKED.
            Es2pandaClassDefinitionModifiers.CLASS_DEFINITION_MODIFIERS_CLASS_DECL,
            nodeVisitor(node.typeParamsDecl, visitor),
            nodeVisitor(node.superClass, visitor),
        )
    }
    if (node instanceof MethodDefinition) {
        // TODO: fix
        return factory.updateMethodDefinition(
            node,
            node.kind,
            node.name,
            factory.createFunctionExpression(
                // TODO: maybe fix
                factory.updateScriptFunction(
                    node.scriptFunction,
                    nodeVisitor(node.scriptFunction.body, visitor),
                    0,
                    node.modifiers | Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC || Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                    false,
                    node.name,
                    node.scriptFunction.parameters,
                    node.scriptFunction.typeParamsDecl,
                    node.scriptFunction.returnTypeAnnotation
                )
            ),
            node.modifiers,
            false
        )
    }
    if (node instanceof ScriptFunction) {
        return factory.updateScriptFunction(
            node,
            nodeVisitor(node.body, visitor),
            node.scriptFunctionFlags,
            Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
            false,
            nodeVisitor(node.ident, visitor),
            nodesVisitor(node.parameters, visitor),
            nodeVisitor(node.typeParamsDecl, visitor),
            nodeVisitor(node.returnTypeAnnotation, visitor)
        )
    }
    if (node instanceof EtsImportDeclaration) {
        return factory.updateImportDeclaration(
            node,
            nodeVisitor(node.importSource, visitor),
            nodesVisitor(node.importSpecifiers, visitor),
            node.importKind,
            node.hasDecl
        )
    }
    if (node instanceof MemberExpression) {
        return factory.updateMemberExpression(
            node,
            nodeVisitor(node.object, visitor),
            nodeVisitor(node.property, visitor),
            node.kind,
            node.computed,
            node.optional
        )
    }
    if (node instanceof TSInterfaceDeclaration) {
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
    if (node instanceof TSInterfaceBody) {
        return factory.updateInterfaceBody(
            node,
            nodesVisitor(node.body, visitor)
        )
    }
    if (node instanceof IfStatement) {
        return factory.updateIfStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor),
        )
    }
    if (node instanceof ConditionalExpression) {
        return factory.updateConditionalExpression(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor),
        )
    }
    if (node instanceof VariableDeclaration) {
        return factory.updateVariableDeclaration(
            node,
            0,
            node.declarationKind,
            nodesVisitor(node.declarators, visitor),
        )
    }
    if (node instanceof VariableDeclarator) {
        return factory.updateVariableDeclarator(
            node,
            Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_UNKNOWN,
            nodeVisitor(node.name, visitor),
            nodeVisitor(node.initializer, visitor),
        )
    }
    if (node instanceof ArrowFunctionExpression) {
        return factory.updateArrowFunction(
            node,
            nodeVisitor(node.scriptFunction, visitor),
        )
    }
    // TODO
    return node
}

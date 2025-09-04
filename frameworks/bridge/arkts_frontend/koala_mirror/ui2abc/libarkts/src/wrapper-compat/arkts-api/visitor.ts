/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { global } from './static/global';
import { factory } from './factory/nodeFactory';
import { factory as factory1 } from '../../arkts-api/factory/nodeFactory';
import { AstNode } from './peers/AstNode';
import {
    isBlockStatement,
    isConditionalExpression,
    isTSInterfaceBody,
    isTSInterfaceDeclaration,
    isClassDeclaration,
    isClassDefinition,
    isTSAsExpression,
    isETSImportDeclaration,
    ImportSource,
    isScriptFunction,
    FunctionSignature,
    Property,
    isClassProperty,
    isImportDeclaration,
    isObjectExpression,
    ObjectExpression,
    isProperty,
    Expression,
    isETSNewClassInstanceExpression,
    isTemplateLiteral,
    isBlockExpression,
    isReturnStatement,
    isArrayExpression,
    isTryStatement,
    isBinaryExpression,
} from '../../generated';
import {
    isEtsScript,
    isCallExpression,
    isFunctionDeclaration,
    isExpressionStatement,
    isStructDeclaration,
    isMethodDefinition,
    // isScriptFunction,
    isMemberExpression,
    isIfStatement,
    isVariableDeclaration,
    isVariableDeclarator,
    isArrowFunctionExpression,
    isAssignmentExpression,
} from './factory/nodeTests';
import { classDefinitionFlags } from './utilities/public';
import { Es2pandaAstNodeType } from '../../generated/Es2pandaEnums';

type Visitor = (node: AstNode) => AstNode;

// Improve: rethink (remove as)
function nodeVisitor<T extends AstNode | undefined>(node: T, visitor: Visitor): T {
    if (node === undefined) {
        return node;
    }
    return visitor(node) as T;
}

// Improve: rethink (remove as)
function nodesVisitor<T extends AstNode, TIn extends readonly T[] | undefined>(
    nodes: TIn,
    visitor: Visitor
): T[] | TIn {
    if (nodes === undefined) {
        return nodes;
    }
    return nodes.map((node) => visitor(node) as T);
}

let updated: boolean = false;

export function visitEachChild(node: AstNode, visitor: Visitor): AstNode {
    updated = false;
    let script: AstNode = node;
    script = visitETSModule(script, visitor);
    script = visitDeclaration(script, visitor);
    script = visitDefinition(script, visitor);
    script = visitDefinitionBody(script, visitor);
    script = visitStatement(script, visitor);
    script = visitOuterExpression(script, visitor);
    script = visitInnerExpression(script, visitor);
    script = visitTrivialExpression(script, visitor);
    script = visitLiteral(script, visitor);
    // Improve:
    return visitWithoutUpdate(script, visitor);
}

function visitOuterExpression(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    } else if (isBlockExpression(node)) {
        updated = true;
        return factory1.updateBlockExpression(node, nodesVisitor(node.statements, visitor));
    } else if (isCallExpression(node)) {
        updated = true;
        const call = factory.updateCallExpression(
            node,
            nodeVisitor(node.expression, visitor),
            nodesVisitor(node.typeArguments, visitor),
            nodesVisitor(node.arguments, visitor)
        );
        if (!!node.trailingBlock) {
            call.setTralingBlock(nodeVisitor(node.trailingBlock, visitor));
        }
        return call;
    } else if (isArrowFunctionExpression(node)) {
        updated = true;
        return factory.updateArrowFunction(node, nodeVisitor(node.scriptFunction, visitor));
    } else if (isAssignmentExpression(node)) {
        updated = true;
        return factory.updateAssignmentExpression(
            node,
            nodeVisitor(node.left as Expression, visitor),
            node.operatorType,
            nodeVisitor(node.right as Expression, visitor)
        );
    } else if (isETSNewClassInstanceExpression(node)) {
        updated = true;
        return factory1.updateETSNewClassInstanceExpression(
            node,
            node.typeRef,
            nodesVisitor(node.arguments, visitor)
        );
    }
    if (isArrayExpression(node)) {
        updated = true;
        return factory.updateArrayExpression(
            node,
            nodesVisitor(node.elements, visitor)
        );
    }
    return node;
}

function visitInnerExpression(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isMemberExpression(node)) {
        updated = true;
        return factory.updateMemberExpression(
            node,
            nodeVisitor(node.object, visitor),
            nodeVisitor(node.property, visitor),
            node.kind,
            node.computed,
            node.optional
        );
    }
    if (isConditionalExpression(node)) {
        updated = true;
        return factory1.updateConditionalExpression(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor)
        );
    }
    if (isTSAsExpression(node)) {
        updated = true;
        return factory1.updateTSAsExpression(
            node,
            nodeVisitor(node.expr, visitor),
            nodeVisitor(node.typeAnnotation, visitor),
            node.isConst
        );
    }
    if (isObjectExpression(node)) {
        updated = true;
        return factory.updateObjectExpression(
            node,
            Es2pandaAstNodeType.AST_NODE_TYPE_OBJECT_EXPRESSION,
            nodesVisitor(node.properties as Property[], visitor),
            false
        );
    }
    if (isProperty(node)) {
        updated = true;
        return factory.updateProperty(node, node.key, nodeVisitor(node.value, visitor));
    }
    // Improve:
    return node;
}

function visitTrivialExpression(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isBinaryExpression(node)) {
        updated = true;
        return factory1.updateBinaryExpression(
            node,
            nodeVisitor(node.left, visitor),
            nodeVisitor(node.right, visitor),
            node.operatorType
        );
    }
    // Improve:
    return node;
}

function visitDeclaration(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isFunctionDeclaration(node)) {
        updated = true;
        return factory.updateFunctionDeclaration(
            node,
            nodeVisitor(node.scriptFunction, visitor),
            node.isAnon,
            node.annotations
        );
    }
    if (isClassDeclaration(node)) {
        updated = true;
        return factory.updateClassDeclaration(node, nodeVisitor(node.definition, visitor));
    }
    if (isStructDeclaration(node)) {
        updated = true;
        return factory.updateStructDeclaration(node, nodeVisitor(node.definition, visitor));
    }
    if (isTSInterfaceDeclaration(node)) {
        updated = true;
        return factory.updateInterfaceDeclaration(
            node,
            nodesVisitor(node.extends, visitor),
            nodeVisitor(node.id, visitor),
            nodeVisitor(node.typeParams, visitor),
            nodeVisitor(node.body, visitor),
            node.isStatic,
            // Improve: how do I get it?
            true
        );
    }
    if (isVariableDeclaration(node)) {
        updated = true;
        return factory.updateVariableDeclaration(
            node,
            0,
            node.declarationKind,
            nodesVisitor(node.declarators, visitor)
        );
    }
    // Improve:
    return node;
}

function visitDefinition(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isClassDefinition(node)) {
        updated = true;
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
        );
    }
    if (isMethodDefinition(node)) {
        updated = true;
        return factory.updateMethodDefinition(
            node,
            node.kind,
            node.name,
            nodeVisitor(node.scriptFunction, visitor),
            node.modifiers,
            false
        );
    }
    if (isTSInterfaceBody(node)) {
        updated = true;
        return factory1.updateInterfaceBody(node, nodesVisitor(node.body, visitor));
    }
    if (isVariableDeclarator(node)) {
        updated = true;
        return factory.updateVariableDeclarator(
            node,
            global.generatedEs2panda._VariableDeclaratorFlag(global.context, node.peer),
            nodeVisitor(node.name, visitor),
            nodeVisitor(node.initializer, visitor)
        );
    }
    return node;
}

function visitStatement(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isBlockStatement(node)) {
        updated = true;
        return factory.updateBlock(node, nodesVisitor(node.statements, visitor));
    }
    if (isExpressionStatement(node)) {
        updated = true;
        return factory.updateExpressionStatement(node, nodeVisitor(node.expression, visitor));
    }
    if (isIfStatement(node)) {
        updated = true;
        return factory.updateIfStatement(
            node,
            nodeVisitor(node.test, visitor),
            nodeVisitor(node.consequent, visitor),
            nodeVisitor(node.alternate, visitor)
        );
    }
    if (isReturnStatement(node)) {
        updated = true;
        return factory1.updateReturnStatement(node, nodeVisitor(node.argument, visitor));
    }
    if (isTryStatement(node)) {
        updated = true;
        return factory.updateTryStatement(
            node,
            nodeVisitor(node.block, visitor),
            nodesVisitor(node.catchClauses, visitor),
            nodeVisitor(node.finallyBlock, visitor),
            [],
            []
        );
    }
    // Improve:
    return node;
}

function visitETSModule(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isEtsScript(node)) {
        updated = true;
        return factory.updateEtsScript(node, nodesVisitor(node.statements, visitor));
    }
    return node;
}

function visitDefinitionBody(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isScriptFunction(node)) {
        updated = true;
        return factory.updateScriptFunction(
            node,
            nodeVisitor(node.body, visitor),
            factory.createFunctionSignature(
                nodeVisitor(node.typeParams, visitor),
                nodesVisitor(node.params, visitor),
                nodeVisitor(node.returnTypeAnnotation, visitor),
                node.hasReceiver
            ),
            node.flags,
            node.modifiers
        );
    }
    if (isClassProperty(node)) {
        updated = true;
        return factory.updateClassProperty(
            node,
            node.key,
            nodeVisitor(node.value, visitor),
            node.typeAnnotation,
            node.modifiers,
            node.isComputed
        );
    }
    // Improve:
    return node;
}

function visitLiteral(node: AstNode, visitor: Visitor): AstNode {
    if (updated) {
        return node;
    }
    if (isTemplateLiteral(node)) {
        updated = true;
        return factory1.updateTemplateLiteral(
            node,
            nodesVisitor(node.quasis, visitor),
            nodesVisitor(node.expressions, visitor),
            node.multilineString
        );
    }
    return node;
}

// Improve: apply this to all nodes that does not require updating
function visitWithoutUpdate<T extends AstNode>(node: T, visitor: Visitor): T {
    if (updated) {
        return node;
    }
    if (isImportDeclaration(node)) {
        nodesVisitor(node.specifiers, visitor);
    }
    return node;
}

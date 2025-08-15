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

import { isSameNativeObject } from "../arkts-api/peers/ArktsObject"
import {
    AnnotationUsage,
    ArrayExpression,
    ArrowFunctionExpression,
    AssignmentExpression,
    BinaryExpression,
    BlockExpression,
    BlockStatement,
    CallExpression,
    CatchClause,
    ChainExpression,
    ClassDeclaration,
    ClassDefinition,
    ClassProperty,
    ClassStaticBlock,
    ConditionalExpression,
    DoWhileStatement,
    ETSFunctionType,
    ETSImportDeclaration,
    ETSModule,
    ETSNewClassInstanceExpression,
    ETSParameterExpression,
    ETSStructDeclaration,
    ETSTuple,
    ETSTypeReference,
    ETSTypeReferencePart,
    ETSUnionType,
    Expression,
    ExpressionStatement,
    ForInStatement,
    ForOfStatement,
    ForUpdateStatement,
    FunctionDeclaration,
    FunctionExpression,
    Identifier,
    IfStatement,
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
    isWhileStatement,
    MemberExpression,
    MethodDefinition,
    ObjectExpression,
    Property,
    ReturnStatement,
    ScriptFunction,
    Statement,
    SwitchCaseStatement,
    SwitchStatement,
    TemplateElement,
    TemplateLiteral,
    TryStatement,
    TSAsExpression,
    TSClassImplements,
    TSInterfaceBody,
    TSInterfaceDeclaration,
    TSInterfaceHeritage,
    TSNonNullExpression,
    TSTypeAliasDeclaration,
    TSTypeParameter,
    TSTypeParameterDeclaration,
    TSTypeParameterInstantiation,
    TypeNode,
    UpdateExpression,
    VariableDeclaration,
    VariableDeclarator,
    WhileStatement
} from "../generated"
import { Es2pandaAstNodeType, Es2pandaImportKinds } from "../generated/Es2pandaEnums"
import { factory } from "./factory/nodeFactory"
import { AstNode } from "./peers/AstNode"
import { global } from "./static/global"

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

// Improve: rethink (remove as)
function nodeVisitor<T extends AstNode | undefined>(node: T, visitor: Visitor): T {
    if (node === undefined) {
        return node
    }
    const result = visitor(node) as T
    if (node != result) {
        global.updateTracker.update()
    }
    return result
}

// Improve: rethink (remove as)
function nodesVisitor<T extends AstNode, TIn extends readonly T[] | undefined>(nodes: TIn, visitor: Visitor): T[] | TIn {
    if (nodes === undefined) {
        return nodes
    }
    return nodes.map(node => {
        const result = visitor(node) as T
        if (node != result) {
            global.updateTracker.update()
        }
        return result
    })
}

function visitBlockStatement(node: BlockStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newStatements: readonly Statement[] = nodesVisitor(node.statements, visitor)
    if (global.updateTracker.check()) {
        node.setStatements(newStatements)
    }
    return node
}

function visitETSModule(node: ETSModule, visitor: Visitor) {
    global.updateTracker.push()
    const newStatements: readonly Statement[] = nodesVisitor(node.statements, visitor)
    const oldIdent = node.ident
    const newIdent = nodeVisitor(oldIdent, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newIdent, oldIdent)) {
            const result = factory.createETSModule(
                newStatements,
                newIdent,
                node.getNamespaceFlag(),
                node.program,
            )
            result.onUpdate(node)
            return result
        }
        node.setStatements(newStatements)
    }
    return node
}

function visitCallExpression(node: CallExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newCallee = nodeVisitor(node.callee, visitor)
    const oldArguments = node.arguments
    const newArguments: readonly Expression[] = nodesVisitor(oldArguments, visitor)
    const newTypeParams = nodeVisitor(node.typeParams, visitor)
    const newTrailingBlock = nodeVisitor(node.trailingBlock, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newArguments, oldArguments)) {
            const result = factory.createCallExpression(
                newCallee,
                newArguments,
                newTypeParams,
                node.isOptional,
                node.hasTrailingComma,
                newTrailingBlock,
            )
            result.onUpdate(node)
            return result
        }
        node.setCallee(newCallee)
        node.setTypeParams(newTypeParams)
        node.setTrailingBlock(newTrailingBlock)
    }
    return node
}

function visitIdentifier(node: Identifier, visitor: Visitor) {
    global.updateTracker.push()
    const newTypeAnnotation = nodeVisitor(node.typeAnnotation, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createIdentifier(node.name, newTypeAnnotation)
        result.onUpdate(node)
        return result
    }
    return node
}

function visitMemberExpression(node: MemberExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newObject = nodeVisitor(node.object, visitor)
    const newProperty = nodeVisitor(node.property, visitor)
    if (global.updateTracker.check()) {
        node.setObject(newObject)
        node.setProperty(newProperty)
    }
    return node
}

function visitETSTypeReference(node: ETSTypeReference, visitor: Visitor) {
    global.updateTracker.push()
    const newPart = nodeVisitor(node.part, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createETSTypeReference(
            newPart,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitETSTypeReferencePart(node: ETSTypeReferencePart, visitor: Visitor) {
    global.updateTracker.push()
    const newName = nodeVisitor(node.name, visitor)
    const newTypeParams = nodeVisitor(node.typeParams, visitor)
    const newPrev = nodeVisitor(node.previous, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createETSTypeReferencePart(
            newName,
            newTypeParams,
            newPrev,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitScriptFunction(node: ScriptFunction, visitor: Visitor) {
    global.updateTracker.push()
    const newBody = nodeVisitor(node.body, visitor)
    const oldTypeParams = node.typeParams
    const newTypeParams = nodeVisitor(oldTypeParams, visitor)
    const newParams: readonly Expression[] = nodesVisitor(node.params, visitor)
    const newReturnTypeAnnotation = nodeVisitor(node.returnTypeAnnotation, visitor)
    const newId = nodeVisitor(node.id, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newTypeParams, oldTypeParams)) {
            const result = factory.createScriptFunction(
                newBody,
                newTypeParams,
                newParams,
                newReturnTypeAnnotation,
                node.hasReceiver,
                node.flags,
                node.modifierFlags,
                newId,
                newAnnotations,
                node.getSignaturePointer(),
                node.getPreferredReturnTypePointer(),
            )
            result.onUpdate(node)
            return result
        }
        node.setBody(newBody)
        node.setParams(newParams)
        node.setReturnTypeAnnotation(newReturnTypeAnnotation)
        if (newId) node.setIdent(newId)
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitMethodDefinition(node: MethodDefinition, visitor: Visitor) {
    global.updateTracker.push()
    const oldId = node.id
    const newId = nodeVisitor(oldId, visitor)
    const oldValue = node.value
    const newValue = nodeVisitor(oldValue, visitor)
    const newOverloads: readonly MethodDefinition[] = nodesVisitor(node.overloads, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newValue, node.value) || !isSameNativeObject(newId, oldId)) {
            const result = factory.createMethodDefinition(
                node.kind,
                newId,
                newValue,
                node.modifierFlags,
                node.isComputed,
                newOverloads,
            )
            result.onUpdate(node)
            return result
        }
        node.setOverloads(newOverloads)
        newOverloads.forEach(it => {
            it.setBaseOverloadMethod(node)
            it.parent = node
        })
    }
    return node
}

function visitArrowFunctionExpression(node: ArrowFunctionExpression, visitor: Visitor) {
    global.updateTracker.push()
    const oldFunction = node.function
    const newFunction = nodeVisitor(oldFunction, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newFunction, oldFunction)) {
            const result = factory.createArrowFunctionExpression(
                newFunction,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitFunctionDeclaration(node: FunctionDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const oldFunction = node.function
    const newFunction = nodeVisitor(oldFunction, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newFunction, oldFunction)) {
            const result = factory.createFunctionDeclaration(
                newFunction,
                newAnnotations,
                node.isAnonymous,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitBlockExpression(node: BlockExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newStatements: readonly Statement[] = nodesVisitor(node.statements, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createBlockExpression(
            newStatements,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitChainExpression(node: ChainExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newExpression = nodeVisitor(node.expression, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createChainExpression(
            newExpression,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitExpressionStatement(node: ExpressionStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newExpression = nodeVisitor(node.expression, visitor)
    if (global.updateTracker.check()) {
        node.setExpression(newExpression)
    }
    return node
}

function visitETSStructDeclaration(node: ETSStructDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const newDefinition = nodeVisitor(node.definition, visitor)
    if (global.updateTracker.check()) {
        node.setDefinition(newDefinition)
    }
    return node
}

function visitClassDeclaration(node: ClassDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const newDefinition = nodeVisitor(node.definition, visitor)
    if (global.updateTracker.check()) {
        node.setDefinition(newDefinition)
    }
    return node
}

function visitTSInterfaceBody(node: TSInterfaceBody, visitor: Visitor) {
    global.updateTracker.push()
    const newBody = nodesVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createTSInterfaceBody(
            newBody,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitClassDefinition(node: ClassDefinition, visitor: Visitor) {
    global.updateTracker.push()
    const newIdent = nodeVisitor(node.ident, visitor)
    const newTypeParams = nodeVisitor(node.typeParams, visitor)
    const oldSuperTypeParams = node.superTypeParams
    const newSuperTypeParams = nodeVisitor(oldSuperTypeParams, visitor)
    const oldImplements = node.implements
    const newImplements: readonly TSClassImplements[] = nodesVisitor(oldImplements, visitor)
    const newSuper = nodeVisitor(node.super, visitor)
    const newBody = nodesVisitor(node.body, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(oldSuperTypeParams, newSuperTypeParams) || !isSameNativeObject(newImplements, oldImplements)) {
            const result = factory.createClassDefinition(
                newIdent,
                newTypeParams,
                newSuperTypeParams,
                newImplements,
                undefined, /* can not pass node.ctor here because of mismatching types */
                newSuper,
                newBody,
                node.modifiers,
                node.modifierFlags,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setIdent(newIdent)
        node.setTypeParams(newTypeParams)
        node.setSuper(newSuper)
        node.setBody(newBody)
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitETSParameterExpression(node: ETSParameterExpression, visitor: Visitor) {
    if (node.isRestParameter) {
        /** there is no RestParameter node at .idl */
        return node
    }
    global.updateTracker.push()
    const newIdent = nodeVisitor(node.ident, visitor)
    const newInit = nodeVisitor(node.initializer, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        node.setIdent(newIdent)
        node.setInitializer(newInit)
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitSwitchStatement(node: SwitchStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newDiscriminant = nodeVisitor(node.discriminant, visitor)
    const oldCases = node.cases
    const newCases: readonly SwitchCaseStatement[] = nodesVisitor(oldCases, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newCases, oldCases)) {
            const result = factory.createSwitchStatement(
                newDiscriminant,
                newCases,
            )
            result.onUpdate(node)
            return result
        }
        node.setDiscriminant(newDiscriminant)
    }
    return node
}

function visitSwitchCaseStatement(node: SwitchCaseStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newTest = nodeVisitor(node.test, visitor)
    const oldConsequent = node.consequent
    const newConsequent: readonly Statement[] = nodesVisitor(oldConsequent, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newConsequent, oldConsequent)) {
            const result = factory.createSwitchCaseStatement(
                newTest,
                newConsequent,
            )
            result.onUpdate(node)
            return result
        }
        node.setTest(newTest)
    }
    return node
}

function visitTSInterfaceDeclaration(node: TSInterfaceDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const newExtends: readonly TSInterfaceHeritage[] = nodesVisitor(node.extends, visitor)
    const newIdent = nodeVisitor(node.id, visitor)
    const newTypeParams = nodeVisitor(node.typeParams, visitor)
    const newBody = nodeVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createInterfaceDeclaration(
            newExtends,
            newIdent,
            newTypeParams,
            newBody,
            node.isStatic,
            node.isFromExternal,
            node.modifierFlags,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitIfStatement(node: IfStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newTest = nodeVisitor(node.test, visitor)
    const oldConsequent = node.consequent
    const newConsequent = nodeVisitor(oldConsequent, visitor)
    const newAlternate = nodeVisitor(node.alternate, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newConsequent, oldConsequent)) {
            const result = factory.createIfStatement(
                newTest,
                newConsequent,
                newAlternate,
            )
            result.onUpdate(node)
            return result
        }
        node.setTest(newTest)
        if (newTest) newTest.parent = node
        node.setAlternate(newAlternate)
    }
    return node
}

function visitConditionalExpression(node: ConditionalExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newTest = nodeVisitor(node.test, visitor)
    const newConsequent = nodeVisitor(node.consequent, visitor)
    const newAlternate = nodeVisitor(node.alternate, visitor)
    if (global.updateTracker.check()) {
        node.setTest(newTest)
        node.setConsequent(newConsequent)
        node.setAlternate(newAlternate)
    }
    return node
}

function visitVariableDeclararion(node: VariableDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const oldDeclarators = node.declarators
    const newDeclarators: readonly VariableDeclarator[] = nodesVisitor(oldDeclarators, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newDeclarators, oldDeclarators)) {
            const result = factory.createVariableDeclaration(
                node.kind,
                newDeclarators,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitVariableDeclarator(node: VariableDeclarator, visitor: Visitor) {
    global.updateTracker.push()
    const oldId = node.id
    const newId = nodeVisitor(oldId, visitor)
    const newInit = nodeVisitor(node.init, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newId, oldId)) {
            const result = factory.createVariableDeclarator(
                node.flag,
                newId,
                newInit,
            )
            result.onUpdate(node)
            return result
        }
        node.setInit(newInit)
    }
    return node
}

function visitReturnStatement(node: ReturnStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newArgument = nodeVisitor(node.argument, visitor)
    if (global.updateTracker.check()) {
        node.setArgument(newArgument)
    }
    return node
}

function visitTSAsExpression(node: TSAsExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newExpr = nodeVisitor(node.expr, visitor)
    const oldTypeAnnotation = node.typeAnnotation
    const newTypeAnnotation = nodeVisitor(oldTypeAnnotation, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newTypeAnnotation, oldTypeAnnotation)) {
            const result = factory.createTSAsExpression(
                newExpr,
                newTypeAnnotation,
                node.isConst,
            )
            result.onUpdate(node)
            return result
        }
        node.setExpr(newExpr)
    }
    return node
}

function visitTemplateLiteral(node: TemplateLiteral, visitor: Visitor) {
    global.updateTracker.push()
    const newQuasis: readonly TemplateElement[] = nodesVisitor(node.quasis, visitor)
    const newExpression: readonly Expression[] = nodesVisitor(node.expressions, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createTemplateLiteral(
            newQuasis,
            newExpression,
            node.multilineString,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitTSTypeAliasDeclaration(node: TSTypeAliasDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const oldId = node.id
    const newId = nodeVisitor(oldId, visitor)
    const newTypeParams = nodeVisitor(node.typeParams, visitor)
    const oldTypeAnnotation = node.typeAnnotation
    const newTypeAnnotation = nodeVisitor(oldTypeAnnotation, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newId, oldId) || !isSameNativeObject(newTypeAnnotation, oldTypeAnnotation)) {
            const result = factory.createTSTypeAliasDeclaration(
                newId,
                newTypeParams,
                newTypeAnnotation,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
        node.setTypeParameters(newTypeParams)
    }
    return node
}

function visitTryStatement(node: TryStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newBlock = nodeVisitor(node.block, visitor)
    const newCatchClauses: readonly CatchClause[] = nodesVisitor(node.catchClauses, visitor)
    const newFinallyBlock = nodeVisitor(node.finallyBlock, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createTryStatement(
            newBlock,
            newCatchClauses,
            newFinallyBlock,
            [],
            [],
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitObjectExpression(node: ObjectExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newProperties: readonly Expression[] = nodesVisitor(node.properties, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createObjectExpression(
            newProperties,
            node.getPreferredTypePointer(),
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitFunctionExpression(node: FunctionExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newId = nodeVisitor(node.id, visitor)
    const newFunction = nodeVisitor(node.function, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createFunctionExpression(
            newId,
            newFunction,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitArrayExpression(node: ArrayExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newElements: readonly Expression[] = nodesVisitor(node.elements, visitor)
    if (global.updateTracker.check()) {
        node.setElements(newElements)
    }
    return node
}

function visitAssignmentExpression(node: AssignmentExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newLeft = nodeVisitor(node.left, visitor)
    const newRight = nodeVisitor(node.right, visitor)
    if (global.updateTracker.check()) {
        node.setLeft(newLeft)
        node.setRight(newRight)
    }
    return node
}

function visitETSTyple(node: ETSTuple, visitor: Visitor) {
    global.updateTracker.push()
    const newTypeAnnotationList: readonly TypeNode[] = nodesVisitor(node.tupleTypeAnnotationsList, visitor)
    if (global.updateTracker.check()) {
        node.setTypeAnnotationsList(newTypeAnnotationList)
    }
    return node
}

function visitETSUnionType(node: ETSUnionType, visitor: Visitor) {
    global.updateTracker.push()
    const oldTypes = node.types
    const newTypes: readonly TypeNode[] = nodesVisitor(oldTypes, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newTypes, oldTypes)) {
            const result = factory.createETSUnionType(
                newTypes,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitETSFunctionType(node: ETSFunctionType, visitor: Visitor) {
    global.updateTracker.push()
    const oldTypeParams = node.typeParams
    const newTypeParams = nodeVisitor(oldTypeParams, visitor)
    const oldParams = node.params
    const newParams: readonly Expression[] = nodesVisitor(oldParams, visitor)
    const oldReturnTypeAnnotation = node.returnType
    const newReturnTypeAnnotation = nodeVisitor(oldReturnTypeAnnotation, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newTypeParams, oldTypeParams)
            || !isSameNativeObject(newParams, oldParams)
            || !isSameNativeObject(newReturnTypeAnnotation, oldReturnTypeAnnotation)
        ) {
            const result = factory.createETSFunctionType(
                newTypeParams,
                newParams,
                newReturnTypeAnnotation,
                node.isExtensionFunction,
                node.flags,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitClassProperty(node: ClassProperty, visitor: Visitor) {
    global.updateTracker.push()
    const oldKey = node.key
    const newKey = nodeVisitor(oldKey, visitor)
    const newValue = nodeVisitor(node.value, visitor)
    const newTypeAnnotation = nodeVisitor(node.typeAnnotation, visitor)
    const newAnnotations: readonly AnnotationUsage[] = nodesVisitor(node.annotations, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newKey, oldKey)) {
            const result = factory.createClassProperty(
                newKey,
                newValue,
                newTypeAnnotation,
                node.modifierFlags,
                node.isComputed,
                newAnnotations,
            )
            result.onUpdate(node)
            return result
        }
        node.setValue(newValue)
        node.setTypeAnnotation(newTypeAnnotation)
        node.setAnnotations(newAnnotations)
    }
    return node
}

function visitProperty(node: Property, visitor: Visitor) {
    global.updateTracker.push()
    const newKey = nodeVisitor(node.key, visitor)
    const newValue = nodeVisitor(node.value, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createProperty(
            node.kind,
            newKey,
            newValue,
            node.isMethod,
            node.isComputed,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitBinaryExpression(node: BinaryExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newLeft = nodeVisitor(node.left, visitor)
    const newRight = nodeVisitor(node.right, visitor)
    if (global.updateTracker.check()) {
        node.setLeft(newLeft)
        node.setRight(newRight)
    }
    return node
}

function visitETSNewClassInstanceExpression(node: ETSNewClassInstanceExpression, visitor: Visitor) {
    global.updateTracker.push()
    const oldTypeRef = node.typeRef
    const newTypeRef = nodeVisitor(oldTypeRef, visitor)
    const newArguments: readonly Expression[] = nodesVisitor(node.arguments, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newTypeRef, oldTypeRef)) {
            const result = factory.createETSNewClassInstanceExpression(
                newTypeRef,
                newArguments,
            )
            result.onUpdate(node)
            return result
        }
        node.setArguments(newArguments)
        newArguments.forEach(it => it.parent = node)
    }
    return node
}

function visitWhileStatement(node: WhileStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newTest = nodeVisitor(node.test, visitor)
    const oldBody = node.body
    const newBody = nodeVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        if (!isSameNativeObject(newBody, oldBody)) {
            const result = factory.createWhileStatement(
                newTest,
                newBody,
            )
            result.onUpdate(node)
            return result
        }
        node.setTest(newTest)
    }
    return node
}

function visitDoWhileStatement(node: DoWhileStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newBody = nodeVisitor(node.body, visitor)
    const newTest = nodeVisitor(node.test, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createDoWhileStatement(
            newBody,
            newTest,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitForUpdateStatement(node: ForUpdateStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newInit = nodeVisitor(node.init, visitor)
    const newTest = nodeVisitor(node.test, visitor)
    const newUpdate = nodeVisitor(node.update, visitor)
    const newBody = nodeVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createForUpdateStatement(
            newInit,
            newTest,
            newUpdate,
            newBody,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitForInStatement(node: ForInStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newLeft = nodeVisitor(node.left, visitor)
    const newRight = nodeVisitor(node.right, visitor)
    const newBody = nodeVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createForInStatement(
            newLeft,
            newRight,
            newBody,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitForOfStatement(node: ForOfStatement, visitor: Visitor) {
    global.updateTracker.push()
    const newLeft = nodeVisitor(node.left, visitor)
    const newRight = nodeVisitor(node.right, visitor)
    const newBody = nodeVisitor(node.body, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createForOfStatement(
            newLeft,
            newRight,
            newBody,
            node.isAwait,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitETSImportDeclaration(node: ETSImportDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const newSource = nodeVisitor(node.source, visitor)
    const newSpecifiers = nodesVisitor(node.specifiers, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createETSImportDeclaration(
            newSource,
            newSpecifiers,
            Es2pandaImportKinds.IMPORT_KINDS_ALL,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitTSNonNullExpression(node: TSNonNullExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newExpr = nodeVisitor(node.expr, visitor)
    if (global.updateTracker.check()) {
        node.setExpr(newExpr)
        if (newExpr) newExpr.parent = node
    }
    return node
}

function visitUpdateExpression(node: UpdateExpression, visitor: Visitor) {
    global.updateTracker.push()
    const newArgument = nodeVisitor(node.argument, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createUpdateExpression(
            newArgument,
            node.operatorType,
            node.isPrefix,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitTSTypeParameterInstantiation(node: TSTypeParameterInstantiation, visitor: Visitor) {
    global.updateTracker.push()
    const newParams: readonly TypeNode[] = nodesVisitor(node.params, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createTSTypeParameterInstantiation(
            newParams,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitTSTypeParameterDeclaration(node: TSTypeParameterDeclaration, visitor: Visitor) {
    global.updateTracker.push()
    const newParams: readonly TSTypeParameter[] = nodesVisitor(node.params, visitor)
    if (global.updateTracker.check()) {
        const result = factory.createTSTypeParameterDeclaration(
            newParams,
            node.requiredParams,
        )
        result.onUpdate(node)
        return result
    }
    return node
}

function visitClassStaticBlock(node: ClassStaticBlock, visitor: Visitor) {
    global.updateTracker.push()
    const newId = nodeVisitor(node.id, visitor)
    const newFunction = nodeVisitor(node.function, visitor)
    if (global.updateTracker.check()) {
        const result = ClassStaticBlock.createClassStaticBlock(
            factory.createFunctionExpression(
                newId,
                newFunction,
            )
        )
        result.onUpdate(node)
        return result
    }
    return node
}

const visitsTable: (((node: any, visitor: Visitor) => any) | undefined)[] = []

export function initVisitsTable() {
    const length = Object.values(Es2pandaAstNodeType).length / 2
    visitsTable.push(...new Array(length))

    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_IDENTIFIER] = visitIdentifier
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION] = visitMemberExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE] = visitETSTypeReference
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE_PART] = visitETSTypeReferencePart
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE] = visitETSModule
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CALL_EXPRESSION] = visitCallExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION] = visitFunctionDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT] = visitBlockStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_EXPRESSION] = visitBlockExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CHAIN_EXPRESSION] = visitChainExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_EXPRESSION_STATEMENT] = visitExpressionStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_STRUCT_DECLARATION] = visitETSStructDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DECLARATION] = visitClassDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DEFINITION] = visitClassDefinition
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_METHOD_DEFINITION] = visitMethodDefinition
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION] = visitScriptFunction
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PARAMETER_EXPRESSION] = visitETSParameterExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_STATEMENT] = visitSwitchStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_CASE_STATEMENT] = visitSwitchCaseStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERFACE_DECLARATION] = visitTSInterfaceDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_INTERFACE_BODY] = visitTSInterfaceBody
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_IF_STATEMENT] = visitIfStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CONDITIONAL_EXPRESSION] = visitConditionalExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION] = visitVariableDeclararion
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATOR] = visitVariableDeclarator
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ARROW_FUNCTION_EXPRESSION] = visitArrowFunctionExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_RETURN_STATEMENT] = visitReturnStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_AS_EXPRESSION] = visitTSAsExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TEMPLATE_LITERAL] = visitTemplateLiteral
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_ALIAS_DECLARATION] = visitTSTypeAliasDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TRY_STATEMENT] = visitTryStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_OBJECT_EXPRESSION] = visitObjectExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_EXPRESSION] = visitFunctionExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ARRAY_EXPRESSION] = visitArrayExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ASSIGNMENT_EXPRESSION] = visitAssignmentExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TUPLE] = visitETSTyple
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_UNION_TYPE] = visitETSUnionType
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_FUNCTION_TYPE] = visitETSFunctionType
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_PROPERTY] = visitClassProperty
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_PROPERTY] = visitProperty
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_BINARY_EXPRESSION] = visitBinaryExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_NEW_CLASS_INSTANCE_EXPRESSION] = visitETSNewClassInstanceExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_WHILE_STATEMENT] = visitWhileStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_DO_WHILE_STATEMENT] = visitDoWhileStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_FOR_UPDATE_STATEMENT] = visitForUpdateStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_FOR_IN_STATEMENT] = visitForInStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_FOR_OF_STATEMENT] = visitForOfStatement
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION] = visitETSImportDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_NON_NULL_EXPRESSION] = visitTSNonNullExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_UPDATE_EXPRESSION] = visitUpdateExpression
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER_DECLARATION] = visitTSTypeParameterDeclaration
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER_INSTANTIATION] = visitTSTypeParameterInstantiation
    visitsTable[Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_STATIC_BLOCK] = visitClassStaticBlock
}

export function visitEachChild(
    node: AstNode,
    visitor: Visitor
): AstNode {
    global.profiler.nodeVisited()
    const visit = visitsTable[node.astNodeType]
    if (visit) {
        return visit(node, visitor)
    }
    return node
}

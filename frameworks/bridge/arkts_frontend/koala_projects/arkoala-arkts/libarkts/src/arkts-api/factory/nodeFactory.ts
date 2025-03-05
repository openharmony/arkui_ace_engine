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

import { updateNodeByNode } from "../utilities/private"
import {
    ArrowFunctionExpression,
    CallExpression,
    ClassDeclaration,
    ClassDefinition,
    ClassProperty,
    EtsImportDeclaration,
    ETSParameterExpression,
    EtsScript,
    ETSTypeReference,
    ETSTypeReferencePart,
    ExpressionStatement,
    FunctionDeclaration,
    FunctionExpression,
    Identifier,
    IfStatement,
    ImportSpecifier,
    MethodDefinition,
    NumberLiteral,
    ReturnStatement,
    ScriptFunction,
    StructDeclaration,
    TSTypeParameter,
    VariableDeclaration,
    VariableDeclarator
} from "../types"
import { MemberExpression } from "../to-be-generated/MemberExpression"
import { AstNode } from "../peers/AstNode"
import {
    AnnotationUsage,
    BinaryExpression,
    BlockStatement,
    ConditionalExpression,
    ETSFunctionType,
    ETSPrimitiveType,
    ETSUndefinedType,
    ETSUnionType,
    FunctionSignature,
    StringLiteral,
    SuperExpression,
    TSInterfaceBody,
    TSInterfaceDeclaration,
    TSTypeParameterDeclaration,
    TSTypeParameterInstantiation,
    UndefinedLiteral
} from "../../generated"


function compose<T extends AstNode, ARGS extends any[]>(
    create: (...args: ARGS) => T,
    update: (node: T, original: T) => T = updateNodeByNode
): (node: T, ...args: ARGS) => T {
    return (node: T, ...args: ARGS) => update(create(...args), node);
}

export const factory = {
    get createIdentifier() {
        return Identifier.create
    },
    get updateIdentifier() {
        return compose(Identifier.create)
    },
    get createCallExpression() {
        return CallExpression.create
    },
    get updateCallExpression() {
        return compose(CallExpression.create)
    },
    get createExpressionStatement() {
        return ExpressionStatement.create
    },
    get updateExpressionStatement() {
        return compose(ExpressionStatement.create)
    },
    get createMemberExpression() {
        return MemberExpression.create
    },
    get updateMemberExpression() {
        return compose(MemberExpression.create)
    },
    get createEtsScript() {
        return EtsScript.createFromSource
    },
    get updateEtsScript() {
        return EtsScript.updateByStatements
    },
    get createFunctionDeclaration() {
        return FunctionDeclaration.create
    },
    get updateFunctionDeclaration() {
        return compose(FunctionDeclaration.create)
    },
    get createBlock() {
        return BlockStatement.createBlockStatement
    },
    get updateBlock() {
        return compose(BlockStatement.createBlockStatement)
    },
    get createArrowFunction() {
        return ArrowFunctionExpression.create
    },
    get updateArrowFunction() {
        return compose(ArrowFunctionExpression.create)
    },
    get createScriptFunction() {
        return ScriptFunction.create
    },
    get updateScriptFunction() {
        return compose(ScriptFunction.create)
    },
    get createStringLiteral() {
        return StringLiteral.create1StringLiteral
    },
    get updateStringLiteral() {
        return compose(StringLiteral.createStringLiteral)
    },
    get create1StringLiteral() {
        return StringLiteral.create1StringLiteral
    },
    get update1StringLiteral() {
        return compose(StringLiteral.create1StringLiteral)
    },
    get createNumericLiteral() {
        return NumberLiteral.create
    },
    get updateNumericLiteral() {
        return compose(NumberLiteral.create)
    },
    get createParameterDeclaration() {
        return ETSParameterExpression.create
    },
    get updateParameterDeclaration() {
        return compose(ETSParameterExpression.create)
    },
    get createTypeParameter() {
        return TSTypeParameter.create
    },
    get updateTypeParameter() {
        return compose(TSTypeParameter.create)
    },
    get createTypeParameterDeclaration() {
        return TSTypeParameterDeclaration.createTSTypeParameterDeclaration
    },
    get updateTypeParameterDeclaration() {
        return compose(TSTypeParameterDeclaration.createTSTypeParameterDeclaration)
    },
    get createPrimitiveType() {
        return ETSPrimitiveType.createETSPrimitiveType
    },
    get updatePrimitiveType() {
        return compose(ETSPrimitiveType.createETSPrimitiveType)
    },
    get createTypeReference() {
        return ETSTypeReference.create
    },
    get updateTypeReference() {
        return compose(ETSTypeReference.create)
    },
    get createTypeReferenceFromId() {
        return ETSTypeReference.createFromId
    },
    get updateTypeReferenceFromId() {
        return compose(ETSTypeReference.createFromId)
    },
    get createTypeReferencePart() {
        return ETSTypeReferencePart.create
    },
    get updateTypeReferencePart() {
        return compose(ETSTypeReferencePart.create)
    },
    get createImportDeclaration() {
        return EtsImportDeclaration.create
    },
    get updateImportDeclaration() {
        return compose(EtsImportDeclaration.create)
    },
    get createImportSpecifier() {
        return ImportSpecifier.create
    },
    get updateImportSpecifier() {
        return compose(ImportSpecifier.create)
    },

// create ImportSource: ImportSource.create,
// update ImportSource: compose(ImportSource.create),

    get createVariableDeclaration() {
        return VariableDeclaration.create
    },
    get updateVariableDeclaration() {
        return compose(VariableDeclaration.create)
    },
    get createVariableDeclarator() {
        return VariableDeclarator.create
    },
    get updateVariableDeclarator() {
        return compose(VariableDeclarator.create)
    },
    get createUnionType() {
        return ETSUnionType.createETSUnionType
    },
    get updateUnionType() {
        return compose(ETSUnionType.createETSUnionType)
    },
    get createReturnStatement() {
        return ReturnStatement.create
    },
    get updateReturnStatement() {
        return compose(ReturnStatement.create)
    },
    get createIfStatement() {
        return IfStatement.create
    },
    get updateIfStatement() {
        return compose(IfStatement.create)
    },
    get createBinaryExpression() {
        return BinaryExpression.createBinaryExpression
    },
    get updateBinaryExpression() {
        return compose(BinaryExpression.createBinaryExpression)
    },
    get createClassDeclaration() {
        return ClassDeclaration.create
    },
    get updateClassDeclaration() {
        return compose(ClassDeclaration.create)
    },
    get createStructDeclaration() {
        return StructDeclaration.create
    },
    get updateStructDeclaration() {
        return compose(StructDeclaration.create)
    },
    get createClassDefinition() {
        return ClassDefinition.create
    },
    get updateClassDefinition() {
        return compose(ClassDefinition.create)
    },
    get createClassProperty() {
        return ClassProperty.create
    },
    get updateClassProperty() {
        return compose(ClassProperty.create)
    },
    get createFunctionType() {
        return ETSFunctionType.createETSFunctionType
    },
    get updateFunctionType() {
        return compose(ETSFunctionType.createETSFunctionType)
    },
    get createFunctionExpression() {
        return FunctionExpression.create
    },
    get updateFunctionExpression() {
        return compose(FunctionExpression.create)
    },
    get createMethodDefinition() {
        return MethodDefinition.create
    },
    get updateMethodDefinition() {
        return compose(MethodDefinition.create)
    },
    get createSuperExpression() {
        return SuperExpression.createSuperExpression
    },
    get updateSuperExpression() {
        return compose(SuperExpression.createSuperExpression)
    },
    get createTSTypeParameterInstantiation() {
        return TSTypeParameterInstantiation.createTSTypeParameterInstantiation
    },
    get updateTSTypeParameterInstantiation() {
        return compose(TSTypeParameterInstantiation.createTSTypeParameterInstantiation)
    },
    get createInterfaceDeclaration() {
        return TSInterfaceDeclaration.createTSInterfaceDeclaration
    },
    get updateInterfaceDeclaration() {
        return compose(TSInterfaceDeclaration.createTSInterfaceDeclaration)
    },
    get createInterfaceBody() {
        return TSInterfaceBody.createTSInterfaceBody
    },
    get updateInterfaceBody() {
        return compose(TSInterfaceBody.createTSInterfaceBody)
    },
    get createUndefinedLiteral() {
        return UndefinedLiteral.createUndefinedLiteral
    },
    get updateUndefinedLiteral() {
        return compose(UndefinedLiteral.createUndefinedLiteral)
    },
    get createAnnotationUsage() {
        return AnnotationUsage.createAnnotationUsage
    },
    get updateAnnotationUsageIr() {
        return compose(AnnotationUsage.createAnnotationUsage)
    },
    get createETSUndefinedType() {
        return ETSUndefinedType.createETSUndefinedType
    },
    get updateETSUndefinedType() {
        return compose(ETSUndefinedType.createETSUndefinedType)
    },
    get createFunctionSignature() {
        return FunctionSignature.createFunctionSignature
    },
    get createConditionalExpression() {
        return ConditionalExpression.createConditionalExpression
    },
    get updateConditionalExpression() {
        return compose(ConditionalExpression.createConditionalExpression)
    },
}

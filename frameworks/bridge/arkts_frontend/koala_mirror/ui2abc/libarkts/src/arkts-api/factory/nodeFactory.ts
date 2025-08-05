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
    BlockStatement,
    CallExpression,
    ClassDefinition,
    ClassProperty,
    ETSImportDeclaration,
    ETSModule,
    ETSStructDeclaration,
    ETSTuple,
    ETSTypeReferencePart,
    MemberExpression,
    ObjectExpression,
    TryStatement,
    TSTypeParameter,
    VariableDeclarator,
} from "../../generated"
import { factory as generatedFactory } from "../../generated/factory"
import { createScriptFunction, updateScriptFunction } from "../node-utilities/ScriptFunction"
import { updateCallExpression } from "../node-utilities/CallExpression"
import { createNumberLiteral, updateNumberLiteral } from "../node-utilities/NumberLiteral"
import { updateMemberExpression } from "../node-utilities/MemberExpression"
import { createETSParameterExpression, updateETSParameterExpression } from "../node-utilities/ETSParameterExpression"
import { updateTSTypeParameter } from "../node-utilities/TSTypeParameter"
import { updateETSTypeReferencePart } from "../node-utilities/TSTypeReferencePart"
import { updateETSImportDeclaration } from "../node-utilities/ETSImportDeclaration"
import { updateVariableDeclarator } from "../node-utilities/VariableDeclarator"
import { updateClassDefinition } from "../node-utilities/ClassDefinition"
import { updateETSStructDeclaration } from "../node-utilities/ETSStructDeclaration"
import { updateClassProperty } from "../node-utilities/ClassProperty"
import { createETSFunctionType, updateETSFunctionType } from "../node-utilities/ETSFunctionType"
import { createMethodDefinition, updateMethodDefinition } from "../node-utilities/MethodDefinition"
import { createTSInterfaceDeclaration, updateTSInterfaceDeclaration } from "../node-utilities/TSInterfaceDeclaration"
import { updateTryStatement } from "../node-utilities/TryStatement"
import { createAssignmentExpression, updateAssignmentExpression } from "../node-utilities/AssignmentExpression"
import { updateObjectExpression } from "../node-utilities/ObjectExpression"
import { updateETSTuple } from "../node-utilities/ETSTuple"
import { createArrayExpression, updateArrayExpression } from "../node-utilities/ArrayExpression"
import { updateBlockStatement } from "../node-utilities/BlockStatement"
import { updateETSModule } from "../node-utilities/ETSModule"

export const factory = {
    ...generatedFactory,

    createETSModule: ETSModule.createETSModule,
    updateETSModule,

    createCallExpression: CallExpression.createCallExpression,
    updateCallExpression,

    createMemberExpression: MemberExpression.createMemberExpression,
    updateMemberExpression,

    createScriptFunction,
    updateScriptFunction,

    createNumberLiteral,
    updateNumberLiteral,

    createETSParameterExpression,
    updateETSParameterExpression,

    createTypeParameter: TSTypeParameter.create1TSTypeParameter,
    updateTypeParameter: updateTSTypeParameter,

    createETSTypeReferencePart: ETSTypeReferencePart.createETSTypeReferencePart,
    updateETSTypeReferencePart,

    createETSImportDeclaration: ETSImportDeclaration.createETSImportDeclaration,
    updateETSImportDeclaration,

    createVariableDeclarator: VariableDeclarator.create1VariableDeclarator,
    updateVariableDeclarator,

    createETSStructDeclaration: ETSStructDeclaration.createETSStructDeclaration,
    updateETSStructDeclaration,

    createClassDefinition: ClassDefinition.createClassDefinition,
    updateClassDefinition,

    createClassProperty: ClassProperty.createClassProperty,
    updateClassProperty,

    createETSFunctionType,
    updateETSFunctionType,

    createMethodDefinition,
    updateMethodDefinition,

    createInterfaceDeclaration: createTSInterfaceDeclaration,
    updateInterfaceDeclaration: updateTSInterfaceDeclaration,

    createTryStatement: TryStatement.createTryStatement,
    updateTryStatement,

    createAssignmentExpression,
    updateAssignmentExpression,

    createObjectExpression: ObjectExpression.createObjectExpression,
    updateObjectExpression,

    createETSTuple: ETSTuple.create2ETSTuple,
    updateETSTuple,

    createArrayExpression,
    updateArrayExpression,

    createBlockStatement: BlockStatement.createBlockStatement,
    updateBlockStatement,

    updateInterfaceBody : generatedFactory.updateTSInterfaceBody,
}

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
    ClassDefinition,
    Expression,
    Identifier,
    isMethodDefinition,
    MethodDefinition,
    TSClassImplements,
    TSTypeParameterDeclaration,
    TSTypeParameterInstantiation
} from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"
import { AstNode } from "../peers/AstNode"
import { Es2pandaClassDefinitionModifiers, Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"
import { throwError } from "../../utils"

export function updateClassDefinition(
    original: ClassDefinition,
    ident: Identifier | undefined,
    typeParams: TSTypeParameterDeclaration | undefined,
    superTypeParams: TSTypeParameterInstantiation | undefined,
    _implements: readonly TSClassImplements[],
    ctor: MethodDefinition | undefined,
    superClass: Expression | undefined,
    body: readonly AstNode[],
    modifiers: Es2pandaClassDefinitionModifiers,
    flags: Es2pandaModifierFlags
): ClassDefinition {
    if (original.ctor !== undefined && !isMethodDefinition(original.ctor)) {
        throwError(`class definition constructor is not method definition: ${ctor?.dump()}`)
    }
    if (isSameNativeObject(ident, original.ident)
        && (isSameNativeObject(typeParams, original.typeParams))
        && (isSameNativeObject(superTypeParams, original.superTypeParams))
        && (isSameNativeObject(_implements, original.implements))
        && (isSameNativeObject(ctor, original.ctor))
        && (isSameNativeObject(superClass, original.super))
        && (isSameNativeObject(body, original.body))
        && (isSameNativeObject(modifiers, original.modifiers))
        && (isSameNativeObject(flags, original.modifierFlags))
    ) {
        return original
    }
    return updateNodeByNode(
        ClassDefinition.createClassDefinition(
            ident,
            typeParams,
            superTypeParams,
            _implements,
            ctor,
            superClass,
            body,
            modifiers,
            flags
        ).setAnnotations(original.annotations),
        original
    )
}

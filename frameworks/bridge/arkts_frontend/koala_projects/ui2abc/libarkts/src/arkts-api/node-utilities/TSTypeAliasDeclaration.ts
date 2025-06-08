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

import { Es2pandaModifierFlags } from ".."
import { AnnotationUsage, Identifier, TSTypeAliasDeclaration, TSTypeParameterDeclaration, TypeNode } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createTSTypeAliasDeclaration(
    id?: Identifier,
    typeParams?: TSTypeParameterDeclaration,
    typeAnnotation?: TypeNode,
    annotations?: readonly AnnotationUsage[],
    modifiers?: Es2pandaModifierFlags
): TSTypeAliasDeclaration {
    const res = TSTypeAliasDeclaration.createTSTypeAliasDeclaration(
        id,
        typeParams,
        typeAnnotation
    )
    if (annotations) {
        res.setAnnotations(annotations)
    }
    if (modifiers) {
        res.modifierFlags = modifiers
    }
    return res
}

export function updateTSTypeAliasDeclaration(
    original: TSTypeAliasDeclaration,
    id?: Identifier,
    typeParams?: TSTypeParameterDeclaration,
    typeAnnotation?: TypeNode,
    annotations?: readonly AnnotationUsage[],
    modifiers?: Es2pandaModifierFlags
): TSTypeAliasDeclaration {
    if (isSameNativeObject(id, original.id)
        && isSameNativeObject(typeParams, original.typeParams)
        && isSameNativeObject(typeAnnotation, original.typeAnnotation)
        && isSameNativeObject(annotations, original.annotations)
        && isSameNativeObject(modifiers, original.modifierFlags)
    ) {
        return original
    }
    return updateNodeByNode(
        createTSTypeAliasDeclaration(
            id,
            typeParams,
            typeAnnotation,
            annotations,
            modifiers
        ),
        original,
    )
}

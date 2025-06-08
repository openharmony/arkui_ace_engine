/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
    AnnotationUsage,
    Expression,
    FunctionSignature,
    Identifier,
    ScriptFunction,
    TSTypeParameterDeclaration,
    TypeNode
} from "../../generated"
import { AstNode } from "../peers/AstNode"
import { Es2pandaModifierFlags, Es2pandaScriptFunctionFlags } from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createScriptFunction(
    databody: AstNode | undefined,
    typeParams: TSTypeParameterDeclaration | undefined,
    params: readonly Expression[],
    returnTypeAnnotation: TypeNode | undefined,
    hasReceiver: boolean,
    datafuncFlags: Es2pandaScriptFunctionFlags,
    dataflags: Es2pandaModifierFlags,
    ident: Identifier | undefined,
    annotations: readonly AnnotationUsage[] | undefined,
) {
    const res = ScriptFunction.createScriptFunction(
        databody,
        FunctionSignature.createFunctionSignature(
            typeParams,
            params,
            returnTypeAnnotation,
            hasReceiver,
        ),
        datafuncFlags,
        dataflags
    )
    if (ident) {
        res.setIdent(ident)
    }
    if (annotations) {
        res.setAnnotations(annotations)
    }
    return res
}

export function updateScriptFunction(
    original: ScriptFunction,
    databody: AstNode | undefined,
    typeParams: TSTypeParameterDeclaration | undefined,
    params: readonly Expression[],
    returnTypeAnnotation: TypeNode | undefined,
    hasReceiver: boolean,
    datafuncFlags: Es2pandaScriptFunctionFlags,
    dataflags: Es2pandaModifierFlags,
    ident: Identifier | undefined,
    annotations: readonly AnnotationUsage[] | undefined,
) {
    if (isSameNativeObject(databody, original.body)
        && isSameNativeObject(typeParams, original.typeParams)
        && isSameNativeObject(params, original.params)
        && isSameNativeObject(returnTypeAnnotation, original.returnTypeAnnotation)
        && isSameNativeObject(hasReceiver, original.hasReceiver)
        && isSameNativeObject(datafuncFlags, original.flags)
        && isSameNativeObject(dataflags, original.modifierFlags)
        && isSameNativeObject(ident, original.id)
        && isSameNativeObject(annotations, original.annotations)
    ) {
        return original
    }
    return updateNodeByNode(
        createScriptFunction(
            databody,
            typeParams,
            params,
            returnTypeAnnotation,
            hasReceiver,
            datafuncFlags,
            dataflags,
            ident,
            annotations
        ),
        original
    )
}
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

import { AnnotationUsage, ETSFunctionType, Expression, FunctionSignature, TSTypeParameterDeclaration, TypeNode } from "../../generated"
import { Es2pandaScriptFunctionFlags } from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createETSFunctionType(
    typeParams: TSTypeParameterDeclaration | undefined,
    params: readonly Expression[],
    returnTypeAnnotation: TypeNode | undefined,
    hasReceiver: boolean,
    funcFlags: Es2pandaScriptFunctionFlags,
    annotations?: readonly AnnotationUsage[],
): ETSFunctionType {
    const res = ETSFunctionType.createETSFunctionType(
        FunctionSignature.createFunctionSignature(
            typeParams,
            params,
            returnTypeAnnotation,
            hasReceiver,
        ),
        funcFlags,
    )
    if (annotations) {
        res.setAnnotations(annotations)
    }
    return res
}

export function updateETSFunctionType(
    original: ETSFunctionType,
    typeParams: TSTypeParameterDeclaration | undefined,
    params: readonly Expression[],
    returnTypeAnnotation: TypeNode | undefined,
    hasReceiver: boolean,
    funcFlags: Es2pandaScriptFunctionFlags,
    annotations?: readonly AnnotationUsage[],
): ETSFunctionType {
    if (isSameNativeObject(typeParams, original.typeParams)
        && isSameNativeObject(params, original.params)
        && isSameNativeObject(returnTypeAnnotation, original.returnType)
        && isSameNativeObject(funcFlags, original.flags)
        && isSameNativeObject(annotations, original.annotations)
    ) {
        return original
    }
    return updateNodeByNode(
        createETSFunctionType(typeParams, params, returnTypeAnnotation, hasReceiver, funcFlags, annotations),
        original
    )
}

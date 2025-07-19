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

import { AnnotatedExpression, AnnotationUsage, ETSParameterExpression, Expression, TypeNode } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createETSParameterExpression(
    identOrSpread: AnnotatedExpression | undefined,
    isOptional: boolean,
    initExpr?: Expression,
    annotations?: readonly AnnotationUsage[]
): ETSParameterExpression {
    const res = ETSParameterExpression.createETSParameterExpression(identOrSpread, isOptional)
    if (initExpr) {
        res.setInitializer(initExpr)
    }
    if (annotations) {
        res.setAnnotations(annotations)
    }
    return res
}

export function updateETSParameterExpression(
    original: ETSParameterExpression,
    identOrSpread: AnnotatedExpression | undefined,
    isOptional: boolean,
    initExpr?: Expression,
    annotations?: readonly AnnotationUsage[],
): ETSParameterExpression {
    if ((isSameNativeObject(identOrSpread, original.ident) || isSameNativeObject(identOrSpread, original.restParameter))
        && isSameNativeObject(isOptional, original.isOptional)
        && isSameNativeObject(initExpr, original.initializer)
        && isSameNativeObject(annotations, original.annotations)
    ) {
        return original
    }
    return updateNodeByNode(
        createETSParameterExpression(identOrSpread, isOptional, initExpr, annotations),
        original
    )
}

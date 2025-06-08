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

import { AnnotationUsage, VariableDeclaration, VariableDeclarator } from "../../generated"
import { Es2pandaVariableDeclarationKind } from "../../generated/Es2pandaEnums"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createVariableDeclaration(
    kind: Es2pandaVariableDeclarationKind,
    declarators: readonly VariableDeclarator[],
    annotations?: readonly AnnotationUsage[]
): VariableDeclaration {
    const res = VariableDeclaration.createVariableDeclaration(
        kind,
        declarators
    )
    if (annotations) {
        res.setAnnotations(
            annotations
        )
    }
    return res
}

export function updateVariableDeclaration(
    original: VariableDeclaration,
    kind: Es2pandaVariableDeclarationKind,
    declarators: readonly VariableDeclarator[],
    annotations?: readonly AnnotationUsage[]
): VariableDeclaration {
    if (isSameNativeObject(kind, original.kind)
        && isSameNativeObject(declarators, original.declarators)
        && isSameNativeObject(annotations, original.annotations)
    ) {
        return original
    }
    return updateNodeByNode(
        createVariableDeclaration(kind, declarators, annotations),
        original
    )
}

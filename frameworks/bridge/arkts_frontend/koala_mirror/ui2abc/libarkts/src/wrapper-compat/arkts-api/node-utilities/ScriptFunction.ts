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

import { FunctionSignature, ScriptFunction } from '../../../generated';
import { isSameNativeObject } from '../../../arkts-api/peers/ArktsObject';
import { AstNode } from '../peers/AstNode';
import { updateThenAttach } from '../utilities/private';

export function updateScriptFunction(
    original: ScriptFunction,
    databody: AstNode | undefined,
    datasignature: FunctionSignature | undefined,
    datafuncFlags: number,
    dataflags: number
): ScriptFunction {
    if (
        isSameNativeObject(databody, original.body) &&
        isSameNativeObject(datasignature?.params, original.params) &&
        isSameNativeObject(datasignature?.typeParams, original.typeParams) &&
        isSameNativeObject(datasignature?.returnType, original.returnTypeAnnotation) &&
        isSameNativeObject(datasignature?.hasReceiver, original.hasReceiver) &&
        isSameNativeObject(datafuncFlags, original.flags) &&
        isSameNativeObject(dataflags, original.modifiers)
    ) {
        return original;
    }

    const update = updateThenAttach(
        ScriptFunction.updateScriptFunction,
        (node: ScriptFunction, original: ScriptFunction) => (!!original.id ? node.setIdent(original.id) : node),
        (node: ScriptFunction, original: ScriptFunction) => node.setAnnotations(original.annotations)
    );
    return update(original, databody, datasignature, datafuncFlags, dataflags);
}

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

import { ETSModule, Identifier, Program, Statement } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"
import { Es2pandaModuleFlag } from "../../generated/Es2pandaEnums"

export function updateETSModule(
    original: ETSModule,
    statementList: readonly Statement[],
    ident: Identifier | undefined,
    flag: Es2pandaModuleFlag,
    program?: Program,
) {
    if (isSameNativeObject(statementList, original.statements)
        && isSameNativeObject(ident, original.ident)
        && isSameNativeObject(flag, original.getNamespaceFlag())
        && isSameNativeObject(program, original.program)
    ) {
        return original
    }
    return updateNodeByNode(
        ETSModule.createETSModule(
            statementList,
            ident,
            flag,
            program,
        ),
        original,
    )
}

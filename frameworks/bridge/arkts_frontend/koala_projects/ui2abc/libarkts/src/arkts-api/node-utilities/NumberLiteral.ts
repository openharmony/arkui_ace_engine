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

import { global } from "../static/global"
import { NumberLiteral } from "../../generated"
import { isSameNativeObject } from "../peers/ArktsObject"
import { updateNodeByNode } from "../utilities/private"

export function createNumberLiteral(
    value: number
): NumberLiteral {
    return new NumberLiteral(
        global.es2panda._CreateNumberLiteral(
            global.context,
            value
        )
    )
}

export function updateNumberLiteral(
    original: NumberLiteral,
    value: number
): NumberLiteral {
    if (isSameNativeObject(value.toString(), original.str)) {
        return original
    }
    return updateNodeByNode(
        createNumberLiteral(value),
        original
    )
}

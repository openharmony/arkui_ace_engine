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

// HEAD:frameworks/bridge/arkts_frontend/koala_mirror/arkoala-arkts/arkui/src/ets/handwritten/ArkNavPathStack.ets
export class PathData {
    readonly name: string
    readonly param: Array<Object> = new Array<Object>()
    constructor(name: string, param: object | undefined) {
        this.name = name
        if (param !== undefined) {
            this.param.push(param!)
        }
    }
    static readonly EMPTY: PathData = new PathData("", undefined)
}
/*
import { NullLiteral } from '../../../generated';
import { attachModifiers, updateThenAttach } from '../utilities/private';

export function updateNullLiteral(original: NullLiteral): NullLiteral {
    /* TODO: no getter provided yet */

    const update = updateThenAttach(NullLiteral.updateNullLiteral, attachModifiers);
    return update(original);
}
>>> origin/OpenHarmony_feature_20250328:frameworks/bridge/arkts_frontend/koala_mirror/ui2abc/libarkts/src/wrapper-compat/arkts-api/node-utilities/NullLiteral.ts
*/
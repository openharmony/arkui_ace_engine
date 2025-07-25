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
    global,
    passNode,
    passNodeArray,
    unpackNonNullableNode,
    unpackNode,
    unpackNodeArray,
    assertValidPeer,
    AstNode,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { SourcePosition } from "./SourcePosition"
export class ValidationInfo extends ArktsObject {
    constructor(pointer: KNativePointer) {
        super(pointer)
    }
    static create1ValidationInfo(m: string, p?: SourcePosition): ValidationInfo {
        return new ValidationInfo(global.generatedEs2panda._CreateValidationInfo1(global.context, m, passNode(p)))
    }
    get fail(): boolean {
        return global.generatedEs2panda._ValidationInfoFailConst(global.context, this.peer)
    }
}
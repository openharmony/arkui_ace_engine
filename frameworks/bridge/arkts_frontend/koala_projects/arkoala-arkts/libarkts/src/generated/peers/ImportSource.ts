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
    Es2pandaAstNodeType,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { StringLiteral } from "./StringLiteral"
export class ImportSource extends ArktsObject {
     constructor(pointer: KNativePointer) {
        super(pointer)
        console.warn("Warning: stub node ImportSource")
    }
    static createImportSource(source: StringLiteral | undefined, resolvedSource: StringLiteral | undefined, hasDecl: boolean): ImportSource {
        return new ImportSource(global.generatedEs2panda._CreateImportSource(global.context, passNode(source), passNode(resolvedSource), hasDecl))
    }
    get source(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ImportSourceSourceConst(global.context, this.peer))
    }
    get resolvedSource(): StringLiteral | undefined {
        return unpackNode(global.generatedEs2panda._ImportSourceResolvedSourceConst(global.context, this.peer))
    }
    get hasDecl(): boolean {
        return global.generatedEs2panda._ImportSourceHasDeclConst(global.context, this.peer)
    }
}
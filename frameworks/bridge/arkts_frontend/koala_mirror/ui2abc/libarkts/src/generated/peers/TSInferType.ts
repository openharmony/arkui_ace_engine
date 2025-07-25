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

import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { TSTypeParameter } from "./TSTypeParameter"
import { TypeNode } from "./TypeNode"
export class TSInferType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 110)
        super(pointer)
    }
    static createTSInferType(typeParam?: TSTypeParameter): TSInferType {
        return new TSInferType(global.generatedEs2panda._CreateTSInferType(global.context, passNode(typeParam)))
    }
    static updateTSInferType(original?: TSInferType, typeParam?: TSTypeParameter): TSInferType {
        return new TSInferType(global.generatedEs2panda._UpdateTSInferType(global.context, passNode(original), passNode(typeParam)))
    }
    get typeParam(): TSTypeParameter | undefined {
        return unpackNode(global.generatedEs2panda._TSInferTypeTypeParamConst(global.context, this.peer))
    }
}
export function isTSInferType(node: object | undefined): node is TSInferType {
    return node instanceof TSInferType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INFER_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_INFER_TYPE, (peer: KNativePointer) => new TSInferType(peer))
}
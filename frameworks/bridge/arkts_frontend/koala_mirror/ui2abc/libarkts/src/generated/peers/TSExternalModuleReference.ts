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
import { Expression } from "./Expression"
export class TSExternalModuleReference extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 89)
        super(pointer)
    }
    static createTSExternalModuleReference(expr?: Expression): TSExternalModuleReference {
        return new TSExternalModuleReference(global.generatedEs2panda._CreateTSExternalModuleReference(global.context, passNode(expr)))
    }
    static updateTSExternalModuleReference(original?: TSExternalModuleReference, expr?: Expression): TSExternalModuleReference {
        return new TSExternalModuleReference(global.generatedEs2panda._UpdateTSExternalModuleReference(global.context, passNode(original), passNode(expr)))
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSExternalModuleReferenceExprConst(global.context, this.peer))
    }
}
export function isTSExternalModuleReference(node: object | undefined): node is TSExternalModuleReference {
    return node instanceof TSExternalModuleReference
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_EXTERNAL_MODULE_REFERENCE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_EXTERNAL_MODULE_REFERENCE, (peer: KNativePointer) => new TSExternalModuleReference(peer))
}
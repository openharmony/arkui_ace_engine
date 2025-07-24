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
import { Es2pandaMetaPropertyKind } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
export class MetaProperty extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 46)
        super(pointer)
    }
    static createMetaProperty(kind: Es2pandaMetaPropertyKind): MetaProperty {
        return new MetaProperty(global.generatedEs2panda._CreateMetaProperty(global.context, kind))
    }
    static updateMetaProperty(original: MetaProperty | undefined, kind: Es2pandaMetaPropertyKind): MetaProperty {
        return new MetaProperty(global.generatedEs2panda._UpdateMetaProperty(global.context, passNode(original), kind))
    }
    get kind(): Es2pandaMetaPropertyKind {
        return global.generatedEs2panda._MetaPropertyKindConst(global.context, this.peer)
    }
}
export function isMetaProperty(node: object | undefined): node is MetaProperty {
    return node instanceof MetaProperty
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_META_PROPERTY_EXPRESSION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_META_PROPERTY_EXPRESSION, (peer: KNativePointer) => new MetaProperty(peer))
}
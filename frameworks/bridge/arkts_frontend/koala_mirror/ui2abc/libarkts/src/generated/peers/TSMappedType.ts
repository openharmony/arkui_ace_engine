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
import { Es2pandaMappedOption } from "./../Es2pandaEnums"
import { TSTypeParameter } from "./TSTypeParameter"
import { TypeNode } from "./TypeNode"
export class TSMappedType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 114)
        super(pointer)
    }
    static createTSMappedType(typeParameter: TSTypeParameter | undefined, typeAnnotation: TypeNode | undefined, readonly_arg: Es2pandaMappedOption, optional_arg: Es2pandaMappedOption): TSMappedType {
        return new TSMappedType(global.generatedEs2panda._CreateTSMappedType(global.context, passNode(typeParameter), passNode(typeAnnotation), readonly_arg, optional_arg))
    }
    static updateTSMappedType(original: TSMappedType | undefined, typeParameter: TSTypeParameter | undefined, typeAnnotation: TypeNode | undefined, readonly_arg: Es2pandaMappedOption, optional_arg: Es2pandaMappedOption): TSMappedType {
        return new TSMappedType(global.generatedEs2panda._UpdateTSMappedType(global.context, passNode(original), passNode(typeParameter), passNode(typeAnnotation), readonly_arg, optional_arg))
    }
    get typeParameter(): TSTypeParameter | undefined {
        return unpackNode(global.generatedEs2panda._TSMappedTypeTypeParameter(global.context, this.peer))
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSMappedTypeTypeAnnotation(global.context, this.peer))
    }
    get readonly(): Es2pandaMappedOption {
        return global.generatedEs2panda._TSMappedTypeReadonly(global.context, this.peer)
    }
    get optional(): Es2pandaMappedOption {
        return global.generatedEs2panda._TSMappedTypeOptional(global.context, this.peer)
    }
}
export function isTSMappedType(node: object | undefined): node is TSMappedType {
    return node instanceof TSMappedType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_MAPPED_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_MAPPED_TYPE, (peer: KNativePointer) => new TSMappedType(peer))
}
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
import { Identifier } from "./Identifier"
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
import { TypeNode } from "./TypeNode"
export class ETSTypeReferencePart extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 73)
        super(pointer)
    }
    static createETSTypeReferencePart(name?: Expression, typeParams?: TSTypeParameterInstantiation, prev?: ETSTypeReferencePart): ETSTypeReferencePart {
        return new ETSTypeReferencePart(global.generatedEs2panda._CreateETSTypeReferencePart(global.context, passNode(name), passNode(typeParams), passNode(prev)))
    }
    static updateETSTypeReferencePart(original?: ETSTypeReferencePart, name?: Expression, typeParams?: TSTypeParameterInstantiation, prev?: ETSTypeReferencePart): ETSTypeReferencePart {
        return new ETSTypeReferencePart(global.generatedEs2panda._UpdateETSTypeReferencePart(global.context, passNode(original), passNode(name), passNode(typeParams), passNode(prev)))
    }
    static update1ETSTypeReferencePart(original?: ETSTypeReferencePart, name?: Expression): ETSTypeReferencePart {
        return new ETSTypeReferencePart(global.generatedEs2panda._UpdateETSTypeReferencePart1(global.context, passNode(original), passNode(name)))
    }
    get previous(): ETSTypeReferencePart | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePartPrevious(global.context, this.peer))
    }
    get name(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePartName(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterInstantiation | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePartTypeParams(global.context, this.peer))
    }
    get ident(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ETSTypeReferencePartGetIdent(global.context, this.peer))
    }
}
export function isETSTypeReferencePart(node: object | undefined): node is ETSTypeReferencePart {
    return node instanceof ETSTypeReferencePart
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE_PART)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_ETS_TYPE_REFERENCE_PART, (peer: KNativePointer) => new ETSTypeReferencePart(peer))
}
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
import { Identifier } from "./Identifier"
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
import { TypeNode } from "./TypeNode"
export class NamedType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 48)
        super(pointer)
    }
    static createNamedType(name?: Identifier): NamedType {
        return new NamedType(global.generatedEs2panda._CreateNamedType(global.context, passNode(name)))
    }
    static updateNamedType(original?: NamedType, name?: Identifier): NamedType {
        return new NamedType(global.generatedEs2panda._UpdateNamedType(global.context, passNode(original), passNode(name)))
    }
    get name(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._NamedTypeNameConst(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterInstantiation | undefined {
        return unpackNode(global.generatedEs2panda._NamedTypeTypeParamsConst(global.context, this.peer))
    }
    get isNullable(): boolean {
        return global.generatedEs2panda._NamedTypeIsNullableConst(global.context, this.peer)
    }
    /** @deprecated */
    setNullable(nullable: boolean): this {
        global.generatedEs2panda._NamedTypeSetNullable(global.context, this.peer, nullable)
        return this
    }
    /** @deprecated */
    setNext(next?: NamedType): this {
        global.generatedEs2panda._NamedTypeSetNext(global.context, this.peer, passNode(next))
        return this
    }
    /** @deprecated */
    setTypeParams(typeParams?: TSTypeParameterInstantiation): this {
        global.generatedEs2panda._NamedTypeSetTypeParams(global.context, this.peer, passNode(typeParams))
        return this
    }
}
export function isNamedType(node: object | undefined): node is NamedType {
    return node instanceof NamedType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_NAMED_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_NAMED_TYPE, (peer: KNativePointer) => new NamedType(peer))
}
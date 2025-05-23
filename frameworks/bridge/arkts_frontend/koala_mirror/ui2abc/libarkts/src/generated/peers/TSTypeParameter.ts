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

import { AnnotationUsage } from "./AnnotationUsage"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { Identifier } from "./Identifier"
import { TypeNode } from "./TypeNode"
export class TSTypeParameter extends Expression {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 118)
        super(pointer)
    }
    static create1TSTypeParameter(name: Identifier | undefined, constraint: TypeNode | undefined, defaultType: TypeNode | undefined, flags: Es2pandaModifierFlags): TSTypeParameter {
        return new TSTypeParameter(global.generatedEs2panda._CreateTSTypeParameter1(global.context, passNode(name), passNode(constraint), passNode(defaultType), flags))
    }
    static updateTSTypeParameter(original?: TSTypeParameter, name?: Identifier, constraint?: TypeNode, defaultType?: TypeNode): TSTypeParameter {
        return new TSTypeParameter(global.generatedEs2panda._UpdateTSTypeParameter(global.context, passNode(original), passNode(name), passNode(constraint), passNode(defaultType)))
    }
    static update1TSTypeParameter(original: TSTypeParameter | undefined, name: Identifier | undefined, constraint: TypeNode | undefined, defaultType: TypeNode | undefined, flags: Es2pandaModifierFlags): TSTypeParameter {
        return new TSTypeParameter(global.generatedEs2panda._UpdateTSTypeParameter1(global.context, passNode(original), passNode(name), passNode(constraint), passNode(defaultType), flags))
    }
    get name(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeParameterName(global.context, this.peer))
    }
    get constraint(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeParameterConstraint(global.context, this.peer))
    }
    /** @deprecated */
    setConstraint(constraint?: TypeNode): this {
        global.generatedEs2panda._TSTypeParameterSetConstraint(global.context, this.peer, passNode(constraint))
        return this
    }
    get defaultType(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeParameterDefaultTypeConst(global.context, this.peer))
    }
    /** @deprecated */
    setDefaultType(defaultType?: TypeNode): this {
        global.generatedEs2panda._TSTypeParameterSetDefaultType(global.context, this.peer, passNode(defaultType))
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._TSTypeParameterAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._TSTypeParameterSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isTSTypeParameter(node: object | undefined): node is TSTypeParameter {
    return node instanceof TSTypeParameter
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER, (peer: KNativePointer) => new TSTypeParameter(peer))
}
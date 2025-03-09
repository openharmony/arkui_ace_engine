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

import { Statement } from "./Statement"
import { Expression } from "./Expression"
import { Identifier } from "./Identifier"
export class AnnotationUsage extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 2)
        super(pointer)
        console.warn("Warning: stub node AnnotationUsage")
    }
    static createAnnotationUsage(expr?: Expression): AnnotationUsage {
        return new AnnotationUsage(global.generatedEs2panda._CreateAnnotationUsageIr(global.context, passNode(expr)))
    }
    static updateAnnotationUsage(original?: AnnotationUsage, expr?: Expression): AnnotationUsage {
        return new AnnotationUsage(global.generatedEs2panda._UpdateAnnotationUsageIr(global.context, passNode(original), passNode(expr)))
    }
    static create1AnnotationUsage(expr: Expression | undefined, properties: readonly AstNode[]): AnnotationUsage {
        return new AnnotationUsage(global.generatedEs2panda._CreateAnnotationUsageIr1(global.context, passNode(expr), passNodeArray(properties), properties.length))
    }
    static update1AnnotationUsage(original: AnnotationUsage | undefined, expr: Expression | undefined, properties: readonly AstNode[]): AnnotationUsage {
        return new AnnotationUsage(global.generatedEs2panda._UpdateAnnotationUsageIr1(global.context, passNode(original), passNode(expr), passNodeArray(properties), properties.length))
    }
    get expr(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._AnnotationUsageIrExpr(global.context, this.peer))
    }
    get properties(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._AnnotationUsageIrPropertiesConst(global.context, this.peer))
    }
    get propertiesPtr(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._AnnotationUsageIrPropertiesPtrConst(global.context, this.peer))
    }
    /** @deprecated */
    addProperty(property: AstNode): this {
        global.generatedEs2panda._AnnotationUsageIrAddProperty(global.context, this.peer, passNode(property))
        return this
    }
    /** @deprecated */
    setProperties(properties: readonly AstNode[]): this {
        global.generatedEs2panda._AnnotationUsageIrSetProperties(global.context, this.peer, passNodeArray(properties), properties.length)
        return this
    }
}
export function isAnnotationUsage(node: AstNode): node is AnnotationUsage {
    return node instanceof AnnotationUsage
}
if (!nodeByType.has(2)) {
    nodeByType.set(2, AnnotationUsage)
}
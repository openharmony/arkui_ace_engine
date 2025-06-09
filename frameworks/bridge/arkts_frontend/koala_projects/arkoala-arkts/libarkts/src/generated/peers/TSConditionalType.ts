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

import { TypeNode } from "./TypeNode"
import { Expression } from "./Expression"
export class TSConditionalType extends TypeNode {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 110)
        super(pointer)
        console.warn("Warning: stub node TSConditionalType")
    }
    static createTSConditionalType(checkType?: Expression, extendsType?: Expression, trueType?: Expression, falseType?: Expression): TSConditionalType {
        return new TSConditionalType(global.generatedEs2panda._CreateTSConditionalType(global.context, passNode(checkType), passNode(extendsType), passNode(trueType), passNode(falseType)))
    }
    static updateTSConditionalType(original?: TSConditionalType, checkType?: Expression, extendsType?: Expression, trueType?: Expression, falseType?: Expression): TSConditionalType {
        return new TSConditionalType(global.generatedEs2panda._UpdateTSConditionalType(global.context, passNode(original), passNode(checkType), passNode(extendsType), passNode(trueType), passNode(falseType)))
    }
    get checkType(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSConditionalTypeCheckTypeConst(global.context, this.peer))
    }
    get extendsType(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSConditionalTypeExtendsTypeConst(global.context, this.peer))
    }
    get trueType(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSConditionalTypeTrueTypeConst(global.context, this.peer))
    }
    get falseType(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSConditionalTypeFalseTypeConst(global.context, this.peer))
    }
}
export function isTSConditionalType(node: AstNode): node is TSConditionalType {
    return node instanceof TSConditionalType
}
if (!nodeByType.has(110)) {
    nodeByType.set(110, TSConditionalType)
}
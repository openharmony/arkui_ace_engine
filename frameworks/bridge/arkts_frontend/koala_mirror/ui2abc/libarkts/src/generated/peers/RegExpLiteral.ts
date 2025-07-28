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
import { Es2pandaRegExpFlags } from "./../Es2pandaEnums"
import { Literal } from "./Literal"
export class RegExpLiteral extends Literal {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 56)
        super(pointer)
    }
    static createRegExpLiteral(pattern: string, flags: Es2pandaRegExpFlags, flagsStr: string): RegExpLiteral {
        return new RegExpLiteral(global.generatedEs2panda._CreateRegExpLiteral(global.context, pattern, flags, flagsStr))
    }
    static updateRegExpLiteral(original: RegExpLiteral | undefined, pattern: string, flags: Es2pandaRegExpFlags, flagsStr: string): RegExpLiteral {
        return new RegExpLiteral(global.generatedEs2panda._UpdateRegExpLiteral(global.context, passNode(original), pattern, flags, flagsStr))
    }
    get pattern(): string {
        return unpackString(global.generatedEs2panda._RegExpLiteralPatternConst(global.context, this.peer))
    }
    get flags(): Es2pandaRegExpFlags {
        return global.generatedEs2panda._RegExpLiteralFlagsConst(global.context, this.peer)
    }
}
export function isRegExpLiteral(node: object | undefined): node is RegExpLiteral {
    return node instanceof RegExpLiteral
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_REGEXP_LITERAL)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_REGEXP_LITERAL, (peer: KNativePointer) => new RegExpLiteral(peer))
}
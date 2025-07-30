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
import { Statement } from "./Statement"
import { SwitchCaseStatement } from "./SwitchCaseStatement"
export class SwitchStatement extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 86)
        super(pointer)
    }
    static createSwitchStatement(discriminant: Expression | undefined, cases: readonly SwitchCaseStatement[]): SwitchStatement {
        return new SwitchStatement(global.generatedEs2panda._CreateSwitchStatement(global.context, passNode(discriminant), passNodeArray(cases), cases.length))
    }
    static updateSwitchStatement(original: SwitchStatement | undefined, discriminant: Expression | undefined, cases: readonly SwitchCaseStatement[]): SwitchStatement {
        return new SwitchStatement(global.generatedEs2panda._UpdateSwitchStatement(global.context, passNode(original), passNode(discriminant), passNodeArray(cases), cases.length))
    }
    get discriminant(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._SwitchStatementDiscriminant(global.context, this.peer))
    }
    /** @deprecated */
    setDiscriminant(discriminant?: Expression): this {
        global.generatedEs2panda._SwitchStatementSetDiscriminant(global.context, this.peer, passNode(discriminant))
        return this
    }
    get cases(): readonly SwitchCaseStatement[] {
        return unpackNodeArray(global.generatedEs2panda._SwitchStatementCases(global.context, this.peer))
    }
}
export function isSwitchStatement(node: object | undefined): node is SwitchStatement {
    return node instanceof SwitchStatement
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_STATEMENT)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_SWITCH_STATEMENT, (peer: KNativePointer) => new SwitchStatement(peer))
}
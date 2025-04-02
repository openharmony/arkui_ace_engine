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
import { SwitchCaseStatement } from "./SwitchCaseStatement"
export class SwitchStatement extends Statement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 85)
        super(pointer)
        console.warn("Warning: stub node SwitchStatement")
    }
    static createSwitchStatement(discriminant: Expression | undefined, cases: readonly SwitchCaseStatement[]): SwitchStatement {
        return new SwitchStatement(global.generatedEs2panda._CreateSwitchStatement(global.context, passNode(discriminant), passNodeArray(cases), cases.length))
    }
    static updateSwitchStatement(original: SwitchStatement | undefined, discriminant: Expression | undefined, cases: readonly SwitchCaseStatement[]): SwitchStatement {
        return new SwitchStatement(global.generatedEs2panda._UpdateSwitchStatement(global.context, passNode(original), passNode(discriminant), passNodeArray(cases), cases.length))
    }
    get discriminant(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._SwitchStatementDiscriminantConst(global.context, this.peer))
    }
    get cases(): readonly SwitchCaseStatement[] {
        return unpackNodeArray(global.generatedEs2panda._SwitchStatementCasesConst(global.context, this.peer))
    }
}
export function isSwitchStatement(node: AstNode): node is SwitchStatement {
    return node instanceof SwitchStatement
}
if (!nodeByType.has(85)) {
    nodeByType.set(85, SwitchStatement)
}
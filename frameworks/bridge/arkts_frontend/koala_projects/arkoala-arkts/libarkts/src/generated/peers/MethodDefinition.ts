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

import { ClassElement } from "./ClassElement"
import { Es2pandaMethodDefinitionKind } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { ScriptFunction } from "./ScriptFunction"
export class MethodDefinition extends ClassElement {
     constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 47)
        super(pointer)
        console.warn("Warning: stub node MethodDefinition")
    }
    static createMethodDefinition(kind: Es2pandaMethodDefinitionKind, key: Expression | undefined, value: Expression | undefined, modifiers: Es2pandaModifierFlags, isComputed: boolean): MethodDefinition {
        return new MethodDefinition(global.generatedEs2panda._CreateMethodDefinition(global.context, kind, passNode(key), passNode(value), modifiers, isComputed))
    }
    static updateMethodDefinition(original: MethodDefinition | undefined, kind: Es2pandaMethodDefinitionKind, key: Expression | undefined, value: Expression | undefined, modifiers: Es2pandaModifierFlags, isComputed: boolean): MethodDefinition {
        return new MethodDefinition(global.generatedEs2panda._UpdateMethodDefinition(global.context, passNode(original), kind, passNode(key), passNode(value), modifiers, isComputed))
    }
    get kind(): Es2pandaMethodDefinitionKind {
        return global.generatedEs2panda._MethodDefinitionKindConst(global.context, this.peer)
    }
    get isConstructor(): boolean {
        return global.generatedEs2panda._MethodDefinitionIsConstructorConst(global.context, this.peer)
    }
    get isExtensionMethod(): boolean {
        return global.generatedEs2panda._MethodDefinitionIsExtensionMethodConst(global.context, this.peer)
    }
    get overloads(): readonly MethodDefinition[] {
        return unpackNodeArray(global.generatedEs2panda._MethodDefinitionOverloadsConst(global.context, this.peer))
    }
    get baseOverloadMethod(): MethodDefinition | undefined {
        return unpackNode(global.generatedEs2panda._MethodDefinitionBaseOverloadMethodConst(global.context, this.peer))
    }
    get asyncPairMethod(): MethodDefinition | undefined {
        return unpackNode(global.generatedEs2panda._MethodDefinitionAsyncPairMethodConst(global.context, this.peer))
    }
    /** @deprecated */
    setOverloads(overloads: readonly MethodDefinition[]): this {
        global.generatedEs2panda._MethodDefinitionSetOverloads(global.context, this.peer, passNodeArray(overloads), overloads.length)
        return this
    }
    /** @deprecated */
    clearOverloads(): this {
        global.generatedEs2panda._MethodDefinitionClearOverloads(global.context, this.peer)
        return this
    }
    /** @deprecated */
    addOverload(overload: MethodDefinition): this {
        global.generatedEs2panda._MethodDefinitionAddOverload(global.context, this.peer, passNode(overload))
        return this
    }
    /** @deprecated */
    setBaseOverloadMethod(baseOverloadMethod: MethodDefinition): this {
        global.generatedEs2panda._MethodDefinitionSetBaseOverloadMethod(global.context, this.peer, passNode(baseOverloadMethod))
        return this
    }
    /** @deprecated */
    setAsyncPairMethod(method: MethodDefinition): this {
        global.generatedEs2panda._MethodDefinitionSetAsyncPairMethod(global.context, this.peer, passNode(method))
        return this
    }
}
export function isMethodDefinition(node: AstNode): node is MethodDefinition {
    return node instanceof MethodDefinition
}
if (!nodeByType.has(47)) {
    nodeByType.set(47, MethodDefinition)
}
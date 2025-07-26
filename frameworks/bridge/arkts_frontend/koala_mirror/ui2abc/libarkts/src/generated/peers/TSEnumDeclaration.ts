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

import { ClassDefinition } from "./ClassDefinition"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Identifier } from "./Identifier"
import { TypedStatement } from "./TypedStatement"
export class TSEnumDeclaration extends TypedStatement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 87)
        super(pointer)
    }
    static createTSEnumDeclaration(key: Identifier | undefined, members: readonly AstNode[], isConst: boolean, isStatic: boolean, isDeclare: boolean): TSEnumDeclaration {
        return new TSEnumDeclaration(global.generatedEs2panda._CreateTSEnumDeclaration(global.context, passNode(key), passNodeArray(members), members.length, isConst, isStatic, isDeclare))
    }
    static updateTSEnumDeclaration(original: TSEnumDeclaration | undefined, key: Identifier | undefined, members: readonly AstNode[], isConst: boolean, isStatic: boolean, isDeclare: boolean): TSEnumDeclaration {
        return new TSEnumDeclaration(global.generatedEs2panda._UpdateTSEnumDeclaration(global.context, passNode(original), passNode(key), passNodeArray(members), members.length, isConst, isStatic, isDeclare))
    }
    get key(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSEnumDeclarationKey(global.context, this.peer))
    }
    get members(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._TSEnumDeclarationMembersConst(global.context, this.peer))
    }
    get internalName(): string {
        return unpackString(global.generatedEs2panda._TSEnumDeclarationInternalNameConst(global.context, this.peer))
    }
    /** @deprecated */
    setInternalName(internalName: string): this {
        global.generatedEs2panda._TSEnumDeclarationSetInternalName(global.context, this.peer, internalName)
        return this
    }
    get boxedClass(): ClassDefinition | undefined {
        return unpackNode(global.generatedEs2panda._TSEnumDeclarationBoxedClassConst(global.context, this.peer))
    }
    /** @deprecated */
    setBoxedClass(wrapperClass?: ClassDefinition): this {
        global.generatedEs2panda._TSEnumDeclarationSetBoxedClass(global.context, this.peer, passNode(wrapperClass))
        return this
    }
    get isConst(): boolean {
        return global.generatedEs2panda._TSEnumDeclarationIsConstConst(global.context, this.peer)
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._TSEnumDeclarationDecoratorsConst(global.context, this.peer))
    }
}
export function isTSEnumDeclaration(node: object | undefined): node is TSEnumDeclaration {
    return node instanceof TSEnumDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ENUM_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_ENUM_DECLARATION, (peer: KNativePointer) => new TSEnumDeclaration(peer))
}
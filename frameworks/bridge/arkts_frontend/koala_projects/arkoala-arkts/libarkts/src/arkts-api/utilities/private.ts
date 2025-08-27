/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { global } from "../static/global"
import { isNumber, throwError } from "../../utils"
import {
    KInt,
    KNativePointer as KPtr,
    KNativePointer,
    nullptr,
    withString,
    withStringArray,
    withStringResult
} from "@koalaui/interop"
import { NativePtrDecoder } from "./nativePtrDecoder"
import { Es2pandaModifierFlags, Es2pandaScriptFunctionFlags } from "../../generated/Es2pandaEnums"
import { classByPeer } from "../class-by-peer"
import type { AstNode } from "../peers/AstNode"
import { ArktsObject } from "../peers/ArktsObject"
import { Es2pandaAstNodeType } from "../../Es2pandaEnums"

export const arrayOfNullptr = new BigUint64Array([nullptr])

export const allFlags =
    Object.values(Es2pandaModifierFlags)
        .filter(isNumber)
        .reduce(
            (prev, next) => (prev | next),
            0

        )

export function assertValidPeer(peer: KPtr, expectedKind: Es2pandaAstNodeType): void {
    if (peer === nullptr) {
        throwError(`invalid peer`)
    }
    const peerType = global.generatedEs2panda._AstNodeTypeConst(global.context, peer)
    if (peerType !== expectedKind) {
        throwError(`expected: ${Es2pandaAstNodeType[expectedKind]}, got: ${Es2pandaAstNodeType[peerType]}`)
    }
}

export function acceptNativeObjectArrayResult<T extends ArktsObject>(arrayObject: KNativePointer, factory: (instance: KNativePointer) => T): T[] {
    return new NativePtrDecoder().decode(arrayObject).map(factory);
}

export function unpackNonNullableNode<T extends AstNode>(peer: KNativePointer): T {
    if (peer === nullptr) {
        throwError('peer is NULLPTR (maybe you should use unpackNode)')
    }
    return classByPeer(peer) as T
}

export function unpackNode<T extends AstNode>(peer: KNativePointer): T | undefined {
    if (peer === nullptr) {
        return undefined
    }
    return classByPeer(peer) as T
}

export function passNode(node: ArktsObject | undefined): KNativePointer {
    return node?.peer ?? nullptr
}

// meaning unpackNonNullableNodeArray
export function unpackNodeArray<T extends AstNode>(nodesPtr: KNativePointer): T[] {
    if (nodesPtr === nullptr) {
        throwError('nodesPtr is NULLPTR (maybe you should use unpackNodeArray)')
    }
    return (new NativePtrDecoder())
        .decode(nodesPtr)
        .map((peer: KNativePointer) => unpackNonNullableNode(peer))
}

export function passNodeArray(nodes: readonly AstNode[] | undefined): BigUint64Array {
    return new BigUint64Array(
        nodes?.map(node => BigInt(node.peer)) ?? []
    )
}

export function unpackNonNullableObject<T extends ArktsObject>(type: { new (peer: KNativePointer): T }, peer: KNativePointer): T {
    if (peer === nullptr) {
        throwError('peer is NULLPTR (maybe you should use unpackObject)')
    }
    return new type(peer)
}

export function unpackObject<T extends ArktsObject>(type: { new (peer: KNativePointer): T }, peer: KNativePointer): T | undefined {
    if (peer === nullptr) {
        return undefined
    }
    return new type(peer)
}

export function unpackString(peer: KNativePointer): string {
    return withStringResult(peer) ?? throwError(`failed to unpack (peer shouldn't be NULLPTR)`)
}

export function passString(str: string | undefined): string {
    if (str === undefined) {
        return ""
    }
    return withString(str, (it: string) => it)
}

export function passStringArray(strings: readonly string[]): string[] {
    return withStringArray(strings, (it: string[]) => it)
}

export function passNodeWithNewModifiers<T extends AstNode>(node: T, modifiers: KInt): T {
    return (unpackNonNullableNode(node.peer) as T).updateModifiers(modifiers)
}

export function scriptFunctionHasBody(peer: KNativePointer): boolean {
    const flags = global.generatedEs2panda._ScriptFunctionFlagsConst(global.context, peer)
    return (flags & Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_EXTERNAL) === 0
        && (flags & Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_EXTERNAL_OVERLOAD) === 0
}

// TODO: remove this
// TODO: update scopes and other data
export function updatePeerByNode<T extends AstNode>(peer: KNativePointer, original: T | undefined): KNativePointer {
    if (peer === nullptr) {
        throwError('updatePeerByNode called on NULLPTR')
    }
    if (original === undefined) {
        return peer
    }
    global.generatedEs2panda._AstNodeSetOriginalNode(global.context, peer, original.peer)
    global.generatedEs2panda._AstNodeSetParent(global.context, peer, global.generatedEs2panda._AstNodeParent(global.context, original.peer))
    global.es2panda._AstNodeUpdateChildren(global.context, peer)
    global.generatedEs2panda._AstNodeClearModifier(global.context, peer, allFlags)
    global.generatedEs2panda._AstNodeAddModifier(global.context, peer, original.modifiers)
    global.es2panda._AstNodeUpdateChildren(global.context, peer)
    return peer
}

// TODO: update scopes and other data
export function updateNodeByNode<T extends AstNode>(node: T, original: AstNode): T {
    if (original.peer === nullptr) {
        throwError('update called on NULLPTR')
    }
    global.generatedEs2panda._AstNodeSetOriginalNode(global.context, node.peer, original.peer)
    global.generatedEs2panda._AstNodeSetParent(global.context, node.peer, global.generatedEs2panda._AstNodeParent(global.context, original.peer))
    global.es2panda._AstNodeUpdateChildren(global.context, node.peer)
    return node
}

export function nodeType(node: AstNode): Es2pandaAstNodeType {
    return global.generatedEs2panda._AstNodeTypeConst(global.context, passNode(node))
}

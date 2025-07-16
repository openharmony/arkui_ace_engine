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
    withStringArray
} from "@koalaui/interop"
import { NativePtrDecoder } from "./nativePtrDecoder"
import { Es2pandaAstNodeType, Es2pandaModifierFlags, Es2pandaScriptFunctionFlags } from "../../generated/Es2pandaEnums"
import { classByPeer } from "../class-by-peer"
import { AstNode } from "../peers/AstNode"
import { ArktsObject } from "../peers/ArktsObject"

export const arrayOfNullptr = new BigUint64Array([nullptr])

export const allFlags =
    Object.values(Es2pandaModifierFlags)
        .filter(isNumber)
        .reduce(
            (prev, next) => prev | next,
            0
        )

export function assertValidPeer(peer: KPtr, expectedKind: Es2pandaAstNodeType): void {
    if (peer === nullptr) {
        throwError(`invalid peer`)
    }

    if (global.validatePeerTypes) {
        const peerType = global.generatedEs2panda._AstNodeTypeConst(global.context, peer)
        if (peerType === Es2pandaAstNodeType.AST_NODE_TYPE_STRUCT_DECLARATION && expectedKind === Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_DECLARATION) {
            // Improve: Struct is a child class of Class
            return
        }
        if (peerType === Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION && expectedKind === Es2pandaAstNodeType.AST_NODE_TYPE_IMPORT_DECLARATION) {
            // Improve: ETSImportDeclaration is a child of a ImportDeclaration
            return
        }
        if (peerType === Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE && expectedKind === Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT) {
            // Improve: ETSModule is a child of a BlockStatement
            return
        }
        if (peerType !== expectedKind) {
            throwError(`expected: ${Es2pandaAstNodeType[expectedKind]}, got: ${Es2pandaAstNodeType[peerType]}`)
        }
    }
}

export function acceptNativeObjectArrayResult<T extends ArktsObject>(arrayObject: KNativePointer, factory: (instance: KNativePointer) => T): T[] {
    return new NativePtrDecoder().decode(arrayObject).map(factory);
}

export function unpackNonNullableNode<T extends AstNode>(peer: KNativePointer): T {
    if (peer === nullptr) {
        throwError('peer is NULLPTR (maybe you should use unpackNode)')
    }
    return classByPeer(peer)
}

export function unpackNode<T extends AstNode>(peer: KNativePointer): T | undefined {
    if (peer === nullptr) {
        return undefined
    }
    return classByPeer<T>(peer)
}

export function passNode(node: ArktsObject | undefined): KNativePointer {
    return node?.peer ?? nullptr
}

export function unpackNodeArray<T extends AstNode>(nodesPtr: KNativePointer): T[] {
    if (nodesPtr === nullptr) {
        throwError('nodesPtr is NULLPTR (maybe you should use unpackNodeArray)')
    }
    return new NativePtrDecoder()
        .decode(nodesPtr)
        .map((peer: KNativePointer) => unpackNonNullableNode(peer))
}

export function passNodeArray(nodes: readonly ArktsObject[] | undefined): BigUint64Array {
    return new BigUint64Array(
        nodes
            ?.filter(it => it.peer != undefined)
            ?.map(node => BigInt(node.peer))
        ?? []
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
    return global.interop._RawUtf8ToString(peer)
}

// Improve: use direct string arguments instead.
export function passString(str: string | undefined): string {
    return str ?? ""
}

// Improve: use direct string arguments instead.
export function passStringArray(strings: readonly string[]): string[] {
    return withStringArray(strings, (it: string[]) => it)
}

export function passNodeWithNewModifiers<T extends AstNode>(node: T, modifiers: KInt): T {
    return unpackNonNullableNode<T>(node.peer).updateModifiers(modifiers)
}

export function scriptFunctionHasBody(peer: KNativePointer): boolean {
    const flags = global.generatedEs2panda._ScriptFunctionFlagsConst(global.context, peer)
    return (flags & Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_EXTERNAL) === 0
        && (flags & Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_EXTERNAL_OVERLOAD) === 0
}

export function updateNodeByNode<T extends ArktsObject>(node: T, original: T): T {
    if (original.peer === nullptr) {
        throwError('update called on NULLPTR')
    }
    node.onUpdate(original)
    return node
}

export function nodeType(node: AstNode): Es2pandaAstNodeType {
    return global.generatedEs2panda._AstNodeTypeConst(global.context, passNode(node))
}


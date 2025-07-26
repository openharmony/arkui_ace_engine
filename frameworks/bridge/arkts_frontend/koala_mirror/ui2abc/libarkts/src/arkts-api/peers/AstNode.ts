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

import { isNullPtr, KInt, KNativePointer, nullptr } from "@koalaui/interop"
import { global } from "../static/global"
import { allFlags, unpackNodeArray, unpackNonNullableNode, unpackString } from "../utilities/private"
import { throwError } from "../../utils"
import { Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"
import { ArktsObject } from "./ArktsObject"
import { SourcePosition } from "./SourcePosition"
import { NodeCache } from "../node-cache"

export abstract class AstNode extends ArktsObject {
    protected constructor(peer: KNativePointer) {
        global.profiler.nodeCreated()
        if (isNullPtr(peer)) {
            throwError(`attempted to create AstNode from nullptr`)
        }
        super(peer)
        this.setChildrenParentPtr()
        NodeCache.addToCache(peer, this)
    }

    public get originalPeer(): KNativePointer {
        const result = global.generatedEs2panda._AstNodeOriginalNodeConst(global.context, this.peer)
        if (result === nullptr) {
            this.originalPeer = this.peer
            return this.peer
        }
        return result
    }

    public set originalPeer(peer: KNativePointer) {
        global.generatedEs2panda._AstNodeSetOriginalNode(global.context, this.peer, peer)
    }

    public getChildren(): readonly AstNode[] {
        return unpackNodeArray(global.es2panda._AstNodeChildren(global.context, this.peer))
    }

    public getSubtree(): readonly AstNode[] {
        return this.getChildren().reduce(
            (prev: readonly AstNode[], curr) => {
                return prev.concat(curr.getSubtree())
            },
            [this]
        )
    }

    public updateModifiers(modifierFlags: KInt | undefined): this {
        global.generatedEs2panda._AstNodeClearModifier(global.context, this.peer, allFlags)
        global.generatedEs2panda._AstNodeAddModifier(global.context, this.peer, modifierFlags ?? Es2pandaModifierFlags.MODIFIER_FLAGS_NONE)
        return this
    }

    public dump(indentation: number = 0): string {
        const children = this.getChildren()
            .map((it) => it.dump(indentation + 1))
        const msg =
            `${indentation}_`
            + ` <mods: ${this.modifierFlags}>`
            + this.dumpMessage()
        return "> " + " ".repeat(4 * indentation) + msg + "\n" + children.join("")
    }

    protected dumpMessage(): string {
        return ``
    }

    public dumpJson(): string {
        return unpackString(global.generatedEs2panda._AstNodeDumpJSONConst(global.context, this.peer))
    }

    public dumpSrc(): string {
        return unpackString(global.generatedEs2panda._AstNodeDumpEtsSrcConst(global.context, this.peer))
    }

    public dumpModifiers(): string {
        return unpackString(global.es2panda._AstNodeDumpModifiers(global.context, this.peer))
    }

    // public clone(): this {
    //     return unpackNonNullableNode(global.generatedEs2panda._AstNodeClone(global.context, this.peer, this.parent.peer));
    // }

    // public get parent(): AstNode {
    //     const parent = global.generatedEs2panda._AstNodeParent(global.context, this.peer)
    //     if (parent === nullptr) {
    //         throwError(`no parent`)
    //     }
    //     return unpackNonNullableNode(parent)
    // }

    // public set parent(node: AstNode) {
    //     global.generatedEs2panda._AstNodeSetParent(global.context, this.peer, node.peer)
    // }

    public clone(): this {
        const clonedNode = unpackNonNullableNode(
            global.generatedEs2panda._AstNodeClone(global.context, this.peer, this.parent?.peer ?? nullptr)
        );
        clonedNode.parent = undefined;
        return clonedNode as this;
    }
    
    public get parent(): AstNode | undefined {
        const parent = global.generatedEs2panda._AstNodeParent(global.context, this.peer);
        return unpackNonNullableNode(parent);
    }

    public set parent(node: AstNode | undefined) {
        global.generatedEs2panda._AstNodeSetParent(global.context, this.peer, node?.peer ?? nullptr);
    }

    public get modifierFlags(): Es2pandaModifierFlags {
        return global.generatedEs2panda._AstNodeModifiers(global.context, this.peer)
    }

    public set modifierFlags(flags: KInt | undefined) {
        global.generatedEs2panda._AstNodeClearModifier(global.context, this.peer, allFlags)
        global.generatedEs2panda._AstNodeAddModifier(global.context, this.peer, flags ?? Es2pandaModifierFlags.MODIFIER_FLAGS_NONE)
    }
    
    /** @deprecated Use {@link modifierFlags} instead */
    public get modifiers(): KInt {
        return this.modifierFlags
    }

    /** @deprecated Use {@link modifierFlags} instead */
    public set modifiers(flags: KInt | undefined) {
        this.modifierFlags = flags
    }

    public setChildrenParentPtr(): void {
        if (this.peer === nullptr) {
            throwError('setChildrenParentPtr called on NULLPTR')
        }
        global.es2panda._AstNodeSetChildrenParentPtr(global.context, this.peer)
    }

    public override onUpdate(original: AstNode): void {
        // Improve: Update modifiers only for specific AST nodes in the generated factory code
        this.modifierFlags = original.modifierFlags
        global.generatedEs2panda._AstNodeSetOriginalNode(global.context, this.peer, original.originalPeer)
        global.generatedEs2panda._AstNodeSetParent(global.context, this.peer, global.generatedEs2panda._AstNodeParent(global.context, original.peer))
        this.setChildrenParentPtr()
    }

    public get isExport(): boolean {
        return global.generatedEs2panda._AstNodeIsExportedConst(global.context, this.peer);
    }

    public get isDefaultExport(): boolean {
        return global.generatedEs2panda._AstNodeIsDefaultExportedConst(global.context, this.peer);
    }

    public get isStatic(): boolean {
        return global.generatedEs2panda._AstNodeIsStaticConst(global.context, this.peer);
    }
    
    public get startPosition(): SourcePosition {
        return new SourcePosition(global.generatedEs2panda._AstNodeStartConst(global.context, this.peer));
    }

    public set startPosition(start: SourcePosition) {
        global.generatedEs2panda._AstNodeSetStart(global.context, this.peer, start.peer);
    }

    public get endPosition(): SourcePosition {
        return new SourcePosition(global.generatedEs2panda._AstNodeEndConst(global.context, this.peer));
    }

    public set endPosition(end: SourcePosition) {
        global.generatedEs2panda._AstNodeSetEnd(global.context, this.peer, end.peer);
    }
}

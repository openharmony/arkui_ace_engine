/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { KoalaCallsiteKey, int32 } from '@koalaui/common'
import { KPointer } from "@koalaui/interop"
import { __context, __id, Disposable, IncrementalNode, NodeAttach } from '@koalaui/runtime';
import { ArkUIAniModule } from "arkui.ani"
import { PeerNode, PeerNodeType } from '../PeerNode';
import { IncrementalScope } from 'arkui.incremental.runtime.state';

class ConditionScopePeer extends PeerNode {
    public static create(): ConditionScopePeer {
        const peerId  = PeerNode.nextId();
        const _peerPtr = ArkUIAniModule._ConditionScopeNode_Construct(peerId);
        if (!_peerPtr) {
            throw new Error('create ConditionScope fail');
        }
        return new ConditionScopePeer(_peerPtr, peerId, 'ConditionScope');
    }

    private _branchesNode: ConditionBranchesNode = new ConditionBranchesNode();
    private scopes: Map<KoalaCallsiteKey, Disposable> = new Map<KoalaCallsiteKey, Disposable>();

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }

    get branchesNode(): ConditionBranchesNode {
        return this._branchesNode;
    }

    /* reuse and recycle object on RootPeers */
    override reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        if (reuseKey !== undefined) {
            return super.reuse(reuseKey, id);
        }

        const result = this.scopes.get(id);
        if (result !== undefined) {
            this.scopes.delete(id);
        }

        return result;
    }

    override recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        if (reuseKey !== undefined) {
            return super.recycle(reuseKey, child, id);
        }

        if (!this.scopes.has(id)) {
            this.scopes.set(id, child);
            return true;
        }

        return false;
    }

    private clearScopes(): void {
        for (const item of this.scopes.values()) {
            item.dispose();
        }
        this.scopes.clear();
    }

    override dispose() {
        this.clearScopes();
        super.dispose();
    }
}

class ConditionBranchesNode extends IncrementalNode {
    private _changed = false;
    private _branches = new Array<ConditionBranchNode>();

    public constructor() {
        super();

        this.onChildInserted = this.onChange;
        this.onChildRemoved = this.onChange;
    }

    public onChange(): void {
        this._changed = true
    }

    public get branches(): Array<ConditionBranchNode> {
        if (this._changed) {
            this._changed = false;
            this._branches = new Array<ConditionBranchNode>();
            for (let child = this.firstChild; child; child = child?.nextSibling) {
                this._branches.push(child as ConditionBranchNode);
            }
        }
        return this._branches;
    }

    public get changed(): boolean  {
        return this._changed;
    }
}

class ConditionBranchNode extends IncrementalNode {
    /** @memo */
    builder: () => void;

    constructor(
        /** @memo */
        builder: () => void
    ) {
        super();
        this.builder = builder;
        this.onChildInserted = (node: IncrementalNode) => {
            if (!node.isKind(PeerNodeType)) {
                return
            }
            const peer = node as PeerNode
            if (peer.reusable) {
                peer.onReuse(false)
            } else {
                peer.reusable = true
            } 
        }
        this.onChildRemoved = (node: IncrementalNode) => {
            if (!node.isKind(PeerNodeType)) {
                return
            }
            const peer = node as PeerNode
            if (!peer.disposed) {
                peer.onRecycle()
            }
        }
    }

    /**
     * Supports Reusable through redirecting requests to the parent node.
     */
    reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        if (this.parent) {
            return this.parent!.reuse(reuseKey, id)
        }
        return undefined;
    }

    recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        if (this.parent) {
            return this.parent!.recycle(reuseKey, child, id)
        }
        return false;
    }
}

function calcIntersection<T>(oldValue: Array<T>, newValue: Array<T>): Array<T> {
    const intersection = new Array<T>();

    let start = 0;
    for (let i = 0; i < oldValue.length; i++) {
        if (start >= newValue.length) {
            break;
        }

        for (let j = start; j < newValue.length; j++) {
            if (oldValue[i] === newValue[j]) {
                intersection.push(oldValue[i]);
                start = j + 1;
                break;
            }
        }
    }

    if (intersection.length === oldValue.length) {
        return oldValue;
    }

    if (intersection.length === newValue.length) {
        return newValue;
    }

    return intersection;
}

/** @memo:intrinsic */
function buildBranches(scope: IncrementalScope<void>, branches: Array<ConditionBranchNode>): void {
    const paramBranches = scope.param(0, branches);
    if (scope.unchanged) {
        scope.cached;
        return;
    }

    for (const branch of paramBranches.value) {
        branch.builder();
    }

    scope.recache();
}

/** @memo:intrinsic */
function buildContent(before: Array<ConditionBranchNode>, node: ConditionBranchesNode): void {
    const branchGroup = node.changed ? [calcIntersection(before, node.branches), node.branches] : [before];

    const scope = __context().scope<void>(__id(), 1);
    for (const branches of branchGroup) {
        buildBranches(scope, branches);
    }
}

/** @memo:intrinsic */
function emptyImplement(): void {}

/** @memo:intrinsic */
export function conditionScopeImpl(
    /** @memo */
    content: () => void
): void {
    NodeAttach(ConditionScopePeer.create, (peer: ConditionScopePeer) => {
        const node = peer.branchesNode;

        const before = node.branches;
        NodeAttach(() => node, content);
        buildContent(before, node);
    })
}

/** @memo:intrinsic */
export function conditionBranchImpl(
    /** @memo */
    content: () => void
): void {
    NodeAttach(() => new ConditionBranchNode(content), emptyImplement);
}

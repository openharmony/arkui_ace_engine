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

import { int32 } from '@koalaui/common'
import { KPointer } from "@koalaui/interop"
import { IncrementalNode, NodeAttach, InternalScope, remember, __context, __id } from '@koalaui/runtime';
import { ArkUIAniModule } from "arkui.ani"
import { PeerNode } from '../PeerNode';

class ConditionScopePeer extends PeerNode {
    public static create(): ConditionScopePeer {
        const peerId  = PeerNode.nextId();
        const _peerPtr  = ArkUIAniModule._ConditionScopeNode_Construct(peerId);
        if (!_peerPtr) {
            throw new Error('create ConditionScope fail');
        }
        return new ConditionScopePeer(_peerPtr, peerId, 'ConditionScope');
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }
}

class ConditionBranchesNode extends IncrementalNode {
    public static create(): ConditionBranchesNode {
        return new ConditionBranchesNode();
    }

    private changed = false;
    private _branches = new Array<ConditionBranchNode>();

    onChange(): void{
        this.changed = true
    }

    protected constructor() {
        super();

        this.onChildInserted = this.onChange;
        this.onChildRemoved = this.onChange;
    }

    public get branches(): Array<ConditionBranchNode> {
        if (this.changed) {
            this.changed = false;
            this._branches = new Array<ConditionBranchNode>();
            for (let child = this.firstChild; child; child = child?.nextSibling) {
                this._branches.push(child as ConditionBranchNode);
            }
        }
        return this._branches;
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
    }
}

function compareArray<T>(oldValue: Array<T>, newValue: Array<T>): boolean {
    if (oldValue === newValue) {
        return true;
    }

    if (oldValue.length !== newValue.length) {
        return false;
    }

    for (let i = 0; i < oldValue.length; i++) {
        if (oldValue[i] !== newValue[i]) {
            return false;
        }
    }

    return false;
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
function buildBranches(scope: InternalScope<void>, branches: Array<ConditionBranchNode>): void {
    const paramBranches = scope.param(0, branches, compareArray);
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
function buildContent(before: Array<ConditionBranchNode>, after: Array<ConditionBranchNode>): void {
    const same = compareArray(before, after);
    const intersection = same ? before : calcIntersection(before, after);

    const scope = __context().scope<void>(__id(), 1);
    buildBranches(scope, intersection);

    if (!same) {
        buildBranches(scope, after);
    }
}

/** @memo:intrinsic */
function emptyImplement(): void {}

/** @memo:intrinsic */
export function conditionScopeImpl(
    /** @memo */
    content: () => void
): void {
    NodeAttach(ConditionScopePeer.create, (_: ConditionScopePeer) => {
        const node = remember(ConditionBranchesNode.create);

        const before = node.branches;
        NodeAttach(() => node, content);
        const after = node.branches;

        buildContent(before, after);
    })
}

/** @memo:intrinsic */
export function conditionBranchImpl(
    /** @memo */
    content: () => void
): void {
    NodeAttach(() => new ConditionBranchNode(content), emptyImplement);
}

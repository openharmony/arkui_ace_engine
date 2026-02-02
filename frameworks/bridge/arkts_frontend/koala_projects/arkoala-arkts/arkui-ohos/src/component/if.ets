/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


// HANDWRITTEN, DO NOT REGENERATE!

import { KoalaCallsiteKey, int32 } from '@koalaui/common';
import { KPointer } from '@koalaui/interop';
import { __context, __id, Disposable, NodeAttach, remember } from '@koalaui/runtime';
import { ArkUIAniModule } from 'arkui.ani';
import { PeerNode } from '../PeerNode';

class IfElsePeer extends PeerNode {
    public static create(): IfElsePeer {
        const peerId  = PeerNode.nextId();
        const _peerPtr = ArkUIAniModule._ConditionScopeNode_Construct(peerId);
        if (!_peerPtr) {
            throw new Error('create IfElse fail');
        }
        return new IfElsePeer(_peerPtr, peerId, 'IfElse');
    }

    private _scopes: Map<KoalaCallsiteKey, Disposable> = new Map<KoalaCallsiteKey, Disposable>();

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }

    /* reuse and recycle object on RootPeers */
    override reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        if (reuseKey !== undefined) {
            return super.reuse(reuseKey, id);
        }

        const result = this._scopes.get(id);
        if (result !== undefined) {
            this._scopes.delete(id);
        }

        return result;
    }

    override recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        if (reuseKey !== undefined) {
            return super.recycle(reuseKey, child, id);
        }

        if (!this._scopes.has(id)) {
            this._scopes.set(id, child);
            return true;
        }

        return false;
    }

    public clearScopes(): void {
        for (const item of this._scopes.values()) {
            item.dispose();
        }
        this._scopes.clear();
    }

    override dispose() {
        this.clearScopes();
        super.dispose();
    }
}

export interface IfAttribute {
    setIfOptions(condition: boolean): this;

    ElseIf(
        condition: boolean,
        /** @memo */
        content: () => void
    ): this;

    Else(
        /** @memo */
        content: () => void
    ): void;

    applyAttributesFinish(): void {}
}

class BranchBuilder {
    /** @memo */
    content: () => void;

    constructor(
        /** @memo */
        content: () => void
    ) {
        this.content = content;
    }

    /** @memo:intrinsic */
    build(): void {
        this.content();
    }
}

class ArkIfElseComponent implements IfAttribute {
    /** @memo */
    private _content: () => void;
    private _peer?: IfElsePeer;

    private _lastBuilder?: BranchBuilder;
    private _builder?: BranchBuilder;

    private _lastBranchId: int32 = -1;
    private _branchId: int32 = -1;

    constructor(
        /** @memo */
        content: () => void,
        node: IfElsePeer
    ) {
        this._content = content;
        this._peer = node;
    }

    setIfOptions(condition: boolean): this {
        // save last branch
        this._lastBranchId = this._branchId;
        this._lastBuilder = this._builder;
        // reset current branch
        this._branchId = 0;
        this._builder = undefined;

        if (condition) {
            this.saveBuilder(this._content);
        }
        return this;
    }

    ElseIf(
        condition: boolean,
        /** @memo */
        content: () => void
    ): this {
        if (!this._builder) {
            this._branchId++;
            if (condition) {
                this.saveBuilder(content);
            }
        }
        return this;
    }

    Else(
        /** @memo */
        content: () => void
    ): void {
        if (!this._builder) {
            this._branchId++;
            this.saveBuilder(content);
        }
    }

    private saveBuilder(
        /** @memo */
        content: () => void
    ): void {
        if (this._lastBranchId === this._branchId && this._lastBuilder) {
            this._builder = this._lastBuilder;
        } else {
            this._builder = new BranchBuilder(content);
        }
    }

    get builder(): BranchBuilder | undefined {
        return this._builder;
    }

    get isBranchChanged(): boolean {
        if (this._lastBuilder === this._builder) {
            return false;
        }
        ArkUIAniModule._ConditionScope_Mark_Dirty(this._peer!.getPeerPtr());
        return true;
    }

    applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
    }
}

/** @memo:intrinsic */
function buildContent(component: ArkIfElseComponent): void {
    const group = component.isBranchChanged ?
        [undefined, component.builder] : [component.builder];

    const scope = __context().scope<void>(__id(), 1);
    for (const item of group) {
        const builder = scope.param(0, item);
        if (scope.unchanged) {
            scope.cached;
            continue;
        }

        builder.value?.build();
        scope.recache();
    }
}

/** @memo:intrinsic */
export function IfImpl(
    /** @memo */
    style: ((instance: IfAttribute) => void),
    /** @memo */
    content: () => void
): void {
    NodeAttach(IfElsePeer.create, (peer: IfElsePeer) => {
        const component = remember(() => new ArkIfElseComponent(content, peer));
        style(component);
        buildContent(component);
    });
}
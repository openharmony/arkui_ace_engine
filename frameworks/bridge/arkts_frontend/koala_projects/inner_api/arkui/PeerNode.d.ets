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

import { int32, KoalaCallsiteKey } from '@koalaui/common';
import { IncrementalNode } from '@koalaui.runtime.tree.IncrementalNode';
import { Disposable } from '@koalaui.runtime.states.Disposable';
import { NativePeerNode } from 'arkui/NativePeerNode';
import { int64 } from '@koalaui/compat';
import { RecordData } from "@ohos.base"

type pointer = int64

export const PeerNodeType = 11;
export const RootPeerType = 33;
export const LazyForEachType = 13;
export const RepeatType = 14;

export declare class PeerNode extends IncrementalNode {
    public readonly name: string;
    protected static currentId: int32;
    public peer: NativePeerNode;
    constructor(peerPtr: pointer, id: int32, name: string, flags: int32, derivedNodeType?: int32);
    public static generateRootPeer(): int32;
    // peer: NativePeerNode
    public static nextId(): int32;
    public getPeerPtr(): pointer;
    public setId(id: int32): void;
    public getId(): int32;
    public onReuse(sync: boolean, param?: RecordData): void;
    public onRecycle(needRecurs?: boolean): void;
    /* reuse and recycle object on RootPeers */
    public reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined;
    public recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean;
    public setOnRecycle(cb: () => void): void;
    public setOnReuse(cb: (param?: RecordData) => void): void;
    public static findPeerByNativeId(id: number): PeerNode | undefined;
    public setInsertMark(mark: pointer, upDirection: boolean): void;
    public applyAttributes(attrs: Object): void;
    public dispose(): void;
}

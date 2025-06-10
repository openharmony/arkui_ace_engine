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

import { ArkUINativeModule } from '#components';
import { KPointer } from '@koalaui/interop';
import { PeerNode } from '../PeerNode';
import { int32 } from '@koalaui/common';
import { NodeAttach } from '@koalaui/runtime';

export class CompatiblePeerNode extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, view: Object, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
        this.view = view;
    }
    public view: Object;
    public static create(_peerPtr: KPointer, view: Object, flags: int32 = 0) {
        const peerId = PeerNode.nextId();
        const _peer = new CompatiblePeerNode(_peerPtr, peerId, view, 'ComponentRoot', flags);
        return _peer;
    }
} 

export interface CompatibleComponentInfo {
    name: string,
    component: Object
}

/** @memo */
export function ArkUICompatible(
    init: () => CompatibleComponentInfo,
    update: (instance: Object) => void
): void {
    NodeAttach<CompatiblePeerNode>((): CompatiblePeerNode => {
        const ptr = ArkUINativeModule._CreateViewStackProcessor();
        const result = init();
        const realComponent = result.component;
        const nodePtr = ArkUINativeModule._PopViewStackProcessor();
        ArkUINativeModule._DeleteViewStackProcessor(ptr);
        return CompatiblePeerNode.create(nodePtr, realComponent);
    }, (node: CompatiblePeerNode) => {
        update(node.view);
    });
}

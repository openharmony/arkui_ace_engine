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

import { Es2pandaAstNodeType } from '../../generated/Es2pandaEnums';
import { throwError } from '../../utils';
import { global } from './static/global';
import { KNativePointer, nullptr } from '@koalaui/interop';
import { AstNode, UnsupportedNode } from './peers/AstNode';

export const nodeByType = new Map<Es2pandaAstNodeType, { new (peer: KNativePointer): AstNode }>([]);

const cache = new Map<KNativePointer, AstNode>();
export function clearNodeCache(): void {
    cache.clear();
}

function getOrPut(peer: KNativePointer, create: (peer: KNativePointer) => AstNode): AstNode {
    if (cache.has(peer)) {
        return cache.get(peer)!;
    }

    const newNode = create(peer);
    cache.set(peer, newNode);
    return newNode;
}

export function classByPeer<T extends AstNode>(peer: KNativePointer): T {
    if (peer === nullptr) {
        throwError('classByPeer: peer is NULLPTR');
    }
    const type = global.generatedEs2panda._AstNodeTypeConst(global.context, peer);
    const node = nodeByType.get(type) ?? UnsupportedNode;
    return getOrPut(peer, (peer) => new node(peer)) as T;
}

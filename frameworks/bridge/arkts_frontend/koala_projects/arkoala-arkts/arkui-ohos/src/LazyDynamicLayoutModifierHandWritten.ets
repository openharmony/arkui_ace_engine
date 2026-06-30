/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkLazyDynamicLayoutPeer, LazyDynamicLayoutAttribute } from '@ohos.arkui.components.ArkLazyDynamicLayout'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback } from './component/common'
import { LazyLayoutAlgorithm } from './LazyLayoutAlgorithm'
import { FrameNode } from 'arkui.FrameNode'
import { ArkUIAniModule } from 'arkui.ani'
import { UIContext } from '@ohos.arkui.UIContext'
import { UIContextUtil } from 'arkui/base/UIContextUtil'

export class LazyDynamicLayoutModifier extends CommonMethodModifier
    implements LazyDynamicLayoutAttribute, AttributeModifier<LazyDynamicLayoutAttribute> {
    private lazyDynamicLayoutAddr: ArrayBuffer = new ArrayBuffer(4096)
    private lazyDynamicLayoutFlagArray: Uint8Array = new Uint8Array(this.lazyDynamicLayoutAddr)

    constructor() {
        super();
        this.lazyDynamicLayoutFlagArray.fill(0);
    }

    public isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LazyDynamicLayoutAttribute): void { }
    applyPressedAttribute(instance: LazyDynamicLayoutAttribute): void { }
    applyFocusedAttribute(instance: LazyDynamicLayoutAttribute): void { }
    applyDisabledAttribute(instance: LazyDynamicLayoutAttribute): void { }
    applySelectedAttribute(instance: LazyDynamicLayoutAttribute): void { }
    applyHoveredAttribute(instance: LazyDynamicLayoutAttribute): void { }

    private algorithmValue?: LazyLayoutAlgorithm | undefined;
    private onVisibleIndexesChangeValue?: Callback<int[]> | undefined;

    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkLazyDynamicLayoutPeer;
        const flagArray = this.lazyDynamicLayoutFlagArray;
        this.applyModifierPatch0(peer, flagArray);
    }

    applyModifierPatch0(peer: ArkLazyDynamicLayoutPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    if (this.algorithmValue !== undefined) {
                        const nodeId: number = peer.getId();
                        const context: UIContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContext;
                        const frameNode = context.getFrameNodeByNodeId(nodeId);
                        if (frameNode) {
                            ArkUIAniModule._SetLazyDynamicLayoutCustomLayoutAlgorithm(
                                peer.peer.ptr,
                                this.algorithmValue!,
                                frameNode as FrameNode
                            );
                        }
                    }
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    ArkUIAniModule._SetLazyDynamicLayoutOnVisibleIndexesChange(
                        peer.peer.ptr,
                        this.onVisibleIndexesChangeValue as Callback<int[]> | undefined
                    );
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    ArkUIAniModule._SetLazyDynamicLayoutOnVisibleIndexesChange(
                        peer.peer.ptr,
                        undefined as Callback<int[]> | undefined
                    );
                }
            }
        }
    }

    mergeModifier(modifier: LazyDynamicLayoutModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier.lazyDynamicLayoutFlagArray;
        this.mergeModifier0(modifier, flagArray);
    }

    mergeModifier0(modifier: LazyDynamicLayoutModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    if (modifier.algorithmValue !== undefined) {
                        this.setLazyDynamicLayoutOptions(modifier.algorithmValue!);
                    }
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onVisibleIndexesChange(modifier.onVisibleIndexesChangeValue as Callback<int[]> | undefined)
                    break;
                }
                default: {
                    this.onVisibleIndexesChange(undefined as Callback<int[]> | undefined);
                }
            }
        }
    }

    setLazyDynamicLayoutOptions(algorithm: LazyLayoutAlgorithm): this {
        if ((this.lazyDynamicLayoutFlagArray[0] == 0) || true) {
            this.lazyDynamicLayoutFlagArray[0] = 1
            this.algorithmValue = algorithm
            this._state.fireChange()
        } else {
            this.lazyDynamicLayoutFlagArray[0] = 3
        }
        return this
    }

    onVisibleIndexesChange(callback: Callback<int[]> | undefined): this {
        if ((this.lazyDynamicLayoutFlagArray[1] == 0) || true) {
            this.lazyDynamicLayoutFlagArray[1] = 1
            this.onVisibleIndexesChangeValue = callback
            this._state.fireChange()
        } else {
            this.lazyDynamicLayoutFlagArray[1] = 3
        }
        return this
    }

    public attributeModifier(
        value: AttributeModifier<LazyDynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
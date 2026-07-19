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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from '@koalaui/interop'
import { int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from './arkui/ComponentBase'
import { PeerNode } from './arkui/PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './arkui/component/common'
import { AttributeModifier, hookSetLazyDynamicLayoutOptions, hookSetLazyDynamicLayoutOnVisibleIndexesChange, hookLazyDynamicLayoutAttributeModifierForHandWritten, AttributeUpdater } from '#handwritten'
import { CustomBuilder, CustomBuilderT } from './arkui/component/builder'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LazyDynamicLayoutModifier } from './arkui/LazyDynamicLayoutModifierHandWritten'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './arkui/CommonModifier'
import { LazyLayoutAlgorithm } from './arkui/LazyLayoutAlgorithm'
import { ArkUIAniModule } from 'arkui.ani'
 
export class ArkLazyDynamicLayoutPeer extends ArkCommonMethodPeer {
    lazyDynamicLayoutAttributeSet?: LazyDynamicLayoutModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyDynamicLayoutPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._LazyDynamicLayout_construct(peerId, flags)
        const _peer = new ArkLazyDynamicLayoutPeer(_peerPtr, peerId, 'LazyDynamicLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyDynamicLayoutOptionsAttribute(algorithm: object): void {
    }
}
export interface LazyDynamicLayoutAttribute extends CommonMethod {
    setLazyDynamicLayoutOptions(algorithm: LazyLayoutAlgorithm): this {
        throw new Error('Unimplemented method setLazyDynamicLayoutOptions')
    }
    onVisibleIndexesChange(callback: ((indexes: Array<int32>) => void) | undefined): this {
        throw new Error('Unimplemented method onVisibleIndexesChange')
    }
    attributeModifier(value: AttributeModifier<LazyDynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
 
export class ArkLazyDynamicLayoutComponent extends ArkCommonMethodComponent implements LazyDynamicLayoutAttribute {
    getPeer(): ArkLazyDynamicLayoutPeer {
        return (this.peer as ArkLazyDynamicLayoutPeer)
    }
    public setLazyDynamicLayoutOptions(algorithm: LazyLayoutAlgorithm): this {
        hookSetLazyDynamicLayoutOptions(this, algorithm)
        return this
    }
    public onVisibleIndexesChange(callback: ((indexes: Array<int32>) => void) | undefined): this {
        hookSetLazyDynamicLayoutOnVisibleIndexesChange(this, callback)
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyDynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLazyDynamicLayoutAttributeModifierForHandWritten(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
 
@memo
export function LazyDynamicLayoutImpl(
    @memo @memo_skip
    style: ((attributes: LazyDynamicLayoutAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyDynamicLayoutComponent>((): ArkLazyDynamicLayoutComponent => {
        return new ArkLazyDynamicLayoutComponent()
    })
    NodeAttach<ArkLazyDynamicLayoutPeer>((): ArkLazyDynamicLayoutPeer => ArkLazyDynamicLayoutPeer.create(receiver), (_: ArkLazyDynamicLayoutPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

@memo
export function LazyDynamicLayout(
    @memo @memo_skip
    style: ((attributes: LazyDynamicLayoutAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyDynamicLayoutComponent>((): ArkLazyDynamicLayoutComponent => {
        return new ArkLazyDynamicLayoutComponent()
    })
    NodeAttach<ArkLazyDynamicLayoutPeer>((): ArkLazyDynamicLayoutPeer => ArkLazyDynamicLayoutPeer.create(receiver), (_: ArkLazyDynamicLayoutPeer): void => {
        style?.(receiver)
        content_?.()
    })
}
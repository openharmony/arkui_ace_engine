/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { AttributeModifier, hookSetDynamicLayoutOptions, hookDynamicLayoutAttributeModifierForHandWritten, AttributeUpdater } from '#handwritten'
import { CustomBuilder } from './arkui/component/builder'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { DynamicLayoutModifier } from './arkui/DynamicLayoutModifierHandWritten'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './arkui/CommonModifier'
import { LayoutAlgorithm } from './arkui/LayoutAlgorithm'
import { ArkUIAniModule } from 'arkui.ani'
 
export class ArkDynamicLayoutPeer extends ArkCommonMethodPeer {
    dynamicLayoutAttributeSet?: DynamicLayoutModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDynamicLayoutPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._DynamicLayout_construct(peerId, flags)
        const _peer = new ArkDynamicLayoutPeer(_peerPtr, peerId, 'DynamicLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDynamicLayoutOptionsAttribute(algorithm: object): void {
    }
}
export interface DynamicLayoutAttribute extends CommonMethod {
    setDynamicLayoutOptions(algorithm: LayoutAlgorithm): this {
        throw new Error('Unimplemented method setDynamicLayoutOptions')
    }
    attributeModifier(value: AttributeModifier<DynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
 
export class ArkDynamicLayoutComponent extends ArkCommonMethodComponent implements DynamicLayoutAttribute {
    getPeer(): ArkDynamicLayoutPeer {
        return (this.peer as ArkDynamicLayoutPeer)
    }
    public setDynamicLayoutOptions(algorithm: LayoutAlgorithm): this {
        hookSetDynamicLayoutOptions(this, algorithm)
        return this
    }
    public attributeModifier(value: AttributeModifier<DynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookDynamicLayoutAttributeModifierForHandWritten(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
 
@memo
export function DynamicLayoutImpl(
    @memo @memo_skip
    style: ((attributes: DynamicLayoutAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkDynamicLayoutComponent>((): ArkDynamicLayoutComponent => {
        return new ArkDynamicLayoutComponent()
    })
    NodeAttach<ArkDynamicLayoutPeer>((): ArkDynamicLayoutPeer => ArkDynamicLayoutPeer.create(receiver), (_: ArkDynamicLayoutPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from '@koalaui/interop'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
import { int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { LengthMetrics as arkui_Graphics_LengthMetrics, LengthUnit } from 'arkui.Graphics'
import { Resource as global_resource_Resource } from 'global.resource'
import { initializers, AttributeModifier, hookLazyGridLayoutAttributeAttributeModifier, AttributeUpdater, hookLazyVGridLayoutAttributeModifier } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { CustomBuilder } from './builder'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
// instructive change start
import { LazyGridLayoutModifier } from './../LazyGridLayoutModifier'
// instructive change end
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { LazyVGridLayoutModifier } from './../LazyVGridLayoutModifier'
export class ArkLazyGridLayoutAttributePeer extends ArkCommonMethodPeer {
// instructive change start
    attributeSet?: LazyGridLayoutModifier;
// instructive change end
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyGridLayoutAttributePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_construct(peerId, flags)
        const _peer = new ArkLazyGridLayoutAttributePeer(_peerPtr, peerId, 'LazyGridLayoutAttribute', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowsGapAttribute(value: arkui_Graphics_LengthMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: arkui_Graphics_LengthMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkLazyVGridLayoutPeer extends ArkLazyGridLayoutAttributePeer {
    attributeSet?: LazyVGridLayoutModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLazyVGridLayoutPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._LazyVGridLayout_construct(peerId, flags)
        const _peer = new ArkLazyVGridLayoutPeer(_peerPtr, peerId, 'LazyVGridLayout', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyVGridLayoutOptionsAttribute(): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        ArkUIGeneratedNativeModule._LazyVGridLayoutInterface_setLazyVGridLayoutOptions(this.peer.ptr)
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyVGridLayoutAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface LazyGridLayoutAttribute extends CommonMethod {
    rowsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        throw new Error('Unimplemented method rowsGap')
    }
    columnsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        throw new Error('Unimplemented method columnsGap')
    }
    attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface LazyVGridLayoutAttribute extends LazyGridLayoutAttribute {
    setLazyVGridLayoutOptions(): this {
        throw new Error('Unimplemented method setLazyVGridLayoutOptions')
    }
    columnsTemplate(value: string | undefined): this {
        throw new Error('Unimplemented method columnsTemplate')
    }
    attributeModifier(value: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkLazyGridLayoutAttributeComponent extends ArkCommonMethodComponent implements LazyGridLayoutAttribute {
    getPeer(): ArkLazyGridLayoutAttributePeer {
        return (this.peer as ArkLazyGridLayoutAttributePeer)
    }
    public rowsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        const value_casted = value as (arkui_Graphics_LengthMetrics | undefined)
        this.getPeer()?.setRowsGapAttribute(value_casted)
        return this
    }
    public columnsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        const value_casted = value as (arkui_Graphics_LengthMetrics | undefined)
        this.getPeer()?.setColumnsGapAttribute(value_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLazyGridLayoutAttributeAttributeModifier(this, value);
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
export class ArkLazyVGridLayoutComponent extends ArkLazyGridLayoutAttributeComponent implements LazyVGridLayoutAttribute {
    getPeer(): ArkLazyVGridLayoutPeer {
        return (this.peer as ArkLazyVGridLayoutPeer)
    }
    public setLazyVGridLayoutOptions(): this {
        this.getPeer()?.setLazyVGridLayoutOptionsAttribute()
        this.applyOptionsFinish('LazyVGridLayoutAttribute');
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setColumnsTemplateAttribute(value_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyVGridLayoutAttribute> | AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLazyVGridLayoutAttributeModifier(this, value);
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
export function LazyVGridLayoutImpl(
    @memo @memo_skip
    style: ((attributes: LazyVGridLayoutAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkLazyVGridLayoutComponent>((): ArkLazyVGridLayoutComponent => {
        return new ArkLazyVGridLayoutComponent()
    })
    NodeAttach<ArkLazyVGridLayoutPeer>((): ArkLazyVGridLayoutPeer => ArkLazyVGridLayoutPeer.create(receiver), (_: ArkLazyVGridLayoutPeer): void => {
        style?.(receiver)
        content_?.()
    })
}


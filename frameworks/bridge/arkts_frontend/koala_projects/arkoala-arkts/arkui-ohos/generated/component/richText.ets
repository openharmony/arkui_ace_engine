/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookRichTextAttributeModifier, AttributeUpdater } from '#handwritten'
import { Resource as global_resource_Resource } from 'global.resource'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { RichTextModifier } from './../RichTextModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkRichTextPeer extends ArkCommonMethodPeer {
    attributeSet?: RichTextModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichText_construct(peerId, flags)
        const _peer  = new ArkRichTextPeer(_peerPtr, peerId, 'RichText', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichTextOptionsAttribute(content: string | global_resource_Resource): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (content instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const contentForIdx0  = content as string
            thisSerializer.writeString(contentForIdx0)
        } else if (content instanceof global_resource_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const contentForIdx1  = content as global_resource_Resource
            global_resource_Resource_serializer.write(thisSerializer, contentForIdx1)
        }
        ArkUIGeneratedNativeModule._RichTextInterface_setRichTextOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RichTextAttribute extends CommonMethod {
    setRichTextOptions(content: string | global_resource_Resource): this {
        throw new Error('Unimplemented method setRichTextOptions')
    }
    onStart(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onStart')
    }
    onComplete(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onComplete')
    }
    attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRichTextComponent extends ArkCommonMethodComponent implements RichTextAttribute {
    getPeer(): ArkRichTextPeer {
        return (this.peer as ArkRichTextPeer)
    }
    public setRichTextOptions(content: string | global_resource_Resource): this {
        if (this.checkPriority('setRichTextOptions')) {
            const content_casted = content as (string | global_resource_Resource)
            this.getPeer()?.setRichTextOptionsAttribute(content_casted)
            this.applyOptionsFinish('RichTextAttribute');
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority('onStart')) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: (() => void) | undefined): this {
        if (this.checkPriority('onComplete')) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRichTextAttributeModifier(this, value);
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
export function RichTextImpl(
    @memo @memo_skip
    style: ((attributes: RichTextAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRichTextComponent>((): ArkRichTextComponent => {
        return new ArkRichTextComponent()
    })
    NodeAttach<ArkRichTextPeer>((): ArkRichTextPeer => ArkRichTextPeer.create(receiver), (_: ArkRichTextPeer): void => {
        style?.(receiver)
        content_?.()
    })
}


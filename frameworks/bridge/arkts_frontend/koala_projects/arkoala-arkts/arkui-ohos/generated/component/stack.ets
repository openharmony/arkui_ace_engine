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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { Alignment } from './enums'
import { AttributeModifier, hookStackAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { StackModifier } from './../StackModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkStackPeer extends ArkCommonMethodPeer {
    attributeSet?: StackModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStackPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Stack_construct(peerId, flags)
        const _peer  = new ArkStackPeer(_peerPtr, peerId, 'Stack', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStackOptionsAttribute(options?: StackOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            StackOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StackInterface_setStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as Alignment)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StackAttribute_setAlignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PointLightStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StackAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StackOptions {
    alignContent?: Alignment;
}
export interface StackAttribute extends CommonMethod {
    setStackOptions(options?: StackOptions): this {
        throw new Error('Unimplemented method setStackOptions')
    }
    alignContent(value: Alignment | undefined): this {
        throw new Error('Unimplemented method alignContent')
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error('Unimplemented method pointLight')
    }
    attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkStackComponent extends ArkCommonMethodComponent implements StackAttribute {
    getPeer(): ArkStackPeer {
        return (this.peer as ArkStackPeer)
    }
    public setStackOptions(options?: StackOptions): this {
        if (this.checkPriority('setStackOptions')) {
            const options_casted = options as (StackOptions | undefined)
            this.getPeer()?.setStackOptionsAttribute(options_casted)
            this.applyOptionsFinish('StackAttribute');
            return this
        }
        return this
    }
    public alignContent(value: Alignment | undefined): this {
        if (this.checkPriority('alignContent')) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.setAlignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority('pointLight')) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookStackAttributeModifier(this, value);
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
export function StackImpl(
    @memo @memo_skip
    style: ((attributes: StackAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkStackComponent>((): ArkStackComponent => {
        return new ArkStackComponent()
    })
    NodeAttach<ArkStackPeer>((): ArkStackPeer => ArkStackPeer.create(receiver), (_: ArkStackPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class StackOptions_serializer {
    public static write(buffer: SerializerBase, value: StackOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAlignContent  = value.alignContent
        if (valueHolderForAlignContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignContentTmpValue  = (valueHolderForAlignContent as Alignment)
            valueSerializer.writeInt32(valueHolderForAlignContentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const alignContentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignContentTmpBuf : Alignment | undefined = undefined
        if ((alignContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignContentTmpBuf = Alignment.fromValue(valueDeserializer.readInt32())
        }
        const alignContentTmpResult : Alignment | undefined = alignContentTmpBuf
        let value : StackOptions = ({alignContent: alignContentTmpResult} as StackOptions)
        return value
    }
}

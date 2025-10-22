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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Alignment } from "./enums"
import { AttributeModifier, hookStackAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { StackModifier } from "./../StackModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStackPeer extends ArkCommonMethodPeer {
    attributeSet?: StackModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
}
export interface StackOptions {
    alignContent?: Alignment;
}
export interface StackAttribute extends CommonMethod {
    setStackOptions(options?: StackOptions): this {
        throw new Error("Unimplemented method setStackOptions")
    }
    alignContent(value: Alignment | undefined): this {
        throw new Error("Unimplemented method alignContent")
    }
    attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStackStyle extends ArkCommonMethodStyle implements StackAttribute {
    alignContent_value?: Alignment | undefined
    attributeModifier_value?: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined
    setStackOptions(options?: StackOptions): this {
        return this
    }
    alignContent(value: Alignment | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkStackComponent extends ArkCommonMethodComponent implements StackAttribute {
    getPeer(): ArkStackPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkStackPeer)
    }
    public setStackOptions(options?: StackOptions): this {
        if (this.checkPriority("setStackOptions")) {
            const options_casted = options as (StackOptions | undefined)
            this.getPeer()?.setStackOptionsAttribute(options_casted)
            this.applyOptionsFinish('StackAttribute');
            return this
        }
        return this
    }
    public alignContent(value: Alignment | undefined): this {
        if (this.checkPriority("alignContent")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.setAlignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookStackAttributeModifier(this, value);
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
    @memo
    style: ((attributes: StackAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStackComponent>((): ArkStackComponent => {
        return new ArkStackComponent()
    })
    NodeAttach<ArkStackPeer>((): ArkStackPeer => ArkStackPeer.create(receiver), (peer: ArkStackPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
        const alignContentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignContentTmpBuf : Alignment | undefined = undefined
        if ((alignContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignContentTmpBuf = Alignment.fromValue(valueDeserializer.readInt32())
        }
        const alignContentTmpResult : Alignment | undefined = alignContentTmpBuf
        let value : StackOptions = ({alignContent: alignContentTmpResult} as StackOptions)
        return value
    }
}

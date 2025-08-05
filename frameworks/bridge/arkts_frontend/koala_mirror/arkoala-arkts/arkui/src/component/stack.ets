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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Alignment } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(valueTmpValue))
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
    alignContent(value: Alignment | undefined): this {
        throw new Error("Unimplemented method alignContent")
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStackStyle extends ArkCommonMethodStyle implements StackAttribute {
    alignContent_value?: Alignment | undefined
    pointLight_value?: PointLightStyle | undefined
    attributeModifier_value?: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined
    public alignContent(value: Alignment | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkStackComponent extends ArkCommonMethodComponent implements StackAttribute {
    getPeer(): ArkStackPeer {
        return (this.peer as ArkStackPeer)
    }
    public setStackOptions(options?: StackOptions): this {
        if (this.checkPriority("setStackOptions")) {
            const options_casted = options as (StackOptions | undefined)
            this.getPeer()?.setStackOptionsAttribute(options_casted)
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
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Stack(
    @memo
    style: ((attributes: StackAttribute) => void) | undefined,
    options?: StackOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStackComponent>((): ArkStackComponent => {
        return new ArkStackComponent()
    })
    NodeAttach<ArkStackPeer>((): ArkStackPeer => ArkStackPeer.create(receiver), (_: ArkStackPeer): void => {
        receiver.setStackOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class StackModifier extends CommonMethodModifier implements StackAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignContent_0_0value?: Alignment | undefined
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    applyModifierPatch(peer: ArkStackPeer): void {
        super.applyModifierPatch(peer)
        if (this._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (this._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StackModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
        if (modifier._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
    }
    alignContent(value: Alignment | undefined): this {
        if (((this._alignContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignContent_0_0value = value
        } else
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class StackOptions_serializer {
    public static write(buffer: SerializerBase, value: StackOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAlignContent  = value.alignContent
        if (valueHolderForAlignContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignContentTmpValue  = (valueHolderForAlignContent as Alignment)
            valueSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(valueHolderForAlignContentTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const alignContentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignContentTmpBuf : Alignment | undefined
        if ((alignContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignContentTmpBuf = TypeChecker.Alignment_FromNumeric(valueDeserializer.readInt32())
        }
        const alignContentTmpResult : Alignment | undefined = alignContentTmpBuf
        let value : StackOptions = ({alignContent: alignContentTmpResult} as StackOptions)
        return value
    }
}

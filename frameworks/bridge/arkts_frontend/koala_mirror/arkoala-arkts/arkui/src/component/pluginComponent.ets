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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPluginComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPluginComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PluginComponent_construct(peerId, flags)
        const _peer  = new ArkPluginComponentPeer(_peerPtr, peerId, "PluginComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPluginComponentOptionsAttribute(options: PluginComponentOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PluginComponentOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._PluginComponentInterface_setPluginComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PluginComponentAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: PluginErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PluginComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PluginComponentTemplate {
    source: string;
    bundleName: string;
}
export interface PluginComponentOptions {
    template: PluginComponentTemplate;
    data: Object | undefined;
}
export interface PluginErrorData {
    errcode: number;
    msg: string;
}
export type PluginErrorCallback = (info: PluginErrorData) => void;
export interface PluginComponentAttribute extends CommonMethod {
    onComplete(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onComplete")
    }
    onError(value: PluginErrorCallback | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkPluginComponentStyle extends ArkCommonMethodStyle implements PluginComponentAttribute {
    onComplete_value?: VoidCallback | undefined
    onError_value?: PluginErrorCallback | undefined
    attributeModifier_value?: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public onComplete(value: VoidCallback | undefined): this {
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: PluginComponentAttribute): void {
        super.apply(target)
        if (this.onComplete_value !== undefined)
            target.onComplete(this.onComplete_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
    }
}

export class ArkPluginComponentComponent extends ArkCommonMethodComponent implements PluginComponentAttribute {
    getPeer(): ArkPluginComponentPeer {
        return (this.peer as ArkPluginComponentPeer)
    }
    public setPluginComponentOptions(options: PluginComponentOptions): this {
        if (this.checkPriority("setPluginComponentOptions")) {
            const options_casted = options as (PluginComponentOptions)
            this.getPeer()?.setPluginComponentOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public onComplete(value: VoidCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (PluginErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withPluginComponentStyle(receiver: PluginComponentAttribute, modifier: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkPluginComponentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("PluginComponent")
// export function PluginComponent(
//     options: PluginComponentOptions,
//     @memo
//     content_?: () => void,
// ): PluginComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function PluginComponent(
    @memo
    style: ((attributes: PluginComponentAttribute) => void) | undefined,
    options: PluginComponentOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPluginComponentComponent>((): ArkPluginComponentComponent => {
        return new ArkPluginComponentComponent()
    })
    NodeAttach<ArkPluginComponentPeer>((): ArkPluginComponentPeer => ArkPluginComponentPeer.create(receiver), (_: ArkPluginComponentPeer): void => {
        receiver.setPluginComponentOptions(options)
        style?.(receiver)
        withPluginComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkPluginComponentSet extends ArkCommonMethodSet implements PluginComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onComplete_flag?: boolean
    _onComplete0_value?: VoidCallback | undefined
    _onError_flag?: boolean
    _onError0_value?: PluginErrorCallback | undefined
    applyModifierPatch(component: PluginComponentAttribute): void {
        if (this._onComplete_flag)
            component.onComplete((this._onComplete0_value as VoidCallback | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as PluginErrorCallback | undefined))
    }
    public onComplete(value: VoidCallback | undefined): this {
        this._onComplete_flag = true
        this._onComplete0_value = value
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PluginComponentTemplate_serializer {
    public static write(buffer: SerializerBase, value: PluginComponentTemplate): void {
        let valueSerializer : SerializerBase = buffer
        const value_source  = value.source
        valueSerializer.writeString(value_source)
        const value_bundleName  = value.bundleName
        valueSerializer.writeString(value_bundleName)
    }
    public static read(buffer: DeserializerBase): PluginComponentTemplate {
        let valueDeserializer : DeserializerBase = buffer
        const source_result : string = (valueDeserializer.readString() as string)
        const bundleName_result : string = (valueDeserializer.readString() as string)
        let value : PluginComponentTemplate = ({source: source_result, bundleName: bundleName_result} as PluginComponentTemplate)
        return value
    }
}
export class PluginErrorData_serializer {
    public static write(buffer: SerializerBase, value: PluginErrorData): void {
        let valueSerializer : SerializerBase = buffer
        const value_errcode  = value.errcode
        valueSerializer.writeNumber(value_errcode)
        const value_msg  = value.msg
        valueSerializer.writeString(value_msg)
    }
    public static read(buffer: DeserializerBase): PluginErrorData {
        let valueDeserializer : DeserializerBase = buffer
        const errcode_result : number = (valueDeserializer.readNumber() as number)
        const msg_result : string = (valueDeserializer.readString() as string)
        let value : PluginErrorData = ({errcode: errcode_result, msg: msg_result} as PluginErrorData)
        return value
    }
}
export class PluginComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: PluginComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_template  = value.template
        PluginComponentTemplate_serializer.write(valueSerializer, value_template)
        const value_data  = value.data
        let value_data_type : int32 = RuntimeType.UNDEFINED
        value_data_type = runtimeType(value_data)
        valueSerializer.writeInt8((value_data_type).toChar())
        if ((value_data_type) != (RuntimeType.UNDEFINED)) {
            const value_data_value  = value_data!
            valueSerializer.holdAndWriteObject(value_data_value)
        }
    }
    public static read(buffer: DeserializerBase): PluginComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const template_result : PluginComponentTemplate = PluginComponentTemplate_serializer.read(valueDeserializer)
        const data_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let data_buf : Object | undefined
        if ((data_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            data_buf = (valueDeserializer.readObject() as object)
        }
        const data_result : Object | undefined = data_buf
        let value : PluginComponentOptions = ({template: template_result, data: data_result} as PluginComponentOptions)
        return value
    }
}

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
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFormLinkPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFormLinkPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormLink_construct(peerId, flags)
        const _peer  = new ArkFormLinkPeer(_peerPtr, peerId, "FormLink", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormLinkOptionsAttribute(options: FormLinkOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FormLinkOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._FormLinkInterface_setFormLinkOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface FormLinkOptions {
    action: string;
    moduleName?: string;
    bundleName?: string;
    abilityName?: string;
    uri?: string;
    params?: Object;
}
export interface FormLinkAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFormLinkStyle extends ArkCommonMethodStyle implements FormLinkAttribute {
    attributeModifier_value?: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: FormLinkAttribute): void {
        super.apply(target)
    }
}

export class ArkFormLinkComponent extends ArkCommonMethodComponent implements FormLinkAttribute {
    getPeer(): ArkFormLinkPeer {
        return (this.peer as ArkFormLinkPeer)
    }
    public setFormLinkOptions(options: FormLinkOptions): this {
        if (this.checkPriority("setFormLinkOptions")) {
            const options_casted = options as (FormLinkOptions)
            this.getPeer()?.setFormLinkOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withFormLinkStyle(receiver: FormLinkAttribute, modifier: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkFormLinkStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("FormLink")
// export function FormLink(
//     options: FormLinkOptions,
//     @memo
//     content_?: () => void,
// ): FormLinkAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function FormLink(
    @memo
    style: ((attributes: FormLinkAttribute) => void) | undefined,
    options: FormLinkOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFormLinkComponent>((): ArkFormLinkComponent => {
        return new ArkFormLinkComponent()
    })
    NodeAttach<ArkFormLinkPeer>((): ArkFormLinkPeer => ArkFormLinkPeer.create(receiver), (_: ArkFormLinkPeer): void => {
        receiver.setFormLinkOptions(options)
        style?.(receiver)
        withFormLinkStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkFormLinkSet extends ArkCommonMethodSet implements FormLinkAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: FormLinkAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FormLinkOptions_serializer {
    public static write(buffer: SerializerBase, value: FormLinkOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_action  = value.action
        valueSerializer.writeString(value_action)
        const value_moduleName  = value.moduleName
        let value_moduleName_type : int32 = RuntimeType.UNDEFINED
        value_moduleName_type = runtimeType(value_moduleName)
        valueSerializer.writeInt8((value_moduleName_type).toChar())
        if ((value_moduleName_type) != (RuntimeType.UNDEFINED)) {
            const value_moduleName_value  = value_moduleName!
            valueSerializer.writeString(value_moduleName_value)
        }
        const value_bundleName  = value.bundleName
        let value_bundleName_type : int32 = RuntimeType.UNDEFINED
        value_bundleName_type = runtimeType(value_bundleName)
        valueSerializer.writeInt8((value_bundleName_type).toChar())
        if ((value_bundleName_type) != (RuntimeType.UNDEFINED)) {
            const value_bundleName_value  = value_bundleName!
            valueSerializer.writeString(value_bundleName_value)
        }
        const value_abilityName  = value.abilityName
        let value_abilityName_type : int32 = RuntimeType.UNDEFINED
        value_abilityName_type = runtimeType(value_abilityName)
        valueSerializer.writeInt8((value_abilityName_type).toChar())
        if ((value_abilityName_type) != (RuntimeType.UNDEFINED)) {
            const value_abilityName_value  = value_abilityName!
            valueSerializer.writeString(value_abilityName_value)
        }
        const value_uri  = value.uri
        let value_uri_type : int32 = RuntimeType.UNDEFINED
        value_uri_type = runtimeType(value_uri)
        valueSerializer.writeInt8((value_uri_type).toChar())
        if ((value_uri_type) != (RuntimeType.UNDEFINED)) {
            const value_uri_value  = value_uri!
            valueSerializer.writeString(value_uri_value)
        }
        const value_params  = value.params
        let value_params_type : int32 = RuntimeType.UNDEFINED
        value_params_type = runtimeType(value_params)
        valueSerializer.writeInt8((value_params_type).toChar())
        if ((value_params_type) != (RuntimeType.UNDEFINED)) {
            const value_params_value  = value_params!
            valueSerializer.holdAndWriteObject(value_params_value)
        }
    }
    public static read(buffer: DeserializerBase): FormLinkOptions {
        let valueDeserializer : DeserializerBase = buffer
        const action_result : string = (valueDeserializer.readString() as string)
        const moduleName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moduleName_buf : string | undefined
        if ((moduleName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            moduleName_buf = (valueDeserializer.readString() as string)
        }
        const moduleName_result : string | undefined = moduleName_buf
        const bundleName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bundleName_buf : string | undefined
        if ((bundleName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bundleName_buf = (valueDeserializer.readString() as string)
        }
        const bundleName_result : string | undefined = bundleName_buf
        const abilityName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let abilityName_buf : string | undefined
        if ((abilityName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            abilityName_buf = (valueDeserializer.readString() as string)
        }
        const abilityName_result : string | undefined = abilityName_buf
        const uri_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uri_buf : string | undefined
        if ((uri_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            uri_buf = (valueDeserializer.readString() as string)
        }
        const uri_result : string | undefined = uri_buf
        const params_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let params_buf : Object | undefined
        if ((params_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            params_buf = (valueDeserializer.readObject() as object)
        }
        const params_result : Object | undefined = params_buf
        let value : FormLinkOptions = ({action: action_result, moduleName: moduleName_result, bundleName: bundleName_result, abilityName: abilityName_result, uri: uri_result, params: params_result} as FormLinkOptions)
        return value
    }
}

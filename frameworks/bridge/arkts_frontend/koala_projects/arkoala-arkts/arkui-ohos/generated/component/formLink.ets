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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookFormLinkAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { FormLinkModifier } from "./../FormLinkModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFormLinkPeer extends ArkCommonMethodPeer {
    attributeSet?: FormLinkModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFormLinkPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormLink_construct(peerId, flags)
        const _peer  = new ArkFormLinkPeer(_peerPtr, peerId, 'FormLink', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormLinkOptionsAttribute(options: FormLinkOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    setFormLinkOptions(options: FormLinkOptions): this {
        throw new Error("Unimplemented method setFormLinkOptions")
    }
    attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFormLinkStyle extends ArkCommonMethodStyle implements FormLinkAttribute {
    attributeModifier_value?: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined
    setFormLinkOptions(options: FormLinkOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkFormLinkComponent extends ArkCommonMethodComponent implements FormLinkAttribute {
    getPeer(): ArkFormLinkPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkFormLinkPeer)
    }
    public setFormLinkOptions(options: FormLinkOptions): this {
        if (this.checkPriority("setFormLinkOptions")) {
            const options_casted = options as (FormLinkOptions)
            this.getPeer()?.setFormLinkOptionsAttribute(options_casted)
            this.applyOptionsFinish('FormLinkAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormLinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookFormLinkAttributeModifier(this, value);
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
export function FormLinkImpl(
    @memo
    style: ((attributes: FormLinkAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFormLinkComponent>((): ArkFormLinkComponent => {
        return new ArkFormLinkComponent()
    })
    NodeAttach<ArkFormLinkPeer>((): ArkFormLinkPeer => ArkFormLinkPeer.create(receiver), (peer: ArkFormLinkPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class FormLinkOptions_serializer {
    public static write(buffer: SerializerBase, value: FormLinkOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAction  = value.action
        valueSerializer.writeString(valueHolderForAction)
        const valueHolderForModuleName  = value.moduleName
        if (valueHolderForModuleName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModuleNameTmpValue  = valueHolderForModuleName!
            valueSerializer.writeString(valueHolderForModuleNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBundleName  = value.bundleName
        if (valueHolderForBundleName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBundleNameTmpValue  = valueHolderForBundleName!
            valueSerializer.writeString(valueHolderForBundleNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAbilityName  = value.abilityName
        if (valueHolderForAbilityName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAbilityNameTmpValue  = valueHolderForAbilityName!
            valueSerializer.writeString(valueHolderForAbilityNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUri  = value.uri
        if (valueHolderForUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUriTmpValue  = valueHolderForUri!
            valueSerializer.writeString(valueHolderForUriTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParams  = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue  = valueHolderForParams!
            valueSerializer.holdAndWriteObject(valueHolderForParamsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FormLinkOptions {
        let valueDeserializer : DeserializerBase = buffer
        const actionTmpResult : string = (valueDeserializer.readString() as string)
        const moduleNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moduleNameTmpBuf : string | undefined = undefined
        if ((moduleNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            moduleNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const moduleNameTmpResult : string | undefined = moduleNameTmpBuf
        const bundleNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bundleNameTmpBuf : string | undefined = undefined
        if ((bundleNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bundleNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const bundleNameTmpResult : string | undefined = bundleNameTmpBuf
        const abilityNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let abilityNameTmpBuf : string | undefined = undefined
        if ((abilityNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            abilityNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const abilityNameTmpResult : string | undefined = abilityNameTmpBuf
        const uriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uriTmpBuf : string | undefined = undefined
        if ((uriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            uriTmpBuf = (valueDeserializer.readString() as string)
        }
        const uriTmpResult : string | undefined = uriTmpBuf
        const paramsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramsTmpBuf : Object | undefined = undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramsTmpBuf = (valueDeserializer.readObject() as object)
        }
        const paramsTmpResult : Object | undefined = paramsTmpBuf
        let value : FormLinkOptions = ({action: actionTmpResult, moduleName: moduleNameTmpResult, bundleName: bundleNameTmpResult, abilityName: abilityNameTmpResult, uri: uriTmpResult, params: paramsTmpResult} as FormLinkOptions)
        return value
    }
}

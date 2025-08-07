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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkPluginComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPluginComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PluginComponent_construct(peerId, flags)
        const _peer  = new ArkPluginComponentPeer(_peerPtr, peerId, 'PluginComponent', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PluginComponentAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: PluginErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class PluginComponentModifier extends CommonMethodModifier implements PluginComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: VoidCallback | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: PluginErrorCallback | undefined
    applyModifierPatch(peer: ArkPluginComponentPeer): void {
        super.applyModifierPatch(peer)
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as VoidCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as PluginErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as PluginErrorCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PluginComponentModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as PluginErrorCallback | undefined));
                }
            }
        }
    }
    onComplete(value: VoidCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: PluginErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PluginComponentTemplate_serializer {
    public static write(buffer: SerializerBase, value: PluginComponentTemplate): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSource  = value.source
        valueSerializer.writeString(valueHolderForSource)
        const valueHolderForBundleName  = value.bundleName
        valueSerializer.writeString(valueHolderForBundleName)
    }
    public static read(buffer: DeserializerBase): PluginComponentTemplate {
        let valueDeserializer : DeserializerBase = buffer
        const sourceTmpResult : string = (valueDeserializer.readString() as string)
        const bundleNameTmpResult : string = (valueDeserializer.readString() as string)
        let value : PluginComponentTemplate = ({source: sourceTmpResult, bundleName: bundleNameTmpResult} as PluginComponentTemplate)
        return value
    }
}
export class PluginErrorData_serializer {
    public static write(buffer: SerializerBase, value: PluginErrorData): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForErrcode  = value.errcode
        valueSerializer.writeNumber(valueHolderForErrcode)
        const valueHolderForMsg  = value.msg
        valueSerializer.writeString(valueHolderForMsg)
    }
    public static read(buffer: DeserializerBase): PluginErrorData {
        let valueDeserializer : DeserializerBase = buffer
        const errcodeTmpResult : number = (valueDeserializer.readNumber() as number)
        const msgTmpResult : string = (valueDeserializer.readString() as string)
        let value : PluginErrorData = ({errcode: errcodeTmpResult, msg: msgTmpResult} as PluginErrorData)
        return value
    }
}
export class PluginComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: PluginComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTemplate  = value.template
        PluginComponentTemplate_serializer.write(valueSerializer, valueHolderForTemplate)
        const valueHolderForData  = value.data
        if (valueHolderForData !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDataTmpValue  = valueHolderForData!
            valueSerializer.holdAndWriteObject(valueHolderForDataTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PluginComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const templateTmpResult : PluginComponentTemplate = PluginComponentTemplate_serializer.read(valueDeserializer)
        const dataTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dataTmpBuf : Object | undefined
        if ((dataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dataTmpBuf = (valueDeserializer.readObject() as object)
        }
        const dataTmpResult : Object | undefined = dataTmpBuf
        let value : PluginComponentOptions = ({template: templateTmpResult, data: dataTmpResult} as PluginComponentOptions)
        return value
    }
}

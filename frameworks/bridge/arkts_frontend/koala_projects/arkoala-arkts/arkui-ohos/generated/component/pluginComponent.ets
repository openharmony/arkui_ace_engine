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
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { VoidCallback } from './units'
import { AttributeModifier, hookPluginComponentAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { RecordData } from '@ohos.base'
import { PluginComponentModifier } from './../PluginComponentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkPluginComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: PluginComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
    source: string | undefined;
    bundleName: string | undefined;
}
export interface PluginComponentOptions {
    template: PluginComponentTemplate;
    data: RecordData;
}
export interface PluginErrorData {
    errcode: int32;
    msg: string;
}
export type PluginErrorCallback = (info: PluginErrorData) => void;
export interface PluginComponentAttribute extends CommonMethod {
    setPluginComponentOptions(options: PluginComponentOptions): this {
        throw new Error('Unimplemented method setPluginComponentOptions')
    }
    onComplete(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onComplete')
    }
    onError(value: PluginErrorCallback | undefined): this {
        throw new Error('Unimplemented method onError')
    }
    attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkPluginComponentComponent extends ArkCommonMethodComponent implements PluginComponentAttribute {
    getPeer(): ArkPluginComponentPeer {
        return (this.peer as ArkPluginComponentPeer)
    }
    public setPluginComponentOptions(options: PluginComponentOptions): this {
        if (this.checkPriority('setPluginComponentOptions')) {
            const options_casted = options as (PluginComponentOptions)
            this.getPeer()?.setPluginComponentOptionsAttribute(options_casted)
            this.applyOptionsFinish('PluginComponentAttribute');
            return this
        }
        return this
    }
    public onComplete(value: VoidCallback | undefined): this {
        if (this.checkPriority('onComplete')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: PluginErrorCallback | undefined): this {
        if (this.checkPriority('onError')) {
            const value_casted = value as (PluginErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PluginComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookPluginComponentAttributeModifier(this, value);
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
export function PluginComponentImpl(
    @memo @memo_skip
    style: ((attributes: PluginComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkPluginComponentComponent>((): ArkPluginComponentComponent => {
        return new ArkPluginComponentComponent()
    })
    NodeAttach<ArkPluginComponentPeer>((): ArkPluginComponentPeer => ArkPluginComponentPeer.create(receiver), (_: ArkPluginComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class PluginComponentTemplate_serializer {
    public static write(buffer: SerializerBase, value: PluginComponentTemplate): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSource  = value.source
        if (valueHolderForSource !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSourceTmpValue  = valueHolderForSource!
            valueSerializer.writeString(valueHolderForSourceTmpValue)
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
    }
    public static read(buffer: DeserializerBase): PluginComponentTemplate {
        let valueDeserializer : DeserializerBase = buffer
        const sourceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sourceTmpBuf : string | undefined = undefined
        if ((sourceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sourceTmpBuf = (valueDeserializer.readString() as string)
        }
        const sourceTmpResult : string | undefined = sourceTmpBuf
        const bundleNameTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let bundleNameTmpBuf : string | undefined = undefined
        if ((bundleNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bundleNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const bundleNameTmpResult : string | undefined = bundleNameTmpBuf
        let value : PluginComponentTemplate = ({source: sourceTmpResult, bundleName: bundleNameTmpResult} as PluginComponentTemplate)
        return value
    }
}
export class PluginErrorData_serializer {
    public static write(buffer: SerializerBase, value: PluginErrorData): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForErrcode  = value.errcode
        valueSerializer.writeInt32(valueHolderForErrcode)
        const valueHolderForMsg  = value.msg
        valueSerializer.writeString(valueHolderForMsg)
    }
    public static read(buffer: DeserializerBase): PluginErrorData {
        let valueDeserializer : DeserializerBase = buffer
        const errcodeTmpResult : int32 = valueDeserializer.readInt32()
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
        if (valueHolderForData !== undefined && valueHolderForData !== null) {
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
        const dataTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dataTmpBuf : Object | null | undefined = undefined
        if ((dataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dataTmpBuf = (valueDeserializer.readObject() as object)
        }
        const dataTmpResult : RecordData = dataTmpBuf
        let value : PluginComponentOptions = ({template: templateTmpResult, data: dataTmpResult} as PluginComponentOptions)
        return value
    }
}

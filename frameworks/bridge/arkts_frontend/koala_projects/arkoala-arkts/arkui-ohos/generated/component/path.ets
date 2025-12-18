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
import { ArkCommonShapeMethodPeer, CommonShapeMethod as arkui_component_common_CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookPathAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { PathModifier } from './../PathModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkPathPeer extends ArkCommonShapeMethodPeer {
    attributeSet?: PathModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPathPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Path_construct(peerId, flags)
        const _peer  = new ArkPathPeer(_peerPtr, peerId, 'Path', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPathOptionsAttribute(options?: PathOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PathOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PathInterface_setPathOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCommandsAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PathAttribute_setCommands(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PathOptions {
    width?: double | string;
    height?: double | string;
    commands?: string;
}
export interface PathAttribute extends arkui_component_common_CommonShapeMethod {
    setPathOptions(options?: PathOptions): this {
        throw new Error('Unimplemented method setPathOptions')
    }
    commands(value: string | undefined): this {
        throw new Error('Unimplemented method commands')
    }
    attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkPathComponent extends ArkCommonShapeMethodComponent implements PathAttribute {
    getPeer(): ArkPathPeer {
        return (this.peer as ArkPathPeer)
    }
    public setPathOptions(options?: PathOptions): this {
        if (this.checkPriority('setPathOptions')) {
            const options_casted = options as (PathOptions | undefined)
            this.getPeer()?.setPathOptionsAttribute(options_casted)
            this.applyOptionsFinish('PathAttribute');
            return this
        }
        return this
    }
    public commands(value: string | undefined): this {
        if (this.checkPriority('commands')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setCommandsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookPathAttributeModifier(this, value);
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
export function PathImpl(
    @memo @memo_skip
    style: ((attributes: PathAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkPathComponent>((): ArkPathComponent => {
        return new ArkPathComponent()
    })
    NodeAttach<ArkPathPeer>((): ArkPathPeer => ArkPathPeer.create(receiver), (_: ArkPathPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class PathOptions_serializer {
    public static write(buffer: SerializerBase, value: PathOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCommands  = value.commands
        if (valueHolderForCommands !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCommandsTmpValue  = valueHolderForCommands!
            valueSerializer.writeString(valueHolderForCommandsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PathOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : double | string | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : double | string | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        const commandsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let commandsTmpBuf : string | undefined = undefined
        if ((commandsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            commandsTmpBuf = (valueDeserializer.readString() as string)
        }
        const commandsTmpResult : string | undefined = commandsTmpBuf
        let value : PathOptions = ({width: widthTmpResult, height: heightTmpResult, commands: commandsTmpResult} as PathOptions)
        return value
    }
}

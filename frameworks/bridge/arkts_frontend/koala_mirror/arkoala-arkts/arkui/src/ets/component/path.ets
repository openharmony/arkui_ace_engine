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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonShapeMethodSet, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPathPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPathPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Path_construct(peerId, flags)
        const _peer  = new ArkPathPeer(_peerPtr, peerId, "Path", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPathOptionsAttribute(options?: PathOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            PathOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._PathInterface_setPathOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCommandsAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._PathAttribute_setCommands(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PathOptions {
    width?: number | string;
    height?: number | string;
    commands?: string;
}
export interface PathAttribute extends CommonShapeMethod {
    commands(value: string | undefined): this
    attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkPathStyle extends ArkCommonShapeMethodStyle implements PathAttribute {
    commands_value?: string | undefined
    attributeModifier_value?: AttributeModifier<PathAttribute> | AttributeModifier<CommonMethod> | undefined
    public commands(value: string | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: PathAttribute): void {
        super.apply(target)
        if (this.commands_value !== undefined)
            target.commands(this.commands_value!)
    }
}

export class ArkPathComponent extends ArkCommonShapeMethodComponent implements PathAttribute {
    getPeer(): ArkPathPeer {
        return (this.peer as ArkPathPeer)
    }
    public setPathOptions(options?: PathOptions): this {
        if (this.checkPriority("setPathOptions")) {
            const options_casted = options as (PathOptions | undefined)
            this.getPeer()?.setPathOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public commands(value: string | undefined): this {
        if (this.checkPriority("commands")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setCommandsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withPathStyle(receiver: PathAttribute, modifier: AttributeModifier<PathAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkPathStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Path")
// export function Path(
//     options?: PathOptions,
//     @memo
//     content_?: () => void,
// ): PathAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Path(
    @memo
    style: ((attributes: PathAttribute) => void) | undefined,
    options?: PathOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPathComponent>((): ArkPathComponent => {
        return new ArkPathComponent()
    })
    NodeAttach<ArkPathPeer>((): ArkPathPeer => ArkPathPeer.create(receiver), (_: ArkPathPeer): void => {
        receiver.setPathOptions(options)
        style?.(receiver)
        withPathStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkPathSet extends ArkCommonShapeMethodSet implements PathAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _commands_flag?: boolean
    _commands0_value?: string | undefined
    applyModifierPatch(component: PathAttribute): void {
        if (this._commands_flag)
            component.commands((this._commands0_value as string | undefined))
    }
    public commands(value: string | undefined): this {
        this._commands_flag = true
        this._commands0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PathOptions_serializer {
    public static write(buffer: SerializerBase, value: PathOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_width_type)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_height_type)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
        const value_commands  = value.commands
        let value_commands_type : int32 = RuntimeType.UNDEFINED
        value_commands_type = runtimeType(value_commands)
        valueSerializer.writeInt8((value_commands_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_commands_type)) {
            const value_commands_value  = value_commands!
            valueSerializer.writeString(value_commands_value)
        }
    }
    public static read(buffer: DeserializerBase): PathOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (width_buf_runtimeType))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (height_buf_runtimeType))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        const commands_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let commands_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (commands_buf_runtimeType))
        {
            commands_buf = (valueDeserializer.readString() as string)
        }
        const commands_result : string | undefined = commands_buf
        let value : PathOptions = ({width: width_result, height: height_result, commands: commands_result} as PathOptions)
        return value
    }
}

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
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceStr, Dimension } from "./units"
import { Resource } from "global.resource"
import { AttributeModifier, extractors, hookComponent3DAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Scene } from "graphics3d.Scene"
import { Component3DModifier } from "./../Component3DModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Scene_serializer } from "./../framework/Scene"
export class ArkComponent3DPeer extends ArkCommonMethodPeer {
    attributeSet?: Component3DModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkComponent3DPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Component3D_construct(peerId, flags)
        const _peer  = new ArkComponent3DPeer(_peerPtr, peerId, 'Component3D', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setComponent3DOptionsAttribute(sceneOptions?: SceneOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (sceneOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sceneOptionsTmpValue  = sceneOptions!
            SceneOptions_serializer.write(thisSerializer, sceneOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DInterface_setComponent3DOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnvironmentAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setEnvironment(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShaderAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setShader(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShaderImageTextureAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setShaderImageTexture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShaderInputBufferAttribute(value: Array<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : number = valueTmpValue[valueTmpValueCounterI]
                thisSerializer.writeNumber(valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setShaderInputBuffer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setRenderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setRenderHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomRenderAttribute(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (uri !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const uriTmpValue  = uri!
            if (uriTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const uriTmpValueForIdx0  = uriTmpValue as string
                thisSerializer.writeString(uriTmpValueForIdx0)
            } else if (uriTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const uriTmpValueForIdx1  = uriTmpValue as Resource
                Resource_serializer.write(thisSerializer, uriTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (selfRenderUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selfRenderUpdateTmpValue  = selfRenderUpdate!
            thisSerializer.writeBoolean(selfRenderUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_setCustomRender(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ModelType {
    TEXTURE = 0,
    SURFACE = 1
}
export interface SceneOptions {
    scene?: ResourceStr | Scene;
    modelType?: ModelType;
}
export interface Component3DAttribute extends CommonMethod {
    setComponent3DOptions(sceneOptions?: SceneOptions): this {
        throw new Error("Unimplemented method setComponent3DOptions")
    }
    environment(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method environment")
    }
    shader(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method shader")
    }
    shaderImageTexture(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method shaderImageTexture")
    }
    shaderInputBuffer(value: Array<number> | undefined): this {
        throw new Error("Unimplemented method shaderInputBuffer")
    }
    renderWidth(value: Dimension | undefined): this {
        throw new Error("Unimplemented method renderWidth")
    }
    renderHeight(value: Dimension | undefined): this {
        throw new Error("Unimplemented method renderHeight")
    }
    customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        throw new Error("Unimplemented method customRender")
    }
    attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkComponent3DStyle extends ArkCommonMethodStyle implements Component3DAttribute {
    environment_value?: ResourceStr | undefined
    shader_value?: ResourceStr | undefined
    shaderImageTexture_value?: ResourceStr | undefined
    shaderInputBuffer_value?: Array<number> | undefined
    renderWidth_value?: Dimension | undefined
    renderHeight_value?: Dimension | undefined
    attributeModifier_value?: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined
    setComponent3DOptions(sceneOptions?: SceneOptions): this {
        return this
    }
    environment(value: ResourceStr | undefined): this {
        return this
    }
    shader(value: ResourceStr | undefined): this {
        return this
    }
    shaderImageTexture(value: ResourceStr | undefined): this {
        return this
    }
    shaderInputBuffer(value: Array<number> | undefined): this {
        return this
    }
    renderWidth(value: Dimension | undefined): this {
        return this
    }
    renderHeight(value: Dimension | undefined): this {
        return this
    }
    customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkComponent3DComponent extends ArkCommonMethodComponent implements Component3DAttribute {
    getPeer(): ArkComponent3DPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkComponent3DPeer)
    }
    public setComponent3DOptions(sceneOptions?: SceneOptions): this {
        if (this.checkPriority("setComponent3DOptions")) {
            const sceneOptions_casted = sceneOptions as (SceneOptions | undefined)
            this.getPeer()?.setComponent3DOptionsAttribute(sceneOptions_casted)
            this.applyOptionsFinish('Component3DAttribute');
            return this
        }
        return this
    }
    public environment(value: ResourceStr | undefined): this {
        if (this.checkPriority("environment")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setEnvironmentAttribute(value_casted)
            return this
        }
        return this
    }
    public shader(value: ResourceStr | undefined): this {
        if (this.checkPriority("shader")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setShaderAttribute(value_casted)
            return this
        }
        return this
    }
    public shaderImageTexture(value: ResourceStr | undefined): this {
        if (this.checkPriority("shaderImageTexture")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setShaderImageTextureAttribute(value_casted)
            return this
        }
        return this
    }
    public shaderInputBuffer(value: Array<number> | undefined): this {
        if (this.checkPriority("shaderInputBuffer")) {
            const value_casted = value as (Array<number> | undefined)
            this.getPeer()?.setShaderInputBufferAttribute(value_casted)
            return this
        }
        return this
    }
    public renderWidth(value: Dimension | undefined): this {
        if (this.checkPriority("renderWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setRenderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public renderHeight(value: Dimension | undefined): this {
        if (this.checkPriority("renderHeight")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setRenderHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        if (this.checkPriority("customRender")) {
            const uri_casted = uri as (ResourceStr | undefined)
            const selfRenderUpdate_casted = selfRenderUpdate as (boolean | undefined)
            this.getPeer()?.setCustomRenderAttribute(uri_casted, selfRenderUpdate_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookComponent3DAttributeModifier(this, value);
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
export function Component3DImpl(
    @memo
    style: ((attributes: Component3DAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkComponent3DComponent>((): ArkComponent3DComponent => {
        return new ArkComponent3DComponent()
    })
    NodeAttach<ArkComponent3DPeer>((): ArkComponent3DPeer => ArkComponent3DPeer.create(receiver), (peer: ArkComponent3DPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class SceneOptions_serializer {
    public static write(buffer: SerializerBase, value: SceneOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScene  = value.scene
        if (valueHolderForScene !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSceneTmpValue  = valueHolderForScene!
            if (valueHolderForSceneTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSceneTmpValueForIdx0  = valueHolderForSceneTmpValue as ResourceStr
                if (valueHolderForSceneTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForSceneTmpValueForIdx0ForIdx0  = valueHolderForSceneTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForSceneTmpValueForIdx0ForIdx0)
                } else if (valueHolderForSceneTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForSceneTmpValueForIdx0ForIdx1  = valueHolderForSceneTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForSceneTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForSceneTmpValue instanceof Scene) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSceneTmpValueForIdx1  = valueHolderForSceneTmpValue as Scene
                Scene_serializer.write(valueSerializer, valueHolderForSceneTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForModelType  = value.modelType
        if (valueHolderForModelType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModelTypeTmpValue  = (valueHolderForModelType as ModelType)
            valueSerializer.writeInt32(valueHolderForModelTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SceneOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sceneTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sceneTmpBuf : ResourceStr | Scene | undefined = undefined
        if ((sceneTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sceneTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let sceneTmpBuf_ : ResourceStr | Scene | undefined
            if (sceneTmpBuf_UnionSelector == (0).toChar()) {
                const sceneTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let sceneTmpBuf_BufU : string | Resource | undefined
                if (sceneTmpBuf_BufUUnionSelector == (0).toChar()) {
                    sceneTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (sceneTmpBuf_BufUUnionSelector == (1).toChar()) {
                    sceneTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for sceneTmpBuf_BufU has to be chosen through deserialisation.")
                }
                sceneTmpBuf_ = (sceneTmpBuf_BufU as string | Resource)
            } else if (sceneTmpBuf_UnionSelector == (1).toChar()) {
                sceneTmpBuf_ = (Scene_serializer.read(valueDeserializer) as Scene)
            } else {
                throw new Error("One of the branches for sceneTmpBuf_ has to be chosen through deserialisation.")
            }
            sceneTmpBuf = (sceneTmpBuf_ as ResourceStr | Scene)
        }
        const sceneTmpResult : ResourceStr | Scene | undefined = sceneTmpBuf
        const modelTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modelTypeTmpBuf : ModelType | undefined = undefined
        if ((modelTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modelTypeTmpBuf = ModelType.fromValue(valueDeserializer.readInt32())
        }
        const modelTypeTmpResult : ModelType | undefined = modelTypeTmpBuf
        let value : SceneOptions = ({scene: sceneTmpResult, modelType: modelTypeTmpResult} as SceneOptions)
        return value
    }
}

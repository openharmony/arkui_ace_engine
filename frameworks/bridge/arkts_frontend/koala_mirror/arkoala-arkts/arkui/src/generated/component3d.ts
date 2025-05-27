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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceStr, Dimension } from "./units"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Scene } from "./arkui-custom"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkComponent3DPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkComponent3DPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Component3D_construct(peerId, flags)
        const _peer  = new ArkComponent3DPeer(_peerPtr, peerId, "Component3D", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setComponent3DOptionsAttribute(sceneOptions?: SceneOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let sceneOptions_type : int32 = RuntimeType.UNDEFINED
        sceneOptions_type = runtimeType(sceneOptions)
        thisSerializer.writeInt8(sceneOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (sceneOptions_type)) {
            const sceneOptions_value  = sceneOptions!
            thisSerializer.writeSceneOptions(sceneOptions_value)
        }
        ArkUIGeneratedNativeModule._Component3DInterface_setComponent3DOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    environmentAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_environment(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shader(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderImageTextureAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shaderImageTexture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderInputBufferAttribute(value: Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : number = value[i]
            thisSerializer.writeNumber(value_element)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shaderInputBuffer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderWidthAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_renderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderHeightAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_renderHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customRenderAttribute(uri: ResourceStr, selfRenderUpdate: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let uri_type : int32 = RuntimeType.UNDEFINED
        uri_type = runtimeType(uri)
        if (RuntimeType.STRING == uri_type) {
            thisSerializer.writeInt8(0 as int32)
            const uri_0  = uri as string
            thisSerializer.writeString(uri_0)
        }
        else if (RuntimeType.OBJECT == uri_type) {
            thisSerializer.writeInt8(1 as int32)
            const uri_1  = uri as Resource
            thisSerializer.writeResource(uri_1)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_customRender(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), selfRenderUpdate ? 1 : 0)
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
    environment(value: ResourceStr): this
    shader(value: ResourceStr): this
    shaderImageTexture(value: ResourceStr): this
    shaderInputBuffer(value: Array<number>): this
    renderWidth(value: Dimension): this
    renderHeight(value: Dimension): this
    customRender(uri: ResourceStr, selfRenderUpdate: boolean): this
    attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIComponent3DAttribute extends UICommonMethod {
    /** @memo */
    environment(value: ResourceStr): this
    /** @memo */
    shader(value: ResourceStr): this
    /** @memo */
    shaderImageTexture(value: ResourceStr): this
    /** @memo */
    shaderInputBuffer(value: Array<number>): this
    /** @memo */
    renderWidth(value: Dimension): this
    /** @memo */
    renderHeight(value: Dimension): this
    /** @memo */
    customRender(uri: ResourceStr, selfRenderUpdate: boolean): this
    /** @memo */
    attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkComponent3DStyle extends ArkCommonMethodStyle implements Component3DAttribute {
    environment_value?: ResourceStr
    shader_value?: ResourceStr
    shaderImageTexture_value?: ResourceStr
    shaderInputBuffer_value?: Array<number>
    renderWidth_value?: Dimension
    renderHeight_value?: Dimension
    public environment(value: ResourceStr): this {
        return this
    }
    public shader(value: ResourceStr): this {
        return this
    }
    public shaderImageTexture(value: ResourceStr): this {
        return this
    }
    public shaderInputBuffer(value: Array<number>): this {
        return this
    }
    public renderWidth(value: Dimension): this {
        return this
    }
    public renderHeight(value: Dimension): this {
        return this
    }
    public customRender(uri: ResourceStr, selfRenderUpdate: boolean): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkComponent3DComponent extends ArkCommonMethodComponent implements UIComponent3DAttribute {
    getPeer(): ArkComponent3DPeer {
        return (this.peer as ArkComponent3DPeer)
    }
    /** @memo */
    public setComponent3DOptions(sceneOptions?: SceneOptions): this {
        if (this.checkPriority("setComponent3DOptions")) {
            const sceneOptions_casted = sceneOptions as (SceneOptions | undefined)
            this.getPeer()?.setComponent3DOptionsAttribute(sceneOptions_casted)
            return this
        }
        return this
    }
    /** @memo */
    public environment(value: ResourceStr): this {
        if (this.checkPriority("environment")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.environmentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shader(value: ResourceStr): this {
        if (this.checkPriority("shader")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.shaderAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shaderImageTexture(value: ResourceStr): this {
        if (this.checkPriority("shaderImageTexture")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.shaderImageTextureAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shaderInputBuffer(value: Array<number>): this {
        if (this.checkPriority("shaderInputBuffer")) {
            const value_casted = value as (Array<number>)
            this.getPeer()?.shaderInputBufferAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderWidth(value: Dimension): this {
        if (this.checkPriority("renderWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.renderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderHeight(value: Dimension): this {
        if (this.checkPriority("renderHeight")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.renderHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customRender(uri: ResourceStr, selfRenderUpdate: boolean): this {
        if (this.checkPriority("customRender")) {
            const uri_casted = uri as (ResourceStr)
            const selfRenderUpdate_casted = selfRenderUpdate as (boolean)
            this.getPeer()?.customRenderAttribute(uri_casted, selfRenderUpdate_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkComponent3D(
    /** @memo */
    style: ((attributes: UIComponent3DAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    sceneOptions?: SceneOptions,
): void {
    const receiver = remember(() => {
        return new ArkComponent3DComponent()
    })
    NodeAttach<ArkComponent3DPeer>((): ArkComponent3DPeer => ArkComponent3DPeer.create(receiver), (_: ArkComponent3DPeer) => {
        receiver.setComponent3DOptions(sceneOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

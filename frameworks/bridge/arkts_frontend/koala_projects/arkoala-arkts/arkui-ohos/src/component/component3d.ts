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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceStr, Dimension, PX, VP, FP, LPX, Percentage } from "./units"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Scene } from "./arkui-custom"

export class ArkComponent3DPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkComponent3DPeer {
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
    environmentAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_environment(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shader(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderImageTextureAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shaderImageTexture(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shaderInputBufferAttribute(value: Array<number> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : number = value_value[i]
                thisSerializer.writeNumber(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_shaderInputBuffer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_renderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_renderHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customRenderAttribute(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let uri_type : int32 = RuntimeType.UNDEFINED
        uri_type = runtimeType(uri)
        thisSerializer.writeInt8(uri_type as int32)
        if ((RuntimeType.UNDEFINED) != (uri_type)) {
            const uri_value  = uri!
            let uri_value_type : int32 = RuntimeType.UNDEFINED
            uri_value_type = runtimeType(uri_value)
            if (RuntimeType.STRING == uri_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const uri_value_0  = uri_value as string
                thisSerializer.writeString(uri_value_0)
            }
            else if (RuntimeType.OBJECT == uri_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const uri_value_1  = uri_value as Resource
                thisSerializer.writeResource(uri_value_1)
            }
        }
        let selfRenderUpdate_type : int32 = RuntimeType.UNDEFINED
        selfRenderUpdate_type = runtimeType(selfRenderUpdate)
        thisSerializer.writeInt8(selfRenderUpdate_type as int32)
        if ((RuntimeType.UNDEFINED) != (selfRenderUpdate_type)) {
            const selfRenderUpdate_value  = selfRenderUpdate!
            thisSerializer.writeBoolean(selfRenderUpdate_value)
        }
        ArkUIGeneratedNativeModule._Component3DAttribute_customRender(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type Component3DInterface = (sceneOptions?: SceneOptions) => Component3DAttribute;
export interface Component3DAttribute extends CommonMethod {
    environment(value: ResourceStr | undefined): this
    shader(value: ResourceStr | undefined): this
    shaderImageTexture(value: ResourceStr | undefined): this
    shaderInputBuffer(value: Array<number> | undefined): this
    renderWidth(value: Dimension | undefined): this
    renderHeight(value: Dimension | undefined): this
    customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this
}
export class ArkComponent3DStyle extends ArkCommonMethodStyle implements Component3DAttribute {
    environment_value?: ResourceStr | undefined
    shader_value?: ResourceStr | undefined
    shaderImageTexture_value?: ResourceStr | undefined
    shaderInputBuffer_value?: Array<number> | undefined
    renderWidth_value?: Dimension | undefined
    renderHeight_value?: Dimension | undefined
    public environment(value: ResourceStr | undefined): this {
        return this
    }
    public shader(value: ResourceStr | undefined): this {
        return this
    }
    public shaderImageTexture(value: ResourceStr | undefined): this {
        return this
    }
    public shaderInputBuffer(value: Array<number> | undefined): this {
        return this
    }
    public renderWidth(value: Dimension | undefined): this {
        return this
    }
    public renderHeight(value: Dimension | undefined): this {
        return this
    }
    public customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        return this
        }
}
export class ArkComponent3DComponent extends ArkCommonMethodComponent implements Component3DAttribute {
    getPeer(): ArkComponent3DPeer {
        return (this.peer as ArkComponent3DPeer)
    }
    public setComponent3DOptions(sceneOptions?: SceneOptions): this {
        if (this.checkPriority("setComponent3DOptions")) {
            const sceneOptions_casted = sceneOptions as (SceneOptions | undefined)
            this.getPeer()?.setComponent3DOptionsAttribute(sceneOptions_casted)
            return this
        }
        return this
    }
    public environment(value: ResourceStr | undefined): this {
        if (this.checkPriority("environment")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.environmentAttribute(value_casted)
            return this
        }
        return this
    }
    public shader(value: ResourceStr | undefined): this {
        if (this.checkPriority("shader")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.shaderAttribute(value_casted)
            return this
        }
        return this
    }
    public shaderImageTexture(value: ResourceStr | undefined): this {
        if (this.checkPriority("shaderImageTexture")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.shaderImageTextureAttribute(value_casted)
            return this
        }
        return this
    }
    public shaderInputBuffer(value: Array<number> | undefined): this {
        if (this.checkPriority("shaderInputBuffer")) {
            const value_casted = value as (Array<number> | undefined)
            this.getPeer()?.shaderInputBufferAttribute(value_casted)
            return this
        }
        return this
    }
    public renderWidth(value: Dimension | undefined): this {
        if (this.checkPriority("renderWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.renderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public renderHeight(value: Dimension | undefined): this {
        if (this.checkPriority("renderHeight")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.renderHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        if (this.checkPriority("customRender")) {
            const uri_casted = uri as (ResourceStr | undefined)
            const selfRenderUpdate_casted = selfRenderUpdate as (boolean | undefined)
            this.getPeer()?.customRenderAttribute(uri_casted, selfRenderUpdate_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Component3D(
    /** @memo */
    style: ((attributes: Component3DAttribute) => void) | undefined,
    sceneOptions?: SceneOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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

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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from "./imageCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { XComponentType } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
export class XComponentControllerInternal {
    public static fromPtr(ptr: KPointer): XComponentController {
        return new XComponentController(ptr)
    }
}
export class XComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onSurfaceCreated(): ((surfaceId: string) => void) {
        return this.getOnSurfaceCreated()
    }
    set onSurfaceCreated(onSurfaceCreated: ((surfaceId: string) => void)) {
        this.setOnSurfaceCreated(onSurfaceCreated)
    }
    get onSurfaceChanged(): ((surfaceId: string,rect: SurfaceRect) => void) {
        return this.getOnSurfaceChanged()
    }
    set onSurfaceChanged(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)) {
        this.setOnSurfaceChanged(onSurfaceChanged)
    }
    get onSurfaceDestroyed(): ((surfaceId: string) => void) {
        return this.getOnSurfaceDestroyed()
    }
    set onSurfaceDestroyed(onSurfaceDestroyed: ((surfaceId: string) => void)) {
        this.setOnSurfaceDestroyed(onSurfaceDestroyed)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, XComponentController.getFinalizer())
    }
    constructor() {
        this(XComponentController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._XComponentController_getFinalizer()
    }
    public getXComponentSurfaceId(): string {
        return this.getXComponentSurfaceId_serialize()
    }
    public getXComponentContext(): Object {
        return this.getXComponentContext_serialize()
    }
    public setXComponentSurfaceRect(rect: SurfaceRect): void {
        const rect_casted = rect as (SurfaceRect)
        this.setXComponentSurfaceRect_serialize(rect_casted)
        return
    }
    public getXComponentSurfaceRect(): SurfaceRect {
        return this.getXComponentSurfaceRect_serialize()
    }
    public setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void {
        const rotationOptions_casted = rotationOptions as (SurfaceRotationOptions)
        this.setXComponentSurfaceRotation_serialize(rotationOptions_casted)
        return
    }
    public getXComponentSurfaceRotation(): SurfaceRotationOptions {
        return this.getXComponentSurfaceRotation_serialize()
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this.stopImageAnalyzer_serialize()
        return
    }
    private getOnSurfaceCreated(): ((surfaceId: string) => void) {
        return this.getOnSurfaceCreated_serialize()
    }
    private setOnSurfaceCreated(onSurfaceCreated: ((surfaceId: string) => void)): void {
        const onSurfaceCreated_casted = onSurfaceCreated as (((surfaceId: string) => void))
        this.setOnSurfaceCreated_serialize(onSurfaceCreated_casted)
        return
    }
    private getOnSurfaceChanged(): ((surfaceId: string,rect: SurfaceRect) => void) {
        return this.getOnSurfaceChanged_serialize()
    }
    private setOnSurfaceChanged(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const onSurfaceChanged_casted = onSurfaceChanged as (((surfaceId: string,rect: SurfaceRect) => void))
        this.setOnSurfaceChanged_serialize(onSurfaceChanged_casted)
        return
    }
    private getOnSurfaceDestroyed(): ((surfaceId: string) => void) {
        return this.getOnSurfaceDestroyed_serialize()
    }
    private setOnSurfaceDestroyed(onSurfaceDestroyed: ((surfaceId: string) => void)): void {
        const onSurfaceDestroyed_casted = onSurfaceDestroyed as (((surfaceId: string) => void))
        this.setOnSurfaceDestroyed_serialize(onSurfaceDestroyed_casted)
        return
    }
    private getXComponentSurfaceId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceId(this.peer!.ptr)
        return retval
    }
    private getXComponentContext_serialize(): Object {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentContext(this.peer!.ptr)
        return retval
    }
    private setXComponentSurfaceRect_serialize(rect: SurfaceRect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SurfaceRect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRect_serialize(): SurfaceRect {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRect(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SurfaceRect = SurfaceRect_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setXComponentSurfaceRotation_serialize(rotationOptions: SurfaceRotationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SurfaceRotationOptions_serializer.write(thisSerializer, rotationOptions)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRotation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRotation_serialize(): SurfaceRotationOptions {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRotation(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SurfaceRotationOptions = SurfaceRotationOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ImageAnalyzerConfig_serializer.write(thisSerializer, config)
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._XComponentController_startImageAnalyzer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._XComponentController_stopImageAnalyzer(this.peer!.ptr)
    }
    private getOnSurfaceCreated_serialize(): ((surfaceId: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceCreated(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceCreated_serialize(onSurfaceCreated: ((surfaceId: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceCreated)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceCreated(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceChanged_serialize(): ((surfaceId: string,rect: SurfaceRect) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceChanged(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceChanged_serialize(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceChanged)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceDestroyed_serialize(): ((surfaceId: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceDestroyed(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceDestroyed_serialize(onSurfaceDestroyed: ((surfaceId: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceDestroyed)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceDestroyed(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkXComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkXComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._XComponent_construct(peerId, flags)
        const _peer  = new ArkXComponentPeer(_peerPtr, peerId, "XComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setXComponentOptions0Attribute(value: XComponentParameter): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        XComponentParameter_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setXComponentOptions1Attribute(options: XComponentOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        XComponentOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setXComponentOptions2Attribute(params: NativeXComponentParameters): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NativeXComponentParameters_serializer.write(thisSerializer, params)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadAttribute(value: OnNativeLoadCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setOnLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDestroyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setOnDestroy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableSecureAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setEnableSecure(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHdrBrightnessAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setHdrBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableTransparentLayerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setEnableTransparentLayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SurfaceRect {
    offsetX?: number;
    offsetY?: number;
    surfaceWidth: number;
    surfaceHeight: number;
}
export interface SurfaceRotationOptions {
    lock?: boolean;
}
export interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
    imageAIOptions?: ImageAIOptions;
    screenId?: number;
}
export interface NativeXComponentParameters {
    type: XComponentType;
    imageAIOptions?: ImageAIOptions;
}
export type OnNativeLoadCallback = (event?: Object) => void;
export interface XComponentAttribute extends CommonMethod {
    onLoad(value: OnNativeLoadCallback | undefined): this {
        throw new Error("Unimplemented method onLoad")
    }
    onDestroy(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onDestroy")
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnalyzer")
    }
    enableSecure(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableSecure")
    }
    hdrBrightness(value: number | undefined): this {
        throw new Error("Unimplemented method hdrBrightness")
    }
    enableTransparentLayer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableTransparentLayer")
    }
    attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkXComponentStyle extends ArkCommonMethodStyle implements XComponentAttribute {
    onLoad_value?: OnNativeLoadCallback | undefined
    onDestroy_value?: VoidCallback | undefined
    enableAnalyzer_value?: boolean | undefined
    enableSecure_value?: boolean | undefined
    hdrBrightness_value?: number | undefined
    enableTransparentLayer_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public onLoad(value: OnNativeLoadCallback | undefined): this {
        return this
    }
    public onDestroy(value: VoidCallback | undefined): this {
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    public enableSecure(value: boolean | undefined): this {
        return this
    }
    public hdrBrightness(value: number | undefined): this {
        return this
    }
    public enableTransparentLayer(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: XComponentAttribute): void {
        super.apply(target)
        if (this.onLoad_value !== undefined)
            target.onLoad(this.onLoad_value!)
        if (this.onDestroy_value !== undefined)
            target.onDestroy(this.onDestroy_value!)
        if (this.enableAnalyzer_value !== undefined)
            target.enableAnalyzer(this.enableAnalyzer_value!)
        if (this.enableSecure_value !== undefined)
            target.enableSecure(this.enableSecure_value!)
        if (this.hdrBrightness_value !== undefined)
            target.hdrBrightness(this.hdrBrightness_value!)
        if (this.enableTransparentLayer_value !== undefined)
            target.enableTransparentLayer(this.enableTransparentLayer_value!)
    }
}
export interface XComponentParameter {
    id: string;
    type: XComponentType;
    libraryname?: string;
    controller?: XComponentController;
}

export class ArkXComponentComponent extends ArkCommonMethodComponent implements XComponentAttribute {
    getPeer(): ArkXComponentPeer {
        return (this.peer as ArkXComponentPeer)
    }
    public setXComponentOptions(value: XComponentParameter): this {
        if (this.checkPriority("setXComponentOptions")) {
            const value_casted = value as (XComponentParameter)
            this.getPeer()?.setXComponentOptions0Attribute(value_casted)
            return this
        }
        return this
    }
    public setXComponentOptions(options: XComponentOptions): this {
        if (this.checkPriority("setXComponentOptions")) {
            const options_casted = options as (XComponentOptions)
            this.getPeer()?.setXComponentOptions1Attribute(options_casted)
            return this
        }
        return this
    }
    public setXComponentOptions(params: NativeXComponentParameters): this {
        if (this.checkPriority("setXComponentOptions")) {
            const params_casted = params as (NativeXComponentParameters)
            this.getPeer()?.setXComponentOptions2Attribute(params_casted)
            return this
        }
        return this
    }
    public onLoad(value: OnNativeLoadCallback | undefined): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as (OnNativeLoadCallback | undefined)
            this.getPeer()?.setOnLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onDestroy(value: VoidCallback | undefined): this {
        if (this.checkPriority("onDestroy")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnDestroyAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public enableSecure(value: boolean | undefined): this {
        if (this.checkPriority("enableSecure")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableSecureAttribute(value_casted)
            return this
        }
        return this
    }
    public hdrBrightness(value: number | undefined): this {
        if (this.checkPriority("hdrBrightness")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setHdrBrightnessAttribute(value_casted)
            return this
        }
        return this
    }
    public enableTransparentLayer(value: boolean | undefined): this {
        if (this.checkPriority("enableTransparentLayer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableTransparentLayerAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withXComponentStyle(receiver: XComponentAttribute, modifier: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkXComponentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("XComponent")
// export function XComponent(
//     value: XComponentParameter,
//     @memo
//     content_?: () => void,
// ): XComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function XComponent(
    @memo
    style: ((attributes: XComponentAttribute) => void) | undefined,
    value: XComponentParameter,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkXComponentComponent>((): ArkXComponentComponent => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer): void => {
        receiver.setXComponentOptions(value)
        style?.(receiver)
        withXComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("XComponent")
// export function XComponent(
//     options: XComponentOptions,
//     @memo
//     content_?: () => void,
// ): XComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function XComponent(
    @memo
    style: ((attributes: XComponentAttribute) => void) | undefined,
    options: XComponentOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkXComponentComponent>((): ArkXComponentComponent => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer): void => {
        receiver.setXComponentOptions(options)
        style?.(receiver)
        withXComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("XComponent")
// export function XComponent(
//     params: NativeXComponentParameters,
//     @memo
//     content_?: () => void,
// ): XComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function XComponent(
    @memo
    style: ((attributes: XComponentAttribute) => void) | undefined,
    params: NativeXComponentParameters,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkXComponentComponent>((): ArkXComponentComponent => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer): void => {
        receiver.setXComponentOptions(params)
        style?.(receiver)
        withXComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkXComponentSet extends ArkCommonMethodSet implements XComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onLoad_flag?: boolean
    _onLoad0_value?: OnNativeLoadCallback | undefined
    _onDestroy_flag?: boolean
    _onDestroy0_value?: VoidCallback | undefined
    _enableAnalyzer_flag?: boolean
    _enableAnalyzer0_value?: boolean | undefined
    _enableSecure_flag?: boolean
    _enableSecure0_value?: boolean | undefined
    _hdrBrightness_flag?: boolean
    _hdrBrightness0_value?: number | undefined
    _enableTransparentLayer_flag?: boolean
    _enableTransparentLayer0_value?: boolean | undefined
    applyModifierPatch(component: XComponentAttribute): void {
        if (this._onLoad_flag)
            component.onLoad((this._onLoad0_value as OnNativeLoadCallback | undefined))
        if (this._onDestroy_flag)
            component.onDestroy((this._onDestroy0_value as VoidCallback | undefined))
        if (this._enableAnalyzer_flag)
            component.enableAnalyzer((this._enableAnalyzer0_value as boolean | undefined))
        if (this._enableSecure_flag)
            component.enableSecure((this._enableSecure0_value as boolean | undefined))
        if (this._hdrBrightness_flag)
            component.hdrBrightness((this._hdrBrightness0_value as number | undefined))
        if (this._enableTransparentLayer_flag)
            component.enableTransparentLayer((this._enableTransparentLayer0_value as boolean | undefined))
    }
    public onLoad(value: OnNativeLoadCallback | undefined): this {
        this._onLoad_flag = true
        this._onLoad0_value = value
        return this
    }
    public onDestroy(value: VoidCallback | undefined): this {
        this._onDestroy_flag = true
        this._onDestroy0_value = value
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        this._enableAnalyzer_flag = true
        this._enableAnalyzer0_value = value
        return this
    }
    public enableSecure(value: boolean | undefined): this {
        this._enableSecure_flag = true
        this._enableSecure0_value = value
        return this
    }
    public hdrBrightness(value: number | undefined): this {
        this._hdrBrightness_flag = true
        this._hdrBrightness0_value = value
        return this
    }
    public enableTransparentLayer(value: boolean | undefined): this {
        this._enableTransparentLayer_flag = true
        this._enableTransparentLayer0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SurfaceRect_serializer {
    public static write(buffer: SerializerBase, value: SurfaceRect): void {
        let valueSerializer : SerializerBase = buffer
        const value_offsetX  = value.offsetX
        let value_offsetX_type : int32 = RuntimeType.UNDEFINED
        value_offsetX_type = runtimeType(value_offsetX)
        valueSerializer.writeInt8((value_offsetX_type).toChar())
        if ((value_offsetX_type) != (RuntimeType.UNDEFINED)) {
            const value_offsetX_value  = value_offsetX!
            valueSerializer.writeNumber(value_offsetX_value)
        }
        const value_offsetY  = value.offsetY
        let value_offsetY_type : int32 = RuntimeType.UNDEFINED
        value_offsetY_type = runtimeType(value_offsetY)
        valueSerializer.writeInt8((value_offsetY_type).toChar())
        if ((value_offsetY_type) != (RuntimeType.UNDEFINED)) {
            const value_offsetY_value  = value_offsetY!
            valueSerializer.writeNumber(value_offsetY_value)
        }
        const value_surfaceWidth  = value.surfaceWidth
        valueSerializer.writeNumber(value_surfaceWidth)
        const value_surfaceHeight  = value.surfaceHeight
        valueSerializer.writeNumber(value_surfaceHeight)
    }
    public static read(buffer: DeserializerBase): SurfaceRect {
        let valueDeserializer : DeserializerBase = buffer
        const offsetX_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetX_buf : number | undefined
        if ((offsetX_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            offsetX_buf = (valueDeserializer.readNumber() as number)
        }
        const offsetX_result : number | undefined = offsetX_buf
        const offsetY_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetY_buf : number | undefined
        if ((offsetY_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            offsetY_buf = (valueDeserializer.readNumber() as number)
        }
        const offsetY_result : number | undefined = offsetY_buf
        const surfaceWidth_result : number = (valueDeserializer.readNumber() as number)
        const surfaceHeight_result : number = (valueDeserializer.readNumber() as number)
        let value : SurfaceRect = ({offsetX: offsetX_result, offsetY: offsetY_result, surfaceWidth: surfaceWidth_result, surfaceHeight: surfaceHeight_result} as SurfaceRect)
        return value
    }
}
export class SurfaceRotationOptions_serializer {
    public static write(buffer: SerializerBase, value: SurfaceRotationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_lock  = value.lock
        let value_lock_type : int32 = RuntimeType.UNDEFINED
        value_lock_type = runtimeType(value_lock)
        valueSerializer.writeInt8((value_lock_type).toChar())
        if ((value_lock_type) != (RuntimeType.UNDEFINED)) {
            const value_lock_value  = value_lock!
            valueSerializer.writeBoolean(value_lock_value)
        }
    }
    public static read(buffer: DeserializerBase): SurfaceRotationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const lock_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lock_buf : boolean | undefined
        if ((lock_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lock_buf = valueDeserializer.readBoolean()
        }
        const lock_result : boolean | undefined = lock_buf
        let value : SurfaceRotationOptions = ({lock: lock_result} as SurfaceRotationOptions)
        return value
    }
}
export class XComponentController_serializer {
    public static write(buffer: SerializerBase, value: XComponentController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): XComponentController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return XComponentControllerInternal.fromPtr(ptr)
    }
}
export class NativeXComponentParameters_serializer {
    public static write(buffer: SerializerBase, value: NativeXComponentParameters): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(value_type))
        const value_imageAIOptions  = value.imageAIOptions
        let value_imageAIOptions_type : int32 = RuntimeType.UNDEFINED
        value_imageAIOptions_type = runtimeType(value_imageAIOptions)
        valueSerializer.writeInt8((value_imageAIOptions_type).toChar())
        if ((value_imageAIOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_imageAIOptions_value  = value_imageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, value_imageAIOptions_value)
        }
    }
    public static read(buffer: DeserializerBase): NativeXComponentParameters {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const imageAIOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptions_buf : ImageAIOptions | undefined
        if ((imageAIOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            imageAIOptions_buf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptions_result : ImageAIOptions | undefined = imageAIOptions_buf
        let value : NativeXComponentParameters = ({type: type_result, imageAIOptions: imageAIOptions_result} as NativeXComponentParameters)
        return value
    }
}
export class XComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: XComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(value_type))
        const value_controller  = value.controller
        XComponentController_serializer.write(valueSerializer, value_controller)
        const value_imageAIOptions  = value.imageAIOptions
        let value_imageAIOptions_type : int32 = RuntimeType.UNDEFINED
        value_imageAIOptions_type = runtimeType(value_imageAIOptions)
        valueSerializer.writeInt8((value_imageAIOptions_type).toChar())
        if ((value_imageAIOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_imageAIOptions_value  = value_imageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, value_imageAIOptions_value)
        }
        const value_screenId  = value.screenId
        let value_screenId_type : int32 = RuntimeType.UNDEFINED
        value_screenId_type = runtimeType(value_screenId)
        valueSerializer.writeInt8((value_screenId_type).toChar())
        if ((value_screenId_type) != (RuntimeType.UNDEFINED)) {
            const value_screenId_value  = value_screenId!
            valueSerializer.writeNumber(value_screenId_value)
        }
    }
    public static read(buffer: DeserializerBase): XComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const controller_result : XComponentController = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        const imageAIOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptions_buf : ImageAIOptions | undefined
        if ((imageAIOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            imageAIOptions_buf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptions_result : ImageAIOptions | undefined = imageAIOptions_buf
        const screenId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let screenId_buf : number | undefined
        if ((screenId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            screenId_buf = (valueDeserializer.readNumber() as number)
        }
        const screenId_result : number | undefined = screenId_buf
        let value : XComponentOptions = ({type: type_result, controller: controller_result, imageAIOptions: imageAIOptions_result, screenId: screenId_result} as XComponentOptions)
        return value
    }
}
export class XComponentParameter_serializer {
    public static write(buffer: SerializerBase, value: XComponentParameter): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeString(value_id)
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(value_type))
        const value_libraryname  = value.libraryname
        let value_libraryname_type : int32 = RuntimeType.UNDEFINED
        value_libraryname_type = runtimeType(value_libraryname)
        valueSerializer.writeInt8((value_libraryname_type).toChar())
        if ((value_libraryname_type) != (RuntimeType.UNDEFINED)) {
            const value_libraryname_value  = value_libraryname!
            valueSerializer.writeString(value_libraryname_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            XComponentController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): XComponentParameter {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : string = (valueDeserializer.readString() as string)
        const type_result : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const libraryname_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let libraryname_buf : string | undefined
        if ((libraryname_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            libraryname_buf = (valueDeserializer.readString() as string)
        }
        const libraryname_result : string | undefined = libraryname_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : XComponentController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        }
        const controller_result : XComponentController | undefined = controller_buf
        let value : XComponentParameter = ({id: id_result, type: type_result, libraryname: libraryname_result, controller: controller_result} as XComponentParameter)
        return value
    }
}

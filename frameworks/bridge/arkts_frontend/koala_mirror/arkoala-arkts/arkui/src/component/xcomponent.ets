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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from "./imageCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { XComponentType } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        const _peer  = new ArkXComponentPeer(_peerPtr, peerId, 'XComponent', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setOnLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDestroyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setOnDestroy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableSecureAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setEnableSecure(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHdrBrightnessAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setHdrBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableTransparentLayerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}


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
        content_?.()
        receiver.applyAttributesFinish()
    })
}


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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class XComponentModifier extends CommonMethodModifier implements XComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoad_0_0value?: OnNativeLoadCallback | undefined
    _onDestroy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDestroy_0_0value?: VoidCallback | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _enableSecure_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableSecure_0_0value?: boolean | undefined
    _hdrBrightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hdrBrightness_0_0value?: number | undefined
    _enableTransparentLayer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableTransparentLayer_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkXComponentPeer): void {
        super.applyModifierPatch(peer)
        if (this._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as OnNativeLoadCallback | undefined));
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadAttribute((undefined as OnNativeLoadCallback | undefined));
                }
            }
        }
        if (this._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDestroyAttribute((this._onDestroy_0_0value as VoidCallback | undefined));
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDestroyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableSecureAttribute((this._enableSecure_0_0value as boolean | undefined));
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableSecureAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHdrBrightnessAttribute((this._hdrBrightness_0_0value as number | undefined));
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHdrBrightnessAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._enableTransparentLayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableTransparentLayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableTransparentLayerAttribute((this._enableTransparentLayer_0_0value as boolean | undefined));
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableTransparentLayerAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: XComponentModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as OnNativeLoadCallback | undefined));
                }
            }
        }
        if (modifier._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDestroy(modifier._onDestroy_0_0value);
                    break;
                }
                default: {
                    this.onDestroy((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableSecure(modifier._enableSecure_0_0value);
                    break;
                }
                default: {
                    this.enableSecure((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hdrBrightness(modifier._hdrBrightness_0_0value);
                    break;
                }
                default: {
                    this.hdrBrightness((undefined as number | undefined));
                }
            }
        }
        if (modifier._enableTransparentLayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableTransparentLayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableTransparentLayer(modifier._enableTransparentLayer_0_0value);
                    break;
                }
                default: {
                    this.enableTransparentLayer((undefined as boolean | undefined));
                }
            }
        }
    }
    onLoad(value: OnNativeLoadCallback | undefined): this {
        if (((this._onLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoad_0_0value = value
        } else
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDestroy(value: VoidCallback | undefined): this {
        if (((this._onDestroy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDestroy_0_0value = value
        } else
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableSecure(value: boolean | undefined): this {
        if (((this._enableSecure_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableSecure_0_0value) !== (value)))
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableSecure_0_0value = value
        } else
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hdrBrightness(value: number | undefined): this {
        if (((this._hdrBrightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hdrBrightness_0_0value) !== (value)))
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.UPDATE
            this._hdrBrightness_0_0value = value
        } else
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableTransparentLayer(value: boolean | undefined): this {
        if (((this._enableTransparentLayer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableTransparentLayer_0_0value) !== (value)))
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableTransparentLayer_0_0value = value
        } else
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SurfaceRect_serializer {
    public static write(buffer: SerializerBase, value: SurfaceRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffsetX  = value.offsetX
        if (valueHolderForOffsetX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetXTmpValue  = valueHolderForOffsetX!
            valueSerializer.writeNumber(valueHolderForOffsetXTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetY  = value.offsetY
        if (valueHolderForOffsetY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetYTmpValue  = valueHolderForOffsetY!
            valueSerializer.writeNumber(valueHolderForOffsetYTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceWidth  = value.surfaceWidth
        valueSerializer.writeNumber(valueHolderForSurfaceWidth)
        const valueHolderForSurfaceHeight  = value.surfaceHeight
        valueSerializer.writeNumber(valueHolderForSurfaceHeight)
    }
    public static read(buffer: DeserializerBase): SurfaceRect {
        let valueDeserializer : DeserializerBase = buffer
        const offsetXTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetXTmpBuf : number | undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetXTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const offsetXTmpResult : number | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetYTmpBuf : number | undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetYTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const offsetYTmpResult : number | undefined = offsetYTmpBuf
        const surfaceWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const surfaceHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : SurfaceRect = ({offsetX: offsetXTmpResult, offsetY: offsetYTmpResult, surfaceWidth: surfaceWidthTmpResult, surfaceHeight: surfaceHeightTmpResult} as SurfaceRect)
        return value
    }
}
export class SurfaceRotationOptions_serializer {
    public static write(buffer: SerializerBase, value: SurfaceRotationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLock  = value.lock
        if (valueHolderForLock !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLockTmpValue  = valueHolderForLock!
            valueSerializer.writeBoolean(valueHolderForLockTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SurfaceRotationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const lockTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lockTmpBuf : boolean | undefined
        if ((lockTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lockTmpBuf = valueDeserializer.readBoolean()
        }
        const lockTmpResult : boolean | undefined = lockTmpBuf
        let value : SurfaceRotationOptions = ({lock: lockTmpResult} as SurfaceRotationOptions)
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
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(valueHolderForType))
        const valueHolderForImageAIOptions  = value.imageAIOptions
        if (valueHolderForImageAIOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageAIOptionsTmpValue  = valueHolderForImageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, valueHolderForImageAIOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeXComponentParameters {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined
        if ((imageAIOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageAIOptionsTmpBuf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptionsTmpResult : ImageAIOptions | undefined = imageAIOptionsTmpBuf
        let value : NativeXComponentParameters = ({type: typeTmpResult, imageAIOptions: imageAIOptionsTmpResult} as NativeXComponentParameters)
        return value
    }
}
export class XComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: XComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(valueHolderForType))
        const valueHolderForController  = value.controller
        XComponentController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForImageAIOptions  = value.imageAIOptions
        if (valueHolderForImageAIOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageAIOptionsTmpValue  = valueHolderForImageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, valueHolderForImageAIOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScreenId  = value.screenId
        if (valueHolderForScreenId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScreenIdTmpValue  = valueHolderForScreenId!
            valueSerializer.writeNumber(valueHolderForScreenIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): XComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const controllerTmpResult : XComponentController = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined
        if ((imageAIOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageAIOptionsTmpBuf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptionsTmpResult : ImageAIOptions | undefined = imageAIOptionsTmpBuf
        const screenIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let screenIdTmpBuf : number | undefined
        if ((screenIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            screenIdTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const screenIdTmpResult : number | undefined = screenIdTmpBuf
        let value : XComponentOptions = ({type: typeTmpResult, controller: controllerTmpResult, imageAIOptions: imageAIOptionsTmpResult, screenId: screenIdTmpResult} as XComponentOptions)
        return value
    }
}
export class XComponentParameter_serializer {
    public static write(buffer: SerializerBase, value: XComponentParameter): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(valueHolderForType))
        const valueHolderForLibraryname  = value.libraryname
        if (valueHolderForLibraryname !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLibrarynameTmpValue  = valueHolderForLibraryname!
            valueSerializer.writeString(valueHolderForLibrarynameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            XComponentController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): XComponentParameter {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const typeTmpResult : XComponentType = TypeChecker.XComponentType_FromNumeric(valueDeserializer.readInt32())
        const librarynameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let librarynameTmpBuf : string | undefined
        if ((librarynameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            librarynameTmpBuf = (valueDeserializer.readString() as string)
        }
        const librarynameTmpResult : string | undefined = librarynameTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controllerTmpBuf : XComponentController | undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        }
        const controllerTmpResult : XComponentController | undefined = controllerTmpBuf
        let value : XComponentParameter = ({id: idTmpResult, type: typeTmpResult, libraryname: librarynameTmpResult, controller: controllerTmpResult} as XComponentParameter)
        return value
    }
}

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

import { SerializerBase, DeserializerBase, resourceFinalizerRegister, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from './imageCommon'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, ArkCommonMethodComponent } from './common'
import { VoidCallback } from './units'
import { AttributeModifier, hookSetXComponentOptions, hookXComponentAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { XComponentType } from './enums'
import { XComponentModifier } from './../XComponentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class XComponentControllerInternal {
    public static fromPtr(ptr: KPointer): XComponentController {
        return new XComponentController(MaterializedBaseTag.NOP, ptr)
    }
}
export class XComponentController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onSurfaceCreated(): ((breakpoints: string) => void) {
        return this.getOnSurfaceCreated()
    }
    set onSurfaceCreated(onSurfaceCreated: ((breakpoints: string) => void)) {
        this.setOnSurfaceCreated(onSurfaceCreated)
    }
    get onSurfaceChanged(): ((surfaceId: string,rect: SurfaceRect) => void) {
        return this.getOnSurfaceChanged()
    }
    set onSurfaceChanged(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)) {
        this.setOnSurfaceChanged(onSurfaceChanged)
    }
    get onSurfaceDestroyed(): ((breakpoints: string) => void) {
        return this.getOnSurfaceDestroyed()
    }
    set onSurfaceDestroyed(onSurfaceDestroyed: ((breakpoints: string) => void)) {
        this.setOnSurfaceDestroyed(onSurfaceDestroyed)
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, XComponentController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, XComponentController.construct())
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
    private getOnSurfaceCreated(): ((breakpoints: string) => void) {
        return this.getOnSurfaceCreated_serialize()
    }
    private setOnSurfaceCreated(onSurfaceCreated: ((breakpoints: string) => void)): void {
        const onSurfaceCreated_casted = onSurfaceCreated as (((breakpoints: string) => void))
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
    private getOnSurfaceDestroyed(): ((breakpoints: string) => void) {
        return this.getOnSurfaceDestroyed_serialize()
    }
    private setOnSurfaceDestroyed(onSurfaceDestroyed: ((breakpoints: string) => void)): void {
        const onSurfaceDestroyed_casted = onSurfaceDestroyed as (((breakpoints: string) => void))
        this.setOnSurfaceDestroyed_serialize(onSurfaceDestroyed_casted)
        return
    }
    private getXComponentSurfaceId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceId(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : string = (retvalDeserializer.readString() as string)
        return returnResult
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
    private getOnSurfaceCreated_serialize(): ((breakpoints: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceCreated(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferBufResource : CallbackResource = retvalDeserializer.readCallbackResource()
        const bufferBufCall : KPointer = retvalDeserializer.readPointer()
        const bufferBufCallSync : KPointer = retvalDeserializer.readPointer()
        const bufferClosure  = (breakpoints: string):void => {
            const bufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
            bufferBufArgsSerializer.writeInt32(bufferBufResource.resourceId);
            bufferBufArgsSerializer.writePointer(bufferBufCall);
            bufferBufArgsSerializer.writePointer(bufferBufCallSync);
            bufferBufArgsSerializer.writeString(breakpoints);
            InteropNativeModule._CallCallbackSync(10, 569646982, bufferBufArgsSerializer.asBuffer(), bufferBufArgsSerializer.length());
            bufferBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(bufferClosure, bufferBufResource)
        const returnResult : ((breakpoints: string) => void) = bufferClosure
        return returnResult
    }
    private setOnSurfaceCreated_serialize(onSurfaceCreated: ((breakpoints: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceCreated)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceCreated(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceChanged_serialize(): ((surfaceId: string,rect: SurfaceRect) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceChanged(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferBufResource : CallbackResource = retvalDeserializer.readCallbackResource()
        const bufferBufCall : KPointer = retvalDeserializer.readPointer()
        const bufferBufCallSync : KPointer = retvalDeserializer.readPointer()
        const bufferClosure  = (surfaceId: string, rect: SurfaceRect):void => {
            const bufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
            bufferBufArgsSerializer.writeInt32(bufferBufResource.resourceId);
            bufferBufArgsSerializer.writePointer(bufferBufCall);
            bufferBufArgsSerializer.writePointer(bufferBufCallSync);
            bufferBufArgsSerializer.writeString(surfaceId);
            SurfaceRect_serializer.write(bufferBufArgsSerializer, rect);
            InteropNativeModule._CallCallbackSync(10, -1982338800, bufferBufArgsSerializer.asBuffer(), bufferBufArgsSerializer.length());
            bufferBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(bufferClosure, bufferBufResource)
        const returnResult : ((surfaceId: string,rect: SurfaceRect) => void) = bufferClosure
        return returnResult
    }
    private setOnSurfaceChanged_serialize(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceChanged)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceDestroyed_serialize(): ((breakpoints: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceDestroyed(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferBufResource : CallbackResource = retvalDeserializer.readCallbackResource()
        const bufferBufCall : KPointer = retvalDeserializer.readPointer()
        const bufferBufCallSync : KPointer = retvalDeserializer.readPointer()
        const bufferClosure  = (breakpoints: string):void => {
            const bufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
            bufferBufArgsSerializer.writeInt32(bufferBufResource.resourceId);
            bufferBufArgsSerializer.writePointer(bufferBufCall);
            bufferBufArgsSerializer.writePointer(bufferBufCallSync);
            bufferBufArgsSerializer.writeString(breakpoints);
            InteropNativeModule._CallCallbackSync(10, 569646982, bufferBufArgsSerializer.asBuffer(), bufferBufArgsSerializer.length());
            bufferBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(bufferClosure, bufferBufResource)
        const returnResult : ((breakpoints: string) => void) = bufferClosure
        return returnResult
    }
    private setOnSurfaceDestroyed_serialize(onSurfaceDestroyed: ((breakpoints: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceDestroyed)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceDestroyed(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkXComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: XComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkXComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._XComponent_construct(peerId, flags)
        const _peer  = new ArkXComponentPeer(_peerPtr, peerId, 'XComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setXComponentOptionsAttribute(params: XComponentParameters | XComponentOptions | NativeXComponentParameters): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (params instanceof XComponentParameters) {
            thisSerializer.writeInt8((0).toByte())
            const paramsForIdx0  = params as XComponentParameters
            XComponentParameters_serializer.write(thisSerializer, paramsForIdx0)
        } else if (params instanceof XComponentOptions) {
            thisSerializer.writeInt8((1).toByte())
            const paramsForIdx1  = params as XComponentOptions
            XComponentOptions_serializer.write(thisSerializer, paramsForIdx1)
        } else if (params instanceof NativeXComponentParameters) {
            thisSerializer.writeInt8((2).toByte())
            const paramsForIdx2  = params as NativeXComponentParameters
            NativeXComponentParameters_serializer.write(thisSerializer, paramsForIdx2)
        }
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadAttribute(value: VoidCallback | undefined): void {
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
    setHdrBrightnessAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_setHdrBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SurfaceRect {
    offsetX?: double;
    offsetY?: double;
    surfaceWidth: double;
    surfaceHeight: double;
}
export type NativeXComponentPointer = int64;
export interface SurfaceRotationOptions {
    lock?: boolean;
}
export interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
    imageAIOptions?: ImageAIOptions;
    screenId?: int64;
}
export interface NativeXComponentParameters {
    type: XComponentType;
    imageAIOptions?: ImageAIOptions;
}
export interface XComponentAttribute extends CommonMethod {
    setXComponentOptions(params: XComponentParameters | XComponentOptions | NativeXComponentParameters): this {
        throw new Error('Unimplemented method setXComponentOptions')
    }
    onLoad(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onLoad')
    }
    onDestroy(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onDestroy')
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableAnalyzer')
    }
    enableSecure(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableSecure')
    }
    enableTransparentLayer(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableTransparentLayer')
    }
    hdrBrightness(value: double | undefined): this {
        throw new Error('Unimplemented method hdrBrightness')
    }
    attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface XComponentParameters {
    id: string;
    type: XComponentType;
    nativeXComponentHandler: arkui_component_common_Callback<int64, void>;
    controller?: XComponentController;
}

export class ArkXComponentComponent extends ArkCommonMethodComponent implements XComponentAttribute {
    getPeer(): ArkXComponentPeer {
        return (this.peer as ArkXComponentPeer)
    }
    public setXComponentOptions(params: XComponentParameters | XComponentOptions | NativeXComponentParameters): this {
        if (this.checkPriority('setXComponentOptions')) {
            const params_casted = params as (XComponentParameters | XComponentOptions | NativeXComponentParameters)
            this.getPeer()?.setXComponentOptionsAttribute(params_casted)
            this.applyOptionsFinish('XComponentAttribute');
            return this
        }
        return this
    }
    public onLoad(value: VoidCallback | undefined): this {
        if (this.checkPriority('onLoad')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onDestroy(value: VoidCallback | undefined): this {
        if (this.checkPriority('onDestroy')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnDestroyAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority('enableAnalyzer')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public enableSecure(value: boolean | undefined): this {
        if (this.checkPriority('enableSecure')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableSecureAttribute(value_casted)
            return this
        }
        return this
    }
    public enableTransparentLayer(value: boolean | undefined): this {
        if (this.checkPriority('enableTransparentLayer')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableTransparentLayerAttribute(value_casted)
            return this
        }
        return this
    }
    public hdrBrightness(value: double | undefined): this {
        if (this.checkPriority('hdrBrightness')) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setHdrBrightnessAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookXComponentAttributeModifier(this, value);
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
export function XComponentImpl(
    @memo @memo_skip
    style: ((attributes: XComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkXComponentComponent>((): ArkXComponentComponent => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
export class SurfaceRect_serializer {
    public static write(buffer: SerializerBase, value: SurfaceRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffsetX  = value.offsetX
        if (valueHolderForOffsetX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetXTmpValue  = valueHolderForOffsetX!
            valueSerializer.writeFloat64(valueHolderForOffsetXTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetY  = value.offsetY
        if (valueHolderForOffsetY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetYTmpValue  = valueHolderForOffsetY!
            valueSerializer.writeFloat64(valueHolderForOffsetYTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceWidth  = value.surfaceWidth
        valueSerializer.writeFloat64(valueHolderForSurfaceWidth)
        const valueHolderForSurfaceHeight  = value.surfaceHeight
        valueSerializer.writeFloat64(valueHolderForSurfaceHeight)
    }
    public static read(buffer: DeserializerBase): SurfaceRect {
        let valueDeserializer : DeserializerBase = buffer
        const offsetXTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetXTmpBuf : double | undefined = undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetXTmpBuf = valueDeserializer.readFloat64()
        }
        const offsetXTmpResult : double | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetYTmpBuf : double | undefined = undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetYTmpBuf = valueDeserializer.readFloat64()
        }
        const offsetYTmpResult : double | undefined = offsetYTmpBuf
        const surfaceWidthTmpResult : double = valueDeserializer.readFloat64()
        const surfaceHeightTmpResult : double = valueDeserializer.readFloat64()
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
        const lockTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lockTmpBuf : boolean | undefined = undefined
        if ((lockTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lockTmpBuf = valueDeserializer.readBoolean()
        }
        const lockTmpResult : boolean | undefined = lockTmpBuf
        let value : SurfaceRotationOptions = ({lock: lockTmpResult} as SurfaceRotationOptions)
        return value
    }
}
export class XComponentParameters_serializer {
    public static write(buffer: SerializerBase, value: XComponentParameters): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForNativeXComponentHandler  = value.nativeXComponentHandler
        valueSerializer.holdAndWriteCallback(valueHolderForNativeXComponentHandler)
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            XComponentController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): XComponentParameters {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const typeTmpResult : XComponentType = XComponentType.fromValue(valueDeserializer.readInt32())
        const nativeXComponentHandlerTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const nativeXComponentHandlerTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const nativeXComponentHandlerTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const nativeXComponentHandlerTmpBufClosure  = (data: int64):void => {
            const nativeXComponentHandlerTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            nativeXComponentHandlerTmpBufBufArgsSerializer.writeInt32(nativeXComponentHandlerTmpBufBufResource.resourceId);
            nativeXComponentHandlerTmpBufBufArgsSerializer.writePointer(nativeXComponentHandlerTmpBufBufCall);
            nativeXComponentHandlerTmpBufBufArgsSerializer.writePointer(nativeXComponentHandlerTmpBufBufCallSync);
            nativeXComponentHandlerTmpBufBufArgsSerializer.writeInt64(data);
            InteropNativeModule._CallCallbackSync(10, -1073090076, nativeXComponentHandlerTmpBufBufArgsSerializer.asBuffer(), nativeXComponentHandlerTmpBufBufArgsSerializer.length());
            nativeXComponentHandlerTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(nativeXComponentHandlerTmpBufClosure, nativeXComponentHandlerTmpBufBufResource)
        const nativeXComponentHandlerTmpResult : arkui_component_common_Callback<int64, void> = nativeXComponentHandlerTmpBufClosure
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let controllerTmpBuf : XComponentController | undefined = undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        }
        const controllerTmpResult : XComponentController | undefined = controllerTmpBuf
        let value : XComponentParameters = ({id: idTmpResult, type: typeTmpResult, nativeXComponentHandler: nativeXComponentHandlerTmpResult, controller: controllerTmpResult} as XComponentParameters)
        return value
    }
}
export class NativeXComponentParameters_serializer {
    public static write(buffer: SerializerBase, value: NativeXComponentParameters): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
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
        const typeTmpResult : XComponentType = XComponentType.fromValue(valueDeserializer.readInt32())
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined = undefined
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
        valueSerializer.writeInt32(valueHolderForType.valueOf())
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
            valueSerializer.writeInt64(valueHolderForScreenIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): XComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : XComponentType = XComponentType.fromValue(valueDeserializer.readInt32())
        const controllerTmpResult : XComponentController = (XComponentController_serializer.read(valueDeserializer) as XComponentController)
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined = undefined
        if ((imageAIOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageAIOptionsTmpBuf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptionsTmpResult : ImageAIOptions | undefined = imageAIOptionsTmpBuf
        const screenIdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let screenIdTmpBuf : int64 | undefined = undefined
        if ((screenIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            screenIdTmpBuf = valueDeserializer.readInt64()
        }
        const screenIdTmpResult : int64 | undefined = screenIdTmpBuf
        let value : XComponentOptions = ({type: typeTmpResult, controller: controllerTmpResult, imageAIOptions: imageAIOptionsTmpResult, screenId: screenIdTmpResult} as XComponentOptions)
        return value
    }
}

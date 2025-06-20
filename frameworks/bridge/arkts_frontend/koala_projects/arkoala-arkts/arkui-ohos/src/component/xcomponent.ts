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

import { ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VoidCallback } from "./units"
import { XComponentType } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"

export class XComponentControllerInternal {
    public static fromPtr(ptr: KPointer): XComponentController {
        const obj : XComponentController = new XComponentController()
        obj.peer = new Finalizable(ptr, XComponentController.getFinalizer())
        return obj
    }
}
export class XComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_xcomponentcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = XComponentController.ctor_xcomponentcontroller()
        this.peer = new Finalizable(ctorPtr, XComponentController.getFinalizer())
    }
    public holdXComponentCallback() {
        this.setOnSurfaceCreatedCallback(this.onSurfaceCreated);
        this.setOnSurfaceChangedCallback(this.onSurfaceChanged);
        this.setOnSurfaceDestroyedCallback(this.onSurfaceDestroyed);
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
    public setXComponentSurfaceSize(value: Literal_Number_surfaceHeight_surfaceWidth): void {
        const value_casted = value as (Literal_Number_surfaceHeight_surfaceWidth)
        this.setXComponentSurfaceSize_serialize(value_casted)
        return
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
    public onSurfaceCreated(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this.onSurfaceCreated_serialize(surfaceId_casted)
        return
    }
    public onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void {
        const surfaceId_casted = surfaceId as (string)
        const rect_casted = rect as (SurfaceRect)
        this.onSurfaceChanged_serialize(surfaceId_casted, rect_casted)
        return
    }
    public onSurfaceDestroyed(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this.onSurfaceDestroyed_serialize(surfaceId_casted)
        return
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this.stopImageAnalyzer_serialize()
        return
    }
    private setOnSurfaceCreatedCallback(onSurfaceCreatedCallback: ((breakpoints: string) => void)): void {
        const onSurfaceCreatedCallback_casted = onSurfaceCreatedCallback as (((breakpoints: string) => void))
        this.setOnSurfaceCreatedCallback_serialize(onSurfaceCreatedCallback_casted)
        return
    }
    private setOnSurfaceChangedCallback(onSurfaceChangedCallback: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const onSurfaceChangedCallback_casted = onSurfaceChangedCallback as (((surfaceId: string,rect: SurfaceRect) => void))
        this.setOnSurfaceChangedCallback_serialize(onSurfaceChangedCallback_casted)
        return
    }
    private setOnSurfaceDestroyedCallback(onSurfaceDestroyedCallback: ((breakpoints: string) => void)): void {
        const onSurfaceDestroyedCallback_casted = onSurfaceDestroyedCallback as (((breakpoints: string) => void))
        this.setOnSurfaceDestroyedCallback_serialize(onSurfaceDestroyedCallback_casted)
        return
    }
    private getXComponentSurfaceId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceId(this.peer!.ptr)
        return retval
    }
    private getXComponentContext_serialize(): Object {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentContext(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setXComponentSurfaceSize_serialize(value: Literal_Number_surfaceHeight_surfaceWidth): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_surfaceWidth  = value.surfaceWidth
        thisSerializer.writeNumber(value_surfaceWidth)
        const value_surfaceHeight  = value.surfaceHeight
        thisSerializer.writeNumber(value_surfaceHeight)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setXComponentSurfaceRect_serialize(rect: SurfaceRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRect_serialize(): SurfaceRect {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : SurfaceRect = retvalDeserializer.readSurfaceRect()
        return returnResult
    }
    private setXComponentSurfaceRotation_serialize(rotationOptions: SurfaceRotationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRotationOptions(rotationOptions)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRotation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRotation_serialize(): SurfaceRotationOptions {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRotation(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : SurfaceRotationOptions = retvalDeserializer.readSurfaceRotationOptions()
        return returnResult
    }
    private onSurfaceCreated_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceCreated(this.peer!.ptr, surfaceId)
    }
    private onSurfaceChanged_serialize(surfaceId: string, rect: SurfaceRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceChanged(this.peer!.ptr, surfaceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSurfaceDestroyed_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceDestroyed(this.peer!.ptr, surfaceId)
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(config)
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._XComponentController_startImageAnalyzer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._XComponentController_stopImageAnalyzer(this.peer!.ptr)
    }
    private setOnSurfaceCreatedCallback_serialize(onSurfaceCreatedCallback: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceCreatedCallback)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceCreatedCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnSurfaceChangedCallback_serialize(onSurfaceChangedCallback: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceChangedCallback)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceChangedCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnSurfaceDestroyedCallback_serialize(onSurfaceDestroyedCallback: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceDestroyedCallback)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceDestroyedCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkXComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkXComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._XComponent_construct(peerId, flags)
        const _peer  = new ArkXComponentPeer(_peerPtr, peerId, "XComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setXComponentOptions0Attribute(value: Type_XComponentInterface_callable0_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_id  = value.id
        thisSerializer.writeString(value_id)
        const value_type  = value.type
        thisSerializer.writeString(value_type)
        const value_libraryname  = value.libraryname
        let value_libraryname_type : int32 = RuntimeType.UNDEFINED
        value_libraryname_type = runtimeType(value_libraryname)
        thisSerializer.writeInt8(value_libraryname_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_libraryname_type)) {
            const value_libraryname_value  = value_libraryname!
            thisSerializer.writeString(value_libraryname_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        thisSerializer.writeInt8(value_controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            thisSerializer.writeXComponentController(value_controller_value)
        }
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setXComponentOptions1Attribute(value: Type_XComponentInterface_callable1_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_id  = value.id
        thisSerializer.writeString(value_id)
        const value_type  = value.type
        thisSerializer.writeInt32(TypeChecker.XComponentType_ToNumeric(value_type))
        const value_libraryname  = value.libraryname
        let value_libraryname_type : int32 = RuntimeType.UNDEFINED
        value_libraryname_type = runtimeType(value_libraryname)
        thisSerializer.writeInt8(value_libraryname_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_libraryname_type)) {
            const value_libraryname_value  = value_libraryname!
            thisSerializer.writeString(value_libraryname_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        thisSerializer.writeInt8(value_controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            thisSerializer.writeXComponentController(value_controller_value)
        }
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setXComponentOptions2Attribute(options: XComponentOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        options.controller?.holdXComponentCallback();
        thisSerializer.writeXComponentOptions(options)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setXComponentOptions3Attribute(params: NativeXComponentParameters): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNativeXComponentParameters(params)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions3(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadAttribute(value: OnNativeLoadCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_onLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDestroyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_onDestroy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_enableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableSecureAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_enableSecure(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hdrBrightnessAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_hdrBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableTransparentLayerAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._XComponentAttribute_enableTransparentLayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface Literal_Number_surfaceHeight_surfaceWidth {
    surfaceWidth: number;
    surfaceHeight: number;
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
export interface Type_XComponentInterface_callable0_value {
    id: string;
    type: string;
    libraryname?: string;
    controller?: XComponentController;
}
export interface Type_XComponentInterface_callable1_value {
    id: string;
    type: XComponentType;
    libraryname?: string;
    controller?: XComponentController;
}
export interface XComponentParameter {
    id: string;
    type: XComponentType;
    libraryname?: string;
    controller?: XComponentController;
}
export type OnNativeLoadCallback = (event?: Object) => void;
export type Callback_String_SurfaceRect_Void = (surfaceId: string, rect: SurfaceRect) => void;
export interface XComponentAttribute extends CommonMethod {
    onLoad(value: OnNativeLoadCallback | undefined): this
    onDestroy(value: VoidCallback | undefined): this
    enableAnalyzer(value: boolean | undefined): this
    enableSecure(value: boolean | undefined): this
    hdrBrightness(value: number | undefined): this
    enableTransparentLayer(value: boolean | undefined): this
}
export class ArkXComponentStyle extends ArkCommonMethodStyle implements XComponentAttribute {
    onLoad_value?: OnNativeLoadCallback | undefined
    onDestroy_value?: VoidCallback | undefined
    enableAnalyzer_value?: boolean | undefined
    enableSecure_value?: boolean | undefined
    hdrBrightness_value?: number | undefined
    enableTransparentLayer_value?: boolean | undefined
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
}
export class ArkXComponentComponent extends ArkCommonMethodComponent implements XComponentAttribute {
    getPeer(): ArkXComponentPeer {
        return (this.peer as ArkXComponentPeer)
    }
    public setXComponentOptions(value: XComponentParameter | XComponentOptions | NativeXComponentParameters): this {
        if (this.checkPriority("setXComponentOptions")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isXComponentOptions(value, true, true, true, false)) {
                const options_casted = value as (XComponentOptions)
                this.getPeer()?.setXComponentOptions2Attribute(options_casted)
                return this
            }
            if (TypeChecker.isNativeXComponentParameters(value, true, true)) {
                const params_casted = value as (NativeXComponentParameters)
                this.getPeer()?.setXComponentOptions3Attribute(params_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Type_XComponentInterface_callable1_value)
                this.getPeer()?.setXComponentOptions1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onLoad(value: OnNativeLoadCallback | undefined): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as (OnNativeLoadCallback | undefined)
            this.getPeer()?.onLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onDestroy(value: VoidCallback | undefined): this {
        if (this.checkPriority("onDestroy")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onDestroyAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public enableSecure(value: boolean | undefined): this {
        if (this.checkPriority("enableSecure")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableSecureAttribute(value_casted)
            return this
        }
        return this
    }
    public hdrBrightness(value: number | undefined): this {
        if (this.checkPriority("hdrBrightness")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.hdrBrightnessAttribute(value_casted)
            return this
        }
        return this
    }
    public enableTransparentLayer(value: boolean | undefined): this {
        if (this.checkPriority("enableTransparentLayer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableTransparentLayerAttribute(value_casted)
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
export function XComponent(
    /** @memo */
    style: ((attributes: XComponentAttribute) => void) | undefined,
    value: XComponentParameter | XComponentOptions | NativeXComponentParameters,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer) => {
        receiver.setXComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

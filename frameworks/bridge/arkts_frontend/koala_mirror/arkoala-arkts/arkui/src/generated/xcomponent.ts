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

import { Callback_String_Void } from "./grid_row"
import { ImageAnalyzerConfig, ImageAIOptions } from "./image_common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { VoidCallback } from "./units"
import { XComponentType } from "./enums"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
    get onSurfaceCreated(): ((breakpoints: string) => void) {
        throw new Error("Not implemented")
    }
    set onSurfaceCreated(onSurfaceCreated: ((breakpoints: string) => void)) {
        this.setOnSurfaceCreated(onSurfaceCreated)
    }
    get onSurfaceChanged(): ((surfaceId: string,rect: SurfaceRect) => void) {
        throw new Error("Not implemented")
    }
    set onSurfaceChanged(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)) {
        this.setOnSurfaceChanged(onSurfaceChanged)
    }
    get onSurfaceDestroyed(): ((breakpoints: string) => void) {
        throw new Error("Not implemented")
    }
    set onSurfaceDestroyed(onSurfaceDestroyed: ((breakpoints: string) => void)) {
        this.setOnSurfaceDestroyed(onSurfaceDestroyed)
    }
    static ctor_xcomponentcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = XComponentController.ctor_xcomponentcontroller()
        this.peer = new Finalizable(ctorPtr, XComponentController.getFinalizer())
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : SurfaceRotationOptions = retvalDeserializer.readSurfaceRotationOptions()
        return returnResult
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
    private getOnSurfaceCreated_serialize(): ((breakpoints: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceCreated(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceCreated_serialize(onSurfaceCreated: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceCreated)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceCreated(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceChanged_serialize(): ((surfaceId: string,rect: SurfaceRect) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceChanged(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceChanged_serialize(onSurfaceChanged: ((surfaceId: string,rect: SurfaceRect) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onSurfaceChanged)
        ArkUIGeneratedNativeModule._XComponentController_setOnSurfaceChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnSurfaceDestroyed_serialize(): ((breakpoints: string) => void) {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getOnSurfaceDestroyed(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnSurfaceDestroyed_serialize(onSurfaceDestroyed: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
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
        thisSerializer.writeXComponentOptions(options)
        ArkUIGeneratedNativeModule._XComponentInterface_setXComponentOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadAttribute(value: OnNativeLoadCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._XComponentAttribute_onLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDestroyAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._XComponentAttribute_onDestroy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._XComponentAttribute_enableAnalyzer(this.peer.ptr, value ? 1 : 0)
    }
    enableSecureAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._XComponentAttribute_enableSecure(this.peer.ptr, value ? 1 : 0)
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
export type Callback_String_SurfaceRect_Void = (surfaceId: string, rect: SurfaceRect) => void;
export interface Literal_Number_surfaceHeight_surfaceWidth {
    surfaceWidth: number;
    surfaceHeight: number;
}
export interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
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

export type OnNativeLoadCallback = (event?: Object) => void;
export interface XComponentAttribute extends CommonMethod {
    onLoad(value: OnNativeLoadCallback): this
    onDestroy(value: VoidCallback): this
    enableAnalyzer(value: boolean): this
    enableSecure(value: boolean): this
    attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIXComponentAttribute extends UICommonMethod {
    /** @memo */
    onLoad(value: OnNativeLoadCallback): this
    /** @memo */
    onDestroy(value: VoidCallback): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    enableSecure(value: boolean): this
    /** @memo */
    attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkXComponentStyle extends ArkCommonMethodStyle implements XComponentAttribute {
    onLoad_value?: OnNativeLoadCallback
    onDestroy_value?: VoidCallback
    enableAnalyzer_value?: boolean
    enableSecure_value?: boolean
    public onLoad(value: OnNativeLoadCallback): this {
        return this
    }
    public onDestroy(value: VoidCallback): this {
        return this
    }
    public enableAnalyzer(value: boolean): this {
        return this
    }
    public enableSecure(value: boolean): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkXComponentComponent extends ArkCommonMethodComponent implements UIXComponentAttribute {
    getPeer(): ArkXComponentPeer {
        return (this.peer as ArkXComponentPeer)
    }
    /** @memo */
    public setXComponentOptions(value: Type_XComponentInterface_callable0_value | Type_XComponentInterface_callable1_value | XComponentOptions): this {
        if (this.checkPriority("setXComponentOptions")) {
            const value_type = runtimeType(value)
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Type_XComponentInterface_callable0_value)
                this.getPeer()?.setXComponentOptions0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Type_XComponentInterface_callable1_value)
                this.getPeer()?.setXComponentOptions1Attribute(value_casted)
                return this
            }
            if (TypeChecker.isXComponentOptions(value, true, true, false)) {
                const options_casted = value as (XComponentOptions)
                this.getPeer()?.setXComponentOptions2Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onLoad(value: OnNativeLoadCallback): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as (OnNativeLoadCallback)
            this.getPeer()?.onLoadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDestroy(value: VoidCallback): this {
        if (this.checkPriority("onDestroy")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onDestroyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableSecure(value: boolean): this {
        if (this.checkPriority("enableSecure")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableSecureAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkXComponent(
    /** @memo */
    style: ((attributes: UIXComponentAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value: Type_XComponentInterface_callable0_value | Type_XComponentInterface_callable1_value | XComponentOptions,
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

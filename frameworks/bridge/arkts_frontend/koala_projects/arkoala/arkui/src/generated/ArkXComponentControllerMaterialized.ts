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

import { SurfaceRect, SurfaceRotationOptions } from "./ArkXcomponentInterfaces"
import { ImageAnalyzerConfig, ImageAnalyzerType } from "./ArkImageCommonInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class XComponentControllerInternal {
    public static fromPtr(ptr: KPointer): XComponentController {
        const obj: XComponentController = new XComponentController()
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
        const retval = ArkUIGeneratedNativeModule._XComponentController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = XComponentController.ctor_xcomponentcontroller()
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
    public setXComponentSurfaceSize(value: { surfaceWidth: number, surfaceHeight: number }): void {
        const value_casted = value as ({ surfaceWidth: number, surfaceHeight: number })
        this?.setXComponentSurfaceSize_serialize(value_casted)
        return
    }
    public setXComponentSurfaceRect(rect: SurfaceRect): void {
        const rect_casted = rect as (SurfaceRect)
        this?.setXComponentSurfaceRect_serialize(rect_casted)
        return
    }
    public getXComponentSurfaceRect(): SurfaceRect {
        return this.getXComponentSurfaceRect_serialize()
    }
    public setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void {
        const rotationOptions_casted = rotationOptions as (SurfaceRotationOptions)
        this?.setXComponentSurfaceRotation_serialize(rotationOptions_casted)
        return
    }
    public getXComponentSurfaceRotation(): SurfaceRotationOptions {
        return this.getXComponentSurfaceRotation_serialize()
    }
    public onSurfaceCreated(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this?.onSurfaceCreated_serialize(surfaceId_casted)
        return
    }
    public onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void {
        const surfaceId_casted = surfaceId as (string)
        const rect_casted = rect as (SurfaceRect)
        this?.onSurfaceChanged_serialize(surfaceId_casted, rect_casted)
        return
    }
    public onSurfaceDestroyed(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this?.onSurfaceDestroyed_serialize(surfaceId_casted)
        return
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this?.stopImageAnalyzer_serialize()
        return
    }
    private getXComponentSurfaceId_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceId(this.peer!.ptr)
        return retval
    }
    private getXComponentContext_serialize(): Object {
        const retval = ArkUIGeneratedNativeModule._XComponentController_getXComponentContext(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setXComponentSurfaceSize_serialize(value: { surfaceWidth: number, surfaceHeight: number }): void {
        const thisSerializer: Serializer = Serializer.hold()
        const value_surfaceWidth = value.surfaceWidth
        thisSerializer.writeNumber(value_surfaceWidth)
        const value_surfaceHeight = value.surfaceHeight
        thisSerializer.writeNumber(value_surfaceHeight)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceSize(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setXComponentSurfaceRect_serialize(rect: SurfaceRect): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRect(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRect_serialize(): SurfaceRect {
        const retval = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRect(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: SurfaceRect = retvalDeserializer.readSurfaceRect()
        return returnResult
    }
    private setXComponentSurfaceRotation_serialize(rotationOptions: SurfaceRotationOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRotationOptions(rotationOptions)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRotation(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRotation_serialize(): SurfaceRotationOptions {
        const retval = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRotation(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: SurfaceRotationOptions = retvalDeserializer.readSurfaceRotationOptions()
        return returnResult
    }
    private onSurfaceCreated_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceCreated(this.peer!.ptr, surfaceId)
    }
    private onSurfaceChanged_serialize(surfaceId: string, rect: SurfaceRect): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceChanged(this.peer!.ptr, surfaceId, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSurfaceDestroyed_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceDestroyed(this.peer!.ptr, surfaceId)
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(config)
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._XComponentController_startImageAnalyzer(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._XComponentController_stopImageAnalyzer(this.peer!.ptr)
    }
}

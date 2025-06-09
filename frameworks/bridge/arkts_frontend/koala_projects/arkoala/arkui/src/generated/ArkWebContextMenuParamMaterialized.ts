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

import { ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType } from "./ArkWebInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class WebContextMenuParamInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuParam {
        const obj: WebContextMenuParam = new WebContextMenuParam()
        obj.peer = new Finalizable(ptr, WebContextMenuParam.getFinalizer())
        return obj
    }
}
export class WebContextMenuParam implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcontextmenuparam(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebContextMenuParam.ctor_webcontextmenuparam()
        this.peer = new Finalizable(ctorPtr, WebContextMenuParam.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebContextMenuParam_getFinalizer()
    }
    public x(): number {
        return this.x_serialize()
    }
    public y(): number {
        return this.y_serialize()
    }
    public getLinkUrl(): string {
        return this.getLinkUrl_serialize()
    }
    public getUnfilteredLinkUrl(): string {
        return this.getUnfilteredLinkUrl_serialize()
    }
    public getSourceUrl(): string {
        return this.getSourceUrl_serialize()
    }
    public existsImageContents(): boolean {
        return this.existsImageContents_serialize()
    }
    public getMediaType(): ContextMenuMediaType {
        return this.getMediaType_serialize()
    }
    public getSelectionText(): string {
        return this.getSelectionText_serialize()
    }
    public getSourceType(): ContextMenuSourceType {
        return this.getSourceType_serialize()
    }
    public getInputFieldType(): ContextMenuInputFieldType {
        return this.getInputFieldType_serialize()
    }
    public isEditable(): boolean {
        return this.isEditable_serialize()
    }
    public getEditStateFlags(): number {
        return this.getEditStateFlags_serialize()
    }
    public getPreviewWidth(): number {
        return this.getPreviewWidth_serialize()
    }
    public getPreviewHeight(): number {
        return this.getPreviewHeight_serialize()
    }
    private x_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_x(this.peer!.ptr)
        return retval
    }
    private y_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_y(this.peer!.ptr)
        return retval
    }
    private getLinkUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getLinkUrl(this.peer!.ptr)
        return retval
    }
    private getUnfilteredLinkUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getUnfilteredLinkUrl(this.peer!.ptr)
        return retval
    }
    private getSourceUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceUrl(this.peer!.ptr)
        return retval
    }
    private existsImageContents_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_existsImageContents(this.peer!.ptr)
        return retval
    }
    private getMediaType_serialize(): ContextMenuMediaType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getMediaType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getSelectionText_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSelectionText(this.peer!.ptr)
        return retval
    }
    private getSourceType_serialize(): ContextMenuSourceType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getInputFieldType_serialize(): ContextMenuInputFieldType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getInputFieldType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private isEditable_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_isEditable(this.peer!.ptr)
        return retval
    }
    private getEditStateFlags_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getEditStateFlags(this.peer!.ptr)
        return retval
    }
    private getPreviewWidth_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewWidth(this.peer!.ptr)
        return retval
    }
    private getPreviewHeight_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewHeight(this.peer!.ptr)
        return retval
    }
}

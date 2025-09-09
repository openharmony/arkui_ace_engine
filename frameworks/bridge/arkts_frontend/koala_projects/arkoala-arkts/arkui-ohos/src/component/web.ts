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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { WebviewController, WebviewControllerInternal } from "./arkui-external"
import { WebviewController as WebviewControllerAni } from "#external"
import { Resource } from "global.resource"
import { Callback_String_Void } from "./gridRow"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, Callback_KeyEvent_Boolean, KeyEvent, NestedScrollOptions, CustomBuilder, TouchEvent, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CopyOptions, NestedScrollMode } from "./enums"
import { EditMenuOptions, MenuType } from "./textCommon"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Position, ResourceStr } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { PreviewMenuOptions } from "./richEditor"
import { ArkUIAniModule } from "arkui.ani"

export class WebKeyboardControllerInternal {
    public static fromPtr(ptr: KPointer): WebKeyboardController {
        const obj : WebKeyboardController = new WebKeyboardController()
        obj.peer = new Finalizable(ptr, WebKeyboardController.getFinalizer())
        return obj
    }
}
export class WebKeyboardController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webkeyboardcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebKeyboardController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebKeyboardController.ctor_webkeyboardcontroller()
        this.peer = new Finalizable(ctorPtr, WebKeyboardController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebKeyboardController_getFinalizer()
    }
    public insertText(text: string): void {
        const text_casted = text as (string)
        this.insertText_serialize(text_casted)
        return
    }
    public deleteForward(length: number): void {
        const length_casted = length as (number)
        this.deleteForward_serialize(length_casted)
        return
    }
    public deleteBackward(length: number): void {
        const length_casted = length as (number)
        this.deleteBackward_serialize(length_casted)
        return
    }
    public sendFunctionKey(key: number): void {
        const key_casted = key as (number)
        this.sendFunctionKey_serialize(key_casted)
        return
    }
    public close(): void {
        this.close_serialize()
        return
    }
    private insertText_serialize(text: string): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_insertText(this.peer!.ptr, text)
    }
    private deleteForward_serialize(length: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteForward(this.peer!.ptr, length)
    }
    private deleteBackward_serialize(length: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteBackward(this.peer!.ptr, length)
    }
    private sendFunctionKey_serialize(key: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_sendFunctionKey(this.peer!.ptr, key)
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_close(this.peer!.ptr)
    }
}
export class FullScreenExitHandlerInternal {
    public static fromPtr(ptr: KPointer): FullScreenExitHandler {
        const obj : FullScreenExitHandler = new FullScreenExitHandler()
        obj.peer = new Finalizable(ptr, FullScreenExitHandler.getFinalizer())
        return obj
    }
}
export class FullScreenExitHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_fullscreenexithandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FullScreenExitHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FullScreenExitHandler.ctor_fullscreenexithandler()
        this.peer = new Finalizable(ctorPtr, FullScreenExitHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FullScreenExitHandler_getFinalizer()
    }
    public exitFullScreen(): void {
        this.exitFullScreen_serialize()
        return
    }
    private exitFullScreen_serialize(): void {
        ArkUIGeneratedNativeModule._FullScreenExitHandler_exitFullScreen(this.peer!.ptr)
    }
}
export class FileSelectorParamInternal {
    public static fromPtr(ptr: KPointer): FileSelectorParam {
        const obj : FileSelectorParam = new FileSelectorParam()
        obj.peer = new Finalizable(ptr, FileSelectorParam.getFinalizer())
        return obj
    }
}
export class FileSelectorParam implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_fileselectorparam(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FileSelectorParam.ctor_fileselectorparam()
        this.peer = new Finalizable(ctorPtr, FileSelectorParam.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FileSelectorParam_getFinalizer()
    }
    public getTitle(): string {
        return this.getTitle_serialize()
    }
    public getMode(): FileSelectorMode {
        return this.getMode_serialize()
    }
    public getAcceptType(): Array<string> {
        return this.getAcceptType_serialize()
    }
    public isCapture(): boolean {
        return this.isCapture_serialize()
    }
    public getMimeTypes(): Array<string> {
        return this.getMimeTypes_serialize()
    }
    private getTitle_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getTitle(this.peer!.ptr)
        return retval
    }
    private getMode_serialize(): FileSelectorMode {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getMode(this.peer!.ptr)
        return TypeChecker.FileSelectorMode_FromNumeric(retval)
    }
    private getAcceptType_serialize(): Array<string> {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptType(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private isCapture_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_isCapture(this.peer!.ptr)
        return retval
    }
    private getMimeTypes_serialize(): Array<string> {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getMimeTypes(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
}
export class JsResultInternal {
    public static fromPtr(ptr: KPointer): JsResult {
        const obj : JsResult = new JsResult()
        obj.peer = new Finalizable(ptr, JsResult.getFinalizer())
        return obj
    }
}
export class JsResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_jsresult(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._JsResult_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = JsResult.ctor_jsresult()
        this.peer = new Finalizable(ctorPtr, JsResult.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._JsResult_getFinalizer()
    }
    public handleCancel(): void {
        this.handleCancel_serialize()
        return
    }
    public handleConfirm(): void {
        this.handleConfirm_serialize()
        return
    }
    public handlePromptConfirm(result: string): void {
        const result_casted = result as (string)
        this.handlePromptConfirm_serialize(result_casted)
        return
    }
    private handleCancel_serialize(): void {
        ArkUIGeneratedNativeModule._JsResult_handleCancel(this.peer!.ptr)
    }
    private handleConfirm_serialize(): void {
        ArkUIGeneratedNativeModule._JsResult_handleConfirm(this.peer!.ptr)
    }
    private handlePromptConfirm_serialize(result: string): void {
        ArkUIGeneratedNativeModule._JsResult_handlePromptConfirm(this.peer!.ptr, result)
    }
}
export class FileSelectorResultInternal {
    public static fromPtr(ptr: KPointer): FileSelectorResult {
        const obj : FileSelectorResult = new FileSelectorResult()
        obj.peer = new Finalizable(ptr, FileSelectorResult.getFinalizer())
        return obj
    }
}
export class FileSelectorResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_fileselectorresult(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorResult_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FileSelectorResult.ctor_fileselectorresult()
        this.peer = new Finalizable(ctorPtr, FileSelectorResult.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FileSelectorResult_getFinalizer()
    }
    public handleFileList(fileList: Array<string>): void {
        const fileList_casted = fileList as (Array<string>)
        this.handleFileList_serialize(fileList_casted)
        return
    }
    private handleFileList_serialize(fileList: Array<string>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(fileList.length as int32)
        for (let i = 0; i < fileList.length; i++) {
            const fileList_element : string = fileList[i]
            thisSerializer.writeString(fileList_element)
        }
        ArkUIGeneratedNativeModule._FileSelectorResult_handleFileList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class HttpAuthHandlerInternal {
    public static fromPtr(ptr: KPointer): HttpAuthHandler {
        const obj : HttpAuthHandler = new HttpAuthHandler()
        obj.peer = new Finalizable(ptr, HttpAuthHandler.getFinalizer())
        return obj
    }
}
export class HttpAuthHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_httpauthhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._HttpAuthHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = HttpAuthHandler.ctor_httpauthhandler()
        this.peer = new Finalizable(ctorPtr, HttpAuthHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HttpAuthHandler_getFinalizer()
    }
    public confirm(userName: string, password: string): boolean {
        const userName_casted = userName as (string)
        const password_casted = password as (string)
        return this.confirm_serialize(userName_casted, password_casted)
    }
    public cancel(): void {
        this.cancel_serialize()
        return
    }
    public isHttpAuthInfoSaved(): boolean {
        return this.isHttpAuthInfoSaved_serialize()
    }
    private confirm_serialize(userName: string, password: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._HttpAuthHandler_confirm(this.peer!.ptr, userName, password)
        return retval
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._HttpAuthHandler_cancel(this.peer!.ptr)
    }
    private isHttpAuthInfoSaved_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._HttpAuthHandler_isHttpAuthInfoSaved(this.peer!.ptr)
        return retval
    }
}
export class SslErrorHandlerInternal {
    public static fromPtr(ptr: KPointer): SslErrorHandler {
        const obj : SslErrorHandler = new SslErrorHandler()
        obj.peer = new Finalizable(ptr, SslErrorHandler.getFinalizer())
        return obj
    }
}
export class SslErrorHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_sslerrorhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SslErrorHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SslErrorHandler.ctor_sslerrorhandler()
        this.peer = new Finalizable(ctorPtr, SslErrorHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SslErrorHandler_getFinalizer()
    }
    public handleConfirm(): void {
        this.handleConfirm_serialize()
        return
    }
    public handleCancel(): void {
        this.handleCancel_serialize()
        return
    }
    private handleConfirm_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleConfirm(this.peer!.ptr)
    }
    private handleCancel_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleCancel(this.peer!.ptr)
    }
}
export class ClientAuthenticationHandlerInternal {
    public static fromPtr(ptr: KPointer): ClientAuthenticationHandler {
        const obj : ClientAuthenticationHandler = new ClientAuthenticationHandler()
        obj.peer = new Finalizable(ptr, ClientAuthenticationHandler.getFinalizer())
        return obj
    }
}
export class ClientAuthenticationHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_clientauthenticationhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ClientAuthenticationHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ClientAuthenticationHandler.ctor_clientauthenticationhandler()
        this.peer = new Finalizable(ctorPtr, ClientAuthenticationHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ClientAuthenticationHandler_getFinalizer()
    }
    public confirm(priKeyFile: string, certChainFile?: string): void {
        const priKeyFile_type = runtimeType(priKeyFile)
        const certChainFile_type = runtimeType(certChainFile)
        const authUri_casted = priKeyFile as (string)
        this.confirm1_serialize(authUri_casted)
        return
    }
    public cancel(): void {
        this.cancel_serialize()
        return
    }
    public ignore(): void {
        this.ignore_serialize()
        return
    }
    private confirm0_serialize(priKeyFile: string, certChainFile: string): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_confirm0(this.peer!.ptr, priKeyFile, certChainFile)
    }
    private confirm1_serialize(authUri: string): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_confirm1(this.peer!.ptr, authUri)
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_cancel(this.peer!.ptr)
    }
    private ignore_serialize(): void {
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_ignore(this.peer!.ptr)
    }
}
export class PermissionRequestInternal {
    public static fromPtr(ptr: KPointer): PermissionRequest {
        const obj : PermissionRequest = new PermissionRequest()
        obj.peer = new Finalizable(ptr, PermissionRequest.getFinalizer())
        return obj
    }
}
export class PermissionRequest implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_permissionrequest(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PermissionRequest_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PermissionRequest.ctor_permissionrequest()
        this.peer = new Finalizable(ctorPtr, PermissionRequest.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PermissionRequest_getFinalizer()
    }
    public deny(): void {
        this.deny_serialize()
        return
    }
    public getOrigin(): string {
        return this.getOrigin_serialize()
    }
    public getAccessibleResource(): Array<string> {
        return this.getAccessibleResource_serialize()
    }
    public grant(resources: Array<string>): void {
        const resources_casted = resources as (Array<string>)
        this.grant_serialize(resources_casted)
        return
    }
    private deny_serialize(): void {
        ArkUIGeneratedNativeModule._PermissionRequest_deny(this.peer!.ptr)
    }
    private getOrigin_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._PermissionRequest_getOrigin(this.peer!.ptr)
        return retval
    }
    private getAccessibleResource_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._PermissionRequest_getAccessibleResource(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private grant_serialize(resources: Array<string>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(resources.length as int32)
        for (let i = 0; i < resources.length; i++) {
            const resources_element : string = resources[i]
            thisSerializer.writeString(resources_element)
        }
        ArkUIGeneratedNativeModule._PermissionRequest_grant(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScreenCaptureHandlerInternal {
    public static fromPtr(ptr: KPointer): ScreenCaptureHandler {
        const obj : ScreenCaptureHandler = new ScreenCaptureHandler()
        obj.peer = new Finalizable(ptr, ScreenCaptureHandler.getFinalizer())
        return obj
    }
}
export class ScreenCaptureHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_screencapturehandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScreenCaptureHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ScreenCaptureHandler.ctor_screencapturehandler()
        this.peer = new Finalizable(ctorPtr, ScreenCaptureHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScreenCaptureHandler_getFinalizer()
    }
    public getOrigin(): string {
        return this.getOrigin_serialize()
    }
    public grant(config: ScreenCaptureConfig): void {
        const config_casted = config as (ScreenCaptureConfig)
        this.grant_serialize(config_casted)
        return
    }
    public deny(): void {
        this.deny_serialize()
        return
    }
    private getOrigin_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._ScreenCaptureHandler_getOrigin(this.peer!.ptr)
        return retval
    }
    private grant_serialize(config: ScreenCaptureConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScreenCaptureConfig(config)
        ArkUIGeneratedNativeModule._ScreenCaptureHandler_grant(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deny_serialize(): void {
        ArkUIGeneratedNativeModule._ScreenCaptureHandler_deny(this.peer!.ptr)
    }
}
export class DataResubmissionHandlerInternal {
    public static fromPtr(ptr: KPointer): DataResubmissionHandler {
        const obj : DataResubmissionHandler = new DataResubmissionHandler()
        obj.peer = new Finalizable(ptr, DataResubmissionHandler.getFinalizer())
        return obj
    }
}
export class DataResubmissionHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_dataresubmissionhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DataResubmissionHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = DataResubmissionHandler.ctor_dataresubmissionhandler()
        this.peer = new Finalizable(ctorPtr, DataResubmissionHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DataResubmissionHandler_getFinalizer()
    }
    public resend(): void {
        this.resend_serialize()
        return
    }
    public cancel(): void {
        this.cancel_serialize()
        return
    }
    private resend_serialize(): void {
        ArkUIGeneratedNativeModule._DataResubmissionHandler_resend(this.peer!.ptr)
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._DataResubmissionHandler_cancel(this.peer!.ptr)
    }
}
export class ControllerHandlerInternal {
    public static fromPtr(ptr: KPointer): ControllerHandler {
        const obj : ControllerHandler = new ControllerHandler()
        obj.peer = new Finalizable(ptr, ControllerHandler.getFinalizer())
        return obj
    }
}
export class ControllerHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_controllerhandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ControllerHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ControllerHandler.ctor_controllerhandler()
        this.peer = new Finalizable(ctorPtr, ControllerHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ControllerHandler_getFinalizer()
    }
    public setWebController(controller: WebviewControllerAni): void {
        const controller_casted = controller as (WebviewControllerAni)
        ArkUIAniModule._Web_SetWebController_ControllerHandler(this.peer!.ptr, controller_casted);
        return
    }
    private setWebController_serialize(controller: WebviewController): void {
        ArkUIGeneratedNativeModule._ControllerHandler_setWebController(this.peer!.ptr, toPeerPtr(controller))
    }
}
export class WebContextMenuParamInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuParam {
        const obj : WebContextMenuParam = new WebContextMenuParam()
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
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebContextMenuParam.ctor_webcontextmenuparam()
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
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_x(this.peer!.ptr)
        return retval
    }
    private y_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_y(this.peer!.ptr)
        return retval
    }
    private getLinkUrl_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getLinkUrl(this.peer!.ptr)
        return retval
    }
    private getUnfilteredLinkUrl_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getUnfilteredLinkUrl(this.peer!.ptr)
        return retval
    }
    private getSourceUrl_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceUrl(this.peer!.ptr)
        return retval
    }
    private existsImageContents_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_existsImageContents(this.peer!.ptr)
        return retval
    }
    private getMediaType_serialize(): ContextMenuMediaType {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getMediaType(this.peer!.ptr)
        return TypeChecker.ContextMenuMediaType_FromNumeric(retval)
    }
    private getSelectionText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getSelectionText(this.peer!.ptr)
        return retval
    }
    private getSourceType_serialize(): ContextMenuSourceType {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceType(this.peer!.ptr)
        return TypeChecker.ContextMenuSourceType_FromNumeric(retval)
    }
    private getInputFieldType_serialize(): ContextMenuInputFieldType {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getInputFieldType(this.peer!.ptr)
        return TypeChecker.ContextMenuInputFieldType_FromNumeric(retval)
    }
    private isEditable_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_isEditable(this.peer!.ptr)
        return retval
    }
    private getEditStateFlags_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getEditStateFlags(this.peer!.ptr)
        return retval
    }
    private getPreviewWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewWidth(this.peer!.ptr)
        return retval
    }
    private getPreviewHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewHeight(this.peer!.ptr)
        return retval
    }
}
export class WebContextMenuResultInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuResult {
        const obj : WebContextMenuResult = new WebContextMenuResult()
        obj.peer = new Finalizable(ptr, WebContextMenuResult.getFinalizer())
        return obj
    }
}
export class WebContextMenuResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcontextmenuresult(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuResult_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebContextMenuResult.ctor_webcontextmenuresult()
        this.peer = new Finalizable(ctorPtr, WebContextMenuResult.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebContextMenuResult_getFinalizer()
    }
    public closeContextMenu(): void {
        this.closeContextMenu_serialize()
        return
    }
    public copyImage(): void {
        this.copyImage_serialize()
        return
    }
    public copy(): void {
        this.copy_serialize()
        return
    }
    public paste(): void {
        this.paste_serialize()
        return
    }
    public cut(): void {
        this.cut_serialize()
        return
    }
    public selectAll(): void {
        this.selectAll_serialize()
        return
    }
    private closeContextMenu_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_closeContextMenu(this.peer!.ptr)
    }
    private copyImage_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_copyImage(this.peer!.ptr)
    }
    private copy_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_copy(this.peer!.ptr)
    }
    private paste_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_paste(this.peer!.ptr)
    }
    private cut_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_cut(this.peer!.ptr)
    }
    private selectAll_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_selectAll(this.peer!.ptr)
    }
}
export class ConsoleMessageInternal {
    public static fromPtr(ptr: KPointer): ConsoleMessage {
        const obj : ConsoleMessage = new ConsoleMessage(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ConsoleMessage.getFinalizer())
        return obj
    }
}
export class ConsoleMessage implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_consolemessage(message: string, sourceId: string, lineNumber: number, messageLevel: MessageLevel): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_ctor(message, sourceId, lineNumber, TypeChecker.MessageLevel_ToNumeric(messageLevel))
        return retval
    }
    constructor(message?: string, sourceId?: string, lineNumber?: number, messageLevel?: MessageLevel) {
        if (((message) !== (undefined)) || ((sourceId) !== (undefined)) || ((lineNumber) !== (undefined)) || ((messageLevel) !== (undefined)))
        {
            const ctorPtr : KPointer = ConsoleMessage.ctor_consolemessage((message)!, (sourceId)!, (lineNumber)!, (messageLevel)!)
            this.peer = new Finalizable(ctorPtr, ConsoleMessage.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ConsoleMessage_getFinalizer()
    }
    public getMessage(): string {
        return this.getMessage_serialize()
    }
    public getSourceId(): string {
        return this.getSourceId_serialize()
    }
    public getLineNumber(): number {
        return this.getLineNumber_serialize()
    }
    public getMessageLevel(): MessageLevel {
        return this.getMessageLevel_serialize()
    }
    private getMessage_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_getMessage(this.peer!.ptr)
        return retval
    }
    private getSourceId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_getSourceId(this.peer!.ptr)
        return retval
    }
    private getLineNumber_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_getLineNumber(this.peer!.ptr)
        return retval
    }
    private getMessageLevel_serialize(): MessageLevel {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_getMessageLevel(this.peer!.ptr)
        return TypeChecker.MessageLevel_FromNumeric(retval)
    }
}
export class WebResourceRequestInternal {
    public static fromPtr(ptr: KPointer): WebResourceRequest {
        const obj : WebResourceRequest = new WebResourceRequest()
        obj.peer = new Finalizable(ptr, WebResourceRequest.getFinalizer())
        return obj
    }
}
export class WebResourceRequest implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourcerequest(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebResourceRequest.ctor_webresourcerequest()
        this.peer = new Finalizable(ctorPtr, WebResourceRequest.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceRequest_getFinalizer()
    }
    public getRequestHeader(): Array<Header> {
        return this.getRequestHeader_serialize()
    }
    public getRequestUrl(): string {
        return this.getRequestUrl_serialize()
    }
    public isRequestGesture(): boolean {
        return this.isRequestGesture_serialize()
    }
    public isMainFrame(): boolean {
        return this.isMainFrame_serialize()
    }
    public isRedirect(): boolean {
        return this.isRedirect_serialize()
    }
    public getRequestMethod(): string {
        return this.getRequestMethod_serialize()
    }
    private getRequestHeader_serialize(): Array<Header> {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestHeader(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHeader()
        }
        const returnResult : Array<Header> = buffer
        return returnResult
    }
    private getRequestUrl_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestUrl(this.peer!.ptr)
        return retval
    }
    private isRequestGesture_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_isRequestGesture(this.peer!.ptr)
        return retval
    }
    private isMainFrame_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_isMainFrame(this.peer!.ptr)
        return retval
    }
    private isRedirect_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_isRedirect(this.peer!.ptr)
        return retval
    }
    private getRequestMethod_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestMethod(this.peer!.ptr)
        return retval
    }
}
export class WebResourceResponseInternal {
    public static fromPtr(ptr: KPointer): WebResourceResponse {
        const obj : WebResourceResponse = new WebResourceResponse()
        obj.peer = new Finalizable(ptr, WebResourceResponse.getFinalizer())
        return obj
    }
}
export class WebResourceResponse implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourceresponse(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebResourceResponse.ctor_webresourceresponse()
        this.peer = new Finalizable(ctorPtr, WebResourceResponse.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceResponse_getFinalizer()
    }
    public getResponseData(): string {
        return this.getResponseData_serialize()
    }
    public getResponseDataEx(): string | number | NativeBuffer | Resource | undefined {
        return this.getResponseDataEx_serialize()
    }
    public getResponseEncoding(): string {
        return this.getResponseEncoding_serialize()
    }
    public getResponseMimeType(): string {
        return this.getResponseMimeType_serialize()
    }
    public getReasonMessage(): string {
        return this.getReasonMessage_serialize()
    }
    public getResponseHeader(): Array<Header> {
        return this.getResponseHeader_serialize()
    }
    public getResponseCode(): number {
        return this.getResponseCode_serialize()
    }
    public setResponseData(data: string | number | Resource | NativeBuffer): void {
        const data_casted = data as (string | number | Resource | NativeBuffer)
        this.setResponseData_serialize(data_casted)
        return
    }
    public setResponseEncoding(encoding: string): void {
        const encoding_casted = encoding as (string)
        this.setResponseEncoding_serialize(encoding_casted)
        return
    }
    public setResponseMimeType(mimeType: string): void {
        const mimeType_casted = mimeType as (string)
        this.setResponseMimeType_serialize(mimeType_casted)
        return
    }
    public setReasonMessage(reason: string): void {
        const reason_casted = reason as (string)
        this.setReasonMessage_serialize(reason_casted)
        return
    }
    public setResponseHeader(header: Array<Header>): void {
        const header_casted = header as (Array<Header>)
        this.setResponseHeader_serialize(header_casted)
        return
    }
    public setResponseCode(code: number): void {
        const code_casted = code as (number)
        this.setResponseCode_serialize(code_casted)
        return
    }
    public setResponseIsReady(IsReady: boolean): void {
        const IsReady_casted = IsReady as (boolean)
        this.setResponseIsReady_serialize(IsReady_casted)
        return
    }
    public getResponseIsReady(): boolean {
        return this.getResponseIsReady_serialize()
    }
    private getResponseData_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseData(this.peer!.ptr)
        return retval
    }
    private getResponseDataEx_serialize(): string | number | NativeBuffer | Resource | undefined {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseDataEx(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getResponseEncoding_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseEncoding(this.peer!.ptr)
        return retval
    }
    private getResponseMimeType_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseMimeType(this.peer!.ptr)
        return retval
    }
    private getReasonMessage_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getReasonMessage(this.peer!.ptr)
        return retval
    }
    private getResponseHeader_serialize(): Array<Header> {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseHeader(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readHeader()
        }
        const returnResult : Array<Header> = buffer
        return returnResult
    }
    private getResponseCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseCode(this.peer!.ptr)
        return retval
    }
    private setResponseData_serialize(data: string | number | Resource | NativeBuffer): void {
        const thisSerializer : Serializer = Serializer.hold()
        let data_type : int32 = RuntimeType.UNDEFINED
        data_type = runtimeType(data)
        if (RuntimeType.STRING == data_type) {
            thisSerializer.writeInt8(0 as int32)
            const data_0  = data as string
            thisSerializer.writeString(data_0)
        }
        else if (RuntimeType.NUMBER == data_type) {
            thisSerializer.writeInt8(1 as int32)
            const data_1  = data as number
            thisSerializer.writeNumber(data_1)
        }
        else if (TypeChecker.isResource(data, false, false, false, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const data_2  = data as Resource
            thisSerializer.writeResource(data_2)
        }
        else if (TypeChecker.isNativeBuffer(data)) {
            thisSerializer.writeInt8(3 as int32)
            const data_3  = data as NativeBuffer
            thisSerializer.writeBuffer(data_3)
        }
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseData(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setResponseEncoding_serialize(encoding: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseEncoding(this.peer!.ptr, encoding)
    }
    private setResponseMimeType_serialize(mimeType: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseMimeType(this.peer!.ptr, mimeType)
    }
    private setReasonMessage_serialize(reason: string): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setReasonMessage(this.peer!.ptr, reason)
    }
    private setResponseHeader_serialize(header: Array<Header>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(header.length as int32)
        for (let i = 0; i < header.length; i++) {
            const header_element : Header = header[i]
            thisSerializer.writeHeader(header_element)
        }
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseHeader(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setResponseCode_serialize(code: number): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseCode(this.peer!.ptr, code)
    }
    private setResponseIsReady_serialize(IsReady: boolean): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseIsReady(this.peer!.ptr, IsReady ? 1 : 0)
    }
    private getResponseIsReady_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseIsReady(this.peer!.ptr)
        return retval
    }
}
export class WebResourceErrorInternal {
    public static fromPtr(ptr: KPointer): WebResourceError {
        const obj : WebResourceError = new WebResourceError()
        obj.peer = new Finalizable(ptr, WebResourceError.getFinalizer())
        return obj
    }
}
export class WebResourceError implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webresourceerror(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebResourceError.ctor_webresourceerror()
        this.peer = new Finalizable(ctorPtr, WebResourceError.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceError_getFinalizer()
    }
    public getErrorInfo(): string {
        return this.getErrorInfo_serialize()
    }
    public getErrorCode(): number {
        return this.getErrorCode_serialize()
    }
    private getErrorInfo_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_getErrorInfo(this.peer!.ptr)
        return retval
    }
    private getErrorCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_getErrorCode(this.peer!.ptr)
        return retval
    }
}
export class JsGeolocationInternal {
    public static fromPtr(ptr: KPointer): JsGeolocation {
        const obj : JsGeolocation = new JsGeolocation()
        obj.peer = new Finalizable(ptr, JsGeolocation.getFinalizer())
        return obj
    }
}
export class JsGeolocation implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_jsgeolocation(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._JsGeolocation_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = JsGeolocation.ctor_jsgeolocation()
        this.peer = new Finalizable(ctorPtr, JsGeolocation.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._JsGeolocation_getFinalizer()
    }
    public invoke(origin: string, allow: boolean, retain: boolean): void {
        const origin_casted = origin as (string)
        const allow_casted = allow as (boolean)
        const retain_casted = retain as (boolean)
        this.invoke_serialize(origin_casted, allow_casted, retain_casted)
        return
    }
    private invoke_serialize(origin: string, allow: boolean, retain: boolean): void {
        ArkUIGeneratedNativeModule._JsGeolocation_invoke(this.peer!.ptr, origin, allow ? 1 : 0, retain ? 1 : 0)
    }
}
export class WebCookieInternal {
    public static fromPtr(ptr: KPointer): WebCookie {
        const obj : WebCookie = new WebCookie()
        obj.peer = new Finalizable(ptr, WebCookie.getFinalizer())
        return obj
    }
}
export class WebCookie implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcookie(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebCookie_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebCookie.ctor_webcookie()
        this.peer = new Finalizable(ctorPtr, WebCookie.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebCookie_getFinalizer()
    }
    public setCookie(): undefined {
        return this.setCookie_serialize()
    }
    public saveCookie(): undefined {
        return this.saveCookie_serialize()
    }
    private setCookie_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebCookie_setCookie(this.peer!.ptr)
        return retval
    }
    private saveCookie_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebCookie_saveCookie(this.peer!.ptr)
        return retval
    }
}
export class EventResultInternal {
    public static fromPtr(ptr: KPointer): EventResult {
        const obj : EventResult = new EventResult()
        obj.peer = new Finalizable(ptr, EventResult.getFinalizer())
        return obj
    }
}
export class EventResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_eventresult(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._EventResult_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = EventResult.ctor_eventresult()
        this.peer = new Finalizable(ctorPtr, EventResult.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._EventResult_getFinalizer()
    }
    public setGestureEventResult(result: boolean, stopPropagation?: boolean): void {
        const result_type = runtimeType(result)
        const stopPropagation_type = runtimeType(stopPropagation)
        const result_casted = result as (boolean)
        this.setGestureEventResult0_serialize(result_casted)
        return
    }
    private setGestureEventResult0_serialize(result: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult0(this.peer!.ptr, result ? 1 : 0)
    }
    private setGestureEventResult1_serialize(result: boolean, stopPropagation: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult1(this.peer!.ptr, result ? 1 : 0, stopPropagation ? 1 : 0)
    }
}
export class WebControllerInternal {
    public static fromPtr(ptr: KPointer): WebController {
        const obj : WebController = new WebController()
        obj.peer = new Finalizable(ptr, WebController.getFinalizer())
        return obj
    }
}
export class WebController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebController.ctor_webcontroller()
        this.peer = new Finalizable(ctorPtr, WebController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebController_getFinalizer()
    }
    public onInactive(): void {
        this.onInactive_serialize()
        return
    }
    public onActive(): void {
        this.onActive_serialize()
        return
    }
    public zoom(factor: number): void {
        const factor_casted = factor as (number)
        this.zoom_serialize(factor_casted)
        return
    }
    public clearHistory(): void {
        this.clearHistory_serialize()
        return
    }
    public runJavaScript(options: Literal_String_script_Callback_String_Void_callback_): undefined {
        const options_casted = options as (Literal_String_script_Callback_String_Void_callback_)
        return this.runJavaScript_serialize(options_casted)
    }
    public loadData(options: Literal_String_baseUrl_data_encoding_historyUrl_mimeType): undefined {
        const options_casted = options as (Literal_String_baseUrl_data_encoding_historyUrl_mimeType)
        return this.loadData_serialize(options_casted)
    }
    public loadUrl(options: Literal_Union_String_Resource_url_Array_Header_headers): undefined {
        const options_casted = options as (Literal_Union_String_Resource_url_Array_Header_headers)
        return this.loadUrl_serialize(options_casted)
    }
    public refresh(): undefined {
        return this.refresh_serialize()
    }
    public stop(): undefined {
        return this.stop_serialize()
    }
    public registerJavaScriptProxy(options: Literal_Object_object__String_name_Array_String_methodList): undefined {
        const options_casted = options as (Literal_Object_object__String_name_Array_String_methodList)
        return this.registerJavaScriptProxy_serialize(options_casted)
    }
    public deleteJavaScriptRegister(name: string): undefined {
        const name_casted = name as (string)
        return this.deleteJavaScriptRegister_serialize(name_casted)
    }
    public getHitTest(): HitTestType {
        return this.getHitTest_serialize()
    }
    public requestFocus(): undefined {
        return this.requestFocus_serialize()
    }
    public accessBackward(): boolean {
        return this.accessBackward_serialize()
    }
    public accessForward(): boolean {
        return this.accessForward_serialize()
    }
    public accessStep(step: number): boolean {
        const step_casted = step as (number)
        return this.accessStep_serialize(step_casted)
    }
    public backward(): undefined {
        return this.backward_serialize()
    }
    public forward(): undefined {
        return this.forward_serialize()
    }
    public getCookieManager(): WebCookie {
        return this.getCookieManager_serialize()
    }
    private onInactive_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_onInactive(this.peer!.ptr)
    }
    private onActive_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_onActive(this.peer!.ptr)
    }
    private zoom_serialize(factor: number): void {
        ArkUIGeneratedNativeModule._WebController_zoom(this.peer!.ptr, factor)
    }
    private clearHistory_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_clearHistory(this.peer!.ptr)
    }
    private runJavaScript_serialize(options: Literal_String_script_Callback_String_Void_callback_): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const options_script  = options.script
        thisSerializer.writeString(options_script)
        const options_callback_  = options.callback_
        let options_callback__type : int32 = RuntimeType.UNDEFINED
        options_callback__type = runtimeType(options_callback_)
        thisSerializer.writeInt8(options_callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (options_callback__type)) {
            const options_callback__value  = options_callback_!
            thisSerializer.holdAndWriteCallback(options_callback__value)
        }
        const retval  = ArkUIGeneratedNativeModule._WebController_runJavaScript(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private loadData_serialize(options: Literal_String_baseUrl_data_encoding_historyUrl_mimeType): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const options_data  = options.data
        thisSerializer.writeString(options_data)
        const options_mimeType  = options.mimeType
        thisSerializer.writeString(options_mimeType)
        const options_encoding  = options.encoding
        thisSerializer.writeString(options_encoding)
        const options_baseUrl  = options.baseUrl
        let options_baseUrl_type : int32 = RuntimeType.UNDEFINED
        options_baseUrl_type = runtimeType(options_baseUrl)
        thisSerializer.writeInt8(options_baseUrl_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_baseUrl_type)) {
            const options_baseUrl_value  = options_baseUrl!
            thisSerializer.writeString(options_baseUrl_value)
        }
        const options_historyUrl  = options.historyUrl
        let options_historyUrl_type : int32 = RuntimeType.UNDEFINED
        options_historyUrl_type = runtimeType(options_historyUrl)
        thisSerializer.writeInt8(options_historyUrl_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_historyUrl_type)) {
            const options_historyUrl_value  = options_historyUrl!
            thisSerializer.writeString(options_historyUrl_value)
        }
        const retval  = ArkUIGeneratedNativeModule._WebController_loadData(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private loadUrl_serialize(options: Literal_Union_String_Resource_url_Array_Header_headers): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const options_url  = options.url
        let options_url_type : int32 = RuntimeType.UNDEFINED
        options_url_type = runtimeType(options_url)
        if (RuntimeType.STRING == options_url_type) {
            thisSerializer.writeInt8(0 as int32)
            const options_url_0  = options_url as string
            thisSerializer.writeString(options_url_0)
        }
        else if (RuntimeType.OBJECT == options_url_type) {
            thisSerializer.writeInt8(1 as int32)
            const options_url_1  = options_url as Resource
            thisSerializer.writeResource(options_url_1)
        }
        const options_headers  = options.headers
        let options_headers_type : int32 = RuntimeType.UNDEFINED
        options_headers_type = runtimeType(options_headers)
        thisSerializer.writeInt8(options_headers_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_headers_type)) {
            const options_headers_value  = options_headers!
            thisSerializer.writeInt32(options_headers_value.length as int32)
            for (let i = 0; i < options_headers_value.length; i++) {
                const options_headers_value_element : Header = options_headers_value[i]
                thisSerializer.writeHeader(options_headers_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._WebController_loadUrl(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private refresh_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_refresh(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_stop(this.peer!.ptr)
        return retval
    }
    private registerJavaScriptProxy_serialize(options: Literal_Object_object__String_name_Array_String_methodList): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const options_object_  = options.object_
        thisSerializer.holdAndWriteObject(options_object_)
        const options_name  = options.name
        thisSerializer.writeString(options_name)
        const options_methodList  = options.methodList
        thisSerializer.writeInt32(options_methodList.length as int32)
        for (let i = 0; i < options_methodList.length; i++) {
            const options_methodList_element : string = options_methodList[i]
            thisSerializer.writeString(options_methodList_element)
        }
        const retval  = ArkUIGeneratedNativeModule._WebController_registerJavaScriptProxy(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private deleteJavaScriptRegister_serialize(name: string): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_deleteJavaScriptRegister(this.peer!.ptr, name)
        return retval
    }
    private getHitTest_serialize(): HitTestType {
        const retval  = ArkUIGeneratedNativeModule._WebController_getHitTest(this.peer!.ptr)
        return TypeChecker.HitTestType_FromNumeric(retval)
    }
    private requestFocus_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_requestFocus(this.peer!.ptr)
        return retval
    }
    private accessBackward_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebController_accessBackward(this.peer!.ptr)
        return retval
    }
    private accessForward_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebController_accessForward(this.peer!.ptr)
        return retval
    }
    private accessStep_serialize(step: number): boolean {
        const retval  = ArkUIGeneratedNativeModule._WebController_accessStep(this.peer!.ptr, step)
        return retval
    }
    private backward_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_backward(this.peer!.ptr)
        return retval
    }
    private forward_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._WebController_forward(this.peer!.ptr)
        return retval
    }
    private getCookieManager_serialize(): WebCookie {
        const retval  = ArkUIGeneratedNativeModule._WebController_getCookieManager(this.peer!.ptr)
        const obj : WebCookie = WebCookieInternal.fromPtr(retval)
        return obj
    }
}
export class ArkWebPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkWebPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Web_construct(peerId, flags)
        const _peer  = new ArkWebPeer(_peerPtr, peerId, "Web", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWebOptionsAttribute(value: WebOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        if (TypeChecker.isWebviewControllerAni(value.controller)) {
            const value_casted = {
                src: value.src,
                renderMode: value.renderMode,
                incognitoMode: value.incognitoMode,
                sharedRenderProcessToken: value.sharedRenderProcessToken
            } as (WebOptionsSerializer)
            thisSerializer.writeWebOptions(value_casted)
            ArkUIGeneratedNativeModule._WebInterface_setWebOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            ArkUIAniModule._Web_SetWebOptions(this.peer.ptr, value.controller)
        }
        thisSerializer.release()
    }
    javaScriptAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fileAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_fileAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onlineImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onlineImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    domStorageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_domStorageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    imageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_imageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mixedModeAttribute(value: MixedMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as MixedMode)
            thisSerializer.writeInt32(TypeChecker.MixedMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_mixedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    zoomAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_zoomAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    geolocationAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_geolocationAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptProxyAttribute(value: JavaScriptProxy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeJavaScriptProxy(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptProxy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    passwordAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_password(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cacheModeAttribute(value: CacheMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CacheMode)
            thisSerializer.writeInt32(TypeChecker.CacheMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_cacheMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    darkModeAttribute(value: WebDarkMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as WebDarkMode)
            thisSerializer.writeInt32(TypeChecker.WebDarkMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_darkMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    forceDarkAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_forceDarkAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mediaOptionsAttribute(value: WebMediaOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeWebMediaOptions(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_mediaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tableDataAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_tableData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    wideViewModeAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_wideViewModeAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    overviewModeAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_overviewModeAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    overScrollModeAttribute(value: OverScrollMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as OverScrollMode)
            thisSerializer.writeInt32(TypeChecker.OverScrollMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_overScrollMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blurOnKeyboardHideModeAttribute(value: BlurOnKeyboardHideMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurOnKeyboardHideMode)
            thisSerializer.writeInt32(TypeChecker.BlurOnKeyboardHideMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_blurOnKeyboardHideMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textZoomAtioAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_textZoomAtio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textZoomRatioAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_textZoomRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    databaseAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_databaseAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    initialScaleAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_initialScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    userAgentAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_userAgent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    metaViewportAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_metaViewport(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageEndAttribute(value: ((parameter: OnPageEndEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onPageEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageBeginAttribute(value: ((parameter: OnPageBeginEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onPageBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onProgressChangeAttribute(value: ((parameter: OnProgressChangeEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onProgressChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTitleReceiveAttribute(value: ((parameter: OnTitleReceiveEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onTitleReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationShowAttribute(value: ((parameter: OnGeolocationShowEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestSelectedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRequestSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAlertAttribute(value: ((parameter: OnAlertEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onAlert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBeforeUnloadAttribute(value: ((parameter: OnBeforeUnloadEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onBeforeUnload(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onConfirmAttribute(value: ((parameter: OnConfirmEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onConfirm(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPromptAttribute(value: ((parameter: OnPromptEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onPrompt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onConsoleAttribute(value: ((parameter: OnConsoleEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onConsole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorReceiveAttribute(value: ((parameter: OnErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpErrorReceiveAttribute(value: ((parameter: OnHttpErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onHttpErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDownloadStartAttribute(value: ((parameter: OnDownloadStartEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onDownloadStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRefreshAccessedHistoryAttribute(value: ((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRefreshAccessedHistory(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUrlLoadInterceptAttribute(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onUrlLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorReceiveAttribute(value: ((event?: Literal_Function_handler_Object_error) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited0Attribute(value: ((parameter: OnRenderExitedEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited1Attribute(value: ((event?: Literal_Object_detail) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onShowFileSelectorAttribute(value: ((parameter: OnShowFileSelectorEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onShowFileSelector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFileSelectorShowAttribute(value: ((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFileSelectorShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onResourceLoadAttribute(value: ((parameter: OnResourceLoadEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onResourceLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenEnterAttribute(value: OnFullScreenEnterCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScaleChangeAttribute(value: ((parameter: OnScaleChangeEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onScaleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpAuthRequestAttribute(value: ((parameter: OnHttpAuthRequestEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onHttpAuthRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptRequestAttribute(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPermissionRequestAttribute(value: ((parameter: OnPermissionRequestEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onPermissionRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScreenCaptureRequestAttribute(value: ((parameter: OnScreenCaptureRequestEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onScreenCaptureRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuShowAttribute(value: ((parameter: OnContextMenuShowEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuHideAttribute(value: OnContextMenuHideCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mediaPlayGestureAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_mediaPlayGestureAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSearchResultReceiveAttribute(value: ((parameter: OnSearchResultReceiveEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onSearchResultReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((parameter: OnScrollEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventReceiveAttribute(value: ((parameter: OnSslErrorEventReceiveEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEventReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventAttribute(value: OnSslErrorEventCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClientAuthenticationRequestAttribute(value: ((parameter: OnClientAuthenticationEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onClientAuthenticationRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowNewAttribute(value: ((parameter: OnWindowNewEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onWindowNew(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onWindowExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    multiWindowAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_multiWindowAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptKeyEventAttribute(value: ((parameter: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webStandardFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webStandardFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webSansSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webSansSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webFixedFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webFixedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webFantasyFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webFantasyFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webCursiveFontAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_webCursiveFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultFixedFontSizeAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_defaultFixedFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultFontSizeAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_defaultFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minLogicalFontSizeAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_minLogicalFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultTextEncodingFormatAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_defaultTextEncodingFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    forceDisplayScrollBarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_forceDisplayScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockNetworkAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_blockNetwork(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    horizontalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_horizontalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_verticalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchIconUrlReceivedAttribute(value: ((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onTouchIconUrlReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFaviconReceivedAttribute(value: ((parameter: OnFaviconReceivedEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFaviconReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageVisibleAttribute(value: ((parameter: OnPageVisibleEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onPageVisible(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDataResubmittedAttribute(value: ((parameter: OnDataResubmittedEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onDataResubmitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pinchSmoothAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_pinchSmooth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    allowWindowOpenMethodAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_allowWindowOpenMethod(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAudioStateChangedAttribute(value: ((parameter: OnAudioStateChangedEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onAudioStateChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstContentfulPaintAttribute(value: ((parameter: OnFirstContentfulPaintEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFirstContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onLargestContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadInterceptAttribute(value: ((parameter: OnLoadInterceptEvent) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onControllerAttachedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onControllerAttached(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onOverScrollAttribute(value: ((parameter: OnOverScrollEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onOverScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onNavigationEntryCommitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ScriptItem = value_value[i]
                thisSerializer.writeScriptItem(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ScriptItem = value_value[i]
                thisSerializer.writeScriptItem(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutModeAttribute(value: WebLayoutMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as WebLayoutMode)
            thisSerializer.writeInt32(TypeChecker.WebLayoutMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_layoutMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isNestedScrollOptions(value_value, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as NestedScrollOptions
                thisSerializer.writeNestedScrollOptions(value_value_0)
            }
            else if (TypeChecker.isNestedScrollOptionsExt(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as NestedScrollOptionsExt
                thisSerializer.writeNestedScrollOptionsExt(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNativeEmbedModeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeEmbedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_copyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onOverrideUrlLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textAutosizingAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_textAutosizing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNativeMediaPlayerConfig(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeMediaPlayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessNotResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuOptionsAttribute(value: Array<ExpandedMenuItemOptions> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ExpandedMenuItemOptions = value_value[i]
                thisSerializer.writeExpandedMenuItemOptions(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_selectionMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onViewportFitChangedAttribute(value: OnViewportFitChangedCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onViewportFitChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptKeyboardAttachAttribute(value: WebKeyboardCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAdsBlockedAttribute(value: OnAdsBlockedCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_onAdsBlocked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardAvoidModeAttribute(value: WebKeyboardAvoidMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as WebKeyboardAvoidMode)
            thisSerializer.writeInt32(TypeChecker.WebKeyboardAvoidMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_keyboardAvoidMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeEditMenuOptions(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optimizeParserBudgetAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_optimizeParserBudget(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableFollowSystemFontWeightAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_enableFollowSystemFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableWebAVSessionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_enableWebAVSession(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    runJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ScriptItem = value_value[i]
                thisSerializer.writeScriptItem(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_runJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    runJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ScriptItem = value_value[i]
                thisSerializer.writeScriptItem(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_runJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    runJavaScriptOnHeadEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ScriptItem = value_value[i]
                thisSerializer.writeScriptItem(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_runJavaScriptOnHeadEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nativeEmbedOptionsAttribute(value: EmbedOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeEmbedOptions(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_nativeEmbedOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    registerNativeEmbedRuleAttribute(tag: string | undefined, type: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let tag_type : int32 = RuntimeType.UNDEFINED
        tag_type = runtimeType(tag)
        thisSerializer.writeInt8(tag_type as int32)
        if ((RuntimeType.UNDEFINED) != (tag_type)) {
            const tag_value  = tag!
            thisSerializer.writeString(tag_value)
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = type!
            thisSerializer.writeString(type_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_registerNativeEmbedRule(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSelectionMenuAttribute(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): void {
        const thisSerializer : Serializer = Serializer.hold()
        let elementType_type : int32 = RuntimeType.UNDEFINED
        elementType_type = runtimeType(elementType)
        thisSerializer.writeInt8(elementType_type as int32)
        if ((RuntimeType.UNDEFINED) != (elementType_type)) {
            const elementType_value  = (elementType as WebElementType)
            thisSerializer.writeInt32(TypeChecker.WebElementType_ToNumeric(elementType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8(responseType_type as int32)
        if ((RuntimeType.UNDEFINED) != (responseType_type)) {
            const responseType_value  = (responseType as WebResponseType)
            thisSerializer.writeInt32(TypeChecker.WebResponseType_ToNumeric(responseType_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionMenuOptionsExt(options_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_bindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    forceEnableZoomAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_forceEnableZoom(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type OnNavigationEntryCommittedCallback = (loadCommittedDetails: LoadCommittedDetails) => void;
export type OnSslErrorEventCallback = (sslErrorEvent: SslErrorEvent) => void;
export type OnLargestContentfulPaintCallback = (largestContentfulPaint: LargestContentfulPaint) => void;
export type OnFirstMeaningfulPaintCallback = (firstMeaningfulPaint: FirstMeaningfulPaint) => void;
export type OnOverrideUrlLoadingCallback = (webResourceRequest: WebResourceRequest) => boolean;
export type OnIntelligentTrackingPreventionCallback = (details: IntelligentTrackingPreventionDetails) => void;
export type OnNativeEmbedVisibilityChangeCallback = (nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo) => void;
export interface NativeMediaPlayerConfig {
    enable: boolean;
    shouldOverlay: boolean;
}
export type OnRenderProcessNotRespondingCallback = (data: RenderProcessNotRespondingData) => void;
export type OnRenderProcessRespondingCallback = () => void;
export type OnViewportFitChangedCallback = (viewportFit: ViewportFit) => void;
export type OnAdsBlockedCallback = (details: AdsBlockedDetails) => void;
export interface AdsBlockedDetails {
    url: string;
    adsBlocked: Array<string>;
}
export interface WebKeyboardOptions {
    useSystemKeyboard: boolean;
    enterKeyType?: number;
    customKeyboard?: CustomBuilder;
}
export interface WebKeyboardCallbackInfo {
    controller: WebKeyboardController;
    attributes: Map<string, string>;
}
export type WebKeyboardCallback = (keyboardCallbackInfo: WebKeyboardCallbackInfo) => WebKeyboardOptions;
export enum MessageLevel {
    DEBUG = 0,
    Debug = 0,
    ERROR = 1,
    Error = 1,
    INFO = 2,
    Info = 2,
    LOG = 3,
    Log = 3,
    WARN = 4,
    Warn = 4
}
export enum MixedMode {
    ALL = 0,
    All = 0,
    COMPATIBLE = 1,
    Compatible = 1,
    NONE = 2,
    None = 2
}
export type OnSafeBrowsingCheckResultCallback = (threatType: ThreatType) => void;
export enum HitTestType {
    EDIT_TEXT = 0,
    EditText = 0,
    EMAIL = 1,
    Email = 1,
    HTTP_ANCHOR = 2,
    HttpAnchor = 2,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = 3,
    IMG = 4,
    Img = 4,
    MAP = 5,
    Map = 5,
    PHONE = 6,
    Phone = 6,
    UNKNOWN = 7,
    Unknown = 7
}
export enum CacheMode {
    DEFAULT = 0,
    Default = 0,
    NONE = 1,
    None = 1,
    ONLINE = 2,
    Online = 2,
    ONLY = 3,
    Only = 3
}
export enum OverScrollMode {
    NEVER = 0,
    ALWAYS = 1
}
export enum BlurOnKeyboardHideMode {
    SILENT = 0,
    BLUR = 1
}
export enum WebDarkMode {
    OFF = 0,
    Off = 0,
    ON = 1,
    On = 1,
    AUTO = 2,
    Auto = 2
}
export enum WebCaptureMode {
    HOME_SCREEN = 0
}
export enum ThreatType {
    THREAT_ILLEGAL = 0,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3
}
export interface WebMediaOptions {
    resumeInterval?: number;
    audioExclusive?: boolean;
}
export interface ScreenCaptureConfig {
    captureMode: WebCaptureMode;
}
export interface FullScreenEnterEvent {
    handler: FullScreenExitHandler;
    videoWidth?: number;
    videoHeight?: number;
}
export type OnFullScreenEnterCallback = (event: FullScreenEnterEvent) => void;
export enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION = 0,
    ProcessAbnormalTermination = 0,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = 1,
    PROCESS_CRASHED = 2,
    ProcessCrashed = 2,
    PROCESS_OOM = 3,
    ProcessOom = 3,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = 4
}
export type OnContextMenuHideCallback = () => void;
export enum SslError {
    INVALID = 0,
    Invalid = 0,
    HOST_MISMATCH = 1,
    HostMismatch = 1,
    DATE_INVALID = 2,
    DateInvalid = 2,
    UNTRUSTED = 3,
    Untrusted = 3
}
export enum FileSelectorMode {
    FILE_OPEN_MODE = 0,
    FileOpenMode = 0,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = 1,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = 2,
    FILE_SAVE_MODE = 3,
    FileSaveMode = 3
}
export enum WebLayoutMode {
    NONE = 0,
    FIT_CONTENT = 1
}
export enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT = 0,
    NAVIGATION_COMMIT_TIMEOUT = 1
}
export enum ProtectedResourceType {
    MIDI_SYSEX = "TYPE_MIDI_SYSEX",
    MidiSysex = "TYPE_MIDI_SYSEX",
    VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE",
    AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE",
    SENSOR = "TYPE_SENSOR"
}
export enum ContextMenuSourceType {
    NONE = 0,
    None = 0,
    MOUSE = 1,
    Mouse = 1,
    LONG_PRESS = 2,
    LongPress = 2
}
export enum ContextMenuMediaType {
    NONE = 0,
    None = 0,
    IMAGE = 1,
    Image = 1
}
export enum ContextMenuInputFieldType {
    NONE = 0,
    None = 0,
    PLAIN_TEXT = 1,
    PlainText = 1,
    PASSWORD = 2,
    Password = 2,
    NUMBER = 3,
    Number = 3,
    TELEPHONE = 4,
    Telephone = 4,
    OTHER = 5,
    Other = 5
}
export enum NativeEmbedStatus {
    CREATE = 0,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4
}
export enum ContextMenuEditStateFlags {
    NONE = 0,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 4,
    CAN_SELECT_ALL = 8
}
export enum WebNavigationType {
    UNKNOWN = 0,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5
}
export enum RenderMode {
    ASYNC_RENDER = 0,
    SYNC_RENDER = 1
}
export enum ViewportFit {
    AUTO = 0,
    CONTAINS = 1,
    COVER = 2
}
export interface Header {
    headerKey: string;
    headerValue: string;
}
export interface Literal_String_script_Callback_String_Void_callback_ {
    script: string;
    callback_?: ((breakpoints: string) => void);
}
export interface Literal_String_baseUrl_data_encoding_historyUrl_mimeType {
    data: string;
    mimeType: string;
    encoding: string;
    baseUrl?: string;
    historyUrl?: string;
}
export interface Literal_Union_String_Resource_url_Array_Header_headers {
    url: string | Resource;
    headers?: Array<Header>;
}
export interface Literal_Object_object__String_name_Array_String_methodList {
    object_: Object;
    name: string;
    methodList: Array<string>;
}
export interface WebOptions {
    src: string | Resource;
    controller: WebviewControllerAni;
    renderMode?: RenderMode;
    incognitoMode?: boolean;
    sharedRenderProcessToken?: string;
}
export interface WebOptionsSerializer {
    src: string | Resource;
    renderMode?: RenderMode;
    incognitoMode?: boolean;
    sharedRenderProcessToken?: string;
}
export interface ScriptItem {
    script: string;
    scriptRules: Array<string>;
}
export interface LoadCommittedDetails {
    isMainFrame: boolean;
    isSameDocument: boolean;
    didReplaceEntry: boolean;
    navigationType: WebNavigationType;
    url: string;
}
export interface IntelligentTrackingPreventionDetails {
    host: string;
    trackerHost: string;
}
export type WebInterface = (value: WebOptions) => WebAttribute;
export interface NativeEmbedInfo {
    id?: string;
    type?: string;
    src?: string;
    position?: Position;
    width?: number;
    height?: number;
    url?: string;
    tag?: string;
    params?: Map<string, string>;
}
export interface NativeEmbedDataInfo {
    status?: NativeEmbedStatus;
    surfaceId?: string;
    embedId?: string;
    info?: NativeEmbedInfo;
}
export interface NativeEmbedVisibilityInfo {
    visibility: boolean;
    embedId: string;
}
export interface NativeEmbedTouchInfo {
    embedId?: string;
    touchEvent?: TouchEvent;
    result?: EventResult;
}
export interface FirstMeaningfulPaint {
    navigationStartTime?: number;
    firstMeaningfulPaintTime?: number;
}
export interface LargestContentfulPaint {
    navigationStartTime?: number;
    largestImagePaintTime?: number;
    largestTextPaintTime?: number;
    imageBPP?: number;
    largestImageLoadStartTime?: number;
    largestImageLoadEndTime?: number;
}
export interface RenderProcessNotRespondingData {
    jsStack: string;
    pid: number;
    reason: RenderProcessNotRespondingReason;
}
export interface OnPageEndEvent {
    url: string;
}
export interface OnPageBeginEvent {
    url: string;
}
export interface OnProgressChangeEvent {
    newProgress: number;
}
export interface OnTitleReceiveEvent {
    title: string;
}
export interface OnGeolocationShowEvent {
    origin: string;
    geolocation: JsGeolocation;
}
export interface OnAlertEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnBeforeUnloadEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnConfirmEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnPromptEvent {
    url: string;
    message: string;
    value: string;
    result: JsResult;
}
export interface OnConsoleEvent {
    message: ConsoleMessage;
}
export interface OnErrorReceiveEvent {
    request: WebResourceRequest;
    error: WebResourceError;
}
export interface OnHttpErrorReceiveEvent {
    request: WebResourceRequest;
    response: WebResourceResponse;
}
export interface OnDownloadStartEvent {
    url: string;
    userAgent: string;
    contentDisposition: string;
    mimetype: string;
    contentLength: number;
}
export interface OnRefreshAccessedHistoryEvent {
    url: string;
    isRefreshed: boolean;
}
export interface OnRenderExitedEvent {
    renderExitReason: RenderExitReason;
}
export interface OnShowFileSelectorEvent {
    result: FileSelectorResult;
    fileSelector: FileSelectorParam;
}
export interface OnResourceLoadEvent {
    url: string;
}
export interface OnScaleChangeEvent {
    oldScale: number;
    newScale: number;
}
export interface OnHttpAuthRequestEvent {
    handler: HttpAuthHandler;
    host: string;
    realm: string;
}
export interface OnInterceptRequestEvent {
    request: WebResourceRequest;
}
export interface OnPermissionRequestEvent {
    request: PermissionRequest;
}
export interface OnScreenCaptureRequestEvent {
    handler: ScreenCaptureHandler;
}
export interface OnContextMenuShowEvent {
    param: WebContextMenuParam;
    result: WebContextMenuResult;
}
export interface OnSearchResultReceiveEvent {
    activeMatchOrdinal: number;
    numberOfMatches: number;
    isDoneCounting: boolean;
}
export interface OnScrollEvent {
    xOffset: number;
    yOffset: number;
}
export interface OnSslErrorEventReceiveEvent {
    handler: SslErrorHandler;
    error: SslError;
    certChainData?: Array<NativeBuffer>;
}
export interface OnClientAuthenticationEvent {
    handler: ClientAuthenticationHandler;
    host: string;
    port: number;
    keyTypes: Array<string>;
    issuers: Array<string>;
}
export interface OnWindowNewEvent {
    isAlert: boolean;
    isUserTrigger: boolean;
    targetUrl: string;
    handler: ControllerHandler;
}
export interface OnTouchIconUrlReceivedEvent {
    url: string;
    precomposed: boolean;
}
export interface OnFaviconReceivedEvent {
    favicon: PixelMap;
}
export interface OnPageVisibleEvent {
    url: string;
}
export interface OnDataResubmittedEvent {
    handler: DataResubmissionHandler;
}
export interface OnAudioStateChangedEvent {
    playing: boolean;
}
export interface OnFirstContentfulPaintEvent {
    navigationStartTick: number;
    firstContentfulPaintMs: number;
}
export interface OnLoadInterceptEvent {
    data: WebResourceRequest;
}
export interface OnOverScrollEvent {
    xOffset: number;
    yOffset: number;
}
export interface JavaScriptProxy {
    object_: Object;
    name: string;
    methodList: Array<string>;
    controller: WebController | WebviewController;
    asyncMethodList?: Array<string>;
    permission?: string;
}
export enum WebKeyboardAvoidMode {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2
}
export enum WebElementType {
    IMAGE = 1
}
export enum WebResponseType {
    LONG_PRESS = 1
}
export interface SelectionMenuOptionsExt {
    onAppear?: (() => void);
    onDisappear?: (() => void);
    preview?: CustomBuilder;
    menuType?: MenuType;
    previewMenuOptions?: PreviewMenuOptions;
}
export type Callback_OnPageEndEvent_Void = (parameter: OnPageEndEvent) => void;
export type Callback_OnPageBeginEvent_Void = (parameter: OnPageBeginEvent) => void;
export type Callback_OnProgressChangeEvent_Void = (parameter: OnProgressChangeEvent) => void;
export type Callback_OnTitleReceiveEvent_Void = (parameter: OnTitleReceiveEvent) => void;
export type Callback_OnGeolocationShowEvent_Void = (parameter: OnGeolocationShowEvent) => void;
export type Callback_OnAlertEvent_Boolean = (parameter: OnAlertEvent) => boolean;
export type Callback_OnBeforeUnloadEvent_Boolean = (parameter: OnBeforeUnloadEvent) => boolean;
export type Callback_OnConfirmEvent_Boolean = (parameter: OnConfirmEvent) => boolean;
export type Callback_OnPromptEvent_Boolean = (parameter: OnPromptEvent) => boolean;
export type Callback_OnConsoleEvent_Boolean = (parameter: OnConsoleEvent) => boolean;
export type Callback_OnErrorReceiveEvent_Void = (parameter: OnErrorReceiveEvent) => void;
export type Callback_OnHttpErrorReceiveEvent_Void = (parameter: OnHttpErrorReceiveEvent) => void;
export type Callback_OnDownloadStartEvent_Void = (parameter: OnDownloadStartEvent) => void;
export type Callback_OnRefreshAccessedHistoryEvent_Void = (parameter: OnRefreshAccessedHistoryEvent) => void;
export interface Literal_Union_String_WebResourceRequest_data {
    data: string | WebResourceRequest;
}
export type Type_WebAttribute_onUrlLoadIntercept_callback = (event?: Literal_Union_String_WebResourceRequest_data) => boolean;
export interface Literal_Function_handler_Object_error {
    handler: Object;
    error: Object;
}
export type Callback_Literal_Function_handler_Object_error_Void = (event?: Literal_Function_handler_Object_error) => void;
export type Callback_OnRenderExitedEvent_Void = (parameter: OnRenderExitedEvent) => void;
export type Callback_OnShowFileSelectorEvent_Boolean = (parameter: OnShowFileSelectorEvent) => boolean;
export interface Literal_Object_detail {
    detail: Object;
}
export type Callback_Literal_Object_detail_Boolean = (event?: Literal_Object_detail) => boolean;
export interface Literal_Function_callback__Object_fileSelector {
    callback_: Object;
    fileSelector: Object;
}
export type Type_WebAttribute_onFileSelectorShow_callback = (event?: Literal_Function_callback__Object_fileSelector) => void;
export type Callback_OnResourceLoadEvent_Void = (parameter: OnResourceLoadEvent) => void;
export type Callback_OnScaleChangeEvent_Void = (parameter: OnScaleChangeEvent) => void;
export type Callback_OnHttpAuthRequestEvent_Boolean = (parameter: OnHttpAuthRequestEvent) => boolean;
export type Callback_OnInterceptRequestEvent_WebResourceResponse = (parameter: OnInterceptRequestEvent) => WebResourceResponse;
export type Callback_OnPermissionRequestEvent_Void = (parameter: OnPermissionRequestEvent) => void;
export type Callback_OnScreenCaptureRequestEvent_Void = (parameter: OnScreenCaptureRequestEvent) => void;
export type Callback_OnContextMenuShowEvent_Boolean = (parameter: OnContextMenuShowEvent) => boolean;
export type Callback_OnSearchResultReceiveEvent_Void = (parameter: OnSearchResultReceiveEvent) => void;
export type Callback_OnScrollEvent_Void = (parameter: OnScrollEvent) => void;
export type Callback_OnSslErrorEventReceiveEvent_Void = (parameter: OnSslErrorEventReceiveEvent) => void;
export type Callback_OnClientAuthenticationEvent_Void = (parameter: OnClientAuthenticationEvent) => void;
export type Callback_OnWindowNewEvent_Void = (parameter: OnWindowNewEvent) => void;
export type Callback_OnTouchIconUrlReceivedEvent_Void = (parameter: OnTouchIconUrlReceivedEvent) => void;
export type Callback_OnFaviconReceivedEvent_Void = (parameter: OnFaviconReceivedEvent) => void;
export type Callback_OnPageVisibleEvent_Void = (parameter: OnPageVisibleEvent) => void;
export type Callback_OnDataResubmittedEvent_Void = (parameter: OnDataResubmittedEvent) => void;
export type Callback_OnAudioStateChangedEvent_Void = (parameter: OnAudioStateChangedEvent) => void;
export type Callback_OnFirstContentfulPaintEvent_Void = (parameter: OnFirstContentfulPaintEvent) => void;
export type Callback_OnLoadInterceptEvent_Boolean = (parameter: OnLoadInterceptEvent) => boolean;
export type Callback_OnOverScrollEvent_Void = (parameter: OnOverScrollEvent) => void;
export type Callback_NativeEmbedDataInfo_Void = (event: NativeEmbedDataInfo) => void;
export type Callback_NativeEmbedTouchInfo_Void = (event: NativeEmbedTouchInfo) => void;
export interface WebAttribute extends CommonMethod {
    javaScriptAccess(value: boolean | undefined): this
    fileAccess(value: boolean | undefined): this
    onlineImageAccess(value: boolean | undefined): this
    domStorageAccess(value: boolean | undefined): this
    imageAccess(value: boolean | undefined): this
    mixedMode(value: MixedMode | undefined): this
    zoomAccess(value: boolean | undefined): this
    geolocationAccess(value: boolean | undefined): this
    javaScriptProxy(value: JavaScriptProxy | undefined): this
    password(value: boolean | undefined): this
    cacheMode(value: CacheMode | undefined): this
    darkMode(value: WebDarkMode | undefined): this
    forceDarkAccess(value: boolean | undefined): this
    mediaOptions(value: WebMediaOptions | undefined): this
    tableData(value: boolean | undefined): this
    wideViewModeAccess(value: boolean | undefined): this
    overviewModeAccess(value: boolean | undefined): this
    overScrollMode(value: OverScrollMode | undefined): this
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this
    textZoomAtio(value: number | undefined): this
    textZoomRatio(value: number | undefined): this
    databaseAccess(value: boolean | undefined): this
    initialScale(value: number | undefined): this
    userAgent(value: string | undefined): this
    metaViewport(value: boolean | undefined): this
    onPageEnd(value: ((parameter: OnPageEndEvent) => void) | undefined): this
    onPageBegin(value: ((parameter: OnPageBeginEvent) => void) | undefined): this
    onProgressChange(value: ((parameter: OnProgressChangeEvent) => void) | undefined): this
    onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void) | undefined): this
    onGeolocationHide(value: (() => void) | undefined): this
    onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void) | undefined): this
    onRequestSelected(value: (() => void) | undefined): this
    onAlert(value: ((parameter: OnAlertEvent) => boolean) | undefined): this
    onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean) | undefined): this
    onConfirm(value: ((parameter: OnConfirmEvent) => boolean) | undefined): this
    onPrompt(value: ((parameter: OnPromptEvent) => boolean) | undefined): this
    onConsole(value: ((parameter: OnConsoleEvent) => boolean) | undefined): this
    onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void) | undefined): this
    onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void) | undefined): this
    onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void) | undefined): this
    onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined): this
    onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined): this
    onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void) | undefined): this
    onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | undefined | ((event?: Literal_Object_detail) => boolean) | undefined): this
    onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean) | undefined): this
    onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined): this
    onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void) | undefined): this
    onFullScreenExit(value: (() => void) | undefined): this
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this
    onScaleChange(value: ((parameter: OnScaleChangeEvent) => void) | undefined): this
    onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean) | undefined): this
    onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this
    onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void) | undefined): this
    onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void) | undefined): this
    onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean) | undefined): this
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this
    mediaPlayGestureAccess(value: boolean | undefined): this
    onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void) | undefined): this
    onScroll(value: ((parameter: OnScrollEvent) => void) | undefined): this
    onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void) | undefined): this
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this
    onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void) | undefined): this
    onWindowNew(value: ((parameter: OnWindowNewEvent) => void) | undefined): this
    onWindowExit(value: (() => void) | undefined): this
    multiWindowAccess(value: boolean | undefined): this
    onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean) | undefined): this
    webStandardFont(value: string | undefined): this
    webSerifFont(value: string | undefined): this
    webSansSerifFont(value: string | undefined): this
    webFixedFont(value: string | undefined): this
    webFantasyFont(value: string | undefined): this
    webCursiveFont(value: string | undefined): this
    defaultFixedFontSize(value: number | undefined): this
    defaultFontSize(value: number | undefined): this
    minFontSize(value: number | undefined): this
    minLogicalFontSize(value: number | undefined): this
    defaultTextEncodingFormat(value: string | undefined): this
    forceDisplayScrollBar(value: boolean | undefined): this
    blockNetwork(value: boolean | undefined): this
    horizontalScrollBarAccess(value: boolean | undefined): this
    verticalScrollBarAccess(value: boolean | undefined): this
    onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined): this
    onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void) | undefined): this
    onPageVisible(value: ((parameter: OnPageVisibleEvent) => void) | undefined): this
    onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void) | undefined): this
    pinchSmooth(value: boolean | undefined): this
    allowWindowOpenMethod(value: boolean | undefined): this
    onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void) | undefined): this
    onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void) | undefined): this
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this
    onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean) | undefined): this
    onControllerAttached(value: (() => void) | undefined): this
    onOverScroll(value: ((parameter: OnOverScrollEvent) => void) | undefined): this
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this
    layoutMode(value: WebLayoutMode | undefined): this
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this
    enableNativeEmbedMode(value: boolean | undefined): this
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this
    copyOptions(value: CopyOptions | undefined): this
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this
    textAutosizing(value: boolean | undefined): this
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this
    selectionMenuOptions(value: Array<ExpandedMenuItemOptions> | undefined): this
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this
    editMenuOptions(value: EditMenuOptions | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    optimizeParserBudget(value: boolean | undefined): this
    enableFollowSystemFontWeight(value: boolean | undefined): this
    enableWebAVSession(value: boolean | undefined): this
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this
    nativeEmbedOptions(value: EmbedOptions | undefined): this
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this
    forceEnableZoom(value: boolean | undefined): this
}
export class ArkWebStyle extends ArkCommonMethodStyle implements WebAttribute {
    javaScriptAccess_value?: boolean | undefined
    fileAccess_value?: boolean | undefined
    onlineImageAccess_value?: boolean | undefined
    domStorageAccess_value?: boolean | undefined
    imageAccess_value?: boolean | undefined
    mixedMode_value?: MixedMode | undefined
    zoomAccess_value?: boolean | undefined
    geolocationAccess_value?: boolean | undefined
    javaScriptProxy_value?: JavaScriptProxy | undefined
    password_value?: boolean | undefined
    cacheMode_value?: CacheMode | undefined
    darkMode_value?: WebDarkMode | undefined
    forceDarkAccess_value?: boolean | undefined
    mediaOptions_value?: WebMediaOptions | undefined
    tableData_value?: boolean | undefined
    wideViewModeAccess_value?: boolean | undefined
    overviewModeAccess_value?: boolean | undefined
    overScrollMode_value?: OverScrollMode | undefined
    blurOnKeyboardHideMode_value?: BlurOnKeyboardHideMode | undefined
    textZoomAtio_value?: number | undefined
    textZoomRatio_value?: number | undefined
    databaseAccess_value?: boolean | undefined
    initialScale_value?: number | undefined
    userAgent_value?: string | undefined
    metaViewport_value?: boolean | undefined
    onPageEnd_value?: ((parameter: OnPageEndEvent) => void) | undefined
    onPageBegin_value?: ((parameter: OnPageBeginEvent) => void) | undefined
    onProgressChange_value?: ((parameter: OnProgressChangeEvent) => void) | undefined
    onTitleReceive_value?: ((parameter: OnTitleReceiveEvent) => void) | undefined
    onGeolocationHide_value?: (() => void) | undefined
    onGeolocationShow_value?: ((parameter: OnGeolocationShowEvent) => void) | undefined
    onRequestSelected_value?: (() => void) | undefined
    onAlert_value?: ((parameter: OnAlertEvent) => boolean) | undefined
    onBeforeUnload_value?: ((parameter: OnBeforeUnloadEvent) => boolean) | undefined
    onConfirm_value?: ((parameter: OnConfirmEvent) => boolean) | undefined
    onPrompt_value?: ((parameter: OnPromptEvent) => boolean) | undefined
    onConsole_value?: ((parameter: OnConsoleEvent) => boolean) | undefined
    onErrorReceive_value?: ((parameter: OnErrorReceiveEvent) => void) | undefined
    onHttpErrorReceive_value?: ((parameter: OnHttpErrorReceiveEvent) => void) | undefined
    onDownloadStart_value?: ((parameter: OnDownloadStartEvent) => void) | undefined
    onRefreshAccessedHistory_value?: ((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined
    onUrlLoadIntercept_value?: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined
    onSslErrorReceive_value?: ((event?: Literal_Function_handler_Object_error) => void) | undefined
    onRenderExited_value?: ((parameter: OnRenderExitedEvent) => void) | undefined
    onShowFileSelector_value?: ((parameter: OnShowFileSelectorEvent) => boolean) | undefined
    onFileSelectorShow_value?: ((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined
    onResourceLoad_value?: ((parameter: OnResourceLoadEvent) => void) | undefined
    onFullScreenExit_value?: (() => void) | undefined
    onFullScreenEnter_value?: OnFullScreenEnterCallback | undefined
    onScaleChange_value?: ((parameter: OnScaleChangeEvent) => void) | undefined
    onHttpAuthRequest_value?: ((parameter: OnHttpAuthRequestEvent) => boolean) | undefined
    onInterceptRequest_value?: ((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined
    onPermissionRequest_value?: ((parameter: OnPermissionRequestEvent) => void) | undefined
    onScreenCaptureRequest_value?: ((parameter: OnScreenCaptureRequestEvent) => void) | undefined
    onContextMenuShow_value?: ((parameter: OnContextMenuShowEvent) => boolean) | undefined
    onContextMenuHide_value?: OnContextMenuHideCallback | undefined
    mediaPlayGestureAccess_value?: boolean | undefined
    onSearchResultReceive_value?: ((parameter: OnSearchResultReceiveEvent) => void) | undefined
    onScroll_value?: ((parameter: OnScrollEvent) => void) | undefined
    onSslErrorEventReceive_value?: ((parameter: OnSslErrorEventReceiveEvent) => void) | undefined
    onSslErrorEvent_value?: OnSslErrorEventCallback | undefined
    onClientAuthenticationRequest_value?: ((parameter: OnClientAuthenticationEvent) => void) | undefined
    onWindowNew_value?: ((parameter: OnWindowNewEvent) => void) | undefined
    onWindowExit_value?: (() => void) | undefined
    multiWindowAccess_value?: boolean | undefined
    onInterceptKeyEvent_value?: ((parameter: KeyEvent) => boolean) | undefined
    webStandardFont_value?: string | undefined
    webSerifFont_value?: string | undefined
    webSansSerifFont_value?: string | undefined
    webFixedFont_value?: string | undefined
    webFantasyFont_value?: string | undefined
    webCursiveFont_value?: string | undefined
    defaultFixedFontSize_value?: number | undefined
    defaultFontSize_value?: number | undefined
    minFontSize_value?: number | undefined
    minLogicalFontSize_value?: number | undefined
    defaultTextEncodingFormat_value?: string | undefined
    forceDisplayScrollBar_value?: boolean | undefined
    blockNetwork_value?: boolean | undefined
    horizontalScrollBarAccess_value?: boolean | undefined
    verticalScrollBarAccess_value?: boolean | undefined
    onTouchIconUrlReceived_value?: ((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined
    onFaviconReceived_value?: ((parameter: OnFaviconReceivedEvent) => void) | undefined
    onPageVisible_value?: ((parameter: OnPageVisibleEvent) => void) | undefined
    onDataResubmitted_value?: ((parameter: OnDataResubmittedEvent) => void) | undefined
    pinchSmooth_value?: boolean | undefined
    allowWindowOpenMethod_value?: boolean | undefined
    onAudioStateChanged_value?: ((parameter: OnAudioStateChangedEvent) => void) | undefined
    onFirstContentfulPaint_value?: ((parameter: OnFirstContentfulPaintEvent) => void) | undefined
    onFirstMeaningfulPaint_value?: OnFirstMeaningfulPaintCallback | undefined
    onLargestContentfulPaint_value?: OnLargestContentfulPaintCallback | undefined
    onLoadIntercept_value?: ((parameter: OnLoadInterceptEvent) => boolean) | undefined
    onControllerAttached_value?: (() => void) | undefined
    onOverScroll_value?: ((parameter: OnOverScrollEvent) => void) | undefined
    onSafeBrowsingCheckResult_value?: OnSafeBrowsingCheckResultCallback | undefined
    onNavigationEntryCommitted_value?: OnNavigationEntryCommittedCallback | undefined
    onIntelligentTrackingPreventionResult_value?: OnIntelligentTrackingPreventionCallback | undefined
    javaScriptOnDocumentStart_value?: Array<ScriptItem> | undefined
    javaScriptOnDocumentEnd_value?: Array<ScriptItem> | undefined
    layoutMode_value?: WebLayoutMode | undefined
    nestedScroll_value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    enableNativeEmbedMode_value?: boolean | undefined
    onNativeEmbedLifecycleChange_value?: ((event: NativeEmbedDataInfo) => void) | undefined
    onNativeEmbedVisibilityChange_value?: OnNativeEmbedVisibilityChangeCallback | undefined
    onNativeEmbedGestureEvent_value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    copyOptions_value?: CopyOptions | undefined
    onOverrideUrlLoading_value?: OnOverrideUrlLoadingCallback | undefined
    textAutosizing_value?: boolean | undefined
    enableNativeMediaPlayer_value?: NativeMediaPlayerConfig | undefined
    onRenderProcessNotResponding_value?: OnRenderProcessNotRespondingCallback | undefined
    onRenderProcessResponding_value?: OnRenderProcessRespondingCallback | undefined
    selectionMenuOptions_value?: Array<ExpandedMenuItemOptions> | undefined
    onViewportFitChanged_value?: OnViewportFitChangedCallback | undefined
    onInterceptKeyboardAttach_value?: WebKeyboardCallback | undefined
    onAdsBlocked_value?: OnAdsBlockedCallback | undefined
    keyboardAvoidMode_value?: WebKeyboardAvoidMode | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enableHapticFeedback_value?: boolean | undefined
    optimizeParserBudget_value?: boolean | undefined
    enableFollowSystemFontWeight_value?: boolean | undefined
    enableWebAVSession_value?: boolean | undefined
    runJavaScriptOnDocumentStart_value?: Array<ScriptItem> | undefined
    runJavaScriptOnDocumentEnd_value?: Array<ScriptItem> | undefined
    runJavaScriptOnHeadEnd_value?: Array<ScriptItem> | undefined
    nativeEmbedOptions_value?: EmbedOptions
    forceEnableZoom_value?: boolean | undefined
    public javaScriptAccess(value: boolean | undefined): this {
        return this
    }
    public fileAccess(value: boolean | undefined): this {
        return this
    }
    public onlineImageAccess(value: boolean | undefined): this {
        return this
    }
    public domStorageAccess(value: boolean | undefined): this {
        return this
    }
    public imageAccess(value: boolean | undefined): this {
        return this
    }
    public mixedMode(value: MixedMode | undefined): this {
        return this
    }
    public zoomAccess(value: boolean | undefined): this {
        return this
    }
    public geolocationAccess(value: boolean | undefined): this {
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy | undefined): this {
        return this
    }
    public password(value: boolean | undefined): this {
        return this
    }
    public cacheMode(value: CacheMode | undefined): this {
        return this
    }
    public darkMode(value: WebDarkMode | undefined): this {
        return this
    }
    public forceDarkAccess(value: boolean | undefined): this {
        return this
    }
    public mediaOptions(value: WebMediaOptions | undefined): this {
        return this
    }
    public tableData(value: boolean | undefined): this {
        return this
    }
    public wideViewModeAccess(value: boolean | undefined): this {
        return this
    }
    public overviewModeAccess(value: boolean | undefined): this {
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        return this
    }
    public textZoomAtio(value: number | undefined): this {
        return this
    }
    public textZoomRatio(value: number | undefined): this {
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        return this
    }
    public initialScale(value: number | undefined): this {
        return this
    }
    public userAgent(value: string | undefined): this {
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        return this
    }
    public onPageEnd(value: ((parameter: OnPageEndEvent) => void) | undefined): this {
        return this
    }
    public onPageBegin(value: ((parameter: OnPageBeginEvent) => void) | undefined): this {
        return this
    }
    public onProgressChange(value: ((parameter: OnProgressChangeEvent) => void) | undefined): this {
        return this
    }
    public onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void) | undefined): this {
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        return this
    }
    public onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void) | undefined): this {
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        return this
    }
    public onAlert(value: ((parameter: OnAlertEvent) => boolean) | undefined): this {
        return this
    }
    public onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean) | undefined): this {
        return this
    }
    public onConfirm(value: ((parameter: OnConfirmEvent) => boolean) | undefined): this {
        return this
    }
    public onPrompt(value: ((parameter: OnPromptEvent) => boolean) | undefined): this {
        return this
    }
    public onConsole(value: ((parameter: OnConsoleEvent) => boolean) | undefined): this {
        return this
    }
    public onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void) | undefined): this {
        return this
    }
    public onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void) | undefined): this {
        return this
    }
    public onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void) | undefined): this {
        return this
    }
    public onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        return this
    }
    public onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined): this {
        return this
    }
    public onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void) | undefined): this {
        return this
    }
    public onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | undefined | ((event?: Literal_Object_detail) => boolean) | undefined): this {
        return this
    }
    public onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean) | undefined): this {
        return this
    }
    public onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined): this {
        return this
    }
    public onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void) | undefined): this {
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        return this
    }
    public onScaleChange(value: ((parameter: OnScaleChangeEvent) => void) | undefined): this {
        return this
    }
    public onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        return this
    }
    public onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        return this
    }
    public onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void) | undefined): this {
        return this
    }
    public onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void) | undefined): this {
        return this
    }
    public onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean) | undefined): this {
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        return this
    }
    public onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void) | undefined): this {
        return this
    }
    public onScroll(value: ((parameter: OnScrollEvent) => void) | undefined): this {
        return this
    }
    public onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        return this
    }
    public onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void) | undefined): this {
        return this
    }
    public onWindowNew(value: ((parameter: OnWindowNewEvent) => void) | undefined): this {
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        return this
    }
    public onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        return this
    }
    public webStandardFont(value: string | undefined): this {
        return this
    }
    public webSerifFont(value: string | undefined): this {
        return this
    }
    public webSansSerifFont(value: string | undefined): this {
        return this
    }
    public webFixedFont(value: string | undefined): this {
        return this
    }
    public webFantasyFont(value: string | undefined): this {
        return this
    }
    public webCursiveFont(value: string | undefined): this {
        return this
    }
    public defaultFixedFontSize(value: number | undefined): this {
        return this
    }
    public defaultFontSize(value: number | undefined): this {
        return this
    }
    public minFontSize(value: number | undefined): this {
        return this
    }
    public minLogicalFontSize(value: number | undefined): this {
        return this
    }
    public defaultTextEncodingFormat(value: string | undefined): this {
        return this
    }
    public forceDisplayScrollBar(value: boolean | undefined): this {
        return this
    }
    public blockNetwork(value: boolean | undefined): this {
        return this
    }
    public horizontalScrollBarAccess(value: boolean | undefined): this {
        return this
    }
    public verticalScrollBarAccess(value: boolean | undefined): this {
        return this
    }
    public onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        return this
    }
    public onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void) | undefined): this {
        return this
    }
    public onPageVisible(value: ((parameter: OnPageVisibleEvent) => void) | undefined): this {
        return this
    }
    public onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void) | undefined): this {
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        return this
    }
    public onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void) | undefined): this {
        return this
    }
    public onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void) | undefined): this {
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        return this
    }
    public onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean) | undefined): this {
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        return this
    }
    public onOverScroll(value: ((parameter: OnOverScrollEvent) => void) | undefined): this {
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        return this
    }
    public layoutMode(value: WebLayoutMode | undefined): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        return this
    }
    public enableNativeEmbedMode(value: boolean | undefined): this {
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        return this
    }
    public textAutosizing(value: boolean | undefined): this {
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        return this
    }
    public selectionMenuOptions(value: Array<ExpandedMenuItemOptions> | undefined): this {
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public optimizeParserBudget(value: boolean | undefined): this {
        return this
    }
    public enableFollowSystemFontWeight(value: boolean | undefined): this {
        return this
    }
    public enableWebAVSession(value: boolean | undefined): this {
        return this
    }
    public runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        return this
    }
    public runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        return this
    }
    public runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        return this
    }
    public nativeEmbedOptions(value: EmbedOptions | undefined): this {
        return this
    }
    public registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        return this
    }
    public bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        return this
    }
    public forceEnableZoom(value: boolean | undefined): this {
        return this
    }
}
export interface SslErrorEvent {
    handler: SslErrorHandler;
    error: SslError;
    url: string;
    originalUrl: string;
    referrer: string;
    isFatalError: boolean;
    isMainFrame: boolean;
}
export interface Literal_String_plainText {
    plainText: string;
}
export type Callback_Literal_String_plainText_Void = (selectedText: Literal_String_plainText) => void;
export interface ExpandedMenuItemOptions {
    content: ResourceStr;
    startIcon?: ResourceStr;
    action: ((selectedText: Literal_String_plainText) => void);
}
export interface NestedScrollOptionsExt {
    scrollUp?: NestedScrollMode;
    scrollDown?: NestedScrollMode;
    scrollRight?: NestedScrollMode;
    scrollLeft?: NestedScrollMode;
}
export interface EmbedOptions {
    supportDefaultIntrinsicSize?: boolean;
}
export class ArkWebComponent extends ArkCommonMethodComponent implements WebAttribute {
    getPeer(): ArkWebPeer {
        return (this.peer as ArkWebPeer)
    }
    public setWebOptions(value: WebOptions): this {
        if (this.checkPriority("setWebOptions")) {
            const value_casted = value as (WebOptions)
            this.getPeer()?.setWebOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptAccess(value: boolean | undefined): this {
        if (this.checkPriority("javaScriptAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.javaScriptAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public fileAccess(value: boolean | undefined): this {
        if (this.checkPriority("fileAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.fileAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onlineImageAccess(value: boolean | undefined): this {
        if (this.checkPriority("onlineImageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.onlineImageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public domStorageAccess(value: boolean | undefined): this {
        if (this.checkPriority("domStorageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.domStorageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public imageAccess(value: boolean | undefined): this {
        if (this.checkPriority("imageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.imageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public mixedMode(value: MixedMode | undefined): this {
        if (this.checkPriority("mixedMode")) {
            const value_casted = value as (MixedMode | undefined)
            this.getPeer()?.mixedModeAttribute(value_casted)
            return this
        }
        return this
    }
    public zoomAccess(value: boolean | undefined): this {
        if (this.checkPriority("zoomAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.zoomAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public geolocationAccess(value: boolean | undefined): this {
        if (this.checkPriority("geolocationAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.geolocationAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (this.checkPriority("javaScriptProxy")) {
            const value_casted = value as (JavaScriptProxy | undefined)
            this.getPeer()?.javaScriptProxyAttribute(value_casted)
            return this
        }
        return this
    }
    public password(value: boolean | undefined): this {
        if (this.checkPriority("password")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.passwordAttribute(value_casted)
            return this
        }
        return this
    }
    public cacheMode(value: CacheMode | undefined): this {
        if (this.checkPriority("cacheMode")) {
            const value_casted = value as (CacheMode | undefined)
            this.getPeer()?.cacheModeAttribute(value_casted)
            return this
        }
        return this
    }
    public darkMode(value: WebDarkMode | undefined): this {
        if (this.checkPriority("darkMode")) {
            const value_casted = value as (WebDarkMode | undefined)
            this.getPeer()?.darkModeAttribute(value_casted)
            return this
        }
        return this
    }
    public forceDarkAccess(value: boolean | undefined): this {
        if (this.checkPriority("forceDarkAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.forceDarkAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public mediaOptions(value: WebMediaOptions | undefined): this {
        if (this.checkPriority("mediaOptions")) {
            const value_casted = value as (WebMediaOptions | undefined)
            this.getPeer()?.mediaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public tableData(value: boolean | undefined): this {
        if (this.checkPriority("tableData")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.tableDataAttribute(value_casted)
            return this
        }
        return this
    }
    public wideViewModeAccess(value: boolean | undefined): this {
        if (this.checkPriority("wideViewModeAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.wideViewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public overviewModeAccess(value: boolean | undefined): this {
        if (this.checkPriority("overviewModeAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.overviewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        if (this.checkPriority("overScrollMode")) {
            const value_casted = value as (OverScrollMode | undefined)
            this.getPeer()?.overScrollModeAttribute(value_casted)
            return this
        }
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (this.checkPriority("blurOnKeyboardHideMode")) {
            const value_casted = value as (BlurOnKeyboardHideMode | undefined)
            this.getPeer()?.blurOnKeyboardHideModeAttribute(value_casted)
            return this
        }
        return this
    }
    public textZoomAtio(value: number | undefined): this {
        if (this.checkPriority("textZoomAtio")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.textZoomAtioAttribute(value_casted)
            return this
        }
        return this
    }
    public textZoomRatio(value: number | undefined): this {
        if (this.checkPriority("textZoomRatio")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.textZoomRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        if (this.checkPriority("databaseAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.databaseAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public initialScale(value: number | undefined): this {
        if (this.checkPriority("initialScale")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.initialScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public userAgent(value: string | undefined): this {
        if (this.checkPriority("userAgent")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.userAgentAttribute(value_casted)
            return this
        }
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        if (this.checkPriority("metaViewport")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.metaViewportAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageEnd(value: ((parameter: OnPageEndEvent) => void) | undefined): this {
        if (this.checkPriority("onPageEnd")) {
            const value_casted = value as (((parameter: OnPageEndEvent) => void) | undefined)
            this.getPeer()?.onPageEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageBegin(value: ((parameter: OnPageBeginEvent) => void) | undefined): this {
        if (this.checkPriority("onPageBegin")) {
            const value_casted = value as (((parameter: OnPageBeginEvent) => void) | undefined)
            this.getPeer()?.onPageBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public onProgressChange(value: ((parameter: OnProgressChangeEvent) => void) | undefined): this {
        if (this.checkPriority("onProgressChange")) {
            const value_casted = value as (((parameter: OnProgressChangeEvent) => void) | undefined)
            this.getPeer()?.onProgressChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onTitleReceive")) {
            const value_casted = value as (((parameter: OnTitleReceiveEvent) => void) | undefined)
            this.getPeer()?.onTitleReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        if (this.checkPriority("onGeolocationHide")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onGeolocationHideAttribute(value_casted)
            return this
        }
        return this
    }
    public onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void) | undefined): this {
        if (this.checkPriority("onGeolocationShow")) {
            const value_casted = value as (((parameter: OnGeolocationShowEvent) => void) | undefined)
            this.getPeer()?.onGeolocationShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        if (this.checkPriority("onRequestSelected")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onRequestSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAlert(value: ((parameter: OnAlertEvent) => boolean) | undefined): this {
        if (this.checkPriority("onAlert")) {
            const value_casted = value as (((parameter: OnAlertEvent) => boolean) | undefined)
            this.getPeer()?.onAlertAttribute(value_casted)
            return this
        }
        return this
    }
    public onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean) | undefined): this {
        if (this.checkPriority("onBeforeUnload")) {
            const value_casted = value as (((parameter: OnBeforeUnloadEvent) => boolean) | undefined)
            this.getPeer()?.onBeforeUnloadAttribute(value_casted)
            return this
        }
        return this
    }
    public onConfirm(value: ((parameter: OnConfirmEvent) => boolean) | undefined): this {
        if (this.checkPriority("onConfirm")) {
            const value_casted = value as (((parameter: OnConfirmEvent) => boolean) | undefined)
            this.getPeer()?.onConfirmAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrompt(value: ((parameter: OnPromptEvent) => boolean) | undefined): this {
        if (this.checkPriority("onPrompt")) {
            const value_casted = value as (((parameter: OnPromptEvent) => boolean) | undefined)
            this.getPeer()?.onPromptAttribute(value_casted)
            return this
        }
        return this
    }
    public onConsole(value: ((parameter: OnConsoleEvent) => boolean) | undefined): this {
        if (this.checkPriority("onConsole")) {
            const value_casted = value as (((parameter: OnConsoleEvent) => boolean) | undefined)
            this.getPeer()?.onConsoleAttribute(value_casted)
            return this
        }
        return this
    }
    public onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onErrorReceive")) {
            const value_casted = value as (((parameter: OnErrorReceiveEvent) => void) | undefined)
            this.getPeer()?.onErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onHttpErrorReceive")) {
            const value_casted = value as (((parameter: OnHttpErrorReceiveEvent) => void) | undefined)
            this.getPeer()?.onHttpErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void) | undefined): this {
        if (this.checkPriority("onDownloadStart")) {
            const value_casted = value as (((parameter: OnDownloadStartEvent) => void) | undefined)
            this.getPeer()?.onDownloadStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        if (this.checkPriority("onRefreshAccessedHistory")) {
            const value_casted = value as (((parameter: OnRefreshAccessedHistoryEvent) => void) | undefined)
            this.getPeer()?.onRefreshAccessedHistoryAttribute(value_casted)
            return this
        }
        return this
    }
    public onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined): this {
        if (this.checkPriority("onUrlLoadIntercept")) {
            const value_casted = value as (((event?: Literal_Union_String_WebResourceRequest_data) => boolean) | undefined)
            this.getPeer()?.onUrlLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    public onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void) | undefined): this {
        if (this.checkPriority("onSslErrorReceive")) {
            const value_casted = value as (((event?: Literal_Function_handler_Object_error) => void) | undefined)
            this.getPeer()?.onSslErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | undefined | ((event?: Literal_Object_detail) => boolean) | undefined): this {
        if (this.checkPriority("onRenderExited")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((parameter: OnRenderExitedEvent) => void) | undefined)
                this.getPeer()?.onRenderExited0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((event?: Literal_Object_detail) => boolean) | undefined)
                this.getPeer()?.onRenderExited1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean) | undefined): this {
        if (this.checkPriority("onShowFileSelector")) {
            const value_casted = value as (((parameter: OnShowFileSelectorEvent) => boolean) | undefined)
            this.getPeer()?.onShowFileSelectorAttribute(value_casted)
            return this
        }
        return this
    }
    public onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined): this {
        if (this.checkPriority("onFileSelectorShow")) {
            const value_casted = value as (((event?: Literal_Function_callback__Object_fileSelector) => void) | undefined)
            this.getPeer()?.onFileSelectorShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void) | undefined): this {
        if (this.checkPriority("onResourceLoad")) {
            const value_casted = value as (((parameter: OnResourceLoadEvent) => void) | undefined)
            this.getPeer()?.onResourceLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        if (this.checkPriority("onFullScreenExit")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFullScreenExitAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (this.checkPriority("onFullScreenEnter")) {
            const value_casted = value as (OnFullScreenEnterCallback | undefined)
            this.getPeer()?.onFullScreenEnterAttribute(value_casted)
            return this
        }
        return this
    }
    public onScaleChange(value: ((parameter: OnScaleChangeEvent) => void) | undefined): this {
        if (this.checkPriority("onScaleChange")) {
            const value_casted = value as (((parameter: OnScaleChangeEvent) => void) | undefined)
            this.getPeer()?.onScaleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        if (this.checkPriority("onHttpAuthRequest")) {
            const value_casted = value as (((parameter: OnHttpAuthRequestEvent) => boolean) | undefined)
            this.getPeer()?.onHttpAuthRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        if (this.checkPriority("onInterceptRequest")) {
            const value_casted = value as (((parameter: OnInterceptRequestEvent) => WebResourceResponse) | undefined)
            this.getPeer()?.onInterceptRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void) | undefined): this {
        if (this.checkPriority("onPermissionRequest")) {
            const value_casted = value as (((parameter: OnPermissionRequestEvent) => void) | undefined)
            this.getPeer()?.onPermissionRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void) | undefined): this {
        if (this.checkPriority("onScreenCaptureRequest")) {
            const value_casted = value as (((parameter: OnScreenCaptureRequestEvent) => void) | undefined)
            this.getPeer()?.onScreenCaptureRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean) | undefined): this {
        if (this.checkPriority("onContextMenuShow")) {
            const value_casted = value as (((parameter: OnContextMenuShowEvent) => boolean) | undefined)
            this.getPeer()?.onContextMenuShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (this.checkPriority("onContextMenuHide")) {
            const value_casted = value as (OnContextMenuHideCallback | undefined)
            this.getPeer()?.onContextMenuHideAttribute(value_casted)
            return this
        }
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        if (this.checkPriority("mediaPlayGestureAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.mediaPlayGestureAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onSearchResultReceive")) {
            const value_casted = value as (((parameter: OnSearchResultReceiveEvent) => void) | undefined)
            this.getPeer()?.onSearchResultReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onScroll(value: ((parameter: OnScrollEvent) => void) | undefined): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((parameter: OnScrollEvent) => void) | undefined)
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onSslErrorEventReceive")) {
            const value_casted = value as (((parameter: OnSslErrorEventReceiveEvent) => void) | undefined)
            this.getPeer()?.onSslErrorEventReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (this.checkPriority("onSslErrorEvent")) {
            const value_casted = value as (OnSslErrorEventCallback | undefined)
            this.getPeer()?.onSslErrorEventAttribute(value_casted)
            return this
        }
        return this
    }
    public onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void) | undefined): this {
        if (this.checkPriority("onClientAuthenticationRequest")) {
            const value_casted = value as (((parameter: OnClientAuthenticationEvent) => void) | undefined)
            this.getPeer()?.onClientAuthenticationRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onWindowNew(value: ((parameter: OnWindowNewEvent) => void) | undefined): this {
        if (this.checkPriority("onWindowNew")) {
            const value_casted = value as (((parameter: OnWindowNewEvent) => void) | undefined)
            this.getPeer()?.onWindowNewAttribute(value_casted)
            return this
        }
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        if (this.checkPriority("onWindowExit")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onWindowExitAttribute(value_casted)
            return this
        }
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        if (this.checkPriority("multiWindowAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.multiWindowAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean) | undefined): this {
        if (this.checkPriority("onInterceptKeyEvent")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean) | undefined)
            this.getPeer()?.onInterceptKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    public webStandardFont(value: string | undefined): this {
        if (this.checkPriority("webStandardFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webStandardFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webSerifFont(value: string | undefined): this {
        if (this.checkPriority("webSerifFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webSansSerifFont(value: string | undefined): this {
        if (this.checkPriority("webSansSerifFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webSansSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webFixedFont(value: string | undefined): this {
        if (this.checkPriority("webFixedFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webFixedFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webFantasyFont(value: string | undefined): this {
        if (this.checkPriority("webFantasyFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webFantasyFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webCursiveFont(value: string | undefined): this {
        if (this.checkPriority("webCursiveFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.webCursiveFontAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultFixedFontSize(value: number | undefined): this {
        if (this.checkPriority("defaultFixedFontSize")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.defaultFixedFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultFontSize(value: number | undefined): this {
        if (this.checkPriority("defaultFontSize")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.defaultFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minLogicalFontSize(value: number | undefined): this {
        if (this.checkPriority("minLogicalFontSize")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.minLogicalFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultTextEncodingFormat(value: string | undefined): this {
        if (this.checkPriority("defaultTextEncodingFormat")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.defaultTextEncodingFormatAttribute(value_casted)
            return this
        }
        return this
    }
    public forceDisplayScrollBar(value: boolean | undefined): this {
        if (this.checkPriority("forceDisplayScrollBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.forceDisplayScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public blockNetwork(value: boolean | undefined): this {
        if (this.checkPriority("blockNetwork")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.blockNetworkAttribute(value_casted)
            return this
        }
        return this
    }
    public horizontalScrollBarAccess(value: boolean | undefined): this {
        if (this.checkPriority("horizontalScrollBarAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.horizontalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public verticalScrollBarAccess(value: boolean | undefined): this {
        if (this.checkPriority("verticalScrollBarAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.verticalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        if (this.checkPriority("onTouchIconUrlReceived")) {
            const value_casted = value as (((parameter: OnTouchIconUrlReceivedEvent) => void) | undefined)
            this.getPeer()?.onTouchIconUrlReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    public onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void) | undefined): this {
        if (this.checkPriority("onFaviconReceived")) {
            const value_casted = value as (((parameter: OnFaviconReceivedEvent) => void) | undefined)
            this.getPeer()?.onFaviconReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageVisible(value: ((parameter: OnPageVisibleEvent) => void) | undefined): this {
        if (this.checkPriority("onPageVisible")) {
            const value_casted = value as (((parameter: OnPageVisibleEvent) => void) | undefined)
            this.getPeer()?.onPageVisibleAttribute(value_casted)
            return this
        }
        return this
    }
    public onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void) | undefined): this {
        if (this.checkPriority("onDataResubmitted")) {
            const value_casted = value as (((parameter: OnDataResubmittedEvent) => void) | undefined)
            this.getPeer()?.onDataResubmittedAttribute(value_casted)
            return this
        }
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        if (this.checkPriority("pinchSmooth")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.pinchSmoothAttribute(value_casted)
            return this
        }
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        if (this.checkPriority("allowWindowOpenMethod")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.allowWindowOpenMethodAttribute(value_casted)
            return this
        }
        return this
    }
    public onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void) | undefined): this {
        if (this.checkPriority("onAudioStateChanged")) {
            const value_casted = value as (((parameter: OnAudioStateChangedEvent) => void) | undefined)
            this.getPeer()?.onAudioStateChangedAttribute(value_casted)
            return this
        }
        return this
    }
    public onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void) | undefined): this {
        if (this.checkPriority("onFirstContentfulPaint")) {
            const value_casted = value as (((parameter: OnFirstContentfulPaintEvent) => void) | undefined)
            this.getPeer()?.onFirstContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (this.checkPriority("onFirstMeaningfulPaint")) {
            const value_casted = value as (OnFirstMeaningfulPaintCallback | undefined)
            this.getPeer()?.onFirstMeaningfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (this.checkPriority("onLargestContentfulPaint")) {
            const value_casted = value as (OnLargestContentfulPaintCallback | undefined)
            this.getPeer()?.onLargestContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean) | undefined): this {
        if (this.checkPriority("onLoadIntercept")) {
            const value_casted = value as (((parameter: OnLoadInterceptEvent) => boolean) | undefined)
            this.getPeer()?.onLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        if (this.checkPriority("onControllerAttached")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onControllerAttachedAttribute(value_casted)
            return this
        }
        return this
    }
    public onOverScroll(value: ((parameter: OnOverScrollEvent) => void) | undefined): this {
        if (this.checkPriority("onOverScroll")) {
            const value_casted = value as (((parameter: OnOverScrollEvent) => void) | undefined)
            this.getPeer()?.onOverScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (this.checkPriority("onSafeBrowsingCheckResult")) {
            const value_casted = value as (OnSafeBrowsingCheckResultCallback | undefined)
            this.getPeer()?.onSafeBrowsingCheckResultAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (this.checkPriority("onNavigationEntryCommitted")) {
            const value_casted = value as (OnNavigationEntryCommittedCallback | undefined)
            this.getPeer()?.onNavigationEntryCommittedAttribute(value_casted)
            return this
        }
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (this.checkPriority("onIntelligentTrackingPreventionResult")) {
            const value_casted = value as (OnIntelligentTrackingPreventionCallback | undefined)
            this.getPeer()?.onIntelligentTrackingPreventionResultAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("javaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.javaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("javaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.javaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutMode(value: WebLayoutMode | undefined): this {
        if (this.checkPriority("layoutMode")) {
            const value_casted = value as (WebLayoutMode | undefined)
            this.getPeer()?.layoutModeAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | NestedScrollOptionsExt | undefined)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNativeEmbedMode(value: boolean | undefined): this {
        if (this.checkPriority("enableNativeEmbedMode")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableNativeEmbedModeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (this.checkPriority("onNativeEmbedLifecycleChange")) {
            const value_casted = value as (((event: NativeEmbedDataInfo) => void) | undefined)
            this.getPeer()?.onNativeEmbedLifecycleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (this.checkPriority("onNativeEmbedVisibilityChange")) {
            const value_casted = value as (OnNativeEmbedVisibilityChangeCallback | undefined)
            this.getPeer()?.onNativeEmbedVisibilityChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (this.checkPriority("onNativeEmbedGestureEvent")) {
            const value_casted = value as (((event: NativeEmbedTouchInfo) => void) | undefined)
            this.getPeer()?.onNativeEmbedGestureEventAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.copyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (this.checkPriority("onOverrideUrlLoading")) {
            const value_casted = value as (OnOverrideUrlLoadingCallback | undefined)
            this.getPeer()?.onOverrideUrlLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    public textAutosizing(value: boolean | undefined): this {
        if (this.checkPriority("textAutosizing")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.textAutosizingAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (this.checkPriority("enableNativeMediaPlayer")) {
            const value_casted = value as (NativeMediaPlayerConfig | undefined)
            this.getPeer()?.enableNativeMediaPlayerAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (this.checkPriority("onRenderProcessNotResponding")) {
            const value_casted = value as (OnRenderProcessNotRespondingCallback | undefined)
            this.getPeer()?.onRenderProcessNotRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (this.checkPriority("onRenderProcessResponding")) {
            const value_casted = value as (OnRenderProcessRespondingCallback | undefined)
            this.getPeer()?.onRenderProcessRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    public selectionMenuOptions(value: Array<ExpandedMenuItemOptions> | undefined): this {
        if (this.checkPriority("selectionMenuOptions")) {
            const value_casted = value as (Array<ExpandedMenuItemOptions> | undefined)
            this.getPeer()?.selectionMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (this.checkPriority("onViewportFitChanged")) {
            const value_casted = value as (OnViewportFitChangedCallback | undefined)
            this.getPeer()?.onViewportFitChangedAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (this.checkPriority("onInterceptKeyboardAttach")) {
            const value_casted = value as (WebKeyboardCallback | undefined)
            this.getPeer()?.onInterceptKeyboardAttachAttribute(value_casted)
            return this
        }
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (this.checkPriority("onAdsBlocked")) {
            const value_casted = value as (OnAdsBlockedCallback | undefined)
            this.getPeer()?.onAdsBlockedAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (this.checkPriority("keyboardAvoidMode")) {
            const value_casted = value as (WebKeyboardAvoidMode | undefined)
            this.getPeer()?.keyboardAvoidModeAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public optimizeParserBudget(value: boolean | undefined): this {
        if (this.checkPriority("optimizeParserBudget")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.optimizeParserBudgetAttribute(value_casted)
            return this
        }
        return this
    }
    public enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (this.checkPriority("enableFollowSystemFontWeight")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableFollowSystemFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public enableWebAVSession(value: boolean | undefined): this {
        if (this.checkPriority("enableWebAVSession")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableWebAVSessionAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.runJavaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.runJavaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnHeadEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.runJavaScriptOnHeadEndAttribute(value_casted)
            return this
        }
        return this
    }
    public nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (this.checkPriority("nativeEmbedOptions")) {
            const value_casted = value as (EmbedOptions | undefined)
            this.getPeer()?.nativeEmbedOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (this.checkPriority("registerNativeEmbedRule")) {
            const tag_casted = tag as (string | undefined)
            const type_casted = type as (string | undefined)
            this.getPeer()?.registerNativeEmbedRuleAttribute(tag_casted, type_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const elementType_casted = elementType as (WebElementType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (WebResponseType | undefined)
            const options_casted = options as (SelectionMenuOptionsExt)
            this.getPeer()?.bindSelectionMenuAttribute(elementType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }

    public forceEnableZoom(value: boolean | undefined): this {
        if (this.checkPriority("forceEnableZoom")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.forceEnableZoomAttribute(value_casted)
            return this
        }
        return this
    }
}
/** @memo */
export function Web(
    /** @memo */
    style: ((attributes: WebAttribute) => void) | undefined,
    value: WebOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkWebComponent()
    })
    NodeAttach<ArkWebPeer>((): ArkWebPeer => ArkWebPeer.create(receiver), (_: ArkWebPeer) => {
        receiver.setWebOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

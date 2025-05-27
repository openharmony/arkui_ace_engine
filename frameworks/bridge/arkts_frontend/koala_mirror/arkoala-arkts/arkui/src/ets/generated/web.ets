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
import { CallbackTransformer } from "./../CallbackTransformer"
import { WebviewController, WebviewControllerInternal } from "./arkui-external"
import { Resource } from "./resource"
import { Callback_String_Void } from "./grid_row"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, Callback_KeyEvent_Boolean, KeyEvent, NestedScrollOptions, CustomBuilder, TouchEvent, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Void } from "./ability_component"
import { CopyOptions, NestedScrollMode } from "./enums"
import { EditMenuOptions, MenuType } from "./text_common"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Position, ResourceStr } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    private getTitle_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getTitle(this.peer!.ptr)
        return retval
    }
    private getMode_serialize(): FileSelectorMode {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getMode(this.peer!.ptr)
        return TypeChecker.FileSelectorMode_FromNumeric(retval)
    }
    private getAcceptType_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptType(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
    public setWebController(controller: WebviewController): void {
        const controller_casted = controller as (WebviewController)
        this.setWebController_serialize(controller_casted)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
            thisSerializer.writeInt8(0)
            const data_0  = data as string
            thisSerializer.writeString(data_0)
        }
        else if (RuntimeType.NUMBER == data_type) {
            thisSerializer.writeInt8(1)
            const data_1  = data as number
            thisSerializer.writeNumber(data_1)
        }
        else if (TypeChecker.isResource(data, false, false, false, false, false)) {
            thisSerializer.writeInt8(2)
            const data_2  = data as Resource
            thisSerializer.writeResource(data_2)
        }
        else if (TypeChecker.isNativeBuffer(data)) {
            thisSerializer.writeInt8(3)
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
    public setCookie(): void {
        this.setCookie_serialize()
        return
    }
    public saveCookie(): void {
        this.saveCookie_serialize()
        return
    }
    private setCookie_serialize(): void {
        ArkUIGeneratedNativeModule._WebCookie_setCookie(this.peer!.ptr)
    }
    private saveCookie_serialize(): void {
        ArkUIGeneratedNativeModule._WebCookie_saveCookie(this.peer!.ptr)
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
    public setGestureEventResult(result: boolean): void {
        const result_casted = result as (boolean)
        this.setGestureEventResult_serialize(result_casted)
        return
    }
    private setGestureEventResult_serialize(result: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult(this.peer!.ptr, result ? 1 : 0)
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
    public runJavaScript(options: Literal_String_script_Callback_String_Void_callback_): void {
        const options_casted = options as (Literal_String_script_Callback_String_Void_callback_)
        this.runJavaScript_serialize(options_casted)
        return
    }
    public loadData(options: Literal_String_baseUrl_data_encoding_historyUrl_mimeType): void {
        const options_casted = options as (Literal_String_baseUrl_data_encoding_historyUrl_mimeType)
        this.loadData_serialize(options_casted)
        return
    }
    public loadUrl(options: Literal_Union_String_Resource_url_Array_Header_headers): void {
        const options_casted = options as (Literal_Union_String_Resource_url_Array_Header_headers)
        this.loadUrl_serialize(options_casted)
        return
    }
    public refresh(): void {
        this.refresh_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    public registerJavaScriptProxy(options: Literal_Object_object__String_name_Array_String_methodList): void {
        const options_casted = options as (Literal_Object_object__String_name_Array_String_methodList)
        this.registerJavaScriptProxy_serialize(options_casted)
        return
    }
    public deleteJavaScriptRegister(name: string): void {
        const name_casted = name as (string)
        this.deleteJavaScriptRegister_serialize(name_casted)
        return
    }
    public getHitTest(): HitTestType {
        return this.getHitTest_serialize()
    }
    public requestFocus(): void {
        this.requestFocus_serialize()
        return
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
    public backward(): void {
        this.backward_serialize()
        return
    }
    public forward(): void {
        this.forward_serialize()
        return
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
    private runJavaScript_serialize(options: Literal_String_script_Callback_String_Void_callback_): void {
        const thisSerializer : Serializer = Serializer.hold()
        const options_script  = options.script
        thisSerializer.writeString(options_script)
        const options_callback_  = options.callback_
        let options_callback__type : int32 = RuntimeType.UNDEFINED
        options_callback__type = runtimeType(options_callback_)
        thisSerializer.writeInt8(options_callback__type)
        if ((RuntimeType.UNDEFINED) != (options_callback__type)) {
            const options_callback__value  = options_callback_!
            thisSerializer.holdAndWriteCallback(options_callback__value)
        }
        ArkUIGeneratedNativeModule._WebController_runJavaScript(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private loadData_serialize(options: Literal_String_baseUrl_data_encoding_historyUrl_mimeType): void {
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
        thisSerializer.writeInt8(options_baseUrl_type)
        if ((RuntimeType.UNDEFINED) != (options_baseUrl_type)) {
            const options_baseUrl_value  = options_baseUrl!
            thisSerializer.writeString(options_baseUrl_value)
        }
        const options_historyUrl  = options.historyUrl
        let options_historyUrl_type : int32 = RuntimeType.UNDEFINED
        options_historyUrl_type = runtimeType(options_historyUrl)
        thisSerializer.writeInt8(options_historyUrl_type)
        if ((RuntimeType.UNDEFINED) != (options_historyUrl_type)) {
            const options_historyUrl_value  = options_historyUrl!
            thisSerializer.writeString(options_historyUrl_value)
        }
        ArkUIGeneratedNativeModule._WebController_loadData(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private loadUrl_serialize(options: Literal_Union_String_Resource_url_Array_Header_headers): void {
        const thisSerializer : Serializer = Serializer.hold()
        const options_url  = options.url
        let options_url_type : int32 = RuntimeType.UNDEFINED
        options_url_type = runtimeType(options_url)
        if (RuntimeType.STRING == options_url_type) {
            thisSerializer.writeInt8(0)
            const options_url_0  = options_url as string
            thisSerializer.writeString(options_url_0)
        }
        else if (RuntimeType.OBJECT == options_url_type) {
            thisSerializer.writeInt8(1)
            const options_url_1  = options_url as Resource
            thisSerializer.writeResource(options_url_1)
        }
        const options_headers  = options.headers
        let options_headers_type : int32 = RuntimeType.UNDEFINED
        options_headers_type = runtimeType(options_headers)
        thisSerializer.writeInt8(options_headers_type)
        if ((RuntimeType.UNDEFINED) != (options_headers_type)) {
            const options_headers_value  = options_headers!
            thisSerializer.writeInt32(options_headers_value.length as int32)
            for (let i = 0; i < options_headers_value.length; i++) {
                const options_headers_value_element : Header = options_headers_value[i]
                thisSerializer.writeHeader(options_headers_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebController_loadUrl(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private refresh_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_refresh(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_stop(this.peer!.ptr)
    }
    private registerJavaScriptProxy_serialize(options: Literal_Object_object__String_name_Array_String_methodList): void {
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
        ArkUIGeneratedNativeModule._WebController_registerJavaScriptProxy(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deleteJavaScriptRegister_serialize(name: string): void {
        ArkUIGeneratedNativeModule._WebController_deleteJavaScriptRegister(this.peer!.ptr, name)
    }
    private getHitTest_serialize(): HitTestType {
        const retval  = ArkUIGeneratedNativeModule._WebController_getHitTest(this.peer!.ptr)
        return TypeChecker.HitTestType_FromNumeric(retval)
    }
    private requestFocus_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_requestFocus(this.peer!.ptr)
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
    private backward_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_backward(this.peer!.ptr)
    }
    private forward_serialize(): void {
        ArkUIGeneratedNativeModule._WebController_forward(this.peer!.ptr)
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWebPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Web_construct(peerId, flags)
        const _peer  = new ArkWebPeer(_peerPtr, peerId, "Web", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWebOptionsAttribute(value: WebOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWebOptions(value)
        ArkUIGeneratedNativeModule._WebInterface_setWebOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptAccess(this.peer.ptr, value ? 1 : 0)
    }
    fileAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_fileAccess(this.peer.ptr, value ? 1 : 0)
    }
    onlineImageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_onlineImageAccess(this.peer.ptr, value ? 1 : 0)
    }
    domStorageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_domStorageAccess(this.peer.ptr, value ? 1 : 0)
    }
    imageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_imageAccess(this.peer.ptr, value ? 1 : 0)
    }
    mixedModeAttribute(value: MixedMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_mixedMode(this.peer.ptr, TypeChecker.MixedMode_ToNumeric(value))
    }
    zoomAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_zoomAccess(this.peer.ptr, value ? 1 : 0)
    }
    geolocationAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_geolocationAccess(this.peer.ptr, value ? 1 : 0)
    }
    javaScriptProxyAttribute(value: JavaScriptProxy): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeJavaScriptProxy(value)
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptProxy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    passwordAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_password(this.peer.ptr, value ? 1 : 0)
    }
    cacheModeAttribute(value: CacheMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_cacheMode(this.peer.ptr, TypeChecker.CacheMode_ToNumeric(value))
    }
    darkModeAttribute(value: WebDarkMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_darkMode(this.peer.ptr, TypeChecker.WebDarkMode_ToNumeric(value))
    }
    forceDarkAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_forceDarkAccess(this.peer.ptr, value ? 1 : 0)
    }
    mediaOptionsAttribute(value: WebMediaOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWebMediaOptions(value)
        ArkUIGeneratedNativeModule._WebAttribute_mediaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tableDataAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_tableData(this.peer.ptr, value ? 1 : 0)
    }
    wideViewModeAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_wideViewModeAccess(this.peer.ptr, value ? 1 : 0)
    }
    overviewModeAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_overviewModeAccess(this.peer.ptr, value ? 1 : 0)
    }
    overScrollModeAttribute(value: OverScrollMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_overScrollMode(this.peer.ptr, TypeChecker.OverScrollMode_ToNumeric(value))
    }
    textZoomAtioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_textZoomAtio(this.peer.ptr, value)
    }
    textZoomRatioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_textZoomRatio(this.peer.ptr, value)
    }
    databaseAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_databaseAccess(this.peer.ptr, value ? 1 : 0)
    }
    initialScaleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_initialScale(this.peer.ptr, value)
    }
    userAgentAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_userAgent(this.peer.ptr, value)
    }
    metaViewportAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_metaViewport(this.peer.ptr, value ? 1 : 0)
    }
    onPageEndAttribute(value: ((parameter: OnPageEndEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageBeginAttribute(value: ((parameter: OnPageBeginEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onProgressChangeAttribute(value: ((parameter: OnProgressChangeEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onProgressChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTitleReceiveAttribute(value: ((parameter: OnTitleReceiveEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onTitleReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationHideAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationShowAttribute(value: ((parameter: OnGeolocationShowEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestSelectedAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRequestSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAlertAttribute(value: ((parameter: OnAlertEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAlert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBeforeUnloadAttribute(value: ((parameter: OnBeforeUnloadEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onBeforeUnload(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onConfirmAttribute(value: ((parameter: OnConfirmEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onConfirm(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPromptAttribute(value: ((parameter: OnPromptEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPrompt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onConsoleAttribute(value: ((parameter: OnConsoleEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onConsole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorReceiveAttribute(value: ((parameter: OnErrorReceiveEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpErrorReceiveAttribute(value: ((parameter: OnHttpErrorReceiveEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onHttpErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDownloadStartAttribute(value: ((parameter: OnDownloadStartEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onDownloadStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRefreshAccessedHistoryAttribute(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRefreshAccessedHistory(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUrlLoadInterceptAttribute(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onUrlLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorReceiveAttribute(value: ((event?: Literal_Function_handler_Object_error) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited0Attribute(value: ((parameter: OnRenderExitedEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited1Attribute(value: ((event?: Literal_Object_detail) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onShowFileSelectorAttribute(value: ((parameter: OnShowFileSelectorEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onShowFileSelector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFileSelectorShowAttribute(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFileSelectorShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onResourceLoadAttribute(value: ((parameter: OnResourceLoadEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onResourceLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenExitAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenEnterAttribute(value: OnFullScreenEnterCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScaleChangeAttribute(value: ((parameter: OnScaleChangeEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScaleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpAuthRequestAttribute(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onHttpAuthRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptRequestAttribute(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPermissionRequestAttribute(value: ((parameter: OnPermissionRequestEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPermissionRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScreenCaptureRequestAttribute(value: ((parameter: OnScreenCaptureRequestEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScreenCaptureRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuShowAttribute(value: ((parameter: OnContextMenuShowEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuHideAttribute(value: OnContextMenuHideCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mediaPlayGestureAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_mediaPlayGestureAccess(this.peer.ptr, value ? 1 : 0)
    }
    onSearchResultReceiveAttribute(value: ((parameter: OnSearchResultReceiveEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSearchResultReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((parameter: OnScrollEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventReceiveAttribute(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEventReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventAttribute(value: OnSslErrorEventCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClientAuthenticationRequestAttribute(value: ((parameter: OnClientAuthenticationEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onClientAuthenticationRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowNewAttribute(value: ((parameter: OnWindowNewEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onWindowNew(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowExitAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onWindowExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    multiWindowAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_multiWindowAccess(this.peer.ptr, value ? 1 : 0)
    }
    onInterceptKeyEventAttribute(value: ((parameter: KeyEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    webStandardFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webStandardFont(this.peer.ptr, value)
    }
    webSerifFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webSerifFont(this.peer.ptr, value)
    }
    webSansSerifFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webSansSerifFont(this.peer.ptr, value)
    }
    webFixedFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webFixedFont(this.peer.ptr, value)
    }
    webFantasyFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webFantasyFont(this.peer.ptr, value)
    }
    webCursiveFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webCursiveFont(this.peer.ptr, value)
    }
    defaultFixedFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultFixedFontSize(this.peer.ptr, value)
    }
    defaultFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultFontSize(this.peer.ptr, value)
    }
    minFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_minFontSize(this.peer.ptr, value)
    }
    minLogicalFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_minLogicalFontSize(this.peer.ptr, value)
    }
    defaultTextEncodingFormatAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultTextEncodingFormat(this.peer.ptr, value)
    }
    forceDisplayScrollBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_forceDisplayScrollBar(this.peer.ptr, value ? 1 : 0)
    }
    blockNetworkAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_blockNetwork(this.peer.ptr, value ? 1 : 0)
    }
    horizontalScrollBarAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_horizontalScrollBarAccess(this.peer.ptr, value ? 1 : 0)
    }
    verticalScrollBarAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_verticalScrollBarAccess(this.peer.ptr, value ? 1 : 0)
    }
    onTouchIconUrlReceivedAttribute(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onTouchIconUrlReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFaviconReceivedAttribute(value: ((parameter: OnFaviconReceivedEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFaviconReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageVisibleAttribute(value: ((parameter: OnPageVisibleEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageVisible(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDataResubmittedAttribute(value: ((parameter: OnDataResubmittedEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onDataResubmitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pinchSmoothAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_pinchSmooth(this.peer.ptr, value ? 1 : 0)
    }
    allowWindowOpenMethodAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_allowWindowOpenMethod(this.peer.ptr, value ? 1 : 0)
    }
    onAudioStateChangedAttribute(value: ((parameter: OnAudioStateChangedEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAudioStateChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstContentfulPaintAttribute(value: ((parameter: OnFirstContentfulPaintEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFirstContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onLargestContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadInterceptAttribute(value: ((parameter: OnLoadInterceptEvent) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onControllerAttachedAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onControllerAttached(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onOverScrollAttribute(value: ((parameter: OnOverScrollEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onOverScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNavigationEntryCommitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentStartAttribute(value: Array<ScriptItem>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ScriptItem = value[i]
            thisSerializer.writeScriptItem(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentEndAttribute(value: Array<ScriptItem>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ScriptItem = value[i]
            thisSerializer.writeScriptItem(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutModeAttribute(value: WebLayoutMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_layoutMode(this.peer.ptr, TypeChecker.WebLayoutMode_ToNumeric(value))
    }
    nestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isNestedScrollOptions(value, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as NestedScrollOptions
            thisSerializer.writeNestedScrollOptions(value_0)
        }
        else if (TypeChecker.isNestedScrollOptionsExt(value, false, false, false, false)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as NestedScrollOptionsExt
            thisSerializer.writeNestedScrollOptionsExt(value_1)
        }
        ArkUIGeneratedNativeModule._WebAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNativeEmbedModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeEmbedMode(this.peer.ptr, value ? 1 : 0)
    }
    onNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._WebAttribute_copyOptions(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    onOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onOverrideUrlLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textAutosizingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_textAutosizing(this.peer.ptr, value ? 1 : 0)
    }
    enableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNativeMediaPlayerConfig(value)
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeMediaPlayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableSmoothDragResizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableSmoothDragResize(this.peer.ptr, value ? 1 : 0)
    }
    onRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessNotResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuOptionsAttribute(value: Array<ExpandedMenuItemOptions>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ExpandedMenuItemOptions = value[i]
            thisSerializer.writeExpandedMenuItemOptions(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_selectionMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onViewportFitChangedAttribute(value: OnViewportFitChangedCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onViewportFitChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptKeyboardAttachAttribute(value: WebKeyboardCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAdsBlockedAttribute(value: OnAdsBlockedCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAdsBlocked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardAvoidModeAttribute(value: WebKeyboardAvoidMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_keyboardAvoidMode(this.peer.ptr, TypeChecker.WebKeyboardAvoidMode_ToNumeric(value))
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEditMenuOptions(value)
        ArkUIGeneratedNativeModule._WebAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    registerNativeEmbedRuleAttribute(tag: string, type: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_registerNativeEmbedRule(this.peer.ptr, tag, type)
    }
    bindSelectionMenuAttribute(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionMenuOptionsExt(options_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_bindSelectionMenu(this.peer.ptr, TypeChecker.WebElementType_ToNumeric(elementType), thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.WebResponseType_ToNumeric(responseType))
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
    controller: WebController | WebviewController;
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
    javaScriptAccess(value: boolean): this
    fileAccess(value: boolean): this
    onlineImageAccess(value: boolean): this
    domStorageAccess(value: boolean): this
    imageAccess(value: boolean): this
    mixedMode(value: MixedMode): this
    zoomAccess(value: boolean): this
    geolocationAccess(value: boolean): this
    javaScriptProxy(value: JavaScriptProxy): this
    password(value: boolean): this
    cacheMode(value: CacheMode): this
    darkMode(value: WebDarkMode): this
    forceDarkAccess(value: boolean): this
    mediaOptions(value: WebMediaOptions): this
    tableData(value: boolean): this
    wideViewModeAccess(value: boolean): this
    overviewModeAccess(value: boolean): this
    overScrollMode(value: OverScrollMode): this
    textZoomAtio(value: number): this
    textZoomRatio(value: number): this
    databaseAccess(value: boolean): this
    initialScale(value: number): this
    userAgent(value: string): this
    metaViewport(value: boolean): this
    onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this
    onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this
    onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this
    onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this
    onGeolocationHide(value: (() => void)): this
    onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this
    onRequestSelected(value: (() => void)): this
    onAlert(value: ((parameter: OnAlertEvent) => boolean)): this
    onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this
    onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this
    onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this
    onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this
    onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this
    onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this
    onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this
    onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this
    onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): this
    onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void)): this
    onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: Literal_Object_detail) => boolean)): this
    onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this
    onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): this
    onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this
    onFullScreenExit(value: (() => void)): this
    onFullScreenEnter(value: OnFullScreenEnterCallback): this
    onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this
    onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this
    onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this
    onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this
    onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this
    onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this
    onContextMenuHide(value: OnContextMenuHideCallback): this
    mediaPlayGestureAccess(value: boolean): this
    onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this
    onScroll(value: ((parameter: OnScrollEvent) => void)): this
    onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this
    onSslErrorEvent(value: OnSslErrorEventCallback): this
    onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this
    onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this
    onWindowExit(value: (() => void)): this
    multiWindowAccess(value: boolean): this
    onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this
    webStandardFont(value: string): this
    webSerifFont(value: string): this
    webSansSerifFont(value: string): this
    webFixedFont(value: string): this
    webFantasyFont(value: string): this
    webCursiveFont(value: string): this
    defaultFixedFontSize(value: number): this
    defaultFontSize(value: number): this
    minFontSize(value: number): this
    minLogicalFontSize(value: number): this
    defaultTextEncodingFormat(value: string): this
    forceDisplayScrollBar(value: boolean): this
    blockNetwork(value: boolean): this
    horizontalScrollBarAccess(value: boolean): this
    verticalScrollBarAccess(value: boolean): this
    onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this
    onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this
    onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this
    onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this
    pinchSmooth(value: boolean): this
    allowWindowOpenMethod(value: boolean): this
    onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this
    onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this
    onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this
    onControllerAttached(value: (() => void)): this
    onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this
    javaScriptOnDocumentStart(value: Array<ScriptItem>): this
    javaScriptOnDocumentEnd(value: Array<ScriptItem>): this
    layoutMode(value: WebLayoutMode): this
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this
    enableNativeEmbedMode(value: boolean): this
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this
    copyOptions(value: CopyOptions): this
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this
    textAutosizing(value: boolean): this
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this
    enableSmoothDragResize(value: boolean): this
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this
    selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this
    onViewportFitChanged(value: OnViewportFitChangedCallback): this
    onInterceptKeyboardAttach(value: WebKeyboardCallback): this
    onAdsBlocked(value: OnAdsBlockedCallback): this
    keyboardAvoidMode(value: WebKeyboardAvoidMode): this
    editMenuOptions(value: EditMenuOptions): this
    enableHapticFeedback(value: boolean): this
    registerNativeEmbedRule(tag: string, type: string): this
    bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this
    attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIWebAttribute extends UICommonMethod {
    @memo
    javaScriptAccess(value: boolean): this
    @memo
    fileAccess(value: boolean): this
    @memo
    onlineImageAccess(value: boolean): this
    @memo
    domStorageAccess(value: boolean): this
    @memo
    imageAccess(value: boolean): this
    @memo
    mixedMode(value: MixedMode): this
    @memo
    zoomAccess(value: boolean): this
    @memo
    geolocationAccess(value: boolean): this
    @memo
    javaScriptProxy(value: JavaScriptProxy): this
    @memo
    password(value: boolean): this
    @memo
    cacheMode(value: CacheMode): this
    @memo
    darkMode(value: WebDarkMode): this
    @memo
    forceDarkAccess(value: boolean): this
    @memo
    mediaOptions(value: WebMediaOptions): this
    @memo
    tableData(value: boolean): this
    @memo
    wideViewModeAccess(value: boolean): this
    @memo
    overviewModeAccess(value: boolean): this
    @memo
    overScrollMode(value: OverScrollMode): this
    @memo
    textZoomAtio(value: number): this
    @memo
    textZoomRatio(value: number): this
    @memo
    databaseAccess(value: boolean): this
    @memo
    initialScale(value: number): this
    @memo
    userAgent(value: string): this
    @memo
    metaViewport(value: boolean): this
    @memo
    onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this
    @memo
    onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this
    @memo
    onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this
    @memo
    onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this
    @memo
    onGeolocationHide(value: (() => void)): this
    @memo
    onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this
    @memo
    onRequestSelected(value: (() => void)): this
    @memo
    onAlert(value: ((parameter: OnAlertEvent) => boolean)): this
    @memo
    onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this
    @memo
    onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this
    @memo
    onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this
    @memo
    onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this
    @memo
    onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this
    @memo
    onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this
    @memo
    onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this
    @memo
    onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this
    @memo
    onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): this
    @memo
    onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void)): this
    @memo
    onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: Literal_Object_detail) => boolean)): this
    @memo
    onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this
    @memo
    onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): this
    @memo
    onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this
    @memo
    onFullScreenExit(value: (() => void)): this
    @memo
    onFullScreenEnter(value: OnFullScreenEnterCallback): this
    @memo
    onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this
    @memo
    onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this
    @memo
    onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this
    @memo
    onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this
    @memo
    onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this
    @memo
    onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this
    @memo
    onContextMenuHide(value: OnContextMenuHideCallback): this
    @memo
    mediaPlayGestureAccess(value: boolean): this
    @memo
    onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this
    @memo
    onScroll(value: ((parameter: OnScrollEvent) => void)): this
    @memo
    onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this
    @memo
    onSslErrorEvent(value: OnSslErrorEventCallback): this
    @memo
    onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this
    @memo
    onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this
    @memo
    onWindowExit(value: (() => void)): this
    @memo
    multiWindowAccess(value: boolean): this
    @memo
    onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this
    @memo
    webStandardFont(value: string): this
    @memo
    webSerifFont(value: string): this
    @memo
    webSansSerifFont(value: string): this
    @memo
    webFixedFont(value: string): this
    @memo
    webFantasyFont(value: string): this
    @memo
    webCursiveFont(value: string): this
    @memo
    defaultFixedFontSize(value: number): this
    @memo
    defaultFontSize(value: number): this
    @memo
    minFontSize(value: number): this
    @memo
    minLogicalFontSize(value: number): this
    @memo
    defaultTextEncodingFormat(value: string): this
    @memo
    forceDisplayScrollBar(value: boolean): this
    @memo
    blockNetwork(value: boolean): this
    @memo
    horizontalScrollBarAccess(value: boolean): this
    @memo
    verticalScrollBarAccess(value: boolean): this
    @memo
    onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this
    @memo
    onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this
    @memo
    onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this
    @memo
    onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this
    @memo
    pinchSmooth(value: boolean): this
    @memo
    allowWindowOpenMethod(value: boolean): this
    @memo
    onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this
    @memo
    onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this
    @memo
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this
    @memo
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this
    @memo
    onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this
    @memo
    onControllerAttached(value: (() => void)): this
    @memo
    onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this
    @memo
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this
    @memo
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this
    @memo
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this
    @memo
    javaScriptOnDocumentStart(value: Array<ScriptItem>): this
    @memo
    javaScriptOnDocumentEnd(value: Array<ScriptItem>): this
    @memo
    layoutMode(value: WebLayoutMode): this
    @memo
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this
    @memo
    enableNativeEmbedMode(value: boolean): this
    @memo
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this
    @memo
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this
    @memo
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this
    @memo
    copyOptions(value: CopyOptions): this
    @memo
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this
    @memo
    textAutosizing(value: boolean): this
    @memo
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this
    @memo
    enableSmoothDragResize(value: boolean): this
    @memo
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this
    @memo
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this
    @memo
    selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this
    @memo
    onViewportFitChanged(value: OnViewportFitChangedCallback): this
    @memo
    onInterceptKeyboardAttach(value: WebKeyboardCallback): this
    @memo
    onAdsBlocked(value: OnAdsBlockedCallback): this
    @memo
    keyboardAvoidMode(value: WebKeyboardAvoidMode): this
    @memo
    editMenuOptions(value: EditMenuOptions): this
    @memo
    enableHapticFeedback(value: boolean): this
    @memo
    registerNativeEmbedRule(tag: string, type: string): this
    @memo
    bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this
    @memo
    attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkWebStyle extends ArkCommonMethodStyle implements WebAttribute {
    javaScriptAccess_value?: boolean
    fileAccess_value?: boolean
    onlineImageAccess_value?: boolean
    domStorageAccess_value?: boolean
    imageAccess_value?: boolean
    mixedMode_value?: MixedMode
    zoomAccess_value?: boolean
    geolocationAccess_value?: boolean
    javaScriptProxy_value?: JavaScriptProxy
    password_value?: boolean
    cacheMode_value?: CacheMode
    darkMode_value?: WebDarkMode
    forceDarkAccess_value?: boolean
    mediaOptions_value?: WebMediaOptions
    tableData_value?: boolean
    wideViewModeAccess_value?: boolean
    overviewModeAccess_value?: boolean
    overScrollMode_value?: OverScrollMode
    textZoomAtio_value?: number
    textZoomRatio_value?: number
    databaseAccess_value?: boolean
    initialScale_value?: number
    userAgent_value?: string
    metaViewport_value?: boolean
    onPageEnd_value?: ((parameter: OnPageEndEvent) => void)
    onPageBegin_value?: ((parameter: OnPageBeginEvent) => void)
    onProgressChange_value?: ((parameter: OnProgressChangeEvent) => void)
    onTitleReceive_value?: ((parameter: OnTitleReceiveEvent) => void)
    onGeolocationHide_value?: (() => void)
    onGeolocationShow_value?: ((parameter: OnGeolocationShowEvent) => void)
    onRequestSelected_value?: (() => void)
    onAlert_value?: ((parameter: OnAlertEvent) => boolean)
    onBeforeUnload_value?: ((parameter: OnBeforeUnloadEvent) => boolean)
    onConfirm_value?: ((parameter: OnConfirmEvent) => boolean)
    onPrompt_value?: ((parameter: OnPromptEvent) => boolean)
    onConsole_value?: ((parameter: OnConsoleEvent) => boolean)
    onErrorReceive_value?: ((parameter: OnErrorReceiveEvent) => void)
    onHttpErrorReceive_value?: ((parameter: OnHttpErrorReceiveEvent) => void)
    onDownloadStart_value?: ((parameter: OnDownloadStartEvent) => void)
    onRefreshAccessedHistory_value?: ((parameter: OnRefreshAccessedHistoryEvent) => void)
    onUrlLoadIntercept_value?: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)
    onSslErrorReceive_value?: ((event?: Literal_Function_handler_Object_error) => void)
    onRenderExited_value?: ((parameter: OnRenderExitedEvent) => void)
    onShowFileSelector_value?: ((parameter: OnShowFileSelectorEvent) => boolean)
    onFileSelectorShow_value?: ((event?: Literal_Function_callback__Object_fileSelector) => void)
    onResourceLoad_value?: ((parameter: OnResourceLoadEvent) => void)
    onFullScreenExit_value?: (() => void)
    onFullScreenEnter_value?: OnFullScreenEnterCallback
    onScaleChange_value?: ((parameter: OnScaleChangeEvent) => void)
    onHttpAuthRequest_value?: ((parameter: OnHttpAuthRequestEvent) => boolean)
    onInterceptRequest_value?: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)
    onPermissionRequest_value?: ((parameter: OnPermissionRequestEvent) => void)
    onScreenCaptureRequest_value?: ((parameter: OnScreenCaptureRequestEvent) => void)
    onContextMenuShow_value?: ((parameter: OnContextMenuShowEvent) => boolean)
    onContextMenuHide_value?: OnContextMenuHideCallback
    mediaPlayGestureAccess_value?: boolean
    onSearchResultReceive_value?: ((parameter: OnSearchResultReceiveEvent) => void)
    onScroll_value?: ((parameter: OnScrollEvent) => void)
    onSslErrorEventReceive_value?: ((parameter: OnSslErrorEventReceiveEvent) => void)
    onSslErrorEvent_value?: OnSslErrorEventCallback
    onClientAuthenticationRequest_value?: ((parameter: OnClientAuthenticationEvent) => void)
    onWindowNew_value?: ((parameter: OnWindowNewEvent) => void)
    onWindowExit_value?: (() => void)
    multiWindowAccess_value?: boolean
    onInterceptKeyEvent_value?: ((parameter: KeyEvent) => boolean)
    webStandardFont_value?: string
    webSerifFont_value?: string
    webSansSerifFont_value?: string
    webFixedFont_value?: string
    webFantasyFont_value?: string
    webCursiveFont_value?: string
    defaultFixedFontSize_value?: number
    defaultFontSize_value?: number
    minFontSize_value?: number
    minLogicalFontSize_value?: number
    defaultTextEncodingFormat_value?: string
    forceDisplayScrollBar_value?: boolean
    blockNetwork_value?: boolean
    horizontalScrollBarAccess_value?: boolean
    verticalScrollBarAccess_value?: boolean
    onTouchIconUrlReceived_value?: ((parameter: OnTouchIconUrlReceivedEvent) => void)
    onFaviconReceived_value?: ((parameter: OnFaviconReceivedEvent) => void)
    onPageVisible_value?: ((parameter: OnPageVisibleEvent) => void)
    onDataResubmitted_value?: ((parameter: OnDataResubmittedEvent) => void)
    pinchSmooth_value?: boolean
    allowWindowOpenMethod_value?: boolean
    onAudioStateChanged_value?: ((parameter: OnAudioStateChangedEvent) => void)
    onFirstContentfulPaint_value?: ((parameter: OnFirstContentfulPaintEvent) => void)
    onFirstMeaningfulPaint_value?: OnFirstMeaningfulPaintCallback
    onLargestContentfulPaint_value?: OnLargestContentfulPaintCallback
    onLoadIntercept_value?: ((parameter: OnLoadInterceptEvent) => boolean)
    onControllerAttached_value?: (() => void)
    onOverScroll_value?: ((parameter: OnOverScrollEvent) => void)
    onSafeBrowsingCheckResult_value?: OnSafeBrowsingCheckResultCallback
    onNavigationEntryCommitted_value?: OnNavigationEntryCommittedCallback
    onIntelligentTrackingPreventionResult_value?: OnIntelligentTrackingPreventionCallback
    javaScriptOnDocumentStart_value?: Array<ScriptItem>
    javaScriptOnDocumentEnd_value?: Array<ScriptItem>
    layoutMode_value?: WebLayoutMode
    nestedScroll_value?: NestedScrollOptions | NestedScrollOptionsExt
    enableNativeEmbedMode_value?: boolean
    onNativeEmbedLifecycleChange_value?: ((event: NativeEmbedDataInfo) => void)
    onNativeEmbedVisibilityChange_value?: OnNativeEmbedVisibilityChangeCallback
    onNativeEmbedGestureEvent_value?: ((event: NativeEmbedTouchInfo) => void)
    copyOptions_value?: CopyOptions
    onOverrideUrlLoading_value?: OnOverrideUrlLoadingCallback
    textAutosizing_value?: boolean
    enableNativeMediaPlayer_value?: NativeMediaPlayerConfig
    enableSmoothDragResize_value?: boolean
    onRenderProcessNotResponding_value?: OnRenderProcessNotRespondingCallback
    onRenderProcessResponding_value?: OnRenderProcessRespondingCallback
    selectionMenuOptions_value?: Array<ExpandedMenuItemOptions>
    onViewportFitChanged_value?: OnViewportFitChangedCallback
    onInterceptKeyboardAttach_value?: WebKeyboardCallback
    onAdsBlocked_value?: OnAdsBlockedCallback
    keyboardAvoidMode_value?: WebKeyboardAvoidMode
    editMenuOptions_value?: EditMenuOptions
    enableHapticFeedback_value?: boolean
    public javaScriptAccess(value: boolean): this {
        return this
    }
    public fileAccess(value: boolean): this {
        return this
    }
    public onlineImageAccess(value: boolean): this {
        return this
    }
    public domStorageAccess(value: boolean): this {
        return this
    }
    public imageAccess(value: boolean): this {
        return this
    }
    public mixedMode(value: MixedMode): this {
        return this
    }
    public zoomAccess(value: boolean): this {
        return this
    }
    public geolocationAccess(value: boolean): this {
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy): this {
        return this
    }
    public password(value: boolean): this {
        return this
    }
    public cacheMode(value: CacheMode): this {
        return this
    }
    public darkMode(value: WebDarkMode): this {
        return this
    }
    public forceDarkAccess(value: boolean): this {
        return this
    }
    public mediaOptions(value: WebMediaOptions): this {
        return this
    }
    public tableData(value: boolean): this {
        return this
    }
    public wideViewModeAccess(value: boolean): this {
        return this
    }
    public overviewModeAccess(value: boolean): this {
        return this
    }
    public overScrollMode(value: OverScrollMode): this {
        return this
    }
    public textZoomAtio(value: number): this {
        return this
    }
    public textZoomRatio(value: number): this {
        return this
    }
    public databaseAccess(value: boolean): this {
        return this
    }
    public initialScale(value: number): this {
        return this
    }
    public userAgent(value: string): this {
        return this
    }
    public metaViewport(value: boolean): this {
        return this
    }
    public onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this {
        return this
    }
    public onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this {
        return this
    }
    public onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this {
        return this
    }
    public onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this {
        return this
    }
    public onGeolocationHide(value: (() => void)): this {
        return this
    }
    public onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this {
        return this
    }
    public onRequestSelected(value: (() => void)): this {
        return this
    }
    public onAlert(value: ((parameter: OnAlertEvent) => boolean)): this {
        return this
    }
    public onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this {
        return this
    }
    public onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this {
        return this
    }
    public onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this {
        return this
    }
    public onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this {
        return this
    }
    public onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this {
        return this
    }
    public onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this {
        return this
    }
    public onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this {
        return this
    }
    public onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this {
        return this
    }
    public onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): this {
        return this
    }
    public onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void)): this {
        return this
    }
    public onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: Literal_Object_detail) => boolean)): this {
        return this
    }
    public onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this {
        return this
    }
    public onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): this {
        return this
    }
    public onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this {
        return this
    }
    public onFullScreenExit(value: (() => void)): this {
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback): this {
        return this
    }
    public onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this {
        return this
    }
    public onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this {
        return this
    }
    public onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this {
        return this
    }
    public onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this {
        return this
    }
    public onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this {
        return this
    }
    public onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this {
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback): this {
        return this
    }
    public mediaPlayGestureAccess(value: boolean): this {
        return this
    }
    public onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this {
        return this
    }
    public onScroll(value: ((parameter: OnScrollEvent) => void)): this {
        return this
    }
    public onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this {
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback): this {
        return this
    }
    public onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this {
        return this
    }
    public onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this {
        return this
    }
    public onWindowExit(value: (() => void)): this {
        return this
    }
    public multiWindowAccess(value: boolean): this {
        return this
    }
    public onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this {
        return this
    }
    public webStandardFont(value: string): this {
        return this
    }
    public webSerifFont(value: string): this {
        return this
    }
    public webSansSerifFont(value: string): this {
        return this
    }
    public webFixedFont(value: string): this {
        return this
    }
    public webFantasyFont(value: string): this {
        return this
    }
    public webCursiveFont(value: string): this {
        return this
    }
    public defaultFixedFontSize(value: number): this {
        return this
    }
    public defaultFontSize(value: number): this {
        return this
    }
    public minFontSize(value: number): this {
        return this
    }
    public minLogicalFontSize(value: number): this {
        return this
    }
    public defaultTextEncodingFormat(value: string): this {
        return this
    }
    public forceDisplayScrollBar(value: boolean): this {
        return this
    }
    public blockNetwork(value: boolean): this {
        return this
    }
    public horizontalScrollBarAccess(value: boolean): this {
        return this
    }
    public verticalScrollBarAccess(value: boolean): this {
        return this
    }
    public onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this {
        return this
    }
    public onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this {
        return this
    }
    public onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this {
        return this
    }
    public onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this {
        return this
    }
    public pinchSmooth(value: boolean): this {
        return this
    }
    public allowWindowOpenMethod(value: boolean): this {
        return this
    }
    public onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this {
        return this
    }
    public onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this {
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this {
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this {
        return this
    }
    public onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this {
        return this
    }
    public onControllerAttached(value: (() => void)): this {
        return this
    }
    public onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this {
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this {
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this {
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this {
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem>): this {
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem>): this {
        return this
    }
    public layoutMode(value: WebLayoutMode): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this {
        return this
    }
    public enableNativeEmbedMode(value: boolean): this {
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this {
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this {
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this {
        return this
    }
    public copyOptions(value: CopyOptions): this {
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this {
        return this
    }
    public textAutosizing(value: boolean): this {
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this {
        return this
    }
    public enableSmoothDragResize(value: boolean): this {
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this {
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this {
        return this
    }
    public selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this {
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback): this {
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback): this {
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback): this {
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions): this {
        return this
    }
    public enableHapticFeedback(value: boolean): this {
        return this
    }
    public registerNativeEmbedRule(tag: string, type: string): this {
        return this
    }
    public bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
@memo_stable
export class ArkWebComponent extends ArkCommonMethodComponent implements UIWebAttribute {
    getPeer(): ArkWebPeer {
        return (this.peer as ArkWebPeer)
    }
    @memo
    public setWebOptions(value: WebOptions): this {
        if (this.checkPriority("setWebOptions")) {
            const value_casted = value as (WebOptions)
            this.getPeer()?.setWebOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public javaScriptAccess(value: boolean): this {
        if (this.checkPriority("javaScriptAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.javaScriptAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fileAccess(value: boolean): this {
        if (this.checkPriority("fileAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fileAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onlineImageAccess(value: boolean): this {
        if (this.checkPriority("onlineImageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.onlineImageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public domStorageAccess(value: boolean): this {
        if (this.checkPriority("domStorageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.domStorageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public imageAccess(value: boolean): this {
        if (this.checkPriority("imageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.imageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public mixedMode(value: MixedMode): this {
        if (this.checkPriority("mixedMode")) {
            const value_casted = value as (MixedMode)
            this.getPeer()?.mixedModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public zoomAccess(value: boolean): this {
        if (this.checkPriority("zoomAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.zoomAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public geolocationAccess(value: boolean): this {
        if (this.checkPriority("geolocationAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.geolocationAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public javaScriptProxy(value: JavaScriptProxy): this {
        if (this.checkPriority("javaScriptProxy")) {
            const value_casted = value as (JavaScriptProxy)
            this.getPeer()?.javaScriptProxyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public password(value: boolean): this {
        if (this.checkPriority("password")) {
            const value_casted = value as (boolean)
            this.getPeer()?.passwordAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public cacheMode(value: CacheMode): this {
        if (this.checkPriority("cacheMode")) {
            const value_casted = value as (CacheMode)
            this.getPeer()?.cacheModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public darkMode(value: WebDarkMode): this {
        if (this.checkPriority("darkMode")) {
            const value_casted = value as (WebDarkMode)
            this.getPeer()?.darkModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public forceDarkAccess(value: boolean): this {
        if (this.checkPriority("forceDarkAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceDarkAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public mediaOptions(value: WebMediaOptions): this {
        if (this.checkPriority("mediaOptions")) {
            const value_casted = value as (WebMediaOptions)
            this.getPeer()?.mediaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public tableData(value: boolean): this {
        if (this.checkPriority("tableData")) {
            const value_casted = value as (boolean)
            this.getPeer()?.tableDataAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public wideViewModeAccess(value: boolean): this {
        if (this.checkPriority("wideViewModeAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.wideViewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public overviewModeAccess(value: boolean): this {
        if (this.checkPriority("overviewModeAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.overviewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public overScrollMode(value: OverScrollMode): this {
        if (this.checkPriority("overScrollMode")) {
            const value_casted = value as (OverScrollMode)
            this.getPeer()?.overScrollModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textZoomAtio(value: number): this {
        if (this.checkPriority("textZoomAtio")) {
            const value_casted = value as (number)
            this.getPeer()?.textZoomAtioAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textZoomRatio(value: number): this {
        if (this.checkPriority("textZoomRatio")) {
            const value_casted = value as (number)
            this.getPeer()?.textZoomRatioAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public databaseAccess(value: boolean): this {
        if (this.checkPriority("databaseAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.databaseAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public initialScale(value: number): this {
        if (this.checkPriority("initialScale")) {
            const value_casted = value as (number)
            this.getPeer()?.initialScaleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public userAgent(value: string): this {
        if (this.checkPriority("userAgent")) {
            const value_casted = value as (string)
            this.getPeer()?.userAgentAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public metaViewport(value: boolean): this {
        if (this.checkPriority("metaViewport")) {
            const value_casted = value as (boolean)
            this.getPeer()?.metaViewportAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this {
        if (this.checkPriority("onPageEnd")) {
            const value_casted = value as (((parameter: OnPageEndEvent) => void))
            this.getPeer()?.onPageEndAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this {
        if (this.checkPriority("onPageBegin")) {
            const value_casted = value as (((parameter: OnPageBeginEvent) => void))
            this.getPeer()?.onPageBeginAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this {
        if (this.checkPriority("onProgressChange")) {
            const value_casted = value as (((parameter: OnProgressChangeEvent) => void))
            this.getPeer()?.onProgressChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this {
        if (this.checkPriority("onTitleReceive")) {
            const value_casted = value as (((parameter: OnTitleReceiveEvent) => void))
            this.getPeer()?.onTitleReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onGeolocationHide(value: (() => void)): this {
        if (this.checkPriority("onGeolocationHide")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onGeolocationHideAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this {
        if (this.checkPriority("onGeolocationShow")) {
            const value_casted = value as (((parameter: OnGeolocationShowEvent) => void))
            this.getPeer()?.onGeolocationShowAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRequestSelected(value: (() => void)): this {
        if (this.checkPriority("onRequestSelected")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onRequestSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onAlert(value: ((parameter: OnAlertEvent) => boolean)): this {
        if (this.checkPriority("onAlert")) {
            const value_casted = value as (((parameter: OnAlertEvent) => boolean))
            this.getPeer()?.onAlertAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this {
        if (this.checkPriority("onBeforeUnload")) {
            const value_casted = value as (((parameter: OnBeforeUnloadEvent) => boolean))
            this.getPeer()?.onBeforeUnloadAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this {
        if (this.checkPriority("onConfirm")) {
            const value_casted = value as (((parameter: OnConfirmEvent) => boolean))
            this.getPeer()?.onConfirmAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this {
        if (this.checkPriority("onPrompt")) {
            const value_casted = value as (((parameter: OnPromptEvent) => boolean))
            this.getPeer()?.onPromptAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this {
        if (this.checkPriority("onConsole")) {
            const value_casted = value as (((parameter: OnConsoleEvent) => boolean))
            this.getPeer()?.onConsoleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this {
        if (this.checkPriority("onErrorReceive")) {
            const value_casted = value as (((parameter: OnErrorReceiveEvent) => void))
            this.getPeer()?.onErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this {
        if (this.checkPriority("onHttpErrorReceive")) {
            const value_casted = value as (((parameter: OnHttpErrorReceiveEvent) => void))
            this.getPeer()?.onHttpErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this {
        if (this.checkPriority("onDownloadStart")) {
            const value_casted = value as (((parameter: OnDownloadStartEvent) => void))
            this.getPeer()?.onDownloadStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this {
        if (this.checkPriority("onRefreshAccessedHistory")) {
            const value_casted = value as (((parameter: OnRefreshAccessedHistoryEvent) => void))
            this.getPeer()?.onRefreshAccessedHistoryAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): this {
        if (this.checkPriority("onUrlLoadIntercept")) {
            const value_casted = value as (((event?: Literal_Union_String_WebResourceRequest_data) => boolean))
            this.getPeer()?.onUrlLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void)): this {
        if (this.checkPriority("onSslErrorReceive")) {
            const value_casted = value as (((event?: Literal_Function_handler_Object_error) => void))
            this.getPeer()?.onSslErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: Literal_Object_detail) => boolean)): this {
        if (this.checkPriority("onRenderExited")) {
            const value_type = runtimeType(value)
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((parameter: OnRenderExitedEvent) => void))
                this.getPeer()?.onRenderExited0Attribute(value_casted)
                return this
            }
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((event?: Literal_Object_detail) => boolean))
                this.getPeer()?.onRenderExited1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    @memo
    public onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this {
        if (this.checkPriority("onShowFileSelector")) {
            const value_casted = value as (((parameter: OnShowFileSelectorEvent) => boolean))
            this.getPeer()?.onShowFileSelectorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): this {
        if (this.checkPriority("onFileSelectorShow")) {
            const value_casted = value as (((event?: Literal_Function_callback__Object_fileSelector) => void))
            this.getPeer()?.onFileSelectorShowAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this {
        if (this.checkPriority("onResourceLoad")) {
            const value_casted = value as (((parameter: OnResourceLoadEvent) => void))
            this.getPeer()?.onResourceLoadAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFullScreenExit(value: (() => void)): this {
        if (this.checkPriority("onFullScreenExit")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFullScreenExitAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFullScreenEnter(value: OnFullScreenEnterCallback): this {
        if (this.checkPriority("onFullScreenEnter")) {
            const value_casted = value as (OnFullScreenEnterCallback)
            this.getPeer()?.onFullScreenEnterAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this {
        if (this.checkPriority("onScaleChange")) {
            const value_casted = value as (((parameter: OnScaleChangeEvent) => void))
            this.getPeer()?.onScaleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this {
        if (this.checkPriority("onHttpAuthRequest")) {
            const value_casted = value as (((parameter: OnHttpAuthRequestEvent) => boolean))
            this.getPeer()?.onHttpAuthRequestAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this {
        if (this.checkPriority("onInterceptRequest")) {
            const value_casted = value as (((parameter: OnInterceptRequestEvent) => WebResourceResponse))
            this.getPeer()?.onInterceptRequestAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this {
        if (this.checkPriority("onPermissionRequest")) {
            const value_casted = value as (((parameter: OnPermissionRequestEvent) => void))
            this.getPeer()?.onPermissionRequestAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this {
        if (this.checkPriority("onScreenCaptureRequest")) {
            const value_casted = value as (((parameter: OnScreenCaptureRequestEvent) => void))
            this.getPeer()?.onScreenCaptureRequestAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this {
        if (this.checkPriority("onContextMenuShow")) {
            const value_casted = value as (((parameter: OnContextMenuShowEvent) => boolean))
            this.getPeer()?.onContextMenuShowAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onContextMenuHide(value: OnContextMenuHideCallback): this {
        if (this.checkPriority("onContextMenuHide")) {
            const value_casted = value as (OnContextMenuHideCallback)
            this.getPeer()?.onContextMenuHideAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public mediaPlayGestureAccess(value: boolean): this {
        if (this.checkPriority("mediaPlayGestureAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.mediaPlayGestureAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this {
        if (this.checkPriority("onSearchResultReceive")) {
            const value_casted = value as (((parameter: OnSearchResultReceiveEvent) => void))
            this.getPeer()?.onSearchResultReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onScroll(value: ((parameter: OnScrollEvent) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((parameter: OnScrollEvent) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this {
        if (this.checkPriority("onSslErrorEventReceive")) {
            const value_casted = value as (((parameter: OnSslErrorEventReceiveEvent) => void))
            this.getPeer()?.onSslErrorEventReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSslErrorEvent(value: OnSslErrorEventCallback): this {
        if (this.checkPriority("onSslErrorEvent")) {
            const value_casted = value as (OnSslErrorEventCallback)
            this.getPeer()?.onSslErrorEventAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this {
        if (this.checkPriority("onClientAuthenticationRequest")) {
            const value_casted = value as (((parameter: OnClientAuthenticationEvent) => void))
            this.getPeer()?.onClientAuthenticationRequestAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this {
        if (this.checkPriority("onWindowNew")) {
            const value_casted = value as (((parameter: OnWindowNewEvent) => void))
            this.getPeer()?.onWindowNewAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onWindowExit(value: (() => void)): this {
        if (this.checkPriority("onWindowExit")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWindowExitAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public multiWindowAccess(value: boolean): this {
        if (this.checkPriority("multiWindowAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.multiWindowAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this {
        if (this.checkPriority("onInterceptKeyEvent")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean))
            this.getPeer()?.onInterceptKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webStandardFont(value: string): this {
        if (this.checkPriority("webStandardFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webStandardFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webSerifFont(value: string): this {
        if (this.checkPriority("webSerifFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webSansSerifFont(value: string): this {
        if (this.checkPriority("webSansSerifFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webSansSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webFixedFont(value: string): this {
        if (this.checkPriority("webFixedFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webFixedFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webFantasyFont(value: string): this {
        if (this.checkPriority("webFantasyFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webFantasyFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public webCursiveFont(value: string): this {
        if (this.checkPriority("webCursiveFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webCursiveFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public defaultFixedFontSize(value: number): this {
        if (this.checkPriority("defaultFixedFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.defaultFixedFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public defaultFontSize(value: number): this {
        if (this.checkPriority("defaultFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.defaultFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public minFontSize(value: number): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public minLogicalFontSize(value: number): this {
        if (this.checkPriority("minLogicalFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.minLogicalFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public defaultTextEncodingFormat(value: string): this {
        if (this.checkPriority("defaultTextEncodingFormat")) {
            const value_casted = value as (string)
            this.getPeer()?.defaultTextEncodingFormatAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public forceDisplayScrollBar(value: boolean): this {
        if (this.checkPriority("forceDisplayScrollBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceDisplayScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public blockNetwork(value: boolean): this {
        if (this.checkPriority("blockNetwork")) {
            const value_casted = value as (boolean)
            this.getPeer()?.blockNetworkAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public horizontalScrollBarAccess(value: boolean): this {
        if (this.checkPriority("horizontalScrollBarAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.horizontalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public verticalScrollBarAccess(value: boolean): this {
        if (this.checkPriority("verticalScrollBarAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.verticalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this {
        if (this.checkPriority("onTouchIconUrlReceived")) {
            const value_casted = value as (((parameter: OnTouchIconUrlReceivedEvent) => void))
            this.getPeer()?.onTouchIconUrlReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this {
        if (this.checkPriority("onFaviconReceived")) {
            const value_casted = value as (((parameter: OnFaviconReceivedEvent) => void))
            this.getPeer()?.onFaviconReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this {
        if (this.checkPriority("onPageVisible")) {
            const value_casted = value as (((parameter: OnPageVisibleEvent) => void))
            this.getPeer()?.onPageVisibleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this {
        if (this.checkPriority("onDataResubmitted")) {
            const value_casted = value as (((parameter: OnDataResubmittedEvent) => void))
            this.getPeer()?.onDataResubmittedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public pinchSmooth(value: boolean): this {
        if (this.checkPriority("pinchSmooth")) {
            const value_casted = value as (boolean)
            this.getPeer()?.pinchSmoothAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public allowWindowOpenMethod(value: boolean): this {
        if (this.checkPriority("allowWindowOpenMethod")) {
            const value_casted = value as (boolean)
            this.getPeer()?.allowWindowOpenMethodAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this {
        if (this.checkPriority("onAudioStateChanged")) {
            const value_casted = value as (((parameter: OnAudioStateChangedEvent) => void))
            this.getPeer()?.onAudioStateChangedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this {
        if (this.checkPriority("onFirstContentfulPaint")) {
            const value_casted = value as (((parameter: OnFirstContentfulPaintEvent) => void))
            this.getPeer()?.onFirstContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this {
        if (this.checkPriority("onFirstMeaningfulPaint")) {
            const value_casted = value as (OnFirstMeaningfulPaintCallback)
            this.getPeer()?.onFirstMeaningfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this {
        if (this.checkPriority("onLargestContentfulPaint")) {
            const value_casted = value as (OnLargestContentfulPaintCallback)
            this.getPeer()?.onLargestContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this {
        if (this.checkPriority("onLoadIntercept")) {
            const value_casted = value as (((parameter: OnLoadInterceptEvent) => boolean))
            this.getPeer()?.onLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onControllerAttached(value: (() => void)): this {
        if (this.checkPriority("onControllerAttached")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onControllerAttachedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this {
        if (this.checkPriority("onOverScroll")) {
            const value_casted = value as (((parameter: OnOverScrollEvent) => void))
            this.getPeer()?.onOverScrollAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this {
        if (this.checkPriority("onSafeBrowsingCheckResult")) {
            const value_casted = value as (OnSafeBrowsingCheckResultCallback)
            this.getPeer()?.onSafeBrowsingCheckResultAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this {
        if (this.checkPriority("onNavigationEntryCommitted")) {
            const value_casted = value as (OnNavigationEntryCommittedCallback)
            this.getPeer()?.onNavigationEntryCommittedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this {
        if (this.checkPriority("onIntelligentTrackingPreventionResult")) {
            const value_casted = value as (OnIntelligentTrackingPreventionCallback)
            this.getPeer()?.onIntelligentTrackingPreventionResultAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public javaScriptOnDocumentStart(value: Array<ScriptItem>): this {
        if (this.checkPriority("javaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem>)
            this.getPeer()?.javaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public javaScriptOnDocumentEnd(value: Array<ScriptItem>): this {
        if (this.checkPriority("javaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem>)
            this.getPeer()?.javaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public layoutMode(value: WebLayoutMode): this {
        if (this.checkPriority("layoutMode")) {
            const value_casted = value as (WebLayoutMode)
            this.getPeer()?.layoutModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | NestedScrollOptionsExt)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableNativeEmbedMode(value: boolean): this {
        if (this.checkPriority("enableNativeEmbedMode")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableNativeEmbedModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this {
        if (this.checkPriority("onNativeEmbedLifecycleChange")) {
            const value_casted = value as (((event: NativeEmbedDataInfo) => void))
            this.getPeer()?.onNativeEmbedLifecycleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this {
        if (this.checkPriority("onNativeEmbedVisibilityChange")) {
            const value_casted = value as (OnNativeEmbedVisibilityChangeCallback)
            this.getPeer()?.onNativeEmbedVisibilityChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this {
        if (this.checkPriority("onNativeEmbedGestureEvent")) {
            const value_casted = value as (((event: NativeEmbedTouchInfo) => void))
            this.getPeer()?.onNativeEmbedGestureEventAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public copyOptions(value: CopyOptions): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this {
        if (this.checkPriority("onOverrideUrlLoading")) {
            const value_casted = value as (OnOverrideUrlLoadingCallback)
            this.getPeer()?.onOverrideUrlLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textAutosizing(value: boolean): this {
        if (this.checkPriority("textAutosizing")) {
            const value_casted = value as (boolean)
            this.getPeer()?.textAutosizingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this {
        if (this.checkPriority("enableNativeMediaPlayer")) {
            const value_casted = value as (NativeMediaPlayerConfig)
            this.getPeer()?.enableNativeMediaPlayerAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableSmoothDragResize(value: boolean): this {
        if (this.checkPriority("enableSmoothDragResize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableSmoothDragResizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this {
        if (this.checkPriority("onRenderProcessNotResponding")) {
            const value_casted = value as (OnRenderProcessNotRespondingCallback)
            this.getPeer()?.onRenderProcessNotRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this {
        if (this.checkPriority("onRenderProcessResponding")) {
            const value_casted = value as (OnRenderProcessRespondingCallback)
            this.getPeer()?.onRenderProcessRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this {
        if (this.checkPriority("selectionMenuOptions")) {
            const value_casted = value as (Array<ExpandedMenuItemOptions>)
            this.getPeer()?.selectionMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onViewportFitChanged(value: OnViewportFitChangedCallback): this {
        if (this.checkPriority("onViewportFitChanged")) {
            const value_casted = value as (OnViewportFitChangedCallback)
            this.getPeer()?.onViewportFitChangedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onInterceptKeyboardAttach(value: WebKeyboardCallback): this {
        if (this.checkPriority("onInterceptKeyboardAttach")) {
            const value_casted = value as (WebKeyboardCallback)
            this.getPeer()?.onInterceptKeyboardAttachAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onAdsBlocked(value: OnAdsBlockedCallback): this {
        if (this.checkPriority("onAdsBlocked")) {
            const value_casted = value as (OnAdsBlockedCallback)
            this.getPeer()?.onAdsBlockedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public keyboardAvoidMode(value: WebKeyboardAvoidMode): this {
        if (this.checkPriority("keyboardAvoidMode")) {
            const value_casted = value as (WebKeyboardAvoidMode)
            this.getPeer()?.keyboardAvoidModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public registerNativeEmbedRule(tag: string, type: string): this {
        if (this.checkPriority("registerNativeEmbedRule")) {
            const tag_casted = tag as (string)
            const type_casted = type as (string)
            this.getPeer()?.registerNativeEmbedRuleAttribute(tag_casted, type_casted)
            return this
        }
        return this
    }
    @memo
    public bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const elementType_casted = elementType as (WebElementType)
            const content_casted = content as (CustomBuilder)
            const responseType_casted = responseType as (WebResponseType)
            const options_casted = options as (SelectionMenuOptionsExt | undefined)
            this.getPeer()?.bindSelectionMenuAttribute(elementType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Web")
export function Web(
    value: WebOptions,
    @memo
    content_?: () => void,
): WebAttribute {
    throw new Error("Not implemented")
}

@memo
export function Web(
    @memo
    style: ((attributes: UIWebAttribute) => void) | undefined,
    value: WebOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWebComponent>((): ArkWebComponent => {
        return new ArkWebComponent()
    })
    NodeAttach<ArkWebPeer>((): ArkWebPeer => ArkWebPeer.create(receiver), (_: ArkWebPeer): void => {
        receiver.setWebOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { webview, webview_WebviewController_serializer } from "./../generated/ohos.web.webview"
import { Resource_serializer, Resource } from "./../generated/resource"
import { NestedScrollOptions_serializer, ArkCommonMethodPeer, CommonMethod, KeyEvent, NestedScrollOptions, TouchEvent, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, TouchEvent_serializer } from "./common"
import { EditMenuOptions_serializer, EditMenuOptions, MenuType } from "./textCommon"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CopyOptions, NestedScrollMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Position, Position_serializer } from "./units"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ClientAuthenticationHandlerInternal {
    public static fromPtr(ptr: KPointer): ClientAuthenticationHandler {
        return new ClientAuthenticationHandler(ptr)
    }
}
export class ClientAuthenticationHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ClientAuthenticationHandler.getFinalizer())
    }
    constructor() {
        this(ClientAuthenticationHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ClientAuthenticationHandler_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ClientAuthenticationHandler_getFinalizer()
    }
    public confirm(priKeyFile: string, certChainFile: string): void {
        const priKeyFile_casted = priKeyFile as (string)
        const certChainFile_casted = certChainFile as (string)
        this.confirm0_serialize(priKeyFile_casted, certChainFile_casted)
        return
    }
    public confirm(authUri: string): void {
        const authUri_casted = authUri as (string)
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
export class ConsoleMessageInternal {
    public static fromPtr(ptr: KPointer): ConsoleMessage {
        return new ConsoleMessage(ptr)
    }
}
export class ConsoleMessage implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ConsoleMessage.getFinalizer())
    }
    constructor() {
        this(ConsoleMessage.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_construct()
        return retval
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
export class ControllerHandlerInternal {
    public static fromPtr(ptr: KPointer): ControllerHandler {
        return new ControllerHandler(ptr)
    }
}
export class ControllerHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ControllerHandler.getFinalizer())
    }
    constructor() {
        this(ControllerHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ControllerHandler_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ControllerHandler_getFinalizer()
    }
    public setWebController(controller: webview.WebviewController): void {
        const controller_casted = controller as (webview.WebviewController)
        this.setWebController_serialize(controller_casted)
        return
    }
    private setWebController_serialize(controller: webview.WebviewController): void {
        ArkUIGeneratedNativeModule._ControllerHandler_setWebController(this.peer!.ptr, toPeerPtr(controller))
    }
}
export class DataResubmissionHandlerInternal {
    public static fromPtr(ptr: KPointer): DataResubmissionHandler {
        return new DataResubmissionHandler(ptr)
    }
}
export class DataResubmissionHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DataResubmissionHandler.getFinalizer())
    }
    constructor() {
        this(DataResubmissionHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DataResubmissionHandler_construct()
        return retval
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
export class EventResultInternal {
    public static fromPtr(ptr: KPointer): EventResult {
        return new EventResult(ptr)
    }
}
export class EventResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, EventResult.getFinalizer())
    }
    constructor() {
        this(EventResult.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._EventResult_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._EventResult_getFinalizer()
    }
    public setGestureEventResult(result: boolean): void {
        const result_casted = result as (boolean)
        this.setGestureEventResult0_serialize(result_casted)
        return
    }
    public setGestureEventResult(result: boolean, stopPropagation: boolean): void {
        const result_casted = result as (boolean)
        const stopPropagation_casted = stopPropagation as (boolean)
        this.setGestureEventResult1_serialize(result_casted, stopPropagation_casted)
        return
    }
    private setGestureEventResult0_serialize(result: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult0(this.peer!.ptr, result ? 1 : 0)
    }
    private setGestureEventResult1_serialize(result: boolean, stopPropagation: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult1(this.peer!.ptr, result ? 1 : 0, stopPropagation ? 1 : 0)
    }
}
export class FileSelectorParamInternal {
    public static fromPtr(ptr: KPointer): FileSelectorParam {
        return new FileSelectorParam(ptr)
    }
}
export class FileSelectorParam implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FileSelectorParam.getFinalizer())
    }
    constructor() {
        this(FileSelectorParam.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_construct()
        return retval
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
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptType(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
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
        const retval  = ArkUIGeneratedNativeModule._FileSelectorParam_getMimeTypes(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
}
export class FileSelectorResultInternal {
    public static fromPtr(ptr: KPointer): FileSelectorResult {
        return new FileSelectorResult(ptr)
    }
}
export class FileSelectorResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FileSelectorResult.getFinalizer())
    }
    constructor() {
        this(FileSelectorResult.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FileSelectorResult_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fileList.length).toInt())
        for (let fileList_counter_i = 0; fileList_counter_i < fileList.length; fileList_counter_i++) {
            const fileList_element : string = fileList[fileList_counter_i]
            thisSerializer.writeString(fileList_element)
        }
        ArkUIGeneratedNativeModule._FileSelectorResult_handleFileList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class FullScreenExitHandlerInternal {
    public static fromPtr(ptr: KPointer): FullScreenExitHandler {
        return new FullScreenExitHandler(ptr)
    }
}
export class FullScreenExitHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FullScreenExitHandler.getFinalizer())
    }
    constructor() {
        this(FullScreenExitHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FullScreenExitHandler_construct()
        return retval
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
export class HttpAuthHandlerInternal {
    public static fromPtr(ptr: KPointer): HttpAuthHandler {
        return new HttpAuthHandler(ptr)
    }
}
export class HttpAuthHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, HttpAuthHandler.getFinalizer())
    }
    constructor() {
        this(HttpAuthHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._HttpAuthHandler_construct()
        return retval
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
export class JsGeolocationInternal {
    public static fromPtr(ptr: KPointer): JsGeolocation {
        return new JsGeolocation(ptr)
    }
}
export class JsGeolocation implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, JsGeolocation.getFinalizer())
    }
    constructor() {
        this(JsGeolocation.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._JsGeolocation_construct()
        return retval
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
export class JsResultInternal {
    public static fromPtr(ptr: KPointer): JsResult {
        return new JsResult(ptr)
    }
}
export class JsResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, JsResult.getFinalizer())
    }
    constructor() {
        this(JsResult.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._JsResult_construct()
        return retval
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
export class PermissionRequestInternal {
    public static fromPtr(ptr: KPointer): PermissionRequest {
        return new PermissionRequest(ptr)
    }
}
export class PermissionRequest implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PermissionRequest.getFinalizer())
    }
    constructor() {
        this(PermissionRequest.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PermissionRequest_construct()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private grant_serialize(resources: Array<string>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((resources.length).toInt())
        for (let resources_counter_i = 0; resources_counter_i < resources.length; resources_counter_i++) {
            const resources_element : string = resources[resources_counter_i]
            thisSerializer.writeString(resources_element)
        }
        ArkUIGeneratedNativeModule._PermissionRequest_grant(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScreenCaptureHandlerInternal {
    public static fromPtr(ptr: KPointer): ScreenCaptureHandler {
        return new ScreenCaptureHandler(ptr)
    }
}
export class ScreenCaptureHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ScreenCaptureHandler.getFinalizer())
    }
    constructor() {
        this(ScreenCaptureHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ScreenCaptureHandler_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ScreenCaptureConfig_serializer.write(thisSerializer, config)
        ArkUIGeneratedNativeModule._ScreenCaptureHandler_grant(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deny_serialize(): void {
        ArkUIGeneratedNativeModule._ScreenCaptureHandler_deny(this.peer!.ptr)
    }
}
export class SslErrorHandlerInternal {
    public static fromPtr(ptr: KPointer): SslErrorHandler {
        return new SslErrorHandler(ptr)
    }
}
export class SslErrorHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SslErrorHandler.getFinalizer())
    }
    constructor() {
        this(SslErrorHandler.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SslErrorHandler_construct()
        return retval
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
export class WebContextMenuParamInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuParam {
        return new WebContextMenuParam(ptr)
    }
}
export class WebContextMenuParam implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebContextMenuParam.getFinalizer())
    }
    constructor() {
        this(WebContextMenuParam.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebContextMenuParam_getFinalizer()
    }
    public x(): int32 {
        return this.x_serialize()
    }
    public y(): int32 {
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
    public getEditStateFlags(): int32 {
        return this.getEditStateFlags_serialize()
    }
    public getPreviewWidth(): int32 {
        return this.getPreviewWidth_serialize()
    }
    public getPreviewHeight(): int32 {
        return this.getPreviewHeight_serialize()
    }
    private x_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_x(this.peer!.ptr)
        return retval
    }
    private y_serialize(): int32 {
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
    private getEditStateFlags_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getEditStateFlags(this.peer!.ptr)
        return retval
    }
    private getPreviewWidth_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewWidth(this.peer!.ptr)
        return retval
    }
    private getPreviewHeight_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewHeight(this.peer!.ptr)
        return retval
    }
}
export class WebContextMenuResultInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuResult {
        return new WebContextMenuResult(ptr)
    }
}
export class WebContextMenuResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebContextMenuResult.getFinalizer())
    }
    constructor() {
        this(WebContextMenuResult.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuResult_construct()
        return retval
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
export class WebCookieInternal {
    public static fromPtr(ptr: KPointer): WebCookie {
        return new WebCookie(ptr)
    }
}
export class WebCookie implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebCookie.getFinalizer())
    }
    constructor() {
        this(WebCookie.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebCookie_construct()
        return retval
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
export class WebKeyboardControllerInternal {
    public static fromPtr(ptr: KPointer): WebKeyboardController {
        return new WebKeyboardController(ptr)
    }
}
export class WebKeyboardController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebKeyboardController.getFinalizer())
    }
    constructor() {
        this(WebKeyboardController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebKeyboardController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebKeyboardController_getFinalizer()
    }
    public insertText(text: string): void {
        const text_casted = text as (string)
        this.insertText_serialize(text_casted)
        return
    }
    public deleteForward(length: int32): void {
        const length_casted = length as (int32)
        this.deleteForward_serialize(length_casted)
        return
    }
    public deleteBackward(length: int32): void {
        const length_casted = length as (int32)
        this.deleteBackward_serialize(length_casted)
        return
    }
    public sendFunctionKey(key: int32): void {
        const key_casted = key as (int32)
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
    private deleteForward_serialize(length: int32): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteForward(this.peer!.ptr, length)
    }
    private deleteBackward_serialize(length: int32): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteBackward(this.peer!.ptr, length)
    }
    private sendFunctionKey_serialize(key: int32): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_sendFunctionKey(this.peer!.ptr, key)
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_close(this.peer!.ptr)
    }
}
export class WebResourceErrorInternal {
    public static fromPtr(ptr: KPointer): WebResourceError {
        return new WebResourceError(ptr)
    }
}
export class WebResourceError implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceError.getFinalizer())
    }
    constructor() {
        this(WebResourceError.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceError_construct()
        return retval
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
export class WebResourceRequestInternal {
    public static fromPtr(ptr: KPointer): WebResourceRequest {
        return new WebResourceRequest(ptr)
    }
}
export class WebResourceRequest implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceRequest.getFinalizer())
    }
    constructor() {
        this(WebResourceRequest.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceRequest_construct()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = Header_serializer.read(retvalDeserializer)
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
        return new WebResourceResponse(ptr)
    }
}
export class WebResourceResponse implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceResponse.getFinalizer())
    }
    constructor() {
        this(WebResourceResponse.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_construct()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : string | number | NativeBuffer | Resource | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__selector : int32 = retvalDeserializer.readInt8()
            let buffer_ : string | number | NativeBuffer | Resource | undefined
            if (buffer__selector == (0).toChar()) {
                buffer_ = (retvalDeserializer.readString() as string)
            }
            else if (buffer__selector == (1).toChar()) {
                buffer_ = (retvalDeserializer.readNumber() as number)
            }
            else if (buffer__selector == (2).toChar()) {
                buffer_ = (retvalDeserializer.readBuffer() as NativeBuffer)
            }
            else if (buffer__selector == (3).toChar()) {
                buffer_ = Resource_serializer.read(retvalDeserializer)
            }
            else {
                throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
            }
            buffer = (buffer_ as string | number | NativeBuffer | Resource)
        }
        const returnResult : string | number | NativeBuffer | Resource | undefined = buffer
        return returnResult
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = Header_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<Header> = buffer
        return returnResult
    }
    private getResponseCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseCode(this.peer!.ptr)
        return retval
    }
    private setResponseData_serialize(data: string | number | Resource | NativeBuffer): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let data_type : int32 = RuntimeType.UNDEFINED
        data_type = runtimeType(data)
        if (RuntimeType.STRING == data_type) {
            thisSerializer.writeInt8((0).toChar())
            const data_0  = data as string
            thisSerializer.writeString(data_0)
        }
        else if (RuntimeType.NUMBER == data_type) {
            thisSerializer.writeInt8((1).toChar())
            const data_1  = data as number
            thisSerializer.writeNumber(data_1)
        }
        else if (TypeChecker.isResource(data, false, false, false, false, false)) {
            thisSerializer.writeInt8((2).toChar())
            const data_2  = data as Resource
            Resource_serializer.write(thisSerializer, data_2)
        }
        else if (TypeChecker.isNativeBuffer(data)) {
            thisSerializer.writeInt8((3).toChar())
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((header.length).toInt())
        for (let header_counter_i = 0; header_counter_i < header.length; header_counter_i++) {
            const header_element : Header = header[header_counter_i]
            Header_serializer.write(thisSerializer, header_element)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WebOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._WebInterface_setWebOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFileAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setFileAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnlineImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnlineImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDomStorageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDomStorageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMixedModeAttribute(value: MixedMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as MixedMode)
            thisSerializer.writeInt32(TypeChecker.MixedMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMixedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setZoomAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setZoomAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGeolocationAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setGeolocationAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptProxyAttribute(value: JavaScriptProxy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            JavaScriptProxy_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptProxy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCacheModeAttribute(value: CacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CacheMode)
            thisSerializer.writeInt32(TypeChecker.CacheMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCacheMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDarkModeAttribute(value: WebDarkMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as WebDarkMode)
            thisSerializer.writeInt32(TypeChecker.WebDarkMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDarkMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDarkAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDarkAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaOptionsAttribute(value: WebMediaOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            WebMediaOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverviewModeAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverviewModeAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverScrollModeAttribute(value: OverScrollMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as OverScrollMode)
            thisSerializer.writeInt32(TypeChecker.OverScrollMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverScrollMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlurOnKeyboardHideModeAttribute(value: BlurOnKeyboardHideMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BlurOnKeyboardHideMode)
            thisSerializer.writeInt32(TypeChecker.BlurOnKeyboardHideMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlurOnKeyboardHideMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextZoomRatioAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextZoomRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDatabaseAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDatabaseAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialScaleAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeFloat64(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setInitialScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMetaViewportAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMetaViewport(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageEndAttribute(value: ((value0: OnPageEndEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageBeginAttribute(value: ((value0: OnPageBeginEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnProgressChangeAttribute(value: ((value0: OnProgressChangeEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnProgressChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTitleReceiveAttribute(value: ((value0: OnTitleReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTitleReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationShowAttribute(value: ((value0: OnGeolocationShowEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestSelectedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRequestSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAlertAttribute(value: ((value0: OnAlertEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAlert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBeforeUnloadAttribute(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnBeforeUnload(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConfirmAttribute(value: ((value0: OnConfirmEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConfirm(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPromptAttribute(value: ((value0: OnPromptEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPrompt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConsoleAttribute(value: ((value0: OnConsoleEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConsole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorReceiveAttribute(value: ((value0: OnErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpErrorReceiveAttribute(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDownloadStartAttribute(value: ((value0: OnDownloadStartEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDownloadStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRefreshAccessedHistoryAttribute(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRefreshAccessedHistory(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderExitedAttribute(value: ((value0: OnRenderExitedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderExited(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnShowFileSelectorAttribute(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnShowFileSelector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnResourceLoadAttribute(value: ((value0: OnResourceLoadEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnResourceLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenEnterAttribute(value: OnFullScreenEnterCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScaleChangeAttribute(value: ((value0: OnScaleChangeEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScaleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpAuthRequestAttribute(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpAuthRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptRequestAttribute(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPermissionRequestAttribute(value: ((value0: OnPermissionRequestEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPermissionRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScreenCaptureRequestAttribute(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScreenCaptureRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuShowAttribute(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuHideAttribute(value: OnContextMenuHideCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaPlayGestureAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaPlayGestureAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSearchResultReceiveAttribute(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSearchResultReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollAttribute(value: ((value0: OnScrollEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventReceiveAttribute(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEventReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventAttribute(value: OnSslErrorEventCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClientAuthenticationRequestAttribute(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnClientAuthenticationRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowNewAttribute(value: ((value0: OnWindowNewEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowNew(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiWindowAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMultiWindowAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyEventAttribute(value: ((event: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebStandardFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebStandardFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSansSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSansSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFixedFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFixedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFantasyFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFantasyFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebCursiveFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebCursiveFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFixedFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFixedFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinLogicalFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinLogicalFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultTextEncodingFormatAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultTextEncodingFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDisplayScrollBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDisplayScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockNetworkAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlockNetwork(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHorizontalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setHorizontalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setVerticalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTouchIconUrlReceivedAttribute(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTouchIconUrlReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFaviconReceivedAttribute(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFaviconReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageVisibleAttribute(value: ((value0: OnPageVisibleEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageVisible(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDataResubmittedAttribute(value: ((value0: OnDataResubmittedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDataResubmitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPinchSmoothAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setPinchSmooth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowWindowOpenMethodAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setAllowWindowOpenMethod(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAudioStateChangedAttribute(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAudioStateChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstContentfulPaintAttribute(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLargestContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadInterceptAttribute(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnControllerAttachedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnControllerAttached(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverScrollAttribute(value: ((value0: OnOverScrollEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNavigationEntryCommitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ScriptItem = value_value[value_value_counter_i]
                ScriptItem_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ScriptItem = value_value[value_value_counter_i]
                ScriptItem_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutModeAttribute(value: WebLayoutMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as WebLayoutMode)
            thisSerializer.writeInt32(TypeChecker.WebLayoutMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setLayoutMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isNestedScrollOptions(value_value, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as NestedScrollOptions
                NestedScrollOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isNestedScrollOptionsExt(value_value, false, false, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as NestedScrollOptionsExt
                NestedScrollOptionsExt_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeEmbedModeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeEmbedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCopyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverrideUrlLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAutosizingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextAutosizing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            NativeMediaPlayerConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeMediaPlayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessNotResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnViewportFitChangedAttribute(value: OnViewportFitChangedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnViewportFitChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyboardAttachAttribute(value: WebKeyboardCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAdsBlockedAttribute(value: OnAdsBlockedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAdsBlocked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAvoidModeAttribute(value: WebKeyboardAvoidMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as WebKeyboardAvoidMode)
            thisSerializer.writeInt32(TypeChecker.WebKeyboardAvoidMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WebAttribute_setKeyboardAvoidMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            EditMenuOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptimizeParserBudgetAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOptimizeParserBudget(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableFollowSystemFontWeightAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableFollowSystemFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableWebAVSessionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableWebAVSession(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ScriptItem = value_value[value_value_counter_i]
                ScriptItem_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ScriptItem = value_value[value_value_counter_i]
                ScriptItem_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnHeadEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ScriptItem = value_value[value_value_counter_i]
                ScriptItem_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnHeadEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNativeEmbedOptionsAttribute(value: EmbedOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            EmbedOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNativeEmbedOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRegisterNativeEmbedRuleAttribute(tag: string | undefined, type: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let tag_type : int32 = RuntimeType.UNDEFINED
        tag_type = runtimeType(tag)
        thisSerializer.writeInt8((tag_type).toChar())
        if ((tag_type) != (RuntimeType.UNDEFINED)) {
            const tag_value  = tag!
            thisSerializer.writeString(tag_value)
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8((type_type).toChar())
        if ((type_type) != (RuntimeType.UNDEFINED)) {
            const type_value  = type!
            thisSerializer.writeString(type_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRegisterNativeEmbedRule(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let elementType_type : int32 = RuntimeType.UNDEFINED
        elementType_type = runtimeType(elementType)
        thisSerializer.writeInt8((elementType_type).toChar())
        if ((elementType_type) != (RuntimeType.UNDEFINED)) {
            const elementType_value  = (elementType as WebElementType)
            thisSerializer.writeInt32(TypeChecker.WebElementType_ToNumeric(elementType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8((content_type).toChar())
        if ((content_type) != (RuntimeType.UNDEFINED)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8((responseType_type).toChar())
        if ((responseType_type) != (RuntimeType.UNDEFINED)) {
            const responseType_value  = (responseType as WebResponseType)
            thisSerializer.writeInt32(TypeChecker.WebResponseType_ToNumeric(responseType_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SelectionMenuOptionsExt_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type WebviewController = webview.WebviewController;
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
    enterKeyType?: int32;
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
    resumeInterval?: int32;
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
    MIDI_SYSEX = "'TYPE_MIDI_SYSEX'",
    MidiSysex = "'TYPE_MIDI_SYSEX'",
    VIDEO_CAPTURE = "'TYPE_VIDEO_CAPTURE'",
    AUDIO_CAPTURE = "'TYPE_AUDIO_CAPTURE'",
    SENSOR = "'TYPE_SENSOR'"
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
    CAN_PASTE = 3,
    CAN_SELECT_ALL = 4
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
export interface WebOptions {
    src: string | Resource;
    controller: webview.WebviewController;
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
    width?: int32;
    height?: int32;
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
    navigationStartTime?: int64;
    firstMeaningfulPaintTime?: int64;
}
export interface LargestContentfulPaint {
    navigationStartTime?: int64;
    largestImagePaintTime?: int64;
    largestTextPaintTime?: int64;
    imageBPP?: double;
    largestImageLoadStartTime?: int64;
    largestImageLoadEndTime?: int64;
}
export interface RenderProcessNotRespondingData {
    jsStack: string;
    pid: int32;
    reason: RenderProcessNotRespondingReason;
}
export interface OnPageEndEvent {
    url: string;
}
export interface OnPageBeginEvent {
    url: string;
}
export interface OnProgressChangeEvent {
    newProgress: int32;
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
    oldScale: double;
    newScale: double;
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
    xOffset: double;
    yOffset: double;
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
    favicon: image.PixelMap;
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
    navigationStartTick: int64;
    firstContentfulPaintMs: int64;
}
export interface OnLoadInterceptEvent {
    data: WebResourceRequest;
}
export interface OnOverScrollEvent {
    xOffset: double;
    yOffset: double;
}
export interface JavaScriptProxy {
    object_: Object;
    name: string;
    methodList: Array<string>;
    controller: webview.WebviewController;
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
export interface WebAttribute extends CommonMethod {
    javaScriptAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method javaScriptAccess")
    }
    fileAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method fileAccess")
    }
    onlineImageAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method onlineImageAccess")
    }
    domStorageAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method domStorageAccess")
    }
    imageAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method imageAccess")
    }
    mixedMode(value: MixedMode | undefined): this {
        throw new Error("Unimplemented method mixedMode")
    }
    zoomAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method zoomAccess")
    }
    geolocationAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method geolocationAccess")
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        throw new Error("Unimplemented method javaScriptProxy")
    }
    cacheMode(value: CacheMode | undefined): this {
        throw new Error("Unimplemented method cacheMode")
    }
    darkMode(value: WebDarkMode | undefined): this {
        throw new Error("Unimplemented method darkMode")
    }
    forceDarkAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method forceDarkAccess")
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        throw new Error("Unimplemented method mediaOptions")
    }
    overviewModeAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method overviewModeAccess")
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        throw new Error("Unimplemented method overScrollMode")
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        throw new Error("Unimplemented method blurOnKeyboardHideMode")
    }
    textZoomRatio(value: int32 | undefined): this {
        throw new Error("Unimplemented method textZoomRatio")
    }
    databaseAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method databaseAccess")
    }
    initialScale(value: double | undefined): this {
        throw new Error("Unimplemented method initialScale")
    }
    metaViewport(value: boolean | undefined): this {
        throw new Error("Unimplemented method metaViewport")
    }
    onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onPageEnd")
    }
    onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onPageBegin")
    }
    onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onProgressChange")
    }
    onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onTitleReceive")
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onGeolocationHide")
    }
    onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onGeolocationShow")
    }
    onRequestSelected(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onRequestSelected")
    }
    onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onAlert")
    }
    onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onBeforeUnload")
    }
    onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onConfirm")
    }
    onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onPrompt")
    }
    onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onConsole")
    }
    onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onErrorReceive")
    }
    onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onHttpErrorReceive")
    }
    onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onDownloadStart")
    }
    onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onRefreshAccessedHistory")
    }
    onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onRenderExited")
    }
    onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onShowFileSelector")
    }
    onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onResourceLoad")
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFullScreenExit")
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        throw new Error("Unimplemented method onFullScreenEnter")
    }
    onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onScaleChange")
    }
    onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onHttpAuthRequest")
    }
    onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        throw new Error("Unimplemented method onInterceptRequest")
    }
    onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onPermissionRequest")
    }
    onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onScreenCaptureRequest")
    }
    onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onContextMenuShow")
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        throw new Error("Unimplemented method onContextMenuHide")
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method mediaPlayGestureAccess")
    }
    onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onSearchResultReceive")
    }
    onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onScroll")
    }
    onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onSslErrorEventReceive")
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        throw new Error("Unimplemented method onSslErrorEvent")
    }
    onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onClientAuthenticationRequest")
    }
    onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onWindowNew")
    }
    onWindowExit(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onWindowExit")
    }
    multiWindowAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method multiWindowAccess")
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onInterceptKeyEvent")
    }
    webStandardFont(value: string | undefined): this {
        throw new Error("Unimplemented method webStandardFont")
    }
    webSerifFont(value: string | undefined): this {
        throw new Error("Unimplemented method webSerifFont")
    }
    webSansSerifFont(value: string | undefined): this {
        throw new Error("Unimplemented method webSansSerifFont")
    }
    webFixedFont(value: string | undefined): this {
        throw new Error("Unimplemented method webFixedFont")
    }
    webFantasyFont(value: string | undefined): this {
        throw new Error("Unimplemented method webFantasyFont")
    }
    webCursiveFont(value: string | undefined): this {
        throw new Error("Unimplemented method webCursiveFont")
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        throw new Error("Unimplemented method defaultFixedFontSize")
    }
    defaultFontSize(value: int32 | undefined): this {
        throw new Error("Unimplemented method defaultFontSize")
    }
    minFontSize(value: int32 | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    minLogicalFontSize(value: int32 | undefined): this {
        throw new Error("Unimplemented method minLogicalFontSize")
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        throw new Error("Unimplemented method defaultTextEncodingFormat")
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method forceDisplayScrollBar")
    }
    blockNetwork(value: boolean | undefined): this {
        throw new Error("Unimplemented method blockNetwork")
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method horizontalScrollBarAccess")
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        throw new Error("Unimplemented method verticalScrollBarAccess")
    }
    onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onTouchIconUrlReceived")
    }
    onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onFaviconReceived")
    }
    onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onPageVisible")
    }
    onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onDataResubmitted")
    }
    pinchSmooth(value: boolean | undefined): this {
        throw new Error("Unimplemented method pinchSmooth")
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        throw new Error("Unimplemented method allowWindowOpenMethod")
    }
    onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onAudioStateChanged")
    }
    onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onFirstContentfulPaint")
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        throw new Error("Unimplemented method onFirstMeaningfulPaint")
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        throw new Error("Unimplemented method onLargestContentfulPaint")
    }
    onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        throw new Error("Unimplemented method onLoadIntercept")
    }
    onControllerAttached(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onControllerAttached")
    }
    onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onOverScroll")
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        throw new Error("Unimplemented method onSafeBrowsingCheckResult")
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        throw new Error("Unimplemented method onNavigationEntryCommitted")
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        throw new Error("Unimplemented method onIntelligentTrackingPreventionResult")
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        throw new Error("Unimplemented method javaScriptOnDocumentStart")
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error("Unimplemented method javaScriptOnDocumentEnd")
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        throw new Error("Unimplemented method layoutMode")
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        throw new Error("Unimplemented method nestedScroll")
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableNativeEmbedMode")
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onNativeEmbedLifecycleChange")
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        throw new Error("Unimplemented method onNativeEmbedVisibilityChange")
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onNativeEmbedGestureEvent")
    }
    copyOptions(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOptions")
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        throw new Error("Unimplemented method onOverrideUrlLoading")
    }
    textAutosizing(value: boolean | undefined): this {
        throw new Error("Unimplemented method textAutosizing")
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        throw new Error("Unimplemented method enableNativeMediaPlayer")
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        throw new Error("Unimplemented method onRenderProcessNotResponding")
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        throw new Error("Unimplemented method onRenderProcessResponding")
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        throw new Error("Unimplemented method onViewportFitChanged")
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        throw new Error("Unimplemented method onInterceptKeyboardAttach")
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        throw new Error("Unimplemented method onAdsBlocked")
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        throw new Error("Unimplemented method keyboardAvoidMode")
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error("Unimplemented method editMenuOptions")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    optimizeParserBudget(value: boolean | undefined): this {
        throw new Error("Unimplemented method optimizeParserBudget")
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableFollowSystemFontWeight")
    }
    enableWebAVSession(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableWebAVSession")
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        throw new Error("Unimplemented method runJavaScriptOnDocumentStart")
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error("Unimplemented method runJavaScriptOnDocumentEnd")
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error("Unimplemented method runJavaScriptOnHeadEnd")
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        throw new Error("Unimplemented method nativeEmbedOptions")
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        throw new Error("Unimplemented method registerNativeEmbedRule")
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        throw new Error("Unimplemented method bindSelectionMenu")
    }
    attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    cacheMode_value?: CacheMode | undefined
    darkMode_value?: WebDarkMode | undefined
    forceDarkAccess_value?: boolean | undefined
    mediaOptions_value?: WebMediaOptions | undefined
    overviewModeAccess_value?: boolean | undefined
    overScrollMode_value?: OverScrollMode | undefined
    blurOnKeyboardHideMode_value?: BlurOnKeyboardHideMode | undefined
    textZoomRatio_value?: int32 | undefined
    databaseAccess_value?: boolean | undefined
    initialScale_value?: double | undefined
    metaViewport_value?: boolean | undefined
    onPageEnd_value?: ((value0: OnPageEndEvent) => void) | undefined
    onPageBegin_value?: ((value0: OnPageBeginEvent) => void) | undefined
    onProgressChange_value?: ((value0: OnProgressChangeEvent) => void) | undefined
    onTitleReceive_value?: ((value0: OnTitleReceiveEvent) => void) | undefined
    onGeolocationHide_value?: (() => void) | undefined
    onGeolocationShow_value?: ((value0: OnGeolocationShowEvent) => void) | undefined
    onRequestSelected_value?: (() => void) | undefined
    onAlert_value?: ((value0: OnAlertEvent) => boolean) | undefined
    onBeforeUnload_value?: ((value0: OnBeforeUnloadEvent) => boolean) | undefined
    onConfirm_value?: ((value0: OnConfirmEvent) => boolean) | undefined
    onPrompt_value?: ((value0: OnPromptEvent) => boolean) | undefined
    onConsole_value?: ((value0: OnConsoleEvent) => boolean) | undefined
    onErrorReceive_value?: ((value0: OnErrorReceiveEvent) => void) | undefined
    onHttpErrorReceive_value?: ((value0: OnHttpErrorReceiveEvent) => void) | undefined
    onDownloadStart_value?: ((value0: OnDownloadStartEvent) => void) | undefined
    onRefreshAccessedHistory_value?: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined
    onRenderExited_value?: ((value0: OnRenderExitedEvent) => void) | undefined
    onShowFileSelector_value?: ((value0: OnShowFileSelectorEvent) => boolean) | undefined
    onResourceLoad_value?: ((value0: OnResourceLoadEvent) => void) | undefined
    onFullScreenExit_value?: (() => void) | undefined
    onFullScreenEnter_value?: OnFullScreenEnterCallback | undefined
    onScaleChange_value?: ((value0: OnScaleChangeEvent) => void) | undefined
    onHttpAuthRequest_value?: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined
    onInterceptRequest_value?: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined
    onPermissionRequest_value?: ((value0: OnPermissionRequestEvent) => void) | undefined
    onScreenCaptureRequest_value?: ((value0: OnScreenCaptureRequestEvent) => void) | undefined
    onContextMenuShow_value?: ((value0: OnContextMenuShowEvent) => boolean) | undefined
    onContextMenuHide_value?: OnContextMenuHideCallback | undefined
    mediaPlayGestureAccess_value?: boolean | undefined
    onSearchResultReceive_value?: ((value0: OnSearchResultReceiveEvent) => void) | undefined
    onScroll_value?: ((value0: OnScrollEvent) => void) | undefined
    onSslErrorEventReceive_value?: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined
    onSslErrorEvent_value?: OnSslErrorEventCallback | undefined
    onClientAuthenticationRequest_value?: ((value0: OnClientAuthenticationEvent) => void) | undefined
    onWindowNew_value?: ((value0: OnWindowNewEvent) => void) | undefined
    onWindowExit_value?: (() => void) | undefined
    multiWindowAccess_value?: boolean | undefined
    onInterceptKeyEvent_value?: ((event: KeyEvent) => boolean) | undefined
    webStandardFont_value?: string | undefined
    webSerifFont_value?: string | undefined
    webSansSerifFont_value?: string | undefined
    webFixedFont_value?: string | undefined
    webFantasyFont_value?: string | undefined
    webCursiveFont_value?: string | undefined
    defaultFixedFontSize_value?: int32 | undefined
    defaultFontSize_value?: int32 | undefined
    minFontSize_value?: int32 | undefined
    minLogicalFontSize_value?: int32 | undefined
    defaultTextEncodingFormat_value?: string | undefined
    forceDisplayScrollBar_value?: boolean | undefined
    blockNetwork_value?: boolean | undefined
    horizontalScrollBarAccess_value?: boolean | undefined
    verticalScrollBarAccess_value?: boolean | undefined
    onTouchIconUrlReceived_value?: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined
    onFaviconReceived_value?: ((value0: OnFaviconReceivedEvent) => void) | undefined
    onPageVisible_value?: ((value0: OnPageVisibleEvent) => void) | undefined
    onDataResubmitted_value?: ((value0: OnDataResubmittedEvent) => void) | undefined
    pinchSmooth_value?: boolean | undefined
    allowWindowOpenMethod_value?: boolean | undefined
    onAudioStateChanged_value?: ((value0: OnAudioStateChangedEvent) => void) | undefined
    onFirstContentfulPaint_value?: ((value0: OnFirstContentfulPaintEvent) => void) | undefined
    onFirstMeaningfulPaint_value?: OnFirstMeaningfulPaintCallback | undefined
    onLargestContentfulPaint_value?: OnLargestContentfulPaintCallback | undefined
    onLoadIntercept_value?: ((value0: OnLoadInterceptEvent) => boolean) | undefined
    onControllerAttached_value?: (() => void) | undefined
    onOverScroll_value?: ((value0: OnOverScrollEvent) => void) | undefined
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
    nativeEmbedOptions_value?: EmbedOptions | undefined
    attributeModifier_value?: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public overviewModeAccess(value: boolean | undefined): this {
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        return this
    }
    public textZoomRatio(value: int32 | undefined): this {
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        return this
    }
    public initialScale(value: double | undefined): this {
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        return this
    }
    public onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        return this
    }
    public onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        return this
    }
    public onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        return this
    }
    public onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        return this
    }
    public onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        return this
    }
    public onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        return this
    }
    public onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        return this
    }
    public onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        return this
    }
    public onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        return this
    }
    public onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        return this
    }
    public onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        return this
    }
    public onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        return this
    }
    public onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        return this
    }
    public onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        return this
    }
    public onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        return this
    }
    public onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        return this
    }
    public onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        return this
    }
    public onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        return this
    }
    public onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        return this
    }
    public onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        return this
    }
    public onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        return this
    }
    public onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        return this
    }
    public onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        return this
    }
    public onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        return this
    }
    public onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        return this
    }
    public onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        return this
    }
    public onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        return this
    }
    public onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        return this
    }
    public onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
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
    public defaultFixedFontSize(value: int32 | undefined): this {
        return this
    }
    public defaultFontSize(value: int32 | undefined): this {
        return this
    }
    public minFontSize(value: int32 | undefined): this {
        return this
    }
    public minLogicalFontSize(value: int32 | undefined): this {
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
    public onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        return this
    }
    public onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        return this
    }
    public onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        return this
    }
    public onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        return this
    }
    public onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        return this
    }
    public onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        return this
    }
    public onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        return this
    }
    public onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
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
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: WebAttribute): void {
        super.apply(target)
        if (this.javaScriptAccess_value !== undefined)
            target.javaScriptAccess(this.javaScriptAccess_value!)
        if (this.fileAccess_value !== undefined)
            target.fileAccess(this.fileAccess_value!)
        if (this.onlineImageAccess_value !== undefined)
            target.onlineImageAccess(this.onlineImageAccess_value!)
        if (this.domStorageAccess_value !== undefined)
            target.domStorageAccess(this.domStorageAccess_value!)
        if (this.imageAccess_value !== undefined)
            target.imageAccess(this.imageAccess_value!)
        if (this.mixedMode_value !== undefined)
            target.mixedMode(this.mixedMode_value!)
        if (this.zoomAccess_value !== undefined)
            target.zoomAccess(this.zoomAccess_value!)
        if (this.geolocationAccess_value !== undefined)
            target.geolocationAccess(this.geolocationAccess_value!)
        if (this.javaScriptProxy_value !== undefined)
            target.javaScriptProxy(this.javaScriptProxy_value!)
        if (this.cacheMode_value !== undefined)
            target.cacheMode(this.cacheMode_value!)
        if (this.darkMode_value !== undefined)
            target.darkMode(this.darkMode_value!)
        if (this.forceDarkAccess_value !== undefined)
            target.forceDarkAccess(this.forceDarkAccess_value!)
        if (this.mediaOptions_value !== undefined)
            target.mediaOptions(this.mediaOptions_value!)
        if (this.overviewModeAccess_value !== undefined)
            target.overviewModeAccess(this.overviewModeAccess_value!)
        if (this.overScrollMode_value !== undefined)
            target.overScrollMode(this.overScrollMode_value!)
        if (this.blurOnKeyboardHideMode_value !== undefined)
            target.blurOnKeyboardHideMode(this.blurOnKeyboardHideMode_value!)
        if (this.textZoomRatio_value !== undefined)
            target.textZoomRatio(this.textZoomRatio_value!)
        if (this.databaseAccess_value !== undefined)
            target.databaseAccess(this.databaseAccess_value!)
        if (this.initialScale_value !== undefined)
            target.initialScale(this.initialScale_value!)
        if (this.metaViewport_value !== undefined)
            target.metaViewport(this.metaViewport_value!)
        if (this.onPageEnd_value !== undefined)
            target.onPageEnd(this.onPageEnd_value!)
        if (this.onPageBegin_value !== undefined)
            target.onPageBegin(this.onPageBegin_value!)
        if (this.onProgressChange_value !== undefined)
            target.onProgressChange(this.onProgressChange_value!)
        if (this.onTitleReceive_value !== undefined)
            target.onTitleReceive(this.onTitleReceive_value!)
        if (this.onGeolocationHide_value !== undefined)
            target.onGeolocationHide(this.onGeolocationHide_value!)
        if (this.onGeolocationShow_value !== undefined)
            target.onGeolocationShow(this.onGeolocationShow_value!)
        if (this.onRequestSelected_value !== undefined)
            target.onRequestSelected(this.onRequestSelected_value!)
        if (this.onAlert_value !== undefined)
            target.onAlert(this.onAlert_value!)
        if (this.onBeforeUnload_value !== undefined)
            target.onBeforeUnload(this.onBeforeUnload_value!)
        if (this.onConfirm_value !== undefined)
            target.onConfirm(this.onConfirm_value!)
        if (this.onPrompt_value !== undefined)
            target.onPrompt(this.onPrompt_value!)
        if (this.onConsole_value !== undefined)
            target.onConsole(this.onConsole_value!)
        if (this.onErrorReceive_value !== undefined)
            target.onErrorReceive(this.onErrorReceive_value!)
        if (this.onHttpErrorReceive_value !== undefined)
            target.onHttpErrorReceive(this.onHttpErrorReceive_value!)
        if (this.onDownloadStart_value !== undefined)
            target.onDownloadStart(this.onDownloadStart_value!)
        if (this.onRefreshAccessedHistory_value !== undefined)
            target.onRefreshAccessedHistory(this.onRefreshAccessedHistory_value!)
        if (this.onRenderExited_value !== undefined)
            target.onRenderExited(this.onRenderExited_value!)
        if (this.onShowFileSelector_value !== undefined)
            target.onShowFileSelector(this.onShowFileSelector_value!)
        if (this.onResourceLoad_value !== undefined)
            target.onResourceLoad(this.onResourceLoad_value!)
        if (this.onFullScreenExit_value !== undefined)
            target.onFullScreenExit(this.onFullScreenExit_value!)
        if (this.onFullScreenEnter_value !== undefined)
            target.onFullScreenEnter(this.onFullScreenEnter_value!)
        if (this.onScaleChange_value !== undefined)
            target.onScaleChange(this.onScaleChange_value!)
        if (this.onHttpAuthRequest_value !== undefined)
            target.onHttpAuthRequest(this.onHttpAuthRequest_value!)
        if (this.onInterceptRequest_value !== undefined)
            target.onInterceptRequest(this.onInterceptRequest_value!)
        if (this.onPermissionRequest_value !== undefined)
            target.onPermissionRequest(this.onPermissionRequest_value!)
        if (this.onScreenCaptureRequest_value !== undefined)
            target.onScreenCaptureRequest(this.onScreenCaptureRequest_value!)
        if (this.onContextMenuShow_value !== undefined)
            target.onContextMenuShow(this.onContextMenuShow_value!)
        if (this.onContextMenuHide_value !== undefined)
            target.onContextMenuHide(this.onContextMenuHide_value!)
        if (this.mediaPlayGestureAccess_value !== undefined)
            target.mediaPlayGestureAccess(this.mediaPlayGestureAccess_value!)
        if (this.onSearchResultReceive_value !== undefined)
            target.onSearchResultReceive(this.onSearchResultReceive_value!)
        if (this.onScroll_value !== undefined)
            target.onScroll(this.onScroll_value!)
        if (this.onSslErrorEventReceive_value !== undefined)
            target.onSslErrorEventReceive(this.onSslErrorEventReceive_value!)
        if (this.onSslErrorEvent_value !== undefined)
            target.onSslErrorEvent(this.onSslErrorEvent_value!)
        if (this.onClientAuthenticationRequest_value !== undefined)
            target.onClientAuthenticationRequest(this.onClientAuthenticationRequest_value!)
        if (this.onWindowNew_value !== undefined)
            target.onWindowNew(this.onWindowNew_value!)
        if (this.onWindowExit_value !== undefined)
            target.onWindowExit(this.onWindowExit_value!)
        if (this.multiWindowAccess_value !== undefined)
            target.multiWindowAccess(this.multiWindowAccess_value!)
        if (this.onInterceptKeyEvent_value !== undefined)
            target.onInterceptKeyEvent(this.onInterceptKeyEvent_value!)
        if (this.webStandardFont_value !== undefined)
            target.webStandardFont(this.webStandardFont_value!)
        if (this.webSerifFont_value !== undefined)
            target.webSerifFont(this.webSerifFont_value!)
        if (this.webSansSerifFont_value !== undefined)
            target.webSansSerifFont(this.webSansSerifFont_value!)
        if (this.webFixedFont_value !== undefined)
            target.webFixedFont(this.webFixedFont_value!)
        if (this.webFantasyFont_value !== undefined)
            target.webFantasyFont(this.webFantasyFont_value!)
        if (this.webCursiveFont_value !== undefined)
            target.webCursiveFont(this.webCursiveFont_value!)
        if (this.defaultFixedFontSize_value !== undefined)
            target.defaultFixedFontSize(this.defaultFixedFontSize_value!)
        if (this.defaultFontSize_value !== undefined)
            target.defaultFontSize(this.defaultFontSize_value!)
        if (this.minFontSize_value !== undefined)
            target.minFontSize(this.minFontSize_value!)
        if (this.minLogicalFontSize_value !== undefined)
            target.minLogicalFontSize(this.minLogicalFontSize_value!)
        if (this.defaultTextEncodingFormat_value !== undefined)
            target.defaultTextEncodingFormat(this.defaultTextEncodingFormat_value!)
        if (this.forceDisplayScrollBar_value !== undefined)
            target.forceDisplayScrollBar(this.forceDisplayScrollBar_value!)
        if (this.blockNetwork_value !== undefined)
            target.blockNetwork(this.blockNetwork_value!)
        if (this.horizontalScrollBarAccess_value !== undefined)
            target.horizontalScrollBarAccess(this.horizontalScrollBarAccess_value!)
        if (this.verticalScrollBarAccess_value !== undefined)
            target.verticalScrollBarAccess(this.verticalScrollBarAccess_value!)
        if (this.onTouchIconUrlReceived_value !== undefined)
            target.onTouchIconUrlReceived(this.onTouchIconUrlReceived_value!)
        if (this.onFaviconReceived_value !== undefined)
            target.onFaviconReceived(this.onFaviconReceived_value!)
        if (this.onPageVisible_value !== undefined)
            target.onPageVisible(this.onPageVisible_value!)
        if (this.onDataResubmitted_value !== undefined)
            target.onDataResubmitted(this.onDataResubmitted_value!)
        if (this.pinchSmooth_value !== undefined)
            target.pinchSmooth(this.pinchSmooth_value!)
        if (this.allowWindowOpenMethod_value !== undefined)
            target.allowWindowOpenMethod(this.allowWindowOpenMethod_value!)
        if (this.onAudioStateChanged_value !== undefined)
            target.onAudioStateChanged(this.onAudioStateChanged_value!)
        if (this.onFirstContentfulPaint_value !== undefined)
            target.onFirstContentfulPaint(this.onFirstContentfulPaint_value!)
        if (this.onFirstMeaningfulPaint_value !== undefined)
            target.onFirstMeaningfulPaint(this.onFirstMeaningfulPaint_value!)
        if (this.onLargestContentfulPaint_value !== undefined)
            target.onLargestContentfulPaint(this.onLargestContentfulPaint_value!)
        if (this.onLoadIntercept_value !== undefined)
            target.onLoadIntercept(this.onLoadIntercept_value!)
        if (this.onControllerAttached_value !== undefined)
            target.onControllerAttached(this.onControllerAttached_value!)
        if (this.onOverScroll_value !== undefined)
            target.onOverScroll(this.onOverScroll_value!)
        if (this.onSafeBrowsingCheckResult_value !== undefined)
            target.onSafeBrowsingCheckResult(this.onSafeBrowsingCheckResult_value!)
        if (this.onNavigationEntryCommitted_value !== undefined)
            target.onNavigationEntryCommitted(this.onNavigationEntryCommitted_value!)
        if (this.onIntelligentTrackingPreventionResult_value !== undefined)
            target.onIntelligentTrackingPreventionResult(this.onIntelligentTrackingPreventionResult_value!)
        if (this.javaScriptOnDocumentStart_value !== undefined)
            target.javaScriptOnDocumentStart(this.javaScriptOnDocumentStart_value!)
        if (this.javaScriptOnDocumentEnd_value !== undefined)
            target.javaScriptOnDocumentEnd(this.javaScriptOnDocumentEnd_value!)
        if (this.layoutMode_value !== undefined)
            target.layoutMode(this.layoutMode_value!)
        if (this.nestedScroll_value !== undefined)
            target.nestedScroll(this.nestedScroll_value!)
        if (this.enableNativeEmbedMode_value !== undefined)
            target.enableNativeEmbedMode(this.enableNativeEmbedMode_value!)
        if (this.onNativeEmbedLifecycleChange_value !== undefined)
            target.onNativeEmbedLifecycleChange(this.onNativeEmbedLifecycleChange_value!)
        if (this.onNativeEmbedVisibilityChange_value !== undefined)
            target.onNativeEmbedVisibilityChange(this.onNativeEmbedVisibilityChange_value!)
        if (this.onNativeEmbedGestureEvent_value !== undefined)
            target.onNativeEmbedGestureEvent(this.onNativeEmbedGestureEvent_value!)
        if (this.copyOptions_value !== undefined)
            target.copyOptions(this.copyOptions_value!)
        if (this.onOverrideUrlLoading_value !== undefined)
            target.onOverrideUrlLoading(this.onOverrideUrlLoading_value!)
        if (this.textAutosizing_value !== undefined)
            target.textAutosizing(this.textAutosizing_value!)
        if (this.enableNativeMediaPlayer_value !== undefined)
            target.enableNativeMediaPlayer(this.enableNativeMediaPlayer_value!)
        if (this.onRenderProcessNotResponding_value !== undefined)
            target.onRenderProcessNotResponding(this.onRenderProcessNotResponding_value!)
        if (this.onRenderProcessResponding_value !== undefined)
            target.onRenderProcessResponding(this.onRenderProcessResponding_value!)
        if (this.onViewportFitChanged_value !== undefined)
            target.onViewportFitChanged(this.onViewportFitChanged_value!)
        if (this.onInterceptKeyboardAttach_value !== undefined)
            target.onInterceptKeyboardAttach(this.onInterceptKeyboardAttach_value!)
        if (this.onAdsBlocked_value !== undefined)
            target.onAdsBlocked(this.onAdsBlocked_value!)
        if (this.keyboardAvoidMode_value !== undefined)
            target.keyboardAvoidMode(this.keyboardAvoidMode_value!)
        if (this.editMenuOptions_value !== undefined)
            target.editMenuOptions(this.editMenuOptions_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
        if (this.optimizeParserBudget_value !== undefined)
            target.optimizeParserBudget(this.optimizeParserBudget_value!)
        if (this.enableFollowSystemFontWeight_value !== undefined)
            target.enableFollowSystemFontWeight(this.enableFollowSystemFontWeight_value!)
        if (this.enableWebAVSession_value !== undefined)
            target.enableWebAVSession(this.enableWebAVSession_value!)
        if (this.runJavaScriptOnDocumentStart_value !== undefined)
            target.runJavaScriptOnDocumentStart(this.runJavaScriptOnDocumentStart_value!)
        if (this.runJavaScriptOnDocumentEnd_value !== undefined)
            target.runJavaScriptOnDocumentEnd(this.runJavaScriptOnDocumentEnd_value!)
        if (this.runJavaScriptOnHeadEnd_value !== undefined)
            target.runJavaScriptOnHeadEnd(this.runJavaScriptOnHeadEnd_value!)
        if (this.nativeEmbedOptions_value !== undefined)
            target.nativeEmbedOptions(this.nativeEmbedOptions_value!)
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
            this.getPeer()?.setJavaScriptAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public fileAccess(value: boolean | undefined): this {
        if (this.checkPriority("fileAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setFileAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onlineImageAccess(value: boolean | undefined): this {
        if (this.checkPriority("onlineImageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setOnlineImageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public domStorageAccess(value: boolean | undefined): this {
        if (this.checkPriority("domStorageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDomStorageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public imageAccess(value: boolean | undefined): this {
        if (this.checkPriority("imageAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setImageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public mixedMode(value: MixedMode | undefined): this {
        if (this.checkPriority("mixedMode")) {
            const value_casted = value as (MixedMode | undefined)
            this.getPeer()?.setMixedModeAttribute(value_casted)
            return this
        }
        return this
    }
    public zoomAccess(value: boolean | undefined): this {
        if (this.checkPriority("zoomAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setZoomAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public geolocationAccess(value: boolean | undefined): this {
        if (this.checkPriority("geolocationAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setGeolocationAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (this.checkPriority("javaScriptProxy")) {
            const value_casted = value as (JavaScriptProxy | undefined)
            this.getPeer()?.setJavaScriptProxyAttribute(value_casted)
            return this
        }
        return this
    }
    public cacheMode(value: CacheMode | undefined): this {
        if (this.checkPriority("cacheMode")) {
            const value_casted = value as (CacheMode | undefined)
            this.getPeer()?.setCacheModeAttribute(value_casted)
            return this
        }
        return this
    }
    public darkMode(value: WebDarkMode | undefined): this {
        if (this.checkPriority("darkMode")) {
            const value_casted = value as (WebDarkMode | undefined)
            this.getPeer()?.setDarkModeAttribute(value_casted)
            return this
        }
        return this
    }
    public forceDarkAccess(value: boolean | undefined): this {
        if (this.checkPriority("forceDarkAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setForceDarkAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public mediaOptions(value: WebMediaOptions | undefined): this {
        if (this.checkPriority("mediaOptions")) {
            const value_casted = value as (WebMediaOptions | undefined)
            this.getPeer()?.setMediaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public overviewModeAccess(value: boolean | undefined): this {
        if (this.checkPriority("overviewModeAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setOverviewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        if (this.checkPriority("overScrollMode")) {
            const value_casted = value as (OverScrollMode | undefined)
            this.getPeer()?.setOverScrollModeAttribute(value_casted)
            return this
        }
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (this.checkPriority("blurOnKeyboardHideMode")) {
            const value_casted = value as (BlurOnKeyboardHideMode | undefined)
            this.getPeer()?.setBlurOnKeyboardHideModeAttribute(value_casted)
            return this
        }
        return this
    }
    public textZoomRatio(value: int32 | undefined): this {
        if (this.checkPriority("textZoomRatio")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setTextZoomRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        if (this.checkPriority("databaseAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDatabaseAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public initialScale(value: double | undefined): this {
        if (this.checkPriority("initialScale")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setInitialScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        if (this.checkPriority("metaViewport")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMetaViewportAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        if (this.checkPriority("onPageEnd")) {
            const value_casted = value as (((value0: OnPageEndEvent) => void) | undefined)
            this.getPeer()?.setOnPageEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        if (this.checkPriority("onPageBegin")) {
            const value_casted = value as (((value0: OnPageBeginEvent) => void) | undefined)
            this.getPeer()?.setOnPageBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        if (this.checkPriority("onProgressChange")) {
            const value_casted = value as (((value0: OnProgressChangeEvent) => void) | undefined)
            this.getPeer()?.setOnProgressChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onTitleReceive")) {
            const value_casted = value as (((value0: OnTitleReceiveEvent) => void) | undefined)
            this.getPeer()?.setOnTitleReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        if (this.checkPriority("onGeolocationHide")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnGeolocationHideAttribute(value_casted)
            return this
        }
        return this
    }
    public onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        if (this.checkPriority("onGeolocationShow")) {
            const value_casted = value as (((value0: OnGeolocationShowEvent) => void) | undefined)
            this.getPeer()?.setOnGeolocationShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        if (this.checkPriority("onRequestSelected")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnRequestSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        if (this.checkPriority("onAlert")) {
            const value_casted = value as (((value0: OnAlertEvent) => boolean) | undefined)
            this.getPeer()?.setOnAlertAttribute(value_casted)
            return this
        }
        return this
    }
    public onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        if (this.checkPriority("onBeforeUnload")) {
            const value_casted = value as (((value0: OnBeforeUnloadEvent) => boolean) | undefined)
            this.getPeer()?.setOnBeforeUnloadAttribute(value_casted)
            return this
        }
        return this
    }
    public onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        if (this.checkPriority("onConfirm")) {
            const value_casted = value as (((value0: OnConfirmEvent) => boolean) | undefined)
            this.getPeer()?.setOnConfirmAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        if (this.checkPriority("onPrompt")) {
            const value_casted = value as (((value0: OnPromptEvent) => boolean) | undefined)
            this.getPeer()?.setOnPromptAttribute(value_casted)
            return this
        }
        return this
    }
    public onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        if (this.checkPriority("onConsole")) {
            const value_casted = value as (((value0: OnConsoleEvent) => boolean) | undefined)
            this.getPeer()?.setOnConsoleAttribute(value_casted)
            return this
        }
        return this
    }
    public onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onErrorReceive")) {
            const value_casted = value as (((value0: OnErrorReceiveEvent) => void) | undefined)
            this.getPeer()?.setOnErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onHttpErrorReceive")) {
            const value_casted = value as (((value0: OnHttpErrorReceiveEvent) => void) | undefined)
            this.getPeer()?.setOnHttpErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        if (this.checkPriority("onDownloadStart")) {
            const value_casted = value as (((value0: OnDownloadStartEvent) => void) | undefined)
            this.getPeer()?.setOnDownloadStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        if (this.checkPriority("onRefreshAccessedHistory")) {
            const value_casted = value as (((value0: OnRefreshAccessedHistoryEvent) => void) | undefined)
            this.getPeer()?.setOnRefreshAccessedHistoryAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        if (this.checkPriority("onRenderExited")) {
            const value_casted = value as (((value0: OnRenderExitedEvent) => void) | undefined)
            this.getPeer()?.setOnRenderExitedAttribute(value_casted)
            return this
        }
        return this
    }
    public onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        if (this.checkPriority("onShowFileSelector")) {
            const value_casted = value as (((value0: OnShowFileSelectorEvent) => boolean) | undefined)
            this.getPeer()?.setOnShowFileSelectorAttribute(value_casted)
            return this
        }
        return this
    }
    public onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        if (this.checkPriority("onResourceLoad")) {
            const value_casted = value as (((value0: OnResourceLoadEvent) => void) | undefined)
            this.getPeer()?.setOnResourceLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        if (this.checkPriority("onFullScreenExit")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnFullScreenExitAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (this.checkPriority("onFullScreenEnter")) {
            const value_casted = value as (OnFullScreenEnterCallback | undefined)
            this.getPeer()?.setOnFullScreenEnterAttribute(value_casted)
            return this
        }
        return this
    }
    public onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        if (this.checkPriority("onScaleChange")) {
            const value_casted = value as (((value0: OnScaleChangeEvent) => void) | undefined)
            this.getPeer()?.setOnScaleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        if (this.checkPriority("onHttpAuthRequest")) {
            const value_casted = value as (((value0: OnHttpAuthRequestEvent) => boolean) | undefined)
            this.getPeer()?.setOnHttpAuthRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        if (this.checkPriority("onInterceptRequest")) {
            const value_casted = value as (((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined)
            this.getPeer()?.setOnInterceptRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        if (this.checkPriority("onPermissionRequest")) {
            const value_casted = value as (((value0: OnPermissionRequestEvent) => void) | undefined)
            this.getPeer()?.setOnPermissionRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        if (this.checkPriority("onScreenCaptureRequest")) {
            const value_casted = value as (((value0: OnScreenCaptureRequestEvent) => void) | undefined)
            this.getPeer()?.setOnScreenCaptureRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        if (this.checkPriority("onContextMenuShow")) {
            const value_casted = value as (((value0: OnContextMenuShowEvent) => boolean) | undefined)
            this.getPeer()?.setOnContextMenuShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (this.checkPriority("onContextMenuHide")) {
            const value_casted = value as (OnContextMenuHideCallback | undefined)
            this.getPeer()?.setOnContextMenuHideAttribute(value_casted)
            return this
        }
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        if (this.checkPriority("mediaPlayGestureAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMediaPlayGestureAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onSearchResultReceive")) {
            const value_casted = value as (((value0: OnSearchResultReceiveEvent) => void) | undefined)
            this.getPeer()?.setOnSearchResultReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((value0: OnScrollEvent) => void) | undefined)
            this.getPeer()?.setOnScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        if (this.checkPriority("onSslErrorEventReceive")) {
            const value_casted = value as (((value0: OnSslErrorEventReceiveEvent) => void) | undefined)
            this.getPeer()?.setOnSslErrorEventReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (this.checkPriority("onSslErrorEvent")) {
            const value_casted = value as (OnSslErrorEventCallback | undefined)
            this.getPeer()?.setOnSslErrorEventAttribute(value_casted)
            return this
        }
        return this
    }
    public onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        if (this.checkPriority("onClientAuthenticationRequest")) {
            const value_casted = value as (((value0: OnClientAuthenticationEvent) => void) | undefined)
            this.getPeer()?.setOnClientAuthenticationRequestAttribute(value_casted)
            return this
        }
        return this
    }
    public onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        if (this.checkPriority("onWindowNew")) {
            const value_casted = value as (((value0: OnWindowNewEvent) => void) | undefined)
            this.getPeer()?.setOnWindowNewAttribute(value_casted)
            return this
        }
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        if (this.checkPriority("onWindowExit")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnWindowExitAttribute(value_casted)
            return this
        }
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        if (this.checkPriority("multiWindowAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMultiWindowAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (this.checkPriority("onInterceptKeyEvent")) {
            const value_casted = value as (((event: KeyEvent) => boolean) | undefined)
            this.getPeer()?.setOnInterceptKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    public webStandardFont(value: string | undefined): this {
        if (this.checkPriority("webStandardFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebStandardFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webSerifFont(value: string | undefined): this {
        if (this.checkPriority("webSerifFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webSansSerifFont(value: string | undefined): this {
        if (this.checkPriority("webSansSerifFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebSansSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webFixedFont(value: string | undefined): this {
        if (this.checkPriority("webFixedFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebFixedFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webFantasyFont(value: string | undefined): this {
        if (this.checkPriority("webFantasyFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebFantasyFontAttribute(value_casted)
            return this
        }
        return this
    }
    public webCursiveFont(value: string | undefined): this {
        if (this.checkPriority("webCursiveFont")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setWebCursiveFontAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultFixedFontSize(value: int32 | undefined): this {
        if (this.checkPriority("defaultFixedFontSize")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setDefaultFixedFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultFontSize(value: int32 | undefined): this {
        if (this.checkPriority("defaultFontSize")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setDefaultFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: int32 | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minLogicalFontSize(value: int32 | undefined): this {
        if (this.checkPriority("minLogicalFontSize")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMinLogicalFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultTextEncodingFormat(value: string | undefined): this {
        if (this.checkPriority("defaultTextEncodingFormat")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setDefaultTextEncodingFormatAttribute(value_casted)
            return this
        }
        return this
    }
    public forceDisplayScrollBar(value: boolean | undefined): this {
        if (this.checkPriority("forceDisplayScrollBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setForceDisplayScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public blockNetwork(value: boolean | undefined): this {
        if (this.checkPriority("blockNetwork")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setBlockNetworkAttribute(value_casted)
            return this
        }
        return this
    }
    public horizontalScrollBarAccess(value: boolean | undefined): this {
        if (this.checkPriority("horizontalScrollBarAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHorizontalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public verticalScrollBarAccess(value: boolean | undefined): this {
        if (this.checkPriority("verticalScrollBarAccess")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setVerticalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    public onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        if (this.checkPriority("onTouchIconUrlReceived")) {
            const value_casted = value as (((value0: OnTouchIconUrlReceivedEvent) => void) | undefined)
            this.getPeer()?.setOnTouchIconUrlReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    public onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        if (this.checkPriority("onFaviconReceived")) {
            const value_casted = value as (((value0: OnFaviconReceivedEvent) => void) | undefined)
            this.getPeer()?.setOnFaviconReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    public onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        if (this.checkPriority("onPageVisible")) {
            const value_casted = value as (((value0: OnPageVisibleEvent) => void) | undefined)
            this.getPeer()?.setOnPageVisibleAttribute(value_casted)
            return this
        }
        return this
    }
    public onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        if (this.checkPriority("onDataResubmitted")) {
            const value_casted = value as (((value0: OnDataResubmittedEvent) => void) | undefined)
            this.getPeer()?.setOnDataResubmittedAttribute(value_casted)
            return this
        }
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        if (this.checkPriority("pinchSmooth")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPinchSmoothAttribute(value_casted)
            return this
        }
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        if (this.checkPriority("allowWindowOpenMethod")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAllowWindowOpenMethodAttribute(value_casted)
            return this
        }
        return this
    }
    public onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        if (this.checkPriority("onAudioStateChanged")) {
            const value_casted = value as (((value0: OnAudioStateChangedEvent) => void) | undefined)
            this.getPeer()?.setOnAudioStateChangedAttribute(value_casted)
            return this
        }
        return this
    }
    public onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        if (this.checkPriority("onFirstContentfulPaint")) {
            const value_casted = value as (((value0: OnFirstContentfulPaintEvent) => void) | undefined)
            this.getPeer()?.setOnFirstContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (this.checkPriority("onFirstMeaningfulPaint")) {
            const value_casted = value as (OnFirstMeaningfulPaintCallback | undefined)
            this.getPeer()?.setOnFirstMeaningfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (this.checkPriority("onLargestContentfulPaint")) {
            const value_casted = value as (OnLargestContentfulPaintCallback | undefined)
            this.getPeer()?.setOnLargestContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    public onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        if (this.checkPriority("onLoadIntercept")) {
            const value_casted = value as (((value0: OnLoadInterceptEvent) => boolean) | undefined)
            this.getPeer()?.setOnLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        if (this.checkPriority("onControllerAttached")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnControllerAttachedAttribute(value_casted)
            return this
        }
        return this
    }
    public onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
        if (this.checkPriority("onOverScroll")) {
            const value_casted = value as (((value0: OnOverScrollEvent) => void) | undefined)
            this.getPeer()?.setOnOverScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (this.checkPriority("onSafeBrowsingCheckResult")) {
            const value_casted = value as (OnSafeBrowsingCheckResultCallback | undefined)
            this.getPeer()?.setOnSafeBrowsingCheckResultAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (this.checkPriority("onNavigationEntryCommitted")) {
            const value_casted = value as (OnNavigationEntryCommittedCallback | undefined)
            this.getPeer()?.setOnNavigationEntryCommittedAttribute(value_casted)
            return this
        }
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (this.checkPriority("onIntelligentTrackingPreventionResult")) {
            const value_casted = value as (OnIntelligentTrackingPreventionCallback | undefined)
            this.getPeer()?.setOnIntelligentTrackingPreventionResultAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("javaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.setJavaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("javaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.setJavaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutMode(value: WebLayoutMode | undefined): this {
        if (this.checkPriority("layoutMode")) {
            const value_casted = value as (WebLayoutMode | undefined)
            this.getPeer()?.setLayoutModeAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | NestedScrollOptionsExt | undefined)
            this.getPeer()?.setNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNativeEmbedMode(value: boolean | undefined): this {
        if (this.checkPriority("enableNativeEmbedMode")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableNativeEmbedModeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (this.checkPriority("onNativeEmbedLifecycleChange")) {
            const value_casted = value as (((event: NativeEmbedDataInfo) => void) | undefined)
            this.getPeer()?.setOnNativeEmbedLifecycleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (this.checkPriority("onNativeEmbedVisibilityChange")) {
            const value_casted = value as (OnNativeEmbedVisibilityChangeCallback | undefined)
            this.getPeer()?.setOnNativeEmbedVisibilityChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (this.checkPriority("onNativeEmbedGestureEvent")) {
            const value_casted = value as (((event: NativeEmbedTouchInfo) => void) | undefined)
            this.getPeer()?.setOnNativeEmbedGestureEventAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (this.checkPriority("onOverrideUrlLoading")) {
            const value_casted = value as (OnOverrideUrlLoadingCallback | undefined)
            this.getPeer()?.setOnOverrideUrlLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    public textAutosizing(value: boolean | undefined): this {
        if (this.checkPriority("textAutosizing")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setTextAutosizingAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (this.checkPriority("enableNativeMediaPlayer")) {
            const value_casted = value as (NativeMediaPlayerConfig | undefined)
            this.getPeer()?.setEnableNativeMediaPlayerAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (this.checkPriority("onRenderProcessNotResponding")) {
            const value_casted = value as (OnRenderProcessNotRespondingCallback | undefined)
            this.getPeer()?.setOnRenderProcessNotRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (this.checkPriority("onRenderProcessResponding")) {
            const value_casted = value as (OnRenderProcessRespondingCallback | undefined)
            this.getPeer()?.setOnRenderProcessRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (this.checkPriority("onViewportFitChanged")) {
            const value_casted = value as (OnViewportFitChangedCallback | undefined)
            this.getPeer()?.setOnViewportFitChangedAttribute(value_casted)
            return this
        }
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (this.checkPriority("onInterceptKeyboardAttach")) {
            const value_casted = value as (WebKeyboardCallback | undefined)
            this.getPeer()?.setOnInterceptKeyboardAttachAttribute(value_casted)
            return this
        }
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (this.checkPriority("onAdsBlocked")) {
            const value_casted = value as (OnAdsBlockedCallback | undefined)
            this.getPeer()?.setOnAdsBlockedAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (this.checkPriority("keyboardAvoidMode")) {
            const value_casted = value as (WebKeyboardAvoidMode | undefined)
            this.getPeer()?.setKeyboardAvoidModeAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public optimizeParserBudget(value: boolean | undefined): this {
        if (this.checkPriority("optimizeParserBudget")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setOptimizeParserBudgetAttribute(value_casted)
            return this
        }
        return this
    }
    public enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (this.checkPriority("enableFollowSystemFontWeight")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableFollowSystemFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public enableWebAVSession(value: boolean | undefined): this {
        if (this.checkPriority("enableWebAVSession")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableWebAVSessionAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.setRunJavaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.setRunJavaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    public runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (this.checkPriority("runJavaScriptOnHeadEnd")) {
            const value_casted = value as (Array<ScriptItem> | undefined)
            this.getPeer()?.setRunJavaScriptOnHeadEndAttribute(value_casted)
            return this
        }
        return this
    }
    public nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (this.checkPriority("nativeEmbedOptions")) {
            const value_casted = value as (EmbedOptions | undefined)
            this.getPeer()?.setNativeEmbedOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (this.checkPriority("registerNativeEmbedRule")) {
            const tag_casted = tag as (string | undefined)
            const type_casted = type as (string | undefined)
            this.getPeer()?.setRegisterNativeEmbedRuleAttribute(tag_casted, type_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const elementType_casted = elementType as (WebElementType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (WebResponseType | undefined)
            const options_casted = options as (SelectionMenuOptionsExt | undefined)
            this.getPeer()?.setBindSelectionMenuAttribute(elementType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withWebStyle(receiver: WebAttribute, modifier: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkWebStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Web")
// export function Web(
//     value: WebOptions,
//     @memo
//     content_?: () => void,
// ): WebAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Web(
    @memo
    style: ((attributes: WebAttribute) => void) | undefined,
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
        withWebStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkWebSet extends ArkCommonMethodSet implements WebAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _javaScriptAccess_flag?: boolean
    _javaScriptAccess0_value?: boolean | undefined
    _fileAccess_flag?: boolean
    _fileAccess0_value?: boolean | undefined
    _onlineImageAccess_flag?: boolean
    _onlineImageAccess0_value?: boolean | undefined
    _domStorageAccess_flag?: boolean
    _domStorageAccess0_value?: boolean | undefined
    _imageAccess_flag?: boolean
    _imageAccess0_value?: boolean | undefined
    _mixedMode_flag?: boolean
    _mixedMode0_value?: MixedMode | undefined
    _zoomAccess_flag?: boolean
    _zoomAccess0_value?: boolean | undefined
    _geolocationAccess_flag?: boolean
    _geolocationAccess0_value?: boolean | undefined
    _javaScriptProxy_flag?: boolean
    _javaScriptProxy0_value?: JavaScriptProxy | undefined
    _cacheMode_flag?: boolean
    _cacheMode0_value?: CacheMode | undefined
    _darkMode_flag?: boolean
    _darkMode0_value?: WebDarkMode | undefined
    _forceDarkAccess_flag?: boolean
    _forceDarkAccess0_value?: boolean | undefined
    _mediaOptions_flag?: boolean
    _mediaOptions0_value?: WebMediaOptions | undefined
    _overviewModeAccess_flag?: boolean
    _overviewModeAccess0_value?: boolean | undefined
    _overScrollMode_flag?: boolean
    _overScrollMode0_value?: OverScrollMode | undefined
    _blurOnKeyboardHideMode_flag?: boolean
    _blurOnKeyboardHideMode0_value?: BlurOnKeyboardHideMode | undefined
    _textZoomRatio_flag?: boolean
    _textZoomRatio0_value?: int32 | undefined
    _databaseAccess_flag?: boolean
    _databaseAccess0_value?: boolean | undefined
    _initialScale_flag?: boolean
    _initialScale0_value?: double | undefined
    _metaViewport_flag?: boolean
    _metaViewport0_value?: boolean | undefined
    _onPageEnd_flag?: boolean
    _onPageEnd0_value?: ((value0: OnPageEndEvent) => void) | undefined
    _onPageBegin_flag?: boolean
    _onPageBegin0_value?: ((value0: OnPageBeginEvent) => void) | undefined
    _onProgressChange_flag?: boolean
    _onProgressChange0_value?: ((value0: OnProgressChangeEvent) => void) | undefined
    _onTitleReceive_flag?: boolean
    _onTitleReceive0_value?: ((value0: OnTitleReceiveEvent) => void) | undefined
    _onGeolocationHide_flag?: boolean
    _onGeolocationHide0_value?: (() => void) | undefined
    _onGeolocationShow_flag?: boolean
    _onGeolocationShow0_value?: ((value0: OnGeolocationShowEvent) => void) | undefined
    _onRequestSelected_flag?: boolean
    _onRequestSelected0_value?: (() => void) | undefined
    _onAlert_flag?: boolean
    _onAlert0_value?: ((value0: OnAlertEvent) => boolean) | undefined
    _onBeforeUnload_flag?: boolean
    _onBeforeUnload0_value?: ((value0: OnBeforeUnloadEvent) => boolean) | undefined
    _onConfirm_flag?: boolean
    _onConfirm0_value?: ((value0: OnConfirmEvent) => boolean) | undefined
    _onPrompt_flag?: boolean
    _onPrompt0_value?: ((value0: OnPromptEvent) => boolean) | undefined
    _onConsole_flag?: boolean
    _onConsole0_value?: ((value0: OnConsoleEvent) => boolean) | undefined
    _onErrorReceive_flag?: boolean
    _onErrorReceive0_value?: ((value0: OnErrorReceiveEvent) => void) | undefined
    _onHttpErrorReceive_flag?: boolean
    _onHttpErrorReceive0_value?: ((value0: OnHttpErrorReceiveEvent) => void) | undefined
    _onDownloadStart_flag?: boolean
    _onDownloadStart0_value?: ((value0: OnDownloadStartEvent) => void) | undefined
    _onRefreshAccessedHistory_flag?: boolean
    _onRefreshAccessedHistory0_value?: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined
    _onRenderExited_flag?: boolean
    _onRenderExited0_value?: ((value0: OnRenderExitedEvent) => void) | undefined
    _onShowFileSelector_flag?: boolean
    _onShowFileSelector0_value?: ((value0: OnShowFileSelectorEvent) => boolean) | undefined
    _onResourceLoad_flag?: boolean
    _onResourceLoad0_value?: ((value0: OnResourceLoadEvent) => void) | undefined
    _onFullScreenExit_flag?: boolean
    _onFullScreenExit0_value?: (() => void) | undefined
    _onFullScreenEnter_flag?: boolean
    _onFullScreenEnter0_value?: OnFullScreenEnterCallback | undefined
    _onScaleChange_flag?: boolean
    _onScaleChange0_value?: ((value0: OnScaleChangeEvent) => void) | undefined
    _onHttpAuthRequest_flag?: boolean
    _onHttpAuthRequest0_value?: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined
    _onInterceptRequest_flag?: boolean
    _onInterceptRequest0_value?: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined
    _onPermissionRequest_flag?: boolean
    _onPermissionRequest0_value?: ((value0: OnPermissionRequestEvent) => void) | undefined
    _onScreenCaptureRequest_flag?: boolean
    _onScreenCaptureRequest0_value?: ((value0: OnScreenCaptureRequestEvent) => void) | undefined
    _onContextMenuShow_flag?: boolean
    _onContextMenuShow0_value?: ((value0: OnContextMenuShowEvent) => boolean) | undefined
    _onContextMenuHide_flag?: boolean
    _onContextMenuHide0_value?: OnContextMenuHideCallback | undefined
    _mediaPlayGestureAccess_flag?: boolean
    _mediaPlayGestureAccess0_value?: boolean | undefined
    _onSearchResultReceive_flag?: boolean
    _onSearchResultReceive0_value?: ((value0: OnSearchResultReceiveEvent) => void) | undefined
    _onScroll_flag?: boolean
    _onScroll0_value?: ((value0: OnScrollEvent) => void) | undefined
    _onSslErrorEventReceive_flag?: boolean
    _onSslErrorEventReceive0_value?: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined
    _onSslErrorEvent_flag?: boolean
    _onSslErrorEvent0_value?: OnSslErrorEventCallback | undefined
    _onClientAuthenticationRequest_flag?: boolean
    _onClientAuthenticationRequest0_value?: ((value0: OnClientAuthenticationEvent) => void) | undefined
    _onWindowNew_flag?: boolean
    _onWindowNew0_value?: ((value0: OnWindowNewEvent) => void) | undefined
    _onWindowExit_flag?: boolean
    _onWindowExit0_value?: (() => void) | undefined
    _multiWindowAccess_flag?: boolean
    _multiWindowAccess0_value?: boolean | undefined
    _onInterceptKeyEvent_flag?: boolean
    _onInterceptKeyEvent0_value?: ((event: KeyEvent) => boolean) | undefined
    _webStandardFont_flag?: boolean
    _webStandardFont0_value?: string | undefined
    _webSerifFont_flag?: boolean
    _webSerifFont0_value?: string | undefined
    _webSansSerifFont_flag?: boolean
    _webSansSerifFont0_value?: string | undefined
    _webFixedFont_flag?: boolean
    _webFixedFont0_value?: string | undefined
    _webFantasyFont_flag?: boolean
    _webFantasyFont0_value?: string | undefined
    _webCursiveFont_flag?: boolean
    _webCursiveFont0_value?: string | undefined
    _defaultFixedFontSize_flag?: boolean
    _defaultFixedFontSize0_value?: int32 | undefined
    _defaultFontSize_flag?: boolean
    _defaultFontSize0_value?: int32 | undefined
    _minFontSize_flag?: boolean
    _minFontSize0_value?: int32 | undefined
    _minLogicalFontSize_flag?: boolean
    _minLogicalFontSize0_value?: int32 | undefined
    _defaultTextEncodingFormat_flag?: boolean
    _defaultTextEncodingFormat0_value?: string | undefined
    _forceDisplayScrollBar_flag?: boolean
    _forceDisplayScrollBar0_value?: boolean | undefined
    _blockNetwork_flag?: boolean
    _blockNetwork0_value?: boolean | undefined
    _horizontalScrollBarAccess_flag?: boolean
    _horizontalScrollBarAccess0_value?: boolean | undefined
    _verticalScrollBarAccess_flag?: boolean
    _verticalScrollBarAccess0_value?: boolean | undefined
    _onTouchIconUrlReceived_flag?: boolean
    _onTouchIconUrlReceived0_value?: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined
    _onFaviconReceived_flag?: boolean
    _onFaviconReceived0_value?: ((value0: OnFaviconReceivedEvent) => void) | undefined
    _onPageVisible_flag?: boolean
    _onPageVisible0_value?: ((value0: OnPageVisibleEvent) => void) | undefined
    _onDataResubmitted_flag?: boolean
    _onDataResubmitted0_value?: ((value0: OnDataResubmittedEvent) => void) | undefined
    _pinchSmooth_flag?: boolean
    _pinchSmooth0_value?: boolean | undefined
    _allowWindowOpenMethod_flag?: boolean
    _allowWindowOpenMethod0_value?: boolean | undefined
    _onAudioStateChanged_flag?: boolean
    _onAudioStateChanged0_value?: ((value0: OnAudioStateChangedEvent) => void) | undefined
    _onFirstContentfulPaint_flag?: boolean
    _onFirstContentfulPaint0_value?: ((value0: OnFirstContentfulPaintEvent) => void) | undefined
    _onFirstMeaningfulPaint_flag?: boolean
    _onFirstMeaningfulPaint0_value?: OnFirstMeaningfulPaintCallback | undefined
    _onLargestContentfulPaint_flag?: boolean
    _onLargestContentfulPaint0_value?: OnLargestContentfulPaintCallback | undefined
    _onLoadIntercept_flag?: boolean
    _onLoadIntercept0_value?: ((value0: OnLoadInterceptEvent) => boolean) | undefined
    _onControllerAttached_flag?: boolean
    _onControllerAttached0_value?: (() => void) | undefined
    _onOverScroll_flag?: boolean
    _onOverScroll0_value?: ((value0: OnOverScrollEvent) => void) | undefined
    _onSafeBrowsingCheckResult_flag?: boolean
    _onSafeBrowsingCheckResult0_value?: OnSafeBrowsingCheckResultCallback | undefined
    _onNavigationEntryCommitted_flag?: boolean
    _onNavigationEntryCommitted0_value?: OnNavigationEntryCommittedCallback | undefined
    _onIntelligentTrackingPreventionResult_flag?: boolean
    _onIntelligentTrackingPreventionResult0_value?: OnIntelligentTrackingPreventionCallback | undefined
    _javaScriptOnDocumentStart_flag?: boolean
    _javaScriptOnDocumentStart0_value?: Array<ScriptItem> | undefined
    _javaScriptOnDocumentEnd_flag?: boolean
    _javaScriptOnDocumentEnd0_value?: Array<ScriptItem> | undefined
    _layoutMode_flag?: boolean
    _layoutMode0_value?: WebLayoutMode | undefined
    _nestedScroll_flag?: boolean
    _nestedScroll0_value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    _enableNativeEmbedMode_flag?: boolean
    _enableNativeEmbedMode0_value?: boolean | undefined
    _onNativeEmbedLifecycleChange_flag?: boolean
    _onNativeEmbedLifecycleChange0_value?: ((event: NativeEmbedDataInfo) => void) | undefined
    _onNativeEmbedVisibilityChange_flag?: boolean
    _onNativeEmbedVisibilityChange0_value?: OnNativeEmbedVisibilityChangeCallback | undefined
    _onNativeEmbedGestureEvent_flag?: boolean
    _onNativeEmbedGestureEvent0_value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    _copyOptions_flag?: boolean
    _copyOptions0_value?: CopyOptions | undefined
    _onOverrideUrlLoading_flag?: boolean
    _onOverrideUrlLoading0_value?: OnOverrideUrlLoadingCallback | undefined
    _textAutosizing_flag?: boolean
    _textAutosizing0_value?: boolean | undefined
    _enableNativeMediaPlayer_flag?: boolean
    _enableNativeMediaPlayer0_value?: NativeMediaPlayerConfig | undefined
    _onRenderProcessNotResponding_flag?: boolean
    _onRenderProcessNotResponding0_value?: OnRenderProcessNotRespondingCallback | undefined
    _onRenderProcessResponding_flag?: boolean
    _onRenderProcessResponding0_value?: OnRenderProcessRespondingCallback | undefined
    _onViewportFitChanged_flag?: boolean
    _onViewportFitChanged0_value?: OnViewportFitChangedCallback | undefined
    _onInterceptKeyboardAttach_flag?: boolean
    _onInterceptKeyboardAttach0_value?: WebKeyboardCallback | undefined
    _onAdsBlocked_flag?: boolean
    _onAdsBlocked0_value?: OnAdsBlockedCallback | undefined
    _keyboardAvoidMode_flag?: boolean
    _keyboardAvoidMode0_value?: WebKeyboardAvoidMode | undefined
    _editMenuOptions_flag?: boolean
    _editMenuOptions0_value?: EditMenuOptions | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _optimizeParserBudget_flag?: boolean
    _optimizeParserBudget0_value?: boolean | undefined
    _enableFollowSystemFontWeight_flag?: boolean
    _enableFollowSystemFontWeight0_value?: boolean | undefined
    _enableWebAVSession_flag?: boolean
    _enableWebAVSession0_value?: boolean | undefined
    _runJavaScriptOnDocumentStart_flag?: boolean
    _runJavaScriptOnDocumentStart0_value?: Array<ScriptItem> | undefined
    _runJavaScriptOnDocumentEnd_flag?: boolean
    _runJavaScriptOnDocumentEnd0_value?: Array<ScriptItem> | undefined
    _runJavaScriptOnHeadEnd_flag?: boolean
    _runJavaScriptOnHeadEnd0_value?: Array<ScriptItem> | undefined
    _nativeEmbedOptions_flag?: boolean
    _nativeEmbedOptions0_value?: EmbedOptions | undefined
    _registerNativeEmbedRule_flag?: boolean
    _registerNativeEmbedRule0_value?: string | undefined
    _registerNativeEmbedRule1_value?: string | undefined
    _bindSelectionMenu_flag?: boolean
    _bindSelectionMenu0_value?: WebElementType | undefined
    _bindSelectionMenu1_value?: CustomBuilder | undefined
    _bindSelectionMenu2_value?: WebResponseType | undefined
    _bindSelectionMenu3_value?: SelectionMenuOptionsExt | undefined
    applyModifierPatch(component: WebAttribute): void {
        if (this._javaScriptAccess_flag)
            component.javaScriptAccess((this._javaScriptAccess0_value as boolean | undefined))
        if (this._fileAccess_flag)
            component.fileAccess((this._fileAccess0_value as boolean | undefined))
        if (this._onlineImageAccess_flag)
            component.onlineImageAccess((this._onlineImageAccess0_value as boolean | undefined))
        if (this._domStorageAccess_flag)
            component.domStorageAccess((this._domStorageAccess0_value as boolean | undefined))
        if (this._imageAccess_flag)
            component.imageAccess((this._imageAccess0_value as boolean | undefined))
        if (this._mixedMode_flag)
            component.mixedMode((this._mixedMode0_value as MixedMode | undefined))
        if (this._zoomAccess_flag)
            component.zoomAccess((this._zoomAccess0_value as boolean | undefined))
        if (this._geolocationAccess_flag)
            component.geolocationAccess((this._geolocationAccess0_value as boolean | undefined))
        if (this._javaScriptProxy_flag)
            component.javaScriptProxy((this._javaScriptProxy0_value as JavaScriptProxy | undefined))
        if (this._cacheMode_flag)
            component.cacheMode((this._cacheMode0_value as CacheMode | undefined))
        if (this._darkMode_flag)
            component.darkMode((this._darkMode0_value as WebDarkMode | undefined))
        if (this._forceDarkAccess_flag)
            component.forceDarkAccess((this._forceDarkAccess0_value as boolean | undefined))
        if (this._mediaOptions_flag)
            component.mediaOptions((this._mediaOptions0_value as WebMediaOptions | undefined))
        if (this._overviewModeAccess_flag)
            component.overviewModeAccess((this._overviewModeAccess0_value as boolean | undefined))
        if (this._overScrollMode_flag)
            component.overScrollMode((this._overScrollMode0_value as OverScrollMode | undefined))
        if (this._blurOnKeyboardHideMode_flag)
            component.blurOnKeyboardHideMode((this._blurOnKeyboardHideMode0_value as BlurOnKeyboardHideMode | undefined))
        if (this._textZoomRatio_flag)
            component.textZoomRatio((this._textZoomRatio0_value as int32 | undefined))
        if (this._databaseAccess_flag)
            component.databaseAccess((this._databaseAccess0_value as boolean | undefined))
        if (this._initialScale_flag)
            component.initialScale((this._initialScale0_value as double | undefined))
        if (this._metaViewport_flag)
            component.metaViewport((this._metaViewport0_value as boolean | undefined))
        if (this._onPageEnd_flag)
            component.onPageEnd((this._onPageEnd0_value as ((value0: OnPageEndEvent) => void) | undefined))
        if (this._onPageBegin_flag)
            component.onPageBegin((this._onPageBegin0_value as ((value0: OnPageBeginEvent) => void) | undefined))
        if (this._onProgressChange_flag)
            component.onProgressChange((this._onProgressChange0_value as ((value0: OnProgressChangeEvent) => void) | undefined))
        if (this._onTitleReceive_flag)
            component.onTitleReceive((this._onTitleReceive0_value as ((value0: OnTitleReceiveEvent) => void) | undefined))
        if (this._onGeolocationHide_flag)
            component.onGeolocationHide((this._onGeolocationHide0_value as (() => void) | undefined))
        if (this._onGeolocationShow_flag)
            component.onGeolocationShow((this._onGeolocationShow0_value as ((value0: OnGeolocationShowEvent) => void) | undefined))
        if (this._onRequestSelected_flag)
            component.onRequestSelected((this._onRequestSelected0_value as (() => void) | undefined))
        if (this._onAlert_flag)
            component.onAlert((this._onAlert0_value as ((value0: OnAlertEvent) => boolean) | undefined))
        if (this._onBeforeUnload_flag)
            component.onBeforeUnload((this._onBeforeUnload0_value as ((value0: OnBeforeUnloadEvent) => boolean) | undefined))
        if (this._onConfirm_flag)
            component.onConfirm((this._onConfirm0_value as ((value0: OnConfirmEvent) => boolean) | undefined))
        if (this._onPrompt_flag)
            component.onPrompt((this._onPrompt0_value as ((value0: OnPromptEvent) => boolean) | undefined))
        if (this._onConsole_flag)
            component.onConsole((this._onConsole0_value as ((value0: OnConsoleEvent) => boolean) | undefined))
        if (this._onErrorReceive_flag)
            component.onErrorReceive((this._onErrorReceive0_value as ((value0: OnErrorReceiveEvent) => void) | undefined))
        if (this._onHttpErrorReceive_flag)
            component.onHttpErrorReceive((this._onHttpErrorReceive0_value as ((value0: OnHttpErrorReceiveEvent) => void) | undefined))
        if (this._onDownloadStart_flag)
            component.onDownloadStart((this._onDownloadStart0_value as ((value0: OnDownloadStartEvent) => void) | undefined))
        if (this._onRefreshAccessedHistory_flag)
            component.onRefreshAccessedHistory((this._onRefreshAccessedHistory0_value as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined))
        if (this._onRenderExited_flag)
            component.onRenderExited((this._onRenderExited0_value as ((value0: OnRenderExitedEvent) => void) | undefined))
        if (this._onShowFileSelector_flag)
            component.onShowFileSelector((this._onShowFileSelector0_value as ((value0: OnShowFileSelectorEvent) => boolean) | undefined))
        if (this._onResourceLoad_flag)
            component.onResourceLoad((this._onResourceLoad0_value as ((value0: OnResourceLoadEvent) => void) | undefined))
        if (this._onFullScreenExit_flag)
            component.onFullScreenExit((this._onFullScreenExit0_value as (() => void) | undefined))
        if (this._onFullScreenEnter_flag)
            component.onFullScreenEnter((this._onFullScreenEnter0_value as OnFullScreenEnterCallback | undefined))
        if (this._onScaleChange_flag)
            component.onScaleChange((this._onScaleChange0_value as ((value0: OnScaleChangeEvent) => void) | undefined))
        if (this._onHttpAuthRequest_flag)
            component.onHttpAuthRequest((this._onHttpAuthRequest0_value as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined))
        if (this._onInterceptRequest_flag)
            component.onInterceptRequest((this._onInterceptRequest0_value as ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined))
        if (this._onPermissionRequest_flag)
            component.onPermissionRequest((this._onPermissionRequest0_value as ((value0: OnPermissionRequestEvent) => void) | undefined))
        if (this._onScreenCaptureRequest_flag)
            component.onScreenCaptureRequest((this._onScreenCaptureRequest0_value as ((value0: OnScreenCaptureRequestEvent) => void) | undefined))
        if (this._onContextMenuShow_flag)
            component.onContextMenuShow((this._onContextMenuShow0_value as ((value0: OnContextMenuShowEvent) => boolean) | undefined))
        if (this._onContextMenuHide_flag)
            component.onContextMenuHide((this._onContextMenuHide0_value as OnContextMenuHideCallback | undefined))
        if (this._mediaPlayGestureAccess_flag)
            component.mediaPlayGestureAccess((this._mediaPlayGestureAccess0_value as boolean | undefined))
        if (this._onSearchResultReceive_flag)
            component.onSearchResultReceive((this._onSearchResultReceive0_value as ((value0: OnSearchResultReceiveEvent) => void) | undefined))
        if (this._onScroll_flag)
            component.onScroll((this._onScroll0_value as ((value0: OnScrollEvent) => void) | undefined))
        if (this._onSslErrorEventReceive_flag)
            component.onSslErrorEventReceive((this._onSslErrorEventReceive0_value as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined))
        if (this._onSslErrorEvent_flag)
            component.onSslErrorEvent((this._onSslErrorEvent0_value as OnSslErrorEventCallback | undefined))
        if (this._onClientAuthenticationRequest_flag)
            component.onClientAuthenticationRequest((this._onClientAuthenticationRequest0_value as ((value0: OnClientAuthenticationEvent) => void) | undefined))
        if (this._onWindowNew_flag)
            component.onWindowNew((this._onWindowNew0_value as ((value0: OnWindowNewEvent) => void) | undefined))
        if (this._onWindowExit_flag)
            component.onWindowExit((this._onWindowExit0_value as (() => void) | undefined))
        if (this._multiWindowAccess_flag)
            component.multiWindowAccess((this._multiWindowAccess0_value as boolean | undefined))
        if (this._onInterceptKeyEvent_flag)
            component.onInterceptKeyEvent((this._onInterceptKeyEvent0_value as ((event: KeyEvent) => boolean) | undefined))
        if (this._webStandardFont_flag)
            component.webStandardFont((this._webStandardFont0_value as string | undefined))
        if (this._webSerifFont_flag)
            component.webSerifFont((this._webSerifFont0_value as string | undefined))
        if (this._webSansSerifFont_flag)
            component.webSansSerifFont((this._webSansSerifFont0_value as string | undefined))
        if (this._webFixedFont_flag)
            component.webFixedFont((this._webFixedFont0_value as string | undefined))
        if (this._webFantasyFont_flag)
            component.webFantasyFont((this._webFantasyFont0_value as string | undefined))
        if (this._webCursiveFont_flag)
            component.webCursiveFont((this._webCursiveFont0_value as string | undefined))
        if (this._defaultFixedFontSize_flag)
            component.defaultFixedFontSize((this._defaultFixedFontSize0_value as int32 | undefined))
        if (this._defaultFontSize_flag)
            component.defaultFontSize((this._defaultFontSize0_value as int32 | undefined))
        if (this._minFontSize_flag)
            component.minFontSize((this._minFontSize0_value as int32 | undefined))
        if (this._minLogicalFontSize_flag)
            component.minLogicalFontSize((this._minLogicalFontSize0_value as int32 | undefined))
        if (this._defaultTextEncodingFormat_flag)
            component.defaultTextEncodingFormat((this._defaultTextEncodingFormat0_value as string | undefined))
        if (this._forceDisplayScrollBar_flag)
            component.forceDisplayScrollBar((this._forceDisplayScrollBar0_value as boolean | undefined))
        if (this._blockNetwork_flag)
            component.blockNetwork((this._blockNetwork0_value as boolean | undefined))
        if (this._horizontalScrollBarAccess_flag)
            component.horizontalScrollBarAccess((this._horizontalScrollBarAccess0_value as boolean | undefined))
        if (this._verticalScrollBarAccess_flag)
            component.verticalScrollBarAccess((this._verticalScrollBarAccess0_value as boolean | undefined))
        if (this._onTouchIconUrlReceived_flag)
            component.onTouchIconUrlReceived((this._onTouchIconUrlReceived0_value as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined))
        if (this._onFaviconReceived_flag)
            component.onFaviconReceived((this._onFaviconReceived0_value as ((value0: OnFaviconReceivedEvent) => void) | undefined))
        if (this._onPageVisible_flag)
            component.onPageVisible((this._onPageVisible0_value as ((value0: OnPageVisibleEvent) => void) | undefined))
        if (this._onDataResubmitted_flag)
            component.onDataResubmitted((this._onDataResubmitted0_value as ((value0: OnDataResubmittedEvent) => void) | undefined))
        if (this._pinchSmooth_flag)
            component.pinchSmooth((this._pinchSmooth0_value as boolean | undefined))
        if (this._allowWindowOpenMethod_flag)
            component.allowWindowOpenMethod((this._allowWindowOpenMethod0_value as boolean | undefined))
        if (this._onAudioStateChanged_flag)
            component.onAudioStateChanged((this._onAudioStateChanged0_value as ((value0: OnAudioStateChangedEvent) => void) | undefined))
        if (this._onFirstContentfulPaint_flag)
            component.onFirstContentfulPaint((this._onFirstContentfulPaint0_value as ((value0: OnFirstContentfulPaintEvent) => void) | undefined))
        if (this._onFirstMeaningfulPaint_flag)
            component.onFirstMeaningfulPaint((this._onFirstMeaningfulPaint0_value as OnFirstMeaningfulPaintCallback | undefined))
        if (this._onLargestContentfulPaint_flag)
            component.onLargestContentfulPaint((this._onLargestContentfulPaint0_value as OnLargestContentfulPaintCallback | undefined))
        if (this._onLoadIntercept_flag)
            component.onLoadIntercept((this._onLoadIntercept0_value as ((value0: OnLoadInterceptEvent) => boolean) | undefined))
        if (this._onControllerAttached_flag)
            component.onControllerAttached((this._onControllerAttached0_value as (() => void) | undefined))
        if (this._onOverScroll_flag)
            component.onOverScroll((this._onOverScroll0_value as ((value0: OnOverScrollEvent) => void) | undefined))
        if (this._onSafeBrowsingCheckResult_flag)
            component.onSafeBrowsingCheckResult((this._onSafeBrowsingCheckResult0_value as OnSafeBrowsingCheckResultCallback | undefined))
        if (this._onNavigationEntryCommitted_flag)
            component.onNavigationEntryCommitted((this._onNavigationEntryCommitted0_value as OnNavigationEntryCommittedCallback | undefined))
        if (this._onIntelligentTrackingPreventionResult_flag)
            component.onIntelligentTrackingPreventionResult((this._onIntelligentTrackingPreventionResult0_value as OnIntelligentTrackingPreventionCallback | undefined))
        if (this._javaScriptOnDocumentStart_flag)
            component.javaScriptOnDocumentStart((this._javaScriptOnDocumentStart0_value as Array<ScriptItem> | undefined))
        if (this._javaScriptOnDocumentEnd_flag)
            component.javaScriptOnDocumentEnd((this._javaScriptOnDocumentEnd0_value as Array<ScriptItem> | undefined))
        if (this._layoutMode_flag)
            component.layoutMode((this._layoutMode0_value as WebLayoutMode | undefined))
        if (this._nestedScroll_flag)
            component.nestedScroll((this._nestedScroll0_value as NestedScrollOptions | NestedScrollOptionsExt | undefined))
        if (this._enableNativeEmbedMode_flag)
            component.enableNativeEmbedMode((this._enableNativeEmbedMode0_value as boolean | undefined))
        if (this._onNativeEmbedLifecycleChange_flag)
            component.onNativeEmbedLifecycleChange((this._onNativeEmbedLifecycleChange0_value as ((event: NativeEmbedDataInfo) => void) | undefined))
        if (this._onNativeEmbedVisibilityChange_flag)
            component.onNativeEmbedVisibilityChange((this._onNativeEmbedVisibilityChange0_value as OnNativeEmbedVisibilityChangeCallback | undefined))
        if (this._onNativeEmbedGestureEvent_flag)
            component.onNativeEmbedGestureEvent((this._onNativeEmbedGestureEvent0_value as ((event: NativeEmbedTouchInfo) => void) | undefined))
        if (this._copyOptions_flag)
            component.copyOptions((this._copyOptions0_value as CopyOptions | undefined))
        if (this._onOverrideUrlLoading_flag)
            component.onOverrideUrlLoading((this._onOverrideUrlLoading0_value as OnOverrideUrlLoadingCallback | undefined))
        if (this._textAutosizing_flag)
            component.textAutosizing((this._textAutosizing0_value as boolean | undefined))
        if (this._enableNativeMediaPlayer_flag)
            component.enableNativeMediaPlayer((this._enableNativeMediaPlayer0_value as NativeMediaPlayerConfig | undefined))
        if (this._onRenderProcessNotResponding_flag)
            component.onRenderProcessNotResponding((this._onRenderProcessNotResponding0_value as OnRenderProcessNotRespondingCallback | undefined))
        if (this._onRenderProcessResponding_flag)
            component.onRenderProcessResponding((this._onRenderProcessResponding0_value as OnRenderProcessRespondingCallback | undefined))
        if (this._onViewportFitChanged_flag)
            component.onViewportFitChanged((this._onViewportFitChanged0_value as OnViewportFitChangedCallback | undefined))
        if (this._onInterceptKeyboardAttach_flag)
            component.onInterceptKeyboardAttach((this._onInterceptKeyboardAttach0_value as WebKeyboardCallback | undefined))
        if (this._onAdsBlocked_flag)
            component.onAdsBlocked((this._onAdsBlocked0_value as OnAdsBlockedCallback | undefined))
        if (this._keyboardAvoidMode_flag)
            component.keyboardAvoidMode((this._keyboardAvoidMode0_value as WebKeyboardAvoidMode | undefined))
        if (this._editMenuOptions_flag)
            component.editMenuOptions((this._editMenuOptions0_value as EditMenuOptions | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._optimizeParserBudget_flag)
            component.optimizeParserBudget((this._optimizeParserBudget0_value as boolean | undefined))
        if (this._enableFollowSystemFontWeight_flag)
            component.enableFollowSystemFontWeight((this._enableFollowSystemFontWeight0_value as boolean | undefined))
        if (this._enableWebAVSession_flag)
            component.enableWebAVSession((this._enableWebAVSession0_value as boolean | undefined))
        if (this._runJavaScriptOnDocumentStart_flag)
            component.runJavaScriptOnDocumentStart((this._runJavaScriptOnDocumentStart0_value as Array<ScriptItem> | undefined))
        if (this._runJavaScriptOnDocumentEnd_flag)
            component.runJavaScriptOnDocumentEnd((this._runJavaScriptOnDocumentEnd0_value as Array<ScriptItem> | undefined))
        if (this._runJavaScriptOnHeadEnd_flag)
            component.runJavaScriptOnHeadEnd((this._runJavaScriptOnHeadEnd0_value as Array<ScriptItem> | undefined))
        if (this._nativeEmbedOptions_flag)
            component.nativeEmbedOptions((this._nativeEmbedOptions0_value as EmbedOptions | undefined))
        if (this._registerNativeEmbedRule_flag)
            component.registerNativeEmbedRule((this._registerNativeEmbedRule0_value as string | undefined), (this._registerNativeEmbedRule1_value as string | undefined))
        if (this._bindSelectionMenu_flag)
            component.bindSelectionMenu((this._bindSelectionMenu0_value as WebElementType | undefined), (this._bindSelectionMenu1_value as CustomBuilder | undefined), (this._bindSelectionMenu2_value as WebResponseType | undefined), (this._bindSelectionMenu3_value as SelectionMenuOptionsExt | undefined))
    }
    public javaScriptAccess(value: boolean | undefined): this {
        this._javaScriptAccess_flag = true
        this._javaScriptAccess0_value = value
        return this
    }
    public fileAccess(value: boolean | undefined): this {
        this._fileAccess_flag = true
        this._fileAccess0_value = value
        return this
    }
    public onlineImageAccess(value: boolean | undefined): this {
        this._onlineImageAccess_flag = true
        this._onlineImageAccess0_value = value
        return this
    }
    public domStorageAccess(value: boolean | undefined): this {
        this._domStorageAccess_flag = true
        this._domStorageAccess0_value = value
        return this
    }
    public imageAccess(value: boolean | undefined): this {
        this._imageAccess_flag = true
        this._imageAccess0_value = value
        return this
    }
    public mixedMode(value: MixedMode | undefined): this {
        this._mixedMode_flag = true
        this._mixedMode0_value = value
        return this
    }
    public zoomAccess(value: boolean | undefined): this {
        this._zoomAccess_flag = true
        this._zoomAccess0_value = value
        return this
    }
    public geolocationAccess(value: boolean | undefined): this {
        this._geolocationAccess_flag = true
        this._geolocationAccess0_value = value
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy | undefined): this {
        this._javaScriptProxy_flag = true
        this._javaScriptProxy0_value = value
        return this
    }
    public cacheMode(value: CacheMode | undefined): this {
        this._cacheMode_flag = true
        this._cacheMode0_value = value
        return this
    }
    public darkMode(value: WebDarkMode | undefined): this {
        this._darkMode_flag = true
        this._darkMode0_value = value
        return this
    }
    public forceDarkAccess(value: boolean | undefined): this {
        this._forceDarkAccess_flag = true
        this._forceDarkAccess0_value = value
        return this
    }
    public mediaOptions(value: WebMediaOptions | undefined): this {
        this._mediaOptions_flag = true
        this._mediaOptions0_value = value
        return this
    }
    public overviewModeAccess(value: boolean | undefined): this {
        this._overviewModeAccess_flag = true
        this._overviewModeAccess0_value = value
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        this._overScrollMode_flag = true
        this._overScrollMode0_value = value
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        this._blurOnKeyboardHideMode_flag = true
        this._blurOnKeyboardHideMode0_value = value
        return this
    }
    public textZoomRatio(value: int32 | undefined): this {
        this._textZoomRatio_flag = true
        this._textZoomRatio0_value = value
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        this._databaseAccess_flag = true
        this._databaseAccess0_value = value
        return this
    }
    public initialScale(value: double | undefined): this {
        this._initialScale_flag = true
        this._initialScale0_value = value
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        this._metaViewport_flag = true
        this._metaViewport0_value = value
        return this
    }
    public onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        this._onPageEnd_flag = true
        this._onPageEnd0_value = value
        return this
    }
    public onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        this._onPageBegin_flag = true
        this._onPageBegin0_value = value
        return this
    }
    public onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        this._onProgressChange_flag = true
        this._onProgressChange0_value = value
        return this
    }
    public onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        this._onTitleReceive_flag = true
        this._onTitleReceive0_value = value
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        this._onGeolocationHide_flag = true
        this._onGeolocationHide0_value = value
        return this
    }
    public onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        this._onGeolocationShow_flag = true
        this._onGeolocationShow0_value = value
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        this._onRequestSelected_flag = true
        this._onRequestSelected0_value = value
        return this
    }
    public onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        this._onAlert_flag = true
        this._onAlert0_value = value
        return this
    }
    public onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        this._onBeforeUnload_flag = true
        this._onBeforeUnload0_value = value
        return this
    }
    public onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        this._onConfirm_flag = true
        this._onConfirm0_value = value
        return this
    }
    public onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        this._onPrompt_flag = true
        this._onPrompt0_value = value
        return this
    }
    public onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        this._onConsole_flag = true
        this._onConsole0_value = value
        return this
    }
    public onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        this._onErrorReceive_flag = true
        this._onErrorReceive0_value = value
        return this
    }
    public onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        this._onHttpErrorReceive_flag = true
        this._onHttpErrorReceive0_value = value
        return this
    }
    public onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        this._onDownloadStart_flag = true
        this._onDownloadStart0_value = value
        return this
    }
    public onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        this._onRefreshAccessedHistory_flag = true
        this._onRefreshAccessedHistory0_value = value
        return this
    }
    public onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        this._onRenderExited_flag = true
        this._onRenderExited0_value = value
        return this
    }
    public onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        this._onShowFileSelector_flag = true
        this._onShowFileSelector0_value = value
        return this
    }
    public onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        this._onResourceLoad_flag = true
        this._onResourceLoad0_value = value
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        this._onFullScreenExit_flag = true
        this._onFullScreenExit0_value = value
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        this._onFullScreenEnter_flag = true
        this._onFullScreenEnter0_value = value
        return this
    }
    public onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        this._onScaleChange_flag = true
        this._onScaleChange0_value = value
        return this
    }
    public onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        this._onHttpAuthRequest_flag = true
        this._onHttpAuthRequest0_value = value
        return this
    }
    public onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        this._onInterceptRequest_flag = true
        this._onInterceptRequest0_value = value
        return this
    }
    public onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        this._onPermissionRequest_flag = true
        this._onPermissionRequest0_value = value
        return this
    }
    public onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        this._onScreenCaptureRequest_flag = true
        this._onScreenCaptureRequest0_value = value
        return this
    }
    public onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        this._onContextMenuShow_flag = true
        this._onContextMenuShow0_value = value
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        this._onContextMenuHide_flag = true
        this._onContextMenuHide0_value = value
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        this._mediaPlayGestureAccess_flag = true
        this._mediaPlayGestureAccess0_value = value
        return this
    }
    public onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        this._onSearchResultReceive_flag = true
        this._onSearchResultReceive0_value = value
        return this
    }
    public onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        this._onScroll_flag = true
        this._onScroll0_value = value
        return this
    }
    public onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        this._onSslErrorEventReceive_flag = true
        this._onSslErrorEventReceive0_value = value
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        this._onSslErrorEvent_flag = true
        this._onSslErrorEvent0_value = value
        return this
    }
    public onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        this._onClientAuthenticationRequest_flag = true
        this._onClientAuthenticationRequest0_value = value
        return this
    }
    public onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        this._onWindowNew_flag = true
        this._onWindowNew0_value = value
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        this._onWindowExit_flag = true
        this._onWindowExit0_value = value
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        this._multiWindowAccess_flag = true
        this._multiWindowAccess0_value = value
        return this
    }
    public onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        this._onInterceptKeyEvent_flag = true
        this._onInterceptKeyEvent0_value = value
        return this
    }
    public webStandardFont(value: string | undefined): this {
        this._webStandardFont_flag = true
        this._webStandardFont0_value = value
        return this
    }
    public webSerifFont(value: string | undefined): this {
        this._webSerifFont_flag = true
        this._webSerifFont0_value = value
        return this
    }
    public webSansSerifFont(value: string | undefined): this {
        this._webSansSerifFont_flag = true
        this._webSansSerifFont0_value = value
        return this
    }
    public webFixedFont(value: string | undefined): this {
        this._webFixedFont_flag = true
        this._webFixedFont0_value = value
        return this
    }
    public webFantasyFont(value: string | undefined): this {
        this._webFantasyFont_flag = true
        this._webFantasyFont0_value = value
        return this
    }
    public webCursiveFont(value: string | undefined): this {
        this._webCursiveFont_flag = true
        this._webCursiveFont0_value = value
        return this
    }
    public defaultFixedFontSize(value: int32 | undefined): this {
        this._defaultFixedFontSize_flag = true
        this._defaultFixedFontSize0_value = value
        return this
    }
    public defaultFontSize(value: int32 | undefined): this {
        this._defaultFontSize_flag = true
        this._defaultFontSize0_value = value
        return this
    }
    public minFontSize(value: int32 | undefined): this {
        this._minFontSize_flag = true
        this._minFontSize0_value = value
        return this
    }
    public minLogicalFontSize(value: int32 | undefined): this {
        this._minLogicalFontSize_flag = true
        this._minLogicalFontSize0_value = value
        return this
    }
    public defaultTextEncodingFormat(value: string | undefined): this {
        this._defaultTextEncodingFormat_flag = true
        this._defaultTextEncodingFormat0_value = value
        return this
    }
    public forceDisplayScrollBar(value: boolean | undefined): this {
        this._forceDisplayScrollBar_flag = true
        this._forceDisplayScrollBar0_value = value
        return this
    }
    public blockNetwork(value: boolean | undefined): this {
        this._blockNetwork_flag = true
        this._blockNetwork0_value = value
        return this
    }
    public horizontalScrollBarAccess(value: boolean | undefined): this {
        this._horizontalScrollBarAccess_flag = true
        this._horizontalScrollBarAccess0_value = value
        return this
    }
    public verticalScrollBarAccess(value: boolean | undefined): this {
        this._verticalScrollBarAccess_flag = true
        this._verticalScrollBarAccess0_value = value
        return this
    }
    public onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        this._onTouchIconUrlReceived_flag = true
        this._onTouchIconUrlReceived0_value = value
        return this
    }
    public onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        this._onFaviconReceived_flag = true
        this._onFaviconReceived0_value = value
        return this
    }
    public onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        this._onPageVisible_flag = true
        this._onPageVisible0_value = value
        return this
    }
    public onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        this._onDataResubmitted_flag = true
        this._onDataResubmitted0_value = value
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        this._pinchSmooth_flag = true
        this._pinchSmooth0_value = value
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        this._allowWindowOpenMethod_flag = true
        this._allowWindowOpenMethod0_value = value
        return this
    }
    public onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        this._onAudioStateChanged_flag = true
        this._onAudioStateChanged0_value = value
        return this
    }
    public onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        this._onFirstContentfulPaint_flag = true
        this._onFirstContentfulPaint0_value = value
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        this._onFirstMeaningfulPaint_flag = true
        this._onFirstMeaningfulPaint0_value = value
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        this._onLargestContentfulPaint_flag = true
        this._onLargestContentfulPaint0_value = value
        return this
    }
    public onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        this._onLoadIntercept_flag = true
        this._onLoadIntercept0_value = value
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        this._onControllerAttached_flag = true
        this._onControllerAttached0_value = value
        return this
    }
    public onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
        this._onOverScroll_flag = true
        this._onOverScroll0_value = value
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        this._onSafeBrowsingCheckResult_flag = true
        this._onSafeBrowsingCheckResult0_value = value
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        this._onNavigationEntryCommitted_flag = true
        this._onNavigationEntryCommitted0_value = value
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        this._onIntelligentTrackingPreventionResult_flag = true
        this._onIntelligentTrackingPreventionResult0_value = value
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        this._javaScriptOnDocumentStart_flag = true
        this._javaScriptOnDocumentStart0_value = value
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        this._javaScriptOnDocumentEnd_flag = true
        this._javaScriptOnDocumentEnd0_value = value
        return this
    }
    public layoutMode(value: WebLayoutMode | undefined): this {
        this._layoutMode_flag = true
        this._layoutMode0_value = value
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        this._nestedScroll_flag = true
        this._nestedScroll0_value = value
        return this
    }
    public enableNativeEmbedMode(value: boolean | undefined): this {
        this._enableNativeEmbedMode_flag = true
        this._enableNativeEmbedMode0_value = value
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        this._onNativeEmbedLifecycleChange_flag = true
        this._onNativeEmbedLifecycleChange0_value = value
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        this._onNativeEmbedVisibilityChange_flag = true
        this._onNativeEmbedVisibilityChange0_value = value
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        this._onNativeEmbedGestureEvent_flag = true
        this._onNativeEmbedGestureEvent0_value = value
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        this._copyOptions_flag = true
        this._copyOptions0_value = value
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        this._onOverrideUrlLoading_flag = true
        this._onOverrideUrlLoading0_value = value
        return this
    }
    public textAutosizing(value: boolean | undefined): this {
        this._textAutosizing_flag = true
        this._textAutosizing0_value = value
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        this._enableNativeMediaPlayer_flag = true
        this._enableNativeMediaPlayer0_value = value
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        this._onRenderProcessNotResponding_flag = true
        this._onRenderProcessNotResponding0_value = value
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        this._onRenderProcessResponding_flag = true
        this._onRenderProcessResponding0_value = value
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        this._onViewportFitChanged_flag = true
        this._onViewportFitChanged0_value = value
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        this._onInterceptKeyboardAttach_flag = true
        this._onInterceptKeyboardAttach0_value = value
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        this._onAdsBlocked_flag = true
        this._onAdsBlocked0_value = value
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        this._keyboardAvoidMode_flag = true
        this._keyboardAvoidMode0_value = value
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        this._editMenuOptions_flag = true
        this._editMenuOptions0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public optimizeParserBudget(value: boolean | undefined): this {
        this._optimizeParserBudget_flag = true
        this._optimizeParserBudget0_value = value
        return this
    }
    public enableFollowSystemFontWeight(value: boolean | undefined): this {
        this._enableFollowSystemFontWeight_flag = true
        this._enableFollowSystemFontWeight0_value = value
        return this
    }
    public enableWebAVSession(value: boolean | undefined): this {
        this._enableWebAVSession_flag = true
        this._enableWebAVSession0_value = value
        return this
    }
    public runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        this._runJavaScriptOnDocumentStart_flag = true
        this._runJavaScriptOnDocumentStart0_value = value
        return this
    }
    public runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        this._runJavaScriptOnDocumentEnd_flag = true
        this._runJavaScriptOnDocumentEnd0_value = value
        return this
    }
    public runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        this._runJavaScriptOnHeadEnd_flag = true
        this._runJavaScriptOnHeadEnd0_value = value
        return this
    }
    public nativeEmbedOptions(value: EmbedOptions | undefined): this {
        this._nativeEmbedOptions_flag = true
        this._nativeEmbedOptions0_value = value
        return this
    }
    public registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        this._registerNativeEmbedRule_flag = true
        this._registerNativeEmbedRule0_value = tag
        this._registerNativeEmbedRule1_value = type
        return this
    }
    public bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        this._bindSelectionMenu_flag = true
        this._bindSelectionMenu0_value = elementType
        this._bindSelectionMenu1_value = content
        this._bindSelectionMenu2_value = responseType
        this._bindSelectionMenu3_value = options
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ClientAuthenticationHandler_serializer {
    public static write(buffer: SerializerBase, value: ClientAuthenticationHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ClientAuthenticationHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ClientAuthenticationHandlerInternal.fromPtr(ptr)
    }
}
export class ConsoleMessage_serializer {
    public static write(buffer: SerializerBase, value: ConsoleMessage): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ConsoleMessage {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ConsoleMessageInternal.fromPtr(ptr)
    }
}
export class ControllerHandler_serializer {
    public static write(buffer: SerializerBase, value: ControllerHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ControllerHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ControllerHandlerInternal.fromPtr(ptr)
    }
}
export class DataResubmissionHandler_serializer {
    public static write(buffer: SerializerBase, value: DataResubmissionHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DataResubmissionHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DataResubmissionHandlerInternal.fromPtr(ptr)
    }
}
export class EventResult_serializer {
    public static write(buffer: SerializerBase, value: EventResult): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): EventResult {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return EventResultInternal.fromPtr(ptr)
    }
}
export class FileSelectorParam_serializer {
    public static write(buffer: SerializerBase, value: FileSelectorParam): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FileSelectorParam {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return FileSelectorParamInternal.fromPtr(ptr)
    }
}
export class FileSelectorResult_serializer {
    public static write(buffer: SerializerBase, value: FileSelectorResult): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FileSelectorResult {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return FileSelectorResultInternal.fromPtr(ptr)
    }
}
export class FullScreenExitHandler_serializer {
    public static write(buffer: SerializerBase, value: FullScreenExitHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FullScreenExitHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return FullScreenExitHandlerInternal.fromPtr(ptr)
    }
}
export class HttpAuthHandler_serializer {
    public static write(buffer: SerializerBase, value: HttpAuthHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): HttpAuthHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return HttpAuthHandlerInternal.fromPtr(ptr)
    }
}
export class JsGeolocation_serializer {
    public static write(buffer: SerializerBase, value: JsGeolocation): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): JsGeolocation {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return JsGeolocationInternal.fromPtr(ptr)
    }
}
export class JsResult_serializer {
    public static write(buffer: SerializerBase, value: JsResult): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): JsResult {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return JsResultInternal.fromPtr(ptr)
    }
}
export class NativeMediaPlayerConfig_serializer {
    public static write(buffer: SerializerBase, value: NativeMediaPlayerConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_enable  = value.enable
        valueSerializer.writeBoolean(value_enable)
        const value_shouldOverlay  = value.shouldOverlay
        valueSerializer.writeBoolean(value_shouldOverlay)
    }
    public static read(buffer: DeserializerBase): NativeMediaPlayerConfig {
        let valueDeserializer : DeserializerBase = buffer
        const enable_result : boolean = valueDeserializer.readBoolean()
        const shouldOverlay_result : boolean = valueDeserializer.readBoolean()
        let value : NativeMediaPlayerConfig = ({enable: enable_result, shouldOverlay: shouldOverlay_result} as NativeMediaPlayerConfig)
        return value
    }
}
export class OnAudioStateChangedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAudioStateChangedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_playing  = value.playing
        valueSerializer.writeBoolean(value_playing)
    }
    public static read(buffer: DeserializerBase): OnAudioStateChangedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const playing_result : boolean = valueDeserializer.readBoolean()
        let value : OnAudioStateChangedEvent = ({playing: playing_result} as OnAudioStateChangedEvent)
        return value
    }
}
export class OnConsoleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConsoleEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_message  = value.message
        ConsoleMessage_serializer.write(valueSerializer, value_message)
    }
    public static read(buffer: DeserializerBase): OnConsoleEvent {
        let valueDeserializer : DeserializerBase = buffer
        const message_result : ConsoleMessage = (ConsoleMessage_serializer.read(valueDeserializer) as ConsoleMessage)
        let value : OnConsoleEvent = ({message: message_result} as OnConsoleEvent)
        return value
    }
}
export class OnDataResubmittedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDataResubmittedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        DataResubmissionHandler_serializer.write(valueSerializer, value_handler)
    }
    public static read(buffer: DeserializerBase): OnDataResubmittedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : DataResubmissionHandler = (DataResubmissionHandler_serializer.read(valueDeserializer) as DataResubmissionHandler)
        let value : OnDataResubmittedEvent = ({handler: handler_result} as OnDataResubmittedEvent)
        return value
    }
}
export class OnFaviconReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFaviconReceivedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_favicon  = value.favicon
        image_PixelMap_serializer.write(valueSerializer, value_favicon)
    }
    public static read(buffer: DeserializerBase): OnFaviconReceivedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const favicon_result : image.PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        let value : OnFaviconReceivedEvent = ({favicon: favicon_result} as OnFaviconReceivedEvent)
        return value
    }
}
export class OnFirstContentfulPaintEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFirstContentfulPaintEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_navigationStartTick  = value.navigationStartTick
        valueSerializer.writeInt64(value_navigationStartTick)
        const value_firstContentfulPaintMs  = value.firstContentfulPaintMs
        valueSerializer.writeInt64(value_firstContentfulPaintMs)
    }
    public static read(buffer: DeserializerBase): OnFirstContentfulPaintEvent {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTick_result : int64 = valueDeserializer.readInt64()
        const firstContentfulPaintMs_result : int64 = valueDeserializer.readInt64()
        let value : OnFirstContentfulPaintEvent = ({navigationStartTick: navigationStartTick_result, firstContentfulPaintMs: firstContentfulPaintMs_result} as OnFirstContentfulPaintEvent)
        return value
    }
}
export class OnOverScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnOverScrollEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_xOffset  = value.xOffset
        valueSerializer.writeFloat64(value_xOffset)
        const value_yOffset  = value.yOffset
        valueSerializer.writeFloat64(value_yOffset)
    }
    public static read(buffer: DeserializerBase): OnOverScrollEvent {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_result : double = valueDeserializer.readFloat64()
        const yOffset_result : double = valueDeserializer.readFloat64()
        let value : OnOverScrollEvent = ({xOffset: xOffset_result, yOffset: yOffset_result} as OnOverScrollEvent)
        return value
    }
}
export class OnProgressChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnProgressChangeEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_newProgress  = value.newProgress
        valueSerializer.writeInt32(value_newProgress)
    }
    public static read(buffer: DeserializerBase): OnProgressChangeEvent {
        let valueDeserializer : DeserializerBase = buffer
        const newProgress_result : int32 = valueDeserializer.readInt32()
        let value : OnProgressChangeEvent = ({newProgress: newProgress_result} as OnProgressChangeEvent)
        return value
    }
}
export class OnScaleChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScaleChangeEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_oldScale  = value.oldScale
        valueSerializer.writeFloat64(value_oldScale)
        const value_newScale  = value.newScale
        valueSerializer.writeFloat64(value_newScale)
    }
    public static read(buffer: DeserializerBase): OnScaleChangeEvent {
        let valueDeserializer : DeserializerBase = buffer
        const oldScale_result : double = valueDeserializer.readFloat64()
        const newScale_result : double = valueDeserializer.readFloat64()
        let value : OnScaleChangeEvent = ({oldScale: oldScale_result, newScale: newScale_result} as OnScaleChangeEvent)
        return value
    }
}
export class OnScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScrollEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_xOffset  = value.xOffset
        valueSerializer.writeFloat64(value_xOffset)
        const value_yOffset  = value.yOffset
        valueSerializer.writeFloat64(value_yOffset)
    }
    public static read(buffer: DeserializerBase): OnScrollEvent {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_result : double = valueDeserializer.readFloat64()
        const yOffset_result : double = valueDeserializer.readFloat64()
        let value : OnScrollEvent = ({xOffset: xOffset_result, yOffset: yOffset_result} as OnScrollEvent)
        return value
    }
}
export class OnSearchResultReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSearchResultReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_activeMatchOrdinal  = value.activeMatchOrdinal
        valueSerializer.writeNumber(value_activeMatchOrdinal)
        const value_numberOfMatches  = value.numberOfMatches
        valueSerializer.writeNumber(value_numberOfMatches)
        const value_isDoneCounting  = value.isDoneCounting
        valueSerializer.writeBoolean(value_isDoneCounting)
    }
    public static read(buffer: DeserializerBase): OnSearchResultReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const activeMatchOrdinal_result : number = (valueDeserializer.readNumber() as number)
        const numberOfMatches_result : number = (valueDeserializer.readNumber() as number)
        const isDoneCounting_result : boolean = valueDeserializer.readBoolean()
        let value : OnSearchResultReceiveEvent = ({activeMatchOrdinal: activeMatchOrdinal_result, numberOfMatches: numberOfMatches_result, isDoneCounting: isDoneCounting_result} as OnSearchResultReceiveEvent)
        return value
    }
}
export class OnShowFileSelectorEvent_serializer {
    public static write(buffer: SerializerBase, value: OnShowFileSelectorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_result  = value.result
        FileSelectorResult_serializer.write(valueSerializer, value_result)
        const value_fileSelector  = value.fileSelector
        FileSelectorParam_serializer.write(valueSerializer, value_fileSelector)
    }
    public static read(buffer: DeserializerBase): OnShowFileSelectorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const result_result : FileSelectorResult = (FileSelectorResult_serializer.read(valueDeserializer) as FileSelectorResult)
        const fileSelector_result : FileSelectorParam = (FileSelectorParam_serializer.read(valueDeserializer) as FileSelectorParam)
        let value : OnShowFileSelectorEvent = ({result: result_result, fileSelector: fileSelector_result} as OnShowFileSelectorEvent)
        return value
    }
}
export class PermissionRequest_serializer {
    public static write(buffer: SerializerBase, value: PermissionRequest): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PermissionRequest {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PermissionRequestInternal.fromPtr(ptr)
    }
}
export class ScreenCaptureHandler_serializer {
    public static write(buffer: SerializerBase, value: ScreenCaptureHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ScreenCaptureHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ScreenCaptureHandlerInternal.fromPtr(ptr)
    }
}
export class SslErrorHandler_serializer {
    public static write(buffer: SerializerBase, value: SslErrorHandler): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SslErrorHandler {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SslErrorHandlerInternal.fromPtr(ptr)
    }
}
export class WebContextMenuParam_serializer {
    public static write(buffer: SerializerBase, value: WebContextMenuParam): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebContextMenuParam {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebContextMenuParamInternal.fromPtr(ptr)
    }
}
export class WebContextMenuResult_serializer {
    public static write(buffer: SerializerBase, value: WebContextMenuResult): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebContextMenuResult {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebContextMenuResultInternal.fromPtr(ptr)
    }
}
export class WebCookie_serializer {
    public static write(buffer: SerializerBase, value: WebCookie): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebCookie {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebCookieInternal.fromPtr(ptr)
    }
}
export class WebKeyboardController_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebKeyboardController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebKeyboardControllerInternal.fromPtr(ptr)
    }
}
export class WebResourceError_serializer {
    public static write(buffer: SerializerBase, value: WebResourceError): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceError {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebResourceErrorInternal.fromPtr(ptr)
    }
}
export class WebResourceRequest_serializer {
    public static write(buffer: SerializerBase, value: WebResourceRequest): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceRequest {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebResourceRequestInternal.fromPtr(ptr)
    }
}
export class WebResourceResponse_serializer {
    public static write(buffer: SerializerBase, value: WebResourceResponse): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceResponse {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WebResourceResponseInternal.fromPtr(ptr)
    }
}
export class AdsBlockedDetails_serializer {
    public static write(buffer: SerializerBase, value: AdsBlockedDetails): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_adsBlocked  = value.adsBlocked
        valueSerializer.writeInt32((value_adsBlocked.length).toInt())
        for (let value_adsBlocked_counter_i = 0; value_adsBlocked_counter_i < value_adsBlocked.length; value_adsBlocked_counter_i++) {
            const value_adsBlocked_element : string = value_adsBlocked[value_adsBlocked_counter_i]
            valueSerializer.writeString(value_adsBlocked_element)
        }
    }
    public static read(buffer: DeserializerBase): AdsBlockedDetails {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const adsBlocked_buf_length : int32 = valueDeserializer.readInt32()
        let adsBlocked_buf : Array<string> = new Array<string>(adsBlocked_buf_length)
        for (let adsBlocked_buf_i = 0; adsBlocked_buf_i < adsBlocked_buf_length; adsBlocked_buf_i++) {
            adsBlocked_buf[adsBlocked_buf_i] = (valueDeserializer.readString() as string)
        }
        const adsBlocked_result : Array<string> = adsBlocked_buf
        let value : AdsBlockedDetails = ({url: url_result, adsBlocked: adsBlocked_result} as AdsBlockedDetails)
        return value
    }
}
export class EmbedOptions_serializer {
    public static write(buffer: SerializerBase, value: EmbedOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_supportDefaultIntrinsicSize  = value.supportDefaultIntrinsicSize
        let value_supportDefaultIntrinsicSize_type : int32 = RuntimeType.UNDEFINED
        value_supportDefaultIntrinsicSize_type = runtimeType(value_supportDefaultIntrinsicSize)
        valueSerializer.writeInt8((value_supportDefaultIntrinsicSize_type).toChar())
        if ((value_supportDefaultIntrinsicSize_type) != (RuntimeType.UNDEFINED)) {
            const value_supportDefaultIntrinsicSize_value  = value_supportDefaultIntrinsicSize!
            valueSerializer.writeBoolean(value_supportDefaultIntrinsicSize_value)
        }
    }
    public static read(buffer: DeserializerBase): EmbedOptions {
        let valueDeserializer : DeserializerBase = buffer
        const supportDefaultIntrinsicSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let supportDefaultIntrinsicSize_buf : boolean | undefined
        if ((supportDefaultIntrinsicSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            supportDefaultIntrinsicSize_buf = valueDeserializer.readBoolean()
        }
        const supportDefaultIntrinsicSize_result : boolean | undefined = supportDefaultIntrinsicSize_buf
        let value : EmbedOptions = ({supportDefaultIntrinsicSize: supportDefaultIntrinsicSize_result} as EmbedOptions)
        return value
    }
}
export class FirstMeaningfulPaint_serializer {
    public static write(buffer: SerializerBase, value: FirstMeaningfulPaint): void {
        let valueSerializer : SerializerBase = buffer
        const value_navigationStartTime  = value.navigationStartTime
        let value_navigationStartTime_type : int32 = RuntimeType.UNDEFINED
        value_navigationStartTime_type = runtimeType(value_navigationStartTime)
        valueSerializer.writeInt8((value_navigationStartTime_type).toChar())
        if ((value_navigationStartTime_type) != (RuntimeType.UNDEFINED)) {
            const value_navigationStartTime_value  = value_navigationStartTime!
            valueSerializer.writeInt64(value_navigationStartTime_value)
        }
        const value_firstMeaningfulPaintTime  = value.firstMeaningfulPaintTime
        let value_firstMeaningfulPaintTime_type : int32 = RuntimeType.UNDEFINED
        value_firstMeaningfulPaintTime_type = runtimeType(value_firstMeaningfulPaintTime)
        valueSerializer.writeInt8((value_firstMeaningfulPaintTime_type).toChar())
        if ((value_firstMeaningfulPaintTime_type) != (RuntimeType.UNDEFINED)) {
            const value_firstMeaningfulPaintTime_value  = value_firstMeaningfulPaintTime!
            valueSerializer.writeInt64(value_firstMeaningfulPaintTime_value)
        }
    }
    public static read(buffer: DeserializerBase): FirstMeaningfulPaint {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navigationStartTime_buf : int64 | undefined
        if ((navigationStartTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            navigationStartTime_buf = valueDeserializer.readInt64()
        }
        const navigationStartTime_result : int64 | undefined = navigationStartTime_buf
        const firstMeaningfulPaintTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let firstMeaningfulPaintTime_buf : int64 | undefined
        if ((firstMeaningfulPaintTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            firstMeaningfulPaintTime_buf = valueDeserializer.readInt64()
        }
        const firstMeaningfulPaintTime_result : int64 | undefined = firstMeaningfulPaintTime_buf
        let value : FirstMeaningfulPaint = ({navigationStartTime: navigationStartTime_result, firstMeaningfulPaintTime: firstMeaningfulPaintTime_result} as FirstMeaningfulPaint)
        return value
    }
}
export class FullScreenEnterEvent_serializer {
    public static write(buffer: SerializerBase, value: FullScreenEnterEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        FullScreenExitHandler_serializer.write(valueSerializer, value_handler)
        const value_videoWidth  = value.videoWidth
        let value_videoWidth_type : int32 = RuntimeType.UNDEFINED
        value_videoWidth_type = runtimeType(value_videoWidth)
        valueSerializer.writeInt8((value_videoWidth_type).toChar())
        if ((value_videoWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_videoWidth_value  = value_videoWidth!
            valueSerializer.writeNumber(value_videoWidth_value)
        }
        const value_videoHeight  = value.videoHeight
        let value_videoHeight_type : int32 = RuntimeType.UNDEFINED
        value_videoHeight_type = runtimeType(value_videoHeight)
        valueSerializer.writeInt8((value_videoHeight_type).toChar())
        if ((value_videoHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_videoHeight_value  = value_videoHeight!
            valueSerializer.writeNumber(value_videoHeight_value)
        }
    }
    public static read(buffer: DeserializerBase): FullScreenEnterEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : FullScreenExitHandler = (FullScreenExitHandler_serializer.read(valueDeserializer) as FullScreenExitHandler)
        const videoWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let videoWidth_buf : number | undefined
        if ((videoWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            videoWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const videoWidth_result : number | undefined = videoWidth_buf
        const videoHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let videoHeight_buf : number | undefined
        if ((videoHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            videoHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const videoHeight_result : number | undefined = videoHeight_buf
        let value : FullScreenEnterEvent = ({handler: handler_result, videoWidth: videoWidth_result, videoHeight: videoHeight_result} as FullScreenEnterEvent)
        return value
    }
}
export class Header_serializer {
    public static write(buffer: SerializerBase, value: Header): void {
        let valueSerializer : SerializerBase = buffer
        const value_headerKey  = value.headerKey
        valueSerializer.writeString(value_headerKey)
        const value_headerValue  = value.headerValue
        valueSerializer.writeString(value_headerValue)
    }
    public static read(buffer: DeserializerBase): Header {
        let valueDeserializer : DeserializerBase = buffer
        const headerKey_result : string = (valueDeserializer.readString() as string)
        const headerValue_result : string = (valueDeserializer.readString() as string)
        let value : Header = ({headerKey: headerKey_result, headerValue: headerValue_result} as Header)
        return value
    }
}
export class IntelligentTrackingPreventionDetails_serializer {
    public static write(buffer: SerializerBase, value: IntelligentTrackingPreventionDetails): void {
        let valueSerializer : SerializerBase = buffer
        const value_host  = value.host
        valueSerializer.writeString(value_host)
        const value_trackerHost  = value.trackerHost
        valueSerializer.writeString(value_trackerHost)
    }
    public static read(buffer: DeserializerBase): IntelligentTrackingPreventionDetails {
        let valueDeserializer : DeserializerBase = buffer
        const host_result : string = (valueDeserializer.readString() as string)
        const trackerHost_result : string = (valueDeserializer.readString() as string)
        let value : IntelligentTrackingPreventionDetails = ({host: host_result, trackerHost: trackerHost_result} as IntelligentTrackingPreventionDetails)
        return value
    }
}
export class JavaScriptProxy_serializer {
    public static write(buffer: SerializerBase, value: JavaScriptProxy): void {
        let valueSerializer : SerializerBase = buffer
        const value_object_  = value.object_
        valueSerializer.holdAndWriteObject(value_object_)
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_methodList  = value.methodList
        valueSerializer.writeInt32((value_methodList.length).toInt())
        for (let value_methodList_counter_i = 0; value_methodList_counter_i < value_methodList.length; value_methodList_counter_i++) {
            const value_methodList_element : string = value_methodList[value_methodList_counter_i]
            valueSerializer.writeString(value_methodList_element)
        }
        const value_controller  = value.controller
        webview_WebviewController_serializer.write(valueSerializer, value_controller)
        const value_asyncMethodList  = value.asyncMethodList
        let value_asyncMethodList_type : int32 = RuntimeType.UNDEFINED
        value_asyncMethodList_type = runtimeType(value_asyncMethodList)
        valueSerializer.writeInt8((value_asyncMethodList_type).toChar())
        if ((value_asyncMethodList_type) != (RuntimeType.UNDEFINED)) {
            const value_asyncMethodList_value  = value_asyncMethodList!
            valueSerializer.writeInt32((value_asyncMethodList_value.length).toInt())
            for (let value_asyncMethodList_value_counter_i = 0; value_asyncMethodList_value_counter_i < value_asyncMethodList_value.length; value_asyncMethodList_value_counter_i++) {
                const value_asyncMethodList_value_element : string = value_asyncMethodList_value[value_asyncMethodList_value_counter_i]
                valueSerializer.writeString(value_asyncMethodList_value_element)
            }
        }
        const value_permission  = value.permission
        let value_permission_type : int32 = RuntimeType.UNDEFINED
        value_permission_type = runtimeType(value_permission)
        valueSerializer.writeInt8((value_permission_type).toChar())
        if ((value_permission_type) != (RuntimeType.UNDEFINED)) {
            const value_permission_value  = value_permission!
            valueSerializer.writeString(value_permission_value)
        }
    }
    public static read(buffer: DeserializerBase): JavaScriptProxy {
        let valueDeserializer : DeserializerBase = buffer
        const object__result : Object = (valueDeserializer.readObject() as object)
        const name_result : string = (valueDeserializer.readString() as string)
        const methodList_buf_length : int32 = valueDeserializer.readInt32()
        let methodList_buf : Array<string> = new Array<string>(methodList_buf_length)
        for (let methodList_buf_i = 0; methodList_buf_i < methodList_buf_length; methodList_buf_i++) {
            methodList_buf[methodList_buf_i] = (valueDeserializer.readString() as string)
        }
        const methodList_result : Array<string> = methodList_buf
        const controller_result : webview.WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const asyncMethodList_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let asyncMethodList_buf : Array<string> | undefined
        if ((asyncMethodList_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const asyncMethodList_buf__length : int32 = valueDeserializer.readInt32()
            let asyncMethodList_buf_ : Array<string> = new Array<string>(asyncMethodList_buf__length)
            for (let asyncMethodList_buf__i = 0; asyncMethodList_buf__i < asyncMethodList_buf__length; asyncMethodList_buf__i++) {
                asyncMethodList_buf_[asyncMethodList_buf__i] = (valueDeserializer.readString() as string)
            }
            asyncMethodList_buf = asyncMethodList_buf_
        }
        const asyncMethodList_result : Array<string> | undefined = asyncMethodList_buf
        const permission_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let permission_buf : string | undefined
        if ((permission_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            permission_buf = (valueDeserializer.readString() as string)
        }
        const permission_result : string | undefined = permission_buf
        let value : JavaScriptProxy = ({object_: object__result, name: name_result, methodList: methodList_result, controller: controller_result, asyncMethodList: asyncMethodList_result, permission: permission_result} as JavaScriptProxy)
        return value
    }
}
export class LargestContentfulPaint_serializer {
    public static write(buffer: SerializerBase, value: LargestContentfulPaint): void {
        let valueSerializer : SerializerBase = buffer
        const value_navigationStartTime  = value.navigationStartTime
        let value_navigationStartTime_type : int32 = RuntimeType.UNDEFINED
        value_navigationStartTime_type = runtimeType(value_navigationStartTime)
        valueSerializer.writeInt8((value_navigationStartTime_type).toChar())
        if ((value_navigationStartTime_type) != (RuntimeType.UNDEFINED)) {
            const value_navigationStartTime_value  = value_navigationStartTime!
            valueSerializer.writeInt64(value_navigationStartTime_value)
        }
        const value_largestImagePaintTime  = value.largestImagePaintTime
        let value_largestImagePaintTime_type : int32 = RuntimeType.UNDEFINED
        value_largestImagePaintTime_type = runtimeType(value_largestImagePaintTime)
        valueSerializer.writeInt8((value_largestImagePaintTime_type).toChar())
        if ((value_largestImagePaintTime_type) != (RuntimeType.UNDEFINED)) {
            const value_largestImagePaintTime_value  = value_largestImagePaintTime!
            valueSerializer.writeInt64(value_largestImagePaintTime_value)
        }
        const value_largestTextPaintTime  = value.largestTextPaintTime
        let value_largestTextPaintTime_type : int32 = RuntimeType.UNDEFINED
        value_largestTextPaintTime_type = runtimeType(value_largestTextPaintTime)
        valueSerializer.writeInt8((value_largestTextPaintTime_type).toChar())
        if ((value_largestTextPaintTime_type) != (RuntimeType.UNDEFINED)) {
            const value_largestTextPaintTime_value  = value_largestTextPaintTime!
            valueSerializer.writeInt64(value_largestTextPaintTime_value)
        }
        const value_imageBPP  = value.imageBPP
        let value_imageBPP_type : int32 = RuntimeType.UNDEFINED
        value_imageBPP_type = runtimeType(value_imageBPP)
        valueSerializer.writeInt8((value_imageBPP_type).toChar())
        if ((value_imageBPP_type) != (RuntimeType.UNDEFINED)) {
            const value_imageBPP_value  = value_imageBPP!
            valueSerializer.writeFloat64(value_imageBPP_value)
        }
        const value_largestImageLoadStartTime  = value.largestImageLoadStartTime
        let value_largestImageLoadStartTime_type : int32 = RuntimeType.UNDEFINED
        value_largestImageLoadStartTime_type = runtimeType(value_largestImageLoadStartTime)
        valueSerializer.writeInt8((value_largestImageLoadStartTime_type).toChar())
        if ((value_largestImageLoadStartTime_type) != (RuntimeType.UNDEFINED)) {
            const value_largestImageLoadStartTime_value  = value_largestImageLoadStartTime!
            valueSerializer.writeInt64(value_largestImageLoadStartTime_value)
        }
        const value_largestImageLoadEndTime  = value.largestImageLoadEndTime
        let value_largestImageLoadEndTime_type : int32 = RuntimeType.UNDEFINED
        value_largestImageLoadEndTime_type = runtimeType(value_largestImageLoadEndTime)
        valueSerializer.writeInt8((value_largestImageLoadEndTime_type).toChar())
        if ((value_largestImageLoadEndTime_type) != (RuntimeType.UNDEFINED)) {
            const value_largestImageLoadEndTime_value  = value_largestImageLoadEndTime!
            valueSerializer.writeInt64(value_largestImageLoadEndTime_value)
        }
    }
    public static read(buffer: DeserializerBase): LargestContentfulPaint {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navigationStartTime_buf : int64 | undefined
        if ((navigationStartTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            navigationStartTime_buf = valueDeserializer.readInt64()
        }
        const navigationStartTime_result : int64 | undefined = navigationStartTime_buf
        const largestImagePaintTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImagePaintTime_buf : int64 | undefined
        if ((largestImagePaintTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            largestImagePaintTime_buf = valueDeserializer.readInt64()
        }
        const largestImagePaintTime_result : int64 | undefined = largestImagePaintTime_buf
        const largestTextPaintTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestTextPaintTime_buf : int64 | undefined
        if ((largestTextPaintTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            largestTextPaintTime_buf = valueDeserializer.readInt64()
        }
        const largestTextPaintTime_result : int64 | undefined = largestTextPaintTime_buf
        const imageBPP_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageBPP_buf : double | undefined
        if ((imageBPP_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            imageBPP_buf = valueDeserializer.readFloat64()
        }
        const imageBPP_result : double | undefined = imageBPP_buf
        const largestImageLoadStartTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImageLoadStartTime_buf : int64 | undefined
        if ((largestImageLoadStartTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            largestImageLoadStartTime_buf = valueDeserializer.readInt64()
        }
        const largestImageLoadStartTime_result : int64 | undefined = largestImageLoadStartTime_buf
        const largestImageLoadEndTime_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImageLoadEndTime_buf : int64 | undefined
        if ((largestImageLoadEndTime_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            largestImageLoadEndTime_buf = valueDeserializer.readInt64()
        }
        const largestImageLoadEndTime_result : int64 | undefined = largestImageLoadEndTime_buf
        let value : LargestContentfulPaint = ({navigationStartTime: navigationStartTime_result, largestImagePaintTime: largestImagePaintTime_result, largestTextPaintTime: largestTextPaintTime_result, imageBPP: imageBPP_result, largestImageLoadStartTime: largestImageLoadStartTime_result, largestImageLoadEndTime: largestImageLoadEndTime_result} as LargestContentfulPaint)
        return value
    }
}
export class LoadCommittedDetails_serializer {
    public static write(buffer: SerializerBase, value: LoadCommittedDetails): void {
        let valueSerializer : SerializerBase = buffer
        const value_isMainFrame  = value.isMainFrame
        valueSerializer.writeBoolean(value_isMainFrame)
        const value_isSameDocument  = value.isSameDocument
        valueSerializer.writeBoolean(value_isSameDocument)
        const value_didReplaceEntry  = value.didReplaceEntry
        valueSerializer.writeBoolean(value_didReplaceEntry)
        const value_navigationType  = value.navigationType
        valueSerializer.writeInt32(TypeChecker.WebNavigationType_ToNumeric(value_navigationType))
        const value_url  = value.url
        valueSerializer.writeString(value_url)
    }
    public static read(buffer: DeserializerBase): LoadCommittedDetails {
        let valueDeserializer : DeserializerBase = buffer
        const isMainFrame_result : boolean = valueDeserializer.readBoolean()
        const isSameDocument_result : boolean = valueDeserializer.readBoolean()
        const didReplaceEntry_result : boolean = valueDeserializer.readBoolean()
        const navigationType_result : WebNavigationType = TypeChecker.WebNavigationType_FromNumeric(valueDeserializer.readInt32())
        const url_result : string = (valueDeserializer.readString() as string)
        let value : LoadCommittedDetails = ({isMainFrame: isMainFrame_result, isSameDocument: isSameDocument_result, didReplaceEntry: didReplaceEntry_result, navigationType: navigationType_result, url: url_result} as LoadCommittedDetails)
        return value
    }
}
export class NativeEmbedVisibilityInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedVisibilityInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_visibility  = value.visibility
        valueSerializer.writeBoolean(value_visibility)
        const value_embedId  = value.embedId
        valueSerializer.writeString(value_embedId)
    }
    public static read(buffer: DeserializerBase): NativeEmbedVisibilityInfo {
        let valueDeserializer : DeserializerBase = buffer
        const visibility_result : boolean = valueDeserializer.readBoolean()
        const embedId_result : string = (valueDeserializer.readString() as string)
        let value : NativeEmbedVisibilityInfo = ({visibility: visibility_result, embedId: embedId_result} as NativeEmbedVisibilityInfo)
        return value
    }
}
export class NestedScrollOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: NestedScrollOptionsExt): void {
        let valueSerializer : SerializerBase = buffer
        const value_scrollUp  = value.scrollUp
        let value_scrollUp_type : int32 = RuntimeType.UNDEFINED
        value_scrollUp_type = runtimeType(value_scrollUp)
        valueSerializer.writeInt8((value_scrollUp_type).toChar())
        if ((value_scrollUp_type) != (RuntimeType.UNDEFINED)) {
            const value_scrollUp_value  = (value_scrollUp as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(value_scrollUp_value))
        }
        const value_scrollDown  = value.scrollDown
        let value_scrollDown_type : int32 = RuntimeType.UNDEFINED
        value_scrollDown_type = runtimeType(value_scrollDown)
        valueSerializer.writeInt8((value_scrollDown_type).toChar())
        if ((value_scrollDown_type) != (RuntimeType.UNDEFINED)) {
            const value_scrollDown_value  = (value_scrollDown as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(value_scrollDown_value))
        }
        const value_scrollRight  = value.scrollRight
        let value_scrollRight_type : int32 = RuntimeType.UNDEFINED
        value_scrollRight_type = runtimeType(value_scrollRight)
        valueSerializer.writeInt8((value_scrollRight_type).toChar())
        if ((value_scrollRight_type) != (RuntimeType.UNDEFINED)) {
            const value_scrollRight_value  = (value_scrollRight as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(value_scrollRight_value))
        }
        const value_scrollLeft  = value.scrollLeft
        let value_scrollLeft_type : int32 = RuntimeType.UNDEFINED
        value_scrollLeft_type = runtimeType(value_scrollLeft)
        valueSerializer.writeInt8((value_scrollLeft_type).toChar())
        if ((value_scrollLeft_type) != (RuntimeType.UNDEFINED)) {
            const value_scrollLeft_value  = (value_scrollLeft as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(value_scrollLeft_value))
        }
    }
    public static read(buffer: DeserializerBase): NestedScrollOptionsExt {
        let valueDeserializer : DeserializerBase = buffer
        const scrollUp_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollUp_buf : NestedScrollMode | undefined
        if ((scrollUp_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scrollUp_buf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollUp_result : NestedScrollMode | undefined = scrollUp_buf
        const scrollDown_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollDown_buf : NestedScrollMode | undefined
        if ((scrollDown_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scrollDown_buf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollDown_result : NestedScrollMode | undefined = scrollDown_buf
        const scrollRight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollRight_buf : NestedScrollMode | undefined
        if ((scrollRight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scrollRight_buf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollRight_result : NestedScrollMode | undefined = scrollRight_buf
        const scrollLeft_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollLeft_buf : NestedScrollMode | undefined
        if ((scrollLeft_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scrollLeft_buf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollLeft_result : NestedScrollMode | undefined = scrollLeft_buf
        let value : NestedScrollOptionsExt = ({scrollUp: scrollUp_result, scrollDown: scrollDown_result, scrollRight: scrollRight_result, scrollLeft: scrollLeft_result} as NestedScrollOptionsExt)
        return value
    }
}
export class OnAlertEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAlertEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_result  = value.result
        JsResult_serializer.write(valueSerializer, value_result)
    }
    public static read(buffer: DeserializerBase): OnAlertEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const message_result : string = (valueDeserializer.readString() as string)
        const result_result : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnAlertEvent = ({url: url_result, message: message_result, result: result_result} as OnAlertEvent)
        return value
    }
}
export class OnBeforeUnloadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnBeforeUnloadEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_result  = value.result
        JsResult_serializer.write(valueSerializer, value_result)
    }
    public static read(buffer: DeserializerBase): OnBeforeUnloadEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const message_result : string = (valueDeserializer.readString() as string)
        const result_result : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnBeforeUnloadEvent = ({url: url_result, message: message_result, result: result_result} as OnBeforeUnloadEvent)
        return value
    }
}
export class OnClientAuthenticationEvent_serializer {
    public static write(buffer: SerializerBase, value: OnClientAuthenticationEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        ClientAuthenticationHandler_serializer.write(valueSerializer, value_handler)
        const value_host  = value.host
        valueSerializer.writeString(value_host)
        const value_port  = value.port
        valueSerializer.writeNumber(value_port)
        const value_keyTypes  = value.keyTypes
        valueSerializer.writeInt32((value_keyTypes.length).toInt())
        for (let value_keyTypes_counter_i = 0; value_keyTypes_counter_i < value_keyTypes.length; value_keyTypes_counter_i++) {
            const value_keyTypes_element : string = value_keyTypes[value_keyTypes_counter_i]
            valueSerializer.writeString(value_keyTypes_element)
        }
        const value_issuers  = value.issuers
        valueSerializer.writeInt32((value_issuers.length).toInt())
        for (let value_issuers_counter_i = 0; value_issuers_counter_i < value_issuers.length; value_issuers_counter_i++) {
            const value_issuers_element : string = value_issuers[value_issuers_counter_i]
            valueSerializer.writeString(value_issuers_element)
        }
    }
    public static read(buffer: DeserializerBase): OnClientAuthenticationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : ClientAuthenticationHandler = (ClientAuthenticationHandler_serializer.read(valueDeserializer) as ClientAuthenticationHandler)
        const host_result : string = (valueDeserializer.readString() as string)
        const port_result : number = (valueDeserializer.readNumber() as number)
        const keyTypes_buf_length : int32 = valueDeserializer.readInt32()
        let keyTypes_buf : Array<string> = new Array<string>(keyTypes_buf_length)
        for (let keyTypes_buf_i = 0; keyTypes_buf_i < keyTypes_buf_length; keyTypes_buf_i++) {
            keyTypes_buf[keyTypes_buf_i] = (valueDeserializer.readString() as string)
        }
        const keyTypes_result : Array<string> = keyTypes_buf
        const issuers_buf_length : int32 = valueDeserializer.readInt32()
        let issuers_buf : Array<string> = new Array<string>(issuers_buf_length)
        for (let issuers_buf_i = 0; issuers_buf_i < issuers_buf_length; issuers_buf_i++) {
            issuers_buf[issuers_buf_i] = (valueDeserializer.readString() as string)
        }
        const issuers_result : Array<string> = issuers_buf
        let value : OnClientAuthenticationEvent = ({handler: handler_result, host: host_result, port: port_result, keyTypes: keyTypes_result, issuers: issuers_result} as OnClientAuthenticationEvent)
        return value
    }
}
export class OnConfirmEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConfirmEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_result  = value.result
        JsResult_serializer.write(valueSerializer, value_result)
    }
    public static read(buffer: DeserializerBase): OnConfirmEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const message_result : string = (valueDeserializer.readString() as string)
        const result_result : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnConfirmEvent = ({url: url_result, message: message_result, result: result_result} as OnConfirmEvent)
        return value
    }
}
export class OnContextMenuShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnContextMenuShowEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_param  = value.param
        WebContextMenuParam_serializer.write(valueSerializer, value_param)
        const value_result  = value.result
        WebContextMenuResult_serializer.write(valueSerializer, value_result)
    }
    public static read(buffer: DeserializerBase): OnContextMenuShowEvent {
        let valueDeserializer : DeserializerBase = buffer
        const param_result : WebContextMenuParam = (WebContextMenuParam_serializer.read(valueDeserializer) as WebContextMenuParam)
        const result_result : WebContextMenuResult = (WebContextMenuResult_serializer.read(valueDeserializer) as WebContextMenuResult)
        let value : OnContextMenuShowEvent = ({param: param_result, result: result_result} as OnContextMenuShowEvent)
        return value
    }
}
export class OnDownloadStartEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDownloadStartEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_userAgent  = value.userAgent
        valueSerializer.writeString(value_userAgent)
        const value_contentDisposition  = value.contentDisposition
        valueSerializer.writeString(value_contentDisposition)
        const value_mimetype  = value.mimetype
        valueSerializer.writeString(value_mimetype)
        const value_contentLength  = value.contentLength
        valueSerializer.writeNumber(value_contentLength)
    }
    public static read(buffer: DeserializerBase): OnDownloadStartEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const userAgent_result : string = (valueDeserializer.readString() as string)
        const contentDisposition_result : string = (valueDeserializer.readString() as string)
        const mimetype_result : string = (valueDeserializer.readString() as string)
        const contentLength_result : number = (valueDeserializer.readNumber() as number)
        let value : OnDownloadStartEvent = ({url: url_result, userAgent: userAgent_result, contentDisposition: contentDisposition_result, mimetype: mimetype_result, contentLength: contentLength_result} as OnDownloadStartEvent)
        return value
    }
}
export class OnErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnErrorReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_request  = value.request
        WebResourceRequest_serializer.write(valueSerializer, value_request)
        const value_error  = value.error
        WebResourceError_serializer.write(valueSerializer, value_error)
    }
    public static read(buffer: DeserializerBase): OnErrorReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const request_result : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const error_result : WebResourceError = (WebResourceError_serializer.read(valueDeserializer) as WebResourceError)
        let value : OnErrorReceiveEvent = ({request: request_result, error: error_result} as OnErrorReceiveEvent)
        return value
    }
}
export class OnGeolocationShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnGeolocationShowEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_origin  = value.origin
        valueSerializer.writeString(value_origin)
        const value_geolocation  = value.geolocation
        JsGeolocation_serializer.write(valueSerializer, value_geolocation)
    }
    public static read(buffer: DeserializerBase): OnGeolocationShowEvent {
        let valueDeserializer : DeserializerBase = buffer
        const origin_result : string = (valueDeserializer.readString() as string)
        const geolocation_result : JsGeolocation = (JsGeolocation_serializer.read(valueDeserializer) as JsGeolocation)
        let value : OnGeolocationShowEvent = ({origin: origin_result, geolocation: geolocation_result} as OnGeolocationShowEvent)
        return value
    }
}
export class OnHttpAuthRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpAuthRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        HttpAuthHandler_serializer.write(valueSerializer, value_handler)
        const value_host  = value.host
        valueSerializer.writeString(value_host)
        const value_realm  = value.realm
        valueSerializer.writeString(value_realm)
    }
    public static read(buffer: DeserializerBase): OnHttpAuthRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : HttpAuthHandler = (HttpAuthHandler_serializer.read(valueDeserializer) as HttpAuthHandler)
        const host_result : string = (valueDeserializer.readString() as string)
        const realm_result : string = (valueDeserializer.readString() as string)
        let value : OnHttpAuthRequestEvent = ({handler: handler_result, host: host_result, realm: realm_result} as OnHttpAuthRequestEvent)
        return value
    }
}
export class OnHttpErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpErrorReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_request  = value.request
        WebResourceRequest_serializer.write(valueSerializer, value_request)
        const value_response  = value.response
        WebResourceResponse_serializer.write(valueSerializer, value_response)
    }
    public static read(buffer: DeserializerBase): OnHttpErrorReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const request_result : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const response_result : WebResourceResponse = (WebResourceResponse_serializer.read(valueDeserializer) as WebResourceResponse)
        let value : OnHttpErrorReceiveEvent = ({request: request_result, response: response_result} as OnHttpErrorReceiveEvent)
        return value
    }
}
export class OnInterceptRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnInterceptRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_request  = value.request
        WebResourceRequest_serializer.write(valueSerializer, value_request)
    }
    public static read(buffer: DeserializerBase): OnInterceptRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const request_result : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value : OnInterceptRequestEvent = ({request: request_result} as OnInterceptRequestEvent)
        return value
    }
}
export class OnLoadInterceptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnLoadInterceptEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_data  = value.data
        WebResourceRequest_serializer.write(valueSerializer, value_data)
    }
    public static read(buffer: DeserializerBase): OnLoadInterceptEvent {
        let valueDeserializer : DeserializerBase = buffer
        const data_result : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value : OnLoadInterceptEvent = ({data: data_result} as OnLoadInterceptEvent)
        return value
    }
}
export class OnPageBeginEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageBeginEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
    }
    public static read(buffer: DeserializerBase): OnPageBeginEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        let value : OnPageBeginEvent = ({url: url_result} as OnPageBeginEvent)
        return value
    }
}
export class OnPageEndEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageEndEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
    }
    public static read(buffer: DeserializerBase): OnPageEndEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        let value : OnPageEndEvent = ({url: url_result} as OnPageEndEvent)
        return value
    }
}
export class OnPageVisibleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageVisibleEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
    }
    public static read(buffer: DeserializerBase): OnPageVisibleEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        let value : OnPageVisibleEvent = ({url: url_result} as OnPageVisibleEvent)
        return value
    }
}
export class OnPermissionRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPermissionRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_request  = value.request
        PermissionRequest_serializer.write(valueSerializer, value_request)
    }
    public static read(buffer: DeserializerBase): OnPermissionRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const request_result : PermissionRequest = (PermissionRequest_serializer.read(valueDeserializer) as PermissionRequest)
        let value : OnPermissionRequestEvent = ({request: request_result} as OnPermissionRequestEvent)
        return value
    }
}
export class OnPromptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPromptEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_value  = value.value
        valueSerializer.writeString(value_value)
        const value_result  = value.result
        JsResult_serializer.write(valueSerializer, value_result)
    }
    public static read(buffer: DeserializerBase): OnPromptEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const message_result : string = (valueDeserializer.readString() as string)
        const value_result : string = (valueDeserializer.readString() as string)
        const result_result : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnPromptEvent = ({url: url_result, message: message_result, value: value_result, result: result_result} as OnPromptEvent)
        return value
    }
}
export class OnRefreshAccessedHistoryEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRefreshAccessedHistoryEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_isRefreshed  = value.isRefreshed
        valueSerializer.writeBoolean(value_isRefreshed)
    }
    public static read(buffer: DeserializerBase): OnRefreshAccessedHistoryEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const isRefreshed_result : boolean = valueDeserializer.readBoolean()
        let value : OnRefreshAccessedHistoryEvent = ({url: url_result, isRefreshed: isRefreshed_result} as OnRefreshAccessedHistoryEvent)
        return value
    }
}
export class OnRenderExitedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRenderExitedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_renderExitReason  = value.renderExitReason
        valueSerializer.writeInt32(TypeChecker.RenderExitReason_ToNumeric(value_renderExitReason))
    }
    public static read(buffer: DeserializerBase): OnRenderExitedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const renderExitReason_result : RenderExitReason = TypeChecker.RenderExitReason_FromNumeric(valueDeserializer.readInt32())
        let value : OnRenderExitedEvent = ({renderExitReason: renderExitReason_result} as OnRenderExitedEvent)
        return value
    }
}
export class OnResourceLoadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnResourceLoadEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
    }
    public static read(buffer: DeserializerBase): OnResourceLoadEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        let value : OnResourceLoadEvent = ({url: url_result} as OnResourceLoadEvent)
        return value
    }
}
export class OnScreenCaptureRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScreenCaptureRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        ScreenCaptureHandler_serializer.write(valueSerializer, value_handler)
    }
    public static read(buffer: DeserializerBase): OnScreenCaptureRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : ScreenCaptureHandler = (ScreenCaptureHandler_serializer.read(valueDeserializer) as ScreenCaptureHandler)
        let value : OnScreenCaptureRequestEvent = ({handler: handler_result} as OnScreenCaptureRequestEvent)
        return value
    }
}
export class OnSslErrorEventReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSslErrorEventReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        SslErrorHandler_serializer.write(valueSerializer, value_handler)
        const value_error  = value.error
        valueSerializer.writeInt32(TypeChecker.SslError_ToNumeric(value_error))
        const value_certChainData  = value.certChainData
        let value_certChainData_type : int32 = RuntimeType.UNDEFINED
        value_certChainData_type = runtimeType(value_certChainData)
        valueSerializer.writeInt8((value_certChainData_type).toChar())
        if ((value_certChainData_type) != (RuntimeType.UNDEFINED)) {
            const value_certChainData_value  = value_certChainData!
            valueSerializer.writeInt32((value_certChainData_value.length).toInt())
            for (let value_certChainData_value_counter_i = 0; value_certChainData_value_counter_i < value_certChainData_value.length; value_certChainData_value_counter_i++) {
                const value_certChainData_value_element : NativeBuffer = value_certChainData_value[value_certChainData_value_counter_i]
                valueSerializer.writeBuffer(value_certChainData_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): OnSslErrorEventReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const error_result : SslError = TypeChecker.SslError_FromNumeric(valueDeserializer.readInt32())
        const certChainData_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let certChainData_buf : Array<NativeBuffer> | undefined
        if ((certChainData_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const certChainData_buf__length : int32 = valueDeserializer.readInt32()
            let certChainData_buf_ : Array<NativeBuffer> = new Array<NativeBuffer>(certChainData_buf__length)
            for (let certChainData_buf__i = 0; certChainData_buf__i < certChainData_buf__length; certChainData_buf__i++) {
                certChainData_buf_[certChainData_buf__i] = (valueDeserializer.readBuffer() as NativeBuffer)
            }
            certChainData_buf = certChainData_buf_
        }
        const certChainData_result : Array<NativeBuffer> | undefined = certChainData_buf
        let value : OnSslErrorEventReceiveEvent = ({handler: handler_result, error: error_result, certChainData: certChainData_result} as OnSslErrorEventReceiveEvent)
        return value
    }
}
export class OnTitleReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTitleReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_title  = value.title
        valueSerializer.writeString(value_title)
    }
    public static read(buffer: DeserializerBase): OnTitleReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const title_result : string = (valueDeserializer.readString() as string)
        let value : OnTitleReceiveEvent = ({title: title_result} as OnTitleReceiveEvent)
        return value
    }
}
export class OnTouchIconUrlReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTouchIconUrlReceivedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_precomposed  = value.precomposed
        valueSerializer.writeBoolean(value_precomposed)
    }
    public static read(buffer: DeserializerBase): OnTouchIconUrlReceivedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const url_result : string = (valueDeserializer.readString() as string)
        const precomposed_result : boolean = valueDeserializer.readBoolean()
        let value : OnTouchIconUrlReceivedEvent = ({url: url_result, precomposed: precomposed_result} as OnTouchIconUrlReceivedEvent)
        return value
    }
}
export class OnWindowNewEvent_serializer {
    public static write(buffer: SerializerBase, value: OnWindowNewEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_isAlert  = value.isAlert
        valueSerializer.writeBoolean(value_isAlert)
        const value_isUserTrigger  = value.isUserTrigger
        valueSerializer.writeBoolean(value_isUserTrigger)
        const value_targetUrl  = value.targetUrl
        valueSerializer.writeString(value_targetUrl)
        const value_handler  = value.handler
        ControllerHandler_serializer.write(valueSerializer, value_handler)
    }
    public static read(buffer: DeserializerBase): OnWindowNewEvent {
        let valueDeserializer : DeserializerBase = buffer
        const isAlert_result : boolean = valueDeserializer.readBoolean()
        const isUserTrigger_result : boolean = valueDeserializer.readBoolean()
        const targetUrl_result : string = (valueDeserializer.readString() as string)
        const handler_result : ControllerHandler = (ControllerHandler_serializer.read(valueDeserializer) as ControllerHandler)
        let value : OnWindowNewEvent = ({isAlert: isAlert_result, isUserTrigger: isUserTrigger_result, targetUrl: targetUrl_result, handler: handler_result} as OnWindowNewEvent)
        return value
    }
}
export class RenderProcessNotRespondingData_serializer {
    public static write(buffer: SerializerBase, value: RenderProcessNotRespondingData): void {
        let valueSerializer : SerializerBase = buffer
        const value_jsStack  = value.jsStack
        valueSerializer.writeString(value_jsStack)
        const value_pid  = value.pid
        valueSerializer.writeInt32(value_pid)
        const value_reason  = value.reason
        valueSerializer.writeInt32(TypeChecker.RenderProcessNotRespondingReason_ToNumeric(value_reason))
    }
    public static read(buffer: DeserializerBase): RenderProcessNotRespondingData {
        let valueDeserializer : DeserializerBase = buffer
        const jsStack_result : string = (valueDeserializer.readString() as string)
        const pid_result : int32 = valueDeserializer.readInt32()
        const reason_result : RenderProcessNotRespondingReason = TypeChecker.RenderProcessNotRespondingReason_FromNumeric(valueDeserializer.readInt32())
        let value : RenderProcessNotRespondingData = ({jsStack: jsStack_result, pid: pid_result, reason: reason_result} as RenderProcessNotRespondingData)
        return value
    }
}
export class ScreenCaptureConfig_serializer {
    public static write(buffer: SerializerBase, value: ScreenCaptureConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_captureMode  = value.captureMode
        valueSerializer.writeInt32(TypeChecker.WebCaptureMode_ToNumeric(value_captureMode))
    }
    public static read(buffer: DeserializerBase): ScreenCaptureConfig {
        let valueDeserializer : DeserializerBase = buffer
        const captureMode_result : WebCaptureMode = TypeChecker.WebCaptureMode_FromNumeric(valueDeserializer.readInt32())
        let value : ScreenCaptureConfig = ({captureMode: captureMode_result} as ScreenCaptureConfig)
        return value
    }
}
export class ScriptItem_serializer {
    public static write(buffer: SerializerBase, value: ScriptItem): void {
        let valueSerializer : SerializerBase = buffer
        const value_script  = value.script
        valueSerializer.writeString(value_script)
        const value_scriptRules  = value.scriptRules
        valueSerializer.writeInt32((value_scriptRules.length).toInt())
        for (let value_scriptRules_counter_i = 0; value_scriptRules_counter_i < value_scriptRules.length; value_scriptRules_counter_i++) {
            const value_scriptRules_element : string = value_scriptRules[value_scriptRules_counter_i]
            valueSerializer.writeString(value_scriptRules_element)
        }
    }
    public static read(buffer: DeserializerBase): ScriptItem {
        let valueDeserializer : DeserializerBase = buffer
        const script_result : string = (valueDeserializer.readString() as string)
        const scriptRules_buf_length : int32 = valueDeserializer.readInt32()
        let scriptRules_buf : Array<string> = new Array<string>(scriptRules_buf_length)
        for (let scriptRules_buf_i = 0; scriptRules_buf_i < scriptRules_buf_length; scriptRules_buf_i++) {
            scriptRules_buf[scriptRules_buf_i] = (valueDeserializer.readString() as string)
        }
        const scriptRules_result : Array<string> = scriptRules_buf
        let value : ScriptItem = ({script: script_result, scriptRules: scriptRules_result} as ScriptItem)
        return value
    }
}
export class SelectionMenuOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: SelectionMenuOptionsExt): void {
        let valueSerializer : SerializerBase = buffer
        const value_onAppear  = value.onAppear
        let value_onAppear_type : int32 = RuntimeType.UNDEFINED
        value_onAppear_type = runtimeType(value_onAppear)
        valueSerializer.writeInt8((value_onAppear_type).toChar())
        if ((value_onAppear_type) != (RuntimeType.UNDEFINED)) {
            const value_onAppear_value  = value_onAppear!
            valueSerializer.holdAndWriteCallback(value_onAppear_value)
        }
        const value_onDisappear  = value.onDisappear
        let value_onDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onDisappear_type = runtimeType(value_onDisappear)
        valueSerializer.writeInt8((value_onDisappear_type).toChar())
        if ((value_onDisappear_type) != (RuntimeType.UNDEFINED)) {
            const value_onDisappear_value  = value_onDisappear!
            valueSerializer.holdAndWriteCallback(value_onDisappear_value)
        }
        const value_preview  = value.preview
        let value_preview_type : int32 = RuntimeType.UNDEFINED
        value_preview_type = runtimeType(value_preview)
        valueSerializer.writeInt8((value_preview_type).toChar())
        if ((value_preview_type) != (RuntimeType.UNDEFINED)) {
            const value_preview_value  = value_preview!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_preview_value))
        }
        const value_menuType  = value.menuType
        let value_menuType_type : int32 = RuntimeType.UNDEFINED
        value_menuType_type = runtimeType(value_menuType)
        valueSerializer.writeInt8((value_menuType_type).toChar())
        if ((value_menuType_type) != (RuntimeType.UNDEFINED)) {
            const value_menuType_value  = (value_menuType as MenuType)
            valueSerializer.writeInt32(TypeChecker.MenuType_ToNumeric(value_menuType_value))
        }
    }
    public static read(buffer: DeserializerBase): SelectionMenuOptionsExt {
        let valueDeserializer : DeserializerBase = buffer
        const onAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAppear_buf : (() => void) | undefined
        if ((onAppear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onAppear_buf = ():void => { 
    const onAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onAppear_buf__argsSerializer.writeInt32(onAppear_buf__resource.resourceId);
    onAppear_buf__argsSerializer.writePointer(onAppear_buf__call);
    onAppear_buf__argsSerializer.writePointer(onAppear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onAppear_buf__argsSerializer.asBuffer(), onAppear_buf__argsSerializer.length());
    onAppear_buf__argsSerializer.release();
    return; }
        }
        const onAppear_result : (() => void) | undefined = onAppear_buf
        const onDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDisappear_buf : (() => void) | undefined
        if ((onDisappear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDisappear_buf = ():void => { 
    const onDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDisappear_buf__argsSerializer.writeInt32(onDisappear_buf__resource.resourceId);
    onDisappear_buf__argsSerializer.writePointer(onDisappear_buf__call);
    onDisappear_buf__argsSerializer.writePointer(onDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onDisappear_buf__argsSerializer.asBuffer(), onDisappear_buf__argsSerializer.length());
    onDisappear_buf__argsSerializer.release();
    return; }
        }
        const onDisappear_result : (() => void) | undefined = onDisappear_buf
        const preview_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let preview_buf : CustomBuilder | undefined
        if ((preview_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const preview_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const preview_buf__call : KPointer = valueDeserializer.readPointer()
            const preview_buf__callSync : KPointer = valueDeserializer.readPointer()
            preview_buf = ():void => { 
    const preview_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    preview_buf__argsSerializer.writeInt32(preview_buf__resource.resourceId);
    preview_buf__argsSerializer.writePointer(preview_buf__call);
    preview_buf__argsSerializer.writePointer(preview_buf__callSync);
    InteropNativeModule._CallCallback(737226752, preview_buf__argsSerializer.asBuffer(), preview_buf__argsSerializer.length());
    preview_buf__argsSerializer.release();
    return; }
        }
        const preview_result : CustomBuilder | undefined = preview_buf
        const menuType_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let menuType_buf : MenuType | undefined
        if ((menuType_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            menuType_buf = TypeChecker.MenuType_FromNumeric(valueDeserializer.readInt32())
        }
        const menuType_result : MenuType | undefined = menuType_buf
        let value : SelectionMenuOptionsExt = ({onAppear: onAppear_result, onDisappear: onDisappear_result, preview: preview_result, menuType: menuType_result} as SelectionMenuOptionsExt)
        return value
    }
}
export class SslErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: SslErrorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_handler  = value.handler
        SslErrorHandler_serializer.write(valueSerializer, value_handler)
        const value_error  = value.error
        valueSerializer.writeInt32(TypeChecker.SslError_ToNumeric(value_error))
        const value_url  = value.url
        valueSerializer.writeString(value_url)
        const value_originalUrl  = value.originalUrl
        valueSerializer.writeString(value_originalUrl)
        const value_referrer  = value.referrer
        valueSerializer.writeString(value_referrer)
        const value_isFatalError  = value.isFatalError
        valueSerializer.writeBoolean(value_isFatalError)
        const value_isMainFrame  = value.isMainFrame
        valueSerializer.writeBoolean(value_isMainFrame)
    }
    public static read(buffer: DeserializerBase): SslErrorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handler_result : SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const error_result : SslError = TypeChecker.SslError_FromNumeric(valueDeserializer.readInt32())
        const url_result : string = (valueDeserializer.readString() as string)
        const originalUrl_result : string = (valueDeserializer.readString() as string)
        const referrer_result : string = (valueDeserializer.readString() as string)
        const isFatalError_result : boolean = valueDeserializer.readBoolean()
        const isMainFrame_result : boolean = valueDeserializer.readBoolean()
        let value : SslErrorEvent = ({handler: handler_result, error: error_result, url: url_result, originalUrl: originalUrl_result, referrer: referrer_result, isFatalError: isFatalError_result, isMainFrame: isMainFrame_result} as SslErrorEvent)
        return value
    }
}
export class WebKeyboardCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardCallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_controller  = value.controller
        WebKeyboardController_serializer.write(valueSerializer, value_controller)
        const value_attributes  = value.attributes
        valueSerializer.writeInt32((value_attributes.size).toInt())
        for (const pair of value_attributes) {
            const value_attributes_key = pair[0]
            const value_attributes_value = pair[1]
            valueSerializer.writeString(value_attributes_key)
            valueSerializer.writeString(value_attributes_value)
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardCallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const controller_result : WebKeyboardController = (WebKeyboardController_serializer.read(valueDeserializer) as WebKeyboardController)
        const attributes_buf_size : int32 = valueDeserializer.readInt32()
        let attributes_buf : Map<string, string> = new Map<string, string>()
        // TODO: TS map resize
        for (let attributes_buf_i = 0; attributes_buf_i < attributes_buf_size; attributes_buf_i++) {
            const attributes_buf_key : string = (valueDeserializer.readString() as string)
            const attributes_buf_value : string = (valueDeserializer.readString() as string)
            attributes_buf.set(attributes_buf_key, attributes_buf_value)
        }
        const attributes_result : Map<string, string> = attributes_buf
        let value : WebKeyboardCallbackInfo = ({controller: controller_result, attributes: attributes_result} as WebKeyboardCallbackInfo)
        return value
    }
}
export class WebKeyboardOptions_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_useSystemKeyboard  = value.useSystemKeyboard
        valueSerializer.writeBoolean(value_useSystemKeyboard)
        const value_enterKeyType  = value.enterKeyType
        let value_enterKeyType_type : int32 = RuntimeType.UNDEFINED
        value_enterKeyType_type = runtimeType(value_enterKeyType)
        valueSerializer.writeInt8((value_enterKeyType_type).toChar())
        if ((value_enterKeyType_type) != (RuntimeType.UNDEFINED)) {
            const value_enterKeyType_value  = value_enterKeyType!
            valueSerializer.writeInt32(value_enterKeyType_value)
        }
        const value_customKeyboard  = value.customKeyboard
        let value_customKeyboard_type : int32 = RuntimeType.UNDEFINED
        value_customKeyboard_type = runtimeType(value_customKeyboard)
        valueSerializer.writeInt8((value_customKeyboard_type).toChar())
        if ((value_customKeyboard_type) != (RuntimeType.UNDEFINED)) {
            const value_customKeyboard_value  = value_customKeyboard!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_customKeyboard_value))
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardOptions {
        let valueDeserializer : DeserializerBase = buffer
        const useSystemKeyboard_result : boolean = valueDeserializer.readBoolean()
        const enterKeyType_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enterKeyType_buf : int32 | undefined
        if ((enterKeyType_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enterKeyType_buf = valueDeserializer.readInt32()
        }
        const enterKeyType_result : int32 | undefined = enterKeyType_buf
        const customKeyboard_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customKeyboard_buf : CustomBuilder | undefined
        if ((customKeyboard_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const customKeyboard_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const customKeyboard_buf__call : KPointer = valueDeserializer.readPointer()
            const customKeyboard_buf__callSync : KPointer = valueDeserializer.readPointer()
            customKeyboard_buf = ():void => { 
    const customKeyboard_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    customKeyboard_buf__argsSerializer.writeInt32(customKeyboard_buf__resource.resourceId);
    customKeyboard_buf__argsSerializer.writePointer(customKeyboard_buf__call);
    customKeyboard_buf__argsSerializer.writePointer(customKeyboard_buf__callSync);
    InteropNativeModule._CallCallback(737226752, customKeyboard_buf__argsSerializer.asBuffer(), customKeyboard_buf__argsSerializer.length());
    customKeyboard_buf__argsSerializer.release();
    return; }
        }
        const customKeyboard_result : CustomBuilder | undefined = customKeyboard_buf
        let value : WebKeyboardOptions = ({useSystemKeyboard: useSystemKeyboard_result, enterKeyType: enterKeyType_result, customKeyboard: customKeyboard_result} as WebKeyboardOptions)
        return value
    }
}
export class WebMediaOptions_serializer {
    public static write(buffer: SerializerBase, value: WebMediaOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_resumeInterval  = value.resumeInterval
        let value_resumeInterval_type : int32 = RuntimeType.UNDEFINED
        value_resumeInterval_type = runtimeType(value_resumeInterval)
        valueSerializer.writeInt8((value_resumeInterval_type).toChar())
        if ((value_resumeInterval_type) != (RuntimeType.UNDEFINED)) {
            const value_resumeInterval_value  = value_resumeInterval!
            valueSerializer.writeInt32(value_resumeInterval_value)
        }
        const value_audioExclusive  = value.audioExclusive
        let value_audioExclusive_type : int32 = RuntimeType.UNDEFINED
        value_audioExclusive_type = runtimeType(value_audioExclusive)
        valueSerializer.writeInt8((value_audioExclusive_type).toChar())
        if ((value_audioExclusive_type) != (RuntimeType.UNDEFINED)) {
            const value_audioExclusive_value  = value_audioExclusive!
            valueSerializer.writeBoolean(value_audioExclusive_value)
        }
    }
    public static read(buffer: DeserializerBase): WebMediaOptions {
        let valueDeserializer : DeserializerBase = buffer
        const resumeInterval_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let resumeInterval_buf : int32 | undefined
        if ((resumeInterval_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            resumeInterval_buf = valueDeserializer.readInt32()
        }
        const resumeInterval_result : int32 | undefined = resumeInterval_buf
        const audioExclusive_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let audioExclusive_buf : boolean | undefined
        if ((audioExclusive_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            audioExclusive_buf = valueDeserializer.readBoolean()
        }
        const audioExclusive_result : boolean | undefined = audioExclusive_buf
        let value : WebMediaOptions = ({resumeInterval: resumeInterval_result, audioExclusive: audioExclusive_result} as WebMediaOptions)
        return value
    }
}
export class WebOptions_serializer {
    public static write(buffer: SerializerBase, value: WebOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_src  = value.src
        let value_src_type : int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        if (RuntimeType.STRING == value_src_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_src_0  = value_src as string
            valueSerializer.writeString(value_src_0)
        }
        else if (RuntimeType.OBJECT == value_src_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_src_1  = value_src as Resource
            Resource_serializer.write(valueSerializer, value_src_1)
        }
        const value_controller  = value.controller
        webview_WebviewController_serializer.write(valueSerializer, value_controller)
        const value_renderMode  = value.renderMode
        let value_renderMode_type : int32 = RuntimeType.UNDEFINED
        value_renderMode_type = runtimeType(value_renderMode)
        valueSerializer.writeInt8((value_renderMode_type).toChar())
        if ((value_renderMode_type) != (RuntimeType.UNDEFINED)) {
            const value_renderMode_value  = (value_renderMode as RenderMode)
            valueSerializer.writeInt32(TypeChecker.RenderMode_ToNumeric(value_renderMode_value))
        }
        const value_incognitoMode  = value.incognitoMode
        let value_incognitoMode_type : int32 = RuntimeType.UNDEFINED
        value_incognitoMode_type = runtimeType(value_incognitoMode)
        valueSerializer.writeInt8((value_incognitoMode_type).toChar())
        if ((value_incognitoMode_type) != (RuntimeType.UNDEFINED)) {
            const value_incognitoMode_value  = value_incognitoMode!
            valueSerializer.writeBoolean(value_incognitoMode_value)
        }
        const value_sharedRenderProcessToken  = value.sharedRenderProcessToken
        let value_sharedRenderProcessToken_type : int32 = RuntimeType.UNDEFINED
        value_sharedRenderProcessToken_type = runtimeType(value_sharedRenderProcessToken)
        valueSerializer.writeInt8((value_sharedRenderProcessToken_type).toChar())
        if ((value_sharedRenderProcessToken_type) != (RuntimeType.UNDEFINED)) {
            const value_sharedRenderProcessToken_value  = value_sharedRenderProcessToken!
            valueSerializer.writeString(value_sharedRenderProcessToken_value)
        }
    }
    public static read(buffer: DeserializerBase): WebOptions {
        let valueDeserializer : DeserializerBase = buffer
        const src_buf_selector : int32 = valueDeserializer.readInt8()
        let src_buf : string | Resource | undefined
        if (src_buf_selector == (0).toChar()) {
            src_buf = (valueDeserializer.readString() as string)
        }
        else if (src_buf_selector == (1).toChar()) {
            src_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for src_buf has to be chosen through deserialisation.")
        }
        const src_result : string | Resource = (src_buf as string | Resource)
        const controller_result : webview.WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const renderMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let renderMode_buf : RenderMode | undefined
        if ((renderMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            renderMode_buf = TypeChecker.RenderMode_FromNumeric(valueDeserializer.readInt32())
        }
        const renderMode_result : RenderMode | undefined = renderMode_buf
        const incognitoMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let incognitoMode_buf : boolean | undefined
        if ((incognitoMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            incognitoMode_buf = valueDeserializer.readBoolean()
        }
        const incognitoMode_result : boolean | undefined = incognitoMode_buf
        const sharedRenderProcessToken_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sharedRenderProcessToken_buf : string | undefined
        if ((sharedRenderProcessToken_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            sharedRenderProcessToken_buf = (valueDeserializer.readString() as string)
        }
        const sharedRenderProcessToken_result : string | undefined = sharedRenderProcessToken_buf
        let value : WebOptions = ({src: src_result, controller: controller_result, renderMode: renderMode_result, incognitoMode: incognitoMode_result, sharedRenderProcessToken: sharedRenderProcessToken_result} as WebOptions)
        return value
    }
}
export class NativeEmbedInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        let value_id_type : int32 = RuntimeType.UNDEFINED
        value_id_type = runtimeType(value_id)
        valueSerializer.writeInt8((value_id_type).toChar())
        if ((value_id_type) != (RuntimeType.UNDEFINED)) {
            const value_id_value  = value_id!
            valueSerializer.writeString(value_id_value)
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = value_type!
            valueSerializer.writeString(value_type_value)
        }
        const value_src  = value.src
        let value_src_type : int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        valueSerializer.writeInt8((value_src_type).toChar())
        if ((value_src_type) != (RuntimeType.UNDEFINED)) {
            const value_src_value  = value_src!
            valueSerializer.writeString(value_src_value)
        }
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8((value_position_type).toChar())
        if ((value_position_type) != (RuntimeType.UNDEFINED)) {
            const value_position_value  = value_position!
            Position_serializer.write(valueSerializer, value_position_value)
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            valueSerializer.writeInt32(value_width_value)
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            valueSerializer.writeInt32(value_height_value)
        }
        const value_url  = value.url
        let value_url_type : int32 = RuntimeType.UNDEFINED
        value_url_type = runtimeType(value_url)
        valueSerializer.writeInt8((value_url_type).toChar())
        if ((value_url_type) != (RuntimeType.UNDEFINED)) {
            const value_url_value  = value_url!
            valueSerializer.writeString(value_url_value)
        }
        const value_tag  = value.tag
        let value_tag_type : int32 = RuntimeType.UNDEFINED
        value_tag_type = runtimeType(value_tag)
        valueSerializer.writeInt8((value_tag_type).toChar())
        if ((value_tag_type) != (RuntimeType.UNDEFINED)) {
            const value_tag_value  = value_tag!
            valueSerializer.writeString(value_tag_value)
        }
        const value_params  = value.params
        let value_params_type : int32 = RuntimeType.UNDEFINED
        value_params_type = runtimeType(value_params)
        valueSerializer.writeInt8((value_params_type).toChar())
        if ((value_params_type) != (RuntimeType.UNDEFINED)) {
            const value_params_value  = value_params!
            valueSerializer.writeInt32((value_params_value.size).toInt())
            for (const pair of value_params_value) {
                const value_params_value_key = pair[0]
                const value_params_value_value = pair[1]
                valueSerializer.writeString(value_params_value_key)
                valueSerializer.writeString(value_params_value_value)
            }
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let id_buf : string | undefined
        if ((id_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            id_buf = (valueDeserializer.readString() as string)
        }
        const id_result : string | undefined = id_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : string | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = (valueDeserializer.readString() as string)
        }
        const type_result : string | undefined = type_buf
        const src_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let src_buf : string | undefined
        if ((src_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            src_buf = (valueDeserializer.readString() as string)
        }
        const src_result : string | undefined = src_buf
        const position_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let position_buf : Position | undefined
        if ((position_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            position_buf = Position_serializer.read(valueDeserializer)
        }
        const position_result : Position | undefined = position_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : int32 | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            width_buf = valueDeserializer.readInt32()
        }
        const width_result : int32 | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : int32 | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            height_buf = valueDeserializer.readInt32()
        }
        const height_result : int32 | undefined = height_buf
        const url_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let url_buf : string | undefined
        if ((url_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            url_buf = (valueDeserializer.readString() as string)
        }
        const url_result : string | undefined = url_buf
        const tag_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let tag_buf : string | undefined
        if ((tag_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            tag_buf = (valueDeserializer.readString() as string)
        }
        const tag_result : string | undefined = tag_buf
        const params_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let params_buf : Map<string, string> | undefined
        if ((params_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const params_buf__size : int32 = valueDeserializer.readInt32()
            let params_buf_ : Map<string, string> = new Map<string, string>()
            // TODO: TS map resize
            for (let params_buf__i = 0; params_buf__i < params_buf__size; params_buf__i++) {
                const params_buf__key : string = (valueDeserializer.readString() as string)
                const params_buf__value : string = (valueDeserializer.readString() as string)
                params_buf_.set(params_buf__key, params_buf__value)
            }
            params_buf = params_buf_
        }
        const params_result : Map<string, string> | undefined = params_buf
        let value : NativeEmbedInfo = ({id: id_result, type: type_result, src: src_result, position: position_result, width: width_result, height: height_result, url: url_result, tag: tag_result, params: params_result} as NativeEmbedInfo)
        return value
    }
}
export class NativeEmbedDataInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedDataInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_status  = value.status
        let value_status_type : int32 = RuntimeType.UNDEFINED
        value_status_type = runtimeType(value_status)
        valueSerializer.writeInt8((value_status_type).toChar())
        if ((value_status_type) != (RuntimeType.UNDEFINED)) {
            const value_status_value  = (value_status as NativeEmbedStatus)
            valueSerializer.writeInt32(TypeChecker.NativeEmbedStatus_ToNumeric(value_status_value))
        }
        const value_surfaceId  = value.surfaceId
        let value_surfaceId_type : int32 = RuntimeType.UNDEFINED
        value_surfaceId_type = runtimeType(value_surfaceId)
        valueSerializer.writeInt8((value_surfaceId_type).toChar())
        if ((value_surfaceId_type) != (RuntimeType.UNDEFINED)) {
            const value_surfaceId_value  = value_surfaceId!
            valueSerializer.writeString(value_surfaceId_value)
        }
        const value_embedId  = value.embedId
        let value_embedId_type : int32 = RuntimeType.UNDEFINED
        value_embedId_type = runtimeType(value_embedId)
        valueSerializer.writeInt8((value_embedId_type).toChar())
        if ((value_embedId_type) != (RuntimeType.UNDEFINED)) {
            const value_embedId_value  = value_embedId!
            valueSerializer.writeString(value_embedId_value)
        }
        const value_info  = value.info
        let value_info_type : int32 = RuntimeType.UNDEFINED
        value_info_type = runtimeType(value_info)
        valueSerializer.writeInt8((value_info_type).toChar())
        if ((value_info_type) != (RuntimeType.UNDEFINED)) {
            const value_info_value  = value_info!
            NativeEmbedInfo_serializer.write(valueSerializer, value_info_value)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedDataInfo {
        let valueDeserializer : DeserializerBase = buffer
        const status_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let status_buf : NativeEmbedStatus | undefined
        if ((status_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            status_buf = TypeChecker.NativeEmbedStatus_FromNumeric(valueDeserializer.readInt32())
        }
        const status_result : NativeEmbedStatus | undefined = status_buf
        const surfaceId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let surfaceId_buf : string | undefined
        if ((surfaceId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            surfaceId_buf = (valueDeserializer.readString() as string)
        }
        const surfaceId_result : string | undefined = surfaceId_buf
        const embedId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let embedId_buf : string | undefined
        if ((embedId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            embedId_buf = (valueDeserializer.readString() as string)
        }
        const embedId_result : string | undefined = embedId_buf
        const info_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let info_buf : NativeEmbedInfo | undefined
        if ((info_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            info_buf = NativeEmbedInfo_serializer.read(valueDeserializer)
        }
        const info_result : NativeEmbedInfo | undefined = info_buf
        let value : NativeEmbedDataInfo = ({status: status_result, surfaceId: surfaceId_result, embedId: embedId_result, info: info_result} as NativeEmbedDataInfo)
        return value
    }
}
export class NativeEmbedTouchInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedTouchInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_embedId  = value.embedId
        let value_embedId_type : int32 = RuntimeType.UNDEFINED
        value_embedId_type = runtimeType(value_embedId)
        valueSerializer.writeInt8((value_embedId_type).toChar())
        if ((value_embedId_type) != (RuntimeType.UNDEFINED)) {
            const value_embedId_value  = value_embedId!
            valueSerializer.writeString(value_embedId_value)
        }
        const value_touchEvent  = value.touchEvent
        let value_touchEvent_type : int32 = RuntimeType.UNDEFINED
        value_touchEvent_type = runtimeType(value_touchEvent)
        valueSerializer.writeInt8((value_touchEvent_type).toChar())
        if ((value_touchEvent_type) != (RuntimeType.UNDEFINED)) {
            const value_touchEvent_value  = value_touchEvent!
            TouchEvent_serializer.write(valueSerializer, value_touchEvent_value)
        }
        const value_result  = value.result
        let value_result_type : int32 = RuntimeType.UNDEFINED
        value_result_type = runtimeType(value_result)
        valueSerializer.writeInt8((value_result_type).toChar())
        if ((value_result_type) != (RuntimeType.UNDEFINED)) {
            const value_result_value  = value_result!
            EventResult_serializer.write(valueSerializer, value_result_value)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedTouchInfo {
        let valueDeserializer : DeserializerBase = buffer
        const embedId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let embedId_buf : string | undefined
        if ((embedId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            embedId_buf = (valueDeserializer.readString() as string)
        }
        const embedId_result : string | undefined = embedId_buf
        const touchEvent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let touchEvent_buf : TouchEvent | undefined
        if ((touchEvent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            touchEvent_buf = (TouchEvent_serializer.read(valueDeserializer) as TouchEvent)
        }
        const touchEvent_result : TouchEvent | undefined = touchEvent_buf
        const result_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let result_buf : EventResult | undefined
        if ((result_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            result_buf = (EventResult_serializer.read(valueDeserializer) as EventResult)
        }
        const result_result : EventResult | undefined = result_buf
        let value : NativeEmbedTouchInfo = ({embedId: embedId_result, touchEvent: touchEvent_result, result: result_result} as NativeEmbedTouchInfo)
        return value
    }
}

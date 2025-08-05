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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { webview, webview_WebviewController_serializer } from "./../generated/ohos.web.webview"
import { Resource_serializer, Resource } from "./../generated/resource"
import { NestedScrollOptions_serializer, ArkCommonMethodPeer, CommonMethod, KeyEvent, NestedScrollOptions, TouchEvent, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, TouchEvent_serializer } from "./common"
import { EditMenuOptions_serializer, EditMenuOptions, MenuType } from "./textCommon"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CopyOptions, NestedScrollMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Position, Position_serializer } from "./units"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
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
        for (let fileListCounterI = 0; fileListCounterI < fileList.length; fileListCounterI++) {
            const fileListTmpElement : string = fileList[fileListCounterI]
            thisSerializer.writeString(fileListTmpElement)
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private grant_serialize(resources: Array<string>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((resources.length).toInt())
        for (let resourcesCounterI = 0; resourcesCounterI < resources.length; resourcesCounterI++) {
            const resourcesTmpElement : string = resources[resourcesCounterI]
            thisSerializer.writeString(resourcesTmpElement)
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = Header_serializer.read(retvalDeserializer)
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
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_UnionSelector : int32 = retvalDeserializer.readInt8()
            let buffer_ : string | number | NativeBuffer | Resource | undefined
            if (buffer_UnionSelector == (0).toChar()) {
                buffer_ = (retvalDeserializer.readString() as string)
            } else if (buffer_UnionSelector == (1).toChar()) {
                buffer_ = (retvalDeserializer.readNumber() as number)
            } else if (buffer_UnionSelector == (2).toChar()) {
                buffer_ = (retvalDeserializer.readBuffer() as NativeBuffer)
            } else if (buffer_UnionSelector == (3).toChar()) {
                buffer_ = Resource_serializer.read(retvalDeserializer)
            } else {
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
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Header> = new Array<Header>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = Header_serializer.read(retvalDeserializer)
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
        if (data instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const dataForIdx0  = data as string
            thisSerializer.writeString(dataForIdx0)
        } else if (data instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const dataForIdx1  = data as number
            thisSerializer.writeNumber(dataForIdx1)
        } else if (data instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const dataForIdx2  = data as Resource
            Resource_serializer.write(thisSerializer, dataForIdx2)
        } else if (data instanceof NativeBuffer) {
            thisSerializer.writeInt8((3).toChar())
            const dataForIdx3  = data as NativeBuffer
            thisSerializer.writeBuffer(dataForIdx3)
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
        for (let headerCounterI = 0; headerCounterI < header.length; headerCounterI++) {
            const headerTmpElement : Header = header[headerCounterI]
            Header_serializer.write(thisSerializer, headerTmpElement)
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
        const _peer  = new ArkWebPeer(_peerPtr, peerId, 'Web', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFileAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setFileAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnlineImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnlineImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDomStorageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDomStorageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMixedModeAttribute(value: MixedMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as MixedMode)
            thisSerializer.writeInt32(TypeChecker.MixedMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMixedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setZoomAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setZoomAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGeolocationAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setGeolocationAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptProxyAttribute(value: JavaScriptProxy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            JavaScriptProxy_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptProxy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCacheModeAttribute(value: CacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CacheMode)
            thisSerializer.writeInt32(TypeChecker.CacheMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCacheMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDarkModeAttribute(value: WebDarkMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as WebDarkMode)
            thisSerializer.writeInt32(TypeChecker.WebDarkMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDarkMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDarkAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDarkAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaOptionsAttribute(value: WebMediaOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            WebMediaOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverviewModeAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverviewModeAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverScrollModeAttribute(value: OverScrollMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as OverScrollMode)
            thisSerializer.writeInt32(TypeChecker.OverScrollMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverScrollMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlurOnKeyboardHideModeAttribute(value: BlurOnKeyboardHideMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BlurOnKeyboardHideMode)
            thisSerializer.writeInt32(TypeChecker.BlurOnKeyboardHideMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlurOnKeyboardHideMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextZoomRatioAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextZoomRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDatabaseAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDatabaseAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialScaleAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setInitialScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMetaViewportAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMetaViewport(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageEndAttribute(value: ((value0: OnPageEndEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageBeginAttribute(value: ((value0: OnPageBeginEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnProgressChangeAttribute(value: ((value0: OnProgressChangeEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnProgressChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTitleReceiveAttribute(value: ((value0: OnTitleReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTitleReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationShowAttribute(value: ((value0: OnGeolocationShowEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestSelectedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRequestSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAlertAttribute(value: ((value0: OnAlertEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAlert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBeforeUnloadAttribute(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnBeforeUnload(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConfirmAttribute(value: ((value0: OnConfirmEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConfirm(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPromptAttribute(value: ((value0: OnPromptEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPrompt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConsoleAttribute(value: ((value0: OnConsoleEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConsole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorReceiveAttribute(value: ((value0: OnErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpErrorReceiveAttribute(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDownloadStartAttribute(value: ((value0: OnDownloadStartEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDownloadStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRefreshAccessedHistoryAttribute(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRefreshAccessedHistory(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderExitedAttribute(value: ((value0: OnRenderExitedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderExited(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnShowFileSelectorAttribute(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnShowFileSelector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnResourceLoadAttribute(value: ((value0: OnResourceLoadEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnResourceLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenEnterAttribute(value: OnFullScreenEnterCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScaleChangeAttribute(value: ((value0: OnScaleChangeEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScaleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpAuthRequestAttribute(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpAuthRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptRequestAttribute(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPermissionRequestAttribute(value: ((value0: OnPermissionRequestEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPermissionRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScreenCaptureRequestAttribute(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScreenCaptureRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuShowAttribute(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuHideAttribute(value: OnContextMenuHideCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaPlayGestureAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaPlayGestureAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSearchResultReceiveAttribute(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSearchResultReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollAttribute(value: ((value0: OnScrollEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventReceiveAttribute(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEventReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventAttribute(value: OnSslErrorEventCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClientAuthenticationRequestAttribute(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnClientAuthenticationRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowNewAttribute(value: ((value0: OnWindowNewEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowNew(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiWindowAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMultiWindowAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyEventAttribute(value: ((event: KeyEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebStandardFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebStandardFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSansSerifFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSansSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFixedFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFixedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFantasyFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFantasyFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebCursiveFontAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebCursiveFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFixedFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFixedFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinLogicalFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinLogicalFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultTextEncodingFormatAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultTextEncodingFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDisplayScrollBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDisplayScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockNetworkAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlockNetwork(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHorizontalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setHorizontalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setVerticalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTouchIconUrlReceivedAttribute(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTouchIconUrlReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFaviconReceivedAttribute(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFaviconReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageVisibleAttribute(value: ((value0: OnPageVisibleEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageVisible(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDataResubmittedAttribute(value: ((value0: OnDataResubmittedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDataResubmitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPinchSmoothAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setPinchSmooth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowWindowOpenMethodAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setAllowWindowOpenMethod(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAudioStateChangedAttribute(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAudioStateChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstContentfulPaintAttribute(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLargestContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadInterceptAttribute(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnControllerAttachedAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnControllerAttached(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverScrollAttribute(value: ((value0: OnOverScrollEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNavigationEntryCommitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutModeAttribute(value: WebLayoutMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as WebLayoutMode)
            thisSerializer.writeInt32(TypeChecker.WebLayoutMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setLayoutMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof NestedScrollOptions) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as NestedScrollOptions
                NestedScrollOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof NestedScrollOptionsExt) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as NestedScrollOptionsExt
                NestedScrollOptionsExt_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeEmbedModeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeEmbedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCopyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverrideUrlLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAutosizingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextAutosizing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            NativeMediaPlayerConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeMediaPlayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessNotResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnViewportFitChangedAttribute(value: OnViewportFitChangedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnViewportFitChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyboardAttachAttribute(value: WebKeyboardCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAdsBlockedAttribute(value: OnAdsBlockedCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAdsBlocked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAvoidModeAttribute(value: WebKeyboardAvoidMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as WebKeyboardAvoidMode)
            thisSerializer.writeInt32(TypeChecker.WebKeyboardAvoidMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setKeyboardAvoidMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            EditMenuOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptimizeParserBudgetAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOptimizeParserBudget(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableFollowSystemFontWeightAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableFollowSystemFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableWebAVSessionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableWebAVSession(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnHeadEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnHeadEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNativeEmbedOptionsAttribute(value: EmbedOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            EmbedOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNativeEmbedOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRegisterNativeEmbedRuleAttribute(tag: string | undefined, type: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (tag !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const tagTmpValue  = tag!
            thisSerializer.writeString(tagTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = type!
            thisSerializer.writeString(typeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRegisterNativeEmbedRule(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (elementType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const elementTypeTmpValue  = (elementType as WebElementType)
            thisSerializer.writeInt32(TypeChecker.WebElementType_ToNumeric(elementTypeTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(contentTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (responseType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTypeTmpValue  = (responseType as WebResponseType)
            thisSerializer.writeInt32(TypeChecker.WebResponseType_ToNumeric(responseTypeTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionMenuOptionsExt_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
    audioSessionType?: AudioSessionType;
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
export enum AudioSessionType {
    AMBIENT = 3
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class WebModifier extends CommonMethodModifier implements WebAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _javaScriptAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptAccess_0_0value?: boolean | undefined
    _fileAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fileAccess_0_0value?: boolean | undefined
    _onlineImageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onlineImageAccess_0_0value?: boolean | undefined
    _domStorageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _domStorageAccess_0_0value?: boolean | undefined
    _imageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _imageAccess_0_0value?: boolean | undefined
    _mixedMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mixedMode_0_0value?: MixedMode | undefined
    _zoomAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _zoomAccess_0_0value?: boolean | undefined
    _geolocationAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _geolocationAccess_0_0value?: boolean | undefined
    _javaScriptProxy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptProxy_0_0value?: JavaScriptProxy | undefined
    _cacheMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cacheMode_0_0value?: CacheMode | undefined
    _darkMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _darkMode_0_0value?: WebDarkMode | undefined
    _forceDarkAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _forceDarkAccess_0_0value?: boolean | undefined
    _mediaOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mediaOptions_0_0value?: WebMediaOptions | undefined
    _overviewModeAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _overviewModeAccess_0_0value?: boolean | undefined
    _overScrollMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _overScrollMode_0_0value?: OverScrollMode | undefined
    _blurOnKeyboardHideMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blurOnKeyboardHideMode_0_0value?: BlurOnKeyboardHideMode | undefined
    _textZoomRatio_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textZoomRatio_0_0value?: int32 | undefined
    _databaseAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _databaseAccess_0_0value?: boolean | undefined
    _initialScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _initialScale_0_0value?: double | undefined
    _metaViewport_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _metaViewport_0_0value?: boolean | undefined
    _onPageEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageEnd_0_0value?: ((value0: OnPageEndEvent) => void) | undefined
    _onPageBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageBegin_0_0value?: ((value0: OnPageBeginEvent) => void) | undefined
    _onProgressChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onProgressChange_0_0value?: ((value0: OnProgressChangeEvent) => void) | undefined
    _onTitleReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTitleReceive_0_0value?: ((value0: OnTitleReceiveEvent) => void) | undefined
    _onGeolocationHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGeolocationHide_0_0value?: (() => void) | undefined
    _onGeolocationShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGeolocationShow_0_0value?: ((value0: OnGeolocationShowEvent) => void) | undefined
    _onRequestSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRequestSelected_0_0value?: (() => void) | undefined
    _onAlert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAlert_0_0value?: ((value0: OnAlertEvent) => boolean) | undefined
    _onBeforeUnload_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBeforeUnload_0_0value?: ((value0: OnBeforeUnloadEvent) => boolean) | undefined
    _onConfirm_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onConfirm_0_0value?: ((value0: OnConfirmEvent) => boolean) | undefined
    _onPrompt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPrompt_0_0value?: ((value0: OnPromptEvent) => boolean) | undefined
    _onConsole_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onConsole_0_0value?: ((value0: OnConsoleEvent) => boolean) | undefined
    _onErrorReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onErrorReceive_0_0value?: ((value0: OnErrorReceiveEvent) => void) | undefined
    _onHttpErrorReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHttpErrorReceive_0_0value?: ((value0: OnHttpErrorReceiveEvent) => void) | undefined
    _onDownloadStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDownloadStart_0_0value?: ((value0: OnDownloadStartEvent) => void) | undefined
    _onRefreshAccessedHistory_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRefreshAccessedHistory_0_0value?: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined
    _onRenderExited_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderExited_0_0value?: ((value0: OnRenderExitedEvent) => void) | undefined
    _onShowFileSelector_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onShowFileSelector_0_0value?: ((value0: OnShowFileSelectorEvent) => boolean) | undefined
    _onResourceLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onResourceLoad_0_0value?: ((value0: OnResourceLoadEvent) => void) | undefined
    _onFullScreenExit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFullScreenExit_0_0value?: (() => void) | undefined
    _onFullScreenEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFullScreenEnter_0_0value?: OnFullScreenEnterCallback | undefined
    _onScaleChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScaleChange_0_0value?: ((value0: OnScaleChangeEvent) => void) | undefined
    _onHttpAuthRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHttpAuthRequest_0_0value?: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined
    _onInterceptRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptRequest_0_0value?: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined
    _onPermissionRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPermissionRequest_0_0value?: ((value0: OnPermissionRequestEvent) => void) | undefined
    _onScreenCaptureRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScreenCaptureRequest_0_0value?: ((value0: OnScreenCaptureRequestEvent) => void) | undefined
    _onContextMenuShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContextMenuShow_0_0value?: ((value0: OnContextMenuShowEvent) => boolean) | undefined
    _onContextMenuHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContextMenuHide_0_0value?: OnContextMenuHideCallback | undefined
    _mediaPlayGestureAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mediaPlayGestureAccess_0_0value?: boolean | undefined
    _onSearchResultReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSearchResultReceive_0_0value?: ((value0: OnSearchResultReceiveEvent) => void) | undefined
    _onScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScroll_0_0value?: ((value0: OnScrollEvent) => void) | undefined
    _onSslErrorEventReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSslErrorEventReceive_0_0value?: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined
    _onSslErrorEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSslErrorEvent_0_0value?: OnSslErrorEventCallback | undefined
    _onClientAuthenticationRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClientAuthenticationRequest_0_0value?: ((value0: OnClientAuthenticationEvent) => void) | undefined
    _onWindowNew_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWindowNew_0_0value?: ((value0: OnWindowNewEvent) => void) | undefined
    _onWindowExit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWindowExit_0_0value?: (() => void) | undefined
    _multiWindowAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiWindowAccess_0_0value?: boolean | undefined
    _onInterceptKeyEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptKeyEvent_0_0value?: ((event: KeyEvent) => boolean) | undefined
    _webStandardFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webStandardFont_0_0value?: string | undefined
    _webSerifFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webSerifFont_0_0value?: string | undefined
    _webSansSerifFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webSansSerifFont_0_0value?: string | undefined
    _webFixedFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webFixedFont_0_0value?: string | undefined
    _webFantasyFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webFantasyFont_0_0value?: string | undefined
    _webCursiveFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webCursiveFont_0_0value?: string | undefined
    _defaultFixedFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultFixedFontSize_0_0value?: int32 | undefined
    _defaultFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultFontSize_0_0value?: int32 | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: int32 | undefined
    _minLogicalFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minLogicalFontSize_0_0value?: int32 | undefined
    _defaultTextEncodingFormat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultTextEncodingFormat_0_0value?: string | undefined
    _forceDisplayScrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _forceDisplayScrollBar_0_0value?: boolean | undefined
    _blockNetwork_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockNetwork_0_0value?: boolean | undefined
    _horizontalScrollBarAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _horizontalScrollBarAccess_0_0value?: boolean | undefined
    _verticalScrollBarAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _verticalScrollBarAccess_0_0value?: boolean | undefined
    _onTouchIconUrlReceived_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTouchIconUrlReceived_0_0value?: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined
    _onFaviconReceived_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFaviconReceived_0_0value?: ((value0: OnFaviconReceivedEvent) => void) | undefined
    _onPageVisible_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageVisible_0_0value?: ((value0: OnPageVisibleEvent) => void) | undefined
    _onDataResubmitted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDataResubmitted_0_0value?: ((value0: OnDataResubmittedEvent) => void) | undefined
    _pinchSmooth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pinchSmooth_0_0value?: boolean | undefined
    _allowWindowOpenMethod_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowWindowOpenMethod_0_0value?: boolean | undefined
    _onAudioStateChanged_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAudioStateChanged_0_0value?: ((value0: OnAudioStateChangedEvent) => void) | undefined
    _onFirstContentfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFirstContentfulPaint_0_0value?: ((value0: OnFirstContentfulPaintEvent) => void) | undefined
    _onFirstMeaningfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFirstMeaningfulPaint_0_0value?: OnFirstMeaningfulPaintCallback | undefined
    _onLargestContentfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLargestContentfulPaint_0_0value?: OnLargestContentfulPaintCallback | undefined
    _onLoadIntercept_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoadIntercept_0_0value?: ((value0: OnLoadInterceptEvent) => boolean) | undefined
    _onControllerAttached_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onControllerAttached_0_0value?: (() => void) | undefined
    _onOverScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onOverScroll_0_0value?: ((value0: OnOverScrollEvent) => void) | undefined
    _onSafeBrowsingCheckResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSafeBrowsingCheckResult_0_0value?: OnSafeBrowsingCheckResultCallback | undefined
    _onNavigationEntryCommitted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNavigationEntryCommitted_0_0value?: OnNavigationEntryCommittedCallback | undefined
    _onIntelligentTrackingPreventionResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onIntelligentTrackingPreventionResult_0_0value?: OnIntelligentTrackingPreventionCallback | undefined
    _javaScriptOnDocumentStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    _javaScriptOnDocumentEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    _layoutMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutMode_0_0value?: WebLayoutMode | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    _enableNativeEmbedMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNativeEmbedMode_0_0value?: boolean | undefined
    _onNativeEmbedLifecycleChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedLifecycleChange_0_0value?: ((event: NativeEmbedDataInfo) => void) | undefined
    _onNativeEmbedVisibilityChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedVisibilityChange_0_0value?: OnNativeEmbedVisibilityChangeCallback | undefined
    _onNativeEmbedGestureEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedGestureEvent_0_0value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    _copyOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOptions_0_0value?: CopyOptions | undefined
    _onOverrideUrlLoading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onOverrideUrlLoading_0_0value?: OnOverrideUrlLoadingCallback | undefined
    _textAutosizing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAutosizing_0_0value?: boolean | undefined
    _enableNativeMediaPlayer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNativeMediaPlayer_0_0value?: NativeMediaPlayerConfig | undefined
    _onRenderProcessNotResponding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderProcessNotResponding_0_0value?: OnRenderProcessNotRespondingCallback | undefined
    _onRenderProcessResponding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderProcessResponding_0_0value?: OnRenderProcessRespondingCallback | undefined
    _onViewportFitChanged_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onViewportFitChanged_0_0value?: OnViewportFitChangedCallback | undefined
    _onInterceptKeyboardAttach_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptKeyboardAttach_0_0value?: WebKeyboardCallback | undefined
    _onAdsBlocked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAdsBlocked_0_0value?: OnAdsBlockedCallback | undefined
    _keyboardAvoidMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAvoidMode_0_0value?: WebKeyboardAvoidMode | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _optimizeParserBudget_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optimizeParserBudget_0_0value?: boolean | undefined
    _enableFollowSystemFontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableFollowSystemFontWeight_0_0value?: boolean | undefined
    _enableWebAVSession_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableWebAVSession_0_0value?: boolean | undefined
    _runJavaScriptOnDocumentStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    _runJavaScriptOnDocumentEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    _runJavaScriptOnHeadEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnHeadEnd_0_0value?: Array<ScriptItem> | undefined
    _nativeEmbedOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nativeEmbedOptions_0_0value?: EmbedOptions | undefined
    _registerNativeEmbedRule_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _registerNativeEmbedRule_0_0value?: string | undefined
    _registerNativeEmbedRule_0_1value?: string | undefined
    _bindSelectionMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSelectionMenu_0_0value?: WebElementType | undefined
    _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    _bindSelectionMenu_0_2value?: WebResponseType | undefined
    _bindSelectionMenu_0_3value?: SelectionMenuOptionsExt | undefined
    applyModifierPatch(peer: ArkWebPeer): void {
        super.applyModifierPatch(peer)
        if (this._javaScriptAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptAccessAttribute((this._javaScriptAccess_0_0value as boolean | undefined));
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fileAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fileAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFileAccessAttribute((this._fileAccess_0_0value as boolean | undefined));
                    this._fileAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fileAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fileAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFileAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onlineImageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onlineImageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnlineImageAccessAttribute((this._onlineImageAccess_0_0value as boolean | undefined));
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnlineImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._domStorageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._domStorageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDomStorageAccessAttribute((this._domStorageAccess_0_0value as boolean | undefined));
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDomStorageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._imageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._imageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImageAccessAttribute((this._imageAccess_0_0value as boolean | undefined));
                    this._imageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._imageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._imageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._mixedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mixedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMixedModeAttribute((this._mixedMode_0_0value as MixedMode | undefined));
                    this._mixedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mixedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mixedMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMixedModeAttribute((undefined as MixedMode | undefined));
                }
            }
        }
        if (this._zoomAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._zoomAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setZoomAccessAttribute((this._zoomAccess_0_0value as boolean | undefined));
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setZoomAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._geolocationAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._geolocationAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGeolocationAccessAttribute((this._geolocationAccess_0_0value as boolean | undefined));
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGeolocationAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._javaScriptProxy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptProxy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptProxyAttribute((this._javaScriptProxy_0_0value as JavaScriptProxy | undefined));
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptProxyAttribute((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (this._cacheMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cacheMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCacheModeAttribute((this._cacheMode_0_0value as CacheMode | undefined));
                    this._cacheMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cacheMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cacheMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCacheModeAttribute((undefined as CacheMode | undefined));
                }
            }
        }
        if (this._darkMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._darkMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDarkModeAttribute((this._darkMode_0_0value as WebDarkMode | undefined));
                    this._darkMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._darkMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._darkMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDarkModeAttribute((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (this._forceDarkAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._forceDarkAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForceDarkAccessAttribute((this._forceDarkAccess_0_0value as boolean | undefined));
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForceDarkAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._mediaOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mediaOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMediaOptionsAttribute((this._mediaOptions_0_0value as WebMediaOptions | undefined));
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMediaOptionsAttribute((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (this._overviewModeAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._overviewModeAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOverviewModeAccessAttribute((this._overviewModeAccess_0_0value as boolean | undefined));
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOverviewModeAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._overScrollMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._overScrollMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOverScrollModeAttribute((this._overScrollMode_0_0value as OverScrollMode | undefined));
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOverScrollModeAttribute((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (this._blurOnKeyboardHideMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blurOnKeyboardHideMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlurOnKeyboardHideModeAttribute((this._blurOnKeyboardHideMode_0_0value as BlurOnKeyboardHideMode | undefined));
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlurOnKeyboardHideModeAttribute((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (this._textZoomRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textZoomRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextZoomRatioAttribute((this._textZoomRatio_0_0value as int32 | undefined));
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextZoomRatioAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._databaseAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._databaseAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDatabaseAccessAttribute((this._databaseAccess_0_0value as boolean | undefined));
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDatabaseAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._initialScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._initialScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInitialScaleAttribute((this._initialScale_0_0value as double | undefined));
                    this._initialScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInitialScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._metaViewport_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._metaViewport_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMetaViewportAttribute((this._metaViewport_0_0value as boolean | undefined));
                    this._metaViewport_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._metaViewport_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._metaViewport_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMetaViewportAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onPageEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageEndAttribute((this._onPageEnd_0_0value as ((value0: OnPageEndEvent) => void) | undefined));
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageEndAttribute((undefined as ((value0: OnPageEndEvent) => void) | undefined));
                }
            }
        }
        if (this._onPageBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageBeginAttribute((this._onPageBegin_0_0value as ((value0: OnPageBeginEvent) => void) | undefined));
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageBeginAttribute((undefined as ((value0: OnPageBeginEvent) => void) | undefined));
                }
            }
        }
        if (this._onProgressChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onProgressChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnProgressChangeAttribute((this._onProgressChange_0_0value as ((value0: OnProgressChangeEvent) => void) | undefined));
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnProgressChangeAttribute((undefined as ((value0: OnProgressChangeEvent) => void) | undefined));
                }
            }
        }
        if (this._onTitleReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTitleReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTitleReceiveAttribute((this._onTitleReceive_0_0value as ((value0: OnTitleReceiveEvent) => void) | undefined));
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTitleReceiveAttribute((undefined as ((value0: OnTitleReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onGeolocationHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGeolocationHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGeolocationHideAttribute((this._onGeolocationHide_0_0value as (() => void) | undefined));
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGeolocationHideAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onGeolocationShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGeolocationShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGeolocationShowAttribute((this._onGeolocationShow_0_0value as ((value0: OnGeolocationShowEvent) => void) | undefined));
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGeolocationShowAttribute((undefined as ((value0: OnGeolocationShowEvent) => void) | undefined));
                }
            }
        }
        if (this._onRequestSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRequestSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRequestSelectedAttribute((this._onRequestSelected_0_0value as (() => void) | undefined));
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRequestSelectedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onAlert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAlert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAlertAttribute((this._onAlert_0_0value as ((value0: OnAlertEvent) => boolean) | undefined));
                    this._onAlert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAlert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAlert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAlertAttribute((undefined as ((value0: OnAlertEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onBeforeUnload_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBeforeUnload_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnBeforeUnloadAttribute((this._onBeforeUnload_0_0value as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnBeforeUnloadAttribute((undefined as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onConfirm_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onConfirm_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnConfirmAttribute((this._onConfirm_0_0value as ((value0: OnConfirmEvent) => boolean) | undefined));
                    this._onConfirm_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onConfirm_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onConfirm_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnConfirmAttribute((undefined as ((value0: OnConfirmEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onPrompt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPrompt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPromptAttribute((this._onPrompt_0_0value as ((value0: OnPromptEvent) => boolean) | undefined));
                    this._onPrompt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPrompt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPrompt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPromptAttribute((undefined as ((value0: OnPromptEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onConsole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onConsole_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnConsoleAttribute((this._onConsole_0_0value as ((value0: OnConsoleEvent) => boolean) | undefined));
                    this._onConsole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onConsole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onConsole_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnConsoleAttribute((undefined as ((value0: OnConsoleEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorReceiveAttribute((this._onErrorReceive_0_0value as ((value0: OnErrorReceiveEvent) => void) | undefined));
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorReceiveAttribute((undefined as ((value0: OnErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onHttpErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHttpErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHttpErrorReceiveAttribute((this._onHttpErrorReceive_0_0value as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHttpErrorReceiveAttribute((undefined as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onDownloadStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDownloadStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDownloadStartAttribute((this._onDownloadStart_0_0value as ((value0: OnDownloadStartEvent) => void) | undefined));
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDownloadStartAttribute((undefined as ((value0: OnDownloadStartEvent) => void) | undefined));
                }
            }
        }
        if (this._onRefreshAccessedHistory_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRefreshAccessedHistory_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRefreshAccessedHistoryAttribute((this._onRefreshAccessedHistory_0_0value as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRefreshAccessedHistoryAttribute((undefined as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                }
            }
        }
        if (this._onRenderExited_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderExited_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderExitedAttribute((this._onRenderExited_0_0value as ((value0: OnRenderExitedEvent) => void) | undefined));
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderExitedAttribute((undefined as ((value0: OnRenderExitedEvent) => void) | undefined));
                }
            }
        }
        if (this._onShowFileSelector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onShowFileSelector_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnShowFileSelectorAttribute((this._onShowFileSelector_0_0value as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnShowFileSelectorAttribute((undefined as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onResourceLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onResourceLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnResourceLoadAttribute((this._onResourceLoad_0_0value as ((value0: OnResourceLoadEvent) => void) | undefined));
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnResourceLoadAttribute((undefined as ((value0: OnResourceLoadEvent) => void) | undefined));
                }
            }
        }
        if (this._onFullScreenExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFullScreenExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFullScreenExitAttribute((this._onFullScreenExit_0_0value as (() => void) | undefined));
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFullScreenExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFullScreenEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFullScreenEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFullScreenEnterAttribute((this._onFullScreenEnter_0_0value as OnFullScreenEnterCallback | undefined));
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFullScreenEnterAttribute((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (this._onScaleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScaleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScaleChangeAttribute((this._onScaleChange_0_0value as ((value0: OnScaleChangeEvent) => void) | undefined));
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScaleChangeAttribute((undefined as ((value0: OnScaleChangeEvent) => void) | undefined));
                }
            }
        }
        if (this._onHttpAuthRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHttpAuthRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHttpAuthRequestAttribute((this._onHttpAuthRequest_0_0value as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHttpAuthRequestAttribute((undefined as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onInterceptRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptRequestAttribute((this._onInterceptRequest_0_0value as ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined));
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptRequestAttribute((undefined as ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined));
                }
            }
        }
        if (this._onPermissionRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPermissionRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPermissionRequestAttribute((this._onPermissionRequest_0_0value as ((value0: OnPermissionRequestEvent) => void) | undefined));
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPermissionRequestAttribute((undefined as ((value0: OnPermissionRequestEvent) => void) | undefined));
                }
            }
        }
        if (this._onScreenCaptureRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScreenCaptureRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScreenCaptureRequestAttribute((this._onScreenCaptureRequest_0_0value as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScreenCaptureRequestAttribute((undefined as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                }
            }
        }
        if (this._onContextMenuShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContextMenuShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContextMenuShowAttribute((this._onContextMenuShow_0_0value as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContextMenuShowAttribute((undefined as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onContextMenuHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContextMenuHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContextMenuHideAttribute((this._onContextMenuHide_0_0value as OnContextMenuHideCallback | undefined));
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContextMenuHideAttribute((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (this._mediaPlayGestureAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mediaPlayGestureAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMediaPlayGestureAccessAttribute((this._mediaPlayGestureAccess_0_0value as boolean | undefined));
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMediaPlayGestureAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onSearchResultReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSearchResultReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSearchResultReceiveAttribute((this._onSearchResultReceive_0_0value as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSearchResultReceiveAttribute((undefined as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollAttribute((this._onScroll_0_0value as ((value0: OnScrollEvent) => void) | undefined));
                    this._onScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollAttribute((undefined as ((value0: OnScrollEvent) => void) | undefined));
                }
            }
        }
        if (this._onSslErrorEventReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSslErrorEventReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSslErrorEventReceiveAttribute((this._onSslErrorEventReceive_0_0value as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSslErrorEventReceiveAttribute((undefined as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onSslErrorEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSslErrorEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSslErrorEventAttribute((this._onSslErrorEvent_0_0value as OnSslErrorEventCallback | undefined));
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSslErrorEventAttribute((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (this._onClientAuthenticationRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClientAuthenticationRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnClientAuthenticationRequestAttribute((this._onClientAuthenticationRequest_0_0value as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnClientAuthenticationRequestAttribute((undefined as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                }
            }
        }
        if (this._onWindowNew_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWindowNew_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWindowNewAttribute((this._onWindowNew_0_0value as ((value0: OnWindowNewEvent) => void) | undefined));
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWindowNewAttribute((undefined as ((value0: OnWindowNewEvent) => void) | undefined));
                }
            }
        }
        if (this._onWindowExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWindowExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWindowExitAttribute((this._onWindowExit_0_0value as (() => void) | undefined));
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWindowExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._multiWindowAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._multiWindowAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMultiWindowAccessAttribute((this._multiWindowAccess_0_0value as boolean | undefined));
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMultiWindowAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onInterceptKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptKeyEventAttribute((this._onInterceptKeyEvent_0_0value as ((event: KeyEvent) => boolean) | undefined));
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptKeyEventAttribute((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (this._webStandardFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webStandardFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebStandardFontAttribute((this._webStandardFont_0_0value as string | undefined));
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebStandardFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebSerifFontAttribute((this._webSerifFont_0_0value as string | undefined));
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webSansSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webSansSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebSansSerifFontAttribute((this._webSansSerifFont_0_0value as string | undefined));
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebSansSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webFixedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webFixedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebFixedFontAttribute((this._webFixedFont_0_0value as string | undefined));
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebFixedFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webFantasyFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webFantasyFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebFantasyFontAttribute((this._webFantasyFont_0_0value as string | undefined));
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebFantasyFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webCursiveFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webCursiveFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebCursiveFontAttribute((this._webCursiveFont_0_0value as string | undefined));
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebCursiveFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._defaultFixedFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultFixedFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultFixedFontSizeAttribute((this._defaultFixedFontSize_0_0value as int32 | undefined));
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultFixedFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._defaultFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultFontSizeAttribute((this._defaultFontSize_0_0value as int32 | undefined));
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as int32 | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._minLogicalFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minLogicalFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinLogicalFontSizeAttribute((this._minLogicalFontSize_0_0value as int32 | undefined));
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinLogicalFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._defaultTextEncodingFormat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultTextEncodingFormat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultTextEncodingFormatAttribute((this._defaultTextEncodingFormat_0_0value as string | undefined));
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultTextEncodingFormatAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._forceDisplayScrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._forceDisplayScrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForceDisplayScrollBarAttribute((this._forceDisplayScrollBar_0_0value as boolean | undefined));
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForceDisplayScrollBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._blockNetwork_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockNetwork_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockNetworkAttribute((this._blockNetwork_0_0value as boolean | undefined));
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockNetworkAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._horizontalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._horizontalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHorizontalScrollBarAccessAttribute((this._horizontalScrollBarAccess_0_0value as boolean | undefined));
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHorizontalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._verticalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._verticalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalScrollBarAccessAttribute((this._verticalScrollBarAccess_0_0value as boolean | undefined));
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onTouchIconUrlReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTouchIconUrlReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTouchIconUrlReceivedAttribute((this._onTouchIconUrlReceived_0_0value as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTouchIconUrlReceivedAttribute((undefined as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                }
            }
        }
        if (this._onFaviconReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFaviconReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFaviconReceivedAttribute((this._onFaviconReceived_0_0value as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFaviconReceivedAttribute((undefined as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                }
            }
        }
        if (this._onPageVisible_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageVisible_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageVisibleAttribute((this._onPageVisible_0_0value as ((value0: OnPageVisibleEvent) => void) | undefined));
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageVisibleAttribute((undefined as ((value0: OnPageVisibleEvent) => void) | undefined));
                }
            }
        }
        if (this._onDataResubmitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDataResubmitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDataResubmittedAttribute((this._onDataResubmitted_0_0value as ((value0: OnDataResubmittedEvent) => void) | undefined));
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDataResubmittedAttribute((undefined as ((value0: OnDataResubmittedEvent) => void) | undefined));
                }
            }
        }
        if (this._pinchSmooth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pinchSmooth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPinchSmoothAttribute((this._pinchSmooth_0_0value as boolean | undefined));
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPinchSmoothAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._allowWindowOpenMethod_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowWindowOpenMethod_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAllowWindowOpenMethodAttribute((this._allowWindowOpenMethod_0_0value as boolean | undefined));
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAllowWindowOpenMethodAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onAudioStateChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAudioStateChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAudioStateChangedAttribute((this._onAudioStateChanged_0_0value as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAudioStateChangedAttribute((undefined as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                }
            }
        }
        if (this._onFirstContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFirstContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFirstContentfulPaintAttribute((this._onFirstContentfulPaint_0_0value as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFirstContentfulPaintAttribute((undefined as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                }
            }
        }
        if (this._onFirstMeaningfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFirstMeaningfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFirstMeaningfulPaintAttribute((this._onFirstMeaningfulPaint_0_0value as OnFirstMeaningfulPaintCallback | undefined));
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFirstMeaningfulPaintAttribute((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (this._onLargestContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLargestContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLargestContentfulPaintAttribute((this._onLargestContentfulPaint_0_0value as OnLargestContentfulPaintCallback | undefined));
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLargestContentfulPaintAttribute((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (this._onLoadIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoadIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadInterceptAttribute((this._onLoadIntercept_0_0value as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadInterceptAttribute((undefined as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onControllerAttached_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onControllerAttached_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnControllerAttachedAttribute((this._onControllerAttached_0_0value as (() => void) | undefined));
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnControllerAttachedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onOverScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onOverScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnOverScrollAttribute((this._onOverScroll_0_0value as ((value0: OnOverScrollEvent) => void) | undefined));
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnOverScrollAttribute((undefined as ((value0: OnOverScrollEvent) => void) | undefined));
                }
            }
        }
        if (this._onSafeBrowsingCheckResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSafeBrowsingCheckResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSafeBrowsingCheckResultAttribute((this._onSafeBrowsingCheckResult_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSafeBrowsingCheckResultAttribute((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (this._onNavigationEntryCommitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNavigationEntryCommitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNavigationEntryCommittedAttribute((this._onNavigationEntryCommitted_0_0value as OnNavigationEntryCommittedCallback | undefined));
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNavigationEntryCommittedAttribute((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (this._onIntelligentTrackingPreventionResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onIntelligentTrackingPreventionResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnIntelligentTrackingPreventionResultAttribute((this._onIntelligentTrackingPreventionResult_0_0value as OnIntelligentTrackingPreventionCallback | undefined));
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnIntelligentTrackingPreventionResultAttribute((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (this._javaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptOnDocumentStartAttribute((this._javaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._javaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptOnDocumentEndAttribute((this._javaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._layoutMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutModeAttribute((this._layoutMode_0_0value as WebLayoutMode | undefined));
                    this._layoutMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutModeAttribute((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (this._enableNativeEmbedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNativeEmbedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNativeEmbedModeAttribute((this._enableNativeEmbedMode_0_0value as boolean | undefined));
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNativeEmbedModeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onNativeEmbedLifecycleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedLifecycleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedLifecycleChangeAttribute((this._onNativeEmbedLifecycleChange_0_0value as ((event: NativeEmbedDataInfo) => void) | undefined));
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedLifecycleChangeAttribute((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (this._onNativeEmbedVisibilityChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedVisibilityChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedVisibilityChangeAttribute((this._onNativeEmbedVisibilityChange_0_0value as OnNativeEmbedVisibilityChangeCallback | undefined));
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedVisibilityChangeAttribute((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (this._onNativeEmbedGestureEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedGestureEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedGestureEventAttribute((this._onNativeEmbedGestureEvent_0_0value as ((event: NativeEmbedTouchInfo) => void) | undefined));
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedGestureEventAttribute((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (this._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionsAttribute((this._copyOptions_0_0value as CopyOptions | undefined));
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionsAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._onOverrideUrlLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onOverrideUrlLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnOverrideUrlLoadingAttribute((this._onOverrideUrlLoading_0_0value as OnOverrideUrlLoadingCallback | undefined));
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnOverrideUrlLoadingAttribute((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (this._textAutosizing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textAutosizing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextAutosizingAttribute((this._textAutosizing_0_0value as boolean | undefined));
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextAutosizingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableNativeMediaPlayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNativeMediaPlayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNativeMediaPlayerAttribute((this._enableNativeMediaPlayer_0_0value as NativeMediaPlayerConfig | undefined));
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNativeMediaPlayerAttribute((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (this._onRenderProcessNotResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderProcessNotResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderProcessNotRespondingAttribute((this._onRenderProcessNotResponding_0_0value as OnRenderProcessNotRespondingCallback | undefined));
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderProcessNotRespondingAttribute((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (this._onRenderProcessResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderProcessResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderProcessRespondingAttribute((this._onRenderProcessResponding_0_0value as OnRenderProcessRespondingCallback | undefined));
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderProcessRespondingAttribute((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (this._onViewportFitChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onViewportFitChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnViewportFitChangedAttribute((this._onViewportFitChanged_0_0value as OnViewportFitChangedCallback | undefined));
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnViewportFitChangedAttribute((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (this._onInterceptKeyboardAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptKeyboardAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptKeyboardAttachAttribute((this._onInterceptKeyboardAttach_0_0value as WebKeyboardCallback | undefined));
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptKeyboardAttachAttribute((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (this._onAdsBlocked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAdsBlocked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAdsBlockedAttribute((this._onAdsBlocked_0_0value as OnAdsBlockedCallback | undefined));
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAdsBlockedAttribute((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (this._keyboardAvoidMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardAvoidMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyboardAvoidModeAttribute((this._keyboardAvoidMode_0_0value as WebKeyboardAvoidMode | undefined));
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyboardAvoidModeAttribute((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._optimizeParserBudget_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optimizeParserBudget_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptimizeParserBudgetAttribute((this._optimizeParserBudget_0_0value as boolean | undefined));
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptimizeParserBudgetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableFollowSystemFontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableFollowSystemFontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableFollowSystemFontWeightAttribute((this._enableFollowSystemFontWeight_0_0value as boolean | undefined));
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableFollowSystemFontWeightAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableWebAVSession_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableWebAVSession_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableWebAVSessionAttribute((this._enableWebAVSession_0_0value as boolean | undefined));
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableWebAVSessionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._runJavaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnDocumentStartAttribute((this._runJavaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._runJavaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnDocumentEndAttribute((this._runJavaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._runJavaScriptOnHeadEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnHeadEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnHeadEndAttribute((this._runJavaScriptOnHeadEnd_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnHeadEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._nativeEmbedOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nativeEmbedOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNativeEmbedOptionsAttribute((this._nativeEmbedOptions_0_0value as EmbedOptions | undefined));
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNativeEmbedOptionsAttribute((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (this._registerNativeEmbedRule_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._registerNativeEmbedRule_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRegisterNativeEmbedRuleAttribute((this._registerNativeEmbedRule_0_0value as string | undefined), (this._registerNativeEmbedRule_0_1value as string | undefined));
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRegisterNativeEmbedRuleAttribute((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (this._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as WebElementType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as WebResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptionsExt | undefined));
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindSelectionMenuAttribute((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WebModifier): void {
        super.mergeModifier(modifier)
        if (modifier._javaScriptAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptAccess(modifier._javaScriptAccess_0_0value);
                    break;
                }
                default: {
                    this.javaScriptAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fileAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fileAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fileAccess(modifier._fileAccess_0_0value);
                    break;
                }
                default: {
                    this.fileAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onlineImageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onlineImageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onlineImageAccess(modifier._onlineImageAccess_0_0value);
                    break;
                }
                default: {
                    this.onlineImageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._domStorageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._domStorageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.domStorageAccess(modifier._domStorageAccess_0_0value);
                    break;
                }
                default: {
                    this.domStorageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._imageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._imageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.imageAccess(modifier._imageAccess_0_0value);
                    break;
                }
                default: {
                    this.imageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._mixedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mixedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mixedMode(modifier._mixedMode_0_0value);
                    break;
                }
                default: {
                    this.mixedMode((undefined as MixedMode | undefined));
                }
            }
        }
        if (modifier._zoomAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._zoomAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.zoomAccess(modifier._zoomAccess_0_0value);
                    break;
                }
                default: {
                    this.zoomAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._geolocationAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._geolocationAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.geolocationAccess(modifier._geolocationAccess_0_0value);
                    break;
                }
                default: {
                    this.geolocationAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._javaScriptProxy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptProxy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptProxy(modifier._javaScriptProxy_0_0value);
                    break;
                }
                default: {
                    this.javaScriptProxy((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (modifier._cacheMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cacheMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cacheMode(modifier._cacheMode_0_0value);
                    break;
                }
                default: {
                    this.cacheMode((undefined as CacheMode | undefined));
                }
            }
        }
        if (modifier._darkMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._darkMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.darkMode(modifier._darkMode_0_0value);
                    break;
                }
                default: {
                    this.darkMode((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (modifier._forceDarkAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._forceDarkAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.forceDarkAccess(modifier._forceDarkAccess_0_0value);
                    break;
                }
                default: {
                    this.forceDarkAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._mediaOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mediaOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mediaOptions(modifier._mediaOptions_0_0value);
                    break;
                }
                default: {
                    this.mediaOptions((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (modifier._overviewModeAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._overviewModeAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.overviewModeAccess(modifier._overviewModeAccess_0_0value);
                    break;
                }
                default: {
                    this.overviewModeAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._overScrollMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._overScrollMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.overScrollMode(modifier._overScrollMode_0_0value);
                    break;
                }
                default: {
                    this.overScrollMode((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (modifier._blurOnKeyboardHideMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blurOnKeyboardHideMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blurOnKeyboardHideMode(modifier._blurOnKeyboardHideMode_0_0value);
                    break;
                }
                default: {
                    this.blurOnKeyboardHideMode((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (modifier._textZoomRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textZoomRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textZoomRatio(modifier._textZoomRatio_0_0value);
                    break;
                }
                default: {
                    this.textZoomRatio((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._databaseAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._databaseAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.databaseAccess(modifier._databaseAccess_0_0value);
                    break;
                }
                default: {
                    this.databaseAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._initialScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._initialScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialScale(modifier._initialScale_0_0value);
                    break;
                }
                default: {
                    this.initialScale((undefined as double | undefined));
                }
            }
        }
        if (modifier._metaViewport_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._metaViewport_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.metaViewport(modifier._metaViewport_0_0value);
                    break;
                }
                default: {
                    this.metaViewport((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onPageEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageEnd(modifier._onPageEnd_0_0value);
                    break;
                }
                default: {
                    this.onPageEnd((undefined as ((value0: OnPageEndEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onPageBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageBegin(modifier._onPageBegin_0_0value);
                    break;
                }
                default: {
                    this.onPageBegin((undefined as ((value0: OnPageBeginEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onProgressChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onProgressChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onProgressChange(modifier._onProgressChange_0_0value);
                    break;
                }
                default: {
                    this.onProgressChange((undefined as ((value0: OnProgressChangeEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onTitleReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTitleReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTitleReceive(modifier._onTitleReceive_0_0value);
                    break;
                }
                default: {
                    this.onTitleReceive((undefined as ((value0: OnTitleReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onGeolocationHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGeolocationHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGeolocationHide(modifier._onGeolocationHide_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationHide((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onGeolocationShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGeolocationShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGeolocationShow(modifier._onGeolocationShow_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationShow((undefined as ((value0: OnGeolocationShowEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRequestSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRequestSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRequestSelected(modifier._onRequestSelected_0_0value);
                    break;
                }
                default: {
                    this.onRequestSelected((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onAlert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAlert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAlert(modifier._onAlert_0_0value);
                    break;
                }
                default: {
                    this.onAlert((undefined as ((value0: OnAlertEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onBeforeUnload_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBeforeUnload_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBeforeUnload(modifier._onBeforeUnload_0_0value);
                    break;
                }
                default: {
                    this.onBeforeUnload((undefined as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onConfirm_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onConfirm_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onConfirm(modifier._onConfirm_0_0value);
                    break;
                }
                default: {
                    this.onConfirm((undefined as ((value0: OnConfirmEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onPrompt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPrompt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPrompt(modifier._onPrompt_0_0value);
                    break;
                }
                default: {
                    this.onPrompt((undefined as ((value0: OnPromptEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onConsole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onConsole_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onConsole(modifier._onConsole_0_0value);
                    break;
                }
                default: {
                    this.onConsole((undefined as ((value0: OnConsoleEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onErrorReceive(modifier._onErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onErrorReceive((undefined as ((value0: OnErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHttpErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHttpErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHttpErrorReceive(modifier._onHttpErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onHttpErrorReceive((undefined as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onDownloadStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDownloadStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDownloadStart(modifier._onDownloadStart_0_0value);
                    break;
                }
                default: {
                    this.onDownloadStart((undefined as ((value0: OnDownloadStartEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRefreshAccessedHistory_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRefreshAccessedHistory_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRefreshAccessedHistory(modifier._onRefreshAccessedHistory_0_0value);
                    break;
                }
                default: {
                    this.onRefreshAccessedHistory((undefined as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRenderExited_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderExited_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderExited(modifier._onRenderExited_0_0value);
                    break;
                }
                default: {
                    this.onRenderExited((undefined as ((value0: OnRenderExitedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onShowFileSelector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onShowFileSelector_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onShowFileSelector(modifier._onShowFileSelector_0_0value);
                    break;
                }
                default: {
                    this.onShowFileSelector((undefined as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onResourceLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onResourceLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onResourceLoad(modifier._onResourceLoad_0_0value);
                    break;
                }
                default: {
                    this.onResourceLoad((undefined as ((value0: OnResourceLoadEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFullScreenExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFullScreenExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFullScreenExit(modifier._onFullScreenExit_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFullScreenEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFullScreenEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFullScreenEnter(modifier._onFullScreenEnter_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenEnter((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (modifier._onScaleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScaleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScaleChange(modifier._onScaleChange_0_0value);
                    break;
                }
                default: {
                    this.onScaleChange((undefined as ((value0: OnScaleChangeEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHttpAuthRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHttpAuthRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHttpAuthRequest(modifier._onHttpAuthRequest_0_0value);
                    break;
                }
                default: {
                    this.onHttpAuthRequest((undefined as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onInterceptRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptRequest(modifier._onInterceptRequest_0_0value);
                    break;
                }
                default: {
                    this.onInterceptRequest((undefined as ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined));
                }
            }
        }
        if (modifier._onPermissionRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPermissionRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPermissionRequest(modifier._onPermissionRequest_0_0value);
                    break;
                }
                default: {
                    this.onPermissionRequest((undefined as ((value0: OnPermissionRequestEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onScreenCaptureRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScreenCaptureRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScreenCaptureRequest(modifier._onScreenCaptureRequest_0_0value);
                    break;
                }
                default: {
                    this.onScreenCaptureRequest((undefined as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onContextMenuShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContextMenuShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContextMenuShow(modifier._onContextMenuShow_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuShow((undefined as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onContextMenuHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContextMenuHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContextMenuHide(modifier._onContextMenuHide_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuHide((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (modifier._mediaPlayGestureAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mediaPlayGestureAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mediaPlayGestureAccess(modifier._mediaPlayGestureAccess_0_0value);
                    break;
                }
                default: {
                    this.mediaPlayGestureAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onSearchResultReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSearchResultReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSearchResultReceive(modifier._onSearchResultReceive_0_0value);
                    break;
                }
                default: {
                    this.onSearchResultReceive((undefined as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScroll(modifier._onScroll_0_0value);
                    break;
                }
                default: {
                    this.onScroll((undefined as ((value0: OnScrollEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSslErrorEventReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSslErrorEventReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSslErrorEventReceive(modifier._onSslErrorEventReceive_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEventReceive((undefined as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSslErrorEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSslErrorEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSslErrorEvent(modifier._onSslErrorEvent_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEvent((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (modifier._onClientAuthenticationRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClientAuthenticationRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClientAuthenticationRequest(modifier._onClientAuthenticationRequest_0_0value);
                    break;
                }
                default: {
                    this.onClientAuthenticationRequest((undefined as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onWindowNew_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWindowNew_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWindowNew(modifier._onWindowNew_0_0value);
                    break;
                }
                default: {
                    this.onWindowNew((undefined as ((value0: OnWindowNewEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onWindowExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWindowExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWindowExit(modifier._onWindowExit_0_0value);
                    break;
                }
                default: {
                    this.onWindowExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._multiWindowAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._multiWindowAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.multiWindowAccess(modifier._multiWindowAccess_0_0value);
                    break;
                }
                default: {
                    this.multiWindowAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onInterceptKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptKeyEvent(modifier._onInterceptKeyEvent_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyEvent((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._webStandardFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webStandardFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webStandardFont(modifier._webStandardFont_0_0value);
                    break;
                }
                default: {
                    this.webStandardFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webSerifFont(modifier._webSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSerifFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webSansSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webSansSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webSansSerifFont(modifier._webSansSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSansSerifFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webFixedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webFixedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webFixedFont(modifier._webFixedFont_0_0value);
                    break;
                }
                default: {
                    this.webFixedFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webFantasyFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webFantasyFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webFantasyFont(modifier._webFantasyFont_0_0value);
                    break;
                }
                default: {
                    this.webFantasyFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webCursiveFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webCursiveFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webCursiveFont(modifier._webCursiveFont_0_0value);
                    break;
                }
                default: {
                    this.webCursiveFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._defaultFixedFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultFixedFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultFixedFontSize(modifier._defaultFixedFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFixedFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._defaultFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultFontSize(modifier._defaultFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._minLogicalFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minLogicalFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minLogicalFontSize(modifier._minLogicalFontSize_0_0value);
                    break;
                }
                default: {
                    this.minLogicalFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._defaultTextEncodingFormat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultTextEncodingFormat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultTextEncodingFormat(modifier._defaultTextEncodingFormat_0_0value);
                    break;
                }
                default: {
                    this.defaultTextEncodingFormat((undefined as string | undefined));
                }
            }
        }
        if (modifier._forceDisplayScrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._forceDisplayScrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.forceDisplayScrollBar(modifier._forceDisplayScrollBar_0_0value);
                    break;
                }
                default: {
                    this.forceDisplayScrollBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._blockNetwork_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockNetwork_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockNetwork(modifier._blockNetwork_0_0value);
                    break;
                }
                default: {
                    this.blockNetwork((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._horizontalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._horizontalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.horizontalScrollBarAccess(modifier._horizontalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.horizontalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._verticalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._verticalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.verticalScrollBarAccess(modifier._verticalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.verticalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onTouchIconUrlReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTouchIconUrlReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTouchIconUrlReceived(modifier._onTouchIconUrlReceived_0_0value);
                    break;
                }
                default: {
                    this.onTouchIconUrlReceived((undefined as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFaviconReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFaviconReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFaviconReceived(modifier._onFaviconReceived_0_0value);
                    break;
                }
                default: {
                    this.onFaviconReceived((undefined as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onPageVisible_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageVisible_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageVisible(modifier._onPageVisible_0_0value);
                    break;
                }
                default: {
                    this.onPageVisible((undefined as ((value0: OnPageVisibleEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onDataResubmitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDataResubmitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDataResubmitted(modifier._onDataResubmitted_0_0value);
                    break;
                }
                default: {
                    this.onDataResubmitted((undefined as ((value0: OnDataResubmittedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._pinchSmooth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pinchSmooth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pinchSmooth(modifier._pinchSmooth_0_0value);
                    break;
                }
                default: {
                    this.pinchSmooth((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._allowWindowOpenMethod_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowWindowOpenMethod_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowWindowOpenMethod(modifier._allowWindowOpenMethod_0_0value);
                    break;
                }
                default: {
                    this.allowWindowOpenMethod((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onAudioStateChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAudioStateChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAudioStateChanged(modifier._onAudioStateChanged_0_0value);
                    break;
                }
                default: {
                    this.onAudioStateChanged((undefined as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFirstContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFirstContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFirstContentfulPaint(modifier._onFirstContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstContentfulPaint((undefined as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFirstMeaningfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFirstMeaningfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFirstMeaningfulPaint(modifier._onFirstMeaningfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstMeaningfulPaint((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (modifier._onLargestContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLargestContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLargestContentfulPaint(modifier._onLargestContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onLargestContentfulPaint((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (modifier._onLoadIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoadIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoadIntercept(modifier._onLoadIntercept_0_0value);
                    break;
                }
                default: {
                    this.onLoadIntercept((undefined as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onControllerAttached_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onControllerAttached_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onControllerAttached(modifier._onControllerAttached_0_0value);
                    break;
                }
                default: {
                    this.onControllerAttached((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onOverScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onOverScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onOverScroll(modifier._onOverScroll_0_0value);
                    break;
                }
                default: {
                    this.onOverScroll((undefined as ((value0: OnOverScrollEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSafeBrowsingCheckResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSafeBrowsingCheckResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSafeBrowsingCheckResult(modifier._onSafeBrowsingCheckResult_0_0value);
                    break;
                }
                default: {
                    this.onSafeBrowsingCheckResult((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (modifier._onNavigationEntryCommitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNavigationEntryCommitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNavigationEntryCommitted(modifier._onNavigationEntryCommitted_0_0value);
                    break;
                }
                default: {
                    this.onNavigationEntryCommitted((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (modifier._onIntelligentTrackingPreventionResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onIntelligentTrackingPreventionResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onIntelligentTrackingPreventionResult(modifier._onIntelligentTrackingPreventionResult_0_0value);
                    break;
                }
                default: {
                    this.onIntelligentTrackingPreventionResult((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (modifier._javaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptOnDocumentStart(modifier._javaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._javaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptOnDocumentEnd(modifier._javaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._layoutMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutMode(modifier._layoutMode_0_0value);
                    break;
                }
                default: {
                    this.layoutMode((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (modifier._enableNativeEmbedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNativeEmbedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNativeEmbedMode(modifier._enableNativeEmbedMode_0_0value);
                    break;
                }
                default: {
                    this.enableNativeEmbedMode((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedLifecycleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedLifecycleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedLifecycleChange(modifier._onNativeEmbedLifecycleChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedLifecycleChange((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedVisibilityChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedVisibilityChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedVisibilityChange(modifier._onNativeEmbedVisibilityChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedVisibilityChange((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedGestureEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedGestureEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedGestureEvent(modifier._onNativeEmbedGestureEvent_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedGestureEvent((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (modifier._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOptions(modifier._copyOptions_0_0value);
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._onOverrideUrlLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onOverrideUrlLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onOverrideUrlLoading(modifier._onOverrideUrlLoading_0_0value);
                    break;
                }
                default: {
                    this.onOverrideUrlLoading((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (modifier._textAutosizing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textAutosizing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textAutosizing(modifier._textAutosizing_0_0value);
                    break;
                }
                default: {
                    this.textAutosizing((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableNativeMediaPlayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNativeMediaPlayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNativeMediaPlayer(modifier._enableNativeMediaPlayer_0_0value);
                    break;
                }
                default: {
                    this.enableNativeMediaPlayer((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (modifier._onRenderProcessNotResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderProcessNotResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderProcessNotResponding(modifier._onRenderProcessNotResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessNotResponding((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (modifier._onRenderProcessResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderProcessResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderProcessResponding(modifier._onRenderProcessResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessResponding((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (modifier._onViewportFitChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onViewportFitChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onViewportFitChanged(modifier._onViewportFitChanged_0_0value);
                    break;
                }
                default: {
                    this.onViewportFitChanged((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (modifier._onInterceptKeyboardAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptKeyboardAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptKeyboardAttach(modifier._onInterceptKeyboardAttach_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyboardAttach((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (modifier._onAdsBlocked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAdsBlocked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAdsBlocked(modifier._onAdsBlocked_0_0value);
                    break;
                }
                default: {
                    this.onAdsBlocked((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (modifier._keyboardAvoidMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._keyboardAvoidMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardAvoidMode(modifier._keyboardAvoidMode_0_0value);
                    break;
                }
                default: {
                    this.keyboardAvoidMode((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._optimizeParserBudget_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optimizeParserBudget_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optimizeParserBudget(modifier._optimizeParserBudget_0_0value);
                    break;
                }
                default: {
                    this.optimizeParserBudget((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableFollowSystemFontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableFollowSystemFontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableFollowSystemFontWeight(modifier._enableFollowSystemFontWeight_0_0value);
                    break;
                }
                default: {
                    this.enableFollowSystemFontWeight((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableWebAVSession_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableWebAVSession_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableWebAVSession(modifier._enableWebAVSession_0_0value);
                    break;
                }
                default: {
                    this.enableWebAVSession((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnDocumentStart(modifier._runJavaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnDocumentEnd(modifier._runJavaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnHeadEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnHeadEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnHeadEnd(modifier._runJavaScriptOnHeadEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnHeadEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._nativeEmbedOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nativeEmbedOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nativeEmbedOptions(modifier._nativeEmbedOptions_0_0value);
                    break;
                }
                default: {
                    this.nativeEmbedOptions((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (modifier._registerNativeEmbedRule_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._registerNativeEmbedRule_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.registerNativeEmbedRule(modifier._registerNativeEmbedRule_0_0value, modifier._registerNativeEmbedRule_0_1value);
                    break;
                }
                default: {
                    this.registerNativeEmbedRule((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (modifier._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu_0_0value, modifier._bindSelectionMenu_0_1value, modifier._bindSelectionMenu_0_2value, modifier._bindSelectionMenu_0_3value);
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
    }
    javaScriptAccess(value: boolean | undefined): this {
        if (((this._javaScriptAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._javaScriptAccess_0_0value) !== (value)))
        {
            this._javaScriptAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptAccess_0_0value = value
        } else
        {
            this._javaScriptAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fileAccess(value: boolean | undefined): this {
        if (((this._fileAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fileAccess_0_0value) !== (value)))
        {
            this._fileAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._fileAccess_0_0value = value
        } else
        {
            this._fileAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onlineImageAccess(value: boolean | undefined): this {
        if (((this._onlineImageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._onlineImageAccess_0_0value) !== (value)))
        {
            this._onlineImageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._onlineImageAccess_0_0value = value
        } else
        {
            this._onlineImageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    domStorageAccess(value: boolean | undefined): this {
        if (((this._domStorageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._domStorageAccess_0_0value) !== (value)))
        {
            this._domStorageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._domStorageAccess_0_0value = value
        } else
        {
            this._domStorageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    imageAccess(value: boolean | undefined): this {
        if (((this._imageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._imageAccess_0_0value) !== (value)))
        {
            this._imageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._imageAccess_0_0value = value
        } else
        {
            this._imageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mixedMode(value: MixedMode | undefined): this {
        if (((this._mixedMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mixedMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._mixedMode_0_0value = value
        } else
        {
            this._mixedMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    zoomAccess(value: boolean | undefined): this {
        if (((this._zoomAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._zoomAccess_0_0value) !== (value)))
        {
            this._zoomAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._zoomAccess_0_0value = value
        } else
        {
            this._zoomAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    geolocationAccess(value: boolean | undefined): this {
        if (((this._geolocationAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._geolocationAccess_0_0value) !== (value)))
        {
            this._geolocationAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._geolocationAccess_0_0value = value
        } else
        {
            this._geolocationAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (((this._javaScriptProxy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptProxy_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptProxy_0_0value = value
        } else
        {
            this._javaScriptProxy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cacheMode(value: CacheMode | undefined): this {
        if (((this._cacheMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._cacheMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._cacheMode_0_0value = value
        } else
        {
            this._cacheMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    darkMode(value: WebDarkMode | undefined): this {
        if (((this._darkMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._darkMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._darkMode_0_0value = value
        } else
        {
            this._darkMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    forceDarkAccess(value: boolean | undefined): this {
        if (((this._forceDarkAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._forceDarkAccess_0_0value) !== (value)))
        {
            this._forceDarkAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._forceDarkAccess_0_0value = value
        } else
        {
            this._forceDarkAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        if (((this._mediaOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mediaOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._mediaOptions_0_0value = value
        } else
        {
            this._mediaOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    overviewModeAccess(value: boolean | undefined): this {
        if (((this._overviewModeAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._overviewModeAccess_0_0value) !== (value)))
        {
            this._overviewModeAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._overviewModeAccess_0_0value = value
        } else
        {
            this._overviewModeAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        if (((this._overScrollMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._overScrollMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._overScrollMode_0_0value = value
        } else
        {
            this._overScrollMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (((this._blurOnKeyboardHideMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._blurOnKeyboardHideMode_0_0value = value
        } else
        {
            this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textZoomRatio(value: int32 | undefined): this {
        if (((this._textZoomRatio_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._textZoomRatio_0_0value) !== (value)))
        {
            this._textZoomRatio_0_flag = AttributeUpdaterFlag.UPDATE
            this._textZoomRatio_0_0value = value
        } else
        {
            this._textZoomRatio_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    databaseAccess(value: boolean | undefined): this {
        if (((this._databaseAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._databaseAccess_0_0value) !== (value)))
        {
            this._databaseAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._databaseAccess_0_0value = value
        } else
        {
            this._databaseAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    initialScale(value: double | undefined): this {
        if (((this._initialScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._initialScale_0_0value) !== (value)))
        {
            this._initialScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._initialScale_0_0value = value
        } else
        {
            this._initialScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    metaViewport(value: boolean | undefined): this {
        if (((this._metaViewport_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._metaViewport_0_0value) !== (value)))
        {
            this._metaViewport_0_flag = AttributeUpdaterFlag.UPDATE
            this._metaViewport_0_0value = value
        } else
        {
            this._metaViewport_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        if (((this._onPageEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageEnd_0_0value = value
        } else
        {
            this._onPageEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        if (((this._onPageBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageBegin_0_0value = value
        } else
        {
            this._onPageBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        if (((this._onProgressChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onProgressChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onProgressChange_0_0value = value
        } else
        {
            this._onProgressChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        if (((this._onTitleReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTitleReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTitleReceive_0_0value = value
        } else
        {
            this._onTitleReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        if (((this._onGeolocationHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGeolocationHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGeolocationHide_0_0value = value
        } else
        {
            this._onGeolocationHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        if (((this._onGeolocationShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGeolocationShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGeolocationShow_0_0value = value
        } else
        {
            this._onGeolocationShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRequestSelected(value: (() => void) | undefined): this {
        if (((this._onRequestSelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRequestSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRequestSelected_0_0value = value
        } else
        {
            this._onRequestSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        if (((this._onAlert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAlert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAlert_0_0value = value
        } else
        {
            this._onAlert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        if (((this._onBeforeUnload_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onBeforeUnload_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBeforeUnload_0_0value = value
        } else
        {
            this._onBeforeUnload_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        if (((this._onConfirm_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onConfirm_0_flag = AttributeUpdaterFlag.UPDATE
            this._onConfirm_0_0value = value
        } else
        {
            this._onConfirm_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        if (((this._onPrompt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPrompt_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPrompt_0_0value = value
        } else
        {
            this._onPrompt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        if (((this._onConsole_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onConsole_0_flag = AttributeUpdaterFlag.UPDATE
            this._onConsole_0_0value = value
        } else
        {
            this._onConsole_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        if (((this._onErrorReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onErrorReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onErrorReceive_0_0value = value
        } else
        {
            this._onErrorReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        if (((this._onHttpErrorReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHttpErrorReceive_0_0value = value
        } else
        {
            this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        if (((this._onDownloadStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDownloadStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDownloadStart_0_0value = value
        } else
        {
            this._onDownloadStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        if (((this._onRefreshAccessedHistory_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRefreshAccessedHistory_0_0value = value
        } else
        {
            this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        if (((this._onRenderExited_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderExited_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderExited_0_0value = value
        } else
        {
            this._onRenderExited_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        if (((this._onShowFileSelector_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onShowFileSelector_0_flag = AttributeUpdaterFlag.UPDATE
            this._onShowFileSelector_0_0value = value
        } else
        {
            this._onShowFileSelector_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        if (((this._onResourceLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onResourceLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onResourceLoad_0_0value = value
        } else
        {
            this._onResourceLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        if (((this._onFullScreenExit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFullScreenExit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFullScreenExit_0_0value = value
        } else
        {
            this._onFullScreenExit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (((this._onFullScreenEnter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFullScreenEnter_0_0value = value
        } else
        {
            this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        if (((this._onScaleChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScaleChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScaleChange_0_0value = value
        } else
        {
            this._onScaleChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        if (((this._onHttpAuthRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHttpAuthRequest_0_0value = value
        } else
        {
            this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse) | undefined): this {
        if (((this._onInterceptRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptRequest_0_0value = value
        } else
        {
            this._onInterceptRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        if (((this._onPermissionRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPermissionRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPermissionRequest_0_0value = value
        } else
        {
            this._onPermissionRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        if (((this._onScreenCaptureRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScreenCaptureRequest_0_0value = value
        } else
        {
            this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        if (((this._onContextMenuShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContextMenuShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContextMenuShow_0_0value = value
        } else
        {
            this._onContextMenuShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (((this._onContextMenuHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContextMenuHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContextMenuHide_0_0value = value
        } else
        {
            this._onContextMenuHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        if (((this._mediaPlayGestureAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._mediaPlayGestureAccess_0_0value) !== (value)))
        {
            this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._mediaPlayGestureAccess_0_0value = value
        } else
        {
            this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        if (((this._onSearchResultReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSearchResultReceive_0_0value = value
        } else
        {
            this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        if (((this._onScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScroll_0_0value = value
        } else
        {
            this._onScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        if (((this._onSslErrorEventReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSslErrorEventReceive_0_0value = value
        } else
        {
            this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (((this._onSslErrorEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSslErrorEvent_0_0value = value
        } else
        {
            this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        if (((this._onClientAuthenticationRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onClientAuthenticationRequest_0_0value = value
        } else
        {
            this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        if (((this._onWindowNew_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWindowNew_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWindowNew_0_0value = value
        } else
        {
            this._onWindowNew_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWindowExit(value: (() => void) | undefined): this {
        if (((this._onWindowExit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWindowExit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWindowExit_0_0value = value
        } else
        {
            this._onWindowExit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    multiWindowAccess(value: boolean | undefined): this {
        if (((this._multiWindowAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._multiWindowAccess_0_0value) !== (value)))
        {
            this._multiWindowAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._multiWindowAccess_0_0value = value
        } else
        {
            this._multiWindowAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (((this._onInterceptKeyEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptKeyEvent_0_0value = value
        } else
        {
            this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webStandardFont(value: string | undefined): this {
        if (((this._webStandardFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webStandardFont_0_0value) !== (value)))
        {
            this._webStandardFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webStandardFont_0_0value = value
        } else
        {
            this._webStandardFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webSerifFont(value: string | undefined): this {
        if (((this._webSerifFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webSerifFont_0_0value) !== (value)))
        {
            this._webSerifFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webSerifFont_0_0value = value
        } else
        {
            this._webSerifFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webSansSerifFont(value: string | undefined): this {
        if (((this._webSansSerifFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webSansSerifFont_0_0value) !== (value)))
        {
            this._webSansSerifFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webSansSerifFont_0_0value = value
        } else
        {
            this._webSansSerifFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webFixedFont(value: string | undefined): this {
        if (((this._webFixedFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webFixedFont_0_0value) !== (value)))
        {
            this._webFixedFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webFixedFont_0_0value = value
        } else
        {
            this._webFixedFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webFantasyFont(value: string | undefined): this {
        if (((this._webFantasyFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webFantasyFont_0_0value) !== (value)))
        {
            this._webFantasyFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webFantasyFont_0_0value = value
        } else
        {
            this._webFantasyFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webCursiveFont(value: string | undefined): this {
        if (((this._webCursiveFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webCursiveFont_0_0value) !== (value)))
        {
            this._webCursiveFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webCursiveFont_0_0value = value
        } else
        {
            this._webCursiveFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        if (((this._defaultFixedFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultFixedFontSize_0_0value) !== (value)))
        {
            this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultFixedFontSize_0_0value = value
        } else
        {
            this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultFontSize(value: int32 | undefined): this {
        if (((this._defaultFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultFontSize_0_0value) !== (value)))
        {
            this._defaultFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultFontSize_0_0value = value
        } else
        {
            this._defaultFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(value: int32 | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minFontSize_0_0value) !== (value)))
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = value
        } else
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minLogicalFontSize(value: int32 | undefined): this {
        if (((this._minLogicalFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minLogicalFontSize_0_0value) !== (value)))
        {
            this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minLogicalFontSize_0_0value = value
        } else
        {
            this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        if (((this._defaultTextEncodingFormat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultTextEncodingFormat_0_0value) !== (value)))
        {
            this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultTextEncodingFormat_0_0value = value
        } else
        {
            this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        if (((this._forceDisplayScrollBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._forceDisplayScrollBar_0_0value) !== (value)))
        {
            this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._forceDisplayScrollBar_0_0value = value
        } else
        {
            this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockNetwork(value: boolean | undefined): this {
        if (((this._blockNetwork_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._blockNetwork_0_0value) !== (value)))
        {
            this._blockNetwork_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockNetwork_0_0value = value
        } else
        {
            this._blockNetwork_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        if (((this._horizontalScrollBarAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._horizontalScrollBarAccess_0_0value) !== (value)))
        {
            this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._horizontalScrollBarAccess_0_0value = value
        } else
        {
            this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        if (((this._verticalScrollBarAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._verticalScrollBarAccess_0_0value) !== (value)))
        {
            this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._verticalScrollBarAccess_0_0value = value
        } else
        {
            this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        if (((this._onTouchIconUrlReceived_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTouchIconUrlReceived_0_0value = value
        } else
        {
            this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        if (((this._onFaviconReceived_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFaviconReceived_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFaviconReceived_0_0value = value
        } else
        {
            this._onFaviconReceived_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        if (((this._onPageVisible_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageVisible_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageVisible_0_0value = value
        } else
        {
            this._onPageVisible_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        if (((this._onDataResubmitted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDataResubmitted_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDataResubmitted_0_0value = value
        } else
        {
            this._onDataResubmitted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pinchSmooth(value: boolean | undefined): this {
        if (((this._pinchSmooth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._pinchSmooth_0_0value) !== (value)))
        {
            this._pinchSmooth_0_flag = AttributeUpdaterFlag.UPDATE
            this._pinchSmooth_0_0value = value
        } else
        {
            this._pinchSmooth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        if (((this._allowWindowOpenMethod_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._allowWindowOpenMethod_0_0value) !== (value)))
        {
            this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowWindowOpenMethod_0_0value = value
        } else
        {
            this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        if (((this._onAudioStateChanged_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAudioStateChanged_0_0value = value
        } else
        {
            this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        if (((this._onFirstContentfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFirstContentfulPaint_0_0value = value
        } else
        {
            this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (((this._onFirstMeaningfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFirstMeaningfulPaint_0_0value = value
        } else
        {
            this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (((this._onLargestContentfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLargestContentfulPaint_0_0value = value
        } else
        {
            this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        if (((this._onLoadIntercept_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoadIntercept_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoadIntercept_0_0value = value
        } else
        {
            this._onLoadIntercept_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onControllerAttached(value: (() => void) | undefined): this {
        if (((this._onControllerAttached_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onControllerAttached_0_flag = AttributeUpdaterFlag.UPDATE
            this._onControllerAttached_0_0value = value
        } else
        {
            this._onControllerAttached_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
        if (((this._onOverScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onOverScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onOverScroll_0_0value = value
        } else
        {
            this._onOverScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (((this._onSafeBrowsingCheckResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSafeBrowsingCheckResult_0_0value = value
        } else
        {
            this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (((this._onNavigationEntryCommitted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNavigationEntryCommitted_0_0value = value
        } else
        {
            this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (((this._onIntelligentTrackingPreventionResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onIntelligentTrackingPreventionResult_0_0value = value
        } else
        {
            this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._javaScriptOnDocumentStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptOnDocumentStart_0_0value = value
        } else
        {
            this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._javaScriptOnDocumentEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptOnDocumentEnd_0_0value = value
        } else
        {
            this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        if (((this._layoutMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutMode_0_0value = value
        } else
        {
            this._layoutMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        if (((this._enableNativeEmbedMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNativeEmbedMode_0_0value) !== (value)))
        {
            this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNativeEmbedMode_0_0value = value
        } else
        {
            this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (((this._onNativeEmbedLifecycleChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedLifecycleChange_0_0value = value
        } else
        {
            this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (((this._onNativeEmbedVisibilityChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedVisibilityChange_0_0value = value
        } else
        {
            this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (((this._onNativeEmbedGestureEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedGestureEvent_0_0value = value
        } else
        {
            this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._copyOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOptions_0_0value = value
        } else
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (((this._onOverrideUrlLoading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.UPDATE
            this._onOverrideUrlLoading_0_0value = value
        } else
        {
            this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textAutosizing(value: boolean | undefined): this {
        if (((this._textAutosizing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._textAutosizing_0_0value) !== (value)))
        {
            this._textAutosizing_0_flag = AttributeUpdaterFlag.UPDATE
            this._textAutosizing_0_0value = value
        } else
        {
            this._textAutosizing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (((this._enableNativeMediaPlayer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNativeMediaPlayer_0_0value = value
        } else
        {
            this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (((this._onRenderProcessNotResponding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderProcessNotResponding_0_0value = value
        } else
        {
            this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (((this._onRenderProcessResponding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderProcessResponding_0_0value = value
        } else
        {
            this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (((this._onViewportFitChanged_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.UPDATE
            this._onViewportFitChanged_0_0value = value
        } else
        {
            this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (((this._onInterceptKeyboardAttach_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptKeyboardAttach_0_0value = value
        } else
        {
            this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (((this._onAdsBlocked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAdsBlocked_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAdsBlocked_0_0value = value
        } else
        {
            this._onAdsBlocked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (((this._keyboardAvoidMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAvoidMode_0_0value = value
        } else
        {
            this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
        } else
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optimizeParserBudget(value: boolean | undefined): this {
        if (((this._optimizeParserBudget_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._optimizeParserBudget_0_0value) !== (value)))
        {
            this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.UPDATE
            this._optimizeParserBudget_0_0value = value
        } else
        {
            this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (((this._enableFollowSystemFontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableFollowSystemFontWeight_0_0value) !== (value)))
        {
            this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableFollowSystemFontWeight_0_0value = value
        } else
        {
            this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableWebAVSession(value: boolean | undefined): this {
        if (((this._enableWebAVSession_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableWebAVSession_0_0value) !== (value)))
        {
            this._enableWebAVSession_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableWebAVSession_0_0value = value
        } else
        {
            this._enableWebAVSession_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnDocumentStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnDocumentStart_0_0value = value
        } else
        {
            this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnDocumentEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnDocumentEnd_0_0value = value
        } else
        {
            this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnHeadEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnHeadEnd_0_0value = value
        } else
        {
            this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (((this._nativeEmbedOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._nativeEmbedOptions_0_0value = value
        } else
        {
            this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (((this._registerNativeEmbedRule_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._registerNativeEmbedRule_0_0value) !== (tag)) || ((this._registerNativeEmbedRule_0_1value) !== (type)))
        {
            this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.UPDATE
            this._registerNativeEmbedRule_0_0value = tag
            this._registerNativeEmbedRule_0_1value = type
        } else
        {
            this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (((this._bindSelectionMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true) || (true))
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindSelectionMenu_0_0value = elementType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
        } else
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
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
        const valueHolderForEnable  = value.enable
        valueSerializer.writeBoolean(valueHolderForEnable)
        const valueHolderForShouldOverlay  = value.shouldOverlay
        valueSerializer.writeBoolean(valueHolderForShouldOverlay)
    }
    public static read(buffer: DeserializerBase): NativeMediaPlayerConfig {
        let valueDeserializer : DeserializerBase = buffer
        const enableTmpResult : boolean = valueDeserializer.readBoolean()
        const shouldOverlayTmpResult : boolean = valueDeserializer.readBoolean()
        let value : NativeMediaPlayerConfig = ({enable: enableTmpResult, shouldOverlay: shouldOverlayTmpResult} as NativeMediaPlayerConfig)
        return value
    }
}
export class OnAudioStateChangedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAudioStateChangedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPlaying  = value.playing
        valueSerializer.writeBoolean(valueHolderForPlaying)
    }
    public static read(buffer: DeserializerBase): OnAudioStateChangedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const playingTmpResult : boolean = valueDeserializer.readBoolean()
        let value : OnAudioStateChangedEvent = ({playing: playingTmpResult} as OnAudioStateChangedEvent)
        return value
    }
}
export class OnConsoleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConsoleEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMessage  = value.message
        ConsoleMessage_serializer.write(valueSerializer, valueHolderForMessage)
    }
    public static read(buffer: DeserializerBase): OnConsoleEvent {
        let valueDeserializer : DeserializerBase = buffer
        const messageTmpResult : ConsoleMessage = (ConsoleMessage_serializer.read(valueDeserializer) as ConsoleMessage)
        let value : OnConsoleEvent = ({message: messageTmpResult} as OnConsoleEvent)
        return value
    }
}
export class OnDataResubmittedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDataResubmittedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        DataResubmissionHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnDataResubmittedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : DataResubmissionHandler = (DataResubmissionHandler_serializer.read(valueDeserializer) as DataResubmissionHandler)
        let value : OnDataResubmittedEvent = ({handler: handlerTmpResult} as OnDataResubmittedEvent)
        return value
    }
}
export class OnFaviconReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFaviconReceivedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFavicon  = value.favicon
        image_PixelMap_serializer.write(valueSerializer, valueHolderForFavicon)
    }
    public static read(buffer: DeserializerBase): OnFaviconReceivedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const faviconTmpResult : image.PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        let value : OnFaviconReceivedEvent = ({favicon: faviconTmpResult} as OnFaviconReceivedEvent)
        return value
    }
}
export class OnFirstContentfulPaintEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFirstContentfulPaintEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationStartTick  = value.navigationStartTick
        valueSerializer.writeInt64(valueHolderForNavigationStartTick)
        const valueHolderForFirstContentfulPaintMs  = value.firstContentfulPaintMs
        valueSerializer.writeInt64(valueHolderForFirstContentfulPaintMs)
    }
    public static read(buffer: DeserializerBase): OnFirstContentfulPaintEvent {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTickTmpResult : int64 = valueDeserializer.readInt64()
        const firstContentfulPaintMsTmpResult : int64 = valueDeserializer.readInt64()
        let value : OnFirstContentfulPaintEvent = ({navigationStartTick: navigationStartTickTmpResult, firstContentfulPaintMs: firstContentfulPaintMsTmpResult} as OnFirstContentfulPaintEvent)
        return value
    }
}
export class OnOverScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnOverScrollEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXOffset  = value.xOffset
        valueSerializer.writeFloat64(valueHolderForXOffset)
        const valueHolderForYOffset  = value.yOffset
        valueSerializer.writeFloat64(valueHolderForYOffset)
    }
    public static read(buffer: DeserializerBase): OnOverScrollEvent {
        let valueDeserializer : DeserializerBase = buffer
        const xOffsetTmpResult : double = valueDeserializer.readFloat64()
        const yOffsetTmpResult : double = valueDeserializer.readFloat64()
        let value : OnOverScrollEvent = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OnOverScrollEvent)
        return value
    }
}
export class OnProgressChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnProgressChangeEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNewProgress  = value.newProgress
        valueSerializer.writeInt32(valueHolderForNewProgress)
    }
    public static read(buffer: DeserializerBase): OnProgressChangeEvent {
        let valueDeserializer : DeserializerBase = buffer
        const newProgressTmpResult : int32 = valueDeserializer.readInt32()
        let value : OnProgressChangeEvent = ({newProgress: newProgressTmpResult} as OnProgressChangeEvent)
        return value
    }
}
export class OnScaleChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScaleChangeEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOldScale  = value.oldScale
        valueSerializer.writeFloat64(valueHolderForOldScale)
        const valueHolderForNewScale  = value.newScale
        valueSerializer.writeFloat64(valueHolderForNewScale)
    }
    public static read(buffer: DeserializerBase): OnScaleChangeEvent {
        let valueDeserializer : DeserializerBase = buffer
        const oldScaleTmpResult : double = valueDeserializer.readFloat64()
        const newScaleTmpResult : double = valueDeserializer.readFloat64()
        let value : OnScaleChangeEvent = ({oldScale: oldScaleTmpResult, newScale: newScaleTmpResult} as OnScaleChangeEvent)
        return value
    }
}
export class OnScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScrollEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXOffset  = value.xOffset
        valueSerializer.writeFloat64(valueHolderForXOffset)
        const valueHolderForYOffset  = value.yOffset
        valueSerializer.writeFloat64(valueHolderForYOffset)
    }
    public static read(buffer: DeserializerBase): OnScrollEvent {
        let valueDeserializer : DeserializerBase = buffer
        const xOffsetTmpResult : double = valueDeserializer.readFloat64()
        const yOffsetTmpResult : double = valueDeserializer.readFloat64()
        let value : OnScrollEvent = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OnScrollEvent)
        return value
    }
}
export class OnSearchResultReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSearchResultReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForActiveMatchOrdinal  = value.activeMatchOrdinal
        valueSerializer.writeNumber(valueHolderForActiveMatchOrdinal)
        const valueHolderForNumberOfMatches  = value.numberOfMatches
        valueSerializer.writeNumber(valueHolderForNumberOfMatches)
        const valueHolderForIsDoneCounting  = value.isDoneCounting
        valueSerializer.writeBoolean(valueHolderForIsDoneCounting)
    }
    public static read(buffer: DeserializerBase): OnSearchResultReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const activeMatchOrdinalTmpResult : number = (valueDeserializer.readNumber() as number)
        const numberOfMatchesTmpResult : number = (valueDeserializer.readNumber() as number)
        const isDoneCountingTmpResult : boolean = valueDeserializer.readBoolean()
        let value : OnSearchResultReceiveEvent = ({activeMatchOrdinal: activeMatchOrdinalTmpResult, numberOfMatches: numberOfMatchesTmpResult, isDoneCounting: isDoneCountingTmpResult} as OnSearchResultReceiveEvent)
        return value
    }
}
export class OnShowFileSelectorEvent_serializer {
    public static write(buffer: SerializerBase, value: OnShowFileSelectorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForResult  = value.result
        FileSelectorResult_serializer.write(valueSerializer, valueHolderForResult)
        const valueHolderForFileSelector  = value.fileSelector
        FileSelectorParam_serializer.write(valueSerializer, valueHolderForFileSelector)
    }
    public static read(buffer: DeserializerBase): OnShowFileSelectorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const resultTmpResult : FileSelectorResult = (FileSelectorResult_serializer.read(valueDeserializer) as FileSelectorResult)
        const fileSelectorTmpResult : FileSelectorParam = (FileSelectorParam_serializer.read(valueDeserializer) as FileSelectorParam)
        let value : OnShowFileSelectorEvent = ({result: resultTmpResult, fileSelector: fileSelectorTmpResult} as OnShowFileSelectorEvent)
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
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForAdsBlocked  = value.adsBlocked
        valueSerializer.writeInt32((valueHolderForAdsBlocked.length).toInt())
        for (let valueHolderForAdsBlockedCounterI = 0; valueHolderForAdsBlockedCounterI < valueHolderForAdsBlocked.length; valueHolderForAdsBlockedCounterI++) {
            const valueHolderForAdsBlockedTmpElement : string = valueHolderForAdsBlocked[valueHolderForAdsBlockedCounterI]
            valueSerializer.writeString(valueHolderForAdsBlockedTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): AdsBlockedDetails {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const adsBlockedTmpBufLength : int32 = valueDeserializer.readInt32()
        let adsBlockedTmpBuf : Array<string> = new Array<string>(adsBlockedTmpBufLength)
        for (let adsBlockedTmpBufBufCounterI = 0; adsBlockedTmpBufBufCounterI < adsBlockedTmpBufLength; adsBlockedTmpBufBufCounterI++) {
            adsBlockedTmpBuf[adsBlockedTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const adsBlockedTmpResult : Array<string> = adsBlockedTmpBuf
        let value : AdsBlockedDetails = ({url: urlTmpResult, adsBlocked: adsBlockedTmpResult} as AdsBlockedDetails)
        return value
    }
}
export class EmbedOptions_serializer {
    public static write(buffer: SerializerBase, value: EmbedOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSupportDefaultIntrinsicSize  = value.supportDefaultIntrinsicSize
        if (valueHolderForSupportDefaultIntrinsicSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSupportDefaultIntrinsicSizeTmpValue  = valueHolderForSupportDefaultIntrinsicSize!
            valueSerializer.writeBoolean(valueHolderForSupportDefaultIntrinsicSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmbedOptions {
        let valueDeserializer : DeserializerBase = buffer
        const supportDefaultIntrinsicSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let supportDefaultIntrinsicSizeTmpBuf : boolean | undefined
        if ((supportDefaultIntrinsicSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            supportDefaultIntrinsicSizeTmpBuf = valueDeserializer.readBoolean()
        }
        const supportDefaultIntrinsicSizeTmpResult : boolean | undefined = supportDefaultIntrinsicSizeTmpBuf
        let value : EmbedOptions = ({supportDefaultIntrinsicSize: supportDefaultIntrinsicSizeTmpResult} as EmbedOptions)
        return value
    }
}
export class FirstMeaningfulPaint_serializer {
    public static write(buffer: SerializerBase, value: FirstMeaningfulPaint): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationStartTime  = value.navigationStartTime
        if (valueHolderForNavigationStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNavigationStartTimeTmpValue  = valueHolderForNavigationStartTime!
            valueSerializer.writeInt64(valueHolderForNavigationStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFirstMeaningfulPaintTime  = value.firstMeaningfulPaintTime
        if (valueHolderForFirstMeaningfulPaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFirstMeaningfulPaintTimeTmpValue  = valueHolderForFirstMeaningfulPaintTime!
            valueSerializer.writeInt64(valueHolderForFirstMeaningfulPaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FirstMeaningfulPaint {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navigationStartTimeTmpBuf : int64 | undefined
        if ((navigationStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            navigationStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const navigationStartTimeTmpResult : int64 | undefined = navigationStartTimeTmpBuf
        const firstMeaningfulPaintTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let firstMeaningfulPaintTimeTmpBuf : int64 | undefined
        if ((firstMeaningfulPaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            firstMeaningfulPaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const firstMeaningfulPaintTimeTmpResult : int64 | undefined = firstMeaningfulPaintTimeTmpBuf
        let value : FirstMeaningfulPaint = ({navigationStartTime: navigationStartTimeTmpResult, firstMeaningfulPaintTime: firstMeaningfulPaintTimeTmpResult} as FirstMeaningfulPaint)
        return value
    }
}
export class FullScreenEnterEvent_serializer {
    public static write(buffer: SerializerBase, value: FullScreenEnterEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        FullScreenExitHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForVideoWidth  = value.videoWidth
        if (valueHolderForVideoWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVideoWidthTmpValue  = valueHolderForVideoWidth!
            valueSerializer.writeNumber(valueHolderForVideoWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVideoHeight  = value.videoHeight
        if (valueHolderForVideoHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVideoHeightTmpValue  = valueHolderForVideoHeight!
            valueSerializer.writeNumber(valueHolderForVideoHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FullScreenEnterEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : FullScreenExitHandler = (FullScreenExitHandler_serializer.read(valueDeserializer) as FullScreenExitHandler)
        const videoWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let videoWidthTmpBuf : number | undefined
        if ((videoWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            videoWidthTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const videoWidthTmpResult : number | undefined = videoWidthTmpBuf
        const videoHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let videoHeightTmpBuf : number | undefined
        if ((videoHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            videoHeightTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const videoHeightTmpResult : number | undefined = videoHeightTmpBuf
        let value : FullScreenEnterEvent = ({handler: handlerTmpResult, videoWidth: videoWidthTmpResult, videoHeight: videoHeightTmpResult} as FullScreenEnterEvent)
        return value
    }
}
export class Header_serializer {
    public static write(buffer: SerializerBase, value: Header): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHeaderKey  = value.headerKey
        valueSerializer.writeString(valueHolderForHeaderKey)
        const valueHolderForHeaderValue  = value.headerValue
        valueSerializer.writeString(valueHolderForHeaderValue)
    }
    public static read(buffer: DeserializerBase): Header {
        let valueDeserializer : DeserializerBase = buffer
        const headerKeyTmpResult : string = (valueDeserializer.readString() as string)
        const headerValueTmpResult : string = (valueDeserializer.readString() as string)
        let value : Header = ({headerKey: headerKeyTmpResult, headerValue: headerValueTmpResult} as Header)
        return value
    }
}
export class IntelligentTrackingPreventionDetails_serializer {
    public static write(buffer: SerializerBase, value: IntelligentTrackingPreventionDetails): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHost  = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForTrackerHost  = value.trackerHost
        valueSerializer.writeString(valueHolderForTrackerHost)
    }
    public static read(buffer: DeserializerBase): IntelligentTrackingPreventionDetails {
        let valueDeserializer : DeserializerBase = buffer
        const hostTmpResult : string = (valueDeserializer.readString() as string)
        const trackerHostTmpResult : string = (valueDeserializer.readString() as string)
        let value : IntelligentTrackingPreventionDetails = ({host: hostTmpResult, trackerHost: trackerHostTmpResult} as IntelligentTrackingPreventionDetails)
        return value
    }
}
export class JavaScriptProxy_serializer {
    public static write(buffer: SerializerBase, value: JavaScriptProxy): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForObject_  = value.object_
        valueSerializer.holdAndWriteObject(valueHolderForObject_)
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForMethodList  = value.methodList
        valueSerializer.writeInt32((valueHolderForMethodList.length).toInt())
        for (let valueHolderForMethodListCounterI = 0; valueHolderForMethodListCounterI < valueHolderForMethodList.length; valueHolderForMethodListCounterI++) {
            const valueHolderForMethodListTmpElement : string = valueHolderForMethodList[valueHolderForMethodListCounterI]
            valueSerializer.writeString(valueHolderForMethodListTmpElement)
        }
        const valueHolderForController  = value.controller
        webview_WebviewController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForAsyncMethodList  = value.asyncMethodList
        if (valueHolderForAsyncMethodList !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAsyncMethodListTmpValue  = valueHolderForAsyncMethodList!
            valueSerializer.writeInt32((valueHolderForAsyncMethodListTmpValue.length).toInt())
            for (let valueHolderForAsyncMethodListTmpValueCounterI = 0; valueHolderForAsyncMethodListTmpValueCounterI < valueHolderForAsyncMethodListTmpValue.length; valueHolderForAsyncMethodListTmpValueCounterI++) {
                const valueHolderForAsyncMethodListTmpValueTmpElement : string = valueHolderForAsyncMethodListTmpValue[valueHolderForAsyncMethodListTmpValueCounterI]
                valueSerializer.writeString(valueHolderForAsyncMethodListTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPermission  = value.permission
        if (valueHolderForPermission !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPermissionTmpValue  = valueHolderForPermission!
            valueSerializer.writeString(valueHolderForPermissionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): JavaScriptProxy {
        let valueDeserializer : DeserializerBase = buffer
        const object_TmpResult : Object = (valueDeserializer.readObject() as object)
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const methodListTmpBufLength : int32 = valueDeserializer.readInt32()
        let methodListTmpBuf : Array<string> = new Array<string>(methodListTmpBufLength)
        for (let methodListTmpBufBufCounterI = 0; methodListTmpBufBufCounterI < methodListTmpBufLength; methodListTmpBufBufCounterI++) {
            methodListTmpBuf[methodListTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const methodListTmpResult : Array<string> = methodListTmpBuf
        const controllerTmpResult : webview.WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const asyncMethodListTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let asyncMethodListTmpBuf : Array<string> | undefined
        if ((asyncMethodListTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const asyncMethodListTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let asyncMethodListTmpBuf_ : Array<string> = new Array<string>(asyncMethodListTmpBuf_Length)
            for (let asyncMethodListTmpBuf_BufCounterI = 0; asyncMethodListTmpBuf_BufCounterI < asyncMethodListTmpBuf_Length; asyncMethodListTmpBuf_BufCounterI++) {
                asyncMethodListTmpBuf_[asyncMethodListTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            asyncMethodListTmpBuf = asyncMethodListTmpBuf_
        }
        const asyncMethodListTmpResult : Array<string> | undefined = asyncMethodListTmpBuf
        const permissionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let permissionTmpBuf : string | undefined
        if ((permissionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            permissionTmpBuf = (valueDeserializer.readString() as string)
        }
        const permissionTmpResult : string | undefined = permissionTmpBuf
        let value : JavaScriptProxy = ({object_: object_TmpResult, name: nameTmpResult, methodList: methodListTmpResult, controller: controllerTmpResult, asyncMethodList: asyncMethodListTmpResult, permission: permissionTmpResult} as JavaScriptProxy)
        return value
    }
}
export class LargestContentfulPaint_serializer {
    public static write(buffer: SerializerBase, value: LargestContentfulPaint): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationStartTime  = value.navigationStartTime
        if (valueHolderForNavigationStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNavigationStartTimeTmpValue  = valueHolderForNavigationStartTime!
            valueSerializer.writeInt64(valueHolderForNavigationStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImagePaintTime  = value.largestImagePaintTime
        if (valueHolderForLargestImagePaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImagePaintTimeTmpValue  = valueHolderForLargestImagePaintTime!
            valueSerializer.writeInt64(valueHolderForLargestImagePaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestTextPaintTime  = value.largestTextPaintTime
        if (valueHolderForLargestTextPaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestTextPaintTimeTmpValue  = valueHolderForLargestTextPaintTime!
            valueSerializer.writeInt64(valueHolderForLargestTextPaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageBPP  = value.imageBPP
        if (valueHolderForImageBPP !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageBPPTmpValue  = valueHolderForImageBPP!
            valueSerializer.writeFloat64(valueHolderForImageBPPTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImageLoadStartTime  = value.largestImageLoadStartTime
        if (valueHolderForLargestImageLoadStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImageLoadStartTimeTmpValue  = valueHolderForLargestImageLoadStartTime!
            valueSerializer.writeInt64(valueHolderForLargestImageLoadStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImageLoadEndTime  = value.largestImageLoadEndTime
        if (valueHolderForLargestImageLoadEndTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImageLoadEndTimeTmpValue  = valueHolderForLargestImageLoadEndTime!
            valueSerializer.writeInt64(valueHolderForLargestImageLoadEndTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LargestContentfulPaint {
        let valueDeserializer : DeserializerBase = buffer
        const navigationStartTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navigationStartTimeTmpBuf : int64 | undefined
        if ((navigationStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            navigationStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const navigationStartTimeTmpResult : int64 | undefined = navigationStartTimeTmpBuf
        const largestImagePaintTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImagePaintTimeTmpBuf : int64 | undefined
        if ((largestImagePaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImagePaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImagePaintTimeTmpResult : int64 | undefined = largestImagePaintTimeTmpBuf
        const largestTextPaintTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestTextPaintTimeTmpBuf : int64 | undefined
        if ((largestTextPaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestTextPaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestTextPaintTimeTmpResult : int64 | undefined = largestTextPaintTimeTmpBuf
        const imageBPPTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageBPPTmpBuf : double | undefined
        if ((imageBPPTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageBPPTmpBuf = valueDeserializer.readFloat64()
        }
        const imageBPPTmpResult : double | undefined = imageBPPTmpBuf
        const largestImageLoadStartTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImageLoadStartTimeTmpBuf : int64 | undefined
        if ((largestImageLoadStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImageLoadStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImageLoadStartTimeTmpResult : int64 | undefined = largestImageLoadStartTimeTmpBuf
        const largestImageLoadEndTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let largestImageLoadEndTimeTmpBuf : int64 | undefined
        if ((largestImageLoadEndTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImageLoadEndTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImageLoadEndTimeTmpResult : int64 | undefined = largestImageLoadEndTimeTmpBuf
        let value : LargestContentfulPaint = ({navigationStartTime: navigationStartTimeTmpResult, largestImagePaintTime: largestImagePaintTimeTmpResult, largestTextPaintTime: largestTextPaintTimeTmpResult, imageBPP: imageBPPTmpResult, largestImageLoadStartTime: largestImageLoadStartTimeTmpResult, largestImageLoadEndTime: largestImageLoadEndTimeTmpResult} as LargestContentfulPaint)
        return value
    }
}
export class LoadCommittedDetails_serializer {
    public static write(buffer: SerializerBase, value: LoadCommittedDetails): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIsMainFrame  = value.isMainFrame
        valueSerializer.writeBoolean(valueHolderForIsMainFrame)
        const valueHolderForIsSameDocument  = value.isSameDocument
        valueSerializer.writeBoolean(valueHolderForIsSameDocument)
        const valueHolderForDidReplaceEntry  = value.didReplaceEntry
        valueSerializer.writeBoolean(valueHolderForDidReplaceEntry)
        const valueHolderForNavigationType  = value.navigationType
        valueSerializer.writeInt32(TypeChecker.WebNavigationType_ToNumeric(valueHolderForNavigationType))
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): LoadCommittedDetails {
        let valueDeserializer : DeserializerBase = buffer
        const isMainFrameTmpResult : boolean = valueDeserializer.readBoolean()
        const isSameDocumentTmpResult : boolean = valueDeserializer.readBoolean()
        const didReplaceEntryTmpResult : boolean = valueDeserializer.readBoolean()
        const navigationTypeTmpResult : WebNavigationType = TypeChecker.WebNavigationType_FromNumeric(valueDeserializer.readInt32())
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        let value : LoadCommittedDetails = ({isMainFrame: isMainFrameTmpResult, isSameDocument: isSameDocumentTmpResult, didReplaceEntry: didReplaceEntryTmpResult, navigationType: navigationTypeTmpResult, url: urlTmpResult} as LoadCommittedDetails)
        return value
    }
}
export class NativeEmbedVisibilityInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedVisibilityInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForVisibility  = value.visibility
        valueSerializer.writeBoolean(valueHolderForVisibility)
        const valueHolderForEmbedId  = value.embedId
        valueSerializer.writeString(valueHolderForEmbedId)
    }
    public static read(buffer: DeserializerBase): NativeEmbedVisibilityInfo {
        let valueDeserializer : DeserializerBase = buffer
        const visibilityTmpResult : boolean = valueDeserializer.readBoolean()
        const embedIdTmpResult : string = (valueDeserializer.readString() as string)
        let value : NativeEmbedVisibilityInfo = ({visibility: visibilityTmpResult, embedId: embedIdTmpResult} as NativeEmbedVisibilityInfo)
        return value
    }
}
export class NestedScrollOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: NestedScrollOptionsExt): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScrollUp  = value.scrollUp
        if (valueHolderForScrollUp !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollUpTmpValue  = (valueHolderForScrollUp as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(valueHolderForScrollUpTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollDown  = value.scrollDown
        if (valueHolderForScrollDown !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollDownTmpValue  = (valueHolderForScrollDown as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(valueHolderForScrollDownTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollRight  = value.scrollRight
        if (valueHolderForScrollRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollRightTmpValue  = (valueHolderForScrollRight as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(valueHolderForScrollRightTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollLeft  = value.scrollLeft
        if (valueHolderForScrollLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollLeftTmpValue  = (valueHolderForScrollLeft as NestedScrollMode)
            valueSerializer.writeInt32(TypeChecker.NestedScrollMode_ToNumeric(valueHolderForScrollLeftTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NestedScrollOptionsExt {
        let valueDeserializer : DeserializerBase = buffer
        const scrollUpTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollUpTmpBuf : NestedScrollMode | undefined
        if ((scrollUpTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollUpTmpBuf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollUpTmpResult : NestedScrollMode | undefined = scrollUpTmpBuf
        const scrollDownTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollDownTmpBuf : NestedScrollMode | undefined
        if ((scrollDownTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollDownTmpBuf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollDownTmpResult : NestedScrollMode | undefined = scrollDownTmpBuf
        const scrollRightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollRightTmpBuf : NestedScrollMode | undefined
        if ((scrollRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollRightTmpBuf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollRightTmpResult : NestedScrollMode | undefined = scrollRightTmpBuf
        const scrollLeftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollLeftTmpBuf : NestedScrollMode | undefined
        if ((scrollLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollLeftTmpBuf = TypeChecker.NestedScrollMode_FromNumeric(valueDeserializer.readInt32())
        }
        const scrollLeftTmpResult : NestedScrollMode | undefined = scrollLeftTmpBuf
        let value : NestedScrollOptionsExt = ({scrollUp: scrollUpTmpResult, scrollDown: scrollDownTmpResult, scrollRight: scrollRightTmpResult, scrollLeft: scrollLeftTmpResult} as NestedScrollOptionsExt)
        return value
    }
}
export class OnAlertEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAlertEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult  = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnAlertEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const resultTmpResult : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnAlertEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult} as OnAlertEvent)
        return value
    }
}
export class OnBeforeUnloadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnBeforeUnloadEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult  = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnBeforeUnloadEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const resultTmpResult : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnBeforeUnloadEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult} as OnBeforeUnloadEvent)
        return value
    }
}
export class OnClientAuthenticationEvent_serializer {
    public static write(buffer: SerializerBase, value: OnClientAuthenticationEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        ClientAuthenticationHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForHost  = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForPort  = value.port
        valueSerializer.writeNumber(valueHolderForPort)
        const valueHolderForKeyTypes  = value.keyTypes
        valueSerializer.writeInt32((valueHolderForKeyTypes.length).toInt())
        for (let valueHolderForKeyTypesCounterI = 0; valueHolderForKeyTypesCounterI < valueHolderForKeyTypes.length; valueHolderForKeyTypesCounterI++) {
            const valueHolderForKeyTypesTmpElement : string = valueHolderForKeyTypes[valueHolderForKeyTypesCounterI]
            valueSerializer.writeString(valueHolderForKeyTypesTmpElement)
        }
        const valueHolderForIssuers  = value.issuers
        valueSerializer.writeInt32((valueHolderForIssuers.length).toInt())
        for (let valueHolderForIssuersCounterI = 0; valueHolderForIssuersCounterI < valueHolderForIssuers.length; valueHolderForIssuersCounterI++) {
            const valueHolderForIssuersTmpElement : string = valueHolderForIssuers[valueHolderForIssuersCounterI]
            valueSerializer.writeString(valueHolderForIssuersTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): OnClientAuthenticationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : ClientAuthenticationHandler = (ClientAuthenticationHandler_serializer.read(valueDeserializer) as ClientAuthenticationHandler)
        const hostTmpResult : string = (valueDeserializer.readString() as string)
        const portTmpResult : number = (valueDeserializer.readNumber() as number)
        const keyTypesTmpBufLength : int32 = valueDeserializer.readInt32()
        let keyTypesTmpBuf : Array<string> = new Array<string>(keyTypesTmpBufLength)
        for (let keyTypesTmpBufBufCounterI = 0; keyTypesTmpBufBufCounterI < keyTypesTmpBufLength; keyTypesTmpBufBufCounterI++) {
            keyTypesTmpBuf[keyTypesTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const keyTypesTmpResult : Array<string> = keyTypesTmpBuf
        const issuersTmpBufLength : int32 = valueDeserializer.readInt32()
        let issuersTmpBuf : Array<string> = new Array<string>(issuersTmpBufLength)
        for (let issuersTmpBufBufCounterI = 0; issuersTmpBufBufCounterI < issuersTmpBufLength; issuersTmpBufBufCounterI++) {
            issuersTmpBuf[issuersTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const issuersTmpResult : Array<string> = issuersTmpBuf
        let value : OnClientAuthenticationEvent = ({handler: handlerTmpResult, host: hostTmpResult, port: portTmpResult, keyTypes: keyTypesTmpResult, issuers: issuersTmpResult} as OnClientAuthenticationEvent)
        return value
    }
}
export class OnConfirmEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConfirmEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult  = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnConfirmEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const resultTmpResult : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnConfirmEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult} as OnConfirmEvent)
        return value
    }
}
export class OnContextMenuShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnContextMenuShowEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForParam  = value.param
        WebContextMenuParam_serializer.write(valueSerializer, valueHolderForParam)
        const valueHolderForResult  = value.result
        WebContextMenuResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnContextMenuShowEvent {
        let valueDeserializer : DeserializerBase = buffer
        const paramTmpResult : WebContextMenuParam = (WebContextMenuParam_serializer.read(valueDeserializer) as WebContextMenuParam)
        const resultTmpResult : WebContextMenuResult = (WebContextMenuResult_serializer.read(valueDeserializer) as WebContextMenuResult)
        let value : OnContextMenuShowEvent = ({param: paramTmpResult, result: resultTmpResult} as OnContextMenuShowEvent)
        return value
    }
}
export class OnDownloadStartEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDownloadStartEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForUserAgent  = value.userAgent
        valueSerializer.writeString(valueHolderForUserAgent)
        const valueHolderForContentDisposition  = value.contentDisposition
        valueSerializer.writeString(valueHolderForContentDisposition)
        const valueHolderForMimetype  = value.mimetype
        valueSerializer.writeString(valueHolderForMimetype)
        const valueHolderForContentLength  = value.contentLength
        valueSerializer.writeNumber(valueHolderForContentLength)
    }
    public static read(buffer: DeserializerBase): OnDownloadStartEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const userAgentTmpResult : string = (valueDeserializer.readString() as string)
        const contentDispositionTmpResult : string = (valueDeserializer.readString() as string)
        const mimetypeTmpResult : string = (valueDeserializer.readString() as string)
        const contentLengthTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : OnDownloadStartEvent = ({url: urlTmpResult, userAgent: userAgentTmpResult, contentDisposition: contentDispositionTmpResult, mimetype: mimetypeTmpResult, contentLength: contentLengthTmpResult} as OnDownloadStartEvent)
        return value
    }
}
export class OnErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnErrorReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRequest  = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
        const valueHolderForError  = value.error
        WebResourceError_serializer.write(valueSerializer, valueHolderForError)
    }
    public static read(buffer: DeserializerBase): OnErrorReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const requestTmpResult : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const errorTmpResult : WebResourceError = (WebResourceError_serializer.read(valueDeserializer) as WebResourceError)
        let value : OnErrorReceiveEvent = ({request: requestTmpResult, error: errorTmpResult} as OnErrorReceiveEvent)
        return value
    }
}
export class OnGeolocationShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnGeolocationShowEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOrigin  = value.origin
        valueSerializer.writeString(valueHolderForOrigin)
        const valueHolderForGeolocation  = value.geolocation
        JsGeolocation_serializer.write(valueSerializer, valueHolderForGeolocation)
    }
    public static read(buffer: DeserializerBase): OnGeolocationShowEvent {
        let valueDeserializer : DeserializerBase = buffer
        const originTmpResult : string = (valueDeserializer.readString() as string)
        const geolocationTmpResult : JsGeolocation = (JsGeolocation_serializer.read(valueDeserializer) as JsGeolocation)
        let value : OnGeolocationShowEvent = ({origin: originTmpResult, geolocation: geolocationTmpResult} as OnGeolocationShowEvent)
        return value
    }
}
export class OnHttpAuthRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpAuthRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        HttpAuthHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForHost  = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForRealm  = value.realm
        valueSerializer.writeString(valueHolderForRealm)
    }
    public static read(buffer: DeserializerBase): OnHttpAuthRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : HttpAuthHandler = (HttpAuthHandler_serializer.read(valueDeserializer) as HttpAuthHandler)
        const hostTmpResult : string = (valueDeserializer.readString() as string)
        const realmTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnHttpAuthRequestEvent = ({handler: handlerTmpResult, host: hostTmpResult, realm: realmTmpResult} as OnHttpAuthRequestEvent)
        return value
    }
}
export class OnHttpErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpErrorReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRequest  = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
        const valueHolderForResponse  = value.response
        WebResourceResponse_serializer.write(valueSerializer, valueHolderForResponse)
    }
    public static read(buffer: DeserializerBase): OnHttpErrorReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const requestTmpResult : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const responseTmpResult : WebResourceResponse = (WebResourceResponse_serializer.read(valueDeserializer) as WebResourceResponse)
        let value : OnHttpErrorReceiveEvent = ({request: requestTmpResult, response: responseTmpResult} as OnHttpErrorReceiveEvent)
        return value
    }
}
export class OnInterceptRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnInterceptRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRequest  = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
    }
    public static read(buffer: DeserializerBase): OnInterceptRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const requestTmpResult : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value : OnInterceptRequestEvent = ({request: requestTmpResult} as OnInterceptRequestEvent)
        return value
    }
}
export class OnLoadInterceptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnLoadInterceptEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForData  = value.data
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForData)
    }
    public static read(buffer: DeserializerBase): OnLoadInterceptEvent {
        let valueDeserializer : DeserializerBase = buffer
        const dataTmpResult : WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value : OnLoadInterceptEvent = ({data: dataTmpResult} as OnLoadInterceptEvent)
        return value
    }
}
export class OnPageBeginEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageBeginEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageBeginEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnPageBeginEvent = ({url: urlTmpResult} as OnPageBeginEvent)
        return value
    }
}
export class OnPageEndEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageEndEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageEndEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnPageEndEvent = ({url: urlTmpResult} as OnPageEndEvent)
        return value
    }
}
export class OnPageVisibleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageVisibleEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageVisibleEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnPageVisibleEvent = ({url: urlTmpResult} as OnPageVisibleEvent)
        return value
    }
}
export class OnPermissionRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPermissionRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRequest  = value.request
        PermissionRequest_serializer.write(valueSerializer, valueHolderForRequest)
    }
    public static read(buffer: DeserializerBase): OnPermissionRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const requestTmpResult : PermissionRequest = (PermissionRequest_serializer.read(valueDeserializer) as PermissionRequest)
        let value : OnPermissionRequestEvent = ({request: requestTmpResult} as OnPermissionRequestEvent)
        return value
    }
}
export class OnPromptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPromptEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForValue  = value.value
        valueSerializer.writeString(valueHolderForValue)
        const valueHolderForResult  = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnPromptEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : string = (valueDeserializer.readString() as string)
        const resultTmpResult : JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value : OnPromptEvent = ({url: urlTmpResult, message: messageTmpResult, value: valueTmpResult, result: resultTmpResult} as OnPromptEvent)
        return value
    }
}
export class OnRefreshAccessedHistoryEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRefreshAccessedHistoryEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForIsRefreshed  = value.isRefreshed
        valueSerializer.writeBoolean(valueHolderForIsRefreshed)
    }
    public static read(buffer: DeserializerBase): OnRefreshAccessedHistoryEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const isRefreshedTmpResult : boolean = valueDeserializer.readBoolean()
        let value : OnRefreshAccessedHistoryEvent = ({url: urlTmpResult, isRefreshed: isRefreshedTmpResult} as OnRefreshAccessedHistoryEvent)
        return value
    }
}
export class OnRenderExitedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRenderExitedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRenderExitReason  = value.renderExitReason
        valueSerializer.writeInt32(TypeChecker.RenderExitReason_ToNumeric(valueHolderForRenderExitReason))
    }
    public static read(buffer: DeserializerBase): OnRenderExitedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const renderExitReasonTmpResult : RenderExitReason = TypeChecker.RenderExitReason_FromNumeric(valueDeserializer.readInt32())
        let value : OnRenderExitedEvent = ({renderExitReason: renderExitReasonTmpResult} as OnRenderExitedEvent)
        return value
    }
}
export class OnResourceLoadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnResourceLoadEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnResourceLoadEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnResourceLoadEvent = ({url: urlTmpResult} as OnResourceLoadEvent)
        return value
    }
}
export class OnScreenCaptureRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScreenCaptureRequestEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        ScreenCaptureHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnScreenCaptureRequestEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : ScreenCaptureHandler = (ScreenCaptureHandler_serializer.read(valueDeserializer) as ScreenCaptureHandler)
        let value : OnScreenCaptureRequestEvent = ({handler: handlerTmpResult} as OnScreenCaptureRequestEvent)
        return value
    }
}
export class OnSslErrorEventReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSslErrorEventReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        SslErrorHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForError  = value.error
        valueSerializer.writeInt32(TypeChecker.SslError_ToNumeric(valueHolderForError))
        const valueHolderForCertChainData  = value.certChainData
        if (valueHolderForCertChainData !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCertChainDataTmpValue  = valueHolderForCertChainData!
            valueSerializer.writeInt32((valueHolderForCertChainDataTmpValue.length).toInt())
            for (let valueHolderForCertChainDataTmpValueCounterI = 0; valueHolderForCertChainDataTmpValueCounterI < valueHolderForCertChainDataTmpValue.length; valueHolderForCertChainDataTmpValueCounterI++) {
                const valueHolderForCertChainDataTmpValueTmpElement : NativeBuffer = valueHolderForCertChainDataTmpValue[valueHolderForCertChainDataTmpValueCounterI]
                valueSerializer.writeBuffer(valueHolderForCertChainDataTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OnSslErrorEventReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const errorTmpResult : SslError = TypeChecker.SslError_FromNumeric(valueDeserializer.readInt32())
        const certChainDataTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let certChainDataTmpBuf : Array<NativeBuffer> | undefined
        if ((certChainDataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const certChainDataTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let certChainDataTmpBuf_ : Array<NativeBuffer> = new Array<NativeBuffer>(certChainDataTmpBuf_Length)
            for (let certChainDataTmpBuf_BufCounterI = 0; certChainDataTmpBuf_BufCounterI < certChainDataTmpBuf_Length; certChainDataTmpBuf_BufCounterI++) {
                certChainDataTmpBuf_[certChainDataTmpBuf_BufCounterI] = (valueDeserializer.readBuffer() as NativeBuffer)
            }
            certChainDataTmpBuf = certChainDataTmpBuf_
        }
        const certChainDataTmpResult : Array<NativeBuffer> | undefined = certChainDataTmpBuf
        let value : OnSslErrorEventReceiveEvent = ({handler: handlerTmpResult, error: errorTmpResult, certChainData: certChainDataTmpResult} as OnSslErrorEventReceiveEvent)
        return value
    }
}
export class OnTitleReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTitleReceiveEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        valueSerializer.writeString(valueHolderForTitle)
    }
    public static read(buffer: DeserializerBase): OnTitleReceiveEvent {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpResult : string = (valueDeserializer.readString() as string)
        let value : OnTitleReceiveEvent = ({title: titleTmpResult} as OnTitleReceiveEvent)
        return value
    }
}
export class OnTouchIconUrlReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTouchIconUrlReceivedEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForPrecomposed  = value.precomposed
        valueSerializer.writeBoolean(valueHolderForPrecomposed)
    }
    public static read(buffer: DeserializerBase): OnTouchIconUrlReceivedEvent {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const precomposedTmpResult : boolean = valueDeserializer.readBoolean()
        let value : OnTouchIconUrlReceivedEvent = ({url: urlTmpResult, precomposed: precomposedTmpResult} as OnTouchIconUrlReceivedEvent)
        return value
    }
}
export class OnWindowNewEvent_serializer {
    public static write(buffer: SerializerBase, value: OnWindowNewEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIsAlert  = value.isAlert
        valueSerializer.writeBoolean(valueHolderForIsAlert)
        const valueHolderForIsUserTrigger  = value.isUserTrigger
        valueSerializer.writeBoolean(valueHolderForIsUserTrigger)
        const valueHolderForTargetUrl  = value.targetUrl
        valueSerializer.writeString(valueHolderForTargetUrl)
        const valueHolderForHandler  = value.handler
        ControllerHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnWindowNewEvent {
        let valueDeserializer : DeserializerBase = buffer
        const isAlertTmpResult : boolean = valueDeserializer.readBoolean()
        const isUserTriggerTmpResult : boolean = valueDeserializer.readBoolean()
        const targetUrlTmpResult : string = (valueDeserializer.readString() as string)
        const handlerTmpResult : ControllerHandler = (ControllerHandler_serializer.read(valueDeserializer) as ControllerHandler)
        let value : OnWindowNewEvent = ({isAlert: isAlertTmpResult, isUserTrigger: isUserTriggerTmpResult, targetUrl: targetUrlTmpResult, handler: handlerTmpResult} as OnWindowNewEvent)
        return value
    }
}
export class RenderProcessNotRespondingData_serializer {
    public static write(buffer: SerializerBase, value: RenderProcessNotRespondingData): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForJsStack  = value.jsStack
        valueSerializer.writeString(valueHolderForJsStack)
        const valueHolderForPid  = value.pid
        valueSerializer.writeInt32(valueHolderForPid)
        const valueHolderForReason  = value.reason
        valueSerializer.writeInt32(TypeChecker.RenderProcessNotRespondingReason_ToNumeric(valueHolderForReason))
    }
    public static read(buffer: DeserializerBase): RenderProcessNotRespondingData {
        let valueDeserializer : DeserializerBase = buffer
        const jsStackTmpResult : string = (valueDeserializer.readString() as string)
        const pidTmpResult : int32 = valueDeserializer.readInt32()
        const reasonTmpResult : RenderProcessNotRespondingReason = TypeChecker.RenderProcessNotRespondingReason_FromNumeric(valueDeserializer.readInt32())
        let value : RenderProcessNotRespondingData = ({jsStack: jsStackTmpResult, pid: pidTmpResult, reason: reasonTmpResult} as RenderProcessNotRespondingData)
        return value
    }
}
export class ScreenCaptureConfig_serializer {
    public static write(buffer: SerializerBase, value: ScreenCaptureConfig): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCaptureMode  = value.captureMode
        valueSerializer.writeInt32(TypeChecker.WebCaptureMode_ToNumeric(valueHolderForCaptureMode))
    }
    public static read(buffer: DeserializerBase): ScreenCaptureConfig {
        let valueDeserializer : DeserializerBase = buffer
        const captureModeTmpResult : WebCaptureMode = TypeChecker.WebCaptureMode_FromNumeric(valueDeserializer.readInt32())
        let value : ScreenCaptureConfig = ({captureMode: captureModeTmpResult} as ScreenCaptureConfig)
        return value
    }
}
export class ScriptItem_serializer {
    public static write(buffer: SerializerBase, value: ScriptItem): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScript  = value.script
        valueSerializer.writeString(valueHolderForScript)
        const valueHolderForScriptRules  = value.scriptRules
        valueSerializer.writeInt32((valueHolderForScriptRules.length).toInt())
        for (let valueHolderForScriptRulesCounterI = 0; valueHolderForScriptRulesCounterI < valueHolderForScriptRules.length; valueHolderForScriptRulesCounterI++) {
            const valueHolderForScriptRulesTmpElement : string = valueHolderForScriptRules[valueHolderForScriptRulesCounterI]
            valueSerializer.writeString(valueHolderForScriptRulesTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): ScriptItem {
        let valueDeserializer : DeserializerBase = buffer
        const scriptTmpResult : string = (valueDeserializer.readString() as string)
        const scriptRulesTmpBufLength : int32 = valueDeserializer.readInt32()
        let scriptRulesTmpBuf : Array<string> = new Array<string>(scriptRulesTmpBufLength)
        for (let scriptRulesTmpBufBufCounterI = 0; scriptRulesTmpBufBufCounterI < scriptRulesTmpBufLength; scriptRulesTmpBufBufCounterI++) {
            scriptRulesTmpBuf[scriptRulesTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const scriptRulesTmpResult : Array<string> = scriptRulesTmpBuf
        let value : ScriptItem = ({script: scriptTmpResult, scriptRules: scriptRulesTmpResult} as ScriptItem)
        return value
    }
}
export class SelectionMenuOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: SelectionMenuOptionsExt): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnAppear  = value.onAppear
        if (valueHolderForOnAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAppearTmpValue  = valueHolderForOnAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDisappear  = value.onDisappear
        if (valueHolderForOnDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDisappearTmpValue  = valueHolderForOnDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreview  = value.preview
        if (valueHolderForPreview !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTmpValue  = valueHolderForPreview!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForPreviewTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMenuType  = value.menuType
        if (valueHolderForMenuType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMenuTypeTmpValue  = (valueHolderForMenuType as MenuType)
            valueSerializer.writeInt32(TypeChecker.MenuType_ToNumeric(valueHolderForMenuTypeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectionMenuOptionsExt {
        let valueDeserializer : DeserializerBase = buffer
        const onAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAppearTmpBuf : (() => void) | undefined
        if ((onAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onAppearTmpBuf = ():void => {
                const onAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAppearTmpBuf_BufArgsSerializer.writeInt32(onAppearTmpBuf_BufResource.resourceId);
                onAppearTmpBuf_BufArgsSerializer.writePointer(onAppearTmpBuf_BufCall);
                onAppearTmpBuf_BufArgsSerializer.writePointer(onAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onAppearTmpBuf_BufArgsSerializer.asBuffer(), onAppearTmpBuf_BufArgsSerializer.length());
                onAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onAppearTmpResult : (() => void) | undefined = onAppearTmpBuf
        const onDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDisappearTmpBuf : (() => void) | undefined
        if ((onDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDisappearTmpBuf = ():void => {
                const onDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDisappearTmpBuf_BufArgsSerializer.writeInt32(onDisappearTmpBuf_BufResource.resourceId);
                onDisappearTmpBuf_BufArgsSerializer.writePointer(onDisappearTmpBuf_BufCall);
                onDisappearTmpBuf_BufArgsSerializer.writePointer(onDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDisappearTmpBuf_BufArgsSerializer.length());
                onDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDisappearTmpResult : (() => void) | undefined = onDisappearTmpBuf
        const previewTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewTmpBuf : CustomBuilder | undefined
        if ((previewTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const previewTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const previewTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const previewTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            previewTmpBuf = ():void => {
                const previewTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                previewTmpBuf_BufArgsSerializer.writeInt32(previewTmpBuf_BufResource.resourceId);
                previewTmpBuf_BufArgsSerializer.writePointer(previewTmpBuf_BufCall);
                previewTmpBuf_BufArgsSerializer.writePointer(previewTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(737226752, previewTmpBuf_BufArgsSerializer.asBuffer(), previewTmpBuf_BufArgsSerializer.length());
                previewTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const previewTmpResult : CustomBuilder | undefined = previewTmpBuf
        const menuTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let menuTypeTmpBuf : MenuType | undefined
        if ((menuTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            menuTypeTmpBuf = TypeChecker.MenuType_FromNumeric(valueDeserializer.readInt32())
        }
        const menuTypeTmpResult : MenuType | undefined = menuTypeTmpBuf
        let value : SelectionMenuOptionsExt = ({onAppear: onAppearTmpResult, onDisappear: onDisappearTmpResult, preview: previewTmpResult, menuType: menuTypeTmpResult} as SelectionMenuOptionsExt)
        return value
    }
}
export class SslErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: SslErrorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHandler  = value.handler
        SslErrorHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForError  = value.error
        valueSerializer.writeInt32(TypeChecker.SslError_ToNumeric(valueHolderForError))
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForOriginalUrl  = value.originalUrl
        valueSerializer.writeString(valueHolderForOriginalUrl)
        const valueHolderForReferrer  = value.referrer
        valueSerializer.writeString(valueHolderForReferrer)
        const valueHolderForIsFatalError  = value.isFatalError
        valueSerializer.writeBoolean(valueHolderForIsFatalError)
        const valueHolderForIsMainFrame  = value.isMainFrame
        valueSerializer.writeBoolean(valueHolderForIsMainFrame)
    }
    public static read(buffer: DeserializerBase): SslErrorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const handlerTmpResult : SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const errorTmpResult : SslError = TypeChecker.SslError_FromNumeric(valueDeserializer.readInt32())
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const originalUrlTmpResult : string = (valueDeserializer.readString() as string)
        const referrerTmpResult : string = (valueDeserializer.readString() as string)
        const isFatalErrorTmpResult : boolean = valueDeserializer.readBoolean()
        const isMainFrameTmpResult : boolean = valueDeserializer.readBoolean()
        let value : SslErrorEvent = ({handler: handlerTmpResult, error: errorTmpResult, url: urlTmpResult, originalUrl: originalUrlTmpResult, referrer: referrerTmpResult, isFatalError: isFatalErrorTmpResult, isMainFrame: isMainFrameTmpResult} as SslErrorEvent)
        return value
    }
}
export class WebKeyboardCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardCallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForController  = value.controller
        WebKeyboardController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForAttributes  = value.attributes
        valueSerializer.writeInt32((valueHolderForAttributes.size).toInt())
        for (const pair of valueHolderForAttributes) {
            const valueHolderForAttributesKeyVar = pair[0]
            const valueHolderForAttributesValueVar = pair[1]
            valueSerializer.writeString(valueHolderForAttributesKeyVar)
            valueSerializer.writeString(valueHolderForAttributesValueVar)
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardCallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const controllerTmpResult : WebKeyboardController = (WebKeyboardController_serializer.read(valueDeserializer) as WebKeyboardController)
        const attributesTmpBufSizeVar : int32 = valueDeserializer.readInt32()
        let attributesTmpBuf : Map<string, string> = new Map<string, string>()
        // TODO: TS map resize
        for (let attributesTmpBufIVar = 0; attributesTmpBufIVar < attributesTmpBufSizeVar; attributesTmpBufIVar++) {
            const attributesTmpBufKeyVar : string = (valueDeserializer.readString() as string)
            const attributesTmpBufValueVar : string = (valueDeserializer.readString() as string)
            attributesTmpBuf.set(attributesTmpBufKeyVar, attributesTmpBufValueVar)
        }
        const attributesTmpResult : Map<string, string> = attributesTmpBuf
        let value : WebKeyboardCallbackInfo = ({controller: controllerTmpResult, attributes: attributesTmpResult} as WebKeyboardCallbackInfo)
        return value
    }
}
export class WebKeyboardOptions_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUseSystemKeyboard  = value.useSystemKeyboard
        valueSerializer.writeBoolean(valueHolderForUseSystemKeyboard)
        const valueHolderForEnterKeyType  = value.enterKeyType
        if (valueHolderForEnterKeyType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnterKeyTypeTmpValue  = valueHolderForEnterKeyType!
            valueSerializer.writeInt32(valueHolderForEnterKeyTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCustomKeyboard  = value.customKeyboard
        if (valueHolderForCustomKeyboard !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomKeyboardTmpValue  = valueHolderForCustomKeyboard!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForCustomKeyboardTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardOptions {
        let valueDeserializer : DeserializerBase = buffer
        const useSystemKeyboardTmpResult : boolean = valueDeserializer.readBoolean()
        const enterKeyTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enterKeyTypeTmpBuf : int32 | undefined
        if ((enterKeyTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enterKeyTypeTmpBuf = valueDeserializer.readInt32()
        }
        const enterKeyTypeTmpResult : int32 | undefined = enterKeyTypeTmpBuf
        const customKeyboardTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customKeyboardTmpBuf : CustomBuilder | undefined
        if ((customKeyboardTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const customKeyboardTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const customKeyboardTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const customKeyboardTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            customKeyboardTmpBuf = ():void => {
                const customKeyboardTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                customKeyboardTmpBuf_BufArgsSerializer.writeInt32(customKeyboardTmpBuf_BufResource.resourceId);
                customKeyboardTmpBuf_BufArgsSerializer.writePointer(customKeyboardTmpBuf_BufCall);
                customKeyboardTmpBuf_BufArgsSerializer.writePointer(customKeyboardTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(737226752, customKeyboardTmpBuf_BufArgsSerializer.asBuffer(), customKeyboardTmpBuf_BufArgsSerializer.length());
                customKeyboardTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const customKeyboardTmpResult : CustomBuilder | undefined = customKeyboardTmpBuf
        let value : WebKeyboardOptions = ({useSystemKeyboard: useSystemKeyboardTmpResult, enterKeyType: enterKeyTypeTmpResult, customKeyboard: customKeyboardTmpResult} as WebKeyboardOptions)
        return value
    }
}
export class WebMediaOptions_serializer {
    public static write(buffer: SerializerBase, value: WebMediaOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForResumeInterval  = value.resumeInterval
        if (valueHolderForResumeInterval !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResumeIntervalTmpValue  = valueHolderForResumeInterval!
            valueSerializer.writeInt32(valueHolderForResumeIntervalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAudioExclusive  = value.audioExclusive
        if (valueHolderForAudioExclusive !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAudioExclusiveTmpValue  = valueHolderForAudioExclusive!
            valueSerializer.writeBoolean(valueHolderForAudioExclusiveTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAudioSessionType  = value.audioSessionType
        if (valueHolderForAudioSessionType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAudioSessionTypeTmpValue  = (valueHolderForAudioSessionType as AudioSessionType)
            valueSerializer.writeInt32(TypeChecker.AudioSessionType_ToNumeric(valueHolderForAudioSessionTypeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebMediaOptions {
        let valueDeserializer : DeserializerBase = buffer
        const resumeIntervalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let resumeIntervalTmpBuf : int32 | undefined
        if ((resumeIntervalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            resumeIntervalTmpBuf = valueDeserializer.readInt32()
        }
        const resumeIntervalTmpResult : int32 | undefined = resumeIntervalTmpBuf
        const audioExclusiveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let audioExclusiveTmpBuf : boolean | undefined
        if ((audioExclusiveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            audioExclusiveTmpBuf = valueDeserializer.readBoolean()
        }
        const audioExclusiveTmpResult : boolean | undefined = audioExclusiveTmpBuf
        const audioSessionTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let audioSessionTypeTmpBuf : AudioSessionType | undefined
        if ((audioSessionTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            audioSessionTypeTmpBuf = TypeChecker.AudioSessionType_FromNumeric(valueDeserializer.readInt32())
        }
        const audioSessionTypeTmpResult : AudioSessionType | undefined = audioSessionTypeTmpBuf
        let value : WebMediaOptions = ({resumeInterval: resumeIntervalTmpResult, audioExclusive: audioExclusiveTmpResult, audioSessionType: audioSessionTypeTmpResult} as WebMediaOptions)
        return value
    }
}
export class WebOptions_serializer {
    public static write(buffer: SerializerBase, value: WebOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForSrcForIdx0  = valueHolderForSrc as string
            valueSerializer.writeString(valueHolderForSrcForIdx0)
        } else if (valueHolderForSrc instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForSrcForIdx1  = valueHolderForSrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSrcForIdx1)
        }
        const valueHolderForController  = value.controller
        webview_WebviewController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForRenderMode  = value.renderMode
        if (valueHolderForRenderMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRenderModeTmpValue  = (valueHolderForRenderMode as RenderMode)
            valueSerializer.writeInt32(TypeChecker.RenderMode_ToNumeric(valueHolderForRenderModeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIncognitoMode  = value.incognitoMode
        if (valueHolderForIncognitoMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIncognitoModeTmpValue  = valueHolderForIncognitoMode!
            valueSerializer.writeBoolean(valueHolderForIncognitoModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSharedRenderProcessToken  = value.sharedRenderProcessToken
        if (valueHolderForSharedRenderProcessToken !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSharedRenderProcessTokenTmpValue  = valueHolderForSharedRenderProcessToken!
            valueSerializer.writeString(valueHolderForSharedRenderProcessTokenTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebOptions {
        let valueDeserializer : DeserializerBase = buffer
        const srcTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let srcTmpBuf : string | Resource | undefined
        if (srcTmpBufUnionSelector == (0).toChar()) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        } else if (srcTmpBufUnionSelector == (1).toChar()) {
            srcTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for srcTmpBuf has to be chosen through deserialisation.")
        }
        const srcTmpResult : string | Resource = (srcTmpBuf as string | Resource)
        const controllerTmpResult : webview.WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const renderModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let renderModeTmpBuf : RenderMode | undefined
        if ((renderModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            renderModeTmpBuf = TypeChecker.RenderMode_FromNumeric(valueDeserializer.readInt32())
        }
        const renderModeTmpResult : RenderMode | undefined = renderModeTmpBuf
        const incognitoModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let incognitoModeTmpBuf : boolean | undefined
        if ((incognitoModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            incognitoModeTmpBuf = valueDeserializer.readBoolean()
        }
        const incognitoModeTmpResult : boolean | undefined = incognitoModeTmpBuf
        const sharedRenderProcessTokenTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sharedRenderProcessTokenTmpBuf : string | undefined
        if ((sharedRenderProcessTokenTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sharedRenderProcessTokenTmpBuf = (valueDeserializer.readString() as string)
        }
        const sharedRenderProcessTokenTmpResult : string | undefined = sharedRenderProcessTokenTmpBuf
        let value : WebOptions = ({src: srcTmpResult, controller: controllerTmpResult, renderMode: renderModeTmpResult, incognitoMode: incognitoModeTmpResult, sharedRenderProcessToken: sharedRenderProcessTokenTmpResult} as WebOptions)
        return value
    }
}
export class NativeEmbedInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        if (valueHolderForId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIdTmpValue  = valueHolderForId!
            valueSerializer.writeString(valueHolderForIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = valueHolderForType!
            valueSerializer.writeString(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue  = valueHolderForSrc!
            valueSerializer.writeString(valueHolderForSrcTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            Position_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            valueSerializer.writeInt32(valueHolderForWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            valueSerializer.writeInt32(valueHolderForHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUrl  = value.url
        if (valueHolderForUrl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlTmpValue  = valueHolderForUrl!
            valueSerializer.writeString(valueHolderForUrlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTag  = value.tag
        if (valueHolderForTag !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTagTmpValue  = valueHolderForTag!
            valueSerializer.writeString(valueHolderForTagTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParams  = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue  = valueHolderForParams!
            valueSerializer.writeInt32((valueHolderForParamsTmpValue.size).toInt())
            for (const pair of valueHolderForParamsTmpValue) {
                const valueHolderForParamsTmpValueKeyVar = pair[0]
                const valueHolderForParamsTmpValueValueVar = pair[1]
                valueSerializer.writeString(valueHolderForParamsTmpValueKeyVar)
                valueSerializer.writeString(valueHolderForParamsTmpValueValueVar)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let idTmpBuf : string | undefined
        if ((idTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            idTmpBuf = (valueDeserializer.readString() as string)
        }
        const idTmpResult : string | undefined = idTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : string | undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult : string | undefined = typeTmpBuf
        const srcTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcTmpBuf : string | undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        }
        const srcTmpResult : string | undefined = srcTmpBuf
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : Position | undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = Position_serializer.read(valueDeserializer)
        }
        const positionTmpResult : Position | undefined = positionTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : int32 | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            widthTmpBuf = valueDeserializer.readInt32()
        }
        const widthTmpResult : int32 | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : int32 | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = valueDeserializer.readInt32()
        }
        const heightTmpResult : int32 | undefined = heightTmpBuf
        const urlTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let urlTmpBuf : string | undefined
        if ((urlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            urlTmpBuf = (valueDeserializer.readString() as string)
        }
        const urlTmpResult : string | undefined = urlTmpBuf
        const tagTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let tagTmpBuf : string | undefined
        if ((tagTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            tagTmpBuf = (valueDeserializer.readString() as string)
        }
        const tagTmpResult : string | undefined = tagTmpBuf
        const paramsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramsTmpBuf : Map<string, string> | undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const paramsTmpBuf_SizeVar : int32 = valueDeserializer.readInt32()
            let paramsTmpBuf_ : Map<string, string> = new Map<string, string>()
            // TODO: TS map resize
            for (let paramsTmpBuf_IVar = 0; paramsTmpBuf_IVar < paramsTmpBuf_SizeVar; paramsTmpBuf_IVar++) {
                const paramsTmpBuf_KeyVar : string = (valueDeserializer.readString() as string)
                const paramsTmpBuf_ValueVar : string = (valueDeserializer.readString() as string)
                paramsTmpBuf_.set(paramsTmpBuf_KeyVar, paramsTmpBuf_ValueVar)
            }
            paramsTmpBuf = paramsTmpBuf_
        }
        const paramsTmpResult : Map<string, string> | undefined = paramsTmpBuf
        let value : NativeEmbedInfo = ({id: idTmpResult, type: typeTmpResult, src: srcTmpResult, position: positionTmpResult, width: widthTmpResult, height: heightTmpResult, url: urlTmpResult, tag: tagTmpResult, params: paramsTmpResult} as NativeEmbedInfo)
        return value
    }
}
export class NativeEmbedDataInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedDataInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStatus  = value.status
        if (valueHolderForStatus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStatusTmpValue  = (valueHolderForStatus as NativeEmbedStatus)
            valueSerializer.writeInt32(TypeChecker.NativeEmbedStatus_ToNumeric(valueHolderForStatusTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceId  = value.surfaceId
        if (valueHolderForSurfaceId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSurfaceIdTmpValue  = valueHolderForSurfaceId!
            valueSerializer.writeString(valueHolderForSurfaceIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEmbedId  = value.embedId
        if (valueHolderForEmbedId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmbedIdTmpValue  = valueHolderForEmbedId!
            valueSerializer.writeString(valueHolderForEmbedIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForInfo  = value.info
        if (valueHolderForInfo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForInfoTmpValue  = valueHolderForInfo!
            NativeEmbedInfo_serializer.write(valueSerializer, valueHolderForInfoTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedDataInfo {
        let valueDeserializer : DeserializerBase = buffer
        const statusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let statusTmpBuf : NativeEmbedStatus | undefined
        if ((statusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            statusTmpBuf = TypeChecker.NativeEmbedStatus_FromNumeric(valueDeserializer.readInt32())
        }
        const statusTmpResult : NativeEmbedStatus | undefined = statusTmpBuf
        const surfaceIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let surfaceIdTmpBuf : string | undefined
        if ((surfaceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            surfaceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const surfaceIdTmpResult : string | undefined = surfaceIdTmpBuf
        const embedIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let embedIdTmpBuf : string | undefined
        if ((embedIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            embedIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const embedIdTmpResult : string | undefined = embedIdTmpBuf
        const infoTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let infoTmpBuf : NativeEmbedInfo | undefined
        if ((infoTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            infoTmpBuf = NativeEmbedInfo_serializer.read(valueDeserializer)
        }
        const infoTmpResult : NativeEmbedInfo | undefined = infoTmpBuf
        let value : NativeEmbedDataInfo = ({status: statusTmpResult, surfaceId: surfaceIdTmpResult, embedId: embedIdTmpResult, info: infoTmpResult} as NativeEmbedDataInfo)
        return value
    }
}
export class NativeEmbedTouchInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedTouchInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEmbedId  = value.embedId
        if (valueHolderForEmbedId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmbedIdTmpValue  = valueHolderForEmbedId!
            valueSerializer.writeString(valueHolderForEmbedIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTouchEvent  = value.touchEvent
        if (valueHolderForTouchEvent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTouchEventTmpValue  = valueHolderForTouchEvent!
            TouchEvent_serializer.write(valueSerializer, valueHolderForTouchEventTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForResult  = value.result
        if (valueHolderForResult !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResultTmpValue  = valueHolderForResult!
            EventResult_serializer.write(valueSerializer, valueHolderForResultTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedTouchInfo {
        let valueDeserializer : DeserializerBase = buffer
        const embedIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let embedIdTmpBuf : string | undefined
        if ((embedIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            embedIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const embedIdTmpResult : string | undefined = embedIdTmpBuf
        const touchEventTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let touchEventTmpBuf : TouchEvent | undefined
        if ((touchEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            touchEventTmpBuf = (TouchEvent_serializer.read(valueDeserializer) as TouchEvent)
        }
        const touchEventTmpResult : TouchEvent | undefined = touchEventTmpBuf
        const resultTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let resultTmpBuf : EventResult | undefined
        if ((resultTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            resultTmpBuf = (EventResult_serializer.read(valueDeserializer) as EventResult)
        }
        const resultTmpResult : EventResult | undefined = resultTmpBuf
        let value : NativeEmbedTouchInfo = ({embedId: embedIdTmpResult, touchEvent: touchEventTmpResult, result: resultTmpResult} as NativeEmbedTouchInfo)
        return value
    }
}

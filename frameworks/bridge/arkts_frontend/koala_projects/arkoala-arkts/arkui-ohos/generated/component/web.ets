/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { extractors, AttributeModifier, hookJavaScriptProxy, hookWebAttributeModifier, AttributeUpdater } from '#handwritten'
import { default as webview } from '@ohos.web.webview'
import { global_resource_Resource_serializer } from './../framework/resource'
import { Resource as global_resource_Resource } from 'global.resource'
import { ArkThemeScopeManager } from '#arktheme'
import { NestedScrollOptions_serializer, ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, KeyEvent, NestedScrollOptions, TouchEvent, MouseEvent, ArkCommonMethodComponent, MouseEvent_serializer, TouchEvent_serializer } from './common'
import { EditMenuOptions_serializer, TextDataDetectorConfig_serializer, EditMenuOptions, TextDataDetectorConfig, MenuType } from './textCommon'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { CopyOptions, NestedScrollMode } from './enums'
import { VoidCallback, Position, Position_serializer } from './units'
import { CustomBuilder } from './builder'
import { PreviewMenuOptions, PreviewMenuOptions_serializer } from './richEditor'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { default as image } from '@ohos.multimedia.image'
import { WebModifier } from './../WebModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
import { webview_WebviewController_serializer } from './../framework/ohos.web.webview'
export class ClientAuthenticationHandlerInternal {
    public static fromPtr(ptr: KPointer): ClientAuthenticationHandler {
        return new ClientAuthenticationHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class ClientAuthenticationHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ClientAuthenticationHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ClientAuthenticationHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ClientAuthenticationHandler_construct()
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
    public confirm(identity: string, credentialTypeOrCertChainFile: CredentialType | string): void {
        const identity_casted = identity as (string)
        const credentialTypeOrCertChainFile_casted = credentialTypeOrCertChainFile as (CredentialType | string)
        this.confirm2_serialize(identity_casted, credentialTypeOrCertChainFile_casted)
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
    private confirm2_serialize(identity: string, credentialTypeOrCertChainFile: CredentialType | string): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (credentialTypeOrCertChainFile instanceof CredentialType) {
            thisSerializer.writeInt8((0).toByte())
            const credentialTypeOrCertChainFileForIdx0 = credentialTypeOrCertChainFile as CredentialType
            thisSerializer.writeInt32(credentialTypeOrCertChainFileForIdx0.valueOf())
        } else if (credentialTypeOrCertChainFile instanceof string) {
            thisSerializer.writeInt8((1).toByte())
            const credentialTypeOrCertChainFileForIdx1 = credentialTypeOrCertChainFile as string
            thisSerializer.writeString(credentialTypeOrCertChainFileForIdx1)
        }
        ArkUIGeneratedNativeModule._ClientAuthenticationHandler_confirm2(this.peer!.ptr, identity, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        return new ConsoleMessage(MaterializedBaseTag.NOP, ptr)
    }
}
export class ConsoleMessage implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ConsoleMessage.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ConsoleMessage.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_construct()
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
    public getLineNumber(): int32 {
        return this.getLineNumber_serialize()
    }
    public getMessageLevel(): MessageLevel {
        return this.getMessageLevel_serialize()
    }
    public getSource(): ConsoleMessageSource {
        return this.getSource_serialize()
    }
    private getMessage_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getMessage(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getSourceId_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getSourceId(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getLineNumber_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getLineNumber(this.peer!.ptr)
        return retval
    }
    private getMessageLevel_serialize(): MessageLevel {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getMessageLevel(this.peer!.ptr)
        return MessageLevel.fromValue(retval)
    }
    private getSource_serialize(): ConsoleMessageSource {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getSource(this.peer!.ptr)
        return ConsoleMessageSource.fromValue(retval)
    }
}
export class ControllerHandlerInternal {
    public static fromPtr(ptr: KPointer): ControllerHandler {
        return new ControllerHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class ControllerHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ControllerHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ControllerHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ControllerHandler_construct()
        return retval
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
        ArkUIGeneratedNativeModule._ControllerHandler_setWebController(this.peer!.ptr, extractors.toWebviewWebviewControllerPtr(controller))
    }
}
export class DataResubmissionHandlerInternal {
    public static fromPtr(ptr: KPointer): DataResubmissionHandler {
        return new DataResubmissionHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class DataResubmissionHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DataResubmissionHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, DataResubmissionHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._DataResubmissionHandler_construct()
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
        return new EventResult(MaterializedBaseTag.NOP, ptr)
    }
}
export class EventResult implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, EventResult.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, EventResult.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._EventResult_construct()
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
    public setMouseEventResult(result: boolean, stopPropagation?: boolean): void {
        const result_casted = result as (boolean)
        const stopPropagation_casted = stopPropagation as (boolean | undefined)
        this.setMouseEventResult_serialize(result_casted, stopPropagation_casted)
        return
    }
    private setGestureEventResult0_serialize(result: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult0(this.peer!.ptr, result ? true : false)
    }
    private setGestureEventResult1_serialize(result: boolean, stopPropagation: boolean): void {
        ArkUIGeneratedNativeModule._EventResult_setGestureEventResult1(this.peer!.ptr, result ? true : false, stopPropagation ? true : false)
    }
    private setMouseEventResult_serialize(result: boolean, stopPropagation?: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (stopPropagation !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const stopPropagationTmpValue = stopPropagation!
            thisSerializer.writeBoolean(stopPropagationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._EventResult_setMouseEventResult(this.peer!.ptr, result ? true : false, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class FileSelectorParamInternal {
    public static fromPtr(ptr: KPointer): FileSelectorParam {
        return new FileSelectorParam(MaterializedBaseTag.NOP, ptr)
    }
}
export class FileSelectorParam implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FileSelectorParam.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, FileSelectorParam.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_construct()
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
    public getSuggestedName(): string {
        return this.getSuggestedName_serialize()
    }
    public getDefaultPath(): string {
        return this.getDefaultPath_serialize()
    }
    public getDescriptions(): Array<string> {
        return this.getDescriptions_serialize()
    }
    public isAcceptAllOptionExcluded(): boolean {
        return this.isAcceptAllOptionExcluded_serialize()
    }
    public getAcceptableFileTypes(): Array<Array<AcceptableFileType>> {
        return this.getAcceptableFileTypes_serialize()
    }
    private getTitle_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getTitle(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getMode_serialize(): FileSelectorMode {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getMode(this.peer!.ptr)
        return FileSelectorMode.fromValue(retval)
    }
    private getAcceptType_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptType(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<string> = new Array<string>(bufferLength, (arg0: int32):string => {
            return (retvalDeserializer.readString() as string);
        })
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private isCapture_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_isCapture(this.peer!.ptr)
        return retval
    }
    private getMimeTypes_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getMimeTypes(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<string> = new Array<string>(bufferLength, (arg0: int32):string => {
            return (retvalDeserializer.readString() as string);
        })
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private getSuggestedName_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getSuggestedName(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getDefaultPath_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getDefaultPath(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getDescriptions_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getDescriptions(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<string> = new Array<string>(bufferLength, (arg0: int32):string => {
            return (retvalDeserializer.readString() as string);
        })
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private isAcceptAllOptionExcluded_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_isAcceptAllOptionExcluded(this.peer!.ptr)
        return retval
    }
    private getAcceptableFileTypes_serialize(): Array<Array<AcceptableFileType>> {
        const retval = ArkUIGeneratedNativeModule._FileSelectorParam_getAcceptableFileTypes(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<Array<AcceptableFileType>> = new Array<Array<AcceptableFileType>>(bufferLength, (arg0: int32):Array<AcceptableFileType> => {
            const bufferTempBufLength: int32 = retvalDeserializer.readInt32();
            const bufferTempBuf: Array<AcceptableFileType> = new Array<AcceptableFileType>(bufferTempBufLength, (arg0: int32):AcceptableFileType => {
            return AcceptableFileType_serializer.read(retvalDeserializer);
        });
            return bufferTempBuf;
        })
        const returnResult: Array<Array<AcceptableFileType>> = buffer
        return returnResult
    }
}
export class FileSelectorResultInternal {
    public static fromPtr(ptr: KPointer): FileSelectorResult {
        return new FileSelectorResult(MaterializedBaseTag.NOP, ptr)
    }
}
export class FileSelectorResult implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FileSelectorResult.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, FileSelectorResult.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._FileSelectorResult_construct()
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
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((fileList.length).toInt())
        for (let fileListCounterI = 0; fileListCounterI < fileList.length; fileListCounterI++) {
            const fileListTmpElement: string = fileList[fileListCounterI]
            thisSerializer.writeString(fileListTmpElement)
        }
        ArkUIGeneratedNativeModule._FileSelectorResult_handleFileList(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class FullScreenExitHandlerInternal {
    public static fromPtr(ptr: KPointer): FullScreenExitHandler {
        return new FullScreenExitHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class FullScreenExitHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, FullScreenExitHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, FullScreenExitHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._FullScreenExitHandler_construct()
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
        return new HttpAuthHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class HttpAuthHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, HttpAuthHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, HttpAuthHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_construct()
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
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_confirm(this.peer!.ptr, userName, password)
        return retval
    }
    private cancel_serialize(): void {
        ArkUIGeneratedNativeModule._HttpAuthHandler_cancel(this.peer!.ptr)
    }
    private isHttpAuthInfoSaved_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._HttpAuthHandler_isHttpAuthInfoSaved(this.peer!.ptr)
        return retval
    }
}
export class JsGeolocationInternal {
    public static fromPtr(ptr: KPointer): JsGeolocation {
        return new JsGeolocation(MaterializedBaseTag.NOP, ptr)
    }
}
export class JsGeolocation implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, JsGeolocation.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, JsGeolocation.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._JsGeolocation_construct()
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
        ArkUIGeneratedNativeModule._JsGeolocation_invoke(this.peer!.ptr, origin, allow ? true : false, retain ? true : false)
    }
}
export class JsResultInternal {
    public static fromPtr(ptr: KPointer): JsResult {
        return new JsResult(MaterializedBaseTag.NOP, ptr)
    }
}
export class JsResult implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, JsResult.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, JsResult.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._JsResult_construct()
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
        return new PermissionRequest(MaterializedBaseTag.NOP, ptr)
    }
}
export class PermissionRequest implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PermissionRequest.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PermissionRequest.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._PermissionRequest_construct()
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
        const retval = ArkUIGeneratedNativeModule._PermissionRequest_getOrigin(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getAccessibleResource_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._PermissionRequest_getAccessibleResource(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<string> = new Array<string>(bufferLength, (arg0: int32):string => {
            return (retvalDeserializer.readString() as string);
        })
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private grant_serialize(resources: Array<string>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((resources.length).toInt())
        for (let resourcesCounterI = 0; resourcesCounterI < resources.length; resourcesCounterI++) {
            const resourcesTmpElement: string = resources[resourcesCounterI]
            thisSerializer.writeString(resourcesTmpElement)
        }
        ArkUIGeneratedNativeModule._PermissionRequest_grant(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScreenCaptureHandlerInternal {
    public static fromPtr(ptr: KPointer): ScreenCaptureHandler {
        return new ScreenCaptureHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class ScreenCaptureHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ScreenCaptureHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ScreenCaptureHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ScreenCaptureHandler_construct()
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
        const retval = ArkUIGeneratedNativeModule._ScreenCaptureHandler_getOrigin(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private grant_serialize(config: ScreenCaptureConfig): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
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
        return new SslErrorHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class SslErrorHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SslErrorHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, SslErrorHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._SslErrorHandler_construct()
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
        this.handleCancel0_serialize()
        return
    }
    public handleCancel(abortLoading: boolean): void {
        const abortLoading_casted = abortLoading as (boolean)
        this.handleCancel1_serialize(abortLoading_casted)
        return
    }
    private handleConfirm_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleConfirm(this.peer!.ptr)
    }
    private handleCancel0_serialize(): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleCancel0(this.peer!.ptr)
    }
    private handleCancel1_serialize(abortLoading: boolean): void {
        ArkUIGeneratedNativeModule._SslErrorHandler_handleCancel1(this.peer!.ptr, abortLoading ? true : false)
    }
}
export class VerifyPinHandlerInternal {
    public static fromPtr(ptr: KPointer): VerifyPinHandler {
        return new VerifyPinHandler(MaterializedBaseTag.NOP, ptr)
    }
}
export class VerifyPinHandler implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, VerifyPinHandler.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, VerifyPinHandler.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._VerifyPinHandler_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VerifyPinHandler_getFinalizer()
    }
    public confirm(result: PinVerifyResult): void {
        const result_casted = result as (PinVerifyResult)
        this.confirm_serialize(result_casted)
        return
    }
    private confirm_serialize(result: PinVerifyResult): void {
        ArkUIGeneratedNativeModule._VerifyPinHandler_confirm(this.peer!.ptr, result.valueOf())
    }
}
export class WebContextMenuParamInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuParam {
        return new WebContextMenuParam(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebContextMenuParam implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebContextMenuParam.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebContextMenuParam.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_construct()
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
    public getContextMenuMediaType(): ContextMenuDataMediaType {
        return this.getContextMenuMediaType_serialize()
    }
    private x_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_x(this.peer!.ptr)
        return retval
    }
    private y_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_y(this.peer!.ptr)
        return retval
    }
    private getLinkUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getLinkUrl(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getUnfilteredLinkUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getUnfilteredLinkUrl(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getSourceUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceUrl(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private existsImageContents_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_existsImageContents(this.peer!.ptr)
        return retval
    }
    private getMediaType_serialize(): ContextMenuMediaType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getMediaType(this.peer!.ptr)
        return ContextMenuMediaType.fromValue(retval)
    }
    private getSelectionText_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSelectionText(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getSourceType_serialize(): ContextMenuSourceType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceType(this.peer!.ptr)
        return ContextMenuSourceType.fromValue(retval)
    }
    private getInputFieldType_serialize(): ContextMenuInputFieldType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getInputFieldType(this.peer!.ptr)
        return ContextMenuInputFieldType.fromValue(retval)
    }
    private isEditable_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_isEditable(this.peer!.ptr)
        return retval
    }
    private getEditStateFlags_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getEditStateFlags(this.peer!.ptr)
        return retval
    }
    private getPreviewWidth_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewWidth(this.peer!.ptr)
        return retval
    }
    private getPreviewHeight_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getPreviewHeight(this.peer!.ptr)
        return retval
    }
    private getContextMenuMediaType_serialize(): ContextMenuDataMediaType {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuParam_getContextMenuMediaType(this.peer!.ptr)
        return ContextMenuDataMediaType.fromValue(retval)
    }
}
export class WebContextMenuResultInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuResult {
        return new WebContextMenuResult(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebContextMenuResult implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebContextMenuResult.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebContextMenuResult.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuResult_construct()
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
    public redo(): void {
        this.redo_serialize()
        return
    }
    public undo(): void {
        this.undo_serialize()
        return
    }
    public pasteAndMatchStyle(): void {
        this.pasteAndMatchStyle_serialize()
        return
    }
    public requestPasswordAutoFill(): void {
        this.requestPasswordAutoFill_serialize()
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
    private redo_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_redo(this.peer!.ptr)
    }
    private undo_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_undo(this.peer!.ptr)
    }
    private pasteAndMatchStyle_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_pasteAndMatchStyle(this.peer!.ptr)
    }
    private requestPasswordAutoFill_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_requestPasswordAutoFill(this.peer!.ptr)
    }
}
export class WebKeyboardControllerInternal {
    public static fromPtr(ptr: KPointer): WebKeyboardController {
        return new WebKeyboardController(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebKeyboardController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebKeyboardController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebKeyboardController.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebKeyboardController_construct()
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
        return new WebResourceError(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebResourceError implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceError.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebResourceError.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebResourceError_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceError_getFinalizer()
    }
    public getErrorInfo(): string {
        return this.getErrorInfo_serialize()
    }
    public getErrorCode(): int32 {
        return this.getErrorCode_serialize()
    }
    private getErrorInfo_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceError_getErrorInfo(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getErrorCode_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebResourceError_getErrorCode(this.peer!.ptr)
        return retval
    }
}
export class WebResourceRequestInternal {
    public static fromPtr(ptr: KPointer): WebResourceRequest {
        return new WebResourceRequest(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebResourceRequest implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceRequest.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebResourceRequest.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_construct()
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
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestHeader(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<Header> = new Array<Header>(bufferLength, (arg0: int32):Header => {
            return Header_serializer.read(retvalDeserializer);
        })
        const returnResult: Array<Header> = buffer
        return returnResult
    }
    private getRequestUrl_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestUrl(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private isRequestGesture_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isRequestGesture(this.peer!.ptr)
        return retval
    }
    private isMainFrame_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isMainFrame(this.peer!.ptr)
        return retval
    }
    private isRedirect_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_isRedirect(this.peer!.ptr)
        return retval
    }
    private getRequestMethod_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceRequest_getRequestMethod(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
}
export class WebResourceResponseInternal {
    public static fromPtr(ptr: KPointer): WebResourceResponse {
        return new WebResourceResponse(MaterializedBaseTag.NOP, ptr)
    }
}
export class WebResourceResponse implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WebResourceResponse.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, WebResourceResponse.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebResourceResponse_getFinalizer()
    }
    public getResponseData(): string {
        return this.getResponseData_serialize()
    }
    public getResponseDataEx(): string | int32 | ArrayBuffer | global_resource_Resource | undefined {
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
    public getResponseCode(): int32 {
        return this.getResponseCode_serialize()
    }
    public setResponseData(data: string | int32 | global_resource_Resource | ArrayBuffer): void {
        const data_casted = data as (string | int32 | global_resource_Resource | ArrayBuffer)
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
    public setResponseCode(code: int32): void {
        const code_casted = code as (int32)
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
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseData(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getResponseDataEx_serialize(): string | int32 | ArrayBuffer | global_resource_Resource | undefined {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseDataEx(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: string | int32 | ArrayBuffer | global_resource_Resource | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector: int32 = retvalDeserializer.readInt8()
            let bufferOpt: string | int32 | ArrayBuffer | global_resource_Resource | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = (retvalDeserializer.readString() as string)
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = retvalDeserializer.readInt32()
            } else if (bufferOptUnionSelector == (2).toByte()) {
                bufferOpt = (retvalDeserializer.readBuffer() as ArrayBuffer)
            } else if (bufferOptUnionSelector == (3).toByte()) {
                bufferOpt = global_resource_Resource_serializer.read(retvalDeserializer)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as string | int32 | ArrayBuffer | global_resource_Resource)
        }
        const returnResult: string | int32 | ArrayBuffer | global_resource_Resource | undefined = buffer
        return returnResult
    }
    private getResponseEncoding_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseEncoding(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getResponseMimeType_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseMimeType(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getReasonMessage_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getReasonMessage(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private getResponseHeader_serialize(): Array<Header> {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseHeader(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        const buffer: Array<Header> = new Array<Header>(bufferLength, (arg0: int32):Header => {
            return Header_serializer.read(retvalDeserializer);
        })
        const returnResult: Array<Header> = buffer
        return returnResult
    }
    private getResponseCode_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseCode(this.peer!.ptr)
        return retval
    }
    private setResponseData_serialize(data: string | int32 | global_resource_Resource | ArrayBuffer): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (data instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const dataForIdx0 = data as string
            thisSerializer.writeString(dataForIdx0)
        } else if (data instanceof int32) {
            thisSerializer.writeInt8((1).toByte())
            const dataForIdx1 = data as int32
            thisSerializer.writeInt32(dataForIdx1)
        } else if (data instanceof global_resource_Resource) {
            thisSerializer.writeInt8((2).toByte())
            const dataForIdx2 = data as global_resource_Resource
            global_resource_Resource_serializer.write(thisSerializer, dataForIdx2)
        } else if (data instanceof ArrayBuffer) {
            thisSerializer.writeInt8((3).toByte())
            const dataForIdx3 = data as ArrayBuffer
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
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((header.length).toInt())
        for (let headerCounterI = 0; headerCounterI < header.length; headerCounterI++) {
            const headerTmpElement: Header = header[headerCounterI]
            Header_serializer.write(thisSerializer, headerTmpElement)
        }
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseHeader(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setResponseCode_serialize(code: int32): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseCode(this.peer!.ptr, code)
    }
    private setResponseIsReady_serialize(IsReady: boolean): void {
        ArkUIGeneratedNativeModule._WebResourceResponse_setResponseIsReady(this.peer!.ptr, IsReady ? true : false)
    }
    private getResponseIsReady_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._WebResourceResponse_getResponseIsReady(this.peer!.ptr)
        return retval
    }
}
export class ArkWebPeer extends ArkCommonMethodPeer {
    attributeSet?: WebModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWebPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Web_construct(peerId, flags)
        const _peer = new ArkWebPeer(_peerPtr, peerId, 'Web', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWebOptionsAttribute(value: WebOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        WebOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._WebInterface_setWebOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFileAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setFileAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnlineImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnlineImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDomStorageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDomStorageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setImageAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMixedModeAttribute(value: MixedMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as MixedMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMixedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setZoomAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setZoomAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGeolocationAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setGeolocationAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptProxyAttribute(value: JavaScriptProxy | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            JavaScriptProxy_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptProxy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCacheModeAttribute(value: CacheMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as CacheMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCacheMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDarkModeAttribute(value: WebDarkMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as WebDarkMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDarkMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDarkAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDarkAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaOptionsAttribute(value: WebMediaOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            WebMediaOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverviewModeAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverviewModeAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOverScrollModeAttribute(value: OverScrollMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as OverScrollMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOverScrollMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlurOnKeyboardHideModeAttribute(value: BlurOnKeyboardHideMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as BlurOnKeyboardHideMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlurOnKeyboardHideMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextZoomRatioAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextZoomRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDatabaseAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDatabaseAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialScaleAttribute(value: double | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setInitialScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMetaViewportAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMetaViewport(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageBeginAttribute(value: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageEndAttribute(value: arkui_component_common_Callback<OnPageEndEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadStartedAttribute(value: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLoadStarted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadFinishedAttribute(value: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLoadFinished(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnProgressChangeAttribute(value: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnProgressChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTitleReceiveAttribute(value: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTitleReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGeolocationShowAttribute(value: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnGeolocationShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestSelectedAttribute(value: (() => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRequestSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAlertAttribute(value: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAlert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBeforeUnloadAttribute(value: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnBeforeUnload(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConfirmAttribute(value: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConfirm(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPromptAttribute(value: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPrompt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnConsoleAttribute(value: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnConsole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorReceiveAttribute(value: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpErrorReceiveAttribute(value: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpErrorReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDownloadStartAttribute(value: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDownloadStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRefreshAccessedHistoryAttribute(value: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRefreshAccessedHistory(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderExitedAttribute(value: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderExited(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnShowFileSelectorAttribute(value: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnShowFileSelector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnResourceLoadAttribute(value: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnResourceLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullScreenEnterAttribute(value: OnFullScreenEnterCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFullScreenEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScaleChangeAttribute(value: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScaleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHttpAuthRequestAttribute(value: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnHttpAuthRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptRequestAttribute(value: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPermissionRequestAttribute(value: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPermissionRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScreenCaptureRequestAttribute(value: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScreenCaptureRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuShowAttribute(value: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContextMenuHideAttribute(value: OnContextMenuHideCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnContextMenuHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMediaPlayGestureAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMediaPlayGestureAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSearchResultReceiveAttribute(value: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSearchResultReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollAttribute(value: arkui_component_common_Callback<OnScrollEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventReceiveAttribute(value: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEventReceive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSslErrorEventAttribute(value: OnSslErrorEventCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSslErrorEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClientAuthenticationRequestAttribute(value: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnClientAuthenticationRequest(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnVerifyPinAttribute(value: OnVerifyPinCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnVerifyPin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowNewAttribute(value: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowNew(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowNewExtAttribute(value: arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowNewExt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWindowExitAttribute(value: (() => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnWindowExit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiWindowAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMultiWindowAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyEventAttribute(value: ((event: KeyEvent) => boolean) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebStandardFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebStandardFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSerifFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebSansSerifFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebSansSerifFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFixedFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFixedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebFantasyFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebFantasyFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWebCursiveFontAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setWebCursiveFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFixedFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFixedFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinLogicalFontSizeAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setMinLogicalFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDefaultTextEncodingFormatAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDefaultTextEncodingFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceDisplayScrollBarAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceDisplayScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockNetworkAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlockNetwork(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHorizontalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setHorizontalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalScrollBarAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setVerticalScrollBarAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTouchIconUrlReceivedAttribute(value: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTouchIconUrlReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFaviconReceivedAttribute(value: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFaviconReceived(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPageVisibleAttribute(value: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPageVisible(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDataResubmittedAttribute(value: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDataResubmitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPinchSmoothAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setPinchSmooth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowWindowOpenMethodAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setAllowWindowOpenMethod(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAudioStateChangedAttribute(value: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAudioStateChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstContentfulPaintAttribute(value: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLargestContentfulPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadInterceptAttribute(value: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnLoadIntercept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnControllerAttachedAttribute(value: (() => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnControllerAttached(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverScrollAttribute(value: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPdfScrollAtBottomAttribute(value: arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPdfScrollAtBottom(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPdfLoadEventAttribute(value: arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnPdfLoadEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSafeBrowsingCheckFinishAttribute(value: OnSafeBrowsingCheckResultCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnSafeBrowsingCheckFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNavigationEntryCommitted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement: ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement: ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutModeAttribute(value: WebLayoutMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as WebLayoutMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setLayoutMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof NestedScrollOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as NestedScrollOptions
                NestedScrollOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof NestedScrollOptionsExt) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as NestedScrollOptionsExt
                NestedScrollOptionsExt_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeEmbedModeAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeEmbedMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedMouseEventAttribute(value: MouseInfoCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedMouseEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as CopyOptions)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setCopyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverrideUrlLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOverrideErrorPageAttribute(value: OnOverrideErrorPageCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnOverrideErrorPage(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAutosizingAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setTextAutosizing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            NativeMediaPlayerConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableNativeMediaPlayer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessNotResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnRenderProcessResponding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnViewportFitChangedAttribute(value: OnViewportFitChangedCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnViewportFitChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInterceptKeyboardAttachAttribute(value: WebKeyboardCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAdsBlockedAttribute(value: OnAdsBlockedCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnAdsBlocked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAvoidModeAttribute(value: WebKeyboardAvoidMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as WebKeyboardAvoidMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setKeyboardAvoidMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            EditMenuOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableFollowSystemFontWeightAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableFollowSystemFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableWebAVSessionAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableWebAVSession(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptimizeParserBudgetAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOptimizeParserBudget(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentStartAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement: ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnDocumentEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement: ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRunJavaScriptOnHeadEndAttribute(value: Array<ScriptItem> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement: ScriptItem = valueTmpValue[valueTmpValueCounterI]
                ScriptItem_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRunJavaScriptOnHeadEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNativeEmbedOptionsAttribute(value: EmbedOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            EmbedOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setNativeEmbedOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setDataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnActivateContentAttribute(value: VoidCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnActivateContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBypassVsyncConditionAttribute(value: WebBypassVsyncCondition | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as WebBypassVsyncCondition)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBypassVsyncCondition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setGestureFocusModeAttribute(value: GestureFocusMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as GestureFocusMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setGestureFocusMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setForceEnableZoomAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setForceEnableZoom(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNativeEmbedObjectParamChangeAttribute(value: OnNativeEmbedObjectParamChangeCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnNativeEmbedObjectParamChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRotateRenderEffectAttribute(value: WebRotateEffect | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as WebRotateEffect)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRotateRenderEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setZoomControlAccessAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setZoomControlAccess(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDetectedBlankScreenAttribute(value: OnDetectBlankScreenCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnDetectedBlankScreen(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlankScreenDetectionConfigAttribute(value: BlankScreenDetectionConfig | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            BlankScreenDetectionConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBlankScreenDetectionConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackToTopAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setBackToTop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableSelectedDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableSelectedDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFirstScreenPaintAttribute(value: OnFirstScreenPaintCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnFirstScreenPaint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAutoFillAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableAutoFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: TextSelectionChangeCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableImageAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableImageAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCameraCaptureStateChangeAttribute(value: OnCameraCaptureStateChangeCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnCameraCaptureStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnMicrophoneCaptureStateChangeAttribute(value: OnMicrophoneCaptureStateChangeCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setOnMicrophoneCaptureStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDefaultContextMenuAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setEnableDefaultContextMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRegisterNativeEmbedRuleAttribute(tag: string | undefined, type: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (tag !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const tagTmpValue = tag!
            thisSerializer.writeString(tagTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue = type!
            thisSerializer.writeString(typeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WebAttribute_setRegisterNativeEmbedRule(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (elementType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const elementTypeTmpValue = (elementType as WebElementType)
            thisSerializer.writeInt32(elementTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(contentTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (responseType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTypeTmpValue = (responseType as WebResponseType)
            thisSerializer.writeInt32(responseTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
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
export type OnVerifyPinCallback = (verifyPinEvent: VerifyPinEvent) => void;
export type OnOverrideErrorPageCallback = (errorPageEvent: OnErrorReceiveEvent) => string;
export type OnLargestContentfulPaintCallback = (largestContentfulPaint: LargestContentfulPaint) => void;
export type OnFirstMeaningfulPaintCallback = (firstMeaningfulPaint: FirstMeaningfulPaint) => void;
export type OnOverrideUrlLoadingCallback = (webResourceRequest: WebResourceRequest) => boolean;
export type OnIntelligentTrackingPreventionCallback = (details: IntelligentTrackingPreventionDetails) => void;
export type OnNativeEmbedVisibilityChangeCallback = (nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo) => void;
export type OnNativeEmbedObjectParamChangeCallback = (event: NativeEmbedParamDataInfo) => void;
export enum NativeEmbedParamStatus {
    ADD = 0,
    UPDATE = 1,
    DELETE = 2
}
export interface NativeEmbedParamItem {
    status: NativeEmbedParamStatus;
    id: string;
    name?: string;
    value?: string;
}
export interface NativeEmbedParamDataInfo {
    embedId: string;
    objectAttributeId?: string;
    paramItems?: Array<NativeEmbedParamItem>;
}
export enum WebRotateEffect {
    TOPLEFT_EFFECT = 0,
    RESIZE_COVER_EFFECT = 1
}
export interface NativeMediaPlayerConfig {
    enable: boolean;
    shouldOverlay: boolean;
}
export type OnRenderProcessNotRespondingCallback = (data: RenderProcessNotRespondingData) => void;
export type OnRenderProcessRespondingCallback = () => void;
export type OnViewportFitChangedCallback = (viewportFit: ViewportFit) => void;
export type OnAdsBlockedCallback = (details: AdsBlockedDetails) => void;
export type OnCameraCaptureStateChangeCallback = (event: CameraCaptureStateChangeInfo) => void;
export type OnMicrophoneCaptureStateChangeCallback = (event: MicrophoneCaptureStateChangeInfo) => void;
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
    attributes: Record<string, string>;
}
export type WebKeyboardCallback = (keyboardCallbackInfo: WebKeyboardCallbackInfo) => WebKeyboardOptions;
export enum MessageLevel {
    DEBUG = 0,
    ERROR = 1,
    INFO = 2,
    LOG = 3,
    WARN = 4
}
export enum ConsoleMessageSource {
    XML = 0,
    JAVASCRIPT = 1,
    NETWORK = 2,
    CONSOLE_API = 3,
    STORAGE = 4,
    RENDERING = 5,
    SECURITY = 6,
    OTHER = 7,
    DEPRECATION = 8,
    WORKER = 9,
    VIOLATION = 10,
    INTERVENTION = 11,
    RECOMMENDATION = 12
}
export enum MixedMode {
    ALL = 0,
    COMPATIBLE = 1,
    NONE = 2
}
export type OnSafeBrowsingCheckResultCallback = (threatType: ThreatType) => void;
export enum CacheMode {
    DEFAULT = 0,
    NONE = 1,
    ONLINE = 2,
    ONLY = 3
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
    ON = 1,
    AUTO = 2
}
export enum WebCaptureMode {
    HOME_SCREEN = 0
}
export enum ThreatType {
    THREAT_ILLEGAL = 0,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3,
    THREAT_NONE = 4,
    THREAT_UNPROCESSED = 5
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
    videoWidth?: int32;
    videoHeight?: int32;
}
export type OnFullScreenEnterCallback = (event: FullScreenEnterEvent) => void;
export type MouseInfoCallback = (event: NativeEmbedMouseInfo) => void;
export enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION = 0,
    PROCESS_WAS_KILLED = 1,
    PROCESS_CRASHED = 2,
    PROCESS_OOM = 3,
    PROCESS_EXIT_UNKNOWN = 4
}
export type OnContextMenuHideCallback = () => void;
export enum SslError {
    INVALID = 0,
    HOST_MISMATCH = 1,
    DATE_INVALID = 2,
    UNTRUSTED = 3
}
export enum FileSelectorMode {
    FILE_OPEN_MODE = 0,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FILE_OPEN_FOLDER_MODE = 2,
    FILE_SAVE_MODE = 3
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
    MIDI_SYSEX = 'TYPE_MIDI_SYSEX',
    VIDEO_CAPTURE = 'TYPE_VIDEO_CAPTURE',
    AUDIO_CAPTURE = 'TYPE_AUDIO_CAPTURE',
    SENSOR = 'TYPE_SENSOR'
}
export enum ContextMenuSourceType {
    NONE = 0,
    MOUSE = 1,
    LONG_PRESS = 2
}
export enum ContextMenuMediaType {
    NONE = 0,
    IMAGE = 1
}
export enum ContextMenuDataMediaType {
    NONE = 0,
    IMAGE = 1,
    VIDEO = 2,
    AUDIO = 3,
    CANVAS = 4
}
export enum ContextMenuInputFieldType {
    NONE = 0,
    PLAIN_TEXT = 1,
    PASSWORD = 2,
    NUMBER_DATA = 3,
    TELEPHONE = 4,
    OTHER = 5
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
    src: string | global_resource_Resource;
    controller: WebviewController;
    renderMode?: RenderMode;
    incognitoMode?: boolean;
    sharedRenderProcessToken?: string;
    emulateTouchFromMouseEvent?: boolean;
}
export interface UrlRegexRule {
    secondLevelDomain: string;
    rule: string;
}
export interface ScriptItem {
    script: string;
    scriptRules: Array<string>;
    urlRegexRules?: Array<UrlRegexRule>;
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
export interface NativeEmbedMouseInfo {
    embedId?: string;
    mouseEvent?: MouseEvent;
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
export interface OnLoadStartedEvent {
    url: string;
}
export interface OnLoadFinishedEvent {
    url: string;
}
export interface OnProgressChangeEvent {
    newProgress: int32;
}
export interface OnTitleReceiveEvent {
    title: string;
    isRealTitle?: boolean;
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
    isReload?: boolean;
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
    contentLength: int64;
}
export interface OnRefreshAccessedHistoryEvent {
    url: string;
    isRefreshed: boolean;
    isMainFrame?: boolean;
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
    activeMatchOrdinal: int32;
    numberOfMatches: int32;
    isDoneCounting: boolean;
}
export interface OnScrollEvent {
    xOffset: double;
    yOffset: double;
}
export interface OnSslErrorEventReceiveEvent {
    handler: SslErrorHandler;
    error: SslError;
    certChainData?: Array<ArrayBuffer>;
}
export interface OnClientAuthenticationEvent {
    handler: ClientAuthenticationHandler;
    host: string;
    port: int32;
    keyTypes: Array<string>;
    issuers: Array<string>;
}
export interface OnWindowNewEvent {
    isAlert: boolean;
    isUserTrigger: boolean;
    targetUrl: string;
    handler: ControllerHandler;
}
export enum NavigationPolicy {
    NEW_POPUP = 0,
    NEW_WINDOW = 1,
    NEW_BACKGROUND_TAB = 2,
    NEW_FOREGROUND_TAB = 3
}
export interface WindowFeatures {
    height: double;
    width: double;
    x: double;
    y: double;
}
export interface OnWindowNewExtEvent {
    isAlert: boolean;
    isUserTrigger: boolean;
    targetUrl: string;
    handler: ControllerHandler;
    windowFeatures: WindowFeatures;
    navigationPolicy: NavigationPolicy;
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
export interface OnPdfScrollEvent {
    url: string;
}
export interface OnPdfLoadEvent {
    result: PdfLoadResult;
    url: string;
}
export interface JavaScriptProxy {
    jsObject: Object;
    name: string;
    methodList: Array<string>;
    controller: WebviewController;
    asyncMethodList?: Array<string>;
    permission?: string;
}
export enum WebKeyboardAvoidMode {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2,
    RETURN_TO_UICONTEXT = 3
}
export enum WebElementType {
    IMAGE = 1,
    LINK = 2,
    TEXT = 3
}
export enum WebResponseType {
    LONG_PRESS = 1,
    RIGHT_CLICK = 2
}
export enum AudioSessionType {
    AMBIENT = 3
}
export enum PdfLoadResult {
    LOAD_SUCCESS = 0,
    PARSE_ERROR_FILE = 1,
    PARSE_ERROR_FORMAT = 2,
    PARSE_ERROR_PASSWORD = 3,
    PARSE_ERROR_HANDLER = 4
}
export enum WebBypassVsyncCondition {
    NONE = 0,
    SCROLLBY_FROM_ZERO_OFFSET = 1
}
export interface SelectionMenuOptionsExt {
    onAppear?: VoidCallback;
    onDisappear?: VoidCallback;
    preview?: CustomBuilder;
    menuType?: MenuType;
    previewMenuOptions?: PreviewMenuOptions;
    onMenuShow?: VoidCallback;
    onMenuHide?: VoidCallback;
}
export interface BlankScreenDetails {
    detectedContentfulNodesCount?: int32;
}
export enum DetectedBlankScreenReason {
    NO_CONTENTFUL_NODES = 0,
    SUB_THRESHOLD_CONTENTFUL_NODES = 1
}
export interface BlankScreenDetectionEventInfo {
    url: string;
    blankScreenReason: DetectedBlankScreenReason;
    blankScreenDetails?: BlankScreenDetails;
}
export type OnDetectBlankScreenCallback = (event: BlankScreenDetectionEventInfo) => void;
export type TextSelectionChangeCallback = (selectionText: string) => void;
export enum BlankScreenDetectionMethod {
    DETECTION_CONTENTFUL_NODES_SEVENTEEN = 0
}
export interface BlankScreenDetectionConfig {
    enable: boolean;
    detectionTiming?: Array<double>;
    detectionMethods?: Array<BlankScreenDetectionMethod>;
    contentfulNodesCountThreshold?: int32;
}
export interface FirstScreenPaint {
    url: string;
    navigationStartTime: int64;
    firstScreenPaintTime: int64;
}
export type OnFirstScreenPaintCallback = (firstScreenPaint: FirstScreenPaint) => void;
export interface WebAttribute extends CommonMethod {
    setWebOptions(value: WebOptions): this {
        throw new Error('Unimplemented method setWebOptions')
    }
    javaScriptAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method javaScriptAccess')
    }
    fileAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method fileAccess')
    }
    onlineImageAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method onlineImageAccess')
    }
    domStorageAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method domStorageAccess')
    }
    imageAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method imageAccess')
    }
    mixedMode(value: MixedMode | undefined): this {
        throw new Error('Unimplemented method mixedMode')
    }
    zoomAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method zoomAccess')
    }
    geolocationAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method geolocationAccess')
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        throw new Error('Unimplemented method javaScriptProxy')
    }
    cacheMode(value: CacheMode | undefined): this {
        throw new Error('Unimplemented method cacheMode')
    }
    darkMode(value: WebDarkMode | undefined): this {
        throw new Error('Unimplemented method darkMode')
    }
    forceDarkAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method forceDarkAccess')
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        throw new Error('Unimplemented method mediaOptions')
    }
    overviewModeAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method overviewModeAccess')
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        throw new Error('Unimplemented method overScrollMode')
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        throw new Error('Unimplemented method blurOnKeyboardHideMode')
    }
    textZoomRatio(value: int32 | undefined): this {
        throw new Error('Unimplemented method textZoomRatio')
    }
    databaseAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method databaseAccess')
    }
    initialScale(value: double | undefined): this {
        throw new Error('Unimplemented method initialScale')
    }
    metaViewport(value: boolean | undefined): this {
        throw new Error('Unimplemented method metaViewport')
    }
    onPageBegin(value: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPageBegin')
    }
    onPageEnd(value: arkui_component_common_Callback<OnPageEndEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPageEnd')
    }
    onLoadStarted(value: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onLoadStarted')
    }
    onLoadFinished(value: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onLoadFinished')
    }
    onProgressChange(value: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined): this {
        throw new Error('Unimplemented method onProgressChange')
    }
    onTitleReceive(value: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined): this {
        throw new Error('Unimplemented method onTitleReceive')
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onGeolocationHide')
    }
    onGeolocationShow(value: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined): this {
        throw new Error('Unimplemented method onGeolocationShow')
    }
    onRequestSelected(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onRequestSelected')
    }
    onAlert(value: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onAlert')
    }
    onBeforeUnload(value: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onBeforeUnload')
    }
    onConfirm(value: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onConfirm')
    }
    onPrompt(value: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onPrompt')
    }
    onConsole(value: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onConsole')
    }
    onErrorReceive(value: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined): this {
        throw new Error('Unimplemented method onErrorReceive')
    }
    onHttpErrorReceive(value: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined): this {
        throw new Error('Unimplemented method onHttpErrorReceive')
    }
    onDownloadStart(value: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined): this {
        throw new Error('Unimplemented method onDownloadStart')
    }
    onRefreshAccessedHistory(value: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined): this {
        throw new Error('Unimplemented method onRefreshAccessedHistory')
    }
    onRenderExited(value: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onRenderExited')
    }
    onShowFileSelector(value: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onShowFileSelector')
    }
    onResourceLoad(value: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined): this {
        throw new Error('Unimplemented method onResourceLoad')
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onFullScreenExit')
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        throw new Error('Unimplemented method onFullScreenEnter')
    }
    onScaleChange(value: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined): this {
        throw new Error('Unimplemented method onScaleChange')
    }
    onHttpAuthRequest(value: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onHttpAuthRequest')
    }
    onInterceptRequest(value: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): this {
        throw new Error('Unimplemented method onInterceptRequest')
    }
    onPermissionRequest(value: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPermissionRequest')
    }
    onScreenCaptureRequest(value: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined): this {
        throw new Error('Unimplemented method onScreenCaptureRequest')
    }
    onContextMenuShow(value: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onContextMenuShow')
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        throw new Error('Unimplemented method onContextMenuHide')
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method mediaPlayGestureAccess')
    }
    onSearchResultReceive(value: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined): this {
        throw new Error('Unimplemented method onSearchResultReceive')
    }
    onScroll(value: arkui_component_common_Callback<OnScrollEvent, void> | undefined): this {
        throw new Error('Unimplemented method onScroll')
    }
    onSslErrorEventReceive(value: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined): this {
        throw new Error('Unimplemented method onSslErrorEventReceive')
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        throw new Error('Unimplemented method onSslErrorEvent')
    }
    onClientAuthenticationRequest(value: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined): this {
        throw new Error('Unimplemented method onClientAuthenticationRequest')
    }
    onVerifyPin(value: OnVerifyPinCallback | undefined): this {
        throw new Error('Unimplemented method onVerifyPin')
    }
    onWindowNew(value: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined): this {
        throw new Error('Unimplemented method onWindowNew')
    }
    onWindowNewExt(value: arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined): this {
        throw new Error('Unimplemented method onWindowNewExt')
    }
    onWindowExit(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onWindowExit')
    }
    multiWindowAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method multiWindowAccess')
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        throw new Error('Unimplemented method onInterceptKeyEvent')
    }
    webStandardFont(value: string | undefined): this {
        throw new Error('Unimplemented method webStandardFont')
    }
    webSerifFont(value: string | undefined): this {
        throw new Error('Unimplemented method webSerifFont')
    }
    webSansSerifFont(value: string | undefined): this {
        throw new Error('Unimplemented method webSansSerifFont')
    }
    webFixedFont(value: string | undefined): this {
        throw new Error('Unimplemented method webFixedFont')
    }
    webFantasyFont(value: string | undefined): this {
        throw new Error('Unimplemented method webFantasyFont')
    }
    webCursiveFont(value: string | undefined): this {
        throw new Error('Unimplemented method webCursiveFont')
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        throw new Error('Unimplemented method defaultFixedFontSize')
    }
    defaultFontSize(value: int32 | undefined): this {
        throw new Error('Unimplemented method defaultFontSize')
    }
    minFontSize(value: int32 | undefined): this {
        throw new Error('Unimplemented method minFontSize')
    }
    minLogicalFontSize(value: int32 | undefined): this {
        throw new Error('Unimplemented method minLogicalFontSize')
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        throw new Error('Unimplemented method defaultTextEncodingFormat')
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        throw new Error('Unimplemented method forceDisplayScrollBar')
    }
    blockNetwork(value: boolean | undefined): this {
        throw new Error('Unimplemented method blockNetwork')
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method horizontalScrollBarAccess')
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method verticalScrollBarAccess')
    }
    onTouchIconUrlReceived(value: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onTouchIconUrlReceived')
    }
    onFaviconReceived(value: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onFaviconReceived')
    }
    onPageVisible(value: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPageVisible')
    }
    onDataResubmitted(value: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onDataResubmitted')
    }
    pinchSmooth(value: boolean | undefined): this {
        throw new Error('Unimplemented method pinchSmooth')
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        throw new Error('Unimplemented method allowWindowOpenMethod')
    }
    onAudioStateChanged(value: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined): this {
        throw new Error('Unimplemented method onAudioStateChanged')
    }
    onFirstContentfulPaint(value: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined): this {
        throw new Error('Unimplemented method onFirstContentfulPaint')
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        throw new Error('Unimplemented method onFirstMeaningfulPaint')
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        throw new Error('Unimplemented method onLargestContentfulPaint')
    }
    onLoadIntercept(value: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined): this {
        throw new Error('Unimplemented method onLoadIntercept')
    }
    onControllerAttached(value: (() => void) | undefined): this {
        throw new Error('Unimplemented method onControllerAttached')
    }
    onOverScroll(value: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined): this {
        throw new Error('Unimplemented method onOverScroll')
    }
    onPdfScrollAtBottom(value: arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPdfScrollAtBottom')
    }
    onPdfLoadEvent(value: arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined): this {
        throw new Error('Unimplemented method onPdfLoadEvent')
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        throw new Error('Unimplemented method onSafeBrowsingCheckResult')
    }
    onSafeBrowsingCheckFinish(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        throw new Error('Unimplemented method onSafeBrowsingCheckFinish')
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        throw new Error('Unimplemented method onNavigationEntryCommitted')
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        throw new Error('Unimplemented method onIntelligentTrackingPreventionResult')
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        throw new Error('Unimplemented method javaScriptOnDocumentStart')
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error('Unimplemented method javaScriptOnDocumentEnd')
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        throw new Error('Unimplemented method layoutMode')
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        throw new Error('Unimplemented method nestedScroll')
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableNativeEmbedMode')
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        throw new Error('Unimplemented method onNativeEmbedLifecycleChange')
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        throw new Error('Unimplemented method onNativeEmbedVisibilityChange')
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        throw new Error('Unimplemented method onNativeEmbedGestureEvent')
    }
    onNativeEmbedMouseEvent(value: MouseInfoCallback | undefined): this {
        throw new Error('Unimplemented method onNativeEmbedMouseEvent')
    }
    copyOptions(value: CopyOptions | undefined): this {
        throw new Error('Unimplemented method copyOptions')
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        throw new Error('Unimplemented method onOverrideUrlLoading')
    }
    onOverrideErrorPage(value: OnOverrideErrorPageCallback | undefined): this {
        throw new Error('Unimplemented method onOverrideErrorPage')
    }
    textAutosizing(value: boolean | undefined): this {
        throw new Error('Unimplemented method textAutosizing')
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        throw new Error('Unimplemented method enableNativeMediaPlayer')
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        throw new Error('Unimplemented method onRenderProcessNotResponding')
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        throw new Error('Unimplemented method onRenderProcessResponding')
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        throw new Error('Unimplemented method onViewportFitChanged')
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        throw new Error('Unimplemented method onInterceptKeyboardAttach')
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        throw new Error('Unimplemented method onAdsBlocked')
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        throw new Error('Unimplemented method keyboardAvoidMode')
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error('Unimplemented method editMenuOptions')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableFollowSystemFontWeight')
    }
    enableWebAVSession(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableWebAVSession')
    }
    optimizeParserBudget(value: boolean | undefined): this {
        throw new Error('Unimplemented method optimizeParserBudget')
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        throw new Error('Unimplemented method runJavaScriptOnDocumentStart')
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error('Unimplemented method runJavaScriptOnDocumentEnd')
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        throw new Error('Unimplemented method runJavaScriptOnHeadEnd')
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        throw new Error('Unimplemented method nativeEmbedOptions')
    }
    enableDataDetector(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableDataDetector')
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        throw new Error('Unimplemented method dataDetectorConfig')
    }
    onActivateContent(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onActivateContent')
    }
    bypassVsyncCondition(value: WebBypassVsyncCondition | undefined): this {
        throw new Error('Unimplemented method bypassVsyncCondition')
    }
    gestureFocusMode(value: GestureFocusMode | undefined): this {
        throw new Error('Unimplemented method gestureFocusMode')
    }
    forceEnableZoom(value: boolean | undefined): this {
        throw new Error('Unimplemented method forceEnableZoom')
    }
    onNativeEmbedObjectParamChange(value: OnNativeEmbedObjectParamChangeCallback | undefined): this {
        throw new Error('Unimplemented method onNativeEmbedObjectParamChange')
    }
    rotateRenderEffect(value: WebRotateEffect | undefined): this {
        throw new Error('Unimplemented method rotateRenderEffect')
    }
    zoomControlAccess(value: boolean | undefined): this {
        throw new Error('Unimplemented method zoomControlAccess')
    }
    onDetectedBlankScreen(value: OnDetectBlankScreenCallback | undefined): this {
        throw new Error('Unimplemented method onDetectedBlankScreen')
    }
    blankScreenDetectionConfig(value: BlankScreenDetectionConfig | undefined): this {
        throw new Error('Unimplemented method blankScreenDetectionConfig')
    }
    backToTop(value: boolean | undefined): this {
        throw new Error('Unimplemented method backToTop')
    }
    enableSelectedDataDetector(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableSelectedDataDetector')
    }
    onFirstScreenPaint(value: OnFirstScreenPaintCallback | undefined): this {
        throw new Error('Unimplemented method onFirstScreenPaint')
    }
    enableAutoFill(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableAutoFill')
    }
    onTextSelectionChange(value: TextSelectionChangeCallback | undefined): this {
        throw new Error('Unimplemented method onTextSelectionChange')
    }
    enableImageAnalyzer(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableImageAnalyzer')
    }
    onCameraCaptureStateChange(value: OnCameraCaptureStateChangeCallback | undefined): this {
        throw new Error('Unimplemented method onCameraCaptureStateChange')
    }
    onMicrophoneCaptureStateChange(value: OnMicrophoneCaptureStateChangeCallback | undefined): this {
        throw new Error('Unimplemented method onMicrophoneCaptureStateChange')
    }
    enableDefaultContextMenu(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableDefaultContextMenu')
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        throw new Error('Unimplemented method registerNativeEmbedRule')
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        throw new Error('Unimplemented method bindSelectionMenu')
    }
    attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
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
    certChainData?: Array<ArrayBuffer>;
}
export interface VerifyPinEvent {
    handler: VerifyPinHandler;
    identity: string;
}
export interface NestedScrollOptionsExt {
    scrollUp?: NestedScrollMode;
    scrollDown?: NestedScrollMode;
    scrollRight?: NestedScrollMode;
    scrollLeft?: NestedScrollMode;
}
export interface EmbedOptions {
    supportDefaultIntrinsicSize?: boolean;
    supportCssDisplayChange?: boolean;
}
export enum GestureFocusMode {
    DEFAULT = 0,
    GESTURE_TAP_AND_LONG_PRESS = 1
}
export interface AcceptableFileType {
    mimeType: string;
    acceptableType: Array<string>;
}

export enum PinVerifyResult {
    PIN_VERIFICATION_SUCCESS = 0,
    PIN_VERIFICATION_FAILED = 1
}
export enum CredentialType {
    CREDENTIAL_USER = 2,
    CREDENTIAL_APP = 3,
    CREDENTIAL_UKEY = 4
}
export interface CameraCaptureStateChangeInfo {
    originalState: CameraCaptureState;
    newState: CameraCaptureState;
}
export enum CameraCaptureState {
    NONE = 0,
    PAUSED = 1,
    ACTIVE = 2
}
export interface MicrophoneCaptureStateChangeInfo {
    originalState: MicrophoneCaptureState;
    newState: MicrophoneCaptureState;
}
export enum MicrophoneCaptureState {
    NONE = 0,
    PAUSED = 1,
    ACTIVE = 2
}
export class ArkWebComponent extends ArkCommonMethodComponent implements WebAttribute {
    getPeer(): ArkWebPeer {
        return (this.peer as ArkWebPeer)
    }
    public setWebOptions(value: WebOptions): this {
        const value_casted = value as (WebOptions)
        this.getPeer()?.setWebOptionsAttribute(value_casted)
        this.applyOptionsFinish('WebAttribute');
        return this
    }
    public javaScriptAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setJavaScriptAccessAttribute(value_casted)
        return this
    }
    public fileAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setFileAccessAttribute(value_casted)
        return this
    }
    public onlineImageAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setOnlineImageAccessAttribute(value_casted)
        return this
    }
    public domStorageAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setDomStorageAccessAttribute(value_casted)
        return this
    }
    public imageAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setImageAccessAttribute(value_casted)
        return this
    }
    public mixedMode(value: MixedMode | undefined): this {
        const value_casted = value as (MixedMode | undefined)
        this.getPeer()?.setMixedModeAttribute(value_casted)
        return this
    }
    public zoomAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setZoomAccessAttribute(value_casted)
        return this
    }
    public geolocationAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setGeolocationAccessAttribute(value_casted)
        return this
    }
    public javaScriptProxy(value: JavaScriptProxy | undefined): this {
        hookJavaScriptProxy(this, value)
        const value_casted = value as (JavaScriptProxy | undefined)
        this.getPeer()?.setJavaScriptProxyAttribute(value_casted)
        return this
    }
    public cacheMode(value: CacheMode | undefined): this {
        const value_casted = value as (CacheMode | undefined)
        this.getPeer()?.setCacheModeAttribute(value_casted)
        return this
    }
    public darkMode(value: WebDarkMode | undefined): this {
        const value_casted = value as (WebDarkMode | undefined)
        this.getPeer()?.setDarkModeAttribute(value_casted)
        return this
    }
    public forceDarkAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setForceDarkAccessAttribute(value_casted)
        return this
    }
    public mediaOptions(value: WebMediaOptions | undefined): this {
        const value_casted = value as (WebMediaOptions | undefined)
        this.getPeer()?.setMediaOptionsAttribute(value_casted)
        return this
    }
    public overviewModeAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setOverviewModeAccessAttribute(value_casted)
        return this
    }
    public overScrollMode(value: OverScrollMode | undefined): this {
        const value_casted = value as (OverScrollMode | undefined)
        this.getPeer()?.setOverScrollModeAttribute(value_casted)
        return this
    }
    public blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        const value_casted = value as (BlurOnKeyboardHideMode | undefined)
        this.getPeer()?.setBlurOnKeyboardHideModeAttribute(value_casted)
        return this
    }
    public textZoomRatio(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setTextZoomRatioAttribute(value_casted)
        return this
    }
    public databaseAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setDatabaseAccessAttribute(value_casted)
        return this
    }
    public initialScale(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setInitialScaleAttribute(value_casted)
        return this
    }
    public metaViewport(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMetaViewportAttribute(value_casted)
        return this
    }
    public onPageBegin(value: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPageBeginEvent, void> | undefined)
        this.getPeer()?.setOnPageBeginAttribute(value_casted)
        return this
    }
    public onPageEnd(value: arkui_component_common_Callback<OnPageEndEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPageEndEvent, void> | undefined)
        this.getPeer()?.setOnPageEndAttribute(value_casted)
        return this
    }
    public onLoadStarted(value: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined)
        this.getPeer()?.setOnLoadStartedAttribute(value_casted)
        return this
    }
    public onLoadFinished(value: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined)
        this.getPeer()?.setOnLoadFinishedAttribute(value_casted)
        return this
    }
    public onProgressChange(value: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined)
        this.getPeer()?.setOnProgressChangeAttribute(value_casted)
        return this
    }
    public onTitleReceive(value: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined)
        this.getPeer()?.setOnTitleReceiveAttribute(value_casted)
        return this
    }
    public onGeolocationHide(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnGeolocationHideAttribute(value_casted)
        return this
    }
    public onGeolocationShow(value: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined)
        this.getPeer()?.setOnGeolocationShowAttribute(value_casted)
        return this
    }
    public onRequestSelected(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnRequestSelectedAttribute(value_casted)
        return this
    }
    public onAlert(value: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnAlertEvent, boolean> | undefined)
        this.getPeer()?.setOnAlertAttribute(value_casted)
        return this
    }
    public onBeforeUnload(value: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined)
        this.getPeer()?.setOnBeforeUnloadAttribute(value_casted)
        return this
    }
    public onConfirm(value: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined)
        this.getPeer()?.setOnConfirmAttribute(value_casted)
        return this
    }
    public onPrompt(value: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPromptEvent, boolean> | undefined)
        this.getPeer()?.setOnPromptAttribute(value_casted)
        return this
    }
    public onConsole(value: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined)
        this.getPeer()?.setOnConsoleAttribute(value_casted)
        return this
    }
    public onErrorReceive(value: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined)
        this.getPeer()?.setOnErrorReceiveAttribute(value_casted)
        return this
    }
    public onHttpErrorReceive(value: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined)
        this.getPeer()?.setOnHttpErrorReceiveAttribute(value_casted)
        return this
    }
    public onDownloadStart(value: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined)
        this.getPeer()?.setOnDownloadStartAttribute(value_casted)
        return this
    }
    public onRefreshAccessedHistory(value: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined)
        this.getPeer()?.setOnRefreshAccessedHistoryAttribute(value_casted)
        return this
    }
    public onRenderExited(value: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined)
        this.getPeer()?.setOnRenderExitedAttribute(value_casted)
        return this
    }
    public onShowFileSelector(value: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined)
        this.getPeer()?.setOnShowFileSelectorAttribute(value_casted)
        return this
    }
    public onResourceLoad(value: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined)
        this.getPeer()?.setOnResourceLoadAttribute(value_casted)
        return this
    }
    public onFullScreenExit(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnFullScreenExitAttribute(value_casted)
        return this
    }
    public onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        const value_casted = value as (OnFullScreenEnterCallback | undefined)
        this.getPeer()?.setOnFullScreenEnterAttribute(value_casted)
        return this
    }
    public onScaleChange(value: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined)
        this.getPeer()?.setOnScaleChangeAttribute(value_casted)
        return this
    }
    public onHttpAuthRequest(value: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined)
        this.getPeer()?.setOnHttpAuthRequestAttribute(value_casted)
        return this
    }
    public onInterceptRequest(value: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined)
        this.getPeer()?.setOnInterceptRequestAttribute(value_casted)
        return this
    }
    public onPermissionRequest(value: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined)
        this.getPeer()?.setOnPermissionRequestAttribute(value_casted)
        return this
    }
    public onScreenCaptureRequest(value: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined)
        this.getPeer()?.setOnScreenCaptureRequestAttribute(value_casted)
        return this
    }
    public onContextMenuShow(value: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined)
        this.getPeer()?.setOnContextMenuShowAttribute(value_casted)
        return this
    }
    public onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        const value_casted = value as (OnContextMenuHideCallback | undefined)
        this.getPeer()?.setOnContextMenuHideAttribute(value_casted)
        return this
    }
    public mediaPlayGestureAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMediaPlayGestureAccessAttribute(value_casted)
        return this
    }
    public onSearchResultReceive(value: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined)
        this.getPeer()?.setOnSearchResultReceiveAttribute(value_casted)
        return this
    }
    public onScroll(value: arkui_component_common_Callback<OnScrollEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnScrollEvent, void> | undefined)
        this.getPeer()?.setOnScrollAttribute(value_casted)
        return this
    }
    public onSslErrorEventReceive(value: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined)
        this.getPeer()?.setOnSslErrorEventReceiveAttribute(value_casted)
        return this
    }
    public onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        const value_casted = value as (OnSslErrorEventCallback | undefined)
        this.getPeer()?.setOnSslErrorEventAttribute(value_casted)
        return this
    }
    public onClientAuthenticationRequest(value: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined)
        this.getPeer()?.setOnClientAuthenticationRequestAttribute(value_casted)
        return this
    }
    public onVerifyPin(value: OnVerifyPinCallback | undefined): this {
        const value_casted = value as (OnVerifyPinCallback | undefined)
        this.getPeer()?.setOnVerifyPinAttribute(value_casted)
        return this
    }
    public onWindowNew(value: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnWindowNewEvent, void> | undefined)
        this.getPeer()?.setOnWindowNewAttribute(value_casted)
        return this
    }
    public onWindowNewExt(value: arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined)
        this.getPeer()?.setOnWindowNewExtAttribute(value_casted)
        return this
    }
    public onWindowExit(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnWindowExitAttribute(value_casted)
        return this
    }
    public multiWindowAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMultiWindowAccessAttribute(value_casted)
        return this
    }
    public onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        const value_casted = value as (((event: KeyEvent) => boolean) | undefined)
        this.getPeer()?.setOnInterceptKeyEventAttribute(value_casted)
        return this
    }
    public webStandardFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebStandardFontAttribute(value_casted)
        return this
    }
    public webSerifFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebSerifFontAttribute(value_casted)
        return this
    }
    public webSansSerifFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebSansSerifFontAttribute(value_casted)
        return this
    }
    public webFixedFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebFixedFontAttribute(value_casted)
        return this
    }
    public webFantasyFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebFantasyFontAttribute(value_casted)
        return this
    }
    public webCursiveFont(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setWebCursiveFontAttribute(value_casted)
        return this
    }
    public defaultFixedFontSize(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setDefaultFixedFontSizeAttribute(value_casted)
        return this
    }
    public defaultFontSize(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setDefaultFontSizeAttribute(value_casted)
        return this
    }
    public minFontSize(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setMinFontSizeAttribute(value_casted)
        return this
    }
    public minLogicalFontSize(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setMinLogicalFontSizeAttribute(value_casted)
        return this
    }
    public defaultTextEncodingFormat(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setDefaultTextEncodingFormatAttribute(value_casted)
        return this
    }
    public forceDisplayScrollBar(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setForceDisplayScrollBarAttribute(value_casted)
        return this
    }
    public blockNetwork(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setBlockNetworkAttribute(value_casted)
        return this
    }
    public horizontalScrollBarAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setHorizontalScrollBarAccessAttribute(value_casted)
        return this
    }
    public verticalScrollBarAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setVerticalScrollBarAccessAttribute(value_casted)
        return this
    }
    public onTouchIconUrlReceived(value: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined)
        this.getPeer()?.setOnTouchIconUrlReceivedAttribute(value_casted)
        return this
    }
    public onFaviconReceived(value: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined)
        this.getPeer()?.setOnFaviconReceivedAttribute(value_casted)
        return this
    }
    public onPageVisible(value: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined)
        this.getPeer()?.setOnPageVisibleAttribute(value_casted)
        return this
    }
    public onDataResubmitted(value: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined)
        this.getPeer()?.setOnDataResubmittedAttribute(value_casted)
        return this
    }
    public pinchSmooth(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setPinchSmoothAttribute(value_casted)
        return this
    }
    public allowWindowOpenMethod(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setAllowWindowOpenMethodAttribute(value_casted)
        return this
    }
    public onAudioStateChanged(value: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined)
        this.getPeer()?.setOnAudioStateChangedAttribute(value_casted)
        return this
    }
    public onFirstContentfulPaint(value: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined)
        this.getPeer()?.setOnFirstContentfulPaintAttribute(value_casted)
        return this
    }
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        const value_casted = value as (OnFirstMeaningfulPaintCallback | undefined)
        this.getPeer()?.setOnFirstMeaningfulPaintAttribute(value_casted)
        return this
    }
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        const value_casted = value as (OnLargestContentfulPaintCallback | undefined)
        this.getPeer()?.setOnLargestContentfulPaintAttribute(value_casted)
        return this
    }
    public onLoadIntercept(value: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined)
        this.getPeer()?.setOnLoadInterceptAttribute(value_casted)
        return this
    }
    public onControllerAttached(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnControllerAttachedAttribute(value_casted)
        return this
    }
    public onOverScroll(value: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnOverScrollEvent, void> | undefined)
        this.getPeer()?.setOnOverScrollAttribute(value_casted)
        return this
    }
    public onPdfScrollAtBottom(value: arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined)
        this.getPeer()?.setOnPdfScrollAtBottomAttribute(value_casted)
        return this
    }
    public onPdfLoadEvent(value: arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined): this {
        const value_casted = value as (arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined)
        this.getPeer()?.setOnPdfLoadEventAttribute(value_casted)
        return this
    }
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        const value_casted = value as (OnSafeBrowsingCheckResultCallback | undefined)
        this.getPeer()?.setOnSafeBrowsingCheckResultAttribute(value_casted)
        return this
    }
    public onSafeBrowsingCheckFinish(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        const value_casted = value as (OnSafeBrowsingCheckResultCallback | undefined)
        this.getPeer()?.setOnSafeBrowsingCheckFinishAttribute(value_casted)
        return this
    }
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        const value_casted = value as (OnNavigationEntryCommittedCallback | undefined)
        this.getPeer()?.setOnNavigationEntryCommittedAttribute(value_casted)
        return this
    }
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        const value_casted = value as (OnIntelligentTrackingPreventionCallback | undefined)
        this.getPeer()?.setOnIntelligentTrackingPreventionResultAttribute(value_casted)
        return this
    }
    public javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        const value_casted = value as (Array<ScriptItem> | undefined)
        this.getPeer()?.setJavaScriptOnDocumentStartAttribute(value_casted)
        return this
    }
    public javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        const value_casted = value as (Array<ScriptItem> | undefined)
        this.getPeer()?.setJavaScriptOnDocumentEndAttribute(value_casted)
        return this
    }
    public layoutMode(value: WebLayoutMode | undefined): this {
        const value_casted = value as (WebLayoutMode | undefined)
        this.getPeer()?.setLayoutModeAttribute(value_casted)
        return this
    }
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        const value_casted = value as (NestedScrollOptions | NestedScrollOptionsExt | undefined)
        this.getPeer()?.setNestedScrollAttribute(value_casted)
        return this
    }
    public enableNativeEmbedMode(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableNativeEmbedModeAttribute(value_casted)
        return this
    }
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        const value_casted = value as (((event: NativeEmbedDataInfo) => void) | undefined)
        this.getPeer()?.setOnNativeEmbedLifecycleChangeAttribute(value_casted)
        return this
    }
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        const value_casted = value as (OnNativeEmbedVisibilityChangeCallback | undefined)
        this.getPeer()?.setOnNativeEmbedVisibilityChangeAttribute(value_casted)
        return this
    }
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        const value_casted = value as (((event: NativeEmbedTouchInfo) => void) | undefined)
        this.getPeer()?.setOnNativeEmbedGestureEventAttribute(value_casted)
        return this
    }
    public onNativeEmbedMouseEvent(value: MouseInfoCallback | undefined): this {
        const value_casted = value as (MouseInfoCallback | undefined)
        this.getPeer()?.setOnNativeEmbedMouseEventAttribute(value_casted)
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        const value_casted = value as (CopyOptions | undefined)
        this.getPeer()?.setCopyOptionsAttribute(value_casted)
        return this
    }
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        const value_casted = value as (OnOverrideUrlLoadingCallback | undefined)
        this.getPeer()?.setOnOverrideUrlLoadingAttribute(value_casted)
        return this
    }
    public onOverrideErrorPage(value: OnOverrideErrorPageCallback | undefined): this {
        const value_casted = value as (OnOverrideErrorPageCallback | undefined)
        this.getPeer()?.setOnOverrideErrorPageAttribute(value_casted)
        return this
    }
    public textAutosizing(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setTextAutosizingAttribute(value_casted)
        return this
    }
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        const value_casted = value as (NativeMediaPlayerConfig | undefined)
        this.getPeer()?.setEnableNativeMediaPlayerAttribute(value_casted)
        return this
    }
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        const value_casted = value as (OnRenderProcessNotRespondingCallback | undefined)
        this.getPeer()?.setOnRenderProcessNotRespondingAttribute(value_casted)
        return this
    }
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        const value_casted = value as (OnRenderProcessRespondingCallback | undefined)
        this.getPeer()?.setOnRenderProcessRespondingAttribute(value_casted)
        return this
    }
    public onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        const value_casted = value as (OnViewportFitChangedCallback | undefined)
        this.getPeer()?.setOnViewportFitChangedAttribute(value_casted)
        return this
    }
    public onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        const value_casted = value as (WebKeyboardCallback | undefined)
        this.getPeer()?.setOnInterceptKeyboardAttachAttribute(value_casted)
        return this
    }
    public onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        const value_casted = value as (OnAdsBlockedCallback | undefined)
        this.getPeer()?.setOnAdsBlockedAttribute(value_casted)
        return this
    }
    public keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        const value_casted = value as (WebKeyboardAvoidMode | undefined)
        this.getPeer()?.setKeyboardAvoidModeAttribute(value_casted)
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        const value_casted = value as (EditMenuOptions | undefined)
        this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
        return this
    }
    public enableFollowSystemFontWeight(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableFollowSystemFontWeightAttribute(value_casted)
        return this
    }
    public enableWebAVSession(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableWebAVSessionAttribute(value_casted)
        return this
    }
    public optimizeParserBudget(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setOptimizeParserBudgetAttribute(value_casted)
        return this
    }
    public runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        const value_casted = value as (Array<ScriptItem> | undefined)
        this.getPeer()?.setRunJavaScriptOnDocumentStartAttribute(value_casted)
        return this
    }
    public runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        const value_casted = value as (Array<ScriptItem> | undefined)
        this.getPeer()?.setRunJavaScriptOnDocumentEndAttribute(value_casted)
        return this
    }
    public runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        const value_casted = value as (Array<ScriptItem> | undefined)
        this.getPeer()?.setRunJavaScriptOnHeadEndAttribute(value_casted)
        return this
    }
    public nativeEmbedOptions(value: EmbedOptions | undefined): this {
        const value_casted = value as (EmbedOptions | undefined)
        this.getPeer()?.setNativeEmbedOptionsAttribute(value_casted)
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableDataDetectorAttribute(value_casted)
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        const value_casted = value as (TextDataDetectorConfig | undefined)
        this.getPeer()?.setDataDetectorConfigAttribute(value_casted)
        return this
    }
    public onActivateContent(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnActivateContentAttribute(value_casted)
        return this
    }
    public bypassVsyncCondition(value: WebBypassVsyncCondition | undefined): this {
        const value_casted = value as (WebBypassVsyncCondition | undefined)
        this.getPeer()?.setBypassVsyncConditionAttribute(value_casted)
        return this
    }
    public gestureFocusMode(value: GestureFocusMode | undefined): this {
        const value_casted = value as (GestureFocusMode | undefined)
        this.getPeer()?.setGestureFocusModeAttribute(value_casted)
        return this
    }
    public forceEnableZoom(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setForceEnableZoomAttribute(value_casted)
        return this
    }
    public onNativeEmbedObjectParamChange(value: OnNativeEmbedObjectParamChangeCallback | undefined): this {
        const value_casted = value as (OnNativeEmbedObjectParamChangeCallback | undefined)
        this.getPeer()?.setOnNativeEmbedObjectParamChangeAttribute(value_casted)
        return this
    }
    public rotateRenderEffect(value: WebRotateEffect | undefined): this {
        const value_casted = value as (WebRotateEffect | undefined)
        this.getPeer()?.setRotateRenderEffectAttribute(value_casted)
        return this
    }
    public zoomControlAccess(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setZoomControlAccessAttribute(value_casted)
        return this
    }
    public onDetectedBlankScreen(value: OnDetectBlankScreenCallback | undefined): this {
        const value_casted = value as (OnDetectBlankScreenCallback | undefined)
        this.getPeer()?.setOnDetectedBlankScreenAttribute(value_casted)
        return this
    }
    public blankScreenDetectionConfig(value: BlankScreenDetectionConfig | undefined): this {
        const value_casted = value as (BlankScreenDetectionConfig | undefined)
        this.getPeer()?.setBlankScreenDetectionConfigAttribute(value_casted)
        return this
    }
    public backToTop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setBackToTopAttribute(value_casted)
        return this
    }
    public enableSelectedDataDetector(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableSelectedDataDetectorAttribute(value_casted)
        return this
    }
    public onFirstScreenPaint(value: OnFirstScreenPaintCallback | undefined): this {
        const value_casted = value as (OnFirstScreenPaintCallback | undefined)
        this.getPeer()?.setOnFirstScreenPaintAttribute(value_casted)
        return this
    }
    public enableAutoFill(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableAutoFillAttribute(value_casted)
        return this
    }
    public onTextSelectionChange(value: TextSelectionChangeCallback | undefined): this {
        const value_casted = value as (TextSelectionChangeCallback | undefined)
        this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
        return this
    }
    public enableImageAnalyzer(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableImageAnalyzerAttribute(value_casted)
        return this
    }
    public onCameraCaptureStateChange(value: OnCameraCaptureStateChangeCallback | undefined): this {
        const value_casted = value as (OnCameraCaptureStateChangeCallback | undefined)
        this.getPeer()?.setOnCameraCaptureStateChangeAttribute(value_casted)
        return this
    }
    public onMicrophoneCaptureStateChange(value: OnMicrophoneCaptureStateChangeCallback | undefined): this {
        const value_casted = value as (OnMicrophoneCaptureStateChangeCallback | undefined)
        this.getPeer()?.setOnMicrophoneCaptureStateChangeAttribute(value_casted)
        return this
    }
    public enableDefaultContextMenu(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableDefaultContextMenuAttribute(value_casted)
        return this
    }
    public registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        const tag_casted = tag as (string | undefined)
        const type_casted = type as (string | undefined)
        this.getPeer()?.setRegisterNativeEmbedRuleAttribute(tag_casted, type_casted)
        return this
    }
    public bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        const elementType_casted = elementType as (WebElementType | undefined)
        const content_casted = content as (CustomBuilder | undefined)
        const responseType_casted = responseType as (WebResponseType | undefined)
        const options_casted = options as (SelectionMenuOptionsExt | undefined)
        this.getPeer()?.setBindSelectionMenuAttribute(elementType_casted, content_casted, responseType_casted, options_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookWebAttributeModifier(this, value);
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
export function WebImpl(
    @memo @memo_skip
    style: ((attributes: WebAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkWebComponent>((): ArkWebComponent => {
        return new ArkWebComponent()
    })
    NodeAttach<ArkWebPeer>((): ArkWebPeer => ArkWebPeer.create(receiver), (_: ArkWebPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class CameraCaptureStateChangeInfo_serializer {
    public static write(buffer: SerializerBase, value: CameraCaptureStateChangeInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOriginalState = value.originalState
        valueSerializer.writeInt32(valueHolderForOriginalState.valueOf())
        const valueHolderForNewState = value.newState
        valueSerializer.writeInt32(valueHolderForNewState.valueOf())
    }
    public static read(buffer: DeserializerBase): CameraCaptureStateChangeInfo {
        let valueDeserializer: DeserializerBase = buffer
        const originalStateTmpResult: CameraCaptureState = CameraCaptureState.fromValue(valueDeserializer.readInt32())
        const newStateTmpResult: CameraCaptureState = CameraCaptureState.fromValue(valueDeserializer.readInt32())
        let value: CameraCaptureStateChangeInfo = ({originalState: originalStateTmpResult, newState: newStateTmpResult} as CameraCaptureStateChangeInfo)
        return value
    }
}
export class ClientAuthenticationHandler_serializer {
    public static write(buffer: SerializerBase, value: ClientAuthenticationHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ClientAuthenticationHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ClientAuthenticationHandlerInternal.fromPtr(ptr)
    }
}
export class ConsoleMessage_serializer {
    public static write(buffer: SerializerBase, value: ConsoleMessage): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ConsoleMessage {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ConsoleMessageInternal.fromPtr(ptr)
    }
}
export class ControllerHandler_serializer {
    public static write(buffer: SerializerBase, value: ControllerHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ControllerHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ControllerHandlerInternal.fromPtr(ptr)
    }
}
export class DataResubmissionHandler_serializer {
    public static write(buffer: SerializerBase, value: DataResubmissionHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DataResubmissionHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return DataResubmissionHandlerInternal.fromPtr(ptr)
    }
}
export class EventResult_serializer {
    public static write(buffer: SerializerBase, value: EventResult): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): EventResult {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return EventResultInternal.fromPtr(ptr)
    }
}
export class FileSelectorParam_serializer {
    public static write(buffer: SerializerBase, value: FileSelectorParam): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FileSelectorParam {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return FileSelectorParamInternal.fromPtr(ptr)
    }
}
export class FileSelectorResult_serializer {
    public static write(buffer: SerializerBase, value: FileSelectorResult): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FileSelectorResult {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return FileSelectorResultInternal.fromPtr(ptr)
    }
}
export class FullScreenExitHandler_serializer {
    public static write(buffer: SerializerBase, value: FullScreenExitHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): FullScreenExitHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return FullScreenExitHandlerInternal.fromPtr(ptr)
    }
}
export class HttpAuthHandler_serializer {
    public static write(buffer: SerializerBase, value: HttpAuthHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): HttpAuthHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return HttpAuthHandlerInternal.fromPtr(ptr)
    }
}
export class JsGeolocation_serializer {
    public static write(buffer: SerializerBase, value: JsGeolocation): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): JsGeolocation {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return JsGeolocationInternal.fromPtr(ptr)
    }
}
export class JsResult_serializer {
    public static write(buffer: SerializerBase, value: JsResult): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): JsResult {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return JsResultInternal.fromPtr(ptr)
    }
}
export class MicrophoneCaptureStateChangeInfo_serializer {
    public static write(buffer: SerializerBase, value: MicrophoneCaptureStateChangeInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOriginalState = value.originalState
        valueSerializer.writeInt32(valueHolderForOriginalState.valueOf())
        const valueHolderForNewState = value.newState
        valueSerializer.writeInt32(valueHolderForNewState.valueOf())
    }
    public static read(buffer: DeserializerBase): MicrophoneCaptureStateChangeInfo {
        let valueDeserializer: DeserializerBase = buffer
        const originalStateTmpResult: MicrophoneCaptureState = MicrophoneCaptureState.fromValue(valueDeserializer.readInt32())
        const newStateTmpResult: MicrophoneCaptureState = MicrophoneCaptureState.fromValue(valueDeserializer.readInt32())
        let value: MicrophoneCaptureStateChangeInfo = ({originalState: originalStateTmpResult, newState: newStateTmpResult} as MicrophoneCaptureStateChangeInfo)
        return value
    }
}
export class NativeMediaPlayerConfig_serializer {
    public static write(buffer: SerializerBase, value: NativeMediaPlayerConfig): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEnable = value.enable
        valueSerializer.writeBoolean(valueHolderForEnable)
        const valueHolderForShouldOverlay = value.shouldOverlay
        valueSerializer.writeBoolean(valueHolderForShouldOverlay)
    }
    public static read(buffer: DeserializerBase): NativeMediaPlayerConfig {
        let valueDeserializer: DeserializerBase = buffer
        const enableTmpResult: boolean = valueDeserializer.readBoolean()
        const shouldOverlayTmpResult: boolean = valueDeserializer.readBoolean()
        let value: NativeMediaPlayerConfig = ({enable: enableTmpResult, shouldOverlay: shouldOverlayTmpResult} as NativeMediaPlayerConfig)
        return value
    }
}
export class OnAudioStateChangedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAudioStateChangedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPlaying = value.playing
        valueSerializer.writeBoolean(valueHolderForPlaying)
    }
    public static read(buffer: DeserializerBase): OnAudioStateChangedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const playingTmpResult: boolean = valueDeserializer.readBoolean()
        let value: OnAudioStateChangedEvent = ({playing: playingTmpResult} as OnAudioStateChangedEvent)
        return value
    }
}
export class OnConsoleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConsoleEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForMessage = value.message
        ConsoleMessage_serializer.write(valueSerializer, valueHolderForMessage)
    }
    public static read(buffer: DeserializerBase): OnConsoleEvent {
        let valueDeserializer: DeserializerBase = buffer
        const messageTmpResult: ConsoleMessage = (ConsoleMessage_serializer.read(valueDeserializer) as ConsoleMessage)
        let value: OnConsoleEvent = ({message: messageTmpResult} as OnConsoleEvent)
        return value
    }
}
export class OnDataResubmittedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDataResubmittedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        DataResubmissionHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnDataResubmittedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: DataResubmissionHandler = (DataResubmissionHandler_serializer.read(valueDeserializer) as DataResubmissionHandler)
        let value: OnDataResubmittedEvent = ({handler: handlerTmpResult} as OnDataResubmittedEvent)
        return value
    }
}
export class OnFaviconReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFaviconReceivedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForFavicon = value.favicon
        image_PixelMap_serializer.write(valueSerializer, valueHolderForFavicon)
    }
    public static read(buffer: DeserializerBase): OnFaviconReceivedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const faviconTmpResult: image.PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        let value: OnFaviconReceivedEvent = ({favicon: faviconTmpResult} as OnFaviconReceivedEvent)
        return value
    }
}
export class OnFirstContentfulPaintEvent_serializer {
    public static write(buffer: SerializerBase, value: OnFirstContentfulPaintEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForNavigationStartTick = value.navigationStartTick
        valueSerializer.writeInt64(valueHolderForNavigationStartTick)
        const valueHolderForFirstContentfulPaintMs = value.firstContentfulPaintMs
        valueSerializer.writeInt64(valueHolderForFirstContentfulPaintMs)
    }
    public static read(buffer: DeserializerBase): OnFirstContentfulPaintEvent {
        let valueDeserializer: DeserializerBase = buffer
        const navigationStartTickTmpResult: int64 = valueDeserializer.readInt64()
        const firstContentfulPaintMsTmpResult: int64 = valueDeserializer.readInt64()
        let value: OnFirstContentfulPaintEvent = ({navigationStartTick: navigationStartTickTmpResult, firstContentfulPaintMs: firstContentfulPaintMsTmpResult} as OnFirstContentfulPaintEvent)
        return value
    }
}
export class OnOverScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnOverScrollEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForXOffset = value.xOffset
        valueSerializer.writeFloat64(valueHolderForXOffset)
        const valueHolderForYOffset = value.yOffset
        valueSerializer.writeFloat64(valueHolderForYOffset)
    }
    public static read(buffer: DeserializerBase): OnOverScrollEvent {
        let valueDeserializer: DeserializerBase = buffer
        const xOffsetTmpResult: double = valueDeserializer.readFloat64()
        const yOffsetTmpResult: double = valueDeserializer.readFloat64()
        let value: OnOverScrollEvent = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OnOverScrollEvent)
        return value
    }
}
export class OnProgressChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnProgressChangeEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForNewProgress = value.newProgress
        valueSerializer.writeInt32(valueHolderForNewProgress)
    }
    public static read(buffer: DeserializerBase): OnProgressChangeEvent {
        let valueDeserializer: DeserializerBase = buffer
        const newProgressTmpResult: int32 = valueDeserializer.readInt32()
        let value: OnProgressChangeEvent = ({newProgress: newProgressTmpResult} as OnProgressChangeEvent)
        return value
    }
}
export class OnScaleChangeEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScaleChangeEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOldScale = value.oldScale
        valueSerializer.writeFloat64(valueHolderForOldScale)
        const valueHolderForNewScale = value.newScale
        valueSerializer.writeFloat64(valueHolderForNewScale)
    }
    public static read(buffer: DeserializerBase): OnScaleChangeEvent {
        let valueDeserializer: DeserializerBase = buffer
        const oldScaleTmpResult: double = valueDeserializer.readFloat64()
        const newScaleTmpResult: double = valueDeserializer.readFloat64()
        let value: OnScaleChangeEvent = ({oldScale: oldScaleTmpResult, newScale: newScaleTmpResult} as OnScaleChangeEvent)
        return value
    }
}
export class OnScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScrollEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForXOffset = value.xOffset
        valueSerializer.writeFloat64(valueHolderForXOffset)
        const valueHolderForYOffset = value.yOffset
        valueSerializer.writeFloat64(valueHolderForYOffset)
    }
    public static read(buffer: DeserializerBase): OnScrollEvent {
        let valueDeserializer: DeserializerBase = buffer
        const xOffsetTmpResult: double = valueDeserializer.readFloat64()
        const yOffsetTmpResult: double = valueDeserializer.readFloat64()
        let value: OnScrollEvent = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OnScrollEvent)
        return value
    }
}
export class OnSearchResultReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSearchResultReceiveEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForActiveMatchOrdinal = value.activeMatchOrdinal
        valueSerializer.writeInt32(valueHolderForActiveMatchOrdinal)
        const valueHolderForNumberOfMatches = value.numberOfMatches
        valueSerializer.writeInt32(valueHolderForNumberOfMatches)
        const valueHolderForIsDoneCounting = value.isDoneCounting
        valueSerializer.writeBoolean(valueHolderForIsDoneCounting)
    }
    public static read(buffer: DeserializerBase): OnSearchResultReceiveEvent {
        let valueDeserializer: DeserializerBase = buffer
        const activeMatchOrdinalTmpResult: int32 = valueDeserializer.readInt32()
        const numberOfMatchesTmpResult: int32 = valueDeserializer.readInt32()
        const isDoneCountingTmpResult: boolean = valueDeserializer.readBoolean()
        let value: OnSearchResultReceiveEvent = ({activeMatchOrdinal: activeMatchOrdinalTmpResult, numberOfMatches: numberOfMatchesTmpResult, isDoneCounting: isDoneCountingTmpResult} as OnSearchResultReceiveEvent)
        return value
    }
}
export class OnShowFileSelectorEvent_serializer {
    public static write(buffer: SerializerBase, value: OnShowFileSelectorEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForResult = value.result
        FileSelectorResult_serializer.write(valueSerializer, valueHolderForResult)
        const valueHolderForFileSelector = value.fileSelector
        FileSelectorParam_serializer.write(valueSerializer, valueHolderForFileSelector)
    }
    public static read(buffer: DeserializerBase): OnShowFileSelectorEvent {
        let valueDeserializer: DeserializerBase = buffer
        const resultTmpResult: FileSelectorResult = (FileSelectorResult_serializer.read(valueDeserializer) as FileSelectorResult)
        const fileSelectorTmpResult: FileSelectorParam = (FileSelectorParam_serializer.read(valueDeserializer) as FileSelectorParam)
        let value: OnShowFileSelectorEvent = ({result: resultTmpResult, fileSelector: fileSelectorTmpResult} as OnShowFileSelectorEvent)
        return value
    }
}
export class PermissionRequest_serializer {
    public static write(buffer: SerializerBase, value: PermissionRequest): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PermissionRequest {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return PermissionRequestInternal.fromPtr(ptr)
    }
}
export class ScreenCaptureHandler_serializer {
    public static write(buffer: SerializerBase, value: ScreenCaptureHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ScreenCaptureHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ScreenCaptureHandlerInternal.fromPtr(ptr)
    }
}
export class SslErrorHandler_serializer {
    public static write(buffer: SerializerBase, value: SslErrorHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SslErrorHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return SslErrorHandlerInternal.fromPtr(ptr)
    }
}
export class UrlRegexRule_serializer {
    public static write(buffer: SerializerBase, value: UrlRegexRule): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSecondLevelDomain = value.secondLevelDomain
        valueSerializer.writeString(valueHolderForSecondLevelDomain)
        const valueHolderForRule = value.rule
        valueSerializer.writeString(valueHolderForRule)
    }
    public static read(buffer: DeserializerBase): UrlRegexRule {
        let valueDeserializer: DeserializerBase = buffer
        const secondLevelDomainTmpResult: string = (valueDeserializer.readString() as string)
        const ruleTmpResult: string = (valueDeserializer.readString() as string)
        let value: UrlRegexRule = ({secondLevelDomain: secondLevelDomainTmpResult, rule: ruleTmpResult} as UrlRegexRule)
        return value
    }
}
export class VerifyPinHandler_serializer {
    public static write(buffer: SerializerBase, value: VerifyPinHandler): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): VerifyPinHandler {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return VerifyPinHandlerInternal.fromPtr(ptr)
    }
}
export class WebContextMenuParam_serializer {
    public static write(buffer: SerializerBase, value: WebContextMenuParam): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebContextMenuParam {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebContextMenuParamInternal.fromPtr(ptr)
    }
}
export class WebContextMenuResult_serializer {
    public static write(buffer: SerializerBase, value: WebContextMenuResult): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebContextMenuResult {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebContextMenuResultInternal.fromPtr(ptr)
    }
}
export class WebKeyboardController_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardController): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebKeyboardController {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebKeyboardControllerInternal.fromPtr(ptr)
    }
}
export class WebResourceError_serializer {
    public static write(buffer: SerializerBase, value: WebResourceError): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceError {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebResourceErrorInternal.fromPtr(ptr)
    }
}
export class WebResourceRequest_serializer {
    public static write(buffer: SerializerBase, value: WebResourceRequest): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceRequest {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebResourceRequestInternal.fromPtr(ptr)
    }
}
export class WebResourceResponse_serializer {
    public static write(buffer: SerializerBase, value: WebResourceResponse): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WebResourceResponse {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return WebResourceResponseInternal.fromPtr(ptr)
    }
}
export class WindowFeatures_serializer {
    public static write(buffer: SerializerBase, value: WindowFeatures): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHeight = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
        const valueHolderForWidth = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForX = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeFloat64(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): WindowFeatures {
        let valueDeserializer: DeserializerBase = buffer
        const heightTmpResult: double = valueDeserializer.readFloat64()
        const widthTmpResult: double = valueDeserializer.readFloat64()
        const xTmpResult: double = valueDeserializer.readFloat64()
        const yTmpResult: double = valueDeserializer.readFloat64()
        let value: WindowFeatures = ({height: heightTmpResult, width: widthTmpResult, x: xTmpResult, y: yTmpResult} as WindowFeatures)
        return value
    }
}
export class AcceptableFileType_serializer {
    public static write(buffer: SerializerBase, value: AcceptableFileType): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForMimeType = value.mimeType
        valueSerializer.writeString(valueHolderForMimeType)
        const valueHolderForAcceptableType = value.acceptableType
        valueSerializer.writeInt32((valueHolderForAcceptableType.length).toInt())
        for (let valueHolderForAcceptableTypeCounterI = 0; valueHolderForAcceptableTypeCounterI < valueHolderForAcceptableType.length; valueHolderForAcceptableTypeCounterI++) {
            const valueHolderForAcceptableTypeTmpElement: string = valueHolderForAcceptableType[valueHolderForAcceptableTypeCounterI]
            valueSerializer.writeString(valueHolderForAcceptableTypeTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): AcceptableFileType {
        let valueDeserializer: DeserializerBase = buffer
        const mimeTypeTmpResult: string = (valueDeserializer.readString() as string)
        const acceptableTypeTmpBufLength: int32 = valueDeserializer.readInt32()
        const acceptableTypeTmpBuf: Array<string> = new Array<string>(acceptableTypeTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const acceptableTypeTmpResult: Array<string> = acceptableTypeTmpBuf
        let value: AcceptableFileType = ({mimeType: mimeTypeTmpResult, acceptableType: acceptableTypeTmpResult} as AcceptableFileType)
        return value
    }
}
export class AdsBlockedDetails_serializer {
    public static write(buffer: SerializerBase, value: AdsBlockedDetails): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForAdsBlocked = value.adsBlocked
        valueSerializer.writeInt32((valueHolderForAdsBlocked.length).toInt())
        for (let valueHolderForAdsBlockedCounterI = 0; valueHolderForAdsBlockedCounterI < valueHolderForAdsBlocked.length; valueHolderForAdsBlockedCounterI++) {
            const valueHolderForAdsBlockedTmpElement: string = valueHolderForAdsBlocked[valueHolderForAdsBlockedCounterI]
            valueSerializer.writeString(valueHolderForAdsBlockedTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): AdsBlockedDetails {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const adsBlockedTmpBufLength: int32 = valueDeserializer.readInt32()
        const adsBlockedTmpBuf: Array<string> = new Array<string>(adsBlockedTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const adsBlockedTmpResult: Array<string> = adsBlockedTmpBuf
        let value: AdsBlockedDetails = ({url: urlTmpResult, adsBlocked: adsBlockedTmpResult} as AdsBlockedDetails)
        return value
    }
}
export class BlankScreenDetails_serializer {
    public static write(buffer: SerializerBase, value: BlankScreenDetails): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForDetectedContentfulNodesCount = value.detectedContentfulNodesCount
        if (valueHolderForDetectedContentfulNodesCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDetectedContentfulNodesCountTmpValue = valueHolderForDetectedContentfulNodesCount!
            valueSerializer.writeInt32(valueHolderForDetectedContentfulNodesCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BlankScreenDetails {
        let valueDeserializer: DeserializerBase = buffer
        const detectedContentfulNodesCountTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let detectedContentfulNodesCountTmpBuf: int32 | undefined = undefined
        if ((detectedContentfulNodesCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            detectedContentfulNodesCountTmpBuf = valueDeserializer.readInt32()
        }
        const detectedContentfulNodesCountTmpResult: int32 | undefined = detectedContentfulNodesCountTmpBuf
        let value: BlankScreenDetails = ({detectedContentfulNodesCount: detectedContentfulNodesCountTmpResult} as BlankScreenDetails)
        return value
    }
}
export class BlankScreenDetectionConfig_serializer {
    public static write(buffer: SerializerBase, value: BlankScreenDetectionConfig): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEnable = value.enable
        valueSerializer.writeBoolean(valueHolderForEnable)
        const valueHolderForDetectionTiming = value.detectionTiming
        if (valueHolderForDetectionTiming !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDetectionTimingTmpValue = valueHolderForDetectionTiming!
            valueSerializer.writeInt32((valueHolderForDetectionTimingTmpValue.length).toInt())
            for (let valueHolderForDetectionTimingTmpValueCounterI = 0; valueHolderForDetectionTimingTmpValueCounterI < valueHolderForDetectionTimingTmpValue.length; valueHolderForDetectionTimingTmpValueCounterI++) {
                const valueHolderForDetectionTimingTmpValueTmpElement: double = valueHolderForDetectionTimingTmpValue[valueHolderForDetectionTimingTmpValueCounterI]
                valueSerializer.writeFloat64(valueHolderForDetectionTimingTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDetectionMethods = value.detectionMethods
        if (valueHolderForDetectionMethods !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDetectionMethodsTmpValue = valueHolderForDetectionMethods!
            valueSerializer.writeInt32((valueHolderForDetectionMethodsTmpValue.length).toInt())
            for (let valueHolderForDetectionMethodsTmpValueCounterI = 0; valueHolderForDetectionMethodsTmpValueCounterI < valueHolderForDetectionMethodsTmpValue.length; valueHolderForDetectionMethodsTmpValueCounterI++) {
                const valueHolderForDetectionMethodsTmpValueTmpElement: BlankScreenDetectionMethod = valueHolderForDetectionMethodsTmpValue[valueHolderForDetectionMethodsTmpValueCounterI]
                valueSerializer.writeInt32(valueHolderForDetectionMethodsTmpValueTmpElement.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForContentfulNodesCountThreshold = value.contentfulNodesCountThreshold
        if (valueHolderForContentfulNodesCountThreshold !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForContentfulNodesCountThresholdTmpValue = valueHolderForContentfulNodesCountThreshold!
            valueSerializer.writeInt32(valueHolderForContentfulNodesCountThresholdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BlankScreenDetectionConfig {
        let valueDeserializer: DeserializerBase = buffer
        const enableTmpResult: boolean = valueDeserializer.readBoolean()
        const detectionTimingTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let detectionTimingTmpBuf: Array<double> | undefined = undefined
        if ((detectionTimingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const detectionTimingTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const detectionTimingTmpBufOpt: Array<double> = new Array<double>(detectionTimingTmpBufOptLength, (arg0: int32):double => {
            return valueDeserializer.readFloat64();
        })
            detectionTimingTmpBuf = detectionTimingTmpBufOpt
        }
        const detectionTimingTmpResult: Array<double> | undefined = detectionTimingTmpBuf
        const detectionMethodsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let detectionMethodsTmpBuf: Array<BlankScreenDetectionMethod> | undefined = undefined
        if ((detectionMethodsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const detectionMethodsTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const detectionMethodsTmpBufOpt: Array<BlankScreenDetectionMethod> = new Array<BlankScreenDetectionMethod>(detectionMethodsTmpBufOptLength, (arg0: int32):BlankScreenDetectionMethod => {
            return BlankScreenDetectionMethod.fromValue(valueDeserializer.readInt32());
        })
            detectionMethodsTmpBuf = detectionMethodsTmpBufOpt
        }
        const detectionMethodsTmpResult: Array<BlankScreenDetectionMethod> | undefined = detectionMethodsTmpBuf
        const contentfulNodesCountThresholdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let contentfulNodesCountThresholdTmpBuf: int32 | undefined = undefined
        if ((contentfulNodesCountThresholdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            contentfulNodesCountThresholdTmpBuf = valueDeserializer.readInt32()
        }
        const contentfulNodesCountThresholdTmpResult: int32 | undefined = contentfulNodesCountThresholdTmpBuf
        let value: BlankScreenDetectionConfig = ({enable: enableTmpResult, detectionTiming: detectionTimingTmpResult, detectionMethods: detectionMethodsTmpResult, contentfulNodesCountThreshold: contentfulNodesCountThresholdTmpResult} as BlankScreenDetectionConfig)
        return value
    }
}
export class EmbedOptions_serializer {
    public static write(buffer: SerializerBase, value: EmbedOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSupportDefaultIntrinsicSize = value.supportDefaultIntrinsicSize
        if (valueHolderForSupportDefaultIntrinsicSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSupportDefaultIntrinsicSizeTmpValue = valueHolderForSupportDefaultIntrinsicSize!
            valueSerializer.writeBoolean(valueHolderForSupportDefaultIntrinsicSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSupportCssDisplayChange = value.supportCssDisplayChange
        if (valueHolderForSupportCssDisplayChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSupportCssDisplayChangeTmpValue = valueHolderForSupportCssDisplayChange!
            valueSerializer.writeBoolean(valueHolderForSupportCssDisplayChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmbedOptions {
        let valueDeserializer: DeserializerBase = buffer
        const supportDefaultIntrinsicSizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let supportDefaultIntrinsicSizeTmpBuf: boolean | undefined = undefined
        if ((supportDefaultIntrinsicSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            supportDefaultIntrinsicSizeTmpBuf = valueDeserializer.readBoolean()
        }
        const supportDefaultIntrinsicSizeTmpResult: boolean | undefined = supportDefaultIntrinsicSizeTmpBuf
        const supportCssDisplayChangeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let supportCssDisplayChangeTmpBuf: boolean | undefined = undefined
        if ((supportCssDisplayChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            supportCssDisplayChangeTmpBuf = valueDeserializer.readBoolean()
        }
        const supportCssDisplayChangeTmpResult: boolean | undefined = supportCssDisplayChangeTmpBuf
        let value: EmbedOptions = ({supportDefaultIntrinsicSize: supportDefaultIntrinsicSizeTmpResult, supportCssDisplayChange: supportCssDisplayChangeTmpResult} as EmbedOptions)
        return value
    }
}
export class FirstMeaningfulPaint_serializer {
    public static write(buffer: SerializerBase, value: FirstMeaningfulPaint): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForNavigationStartTime = value.navigationStartTime
        if (valueHolderForNavigationStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNavigationStartTimeTmpValue = valueHolderForNavigationStartTime!
            valueSerializer.writeInt64(valueHolderForNavigationStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFirstMeaningfulPaintTime = value.firstMeaningfulPaintTime
        if (valueHolderForFirstMeaningfulPaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFirstMeaningfulPaintTimeTmpValue = valueHolderForFirstMeaningfulPaintTime!
            valueSerializer.writeInt64(valueHolderForFirstMeaningfulPaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FirstMeaningfulPaint {
        let valueDeserializer: DeserializerBase = buffer
        const navigationStartTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let navigationStartTimeTmpBuf: int64 | undefined = undefined
        if ((navigationStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            navigationStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const navigationStartTimeTmpResult: int64 | undefined = navigationStartTimeTmpBuf
        const firstMeaningfulPaintTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let firstMeaningfulPaintTimeTmpBuf: int64 | undefined = undefined
        if ((firstMeaningfulPaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            firstMeaningfulPaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const firstMeaningfulPaintTimeTmpResult: int64 | undefined = firstMeaningfulPaintTimeTmpBuf
        let value: FirstMeaningfulPaint = ({navigationStartTime: navigationStartTimeTmpResult, firstMeaningfulPaintTime: firstMeaningfulPaintTimeTmpResult} as FirstMeaningfulPaint)
        return value
    }
}
export class FirstScreenPaint_serializer {
    public static write(buffer: SerializerBase, value: FirstScreenPaint): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForNavigationStartTime = value.navigationStartTime
        valueSerializer.writeInt64(valueHolderForNavigationStartTime)
        const valueHolderForFirstScreenPaintTime = value.firstScreenPaintTime
        valueSerializer.writeInt64(valueHolderForFirstScreenPaintTime)
    }
    public static read(buffer: DeserializerBase): FirstScreenPaint {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const navigationStartTimeTmpResult: int64 = valueDeserializer.readInt64()
        const firstScreenPaintTimeTmpResult: int64 = valueDeserializer.readInt64()
        let value: FirstScreenPaint = ({url: urlTmpResult, navigationStartTime: navigationStartTimeTmpResult, firstScreenPaintTime: firstScreenPaintTimeTmpResult} as FirstScreenPaint)
        return value
    }
}
export class FullScreenEnterEvent_serializer {
    public static write(buffer: SerializerBase, value: FullScreenEnterEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        FullScreenExitHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForVideoWidth = value.videoWidth
        if (valueHolderForVideoWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVideoWidthTmpValue = valueHolderForVideoWidth!
            valueSerializer.writeInt32(valueHolderForVideoWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVideoHeight = value.videoHeight
        if (valueHolderForVideoHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVideoHeightTmpValue = valueHolderForVideoHeight!
            valueSerializer.writeInt32(valueHolderForVideoHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FullScreenEnterEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: FullScreenExitHandler = (FullScreenExitHandler_serializer.read(valueDeserializer) as FullScreenExitHandler)
        const videoWidthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let videoWidthTmpBuf: int32 | undefined = undefined
        if ((videoWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            videoWidthTmpBuf = valueDeserializer.readInt32()
        }
        const videoWidthTmpResult: int32 | undefined = videoWidthTmpBuf
        const videoHeightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let videoHeightTmpBuf: int32 | undefined = undefined
        if ((videoHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            videoHeightTmpBuf = valueDeserializer.readInt32()
        }
        const videoHeightTmpResult: int32 | undefined = videoHeightTmpBuf
        let value: FullScreenEnterEvent = ({handler: handlerTmpResult, videoWidth: videoWidthTmpResult, videoHeight: videoHeightTmpResult} as FullScreenEnterEvent)
        return value
    }
}
export class Header_serializer {
    public static write(buffer: SerializerBase, value: Header): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHeaderKey = value.headerKey
        valueSerializer.writeString(valueHolderForHeaderKey)
        const valueHolderForHeaderValue = value.headerValue
        valueSerializer.writeString(valueHolderForHeaderValue)
    }
    public static read(buffer: DeserializerBase): Header {
        let valueDeserializer: DeserializerBase = buffer
        const headerKeyTmpResult: string = (valueDeserializer.readString() as string)
        const headerValueTmpResult: string = (valueDeserializer.readString() as string)
        let value: Header = ({headerKey: headerKeyTmpResult, headerValue: headerValueTmpResult} as Header)
        return value
    }
}
export class IntelligentTrackingPreventionDetails_serializer {
    public static write(buffer: SerializerBase, value: IntelligentTrackingPreventionDetails): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHost = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForTrackerHost = value.trackerHost
        valueSerializer.writeString(valueHolderForTrackerHost)
    }
    public static read(buffer: DeserializerBase): IntelligentTrackingPreventionDetails {
        let valueDeserializer: DeserializerBase = buffer
        const hostTmpResult: string = (valueDeserializer.readString() as string)
        const trackerHostTmpResult: string = (valueDeserializer.readString() as string)
        let value: IntelligentTrackingPreventionDetails = ({host: hostTmpResult, trackerHost: trackerHostTmpResult} as IntelligentTrackingPreventionDetails)
        return value
    }
}
export class JavaScriptProxy_serializer {
    public static write(buffer: SerializerBase, value: JavaScriptProxy): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForJsObject = value.jsObject
        valueSerializer.holdAndWriteObject(valueHolderForJsObject)
        const valueHolderForName = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForMethodList = value.methodList
        valueSerializer.writeInt32((valueHolderForMethodList.length).toInt())
        for (let valueHolderForMethodListCounterI = 0; valueHolderForMethodListCounterI < valueHolderForMethodList.length; valueHolderForMethodListCounterI++) {
            const valueHolderForMethodListTmpElement: string = valueHolderForMethodList[valueHolderForMethodListCounterI]
            valueSerializer.writeString(valueHolderForMethodListTmpElement)
        }
        const valueHolderForController = value.controller
        webview_WebviewController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForAsyncMethodList = value.asyncMethodList
        if (valueHolderForAsyncMethodList !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAsyncMethodListTmpValue = valueHolderForAsyncMethodList!
            valueSerializer.writeInt32((valueHolderForAsyncMethodListTmpValue.length).toInt())
            for (let valueHolderForAsyncMethodListTmpValueCounterI = 0; valueHolderForAsyncMethodListTmpValueCounterI < valueHolderForAsyncMethodListTmpValue.length; valueHolderForAsyncMethodListTmpValueCounterI++) {
                const valueHolderForAsyncMethodListTmpValueTmpElement: string = valueHolderForAsyncMethodListTmpValue[valueHolderForAsyncMethodListTmpValueCounterI]
                valueSerializer.writeString(valueHolderForAsyncMethodListTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPermission = value.permission
        if (valueHolderForPermission !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPermissionTmpValue = valueHolderForPermission!
            valueSerializer.writeString(valueHolderForPermissionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): JavaScriptProxy {
        let valueDeserializer: DeserializerBase = buffer
        const jsObjectTmpResult: Object = (valueDeserializer.readObject() as object)
        const nameTmpResult: string = (valueDeserializer.readString() as string)
        const methodListTmpBufLength: int32 = valueDeserializer.readInt32()
        const methodListTmpBuf: Array<string> = new Array<string>(methodListTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const methodListTmpResult: Array<string> = methodListTmpBuf
        const controllerTmpResult: WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const asyncMethodListTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let asyncMethodListTmpBuf: Array<string> | undefined = undefined
        if ((asyncMethodListTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const asyncMethodListTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const asyncMethodListTmpBufOpt: Array<string> = new Array<string>(asyncMethodListTmpBufOptLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
            asyncMethodListTmpBuf = asyncMethodListTmpBufOpt
        }
        const asyncMethodListTmpResult: Array<string> | undefined = asyncMethodListTmpBuf
        const permissionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let permissionTmpBuf: string | undefined = undefined
        if ((permissionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            permissionTmpBuf = (valueDeserializer.readString() as string)
        }
        const permissionTmpResult: string | undefined = permissionTmpBuf
        let value: JavaScriptProxy = ({jsObject: jsObjectTmpResult, name: nameTmpResult, methodList: methodListTmpResult, controller: controllerTmpResult, asyncMethodList: asyncMethodListTmpResult, permission: permissionTmpResult} as JavaScriptProxy)
        return value
    }
}
export class LargestContentfulPaint_serializer {
    public static write(buffer: SerializerBase, value: LargestContentfulPaint): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForNavigationStartTime = value.navigationStartTime
        if (valueHolderForNavigationStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNavigationStartTimeTmpValue = valueHolderForNavigationStartTime!
            valueSerializer.writeInt64(valueHolderForNavigationStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImagePaintTime = value.largestImagePaintTime
        if (valueHolderForLargestImagePaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImagePaintTimeTmpValue = valueHolderForLargestImagePaintTime!
            valueSerializer.writeInt64(valueHolderForLargestImagePaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestTextPaintTime = value.largestTextPaintTime
        if (valueHolderForLargestTextPaintTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestTextPaintTimeTmpValue = valueHolderForLargestTextPaintTime!
            valueSerializer.writeInt64(valueHolderForLargestTextPaintTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageBPP = value.imageBPP
        if (valueHolderForImageBPP !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageBPPTmpValue = valueHolderForImageBPP!
            valueSerializer.writeFloat64(valueHolderForImageBPPTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImageLoadStartTime = value.largestImageLoadStartTime
        if (valueHolderForLargestImageLoadStartTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImageLoadStartTimeTmpValue = valueHolderForLargestImageLoadStartTime!
            valueSerializer.writeInt64(valueHolderForLargestImageLoadStartTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLargestImageLoadEndTime = value.largestImageLoadEndTime
        if (valueHolderForLargestImageLoadEndTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLargestImageLoadEndTimeTmpValue = valueHolderForLargestImageLoadEndTime!
            valueSerializer.writeInt64(valueHolderForLargestImageLoadEndTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LargestContentfulPaint {
        let valueDeserializer: DeserializerBase = buffer
        const navigationStartTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let navigationStartTimeTmpBuf: int64 | undefined = undefined
        if ((navigationStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            navigationStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const navigationStartTimeTmpResult: int64 | undefined = navigationStartTimeTmpBuf
        const largestImagePaintTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let largestImagePaintTimeTmpBuf: int64 | undefined = undefined
        if ((largestImagePaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImagePaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImagePaintTimeTmpResult: int64 | undefined = largestImagePaintTimeTmpBuf
        const largestTextPaintTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let largestTextPaintTimeTmpBuf: int64 | undefined = undefined
        if ((largestTextPaintTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestTextPaintTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestTextPaintTimeTmpResult: int64 | undefined = largestTextPaintTimeTmpBuf
        const imageBPPTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let imageBPPTmpBuf: double | undefined = undefined
        if ((imageBPPTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageBPPTmpBuf = valueDeserializer.readFloat64()
        }
        const imageBPPTmpResult: double | undefined = imageBPPTmpBuf
        const largestImageLoadStartTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let largestImageLoadStartTimeTmpBuf: int64 | undefined = undefined
        if ((largestImageLoadStartTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImageLoadStartTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImageLoadStartTimeTmpResult: int64 | undefined = largestImageLoadStartTimeTmpBuf
        const largestImageLoadEndTimeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let largestImageLoadEndTimeTmpBuf: int64 | undefined = undefined
        if ((largestImageLoadEndTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            largestImageLoadEndTimeTmpBuf = valueDeserializer.readInt64()
        }
        const largestImageLoadEndTimeTmpResult: int64 | undefined = largestImageLoadEndTimeTmpBuf
        let value: LargestContentfulPaint = ({navigationStartTime: navigationStartTimeTmpResult, largestImagePaintTime: largestImagePaintTimeTmpResult, largestTextPaintTime: largestTextPaintTimeTmpResult, imageBPP: imageBPPTmpResult, largestImageLoadStartTime: largestImageLoadStartTimeTmpResult, largestImageLoadEndTime: largestImageLoadEndTimeTmpResult} as LargestContentfulPaint)
        return value
    }
}
export class LoadCommittedDetails_serializer {
    public static write(buffer: SerializerBase, value: LoadCommittedDetails): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForIsMainFrame = value.isMainFrame
        valueSerializer.writeBoolean(valueHolderForIsMainFrame)
        const valueHolderForIsSameDocument = value.isSameDocument
        valueSerializer.writeBoolean(valueHolderForIsSameDocument)
        const valueHolderForDidReplaceEntry = value.didReplaceEntry
        valueSerializer.writeBoolean(valueHolderForDidReplaceEntry)
        const valueHolderForNavigationType = value.navigationType
        valueSerializer.writeInt32(valueHolderForNavigationType.valueOf())
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): LoadCommittedDetails {
        let valueDeserializer: DeserializerBase = buffer
        const isMainFrameTmpResult: boolean = valueDeserializer.readBoolean()
        const isSameDocumentTmpResult: boolean = valueDeserializer.readBoolean()
        const didReplaceEntryTmpResult: boolean = valueDeserializer.readBoolean()
        const navigationTypeTmpResult: WebNavigationType = WebNavigationType.fromValue(valueDeserializer.readInt32())
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: LoadCommittedDetails = ({isMainFrame: isMainFrameTmpResult, isSameDocument: isSameDocumentTmpResult, didReplaceEntry: didReplaceEntryTmpResult, navigationType: navigationTypeTmpResult, url: urlTmpResult} as LoadCommittedDetails)
        return value
    }
}
export class NativeEmbedMouseInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedMouseInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEmbedId = value.embedId
        if (valueHolderForEmbedId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmbedIdTmpValue = valueHolderForEmbedId!
            valueSerializer.writeString(valueHolderForEmbedIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMouseEvent = value.mouseEvent
        if (valueHolderForMouseEvent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMouseEventTmpValue = valueHolderForMouseEvent!
            MouseEvent_serializer.write(valueSerializer, valueHolderForMouseEventTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForResult = value.result
        if (valueHolderForResult !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResultTmpValue = valueHolderForResult!
            EventResult_serializer.write(valueSerializer, valueHolderForResultTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedMouseInfo {
        let valueDeserializer: DeserializerBase = buffer
        const embedIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let embedIdTmpBuf: string | undefined = undefined
        if ((embedIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            embedIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const embedIdTmpResult: string | undefined = embedIdTmpBuf
        const mouseEventTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let mouseEventTmpBuf: MouseEvent | undefined = undefined
        if ((mouseEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mouseEventTmpBuf = (MouseEvent_serializer.read(valueDeserializer) as MouseEvent)
        }
        const mouseEventTmpResult: MouseEvent | undefined = mouseEventTmpBuf
        const resultTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let resultTmpBuf: EventResult | undefined = undefined
        if ((resultTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            resultTmpBuf = (EventResult_serializer.read(valueDeserializer) as EventResult)
        }
        const resultTmpResult: EventResult | undefined = resultTmpBuf
        let value: NativeEmbedMouseInfo = ({embedId: embedIdTmpResult, mouseEvent: mouseEventTmpResult, result: resultTmpResult} as NativeEmbedMouseInfo)
        return value
    }
}
export class NativeEmbedParamDataInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedParamDataInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEmbedId = value.embedId
        valueSerializer.writeString(valueHolderForEmbedId)
        const valueHolderForObjectAttributeId = value.objectAttributeId
        if (valueHolderForObjectAttributeId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForObjectAttributeIdTmpValue = valueHolderForObjectAttributeId!
            valueSerializer.writeString(valueHolderForObjectAttributeIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParamItems = value.paramItems
        if (valueHolderForParamItems !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamItemsTmpValue = valueHolderForParamItems!
            valueSerializer.writeInt32((valueHolderForParamItemsTmpValue.length).toInt())
            for (let valueHolderForParamItemsTmpValueCounterI = 0; valueHolderForParamItemsTmpValueCounterI < valueHolderForParamItemsTmpValue.length; valueHolderForParamItemsTmpValueCounterI++) {
                const valueHolderForParamItemsTmpValueTmpElement: NativeEmbedParamItem = valueHolderForParamItemsTmpValue[valueHolderForParamItemsTmpValueCounterI]
                NativeEmbedParamItem_serializer.write(valueSerializer, valueHolderForParamItemsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedParamDataInfo {
        let valueDeserializer: DeserializerBase = buffer
        const embedIdTmpResult: string = (valueDeserializer.readString() as string)
        const objectAttributeIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let objectAttributeIdTmpBuf: string | undefined = undefined
        if ((objectAttributeIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            objectAttributeIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const objectAttributeIdTmpResult: string | undefined = objectAttributeIdTmpBuf
        const paramItemsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let paramItemsTmpBuf: Array<NativeEmbedParamItem> | undefined = undefined
        if ((paramItemsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const paramItemsTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const paramItemsTmpBufOpt: Array<NativeEmbedParamItem> = new Array<NativeEmbedParamItem>(paramItemsTmpBufOptLength, (arg0: int32):NativeEmbedParamItem => {
            return NativeEmbedParamItem_serializer.read(valueDeserializer);
        })
            paramItemsTmpBuf = paramItemsTmpBufOpt
        }
        const paramItemsTmpResult: Array<NativeEmbedParamItem> | undefined = paramItemsTmpBuf
        let value: NativeEmbedParamDataInfo = ({embedId: embedIdTmpResult, objectAttributeId: objectAttributeIdTmpResult, paramItems: paramItemsTmpResult} as NativeEmbedParamDataInfo)
        return value
    }
}
export class NativeEmbedParamItem_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedParamItem): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStatus = value.status
        valueSerializer.writeInt32(valueHolderForStatus.valueOf())
        const valueHolderForId = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForName = value.name
        if (valueHolderForName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNameTmpValue = valueHolderForName!
            valueSerializer.writeString(valueHolderForNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValue = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue = valueHolderForValue!
            valueSerializer.writeString(valueHolderForValueTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedParamItem {
        let valueDeserializer: DeserializerBase = buffer
        const statusTmpResult: NativeEmbedParamStatus = NativeEmbedParamStatus.fromValue(valueDeserializer.readInt32())
        const idTmpResult: string = (valueDeserializer.readString() as string)
        const nameTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let nameTmpBuf: string | undefined = undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult: string | undefined = nameTmpBuf
        const valueTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf: string | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        }
        const valueTmpResult: string | undefined = valueTmpBuf
        let value: NativeEmbedParamItem = ({status: statusTmpResult, id: idTmpResult, name: nameTmpResult, value: valueTmpResult} as NativeEmbedParamItem)
        return value
    }
}
export class NativeEmbedTouchInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedTouchInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEmbedId = value.embedId
        if (valueHolderForEmbedId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmbedIdTmpValue = valueHolderForEmbedId!
            valueSerializer.writeString(valueHolderForEmbedIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTouchEvent = value.touchEvent
        if (valueHolderForTouchEvent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTouchEventTmpValue = valueHolderForTouchEvent!
            TouchEvent_serializer.write(valueSerializer, valueHolderForTouchEventTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForResult = value.result
        if (valueHolderForResult !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResultTmpValue = valueHolderForResult!
            EventResult_serializer.write(valueSerializer, valueHolderForResultTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedTouchInfo {
        let valueDeserializer: DeserializerBase = buffer
        const embedIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let embedIdTmpBuf: string | undefined = undefined
        if ((embedIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            embedIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const embedIdTmpResult: string | undefined = embedIdTmpBuf
        const touchEventTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let touchEventTmpBuf: TouchEvent | undefined = undefined
        if ((touchEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            touchEventTmpBuf = (TouchEvent_serializer.read(valueDeserializer) as TouchEvent)
        }
        const touchEventTmpResult: TouchEvent | undefined = touchEventTmpBuf
        const resultTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let resultTmpBuf: EventResult | undefined = undefined
        if ((resultTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            resultTmpBuf = (EventResult_serializer.read(valueDeserializer) as EventResult)
        }
        const resultTmpResult: EventResult | undefined = resultTmpBuf
        let value: NativeEmbedTouchInfo = ({embedId: embedIdTmpResult, touchEvent: touchEventTmpResult, result: resultTmpResult} as NativeEmbedTouchInfo)
        return value
    }
}
export class NativeEmbedVisibilityInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedVisibilityInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForVisibility = value.visibility
        valueSerializer.writeBoolean(valueHolderForVisibility)
        const valueHolderForEmbedId = value.embedId
        valueSerializer.writeString(valueHolderForEmbedId)
    }
    public static read(buffer: DeserializerBase): NativeEmbedVisibilityInfo {
        let valueDeserializer: DeserializerBase = buffer
        const visibilityTmpResult: boolean = valueDeserializer.readBoolean()
        const embedIdTmpResult: string = (valueDeserializer.readString() as string)
        let value: NativeEmbedVisibilityInfo = ({visibility: visibilityTmpResult, embedId: embedIdTmpResult} as NativeEmbedVisibilityInfo)
        return value
    }
}
export class NestedScrollOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: NestedScrollOptionsExt): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForScrollUp = value.scrollUp
        if (valueHolderForScrollUp !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollUpTmpValue = (valueHolderForScrollUp as NestedScrollMode)
            valueSerializer.writeInt32(valueHolderForScrollUpTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollDown = value.scrollDown
        if (valueHolderForScrollDown !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollDownTmpValue = (valueHolderForScrollDown as NestedScrollMode)
            valueSerializer.writeInt32(valueHolderForScrollDownTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollRight = value.scrollRight
        if (valueHolderForScrollRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollRightTmpValue = (valueHolderForScrollRight as NestedScrollMode)
            valueSerializer.writeInt32(valueHolderForScrollRightTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScrollLeft = value.scrollLeft
        if (valueHolderForScrollLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollLeftTmpValue = (valueHolderForScrollLeft as NestedScrollMode)
            valueSerializer.writeInt32(valueHolderForScrollLeftTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NestedScrollOptionsExt {
        let valueDeserializer: DeserializerBase = buffer
        const scrollUpTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scrollUpTmpBuf: NestedScrollMode | undefined = undefined
        if ((scrollUpTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollUpTmpBuf = NestedScrollMode.fromValue(valueDeserializer.readInt32())
        }
        const scrollUpTmpResult: NestedScrollMode | undefined = scrollUpTmpBuf
        const scrollDownTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scrollDownTmpBuf: NestedScrollMode | undefined = undefined
        if ((scrollDownTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollDownTmpBuf = NestedScrollMode.fromValue(valueDeserializer.readInt32())
        }
        const scrollDownTmpResult: NestedScrollMode | undefined = scrollDownTmpBuf
        const scrollRightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scrollRightTmpBuf: NestedScrollMode | undefined = undefined
        if ((scrollRightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollRightTmpBuf = NestedScrollMode.fromValue(valueDeserializer.readInt32())
        }
        const scrollRightTmpResult: NestedScrollMode | undefined = scrollRightTmpBuf
        const scrollLeftTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scrollLeftTmpBuf: NestedScrollMode | undefined = undefined
        if ((scrollLeftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollLeftTmpBuf = NestedScrollMode.fromValue(valueDeserializer.readInt32())
        }
        const scrollLeftTmpResult: NestedScrollMode | undefined = scrollLeftTmpBuf
        let value: NestedScrollOptionsExt = ({scrollUp: scrollUpTmpResult, scrollDown: scrollDownTmpResult, scrollRight: scrollRightTmpResult, scrollLeft: scrollLeftTmpResult} as NestedScrollOptionsExt)
        return value
    }
}
export class OnAlertEvent_serializer {
    public static write(buffer: SerializerBase, value: OnAlertEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnAlertEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const resultTmpResult: JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value: OnAlertEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult} as OnAlertEvent)
        return value
    }
}
export class OnBeforeUnloadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnBeforeUnloadEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
        const valueHolderForIsReload = value.isReload
        if (valueHolderForIsReload !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsReloadTmpValue = valueHolderForIsReload!
            valueSerializer.writeBoolean(valueHolderForIsReloadTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OnBeforeUnloadEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const resultTmpResult: JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        const isReloadTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let isReloadTmpBuf: boolean | undefined = undefined
        if ((isReloadTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isReloadTmpBuf = valueDeserializer.readBoolean()
        }
        const isReloadTmpResult: boolean | undefined = isReloadTmpBuf
        let value: OnBeforeUnloadEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult, isReload: isReloadTmpResult} as OnBeforeUnloadEvent)
        return value
    }
}
export class OnClientAuthenticationEvent_serializer {
    public static write(buffer: SerializerBase, value: OnClientAuthenticationEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        ClientAuthenticationHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForHost = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForPort = value.port
        valueSerializer.writeInt32(valueHolderForPort)
        const valueHolderForKeyTypes = value.keyTypes
        valueSerializer.writeInt32((valueHolderForKeyTypes.length).toInt())
        for (let valueHolderForKeyTypesCounterI = 0; valueHolderForKeyTypesCounterI < valueHolderForKeyTypes.length; valueHolderForKeyTypesCounterI++) {
            const valueHolderForKeyTypesTmpElement: string = valueHolderForKeyTypes[valueHolderForKeyTypesCounterI]
            valueSerializer.writeString(valueHolderForKeyTypesTmpElement)
        }
        const valueHolderForIssuers = value.issuers
        valueSerializer.writeInt32((valueHolderForIssuers.length).toInt())
        for (let valueHolderForIssuersCounterI = 0; valueHolderForIssuersCounterI < valueHolderForIssuers.length; valueHolderForIssuersCounterI++) {
            const valueHolderForIssuersTmpElement: string = valueHolderForIssuers[valueHolderForIssuersCounterI]
            valueSerializer.writeString(valueHolderForIssuersTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): OnClientAuthenticationEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: ClientAuthenticationHandler = (ClientAuthenticationHandler_serializer.read(valueDeserializer) as ClientAuthenticationHandler)
        const hostTmpResult: string = (valueDeserializer.readString() as string)
        const portTmpResult: int32 = valueDeserializer.readInt32()
        const keyTypesTmpBufLength: int32 = valueDeserializer.readInt32()
        const keyTypesTmpBuf: Array<string> = new Array<string>(keyTypesTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const keyTypesTmpResult: Array<string> = keyTypesTmpBuf
        const issuersTmpBufLength: int32 = valueDeserializer.readInt32()
        const issuersTmpBuf: Array<string> = new Array<string>(issuersTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const issuersTmpResult: Array<string> = issuersTmpBuf
        let value: OnClientAuthenticationEvent = ({handler: handlerTmpResult, host: hostTmpResult, port: portTmpResult, keyTypes: keyTypesTmpResult, issuers: issuersTmpResult} as OnClientAuthenticationEvent)
        return value
    }
}
export class OnConfirmEvent_serializer {
    public static write(buffer: SerializerBase, value: OnConfirmEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForResult = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnConfirmEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const resultTmpResult: JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value: OnConfirmEvent = ({url: urlTmpResult, message: messageTmpResult, result: resultTmpResult} as OnConfirmEvent)
        return value
    }
}
export class OnContextMenuShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnContextMenuShowEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForParam = value.param
        WebContextMenuParam_serializer.write(valueSerializer, valueHolderForParam)
        const valueHolderForResult = value.result
        WebContextMenuResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnContextMenuShowEvent {
        let valueDeserializer: DeserializerBase = buffer
        const paramTmpResult: WebContextMenuParam = (WebContextMenuParam_serializer.read(valueDeserializer) as WebContextMenuParam)
        const resultTmpResult: WebContextMenuResult = (WebContextMenuResult_serializer.read(valueDeserializer) as WebContextMenuResult)
        let value: OnContextMenuShowEvent = ({param: paramTmpResult, result: resultTmpResult} as OnContextMenuShowEvent)
        return value
    }
}
export class OnDownloadStartEvent_serializer {
    public static write(buffer: SerializerBase, value: OnDownloadStartEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForUserAgent = value.userAgent
        valueSerializer.writeString(valueHolderForUserAgent)
        const valueHolderForContentDisposition = value.contentDisposition
        valueSerializer.writeString(valueHolderForContentDisposition)
        const valueHolderForMimetype = value.mimetype
        valueSerializer.writeString(valueHolderForMimetype)
        const valueHolderForContentLength = value.contentLength
        valueSerializer.writeInt64(valueHolderForContentLength)
    }
    public static read(buffer: DeserializerBase): OnDownloadStartEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const userAgentTmpResult: string = (valueDeserializer.readString() as string)
        const contentDispositionTmpResult: string = (valueDeserializer.readString() as string)
        const mimetypeTmpResult: string = (valueDeserializer.readString() as string)
        const contentLengthTmpResult: int64 = valueDeserializer.readInt64()
        let value: OnDownloadStartEvent = ({url: urlTmpResult, userAgent: userAgentTmpResult, contentDisposition: contentDispositionTmpResult, mimetype: mimetypeTmpResult, contentLength: contentLengthTmpResult} as OnDownloadStartEvent)
        return value
    }
}
export class OnErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnErrorReceiveEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRequest = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
        const valueHolderForError = value.error
        WebResourceError_serializer.write(valueSerializer, valueHolderForError)
    }
    public static read(buffer: DeserializerBase): OnErrorReceiveEvent {
        let valueDeserializer: DeserializerBase = buffer
        const requestTmpResult: WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const errorTmpResult: WebResourceError = (WebResourceError_serializer.read(valueDeserializer) as WebResourceError)
        let value: OnErrorReceiveEvent = ({request: requestTmpResult, error: errorTmpResult} as OnErrorReceiveEvent)
        return value
    }
}
export class OnGeolocationShowEvent_serializer {
    public static write(buffer: SerializerBase, value: OnGeolocationShowEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOrigin = value.origin
        valueSerializer.writeString(valueHolderForOrigin)
        const valueHolderForGeolocation = value.geolocation
        JsGeolocation_serializer.write(valueSerializer, valueHolderForGeolocation)
    }
    public static read(buffer: DeserializerBase): OnGeolocationShowEvent {
        let valueDeserializer: DeserializerBase = buffer
        const originTmpResult: string = (valueDeserializer.readString() as string)
        const geolocationTmpResult: JsGeolocation = (JsGeolocation_serializer.read(valueDeserializer) as JsGeolocation)
        let value: OnGeolocationShowEvent = ({origin: originTmpResult, geolocation: geolocationTmpResult} as OnGeolocationShowEvent)
        return value
    }
}
export class OnHttpAuthRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpAuthRequestEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        HttpAuthHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForHost = value.host
        valueSerializer.writeString(valueHolderForHost)
        const valueHolderForRealm = value.realm
        valueSerializer.writeString(valueHolderForRealm)
    }
    public static read(buffer: DeserializerBase): OnHttpAuthRequestEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: HttpAuthHandler = (HttpAuthHandler_serializer.read(valueDeserializer) as HttpAuthHandler)
        const hostTmpResult: string = (valueDeserializer.readString() as string)
        const realmTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnHttpAuthRequestEvent = ({handler: handlerTmpResult, host: hostTmpResult, realm: realmTmpResult} as OnHttpAuthRequestEvent)
        return value
    }
}
export class OnHttpErrorReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnHttpErrorReceiveEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRequest = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
        const valueHolderForResponse = value.response
        WebResourceResponse_serializer.write(valueSerializer, valueHolderForResponse)
    }
    public static read(buffer: DeserializerBase): OnHttpErrorReceiveEvent {
        let valueDeserializer: DeserializerBase = buffer
        const requestTmpResult: WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        const responseTmpResult: WebResourceResponse = (WebResourceResponse_serializer.read(valueDeserializer) as WebResourceResponse)
        let value: OnHttpErrorReceiveEvent = ({request: requestTmpResult, response: responseTmpResult} as OnHttpErrorReceiveEvent)
        return value
    }
}
export class OnInterceptRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnInterceptRequestEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRequest = value.request
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForRequest)
    }
    public static read(buffer: DeserializerBase): OnInterceptRequestEvent {
        let valueDeserializer: DeserializerBase = buffer
        const requestTmpResult: WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value: OnInterceptRequestEvent = ({request: requestTmpResult} as OnInterceptRequestEvent)
        return value
    }
}
export class OnLoadFinishedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnLoadFinishedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnLoadFinishedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnLoadFinishedEvent = ({url: urlTmpResult} as OnLoadFinishedEvent)
        return value
    }
}
export class OnLoadInterceptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnLoadInterceptEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForData = value.data
        WebResourceRequest_serializer.write(valueSerializer, valueHolderForData)
    }
    public static read(buffer: DeserializerBase): OnLoadInterceptEvent {
        let valueDeserializer: DeserializerBase = buffer
        const dataTmpResult: WebResourceRequest = (WebResourceRequest_serializer.read(valueDeserializer) as WebResourceRequest)
        let value: OnLoadInterceptEvent = ({data: dataTmpResult} as OnLoadInterceptEvent)
        return value
    }
}
export class OnLoadStartedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnLoadStartedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnLoadStartedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnLoadStartedEvent = ({url: urlTmpResult} as OnLoadStartedEvent)
        return value
    }
}
export class OnPageBeginEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageBeginEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageBeginEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnPageBeginEvent = ({url: urlTmpResult} as OnPageBeginEvent)
        return value
    }
}
export class OnPageEndEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageEndEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageEndEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnPageEndEvent = ({url: urlTmpResult} as OnPageEndEvent)
        return value
    }
}
export class OnPageVisibleEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPageVisibleEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPageVisibleEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnPageVisibleEvent = ({url: urlTmpResult} as OnPageVisibleEvent)
        return value
    }
}
export class OnPdfLoadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPdfLoadEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForResult = value.result
        valueSerializer.writeInt32(valueHolderForResult.valueOf())
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPdfLoadEvent {
        let valueDeserializer: DeserializerBase = buffer
        const resultTmpResult: PdfLoadResult = PdfLoadResult.fromValue(valueDeserializer.readInt32())
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnPdfLoadEvent = ({result: resultTmpResult, url: urlTmpResult} as OnPdfLoadEvent)
        return value
    }
}
export class OnPdfScrollEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPdfScrollEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnPdfScrollEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnPdfScrollEvent = ({url: urlTmpResult} as OnPdfScrollEvent)
        return value
    }
}
export class OnPermissionRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPermissionRequestEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRequest = value.request
        PermissionRequest_serializer.write(valueSerializer, valueHolderForRequest)
    }
    public static read(buffer: DeserializerBase): OnPermissionRequestEvent {
        let valueDeserializer: DeserializerBase = buffer
        const requestTmpResult: PermissionRequest = (PermissionRequest_serializer.read(valueDeserializer) as PermissionRequest)
        let value: OnPermissionRequestEvent = ({request: requestTmpResult} as OnPermissionRequestEvent)
        return value
    }
}
export class OnPromptEvent_serializer {
    public static write(buffer: SerializerBase, value: OnPromptEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForValue = value.value
        valueSerializer.writeString(valueHolderForValue)
        const valueHolderForResult = value.result
        JsResult_serializer.write(valueSerializer, valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): OnPromptEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const valueTmpResult: string = (valueDeserializer.readString() as string)
        const resultTmpResult: JsResult = (JsResult_serializer.read(valueDeserializer) as JsResult)
        let value: OnPromptEvent = ({url: urlTmpResult, message: messageTmpResult, value: valueTmpResult, result: resultTmpResult} as OnPromptEvent)
        return value
    }
}
export class OnRefreshAccessedHistoryEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRefreshAccessedHistoryEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForIsRefreshed = value.isRefreshed
        valueSerializer.writeBoolean(valueHolderForIsRefreshed)
        const valueHolderForIsMainFrame = value.isMainFrame
        if (valueHolderForIsMainFrame !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsMainFrameTmpValue = valueHolderForIsMainFrame!
            valueSerializer.writeBoolean(valueHolderForIsMainFrameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OnRefreshAccessedHistoryEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const isRefreshedTmpResult: boolean = valueDeserializer.readBoolean()
        const isMainFrameTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let isMainFrameTmpBuf: boolean | undefined = undefined
        if ((isMainFrameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isMainFrameTmpBuf = valueDeserializer.readBoolean()
        }
        const isMainFrameTmpResult: boolean | undefined = isMainFrameTmpBuf
        let value: OnRefreshAccessedHistoryEvent = ({url: urlTmpResult, isRefreshed: isRefreshedTmpResult, isMainFrame: isMainFrameTmpResult} as OnRefreshAccessedHistoryEvent)
        return value
    }
}
export class OnRenderExitedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnRenderExitedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRenderExitReason = value.renderExitReason
        valueSerializer.writeInt32(valueHolderForRenderExitReason.valueOf())
    }
    public static read(buffer: DeserializerBase): OnRenderExitedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const renderExitReasonTmpResult: RenderExitReason = RenderExitReason.fromValue(valueDeserializer.readInt32())
        let value: OnRenderExitedEvent = ({renderExitReason: renderExitReasonTmpResult} as OnRenderExitedEvent)
        return value
    }
}
export class OnResourceLoadEvent_serializer {
    public static write(buffer: SerializerBase, value: OnResourceLoadEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
    }
    public static read(buffer: DeserializerBase): OnResourceLoadEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        let value: OnResourceLoadEvent = ({url: urlTmpResult} as OnResourceLoadEvent)
        return value
    }
}
export class OnScreenCaptureRequestEvent_serializer {
    public static write(buffer: SerializerBase, value: OnScreenCaptureRequestEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        ScreenCaptureHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnScreenCaptureRequestEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: ScreenCaptureHandler = (ScreenCaptureHandler_serializer.read(valueDeserializer) as ScreenCaptureHandler)
        let value: OnScreenCaptureRequestEvent = ({handler: handlerTmpResult} as OnScreenCaptureRequestEvent)
        return value
    }
}
export class OnSslErrorEventReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnSslErrorEventReceiveEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        SslErrorHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForError = value.error
        valueSerializer.writeInt32(valueHolderForError.valueOf())
        const valueHolderForCertChainData = value.certChainData
        if (valueHolderForCertChainData !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCertChainDataTmpValue = valueHolderForCertChainData!
            valueSerializer.writeInt32((valueHolderForCertChainDataTmpValue.length).toInt())
            for (let valueHolderForCertChainDataTmpValueCounterI = 0; valueHolderForCertChainDataTmpValueCounterI < valueHolderForCertChainDataTmpValue.length; valueHolderForCertChainDataTmpValueCounterI++) {
                const valueHolderForCertChainDataTmpValueTmpElement: ArrayBuffer = valueHolderForCertChainDataTmpValue[valueHolderForCertChainDataTmpValueCounterI]
                valueSerializer.writeBuffer(valueHolderForCertChainDataTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OnSslErrorEventReceiveEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const errorTmpResult: SslError = SslError.fromValue(valueDeserializer.readInt32())
        const certChainDataTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let certChainDataTmpBuf: Array<ArrayBuffer> | undefined = undefined
        if ((certChainDataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const certChainDataTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const certChainDataTmpBufOpt: Array<ArrayBuffer> = new Array<ArrayBuffer>(certChainDataTmpBufOptLength, (arg0: int32):ArrayBuffer => {
            return (valueDeserializer.readBuffer() as ArrayBuffer);
        })
            certChainDataTmpBuf = certChainDataTmpBufOpt
        }
        const certChainDataTmpResult: Array<ArrayBuffer> | undefined = certChainDataTmpBuf
        let value: OnSslErrorEventReceiveEvent = ({handler: handlerTmpResult, error: errorTmpResult, certChainData: certChainDataTmpResult} as OnSslErrorEventReceiveEvent)
        return value
    }
}
export class OnTitleReceiveEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTitleReceiveEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTitle = value.title
        valueSerializer.writeString(valueHolderForTitle)
        const valueHolderForIsRealTitle = value.isRealTitle
        if (valueHolderForIsRealTitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsRealTitleTmpValue = valueHolderForIsRealTitle!
            valueSerializer.writeBoolean(valueHolderForIsRealTitleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OnTitleReceiveEvent {
        let valueDeserializer: DeserializerBase = buffer
        const titleTmpResult: string = (valueDeserializer.readString() as string)
        const isRealTitleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let isRealTitleTmpBuf: boolean | undefined = undefined
        if ((isRealTitleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isRealTitleTmpBuf = valueDeserializer.readBoolean()
        }
        const isRealTitleTmpResult: boolean | undefined = isRealTitleTmpBuf
        let value: OnTitleReceiveEvent = ({title: titleTmpResult, isRealTitle: isRealTitleTmpResult} as OnTitleReceiveEvent)
        return value
    }
}
export class OnTouchIconUrlReceivedEvent_serializer {
    public static write(buffer: SerializerBase, value: OnTouchIconUrlReceivedEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForPrecomposed = value.precomposed
        valueSerializer.writeBoolean(valueHolderForPrecomposed)
    }
    public static read(buffer: DeserializerBase): OnTouchIconUrlReceivedEvent {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const precomposedTmpResult: boolean = valueDeserializer.readBoolean()
        let value: OnTouchIconUrlReceivedEvent = ({url: urlTmpResult, precomposed: precomposedTmpResult} as OnTouchIconUrlReceivedEvent)
        return value
    }
}
export class OnWindowNewEvent_serializer {
    public static write(buffer: SerializerBase, value: OnWindowNewEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForIsAlert = value.isAlert
        valueSerializer.writeBoolean(valueHolderForIsAlert)
        const valueHolderForIsUserTrigger = value.isUserTrigger
        valueSerializer.writeBoolean(valueHolderForIsUserTrigger)
        const valueHolderForTargetUrl = value.targetUrl
        valueSerializer.writeString(valueHolderForTargetUrl)
        const valueHolderForHandler = value.handler
        ControllerHandler_serializer.write(valueSerializer, valueHolderForHandler)
    }
    public static read(buffer: DeserializerBase): OnWindowNewEvent {
        let valueDeserializer: DeserializerBase = buffer
        const isAlertTmpResult: boolean = valueDeserializer.readBoolean()
        const isUserTriggerTmpResult: boolean = valueDeserializer.readBoolean()
        const targetUrlTmpResult: string = (valueDeserializer.readString() as string)
        const handlerTmpResult: ControllerHandler = (ControllerHandler_serializer.read(valueDeserializer) as ControllerHandler)
        let value: OnWindowNewEvent = ({isAlert: isAlertTmpResult, isUserTrigger: isUserTriggerTmpResult, targetUrl: targetUrlTmpResult, handler: handlerTmpResult} as OnWindowNewEvent)
        return value
    }
}
export class OnWindowNewExtEvent_serializer {
    public static write(buffer: SerializerBase, value: OnWindowNewExtEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForIsAlert = value.isAlert
        valueSerializer.writeBoolean(valueHolderForIsAlert)
        const valueHolderForIsUserTrigger = value.isUserTrigger
        valueSerializer.writeBoolean(valueHolderForIsUserTrigger)
        const valueHolderForTargetUrl = value.targetUrl
        valueSerializer.writeString(valueHolderForTargetUrl)
        const valueHolderForHandler = value.handler
        ControllerHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForWindowFeatures = value.windowFeatures
        WindowFeatures_serializer.write(valueSerializer, valueHolderForWindowFeatures)
        const valueHolderForNavigationPolicy = value.navigationPolicy
        valueSerializer.writeInt32(valueHolderForNavigationPolicy.valueOf())
    }
    public static read(buffer: DeserializerBase): OnWindowNewExtEvent {
        let valueDeserializer: DeserializerBase = buffer
        const isAlertTmpResult: boolean = valueDeserializer.readBoolean()
        const isUserTriggerTmpResult: boolean = valueDeserializer.readBoolean()
        const targetUrlTmpResult: string = (valueDeserializer.readString() as string)
        const handlerTmpResult: ControllerHandler = (ControllerHandler_serializer.read(valueDeserializer) as ControllerHandler)
        const windowFeaturesTmpResult: WindowFeatures = WindowFeatures_serializer.read(valueDeserializer)
        const navigationPolicyTmpResult: NavigationPolicy = NavigationPolicy.fromValue(valueDeserializer.readInt32())
        let value: OnWindowNewExtEvent = ({isAlert: isAlertTmpResult, isUserTrigger: isUserTriggerTmpResult, targetUrl: targetUrlTmpResult, handler: handlerTmpResult, windowFeatures: windowFeaturesTmpResult, navigationPolicy: navigationPolicyTmpResult} as OnWindowNewExtEvent)
        return value
    }
}
export class RenderProcessNotRespondingData_serializer {
    public static write(buffer: SerializerBase, value: RenderProcessNotRespondingData): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForJsStack = value.jsStack
        valueSerializer.writeString(valueHolderForJsStack)
        const valueHolderForPid = value.pid
        valueSerializer.writeInt32(valueHolderForPid)
        const valueHolderForReason = value.reason
        valueSerializer.writeInt32(valueHolderForReason.valueOf())
    }
    public static read(buffer: DeserializerBase): RenderProcessNotRespondingData {
        let valueDeserializer: DeserializerBase = buffer
        const jsStackTmpResult: string = (valueDeserializer.readString() as string)
        const pidTmpResult: int32 = valueDeserializer.readInt32()
        const reasonTmpResult: RenderProcessNotRespondingReason = RenderProcessNotRespondingReason.fromValue(valueDeserializer.readInt32())
        let value: RenderProcessNotRespondingData = ({jsStack: jsStackTmpResult, pid: pidTmpResult, reason: reasonTmpResult} as RenderProcessNotRespondingData)
        return value
    }
}
export class ScreenCaptureConfig_serializer {
    public static write(buffer: SerializerBase, value: ScreenCaptureConfig): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForCaptureMode = value.captureMode
        valueSerializer.writeInt32(valueHolderForCaptureMode.valueOf())
    }
    public static read(buffer: DeserializerBase): ScreenCaptureConfig {
        let valueDeserializer: DeserializerBase = buffer
        const captureModeTmpResult: WebCaptureMode = WebCaptureMode.fromValue(valueDeserializer.readInt32())
        let value: ScreenCaptureConfig = ({captureMode: captureModeTmpResult} as ScreenCaptureConfig)
        return value
    }
}
export class ScriptItem_serializer {
    public static write(buffer: SerializerBase, value: ScriptItem): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForScript = value.script
        valueSerializer.writeString(valueHolderForScript)
        const valueHolderForScriptRules = value.scriptRules
        valueSerializer.writeInt32((valueHolderForScriptRules.length).toInt())
        for (let valueHolderForScriptRulesCounterI = 0; valueHolderForScriptRulesCounterI < valueHolderForScriptRules.length; valueHolderForScriptRulesCounterI++) {
            const valueHolderForScriptRulesTmpElement: string = valueHolderForScriptRules[valueHolderForScriptRulesCounterI]
            valueSerializer.writeString(valueHolderForScriptRulesTmpElement)
        }
        const valueHolderForUrlRegexRules = value.urlRegexRules
        if (valueHolderForUrlRegexRules !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlRegexRulesTmpValue = valueHolderForUrlRegexRules!
            valueSerializer.writeInt32((valueHolderForUrlRegexRulesTmpValue.length).toInt())
            for (let valueHolderForUrlRegexRulesTmpValueCounterI = 0; valueHolderForUrlRegexRulesTmpValueCounterI < valueHolderForUrlRegexRulesTmpValue.length; valueHolderForUrlRegexRulesTmpValueCounterI++) {
                const valueHolderForUrlRegexRulesTmpValueTmpElement: UrlRegexRule = valueHolderForUrlRegexRulesTmpValue[valueHolderForUrlRegexRulesTmpValueCounterI]
                UrlRegexRule_serializer.write(valueSerializer, valueHolderForUrlRegexRulesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScriptItem {
        let valueDeserializer: DeserializerBase = buffer
        const scriptTmpResult: string = (valueDeserializer.readString() as string)
        const scriptRulesTmpBufLength: int32 = valueDeserializer.readInt32()
        const scriptRulesTmpBuf: Array<string> = new Array<string>(scriptRulesTmpBufLength, (arg0: int32):string => {
            return (valueDeserializer.readString() as string);
        })
        const scriptRulesTmpResult: Array<string> = scriptRulesTmpBuf
        const urlRegexRulesTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let urlRegexRulesTmpBuf: Array<UrlRegexRule> | undefined = undefined
        if ((urlRegexRulesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const urlRegexRulesTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const urlRegexRulesTmpBufOpt: Array<UrlRegexRule> = new Array<UrlRegexRule>(urlRegexRulesTmpBufOptLength, (arg0: int32):UrlRegexRule => {
            return UrlRegexRule_serializer.read(valueDeserializer);
        })
            urlRegexRulesTmpBuf = urlRegexRulesTmpBufOpt
        }
        const urlRegexRulesTmpResult: Array<UrlRegexRule> | undefined = urlRegexRulesTmpBuf
        let value: ScriptItem = ({script: scriptTmpResult, scriptRules: scriptRulesTmpResult, urlRegexRules: urlRegexRulesTmpResult} as ScriptItem)
        return value
    }
}
export class SslErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: SslErrorEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        SslErrorHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForError = value.error
        valueSerializer.writeInt32(valueHolderForError.valueOf())
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForOriginalUrl = value.originalUrl
        valueSerializer.writeString(valueHolderForOriginalUrl)
        const valueHolderForReferrer = value.referrer
        valueSerializer.writeString(valueHolderForReferrer)
        const valueHolderForIsFatalError = value.isFatalError
        valueSerializer.writeBoolean(valueHolderForIsFatalError)
        const valueHolderForIsMainFrame = value.isMainFrame
        valueSerializer.writeBoolean(valueHolderForIsMainFrame)
        const valueHolderForCertChainData = value.certChainData
        if (valueHolderForCertChainData !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCertChainDataTmpValue = valueHolderForCertChainData!
            valueSerializer.writeInt32((valueHolderForCertChainDataTmpValue.length).toInt())
            for (let valueHolderForCertChainDataTmpValueCounterI = 0; valueHolderForCertChainDataTmpValueCounterI < valueHolderForCertChainDataTmpValue.length; valueHolderForCertChainDataTmpValueCounterI++) {
                const valueHolderForCertChainDataTmpValueTmpElement: ArrayBuffer = valueHolderForCertChainDataTmpValue[valueHolderForCertChainDataTmpValueCounterI]
                valueSerializer.writeBuffer(valueHolderForCertChainDataTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SslErrorEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: SslErrorHandler = (SslErrorHandler_serializer.read(valueDeserializer) as SslErrorHandler)
        const errorTmpResult: SslError = SslError.fromValue(valueDeserializer.readInt32())
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const originalUrlTmpResult: string = (valueDeserializer.readString() as string)
        const referrerTmpResult: string = (valueDeserializer.readString() as string)
        const isFatalErrorTmpResult: boolean = valueDeserializer.readBoolean()
        const isMainFrameTmpResult: boolean = valueDeserializer.readBoolean()
        const certChainDataTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let certChainDataTmpBuf: Array<ArrayBuffer> | undefined = undefined
        if ((certChainDataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const certChainDataTmpBufOptLength: int32 = valueDeserializer.readInt32()
            const certChainDataTmpBufOpt: Array<ArrayBuffer> = new Array<ArrayBuffer>(certChainDataTmpBufOptLength, (arg0: int32):ArrayBuffer => {
            return (valueDeserializer.readBuffer() as ArrayBuffer);
        })
            certChainDataTmpBuf = certChainDataTmpBufOpt
        }
        const certChainDataTmpResult: Array<ArrayBuffer> | undefined = certChainDataTmpBuf
        let value: SslErrorEvent = ({handler: handlerTmpResult, error: errorTmpResult, url: urlTmpResult, originalUrl: originalUrlTmpResult, referrer: referrerTmpResult, isFatalError: isFatalErrorTmpResult, isMainFrame: isMainFrameTmpResult, certChainData: certChainDataTmpResult} as SslErrorEvent)
        return value
    }
}
export class VerifyPinEvent_serializer {
    public static write(buffer: SerializerBase, value: VerifyPinEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForHandler = value.handler
        VerifyPinHandler_serializer.write(valueSerializer, valueHolderForHandler)
        const valueHolderForIdentity = value.identity
        valueSerializer.writeString(valueHolderForIdentity)
    }
    public static read(buffer: DeserializerBase): VerifyPinEvent {
        let valueDeserializer: DeserializerBase = buffer
        const handlerTmpResult: VerifyPinHandler = (VerifyPinHandler_serializer.read(valueDeserializer) as VerifyPinHandler)
        const identityTmpResult: string = (valueDeserializer.readString() as string)
        let value: VerifyPinEvent = ({handler: handlerTmpResult, identity: identityTmpResult} as VerifyPinEvent)
        return value
    }
}
export class WebKeyboardCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardCallbackInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForController = value.controller
        WebKeyboardController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForAttributes = value.attributes
        valueSerializer.writeInt32((valueHolderForAttributes.size).toInt())
        for (const pair of valueHolderForAttributes) {
            const valueHolderForAttributesKeyVar = pair[0]
            const valueHolderForAttributesValueVar = pair[1]
            valueSerializer.writeString(valueHolderForAttributesKeyVar)
            valueSerializer.writeString(valueHolderForAttributesValueVar)
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardCallbackInfo {
        let valueDeserializer: DeserializerBase = buffer
        const controllerTmpResult: WebKeyboardController = (WebKeyboardController_serializer.read(valueDeserializer) as WebKeyboardController)
        const attributesTmpBufSizeVar: int32 = valueDeserializer.readInt32()
        let attributesTmpBuf: Record<string, string> = new Record<string, string>()
        // TODO: TS map resize
        for (let attributesTmpBufIVar = 0; attributesTmpBufIVar < attributesTmpBufSizeVar; attributesTmpBufIVar++) {
            const attributesTmpBufKeyVar: string = (valueDeserializer.readString() as string)
            const attributesTmpBufValueVar: string = (valueDeserializer.readString() as string)
            attributesTmpBuf.set(attributesTmpBufKeyVar, attributesTmpBufValueVar)
        }
        const attributesTmpResult: Record<string, string> = attributesTmpBuf
        let value: WebKeyboardCallbackInfo = ({controller: controllerTmpResult, attributes: attributesTmpResult} as WebKeyboardCallbackInfo)
        return value
    }
}
export class WebKeyboardOptions_serializer {
    public static write(buffer: SerializerBase, value: WebKeyboardOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUseSystemKeyboard = value.useSystemKeyboard
        valueSerializer.writeBoolean(valueHolderForUseSystemKeyboard)
        const valueHolderForEnterKeyType = value.enterKeyType
        if (valueHolderForEnterKeyType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnterKeyTypeTmpValue = valueHolderForEnterKeyType!
            valueSerializer.writeInt32(valueHolderForEnterKeyTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCustomKeyboard = value.customKeyboard
        if (valueHolderForCustomKeyboard !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomKeyboardTmpValue = valueHolderForCustomKeyboard!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForCustomKeyboardTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebKeyboardOptions {
        let valueDeserializer: DeserializerBase = buffer
        const useSystemKeyboardTmpResult: boolean = valueDeserializer.readBoolean()
        const enterKeyTypeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enterKeyTypeTmpBuf: int32 | undefined = undefined
        if ((enterKeyTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enterKeyTypeTmpBuf = valueDeserializer.readInt32()
        }
        const enterKeyTypeTmpResult: int32 | undefined = enterKeyTypeTmpBuf
        const customKeyboardTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let customKeyboardTmpBuf: CustomBuilder | undefined = undefined
        if ((customKeyboardTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const customKeyboardTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const customKeyboardTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const customKeyboardTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const customKeyboardTmpBufOptClosure = ():void => {
                const customKeyboardTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                customKeyboardTmpBufOptBufArgsSerializer.writeInt32(customKeyboardTmpBufOptBufResource.resourceId);
                customKeyboardTmpBufOptBufArgsSerializer.writePointer(customKeyboardTmpBufOptBufCall);
                customKeyboardTmpBufOptBufArgsSerializer.writePointer(customKeyboardTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, customKeyboardTmpBufOptBufArgsSerializer.asBuffer(), customKeyboardTmpBufOptBufArgsSerializer.length());
                customKeyboardTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(customKeyboardTmpBufOptClosure, customKeyboardTmpBufOptBufResource)
            customKeyboardTmpBuf = customKeyboardTmpBufOptClosure
        }
        const customKeyboardTmpResult: CustomBuilder | undefined = customKeyboardTmpBuf
        let value: WebKeyboardOptions = ({useSystemKeyboard: useSystemKeyboardTmpResult, enterKeyType: enterKeyTypeTmpResult, customKeyboard: customKeyboardTmpResult} as WebKeyboardOptions)
        return value
    }
}
export class WebMediaOptions_serializer {
    public static write(buffer: SerializerBase, value: WebMediaOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForResumeInterval = value.resumeInterval
        if (valueHolderForResumeInterval !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForResumeIntervalTmpValue = valueHolderForResumeInterval!
            valueSerializer.writeInt32(valueHolderForResumeIntervalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAudioExclusive = value.audioExclusive
        if (valueHolderForAudioExclusive !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAudioExclusiveTmpValue = valueHolderForAudioExclusive!
            valueSerializer.writeBoolean(valueHolderForAudioExclusiveTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAudioSessionType = value.audioSessionType
        if (valueHolderForAudioSessionType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAudioSessionTypeTmpValue = (valueHolderForAudioSessionType as AudioSessionType)
            valueSerializer.writeInt32(valueHolderForAudioSessionTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebMediaOptions {
        let valueDeserializer: DeserializerBase = buffer
        const resumeIntervalTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let resumeIntervalTmpBuf: int32 | undefined = undefined
        if ((resumeIntervalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            resumeIntervalTmpBuf = valueDeserializer.readInt32()
        }
        const resumeIntervalTmpResult: int32 | undefined = resumeIntervalTmpBuf
        const audioExclusiveTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let audioExclusiveTmpBuf: boolean | undefined = undefined
        if ((audioExclusiveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            audioExclusiveTmpBuf = valueDeserializer.readBoolean()
        }
        const audioExclusiveTmpResult: boolean | undefined = audioExclusiveTmpBuf
        const audioSessionTypeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let audioSessionTypeTmpBuf: AudioSessionType | undefined = undefined
        if ((audioSessionTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            audioSessionTypeTmpBuf = AudioSessionType.fromValue(valueDeserializer.readInt32())
        }
        const audioSessionTypeTmpResult: AudioSessionType | undefined = audioSessionTypeTmpBuf
        let value: WebMediaOptions = ({resumeInterval: resumeIntervalTmpResult, audioExclusive: audioExclusiveTmpResult, audioSessionType: audioSessionTypeTmpResult} as WebMediaOptions)
        return value
    }
}
export class WebOptions_serializer {
    public static write(buffer: SerializerBase, value: WebOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSrc = value.src
        if (valueHolderForSrc instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSrcForIdx0 = valueHolderForSrc as string
            valueSerializer.writeString(valueHolderForSrcForIdx0)
        } else if (valueHolderForSrc instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSrcForIdx1 = valueHolderForSrc as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForSrcForIdx1)
        }
        const valueHolderForController = value.controller
        webview_WebviewController_serializer.write(valueSerializer, valueHolderForController)
        const valueHolderForRenderMode = value.renderMode
        if (valueHolderForRenderMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRenderModeTmpValue = (valueHolderForRenderMode as RenderMode)
            valueSerializer.writeInt32(valueHolderForRenderModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIncognitoMode = value.incognitoMode
        if (valueHolderForIncognitoMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIncognitoModeTmpValue = valueHolderForIncognitoMode!
            valueSerializer.writeBoolean(valueHolderForIncognitoModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSharedRenderProcessToken = value.sharedRenderProcessToken
        if (valueHolderForSharedRenderProcessToken !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSharedRenderProcessTokenTmpValue = valueHolderForSharedRenderProcessToken!
            valueSerializer.writeString(valueHolderForSharedRenderProcessTokenTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEmulateTouchFromMouseEvent = value.emulateTouchFromMouseEvent
        if (valueHolderForEmulateTouchFromMouseEvent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmulateTouchFromMouseEventTmpValue = valueHolderForEmulateTouchFromMouseEvent!
            valueSerializer.writeBoolean(valueHolderForEmulateTouchFromMouseEventTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WebOptions {
        let valueDeserializer: DeserializerBase = buffer
        const srcTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let srcTmpBuf: string | global_resource_Resource | undefined
        if (srcTmpBufUnionSelector == (0).toByte()) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        } else if (srcTmpBufUnionSelector == (1).toByte()) {
            srcTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for srcTmpBuf has to be chosen through deserialisation.')
        }
        const srcTmpResult: string | global_resource_Resource = (srcTmpBuf as string | global_resource_Resource)
        const controllerTmpResult: WebviewController = (webview_WebviewController_serializer.read(valueDeserializer) as webview.WebviewController)
        const renderModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let renderModeTmpBuf: RenderMode | undefined = undefined
        if ((renderModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            renderModeTmpBuf = RenderMode.fromValue(valueDeserializer.readInt32())
        }
        const renderModeTmpResult: RenderMode | undefined = renderModeTmpBuf
        const incognitoModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let incognitoModeTmpBuf: boolean | undefined = undefined
        if ((incognitoModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            incognitoModeTmpBuf = valueDeserializer.readBoolean()
        }
        const incognitoModeTmpResult: boolean | undefined = incognitoModeTmpBuf
        const sharedRenderProcessTokenTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sharedRenderProcessTokenTmpBuf: string | undefined = undefined
        if ((sharedRenderProcessTokenTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sharedRenderProcessTokenTmpBuf = (valueDeserializer.readString() as string)
        }
        const sharedRenderProcessTokenTmpResult: string | undefined = sharedRenderProcessTokenTmpBuf
        const emulateTouchFromMouseEventTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let emulateTouchFromMouseEventTmpBuf: boolean | undefined = undefined
        if ((emulateTouchFromMouseEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            emulateTouchFromMouseEventTmpBuf = valueDeserializer.readBoolean()
        }
        const emulateTouchFromMouseEventTmpResult: boolean | undefined = emulateTouchFromMouseEventTmpBuf
        let value: WebOptions = ({src: srcTmpResult, controller: controllerTmpResult, renderMode: renderModeTmpResult, incognitoMode: incognitoModeTmpResult, sharedRenderProcessToken: sharedRenderProcessTokenTmpResult, emulateTouchFromMouseEvent: emulateTouchFromMouseEventTmpResult} as WebOptions)
        return value
    }
}
export class BlankScreenDetectionEventInfo_serializer {
    public static write(buffer: SerializerBase, value: BlankScreenDetectionEventInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForBlankScreenReason = value.blankScreenReason
        valueSerializer.writeInt32(valueHolderForBlankScreenReason.valueOf())
        const valueHolderForBlankScreenDetails = value.blankScreenDetails
        if (valueHolderForBlankScreenDetails !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBlankScreenDetailsTmpValue = valueHolderForBlankScreenDetails!
            BlankScreenDetails_serializer.write(valueSerializer, valueHolderForBlankScreenDetailsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BlankScreenDetectionEventInfo {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const blankScreenReasonTmpResult: DetectedBlankScreenReason = DetectedBlankScreenReason.fromValue(valueDeserializer.readInt32())
        const blankScreenDetailsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let blankScreenDetailsTmpBuf: BlankScreenDetails | undefined = undefined
        if ((blankScreenDetailsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            blankScreenDetailsTmpBuf = BlankScreenDetails_serializer.read(valueDeserializer)
        }
        const blankScreenDetailsTmpResult: BlankScreenDetails | undefined = blankScreenDetailsTmpBuf
        let value: BlankScreenDetectionEventInfo = ({url: urlTmpResult, blankScreenReason: blankScreenReasonTmpResult, blankScreenDetails: blankScreenDetailsTmpResult} as BlankScreenDetectionEventInfo)
        return value
    }
}
export class SelectionMenuOptionsExt_serializer {
    public static write(buffer: SerializerBase, value: SelectionMenuOptionsExt): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOnAppear = value.onAppear
        if (valueHolderForOnAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAppearTmpValue = valueHolderForOnAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDisappear = value.onDisappear
        if (valueHolderForOnDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDisappearTmpValue = valueHolderForOnDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreview = value.preview
        if (valueHolderForPreview !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTmpValue = valueHolderForPreview!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForPreviewTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMenuType = value.menuType
        if (valueHolderForMenuType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMenuTypeTmpValue = (valueHolderForMenuType as MenuType)
            valueSerializer.writeInt32(valueHolderForMenuTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreviewMenuOptions = value.previewMenuOptions
        if (valueHolderForPreviewMenuOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewMenuOptionsTmpValue = valueHolderForPreviewMenuOptions!
            PreviewMenuOptions_serializer.write(valueSerializer, valueHolderForPreviewMenuOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnMenuShow = value.onMenuShow
        if (valueHolderForOnMenuShow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnMenuShowTmpValue = valueHolderForOnMenuShow!
            valueSerializer.holdAndWriteCallback(valueHolderForOnMenuShowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnMenuHide = value.onMenuHide
        if (valueHolderForOnMenuHide !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnMenuHideTmpValue = valueHolderForOnMenuHide!
            valueSerializer.holdAndWriteCallback(valueHolderForOnMenuHideTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectionMenuOptionsExt {
        let valueDeserializer: DeserializerBase = buffer
        const onAppearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onAppearTmpBuf: VoidCallback | undefined = undefined
        if ((onAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAppearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onAppearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onAppearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onAppearTmpBufOptClosure = ():void => {
                const onAppearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onAppearTmpBufOptBufArgsSerializer.writeInt32(onAppearTmpBufOptBufResource.resourceId);
                onAppearTmpBufOptBufArgsSerializer.writePointer(onAppearTmpBufOptBufCall);
                onAppearTmpBufOptBufArgsSerializer.writePointer(onAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onAppearTmpBufOptBufArgsSerializer.asBuffer(), onAppearTmpBufOptBufArgsSerializer.length());
                onAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onAppearTmpBufOptClosure, onAppearTmpBufOptBufResource)
            onAppearTmpBuf = onAppearTmpBufOptClosure
        }
        const onAppearTmpResult: VoidCallback | undefined = onAppearTmpBuf
        const onDisappearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onDisappearTmpBuf: VoidCallback | undefined = undefined
        if ((onDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDisappearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onDisappearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onDisappearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onDisappearTmpBufOptClosure = ():void => {
                const onDisappearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onDisappearTmpBufOptBufArgsSerializer.writeInt32(onDisappearTmpBufOptBufResource.resourceId);
                onDisappearTmpBufOptBufArgsSerializer.writePointer(onDisappearTmpBufOptBufCall);
                onDisappearTmpBufOptBufArgsSerializer.writePointer(onDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDisappearTmpBufOptBufArgsSerializer.length());
                onDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDisappearTmpBufOptClosure, onDisappearTmpBufOptBufResource)
            onDisappearTmpBuf = onDisappearTmpBufOptClosure
        }
        const onDisappearTmpResult: VoidCallback | undefined = onDisappearTmpBuf
        const previewTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let previewTmpBuf: CustomBuilder | undefined = undefined
        if ((previewTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const previewTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const previewTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const previewTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const previewTmpBufOptClosure = ():void => {
                const previewTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                previewTmpBufOptBufArgsSerializer.writeInt32(previewTmpBufOptBufResource.resourceId);
                previewTmpBufOptBufArgsSerializer.writePointer(previewTmpBufOptBufCall);
                previewTmpBufOptBufArgsSerializer.writePointer(previewTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, previewTmpBufOptBufArgsSerializer.asBuffer(), previewTmpBufOptBufArgsSerializer.length());
                previewTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(previewTmpBufOptClosure, previewTmpBufOptBufResource)
            previewTmpBuf = previewTmpBufOptClosure
        }
        const previewTmpResult: CustomBuilder | undefined = previewTmpBuf
        const menuTypeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let menuTypeTmpBuf: MenuType | undefined = undefined
        if ((menuTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            menuTypeTmpBuf = MenuType.fromValue(valueDeserializer.readInt32())
        }
        const menuTypeTmpResult: MenuType | undefined = menuTypeTmpBuf
        const previewMenuOptionsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let previewMenuOptionsTmpBuf: PreviewMenuOptions | undefined = undefined
        if ((previewMenuOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewMenuOptionsTmpBuf = PreviewMenuOptions_serializer.read(valueDeserializer)
        }
        const previewMenuOptionsTmpResult: PreviewMenuOptions | undefined = previewMenuOptionsTmpBuf
        const onMenuShowTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onMenuShowTmpBuf: VoidCallback | undefined = undefined
        if ((onMenuShowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onMenuShowTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuShowTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onMenuShowTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onMenuShowTmpBufOptClosure = ():void => {
                const onMenuShowTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onMenuShowTmpBufOptBufArgsSerializer.writeInt32(onMenuShowTmpBufOptBufResource.resourceId);
                onMenuShowTmpBufOptBufArgsSerializer.writePointer(onMenuShowTmpBufOptBufCall);
                onMenuShowTmpBufOptBufArgsSerializer.writePointer(onMenuShowTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onMenuShowTmpBufOptBufArgsSerializer.asBuffer(), onMenuShowTmpBufOptBufArgsSerializer.length());
                onMenuShowTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onMenuShowTmpBufOptClosure, onMenuShowTmpBufOptBufResource)
            onMenuShowTmpBuf = onMenuShowTmpBufOptClosure
        }
        const onMenuShowTmpResult: VoidCallback | undefined = onMenuShowTmpBuf
        const onMenuHideTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onMenuHideTmpBuf: VoidCallback | undefined = undefined
        if ((onMenuHideTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onMenuHideTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuHideTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onMenuHideTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onMenuHideTmpBufOptClosure = ():void => {
                const onMenuHideTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onMenuHideTmpBufOptBufArgsSerializer.writeInt32(onMenuHideTmpBufOptBufResource.resourceId);
                onMenuHideTmpBufOptBufArgsSerializer.writePointer(onMenuHideTmpBufOptBufCall);
                onMenuHideTmpBufOptBufArgsSerializer.writePointer(onMenuHideTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onMenuHideTmpBufOptBufArgsSerializer.asBuffer(), onMenuHideTmpBufOptBufArgsSerializer.length());
                onMenuHideTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onMenuHideTmpBufOptClosure, onMenuHideTmpBufOptBufResource)
            onMenuHideTmpBuf = onMenuHideTmpBufOptClosure
        }
        const onMenuHideTmpResult: VoidCallback | undefined = onMenuHideTmpBuf
        let value: SelectionMenuOptionsExt = ({onAppear: onAppearTmpResult, onDisappear: onDisappearTmpResult, preview: previewTmpResult, menuType: menuTypeTmpResult, previewMenuOptions: previewMenuOptionsTmpResult, onMenuShow: onMenuShowTmpResult, onMenuHide: onMenuHideTmpResult} as SelectionMenuOptionsExt)
        return value
    }
}
export class NativeEmbedInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForId = value.id
        if (valueHolderForId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIdTmpValue = valueHolderForId!
            valueSerializer.writeString(valueHolderForIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue = valueHolderForType!
            valueSerializer.writeString(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSrc = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue = valueHolderForSrc!
            valueSerializer.writeString(valueHolderForSrcTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue = valueHolderForPosition!
            Position_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue = valueHolderForWidth!
            valueSerializer.writeInt32(valueHolderForWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue = valueHolderForHeight!
            valueSerializer.writeInt32(valueHolderForHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUrl = value.url
        if (valueHolderForUrl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlTmpValue = valueHolderForUrl!
            valueSerializer.writeString(valueHolderForUrlTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTag = value.tag
        if (valueHolderForTag !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTagTmpValue = valueHolderForTag!
            valueSerializer.writeString(valueHolderForTagTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParams = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue = valueHolderForParams!
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
        let valueDeserializer: DeserializerBase = buffer
        const idTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let idTmpBuf: string | undefined = undefined
        if ((idTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            idTmpBuf = (valueDeserializer.readString() as string)
        }
        const idTmpResult: string | undefined = idTmpBuf
        const typeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf: string | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult: string | undefined = typeTmpBuf
        const srcTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let srcTmpBuf: string | undefined = undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        }
        const srcTmpResult: string | undefined = srcTmpBuf
        const positionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf: Position | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = Position_serializer.read(valueDeserializer)
        }
        const positionTmpResult: Position | undefined = positionTmpBuf
        const widthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf: int32 | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            widthTmpBuf = valueDeserializer.readInt32()
        }
        const widthTmpResult: int32 | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf: int32 | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = valueDeserializer.readInt32()
        }
        const heightTmpResult: int32 | undefined = heightTmpBuf
        const urlTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let urlTmpBuf: string | undefined = undefined
        if ((urlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            urlTmpBuf = (valueDeserializer.readString() as string)
        }
        const urlTmpResult: string | undefined = urlTmpBuf
        const tagTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let tagTmpBuf: string | undefined = undefined
        if ((tagTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            tagTmpBuf = (valueDeserializer.readString() as string)
        }
        const tagTmpResult: string | undefined = tagTmpBuf
        const paramsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let paramsTmpBuf: Map<string, string> | undefined = undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const paramsTmpBufOptSizeVar: int32 = valueDeserializer.readInt32()
            let paramsTmpBufOpt: Map<string, string> = new Map<string, string>()
            // TODO: TS map resize
            for (let paramsTmpBufOptIVar = 0; paramsTmpBufOptIVar < paramsTmpBufOptSizeVar; paramsTmpBufOptIVar++) {
                const paramsTmpBufOptKeyVar: string = (valueDeserializer.readString() as string)
                const paramsTmpBufOptValueVar: string = (valueDeserializer.readString() as string)
                paramsTmpBufOpt.set(paramsTmpBufOptKeyVar, paramsTmpBufOptValueVar)
            }
            paramsTmpBuf = paramsTmpBufOpt
        }
        const paramsTmpResult: Map<string, string> | undefined = paramsTmpBuf
        let value: NativeEmbedInfo = ({id: idTmpResult, type: typeTmpResult, src: srcTmpResult, position: positionTmpResult, width: widthTmpResult, height: heightTmpResult, url: urlTmpResult, tag: tagTmpResult, params: paramsTmpResult} as NativeEmbedInfo)
        return value
    }
}
export class NativeEmbedDataInfo_serializer {
    public static write(buffer: SerializerBase, value: NativeEmbedDataInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStatus = value.status
        if (valueHolderForStatus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStatusTmpValue = (valueHolderForStatus as NativeEmbedStatus)
            valueSerializer.writeInt32(valueHolderForStatusTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceId = value.surfaceId
        if (valueHolderForSurfaceId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSurfaceIdTmpValue = valueHolderForSurfaceId!
            valueSerializer.writeString(valueHolderForSurfaceIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEmbedId = value.embedId
        if (valueHolderForEmbedId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmbedIdTmpValue = valueHolderForEmbedId!
            valueSerializer.writeString(valueHolderForEmbedIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForInfo = value.info
        if (valueHolderForInfo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForInfoTmpValue = valueHolderForInfo!
            NativeEmbedInfo_serializer.write(valueSerializer, valueHolderForInfoTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NativeEmbedDataInfo {
        let valueDeserializer: DeserializerBase = buffer
        const statusTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let statusTmpBuf: NativeEmbedStatus | undefined = undefined
        if ((statusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            statusTmpBuf = NativeEmbedStatus.fromValue(valueDeserializer.readInt32())
        }
        const statusTmpResult: NativeEmbedStatus | undefined = statusTmpBuf
        const surfaceIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let surfaceIdTmpBuf: string | undefined = undefined
        if ((surfaceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            surfaceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const surfaceIdTmpResult: string | undefined = surfaceIdTmpBuf
        const embedIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let embedIdTmpBuf: string | undefined = undefined
        if ((embedIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            embedIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const embedIdTmpResult: string | undefined = embedIdTmpBuf
        const infoTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let infoTmpBuf: NativeEmbedInfo | undefined = undefined
        if ((infoTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            infoTmpBuf = NativeEmbedInfo_serializer.read(valueDeserializer)
        }
        const infoTmpResult: NativeEmbedInfo | undefined = infoTmpBuf
        let value: NativeEmbedDataInfo = ({status: statusTmpResult, surfaceId: surfaceIdTmpResult, embedId: embedIdTmpResult, info: infoTmpResult} as NativeEmbedDataInfo)
        return value
    }
}

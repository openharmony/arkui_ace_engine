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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { WebviewController, WebviewControllerInternal } from "./../generated/ArkWebviewControllerMaterialized"
import { Resource } from "global/resource";
import { Callback_String_Void } from "./gridRow"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CustomBuilder, TouchEvent, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions } from "./common"
import { Position, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { Callback_Void } from "./abilityComponent"
import { MenuType, EditMenuOptions } from "./textCommon"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, CopyOptions, NestedScrollMode } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { ArkWebComponent } from "./../generated/ArkWeb"
import { ArkWebPeer } from "./../generated/peers/ArkWebPeer"
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
        throw new Error("Object deserialization is not implemented.")
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
        if (RuntimeType.UNDEFINED == certChainFile_type) {
            const authUri_casted = priKeyFile as (string)
            this.confirm1_serialize(authUri_casted)
            return
        }
        if (RuntimeType.STRING == certChainFile_type) {
            const priKeyFile_casted = priKeyFile as (string)
            const certChainFile_casted = certChainFile as (string)
            this.confirm0_serialize(priKeyFile_casted, certChainFile_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
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
        throw new Error("Object deserialization is not implemented.")
    }
    private getSelectionText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getSelectionText(this.peer!.ptr)
        return retval
    }
    private getSourceType_serialize(): ContextMenuSourceType {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getSourceType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getInputFieldType_serialize(): ContextMenuInputFieldType {
        const retval  = ArkUIGeneratedNativeModule._WebContextMenuParam_getInputFieldType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
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
        const retval  = ArkUIGeneratedNativeModule._ConsoleMessage_ctor(message, sourceId, lineNumber, messageLevel.valueOf())
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
        throw new Error("Object deserialization is not implemented.")
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
        thisSerializer.writeCustomObject("Object", options_object_)
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
        throw new Error("Object deserialization is not implemented.")
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
    handler: Function0<void>;
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
    callback_: Function0<void>;
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
/** @memo:stable */
export interface WebAttribute extends CommonMethod {
    /** @memo */
    setWebOptions(value: WebOptions): this
    /** @memo */
    javaScriptAccess(value: boolean): this
    /** @memo */
    fileAccess(value: boolean): this
    /** @memo */
    onlineImageAccess(value: boolean): this
    /** @memo */
    domStorageAccess(value: boolean): this
    /** @memo */
    imageAccess(value: boolean): this
    /** @memo */
    mixedMode(value: MixedMode): this
    /** @memo */
    zoomAccess(value: boolean): this
    /** @memo */
    geolocationAccess(value: boolean): this
    /** @memo */
    javaScriptProxy(value: JavaScriptProxy): this
    /** @memo */
    password(value: boolean): this
    /** @memo */
    cacheMode(value: CacheMode): this
    /** @memo */
    darkMode(value: WebDarkMode): this
    /** @memo */
    forceDarkAccess(value: boolean): this
    /** @memo */
    mediaOptions(value: WebMediaOptions): this
    /** @memo */
    tableData(value: boolean): this
    /** @memo */
    wideViewModeAccess(value: boolean): this
    /** @memo */
    overviewModeAccess(value: boolean): this
    /** @memo */
    overScrollMode(value: OverScrollMode): this
    /** @memo */
    textZoomAtio(value: number): this
    /** @memo */
    textZoomRatio(value: number): this
    /** @memo */
    databaseAccess(value: boolean): this
    /** @memo */
    initialScale(value: number): this
    /** @memo */
    userAgent(value: string): this
    /** @memo */
    metaViewport(value: boolean): this
    /** @memo */
    onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this
    /** @memo */
    onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this
    /** @memo */
    onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this
    /** @memo */
    onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this
    /** @memo */
    onGeolocationHide(value: (() => void)): this
    /** @memo */
    onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this
    /** @memo */
    onRequestSelected(value: (() => void)): this
    /** @memo */
    onAlert(value: ((parameter: OnAlertEvent) => boolean)): this
    /** @memo */
    onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this
    /** @memo */
    onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this
    /** @memo */
    onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this
    /** @memo */
    onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this
    /** @memo */
    onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this
    /** @memo */
    onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this
    /** @memo */
    onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this
    /** @memo */
    onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this
    /** @memo */
    onUrlLoadIntercept(value: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)): this
    /** @memo */
    onSslErrorReceive(value: ((event?: Literal_Function_handler_Object_error) => void)): this
    /** @memo */
    onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: Literal_Object_detail) => boolean)): this
    /** @memo */
    onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this
    /** @memo */
    onFileSelectorShow(value: ((event?: Literal_Function_callback__Object_fileSelector) => void)): this
    /** @memo */
    onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this
    /** @memo */
    onFullScreenExit(value: (() => void)): this
    /** @memo */
    onFullScreenEnter(value: OnFullScreenEnterCallback): this
    /** @memo */
    onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this
    /** @memo */
    onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this
    /** @memo */
    onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this
    /** @memo */
    onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this
    /** @memo */
    onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this
    /** @memo */
    onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this
    /** @memo */
    onContextMenuHide(value: OnContextMenuHideCallback): this
    /** @memo */
    mediaPlayGestureAccess(value: boolean): this
    /** @memo */
    onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this
    /** @memo */
    onScroll(value: ((parameter: OnScrollEvent) => void)): this
    /** @memo */
    onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this
    /** @memo */
    onSslErrorEvent(value: OnSslErrorEventCallback): this
    /** @memo */
    onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this
    /** @memo */
    onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this
    /** @memo */
    onWindowExit(value: (() => void)): this
    /** @memo */
    multiWindowAccess(value: boolean): this
    /** @memo */
    onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this
    /** @memo */
    webStandardFont(value: string): this
    /** @memo */
    webSerifFont(value: string): this
    /** @memo */
    webSansSerifFont(value: string): this
    /** @memo */
    webFixedFont(value: string): this
    /** @memo */
    webFantasyFont(value: string): this
    /** @memo */
    webCursiveFont(value: string): this
    /** @memo */
    defaultFixedFontSize(value: number): this
    /** @memo */
    defaultFontSize(value: number): this
    /** @memo */
    minFontSize(value: number): this
    /** @memo */
    minLogicalFontSize(value: number): this
    /** @memo */
    defaultTextEncodingFormat(value: string): this
    /** @memo */
    forceDisplayScrollBar(value: boolean): this
    /** @memo */
    blockNetwork(value: boolean): this
    /** @memo */
    horizontalScrollBarAccess(value: boolean): this
    /** @memo */
    verticalScrollBarAccess(value: boolean): this
    /** @memo */
    onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this
    /** @memo */
    onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this
    /** @memo */
    onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this
    /** @memo */
    onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this
    /** @memo */
    pinchSmooth(value: boolean): this
    /** @memo */
    allowWindowOpenMethod(value: boolean): this
    /** @memo */
    onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this
    /** @memo */
    onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this
    /** @memo */
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this
    /** @memo */
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this
    /** @memo */
    onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this
    /** @memo */
    onControllerAttached(value: (() => void)): this
    /** @memo */
    onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this
    /** @memo */
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this
    /** @memo */
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this
    /** @memo */
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this
    /** @memo */
    javaScriptOnDocumentStart(value: Array<ScriptItem>): this
    /** @memo */
    javaScriptOnDocumentEnd(value: Array<ScriptItem>): this
    /** @memo */
    layoutMode(value: WebLayoutMode): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this
    /** @memo */
    enableNativeEmbedMode(value: boolean): this
    /** @memo */
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this
    /** @memo */
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this
    /** @memo */
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this
    /** @memo */
    copyOptions(value: CopyOptions): this
    /** @memo */
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this
    /** @memo */
    textAutosizing(value: boolean): this
    /** @memo */
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this
    /** @memo */
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this
    /** @memo */
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this
    /** @memo */
    selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this
    /** @memo */
    onViewportFitChanged(value: OnViewportFitChangedCallback): this
    /** @memo */
    onInterceptKeyboardAttach(value: WebKeyboardCallback): this
    /** @memo */
    onAdsBlocked(value: OnAdsBlockedCallback): this
    /** @memo */
    keyboardAvoidMode(value: WebKeyboardAvoidMode): this
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    registerNativeEmbedRule(tag: string, type: string): this
    /** @memo */
    bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this
}
/** @memo */
export function Web(
  /** @memo */
  style: ((attributes: WebAttribute) => void) | undefined,
  value: WebOptions, 
  /** @memo */
  content_?: () => void,
) {
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

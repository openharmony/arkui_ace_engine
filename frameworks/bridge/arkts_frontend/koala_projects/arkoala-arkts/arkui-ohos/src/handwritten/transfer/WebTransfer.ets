/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { TypeChecker } from "#components"
import { ArkUIAniModule } from "arkui.ani"
import { registerNativeModuleLibraryName } from '@koalaui/interop'
import { ScreenCaptureHandler, FileSelectorParam, JsGeolocation, JsResult, EventResult, FileSelectorResult, WebContextMenuParam, WebContextMenuResult, HttpAuthHandler, WebResourceResponse, WebResourceRequest, ConsoleMessage, DataResubmissionHandler, ClientAuthenticationHandler, SslErrorHandler, PermissionRequest, WebKeyboardController, ControllerHandler, MessageLevel } from '../../component/web'

function registerAllNativeModuleLibraryName() {
    registerNativeModuleLibraryName('InteropNativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('ArkUINativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('ArkUIGeneratedNativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('TestNativeModule', 'ArkoalaNative_ark.z')
}

export class ArkWebTransfer {
    public static transferScreenCaptureHandlerStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: ScreenCaptureHandler = new ScreenCaptureHandler()
        if (!ArkUIAniModule._TransferScreenCaptureHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferScreenCaptureHandlerDynamic(value: Object): Any {
        if (!TypeChecker.isScreenCaptureHandler(value)) {
            throw new Error('staticObject type mismatch')
        }
        const value_casted = value as ScreenCaptureHandler
        return ArkUIAniModule._TransferScreenCaptureHandlerToDynamic(value_casted.peer!.ptr)
    }

    public static transferFileSelectorParamStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: FileSelectorParam = new FileSelectorParam()
        if (!ArkUIAniModule._TransferFileSelectorParamToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferFileSelectorParamDynamic(value: Object): Any {
        if (!TypeChecker.isFileSelectorParam(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as FileSelectorParam
        return ArkUIAniModule._TransferFileSelectorParamToDynamic(value_casted.peer!.ptr)
    }

    public static transferJsGeolocationStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: JsGeolocation = new JsGeolocation()
        if (!ArkUIAniModule._TransferJsGeolocationToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferJsGeolocationDynamic(value: Object): Any {
        if (!TypeChecker.isJsGeolocation(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as JsGeolocation
        return ArkUIAniModule._TransferJsGeolocationToDynamic(value_casted.peer!.ptr)
    }

    public static transferJsResultStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: JsResult = new JsResult()
        if (!ArkUIAniModule._TransferJsResultToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferJsResultDynamic(value: Object): Any {
        if (!TypeChecker.isJsResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as JsResult
        return ArkUIAniModule._TransferJsResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferEventResultStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: EventResult = new EventResult()
        if (!ArkUIAniModule._TransferEventResultToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferEventResultDynamic(value: Object): Any {
        if (!TypeChecker.isEventResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as EventResult
        return ArkUIAniModule._TransferEventResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferFileSelectorResultStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: FileSelectorResult = new FileSelectorResult()
        if (!ArkUIAniModule._TransferFileSelectorResultToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferFileSelectorResultDynamic(value: Object): Any {
        if (!TypeChecker.isFileSelectorResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as FileSelectorResult
        return ArkUIAniModule._TransferFileSelectorResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebContextMenuParamStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: WebContextMenuParam = new WebContextMenuParam()
        if (!ArkUIAniModule._TransferWebContextMenuParamToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebContextMenuParamDynamic(value: Object): Any {
        if (!TypeChecker.isWebContextMenuParam(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebContextMenuParam
        return ArkUIAniModule._TransferWebContextMenuParamToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebContextMenuResultStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: WebContextMenuResult = new WebContextMenuResult()
        if (!ArkUIAniModule._TransferWebContextMenuResultToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebContextMenuResultDynamic(value: Object): Any {
        if (!TypeChecker.isWebContextMenuResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebContextMenuResult
        return ArkUIAniModule._TransferWebContextMenuResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferHttpAuthHandlerToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: HttpAuthHandler = new HttpAuthHandler()
        if (!ArkUIAniModule._TransferHttpAuthHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferHttpAuthHandlerToDynamic(value: Object): Any {
        if (!TypeChecker.isHttpAuthHandler(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as HttpAuthHandler
        return ArkUIAniModule._TransferHttpAuthHandlerToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebResourceReponseToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: WebResourceResponse = new WebResourceResponse()
        if (!ArkUIAniModule._TransferWebResourceReponseToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebResourceReponseToDynamic(value: Object): Any {
        if (!TypeChecker.isWebResourceResponse(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebResourceResponse
        return ArkUIAniModule._TransferWebResourceReponseToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebResourceRequestToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: WebResourceRequest = new WebResourceRequest()
        if (!ArkUIAniModule._TransferWebResourceRequestToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebResourceRequestToDynamic(value: Object): Any {
        if (!TypeChecker.isWebResourceRequest(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebResourceRequest
        return ArkUIAniModule._TransferWebResourceRequestToDynamic(value_casted.peer!.ptr)
    }

    public static transferConsoleMessageToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: ConsoleMessage = new ConsoleMessage()
        if (!ArkUIAniModule._TransferConsoleMessageToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferConsoleMessageToDynamic(value: Object): Any {
        if (!TypeChecker.isConsoleMessage(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as ConsoleMessage
        return ArkUIAniModule._TransferConsoleMessageToDynamic(value_casted.peer!.ptr)
    }

    public static transferDataResubmissionHandlerToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: DataResubmissionHandler = new DataResubmissionHandler()
        if (!ArkUIAniModule._TransferDataResubmissionHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferDataResubmissionHandlerToDynamic(value: Object): Any {
        if (!TypeChecker.isDataResubmissionHandler(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as DataResubmissionHandler
        return ArkUIAniModule._TransferDataResubmissionHandlerToDynamic(value_casted.peer!.ptr)
    }

    public static transferClientAuthenticationHandlerToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: ClientAuthenticationHandler = new ClientAuthenticationHandler()
        if (!ArkUIAniModule._TransferClientAuthenticationHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferClientAuthenticationHandlerToDynamic(value: Object): Any {
        if (!TypeChecker.isClientAuthenticationHandler(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as ClientAuthenticationHandler
        return ArkUIAniModule._TransferClientAuthenticationHandlerToDynamic(value_casted.peer!.ptr)
    }

    public static transferSslErrorHandlerToStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: SslErrorHandler = new SslErrorHandler()
        if (!ArkUIAniModule._TransferSslErrorHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferSslErrorHandlerToDynamic(value: Object): Any {
        if (!TypeChecker.isSslErrorHandler(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as SslErrorHandler
        return ArkUIAniModule._TransferSslErrorHandlerToDynamic(value_casted.peer!.ptr)
    }
    public static transferPermissionRequestStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: PermissionRequest = new PermissionRequest()
        if (!ArkUIAniModule._TransferPermissionRequestToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }

    public static transferPermissionRequestDynamic(value: Object): Any {
        if (!TypeChecker.isPermissionRequest(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as PermissionRequest
        return ArkUIAniModule._TransferPermissionRequestToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebKeyboardControllerStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: WebKeyboardController = new WebKeyboardController()
        if (!ArkUIAniModule._TransferWebKeyboardControllerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }

    public static transferWebKeyboardControllerDynamic(value: Object): Any {
        if (!TypeChecker.isWebKeyboardController(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebKeyboardController
        return ArkUIAniModule._TransferWebKeyboardControllerToDynamic(value_casted.peer!.ptr)
    }

    public static transferControllerHandlerStatic(value: Any): Object {
        registerAllNativeModuleLibraryName()
        let result: ControllerHandler = new ControllerHandler()
        if (!ArkUIAniModule._TransferControllerHandlerToStatic(result.peer!.ptr, ESValue.wrap(value))) {
            throw new Error('transfer failed')
        }
        return result as Object
    }

    public static transferControllerHandlerDynamic(value: Object): Any {
        if (!TypeChecker.isControllerHandler(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as ControllerHandler
        return ArkUIAniModule._TransferControllerHandlerToDynamic(value_casted.peer!.ptr)
    }
}

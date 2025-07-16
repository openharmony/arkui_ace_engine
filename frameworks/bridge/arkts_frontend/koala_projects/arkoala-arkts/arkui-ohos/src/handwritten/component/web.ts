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

function registerAllNativeModuleLibraryName() {
    registerNativeModuleLibraryName('InteropNativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('ArkUINativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('ArkUIGeneratedNativeModule', 'ArkoalaNative_ark.z')
    registerNativeModuleLibraryName('TestNativeModule', 'ArkoalaNative_ark.z')
}

export class ArkWebTransfer {
    public static transferScreenCaptureHandlerStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamicObject is null or undefined')
        }
        let result: ScreenCaptureHandler = new ScreenCaptureHandler()
        if (!ArkUIAniModule._TransferScreenCaptureHandlerToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferScreenCaptureHandlerDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isScreenCaptureHandler(value)) {
            throw new Error('staticObject type mismatch')
        }
        const value_casted = value as ScreenCaptureHandler
        return ArkUIAniModule._TransferScreenCaptureHandlerToDynamic(value_casted.peer!.ptr)
    }

    public static transferFileSelectorParamStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamic object is null or undefined')
        }
        let result: FileSelectorParam = new FileSelectorParam()
        if (!ArkUIAniModule._TransferFileSelectorParamToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferFileSelectorParamDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isFileSelectorParam(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as FileSelectorParam
        return ArkUIAniModule._TransferFileSelectorParamToDynamic(value_casted.peer!.ptr)
    }

    public static transferJsResultStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamic object is null or undefined')
        }
        let result: JsResult = new JsResult()
        if (!ArkUIAniModule._TransferJsResultToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferJsResultDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isJsResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as JsResult
        return ArkUIAniModule._TransferJsResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferFileSelectorResultStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamic object is null or undefined')
        }
        let result: FileSelectorResult = new FileSelectorResult()
        if (!ArkUIAniModule._TransferFileSelectorResultToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferFileSelectorResultDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isFileSelectorResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as FileSelectorResult
        return ArkUIAniModule._TransferFileSelectorResultToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebContextMenuParamStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamic object is null or undefined')
        }
        let result: WebContextMenuParam = new WebContextMenuParam()
        if (!ArkUIAniModule._TransferWebContextMenuParamToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebContextMenuParamDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isWebContextMenuParam(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebContextMenuParam
        return ArkUIAniModule._TransferWebContextMenuParamToDynamic(value_casted.peer!.ptr)
    }

    public static transferWebContextMenuResultStatic(value: Object | undefined | null): Object {
        registerAllNativeModuleLibraryName()
        if (value === undefined || value === null) {
            throw new Error('dynamic object is null or undefined')
        }
        let result: WebContextMenuResult = new WebContextMenuResult()
        if (!ArkUIAniModule._TransferWebContextMenuResultToStatic(result.peer!.ptr, value)) {
            throw new Error('transfer failed')
        }
        return result as Object
    }
    public static transferWebContextMenuResultDynamic(value: Object): Object | undefined | null {
        if (!TypeChecker.isWebContextMenuResult(value)) {
            throw new Error('static object type mismatch')
        }
        const value_casted = value as WebContextMenuResult
        return ArkUIAniModule._TransferWebContextMenuResultToDynamic(value_casted.peer!.ptr)
    }
}

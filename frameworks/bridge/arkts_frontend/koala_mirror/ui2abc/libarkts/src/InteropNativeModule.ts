/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import {
    KNativePointer as KPtr,
    KInt,
    registerNativeModuleLibraryName,
    loadNativeModuleLibrary
} from "@koalaui/interop"
import { findNativeModule } from "./Es2pandaNativeModule"

export class InteropNativeModule {
    _StringLength(ptr: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _StringData(ptr: KPtr, buffer: KPtr, length: KInt): void {
        throw new Error("Not implemented")
    }
    _GetStringFinalizer(): KPtr {
        throw new Error("Not implemented")
    }
    _RawUtf8ToString(ptr: KPtr): string  {
        throw new Error("Not implemented")
    }
    _InvokeFinalizer(ptr: KPtr, finalizer: KPtr): void {
        throw new Error("Not implemented")
    }
    _GetPtrVectorSize(ptr: KPtr): KInt {
        throw new Error("Not implemented")
    }
    _GetPtrVectorElement(ptr: KPtr, index: KInt): KPtr {
        throw new Error("Not implemented")
    }
}

export function initInterop(): InteropNativeModule {
    registerNativeModuleLibraryName("InteropNativeModule", findNativeModule())
    const instance = new InteropNativeModule()
    loadNativeModuleLibrary("InteropNativeModule", instance)
    return instance
}

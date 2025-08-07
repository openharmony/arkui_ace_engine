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

import { KPointer, KInt } from "@koalaui/interop"
import image from "@ohos.multimedia.image"
import webview from "@ohos.web.webview"
import common from "@ohos.app.ability.common"
import { DrawContext } from "arkui/Graphics"
import { DrawModifier } from "arkui/component"

export class ArkUIAniModule {
    static {
        loadLibrary("arkoala_native_ani")
    }

    native static _Image_Transfer_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void

    native static _Web_SetWebOptions(ptr: KPointer, webviewController: webview.WebviewController): void
    native static _Web_SetWebController_ControllerHandler(ptr: KPointer, webviewController: webview.WebviewController): void
    native static _ConvertUtils_ConvertFromPixelMapAni(pixelmap: image.PixelMap): KPointer

    native static _ConvertUtils_ConvertToPixelMapAni(ptr: KPointer): image.PixelMap

    native static _Common_GetHostContext(key: KInt): common.Context

    native static _Common_Sync_InstanceId(id: KInt): void
    native static _Common_Restore_InstanceId(): void

    native static _ContentSlot_construct(id: KInt): KPointer

    native static _ContentSlotInterface_setContentSlotOptions(slot: KPointer, content: KPointer): void

    native static _SetDrawCallback(ptr: KPointer, callback: ((context: DrawContext) => void)): void

    native static _SetDrawModifier(ptr: KPointer, drawModifier: DrawModifier): void

    native static _Invalidate(ptr: KPointer): void
}

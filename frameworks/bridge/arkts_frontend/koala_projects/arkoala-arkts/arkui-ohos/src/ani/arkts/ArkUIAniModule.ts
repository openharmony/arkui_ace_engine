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

import { KPointer, KInt, KLong } from "@koalaui/interop"
import image from "@ohos.multimedia.image"
import webview from "@ohos.web.webview"
import common from "@ohos.app.ability.common"
import unifiedDataChannel from "@ohos.data.unifiedDataChannel"
import { DrawContext } from "arkui/Graphics"
import { DrawModifier, AsyncCallback } from "arkui/component"
import { ArkCustomComponent } from "arkui/ArkCustomComponent"
import { WaterFlowOptions,WaterFlowSections } from "arkui/component"
import { HookDragInfo } from "arkui/handwritten"

export class ArkUIAniModule {
    static {
        loadLibrary("arkoala_native_ani")
    }

    native static _Web_SetWebOptions(ptr: KPointer, webviewController: webview.WebviewController): void
    native static _ConvertUtils_ConvertFromPixelMapAni(pixelmap: image.PixelMap): KPointer
    native static _ConvertUtils_ConvertToPixelMapAni(ptr: KPointer): image.PixelMap
    native static _Common_GetHostContext(): common.Context
    native static _Common_Sync_InstanceId(id: KInt): void
    native static _Common_Restore_InstanceId(): void
    native static _Common_Get_Current_InstanceId(): KInt
    native static _CustomNode_Construct(id: KInt, component: ArkCustomComponent): KPointer
    native static _BuilderProxyNode_Construct(id: KInt): KPointer
    native static _ContentSlot_construct(id: KInt): KPointer
    native static _ContentSlotInterface_setContentSlotOptions(slot: KPointer, content: KPointer): void
    native static _SetDrawCallback(ptr: KPointer, callback: ((context: DrawContext) => void)): void
    native static _SetDrawModifier(ptr: KPointer, drawModifier: DrawModifier): void
    native static _Invalidate(ptr: KPointer): void
    native static _SetWaterFlowOptions(ptr: KPointer, options: WaterFlowOptions): void

    // for Drag
    native static _DragEvent_Set_Data(ptr: KLong, data : unifiedDataChannel.UnifiedData) : void

    native static _DragEvent_Get_Data(ptr: KLong) : unifiedDataChannel.UnifiedData

    native static _DragEvent_Get_Summary(ptr: KLong) : unifiedDataChannel.Summary

    native static _DragEvent_Set_PixelMap(ptr: KLong, pixelMap: image.PixelMap) : void

    native static _DragEvent_Set_ExtraInfo(ptr: KLong, extraInfo: string) : void

    native static _DragEvent_Set_CustomNode(ptr: KLong, customNode: KPointer) : void

    native static _DragEvent_ConvertFromPixelMapToAniPointer(pixelMap: image.PixelMap) : KPointer

    native static _Drag_Set_AllowDrop_Null(ptr: KLong) : void

    native static _Drag_Set_AllowDrop(ptr: KPointer, thisArray: Array<string>, thisLength: KInt): void

    native static _Drag_Set_DragPreview(ptr: KPointer, dragInfo: HookDragInfo): void

    // for componentSnapshot
    native static _ComponentSnapshot_createFromBuilderWithCallback(ptr: KPointer, destroyCallback: () => void,
        callback: AsyncCallback<image.PixelMap>, delay?: number, checkImageStatus?: boolean): void
    native static _ComponentSnapshot_createFromBuilderWithPromise(ptr: KPointer, destroyCallback: () => void,
            delay?: number, checkImageStatus?: boolean): Promise<image.PixelMap>
}

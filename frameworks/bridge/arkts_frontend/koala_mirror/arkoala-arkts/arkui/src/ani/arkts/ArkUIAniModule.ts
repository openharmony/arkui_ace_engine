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

import { KPointer, KInt, KLong, KBoolean, KFloat } from "@koalaui/interop"
//import { drawing } from "@ohos/graphics/drawing"
//import image from "@ohos.multimedia.image"
//import webview from "@ohos.web.webview"
//import common from "@ohos.app.ability.common"
//import unifiedDataChannel from "@ohos.data.unifiedDataChannel"
import { LocalStorage } from '@ohos.arkui.stateManagement';
//import { DrawContext } from "arkui/Graphics"
//import { AnimatableArithmetic, DrawModifier, AsyncCallback, Callback, DragItemInfo, ResourceColor } from "arkui/component"
//import { ArkCustomComponent } from "arkui/ArkCustomComponent"
//import { WaterFlowOptions,WaterFlowSections, XComponentControllerCallbackInternal, OverlayOptions } from "arkui/component"
//import { ChildrenMainSize } from "arkui/component"
//import { HookDragInfo } from "arkui/handwritten"
//import { dragController } from "@ohos/arkui/dragController"
//import { componentSnapshot } from "@ohos/arkui/componentSnapshot"
//import { DrawableDescriptor } from "@ohos.arkui.drawableDescriptor"
//import { uiObserver }  from "@ohos/arkui/observer"

export class ArkUIAniModule {
    static {
        loadLibrary('arkoala_native_ani')
    }

//    native static _Image_ResizableOptions(ptr: KPointer, value: drawing.Lattice): void
//    native static _Image_Consturct_PixelMap(ptr: KPointer, value: image.PixelMap): void
//    native static _Image_Consturct_DrawableDescriptor(ptr: KPointer, value: DrawableDescriptor, type: int): void
//    native static _Image_DrawingColorFilter(ptr: KPointer, value: drawing.ColorFilter): void
//    native static _Web_SetWebOptions(ptr: KPointer, webviewController: webview.WebviewController): void
//    native static _Web_SetWebController_ControllerHandler(ptr: KPointer, webviewController: webview.WebviewController): void
//    native static _ConvertUtils_ConvertFromPixelMapAni(pixelmap: image.PixelMap): KPointer
//    native static _ConvertUtils_ConvertToPixelMapAni(ptr: KPointer): image.PixelMap
//    native static _Common_GetHostContext(): common.Context
//    native static _Common_Sync_InstanceId(id: KInt): void
//    native static _Common_Restore_InstanceId(): void
//    native static _Common_Get_Current_InstanceId(): KInt
//    native static _Common_GetFocused_InstanceId(): KInt
//    native static _Common_GetSharedLocalStorage(): LocalStorage
//    native static _CustomNode_Construct(id: KInt, component: ArkCustomComponent): KPointer
//    native static _CustomNode_QueryNavigationInfo(ptr: KPointer): uiObserver.NavigationInfo
//    native static _CustomNode_QueryNavDestinationInfo(ptr: KPointer): uiObserver.NavDestinationInfo
//    native static _CustomNode_QueryNavDestinationInfo0(ptr: KPointer, isInner: boolean): uiObserver.NavDestinationInfo
//    native static _CustomNode_QueryRouterPageInfo(ptr: KPointer): uiObserver.RouterPageInfo
//    native static _BuilderProxyNode_Construct(id: KInt): KPointer
//    native static _ContentSlot_construct(id: KInt): KPointer
//    native static _ContentSlotInterface_setContentSlotOptions(slot: KPointer, content: KPointer): void
//    native static _SetDrawCallback(ptr: KPointer, callback: ((context: DrawContext) => void)): void
//    native static _SetDrawModifier(ptr: KPointer, flag: KInt, drawModifier: DrawModifier): void
//    native static _Invalidate(ptr: KPointer): void
//    native static _SetWaterFlowOptions(ptr: KPointer, options: WaterFlowOptions): void
//    native static _SetListChildrenMainSize(ptr: KPointer, value: ChildrenMainSize): void
//    native static _LazyForEachNode_Construct(id: KInt): KPointer
//    native static _SetOverlay_ComponentContent(node: KPointer, buildNodePtr: KPointer, options?: OverlayOptions): void

    // for Drag
//    native static _DragEvent_Set_Data(ptr: KLong, data : unifiedDataChannel.UnifiedData) : void
//    native static _DragEvent_Get_Data(ptr: KLong) : unifiedDataChannel.UnifiedData
//    native static _DragEvent_Get_Summary(ptr: KLong) : unifiedDataChannel.Summary
//    native static _DragEvent_Start_Data_Loading(ptr: KLong, data : unifiedDataChannel.GetDataParams) : string
//    native static _DragEvent_Set_PixelMap(ptr: KLong, pixelMap: image.PixelMap) : void
//    native static _DragEvent_Set_ExtraInfo(ptr: KLong, extraInfo: string) : void
//    native static _DragEvent_Set_CustomNode(ptr: KLong, customNode: KPointer) : void
//    native static _Drag_Set_AllowDrop_Null(ptr: KLong) : void
//    native static _Drag_Set_AllowDrop(ptr: KPointer, thisArray: Array<string>, thisLength: KInt): void
//    native static _Drag_Set_DragPreview(ptr: KPointer, dragInfo: HookDragInfo): void

    // for componentSnapshot
//    native static _ComponentSnapshot_createFromBuilderWithCallback(ptr: KPointer, destroyCallback: () => void,
//        callback: AsyncCallback<image.PixelMap>, delay?: number, checkImageStatus?: boolean,
//        options?: componentSnapshot.SnapshotOptions): void
//    native static _ComponentSnapshot_createFromBuilderWithPromise(ptr: KPointer, destroyCallback: () => void,
//        delay?: number, checkImageStatus?: boolean,
//        options?: componentSnapshot.SnapshotOptions): Promise<image.PixelMap>
//    native static _ComponentSnapshot_createFromComponentWithPromise(ptr: KPointer, destroyCallback: () => void,
//        delay?: number, checkImageStatus?: boolean,
//        options?: componentSnapshot.SnapshotOptions): Promise<image.PixelMap>

    // for dragController
//    native static _DragController_executeDragWithCallback(custom: DragItemInfo, builder: KPointer,
//        destroyCallback: () => void, dragInfo: dragController.DragInfo,
//        callback: AsyncCallback<dragController.DragEventParam>): void
//    native static _DragController_executeDragWithPromise(custom: DragItemInfo, builder: KPointer,
//        destroyCallback: () => void, dragInfo: dragController.DragInfo): Promise<dragController.DragEventParam>
//    native static _DragController_createDragAction(customArray: Array<DragItemInfo>, builderArray: Array<KPointer>,
//        destroyCallback: () => void, dragInfo: dragController.DragInfo): dragController.DragAction
//    native static _DragController_startDrag(dragActionPtr: KPointer): Promise<void>
//    native static _DragController_on(type: string, callback: Callback<dragController.DragAndDropInfo>,
//        dragActionPtr: KPointer): void
//    native static _DragController_off(type: string, callback: Callback<dragController.DragAndDropInfo> | undefined,
//        dragActionPtr: KPointer): void
//    native static _DragController_setDragEventStrictReportingEnabled(enable: boolean): void
//    native static _DragController_cancelDataLoading(key: string): void
//    native static _DragController_notifyDragStartReques(requestStatus: dragController.DragStartRequestStatus): void

//    native static _DragController_getDragPreview(): dragController.DragPreview

//    native static _DragController_setForegroundColor(color: ResourceColor, dragPreviewPtr: KPointer): void

//    native static _DragController_animate(options: dragController.AnimationOptions, handler: () =>void,
//        dragPreviewPtr: KPointer): void

//    native static _Animation_SetOrCreateAnimatableProperty<T>(ptr: KPointer, propertyName: string, property: number | AnimatableArithmetic<T>,
//        callback: (value: number | AnimatableArithmetic<T>) => void): void

    native static _CreateViewStackProcessor(): KPointer

    native static _PopViewStackProcessor(): KPointer

    native static _DeleteViewStackProcessor(ptr: KPointer): void
    
//    native static _BackgroundImage_PixelMap(ptr: KPointer, pixelmap: image.PixelMap, repeat: KInt): void
    // for ImageSpan
//    native static _ImageSpan_Set_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void
//    native static _ImageSpan_SetAlt_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void
//    native static _ImageSpan_Set_DrawingColorFilter(ptr: KPointer, value: drawing.ColorFilter): void

//    native static _SetCustomCallback(ptr: KPointer,
//        measureCallback: ((width1: number, height1: number, width2: number, height2: number, width3: number,
//        height3: number) => void), layoutCallback: ((x: number, y: number) => void)): void
//    native static _RequireArkoalaNodeId(capacity: KInt): KInt

    // for Video
//    native static _Video_Transfer_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void;

    // for Shape
//    native static _Shape_Transfer_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void;

    // for  stateMgmt
    native static _PersistentStorage_Get(key: string): string
    native static _PersistentStorage_Set(key: string, value: string): void
    native static _PersistentStorage_Has(key: string): boolean
    native static _PersistentStorage_Clear(): void
    native static _PersistentStorage_Delete(key: string): void
    native static _Env_GetColorMode(): KInt
    native static _Env_GetFontScale(): KFloat
    native static _Env_GetFontWeightScale(): KFloat
    native static _Env_GetAccessibilityEnabled(): boolean
    native static _Env_GetLayoutDirection(): string
    native static _Env_GetLanguageCode(): string

    // for XComponent
//    native static _XComponent_SetSurfaceCallback(ptr: KPointer, callback: XComponentControllerCallbackInternal): void;
    // for ComponentContent
//    native static _RemoveComponent_FromFrameNode(ptr: KPointer, content: KPointer): void
//    native static _AddComponent_ToFrameNode(ptr: KPointer, content: KPointer): void

//    native static _CheckIsUIThread(id: KInt): KBoolean
//    native static _IsDebugMode(id: KInt): KBoolean
//    native static _OnMeasure_InnerMeasure(ptr: KPointer): void
//    native static _OnLayout_InnerLayout(ptr: KPointer): void
//    native static _FrameNode_MarkDirtyNode(ptr: KPointer): void
//    native static _SetParallelScoped(parallel: boolean): void
//    native static _Common_SetCustomPropertyCallBack(ptr: KPointer, removeCallback: () => void,
//        getCallback: (name: string) => string | undefined): void
//    native static _Common_getCustomProperty<T>(ptr: KPointer, key: string): string | undefined
//    native static _ConditionScopeNode_Construct(id: KInt): KPointer;
}

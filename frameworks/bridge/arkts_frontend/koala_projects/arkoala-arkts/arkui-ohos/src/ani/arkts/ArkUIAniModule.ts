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

import { KPointer, KInt, KLong, KBoolean, KFloat, KUInt, KSerializerBuffer  } from '@koalaui/interop';
import { default as drawing } from '@ohos.graphics.drawing';
import image from '@ohos.multimedia.image';
import webview from '@ohos.web.webview';
import common from '@ohos.app.ability.common';
import unifiedDataChannel from '@ohos.data.unifiedDataChannel';
import uniformTypeDescriptor from '@ohos.data.uniformTypeDescriptor';
import { LocalStorage } from '@ohos.arkui.stateManagement';
import { DrawContext } from 'arkui.Graphics';
import { AnimatableArithmetic, AsyncCallback, Callback, DragItemInfo, ResourceColor, DragPreviewOptions, DragInteractionOptions, ExpectedFrameRateRange } from '#generated';
import { ArkCustomComponent } from 'arkui/ArkCustomComponent';
import { WaterFlowOptions, WaterFlowSections, OverlayOptions } from '#generated';
import { ChildrenMainSize, PageTransitionOptions, PageTransitionCallback, SlideEffect, ScaleOptions, TranslateOptions } from '#generated';
import { XComponentOptionsInternal } from '#generated';
import { HookDragInfo } from 'arkui/handwritten';
import { dragController } from '@ohos/arkui/dragController';
import { componentSnapshot } from '@ohos/arkui/componentSnapshot';
import { KeyboardAvoidMode } from '@ohos/arkui/UIContext';
import { DrawableDescriptor } from '@ohos.arkui.drawableDescriptor';
import { default as uiObserver }  from '@ohos/arkui/observer';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import { TextModifier } from 'arkui.TextModifier'
import { NodeAdapter } from 'arkui.FrameNode'
import { Scene } from '@ohos.graphics.scene';
import { RectShape, CircleShape, EllipseShape, PathShape } from '@ohos.arkui.shape';
import curves from '@ohos.curves';
import matrix4 from '@ohos.matrix4';
import uiEffect from '@ohos.graphics.uiEffect';
import { DrawModifier } from "#handwritten"

export class ArkUIAniModule {
    static {
        loadLibrary('arkoala_native_ani')
    }
    native static _Extractors_ToDrawableDescriptorPtr(value: DrawableDescriptor): KPointer;
    native static _Extractors_ToDrawingColorFilterPtr(drawingColorFilter: drawing.ColorFilter): KPointer;
    native static _Extractors_ToDrawingLatticePtr(drawingLattice: drawing.Lattice): KPointer;
    native static _Extractors_ToImagePixelMapPtr(pixelmap: image.PixelMap): KPointer;
    native static _Extractors_FromImagePixelMapPtr(ptr: KPointer): image.PixelMap;
    native static _Extractors_ToRectShapePtr(value: RectShape): KPointer;
    native static _Extractors_FromRectShapePtr(ptr: KPointer): RectShape;
    native static _Extractors_ToCircleShapePtr(value: CircleShape): KPointer;
    native static _Extractors_FromCircleShapePtr(ptr: KPointer): CircleShape;
    native static _Extractors_ToEllipseShapePtr(value: EllipseShape): KPointer;
    native static _Extractors_FromEllipseShapePtr(ptr: KPointer): EllipseShape;
    native static _Extractors_ToPathShapePtr(value: PathShape): KPointer;
    native static _Extractors_FromPathShapePtr(ptr: KPointer): PathShape;
    native static _Extractors_ToICurvePtr(value: curves.ICurve): KPointer;
    native static _Extractors_ToMatrix4TransitPtr(value: matrix4.Matrix4Transit): KPointer;
    native static _Extractors_ToUiEffectFilterPtr(value: uiEffect.Filter): KPointer;
    native static _Extractors_ToUiEffectVisualEffectPtr(value: uiEffect.VisualEffect): KPointer;
    native static _Extractors_ToDrawContextPtr(value: DrawContext): KPointer;
    native static _Extractors_FromDrawContextPtr(ptr: KPointer): DrawContext;
    native static _Extractors_ToWebviewWebviewControllerPtr(value: webview.WebviewController): KPointer;
    native static _Extractors_FromWebviewWebviewControllerPtr(ptr: KPointer): webview.WebviewController;
    native static _Image_ColorFilter_TransferStatic(ptr: KPointer): KPointer
    native static _Image_ColorFilter_TransferDynamic(ptr: KPointer): KPointer
    native static _Image_ResizableOptions(ptr: KPointer, value: drawing.Lattice): void
    native static _Image_Consturct_PixelMap(ptr: KPointer, value: image.PixelMap): void
    native static _Image_Consturct_DrawableDescriptor(ptr: KPointer, value: DrawableDescriptor, type: int): void
    native static _Image_DrawingColorFilter(ptr: KPointer, value: drawing.ColorFilter): void
    native static _ConvertUtils_ConvertFromPixelMapAni(pixelmap: image.PixelMap): KPointer
    native static _ConvertUtils_ConvertToPixelMapAni(ptr: KPointer): image.PixelMap
    native static _Common_GetHostContext(key: KInt): common.Context
    native static _Common_SetFrameRateRange(ptr: KPointer, value: ExpectedFrameRateRange, type: KInt): void
    native static _Common_Sync_InstanceId(id: KInt): void
    native static _Common_Restore_InstanceId(): void
    native static _Common_Get_Current_InstanceId(): KInt
    native static _Common_GetFocused_InstanceId(): KInt
    native static _Common_SetImageCacheCount(value: KInt, instanceId: KInt): void
    native static _Common_SetImageRawDataCacheSize(value: KInt, instanceId: KInt): void
    native static _GetNodePtrWithPeerPtr(ptr: KPointer): KLong
    native static _GetNodeIdWithNodePtr(ptr: KPointer): KInt
    native static _GetNodeIdWithPeerPtr(ptr: KPointer): KInt
    native static _CreateRenderNodePeerWithNodePtr(ptr: KPointer): KPointer
    native static _ToColorLong(color: KInt): KLong
    native static _ToColorInt(color: KLong): KInt
    native static _Common_GetSharedLocalStorage(): LocalStorage
    native static _GetKeyboardAvoidMode(): KeyboardAvoidMode
    native static _SetKeyboardAvoidMode(mode: KeyboardAvoidMode): void
    native static _CustomNode_Construct(id: KInt, component: ArkCustomComponent): KPointer
    native static _CustomNode_RequestFrame(): void
    native static _CustomNode_QueryNavigationInfo(ptr: KPointer): uiObserver.NavigationInfo
    native static _CustomNode_QueryNavDestinationInfo(ptr: KPointer): uiObserver.NavDestinationInfo
    native static _CustomNode_QueryNavDestinationInfo0(ptr: KPointer, isInner: boolean): uiObserver.NavDestinationInfo
    native static _CustomNode_OnReuse(ptr: KPointer): void
    native static _CustomNode_OnRecycle(ptr: KPointer): void
    native static _CustomNode_QueryNavDestinationInfo1(uniqueId: KInt): uiObserver.NavDestinationInfo
    native static _CustomNode_QueryRouterPageInfo(ptr: KPointer): uiObserver.RouterPageInfo
    native static _CustomNode_QueryRouterPageInfo1(uniqueId: KInt): uiObserver.RouterPageInfo
    native static _BuilderProxyNode_Construct(id: KInt): KPointer
    native static _ContentSlot_construct(id: KInt): KPointer
    native static _ContentSlotInterface_setContentSlotOptions(slot: KPointer, content: KPointer): void
    native static _SetDrawCallback(ptr: KPointer, callback: ((context: DrawContext) => void)): void
    native static _SetFrameNodeDrawCallback(ptr: KPointer, callback: ((context: DrawContext) => void)): void
    native static _SetDrawModifier(ptr: KPointer, flag: KInt, drawModifier: DrawModifier): void
    native static _Invalidate(ptr: KPointer): void
    native static _SetWaterFlowSection(ptr: KPointer, sections: WaterFlowSections): void
    native static _SetWaterFlowFooterContent(ptr: KPointer, footerContent: KPointer): void
    native static _SetWaterFlowFooter(ptr: KPointer, footer: KPointer): void
    native static _ResetWaterFlowFooter(ptr: KPointer): void
    native static _SetWaterFlowScroller(ptr: KPointer, scroller: KPointer): void
    native static _SetWaterFlowLayoutMode(ptr: KPointer, mode: KInt): void
    native static _SetListChildrenMainSize(ptr: KPointer, value: ChildrenMainSize): void
    native static _LazyForEachNode_Construct(id: KInt, isRepeat: boolean): KPointer
    native static _SetOverlay_ComponentContent(node: KPointer, buildNodePtr: KPointer, options?: OverlayOptions): void

    native static _TransferKeyEventPointer(input: KPointer): KPointer
    native static _CreateKeyEventAccessorWithPointer(input: KPointer): KPointer
    native static _CreateEventTargetInfoAccessor(): KPointer
    native static _EventTargetInfoAccessorWithId(input: KPointer, id: string): void
    native static _CreateScrollableTargetInfoAccessor(): KPointer
    native static _ScrollableTargetInfoAccessorWithId(input: KPointer, id: string): void
    native static _ScrollableTargetInfoAccessorWithPointer(input: KPointer, pointer: KPointer): void
    native static _TransferScrollableTargetInfoPointer(input: KPointer): KPointer

    // for web
    native static _TransferScreenCaptureHandlerToStatic(ptr: KPointer, value: ESValue): boolean
    native static _TransferJsGeolocationToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferJsResultToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferEventResultToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferFileSelectorResultToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferFileSelectorParamToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferWebContextMenuResultToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferWebContextMenuParamToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferHttpAuthHandlerToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferWebResourceReponseToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferWebResourceRequestToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferConsoleMessageToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferDataResubmissionHandlerToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferClientAuthenticationHandlerToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferSslErrorHandlerToStatic(ptr: KPointer, value: ESValue) : boolean
    native static _TransferPermissionRequestToStatic(ptr: KPointer, value: ESValue): boolean
    native static _TransferControllerHandlerToStatic(ptr: KPointer, value: ESValue): boolean
    native static _TransferWebKeyboardControllerToStatic(ptr: KPointer, value: ESValue): boolean

    native static _TransferScreenCaptureHandlerToDynamic(ptr: KPointer): Any
    native static _TransferJsGeolocationToDynamic(ptr: KPointer) : Any
    native static _TransferJsResultToDynamic(ptr: KPointer) : Any
    native static _TransferEventResultToDynamic(ptr: KPointer) : Any
    native static _TransferFileSelectorResultToDynamic(ptr: KPointer) : Any
    native static _TransferFileSelectorParamToDynamic(ptr: KPointer) : Any
    native static _TransferWebContextMenuResultToDynamic(ptr: KPointer) : Any
    native static _TransferWebContextMenuParamToDynamic(ptr: KPointer) : Any
    native static _TransferHttpAuthHandlerToDynamic(ptr: KPointer) : Any
    native static _TransferWebResourceReponseToDynamic(ptr: KPointer) : Any
    native static _TransferWebResourceRequestToDynamic(ptr: KPointer) : Any
    native static _TransferConsoleMessageToDynamic(ptr: KPointer) : Any
    native static _TransferDataResubmissionHandlerToDynamic(ptr: KPointer) : Any
    native static _TransferClientAuthenticationHandlerToDynamic(ptr: KPointer) : Any
    native static _TransferSslErrorHandlerToDynamic(ptr: KPointer) : Any
    native static _TransferPermissionRequestToDynamic(ptr: KPointer) : Any
    native static _TransferControllerHandlerToDynamic(ptr: KPointer) : Any
    native static _TransferWebKeyboardControllerToDynamic(ptr: KPointer) : Any

    // for Drag
    native static _DragEvent_Set_Data(ptr: KLong, data : unifiedDataChannel.UnifiedData) : void
    native static _DragEvent_Get_Data(ptr: KLong) : unifiedDataChannel.UnifiedData
    native static _DragEvent_Get_Summary(ptr: KLong) : unifiedDataChannel.Summary
    native static _DragEvent_Start_Data_Loading(ptr: KLong, data : unifiedDataChannel.GetDataParams) : string
    native static _DragEvent_Set_PixelMap(ptr: KLong, pixelMap: image.PixelMap) : void
    native static _DragEvent_Set_ExtraInfo(ptr: KLong, extraInfo: string) : void
    native static _DragEvent_Set_CustomNode(ptr: KLong, customNode: KPointer) : void
    native static _Drag_Set_AllowDrop_Null(ptr: KLong) : void
    native static _Drag_Set_AllowDrop(ptr: KPointer, thisArray: Array<uniformTypeDescriptor.UniformDataType> | undefined): void
    native static _Drag_Set_DragPreview(ptr: KPointer, dragInfo: HookDragInfo): void
    native static _Drag_Set_DragPreviewOptions(ptr: KPointer, value: DragPreviewOptions | undefined, options?: DragInteractionOptions): void
    native static _Extractors_toUnifiedDataChannelUnifiedDataPtr(value: unifiedDataChannel.UnifiedData) : KPointer
    native static _Extractors_fromUnifiedDataChannelUnifiedDataPtr(ptr: KPointer) : unifiedDataChannel.UnifiedData

    native static _createDragEventAccessorWithPointer(input: KPointer) : KPointer
    native static _getDragEventPointer(input: KPointer): KPointer

    // for componentSnapshot
    native static _ComponentSnapshot_createFromBuilderWithCallback(ptr: KPointer, destroyCallback: () => void,
        callback: AsyncCallback<image.PixelMap>, delay?: int, checkImageStatus?: boolean,
        options?: componentSnapshot.SnapshotOptions): void
    native static _ComponentSnapshot_createFromBuilderWithPromise(ptr: KPointer, destroyCallback: () => void,
        delay?: int, checkImageStatus?: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<image.PixelMap>
    native static _ComponentSnapshot_createFromComponentWithPromise(ptr: KPointer, destroyCallback: () => void,
        delay?: int, checkImageStatus?: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<image.PixelMap>

    // for dragController
    native static _DragController_executeDragWithCallback(custom: DragItemInfo, builder: KPointer,
        destroyCallback: () => void, dragInfo: dragController.DragInfo,
        callback: AsyncCallback<dragController.DragEventParam>): void
    native static _DragController_executeDragWithPromise(custom: DragItemInfo, builder: KPointer,
        destroyCallback: () => void, dragInfo: dragController.DragInfo): Promise<dragController.DragEventParam>
    native static _DragController_createDragAction(customArray: Array<DragItemInfo>, builderArray: Array<KPointer>,
        destroyCallback: () => void, dragInfo: dragController.DragInfo): dragController.DragAction
    native static _DragController_startDrag(dragActionPtr: KPointer): Promise<void>
    native static _DragController_on(callback: Callback<dragController.DragAndDropInfo>,
        dragActionPtr: KPointer): void
    native static _DragController_off(callback: Callback<dragController.DragAndDropInfo> | undefined,
        dragActionPtr: KPointer): void
    native static _DragController_setDragEventStrictReportingEnabled(enable: boolean): void
    native static _DragController_cancelDataLoading(key: string): void
    native static _DragController_notifyDragStartReques(requestStatus: dragController.DragStartRequestStatus): void
    native static _DragController_getDragPreview(): dragController.DragPreview
    native static _DragController_setForegroundColor(color: ResourceColor, dragPreviewPtr: KPointer): void
    native static _DragController_animate(options: dragController.AnimationOptions, handler: () =>void,
        dragPreviewPtr: KPointer): void
    native static _DragController_cleanDragAction(dragActionptr: KPointer): void
    native static _DragController_cleanDragPreview(dragPreviewptr: KPointer): void

    native static _Animation_SetOrCreateAnimatableProperty<T>(ptr: KPointer, propertyName: string, property: number | AnimatableArithmetic<T>,
        callback: (value: number | AnimatableArithmetic<T>) => void): void
    native static _Animation_CreatePageTransitionEnter(options: PageTransitionOptions): void
    native static _Animation_CreatePageTransitionExit(options: PageTransitionOptions): void
    native static _Animation_PageTransitionSetOnEnter(event: PageTransitionCallback): void
    native static _Animation_PageTransitionSetOnExit(event: PageTransitionCallback): void
    native static _Animation_PageTransitionSetSlide(value: SlideEffect): void
    native static _Animation_PageTransitionSetTranslate(value: TranslateOptions): void
    native static _Animation_PageTransitionSetScale(value: ScaleOptions): void
    native static _Animation_PageTransitionSetOpacity(value: number): void

    native static _CreateViewStackProcessor(): KPointer

    native static _PopViewStackProcessor(): KPointer

    native static _DeleteViewStackProcessor(ptr: KPointer): void

    native static _BackgroundImage_PixelMap(ptr: KPointer, pixelmap: image.PixelMap, repeat: KInt): void
    // for StyledString
    native static _StyledString_SetPixelMap(peerPtr: KPointer, pixelmap: image.PixelMap): void
    native static _StyledString_GetPixelMap(peerPtr: KPointer): image.PixelMap

    // for SymbolGlyph Modifier
    native static _Extractors_ToSymbolGlyphModifierPtr(callBack: (node: KPointer) => void,
        value: SymbolGlyphModifier): KPointer;
    native static _Extractors_FromSymbolGlyphModifierPtr(ptr: KPointer): SymbolGlyphModifier;

    // for Text Modifier
    native static _Extractors_ToTextModifierPtr(callBack: (node: KPointer) => void,
        value: TextModifier): KPointer;
    native static _Extractors_FromTextModifierPtr(ptr: KPointer): TextModifier;

    // for ImageSpan
    native static _ImageSpan_Set_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void
    native static _ImageSpan_SetAlt_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void
    native static _ImageSpan_Set_DrawingColorFilter(ptr: KPointer, value: drawing.ColorFilter): void

    native static _SetCustomCallback(ptr: KPointer,
        measureCallback: ((width1: number, height1: number, width2: number, height2: number, width3: number,
        height3: number) => void), layoutCallback: ((x: number, y: number) => void)): void
    native static _RequireArkoalaNodeId(capacity: KInt): KInt

    // for Video
    native static _Video_Transfer_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void;

    // for Shape
    native static _Shape_Transfer_PixelMap(ptr: KPointer, pixelmap: image.PixelMap): void;

    // for RichEditor
    native static _RichEditor_Transfer_PixelMap(pixelmap: image.PixelMap): KPointer;

    // for  stateMgmt
    native static _PersistentStorage_Get(key: string, areaMode: KInt): string
    native static _PersistentStorage_Set(key: string, value: string, areaMode: KInt): void
    native static _PersistentStorage_Has(key: string, areaMode: KInt): boolean
    native static _PersistentStorage_Clear(): void
    native static _PersistentStorage_Delete(key: string, areaMode: KInt): void
    native static _Env_GetColorMode(): KInt
    native static _Env_GetFontScale(): KFloat
    native static _Env_GetFontWeightScale(): KFloat
    native static _Env_GetAccessibilityEnabled(): boolean
    native static _Env_GetLayoutDirection(): string
    native static _Env_GetLanguageCode(): string

    // for XComponent
    native static _XComponent_SetXComponentControllerCallback(ptr: KPointer, options: XComponentOptionsInternal): void;
    // for ComponentContent
    native static _RemoveComponent_FromFrameNode(ptr: KPointer, content: KPointer): void
    native static _AddComponent_ToFrameNode(ptr: KPointer, content: KPointer): void

    // for UIContext without window
    native static _CreateWindowFreeContainer(context: common.Context): KInt
    native static _DestroyWindowFreeContainer(instanceId: KInt): void

    native static _CheckIsUIThread(id: KInt): KBoolean
    native static _IsDebugMode(id: KInt): KBoolean
    native static _OnMeasure_InnerMeasure(ptr: KPointer): void
    native static _OnLayout_InnerLayout(ptr: KPointer): void
    native static _SetParallelScoped(parallel: boolean): void
    native static _Common_SetCustomPropertyCallBack(ptr: KPointer, removeCallback: () => void,
        getCallback: (name: string) => string | undefined): void
    native static _Common_getCustomProperty<T>(ptr: KPointer, key: string): string | undefined
    native static _ConditionScopeNode_Construct(id: KInt): KPointer;

    native static _Common_vp2px(value:number, instanceId: KInt): number
    native static _Common_px2vp(value:number, instanceId: KInt): number
    native static _Common_fp2px(value:number, instanceId: KInt): number
    native static _Common_px2fp(value:number, instanceId: KInt): number
    native static _Common_lpx2px(value:number, instanceId: KInt): number
    native static _Common_px2lpx(value:number, instanceId: KInt): number
    native static _Common_getWindowName(instanceId: KInt): string

    // for transfer
    native static _createTouchEventAccessorWithPointer(input: KPointer): KPointer
    native static _createMouseEventAccessorWithPointer(input: KPointer): KPointer
    native static _createAxisEventAccessorWithPointer(input: KPointer): KPointer
    native static _createClickEventAccessorWithPointer(input: KPointer): KPointer
    native static _createHoverEventAccessorWithPointer(input: KPointer): KPointer
    native static _getTouchEventPointer(peer: KPointer): KPointer
    native static _getMouseEventPointer(peer: KPointer): KPointer
    native static _getAxisEventPointer(peer: KPointer): KPointer
    native static _getClickEventPointer(peer: KPointer): KPointer
    native static _getHoverEventPointer(peer: KPointer): KPointer
    // for Canvas
    native static _CanvasRenderer_SetPixelMap(peerPtr: KPointer, pixelmap: image.PixelMap): void
    native static _CanvasRenderer_DrawPixelMap0(peerPtr: KPointer, pixelmap: image.PixelMap, dx: number, dy: number): void
    native static _CanvasRenderer_DrawPixelMap1(peerPtr: KPointer, pixelmap: image.PixelMap, dx: number, dy: number, dw: number, dh: number): void
    native static _CanvasRenderer_DrawPixelMap2(peerPtr: KPointer, pixelmap: image.PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void
    native static _ImageBitmap_Construct0(src: string, unit: KInt): KPointer
    native static _ImageBitmap_Construct1(src: image.PixelMap, unit: KInt): KPointer
    native static _CanvasRenderer_GetCanvasDensity(peerPtr: KPointer): number
    native static _GetSystemDensity(): number
    native static _CanvasRenderer_GetImageData(peerPtr: KPointer, sx: number, sy: number, sw: number, sh: number): Uint8ClampedArray
    native static _CanvasRenderer_PutImageData0(peerPtr: KPointer, array: Uint8ClampedArray, dx: number, dy: number, width: KInt, height: KInt): void
    native static _CanvasRenderer_PutImageData1(peerPtr: KPointer, array: Uint8ClampedArray, dx: number, dy: number, width: KInt, height: KInt,
        dirtyX: number, dirtyY: number, dirtyWidth: number, dirtyHeight: number): void
    native static _DrawingRenderingContext_GetCanvas(peerPtr: KPointer): drawing.Canvas
    native static _CanvasRenderingContext_GetCanvasId(peerPtr: KPointer): KInt
    native static _CanvasRenderingContext_setAttachCallbackId(peerPtr: KPointer, attachCallbackId: KInt): void
    native static _CanvasRenderingContext_setDetachCallbackId(peerPtr: KPointer, detachCallbackId: KInt): void
    native static _Extractors_ToDrawingCanvasPtr(value: drawing.Canvas): KPointer
    native static _Extractors_FromDrawingCanvasPtr(ptr: KPointer): drawing.Canvas

    native static _FrameNode_MarkDirtyNode(ptr: KPointer): void
    native static _GetAttributeSetTraceEnabled(): boolean
    native static _TraceBegin(traceName: string): void
    native static _TraceEnd(): void
    native static _AsyncTraceBegin(traceName: string, taskId: KInt): void
    native static _AsyncTraceEnd(traceName: string, taskId: KInt): void
    native static _StartProfiler(asptFileName: string, interva: KInt): void
    native static _StopProfiler(): void
    native static _GetColorValue(color: number | string): KUInt
    native static _GetStringColorValue(color: string): KUInt
    native static _GetNumberColorValue(color: number): KUInt
    native static _SendThemeToNative(thisArray: KSerializerBuffer, thisLength: number, elmtId: KInt): void
    native static _SetDefaultTheme(thisArray: KSerializerBuffer, thisLength: number, isDark: boolean): void
    native static _RemoveThemeInNative(withThemeId: number): void
    native static _UpdateColorMode(colorMode: KInt): void
    native static _RestoreColorMode(): void
    native static _SetThemeScopeId(themeScopeId: number): void
    native static _CreateAndBindTheme(
        themeScopeId: KInt,
        themeId: KInt,
        thisArray: KSerializerBuffer, thisLength: number,
        colorMode: KInt,
        onThemeScopeDestroy: () => void
    ): void;
    native static _ApplyParentThemeScopeId(self: KPointer, parent: KPointer): void
    native static _UINode_OnUpdateDone(peer: KPointer): void;
    native static _UINode_SetStatic(peer: KPointer): void;
    
    //NodeAdapter 
    native static _NodeAdapter_Construct( nodeAdapter : NodeAdapter): KPointer
    native static _NodeAdapter_DetachNodeAdapter(ptr : KPointer) : void
    native static _NodeAdapter_AttachNodeAdapter(ptr : KPointer, node: KPointer) : boolean
    native static _NodeAdapter_Dispose(ptr : KPointer) : void
    native static _NodeAdapter_SetTotalNodeCount(ptr : KPointer, count : number) : void
    native static _NodeAdapter_NotifyItemReloaded(ptr : KPointer) : void
    native static _NodeAdapter_NotifyItemChanged(ptr : KPointer, start : number, count : number) : void
    native static _NodeAdapter_NotifyItemRemoved(ptr : KPointer, start : number, count : number) : void
    native static _NodeAdapter_NotifyItemInserted(ptr : KPointer, start : number, count : number) : void
    native static _NodeAdapter_NotifyItemMoved(ptr : KPointer, from : number, to : number) : void
    native static _NodeAdapter_GetAllItems(ptr : KPointer) : Array<number>
    // for ForEach
    native static _SyntaxItem_Construct(id: KInt): KPointer
    native static _ForEachNode_Construct(id: KInt, isRepeat: boolean): KPointer
    native static _ForEach_FinishRender(peerPtr: KPointer): void
    // for Component3D
    native static _Component3D_SetScene(ptr: KPointer, scene: Scene, modelType: KInt): void
    native static _Component3D_SetWidget(ptr: KPointer, scenePath: string, modelType: KInt): void
    native static _Extractors_ToScenePtr(scene: Scene): KPointer;
    // for AppBar
    native static _XBar_Set_ComponentCreateFunc(value: (isTitlebar: KInt, instanceID: KInt) => KLong): void;
    native static _XBar_Set_JsFunc(ptr: KLong, component: Any): void
    native static _XBar_Call_Native(xBarType: KInt, callType: string, message: string): void
}

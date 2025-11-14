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

import { AccessibilityHoverEvent_serializer, TouchTestInfo_serializer, TouchResult_serializer, AxisEvent_serializer, HoverEvent_serializer, ClickEvent_serializer, CrownEvent_serializer, DismissContentCoverAction_serializer, DismissPopupAction_serializer, DismissSheetAction_serializer, DragEvent_serializer, FocusAxisEvent_serializer, ItemDragInfo_serializer, KeyEvent_serializer, MouseEvent_serializer, GeometryInfo_serializer, Measurable_serializer, SizeResult_serializer, Layoutable_serializer, ScrollResult_serializer, SheetDismiss_serializer, SpringBackAction_serializer, TerminationInfo_serializer, TouchEvent_serializer, DragItemInfo_serializer, PopupStateChangeParam_serializer, AccessibilityActionInterceptCallback, AccessibilityAction, AccessibilityActionInterceptResult, AccessibilityCallback, AccessibilityHoverEvent, AccessibilityTransparentCallback, AccessibilityFocusCallback, TouchTestInfo, TouchResult, AxisEvent, HoverEvent, ClickEvent, CrownEvent, DismissContentCoverAction, DismissPopupAction, DismissSheetAction, DragEvent, FocusAxisEvent, ItemDragInfo, KeyEvent, MouseEvent, GeometryInfo, Measurable, SizeResult, Layoutable, ScrollResult, PreDragStatus, SheetDismiss, SheetType, SpringBackAction, TerminationInfo, TouchEvent, DragItemInfo, GestureRecognizerJudgeBeginCallback, HoverCallback, ModifierKeyStateGetter, OnDragEventCallback, OnItemDragStartCallback, OnMoveHandler, OnScrollCallback, OnWillScrollCallback, PopupStateChangeCallback, PopupStateChangeParam, ReuseIdCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, TransitionFinishCallback, VisibleAreaChangeCallback } from "./../../component/common"
import { image_PixelMap_serializer } from "./../ohos.multimedia.image"
import { ButtonConfiguration_serializer, ButtonConfiguration, ButtonTriggerClickCallback } from "./../../component/button"
import { Area_serializer, ConstraintSizeOptions_serializer, SizeOptions_serializer, Area, ConstraintSizeOptions, Length, ResourceStr, SizeOptions, VoidCallback } from "./../../component/units"
import { TextMenuItem_serializer, DeleteValue_serializer, EditableTextChangeValue_serializer, InsertValue_serializer, StyledStringChangeValue_serializer, TextRange_serializer, PreviewText_serializer, TextChangeOptions_serializer, TextMenuItem, DeleteValue, EditableTextChangeValue, InsertValue, StyledStringChangeValue, TextRange, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, OnCreateMenuCallback, OnDidChangeCallback, OnMenuItemClickCallback } from "./../../component/textCommon"
import { ComputedBarAttribute_serializer, ComputedBarAttribute } from "./../../component/grid"
import { CopyEvent_serializer, CutEvent_serializer, RichEditorChangeValue_serializer, RichEditorDeleteValue_serializer, RichEditorInsertValue_serializer, RichEditorRange_serializer, RichEditorSelection_serializer, RichEditorTextSpanResult_serializer, PasteEvent_serializer, CopyEvent, CutEvent, RichEditorChangeValue, RichEditorDeleteValue, RichEditorInsertValue, RichEditorRange, RichEditorSelection, RichEditorTextSpanResult, PasteEvent, MenuCallback, MenuOnAppearCallback, OnHoverCallback, PasteEventCallback, SubmitCallback } from "./../../component/richEditor"
import { CustomSpanMeasureInfo_serializer, CustomSpanMetrics_serializer, CustomSpanDrawInfo_serializer, StyledString_serializer, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledString, UserDataSpan, StyledStringMarshallCallback, StyledStringUnmarshallCallback } from "./../../component/styledString"
import { DismissDialogAction_serializer, DismissDialogAction } from "./../../component/actionSheet"
import { DrawContext_serializer, Size_serializer } from "./../../Graphics"
import { ErrorInformation_serializer, FormCallbackInfo_serializer, RouterCallbackInfo_serializer, ErrorInformation, FormCallbackInfo, RouterCallbackInfo } from "./../../component/formComponent"
import { FullscreenInfo_serializer, PlaybackInfo_serializer, PreparedInfo_serializer, FullscreenInfo, PlaybackInfo, PreparedInfo } from "./../../component/video"
import { GestureEvent_serializer, GestureInfo_serializer, BaseGestureEvent_serializer, GestureRecognizer_serializer, GestureEvent, GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer } from "./../../component/gesture"
import { NativeEmbedDataInfo_serializer, NativeEmbedTouchInfo_serializer, OnAlertEvent_serializer, OnAudioStateChangedEvent_serializer, OnBeforeUnloadEvent_serializer, OnClientAuthenticationEvent_serializer, OnConfirmEvent_serializer, OnConsoleEvent_serializer, OnContextMenuShowEvent_serializer, OnDataResubmittedEvent_serializer, OnDownloadStartEvent_serializer, OnErrorReceiveEvent_serializer, OnFaviconReceivedEvent_serializer, OnFirstContentfulPaintEvent_serializer, OnGeolocationShowEvent_serializer, OnHttpAuthRequestEvent_serializer, OnHttpErrorReceiveEvent_serializer, OnInterceptRequestEvent_serializer, WebResourceResponse_serializer, OnLoadFinishedEvent_serializer, OnLoadInterceptEvent_serializer, OnLoadStartedEvent_serializer, OnOverScrollEvent_serializer, OnPageBeginEvent_serializer, OnPageEndEvent_serializer, OnPageVisibleEvent_serializer, OnPdfLoadEvent_serializer, OnPdfScrollEvent_serializer, OnPermissionRequestEvent_serializer, OnProgressChangeEvent_serializer, OnPromptEvent_serializer, OnRefreshAccessedHistoryEvent_serializer, OnRenderExitedEvent_serializer, OnResourceLoadEvent_serializer, OnScaleChangeEvent_serializer, OnScreenCaptureRequestEvent_serializer, OnScrollEvent_serializer, OnSearchResultReceiveEvent_serializer, OnShowFileSelectorEvent_serializer, OnSslErrorEventReceiveEvent_serializer, OnTitleReceiveEvent_serializer, OnTouchIconUrlReceivedEvent_serializer, OnWindowNewEvent_serializer, WebKeyboardOptions_serializer, NativeEmbedMouseInfo_serializer, AdsBlockedDetails_serializer, BlankScreenDetectionEventInfo_serializer, FirstMeaningfulPaint_serializer, FullScreenEnterEvent_serializer, IntelligentTrackingPreventionDetails_serializer, LargestContentfulPaint_serializer, NativeEmbedParamDataInfo_serializer, NativeEmbedVisibilityInfo_serializer, LoadCommittedDetails_serializer, WebResourceRequest_serializer, RenderProcessNotRespondingData_serializer, SslErrorEvent_serializer, WebKeyboardCallbackInfo_serializer, NativeEmbedDataInfo, NativeEmbedTouchInfo, OnAlertEvent, OnAudioStateChangedEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnConsoleEvent, OnContextMenuShowEvent, OnDataResubmittedEvent, OnDownloadStartEvent, OnErrorReceiveEvent, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, WebResourceResponse, OnLoadFinishedEvent, OnLoadInterceptEvent, OnLoadStartedEvent, OnOverScrollEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPdfLoadEvent, OnPdfScrollEvent, OnPermissionRequestEvent, OnProgressChangeEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnScreenCaptureRequestEvent, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, OnSslErrorEventReceiveEvent, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, WebKeyboardOptions, MouseInfoCallback, NativeEmbedMouseInfo, OnAdsBlockedCallback, AdsBlockedDetails, OnContextMenuHideCallback, OnDetectBlankScreenCallback, BlankScreenDetectionEventInfo, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnFullScreenEnterCallback, FullScreenEnterEvent, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnNativeEmbedObjectParamChangeCallback, NativeEmbedParamDataInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnOverrideErrorPageCallback, OnOverrideUrlLoadingCallback, WebResourceRequest, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnSafeBrowsingCheckResultCallback, ThreatType, OnSslErrorEventCallback, SslErrorEvent, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo } from "./../../component/web"
import { NavDestinationContext_serializer, NavDestinationTransition_serializer, NavDestinationActiveReason, NavDestinationContext, NavDestinationTransition, NavDestinationTransitionDelegate, VisibilityChangeReason } from "./../../component/navDestination"
import { NavigationTransitionProxy_serializer, NavigationAnimatedTransition_serializer, PopInfo_serializer, NavContentInfo_serializer, NavigationMode, NavigationTitleMode, NavigationTransitionProxy, NavigationAnimatedTransition, PopInfo, InterceptionModeCallback, InterceptionShowCallback, NavBar, NavigationOperation, NavContentInfo, UpdateTransitionCallback } from "./../../component/navigation"
import { OnScrollFrameBeginHandlerResult_serializer, OffsetResult_serializer, OnScrollFrameBeginHandlerResult, OffsetResult, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollOnScrollCallback, ScrollOnWillScrollCallback } from "./../../component/scroll"
import { TabContentAnimatedTransition_serializer, TabContentTransitionProxy_serializer, TabsAnimationEvent_serializer, TabContentAnimatedTransition, TabContentTransitionProxy, OnTabsAnimationEndCallback, TabsAnimationEvent, OnTabsAnimationStartCallback, OnTabsContentDidScrollCallback, OnTabsContentWillChangeCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback } from "./../../component/tabs"
import { SurfaceRect_serializer, NativeXComponentPointer, SurfaceRect } from "./../../component/xcomponent"
import { SwiperContentTransitionProxy_serializer, SwiperContentWillScrollResult_serializer, SwiperAnimationEvent_serializer, SwiperContentTransitionProxy, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult, OnSwiperAnimationEndCallback, SwiperAnimationEvent, OnSwiperAnimationStartCallback, OnSwiperGestureSwipeCallback } from "./../../component/swiper"
import { Resource_serializer } from "./../resource"
import { TextPickerResult_serializer, TextPickerResult, OnTextPickerChangeCallback, TextPickerEnterSelectedAreaCallback, TextPickerScrollStopCallback } from "./../../component/textPicker"
import { TimePickerResult_serializer, TimePickerResult, OnTimePickerChangeCallback } from "./../../component/timePicker"
import { UIExtensionProxy_serializer, UIExtensionProxy } from "./../../component/uiExtensionComponent"
import { CheckBoxConfiguration_serializer, CheckBoxConfiguration, OnCheckboxChangeCallback } from "./../../component/checkbox"
import { DataPanelConfiguration_serializer, DataPanelConfiguration } from "./../../component/dataPanel"
import { BusinessError_serializer } from "./../ohos.base"
import { GaugeConfiguration_serializer, GaugeConfiguration } from "./../../component/gauge"
import { ImageLoadResult_serializer, ImageCompleteCallback, ImageLoadResult } from "./../../component/imageSpan"
import { ImageError_serializer, ImageCompleteEvent_serializer, ImageErrorCallback, ImageError, ImageOnCompleteCallback, ImageCompleteEvent } from "./../../component/image"
import { LoadingProgressConfiguration_serializer, LoadingProgressConfiguration } from "./../../component/loadingProgress"
import { MenuItemConfiguration_serializer, MenuItemConfiguration, OnSelectCallback } from "./../../component/select"
import { CheckBoxGroupConfiguration_serializer, CheckboxGroupResult_serializer, CheckBoxGroupConfiguration, OnCheckboxGroupChangeCallback, CheckboxGroupResult } from "./../../component/checkboxgroup"
import { OnFoldStatusChangeInfo_serializer, HoverEventParam_serializer, OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam } from "./../../component/folderStack"
import { VisibleListContentInfo_serializer, ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo } from "./../../component/list"
import { SubmitEvent_serializer, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback } from "./../../component/textInput"
import { PluginErrorData_serializer, RecordData, PluginErrorCallback, PluginErrorData } from "./../../component/pluginComponent"
import { ProgressConfiguration_serializer, ProgressConfiguration } from "./../../component/progress"
import { RadioConfiguration_serializer, OnRadioChangeCallback, RadioConfiguration } from "./../../component/radio"
import { RatingConfiguration_serializer, OnRatingChangeCallback, RatingConfiguration } from "./../../component/rating"
import { ErrorEvent_serializer, MessageEvents_serializer, Event_serializer, Callback_CreateItem, Callback_Extender_OnFinish, Callback_Extender_OnProgress, Callback_OnDestory_Void, Callback_onMeasureSize_SizeResult, Callback_OnMoveFromTo, Callback_onPlaceChildren_Void, Callback_RangeUpdate, Callback_Size_Void, Callback_StateStylesChange, CustomNodeBuilder, CustomBuilderT_Arkui_Component_Enums_ResponseType, NavExtender_CreateNavDestination, NavExtender_OnUpdateStack, RestrictedWorker_onerror_Callback, ErrorEvent, RestrictedWorker_onexit_Callback, RestrictedWorker_onmessage_Callback, MessageEvents, RouterFinishCallback, WorkerEventListener, Event } from "./../../component/idlize"
import { SliderConfiguration_serializer, SliderChangeMode, SliderConfiguration, SliderTriggerChangeCallback } from "./../../component/slider"
import { TextClockConfiguration_serializer, TextClockConfiguration } from "./../../component/textClock"
import { TextTimerConfiguration_serializer, TextTimerConfiguration, TimerCallback } from "./../../component/textTimer"
import { ToggleConfiguration_serializer, ToggleConfiguration } from "./../../component/toggle"
import { registerApiEventHandler, ResourceHolder, KInt, KStringPtr, wrapSystemCallback, DeserializerBase, SerializerBase, CallbackResource, InteropNativeModule, KPointer, RuntimeType, KSerializerBuffer, NativeBuffer, runtimeType } from "@koalaui/interop"
import { int32, float32, int64 } from "@koalaui/common"
import { CallbackTransformer } from "./../../CallbackTransformer"
import { extractors } from "#handwritten"
import { default as image } from "@ohos.multimedia.image"
import { DrawContext, Size } from "arkui.Graphics"
import { HitTestMode, ResponseType, Edge, ScrollSource } from "./../../component/enums"
import { MarqueeState } from "./../../component/text"
import { CustomBuilder, CustomBuilderT, PageMapBuilder } from "./../../component/builder"
import { RefreshStatus } from "./../../component/refresh"
import { SwipeActionState } from "./../../component/listItem"
import { Resource } from "global.resource"
import { AsyncCallback, ErrorCallback, BusinessError } from "@ohos.base"
import { GetItemMainSizeByIndex } from "./../../component/waterFlow"
import { OnAlphabetIndexerPopupSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerSelectCallback } from "./../../component/alphabetIndexer"
import { OnLinearIndicatorChangeCallback } from "./../../component/linearindicator"
import { OnPickerCallback } from "./../../component/picker"
import { PageTransitionCallback, RouteType } from "./../../component/pageTransition"
import { PasteButtonCallback, PasteButtonOnClickResult } from "./../../component/pasteButton"
import { SaveButtonCallback, SaveButtonOnClickResult } from "./../../component/saveButton"
import { SearchSubmitCallback } from "./../../component/search"
import { SearchValueCallback } from "./../searchOps"
import { TextAreaSubmitCallback } from "./../../component/textArea"
import { TextFieldValueCallback } from "./../textFieldOps"
import { TypeChecker } from "#components"
import { CallbackKind } from "./CallbackKind"
import { ArcScrollIndexHandler } from "@ohos.arkui.ArcList"
export function deserializeAndCallAccessibilityActionInterceptCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityActionInterceptCallback)
    let action : AccessibilityAction = AccessibilityAction.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: AccessibilityActionInterceptResult) => void) = (value: AccessibilityActionInterceptResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -1365174832, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(action)
    continuationResult(_callResult)
}
export function deserializeAndCallAccessibilityCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : AccessibilityHoverEvent = (AccessibilityHoverEvent_serializer.read(thisDeserializer) as AccessibilityHoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallAccessibilityFocusCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityFocusCallback)
    let isFocus : boolean = thisDeserializer.readBoolean()
    _call(isFocus)
}
export function deserializeAndCallAccessibilityTransparentCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityTransparentCallback)
    let event : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    _call(event)
}
export function deserializeAndCallArcScrollIndexHandler(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ArcScrollIndexHandler)
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    let center : int32 = thisDeserializer.readInt32()
    _call(start, end, center)
}
export function deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((result: image.PixelMap) => void))
    let result : image.PixelMap = (image_PixelMap_serializer.read(thisDeserializer) as image.PixelMap)
    _call(result)
}
export function deserializeAndCallAsyncCallback_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AsyncCallback<void>)
    const errTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let errTmpBuf : BusinessError | null = null
    if ((errTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        errTmpBuf = (BusinessError_serializer.read(thisDeserializer) as BusinessError)
    }
    // let err : BusinessError | null = errTmpBuf
    // const dataTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    // //@ts-ignore
    // let dataTmpBuf : void | undefined = undefined
    // if ((dataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
    //     dataTmpBuf = undefined
    // }
    // //@ts-ignore
    // let data : void | undefined = dataTmpBuf
    // _call(err, data)
}
export function deserializeAndCallButtonModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ButtonConfiguration = ButtonConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallButtonTriggerClickCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ButtonTriggerClickCallback)
    let xPos : double = thisDeserializer.readFloat64()
    let yPos : double = thisDeserializer.readFloat64()
    _call(xPos, yPos)
}
export function deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: AccessibilityActionInterceptResult) => void))
    let value : AccessibilityActionInterceptResult = AccessibilityActionInterceptResult.fromValue(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_Area_Area_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((oldValue: Area,newValue: Area) => void))
    let oldValue : Area = Area_serializer.read(thisDeserializer)
    let newValue : Area = Area_serializer.read(thisDeserializer)
    _call(oldValue, newValue)
}
export function deserializeAndCallCallback_Array_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((input: Array<int32>) => void))
    const inputTmpBufLength : int32 = thisDeserializer.readInt32()
    let inputTmpBuf : Array<int32> = new int32[inputTmpBufLength]
    for (let inputTmpBufBufCounterI = 0; inputTmpBufBufCounterI < inputTmpBufLength; inputTmpBufBufCounterI++) {
        inputTmpBuf[inputTmpBufBufCounterI] = thisDeserializer.readInt32()
    }
    let input : Array<int32> = inputTmpBuf
    _call(input)
}
export function deserializeAndCallCallback_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<string>) => void))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<string> = new Array<string>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let value : Array<string> = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TextMenuItem>) => void))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<TextMenuItem> = new Array<TextMenuItem>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let value : Array<TextMenuItem> = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TouchTestInfo>) => TouchResult))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<TouchTestInfo> = new Array<TouchTestInfo>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = TouchTestInfo_serializer.read(thisDeserializer)
    }
    let value : Array<TouchTestInfo> = valueTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: TouchResult) => void) = (value: TouchResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        TouchResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 1943507619, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_AxisEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: AxisEvent) => void))
    let value0 : AxisEvent = (AxisEvent_serializer.read(thisDeserializer) as AxisEvent)
    _call(value0)
}
export function deserializeAndCallCallback_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => boolean))
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call()
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((isHover: boolean,event: HoverEvent) => void))
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallCallback_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: boolean) => void))
    let value0 : boolean = thisDeserializer.readBoolean()
    _call(value0)
}
export function deserializeAndCallCallback_Buffer_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ArrayBuffer) => void))
    let value : ArrayBuffer = (thisDeserializer.readBuffer() as ArrayBuffer)
    _call(value)
}
export function deserializeAndCallCallback_ClickEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    _call(event)
}
export function deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ComputedBarAttribute) => void))
    let value : ComputedBarAttribute = ComputedBarAttribute_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_CopyEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: CopyEvent) => void))
    let value0 : CopyEvent = CopyEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_CreateItem(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_CreateItem)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_CrownEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: CrownEvent) => void))
    let value0 : CrownEvent = CrownEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics))
    let measureInfo : CustomSpanMeasureInfo = CustomSpanMeasureInfo_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: CustomSpanMetrics) => void) = (value: CustomSpanMetrics):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        CustomSpanMetrics_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 1362306791, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(measureInfo)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_CustomSpanMetrics_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomSpanMetrics) => void))
    let value : CustomSpanMetrics = CustomSpanMetrics_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_CutEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: CutEvent) => void))
    let value0 : CutEvent = CutEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_Date_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Date) => void))
    let value0 : Date = new Date(thisDeserializer.readInt64())
    _call(value0)
}
export function deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DeleteValue) => boolean))
    let value0 : DeleteValue = DeleteValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_DeleteValue_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DeleteValue) => void))
    let value0 : DeleteValue = DeleteValue_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DismissContentCoverAction) => void))
    let value0 : DismissContentCoverAction = DismissContentCoverAction_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DismissDialogAction) => void))
    let value0 : DismissDialogAction = (DismissDialogAction_serializer.read(thisDeserializer) as DismissDialogAction)
    _call(value0)
}
export function deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DismissPopupAction) => void))
    let value0 : DismissPopupAction = (DismissPopupAction_serializer.read(thisDeserializer) as DismissPopupAction)
    _call(value0)
}
export function deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: DismissSheetAction) => void))
    let value0 : DismissSheetAction = DismissSheetAction_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_DragEvent_Opt_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent,extraParams?: string) => void))
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    _call(event, extraParams)
}
export function deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((context: DrawContext,drawInfo: CustomSpanDrawInfo) => void))
    let context : DrawContext = (DrawContext_serializer.read(thisDeserializer) as DrawContext)
    let drawInfo : CustomSpanDrawInfo = CustomSpanDrawInfo_serializer.read(thisDeserializer)
    _call(context, drawInfo)
}
export function deserializeAndCallCallback_DrawContext_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((drawContext: DrawContext) => void))
    let drawContext : DrawContext = (DrawContext_serializer.read(thisDeserializer) as DrawContext)
    _call(drawContext)
}
export function deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: EditableTextChangeValue) => boolean))
    let value0 : EditableTextChangeValue = EditableTextChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_ErrorInformation_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: ErrorInformation) => void))
    let value0 : ErrorInformation = ErrorInformation_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_Extender_OnFinish(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnFinish)
    _call()
}
export function deserializeAndCallCallback_Extender_OnProgress(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnProgress)
    let value : float = thisDeserializer.readFloat32()
    _call(value)
}
export function deserializeAndCallCallback_F64_F64_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((totalOffsetX: double,totalOffsetY: double) => void))
    let totalOffsetX : double = thisDeserializer.readFloat64()
    let totalOffsetY : double = thisDeserializer.readFloat64()
    _call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallCallback_F64_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((offset: double) => void))
    let offset : double = thisDeserializer.readFloat64()
    _call(offset)
}
export function deserializeAndCallCallback_F64_SliderChangeMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: double,mode: SliderChangeMode) => void))
    let value : double = thisDeserializer.readFloat64()
    let mode : SliderChangeMode = SliderChangeMode.fromValue(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: FocusAxisEvent) => void))
    let value0 : FocusAxisEvent = (FocusAxisEvent_serializer.read(thisDeserializer) as FocusAxisEvent)
    _call(value0)
}
export function deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: FormCallbackInfo) => void))
    let value0 : FormCallbackInfo = FormCallbackInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: FullscreenInfo) => void))
    let value0 : FullscreenInfo = FullscreenInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_GestureEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: GestureEvent) => void))
    let value0 : GestureEvent = (GestureEvent_serializer.read(thisDeserializer) as GestureEvent)
    _call(value0)
}
export function deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult))
    let gestureInfo : GestureInfo = GestureInfo_serializer.read(thisDeserializer)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: GestureJudgeResult) => void) = (value: GestureJudgeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -684588584, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(gestureInfo, event)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: GestureJudgeResult) => void))
    let value : GestureJudgeResult = GestureJudgeResult.fromValue(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: GestureRecognizer) => void))
    let value : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    _call(value)
}
export function deserializeAndCallCallback_HitTestMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: HitTestMode) => void))
    let value : HitTestMode = HitTestMode.fromValue(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_HoverEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: HoverEvent) => void))
    let value0 : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    _call(value0)
}
export function deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: int32,offset: double) => ComputedBarAttribute))
    let index : int32 = thisDeserializer.readInt32()
    let offset : double = thisDeserializer.readFloat64()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: ComputedBarAttribute) => void) = (value: ComputedBarAttribute):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        ComputedBarAttribute_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, -1270343661, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index, offset)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_I32_I32_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: int32,to: int32) => boolean))
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(from, to)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_I32_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((start: int32,end: int32,center: int32) => void))
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    let center : int32 = thisDeserializer.readInt32()
    _call(start, end, center)
}
export function deserializeAndCallCallback_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((first: int32,last: int32) => void))
    let first : int32 = thisDeserializer.readInt32()
    let last : int32 = thisDeserializer.readInt32()
    _call(first, last)
}
export function deserializeAndCallCallback_I32_Tuple_I32_I32(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: int32) => [ int32, int32 ]))
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: [ int32, int32 ]) => void) = (value: [ int32, int32 ]):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        const value_0  = value[0];
        continuationBufferBufArgsSerializer.writeInt32(value_0);
        const value_1  = value[1];
        continuationBufferBufArgsSerializer.writeInt32(value_1);
        InteropNativeModule._CallCallbackSync(10, -1321460777, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: int32) => [ int32, int32, int32, int32 ]))
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: [ int32, int32, int32, int32 ]) => void) = (value: [ int32, int32, int32, int32 ]):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        const value_0  = value[0];
        continuationBufferBufArgsSerializer.writeInt32(value_0);
        const value_1  = value[1];
        continuationBufferBufArgsSerializer.writeInt32(value_1);
        const value_2  = value[2];
        continuationBufferBufArgsSerializer.writeInt32(value_2);
        const value_3  = value[3];
        continuationBufferBufArgsSerializer.writeInt32(value_3);
        InteropNativeModule._CallCallbackSync(10, 1381083927, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: int32) => void))
    let value0 : int32 = thisDeserializer.readInt32()
    _call(value0)
}
export function deserializeAndCallCallback_I64_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: int64) => void))
    let value : int64 = thisDeserializer.readInt64()
    _call(value)
}
export function deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: InsertValue) => boolean))
    let value0 : InsertValue = InsertValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_InsertValue_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: InsertValue) => void))
    let value0 : InsertValue = InsertValue_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    let insertIndex : int32 = thisDeserializer.readInt32()
    let isSuccess : boolean = thisDeserializer.readBoolean()
    _call(event, itemIndex, insertIndex, isSuccess)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    let insertIndex : int32 = thisDeserializer.readInt32()
    _call(event, itemIndex, insertIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: int32) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    _call(event, itemIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: KeyEvent) => boolean))
    let value0 : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_KeyEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: KeyEvent) => void))
    let event : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    _call(event)
}
export function deserializeAndCallCallback_Map_String_RecordData_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Map<string, RecordData>) => void))
    const value0TmpBufSizeVar : int32 = thisDeserializer.readInt32()
    let value0TmpBuf : Map<string, RecordData> = new Map<string, RecordData>()
    // TODO: TS map resize
    for (let value0TmpBufIVar = 0; value0TmpBufIVar < value0TmpBufSizeVar; value0TmpBufIVar++) {
        const value0TmpBufKeyVar : string = (thisDeserializer.readString() as string)
        const value0TmpBufValueVarTempBuf_runtimeType  = thisDeserializer.readInt8().toInt()
        let value0TmpBufValueVarTempBuf : Object | null | undefined = undefined
        if ((value0TmpBufValueVarTempBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            value0TmpBufValueVarTempBuf = (thisDeserializer.readObject() as object)
        }
        const value0TmpBufValueVar : RecordData = value0TmpBufValueVarTempBuf
        value0TmpBuf.set(value0TmpBufKeyVar, value0TmpBufValueVar)
    }
    let value0 : Map<string, RecordData> = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_MarqueeState_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: MarqueeState) => void))
    let value0 : MarqueeState = MarqueeState.fromValue(thisDeserializer.readInt32())
    _call(value0)
}
export function deserializeAndCallCallback_MouseEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: MouseEvent) => void))
    let event : MouseEvent = (MouseEvent_serializer.read(thisDeserializer) as MouseEvent)
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedDataInfo) => void))
    let event : NativeEmbedDataInfo = NativeEmbedDataInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedTouchInfo) => void))
    let event : NativeEmbedTouchInfo = NativeEmbedTouchInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallCallback_NativeXComponentPointer_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: NativeXComponentPointer) => void))
    let value0 : NativeXComponentPointer = thisDeserializer.readInt64()
    _call(value0)
}
export function deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: NavDestinationActiveReason) => void))
    let value0 : NavDestinationActiveReason = NavDestinationActiveReason.fromValue(thisDeserializer.readInt32())
    _call(value0)
}
export function deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: NavDestinationContext) => void))
    let value0 : NavDestinationContext = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    _call(value0)
}
export function deserializeAndCallCallback_NavigationMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((mode: NavigationMode) => void))
    let mode : NavigationMode = NavigationMode.fromValue(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((titleMode: NavigationTitleMode) => void))
    let titleMode : NavigationTitleMode = NavigationTitleMode.fromValue(thisDeserializer.readInt32())
    _call(titleMode)
}
export function deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((transitionProxy: NavigationTransitionProxy) => void))
    let transitionProxy : NavigationTransitionProxy = (NavigationTransitionProxy_serializer.read(thisDeserializer) as NavigationTransitionProxy)
    _call(transitionProxy)
}
export function deserializeAndCallCallback_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((prevIndex: number,index: number) => void))
    let prevIndex : number = (thisDeserializer.readNumber() as number)
    let index : number = (thisDeserializer.readNumber() as number)
    _call(prevIndex, index)
}
export function deserializeAndCallCallback_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: number) => void))
    let value : number = (thisDeserializer.readNumber() as number)
    _call(value)
}
export function deserializeAndCallCallback_Object_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Object) => void))
    let value0 : Object = (thisDeserializer.readObject() as object)
    _call(value0)
}
export function deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnAlertEvent) => boolean))
    let value0 : OnAlertEvent = OnAlertEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnAudioStateChangedEvent) => void))
    let value0 : OnAudioStateChangedEvent = OnAudioStateChangedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnBeforeUnloadEvent) => boolean))
    let value0 : OnBeforeUnloadEvent = OnBeforeUnloadEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnClientAuthenticationEvent) => void))
    let value0 : OnClientAuthenticationEvent = OnClientAuthenticationEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnConfirmEvent) => boolean))
    let value0 : OnConfirmEvent = OnConfirmEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnConsoleEvent) => boolean))
    let value0 : OnConsoleEvent = OnConsoleEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnContextMenuShowEvent) => boolean))
    let value0 : OnContextMenuShowEvent = OnContextMenuShowEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnDataResubmittedEvent) => void))
    let value0 : OnDataResubmittedEvent = OnDataResubmittedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnDestory_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_OnDestory_Void)
    let nodeId : int64 = thisDeserializer.readInt64()
    _call(nodeId)
}
export function deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnDownloadStartEvent) => void))
    let value0 : OnDownloadStartEvent = OnDownloadStartEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnErrorReceiveEvent) => void))
    let value0 : OnErrorReceiveEvent = OnErrorReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnFaviconReceivedEvent) => void))
    let value0 : OnFaviconReceivedEvent = OnFaviconReceivedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnFirstContentfulPaintEvent) => void))
    let value0 : OnFirstContentfulPaintEvent = OnFirstContentfulPaintEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnGeolocationShowEvent) => void))
    let value0 : OnGeolocationShowEvent = OnGeolocationShowEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnHttpAuthRequestEvent) => boolean))
    let value0 : OnHttpAuthRequestEvent = OnHttpAuthRequestEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnHttpErrorReceiveEvent) => void))
    let value0 : OnHttpErrorReceiveEvent = OnHttpErrorReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnLoadFinishedEvent) => void))
    let value0 : OnLoadFinishedEvent = OnLoadFinishedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnLoadInterceptEvent) => boolean))
    let value0 : OnLoadInterceptEvent = OnLoadInterceptEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnLoadStartedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnLoadStartedEvent) => void))
    let value0 : OnLoadStartedEvent = OnLoadStartedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_onMeasureSize_SizeResult)
    let selfLayoutInfo : GeometryInfo = GeometryInfo_serializer.read(thisDeserializer)
    const childrenTmpBufLength : int32 = thisDeserializer.readInt32()
    let childrenTmpBuf : Array<Measurable> = new Array<Measurable>(childrenTmpBufLength)
    for (let childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf[childrenTmpBufBufCounterI] = (Measurable_serializer.read(thisDeserializer) as Measurable)
    }
    let children : Array<Measurable> = childrenTmpBuf
    let constraint : ConstraintSizeOptions = ConstraintSizeOptions_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: SizeResult) => void) = (value: SizeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        SizeResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 1318865891, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(selfLayoutInfo, children, constraint)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnMoveFromTo(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_OnMoveFromTo)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    _call(from, to)
}
export function deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnOverScrollEvent) => void))
    let value0 : OnOverScrollEvent = OnOverScrollEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPageBeginEvent) => void))
    let value0 : OnPageBeginEvent = OnPageBeginEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPageEndEvent) => void))
    let value0 : OnPageEndEvent = OnPageEndEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPageVisibleEvent) => void))
    let value0 : OnPageVisibleEvent = OnPageVisibleEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPdfLoadEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPdfLoadEvent) => void))
    let value0 : OnPdfLoadEvent = OnPdfLoadEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPdfScrollEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPdfScrollEvent) => void))
    let value0 : OnPdfScrollEvent = OnPdfScrollEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPermissionRequestEvent) => void))
    let value0 : OnPermissionRequestEvent = OnPermissionRequestEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_onPlaceChildren_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_onPlaceChildren_Void)
    let selfLayoutInfo : GeometryInfo = GeometryInfo_serializer.read(thisDeserializer)
    const childrenTmpBufLength : int32 = thisDeserializer.readInt32()
    let childrenTmpBuf : Array<Layoutable> = new Array<Layoutable>(childrenTmpBufLength)
    for (let childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf[childrenTmpBufBufCounterI] = (Layoutable_serializer.read(thisDeserializer) as Layoutable)
    }
    let children : Array<Layoutable> = childrenTmpBuf
    let constraint : ConstraintSizeOptions = ConstraintSizeOptions_serializer.read(thisDeserializer)
    _call(selfLayoutInfo, children, constraint)
}
export function deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnProgressChangeEvent) => void))
    let value0 : OnProgressChangeEvent = OnProgressChangeEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnPromptEvent) => boolean))
    let value0 : OnPromptEvent = OnPromptEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnRefreshAccessedHistoryEvent) => void))
    let value0 : OnRefreshAccessedHistoryEvent = OnRefreshAccessedHistoryEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnRenderExitedEvent) => void))
    let value0 : OnRenderExitedEvent = OnRenderExitedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnResourceLoadEvent) => void))
    let value0 : OnResourceLoadEvent = OnResourceLoadEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnScaleChangeEvent) => void))
    let value0 : OnScaleChangeEvent = OnScaleChangeEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnScreenCaptureRequestEvent) => void))
    let value0 : OnScreenCaptureRequestEvent = OnScreenCaptureRequestEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnScrollEvent) => void))
    let value0 : OnScrollEvent = OnScrollEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: OnScrollFrameBeginHandlerResult) => void))
    let value : OnScrollFrameBeginHandlerResult = OnScrollFrameBeginHandlerResult_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnSearchResultReceiveEvent) => void))
    let value0 : OnSearchResultReceiveEvent = OnSearchResultReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnShowFileSelectorEvent) => boolean))
    let value0 : OnShowFileSelectorEvent = OnShowFileSelectorEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnSslErrorEventReceiveEvent) => void))
    let value0 : OnSslErrorEventReceiveEvent = OnSslErrorEventReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnTitleReceiveEvent) => void))
    let value0 : OnTitleReceiveEvent = OnTitleReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnTouchIconUrlReceivedEvent) => void))
    let value0 : OnTouchIconUrlReceivedEvent = OnTouchIconUrlReceivedEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnWindowNewEvent) => void))
    let value0 : OnWindowNewEvent = OnWindowNewEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<NavDestinationTransition> | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : Array<NavDestinationTransition> | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const valueTmpBuf_Length : int32 = thisDeserializer.readInt32()
        let valueTmpBuf_ : Array<NavDestinationTransition> = new Array<NavDestinationTransition>(valueTmpBuf_Length)
        for (let valueTmpBuf_BufCounterI = 0; valueTmpBuf_BufCounterI < valueTmpBuf_Length; valueTmpBuf_BufCounterI++) {
            valueTmpBuf_[valueTmpBuf_BufCounterI] = NavDestinationTransition_serializer.read(thisDeserializer)
        }
        valueTmpBuf = valueTmpBuf_
    }
    let value : Array<NavDestinationTransition> | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((error?: Array<string> | undefined) => void))
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let errorTmpBuf : Array<string> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBuf_Length : int32 = thisDeserializer.readInt32()
        let errorTmpBuf_ : Array<string> = new Array<string>(errorTmpBuf_Length)
        for (let errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_[errorTmpBuf_BufCounterI] = (thisDeserializer.readString() as string)
        }
        errorTmpBuf = errorTmpBuf_
    }
    let error : Array<string> | undefined = errorTmpBuf
    _call(error)
}
export function deserializeAndCallCallback_Opt_CustomBuilder_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : CustomBuilder | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const valueTmpBuf_BufResource : CallbackResource = thisDeserializer.readCallbackResource()
        const valueTmpBuf_BufCall : KPointer = thisDeserializer.readPointer()
        const valueTmpBuf_BufCallSync : KPointer = thisDeserializer.readPointer()
        valueTmpBuf = ():void => {
            const valueTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
            valueTmpBuf_BufArgsSerializer.writeInt32(valueTmpBuf_BufResource.resourceId);
            valueTmpBuf_BufArgsSerializer.writePointer(valueTmpBuf_BufCall);
            valueTmpBuf_BufArgsSerializer.writePointer(valueTmpBuf_BufCallSync);
            InteropNativeModule._CallCallbackSync(10, 737226752, valueTmpBuf_BufArgsSerializer.asBuffer(), valueTmpBuf_BufArgsSerializer.length());
            valueTmpBuf_BufArgsSerializer.release();
            return;
        }
    }
    let value : CustomBuilder | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: NavigationAnimatedTransition | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : NavigationAnimatedTransition | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = NavigationAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : NavigationAnimatedTransition | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: OffsetResult | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : OffsetResult | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = OffsetResult_serializer.read(thisDeserializer)
    }
    let value : OffsetResult | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ScrollResult | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : ScrollResult | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (ScrollResult_serializer.read(thisDeserializer) as ScrollResult)
    }
    let value : ScrollResult | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: StyledString | undefined,error?: Array<string> | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : StyledString | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (StyledString_serializer.read(thisDeserializer) as StyledString)
    }
    let value : StyledString | undefined = valueTmpBuf
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let errorTmpBuf : Array<string> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBuf_Length : int32 = thisDeserializer.readInt32()
        let errorTmpBuf_ : Array<string> = new Array<string>(errorTmpBuf_Length)
        for (let errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_[errorTmpBuf_BufCounterI] = (thisDeserializer.readString() as string)
        }
        errorTmpBuf = errorTmpBuf_
    }
    let error : Array<string> | undefined = errorTmpBuf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TabContentAnimatedTransition | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : TabContentAnimatedTransition | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = TabContentAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : TabContentAnimatedTransition | undefined = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WebResourceResponse | null) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let valueTmpBuf : WebResourceResponse | null = null
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (WebResourceResponse_serializer.read(thisDeserializer) as WebResourceResponse)
    }
    let value : WebResourceResponse | null = valueTmpBuf
    _call(value)
}
export function deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: PlaybackInfo) => void))
    let value0 : PlaybackInfo = PlaybackInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_Pointer_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: KPointer) => void))
    let value : KPointer = thisDeserializer.readPointer()
    _call(value)
}
export function deserializeAndCallCallback_PopInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: PopInfo) => void))
    let value0 : PopInfo = PopInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: PreDragStatus) => void))
    let value0 : PreDragStatus = PreDragStatus.fromValue(thisDeserializer.readInt32())
    _call(value0)
}
export function deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: PreparedInfo) => void))
    let value0 : PreparedInfo = PreparedInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_RangeUpdate(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_RangeUpdate)
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    let cacheStart : int32 = thisDeserializer.readInt32()
    let cacheEnd : int32 = thisDeserializer.readInt32()
    let isLoop : boolean = thisDeserializer.readBoolean()
    _call(start, end, cacheStart, cacheEnd, isLoop)
}
export function deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: RefreshStatus) => void))
    let state : RefreshStatus = RefreshStatus.fromValue(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorChangeValue) => boolean))
    let value0 : RichEditorChangeValue = RichEditorChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorDeleteValue) => boolean))
    let value0 : RichEditorDeleteValue = RichEditorDeleteValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorInsertValue) => boolean))
    let value0 : RichEditorInsertValue = RichEditorInsertValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorRange) => void))
    let value0 : RichEditorRange = RichEditorRange_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorSelection) => void))
    let value0 : RichEditorSelection = RichEditorSelection_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorTextSpanResult) => void))
    let value0 : RichEditorTextSpanResult = RichEditorTextSpanResult_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_RouterCallbackInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RouterCallbackInfo) => void))
    let value0 : RouterCallbackInfo = RouterCallbackInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((sheetDismiss: SheetDismiss) => void))
    let sheetDismiss : SheetDismiss = SheetDismiss_serializer.read(thisDeserializer)
    _call(sheetDismiss)
}
export function deserializeAndCallCallback_SheetType_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: SheetType) => void))
    let value0 : SheetType = SheetType.fromValue(thisDeserializer.readInt32())
    _call(value0)
}
export function deserializeAndCallCallback_Size_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_Size_Void)
    let size : Size = Size_serializer.read(thisDeserializer)
    _call(size)
}
export function deserializeAndCallCallback_SizeResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: SizeResult) => void))
    let value : SizeResult = SizeResult_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: SpringBackAction) => void))
    let value0 : SpringBackAction = (SpringBackAction_serializer.read(thisDeserializer) as SpringBackAction)
    _call(value0)
}
export function deserializeAndCallCallback_StateStylesChange(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_StateStylesChange)
    let currentState : int32 = thisDeserializer.readInt32()
    _call(currentState)
}
export function deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: string,event: PasteEvent) => void))
    let value : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = PasteEvent_serializer.read(thisDeserializer)
    _call(value, event)
}
export function deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((surfaceId: string,rect: SurfaceRect) => void))
    let surfaceId : string = (thisDeserializer.readString() as string)
    let rect : SurfaceRect = SurfaceRect_serializer.read(thisDeserializer)
    _call(surfaceId, rect)
}
export function deserializeAndCallCallback_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((breakpoints: string) => void))
    let breakpoints : string = (thisDeserializer.readString() as string)
    _call(breakpoints)
}
export function deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: StyledStringChangeValue) => boolean))
    let value0 : StyledStringChangeValue = StyledStringChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: UserDataSpan) => void))
    let value : UserDataSpan = (thisDeserializer.readObject() as UserDataSpan)
    _call(value)
}
export function deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: SwipeActionState) => void))
    let state : SwipeActionState = SwipeActionState.fromValue(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: SwiperContentTransitionProxy) => void))
    let value0 : SwiperContentTransitionProxy = (SwiperContentTransitionProxy_serializer.read(thisDeserializer) as SwiperContentTransitionProxy)
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Arkui_Component_Units_Length(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Length) => void))
    const value0TmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let value0TmpBuf : string | number | Resource | undefined
    if (value0TmpBufUnionSelector == (0).toChar()) {
        value0TmpBuf = (thisDeserializer.readString() as string)
    } else if (value0TmpBufUnionSelector == (1).toChar()) {
        value0TmpBuf = (thisDeserializer.readNumber() as number)
    } else if (value0TmpBufUnionSelector == (2).toChar()) {
        value0TmpBuf = Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error("One of the branches for value0TmpBuf has to be chosen through deserialisation.")
    }
    let value0 : Length = (value0TmpBuf as string | number | Resource)
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Arkui_Component_Units_ResourceStr(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: ResourceStr) => void))
    const value0TmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let value0TmpBuf : string | Resource | undefined
    if (value0TmpBufUnionSelector == (0).toChar()) {
        value0TmpBuf = (thisDeserializer.readString() as string)
    } else if (value0TmpBufUnionSelector == (1).toChar()) {
        value0TmpBuf = Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error("One of the branches for value0TmpBuf has to be chosen through deserialisation.")
    }
    let value0 : ResourceStr = (value0TmpBuf as string | Resource)
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Array<ResourceStr>) => void))
    const value0TmpBufLength : int32 = thisDeserializer.readInt32()
    let value0TmpBuf : Array<ResourceStr> = new Array<ResourceStr>(value0TmpBufLength)
    for (let value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        const value0TmpBufTempBufUnionSelector : int32 = thisDeserializer.readInt8()
        let value0TmpBufTempBuf : string | Resource | undefined
        if (value0TmpBufTempBufUnionSelector == (0).toChar()) {
            value0TmpBufTempBuf = (thisDeserializer.readString() as string)
        } else if (value0TmpBufTempBufUnionSelector == (1).toChar()) {
            value0TmpBufTempBuf = Resource_serializer.read(thisDeserializer)
        } else {
            throw new Error("One of the branches for value0TmpBufTempBuf has to be chosen through deserialisation.")
        }
        value0TmpBuf[value0TmpBufBufCounterI] = (value0TmpBufTempBuf as string | Resource)
    }
    let value0 : Array<ResourceStr> = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Array_Global_Resource_Resource(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Array<Resource>) => void))
    const value0TmpBufLength : int32 = thisDeserializer.readInt32()
    let value0TmpBuf : Array<Resource> = new Array<Resource>(value0TmpBufLength)
    for (let value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf[value0TmpBufBufCounterI] = Resource_serializer.read(thisDeserializer)
    }
    let value0 : Array<Resource> = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Array_I32(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Array<int32>) => void))
    const value0TmpBufLength : int32 = thisDeserializer.readInt32()
    let value0TmpBuf : Array<int32> = new int32[value0TmpBufLength]
    for (let value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf[value0TmpBufBufCounterI] = thisDeserializer.readInt32()
    }
    let value0 : Array<int32> = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Array_String(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Array<string>) => void))
    const value0TmpBufLength : int32 = thisDeserializer.readInt32()
    let value0TmpBuf : Array<string> = new Array<string>(value0TmpBufLength)
    for (let value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf[value0TmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let value0 : Array<string> = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: boolean) => void))
    let value0 : boolean = thisDeserializer.readBoolean()
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Date(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Date) => void))
    let value0 : Date = new Date(thisDeserializer.readInt64())
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_F64(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: double) => void))
    let value0 : double = thisDeserializer.readFloat64()
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Global_Resource_Resource(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Resource) => void))
    let value0 : Resource = Resource_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_I32(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: int32) => void))
    let value0 : int32 = thisDeserializer.readInt32()
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_Number(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: number) => void))
    let value0 : number = (thisDeserializer.readNumber() as number)
    _call(value0)
}
export function deserializeAndCallCallback_T_Void_String(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: string) => void))
    let value0 : string = (thisDeserializer.readString() as string)
    _call(value0)
}
export function deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: TabContentTransitionProxy) => void))
    let value0 : TabContentTransitionProxy = (TabContentTransitionProxy_serializer.read(thisDeserializer) as TabContentTransitionProxy)
    _call(value0)
}
export function deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: TerminationInfo) => void))
    let value0 : TerminationInfo = TerminationInfo_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TextPickerResult) => void))
    let value : TextPickerResult = TextPickerResult_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_TextRange_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: TextRange) => void))
    let value0 : TextRange = TextRange_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: TimePickerResult) => void))
    let value0 : TimePickerResult = TimePickerResult_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: TouchEvent) => HitTestMode))
    let value0 : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: HitTestMode) => void) = (value: HitTestMode):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -1755111025, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallCallback_TouchEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: TouchEvent) => void))
    let event : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    _call(event)
}
export function deserializeAndCallCallback_TouchResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TouchResult) => void))
    let value : TouchResult = TouchResult_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ int32, int32, int32, int32 ]) => void))
    const valueTmpBufValue0 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue1 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue2 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue3 : int32 = thisDeserializer.readInt32()
    let value : [ int32, int32, int32, int32 ] = ([valueTmpBufValue0, valueTmpBufValue1, valueTmpBufValue2, valueTmpBufValue3] as [ int32, int32, int32, int32 ])
    _call(value)
}
export function deserializeAndCallCallback_Tuple_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ int32, int32 ]) => void))
    const valueTmpBufValue0 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue1 : int32 = thisDeserializer.readInt32()
    let value : [ int32, int32 ] = ([valueTmpBufValue0, valueTmpBufValue1] as [ int32, int32 ])
    _call(value)
}
export function deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: UIExtensionProxy) => void))
    let value0 : UIExtensionProxy = (UIExtensionProxy_serializer.read(thisDeserializer) as UIExtensionProxy)
    _call(value0)
}
export function deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder | DragItemInfo) => void))
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : CustomBuilder | DragItemInfo | undefined
    if (valueTmpBufUnionSelector == (0).toChar()) {
        const valueTmpBufBufUBufResource : CallbackResource = thisDeserializer.readCallbackResource()
        const valueTmpBufBufUBufCall : KPointer = thisDeserializer.readPointer()
        const valueTmpBufBufUBufCallSync : KPointer = thisDeserializer.readPointer()
        valueTmpBuf = ():void => {
            const valueTmpBufBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
            valueTmpBufBufUBufArgsSerializer.writeInt32(valueTmpBufBufUBufResource.resourceId);
            valueTmpBufBufUBufArgsSerializer.writePointer(valueTmpBufBufUBufCall);
            valueTmpBufBufUBufArgsSerializer.writePointer(valueTmpBufBufUBufCallSync);
            InteropNativeModule._CallCallbackSync(10, 737226752, valueTmpBufBufUBufArgsSerializer.asBuffer(), valueTmpBufBufUBufArgsSerializer.length());
            valueTmpBufBufUBufArgsSerializer.release();
            return;
        }
    } else if (valueTmpBufUnionSelector == (1).toChar()) {
        valueTmpBuf = DragItemInfo_serializer.read(thisDeserializer)
    } else {
        throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
    }
    let value : CustomBuilder | DragItemInfo = (valueTmpBuf as CustomBuilder | DragItemInfo)
    _call(value)
}
export function deserializeAndCallCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Object | null | undefined) => void))
    const value0TmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value0TmpBuf : Object | null | undefined = undefined
    if ((value0TmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        value0TmpBuf = (thisDeserializer.readObject() as object)
    }
    let value0 : Object | null | undefined = value0TmpBuf
    _call(value0)
}
export function deserializeAndCallCallback_VisibilityChangeReason_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: VisibilityChangeReason) => void))
    let value0 : VisibilityChangeReason = VisibilityChangeReason.fromValue(thisDeserializer.readInt32())
    _call(value0)
}
export function deserializeAndCallCallback_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => void))
    _call()
}
export function deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WebKeyboardOptions) => void))
    let value : WebKeyboardOptions = WebKeyboardOptions_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallCheckBoxGroupModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: CheckBoxGroupConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : CheckBoxGroupConfiguration = (CheckBoxGroupConfiguration_serializer.read(thisDeserializer) as CheckBoxGroupConfiguration)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallCheckBoxModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : CheckBoxConfiguration = CheckBoxConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallContentDidScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentDidScrollCallback)
    let selectedIndex : int32 = thisDeserializer.readInt32()
    let index : int32 = thisDeserializer.readInt32()
    let position : double = thisDeserializer.readFloat64()
    let mainAxisLength : double = thisDeserializer.readFloat64()
    _call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallContentWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentWillScrollCallback)
    let result : SwiperContentWillScrollResult = SwiperContentWillScrollResult_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(result)
    continuationResult(_callResult)
}
export function deserializeAndCallCustomBuilderT_Arkui_Component_Enums_ResponseType(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CustomBuilderT_Arkui_Component_Enums_ResponseType)
    let t : ResponseType = ResponseType.fromValue(thisDeserializer.readInt32())
    let parentNode : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(t, parentNode)
    continuationResult(_callResult)
}
export function deserializeAndCallCustomBuilderT_I32(thisDeserializer: DeserializerBase): void {
    // const _resourceId : int32 = thisDeserializer.readInt32()
    // const _call  = (ResourceHolder.instance().get(_resourceId) as CustomBuilderT<int32>)
    // let t : int32 = thisDeserializer.readInt32()
    // _call(t)
}
export function deserializeAndCallCustomNodeBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CustomNodeBuilder)
    let parentNode : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode)
    continuationResult(_callResult)
}
export function deserializeAndCallDataPanelModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : DataPanelConfiguration = DataPanelConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallEditableTextOnChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as EditableTextOnChangeCallback)
    let value : string = (thisDeserializer.readString() as string)
    const previewTextTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let previewTextTmpBuf : PreviewText | undefined = undefined
    if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        previewTextTmpBuf = PreviewText_serializer.read(thisDeserializer)
    }
    let previewText : PreviewText | undefined = previewTextTmpBuf
    const optionsTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let optionsTmpBuf : TextChangeOptions | undefined = undefined
    if ((optionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        optionsTmpBuf = TextChangeOptions_serializer.read(thisDeserializer)
    }
    let options : TextChangeOptions | undefined = optionsTmpBuf
    _call(value, previewText, options)
}
export function deserializeAndCallErrorCallback_Ohos_Base_BusinessError(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ErrorCallback<BusinessError>)
    let err : BusinessError = (BusinessError_serializer.read(thisDeserializer) as BusinessError)
    _call(err)
}
export function deserializeAndCallGaugeModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: GaugeConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : GaugeConfiguration = GaugeConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GestureRecognizerJudgeBeginCallback)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    let current : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    const recognizersTmpBufLength : int32 = thisDeserializer.readInt32()
    let recognizersTmpBuf : Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizersTmpBufLength)
    for (let recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength; recognizersTmpBufBufCounterI++) {
        recognizersTmpBuf[recognizersTmpBufBufCounterI] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let recognizers : Array<GestureRecognizer> = recognizersTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: GestureJudgeResult) => void) = (value: GestureJudgeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -684588584, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(event, current, recognizers)
    continuationResult(_callResult)
}
export function deserializeAndCallGetItemMainSizeByIndex(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GetItemMainSizeByIndex)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((offset: double) => void) = (offset: double):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeFloat64(offset);
        InteropNativeModule._CallCallbackSync(10, -949162837, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallHoverCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as HoverCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallImageCompleteCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ImageCompleteCallback)
    let result : ImageLoadResult = ImageLoadResult_serializer.read(thisDeserializer)
    _call(result)
}
export function deserializeAndCallImageErrorCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ImageErrorCallback)
    let error : ImageError = ImageError_serializer.read(thisDeserializer)
    _call(error)
}
export function deserializeAndCallImageOnCompleteCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ImageOnCompleteCallback)
    const loadEventTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let loadEventTmpBuf : ImageCompleteEvent | undefined = undefined
    if ((loadEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        loadEventTmpBuf = ImageCompleteEvent_serializer.read(thisDeserializer)
    }
    let loadEvent : ImageCompleteEvent | undefined = loadEventTmpBuf
    _call(loadEvent)
}
export function deserializeAndCallInterceptionModeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionModeCallback)
    let mode : NavigationMode = NavigationMode.fromValue(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallInterceptionShowCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionShowCallback)
    const fromTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let fromTmpBuf : NavDestinationContext | NavBar | undefined
    if (fromTmpBufUnionSelector == (0).toChar()) {
        fromTmpBuf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    } else if (fromTmpBufUnionSelector == (1).toChar()) {
        fromTmpBuf = (thisDeserializer.readString() as string)
    } else {
        throw new Error("One of the branches for fromTmpBuf has to be chosen through deserialisation.")
    }
    let from : NavDestinationContext | NavBar = (fromTmpBuf as NavDestinationContext | NavBar)
    const toTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let toTmpBuf : NavDestinationContext | NavBar | undefined
    if (toTmpBufUnionSelector == (0).toChar()) {
        toTmpBuf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    } else if (toTmpBufUnionSelector == (1).toChar()) {
        toTmpBuf = (thisDeserializer.readString() as string)
    } else {
        throw new Error("One of the branches for toTmpBuf has to be chosen through deserialisation.")
    }
    let to : NavDestinationContext | NavBar = (toTmpBuf as NavDestinationContext | NavBar)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    let isAnimated : boolean = thisDeserializer.readBoolean()
    _call(from, to, operation, isAnimated)
}
export function deserializeAndCallLoadingProgressModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : LoadingProgressConfiguration = LoadingProgressConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallMenuCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuCallback)
    let start : int32 = (thisDeserializer.readInt32() as int32)
    let end : int32 = (thisDeserializer.readInt32() as int32)
    _call(start, end)
}
export function deserializeAndCallMenuItemModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : MenuItemConfiguration = (MenuItemConfiguration_serializer.read(thisDeserializer) as MenuItemConfiguration)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallMenuOnAppearCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuOnAppearCallback)
    let start : int32 = (thisDeserializer.readInt32() as int32)
    let end : int32 = (thisDeserializer.readInt32() as int32)
    _call(start, end)
}
export function deserializeAndCallModifierKeyStateGetter(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ModifierKeyStateGetter)
    const keysTmpBufLength : int32 = thisDeserializer.readInt32()
    let keysTmpBuf : Array<string> = new Array<string>(keysTmpBufLength)
    for (let keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++) {
        keysTmpBuf[keysTmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let keys : Array<string> = keysTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(keys)
    continuationResult(_callResult)
}
export function deserializeAndCallMouseInfoCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MouseInfoCallback)
    let event : NativeEmbedMouseInfo = NativeEmbedMouseInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavDestinationTransitionDelegate)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    let isEnter : boolean = thisDeserializer.readBoolean()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: Array<NavDestinationTransition> | undefined) => void) = (value?: Array<NavDestinationTransition> | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            continuationBufferBufArgsSerializer.writeInt32((valueTmpValue.length).toInt());
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : NavDestinationTransition = valueTmpValue[valueTmpValueCounterI];
                NavDestinationTransition_serializer.write(continuationBufferBufArgsSerializer, valueTmpValueTmpElement);
            }
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, 406871767, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(operation, isEnter)
    continuationResult(_callResult)
}
export function deserializeAndCallNavExtender_CreateNavDestination(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavExtender_CreateNavDestination)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavExtender_OnUpdateStack)
    _call()
}
export function deserializeAndCallOnAdsBlockedCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAdsBlockedCallback)
    let details : AdsBlockedDetails = AdsBlockedDetails_serializer.read(thisDeserializer)
    _call(details)
}
export function deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerPopupSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    _call(index)
}
export function deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerRequestPopupDataCallback)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: Array<string>) => void) = (value: Array<string>):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32((value.length).toInt());
        for (let valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
            const valueTmpElement : string = value[valueCounterI];
            continuationBufferBufArgsSerializer.writeString(valueTmpElement);
        }
        InteropNativeModule._CallCallbackSync(10, -440782244, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(index)
    continuationResult(_callResult)
}
export function deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    _call(index)
}
export function deserializeAndCallOnCheckboxChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnCheckboxChangeCallback)
    let value : boolean = thisDeserializer.readBoolean()
    _call(value)
}
export function deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnCheckboxGroupChangeCallback)
    let value : CheckboxGroupResult = CheckboxGroupResult_serializer.read(thisDeserializer)
    _call(value)
}
export function deserializeAndCallOnContentScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnContentScrollCallback)
    let totalOffsetX : double = thisDeserializer.readFloat64()
    let totalOffsetY : double = thisDeserializer.readFloat64()
    _call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallOnContextMenuHideCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnContextMenuHideCallback)
    _call()
}
export function deserializeAndCallOnCreateMenuCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnCreateMenuCallback)
    const menuItemsTmpBufLength : int32 = thisDeserializer.readInt32()
    let menuItemsTmpBuf : Array<TextMenuItem> = new Array<TextMenuItem>(menuItemsTmpBufLength)
    for (let menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength; menuItemsTmpBufBufCounterI++) {
        menuItemsTmpBuf[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let menuItems : Array<TextMenuItem> = menuItemsTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32((value.length).toInt());
        for (let valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
            const valueTmpElement : TextMenuItem = value[valueCounterI];
            TextMenuItem_serializer.write(continuationBufferBufArgsSerializer, valueTmpElement);
        }
        InteropNativeModule._CallCallbackSync(10, 528588498, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(menuItems)
    continuationResult(_callResult)
}
export function deserializeAndCallOnDetectBlankScreenCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnDetectBlankScreenCallback)
    let event : BlankScreenDetectionEventInfo = BlankScreenDetectionEventInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallOnDidChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnDidChangeCallback)
    let rangeBefore : TextRange = TextRange_serializer.read(thisDeserializer)
    let rangeAfter : TextRange = TextRange_serializer.read(thisDeserializer)
    _call(rangeBefore, rangeAfter)
}
export function deserializeAndCallOnDragEventCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnDragEventCallback)
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    _call(event, extraParams)
}
export function deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFirstMeaningfulPaintCallback)
    let firstMeaningfulPaint : FirstMeaningfulPaint = FirstMeaningfulPaint_serializer.read(thisDeserializer)
    _call(firstMeaningfulPaint)
}
export function deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFoldStatusChangeCallback)
    let event : OnFoldStatusChangeInfo = OnFoldStatusChangeInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallOnFullScreenEnterCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFullScreenEnterCallback)
    let event : FullScreenEnterEvent = FullScreenEnterEvent_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallOnHoverCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnHoverCallback)
    let status : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    _call(status, event)
}
export function deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnHoverStatusChangeCallback)
    let param : HoverEventParam = HoverEventParam_serializer.read(thisDeserializer)
    _call(param)
}
export function deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnIntelligentTrackingPreventionCallback)
    let details : IntelligentTrackingPreventionDetails = IntelligentTrackingPreventionDetails_serializer.read(thisDeserializer)
    _call(details)
}
export function deserializeAndCallOnItemDragStartCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnItemDragStartCallback)
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: CustomBuilder | undefined) => void) = (value?: CustomBuilder | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            continuationBufferBufArgsSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValue));
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, 859020393, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(event, itemIndex)
    continuationResult(_callResult)
}
export function deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnLargestContentfulPaintCallback)
    let largestContentfulPaint : LargestContentfulPaint = LargestContentfulPaint_serializer.read(thisDeserializer)
    _call(largestContentfulPaint)
}
export function deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnLinearIndicatorChangeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let progress : number = (thisDeserializer.readNumber() as number)
    _call(index, progress)
}
export function deserializeAndCallOnMenuItemClickCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnMenuItemClickCallback)
    let menuItem : TextMenuItem = TextMenuItem_serializer.read(thisDeserializer)
    let range : TextRange = TextRange_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(menuItem, range)
    continuationResult(_callResult)
}
export function deserializeAndCallOnMoveHandler(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnMoveHandler)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    _call(from, to)
}
export function deserializeAndCallOnNativeEmbedObjectParamChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeEmbedObjectParamChangeCallback)
    let event : NativeEmbedParamDataInfo = NativeEmbedParamDataInfo_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeEmbedVisibilityChangeCallback)
    let nativeEmbedVisibilityInfo : NativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer.read(thisDeserializer)
    _call(nativeEmbedVisibilityInfo)
}
export function deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNavigationEntryCommittedCallback)
    let loadCommittedDetails : LoadCommittedDetails = LoadCommittedDetails_serializer.read(thisDeserializer)
    _call(loadCommittedDetails)
}
export function deserializeAndCallOnOverrideErrorPageCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnOverrideErrorPageCallback)
    let errorPageEvent : OnErrorReceiveEvent = OnErrorReceiveEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((breakpoints: string) => void) = (breakpoints: string):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeString(breakpoints);
        InteropNativeModule._CallCallbackSync(10, 814634522, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(errorPageEvent)
    continuationResult(_callResult)
}
export function deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnOverrideUrlLoadingCallback)
    let webResourceRequest : WebResourceRequest = (WebResourceRequest_serializer.read(thisDeserializer) as WebResourceRequest)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(webResourceRequest)
    continuationResult(_callResult)
}
export function deserializeAndCallOnPasteCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnPasteCallback)
    let content : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = PasteEvent_serializer.read(thisDeserializer)
    _call(content, event)
}
export function deserializeAndCallOnPickerCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnPickerCallback)
    let selectedIndex : int32 = thisDeserializer.readInt32()
    _call(selectedIndex)
}
export function deserializeAndCallOnRadioChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRadioChangeCallback)
    let isChecked : boolean = thisDeserializer.readBoolean()
    _call(isChecked)
}
export function deserializeAndCallOnRatingChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRatingChangeCallback)
    let rating : double = thisDeserializer.readFloat64()
    _call(rating)
}
export function deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessNotRespondingCallback)
    let data : RenderProcessNotRespondingData = RenderProcessNotRespondingData_serializer.read(thisDeserializer)
    _call(data)
}
export function deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessRespondingCallback)
    _call()
}
export function deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSafeBrowsingCheckResultCallback)
    let threatType : ThreatType = ThreatType.fromValue(thisDeserializer.readInt32())
    _call(threatType)
}
export function deserializeAndCallOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollCallback)
    let scrollOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    _call(scrollOffset, scrollState)
}
export function deserializeAndCallOnScrollEdgeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollEdgeCallback)
    let side : Edge = Edge.fromValue(thisDeserializer.readInt32())
    _call(side)
}
export function deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollFrameBeginCallback)
    let offset : double = thisDeserializer.readFloat64()
    let state : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: OnScrollFrameBeginHandlerResult) => void) = (value: OnScrollFrameBeginHandlerResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        OnScrollFrameBeginHandlerResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 1637092936, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(offset, state)
    continuationResult(_callResult)
}
export function deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollVisibleContentChangeCallback)
    let start : VisibleListContentInfo = VisibleListContentInfo_serializer.read(thisDeserializer)
    let end : VisibleListContentInfo = VisibleListContentInfo_serializer.read(thisDeserializer)
    _call(start, end)
}
export function deserializeAndCallOnSelectCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    let selectStr : string = (thisDeserializer.readString() as string)
    _call(index, selectStr)
}
export function deserializeAndCallOnSslErrorEventCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSslErrorEventCallback)
    let sslErrorEvent : SslErrorEvent = SslErrorEvent_serializer.read(thisDeserializer)
    _call(sslErrorEvent)
}
export function deserializeAndCallOnSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSubmitCallback)
    let enterKey : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationEndCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationStartCallback)
    let index : int32 = thisDeserializer.readInt32()
    let targetIndex : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperGestureSwipeCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationEndCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationStartCallback)
    let index : int32 = thisDeserializer.readInt32()
    let targetIndex : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnTabsContentDidScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsContentDidScrollCallback)
    let selectedIndex : int32 = thisDeserializer.readInt32()
    let index : int32 = thisDeserializer.readInt32()
    let position : double = thisDeserializer.readFloat64()
    let mainAxisLength : double = thisDeserializer.readFloat64()
    _call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsContentWillChangeCallback)
    let currentIndex : int32 = thisDeserializer.readInt32()
    let comingIndex : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value0: boolean) => void) = (value0: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(value0);
        InteropNativeModule._CallCallbackSync(10, 313269291, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(currentIndex, comingIndex)
    continuationResult(_callResult)
}
export function deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsGestureSwipeCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTextPickerChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextPickerChangeCallback)
    const selectItemTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let selectItemTmpBuf : string | Array<string> | undefined
    if (selectItemTmpBufUnionSelector == (0).toChar()) {
        selectItemTmpBuf = (thisDeserializer.readString() as string)
    } else if (selectItemTmpBufUnionSelector == (1).toChar()) {
        const selectItemTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let selectItemTmpBufBufU : Array<string> = new Array<string>(selectItemTmpBufBufULength)
        for (let selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength; selectItemTmpBufBufUBufCounterI++) {
            selectItemTmpBufBufU[selectItemTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        selectItemTmpBuf = selectItemTmpBufBufU
    } else {
        throw new Error("One of the branches for selectItemTmpBuf has to be chosen through deserialisation.")
    }
    let selectItem : string | Array<string> = (selectItemTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toChar()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toChar()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new int32[indexTmpBufBufULength]
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error("One of the branches for indexTmpBuf has to be chosen through deserialisation.")
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    _call(selectItem, index)
}
export function deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextSelectionChangeCallback)
    let selectionStart : int32 = thisDeserializer.readInt32()
    let selectionEnd : int32 = thisDeserializer.readInt32()
    _call(selectionStart, selectionEnd)
}
export function deserializeAndCallOnTimePickerChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTimePickerChangeCallback)
    let result : TimePickerResult = TimePickerResult_serializer.read(thisDeserializer)
    _call(result)
}
export function deserializeAndCallOnViewportFitChangedCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnViewportFitChangedCallback)
    let viewportFit : ViewportFit = ViewportFit.fromValue(thisDeserializer.readInt32())
    _call(viewportFit)
}
export function deserializeAndCallOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnWillScrollCallback)
    let scrollOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = ScrollSource.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: ScrollResult | undefined) => void) = (value?: ScrollResult | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            ScrollResult_serializer.write(continuationBufferBufArgsSerializer, valueTmpValue);
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, 648568223, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(scrollOffset, scrollState, scrollSource)
    continuationResult(_callResult)
}
export function deserializeAndCallPageMapBuilder(thisDeserializer: DeserializerBase): void {
    // const _resourceId : int32 = thisDeserializer.readInt32()
    // const _call  = (ResourceHolder.instance().get(_resourceId) as PageMapBuilder)
    // let name : string = (thisDeserializer.readString() as string)
    // const paramTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    // let paramTmpBuf : Object | null | undefined = undefined
    // if ((paramTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
    //     paramTmpBuf = (thisDeserializer.readObject() as object)
    // }
    // let param : Object | null | undefined = paramTmpBuf
    // _call(name, param)
}
export function deserializeAndCallPageTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PageTransitionCallback)
    let type : RouteType = RouteType.fromValue(thisDeserializer.readInt32())
    let progress : double = thisDeserializer.readFloat64()
    _call(type, progress)
}
export function deserializeAndCallPasteButtonCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PasteButtonCallback)
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : PasteButtonOnClickResult = PasteButtonOnClickResult.fromValue(thisDeserializer.readInt32())
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let errorTmpBuf : BusinessError | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        errorTmpBuf = (BusinessError_serializer.read(thisDeserializer) as BusinessError)
    }
    let error : BusinessError | undefined = errorTmpBuf
    _call(event, result, error)
}
export function deserializeAndCallPasteEventCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PasteEventCallback)
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let eventTmpBuf : PasteEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = PasteEvent_serializer.read(thisDeserializer)
    }
    let event : PasteEvent | undefined = eventTmpBuf
    _call(event)
}
export function deserializeAndCallPluginErrorCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PluginErrorCallback)
    let info : PluginErrorData = PluginErrorData_serializer.read(thisDeserializer)
    _call(info)
}
export function deserializeAndCallPopupStateChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PopupStateChangeCallback)
    let event : PopupStateChangeParam = PopupStateChangeParam_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallProgressModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: ProgressConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ProgressConfiguration = ProgressConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallRadioModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: RadioConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RadioConfiguration = RadioConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallRatingModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: RatingConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RatingConfiguration = RatingConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onerror_Callback)
    let ev : ErrorEvent = ErrorEvent_serializer.read(thisDeserializer)
    _call(ev)
}
export function deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onexit_Callback)
    let code : number = (thisDeserializer.readNumber() as number)
    _call(code)
}
export function deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onmessage_Callback)
    let event : MessageEvents = MessageEvents_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallReuseIdCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ReuseIdCallback)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((breakpoints: string) => void) = (breakpoints: string):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeString(breakpoints);
        InteropNativeModule._CallCallbackSync(10, 814634522, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call()
    continuationResult(_callResult)
}
export function deserializeAndCallRouterFinishCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RouterFinishCallback)
    let value : KPointer = thisDeserializer.readPointer()
    _call(value)
}
export function deserializeAndCallSaveButtonCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SaveButtonCallback)
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : SaveButtonOnClickResult = SaveButtonOnClickResult.fromValue(thisDeserializer.readInt32())
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let errorTmpBuf : BusinessError | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        errorTmpBuf = (BusinessError_serializer.read(thisDeserializer) as BusinessError)
    }
    let error : BusinessError | undefined = errorTmpBuf
    _call(event, result, error)
}
export function deserializeAndCallScrollOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnScrollCallback)
    let xOffset : double = thisDeserializer.readFloat64()
    let yOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    _call(xOffset, yOffset, scrollState)
}
export function deserializeAndCallScrollOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnWillScrollCallback)
    let xOffset : double = thisDeserializer.readFloat64()
    let yOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = ScrollSource.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: OffsetResult | undefined) => void) = (value?: OffsetResult | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            OffsetResult_serializer.write(continuationBufferBufArgsSerializer, valueTmpValue);
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, 1321949695, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(xOffset, yOffset, scrollState, scrollSource)
    continuationResult(_callResult)
}
export function deserializeAndCallSearchSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SearchSubmitCallback)
    let searchContent : string = (thisDeserializer.readString() as string)
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let eventTmpBuf : SubmitEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = eventTmpBuf
    _call(searchContent, event)
}
export function deserializeAndCallSearchValueCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SearchValueCallback)
    let value : string = (thisDeserializer.readString() as string)
    _call(value)
}
export function deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ShouldBuiltInRecognizerParallelWithCallback)
    let current : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    const othersTmpBufLength : int32 = thisDeserializer.readInt32()
    let othersTmpBuf : Array<GestureRecognizer> = new Array<GestureRecognizer>(othersTmpBufLength)
    for (let othersTmpBufBufCounterI = 0; othersTmpBufBufCounterI < othersTmpBufLength; othersTmpBufBufCounterI++) {
        othersTmpBuf[othersTmpBufBufCounterI] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let others : Array<GestureRecognizer> = othersTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: GestureRecognizer) => void) = (value: GestureRecognizer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        GestureRecognizer_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 776202910, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(current, others)
    continuationResult(_callResult)
}
export function deserializeAndCallSizeChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SizeChangeCallback)
    let oldValue : SizeOptions = SizeOptions_serializer.read(thisDeserializer)
    let newValue : SizeOptions = SizeOptions_serializer.read(thisDeserializer)
    _call(oldValue, newValue)
}
export function deserializeAndCallSliderModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: SliderConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : SliderConfiguration = SliderConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallSliderTriggerChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SliderTriggerChangeCallback)
    let value : double = thisDeserializer.readFloat64()
    let mode : SliderChangeMode = SliderChangeMode.fromValue(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallStyledStringMarshallCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringMarshallCallback)
    let marshallableVal : UserDataSpan = (thisDeserializer.readObject() as UserDataSpan)

    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: ArrayBuffer) => void) = (value: ArrayBuffer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBuffer(value);
        InteropNativeModule._CallCallbackSync(10, 908731311, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(marshallableVal)
    continuationResult(_callResult)
}
export function deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringUnmarshallCallback)
    let buf : ArrayBuffer = (thisDeserializer.readBuffer() as ArrayBuffer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: UserDataSpan) => void) = (value: UserDataSpan):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        const valueHolderForUserDataSpan  = value;
        continuationBufferBufArgsSerializer.holdAndWriteObject(valueHolderForUserDataSpan);
        InteropNativeModule._CallCallbackSync(10, -1198150682, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(buf)
    continuationResult(_callResult)
}
export function deserializeAndCallSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SubmitCallback)
    let enterKey : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TabsCustomContentTransitionCallback)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: TabContentAnimatedTransition | undefined) => void) = (value?: TabContentAnimatedTransition | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            TabContentAnimatedTransition_serializer.write(continuationBufferBufArgsSerializer, valueTmpValue);
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, -143931627, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(from, to)
    continuationResult(_callResult)
}
export function deserializeAndCallTextAreaSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextAreaSubmitCallback)
    let enterKeyType : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let eventTmpBuf : SubmitEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = eventTmpBuf
    _call(enterKeyType, event)
}
export function deserializeAndCallTextClockModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: TextClockConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextClockConfiguration = TextClockConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallTextFieldValueCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextFieldValueCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | Resource | undefined
    if (valueTmpBufUnionSelector == (0).toChar()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toChar()) {
        valueTmpBuf = Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
    }
    let value : ResourceStr = (valueTmpBuf as string | Resource)
    _call(value)
}
export function deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerEnterSelectedAreaCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | Array<string> | undefined
    if (valueTmpBufUnionSelector == (0).toChar()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toChar()) {
        const valueTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
        for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        valueTmpBuf = valueTmpBufBufU
    } else {
        throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
    }
    let value : string | Array<string> = (valueTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toChar()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toChar()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new int32[indexTmpBufBufULength]
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error("One of the branches for indexTmpBuf has to be chosen through deserialisation.")
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    _call(value, index)
}
export function deserializeAndCallTextPickerScrollStopCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerScrollStopCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | Array<string> | undefined
    if (valueTmpBufUnionSelector == (0).toChar()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toChar()) {
        const valueTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
        for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        valueTmpBuf = valueTmpBufBufU
    } else {
        throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
    }
    let value : string | Array<string> = (valueTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toChar()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toChar()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new int32[indexTmpBufBufULength]
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error("One of the branches for indexTmpBuf has to be chosen through deserialisation.")
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    _call(value, index)
}
export function deserializeAndCallTextTimerModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextTimerConfiguration = TextTimerConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallTimerCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TimerCallback)
    let utc : int64 = thisDeserializer.readInt64()
    let elapsedTime : int64 = thisDeserializer.readInt64()
    _call(utc, elapsedTime)
}
export function deserializeAndCallToggleModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ToggleConfiguration = ToggleConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: KPointer) => void) = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, 721562324, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(parentNode, config)
    continuationResult(_callResult)
}
export function deserializeAndCallTransitionFinishCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TransitionFinishCallback)
    let transitionIn : boolean = thisDeserializer.readBoolean()
    _call(transitionIn)
}
export function deserializeAndCallType_CommonMethod_onDragStart(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo))
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: CustomBuilder | DragItemInfo) => void) = (value: CustomBuilder | DragItemInfo):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value instanceof CustomBuilder) {
            continuationBufferBufArgsSerializer.writeInt8((0).toByte());
            const valueForIdx0  = value as CustomBuilder;
            continuationBufferBufArgsSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueForIdx0));
        } else if (value instanceof DragItemInfo) {
            continuationBufferBufArgsSerializer.writeInt8((1).toByte());
            const valueForIdx1  = value as DragItemInfo;
            DragItemInfo_serializer.write(continuationBufferBufArgsSerializer, valueForIdx1);
        }
        InteropNativeModule._CallCallbackSync(10, -620935067, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(event, extraParams)
    continuationResult(_callResult)
}
export function deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
    let from : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let to : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: NavigationAnimatedTransition | undefined) => void) = (value?: NavigationAnimatedTransition | undefined):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== undefined) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            NavigationAnimatedTransition_serializer.write(continuationBufferBufArgsSerializer, valueTmpValue);
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, -2035339519, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(from, to, operation)
    continuationResult(_callResult)
}
export function deserializeAndCallType_WebAttribute_onInterceptRequest(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnInterceptRequestEvent) => WebResourceResponse | null))
    let value0 : OnInterceptRequestEvent = OnInterceptRequestEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: WebResourceResponse | null) => void) = (value?: WebResourceResponse | null):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        if (value !== null) {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
            const valueTmpValue  = value!;
            WebResourceResponse_serializer.write(continuationBufferBufArgsSerializer, valueTmpValue);
        } else {
            continuationBufferBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
        }
        InteropNativeModule._CallCallbackSync(10, 1022161794, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(value0)
    continuationResult(_callResult)
}
export function deserializeAndCallUpdateTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as UpdateTransitionCallback)
    let progress : double = thisDeserializer.readFloat64()
    _call(progress)
}
export function deserializeAndCallVisibleAreaChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as VisibleAreaChangeCallback)
    let isExpanding : boolean = thisDeserializer.readBoolean()
    let currentRatio : double = thisDeserializer.readFloat64()
    _call(isExpanding, currentRatio)
}
export function deserializeAndCallVoidCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as VoidCallback)
    _call()
}
export function deserializeAndCallWebKeyboardCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as WebKeyboardCallback)
    let keyboardCallbackInfo : WebKeyboardCallbackInfo = WebKeyboardCallbackInfo_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    let continuationResult : ((value: WebKeyboardOptions) => void) = (value: WebKeyboardOptions):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        WebKeyboardOptions_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, -1376223390, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    const _callResult  = _call(keyboardCallbackInfo)
    continuationResult(_callResult)
}
export function deserializeAndCallWorkerEventListener(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as WorkerEventListener)
    let event : Event = Event_serializer.read(thisDeserializer)
    _call(event)
}
export function deserializeAndCallCallback(thisDeserializer: DeserializerBase): void {
    const kind : int32 = thisDeserializer.readInt32()
    switch ((kind as CallbackKind)) {
        case CallbackKind.Kind_AccessibilityActionInterceptCallback: return deserializeAndCallAccessibilityActionInterceptCallback(thisDeserializer);
        case CallbackKind.Kind_AccessibilityCallback: return deserializeAndCallAccessibilityCallback(thisDeserializer);
        case CallbackKind.Kind_AccessibilityFocusCallback: return deserializeAndCallAccessibilityFocusCallback(thisDeserializer);
        case CallbackKind.Kind_AccessibilityTransparentCallback: return deserializeAndCallAccessibilityTransparentCallback(thisDeserializer);
        case CallbackKind.Kind_ArcScrollIndexHandler: return deserializeAndCallArcScrollIndexHandler(thisDeserializer);
        case CallbackKind.Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer);
        case CallbackKind.Kind_AsyncCallback_Void: return deserializeAndCallAsyncCallback_Void(thisDeserializer);
        case CallbackKind.Kind_ButtonModifierBuilder: return deserializeAndCallButtonModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_ButtonTriggerClickCallback: return deserializeAndCallButtonTriggerClickCallback(thisDeserializer);
        case CallbackKind.Kind_Callback_AccessibilityActionInterceptResult_Void: return deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Area_Area_Void: return deserializeAndCallCallback_Area_Area_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_I32_Void: return deserializeAndCallCallback_Array_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_String_Void: return deserializeAndCallCallback_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer);
        case CallbackKind.Kind_Callback_AxisEvent_Void: return deserializeAndCallCallback_AxisEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean: return deserializeAndCallCallback_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean_Void: return deserializeAndCallCallback_Boolean_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Buffer_Void: return deserializeAndCallCallback_Buffer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ClickEvent_Void: return deserializeAndCallCallback_ClickEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ComputedBarAttribute_Void: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_CopyEvent_Void: return deserializeAndCallCallback_CopyEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_CreateItem: return deserializeAndCallCallback_CreateItem(thisDeserializer);
        case CallbackKind.Kind_Callback_CrownEvent_Void: return deserializeAndCallCallback_CrownEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics: return deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisDeserializer);
        case CallbackKind.Kind_Callback_CustomSpanMetrics_Void: return deserializeAndCallCallback_CustomSpanMetrics_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_CutEvent_Void: return deserializeAndCallCallback_CutEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Date_Void: return deserializeAndCallCallback_Date_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DeleteValue_Boolean: return deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_DeleteValue_Void: return deserializeAndCallCallback_DeleteValue_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DismissContentCoverAction_Void: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DismissDialogAction_Void: return deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DismissPopupAction_Void: return deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DismissSheetAction_Void: return deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DragEvent_Opt_String_Void: return deserializeAndCallCallback_DragEvent_Opt_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DrawContext_CustomSpanDrawInfo_Void: return deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_DrawContext_Void: return deserializeAndCallCallback_DrawContext_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_EditableTextChangeValue_Boolean: return deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_ErrorInformation_Void: return deserializeAndCallCallback_ErrorInformation_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Extender_OnFinish: return deserializeAndCallCallback_Extender_OnFinish(thisDeserializer);
        case CallbackKind.Kind_Callback_Extender_OnProgress: return deserializeAndCallCallback_Extender_OnProgress(thisDeserializer);
        case CallbackKind.Kind_Callback_F64_F64_Void: return deserializeAndCallCallback_F64_F64_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_F64_SliderChangeMode_Void: return deserializeAndCallCallback_F64_SliderChangeMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_F64_Void: return deserializeAndCallCallback_F64_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_FullscreenInfo_Void: return deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureEvent_Void: return deserializeAndCallCallback_GestureEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureRecognizer_Void: return deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_HitTestMode_Void: return deserializeAndCallCallback_HitTestMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_HoverEvent_Void: return deserializeAndCallCallback_HoverEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_F64_ComputedBarAttribute: return deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_I32_Boolean: return deserializeAndCallCallback_I32_I32_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_I32_I32_Void: return deserializeAndCallCallback_I32_I32_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_I32_Void: return deserializeAndCallCallback_I32_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_Tuple_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_Tuple_I32_I32_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisDeserializer);
        case CallbackKind.Kind_Callback_I64_Void: return deserializeAndCallCallback_I64_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_I32_Void: return deserializeAndCallCallback_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_InsertValue_Boolean: return deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_InsertValue_Void: return deserializeAndCallCallback_InsertValue_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_I32_I32_Void: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_I32_Void: return deserializeAndCallCallback_ItemDragInfo_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_Void: return deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_KeyEvent_Boolean: return deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_KeyEvent_Void: return deserializeAndCallCallback_KeyEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Map_String_RecordData_Void: return deserializeAndCallCallback_Map_String_RecordData_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_MarqueeState_Void: return deserializeAndCallCallback_MarqueeState_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_MouseEvent_Void: return deserializeAndCallCallback_MouseEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NativeXComponentPointer_Void: return deserializeAndCallCallback_NativeXComponentPointer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavDestinationContext_Void: return deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationMode_Void: return deserializeAndCallCallback_NavigationMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Void: return deserializeAndCallCallback_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Object_Void: return deserializeAndCallCallback_Object_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnAlertEvent_Boolean: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnAudioStateChangedEvent_Void: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnBeforeUnloadEvent_Boolean: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnClientAuthenticationEvent_Void: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnConfirmEvent_Boolean: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnConsoleEvent_Boolean: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnContextMenuShowEvent_Boolean: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnDataResubmittedEvent_Void: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnDestory_Void: return deserializeAndCallCallback_OnDestory_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnLoadFinishedEvent_Void: return deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnLoadStartedEvent_Void: return deserializeAndCallCallback_OnLoadStartedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer);
        case CallbackKind.Kind_Callback_OnMoveFromTo: return deserializeAndCallCallback_OnMoveFromTo(thisDeserializer);
        case CallbackKind.Kind_Callback_OnOverScrollEvent_Void: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageBeginEvent_Void: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageEndEvent_Void: return deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageVisibleEvent_Void: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPdfLoadEvent_Void: return deserializeAndCallCallback_OnPdfLoadEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPdfScrollEvent_Void: return deserializeAndCallCallback_OnPdfScrollEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPermissionRequestEvent_Void: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_onPlaceChildren_Void: return deserializeAndCallCallback_onPlaceChildren_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnProgressChangeEvent_Void: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPromptEvent_Boolean: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnRefreshAccessedHistoryEvent_Void: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnRenderExitedEvent_Void: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnResourceLoadEvent_Void: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnScaleChangeEvent_Void: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnScreenCaptureRequestEvent_Void: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnScrollEvent_Void: return deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnSearchResultReceiveEvent_Void: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnShowFileSelectorEvent_Boolean: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnSslErrorEventReceiveEvent_Void: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnTitleReceiveEvent_Void: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnTouchIconUrlReceivedEvent_Void: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnWindowNewEvent_Void: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallCallback_Opt_CustomBuilder_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_WebResourceResponse_Void: return deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_PlaybackInfo_Void: return deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Pointer_Void: return deserializeAndCallCallback_Pointer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_PopInfo_Void: return deserializeAndCallCallback_PopInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_PreDragStatus_Void: return deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_PreparedInfo_Void: return deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_RangeUpdate: return deserializeAndCallCallback_RangeUpdate(thisDeserializer);
        case CallbackKind.Kind_Callback_RefreshStatus_Void: return deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorChangeValue_Boolean: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorDeleteValue_Boolean: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorInsertValue_Boolean: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorRange_Void: return deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorSelection_Void: return deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_RichEditorTextSpanResult_Void: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_RouterCallbackInfo_Void: return deserializeAndCallCallback_RouterCallbackInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SheetDismiss_Void: return deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SheetType_Void: return deserializeAndCallCallback_SheetType_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Size_Void: return deserializeAndCallCallback_Size_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SizeResult_Void: return deserializeAndCallCallback_SizeResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SpringBackAction_Void: return deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_StateStylesChange: return deserializeAndCallCallback_StateStylesChange(thisDeserializer);
        case CallbackKind.Kind_Callback_String_PasteEvent_Void: return deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_String_Void: return deserializeAndCallCallback_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SwipeActionState_Void: return deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Arkui_Component_Units_Length: return deserializeAndCallCallback_T_Void_Arkui_Component_Units_Length(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr: return deserializeAndCallCallback_T_Void_Arkui_Component_Units_ResourceStr(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr: return deserializeAndCallCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Array_Global_Resource_Resource: return deserializeAndCallCallback_T_Void_Array_Global_Resource_Resource(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Array_I32: return deserializeAndCallCallback_T_Void_Array_I32(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Array_String: return deserializeAndCallCallback_T_Void_Array_String(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Boolean: return deserializeAndCallCallback_T_Void_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Date: return deserializeAndCallCallback_T_Void_Date(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_F64: return deserializeAndCallCallback_T_Void_F64(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Global_Resource_Resource: return deserializeAndCallCallback_T_Void_Global_Resource_Resource(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_I32: return deserializeAndCallCallback_T_Void_I32(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_Number: return deserializeAndCallCallback_T_Void_Number(thisDeserializer);
        case CallbackKind.Kind_Callback_T_Void_String: return deserializeAndCallCallback_T_Void_String(thisDeserializer);
        case CallbackKind.Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TerminationInfo_Void: return deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TextPickerResult_Void: return deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TextRange_Void: return deserializeAndCallCallback_TextRange_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TimePickerResult_Void: return deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchEvent_Void: return deserializeAndCallCallback_TouchEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchResult_Void: return deserializeAndCallCallback_TouchResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Tuple_I32_I32_I32_I32_Void: return deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Tuple_I32_I32_Void: return deserializeAndCallCallback_Tuple_I32_I32_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void: return deserializeAndCallCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_VisibilityChangeReason_Void: return deserializeAndCallCallback_VisibilityChangeReason_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Void: return deserializeAndCallCallback_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer);
        case CallbackKind.Kind_CheckBoxGroupModifierBuilder: return deserializeAndCallCheckBoxGroupModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_CheckBoxModifierBuilder: return deserializeAndCallCheckBoxModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_ContentDidScrollCallback: return deserializeAndCallContentDidScrollCallback(thisDeserializer);
        case CallbackKind.Kind_ContentWillScrollCallback: return deserializeAndCallContentWillScrollCallback(thisDeserializer);
        case CallbackKind.Kind_CustomBuilderT_Arkui_Component_Enums_ResponseType: return deserializeAndCallCustomBuilderT_Arkui_Component_Enums_ResponseType(thisDeserializer);
        case CallbackKind.Kind_CustomBuilderT_I32: return deserializeAndCallCustomBuilderT_I32(thisDeserializer);
        case CallbackKind.Kind_CustomNodeBuilder: return deserializeAndCallCustomNodeBuilder(thisDeserializer);
        case CallbackKind.Kind_DataPanelModifierBuilder: return deserializeAndCallDataPanelModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_EditableTextOnChangeCallback: return deserializeAndCallEditableTextOnChangeCallback(thisDeserializer);
        case CallbackKind.Kind_ErrorCallback_Ohos_Base_BusinessError: return deserializeAndCallErrorCallback_Ohos_Base_BusinessError(thisDeserializer);
        case CallbackKind.Kind_GaugeModifierBuilder: return deserializeAndCallGaugeModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_GestureRecognizerJudgeBeginCallback: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer);
        case CallbackKind.Kind_GetItemMainSizeByIndex: return deserializeAndCallGetItemMainSizeByIndex(thisDeserializer);
        case CallbackKind.Kind_HoverCallback: return deserializeAndCallHoverCallback(thisDeserializer);
        case CallbackKind.Kind_ImageCompleteCallback: return deserializeAndCallImageCompleteCallback(thisDeserializer);
        case CallbackKind.Kind_ImageErrorCallback: return deserializeAndCallImageErrorCallback(thisDeserializer);
        case CallbackKind.Kind_ImageOnCompleteCallback: return deserializeAndCallImageOnCompleteCallback(thisDeserializer);
        case CallbackKind.Kind_InterceptionModeCallback: return deserializeAndCallInterceptionModeCallback(thisDeserializer);
        case CallbackKind.Kind_InterceptionShowCallback: return deserializeAndCallInterceptionShowCallback(thisDeserializer);
        case CallbackKind.Kind_LoadingProgressModifierBuilder: return deserializeAndCallLoadingProgressModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_MenuCallback: return deserializeAndCallMenuCallback(thisDeserializer);
        case CallbackKind.Kind_MenuItemModifierBuilder: return deserializeAndCallMenuItemModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_MenuOnAppearCallback: return deserializeAndCallMenuOnAppearCallback(thisDeserializer);
        case CallbackKind.Kind_ModifierKeyStateGetter: return deserializeAndCallModifierKeyStateGetter(thisDeserializer);
        case CallbackKind.Kind_MouseInfoCallback: return deserializeAndCallMouseInfoCallback(thisDeserializer);
        case CallbackKind.Kind_NavDestinationTransitionDelegate: return deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer);
        case CallbackKind.Kind_NavExtender_CreateNavDestination: return deserializeAndCallNavExtender_CreateNavDestination(thisDeserializer);
        case CallbackKind.Kind_NavExtender_OnUpdateStack: return deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer);
        case CallbackKind.Kind_OnAdsBlockedCallback: return deserializeAndCallOnAdsBlockedCallback(thisDeserializer);
        case CallbackKind.Kind_OnAlphabetIndexerPopupSelectCallback: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer);
        case CallbackKind.Kind_OnAlphabetIndexerRequestPopupDataCallback: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer);
        case CallbackKind.Kind_OnAlphabetIndexerSelectCallback: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer);
        case CallbackKind.Kind_OnCheckboxChangeCallback: return deserializeAndCallOnCheckboxChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnCheckboxGroupChangeCallback: return deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnContentScrollCallback: return deserializeAndCallOnContentScrollCallback(thisDeserializer);
        case CallbackKind.Kind_OnContextMenuHideCallback: return deserializeAndCallOnContextMenuHideCallback(thisDeserializer);
        case CallbackKind.Kind_OnCreateMenuCallback: return deserializeAndCallOnCreateMenuCallback(thisDeserializer);
        case CallbackKind.Kind_OnDetectBlankScreenCallback: return deserializeAndCallOnDetectBlankScreenCallback(thisDeserializer);
        case CallbackKind.Kind_OnDidChangeCallback: return deserializeAndCallOnDidChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnDragEventCallback: return deserializeAndCallOnDragEventCallback(thisDeserializer);
        case CallbackKind.Kind_OnFirstMeaningfulPaintCallback: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer);
        case CallbackKind.Kind_OnFoldStatusChangeCallback: return deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnFullScreenEnterCallback: return deserializeAndCallOnFullScreenEnterCallback(thisDeserializer);
        case CallbackKind.Kind_OnHoverCallback: return deserializeAndCallOnHoverCallback(thisDeserializer);
        case CallbackKind.Kind_OnHoverStatusChangeCallback: return deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnIntelligentTrackingPreventionCallback: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer);
        case CallbackKind.Kind_OnItemDragStartCallback: return deserializeAndCallOnItemDragStartCallback(thisDeserializer);
        case CallbackKind.Kind_OnLargestContentfulPaintCallback: return deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer);
        case CallbackKind.Kind_OnLinearIndicatorChangeCallback: return deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnMenuItemClickCallback: return deserializeAndCallOnMenuItemClickCallback(thisDeserializer);
        case CallbackKind.Kind_OnMoveHandler: return deserializeAndCallOnMoveHandler(thisDeserializer);
        case CallbackKind.Kind_OnNativeEmbedObjectParamChangeCallback: return deserializeAndCallOnNativeEmbedObjectParamChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnNativeEmbedVisibilityChangeCallback: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnNavigationEntryCommittedCallback: return deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer);
        case CallbackKind.Kind_OnOverrideErrorPageCallback: return deserializeAndCallOnOverrideErrorPageCallback(thisDeserializer);
        case CallbackKind.Kind_OnOverrideUrlLoadingCallback: return deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer);
        case CallbackKind.Kind_OnPasteCallback: return deserializeAndCallOnPasteCallback(thisDeserializer);
        case CallbackKind.Kind_OnPickerCallback: return deserializeAndCallOnPickerCallback(thisDeserializer);
        case CallbackKind.Kind_OnRadioChangeCallback: return deserializeAndCallOnRadioChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnRatingChangeCallback: return deserializeAndCallOnRatingChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnRenderProcessNotRespondingCallback: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer);
        case CallbackKind.Kind_OnRenderProcessRespondingCallback: return deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer);
        case CallbackKind.Kind_OnSafeBrowsingCheckResultCallback: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer);
        case CallbackKind.Kind_OnScrollCallback: return deserializeAndCallOnScrollCallback(thisDeserializer);
        case CallbackKind.Kind_OnScrollEdgeCallback: return deserializeAndCallOnScrollEdgeCallback(thisDeserializer);
        case CallbackKind.Kind_OnScrollFrameBeginCallback: return deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer);
        case CallbackKind.Kind_OnScrollVisibleContentChangeCallback: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnSelectCallback: return deserializeAndCallOnSelectCallback(thisDeserializer);
        case CallbackKind.Kind_OnSslErrorEventCallback: return deserializeAndCallOnSslErrorEventCallback(thisDeserializer);
        case CallbackKind.Kind_OnSubmitCallback: return deserializeAndCallOnSubmitCallback(thisDeserializer);
        case CallbackKind.Kind_OnSwiperAnimationEndCallback: return deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer);
        case CallbackKind.Kind_OnSwiperAnimationStartCallback: return deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer);
        case CallbackKind.Kind_OnSwiperGestureSwipeCallback: return deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsAnimationEndCallback: return deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsAnimationStartCallback: return deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsContentDidScrollCallback: return deserializeAndCallOnTabsContentDidScrollCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsContentWillChangeCallback: return deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsGestureSwipeCallback: return deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTextPickerChangeCallback: return deserializeAndCallOnTextPickerChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTextSelectionChangeCallback: return deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTimePickerChangeCallback: return deserializeAndCallOnTimePickerChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnViewportFitChangedCallback: return deserializeAndCallOnViewportFitChangedCallback(thisDeserializer);
        case CallbackKind.Kind_OnWillScrollCallback: return deserializeAndCallOnWillScrollCallback(thisDeserializer);
        case CallbackKind.Kind_PageMapBuilder: return deserializeAndCallPageMapBuilder(thisDeserializer);
        case CallbackKind.Kind_PageTransitionCallback: return deserializeAndCallPageTransitionCallback(thisDeserializer);
        case CallbackKind.Kind_PasteButtonCallback: return deserializeAndCallPasteButtonCallback(thisDeserializer);
        case CallbackKind.Kind_PasteEventCallback: return deserializeAndCallPasteEventCallback(thisDeserializer);
        case CallbackKind.Kind_PluginErrorCallback: return deserializeAndCallPluginErrorCallback(thisDeserializer);
        case CallbackKind.Kind_PopupStateChangeCallback: return deserializeAndCallPopupStateChangeCallback(thisDeserializer);
        case CallbackKind.Kind_ProgressModifierBuilder: return deserializeAndCallProgressModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_RadioModifierBuilder: return deserializeAndCallRadioModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_RatingModifierBuilder: return deserializeAndCallRatingModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_RestrictedWorker_onerror_Callback: return deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer);
        case CallbackKind.Kind_RestrictedWorker_onexit_Callback: return deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer);
        case CallbackKind.Kind_RestrictedWorker_onmessage_Callback: return deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer);
        case CallbackKind.Kind_ReuseIdCallback: return deserializeAndCallReuseIdCallback(thisDeserializer);
        case CallbackKind.Kind_RouterFinishCallback: return deserializeAndCallRouterFinishCallback(thisDeserializer);
        case CallbackKind.Kind_SaveButtonCallback: return deserializeAndCallSaveButtonCallback(thisDeserializer);
        case CallbackKind.Kind_ScrollOnScrollCallback: return deserializeAndCallScrollOnScrollCallback(thisDeserializer);
        case CallbackKind.Kind_ScrollOnWillScrollCallback: return deserializeAndCallScrollOnWillScrollCallback(thisDeserializer);
        case CallbackKind.Kind_SearchSubmitCallback: return deserializeAndCallSearchSubmitCallback(thisDeserializer);
        case CallbackKind.Kind_SearchValueCallback: return deserializeAndCallSearchValueCallback(thisDeserializer);
        case CallbackKind.Kind_ShouldBuiltInRecognizerParallelWithCallback: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer);
        case CallbackKind.Kind_SizeChangeCallback: return deserializeAndCallSizeChangeCallback(thisDeserializer);
        case CallbackKind.Kind_SliderModifierBuilder: return deserializeAndCallSliderModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_SliderTriggerChangeCallback: return deserializeAndCallSliderTriggerChangeCallback(thisDeserializer);
        case CallbackKind.Kind_StyledStringMarshallCallback: return deserializeAndCallStyledStringMarshallCallback(thisDeserializer);
        case CallbackKind.Kind_StyledStringUnmarshallCallback: return deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer);
        case CallbackKind.Kind_SubmitCallback: return deserializeAndCallSubmitCallback(thisDeserializer);
        case CallbackKind.Kind_TabsCustomContentTransitionCallback: return deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer);
        case CallbackKind.Kind_TextAreaSubmitCallback: return deserializeAndCallTextAreaSubmitCallback(thisDeserializer);
        case CallbackKind.Kind_TextClockModifierBuilder: return deserializeAndCallTextClockModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_TextFieldValueCallback: return deserializeAndCallTextFieldValueCallback(thisDeserializer);
        case CallbackKind.Kind_TextPickerEnterSelectedAreaCallback: return deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer);
        case CallbackKind.Kind_TextPickerScrollStopCallback: return deserializeAndCallTextPickerScrollStopCallback(thisDeserializer);
        case CallbackKind.Kind_TextTimerModifierBuilder: return deserializeAndCallTextTimerModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_TimerCallback: return deserializeAndCallTimerCallback(thisDeserializer);
        case CallbackKind.Kind_ToggleModifierBuilder: return deserializeAndCallToggleModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_TransitionFinishCallback: return deserializeAndCallTransitionFinishCallback(thisDeserializer);
        case CallbackKind.Kind_Type_CommonMethod_onDragStart: return deserializeAndCallType_CommonMethod_onDragStart(thisDeserializer);
        case CallbackKind.Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer);
        case CallbackKind.Kind_Type_WebAttribute_onInterceptRequest: return deserializeAndCallType_WebAttribute_onInterceptRequest(thisDeserializer);
        case CallbackKind.Kind_UpdateTransitionCallback: return deserializeAndCallUpdateTransitionCallback(thisDeserializer);
        case CallbackKind.Kind_VisibleAreaChangeCallback: return deserializeAndCallVisibleAreaChangeCallback(thisDeserializer);
        case CallbackKind.Kind_VoidCallback: return deserializeAndCallVoidCallback(thisDeserializer);
        case CallbackKind.Kind_WebKeyboardCallback: return deserializeAndCallWebKeyboardCallback(thisDeserializer);
        case CallbackKind.Kind_WorkerEventListener: return deserializeAndCallWorkerEventListener(thisDeserializer);
    }
    throw new Error("Unknown callback kind")
}
export function registerArkuiApiHandler(): void {
    registerApiEventHandler(10, deserializeAndCallCallback)
}

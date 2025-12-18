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

import { AccessibilityActionInterceptCallback, AccessibilityCallback, AccessibilityHoverEvent_serializer, AccessibilityFocusCallback, AccessibilityTransparentCallback, TouchEvent_serializer, Callback as arkui_component_common_Callback, TouchTestInfo_serializer, TouchResult_serializer, AxisEvent_serializer, HoverEvent_serializer, ClickEvent_serializer, CrownEvent_serializer, DismissContentCoverAction_serializer, DismissPopupAction_serializer, DismissSheetAction_serializer, DragEvent_serializer, FocusAxisEvent_serializer, ItemDragInfo_serializer, KeyEvent_serializer, MouseEvent_serializer, GeometryInfo_serializer, Measurable_serializer, SizeResult_serializer, Layoutable_serializer, ScrollResult_serializer, SheetDismiss_serializer, SpringBackAction_serializer, TerminationInfo_serializer, DragItemInfo_serializer, GestureRecognizerJudgeBeginCallback, HoverCallback, ModifierKeyStateGetter, OnDragEventCallback, OnItemDragStartCallback, OnMoveHandler, OnScrollCallback, OnWillScrollCallback, PopupStateChangeCallback, PopupStateChangeParam_serializer, ReuseIdCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, TouchTestDoneCallback, TransitionFinishCallback, VisibleAreaChangeCallback, AccessibilityAction, AccessibilityActionInterceptResult, AccessibilityHoverEvent, TouchEvent, TouchTestInfo, TouchResult, AxisEvent, HoverEvent, ClickEvent, CrownEvent, DismissContentCoverAction, DismissPopupAction, DismissSheetAction, DragEvent, DrawContext as arkui_component_common_DrawContext, FocusAxisEvent, ItemDragInfo, KeyEvent, MouseEvent, GeometryInfo, Measurable, SizeResult, Layoutable, ScrollResult, PreDragStatus, SheetDismiss, SheetType, SpringBackAction, TerminationInfo, DragItemInfo, PopupStateChangeParam } from './../../component/common'
import { resourceFinalizerRegister, registerApiEventHandler, ResourceHolder, KInt, KStringPtr, wrapSystemCallback, DeserializerBase, SerializerBase, CallbackResource, InteropNativeModule, KPointer, RuntimeType, KSerializerBuffer, NativeBuffer } from '@koalaui/interop'
import { ButtonConfiguration_serializer, ButtonTriggerClickCallback, ButtonConfiguration } from './../../component/button'
import { Area_serializer, ConstraintSizeOptions_serializer, SizeOptions_serializer, VoidCallback, Area, ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, Length, ConstraintSizeOptions, SizeOptions } from './../../component/units'
import { global_resource_Resource_serializer } from './../resource'
import { TextMenuItem_serializer, DeleteValue_serializer, EditableTextChangeValue_serializer, InsertValue_serializer, StyledStringChangeValue_serializer, TextRange_serializer, EditableTextOnChangeCallback, PreviewText_serializer, TextChangeOptions_serializer, OnCreateMenuCallback, OnDidChangeCallback, OnMenuItemClickCallback, TextMenuItem, DeleteValue, EditableTextChangeValue, InsertValue, StyledStringChangeValue, TextRange, PreviewText, TextChangeOptions } from './../../component/textCommon'
import { ComputedBarAttribute_serializer, ComputedBarAttribute } from './../../component/grid'
import { CopyEvent_serializer, CutEvent_serializer, RichEditorChangeValue_serializer, RichEditorDeleteValue_serializer, RichEditorInsertValue_serializer, RichEditorRange_serializer, RichEditorSelection_serializer, RichEditorTextSpanResult_serializer, PasteEvent_serializer, MenuCallback, MenuOnAppearCallback, OnHoverCallback, PasteEventCallback, SubmitCallback, CopyEvent, CutEvent, RichEditorChangeValue, RichEditorDeleteValue, RichEditorInsertValue, RichEditorRange, RichEditorSelection, RichEditorTextSpanResult, PasteEvent } from './../../component/richEditor'
import { Callback_CreateItem, Callback_Extender_OnFinish, Callback_Extender_OnProgress, Callback_OnDestory_Void, Callback_onMeasureSize_SizeResult, Callback_OnMoveFromTo, Callback_onPlaceChildren_Void, Callback_RangeUpdate, Callback_Size_Void, Callback_StateStylesChange, CustomNodeBuilder, BusinessErrorInterface, BusinessErrorInterface_Void_serializer, FrameCallbackHandler, GestureEventHandler, NavExtender_CreateNavDestination, NavExtender_OnUpdateStack, NodeContainerOpsOnTouchCallback, PageMapNodeBuilder, RestrictedWorker_onerror_Callback, ErrorEvent_serializer, RestrictedWorker_onexit_Callback, RestrictedWorker_onmessage_Callback, MessageEvents_serializer, RouterFinishCallback, WorkerEventListener, Event_serializer, ErrorEvent, MessageEvents, Event } from './../../component/idlize'
import { CustomSpanMeasureInfo_serializer, CustomSpanMetrics_serializer, CustomSpanDrawInfo_serializer, StyledString_serializer, StyledStringMarshallCallback, StyledStringUnmarshallCallback, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledString, StyledStringMarshallingValue, UserDataSpan } from './../../component/styledString'
import { DismissDialogAction_serializer, DismissDialogAction } from './../../component/actionSheet'
import { arkui_Graphics_DrawContext_serializer, Size_serializer } from './../Graphics'
import { ErrorInformation_serializer, FormCallbackInfo_serializer, ErrorInformation, FormCallbackInfo } from './../../component/formComponent'
import { FullscreenInfo_serializer, PlaybackInfo_serializer, PreparedInfo_serializer, FullscreenInfo, PlaybackInfo, PreparedInfo } from './../../component/video'
import { GestureEvent_serializer, GestureInfo_serializer, BaseGestureEvent_serializer, GestureRecognizer_serializer, TouchRecognizer_serializer, GestureEvent, GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer, TouchRecognizer } from './../../component/gesture'
import { Callback as ohos_base_Callback, ErrorCallback, RecordData, BusinessError } from '@ohos.base'
import { NativeEmbedDataInfo_serializer, NativeEmbedTouchInfo_serializer, OnAlertEvent_serializer, OnAudioStateChangedEvent_serializer, OnBeforeUnloadEvent_serializer, OnClientAuthenticationEvent_serializer, OnConfirmEvent_serializer, OnConsoleEvent_serializer, OnContextMenuShowEvent_serializer, OnDataResubmittedEvent_serializer, OnDownloadStartEvent_serializer, OnErrorReceiveEvent_serializer, OnFaviconReceivedEvent_serializer, OnFirstContentfulPaintEvent_serializer, OnGeolocationShowEvent_serializer, OnHttpAuthRequestEvent_serializer, OnHttpErrorReceiveEvent_serializer, OnInterceptRequestEvent_serializer, WebResourceResponse_serializer, OnLoadFinishedEvent_serializer, OnLoadInterceptEvent_serializer, OnLoadStartedEvent_serializer, OnOverScrollEvent_serializer, OnPageBeginEvent_serializer, OnPageEndEvent_serializer, OnPageVisibleEvent_serializer, OnPermissionRequestEvent_serializer, OnProgressChangeEvent_serializer, OnPromptEvent_serializer, OnRefreshAccessedHistoryEvent_serializer, OnRenderExitedEvent_serializer, OnResourceLoadEvent_serializer, OnScaleChangeEvent_serializer, OnScreenCaptureRequestEvent_serializer, OnScrollEvent_serializer, OnSearchResultReceiveEvent_serializer, OnShowFileSelectorEvent_serializer, OnSslErrorEventReceiveEvent_serializer, OnTitleReceiveEvent_serializer, OnTouchIconUrlReceivedEvent_serializer, OnWindowNewEvent_serializer, WebKeyboardOptions_serializer, OnAdsBlockedCallback, AdsBlockedDetails_serializer, OnContextMenuHideCallback, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint_serializer, OnFullScreenEnterCallback, FullScreenEnterEvent_serializer, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails_serializer, OnLargestContentfulPaintCallback, LargestContentfulPaint_serializer, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo_serializer, OnNavigationEntryCommittedCallback, LoadCommittedDetails_serializer, OnOverrideUrlLoadingCallback, WebResourceRequest_serializer, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData_serializer, OnRenderProcessRespondingCallback, OnSafeBrowsingCheckResultCallback, OnSslErrorEventCallback, SslErrorEvent_serializer, OnViewportFitChangedCallback, WebKeyboardCallback, WebKeyboardCallbackInfo_serializer, NativeEmbedDataInfo, NativeEmbedTouchInfo, OnAlertEvent, OnAudioStateChangedEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnConsoleEvent, OnContextMenuShowEvent, OnDataResubmittedEvent, OnDownloadStartEvent, OnErrorReceiveEvent, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, WebResourceResponse, OnLoadFinishedEvent, OnLoadInterceptEvent, OnLoadStartedEvent, OnOverScrollEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPermissionRequestEvent, OnProgressChangeEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnScreenCaptureRequestEvent, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, OnSslErrorEventReceiveEvent, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, WebKeyboardOptions, AdsBlockedDetails, FirstMeaningfulPaint, FullScreenEnterEvent, IntelligentTrackingPreventionDetails, LargestContentfulPaint, NativeEmbedVisibilityInfo, LoadCommittedDetails, WebResourceRequest, RenderProcessNotRespondingData, ThreatType, SslErrorEvent, ViewportFit, WebKeyboardCallbackInfo } from './../../component/web'
import { NavDestinationContext_serializer, NavDestinationTransition_serializer, NavDestinationTransitionDelegate, NavDestinationActiveReason, NavDestinationContext, NavDestinationTransition } from './../../component/navDestination'
import { NavigationTransitionProxy_serializer, NavigationAnimatedTransition_serializer, PopInfo_serializer, InterceptionModeCallback, InterceptionShowCallback, NavContentInfo_serializer, UpdateTransitionCallback, NavigationMode, NavigationTitleMode, NavigationTransitionProxy, NavigationAnimatedTransition, PopInfo, NavBar, NavigationOperation, NavContentInfo } from './../../component/navigation'
import { OnScrollFrameBeginHandlerResult_serializer, OffsetResult_serializer, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollOnScrollCallback, ScrollOnWillScrollCallback, OnScrollFrameBeginHandlerResult, OffsetResult } from './../../component/scroll'
import { TabContentAnimatedTransition_serializer, TabContentTransitionProxy_serializer, OnTabsAnimationEndCallback, TabsAnimationEvent_serializer, OnTabsAnimationStartCallback, OnTabsContentWillChangeCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback, TabContentAnimatedTransition, TabContentTransitionProxy, TabsAnimationEvent } from './../../component/tabs'
import { SurfaceRect_serializer, SurfaceRect } from './../../component/xcomponent'
import { SwiperContentTransitionProxy_serializer, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult_serializer, OnSwiperAnimationEndCallback, SwiperAnimationEvent_serializer, OnSwiperAnimationStartCallback, OnSwiperGestureSwipeCallback, SwiperContentTransitionProxy, SwiperContentWillScrollResult, SwiperAnimationEvent } from './../../component/swiper'
import { TextPickerResult_serializer, OnTextPickerChangeCallback, TextPickerEnterSelectedAreaCallback, TextPickerScrollStopCallback, TextPickerResult } from './../../component/textPicker'
import { TimePickerResult_serializer, OnTimePickerChangeCallback, TimePickerResult } from './../../component/timePicker'
import { UIExtensionProxy_serializer, UIExtensionProxy } from './../../component/uiExtensionComponent'
import { CheckBoxConfiguration_serializer, OnCheckboxChangeCallback, CheckBoxConfiguration } from './../../component/checkbox'
import { DataPanelConfiguration_serializer, DataPanelConfiguration } from './../../component/dataPanel'
import { default as DataProgressListener, default as unifiedDataChannel } from '@ohos.data.unifiedDataChannel'
import { unifiedDataChannel_ProgressInfo_serializer, unifiedDataChannel_UnifiedData_serializer } from './../ohos.data.unifiedDataChannel'
import { extractors } from '#handwritten'
import { GaugeConfiguration_serializer, GaugeConfiguration } from './../../component/gauge'
import { ImageCompleteCallback, ImageLoadResult_serializer, ImageLoadResult } from './../../component/imageSpan'
import { ImageErrorCallback, ImageError_serializer, ImageOnCompleteCallback, ImageCompleteEvent_serializer, ImageError, ImageCompleteEvent } from './../../component/image'
import { LoadingProgressConfiguration_serializer, LoadingProgressConfiguration } from './../../component/loadingProgress'
import { MenuItemConfiguration_serializer, OnSelectCallback, MenuItemConfiguration } from './../../component/select'
import { OnAlphabetIndexerPopupSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerSelectCallback } from './../../component/alphabetIndexer'
import { OnCheckboxGroupChangeCallback, CheckboxGroupResult_serializer, CheckboxGroupResult } from './../../component/checkboxgroup'
import { OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, SubmitEvent_serializer, OnTextSelectionChangeCallback, EnterKeyType, SubmitEvent } from './../../component/textInput'
import { OnFoldStatusChangeCallback, OnFoldStatusChangeInfo_serializer, OnHoverStatusChangeCallback, HoverEventParam_serializer, OnFoldStatusChangeInfo, HoverEventParam } from './../../component/folderStack'
import { OnRadioChangeCallback, RadioConfiguration_serializer, RadioConfiguration } from './../../component/radio'
import { OnRatingChangeCallback, RatingConfiguration_serializer, RatingConfiguration } from './../../component/rating'
import { OnScrollVisibleContentChangeCallback, VisibleListContentInfo_serializer, ScrollState, VisibleListContentInfo } from './../../component/list'
import { PasteButtonCallback, PasteButtonOnClickResult } from './../../component/pasteButton'
import { PluginErrorCallback, PluginErrorData_serializer, PluginErrorData } from './../../component/pluginComponent'
import { ProgressConfiguration_serializer, ProgressConfiguration } from './../../component/progress'
import { SaveButtonCallback, SaveButtonOnClickResult } from './../../component/saveButton'
import { SearchSubmitCallback } from './../../component/search'
import { SearchValueCallback } from './../searchOps'
import { SliderConfiguration_serializer, SliderTriggerChangeCallback, SliderChangeMode, SliderConfiguration } from './../../component/slider'
import { image_PixelMap_serializer } from './../ohos.multimedia.image'
import { TextAreaSubmitCallback } from './../../component/textArea'
import { TextClockConfiguration_serializer, TextClockConfiguration } from './../../component/textClock'
import { TextFieldValueCallback } from './../textFieldOps'
import { TextTimerConfiguration_serializer, TimerCallback, TextTimerConfiguration } from './../../component/textTimer'
import { ToggleConfiguration_serializer, ToggleConfiguration } from './../../component/toggle'
import { int32, float32, int64 } from '@koalaui/common'
import { CallbackTransformer } from './../../CallbackTransformer'
import { Resource as global_resource_Resource } from 'global.resource'
import { DrawContext as arkui_Graphics_DrawContext, Size } from '@arkui.Graphics'
import { HitTestMode, Edge, ScrollSource } from './../../component/enums'
import { MarqueeState } from './../../component/text'
import { CustomBuilder } from './../../component/builder'
import { RefreshStatus } from './../../component/refresh'
import { SwipeActionState } from './../../component/listItem'
import { default as image } from '@ohos.multimedia.image'
import { CallbackKind } from './CallbackKind'
export function deserializeAndCallAccessibilityActionInterceptCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as AccessibilityActionInterceptCallback)
    let action : AccessibilityAction = AccessibilityAction.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: AccessibilityActionInterceptResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -198060944, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: AccessibilityActionInterceptResult) => void) = continuationBufferClosure
    const callResult  = call(action)
    continuationResult(callResult)
}
export function deserializeAndCallAccessibilityCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as AccessibilityCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : AccessibilityHoverEvent = (AccessibilityHoverEvent_serializer.read(thisDeserializer) as AccessibilityHoverEvent)
    call(isHover, event)
}
export function deserializeAndCallAccessibilityFocusCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as AccessibilityFocusCallback)
    let isFocus : boolean = thisDeserializer.readBoolean()
    call(isFocus)
}
export function deserializeAndCallAccessibilityTransparentCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as AccessibilityTransparentCallback)
    let event : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    call(event)
}
export function deserializeAndCallButtonModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ButtonConfiguration = ButtonConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallButtonTriggerClickCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ButtonTriggerClickCallback)
    let xPos : double = thisDeserializer.readFloat64()
    let yPos : double = thisDeserializer.readFloat64()
    call(xPos, yPos)
}
export function deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: AccessibilityActionInterceptResult) => void))
    let value : AccessibilityActionInterceptResult = AccessibilityActionInterceptResult.fromValue(thisDeserializer.readInt32())
    call(value)
}
export function deserializeAndCallCallback_Area_Area_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((oldValue: Area,newValue: Area) => void))
    let oldValue : Area = Area_serializer.read(thisDeserializer)
    let newValue : Area = Area_serializer.read(thisDeserializer)
    call(oldValue, newValue)
}
export function deserializeAndCallCallback_Array_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Array<int32>, void>)
    const dataTmpBufLength : int32 = thisDeserializer.readInt32()
    let dataTmpBuf : Array<int32> = new Array<int32>(dataTmpBufLength)
    for (let dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++) {
        dataTmpBuf[dataTmpBufBufCounterI] = thisDeserializer.readInt32()
    }
    let data : Array<int32> = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_Array_Resource_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Array<global_resource_Resource>, void>)
    const dataTmpBufLength : int32 = thisDeserializer.readInt32()
    let dataTmpBuf : Array<global_resource_Resource> = new Array<global_resource_Resource>(dataTmpBufLength)
    for (let dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++) {
        dataTmpBuf[dataTmpBufBufCounterI] = global_resource_Resource_serializer.read(thisDeserializer)
    }
    let data : Array<global_resource_Resource> = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_Array_ResourceStr_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Array<arkui_component_units_ResourceStr>, void>)
    const dataTmpBufLength : int32 = thisDeserializer.readInt32()
    let dataTmpBuf : Array<arkui_component_units_ResourceStr> = new Array<arkui_component_units_ResourceStr>(dataTmpBufLength)
    for (let dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++) {
        const dataTmpBufTempBufUnionSelector : int32 = thisDeserializer.readInt8()
        let dataTmpBufTempBuf : string | arkui_component_units_Resource | undefined
        if (dataTmpBufTempBufUnionSelector == (0).toByte()) {
            dataTmpBufTempBuf = (thisDeserializer.readString() as string)
        } else if (dataTmpBufTempBufUnionSelector == (1).toByte()) {
            dataTmpBufTempBuf = global_resource_Resource_serializer.read(thisDeserializer)
        } else {
            throw new Error('One of the branches for dataTmpBufTempBuf has to be chosen through deserialisation.')
        }
        dataTmpBuf[dataTmpBufBufCounterI] = (dataTmpBufTempBuf as string | arkui_component_units_Resource)
    }
    let data : Array<arkui_component_units_ResourceStr> = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Array<string>, void>)
    const dataTmpBufLength : int32 = thisDeserializer.readInt32()
    let dataTmpBuf : Array<string> = new Array<string>(dataTmpBufLength)
    for (let dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++) {
        dataTmpBuf[dataTmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let data : Array<string> = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: Array<TextMenuItem>) => void))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<TextMenuItem> = new Array<TextMenuItem>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let value : Array<TextMenuItem> = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: Array<TouchTestInfo>) => TouchResult))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<TouchTestInfo> = new Array<TouchTestInfo>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = TouchTestInfo_serializer.read(thisDeserializer)
    }
    let value : Array<TouchTestInfo> = valueTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: TouchResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        TouchResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, -1269354333, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: TouchResult) => void) = continuationBufferClosure
    const callResult  = call(value)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_AxisEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<AxisEvent, void>)
    let data : AxisEvent = (AxisEvent_serializer.read(thisDeserializer) as AxisEvent)
    call(data)
}
export function deserializeAndCallCallback_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as (() => boolean))
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call()
    continuationResult(callResult)
}
export function deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((isHover: boolean,event: HoverEvent) => void))
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    call(isHover, event)
}
export function deserializeAndCallCallback_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<boolean, void>)
    let data : boolean = thisDeserializer.readBoolean()
    call(data)
}
export function deserializeAndCallCallback_Buffer_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: ArrayBuffer) => void))
    let value : ArrayBuffer = (thisDeserializer.readBuffer() as ArrayBuffer)
    call(value)
}
export function deserializeAndCallCallback_BusinessError_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((code: int32,message: string) => void))
    let code : int32 = thisDeserializer.readInt32()
    let message : string = (thisDeserializer.readString() as string)
    call(code, message)
}
export function deserializeAndCallCallback_ClickEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: ClickEvent) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    call(event)
}
export function deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: ComputedBarAttribute) => void))
    let value : ComputedBarAttribute = ComputedBarAttribute_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCallback_CopyEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<CopyEvent, void>)
    let data : CopyEvent = (CopyEvent_serializer.read(thisDeserializer) as CopyEvent)
    call(data)
}
export function deserializeAndCallCallback_CreateItem(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_CreateItem)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(index)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_CrownEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<CrownEvent, void>)
    let data : CrownEvent = (CrownEvent_serializer.read(thisDeserializer) as CrownEvent)
    call(data)
}
export function deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics))
    let measureInfo : CustomSpanMeasureInfo = CustomSpanMeasureInfo_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: CustomSpanMetrics):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        CustomSpanMetrics_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, -1129158393, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: CustomSpanMetrics) => void) = continuationBufferClosure
    const callResult  = call(measureInfo)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_CustomSpanMetrics_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: CustomSpanMetrics) => void))
    let value : CustomSpanMetrics = CustomSpanMetrics_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCallback_CutEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<CutEvent, void>)
    let data : CutEvent = (CutEvent_serializer.read(thisDeserializer) as CutEvent)
    call(data)
}
export function deserializeAndCallCallback_Date_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Date, void>)
    let data : Date = new Date(thisDeserializer.readInt64())
    call(data)
}
export function deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DeleteValue, boolean>)
    let data : DeleteValue = DeleteValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_DeleteValue_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DeleteValue, void>)
    let data : DeleteValue = DeleteValue_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DismissContentCoverAction, void>)
    let data : DismissContentCoverAction = DismissContentCoverAction_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DismissDialogAction, void>)
    let data : DismissDialogAction = (DismissDialogAction_serializer.read(thisDeserializer) as DismissDialogAction)
    call(data)
}
export function deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DismissPopupAction, void>)
    let data : DismissPopupAction = (DismissPopupAction_serializer.read(thisDeserializer) as DismissPopupAction)
    call(data)
}
export function deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<DismissSheetAction, void>)
    let data : DismissSheetAction = DismissSheetAction_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_DragEvent_Opt_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: DragEvent,extraParams?: string) => void))
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    call(event, extraParams)
}
export function deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((context: arkui_Graphics_DrawContext,drawInfo: CustomSpanDrawInfo) => void))
    let context : arkui_Graphics_DrawContext = (arkui_Graphics_DrawContext_serializer.read(thisDeserializer) as arkui_Graphics_DrawContext)
    let drawInfo : CustomSpanDrawInfo = CustomSpanDrawInfo_serializer.read(thisDeserializer)
    call(context, drawInfo)
}
export function deserializeAndCallCallback_DrawContext_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((drawContext: arkui_component_common_DrawContext) => void))
    let drawContext : arkui_component_common_DrawContext = (arkui_Graphics_DrawContext_serializer.read(thisDeserializer) as arkui_Graphics_DrawContext)
    call(drawContext)
}
export function deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<EditableTextChangeValue, boolean>)
    let data : EditableTextChangeValue = EditableTextChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_ErrorInformation_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<ErrorInformation, void>)
    let data : ErrorInformation = ErrorInformation_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_Extender_OnFinish(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_Extender_OnFinish)
    call()
}
export function deserializeAndCallCallback_Extender_OnProgress(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_Extender_OnProgress)
    let value : float = thisDeserializer.readFloat32()
    call(value)
}
export function deserializeAndCallCallback_F64_F64_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((totalOffsetX: double,totalOffsetY: double) => void))
    let totalOffsetX : double = thisDeserializer.readFloat64()
    let totalOffsetY : double = thisDeserializer.readFloat64()
    call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallCallback_F64_SliderChangeMode_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: double,mode: SliderChangeMode) => void))
    let value : double = thisDeserializer.readFloat64()
    let mode : SliderChangeMode = SliderChangeMode.fromValue(thisDeserializer.readInt32())
    call(value, mode)
}
export function deserializeAndCallCallback_F64_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<double, void>)
    let data : double = thisDeserializer.readFloat64()
    call(data)
}
export function deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<FocusAxisEvent, void>)
    let data : FocusAxisEvent = (FocusAxisEvent_serializer.read(thisDeserializer) as FocusAxisEvent)
    call(data)
}
export function deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<FormCallbackInfo, void>)
    let data : FormCallbackInfo = FormCallbackInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<FullscreenInfo, void>)
    let data : FullscreenInfo = FullscreenInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_GestureEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<GestureEvent, void>)
    let data : GestureEvent = (GestureEvent_serializer.read(thisDeserializer) as GestureEvent)
    call(data)
}
export function deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult))
    let gestureInfo : GestureInfo = GestureInfo_serializer.read(thisDeserializer)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: GestureJudgeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, 294634328, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: GestureJudgeResult) => void) = continuationBufferClosure
    const callResult  = call(gestureInfo, event)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: GestureJudgeResult) => void))
    let value : GestureJudgeResult = GestureJudgeResult.fromValue(thisDeserializer.readInt32())
    call(value)
}
export function deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: GestureRecognizer) => void))
    let value : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    call(value)
}
export function deserializeAndCallCallback_HitTestMode_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: HitTestMode) => void))
    let value : HitTestMode = HitTestMode.fromValue(thisDeserializer.readInt32())
    call(value)
}
export function deserializeAndCallCallback_HoverEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<HoverEvent, void>)
    let data : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    call(data)
}
export function deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((index: int32,offset: double) => ComputedBarAttribute))
    let index : int32 = thisDeserializer.readInt32()
    let offset : double = thisDeserializer.readFloat64()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: ComputedBarAttribute):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        ComputedBarAttribute_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 360019859, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: ComputedBarAttribute) => void) = continuationBufferClosure
    const callResult  = call(index, offset)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_I32_I32_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((from: int32,to: int32) => boolean))
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(from, to)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_I32_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((start: int32,end: int32,center: int32) => void))
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    let center : int32 = thisDeserializer.readInt32()
    call(start, end, center)
}
export function deserializeAndCallCallback_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((first: int32,last: int32) => void))
    let first : int32 = thisDeserializer.readInt32()
    let last : int32 = thisDeserializer.readInt32()
    call(first, last)
}
export function deserializeAndCallCallback_I32_Tuple_I32_I32(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((index: int32) => [ int32, int32 ]))
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: [ int32, int32 ]):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        const value_0  = value[0];
        continuationBufferBufArgsSerializer.writeInt32(value_0);
        const value_1  = value[1];
        continuationBufferBufArgsSerializer.writeInt32(value_1);
        InteropNativeModule._CallCallbackSync(10, 1077709751, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: [ int32, int32 ]) => void) = continuationBufferClosure
    const callResult  = call(index)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((index: int32) => [ int32, int32, int32, int32 ]))
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: [ int32, int32, int32, int32 ]):void => {
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
        InteropNativeModule._CallCallbackSync(10, 1986543351, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: [ int32, int32, int32, int32 ]) => void) = continuationBufferClosure
    const callResult  = call(index)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<int32, void>)
    let data : int32 = thisDeserializer.readInt32()
    call(data)
}
export function deserializeAndCallCallback_I64_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<int64, void>)
    let data : int64 = thisDeserializer.readInt64()
    call(data)
}
export function deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<InsertValue, boolean>)
    let data : InsertValue = InsertValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_InsertValue_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<InsertValue, void>)
    let data : InsertValue = InsertValue_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    let insertIndex : int32 = thisDeserializer.readInt32()
    let isSuccess : boolean = thisDeserializer.readBoolean()
    call(event, itemIndex, insertIndex, isSuccess)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    let insertIndex : int32 = thisDeserializer.readInt32()
    call(event, itemIndex, insertIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: ItemDragInfo,itemIndex: int32) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    call(event, itemIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: ItemDragInfo) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<KeyEvent, boolean>)
    let data : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_KeyEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<KeyEvent, void>)
    let data : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    call(data)
}
export function deserializeAndCallCallback_Length_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Length, void>)
    const dataTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let dataTmpBuf : string | double | arkui_component_units_Resource | undefined
    if (dataTmpBufUnionSelector == (0).toByte()) {
        dataTmpBuf = (thisDeserializer.readString() as string)
    } else if (dataTmpBufUnionSelector == (1).toByte()) {
        dataTmpBuf = thisDeserializer.readFloat64()
    } else if (dataTmpBufUnionSelector == (2).toByte()) {
        dataTmpBuf = global_resource_Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error('One of the branches for dataTmpBuf has to be chosen through deserialisation.')
    }
    let data : Length = (dataTmpBuf as string | double | arkui_component_units_Resource)
    call(data)
}
export function deserializeAndCallCallback_Map_String_Opt_Object(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ohos_base_Callback<Record<string, RecordData>>)
    const dataTmpBufSizeVar : int32 = thisDeserializer.readInt32()
    let dataTmpBuf : Record<string, RecordData> = new Record<string, RecordData>()
    // TODO: TS map resize
    for (let dataTmpBufIVar = 0; dataTmpBufIVar < dataTmpBufSizeVar; dataTmpBufIVar++) {
        const dataTmpBufKeyVar : string = (thisDeserializer.readString() as string)
        const dataTmpBufValueVarTempBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
        let dataTmpBufValueVarTempBuf : Object | null | undefined = undefined
        if ((dataTmpBufValueVarTempBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dataTmpBufValueVarTempBuf = (thisDeserializer.readObject() as object)
        }
        const dataTmpBufValueVar : RecordData = dataTmpBufValueVarTempBuf
        dataTmpBuf.set(dataTmpBufKeyVar, dataTmpBufValueVar)
    }
    let data : Record<string, RecordData> = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_MarqueeState_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<MarqueeState, void>)
    let data : MarqueeState = MarqueeState.fromValue(thisDeserializer.readInt32())
    call(data)
}
export function deserializeAndCallCallback_MouseEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: MouseEvent) => void))
    let event : MouseEvent = (MouseEvent_serializer.read(thisDeserializer) as MouseEvent)
    call(event)
}
export function deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: NativeEmbedDataInfo) => void))
    let event : NativeEmbedDataInfo = NativeEmbedDataInfo_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: NativeEmbedTouchInfo) => void))
    let event : NativeEmbedTouchInfo = NativeEmbedTouchInfo_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<NavDestinationActiveReason, void>)
    let data : NavDestinationActiveReason = NavDestinationActiveReason.fromValue(thisDeserializer.readInt32())
    call(data)
}
export function deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<NavDestinationContext, void>)
    let data : NavDestinationContext = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    call(data)
}
export function deserializeAndCallCallback_NavigationMode_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((mode: NavigationMode) => void))
    let mode : NavigationMode = NavigationMode.fromValue(thisDeserializer.readInt32())
    call(mode)
}
export function deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((titleMode: NavigationTitleMode) => void))
    let titleMode : NavigationTitleMode = NavigationTitleMode.fromValue(thisDeserializer.readInt32())
    call(titleMode)
}
export function deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((transitionProxy: NavigationTransitionProxy) => void))
    let transitionProxy : NavigationTransitionProxy = (NavigationTransitionProxy_serializer.read(thisDeserializer) as NavigationTransitionProxy)
    call(transitionProxy)
}
export function deserializeAndCallCallback_Number_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<number, void>)
    let data : number = (thisDeserializer.readNumber() as number)
    call(data)
}
export function deserializeAndCallCallback_Object_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Object, void>)
    let data : Object = (thisDeserializer.readObject() as object)
    call(data)
}
export function deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnAlertEvent, boolean>)
    let data : OnAlertEvent = OnAlertEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnAudioStateChangedEvent, void>)
    let data : OnAudioStateChangedEvent = OnAudioStateChangedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean>)
    let data : OnBeforeUnloadEvent = OnBeforeUnloadEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnClientAuthenticationEvent, void>)
    let data : OnClientAuthenticationEvent = OnClientAuthenticationEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnConfirmEvent, boolean>)
    let data : OnConfirmEvent = OnConfirmEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnConsoleEvent, boolean>)
    let data : OnConsoleEvent = OnConsoleEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnContextMenuShowEvent, boolean>)
    let data : OnContextMenuShowEvent = OnContextMenuShowEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnDataResubmittedEvent, void>)
    let data : OnDataResubmittedEvent = OnDataResubmittedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnDestory_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_OnDestory_Void)
    let nodeId : int64 = thisDeserializer.readInt64()
    call(nodeId)
}
export function deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnDownloadStartEvent, void>)
    let data : OnDownloadStartEvent = OnDownloadStartEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnErrorReceiveEvent, void>)
    let data : OnErrorReceiveEvent = OnErrorReceiveEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnFaviconReceivedEvent, void>)
    let data : OnFaviconReceivedEvent = OnFaviconReceivedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void>)
    let data : OnFirstContentfulPaintEvent = OnFirstContentfulPaintEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnGeolocationShowEvent, void>)
    let data : OnGeolocationShowEvent = OnGeolocationShowEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean>)
    let data : OnHttpAuthRequestEvent = OnHttpAuthRequestEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void>)
    let data : OnHttpErrorReceiveEvent = OnHttpErrorReceiveEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null>)
    let data : OnInterceptRequestEvent = OnInterceptRequestEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: WebResourceResponse | null):void => {
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
        InteropNativeModule._CallCallbackSync(10, -1580893022, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: WebResourceResponse | null) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnLoadFinishedEvent, void>)
    let data : OnLoadFinishedEvent = OnLoadFinishedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnLoadInterceptEvent, boolean>)
    let data : OnLoadInterceptEvent = OnLoadInterceptEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnLoadStartedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnLoadStartedEvent, void>)
    let data : OnLoadStartedEvent = OnLoadStartedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_onMeasureSize_SizeResult)
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
    const continuationBufferClosure  = (value: SizeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        SizeResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, -1105842237, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: SizeResult) => void) = continuationBufferClosure
    const callResult  = call(selfLayoutInfo, children, constraint)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnMoveFromTo(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_OnMoveFromTo)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    call(from, to)
}
export function deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnOverScrollEvent, void>)
    let data : OnOverScrollEvent = OnOverScrollEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnPageBeginEvent, void>)
    let data : OnPageBeginEvent = OnPageBeginEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnPageEndEvent, void>)
    let data : OnPageEndEvent = OnPageEndEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnPageVisibleEvent, void>)
    let data : OnPageVisibleEvent = OnPageVisibleEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnPermissionRequestEvent, void>)
    let data : OnPermissionRequestEvent = OnPermissionRequestEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_onPlaceChildren_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_onPlaceChildren_Void)
    let selfLayoutInfo : GeometryInfo = GeometryInfo_serializer.read(thisDeserializer)
    const childrenTmpBufLength : int32 = thisDeserializer.readInt32()
    let childrenTmpBuf : Array<Layoutable> = new Array<Layoutable>(childrenTmpBufLength)
    for (let childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf[childrenTmpBufBufCounterI] = (Layoutable_serializer.read(thisDeserializer) as Layoutable)
    }
    let children : Array<Layoutable> = childrenTmpBuf
    let constraint : ConstraintSizeOptions = ConstraintSizeOptions_serializer.read(thisDeserializer)
    call(selfLayoutInfo, children, constraint)
}
export function deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnProgressChangeEvent, void>)
    let data : OnProgressChangeEvent = OnProgressChangeEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnPromptEvent, boolean>)
    let data : OnPromptEvent = OnPromptEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void>)
    let data : OnRefreshAccessedHistoryEvent = OnRefreshAccessedHistoryEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnRenderExitedEvent, void>)
    let data : OnRenderExitedEvent = OnRenderExitedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnResourceLoadEvent, void>)
    let data : OnResourceLoadEvent = OnResourceLoadEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnScaleChangeEvent, void>)
    let data : OnScaleChangeEvent = OnScaleChangeEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void>)
    let data : OnScreenCaptureRequestEvent = OnScreenCaptureRequestEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnScrollEvent, void>)
    let data : OnScrollEvent = OnScrollEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: OnScrollFrameBeginHandlerResult) => void))
    let value : OnScrollFrameBeginHandlerResult = OnScrollFrameBeginHandlerResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnSearchResultReceiveEvent, void>)
    let data : OnSearchResultReceiveEvent = OnSearchResultReceiveEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean>)
    let data : OnShowFileSelectorEvent = OnShowFileSelectorEvent_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void>)
    let data : OnSslErrorEventReceiveEvent = OnSslErrorEventReceiveEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnTitleReceiveEvent, void>)
    let data : OnTitleReceiveEvent = OnTitleReceiveEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void>)
    let data : OnTouchIconUrlReceivedEvent = OnTouchIconUrlReceivedEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<OnWindowNewEvent, void>)
    let data : OnWindowNewEvent = OnWindowNewEvent_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: Array<NavDestinationTransition> | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : Array<NavDestinationTransition> | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const valueTmpBufOptLength : int32 = thisDeserializer.readInt32()
        let valueTmpBufOpt : Array<NavDestinationTransition> = new Array<NavDestinationTransition>(valueTmpBufOptLength)
        for (let valueTmpBufOptBufCounterI = 0; valueTmpBufOptBufCounterI < valueTmpBufOptLength; valueTmpBufOptBufCounterI++) {
            valueTmpBufOpt[valueTmpBufOptBufCounterI] = NavDestinationTransition_serializer.read(thisDeserializer)
        }
        valueTmpBuf = valueTmpBufOpt
    }
    let value : Array<NavDestinationTransition> | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((error?: Array<string> | undefined) => void))
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let errorTmpBuf : Array<string> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBufOptLength : int32 = thisDeserializer.readInt32()
        let errorTmpBufOpt : Array<string> = new Array<string>(errorTmpBufOptLength)
        for (let errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength; errorTmpBufOptBufCounterI++) {
            errorTmpBufOpt[errorTmpBufOptBufCounterI] = (thisDeserializer.readString() as string)
        }
        errorTmpBuf = errorTmpBufOpt
    }
    let error : Array<string> | undefined = errorTmpBuf
    call(error)
}
export function deserializeAndCallCallback_Opt_CustomNodeBuilder_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: CustomBuilder | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : CustomBuilder | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const valueTmpBufOptBufResource : CallbackResource = thisDeserializer.readCallbackResource()
        const valueTmpBufOptBufCall : KPointer = thisDeserializer.readPointer()
        const valueTmpBufOptBufCallSync : KPointer = thisDeserializer.readPointer()
        const valueTmpBufOptClosure  = ():void => {
            const valueTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
            valueTmpBufOptBufArgsSerializer.writeInt32(valueTmpBufOptBufResource.resourceId);
            valueTmpBufOptBufArgsSerializer.writePointer(valueTmpBufOptBufCall);
            valueTmpBufOptBufArgsSerializer.writePointer(valueTmpBufOptBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -1834072896, valueTmpBufOptBufArgsSerializer.asBuffer(), valueTmpBufOptBufArgsSerializer.length());
            valueTmpBufOptBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(valueTmpBufOptClosure, valueTmpBufOptBufResource)
        valueTmpBuf = valueTmpBufOptClosure
    }
    let value : CustomBuilder | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: NavigationAnimatedTransition | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : NavigationAnimatedTransition | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = NavigationAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : NavigationAnimatedTransition | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_Object_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<Object | null | undefined, void>)
    const dataTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let dataTmpBuf : Object | null | undefined = undefined
    if ((dataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        dataTmpBuf = (thisDeserializer.readObject() as object)
    }
    let data : Object | null | undefined = dataTmpBuf
    call(data)
}
export function deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: OffsetResult | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : OffsetResult | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = OffsetResult_serializer.read(thisDeserializer)
    }
    let value : OffsetResult | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: ScrollResult | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : ScrollResult | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (ScrollResult_serializer.read(thisDeserializer) as ScrollResult)
    }
    let value : ScrollResult | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value?: StyledString | undefined,error?: Array<string> | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : StyledString | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (StyledString_serializer.read(thisDeserializer) as StyledString)
    }
    let value : StyledString | undefined = valueTmpBuf
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let errorTmpBuf : Array<string> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBufOptLength : int32 = thisDeserializer.readInt32()
        let errorTmpBufOpt : Array<string> = new Array<string>(errorTmpBufOptLength)
        for (let errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength; errorTmpBufOptBufCounterI++) {
            errorTmpBufOpt[errorTmpBufOptBufCounterI] = (thisDeserializer.readString() as string)
        }
        errorTmpBuf = errorTmpBufOpt
    }
    let error : Array<string> | undefined = errorTmpBuf
    call(value, error)
}
export function deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: TabContentAnimatedTransition | undefined) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : TabContentAnimatedTransition | undefined = undefined
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = TabContentAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : TabContentAnimatedTransition | undefined = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: WebResourceResponse | null) => void))
    const valueTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let valueTmpBuf : WebResourceResponse | null = null
    if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        valueTmpBuf = (WebResourceResponse_serializer.read(thisDeserializer) as WebResourceResponse)
    }
    let value : WebResourceResponse | null = valueTmpBuf
    call(value)
}
export function deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<PlaybackInfo, void>)
    let data : PlaybackInfo = PlaybackInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_Pointer_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: KPointer) => void))
    let value : KPointer = thisDeserializer.readPointer()
    call(value)
}
export function deserializeAndCallCallback_PopInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<PopInfo, void>)
    let data : PopInfo = PopInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<PreDragStatus, void>)
    let data : PreDragStatus = PreDragStatus.fromValue(thisDeserializer.readInt32())
    call(data)
}
export function deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<PreparedInfo, void>)
    let data : PreparedInfo = PreparedInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_RangeUpdate(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_RangeUpdate)
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    let cacheStart : int32 = thisDeserializer.readInt32()
    let cacheEnd : int32 = thisDeserializer.readInt32()
    let isLoop : boolean = thisDeserializer.readBoolean()
    call(start, end, cacheStart, cacheEnd, isLoop)
}
export function deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((state: RefreshStatus) => void))
    let state : RefreshStatus = RefreshStatus.fromValue(thisDeserializer.readInt32())
    call(state)
}
export function deserializeAndCallCallback_Resource_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<global_resource_Resource, void>)
    let data : global_resource_Resource = global_resource_Resource_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_ResourceStr_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<arkui_component_units_ResourceStr, void>)
    const dataTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let dataTmpBuf : string | arkui_component_units_Resource | undefined
    if (dataTmpBufUnionSelector == (0).toByte()) {
        dataTmpBuf = (thisDeserializer.readString() as string)
    } else if (dataTmpBufUnionSelector == (1).toByte()) {
        dataTmpBuf = global_resource_Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error('One of the branches for dataTmpBuf has to be chosen through deserialisation.')
    }
    let data : arkui_component_units_ResourceStr = (dataTmpBuf as string | arkui_component_units_Resource)
    call(data)
}
export function deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorChangeValue, boolean>)
    let data : RichEditorChangeValue = RichEditorChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorDeleteValue, boolean>)
    let data : RichEditorDeleteValue = RichEditorDeleteValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorInsertValue, boolean>)
    let data : RichEditorInsertValue = RichEditorInsertValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorRange, void>)
    let data : RichEditorRange = RichEditorRange_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorSelection, void>)
    let data : RichEditorSelection = RichEditorSelection_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<RichEditorTextSpanResult, void>)
    let data : RichEditorTextSpanResult = RichEditorTextSpanResult_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((sheetDismiss: SheetDismiss) => void))
    let sheetDismiss : SheetDismiss = SheetDismiss_serializer.read(thisDeserializer)
    call(sheetDismiss)
}
export function deserializeAndCallCallback_SheetType_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<SheetType, void>)
    let data : SheetType = SheetType.fromValue(thisDeserializer.readInt32())
    call(data)
}
export function deserializeAndCallCallback_Size_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_Size_Void)
    let size : Size = Size_serializer.read(thisDeserializer)
    call(size)
}
export function deserializeAndCallCallback_SizeResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: SizeResult) => void))
    let value : SizeResult = SizeResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<SpringBackAction, void>)
    let data : SpringBackAction = (SpringBackAction_serializer.read(thisDeserializer) as SpringBackAction)
    call(data)
}
export function deserializeAndCallCallback_StateStylesChange(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as Callback_StateStylesChange)
    let currentState : int32 = thisDeserializer.readInt32()
    call(currentState)
}
export function deserializeAndCallCallback_String(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ohos_base_Callback<string>)
    let data : string = (thisDeserializer.readString() as string)
    call(data)
}
export function deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: string,event: PasteEvent) => void))
    let value : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = (PasteEvent_serializer.read(thisDeserializer) as PasteEvent)
    call(value, event)
}
export function deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((surfaceId: string,rect: SurfaceRect) => void))
    let surfaceId : string = (thisDeserializer.readString() as string)
    let rect : SurfaceRect = SurfaceRect_serializer.read(thisDeserializer)
    call(surfaceId, rect)
}
export function deserializeAndCallCallback_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<string, void>)
    let data : string = (thisDeserializer.readString() as string)
    call(data)
}
export function deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<StyledStringChangeValue, boolean>)
    let data : StyledStringChangeValue = StyledStringChangeValue_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((state: SwipeActionState) => void))
    let state : SwipeActionState = SwipeActionState.fromValue(thisDeserializer.readInt32())
    call(state)
}
export function deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<SwiperContentTransitionProxy, void>)
    let data : SwiperContentTransitionProxy = (SwiperContentTransitionProxy_serializer.read(thisDeserializer) as SwiperContentTransitionProxy)
    call(data)
}
export function deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<TabContentTransitionProxy, void>)
    let data : TabContentTransitionProxy = (TabContentTransitionProxy_serializer.read(thisDeserializer) as TabContentTransitionProxy)
    call(data)
}
export function deserializeAndCallCallback_TerminationInfo(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ohos_base_Callback<TerminationInfo>)
    let data : TerminationInfo = TerminationInfo_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<TextPickerResult, void>)
    let data : TextPickerResult = TextPickerResult_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_TextRange_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<TextRange, void>)
    let data : TextRange = TextRange_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<TimePickerResult, void>)
    let data : TimePickerResult = TimePickerResult_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<TouchEvent, HitTestMode>)
    let data : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: HitTestMode):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, -1849282769, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: HitTestMode) => void) = continuationBufferClosure
    const callResult  = call(data)
    continuationResult(callResult)
}
export function deserializeAndCallCallback_TouchEvent_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: TouchEvent) => void))
    let event : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    call(event)
}
export function deserializeAndCallCallback_TouchResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: TouchResult) => void))
    let value : TouchResult = TouchResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: [ int32, int32, int32, int32 ]) => void))
    const valueTmpBufValue0 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue1 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue2 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue3 : int32 = thisDeserializer.readInt32()
    let value : [ int32, int32, int32, int32 ] = ([valueTmpBufValue0, valueTmpBufValue1, valueTmpBufValue2, valueTmpBufValue3] as [ int32, int32, int32, int32 ])
    call(value)
}
export function deserializeAndCallCallback_Tuple_I32_I32_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: [ int32, int32 ]) => void))
    const valueTmpBufValue0 : int32 = thisDeserializer.readInt32()
    const valueTmpBufValue1 : int32 = thisDeserializer.readInt32()
    let value : [ int32, int32 ] = ([valueTmpBufValue0, valueTmpBufValue1] as [ int32, int32 ])
    call(value)
}
export function deserializeAndCallCallback_UIExtensionProxy(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ohos_base_Callback<UIExtensionProxy>)
    let data : UIExtensionProxy = (UIExtensionProxy_serializer.read(thisDeserializer) as UIExtensionProxy)
    call(data)
}
export function deserializeAndCallCallback_Union_CustomNodeBuilder_DragItemInfo_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: CustomBuilder | DragItemInfo) => void))
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : CustomBuilder | DragItemInfo | undefined
    if (valueTmpBufUnionSelector == (0).toByte()) {
        const valueTmpBufBufUBufResource : CallbackResource = thisDeserializer.readCallbackResource()
        const valueTmpBufBufUBufCall : KPointer = thisDeserializer.readPointer()
        const valueTmpBufBufUBufCallSync : KPointer = thisDeserializer.readPointer()
        const valueTmpBufBufUClosure  = ():void => {
            const valueTmpBufBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
            valueTmpBufBufUBufArgsSerializer.writeInt32(valueTmpBufBufUBufResource.resourceId);
            valueTmpBufBufUBufArgsSerializer.writePointer(valueTmpBufBufUBufCall);
            valueTmpBufBufUBufArgsSerializer.writePointer(valueTmpBufBufUBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -1834072896, valueTmpBufBufUBufArgsSerializer.asBuffer(), valueTmpBufBufUBufArgsSerializer.length());
            valueTmpBufBufUBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(valueTmpBufBufUClosure, valueTmpBufBufUBufResource)
        valueTmpBuf = valueTmpBufBufUClosure
    } else if (valueTmpBufUnionSelector == (1).toByte()) {
        valueTmpBuf = DragItemInfo_serializer.read(thisDeserializer)
    } else {
        throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
    }
    let value : CustomBuilder | DragItemInfo = (valueTmpBuf as CustomBuilder | DragItemInfo)
    call(value)
}
export function deserializeAndCallCallback_UserDataSpan_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: StyledStringMarshallingValue) => void))
    let value : StyledStringMarshallingValue = (thisDeserializer.readObject() as UserDataSpan)
    call(value)
}
export function deserializeAndCallCallback_Void_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as arkui_component_common_Callback<void, void>)
    call(undefined)
}
export function deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: WebKeyboardOptions) => void))
    let value : WebKeyboardOptions = WebKeyboardOptions_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallCheckBoxModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : CheckBoxConfiguration = CheckBoxConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallContentDidScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ContentDidScrollCallback)
    let selectedIndex : int32 = thisDeserializer.readInt32()
    let index : int32 = thisDeserializer.readInt32()
    let position : double = thisDeserializer.readFloat64()
    let mainAxisLength : double = thisDeserializer.readFloat64()
    call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallContentWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ContentWillScrollCallback)
    let result : SwiperContentWillScrollResult = SwiperContentWillScrollResult_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(result)
    continuationResult(callResult)
}
export function deserializeAndCallCustomNodeBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as CustomNodeBuilder)
    let parentNode : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode)
    continuationResult(callResult)
}
export function deserializeAndCallDataPanelModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : DataPanelConfiguration = DataPanelConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallDataProgressListener(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as unifiedDataChannel.DataProgressListener)
    let progressInfo : unifiedDataChannel.ProgressInfo = unifiedDataChannel_ProgressInfo_serializer.read(thisDeserializer)
    const dataTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let dataTmpBuf : unifiedDataChannel.UnifiedData | null = null
    if ((dataTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        dataTmpBuf = (unifiedDataChannel_UnifiedData_serializer.read(thisDeserializer) as unifiedDataChannel.UnifiedData)
    }
    let data : unifiedDataChannel.UnifiedData | null = dataTmpBuf
    call(progressInfo, data)
}
export function deserializeAndCallEditableTextOnChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as EditableTextOnChangeCallback)
    let value : string = (thisDeserializer.readString() as string)
    const previewTextTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let previewTextTmpBuf : PreviewText | undefined = undefined
    if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        previewTextTmpBuf = PreviewText_serializer.read(thisDeserializer)
    }
    let previewText : PreviewText | undefined = previewTextTmpBuf
    const optionsTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let optionsTmpBuf : TextChangeOptions | undefined = undefined
    if ((optionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        optionsTmpBuf = TextChangeOptions_serializer.read(thisDeserializer)
    }
    let options : TextChangeOptions | undefined = optionsTmpBuf
    call(value, previewText, options)
}
export function deserializeAndCallErrorCallback_BusinessErrorInterface_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ErrorCallback<BusinessError<void>>)
    const errTmpBufDeserialized : BusinessErrorInterface<void> = BusinessErrorInterface_Void_serializer.read(thisDeserializer)
    let err : BusinessError<void> = extractors.transform_Ark_BusinessErrorInterface_Void_to_Ark_BusinessError_Void(errTmpBufDeserialized)
    call(err)
}
export function deserializeAndCallFrameCallbackHandler(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as FrameCallbackHandler)
    let arg : int64 = thisDeserializer.readInt64()
    call(arg)
}
export function deserializeAndCallGaugeModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: GaugeConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : GaugeConfiguration = GaugeConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallGestureEventHandler(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as GestureEventHandler)
    let event : GestureEvent = (GestureEvent_serializer.read(thisDeserializer) as GestureEvent)
    call(event)
}
export function deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as GestureRecognizerJudgeBeginCallback)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    let current : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    const recognizersTmpBufLength : int32 = thisDeserializer.readInt32()
    let recognizersTmpBuf : Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizersTmpBufLength)
    for (let recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength; recognizersTmpBufBufCounterI++) {
        recognizersTmpBuf[recognizersTmpBufBufCounterI] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let recognizers : Array<GestureRecognizer> = recognizersTmpBuf
    const touchRecognizersTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let touchRecognizersTmpBuf : Array<TouchRecognizer> | undefined = undefined
    if ((touchRecognizersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const touchRecognizersTmpBufOptLength : int32 = thisDeserializer.readInt32()
        let touchRecognizersTmpBufOpt : Array<TouchRecognizer> = new Array<TouchRecognizer>(touchRecognizersTmpBufOptLength)
        for (let touchRecognizersTmpBufOptBufCounterI = 0; touchRecognizersTmpBufOptBufCounterI < touchRecognizersTmpBufOptLength; touchRecognizersTmpBufOptBufCounterI++) {
            touchRecognizersTmpBufOpt[touchRecognizersTmpBufOptBufCounterI] = (TouchRecognizer_serializer.read(thisDeserializer) as TouchRecognizer)
        }
        touchRecognizersTmpBuf = touchRecognizersTmpBufOpt
    }
    let touchRecognizers : Array<TouchRecognizer> | undefined = touchRecognizersTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: GestureJudgeResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32(value.valueOf());
        InteropNativeModule._CallCallbackSync(10, 294634328, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: GestureJudgeResult) => void) = continuationBufferClosure
    const callResult  = call(event, current, recognizers, touchRecognizers)
    continuationResult(callResult)
}
export function deserializeAndCallHoverCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as HoverCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    call(isHover, event)
}
export function deserializeAndCallImageCompleteCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ImageCompleteCallback)
    let result : ImageLoadResult = ImageLoadResult_serializer.read(thisDeserializer)
    call(result)
}
export function deserializeAndCallImageErrorCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ImageErrorCallback)
    let error : ImageError = ImageError_serializer.read(thisDeserializer)
    call(error)
}
export function deserializeAndCallImageOnCompleteCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ImageOnCompleteCallback)
    const loadEventTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let loadEventTmpBuf : ImageCompleteEvent | undefined = undefined
    if ((loadEventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        loadEventTmpBuf = ImageCompleteEvent_serializer.read(thisDeserializer)
    }
    let loadEvent : ImageCompleteEvent | undefined = loadEventTmpBuf
    call(loadEvent)
}
export function deserializeAndCallInterceptionModeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as InterceptionModeCallback)
    let mode : NavigationMode = NavigationMode.fromValue(thisDeserializer.readInt32())
    call(mode)
}
export function deserializeAndCallInterceptionShowCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as InterceptionShowCallback)
    const fromTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let fromTmpBuf : NavDestinationContext | NavBar | undefined
    if (fromTmpBufUnionSelector == (0).toByte()) {
        fromTmpBuf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    } else if (fromTmpBufUnionSelector == (1).toByte()) {
        fromTmpBuf = (thisDeserializer.readString() as string)
    } else {
        throw new Error('One of the branches for fromTmpBuf has to be chosen through deserialisation.')
    }
    let from : NavDestinationContext | NavBar = (fromTmpBuf as NavDestinationContext | NavBar)
    const toTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let toTmpBuf : NavDestinationContext | NavBar | undefined
    if (toTmpBufUnionSelector == (0).toByte()) {
        toTmpBuf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    } else if (toTmpBufUnionSelector == (1).toByte()) {
        toTmpBuf = (thisDeserializer.readString() as string)
    } else {
        throw new Error('One of the branches for toTmpBuf has to be chosen through deserialisation.')
    }
    let to : NavDestinationContext | NavBar = (toTmpBuf as NavDestinationContext | NavBar)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    let isAnimated : boolean = thisDeserializer.readBoolean()
    call(from, to, operation, isAnimated)
}
export function deserializeAndCallLoadingProgressModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : LoadingProgressConfiguration = LoadingProgressConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallMenuCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as MenuCallback)
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    call(start, end)
}
export function deserializeAndCallMenuItemModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : MenuItemConfiguration = (MenuItemConfiguration_serializer.read(thisDeserializer) as MenuItemConfiguration)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallMenuOnAppearCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as MenuOnAppearCallback)
    let start : int32 = thisDeserializer.readInt32()
    let end : int32 = thisDeserializer.readInt32()
    call(start, end)
}
export function deserializeAndCallModifierKeyStateGetter(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ModifierKeyStateGetter)
    const keysTmpBufLength : int32 = thisDeserializer.readInt32()
    let keysTmpBuf : Array<string> = new Array<string>(keysTmpBufLength)
    for (let keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++) {
        keysTmpBuf[keysTmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let keys : Array<string> = keysTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(keys)
    continuationResult(callResult)
}
export function deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as NavDestinationTransitionDelegate)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    let isEnter : boolean = thisDeserializer.readBoolean()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: Array<NavDestinationTransition> | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, 556017751, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: Array<NavDestinationTransition> | undefined) => void) = continuationBufferClosure
    const callResult  = call(operation, isEnter)
    continuationResult(callResult)
}
export function deserializeAndCallNavExtender_CreateNavDestination(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as NavExtender_CreateNavDestination)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(index)
    continuationResult(callResult)
}
export function deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as NavExtender_OnUpdateStack)
    call()
}
export function deserializeAndCallNodeContainerOpsOnTouchCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as NodeContainerOpsOnTouchCallback)
    let event : TouchEvent = (TouchEvent_serializer.read(thisDeserializer) as TouchEvent)
    call(event)
}
export function deserializeAndCallOnAdsBlockedCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnAdsBlockedCallback)
    let details : AdsBlockedDetails = AdsBlockedDetails_serializer.read(thisDeserializer)
    call(details)
}
export function deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnAlphabetIndexerPopupSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    call(index)
}
export function deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnAlphabetIndexerRequestPopupDataCallback)
    let index : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: Array<string>):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32((value.length).toInt());
        for (let valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
            const valueTmpElement : string = value[valueCounterI];
            continuationBufferBufArgsSerializer.writeString(valueTmpElement);
        }
        InteropNativeModule._CallCallbackSync(10, 1639582720, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: Array<string>) => void) = continuationBufferClosure
    const callResult  = call(index)
    continuationResult(callResult)
}
export function deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnAlphabetIndexerSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    call(index)
}
export function deserializeAndCallOnCheckboxChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnCheckboxChangeCallback)
    let value : boolean = thisDeserializer.readBoolean()
    call(value)
}
export function deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnCheckboxGroupChangeCallback)
    let value : CheckboxGroupResult = CheckboxGroupResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallOnContentScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnContentScrollCallback)
    let totalOffsetX : double = thisDeserializer.readFloat64()
    let totalOffsetY : double = thisDeserializer.readFloat64()
    call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallOnContextMenuHideCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnContextMenuHideCallback)
    call()
}
export function deserializeAndCallOnCreateMenuCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnCreateMenuCallback)
    const menuItemsTmpBufLength : int32 = thisDeserializer.readInt32()
    let menuItemsTmpBuf : Array<TextMenuItem> = new Array<TextMenuItem>(menuItemsTmpBufLength)
    for (let menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength; menuItemsTmpBufBufCounterI++) {
        menuItemsTmpBuf[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let menuItems : Array<TextMenuItem> = menuItemsTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: Array<TextMenuItem>):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeInt32((value.length).toInt());
        for (let valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
            const valueTmpElement : TextMenuItem = value[valueCounterI];
            TextMenuItem_serializer.write(continuationBufferBufArgsSerializer, valueTmpElement);
        }
        InteropNativeModule._CallCallbackSync(10, -1010549102, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: Array<TextMenuItem>) => void) = continuationBufferClosure
    const callResult  = call(menuItems)
    continuationResult(callResult)
}
export function deserializeAndCallOnDidChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnDidChangeCallback)
    let rangeBefore : TextRange = TextRange_serializer.read(thisDeserializer)
    let rangeAfter : TextRange = TextRange_serializer.read(thisDeserializer)
    call(rangeBefore, rangeAfter)
}
export function deserializeAndCallOnDragEventCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnDragEventCallback)
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    call(event, extraParams)
}
export function deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnFirstMeaningfulPaintCallback)
    let firstMeaningfulPaint : FirstMeaningfulPaint = FirstMeaningfulPaint_serializer.read(thisDeserializer)
    call(firstMeaningfulPaint)
}
export function deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnFoldStatusChangeCallback)
    let event : OnFoldStatusChangeInfo = OnFoldStatusChangeInfo_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallOnFullScreenEnterCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnFullScreenEnterCallback)
    let event : FullScreenEnterEvent = FullScreenEnterEvent_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallOnHoverCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnHoverCallback)
    let status : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    call(status, event)
}
export function deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnHoverStatusChangeCallback)
    let param : HoverEventParam = HoverEventParam_serializer.read(thisDeserializer)
    call(param)
}
export function deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnIntelligentTrackingPreventionCallback)
    let details : IntelligentTrackingPreventionDetails = IntelligentTrackingPreventionDetails_serializer.read(thisDeserializer)
    call(details)
}
export function deserializeAndCallOnItemDragStartCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnItemDragStartCallback)
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: CustomBuilder | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, 1579551593, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: CustomBuilder | undefined) => void) = continuationBufferClosure
    const callResult  = call(event, itemIndex)
    continuationResult(callResult)
}
export function deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnLargestContentfulPaintCallback)
    let largestContentfulPaint : LargestContentfulPaint = LargestContentfulPaint_serializer.read(thisDeserializer)
    call(largestContentfulPaint)
}
export function deserializeAndCallOnMenuItemClickCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnMenuItemClickCallback)
    let menuItem : TextMenuItem = TextMenuItem_serializer.read(thisDeserializer)
    let range : TextRange = TextRange_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(menuItem, range)
    continuationResult(callResult)
}
export function deserializeAndCallOnMoveHandler(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnMoveHandler)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    call(from, to)
}
export function deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnNativeEmbedVisibilityChangeCallback)
    let nativeEmbedVisibilityInfo : NativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer.read(thisDeserializer)
    call(nativeEmbedVisibilityInfo)
}
export function deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnNavigationEntryCommittedCallback)
    let loadCommittedDetails : LoadCommittedDetails = LoadCommittedDetails_serializer.read(thisDeserializer)
    call(loadCommittedDetails)
}
export function deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnOverrideUrlLoadingCallback)
    let webResourceRequest : WebResourceRequest = (WebResourceRequest_serializer.read(thisDeserializer) as WebResourceRequest)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(webResourceRequest)
    continuationResult(callResult)
}
export function deserializeAndCallOnPasteCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnPasteCallback)
    let content : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = (PasteEvent_serializer.read(thisDeserializer) as PasteEvent)
    call(content, event)
}
export function deserializeAndCallOnRadioChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnRadioChangeCallback)
    let isChecked : boolean = thisDeserializer.readBoolean()
    call(isChecked)
}
export function deserializeAndCallOnRatingChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnRatingChangeCallback)
    let rating : double = thisDeserializer.readFloat64()
    call(rating)
}
export function deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnRenderProcessNotRespondingCallback)
    let data : RenderProcessNotRespondingData = RenderProcessNotRespondingData_serializer.read(thisDeserializer)
    call(data)
}
export function deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnRenderProcessRespondingCallback)
    call()
}
export function deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSafeBrowsingCheckResultCallback)
    let threatType : ThreatType = ThreatType.fromValue(thisDeserializer.readInt32())
    call(threatType)
}
export function deserializeAndCallOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnScrollCallback)
    let scrollOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    call(scrollOffset, scrollState)
}
export function deserializeAndCallOnScrollEdgeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnScrollEdgeCallback)
    let side : Edge = Edge.fromValue(thisDeserializer.readInt32())
    call(side)
}
export function deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnScrollFrameBeginCallback)
    let offset : double = thisDeserializer.readFloat64()
    let state : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: OnScrollFrameBeginHandlerResult):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        OnScrollFrameBeginHandlerResult_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 811282760, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: OnScrollFrameBeginHandlerResult) => void) = continuationBufferClosure
    const callResult  = call(offset, state)
    continuationResult(callResult)
}
export function deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnScrollVisibleContentChangeCallback)
    let start : VisibleListContentInfo = VisibleListContentInfo_serializer.read(thisDeserializer)
    let end : VisibleListContentInfo = VisibleListContentInfo_serializer.read(thisDeserializer)
    call(start, end)
}
export function deserializeAndCallOnSelectCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSelectCallback)
    let index : int32 = thisDeserializer.readInt32()
    let selectStr : string = (thisDeserializer.readString() as string)
    call(index, selectStr)
}
export function deserializeAndCallOnSslErrorEventCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSslErrorEventCallback)
    let sslErrorEvent : SslErrorEvent = SslErrorEvent_serializer.read(thisDeserializer)
    call(sslErrorEvent)
}
export function deserializeAndCallOnSubmitCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSubmitCallback)
    let enterKey : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    call(enterKey, event)
}
export function deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSwiperAnimationEndCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    call(index, extraInfo)
}
export function deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSwiperAnimationStartCallback)
    let index : int32 = thisDeserializer.readInt32()
    let targetIndex : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnSwiperGestureSwipeCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTabsAnimationEndCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTabsAnimationStartCallback)
    let index : int32 = thisDeserializer.readInt32()
    let targetIndex : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTabsContentWillChangeCallback)
    let currentIndex : int32 = thisDeserializer.readInt32()
    let comingIndex : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(currentIndex, comingIndex)
    continuationResult(callResult)
}
export function deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTabsGestureSwipeCallback)
    let index : int32 = thisDeserializer.readInt32()
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    call(index, extraInfo)
}
export function deserializeAndCallOnTextPickerChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTextPickerChangeCallback)
    const selectItemTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let selectItemTmpBuf : string | Array<string> | undefined
    if (selectItemTmpBufUnionSelector == (0).toByte()) {
        selectItemTmpBuf = (thisDeserializer.readString() as string)
    } else if (selectItemTmpBufUnionSelector == (1).toByte()) {
        const selectItemTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let selectItemTmpBufBufU : Array<string> = new Array<string>(selectItemTmpBufBufULength)
        for (let selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength; selectItemTmpBufBufUBufCounterI++) {
            selectItemTmpBufBufU[selectItemTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        selectItemTmpBuf = selectItemTmpBufBufU
    } else {
        throw new Error('One of the branches for selectItemTmpBuf has to be chosen through deserialisation.')
    }
    let selectItem : string | Array<string> = (selectItemTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toByte()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toByte()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new Array<int32>(indexTmpBufBufULength)
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error('One of the branches for indexTmpBuf has to be chosen through deserialisation.')
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    call(selectItem, index)
}
export function deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTextSelectionChangeCallback)
    let selectionStart : int32 = thisDeserializer.readInt32()
    let selectionEnd : int32 = thisDeserializer.readInt32()
    call(selectionStart, selectionEnd)
}
export function deserializeAndCallOnTimePickerChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnTimePickerChangeCallback)
    let result : TimePickerResult = TimePickerResult_serializer.read(thisDeserializer)
    call(result)
}
export function deserializeAndCallOnViewportFitChangedCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnViewportFitChangedCallback)
    let viewportFit : ViewportFit = ViewportFit.fromValue(thisDeserializer.readInt32())
    call(viewportFit)
}
export function deserializeAndCallOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as OnWillScrollCallback)
    let scrollOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = ScrollSource.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: ScrollResult | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, -1470069697, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: ScrollResult | undefined) => void) = continuationBufferClosure
    const callResult  = call(scrollOffset, scrollState, scrollSource)
    continuationResult(callResult)
}
export function deserializeAndCallPageMapNodeBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as PageMapNodeBuilder)
    let parentNode : KPointer = thisDeserializer.readPointer()
    let name : string = (thisDeserializer.readString() as string)
    const paramTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let paramTmpBuf : Object | null | undefined = undefined
    if ((paramTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        paramTmpBuf = (thisDeserializer.readObject() as object)
    }
    let param : Object | null | undefined = paramTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, name, param)
    continuationResult(callResult)
}
export function deserializeAndCallPasteButtonCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as PasteButtonCallback)
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : PasteButtonOnClickResult = PasteButtonOnClickResult.fromValue(thisDeserializer.readInt32())
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let errorTmpBuf : BusinessError<void> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBufOptDeserialized : BusinessErrorInterface<void> = BusinessErrorInterface_Void_serializer.read(thisDeserializer)
        errorTmpBuf = extractors.transform_Ark_BusinessErrorInterface_Void_to_Ark_BusinessError_Void(errorTmpBufOptDeserialized)
    }
    let error : BusinessError<void> | undefined = errorTmpBuf
    call(event, result, error)
}
export function deserializeAndCallPasteEventCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as PasteEventCallback)
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let eventTmpBuf : PasteEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = (PasteEvent_serializer.read(thisDeserializer) as PasteEvent)
    }
    let event : PasteEvent | undefined = eventTmpBuf
    call(event)
}
export function deserializeAndCallPluginErrorCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as PluginErrorCallback)
    let info : PluginErrorData = PluginErrorData_serializer.read(thisDeserializer)
    call(info)
}
export function deserializeAndCallPopupStateChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as PopupStateChangeCallback)
    let event : PopupStateChangeParam = PopupStateChangeParam_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallProgressModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: ProgressConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ProgressConfiguration = ProgressConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallRadioModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: RadioConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RadioConfiguration = RadioConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallRatingModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: RatingConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RatingConfiguration = RatingConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as RestrictedWorker_onerror_Callback)
    let ev : ErrorEvent = ErrorEvent_serializer.read(thisDeserializer)
    call(ev)
}
export function deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as RestrictedWorker_onexit_Callback)
    let code : number = (thisDeserializer.readNumber() as number)
    call(code)
}
export function deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as RestrictedWorker_onmessage_Callback)
    let event : MessageEvents = MessageEvents_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallReuseIdCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ReuseIdCallback)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (breakpoints: string):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeString(breakpoints);
        InteropNativeModule._CallCallbackSync(10, 569646982, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((breakpoints: string) => void) = continuationBufferClosure
    const callResult  = call()
    continuationResult(callResult)
}
export function deserializeAndCallRouterFinishCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as RouterFinishCallback)
    let value : KPointer = thisDeserializer.readPointer()
    call(value)
}
export function deserializeAndCallSaveButtonCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SaveButtonCallback)
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : SaveButtonOnClickResult = SaveButtonOnClickResult.fromValue(thisDeserializer.readInt32())
    const errorTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let errorTmpBuf : BusinessError<void> | undefined = undefined
    if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        const errorTmpBufOptDeserialized : BusinessErrorInterface<void> = BusinessErrorInterface_Void_serializer.read(thisDeserializer)
        errorTmpBuf = extractors.transform_Ark_BusinessErrorInterface_Void_to_Ark_BusinessError_Void(errorTmpBufOptDeserialized)
    }
    let error : BusinessError<void> | undefined = errorTmpBuf
    call(event, result, error)
}
export function deserializeAndCallScrollOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ScrollOnScrollCallback)
    let xOffset : double = thisDeserializer.readFloat64()
    let yOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    call(xOffset, yOffset, scrollState)
}
export function deserializeAndCallScrollOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ScrollOnWillScrollCallback)
    let xOffset : double = thisDeserializer.readFloat64()
    let yOffset : double = thisDeserializer.readFloat64()
    let scrollState : ScrollState = ScrollState.fromValue(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = ScrollSource.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: OffsetResult | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, -745388577, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: OffsetResult | undefined) => void) = continuationBufferClosure
    const callResult  = call(xOffset, yOffset, scrollState, scrollSource)
    continuationResult(callResult)
}
export function deserializeAndCallSearchSubmitCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SearchSubmitCallback)
    let searchContent : string = (thisDeserializer.readString() as string)
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let eventTmpBuf : SubmitEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = eventTmpBuf
    call(searchContent, event)
}
export function deserializeAndCallSearchValueCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SearchValueCallback)
    let value : string = (thisDeserializer.readString() as string)
    call(value)
}
export function deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ShouldBuiltInRecognizerParallelWithCallback)
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
    const continuationBufferClosure  = (value: GestureRecognizer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        GestureRecognizer_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 516676510, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: GestureRecognizer) => void) = continuationBufferClosure
    const callResult  = call(current, others)
    continuationResult(callResult)
}
export function deserializeAndCallSizeChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SizeChangeCallback)
    let oldValue : SizeOptions = SizeOptions_serializer.read(thisDeserializer)
    let newValue : SizeOptions = SizeOptions_serializer.read(thisDeserializer)
    call(oldValue, newValue)
}
export function deserializeAndCallSliderModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: SliderConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : SliderConfiguration = SliderConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallSliderTriggerChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SliderTriggerChangeCallback)
    let value : double = thisDeserializer.readFloat64()
    let mode : SliderChangeMode = SliderChangeMode.fromValue(thisDeserializer.readInt32())
    call(value, mode)
}
export function deserializeAndCallStyledStringMarshallCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as StyledStringMarshallCallback)
    let marshallableVal : StyledStringMarshallingValue = (thisDeserializer.readObject() as UserDataSpan)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: ArrayBuffer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBuffer(value);
        InteropNativeModule._CallCallbackSync(10, -372985937, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: ArrayBuffer) => void) = continuationBufferClosure
    const callResult  = call(marshallableVal)
    continuationResult(callResult)
}
export function deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as StyledStringUnmarshallCallback)
    let buf : ArrayBuffer = (thisDeserializer.readBuffer() as ArrayBuffer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: StyledStringMarshallingValue):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.holdAndWriteObject(value);
        InteropNativeModule._CallCallbackSync(10, 2051913890, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: StyledStringMarshallingValue) => void) = continuationBufferClosure
    const callResult  = call(buf)
    continuationResult(callResult)
}
export function deserializeAndCallSubmitCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as SubmitCallback)
    let enterKey : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    call(enterKey, event)
}
export function deserializeAndCallsynthetic_AsyncCallback_image_PixelMap_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((result: image.PixelMap) => void))
    let result : image.PixelMap = (image_PixelMap_serializer.read(thisDeserializer) as image.PixelMap)
    call(result)
}
export function deserializeAndCallsynthetic_Callback_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: Array<string>) => void))
    const valueTmpBufLength : int32 = thisDeserializer.readInt32()
    let valueTmpBuf : Array<string> = new Array<string>(valueTmpBufLength)
    for (let valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf[valueTmpBufBufCounterI] = (thisDeserializer.readString() as string)
    }
    let value : Array<string> = valueTmpBuf
    call(value)
}
export function deserializeAndCallsynthetic_Callback_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((isSelected: boolean) => void))
    let isSelected : boolean = thisDeserializer.readBoolean()
    call(isSelected)
}
export function deserializeAndCallsynthetic_Callback_DismissDialogAction_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value0: DismissDialogAction) => void))
    let value0 : DismissDialogAction = (DismissDialogAction_serializer.read(thisDeserializer) as DismissDialogAction)
    call(value0)
}
export function deserializeAndCallsynthetic_Callback_F64_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((progress: double) => void))
    let progress : double = thisDeserializer.readFloat64()
    call(progress)
}
export function deserializeAndCallsynthetic_Callback_KeyEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: KeyEvent) => boolean))
    let event : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (isSelected: boolean):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writeBoolean(isSelected);
        InteropNativeModule._CallCallbackSync(10, -2127714345, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((isSelected: boolean) => void) = continuationBufferClosure
    const callResult  = call(event)
    continuationResult(callResult)
}
export function deserializeAndCallsynthetic_Callback_String_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((breakpoints: string) => void))
    let breakpoints : string = (thisDeserializer.readString() as string)
    call(breakpoints)
}
export function deserializeAndCallsynthetic_Callback_TextPickerResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: TextPickerResult) => void))
    let value : TextPickerResult = TextPickerResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallsynthetic_Callback_TimePickerResult_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((value: TimePickerResult) => void))
    let value : TimePickerResult = TimePickerResult_serializer.read(thisDeserializer)
    call(value)
}
export function deserializeAndCallsynthetic_Callback_Void(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as (() => void))
    call()
}
export function deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TabsCustomContentTransitionCallback)
    let from : int32 = thisDeserializer.readInt32()
    let to : int32 = thisDeserializer.readInt32()
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: TabContentAnimatedTransition | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, 234942517, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: TabContentAnimatedTransition | undefined) => void) = continuationBufferClosure
    const callResult  = call(from, to)
    continuationResult(callResult)
}
export function deserializeAndCallTextAreaSubmitCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TextAreaSubmitCallback)
    let enterKeyType : EnterKeyType = EnterKeyType.fromValue(thisDeserializer.readInt32())
    const eventTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let eventTmpBuf : SubmitEvent | undefined = undefined
    if ((eventTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        eventTmpBuf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = eventTmpBuf
    call(enterKeyType, event)
}
export function deserializeAndCallTextClockModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: TextClockConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextClockConfiguration = TextClockConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallTextFieldValueCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TextFieldValueCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | arkui_component_units_Resource | undefined
    if (valueTmpBufUnionSelector == (0).toByte()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toByte()) {
        valueTmpBuf = global_resource_Resource_serializer.read(thisDeserializer)
    } else {
        throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
    }
    let value : arkui_component_units_ResourceStr = (valueTmpBuf as string | arkui_component_units_Resource)
    call(value)
}
export function deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TextPickerEnterSelectedAreaCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | Array<string> | undefined
    if (valueTmpBufUnionSelector == (0).toByte()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toByte()) {
        const valueTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
        for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        valueTmpBuf = valueTmpBufBufU
    } else {
        throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
    }
    let value : string | Array<string> = (valueTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toByte()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toByte()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new Array<int32>(indexTmpBufBufULength)
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error('One of the branches for indexTmpBuf has to be chosen through deserialisation.')
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    call(value, index)
}
export function deserializeAndCallTextPickerScrollStopCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TextPickerScrollStopCallback)
    const valueTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let valueTmpBuf : string | Array<string> | undefined
    if (valueTmpBufUnionSelector == (0).toByte()) {
        valueTmpBuf = (thisDeserializer.readString() as string)
    } else if (valueTmpBufUnionSelector == (1).toByte()) {
        const valueTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let valueTmpBufBufU : Array<string> = new Array<string>(valueTmpBufBufULength)
        for (let valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU[valueTmpBufBufUBufCounterI] = (thisDeserializer.readString() as string)
        }
        valueTmpBuf = valueTmpBufBufU
    } else {
        throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
    }
    let value : string | Array<string> = (valueTmpBuf as string | Array<string>)
    const indexTmpBufUnionSelector : int32 = thisDeserializer.readInt8()
    let indexTmpBuf : int32 | Array<int32> | undefined
    if (indexTmpBufUnionSelector == (0).toByte()) {
        indexTmpBuf = thisDeserializer.readInt32()
    } else if (indexTmpBufUnionSelector == (1).toByte()) {
        const indexTmpBufBufULength : int32 = thisDeserializer.readInt32()
        let indexTmpBufBufU : Array<int32> = new Array<int32>(indexTmpBufBufULength)
        for (let indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32()
        }
        indexTmpBuf = indexTmpBufBufU
    } else {
        throw new Error('One of the branches for indexTmpBuf has to be chosen through deserialisation.')
    }
    let index : int32 | Array<int32> = (indexTmpBuf as int32 | Array<int32>)
    call(value, index)
}
export function deserializeAndCallTextTimerModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextTimerConfiguration = TextTimerConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallTimerCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TimerCallback)
    let utc : int64 = thisDeserializer.readInt64()
    let elapsedTime : int64 = thisDeserializer.readInt64()
    call(utc, elapsedTime)
}
export function deserializeAndCallToggleModifierBuilder(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ToggleConfiguration = ToggleConfiguration_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: KPointer):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        continuationBufferBufArgsSerializer.writePointer(value);
        InteropNativeModule._CallCallbackSync(10, -210450188, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: KPointer) => void) = continuationBufferClosure
    const callResult  = call(parentNode, config)
    continuationResult(callResult)
}
export function deserializeAndCallTouchTestDoneCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TouchTestDoneCallback)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    const recognizersTmpBufLength : int32 = thisDeserializer.readInt32()
    let recognizersTmpBuf : Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizersTmpBufLength)
    for (let recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength; recognizersTmpBufBufCounterI++) {
        recognizersTmpBuf[recognizersTmpBufBufCounterI] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let recognizers : Array<GestureRecognizer> = recognizersTmpBuf
    call(event, recognizers)
}
export function deserializeAndCallTransitionFinishCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as TransitionFinishCallback)
    let transitionIn : boolean = thisDeserializer.readBoolean()
    call(transitionIn)
}
export function deserializeAndCallType_CommonMethod_onDragStart(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo))
    let event : DragEvent = (DragEvent_serializer.read(thisDeserializer) as DragEvent)
    const extraParamsTmpBuf_runtimeType  = thisDeserializer.readInt8()!.toInt()
    let extraParamsTmpBuf : string | undefined = undefined
    if ((extraParamsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
        extraParamsTmpBuf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParamsTmpBuf
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: CustomBuilder | DragItemInfo):void => {
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
        InteropNativeModule._CallCallbackSync(10, 1325601477, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: CustomBuilder | DragItemInfo) => void) = continuationBufferClosure
    const callResult  = call(event, extraParams)
    continuationResult(callResult)
}
export function deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
    let from : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let to : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let operation : NavigationOperation = NavigationOperation.fromValue(thisDeserializer.readInt32())
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value?: NavigationAnimatedTransition | undefined):void => {
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
        InteropNativeModule._CallCallbackSync(10, -1363541055, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: NavigationAnimatedTransition | undefined) => void) = continuationBufferClosure
    const callResult  = call(from, to, operation)
    continuationResult(callResult)
}
export function deserializeAndCallUpdateTransitionCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as UpdateTransitionCallback)
    let progress : double = thisDeserializer.readFloat64()
    call(progress)
}
export function deserializeAndCallVisibleAreaChangeCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as VisibleAreaChangeCallback)
    let isExpanding : boolean = thisDeserializer.readBoolean()
    let currentRatio : double = thisDeserializer.readFloat64()
    call(isExpanding, currentRatio)
}
export function deserializeAndCallVoidCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as VoidCallback)
    call()
}
export function deserializeAndCallWebKeyboardCallback(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as WebKeyboardCallback)
    let keyboardCallbackInfo : WebKeyboardCallbackInfo = WebKeyboardCallbackInfo_serializer.read(thisDeserializer)
    const continuationBufferBufResource : CallbackResource = thisDeserializer.readCallbackResource()
    const continuationBufferBufCall : KPointer = thisDeserializer.readPointer()
    const continuationBufferBufCallSync : KPointer = thisDeserializer.readPointer()
    const continuationBufferClosure  = (value: WebKeyboardOptions):void => {
        const continuationBufferBufArgsSerializer : SerializerBase = SerializerBase.hold();
        continuationBufferBufArgsSerializer.writeInt32(continuationBufferBufResource.resourceId);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCall);
        continuationBufferBufArgsSerializer.writePointer(continuationBufferBufCallSync);
        WebKeyboardOptions_serializer.write(continuationBufferBufArgsSerializer, value);
        InteropNativeModule._CallCallbackSync(10, 1533934626, continuationBufferBufArgsSerializer.asBuffer(), continuationBufferBufArgsSerializer.length());
        continuationBufferBufArgsSerializer.release();
        return;
    }
    resourceFinalizerRegister(continuationBufferClosure, continuationBufferBufResource)
    let continuationResult : ((value: WebKeyboardOptions) => void) = continuationBufferClosure
    const callResult  = call(keyboardCallbackInfo)
    continuationResult(callResult)
}
export function deserializeAndCallWorkerEventListener(thisDeserializer: DeserializerBase): void {
    const resourceId : int32 = thisDeserializer.readInt32()
    const call  = (ResourceHolder.instance().get(resourceId) as WorkerEventListener)
    let event : Event = Event_serializer.read(thisDeserializer)
    call(event)
}
export function deserializeAndCallCallback(thisDeserializer: DeserializerBase): void {
    const kind : int32 = thisDeserializer.readInt32()
    switch ((kind as CallbackKind)) {
        case CallbackKind.KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK: return deserializeAndCallAccessibilityActionInterceptCallback(thisDeserializer);
        case CallbackKind.KIND_ACCESSIBILITYCALLBACK: return deserializeAndCallAccessibilityCallback(thisDeserializer);
        case CallbackKind.KIND_ACCESSIBILITYFOCUSCALLBACK: return deserializeAndCallAccessibilityFocusCallback(thisDeserializer);
        case CallbackKind.KIND_ACCESSIBILITYTRANSPARENTCALLBACK: return deserializeAndCallAccessibilityTransparentCallback(thisDeserializer);
        case CallbackKind.KIND_BUTTONMODIFIERBUILDER: return deserializeAndCallButtonModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_BUTTONTRIGGERCLICKCALLBACK: return deserializeAndCallButtonTriggerClickCallback(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID: return deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_AREA_AREA_VOID: return deserializeAndCallCallback_Area_Area_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_I32_VOID: return deserializeAndCallCallback_Array_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_RESOURCE_VOID: return deserializeAndCallCallback_Array_Resource_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_RESOURCESTR_VOID: return deserializeAndCallCallback_Array_ResourceStr_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_STRING_VOID: return deserializeAndCallCallback_Array_String_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_AXISEVENT_VOID: return deserializeAndCallCallback_AxisEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_BOOLEAN: return deserializeAndCallCallback_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_BOOLEAN_VOID: return deserializeAndCallCallback_Boolean_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_BUFFER_VOID: return deserializeAndCallCallback_Buffer_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_BUSINESSERROR_VOID: return deserializeAndCallCallback_BusinessError_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CLICKEVENT_VOID: return deserializeAndCallCallback_ClickEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_COPYEVENT_VOID: return deserializeAndCallCallback_CopyEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CREATEITEM: return deserializeAndCallCallback_CreateItem(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CROWNEVENT_VOID: return deserializeAndCallCallback_CrownEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS: return deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CUSTOMSPANMETRICS_VOID: return deserializeAndCallCallback_CustomSpanMetrics_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_CUTEVENT_VOID: return deserializeAndCallCallback_CutEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DATE_VOID: return deserializeAndCallCallback_Date_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DELETEVALUE_BOOLEAN: return deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DELETEVALUE_VOID: return deserializeAndCallCallback_DeleteValue_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DISMISSDIALOGACTION_VOID: return deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DISMISSPOPUPACTION_VOID: return deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DISMISSSHEETACTION_VOID: return deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID: return deserializeAndCallCallback_DragEvent_Opt_String_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID: return deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_DRAWCONTEXT_VOID: return deserializeAndCallCallback_DrawContext_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN: return deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ERRORINFORMATION_VOID: return deserializeAndCallCallback_ErrorInformation_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_EXTENDER_ONFINISH: return deserializeAndCallCallback_Extender_OnFinish(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_EXTENDER_ONPROGRESS: return deserializeAndCallCallback_Extender_OnProgress(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_F64_F64_VOID: return deserializeAndCallCallback_F64_F64_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID: return deserializeAndCallCallback_F64_SliderChangeMode_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_F64_VOID: return deserializeAndCallCallback_F64_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_FOCUSAXISEVENT_VOID: return deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_FORMCALLBACKINFO_VOID: return deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_FULLSCREENINFO_VOID: return deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_GESTUREEVENT_VOID: return deserializeAndCallCallback_GestureEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_GESTUREJUDGERESULT_VOID: return deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_GESTURERECOGNIZER_VOID: return deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_HITTESTMODE_VOID: return deserializeAndCallCallback_HitTestMode_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_HOVEREVENT_VOID: return deserializeAndCallCallback_HoverEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE: return deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_I32_BOOLEAN: return deserializeAndCallCallback_I32_I32_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_I32_I32_VOID: return deserializeAndCallCallback_I32_I32_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_I32_VOID: return deserializeAndCallCallback_I32_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_TUPLE_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I32_VOID: return deserializeAndCallCallback_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_I64_VOID: return deserializeAndCallCallback_I64_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_INSERTVALUE_BOOLEAN: return deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_INSERTVALUE_VOID: return deserializeAndCallCallback_InsertValue_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ITEMDRAGINFO_I32_VOID: return deserializeAndCallCallback_ItemDragInfo_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ITEMDRAGINFO_VOID: return deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_KEYEVENT_BOOLEAN: return deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_KEYEVENT_VOID: return deserializeAndCallCallback_KeyEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_LENGTH_VOID: return deserializeAndCallCallback_Length_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_MAP_STRING_OPT_OBJECT: return deserializeAndCallCallback_Map_String_Opt_Object(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_MARQUEESTATE_VOID: return deserializeAndCallCallback_MarqueeState_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_MOUSEEVENT_VOID: return deserializeAndCallCallback_MouseEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID: return deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NAVIGATIONMODE_VOID: return deserializeAndCallCallback_NavigationMode_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID: return deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_NUMBER_VOID: return deserializeAndCallCallback_Number_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OBJECT_VOID: return deserializeAndCallCallback_Object_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONALERTEVENT_BOOLEAN: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONDESTORY_VOID: return deserializeAndCallCallback_OnDestory_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE: return deserializeAndCallCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID: return deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID: return deserializeAndCallCallback_OnLoadStartedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONMEASURESIZE_SIZERESULT: return deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONMOVEFROMTO: return deserializeAndCallCallback_OnMoveFromTo(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONOVERSCROLLEVENT_VOID: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPAGEBEGINEVENT_VOID: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPAGEENDEVENT_VOID: return deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPLACECHILDREN_VOID: return deserializeAndCallCallback_onPlaceChildren_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONRESOURCELOADEVENT_VOID: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSCALECHANGEEVENT_VOID: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSCROLLEVENT_VOID: return deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_ONWINDOWNEWEVENT_VOID: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_ARRAY_STRING_VOID: return deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID: return deserializeAndCallCallback_Opt_CustomNodeBuilder_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_OBJECT_VOID: return deserializeAndCallCallback_Opt_Object_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_OFFSETRESULT_VOID: return deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_SCROLLRESULT_VOID: return deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID: return deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_PLAYBACKINFO_VOID: return deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_POINTER_VOID: return deserializeAndCallCallback_Pointer_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_POPINFO_VOID: return deserializeAndCallCallback_PopInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_PREDRAGSTATUS_VOID: return deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_PREPAREDINFO_VOID: return deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RANGEUPDATE: return deserializeAndCallCallback_RangeUpdate(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_REFRESHSTATUS_VOID: return deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RESOURCE_VOID: return deserializeAndCallCallback_Resource_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RESOURCESTR_VOID: return deserializeAndCallCallback_ResourceStr_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORRANGE_VOID: return deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORSELECTION_VOID: return deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SHEETDISMISS_VOID: return deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SHEETTYPE_VOID: return deserializeAndCallCallback_SheetType_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SIZE_VOID: return deserializeAndCallCallback_Size_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SIZERESULT_VOID: return deserializeAndCallCallback_SizeResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SPRINGBACKACTION_VOID: return deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STATESTYLESCHANGE: return deserializeAndCallCallback_StateStylesChange(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STRING: return deserializeAndCallCallback_String(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STRING_PASTEEVENT_VOID: return deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STRING_SURFACERECT_VOID: return deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STRING_VOID: return deserializeAndCallCallback_String_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SWIPEACTIONSTATE_VOID: return deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TERMINATIONINFO: return deserializeAndCallCallback_TerminationInfo(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TEXTPICKERRESULT_VOID: return deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TEXTRANGE_VOID: return deserializeAndCallCallback_TextRange_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TIMEPICKERRESULT_VOID: return deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TOUCHEVENT_HITTESTMODE: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TOUCHEVENT_VOID: return deserializeAndCallCallback_TouchEvent_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TOUCHRESULT_VOID: return deserializeAndCallCallback_TouchResult_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID: return deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_TUPLE_I32_I32_VOID: return deserializeAndCallCallback_Tuple_I32_I32_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_UIEXTENSIONPROXY: return deserializeAndCallCallback_UIExtensionProxy(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID: return deserializeAndCallCallback_Union_CustomNodeBuilder_DragItemInfo_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_USERDATASPAN_VOID: return deserializeAndCallCallback_UserDataSpan_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_VOID_VOID: return deserializeAndCallCallback_Void_Void(thisDeserializer);
        case CallbackKind.KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer);
        case CallbackKind.KIND_CHECKBOXMODIFIERBUILDER: return deserializeAndCallCheckBoxModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_CONTENTDIDSCROLLCALLBACK: return deserializeAndCallContentDidScrollCallback(thisDeserializer);
        case CallbackKind.KIND_CONTENTWILLSCROLLCALLBACK: return deserializeAndCallContentWillScrollCallback(thisDeserializer);
        case CallbackKind.KIND_CUSTOMNODEBUILDER: return deserializeAndCallCustomNodeBuilder(thisDeserializer);
        case CallbackKind.KIND_DATAPANELMODIFIERBUILDER: return deserializeAndCallDataPanelModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_DATAPROGRESSLISTENER: return deserializeAndCallDataProgressListener(thisDeserializer);
        case CallbackKind.KIND_EDITABLETEXTONCHANGECALLBACK: return deserializeAndCallEditableTextOnChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID: return deserializeAndCallErrorCallback_BusinessErrorInterface_Void(thisDeserializer);
        case CallbackKind.KIND_FRAMECALLBACKHANDLER: return deserializeAndCallFrameCallbackHandler(thisDeserializer);
        case CallbackKind.KIND_GAUGEMODIFIERBUILDER: return deserializeAndCallGaugeModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_GESTUREEVENTHANDLER: return deserializeAndCallGestureEventHandler(thisDeserializer);
        case CallbackKind.KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer);
        case CallbackKind.KIND_HOVERCALLBACK: return deserializeAndCallHoverCallback(thisDeserializer);
        case CallbackKind.KIND_IMAGECOMPLETECALLBACK: return deserializeAndCallImageCompleteCallback(thisDeserializer);
        case CallbackKind.KIND_IMAGEERRORCALLBACK: return deserializeAndCallImageErrorCallback(thisDeserializer);
        case CallbackKind.KIND_IMAGEONCOMPLETECALLBACK: return deserializeAndCallImageOnCompleteCallback(thisDeserializer);
        case CallbackKind.KIND_INTERCEPTIONMODECALLBACK: return deserializeAndCallInterceptionModeCallback(thisDeserializer);
        case CallbackKind.KIND_INTERCEPTIONSHOWCALLBACK: return deserializeAndCallInterceptionShowCallback(thisDeserializer);
        case CallbackKind.KIND_LOADINGPROGRESSMODIFIERBUILDER: return deserializeAndCallLoadingProgressModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_MENUCALLBACK: return deserializeAndCallMenuCallback(thisDeserializer);
        case CallbackKind.KIND_MENUITEMMODIFIERBUILDER: return deserializeAndCallMenuItemModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_MENUONAPPEARCALLBACK: return deserializeAndCallMenuOnAppearCallback(thisDeserializer);
        case CallbackKind.KIND_MODIFIERKEYSTATEGETTER: return deserializeAndCallModifierKeyStateGetter(thisDeserializer);
        case CallbackKind.KIND_NAVDESTINATIONTRANSITIONDELEGATE: return deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer);
        case CallbackKind.KIND_NAVEXTENDER_CREATENAVDESTINATION: return deserializeAndCallNavExtender_CreateNavDestination(thisDeserializer);
        case CallbackKind.KIND_NAVEXTENDER_ONUPDATESTACK: return deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer);
        case CallbackKind.KIND_NODECONTAINEROPSONTOUCHCALLBACK: return deserializeAndCallNodeContainerOpsOnTouchCallback(thisDeserializer);
        case CallbackKind.KIND_ONADSBLOCKEDCALLBACK: return deserializeAndCallOnAdsBlockedCallback(thisDeserializer);
        case CallbackKind.KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer);
        case CallbackKind.KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer);
        case CallbackKind.KIND_ONALPHABETINDEXERSELECTCALLBACK: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer);
        case CallbackKind.KIND_ONCHECKBOXCHANGECALLBACK: return deserializeAndCallOnCheckboxChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONCHECKBOXGROUPCHANGECALLBACK: return deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONCONTENTSCROLLCALLBACK: return deserializeAndCallOnContentScrollCallback(thisDeserializer);
        case CallbackKind.KIND_ONCONTEXTMENUHIDECALLBACK: return deserializeAndCallOnContextMenuHideCallback(thisDeserializer);
        case CallbackKind.KIND_ONCREATEMENUCALLBACK: return deserializeAndCallOnCreateMenuCallback(thisDeserializer);
        case CallbackKind.KIND_ONDIDCHANGECALLBACK: return deserializeAndCallOnDidChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONDRAGEVENTCALLBACK: return deserializeAndCallOnDragEventCallback(thisDeserializer);
        case CallbackKind.KIND_ONFIRSTMEANINGFULPAINTCALLBACK: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer);
        case CallbackKind.KIND_ONFOLDSTATUSCHANGECALLBACK: return deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONFULLSCREENENTERCALLBACK: return deserializeAndCallOnFullScreenEnterCallback(thisDeserializer);
        case CallbackKind.KIND_ONHOVERCALLBACK: return deserializeAndCallOnHoverCallback(thisDeserializer);
        case CallbackKind.KIND_ONHOVERSTATUSCHANGECALLBACK: return deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer);
        case CallbackKind.KIND_ONITEMDRAGSTARTCALLBACK: return deserializeAndCallOnItemDragStartCallback(thisDeserializer);
        case CallbackKind.KIND_ONLARGESTCONTENTFULPAINTCALLBACK: return deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer);
        case CallbackKind.KIND_ONMENUITEMCLICKCALLBACK: return deserializeAndCallOnMenuItemClickCallback(thisDeserializer);
        case CallbackKind.KIND_ONMOVEHANDLER: return deserializeAndCallOnMoveHandler(thisDeserializer);
        case CallbackKind.KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK: return deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer);
        case CallbackKind.KIND_ONOVERRIDEURLLOADINGCALLBACK: return deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer);
        case CallbackKind.KIND_ONPASTECALLBACK: return deserializeAndCallOnPasteCallback(thisDeserializer);
        case CallbackKind.KIND_ONRADIOCHANGECALLBACK: return deserializeAndCallOnRadioChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONRATINGCHANGECALLBACK: return deserializeAndCallOnRatingChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer);
        case CallbackKind.KIND_ONRENDERPROCESSRESPONDINGCALLBACK: return deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer);
        case CallbackKind.KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer);
        case CallbackKind.KIND_ONSCROLLCALLBACK: return deserializeAndCallOnScrollCallback(thisDeserializer);
        case CallbackKind.KIND_ONSCROLLEDGECALLBACK: return deserializeAndCallOnScrollEdgeCallback(thisDeserializer);
        case CallbackKind.KIND_ONSCROLLFRAMEBEGINCALLBACK: return deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer);
        case CallbackKind.KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONSELECTCALLBACK: return deserializeAndCallOnSelectCallback(thisDeserializer);
        case CallbackKind.KIND_ONSSLERROREVENTCALLBACK: return deserializeAndCallOnSslErrorEventCallback(thisDeserializer);
        case CallbackKind.KIND_ONSUBMITCALLBACK: return deserializeAndCallOnSubmitCallback(thisDeserializer);
        case CallbackKind.KIND_ONSWIPERANIMATIONENDCALLBACK: return deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer);
        case CallbackKind.KIND_ONSWIPERANIMATIONSTARTCALLBACK: return deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer);
        case CallbackKind.KIND_ONSWIPERGESTURESWIPECALLBACK: return deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer);
        case CallbackKind.KIND_ONTABSANIMATIONENDCALLBACK: return deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer);
        case CallbackKind.KIND_ONTABSANIMATIONSTARTCALLBACK: return deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer);
        case CallbackKind.KIND_ONTABSCONTENTWILLCHANGECALLBACK: return deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONTABSGESTURESWIPECALLBACK: return deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer);
        case CallbackKind.KIND_ONTEXTPICKERCHANGECALLBACK: return deserializeAndCallOnTextPickerChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONTEXTSELECTIONCHANGECALLBACK: return deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONTIMEPICKERCHANGECALLBACK: return deserializeAndCallOnTimePickerChangeCallback(thisDeserializer);
        case CallbackKind.KIND_ONVIEWPORTFITCHANGEDCALLBACK: return deserializeAndCallOnViewportFitChangedCallback(thisDeserializer);
        case CallbackKind.KIND_ONWILLSCROLLCALLBACK: return deserializeAndCallOnWillScrollCallback(thisDeserializer);
        case CallbackKind.KIND_PAGEMAPNODEBUILDER: return deserializeAndCallPageMapNodeBuilder(thisDeserializer);
        case CallbackKind.KIND_PASTEBUTTONCALLBACK: return deserializeAndCallPasteButtonCallback(thisDeserializer);
        case CallbackKind.KIND_PASTEEVENTCALLBACK: return deserializeAndCallPasteEventCallback(thisDeserializer);
        case CallbackKind.KIND_PLUGINERRORCALLBACK: return deserializeAndCallPluginErrorCallback(thisDeserializer);
        case CallbackKind.KIND_POPUPSTATECHANGECALLBACK: return deserializeAndCallPopupStateChangeCallback(thisDeserializer);
        case CallbackKind.KIND_PROGRESSMODIFIERBUILDER: return deserializeAndCallProgressModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_RADIOMODIFIERBUILDER: return deserializeAndCallRadioModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_RATINGMODIFIERBUILDER: return deserializeAndCallRatingModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_RESTRICTEDWORKER_ONERROR_CALLBACK: return deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer);
        case CallbackKind.KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK: return deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer);
        case CallbackKind.KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK: return deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer);
        case CallbackKind.KIND_REUSEIDCALLBACK: return deserializeAndCallReuseIdCallback(thisDeserializer);
        case CallbackKind.KIND_ROUTERFINISHCALLBACK: return deserializeAndCallRouterFinishCallback(thisDeserializer);
        case CallbackKind.KIND_SAVEBUTTONCALLBACK: return deserializeAndCallSaveButtonCallback(thisDeserializer);
        case CallbackKind.KIND_SCROLLONSCROLLCALLBACK: return deserializeAndCallScrollOnScrollCallback(thisDeserializer);
        case CallbackKind.KIND_SCROLLONWILLSCROLLCALLBACK: return deserializeAndCallScrollOnWillScrollCallback(thisDeserializer);
        case CallbackKind.KIND_SEARCHSUBMITCALLBACK: return deserializeAndCallSearchSubmitCallback(thisDeserializer);
        case CallbackKind.KIND_SEARCHVALUECALLBACK: return deserializeAndCallSearchValueCallback(thisDeserializer);
        case CallbackKind.KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer);
        case CallbackKind.KIND_SIZECHANGECALLBACK: return deserializeAndCallSizeChangeCallback(thisDeserializer);
        case CallbackKind.KIND_SLIDERMODIFIERBUILDER: return deserializeAndCallSliderModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_SLIDERTRIGGERCHANGECALLBACK: return deserializeAndCallSliderTriggerChangeCallback(thisDeserializer);
        case CallbackKind.KIND_STYLEDSTRINGMARSHALLCALLBACK: return deserializeAndCallStyledStringMarshallCallback(thisDeserializer);
        case CallbackKind.KIND_STYLEDSTRINGUNMARSHALLCALLBACK: return deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer);
        case CallbackKind.KIND_SUBMITCALLBACK: return deserializeAndCallSubmitCallback(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID: return deserializeAndCallsynthetic_AsyncCallback_image_PixelMap_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID: return deserializeAndCallsynthetic_Callback_Array_String_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID: return deserializeAndCallsynthetic_Callback_Boolean_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID: return deserializeAndCallsynthetic_Callback_DismissDialogAction_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_F64_VOID: return deserializeAndCallsynthetic_Callback_F64_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN: return deserializeAndCallsynthetic_Callback_KeyEvent_Boolean(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_STRING_VOID: return deserializeAndCallsynthetic_Callback_String_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID: return deserializeAndCallsynthetic_Callback_TextPickerResult_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID: return deserializeAndCallsynthetic_Callback_TimePickerResult_Void(thisDeserializer);
        case CallbackKind.KIND_SYNTHETIC_CALLBACK_VOID: return deserializeAndCallsynthetic_Callback_Void(thisDeserializer);
        case CallbackKind.KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK: return deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer);
        case CallbackKind.KIND_TEXTAREASUBMITCALLBACK: return deserializeAndCallTextAreaSubmitCallback(thisDeserializer);
        case CallbackKind.KIND_TEXTCLOCKMODIFIERBUILDER: return deserializeAndCallTextClockModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_TEXTFIELDVALUECALLBACK: return deserializeAndCallTextFieldValueCallback(thisDeserializer);
        case CallbackKind.KIND_TEXTPICKERENTERSELECTEDAREACALLBACK: return deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer);
        case CallbackKind.KIND_TEXTPICKERSCROLLSTOPCALLBACK: return deserializeAndCallTextPickerScrollStopCallback(thisDeserializer);
        case CallbackKind.KIND_TEXTTIMERMODIFIERBUILDER: return deserializeAndCallTextTimerModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_TIMERCALLBACK: return deserializeAndCallTimerCallback(thisDeserializer);
        case CallbackKind.KIND_TOGGLEMODIFIERBUILDER: return deserializeAndCallToggleModifierBuilder(thisDeserializer);
        case CallbackKind.KIND_TOUCHTESTDONECALLBACK: return deserializeAndCallTouchTestDoneCallback(thisDeserializer);
        case CallbackKind.KIND_TRANSITIONFINISHCALLBACK: return deserializeAndCallTransitionFinishCallback(thisDeserializer);
        case CallbackKind.KIND_TYPE_COMMONMETHOD_ONDRAGSTART: return deserializeAndCallType_CommonMethod_onDragStart(thisDeserializer);
        case CallbackKind.KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION: return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer);
        case CallbackKind.KIND_UPDATETRANSITIONCALLBACK: return deserializeAndCallUpdateTransitionCallback(thisDeserializer);
        case CallbackKind.KIND_VISIBLEAREACHANGECALLBACK: return deserializeAndCallVisibleAreaChangeCallback(thisDeserializer);
        case CallbackKind.KIND_VOIDCALLBACK: return deserializeAndCallVoidCallback(thisDeserializer);
        case CallbackKind.KIND_WEBKEYBOARDCALLBACK: return deserializeAndCallWebKeyboardCallback(thisDeserializer);
        case CallbackKind.KIND_WORKEREVENTLISTENER: return deserializeAndCallWorkerEventListener(thisDeserializer);
    }
    throw new Error('Unknown callback kind')
}
export function registerArkuiApiHandler(): void {
    registerApiEventHandler(10, deserializeAndCallCallback)
}

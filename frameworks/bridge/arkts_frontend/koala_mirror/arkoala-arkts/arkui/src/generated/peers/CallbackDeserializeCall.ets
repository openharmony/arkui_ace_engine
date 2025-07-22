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

import { AccessibilityHoverEvent_serializer, TouchTestInfo_serializer, TouchResult_serializer, AxisEvent_serializer, HoverEvent_serializer, ClickEvent_serializer, CrownEvent_serializer, DismissContentCoverAction_serializer, DismissPopupAction_serializer, DismissSheetAction_serializer, DragEvent_serializer, FocusAxisEvent_serializer, ItemDragInfo_serializer, KeyEvent_serializer, MouseEvent_serializer, GeometryInfo_serializer, Measurable_serializer, SizeResult_serializer, Layoutable_serializer, ScrollResult_serializer, SheetDismiss_serializer, SpringBackAction_serializer, TerminationInfo_serializer, TouchEvent_serializer, DragItemInfo_serializer, PopupStateChangeParam_serializer, AccessibilityCallback, AccessibilityHoverEvent, AccessibilityFocusCallback, TouchTestInfo, TouchResult, AxisEvent, HoverEvent, ClickEvent, CrownEvent, DismissContentCoverAction, DismissPopupAction, DismissSheetAction, DragEvent, FocusAxisEvent, ItemDragInfo, KeyEvent, MouseEvent, GeometryInfo, Measurable, SizeResult, Layoutable, ScrollResult, PreDragStatus, SheetDismiss, SheetType, SpringBackAction, TerminationInfo, TouchEvent, DragItemInfo, GestureRecognizerJudgeBeginCallback, HoverCallback, ModifierKeyStateGetter, OnDragEventCallback, OnItemDragStartCallback, OnMoveHandler, OnScrollCallback, OnWillScrollCallback, PopupStateChangeCallback, PopupStateChangeParam, ReuseIdCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, TransitionFinishCallback, VisibleAreaChangeCallback } from "./../../component/common"
import { image_PixelMap_serializer, image } from "./../ohos.multimedia.image"
import { ButtonConfiguration_serializer, ButtonConfiguration, ButtonTriggerClickCallback } from "./../../component/button"
import { Area_serializer, ConstraintSizeOptions_serializer, SizeOptions_serializer, Area, ConstraintSizeOptions, ResourceStr, SizeOptions, VoidCallback } from "./../../component/units"
import { TextMenuItem_serializer, DeleteValue_serializer, EditableTextChangeValue_serializer, InsertValue_serializer, StyledStringChangeValue_serializer, TextRange_serializer, PreviewText_serializer, TextChangeOptions_serializer, TextMenuItem, DeleteValue, EditableTextChangeValue, InsertValue, StyledStringChangeValue, TextRange, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, OnCreateMenuCallback, OnDidChangeCallback, OnMenuItemClickCallback } from "./../../component/textCommon"
import { CompatibleComponentInfo_serializer, CompatibleComponentInfo, CompatibleInitCallback, CompatibleUpdateCallback } from "./../../component/interop"
import { ComputedBarAttribute_serializer, ComputedBarAttribute } from "./../../component/grid"
import { CopyEvent_serializer, CutEvent_serializer, RichEditorChangeValue_serializer, RichEditorDeleteValue_serializer, RichEditorInsertValue_serializer, RichEditorRange_serializer, RichEditorSelection_serializer, RichEditorTextSpanResult_serializer, PasteEvent_serializer, CopyEvent, CutEvent, RichEditorChangeValue, RichEditorDeleteValue, RichEditorInsertValue, RichEditorRange, RichEditorSelection, RichEditorTextSpanResult, PasteEvent, MenuCallback, MenuOnAppearCallback, OnHoverCallback, PasteEventCallback, SubmitCallback } from "./../../component/richEditor"
import { CustomSpanMeasureInfo_serializer, CustomSpanMetrics_serializer, CustomSpanDrawInfo_serializer, StyledString_serializer, UserDataSpan_serializer, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledString, UserDataSpan, StyledStringMarshallCallback, StyledStringUnmarshallCallback } from "./../../component/styledString"
import { DismissDialogAction_serializer, DismissDialogAction } from "./../../component/actionSheet"
import { DrawContext_serializer, DrawContext } from "./../arkui.Graphics"
import { ErrorInformation_serializer, FormCallbackInfo_serializer, ErrorInformation, FormCallbackInfo } from "./../../component/formComponent"
import { FullscreenInfo_serializer, PlaybackInfo_serializer, PreparedInfo_serializer, FullscreenInfo, PlaybackInfo, PreparedInfo } from "./../../component/video"
import { GestureEvent_serializer, GestureInfo_serializer, BaseGestureEvent_serializer, GestureRecognizer_serializer, RotationGesture_serializer, SwipeGesture_serializer, GestureEvent, GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer, RotationGesture, SwipeGesture } from "./../../component/gesture"
import { NativeEmbedDataInfo_serializer, NativeEmbedTouchInfo_serializer, OnAlertEvent_serializer, OnAudioStateChangedEvent_serializer, OnBeforeUnloadEvent_serializer, OnClientAuthenticationEvent_serializer, OnConfirmEvent_serializer, OnConsoleEvent_serializer, OnContextMenuShowEvent_serializer, OnDataResubmittedEvent_serializer, OnDownloadStartEvent_serializer, OnErrorReceiveEvent_serializer, OnFaviconReceivedEvent_serializer, OnFirstContentfulPaintEvent_serializer, OnGeolocationShowEvent_serializer, OnHttpAuthRequestEvent_serializer, OnHttpErrorReceiveEvent_serializer, OnInterceptRequestEvent_serializer, WebResourceResponse_serializer, OnLoadInterceptEvent_serializer, OnOverScrollEvent_serializer, OnPageBeginEvent_serializer, OnPageEndEvent_serializer, OnPageVisibleEvent_serializer, OnPermissionRequestEvent_serializer, OnProgressChangeEvent_serializer, OnPromptEvent_serializer, OnRefreshAccessedHistoryEvent_serializer, OnRenderExitedEvent_serializer, OnResourceLoadEvent_serializer, OnScaleChangeEvent_serializer, OnScreenCaptureRequestEvent_serializer, OnScrollEvent_serializer, OnSearchResultReceiveEvent_serializer, OnShowFileSelectorEvent_serializer, OnSslErrorEventReceiveEvent_serializer, OnTitleReceiveEvent_serializer, OnTouchIconUrlReceivedEvent_serializer, OnWindowNewEvent_serializer, WebKeyboardOptions_serializer, AdsBlockedDetails_serializer, FirstMeaningfulPaint_serializer, FullScreenEnterEvent_serializer, IntelligentTrackingPreventionDetails_serializer, LargestContentfulPaint_serializer, NativeEmbedVisibilityInfo_serializer, LoadCommittedDetails_serializer, WebResourceRequest_serializer, RenderProcessNotRespondingData_serializer, SslErrorEvent_serializer, WebKeyboardCallbackInfo_serializer, NativeEmbedDataInfo, NativeEmbedTouchInfo, OnAlertEvent, OnAudioStateChangedEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnConsoleEvent, OnContextMenuShowEvent, OnDataResubmittedEvent, OnDownloadStartEvent, OnErrorReceiveEvent, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, WebResourceResponse, OnLoadInterceptEvent, OnOverScrollEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPermissionRequestEvent, OnProgressChangeEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnScreenCaptureRequestEvent, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, OnSslErrorEventReceiveEvent, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, WebKeyboardOptions, OnAdsBlockedCallback, AdsBlockedDetails, OnContextMenuHideCallback, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnFullScreenEnterCallback, FullScreenEnterEvent, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnOverrideUrlLoadingCallback, WebResourceRequest, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnSafeBrowsingCheckResultCallback, ThreatType, OnSslErrorEventCallback, SslErrorEvent, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo } from "./../../component/web"
import { NavDestinationContext_serializer, NavDestinationTransition_serializer, NavDestinationActiveReason, NavDestinationContext, NavDestinationTransition, NavDestinationTransitionDelegate } from "./../../component/navDestination"
import { NavigationTransitionProxy_serializer, NavigationAnimatedTransition_serializer, PopInfo_serializer, NavContentInfo_serializer, NavigationMode, NavigationTitleMode, NavigationTransitionProxy, NavigationAnimatedTransition, PopInfo, InterceptionModeCallback, InterceptionShowCallback, NavBar, NavigationOperation, NavContentInfo, UpdateTransitionCallback } from "./../../component/navigation"
import { OnScrollFrameBeginHandlerResult_serializer, OffsetResult_serializer, OnScrollFrameBeginHandlerResult, OffsetResult, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollOnScrollCallback, ScrollOnWillScrollCallback } from "./../../component/scroll"
import { Scene_serializer, ErrorEvent_serializer, MessageEvents_serializer, Callback_CreateItem, Callback_Extender_OnFinish, Callback_Extender_OnProgress, Callback_onMeasureSize_SizeResult, Callback_onPlaceChildren_Void, Scene, Callback_RangeUpdate, Callback_StateStylesChange, CustomNodeBuilder, NavExtender_OnUpdateStack, RestrictedWorker_onerror_Callback, ErrorEvent, RestrictedWorker_onexit_Callback, RestrictedWorker_onmessage_Callback, MessageEvents } from "./../../component/idlize"
import { TabContentAnimatedTransition_serializer, TabContentTransitionProxy_serializer, TabsAnimationEvent_serializer, TabContentAnimatedTransition, TabContentTransitionProxy, OnTabsAnimationEndCallback, TabsAnimationEvent, OnTabsAnimationStartCallback, OnTabsContentWillChangeCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback } from "./../../component/tabs"
import { Resource_serializer, Resource } from "./../resource"
import { SurfaceRect_serializer, SurfaceRect, OnNativeLoadCallback } from "./../../component/xcomponent"
import { SwiperContentTransitionProxy_serializer, SwiperContentWillScrollResult_serializer, SwiperAnimationEvent_serializer, SwiperContentTransitionProxy, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult, OnSwiperAnimationEndCallback, SwiperAnimationEvent, OnSwiperAnimationStartCallback, OnSwiperGestureSwipeCallback } from "./../../component/swiper"
import { TextPickerResult_serializer, TextPickerResult, OnTextPickerChangeCallback, TextPickerEnterSelectedAreaCallback, TextPickerScrollStopCallback } from "./../../component/textPicker"
import { TimePickerResult_serializer, TimePickerResult, OnTimePickerChangeCallback } from "./../../component/timePicker"
import { UIExtensionProxy_serializer, UIExtensionProxy } from "./../../component/uiExtensionComponent"
import { CheckBoxConfiguration_serializer, CheckBoxConfiguration, OnCheckboxChangeCallback } from "./../../component/checkbox"
import { DataPanelConfiguration_serializer, DataPanelConfiguration } from "./../../component/dataPanel"
import { BusinessError_serializer, ErrorCallback, BusinessError } from "./../ohos.base"
import { GaugeConfiguration_serializer, GaugeConfiguration } from "./../../component/gauge"
import { ImageLoadResult_serializer, ImageCompleteCallback, ImageLoadResult } from "./../../component/imageSpan"
import { ImageError_serializer, ImageCompleteEvent_serializer, ImageErrorCallback, ImageError, ImageOnCompleteCallback, ImageCompleteEvent } from "./../../component/image"
import { LoadingProgressConfiguration_serializer, LoadingProgressConfiguration } from "./../../component/loadingProgress"
import { MenuItemConfiguration_serializer, MenuItemConfiguration, OnSelectCallback } from "./../../component/select"
import { CheckboxGroupResult_serializer, OnCheckboxGroupChangeCallback, CheckboxGroupResult } from "./../../component/checkboxgroup"
import { OnFoldStatusChangeInfo_serializer, HoverEventParam_serializer, OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam } from "./../../component/folderStack"
import { VisibleListContentInfo_serializer, ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo } from "./../../component/list"
import { SubmitEvent_serializer, EnterKeyType, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, SubmitEvent, OnTextSelectionChangeCallback } from "./../../component/textInput"
import { PluginErrorData_serializer, PluginErrorCallback, PluginErrorData } from "./../../component/pluginComponent"
import { ProgressConfiguration_serializer, ProgressConfiguration } from "./../../component/progress"
import { RadioConfiguration_serializer, OnRadioChangeCallback, RadioConfiguration } from "./../../component/radio"
import { RatingConfiguration_serializer, OnRatingChangeCallback, RatingConfiguration } from "./../../component/rating"
import { SliderConfiguration_serializer, SliderChangeMode, SliderConfiguration, SliderTriggerChangeCallback } from "./../../component/slider"
import { TextClockConfiguration_serializer, TextClockConfiguration } from "./../../component/textClock"
import { TextTimerConfiguration_serializer, TextTimerConfiguration } from "./../../component/textTimer"
import { ToggleConfiguration_serializer, ToggleConfiguration } from "./../../component/toggle"
import { CallbackKind } from "./CallbackKind"
import { int32, float32, int64 } from "@koalaui/common"
import { ResourceHolder, KInt, KStringPtr, wrapSystemCallback, DeserializerBase, SerializerBase, CallbackResource, InteropNativeModule, KPointer, RuntimeType, KSerializerBuffer, NativeBuffer, runtimeType } from "@koalaui/interop"
import { CallbackTransformer } from "./../../CallbackTransformer"
import { LocationButtonOnClickResult } from "./../../component/locationButton"
import { PasteButtonOnClickResult } from "./../../component/pasteButton"
import { SaveButtonOnClickResult } from "./../../component/saveButton"
import { HitTestMode, Edge, ScrollSource } from "./../../component/enums"
import { MarqueeState } from "./../../component/text"
import { CustomBuilder, PageMapBuilder } from "./../../component/builder"
import { RefreshStatus } from "./../../component/refresh"
import { SwipeActionState } from "./../../component/listItem"
import { Context_getGroupDir_Callback } from "./../ohos.app.ability.common"
import { GetItemMainSizeByIndex } from "./../../component/waterFlow"
import { OnAlphabetIndexerPopupSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerSelectCallback } from "./../../component/alphabetIndexer"
import { OnLinearIndicatorChangeCallback } from "./../../component/linearindicator"
import { PageTransitionCallback, RouteType } from "./../../component/pageTransition"
import { SearchSubmitCallback } from "./../../component/search"
import { SearchValueCallback } from "./../searchOps"
import { TextAreaSubmitCallback } from "./../../component/textArea"
import { TextFieldValueCallback } from "./../textFieldOps"
import { TypeChecker } from "#components"
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
export function deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((result: image.PixelMap) => void))
    let result : image.PixelMap = (image_PixelMap_serializer.read(thisDeserializer) as image.PixelMap)
    _call(result)
}
export function deserializeAndCallButtonModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ButtonConfiguration = ButtonConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallButtonTriggerClickCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ButtonTriggerClickCallback)
    let xPos : number = (thisDeserializer.readNumber() as number)
    let yPos : number = (thisDeserializer.readNumber() as number)
    _call(xPos, yPos)
}
export function deserializeAndCallCallback_Area_Area_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((oldValue: Area,newValue: Area) => void))
    let oldValue : Area = Area_serializer.read(thisDeserializer)
    let newValue : Area = Area_serializer.read(thisDeserializer)
    _call(oldValue, newValue)
}
export function deserializeAndCallCallback_Array_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((input: Array<number>) => void))
    const input_buf_length : int32 = thisDeserializer.readInt32()
    let input_buf : Array<number> = new Array<number>(input_buf_length)
    for (let input_buf_i = 0; input_buf_i < input_buf_length; input_buf_i++) {
        input_buf[input_buf_i] = (thisDeserializer.readNumber() as number)
    }
    let input : Array<number> = input_buf
    _call(input)
}
export function deserializeAndCallCallback_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<string>) => void))
    const value_buf_length : int32 = thisDeserializer.readInt32()
    let value_buf : Array<string> = new Array<string>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = (thisDeserializer.readString() as string)
    }
    let value : Array<string> = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TextMenuItem>) => void))
    const value_buf_length : int32 = thisDeserializer.readInt32()
    let value_buf : Array<TextMenuItem> = new Array<TextMenuItem>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let value : Array<TextMenuItem> = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TouchTestInfo>) => TouchResult))
    const value_buf_length : int32 = thisDeserializer.readInt32()
    let value_buf : Array<TouchTestInfo> = new Array<TouchTestInfo>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = TouchTestInfo_serializer.read(thisDeserializer)
    }
    let value : Array<TouchTestInfo> = value_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: TouchResult) => void) = (value: TouchResult):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    TouchResult_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(1943507619, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call()
    _continuation(_callResult)
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
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: NativeBuffer) => void))
    let value : NativeBuffer = (thisDeserializer.readBuffer() as NativeBuffer)
    _call(value)
}
export function deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent,result: LocationButtonOnClickResult) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : LocationButtonOnClickResult = TypeChecker.LocationButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent,result: PasteButtonOnClickResult) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : PasteButtonOnClickResult = TypeChecker.PasteButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent,result: SaveButtonOnClickResult) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    let result : SaveButtonOnClickResult = TypeChecker.SaveButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent) => void))
    let event : ClickEvent = (ClickEvent_serializer.read(thisDeserializer) as ClickEvent)
    _call(event)
}
export function deserializeAndCallCallback_CompatibleComponentInfo_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CompatibleComponentInfo) => void))
    let value : CompatibleComponentInfo = CompatibleComponentInfo_serializer.read(thisDeserializer)
    _call(value)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: CustomSpanMetrics) => void) = (value: CustomSpanMetrics):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    CustomSpanMetrics_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(1362306791, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(measureInfo)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
    const extraParams_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParams_buf : string | undefined
    if ((extraParams_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((enterKey: EnterKeyType) => void))
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    _call(enterKey)
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
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: GestureEvent) => void))
    let event : GestureEvent = (GestureEvent_serializer.read(thisDeserializer) as GestureEvent)
    _call(event)
}
export function deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult))
    let gestureInfo : GestureInfo = GestureInfo_serializer.read(thisDeserializer)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: GestureJudgeResult) => void) = (value: GestureJudgeResult):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeInt32(TypeChecker.GestureJudgeResult_ToNumeric(value));
    InteropNativeModule._CallCallbackSync(-684588584, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(gestureInfo, event)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: GestureJudgeResult) => void))
    let value : GestureJudgeResult = TypeChecker.GestureJudgeResult_FromNumeric(thisDeserializer.readInt32())
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
    let value : HitTestMode = TypeChecker.HitTestMode_FromNumeric(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_HoverEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: HoverEvent) => void))
    let value0 : HoverEvent = (HoverEvent_serializer.read(thisDeserializer) as HoverEvent)
    _call(value0)
}
export function deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: InsertValue) => boolean))
    let value0 : InsertValue = InsertValue_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_InsertValue_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: InsertValue) => void))
    let value0 : InsertValue = InsertValue_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let insertIndex : number = (thisDeserializer.readNumber() as number)
    let isSuccess : boolean = thisDeserializer.readBoolean()
    _call(event, itemIndex, insertIndex, isSuccess)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let insertIndex : number = (thisDeserializer.readNumber() as number)
    _call(event, itemIndex, insertIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number) => void))
    let event : ItemDragInfo = ItemDragInfo_serializer.read(thisDeserializer)
    let itemIndex : number = (thisDeserializer.readNumber() as number)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_KeyEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: KeyEvent) => void))
    let event : KeyEvent = (KeyEvent_serializer.read(thisDeserializer) as KeyEvent)
    _call(event)
}
export function deserializeAndCallCallback_Map_String_Object_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Map<string, Object>) => void))
    const value0_buf_size : int32 = thisDeserializer.readInt32()
    let value0_buf : Map<string, Object> = new Map<string, Object>()
    // TODO: TS map resize
    for (let value0_buf_i = 0; value0_buf_i < value0_buf_size; value0_buf_i++) {
        const value0_buf_key : string = (thisDeserializer.readString() as string)
        const value0_buf_value : Object = (thisDeserializer.readObject() as object)
        value0_buf.set(value0_buf_key, value0_buf_value)
    }
    let value0 : Map<string, Object> = value0_buf
    _call(value0)
}
export function deserializeAndCallCallback_MarqueeState_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: MarqueeState) => void))
    let value0 : MarqueeState = TypeChecker.MarqueeState_FromNumeric(thisDeserializer.readInt32())
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
export function deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: NavDestinationActiveReason) => void))
    let value0 : NavDestinationActiveReason = TypeChecker.NavDestinationActiveReason_FromNumeric(thisDeserializer.readInt32())
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
    let mode : NavigationMode = TypeChecker.NavigationMode_FromNumeric(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((titleMode: NavigationTitleMode) => void))
    let titleMode : NavigationTitleMode = TypeChecker.NavigationTitleMode_FromNumeric(thisDeserializer.readInt32())
    _call(titleMode)
}
export function deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((transitionProxy: NavigationTransitionProxy) => void))
    let transitionProxy : NavigationTransitionProxy = (NavigationTransitionProxy_serializer.read(thisDeserializer) as NavigationTransitionProxy)
    _call(transitionProxy)
}
export function deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: number,to: number) => boolean))
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Boolean_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((offset: number,index: number,leadingEdge: boolean) => boolean))
    let offset : number = (thisDeserializer.readNumber() as number)
    let index : number = (thisDeserializer.readNumber() as number)
    let leadingEdge : boolean = thisDeserializer.readBoolean()
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(offset, index, leadingEdge)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number,offset: number) => ComputedBarAttribute))
    let index : number = (thisDeserializer.readNumber() as number)
    let offset : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: ComputedBarAttribute) => void) = (value: ComputedBarAttribute):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    ComputedBarAttribute_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(-1270343661, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index, offset)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((start: number,end: number,center: number) => void))
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    let center : number = (thisDeserializer.readNumber() as number)
    _call(start, end, center)
}
export function deserializeAndCallCallback_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((first: number,last: number) => void))
    let first : number = (thisDeserializer.readNumber() as number)
    let last : number = (thisDeserializer.readNumber() as number)
    _call(first, last)
}
export function deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: number,mode: SliderChangeMode) => void))
    let value : number = (thisDeserializer.readNumber() as number)
    let mode : SliderChangeMode = TypeChecker.SliderChangeMode_FromNumeric(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number ]))
    let index : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: [ number, number ]) => void) = (value: [ number, number ]):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    const value_0  = value[0];
    _continuation_buf_argsSerializer.writeNumber(value_0);
    const value_1  = value[1];
    _continuation_buf_argsSerializer.writeNumber(value_1);
    InteropNativeModule._CallCallbackSync(-607365481, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number, number, number ]))
    let index : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: [ number, number, number, number ]) => void) = (value: [ number, number, number, number ]):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    const value_0  = value[0];
    _continuation_buf_argsSerializer.writeNumber(value_0);
    const value_1  = value[1];
    _continuation_buf_argsSerializer.writeNumber(value_1);
    const value_2  = value[2];
    _continuation_buf_argsSerializer.writeNumber(value_2);
    const value_3  = value[3];
    _continuation_buf_argsSerializer.writeNumber(value_3);
    InteropNativeModule._CallCallbackSync(148489367, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: number) => void))
    let value0 : number = (thisDeserializer.readNumber() as number)
    _call(value0)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnConsoleEvent) => boolean))
    let value0 : OnConsoleEvent = OnConsoleEvent_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnContextMenuShowEvent) => boolean))
    let value0 : OnContextMenuShowEvent = OnContextMenuShowEvent_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnDataResubmittedEvent) => void))
    let value0 : OnDataResubmittedEvent = OnDataResubmittedEvent_serializer.read(thisDeserializer)
    _call(value0)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnHttpErrorReceiveEvent) => void))
    let value0 : OnHttpErrorReceiveEvent = OnHttpErrorReceiveEvent_serializer.read(thisDeserializer)
    _call(value0)
}
export function deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnInterceptRequestEvent) => WebResourceResponse))
    let value0 : OnInterceptRequestEvent = OnInterceptRequestEvent_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: WebResourceResponse) => void) = (value: WebResourceResponse):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    WebResourceResponse_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(831645046, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: OnLoadInterceptEvent) => boolean))
    let value0 : OnLoadInterceptEvent = OnLoadInterceptEvent_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_onMeasureSize_SizeResult)
    let selfLayoutInfo : GeometryInfo = GeometryInfo_serializer.read(thisDeserializer)
    const children_buf_length : int32 = thisDeserializer.readInt32()
    let children_buf : Array<Measurable> = new Array<Measurable>(children_buf_length)
    for (let children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf[children_buf_i] = (Measurable_serializer.read(thisDeserializer) as Measurable)
    }
    let children : Array<Measurable> = children_buf
    let constraint : ConstraintSizeOptions = ConstraintSizeOptions_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: SizeResult) => void) = (value: SizeResult):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    SizeResult_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(1318865891, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(selfLayoutInfo, children, constraint)
    _continuation(_callResult)
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
    const children_buf_length : int32 = thisDeserializer.readInt32()
    let children_buf : Array<Layoutable> = new Array<Layoutable>(children_buf_length)
    for (let children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf[children_buf_i] = (Layoutable_serializer.read(thisDeserializer) as Layoutable)
    }
    let children : Array<Layoutable> = children_buf
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
export function deserializeAndCallCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: Array<object> | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : Array<object> | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const value_buf__length : int32 = thisDeserializer.readInt32()
        let value_buf_ : Array<object> = new Array<object>(value_buf__length)
        for (let value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_[value_buf__i] = (thisDeserializer.readCustomObject("object") as object)
        }
        value_buf = value_buf_
    }
    let value : Array<object> | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<NavDestinationTransition> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : Array<NavDestinationTransition> | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const value_buf__length : int32 = thisDeserializer.readInt32()
        let value_buf_ : Array<NavDestinationTransition> = new Array<NavDestinationTransition>(value_buf__length)
        for (let value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_[value_buf__i] = NavDestinationTransition_serializer.read(thisDeserializer)
        }
        value_buf = value_buf_
    }
    let value : Array<NavDestinationTransition> | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Array_String_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: Array<string> | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : Array<string> | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const value_buf__length : int32 = thisDeserializer.readInt32()
        let value_buf_ : Array<string> = new Array<string>(value_buf__length)
        for (let value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_[value_buf__i] = (thisDeserializer.readString() as string)
        }
        value_buf = value_buf_
    }
    let value : Array<string> | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((error?: Array<string> | undefined) => void))
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(error)
}
export function deserializeAndCallCallback_Opt_Boolean_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((select: boolean | undefined) => void))
    const select_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let select_buf : boolean | undefined
    if ((select_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        select_buf = thisDeserializer.readBoolean()
    }
    let select : boolean | undefined = select_buf
    _call(select)
}
export function deserializeAndCallCallback_Opt_CustomBuilder_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : CustomBuilder | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const value_buf__resource : CallbackResource = thisDeserializer.readCallbackResource()
        const value_buf__call : KPointer = thisDeserializer.readPointer()
        const value_buf__callSync : KPointer = thisDeserializer.readPointer()
        value_buf = ():void => { 
    const value_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    value_buf__argsSerializer.writeInt32(value_buf__resource.resourceId);
    value_buf__argsSerializer.writePointer(value_buf__call);
    value_buf__argsSerializer.writePointer(value_buf__callSync);
    InteropNativeModule._CallCallback(737226752, value_buf__argsSerializer.asBuffer(), value_buf__argsSerializer.length());
    value_buf__argsSerializer.release();
    return; }
    }
    let value : CustomBuilder | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_FontDescriptor_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: object | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : object | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = (thisDeserializer.readCustomObject("object") as object)
    }
    let value : object | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: NavigationAnimatedTransition | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : NavigationAnimatedTransition | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = NavigationAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : NavigationAnimatedTransition | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | undefined) => void))
    const selected_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let selected_buf : number | undefined
    if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    let selected : number | undefined = selected_buf
    _call(selected)
}
export function deserializeAndCallCallback_Opt_Object_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: Object | undefined) => void))
    const value0_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value0_buf : Object | undefined
    if ((value0_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value0_buf = (thisDeserializer.readObject() as object)
    }
    let value0 : Object | undefined = value0_buf
    _call(value0)
}
export function deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: OffsetResult | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : OffsetResult | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = OffsetResult_serializer.read(thisDeserializer)
    }
    let value : OffsetResult | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Scene_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: Scene | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : Scene | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = (Scene_serializer.read(thisDeserializer) as Scene)
    }
    let value : Scene | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ScrollResult | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : ScrollResult | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = (ScrollResult_serializer.read(thisDeserializer) as ScrollResult)
    }
    let value : ScrollResult | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_String_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: string | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : string | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = (thisDeserializer.readString() as string)
    }
    let value : string | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: StyledString | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : StyledString | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = (StyledString_serializer.read(thisDeserializer) as StyledString)
    }
    let value : StyledString | undefined = value_buf
    const error_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let error_buf : Array<string> | undefined
    if ((error_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const error_buf__length : int32 = thisDeserializer.readInt32()
        let error_buf_ : Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error : Array<string> | undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TabContentAnimatedTransition | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : TabContentAnimatedTransition | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        value_buf = TabContentAnimatedTransition_serializer.read(thisDeserializer)
    }
    let value : TabContentAnimatedTransition | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Union_Number_Resource_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Resource | undefined) => void))
    const selected_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let selected_buf : number | Resource | undefined
    if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const selected_buf__selector : int32 = thisDeserializer.readInt8()
        let selected_buf_ : number | Resource | undefined
        if (selected_buf__selector == (0).toChar()) {
            selected_buf_ = (thisDeserializer.readNumber() as number)
        }
        else if (selected_buf__selector == (1).toChar()) {
            selected_buf_ = Resource_serializer.read(thisDeserializer)
        }
        else {
            throw new Error("One of the branches for selected_buf_ has to be chosen through deserialisation.")
        }
        selected_buf = (selected_buf_ as number | Resource)
    }
    let selected : number | Resource | undefined = selected_buf
    _call(selected)
}
export function deserializeAndCallCallback_Opt_Union_ResourceStr_String_Resource_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ResourceStr | string | Resource | undefined) => void))
    const value_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let value_buf : ResourceStr | string | Resource | undefined
    if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        const value_buf__selector : int32 = thisDeserializer.readInt8()
        let value_buf_ : ResourceStr | string | Resource | undefined
        if (value_buf__selector == (0).toChar()) {
            const value_buf__u_selector : int32 = thisDeserializer.readInt8()
            let value_buf__u : string | Resource | undefined
            if (value_buf__u_selector == (0).toChar()) {
                value_buf__u = (thisDeserializer.readString() as string)
            }
            else if (value_buf__u_selector == (1).toChar()) {
                value_buf__u = Resource_serializer.read(thisDeserializer)
            }
            else {
                throw new Error("One of the branches for value_buf__u has to be chosen through deserialisation.")
            }
            value_buf_ = (value_buf__u as string | Resource)
        }
        else if (value_buf__selector == (1).toChar()) {
            value_buf_ = (thisDeserializer.readString() as string)
        }
        else if (value_buf__selector == (2).toChar()) {
            value_buf_ = Resource_serializer.read(thisDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf_ has to be chosen through deserialisation.")
        }
        value_buf = (value_buf_ as ResourceStr | string | Resource)
    }
    let value : ResourceStr | string | Resource | undefined = value_buf
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
    let value0 : PreDragStatus = TypeChecker.PreDragStatus_FromNumeric(thisDeserializer.readInt32())
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
    _call(start, end)
}
export function deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: RefreshStatus) => void))
    let state : RefreshStatus = TypeChecker.RefreshStatus_FromNumeric(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorChangeValue) => boolean))
    let value0 : RichEditorChangeValue = RichEditorChangeValue_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorDeleteValue) => boolean))
    let value0 : RichEditorDeleteValue = RichEditorDeleteValue_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: RichEditorInsertValue) => boolean))
    let value0 : RichEditorInsertValue = RichEditorInsertValue_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
export function deserializeAndCallCallback_RotationGesture(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => RotationGesture))
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: RotationGesture) => void) = (value: RotationGesture):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    RotationGesture_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(924806076, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RotationGesture_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: RotationGesture) => void))
    let value : RotationGesture = (RotationGesture_serializer.read(thisDeserializer) as RotationGesture)
    _call(value)
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
    let value0 : SheetType = TypeChecker.SheetType_FromNumeric(thisDeserializer.readInt32())
    _call(value0)
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
    let value0 : SpringBackAction = SpringBackAction_serializer.read(thisDeserializer)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: UserDataSpan) => void))
    let value : UserDataSpan = (UserDataSpan_serializer.read(thisDeserializer) as UserDataSpan)
    _call(value)
}
export function deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: SwipeActionState) => void))
    let state : SwipeActionState = TypeChecker.SwipeActionState_FromNumeric(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_SwipeGesture(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => SwipeGesture))
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: SwipeGesture) => void) = (value: SwipeGesture):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    SwipeGesture_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(-768726640, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallCallback_SwipeGesture_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: SwipeGesture) => void))
    let value : SwipeGesture = (SwipeGesture_serializer.read(thisDeserializer) as SwipeGesture)
    _call(value)
}
export function deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value0: SwiperContentTransitionProxy) => void))
    let value0 : SwiperContentTransitionProxy = (SwiperContentTransitionProxy_serializer.read(thisDeserializer) as SwiperContentTransitionProxy)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: HitTestMode) => void) = (value: HitTestMode):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeInt32(TypeChecker.HitTestMode_ToNumeric(value));
    InteropNativeModule._CallCallbackSync(-1755111025, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(value0)
    _continuation(_callResult)
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
export function deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number, number, number ]) => void))
    const value_buf_value0 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value1 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value2 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value3 : number = (thisDeserializer.readNumber() as number)
    let value : [ number, number, number, number ] = ([value_buf_value0, value_buf_value1, value_buf_value2, value_buf_value3] as [ number, number, number, number ])
    _call(value)
}
export function deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number ]) => void))
    const value_buf_value0 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value1 : number = (thisDeserializer.readNumber() as number)
    let value : [ number, number ] = ([value_buf_value0, value_buf_value1] as [ number, number ])
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
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : CustomBuilder | DragItemInfo | undefined
    if (value_buf_selector == (0).toChar()) {
        const value_buf_u_resource : CallbackResource = thisDeserializer.readCallbackResource()
        const value_buf_u_call : KPointer = thisDeserializer.readPointer()
        const value_buf_u_callSync : KPointer = thisDeserializer.readPointer()
        value_buf = ():void => { 
    const value_buf_u_argsSerializer : SerializerBase = SerializerBase.hold();
    value_buf_u_argsSerializer.writeInt32(value_buf_u_resource.resourceId);
    value_buf_u_argsSerializer.writePointer(value_buf_u_call);
    value_buf_u_argsSerializer.writePointer(value_buf_u_callSync);
    InteropNativeModule._CallCallback(737226752, value_buf_u_argsSerializer.asBuffer(), value_buf_u_argsSerializer.length());
    value_buf_u_argsSerializer.release();
    return; }
    }
    else if (value_buf_selector == (1).toChar()) {
        value_buf = DragItemInfo_serializer.read(thisDeserializer)
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : CustomBuilder | DragItemInfo = (value_buf as CustomBuilder | DragItemInfo)
    _call(value)
}
export function deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Array<number>) => void))
    const selected_buf_selector : int32 = thisDeserializer.readInt8()
    let selected_buf : number | Array<number> | undefined
    if (selected_buf_selector == (0).toChar()) {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    else if (selected_buf_selector == (1).toChar()) {
        const selected_buf_u_length : int32 = thisDeserializer.readInt32()
        let selected_buf_u : Array<number> = new Array<number>(selected_buf_u_length)
        for (let selected_buf_u_i = 0; selected_buf_u_i < selected_buf_u_length; selected_buf_u_i++) {
            selected_buf_u[selected_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        selected_buf = selected_buf_u
    }
    else {
        throw new Error("One of the branches for selected_buf has to be chosen through deserialisation.")
    }
    let selected : number | Array<number> = (selected_buf as number | Array<number>)
    _call(selected)
}
export function deserializeAndCallCallback_Union_ResourceStr_Array_ResourceStr_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ResourceStr | Array<ResourceStr>) => void))
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : ResourceStr | Array<ResourceStr> | undefined
    if (value_buf_selector == (0).toChar()) {
        const value_buf_u_selector : int32 = thisDeserializer.readInt8()
        let value_buf_u : string | Resource | undefined
        if (value_buf_u_selector == (0).toChar()) {
            value_buf_u = (thisDeserializer.readString() as string)
        }
        else if (value_buf_u_selector == (1).toChar()) {
            value_buf_u = Resource_serializer.read(thisDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf_u has to be chosen through deserialisation.")
        }
        value_buf = (value_buf_u as string | Resource)
    }
    else if (value_buf_selector == (1).toChar()) {
        const value_buf_u_length : int32 = thisDeserializer.readInt32()
        let value_buf_u : Array<ResourceStr> = new Array<ResourceStr>(value_buf_u_length)
        for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            const value_buf_u_buf_selector : int32 = thisDeserializer.readInt8()
            let value_buf_u_buf : string | Resource | undefined
            if (value_buf_u_buf_selector == (0).toChar()) {
                value_buf_u_buf = (thisDeserializer.readString() as string)
            }
            else if (value_buf_u_buf_selector == (1).toChar()) {
                value_buf_u_buf = Resource_serializer.read(thisDeserializer)
            }
            else {
                throw new Error("One of the branches for value_buf_u_buf has to be chosen through deserialisation.")
            }
            value_buf_u[value_buf_u_i] = (value_buf_u_buf as string | Resource)
        }
        value_buf = value_buf_u
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : ResourceStr | Array<ResourceStr> = (value_buf as ResourceStr | Array<ResourceStr>)
    _call(value)
}
export function deserializeAndCallCallback_Union_ResourceStr_Resource_String_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((text: ResourceStr | Resource | string) => void))
    const text_buf_selector : int32 = thisDeserializer.readInt8()
    let text_buf : ResourceStr | Resource | string | undefined
    if (text_buf_selector == (0).toChar()) {
        const text_buf_u_selector : int32 = thisDeserializer.readInt8()
        let text_buf_u : string | Resource | undefined
        if (text_buf_u_selector == (0).toChar()) {
            text_buf_u = (thisDeserializer.readString() as string)
        }
        else if (text_buf_u_selector == (1).toChar()) {
            text_buf_u = Resource_serializer.read(thisDeserializer)
        }
        else {
            throw new Error("One of the branches for text_buf_u has to be chosen through deserialisation.")
        }
        text_buf = (text_buf_u as string | Resource)
    }
    else if (text_buf_selector == (1).toChar()) {
        text_buf = Resource_serializer.read(thisDeserializer)
    }
    else if (text_buf_selector == (2).toChar()) {
        text_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for text_buf has to be chosen through deserialisation.")
    }
    let text : ResourceStr | Resource | string = (text_buf as ResourceStr | Resource | string)
    _call(text)
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
export function deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WebResourceResponse) => void))
    let value : WebResourceResponse = (WebResourceResponse_serializer.read(thisDeserializer) as WebResourceResponse)
    _call(value)
}
export function deserializeAndCallCheckBoxModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : CheckBoxConfiguration = CheckBoxConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallCompatibleInitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CompatibleInitCallback)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: CompatibleComponentInfo) => void) = (value: CompatibleComponentInfo):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    CompatibleComponentInfo_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(-494015096, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallCompatibleUpdateCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CompatibleUpdateCallback)
    let component : object = (thisDeserializer.readCustomObject("object") as object)
    _call(component)
}
export function deserializeAndCallContentDidScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentDidScrollCallback)
    let selectedIndex : number = (thisDeserializer.readNumber() as number)
    let index : number = (thisDeserializer.readNumber() as number)
    let position : number = (thisDeserializer.readNumber() as number)
    let mainAxisLength : number = (thisDeserializer.readNumber() as number)
    _call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallContentWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentWillScrollCallback)
    let result : SwiperContentWillScrollResult = SwiperContentWillScrollResult_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(result)
    _continuation(_callResult)
}
export function deserializeAndCallContext_getGroupDir_Callback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Context_getGroupDir_Callback)
    let result : string = (thisDeserializer.readString() as string)
    _call(result)
}
export function deserializeAndCallCustomNodeBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CustomNodeBuilder)
    let parentNode : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode)
    _continuation(_callResult)
}
export function deserializeAndCallDataPanelModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : DataPanelConfiguration = DataPanelConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallEditableTextOnChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as EditableTextOnChangeCallback)
    let value : string = (thisDeserializer.readString() as string)
    const previewText_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let previewText_buf : PreviewText | undefined
    if ((previewText_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        previewText_buf = PreviewText_serializer.read(thisDeserializer)
    }
    let previewText : PreviewText | undefined = previewText_buf
    const options_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let options_buf : TextChangeOptions | undefined
    if ((options_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        options_buf = TextChangeOptions_serializer.read(thisDeserializer)
    }
    let options : TextChangeOptions | undefined = options_buf
    _call(value, previewText, options)
}
export function deserializeAndCallErrorCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ErrorCallback)
    let error : BusinessError = BusinessError_serializer.read(thisDeserializer)
    _call(error)
}
export function deserializeAndCallGaugeModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: GaugeConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : GaugeConfiguration = GaugeConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GestureRecognizerJudgeBeginCallback)
    let event : BaseGestureEvent = (BaseGestureEvent_serializer.read(thisDeserializer) as BaseGestureEvent)
    let current : GestureRecognizer = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    const recognizers_buf_length : int32 = thisDeserializer.readInt32()
    let recognizers_buf : Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizers_buf_length)
    for (let recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf[recognizers_buf_i] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let recognizers : Array<GestureRecognizer> = recognizers_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: GestureJudgeResult) => void) = (value: GestureJudgeResult):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeInt32(TypeChecker.GestureJudgeResult_ToNumeric(value));
    InteropNativeModule._CallCallbackSync(-684588584, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(event, current, recognizers)
    _continuation(_callResult)
}
export function deserializeAndCallGetItemMainSizeByIndex(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GetItemMainSizeByIndex)
    let index : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: number) => void) = (value: number):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeNumber(value);
    InteropNativeModule._CallCallbackSync(36519084, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index)
    _continuation(_callResult)
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
    const loadEvent_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let loadEvent_buf : ImageCompleteEvent | undefined
    if ((loadEvent_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        loadEvent_buf = ImageCompleteEvent_serializer.read(thisDeserializer)
    }
    let loadEvent : ImageCompleteEvent | undefined = loadEvent_buf
    _call(loadEvent)
}
export function deserializeAndCallInterceptionModeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionModeCallback)
    let mode : NavigationMode = TypeChecker.NavigationMode_FromNumeric(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallInterceptionShowCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionShowCallback)
    const from_buf_selector : int32 = thisDeserializer.readInt8()
    let from_buf : NavDestinationContext | NavBar | undefined
    if (from_buf_selector == (0).toChar()) {
        from_buf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    }
    else if (from_buf_selector == (1).toChar()) {
        from_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for from_buf has to be chosen through deserialisation.")
    }
    let from : NavDestinationContext | NavBar = (from_buf as NavDestinationContext | NavBar)
    const to_buf_selector : int32 = thisDeserializer.readInt8()
    let to_buf : NavDestinationContext | NavBar | undefined
    if (to_buf_selector == (0).toChar()) {
        to_buf = (NavDestinationContext_serializer.read(thisDeserializer) as NavDestinationContext)
    }
    else if (to_buf_selector == (1).toChar()) {
        to_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for to_buf has to be chosen through deserialisation.")
    }
    let to : NavDestinationContext | NavBar = (to_buf as NavDestinationContext | NavBar)
    let operation : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(thisDeserializer.readInt32())
    let isAnimated : boolean = thisDeserializer.readBoolean()
    _call(from, to, operation, isAnimated)
}
export function deserializeAndCallLoadingProgressModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : LoadingProgressConfiguration = LoadingProgressConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallMenuCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuCallback)
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    _call(start, end)
}
export function deserializeAndCallMenuItemModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : MenuItemConfiguration = MenuItemConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallMenuOnAppearCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuOnAppearCallback)
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    _call(start, end)
}
export function deserializeAndCallModifierKeyStateGetter(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ModifierKeyStateGetter)
    const keys_buf_length : int32 = thisDeserializer.readInt32()
    let keys_buf : Array<string> = new Array<string>(keys_buf_length)
    for (let keys_buf_i = 0; keys_buf_i < keys_buf_length; keys_buf_i++) {
        keys_buf[keys_buf_i] = (thisDeserializer.readString() as string)
    }
    let keys : Array<string> = keys_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(keys)
    _continuation(_callResult)
}
export function deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavDestinationTransitionDelegate)
    let operation : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(thisDeserializer.readInt32())
    let isEnter : boolean = thisDeserializer.readBoolean()
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: Array<NavDestinationTransition> | undefined) => void) = (value?: Array<NavDestinationTransition> | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        _continuation_buf_argsSerializer.writeInt32((value_value.length).toInt());
        for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
            const value_value_element : NavDestinationTransition = value_value[value_value_counter_i];
            NavDestinationTransition_serializer.write(_continuation_buf_argsSerializer, value_value_element);
        }
    }
    InteropNativeModule._CallCallbackSync(406871767, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(operation, isEnter)
    _continuation(_callResult)
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
    let index : number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerRequestPopupDataCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: Array<string>) => void) = (value: Array<string>):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeInt32((value.length).toInt());
    for (let value_counter_i = 0; value_counter_i < value.length; value_counter_i++) {
        const value_element : string = value[value_counter_i];
        _continuation_buf_argsSerializer.writeString(value_element);
    }
    InteropNativeModule._CallCallbackSync(-440782244, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerSelectCallback)
    let index : number = (thisDeserializer.readNumber() as number)
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
    let totalOffsetX : number = (thisDeserializer.readNumber() as number)
    let totalOffsetY : number = (thisDeserializer.readNumber() as number)
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
    const menuItems_buf_length : int32 = thisDeserializer.readInt32()
    let menuItems_buf : Array<TextMenuItem> = new Array<TextMenuItem>(menuItems_buf_length)
    for (let menuItems_buf_i = 0; menuItems_buf_i < menuItems_buf_length; menuItems_buf_i++) {
        menuItems_buf[menuItems_buf_i] = TextMenuItem_serializer.read(thisDeserializer)
    }
    let menuItems : Array<TextMenuItem> = menuItems_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeInt32((value.length).toInt());
    for (let value_counter_i = 0; value_counter_i < value.length; value_counter_i++) {
        const value_element : TextMenuItem = value[value_counter_i];
        TextMenuItem_serializer.write(_continuation_buf_argsSerializer, value_element);
    }
    InteropNativeModule._CallCallbackSync(528588498, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(menuItems)
    _continuation(_callResult)
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
    const extraParams_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParams_buf : string | undefined
    if ((extraParams_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
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
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: CustomBuilder | undefined) => void) = (value?: CustomBuilder | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        _continuation_buf_argsSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value));
    }
    InteropNativeModule._CallCallbackSync(859020393, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(event, itemIndex)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(menuItem, range)
    _continuation(_callResult)
}
export function deserializeAndCallOnMoveHandler(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnMoveHandler)
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    _call(from, to)
}
export function deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeEmbedVisibilityChangeCallback)
    let nativeEmbedVisibilityInfo : NativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer.read(thisDeserializer)
    _call(nativeEmbedVisibilityInfo)
}
export function deserializeAndCallOnNativeLoadCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeLoadCallback)
    const event_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let event_buf : Object | undefined
    if ((event_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        event_buf = (thisDeserializer.readObject() as object)
    }
    let event : Object | undefined = event_buf
    _call(event)
}
export function deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNavigationEntryCommittedCallback)
    let loadCommittedDetails : LoadCommittedDetails = LoadCommittedDetails_serializer.read(thisDeserializer)
    _call(loadCommittedDetails)
}
export function deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnOverrideUrlLoadingCallback)
    let webResourceRequest : WebResourceRequest = (WebResourceRequest_serializer.read(thisDeserializer) as WebResourceRequest)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(webResourceRequest)
    _continuation(_callResult)
}
export function deserializeAndCallOnPasteCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnPasteCallback)
    let content : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = PasteEvent_serializer.read(thisDeserializer)
    _call(content, event)
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
    let rating : number = (thisDeserializer.readNumber() as number)
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
    let threatType : ThreatType = TypeChecker.ThreatType_FromNumeric(thisDeserializer.readInt32())
    _call(threatType)
}
export function deserializeAndCallOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollCallback)
    let scrollOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    _call(scrollOffset, scrollState)
}
export function deserializeAndCallOnScrollEdgeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollEdgeCallback)
    let side : Edge = TypeChecker.Edge_FromNumeric(thisDeserializer.readInt32())
    _call(side)
}
export function deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollFrameBeginCallback)
    let offset : number = (thisDeserializer.readNumber() as number)
    let state : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: OnScrollFrameBeginHandlerResult) => void) = (value: OnScrollFrameBeginHandlerResult):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    OnScrollFrameBeginHandlerResult_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(1637092936, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(offset, state)
    _continuation(_callResult)
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
    let index : number = (thisDeserializer.readNumber() as number)
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
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationEndCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationStartCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let targetIndex : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperGestureSwipeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = SwiperAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationEndCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationStartCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let targetIndex : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsContentWillChangeCallback)
    let currentIndex : number = (thisDeserializer.readNumber() as number)
    let comingIndex : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value0: boolean) => void) = (value0: boolean):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallbackSync(313269291, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(currentIndex, comingIndex)
    _continuation(_callResult)
}
export function deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsGestureSwipeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = TabsAnimationEvent_serializer.read(thisDeserializer)
    _call(index, extraInfo)
}
export function deserializeAndCallOnTextPickerChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextPickerChangeCallback)
    const selectItem_buf_selector : int32 = thisDeserializer.readInt8()
    let selectItem_buf : string | Array<string> | undefined
    if (selectItem_buf_selector == (0).toChar()) {
        selectItem_buf = (thisDeserializer.readString() as string)
    }
    else if (selectItem_buf_selector == (1).toChar()) {
        const selectItem_buf_u_length : int32 = thisDeserializer.readInt32()
        let selectItem_buf_u : Array<string> = new Array<string>(selectItem_buf_u_length)
        for (let selectItem_buf_u_i = 0; selectItem_buf_u_i < selectItem_buf_u_length; selectItem_buf_u_i++) {
            selectItem_buf_u[selectItem_buf_u_i] = (thisDeserializer.readString() as string)
        }
        selectItem_buf = selectItem_buf_u
    }
    else {
        throw new Error("One of the branches for selectItem_buf has to be chosen through deserialisation.")
    }
    let selectItem : string | Array<string> = (selectItem_buf as string | Array<string>)
    const index_buf_selector : int32 = thisDeserializer.readInt8()
    let index_buf : number | Array<number> | undefined
    if (index_buf_selector == (0).toChar()) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == (1).toChar()) {
        const index_buf_u_length : int32 = thisDeserializer.readInt32()
        let index_buf_u : Array<number> = new Array<number>(index_buf_u_length)
        for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u[index_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        index_buf = index_buf_u
    }
    else {
        throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
    }
    let index : number | Array<number> = (index_buf as number | Array<number>)
    _call(selectItem, index)
}
export function deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextSelectionChangeCallback)
    let selectionStart : number = (thisDeserializer.readNumber() as number)
    let selectionEnd : number = (thisDeserializer.readNumber() as number)
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
    let viewportFit : ViewportFit = TypeChecker.ViewportFit_FromNumeric(thisDeserializer.readInt32())
    _call(viewportFit)
}
export function deserializeAndCallOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnWillScrollCallback)
    let scrollOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = TypeChecker.ScrollSource_FromNumeric(thisDeserializer.readInt32())
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: ScrollResult | undefined) => void) = (value?: ScrollResult | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        ScrollResult_serializer.write(_continuation_buf_argsSerializer, value_value);
    }
    InteropNativeModule._CallCallbackSync(648568223, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(scrollOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallPageMapBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PageMapBuilder)
    let name : string = (thisDeserializer.readString() as string)
    const param_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let param_buf : Object | undefined
    if ((param_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        param_buf = (thisDeserializer.readObject() as object)
    }
    let param : Object | undefined = param_buf
    _call(name, param)
}
export function deserializeAndCallPageTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PageTransitionCallback)
    let type : RouteType = TypeChecker.RouteType_FromNumeric(thisDeserializer.readInt32())
    let progress : number = (thisDeserializer.readNumber() as number)
    _call(type, progress)
}
export function deserializeAndCallPasteEventCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PasteEventCallback)
    const event_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let event_buf : PasteEvent | undefined
    if ((event_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        event_buf = PasteEvent_serializer.read(thisDeserializer)
    }
    let event : PasteEvent | undefined = event_buf
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallRadioModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: RadioConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RadioConfiguration = RadioConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallRatingModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: RatingConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : RatingConfiguration = RatingConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((breakpoints: string) => void) = (breakpoints: string):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeString(breakpoints);
    InteropNativeModule._CallCallbackSync(814634522, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallScrollOnScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnScrollCallback)
    let xOffset : number = (thisDeserializer.readNumber() as number)
    let yOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    _call(xOffset, yOffset, scrollState)
}
export function deserializeAndCallScrollOnWillScrollCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnWillScrollCallback)
    let xOffset : number = (thisDeserializer.readNumber() as number)
    let yOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = TypeChecker.ScrollSource_FromNumeric(thisDeserializer.readInt32())
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: OffsetResult | undefined) => void) = (value?: OffsetResult | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        OffsetResult_serializer.write(_continuation_buf_argsSerializer, value_value);
    }
    InteropNativeModule._CallCallbackSync(1321949695, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(xOffset, yOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallSearchSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SearchSubmitCallback)
    let searchContent : string = (thisDeserializer.readString() as string)
    const event_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let event_buf : SubmitEvent | undefined
    if ((event_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        event_buf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = event_buf
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
    const others_buf_length : int32 = thisDeserializer.readInt32()
    let others_buf : Array<GestureRecognizer> = new Array<GestureRecognizer>(others_buf_length)
    for (let others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf[others_buf_i] = (GestureRecognizer_serializer.read(thisDeserializer) as GestureRecognizer)
    }
    let others : Array<GestureRecognizer> = others_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: GestureRecognizer) => void) = (value: GestureRecognizer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    GestureRecognizer_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(776202910, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(current, others)
    _continuation(_callResult)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallSliderTriggerChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SliderTriggerChangeCallback)
    let value : number = (thisDeserializer.readNumber() as number)
    let mode : SliderChangeMode = TypeChecker.SliderChangeMode_FromNumeric(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallStyledStringMarshallCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringMarshallCallback)
    let marshallableVal : UserDataSpan = (UserDataSpan_serializer.read(thisDeserializer) as UserDataSpan)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: NativeBuffer) => void) = (value: NativeBuffer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writeBuffer(value);
    InteropNativeModule._CallCallbackSync(908731311, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(marshallableVal)
    _continuation(_callResult)
}
export function deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringUnmarshallCallback)
    let buf : NativeBuffer = (thisDeserializer.readBuffer() as NativeBuffer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: UserDataSpan) => void) = (value: UserDataSpan):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    UserDataSpan_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(-1198150682, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(buf)
    _continuation(_callResult)
}
export function deserializeAndCallSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SubmitCallback)
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    let event : SubmitEvent = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TabsCustomContentTransitionCallback)
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: TabContentAnimatedTransition | undefined) => void) = (value?: TabContentAnimatedTransition | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        TabContentAnimatedTransition_serializer.write(_continuation_buf_argsSerializer, value_value);
    }
    InteropNativeModule._CallCallbackSync(-143931627, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallTextAreaSubmitCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextAreaSubmitCallback)
    let enterKeyType : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    const event_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let event_buf : SubmitEvent | undefined
    if ((event_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        event_buf = (SubmitEvent_serializer.read(thisDeserializer) as SubmitEvent)
    }
    let event : SubmitEvent | undefined = event_buf
    _call(enterKeyType, event)
}
export function deserializeAndCallTextClockModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: TextClockConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextClockConfiguration = TextClockConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallTextFieldValueCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextFieldValueCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Resource | undefined
    if (value_buf_selector == (0).toChar()) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == (1).toChar()) {
        value_buf = Resource_serializer.read(thisDeserializer)
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : ResourceStr = (value_buf as string | Resource)
    _call(value)
}
export function deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerEnterSelectedAreaCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == (0).toChar()) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == (1).toChar()) {
        const value_buf_u_length : int32 = thisDeserializer.readInt32()
        let value_buf_u : Array<string> = new Array<string>(value_buf_u_length)
        for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u[value_buf_u_i] = (thisDeserializer.readString() as string)
        }
        value_buf = value_buf_u
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : string | Array<string> = (value_buf as string | Array<string>)
    const index_buf_selector : int32 = thisDeserializer.readInt8()
    let index_buf : number | Array<number> | undefined
    if (index_buf_selector == (0).toChar()) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == (1).toChar()) {
        const index_buf_u_length : int32 = thisDeserializer.readInt32()
        let index_buf_u : Array<number> = new Array<number>(index_buf_u_length)
        for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u[index_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        index_buf = index_buf_u
    }
    else {
        throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
    }
    let index : number | Array<number> = (index_buf as number | Array<number>)
    _call(value, index)
}
export function deserializeAndCallTextPickerScrollStopCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerScrollStopCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == (0).toChar()) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == (1).toChar()) {
        const value_buf_u_length : int32 = thisDeserializer.readInt32()
        let value_buf_u : Array<string> = new Array<string>(value_buf_u_length)
        for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u[value_buf_u_i] = (thisDeserializer.readString() as string)
        }
        value_buf = value_buf_u
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : string | Array<string> = (value_buf as string | Array<string>)
    const index_buf_selector : int32 = thisDeserializer.readInt8()
    let index_buf : number | Array<number> | undefined
    if (index_buf_selector == (0).toChar()) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == (1).toChar()) {
        const index_buf_u_length : int32 = thisDeserializer.readInt32()
        let index_buf_u : Array<number> = new Array<number>(index_buf_u_length)
        for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u[index_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        index_buf = index_buf_u
    }
    else {
        throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
    }
    let index : number | Array<number> = (index_buf as number | Array<number>)
    _call(value, index)
}
export function deserializeAndCallTextTimerModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : TextTimerConfiguration = TextTimerConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
}
export function deserializeAndCallToggleModifierBuilder(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
    let parentNode : KPointer = thisDeserializer.readPointer()
    let config : ToggleConfiguration = ToggleConfiguration_serializer.read(thisDeserializer)
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = (value: KPointer):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    _continuation_buf_argsSerializer.writePointer(value);
    InteropNativeModule._CallCallbackSync(721562324, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(parentNode, config)
    _continuation(_callResult)
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
    const extraParams_buf_runtimeType  = thisDeserializer.readInt8().toInt()
    let extraParams_buf : string | undefined
    if ((extraParams_buf_runtimeType) != (RuntimeType.UNDEFINED))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: CustomBuilder | DragItemInfo) => void) = (value: CustomBuilder | DragItemInfo):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    if (RuntimeType.FUNCTION == value_type) {
        _continuation_buf_argsSerializer.writeInt8((0).toChar());
        const value_0  = value as CustomBuilder;
        _continuation_buf_argsSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_0));
    }
    else if (RuntimeType.OBJECT == value_type) {
        _continuation_buf_argsSerializer.writeInt8((1).toChar());
        const value_1  = value as DragItemInfo;
        DragItemInfo_serializer.write(_continuation_buf_argsSerializer, value_1);
    }
    InteropNativeModule._CallCallbackSync(-620935067, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(event, extraParams)
    _continuation(_callResult)
}
export function deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
    let from : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let to : NavContentInfo = NavContentInfo_serializer.read(thisDeserializer)
    let operation : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(thisDeserializer.readInt32())
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: NavigationAnimatedTransition | undefined) => void) = (value?: NavigationAnimatedTransition | undefined):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    let value_type : int32 = RuntimeType.UNDEFINED;
    value_type = runtimeType(value);
    _continuation_buf_argsSerializer.writeInt8((value_type).toChar());
    if ((value_type) != (RuntimeType.UNDEFINED)) {
        const value_value  = value!;
        NavigationAnimatedTransition_serializer.write(_continuation_buf_argsSerializer, value_value);
    }
    InteropNativeModule._CallCallbackSync(-2035339519, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(from, to, operation)
    _continuation(_callResult)
}
export function deserializeAndCallUpdateTransitionCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as UpdateTransitionCallback)
    let progress : number = (thisDeserializer.readNumber() as number)
    _call(progress)
}
export function deserializeAndCallVisibleAreaChangeCallback(thisDeserializer: DeserializerBase): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as VisibleAreaChangeCallback)
    let isExpanding : boolean = thisDeserializer.readBoolean()
    let currentRatio : number = (thisDeserializer.readNumber() as number)
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
    const _continuation_buf_resource : CallbackResource = thisDeserializer.readCallbackResource()
    const _continuation_buf_call : KPointer = thisDeserializer.readPointer()
    const _continuation_buf_callSync : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: WebKeyboardOptions) => void) = (value: WebKeyboardOptions):void => { 
    const _continuation_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    _continuation_buf_argsSerializer.writeInt32(_continuation_buf_resource.resourceId);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_call);
    _continuation_buf_argsSerializer.writePointer(_continuation_buf_callSync);
    WebKeyboardOptions_serializer.write(_continuation_buf_argsSerializer, value);
    InteropNativeModule._CallCallbackSync(-1376223390, _continuation_buf_argsSerializer.asBuffer(), _continuation_buf_argsSerializer.length());
    _continuation_buf_argsSerializer.release();
    return; }
    const _callResult  = _call(keyboardCallbackInfo)
    _continuation(_callResult)
}
export function deserializeAndCallCallback(thisDeserializer: DeserializerBase): void {
    const kind : int32 = thisDeserializer.readInt32()
    switch ((kind as CallbackKind)) {
        case CallbackKind.Kind_AccessibilityCallback: return deserializeAndCallAccessibilityCallback(thisDeserializer);
        case CallbackKind.Kind_AccessibilityFocusCallback: return deserializeAndCallAccessibilityFocusCallback(thisDeserializer);
        case CallbackKind.Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer);
        case CallbackKind.Kind_ButtonModifierBuilder: return deserializeAndCallButtonModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_ButtonTriggerClickCallback: return deserializeAndCallButtonTriggerClickCallback(thisDeserializer);
        case CallbackKind.Kind_Callback_Area_Area_Void: return deserializeAndCallCallback_Area_Area_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_Number_Void: return deserializeAndCallCallback_Array_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_String_Void: return deserializeAndCallCallback_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer);
        case CallbackKind.Kind_Callback_AxisEvent_Void: return deserializeAndCallCallback_AxisEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean: return deserializeAndCallCallback_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Boolean_Void: return deserializeAndCallCallback_Boolean_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Buffer_Void: return deserializeAndCallCallback_Buffer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ClickEvent_Void: return deserializeAndCallCallback_ClickEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_CompatibleComponentInfo_Void: return deserializeAndCallCallback_CompatibleComponentInfo_Void(thisDeserializer);
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
        case CallbackKind.Kind_Callback_EnterKeyType_Void: return deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ErrorInformation_Void: return deserializeAndCallCallback_ErrorInformation_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Extender_OnFinish: return deserializeAndCallCallback_Extender_OnFinish(thisDeserializer);
        case CallbackKind.Kind_Callback_Extender_OnProgress: return deserializeAndCallCallback_Extender_OnProgress(thisDeserializer);
        case CallbackKind.Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_FullscreenInfo_Void: return deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureEvent_Void: return deserializeAndCallCallback_GestureEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_GestureRecognizer_Void: return deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_HitTestMode_Void: return deserializeAndCallCallback_HitTestMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_HoverEvent_Void: return deserializeAndCallCallback_HoverEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_InsertValue_Boolean: return deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_InsertValue_Void: return deserializeAndCallCallback_InsertValue_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_Number_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_ItemDragInfo_Void: return deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_KeyEvent_Boolean: return deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_KeyEvent_Void: return deserializeAndCallCallback_KeyEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Map_String_Object_Void: return deserializeAndCallCallback_Map_String_Object_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_MarqueeState_Void: return deserializeAndCallCallback_MarqueeState_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_MouseEvent_Void: return deserializeAndCallCallback_MouseEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavDestinationContext_Void: return deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationMode_Void: return deserializeAndCallCallback_NavigationMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_Boolean: return deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_Boolean_Boolean: return deserializeAndCallCallback_Number_Number_Boolean_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_ComputedBarAttribute: return deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_SliderChangeMode_Void: return deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Tuple_Number_Number: return deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer);
        case CallbackKind.Kind_Callback_Number_Tuple_Number_Number_Number_Number: return deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer);
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
        case CallbackKind.Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnInterceptRequestEvent_WebResourceResponse: return deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer);
        case CallbackKind.Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallCallback_onMeasureSize_SizeResult(thisDeserializer);
        case CallbackKind.Kind_Callback_OnOverScrollEvent_Void: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageBeginEvent_Void: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageEndEvent_Void: return deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_OnPageVisibleEvent_Void: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer);
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
        case CallbackKind.Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Array_String_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Boolean_Void: return deserializeAndCallCallback_Opt_Boolean_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallCallback_Opt_CustomBuilder_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_FontDescriptor_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Number_Void: return deserializeAndCallCallback_Opt_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Object_Void: return deserializeAndCallCallback_Opt_Object_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallCallback_Opt_OffsetResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Scene_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Scene_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallCallback_Opt_ScrollResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_String_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_String_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Union_Number_Resource_Void: return deserializeAndCallCallback_Opt_Union_Number_Resource_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Opt_Union_ResourceStr_String_Resource_Void: return deserializeAndCallCallback_Opt_Union_ResourceStr_String_Resource_Void(thisDeserializer);
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
        case CallbackKind.Kind_Callback_RotationGesture: return deserializeAndCallCallback_RotationGesture(thisDeserializer);
        case CallbackKind.Kind_Callback_RotationGesture_Void: return deserializeAndCallCallback_RotationGesture_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SheetDismiss_Void: return deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SheetType_Void: return deserializeAndCallCallback_SheetType_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SizeResult_Void: return deserializeAndCallCallback_SizeResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SpringBackAction_Void: return deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_StateStylesChange: return deserializeAndCallCallback_StateStylesChange(thisDeserializer);
        case CallbackKind.Kind_Callback_String_PasteEvent_Void: return deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_String_Void: return deserializeAndCallCallback_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer);
        case CallbackKind.Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SwipeActionState_Void: return deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SwipeGesture: return deserializeAndCallCallback_SwipeGesture(thisDeserializer);
        case CallbackKind.Kind_Callback_SwipeGesture_Void: return deserializeAndCallCallback_SwipeGesture_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TerminationInfo_Void: return deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TextPickerResult_Void: return deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TextRange_Void: return deserializeAndCallCallback_TextRange_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TimePickerResult_Void: return deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchEvent_Void: return deserializeAndCallCallback_TouchEvent_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_TouchResult_Void: return deserializeAndCallCallback_TouchResult_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Tuple_Number_Number_Number_Number_Void: return deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Tuple_Number_Number_Void: return deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_Number_Array_Number_Void: return deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_ResourceStr_Array_ResourceStr_Void: return deserializeAndCallCallback_Union_ResourceStr_Array_ResourceStr_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Union_ResourceStr_Resource_String_Void: return deserializeAndCallCallback_Union_ResourceStr_Resource_String_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_Void: return deserializeAndCallCallback_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer);
        case CallbackKind.Kind_Callback_WebResourceResponse_Void: return deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer);
        case CallbackKind.Kind_CheckBoxModifierBuilder: return deserializeAndCallCheckBoxModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_CompatibleInitCallback: return deserializeAndCallCompatibleInitCallback(thisDeserializer);
        case CallbackKind.Kind_CompatibleUpdateCallback: return deserializeAndCallCompatibleUpdateCallback(thisDeserializer);
        case CallbackKind.Kind_ContentDidScrollCallback: return deserializeAndCallContentDidScrollCallback(thisDeserializer);
        case CallbackKind.Kind_ContentWillScrollCallback: return deserializeAndCallContentWillScrollCallback(thisDeserializer);
        case CallbackKind.Kind_Context_getGroupDir_Callback: return deserializeAndCallContext_getGroupDir_Callback(thisDeserializer);
        case CallbackKind.Kind_CustomNodeBuilder: return deserializeAndCallCustomNodeBuilder(thisDeserializer);
        case CallbackKind.Kind_DataPanelModifierBuilder: return deserializeAndCallDataPanelModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_EditableTextOnChangeCallback: return deserializeAndCallEditableTextOnChangeCallback(thisDeserializer);
        case CallbackKind.Kind_ErrorCallback: return deserializeAndCallErrorCallback(thisDeserializer);
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
        case CallbackKind.Kind_NavDestinationTransitionDelegate: return deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer);
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
        case CallbackKind.Kind_OnNativeEmbedVisibilityChangeCallback: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnNativeLoadCallback: return deserializeAndCallOnNativeLoadCallback(thisDeserializer);
        case CallbackKind.Kind_OnNavigationEntryCommittedCallback: return deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer);
        case CallbackKind.Kind_OnOverrideUrlLoadingCallback: return deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer);
        case CallbackKind.Kind_OnPasteCallback: return deserializeAndCallOnPasteCallback(thisDeserializer);
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
        case CallbackKind.Kind_OnTabsContentWillChangeCallback: return deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTabsGestureSwipeCallback: return deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTextPickerChangeCallback: return deserializeAndCallOnTextPickerChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTextSelectionChangeCallback: return deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnTimePickerChangeCallback: return deserializeAndCallOnTimePickerChangeCallback(thisDeserializer);
        case CallbackKind.Kind_OnViewportFitChangedCallback: return deserializeAndCallOnViewportFitChangedCallback(thisDeserializer);
        case CallbackKind.Kind_OnWillScrollCallback: return deserializeAndCallOnWillScrollCallback(thisDeserializer);
        case CallbackKind.Kind_PageMapBuilder: return deserializeAndCallPageMapBuilder(thisDeserializer);
        case CallbackKind.Kind_PageTransitionCallback: return deserializeAndCallPageTransitionCallback(thisDeserializer);
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
        case CallbackKind.Kind_ToggleModifierBuilder: return deserializeAndCallToggleModifierBuilder(thisDeserializer);
        case CallbackKind.Kind_TransitionFinishCallback: return deserializeAndCallTransitionFinishCallback(thisDeserializer);
        case CallbackKind.Kind_Type_CommonMethod_onDragStart: return deserializeAndCallType_CommonMethod_onDragStart(thisDeserializer);
        case CallbackKind.Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisDeserializer);
        case CallbackKind.Kind_UpdateTransitionCallback: return deserializeAndCallUpdateTransitionCallback(thisDeserializer);
        case CallbackKind.Kind_VisibleAreaChangeCallback: return deserializeAndCallVisibleAreaChangeCallback(thisDeserializer);
        case CallbackKind.Kind_VoidCallback: return deserializeAndCallVoidCallback(thisDeserializer);
        case CallbackKind.Kind_WebKeyboardCallback: return deserializeAndCallWebKeyboardCallback(thisDeserializer);
    }
    console.log("Unknown callback kind")
}

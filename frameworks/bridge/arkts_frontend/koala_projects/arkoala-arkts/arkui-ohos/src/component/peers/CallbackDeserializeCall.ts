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

import { CallbackKind } from "./CallbackKind"
import { Deserializer } from "./Deserializer"
import { int32, float32, int64 } from "@koalaui/common"
import { ResourceHolder, KInt, KStringPtr, wrapSystemCallback, KPointer, RuntimeType, KSerializerBuffer, NativeBuffer } from "@koalaui/interop"
import { CallbackTransformer } from "./CallbackTransformer"
import { AccessibilityCallback, AccessibilityHoverEvent, AccessibilityFocusCallback, Callback_Area_Area_Void, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, Callback_AxisEvent_Void, AxisEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, Callback_ClickEvent_Void, ClickEvent, Callback_CrownEvent_Void, CrownEvent, CustomBuilder, Callback_DismissContentCoverAction_Void, DismissContentCoverAction, Callback_DismissPopupAction_Void, DismissPopupAction, Callback_DismissSheetAction_Void, DismissSheetAction, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, DragItemInfo, Callback_DragEvent_String_Void, Callback_FocusAxisEvent_Void, FocusAxisEvent, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_HoverEvent_Void, ItemDragInfo, Callback_KeyEvent_Boolean, KeyEvent, Callback_KeyEvent_Void, Callback_Literal_Boolean_isVisible_Void, Literal_Boolean_isVisible, Callback_MouseEvent_Void, MouseEvent, Callback_PreDragStatus_Void, PreDragStatus, Callback_SheetDismiss_Void, SheetDismiss, Callback_SheetType_Void, SheetType, Callback_SpringBackAction_Void, SpringBackAction, Callback_TouchEvent_HitTestMode, TouchEvent, Callback_TouchEvent_Void, GestureRecognizerJudgeBeginCallback, HoverCallback, OnDragEventCallback, OnMoveHandler, OnScrollCallback, PopupStateChangeCallback, PopupStateChangeParam, ReuseIdCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, TransitionFinishCallback, VisibleAreaChangeCallback, ScrollResult, OnWillScrollCallback } from "./../common"
import { AsyncCallback_Array_TextMenuItem_Array_TextMenuItem, TextMenuItem, AsyncCallback_TextMenuItem_TextRange_Boolean, TextRange, DeleteValue, EditableTextChangeValue, InsertValue, Callback_StyledStringChangeValue_Boolean, StyledStringChangeValue, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, OnDidChangeCallback } from "./../textCommon"
import { AsyncCallback_image_PixelMap_Void, ReceiveCallback } from "./../arkui-external"
import { PixelMap } from "./../arkui-pixelmap"
import { ButtonTriggerClickCallback } from "./../button"
import { Callback_Any_Void, Callback_FormCallbackInfo_Void, FormCallbackInfo, Callback_Literal_Number_errcode_String_msg_Void, Literal_Number_errcode_String_msg } from "./../formComponent"
import { Area, ResourceStr, SizeOptions, VoidCallback } from "./../units"
import { Callback_Array_Number_Void } from "./../patternLock"
import { Callback_Array_String_Void, Callback_Array_TextMenuItem_Void, Callback_Buffer_Void, Callback_ComputedBarAttribute_Void, Callback_CustomBuilder_Void, Callback_GestureJudgeResult_Void, Callback_GestureRecognizer_Void, Callback_HitTestMode_Void, Callback_Literal_Number_offsetRemain_Void, Callback_OffsetResult_Void, Callback_OnScrollFrameBeginHandlerResult_Void, Callback_Opt_Array_NavDestinationTransition_Void, Callback_Opt_Array_String_Void, Callback_Opt_NavigationAnimatedTransition_Void, Callback_Opt_StyledString_Opt_Array_String_Void, Callback_Opt_TabContentAnimatedTransition_Void, Callback_Pointer_Void, Callback_StyledStringMarshallingValue_Void, Callback_TouchResult_Void, Callback_Tuple_Number_Number_Number_Number_Void, Callback_Tuple_Number_Number_Void, Callback_Union_CustomBuilder_DragItemInfo_Void, Callback_WebKeyboardOptions_Void, Callback_WebResourceResponse_Void, Callback_WithThemeAttribute_Void } from "./../generatorSynthetic"
import { Callback_Boolean, Callback_NavDestinationActiveReason_Void, NavDestinationActiveReason, Callback_NavDestinationContext_Void, NavDestinationContext, Callback_Object_Void, NavDestinationTransition, NavDestinationTransitionDelegate } from "./../navDestination"
import { Callback_Boolean_Void, Callback_NavigationMode_Void, NavigationMode, Callback_NavigationTitleMode_Void, NavigationTitleMode, Callback_NavigationTransitionProxy_Void, NavigationTransitionProxy, NavigationAnimatedTransition, Callback_PopInfo_Void, PopInfo, Callback_String_Opt_Object_Void, InterceptionModeCallback, InterceptionShowCallback, NavBar, NavigationOperation, Type_NavigationAttribute_customNavContentTransition_delegate, NavContentInfo } from "./../navigation"
import { Callback_CalendarRequestedData_Void, CalendarRequestedData, Callback_CalendarSelectedDate_Void, CalendarSelectedDate } from "./../calendar"
import { ComputedBarAttribute, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Void, Literal_Number_offsetRemain, Callback_Number_Number_ComputedBarAttribute, Callback_Number_Number_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Callback_Number_Tuple_Number_Number, Callback_Number_Tuple_Number_Number_Number_Number, Tuple_Number_Number_Number_Number } from "./../grid"
import { Callback_CopyEvent_Void, CopyEvent, Callback_CutEvent_Void, CutEvent, Callback_RichEditorChangeValue_Boolean, RichEditorChangeValue, Callback_RichEditorDeleteValue_Boolean, RichEditorDeleteValue, Callback_RichEditorInsertValue_Boolean, RichEditorInsertValue, Callback_RichEditorRange_Void, RichEditorRange, Callback_RichEditorSelection_Void, RichEditorSelection, Callback_RichEditorTextSpanResult_Void, RichEditorTextSpanResult, PasteEvent, Callback_TextRange_Void, MenuCallback, MenuOnAppearCallback, PasteEventCallback, SubmitCallback } from "./../richEditor"
import { Callback_Date_Void } from "./../calendarPicker"
import { Callback_DatePickerResult_Void, DatePickerResult } from "./../datePicker"
import { Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_EditableTextChangeValue_Boolean, Callback_InsertValue_Boolean, Callback_InsertValue_Void, SearchSubmitCallback } from "./../search"
import { Callback_DismissDialogAction_Void, DismissDialogAction } from "./../actionSheet"
import { Callback_EnterKeyType_Void, Callback_ResourceStr_Void, Callback_String_PasteEvent_Void, TextAreaSubmitCallback } from "./../textArea"
import { EnterKeyType, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, SubmitEvent, OnTextSelectionChangeCallback } from "./../textInput"
import { Callback_Extender_OnFinish, Callback_Extender_OnProgress } from "./../animationExtender"
import { Callback_FullscreenInfo_Void, FullscreenInfo, Callback_PlaybackInfo_Void, PlaybackInfo, Callback_PreparedInfo_Void, PreparedInfo } from "./../video"
import { Callback_GestureEvent_Void, GestureEvent, GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer } from "./../gesture"
import { HitTestMode, Edge, ScrollSource } from "./../enums"
import { Callback_Literal_Function_handler_Object_error_Void, Literal_Function_handler_Object_error, Callback_Literal_Object_detail_Boolean, Literal_Object_detail, Callback_Literal_String_plainText_Void, Literal_String_plainText, Callback_NativeEmbedDataInfo_Void, NativeEmbedDataInfo, Callback_NativeEmbedTouchInfo_Void, NativeEmbedTouchInfo, Callback_OnAlertEvent_Boolean, OnAlertEvent, Callback_OnAudioStateChangedEvent_Void, OnAudioStateChangedEvent, Callback_OnBeforeUnloadEvent_Boolean, OnBeforeUnloadEvent, Callback_OnClientAuthenticationEvent_Void, OnClientAuthenticationEvent, Callback_OnConfirmEvent_Boolean, OnConfirmEvent, Callback_OnConsoleEvent_Boolean, OnConsoleEvent, Callback_OnContextMenuShowEvent_Boolean, OnContextMenuShowEvent, Callback_OnDataResubmittedEvent_Void, OnDataResubmittedEvent, Callback_OnDownloadStartEvent_Void, OnDownloadStartEvent, Callback_OnErrorReceiveEvent_Void, OnErrorReceiveEvent, Callback_OnFaviconReceivedEvent_Void, OnFaviconReceivedEvent, Callback_OnFirstContentfulPaintEvent_Void, OnFirstContentfulPaintEvent, Callback_OnGeolocationShowEvent_Void, OnGeolocationShowEvent, Callback_OnHttpAuthRequestEvent_Boolean, OnHttpAuthRequestEvent, Callback_OnHttpErrorReceiveEvent_Void, OnHttpErrorReceiveEvent, Callback_OnInterceptRequestEvent_WebResourceResponse, OnInterceptRequestEvent, WebResourceResponse, Callback_OnLoadInterceptEvent_Boolean, OnLoadInterceptEvent, Callback_OnOverScrollEvent_Void, OnOverScrollEvent, Callback_OnPageBeginEvent_Void, OnPageBeginEvent, Callback_OnPageEndEvent_Void, OnPageEndEvent, Callback_OnPageVisibleEvent_Void, OnPageVisibleEvent, Callback_OnPermissionRequestEvent_Void, OnPermissionRequestEvent, Callback_OnProgressChangeEvent_Void, OnProgressChangeEvent, Callback_OnPromptEvent_Boolean, OnPromptEvent, Callback_OnRefreshAccessedHistoryEvent_Void, OnRefreshAccessedHistoryEvent, Callback_OnRenderExitedEvent_Void, OnRenderExitedEvent, Callback_OnResourceLoadEvent_Void, OnResourceLoadEvent, Callback_OnScaleChangeEvent_Void, OnScaleChangeEvent, Callback_OnScreenCaptureRequestEvent_Void, OnScreenCaptureRequestEvent, Callback_OnScrollEvent_Void, OnScrollEvent, Callback_OnSearchResultReceiveEvent_Void, OnSearchResultReceiveEvent, Callback_OnShowFileSelectorEvent_Boolean, OnShowFileSelectorEvent, Callback_OnSslErrorEventReceiveEvent_Void, OnSslErrorEventReceiveEvent, Callback_OnTitleReceiveEvent_Void, OnTitleReceiveEvent, Callback_OnTouchIconUrlReceivedEvent_Void, OnTouchIconUrlReceivedEvent, Callback_OnWindowNewEvent_Void, OnWindowNewEvent, WebKeyboardOptions, OnAdsBlockedCallback, AdsBlockedDetails, OnContextMenuHideCallback, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnFullScreenEnterCallback, FullScreenEnterEvent, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnOverrideUrlLoadingCallback, WebResourceRequest, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnSafeBrowsingCheckResultCallback, ThreatType, OnSslErrorEventCallback, SslErrorEvent, OnViewportFitChangedCallback, ViewportFit, Type_WebAttribute_onFileSelectorShow_callback, Literal_Function_callback__Object_fileSelector, Type_WebAttribute_onUrlLoadIntercept_callback, Literal_Union_String_WebResourceRequest_data, WebKeyboardCallback, WebKeyboardCallbackInfo } from "./../web"
import { Callback_Literal_Number_code__want_Void, Literal_Number_code__want, Callback_Map_String_Object_Void, Callback_UIExtensionProxy_Void, UIExtensionProxy } from "./../uiExtensionComponent"
import { Want } from "./../ohos.app.ability"
import { Callback_MarqueeState_Void, MarqueeState } from "./../text"
import { Callback_Number_Boolean, Callback_Number_Number_Boolean, Callback_Number_Number_Number_Void, ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo } from "./../list"
import { Callback_Number_Number_PanelMode_Void, PanelMode, Callback_Opt_PanelMode_Void } from "./../panel"
import { Callback_Number_SliderChangeMode_Void, SliderChangeMode, SliderTriggerChangeCallback } from "./../slider"
import { Callback_Number_String_Void, Callback_Opt_ResourceStr_Void, Callback_Opt_Union_Number_Resource_Void, OnSelectCallback } from "./../select"
import { Tuple_Number_Number } from "./../arkui-synthetics"
import { Callback_Number_Void, Callback_Opt_Number_Void, OnAlphabetIndexerPopupSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerSelectCallback } from "./../alphabetIndexer"
import { OffsetResult, OnScrollFrameBeginHandlerResult, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollOnScrollCallback, ScrollOnWillScrollCallback } from "./../scroll"
import { Callback_Opt_Boolean_Void, OnCheckboxChangeCallback } from "./../checkbox"
import { Resource } from "global/resource"
import { StyledString, UserDataSpan, StyledStringMarshallCallback, StyledStringUnmarshallCallback } from "./../styledString"
import { TabContentAnimatedTransition, Callback_TabContentTransitionProxy_Void, TabContentTransitionProxy, OnTabsAnimationEndCallback, TabsAnimationEvent, OnTabsAnimationStartCallback, OnTabsContentWillChangeCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback } from "./../tabs"
import { Callback_RangeUpdate, Callback_StateStylesChange, Context_getGroupDir_Callback, RestrictedWorker_onerror_Callback, ErrorEvent, RestrictedWorker_onexit_Callback, RestrictedWorker_onmessage_Callback, MessageEvents, Callback_CreateItem } from "./../arkui-custom"
import { Callback_RefreshStatus_Void, RefreshStatus } from "./../refresh"
import { Callback_String_Number_Void, Callback_TextPickerResult_Void, TextPickerResult, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void, OnTextPickerChangeCallback, TextPickerEnterSelectedAreaCallback, TextPickerScrollStopCallback, Type_TextPickerAttribute_onChange_callback } from "./../textPicker"
import { Callback_String_Void } from "./../gridRow"
import { Callback_SwipeActionState_Void, SwipeActionState } from "./../listItem"
import { Callback_SwiperContentTransitionProxy_Void, SwiperContentTransitionProxy, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult, OnSwiperAnimationEndCallback, SwiperAnimationEvent, OnSwiperAnimationStartCallback, OnSwiperGestureSwipeCallback } from "./../swiper"
import { Callback_TerminationInfo_Void, TerminationInfo } from "./../embeddedComponent"
import { Callback_TimePickerResult_Void, TimePickerResult, OnTimePickerChangeCallback } from "./../timePicker"
import { Callback_Type_ImageAttribute_onComplete_callback_event_Void, Type_ImageAttribute_onComplete_callback_event, ImageErrorCallback, ImageError } from "./../image"
import { WithThemeAttribute, WithThemeInterface, WithThemeOptions } from "./../withTheme"
import { Callback_WrappedBuilder_Args_Void, CommonConfiguration } from "./../arkui-wrapper-builder"
import { CustomNodeBuilder } from "./../customBuilder"
import { ErrorCallback } from "./../ohos.base"
import { BusinessError } from "#external"
import { GetItemMainSizeByIndex } from "./../waterFlow"
import { GridAttribute_onItemDragStart_event_type, ListAttribute_onItemDragStart_event_type, TextTimerAttribute_onTimer_event_type } from "./../type-replacements"
import { ImageCompleteCallback, ImageLoadResult } from "./../imageSpan"
import { LocationButtonCallback, LocationButtonOnClickResult } from "./../locationButton"
import { NavExtender_OnUpdateStack } from "./../navigationExtender"
import { OnCheckboxGroupChangeCallback, CheckboxGroupResult } from "./../checkboxgroup"
import { OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam } from "./../folderStack"
import { OnHoverCallback } from "./../sdk-stubs"
import { OnLinearIndicatorChangeCallback } from "./../linearindicator"
import { SurfaceRect, Callback_String_SurfaceRect_Void, OnNativeLoadCallback } from "./../xcomponent"
import { OnRadioChangeCallback } from "./../radio"
import { OnRatingChangeCallback } from "./../rating"
import { PageTransitionCallback, RouteType } from "./../pageTransition"
import { PasteButtonCallback, PasteButtonOnClickResult } from "./../pasteButton"
import { PluginErrorCallback, PluginErrorData } from "./../pluginComponent"
import { SaveButtonCallback, SaveButtonOnClickResult } from "./../saveButton"
import { SearchValueCallback } from "./../searchops"
import { TextFieldValueCallback } from "./../textfieldops"
import { SelectedCallback } from "./../griditemops"
import { StepperIndexCallback } from "./../stepperops"
import { TypeChecker } from "#components"
import { NodeContainer_AboutToResizeCallback } from "./../nodeContainer"
import { Size, DrawContext } from "../../Graphics"
import { DrawCallback } from "./../../RenderNode"
export function deserializeAndCallAccessibilityCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : AccessibilityHoverEvent = (thisDeserializer.readAccessibilityHoverEvent() as AccessibilityHoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallAccessibilityFocusCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as AccessibilityFocusCallback)
    let isFocus : boolean = thisDeserializer.readBoolean()
    _call(isFocus)
}
export function deserializeAndCallAsyncCallback_Array_TextMenuItem_Array_TextMenuItem(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((menuItems: Array<TextMenuItem>) => Array<TextMenuItem>))
    const menuItems_buf_length : int32 = thisDeserializer.readInt32()
    let menuItems_buf : Array<TextMenuItem> = new Array<TextMenuItem>(menuItems_buf_length)
    for (let menuItems_buf_i = 0; menuItems_buf_i < menuItems_buf_length; menuItems_buf_i++) {
        menuItems_buf[menuItems_buf_i] = thisDeserializer.readTextMenuItem()
    }
    let menuItems : Array<TextMenuItem> = menuItems_buf
    let _continuation : ((value: Array<TextMenuItem>) => void) = thisDeserializer.readCallback_Array_TextMenuItem_Void(true)
    const _callResult  = _call(menuItems)
    _continuation(_callResult)
}
export function deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((result: PixelMap) => void))
    let result : PixelMap = (thisDeserializer.readPixelMap() as PixelMap)
    _call(result)
}
export function deserializeAndCallAsyncCallback_TextMenuItem_TextRange_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((menuItem: TextMenuItem,range: TextRange) => boolean))
    let menuItem : TextMenuItem = thisDeserializer.readTextMenuItem()
    let range : TextRange = thisDeserializer.readTextRange()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(menuItem, range)
    _continuation(_callResult)
}
export function deserializeAndCallButtonTriggerClickCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ButtonTriggerClickCallback)
    let xPos : number = (thisDeserializer.readNumber() as number)
    let yPos : number = (thisDeserializer.readNumber() as number)
    _call(xPos, yPos)
}
export function deserializeAndCallCallback_Any_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((info: object) => void))
    let info : object = (thisDeserializer.readObject() as object)
    _call(info)
}
export function deserializeAndCallCallback_Area_Area_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((oldValue: Area,newValue: Area) => void))
    let oldValue : Area = thisDeserializer.readArea()
    let newValue : Area = thisDeserializer.readArea()
    _call(oldValue, newValue)
}
export function deserializeAndCallCallback_Array_Number_Void(thisDeserializer: Deserializer): void {
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
export function deserializeAndCallCallback_Array_String_Void(thisDeserializer: Deserializer): void {
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
export function deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TextMenuItem>) => void))
    const value_buf_length : int32 = thisDeserializer.readInt32()
    let value_buf : Array<TextMenuItem> = new Array<TextMenuItem>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = thisDeserializer.readTextMenuItem()
    }
    let value : Array<TextMenuItem> = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TouchTestInfo>) => TouchResult))
    const value_buf_length : int32 = thisDeserializer.readInt32()
    let value_buf : Array<TouchTestInfo> = new Array<TouchTestInfo>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = thisDeserializer.readTouchTestInfo()
    }
    let value : Array<TouchTestInfo> = value_buf
    let _continuation : ((value: TouchResult) => void) = thisDeserializer.readCallback_TouchResult_Void(true)
    const _callResult  = _call(value)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_AxisEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: AxisEvent) => void))
    let parameter : AxisEvent = (thisDeserializer.readAxisEvent() as AxisEvent)
    _call(parameter)
}
export function deserializeAndCallCallback_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => boolean))
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((isHover: boolean,event: HoverEvent) => void))
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (thisDeserializer.readHoverEvent() as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallCallback_Boolean_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((isVisible: boolean) => void))
    let isVisible : boolean = thisDeserializer.readBoolean()
    _call(isVisible)
}
export function deserializeAndCallCallback_Buffer_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: NativeBuffer) => void))
    let value : NativeBuffer = (thisDeserializer.readBuffer() as NativeBuffer)
    _call(value)
}
export function deserializeAndCallCallback_CalendarRequestedData_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: CalendarRequestedData) => void))
    let event : CalendarRequestedData = thisDeserializer.readCalendarRequestedData()
    _call(event)
}
export function deserializeAndCallCallback_CalendarSelectedDate_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: CalendarSelectedDate) => void))
    let event : CalendarSelectedDate = thisDeserializer.readCalendarSelectedDate()
    _call(event)
}
export function deserializeAndCallCallback_ClickEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent) => void))
    let event : ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    _call(event)
}
export function deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ComputedBarAttribute) => void))
    let value : ComputedBarAttribute = thisDeserializer.readComputedBarAttribute()
    _call(value)
}
export function deserializeAndCallCallback_CopyEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: CopyEvent) => void))
    let parameter : CopyEvent = thisDeserializer.readCopyEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_CreateItem(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as Callback_CreateItem)
    let index: int32 = thisDeserializer.readInt32()
    let _continuation: ((value: KPointer) => void) = thisDeserializer.readCallback_Pointer_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_CrownEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: CrownEvent) => void))
    let parameter : CrownEvent = thisDeserializer.readCrownEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_CustomBuilder_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder) => void))
    let value : CustomBuilder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    _call(value)
}
export function deserializeAndCallCallback_CutEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: CutEvent) => void))
    let parameter : CutEvent = thisDeserializer.readCutEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_Date_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: Date) => void))
    let parameter : Date = new Date(thisDeserializer.readInt64())
    _call(parameter)
}
export function deserializeAndCallCallback_DatePickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: DatePickerResult) => void))
    let value : DatePickerResult = thisDeserializer.readDatePickerResult()
    _call(value)
}
export function deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DeleteValue) => boolean))
    let parameter : DeleteValue = thisDeserializer.readDeleteValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_DeleteValue_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DeleteValue) => void))
    let parameter : DeleteValue = thisDeserializer.readDeleteValue()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissContentCoverAction) => void))
    let parameter : DismissContentCoverAction = thisDeserializer.readDismissContentCoverAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissDialogAction) => void))
    let parameter : DismissDialogAction = thisDeserializer.readDismissDialogAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissPopupAction) => void))
    let parameter : DismissPopupAction = thisDeserializer.readDismissPopupAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissSheetAction) => void))
    let parameter : DismissSheetAction = thisDeserializer.readDismissSheetAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo))
    let event : DragEvent = (thisDeserializer.readDragEvent() as DragEvent)
    const extraParams_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let extraParams_buf : string | undefined
    if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
    let _continuation : ((value: CustomBuilder | DragItemInfo) => void) = thisDeserializer.readCallback_Union_CustomBuilder_DragItemInfo_Void(true)
    const _callResult  = _call(event, extraParams)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_DragEvent_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent,extraParams?: string) => void))
    let event : DragEvent = (thisDeserializer.readDragEvent() as DragEvent)
    const extraParams_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let extraParams_buf : string | undefined
    if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
    _call(event, extraParams)
}
export function deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: EditableTextChangeValue) => boolean))
    let parameter : EditableTextChangeValue = thisDeserializer.readEditableTextChangeValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((enterKey: EnterKeyType) => void))
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    _call(enterKey)
}
export function deserializeAndCallCallback_Extender_OnFinish(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnFinish)
    _call()
}
export function deserializeAndCallCallback_Extender_OnProgress(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnProgress)
    let value : float32 = thisDeserializer.readFloat32()
    _call(value)
}
export function deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: FocusAxisEvent) => void))
    let parameter : FocusAxisEvent = (thisDeserializer.readFocusAxisEvent() as FocusAxisEvent)
    _call(parameter)
}
export function deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: FormCallbackInfo) => void))
    let parameter : FormCallbackInfo = thisDeserializer.readFormCallbackInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: FullscreenInfo) => void))
    let parameter : FullscreenInfo = thisDeserializer.readFullscreenInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_GestureEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: GestureEvent) => void))
    let event : GestureEvent = (thisDeserializer.readGestureEvent() as GestureEvent)
    _call(event)
}
export function deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult))
    let gestureInfo : GestureInfo = thisDeserializer.readGestureInfo()
    let event : BaseGestureEvent = (thisDeserializer.readBaseGestureEvent() as BaseGestureEvent)
    let _continuation : ((value: GestureJudgeResult) => void) = thisDeserializer.readCallback_GestureJudgeResult_Void(true)
    const _callResult  = _call(gestureInfo, event)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: GestureJudgeResult) => void))
    let value : GestureJudgeResult = TypeChecker.GestureJudgeResult_FromNumeric(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: GestureRecognizer) => void))
    let value : GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    _call(value)
}
export function deserializeAndCallCallback_HitTestMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: HitTestMode) => void))
    let value : HitTestMode = TypeChecker.HitTestMode_FromNumeric(thisDeserializer.readInt32())
    _call(value)
}
export function deserializeAndCallCallback_HoverEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: HoverEvent) => void))
    let parameter : HoverEvent = (thisDeserializer.readHoverEvent() as HoverEvent)
    _call(parameter)
}
export function deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: InsertValue) => boolean))
    let parameter : InsertValue = thisDeserializer.readInsertValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_InsertValue_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: InsertValue) => void))
    let parameter : InsertValue = thisDeserializer.readInsertValue()
    _call(parameter)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let insertIndex : number = (thisDeserializer.readNumber() as number)
    let isSuccess : boolean = thisDeserializer.readBoolean()
    _call(event, itemIndex, insertIndex, isSuccess)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let insertIndex : number = (thisDeserializer.readNumber() as number)
    _call(event, itemIndex, insertIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number) => void))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    _call(event, itemIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo) => void))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    _call(event)
}
export function deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: KeyEvent) => boolean))
    let parameter : KeyEvent = (thisDeserializer.readKeyEvent() as KeyEvent)
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_KeyEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: KeyEvent) => void))
    let event : KeyEvent = (thisDeserializer.readKeyEvent() as KeyEvent)
    _call(event)
}
export function deserializeAndCallCallback_Literal_Boolean_isVisible_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: Literal_Boolean_isVisible) => void))
    const event_buf_isVisible : boolean = thisDeserializer.readBoolean()
    let event : Literal_Boolean_isVisible = ({isVisible: event_buf_isVisible} as Literal_Boolean_isVisible)
    _call(event)
}
export function deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event?: Literal_Function_handler_Object_error) => void))
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Literal_Function_handler_Object_error | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        throw new Error("Not implemented yet")
    }
    let event : Literal_Function_handler_Object_error | undefined = event_buf
    _call(event)
}
export function deserializeAndCallCallback_Literal_Number_code__want_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: Literal_Number_code__want) => void))
    const parameter_buf_code : number = (thisDeserializer.readNumber() as number)
    const parameter_buf_want_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let parameter_buf_want_buf : Want | undefined
    if ((RuntimeType.UNDEFINED) != (parameter_buf_want_buf_runtimeType))
    {
        parameter_buf_want_buf = thisDeserializer.readWant()
    }
    const parameter_buf_want : undefined | Want = parameter_buf_want_buf
    let parameter : Literal_Number_code__want = ({code: parameter_buf_code, want: parameter_buf_want} as Literal_Number_code__want)
    _call(parameter)
}
export function deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((info: Literal_Number_errcode_String_msg) => void))
    const info_buf_errcode : number = (thisDeserializer.readNumber() as number)
    const info_buf_msg : string = (thisDeserializer.readString() as string)
    let info : Literal_Number_errcode_String_msg = ({errcode: info_buf_errcode, msg: info_buf_msg} as Literal_Number_errcode_String_msg)
    _call(info)
}
export function deserializeAndCallCallback_Literal_Number_offsetRemain_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Literal_Number_offsetRemain) => void))
    const value_buf_offsetRemain : number = (thisDeserializer.readNumber() as number)
    let value : Literal_Number_offsetRemain = ({offsetRemain: value_buf_offsetRemain} as Literal_Number_offsetRemain)
    _call(value)
}
export function deserializeAndCallCallback_Literal_Object_detail_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event?: Literal_Object_detail) => boolean))
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Literal_Object_detail | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__detail : Object = (thisDeserializer.readObject() as Object)
        event_buf = ({detail: event_buf__detail} as Literal_Object_detail)
    }
    let event : Literal_Object_detail | undefined = event_buf
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(event)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Literal_String_plainText_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selectedText: Literal_String_plainText) => void))
    const selectedText_buf_plainText : string = (thisDeserializer.readString() as string)
    let selectedText : Literal_String_plainText = ({plainText: selectedText_buf_plainText} as Literal_String_plainText)
    _call(selectedText)
}
export function deserializeAndCallCallback_Map_String_Object_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: Map<string, Object>) => void))
    const parameter_buf_size : int32 = thisDeserializer.readInt32()
    let parameter_buf : Map<string, Object> = new Map<string, Object>()
    // TODO: TS map resize
    for (let parameter_buf_i = 0; parameter_buf_i < parameter_buf_size; parameter_buf_i++) {
        const parameter_buf_key : string = (thisDeserializer.readString() as string)
        const parameter_buf_value : Object = (thisDeserializer.readObject() as Object)
        parameter_buf.set(parameter_buf_key, parameter_buf_value)
    }
    let parameter : Map<string, Object> = parameter_buf
    _call(parameter)
}
export function deserializeAndCallCallback_MarqueeState_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: MarqueeState) => void))
    let parameter : MarqueeState = TypeChecker.MarqueeState_FromNumeric(thisDeserializer.readInt32())
    _call(parameter)
}
export function deserializeAndCallCallback_MouseEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: MouseEvent) => void))
    let event : MouseEvent = (thisDeserializer.readMouseEvent() as MouseEvent)
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedDataInfo) => void))
    let event : NativeEmbedDataInfo = thisDeserializer.readNativeEmbedDataInfo()
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedTouchInfo) => void))
    let event : NativeEmbedTouchInfo = thisDeserializer.readNativeEmbedTouchInfo()
    _call(event)
}
export function deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: NavDestinationActiveReason) => void))
    let parameter : NavDestinationActiveReason = TypeChecker.NavDestinationActiveReason_FromNumeric(thisDeserializer.readInt32())
    _call(parameter)
}
export function deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: NavDestinationContext) => void))
    let parameter : NavDestinationContext = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    _call(parameter)
}
export function deserializeAndCallCallback_NavigationMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((mode: NavigationMode) => void))
    let mode : NavigationMode = TypeChecker.NavigationMode_FromNumeric(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((titleMode: NavigationTitleMode) => void))
    let titleMode : NavigationTitleMode = TypeChecker.NavigationTitleMode_FromNumeric(thisDeserializer.readInt32())
    _call(titleMode)
}
export function deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((transitionProxy: NavigationTransitionProxy) => void))
    let transitionProxy : NavigationTransitionProxy = (thisDeserializer.readNavigationTransitionProxy() as NavigationTransitionProxy)
    _call(transitionProxy)
}
export function deserializeAndCallCallback_Number_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => boolean))
    let index : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: number,to: number) => boolean))
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number,offset: number) => ComputedBarAttribute))
    let index : number = (thisDeserializer.readNumber() as number)
    let offset : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: ComputedBarAttribute) => void) = thisDeserializer.readCallback_ComputedBarAttribute_Void(true)
    const _callResult  = _call(index, offset)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((start: number,end: number,center: number) => void))
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    let center : number = (thisDeserializer.readNumber() as number)
    _call(start, end, center)
}
export function deserializeAndCallCallback_Number_Number_PanelMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((width: number,height: number,mode: PanelMode) => void))
    let width : number = (thisDeserializer.readNumber() as number)
    let height : number = (thisDeserializer.readNumber() as number)
    let mode : PanelMode = TypeChecker.PanelMode_FromNumeric(thisDeserializer.readInt32())
    _call(width, height, mode)
}
export function deserializeAndCallCallback_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((first: number,last: number) => void))
    let first : number = (thisDeserializer.readNumber() as number)
    let last : number = (thisDeserializer.readNumber() as number)
    _call(first, last)
}
export function deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((offset: number,state: ScrollState) => Literal_Number_offsetRemain))
    let offset : number = (thisDeserializer.readNumber() as number)
    let state : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    let _continuation : ((value: Literal_Number_offsetRemain) => void) = thisDeserializer.readCallback_Literal_Number_offsetRemain_Void(true)
    const _callResult  = _call(offset, state)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: number,mode: SliderChangeMode) => void))
    let value : number = (thisDeserializer.readNumber() as number)
    let mode : SliderChangeMode = TypeChecker.SliderChangeMode_FromNumeric(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallCallback_Number_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number,value: string) => void))
    let index : number = (thisDeserializer.readNumber() as number)
    let value : string = (thisDeserializer.readString() as string)
    _call(index, value)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number ]))
    let index : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: [ number, number ]) => void) = thisDeserializer.readCallback_Tuple_Number_Number_Void(true)
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number, number, number ]))
    let index : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: [ number, number, number, number ]) => void) = thisDeserializer.readCallback_Tuple_Number_Number_Number_Number_Void(true)
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((index: number) => void))
    let index : number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallCallback_Object_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: Object) => void))
    let parameter : Object = (thisDeserializer.readObject() as Object)
    _call(parameter)
}
export function deserializeAndCallCallback_OffsetResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: OffsetResult) => void))
    let value : OffsetResult = thisDeserializer.readOffsetResult()
    _call(value)
}
export function deserializeAndCallCallback_ScrollResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ScrollResult) => void))
    let value : ScrollResult = thisDeserializer.readScrollResult()
    _call(value)
}
export function deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnAlertEvent) => boolean))
    let parameter : OnAlertEvent = thisDeserializer.readOnAlertEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnAudioStateChangedEvent) => void))
    let parameter : OnAudioStateChangedEvent = thisDeserializer.readOnAudioStateChangedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnBeforeUnloadEvent) => boolean))
    let parameter : OnBeforeUnloadEvent = thisDeserializer.readOnBeforeUnloadEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnClientAuthenticationEvent) => void))
    let parameter : OnClientAuthenticationEvent = thisDeserializer.readOnClientAuthenticationEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnConfirmEvent) => boolean))
    let parameter : OnConfirmEvent = thisDeserializer.readOnConfirmEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnConsoleEvent) => boolean))
    let parameter : OnConsoleEvent = thisDeserializer.readOnConsoleEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnContextMenuShowEvent) => boolean))
    let parameter : OnContextMenuShowEvent = thisDeserializer.readOnContextMenuShowEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnDataResubmittedEvent) => void))
    let parameter : OnDataResubmittedEvent = thisDeserializer.readOnDataResubmittedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnDownloadStartEvent) => void))
    let parameter : OnDownloadStartEvent = thisDeserializer.readOnDownloadStartEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnErrorReceiveEvent) => void))
    let parameter : OnErrorReceiveEvent = thisDeserializer.readOnErrorReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnFaviconReceivedEvent) => void))
    let parameter : OnFaviconReceivedEvent = thisDeserializer.readOnFaviconReceivedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnFirstContentfulPaintEvent) => void))
    let parameter : OnFirstContentfulPaintEvent = thisDeserializer.readOnFirstContentfulPaintEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnGeolocationShowEvent) => void))
    let parameter : OnGeolocationShowEvent = thisDeserializer.readOnGeolocationShowEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnHttpAuthRequestEvent) => boolean))
    let parameter : OnHttpAuthRequestEvent = thisDeserializer.readOnHttpAuthRequestEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnHttpErrorReceiveEvent) => void))
    let parameter : OnHttpErrorReceiveEvent = thisDeserializer.readOnHttpErrorReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnInterceptRequestEvent) => WebResourceResponse))
    let parameter : OnInterceptRequestEvent = thisDeserializer.readOnInterceptRequestEvent()
    let _continuation : ((value: WebResourceResponse) => void) = thisDeserializer.readCallback_WebResourceResponse_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnLoadInterceptEvent) => boolean))
    let parameter : OnLoadInterceptEvent = thisDeserializer.readOnLoadInterceptEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnOverScrollEvent) => void))
    let parameter : OnOverScrollEvent = thisDeserializer.readOnOverScrollEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageBeginEvent) => void))
    let parameter : OnPageBeginEvent = thisDeserializer.readOnPageBeginEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageEndEvent) => void))
    let parameter : OnPageEndEvent = thisDeserializer.readOnPageEndEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageVisibleEvent) => void))
    let parameter : OnPageVisibleEvent = thisDeserializer.readOnPageVisibleEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPermissionRequestEvent) => void))
    let parameter : OnPermissionRequestEvent = thisDeserializer.readOnPermissionRequestEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnProgressChangeEvent) => void))
    let parameter : OnProgressChangeEvent = thisDeserializer.readOnProgressChangeEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPromptEvent) => boolean))
    let parameter : OnPromptEvent = thisDeserializer.readOnPromptEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnRefreshAccessedHistoryEvent) => void))
    let parameter : OnRefreshAccessedHistoryEvent = thisDeserializer.readOnRefreshAccessedHistoryEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnRenderExitedEvent) => void))
    let parameter : OnRenderExitedEvent = thisDeserializer.readOnRenderExitedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnResourceLoadEvent) => void))
    let parameter : OnResourceLoadEvent = thisDeserializer.readOnResourceLoadEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScaleChangeEvent) => void))
    let parameter : OnScaleChangeEvent = thisDeserializer.readOnScaleChangeEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScreenCaptureRequestEvent) => void))
    let parameter : OnScreenCaptureRequestEvent = thisDeserializer.readOnScreenCaptureRequestEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScrollEvent) => void))
    let parameter : OnScrollEvent = thisDeserializer.readOnScrollEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: OnScrollFrameBeginHandlerResult) => void))
    let value : OnScrollFrameBeginHandlerResult = thisDeserializer.readOnScrollFrameBeginHandlerResult()
    _call(value)
}
export function deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnSearchResultReceiveEvent) => void))
    let parameter : OnSearchResultReceiveEvent = thisDeserializer.readOnSearchResultReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnShowFileSelectorEvent) => boolean))
    let parameter : OnShowFileSelectorEvent = thisDeserializer.readOnShowFileSelectorEvent()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnSslErrorEventReceiveEvent) => void))
    let parameter : OnSslErrorEventReceiveEvent = thisDeserializer.readOnSslErrorEventReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnTitleReceiveEvent) => void))
    let parameter : OnTitleReceiveEvent = thisDeserializer.readOnTitleReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnTouchIconUrlReceivedEvent) => void))
    let parameter : OnTouchIconUrlReceivedEvent = thisDeserializer.readOnTouchIconUrlReceivedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnWindowNewEvent) => void))
    let parameter : OnWindowNewEvent = thisDeserializer.readOnWindowNewEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: Array<NavDestinationTransition> | undefined) => void))
    const value_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let value_buf : Array<NavDestinationTransition> | undefined
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        const value_buf__length : int32 = thisDeserializer.readInt32()
        let value_buf_ : Array<NavDestinationTransition> = new Array<NavDestinationTransition>(value_buf__length)
        for (let value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_[value_buf__i] = thisDeserializer.readNavDestinationTransition()
        }
        value_buf = value_buf_
    }
    let value : Array<NavDestinationTransition> | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((error?: Array<string> | undefined) => void))
    const error_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let error_buf : Array<string> | undefined
    if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
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
export function deserializeAndCallCallback_Opt_Boolean_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((select: boolean | undefined) => void))
    const select_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let select_buf : boolean | undefined
    if ((RuntimeType.UNDEFINED) != (select_buf_runtimeType))
    {
        select_buf = thisDeserializer.readBoolean()
    }
    let select : boolean | undefined = select_buf
    _call(select)
}
export function deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: NavigationAnimatedTransition | undefined) => void))
    const value_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let value_buf : NavigationAnimatedTransition | undefined
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = thisDeserializer.readNavigationAnimatedTransition()
    }
    let value : NavigationAnimatedTransition | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | undefined) => void))
    const selected_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let selected_buf : number | undefined
    if ((RuntimeType.UNDEFINED) != (selected_buf_runtimeType))
    {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    let selected : number | undefined = selected_buf
    _call(selected)
}
export function deserializeAndCallCallback_Opt_PanelMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((mode: PanelMode | undefined) => void))
    const mode_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let mode_buf : PanelMode | undefined
    if ((RuntimeType.UNDEFINED) != (mode_buf_runtimeType))
    {
        mode_buf = TypeChecker.PanelMode_FromNumeric(thisDeserializer.readInt32())
    }
    let mode : PanelMode | undefined = mode_buf
    _call(mode)
}
export function deserializeAndCallCallback_Opt_ResourceStr_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: ResourceStr | undefined) => void))
    const value_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let value_buf : ResourceStr | undefined
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        const value_buf__selector : int32 = thisDeserializer.readInt8()
        let value_buf_ : string | Resource | undefined
        if (value_buf__selector == 0) {
            value_buf_ = (thisDeserializer.readString() as string)
        }
        else if (value_buf__selector == 1) {
            value_buf_ = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for value_buf_ has to be chosen through deserialisation.")
        }
        value_buf = (value_buf_ as string | Resource)
    }
    let value : ResourceStr | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value?: StyledString | undefined,error?: Array<string> | undefined) => void))
    const value_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let value_buf : StyledString | undefined
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = (thisDeserializer.readStyledString() as StyledString)
    }
    let value : StyledString | undefined = value_buf
    const error_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let error_buf : Array<string> | undefined
    if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
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
export function deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TabContentAnimatedTransition | undefined) => void))
    const value_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let value_buf : TabContentAnimatedTransition | undefined
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = thisDeserializer.readTabContentAnimatedTransition()
    }
    let value : TabContentAnimatedTransition | undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_Union_Number_Resource_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Resource | undefined) => void))
    const selected_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let selected_buf : number | Resource | undefined
    if ((RuntimeType.UNDEFINED) != (selected_buf_runtimeType))
    {
        const selected_buf__selector : int32 = thisDeserializer.readInt8()
        let selected_buf_ : number | Resource | undefined
        if (selected_buf__selector == 0) {
            selected_buf_ = (thisDeserializer.readNumber() as number)
        }
        else if (selected_buf__selector == 1) {
            selected_buf_ = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selected_buf_ has to be chosen through deserialisation.")
        }
        selected_buf = (selected_buf_ as number | Resource)
    }
    let selected : number | Resource | undefined = selected_buf
    _call(selected)
}
export function deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: PlaybackInfo) => void))
    let parameter : PlaybackInfo = thisDeserializer.readPlaybackInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_Pointer_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: KPointer) => void))
    let value : KPointer = thisDeserializer.readPointer()
    _call(value)
}
export function deserializeAndCallCallback_PopInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: PopInfo) => void))
    let parameter : PopInfo = thisDeserializer.readPopInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: PreDragStatus) => void))
    let parameter : PreDragStatus = TypeChecker.PreDragStatus_FromNumeric(thisDeserializer.readInt32())
    _call(parameter)
}
export function deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: PreparedInfo) => void))
    let parameter : PreparedInfo = thisDeserializer.readPreparedInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_RangeUpdate(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as Callback_RangeUpdate)
    let start: int32 = thisDeserializer.readInt32()
    let end: int32 = thisDeserializer.readInt32()
    _call(start, end)
}
export function deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: RefreshStatus) => void))
    let state : RefreshStatus = TypeChecker.RefreshStatus_FromNumeric(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_ResourceStr_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((text: ResourceStr) => void))
    const text_buf_selector : int32 = thisDeserializer.readInt8()
    let text_buf : string | Resource | undefined
    if (text_buf_selector == 0) {
        text_buf = (thisDeserializer.readString() as string)
    }
    else if (text_buf_selector == 1) {
        text_buf = thisDeserializer.readResource()
    }
    else {
        throw new Error("One of the branches for text_buf has to be chosen through deserialisation.")
    }
    let text : ResourceStr = (text_buf as string | Resource)
    _call(text)
}
export function deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorChangeValue) => boolean))
    let parameter : RichEditorChangeValue = thisDeserializer.readRichEditorChangeValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorDeleteValue) => boolean))
    let parameter : RichEditorDeleteValue = thisDeserializer.readRichEditorDeleteValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorInsertValue) => boolean))
    let parameter : RichEditorInsertValue = thisDeserializer.readRichEditorInsertValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorRange) => void))
    let parameter : RichEditorRange = thisDeserializer.readRichEditorRange()
    _call(parameter)
}
export function deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorSelection) => void))
    let parameter : RichEditorSelection = thisDeserializer.readRichEditorSelection()
    _call(parameter)
}
export function deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorTextSpanResult) => void))
    let parameter : RichEditorTextSpanResult = thisDeserializer.readRichEditorTextSpanResult()
    _call(parameter)
}
export function deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((sheetDismiss: SheetDismiss) => void))
    let sheetDismiss : SheetDismiss = thisDeserializer.readSheetDismiss()
    _call(sheetDismiss)
}
export function deserializeAndCallCallback_SheetType_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: SheetType) => void))
    let parameter : SheetType = TypeChecker.SheetType_FromNumeric(thisDeserializer.readInt32())
    _call(parameter)
}
export function deserializeAndCallCallback_StateStylesChange(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Callback_StateStylesChange)
    let currentState : int32 = thisDeserializer.readInt32()
    _call(currentState)
}
export function deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: SpringBackAction) => void))
    let parameter : SpringBackAction = thisDeserializer.readSpringBackAction()
    _call(parameter)
}
export function deserializeAndCallCallback_String_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: string,index: number) => void))
    let value : string = (thisDeserializer.readString() as string)
    let index : number = (thisDeserializer.readNumber() as number)
    _call(value, index)
}
export function deserializeAndCallCallback_String_Opt_Object_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((name: string,param: Object | undefined) => void))
    let name : string = (thisDeserializer.readString() as string)
    const param_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let param_buf : Object | undefined
    if ((RuntimeType.UNDEFINED) != (param_buf_runtimeType))
    {
        param_buf = (thisDeserializer.readObject() as Object)
    }
    let param : Object | undefined = param_buf
    _call(name, param)
}
export function deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: string,event: PasteEvent) => void))
    let value : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = thisDeserializer.readPasteEvent()
    _call(value, event)
}
export function deserializeAndCallCallback_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((breakpoints: string) => void))
    let breakpoints : string = (thisDeserializer.readString() as string)
    _call(breakpoints)
}
export function deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: StyledStringChangeValue) => boolean))
    let parameter : StyledStringChangeValue = thisDeserializer.readStyledStringChangeValue()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: UserDataSpan) => void))
    let value : UserDataSpan = thisDeserializer.readUserDataSpan()
    _call(value)
}
export function deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((state: SwipeActionState) => void))
    let state : SwipeActionState = TypeChecker.SwipeActionState_FromNumeric(thisDeserializer.readInt32())
    _call(state)
}
export function deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: SwiperContentTransitionProxy) => void))
    let parameter : SwiperContentTransitionProxy = (thisDeserializer.readSwiperContentTransitionProxy() as SwiperContentTransitionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: TabContentTransitionProxy) => void))
    let parameter : TabContentTransitionProxy = (thisDeserializer.readTabContentTransitionProxy() as TabContentTransitionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: TerminationInfo) => void))
    let parameter : TerminationInfo = thisDeserializer.readTerminationInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TextPickerResult) => void))
    let value : TextPickerResult = thisDeserializer.readTextPickerResult()
    _call(value)
}
export function deserializeAndCallCallback_TextRange_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: TextRange) => void))
    let parameter : TextRange = thisDeserializer.readTextRange()
    _call(parameter)
}
export function deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TimePickerResult) => void))
    let value : TimePickerResult = thisDeserializer.readTimePickerResult()
    _call(value)
}
export function deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: TouchEvent) => HitTestMode))
    let parameter : TouchEvent = (thisDeserializer.readTouchEvent() as TouchEvent)
    let _continuation : ((value: HitTestMode) => void) = thisDeserializer.readCallback_HitTestMode_Void(true)
    const _callResult  = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_TouchEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: TouchEvent) => void))
    let event : TouchEvent = (thisDeserializer.readTouchEvent() as TouchEvent)
    _call(event)
}
export function deserializeAndCallCallback_TouchResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: TouchResult) => void))
    let value : TouchResult = thisDeserializer.readTouchResult()
    _call(value)
}
export function deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number, number, number ]) => void))
    const value_buf_value0 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value1 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value2 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value3 : number = (thisDeserializer.readNumber() as number)
    let value : [ number, number, number, number ] = ([value_buf_value0, value_buf_value1, value_buf_value2, value_buf_value3] as [ number, number, number, number ])
    _call(value)
}
export function deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number ]) => void))
    const value_buf_value0 : number = (thisDeserializer.readNumber() as number)
    const value_buf_value1 : number = (thisDeserializer.readNumber() as number)
    let value : [ number, number ] = ([value_buf_value0, value_buf_value1] as [ number, number ])
    _call(value)
}
export function deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event?: Type_ImageAttribute_onComplete_callback_event) => void))
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Type_ImageAttribute_onComplete_callback_event | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__width : number = (thisDeserializer.readNumber() as number)
        const event_buf__height : number = (thisDeserializer.readNumber() as number)
        const event_buf__componentWidth : number = (thisDeserializer.readNumber() as number)
        const event_buf__componentHeight : number = (thisDeserializer.readNumber() as number)
        const event_buf__loadingStatus : number = (thisDeserializer.readNumber() as number)
        const event_buf__contentWidth : number = (thisDeserializer.readNumber() as number)
        const event_buf__contentHeight : number = (thisDeserializer.readNumber() as number)
        const event_buf__contentOffsetX : number = (thisDeserializer.readNumber() as number)
        const event_buf__contentOffsetY : number = (thisDeserializer.readNumber() as number)
        event_buf = ({width: event_buf__width, height: event_buf__height, componentWidth: event_buf__componentWidth, componentHeight: event_buf__componentHeight, loadingStatus: event_buf__loadingStatus, contentWidth: event_buf__contentWidth, contentHeight: event_buf__contentHeight, contentOffsetX: event_buf__contentOffsetX, contentOffsetY: event_buf__contentOffsetY} as Type_ImageAttribute_onComplete_callback_event)
    }
    let event : Type_ImageAttribute_onComplete_callback_event | undefined = event_buf
    _call(event)
}
export function deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((parameter: UIExtensionProxy) => void))
    let parameter : UIExtensionProxy = (thisDeserializer.readUIExtensionProxy() as UIExtensionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder | DragItemInfo) => void))
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : CustomBuilder | DragItemInfo | undefined
    if (value_buf_selector == 0) {
        value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    }
    else if (value_buf_selector == 1) {
        value_buf = thisDeserializer.readDragItemInfo()
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : CustomBuilder | DragItemInfo = (value_buf as CustomBuilder | DragItemInfo)
    _call(value)
}
export function deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Array<number>) => void))
    const selected_buf_selector : int32 = thisDeserializer.readInt8()
    let selected_buf : number | Array<number> | undefined
    if (selected_buf_selector == 0) {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    else if (selected_buf_selector == 1) {
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
export function deserializeAndCallCallback_Union_String_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: string | Array<string>) => void))
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
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
    _call(value)
}
export function deserializeAndCallCallback_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as (() => void))
    _call()
}
export function deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WebKeyboardOptions) => void))
    let value : WebKeyboardOptions = thisDeserializer.readWebKeyboardOptions()
    _call(value)
}
export function deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WebResourceResponse) => void))
    let value : WebResourceResponse = (thisDeserializer.readWebResourceResponse() as WebResourceResponse)
    _call(value)
}
export function deserializeAndCallCallback_WithThemeAttribute_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: WithThemeAttribute) => void))
    let value : WithThemeAttribute = thisDeserializer.readWithThemeAttribute()
    _call(value)
}
export function deserializeAndCallCallback_WrappedBuilder_Args_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((args: CommonConfiguration) => void))
    let args : CommonConfiguration = thisDeserializer.readCommonConfiguration()
    _call(args)
}
export function deserializeAndCallContentDidScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentDidScrollCallback)
    let selectedIndex : number = (thisDeserializer.readNumber() as number)
    let index : number = (thisDeserializer.readNumber() as number)
    let position : number = (thisDeserializer.readNumber() as number)
    let mainAxisLength : number = (thisDeserializer.readNumber() as number)
    _call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallContentWillScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ContentWillScrollCallback)
    let result : SwiperContentWillScrollResult = thisDeserializer.readSwiperContentWillScrollResult()
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(result)
    _continuation(_callResult)
}
export function deserializeAndCallContext_getGroupDir_Callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as Context_getGroupDir_Callback)
    let result : string = (thisDeserializer.readString() as string)
    _call(result)
}
export function deserializeAndCallCustomNodeBuilder(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as CustomNodeBuilder)
    let parentNode : KPointer = thisDeserializer.readPointer()
    let _continuation : ((value: KPointer) => void) = thisDeserializer.readCallback_Pointer_Void(true)
    const _callResult  = _call(parentNode)
    _continuation(_callResult)
}
export function deserializeAndCallDrawCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as DrawCallback)
    let context : DrawContext = thisDeserializer.readDrawContext()
    _call(context)
}
export function deserializeAndCallEditableTextOnChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as EditableTextOnChangeCallback)
    let value : string = (thisDeserializer.readString() as string)
    const previewText_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let previewText_buf : PreviewText | undefined
    if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
    {
        previewText_buf = thisDeserializer.readPreviewText()
    }
    let previewText : PreviewText | undefined = previewText_buf
    const options_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let options_buf : TextChangeOptions | undefined
    if ((RuntimeType.UNDEFINED) != (options_buf_runtimeType))
    {
        options_buf = thisDeserializer.readTextChangeOptions()
    }
    let options : TextChangeOptions | undefined = options_buf
    _call(value, previewText, options)
}
export function deserializeAndCallErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ErrorCallback)
    let err : BusinessError = thisDeserializer.readBusinessError()
    _call(err)
}
export function deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GestureRecognizerJudgeBeginCallback)
    let event : BaseGestureEvent = (thisDeserializer.readBaseGestureEvent() as BaseGestureEvent)
    let current : GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    const recognizers_buf_length : int32 = thisDeserializer.readInt32()
    let recognizers_buf : Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizers_buf_length)
    for (let recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf[recognizers_buf_i] = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    }
    let recognizers : Array<GestureRecognizer> = recognizers_buf
    let _continuation : ((value: GestureJudgeResult) => void) = thisDeserializer.readCallback_GestureJudgeResult_Void(true)
    const _callResult  = _call(event, current, recognizers)
    _continuation(_callResult)
}
export function deserializeAndCallGetItemMainSizeByIndex(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as GetItemMainSizeByIndex)
    let index : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((index: number) => void) = thisDeserializer.readCallback_Number_Void(true)
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallGridAttribute_onItemDragStart_event_type(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number) => CustomBuilder))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: CustomBuilder) => void) = thisDeserializer.readCallback_CustomBuilder_Void(true)
    const _callResult  = _call(event, itemIndex)
    _continuation(_callResult)
}
export function deserializeAndCallHoverCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as HoverCallback)
    let isHover : boolean = thisDeserializer.readBoolean()
    let event : HoverEvent = (thisDeserializer.readHoverEvent() as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallImageCompleteCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ImageCompleteCallback)
    let result : ImageLoadResult = thisDeserializer.readImageLoadResult()
    _call(result)
}
export function deserializeAndCallImageErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ImageErrorCallback)
    let error : ImageError = thisDeserializer.readImageError()
    _call(error)
}
export function deserializeAndCallInterceptionModeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionModeCallback)
    let mode : NavigationMode = TypeChecker.NavigationMode_FromNumeric(thisDeserializer.readInt32())
    _call(mode)
}
export function deserializeAndCallInterceptionShowCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as InterceptionShowCallback)
    const from_buf_selector : int32 = thisDeserializer.readInt8()
    let from_buf : NavDestinationContext | NavBar | undefined
    if (from_buf_selector == 0) {
        from_buf = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    }
    else if (from_buf_selector == 1) {
        from_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for from_buf has to be chosen through deserialisation.")
    }
    let from : NavDestinationContext | NavBar = (from_buf as NavDestinationContext | NavBar)
    const to_buf_selector : int32 = thisDeserializer.readInt8()
    let to_buf : NavDestinationContext | NavBar | undefined
    if (to_buf_selector == 0) {
        to_buf = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    }
    else if (to_buf_selector == 1) {
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
export function deserializeAndCallListAttribute_onItemDragStart_event_type(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo,itemIndex: number) => CustomBuilder))
    let event : ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: CustomBuilder) => void) = thisDeserializer.readCallback_CustomBuilder_Void(true)
    const _callResult  = _call(event, itemIndex)
    _continuation(_callResult)
}
export function deserializeAndCallLocationButtonCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as LocationButtonCallback)
    let event : ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result : LocationButtonOnClickResult = TypeChecker.LocationButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    const error_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let error_buf : BusinessError<void> | undefined
    if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
    {
        error_buf = thisDeserializer.readBusinessError()
    }
    let error : BusinessError<void> | undefined = error_buf
    _call(event, result, error)
}
export function deserializeAndCallMenuCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuCallback)
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    _call(start, end)
}
export function deserializeAndCallMenuOnAppearCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as MenuOnAppearCallback)
    let start : number = (thisDeserializer.readNumber() as number)
    let end : number = (thisDeserializer.readNumber() as number)
    _call(start, end)
}
export function deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavDestinationTransitionDelegate)
    let operation : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(thisDeserializer.readInt32())
    let isEnter : boolean = thisDeserializer.readBoolean()
    let _continuation : ((value: Array<NavDestinationTransition> | undefined) => void) = thisDeserializer.readCallback_Opt_Array_NavDestinationTransition_Void(true)
    const _callResult  = _call(operation, isEnter)
    _continuation(_callResult)
}
export function deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NavExtender_OnUpdateStack)
    _call()
}
export function deserializeAndCallNodeContainer_AboutToResizeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as NodeContainer_AboutToResizeCallback)
    let size : Size = thisDeserializer.readSize()
    _call(size)
}
export function deserializeAndCallOnAdsBlockedCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAdsBlockedCallback)
    let details : AdsBlockedDetails = thisDeserializer.readAdsBlockedDetails()
    _call(details)
}
export function deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerPopupSelectCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerRequestPopupDataCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: Array<string>) => void) = thisDeserializer.readCallback_Array_String_Void(true)
    const _callResult  = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerSelectCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallOnCheckboxChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnCheckboxChangeCallback)
    let value : boolean = thisDeserializer.readBoolean()
    _call(value)
}
export function deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnCheckboxGroupChangeCallback)
    let value : CheckboxGroupResult = thisDeserializer.readCheckboxGroupResult()
    _call(value)
}
export function deserializeAndCallOnContentScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnContentScrollCallback)
    let totalOffsetX : number = (thisDeserializer.readNumber() as number)
    let totalOffsetY : number = (thisDeserializer.readNumber() as number)
    _call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallOnContextMenuHideCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnContextMenuHideCallback)
    _call()
}
export function deserializeAndCallOnDidChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnDidChangeCallback)
    let rangeBefore : TextRange = thisDeserializer.readTextRange()
    let rangeAfter : TextRange = thisDeserializer.readTextRange()
    _call(rangeBefore, rangeAfter)
}
export function deserializeAndCallOnDragEventCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnDragEventCallback)
    let event : DragEvent = (thisDeserializer.readDragEvent() as DragEvent)
    const extraParams_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let extraParams_buf : string | undefined
    if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams : string | undefined = extraParams_buf
    _call(event, extraParams)
}
export function deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFirstMeaningfulPaintCallback)
    let firstMeaningfulPaint : FirstMeaningfulPaint = thisDeserializer.readFirstMeaningfulPaint()
    _call(firstMeaningfulPaint)
}
export function deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFoldStatusChangeCallback)
    let event : OnFoldStatusChangeInfo = thisDeserializer.readOnFoldStatusChangeInfo()
    _call(event)
}
export function deserializeAndCallOnFullScreenEnterCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnFullScreenEnterCallback)
    let event : FullScreenEnterEvent = thisDeserializer.readFullScreenEnterEvent()
    _call(event)
}
export function deserializeAndCallOnHoverCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnHoverCallback)
    _call()
}
export function deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnHoverStatusChangeCallback)
    let param : HoverEventParam = thisDeserializer.readHoverEventParam()
    _call(param)
}
export function deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnIntelligentTrackingPreventionCallback)
    let details : IntelligentTrackingPreventionDetails = thisDeserializer.readIntelligentTrackingPreventionDetails()
    _call(details)
}
export function deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnLargestContentfulPaintCallback)
    let largestContentfulPaint : LargestContentfulPaint = thisDeserializer.readLargestContentfulPaint()
    _call(largestContentfulPaint)
}
export function deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnLinearIndicatorChangeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let progress : number = (thisDeserializer.readNumber() as number)
    _call(index, progress)
}
export function deserializeAndCallOnMoveHandler(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnMoveHandler)
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    _call(from, to)
}
export function deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeEmbedVisibilityChangeCallback)
    let nativeEmbedVisibilityInfo : NativeEmbedVisibilityInfo = thisDeserializer.readNativeEmbedVisibilityInfo()
    _call(nativeEmbedVisibilityInfo)
}
export function deserializeAndCallOnNativeLoadCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNativeLoadCallback)
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Object | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readObject() as Object)
    }
    let event : Object | undefined = event_buf
    _call(event)
}
export function deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnNavigationEntryCommittedCallback)
    let loadCommittedDetails : LoadCommittedDetails = thisDeserializer.readLoadCommittedDetails()
    _call(loadCommittedDetails)
}
export function deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnOverrideUrlLoadingCallback)
    let webResourceRequest : WebResourceRequest = (thisDeserializer.readWebResourceRequest() as WebResourceRequest)
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(webResourceRequest)
    _continuation(_callResult)
}
export function deserializeAndCallOnPasteCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnPasteCallback)
    let content : string = (thisDeserializer.readString() as string)
    let event : PasteEvent = thisDeserializer.readPasteEvent()
    _call(content, event)
}
export function deserializeAndCallOnRadioChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRadioChangeCallback)
    let isChecked : boolean = thisDeserializer.readBoolean()
    _call(isChecked)
}
export function deserializeAndCallOnRatingChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRatingChangeCallback)
    let rating : number = (thisDeserializer.readNumber() as number)
    _call(rating)
}
export function deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessNotRespondingCallback)
    let data : RenderProcessNotRespondingData = thisDeserializer.readRenderProcessNotRespondingData()
    _call(data)
}
export function deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessRespondingCallback)
    _call()
}
export function deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSafeBrowsingCheckResultCallback)
    let threatType : ThreatType = TypeChecker.ThreatType_FromNumeric(thisDeserializer.readInt32())
    _call(threatType)
}
export function deserializeAndCallOnScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollCallback)
    let scrollOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    _call(scrollOffset, scrollState)
}
export function deserializeAndCallOnWillScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnWillScrollCallback)
    let scrollOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = (thisDeserializer.readInt32() as ScrollState)
    let scrollSource : ScrollSource = (thisDeserializer.readInt32() as ScrollSource)
    let _continuation : ((value: ScrollResult) => void) = thisDeserializer.readCallback_ScrollResult_Void(true)
    const _callResult  = _call(scrollOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallOnScrollEdgeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollEdgeCallback)
    let side : Edge = TypeChecker.Edge_FromNumeric(thisDeserializer.readInt32())
    _call(side)
}
export function deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollFrameBeginCallback)
    let offset : number = (thisDeserializer.readNumber() as number)
    let state : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    let _continuation : ((value: OnScrollFrameBeginHandlerResult) => void) = thisDeserializer.readCallback_OnScrollFrameBeginHandlerResult_Void(true)
    const _callResult  = _call(offset, state)
    _continuation(_callResult)
}
export function deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnScrollVisibleContentChangeCallback)
    let start : VisibleListContentInfo = thisDeserializer.readVisibleListContentInfo()
    let end : VisibleListContentInfo = thisDeserializer.readVisibleListContentInfo()
    _call(start, end)
}
export function deserializeAndCallOnSelectCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSelectCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let selectStr : string = (thisDeserializer.readString() as string)
    _call(index, selectStr)
}
export function deserializeAndCallOnSslErrorEventCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSslErrorEventCallback)
    let sslErrorEvent : SslErrorEvent = thisDeserializer.readSslErrorEvent()
    _call(sslErrorEvent)
}
export function deserializeAndCallOnSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSubmitCallback)
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    let event : SubmitEvent = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationEndCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationStartCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let targetIndex : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnSwiperGestureSwipeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationEndCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationStartCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let targetIndex : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsContentWillChangeCallback)
    let currentIndex : number = (thisDeserializer.readNumber() as number)
    let comingIndex : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(currentIndex, comingIndex)
    _continuation(_callResult)
}
export function deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTabsGestureSwipeCallback)
    let index : number = (thisDeserializer.readNumber() as number)
    let extraInfo : TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTextPickerChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextPickerChangeCallback)
    const selectItem_buf_selector : int32 = thisDeserializer.readInt8()
    let selectItem_buf : string | Array<string> | undefined
    if (selectItem_buf_selector == 0) {
        selectItem_buf = (thisDeserializer.readString() as string)
    }
    else if (selectItem_buf_selector == 1) {
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
    if (index_buf_selector == 0) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == 1) {
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
export function deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTextSelectionChangeCallback)
    let selectionStart : number = (thisDeserializer.readNumber() as number)
    let selectionEnd : number = (thisDeserializer.readNumber() as number)
    _call(selectionStart, selectionEnd)
}
export function deserializeAndCallOnTimePickerChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnTimePickerChangeCallback)
    let result : TimePickerResult = thisDeserializer.readTimePickerResult()
    _call(result)
}
export function deserializeAndCallOnViewportFitChangedCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as OnViewportFitChangedCallback)
    let viewportFit : ViewportFit = TypeChecker.ViewportFit_FromNumeric(thisDeserializer.readInt32())
    _call(viewportFit)
}
export function deserializeAndCallPageTransitionCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PageTransitionCallback)
    let type : RouteType = TypeChecker.RouteType_FromNumeric(thisDeserializer.readInt32())
    let progress : number = (thisDeserializer.readNumber() as number)
    _call(type, progress)
}
export function deserializeAndCallPasteButtonCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PasteButtonCallback)
    let event : ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result : PasteButtonOnClickResult = TypeChecker.PasteButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    let error_buf : BusinessError<void> | undefined
    let error : BusinessError<void> | undefined = error_buf
    _call(event, result, error)
}
export function deserializeAndCallPasteEventCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PasteEventCallback)
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : PasteEvent | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = thisDeserializer.readPasteEvent()
    }
    let event : PasteEvent | undefined = event_buf
    _call(event)
}
export function deserializeAndCallPluginErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PluginErrorCallback)
    let info : PluginErrorData = thisDeserializer.readPluginErrorData()
    _call(info)
}
export function deserializeAndCallPopupStateChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as PopupStateChangeCallback)
    let event : PopupStateChangeParam = thisDeserializer.readPopupStateChangeParam()
    _call(event)
}
export function deserializeAndCallReceiveCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ReceiveCallback)
    const data_buf_size : int32 = thisDeserializer.readInt32()
    let data_buf : Map<string, Object> = new Map<string, Object>()
    // TODO: TS map resize
    for (let data_buf_i = 0; data_buf_i < data_buf_size; data_buf_i++) {
        const data_buf_key : string = (thisDeserializer.readString() as string)
        const data_buf_value : Object = (thisDeserializer.readObject() as Object)
        data_buf.set(data_buf_key, data_buf_value)
    }
    let data : Map<string, Object> = data_buf
    _call(data)
}
export function deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onerror_Callback)
    let ev : ErrorEvent = thisDeserializer.readErrorEvent()
    _call(ev)
}
export function deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onexit_Callback)
    let code : number = (thisDeserializer.readNumber() as number)
    _call(code)
}
export function deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as RestrictedWorker_onmessage_Callback)
    let event : MessageEvents = thisDeserializer.readMessageEvents()
    _call(event)
}
export function deserializeAndCallReuseIdCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ReuseIdCallback)
    let _continuation : ((breakpoints: string) => void) = thisDeserializer.readCallback_String_Void(true)
    const _callResult  = _call()
    _continuation(_callResult)
}
export function deserializeAndCallSaveButtonCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SaveButtonCallback)
    let event : ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result : SaveButtonOnClickResult = TypeChecker.SaveButtonOnClickResult_FromNumeric(thisDeserializer.readInt32())
    let error_buf : BusinessError<void> | undefined
    let error : BusinessError<void> | undefined = error_buf
    _call(event, result, error)
}
export function deserializeAndCallScrollOnScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnScrollCallback)
    let xOffset : number = (thisDeserializer.readNumber() as number)
    let yOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    _call(xOffset, yOffset, scrollState)
}
export function deserializeAndCallScrollOnWillScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ScrollOnWillScrollCallback)
    let xOffset : number = (thisDeserializer.readNumber() as number)
    let yOffset : number = (thisDeserializer.readNumber() as number)
    let scrollState : ScrollState = TypeChecker.ScrollState_FromNumeric(thisDeserializer.readInt32())
    let scrollSource : ScrollSource = TypeChecker.ScrollSource_FromNumeric(thisDeserializer.readInt32())
    let _continuation : ((value: OffsetResult) => void) = thisDeserializer.readCallback_OffsetResult_Void(true)
    const _callResult  = _call(xOffset, yOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallSearchSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SearchSubmitCallback)
    let searchContent : string = (thisDeserializer.readString() as string)
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : SubmitEvent | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    }
    let event : SubmitEvent | undefined = event_buf
    _call(searchContent, event)
}
export function deserializeAndCallSearchValueCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SearchValueCallback)
    let value : string = (thisDeserializer.readString() as string)
    _call(value)
}
export function deserializeAndCallSelectedCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SelectedCallback)
    let selected : boolean = thisDeserializer.readBoolean()
    _call(selected)
}
export function deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ShouldBuiltInRecognizerParallelWithCallback)
    let current : GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    const others_buf_length : int32 = thisDeserializer.readInt32()
    let others_buf : Array<GestureRecognizer> = new Array<GestureRecognizer>(others_buf_length)
    for (let others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf[others_buf_i] = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    }
    let others : Array<GestureRecognizer> = others_buf
    let _continuation : ((value: GestureRecognizer) => void) = thisDeserializer.readCallback_GestureRecognizer_Void(true)
    const _callResult  = _call(current, others)
    _continuation(_callResult)
}
export function deserializeAndCallSizeChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SizeChangeCallback)
    let oldValue : SizeOptions = thisDeserializer.readSizeOptions()
    let newValue : SizeOptions = thisDeserializer.readSizeOptions()
    _call(oldValue, newValue)
}
export function deserializeAndCallSliderTriggerChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SliderTriggerChangeCallback)
    let value : number = (thisDeserializer.readNumber() as number)
    let mode : SliderChangeMode = TypeChecker.SliderChangeMode_FromNumeric(thisDeserializer.readInt32())
    _call(value, mode)
}
export function deserializeAndCallStepperIndexCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StepperIndexCallback)
    let stepperIndex : number = (thisDeserializer.readNumber() as number)
    _call(stepperIndex)
}
export function deserializeAndCallStyledStringMarshallCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringMarshallCallback)
    let marshallableVal : UserDataSpan = thisDeserializer.readUserDataSpan()
    let _continuation : ((value: NativeBuffer) => void) = thisDeserializer.readCallback_Buffer_Void(true)
    const _callResult  = _call(marshallableVal)
    _continuation(_callResult)
}
export function deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as StyledStringUnmarshallCallback)
    let buf : NativeBuffer = (thisDeserializer.readBuffer() as NativeBuffer)
    let _continuation : ((value: UserDataSpan) => void) = thisDeserializer.readCallback_StyledStringMarshallingValue_Void(true)
    const _callResult  = _call(buf)
    _continuation(_callResult)
}
export function deserializeAndCallSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as SubmitCallback)
    let enterKey : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    let event : SubmitEvent = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TabsCustomContentTransitionCallback)
    let from : number = (thisDeserializer.readNumber() as number)
    let to : number = (thisDeserializer.readNumber() as number)
    let _continuation : ((value: TabContentAnimatedTransition | undefined) => void) = thisDeserializer.readCallback_Opt_TabContentAnimatedTransition_Void(true)
    const _callResult  = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallTextAreaSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextAreaSubmitCallback)
    let enterKeyType : EnterKeyType = TypeChecker.EnterKeyType_FromNumeric(thisDeserializer.readInt32())
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : SubmitEvent | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    }
    let event : SubmitEvent | undefined = event_buf
    _call(enterKeyType, event)
}
export function deserializeAndCallTextFieldValueCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextFieldValueCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Resource | undefined
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
        value_buf = thisDeserializer.readResource()
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value : ResourceStr = (value_buf as string | Resource)
    _call(value)
}
export function deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerEnterSelectedAreaCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
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
    if (index_buf_selector == 0) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == 1) {
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
export function deserializeAndCallTextPickerScrollStopCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TextPickerScrollStopCallback)
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
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
    if (index_buf_selector == 0) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == 1) {
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
export function deserializeAndCallTextTimerAttribute_onTimer_event_type(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((utc: int64,elapsedTime: int64) => void))
    let utc : int64 = thisDeserializer.readInt64()
    let elapsedTime : int64 = thisDeserializer.readInt64()
    _call(utc, elapsedTime)
}
export function deserializeAndCallTransitionFinishCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as TransitionFinishCallback)
    let transitionIn : boolean = thisDeserializer.readBoolean()
    _call(transitionIn)
}
export function deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
    let from : NavContentInfo = thisDeserializer.readNavContentInfo()
    let to : NavContentInfo = thisDeserializer.readNavContentInfo()
    let operation : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(thisDeserializer.readInt32())
    let _continuation : ((value: NavigationAnimatedTransition | undefined) => void) = thisDeserializer.readCallback_Opt_NavigationAnimatedTransition_Void(true)
    const _callResult  = _call(from, to, operation)
    _continuation(_callResult)
}
export function deserializeAndCallType_TextPickerAttribute_onChange_callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((value: string | Array<string>,index: number | Array<number>) => void))
    const value_buf_selector : int32 = thisDeserializer.readInt8()
    let value_buf : string | Array<string> | undefined
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
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
    if (index_buf_selector == 0) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == 1) {
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
export function deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event?: Literal_Function_callback__Object_fileSelector) => void))
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Literal_Function_callback__Object_fileSelector | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        throw new Error("Not implemented yet")
    }
    let event : Literal_Function_callback__Object_fileSelector | undefined = event_buf
    _call(event)
}
export function deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((event?: Literal_Union_String_WebResourceRequest_data) => boolean))
    const event_buf_runtimeType  = (thisDeserializer.readInt8() as int32)
    let event_buf : Literal_Union_String_WebResourceRequest_data | undefined
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__data_buf_selector : int32 = thisDeserializer.readInt8()
        let event_buf__data_buf : string | WebResourceRequest | undefined
        if (event_buf__data_buf_selector == 0) {
            event_buf__data_buf = (thisDeserializer.readString() as string)
        }
        else if (event_buf__data_buf_selector == 1) {
            event_buf__data_buf = (thisDeserializer.readWebResourceRequest() as WebResourceRequest)
        }
        else {
            throw new Error("One of the branches for event_buf__data_buf has to be chosen through deserialisation.")
        }
        const event_buf__data : string | WebResourceRequest = (event_buf__data_buf as string | WebResourceRequest)
        event_buf = ({data: event_buf__data} as Literal_Union_String_WebResourceRequest_data)
    }
    let event : Literal_Union_String_WebResourceRequest_data | undefined = event_buf
    let _continuation : ((isVisible: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult  = _call(event)
    _continuation(_callResult)
}
export function deserializeAndCallVisibleAreaChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as VisibleAreaChangeCallback)
    let isExpanding : boolean = thisDeserializer.readBoolean()
    let currentRatio : number = (thisDeserializer.readNumber() as number)
    _call(isExpanding, currentRatio)
}
export function deserializeAndCallVoidCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as VoidCallback)
    _call()
}
export function deserializeAndCallWebKeyboardCallback(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as WebKeyboardCallback)
    let keyboardCallbackInfo : WebKeyboardCallbackInfo = thisDeserializer.readWebKeyboardCallbackInfo()
    let _continuation : ((value: WebKeyboardOptions) => void) = thisDeserializer.readCallback_WebKeyboardOptions_Void(true)
    const _callResult  = _call(keyboardCallbackInfo)
    _continuation(_callResult)
}
export function deserializeAndCallWithThemeInterface(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as WithThemeInterface)
    let options : WithThemeOptions = thisDeserializer.readWithThemeOptions()
    let _continuation : ((value: WithThemeAttribute) => void) = thisDeserializer.readCallback_WithThemeAttribute_Void(true)
    const _callResult  = _call(options)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((surfaceId: string,rect: SurfaceRect) => void))
    let surfaceId : string = (thisDeserializer.readString() as string)
    let rect : SurfaceRect = thisDeserializer.readSurfaceRect()
    _call(surfaceId, rect)
}
export function deserializeAndCallCallback(thisDeserializer: Deserializer): void {
    const kind : int32 = thisDeserializer.readInt32()
    switch (kind) {
        case 589030517/*CallbackKind.Kind_AccessibilityCallback*/: return deserializeAndCallAccessibilityCallback(thisDeserializer);
        case 1715445305/*CallbackKind.Kind_AccessibilityFocusCallback*/: return deserializeAndCallAccessibilityFocusCallback(thisDeserializer);
        case 300202685/*CallbackKind.Kind_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem*/: return deserializeAndCallAsyncCallback_Array_TextMenuItem_Array_TextMenuItem(thisDeserializer);
        case 1289587365/*CallbackKind.Kind_AsyncCallback_image_PixelMap_Void*/: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer);
        case -1581515233/*CallbackKind.Kind_AsyncCallback_TextMenuItem_TextRange_Boolean*/: return deserializeAndCallAsyncCallback_TextMenuItem_TextRange_Boolean(thisDeserializer);
        case -1964292933/*CallbackKind.Kind_ButtonTriggerClickCallback*/: return deserializeAndCallButtonTriggerClickCallback(thisDeserializer);
        case 197193081/*CallbackKind.Kind_Callback_Any_Void*/: return deserializeAndCallCallback_Any_Void(thisDeserializer);
        case -2024393616/*CallbackKind.Kind_Callback_Area_Area_Void*/: return deserializeAndCallCallback_Area_Area_Void(thisDeserializer);
        case 582384234/*CallbackKind.Kind_Callback_Array_Number_Void*/: return deserializeAndCallCallback_Array_Number_Void(thisDeserializer);
        case -440782244/*CallbackKind.Kind_Callback_Array_String_Void*/: return deserializeAndCallCallback_Array_String_Void(thisDeserializer);
        case 528588498/*CallbackKind.Kind_Callback_Array_TextMenuItem_Void*/: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisDeserializer);
        case -547276916/*CallbackKind.Kind_Callback_Array_TouchTestInfo_TouchResult*/: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer);
        case 109087936/*CallbackKind.Kind_Callback_AxisEvent_Void*/: return deserializeAndCallCallback_AxisEvent_Void(thisDeserializer);
        case -1541107680/*CallbackKind.Kind_Callback_Boolean*/: return deserializeAndCallCallback_Boolean(thisDeserializer);
        case -916602978/*CallbackKind.Kind_Callback_Boolean_HoverEvent_Void*/: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer);
        case 313269291/*CallbackKind.Kind_Callback_Boolean_Void*/: return deserializeAndCallCallback_Boolean_Void(thisDeserializer);
        case 908731311/*CallbackKind.Kind_Callback_Buffer_Void*/: return deserializeAndCallCallback_Buffer_Void(thisDeserializer);
        case 1074619005/*CallbackKind.Kind_Callback_CalendarRequestedData_Void*/: return deserializeAndCallCallback_CalendarRequestedData_Void(thisDeserializer);
        case -289198976/*CallbackKind.Kind_Callback_CalendarSelectedDate_Void*/: return deserializeAndCallCallback_CalendarSelectedDate_Void(thisDeserializer);
        case 1097178637/*CallbackKind.Kind_Callback_ClickEvent_Void*/: return deserializeAndCallCallback_ClickEvent_Void(thisDeserializer);
        case -1270343661/*CallbackKind.Kind_Callback_ComputedBarAttribute_Void*/: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer);
        case -120437466/*CallbackKind.Kind_Callback_CopyEvent_Void*/: return deserializeAndCallCallback_CopyEvent_Void(thisDeserializer);
        case -2019730059/*CallbackKind.Kind_Callback_CreateItem*/: return deserializeAndCallCallback_CreateItem(thisDeserializer);
        case -827253372/*CallbackKind.Kind_Callback_CrownEvent_Void*/: return deserializeAndCallCallback_CrownEvent_Void(thisDeserializer);
        case -721106019/*CallbackKind.Kind_Callback_CustomBuilder_Void*/: return deserializeAndCallCallback_CustomBuilder_Void(thisDeserializer);
        case -1875695871/*CallbackKind.Kind_Callback_CutEvent_Void*/: return deserializeAndCallCallback_CutEvent_Void(thisDeserializer);
        case 1405382363/*CallbackKind.Kind_Callback_Date_Void*/: return deserializeAndCallCallback_Date_Void(thisDeserializer);
        case 1280920532/*CallbackKind.Kind_Callback_DatePickerResult_Void*/: return deserializeAndCallCallback_DatePickerResult_Void(thisDeserializer);
        case -1357792883/*CallbackKind.Kind_Callback_DeleteValue_Boolean*/: return deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer);
        case -126251459/*CallbackKind.Kind_Callback_DeleteValue_Void*/: return deserializeAndCallCallback_DeleteValue_Void(thisDeserializer);
        case -1283506641/*CallbackKind.Kind_Callback_DismissContentCoverAction_Void*/: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer);
        case -2095828093/*CallbackKind.Kind_Callback_DismissDialogAction_Void*/: return deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer);
        case -2004166751/*CallbackKind.Kind_Callback_DismissPopupAction_Void*/: return deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer);
        case 889549796/*CallbackKind.Kind_Callback_DismissSheetAction_Void*/: return deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer);
        case 480978023/*CallbackKind.Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo*/: return deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(thisDeserializer);
        case -17167687/*CallbackKind.Kind_Callback_DragEvent_String_Void*/: return deserializeAndCallCallback_DragEvent_String_Void(thisDeserializer);
        case -602545319/*CallbackKind.Kind_Callback_EditableTextChangeValue_Boolean*/: return deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisDeserializer);
        case -1802605016/*CallbackKind.Kind_Callback_EnterKeyType_Void*/: return deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer);
        case -733525640/*CallbackKind.Kind_Callback_Extender_OnFinish*/: return deserializeAndCallCallback_Extender_OnFinish(thisDeserializer);
        case 1264236374/*CallbackKind.Kind_Callback_Extender_OnProgress*/: return deserializeAndCallCallback_Extender_OnProgress(thisDeserializer);
        case 394781580/*CallbackKind.Kind_Callback_FocusAxisEvent_Void*/: return deserializeAndCallCallback_FocusAxisEvent_Void(thisDeserializer);
        case 758395742/*CallbackKind.Kind_Callback_FormCallbackInfo_Void*/: return deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer);
        case 583294398/*CallbackKind.Kind_Callback_FullscreenInfo_Void*/: return deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer);
        case -1143194492/*CallbackKind.Kind_Callback_GestureEvent_Void*/: return deserializeAndCallCallback_GestureEvent_Void(thisDeserializer);
        case 1319043556/*CallbackKind.Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult*/: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer);
        case -684588584/*CallbackKind.Kind_Callback_GestureJudgeResult_Void*/: return deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer);
        case 776202910/*CallbackKind.Kind_Callback_GestureRecognizer_Void*/: return deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer);
        case -1755111025/*CallbackKind.Kind_Callback_HitTestMode_Void*/: return deserializeAndCallCallback_HitTestMode_Void(thisDeserializer);
        case -1576788379/*CallbackKind.Kind_Callback_HoverEvent_Void*/: return deserializeAndCallCallback_HoverEvent_Void(thisDeserializer);
        case -383025085/*CallbackKind.Kind_Callback_InsertValue_Boolean*/: return deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer);
        case -1121207885/*CallbackKind.Kind_Callback_InsertValue_Void*/: return deserializeAndCallCallback_InsertValue_Void(thisDeserializer);
        case -1627362945/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer);
        case -918805852/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer);
        case 296908152/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer);
        case 137353252/*CallbackKind.Kind_Callback_ItemDragInfo_Void*/: return deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer);
        case -2061548092/*CallbackKind.Kind_Callback_KeyEvent_Boolean*/: return deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer);
        case 707696468/*CallbackKind.Kind_Callback_KeyEvent_Void*/: return deserializeAndCallCallback_KeyEvent_Void(thisDeserializer);
        case -1561407084/*CallbackKind.Kind_Callback_Literal_Boolean_isVisible_Void*/: return deserializeAndCallCallback_Literal_Boolean_isVisible_Void(thisDeserializer);
        case 361012115/*CallbackKind.Kind_Callback_Literal_Function_handler_Object_error_Void*/: return deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(thisDeserializer);
        case -946200218/*CallbackKind.Kind_Callback_Literal_Number_code__want_Void*/: return deserializeAndCallCallback_Literal_Number_code__want_Void(thisDeserializer);
        case 1321277443/*CallbackKind.Kind_Callback_Literal_Number_errcode_String_msg_Void*/: return deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(thisDeserializer);
        case -251706058/*CallbackKind.Kind_Callback_Literal_Number_offsetRemain_Void*/: return deserializeAndCallCallback_Literal_Number_offsetRemain_Void(thisDeserializer);
        case 222742448/*CallbackKind.Kind_Callback_Literal_Object_detail_Boolean*/: return deserializeAndCallCallback_Literal_Object_detail_Boolean(thisDeserializer);
        case -122223466/*CallbackKind.Kind_Callback_Literal_String_plainText_Void*/: return deserializeAndCallCallback_Literal_String_plainText_Void(thisDeserializer);
        case -1146723341/*CallbackKind.Kind_Callback_Map_String_Object_Void*/: return deserializeAndCallCallback_Map_String_Object_Void(thisDeserializer);
        case -716263454/*CallbackKind.Kind_Callback_MarqueeState_Void*/: return deserializeAndCallCallback_MarqueeState_Void(thisDeserializer);
        case -1382640094/*CallbackKind.Kind_Callback_MouseEvent_Void*/: return deserializeAndCallCallback_MouseEvent_Void(thisDeserializer);
        case 477481563/*CallbackKind.Kind_Callback_NativeEmbedDataInfo_Void*/: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer);
        case -1090303858/*CallbackKind.Kind_Callback_NativeEmbedTouchInfo_Void*/: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer);
        case 634825762/*CallbackKind.Kind_Callback_NavDestinationActiveReason_Void*/: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisDeserializer);
        case -1642725259/*CallbackKind.Kind_Callback_NavDestinationContext_Void*/: return deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer);
        case 960690982/*CallbackKind.Kind_Callback_NavigationMode_Void*/: return deserializeAndCallCallback_NavigationMode_Void(thisDeserializer);
        case 1685437830/*CallbackKind.Kind_Callback_NavigationTitleMode_Void*/: return deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer);
        case -1375731066/*CallbackKind.Kind_Callback_NavigationTransitionProxy_Void*/: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer);
        case 1054099324/*CallbackKind.Kind_Callback_Number_Boolean*/: return deserializeAndCallCallback_Number_Boolean(thisDeserializer);
        case -1427334496/*CallbackKind.Kind_Callback_Number_Number_Boolean*/: return deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer);
        case -3987624/*CallbackKind.Kind_Callback_Number_Number_ComputedBarAttribute*/: return deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer);
        case -352942292/*CallbackKind.Kind_Callback_Number_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer);
        case 1613628570/*CallbackKind.Kind_Callback_Number_Number_PanelMode_Void*/: return deserializeAndCallCallback_Number_Number_PanelMode_Void(thisDeserializer);
        case 1894574320/*CallbackKind.Kind_Callback_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Void(thisDeserializer);
        case 2012829508/*CallbackKind.Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain*/: return deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(thisDeserializer);
        case 88697971/*CallbackKind.Kind_Callback_Number_SliderChangeMode_Void*/: return deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer);
        case 794065478/*CallbackKind.Kind_Callback_Number_String_Void*/: return deserializeAndCallCallback_Number_String_Void(thisDeserializer);
        case 1602877440/*CallbackKind.Kind_Callback_Number_Tuple_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer);
        case 1618565120/*CallbackKind.Kind_Callback_Number_Tuple_Number_Number_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer);
        case 36519084/*CallbackKind.Kind_Callback_Number_Void*/: return deserializeAndCallCallback_Number_Void(thisDeserializer);
        case -1782529222/*CallbackKind.Kind_Callback_Object_Void*/: return deserializeAndCallCallback_Object_Void(thisDeserializer);
        case 1295952075/*CallbackKind.Kind_Callback_OffsetResult_Void*/: return deserializeAndCallCallback_OffsetResult_Void(thisDeserializer);
        case 1385252075/*CallbackKind.Kind_Callback_ScrollResult_Void*/: return deserializeAndCallCallback_ScrollResult_Void(thisDeserializer);
        case 806070428/*CallbackKind.Kind_Callback_OnAlertEvent_Boolean*/: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer);
        case -1559789631/*CallbackKind.Kind_Callback_OnAudioStateChangedEvent_Void*/: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer);
        case -873162122/*CallbackKind.Kind_Callback_OnBeforeUnloadEvent_Boolean*/: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer);
        case 608991355/*CallbackKind.Kind_Callback_OnClientAuthenticationEvent_Void*/: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer);
        case 317864672/*CallbackKind.Kind_Callback_OnConfirmEvent_Boolean*/: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer);
        case 893367077/*CallbackKind.Kind_Callback_OnConsoleEvent_Boolean*/: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer);
        case 332449533/*CallbackKind.Kind_Callback_OnContextMenuShowEvent_Boolean*/: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer);
        case 118631204/*CallbackKind.Kind_Callback_OnDataResubmittedEvent_Void*/: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer);
        case 1834611702/*CallbackKind.Kind_Callback_OnDownloadStartEvent_Void*/: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer);
        case -1792851375/*CallbackKind.Kind_Callback_OnErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer);
        case -243916553/*CallbackKind.Kind_Callback_OnFaviconReceivedEvent_Void*/: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer);
        case -1852060212/*CallbackKind.Kind_Callback_OnFirstContentfulPaintEvent_Void*/: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer);
        case -941896815/*CallbackKind.Kind_Callback_OnGeolocationShowEvent_Void*/: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer);
        case 780282803/*CallbackKind.Kind_Callback_OnHttpAuthRequestEvent_Boolean*/: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer);
        case -2066745559/*CallbackKind.Kind_Callback_OnHttpErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer);
        case 1442698200/*CallbackKind.Kind_Callback_OnInterceptRequestEvent_WebResourceResponse*/: return deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer);
        case 1231444306/*CallbackKind.Kind_Callback_OnLoadInterceptEvent_Boolean*/: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer);
        case -860386431/*CallbackKind.Kind_Callback_OnOverScrollEvent_Void*/: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer);
        case -2040193994/*CallbackKind.Kind_Callback_OnPageBeginEvent_Void*/: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer);
        case -130135362/*CallbackKind.Kind_Callback_OnPageEndEvent_Void*/: return deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer);
        case 1805946367/*CallbackKind.Kind_Callback_OnPageVisibleEvent_Void*/: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer);
        case 529980696/*CallbackKind.Kind_Callback_OnPermissionRequestEvent_Void*/: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer);
        case 1018740377/*CallbackKind.Kind_Callback_OnProgressChangeEvent_Void*/: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer);
        case -1826742986/*CallbackKind.Kind_Callback_OnPromptEvent_Boolean*/: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer);
        case 1978364344/*CallbackKind.Kind_Callback_OnRefreshAccessedHistoryEvent_Void*/: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer);
        case -1413785559/*CallbackKind.Kind_Callback_OnRenderExitedEvent_Void*/: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer);
        case 793995118/*CallbackKind.Kind_Callback_OnResourceLoadEvent_Void*/: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer);
        case -1782102148/*CallbackKind.Kind_Callback_OnScaleChangeEvent_Void*/: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer);
        case -1972321573/*CallbackKind.Kind_Callback_OnScreenCaptureRequestEvent_Void*/: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer);
        case -172908881/*CallbackKind.Kind_Callback_OnScrollEvent_Void*/: return deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer);
        case 1637092936/*CallbackKind.Kind_Callback_OnScrollFrameBeginHandlerResult_Void*/: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer);
        case -1495570/*CallbackKind.Kind_Callback_OnSearchResultReceiveEvent_Void*/: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer);
        case -636069598/*CallbackKind.Kind_Callback_OnShowFileSelectorEvent_Boolean*/: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer);
        case 1624791665/*CallbackKind.Kind_Callback_OnSslErrorEventReceiveEvent_Void*/: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer);
        case -318085495/*CallbackKind.Kind_Callback_OnTitleReceiveEvent_Void*/: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer);
        case 1657893064/*CallbackKind.Kind_Callback_OnTouchIconUrlReceivedEvent_Void*/: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer);
        case -2052382574/*CallbackKind.Kind_Callback_OnWindowNewEvent_Void*/: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer);
        case 406871767/*CallbackKind.Kind_Callback_Opt_Array_NavDestinationTransition_Void*/: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisDeserializer);
        case -543655128/*CallbackKind.Kind_Callback_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer);
        case -1777674145/*CallbackKind.Kind_Callback_Opt_Boolean_Void*/: return deserializeAndCallCallback_Opt_Boolean_Void(thisDeserializer);
        case -2035339519/*CallbackKind.Kind_Callback_Opt_NavigationAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer);
        case -233776232/*CallbackKind.Kind_Callback_Opt_Number_Void*/: return deserializeAndCallCallback_Opt_Number_Void(thisDeserializer);
        case -489468818/*CallbackKind.Kind_Callback_Opt_PanelMode_Void*/: return deserializeAndCallCallback_Opt_PanelMode_Void(thisDeserializer);
        case 1613641828/*CallbackKind.Kind_Callback_Opt_ResourceStr_Void*/: return deserializeAndCallCallback_Opt_ResourceStr_Void(thisDeserializer);
        case -756319131/*CallbackKind.Kind_Callback_Opt_StyledString_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer);
        case -143931627/*CallbackKind.Kind_Callback_Opt_TabContentAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer);
        case 1906972865/*CallbackKind.Kind_Callback_Opt_Union_Number_Resource_Void*/: return deserializeAndCallCallback_Opt_Union_Number_Resource_Void(thisDeserializer);
        case -2058966418/*CallbackKind.Kind_Callback_PlaybackInfo_Void*/: return deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer);
        case 721562324/*CallbackKind.Kind_Callback_Pointer_Void*/: return deserializeAndCallCallback_Pointer_Void(thisDeserializer);
        case 624053870/*CallbackKind.Kind_Callback_PopInfo_Void*/: return deserializeAndCallCallback_PopInfo_Void(thisDeserializer);
        case 463894668/*CallbackKind.Kind_Callback_PreDragStatus_Void*/: return deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer);
        case 1300890372/*CallbackKind.Kind_Callback_PreparedInfo_Void*/: return deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer);
        case 797834474/*CallbackKind.Kind_Callback_RangeUpdate*/: return deserializeAndCallCallback_RangeUpdate(thisDeserializer);
        case 934309126/*CallbackKind.Kind_Callback_RefreshStatus_Void*/: return deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer);
        case 188373904/*CallbackKind.Kind_Callback_ResourceStr_Void*/: return deserializeAndCallCallback_ResourceStr_Void(thisDeserializer);
        case 1465860515/*CallbackKind.Kind_Callback_RichEditorChangeValue_Boolean*/: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer);
        case 667698748/*CallbackKind.Kind_Callback_RichEditorDeleteValue_Boolean*/: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer);
        case -319221262/*CallbackKind.Kind_Callback_RichEditorInsertValue_Boolean*/: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer);
        case -62253375/*CallbackKind.Kind_Callback_RichEditorRange_Void*/: return deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer);
        case -963852514/*CallbackKind.Kind_Callback_RichEditorSelection_Void*/: return deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer);
        case 1980824326/*CallbackKind.Kind_Callback_RichEditorTextSpanResult_Void*/: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer);
        case 22609082/*CallbackKind.Kind_Callback_SheetDismiss_Void*/: return deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer);
        case -224451112/*CallbackKind.Kind_Callback_SheetType_Void*/: return deserializeAndCallCallback_SheetType_Void(thisDeserializer);
        case 1536231691/*CallbackKind.Kind_Callback_SpringBackAction_Void*/: return deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer);
        case -1872286415/*CallbackKind.Kind_Callback_StateStylesChange*/: return deserializeAndCallCallback_StateStylesChange(thisDeserializer);
        case -879490874/*CallbackKind.Kind_Callback_String_Number_Void*/: return deserializeAndCallCallback_String_Number_Void(thisDeserializer);
        case -716524508/*CallbackKind.Kind_Callback_String_Opt_Object_Void*/: return deserializeAndCallCallback_String_Opt_Object_Void(thisDeserializer);
        case -683652998/*CallbackKind.Kind_Callback_String_PasteEvent_Void*/: return deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer);
        case 814634522/*CallbackKind.Kind_Callback_String_Void*/: return deserializeAndCallCallback_String_Void(thisDeserializer);
        case 2116745428/*CallbackKind.Kind_Callback_StyledStringChangeValue_Boolean*/: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer);
        case -1198150682/*CallbackKind.Kind_Callback_StyledStringMarshallingValue_Void*/: return deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisDeserializer);
        case -301561698/*CallbackKind.Kind_Callback_SwipeActionState_Void*/: return deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer);
        case -416053361/*CallbackKind.Kind_Callback_SwiperContentTransitionProxy_Void*/: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer);
        case -1223938478/*CallbackKind.Kind_Callback_TabContentTransitionProxy_Void*/: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer);
        case 691098197/*CallbackKind.Kind_Callback_TerminationInfo_Void*/: return deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer);
        case 1290504509/*CallbackKind.Kind_Callback_TextPickerResult_Void*/: return deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer);
        case 811915501/*CallbackKind.Kind_Callback_TextRange_Void*/: return deserializeAndCallCallback_TextRange_Void(thisDeserializer);
        case 1557859605/*CallbackKind.Kind_Callback_TimePickerResult_Void*/: return deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer);
        case -274419246/*CallbackKind.Kind_Callback_TouchEvent_HitTestMode*/: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer);
        case -1676021850/*CallbackKind.Kind_Callback_TouchEvent_Void*/: return deserializeAndCallCallback_TouchEvent_Void(thisDeserializer);
        case 1943507619/*CallbackKind.Kind_Callback_TouchResult_Void*/: return deserializeAndCallCallback_TouchResult_Void(thisDeserializer);
        case 148489367/*CallbackKind.Kind_Callback_Tuple_Number_Number_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer);
        case -607365481/*CallbackKind.Kind_Callback_Tuple_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer);
        case -1352745727/*CallbackKind.Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void*/: return deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(thisDeserializer);
        case -1063506522/*CallbackKind.Kind_Callback_UIExtensionProxy_Void*/: return deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer);
        case -620935067/*CallbackKind.Kind_Callback_Union_CustomBuilder_DragItemInfo_Void*/: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer);
        case -1111620998/*CallbackKind.Kind_Callback_Union_Number_Array_Number_Void*/: return deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer);
        case -720435526/*CallbackKind.Kind_Callback_Union_String_Array_String_Void*/: return deserializeAndCallCallback_Union_String_Array_String_Void(thisDeserializer);
        case -1867723152/*CallbackKind.Kind_Callback_Void*/: return deserializeAndCallCallback_Void(thisDeserializer);
        case -1376223390/*CallbackKind.Kind_Callback_WebKeyboardOptions_Void*/: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer);
        case 831645046/*CallbackKind.Kind_Callback_WebResourceResponse_Void*/: return deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer);
        case 1436479104/*CallbackKind.Kind_Callback_WithThemeAttribute_Void*/: return deserializeAndCallCallback_WithThemeAttribute_Void(thisDeserializer);
        case -824029805/*CallbackKind.Kind_Callback_WrappedBuilder_Args_Void*/: return deserializeAndCallCallback_WrappedBuilder_Args_Void(thisDeserializer);
        case 1532328438/*CallbackKind.Kind_ContentDidScrollCallback*/: return deserializeAndCallContentDidScrollCallback(thisDeserializer);
        case -2146044511/*CallbackKind.Kind_ContentWillScrollCallback*/: return deserializeAndCallContentWillScrollCallback(thisDeserializer);
        case 260483890/*CallbackKind.Kind_Context_getGroupDir_Callback*/: return deserializeAndCallContext_getGroupDir_Callback(thisDeserializer);
        case 1766817632/*CallbackKind.Kind_CustomNodeBuilder*/: return deserializeAndCallCustomNodeBuilder(thisDeserializer);
        case -177744805/*CallbackKind.Kind_DrawCallback*/: return deserializeAndCallDrawCallback(thisDeserializer);
        case -1729563209/*CallbackKind.Kind_EditableTextOnChangeCallback*/: return deserializeAndCallEditableTextOnChangeCallback(thisDeserializer);
        case -1936519453/*CallbackKind.Kind_ErrorCallback*/: return deserializeAndCallErrorCallback(thisDeserializer);
        case -2119548940/*CallbackKind.Kind_GestureRecognizerJudgeBeginCallback*/: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer);
        case -2076995110/*CallbackKind.Kind_GetItemMainSizeByIndex*/: return deserializeAndCallGetItemMainSizeByIndex(thisDeserializer);
        case 1938653177/*CallbackKind.Kind_GridAttribute_onItemDragStart_event_type*/: return deserializeAndCallGridAttribute_onItemDragStart_event_type(thisDeserializer);
        case 68560477/*CallbackKind.Kind_HoverCallback*/: return deserializeAndCallHoverCallback(thisDeserializer);
        case -1180567691/*CallbackKind.Kind_ImageCompleteCallback*/: return deserializeAndCallImageCompleteCallback(thisDeserializer);
        case 1906248580/*CallbackKind.Kind_ImageErrorCallback*/: return deserializeAndCallImageErrorCallback(thisDeserializer);
        case 1502213270/*CallbackKind.Kind_InterceptionModeCallback*/: return deserializeAndCallInterceptionModeCallback(thisDeserializer);
        case 1852781814/*CallbackKind.Kind_InterceptionShowCallback*/: return deserializeAndCallInterceptionShowCallback(thisDeserializer);
        case -464108861/*CallbackKind.Kind_ListAttribute_onItemDragStart_event_type*/: return deserializeAndCallListAttribute_onItemDragStart_event_type(thisDeserializer);
        case -957598032/*CallbackKind.Kind_LocationButtonCallback*/: return deserializeAndCallLocationButtonCallback(thisDeserializer);
        case 810927048/*CallbackKind.Kind_MenuCallback*/: return deserializeAndCallMenuCallback(thisDeserializer);
        case -614475458/*CallbackKind.Kind_MenuOnAppearCallback*/: return deserializeAndCallMenuOnAppearCallback(thisDeserializer);
        case -1066063065/*CallbackKind.Kind_NavDestinationTransitionDelegate*/: return deserializeAndCallNavDestinationTransitionDelegate(thisDeserializer);
        case -588228933/*CallbackKind.Kind_NavExtender_OnUpdateStack*/: return deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer);
        case -1817630617/*CallbackKind.Kind_NodeContainer_AboutToResizeCallback*/: return deserializeAndCallNodeContainer_AboutToResizeCallback(thisDeserializer);
        case 1572284740/*CallbackKind.Kind_OnAdsBlockedCallback*/: return deserializeAndCallOnAdsBlockedCallback(thisDeserializer);
        case 726938390/*CallbackKind.Kind_OnAlphabetIndexerPopupSelectCallback*/: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer);
        case -1956514817/*CallbackKind.Kind_OnAlphabetIndexerRequestPopupDataCallback*/: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer);
        case -1189721220/*CallbackKind.Kind_OnAlphabetIndexerSelectCallback*/: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer);
        case -1198592337/*CallbackKind.Kind_OnCheckboxChangeCallback*/: return deserializeAndCallOnCheckboxChangeCallback(thisDeserializer);
        case -1053064240/*CallbackKind.Kind_OnCheckboxGroupChangeCallback*/: return deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer);
        case -419979106/*CallbackKind.Kind_OnContentScrollCallback*/: return deserializeAndCallOnContentScrollCallback(thisDeserializer);
        case 1788572278/*CallbackKind.Kind_OnContextMenuHideCallback*/: return deserializeAndCallOnContextMenuHideCallback(thisDeserializer);
        case 1648184341/*CallbackKind.Kind_OnDidChangeCallback*/: return deserializeAndCallOnDidChangeCallback(thisDeserializer);
        case 1451593190/*CallbackKind.Kind_OnDragEventCallback*/: return deserializeAndCallOnDragEventCallback(thisDeserializer);
        case 767275770/*CallbackKind.Kind_OnFirstMeaningfulPaintCallback*/: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer);
        case 2050387049/*CallbackKind.Kind_OnFoldStatusChangeCallback*/: return deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer);
        case 81230317/*CallbackKind.Kind_OnFullScreenEnterCallback*/: return deserializeAndCallOnFullScreenEnterCallback(thisDeserializer);
        case -2025767812/*CallbackKind.Kind_OnHoverCallback*/: return deserializeAndCallOnHoverCallback(thisDeserializer);
        case 9040430/*CallbackKind.Kind_OnHoverStatusChangeCallback*/: return deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer);
        case -1377876844/*CallbackKind.Kind_OnIntelligentTrackingPreventionCallback*/: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer);
        case 1390640532/*CallbackKind.Kind_OnLargestContentfulPaintCallback*/: return deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer);
        case -968773856/*CallbackKind.Kind_OnLinearIndicatorChangeCallback*/: return deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer);
        case -1200281222/*CallbackKind.Kind_OnMoveHandler*/: return deserializeAndCallOnMoveHandler(thisDeserializer);
        case -1641338704/*CallbackKind.Kind_OnNativeEmbedVisibilityChangeCallback*/: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer);
        case -823037763/*CallbackKind.Kind_OnNativeLoadCallback*/: return deserializeAndCallOnNativeLoadCallback(thisDeserializer);
        case -398722176/*CallbackKind.Kind_OnNavigationEntryCommittedCallback*/: return deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer);
        case 865258467/*CallbackKind.Kind_OnOverrideUrlLoadingCallback*/: return deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer);
        case 1738363337/*CallbackKind.Kind_OnPasteCallback*/: return deserializeAndCallOnPasteCallback(thisDeserializer);
        case 511412333/*CallbackKind.Kind_OnRadioChangeCallback*/: return deserializeAndCallOnRadioChangeCallback(thisDeserializer);
        case -551895045/*CallbackKind.Kind_OnRatingChangeCallback*/: return deserializeAndCallOnRatingChangeCallback(thisDeserializer);
        case 47282303/*CallbackKind.Kind_OnRenderProcessNotRespondingCallback*/: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer);
        case 1334389194/*CallbackKind.Kind_OnRenderProcessRespondingCallback*/: return deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer);
        case -1099824577/*CallbackKind.Kind_OnSafeBrowsingCheckResultCallback*/: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer);
        case -160015401/*CallbackKind.Kind_OnScrollCallback*/: return deserializeAndCallOnScrollCallback(thisDeserializer);
        case -150015401/*CallbackKind.Kind_OnWillScrollCallback*/: return deserializeAndCallOnWillScrollCallback(thisDeserializer);
        case -1259214476/*CallbackKind.Kind_OnScrollEdgeCallback*/: return deserializeAndCallOnScrollEdgeCallback(thisDeserializer);
        case -2133791987/*CallbackKind.Kind_OnScrollFrameBeginCallback*/: return deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer);
        case 625641334/*CallbackKind.Kind_OnScrollVisibleContentChangeCallback*/: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer);
        case -1486869198/*CallbackKind.Kind_OnSelectCallback*/: return deserializeAndCallOnSelectCallback(thisDeserializer);
        case -399603614/*CallbackKind.Kind_OnSslErrorEventCallback*/: return deserializeAndCallOnSslErrorEventCallback(thisDeserializer);
        case -1961646162/*CallbackKind.Kind_OnSubmitCallback*/: return deserializeAndCallOnSubmitCallback(thisDeserializer);
        case -143686583/*CallbackKind.Kind_OnSwiperAnimationEndCallback*/: return deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer);
        case 876602502/*CallbackKind.Kind_OnSwiperAnimationStartCallback*/: return deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer);
        case 606029871/*CallbackKind.Kind_OnSwiperGestureSwipeCallback*/: return deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer);
        case 1942856551/*CallbackKind.Kind_OnTabsAnimationEndCallback*/: return deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer);
        case -147408344/*CallbackKind.Kind_OnTabsAnimationStartCallback*/: return deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer);
        case -349727249/*CallbackKind.Kind_OnTabsContentWillChangeCallback*/: return deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer);
        case 253696833/*CallbackKind.Kind_OnTabsGestureSwipeCallback*/: return deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer);
        case -1902343417/*CallbackKind.Kind_OnTextPickerChangeCallback*/: return deserializeAndCallOnTextPickerChangeCallback(thisDeserializer);
        case 695228737/*CallbackKind.Kind_OnTextSelectionChangeCallback*/: return deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer);
        case 994429103/*CallbackKind.Kind_OnTimePickerChangeCallback*/: return deserializeAndCallOnTimePickerChangeCallback(thisDeserializer);
        case 1847083191/*CallbackKind.Kind_OnViewportFitChangedCallback*/: return deserializeAndCallOnViewportFitChangedCallback(thisDeserializer);
        case 1627123591/*CallbackKind.Kind_PageTransitionCallback*/: return deserializeAndCallPageTransitionCallback(thisDeserializer);
        case 1501373374/*CallbackKind.Kind_PasteButtonCallback*/: return deserializeAndCallPasteButtonCallback(thisDeserializer);
        case 919057028/*CallbackKind.Kind_PasteEventCallback*/: return deserializeAndCallPasteEventCallback(thisDeserializer);
        case -1992671958/*CallbackKind.Kind_PluginErrorCallback*/: return deserializeAndCallPluginErrorCallback(thisDeserializer);
        case -1444325632/*CallbackKind.Kind_PopupStateChangeCallback*/: return deserializeAndCallPopupStateChangeCallback(thisDeserializer);
        case 2053798608/*CallbackKind.Kind_ReceiveCallback*/: return deserializeAndCallReceiveCallback(thisDeserializer);
        case -1213708823/*CallbackKind.Kind_RestrictedWorker_onerror_Callback*/: return deserializeAndCallRestrictedWorker_onerror_Callback(thisDeserializer);
        case -2095497263/*CallbackKind.Kind_RestrictedWorker_onexit_Callback*/: return deserializeAndCallRestrictedWorker_onexit_Callback(thisDeserializer);
        case 1614214490/*CallbackKind.Kind_RestrictedWorker_onmessage_Callback*/: return deserializeAndCallRestrictedWorker_onmessage_Callback(thisDeserializer);
        case 1110529154/*CallbackKind.Kind_ReuseIdCallback*/: return deserializeAndCallReuseIdCallback(thisDeserializer);
        case -1634474996/*CallbackKind.Kind_SaveButtonCallback*/: return deserializeAndCallSaveButtonCallback(thisDeserializer);
        case -1265626662/*CallbackKind.Kind_ScrollOnScrollCallback*/: return deserializeAndCallScrollOnScrollCallback(thisDeserializer);
        case -721521596/*CallbackKind.Kind_ScrollOnWillScrollCallback*/: return deserializeAndCallScrollOnWillScrollCallback(thisDeserializer);
        case 1717691617/*CallbackKind.Kind_SearchSubmitCallback*/: return deserializeAndCallSearchSubmitCallback(thisDeserializer);
        case 2049289694/*CallbackKind.Kind_SearchValueCallback*/: return deserializeAndCallSearchValueCallback(thisDeserializer);
        case -1480175598/*CallbackKind.Kind_SelectedCallback*/: return deserializeAndCallSelectedCallback(thisDeserializer);
        case -250780276/*CallbackKind.Kind_ShouldBuiltInRecognizerParallelWithCallback*/: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer);
        case -1716637992/*CallbackKind.Kind_SizeChangeCallback*/: return deserializeAndCallSizeChangeCallback(thisDeserializer);
        case 711649376/*CallbackKind.Kind_SliderTriggerChangeCallback*/: return deserializeAndCallSliderTriggerChangeCallback(thisDeserializer);
        case 2068688176/*CallbackKind.Kind_StepperIndexCallback*/: return deserializeAndCallStepperIndexCallback(thisDeserializer);
        case 1095217433/*CallbackKind.Kind_StyledStringMarshallCallback*/: return deserializeAndCallStyledStringMarshallCallback(thisDeserializer);
        case 1359717794/*CallbackKind.Kind_StyledStringUnmarshallCallback*/: return deserializeAndCallStyledStringUnmarshallCallback(thisDeserializer);
        case -712186065/*CallbackKind.Kind_SubmitCallback*/: return deserializeAndCallSubmitCallback(thisDeserializer);
        case 221706282/*CallbackKind.Kind_TabsCustomContentTransitionCallback*/: return deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer);
        case -401980571/*CallbackKind.Kind_TextAreaSubmitCallback*/: return deserializeAndCallTextAreaSubmitCallback(thisDeserializer);
        case 18061455/*CallbackKind.Kind_TextFieldValueCallback*/: return deserializeAndCallTextFieldValueCallback(thisDeserializer);
        case -202014218/*CallbackKind.Kind_TextPickerEnterSelectedAreaCallback*/: return deserializeAndCallTextPickerEnterSelectedAreaCallback(thisDeserializer);
        case -1928298699/*CallbackKind.Kind_TextPickerScrollStopCallback*/: return deserializeAndCallTextPickerScrollStopCallback(thisDeserializer);
        case 2057659801/*CallbackKind.Kind_TextTimerAttribute_onTimer_event_type*/: return deserializeAndCallTextTimerAttribute_onTimer_event_type(thisDeserializer);
        case -1878458553/*CallbackKind.Kind_TransitionFinishCallback*/: return deserializeAndCallTransitionFinishCallback(thisDeserializer);
        case 1044833488/*CallbackKind.Kind_Type_NavigationAttribute_customNavContentTransition_delegate*/: return deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(thisDeserializer);
        case -1078223620/*CallbackKind.Kind_Type_TextPickerAttribute_onChange_callback*/: return deserializeAndCallType_TextPickerAttribute_onChange_callback(thisDeserializer);
        case 1962174977/*CallbackKind.Kind_Type_WebAttribute_onFileSelectorShow_callback*/: return deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(thisDeserializer);
        case -985284966/*CallbackKind.Kind_Type_WebAttribute_onUrlLoadIntercept_callback*/: return deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(thisDeserializer);
        case 541663396/*CallbackKind.Kind_VisibleAreaChangeCallback*/: return deserializeAndCallVisibleAreaChangeCallback(thisDeserializer);
        case -2038961969/*CallbackKind.Kind_VoidCallback*/: return deserializeAndCallVoidCallback(thisDeserializer);
        case -1829763354/*CallbackKind.Kind_WebKeyboardCallback*/: return deserializeAndCallWebKeyboardCallback(thisDeserializer);
        case 219587748/*CallbackKind.Kind_WithThemeInterface*/: return deserializeAndCallWithThemeInterface(thisDeserializer);
        case -1736208400/*CallbackKind.Kind_Callback_String_SurfaceRect_Void*/: return deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer);
    }
    console.log("Unknown callback kind")
}

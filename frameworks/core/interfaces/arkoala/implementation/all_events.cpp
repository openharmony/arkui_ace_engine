/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedEvents {
enum PeerEventKind {
    KindAbilityComponent_onConnect = 0,
    KindAbilityComponent_onDisconnect = 1,
    KindAlphabetIndexer_onSelected = 2,
    KindAlphabetIndexer_onSelect = 3,
    KindAlphabetIndexer_onRequestPopupData = 4,
    KindAlphabetIndexer_onPopupSelect = 5,
    KindAnimator_onStart = 6,
    KindAnimator_onPause = 7,
    KindAnimator_onRepeat = 8,
    KindAnimator_onCancel = 9,
    KindAnimator_onFinish = 10,
    KindAnimator_onFrame = 11,
    KindCalendar_onSelectChange = 12,
    KindCalendar_onRequestData = 13,
    KindCalendarPicker_onChange = 14,
    KindCanvas_onReady = 15,
    KindCheckbox_onChange = 16,
    KindCheckboxGroup_onChange = 17,
    KindCommonMethod_onChildTouchTest = 18,
    KindCommonMethod_onClick = 19,
    KindCommonMethod_onHover = 20,
    KindCommonMethod_onAccessibilityHover = 21,
    KindCommonMethod_onMouse = 22,
    KindCommonMethod_onTouch = 23,
    KindCommonMethod_onKeyEvent = 24,
    KindCommonMethod_onKeyPreIme = 25,
    KindCommonMethod_onFocus = 26,
    KindCommonMethod_onBlur = 27,
    KindCommonMethod_onAppear = 28,
    KindCommonMethod_onDisAppear = 29,
    KindCommonMethod_onAttach = 30,
    KindCommonMethod_onDetach = 31,
    KindCommonMethod_onAreaChange = 32,
    KindCommonMethod_onDragStart = 33,
    KindCommonMethod_onDragEnter = 34,
    KindCommonMethod_onDragMove = 35,
    KindCommonMethod_onDragLeave = 36,
    KindCommonMethod_onDrop = 37,
    KindCommonMethod_onDragEnd = 38,
    KindCommonMethod_onPreDrag = 39,
    KindCommonMethod_onGestureJudgeBegin = 40,
    KindCommonMethod_onGestureRecognizerJudgeBegin = 41,
    KindCommonMethod_shouldBuiltInRecognizerParallelWith = 42,
    KindCommonMethod_onTouchIntercept = 43,
    KindCommonMethod_onSizeChange = 44,
    KindCommonMethod_onVisibleAreaChange = 45,
    KindCommonMethod_keyboardShortcut = 46,
    KindScrollableCommonMethod_onScroll = 47,
    KindScrollableCommonMethod_onDidScroll = 48,
    KindScrollableCommonMethod_onReachStart = 49,
    KindScrollableCommonMethod_onReachEnd = 50,
    KindScrollableCommonMethod_onScrollStart = 51,
    KindScrollableCommonMethod_onScrollStop = 52,
    KindCounter_onInc = 53,
    KindCounter_onDec = 54,
    KindDatePicker_onChange = 55,
    KindDatePicker_onDateChange = 56,
    KindFolderStack_onFolderStateChange = 57,
    KindFolderStack_onHoverStatusChange = 58,
    KindFormComponent_onAcquired = 59,
    KindFormComponent_onError = 60,
    KindFormComponent_onRouter = 61,
    KindFormComponent_onUninstall = 62,
    KindFormComponent_onLoad = 63,
    KindGrid_onScrollBarUpdate = 64,
    KindGrid_onScrollIndex = 65,
    KindGrid_onItemDragStart = 66,
    KindGrid_onItemDragEnter = 67,
    KindGrid_onItemDragMove = 68,
    KindGrid_onItemDragLeave = 69,
    KindGrid_onItemDrop = 70,
    KindGrid_onScroll = 71,
    KindGrid_onReachStart = 72,
    KindGrid_onReachEnd = 73,
    KindGrid_onScrollStart = 74,
    KindGrid_onScrollStop = 75,
    KindGrid_onScrollFrameBegin = 76,
    KindGridItem_onSelect = 77,
    KindGridRow_onBreakpointChange = 78,
    KindImage_onComplete = 79,
    KindImage_onError = 80,
    KindImage_onFinish = 81,
    KindImageAnimator_onStart = 82,
    KindImageAnimator_onPause = 83,
    KindImageAnimator_onRepeat = 84,
    KindImageAnimator_onCancel = 85,
    KindImageAnimator_onFinish = 86,
    KindImageSpan_onComplete = 87,
    KindImageSpan_onError = 88,
    KindList_onScroll = 89,
    KindList_onScrollIndex = 90,
    KindList_onScrollVisibleContentChange = 91,
    KindList_onReachStart = 92,
    KindList_onReachEnd = 93,
    KindList_onScrollStart = 94,
    KindList_onScrollStop = 95,
    KindList_onItemDelete = 96,
    KindList_onItemMove = 97,
    KindList_onItemDragStart = 98,
    KindList_onItemDragEnter = 99,
    KindList_onItemDragMove = 100,
    KindList_onItemDragLeave = 101,
    KindList_onItemDrop = 102,
    KindList_onScrollFrameBegin = 103,
    KindListItem_onSelect = 104,
    KindLocationButton_onClick = 105,
    KindMarquee_onStart = 106,
    KindMarquee_onBounce = 107,
    KindMarquee_onFinish = 108,
    KindMenuItem_onChange = 109,
    KindNavDestination_onShown = 110,
    KindNavDestination_onHidden = 111,
    KindNavDestination_onBackPressed = 112,
    KindNavDestination_onWillAppear = 113,
    KindNavDestination_onWillDisappear = 114,
    KindNavDestination_onWillShow = 115,
    KindNavDestination_onWillHide = 116,
    KindNavRouter_onStateChange = 117,
    KindNavigation_onTitleModeChange = 118,
    KindNavigation_onNavBarStateChange = 119,
    KindNavigation_onNavigationModeChange = 120,
    KindNavigation_navDestination = 121,
    KindNavigation_customNavContentTransition = 122,
    KindPanel_onChange = 123,
    KindPanel_onHeightChange = 124,
    KindPasteButton_onClick = 125,
    KindPatternLock_onPatternComplete = 126,
    KindPluginComponent_onComplete = 127,
    KindPluginComponent_onError = 128,
    KindRadio_onChange = 129,
    KindRating_onChange = 130,
    KindRefresh_onStateChange = 131,
    KindRefresh_onRefreshing = 132,
    KindRefresh_onOffsetChange = 133,
    KindRichEditor_onReady = 134,
    KindRichEditor_onSelect = 135,
    KindRichEditor_onSelectionChange = 136,
    KindRichEditor_aboutToIMEInput = 137,
    KindRichEditor_onIMEInputComplete = 138,
    KindRichEditor_onDidIMEInput = 139,
    KindRichEditor_aboutToDelete = 140,
    KindRichEditor_onDeleteComplete = 141,
    KindRichEditor_onPaste = 142,
    KindRichEditor_onEditingChange = 143,
    KindRichEditor_onSubmit = 144,
    KindRichEditor_onWillChange = 145,
    KindRichEditor_onDidChange = 146,
    KindRichEditor_onCut = 147,
    KindRichEditor_onCopy = 148,
    KindRichText_onStart = 149,
    KindRichText_onComplete = 150,
    KindSaveButton_onClick = 151,
    KindScroll_onScroll = 152,
    KindScroll_onDidScroll = 153,
    KindScroll_onScrollEdge = 154,
    KindScroll_onScrollStart = 155,
    KindScroll_onScrollEnd = 156,
    KindScroll_onScrollStop = 157,
    KindScroll_onScrollFrameBegin = 158,
    KindSearch_onEditChange = 159,
    KindSearch_onSubmit = 160,
    KindSearch_onChange = 161,
    KindSearch_onTextSelectionChange = 162,
    KindSearch_onContentScroll = 163,
    KindSearch_onCopy = 164,
    KindSearch_onCut = 165,
    KindSearch_onPaste = 166,
    KindSearch_onWillInsert = 167,
    KindSearch_onDidInsert = 168,
    KindSearch_onWillDelete = 169,
    KindSearch_onDidDelete = 170,
    KindSearch_inputFilter = 171,
    KindSelect_onSelect = 172,
    KindSlider_onChange = 173,
    KindStepper_onFinish = 174,
    KindStepper_onSkip = 175,
    KindStepper_onChange = 176,
    KindStepper_onNext = 177,
    KindStepper_onPrevious = 178,
    KindSwiper_onChange = 179,
    KindSwiper_onAnimationStart = 180,
    KindSwiper_onAnimationEnd = 181,
    KindSwiper_onGestureSwipe = 182,
    KindSwiper_onContentDidScroll = 183,
    KindTabs_onChange = 184,
    KindTabs_onTabBarClick = 185,
    KindTabs_onAnimationStart = 186,
    KindTabs_onAnimationEnd = 187,
    KindTabs_onGestureSwipe = 188,
    KindTabs_customContentTransition = 189,
    KindTabs_onContentWillChange = 190,
    KindTabContent_onWillShow = 191,
    KindTabContent_onWillHide = 192,
    KindText_onCopy = 193,
    KindText_onTextSelectionChange = 194,
    KindTextArea_onSubmit = 195,
    KindTextArea_onChange = 196,
    KindTextArea_onTextSelectionChange = 197,
    KindTextArea_onContentScroll = 198,
    KindTextArea_onEditChange = 199,
    KindTextArea_onCopy = 200,
    KindTextArea_onCut = 201,
    KindTextArea_onPaste = 202,
    KindTextArea_onWillInsert = 203,
    KindTextArea_onDidInsert = 204,
    KindTextArea_onWillDelete = 205,
    KindTextArea_onDidDelete = 206,
    KindTextArea_inputFilter = 207,
    KindTextClock_onDateChange = 208,
    KindTextInput_onEditChanged = 209,
    KindTextInput_onEditChange = 210,
    KindTextInput_onSubmit = 211,
    KindTextInput_onChange = 212,
    KindTextInput_onTextSelectionChange = 213,
    KindTextInput_onContentScroll = 214,
    KindTextInput_onCopy = 215,
    KindTextInput_onCut = 216,
    KindTextInput_onPaste = 217,
    KindTextInput_onSecurityStateChange = 218,
    KindTextInput_onWillInsert = 219,
    KindTextInput_onDidInsert = 220,
    KindTextInput_onWillDelete = 221,
    KindTextInput_onDidDelete = 222,
    KindTextInput_inputFilter = 223,
    KindTextPicker_onAccept = 224,
    KindTextPicker_onCancel = 225,
    KindTextPicker_onChange = 226,
    KindTextTimer_onTimer = 227,
    KindTimePicker_onChange = 228,
    KindToggle_onChange = 229,
    KindVideo_onStart = 230,
    KindVideo_onPause = 231,
    KindVideo_onFinish = 232,
    KindVideo_onFullscreenChange = 233,
    KindVideo_onPrepared = 234,
    KindVideo_onSeeking = 235,
    KindVideo_onSeeked = 236,
    KindVideo_onUpdate = 237,
    KindVideo_onError = 238,
    KindVideo_onStop = 239,
    KindWeb_onPageEnd = 240,
    KindWeb_onPageBegin = 241,
    KindWeb_onProgressChange = 242,
    KindWeb_onTitleReceive = 243,
    KindWeb_onGeolocationHide = 244,
    KindWeb_onGeolocationShow = 245,
    KindWeb_onRequestSelected = 246,
    KindWeb_onAlert = 247,
    KindWeb_onBeforeUnload = 248,
    KindWeb_onConfirm = 249,
    KindWeb_onPrompt = 250,
    KindWeb_onConsole = 251,
    KindWeb_onErrorReceive = 252,
    KindWeb_onHttpErrorReceive = 253,
    KindWeb_onDownloadStart = 254,
    KindWeb_onRefreshAccessedHistory = 255,
    KindWeb_onUrlLoadIntercept = 256,
    KindWeb_onSslErrorReceive = 257,
    KindWeb_onRenderExited0 = 258,
    KindWeb_onShowFileSelector = 259,
    KindWeb_onRenderExited1 = 260,
    KindWeb_onFileSelectorShow = 261,
    KindWeb_onResourceLoad = 262,
    KindWeb_onFullScreenExit = 263,
    KindWeb_onFullScreenEnter = 264,
    KindWeb_onScaleChange = 265,
    KindWeb_onHttpAuthRequest = 266,
    KindWeb_onInterceptRequest = 267,
    KindWeb_onPermissionRequest = 268,
    KindWeb_onScreenCaptureRequest = 269,
    KindWeb_onContextMenuShow = 270,
    KindWeb_onContextMenuHide = 271,
    KindWeb_onSearchResultReceive = 272,
    KindWeb_onScroll = 273,
    KindWeb_onSslErrorEventReceive = 274,
    KindWeb_onSslErrorEvent = 275,
    KindWeb_onClientAuthenticationRequest = 276,
    KindWeb_onWindowNew = 277,
    KindWeb_onWindowExit = 278,
    KindWeb_onInterceptKeyEvent = 279,
    KindWeb_onTouchIconUrlReceived = 280,
    KindWeb_onFaviconReceived = 281,
    KindWeb_onPageVisible = 282,
    KindWeb_onDataResubmitted = 283,
    KindWeb_onAudioStateChanged = 284,
    KindWeb_onFirstContentfulPaint = 285,
    KindWeb_onFirstMeaningfulPaint = 286,
    KindWeb_onLargestContentfulPaint = 287,
    KindWeb_onLoadIntercept = 288,
    KindWeb_onControllerAttached = 289,
    KindWeb_onOverScroll = 290,
    KindWeb_onSafeBrowsingCheckResult = 291,
    KindWeb_onNavigationEntryCommitted = 292,
    KindWeb_onIntelligentTrackingPreventionResult = 293,
    KindWeb_onNativeEmbedLifecycleChange = 294,
    KindWeb_onNativeEmbedVisibilityChange = 295,
    KindWeb_onNativeEmbedGestureEvent = 296,
    KindWeb_onOverrideUrlLoading = 297,
    KindWeb_onRenderProcessNotResponding = 298,
    KindWeb_onRenderProcessResponding = 299,
    KindWeb_onViewportFitChanged = 300,
    KindWeb_onInterceptKeyboardAttach = 301,
    KindWeb_onAdsBlocked = 302,
    KindXComponent_onLoad = 303,
    KindXComponent_onDestroy = 304,
    KindSideBarContainer_onChange = 305,
    KindWaterFlow_onReachStart = 306,
    KindWaterFlow_onReachEnd = 307,
    KindWaterFlow_onScrollFrameBegin = 308,
    KindWaterFlow_onScrollIndex = 309,
    KindUIExtensionComponent_onTerminated = 310,
};

namespace AbilityComponent {
void onConnectImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAbilityComponent_onConnect);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onDisconnectImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAbilityComponent_onDisconnect);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace AlphabetIndexer {
void onSelectedImpl(Ark_Int32 nodeId,
                    const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onSelected);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onSelectImpl(Ark_Int32 nodeId,
                  const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onRequestPopupDataImpl(Ark_Int32 nodeId,
                            const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onRequestPopupData);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onPopupSelectImpl(Ark_Int32 nodeId,
                       const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onPopupSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
}
namespace Animator {
void onStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onPauseImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onPause);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onRepeatImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onRepeat);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onCancelImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onCancel);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFrameImpl(Ark_Int32 nodeId,
                 const Ark_Number value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindAnimator_onFrame);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    sendEvent(&_eventBuffer);
}
}
namespace Calendar {
void onSelectChangeImpl(Ark_Int32 nodeId,
                        const Ark_CalendarSelectedDate event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCalendar_onSelectChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCalendarSelectedDate(event);
    sendEvent(&_eventBuffer);
}
void onRequestDataImpl(Ark_Int32 nodeId,
                       const Ark_CalendarRequestedData event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCalendar_onRequestData);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCalendarRequestedData(event);
    sendEvent(&_eventBuffer);
}
}
namespace CalendarPicker {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_CustomObject value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCalendarPicker_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCustomObject("Date", value);
    sendEvent(&_eventBuffer);
}
}
namespace Canvas {
void onReadyImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCanvas_onReady);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace Checkbox {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Boolean value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCheckbox_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(value);
    sendEvent(&_eventBuffer);
}
}
namespace CheckboxGroup {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_CheckboxGroupResult value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCheckboxGroup_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCheckboxGroupResult(value);
    sendEvent(&_eventBuffer);
}
}
namespace CommonMethod {
void onChildTouchTestImpl(Ark_Int32 nodeId,
                          const Array_TouchTestInfo value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onChildTouchTest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt8(runtimeType(value));
    _eventBufferSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const auto value_element = value.array[i];
        _eventBufferSerializer.writeTouchTestInfo(value_element);
    }
    sendEvent(&_eventBuffer);
}
void onClickImpl(Ark_Int32 nodeId,
                 const Ark_ClickEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onClick);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeClickEvent(value);
    sendEvent(&_eventBuffer);
}
void onHoverImpl(Ark_Int32 nodeId,
                 const Ark_Boolean isHover,
                 const Ark_HoverEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onHover);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isHover);
    _eventBufferSerializer.writeHoverEvent(event);
    sendEvent(&_eventBuffer);
}
void onAccessibilityHoverImpl(Ark_Int32 nodeId,
                              const Ark_Boolean isHover,
                              const Ark_AccessibilityHoverEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onAccessibilityHover);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isHover);
    _eventBufferSerializer.writeAccessibilityHoverEvent(event);
    sendEvent(&_eventBuffer);
}
void onMouseImpl(Ark_Int32 nodeId,
                 const Ark_MouseEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onMouse);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeMouseEvent(event);
    sendEvent(&_eventBuffer);
}
void onTouchImpl(Ark_Int32 nodeId,
                 const Ark_TouchEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onTouch);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTouchEvent(event);
    sendEvent(&_eventBuffer);
}
void onKeyEventImpl(Ark_Int32 nodeId,
                    const Ark_KeyEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onKeyEvent);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeKeyEvent(event);
    sendEvent(&_eventBuffer);
}
void onKeyPreImeImpl(Ark_Int32 nodeId,
                     const Ark_KeyEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onKeyPreIme);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeKeyEvent(value);
    sendEvent(&_eventBuffer);
}
void onFocusImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onFocus);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onBlurImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onBlur);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onAppearImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onAppear);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onDisAppearImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDisAppear);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onAttachImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onAttach);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onDetachImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDetach);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onAreaChangeImpl(Ark_Int32 nodeId,
                      const Ark_Area oldValue,
                      const Ark_Area newValue)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onAreaChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeArea(oldValue);
    _eventBufferSerializer.writeArea(newValue);
    sendEvent(&_eventBuffer);
}
void onDragStartImpl(Ark_Int32 nodeId,
                     const Ark_DragEvent event,
                     const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDragStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onDragEnterImpl(Ark_Int32 nodeId,
                     const Ark_DragEvent event,
                     const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDragEnter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onDragMoveImpl(Ark_Int32 nodeId,
                    const Ark_DragEvent event,
                    const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDragMove);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onDragLeaveImpl(Ark_Int32 nodeId,
                     const Ark_DragEvent event,
                     const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDragLeave);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onDropImpl(Ark_Int32 nodeId,
                const Ark_DragEvent event,
                const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDrop);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onDragEndImpl(Ark_Int32 nodeId,
                   const Ark_DragEvent event,
                   const Opt_String extraParams)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onDragEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = ARK_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    _eventBufferSerializer.writeInt8(extraParams_type);
    if ((ARK_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        _eventBufferSerializer.writeString(extraParams_value);
    }
    sendEvent(&_eventBuffer);
}
void onPreDragImpl(Ark_Int32 nodeId,
                   const Ark_PreDragStatus value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onPreDrag);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(value);
    sendEvent(&_eventBuffer);
}
void onGestureJudgeBeginImpl(Ark_Int32 nodeId,
                             const Ark_GestureInfo gestureInfo,
                             const Ark_BaseGestureEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onGestureJudgeBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeGestureInfo(gestureInfo);
    _eventBufferSerializer.writeBaseGestureEvent(event);
    sendEvent(&_eventBuffer);
}
void onGestureRecognizerJudgeBeginImpl(Ark_Int32 nodeId,
                                       const Ark_BaseGestureEvent event,
                                       const Ark_Materialized current,
                                       const Array_GestureRecognizer recognizers)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onGestureRecognizerJudgeBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBaseGestureEvent(event);
    _eventBufferSerializer.writeMaterialized(current);
    _eventBufferSerializer.writeInt8(runtimeType(recognizers));
    _eventBufferSerializer.writeInt32(recognizers.length);
    for (int i = 0; i < recognizers.length; i++) {
        const auto recognizers_element = recognizers.array[i];
        _eventBufferSerializer.writeMaterialized(recognizers_element);
    }
    sendEvent(&_eventBuffer);
}
void shouldBuiltInRecognizerParallelWithImpl(Ark_Int32 nodeId,
                                             const Ark_Materialized current,
                                             const Array_GestureRecognizer others)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_shouldBuiltInRecognizerParallelWith);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeMaterialized(current);
    _eventBufferSerializer.writeInt8(runtimeType(others));
    _eventBufferSerializer.writeInt32(others.length);
    for (int i = 0; i < others.length; i++) {
        const auto others_element = others.array[i];
        _eventBufferSerializer.writeMaterialized(others_element);
    }
    sendEvent(&_eventBuffer);
}
void onTouchInterceptImpl(Ark_Int32 nodeId,
                          const Ark_TouchEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onTouchIntercept);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTouchEvent(value);
    sendEvent(&_eventBuffer);
}
void onSizeChangeImpl(Ark_Int32 nodeId,
                      const Ark_SizeOptions oldValue,
                      const Ark_SizeOptions newValue)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onSizeChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeSizeOptions(oldValue);
    _eventBufferSerializer.writeSizeOptions(newValue);
    sendEvent(&_eventBuffer);
}
void onVisibleAreaChangeImpl(Ark_Int32 nodeId,
                             const Ark_Boolean isExpanding,
                             const Ark_Number currentRatio)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_onVisibleAreaChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isExpanding);
    _eventBufferSerializer.writeNumber(currentRatio);
    sendEvent(&_eventBuffer);
}
void keyboardShortcutImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCommonMethod_keyboardShortcut);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace ScrollableCommonMethod {
void onScrollImpl(Ark_Int32 nodeId,
                  const Ark_Number scrollOffset,
                  const Ark_ScrollState scrollState)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(scrollOffset);
    _eventBufferSerializer.writeInt32(scrollState);
    sendEvent(&_eventBuffer);
}
void onDidScrollImpl(Ark_Int32 nodeId,
                     const Ark_Number scrollOffset,
                     const Ark_ScrollState scrollState)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onDidScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(scrollOffset);
    _eventBufferSerializer.writeInt32(scrollState);
    sendEvent(&_eventBuffer);
}
void onReachStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onReachStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onReachEndImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onReachEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScrollStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStopImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScrollStop);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace Counter {
void onIncImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCounter_onInc);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onDecImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindCounter_onDec);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace DatePicker {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_DatePickerResult value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindDatePicker_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDatePickerResult(value);
    sendEvent(&_eventBuffer);
}
void onDateChangeImpl(Ark_Int32 nodeId,
                      const Ark_CustomObject value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindDatePicker_onDateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCustomObject("Date", value);
    sendEvent(&_eventBuffer);
}
}
namespace FolderStack {
void onFolderStateChangeImpl(Ark_Int32 nodeId,
                             const Ark_OnFoldStatusChangeInfo event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFolderStack_onFolderStateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnFoldStatusChangeInfo(event);
    sendEvent(&_eventBuffer);
}
void onHoverStatusChangeImpl(Ark_Int32 nodeId,
                             const Ark_HoverEventParam param)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFolderStack_onHoverStatusChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeHoverEventParam(param);
    sendEvent(&_eventBuffer);
}
}
namespace FormComponent {
void onAcquiredImpl(Ark_Int32 nodeId,
                    const Ark_FormCallbackInfo value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFormComponent_onAcquired);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeFormCallbackInfo(value);
    sendEvent(&_eventBuffer);
}
void onErrorImpl(Ark_Int32 nodeId,
                 const Ark_Literal_Number_errcode_String_msg info)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFormComponent_onError);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto info_errcode = info.errcode;
    _eventBufferSerializer.writeNumber(info_errcode);
    const auto info_msg = info.msg;
    _eventBufferSerializer.writeString(info_msg);
    sendEvent(&_eventBuffer);
}
void onRouterImpl(Ark_Int32 nodeId,
                  const Ark_CustomObject info)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFormComponent_onRouter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCustomObject("Any", info);
    sendEvent(&_eventBuffer);
}
void onUninstallImpl(Ark_Int32 nodeId,
                     const Ark_FormCallbackInfo value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFormComponent_onUninstall);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeFormCallbackInfo(value);
    sendEvent(&_eventBuffer);
}
void onLoadImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindFormComponent_onLoad);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace Grid {
void onScrollBarUpdateImpl(Ark_Int32 nodeId,
                           const Ark_Number index,
                           const Ark_Number offset)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScrollBarUpdate);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(offset);
    sendEvent(&_eventBuffer);
}
void onScrollIndexImpl(Ark_Int32 nodeId,
                       const Ark_Number first,
                       const Ark_Number last)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScrollIndex);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(first);
    _eventBufferSerializer.writeNumber(last);
    sendEvent(&_eventBuffer);
}
void onItemDragStartImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event,
                         const Ark_Number itemIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onItemDragStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    sendEvent(&_eventBuffer);
}
void onItemDragEnterImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onItemDragEnter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    sendEvent(&_eventBuffer);
}
void onItemDragMoveImpl(Ark_Int32 nodeId,
                        const Ark_ItemDragInfo event,
                        const Ark_Number itemIndex,
                        const Ark_Number insertIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onItemDragMove);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    _eventBufferSerializer.writeNumber(insertIndex);
    sendEvent(&_eventBuffer);
}
void onItemDragLeaveImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event,
                         const Ark_Number itemIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onItemDragLeave);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    sendEvent(&_eventBuffer);
}
void onItemDropImpl(Ark_Int32 nodeId,
                    const Ark_ItemDragInfo event,
                    const Ark_Number itemIndex,
                    const Ark_Number insertIndex,
                    const Ark_Boolean isSuccess)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onItemDrop);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    _eventBufferSerializer.writeNumber(insertIndex);
    _eventBufferSerializer.writeBoolean(isSuccess);
    sendEvent(&_eventBuffer);
}
void onScrollImpl(Ark_Int32 nodeId,
                  const Ark_Number scrollOffset,
                  const Ark_ScrollState scrollState)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(scrollOffset);
    _eventBufferSerializer.writeInt32(scrollState);
    sendEvent(&_eventBuffer);
}
void onReachStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onReachStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onReachEndImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onReachEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScrollStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStopImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScrollStop);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                            const Ark_Number offset,
                            const Ark_ScrollState state)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGrid_onScrollFrameBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(offset);
    _eventBufferSerializer.writeInt32(state);
    sendEvent(&_eventBuffer);
}
}
namespace GridItem {
void onSelectImpl(Ark_Int32 nodeId,
                  const Ark_Boolean isSelected)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGridItem_onSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isSelected);
    sendEvent(&_eventBuffer);
}
}
namespace GridRow {
void onBreakpointChangeImpl(Ark_Int32 nodeId,
                            const Ark_String breakpoints)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindGridRow_onBreakpointChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(breakpoints);
    sendEvent(&_eventBuffer);
}
}
namespace Image {
void onCompleteImpl(Ark_Int32 nodeId,
                    const Opt_Type_ImageAttribute_onComplete_callback_event event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImage_onComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_width = event_value.width;
        _eventBufferSerializer.writeNumber(event_value_width);
        const auto event_value_height = event_value.height;
        _eventBufferSerializer.writeNumber(event_value_height);
        const auto event_value_componentWidth = event_value.componentWidth;
        _eventBufferSerializer.writeNumber(event_value_componentWidth);
        const auto event_value_componentHeight = event_value.componentHeight;
        _eventBufferSerializer.writeNumber(event_value_componentHeight);
        const auto event_value_loadingStatus = event_value.loadingStatus;
        _eventBufferSerializer.writeNumber(event_value_loadingStatus);
        const auto event_value_contentWidth = event_value.contentWidth;
        _eventBufferSerializer.writeNumber(event_value_contentWidth);
        const auto event_value_contentHeight = event_value.contentHeight;
        _eventBufferSerializer.writeNumber(event_value_contentHeight);
        const auto event_value_contentOffsetX = event_value.contentOffsetX;
        _eventBufferSerializer.writeNumber(event_value_contentOffsetX);
        const auto event_value_contentOffsetY = event_value.contentOffsetY;
        _eventBufferSerializer.writeNumber(event_value_contentOffsetY);
    }
    sendEvent(&_eventBuffer);
}
void onErrorImpl(Ark_Int32 nodeId,
                 const Ark_ImageError error)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImage_onError);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeImageError(error);
    sendEvent(&_eventBuffer);
}
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImage_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace ImageAnimator {
void onStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageAnimator_onStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onPauseImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageAnimator_onPause);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onRepeatImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageAnimator_onRepeat);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onCancelImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageAnimator_onCancel);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageAnimator_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace ImageSpan {
void onCompleteImpl(Ark_Int32 nodeId,
                    const Ark_ImageLoadResult result)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageSpan_onComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeImageLoadResult(result);
    sendEvent(&_eventBuffer);
}
void onErrorImpl(Ark_Int32 nodeId,
                 const Ark_ImageError error)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindImageSpan_onError);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeImageError(error);
    sendEvent(&_eventBuffer);
}
}
namespace List {
void onScrollImpl(Ark_Int32 nodeId,
                  const Ark_Number scrollOffset,
                  const Ark_ScrollState scrollState)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(scrollOffset);
    _eventBufferSerializer.writeInt32(scrollState);
    sendEvent(&_eventBuffer);
}
void onScrollIndexImpl(Ark_Int32 nodeId,
                       const Ark_Number start,
                       const Ark_Number end,
                       const Ark_Number center)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScrollIndex);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(start);
    _eventBufferSerializer.writeNumber(end);
    _eventBufferSerializer.writeNumber(center);
    sendEvent(&_eventBuffer);
}
void onScrollVisibleContentChangeImpl(Ark_Int32 nodeId,
                                      const Ark_VisibleListContentInfo start,
                                      const Ark_VisibleListContentInfo end)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScrollVisibleContentChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeVisibleListContentInfo(start);
    _eventBufferSerializer.writeVisibleListContentInfo(end);
    sendEvent(&_eventBuffer);
}
void onReachStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onReachStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onReachEndImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onReachEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScrollStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStopImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScrollStop);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onItemDeleteImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onItemMoveImpl(Ark_Int32 nodeId,
                    const Ark_Number from,
                    const Ark_Number to)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemMove);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(from);
    _eventBufferSerializer.writeNumber(to);
    sendEvent(&_eventBuffer);
}
void onItemDragStartImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event,
                         const Ark_Number itemIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDragStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    sendEvent(&_eventBuffer);
}
void onItemDragEnterImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDragEnter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    sendEvent(&_eventBuffer);
}
void onItemDragMoveImpl(Ark_Int32 nodeId,
                        const Ark_ItemDragInfo event,
                        const Ark_Number itemIndex,
                        const Ark_Number insertIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDragMove);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    _eventBufferSerializer.writeNumber(insertIndex);
    sendEvent(&_eventBuffer);
}
void onItemDragLeaveImpl(Ark_Int32 nodeId,
                         const Ark_ItemDragInfo event,
                         const Ark_Number itemIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDragLeave);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    sendEvent(&_eventBuffer);
}
void onItemDropImpl(Ark_Int32 nodeId,
                    const Ark_ItemDragInfo event,
                    const Ark_Number itemIndex,
                    const Ark_Number insertIndex,
                    const Ark_Boolean isSuccess)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onItemDrop);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeItemDragInfo(event);
    _eventBufferSerializer.writeNumber(itemIndex);
    _eventBufferSerializer.writeNumber(insertIndex);
    _eventBufferSerializer.writeBoolean(isSuccess);
    sendEvent(&_eventBuffer);
}
void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                            const Ark_Number offset,
                            const Ark_ScrollState state)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindList_onScrollFrameBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(offset);
    _eventBufferSerializer.writeInt32(state);
    sendEvent(&_eventBuffer);
}
}
namespace ListItem {
void onSelectImpl(Ark_Int32 nodeId,
                  const Ark_Boolean isSelected)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindListItem_onSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isSelected);
    sendEvent(&_eventBuffer);
}
}
namespace LocationButton {
void onClickImpl(Ark_Int32 nodeId,
                 const Ark_ClickEvent event,
                 const Ark_LocationButtonOnClickResult result)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindLocationButton_onClick);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeClickEvent(event);
    _eventBufferSerializer.writeInt32(result);
    sendEvent(&_eventBuffer);
}
}
namespace Marquee {
void onStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindMarquee_onStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onBounceImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindMarquee_onBounce);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindMarquee_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace MenuItem {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Boolean selected)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindMenuItem_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(selected);
    sendEvent(&_eventBuffer);
}
}
namespace NavDestination {
void onShownImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onShown);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onHiddenImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onHidden);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onBackPressedImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onBackPressed);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onWillAppearImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onWillAppear);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onWillDisappearImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onWillDisappear);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onWillShowImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onWillShow);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onWillHideImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavDestination_onWillHide);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace NavRouter {
void onStateChangeImpl(Ark_Int32 nodeId,
                       const Ark_Boolean isActivated)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavRouter_onStateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isActivated);
    sendEvent(&_eventBuffer);
}
}
namespace Navigation {
void onTitleModeChangeImpl(Ark_Int32 nodeId,
                           const Ark_NavigationTitleMode titleMode)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavigation_onTitleModeChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(titleMode);
    sendEvent(&_eventBuffer);
}
void onNavBarStateChangeImpl(Ark_Int32 nodeId,
                             const Ark_Boolean isVisible)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavigation_onNavBarStateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isVisible);
    sendEvent(&_eventBuffer);
}
void onNavigationModeChangeImpl(Ark_Int32 nodeId,
                                const Ark_NavigationMode mode)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavigation_onNavigationModeChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(mode);
    sendEvent(&_eventBuffer);
}
void navDestinationImpl(Ark_Int32 nodeId,
                        const Ark_String name,
                        const Ark_CustomObject param)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavigation_navDestination);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(name);
    _eventBufferSerializer.writeCustomObject("Any", param);
    sendEvent(&_eventBuffer);
}
void customNavContentTransitionImpl(Ark_Int32 nodeId,
                                    const Ark_NavContentInfo from,
                                    const Ark_NavContentInfo to,
                                    const Ark_NavigationOperation operation)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindNavigation_customNavContentTransition);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNavContentInfo(from);
    _eventBufferSerializer.writeNavContentInfo(to);
    _eventBufferSerializer.writeInt32(operation);
    sendEvent(&_eventBuffer);
}
}
namespace Panel {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number width,
                  const Ark_Number height,
                  const Ark_PanelMode mode)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPanel_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(width);
    _eventBufferSerializer.writeNumber(height);
    _eventBufferSerializer.writeInt32(mode);
    sendEvent(&_eventBuffer);
}
void onHeightChangeImpl(Ark_Int32 nodeId,
                        const Ark_Number value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPanel_onHeightChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    sendEvent(&_eventBuffer);
}
}
namespace PasteButton {
void onClickImpl(Ark_Int32 nodeId,
                 const Ark_ClickEvent event,
                 const Ark_PasteButtonOnClickResult result)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPasteButton_onClick);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeClickEvent(event);
    _eventBufferSerializer.writeInt32(result);
    sendEvent(&_eventBuffer);
}
}
namespace PatternLock {
void onPatternCompleteImpl(Ark_Int32 nodeId,
                           const Array_Number input)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPatternLock_onPatternComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt8(runtimeType(input));
    _eventBufferSerializer.writeInt32(input.length);
    for (int i = 0; i < input.length; i++) {
        const auto input_element = input.array[i];
        _eventBufferSerializer.writeNumber(input_element);
    }
    sendEvent(&_eventBuffer);
}
}
namespace PluginComponent {
void onCompleteImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPluginComponent_onComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onErrorImpl(Ark_Int32 nodeId,
                 const Ark_Literal_Number_errcode_String_msg info)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindPluginComponent_onError);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto info_errcode = info.errcode;
    _eventBufferSerializer.writeNumber(info_errcode);
    const auto info_msg = info.msg;
    _eventBufferSerializer.writeString(info_msg);
    sendEvent(&_eventBuffer);
}
}
namespace Radio {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Boolean isChecked)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRadio_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isChecked);
    sendEvent(&_eventBuffer);
}
}
namespace Rating {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRating_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    sendEvent(&_eventBuffer);
}
}
namespace Refresh {
void onStateChangeImpl(Ark_Int32 nodeId,
                       const Ark_RefreshStatus state)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRefresh_onStateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(state);
    sendEvent(&_eventBuffer);
}
void onRefreshingImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRefresh_onRefreshing);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onOffsetChangeImpl(Ark_Int32 nodeId,
                        const Ark_Number value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRefresh_onOffsetChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    sendEvent(&_eventBuffer);
}
}
namespace RichEditor {
void onReadyImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onReady);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onSelectImpl(Ark_Int32 nodeId,
                  const Ark_RichEditorSelection value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorSelection(value);
    sendEvent(&_eventBuffer);
}
void onSelectionChangeImpl(Ark_Int32 nodeId,
                           const Ark_RichEditorRange value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onSelectionChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorRange(value);
    sendEvent(&_eventBuffer);
}
void aboutToIMEInputImpl(Ark_Int32 nodeId,
                         const Ark_RichEditorInsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_aboutToIMEInput);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onIMEInputCompleteImpl(Ark_Int32 nodeId,
                            const Ark_RichEditorTextSpanResult value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onIMEInputComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorTextSpanResult(value);
    sendEvent(&_eventBuffer);
}
void onDidIMEInputImpl(Ark_Int32 nodeId,
                       const Ark_TextRange value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onDidIMEInput);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTextRange(value);
    sendEvent(&_eventBuffer);
}
void aboutToDeleteImpl(Ark_Int32 nodeId,
                       const Ark_RichEditorDeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_aboutToDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void onDeleteCompleteImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onDeleteComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onPasteImpl(Ark_Int32 nodeId,
                 const Opt_PasteEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onPaste);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        _eventBufferSerializer.writePasteEvent(event_value);
    }
    sendEvent(&_eventBuffer);
}
void onEditingChangeImpl(Ark_Int32 nodeId,
                         const Ark_Boolean value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onEditingChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(value);
    sendEvent(&_eventBuffer);
}
void onSubmitImpl(Ark_Int32 nodeId,
                  const Ark_EnterKeyType enterKey,
                  const Ark_SubmitEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onSubmit);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(enterKey);
    _eventBufferSerializer.writeSubmitEvent(event);
    sendEvent(&_eventBuffer);
}
void onWillChangeImpl(Ark_Int32 nodeId,
                      const Ark_RichEditorChangeValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onWillChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRichEditorChangeValue(value);
    sendEvent(&_eventBuffer);
}
void onDidChangeImpl(Ark_Int32 nodeId,
                     const Ark_TextRange rangeBefore,
                     const Ark_TextRange rangeAfter)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onDidChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTextRange(rangeBefore);
    _eventBufferSerializer.writeTextRange(rangeAfter);
    sendEvent(&_eventBuffer);
}
void onCutImpl(Ark_Int32 nodeId,
               const Ark_CutEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onCut);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCutEvent(value);
    sendEvent(&_eventBuffer);
}
void onCopyImpl(Ark_Int32 nodeId,
                const Ark_CopyEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichEditor_onCopy);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeCopyEvent(value);
    sendEvent(&_eventBuffer);
}
}
namespace RichText {
void onStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichText_onStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onCompleteImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindRichText_onComplete);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace SaveButton {
void onClickImpl(Ark_Int32 nodeId,
                 const Ark_ClickEvent event,
                 const Ark_SaveButtonOnClickResult result)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSaveButton_onClick);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeClickEvent(event);
    _eventBufferSerializer.writeInt32(result);
    sendEvent(&_eventBuffer);
}
}
namespace Scroll {
void onScrollImpl(Ark_Int32 nodeId,
                  const Ark_Number xOffset,
                  const Ark_Number yOffset)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(xOffset);
    _eventBufferSerializer.writeNumber(yOffset);
    sendEvent(&_eventBuffer);
}
void onDidScrollImpl(Ark_Int32 nodeId,
                     const Ark_Number xOffset,
                     const Ark_Number yOffset,
                     const Ark_ScrollState scrollState)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onDidScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(xOffset);
    _eventBufferSerializer.writeNumber(yOffset);
    _eventBufferSerializer.writeInt32(scrollState);
    sendEvent(&_eventBuffer);
}
void onScrollEdgeImpl(Ark_Int32 nodeId,
                      const Ark_Edge side)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScrollEdge);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(side);
    sendEvent(&_eventBuffer);
}
void onScrollStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScrollStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollEndImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScrollEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollStopImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScrollStop);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                            const Ark_Number offset,
                            const Ark_ScrollState state)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindScroll_onScrollFrameBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(offset);
    _eventBufferSerializer.writeInt32(state);
    sendEvent(&_eventBuffer);
}
}
namespace Search {
void onEditChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onEditChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(value);
    sendEvent(&_eventBuffer);
}
void onSubmitImpl(Ark_Int32 nodeId,
                  const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onSubmit);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_String value,
                  const Opt_PreviewText previewText)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    Ark_Int32 previewText_type = ARK_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    _eventBufferSerializer.writeInt8(previewText_type);
    if ((ARK_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        _eventBufferSerializer.writePreviewText(previewText_value);
    }
    sendEvent(&_eventBuffer);
}
void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                               const Ark_Number selectionStart,
                               const Ark_Number selectionEnd)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onTextSelectionChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(selectionStart);
    _eventBufferSerializer.writeNumber(selectionEnd);
    sendEvent(&_eventBuffer);
}
void onContentScrollImpl(Ark_Int32 nodeId,
                         const Ark_Number totalOffsetX,
                         const Ark_Number totalOffsetY)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onContentScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(totalOffsetX);
    _eventBufferSerializer.writeNumber(totalOffsetY);
    sendEvent(&_eventBuffer);
}
void onCopyImpl(Ark_Int32 nodeId,
                const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onCopy);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onCutImpl(Ark_Int32 nodeId,
               const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onCut);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onPasteImpl(Ark_Int32 nodeId,
                 const Ark_String value,
                 const Ark_PasteEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onPaste);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    _eventBufferSerializer.writePasteEvent(event);
    sendEvent(&_eventBuffer);
}
void onWillInsertImpl(Ark_Int32 nodeId,
                      const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onWillInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onDidInsertImpl(Ark_Int32 nodeId,
                     const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onDidInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onWillDeleteImpl(Ark_Int32 nodeId,
                      const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onWillDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void onDidDeleteImpl(Ark_Int32 nodeId,
                     const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_onDidDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void inputFilterImpl(Ark_Int32 nodeId,
                     const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSearch_inputFilter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
}
namespace Select {
void onSelectImpl(Ark_Int32 nodeId,
                  const Ark_Number index,
                  const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSelect_onSelect);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
}
namespace Slider {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number value,
                  const Ark_SliderChangeMode mode)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSlider_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    _eventBufferSerializer.writeInt32(mode);
    sendEvent(&_eventBuffer);
}
}
namespace Stepper {
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindStepper_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onSkipImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindStepper_onSkip);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number prevIndex,
                  const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindStepper_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(prevIndex);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onNextImpl(Ark_Int32 nodeId,
                const Ark_Number index,
                const Ark_Number pendingIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindStepper_onNext);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(pendingIndex);
    sendEvent(&_eventBuffer);
}
void onPreviousImpl(Ark_Int32 nodeId,
                    const Ark_Number index,
                    const Ark_Number pendingIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindStepper_onPrevious);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(pendingIndex);
    sendEvent(&_eventBuffer);
}
}
namespace Swiper {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSwiper_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onAnimationStartImpl(Ark_Int32 nodeId,
                          const Ark_Number index,
                          const Ark_Number targetIndex,
                          const Ark_SwiperAnimationEvent extraInfo)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSwiper_onAnimationStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(targetIndex);
    _eventBufferSerializer.writeSwiperAnimationEvent(extraInfo);
    sendEvent(&_eventBuffer);
}
void onAnimationEndImpl(Ark_Int32 nodeId,
                        const Ark_Number index,
                        const Ark_SwiperAnimationEvent extraInfo)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSwiper_onAnimationEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeSwiperAnimationEvent(extraInfo);
    sendEvent(&_eventBuffer);
}
void onGestureSwipeImpl(Ark_Int32 nodeId,
                        const Ark_Number index,
                        const Ark_SwiperAnimationEvent extraInfo)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSwiper_onGestureSwipe);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeSwiperAnimationEvent(extraInfo);
    sendEvent(&_eventBuffer);
}
void onContentDidScrollImpl(Ark_Int32 nodeId,
                            const Ark_Number selectedIndex,
                            const Ark_Number index,
                            const Ark_Number position,
                            const Ark_Number mainAxisLength)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSwiper_onContentDidScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(selectedIndex);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(position);
    _eventBufferSerializer.writeNumber(mainAxisLength);
    sendEvent(&_eventBuffer);
}
}
namespace Tabs {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onTabBarClickImpl(Ark_Int32 nodeId,
                       const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onTabBarClick);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onAnimationStartImpl(Ark_Int32 nodeId,
                          const Ark_Number index,
                          const Ark_Number targetIndex,
                          const Ark_TabsAnimationEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onAnimationStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeNumber(targetIndex);
    _eventBufferSerializer.writeTabsAnimationEvent(event);
    sendEvent(&_eventBuffer);
}
void onAnimationEndImpl(Ark_Int32 nodeId,
                        const Ark_Number index,
                        const Ark_TabsAnimationEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onAnimationEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeTabsAnimationEvent(event);
    sendEvent(&_eventBuffer);
}
void onGestureSwipeImpl(Ark_Int32 nodeId,
                        const Ark_Number index,
                        const Ark_TabsAnimationEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onGestureSwipe);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(index);
    _eventBufferSerializer.writeTabsAnimationEvent(event);
    sendEvent(&_eventBuffer);
}
void customContentTransitionImpl(Ark_Int32 nodeId,
                                 const Ark_Number from,
                                 const Ark_Number to)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_customContentTransition);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(from);
    _eventBufferSerializer.writeNumber(to);
    sendEvent(&_eventBuffer);
}
void onContentWillChangeImpl(Ark_Int32 nodeId,
                             const Ark_Number currentIndex,
                             const Ark_Number comingIndex)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabs_onContentWillChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(currentIndex);
    _eventBufferSerializer.writeNumber(comingIndex);
    sendEvent(&_eventBuffer);
}
}
namespace TabContent {
void onWillShowImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabContent_onWillShow);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onWillHideImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTabContent_onWillHide);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace Text {
void onCopyImpl(Ark_Int32 nodeId,
                const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindText_onCopy);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                               const Ark_Number selectionStart,
                               const Ark_Number selectionEnd)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindText_onTextSelectionChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(selectionStart);
    _eventBufferSerializer.writeNumber(selectionEnd);
    sendEvent(&_eventBuffer);
}
}
namespace TextArea {
void onSubmitImpl(Ark_Int32 nodeId,
                  const Ark_EnterKeyType enterKey)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onSubmit);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(enterKey);
    sendEvent(&_eventBuffer);
}
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_String value,
                  const Opt_PreviewText previewText)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    Ark_Int32 previewText_type = ARK_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    _eventBufferSerializer.writeInt8(previewText_type);
    if ((ARK_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        _eventBufferSerializer.writePreviewText(previewText_value);
    }
    sendEvent(&_eventBuffer);
}
void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                               const Ark_Number selectionStart,
                               const Ark_Number selectionEnd)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onTextSelectionChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(selectionStart);
    _eventBufferSerializer.writeNumber(selectionEnd);
    sendEvent(&_eventBuffer);
}
void onContentScrollImpl(Ark_Int32 nodeId,
                         const Ark_Number totalOffsetX,
                         const Ark_Number totalOffsetY)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onContentScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(totalOffsetX);
    _eventBufferSerializer.writeNumber(totalOffsetY);
    sendEvent(&_eventBuffer);
}
void onEditChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean isEditing)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onEditChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isEditing);
    sendEvent(&_eventBuffer);
}
void onCopyImpl(Ark_Int32 nodeId,
                const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onCopy);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onCutImpl(Ark_Int32 nodeId,
               const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onCut);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onPasteImpl(Ark_Int32 nodeId,
                 const Ark_String value,
                 const Ark_PasteEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onPaste);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    _eventBufferSerializer.writePasteEvent(event);
    sendEvent(&_eventBuffer);
}
void onWillInsertImpl(Ark_Int32 nodeId,
                      const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onWillInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onDidInsertImpl(Ark_Int32 nodeId,
                     const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onDidInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onWillDeleteImpl(Ark_Int32 nodeId,
                      const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onWillDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void onDidDeleteImpl(Ark_Int32 nodeId,
                     const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_onDidDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void inputFilterImpl(Ark_Int32 nodeId,
                     const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextArea_inputFilter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
}
namespace TextClock {
void onDateChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextClock_onDateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(value);
    sendEvent(&_eventBuffer);
}
}
namespace TextInput {
void onEditChangedImpl(Ark_Int32 nodeId,
                       const Ark_Boolean isEditing)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onEditChanged);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isEditing);
    sendEvent(&_eventBuffer);
}
void onEditChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean isEditing)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onEditChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isEditing);
    sendEvent(&_eventBuffer);
}
void onSubmitImpl(Ark_Int32 nodeId,
                  const Ark_EnterKeyType enterKey,
                  const Ark_SubmitEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onSubmit);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(enterKey);
    _eventBufferSerializer.writeSubmitEvent(event);
    sendEvent(&_eventBuffer);
}
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_String value,
                  const Opt_PreviewText previewText)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    Ark_Int32 previewText_type = ARK_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    _eventBufferSerializer.writeInt8(previewText_type);
    if ((ARK_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        _eventBufferSerializer.writePreviewText(previewText_value);
    }
    sendEvent(&_eventBuffer);
}
void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                               const Ark_Number selectionStart,
                               const Ark_Number selectionEnd)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onTextSelectionChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(selectionStart);
    _eventBufferSerializer.writeNumber(selectionEnd);
    sendEvent(&_eventBuffer);
}
void onContentScrollImpl(Ark_Int32 nodeId,
                         const Ark_Number totalOffsetX,
                         const Ark_Number totalOffsetY)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onContentScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(totalOffsetX);
    _eventBufferSerializer.writeNumber(totalOffsetY);
    sendEvent(&_eventBuffer);
}
void onCopyImpl(Ark_Int32 nodeId,
                const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onCopy);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onCutImpl(Ark_Int32 nodeId,
               const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onCut);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
void onPasteImpl(Ark_Int32 nodeId,
                 const Ark_String value,
                 const Ark_PasteEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onPaste);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    _eventBufferSerializer.writePasteEvent(event);
    sendEvent(&_eventBuffer);
}
void onSecurityStateChangeImpl(Ark_Int32 nodeId,
                               const Ark_Boolean value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onSecurityStateChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(value);
    sendEvent(&_eventBuffer);
}
void onWillInsertImpl(Ark_Int32 nodeId,
                      const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onWillInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onDidInsertImpl(Ark_Int32 nodeId,
                     const Ark_InsertValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onDidInsert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInsertValue(value);
    sendEvent(&_eventBuffer);
}
void onWillDeleteImpl(Ark_Int32 nodeId,
                      const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onWillDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void onDidDeleteImpl(Ark_Int32 nodeId,
                     const Ark_DeleteValue value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_onDidDelete);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeDeleteValue(value);
    sendEvent(&_eventBuffer);
}
void inputFilterImpl(Ark_Int32 nodeId,
                     const Ark_String value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextInput_inputFilter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    sendEvent(&_eventBuffer);
}
}
namespace TextPicker {
void onAcceptImpl(Ark_Int32 nodeId,
                  const Ark_String value,
                  const Ark_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextPicker_onAccept);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeString(value);
    _eventBufferSerializer.writeNumber(index);
    sendEvent(&_eventBuffer);
}
void onCancelImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextPicker_onCancel);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Union_String_Array_String value,
                  const Ark_Union_Number_Array_Number index)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextPicker_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 value_type = ARK_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (((value_type == 0))) {
        _eventBufferSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        _eventBufferSerializer.writeString(value_0);
    }
    else if (((value_type == 1))) {
        _eventBufferSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        _eventBufferSerializer.writeInt8(runtimeType(value_1));
        _eventBufferSerializer.writeInt32(value_1.length);
        for (int i = 0; i < value_1.length; i++) {
            const auto value_1_element = value_1.array[i];
            _eventBufferSerializer.writeString(value_1_element);
        }
    }
    Ark_Int32 index_type = ARK_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (((index_type == 0))) {
        _eventBufferSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        _eventBufferSerializer.writeNumber(index_0);
    }
    else if (((index_type == 1))) {
        _eventBufferSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        _eventBufferSerializer.writeInt8(runtimeType(index_1));
        _eventBufferSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const auto index_1_element = index_1.array[i];
            _eventBufferSerializer.writeNumber(index_1_element);
        }
    }
    sendEvent(&_eventBuffer);
}
}
namespace TextTimer {
void onTimerImpl(Ark_Int32 nodeId,
                 const Ark_Number utc,
                 const Ark_Number elapsedTime)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTextTimer_onTimer);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(utc);
    _eventBufferSerializer.writeNumber(elapsedTime);
    sendEvent(&_eventBuffer);
}
}
namespace TimePicker {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_TimePickerResult value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindTimePicker_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTimePickerResult(value);
    sendEvent(&_eventBuffer);
}
}
namespace Toggle {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Boolean isOn)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindToggle_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(isOn);
    sendEvent(&_eventBuffer);
}
}
namespace Video {
void onStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onPauseImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onPause);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFinishImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onFinish);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFullscreenChangeImpl(Ark_Int32 nodeId,
                            const Ark_Literal_Boolean_fullscreen event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onFullscreenChange);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto event_fullscreen = event.fullscreen;
    _eventBufferSerializer.writeBoolean(event_fullscreen);
    sendEvent(&_eventBuffer);
}
void onPreparedImpl(Ark_Int32 nodeId,
                    const Ark_Literal_Number_duration event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onPrepared);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto event_duration = event.duration;
    _eventBufferSerializer.writeNumber(event_duration);
    sendEvent(&_eventBuffer);
}
void onSeekingImpl(Ark_Int32 nodeId,
                   const Ark_Literal_Number_time event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onSeeking);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto event_time = event.time;
    _eventBufferSerializer.writeNumber(event_time);
    sendEvent(&_eventBuffer);
}
void onSeekedImpl(Ark_Int32 nodeId,
                  const Ark_Literal_Number_time event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onSeeked);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto event_time = event.time;
    _eventBufferSerializer.writeNumber(event_time);
    sendEvent(&_eventBuffer);
}
void onUpdateImpl(Ark_Int32 nodeId,
                  const Ark_Literal_Number_time event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onUpdate);
    _eventBufferSerializer.writeInt32(nodeId);
    const auto event_time = event.time;
    _eventBufferSerializer.writeNumber(event_time);
    sendEvent(&_eventBuffer);
}
void onErrorImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onError);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onStopImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindVideo_onStop);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace Web {
void onPageEndImpl(Ark_Int32 nodeId,
                   const Ark_OnPageEndEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onPageEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnPageEndEvent(value);
    sendEvent(&_eventBuffer);
}
void onPageBeginImpl(Ark_Int32 nodeId,
                     const Ark_OnPageBeginEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onPageBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnPageBeginEvent(value);
    sendEvent(&_eventBuffer);
}
void onProgressChangeImpl(Ark_Int32 nodeId,
                          const Ark_OnProgressChangeEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onProgressChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnProgressChangeEvent(value);
    sendEvent(&_eventBuffer);
}
void onTitleReceiveImpl(Ark_Int32 nodeId,
                        const Ark_OnTitleReceiveEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onTitleReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnTitleReceiveEvent(value);
    sendEvent(&_eventBuffer);
}
void onGeolocationHideImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onGeolocationHide);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onGeolocationShowImpl(Ark_Int32 nodeId,
                           const Ark_OnGeolocationShowEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onGeolocationShow);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnGeolocationShowEvent(value);
    sendEvent(&_eventBuffer);
}
void onRequestSelectedImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRequestSelected);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onAlertImpl(Ark_Int32 nodeId,
                 const Ark_OnAlertEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onAlert);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnAlertEvent(value);
    sendEvent(&_eventBuffer);
}
void onBeforeUnloadImpl(Ark_Int32 nodeId,
                        const Ark_OnBeforeUnloadEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onBeforeUnload);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnBeforeUnloadEvent(value);
    sendEvent(&_eventBuffer);
}
void onConfirmImpl(Ark_Int32 nodeId,
                   const Ark_OnConfirmEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onConfirm);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnConfirmEvent(value);
    sendEvent(&_eventBuffer);
}
void onPromptImpl(Ark_Int32 nodeId,
                  const Ark_OnPromptEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onPrompt);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnPromptEvent(value);
    sendEvent(&_eventBuffer);
}
void onConsoleImpl(Ark_Int32 nodeId,
                   const Ark_OnConsoleEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onConsole);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnConsoleEvent(value);
    sendEvent(&_eventBuffer);
}
void onErrorReceiveImpl(Ark_Int32 nodeId,
                        const Ark_OnErrorReceiveEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onErrorReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnErrorReceiveEvent(value);
    sendEvent(&_eventBuffer);
}
void onHttpErrorReceiveImpl(Ark_Int32 nodeId,
                            const Ark_OnHttpErrorReceiveEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onHttpErrorReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnHttpErrorReceiveEvent(value);
    sendEvent(&_eventBuffer);
}
void onDownloadStartImpl(Ark_Int32 nodeId,
                         const Ark_OnDownloadStartEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onDownloadStart);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnDownloadStartEvent(value);
    sendEvent(&_eventBuffer);
}
void onRefreshAccessedHistoryImpl(Ark_Int32 nodeId,
                                  const Ark_OnRefreshAccessedHistoryEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRefreshAccessedHistory);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnRefreshAccessedHistoryEvent(value);
    sendEvent(&_eventBuffer);
}
void onUrlLoadInterceptImpl(Ark_Int32 nodeId,
                            const Opt_Literal_Union_String_WebResourceRequest_data event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onUrlLoadIntercept);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_data = event_value.data;
        Ark_Int32 event_value_data_type = ARK_RUNTIME_UNDEFINED;
        event_value_data_type = event_value_data.selector;
        if (((event_value_data_type == 0))) {
            _eventBufferSerializer.writeInt8(0);
            const auto event_value_data_0 = event_value_data.value0;
            _eventBufferSerializer.writeString(event_value_data_0);
        }
        else if (((event_value_data_type == 1))) {
            _eventBufferSerializer.writeInt8(1);
            const auto event_value_data_1 = event_value_data.value1;
            _eventBufferSerializer.writeMaterialized(event_value_data_1);
        }
    }
    sendEvent(&_eventBuffer);
}
void onSslErrorReceiveImpl(Ark_Int32 nodeId,
                           const Opt_Literal_Function_handler_object_error event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onSslErrorReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_handler = event_value.handler;
        _eventBufferSerializer.writeFunction(event_value_handler);
        const auto event_value_error = event_value.error;
        _eventBufferSerializer.writeCustomObject("Object", event_value_error);
    }
    sendEvent(&_eventBuffer);
}
void onRenderExited0Impl(Ark_Int32 nodeId,
                         const Ark_OnRenderExitedEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRenderExited0);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnRenderExitedEvent(value);
    sendEvent(&_eventBuffer);
}
void onShowFileSelectorImpl(Ark_Int32 nodeId,
                            const Ark_OnShowFileSelectorEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onShowFileSelector);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnShowFileSelectorEvent(value);
    sendEvent(&_eventBuffer);
}
void onRenderExited1Impl(Ark_Int32 nodeId,
                         const Opt_Literal_object_detail event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRenderExited1);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_detail = event_value.detail;
        _eventBufferSerializer.writeCustomObject("Object", event_value_detail);
    }
    sendEvent(&_eventBuffer);
}
void onFileSelectorShowImpl(Ark_Int32 nodeId,
                            const Opt_Literal_Function_callback_object_fileSelector event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFileSelectorShow);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_callback = event_value.callback;
        _eventBufferSerializer.writeFunction(event_value_callback);
        const auto event_value_fileSelector = event_value.fileSelector;
        _eventBufferSerializer.writeCustomObject("Object", event_value_fileSelector);
    }
    sendEvent(&_eventBuffer);
}
void onResourceLoadImpl(Ark_Int32 nodeId,
                        const Ark_OnResourceLoadEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onResourceLoad);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnResourceLoadEvent(value);
    sendEvent(&_eventBuffer);
}
void onFullScreenExitImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFullScreenExit);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onFullScreenEnterImpl(Ark_Int32 nodeId,
                           const Ark_FullScreenEnterEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFullScreenEnter);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeFullScreenEnterEvent(event);
    sendEvent(&_eventBuffer);
}
void onScaleChangeImpl(Ark_Int32 nodeId,
                       const Ark_OnScaleChangeEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onScaleChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnScaleChangeEvent(value);
    sendEvent(&_eventBuffer);
}
void onHttpAuthRequestImpl(Ark_Int32 nodeId,
                           const Ark_OnHttpAuthRequestEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onHttpAuthRequest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnHttpAuthRequestEvent(value);
    sendEvent(&_eventBuffer);
}
void onInterceptRequestImpl(Ark_Int32 nodeId,
                            const Ark_OnInterceptRequestEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onInterceptRequest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnInterceptRequestEvent(value);
    sendEvent(&_eventBuffer);
}
void onPermissionRequestImpl(Ark_Int32 nodeId,
                             const Ark_OnPermissionRequestEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onPermissionRequest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnPermissionRequestEvent(value);
    sendEvent(&_eventBuffer);
}
void onScreenCaptureRequestImpl(Ark_Int32 nodeId,
                                const Ark_OnScreenCaptureRequestEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onScreenCaptureRequest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnScreenCaptureRequestEvent(value);
    sendEvent(&_eventBuffer);
}
void onContextMenuShowImpl(Ark_Int32 nodeId,
                           const Ark_OnContextMenuShowEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onContextMenuShow);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnContextMenuShowEvent(value);
    sendEvent(&_eventBuffer);
}
void onContextMenuHideImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onContextMenuHide);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onSearchResultReceiveImpl(Ark_Int32 nodeId,
                               const Ark_OnSearchResultReceiveEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onSearchResultReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnSearchResultReceiveEvent(value);
    sendEvent(&_eventBuffer);
}
void onScrollImpl(Ark_Int32 nodeId,
                  const Ark_OnScrollEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnScrollEvent(value);
    sendEvent(&_eventBuffer);
}
void onSslErrorEventReceiveImpl(Ark_Int32 nodeId,
                                const Ark_OnSslErrorEventReceiveEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onSslErrorEventReceive);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnSslErrorEventReceiveEvent(value);
    sendEvent(&_eventBuffer);
}
void onSslErrorEventImpl(Ark_Int32 nodeId,
                         const Ark_SslErrorEvent sslErrorEvent)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onSslErrorEvent);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeSslErrorEvent(sslErrorEvent);
    sendEvent(&_eventBuffer);
}
void onClientAuthenticationRequestImpl(Ark_Int32 nodeId,
                                       const Ark_OnClientAuthenticationEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onClientAuthenticationRequest);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnClientAuthenticationEvent(value);
    sendEvent(&_eventBuffer);
}
void onWindowNewImpl(Ark_Int32 nodeId,
                     const Ark_OnWindowNewEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onWindowNew);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnWindowNewEvent(value);
    sendEvent(&_eventBuffer);
}
void onWindowExitImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onWindowExit);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onInterceptKeyEventImpl(Ark_Int32 nodeId,
                             const Ark_KeyEvent event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onInterceptKeyEvent);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeKeyEvent(event);
    sendEvent(&_eventBuffer);
}
void onTouchIconUrlReceivedImpl(Ark_Int32 nodeId,
                                const Ark_OnTouchIconUrlReceivedEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onTouchIconUrlReceived);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnTouchIconUrlReceivedEvent(value);
    sendEvent(&_eventBuffer);
}
void onFaviconReceivedImpl(Ark_Int32 nodeId,
                           const Ark_OnFaviconReceivedEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFaviconReceived);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnFaviconReceivedEvent(value);
    sendEvent(&_eventBuffer);
}
void onPageVisibleImpl(Ark_Int32 nodeId,
                       const Ark_OnPageVisibleEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onPageVisible);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnPageVisibleEvent(value);
    sendEvent(&_eventBuffer);
}
void onDataResubmittedImpl(Ark_Int32 nodeId,
                           const Ark_OnDataResubmittedEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onDataResubmitted);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnDataResubmittedEvent(value);
    sendEvent(&_eventBuffer);
}
void onAudioStateChangedImpl(Ark_Int32 nodeId,
                             const Ark_OnAudioStateChangedEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onAudioStateChanged);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnAudioStateChangedEvent(value);
    sendEvent(&_eventBuffer);
}
void onFirstContentfulPaintImpl(Ark_Int32 nodeId,
                                const Ark_OnFirstContentfulPaintEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFirstContentfulPaint);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnFirstContentfulPaintEvent(value);
    sendEvent(&_eventBuffer);
}
void onFirstMeaningfulPaintImpl(Ark_Int32 nodeId,
                                const Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onFirstMeaningfulPaint);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeFirstMeaningfulPaint(firstMeaningfulPaint);
    sendEvent(&_eventBuffer);
}
void onLargestContentfulPaintImpl(Ark_Int32 nodeId,
                                  const Ark_LargestContentfulPaint largestContentfulPaint)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onLargestContentfulPaint);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeLargestContentfulPaint(largestContentfulPaint);
    sendEvent(&_eventBuffer);
}
void onLoadInterceptImpl(Ark_Int32 nodeId,
                         const Ark_OnLoadInterceptEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onLoadIntercept);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnLoadInterceptEvent(value);
    sendEvent(&_eventBuffer);
}
void onControllerAttachedImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onControllerAttached);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onOverScrollImpl(Ark_Int32 nodeId,
                      const Ark_OnOverScrollEvent value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onOverScroll);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeOnOverScrollEvent(value);
    sendEvent(&_eventBuffer);
}
void onSafeBrowsingCheckResultImpl(Ark_Int32 nodeId,
                                   const Ark_ThreatType threatType)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onSafeBrowsingCheckResult);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(threatType);
    sendEvent(&_eventBuffer);
}
void onNavigationEntryCommittedImpl(Ark_Int32 nodeId,
                                    const Ark_LoadCommittedDetails loadCommittedDetails)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onNavigationEntryCommitted);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeLoadCommittedDetails(loadCommittedDetails);
    sendEvent(&_eventBuffer);
}
void onIntelligentTrackingPreventionResultImpl(Ark_Int32 nodeId,
                                               const Ark_IntelligentTrackingPreventionDetails details)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onIntelligentTrackingPreventionResult);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeIntelligentTrackingPreventionDetails(details);
    sendEvent(&_eventBuffer);
}
void onNativeEmbedLifecycleChangeImpl(Ark_Int32 nodeId,
                                      const Ark_NativeEmbedDataInfo event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedLifecycleChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNativeEmbedDataInfo(event);
    sendEvent(&_eventBuffer);
}
void onNativeEmbedVisibilityChangeImpl(Ark_Int32 nodeId,
                                       const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedVisibilityChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNativeEmbedVisibilityInfo(nativeEmbedVisibilityInfo);
    sendEvent(&_eventBuffer);
}
void onNativeEmbedGestureEventImpl(Ark_Int32 nodeId,
                                   const Ark_NativeEmbedTouchInfo event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedGestureEvent);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNativeEmbedTouchInfo(event);
    sendEvent(&_eventBuffer);
}
void onOverrideUrlLoadingImpl(Ark_Int32 nodeId,
                              const Ark_Materialized webResourceRequest)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onOverrideUrlLoading);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeMaterialized(webResourceRequest);
    sendEvent(&_eventBuffer);
}
void onRenderProcessNotRespondingImpl(Ark_Int32 nodeId,
                                      const Ark_RenderProcessNotRespondingData data)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRenderProcessNotResponding);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeRenderProcessNotRespondingData(data);
    sendEvent(&_eventBuffer);
}
void onRenderProcessRespondingImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onRenderProcessResponding);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onViewportFitChangedImpl(Ark_Int32 nodeId,
                              const Ark_ViewportFit viewportFit)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onViewportFitChanged);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeInt32(viewportFit);
    sendEvent(&_eventBuffer);
}
void onInterceptKeyboardAttachImpl(Ark_Int32 nodeId,
                                   const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onInterceptKeyboardAttach);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeWebKeyboardCallbackInfo(keyboardCallbackInfo);
    sendEvent(&_eventBuffer);
}
void onAdsBlockedImpl(Ark_Int32 nodeId,
                      const Ark_AdsBlockedDetails details)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWeb_onAdsBlocked);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeAdsBlockedDetails(details);
    sendEvent(&_eventBuffer);
}
}
namespace XComponent {
void onLoadImpl(Ark_Int32 nodeId,
                const Opt_CustomObject event)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindXComponent_onLoad);
    _eventBufferSerializer.writeInt32(nodeId);
    Ark_Int32 event_type = ARK_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    _eventBufferSerializer.writeInt8(event_type);
    if ((ARK_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        _eventBufferSerializer.writeCustomObject("Object", event_value);
    }
    sendEvent(&_eventBuffer);
}
void onDestroyImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindXComponent_onDestroy);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
}
namespace SideBarContainer {
void onChangeImpl(Ark_Int32 nodeId,
                  const Ark_Boolean value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindSideBarContainer_onChange);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeBoolean(value);
    sendEvent(&_eventBuffer);
}
}
namespace WaterFlow {
void onReachStartImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWaterFlow_onReachStart);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onReachEndImpl(Ark_Int32 nodeId)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWaterFlow_onReachEnd);
    _eventBufferSerializer.writeInt32(nodeId);
    sendEvent(&_eventBuffer);
}
void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                            const Ark_Number offset,
                            const Ark_ScrollState state)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWaterFlow_onScrollFrameBegin);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(offset);
    _eventBufferSerializer.writeInt32(state);
    sendEvent(&_eventBuffer);
}
void onScrollIndexImpl(Ark_Int32 nodeId,
                       const Ark_Number first,
                       const Ark_Number last)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindWaterFlow_onScrollIndex);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeNumber(first);
    _eventBufferSerializer.writeNumber(last);
    sendEvent(&_eventBuffer);
}
}
namespace UIExtensionComponent {
void onTerminatedImpl(Ark_Int32 nodeId,
                      const Ark_TerminationInfo value)
{
    EventBuffer _eventBuffer;
    Serializer _eventBufferSerializer(_eventBuffer.buffer);
    _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onTerminated);
    _eventBufferSerializer.writeInt32(nodeId);
    _eventBufferSerializer.writeTerminationInfo(value);
    sendEvent(&_eventBuffer);
}
}
const GENERATED_ArkUIAbilityComponentEventsReceiver* GetAbilityComponentEventsReceiver()
{
    static const GENERATED_ArkUIAbilityComponentEventsReceiver GENERATED_ArkUIAbilityComponentEventsReceiverImpl {
        AbilityComponent::onConnectImpl,
        AbilityComponent::onDisconnectImpl,
    };

    return &GENERATED_ArkUIAbilityComponentEventsReceiverImpl;
}
const GENERATED_ArkUIAlphabetIndexerEventsReceiver* GetAlphabetIndexerEventsReceiver()
{
    static const GENERATED_ArkUIAlphabetIndexerEventsReceiver GENERATED_ArkUIAlphabetIndexerEventsReceiverImpl {
        AlphabetIndexer::onSelectedImpl,
        AlphabetIndexer::onSelectImpl,
        AlphabetIndexer::onRequestPopupDataImpl,
        AlphabetIndexer::onPopupSelectImpl,
    };

    return &GENERATED_ArkUIAlphabetIndexerEventsReceiverImpl;
}
const GENERATED_ArkUIAnimatorEventsReceiver* GetAnimatorEventsReceiver()
{
    static const GENERATED_ArkUIAnimatorEventsReceiver GENERATED_ArkUIAnimatorEventsReceiverImpl {
        Animator::onStartImpl,
        Animator::onPauseImpl,
        Animator::onRepeatImpl,
        Animator::onCancelImpl,
        Animator::onFinishImpl,
        Animator::onFrameImpl,
    };

    return &GENERATED_ArkUIAnimatorEventsReceiverImpl;
}
const GENERATED_ArkUICalendarEventsReceiver* GetCalendarEventsReceiver()
{
    static const GENERATED_ArkUICalendarEventsReceiver GENERATED_ArkUICalendarEventsReceiverImpl {
        Calendar::onSelectChangeImpl,
        Calendar::onRequestDataImpl,
    };

    return &GENERATED_ArkUICalendarEventsReceiverImpl;
}
const GENERATED_ArkUICalendarPickerEventsReceiver* GetCalendarPickerEventsReceiver()
{
    static const GENERATED_ArkUICalendarPickerEventsReceiver GENERATED_ArkUICalendarPickerEventsReceiverImpl {
        CalendarPicker::onChangeImpl,
    };

    return &GENERATED_ArkUICalendarPickerEventsReceiverImpl;
}
const GENERATED_ArkUICanvasEventsReceiver* GetCanvasEventsReceiver()
{
    static const GENERATED_ArkUICanvasEventsReceiver GENERATED_ArkUICanvasEventsReceiverImpl {
        Canvas::onReadyImpl,
    };

    return &GENERATED_ArkUICanvasEventsReceiverImpl;
}
const GENERATED_ArkUICheckboxEventsReceiver* GetCheckboxEventsReceiver()
{
    static const GENERATED_ArkUICheckboxEventsReceiver GENERATED_ArkUICheckboxEventsReceiverImpl {
        Checkbox::onChangeImpl,
    };

    return &GENERATED_ArkUICheckboxEventsReceiverImpl;
}
const GENERATED_ArkUICheckboxGroupEventsReceiver* GetCheckboxGroupEventsReceiver()
{
    static const GENERATED_ArkUICheckboxGroupEventsReceiver GENERATED_ArkUICheckboxGroupEventsReceiverImpl {
        CheckboxGroup::onChangeImpl,
    };

    return &GENERATED_ArkUICheckboxGroupEventsReceiverImpl;
}
const GENERATED_ArkUICommonMethodEventsReceiver* GetCommonMethodEventsReceiver()
{
    static const GENERATED_ArkUICommonMethodEventsReceiver GENERATED_ArkUICommonMethodEventsReceiverImpl {
        CommonMethod::onChildTouchTestImpl,
        CommonMethod::onClickImpl,
        CommonMethod::onHoverImpl,
        CommonMethod::onAccessibilityHoverImpl,
        CommonMethod::onMouseImpl,
        CommonMethod::onTouchImpl,
        CommonMethod::onKeyEventImpl,
        CommonMethod::onKeyPreImeImpl,
        CommonMethod::onFocusImpl,
        CommonMethod::onBlurImpl,
        CommonMethod::onAppearImpl,
        CommonMethod::onDisAppearImpl,
        CommonMethod::onAttachImpl,
        CommonMethod::onDetachImpl,
        CommonMethod::onAreaChangeImpl,
        CommonMethod::onDragStartImpl,
        CommonMethod::onDragEnterImpl,
        CommonMethod::onDragMoveImpl,
        CommonMethod::onDragLeaveImpl,
        CommonMethod::onDropImpl,
        CommonMethod::onDragEndImpl,
        CommonMethod::onPreDragImpl,
        CommonMethod::onGestureJudgeBeginImpl,
        CommonMethod::onGestureRecognizerJudgeBeginImpl,
        CommonMethod::shouldBuiltInRecognizerParallelWithImpl,
        CommonMethod::onTouchInterceptImpl,
        CommonMethod::onSizeChangeImpl,
        CommonMethod::onVisibleAreaChangeImpl,
        CommonMethod::keyboardShortcutImpl,
    };

    return &GENERATED_ArkUICommonMethodEventsReceiverImpl;
}
const GENERATED_ArkUIScrollableCommonMethodEventsReceiver* GetScrollableCommonMethodEventsReceiver()
{
    static const GENERATED_ArkUIScrollableCommonMethodEventsReceiver GENERATED_ArkUIScrollableCommonMethodEventsReceiverImpl {
        ScrollableCommonMethod::onScrollImpl,
        ScrollableCommonMethod::onDidScrollImpl,
        ScrollableCommonMethod::onReachStartImpl,
        ScrollableCommonMethod::onReachEndImpl,
        ScrollableCommonMethod::onScrollStartImpl,
        ScrollableCommonMethod::onScrollStopImpl,
    };

    return &GENERATED_ArkUIScrollableCommonMethodEventsReceiverImpl;
}
const GENERATED_ArkUICounterEventsReceiver* GetCounterEventsReceiver()
{
    static const GENERATED_ArkUICounterEventsReceiver GENERATED_ArkUICounterEventsReceiverImpl {
        Counter::onIncImpl,
        Counter::onDecImpl,
    };

    return &GENERATED_ArkUICounterEventsReceiverImpl;
}
const GENERATED_ArkUIDatePickerEventsReceiver* GetDatePickerEventsReceiver()
{
    static const GENERATED_ArkUIDatePickerEventsReceiver GENERATED_ArkUIDatePickerEventsReceiverImpl {
        DatePicker::onChangeImpl,
        DatePicker::onDateChangeImpl,
    };

    return &GENERATED_ArkUIDatePickerEventsReceiverImpl;
}
const GENERATED_ArkUIFolderStackEventsReceiver* GetFolderStackEventsReceiver()
{
    static const GENERATED_ArkUIFolderStackEventsReceiver GENERATED_ArkUIFolderStackEventsReceiverImpl {
        FolderStack::onFolderStateChangeImpl,
        FolderStack::onHoverStatusChangeImpl,
    };

    return &GENERATED_ArkUIFolderStackEventsReceiverImpl;
}
const GENERATED_ArkUIFormComponentEventsReceiver* GetFormComponentEventsReceiver()
{
    static const GENERATED_ArkUIFormComponentEventsReceiver GENERATED_ArkUIFormComponentEventsReceiverImpl {
        FormComponent::onAcquiredImpl,
        FormComponent::onErrorImpl,
        FormComponent::onRouterImpl,
        FormComponent::onUninstallImpl,
        FormComponent::onLoadImpl,
    };

    return &GENERATED_ArkUIFormComponentEventsReceiverImpl;
}
const GENERATED_ArkUIGridEventsReceiver* GetGridEventsReceiver()
{
    static const GENERATED_ArkUIGridEventsReceiver GENERATED_ArkUIGridEventsReceiverImpl {
        Grid::onScrollBarUpdateImpl,
        Grid::onScrollIndexImpl,
        Grid::onItemDragStartImpl,
        Grid::onItemDragEnterImpl,
        Grid::onItemDragMoveImpl,
        Grid::onItemDragLeaveImpl,
        Grid::onItemDropImpl,
        Grid::onScrollImpl,
        Grid::onReachStartImpl,
        Grid::onReachEndImpl,
        Grid::onScrollStartImpl,
        Grid::onScrollStopImpl,
        Grid::onScrollFrameBeginImpl,
    };

    return &GENERATED_ArkUIGridEventsReceiverImpl;
}
const GENERATED_ArkUIGridItemEventsReceiver* GetGridItemEventsReceiver()
{
    static const GENERATED_ArkUIGridItemEventsReceiver GENERATED_ArkUIGridItemEventsReceiverImpl {
        GridItem::onSelectImpl,
    };

    return &GENERATED_ArkUIGridItemEventsReceiverImpl;
}
const GENERATED_ArkUIGridRowEventsReceiver* GetGridRowEventsReceiver()
{
    static const GENERATED_ArkUIGridRowEventsReceiver GENERATED_ArkUIGridRowEventsReceiverImpl {
        GridRow::onBreakpointChangeImpl,
    };

    return &GENERATED_ArkUIGridRowEventsReceiverImpl;
}
const GENERATED_ArkUIImageEventsReceiver* GetImageEventsReceiver()
{
    static const GENERATED_ArkUIImageEventsReceiver GENERATED_ArkUIImageEventsReceiverImpl {
        Image::onCompleteImpl,
        Image::onErrorImpl,
        Image::onFinishImpl,
    };

    return &GENERATED_ArkUIImageEventsReceiverImpl;
}
const GENERATED_ArkUIImageAnimatorEventsReceiver* GetImageAnimatorEventsReceiver()
{
    static const GENERATED_ArkUIImageAnimatorEventsReceiver GENERATED_ArkUIImageAnimatorEventsReceiverImpl {
        ImageAnimator::onStartImpl,
        ImageAnimator::onPauseImpl,
        ImageAnimator::onRepeatImpl,
        ImageAnimator::onCancelImpl,
        ImageAnimator::onFinishImpl,
    };

    return &GENERATED_ArkUIImageAnimatorEventsReceiverImpl;
}
const GENERATED_ArkUIImageSpanEventsReceiver* GetImageSpanEventsReceiver()
{
    static const GENERATED_ArkUIImageSpanEventsReceiver GENERATED_ArkUIImageSpanEventsReceiverImpl {
        ImageSpan::onCompleteImpl,
        ImageSpan::onErrorImpl,
    };

    return &GENERATED_ArkUIImageSpanEventsReceiverImpl;
}
const GENERATED_ArkUIListEventsReceiver* GetListEventsReceiver()
{
    static const GENERATED_ArkUIListEventsReceiver GENERATED_ArkUIListEventsReceiverImpl {
        List::onScrollImpl,
        List::onScrollIndexImpl,
        List::onScrollVisibleContentChangeImpl,
        List::onReachStartImpl,
        List::onReachEndImpl,
        List::onScrollStartImpl,
        List::onScrollStopImpl,
        List::onItemDeleteImpl,
        List::onItemMoveImpl,
        List::onItemDragStartImpl,
        List::onItemDragEnterImpl,
        List::onItemDragMoveImpl,
        List::onItemDragLeaveImpl,
        List::onItemDropImpl,
        List::onScrollFrameBeginImpl,
    };

    return &GENERATED_ArkUIListEventsReceiverImpl;
}
const GENERATED_ArkUIListItemEventsReceiver* GetListItemEventsReceiver()
{
    static const GENERATED_ArkUIListItemEventsReceiver GENERATED_ArkUIListItemEventsReceiverImpl {
        ListItem::onSelectImpl,
    };

    return &GENERATED_ArkUIListItemEventsReceiverImpl;
}
const GENERATED_ArkUILocationButtonEventsReceiver* GetLocationButtonEventsReceiver()
{
    static const GENERATED_ArkUILocationButtonEventsReceiver GENERATED_ArkUILocationButtonEventsReceiverImpl {
        LocationButton::onClickImpl,
    };

    return &GENERATED_ArkUILocationButtonEventsReceiverImpl;
}
const GENERATED_ArkUIMarqueeEventsReceiver* GetMarqueeEventsReceiver()
{
    static const GENERATED_ArkUIMarqueeEventsReceiver GENERATED_ArkUIMarqueeEventsReceiverImpl {
        Marquee::onStartImpl,
        Marquee::onBounceImpl,
        Marquee::onFinishImpl,
    };

    return &GENERATED_ArkUIMarqueeEventsReceiverImpl;
}
const GENERATED_ArkUIMenuItemEventsReceiver* GetMenuItemEventsReceiver()
{
    static const GENERATED_ArkUIMenuItemEventsReceiver GENERATED_ArkUIMenuItemEventsReceiverImpl {
        MenuItem::onChangeImpl,
    };

    return &GENERATED_ArkUIMenuItemEventsReceiverImpl;
}
const GENERATED_ArkUINavDestinationEventsReceiver* GetNavDestinationEventsReceiver()
{
    static const GENERATED_ArkUINavDestinationEventsReceiver GENERATED_ArkUINavDestinationEventsReceiverImpl {
        NavDestination::onShownImpl,
        NavDestination::onHiddenImpl,
        NavDestination::onBackPressedImpl,
        NavDestination::onWillAppearImpl,
        NavDestination::onWillDisappearImpl,
        NavDestination::onWillShowImpl,
        NavDestination::onWillHideImpl,
    };

    return &GENERATED_ArkUINavDestinationEventsReceiverImpl;
}
const GENERATED_ArkUINavRouterEventsReceiver* GetNavRouterEventsReceiver()
{
    static const GENERATED_ArkUINavRouterEventsReceiver GENERATED_ArkUINavRouterEventsReceiverImpl {
        NavRouter::onStateChangeImpl,
    };

    return &GENERATED_ArkUINavRouterEventsReceiverImpl;
}
const GENERATED_ArkUINavigationEventsReceiver* GetNavigationEventsReceiver()
{
    static const GENERATED_ArkUINavigationEventsReceiver GENERATED_ArkUINavigationEventsReceiverImpl {
        Navigation::onTitleModeChangeImpl,
        Navigation::onNavBarStateChangeImpl,
        Navigation::onNavigationModeChangeImpl,
        Navigation::navDestinationImpl,
        Navigation::customNavContentTransitionImpl,
    };

    return &GENERATED_ArkUINavigationEventsReceiverImpl;
}
const GENERATED_ArkUIPanelEventsReceiver* GetPanelEventsReceiver()
{
    static const GENERATED_ArkUIPanelEventsReceiver GENERATED_ArkUIPanelEventsReceiverImpl {
        Panel::onChangeImpl,
        Panel::onHeightChangeImpl,
    };

    return &GENERATED_ArkUIPanelEventsReceiverImpl;
}
const GENERATED_ArkUIPasteButtonEventsReceiver* GetPasteButtonEventsReceiver()
{
    static const GENERATED_ArkUIPasteButtonEventsReceiver GENERATED_ArkUIPasteButtonEventsReceiverImpl {
        PasteButton::onClickImpl,
    };

    return &GENERATED_ArkUIPasteButtonEventsReceiverImpl;
}
const GENERATED_ArkUIPatternLockEventsReceiver* GetPatternLockEventsReceiver()
{
    static const GENERATED_ArkUIPatternLockEventsReceiver GENERATED_ArkUIPatternLockEventsReceiverImpl {
        PatternLock::onPatternCompleteImpl,
    };

    return &GENERATED_ArkUIPatternLockEventsReceiverImpl;
}
const GENERATED_ArkUIPluginComponentEventsReceiver* GetPluginComponentEventsReceiver()
{
    static const GENERATED_ArkUIPluginComponentEventsReceiver GENERATED_ArkUIPluginComponentEventsReceiverImpl {
        PluginComponent::onCompleteImpl,
        PluginComponent::onErrorImpl,
    };

    return &GENERATED_ArkUIPluginComponentEventsReceiverImpl;
}
const GENERATED_ArkUIRadioEventsReceiver* GetRadioEventsReceiver()
{
    static const GENERATED_ArkUIRadioEventsReceiver GENERATED_ArkUIRadioEventsReceiverImpl {
        Radio::onChangeImpl,
    };

    return &GENERATED_ArkUIRadioEventsReceiverImpl;
}
const GENERATED_ArkUIRatingEventsReceiver* GetRatingEventsReceiver()
{
    static const GENERATED_ArkUIRatingEventsReceiver GENERATED_ArkUIRatingEventsReceiverImpl {
        Rating::onChangeImpl,
    };

    return &GENERATED_ArkUIRatingEventsReceiverImpl;
}
const GENERATED_ArkUIRefreshEventsReceiver* GetRefreshEventsReceiver()
{
    static const GENERATED_ArkUIRefreshEventsReceiver GENERATED_ArkUIRefreshEventsReceiverImpl {
        Refresh::onStateChangeImpl,
        Refresh::onRefreshingImpl,
        Refresh::onOffsetChangeImpl,
    };

    return &GENERATED_ArkUIRefreshEventsReceiverImpl;
}
const GENERATED_ArkUIRichEditorEventsReceiver* GetRichEditorEventsReceiver()
{
    static const GENERATED_ArkUIRichEditorEventsReceiver GENERATED_ArkUIRichEditorEventsReceiverImpl {
        RichEditor::onReadyImpl,
        RichEditor::onSelectImpl,
        RichEditor::onSelectionChangeImpl,
        RichEditor::aboutToIMEInputImpl,
        RichEditor::onIMEInputCompleteImpl,
        RichEditor::onDidIMEInputImpl,
        RichEditor::aboutToDeleteImpl,
        RichEditor::onDeleteCompleteImpl,
        RichEditor::onPasteImpl,
        RichEditor::onEditingChangeImpl,
        RichEditor::onSubmitImpl,
        RichEditor::onWillChangeImpl,
        RichEditor::onDidChangeImpl,
        RichEditor::onCutImpl,
        RichEditor::onCopyImpl,
    };

    return &GENERATED_ArkUIRichEditorEventsReceiverImpl;
}
const GENERATED_ArkUIRichTextEventsReceiver* GetRichTextEventsReceiver()
{
    static const GENERATED_ArkUIRichTextEventsReceiver GENERATED_ArkUIRichTextEventsReceiverImpl {
        RichText::onStartImpl,
        RichText::onCompleteImpl,
    };

    return &GENERATED_ArkUIRichTextEventsReceiverImpl;
}
const GENERATED_ArkUISaveButtonEventsReceiver* GetSaveButtonEventsReceiver()
{
    static const GENERATED_ArkUISaveButtonEventsReceiver GENERATED_ArkUISaveButtonEventsReceiverImpl {
        SaveButton::onClickImpl,
    };

    return &GENERATED_ArkUISaveButtonEventsReceiverImpl;
}
const GENERATED_ArkUIScrollEventsReceiver* GetScrollEventsReceiver()
{
    static const GENERATED_ArkUIScrollEventsReceiver GENERATED_ArkUIScrollEventsReceiverImpl {
        Scroll::onScrollImpl,
        Scroll::onDidScrollImpl,
        Scroll::onScrollEdgeImpl,
        Scroll::onScrollStartImpl,
        Scroll::onScrollEndImpl,
        Scroll::onScrollStopImpl,
        Scroll::onScrollFrameBeginImpl,
    };

    return &GENERATED_ArkUIScrollEventsReceiverImpl;
}
const GENERATED_ArkUISearchEventsReceiver* GetSearchEventsReceiver()
{
    static const GENERATED_ArkUISearchEventsReceiver GENERATED_ArkUISearchEventsReceiverImpl {
        Search::onEditChangeImpl,
        Search::onSubmitImpl,
        Search::onChangeImpl,
        Search::onTextSelectionChangeImpl,
        Search::onContentScrollImpl,
        Search::onCopyImpl,
        Search::onCutImpl,
        Search::onPasteImpl,
        Search::onWillInsertImpl,
        Search::onDidInsertImpl,
        Search::onWillDeleteImpl,
        Search::onDidDeleteImpl,
        Search::inputFilterImpl,
    };

    return &GENERATED_ArkUISearchEventsReceiverImpl;
}
const GENERATED_ArkUISelectEventsReceiver* GetSelectEventsReceiver()
{
    static const GENERATED_ArkUISelectEventsReceiver GENERATED_ArkUISelectEventsReceiverImpl {
        Select::onSelectImpl,
    };

    return &GENERATED_ArkUISelectEventsReceiverImpl;
}
const GENERATED_ArkUISliderEventsReceiver* GetSliderEventsReceiver()
{
    static const GENERATED_ArkUISliderEventsReceiver GENERATED_ArkUISliderEventsReceiverImpl {
        Slider::onChangeImpl,
    };

    return &GENERATED_ArkUISliderEventsReceiverImpl;
}
const GENERATED_ArkUIStepperEventsReceiver* GetStepperEventsReceiver()
{
    static const GENERATED_ArkUIStepperEventsReceiver GENERATED_ArkUIStepperEventsReceiverImpl {
        Stepper::onFinishImpl,
        Stepper::onSkipImpl,
        Stepper::onChangeImpl,
        Stepper::onNextImpl,
        Stepper::onPreviousImpl,
    };

    return &GENERATED_ArkUIStepperEventsReceiverImpl;
}
const GENERATED_ArkUISwiperEventsReceiver* GetSwiperEventsReceiver()
{
    static const GENERATED_ArkUISwiperEventsReceiver GENERATED_ArkUISwiperEventsReceiverImpl {
        Swiper::onChangeImpl,
        Swiper::onAnimationStartImpl,
        Swiper::onAnimationEndImpl,
        Swiper::onGestureSwipeImpl,
        Swiper::onContentDidScrollImpl,
    };

    return &GENERATED_ArkUISwiperEventsReceiverImpl;
}
const GENERATED_ArkUITabsEventsReceiver* GetTabsEventsReceiver()
{
    static const GENERATED_ArkUITabsEventsReceiver GENERATED_ArkUITabsEventsReceiverImpl {
        Tabs::onChangeImpl,
        Tabs::onTabBarClickImpl,
        Tabs::onAnimationStartImpl,
        Tabs::onAnimationEndImpl,
        Tabs::onGestureSwipeImpl,
        Tabs::customContentTransitionImpl,
        Tabs::onContentWillChangeImpl,
    };

    return &GENERATED_ArkUITabsEventsReceiverImpl;
}
const GENERATED_ArkUITabContentEventsReceiver* GetTabContentEventsReceiver()
{
    static const GENERATED_ArkUITabContentEventsReceiver GENERATED_ArkUITabContentEventsReceiverImpl {
        TabContent::onWillShowImpl,
        TabContent::onWillHideImpl,
    };

    return &GENERATED_ArkUITabContentEventsReceiverImpl;
}
const GENERATED_ArkUITextEventsReceiver* GetTextEventsReceiver()
{
    static const GENERATED_ArkUITextEventsReceiver GENERATED_ArkUITextEventsReceiverImpl {
        Text::onCopyImpl,
        Text::onTextSelectionChangeImpl,
    };

    return &GENERATED_ArkUITextEventsReceiverImpl;
}
const GENERATED_ArkUITextAreaEventsReceiver* GetTextAreaEventsReceiver()
{
    static const GENERATED_ArkUITextAreaEventsReceiver GENERATED_ArkUITextAreaEventsReceiverImpl {
        TextArea::onSubmitImpl,
        TextArea::onChangeImpl,
        TextArea::onTextSelectionChangeImpl,
        TextArea::onContentScrollImpl,
        TextArea::onEditChangeImpl,
        TextArea::onCopyImpl,
        TextArea::onCutImpl,
        TextArea::onPasteImpl,
        TextArea::onWillInsertImpl,
        TextArea::onDidInsertImpl,
        TextArea::onWillDeleteImpl,
        TextArea::onDidDeleteImpl,
        TextArea::inputFilterImpl,
    };

    return &GENERATED_ArkUITextAreaEventsReceiverImpl;
}
const GENERATED_ArkUITextClockEventsReceiver* GetTextClockEventsReceiver()
{
    static const GENERATED_ArkUITextClockEventsReceiver GENERATED_ArkUITextClockEventsReceiverImpl {
        TextClock::onDateChangeImpl,
    };

    return &GENERATED_ArkUITextClockEventsReceiverImpl;
}
const GENERATED_ArkUITextInputEventsReceiver* GetTextInputEventsReceiver()
{
    static const GENERATED_ArkUITextInputEventsReceiver GENERATED_ArkUITextInputEventsReceiverImpl {
        TextInput::onEditChangedImpl,
        TextInput::onEditChangeImpl,
        TextInput::onSubmitImpl,
        TextInput::onChangeImpl,
        TextInput::onTextSelectionChangeImpl,
        TextInput::onContentScrollImpl,
        TextInput::onCopyImpl,
        TextInput::onCutImpl,
        TextInput::onPasteImpl,
        TextInput::onSecurityStateChangeImpl,
        TextInput::onWillInsertImpl,
        TextInput::onDidInsertImpl,
        TextInput::onWillDeleteImpl,
        TextInput::onDidDeleteImpl,
        TextInput::inputFilterImpl,
    };

    return &GENERATED_ArkUITextInputEventsReceiverImpl;
}
const GENERATED_ArkUITextPickerEventsReceiver* GetTextPickerEventsReceiver()
{
    static const GENERATED_ArkUITextPickerEventsReceiver GENERATED_ArkUITextPickerEventsReceiverImpl {
        TextPicker::onAcceptImpl,
        TextPicker::onCancelImpl,
        TextPicker::onChangeImpl,
    };

    return &GENERATED_ArkUITextPickerEventsReceiverImpl;
}
const GENERATED_ArkUITextTimerEventsReceiver* GetTextTimerEventsReceiver()
{
    static const GENERATED_ArkUITextTimerEventsReceiver GENERATED_ArkUITextTimerEventsReceiverImpl {
        TextTimer::onTimerImpl,
    };

    return &GENERATED_ArkUITextTimerEventsReceiverImpl;
}
const GENERATED_ArkUITimePickerEventsReceiver* GetTimePickerEventsReceiver()
{
    static const GENERATED_ArkUITimePickerEventsReceiver GENERATED_ArkUITimePickerEventsReceiverImpl {
        TimePicker::onChangeImpl,
    };

    return &GENERATED_ArkUITimePickerEventsReceiverImpl;
}
const GENERATED_ArkUIToggleEventsReceiver* GetToggleEventsReceiver()
{
    static const GENERATED_ArkUIToggleEventsReceiver GENERATED_ArkUIToggleEventsReceiverImpl {
        Toggle::onChangeImpl,
    };

    return &GENERATED_ArkUIToggleEventsReceiverImpl;
}
const GENERATED_ArkUIVideoEventsReceiver* GetVideoEventsReceiver()
{
    static const GENERATED_ArkUIVideoEventsReceiver GENERATED_ArkUIVideoEventsReceiverImpl {
        Video::onStartImpl,
        Video::onPauseImpl,
        Video::onFinishImpl,
        Video::onFullscreenChangeImpl,
        Video::onPreparedImpl,
        Video::onSeekingImpl,
        Video::onSeekedImpl,
        Video::onUpdateImpl,
        Video::onErrorImpl,
        Video::onStopImpl,
    };

    return &GENERATED_ArkUIVideoEventsReceiverImpl;
}
const GENERATED_ArkUIWebEventsReceiver* GetWebEventsReceiver()
{
    static const GENERATED_ArkUIWebEventsReceiver GENERATED_ArkUIWebEventsReceiverImpl {
        Web::onPageEndImpl,
        Web::onPageBeginImpl,
        Web::onProgressChangeImpl,
        Web::onTitleReceiveImpl,
        Web::onGeolocationHideImpl,
        Web::onGeolocationShowImpl,
        Web::onRequestSelectedImpl,
        Web::onAlertImpl,
        Web::onBeforeUnloadImpl,
        Web::onConfirmImpl,
        Web::onPromptImpl,
        Web::onConsoleImpl,
        Web::onErrorReceiveImpl,
        Web::onHttpErrorReceiveImpl,
        Web::onDownloadStartImpl,
        Web::onRefreshAccessedHistoryImpl,
        Web::onUrlLoadInterceptImpl,
        Web::onSslErrorReceiveImpl,
        Web::onRenderExited0Impl,
        Web::onShowFileSelectorImpl,
        Web::onRenderExited1Impl,
        Web::onFileSelectorShowImpl,
        Web::onResourceLoadImpl,
        Web::onFullScreenExitImpl,
        Web::onFullScreenEnterImpl,
        Web::onScaleChangeImpl,
        Web::onHttpAuthRequestImpl,
        Web::onInterceptRequestImpl,
        Web::onPermissionRequestImpl,
        Web::onScreenCaptureRequestImpl,
        Web::onContextMenuShowImpl,
        Web::onContextMenuHideImpl,
        Web::onSearchResultReceiveImpl,
        Web::onScrollImpl,
        Web::onSslErrorEventReceiveImpl,
        Web::onSslErrorEventImpl,
        Web::onClientAuthenticationRequestImpl,
        Web::onWindowNewImpl,
        Web::onWindowExitImpl,
        Web::onInterceptKeyEventImpl,
        Web::onTouchIconUrlReceivedImpl,
        Web::onFaviconReceivedImpl,
        Web::onPageVisibleImpl,
        Web::onDataResubmittedImpl,
        Web::onAudioStateChangedImpl,
        Web::onFirstContentfulPaintImpl,
        Web::onFirstMeaningfulPaintImpl,
        Web::onLargestContentfulPaintImpl,
        Web::onLoadInterceptImpl,
        Web::onControllerAttachedImpl,
        Web::onOverScrollImpl,
        Web::onSafeBrowsingCheckResultImpl,
        Web::onNavigationEntryCommittedImpl,
        Web::onIntelligentTrackingPreventionResultImpl,
        Web::onNativeEmbedLifecycleChangeImpl,
        Web::onNativeEmbedVisibilityChangeImpl,
        Web::onNativeEmbedGestureEventImpl,
        Web::onOverrideUrlLoadingImpl,
        Web::onRenderProcessNotRespondingImpl,
        Web::onRenderProcessRespondingImpl,
        Web::onViewportFitChangedImpl,
        Web::onInterceptKeyboardAttachImpl,
        Web::onAdsBlockedImpl,
    };

    return &GENERATED_ArkUIWebEventsReceiverImpl;
}
const GENERATED_ArkUIXComponentEventsReceiver* GetXComponentEventsReceiver()
{
    static const GENERATED_ArkUIXComponentEventsReceiver GENERATED_ArkUIXComponentEventsReceiverImpl {
        XComponent::onLoadImpl,
        XComponent::onDestroyImpl,
    };

    return &GENERATED_ArkUIXComponentEventsReceiverImpl;
}
const GENERATED_ArkUISideBarContainerEventsReceiver* GetSideBarContainerEventsReceiver()
{
    static const GENERATED_ArkUISideBarContainerEventsReceiver GENERATED_ArkUISideBarContainerEventsReceiverImpl {
        SideBarContainer::onChangeImpl,
    };

    return &GENERATED_ArkUISideBarContainerEventsReceiverImpl;
}
const GENERATED_ArkUIWaterFlowEventsReceiver* GetWaterFlowEventsReceiver()
{
    static const GENERATED_ArkUIWaterFlowEventsReceiver GENERATED_ArkUIWaterFlowEventsReceiverImpl {
        WaterFlow::onReachStartImpl,
        WaterFlow::onReachEndImpl,
        WaterFlow::onScrollFrameBeginImpl,
        WaterFlow::onScrollIndexImpl,
    };

    return &GENERATED_ArkUIWaterFlowEventsReceiverImpl;
}
const GENERATED_ArkUIUIExtensionComponentEventsReceiver* GetUIExtensionComponentEventsReceiver()
{
    static const GENERATED_ArkUIUIExtensionComponentEventsReceiver GENERATED_ArkUIUIExtensionComponentEventsReceiverImpl {
        UIExtensionComponent::onTerminatedImpl,
    };

    return &GENERATED_ArkUIUIExtensionComponentEventsReceiverImpl;
}
const GENERATED_ArkUIEventsAPI* g_OverriddenEventsImpl = nullptr;
void GENERATED_SetArkUiEventsAPI(const GENERATED_ArkUIEventsAPI* api)
{
    g_OverriddenEventsImpl = api;
}
const GENERATED_ArkUIEventsAPI* GENERATED_GetArkUiEventsAPI()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = {
        GetAbilityComponentEventsReceiver,
        GetAlphabetIndexerEventsReceiver,
        GetAnimatorEventsReceiver,
        GetCalendarEventsReceiver,
        GetCalendarPickerEventsReceiver,
        GetCanvasEventsReceiver,
        GetCheckboxEventsReceiver,
        GetCheckboxGroupEventsReceiver,
        GetCommonMethodEventsReceiver,
        GetScrollableCommonMethodEventsReceiver,
        GetCounterEventsReceiver,
        GetDatePickerEventsReceiver,
        GetFolderStackEventsReceiver,
        GetFormComponentEventsReceiver,
        GetGridEventsReceiver,
        GetGridItemEventsReceiver,
        GetGridRowEventsReceiver,
        GetImageEventsReceiver,
        GetImageAnimatorEventsReceiver,
        GetImageSpanEventsReceiver,
        GetListEventsReceiver,
        GetListItemEventsReceiver,
        GetLocationButtonEventsReceiver,
        GetMarqueeEventsReceiver,
        GetMenuItemEventsReceiver,
        GetNavDestinationEventsReceiver,
        GetNavRouterEventsReceiver,
        GetNavigationEventsReceiver,
        GetPanelEventsReceiver,
        GetPasteButtonEventsReceiver,
        GetPatternLockEventsReceiver,
        GetPluginComponentEventsReceiver,
        GetRadioEventsReceiver,
        GetRatingEventsReceiver,
        GetRefreshEventsReceiver,
        GetRichEditorEventsReceiver,
        GetRichTextEventsReceiver,
        GetSaveButtonEventsReceiver,
        GetScrollEventsReceiver,
        GetSearchEventsReceiver,
        GetSelectEventsReceiver,
        GetSliderEventsReceiver,
        GetStepperEventsReceiver,
        GetSwiperEventsReceiver,
        GetTabsEventsReceiver,
        GetTabContentEventsReceiver,
        GetTextEventsReceiver,
        GetTextAreaEventsReceiver,
        GetTextClockEventsReceiver,
        GetTextInputEventsReceiver,
        GetTextPickerEventsReceiver,
        GetTextTimerEventsReceiver,
        GetTimePickerEventsReceiver,
        GetToggleEventsReceiver,
        GetVideoEventsReceiver,
        GetWebEventsReceiver,
        GetXComponentEventsReceiver,
        GetSideBarContainerEventsReceiver,
        GetWaterFlowEventsReceiver,
        GetUIExtensionComponentEventsReceiver,
    };
    if ((g_OverriddenEventsImpl) != (nullptr)) {
        return g_OverriddenEventsImpl;
    }
    return &eventsImpl;
}
}

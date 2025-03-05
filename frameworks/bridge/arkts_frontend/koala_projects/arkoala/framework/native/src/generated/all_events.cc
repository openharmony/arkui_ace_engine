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

#include "arkoala_api_generated.h"
#include "events.h"
#include "Serializers.h"

namespace Generated {
    enum PeerEventKind {
        KindAbilityComponent_onConnect = 0,
        KindAbilityComponent_onDisconnect = 1,
        KindAlphabetIndexer_onSelected = 2,
        KindAlphabetIndexer_onSelect = 3,
        KindAlphabetIndexer_onRequestPopupData = 4,
        KindAlphabetIndexer_onPopupSelect = 5,
        KindAlphabetIndexer__onChangeEvent_selected = 6,
        KindAnimator_onStart = 7,
        KindAnimator_onPause = 8,
        KindAnimator_onRepeat = 9,
        KindAnimator_onCancel = 10,
        KindAnimator_onFinish = 11,
        KindAnimator_onFrame = 12,
        KindCalendar_onSelectChange = 13,
        KindCalendar_onRequestData = 14,
        KindCalendarPicker_onChange = 15,
        KindCanvas_onReady = 16,
        KindCheckbox_onChange = 17,
        KindCheckbox__onChangeEvent_select = 18,
        KindCheckboxGroup_onChange = 19,
        KindCheckboxGroup__onChangeEvent_selectAll = 20,
        KindCommonMethod_onChildTouchTest = 21,
        KindCommonMethod_onClick0 = 22,
        KindCommonMethod_onClick1 = 23,
        KindCommonMethod_onHover = 24,
        KindCommonMethod_onAccessibilityHover = 25,
        KindCommonMethod_onMouse = 26,
        KindCommonMethod_onTouch = 27,
        KindCommonMethod_onKeyEvent = 28,
        KindCommonMethod_onKeyPreIme = 29,
        KindCommonMethod_onFocus = 30,
        KindCommonMethod_onBlur = 31,
        KindCommonMethod_onAppear = 32,
        KindCommonMethod_onDisAppear = 33,
        KindCommonMethod_onAttach = 34,
        KindCommonMethod_onDetach = 35,
        KindCommonMethod_onAreaChange = 36,
        KindCommonMethod_onDragStart = 37,
        KindCommonMethod_onDragEnter = 38,
        KindCommonMethod_onDragMove = 39,
        KindCommonMethod_onDragLeave = 40,
        KindCommonMethod_onDrop = 41,
        KindCommonMethod_onDragEnd = 42,
        KindCommonMethod_onPreDrag = 43,
        KindCommonMethod_accessibilityVirtualNode = 44,
        KindCommonMethod_onGestureJudgeBegin = 45,
        KindCommonMethod_onGestureRecognizerJudgeBegin0 = 46,
        KindCommonMethod_onGestureRecognizerJudgeBegin1 = 47,
        KindCommonMethod_shouldBuiltInRecognizerParallelWith = 48,
        KindCommonMethod_onTouchIntercept = 49,
        KindCommonMethod_onSizeChange = 50,
        KindCommonMethod_background = 51,
        KindCommonMethod_bindContextMenu0 = 52,
        KindCommonMethod_bindContextMenu1 = 53,
        KindCommonMethod_bindContentCover0 = 54,
        KindCommonMethod_bindContentCover1 = 55,
        KindCommonMethod_bindSheet = 56,
        KindCommonMethod_onVisibleAreaChange = 57,
        KindScrollableCommonMethod_onScroll = 58,
        KindScrollableCommonMethod_onDidScroll = 59,
        KindScrollableCommonMethod_onReachStart = 60,
        KindScrollableCommonMethod_onReachEnd = 61,
        KindScrollableCommonMethod_onScrollStart = 62,
        KindScrollableCommonMethod_onScrollStop = 63,
        KindCounter_onInc = 64,
        KindCounter_onDec = 65,
        KindDatePicker_onChange = 66,
        KindDatePicker_onDateChange = 67,
        KindDatePicker__onChangeEvent_selected = 68,
        KindEmbeddedComponent_onTerminated = 69,
        KindEmbeddedComponent_onError = 70,
        KindFolderStack_onFolderStateChange = 71,
        KindFolderStack_onHoverStatusChange = 72,
        KindFormComponent_onAcquired = 73,
        KindFormComponent_onError = 74,
        KindFormComponent_onRouter = 75,
        KindFormComponent_onUninstall = 76,
        KindFormComponent_onLoad = 77,
        KindGauge_description = 78,
        KindGrid_onScrollBarUpdate = 79,
        KindGrid_onScrollIndex = 80,
        KindGrid_onItemDragStart = 81,
        KindGrid_onItemDragEnter = 82,
        KindGrid_onItemDragMove = 83,
        KindGrid_onItemDragLeave = 84,
        KindGrid_onItemDrop = 85,
        KindGrid_onScroll = 86,
        KindGrid_onReachStart = 87,
        KindGrid_onReachEnd = 88,
        KindGrid_onScrollStart = 89,
        KindGrid_onScrollStop = 90,
        KindGrid_onScrollFrameBegin = 91,
        KindGridItem_onSelect = 92,
        KindGridItem__onChangeEvent_selected = 93,
        KindGridRow_onBreakpointChange = 94,
        KindImage_onComplete = 95,
        KindImage_onError = 96,
        KindImage_onFinish = 97,
        KindImageAnimator_onStart = 98,
        KindImageAnimator_onPause = 99,
        KindImageAnimator_onRepeat = 100,
        KindImageAnimator_onCancel = 101,
        KindImageAnimator_onFinish = 102,
        KindImageSpan_onComplete = 103,
        KindImageSpan_onError = 104,
        KindList_onScroll = 105,
        KindList_onScrollIndex = 106,
        KindList_onScrollVisibleContentChange = 107,
        KindList_onReachStart = 108,
        KindList_onReachEnd = 109,
        KindList_onScrollStart = 110,
        KindList_onScrollStop = 111,
        KindList_onItemDelete = 112,
        KindList_onItemMove = 113,
        KindList_onItemDragStart = 114,
        KindList_onItemDragEnter = 115,
        KindList_onItemDragMove = 116,
        KindList_onItemDragLeave = 117,
        KindList_onItemDrop = 118,
        KindList_onScrollFrameBegin = 119,
        KindListItem_onSelect = 120,
        KindListItem__onChangeEvent_selected = 121,
        KindLocationButton_onClick = 122,
        KindMarquee_onStart = 123,
        KindMarquee_onBounce = 124,
        KindMarquee_onFinish = 125,
        KindMenuItem_onChange = 126,
        KindMenuItem__onChangeEvent_selected = 127,
        KindNavDestination_onShown = 128,
        KindNavDestination_onHidden = 129,
        KindNavDestination_onBackPressed = 130,
        KindNavDestination_onReady = 131,
        KindNavDestination_onWillAppear = 132,
        KindNavDestination_onWillDisappear = 133,
        KindNavDestination_onWillShow = 134,
        KindNavDestination_onWillHide = 135,
        KindNavRouter_onStateChange = 136,
        KindPanel_onChange = 137,
        KindPanel_onHeightChange = 138,
        KindPanel__onChangeEvent_mode = 139,
        KindPasteButton_onClick = 140,
        KindPatternLock_onPatternComplete = 141,
        KindPatternLock_onDotConnect = 142,
        KindPluginComponent_onComplete = 143,
        KindPluginComponent_onError = 144,
        KindRadio_onChange = 145,
        KindRadio__onChangeEvent_checked = 146,
        KindRating_onChange = 147,
        KindRating__onChangeEvent_rating = 148,
        KindRefresh_onStateChange = 149,
        KindRefresh_onRefreshing = 150,
        KindRefresh_onOffsetChange = 151,
        KindRefresh__onChangeEvent_refreshing = 152,
        KindRichEditor_onReady = 153,
        KindRichEditor_onSelect = 154,
        KindRichEditor_onSelectionChange = 155,
        KindRichEditor_aboutToIMEInput = 156,
        KindRichEditor_onIMEInputComplete = 157,
        KindRichEditor_onDidIMEInput = 158,
        KindRichEditor_aboutToDelete = 159,
        KindRichEditor_onDeleteComplete = 160,
        KindRichEditor_onPaste = 161,
        KindRichEditor_onEditingChange = 162,
        KindRichEditor_onSubmit = 163,
        KindRichEditor_onWillChange = 164,
        KindRichEditor_onDidChange = 165,
        KindRichEditor_onCut = 166,
        KindRichEditor_onCopy = 167,
        KindRichEditor_bindSelectionMenu = 168,
        KindRichEditor_customKeyboard = 169,
        KindRichText_onStart = 170,
        KindRichText_onComplete = 171,
        KindSaveButton_onClick = 172,
        KindScroll_onScroll = 173,
        KindScroll_onDidScroll = 174,
        KindScroll_onScrollEdge = 175,
        KindScroll_onScrollStart = 176,
        KindScroll_onScrollEnd = 177,
        KindScroll_onScrollStop = 178,
        KindScroll_onScrollFrameBegin = 179,
        KindSearch_onEditChange = 180,
        KindSearch_onSubmit0 = 181,
        KindSearch_onSubmit1 = 182,
        KindSearch_onChange = 183,
        KindSearch_onTextSelectionChange = 184,
        KindSearch_onContentScroll = 185,
        KindSearch_onCopy = 186,
        KindSearch_onCut = 187,
        KindSearch_onPaste = 188,
        KindSearch_onWillInsert = 189,
        KindSearch_onDidInsert = 190,
        KindSearch_onWillDelete = 191,
        KindSearch_onDidDelete = 192,
        KindSearch_customKeyboard = 193,
        KindSearch__onChangeEvent_value = 194,
        KindSelect_onSelect = 195,
        KindSelect__onChangeEvent_selected = 196,
        KindSelect__onChangeEvent_value = 197,
        KindSlider_onChange = 198,
        KindSlider__onChangeEvent_value = 199,
        KindStepper_onFinish = 200,
        KindStepper_onSkip = 201,
        KindStepper_onChange = 202,
        KindStepper_onNext = 203,
        KindStepper_onPrevious = 204,
        KindStepper__onChangeEvent_index = 205,
        KindSwiper_onChange = 206,
        KindSwiper_onAnimationStart = 207,
        KindSwiper_onAnimationEnd = 208,
        KindSwiper_onGestureSwipe = 209,
        KindSwiper_onContentDidScroll = 210,
        KindSwiper__onChangeEvent_index = 211,
        KindIndicatorComponent_onChange = 212,
        KindTabs_onChange = 213,
        KindTabs_onTabBarClick = 214,
        KindTabs_onAnimationStart = 215,
        KindTabs_onAnimationEnd = 216,
        KindTabs_onGestureSwipe = 217,
        KindTabs_customContentTransition = 218,
        KindTabs_onContentWillChange = 219,
        KindTabs__onChangeEvent_index = 220,
        KindTabContent_onWillShow = 221,
        KindTabContent_onWillHide = 222,
        KindText_onCopy = 223,
        KindText_onTextSelectionChange = 224,
        KindText_bindSelectionMenu = 225,
        KindTextArea_onSubmit0 = 226,
        KindTextArea_onSubmit1 = 227,
        KindTextArea_onChange = 228,
        KindTextArea_onTextSelectionChange = 229,
        KindTextArea_onContentScroll = 230,
        KindTextArea_onEditChange = 231,
        KindTextArea_onCopy = 232,
        KindTextArea_onCut = 233,
        KindTextArea_onPaste = 234,
        KindTextArea_onWillInsert = 235,
        KindTextArea_onDidInsert = 236,
        KindTextArea_onWillDelete = 237,
        KindTextArea_onDidDelete = 238,
        KindTextArea_customKeyboard = 239,
        KindTextArea__onChangeEvent_text = 240,
        KindTextClock_onDateChange = 241,
        KindTextInput_onEditChanged = 242,
        KindTextInput_onEditChange = 243,
        KindTextInput_onSubmit = 244,
        KindTextInput_onChange = 245,
        KindTextInput_onTextSelectionChange = 246,
        KindTextInput_onContentScroll = 247,
        KindTextInput_onCopy = 248,
        KindTextInput_onCut = 249,
        KindTextInput_onPaste = 250,
        KindTextInput_showUnit = 251,
        KindTextInput_onSecurityStateChange = 252,
        KindTextInput_onWillInsert = 253,
        KindTextInput_onDidInsert = 254,
        KindTextInput_onWillDelete = 255,
        KindTextInput_onDidDelete = 256,
        KindTextInput_customKeyboard = 257,
        KindTextInput__onChangeEvent_text = 258,
        KindTextPicker_onAccept = 259,
        KindTextPicker_onCancel = 260,
        KindTextPicker_onChange = 261,
        KindTextPicker__onChangeEvent_selected = 262,
        KindTextPicker__onChangeEvent_value = 263,
        KindTextTimer_onTimer = 264,
        KindTimePicker_onChange = 265,
        KindTimePicker__onChangeEvent_selected = 266,
        KindToggle_onChange = 267,
        KindToggle__onChangeEvent_isOn = 268,
        KindVideo_onStart = 269,
        KindVideo_onPause = 270,
        KindVideo_onFinish = 271,
        KindVideo_onFullscreenChange = 272,
        KindVideo_onPrepared = 273,
        KindVideo_onSeeking = 274,
        KindVideo_onSeeked = 275,
        KindVideo_onUpdate = 276,
        KindVideo_onError = 277,
        KindVideo_onStop = 278,
        KindWeb_onPageEnd = 279,
        KindWeb_onPageBegin = 280,
        KindWeb_onProgressChange = 281,
        KindWeb_onTitleReceive = 282,
        KindWeb_onGeolocationHide = 283,
        KindWeb_onGeolocationShow = 284,
        KindWeb_onRequestSelected = 285,
        KindWeb_onAlert = 286,
        KindWeb_onBeforeUnload = 287,
        KindWeb_onConfirm = 288,
        KindWeb_onPrompt = 289,
        KindWeb_onConsole = 290,
        KindWeb_onErrorReceive = 291,
        KindWeb_onHttpErrorReceive = 292,
        KindWeb_onDownloadStart = 293,
        KindWeb_onRefreshAccessedHistory = 294,
        KindWeb_onUrlLoadIntercept = 295,
        KindWeb_onSslErrorReceive = 296,
        KindWeb_onRenderExited0 = 297,
        KindWeb_onRenderExited1 = 298,
        KindWeb_onShowFileSelector = 299,
        KindWeb_onFileSelectorShow = 300,
        KindWeb_onResourceLoad = 301,
        KindWeb_onFullScreenExit = 302,
        KindWeb_onFullScreenEnter = 303,
        KindWeb_onScaleChange = 304,
        KindWeb_onHttpAuthRequest = 305,
        KindWeb_onInterceptRequest = 306,
        KindWeb_onPermissionRequest = 307,
        KindWeb_onScreenCaptureRequest = 308,
        KindWeb_onContextMenuShow = 309,
        KindWeb_onContextMenuHide = 310,
        KindWeb_onSearchResultReceive = 311,
        KindWeb_onScroll = 312,
        KindWeb_onSslErrorEventReceive = 313,
        KindWeb_onSslErrorEvent = 314,
        KindWeb_onClientAuthenticationRequest = 315,
        KindWeb_onWindowNew = 316,
        KindWeb_onWindowExit = 317,
        KindWeb_onInterceptKeyEvent = 318,
        KindWeb_onTouchIconUrlReceived = 319,
        KindWeb_onFaviconReceived = 320,
        KindWeb_onPageVisible = 321,
        KindWeb_onDataResubmitted = 322,
        KindWeb_onAudioStateChanged = 323,
        KindWeb_onFirstContentfulPaint = 324,
        KindWeb_onFirstMeaningfulPaint = 325,
        KindWeb_onLargestContentfulPaint = 326,
        KindWeb_onLoadIntercept = 327,
        KindWeb_onControllerAttached = 328,
        KindWeb_onOverScroll = 329,
        KindWeb_onSafeBrowsingCheckResult = 330,
        KindWeb_onNavigationEntryCommitted = 331,
        KindWeb_onIntelligentTrackingPreventionResult = 332,
        KindWeb_onNativeEmbedLifecycleChange = 333,
        KindWeb_onNativeEmbedVisibilityChange = 334,
        KindWeb_onNativeEmbedGestureEvent = 335,
        KindWeb_onOverrideUrlLoading = 336,
        KindWeb_onRenderProcessNotResponding = 337,
        KindWeb_onRenderProcessResponding = 338,
        KindWeb_onViewportFitChanged = 339,
        KindWeb_onInterceptKeyboardAttach = 340,
        KindWeb_onAdsBlocked = 341,
        KindWeb_bindSelectionMenu = 342,
        KindXComponent_onLoad = 343,
        KindXComponent_onDestroy = 344,
        KindSideBarContainer_onChange = 345,
        KindSideBarContainer__onChangeEvent_showSideBar = 346,
        KindWaterFlow_onReachStart = 347,
        KindWaterFlow_onReachEnd = 348,
        KindWaterFlow_onScrollFrameBegin = 349,
        KindWaterFlow_onScrollIndex = 350,
        KindUIExtensionComponent_onRemoteReady = 351,
        KindUIExtensionComponent_onResult = 352,
        KindUIExtensionComponent_onRelease = 353,
        KindUIExtensionComponent_onError = 354,
        KindUIExtensionComponent_onTerminated = 355,
    };

    namespace AbilityComponent {
    void onConnectImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAbilityComponent_onConnect);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onDisconnectImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onSelected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onSelectImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onRequestPopupDataImpl(Ark_Int32 nodeId,
                                const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onRequestPopupData);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onPopupSelectImpl(Ark_Int32 nodeId,
                           const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAlphabetIndexer_onPopupSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAlphabetIndexer__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Animator {
    void onStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onPauseImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onPause);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onRepeatImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onRepeat);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onCancelImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onCancel);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onFinish);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFrameImpl(Ark_Int32 nodeId,
                     const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindAnimator_onFrame);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Calendar {
    void onSelectChangeImpl(Ark_Int32 nodeId,
                            const Ark_CalendarSelectedDate event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCalendar_onSelectChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCalendarSelectedDate(event);
        sendEvent(&_eventBuffer);
    }
    void onRequestDataImpl(Ark_Int32 nodeId,
                           const Ark_CalendarRequestedData event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCalendar_onRequestData);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCalendarRequestedData(event);
        sendEvent(&_eventBuffer);
    }
    }
    namespace CalendarPicker {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Date parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCalendarPicker_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt64(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Canvas {
    void onReadyImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCheckbox_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(value);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectImpl(Ark_Int32 nodeId,
                                   const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCheckbox__onChangeEvent_select);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace CheckboxGroup {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_CheckboxGroupResult value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCheckboxGroup_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCheckboxGroupResult(value);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectAllImpl(Ark_Int32 nodeId,
                                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCheckboxGroup__onChangeEvent_selectAll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace CommonMethod {
    void onChildTouchTestImpl(Ark_Int32 nodeId,
                              const Array_TouchTestInfo value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onChildTouchTest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(value.length);
        for (int i = 0; i < value.length; i++) {
            const Ark_TouchTestInfo value_element = value.array[i];
            _eventBufferSerializer.writeTouchTestInfo(value_element);
        }
        sendEvent(&_eventBuffer);
    }
    void onClick0Impl(Ark_Int32 nodeId,
                      const Ark_ClickEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onClick0);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeClickEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onClick1Impl(Ark_Int32 nodeId,
                      const Ark_ClickEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onClick1);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeClickEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onHoverImpl(Ark_Int32 nodeId,
                     const Ark_Boolean isHover,
                     const Ark_HoverEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onMouse);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeMouseEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onTouchImpl(Ark_Int32 nodeId,
                     const Ark_TouchEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onTouch);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTouchEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onKeyEventImpl(Ark_Int32 nodeId,
                        const Ark_KeyEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onKeyEvent);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeKeyEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onKeyPreImeImpl(Ark_Int32 nodeId,
                         const Ark_KeyEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onKeyPreIme);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeKeyEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFocusImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onFocus);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onBlurImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onBlur);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onAppearImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onAppear);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onDisAppearImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDisAppear);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onAttachImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onAttach);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onDetachImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDetach);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onAreaChangeImpl(Ark_Int32 nodeId,
                          const Ark_Area oldValue,
                          const Ark_Area newValue)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDragStart);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDragEnter);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDragMove);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDragLeave);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDrop);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onDragEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDragEvent(event);
        Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
        extraParams_type = runtimeType(extraParams);
        _eventBufferSerializer.writeInt8(extraParams_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
            const auto extraParams_value = extraParams.value;
            _eventBufferSerializer.writeString(extraParams_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onPreDragImpl(Ark_Int32 nodeId,
                       const Ark_PreDragStatus parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onPreDrag);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_PreDragStatus>(parameter));
        sendEvent(&_eventBuffer);
    }
    void accessibilityVirtualNodeImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_accessibilityVirtualNode);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onGestureJudgeBeginImpl(Ark_Int32 nodeId,
                                 const Ark_GestureInfo gestureInfo,
                                 const Ark_BaseGestureEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onGestureJudgeBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeGestureInfo(gestureInfo);
        _eventBufferSerializer.writeBaseGestureEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onGestureRecognizerJudgeBegin0Impl(Ark_Int32 nodeId,
                                            const Ark_BaseGestureEvent event,
                                            const Ark_GestureRecognizer current,
                                            const Array_GestureRecognizer recognizers)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onGestureRecognizerJudgeBegin0);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBaseGestureEvent(event);
        _eventBufferSerializer.writeGestureRecognizer(current);
        _eventBufferSerializer.writeInt32(recognizers.length);
        for (int i = 0; i < recognizers.length; i++) {
            const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
            _eventBufferSerializer.writeGestureRecognizer(recognizers_element);
        }
        sendEvent(&_eventBuffer);
    }
    void onGestureRecognizerJudgeBegin1Impl(Ark_Int32 nodeId,
                                            const Ark_BaseGestureEvent event,
                                            const Ark_GestureRecognizer current,
                                            const Array_GestureRecognizer recognizers)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onGestureRecognizerJudgeBegin1);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBaseGestureEvent(event);
        _eventBufferSerializer.writeGestureRecognizer(current);
        _eventBufferSerializer.writeInt32(recognizers.length);
        for (int i = 0; i < recognizers.length; i++) {
            const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
            _eventBufferSerializer.writeGestureRecognizer(recognizers_element);
        }
        sendEvent(&_eventBuffer);
    }
    void shouldBuiltInRecognizerParallelWithImpl(Ark_Int32 nodeId,
                                                 const Ark_GestureRecognizer current,
                                                 const Array_GestureRecognizer others)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_shouldBuiltInRecognizerParallelWith);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeGestureRecognizer(current);
        _eventBufferSerializer.writeInt32(others.length);
        for (int i = 0; i < others.length; i++) {
            const Ark_GestureRecognizer others_element = others.array[i];
            _eventBufferSerializer.writeGestureRecognizer(others_element);
        }
        sendEvent(&_eventBuffer);
    }
    void onTouchInterceptImpl(Ark_Int32 nodeId,
                              const Ark_TouchEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onTouchIntercept);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTouchEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSizeChangeImpl(Ark_Int32 nodeId,
                          const Ark_SizeOptions oldValue,
                          const Ark_SizeOptions newValue)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onSizeChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeSizeOptions(oldValue);
        _eventBufferSerializer.writeSizeOptions(newValue);
        sendEvent(&_eventBuffer);
    }
    void backgroundImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_background);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void bindContextMenu0Impl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_bindContextMenu0);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void bindContextMenu1Impl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_bindContextMenu1);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void bindContentCover0Impl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_bindContentCover0);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void bindContentCover1Impl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_bindContentCover1);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void bindSheetImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_bindSheet);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onVisibleAreaChangeImpl(Ark_Int32 nodeId,
                                 const Ark_Boolean isExpanding,
                                 const Ark_Number currentRatio)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCommonMethod_onVisibleAreaChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(isExpanding);
        _eventBufferSerializer.writeNumber(currentRatio);
        sendEvent(&_eventBuffer);
    }
    }
    namespace ScrollableCommonMethod {
    void onScrollImpl(Ark_Int32 nodeId,
                      const Ark_Number first,
                      const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onDidScrollImpl(Ark_Int32 nodeId,
                         const Ark_Number xOffset,
                         const Ark_Number yOffset,
                         const Ark_ScrollState scrollState)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onDidScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(xOffset);
        _eventBufferSerializer.writeNumber(yOffset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
        sendEvent(&_eventBuffer);
    }
    void onReachStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onReachStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onReachEndImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onReachEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScrollStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStopImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScrollableCommonMethod_onScrollStop);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Counter {
    void onIncImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindCounter_onInc);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onDecImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindDatePicker_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDatePickerResult(value);
        sendEvent(&_eventBuffer);
    }
    void onDateChangeImpl(Ark_Int32 nodeId,
                          const Ark_Date parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindDatePicker_onDateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt64(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Date parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindDatePicker__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt64(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace EmbeddedComponent {
    void onTerminatedImpl(Ark_Int32 nodeId,
                          const Ark_TerminationInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindEmbeddedComponent_onTerminated);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTerminationInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId,
                     const Ark_BusinessError err)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindEmbeddedComponent_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBusinessError(err);
        sendEvent(&_eventBuffer);
    }
    }
    namespace FolderStack {
    void onFolderStateChangeImpl(Ark_Int32 nodeId,
                                 const Ark_OnFoldStatusChangeInfo event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFolderStack_onFolderStateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnFoldStatusChangeInfo(event);
        sendEvent(&_eventBuffer);
    }
    void onHoverStatusChangeImpl(Ark_Int32 nodeId,
                                 const Ark_HoverEventParam param)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFolderStack_onHoverStatusChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeHoverEventParam(param);
        sendEvent(&_eventBuffer);
    }
    }
    namespace FormComponent {
    void onAcquiredImpl(Ark_Int32 nodeId,
                        const Ark_FormCallbackInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFormComponent_onAcquired);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeFormCallbackInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId,
                     const Ark_Literal_Number_errcode_String_msg info)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFormComponent_onRouter);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCustomObject("Any", info);
        sendEvent(&_eventBuffer);
    }
    void onUninstallImpl(Ark_Int32 nodeId,
                         const Ark_FormCallbackInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFormComponent_onUninstall);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeFormCallbackInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onLoadImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindFormComponent_onLoad);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Gauge {
    void descriptionImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGauge_description);
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onItemDrop);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeItemDragInfo(event);
        _eventBufferSerializer.writeNumber(itemIndex);
        _eventBufferSerializer.writeNumber(insertIndex);
        _eventBufferSerializer.writeBoolean(isSuccess);
        sendEvent(&_eventBuffer);
    }
    void onScrollImpl(Ark_Int32 nodeId,
                      const Ark_Number first,
                      const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onReachStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onReachStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onReachEndImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onReachEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onScrollStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStopImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onScrollStop);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                                const Ark_Number offset,
                                const Ark_ScrollState state)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGrid_onScrollFrameBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(offset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
        sendEvent(&_eventBuffer);
    }
    }
    namespace GridItem {
    void onSelectImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGridItem_onSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindGridItem__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace GridRow {
    void onBreakpointChangeImpl(Ark_Int32 nodeId,
                                const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImage_onComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImage_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeImageError(error);
        sendEvent(&_eventBuffer);
    }
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImage_onFinish);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace ImageAnimator {
    void onStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageAnimator_onStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onPauseImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageAnimator_onPause);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onRepeatImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageAnimator_onRepeat);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onCancelImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageAnimator_onCancel);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageSpan_onComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeImageLoadResult(result);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId,
                     const Ark_ImageError error)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindImageSpan_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeImageError(error);
        sendEvent(&_eventBuffer);
    }
    }
    namespace List {
    void onScrollImpl(Ark_Int32 nodeId,
                      const Ark_Number first,
                      const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onScrollIndexImpl(Ark_Int32 nodeId,
                           const Ark_Number start,
                           const Ark_Number end,
                           const Ark_Number center)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onScrollVisibleContentChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeVisibleListContentInfo(start);
        _eventBufferSerializer.writeVisibleListContentInfo(end);
        sendEvent(&_eventBuffer);
    }
    void onReachStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onReachStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onReachEndImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onReachEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onScrollStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStopImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onScrollStop);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onItemDeleteImpl(Ark_Int32 nodeId,
                          const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindList_onScrollFrameBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(offset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
        sendEvent(&_eventBuffer);
    }
    }
    namespace ListItem {
    void onSelectImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindListItem_onSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindListItem__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace LocationButton {
    void onClickImpl(Ark_Int32 nodeId,
                     const Ark_ClickEvent event,
                     const Ark_LocationButtonOnClickResult result)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindLocationButton_onClick);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeClickEvent(event);
        _eventBufferSerializer.writeInt32(static_cast<Ark_LocationButtonOnClickResult>(result));
        sendEvent(&_eventBuffer);
    }
    }
    namespace Marquee {
    void onStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindMarquee_onStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onBounceImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindMarquee_onBounce);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindMarquee_onFinish);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace MenuItem {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindMenuItem_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindMenuItem__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace NavDestination {
    void onShownImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onShown);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onHiddenImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onHidden);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onBackPressedImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onBackPressed);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onReadyImpl(Ark_Int32 nodeId,
                     const Ark_NavDestinationContext parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onReady);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNavDestinationContext(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWillAppearImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onWillAppear);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onWillDisappearImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onWillDisappear);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onWillShowImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onWillShow);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onWillHideImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavDestination_onWillHide);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace NavRouter {
    void onStateChangeImpl(Ark_Int32 nodeId,
                           const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindNavRouter_onStateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPanel_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(width);
        _eventBufferSerializer.writeNumber(height);
        _eventBufferSerializer.writeInt32(static_cast<Ark_PanelMode>(mode));
        sendEvent(&_eventBuffer);
    }
    void onHeightChangeImpl(Ark_Int32 nodeId,
                            const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPanel_onHeightChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_modeImpl(Ark_Int32 nodeId,
                                 const Ark_PanelMode mode)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPanel__onChangeEvent_mode);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_PanelMode>(mode));
        sendEvent(&_eventBuffer);
    }
    }
    namespace PasteButton {
    void onClickImpl(Ark_Int32 nodeId,
                     const Ark_ClickEvent event,
                     const Ark_PasteButtonOnClickResult result)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPasteButton_onClick);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeClickEvent(event);
        _eventBufferSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
        sendEvent(&_eventBuffer);
    }
    }
    namespace PatternLock {
    void onPatternCompleteImpl(Ark_Int32 nodeId,
                               const Array_Number input)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPatternLock_onPatternComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(input.length);
        for (int i = 0; i < input.length; i++) {
            const Ark_Number input_element = input.array[i];
            _eventBufferSerializer.writeNumber(input_element);
        }
        sendEvent(&_eventBuffer);
    }
    void onDotConnectImpl(Ark_Int32 nodeId,
                          const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPatternLock_onDotConnect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace PluginComponent {
    void onCompleteImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPluginComponent_onComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId,
                     const Ark_PluginErrorData info)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindPluginComponent_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writePluginErrorData(info);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Radio {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRadio_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_checkedImpl(Ark_Int32 nodeId,
                                    const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRadio__onChangeEvent_checked);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Rating {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRating_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_ratingImpl(Ark_Int32 nodeId,
                                   const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRating__onChangeEvent_rating);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Refresh {
    void onStateChangeImpl(Ark_Int32 nodeId,
                           const Ark_RefreshStatus state)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRefresh_onStateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
        sendEvent(&_eventBuffer);
    }
    void onRefreshingImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRefresh_onRefreshing);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onOffsetChangeImpl(Ark_Int32 nodeId,
                            const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRefresh_onOffsetChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_refreshingImpl(Ark_Int32 nodeId,
                                       const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRefresh__onChangeEvent_refreshing);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace RichEditor {
    void onReadyImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onReady);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onSelectImpl(Ark_Int32 nodeId,
                      const Ark_RichEditorSelection parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorSelection(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSelectionChangeImpl(Ark_Int32 nodeId,
                               const Ark_RichEditorRange parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onSelectionChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorRange(parameter);
        sendEvent(&_eventBuffer);
    }
    void aboutToIMEInputImpl(Ark_Int32 nodeId,
                             const Ark_RichEditorInsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_aboutToIMEInput);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onIMEInputCompleteImpl(Ark_Int32 nodeId,
                                const Ark_RichEditorTextSpanResult parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onIMEInputComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorTextSpanResult(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidIMEInputImpl(Ark_Int32 nodeId,
                           const Ark_TextRange parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onDidIMEInput);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTextRange(parameter);
        sendEvent(&_eventBuffer);
    }
    void aboutToDeleteImpl(Ark_Int32 nodeId,
                           const Ark_RichEditorDeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_aboutToDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDeleteCompleteImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onDeleteComplete);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onPasteImpl(Ark_Int32 nodeId,
                     const Opt_PasteEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onPaste);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            _eventBufferSerializer.writePasteEvent(event_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onEditingChangeImpl(Ark_Int32 nodeId,
                             const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onEditingChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSubmitImpl(Ark_Int32 nodeId,
                      const Ark_EnterKeyType enterKey,
                      const Ark_SubmitEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onSubmit);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
        _eventBufferSerializer.writeSubmitEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onWillChangeImpl(Ark_Int32 nodeId,
                          const Ark_RichEditorChangeValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onWillChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRichEditorChangeValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidChangeImpl(Ark_Int32 nodeId,
                         const Ark_TextRange rangeBefore,
                         const Ark_TextRange rangeAfter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onDidChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTextRange(rangeBefore);
        _eventBufferSerializer.writeTextRange(rangeAfter);
        sendEvent(&_eventBuffer);
    }
    void onCutImpl(Ark_Int32 nodeId,
                   const Ark_CutEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onCut);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCutEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onCopyImpl(Ark_Int32 nodeId,
                    const Ark_CopyEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_onCopy);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeCopyEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void bindSelectionMenuImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_bindSelectionMenu);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void customKeyboardImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichEditor_customKeyboard);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace RichText {
    void onStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindRichText_onStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onCompleteImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSaveButton_onClick);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeClickEvent(event);
        _eventBufferSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
        sendEvent(&_eventBuffer);
    }
    }
    namespace Scroll {
    void onScrollImpl(Ark_Int32 nodeId,
                      const Ark_Number first,
                      const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onDidScrollImpl(Ark_Int32 nodeId,
                         const Ark_Number xOffset,
                         const Ark_Number yOffset,
                         const Ark_ScrollState scrollState)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onDidScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(xOffset);
        _eventBufferSerializer.writeNumber(yOffset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
        sendEvent(&_eventBuffer);
    }
    void onScrollEdgeImpl(Ark_Int32 nodeId,
                          const Ark_Edge side)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScrollEdge);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_Edge>(side));
        sendEvent(&_eventBuffer);
    }
    void onScrollStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScrollStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollEndImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScrollEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollStopImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScrollStop);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                                const Ark_Number offset,
                                const Ark_ScrollState state)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindScroll_onScrollFrameBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(offset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
        sendEvent(&_eventBuffer);
    }
    }
    namespace Search {
    void onEditChangeImpl(Ark_Int32 nodeId,
                          const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onEditChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSubmit0Impl(Ark_Int32 nodeId,
                       const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onSubmit0);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onSubmit1Impl(Ark_Int32 nodeId,
                       const Ark_String searchContent,
                       const Opt_SubmitEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onSubmit1);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(searchContent);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            _eventBufferSerializer.writeSubmitEvent(event_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_String value,
                      const Opt_PreviewText previewText)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(value);
        Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
        previewText_type = runtimeType(previewText);
        _eventBufferSerializer.writeInt8(previewText_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onContentScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(totalOffsetX);
        _eventBufferSerializer.writeNumber(totalOffsetY);
        sendEvent(&_eventBuffer);
    }
    void onCopyImpl(Ark_Int32 nodeId,
                    const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onCopy);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onCutImpl(Ark_Int32 nodeId,
                   const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onCut);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onPasteImpl(Ark_Int32 nodeId,
                     const Ark_String content,
                     const Ark_PasteEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onPaste);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(content);
        _eventBufferSerializer.writePasteEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onWillInsertImpl(Ark_Int32 nodeId,
                          const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onWillInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidInsertImpl(Ark_Int32 nodeId,
                         const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onDidInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWillDeleteImpl(Ark_Int32 nodeId,
                          const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onWillDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidDeleteImpl(Ark_Int32 nodeId,
                         const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_onDidDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void customKeyboardImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch_customKeyboard);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_valueImpl(Ark_Int32 nodeId,
                                  const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSearch__onChangeEvent_value);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Select {
    void onSelectImpl(Ark_Int32 nodeId,
                      const Ark_Number index,
                      const Ark_String value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSelect_onSelect);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        _eventBufferSerializer.writeString(value);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Union_Number_Resource selected)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSelect__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
        selected_type = selected.selector;
        if (selected_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto selected_0 = selected.value0;
            _eventBufferSerializer.writeNumber(selected_0);
        }
        else if (selected_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto selected_1 = selected.value1;
            _eventBufferSerializer.writeResource(selected_1);
        }
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_valueImpl(Ark_Int32 nodeId,
                                  const Ark_ResourceStr value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSelect__onChangeEvent_value);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
        value_type = value.selector;
        if (value_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto value_0 = value.value0;
            _eventBufferSerializer.writeString(value_0);
        }
        else if (value_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto value_1 = value.value1;
            _eventBufferSerializer.writeResource(value_1);
        }
        sendEvent(&_eventBuffer);
    }
    }
    namespace Slider {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number value,
                      const Ark_SliderChangeMode mode)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSlider_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(value);
        _eventBufferSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_valueImpl(Ark_Int32 nodeId,
                                  const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSlider__onChangeEvent_value);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Stepper {
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper_onFinish);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onSkipImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper_onSkip);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number first,
                      const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onNextImpl(Ark_Int32 nodeId,
                    const Ark_Number first,
                    const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper_onNext);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onPreviousImpl(Ark_Int32 nodeId,
                        const Ark_Number first,
                        const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper_onPrevious);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_indexImpl(Ark_Int32 nodeId,
                                  const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindStepper__onChangeEvent_index);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Swiper {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSwiper_onContentDidScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(selectedIndex);
        _eventBufferSerializer.writeNumber(index);
        _eventBufferSerializer.writeNumber(position);
        _eventBufferSerializer.writeNumber(mainAxisLength);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_indexImpl(Ark_Int32 nodeId,
                                  const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSwiper__onChangeEvent_index);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace IndicatorComponent {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindIndicatorComponent_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Tabs {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onTabBarClickImpl(Ark_Int32 nodeId,
                           const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onTabBarClick);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onAnimationStartImpl(Ark_Int32 nodeId,
                              const Ark_Number index,
                              const Ark_Number targetIndex,
                              const Ark_TabsAnimationEvent extraInfo)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onAnimationStart);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        _eventBufferSerializer.writeNumber(targetIndex);
        _eventBufferSerializer.writeTabsAnimationEvent(extraInfo);
        sendEvent(&_eventBuffer);
    }
    void onAnimationEndImpl(Ark_Int32 nodeId,
                            const Ark_Number index,
                            const Ark_TabsAnimationEvent extraInfo)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onAnimationEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        _eventBufferSerializer.writeTabsAnimationEvent(extraInfo);
        sendEvent(&_eventBuffer);
    }
    void onGestureSwipeImpl(Ark_Int32 nodeId,
                            const Ark_Number index,
                            const Ark_TabsAnimationEvent extraInfo)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onGestureSwipe);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        _eventBufferSerializer.writeTabsAnimationEvent(extraInfo);
        sendEvent(&_eventBuffer);
    }
    void customContentTransitionImpl(Ark_Int32 nodeId,
                                     const Ark_Number from,
                                     const Ark_Number to)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs_onContentWillChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(currentIndex);
        _eventBufferSerializer.writeNumber(comingIndex);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_indexImpl(Ark_Int32 nodeId,
                                  const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabs__onChangeEvent_index);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace TabContent {
    void onWillShowImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabContent_onWillShow);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onWillHideImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTabContent_onWillHide);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Text {
    void onCopyImpl(Ark_Int32 nodeId,
                    const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindText_onCopy);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                                   const Ark_Number first,
                                   const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindText_onTextSelectionChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void bindSelectionMenuImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindText_bindSelectionMenu);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace TextArea {
    void onSubmit0Impl(Ark_Int32 nodeId,
                       const Ark_EnterKeyType enterKey)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onSubmit0);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
        sendEvent(&_eventBuffer);
    }
    void onSubmit1Impl(Ark_Int32 nodeId,
                       const Ark_EnterKeyType enterKeyType,
                       const Opt_SubmitEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onSubmit1);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            _eventBufferSerializer.writeSubmitEvent(event_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_String value,
                      const Opt_PreviewText previewText)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(value);
        Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
        previewText_type = runtimeType(previewText);
        _eventBufferSerializer.writeInt8(previewText_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
            const auto previewText_value = previewText.value;
            _eventBufferSerializer.writePreviewText(previewText_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onTextSelectionChangeImpl(Ark_Int32 nodeId,
                                   const Ark_Number first,
                                   const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onTextSelectionChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onContentScrollImpl(Ark_Int32 nodeId,
                             const Ark_Number first,
                             const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onContentScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    void onEditChangeImpl(Ark_Int32 nodeId,
                          const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onEditChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onCopyImpl(Ark_Int32 nodeId,
                    const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onCopy);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onCutImpl(Ark_Int32 nodeId,
                   const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onCut);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onPasteImpl(Ark_Int32 nodeId,
                     const Ark_String value,
                     const Ark_PasteEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onPaste);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(value);
        _eventBufferSerializer.writePasteEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onWillInsertImpl(Ark_Int32 nodeId,
                          const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onWillInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidInsertImpl(Ark_Int32 nodeId,
                         const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onDidInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWillDeleteImpl(Ark_Int32 nodeId,
                          const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onWillDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidDeleteImpl(Ark_Int32 nodeId,
                         const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_onDidDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void customKeyboardImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea_customKeyboard);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_textImpl(Ark_Int32 nodeId,
                                 const Ark_ResourceStr value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextArea__onChangeEvent_text);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
        value_type = value.selector;
        if (value_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto value_0 = value.value0;
            _eventBufferSerializer.writeString(value_0);
        }
        else if (value_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto value_1 = value.value1;
            _eventBufferSerializer.writeResource(value_1);
        }
        sendEvent(&_eventBuffer);
    }
    }
    namespace TextClock {
    void onDateChangeImpl(Ark_Int32 nodeId,
                          const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextClock_onDateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    }
    namespace TextInput {
    void onEditChangedImpl(Ark_Int32 nodeId,
                           const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onEditChanged);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onEditChangeImpl(Ark_Int32 nodeId,
                          const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onEditChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSubmitImpl(Ark_Int32 nodeId,
                      const Ark_EnterKeyType enterKey,
                      const Ark_SubmitEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onSubmit);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
        _eventBufferSerializer.writeSubmitEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_String value,
                      const Opt_PreviewText previewText)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(value);
        Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
        previewText_type = runtimeType(previewText);
        _eventBufferSerializer.writeInt8(previewText_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
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
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onContentScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(totalOffsetX);
        _eventBufferSerializer.writeNumber(totalOffsetY);
        sendEvent(&_eventBuffer);
    }
    void onCopyImpl(Ark_Int32 nodeId,
                    const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onCopy);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onCutImpl(Ark_Int32 nodeId,
                   const Ark_String breakpoints)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onCut);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(breakpoints);
        sendEvent(&_eventBuffer);
    }
    void onPasteImpl(Ark_Int32 nodeId,
                     const Ark_String content,
                     const Ark_PasteEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onPaste);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(content);
        _eventBufferSerializer.writePasteEvent(event);
        sendEvent(&_eventBuffer);
    }
    void showUnitImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_showUnit);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onSecurityStateChangeImpl(Ark_Int32 nodeId,
                                   const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onSecurityStateChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWillInsertImpl(Ark_Int32 nodeId,
                          const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onWillInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidInsertImpl(Ark_Int32 nodeId,
                         const Ark_InsertValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onDidInsert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInsertValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWillDeleteImpl(Ark_Int32 nodeId,
                          const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onWillDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDidDeleteImpl(Ark_Int32 nodeId,
                         const Ark_DeleteValue parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_onDidDelete);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeDeleteValue(parameter);
        sendEvent(&_eventBuffer);
    }
    void customKeyboardImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput_customKeyboard);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_textImpl(Ark_Int32 nodeId,
                                 const Ark_ResourceStr value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextInput__onChangeEvent_text);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
        value_type = value.selector;
        if (value_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto value_0 = value.value0;
            _eventBufferSerializer.writeString(value_0);
        }
        else if (value_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto value_1 = value.value1;
            _eventBufferSerializer.writeResource(value_1);
        }
        sendEvent(&_eventBuffer);
    }
    }
    namespace TextPicker {
    void onAcceptImpl(Ark_Int32 nodeId,
                      const Ark_String value,
                      const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextPicker_onAccept);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeString(value);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onCancelImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextPicker_onCancel);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Union_String_Array_String value,
                      const Ark_Union_Number_Array_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextPicker_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
        value_type = value.selector;
        if (value_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto value_0 = value.value0;
            _eventBufferSerializer.writeString(value_0);
        }
        else if (value_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto value_1 = value.value1;
            _eventBufferSerializer.writeInt32(value_1.length);
            for (int i = 0; i < value_1.length; i++) {
                const Ark_String value_1_element = value_1.array[i];
                _eventBufferSerializer.writeString(value_1_element);
            }
        }
        Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
        index_type = index.selector;
        if (index_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto index_0 = index.value0;
            _eventBufferSerializer.writeNumber(index_0);
        }
        else if (index_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto index_1 = index.value1;
            _eventBufferSerializer.writeInt32(index_1.length);
            for (int i = 0; i < index_1.length; i++) {
                const Ark_Number index_1_element = index_1.array[i];
                _eventBufferSerializer.writeNumber(index_1_element);
            }
        }
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Union_Number_Array_Number selected)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextPicker__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
        selected_type = selected.selector;
        if (selected_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto selected_0 = selected.value0;
            _eventBufferSerializer.writeNumber(selected_0);
        }
        else if (selected_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto selected_1 = selected.value1;
            _eventBufferSerializer.writeInt32(selected_1.length);
            for (int i = 0; i < selected_1.length; i++) {
                const Ark_Number selected_1_element = selected_1.array[i];
                _eventBufferSerializer.writeNumber(selected_1_element);
            }
        }
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_valueImpl(Ark_Int32 nodeId,
                                  const Ark_Union_String_Array_String value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextPicker__onChangeEvent_value);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
        value_type = value.selector;
        if (value_type == 0) {
            _eventBufferSerializer.writeInt8(0);
            const auto value_0 = value.value0;
            _eventBufferSerializer.writeString(value_0);
        }
        else if (value_type == 1) {
            _eventBufferSerializer.writeInt8(1);
            const auto value_1 = value.value1;
            _eventBufferSerializer.writeInt32(value_1.length);
            for (int i = 0; i < value_1.length; i++) {
                const Ark_String value_1_element = value_1.array[i];
                _eventBufferSerializer.writeString(value_1_element);
            }
        }
        sendEvent(&_eventBuffer);
    }
    }
    namespace TextTimer {
    void onTimerImpl(Ark_Int32 nodeId,
                     const Ark_Number first,
                     const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTextTimer_onTimer);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    }
    namespace TimePicker {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_TimePickerResult value)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTimePicker_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTimePickerResult(value);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_selectedImpl(Ark_Int32 nodeId,
                                     const Ark_Date parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindTimePicker__onChangeEvent_selected);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt64(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Toggle {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindToggle_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_isOnImpl(Ark_Int32 nodeId,
                                 const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindToggle__onChangeEvent_isOn);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Video {
    void onStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onPauseImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onPause);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFinishImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onFinish);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFullscreenChangeImpl(Ark_Int32 nodeId,
                                const Ark_FullscreenInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onFullscreenChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeFullscreenInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onPreparedImpl(Ark_Int32 nodeId,
                        const Ark_PreparedInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onPrepared);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writePreparedInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSeekingImpl(Ark_Int32 nodeId,
                       const Ark_PlaybackInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onSeeking);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writePlaybackInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSeekedImpl(Ark_Int32 nodeId,
                      const Ark_PlaybackInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onSeeked);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writePlaybackInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onUpdateImpl(Ark_Int32 nodeId,
                      const Ark_PlaybackInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onUpdate);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writePlaybackInfo(parameter);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onStopImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindVideo_onStop);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace Web {
    void onPageEndImpl(Ark_Int32 nodeId,
                       const Ark_OnPageEndEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onPageEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnPageEndEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onPageBeginImpl(Ark_Int32 nodeId,
                         const Ark_OnPageBeginEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onPageBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnPageBeginEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onProgressChangeImpl(Ark_Int32 nodeId,
                              const Ark_OnProgressChangeEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onProgressChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnProgressChangeEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onTitleReceiveImpl(Ark_Int32 nodeId,
                            const Ark_OnTitleReceiveEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onTitleReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnTitleReceiveEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onGeolocationHideImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onGeolocationHide);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onGeolocationShowImpl(Ark_Int32 nodeId,
                               const Ark_OnGeolocationShowEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onGeolocationShow);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnGeolocationShowEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onRequestSelectedImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRequestSelected);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onAlertImpl(Ark_Int32 nodeId,
                     const Ark_OnAlertEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onAlert);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnAlertEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onBeforeUnloadImpl(Ark_Int32 nodeId,
                            const Ark_OnBeforeUnloadEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onBeforeUnload);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnBeforeUnloadEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onConfirmImpl(Ark_Int32 nodeId,
                       const Ark_OnConfirmEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onConfirm);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnConfirmEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onPromptImpl(Ark_Int32 nodeId,
                      const Ark_OnPromptEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onPrompt);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnPromptEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onConsoleImpl(Ark_Int32 nodeId,
                       const Ark_OnConsoleEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onConsole);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnConsoleEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onErrorReceiveImpl(Ark_Int32 nodeId,
                            const Ark_OnErrorReceiveEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onErrorReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnErrorReceiveEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onHttpErrorReceiveImpl(Ark_Int32 nodeId,
                                const Ark_OnHttpErrorReceiveEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onHttpErrorReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnHttpErrorReceiveEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDownloadStartImpl(Ark_Int32 nodeId,
                             const Ark_OnDownloadStartEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onDownloadStart);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnDownloadStartEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onRefreshAccessedHistoryImpl(Ark_Int32 nodeId,
                                      const Ark_OnRefreshAccessedHistoryEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRefreshAccessedHistory);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnRefreshAccessedHistoryEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onUrlLoadInterceptImpl(Ark_Int32 nodeId,
                                const Opt_Literal_Union_String_WebResourceRequest_data event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onUrlLoadIntercept);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            const auto event_value_data = event_value.data;
            Ark_Int32 event_value_data_type = INTEROP_RUNTIME_UNDEFINED;
            event_value_data_type = event_value_data.selector;
            if (event_value_data_type == 0) {
                _eventBufferSerializer.writeInt8(0);
                const auto event_value_data_0 = event_value_data.value0;
                _eventBufferSerializer.writeString(event_value_data_0);
            }
            else if (event_value_data_type == 1) {
                _eventBufferSerializer.writeInt8(1);
                const auto event_value_data_1 = event_value_data.value1;
                _eventBufferSerializer.writeWebResourceRequest(event_value_data_1);
            }
        }
        sendEvent(&_eventBuffer);
    }
    void onSslErrorReceiveImpl(Ark_Int32 nodeId,
                               const Opt_Literal_Function_handler_Object_error event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onSslErrorReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            const auto event_value_handler = event_value.handler;
            _eventBufferSerializer.writeFunction(event_value_handler);
            const auto event_value_error = event_value.error;
            _eventBufferSerializer.writeCustomObject("Object", event_value_error);
        }
        sendEvent(&_eventBuffer);
    }
    void onRenderExited0Impl(Ark_Int32 nodeId,
                             const Ark_OnRenderExitedEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRenderExited0);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnRenderExitedEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onRenderExited1Impl(Ark_Int32 nodeId,
                             const Opt_Literal_Object_detail event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRenderExited1);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            const auto event_value_detail = event_value.detail;
            _eventBufferSerializer.writeCustomObject("Object", event_value_detail);
        }
        sendEvent(&_eventBuffer);
    }
    void onShowFileSelectorImpl(Ark_Int32 nodeId,
                                const Ark_OnShowFileSelectorEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onShowFileSelector);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnShowFileSelectorEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFileSelectorShowImpl(Ark_Int32 nodeId,
                                const Opt_Literal_Function_callback__Object_fileSelector event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFileSelectorShow);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            const auto event_value_callback_ = event_value.callback_;
            _eventBufferSerializer.writeFunction(event_value_callback_);
            const auto event_value_fileSelector = event_value.fileSelector;
            _eventBufferSerializer.writeCustomObject("Object", event_value_fileSelector);
        }
        sendEvent(&_eventBuffer);
    }
    void onResourceLoadImpl(Ark_Int32 nodeId,
                            const Ark_OnResourceLoadEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onResourceLoad);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnResourceLoadEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFullScreenExitImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFullScreenExit);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onFullScreenEnterImpl(Ark_Int32 nodeId,
                               const Ark_FullScreenEnterEvent event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFullScreenEnter);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeFullScreenEnterEvent(event);
        sendEvent(&_eventBuffer);
    }
    void onScaleChangeImpl(Ark_Int32 nodeId,
                           const Ark_OnScaleChangeEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onScaleChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnScaleChangeEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onHttpAuthRequestImpl(Ark_Int32 nodeId,
                               const Ark_OnHttpAuthRequestEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onHttpAuthRequest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnHttpAuthRequestEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onInterceptRequestImpl(Ark_Int32 nodeId,
                                const Ark_OnInterceptRequestEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onInterceptRequest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnInterceptRequestEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onPermissionRequestImpl(Ark_Int32 nodeId,
                                 const Ark_OnPermissionRequestEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onPermissionRequest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnPermissionRequestEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onScreenCaptureRequestImpl(Ark_Int32 nodeId,
                                    const Ark_OnScreenCaptureRequestEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onScreenCaptureRequest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnScreenCaptureRequestEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onContextMenuShowImpl(Ark_Int32 nodeId,
                               const Ark_OnContextMenuShowEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onContextMenuShow);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnContextMenuShowEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onContextMenuHideImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onContextMenuHide);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onSearchResultReceiveImpl(Ark_Int32 nodeId,
                                   const Ark_OnSearchResultReceiveEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onSearchResultReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnSearchResultReceiveEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onScrollImpl(Ark_Int32 nodeId,
                      const Ark_OnScrollEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnScrollEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSslErrorEventReceiveImpl(Ark_Int32 nodeId,
                                    const Ark_OnSslErrorEventReceiveEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onSslErrorEventReceive);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnSslErrorEventReceiveEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSslErrorEventImpl(Ark_Int32 nodeId,
                             const Ark_SslErrorEvent sslErrorEvent)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onSslErrorEvent);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeSslErrorEvent(sslErrorEvent);
        sendEvent(&_eventBuffer);
    }
    void onClientAuthenticationRequestImpl(Ark_Int32 nodeId,
                                           const Ark_OnClientAuthenticationEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onClientAuthenticationRequest);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnClientAuthenticationEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWindowNewImpl(Ark_Int32 nodeId,
                         const Ark_OnWindowNewEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onWindowNew);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnWindowNewEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onWindowExitImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onWindowExit);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onInterceptKeyEventImpl(Ark_Int32 nodeId,
                                 const Ark_KeyEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onInterceptKeyEvent);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeKeyEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onTouchIconUrlReceivedImpl(Ark_Int32 nodeId,
                                    const Ark_OnTouchIconUrlReceivedEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onTouchIconUrlReceived);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnTouchIconUrlReceivedEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFaviconReceivedImpl(Ark_Int32 nodeId,
                               const Ark_OnFaviconReceivedEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFaviconReceived);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnFaviconReceivedEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onPageVisibleImpl(Ark_Int32 nodeId,
                           const Ark_OnPageVisibleEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onPageVisible);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnPageVisibleEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onDataResubmittedImpl(Ark_Int32 nodeId,
                               const Ark_OnDataResubmittedEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onDataResubmitted);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnDataResubmittedEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onAudioStateChangedImpl(Ark_Int32 nodeId,
                                 const Ark_OnAudioStateChangedEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onAudioStateChanged);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnAudioStateChangedEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFirstContentfulPaintImpl(Ark_Int32 nodeId,
                                    const Ark_OnFirstContentfulPaintEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFirstContentfulPaint);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnFirstContentfulPaintEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onFirstMeaningfulPaintImpl(Ark_Int32 nodeId,
                                    const Ark_FirstMeaningfulPaint firstMeaningfulPaint)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onFirstMeaningfulPaint);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeFirstMeaningfulPaint(firstMeaningfulPaint);
        sendEvent(&_eventBuffer);
    }
    void onLargestContentfulPaintImpl(Ark_Int32 nodeId,
                                      const Ark_LargestContentfulPaint largestContentfulPaint)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onLargestContentfulPaint);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeLargestContentfulPaint(largestContentfulPaint);
        sendEvent(&_eventBuffer);
    }
    void onLoadInterceptImpl(Ark_Int32 nodeId,
                             const Ark_OnLoadInterceptEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onLoadIntercept);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnLoadInterceptEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onControllerAttachedImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onControllerAttached);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onOverScrollImpl(Ark_Int32 nodeId,
                          const Ark_OnOverScrollEvent parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onOverScroll);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeOnOverScrollEvent(parameter);
        sendEvent(&_eventBuffer);
    }
    void onSafeBrowsingCheckResultImpl(Ark_Int32 nodeId,
                                       const Ark_ThreatType threatType)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onSafeBrowsingCheckResult);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
        sendEvent(&_eventBuffer);
    }
    void onNavigationEntryCommittedImpl(Ark_Int32 nodeId,
                                        const Ark_LoadCommittedDetails loadCommittedDetails)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onNavigationEntryCommitted);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeLoadCommittedDetails(loadCommittedDetails);
        sendEvent(&_eventBuffer);
    }
    void onIntelligentTrackingPreventionResultImpl(Ark_Int32 nodeId,
                                                   const Ark_IntelligentTrackingPreventionDetails details)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onIntelligentTrackingPreventionResult);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeIntelligentTrackingPreventionDetails(details);
        sendEvent(&_eventBuffer);
    }
    void onNativeEmbedLifecycleChangeImpl(Ark_Int32 nodeId,
                                          const Ark_NativeEmbedDataInfo event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedLifecycleChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNativeEmbedDataInfo(event);
        sendEvent(&_eventBuffer);
    }
    void onNativeEmbedVisibilityChangeImpl(Ark_Int32 nodeId,
                                           const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedVisibilityChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNativeEmbedVisibilityInfo(nativeEmbedVisibilityInfo);
        sendEvent(&_eventBuffer);
    }
    void onNativeEmbedGestureEventImpl(Ark_Int32 nodeId,
                                       const Ark_NativeEmbedTouchInfo event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onNativeEmbedGestureEvent);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNativeEmbedTouchInfo(event);
        sendEvent(&_eventBuffer);
    }
    void onOverrideUrlLoadingImpl(Ark_Int32 nodeId,
                                  const Ark_WebResourceRequest webResourceRequest)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onOverrideUrlLoading);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeWebResourceRequest(webResourceRequest);
        sendEvent(&_eventBuffer);
    }
    void onRenderProcessNotRespondingImpl(Ark_Int32 nodeId,
                                          const Ark_RenderProcessNotRespondingData data)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRenderProcessNotResponding);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeRenderProcessNotRespondingData(data);
        sendEvent(&_eventBuffer);
    }
    void onRenderProcessRespondingImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onRenderProcessResponding);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onViewportFitChangedImpl(Ark_Int32 nodeId,
                                  const Ark_ViewportFit viewportFit)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onViewportFitChanged);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
        sendEvent(&_eventBuffer);
    }
    void onInterceptKeyboardAttachImpl(Ark_Int32 nodeId,
                                       const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onInterceptKeyboardAttach);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeWebKeyboardCallbackInfo(keyboardCallbackInfo);
        sendEvent(&_eventBuffer);
    }
    void onAdsBlockedImpl(Ark_Int32 nodeId,
                          const Ark_AdsBlockedDetails details)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_onAdsBlocked);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeAdsBlockedDetails(details);
        sendEvent(&_eventBuffer);
    }
    void bindSelectionMenuImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWeb_bindSelectionMenu);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace XComponent {
    void onLoadImpl(Ark_Int32 nodeId,
                    const Opt_CustomObject event)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindXComponent_onLoad);
        _eventBufferSerializer.writeInt32(nodeId);
        Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
        event_type = runtimeType(event);
        _eventBufferSerializer.writeInt8(event_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
            const auto event_value = event.value;
            _eventBufferSerializer.writeCustomObject("Object", event_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onDestroyImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindXComponent_onDestroy);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    }
    namespace SideBarContainer {
    void onChangeImpl(Ark_Int32 nodeId,
                      const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSideBarContainer_onChange);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    void _onChangeEvent_showSideBarImpl(Ark_Int32 nodeId,
                                        const Ark_Boolean parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindSideBarContainer__onChangeEvent_showSideBar);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBoolean(parameter);
        sendEvent(&_eventBuffer);
    }
    }
    namespace WaterFlow {
    void onReachStartImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWaterFlow_onReachStart);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onReachEndImpl(Ark_Int32 nodeId)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWaterFlow_onReachEnd);
        _eventBufferSerializer.writeInt32(nodeId);
        sendEvent(&_eventBuffer);
    }
    void onScrollFrameBeginImpl(Ark_Int32 nodeId,
                                const Ark_Number offset,
                                const Ark_ScrollState state)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWaterFlow_onScrollFrameBegin);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(offset);
        _eventBufferSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
        sendEvent(&_eventBuffer);
    }
    void onScrollIndexImpl(Ark_Int32 nodeId,
                           const Ark_Number first,
                           const Ark_Number last)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindWaterFlow_onScrollIndex);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(first);
        _eventBufferSerializer.writeNumber(last);
        sendEvent(&_eventBuffer);
    }
    }
    namespace UIExtensionComponent {
    void onRemoteReadyImpl(Ark_Int32 nodeId,
                           const Ark_UIExtensionProxy parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onRemoteReady);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeUIExtensionProxy(parameter);
        sendEvent(&_eventBuffer);
    }
    void onResultImpl(Ark_Int32 nodeId,
                      const Ark_Literal_Number_code_Want_want parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onResult);
        _eventBufferSerializer.writeInt32(nodeId);
        const auto parameter_code = parameter.code;
        _eventBufferSerializer.writeNumber(parameter_code);
        const auto parameter_want = parameter.want;
        Ark_Int32 parameter_want_type = INTEROP_RUNTIME_UNDEFINED;
        parameter_want_type = runtimeType(parameter_want);
        _eventBufferSerializer.writeInt8(parameter_want_type);
        if ((INTEROP_RUNTIME_UNDEFINED) != (parameter_want_type)) {
            const auto parameter_want_value = parameter_want.value;
            _eventBufferSerializer.writeWant(parameter_want_value);
        }
        sendEvent(&_eventBuffer);
    }
    void onReleaseImpl(Ark_Int32 nodeId,
                       const Ark_Number index)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onRelease);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeNumber(index);
        sendEvent(&_eventBuffer);
    }
    void onErrorImpl(Ark_Int32 nodeId,
                     const Ark_BusinessError err)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onError);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeBusinessError(err);
        sendEvent(&_eventBuffer);
    }
    void onTerminatedImpl(Ark_Int32 nodeId,
                          const Ark_TerminationInfo parameter)
    {
        EventBuffer _eventBuffer;
        Serializer _eventBufferSerializer(_eventBuffer.buffer, sizeof(_eventBuffer.buffer));
        _eventBufferSerializer.writeInt32(KindUIExtensionComponent_onTerminated);
        _eventBufferSerializer.writeInt32(nodeId);
        _eventBufferSerializer.writeTerminationInfo(parameter);
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
            AlphabetIndexer::_onChangeEvent_selectedImpl,
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
            Checkbox::_onChangeEvent_selectImpl,
        };

        return &GENERATED_ArkUICheckboxEventsReceiverImpl;
    }
    const GENERATED_ArkUICheckboxGroupEventsReceiver* GetCheckboxGroupEventsReceiver()
    {
        static const GENERATED_ArkUICheckboxGroupEventsReceiver GENERATED_ArkUICheckboxGroupEventsReceiverImpl {
            CheckboxGroup::onChangeImpl,
            CheckboxGroup::_onChangeEvent_selectAllImpl,
        };

        return &GENERATED_ArkUICheckboxGroupEventsReceiverImpl;
    }
    const GENERATED_ArkUICommonMethodEventsReceiver* GetCommonMethodEventsReceiver()
    {
        static const GENERATED_ArkUICommonMethodEventsReceiver GENERATED_ArkUICommonMethodEventsReceiverImpl {
            CommonMethod::onChildTouchTestImpl,
            CommonMethod::onClick0Impl,
            CommonMethod::onClick1Impl,
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
            CommonMethod::accessibilityVirtualNodeImpl,
            CommonMethod::onGestureJudgeBeginImpl,
            CommonMethod::onGestureRecognizerJudgeBegin0Impl,
            CommonMethod::onGestureRecognizerJudgeBegin1Impl,
            CommonMethod::shouldBuiltInRecognizerParallelWithImpl,
            CommonMethod::onTouchInterceptImpl,
            CommonMethod::onSizeChangeImpl,
            CommonMethod::backgroundImpl,
            CommonMethod::bindContextMenu0Impl,
            CommonMethod::bindContextMenu1Impl,
            CommonMethod::bindContentCover0Impl,
            CommonMethod::bindContentCover1Impl,
            CommonMethod::bindSheetImpl,
            CommonMethod::onVisibleAreaChangeImpl,
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
            DatePicker::_onChangeEvent_selectedImpl,
        };

        return &GENERATED_ArkUIDatePickerEventsReceiverImpl;
    }
    const GENERATED_ArkUIEmbeddedComponentEventsReceiver* GetEmbeddedComponentEventsReceiver()
    {
        static const GENERATED_ArkUIEmbeddedComponentEventsReceiver GENERATED_ArkUIEmbeddedComponentEventsReceiverImpl {
            EmbeddedComponent::onTerminatedImpl,
            EmbeddedComponent::onErrorImpl,
        };

        return &GENERATED_ArkUIEmbeddedComponentEventsReceiverImpl;
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
    const GENERATED_ArkUIGaugeEventsReceiver* GetGaugeEventsReceiver()
    {
        static const GENERATED_ArkUIGaugeEventsReceiver GENERATED_ArkUIGaugeEventsReceiverImpl {
            Gauge::descriptionImpl,
        };

        return &GENERATED_ArkUIGaugeEventsReceiverImpl;
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
            GridItem::_onChangeEvent_selectedImpl,
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
            ListItem::_onChangeEvent_selectedImpl,
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
            MenuItem::_onChangeEvent_selectedImpl,
        };

        return &GENERATED_ArkUIMenuItemEventsReceiverImpl;
    }
    const GENERATED_ArkUINavDestinationEventsReceiver* GetNavDestinationEventsReceiver()
    {
        static const GENERATED_ArkUINavDestinationEventsReceiver GENERATED_ArkUINavDestinationEventsReceiverImpl {
            NavDestination::onShownImpl,
            NavDestination::onHiddenImpl,
            NavDestination::onBackPressedImpl,
            NavDestination::onReadyImpl,
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
    const GENERATED_ArkUIPanelEventsReceiver* GetPanelEventsReceiver()
    {
        static const GENERATED_ArkUIPanelEventsReceiver GENERATED_ArkUIPanelEventsReceiverImpl {
            Panel::onChangeImpl,
            Panel::onHeightChangeImpl,
            Panel::_onChangeEvent_modeImpl,
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
            PatternLock::onDotConnectImpl,
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
            Radio::_onChangeEvent_checkedImpl,
        };

        return &GENERATED_ArkUIRadioEventsReceiverImpl;
    }
    const GENERATED_ArkUIRatingEventsReceiver* GetRatingEventsReceiver()
    {
        static const GENERATED_ArkUIRatingEventsReceiver GENERATED_ArkUIRatingEventsReceiverImpl {
            Rating::onChangeImpl,
            Rating::_onChangeEvent_ratingImpl,
        };

        return &GENERATED_ArkUIRatingEventsReceiverImpl;
    }
    const GENERATED_ArkUIRefreshEventsReceiver* GetRefreshEventsReceiver()
    {
        static const GENERATED_ArkUIRefreshEventsReceiver GENERATED_ArkUIRefreshEventsReceiverImpl {
            Refresh::onStateChangeImpl,
            Refresh::onRefreshingImpl,
            Refresh::onOffsetChangeImpl,
            Refresh::_onChangeEvent_refreshingImpl,
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
            RichEditor::bindSelectionMenuImpl,
            RichEditor::customKeyboardImpl,
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
            Search::onSubmit0Impl,
            Search::onSubmit1Impl,
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
            Search::customKeyboardImpl,
            Search::_onChangeEvent_valueImpl,
        };

        return &GENERATED_ArkUISearchEventsReceiverImpl;
    }
    const GENERATED_ArkUISelectEventsReceiver* GetSelectEventsReceiver()
    {
        static const GENERATED_ArkUISelectEventsReceiver GENERATED_ArkUISelectEventsReceiverImpl {
            Select::onSelectImpl,
            Select::_onChangeEvent_selectedImpl,
            Select::_onChangeEvent_valueImpl,
        };

        return &GENERATED_ArkUISelectEventsReceiverImpl;
    }
    const GENERATED_ArkUISliderEventsReceiver* GetSliderEventsReceiver()
    {
        static const GENERATED_ArkUISliderEventsReceiver GENERATED_ArkUISliderEventsReceiverImpl {
            Slider::onChangeImpl,
            Slider::_onChangeEvent_valueImpl,
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
            Stepper::_onChangeEvent_indexImpl,
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
            Swiper::_onChangeEvent_indexImpl,
        };

        return &GENERATED_ArkUISwiperEventsReceiverImpl;
    }
    const GENERATED_ArkUIIndicatorComponentEventsReceiver* GetIndicatorComponentEventsReceiver()
    {
        static const GENERATED_ArkUIIndicatorComponentEventsReceiver GENERATED_ArkUIIndicatorComponentEventsReceiverImpl {
            IndicatorComponent::onChangeImpl,
        };

        return &GENERATED_ArkUIIndicatorComponentEventsReceiverImpl;
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
            Tabs::_onChangeEvent_indexImpl,
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
            Text::bindSelectionMenuImpl,
        };

        return &GENERATED_ArkUITextEventsReceiverImpl;
    }
    const GENERATED_ArkUITextAreaEventsReceiver* GetTextAreaEventsReceiver()
    {
        static const GENERATED_ArkUITextAreaEventsReceiver GENERATED_ArkUITextAreaEventsReceiverImpl {
            TextArea::onSubmit0Impl,
            TextArea::onSubmit1Impl,
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
            TextArea::customKeyboardImpl,
            TextArea::_onChangeEvent_textImpl,
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
            TextInput::showUnitImpl,
            TextInput::onSecurityStateChangeImpl,
            TextInput::onWillInsertImpl,
            TextInput::onDidInsertImpl,
            TextInput::onWillDeleteImpl,
            TextInput::onDidDeleteImpl,
            TextInput::customKeyboardImpl,
            TextInput::_onChangeEvent_textImpl,
        };

        return &GENERATED_ArkUITextInputEventsReceiverImpl;
    }
    const GENERATED_ArkUITextPickerEventsReceiver* GetTextPickerEventsReceiver()
    {
        static const GENERATED_ArkUITextPickerEventsReceiver GENERATED_ArkUITextPickerEventsReceiverImpl {
            TextPicker::onAcceptImpl,
            TextPicker::onCancelImpl,
            TextPicker::onChangeImpl,
            TextPicker::_onChangeEvent_selectedImpl,
            TextPicker::_onChangeEvent_valueImpl,
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
            TimePicker::_onChangeEvent_selectedImpl,
        };

        return &GENERATED_ArkUITimePickerEventsReceiverImpl;
    }
    const GENERATED_ArkUIToggleEventsReceiver* GetToggleEventsReceiver()
    {
        static const GENERATED_ArkUIToggleEventsReceiver GENERATED_ArkUIToggleEventsReceiverImpl {
            Toggle::onChangeImpl,
            Toggle::_onChangeEvent_isOnImpl,
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
            Web::onRenderExited1Impl,
            Web::onShowFileSelectorImpl,
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
            Web::bindSelectionMenuImpl,
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
            SideBarContainer::_onChangeEvent_showSideBarImpl,
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
            UIExtensionComponent::onRemoteReadyImpl,
            UIExtensionComponent::onResultImpl,
            UIExtensionComponent::onReleaseImpl,
            UIExtensionComponent::onErrorImpl,
            UIExtensionComponent::onTerminatedImpl,
        };

        return &GENERATED_ArkUIUIExtensionComponentEventsReceiverImpl;
    }
    const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPI()
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
            GetEmbeddedComponentEventsReceiver,
            GetFolderStackEventsReceiver,
            GetFormComponentEventsReceiver,
            GetGaugeEventsReceiver,
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
            GetIndicatorComponentEventsReceiver,
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
        return &eventsImpl;
    }
}
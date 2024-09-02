/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/**
 * @addtogroup ArkUI_AccessibilityProvider
 * @{
 *
 * @brief
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file native_interface_accessibility.h
 *
 * @brief
 *
 * @since 13
 * @version 1.0
 */
#ifndef _NATIVE_INTERFACE_ACCESSIBILITY_H
#define _NATIVE_INTERFACE_ACCESSIBILITY_H

#include <cstdint>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Provides an encapsulated <b>ArkUI_AccessibilityElementInfo</b> instance.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfo ArkUI_AccessibilityElementInfo;

/**
 * @brief Defines the accessibility event info.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityEventInfo ArkUI_AccessibilityEventInfo;

/**
 * @brief Definesthe accessibility native provider.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProvider ArkUI_AccessibilityProvider;

/**
 * @brief Provides an encapsulated <b>OH_NativeAccessibilityDictionary</b> instance,
 * Implement the function of cpp dictionary.
 *
 * @since 13
 * @version 1.0
 */
typedef struct ArkUI_AccessibilityActionArguments  ArkUI_AccessibilityActionArguments;

/**
 * @brief Enumerates the API accessibility actions.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /** Invalid */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_INVALID = 0,
    /** After receiving the event, the component needs to respond to the click. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_CLICK = 0x00000010,
    /** After receiving the event, the component needs to respond to the long click. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_LONG_CLICK = 0x00000020,
    /** Indicates the operation of obtaining the accessibility focus. The specific component is focused */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS = 0x00000040,
    /** Indicates the operation of clearing the accessibility focus. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS = 0x00000080,
    /** The scrolling component responds to forward scrolling action. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_SCROLL_FORWARD = 0x00000100,
    /** The scrolling component responds to backwrad scrolling action. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_SCROLL_BACKWARD = 0x00000200,
    /** Coping the selected content for the text component. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_COPY = 0x00000400,
    /** Paste the selected content for the text component. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_PASTE = 0x00000800,
    /** Cut the selected content for the text component. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_CUT = 0x00001000,
    /** Indicates the selection operation. The selectTextBegin, selectTextEnd, and selectTextInForWard parameters need to be set. Select a text segment in the edit box. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_SET_SELECTION = 0x00002000,
    /** Set the text Content for the text component. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_SET_TEXT = 0x00004000,
    /** Set the cursor position for the text component. */
    ARKUI_NATIVE_ACCESSIBILITY_ACTION_SET_CURSOR_POSITION = 0x00100000,
} ArkUI_Accessibility_ActionType;

/**
 * @brief Enumerates the API accessibility event types.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /** Invalid */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_INVALID = 0,
    /** Clicked event, which is sent after the UI component responds. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_CLICKED_EVENT = 0x00000001,
    /** Long-Clicked event, which is sent after the UI component responds. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_LONG_CLICKED_EVENT = 0x00000002,
    /** Selected event, which is sent after the UI component responds. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_SELECTED_EVENT = 0x00000004,
    /** Text update event, needs to be send when the text is updated. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_TEXT_UPDATE_EVENT = 0x00000010,
    /** Page update event, which is sent when the page jumps, switchs, changes in size, or moves. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_PAGE_STATE_UPDATE = 0x00000020,
    /** Content update event, which is sent when the page content changes. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_PAGE_CONTENT_UPDATE = 0x00000800,
    /** scrolled event, this event is send when a scrolling event occurs on a component that can be scrolled. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_SCROLLED_EVENT = 0x000001000,
    /** Accessibility focus event, which is send after the UI component responds. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_ACCESSIBILITY_FOCUSED_EVENT = 0x00008000,
    /** Accessibility focus clear event, which is send after the UI component responds. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_ACCESSIBILITY_FOCUS_CLEARED_EVENT = 0x00010000,
    /** Request focus for accessibility event, proactively reqeust to focus on a specified node. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_REQUEST_FOCUS_FOR_ACCESSIBILITY = 0x02000000,
    /** Page open event. the event is reported when the UI component */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_PAGE_OPEN = 0x20000000,
    /** Page close event. the event is reported when the UI component */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_PAGE_CLOSE = 0x08000000,
    /** Announce for accessibility event, requesting to actively play the specified content event. */
    ARKUI_NATIVE_ACCESSIBILITY_TYPE_VIEW_ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,
} ArkUI_AccessibilityEventType;

/**
 * @brief Defines the accessible of action
 *
 * @since 13
 * @version 1.0
 */
typedef struct {
    /** action type. */
    ArkUI_Accessibility_ActionType actionType;
    /** the description message of action. */
    const char* description;
} ArkUI_AccessibleAction;

/**
 * @brief Defines the accessible of rect.
 *
 * @since 13
 * @version 1.0
 */
typedef struct {
    /** the left top x pixel corrdinates. */
    int32_t leftTopX;
    /** the left top y pixel corrdinates. */
    int32_t leftTopY;
    /** the right bottom x pixel corrdinates. */
    int32_t rightBottomX;
    /** the right bottom y pixel corrdinates. */
    int32_t rightBottomY;
} ArkUI_AccessibleRect;

/**
 * @brief Defines the accessible of range info.
 *
 * @since 13
 * @version 1.0
 */
typedef struct {
    /** the min value. */
    double min;
    /** the max value. */
    double max;
    /** the current value. */
    double current;
} ArkUI_AccessibleRangeInfo;

/**
 * @brief Defines the accessible of grid info.
 *
 * @since 13
 * @version 1.0
 */
typedef struct {
    /** The number of row.*/
    int32_t rowCount;
    /** The number of column.*/
    int32_t columnCount;
    /** 0: select one line only, otherwise select multilines.*/
    int32_t selectionMode;
} ArkUI_AccessibleGridInfo;

/**
 * @brief Defines the accessible of grid item info.
 *
 * @since 13
 * @version 1.0
 */
typedef struct {
    /** true: The item isHeading, otherwise is not.*/
    bool heading;
    /** true: The item selected, otherwise is not.*/
    bool selected;
    /** the index of column.*/
    int32_t columnIndex;
    /** the index of row.*/
    int32_t rowIndex;
    /** the column spanned.*/
    int32_t columnSpan;
    /** the row spanned.*/
    int32_t rowSpan;
} ArkUI_AccessibleGridItemInfo;

/**
 * @brief Enumerates the API accessibility ErrorCode states.
 *
 * @since 13
 * @version 1.0
 */
enum AcessbilityErrorCode {
    /** Successful.*/
    OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS = 0,
    /** Failed.*/
    OH_ARKUI_ACCESSIBILITY_RESULT_FAILED = -1,
    /** Invalid parameters.*/
    OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER = -2,
    /** Out of memory.*/
    OH_ARKUI_ACCESSIBILITY_RESULT_OUT_OF_MEMORY = -3,
};

/**
 * @brief Enumerates the API accessibility search mode.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /** predecessors */
    NATIVE_SEARCH_MODE_PREFETCH_PREDECESSORS = 1 << 0,
    /** slbings */
    NATIVE_SEARCH_MODE_PREFETCH_SIBLINGS = 1 << 1,
    /** children */
    NATIVE_SEARCH_MODE_PREFETCH_CHILDREN = 1 << 2,
    /** recusive children */
    NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN = 1 << 3,
} ArkUI_AccessibilitySearchMode;

/**
 * @brief Enumerates the API accessibility focus type.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /** Invalid */
    NATIVE_FOCUS_TYPE_INVALID = -1,
    /** Input focus type */
    NATIVE_FOCUS_TYPE_INPUT = 1 << 0,
    /** Accessibility focus type */
    NATIVE_FOCUS_TYPE_ACCESSIBILITY = 1 << 1,
} ArkUI_AccessibilityFocusType;

/**
 * @brief Enumerates the API accessibility focus move direction.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /** Invalid */
    NATIVE_DIRECTION_INVALID = 0,
    /** up direction. */
    NATIVE_DIRECTION_UP = 0x00000001,
    /** down direction. */
    NATIVE_DIRECTION_DOWN = 0x00000002,
    /** left direction. */
    NATIVE_DIRECTION_LEFT = 0x00000004,
    /** right direction. */
    NATIVE_DIRECTION_RIGHT = 0x00000008,
    /** forward direction. */
    NATIVE_DIRECTION_FORWARD = 0x00000010,
    /** backward direction. */
    NATIVE_DIRECTION_BACKWARD = 0x00000020,
} ArkUI_AccessibilityFocusMoveDirection;

/**
 * @brief Provides an encapsulated <b>ArkUI_AccessibilityElementInfoList</b> instance.
 *
 * @since 13
 * @version 1.0
 */
typedef struct ArkUI_AccessibilityElementInfoList ArkUI_AccessibilityElementInfoList;

/**
 * @brief Registers the accessibility provider callbacks
 *
 * @since 13
 * @version 1.0
 */
typedef struct ArkUI_AccessibilityProviderCallbacks {
    /** Called when need to get element infos based on a specified node. */
    int32_t (*FindAccessibilityNodeInfosById)(
        int64_t elementId, ArkUI_AccessibilitySearchMode mode,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /** Called when need to get element infos based on a specified node and text content. */
    int32_t (*FindAccessibilityNodeInfosByText)(
        int64_t elementId, const char* text, int32_t requestId,
        ArkUI_AccessibilityElementInfoList* elementList);
    /** Called when need to get the focused element info based on a specified node. */
    int32_t (*FindFocusedAccessibilityNode)(
        int64_t elementId, ArkUI_AccessibilityFocusType focusType,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementinfo);
    /** Query the node that can be focused based on the reference node.
     * Query the next node that can be focused based on the mode and direction.\
     */
    int32_t (*FindNextFocusAccessibilityNode)(
        int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementList);
    /** Performing the Action operation on a specified node. */
    int32_t (*ExecuteAccessibilityAction)(
        int64_t elementId, ArkUI_Accessibility_ActionType action,
        ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /** Clears the focus status of the currently focused node */
    int32_t (*ClearFocusedFocusAccessibilityNode)();
    /** Queries the current cursor position of a specified node. */
    int32_t (*GetAccessibilityNodeCursorPosition)(
        int64_t elementId, int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacks;

/**
 * @brief Registers a callback for this <b>ArkUI_AccessibilityProvider</b> instance.
 *
 * @param provider Indicates the pointer to this <b>ArkUI_AccessibilityProvider</b> instance.
 * @param callbacks Indicates the pointer to a GetAccessibilityNodeCursorPosition callback.
 * @return Returns the status code of the execution.
 * @since 13
 * @version 1.0
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacks* callbacks);

/**
 * @brief send accessibility event info.
 *
 * @param provider Indicates the pointer to this <b>ArkUI_AccessibilityProvider</b> instance.
 * @param eventInfo Indicates the pointer to the accessibility event info.
 * @param callback Indicates the pointer to a SendAccessibilityAsyncEvent callback.
 * @return Returns the status code of the execution.
 * @since 13
 * @version 1.0
 */
void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode));

/**
 * @brief Adds an element to the list.
 *
 * @param list Indicates the pointer to the accessibility element list.
 * @return Returns the pointer to the accessibility elementInfo.
 * @since 13
 * @version 1.0
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list);

/**
* @brief Sets the element id of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param elementId Indicates the page id.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId);

/**
* @brief Sets the page id of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param componentId Indicates the component id.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoComponentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t componentId);

/**
* @brief Sets the parent id of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param parentId Indicates the parent id.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId);

/**
* @brief Sets the component type of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param componentType Indicates the component type.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType);

/**
* @brief Sets the component contents of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param contents Indicates the component contents.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents);

/**
* @brief Sets the hint text of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param hintText Indicates the hint text.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText);

/**
* @brief Sets the accessibility text of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param accessibilityText Indicates the accessibility text.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText);

/**
* @brief Sets the accessibility description of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param accessibilityDescription Indicates the accessibility description.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription);

/**
* @brief Sets the child node ids of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param childCount Indicates the child count.
* @param childNodeIds Indicates the child node ids.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds);

/**
* @brief Sets the child count of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param operationActions Indicates All actions supported by the element.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoOperationActions(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t operationCount,
    ArkUI_AccessibleAction* operationActions);

/**
* @brief Sets the screen rect of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param screenRect Indicates screen rect.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect);

/**
* @brief Sets the checkable of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param checkable Indicates checkable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable);

/**
* @brief Sets the checked of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param checked Indicates whether the element is checked.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked);

/**
* @brief Sets the focusable of the accessibility element information.
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param focusable Indicates whether the element is focusable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable);

/**
* @brief Sets the isFocused of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param isFocused Indicates whether the element is focused.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused);

/**
* @brief Sets the isVisible of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param isVisible Indicates whether the element is visible.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible);

/**
* @brief Sets the accessibilityFocused of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param accessibilityFocused Indicates whether the element is accessibility focused.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused);

/**
* @brief Sets the selected of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param selected Indicates whether the element is selected.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected);

/**
* @brief Sets the clickable of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param clickable Indicates whether the element is clickable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable);

/**
* @brief Sets the longClickable of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param longClickable Indicates whether the element is long clickable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable);

/**
* @brief Sets the isEnabled of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param isEnable Indicates whether the element is enable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled);

/**
* @brief Sets the isPassword of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param isPassword Indicates whether the element is a password.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword);

/**
* @brief Sets the scrollable of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param scrollable Indicates whether the element is scrollable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable);

/**
* @brief Sets the editable of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param editable Indicates whether the element is editable.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable);

/**
* @brief Sets the isHint of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param isHint Indicates whether the element is in the hint state.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint);

/**
* @brief Sets the rangeInfo of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param rangeInfo Indicates element's range info.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo);

/**
* @brief Sets the grid of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param gridInfo Indicates element's grid info.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo);

/**
* @brief Sets the gridItem of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param gridItem Indicates element's grid item info.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem);

/**
* @brief Sets the textBeginSelected of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param textBeginSelected Indicates the start position of the selection.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoTextBeginSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t textBeginSelected);

/**
* @brief Sets the textEndSelected of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param textEndSelected Indicates the end position of the selection.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoTextEndSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t textEndSelected);

/**
* @brief Sets the currentItemIndex of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param currentItemIndex Indicates index of the current item.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex);

/**
* @brief Sets the beginItemIndex of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param beginItemIndex Indicates index of the begin item.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoBeginItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t beginItemIndex);

/**
* @brief Sets the endItemIndex of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param endItemIndex Indicates index of the end item.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex);

/**
* @brief Sets the itemCount of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param itemCount Indicates total number of items.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount);

/**
* @brief Sets the offset of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param offset Indicates pixel offset for scrolling relative to the top coordinate of the element.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset);

/**
* @brief Sets the accessibilityGroup of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param accessibilityGroup Indicates accessibility group.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup);

/**
* @brief Sets the accessibilityLevel of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param accessibilityLevel Indicates accessibility level.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel);

/**
* @brief Sets the zIndex of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param zIndex Indicates z index.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex);

/**
* @brief Sets the opacity of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param opacity Indicates opacity.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity);

/**
* @brief Sets the backgroundColor of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param backgroundColor Indicates background color.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor);

/**
* @brief Sets the backgroundImage of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param backgroundImage Indicates background image.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage);

/**
* @brief Sets the blur of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param blur Indicates blur.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur);

/**
* @brief Sets the hitTestBehavior of the accessibility element information.
*
* @param elementInfo Indicates the pointer to the accessibility element information.
* @param hitTestBehavior Indicates hitTest behavior.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityElementInfoHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior);

/**
 * @brief Create an accessibility elementInfo.
 *
 * @return Returns the pointer to the accessibility elementInfo.
 * @since 13
 * @version 1.0
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void);

/**
 * @brief Destorys an accessibility elementInfo.
 *
 * @param elementInfo Indicates the pointer to to the accessibility elementInfo info to be destoryed.
 * @since 13
 * @version 1.0
 */
void OH_ArkUI_DestoryAccessibilityElementInfo(ArkUI_AccessibilityElementInfo* elementInfo);

/**
 * @brief Create an accessibility eventInfo.
 *
 * @return Returns the pointer to the accessibility event info.
 * @since 13
 * @version 1.0
 */
ArkUI_AccessibilityEventInfo* OH_ArkUI_CreateAccessibilityEventInfo(void);

/**
 * @brief Destorys an accessibility eventInfo.
 *
 * @param eventInfo Indicates the pointer to to the accessibility event info to be destoryed.
 * @since 13
 * @version 1.0
 */
void OH_ArkUI_DestoryAccessibilityEventInfo(ArkUI_AccessibilityEventInfo* eventInfo);

/**
* @brief Sets the eventType of the accessibility event information.
*
* @param eventInfo Indicates the pointer to the accessibility event information.
* @param eventType Indicates event type.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityEventEventType(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityEventType eventType);

/**
* @brief Sets the textAnnouncedForAccessibility of the accessibility event information.
*
* @param eventInfo Indicates the pointer to the accessibility event information.
* @param textAnnouncedForAccessibility Indicates text announced for accessibility.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityEventTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo,  const char* textAnnouncedForAccessibility);

/**
* @brief Sets the requestFocusId of the accessibility event information.
*
* @param eventInfo Indicates the pointer to the accessibility event information.
* @param requestFocusId Indicates ID of the request for active focus.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityEventRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo,  int32_t requestFocusId);

/**
* @brief Sets the elementInfo of the accessibility event information.
*
* @param eventInfo Indicates the pointer to the accessibility event information.
* @param elementInfo Indicates element Info.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_SetAccessibilityEventElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityElementInfo* elementInfo);

/**
* @brief Gets the value of the accessibility action argument by key.
*
* @param arguments Indicates the pointer to the accessibility action arguments.
* @param key Indicates key.
* @param value Indicates value.
* @return Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS} if success.
*         Returns {@link OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER} if a parameter exception occurs.
* @since 13
*/
int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value);
#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_ACCESSIBILITY_H

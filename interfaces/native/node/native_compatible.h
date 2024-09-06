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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI
 * component creation and destruction, tree node operations, attribute setting,
 * and event listening.
 *
 * @since 12
 */

/**
 * @file native_event.h
 *
 * @brief Provides the event type definitions of ArkUI on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_COMPATIBLE
#define ARKUI_NATIVE_COMPATIBLE

#include <cstdint>

#include "native_node.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the tool types of the touch event.
 *
 * @since 12
 */
typedef enum {
    /** Unknown tool type. */
    NODE_TOOL_TYPE_UNKNOWN = -1,

    /** Finger. */
    NODE_TOOL_TYPE_FINGER = 0,

    /** Stylus. */
    NODE_TOOL_TYPE_STYLUS = 1,
} ArkUI_NodeToolType;

/**
 * @brief Enumerates the source types of the touch event.
 *
 * @since 12
 */
typedef enum {
    /** Unknown source type. */
    NODE_SOURCE_TYPE_UNKNOWN = -1,
    /** Touchscreen. */
    NODE_SOURCE_TYPE_TOUCH_SCREEN = 0,
    /** Stylus. */
    NODE_SOURCE_TYPE_STYLUS = 1,
    /** Touchpad. */
    NODE_SOURCE_TYPE_TOUCHPAD = 2,
} ArkUI_NodeSourceType;

/**
 * @brief Defines the data structure of the touch point information of the
 * touch event.
 *
 * @since 12
 */
typedef struct {
    /** ID of the touch event. */
    int32_t id;

    /** Timestamp when a finger is pressed, in μs. */
    int64_t pressedTime;

    /** X coordinate of the touch point on the screen. */
    int32_t screenX;

    /** Y coordinate of the touch point on the screen. */
    int32_t screenY;

    /** X coordinate of the touch point in the window. */
    int32_t windowX;

    /** Y coordinate of the touch point in the window. */
    int32_t windowY;

    /** X coordinate of the touch point in the component that triggers the event. */
    int32_t nodeX;

    /** Y coordinate of the touch point in the component that triggers the event. */
    int32_t nodeY;

    /** Pressure value. The value range is [0.0, 1.0]. The value 0.0 indicates
        that the pressure is not supported. */
    double pressure;

    /** Width of the touch area. */
    int32_t contactAreaWidth;

    /** Height of the touch area. */
    int32_t contactAreaHeight;

    /** Angle relative to the YZ plane. The value range is [-90, 90]. A positive value indicates a rightward tilt. */
    double tiltX;

    /** Angle relative to the XZ plane. The value range is [-90, 90]. A positive value indicates a downward tilt. */
    double tiltY;

    /** X coordinate of the center point of the tool area. */
    int32_t toolX;

    /** Y coordinate of the center point of the tool area. */
    int32_t toolY;

    /** Width of the tool area. */
    int32_t toolWidth;

    /** Height of the tool area. */
    int32_t toolHeight;

    /** X coordinate of the input device. */
    int32_t rawX;

    /** Y coordinate of the input device. */
    int32_t rawY;

    /** Tool type. */
    ArkUI_NodeToolType toolType;
} ArkUI_NodeTouchPoint;

/**
 * @brief Enumerates touch event types.
 *
 * @since 12
 */
typedef enum {
    /** Cancellation of touch. */
    NODE_ACTION_CANCEL = 0,
    /** Pressing of a touch point. */
    NODE_ACTION_DOWN = 1,
    /** Moving of a touch point. */
    NODE_ACTION_MOVE = 2,
    /** Lifting of a touch point. */
    NODE_ACTION_UP = 3,
} ArkUI_NodeTouchEventAction;

/**

 * @brief Defines the data structure of the historical point information.
 *
 * @since 12
 */
typedef struct {
    /** Touch event type. */
    ArkUI_NodeTouchEventAction action;
    /** Timestamp of the historical touch event, in μs. */
    int64_t timeStamp;
    /** Source type of the historical touch event. */
    ArkUI_NodeTouchPoint actionTouch;
    /** Source type of the historical touch event. */
    ArkUI_NodeSourceType sourceType;
} ArkUI_NodeHistoricalTouchPoint;

/**
 * @brief Defines the data structure of the touch event.
 *
 * @since 12
 */
typedef struct {
    /** Touch event type. */
    ArkUI_NodeTouchEventAction action;

    /** Timestamp of the touch event, in μs. */
    int64_t timeStamp;

    /** Touch point information of the touch event. */
    ArkUI_NodeTouchPoint actionTouch;

    /**
     * @brief Returns information about all touch points when this event occurs.
     * @param points Indicates the pointer to the object that receives data.
     * @return Returns the number of elements in the touch point information array.
     * @note
     * When this function is called, ArkUI creates a heap memory object of the touch point information array and
     * returns the pointer to the pointer. You need to call <b>delete[]</b> to manually free the memory when the
     * object is not in use.
     */
    int32_t (*getTouches)(ArkUI_NodeTouchPoint** points);

    /**
     * @brief Returns the historical point information of this event, which covers actions that occur between
     * this event and the previous event.
     * @param historicalPoints Indicates the pointer to the object that receives data.
     * @return Returns the number of elements in the historical touch point information array.
     * @note
     * When this function is called, ArkUI creates a heap memory object of the historical touch point information array
     * and returns the pointer to the pointer. You need to call <b>delete[]</b> to manually free the memory
     * when the object is not in use.
     */
    int32_t (*getHistoricalPoints)(ArkUI_NodeHistoricalTouchPoint** historicalPoints);

    /** Source type of the touch event. */
    ArkUI_NodeSourceType sourceType;

    /** Whether to prevent propagation of the event to the parent node. */
    bool stopPropagation;

    /** Whether to prevent the default event processing behavior of
    * the current node and allow propagation of the event. */
    bool preventDefault;
} ArkUI_NodeTouchEvent;

/**
 * @brief Defines the common structure type of a component event.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Enumerates the event types.
     *
     * @see ArkUI_NodeEventType
     */
    int32_t kind;

    /**
     * @brief Defines the custom ID of the event.
     *
     * The event ID is passed as a parameter in {@link registerNodeEvent} and can be applied to the dispatch logic
     * of the same event entry function {@link registerNodeEventReceiver}.
     */
    int32_t eventId;

    /** Component object that triggers the event. */
    ArkUI_NodeHandle node;
    union {
        /** Callback parameter of the touch event type. */
        ArkUI_NodeTouchEvent touchEvent;
        /** The universal component event uses callback parameters of the number type. */
        ArkUI_NodeComponentEvent componentEvent;
        /** The universal component event uses callback parameters of the string type. */
        ArkUI_StringAsyncEvent stringEvent;
    };
    /**
     * @brief Defines the custom parameter of the event.
     *
     * This parameter is passed in {@link registerNodeEvent} and can be applied to the service logic when the event
     * is triggered.
     */
    void* extraParam;
} ArkUI_CompatibleNodeEvent;

/**
 * @brief Declares a collection of native node APIs provided by ArkUI.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /** Struct version. */
    int32_t version;

    /**
     * @brief Creates a component based on {@link ArkUI_NodeType} and returns the pointer to the created component.
     *
     * @param type Indicates the type of component to create.
     * @return Returns the pointer to the created component. If the component fails to be created, NULL is returned.
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief Destroys the component to which the specified pointer points.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the pointer.
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief Adds a component to a parent node.
     *
     * When the parent component is being displayed, this API must be called in the main thread.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     */
    int32_t (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Removes a component from its parent node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     */
    int32_t (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Inserts a component to a parent node after the specified <b>sibling</b> node.
     *
     * When the parent component is being displayed, this API must be called in the main thread.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node after which the target node is to be inserted.
     * If the value is null, the node is inserted at the start of the parent node.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to a parent node before the specified <b>sibling</b> node.
     *
     * When the parent component is being displayed, this API must be called in the main thread.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node before which the target node is to be inserted.
     * If the value is null, the node is inserted at the end of the parent node.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildBefore)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to the specified position in a parent node.
     *
     * When the parent component is being displayed, this API must be called in the main thread.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param position Indicates the position to which the target child node is to be inserted. If the value is a
     * negative number or invalid, the node is inserted at the end of the parent node.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildAt)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, int32_t position);

    /**
     * @brief Sets the attribute of a node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the node whose attribute needs to be set.
     * @param attribute Indicates the type of attribute to set.
     * @param value Indicates the attribute value.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     * Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* item);

    /**
     * @brief Obtains an attribute.
     *
     * The pointer returned by this API is an internal buffer pointer of the ArkUI framework. As such, you do not need
     * to call <b>delete</b> to release the memory. However, the pointer must be used before this API is called next
     * time. Otherwise, the pointer may be overwritten by other values.
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the node whose attribute needs to be obtained.
     * @param attribute Indicates the type of attribute to obtain.
     * @return Returns the attribute value. If the operation fails, a null pointer is returned.
     */
    const ArkUI_AttributeItem* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Resets an attribute.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the node whose attribute needs to be reset.
     * @param attribute Indicates the type of attribute to reset.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     * Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Registers an event for the specified node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to register.
     * @param eventId Indicates the custom event ID, which is passed in the callback of <@link ArkUI_NodeEvent>
     * when the event is triggered.
     * @return Returns 0 if success.
     * Returns 401 if a parameter exception occurs.
     * Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*registerNodeEvent)(
        ArkUI_NodeHandle node, ArkUI_NodeEventType eventType, int32_t eventId);

    /**
     * @brief Unregisters an event for the specified node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to unregister.
     */
    void (*unregisterNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

    /**
     * @brief Registers an event receiver.
     *
     * The ArkUI framework collects component events generated during the process and calls back the events through the
     * registered event receiver. \n
     * A new call to this API will overwrite the previously registered event receiver.
     *
     * @param eventReceiver Indicates the event receiver to register.
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_CompatibleNodeEvent* event));

    /**
     * @brief Unregisters the event receiver.
     *
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief Forcibly marks the current node that needs to be measured, laid out, or rendered again.
     *
     * Regarding updates to system attributes, the ArkUI framework automatically marks the dirty area and performs
     * measuring, layout, or rendering again. In this case, you do not need to call this API.
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the node for which you want to mark as dirty area.
     * @param dirtyFlag Indicates type of dirty area.
     */
    void (*markDirty)(ArkUI_NodeHandle node, ArkUI_NodeDirtyFlag dirtyFlag);
} ArkUI_NativeNodeAPI_Compatible;


#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_COMPATIBLE
/** @} */

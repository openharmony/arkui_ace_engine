/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_EXTENED_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_EXTENED_H

#include "drawable_descriptor.h"
#include "native_node.h"
#include "native_type.h"
#include "resource.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "pixelmap_native_impl.h"

#ifdef __cplusplus
extern "C" {
#endif
struct ArkUI_LayoutConstraint {
    /** 元素最小宽度。 */
    int32_t minWidth;
    /** 元素最小高度。 */
    int32_t minHeight;
    /** 元素最大宽度。 */
    int32_t maxWidth;
    /** 元素最小宽度。 */
    int32_t maxHeight;
    /** 元素宽度百分比基准。 */
    int32_t percentReferWidth;
    /** 元素高度百分比基准。*/
    int32_t percentReferHeight;
};

/**
 * @brief 定义自定义组件回调事件的参数类型。
 *
 * @since 12
 */
struct ArkUI_CustomNodeAsyncEvent {
    /** 数据数组对象。*/
    ArkUI_NumberValue data[MAX_COMPONENT_EVENT_ARG_NUM];
};

/**
 * 定义组件绘制上下文类型结构。
 *
 * @since 12
 */
struct ArkUI_DrawContext {
    /** 画布宽度。*/
    int32_t width;
    /** 画布高度。*/
    int32_t height;
    /** 绘制的画布。*/
    void* canvas;
};

/**
 * @brief 定义自定义组件事件的通用结构类型。
 *
 * @since 12
 */
struct ArkUI_NodeCustomEvent {
    int32_t targetId;
    ArkUI_NodeHandle node;
    ArkUICustomNodeEvent* event;
    ArkUI_LayoutConstraint constraint;
    void* userData;
};

struct ArkUI_OptionalFloat {
    int32_t isSet;
    float value;
};

struct ArkUI_OptionalInt {
    int32_t isSet;
    int32_t value;
};

struct ArkUI_OptionalUint {
    int32_t isSet;
    uint32_t value;
};

struct ArkUI_OptionalCharPtr {
    int32_t isSet;
    const char* value;
};

struct ArkUI_SwiperIndicator {
    ArkUI_SwiperIndicatorType type;
    ArkUI_OptionalFloat dimLeft;
    ArkUI_OptionalFloat dimTop;
    ArkUI_OptionalFloat dimRight;
    ArkUI_OptionalFloat dimBottom;
    ArkUI_OptionalFloat itemWidth;
    ArkUI_OptionalFloat itemHeight;
    ArkUI_OptionalFloat selectedItemWidth;
    ArkUI_OptionalFloat selectedItemHeight;
    ArkUI_OptionalInt maskValue;
    ArkUI_OptionalUint colorValue;
    ArkUI_OptionalUint selectedColorValue;
    ArkUI_OptionalInt maxDisplayCount;
};

struct ArkUI_DrawableDescriptor {
    OH_PixelmapNativeHandle pixelMap;
    OH_PixelmapNativeHandle* pixelMapArray;
    ArkUI_Int32 size;
    std::shared_ptr<OHOS::Ace::Napi::DrawableDescriptor> drawableDescriptor;
    std::shared_ptr<OHOS::Ace::Napi::AnimatedDrawableDescriptor> animatedDrawableDescriptor;
    std::shared_ptr<OHOS::Ace::Napi::LayeredDrawableDescriptor> layeredDrawableDescriptor;
    std::shared_ptr<ArkUI_Resource> resource;
};

struct ArkUI_AccessibilityState {
    ArkUI_OptionalInt isDisabled;
    ArkUI_OptionalInt isSelected;
    ArkUI_OptionalInt checkedType;
};

struct ArkUI_AccessibilityValue {
    ArkUI_OptionalInt min;
    ArkUI_OptionalInt max;
    ArkUI_OptionalInt current;
    ArkUI_OptionalInt rangeMin;
    ArkUI_OptionalInt rangeMax;
    ArkUI_OptionalInt rangeCurrent;
    ArkUI_OptionalCharPtr text;
};

struct ArkUI_CustomSpanMeasureInfo {
    float fontSize;
};

struct ArkUI_CustomSpanMetrics {
    float width;
    float height;
};

struct ArkUI_CustomSpanDrawInfo {
    float optionsX;
    float optionsLineTop;
    float optionsLineBottom;
    float optionsBaseLine;
};

struct ArkUI_CustomProperty {
    char* value;
};

struct ArkUI_HostWindowInfo {
    char* name;
};

struct ArkUI_ActiveChildrenInfo {
    ArkUI_NodeHandle* nodeList;
    int32_t nodeCount;
};

#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::NodeModel {

void NodeAddExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);
int32_t RegisterNodeCustomEvent(
    ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);
void NodeRemoveExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType);
void UnregisterNodeCustomEvent(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType);
void RegisterNodeCustomReceiver(void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
void UnregisterNodeCustomEventReceiver();
void HandleInnerCustomEvent(ArkUICustomNodeEvent* origin);
void HandleCustomEvent(ArkUI_NodeCustomEvent* event);
int32_t AddNodeCustomEventReceiver(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
int32_t RemoveNodeCustomEventReceiver(ArkUI_NodeHandle nodePtr,
    void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
int32_t SetMeasuredSize(ArkUI_NodeHandle node, int32_t width, int32_t height);
int32_t SetLayoutPosition(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);
int32_t GetLayoutConstraint(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* layoutConstraint);
ArkUI_IntSize GetMeasuredSize(ArkUI_NodeHandle node);
ArkUI_IntOffset GetLayoutPosition(ArkUI_NodeHandle node);
int32_t MeasureNode(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* constraint);
int32_t LayoutNode(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);

uint32_t GetTotalChildCount(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetChildAt(ArkUI_NodeHandle node, int32_t position);
ArkUI_NodeHandle GetFirstChild(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetLastChild(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetPreviousSibling(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetNextSibling(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetParent(ArkUI_NodeHandle node);
int32_t RemoveAllChildren(ArkUI_NodeHandle parentNode);
} // namespace OHOS::Ace::NodeModel
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_EXTENED_H
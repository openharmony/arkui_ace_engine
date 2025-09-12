/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_H

#include <cstdint>
#include <set>
#include <vector>
#include <string>

#include "native_compatible.h"
#include "native_node.h"
#include "native_type.h"

#include "frameworks/core/common/ace_application_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_Node {
    int32_t type;
    ArkUINodeHandle uiNodeHandle = nullptr;
    bool cNode = false;
    bool threadSafeNode = false;
    bool buildNode = false;
    void* extraData = nullptr;
    void* extraCustomData = nullptr;
    ArkUI_LengthMetricUnit lengthMetricUnit = ARKUI_LENGTH_METRIC_UNIT_DEFAULT;
    void* eventListeners = nullptr;
    void* barrierOption = nullptr;
    void* guidelineOption = nullptr;
    void* alignRuleOption = nullptr;
    void* userData = nullptr;
    void* swiperIndicator = nullptr;
    int32_t linearGradientDirection = -1;
    void* customEventListeners = nullptr;
    void* altDrawableDescriptor = nullptr;
    void* drawableDescriptor = nullptr;
    void* imageFrameInfos = nullptr;
    ArkUI_AttributeItem* areaChangeRadio = nullptr;
    void* transitionOption = nullptr;
    void* progressLinearStyle = nullptr;
    void* visibleAreaEventOptions = nullptr;
    bool isBindNative = false;
    void* commonEventListeners = nullptr;
    void* extraCommonData = nullptr;
    void* gridLayoutOptions =  nullptr;
};

struct ArkUI_Context {
    int32_t id;
};

constexpr int BASIC_COMPONENT_NUM = 22;
struct ArkUI_GuidelineStyle {
    std::string id;
    ArkUI_Axis direction;
    float start;
    bool hasStart;
    float end;
    bool hasEnd;
};

struct ArkUI_GuidelineOption {
    std::vector<ArkUI_GuidelineStyle> styles;
};

struct ArkUI_BarrierStyle {
    std::string id;
    ArkUI_BarrierDirection direction;
    std::vector<std::string> referencedId;
};

struct ArkUI_BarrierOption {
    std::vector<ArkUI_BarrierStyle> styles;
};

struct ArkUI_HorizontalAlignRule {
    bool hasValue;
    std::string anchor;
    ArkUI_HorizontalAlignment align;
};

struct ArkUI_VerticalAlignRule {
    bool hasValue;
    std::string anchor;
    ArkUI_VerticalAlignment align;
};

struct ArkUI_AlignmentRuleOption {
    ArkUI_HorizontalAlignRule left;
    ArkUI_HorizontalAlignRule middle;
    ArkUI_HorizontalAlignRule right;
    ArkUI_VerticalAlignRule top;
    ArkUI_VerticalAlignRule center;
    ArkUI_VerticalAlignRule bottom;
    float biasHorizontal;
    float biasVertical;
};

struct InnerEventExtraParam {
    int32_t targetId;
    ArkUI_NodeHandle nodePtr;
    void* userData;
};

struct ExtraData {
    std::unordered_map<int64_t, InnerEventExtraParam*> eventMap;
};

#ifdef __cplusplus
};
#endif

struct ArkUIFullNodeAPI;

namespace OHOS::Ace::NodeModel {

inline bool UsePXUnit(ArkUI_NodeHandle nodePtr)
{
    return nodePtr && (nodePtr->lengthMetricUnit == ARKUI_LENGTH_METRIC_UNIT_PX);
}

bool InitialFullImpl();
ArkUIFullNodeAPI* GetFullImpl();
ArkUI_NodeHandle CreateNode(ArkUI_NodeType type);
void DisposeNativeSource(ArkUI_NodeHandle nativePtr);
void DisposeNode(ArkUI_NodeHandle nativePtr);
bool IsValidArkUINode(ArkUI_NodeHandle nodePtr);

int32_t AddChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t RemoveChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t InsertChildAfter(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildBefore(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildAt(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, int32_t position);

// deprecated.
[[deprecated]] void SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value);

int32_t SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value);
const ArkUI_AttributeItem* GetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
int32_t ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId);
int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId, void* userData);
void UnregisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType);
bool GreatOrEqualTargetAPIVersion(OHOS::Ace::PlatformVersion platfromVersion);
void RegisterOnEvent(void (*eventReceiver)(ArkUI_NodeEvent* event));
void RegisterOnEvent(void (*eventReceiver)(ArkUI_CompatibleNodeEvent* event));
void UnregisterOnEvent();
void HandleTouchEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
void HandleMouseEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
void HandleKeyEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
void HandleFocusAxisEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
void HandleHoverEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
void HandleClickEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent);
int32_t CheckEvent(ArkUI_NodeEvent* event);
void HandleInnerNodeEvent(ArkUINodeEvent* innerEvent);
int32_t GetNativeNodeEventType(ArkUINodeEvent* innerEvent, bool isCommonEvent);
void HandleNodeEvent(ArkUI_NodeEvent* event);
void TriggerNodeEvent(ArkUI_NodeEvent* event, std::set<void (*)(ArkUI_NodeEvent*)>* eventListenersSet);
void HandleInnerNodeCommonEvent(ArkUINodeEvent* innerEvent);
void HandleNodeCommonEvent(ArkUI_NodeEvent* event, int32_t eventType);
void TriggerNodeCommonEvent(ArkUI_NodeEvent* event, int32_t eventType,
    std::map<uint32_t, void (*)(ArkUI_NodeEvent*)>* commonEventListenersMap);
void ApplyModifierFinish(ArkUI_NodeHandle nodePtr);
void MarkDirty(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag);

int32_t SetUserData(ArkUI_NodeHandle node, void* userData);
void* GetUserData(ArkUI_NodeHandle node);
int32_t SetLengthMetricUnit(ArkUI_NodeHandle nodePtr, ArkUI_LengthMetricUnit unit);
int32_t AddNodeEventReceiver(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
int32_t RemoveNodeEventReceiver(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
void* GetParseJsMedia();
uint32_t GetDrawableType(void* object);
void IncreaseRefDrawable(void* object);
void DecreaseRefDrawable(void* object);
void* CreateDrawable(uint32_t type);
void SetTotalDuration(void* object, int32_t duration);
int32_t GetTotalDuration(void* object);
void SetIterations(void* object, int32_t duration);
int32_t GetIterations(void* object);
bool CheckIsCNode(ArkUI_NodeHandle node);
bool CheckIsCNodeOrCrossLanguage(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetArkUINode(ArkUINodeHandle node);
int32_t GetNodeTypeByTag(ArkUI_NodeHandle node);
std::string ConvertNodeTypeToTag(ArkUI_NodeType nodeType);
void RegisterBindNativeNode(ArkUI_NodeHandle node);
bool MakeCommonEventMap(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType, void* userData,
    void (*callback)(ArkUI_NodeEvent* event));
bool ClearCommonEventMap(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);
}; // namespace OHOS::Ace::NodeModel
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_H

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"

namespace OHOS::Ace::NG {
namespace {
const float ERROR_FLOAT_CODE = -1.0f;
constexpr int32_t DEFAULT_FRICTION = 62;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetRefreshing(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshing(frameNode, static_cast<bool>(value));
}

ArkUI_Bool GetRefreshing(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(RefreshModelNG::GetRefreshing(frameNode));
}

void SetRefreshOffset(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshOffset(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    RefreshModelNG::CreateWithResourceObjRefreshOffset(
        frameNode, AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

void ResetRefreshOffset(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshOffset(frameNode, Dimension(0.0f, DimensionUnit::VP));
    RefreshModelNG::CreateWithResourceObjRefreshOffset(frameNode, nullptr);
}

void SetIndicatorOffset(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetIndicatorOffset(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetIndicatorOffset(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetIndicatorOffset(frameNode, Dimension(0.0f, DimensionUnit::VP));
}

void SetPullToRefresh(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullToRefresh(frameNode, value);
}

void ResetPullToRefresh(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullToRefresh(frameNode, true);
}

void SetPullUpToCancelRefresh(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullUpToCancelRefresh(frameNode, value);
}

void ResetPullUpToCancelRefresh(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullUpToCancelRefresh(frameNode, true);
}

void SetRefreshContent(ArkUINodeHandle node, ArkUINodeHandle content)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto contentNode = reinterpret_cast<FrameNode*>(content);
    CHECK_NULL_VOID(contentNode);
    RefreshModelNG::SetCustomBuilder(frameNode, contentNode);
}

void SetPullDownRatio(ArkUINodeHandle node, ArkUI_Float32 ratio)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    float value = ratio;
    std::optional<float> ratioValue = value;
    RefreshModelNG::SetPullDownRatio(frameNode, ratioValue);
}

void ResetPullDownRatio(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> ratioValue = std::nullopt;
    RefreshModelNG::SetPullDownRatio(frameNode, ratioValue);
}

ArkUI_Float32 GetPullDownRatio(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return RefreshModelNG::GetPullDownRatio(frameNode);
}

ArkUI_Float32 GetRefreshOffset(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return RefreshModelNG::GetRefreshOffset(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Bool GetPullToRefresh(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(RefreshModelNG::GetPullToRefresh(frameNode));
}

ArkUI_Bool GetPullUpToCancelRefresh(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(RefreshModelNG::GetPullUpToCancelRefresh(frameNode));
}

void SetRefreshOnStateChangeCallback(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onStateChangeEvent = reinterpret_cast<StateChangeEvent*>(callback);
        RefreshModelNG::SetOnStateChange(frameNode, std::move(*onStateChangeEvent));
    } else {
        RefreshModelNG::SetOnStateChange(frameNode, nullptr);
    }
}

void ResetRefreshOnStateChangeCallback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnStateChange(frameNode, nullptr);
}

void SetOnRefreshingCallback(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onRefreshingEvent = reinterpret_cast<RefreshingEvent*>(callback);
        RefreshModelNG::SetOnRefreshing(frameNode, std::move(*onRefreshingEvent));
    } else {
        RefreshModelNG::SetOnRefreshing(frameNode, nullptr);
    }
}

void ResetOnRefreshingCallback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnRefreshing(frameNode, nullptr);
}

void SetRefreshOnOffsetChangeCallback(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onOffsetChangeEvent = reinterpret_cast<OffsetChangeEvent*>(callback);
        RefreshModelNG::SetOnOffsetChange(frameNode, std::move(*onOffsetChangeEvent));
    } else {
        RefreshModelNG::SetOnOffsetChange(frameNode, nullptr);
    }
}

void ResetRefreshOnOffsetChangeCallback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnOffsetChange(frameNode, nullptr);
}

void SetMaxPullDownDistance(ArkUINodeHandle node, ArkUI_Float32 distance, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> distanceValue = distance;
    RefreshModelNG::SetMaxPullDownDistance(frameNode, distanceValue);
    RefreshModelNG::CreateWithResourceObjMaxPullDownDistance(
        frameNode, AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

void ResetMaxPullDownDistance(ArkUINodeHandle node, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> distanceValue = std::nullopt;
    RefreshModelNG::SetMaxPullDownDistance(frameNode, distanceValue);
    RefreshModelNG::CreateWithResourceObjMaxPullDownDistance(
        frameNode, AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

ArkUI_Float32 GetMaxPullDownDistance(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return RefreshModelNG::GetMaxPullDownDistance(frameNode);
}

void SetOnStepOffsetChangeCallback(ArkUINodeHandle node,
    void (*callback)(const ArkUI_Float32 offset, void* extraData, const bool isDrag), void* extraData)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode && callback);
    auto onChange = [callback, extraData](
                        const float offset, const bool isDrag) { callback(offset, extraData, isDrag); };
    RefreshModelNG::SetStepOffsetChange(frameNode, std::move(onChange));
}

void ResetOnStepOffsetChangeCallback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetStepOffsetChange(frameNode, nullptr);
}

ArkUINodeHandle CreateRefreshFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = RefreshModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void InitCoordinationEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    auto* coordinationEvent = reinterpret_cast<RefPtr<ScrollableCoordinationEvent>*>(callback);
    CHECK_NULL_VOID(coordinationEvent);
    pattern->InitCoordinationEvent(*coordinationEvent);
}

void CreateRefresh()
{
    RefreshModelNG model;
    model.Create();
}

void SetFriction(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetFriction(frameNode, static_cast<int32_t>(friction));
}

void ResetFriction(ArkUINodeHandle node)
{
    SetFriction(node, DEFAULT_FRICTION);
}

void SetOnChangeEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto changeEvent = reinterpret_cast<RefreshChangeEvent*>(callback);
        RefreshModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
    } else {
        RefreshModelNG::SetChangeEvent(frameNode, nullptr);
    }
}


void ResetOnChangeEvent(ArkUINodeHandle node)
{
    SetOnChangeEvent(node, nullptr);
}

void SetBuilder(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto* builderFunc = reinterpret_cast<std::function<void()>*>(callback);
        if (builderFunc && *builderFunc) {
            NG::ScopedViewStackProcessor scopedViewStackProcessor;
            (*builderFunc)();
            auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
            auto customFrameNode = AceType::DynamicCast<FrameNode>(customNode);
            if (customFrameNode) {
                RefreshModelNG::SetCustomBuilder(frameNode, AceType::RawPtr(customFrameNode));
            }
        }
    }
}

void ResetBuilder(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetCustomBuilder(frameNode, nullptr);
}

void SetIsCustomBuilderExist(ArkUINodeHandle node, ArkUI_Bool isExist)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetIsCustomBuilderExist(frameNode, static_cast<bool>(isExist));
}

void ResetIsCustomBuilderExist(ArkUINodeHandle node)
{
    SetIsCustomBuilderExist(node, false);
}

void SetLoadingText(ArkUINodeHandle node, const char* text, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* resObj = reinterpret_cast<ResourceObject*>(resObjRawPtr);
    RefPtr<ResourceObject> resObjRef = resObj ? AceType::Claim(resObj) : nullptr;
    if (resObjRef) {
        RefreshModelNG::CreateWithResourceObj(frameNode, resObjRef);
    }
    if (text) {
        RefreshModelNG::SetLoadingText(frameNode, std::string(text));
    }
}

void ResetLoadingText(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::ResetLoadingText(frameNode);
}

} // namespace

#ifndef CROSS_PLATFORM
RefreshModel* GetRefreshModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("refresh");
    static RefreshModel* instance = loader ? reinterpret_cast<RefreshModel*>(loader->CreateModel()) : nullptr;
    return instance;
}

void SetRefreshingImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetRefreshModelImpl()->SetRefreshing(static_cast<bool>(value));
}

ArkUI_Bool GetRefreshingImpl(ArkUINodeHandle node)
{
    return false;
}

void SetRefreshOffsetImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_VoidPtr resObjRawPtr)
{
    GetRefreshModelImpl()->SetRefreshOffset(Dimension(value, static_cast<DimensionUnit>(unit)));
    GetRefreshModelImpl()->CreateWithResourceObjRefreshOffset(
        AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

void ResetRefreshOffsetImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetRefreshOffset(Dimension(0.0f, DimensionUnit::VP));
    GetRefreshModelImpl()->CreateWithResourceObjRefreshOffset(nullptr);
}

void SetPullToRefreshImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetRefreshModelImpl()->SetPullToRefresh(value);
}

void ResetPullToRefreshImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetPullToRefresh(true);
}

void SetPullUpToCancelRefreshImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetRefreshModelImpl()->SetPullUpToCancelRefresh(value);
}

void ResetPullUpToCancelRefreshImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetPullUpToCancelRefresh(true);
}

void SetRefreshContentImpl(ArkUINodeHandle node, ArkUINodeHandle content) {}

void SetPullDownRatioImpl(ArkUINodeHandle node, ArkUI_Float32 ratio)
{
    std::optional<float> ratioValue = ratio;
    GetRefreshModelImpl()->SetPullDownRatio(ratioValue);
}

void ResetPullDownRatioImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetPullDownRatio(std::nullopt);
}

ArkUI_Float32 GetPullDownRatioImpl(ArkUINodeHandle node)
{
    return ERROR_FLOAT_CODE;
}

ArkUI_Float32 GetRefreshOffsetImpl(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    return ERROR_FLOAT_CODE;
}

ArkUI_Bool GetPullToRefreshImpl(ArkUINodeHandle node)
{
    return false;
}

ArkUI_Bool GetPullUpToCancelRefreshImpl(ArkUINodeHandle node)
{
    return false;
}

void SetRefreshOnStateChangeCallbackImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onStateChangeEvent = reinterpret_cast<StateChangeEvent*>(callback);
        GetRefreshModelImpl()->SetOnStateChange(std::move(*onStateChangeEvent));
    }
}

void ResetRefreshOnStateChangeCallbackImpl(ArkUINodeHandle node) {}

void SetOnRefreshingCallbackImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onRefreshingEvent = reinterpret_cast<RefreshingEvent*>(callback);
        GetRefreshModelImpl()->SetOnRefreshing(std::move(*onRefreshingEvent));
    }
}

void ResetOnRefreshingCallbackImpl(ArkUINodeHandle node) {}

void SetRefreshOnOffsetChangeCallbackImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onOffsetChangeEvent = reinterpret_cast<OffsetChangeEvent*>(callback);
        GetRefreshModelImpl()->SetOnOffsetChange(std::move(*onOffsetChangeEvent));
    }
}

void ResetRefreshOnOffsetChangeCallbackImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->ResetOnOffsetChange();
}

void SetMaxPullDownDistanceImpl(ArkUINodeHandle node, ArkUI_Float32 distance, ArkUI_VoidPtr resObjRawPtr)
{
    std::optional<float> distanceValue = std::max(distance, 0.0f);
    GetRefreshModelImpl()->SetMaxPullDownDistance(distanceValue);
    GetRefreshModelImpl()->CreateWithResourceObjMaxPullDownDistance(
        AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

void ResetMaxPullDownDistanceImpl(ArkUINodeHandle node, ArkUI_VoidPtr resObjRawPtr)
{
    GetRefreshModelImpl()->SetMaxPullDownDistance(std::nullopt);
    GetRefreshModelImpl()->CreateWithResourceObjMaxPullDownDistance(
        AceType::Claim(static_cast<ResourceObject*>(resObjRawPtr)));
}

ArkUI_Float32 GetMaxPullDownDistanceImpl(ArkUINodeHandle node)
{
    return ERROR_FLOAT_CODE;
}

void SetOnStepOffsetChangeCallbackImpl(ArkUINodeHandle node,
    void (*callback)(const ArkUI_Float32 offset, void* extraData, const bool isDrag), void* extraData)
{}

void ResetOnStepOffsetChangeCallbackImpl(ArkUINodeHandle node) {}

ArkUINodeHandle CreateRefreshFrameNodeImpl(ArkUI_Uint32 nodeId)
{
    return nullptr;
}

void InitCoordinationEventImpl(ArkUINodeHandle node, void* callback) {}

void SetFrictionImpl(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    GetRefreshModelImpl()->SetFriction(static_cast<int32_t>(friction));
}

void ResetFrictionImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetFriction(DEFAULT_FRICTION);
}

void SetOnChangeEventImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto changeEvent = reinterpret_cast<RefreshChangeEvent*>(callback);
        GetRefreshModelImpl()->SetChangeEvent(std::move(*changeEvent));
    }
}

void ResetOnChangeEventImpl(ArkUINodeHandle node) {}

void SetBuilderImpl(ArkUINodeHandle node, void* callback) {}

void ResetBuilderImpl(ArkUINodeHandle node) {}

void CreateRefreshImpl()
{
    GetRefreshModelImpl()->Create();
}

void SetIsCustomBuilderExistImpl(ArkUINodeHandle node, ArkUI_Bool isExist)
{
    GetRefreshModelImpl()->SetIsCustomBuilderExist(isExist);
}

void ResetIsCustomBuilderExistImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->SetIsCustomBuilderExist(false);
}

void SetLoadingTextImpl(ArkUINodeHandle node, const char* text, ArkUI_VoidPtr resObjRawPtr)
{
    auto* resObj = reinterpret_cast<ResourceObject*>(resObjRawPtr);
    RefPtr<ResourceObject> resObjRef = resObj ? AceType::Claim(resObj) : nullptr;
    if (resObjRef) {
        GetRefreshModelImpl()->CreateWithResourceObj(resObjRef);
    }
    if (text) {
        GetRefreshModelImpl()->SetLoadingText(std::string(text));
    }
}

void ResetLoadingTextImpl(ArkUINodeHandle node)
{
    GetRefreshModelImpl()->ResetLoadingText();
}

void SetIndicatorOffsetImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_VoidPtr resObjRawPtr) {}

void ResetIndicatorOffsetImpl(ArkUINodeHandle node) {}
#endif

namespace NodeModifier {

const ArkUIRefreshModifier* GetRefreshModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN();
        static const ArkUIRefreshModifier modifier = {
            .setRefreshing = SetRefreshingImpl,
            .getRefreshing = GetRefreshingImpl,
            .setRefreshOffset = SetRefreshOffsetImpl,
            .resetRefreshOffset = ResetRefreshOffsetImpl,
            .setPullToRefresh = SetPullToRefreshImpl,
            .resetPullToRefresh = ResetPullToRefreshImpl,
            .setPullUpToCancelRefresh = SetPullUpToCancelRefreshImpl,
            .resetPullUpToCancelRefresh = ResetPullUpToCancelRefreshImpl,
            .setRefreshContent = SetRefreshContentImpl,
            .setPullDownRatio = SetPullDownRatioImpl,
            .resetPullDownRatio = ResetPullDownRatioImpl,
            .getPullDownRatio = GetPullDownRatioImpl,
            .getRefreshOffset = GetRefreshOffsetImpl,
            .getPullToRefresh = GetPullToRefreshImpl,
            .getPullUpToCancelRefresh = GetPullUpToCancelRefreshImpl,
            .setRefreshOnStateChangeCallback = SetRefreshOnStateChangeCallbackImpl,
            .resetRefreshOnStateChangeCallback = ResetRefreshOnStateChangeCallbackImpl,
            .setOnRefreshingCallback = SetOnRefreshingCallbackImpl,
            .resetOnRefreshingCallback = ResetOnRefreshingCallbackImpl,
            .setRefreshOnOffsetChangeCallback = SetRefreshOnOffsetChangeCallbackImpl,
            .resetRefreshOnOffsetChangeCallback = ResetRefreshOnOffsetChangeCallbackImpl,
            .setMaxPullDownDistance = SetMaxPullDownDistanceImpl,
            .resetMaxPullDownDistance = ResetMaxPullDownDistanceImpl,
            .getMaxPullDownDistance = GetMaxPullDownDistanceImpl,
            .setOnStepOffsetChangeCallback = SetOnStepOffsetChangeCallbackImpl,
            .resetOnStepOffsetChangeCallback = ResetOnStepOffsetChangeCallbackImpl,
            .createRefreshFrameNode = CreateRefreshFrameNodeImpl,
            .initCoordinationEvent = InitCoordinationEventImpl,
            .setFriction = SetFrictionImpl,
            .resetFriction = ResetFrictionImpl,
            .setOnChangeEvent = SetOnChangeEventImpl,
            .resetOnChangeEvent = ResetOnChangeEventImpl,
            .setBuilder = SetBuilderImpl,
            .resetBuilder = ResetBuilderImpl,
            .createRefresh = CreateRefreshImpl,
            .setIsCustomBuilderExist = SetIsCustomBuilderExistImpl,
            .resetIsCustomBuilderExist = ResetIsCustomBuilderExistImpl,
            .setLoadingText = SetLoadingTextImpl,
            .resetLoadingText = ResetLoadingTextImpl,
            .setIndicatorOffset = SetIndicatorOffsetImpl,
            .resetIndicatorOffset = ResetIndicatorOffsetImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIRefreshModifier modifier = {
        .setRefreshing = SetRefreshing,
        .getRefreshing = GetRefreshing,
        .setRefreshOffset = SetRefreshOffset,
        .resetRefreshOffset = ResetRefreshOffset,
        .setPullToRefresh = SetPullToRefresh,
        .resetPullToRefresh = ResetPullToRefresh,
        .setPullUpToCancelRefresh = SetPullUpToCancelRefresh,
        .resetPullUpToCancelRefresh = ResetPullUpToCancelRefresh,
        .setRefreshContent = SetRefreshContent,
        .setPullDownRatio = SetPullDownRatio,
        .resetPullDownRatio = ResetPullDownRatio,
        .getPullDownRatio = GetPullDownRatio,
        .getRefreshOffset = GetRefreshOffset,
        .getPullToRefresh = GetPullToRefresh,
        .getPullUpToCancelRefresh = GetPullUpToCancelRefresh,
        .setRefreshOnStateChangeCallback = SetRefreshOnStateChangeCallback,
        .resetRefreshOnStateChangeCallback = ResetRefreshOnStateChangeCallback,
        .setOnRefreshingCallback = SetOnRefreshingCallback,
        .resetOnRefreshingCallback = ResetOnRefreshingCallback,
        .setRefreshOnOffsetChangeCallback = SetRefreshOnOffsetChangeCallback,
        .resetRefreshOnOffsetChangeCallback = ResetRefreshOnOffsetChangeCallback,
        .setMaxPullDownDistance = SetMaxPullDownDistance,
        .resetMaxPullDownDistance = ResetMaxPullDownDistance,
        .getMaxPullDownDistance = GetMaxPullDownDistance,
        .setOnStepOffsetChangeCallback = SetOnStepOffsetChangeCallback,
        .resetOnStepOffsetChangeCallback = ResetOnStepOffsetChangeCallback,
        .createRefreshFrameNode = CreateRefreshFrameNode,
        .initCoordinationEvent = InitCoordinationEvent,
        .setFriction = SetFriction,
        .resetFriction = ResetFriction,
        .setOnChangeEvent = SetOnChangeEvent,
        .resetOnChangeEvent = ResetOnChangeEvent,
        .setBuilder = SetBuilder,
        .resetBuilder = ResetBuilder,
        .createRefresh = CreateRefresh,
        .setIsCustomBuilderExist = SetIsCustomBuilderExist,
        .resetIsCustomBuilderExist = ResetIsCustomBuilderExist,
        .setLoadingText = SetLoadingText,
        .resetLoadingText = ResetLoadingText,
        .setIndicatorOffset = SetIndicatorOffset,
        .resetIndicatorOffset = ResetIndicatorOffset,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

const CJUIRefreshModifier* GetCJUIRefreshModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const CJUIRefreshModifier modifier = {
        .setRefreshing = SetRefreshing,
        .getRefreshing = GetRefreshing,
        .setRefreshContent = SetRefreshContent,
        .setRefreshOffset = SetRefreshOffset,
        .resetRefreshOffset = ResetRefreshOffset,
        .setPullToRefresh = SetPullToRefresh,
        .resetPullToRefresh = ResetPullToRefresh,
        .setPullDownRatio = SetPullDownRatio,
        .resetPullDownRatio = ResetPullDownRatio,
        .getPullDownRatio = GetPullDownRatio,
        .getRefreshOffset = GetRefreshOffset,
        .getPullToRefresh = GetPullToRefresh,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG

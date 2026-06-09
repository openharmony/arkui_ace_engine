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

#include "core/common/container.h"
#include "core/components_ng/pattern/relative_container/bridge/relative_container_model_impl.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/interfaces/native/node/node_relative_container_modifier.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::RelativeContainerModelImpl* GetRelativeContainerModelImpl()
{
    static Framework::RelativeContainerModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

void CreateModel()
{
    RelativeContainerModelNG::CreateRelativeContainerModelNG();
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = RelativeContainerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

constexpr int NUM_2 = 2;
void SetGuideLine(ArkUINodeHandle node, ArkUIGuidelineStyle* values, ArkUI_Int32 size, void* rawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RelativeContainerModelNG::ResetResObj(frameNode, "relativeContainer.guideLine");
    std::vector<GuidelineInfo> guidelineInfos;
    for (int32_t i = 0; i < size; ++i) {
        GuidelineInfo info;
        std::string idStr(values[i].id);
        info.id = idStr;
        info.direction = static_cast<LineDirection>(values[i].direction);
        if (values[i].hasStart && values[i].hasEnd) {
            CalcDimension start(values[i].start, DimensionUnit::VP);
            info.start = start;
        } else if (values[i].hasStart) {
            CalcDimension start(values[i].start, DimensionUnit::VP);
            info.start = start;
        } else if (values[i].hasEnd) {
            CalcDimension end(values[i].end, DimensionUnit::VP);
            info.end = end;
        } else {
            CalcDimension start(0.0, DimensionUnit::VP);
            info.start = start;
        }
        if (SystemProperties::ConfigChangePerform() && rawPtr) {
            auto objs = *(reinterpret_cast<const std::vector<RefPtr<ResourceObject>>*>(rawPtr));
            RelativeContainerModelNG::SetPositionResObj(
                objs[NUM_2 * i], info, "relativeContainer.guideLine.position.start");
            RelativeContainerModelNG::SetPositionResObj(
                objs[NUM_2 * i + 1], info, "relativeContainer.guideLine.position.end");
        }
        guidelineInfos.push_back(info);
    }
    RelativeContainerModelNG::SetGuideline(frameNode, guidelineInfos);
}

void SetBarrier(ArkUINodeHandle node, ArkUIBarrierStyle* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<BarrierInfo> barrierInfos;
    for (int32_t i = 0; i < size; ++i) {
        BarrierInfo info;
        std::string idStr(values[i].id);
        info.id = idStr;
        info.direction = static_cast<BarrierDirection>(values[i].direction);
        auto referencedIdChar = values[i].referencedId;
        auto referencedIdSize = values[i].referencedIdSize;
        std::vector<std::string> referencedId;
        for (int32_t j = 0; j < referencedIdSize; ++j) {
            std::string idItem(referencedIdChar[j]);
            referencedId.push_back(idItem);
        }
        info.referencedId = referencedId;
        barrierInfos.push_back(info);
    }
    RelativeContainerModelNG::SetBarrier(frameNode, barrierInfos);
}

void GetGuideLine(ArkUINodeHandle node, ArkUIGuidelineStyle* values, ArkUI_Int32* size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    static std::vector<GuidelineInfo> guidelineInfos = RelativeContainerModelNG::GetGuideline(frameNode);
    int32_t index = 0;
    for (auto info : guidelineInfos) {
        values[index].id = info.id.c_str();
        values[index].direction = static_cast<ArkUI_Int32>(info.direction);
        values[index].start = static_cast<ArkUI_Float32>(info.start.has_value() ? info.start.value().Value() : 0);
        values[index].end = static_cast<ArkUI_Float32>(info.end.has_value() ? info.end.value().Value() : 0);
        index++;
    }
    *size = index;
}

void GetBarrier(ArkUINodeHandle node, ArkUIBarrierStyle* values, ArkUI_Int32* size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    static std::vector<BarrierInfo> barrierInfo = RelativeContainerModelNG::GetBarrier(frameNode);
    int32_t index = 0;
    for (auto info : barrierInfo) {
        if (index >= *size) {
            break;
        }
        values[index].id = info.id.c_str();
        values[index].direction = static_cast<ArkUI_Int32>(info.direction);
        values[index].referencedId = new ArkUI_CharPtr[info.referencedId.size()];
        int j = 0;
        for (auto str : info.referencedId) {
            values[index].referencedId[j++] = str.c_str();
        }
        values[index].referencedIdSize = j;
        index++;
    }
    *size = index;
}

void ResetGuideline(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RelativeContainerModelNG::ResetResObj(frameNode, "relativeContainer.guideLine");
    RelativeContainerModelNG::ResetGuideline(frameNode);
}

void ResetBarrier(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RelativeContainerModelNG::ResetBarrier(frameNode);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl()
{
    GetRelativeContainerModelImpl()->Create();
}

void SetGuideLineImpl(ArkUINodeHandle node, ArkUIGuidelineStyle* values, ArkUI_Int32 size, void* rawPtr)
{
    std::vector<GuidelineInfo> guidelineInfos;
    for (int32_t i = 0; i < size; ++i) {
        GuidelineInfo info;
        info.id = values[i].id ? std::string(values[i].id) : std::string();
        info.direction = static_cast<LineDirection>(values[i].direction);
        if (values[i].hasStart) {
            info.start = CalcDimension(values[i].start, DimensionUnit::VP);
        }
        if (values[i].hasEnd) {
            info.end = CalcDimension(values[i].end, DimensionUnit::VP);
        }
        if (!info.start.has_value() && !info.end.has_value()) {
            info.start = CalcDimension(0.0, DimensionUnit::VP);
        }
        guidelineInfos.emplace_back(info);
    }
    GetRelativeContainerModelImpl()->SetGuideline(guidelineInfos);
}

void SetBarrierImpl(ArkUINodeHandle node, ArkUIBarrierStyle* values, ArkUI_Int32 size)
{
    std::vector<BarrierInfo> barrierInfos;
    for (int32_t i = 0; i < size; ++i) {
        BarrierInfo info;
        info.id = values[i].id ? std::string(values[i].id) : std::string();
        info.direction = static_cast<BarrierDirection>(values[i].direction);
        auto referencedIdChar = values[i].referencedId;
        auto referencedIdSize = values[i].referencedIdSize;
        for (int32_t j = 0; j < referencedIdSize; ++j) {
            if (referencedIdChar && referencedIdChar[j]) {
                info.referencedId.emplace_back(referencedIdChar[j]);
            }
        }
        barrierInfos.emplace_back(info);
    }
    GetRelativeContainerModelImpl()->SetBarrier(barrierInfos);
}

void ResetGuidelineImpl(ArkUINodeHandle node)
{
    GetRelativeContainerModelImpl()->SetGuideline({});
}

void ResetBarrierImpl(ArkUINodeHandle node)
{
    GetRelativeContainerModelImpl()->SetBarrier({});
}
#endif

const ArkUIRelativeContainerModifier* GetRelativeContainerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIRelativeContainerModifier modifier = {
            .createModel = CreateModelImpl,
            .setGuideLine = SetGuideLineImpl,
            .setBarrier = SetBarrierImpl,
            .getGuideLine = nullptr,
            .getBarrier = nullptr,
            .resetGuideline = ResetGuidelineImpl,
            .resetBarrier = ResetBarrierImpl,
            .createFrameNode = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRelativeContainerModifier modifier = {
        .createModel = CreateModel,
        .setGuideLine = SetGuideLine,
        .setBarrier = SetBarrier,
        .getGuideLine = GetGuideLine,
        .getBarrier = GetBarrier,
        .resetGuideline = ResetGuideline,
        .resetBarrier = ResetBarrier,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIRelativeContainerModifier* GetCJUIRelativeContainerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRelativeContainerModifier modifier = {
        .setGuideLine = SetGuideLine,
        .setBarrier = SetBarrier,
        .getGuideLine = GetGuideLine,
        .getBarrier = GetBarrier,
        .resetGuideline = ResetGuideline,
        .resetBarrier = ResetBarrier,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG

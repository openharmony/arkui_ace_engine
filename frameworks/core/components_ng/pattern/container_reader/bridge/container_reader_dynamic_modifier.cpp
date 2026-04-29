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

#include "core/components_ng/pattern/container_reader/container_reader_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/common/window_size_breakpoint.h"

namespace OHOS::Ace::NG {

namespace {

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

} // namespace

void CreateContainerReader()
{
    static ContainerReaderModelNG model;
    model.Create();
}

void SetBreakPointConfig(ArkUINodeHandle node, double* widthArr, uint32_t widthLen,
    double* heightArr, uint32_t heightLen)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);

    auto* widthData = widthArr;
    auto* heightData = heightArr;
    std::vector<double> widthBreakpoints;
    std::vector<double> heightBreakpoints;
    if (widthData && widthLen > 0) {
        widthBreakpoints.assign(widthData, widthData + widthLen);
    }
    if (heightData && heightLen > 0) {
        heightBreakpoints.assign(heightData, heightData + heightLen);
    }
    ContainerReaderModelNG::SetBreakPointConfig(frameNode, widthBreakpoints, heightBreakpoints);
}
void ResetBreakPointConfig(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ContainerReaderModelNG::ResetBreakPointConfig(frameNode);
}
void SetOnSizeChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback == nullptr) {
        ContainerReaderModelNG::SetOnSizeChange(frameNode, nullptr);
        return;
    }
    auto* cb = reinterpret_cast<std::function<void(const SizeF&)>*>(callback);
    ContainerReaderModelNG::SetOnSizeChange(frameNode, std::move(*cb));
}

void SetOnWidthBreakpointChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback == nullptr) {
        ContainerReaderModelNG::SetOnWidthBreakpointChange(frameNode, nullptr);
        return;
    }
    auto* cb = reinterpret_cast<std::function<void(WidthBreakpoint)>*>(callback);
    ContainerReaderModelNG::SetOnWidthBreakpointChange(frameNode, std::move(*cb));
}

void SetOnHeightBreakpointChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback == nullptr) {
        ContainerReaderModelNG::SetOnHeightBreakpointChange(frameNode, nullptr);
        return;
    }
    auto* cb = reinterpret_cast<std::function<void(HeightBreakpoint)>*>(callback);
    ContainerReaderModelNG::SetOnHeightBreakpointChange(frameNode, std::move(*cb));
}

void SetRenderFunction(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback == nullptr) {
        ContainerReaderModelNG::SetRenderFunction(frameNode, nullptr);
        return;
    }

    //using ContainerReaderRenderFunction = std::function<RefPtr<UINode>(int64_t, bool&)>;
    auto* cb = reinterpret_cast<ContainerReaderRenderFunction*>(callback);
    ContainerReaderModelNG::SetRenderFunction(frameNode, std::move(*cb));
}

const ArkUIContainerReaderModifier* GetContainerReaderDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIContainerReaderModifier modifier = {
        .create = CreateContainerReader,
        .setBreakPointConfig = SetBreakPointConfig,
        .resetBreakPointConfig = ResetBreakPointConfig,
        .setOnSizeChange = SetOnSizeChange,
        .setOnWidthBreakpointChange = SetOnWidthBreakpointChange,
        .setOnHeightBreakpointChange = SetOnHeightBreakpointChange,
        .setRenderFunction = SetRenderFunction,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace OHOS::Ace::NG

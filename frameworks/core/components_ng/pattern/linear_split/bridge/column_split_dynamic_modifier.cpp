/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_impl.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
static Framework::LinearSplitModelImpl* GetLinearSplitModelImpl()
{
    static Framework::LinearSplitModelImpl instance;
    return &instance;
}
namespace {
static Framework::ViewAbstractModelImpl* GetViewAbstractModelImpl()
{
    static Framework::ViewAbstractModelImpl instance;
    return &instance;
}
} // namespace

} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_COLUMN_SPLIT_RESIZABLE = false;
constexpr Dimension DEFAULT_DIVIDER_START = Dimension(0.0, DimensionUnit::VP);
constexpr Dimension DEFAULT_DIVIDER_END = Dimension(0.0, DimensionUnit::VP);
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace
void CreateColumnSplit()
{
    static LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
}

void SetColumnSplitResizable(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::COLUMN_SPLIT, resizable);
}

void ResetColumnSplitResizable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::COLUMN_SPLIT, DEFAULT_COLUMN_SPLIT_RESIZABLE);
}

void SetColumnSplitDivider(ArkUINodeHandle node, ArkUI_Float32 stVal, int32_t stUnit, ArkUI_Float32 endVal,
    int32_t endUnit, void* startMarginRawPtr, void* endMarginRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::ResetResObj(frameNode, "columnSplit.divider");
    Dimension startMarginDimension(stVal, static_cast<DimensionUnit>(stUnit));
    Dimension endMarginDimension(endVal, static_cast<DimensionUnit>(endUnit));
    ColumnSplitDivider divider = { startMarginDimension, endMarginDimension };
    if (SystemProperties::ConfigChangePerform() && startMarginRawPtr) {
        auto* start = reinterpret_cast<ResourceObject*>(startMarginRawPtr);
        auto startResObj = AceType::Claim(start);
        LinearSplitModelNG::RegisterResObj(startResObj, divider, "columnSplit.divider.startMargin");
    }
    if (SystemProperties::ConfigChangePerform() && endMarginRawPtr) {
        auto* end = reinterpret_cast<ResourceObject*>(endMarginRawPtr);
        auto endResObj = AceType::Claim(end);
        LinearSplitModelNG::RegisterResObj(endResObj, divider, "columnSplit.divider.endMargin");
    }
    LinearSplitModelNG::SetDivider(frameNode, SplitType::COLUMN_SPLIT, divider);
}

void ResetColumnSplitDivider(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::ResetResObj(frameNode, "columnSplit.divider");
    LinearSplitModelNG::SetDivider(frameNode, SplitType::COLUMN_SPLIT, { DEFAULT_DIVIDER_START, DEFAULT_DIVIDER_END });
}

void SetColumnSplitClip(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetClipEdge(frameNode, value);
}

void SetColumnSplitClipShape(ArkUINodeHandle node, void* value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto clipShape = AceType::Claim(reinterpret_cast<BasicShape*>(value));
    CHECK_NULL_VOID(clipShape);
    ViewAbstractModelNG::SetClipShape(frameNode, clipShape);
}

#ifndef CROSS_PLATFORM
void CreateColumnSplitImpl()
{
    GetLinearSplitModelImpl()->Create(SplitType::COLUMN_SPLIT);
}

void SetColumnSplitDividerImpl(ArkUINodeHandle node, ArkUI_Float32 stVal, int32_t stUnit, ArkUI_Float32 endVal,
    int32_t endUnit, void* startMarginRawPtr, void* endMarginRawPtr)
{
    GetLinearSplitModelImpl()->ResetResObj("columnSplit.divider");
    Dimension startMarginDimension(stVal, static_cast<DimensionUnit>(stUnit));
    Dimension endMarginDimension(endVal, static_cast<DimensionUnit>(endUnit));
    ColumnSplitDivider divider = { startMarginDimension, endMarginDimension };
    if (SystemProperties::ConfigChangePerform() && startMarginRawPtr) {
        auto* start = reinterpret_cast<ResourceObject*>(startMarginRawPtr);
        auto startResObj = AceType::Claim(start);
        LinearSplitModelNG::RegisterResObj(startResObj, divider, "columnSplit.divider.startMargin");
    }
    if (SystemProperties::ConfigChangePerform() && endMarginRawPtr) {
        auto* end = reinterpret_cast<ResourceObject*>(endMarginRawPtr);
        auto endResObj = AceType::Claim(end);
        LinearSplitModelNG::RegisterResObj(endResObj, divider, "columnSplit.divider.endMargin");
    }
    GetLinearSplitModelImpl()->SetDivider(SplitType::COLUMN_SPLIT, divider);
}

void SetColumnSplitResizableImpl(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    GetLinearSplitModelImpl()->SetResizable(NG::SplitType::COLUMN_SPLIT, resizable);
}

void SetColumnSplitClipImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetViewAbstractModelImpl()->SetClipEdge(value);
}

void SetColumnSplitClipShapeImpl(ArkUINodeHandle node, void* value)
{
    auto clipShape = AceType::Claim(reinterpret_cast<BasicShape*>(value));
    CHECK_NULL_VOID(clipShape);
    GetViewAbstractModelImpl()->SetClipShape(clipShape);
}
#endif

namespace NodeModifier {
const ArkUIColumnSplitModifier* GetColumnSplitDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIColumnSplitModifier modifier = {
            .createColumnSplit = CreateColumnSplitImpl,
            .setColumnSplitDivider = SetColumnSplitDividerImpl,
            .resetColumnSplitDivider = nullptr,
            .setColumnSplitResizable = SetColumnSplitResizableImpl,
            .resetColumnSplitResizable = nullptr,
            .setColumnSplitClip = SetColumnSplitClipImpl,
            .setColumnSplitClipShape = SetColumnSplitClipShapeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIColumnSplitModifier modifier = {
        .createColumnSplit = CreateColumnSplit,
        .setColumnSplitDivider = SetColumnSplitDivider,
        .resetColumnSplitDivider = ResetColumnSplitDivider,
        .setColumnSplitResizable = SetColumnSplitResizable,
        .resetColumnSplitResizable = ResetColumnSplitResizable,
        .setColumnSplitClip = SetColumnSplitClip,
        .setColumnSplitClipShape = SetColumnSplitClipShape,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIColumnSplitModifier* GetCJUIColumnSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIColumnSplitModifier modifier = {
        .setColumnSplitDivider = SetColumnSplitDivider,
        .resetColumnSplitDivider = ResetColumnSplitDivider,
        .setColumnSplitResizable = SetColumnSplitResizable,
        .resetColumnSplitResizable = ResetColumnSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

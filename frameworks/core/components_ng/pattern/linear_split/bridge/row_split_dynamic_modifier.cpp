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
constexpr bool DEFAULT_ROW_SPLIT_RESIZABLE = false;
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
}
void CreateRowSplit()
{
    static LinearSplitModelNG model;
    model.Create(SplitType::ROW_SPLIT);
}

void SetRowSplitResizable(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::ROW_SPLIT, resizable);
}

void ResetRowSplitResizable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::ROW_SPLIT, DEFAULT_ROW_SPLIT_RESIZABLE);
}

void SetRowSplitClip(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModel::GetInstance()->SetClipEdge(value);
}

void SetRowSplitClipShape(ArkUINodeHandle node, void* value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto clipShape = AceType::Claim(reinterpret_cast<BasicShape*>(value));
    CHECK_NULL_VOID(clipShape);
    ViewAbstractModel::GetInstance()->SetClipShape(clipShape);
}

#ifndef CROSS_PLATFORM
void CreateRowSplitImpl()
{
    GetLinearSplitModelImpl()->Create(SplitType::ROW_SPLIT);
}

void SetRowSplitResizableImpl(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetLinearSplitModelImpl()->SetResizable(NG::SplitType::ROW_SPLIT, resizable);
}

void SetRowSplitClipImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetViewAbstractModelImpl()->SetClipEdge(value);
}

void SetRowSplitClipShapeImpl(ArkUINodeHandle node, void* value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto clipShape = AceType::Claim(reinterpret_cast<BasicShape*>(value));
    CHECK_NULL_VOID(clipShape);
    GetViewAbstractModelImpl()->SetClipShape(clipShape);
}
#endif

namespace NodeModifier {
const ArkUIRowSplitModifier* GetRowSplitDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIRowSplitModifier modifier = {
            .createRowSplit = CreateRowSplitImpl,
            .setRowSplitResizable = SetRowSplitResizableImpl,
            .resetRowSplitResizable = nullptr,
            .setRowSplitClip = SetRowSplitClipImpl,
            .setRowSplitClipShape = SetRowSplitClipShapeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRowSplitModifier modifier = {
        .createRowSplit = CreateRowSplit,
        .setRowSplitResizable = SetRowSplitResizable,
        .resetRowSplitResizable = ResetRowSplitResizable,
        .setRowSplitClip = SetRowSplitClip,
        .setRowSplitClipShape = SetRowSplitClipShape,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIRowSplitModifier* GetCJUIRowSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRowSplitModifier modifier = {
        .setRowSplitResizable = SetRowSplitResizable,
        .resetRowSplitResizable = ResetRowSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
}

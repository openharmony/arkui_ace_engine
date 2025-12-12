/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/arkoala_for_each_node.h"

#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {

ArkoalaForEachNode::ArkoalaForEachNode(int32_t nodeId, bool isRepeat) : ForEachBaseNode(
    isRepeat ? V2::JS_REPEAT_ETS_TAG : V2::JS_FOR_EACH_ETS_TAG, nodeId), isRepeat_(isRepeat) {}

void ArkoalaForEachNode::FinishRender()
{
    TAG_LOGD(AceLogTag::ACE_FOREACH, "nodeId:%{public}d FinishRender() ...", GetId());
    if (auto frameNode = GetParentFrameNode()) {
        frameNode->ChildrenUpdatedFrom(0);
    }
    FlushUpdateAndMarkDirty();
}

void ArkoalaForEachNode::FlushUpdateAndMarkDirty()
{
    // mark parent dirty to flush measure.
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void ArkoalaForEachNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        auto parentNode = GetParentFrameNode();
        if (parentNode) {
            InitAllChildrenDragManager(true);
        } else {
            auto piplineContext = GetContext();
            CHECK_NULL_VOID(piplineContext);
            auto taskExecutor = piplineContext->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak = WeakClaim(this)]() mutable {
                    auto forEach = weak.Upgrade();
                    CHECK_NULL_VOID(forEach);
                    forEach->InitAllChildrenDragManager(true);
                },
                TaskExecutor::TaskType::UI, "ArkUIInitAllChildrenDragManager");
        }
    } else if (!onMove && onMoveEvent_) {
        InitAllChildrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void ArkoalaForEachNode::SetItemDragEvent(std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    if (onMoveEvent_) {
        onLongPressEvent_ = onLongPress;
        onDragStartEvent_ = onDragStart;
        onMoveThroughEvent_ = onMoveThrough;
        onDropEvent_ = onDrop;
    }
}

RefPtr<FrameNode> ArkoalaForEachNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false));
}

void ArkoalaForEachNode::MoveData(int32_t from, int32_t to)
{
    if (from == to || from < 0 || to < 0) {
        return;
    }
    auto& children = ModifyChildren();
    auto fromIter = children.begin();
    std::advance(fromIter, from);
    auto child = *fromIter;
    TraversingCheck(child);
    children.erase(fromIter);
    auto toIter = children.begin();
    std::advance(toIter, to);
    children.insert(toIter, child);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void ArkoalaForEachNode::FireOnMove(int32_t from, int32_t to)
{
    ForEachBaseNode::FireOnMove(from, to);
}

void ArkoalaForEachNode::InitDragManager(const RefPtr<FrameNode>& child)
{
    CHECK_NULL_VOID(child);
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    auto pattern = child->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(AceType::Claim(this));
}

void ArkoalaForEachNode::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        onMoveEvent_ = nullptr;
        return;
    }
    const auto& children = GetChildren();
    for (const auto& child : children) {
        if (!child || (child->GetChildren().size() != 1)) {
            continue;
        }
        auto listItem = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        if (!listItem) {
            continue;
        }
        auto pattern = listItem->GetPattern<ListItemPattern>();
        if (!pattern) {
            continue;
        }
        if (init) {
            pattern->InitDragManager(AceType::Claim(this));
        } else {
            pattern->DeInitDragManager();
        }
    }
}

void ArkoalaForEachNode::DumpInfo()
{
    if (isRepeat_) {
        DumpLog::GetInstance().AddDesc("VirtualScroll: false");
    }
}
} // namespace OHOS::Ace::NG
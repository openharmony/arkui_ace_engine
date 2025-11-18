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

#include "test/unittest/core/syntax/syntax_test_ng.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"

#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/image/image_model_ng.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> SyntaxTestNg::GetMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> SyntaxTestNg::CreateTextNode(std::string content)
{
    TextModelNG textModelNG;
    textModelNG.Create(content);
    auto frameNode = GetMainFrameNode();
    return frameNode;
}

RefPtr<FrameNode> SyntaxTestNg::CreateImageNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    stack->Push(frameNode);
    return AceType::DynamicCast<FrameNode>(element);
}

ListModelNG SyntaxTestNg::CreateList()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create();
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    listNode_ = AceType::DynamicCast<FrameNode>(element);
    return model;
}

GridModelNG SyntaxTestNg::CreateGrid()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    gridNode_ = AceType::DynamicCast<FrameNode>(element);
    return model;
}

SwiperModelNG SyntaxTestNg::CreateSwiper()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    SwiperModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    swiperNode_ = AceType::DynamicCast<FrameNode>(element);
    return model;
}

WaterFlowModelNG SyntaxTestNg::CreateWaterFlow(WaterFlowLayoutMode mode)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    WaterFlowModelNG model;
    model.Create();
    model.SetLayoutMode(mode);
    waterFlowNode_ = GetMainFrameNode();
    return model;
}

RefPtr<FrameNode> SyntaxTestNg::CreateScroller(const Scroller& parentTag)
{
    RefPtr<FrameNode> scrollerNode;
    switch (parentTag) {
        case Scroller::LIST:
            {
                ListModelNG listModel;
                listModel.Create();
                scrollerNode = listNode_;
                break;
            }
        case Scroller::GRID:
            {
                GridModelNG gridModel;
                gridModel.Create();
                scrollerNode = gridNode_;
                break;
            }
        case Scroller::SWIPER:
            {
                SwiperModelNG swiperModel;
                swiperModel.Create();
                scrollerNode = swiperNode_;
                break;
            }
        case Scroller::WATER_FLOW:
            {
                WaterFlowModelNG waterFlowModel;
                waterFlowModel.Create();
                scrollerNode = waterFlowNode_;
                break;
            }
        default:
            break;
    }
}

RefPtr<ForEachNode> CreateForEach()
{
    ForEachModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto node = AceType::DynamicCast<ForEachNode>(element);
    return node;
}

RefPtr<LazyForEachNode> CreateLazyForEach()
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. Add children items to lazyForEachNode.
     */
    UpdateItems(lazyForEachNode, mockLazyForEachActuator);
    return lazyForEachNode;
}

RefPtr<RepeatNode> SyntaxTestNg::CreateRepeat()
{
    RepeatModelNG model;
    model.StartRender();
    std::vector<int32_t> removedElmtId{};
    model.FinishRender(removedElmtId);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto node = AceType::DynamicCast<RepeatNode>(element);
    return node;
}

RefPtr<RepeatVirtualScrollNode> SyntaxTestNg::CreateRepeatVirtual()
{
    RepeatVirtualScrollModelNG model;
    std::function<void(const std::string&, uint32_t)> updateFunc = [](const std::string& value, uint32_t idx) {};
    std::function<std::list<std::string>(uint32_t, uint32_t)> getKeys = [](uint32_t start, uint32_t end) {
        std::list<std::string> keys;
        for (uint32_t i = start; i <= end; ++i) {
            keys.emplace_back(std::to_string(i));
        }
        return keys;
    };
    std::function<std::list<std::string>(uint32_t, uint32_t)> getTypes = [](uint32_t start, uint32_t end) {
        std::list<std::string> keys;
        for (uint32_t i = start; i <= end; ++i) {
            keys.emplace_back("0");
        }
        return keys;
    };
    std::function<void(uint32_t, uint32_t)> setActiveRange = [](uint32_t start, uint32_t end) {};
    model.Create(0, {}, createFunc, updateFunc, getKeys, getTypes, setActiveRange);
    auto repeatNode = GetMainFrameNode();
    return AceType::DynamicCast<RepeatVirtualScrollNode>(repeatNode);
}

RefPtr<RepeatVirtualScroll2Node> SyntaxTestNg::CreateRepeatVirtual2()
{
    RepeatVirtualScroll2ModelNG model;
    std::map<IndexType, RIDType> l1Rid4Index = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 6}
    };
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index =
        [&](IndexType index) -> std::pair<RIDType, uint32_t> {
            auto it = l1Rid4Index_.find(0);
            if (it != l1Rid4Index_.end()) {
                return {index, 2};
            }
            return {index, 1};
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](IndexType fromIndex, IndexType toIndex) -> void {
        return;
    };
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t fromIndex, int32_t toIndex, int32_t vStart, int32_t vEnd, bool isLoop, bool forceUpdate) -> void {
            return;
    };
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](IndexType, IndexType) -> void {
        return;
    };
    std::function<void()> onPurge = []() -> void {
        return;
    };
    std::function<void()> onUpdateDirty = []() -> void {
        return;
    };
    model.Create(0, 0, onGetRid4Index, onRecycleItems, onActiveRange,
        onMoveFromTo, onPurge, onUpdateDirty);
    auto repeatNode = GetMainFrameNode();
    return AceType::DynamicCast<RepeatVirtualScroll2Node>(repeatNode);
}

RefPtr<ForEachNode> SyntaxTestNg::CreateForEachWithChildren(TotalCount totalCount)
{
    auto node = CreateForEach();
    for (int32_t i = 0; i < static_cast<int32_t>(totalCount); ++i) {
        node->AddChild(CreateTextNode(TEXT_CONTEXT + std::to_string(i)));
    }
    return node;
}

RefPtr<LazyForEachNode> SyntaxTestNg::CreateLazyForEachWithChildren(TotalCount totalCount)
{
    auto node = CreateLazyForEach();
    for (int32_t i = 0; i < static_cast<int32_t>(totalCount); ++i) {
        node->AddChild(CreateTextNode(TEXT_CONTEXT + std::to_string(i)));
    }
    return node;
}

RefPtr<RepeatNode> SyntaxTestNg::CreateRepeatWithChildren(TotalCount totalCount)
{
    auto node = CreateRepeat();
    for (int32_t i = 0; i < static_cast<int32_t>(totalCount); ++i) {
        node->AddChild(CreateTextNode(TEXT_CONTEXT + std::to_string(i)));
    }
    return node;
}

RefPtr<RepeatVirtualScrollNode> SyntaxTestNg::CreateRepeatVirtualWithChildren(TotalCount totalCount)
{
    auto node = CreateRepeatVirtual();
    for (int32_t i = 0; i < static_cast<int32_t>(totalCount); ++i) {
        node->AddChild(CreateTextNode(TEXT_CONTEXT + std::to_string(i)));
    }
    return node;
}

RefPtr<RepeatVirtualScroll2Node> SyntaxTestNg::CreateRepeatVirtual2WithChildren(TotalCount totalCount)
{
    auto node = CreateRepeatVirtual2();
    for (int32_t i = 0; i < static_cast<int32_t>(totalCount); ++i) {
        node->AddChild(CreateTextNode(TEXT_CONTEXT + std::to_string(i)));
    }
    return node;
}

RefPtr<ForEachNode> SyntaxTestNg::CreateScrollerWithForEach(const Scroller& parentTag, TotalCount totalCount)
{
    auto scroller = CreateScroller(parentTag);
    scroller->AddChild(CreateForEachWithChildren(totalCount));
    return AceType::DynamicCast<ForEachNode>(scroller->GetChildren().front());
}

RefPtr<LazyForEachNode> SyntaxTestNg::CreateScrollerWithLazyForEach(
    const Scroller& parentTag, TotalCount totalCount)
{
    auto scroller = CreateScroller(parentTag);
    scroller->AddChild(CreateLazyForEachWithChildren(totalCount));
    return AceType::DynamicCast<LazyForEachNode>(scroller->GetChildren().front());
}

RefPtr<RepeatNode> SyntaxTestNg::CreateScrollerWithRepeat(
    const Scroller& parentTag, TotalCount totalCount)
{
    auto scroller = CreateScroller(parentTag);
    scroller->AddChild(CreateRepeatWithChildren(totalCount));
    return AceType::DynamicCast<RepeatNode>(scroller->GetChildren().front());
}

RefPtr<RepeatVirtualScrollNode> SyntaxTestNg::CreateScrollerWithRepeatVirtual(
    const Scroller& parentTag, TotalCount totalCount)
{
    auto scroller = CreateScroller(parentTag);
    scroller->AddChild(CreateRepeatVirtualWithChildren(totalCount));
    return AceType::DynamicCast<RepeatVirtualScrollNode>(scroller->GetChildren().front());
}

RefPtr<RepeatVirtualScroll2Node> SyntaxTestNg::CreateScrollerWithRepeatVirtual2(
    const Scroller& parentTag, TotalCount totalCount)
{
    auto scroller = CreateScroller(parentTag);
    scroller->AddChild(CreateRepeatVirtual2WithChildren(totalCount));
    return AceType::DynamicCast<RepeatVirtualScroll2Node>(scroller->GetChildren().front());
}
} // namespace OHOS::Ace::NG
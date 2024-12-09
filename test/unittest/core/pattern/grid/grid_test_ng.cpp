/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"

#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"

#ifndef TEST_IRREGULAR_GRID
#include "test/mock/base/mock_system_properties.h"
#endif
namespace OHOS::Ace::NG {
void GridTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_GRID);
    auto gridItemTheme = GridItemTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(GridItemTheme::TypeId())).WillRepeatedly(Return(gridItemTheme));
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    auto container = Container::GetContainer(CONTAINER_ID_DIVIDE_SIZE);
    EXPECT_CALL(*(AceType::DynamicCast<MockContainer>(container)), GetWindowId()).Times(AnyNumber());
    MockAnimationManager::Enable(true);
#ifndef TEST_IRREGULAR_GRID
    g_irregularGrid = false;
#endif
    testing::FLAGS_gmock_verbose = "error";
}

void GridTestNg::CheckPreloadListEqual(const std::list<int32_t>& expectedList) const
{
    ASSERT_EQ(expectedList.size(), pattern_->preloadItemList_.size());
    auto it = expectedList.begin();
    for (auto&& item : pattern_->preloadItemList_) {
        EXPECT_EQ(*it, item.idx);
        ++it;
    }
}

void GridTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GridTestNg::SetUp()
{
    MockAnimationManager::GetInstance().Reset();
}

void GridTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    positionController_ = nullptr;
    ClearOldNodes(); // Each testCase will create new list at begin
    MockAnimationManager::GetInstance().Reset();
    PipelineContext::GetCurrentContext()->SetMinPlatformVersion(0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(0);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

void GridTestNg::GetGrid()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GridPattern>();
    eventHub_ = frameNode_->GetEventHub<GridEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GridLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GridAccessibilityProperty>();
    positionController_ = pattern_->GetOrCreatePositionController();
}

GridModelNG GridTestNg::CreateGrid()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    GetGrid();
    return model;
}

GridItemModelNG GridTestNg::CreateGridItem(float width, float height, GridItemStyle gridItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridItemModelNG itemModel;
    itemModel.Create(gridItemStyle);
    if (width == FILL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    } else if (width != NULL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(width));
    }
    if (height == FILL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    } else if (height != NULL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(height));
    }
    ViewAbstract::SetFocusable(true);
    return itemModel;
}

void GridTestNg::CreateGridItems(int32_t itemNumber, float width, float height, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < itemNumber; i++) {
        CreateGridItem(width, height, gridItemStyle);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void GridTestNg::CreateFocusableGridItems(int32_t itemNumber, float width, float height, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < itemNumber; i++) {
        CreateGridItem(width, height, gridItemStyle);
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void GridTestNg::CreateFixedItems(int32_t itemNumber, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE, gridItemStyle);
}

void GridTestNg::CreateFixedHeightItems(int32_t itemNumber, float height, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, FILL_VALUE, height, gridItemStyle);
}

void GridTestNg::CreateFixedWidthItems(int32_t itemNumber, float width, GridItemStyle gridItemStyle)
{
    CreateGridItems(itemNumber, width, FILL_VALUE, gridItemStyle);
}

void GridTestNg::CreateBigItem(
    int32_t rowStart, int32_t rowEnd, int32_t colStart, int32_t colEnd, float width, float height)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    if (rowStart != NULL_VALUE) {
        itemModel.SetRowStart(rowStart);
    }
    if (rowEnd != NULL_VALUE) {
        itemModel.SetRowEnd(rowEnd);
    }
    if (colStart != NULL_VALUE) {
        itemModel.SetColumnStart(colStart);
    }
    if (colEnd != NULL_VALUE) {
        itemModel.SetColumnEnd(colEnd);
    }
    if (width != NULL_VALUE) {
        ViewAbstract::SetWidth(CalcLength(width));
    }
    if (height != NULL_VALUE) {
        ViewAbstract::SetHeight(CalcLength(height));
    }
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
}

void GridTestNg::CreateBigColItem(int32_t colStart, int32_t colEnd)
{
    CreateBigItem(NULL_VALUE, NULL_VALUE, colStart, colEnd, NULL_VALUE, ITEM_MAIN_SIZE);
}

void GridTestNg::CreateBigRowItem(int32_t rowStart, int32_t rowEnd)
{
    CreateBigItem(rowStart, rowEnd, NULL_VALUE, NULL_VALUE, 60.0f, NULL_VALUE);
}

void GridTestNg::AddFixedHeightItems(int32_t cnt, float height)
{
    for (int i = 0; i < cnt; ++i) {
        auto child = FrameNode::GetOrCreateFrameNode(
            V2::GRID_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<GridItemPattern>(nullptr); });
        child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(height))));
        frameNode_->AddChild(child);
    }
}

void GridTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushUITasks();
}

void GridTestNg::ScrollTo(float position)
{
    pattern_->ScrollTo(position);
    FlushUITasks();
}

void GridTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushUITasks();
}

GridModelNG GridTestNg::CreateRepeatGrid(int32_t itemNumber, std::function<float(uint32_t)>&& getSize)
{
    auto model = CreateGrid();

    RepeatVirtualScrollModelNG repeatModel;
    std::function<void(uint32_t)> createFunc = [this, getSize](uint32_t idx) {
        CreateFocusableGridItems(1, FILL_VALUE, getSize(idx), GridItemStyle::NONE);
        ViewStackProcessor::GetInstance()->Pop();
    };
    std::function<void(const std::string&, uint32_t)> updateFunc = [this, getSize](
                                                                       const std::string& value, uint32_t idx) {
        CreateFocusableGridItems(1, FILL_VALUE, getSize(idx), GridItemStyle::NONE);
        ViewStackProcessor::GetInstance()->Finish();
    };
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
    repeatModel.Create(itemNumber, {}, createFunc, updateFunc, getKeys, getTypes, setActiveRange);
    return model;
}

void GridTestNg::CreateAdaptChildSizeGridItems(int32_t itemNumber, GridItemStyle gridItemStyle)
{
    for (int32_t i = 0; i < itemNumber; i++) {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        GridItemModelNG itemModel;
        itemModel.Create(gridItemStyle);
        {
            auto columnFrameNode = FrameNode::CreateFrameNode(
                V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

class GridMockLazy : public Framework::MockLazyForEachBuilder {
public:
    GridMockLazy(int32_t itemCnt, std::function<float(int32_t)>&& getHeight) : itemCnt_(itemCnt), getHeight_(getHeight)
    {}

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        ViewAbstract::SetWidth(CalcLength(FILL_VALUE));
        ViewAbstract::SetHeight(CalcLength(getHeight_(index)));
        ViewAbstract::SetFocusable(true);
        auto node = ViewStackProcessor::GetInstance()->Finish();
        return { std::to_string(index), node };
    }

private:
    int32_t itemCnt_ = 0;
    const std::function<float(int32_t)> getHeight_;
};

void GridTestNg::CreateItemsInLazyForEach(int32_t itemNumber, std::function<float(uint32_t)>&& getHeight)
{
    RefPtr<LazyForEachActuator> mockLazy = AceType::MakeRefPtr<GridMockLazy>(itemNumber, std::move(getHeight));
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(mockLazy);
}

RefPtr<FrameNode> GridTestNg::GetItem(int32_t idx, bool asCache)
{
    return AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(idx, asCache));
}

void GridTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    positionController_->ScrollToIndex(index, smooth, align, extraOffset);
    FlushUITasks();
}

bool GridTestNg::AnimateTo(
    const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    bool result = positionController_->AnimateTo(position, duration, curve, smooth, canOverScroll);
    FlushUITasks();
    return result;
}

AssertionResult GridTestNg::Position(float expectOffset)
{
    if (!MockAnimationManager::GetInstance().AllFinished()) {
        MockAnimationManager::GetInstance().Tick();
        FlushUITasks();
    }
    return IsEqual(-(pattern_->GetTotalOffset()), expectOffset);
}

AssertionResult GridTestNg::VelocityPosition(float velocity, float expectOffset)
{
    MockAnimationManager::GetInstance().TickByVelocity(velocity);
    FlushUITasks();
    return IsEqual(-(pattern_->GetTotalOffset()), expectOffset);
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class SheetDragBarTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SheetDragBarTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetDragBarTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: InitTouchEvent001
 * @tc.desc: Increase the coverage of SheetDragBarPattern::InitTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto host = dragBarPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    dragBarPattern->InitTouchEvent(gestureHub);

    auto touchTask = [](TouchEventInfo& info) {};
    dragBarPattern->touchEvent_ = AccessibilityManager::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    dragBarPattern->InitTouchEvent(gestureHub);
}

/**
 * @tc.name: InitClickEvent001
 * @tc.desc: Increase the coverage of SheetDragBarPattern::InitClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitClickEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->clickListener_, nullptr);
    dragBarPattern->InitClickEvent();

    EXPECT_NE(dragBarPattern->clickListener_, nullptr);
    dragBarPattern->InitClickEvent();
}

/**
 * @tc.name: OnClick001
 * @tc.desc: Increase the coverage of SheetDragBarPattern::OnClick function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, OnClick001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->clickArrowCallback_, nullptr);
    dragBarPattern->OnClick();

    dragBarPattern->clickArrowCallback_ = []() {};
    EXPECT_NE(dragBarPattern->clickArrowCallback_, nullptr);
    dragBarPattern->OnClick();
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Increase the coverage of SheetDragBarPattern::HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, HandleTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::UNKNOWN;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::UNKNOWN);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::DOWN;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::DOWN);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::CANCEL;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::CANCEL);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::UP;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::UP);
    dragBarPattern->HandleTouchEvent(eventInfo);
}

/**
 * @tc.name: CreatePropertyCallback001
 * @tc.desc: Increase the coverage of SheetDragBarPattern::CreatePropertyCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, CreatePropertyCallback001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->property_, nullptr);
    dragBarPattern->CreatePropertyCallback();

    float scale = 1.0f;
    dragBarPattern->isDown_ = false;
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto property = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->property_);
    ASSERT_NE(property, nullptr);
    EXPECT_FALSE(NearZero(scale));
    EXPECT_NE(dragBarPattern->GetPaintProperty<SheetDragBarPaintProperty>(), nullptr);
    EXPECT_FALSE(dragBarPattern->isDown_);
    property->updateCallback_(scale);

    dragBarPattern->isDown_ = true;
    EXPECT_TRUE(dragBarPattern->isDown_);
    property->updateCallback_(scale);

    scale = 0.0f;
    EXPECT_TRUE(NearZero(scale));
    property->updateCallback_(scale);

    EXPECT_NE(dragBarPattern->property_, nullptr);
    dragBarPattern->CreatePropertyCallback();
}
} // namespace OHOS::Ace::NG
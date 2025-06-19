/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @tc.desc: Branch: if (touchEvent_) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->touchEvent_ = nullptr;

    auto hostNode = dragBarPattern->GetHost();
    ASSERT_NE(hostNode, nullptr);
    auto eventHub = hostNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    dragBarPattern->InitTouchEvent(gestureEventHub);
    EXPECT_NE(dragBarPattern->touchEvent_, nullptr);
}

/**
 * @tc.name: InitTouchEvent002
 * @tc.desc: Branch: if (touchEvent_) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitTouchEvent002, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto touchTask = [](TouchEventInfo& info) {};
    auto touchEvent = AccessibilityManager::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    dragBarPattern->touchEvent_ = touchEvent;

    auto hostNode = dragBarPattern->GetHost();
    ASSERT_NE(hostNode, nullptr);
    auto eventHub = hostNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    dragBarPattern->InitTouchEvent(gestureEventHub);
    EXPECT_EQ(dragBarPattern->touchEvent_, touchEvent);
}

/**
 * @tc.name: InitClickEvent001
 * @tc.desc: Branch: if (clickListener_) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitClickEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->clickListener_ = nullptr;

    dragBarPattern->InitClickEvent();
    EXPECT_NE(dragBarPattern->clickListener_, nullptr);
}

/**
 * @tc.name: InitClickEvent002
 * @tc.desc: Branch: if (clickListener_) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, InitClickEvent002, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto clickCallback = [](GestureEvent& info) { };
    auto clickListener = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    dragBarPattern->clickListener_ = clickListener;

    dragBarPattern->InitClickEvent();
    EXPECT_EQ(dragBarPattern->clickListener_, clickListener);
}

/**
 * @tc.name: OnClick001
 * @tc.desc: Branch: if (clickArrowCallback_) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, OnClick001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->clickArrowCallback_ = nullptr;

    dragBarPattern->OnClick();
    EXPECT_EQ(dragBarPattern->clickArrowCallback_, nullptr);
}

/**
 * @tc.name: OnClick002
 * @tc.desc: Branch: if (clickArrowCallback_) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, OnClick002, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    int32_t clickTimes = 0;
    dragBarPattern->clickArrowCallback_ = [&clickTimes]() {
        clickTimes++;
    };

    dragBarPattern->OnClick();
    EXPECT_EQ(clickTimes, 1);
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = false
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, HandleTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->downPoint_ = OffsetF(-1, -1);
    dragBarPattern->isDown_ = true;

    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::UNKNOWN;
    locationInfo.SetGlobalLocation(Offset(10, 10));
    eventInfo.touches_.emplace_front(locationInfo);
    dragBarPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarPattern->downPoint_, OffsetF(-1, -1));
    EXPECT_TRUE(dragBarPattern->isDown_);
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = true
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = false
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, HandleTouchEvent002, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->downPoint_ = OffsetF(-1, -1);
    dragBarPattern->isDown_ = true;

    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::DOWN;
    locationInfo.SetGlobalLocation(Offset(10, 10));
    eventInfo.touches_.emplace_front(locationInfo);
    dragBarPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarPattern->downPoint_, OffsetF(10, 10));
    EXPECT_TRUE(dragBarPattern->isDown_);
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = true
 *           Condition: touchType == TouchType::UP = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, HandleTouchEvent003, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->downPoint_ = OffsetF(-1, -1);
    dragBarPattern->isDown_ = true;

    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::UP;
    locationInfo.SetGlobalLocation(Offset(10, 10));
    eventInfo.touches_.emplace_front(locationInfo);
    dragBarPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarPattern->downPoint_, OffsetF(-1, -1));
    EXPECT_FALSE(dragBarPattern->isDown_);
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = true
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, HandleTouchEvent004, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->downPoint_ = OffsetF(-1, -1);
    dragBarPattern->isDown_ = true;

    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::CANCEL;
    locationInfo.SetGlobalLocation(Offset(10, 10));
    eventInfo.touches_.emplace_front(locationInfo);
    dragBarPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarPattern->downPoint_, OffsetF(-1, -1));
    EXPECT_FALSE(dragBarPattern->isDown_);
}

/**
 * @tc.name: CreatePropertyCallback001
 * @tc.desc: Branch: if (property_) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, CreatePropertyCallback001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    int32_t scale = 0;
    auto propertyCallback = [&scale](float value) {
        scale = value;
    };
    dragBarPattern->property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, propertyCallback);

    dragBarPattern->CreatePropertyCallback();
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto normalProperty = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->GetProperty());
    ASSERT_NE(normalProperty, nullptr);
    normalProperty->updateCallback_(1.0f);
    EXPECT_EQ(scale, 1.0f);
}

/**
 * @tc.name: CreatePropertyCallback002
 * @tc.desc: Branch: if (property_) = false
 *           Branch: if (NearZero(scale)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, CreatePropertyCallback002, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->property_ = nullptr;
    auto paintProperty = dragBarPattern->GetPaintProperty<SheetDragBarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBarWidth(300.0_vp);

    dragBarPattern->CreatePropertyCallback();
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto normalProperty = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->GetProperty());
    ASSERT_NE(normalProperty, nullptr);
    normalProperty->updateCallback_(0.0f);
    EXPECT_EQ(paintProperty->GetBarWidth(), 300.0_vp);
}

/**
 * @tc.name: CreatePropertyCallback003
 * @tc.desc: Branch: if (property_) = false
 *           Branch: if (NearZero(scale)) = false
 *           Branch: if (ref->isDown_) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, CreatePropertyCallback003, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->property_ = nullptr;
    dragBarPattern->isDown_ = true;
    auto paintProperty = dragBarPattern->GetPaintProperty<SheetDragBarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBarWidth(300.0_vp);

    dragBarPattern->CreatePropertyCallback();
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto normalProperty = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->GetProperty());
    ASSERT_NE(normalProperty, nullptr);
    normalProperty->updateCallback_(1.0f);
    EXPECT_EQ(paintProperty->GetBarWidth(), 6.0_vp);
}

/**
 * @tc.name: CreatePropertyCallback004
 * @tc.desc: Branch: if (property_) = false
 *           Branch: if (NearZero(scale)) = false
 *           Branch: if (ref->isDown_) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetDragBarTestNg, CreatePropertyCallback004, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->property_ = nullptr;
    dragBarPattern->isDown_ = false;
    auto paintProperty = dragBarPattern->GetPaintProperty<SheetDragBarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBarWidth(300.0_vp);

    dragBarPattern->CreatePropertyCallback();
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto normalProperty = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->GetProperty());
    ASSERT_NE(normalProperty, nullptr);
    normalProperty->updateCallback_(1.0f);
    EXPECT_EQ(paintProperty->GetBarWidth(), 4.0_vp);
}
} // namespace OHOS::Ace::NG
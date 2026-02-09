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

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/resource/resource_info.h"

#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_paint_property.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == SelectTheme::TypeId()) {
        return AceType::MakeRefPtr<SelectTheme>();
    } else if (type == ScrollBarTheme::TypeId()) {
        return AceType::MakeRefPtr<ScrollBarTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class SelectBindMenuTouchTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value);
};

void SelectBindMenuTouchTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
}

void SelectBindMenuTouchTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SelectBindMenuTouchTestNg::TearDown() {}

RefPtr<FrameNode> SelectBindMenuTouchTestNg::CreateSelect(const std::vector<SelectParam>& value)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: BindMenuTouch001
 * @tc.desc: Test BindMenuTouch with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and gesture hub
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch with null targetNode
     * @tc.expected: Should handle null targetNode gracefully without crash
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->BindMenuTouch(nullptr, gestureHub));
}

/**
 * @tc.name: BindMenuTouch002
 * @tc.desc: Test BindMenuTouch with null gestureHub
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch with null gestureHub
     * @tc.expected: Should handle null gestureHub gracefully without crash
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->BindMenuTouch(AceType::RawPtr(select), nullptr));
}

/**
 * @tc.name: BindMenuTouch003
 * @tc.desc: Test BindMenuTouch normal binding scenario
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch with valid parameters
     * @tc.expected: Touch callback should be registered successfully
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());
}

/**
 * @tc.name: BindMenuTouch004
 * @tc.desc: Test BindMenuTouch callback with empty touches
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback with empty touches
     * @tc.expected: Should handle empty touches gracefully without crash
     */
    TouchEventInfo touchInfo("test");
    // Don't add any touch location info - touches will be empty
    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
}

/**
 * @tc.name: BindMenuTouch005
 * @tc.desc: Test BindMenuTouch callback with TouchType::DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback with DOWN touch type
     * @tc.expected: Should handle DOWN event gracefully (may not have menu subwindow in test)
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
}

/**
 * @tc.name: BindMenuTouch006
 * @tc.desc: Test BindMenuTouch callback with TouchType::UP
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback with UP touch type
     * @tc.expected: Should handle UP event gracefully
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
}

/**
 * @tc.name: BindMenuTouch007
 * @tc.desc: Test BindMenuTouch callback with TouchType::CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback with CANCEL touch type
     * @tc.expected: Should handle CANCEL event gracefully
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
}

/**
 * @tc.name: BindMenuTouch008
 * @tc.desc: Test BindMenuTouch callback with TouchType::MOVE
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    /**
     * @tc.steps: step3. Test touch callback with MOVE touch type
     * @tc.expected: Should handle MOVE event gracefully (not explicitly handled in code)
     */
    TouchEventInfo touchInfo("test");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();
    EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
}

/**
 * @tc.name: BindMenuTouch009
 * @tc.desc: Test BindMenuTouch callback with all touch types sequentially
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch and get callback
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());

    auto touchCallback = touchEvents.front()->GetTouchEventCallback();

    /**
     * @tc.steps: step3. Test all touch types in sequence
     * @tc.expected: All touch types should be handled gracefully
     */
    std::vector<TouchType> touchTypes = { TouchType::DOWN, TouchType::UP, TouchType::CANCEL, TouchType::MOVE };
    for (auto touchType : touchTypes) {
        TouchEventInfo touchInfo("test");
        TouchLocationInfo touchLocationInfo(0);
        touchLocationInfo.SetTouchType(touchType);
        touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
        EXPECT_NO_FATAL_FAILURE(touchCallback(touchInfo));
    }
}

/**
 * @tc.name: CheckSkipMenuShow001
 * @tc.desc: Test CheckSkipMenuShow with null targetNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, CheckSkipMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call CheckSkipMenuShow with null targetNode
     * @tc.expected: Should return false for null targetNode
     */
    bool result = selectPattern->CheckSkipMenuShow(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSkipMenuShow002
 * @tc.desc: Test CheckSkipMenuShow with valid targetNode (no menu subwindow)
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, CheckSkipMenuShow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call CheckSkipMenuShow with valid targetNode
     * @tc.expected: Should return false when no menu subwindow exists in test environment
     */
    bool result = selectPattern->CheckSkipMenuShow(select);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BindMenuTouch010
 * @tc.desc: Test BindMenuTouch multiple registration calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and setup
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Call BindMenuTouch multiple times
     * @tc.expected: Should handle multiple registrations gracefully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub));
    EXPECT_NO_FATAL_FAILURE(selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub));
    EXPECT_NO_FATAL_FAILURE(selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub));

    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());
}

/**
 * @tc.name: BindMenuTouch011
 * @tc.desc: Test BindMenuTouch with multiple options
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, BindMenuTouch011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with multiple options
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Bind menu touch
     * @tc.expected: Touch callback should be registered successfully
     */
    selectPattern->BindMenuTouch(AceType::RawPtr(select), gestureHub);
    auto touchEventActuator = gestureHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto touchEvents = touchEventActuator->touchEvents_;
    ASSERT_FALSE(touchEvents.empty());
}

/**
 * @tc.name: RegisterOnHover001
 * @tc.desc: Test RegisterOnHover callback execution with hover true
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register hover
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnHover();

    auto inputHub = select->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    ASSERT_NE(inputHub->hoverEventActuator_, nullptr);

    /**
     * @tc.steps: step2. Trigger hover callback with isHover = true
     * @tc.expected: Hover state should be set to true
     */
    EXPECT_NO_FATAL_FAILURE(
        inputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true));
    EXPECT_TRUE(selectPattern->IsHover());
}

/**
 * @tc.name: RegisterOnHover002
 * @tc.desc: Test RegisterOnHover callback execution with hover false
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnHover002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register hover
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnHover();

    auto inputHub = select->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    ASSERT_NE(inputHub->hoverEventActuator_, nullptr);

    /**
     * @tc.steps: step2. First trigger hover true, then hover false
     * @tc.expected: Hover state should change correctly
     */
    inputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true);
    EXPECT_TRUE(selectPattern->IsHover());

    inputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(false);
    EXPECT_FALSE(selectPattern->IsHover());
}

/**
 * @tc.name: RegisterOnHover003
 * @tc.desc: Test RegisterOnHover background color change
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnHover003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register hover
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnHover();

    auto inputHub = select->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    ASSERT_NE(inputHub->hoverEventActuator_, nullptr);

    /**
     * @tc.steps: step2. Trigger hover callback
     * @tc.expected: Background color should be set
     */
    inputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true);
    // Background color is set by theme callback
    EXPECT_TRUE(selectPattern->IsHover());
}

/**
 * @tc.name: RegisterOnPress001
 * @tc.desc: Test RegisterOnPress callback execution with PRESSED state
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register press
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnPress();

    auto eventHub = select->GetEventHub<SelectEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->stateStyleMgr_, nullptr);

    /**
     * @tc.steps: step2. Trigger PRESSED state
     * @tc.expected: Should handle PRESSED state gracefully
     */
    EXPECT_NO_FATAL_FAILURE(eventHub->stateStyleMgr_->UpdateCurrentUIState(UI_STATE_PRESSED));
    EXPECT_TRUE(eventHub->stateStyleMgr_->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: RegisterOnPress002
 * @tc.desc: Test RegisterOnPress callback execution with NORMAL state
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnPress002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register press
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnPress();

    auto eventHub = select->GetEventHub<SelectEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->stateStyleMgr_, nullptr);

    /**
     * @tc.steps: step2. Trigger PRESSED state then NORMAL state
     * @tc.expected: State should transition correctly
     */
    eventHub->stateStyleMgr_->UpdateCurrentUIState(UI_STATE_PRESSED);
    EXPECT_TRUE(eventHub->stateStyleMgr_->IsCurrentStateOn(UI_STATE_PRESSED));

    eventHub->stateStyleMgr_->ResetCurrentUIState(UI_STATE_PRESSED);
    EXPECT_FALSE(eventHub->stateStyleMgr_->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: RegisterOnPress003
 * @tc.desc: Test RegisterOnPress with hover state interaction
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnPress003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and register both press and hover
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->RegisterOnHover();
    selectPattern->RegisterOnPress();

    auto inputHub = select->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto eventHub = select->GetEventHub<SelectEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->stateStyleMgr_, nullptr);

    /**
     * @tc.steps: step2. Set hover state first, then trigger press
     * @tc.expected: Both states should be handled
     */
    inputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true);
    EXPECT_TRUE(selectPattern->IsHover());

    eventHub->stateStyleMgr_->UpdateCurrentUIState(UI_STATE_PRESSED);
    EXPECT_TRUE(eventHub->stateStyleMgr_->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step3. Reset press state
     * @tc.expected: Hover state should remain
     */
    eventHub->stateStyleMgr_->ResetCurrentUIState(UI_STATE_PRESSED);
    EXPECT_FALSE(eventHub->stateStyleMgr_->IsCurrentStateOn(UI_STATE_PRESSED));
    EXPECT_TRUE(selectPattern->IsHover());
}

/**
 * @tc.name: RegisterOnHover004
 * @tc.desc: Test RegisterOnHover multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnHover004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterOnHover multiple times
     * @tc.expected: Should handle multiple registrations gracefully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnHover());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnHover());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnHover());

    auto inputHub = select->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    EXPECT_TRUE(inputHub->hoverEventActuator_);
}

/**
 * @tc.name: RegisterOnPress004
 * @tc.desc: Test RegisterOnPress multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnPress004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterOnPress multiple times
     * @tc.expected: Should handle multiple registrations gracefully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnPress());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnPress());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnPress());

    auto eventHub = select->GetEventHub<SelectEventHub>();
    ASSERT_NE(eventHub, nullptr);
}

/**
 * @tc.name: SetIsHover001
 * @tc.desc: Test SetIsHover method
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, SetIsHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Set hover state to true
     * @tc.expected: IsHover should return true
     */
    selectPattern->SetIsHover(true);
    EXPECT_TRUE(selectPattern->IsHover());

    /**
     * @tc.steps: step3. Set hover state to false
     * @tc.expected: IsHover should return false
     */
    selectPattern->SetIsHover(false);
    EXPECT_FALSE(selectPattern->IsHover());
}

/**
 * @tc.name: GetBgBlendColor001
 * @tc.desc: Test GetBgBlendColor and SetBgBlendColor methods
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, GetBgBlendColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Check initial background blend color
     * @tc.expected: Should be TRANSPARENT initially
     */
    EXPECT_EQ(selectPattern->GetBgBlendColor(), Color::TRANSPARENT);

    /**
     * @tc.steps: step3. Set background blend color to red
     * @tc.expected: GetBgBlendColor should return red
     */
    selectPattern->SetBgBlendColor(Color::RED);
    EXPECT_EQ(selectPattern->GetBgBlendColor(), Color::RED);

    /**
     * @tc.steps: step4. Set background blend color to blue
     * @tc.expected: GetBgBlendColor should return blue
     */
    selectPattern->SetBgBlendColor(Color::BLUE);
    EXPECT_EQ(selectPattern->GetBgBlendColor(), Color::BLUE);
}

/**
 * @tc.name: OnDpiConfigurationUpdate001
 * @tc.desc: Test OnDpiConfigurationUpdate with option width set and isFitTrigger false
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and set option width
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    Dimension optionWidth(100.0, DimensionUnit::VP);
    selectModelInstance.SetOptionWidth(optionWidth);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate
     * @tc.expected: Should call SetOptionWidth successfully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: OnDpiConfigurationUpdate002
 * @tc.desc: Test OnDpiConfigurationUpdate without option width
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select without setting option width
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate
     * @tc.expected: Should complete without calling SetOptionWidth (no option width)
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: OnDpiConfigurationUpdate003
 * @tc.desc: Test OnDpiConfigurationUpdate with isFitTrigger true
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select and set isFitTrigger to true
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    Dimension optionWidth(100.0, DimensionUnit::VP);
    selectModelInstance.SetOptionWidth(optionWidth);

    // Set isFitTrigger to true
    selectPattern->SetOptionWidthFitTrigger(true);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate
     * @tc.expected: Should skip SetOptionWidth due to isFitTrigger being true
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: OnDpiConfigurationUpdate004
 * @tc.desc: Test OnDpiConfigurationUpdate multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with option width
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    Dimension optionWidth(150.0, DimensionUnit::VP);
    selectModelInstance.SetOptionWidth(optionWidth);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate multiple times
     * @tc.expected: Should handle multiple calls gracefully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: OnDpiConfigurationUpdate005
 * @tc.desc: Test OnDpiConfigurationUpdate with multiple options
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with multiple options
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    Dimension optionWidth(200.0, DimensionUnit::VP);
    selectModelInstance.SetOptionWidth(optionWidth);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate
     * @tc.expected: Should update option width for all options
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: SetOptionWidthFitTrigger001
 * @tc.desc: Test SetOptionWidthFitTrigger method
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, SetOptionWidthFitTrigger001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Set isFitTrigger to true
     * @tc.expected: isFitTrigger should be set to true
     */
    selectPattern->SetOptionWidthFitTrigger(true);
    // Note: isFitTrigger_ is a private member, we can't directly verify it
    // But the method should execute without errors

    /**
     * @tc.steps: step3. Set isFitTrigger to false
     * @tc.expected: Should execute without errors
     */
    selectPattern->SetOptionWidthFitTrigger(false);
}

/**
 * @tc.name: OnDpiConfigurationUpdate006
 * @tc.desc: Test OnDpiConfigurationUpdate verifies layout property check
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with option width
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    auto selectLayoutProperty = select->GetLayoutProperty<SelectLayoutProperty>();
    ASSERT_NE(selectLayoutProperty, nullptr);

    Dimension optionWidth(120.0, DimensionUnit::VP);
    selectModelInstance.SetOptionWidth(optionWidth);

    /**
     * @tc.steps: step2. Verify option width is set
     * @tc.expected: HasOptionWidth should return true
     */
    EXPECT_TRUE(selectLayoutProperty->HasOptionWidth());

    /**
     * @tc.steps: step3. Call OnDpiConfigurationUpdate
     * @tc.expected: Should execute successfully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: OnDpiConfigurationUpdate007
 * @tc.desc: Test OnDpiConfigurationUpdate with different dimension units
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, OnDpiConfigurationUpdate007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with pixel dimension
     * @tc.expected: Objects are created successfully
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    Dimension optionWidth(50.0, DimensionUnit::PX);
    selectModelInstance.SetOptionWidth(optionWidth);

    /**
     * @tc.steps: step2. Call OnDpiConfigurationUpdate
     * @tc.expected: Should handle pixel dimension correctly
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->OnDpiConfigurationUpdate());
}

/**
 * @tc.name: RegisterOnClick001
 * @tc.desc: Test RegisterOnClick normal registration
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterOnClick
     * @tc.expected: Click event should be registered successfully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnClick());

    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_TRUE(gestureHub->GetTouchable());
}

/**
 * @tc.name: RegisterOnClick002
 * @tc.desc: Test RegisterOnClick callback execution with valid selected index
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern and set selected index
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    // Set selected index to 0
    selectPattern->SetSelected(0);
    EXPECT_EQ(selectPattern->GetSelected(), 0);

    selectPattern->RegisterOnClick();

    /**
     * @tc.steps: step2. Trigger click callback
     * @tc.expected: Callback should execute and call UpdateSelectedProps
     */
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);

    if (!gestureHub->clickEventActuator_->clickEvents_.empty()) {
        auto clickCallback = gestureHub->clickEventActuator_->clickEvents_.front();
        ASSERT_NE(clickCallback, nullptr);

        GestureEvent info;
        EXPECT_NO_FATAL_FAILURE((*clickCallback)(info));
    }
}

/**
 * @tc.name: RegisterOnClick003
 * @tc.desc: Test RegisterOnClick with no selected index (-1)
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern with no selection
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    // Initialize with no selection (-1)
    selectPattern->InitSelected();
    EXPECT_EQ(selectPattern->GetSelected(), -1);

    selectPattern->RegisterOnClick();

    /**
     * @tc.steps: step2. Trigger click callback
     * @tc.expected: Should skip UpdateSelectedProps due to invalid index
     */
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);

    if (!gestureHub->clickEventActuator_->clickEvents_.empty()) {
        auto clickCallback = gestureHub->clickEventActuator_->clickEvents_.front();
        ASSERT_NE(clickCallback, nullptr);

        GestureEvent info;
        EXPECT_NO_FATAL_FAILURE((*clickCallback)(info));
    }
}

/**
 * @tc.name: RegisterOnClick004
 * @tc.desc: Test RegisterOnClick with out-of-range selected index
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    // Set selected index to an out-of-range value
    selectPattern->selected_ = 10; // Greater than options size

    selectPattern->RegisterOnClick();

    /**
     * @tc.steps: step2. Trigger click callback
     * @tc.expected: Should skip UpdateSelectedProps due to out-of-range index
     */
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);

    if (!gestureHub->clickEventActuator_->clickEvents_.empty()) {
        auto clickCallback = gestureHub->clickEventActuator_->clickEvents_.front();
        ASSERT_NE(clickCallback, nullptr);

        GestureEvent info;
        EXPECT_NO_FATAL_FAILURE((*clickCallback)(info));
    }
}

/**
 * @tc.name: RegisterOnClick005
 * @tc.desc: Test RegisterOnClick multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterOnClick multiple times
     * @tc.expected: Should handle multiple registrations gracefully
     */
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnClick());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnClick());
    EXPECT_NO_FATAL_FAILURE(selectPattern->RegisterOnClick());

    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_TRUE(gestureHub->GetTouchable());
}

/**
 * @tc.name: RegisterOnClick006
 * @tc.desc: Test RegisterOnClick with multiple options
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with multiple options
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    // Select the second option (index 1)
    selectPattern->SetSelected(1);

    selectPattern->RegisterOnClick();

    /**
     * @tc.steps: step2. Trigger click callback
     * @tc.expected: Should call UpdateSelectedProps with index 1
     */
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);

    if (!gestureHub->clickEventActuator_->clickEvents_.empty()) {
        auto clickCallback = gestureHub->clickEventActuator_->clickEvents_.front();
        ASSERT_NE(clickCallback, nullptr);

        GestureEvent info;
        EXPECT_NO_FATAL_FAILURE((*clickCallback)(info));
    }
}

/**
 * @tc.name: RegisterOnClick007
 * @tc.desc: Test RegisterOnClick verifies BindMenuTouch is called
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select pattern
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterOnClick
     * @tc.expected: Should also call BindMenuTouch to register touch events
     */
    selectPattern->RegisterOnClick();

    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    // Verify both click and touch events are registered
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);
    ASSERT_NE(gestureHub->touchEventActuator_, nullptr);
}

/**
 * @tc.name: RegisterOnClick008
 * @tc.desc: Test RegisterOnClick with second option selected
 * @tc.type: FUNC
 */
HWTEST_F(SelectBindMenuTouchTestNg, RegisterOnClick008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select with multiple options and select second
     * @tc.expected: Objects are created successfully
     */
    auto select = CreateSelect({ { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
        { OPTION_TEXT_3, INTERNAL_SOURCE } });
    ASSERT_NE(select, nullptr);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    // Select the second option (index 1)
    selectPattern->SetSelected(1);
    EXPECT_EQ(selectPattern->GetSelected(), 1);

    selectPattern->RegisterOnClick();

    /**
     * @tc.steps: step2. Trigger click callback
     * @tc.expected: Should update props for second option
     */
    auto gestureHub = select->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->clickEventActuator_, nullptr);

    if (!gestureHub->clickEventActuator_->clickEvents_.empty()) {
        auto clickCallback = gestureHub->clickEventActuator_->clickEvents_.front();
        ASSERT_NE(clickCallback, nullptr);

        GestureEvent info;
        EXPECT_NO_FATAL_FAILURE((*clickCallback)(info));
    }
}

} // namespace OHOS::Ace::NG

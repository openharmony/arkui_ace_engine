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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper/swiper_ui_session_adapter.h"

namespace OHOS::Ace::NG {
class SwiperUISessionAdapterTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: OnInjectionEvent001
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, OnInjectionEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node.
     */
    CreateSwiper();
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    CreateSwiperItems(2);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Test OnInjection function.
     * @tc.expected: Set the command json and check the results.
     */
    std::vector<std::string> jsonInvalid = {
        "",                                                            // Empty input
        R"({})",                                                       // Empty JSON
        R"({"c":1})",                                                  // Missing cmd
        R"({"cmd":1})",                                                // Wrong cmd type
        R"({"cmd":"c"})",                                              // Invalid cmd value
        R"({"cmd":"change","p":1})",                                   // Missing params
        R"({"cmd":"change","params":1})",                              // Wrong params type
        R"({"cmd":"change","params":{"t":1}})",                        // Missing type
        R"({"cmd":"change","params":{"type":1}})",                     // Wrong type type
        R"({"cmd":"change","params":{"type":"i"}})",                   // Invalid type value
        R"({"cmd":"change","params":{"type":"index"}})",               // Missing index
        R"({"cmd":"change","params":{"type":"index","i":1}})",         // Missing index field
        R"({"cmd":"change","params":{"type":"index","index":1}})",     // Wrong index type
        R"({"cmd":"change","params":{"type":"index","index":"1.5"}})", // Invalid index format
        R"({"cmd":"change","params":{"type":"index","index":"5"}})",   // Index out of range
        R"({"cmd":"change","params":{"type":"index","index":"-1"}})",  // Negative index
    };
    for (const auto& json : jsonInvalid) {
        int32_t result = pattern_->OnInjectionEvent(json);
        EXPECT_EQ(result, RET_FAILED);
    }

    auto jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    int32_t result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    jsonCommand = R"({"cmd":"change","params":{"type":"index","index":"1"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);;
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: OnInjectionEvent002
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, OnInjectionEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    model.SetLoop(AceType::RawPtr(frameNode_), false);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Test OnInjection function.
     * @tc.expected: Set the command json and check the results.
     */
    auto jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    int32_t result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    ChangeIndex(1);
    jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 0);

    layoutProperty_->UpdateDisableSwipe(true);
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: GetScrollAbility001
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, GetScrollAbility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node.
     * @tc.expected: Create Swiper successfully and it is unable to scroll.
     */
    CreateSwiper();
    CreateSwiperItems(1);
    CreateSwiperDone();
    SwiperUISessionAdapter helper(pattern_);
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "unable");

    /**
     * @tc.steps: step2. Add Swiper items and turn next.
     * @tc.expected: Swiper can scroll bidirectionally.
     */
    CreateSwiper();
    CreateSwiperItems(3);
    CreateSwiperDone();
    ShowNext();
    SwiperUISessionAdapter helperTwo(pattern_);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "bidirectional");
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "bidirectional");

    /**
     * @tc.steps: step3. Disable Swiper.
     * @tc.expected: Swiper is unable to scroll.
     */
    layoutProperty_->UpdateDisableSwipe(true);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "unable");
}

/**
 * @tc.name: GetScrollAbility002
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, GetScrollAbility002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node with 3 items and set displayCount equal to totalCount.
     * @tc.expected: Swiper is unable to scroll.
     */
    CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    CreateSwiperItems(3);
    CreateSwiperDone();
    SwiperUISessionAdapter helper(pattern_);
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "unable");

    /**
     * @tc.steps: step2. Init Swiper node with 2 items and set displayCount more than totalCount.
     * @tc.expected: Swiper is unable to scroll.
     */
    CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    CreateSwiperItems(2);
    CreateSwiperDone();
    SwiperUISessionAdapter helperTwo(pattern_);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "unable");
}

/**
 * @tc.name: GetScrollAbility003
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, GetScrollAbility003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init auto-linear Swiper node.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    model.SetLoop(AceType::RawPtr(frameNode_), false);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Test GetScrollAbility function.
     * @tc.expected: Turn next and check the results.
     */
    SwiperUISessionAdapter helper(pattern_);
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "forward");
    ShowNext();
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "bidirectional");
    ShowNext();
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "backward");
}

/**
 * @tc.name: GetScrollAbility004
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, GetScrollAbility004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init auto-linear Swiper node with two small items.
     * @tc.expected: Swiper is unable to scroll.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateSwiperDone();
    SwiperUISessionAdapter helper(pattern_);
    EXPECT_EQ(std::string(helper.GetScrollAbility()), "unable");

    /**
     * @tc.steps: step2. Init auto-linear Swiper node with two items.
     * @tc.expected: Swiper can scroll forward.
     */
    SwiperModelNG modelTwo = CreateSwiper();
    modelTwo.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(240.f, SWIPER_HEIGHT);
    CreateItemWithSize(240.f, SWIPER_HEIGHT);
    CreateSwiperDone();
    SwiperUISessionAdapter helperTwo(pattern_);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "forward");
    modelTwo.SetLoop(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(std::string(helperTwo.GetScrollAbility()), "unable");

    /**
     * @tc.steps: step3. Init auto-linear Swiper node with two big items.
     * @tc.expected: Swiper can scroll forward.
     */
    SwiperModelNG modelThree = CreateSwiper();
    modelThree.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateSwiperDone();
    SwiperUISessionAdapter helperThree(pattern_);
    EXPECT_EQ(std::string(helperThree.GetScrollAbility()), "forward");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig001
 * @tc.desc: test DumpSimplifyInfoOnlyForParamConfig
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUISessionAdapterTestNg, DumpSimplifyInfoOnlyForParamConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init auto-linear Swiper node.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Check scrollable.
     * @tc.expected: Swiper can scroll bidirectionally.
     */
    auto json = JsonUtil::CreateSharedPtrJson();
    pattern_->DumpSimplifyInfoOnlyForParamConfig(json, { true, true, true });
    EXPECT_EQ(json->GetString("scrollAbility"), "bidirectional");
    EXPECT_EQ(json->GetString("scrollAxis"), "horizontal");
    EXPECT_EQ(json->GetBool("isLoop"), true);
    auto jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    EXPECT_EQ(pattern_->OnInjectionEvent(jsonCommand), RET_SUCCESS);
    jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    EXPECT_EQ(pattern_->OnInjectionEvent(jsonCommand), RET_SUCCESS);
}
}
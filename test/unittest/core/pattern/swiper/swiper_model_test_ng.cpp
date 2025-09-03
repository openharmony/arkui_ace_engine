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

#include "swiper_test_ng.h"

#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_event_hub.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/common/resource/resource_parse_utils.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"

namespace OHOS::Ace::NG {

class SwiperModelTestNg : public SwiperTestNg {
public:
    void TearDown() override;

    void ShowNextPage();
    void ShowPreviousPage();
    void ChangeIndex(int32_t index, bool animation = false);
    void CreateWithItem(const std::function<void(SwiperModelNG)>& callback = nullptr,
        int32_t itemNumber = ITEM_NUMBER);

private:
    RefPtr<IndicatorController> indicatorController_;
};

void SwiperModelTestNg::TearDown()
{
    indicatorController_ = nullptr;
    SwiperTestNg::TearDown();
}

void SwiperModelTestNg::ShowNextPage()
{
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->ShowNext();
    FlushUITasks(frameNode_);
}

void SwiperModelTestNg::ShowPreviousPage()
{
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->ShowPrevious();
    FlushUITasks(frameNode_);
}

void SwiperModelTestNg::ChangeIndex(int32_t index, bool animation)
{
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->ChangeIndex(index, animation);
    FlushUITasks(frameNode_);
}

void SwiperModelTestNg::CreateWithItem(const std::function<void(SwiperModelNG)>& callback, int32_t itemNumber)
{
    SwiperModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    if (callback) {
        callback(model);
    }
    CreateSwiperItems(itemNumber);
    GetSwiper();
    int index = pattern_->RealTotalCount();
    if (pattern_->IsShowIndicator() && pattern_->HasIndicatorNode()) {
        indicatorNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasLeftButtonNode()) {
        leftArrowNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasRightButtonNode()) {
        rightArrowNode_ = GetChildFrameNode(frameNode_, index);
    }
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: SwiperModelTestNg001
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is BIND
     */
    SwiperParameters swiperParameters { Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f),
        Dimension(2.f), Dimension(2.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), true,
        Color::RED, Color::GREEN, 6 };
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange, &swiperParameters](SwiperModelNG model) {
        model.SetDotIndicatorStyle(swiperParameters);
        model.SetDirection(Axis::HORIZONTAL);
        model.SetShowIndicator(false);
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorPattern->InitIndicatorController();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    indicatorPattern->SetChangeIndexWithAnimation(false);
    FlushUITasks(indicatorNode_);
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 0
     */
    ChangeIndex(2);
    EXPECT_EQ(currentIndex, 2);
}

/**
 * @tc.name: SwiperModelTestNg002
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetBindIndicator(true);
        model.SetIndex(0);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorPattern->InitIndicatorController();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SwiperModelTestNg003
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg004
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);

    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 0
     */
    ChangeIndex(0);
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg005
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetBindIndicator(true);
        model.SetIndex(0);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorPattern->InitIndicatorController();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);

    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SwiperModelTestNg006
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);

    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg007
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and indicator type is DOT, indicator use mode is SINGLE, loop is true.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetBindIndicator(true);
        model.SetIndex(3);
        model.SetLoop(true);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_TRUE(indicatorPattern->IsLoop());

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 0
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg008
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and indicator type is DIGIT, indicator use mode is SINGLE, loop is true.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetBindIndicator(true);
        model.SetIndex(3);
        model.SetLoop(true);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_TRUE(indicatorPattern->IsLoop());

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 0
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg009
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, cout < index.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DOT);
        model.SetBindIndicator(true);
        model.SetIndex(5);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorPattern->InitIndicatorController();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_FALSE(indicatorPattern->IsLoop());

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SwiperModelTestNg010
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, cout < index.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetBindIndicator(true);
        model.SetIndex(5);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);

    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern->IsLoop());

    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg011
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, not set SwiperParameters.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG model) {
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 0
     */
    ChangeIndex(0);
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg012
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, not set SwiperDigitalParameters.
     */
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.fontColor = Color::RED;
    swiperDigitalParameters.selectedFontColor = Color::GREEN;
    swiperDigitalParameters.fontSize = Dimension(12.f);
    swiperDigitalParameters.selectedFontSize = Dimension(16.f);
    swiperDigitalParameters.fontWeight = FontWeight::W500;
    swiperDigitalParameters.selectedFontWeight = FontWeight::W900;
    swiperDigitalParameters.dimLeft = std::make_optional<Dimension>(10.f);
    swiperDigitalParameters.dimTop = std::make_optional<Dimension>(10.f);
    swiperDigitalParameters.dimRight = std::make_optional<Dimension>(10.f);
    swiperDigitalParameters.dimBottom = std::make_optional<Dimension>(10.f);
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange, &swiperDigitalParameters](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDigitIndicatorStyle(swiperDigitalParameters);
        model.SetShowIndicator(false);
        model.SetBindIndicator(true);
        model.SetIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    indicatorPattern->InitIndicatorController();
    indicatorController_ = indicatorPattern->GetIndicatorController();
    indicatorController_->SetSwiperNode(frameNode_);
    SwiperHelper::SaveDigitIndicatorProperty(indicatorNode_, *(AceType::RawPtr(pattern_)));

    EXPECT_EQ(layoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 2
     */
    ChangeIndex(2);
    EXPECT_EQ(currentIndex, 2);
}

/**
 * @tc.name: SwiperModelTestNg013
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.indicator type is DOT, indicator use mode is BIND, not set loop.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(3);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 0
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperModelTestNg014
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and indicator type is DOT, indicator use mode is BIND, swiper loop is true.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetLoop(true);
        swiperModel.SetIndex(0);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is true.
     * @tc.expected: loop is true,change page to 3.
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 3);
}

/**
 * @tc.name: SwiperModelTestNg015
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, swiper loop is false.
     * @tc.expected: loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetLoop(false);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is false.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. swiper loop is false.
     * @tc.expected: not change page.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
}

/**
 * @tc.name: SwiperModelTestNg016
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator loop is true.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(3);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetLoop(true);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is true.
     * @tc.expected: change page to 0.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg017
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator loop is false.
     * @tc.expected: loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetLoop(false);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is false.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. swiper loop is false.
     * @tc.expected: not change page.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg018
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator loop is false.
     * @tc.expected: loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(3);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetLoop(true);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is true.
     * @tc.expected: change page to 0.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step3. swiper loop is false.
     * @tc.expected: not change page.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateLoop(false);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
}

/**
 * @tc.name: SwiperModelTestNg019
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator loop is false.
     * @tc.expected: loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetLoop(true);
        swiperModel.SetIndex(3);
        swiperModel.SetOnChange(onChange);
    });
    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is true.
     * @tc.expected: change page to 0.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step3. swiper loop is false.
     * @tc.expected: not change page.
     */
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateLoop(false);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    FlushUITasks(frameNode_);
    FlushUITasks(indicatorNode_);
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg020
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator loop is false.
     * @tc.expected: loop is false.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetLoop(false);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetLoop(false);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is false.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. swiper loop is false.
     * @tc.expected: not change page.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateLoop(true);
    EXPECT_FALSE(indicatorPattern->IsLoop());
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
}

/**
 * @tc.name: SwiperModelTestNg021
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, swiper lopp is true and
     * indicator loop is false.
     * @tc.expected: loop is true.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetLoop(true);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetLoop(false);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    /**
     * @tc.steps: step2. swiper loop is false.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. swiper loop is true.
     * @tc.expected: change page to 0.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateLoop(true);
    EXPECT_TRUE(indicatorPattern->IsLoop());
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg022
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and indicator type is DOT, indicator use mode is BIND, swiper index is 1.
     * @tc.expected: index is 1.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 1.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step3. loop is true and Reset index.
     * @tc.expected: change page to 0.
     */
    layoutProperty_->ResetIndex();
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperModelTestNg023
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and indicator type is DOT, indicator use mode is BIND, swiper index is 1.
     * @tc.expected: index is 1.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(1);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 2.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
}

/**
 * @tc.name: SwiperModelTestNg024
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator index is 2.
     * @tc.expected: index is 2.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetInitialIndex(2);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
}

/**
 * @tc.name: SwiperModelTestNg025
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND，not set index.
     * @tc.expected: index is 0.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetInitialIndex(2);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step3. loop is true.
     * @tc.expected: change page to 2.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateInitialIndex(1);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
    ShowNextPage();
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
}

/**
 * @tc.name: SwiperModelTestNg026
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND，not set index.
     * @tc.expected: index is 0.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. loop is true and update index.
     * @tc.expected: change page to 1.
     */
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateIndex(1);
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
}

/**
 * @tc.name: SwiperModelTestNg027
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND，not set index.
     * @tc.expected: index is 0.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(1);
        swiperModel.SetOnChange(onChange);
    });
    CreateSwiperDone();
    IndicatorModelNG model;
    model.Create();
    model.SetInitialIndex(2);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 2.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
    /**
     * @tc.steps: step3. loop is true.
     * @tc.expected: change page to 2.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateInitialIndex(3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);

    SwipeTo(2);
    EXPECT_EQ(currentIndex, 2);
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SwiperModelTestNg028
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND，not set index.
     * @tc.expected: index is 0.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetIndex(2);
        swiperModel.SetOnChange(onChange);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetInitialIndex(1);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
    /**
     * @tc.steps: step2. loop is true.
     * @tc.expected: change page to 3.
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 3);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step3. loop is true and update index.
     * @tc.expected: change page to 2.
     */
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(2);
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(indicatorPattern->GetCurrentIndex(), 2);
    /**
     * @tc.steps: step4. call GetTextContentSub.
     */
    EXPECT_NE(indicatorPattern->GetNonAutoLayoutDirection(), TextDirection::RTL);

    std::string firstContent;
    std::string lastContent;
    swiperLayoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    indicatorPattern->GetTextContentSub(firstContent, lastContent);
    EXPECT_EQ(firstContent, "3");
    EXPECT_EQ(lastContent, "/4");
    /**
     * @tc.steps: step5. call GetTextContentSub.
     */
    swiperLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    indicatorPattern->GetTextContentSub(firstContent, lastContent);
    EXPECT_EQ(firstContent, "4");
    EXPECT_EQ(lastContent, "3/");
}

/**
 * @tc.name: SwiperModelTestNg029
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, swiper direct is HORIZONTAL.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) { swiperModel.SetBindIndicator(true); });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperModelTestNg030
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator direct is HORIZONTAL.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperModelTestNg031
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, indicator direct is HORIZONTAL.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) { swiperModel.SetBindIndicator(true); });

    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperModelTestNg032
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, swiper direct is HORIZONTAL.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. indicator direct is VERTICAL.
     * @tc.expected: direct is VERTICAL.
     */
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: SwiperModelTestNg033
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND, swiper not set direct.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) { swiperModel.SetBindIndicator(true); });

    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. update indicator direct is VERTICAL.
     * @tc.expected: direct not change.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperModelTestNg034
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND.
     * @tc.expected: direct is HORIZONTAL.
     */
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. indicator direct is HORIZONTAL and swiper direct is VERTICAL.
     * @tc.expected: direct is VERTICAL.
     */
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: SwiperModelTestNg035
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND.
     * @tc.expected: direct is HORIZONTAL.
     */
    SwiperParameters swiperParameters { Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f),
        std::nullopt, Dimension(2.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), true,
        Color::RED, Color::GREEN, 6 };
    CreateWithItem([&swiperParameters](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
        swiperModel.SetDotIndicatorStyle(swiperParameters);
        swiperModel.SetIndicatorInteractive(true);
    });

    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    auto pattern = indicatorPattern->GetSwiperPattern();
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    SwiperHelper::SaveDotIndicatorProperty(indicatorNode_, *(AceType::RawPtr(pattern_)));
    EXPECT_NE(indicatorPattern->GetSwiperParameters(), nullptr);
    /**
     * @tc.steps: step2. indicator direct is VERTICAL and swiper direct is HORIZONTAL.
     * @tc.expected: direct is HORIZONTAL.
     */
    auto indicatorLayoutProperty = indicatorPattern->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    indicatorLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperModelTestNg036
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is BIND.
     * @tc.expected: indicator's count not equal RealTotalCount.
     */
    SwiperModelNG swiperModel;
    frameNode_ = swiperModel.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    FrameNode* frameNode = AceType::RawPtr(frameNode_);
    swiperModel.SetBindIndicator(frameNode, true);
    swiperModel.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    swiperModel.SetSwipeByGroup(frameNode, false);
    swiperModel.SetDisplayMode(frameNode, SwiperDisplayMode::AUTO_LINEAR);
    swiperModel.SetMinSize(frameNode, Dimension { 10.f });
    swiperModel.SetHoverShow(frameNode, true);
    swiperModel.SetNextMargin(frameNode, Dimension { 10.f }, true);
    swiperModel.SetPreviousMargin(frameNode, Dimension { 10.f }, true);
    swiperModel.SetEnabled(frameNode, false);
    SwiperDigitalParameters swiperDigitalParameters;
    swiperModel.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    FlushUITasks(frameNode_);
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern_, nullptr);

    IndicatorModelNG model;
    model.Create();
    model.SetCount(2);
    model.SetDirection(Axis::VERTICAL);
    indicatorNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorPattern->CreateDotIndicatorPaintMethod(pattern_);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    EXPECT_NE(indicatorPattern->RealTotalCount(), 2);
}

/**
 * @tc.name: SwiperModelTestNg037
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, SwiperModelTestNg037, TestSize.Level1)
{
    auto restFunc = []() {};
    CreateWithItem([restFunc](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetJSIndicatorController(restFunc);
        swiperModel.ResetJSIndicatorController();
    });

    IndicatorModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    KeyEvent event;
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_FALSE(indicatorPattern->OnKeyEvent(event));
}
 
/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(indicatorPattern->OnKeyEvent(event));
}
 
/**
 * @tc.name: OnKeyEvent003
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(indicatorPattern->OnKeyEvent(event));
}
 
/**
 * @tc.name: OnKeyEvent004
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(indicatorPattern->OnKeyEvent(event));
}
 
/**
 * @tc.name: OnKeyEvent005
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::VERTICAL);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(indicatorPattern->OnKeyEvent(event));
}
 
/**
 * @tc.name: OnKeyEvent006
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnKeyEvent006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorController_ = indicatorPattern->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);
    indicatorController_->SetSwiperNode(frameNode_);
    FlushUITasks(indicatorNode_);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::HORIZONTAL);
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(indicatorPattern->GetDirection(), Axis::VERTICAL);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(indicatorPattern->OnKeyEvent(event));
}

 /**
 * @tc.name: OnIndexChangeInSingleMode001
 * @tc.desc: OnIndexChangeInSingleMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnIndexChangeInSingleMode001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
        swiperModel.SetLoop(true);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorPattern->isPressed_ = true;
    indicatorPattern->isHover_ = false;
    indicatorPattern->OnIndexChangeInSingleMode(5);
    EXPECT_EQ(indicatorPattern->currentIndexInSingleMode_, 1);
}

/**
 * @tc.name: OnIndexChangeInSingleMode002
 * @tc.desc: OnIndexChangeInSingleMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, OnIndexChangeInSingleMode002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG swiperModel) {
        swiperModel.SetBindIndicator(true);
        swiperModel.SetDirection(Axis::HORIZONTAL);
        swiperModel.SetLoop(true);
    });
    IndicatorModelNG model;
    model.Create();
    model.SetDirection(Axis::HORIZONTAL);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    indicatorNode_ = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorPattern->isPressed_ = false;
    indicatorPattern->isHover_ = true;
    indicatorPattern->OnIndexChangeInSingleMode(-5);
    EXPECT_EQ(indicatorPattern->currentIndexInSingleMode_, 0);
}

/**
 * @tc.name: ProcessDotPositionWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDotPositionWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDotPositionWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperParameters swiperParameters;
    pattern_->SetSwiperParameters(swiperParameters);

    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObj);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObj);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObj);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimLeft, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimRight, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimTop, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimBottom, 0.0_vp);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimLeft, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimRight, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimTop, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimBottom, 100.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObjWithString);
    model.ProcessDotPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimLeft, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimRight, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimTop, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->dimBottom, 0.0_vp);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessDotSizeWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDotSizeWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDotSizeWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperParameters swiperParameters;
    pattern_->SetSwiperParameters(swiperParameters);

    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemWidth", resObj);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemHeight", resObj);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemWidth", resObj);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemHeight", resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto result = theme->GetSize();
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemWidth, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemHeight, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemWidth, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemHeight, result);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemWidth", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemHeight", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemWidth", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemHeight", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemWidth, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemHeight, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemWidth, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemHeight, 100.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemWidth", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "itemHeight", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemWidth", resObjWithString);
    model.ProcessDotSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedItemHeight", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemWidth, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->itemHeight, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemWidth, result);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedItemHeight, result);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessDotColorWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDotColorWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDotColorWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperParameters swiperParameters;
    pattern_->SetSwiperParameters(swiperParameters);

    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "colorVal", resObj);
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedColorVal", resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto colorVal = theme->GetColor();
    auto selectedColorVal = theme->GetSelectedColor();
    EXPECT_EQ(pattern_->GetSwiperParameters()->colorVal, colorVal);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedColorVal, selectedColorVal);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "colorVal", resObjWithString);
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedColorVal", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->colorVal, Color::RED);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedColorVal, Color::RED);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "colorVal", resObjWithString);
    model.ProcessDotColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedColorVal", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperParameters()->colorVal, colorVal);
    EXPECT_EQ(pattern_->GetSwiperParameters()->selectedColorVal, selectedColorVal);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessDigitalPositionWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDigitalPositionWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDigitalPositionWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperDigitalParameters swiperParameters;
    pattern_->SetSwiperDigitalParameters(swiperParameters);

    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObj);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObj);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObj);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimLeft, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimRight, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimTop, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimBottom, 0.0_vp);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimLeft, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimRight, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimTop, 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimBottom, 100.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimLeft", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimRight", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimTop", resObjWithString);
    model.ProcessDigitalPositionWithResourceObj(Referenced::RawPtr(frameNode_), "dimBottom", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimLeft, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimRight, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimTop, 0.0_vp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->dimBottom, 0.0_vp);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessDigitalFontSizeWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDigitalFontSizeWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDigitalFontSizeWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperDigitalParameters swiperParameters;
    pattern_->SetSwiperDigitalParameters(swiperParameters);

    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "fontSize", resObj);
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontSize", resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto fontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontSize.value(), fontSize);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontSize.value(), fontSize);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "fontSize", resObjWithString);
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontSize", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontSize.value(), 100.0_fp);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontSize.value(), 100.0_fp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "fontSize", resObjWithString);
    model.ProcessDigitalFontSizeWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontSize", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontSize.value(), fontSize);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontSize.value(), fontSize);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessDigitalColorWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessDigitalColorWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessDigitalColorWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperDigitalParameters swiperParameters;
    pattern_->SetSwiperDigitalParameters(swiperParameters);

    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "", nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "fontColor", resObj);
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontColor", resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto fontColor = theme->GetDigitalIndicatorTextStyle().GetTextColor();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontColor, fontColor);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontColor, fontColor);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "fontColor", resObjWithString);
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontColor", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontColor, Color::RED);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontColor, Color::RED);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "fontColor", resObjWithString);
    model.ProcessDigitalColorWithResourceObj(Referenced::RawPtr(frameNode_), "selectedFontColor", resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->fontColor, fontColor);
    EXPECT_EQ(pattern_->GetSwiperDigitalParameters()->selectedFontColor, fontColor);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessArrowColorWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessArrowColorWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessArrowColorWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateArrowColor(Color::RED);

    model.ProcessArrowColorWithResourceObj(Referenced::RawPtr(frameNode_), nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessArrowColorWithResourceObj(Referenced::RawPtr(frameNode_), resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto param = pattern_->GetSwiperArrowParameters();
    auto arrowColor = param->isSidebarMiddle.value() ? theme->GetBigArrowColor() : theme->GetSmallArrowColor();
    EXPECT_EQ(swiperLayoutProperty->GetArrowColorValue(), arrowColor);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    model.ProcessArrowColorWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(swiperLayoutProperty->GetArrowColorValue(), Color::RED);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessArrowColorWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(swiperLayoutProperty->GetArrowColorValue(), arrowColor);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessArrowBackgroundColorWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessArrowBackgroundColorWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessArrowBackgroundColorWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateBackgroundColor(Color::RED);

    model.ProcessArrowBackgroundColorWithResourceObj(Referenced::RawPtr(frameNode_), nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessArrowBackgroundColorWithResourceObj(Referenced::RawPtr(frameNode_), resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    auto param = pattern_->GetSwiperArrowParameters();
    auto backgroundColor =
        param->isSidebarMiddle.value() ? theme->GetBigArrowBackgroundColor() : theme->GetSmallArrowBackgroundColor();
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundColorValue(), backgroundColor);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "#FF0000");
    model.ProcessArrowBackgroundColorWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundColorValue(), Color::RED);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessArrowBackgroundColorWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundColorValue(), backgroundColor);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessArrowSizeWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessArrowSizeWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessArrowSizeWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperArrowParameters swiperParameters;
    swiperParameters.isSidebarMiddle = true;
    swiperParameters.isShowBackground = false;
    pattern_->SetSwiperArrowParameters(swiperParameters);
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateBackgroundSize(Dimension(0.0, DimensionUnit::PX));
    swiperLayoutProperty->UpdateArrowSize(Dimension(0.0, DimensionUnit::PX));

    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto fontSize = pattern_->GetSwiperArrowParameters()->isSidebarMiddle.value() ? theme->GetBigArrowSize()
                                                                                  : theme->GetSmallArrowSize();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), fontSize);
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), fontSize);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), 100.0_vp);
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), 100.0_vp);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), 100.0_vp);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), 100.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), fontSize);
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), fontSize);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessArrowSizeWithResourceObjTest002
 * @tc.desc: Verify SwiperModelTestNg::ProcessArrowSizeWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessArrowSizeWithResourceObjTest002, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperArrowParameters swiperParameters;
    swiperParameters.isSidebarMiddle = true;
    swiperParameters.isShowBackground = true;
    swiperParameters.backgroundSize = Dimension(0.0, DimensionUnit::PX);
    pattern_->SetSwiperArrowParameters(swiperParameters);
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateBackgroundSize(Dimension(0.0, DimensionUnit::PX));
    swiperLayoutProperty->UpdateArrowSize(Dimension(0.0, DimensionUnit::PX));

    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObj);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), 0.0_px);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), 0.0_px);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessArrowSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->arrowSize.value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize().value(), 0.0_px);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), 0.0_px);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}

/**
 * @tc.name: ProcessBackgroundSizeWithResourceObjTest001
 * @tc.desc: Verify SwiperModelTestNg::ProcessBackgroundSizeWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModelTestNg, ProcessBackgroundSizeWithResourceObjTest001, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();

    SwiperArrowParameters swiperParameters;
    swiperParameters.isSidebarMiddle = true;
    swiperParameters.isShowBackground = false;
    pattern_->SetSwiperArrowParameters(swiperParameters);
    auto swiperLayoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateBackgroundSize(Dimension(0.0, DimensionUnit::PX));
    swiperLayoutProperty->UpdateArrowSize(Dimension(0.0, DimensionUnit::PX));

    model.ProcessBackgroundSizeWithResourceObj(Referenced::RawPtr(frameNode_), nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessBackgroundSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObj);
    pattern_->resourceMgr_->ReloadResources();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto fontSize = pattern_->GetSwiperArrowParameters()->isSidebarMiddle.value()
                        ? theme->GetBigArrowBackgroundSize()
                        : theme->GetSmallArrowBackgroundSize();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), fontSize);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100");
    model.ProcessBackgroundSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), 100.0_vp);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), 100.0_vp);

    ResetMockResourceData();
    AddMockResourceData(0, "-100");
    model.ProcessBackgroundSizeWithResourceObj(Referenced::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern_->GetSwiperArrowParameters()->backgroundSize.value(), fontSize);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize().value(), fontSize);

    CreateSwiperDone();
    g_isConfigChangePerform = false;
    ResetMockResourceData();
}
} // namespace OHOS::Ace::NG

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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_event_hub.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class IndicatorModelTestNg : public SwiperTestNg {
public:
    void TearDown() override;

    void Create(const std::function<void(IndicatorModelNG)>& callback = nullptr);
    void CreateWithItem(
        const std::function<void(IndicatorModelNG)>& callback = nullptr, int32_t itemNumber = ITEM_NUMBER);

    void ShowNextPage();
    void ShowPreviousPage();
    void ChangeIndex(int32_t index, bool useAnimation = false);

private:
    RefPtr<IndicatorPattern> indicatorPattern_;
    RefPtr<IndicatorEventHub> indicatorEventHub_;
    RefPtr<SwiperIndicatorLayoutProperty> indicatorLayoutProperty_;
    RefPtr<DotIndicatorPaintProperty> indicatorPaintProperty_;
    RefPtr<IndicatorController> indicatorController_;
    RefPtr<SwiperIndicatorAccessibilityProperty> indicatorAccessibilityProperty_;
};

void IndicatorModelTestNg::TearDown()
{
    frameNode_ = nullptr;
    indicatorPattern_ = nullptr;
    indicatorEventHub_ = nullptr;
    indicatorLayoutProperty_ = nullptr;
    indicatorPaintProperty_ = nullptr;
    indicatorController_ = nullptr;
    indicatorAccessibilityProperty_ = nullptr;
    SwiperTestNg::TearDown();
}

void IndicatorModelTestNg::Create(const std::function<void(IndicatorModelNG)>& callback)
{
    IndicatorModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    indicatorEventHub_ = frameNode_->GetEventHub<IndicatorEventHub>();
    EXPECT_NE(indicatorEventHub_, nullptr);
    indicatorLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_NE(indicatorLayoutProperty_, nullptr);
    indicatorAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperIndicatorAccessibilityProperty>();
    indicatorController_ = indicatorPattern_->GetIndicatorController();
    FlushUITasks(frameNode_);
}

void IndicatorModelTestNg::CreateWithItem(const std::function<void(IndicatorModelNG)>& callback, int32_t itemNumber)
{
    Create([callback, itemNumber](IndicatorModelNG model) {
        if (callback) {
            callback(model);
        }
    });
}

void IndicatorModelTestNg::ShowNextPage()
{
    indicatorController_->ShowNext();
    FlushUITasks(frameNode_);
}

void IndicatorModelTestNg::ShowPreviousPage()
{
    indicatorController_->ShowPrevious();
    FlushUITasks(frameNode_);
}

void IndicatorModelTestNg::ChangeIndex(int32_t index, bool useAnimation)
{
    indicatorController_->ChangeIndex(index, useAnimation);
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: IndicatorModelTestNg001
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, loop is false.
     */
    SwiperParameters swiperParameters { Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f),
        Dimension(2.f), Dimension(2.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), true,
        Color::RED, Color::GREEN, 0 };

    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange, &swiperParameters](IndicatorModelNG model) {
        model.SetIndicatorStyle(swiperParameters);
        model.SetDirection(Axis::HORIZONTAL);
        model.SetShowIndicator(true);
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    indicatorLayoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->colorVal, Color::RED);
    EXPECT_EQ(indicatorPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_TRUE(indicatorLayoutProperty_->GetShowIndicator());
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    indicatorPattern_->OnModifyDone();
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 2
     */
    ChangeIndex(2);
    EXPECT_EQ(currentIndex, 2);
}

/**
 * @tc.name: IndicatorModelTestNg002
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, loop is false.
     */
    SwiperParameters swiperParameters { Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f),
        std::nullopt, std::nullopt, Dimension(10.f), Dimension(10.f), Dimension(10.f), Dimension(10.f), true,
        Color::RED, Color::GREEN, std::nullopt };

    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange, &swiperParameters](IndicatorModelNG model) {
        model.SetDotIndicatorStyle(swiperParameters);
        model.SetCount(4);
        model.SetInitialIndex(0);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->colorVal, Color::RED);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: IndicatorModelTestNg003
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg003, TestSize.Level1)
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
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg004
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, loop is false.
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
    CreateWithItem([&onChange, &swiperDigitalParameters](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDigitIndicatorStyle(swiperDigitalParameters);
        model.SetDirection(Axis::HORIZONTAL);
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->fontColor, Color::RED);
    EXPECT_EQ(indicatorPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    indicatorPattern_->DumpAdvanceInfo();
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 1
     */
    ChangeIndex(0);
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg005
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg005, TestSize.Level1)
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
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetCount(4);
        model.SetInitialIndex(0);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: IndicatorModelTestNg006
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg006, TestSize.Level1)
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
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg007
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg007, TestSize.Level1)
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
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetCount(4);
        model.SetInitialIndex(3);
        model.SetLoop(true);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(indicatorPattern_->IsLoop());

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 0
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg008
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg008, TestSize.Level1)
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

    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetCount(4);
        model.SetInitialIndex(3);
        model.SetLoop(true);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 3);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_TRUE(indicatorPattern_->IsLoop());

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change to 0
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg009
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DOT, indicator use mode is SINGLE, cout < index.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = std::make_optional<Color>(Color::RED);
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    indicatorPattern_->InitIndicatorController();
    indicatorLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_NE(indicatorLayoutProperty_, nullptr);
    indicatorController_ = indicatorPattern_->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);

    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    model.SetDirection(frameNode, Axis::HORIZONTAL);
    model.SetShowIndicator(frameNode, true);
    model.SetCount(frameNode, 4);
    model.SetInitialIndex(frameNode, 5);
    model.SetLoop(frameNode, false);
    model.SetOnChange(frameNode, onChange);

    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->colorVal, Color::RED);
    EXPECT_EQ(indicatorPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_TRUE(indicatorLayoutProperty_->GetShowIndicator());
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    EXPECT_FALSE(model.GetLoop(frameNode));
    EXPECT_EQ(model.GetCount(frameNode), 4);

    /**
     * @tc.steps: step2. show next page
     * @tc.expected: currentIndex change 0 to 1
     */
    ShowNextPage();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: IndicatorModelTestNg010
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, cout < index.
     */
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.fontColor = Color::RED;
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };

    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    indicatorLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_NE(indicatorLayoutProperty_, nullptr);
    indicatorController_ = indicatorPattern_->GetIndicatorController();
    EXPECT_NE(indicatorController_, nullptr);

    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    model.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    model.SetDirection(frameNode, Axis::HORIZONTAL);
    model.SetCount(frameNode, 4);
    model.SetInitialIndex(frameNode, 5);
    model.SetLoop(frameNode, false);
    model.SetOnChange(frameNode, onChange);

    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->fontColor, Color::RED);
    EXPECT_EQ(indicatorPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
    EXPECT_FALSE(indicatorPattern_->IsLoop());

    /**
     * @tc.steps: step2. show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPreviousPage();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: IndicatorModelTestNg011
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg011, TestSize.Level1)
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
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 0
     */
    ChangeIndex(0);
    EXPECT_EQ(currentIndex, 0);
    /**
     * @tc.steps: step3. change page
     * @tc.expected: currentIndex change to 3
     */
    ChangeIndex(-1);
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg012
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, not set SwiperDigitalParameters.
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    CreateWithItem([&onChange](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDirection(Axis::HORIZONTAL);
        model.SetCount(4);
        model.SetInitialIndex(1);
        model.SetLoop(false);
        model.SetOnChange(onChange);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_EQ(indicatorPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 4);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 1);
    EXPECT_FALSE(indicatorPattern_->IsLoop());
    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex change to 2
     */
    ChangeIndex(2);
    EXPECT_EQ(currentIndex, 2);
    /**
     * @tc.steps: step3. call GetTextContentSub.
     */
    EXPECT_FALSE(indicatorPattern_->IsHorizontalAndRightToLeft());

    std::string firstContent;
    std::string lastContent;
    indicatorLayoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    indicatorPattern_->GetTextContentSub(firstContent, lastContent);
    EXPECT_EQ(firstContent, "3");
    EXPECT_EQ(lastContent, "/4");
    /**
     * @tc.steps: step4. call GetTextContentSub.
     */
    indicatorLayoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(indicatorPattern_->IsHorizontalAndRightToLeft());
    indicatorPattern_->GetTextContentSub(firstContent, lastContent);
    EXPECT_EQ(firstContent, "4");
    EXPECT_EQ(lastContent, "3\\");

    /**
     * @tc.steps: step2. change page
     * @tc.expected: currentIndex equal 2, change page to others idnex.
     */
    ChangeIndex(2, true);
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 2);
    ChangeIndex(1, true);
    EXPECT_EQ(currentIndex, 1);
    ChangeIndex(3, true);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 3);
    ChangeIndex(4, true);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg013
 * @tc.desc: indicator Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init.
     * indicator type is DIGIT, indicator use mode is SINGLE, not set SwiperDigitalParameters.
     */
    CreateWithItem([](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDirection(Axis::VERTICAL);
        model.SetCount(3);
    });
    EXPECT_EQ(indicatorLayoutProperty_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    EXPECT_FALSE(indicatorPattern_->IsHorizontalAndRightToLeft());
    EXPECT_TRUE(indicatorPattern_->IsLoop());
    EXPECT_EQ(indicatorPattern_->GetCountFromProperty(), 3);
    EXPECT_EQ(indicatorPattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg014
 * @tc.desc: check function about SwiperIndicatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1.indicator type is DOT, indicator use mode is SINGLE
     */
    SwiperParameters swiperParameters;
    swiperParameters.dimStart = std::make_optional<Dimension>(2.f);
    swiperParameters.dimEnd = std::make_optional<Dimension>(2.f);
    CreateWithItem([&swiperParameters](IndicatorModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DOT);
        model.SetDotIndicatorStyle(swiperParameters);
    });
    indicatorLayoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    indicatorPattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    indicatorPattern_->isRepeatClicked_ = false;
    indicatorPattern_->mouseClickIndex_ = 0;
    std::optional<int32_t> mouseClickIndex;
    indicatorPattern_->SwipeTo(mouseClickIndex);
    ASSERT_NE(frameNode_, nullptr);
    auto eventHub = frameNode_->GetOrCreateGestureEventHub();
    indicatorPattern_->InitClickEvent(eventHub);
    indicatorPattern_->InitLongPressEvent(eventHub);
    GestureEvent info;
    info.SetSourceDevice(SourceType::KEYBOARD);
    indicatorPattern_->clickEvent_->GetGestureEventFunc()(info);
    EXPECT_FALSE(indicatorPattern_->isClicked_);
    info.SetSourceDevice(SourceType::MOUSE);
    indicatorPattern_->clickEvent_->GetGestureEventFunc()(info);
    EXPECT_TRUE(indicatorPattern_->isClicked_);
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern_->clickEvent_->GetGestureEventFunc()(info);
    EXPECT_TRUE(indicatorPattern_->isClicked_);
    indicatorPattern_->longPressEvent_->GetGestureEventFunc()(info);
    EXPECT_TRUE(indicatorPattern_->IsHorizontalAndRightToLeft());
    EXPECT_EQ(indicatorPattern_->GetCurrentShownIndex(), 1);
}

/**
 * @tc.name: IndicatorModelTestNg015
 * @tc.desc: Text dimBottom of DigitalIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg015, TestSize.Level1)
{
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.dimBottom = std::make_optional<Dimension>(2.f);
    swiperDigitalParameters.ignoreSizeValue = std::make_optional<bool>(false);
    swiperDigitalParameters.setIgnoreSizeValue = std::make_optional<bool>(false);
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));
    EXPECT_NE(frameNode, nullptr);
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    model.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);

    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->dimBottom, Dimension(2.f));
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->ignoreSizeValue, false);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->setIgnoreSizeValue, false);

    swiperDigitalParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::VP);
    model.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->dimBottom, Dimension(2.f, DimensionUnit::VP));

    swiperDigitalParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::FP);
    model.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->dimBottom, Dimension(2.f, DimensionUnit::FP));

    swiperDigitalParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::LPX);
    model.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    EXPECT_EQ(indicatorPattern_->swiperDigitalParameters_->dimBottom, Dimension(2.f, DimensionUnit::LPX));
}

/**
 * @tc.name: IndicatorModelTestNg016
 * @tc.desc: Text dimBottom of DotIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg016, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.dimBottom = std::make_optional<Dimension>(2.f);
    swiperParameters.ignoreSizeValue = std::make_optional<bool>(false);
    swiperParameters.setIgnoreSizeValue = std::make_optional<bool>(false);
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));
    EXPECT_NE(frameNode, nullptr);
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimBottom, Dimension(2.f));
    EXPECT_EQ(indicatorPattern_->swiperParameters_->ignoreSizeValue, false);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->setIgnoreSizeValue, false);

    swiperParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::VP);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimBottom, Dimension(2.f, DimensionUnit::VP));

    swiperParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::FP);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimBottom, Dimension(2.f, DimensionUnit::FP));

    swiperParameters.dimBottom = std::make_optional<Dimension>(2.f, DimensionUnit::LPX);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimBottom, Dimension(2.f, DimensionUnit::LPX));
}

/**
 * @tc.name: IndicatorModelTestNg017
 * @tc.desc: Text dimSpace of DotIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg017, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.dimSpace = std::make_optional<Dimension>(2.f);
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));
    EXPECT_NE(frameNode, nullptr);
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimSpace, Dimension(2.f));

    swiperParameters.dimSpace = std::make_optional<Dimension>(2.f, DimensionUnit::VP);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimSpace, Dimension(2.f, DimensionUnit::VP));

    swiperParameters.dimSpace = std::make_optional<Dimension>(2.f, DimensionUnit::FP);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimSpace, Dimension(2.f, DimensionUnit::FP));

    swiperParameters.dimSpace = std::make_optional<Dimension>(2.f, DimensionUnit::LPX);
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->swiperParameters_->dimSpace, Dimension(2.f, DimensionUnit::LPX));
}

/**
 * @tc.name: IndicatorModelTestNg018
 * @tc.desc: Text CreateDigitWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg018, TestSize.Level1)
{
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.fontColor = Color::RED;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.CreateDigitWithResourceObj(frameNode, swiperDigitalParameters);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: IndicatorModelTestNg019
 * @tc.desc: Text CreateDotWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg019, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color::RED;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.CreateDotWithResourceObj(frameNode, swiperParameters);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: IndicatorModelTestNg020
 * @tc.desc: Text ProcessDotSizeWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg020, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.ProcessDotSizeWithResourceObj(frameNode, "itemWidth", nullptr);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);
 
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDotSizeWithResourceObj(frameNode, "itemWidth", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDotSizeWithResourceObj(frameNode, "itemHeight", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDotSizeWithResourceObj(frameNode, "SelectedItemWidth", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDotSizeWithResourceObj(frameNode, "selectedItemHeight", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg021
 * @tc.desc: Text ProcessDigitalFontSizeWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg021, TestSize.Level1)
{
    SwiperDigitalParameters swiperDigitalParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.ProcessDigitalFontSizeWithResourceObj(frameNode, "fontSize", nullptr);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDigitalFontSizeWithResourceObj(frameNode, "fontSize", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDigitalFontSizeWithResourceObj(frameNode, "fontSize", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDigitalFontSizeWithResourceObj(frameNode, "selectedFontSize", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg022
 * @tc.desc: Text ProcessDotColorWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg022, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.ProcessDotColorWithResourceObj(frameNode, "colorVal", nullptr);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDotColorWithResourceObj(frameNode, "colorVal", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDotColorWithResourceObj(frameNode, "selectedColorVal", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg023
 * @tc.desc: Text ProcessDigitalFontColorWithResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg023, TestSize.Level1)
{
    SwiperDigitalParameters swiperDigitalParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    model.ProcessDigitalColorWithResourceObj(frameNode, "fontColor", nullptr);
    EXPECT_EQ(indicatorPattern_->resourceMgr_, nullptr);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.ProcessDigitalColorWithResourceObj(frameNode, "fontColor", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);

    model.ProcessDigitalColorWithResourceObj(frameNode, "selectedFontColor", resObj);
    indicatorPattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(indicatorPattern_->resourceMgr_, nullptr);
    EXPECT_NE(indicatorPattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: IndicatorModelTestNg024
 * @tc.desc: Text UpdateDefaultColor
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg024, TestSize.Level1)
{
    SwiperDigitalParameters swiperDigitalParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    swiperDigitalParameters.fontColor = Color::RED;
    swiperDigitalParameters.selectedFontColor = Color::BLUE;
    model.SetDigitIndicatorStyle(swiperDigitalParameters);
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    indicatorPattern_->OnColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    EXPECT_NE(indicatorPattern_->GetSwiperDigitalParameters()->fontColor, Color::RED);
    EXPECT_NE(indicatorPattern_->GetSwiperDigitalParameters()->selectedFontColor, Color::BLUE);
    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
}

/**
 * @tc.name: IndicatorModelTestNg025
 * @tc.desc: Text OnColorModeChange
 */
HWTEST_F(IndicatorModelTestNg, IndicatorModelTestNg025, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    IndicatorModelNG model;
    frameNode_ = model.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    indicatorPattern_ = frameNode_->GetPattern<IndicatorPattern>();
    EXPECT_NE(indicatorPattern_, nullptr);
    indicatorPaintProperty_ = frameNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    FrameNode* frameNode = static_cast<FrameNode*>(AceType::RawPtr(frameNode_));

    swiperParameters.colorVal = Color::RED;
    swiperParameters.parametersByUser.insert("colorVal");
    model.SetDotIndicatorStyle(frameNode, swiperParameters);
    model.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    indicatorPattern_->OnColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    EXPECT_EQ(indicatorPaintProperty_->GetColorValue(Color::BLACK), Color::RED);
    EXPECT_EQ(indicatorPattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
}
} // namespace OHOS::Ace::NG
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_theme_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr uint32_t TOKEN_THEME_ID = 10001;
constexpr Dimension WIDTH = 10.0_vp;
constexpr Dimension HEIGHT = 10.0_vp;
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const Color COLOR = Color::BLUE;
constexpr double DEFAULT_BUTTON_OPACITY = 1.0;
struct TestProperty {
    const ArkUI_Uint32 colors_[TokenColors::TOTAL_NUMBER] = {
        // id for color value for test
        125830976, /* BRAND = 0 */
        125830979, /* WARNING = 1; */
        125830980, /* ALERT = 2 */
        125830981, /* CONFIRM = 3 */
        125830982, /* FONT_PRIMARY = 4 */
        125830983, /* FONT_SECONDARY = 5 */
        125830984, /* FONT_TERTIARY = 6 */
        125830985, /* FONT_FOURTH = 7 */
        125830986, /* FONT_EMPHASIZE = 8 */
        125830987, /* FONT_ON_PRIMARY = 9 */
        125830988, /* FONT_ON_SECONDARY = 10 */
        125830989, /* FONT_ON_TERTIARY = 11 */
        125830990, /* FONT_ON_FOURTH = 12 */
        125830991, /* ICON_PRIMARY = 13 */
        125830992, /* ICON_SECONDARY = 14 */
        125830993, /* ICON_TERTIARY = 15 */
        125830994, /* ICON_FOURTH = 16 */
        125830995, /* ICON_EMPHASIZE = 17 */
        125830996, /* ICON_SUB_EMPHASIZE = 18 */
        125831057, /* ICON_ON_PRIMARY = 19 */
        125831058, /* ICON_ON_SECONDARY = 20 */
        125831059, /* ICON_ON_TERTIARY = 21 */
        125831060, /* ICON_ON_FOURTH = 22 */
        125831061, /* BACKGROUND_PRIMARY = 23 */
        125831062, /* BACKGROUND_SECONDARY = 24 */
        125831063, /* BACKGROUND_TERTIARY = 25 */
        125831064, /* BACKGROUND_FOURTH = 26 */
        125831065, /* BACKGROUND_EMPHASIZE = 27 */
        125831003, /* COMP_FOREGROUND_PRIMARY = 28 */
        125831004, /* COMP_BACKGROUND_PRIMARY = 29 */
        -1,        /* COMP_BACKGROUND_PRIMARY_TRAN = 30 */
        125831005, /* COMP_BACKGROUND_PRIMARY_CONTRARY = 31 */
        125831006, /* COMP_BACKGROUND_GRAY = 32 */
        125831007, /* COMP_BACKGROUND_SECONDARY = 33 */
        125831008, /* COMP_BACKGROUND_TERTIARY = 34 */
        125831009, /* COMP_BACKGROUND_EMPHASIZE = 35 */
        125831066, /* COMP_BACKGROUND_NEUTRAL = 36 */
        125831011, /* COMP_EMPHASIZE_SECONDARY = 37 */
        125831012, /* COMP_EMPHASIZE_TERTIARY = 38 */
        125831013, /* COMP_DIVIDER = 39 */
        125831014, /* COMP_COMMON_CONTRARY = 40 */
        125831015, /* COMP_BACKGROUND_FOCUS = 41 */
        125831016, /* COMP_FOCUSED_PRIMARY = 42 */
        125831017, /* COMP_FOCUSED_SECONDARY = 43 */
        125831018, /* COMP_FOCUSED_TERTIARY = 44 */
        125831019, /* INTERACTIVE_HOVER = 45 */
        125831020, /* INTERACTIVE_PRESSED = 46 */
        125831021, /* INTERACTIVE_FOCUS = 47 */
        125831022, /* INTERACTIVE_ACTIVE = 48 */
        125831023, /* INTERACTIVE_SELECT = 49 */
        125831024, /* INTERACTIVE_CLICK = 50 */
    };
    RefPtr<TokenColors> tokenColors_;
};
} // namespace

class CounterTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(CounterModelNG)>& callback = nullptr);

    RefPtr<CounterNode> frameNode_;
    RefPtr<CounterPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
};

void CounterTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly(Return(CounterThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants)));
}

void CounterTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void CounterTestNg::SetUp() {}

void CounterTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

void CounterTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<CounterNode>(element);
    pattern_ = frameNode_->GetPattern<CounterPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
}

void CounterTestNg::Create(const std::function<void(CounterModelNG)>& callback)
{
    CounterModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: CounterPatternTest002
 * @tc.desc: Test counter SetOnInc and SetOnDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest002, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        auto counterEventFunc1 = []() {};
        model.SetOnInc(std::move(counterEventFunc1));
        auto counterEventFunc2 = []() {};
        model.SetOnDec(std::move(counterEventFunc2));
    });

    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subGestureHub = subNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(subGestureHub->parallelCombineClick, false);
    EXPECT_NE(subGestureHub->clickEventActuator_->userCallback_, nullptr);

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addGestureHub = addNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(addGestureHub->parallelCombineClick, false);
    EXPECT_NE(addGestureHub->clickEventActuator_->userCallback_, nullptr);
}

/**
 * @tc.name: CounterPatternTest003
 * @tc.desc: Test counter SetHeight and SetWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest003, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(WIDTH);
        model.SetHeight(HEIGHT);
    });

    auto selfIdealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Width()->dimension_, WIDTH);
    EXPECT_EQ(selfIdealSize->Height()->dimension_, HEIGHT);
}

/**
 * @tc.name: CounterPatternTest004
 * @tc.desc: Test counter SetControlWidth, SetStateChange and SetBackgroundColor function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest004, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetControlWidth(WIDTH);
        model.SetStateChange(true);
        model.SetBackgroundColor(COLOR);
    });

    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), COLOR);
}

/**
 * @tc.name: CounterPatternTest005
 * @tc.desc: Test CounterNode AddChildToGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest005, TestSize.Level1)
{
    Create();

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t contentId = pattern_->GetContentId();
    auto contentChildNode = frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(contentId));
    frameNode_->AddChildToGroup(childNode);
    EXPECT_EQ(contentChildNode->children_.size(), 1);

    frameNode_->DeleteChildFromGroup();
    EXPECT_EQ(contentChildNode->children_.size(), 0);
}

/**
 * @tc.name: CounterPatternTest007
 * @tc.desc: Test counter SetEnableInc function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest007, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(true);
        model.SetEnableDec(true);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetOrCreateEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetOrCreateEventHub<EventHub>();
    EXPECT_EQ(addEventHub->IsEnabled(), true);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
    EXPECT_EQ(subEventHub->IsEnabled(), true);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
}

/**
 * @tc.name: CounterPatternTest008
 * @tc.desc: Test counter SetEnableDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest008, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(false);
        model.SetEnableDec(false);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetOrCreateEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetOrCreateEventHub<EventHub>();
    EXPECT_EQ(addEventHub->IsEnabled(), false);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
    EXPECT_EQ(subEventHub->IsEnabled(), false);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterPatternTest009
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest009, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    CounterModelNG model;
    model.Create();
    GetInstance();
    EXPECT_TRUE(pattern_->HasSubNode());
    EXPECT_TRUE(pattern_->HasContentNode());
    EXPECT_TRUE(pattern_->HasAddNode());

    /**
     * Create again,cover all branches in function Create
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    model.Create();
}

/**
 * @tc.name: CounterPatternTest010
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest010, TestSize.Level1)
{
    auto columnNode =
        CounterNode::GetOrCreateCounterNode("Column", 100, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    ASSERT_NE(columnNode, nullptr);
    auto subNode =
        CounterNode::GetOrCreateCounterNode("Column", 101, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    ASSERT_NE(subNode, nullptr);
    subNode->MountToParent(columnNode);
    CounterNode::GetOrCreateCounterNode("Counter", 101, []() { return AceType::MakeRefPtr<CounterPattern>(); });
}

/**
 * @tc.name: CounterPatternTest011
 * @tc.desc: Test counter SetEnableInc function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest011, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetOrCreateEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetOrCreateEventHub<EventHub>();
    model.SetEnableInc(AceType::RawPtr(frameNode_), true);
    model.SetEnableDec(AceType::RawPtr(frameNode_), true);
    EXPECT_EQ(addEventHub->IsEnabled(), true);
    EXPECT_EQ(subEventHub->IsEnabled(), true);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);

    model.SetEnableInc(AceType::RawPtr(frameNode_), false);
    model.SetEnableDec(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(addEventHub->IsEnabled(), false);
    EXPECT_EQ(subEventHub->IsEnabled(), false);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterLayoutAlgorithmTestNg001
 * @tc.desc: test counter Layout.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmTestNg001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto counterPattern = AceType::DynamicCast<CounterPattern>(frameNode->GetPattern());
    ASSERT_NE(counterPattern, nullptr);
    auto counterLayoutAlgorithm = counterPattern->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    counterLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: CounterLayoutAlgorithmTest001
 * @tc.desc: Test counter UpdateTextColor function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    auto counterPattern = AceType::DynamicCast<CounterPattern>(frameNode_->GetPattern());
    ASSERT_NE(counterPattern, nullptr);
    int32_t contentId = counterPattern->GetAddId();
    auto addNode =
        AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(contentId)));
    ASSERT_NE(addNode, nullptr);
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetChildren().front());
    ASSERT_NE(addTextNode, nullptr);
    auto counterLayoutAlgorithm = AceType::DynamicCast<CounterLayoutAlgorithm>(counterPattern->CreateLayoutAlgorithm());
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    counterLayoutAlgorithm->UpdateTextColor(addTextNode, COLOR);
    auto addRenderContext = addTextNode->GetRenderContext();
    ASSERT_NE(addRenderContext, nullptr);
    ASSERT_EQ(addRenderContext->GetForegroundColor(), COLOR);
}

/**
 * @tc.name: CounterLayoutPropertyTest001
 * @tc.desc: test CounterLayoutProperty.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterLayoutPropertyTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    auto layoutProperty = pattern_->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto counterLayoutProperty = AceType::DynamicCast<CounterLayoutProperty>(layoutProperty);
    ASSERT_NE(counterLayoutProperty, nullptr);
    auto clone = counterLayoutProperty->Clone();
    ASSERT_NE(clone, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    counterLayoutProperty->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
    counterLayoutProperty->Reset();
    EXPECT_FALSE(counterLayoutProperty->isVertical_);
}

/**
 * @tc.name: CounterModelNGTest001
 * @tc.desc: test ResetBackgroundColor.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterModelNGTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_EQ(renderContext->GetBackgroundColor().has_value(), false);
    renderContext->UpdateBackgroundColor(COLOR);
    ASSERT_EQ(renderContext->GetBackgroundColor(), COLOR); //
    model.ResetBackgroundColor(Referenced::RawPtr(frameNode_));
    ASSERT_EQ(renderContext->GetBackgroundColor().has_value(), false);
}

/**
 * @tc.name: CounterPatternTest001
 * @tc.desc: test CreateLayoutProperty OnThemeScopeUpdate.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterPatternTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto layoutProperty = pattern_->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_TRUE(pattern_->OnThemeScopeUpdate(host->GetThemeScopeId()));
    renderContext->UpdateForegroundColor(COLOR);
    EXPECT_FALSE(pattern_->OnThemeScopeUpdate(host->GetThemeScopeId()));
}

/**
 * @tc.name: CounterThemeWrapperTest001
 * @tc.desc: test ApplyTokenTheme BuildWrapper.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterThemeWrapperTest001, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterThemeWrapper = CounterThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants);
    EXPECT_NE(counterThemeWrapper, nullptr);
    auto counterTheme = AceType::DynamicCast<CounterTheme>(counterThemeWrapper);
    ASSERT_NE(counterTheme, nullptr);

    std::vector<Color> colors;
    TestProperty testProperty;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (int i = 0; i < TokenColors::TOTAL_NUMBER; i++) {
        colors.push_back(Color(testProperty.colors_[i]));
    }
    auto themeColors = AceType::MakeRefPtr<TokenColors>();
    themeColors->SetColors(std::move(colors));
    testProperty.tokenColors_ = themeColors;
    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(TOKEN_THEME_ID);
    ASSERT_NE(tokenTheme, nullptr);
    EXPECT_NE(counterTheme->GetContentTextStyle().GetTextColor(), colors[TokenColors::FONT_PRIMARY]);
    tokenTheme->SetColors(testProperty.tokenColors_);
    counterThemeWrapper->ApplyTokenTheme(*tokenTheme);
    EXPECT_EQ(counterTheme->GetContentTextStyle().GetTextColor(), colors[TokenColors::FONT_PRIMARY]);
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest001
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::Height.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::Height;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();

    model.CreateWithResourceObj(jsResourceType, resObj);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    ASSERT_NE(counterTheme, nullptr);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Height()->dimension_.Value(), counterTheme->GetHeight().Value());
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest002
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::Width.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest002, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::Width;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();

    model.CreateWithResourceObj(jsResourceType, resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    ASSERT_NE(counterTheme, nullptr);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Width()->dimension_.Value(), counterTheme->GetWidth().Value());
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest003
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::Height.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest003, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::Height;
    std::vector<ResourceObjectParams> resObjParamsList;
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(-1, -1, resObjParamsList, "com.example.test", "entry", 100000);
    model.CreateWithResourceObj(jsResourceType, resObj);

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto frameNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Height()->dimension_.Value(), 0);
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest004
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::Width.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest004, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::Width;
    std::vector<ResourceObjectParams> resObjParamsList;
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(-1, -1, resObjParamsList, "com.example.test", "entry", 100000);
    model.CreateWithResourceObj(jsResourceType, resObj);

    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto frameNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Width()->dimension_.Value(), 0);
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest005
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::BackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest005, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::BackgroundColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();

    model.CreateWithResourceObj(jsResourceType, resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    ASSERT_NE(counterTheme, nullptr);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor().has_value(), false);
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest006
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType::BackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest006, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::BackgroundColor;
    std::vector<ResourceObjectParams> resObjParamsList;
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(-1, -1, resObjParamsList, "com.example.test", "entry", 100000);

    model.CreateWithResourceObj(jsResourceType, resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    ASSERT_NE(counterTheme, nullptr);

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);
    g_isConfigChangePerform = false;
    int32_t colorMode = static_cast<int32_t>(ColorMode::LIGHT);
    pattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor().has_value(), true);

    g_isConfigChangePerform = true;
    colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    EXPECT_EQ(renderContext->GetBackgroundColor().has_value(), true);
}

/**
 * @tc.name: CounterModelNGCreateWithResourceObjTest007
 * @tc.desc: Test CreateWithResourceObj function with JsCounterResourceType error.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateWithResourceObjTest007, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto jsResourceType = static_cast<JsCounterResourceType>(-1);
    model.CreateWithResourceObj(jsResourceType, resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    ASSERT_NE(counterTheme, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor().has_value(), false);
}
} // namespace OHOS::Ace::NG

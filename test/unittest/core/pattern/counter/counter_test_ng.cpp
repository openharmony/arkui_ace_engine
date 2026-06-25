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
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/accessibility/accessibility_manager.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_model_static.h"
#include "core/components_ng/pattern/counter/counter_theme_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

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
HWTEST_F(CounterTestNg, CounterPatternTest002, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest003, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest004, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest005, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest007, TestSize.Level0)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(true);
        model.SetEnableDec(true);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
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
HWTEST_F(CounterTestNg, CounterPatternTest008, TestSize.Level0)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(false);
        model.SetEnableDec(false);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
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
HWTEST_F(CounterTestNg, CounterPatternTest009, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest010, TestSize.Level0)
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
HWTEST_F(CounterTestNg, CounterPatternTest011, TestSize.Level0)
{
    CounterModelNG model;
    model.Create();
    GetInstance();

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
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
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmTestNg001, TestSize.Level0)
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
 * @tc.name: CounterPatternTest001
 * @tc.desc: test CreateLayoutProperty OnThemeScopeUpdate.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterPatternTest001, TestSize.Level0)
{
    // Create counter with original CounterTheme mock
    CounterModelNG model;
    model.Create();
    GetInstance();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto layoutProperty = pattern_->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);

    // Set API version on host node for GreatOrEqualAPITargetVersion check
    host->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);

    // Switch to TextTheme mock for OnThemeScopeUpdate
    auto originalThemeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    auto textTheme = TextTheme::Builder().Build(themeConstants);
    auto textThemeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(textThemeManager);
    EXPECT_CALL(*textThemeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    EXPECT_CALL(*textThemeManager, GetTheme(_, _)).WillRepeatedly(Return(textTheme));

    EXPECT_TRUE(pattern_->OnThemeScopeUpdate(host->GetThemeScopeId()));
    renderContext->UpdateForegroundColor(COLOR);
    renderContext->UpdateForegroundColorFlag(true);
    EXPECT_FALSE(pattern_->OnThemeScopeUpdate(host->GetThemeScopeId()));

    // Restore original themeManager
    MockPipelineContext::GetCurrent()->SetThemeManager(originalThemeManager);
}

/**
 * @tc.name: CounterThemeWrapperTest001
 * @tc.desc: test ApplyTokenTheme BuildWrapper.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterThemeWrapperTest001, TestSize.Level0)
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

/**
 * @tc.name: CounterModelNGSetOnIncTest001
 * @tc.desc: Test SetOnInc function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGSetOnIncTest001, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        bool called = false;
        CounterModel::CounterEventFunc onInc = [&called]() { called = true; };
        model.SetOnInc(std::move(onInc));
    });

    auto counterPattern = frameNode_->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);
    auto addId = counterPattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    ASSERT_NE(addNode, nullptr);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();

    EXPECT_EQ(gestureHub->parallelCombineClick, false);
}

/**
 * @tc.name: CounterModelNGCreateContentNodeChildTest001
 * @tc.desc: Test CreateContentNodeChild function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateContentNodeChildTest001, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterThemeWrapper = CounterThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants);
    EXPECT_NE(counterThemeWrapper, nullptr);
    auto counterTheme = AceType::DynamicCast<CounterTheme>(counterThemeWrapper);
    ASSERT_NE(counterTheme, nullptr);

    int32_t contentId = 2;
    auto contentNode = CounterModelStatic::CreateContentNodeChild(contentId, counterTheme);
    ASSERT_NE(contentNode, nullptr);
    auto layoutProperty = contentNode->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::CENTER);
}

/**
 * @tc.name: CounterModelNGUpdatesHeightForAllChildrenTest001
 * @tc.desc: Test UpdatesHeightForAllChildren function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGUpdatesHeightForAllChildrenTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    CalcLength height(50.0);
    CounterModelStatic::SetHeight(frameNode, height);

    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);

    int32_t subId = counterPattern->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    ASSERT_NE(subNode, nullptr);
    auto subLayoutProperty = subNode->GetLayoutProperty();
    ASSERT_NE(subLayoutProperty, nullptr);

    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetFirstChild());
    ASSERT_NE(subTextNode, nullptr);
    auto subTextLayoutProperty = subTextNode->GetLayoutProperty();
    ASSERT_NE(subTextLayoutProperty, nullptr);

    int32_t addId = counterPattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    ASSERT_NE(addNode, nullptr);
    auto addLayoutProperty = addNode->GetLayoutProperty();
    ASSERT_NE(addLayoutProperty, nullptr);

    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetFirstChild());
    ASSERT_NE(addTextNode, nullptr);
    auto addTextLayoutProperty = addTextNode->GetLayoutProperty();
    ASSERT_NE(addTextLayoutProperty, nullptr);

    int32_t contentId = counterPattern->GetContentId();
    auto contentNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(contentId)));
    ASSERT_NE(contentNode, nullptr);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
}

/**
 * @tc.name: CounterModelNGOnInjectionEventTest001
 * @tc.desc: Test OnInjectionEvent function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGOnInjectionEventTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();

    auto jsResourceType = JsCounterResourceType::BackgroundColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();

    model.CreateWithResourceObj(jsResourceType, resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);
    std::string jsonCommand = R"({"cmd":"setCounterOnInc"})";
    int32_t result = counterPattern->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);

    jsonCommand = R"({"cmd":"setCounterOnDec"})";
    result = counterPattern->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);

    jsonCommand = R"({"cmd":"setCounter"})";
    result = counterPattern->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = R"({")";
    result = counterPattern->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = "";
    result = counterPattern->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: CounterPatternUpdateTextColorTest001
 * @tc.desc: Test UpdateTextColor function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternUpdateTextColorTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    const Color testColor = Color::RED;
    pattern_->UpdateTextColor(textNode, testColor);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->HasTextColor());
    EXPECT_EQ(textLayoutProperty->GetTextColorValue(Color::BLACK), testColor);
}

/**
 * @tc.name: CounterPatternUpdateButtonTextColorTest001
 * @tc.desc: Test UpdateButtonTextColor function
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternUpdateButtonTextColorTest001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    const Color testColor = Color::RED;

    pattern_->UpdateButtonTextColor(frameNode_, pattern_->GetSubId(), testColor);
    auto subNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetSubId())));
    ASSERT_NE(subNode, nullptr);
    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetChildren().front());
    ASSERT_NE(subTextNode, nullptr);
    auto subTextLayoutProperty = subTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(subTextLayoutProperty, nullptr);
    EXPECT_TRUE(subTextLayoutProperty->HasTextColor());
    EXPECT_EQ(subTextLayoutProperty->GetTextColorValue(Color::BLACK), testColor);

    const Color anotherTestColor = Color::BLUE;
    pattern_->UpdateButtonTextColor(frameNode_, pattern_->GetAddId(), anotherTestColor);
    auto addNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetAddId())));
    ASSERT_NE(addNode, nullptr);
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetChildren().front());
    ASSERT_NE(addTextNode, nullptr);
    auto addTextLayoutProperty = addTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(addTextLayoutProperty, nullptr);
    EXPECT_TRUE(addTextLayoutProperty->HasTextColor());
    EXPECT_EQ(addTextLayoutProperty->GetTextColorValue(Color::BLACK), anotherTestColor);
}

/**
 * @tc.name: CounterModelNGCreateCounterModelNGTest001
 * @tc.desc: Test CreateCounterModelNG creates counter with 3 child nodes and correct layout properties
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateCounterModelNGTest001, TestSize.Level1)
{
    CounterModelNG::CreateCounterModelNG();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto counterNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(counterNode, nullptr);

    // Verify 3 child nodes: sub, content, add
    EXPECT_EQ(counterNode->GetChildren().size(), 3);

    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);
    EXPECT_TRUE(counterPattern->HasSubNode());
    EXPECT_TRUE(counterPattern->HasContentNode());
    EXPECT_TRUE(counterPattern->HasAddNode());

    // Verify layout properties
    auto linearLayoutProperty = counterNode->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(linearLayoutProperty, nullptr);
    EXPECT_EQ(linearLayoutProperty->GetMainAxisAlign(), FlexAlign::CENTER);

    auto renderContext = counterNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Verify default size from theme is applied
    auto layoutProperty = counterNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_TRUE(selfIdealSize.has_value());
}

/**
 * @tc.name: CounterModelNGCreateCounterModelNGTest002
 * @tc.desc: Test CreateCounterModelNG sub button has correct text and properties
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateCounterModelNGTest002, TestSize.Level1)
{
    CounterModelNG::CreateCounterModelNG();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto counterNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(counterNode, nullptr);
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);

    auto subId = counterPattern->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(
        counterNode->GetChildAtIndex(counterNode->GetChildIndexById(subId)));
    ASSERT_NE(subNode, nullptr);

    // Sub button has transparent background
    auto subRenderContext = subNode->GetRenderContext();
    ASSERT_NE(subRenderContext, nullptr);
    EXPECT_EQ(subRenderContext->GetBackgroundColor(), Color::TRANSPARENT);

    // Sub button has state effect enabled
    auto buttonEventHub = subNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(buttonEventHub, nullptr);
    EXPECT_TRUE(buttonEventHub->GetStateEffect());

    // Sub button type is NORMAL
    auto buttonLayoutProperty = subNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE), ButtonType::NORMAL);

    // Sub button text is "-"
    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetFirstChild());
    ASSERT_NE(subTextNode, nullptr);
    auto textLayoutProperty = subTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent().value_or(u""), u"-");
    EXPECT_EQ(textLayoutProperty->GetTextAlignValue(TextAlign::START), TextAlign::CENTER);
}

/**
 * @tc.name: CounterModelNGCreateCounterModelNGTest003
 * @tc.desc: Test CreateCounterModelNG add button has correct text and properties
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateCounterModelNGTest003, TestSize.Level1)
{
    CounterModelNG::CreateCounterModelNG();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto counterNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(counterNode, nullptr);
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);

    auto addId = counterPattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(
        counterNode->GetChildAtIndex(counterNode->GetChildIndexById(addId)));
    ASSERT_NE(addNode, nullptr);

    // Add button has transparent background
    auto addRenderContext = addNode->GetRenderContext();
    ASSERT_NE(addRenderContext, nullptr);
    EXPECT_EQ(addRenderContext->GetBackgroundColor(), Color::TRANSPARENT);

    // Add button has state effect enabled
    auto buttonEventHub = addNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(buttonEventHub, nullptr);
    EXPECT_TRUE(buttonEventHub->GetStateEffect());

    // Add button text is "+"
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetFirstChild());
    ASSERT_NE(addTextNode, nullptr);
    auto textLayoutProperty = addTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent().value_or(u""), u"+");
    EXPECT_EQ(textLayoutProperty->GetTextAlignValue(TextAlign::START), TextAlign::CENTER);

    // Text node has transparent background
    auto textRenderContext = addTextNode->GetRenderContext();
    ASSERT_NE(textRenderContext, nullptr);
    EXPECT_EQ(textRenderContext->GetBackgroundColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: CounterModelNGCreateCounterModelNGTest004
 * @tc.desc: Test CreateCounterModelNG content node has correct properties
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateCounterModelNGTest004, TestSize.Level1)
{
    CounterModelNG::CreateCounterModelNG();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto counterNode = AceType::DynamicCast<CounterNode>(element);
    ASSERT_NE(counterNode, nullptr);
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);

    auto contentId = counterPattern->GetContentId();
    auto contentNode = AceType::DynamicCast<FrameNode>(
        counterNode->GetChildAtIndex(counterNode->GetChildIndexById(contentId)));
    ASSERT_NE(contentNode, nullptr);

    // Content node has transparent background
    auto contentRenderContext = contentNode->GetRenderContext();
    ASSERT_NE(contentRenderContext, nullptr);
    EXPECT_EQ(contentRenderContext->GetBackgroundColor(), Color::TRANSPARENT);

    // Content node has main axis alignment CENTER
    auto linearLayoutProperty = contentNode->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(linearLayoutProperty, nullptr);
    EXPECT_EQ(linearLayoutProperty->GetMainAxisAlign(), FlexAlign::CENTER);
}

/**
 * @tc.name: CounterModelNGCreateButtonChildStaticTest001
 * @tc.desc: Test CreateButtonChildStatic with SUB symbol "-"
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateButtonChildStaticTest001, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    ASSERT_NE(counterTheme, nullptr);

    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = CounterModelNG::CreateButtonChildStatic(buttonId, u"-", counterTheme);
    ASSERT_NE(buttonNode, nullptr);

    // Verify button has one text child
    EXPECT_EQ(buttonNode->GetChildren().size(), 1);

    // Verify button properties
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE), ButtonType::NORMAL);
    EXPECT_EQ(buttonLayoutProperty->GetCreateWithLabelValue(true), false);

    // Verify button ideal size from theme
    auto selfIdealSize = buttonNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    ASSERT_TRUE(selfIdealSize.has_value());
    ASSERT_TRUE(selfIdealSize->Width().has_value());
    ASSERT_TRUE(selfIdealSize->Height().has_value());
    EXPECT_EQ(selfIdealSize->Width()->GetDimension().Value(), counterTheme->GetControlWidth().Value());
    EXPECT_EQ(selfIdealSize->Height()->GetDimension().Value(), counterTheme->GetHeight().Value());

    // Verify button state effect
    auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(buttonEventHub, nullptr);
    EXPECT_TRUE(buttonEventHub->GetStateEffect());

    // Verify text child content is "-"
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent().value_or(u""), u"-");
    EXPECT_EQ(textLayoutProperty->GetTextAlignValue(TextAlign::START), TextAlign::CENTER);
}

/**
 * @tc.name: CounterModelNGCreateButtonChildStaticTest002
 * @tc.desc: Test CreateButtonChildStatic with ADD symbol "+"
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateButtonChildStaticTest002, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    ASSERT_NE(counterTheme, nullptr);

    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = CounterModelNG::CreateButtonChildStatic(buttonId, u"+", counterTheme);
    ASSERT_NE(buttonNode, nullptr);

    // Verify text child content is "+"
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent().value_or(u""), u"+");
}

/**
 * @tc.name: CounterModelNGCreateButtonChildStaticTest003
 * @tc.desc: Test CreateButtonChildStatic text node properties
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateButtonChildStaticTest003, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    ASSERT_NE(counterTheme, nullptr);

    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = CounterModelNG::CreateButtonChildStatic(buttonId, u"-", counterTheme);
    ASSERT_NE(buttonNode, nullptr);

    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);

    // Verify text node ideal size from theme
    auto textSelfIdealSize = textNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    ASSERT_TRUE(textSelfIdealSize.has_value());
    ASSERT_TRUE(textSelfIdealSize->Width().has_value());
    ASSERT_TRUE(textSelfIdealSize->Height().has_value());
    EXPECT_EQ(textSelfIdealSize->Width()->GetDimension().Value(), counterTheme->GetControlWidth().Value());
    EXPECT_EQ(textSelfIdealSize->Height()->GetDimension().Value(), counterTheme->GetHeight().Value());
}

/**
 * @tc.name: CounterModelNGCreateButtonChildStaticTest004
 * @tc.desc: Test CreateButtonChildStatic returns existing node when id is registered
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGCreateButtonChildStaticTest004, TestSize.Level1)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    ASSERT_NE(themeConstants, nullptr);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    ASSERT_NE(counterTheme, nullptr);

    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    // First call creates the button node
    auto buttonNode1 = CounterModelNG::CreateButtonChildStatic(buttonId, u"-", counterTheme);
    ASSERT_NE(buttonNode1, nullptr);

    // Second call with same id returns the same button node (GetOrCreateFrameNode)
    auto buttonNode2 = CounterModelNG::CreateButtonChildStatic(buttonId, u"+", counterTheme);
    ASSERT_NE(buttonNode2, nullptr);
    // Same node instance
    EXPECT_EQ(buttonNode1->GetId(), buttonNode2->GetId());
}

/**
 * @tc.name: CounterModelNGSetOnIncTest002
 * @tc.desc: Test SetOnInc with null callback
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGSetOnIncTest002, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        CounterModel::CounterEventFunc nullCallback;
        model.SetOnInc(std::move(nullCallback));
    });

    // Verify add button gesture hub has no user click callback (null callback skipped)
    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    ASSERT_NE(addNode, nullptr);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->clickEventActuator_, nullptr);
}

/**
 * @tc.name: CounterModelNGSetOnIncTest003
 * @tc.desc: Test SetOnInc sets click event and callback is invocable
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGSetOnIncTest003, TestSize.Level1)
{
    bool called = false;
    Create([](CounterModelNG model) {
        // empty callback - will be overridden below
    });

    CounterModelNG model;
    CounterModel::CounterEventFunc onInc = [&called]() { called = true; };
    model.SetOnInc(std::move(onInc));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);
    auto addId = counterPattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    ASSERT_NE(addNode, nullptr);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->parallelCombineClick, false);
    EXPECT_NE(gestureHub->clickEventActuator_, nullptr);
    EXPECT_NE(gestureHub->clickEventActuator_->userCallback_, nullptr);
}

/**
 * @tc.name: CounterModelNGSetOnDecTest001
 * @tc.desc: Test SetOnDec with null callback
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGSetOnDecTest001, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        CounterModel::CounterEventFunc nullCallback;
        model.SetOnDec(std::move(nullCallback));
    });

    // Verify sub button gesture hub has no user click callback (null callback skipped)
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    ASSERT_NE(subNode, nullptr);
    auto gestureHub = subNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->clickEventActuator_, nullptr);
}

/**
 * @tc.name: CounterModelNGSetOnDecTest002
 * @tc.desc: Test SetOnDec sets click event and callback is invocable
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterModelNGSetOnDecTest002, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        // empty callback - will be overridden below
    });

    CounterModelNG model;
    CounterModel::CounterEventFunc onDec = []() {};
    model.SetOnDec(std::move(onDec));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    ASSERT_NE(counterPattern, nullptr);
    auto subId = counterPattern->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    ASSERT_NE(subNode, nullptr);
    auto gestureHub = subNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->parallelCombineClick, false);
    EXPECT_NE(gestureHub->clickEventActuator_, nullptr);
    EXPECT_NE(gestureHub->clickEventActuator_->userCallback_, nullptr);
}

/**
 * @tc.name: CounterLayoutAlgorithmMeasureTest001
 * @tc.desc: Test Measure with width MATCH_PARENT layout policy
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmMeasureTest001, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(300.0_vp);
        model.SetHeight(40.0_vp);
    });

    auto counterLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);

    // Set parent constraint with parentIdealSize
    LayoutConstraintF parentConstraint;
    parentConstraint.parentIdealSize = OptionalSizeF(500.0f, 100.0f);
    parentConstraint.percentReference = SizeF(500.0f, 100.0f);
    parentConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    parentConstraint.minSize = SizeF(0.0f, 0.0f);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(counterLayoutAlgorithm));

    counterLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    // Width should be set from parentIdealSize (MATCH_PARENT)
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 500.0f);
}

/**
 * @tc.name: CounterLayoutAlgorithmMeasureTest002
 * @tc.desc: Test Measure with height MATCH_PARENT layout policy
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmMeasureTest002, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(300.0_vp);
        model.SetHeight(40.0_vp);
    });

    auto counterLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    LayoutConstraintF parentConstraint;
    parentConstraint.parentIdealSize = OptionalSizeF(500.0f, 100.0f);
    parentConstraint.percentReference = SizeF(500.0f, 100.0f);
    parentConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    parentConstraint.minSize = SizeF(0.0f, 0.0f);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(counterLayoutAlgorithm));

    counterLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Height(), 100.0f);
}

/**
 * @tc.name: CounterLayoutAlgorithmMeasureTest003
 * @tc.desc: Test Measure with width FIX_AT_IDEAL_SIZE layout policy
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmMeasureTest003, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(300.0_vp);
        model.SetHeight(40.0_vp);
    });

    auto counterLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    LayoutConstraintF parentConstraint;
    parentConstraint.parentIdealSize = OptionalSizeF(500.0f, 100.0f);
    parentConstraint.percentReference = SizeF(500.0f, 100.0f);
    parentConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    parentConstraint.minSize = SizeF(0.0f, 0.0f);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(counterLayoutAlgorithm));

    counterLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    // Verify layout policy was set correctly
    auto policy = layoutProperty_->GetLayoutPolicyProperty();
    ASSERT_TRUE(policy.has_value());
    EXPECT_TRUE(policy->IsWidthFix());
    EXPECT_TRUE(policy->IsHeightFix());
}

/**
 * @tc.name: CounterLayoutAlgorithmMeasureTest004
 * @tc.desc: Test Measure with width WRAP_CONTENT layout policy
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmMeasureTest004, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(300.0_vp);
        model.SetHeight(40.0_vp);
    });

    auto counterLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);

    LayoutConstraintF parentConstraint;
    parentConstraint.parentIdealSize = OptionalSizeF(500.0f, 100.0f);
    parentConstraint.percentReference = SizeF(500.0f, 100.0f);
    parentConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    parentConstraint.minSize = SizeF(0.0f, 0.0f);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(counterLayoutAlgorithm));

    counterLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    // Verify WRAP_CONTENT policy was set correctly
    auto policy = layoutProperty_->GetLayoutPolicyProperty();
    ASSERT_TRUE(policy.has_value());
    EXPECT_TRUE(policy->IsWidthWrap());
    EXPECT_TRUE(policy->IsHeightWrap());
}

/**
 * @tc.name: CounterLayoutAlgorithmMeasureTest005
 * @tc.desc: Test Measure with width NO_MATCH and height MATCH_PARENT (else + match branch)
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmMeasureTest005, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(300.0_vp);
        model.SetHeight(40.0_vp);
    });

    auto counterLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    // Width NO_MATCH + Height MATCH_PARENT: checkLayoutPolicy=true (height is not NO_MATCH)
    // Width falls into else branch, Height falls into IsHeightMatch branch
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    LayoutConstraintF parentConstraint;
    parentConstraint.parentIdealSize = OptionalSizeF(500.0f, 100.0f);
    parentConstraint.percentReference = SizeF(500.0f, 100.0f);
    parentConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    parentConstraint.minSize = SizeF(0.0f, 0.0f);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(counterLayoutAlgorithm));

    counterLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));

    // Height should be set from parentIdealSize (MATCH_PARENT)
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Height(), 100.0f);
}
} // namespace OHOS::Ace::NG

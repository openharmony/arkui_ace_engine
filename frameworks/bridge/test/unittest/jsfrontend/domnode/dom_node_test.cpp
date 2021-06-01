/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/common/dom/dom_div.h"
#include "frameworks/bridge/common/dom/dom_document.h"
#include "frameworks/bridge/common/dom/dom_text.h"
#include "frameworks/bridge/test/unittest/jsfrontend/dom_node_factory.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {

const double DIV_WIDTH = 200.0;
const double DIV_HEIGHT = 100.0;
const double DIV_PADDING_TOP = 10.0;
const double DIV_PADDING_RIGHT = 30.0;
const double DIV_PADDING_BOTTOM = 70.0;
const double DIV_PADDING_LEFT = 50.0;
const double DIV_MARGIN_TOP = 10.0;
const double DIV_MARGIN_RIGHT = 30.0;
const double DIV_MARGIN_BOTTOM = 70.0;
const double DIV_MARGIN_LEFT = 50.0;
const double DIV_BORDER_TOP_WIDTH = 10.0;
const double DIV_BORDER_RIGHT_WIDTH = 20.0;
const double DIV_BORDER_BOTTOM_WIDTH = 30.0;
const double DIV_BORDER_LEFT_WIDTH = 40.0;
const double DIV_BOX_SHADOW_H = 50.0;
const double DIV_BOX_SHADOW_V = 100.0;
const double DIV_BOX_SHADOW_BLUR = 10.0;
const double DIV_BOX_SHADOW_SPREAD = 20.0;
const std::string DIV_BOX_SHADOW_COLOR = "#ff0000";
const std::string DIV_BORDER_TOP_COLOR = "#759432";
const std::string DIV_BORDER_RIGHT_COLOR = "#521674";
const std::string DIV_BORDER_BOTTOM_COLOR = "#631482";
const std::string DIV_BORDER_LEFT_COLOR = "#264798";
constexpr int32_t DIV_BORDER_STYLE = 2;
const double DIV_BORDER_TOP_LEFT_RADIUS = 10.0;
const double DIV_BORDER_TOP_RIGHT_RADIUS = 20.0;
const double DIV_BORDER_BOTTOM_RIGHT_RADIUS = 30.0;
const double DIV_BORDER_BOTTOM_LEFT_RADIUS = 40.0;
const std::string DIV_BACKGROUND_COLOR = "#759432";
const std::string DIV_BACKGROUND_IMAGE_SRC = "picture/test2.jpg";
const double DIV_BACKGROUND_IMAGE_SIZE = 200.0;
const double DIV_BACKGROUND_IMAGE_POSITION_VALUE_X = 100.0;
const double DIV_BACKGROUND_IMAGE_POSITION_VALUE_Y = 200.0;
constexpr int32_t DIV_BACKGROUND_IMAGE_POSITION_TYPE_X = 1;
constexpr int32_t DIV_BACKGROUND_IMAGE_POSITION_TYPE_Y = 1;
constexpr int32_t DIV_BACKGROUND_IMAGE_REPEAT = 1;
const std::string JSON_DIV_TEST_004 = ""
                                   "{                                          "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                    "
                                   "        \"borderTopWidth\": \"10px\"       "
                                   "    },"
                                   "    {"
                                   "        \"borderRightWidth\": \"20px\"     "
                                   "    },"
                                   "    {"
                                   "        \"borderBottomWidth\": \"30px\"    "
                                   "    },"
                                   "    {"
                                   "        \"borderLeftWidth\": \"40px\"      "
                                   "    },"
                                   "    {"
                                   "        \"borderStyle\": \"dotted\"         "
                                   "    },"
                                   "    {"
                                   "        \"borderTopColor\": \"#759432\"      "
                                   "    },"
                                   "    {"
                                   "        \"borderRightColor\": \"#521674\"    "
                                   "    },"
                                   "    {"
                                   "        \"borderBottomColor\": \"#631482\"   "
                                   "    },"
                                   "    {"
                                   "        \"borderLeftColor\": \"#264798\"     "
                                   "    }]"
                                   "}";

} // namespace

class DomNodeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void DomNodeTest::SetUpTestCase() {}
void DomNodeTest::TearDownTestCase() {}
void DomNodeTest::SetUp() {}
void DomNodeTest::TearDown() {}

/**
 * @tc.name: DomNodeTest001
 * @tc.desc: Verify that DomNode can be set width and height.
 * @tc.type: FUNC
 * @tc.require: SR000DD67J
 * @tc.author: wuhaibin
 */
HWTEST_F(DomNodeTest, DomNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with two attributes:
     * width, height.
     */
    const std::string jsonDivStr = ""
                                   "{                               "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{          "
                                   "        \"width\": \"200px\" "
                                   "    },"
                                   "    {"
                                   "       \"height\": \"100px\"    "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its commonStyle.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    double width = boxChildComponent->GetWidthDimension().Value();
    double height = boxChildComponent->GetHeightDimension().Value();

    /**
     * @tc.steps: step3. Verify the DomNode's commonStyle is set correctly.
     * @tc.expected: step3. width is 200.0, height is 100.0
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_TRUE(width == DIV_WIDTH);
    EXPECT_TRUE(height == DIV_HEIGHT);
}

/**
 * @tc.name: DomNodeTest002
 * @tc.desc: Verify that DomNode can be set padding .
 * @tc.type: FUNC
 * @tc.require: SR000DD67J
 * @tc.author: wuhaibin
 */
HWTEST_F(DomNodeTest, DomNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with four attributes:
     * padding-top, padding-right, padding-bottom, padding-left.
     */
    const std::string jsonDivStr = ""
                                   "{                               "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                             "
                                   "        \"paddingTop\": \"10px\" "
                                   "    },"
                                   "    {"
                                   "        \"paddingRight\": \"30px\"    "
                                   "    },"
                                   "    {"
                                   "        \"paddingBottom\": \"70px\"    "
                                   "    },"
                                   "    {"
                                   "        \"paddingLeft\": \"50px\" "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its commonStyle.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    double top = static_cast<double>(boxChildComponent->GetPadding().Top().Value());
    double right = static_cast<double>(boxChildComponent->GetPadding().Right().Value());
    double bottom = static_cast<double>(boxChildComponent->GetPadding().Bottom().Value());
    double left = static_cast<double>(boxChildComponent->GetPadding().Left().Value());

    /**
     * @tc.steps: step3. Verify the DomNode's commonStyle is set correctly.
     * @tc.expected: step3. padding-top is 10, padding-right is 10, padding-bottom is 10, padding-left is 10,
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_TRUE(top == DIV_PADDING_TOP);
    EXPECT_TRUE(right == DIV_PADDING_RIGHT);
    EXPECT_TRUE(bottom == DIV_PADDING_BOTTOM);
    EXPECT_TRUE(left == DIV_PADDING_LEFT);
}

/**
 * @tc.name: DomNodeTest003
 * @tc.desc: Verify that DomNode can be set margin .
 * @tc.type: FUNC
 * @tc.require: SR000DD67J
 * @tc.author: wuhaibin
 */
HWTEST_F(DomNodeTest, DomNodeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with four attributes:
     * margin-top, margin-right, margin-bottom, margin-left.
     */
    const std::string jsonDivStr = ""
                                   "{                               "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                             "
                                   "        \"marginTop\": \"10px\" "
                                   "    },"
                                   "    {"
                                   "        \"marginRight\": \"30px\"    "
                                   "    },"
                                   "    {"
                                   "        \"marginBottom\": \"70px\"    "
                                   "    },"
                                   "    {"
                                   "        \"marginLeft\": \"50px\" "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its commonStyle.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    double top = static_cast<double>(boxChildComponent->GetMargin().Top().Value());
    double right = static_cast<double>(boxChildComponent->GetMargin().Right().Value());
    double bottom = static_cast<double>(boxChildComponent->GetMargin().Bottom().Value());
    double left = static_cast<double>(boxChildComponent->GetMargin().Left().Value());

    /**
     * @tc.steps: step3. Verify the DomNode's commonStyle is set correctly.
     * @tc.expected: step3. margin-top is 10, margin-right is 10, margin-bottom is 10, margin-left is 10,
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_TRUE(top == DIV_MARGIN_TOP);
    EXPECT_TRUE(right == DIV_MARGIN_RIGHT);
    EXPECT_TRUE(bottom == DIV_MARGIN_BOTTOM);
    EXPECT_TRUE(left == DIV_MARGIN_LEFT);
}

/**
 * @tc.name: DomNodeTest004
 * @tc.desc: Verify that DomNode can be set border.
 * @tc.type: FUNC
 * @tc.require: SR000DD67O
 * @tc.author: liwenzhen
 */
HWTEST_F(DomNodeTest, DomNodeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with border-related attributes:
     * borderTopWidth, borderRightWidth, borderBottomWidth, borderLeftWidth, borderStyle,
     * borderTopColor, borderRightColor, borderBottomColor, borderLeftColor.
     */
    const std::string& jsonDivStr = JSON_DIV_TEST_004;
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its border-related common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    Border border = boxChildComponent->GetBackDecoration()->GetBorder();
    BorderEdge borderTopEdge = border.Top();
    BorderEdge borderRightEdge = border.Right();
    BorderEdge borderBottomEdge = border.Bottom();
    BorderEdge borderLeftEdge = border.Left();

    /**
     * @tc.steps: step3. Verify the DomNode's bordrt-related common styles can be set correctly.
     * @tc.expected: step3. borderTopWidth is 10px, borderRightWidth is 20px, borderBottomWidth is 30px,
     * borderLeftWidth is 40px, borderStyle is dotted, borderTopColor is #759432, borderRightColor is #521674,
     * borderBottomColor is #631482, borderLeftColor is #264798.
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_EQ(borderTopEdge.GetWidth().Value(), DIV_BORDER_TOP_WIDTH);
    EXPECT_EQ(borderRightEdge.GetWidth().Value(), DIV_BORDER_RIGHT_WIDTH);
    EXPECT_EQ(borderBottomEdge.GetWidth().Value(), DIV_BORDER_BOTTOM_WIDTH);
    EXPECT_EQ(borderLeftEdge.GetWidth().Value(), DIV_BORDER_LEFT_WIDTH);
    EXPECT_EQ(borderTopEdge.GetColor(), Color::FromString(DIV_BORDER_TOP_COLOR));
    EXPECT_EQ(borderRightEdge.GetColor(), Color::FromString(DIV_BORDER_RIGHT_COLOR));
    EXPECT_EQ(borderBottomEdge.GetColor(), Color::FromString(DIV_BORDER_BOTTOM_COLOR));
    EXPECT_EQ(borderLeftEdge.GetColor(), Color::FromString(DIV_BORDER_LEFT_COLOR));
    EXPECT_EQ(static_cast<int32_t>(borderTopEdge.GetBorderStyle()), DIV_BORDER_STYLE);
    EXPECT_EQ(static_cast<int32_t>(borderRightEdge.GetBorderStyle()), DIV_BORDER_STYLE);
    EXPECT_EQ(static_cast<int32_t>(borderBottomEdge.GetBorderStyle()), DIV_BORDER_STYLE);
    EXPECT_EQ(static_cast<int32_t>(borderLeftEdge.GetBorderStyle()), DIV_BORDER_STYLE);
}

/**
 * @tc.name: DomNodeTest005
 * @tc.desc: Verify that DomNode can be set border radius.
 * @tc.type: FUNC
 * @tc.require: SR000DD67O
 * @tc.author: liwenzhen
 */
HWTEST_F(DomNodeTest, DomNodeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with border radius attributes:
     * borderTopLeftRadius, borderTopRightRadius, borderBottomRightRadius, borderBottomLeftRadius.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"borderTopLeftRadius\": \"10px\"         "
                                   "    },"
                                   "    {"
                                   "        \"borderTopRightRadius\": \"20px\"        "
                                   "    },"
                                   "    {"
                                   "        \"borderBottomRightRadius\": \"30px\"     "
                                   "    },"
                                   "    {"
                                   "        \"borderBottomLeftRadius\": \"40px\"      "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its border radius common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    Border border = boxChildComponent->GetBackDecoration()->GetBorder();

    /**
     * @tc.steps: step3. Verify the DomNode's bordrt radius common styles can be set correctly.
     * @tc.expected: step3. borderTopLeftRadius is 10px, borderTopRightRadius is 20px,
     * borderBottomRightRadius is 30px, borderBottomLeftRadius is 40px.
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_EQ(border.TopLeftRadius(), Radius(DIV_BORDER_TOP_LEFT_RADIUS));
    EXPECT_EQ(border.TopRightRadius(), Radius(DIV_BORDER_TOP_RIGHT_RADIUS));
    EXPECT_EQ(border.BottomRightRadius(), Radius(DIV_BORDER_BOTTOM_RIGHT_RADIUS));
    EXPECT_EQ(border.BottomLeftRadius(), Radius(DIV_BORDER_BOTTOM_LEFT_RADIUS));
}

/**
 * @tc.name: DomNodeTest006
 * @tc.desc: Verify that DomNode can be set background.
 * @tc.type: FUNC
 * @tc.require: SR000DD67U
 * @tc.author: liwenzhen
 */
HWTEST_F(DomNodeTest, DomNodeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with background-related attributes:
     * backgroundColor, backgroundImage, backgroundSize, backgroundPosition, backgroundRepeat.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"backgroundColor\": \"#759432\"         "
                                   "    },"
                                   "    {"
                                   "        \"backgroundImage\": \"picture/test2.jpg\"        "
                                   "    },"
                                   "    {"
                                   "        \"backgroundSize\": \"200px\"     "
                                   "    },"
                                   "    {"
                                   "        \"backgroundPosition\": \"100px 200px\"      "
                                   "    },"
                                   "    {"
                                   "        \"backgroundRepeat\": \"repeat-x\"      "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its background-related common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    RefPtr<Decoration> decoration = boxChildComponent->GetBackDecoration();
    RefPtr<BackgroundImage> image = decoration->GetImage();
    BackgroundImagePosition backgroundImagePosition = image->GetImagePosition();

    /**
     * @tc.steps: step3. Verify the DomNode's background-related common styles can be set correctly.
     * @tc.expected: step3. backgroundColor is #759432, backgroundImage's src is picture/test2.jpg,
     * backgroundSize is 200px, backgroundPositionValue is 100px 200px, backgroundPositiontype is px,
     * backgroundRepeat is repeat-x.
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_EQ(decoration->GetBackgroundColor(), Color::FromString(DIV_BORDER_TOP_COLOR));
    EXPECT_EQ(image->GetSrc(), DIV_BACKGROUND_IMAGE_SRC);
    EXPECT_EQ(image->GetImageSize().GetSizeValueX(), DIV_BACKGROUND_IMAGE_SIZE);
    EXPECT_EQ(backgroundImagePosition.GetSizeValueX(), DIV_BACKGROUND_IMAGE_POSITION_VALUE_X);
    EXPECT_EQ(backgroundImagePosition.GetSizeValueY(), DIV_BACKGROUND_IMAGE_POSITION_VALUE_Y);
    EXPECT_EQ(static_cast<int32_t>(backgroundImagePosition.GetSizeTypeX()), DIV_BACKGROUND_IMAGE_POSITION_TYPE_X);
    EXPECT_EQ(static_cast<int32_t>(backgroundImagePosition.GetSizeTypeY()), DIV_BACKGROUND_IMAGE_POSITION_TYPE_Y);
    EXPECT_EQ(static_cast<int32_t>(image->GetImageRepeat()), DIV_BACKGROUND_IMAGE_REPEAT);
}

/**
 * @tc.name: DomNodeTest007
 * @tc.desc: Verify that DomNode can be set minWidth/minHeight/maxWidth/maxHeight.
 * @tc.type: FUNC
 * @tc.require: AR000F3BAI AR000F3BAQ
 * @tc.author: yangfan
 */
HWTEST_F(DomNodeTest, DomNodeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * flexWeight.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"flexWeight\": \"1\"                     "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its border radius common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto weight = domNodeRoot->GetFlexWeight();

    /**
     * @tc.steps: step3. Verify the DomNode's bordrt radius common styles can be set correctly.
     * @tc.expected: step3. flexWeight is 1.
     */
    EXPECT_EQ(weight, 1);
}

/**
 * @tc.name: BoxShadowTest001
 * @tc.desc: Verify that DomNode can be set box shadow.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDQ
 * @tc.author: jiangdayuan
 */
HWTEST_F(DomNodeTest, BoxShadowTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with box shadow offset attributes.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"boxShadowH\": \"50px\"         "
                                   "    },"
                                   "    {"
                                   "        \"boxShadowV\": \"100px\"        "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its box shadow common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    RefPtr<Decoration> decoration = boxChildComponent->GetBackDecoration();
    auto shadow = decoration->GetShadows().front();

    /**
     * @tc.steps: step3. Verify the DomNode's box shadow common styles can be set correctly.
     * @tc.expected: step3. boxShadowH is 50px, boxShadowV is 100px
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_EQ(shadow.GetOffset().GetX(), DIV_BOX_SHADOW_H);
    EXPECT_EQ(shadow.GetOffset().GetY(), DIV_BOX_SHADOW_V);
}

/**
 * @tc.name: BoxShadowTest002
 * @tc.desc: Verify that DomNode can be set box shadow.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDQ
 * @tc.author: jiangdayuan
 */
HWTEST_F(DomNodeTest, BoxShadowTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with box shadow  attributes.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"boxShadowH\": \"50px\"         "
                                   "    },"
                                   "    {"
                                   "        \"boxShadowV\": \"100px\"        "
                                   "    },"
                                   "    {"
                                   "        \"boxShadowBlur\": \"10px\"        "
                                   "    },"
                                   "    {"
                                   "        \"boxShadowSpread\": \"20px\"        "
                                   "    },"
                                   "    {"
                                   "        \"boxShadowColor\": \"#ff0000\"        "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its box shadow common style.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    auto boxChildComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    RefPtr<Decoration> decoration = boxChildComponent->GetBackDecoration();
    auto shadow = decoration->GetShadows().front();

    /**
     * @tc.steps: step3. Verify the DomNode's box shadow common styles can be set correctly.
     * @tc.expected: step3. boxShadowH is 50px, boxShadowV is 100px, boxShadowSpread is 20px, boxShadowBlur is 10px
     */
    ASSERT_TRUE(domNodeRoot != nullptr);
    EXPECT_EQ(shadow.GetOffset().GetX(), DIV_BOX_SHADOW_H);
    EXPECT_EQ(shadow.GetOffset().GetY(), DIV_BOX_SHADOW_V);
    EXPECT_EQ(shadow.GetSpreadRadius(), DIV_BOX_SHADOW_SPREAD);
    EXPECT_EQ(shadow.GetBlurRadius(), DIV_BOX_SHADOW_BLUR);
    EXPECT_EQ(shadow.GetColor(), Color::FromString(DIV_BOX_SHADOW_COLOR));
}

/*
 * @tc.name: ClickEffectTest001
 * @tc.desc: Verify that DomNode can be set click-effect.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDD AR000F3CDE AR000F3CDF
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, ClickEffectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * click-effect.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"attr\": [{                           "
                                   "        \"clickEffect\": \"spring-small\"        "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its click-effect.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto transformComponent = domNodeRoot->GetTransformComponent();
    ASSERT_TRUE(transformComponent != nullptr);
    auto effectType = transformComponent->GetClickSpringEffectType();
    /**
     * @tc.steps: step3. Verify the DomNode's click-effect attr can be set correctly.
     * @tc.expected: step3. effectType is SMALL.
     */
    EXPECT_EQ(effectType, ClickSpringEffectType::SMALL);
}

/*
 * @tc.name: ClickEffectTest002
 * @tc.desc: Verify that DomNode can be set click-effect.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDD AR000F3CDE AR000F3CDF
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, ClickEffectTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * click-effect.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"attr\": [{                           "
                                   "        \"clickEffect\": \"spring-medium\"        "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its click-effect with spring-medium.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto transformComponent = domNodeRoot->GetTransformComponent();
    ASSERT_TRUE(transformComponent != nullptr);
    auto effectType = transformComponent->GetClickSpringEffectType();
    /**
     * @tc.steps: step3. Verify the DomNode's click-effect attr can be set correctly.
     * @tc.expected: step3. effectType is MEDIUM.
     */
    EXPECT_EQ(effectType, ClickSpringEffectType::MEDIUM);
}

/*
 * @tc.name: ClickEffectTest003
 * @tc.desc: Verify that DomNode can be set click-effect.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDD AR000F3CDE AR000F3CDF
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, ClickEffectTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * click-effect.
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"attr\": [{                           "
                                   "        \"clickEffect\": \"spring-large\"        "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its click-effect.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto transformComponent = domNodeRoot->GetTransformComponent();
    ASSERT_TRUE(transformComponent != nullptr);
    auto effectType = transformComponent->GetClickSpringEffectType();
    /**
     * @tc.steps: step3. Verify the DomNode's click-effect attr can be set correctly.
     * @tc.expected: step3. effectType is LARGE.
     */
    EXPECT_EQ(effectType, ClickSpringEffectType::LARGE);
}

/*
 * @tc.name: BoxBlurTest001
 * @tc.desc: Verify that DomNode can be set filter and backdrop-filter.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDU
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, BoxBlurTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * click-effect.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"filter\": \"blur(20px)\""
                                   "        },"
                                   "        {"
                                   "            \"backdropFilter\": \"blur(31px)\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its click-effect.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto boxComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    ASSERT_TRUE(boxComponent != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's filter common styles can be set correctly.
     * @tc.expected: step3. blurRadius is 20.
     */
    auto frontDecoration = boxComponent->GetFrontDecoration();
    ASSERT_TRUE(frontDecoration != nullptr);
    EXPECT_EQ(frontDecoration->GetBlurRadius().Value(), 20.0);

    /**
     * @tc.steps: step3. Verify the DomNode's backdrop-filter common styles can be set correctly.
     * @tc.expected: step3. blurRadius is 31.
     */
    auto backDecoration = boxComponent->GetBackDecoration();
    ASSERT_TRUE(backDecoration != nullptr);
    EXPECT_EQ(backDecoration->GetBlurRadius().Value(), 31.0);
}

/*
 * @tc.name: DomeNodeTransitionAnimatioOpitionTest001
 * @tc.desc: Verify that DomNode can be set transition-effect.
 * @tc.type: FUNC
 * @tc.require: AR000F3CA9
 * @tc.author: chenlien
 */
HWTEST_F(DomNodeTest, DomeNodeTransitionAnimatioOpitionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes: transition-effect
     */
    const std::string jsonDivStr = ""
                                   "{                                                 "
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": [{                           "
                                   "        \"transitionEffect\": \"unfold\" "
                                   "    }]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set transition-effect.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto transformComponent = domNodeRoot->GetTransformComponent();
    ASSERT_TRUE(transformComponent != nullptr);
    auto transitionEffect = transformComponent->GetTransitionEffect();
    /**
     * @tc.steps: step3. Verify the DomNode's transition-effect common styles can be set correctly.
     * @tc.expected: step3. effectType is UNFOLD.
     */
    EXPECT_EQ(transitionEffect, TransitionEffect::UNFOLD);
}

/*
 * @tc.name: WindowBlurTest001
 * @tc.desc: Verify that DomNode can be set window-filter.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, WindowBlurTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"windowFilter\": \"blur(50%)\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its window-filter.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto boxComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    ASSERT_TRUE(boxComponent != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's window-filter common styles can be set correctly.
     * @tc.expected: step3. window blur progress is 0.5.
     */
    auto backDecoration = boxComponent->GetBackDecoration();
    ASSERT_TRUE(backDecoration != nullptr);
    EXPECT_EQ(backDecoration->GetWindowBlurProgress(), 0.5f);
}

/*
 * @tc.name: WindowBlurTest002
 * @tc.desc: Verify that DomNode can not be set window-filter invalid value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, WindowBlurTest002, TestSize.Level1) {
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"windowFilter\": \"blur(150%)\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its window-filter.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto boxComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    ASSERT_TRUE(boxComponent != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's window-filter common styles can not be set correctly.
     * @tc.expected: step3. window blur progress is 0.0.
     */
    auto backDecoration = boxComponent->GetBackDecoration();
    ASSERT_TRUE(backDecoration != nullptr);
    EXPECT_EQ(backDecoration->GetWindowBlurProgress(), 0.0f);
}

/*
 * @tc.name: WindowBlurTest003
 * @tc.desc: Verify that DomNode can set window-filter boundary value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, WindowBlurTest003, TestSize.Level1) {
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"windowFilter\": \"blur(100%)\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its window-filter.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto boxComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    ASSERT_TRUE(boxComponent != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's window-filter common styles can be set correctly.
     * @tc.expected: step3. window blur progress is 1.0.
     */
    auto backDecoration = boxComponent->GetBackDecoration();
    ASSERT_TRUE(backDecoration != nullptr);
    EXPECT_EQ(backDecoration->GetWindowBlurProgress(), 1.0f);
}

/*
 * @tc.name: WindowBlurTest004
 * @tc.desc: Verify that DomNode can not be set window-filter with different unit.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, WindowBlurTest004, TestSize.Level1) {
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"windowFilter\": \"blur(1px)\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its window-filter.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);
    auto boxComponent = DOMNodeFactory::GetInstance().GetBoxChildComponent(domNodeRoot);
    ASSERT_TRUE(boxComponent != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's window-filter common styles can not be set correctly.
     * @tc.expected: step3. window blur progress is 0.0.
     */
    auto backDecoration = boxComponent->GetBackDecoration();
    ASSERT_TRUE(backDecoration != nullptr);
    EXPECT_EQ(backDecoration->GetWindowBlurProgress(), 0.0f);
}

/*
 * @tc.name: TransformOriginTest001
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"center\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 50% 50%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.5);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 0.5);
}

/*
 * @tc.name: TransformOriginTest002
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"left\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 0% 50%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.0);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 0.5);
}

/*
 * @tc.name: TransformOriginTest003
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"bottom\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 50% 100%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.5);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 1.0);
}

/*
 * @tc.name: TransformOriginTest004
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"top\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 50% 0%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.5);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 0.0);
}

/*
 * @tc.name: TransformOriginTest005
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"bottom\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 50% 100%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.5);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 1.0);
}

/*
 * @tc.name: TransformOriginTest006
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"40px\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 40px 50%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PX);
    ASSERT_EQ(originOffsetX.Value(), 40);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 0.5);
}

/*
 * @tc.name: TransformOriginTest007
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"30%\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 30% 50%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.3);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 0.5);
}

/*
 * @tc.name: TransformOriginTest008
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"0% 0px\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 0% 0px
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.0);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PX);
    ASSERT_EQ(originOffsetY.Value(), 0.0);
}

/*
 * @tc.name: TransformOriginTest009
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"left 30px\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 0% 30px
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.0);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PX);
    ASSERT_EQ(originOffsetY.Value(), 30);
}

/*
 * @tc.name: TransformOriginTest010
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"left bottom\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 0% 100%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.0);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 1.0);
}

/*
 * @tc.name: TransformOriginTest011
 * @tc.desc: Verify that DomNode can set transform-origin with one value.
 * @tc.type: FUNC
 * @tc.require: AR000F3CDV
 * @tc.author: jiangtao
 */
HWTEST_F(DomNodeTest, TransformOriginTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the json string of DomNode with constraint attributes:
     * windowFilter.
     */
    const std::string jsonDivStr = "{"
                                   "    \"tag\": \"div\","
                                   "    \"commonStyle\": ["
                                   "        {"
                                   "            \"transformOrigin\": \"bottom bottom\""
                                   "        }"
                                   "    ]"
                                   "}";
    /**
     * @tc.steps: step2. call JsonUtil interface, create DomNode and set its transform-origin.
     */
    auto domNodeRoot = DOMNodeFactory::GetInstance().CreateDOMNodeFromDsl(jsonDivStr);
    ASSERT_TRUE(domNodeRoot != nullptr);

    /**
     * @tc.steps: step3. Verify the DomNode's transform-origin common styles can be set correctly.
     * @tc.expected: step3. 50% 100%
     */
    auto originOffsetX = domNodeRoot->GetTweenOption().GetTransformOriginX();
    auto originOffsetY = domNodeRoot->GetTweenOption().GetTransformOriginY();
    ASSERT_TRUE(originOffsetX.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetX.Value(), 0.5);
    ASSERT_TRUE(originOffsetY.Unit() == DimensionUnit::PERCENT);
    ASSERT_EQ(originOffsetY.Value(), 1.0);
}

} // namespace OHOS::Ace::Framework

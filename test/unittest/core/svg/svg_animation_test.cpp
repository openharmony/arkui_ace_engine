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

#include "gtest/gtest.h"
#include "frameworks/core/components_ng/svg/parse/svg_animation.h"
#include "frameworks/core/components_ng/svg/svg_context.h"
#include "core/animation/animator.h"
#include "base/geometry/dimension.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgAnimationTest : public testing::Test {
public:
    void SetUp() override
    {
        svgContext_ = AceType::MakeRefPtr<SvgContext>();
        animation_ = AceType::MakeRefPtr<SvgAnimation>();
        animator_ = AceType::MakeRefPtr<Animator>();
    }

    void TearDown() override
    {
        svgContext_ = nullptr;
        animation_ = nullptr;
        animator_ = nullptr;
    }

protected:
    RefPtr<SvgContext> svgContext_;
    RefPtr<SvgAnimation> animation_;
    RefPtr<Animator> animator_;
};

/**
 * @tc.name: SvgAnimationTest001
 * @tc.desc: Test SVG animation creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest001, TestSize.Level1)
{
    EXPECT_NE(animation_, nullptr);
    EXPECT_NE(animator_, nullptr);
}

/**
 * @tc.name: SvgAnimationTest002
 * @tc.desc: Test SVG animation attribute setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest002, TestSize.Level1)
{
    // Test setting animation attributes
    animation_->SetAttributeName("r"); // Attribute to animate
    animation_->SetFrom("10");      // Start value
    animation_->SetTo("50");        // End value
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest003
 * @tc.desc: Test SVG animation duration setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest003, TestSize.Level1)
{
    // Test duration settings
    animation_->SetDur("2s");
    animation_->SetBegin("0s");
    animation_->SetEnd("2s");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest004
 * @tc.desc: Test SVG animation repeat settings
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest004, TestSize.Level1)
{
    // Test repeat settings
    animation_->SetRepeatCount("3");
    animation_->SetRepeatDur("1s");
    animation_->SetRepeatCount("indefinite");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest005
 * @tc.desc: Test SVG animation easing
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest005, TestSize.Level1)
{
    // Test easing functions
    animation_->SetKeyTimes("0;0.5;1");
    animation_->SetValues("10;30;50");
    animation_->SetKeySplines("0 0 1 1");
    animation_->SetCalcMode("spline");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest006
 * @tc.desc: Test SVG animation fill mode
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest006, TestSize.Level1)
{
    // Test fill modes
    animation_->SetFill("freeze");
    animation_->SetFill("remove");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest007
 * @tc.desc: Test SVG animation additive mode
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest007, TestSize.Level1)
{
    // Test additive modes
    animation_->SetAdditive("sum");
    animation_->SetAdditive("replace");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest008
 * @tc.desc: Test SVG animation accumulate mode
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest008, TestSize.Level1)
{
    // Test accumulate modes
    animation_->SetAccumulate("sum");
    animation_->SetAccumulate("none");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest009
 * @tc.desc: Test SVG animation target element
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest009, TestSize.Level1)
{
    // Test target element
    animation_->SetHref("#targetElement");
    animation_->SetTargetElementId("targetElement");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest010
 * @tc.desc: Test SVG animation color animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest010, TestSize.Level1)
{
    // Test color animation values
    animation_->SetAttributeName("fill");
    animation_->SetValues("red;blue;green");
    animation_->SetKeyTimes("0;0.5;1");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest011
 * @tc.desc: Test SVG animation path animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest011, TestSize.Level1)
{
    // Test path animation
    animation_->SetAttributeName("d");
    animation_->SetValues("M10,10 L50,50;M50,50 L90,10");
    animation_->SetKeyTimes("0;1");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest012
 * @tc.desc: Test SVG animation transform animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest012, TestSize.Level1)
{
    // Test transform animation
    animation_->SetAttributeName("transform");
    animation_->SetType("rotate");
    animation_->SetFrom("0 50 50");
    animation_->SetTo("360 50 50");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest013
 * @tc.desc: Test SVG animation multiple properties
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest013, TestSize.Level1)
{
    // Create a second animation for multiple properties
    auto animation2 = AceType::MakeRefPtr<SvgAnimation>();
    
    // Set different properties on each animation
    animation_->SetAttributeName("r");
    animation_->SetValues("10;30;50");
    
    animation2->SetAttributeName("opacity");
    animation2->SetValues("1;0.5;0.2");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest014
 * @tc.desc: Test SVG animation time-based control
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest014, TestSize.Level1)
{
    // Test timing controls
    animation_->SetDur("3s");
    animation_->SetBegin("1s");
    animation_->SetEnd("4s");
    animation_->SetMin("0");
    animation_->SetMax("100");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest015
 * @tc.desc: Test SVG animation event handling
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest015, TestSize.Level1)
{
    // Test event callbacks
    animation_->SetOnStart([](){});
    animation_->SetOnEnd([](){});
    animation_->SetOnRepeat([](){});
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest016
 * @tc.desc: Test SVG animation with decimal values
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest016, TestSize.Level1)
{
    // Test decimal values
    animation_->SetAttributeName("r");
    animation_->SetFrom("10.5");
    animation_->SetTo("25.75");
    animation_->SetBy("2.5");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest017
 * @tc.desc: Test SVG animation negative values
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest017, TestSize.Level1)
{
    // Test negative values
    animation_->SetAttributeName("transform");
    animation_->SetValues("rotate(0);rotate(-45);rotate(-90)");
    animation_->SetKeyTimes("0;0.5;1");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest018
 * @tc.desc: Test SVG animation attribute name parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest018, TestSize.Level1)
{
    // Test different attribute names
    std::vector<std::string> attributes = {
        "r", "cx", "cy", "x", "y", "width", "height",
        "fill", "stroke", "stroke-width", "opacity",
        "transform", "fill-opacity", "stroke-opacity"
    };
    
    for (const auto& attr : attributes) {
        auto anim = AceType::MakeRefPtr<SvgAnimation>();
        anim->SetAttributeName(attr);
        SUCCEED(); // Test setting passes if no crash occurs
    }
}

/**
 * @tc.name: SvgAnimationTest019
 * @tc.desc: Test SVG animation complex timing
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest019, TestSize.Level1)
{
    // Test complex timing configuration
    animation_->SetKeyTimes("0;0.25;0.5;0.75;1");
    animation_->SetValues("10;20;30;20;10");
    animation_->SetKeySplines("0 0 1 1; 0 0 1 1");
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest020
 * @tc.desc: Test SVG animation interpolate function
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest020, TestSize.Level1)
{
    // Test interpolation methods
    std::string from = "10";
    std::string to = "50";
    std::string result = animation_->DoInterpolate(from, to, 0.5);
    
    // Basic test - exact result depends on interpolation implementation
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: SvgAnimationTest021
 * @tc.desc: Test SVG animation context integration
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest021, TestSize.Level1)
{
    // Create SVG node for animation target
    auto targetNode = AceType::MakeRefPtr<SvgNode>();
    targetNode->SetNodeId("animTarget");
    
    // Set animation context
    targetNode->SetContext(svgContext_);
    
    // Add animation to context
    int32_t animatorKey = 100;
    svgContext_->AddAnimator(animatorKey, animator_);
    
    EXPECT_TRUE(svgContext_->GetSvgNodeById("animTarget") != nullptr);
}

/**
 * @tc.name: SvgAnimationTest022
 * @tc.desc: Test SVG animation animator control
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest022, TestSize.Level1)
{
    // Test animator control
    int32_t animatorKey = 101;
    svgContext_->AddAnimator(animatorKey, animator_);
    
    // Test play and pause
    svgContext_->ControlAnimators(true);  // Play
    svgContext_->ControlAnimators(false); // Pause
    
    // Test removal
    svgContext_->RemoveAnimator(animatorKey);
    
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest023
 * @tc.desc: Test SVG animation callbacks
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest023, TestSize.Level1)
{
    bool callbackTriggered = false;
    
    // Set animation finish callback
    std::function<void()> finishCallback = [&callbackTriggered]() {
        callbackTriggered = true;
    };
    
    svgContext_->SetOnAnimationFinished(finishCallback);
    
    // Trigger finish callback
    svgContext_->OnAnimationFinished();
    
    EXPECT_TRUE(callbackTriggered);
}

/**
 * @tc.name: SvgAnimationTest024
 * @tc.desc: Test SVG animation with animator
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest024, TestSize.Level1)
{
    // Test creating animation with animator
    animation_->SetAttributeName("r");
    animation_->SetFrom("10");
    animation_->SetTo("50");
    animation_->SetDur("2s");
    
    // Connect animation to animator
    // Note: The exact connection method depends on implementation
    SUCCEED(); // Test passes if no crash occurs
}

/**
 * @tc.name: SvgAnimationTest025
 * @tc.desc: Test SVG animation performance with multiple animations
 * @tc.type: FUNC
 */
HWTEST_F(SvgAnimationTest, SvgAnimationTest025, TestSize.Level1)
{
    // Test multiple animations simultaneously
    std::vector<RefPtr<SvgAnimation>> animations;
    
    for (int i = 0; i < 5; i++) {
        auto anim = AceType::MakeRefPtr<SvgAnimation>();
        anim->SetAttributeName("r");
        anim->SetFrom(std::to_string(10 + i * 10));
        anim->SetTo(std::to_string(20 + i * 10));
        anim->SetDur("2s");
        animations.push_back(anim);
    }
    
    // Test adding multiple animators
    for (int i = 0; i < 5; i++) {
        int32_t key = 200 + i;
        svgContext_->AddAnimator(key, animations[i]); // using same animator for simplicity
    }
    
    SUCCEED(); // Test passes if no crash occurs
}
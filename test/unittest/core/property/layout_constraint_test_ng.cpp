/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include <functional>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class LayoutConstraintTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: LayoutConstraintTestNg001
 * @tc.desc: Test ApplyAspectRatio.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg001, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    auto calcSize = std::make_optional<CalcSize>();
    /**
     * @tc.steps: step1 call ApplyAspectRatio and set ratio < 0.
     * @tc.expected: the set value do not change.
     */
    float ratio = -1.0;
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step2 call ApplyAspectRatio, set ratio = 1 and useDefinedWidth.
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 1.
     */
    ratio = 1.0;
    std::string widthStr = "768px";
    CalcLength width = CalcLength::FromString(widthStr);
    std::string heightStr = "1024px";
    CalcLength height = CalcLength::FromString(heightStr);
    calcSize = std::make_optional<CalcSize>(width, height);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width(), layoutConstraint.selfIdealSize.Height());

    /**
     * @tc.steps: step3 call ApplyAspectRatio, set ratio = 2 and not useDefinedWidth
                    and selfIdealSize.Width().
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 2.
     */
    ratio = 2.0;
    width = CalcLength();
    heightStr = "1024px";
    height = CalcLength::FromString(heightStr);
    calcSize = std::make_optional<CalcSize>(width, height);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width().value(), layoutConstraint.selfIdealSize.Height().value() * 2);

    /**
     * @tc.steps: step4 call ApplyAspectRatio, set ratio = 4 and not useDefinedWidth
                    and selfIdealSize.Height().
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 4.
     */
    ratio = 4.0;
    widthStr = "768px";
    width = CalcLength::FromString(widthStr);
    height = CalcLength();
    calcSize = std::make_optional<CalcSize>(width, height);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width().value(), layoutConstraint.selfIdealSize.Height().value() * 4);

    /**
     * @tc.steps: step5 call ApplyAspectRatio, set ratio = 4 and not useDefinedWidth
                    and selfIdealSize is null and maxHeight and maxWidth is inf.
     * @tc.expected: the set value do not change.
     */
    calcSize = std::nullopt;
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step6 call ApplyAspectRatio, set ratio = 4 and not useDefinedWidth
                    and selfIdealSize is null and maxHeight and maxWidth is 1024.
     * @tc.expected: the set value do not change.
     */
    SizeT<float> size(1024, 2048);
    layoutConstraint.UpdateMaxSizeWithCheck(size);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), layoutConstraint.parentIdealSize.Height().value() * 4);

    /**
     * @tc.steps: step7 call ApplyAspectRatio, set ratio = 1, useDefinedWidth and useDefinedWidth.value() = false.
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 1.
     */
    ratio = 1.0;
    heightStr = "1024px";
    height = CalcLength::FromString(heightStr);
    calcSize = std::make_optional<CalcSize>(std::nullopt, height);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width(), layoutConstraint.selfIdealSize.Height());

    /**
     * @tc.steps: step8 call ApplyAspectRatio, set ratio = 1, useDefinedWidth NULL.
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 2.
     */
    ratio = 2.0;
    calcSize = std::nullopt;
    std::optional<float> selfIdeaWidth = std::nullopt;
    auto selfIdeaHeight = std::make_optional<float>(960);
    layoutConstraint.selfIdealSize = OptionalSizeF(selfIdeaWidth, selfIdeaHeight);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width().value(), layoutConstraint.selfIdealSize.Height().value() * 2);

    /**
     * @tc.steps: step8 call ApplyAspectRatio, set ratio = 1, useDefinedWidth NULL.
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 4.
     */
    ratio = 4.0;
    calcSize = std::nullopt;
    selfIdeaWidth = std::nullopt;
    selfIdeaHeight = std::nullopt;
    layoutConstraint.selfIdealSize = OptionalSizeF(selfIdeaWidth, selfIdeaHeight);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.minSize.Width(), 0);

    /**
     * @tc.steps: step8 call ApplyAspectRatio, set ratio = 1, useDefinedWidth NULL.
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 1.
     */
    ratio = 1.0;
    calcSize = std::nullopt;
    selfIdeaWidth = std::nullopt;
    selfIdeaHeight = std::nullopt;
    layoutConstraint.selfIdealSize = OptionalSizeF(selfIdeaWidth, selfIdeaHeight);
    layoutConstraint.minSize = SizeT<float>(1, 2);
    layoutConstraint.maxSize = SizeT<float>(100, 200);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height());
}

/**
 * @tc.name: LayoutConstraintTestNg002
 * @tc.desc: Test ApplyAspectRatioToParentIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg002, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    /**
     * @tc.steps: step1 call ApplyAspectRatioToParentIdealSize and set ratio < 0 and useWidth false.
     * @tc.expected: the set value do not change.
     */
    bool useWidth = false;
    float ratio = -1;
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step2 call ApplyAspectRatioToParentIdealSize and set ratio = 1 and useWidth true.
     * @tc.expected: parentIdealSize.Width() == layoutConstraint.parentIdealSize.Height().
     */
    ratio = 1;
    useWidth = true;
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), layoutConstraint.parentIdealSize.Height().value());

    /**
     * @tc.steps: step3 call ApplyAspectRatioToParentIdealSize and set ratio = 2 and useWidth false.
     * @tc.expected: parentIdealSize.Width() == layoutConstraint.parentIdealSize.Height() * 2.
     */
    ratio = 2;
    useWidth = false;
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), layoutConstraint.parentIdealSize.Height().value() * 2);

    /**
     * @tc.steps: step4 call ApplyAspectRatioToParentIdealSize and set ratio = 2 and useWidth false.
     * @tc.expected: the set value do not change.
     */
    ratio = 4;
    useWidth = false;
    layoutConstraint.parentIdealSize = OptionalSizeF();
    layoutConstraint.parentIdealSize.SetWidth(768);
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);
}

/**
 * @tc.name: LayoutConstraintTestNg003
 * @tc.desc: Test ApplyAspectRatioByMaxSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg003, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);
    layoutConstraint.minSize.SetWidth(2);
    layoutConstraint.minSize.SetHeight(3);
    layoutConstraint.maxSize.SetWidth(2048);
    layoutConstraint.maxSize.SetHeight(4096);

    /**
     * @tc.steps: step1 call ApplyAspectRatioByMaxSize and set ratio < 0 and useDefinedWidth false.
     * @tc.expected: the set value do not change.
     */
    auto useDefinedWidth = std::make_optional<bool>(false);
    float ratio = -1;
    layoutConstraint.ApplyAspectRatioByMaxSize(ratio, useDefinedWidth);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step2 call ApplyAspectRatioByMaxSize and set ratio = 1 and useDefinedWidth true.
     * @tc.expected: the set value do not change.
     */
    ratio = 1;
    useDefinedWidth = std::make_optional<bool>(true);
    layoutConstraint.ApplyAspectRatioByMaxSize(ratio, useDefinedWidth);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height());

    /**
     * @tc.steps: step3 call ApplyAspectRatioByMaxSize and set ratio = 2 and useDefinedWidth false.
     * @tc.expected: minSize.Width() == minSize.Height() * 2.
     */
    ratio = 2;
    useDefinedWidth = std::make_optional<bool>(false);
    layoutConstraint.ApplyAspectRatioByMaxSize(ratio, useDefinedWidth);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height() * 2);

    /**
     * @tc.steps: step4 call ApplyAspectRatioByMaxSize and set ratio = 2 and useDefinedWidth is null.
     * @tc.expected: minSize.Width() == minSize.Height() * 4.
     */
    ratio = 4;
    useDefinedWidth = std::nullopt;
    layoutConstraint.ApplyAspectRatioByMaxSize(ratio, useDefinedWidth);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height() * 4);
}

/**
 * @tc.name: LayoutConstraintTestNg004
 * @tc.desc: Test ApplyAspectRatioByMaxSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg004, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);

    /**
     * @tc.steps: step1 call ApplyAspectRatioByMaxSize and set ratio < 0 and useDefinedWidth false.
     * @tc.expected: the set value do not change.
     */
    float ratio = -1;
    bool useDefinedWidth = false;
    layoutConstraint.ApplyAspectRatioWithCalcSize(ratio, useDefinedWidth);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);
}

/**
 * @tc.name: LayoutConstraintTestNg005
 * @tc.desc: Test ApplyAspectRatioWithoutCalcSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg005, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    /**
     * @tc.steps: step1 call ApplyAspectRatioWithoutCalcSize and set ratio < 0 and useDefinedWidth false.
     * @tc.expected: the set value do not change.
     */
    float ratio = -1;
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step1 call ApplyAspectRatioWithoutCalcSize and set ratio = 1 and
                  maxSize.Width() < maxSize.Height().
     * @tc.expected: the minSize.Width() == minSize.Height().
     */
    ratio = 1;
    layoutConstraint.maxSize.SetWidth(2048);
    layoutConstraint.maxSize.SetHeight(4096);
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height());

    /**
     * @tc.steps: step1 call ApplyAspectRatioWithoutCalcSize and set ratio = 1 and
                  maxSize.Width() > maxSize.Height().
     * @tc.expected: the minSize.Width() == minSize.Height().
     */
    ratio = 2;
    layoutConstraint.maxSize.SetWidth(4096);
    layoutConstraint.maxSize.SetHeight(2048);
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio);
    EXPECT_EQ(layoutConstraint.minSize.Width(), layoutConstraint.minSize.Height() * 2);
}

/**
 * @tc.name: LayoutConstraintTestNg006
 * @tc.desc: Test ApplyAspectRatio.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg006, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);

    auto calcSize = std::make_optional<CalcSize>();
    /**
     * @tc.steps: step1 call ApplyAspectRatio and set ratio > 0 and calcSize not has width and height.
     * @tc.expected: the set value do not change.
     */
    float ratio = 1.0;
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step2 call ApplyAspectRatio, set ratio = 1 and useDefinedWidth.
     * @tc.expected: set Height failure, height not change.
     */
    std::string widthStr = "768px";
    CalcLength width = CalcLength::FromString(widthStr);
    std::string heightStr = "1024px";
    CalcLength height = CalcLength::FromString(heightStr);
    calcSize = std::make_optional<CalcSize>(width, height);
    layoutConstraint.selfIdealSize.SetHeight(960);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Height(), 960.0);

    /**
     * @tc.steps: step3 call ApplyAspectRatio, set ratio = 2 and not useDefinedWidth
                    and selfIdealSize.Width().
     * @tc.expected: the selfIdealSize.Width() = selfIdealSize.Height() * 2.
     */
    ratio = 2.0;
    width = CalcLength();
    heightStr = "1024px";
    height = CalcLength::FromString(heightStr);
    calcSize.value().Reset();
    calcSize->SetHeight(height);
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width().value(), layoutConstraint.selfIdealSize.Height().value() * 2);

    /**
     * @tc.steps: step4 call ApplyAspectRatio, set minSize and set maxSize
     * @tc.expected: minSize and maxSize is neaer Infinity.
     */
    layoutConstraint.minSize = { Infinity<float>() / 2, Infinity<float>() / 2 };
    layoutConstraint.maxSize = { Infinity<float>() / 2, Infinity<float>() / 2 };
    layoutConstraint.ApplyAspectRatio(ratio, calcSize);
    EXPECT_EQ(layoutConstraint.maxSize.Width(), Infinity<float>());
    EXPECT_EQ(layoutConstraint.minSize.Width(), Infinity<float>());
}

/**
 * @tc.name: LayoutConstraintTestNg007
 * @tc.desc: Test ApplyAspectRatioToParentIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg007, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(0, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    /**
     * @tc.steps: step1 call ApplyAspectRatioToParentIdealSize and set ratio > 0 and useWidth false
     * and parentIdealSize width false.
     * @tc.expected: width changed successfully
     */
    bool useWidth = false;
    float ratio = 2;
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 2048);

    /**
     * @tc.steps: step2 call ApplyAspectRatioToParentIdealSize and set ratio > 0 and useWidth true
     * and parentIdealSize width false.
     * @tc.expected: width changed successfully
     */
    ratio = 1;
    useWidth = true;
    layoutConstraint.parentIdealSize.Reset();
    layoutConstraint.parentIdealSize.SetHeight(1024);
    layoutConstraint.ApplyAspectRatioToParentIdealSize(useWidth, ratio);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 1024);
}

/**
 * @tc.name: LayoutConstraintTestNg008
 * @tc.desc: Test ApplyAspectRatioWithoutCalcSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg008, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    /**
     * @tc.steps: step1 call ApplyAspectRatioWithoutCalcSize and set ratio < 0 and greaterThanApiTen true.
     * @tc.expected: the set value do not change.
     */
    float ratio = -1;
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio, true);
    EXPECT_EQ(layoutConstraint.parentIdealSize.Width().value(), 768.0);

    /**
     * @tc.steps: step2 call ApplyAspectRatioWithoutCalcSize and set ratio = 2 reaterThanApiTen true.
     * @tc.expected: minSize,maxSize,percentRef height all set success
     */
    ratio = 2;
    layoutConstraint.percentReference = { 0, 1025 };
    layoutConstraint.maxSize.SetWidth(2048);
    layoutConstraint.maxSize.SetHeight(4096);
    layoutConstraint.minSize.SetWidth(1);
    layoutConstraint.minSize.SetHeight(2);
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio, true);
    EXPECT_EQ(layoutConstraint.minSize.Height(), 0.5f);
    EXPECT_EQ(layoutConstraint.maxSize.Height(), 1024);
    EXPECT_EQ(layoutConstraint.percentReference.Height(), 0);

    /**
     * @tc.steps: step3 call ApplyAspectRatioWithoutCalcSize and set ratio = 2 reaterThanApiTen true.
     * @tc.expected: minSize,maxSize,percentRef width all set success
     */
    ratio = 2;
    layoutConstraint.maxSize.SetWidth(4096);
    layoutConstraint.maxSize.SetHeight(2048);
    layoutConstraint.minSize.SetWidth(1);
    layoutConstraint.minSize.SetHeight(2);
    layoutConstraint.percentReference = { 8193, 0 };
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio, true);
    EXPECT_EQ(layoutConstraint.minSize.Width(), 4);
    EXPECT_EQ(layoutConstraint.maxSize.Width(), 4096);
    EXPECT_EQ(layoutConstraint.percentReference.Width(), 0);

    /**
     * @tc.steps: step4 call ApplyAspectRatioWithoutCalcSize and set ratio = 2 reaterThanApiTen true.
     * @tc.expected: minSize,maxSize,percentRef all set fail
     */
    layoutConstraint.percentReference = { 0, 0 };
    layoutConstraint.ApplyAspectRatioWithoutCalcSize(ratio, true);
    EXPECT_EQ(layoutConstraint.percentReference.Width(), 0);
    EXPECT_EQ(layoutConstraint.percentReference.Height(), 0);
}

/**
 * @tc.name: LayoutConstraintTestNg009
 * @tc.desc: Test ApplyAspectRatioWithoutCalcSize.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutConstraintTestNg, LayoutConstraintTestNg009, TestSize.Level0)
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);

    /**
     * @tc.steps: step1 call Reset.
     * @tc.expected: Reset Success.
     */
    layoutConstraint.Reset();
    EXPECT_EQ(layoutConstraint.minSize.Width(), 0);
    EXPECT_EQ(layoutConstraint.minSize.Height(), 0);
}
} // namespace OHOS::Ace::NG
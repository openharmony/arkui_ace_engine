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
#include "divider_base_test_ng.h"

#include "core/components_ng/property/layout_constraint.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {} // namespace
class DividerNewTestNG : public DividerBaseTestNG {};

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, horizontal.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest01, TestSize.Level1)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 200);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) {});
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());

    // expect: divider length = 200
    EXPECT_EQ(pattern->dividerLength_, 200.0f);
}

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, vertical
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest02, TestSize.Level1)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 100);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) { model.Vertical(true); });
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());
    EXPECT_EQ(pattern->dividerLength_, 100.0f);
}
} // namespace OHOS::Ace::NG
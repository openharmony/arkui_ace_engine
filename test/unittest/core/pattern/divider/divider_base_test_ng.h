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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DIVIDER_BASE_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DIVIDER_BASE_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/divider/divider_layout_algorithm.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/components_ng/pattern/divider/divider_modifier.h"
#include "core/components_ng/pattern/divider/divider_paint_method.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"

namespace OHOS::Ace::NG {
class DividerBaseTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateDivider(const std::function<void(DividerModelNG)>& callback);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DIVIDER_BASE_TEST_NG_H
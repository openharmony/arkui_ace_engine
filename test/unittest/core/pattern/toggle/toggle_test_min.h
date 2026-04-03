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

#ifndef TEST_UNITTEST_CORE_PATTERN_TOGGLE_TOGGLE_TEST_MIN_H
#define TEST_UNITTEST_CORE_PATTERN_TOGGLE_TOGGLE_TEST_MIN_H

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_base_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

namespace OHOS::Ace::NG {

// Base test class for toggle tests
class ToggleTestBase : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_PATTERN_TOGGLE_TOGGLE_TEST_MIN_H

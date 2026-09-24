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

#ifndef TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_TEST_MIN_H
#define TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_TEST_MIN_H

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/napi_rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_foreground_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_accessibility_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/common_text/counter_host.h"
#include "core/components_ng/pattern/common_text/counter_decorator.h"
#include "core/components_ng/pattern/common_text/counter_constants.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components/text_field/textfield_theme.h"

#undef private
#undef protected

class RichEditorTestBase : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> richEditorNode_;
};

#endif // TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_TEST_MIN_H

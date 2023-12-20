/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_DRAG_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_DRAG_TEST_NG_H

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "frameworks/core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"

namespace OHOS::Ace::NG {
class RichEditorDragTestNG : public TestNG {
public:
    using Callback = std::function<void (RichEditorModelNG& model)>;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateRichEditor(Callback&& callback, uint32_t childSpanNum = 0);
    void CreateDragNodeWithImageSpan(uint32_t childSpanNum);
    void AddImageSpan();
    void ClearSpan();
    RefPtr<FrameNode> frameNode_;
    RefPtr<RichEditorPattern> pattern_;
    RefPtr<FrameNode> dragNode_;
    RefPtr<RichEditorDragPattern> dragPattern_;
};
} // namespace OHOS::Ace::NG
#endif
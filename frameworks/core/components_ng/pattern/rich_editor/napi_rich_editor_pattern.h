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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_NAPI_RICH_EDITOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_NAPI_RICH_EDITOR_PATTERN_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
class NapiRichEditorPattern : public RichEditorPattern {
    DECLARE_ACE_TYPE(NapiRichEditorPattern, RichEditorPattern);
    ACE_DISALLOW_COPY_AND_MOVE(NapiRichEditorPattern);

public:
    explicit NapiRichEditorPattern(bool isStyledStringMode = false) : RichEditorPattern(isStyledStringMode) {}
    ~NapiRichEditorPattern() override = default;

    bool IsNapiRichEditorPattern() const override { return true; }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_NAPI_RICH_EDITOR_PATTERN_H

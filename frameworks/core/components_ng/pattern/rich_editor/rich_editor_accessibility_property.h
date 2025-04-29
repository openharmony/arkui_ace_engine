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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_ACCESSIBILITY_PROPERTY_H

#include "core/components_ng/pattern/text/text_accessibility_property.h"

namespace OHOS::Ace::NG {
class RichEditorAccessibilityProperty : public TextAccessibilityProperty {
    DECLARE_ACE_TYPE(RichEditorAccessibilityProperty, TextAccessibilityProperty);

public:
    RichEditorAccessibilityProperty() = default;

    ~RichEditorAccessibilityProperty() override = default;

    bool IsEditable() const override;

    std::string GetHintText() const override;

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif

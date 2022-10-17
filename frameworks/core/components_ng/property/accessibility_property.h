/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_H

#include <cstdint>
#include <string>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT AccessibilityProperty : public virtual AceType {
    DECLARE_ACE_TYPE(AccessibilityProperty, AceType);

public:
    AccessibilityProperty() = default;

    ~AccessibilityProperty() override = default;

    virtual std::string GetText() const
    {
        return "";
    }

    virtual void SetText(const std::string& text) {}

    virtual bool IsCheckable() const
    {
        return false;
    }

    virtual bool IsChecked() const
    {
        return false;
    }

    virtual bool IsAccessibilityFocused() const
    {
        return false;
    }

    virtual bool IsSelected() const
    {
        return false;
    }

    virtual bool IsPassword() const
    {
        return false;
    }

    virtual bool IsEditable() const
    {
        return false;
    }

    virtual bool IsMultiLine() const
    {
        return false;
    }

    virtual bool IsDeletable() const
    {
        return false;
    }

    virtual bool IsHint() const
    {
        return false;
    }

    virtual int32_t GetCurrentIndex() const
    {
        return 0;
    }

    virtual int32_t GetBeginIndex() const
    {
        return 0;
    }

    virtual int32_t GetEndIndex() const
    {
        return 0;
    }

protected:
    ACE_DISALLOW_COPY_AND_MOVE(AccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif
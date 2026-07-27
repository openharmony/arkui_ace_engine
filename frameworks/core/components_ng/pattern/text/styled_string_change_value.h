
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_STYLED_STRING_CHANGE_VALUE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_STYLED_STRING_CHANGE_VALUE_H

#include "base/memory/ace_type.h"

#include "core/components_ng/pattern/text/text_model.h"
#include "core/common/ime/text_range.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT StyledStringChangeValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(StyledStringChangeValue, BaseEventInfo);
public:
    StyledStringChangeValue() : BaseEventInfo("StyledStringChangeValue") {}
    ~StyledStringChangeValue() = default;

    void SetRangeBefore(const TextRange& range)
    {
        rangeBefore_ = range;
    }

    TextRange GetRangeBefore() const
    {
        return rangeBefore_;
    }

    void SetRangeAfter(const TextRange& range)
    {
        rangeAfter_ = range;
    }

    TextRange GetRangeAfter() const
    {
        return rangeAfter_;
    }

    void SetReplacementString(const RefPtr<SpanStringBase>& styledString)
    {
        replacementString_ = styledString;
    }

    const RefPtr<SpanStringBase> GetReplacementString() const
    {
        return replacementString_;
    }

    void SetPreviewText(const RefPtr<SpanStringBase>& previewText)
    {
        previewText_ = previewText;
    }

    const RefPtr<SpanStringBase> GetPreviewText() const
    {
        return previewText_;
    }

private:
    TextRange rangeBefore_;
    TextRange rangeAfter_;
    RefPtr<SpanStringBase> replacementString_;
    RefPtr<SpanStringBase> previewText_;
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_STYLED_STRING_CHANGE_VALUE_H
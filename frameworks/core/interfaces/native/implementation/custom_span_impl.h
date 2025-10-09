/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INT7ERFACES_NATIVE_IMPLEMENTATION_CUSTOM_SPAN_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INT7ERFACES_NATIVE_IMPLEMENTATION_CUSTOM_SPAN_IMPL_H

#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"

namespace OHOS::Ace::NG {
class CustomSpanImpl : public CustomSpan {
    DECLARE_ACE_TYPE(CustomSpanImpl, CustomSpan);

public:
    void AddStyledString(const WeakPtr<SpanStringBase>& spanString) override
    {
        spanStringBaseSet_.insert(spanString);
    }
    void RemoveStyledString(const WeakPtr<SpanStringBase>& spanString) override
    {
        spanStringBaseSet_.erase(spanString);
    }
    void Invalidate()
    {
        for (const auto& styledStringWeakPtr : spanStringBaseSet_) {
            auto styledString = AceType::DynamicCast<SpanString>(styledStringWeakPtr.Upgrade());
            if (!styledString) {
                continue;
            }
            styledString->MarkDirtyFrameNode();
        }
    }
private:
    std::set<WeakPtr<SpanStringBase>> spanStringBaseSet_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INT7ERFACES_NATIVE_IMPLEMENTATION_CUSTOM_SPAN_IMPL_H
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

    using SpanSet = std::set<WeakPtr<SpanStringBase>>;

    CustomSpanImpl(std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure,
        std::optional<std::function<void(OHOS::Ace::NG::DrawingContext&, CustomSpanOptions)>> onDraw,
        std::shared_ptr<SpanSet> spanSet, int32_t start, int32_t end)
        : CustomSpan(onMeasure, onDraw, start, end), spanStringBaseSet_(spanSet) {}

public:
    CustomSpanImpl() : spanStringBaseSet_(new SpanSet()) {}

    void AddStyledString(const WeakPtr<SpanStringBase>& spanString) override
    {
        if (spanStringBaseSet_) {
            spanStringBaseSet_->insert(spanString);
        }
    }
    void RemoveStyledString(const WeakPtr<SpanStringBase>& spanString) override
    {
        if (spanStringBaseSet_) {
            spanStringBaseSet_->erase(spanString);
        }
    }
    void Invalidate()
    {
        if (!spanStringBaseSet_) {
            return;
        }

        for (const auto& styledStringWeakPtr : *spanStringBaseSet_) {
            auto styledString = AceType::DynamicCast<SpanString>(styledStringWeakPtr.Upgrade());
            if (!styledString) {
                continue;
            }
            styledString->MarkDirtyFrameNode();
        }
    }
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override
    {
        if (end - start > 1) {
            return nullptr;
        }
        auto span = MakeRefPtr<CustomSpanImpl>(GetOnMeasure(), GetOnDraw(), spanStringBaseSet_, start, end);
        return AceType::DynamicCast<SpanBase>(span);
    }
private:
    std::shared_ptr<SpanSet> spanStringBaseSet_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INT7ERFACES_NATIVE_IMPLEMENTATION_CUSTOM_SPAN_IMPL_H
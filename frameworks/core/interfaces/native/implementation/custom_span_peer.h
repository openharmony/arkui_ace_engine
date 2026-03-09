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

#pragma once

#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "arkoala_api_generated.h"

struct CustomSpanNativePeer : public OHOS::Ace::CustomSpan {
    DECLARE_ACE_TYPE(CustomSpanNativePeer, OHOS::Ace::CustomSpan);

    using SpanSet = std::set<OHOS::Ace::WeakPtr<OHOS::Ace::SpanStringBase>>;

    CustomSpanNativePeer(CustomSpanNativePeer& other, int32_t start, int32_t end)
        : OHOS::Ace::CustomSpan(other.GetOnMeasure(), other.GetOnDraw(), start, end),
          spanStringBaseSet_(other.spanStringBaseSet_),
          obj_(other.obj_)
    {
        if (obj_.resource.hold) {
            (*obj_.resource.hold)(obj_.resource.resourceId);
        }
    }

public:
    CustomSpanNativePeer() : OHOS::Ace::CustomSpan(), spanStringBaseSet_(new SpanSet()), isOriginal_(true) {}
    ~CustomSpanNativePeer() override
    {
        if (!isOriginal_ && obj_.resource.release) {
            (*obj_.resource.release)(obj_.resource.resourceId);
        }
    }

    void AddStyledString(const OHOS::Ace::WeakPtr<OHOS::Ace::SpanStringBase>& spanString) override
    {
        if (spanStringBaseSet_) {
            spanStringBaseSet_->insert(spanString);
        }
    }
    void RemoveStyledString(const OHOS::Ace::WeakPtr<OHOS::Ace::SpanStringBase>& spanString) override
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
            auto styledString = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::SpanString>(styledStringWeakPtr.Upgrade());
            if (!styledString) {
                continue;
            }
            styledString->MarkDirtyFrameNode();
        }
    }
    OHOS::Ace::RefPtr<OHOS::Ace::SpanBase> GetSubSpan(int32_t start, int32_t end) override
    {
        if (end - start > 1) {
            return nullptr;
        }
        return MakeRefPtr<CustomSpanNativePeer>(*this, start, end);
    }
    void SetObject(const Ark_Object &arkObj)
    {
        obj_ = arkObj;
    }
    const Ark_Object &GetObject() const
    {
        return obj_;
    }
private:
    std::shared_ptr<SpanSet> spanStringBaseSet_;
    Ark_Object obj_ {};
    bool isOriginal_ {false};
};

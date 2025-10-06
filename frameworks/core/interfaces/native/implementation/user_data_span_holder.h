/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_USER_DATA_SPAN_HOLDER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_USER_DATA_SPAN_HOLDER_IMPL_H

#include "core/components_ng/pattern/text/span/span_object.h"
#include "base/memory/ace_type.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
class UserDataSpanHolder final : public ExtSpan {
    DECLARE_ACE_TYPE(UserDataSpanHolder, ExtSpan)
public:
    UserDataSpanHolder(const Ark_UserDataSpan& span, int32_t start, int32_t end): 
        ExtSpan(start, end), span_(span)
    {
        if (span_.resource.hold) {
            (*span_.resource.hold)(span_.resource.resourceId);
        }
    }
    explicit UserDataSpanHolder(const Ark_UserDataSpan& span): UserDataSpanHolder(span, 0, 0) {}
    ~UserDataSpanHolder()
    {
        if (span_.resource.release) {
            (*span_.resource.release)(span_.resource.resourceId);
        }
    }
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override
    {
        return AceType::MakeRefPtr<UserDataSpanHolder>(span_, start, end);
    }

    Ark_UserDataSpan span_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_USER_DATA_SPAN_HOLDER_IMPL_H
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_LINK_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_LINK_INFO_H

#include "base/geometry/ng/rect_t.h"
#include "base/json/json_util.h"

namespace OHOS::Ace::NG {
class FormLinkInfo final {
public:
    FormLinkInfo() = default;

    ~FormLinkInfo() = default;

    void SetAction(const std::string& action)
    {
        action_ = action;
    }

    void SetFomLinkRect(const RectF& rect)
    {
        formLinkRect_ = rect;
    }

    std::unique_ptr<OHOS::Ace::JsonValue> ToJsonObject() const
    {
        auto json = JsonUtil::Create(true);
        json->Put("action", action_.c_str());
        json->Put("formLinkRect", formLinkRect_.ToString().c_str());
        return json;
    }

    std::string ToString() const
    {
        return ToJsonObject()->ToString();
    }

private:
    RectF formLinkRect_;
    std::string action_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_LINK_INFO_H

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

#include "base/memory/ace_type.h"
#include "base/utils/utf_helper.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_event_hub.h"

namespace OHOS::Ace::NG {
void SearchEventHub::UpdateChangeEvent(const std::u16string& value) const
{
    if (onValueChangeEvent_) {
        onValueChangeEvent_(value);
    }
    if (changeEvent_) {
        changeEvent_(value);
    }

    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateChangeEvent(value);
    auto id = host->GetInspectorIdValue("");
    if (!id.empty()) {
        Recorder::NodeDataCache::Get().PutString(host, id, UtfUtils::Str16ToStr8(value));
    }
}
} // namespace OHOS::Ace::NG

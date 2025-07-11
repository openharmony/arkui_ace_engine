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

#include "core/components_ng/pattern/list/list_item_group_pattern.h"

#include "base/log/dump_log.h"
#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ListItemGroupPattern::OnAttachToFrameNodeMultiThread()
{
    // do nothing unsafe thread
}
void ListItemGroupPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemGroupStyle_ == V2::ListItemGroupStyle::CARD) {
        SetListItemGroupDefaultAttributes(host);
    }
}
} // namespace OHOS::Ace::NG

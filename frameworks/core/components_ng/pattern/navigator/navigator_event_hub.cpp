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

#include "navigator_event_hub.h"

#include "core/common/container.h"
#include "core/components/page/page_target.h"

namespace OHOS::Ace::NG {

void NavigatorEventHub::OnClick()
{
    NavigatePage();
    // click event
}

void NavigatorEventHub::NavigatePage()
{
    auto container = Ace::Container::Current();
    auto target = Ace::PageTarget(url_, nullptr);
    container->NavigatePage(type_, target, params_);
}
} // namespace OHOS::Ace::NG
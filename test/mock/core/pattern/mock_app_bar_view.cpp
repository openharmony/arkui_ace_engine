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
#include "core/components_ng/pattern/app_bar/app_bar_view.h"

namespace OHOS::Ace::NG {
ACE_WEAK_SYM RefPtr<FrameNode> AppBarView::Create(const RefPtr<FrameNode>& stage)
{
    return nullptr;
}

ACE_WEAK_SYM void AppBarView::SetStatusBarItemColor(bool isLight)
{
    return;
}

ACE_WEAK_SYM std::optional<RectF> AppBarView::GetAppBarRect()
{
    return RectF();
}
} // namespace OHOS::Ace::NG

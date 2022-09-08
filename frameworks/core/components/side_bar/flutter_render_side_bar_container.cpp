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

#include "core/components/side_bar/flutter_render_side_bar_container.h"


namespace OHOS::Ace {
RenderLayer FlutterRenderSideBarContainer::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<Flutter::ClipLayer>(
            0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
        lastLayoutSize_ = GetLayoutSize();
    } else if (lastLayoutSize_ != GetLayoutSize()) {
        layer_->SetClip(0, GetLayoutSize().Width(), 0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
        lastLayoutSize_ = GetLayoutSize();
    }
    return AceType::RawPtr(layer_);
}
} // namespace OHOS::Ace

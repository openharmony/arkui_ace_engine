/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/paint_property.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void PaintProperty::SetHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> PaintProperty::GetHost() const
{
    return host_.Upgrade();
}

void PaintProperty::UpdatePaintPropertyHost(const PaintProperty* renderProperty)
{
    CHECK_NULL_VOID(renderProperty);
    host_ = renderProperty->host_;
}

} // namespace OHOS::Ace::NG

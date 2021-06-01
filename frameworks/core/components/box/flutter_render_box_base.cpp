/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/box/flutter_render_box_base.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderBoxBase::Create()
{
    return AceType::MakeRefPtr<FlutterRenderBoxBase>();
}

void FlutterRenderBoxBase::Paint(RenderContext& context, const Offset& offset)
{
    const auto renderContext = static_cast<FlutterRenderContext*>(&context);
    flutter::Canvas* canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    RenderNode::Paint(context, offset); // paint child
}

} // namespace OHOS::Ace

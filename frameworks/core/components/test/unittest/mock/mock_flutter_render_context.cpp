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

#include "core/pipeline/base/flutter_render_context.h"

#include "core/pipeline/base/render_node.h"
#include "core/pipeline/layers/offset_layer.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderContext> RenderContext::Create()
{
    return AceType::MakeRefPtr<FlutterRenderContext>();
}

FlutterRenderContext::~FlutterRenderContext()
{
}

void FlutterRenderContext::Repaint(const RefPtr<RenderNode>& node)
{
    return;
}

void FlutterRenderContext::PaintChild(const RefPtr<RenderNode>& child, const Offset& offset)
{
    return;
}

void FlutterRenderContext::StartRecording()
{
    return;
}

void FlutterRenderContext::StopRecordingIfNeeded()
{
    return;
}

void FlutterRenderContext::InitContext(RenderLayer layer, const Rect& rect)
{
    return;
}

flutter::Canvas* FlutterRenderContext::GetCanvas()
{
    return nullptr;
}

} // namespace OHOS::Ace

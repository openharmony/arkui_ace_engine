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

#include "core/components/plugin/render_plugin.h"

#include "base/log/event_report.h"

namespace OHOS::Ace {
void RenderPlugin::Update(const RefPtr<Component>& component)
{
    auto plugin = AceType::DynamicCast<PluginComponent>(component);

    Dimension rootWidht = 0.0_vp;
    Dimension rootHeight = 0.0_vp;
    if (plugin) {
        rootWidht = plugin->GetWidth();
        rootHeight = plugin->GetHeight();
    }

    if (rootWidht_ == rootWidht && rootHeight_ == rootHeight) {
        LOGE("same size, not resize render plugin");
        return;
    }

    if (rootWidht.IsValid() && rootHeight.IsValid()) {
        drawSize_ = Size(NormalizePercentToPx(rootWidht, false), NormalizePercentToPx(rootHeight, true));
    }
    rootWidht_ = rootWidht;
    rootHeight_ = rootHeight;

    MarkNeedLayout();
}

void RenderPlugin::PerformLayout()
{
    if (!NeedLayout()) {
        return;
    }

    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

bool RenderPlugin::TouchTest(const Point& globalPoint,
    const Point& parentLocalPoint, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    auto context = GetContext().Upgrade();
    if (context) {
        auto pluginContext = GetSubPipelineContext();
        if (pluginContext) {
            double x = globalPoint.GetX() - pluginContext->GetPluginEventOffset().GetX();
            double y = globalPoint.GetY() - pluginContext->GetPluginEventOffset().GetY();
            if (x <= rootWidht_.Value() && y <= rootHeight_.Value()) {
                context->SetTouchPipeline(WeakPtr<PipelineContext>(pluginContext));
            }
        }
    }
    return true;
}
}; // namespace OHOS::Ace

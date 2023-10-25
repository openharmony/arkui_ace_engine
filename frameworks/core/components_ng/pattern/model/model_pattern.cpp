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

#include "core/components_ng/pattern/model/model_pattern.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ModelPattern::OnRebuildFrame()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    modelAdapter_->OnRebuildFrame(context);
}

ModelPattern::ModelPattern(uint32_t key, Render3D::SurfaceType surfaceType) : key_(key)
{
    LOGD("MODEL_NG: ModelPattern::ModelPattern(%d)", key);
    modelAdapter_ = MakeRefPtr<ModelAdapterWrapper>(key_, surfaceType);
    modelAdapter_->SetPaintFinishCallback([weak = WeakClaim(this)]() {
            auto model = weak.Upgrade();
            if (model) {
                if (model->NeedsRepaint()) {
                    model->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                }
                model->GetPaintProperty<ModelPaintProperty>()->ResetFlagProperties();
            }
        });
}

void ModelPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    LOGD("MODEL_NG: ModelPattern::OnModifyDone()");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (touchListener_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchListener_) {
        gestureHub->RemoveTouchEvent(touchListener_);
    }
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchListener_);
}

bool ModelPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(modelAdapter_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(dirty, false);
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    auto contentSize = geometryNode->GetContentSize();
    auto contentOffset = geometryNode->GetContentOffset();

    bool measure = (config.skipMeasure || dirty->SkipMeasureContent()) ? false : true;
    float width = contentSize.Width();
    float height = contentSize.Height();
    float scale = PipelineContext::GetCurrentContext()->GetViewScale();
    modelAdapter_->OnDirtyLayoutWrapperSwap(contentOffset.GetX(), contentOffset.GetY(), width, height, scale,
        config.contentSizeChange);
    host->MarkNeedSyncRenderTree();

    return measure;
}

void ModelPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(modelAdapter_);
    modelAdapter_->OnAttachToFrameNode(host->GetRenderContext());
}

void ModelPattern::OnDetachFromFrameNode(FrameNode* node)
{
    LOGD("MODEL_NG: ModelPattern::OnDetachFromFrameNode(FrameNode* node)");
}

void ModelPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(modelAdapter_);
    bool repaint = modelAdapter_->HandleTouchEvent(info);
    if (repaint) {
        MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool ModelPattern::NeedsRepaint()
{
    CHECK_NULL_RETURN(modelAdapter_, false);
    return modelAdapter_->NeedsRepaint();
}

void ModelPattern::MarkDirtyNode(const PropertyChangeFlag flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(flag);
}

} // namespace OHOS::Ace::NG

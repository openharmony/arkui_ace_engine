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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MODEL_MODEL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MODEL_MODEL_PATTERN_H

#include <memory>

#include "base/memory/referenced.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/model/model_adapter_wrapper.h"
#include "core/components_ng/pattern/model/model_layout_algorithm.h"
#include "core/components_ng/pattern/model/model_paint_method.h"
#include "core/components_ng/pattern/model/model_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ModelPattern : public Pattern {
    DECLARE_ACE_TYPE(ModelPattern, Pattern);

public:
    ModelPattern(uint32_t key, const ModelViewContext& context);
    explicit ModelPattern(uint32_t key);
    ~ModelPattern() override;

    void SetModelViewContext(const ModelViewContext& context);

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ModelPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<ModelPaintMethod>(WeakClaim(RawPtr(modelAdapter_)));
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ModelLayoutAlgorithm>(WeakClaim(RawPtr(modelAdapter_)));
    }

    void UpdateTransformHintChangedCallbackId(std::optional<int32_t> id)
    {
        transformHintChangedCallbackId_ = id;
    }

    bool HasTransformHintChangedCallbackId() const
    {
        return transformHintChangedCallbackId_.has_value();
    }

    void OnModifyDone() override;
    void OnRebuildFrame() override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

private:
    uint32_t GetKey();
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool NeedsRepaint();
    void HandleTouchEvent(const TouchEventInfo& info);
    void MarkDirtyNode(const PropertyChangeFlag flag);

    uint32_t key_ = -1;

    RefPtr<ModelAdapterWrapper> modelAdapter_;
    RefPtr<TouchEventImpl> touchListener_;

    std::optional<int32_t> transformHintChangedCallbackId_;
    uint32_t rotation_ = 0; // Transform

    ACE_DISALLOW_COPY_AND_MOVE(ModelPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MODEL_MODEL_PATTERN_H

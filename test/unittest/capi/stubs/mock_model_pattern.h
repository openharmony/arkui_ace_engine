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
#ifndef CAPI_STUBS_MOCK_MODEL_PATTERN_H
#define CAPI_STUBS_MOCK_MODEL_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "test/unittest/capi/stubs/mock_shader_input_buffer.h"
#include "test/unittest/capi/stubs/mock_custom_render_descriptor.h"
#include "core/components_ng/pattern/model/model_adapter_wrapper.h"
#include "core/components_ng/pattern/model/model_view.h"

namespace OHOS::Ace::NG {

class ModelPattern : public Pattern {
    DECLARE_ACE_TYPE(ModelPattern, Pattern);
public:
    ModelPattern(uint32_t key, const ModelViewContext& context);
    ModelPattern(uint32_t key);
    ~ModelPattern() override;

    void SetModelViewContext(const ModelViewContext& context);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ModelPaintProperty>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LayoutProperty>();
    }
private:
    uint32_t key_ = -1;
    RefPtr<ModelAdapterWrapper> modelAdapter_;
};
} // namespace OHOS::Ace::NG
#endif // CAPI_STUBS_MOCK_MODEL_PATTERN_H
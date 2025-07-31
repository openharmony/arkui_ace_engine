/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ARKTS_DYNAMIC_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ARKTS_DYNAMIC_PATTERN_H

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"

namespace OHOS::Ace::NG {
class ArktsDynamicPattern : public DynamicPattern {
    DECLARE_ACE_TYPE(ArktsDynamicPattern, DynamicPattern);

public:
    ArktsDynamicPattern();
    ~ArktsDynamicPattern() override;

    void InitializeDynamicComponent();
    void OnAttachContext(PipelineContext *context) override;
    void OnDetachContext(PipelineContext *context) override;

    void SetDynamicParam(const DynamicParam& param);

private:
    void InitializeArktsDcRender();
    bool CheckDynamicRendererConstraint(int32_t workerId);

    DynamicParam param_;
    ACE_DISALLOW_COPY_AND_MOVE(ArktsDynamicPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_ARKTS_DYNAMIC_PATTERN_H

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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EFFECT_COMPONENT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EFFECT_COMPONENT_MODEL_NG_H

#include "core/components_ng/pattern/effect_component/effect_component_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT EffectComponentModelNG : public OHOS::Ace::EffectComponentModel {
public:
    void Create() override;
    void Create(NG::EffectLayer independentLayer) override;
    void AlwaysSnapshot(bool enable) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EFFECT_COMPONENT_MODEL_NG_H
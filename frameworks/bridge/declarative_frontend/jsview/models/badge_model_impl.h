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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BADGE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BADGE_MODEL_IMPL_H

#include "core/components_ng/pattern/badge/badge_model.h"

namespace OHOS::Ace::Framework {
class BadgeModelImpl : public OHOS::Ace::BadgeModel {
public:
    void Create(BadgeParameters& badgeParameters) override;
    void CreateByFrameNode(const RefPtr<NG::FrameNode>& frameNode, BadgeParameters& badgeParameters) override
    {
        Create(badgeParameters);
    };
    
    RefPtr<NG::FrameNode> CreateBadgeFrameNode() override
    {
        return nullptr;
    };
    void SetIsDefault(bool isDefaultFontSize, bool isDefaultBadgeSize) override {};

private:
    void SetPositionForBadge(BadgeParameters& badgeParameters);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BADGE_MODEL_IMPL_H

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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_DADGE_DOM_BADGE_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_DADGE_DOM_BADGE_H

#include "compatible/components/badge/badge_component.h"
#include "core/components/badge/badge_theme.h"
#include "frameworks/bridge/common/dom/dom_configs.h"
#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

extern const char DOM_BADGE_CONFIG[];
extern const char DOM_BADGE_COUNT[];
extern const char DOM_BADGE_LABEL[];
extern const char DOM_BADGE_PLACEMENT[];
extern const char DOM_BADGE_VISIBLE[];
extern const char DOM_BADGE_MAX_COUNT[];
extern const char DOM_BADGE_COLOR[];
extern const char DOM_BADGE_CIRCLE_SIZE[];
extern const char DOM_BADGE_TEXT_FONT_SIZE[];
extern const char DOM_BADGE_TEXT_COLOR[];

class DOMBadge final : public DOMNode {
    DECLARE_ACE_TYPE(DOMBadge, DOMNode);

public:
    DOMBadge(NodeId nodeId, const std::string& nodeName);
    ~DOMBadge() override = default;

    void SetBadgeConfig(const BadgeConfig& badgeConfig);

    RefPtr<Component> GetSpecializedComponent() override
    {
        return badgeChild_;
    }

protected:
    void PrepareSpecializedComponent() override;
    void ResetInitializedStyle() override;
    void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) override;
    void OnChildNodeRemoved(const RefPtr<DOMNode>& child) override;

private:
    RefPtr<BadgeComponent> badgeChild_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_DADGE_DOM_BADGE_H

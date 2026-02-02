/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_H

#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

#include "ecmascript/napi/include/jsnapi.h"

namespace OHOS::Ace::NG {
class FrameNode;
}

namespace OHOS::Ace::Framework {
using OnSectionChangedCallback =
    std::function<void(size_t start, size_t deleteCount, std::vector<NG::WaterFlowSections::Section>& newSections,
        const std::vector<NG::WaterFlowSections::Section>& allSections)>;

class JSWaterFlowSections : public Referenced {
public:
    JSWaterFlowSections() = default;
    ~JSWaterFlowSections() override = default;

    void SetOnSectionChangedCallback(NG::FrameNode* node, OnSectionChangedCallback callback)
    {
        callbacks_.emplace(AceType::WeakClaim(node), callback);
    }

    bool IsBound(NG::FrameNode* node) const
    {
        return callbacks_.find(AceType::WeakClaim(node)) != callbacks_.end();
    }
    ACE_FORCE_EXPORT static panda::Local<panda::ObjectRef> NewInstance();

private:
    friend class JSWaterFlowSectionsBinding;
    ACE_DISALLOW_COPY_AND_MOVE(JSWaterFlowSections);
    std::map<WeakPtr<NG::FrameNode>, OnSectionChangedCallback> callbacks_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_H
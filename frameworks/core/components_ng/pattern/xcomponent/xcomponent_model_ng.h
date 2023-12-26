/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H

#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT XComponentModelNG : public OHOS::Ace::XComponentModel {
public:
    void Create(const std::string& id, XComponentType type, const std::string& libraryname,
        const std::shared_ptr<InnerXComponentController>& xcomponentController) override;
    RefPtr<AceType> Create(int32_t nodeId, float width, float height,
        const std::string& id, XComponentType type, const std::string& libraryname,
        const std::shared_ptr<InnerXComponentController>& xcomponentController) override;
    void SetSoPath(const std::string& soPath) override;
    void SetOnLoad(LoadEvent&& onLoad) override;
    void SetOnDestroy(DestroyEvent&& onDestroy) override;
    void RegisterOnCreate(RefPtr<AceType> node, LoadEvent&& onLoad) override;
    void RegisterOnDestroy(RefPtr<AceType> node, DestroyEvent&& onDestroy) override;
    bool IsTexture() override;
    void SetDetachCallback(DetachCallback&& onDetach) override;

    static bool IsTexture(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H

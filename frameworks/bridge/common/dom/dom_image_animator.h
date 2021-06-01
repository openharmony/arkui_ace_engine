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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_IMAGE_ANIMATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_IMAGE_ANIMATOR_H

#include "base/utils/macros.h"
#include "core/components/image/image_animator_component.h"
#include "core/components/image/image_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT DOMImageAnimator final : public DOMNode {
    DECLARE_ACE_TYPE(DOMImageAnimator, DOMNode);

public:
    DOMImageAnimator(NodeId nodeId, const std::string& nodeName);
    ~DOMImageAnimator() override = default;

    void CallSpecializedMethod(const std::string& method, const std::string& args) override;

    const char* GetState() const;

    RefPtr<Component> GetSpecializedComponent() override
    {
        return imageAnimator_;
    }

    void SetImagesAttr(const std::vector<ImageProperties>& imagesAttr)
    {
        imagesAttr_ = std::move(imagesAttr);
    }

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    void PrepareSpecializedComponent() override;

private:
    RefPtr<Animator> controller_;
    RefPtr<ImageAnimatorComponent> imageAnimator_;
    std::vector<ImageProperties> imagesAttr_;
    int32_t iteration_ = ANIMATION_REPEAT_INFINITE; // infinite as default.
    int32_t duration_ = 0; // Duration in millisecond.
    int32_t preDecode_ = 1;
    bool isReverse_ = false;
    bool fixedSize_ = true;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_IMAGE_ANIMATOR_H

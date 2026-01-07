/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_IMAGE_ANIMATOR_DOM_IMAGE_ANIMATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_IMAGE_ANIMATOR_DOM_IMAGE_ANIMATOR_H

#include "compatible/components/image-animator/image_animator_component.h"

#include "base/utils/macros.h"
#include "core/components/image/image_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {
ACE_EXPORT extern const char DOM_ITERATION[];
ACE_EXPORT extern const char DOM_PREDECODE[];
ACE_EXPORT extern const char DOM_DURATION[];
ACE_EXPORT extern const char DOM_FIXEDSIZE[];
ACE_EXPORT extern const char DOM_REVERSE[];
ACE_EXPORT extern const char DOM_FILLMODE[];
ACE_EXPORT extern const char DOM_ANIMATION_FILL_MODE_FORWARDS[];
ACE_EXPORT extern const char DOM_ANIMATION_FILL_MODE_BACKWARDS[];
ACE_EXPORT extern const char DOM_ANIMATION_FILL_MODE_BOTH[];
ACE_EXPORT extern const char DOM_IMAGE_ANIMATOR_START[];
ACE_EXPORT extern const char DOM_IMAGE_ANIMATOR_STOP[];
ACE_EXPORT extern const char DOM_IMAGE_ANIMATOR_PAUSE[];
ACE_EXPORT extern const char DOM_IMAGE_ANIMATOR_RESUME[];

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

    void SetImagesAttr(std::vector<ImageProperties>& imagesAttr)
    {
        imagesAttr_ = std::move(imagesAttr);
    }

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    void PrepareSpecializedComponent() override;

private:
    RefPtr<ImageAnimatorComponent> imageAnimator_;
    std::vector<ImageProperties> imagesAttr_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_IMAGE_ANIMATOR_DOM_IMAGE_ANIMATOR_H

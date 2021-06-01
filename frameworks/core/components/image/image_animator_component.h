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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_ANIMATOR_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_ANIMATOR_COMPONENT_H

#include "core/components/common/properties/border.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

struct ImageProperties {
    std::string src;
    std::string width;
    std::string height;
    std::string top;
    std::string left;
    std::string duration;
};

class ImageAnimatorComponent : public ComposedComponent {
    DECLARE_ACE_TYPE(ImageAnimatorComponent, ComposedComponent);

public:
    explicit ImageAnimatorComponent(const std::string& name) : ComposedComponent(GenerateComponentId(), name) {}
    ~ImageAnimatorComponent() override = default;

    RefPtr<Element> CreateElement() override;

    static ComposeId GenerateComponentId();

    void SetIteration(int32_t iteration);
    void SetDuration(int32_t duration);
    void SetIsReverse(bool isReverse);
    void SetIsFixedSize(bool isFixedSize);
    void SetBorder(const Border& border);
    void SetImageProperties(const std::vector<ImageProperties>& images);
    void SetAnimator(const RefPtr<Animator>& controller);
    void SetPreDecode(int32_t preDecode);

    int32_t GetIteration() const;
    int32_t GetDuration() const;
    int32_t GetPreDecode() const;
    bool GetIsReverse() const;
    bool GetIsFixedSize() const;
    const Border& GetBorder() const;
    const std::vector<ImageProperties>& GetImageProperties() const;
    RefPtr<Animator> GetAnimator() const;

private:
    RefPtr<Animator> controller_;
    std::vector<ImageProperties> images_;
    Border border_;
    int32_t iteration_ = 1;
    int32_t duration_ = 0; // Duration in millisecond.
    int32_t preDecode_ = 1;
    bool isReverse_ = false;
    bool isFixedSize_ = true;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_ANIMATOR_COMPONENT_H

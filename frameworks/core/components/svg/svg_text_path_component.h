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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_PATH_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_PATH_COMPONENT_H

#include "frameworks/core/components/svg/svg_sharp.h"
#include "frameworks/core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class SvgTextPathComponent : public ComponentGroup, public SvgSharp {
    DECLARE_ACE_TYPE(SvgTextPathComponent, ComponentGroup);

public:
    SvgTextPathComponent() = default;
    explicit SvgTextPathComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {};
    ~SvgTextPathComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Element> CreateElement() override;

    const std::string& GetTextData() const
    {
        return textData_;
    }

    void SetTextData(const std::string& textData)
    {
        textData_ = textData;
    }

    const std::string& GetPath() const
    {
        return path_;
    }

    void SetPath(const std::string& path)
    {
        path_ = path;
    }

    void SetStartOffset(const Dimension& startOffset)
    {
        startOffset_ = startOffset;
    }

    const Dimension& GetStartOffset() const
    {
        return startOffset_;
    }

    void SetTextLength(const Dimension& textLength)
    {
        textLength_ = textLength;
    }

    const Dimension& GetTextLength() const
    {
        return textLength_;
    }

    void SetLengthAdjust(const std::string& lengthAdjust)
    {
        lengthAdjust_ = lengthAdjust;
    }

    const std::string&  GetLengthAdjust() const
    {
        return lengthAdjust_;
    }

private:
    Dimension textLength_ = Dimension(0.0);
    Dimension startOffset_ = Dimension(0.0);
    std::string lengthAdjust_ = "spacing"; // Value type: spacing | spacingAndGlyphs
    std::string path_;
    std::string textData_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_PATH_COMPONENT_H

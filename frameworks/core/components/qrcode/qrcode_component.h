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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_COMPONENT_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class ACE_EXPORT QrcodeComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(QrcodeComponent, SoleChildComponent);

public:
    QrcodeComponent();
    ~QrcodeComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    const std::string& GetValue() const
    {
        return value_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetQrcodeColor() const
    {
        return qrcodeColor_;
    }

    QrcodeType GetType() const
    {
        return qrcodeType_;
    }

    const Dimension& GetQrcodeWidth() const
    {
        return qrcodeWidth_;
    }

    const Dimension& GetQrcodeHeight() const
    {
        return qrcodeHeight_;
    }

    bool IsWidthDefined() const
    {
        return isWidthDefined_;
    }

    bool IsHeightDefined() const
    {
        return isHeightDefined_;
    }

    void SetValue(const std::string& value)
    {
        value_ = value;
    }

    void SetBackgroundColor(const Color& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }

    void SetQrcodeColor(const Color& qrcodeColor)
    {
        qrcodeColor_ = qrcodeColor;
    }

    void SetQrcodeType(QrcodeType qrcodeType)
    {
        qrcodeType_ = qrcodeType;
    }

    void SetQrcodeWidth(const Dimension& qrcodeWidth)
    {
        qrcodeWidth_ = qrcodeWidth;
    }

    void SetQrcodeHeight(const Dimension& qrcodeHeight)
    {
        qrcodeHeight_ = qrcodeHeight;
    }

    void SetWidthDefined(bool isWidthDefined)
    {
        isWidthDefined_ = isWidthDefined;
    }

    void SetHeightDefined(bool isHeightDefined)
    {
        isHeightDefined_ = isHeightDefined;
    }

private:
    std::string value_;
    Color backgroundColor_;
    Color qrcodeColor_;
    QrcodeType qrcodeType_ { QrcodeType::RECT };
    Dimension qrcodeWidth_;
    Dimension qrcodeHeight_;
    bool isWidthDefined_ = false;
    bool isHeightDefined_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_COMPONENT_H

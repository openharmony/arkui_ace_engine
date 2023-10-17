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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_RESPONSE_AREA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_RESPONSE_AREA_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
class TextInputResponseArea : public virtual AceType {
    DECLARE_ACE_TYPE(TextInputResponseArea, AceType);

public:
    TextInputResponseArea() = default;
    ~TextInputResponseArea() = default;

    virtual void InitResponseArea(const WeakPtr<Pattern>& hostPattern) = 0;

    virtual SizeF Measure(LayoutWrapper* layoutWrapper) = 0;

    virtual void Layout(LayoutWrapper* layoutWrapper) = 0;

    virtual void DestoryArea()
    {
        areaRect_.Reset();
    }

    virtual OffsetF GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize) = 0;

    RectF GetAreaRect()
    {
        return areaRect_;
    }

protected:
    void LayoutChild(LayoutWrapper* layoutWrapper);
    WeakPtr<Pattern> hostPattern_;
    RectF areaRect_;
};

class PasswordResponseArea : public TextInputResponseArea {
    DECLARE_ACE_TYPE(PasswordResponseArea, TextInputResponseArea);

public:
    PasswordResponseArea() = default;
    ~PasswordResponseArea() = default;

    void InitResponseArea(const WeakPtr<Pattern>& hostPattern) override;

    SizeF Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    OffsetF GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize) override;

    void AddEvent(const RefPtr<FrameNode>& node);

    void DestoryArea() override;

    void SetObscured(bool isObscured)
    {
        isObscured_ = isObscured;
    }

private:
    void LoadImageSourceInfo();
    void UpdateImageSource();
    bool IsShowPasswordIcon();
    void OnPasswordIconClicked();
    RefPtr<FrameNode> CreateNode();
    std::optional<ImageSourceInfo> GetCurrentSourceInfo()
    {
        return isObscured_ ? hideIcon_ : showIcon_;
    }
    bool isObscured_ = true;
    std::optional<ImageSourceInfo> showIcon_;
    std::optional<ImageSourceInfo> hideIcon_;
    RefPtr<ClickEvent> clickListener_;
    WeakPtr<FrameNode> passwordNode_;
};

class UnitResponseArea : public TextInputResponseArea {
    DECLARE_ACE_TYPE(UnitResponseArea, TextInputResponseArea);

public:
    UnitResponseArea(const RefPtr<NG::UINode>& unitNode) : unitNode_(WeakClaim(AceType::RawPtr(unitNode))) {}
    ~UnitResponseArea() = default;

    void SetUnitNode(const RefPtr<NG::UINode>& unitNode)
    {
        unitNode_ = WeakClaim(AceType::RawPtr(unitNode));
    }

    void InitResponseArea(const WeakPtr<Pattern>& hostPattern) override;

    SizeF Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    OffsetF GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize) override;

    void DestoryArea() override;

private:
    bool IsShowUnit();
    WeakPtr<NG::UINode> unitNode_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_RESPONSE_AREA_H

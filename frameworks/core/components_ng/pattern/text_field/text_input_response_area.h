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
    TextInputResponseArea(const WeakPtr<Pattern>& hostPattern) : hostPattern_(hostPattern) {}
    ~TextInputResponseArea() = default;

    virtual void InitResponseArea() = 0;

    virtual SizeF Measure(LayoutWrapper* layoutWrapper, int32_t index) = 0;

    virtual void Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth) = 0;

    virtual void Refresh() {}

    virtual void ClearArea() {}

    virtual OffsetF GetChildOffset(SizeF parentSize, RectF contentRect, SizeF childSize, float nodeWidth);

    RectF GetAreaRect()
    {
        return areaRect_;
    }

    virtual const RefPtr<FrameNode> GetFrameNode() = 0;

    SizeF GetFrameSize(bool withSafeArea = false);

protected:
    Alignment GetStackAlignment(const TextDirection& userDirection);
    void LayoutChild(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth);
    WeakPtr<Pattern> hostPattern_;
    RectF areaRect_;
};

class PasswordResponseArea : public TextInputResponseArea {
    DECLARE_ACE_TYPE(PasswordResponseArea, TextInputResponseArea);

public:
    PasswordResponseArea(const WeakPtr<Pattern>& hostPattern, bool isObscured)
        : TextInputResponseArea(hostPattern), isObscured_(isObscured) {}
    ~PasswordResponseArea()
    {
        ClearArea();
    }

    void InitResponseArea() override;

    SizeF Measure(LayoutWrapper* layoutWrapper, int32_t index) override;

    void Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth) override;

    void AddEvent(const RefPtr<FrameNode>& node);

    void SetObscured(bool isObscured)
    {
        isObscured_ = isObscured;
        ChangeObscuredState();
    }

    bool IsObscured() const
    {
        return isObscured_;
    }

    void Refresh() override;

    void ClearArea() override
    {
        auto hostPattern = hostPattern_.Upgrade();
        CHECK_NULL_VOID(hostPattern);
        auto host = hostPattern->GetHost();
        CHECK_NULL_VOID(host);
        CHECK_NULL_VOID(stackNode_);
        host->RemoveChildAndReturnIndex(stackNode_);
        passwordNode_.Reset();
        areaRect_.Reset();
    }

    const RefPtr<FrameNode> GetFrameNode() override;

    void OnPasswordIconClicked();

private:
    void LoadImageSourceInfo();
    void AddImageEventOnError();
    void ChangeObscuredState();
    ImageSourceInfo GetDefaultSourceInfo(bool isObscured);
    void UpdateImageSource();
    void UpdateSymbolSource();
    void InitSymbolEffectOptions();
    bool IsShowSymbol();
    bool IsSymbolIcon();
    void ReplaceNode();
    bool IsShowPasswordIcon();
    float GetIconRightOffset();
    float GetIconSize();
    RefPtr<FrameNode> CreateNode();
    std::optional<ImageSourceInfo> GetCurrentSourceInfo()
    {
        return isObscured_ ? hideIcon_ : showIcon_;
    }
    bool isObscured_ = true;
    std::optional<ImageSourceInfo> showIcon_;
    std::optional<ImageSourceInfo> hideIcon_;
    RefPtr<FrameNode> stackNode_;
    WeakPtr<FrameNode> passwordNode_;
};

class UnitResponseArea : public TextInputResponseArea {
    DECLARE_ACE_TYPE(UnitResponseArea, TextInputResponseArea);

public:
    UnitResponseArea(const WeakPtr<Pattern>& hostPattern, const RefPtr<NG::UINode>& unitNode)
        : TextInputResponseArea(hostPattern), unitNode_(std::move(unitNode)) {}
    ~UnitResponseArea()
    {
        ClearArea();
    }

    void InitResponseArea() override;

    SizeF Measure(LayoutWrapper* layoutWrapper, int32_t index) override;

    void Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth) override;

    const RefPtr<FrameNode> GetFrameNode() override;

    void ClearArea() override
    {
        auto hostPattern = hostPattern_.Upgrade();
        CHECK_NULL_VOID(hostPattern);
        auto host = hostPattern->GetHost();
        CHECK_NULL_VOID(host);
        CHECK_NULL_VOID(unitNode_);
        host->RemoveChildAndReturnIndex(unitNode_);
        areaRect_.Reset();
    }

private:
    bool IsShowUnit();
    RefPtr<NG::UINode> unitNode_;
};

class CleanNodeResponseArea : public TextInputResponseArea {
    DECLARE_ACE_TYPE(CleanNodeResponseArea, TextInputResponseArea);

public:
    CleanNodeResponseArea(const WeakPtr<Pattern>& hostPattern) : TextInputResponseArea(hostPattern) {}
    ~CleanNodeResponseArea() = default;

    void InitResponseArea() override;

    SizeF Measure(LayoutWrapper* layoutWrapper, int32_t index) override;

    void Layout(LayoutWrapper* layoutWrapper, int32_t index, float& nodeWidth) override;

    const RefPtr<FrameNode> GetFrameNode() override;

    void UpdateCleanNode(bool isShow);

    bool IsShow() const
    {
        return isShow_;
    }

    void ClearArea() override;

    void Refresh() override;

    float GetIconSize()
    {
        return static_cast<float>(iconSize_.ConvertToPxDistribute(std::optional<float>(), std::optional<float>()));
    }

    bool CheckUpdateCleanNode();

private:
    bool IsShowClean();
    bool IsShowSymbol();
    bool IsSymbolIcon();
    void ReplaceNode();
    void UpdateSymbolSource();
    void InitClickEvent(const RefPtr<FrameNode>& frameNode);
    void SetCancelSymbolIconSize();
    CalcDimension GetSymbolDefaultSize();
    void OnCleanNodeClicked();
    RefPtr<FrameNode> CreateNode();
    void LoadingImageProperty();
    void LoadingCancelButtonColor();
    ImageSourceInfo CreateImageSourceInfo();
    RefPtr<FrameNode> cleanNode_;
    CalcDimension iconSize_ = 0.0_px;
    std::string iconSrc_;
    std::string bundleName_;
    std::string moduleName_;
    Color iconColor_;
    bool isShow_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_RESPONSE_AREA_H

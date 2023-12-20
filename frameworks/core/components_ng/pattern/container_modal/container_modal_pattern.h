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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_accessibility_property.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalPattern : public Pattern {
    DECLARE_ACE_TYPE(ContainerModalPattern, Pattern);

public:
    ContainerModalPattern() = default;
    ~ContainerModalPattern() override = default;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ContainerModalAccessibilityProperty>();
    }

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    }

    void OnWindowFocused() override;

    void OnWindowUnfocused() override;

    virtual void OnWindowForceUnfocused();

    void InitContainerEvent();

    void ShowTitle(bool isShow, bool hasDeco = true, bool needUpdate = false);

    void SetAppTitle(const std::string& title);

    void SetAppIcon(const RefPtr<PixelMap>& icon);

    virtual void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize);

    void SetCloseButtonStatus(bool isEnabled);

    bool GetIsFocus() const
    {
        return isFocus_;
    }

    void SetIsFocus(bool isFocus)
    {
        isFocus_ = isFocus;
    }

    std::string GetAppLabel()
    {
        return appLabel_;
    }

    RefPtr<FrameNode> GetColumnNode()
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    }

    RefPtr<FrameNode> GetFloatingTitleRow()
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    }

    RefPtr<FrameNode> GetControlButtonRow()
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return AceType::DynamicCast<FrameNode>(host->GetChildren().back());
    }

    RefPtr<FrameNode> GetCustomTitleRow()
    {
        auto columnNode = GetColumnNode();
        CHECK_NULL_RETURN(columnNode, nullptr);
        return AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    }

    RefPtr<CustomTitleNode> GetCustomTitleNode()
    {
        auto row = GetCustomTitleRow();
        CHECK_NULL_RETURN(row, nullptr);
        return AceType::DynamicCast<CustomTitleNode>(row->GetChildren().front());
    }

    RefPtr<FrameNode> GetStackNode()
    {
        auto columnNode = GetColumnNode();
        CHECK_NULL_RETURN(columnNode, nullptr);
        return AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    }

    RefPtr<CustomTitleNode> GetFloatingTitleNode()
    {
        auto row = GetFloatingTitleRow();
        CHECK_NULL_RETURN(row, nullptr);
        return AceType::DynamicCast<CustomTitleNode>(row->GetChildren().front());
    }

    void SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow);
    void SetContainerModalTitleHeight(int32_t height);
    int32_t GetContainerModalTitleHeight();
    bool GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons);
    void SubscribeContainerModalButtonsRectChange(
        std::function<void(RectF& containerModal, RectF& buttons)>&& callback);
    void CallButtonsRectChange();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&) override
    {
        CallButtonsRectChange();
        return false;
    }

protected:
    virtual RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex)
    {
        return controlButtonsNode->GetChildAtIndex(originIndex);
    }

    virtual void AddOrRemovePanEvent(const RefPtr<FrameNode>& controlButtonsNode);

    virtual void ChangeFloatingTitle(bool isFocus);

    virtual void ChangeCustomTitle(bool isFocus);

    virtual void ChangeControlButtons(bool isFocus);

    virtual void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus);

    virtual bool CanHideFloatingTitle()
    {
        return true;
    }

    bool CanShowFloatingTitle();

    WindowMode windowMode_;
    bool customTitleSettedShow_ = true;
    bool floatingTitleSettedShow_ = true;
    std::function<void(RectF&, RectF&)> controlButtonsRectChangeCallback_;
    RectF buttonsRect_;
    Dimension titleHeight_ = CONTAINER_TITLE_HEIGHT;

private:
    void WindowFocus(bool isFocus);

    void SetTitleButtonHide(
        const RefPtr<FrameNode>& controlButtonsNode, bool hideSplit, bool hideMaximize, bool hideMinimize);

    std::string appLabel_;
    RefPtr<PanEvent> panEvent_ = nullptr;

    float moveX_ = 0.0f;
    float moveY_ = 0.0f;
    bool hasDeco_ = true;
    bool isFocus_ = true;
    bool hideSplitButton_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H

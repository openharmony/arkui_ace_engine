/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/container_modal_accessibility_property.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"


namespace OHOS::Ace::NG {
enum class ItemPlacementType {
    NONE = -1,
    SIDE_BAR_START = 0,
    SIDE_BAR_END,
    NAV_BAR_START,
    NAV_BAR_END,
    NAVDEST_START,
    NAVDEST_END,
};
class ACE_EXPORT ContainerModalPattern : public Pattern {
    DECLARE_ACE_TYPE(ContainerModalPattern, Pattern);

public:
    ContainerModalPattern() = default;
    ~ContainerModalPattern() override = default;

     void OnColorConfigurationUpdate() override;

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

    void CallSetContainerWindow(bool considerFloatingWindow);

    void OnAttachToFrameNode() override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipeline->AddWindowActivateChangedCallback(host->GetId());
    }

    void OnWindowActivated() override;

    void OnWindowDeactivated() override;

    virtual void OnWindowForceUnfocused();

    virtual void Init();

    virtual void ShowTitle(bool isShow, bool hasDeco = true, bool needUpdate = false);

    void SetAppTitle(const std::string& title);

    void SetAppIcon(const RefPtr<PixelMap>& icon);

    virtual void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose);

    virtual void SetCloseButtonStatus(bool isEnabled);

    virtual void SetWindowContainerColor(const Color& activeColor, const Color& inactiveColor);

    bool GetIsFocus() const
    {
        return isFocus_;
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
        auto title= row->GetChildren().front();
        CHECK_NULL_RETURN(title, nullptr);
        return AceType::DynamicCast<CustomTitleNode>(title->GetChildren().front());
    }

    RefPtr<FrameNode> GetStackNode()
    {
        auto columnNode = GetColumnNode();
        CHECK_NULL_RETURN(columnNode, nullptr);
        return AceType::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(1));
    }

    RefPtr<FrameNode> GetContentNode()
    {
        auto stack = GetStackNode();
        CHECK_NULL_RETURN(stack, nullptr);
        return AceType::DynamicCast<FrameNode>(stack->GetChildren().front());
    }

    RefPtr<CustomTitleNode> GetFloatingTitleNode()
    {
        auto row = GetFloatingTitleRow();
        CHECK_NULL_RETURN(row, nullptr);
        return AceType::DynamicCast<CustomTitleNode>(row->GetChildren().front());
    }

    RefPtr<FrameNode> GetGestureRow()
    {
        auto column = GetColumnNode();
        CHECK_NULL_RETURN(column, nullptr);
        return AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(2));
    }

    RefPtr<CustomTitleNode> GetCustomButtonNode()
    {
        auto row = GetControlButtonRow();
        CHECK_NULL_RETURN(row, nullptr);
        return AceType::DynamicCast<CustomTitleNode>(row->GetChildren().front());
    }
    void UpdateRowHeight(const RefPtr<FrameNode>& row, Dimension height);
    void UpdateGestureRowVisible();
    void SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow);
    bool GetContainerModalTitleVisible(bool isImmersive);
    virtual void SetContainerModalTitleHeight(int32_t height);
    int32_t GetContainerModalTitleHeight();
    virtual bool GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons);
    void SubscribeContainerModalButtonsRectChange(
        std::function<void(RectF& containerModal, RectF& buttons)>&& callback);
    virtual void CallContainerModalNative(const std::string& name, const std::string& value) {};
    virtual void OnContainerModalEvent(const std::string& name, const std::string& value) {};
    void GetWindowPaintRectWithoutMeasureAndLayout(RectInt& rect);
    void GetWindowPaintRectWithoutMeasureAndLayout(Rect& rect, bool isContainerModal);
    void CallButtonsRectChange();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>&, const DirtySwapConfig&) override;

    void OnLanguageConfigurationUpdate() override;

    void InitColumnTouchTestFunc();

    bool GetIsHoveredMenu()
    {
        return isHoveredMenu_;
    }

    Dimension GetCustomTitleHeight();

    virtual void EnableContainerModalGesture(bool isEnable) {}

    virtual bool GetFloatingTitleVisible()
    {
        return false;
    }

    virtual bool GetCustomTitleVisible()
    {
        return false;
    }
    
    virtual bool GetControlButtonVisible()
    {
        return false;
    }

    void InitAllTitleRowLayoutProperty();

    void SetEnableContainerModalCustomGesture(bool enable)
    {
        this->enableContainerModalCustomGesture_ = enable;
    }
    
    static void EnableContainerModalCustomGesture(RefPtr<PipelineContext> pipeline, bool enable);

    void InitToolBarManager();
    void SetToolbarBuilder(const RefPtr<FrameNode>& parent, std::function<RefPtr<UINode>()>&& builder);
    void PrasePlaceMentType();
    bool HandleToolbarItemList(const RefPtr<FrameNode>& parentNode, std::list<RefPtr<UINode>>& list);
    ItemPlacementType GetItemTypeFromTag(const std::string& tag, uint32_t placement);
    void RemoveToolbarItem(const RefPtr<FrameNode>& frameNode);

    void AddToolbarItemToContainer();
    bool AddToolbarItemToRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& node);
    bool AddToolbarItemToSpecificRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavBarStart(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavBarEnd(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavDestStart(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavDestEnd(const RefPtr<FrameNode>& frameNode);

    void AddToolbarRowContainers();
    void AddSideBarDivider(const RefPtr<FrameNode>& customTitleRow, const ToolbarInfo& sideBarInfo);
    void AddNavBarRow(
        const RefPtr<FrameNode>& customTitleRow, const ToolbarInfo& navBarInfo, const ToolbarInfo& sideBarInfo);
    void AddNavBarDivider(const RefPtr<FrameNode>& customTitleRow);
    void AddNavDestBarRow(const RefPtr<FrameNode>& customTitleRow, const ToolbarInfo& navDestInfo);

    void OnToolBarLayoutChange();
    void AdjustNavbarRowWidth();
    void AdjustNavDestRowWidth();
    void AdjustContainerModalTitleHeight();

protected:
    virtual RefPtr<UINode> GetTitleItemByIndex(const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex)
    {
        return controlButtonsNode->GetChildAtIndex(originIndex);
    }

    virtual void AddPanEvent(const RefPtr<FrameNode>& controlButtonsNode);

    virtual void RemovePanEvent(const RefPtr<FrameNode>& controlButtonsNode);

    virtual void ChangeFloatingTitle(bool isFocus);

    virtual void ChangeCustomTitle(bool isFocus);

    virtual void ChangeControlButtons(bool isFocus);

    virtual void ChangeTitleButtonIcon(
        const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus, bool isCloseBtn);

    virtual bool CanHideFloatingTitle()
    {
        return true;
    }

    bool CanShowFloatingTitle();
    bool CanShowCustomTitle();
    Color GetContainerColor(bool isFocus);

    WindowMode windowMode_;
    bool customTitleSettedShow_ = true;
    bool floatingTitleSettedShow_ = true;
    std::function<void(RectF&, RectF&)> controlButtonsRectChangeCallback_;
    RectF buttonsRect_;
    bool isInitButtonsRect_ = false;
    Dimension titleHeight_ = CONTAINER_TITLE_HEIGHT;
    Color activeColor_;
    Color inactiveColor_;
    void InitTitleRowLayoutProperty(RefPtr<FrameNode> titleRow, bool isFloating);

    RefPtr<FrameNode> sideBarDivider_ = nullptr;
    RefPtr<FrameNode> navbarRow_ = nullptr;
    RefPtr<FrameNode> leftNavRow_ = nullptr;
    RefPtr<FrameNode> rightNavRow_ = nullptr;
    RefPtr<FrameNode> navBarDivider_ = nullptr;
    RefPtr<FrameNode> navDestbarRow_ = nullptr;
    RefPtr<FrameNode> leftNavDestRow_ = nullptr;
    RefPtr<FrameNode> rightNavDestRow_ = nullptr;

protected:
    void WindowFocus(bool isFocus);
    void SetTitleButtonHide(
        const RefPtr<FrameNode>& controlButtonsNode, bool hideSplit, bool hideMaximize, bool hideMinimize,
            bool hideClose);
    virtual CalcLength GetControlButtonRowWidth();
    void InitTitle();
    void InitContainerEvent();
    void InitLayoutProperty();
    void InitContainerColor();

    virtual void InitButtonsLayoutProperty();
    virtual void NotifyButtonsRectChange(const RectF& containerModal, const RectF& buttonsRect) {}

    std::string appLabel_;
    RefPtr<PanEvent> panEvent_ = nullptr;

    float moveX_ = 0.0f;
    float moveY_ = 0.0f;
    float toolbarItemMaxHeight_ = 0.0f;
    bool hasDeco_ = true;
    bool isFocus_ = false;
    bool hideSplitButton_ = false;
    bool isHoveredMenu_ = false;
    bool isTitleShow_ = false;
    bool enableContainerModalCustomGesture_ = false;
    RRect windowPaintRect_;
    bool isCustomColor_;

    RefPtr<ToolbarManager> toolbarManager_;

    std::map<ItemPlacementType, std::list<RefPtr<FrameNode>>> itemWillAdd_;
    std::map<RefPtr<FrameNode>, std::list<RefPtr<UINode>>> itemsWillOnTree_;
    std::map<RefPtr<FrameNode>, std::list<RefPtr<UINode>>> itemsOnTree_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_PATTERN_H

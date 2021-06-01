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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_NODE_H

#include <list>

#include "base/geometry/dimension.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/animation/keyframe_animation.h"
#include "core/common/draw_delegate.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components/common/properties/text_style.h"
#include "core/gestures/touch_event.h"
#include "core/pipeline/base/render_context.h"
#include "core/pipeline/base/render_layer.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

extern const Dimension FOCUS_BOUNDARY;

class Component;

// If no insertion location is specified, new child will be added to the end of children list by default.
constexpr int32_t DEFAULT_RENDER_NODE_SLOT = -1;
constexpr int32_t PRESS_DURATION = 100;
constexpr int32_t HOVER_DURATION = 250;

using HoverAndPressCallback = std::function<void(const Color&)>;

// RenderNode is the base class for different render backend, represent a render unit for render pipeline.
class ACE_EXPORT RenderNode : public virtual AceType {
    DECLARE_ACE_TYPE(RenderNode, AceType);

public:
    using OpacityCallback = std::function<void(uint8_t)>;
    using SlipFactorSetting = std::function<void(double)>;
    ~RenderNode() override = default;

    void SetZindex(int32_t zIndex)
    {
        zIndex_ = zIndex;
    }

    int32_t GetZindex() const
    {
        return zIndex_;
    }

    void AddChild(const RefPtr<RenderNode>& child, int32_t slot = DEFAULT_RENDER_NODE_SLOT);

    void RemoveChild(const RefPtr<RenderNode>& child);

    virtual void MoveWhenOutOfViewPort(bool hasEffect);

    void Attach(const WeakPtr<PipelineContext>& context)
    {
        context_ = context;
        OnAttachContext();
    }

    // unmount from render tree
    void Unmount()
    {
        RefPtr<RenderNode> parent = parent_.Upgrade();
        if (parent) {
            parent->MarkNeedLayout();
            parent->RemoveChild(AceType::Claim(this));
        }
    }

    // Update node with attr, style, event, method and so on.
    // This method will call Update virtual function.
    void UpdateAll(const RefPtr<Component>& component);

    virtual void AddToScene() {}

    virtual void Update(const RefPtr<Component>& component) = 0;

    // Called when page context attached, subclass can initialize object which needs page context.
    virtual void OnAttachContext() {}

    void Render()
    {
        if (!needRender_) {
            return;
        }
        PerformRender();
        needRender_ = false;
        OnRenderFinish();
    }

    // Each subclass should override this function for actual render operation.
    virtual void PerformRender() {}

    virtual void FinishRender(const std::unique_ptr<DrawDelegate>& delegate, const Rect& dirty) {}

    virtual void UpdateTouchRect();

    bool NeedLayout() const
    {
        return needLayout_;
    }

    void SetNeedLayout(bool needLayout)
    {
        needLayout_ = needLayout;
    }

    void MarkNeedLayout(bool selfOnly = false, bool forceParent = false);

    void MarkNeedPredictLayout();

    void OnLayout();

    virtual void OnPredictLayout() {}

    virtual Size GetChildViewPort()
    {
        return viewPort_;
    }

    // Called by parent to perform layout.
    void Layout(const LayoutParam& layoutParam)
    {
        auto pipeline = context_.Upgrade();
        if (!pipeline) {
            LOGE("pipeline is null when layout");
            return;
        }

        bool dipScaleChange = pipeline->GetDipScale() != dipScale_;
        dipScale_ = pipeline->GetDipScale();
        if (dipScaleChange || layoutParam_ != layoutParam) {
            layoutParam_ = layoutParam;
            layoutParamChanged_ = true;
            SetNeedLayout(true);
        }

        if (onChangeCallback_) {
            onChangeCallback_();
        }
        OnLayout();
    }

    // Called by parent to update layout param without PerformLayout.
    void SetLayoutParam(const LayoutParam& layoutParam)
    {
        if (layoutParam_ != layoutParam) {
            layoutParam_ = layoutParam;
            layoutParamChanged_ = true;
            MarkNeedLayout();
        }
    }

    const LayoutParam& GetLayoutParam() const
    {
        return layoutParam_;
    }

    // Each subclass should override this function for actual layout operation.
    virtual void PerformLayout() = 0;

    Offset GetPosition() const
    {
        return paintRect_.GetOffset();
    }

    void SetPosition(const Offset& offset);

    void SetAbsolutePosition(const Offset& offset)
    {
        SetPositionInternal(offset);
    }

    Size GetLayoutSize() const
    {
        return paintRect_.GetSize();
    }

    Rect GetRectWithShadow() const;

    void SetShadow(const Shadow& shadow)
    {
        shadow_ = shadow;
        hasShadow_ = true;
    }

    void SetLayoutSize(const Size& size)
    {
        if (paintRect_.GetSize() != size) {
            paintRect_.SetSize(size);
            needUpdateTouchRect_ = true;
            OnSizeChanged();
        }
    }

    static bool SortZIndexCompartor(const WeakPtr<RenderNode>& left, const WeakPtr<RenderNode>& right)
    {
        auto leftChild = left.Upgrade();
        auto rightChild = right.Upgrade();
        if (!leftChild) {
            return false;
        } else if (!rightChild) {
            return true;
        }
        return (leftChild->GetZindex() < rightChild->GetZindex());
    }

    void SortPaintChildrenBasedOnZIndex()
    {
        paintChildren_.clear();
        for (const auto& child: children_) {
            paintChildren_.emplace_back(WeakPtr<RenderNode>(child));
        }
        paintChildren_.sort(SortZIndexCompartor);
    }

    Rect GetRectBasedWindowTopLeft()
    {
        Offset offset = GetGlobalOffset() + touchRect_.GetOffset();
        return Rect(offset, touchRect_.GetSize());
    }

    virtual const Rect& GetTouchRect()
    {
        if (needUpdateTouchRect_) {
            needUpdateTouchRect_ = false;
            UpdateTouchRect();
        }
        return touchRect_;
    }

    const Rect& GetPaintRect() const
    {
        return paintRect_;
    }

    void SetPaintRect(const Rect& rect)
    {
        paintRect_ = rect;
        needUpdateTouchRect_ = true;
    }

    void SetTouchRect(const Rect& rect)
    {
        touchRect_ = rect;
        needUpdateTouchRect_ = false;
    }

    virtual void OnChildAdded(const RefPtr<RenderNode>& child)
    {
        if (slipFactorSetting_) {
            child->SetSlipFactorSetting(slipFactorSetting_);
        }
    }

    virtual void OnChildRemoved(const RefPtr<RenderNode>& child) {}

    const std::string& GetAccessibilityText() const
    {
        return accessibilityText_;
    }

    void SetAccessibilityText(const std::string& accessibilityText)
    {
        accessibilityText_ = accessibilityText;
    }

    virtual void DumpTree(int32_t depth);

    virtual void Dump();

    enum class BridgeType { NONE, AGP, FLUTTER };

    virtual BridgeType GetBridgeType() const
    {
        return BridgeType::NONE;
    }

    void SetNeedRender(bool needRender)
    {
        needRender_ = needRender;
    }

    void MarkNeedRender(bool overlay = false);

    bool NeedRender() const
    {
        return needRender_;
    }

    void SetDepth(int32_t depth)
    {
        depth_ = depth;
    }

    int32_t GetDepth() const
    {
        return depth_;
    }

    PositionType GetPositionType() const
    {
        return positionParam_.type;
    }

    virtual const Dimension& GetLeft() const
    {
        return positionParam_.left.first;
    }

    virtual const Dimension& GetRight() const
    {
        return positionParam_.right.first;
    }

    virtual const Dimension& GetTop() const
    {
        return positionParam_.top.first;
    }

    virtual const Dimension& GetBottom() const
    {
        return positionParam_.bottom.first;
    }

    virtual bool HasLeft() const
    {
        return positionParam_.left.second;
    }

    virtual bool HasRight() const
    {
        return positionParam_.right.second;
    }

    virtual bool HasTop() const
    {
        return positionParam_.top.second;
    }

    virtual bool HasBottom() const
    {
        return positionParam_.bottom.second;
    }

    WeakPtr<RenderNode> GetParent() const
    {
        return parent_;
    }

    WeakPtr<PipelineContext> GetContext() const
    {
        return context_;
    }

    virtual RenderLayer GetRenderLayer()
    {
        return nullptr;
    }

    void SetVisible(bool visible)
    {
        if (visible_ != visible) {
            visible_ = visible;
            AddDirtyRenderBoundaryNode();
            OnVisibleChanged();
        }
        for (auto& child : children_) {
            child->SetVisible(visible);
        }
    }

    virtual bool GetVisible() const
    {
        return visible_;
    }

    virtual void SetHidden(bool hidden)
    {
        if (hidden_ != hidden) {
            hidden_ = hidden;
            AddDirtyRenderBoundaryNode();
            OnHiddenChanged(hidden);
            for (auto& child : children_) {
                child->SetHidden(hidden);
            }
        }
    }

    bool GetHidden() const
    {
        return hidden_;
    }

    bool IsTakenBoundary() const
    {
        return takeBoundary_;
    }

    virtual bool IsRepaintBoundary() const
    {
        return false;
    }

    const std::list<RefPtr<RenderNode>>& GetChildren() const
    {
        return children_;
    }

    void NotifyPaintFinish()
    {
        if (needUpdateAccessibility_) {
            for (auto& child : children_) {
                child->NotifyPaintFinish();
            }
            OnPaintFinish();
        }
    }

    virtual void RenderWithContext(RenderContext& context, const Offset& offset);
    virtual void Paint(RenderContext& context, const Offset& offset);
    virtual void PaintChild(const RefPtr<RenderNode>& child, RenderContext& context, const Offset& offset);

    virtual void OnPaintFinish() {}

    virtual bool TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
        TouchTestResult& result);

    virtual void MouseTest(const Point& globalPoint, const Point& parentLocalPoint, MouseTestResult& result);
    virtual bool MouseHoverTest(const Point& parentLocalPoint);

    virtual bool RotationMatchTest(const RefPtr<RenderNode>& requestRenderNode);

    virtual bool RotationTest(const RotationEvent& event);

    virtual bool RotationTestForward(const RotationEvent& event);

    virtual double GetBaselineDistance(TextBaseline textBaseline);

    virtual bool ScrollPageByChild(Offset& delta, int32_t source);

    // Change render nodes' status
    void ChangeStatus(RenderStatus renderStatus)
    {
        // Myself status should be changed and function achieved by derived class which is component
        OnStatusChanged(renderStatus);

        // Deep traversal
        for (auto& child : children_) {
            child->ChangeStatus(renderStatus);
        }
    }

    Offset GetOffsetFromOrigin(const Offset& offset) const;

    Offset GetGlobalOffset() const;

    // Whether |rect| is in the paint rect of render tree recursively.
    bool IsVisible(const Rect& rect, bool totally = false) const;

    void SetOnChangeCallback(std::function<void()>&& onChangeCallback)
    {
        onChangeCallback_ = std::move(onChangeCallback);
    }

    void SetDisableTouchEvent(bool disableTouchEvent)
    {
        disableTouchEvent_ = disableTouchEvent;
    }

    bool GetDisableTouchEvent() const
    {
        return disableTouchEvent_;
    }

    void SetTextDirection(TextDirection textDirection)
    {
        textDirection_ = textDirection;
    }

    TextDirection GetTextDirection() const
    {
        return textDirection_;
    }

    // Transfer any other dimension unit to logical px.
    // NOTE: context_ MUST be initialized before call this method.
    double NormalizeToPx(Dimension dimension) const;

    // Mainly use this function to convert Percent to Px. Do not call this function in Update().
    double NormalizePercentToPx(const Dimension& dimension, bool isVertical) const;

    // for accessibility
    void SetAccessibilityNode(const WeakPtr<AccessibilityNode>& accessibilityNode)
    {
        accessibilityNode_ = accessibilityNode;
    }

    const WeakPtr<AccessibilityNode>& GetAccessibilityNode() const
    {
        return accessibilityNode_;
    }

    int32_t GetAccessibilityNodeId() const
    {
        auto accessibilityNode = accessibilityNode_.Upgrade();
        if (accessibilityNode) {
            return accessibilityNode->GetNodeId();
        }
        return 0;
    }

    void ClearAccessibilityRect()
    {
        auto node = accessibilityNode_.Upgrade();
        if (node) {
            node->SetRect(Rect());
        }
        for (auto& child : children_) {
            child->ClearAccessibilityRect();
        }
    }

    void SetAccessibilityRect(const Rect& rect)
    {
        Rect parentRect = rect;
        if (!selfOffset_.IsZero()) {
            parentRect.SetOffset(parentRect.GetOffset() + selfOffset_);
        }
        auto node = accessibilityNode_.Upgrade();
        auto content = context_.Upgrade();
        Rect currentRect = Rect(GetGlobalOffset(), GetLayoutSize());
        Rect clampRect = currentRect.Constrain(parentRect);
        if (node && content) {
            if (clampRect.IsValid()) {
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
                node->SetRect(clampRect * content->GetViewScale());
#else
                auto size = Size(clampRect.Width(), clampRect.Height()) * content->GetViewScale();
                if (size.Width() > node->GetWidth() || size.Height() > node->GetHeight()) {
                    // Same AccessibilityNode update the largest size.
                    node->SetWidth(size.Width());
                    node->SetHeight(size.Height());
                    node->SetLeft(clampRect.Left() * content->GetViewScale());
                    node->SetTop(clampRect.Top() * content->GetViewScale());
                } else if (NearEqual(size.Width(), node->GetWidth()) && NearEqual(size.Height(), node->GetHeight())) {
                    // Update the offset when same size.
                    node->SetLeft(clampRect.Left() * content->GetViewScale());
                    node->SetTop(clampRect.Top() * content->GetViewScale());
                }
                if (node->GetTag() == "tab-bar") {
                    return;
                }
#endif
            } else {
                SetAccessibilityVisible(false);
            }
        }
        if (clampRect.IsValid()) {
            for (auto& child : children_) {
                child->SetAccessibilityRect(clampRect);
            }
        }
    }

    void SetNeedUpdateAccessibility(bool needUpdate)
    {
        needUpdateAccessibility_ = needUpdate;
        for (auto& child : children_) {
            child->SetNeedUpdateAccessibility(needUpdate);
        }
    }

    void SetAccessibilityVisible(bool visible)
    {
        auto node = accessibilityNode_.Upgrade();
        if (node) {
            node->SetVisible(visible);
        }
        for (auto& child : children_) {
            child->SetAccessibilityVisible(visible);
        }
    }

    RefPtr<RenderNode> GetLastChild() const;

    RefPtr<RenderNode> GetFirstChild() const;

    Offset GetOffsetToStage() const
    {
        auto offset = GetGlobalOffset();
        auto context = GetContext().Upgrade();
        if (context) {
            offset = offset - context->GetStageRect().GetOffset();
        }
        return offset;
    }

    Offset GetOffsetToPage() const;

    double GetFlexWeight() const
    {
        return flexWeight_;
    }

    int32_t GetDisplayIndex() const
    {
        return displayIndex_;
    }

    OpacityCallback GetOpacityCallback(int32_t domId);

    virtual bool SupportOpacity();

    void GetDomOpacityCallbacks(int32_t domId, std::list<OpacityCallback>& result);

    int32_t GetNodeId() const;

    uint8_t GetOpacity() const;

    virtual void UpdateOpacity(uint8_t opacity);

    bool InterceptTouchEvent() const
    {
        return interceptTouchEvent_;
    }

    void SetInterceptTouchEvent(bool interceptTouchEvent)
    {
        interceptTouchEvent_ = interceptTouchEvent;
    }

    virtual void OnMouseHoverEnterAnimation() {}
    virtual void OnMouseHoverExitAnimation() {}
    virtual void OnMouseClickDownAnimation() {}
    virtual void OnMouseClickUpAnimation() {}
    virtual void StopMouseHoverAnimation() {}

    void CreateMouseAnimation(RefPtr<KeyframeAnimation<Color>>& animation, const Color& from, const Color& to);
    void SetHoverAndPressCallback(const HoverAndPressCallback& callback)
    {
        hoveAndPressCallback_ = callback;
    }

    Color GetEventEffectColor() const
    {
        return eventEffectColor_;
    }

    void UpdateWindowBlurRRect(bool clear = false);

    void WindowBlurTest();

    virtual RRect GetWindowBlurRRect() const
    {
        return RRect::MakeRRect(Rect(Offset::Zero(), GetLayoutSize()), Radius(0.0));
    }

    RRect GetGlobalWindowBlurRRect(std::vector<RRect>& coords) const;

    void MarkNeedWindowBlur(bool flag)
    {
        if (needWindowBlur_ != flag) {
            needWindowBlur_ = flag;
            if (!needWindowBlur_) {
                SetWindowBlurProgress(0.0f);
                SetWindowBlurStyle(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT);
            }
            OnWindowBlurChanged();
        }
    }

    bool NeedWindowBlur() const
    {
        return needWindowBlur_;
    }

    void SetWindowBlurProgress(float progress)
    {
        windowBlurProgress_ = progress;
    }

    float GetWindowBlurProgress() const
    {
        return windowBlurProgress_;
    }

    void SetWindowBlurStyle(WindowBlurStyle style)
    {
        windowBlurStyle_ = style;
    }

    WindowBlurStyle GetWindowBlurStyle() const
    {
        return windowBlurStyle_;
    }

    void SetSlipFactorSetting(const SlipFactorSetting& slipFactorSetting)
    {
        slipFactorSetting_ = slipFactorSetting;
    }

    bool IsInfiniteLayout() const
    {
        return GetLayoutSize().Width() > INT32_MAX || GetLayoutSize().Height() > INT32_MAX;
    }

    bool IsIgnored() const
    {
        return isIgnored_;
    }

    void SetIsIgnored(bool ignore)
    {
        isIgnored_ = ignore;
    }

    bool IsDeclarativeAnimationActive() const
    {
        return declarativeAnimationActive_;
    }

    void SetDeclarativeAnimationActive(bool active)
    {
        declarativeAnimationActive_ = active;
    }

    virtual void OnAppShow()
    {
        isAppOnShow_ = true;
        for (const auto& child : children_) {
            child->OnAppShow();
        }
    }

    virtual void OnAppHide()
    {
        isAppOnShow_ = false;
        for (const auto& child : children_) {
            child->OnAppHide();
        }
    }

    template<typename T>
    RefPtr<T> GetTheme() const
    {
        auto context = context_.Upgrade();
        if (!context) {
            return nullptr;
        }
        auto themeManager = context->GetThemeManager();
        if (!themeManager) {
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }

    virtual bool HasEffectiveTransform() const;

    Rect GetDirtyRect() const;

protected:
    explicit RenderNode(bool takeBoundary = false);
    virtual void ClearRenderObject();
    // Each subclass override this to return touch target object which is used to receive touch event.
    // For convenience, it is recommended to return directly to the corresponding gesture recognizer.
    // Sees gestures directory.
    // Uses coordinateOffset for recognizer to calculate the local location of the touch point.
    // Uses touchRestrict for restrict gesture recognition in some sense.
    virtual void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
    {}

    virtual void OnMouseTestHit(const Offset& coordinateOffset, MouseTestResult& result) {}
    virtual void OnMouseHoverEnterTest() {}
    virtual void OnMouseHoverExitTest() {}

    void PrepareLayout();

    void SetParent(const WeakPtr<RenderNode>& parent)
    {
        parent_ = parent;
    }

    void TakeBoundary(bool taken = true)
    {
        takeBoundary_ = taken;
    }

    bool IsLayoutParamChanged() const
    {
        return layoutParamChanged_;
    }

    virtual void OnGlobalPositionChanged()
    {
        for (const auto& child : children_) {
            if (child) {
                child->OnGlobalPositionChanged();
            }
        }
    };
    virtual void OnPositionChanged() {};
    virtual void OnSizeChanged() {};
    virtual void OnVisibleChanged() {};
    virtual void OnRenderFinish() {};
    virtual void OnStatusChanged(RenderStatus renderStatus) {};
    virtual void OnHiddenChanged(bool hidden) {};
    virtual void OnWindowBlurChanged() {};
    virtual bool MarkNeedRenderSpecial();

    double GetHighestChildBaseline(TextBaseline baseline);
    double GetFirstChildBaseline(TextBaseline baseline);
    void UpdateAccessibilityPosition();

    RefPtr<ThemeManager> GetThemeManager() const
    {
        auto context = context_.Upgrade();
        if (!context) {
            return nullptr;
        }
        return context->GetThemeManager();
    }

    WeakPtr<PipelineContext> context_;
    Size viewPort_;
    Point globalPoint_;
    WeakPtr<AccessibilityNode> accessibilityNode_;
    Rect touchRect_;
    PositionParam positionParam_;
    uint8_t opacity_ = 255;
    Shadow shadow_;

    float windowBlurProgress_ = 0.0f;
    WindowBlurStyle windowBlurStyle_ = WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT;
    bool touchable_ = true;
    bool interceptTouchEvent_ = false;
    bool needWindowBlur_ = false;
    bool needUpdateAccessibility_ = true;
    bool disabled_ = false;

    MouseState mouseState_ = MouseState::NONE;
    SlipFactorSetting slipFactorSetting_;

    HoverAndPressCallback hoveAndPressCallback_;

    // hover or press color
    Color eventEffectColor_ = Color::TRANSPARENT;
    std::function<void(const std::string&)> onLayoutReady_;

    bool isAppOnShow_ = true;

private:
    void AddDirtyRenderBoundaryNode()
    {
        if (visible_ && !hidden_ && IsRepaintBoundary()) {
            auto pipelineContext = context_.Upgrade();
            if (pipelineContext == nullptr) {
                return;
            }
            pipelineContext->AddDirtyRenderNode(AceType::Claim(this));
        }
    }

    void SetPositionInternal(const Offset& offset);

    std::list<RefPtr<RenderNode>> hoverChildren_;
    std::list<WeakPtr<RenderNode>> paintChildren_;
    std::list<RefPtr<RenderNode>> children_;
    std::string accessibilityText_;
    LayoutParam layoutParam_;
    Rect paintRect_;
    WeakPtr<RenderNode> parent_;
    int32_t depth_ = 0;
    bool needRender_ = false;
    bool needLayout_ = false;
    bool visible_ = true;
    bool takeBoundary_ = false;
    bool layoutParamChanged_ = false;
    bool disableTouchEvent_ = false;
    bool needUpdateTouchRect_ = false;
    bool hasShadow_ = false;

    double flexWeight_ = 0.0;
    int32_t displayIndex_ = 1;

    double dipScale_ = 0.0;

    TextDirection textDirection_ { TextDirection::LTR };
    Offset selfOffset_ { 0, 0 };

    bool hidden_ = false;
    bool isIgnored_ = false;
    bool declarativeAnimationActive_ = false;
    std::function<void()> onChangeCallback_;
    ACE_DISALLOW_COPY_AND_MOVE(RenderNode);

    int32_t zIndex_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_NODE_H

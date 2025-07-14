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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H

#include <optional>

#include "ui/properties/dirty_flag.h"

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "base/view_data/view_data_wrap.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/pattern_resource_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_property.h"
#include "core/event/pointer_event.h"
#include "core/common/container_consts.h"

struct _ArkUINodeAdapter;
typedef _ArkUINodeAdapter* ArkUINodeAdapterHandle;

namespace OHOS::Accessibility {
class AccessibilityElementInfo;
class AccessibilityEventInfo;
}

namespace OHOS::Ace::NG {
class AccessibilitySessionAdapter;
class InspectorFilter;

class ScrollingListener : public AceType {
    DECLARE_ACE_TYPE(ScrollingListener, AceType);

public:
    explicit ScrollingListener(std::function<void()>&& callback) : callback_(std::move(callback)) {}

    ~ScrollingListener() override = default;

    void NotifyScrollingEvent()
    {
        if (callback_) {
            callback_();
        }
    }

private:
    std::function<void()> callback_;
};

// Pattern is the base class for different measure, layout and paint behavior.
class ACE_FORCE_EXPORT Pattern : public virtual AceType {
    DECLARE_ACE_TYPE(Pattern, AceType);

public:
    Pattern() = default;
    ~Pattern() override = default;

    // atomic node is like button, image, custom node and so on.
    // In ets UI compiler, the atomic node does not Add Pop function, only have Create function.
    virtual bool IsAtomicNode() const
    {
        return true;
    }

    virtual bool ConsumeChildrenAdjustment(const OffsetF& /* offset */)
    {
        return false;
    }

    virtual void OnForegroundColorUpdate() {}

    virtual void ProcessSafeAreaPadding() {}

    virtual bool IsNeedPercent() const
    {
        return false;
    }

    virtual bool CheckCustomAvoidKeyboard() const
    {
        return false;
    }

    virtual bool IsSupportDrawModifier() const
    {
        return true;
    }

    // The pattern needs softkeyboard is like search, rich editor, text area, text field pattern.
    virtual bool NeedSoftKeyboard() const
    {
        return false;
    }

    virtual bool NeedToRequestKeyboardOnFocus() const
    {
        return true;
    }

    virtual bool DefaultSupportDrag()
    {
        return false;
    }

    virtual bool IsEnableMatchParent()
    {
        return false;
    }

    virtual bool IsEnableChildrenMatchParent()
    {
        return false;
    }

    virtual bool IsEnableFix()
    {
        return false;
    }

    virtual std::optional<RenderContext::ContextParam> GetContextParam() const
    {
        return std::nullopt;
    }

    void DetachFromFrameNode(FrameNode* frameNode)
    {
        onDetach_ = true;
        OnDetachFromFrameNode(frameNode);
        onDetach_ = false;
        frameNode_.Reset();
    }

    void AttachToFrameNode(const WeakPtr<FrameNode>& frameNode)
    {
        if (frameNode_ == frameNode) {
            return;
        }
        frameNode_ = frameNode;
        OnAttachToFrameNode();
    }

    virtual bool CustomizeExpandSafeArea()
    {
        return false;
    }

    virtual RefPtr<AccessibilityProperty> CreateAccessibilityProperty()
    {
        return MakeRefPtr<AccessibilityProperty>();
    }

    virtual RefPtr<PaintProperty> CreatePaintProperty()
    {
        return MakeRefPtr<PaintProperty>();
    }

    virtual RefPtr<LayoutProperty> CreateLayoutProperty()
    {
        return MakeRefPtr<LayoutProperty>();
    }

    virtual RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm()
    {
        return MakeRefPtr<BoxLayoutAlgorithm>();
    }

    virtual RefPtr<NodePaintMethod> CreateNodePaintMethod()
    {
        return nullptr;
    }

    virtual RefPtr<NodePaintMethod> CreateDefaultNodePaintMethod()
    {
        return MakeRefPtr<NodePaintMethod>();
    }

    virtual std::optional<RectF> GetOverridePaintRect() const
    {
        return std::nullopt;
    }

    virtual RefPtr<EventHub> CreateEventHub()
    {
        return MakeRefPtr<EventHub>();
    }

    virtual void OnContextAttached() {}

    virtual OPINC_TYPE_E OpIncType()
    {
        return OPINC_NODE_POSSIBLE;
    }

    virtual void OnModifyDone()
    {
        CheckLocalized();
        auto frameNode = GetHost();
        const auto& children = frameNode->GetChildren();
        if (children.empty()) {
            return;
        }
        const auto& renderContext = frameNode->GetRenderContext();
        if (!renderContext->HasForegroundColor() && !renderContext->HasForegroundColorStrategy()) {
            return;
        }
        std::list<RefPtr<FrameNode>> childrenList {};
        std::queue<RefPtr<FrameNode>> queue {};
        queue.emplace(frameNode);
        RefPtr<FrameNode> parentNode;
        while (!queue.empty()) {
            parentNode = queue.front();
            queue.pop();
            auto childs = parentNode->GetChildren();
            if (childs.empty()) {
                continue;
            }
            for (auto child : childs) {
                if (!AceType::InstanceOf<NG::FrameNode>(child)) {
                    continue;
                }
                auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
                auto childRenderContext = childFrameNode->GetRenderContext();
                if (childRenderContext->HasForegroundColorFlag() && childRenderContext->GetForegroundColorFlagValue()) {
                    continue;
                }
                queue.emplace(childFrameNode);
                childrenList.emplace_back(childFrameNode);
            }
        }
        UpdateChildRenderContext(renderContext, childrenList);
    }

    void UpdateChildRenderContext(
        const RefPtr<RenderContext>& renderContext, std::list<RefPtr<FrameNode>>& childrenList)
    {
        bool isForegroundColor = renderContext->HasForegroundColor();
        for (auto child : childrenList) {
            auto childRenderContext = child->GetRenderContext();
            if (!childRenderContext->HasForegroundColor() && !childRenderContext->HasForegroundColorStrategy()) {
                if (isForegroundColor) {
                    childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
                    childRenderContext->ResetForegroundColorStrategy();
                    childRenderContext->UpdateForegroundColorFlag(false);
                } else {
                    childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
                    childRenderContext->ResetForegroundColor();
                    childRenderContext->UpdateForegroundColorFlag(false);
                }
            } else {
                if (!childRenderContext->HasForegroundColorFlag()) {
                    continue;
                }
                if (childRenderContext->GetForegroundColorFlagValue()) {
                    continue;
                }
                if (isForegroundColor) {
                    childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
                    childRenderContext->ResetForegroundColorStrategy();
                    childRenderContext->UpdateForegroundColorFlag(false);
                } else {
                    childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
                    childRenderContext->ResetForegroundColor();
                    childRenderContext->UpdateForegroundColorFlag(false);
                }
            }
        }
    }

    virtual void OnAfterModifyDone() {}

    virtual void OnMountToParentDone() {}

    virtual void AfterMountToParent() {}

    virtual void OnSensitiveStyleChange(bool isSensitive) {}

    virtual bool AllowVisibleAreaCheck() const
    {
        return false;
    }

    virtual bool IsRootPattern() const
    {
        return false;
    }

    virtual bool IsMeasureBoundary() const
    {
        return false;
    }

    virtual bool IsRenderBoundary() const
    {
        return true;
    }

    virtual void NotifyForNextTouchEvent() {}

    virtual bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& /*dirty*/, bool /*skipMeasure*/, bool /*skipLayout*/)
    {
        return false;
    }

    virtual void BeforeSyncGeometryProperties(const DirtySwapConfig& config) {}
    virtual void OnSyncGeometryNode(const DirtySwapConfig& config) {}

    // Called on main thread to check if need rerender of the content.
    virtual bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& /*dirty*/, const DirtySwapConfig& /*changeConfig*/)
    {
        return false;
    }

    virtual bool UsResRegion()
    {
        return true;
    }

    std::optional<SizeF> GetHostFrameSize() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetMarginFrameSize();
    }

    std::optional<OffsetF> GetHostFrameOffset() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameOffset();
    }

    std::optional<OffsetF> GetHostFrameGlobalOffset() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameOffset() + frameNode->GetGeometryNode()->GetParentGlobalOffset();
    }

    std::optional<SizeF> GetHostContentSize() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        const auto& content = frameNode->GetGeometryNode()->GetContent();
        if (!content) {
            return std::nullopt;
        }
        return content->GetRect().GetSize();
    }

    RefPtr<FrameNode> GetHost() const
    {
        if (onDetach_ && SystemProperties::DetectGetHostOnDetach()) {
            LOGF_ABORT("fatal: can't GetHost at detaching period");
        }
        return frameNode_.Upgrade();
    }

    int32_t GetHostInstanceId() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, INSTANCE_ID_UNDEFINED);
        return host->GetInstanceId();
    }

    PipelineContext* GetContext() const
    {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode->GetContext();
    }

    RenderContext* GetRenderContext() const
    {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode->GetRenderContext().GetRawPtr();
    }

    virtual void DumpInfo() {}
    virtual void DumpInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpAdvanceInfo() {}
    virtual void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData = false) {}
    virtual void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) {}
    virtual void NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap,
        RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType) {}
    virtual void NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent = "", bool isPopup = false) {}
    virtual bool CheckAutoSave()
    {
        return false;
    }

    template<typename T>
    RefPtr<T> GetLayoutProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetLayoutProperty<T>());
    }

    template<typename T>
    RefPtr<T> GetPaintProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetPaintProperty<T>());
    }

    template<typename T>
    RefPtr<T> GetOrCreateEventHub() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetOrCreateEventHub<T>());
    }

    void MarkDirty(PropertyChangeFlag flag = PROPERTY_UPDATE_MEASURE_SELF)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(flag);
    }

    // Called after frameNode RebuildRenderContextTree.
    virtual void OnRebuildFrame() {}
    // Called before frameNode CreateLayoutWrapper.
    virtual void BeforeCreateLayoutWrapper() {}
    // Called before frameNode CreatePaintWrapper.
    virtual void BeforeCreatePaintWrapper() {}

    virtual FocusPattern GetFocusPattern() const
    {
        return { FocusType::DISABLE, false, FocusStyleType::NONE };
    }

    virtual ScopeFocusAlgorithm GetScopeFocusAlgorithm()
    {
        return ScopeFocusAlgorithm();
    }

    virtual bool ScrollToNode(const RefPtr<FrameNode>& focusFrameNode)
    {
        return false;
    }

    virtual int32_t GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode)
    {
        return -1;
    }

    virtual void ScrollToFocusNodeIndex(int32_t index) {}

    // out of viewport or visible is none or gone.
    virtual void OnInActive() {}
    virtual void OnActive() {}

    // called by window life cycle.
    virtual void OnWindowShow() {}
    virtual void OnWindowHide() {}
    virtual void OnWindowFocused() {}
    virtual void OnWindowUnfocused() {}
    virtual void OnWindowActivated() {}
    virtual void OnWindowDeactivated() {}
    virtual void OnPixelRoundFinish(const SizeF& pixelGridRoundSize) {}
    virtual void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) {}
    virtual void OnNotifyMemoryLevel(int32_t level) {}

    // get XTS inspector value
    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

    virtual void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const {}

    // call by recycle framework.
    virtual void OnRecycle() {}
    virtual void OnReuse() {}

    virtual void OnAttachToMainTree() {}
    virtual void OnAttachToBuilderNode(NodeStatus nodeStatus) {}

    virtual void OnDetachFromMainTree() {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    virtual void OnAreaChangedInner() {}
    virtual void OnVisibleChange(bool isVisible) {}
    virtual std::string ProvideRestoreInfo()
    {
        return "";
    }

    virtual void OnRestoreInfo(const std::string& restoreInfo) {}

    virtual bool IsNeedAdjustByAspectRatio()
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto layoutProperty = host->GetLayoutProperty();
        CHECK_NULL_RETURN(host, false);
        return layoutProperty->HasAspectRatio();
    }

    virtual void OnTouchTestHit(SourceType hitTestType) {}

    virtual int32_t GetDragRecordSize()
    {
        return -1;
    }

    virtual bool OnBackPressedCallback()
    {
        return false;
    }

    virtual void HandleOnDragStatusCallback(
        const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent) {};

    virtual void HandleDragEvent(const DragPointerEvent& info) {};
    virtual void OnLanguageConfigurationUpdate() {}
    virtual void OnColorConfigurationUpdate() {}
    virtual void OnColorModeChange(uint32_t colorMode);
    virtual void OnDirectionConfigurationUpdate() {}
    virtual void OnDpiConfigurationUpdate() {}
    virtual void OnIconConfigurationUpdate() {}
    virtual void OnFontConfigurationUpdate() {}
    virtual void OnFontScaleConfigurationUpdate() {}
    virtual void OnForegroundColorUpdate(const Color& value) {}

    virtual bool ShouldDelayChildPressedState() const
    {
        return false;
    }

    virtual bool ShouldPreventChildPressedState() const
    {
        return false;
    }

    virtual void RegisterScrollingListener(const RefPtr<ScrollingListener> listener) {}
    virtual void FireAndCleanScrollingListener() {}
    virtual void CleanScrollingListener() {}
    virtual void ResetDragOption() {}

    virtual int64_t WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
    {
        return -1;
    }

    virtual void SearchExtensionElementInfoByAccessibilityId(int64_t elementId, int32_t mode,
        int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) {}
    virtual void SearchElementInfosByText(int64_t elementId, const std::string& text,
        int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) {}
    virtual void FindFocusedElementInfo(int64_t elementId, int32_t focusType,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) {}
    virtual void FocusMoveSearch(int64_t elementId, int32_t direction,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) {}
    virtual bool TransferExecuteAction(
        int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
    {
        return false;
    }

    virtual RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter()
    {
        return nullptr;
    }

    virtual int32_t GetUiExtensionId()
    {
        return -1;
    }

    GestureEventFunc GetLongPressEventRecorder()
    {
        auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
            if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
                return;
            }
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto inspectorId = host->GetInspectorId().value_or("");
            auto text = host->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetGroupText(true);
            auto desc = host->GetAutoEventParamValue("");

            Recorder::EventParamsBuilder builder;
            builder.SetId(inspectorId)
                .SetType(host->GetTag())
                .SetEventType(Recorder::LONG_PRESS)
                .SetText(text)
                .SetHost(host)
                .SetDescription(desc);
            if (Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_RECT)) {
                auto rect = host->GetTransformRectRelativeToWindow().ToBounds();
                builder.SetExtra(Recorder::KEY_NODE_RECT, std::move(rect));
            }
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        };
        return longPressCallback;
    }

    virtual void OnAttachContext(PipelineContext *context) {}
    virtual void OnDetachContext(PipelineContext *context) {}
    virtual void SetFrameRateRange(const RefPtr<FrameRateRange>& rateRange, SwiperDynamicSyncSceneType type) {}

    void CheckLocalized()
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
        if (layoutProperty->IsPositionLocalizedEdges()) {
            layoutProperty->CheckPositionLocalizedEdges(layoutDirection);
        }
        layoutProperty->CheckMarkAnchorPosition(layoutDirection);
        if (layoutProperty->IsOffsetLocalizedEdges()) {
            layoutProperty->CheckOffsetLocalizedEdges(layoutDirection);
        }
        layoutProperty->CheckLocalizedPadding(layoutProperty, layoutDirection);
        layoutProperty->CheckLocalizedMargin(layoutProperty, layoutDirection);
        layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, layoutDirection);
        layoutProperty->CheckLocalizedEdgeColors(layoutDirection);
        layoutProperty->CheckLocalizedBorderRadiuses(layoutDirection);
        layoutProperty->CheckLocalizedOuterBorderColor(layoutDirection);
        layoutProperty->CheckLocalizedBorderImageSlice(layoutDirection);
        layoutProperty->CheckLocalizedBorderImageWidth(layoutDirection);
        layoutProperty->CheckLocalizedBorderImageOutset(layoutDirection);
        layoutProperty->CheckLocalizedAlignment(layoutDirection);
        // Reset for safeAreaExpand's Cache in GeometryNode
        host->ResetSafeAreaPadding();
        layoutProperty->CheckLocalizedSafeAreaPadding(layoutDirection);
        layoutProperty->CheckIgnoreLayoutSafeArea(layoutDirection);
        layoutProperty->CheckBackgroundLayoutSafeAreaEdges(layoutDirection);
    }

    virtual void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) {}

    virtual uint32_t GetWindowPatternType() const
    {
        return 0;
    }

    virtual bool IsResponseRegionExpandingNeededForStylus(const TouchEvent& touchEvent) const
    {
        return false;
    }

    virtual RectF ExpandDefaultResponseRegion(RectF& rect)
    {
        return RectF();
    }

    virtual void NotifyDataChange(int32_t index, int32_t count) {};

    virtual bool RenderCustomChild(int64_t deadline)
    {
        return true;
    }

    virtual bool TriggerAutoSaveWhenInvisible()
    {
        return false;
    }

    virtual void AddInnerOnGestureRecognizerJudgeBegin(
        GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc) {};

    virtual void RecoverInnerOnGestureRecognizerJudgeBegin() {};

    virtual bool OnThemeScopeUpdate(int32_t themeScopeId)
    {
        return false;
    }

    void AddResObj(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);

    void RemoveResObj(const std::string& key);

    void AddResCache(const std::string& key, const std::string& value);

    std::string GetResCacheMapByKey(const std::string& key);

    int32_t GetThemeScopeId() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, 0);
        return host->GetThemeScopeId();
    }

    virtual bool ReusedNodeSkipMeasure()
    {
        return false;
    }

    virtual void OnFocusNodeChange(FocusReason focusReason) {}
    virtual void OnCollectRemoved() {}
    virtual std::string GetCurrentLanguage()
    {
        return nullptr;
    };
    virtual void GetTranslateText(
        std::string extraData, std::function<void(std::string)> callback, bool isContinued) {};
    virtual void SendTranslateResult(std::vector<std::string> results, std::vector<int32_t> ids) {};
    virtual void EndTranslate() {};
    virtual void SendTranslateResult(std::string results) {};
    int32_t OnRecvCommand(const std::string& command);
    virtual int32_t OnInjectionEvent(const std::string& command)
    {
        return RET_SUCCESS;
    };

    virtual bool BorderUnoccupied() const
    {
        return false;
    }

    virtual void UnRegisterResource(const std::string& key);

    template<typename T>
    void RegisterResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
    {
        if (resourceMgr_ == nullptr) {
            resourceMgr_ = MakeRefPtr<PatternResourceManager>();
        }
        auto&& propUpdateFunc = [weakptr = AceType::WeakClaim(this)](
                                    const std::string& key, const RefPtr<PropertyValueBase>& valueBase) {
            auto pattern = weakptr.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePropertyImpl(key, valueBase);
        };
        resourceMgr_->RegisterResource<T>(std::move(propUpdateFunc), key, resObj, value);
    }

    virtual void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> valueBase) {};

    virtual bool OnAttachAdapter(const RefPtr<FrameNode>& node, const RefPtr<UINode>& child)
    {
        return false;
    }

    virtual void UpdateBorderResource() {};
    virtual void UpdateMarginResource() {};
    virtual bool DetachHostNodeAdapter(const RefPtr<FrameNode>& node)
    {
        return false;
    }
    virtual bool GetNodeAdapterComponent(ArkUINodeAdapterHandle handle, const RefPtr<FrameNode>& node)
    {
        return false;
    }
    virtual bool ChildPreMeasureHelperEnabled()
    {
        return false;
    }
    virtual bool ChildPreMeasureHelperCustomized()
    {
        return false;
    }
    virtual bool ChildPreMeasureHelper(
        LayoutWrapper* layoutWrapper, const std::optional<LayoutConstraintF>& parentConstraint)
    {
        return false;
    }
    virtual bool AccumulatingTerminateHelper(RectF& adjustingRect, ExpandEdges& totalExpand, bool fromSelf = false,
        LayoutSafeAreaType ignoreType = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM)
    {
        return false;
    }
    virtual bool PostponedTaskForIgnoreEnabled()
    {
        return false;
    }
    virtual bool PostponedTaskForIgnoreCustomized()
    {
        return false;
    }
    virtual void PostponedTaskForIgnore() {}
    virtual bool NeedCustomizeSafeAreaPadding()
    {
        return false;
    }
    virtual PaddingPropertyF CustomizeSafeAreaPadding(PaddingPropertyF safeAreaPadding, bool needRotate)
    {
        return safeAreaPadding;
    }
    virtual bool ChildTentativelyLayouted(IgnoreStrategy& strategy)
    {
        return false;
    }

protected:
    virtual void OnAttachToFrameNode() {}
    virtual void OnDetachFromFrameNode(FrameNode* frameNode) {}

    WeakPtr<FrameNode> frameNode_;
    RefPtr<PatternResourceManager> resourceMgr_;

private:
    bool onDetach_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(Pattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H

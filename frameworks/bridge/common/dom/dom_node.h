/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H

#include <string>
#include <unordered_map>

#include "base/geometry/transform_util.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/animation/animation_util.h"
#include "core/animation/keyframe_animation.h"
#include "core/animation/property_animation.h"
#include "core/components/box/box_component.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/declaration/common/declaration_creator_manager.h"
#include "core/components/display/display_component.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/focusable/focusable_component.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/components/list/list_component.h"
#include "core/components/mouse_listener/mouse_listener_component.h"
#include "core/components/page_transition/page_transition_component.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/shared_transition/shared_transition_component.h"
#include "core/components/stack/stack_component.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components/theme/theme_utils.h"
#include "core/components/touch_listener/touch_listener_component.h"
#include "core/components/transform/transform_component.h"
#include "core/components/transition/transition_component.h"
#include "core/components/tween/tween_component.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/utils/transform_convertor.h"
#include "frameworks/core/animation/animatable_data.h"

#ifndef WEARABLE_PRODUCT
#include "core/components/multimodal/multimodal_component.h"
#endif

namespace OHOS::Ace::Framework {

// If no insertion location is specified, new child will be added to the end of children list by default.
inline constexpr int32_t DEFAULT_ITEM_INDEX = -1;

class ACE_FORCE_EXPORT DOMNode : public virtual AceType {
    DECLARE_ACE_TYPE(DOMNode, AceType);

public:
    DOMNode(NodeId nodeId, const std::string& nodeName);
    ~DOMNode() override;

    void SetAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);
    bool ParseAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);
    void SetSharedTransitionStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);
    bool ParseTransitionPropertyStyle(const std::string& transitionProperty);
    bool ParseTransitionNameStyle(const std::string& transitionName);
    void CreateDeclaration(const std::string& tag);
    void TweenOptionSetKeyframes(TweenOption& tweenOption);
    void SetCustomAnimationStyleUpdate(bool enable);
    void AddNode(const RefPtr<DOMNode>& node, int32_t slot = DEFAULT_ITEM_INDEX);
    void RemoveNode(const RefPtr<DOMNode>& node);
    virtual void Mount(int32_t slot);
    void GenerateComponentNode();
    virtual void OnPageLoadFinish() {}

    virtual void SetShowAttr(const std::string& showValue);

    virtual const RefPtr<ScrollComponent>& GetScrollComponent() const
    {
        return scrollComponent_;
    }

    void MarkNeedUpdate();

    void SetTweenComponent(const RefPtr<TweenComponent>& tweenComponent)
    {
        tweenComponent_ = tweenComponent;
        if (!displayComponent_) {
            displayComponent_ = AceType::MakeRefPtr<DisplayComponent>(rootComponent_->GetChild());
        }
        if (!transformComponent_) {
            transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
        }
    }

    RefPtr<TweenComponent> GetTweenComponent() const
    {
        return tweenComponent_;
    }

    const std::list<RefPtr<DOMNode>>& GetChildList() const
    {
        return children_;
    }

    const RefPtr<Declaration>& GetDeclaration() const
    {
        return declaration_;
    }

    const RefPtr<ComposedComponent>& GetRootComponent() const
    {
        return rootComponent_;
    }

    const RefPtr<BoxComponent>& GetBoxComponent() const
    {
        return boxComponent_;
    }

    const RefPtr<DisplayComponent>& GetDisplayComponent() const
    {
        return displayComponent_;
    }

    const RefPtr<TouchListenerComponent>& GetTouchListenerComponent() const
    {
        return touchEventComponent_;
    }

    const RefPtr<MouseListenerComponent>& GetMouseListenerComponent() const
    {
        return mouseEventComponent_;
    }

    const RefPtr<GestureListenerComponent>& GetGestureListenerComponent() const
    {
        return gestureEventComponent_;
    }

    const RefPtr<FocusableComponent>& GetFocusableComponent() const
    {
        return focusableEventComponent_;
    }

    const RefPtr<TransformComponent>& GetTransformComponent() const
    {
        return transformComponent_;
    }

    void SetShareId(const std::string& shareId)
    {
        shareId_ = shareId;
        if (declaration_) {
            declaration_->SetShareId(shareId);
        }
    }

    const std::string& GetShareId() const
    {
        return shareId_;
    }

    const RefPtr<PageTransitionComponent>& BuildTransitionComponent();

    // Ensure DOMPopup can response onClick event even without defining it.
    void SetOnClick(const EventMarker& eventMarker)
    {
        ACE_DCHECK(gestureEventComponent_);
        gestureEventComponent_->SetOnClickId(eventMarker);
    }

    void SetOnDoubleClick(const EventMarker& eventMarker)
    {
        ACE_DCHECK(gestureEventComponent_);
        gestureEventComponent_->SetOnDoubleClickId(eventMarker);
    }

    void SetOnDragStart(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnFreeDragStartId(eventMarker);
    }

    void SetOnDrag(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnFreeDragUpdateId(eventMarker);
    }

    void SetOnDragEnd(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnFreeDragEndId(eventMarker);
    }

    void SetOnLongPress(const EventMarker& eventMarker)
    {
        ACE_DCHECK(gestureEventComponent_);
        gestureEventComponent_->SetOnLongPressId(eventMarker);
    }

    void SetOnPinchStart(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnPinchStartId(eventMarker);
    }

    void SetOnPinchUpdate(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnPinchUpdateId(eventMarker);
    }

    void SetOnPinchEnd(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnPinchEndId(eventMarker);
    }

    void SetOnPinchCancel(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnPinchCancelId(eventMarker);
    }

    void SetIsRootNode(bool isRootNode)
    {
        isRootNode_ = isRootNode;
    }

    bool IsRootNode() const
    {
        return isRootNode_;
    }

    void SetIsTransition(bool isTransition)
    {
        isTransition_ = isTransition;
    }

    bool GetIsTransition() const
    {
        return isTransition_;
    }

    void SetOnFocusClick(const EventMarker& eventMarker);

    bool IsNodeDisabled() const;

    void SetIsEnter(bool isEnter)
    {
        isEnter_ = isEnter;
    }

    bool GetIsEnter() const
    {
        return isEnter_;
    }

    NodeId GetNodeId() const
    {
        return nodeId_;
    }

    std::string GetNodeIdForEvent() const;

    const std::string& GetTag() const
    {
        return tag_;
    }

    void SetProxyNode(bool isProxy)
    {
        isProxy_ = isProxy;
    }

    bool IsProxy() const
    {
        return isProxy_;
    }

    bool IsShow() const
    {
        double opacity = 1.0;
        if (declaration_) {
            auto& opacityStyle =
                static_cast<CommonOpacityStyle&>(declaration_->GetStyle(StyleTag::COMMON_OPACITY_STYLE));
            if (opacityStyle.IsValid()) {
                opacity = opacityStyle.opacity;
            }
        }
        return visible_ == VisibleType::VISIBLE && !NearZero(opacity);
    }

    Color GetBackGroundColor() const
    {
        Color color = Color::TRANSPARENT;
        if (declaration_ && isTransitionColor_) {
            auto& style =
                static_cast<CommonBackgroundStyle&>(declaration_->GetStyle(StyleTag::COMMON_BACKGROUND_STYLE));
            if (style.IsValid()) {
                color = style.backgroundColor;
            }
        }
        return color;
    }

    double GetOpacity() const
    {
        double opacity = 1.0;
        if (declaration_) {
            auto& style = static_cast<CommonOpacityStyle&>(declaration_->GetStyle(StyleTag::COMMON_OPACITY_STYLE));
            if (style.IsValid()) {
                opacity = style.opacity;
            }
        }
        return opacity;
    }

    NodeId GetParentId() const
    {
        return parentId_;
    }

    RefPtr<DOMNode> GetParentNode() const
    {
        return parentNode_.Upgrade();
    }

    bool IsTabbarSubNode() const;

    void SetParentNode(const RefPtr<DOMNode>& parentNode)
    {
        if (!parentNode) {
            return;
        }
        parentNode_ = parentNode;
        parentId_ = parentNode->GetNodeId();
        parentTag_ = parentNode->GetTag();

        if (tag_ == DOM_NODE_TAG_SVG || parentNode->HasSvgTag()) {
            hasSvgTag_ = true;
        }
    }

    int32_t GetPageId() const
    {
        return pageId_;
    }
    void SetPageId(int32_t pageId)
    {
        pageId_ = pageId;
    }

    // Subclasses need to implement this interface to return their specialized components, which will be added to the
    // last node of the component tree.
    virtual RefPtr<Component> GetSpecializedComponent() = 0;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipelineContext)
    {
        pipelineContext_ = pipelineContext;
    }

    const WeakPtr<PipelineContext>& GetPipelineContext() const
    {
        return pipelineContext_;
    }

    // Initialize node theme style when created.
    virtual void InitializeStyle() {}

    void OnActive(bool isActive);

    bool HasPseudo() const
    {
        return (cachedPseudoType_ != STATE_NORMAL);
    }

    bool HasDisabledPseudo() const
    {
        return ((cachedPseudoType_ & STATE_DISABLED) > 0);
    }

    bool HasCheckedPseudo() const
    {
        return ((cachedPseudoType_ & STATE_CHECKED) > 0);
    }

    bool HasFocusPseudo() const
    {
        return ((cachedPseudoType_ & STATE_FOCUS) > 0);
    }

    bool HasActivePseudo() const
    {
        return ((cachedPseudoType_ & STATE_ACTIVE) > 0);
    }

    bool HasSvgTag()
    {
        return hasSvgTag_;
    }

    /*
     * Parse color from string content and reference for id/attr, including format:
     * #rrggbb, #aarrggbb, "@id001", "@attr_sys_color".
     */
    Color ParseColor(const std::string& value, uint32_t maskAlpha = COLOR_ALPHA_MASK) const;

    /*
     * Parse double from string content and reference for id/attr, including format:
     * 100.01, "@id001", "@attr_sys_alpha".
     */
    double ParseDouble(const std::string& value) const;

    /*
     * Parse dimension from string content and reference for id/attr, including format:
     * 10px, "@id001", "@attr_sys_dimension, expression".
     */
    CalcDimension ParseDimension(const std::string& value) const;

    /*
     * Parse line height from string content and reference for id/attr, including format:
     * 1.5, "@id001", "@attr_sys_line_height".
     */
    Dimension ParseLineHeight(const std::string& value) const;

    /*
     * Parse font family list from string content and reference for id/attr, including format:
     * sans-serif, "@id001", "@attr_sys_font_family".
     */
    std::vector<std::string> ParseFontFamilies(const std::string& value) const;

    /*
     * Parse dimension list from string content and reference for id/attr, including format:
     * 10px, "@id001", "@attr_sys_dimension".
     */
    std::vector<Dimension> ParsePreferFontSizes(const std::string& value) const;

    /*
     * Parse image src from string content and reference for id/attr, including format:
     * "@app.media.customized_image", "@sys.media.123".
     */
    std::string ParseImageSrc(const std::string& imgSrc) const;

    RefPtr<ThemeManager> GetThemeManager() const
    {
        auto context = pipelineContext_.Upgrade();
        if (!context) {
            return nullptr;
        }
        return context->GetThemeManager();
    }

    template<typename T>
    RefPtr<T> GetTheme() const
    {
        auto context = pipelineContext_.Upgrade();
        if (!context) {
            return nullptr;
        }
        auto themeManager = context->GetThemeManager();
        if (!themeManager) {
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }

    virtual void UpdateStyleWithChildren();

    bool IsCustomComponent() const
    {
        return isCustomComponent_;
    }

    void SetIsCustomComponent(bool isCustomComponent)
    {
        isCustomComponent_ = isCustomComponent;
    }

    bool HasBorderRadiusStyle() const
    {
        return declaration_ ? declaration_->HasBorderRadiusStyle() : false;
    }

    bool HasOverflowStyle() const
    {
        return declaration_ ? declaration_->HasOverflowStyle() : false;
    }

    bool IsBoxWrap() const
    {
        return boxWrap_;
    }

    void SetBoxWrap(bool boxWrap)
    {
        boxWrap_ = boxWrap;
    }

    void AdjustParamInLiteMode();

    virtual void AdjustSpecialParamInLiteMode() {}

    virtual void SetAttr(const std::vector<std::pair<std::string, std::string>>& attrs);
    virtual void SetStyle(const std::vector<std::pair<std::string, std::string>>& styles);
    virtual void AddEvent(int32_t pageId, const std::vector<std::string>& events);
    virtual void CallMethod(const std::string& method, const std::string& args);
    virtual void OnRequestFocus(bool shouldFocus);
    virtual void OnScrollBy(double dx, double dy, bool isSmooth);

    bool SetCurrentStyle(const std::pair<std::string, std::string>& style);

    bool IsRightToLeft() const
    {
        return declaration_ ? declaration_->IsRightToLeft() : false;
    }

    void SetHeight(const CalcDimension& height)
    {
        if (declaration_) {
            auto& sizeStyle = declaration_->MaybeResetStyle<CommonSizeStyle>(StyleTag::COMMON_SIZE_STYLE);
            if (sizeStyle.IsValid()) {
                sizeStyle.height = height;
            }
        }
    }

    void SetWidth(const CalcDimension& width)
    {
        if (declaration_) {
            auto& sizeStyle = declaration_->MaybeResetStyle<CommonSizeStyle>(StyleTag::COMMON_SIZE_STYLE);
            if (sizeStyle.IsValid()) {
                sizeStyle.width = width;
            }
        }
    }

    virtual Dimension GetHeight() const;

    virtual CalcDimension GetCalcHeight() const;

    virtual Dimension GetWidth() const;

    virtual CalcDimension GetCalcWidth() const;

    DisplayType GetDisplay() const
    {
        DisplayType display = DisplayType::NO_SETTING;
        if (declaration_) {
            auto& displayStyle =
                static_cast<CommonDisplayStyle&>(declaration_->GetStyle(StyleTag::COMMON_DISPLAY_STYLE));
            if (displayStyle.IsValid()) {
                display = displayStyle.display;
            }
        }
        return display;
    }

    void SetDisplay(DisplayType type)
    {
        if (declaration_) {
            auto& displayStyle = declaration_->MaybeResetStyle<CommonDisplayStyle>(StyleTag::COMMON_DISPLAY_STYLE);
            if (displayStyle.IsValid()) {
                displayStyle.display = type;
            }
        }
    }

    PositionType GetPosition() const
    {
        PositionType position = PositionType::PTRELATIVE;
        if (declaration_) {
            auto& positionStyle =
                static_cast<CommonPositionStyle&>(declaration_->GetStyle(StyleTag::COMMON_POSITION_STYLE));
            if (positionStyle.IsValid()) {
                position = positionStyle.position;
            }
        }
        return position;
    }

    std::optional<Color> GetImageFill() const
    {
        std::optional<Color> imageFill = std::nullopt;
        if (declaration_) {
            auto& imageStyle = static_cast<CommonImageStyle&>(declaration_->GetStyle(StyleTag::COMMON_IMAGE_STYLE));
            if (imageStyle.IsValid()) {
                imageFill = imageStyle.imageFill;
            }
        }
        return imageFill;
    }

    virtual NodeId GetDirtyNodeId() const
    {
        return nodeId_;
    }

protected:
    virtual void OnMounted(const RefPtr<DOMNode>& parentNode) {}
    virtual void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) {}
    virtual void OnChildNodeRemoved(const RefPtr<DOMNode>& child) {}
    virtual void OnSetStyleFinished() {}
    // Confirm declaration is exist before call GetClickId and GetLongPressId.
    virtual const EventMarker& GetClickId();
    virtual const EventMarker& GetDoubleClickId();
    const EventMarker& GetDragStartId();
    const EventMarker& GetDragId();
    const EventMarker& GetDragEndId();
    const EventMarker& GetDragEnterId();
    const EventMarker& GetDragOverId();
    const EventMarker& GetDragLeaveId();
    const EventMarker& GetDragDropId();
    virtual const EventMarker& GetLongPressId();
    const EventMarker& GetPinchStartId();
    const EventMarker& GetPinchUpdateId();
    const EventMarker& GetPinchEndId();
    const EventMarker& GetPinchCancelId();

    EventMarker& GetSwipeId(uint32_t action, uint32_t stage);

    // Confirm declaration exist and support raw event before call GetTouchId.
    EventMarker& GetTouchId(uint32_t action, uint32_t stage, uint32_t type);

    // Subclasses need to implement this interface to composit specialized component into common components.
    virtual RefPtr<Component> CompositeSpecializedComponent(const std::vector<RefPtr<SingleChild>>& components);

    // Subclasses need to override this interface to update component with declaration.
    virtual void UpdateSpecializedComponentWithDeclaration() {}

    // Subclasses need to override this interface to implement the dynamic creation of subclass specialized components.
    virtual void PrepareSpecializedComponent() {}

    virtual void CompositeComponents();

    virtual void UpdateBoxSize(const CalcDimension& width, const CalcDimension& height);
    virtual void UpdateBoxPadding(const Edge& padding);
    virtual void UpdateBoxBorder(const Border& border);
    virtual void UpdatePropAnimations(const PropAnimationMap& animations);
    virtual void UpdatePositionAnimations(const RefPtr<Component> component);

    // Subclasses need to override this interface to implement reset initialization style before any frontend style set.
    virtual void ResetInitializedStyle() {}

    virtual bool IsLeafNode() const
    {
        return false;
    }

    void PrepareScrollComponent();

    RefPtr<SingleChild> GetLastCommonParent()
    {
        if (sharedTransitionComponent_) {
            return sharedTransitionComponent_;
        }
        return boxComponent_;
    }

    void SetAlignment(const Alignment& align)
    {
        ACE_DCHECK(boxComponent_);
        boxComponent_->SetAlignment(align);
    }

    void OnChecked(bool isChecked);

    // Each subclass needs to override this function to obtain the properties. If it returns true, it means that the
    // property has been consumed. If it returns false, it means it is handed over to the parent class.
    virtual bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
    {
        return false;
    }

    // Each subclass needs to override this function to obtain the style. If it returns true, it means that the
    // style has been consumed. If it returns false, it means it is handed over to the parent class.
    virtual bool SetSpecializedStyle(const std::pair<std::string, std::string>& style)
    {
        return false;
    }

    // Each subclass needs to override this function to obtain the event. If it returns true, it means that the
    // event has been consumed. If it returns false, it means it is handed over to the parent class.
    virtual bool AddSpecializedEvent(int32_t pageId, const std::string& event)
    {
        return false;
    }

    virtual void CallSpecializedMethod(const std::string& method, const std::string& args) {}

    // When the multi-mode input subscript is set to auto, need to determine whether the current component has the
    // ability to support the subscript.
    virtual bool IsSubscriptEnable() const
    {
        if (declaration_) {
            declaration_->SetIsSubscriptEnable(false);
        }
        return false;
    }

    WeakPtr<DOMNode> parentNode_;
    NodeId parentId_ = -1;
    bool isRootNode_ = false;
    std::string parentTag_;
    std::list<RefPtr<DOMNode>> children_;
    // for pseudo class
    std::vector<std::pair<std::string, std::string>> attributesCache_;
    std::unordered_map<int32_t, std::unordered_map<std::string, std::string>> pseudoClassStyleMap_;
    RefPtr<ComposedComponent> rootComponent_;
    RefPtr<BoxComponent> boxComponent_;
    RefPtr<ScrollComponent> scrollComponent_;
    RefPtr<FlexItemComponent> flexItemComponent_;
    RefPtr<TransformComponent> transformComponent_;
    WeakPtr<PipelineContext> pipelineContext_;
    RefPtr<Declaration> declaration_;
    bool isCustomComponent_ = false;
    bool boxWrap_ = false;

private:
    static void SetTransform(const std::string& value, DOMNode& node);
    static void AddKeyframe(
        double time, const std::string& typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes);
    static void AddKeyframe(double time, double typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes);
    std::string GetTransformJsonValue(const std::string& value);
    std::string GetTransformType(const std::unique_ptr<JsonValue>& transformJson);
    std::string GetTransformTypeValue(const std::unique_ptr<JsonValue>& transformJson);

    void CreatePropertyAnimation(const std::string& property);
    RefPtr<KeyframeAnimation<float>> SetPropertyFloatAnimationKeyframe(float begin, float end);
    RefPtr<KeyframeAnimation<Color>> SetPropertyColorAnimationKeyframe(const Color& begin, const Color& end);
    void TransitionOptionSetKeyframes(TweenOption& tweenOption);
    void SetDisplayStyle();

    void SetDisplayType();
    void UpdateFlexItemComponent();
    void UpdateUiComponents();
    void UpdateBoxComponent();
    void UpdateDisplayComponent();
    void UpdateTweenComponent();
    void UpdateTouchEventComponent();
    void UpdateGestureEventComponent();
    void UpdateMouseEventComponent();
    void UpdateFocusableEventComponents();
    void UpdatePositionComponent();
    void UpdatePositionProps();
    void UpdateTweenPosition(const RefPtr<TweenComponent> tweenComponent);
#ifndef WEARABLE_PRODUCT
    void UpdateMultimodalComponent();
#endif

    void CachePseudoClassStyle(const std::pair<std::string, std::string>& pseudoClassStyle);
    void UpdatePseudoStyle(bool isBackendChange);
    void PrepareTouchEvent(EventMarker& eventMarker, uint32_t type);
    void PrepareFocusableEventId();
    void PrepareMouseHoverEvent();
    void UpdatePseudoStyleByStatus(int32_t status, bool isBackendChange);
    void ResetDefaultStyles();
    uint32_t CalculatePseudoStatus() const;
    void SetAttrInternal(const std::vector<std::pair<std::string, std::string>>& attrs);

    // for state update callbacks
    void OnFocus(bool isFocus);
    void OnHover(bool isHover);

    RefPtr<ThemeConstants> GetThemeConstants() const;

    template<typename T>
    T ParseThemeReference(const std::string& value, std::function<T()>&& noRefFunc,
        std::function<T(uint32_t refId)>&& idRefFunc, const T& errorValue) const
    {
        const auto& parseResult = ThemeUtils::ParseThemeIdReference(value, GetThemeConstants());
        if (!parseResult.parseSuccess) {
            return noRefFunc();
        }
        auto themeConstants = GetThemeConstants();
        if (!themeConstants) {
            return errorValue;
        }
        // Refer to a theme id resource.
        if (parseResult.isIdRef) {
            return idRefFunc(parseResult.id);
        }
        // Refer to a theme attribute.
        auto themeStyle = themeConstants->GetThemeStyle();
        if (!themeStyle) {
            return errorValue;
        }
        return themeStyle->GetAttr<T>(parseResult.refAttr, errorValue);
    }

    bool isTransition_ = false;
    bool isEnter_ = false;
    bool isProxy_ = false;
    bool animationStyleUpdated_ = false;
    bool customAnimationStyleUpdated_ = false;
    bool hasSvgTag_ = false;
    VisibleType visible_ = VisibleType::VISIBLE;

    int32_t pageId_ = -1;
    NodeId nodeId_ = -1;
    std::string tag_;

    RefPtr<DisplayComponent> displayComponent_;
    RefPtr<TouchListenerComponent> touchEventComponent_;
    RefPtr<GestureListenerComponent> gestureEventComponent_;
    RefPtr<FocusableComponent> focusableEventComponent_;
    RefPtr<MouseListenerComponent> mouseEventComponent_;
    RefPtr<PositionedComponent> positionComponent_;
    RefPtr<SharedTransitionComponent> sharedTransitionComponent_;
    RefPtr<TweenComponent> tweenComponent_;
    RefPtr<TransitionComponent> propTransitionComponent_;
    RefPtr<PageTransitionComponent> transitionComponent_;

    PropAnimationMap propAnimations_;
    AnimationUtil animationUtil_;
    RefPtr<KeyframeAnimation<float>> propertyWidthAnimation_;
    RefPtr<KeyframeAnimation<float>> propertyHeightAnimation_;
    RefPtr<KeyframeAnimation<Color>> propertyColorAnimation_;
    std::string animationName_;
    bool isActive_ = false;
    bool isFocus_ = false;
    uint32_t cachedPseudoType_ = STATE_NORMAL;

    TweenOption propTransitionOption_;
    std::string transitionPropertyName_ = "all";
    std::string transitionTimeFunction_ = "ease";
    int32_t transitionDuration_ = 0;
    int32_t transitionDelay_ = 0;
    bool isTransitionNameUpdateFirst_ = true;
    bool isTransitionDurationUpdateFirst_ = true;
    bool transitionStyleUpdated_ = false;
    bool isTransitionColor_ = false;

    // for shared transition
    std::string shareId_;
#ifndef WEARABLE_PRODUCT
    // for multi modal input.
    RefPtr<MultimodalComponent> multimodalComponent_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H

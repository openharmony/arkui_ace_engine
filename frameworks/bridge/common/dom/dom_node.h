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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H

#include <string>
#include <unordered_map>

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/animation/keyframe_animation.h"
#include "core/components/box/box_component.h"
#include "core/components/common/properties/shadow.h"
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
#include "core/components/tween/tween_component.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/dom/dom_type.h"

#ifndef WEARABLE_PRODUCT
#include "core/components/multimodal/multimodal_component.h"
#include "core/event/multimodal/multimodal_properties.h"
#endif

namespace OHOS::Ace::Framework {

enum class DisplayType {
    NO_SETTING = 0,
    FLEX,
    GRID,
    NONE,
};

enum class VisibilityType {
    NO_SETTING = 0,
    VISIBLE,
    HIDDEN,
};

// If no insertion location is specified, new child will be added to the end of children list by default.
inline constexpr int32_t DEFAULT_ITEM_INDEX = -1;

class ACE_EXPORT DOMNode : public AceType {
    DECLARE_ACE_TYPE(DOMNode, AceType);

public:
    DOMNode(NodeId nodeId, const std::string& nodeName);
    ~DOMNode() override;

    virtual void SetAttr(const std::vector<std::pair<std::string, std::string>>& attrs);
    virtual void SetStyle(const std::vector<std::pair<std::string, std::string>>& styles);
    virtual void AddEvent(int32_t pageId, const std::vector<std::string>& events);
    void SetTweenComponent(const RefPtr<TweenComponent>& tweenComponent);
    void SetAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);
    bool ParseAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);
    void SetSharedTransitionStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes);

    void AddNode(const RefPtr<DOMNode>& node, int32_t slot = DEFAULT_ITEM_INDEX);
    void RemoveNode(const RefPtr<DOMNode>& node);
    virtual void Mount(int32_t slot);
    void GenerateComponentNode();
    virtual void OnPageLoadFinish() {};

    virtual void CallMethod(const std::string& method, const std::string& args);

    virtual void OnRequestFocus(bool shouldFocus);

    virtual void OnScrollBy(double dx, double dy, bool isSmooth);

    virtual void SetShowAttr(const std::string& showValue);

    virtual const RefPtr<ScrollComponent>& GetScrollComponent() const
    {
        return scrollComponent_;
    }

    void MarkNeedUpdate();

    const std::list<RefPtr<DOMNode>>& GetChildList() const
    {
        return children_;
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

    PositionType GetPosition() const
    {
        return position_;
    }

    const RefPtr<PageTransitionComponent>& BuildTransitionComponent();

    // Ensure DOMPopup can response onClick event even without defining it.
    void SetOnClick(const EventMarker& eventMarker)
    {
        ACE_DCHECK(gestureEventComponent_);
        gestureEventComponent_->SetOnClickId(eventMarker);
    }

    void SetOnLongPress(const EventMarker& eventMarker)
    {
        gestureEventComponent_->SetOnLongPressId(eventMarker);
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

    std::string GetNodeIdForEvent() const
    {
        return isRootNode_ ? DOM_DEFAULT_ROOT_NODE_ID : std::to_string(GetNodeId());
    }

    const std::string& GetTag() const
    {
        return tag_;
    }

    DisplayType GetDisplay() const
    {
        return display_;
    }

    void SetDisplay(DisplayType type)
    {
        display_ = type;
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
        return visible_ == VisibleType::VISIBLE && !NearZero(opacity_);
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    void SetHeight(const Dimension& height)
    {
        height_ = height;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    void SetWidth(const Dimension& width)
    {
        width_ = width;
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

    RefPtr<TweenComponent> GetTweenComponent() const;

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

    bool IsRightToLeft() const
    {
        return isRightToLeft_;
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
    virtual void InitializeStyle() {};

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

    void SetShareId(const std::string& shareId)
    {
        shareId_ = shareId;
    }

    const std::string& GetShareId() const
    {
        return shareId_;
    }

    void SetHasDisplayStyleFlag(bool flag)
    {
        hasDisplayStyle_ = flag;
    }

    const Dimension& GetMarginTop() const
    {
        return marginTop_;
    }

    const Dimension& GetMarginBottom() const
    {
        return marginBottom_;
    }

    const Dimension& GetMarginLeft() const
    {
        return marginLeft_;
    }

    const Dimension& GetMarginRight() const
    {
        return marginRight_;
    }

    bool GetDisable() const
    {
        return nodeDisabled_;
    }

    double GetFlexWeight() const
    {
        return flexWeight_;
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
     * 10px, "@id001", "@attr_sys_dimension".
     */
    Dimension ParseDimension(const std::string& value) const;

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
        return hasBorderRadiusStyle_;
    }

    bool HasPositionStyle() const
    {
        return hasPositionStyle_;
    }

    bool HasOverflowStyle() const
    {
        return hasOverflowStyle_;
    }

    bool IsBoxWrap() const
    {
        return boxWrap_;
    }

    void SetBoxWrap(bool boxWrap)
    {
        boxWrap_ = boxWrap;
    }

    const TweenOption& GetTweenOption() const
    {
        return tweenOption_;
    }

    void AdjustParamInLiteMode();

    virtual void AdjustSpecialParamInLiteMode() {}

protected:
    virtual void OnMounted(const RefPtr<DOMNode>& parentNode) {};
    virtual void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) {};
    virtual void OnChildNodeRemoved(const RefPtr<DOMNode>& child) {};
    virtual void CallSpecializedMethod(const std::string& method, const std::string& args) {};
    virtual void OnSetStyleFinished() {};
    virtual const EventMarker& GetClickId()
    {
        return onClickId_;
    };

    // Subclasses need to implement this interface to composite specialized component into common components.
    virtual RefPtr<Component> CompositeSpecializedComponent(const std::vector<RefPtr<SingleChild>>& components);

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

    // Subclasses need to override this interface to implement the dynamic creation of subclass specialized components.
    virtual void PrepareSpecializedComponent() {};

    virtual void CompositeComponents();

    virtual void UpdateBoxSize(const Dimension& width, const Dimension& height);
    virtual void UpdateBoxPadding(const Edge& padding);
    virtual void UpdateBoxBorder(const Border& border);

    // Subclasses need to override this interface to implement reset initialization style before any frontend style set.
    virtual void ResetInitializedStyle() {};

    // When the multi-mode input subscript is set to auto, need to determine whether the current component has the
    // ability to support the subscript.
    virtual bool IsSubscriptEnable() const
    {
        return false;
    }

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

    void SetPosition(const PositionType& positionType, const Dimension& top, const Dimension& left)
    {
        hasPositionStyle_ = true;
        position_ = positionType;
        left_ = left;
        top_ = top;
        hasLeft_ = true;
        hasTop_ = true;
    }

    void OnChecked(bool isChecked);

    WeakPtr<DOMNode> parentNode_;
    NodeId parentId_ = -1;
    bool isRootNode_ = false;
    bool hasBackGroundColor_ = false;
    bool hasPositionProcessed_ = false;
    std::string parentTag_;
    std::list<RefPtr<DOMNode>> children_;
#ifndef WEARABLE_PRODUCT
    MultimodalProperties multimodalProperties_;
#endif
    RefPtr<ComposedComponent> rootComponent_;
    RefPtr<BoxComponent> boxComponent_;
    RefPtr<ScrollComponent> scrollComponent_;
    RefPtr<FlexItemComponent> flexItemComponent_;
    RefPtr<TransformComponent> transformComponent_;
    WeakPtr<PipelineContext> pipelineContext_;
    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    Shadow shadow_;
    Border border_ = Border(borderLeftEdge_, borderTopEdge_, borderRightEdge_, borderBottomEdge_);
    Dimension paddingTop_;
    Dimension paddingRight_;
    Dimension paddingBottom_;
    Dimension paddingLeft_;
    bool hasBoxStyle_ = false;
    bool hasDecorationStyle_ = false;
    bool hasShadowStyle_ = false;
    bool hasFrontDecorationStyle_ = false;
    bool hasBorderStyle_ = false;
    bool hasBorderRadiusStyle_ = false;
    double opacity_ = 1.0;
    bool hasClickEffect_ = false;
    bool hasTransitionAnimation_ = false;
    Overflow overflow_ = Overflow::OBSERVABLE;
    bool hasOverflowStyle_ = false;
    bool isCustomComponent_ = false;
    Dimension height_ = Dimension(-1.0, DimensionUnit::PX);
    Dimension width_ = Dimension(-1.0, DimensionUnit::PX);
    bool useLiteStyle_ = false;
    bool boxWrap_ = false;

    // scroll bar
    std::pair<bool, Color> scrollBarColor_;
    std::pair<bool, Dimension> scrollBarWidth_;
    EdgeEffect edgeEffect_ = EdgeEffect::NONE;

private:
    static void SetBackgroundImageSize(const std::string& value, DOMNode& node);
    static void SetBackgroundImagePosition(const std::string& value, DOMNode& node);
    static void SetBorderColorForFourEdges(const std::string& value, DOMNode& node);
    static void SetBorderStyleForFourEdges(const std::string& value, DOMNode& node);
    static void SetBorderWidthForFourEdges(const std::string& value, DOMNode& node);
    static void SetBorderOverall(const std::string& value, DOMNode& node);
    static void SetMarginOverall(const std::string& value, DOMNode& node);
    static void SetPaddingOverall(const std::string& value, DOMNode& node);
    static void SetGradientType(const std::string& gradientType, DOMNode& node);
    static void SetGradientDirections(const std::unique_ptr<JsonValue>& gradientDirections, DOMNode& node);
    static void SetGradientColor(const std::unique_ptr<JsonValue>& gradientColorValues, DOMNode& node);
    static void SetBackground(const std::string& value, DOMNode& node);
    static void SetTransform(const std::string& value, DOMNode& node);
    static void AddKeyframe(
        double time, const std::string& typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes);
    static void AddKeyframe(
        double time, double typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes);
    void AddKeyframeOffset(const std::string& keyValue, double time, const std::string& typeValue,
        RefPtr<KeyframeAnimation<DimensionOffset>>& transformKeyframes);
    std::string GetTransformJsonValue(const std::string& value);
    std::string GetTransformType(const std::unique_ptr<JsonValue>& transformJson);
    std::string GetTransformTypeValue(const std::unique_ptr<JsonValue>& transformJson);
    void KeyframesAddKeyFrame(const std::string& keyStyle, const std::string& value, double time);
    void TransformAnimationAddKeyframe(const std::string& typeKey, const std::string& typeValue, double time);
    void TweenOptionSetKeyframes(TweenOption& tweenOption);
    void SetDisplayStyle();

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

    void SetCurrentStyle(const std::pair<std::string, std::string>& style);
    void CachePseudoClassStyle(const std::pair<std::string, std::string>& pseudoClassStyle);
    void UpdatePseudoStyle(bool isBackendChange);
    void PrepareTouchEvent(EventMarker& eventMarker, uint32_t type);
    void PrepareFocusableEventId();
    void UpdatePseudoStyleByStatus(int32_t status, bool isBackendChange);
    void ResetDefaultStyles();
    uint32_t CalculatePseudoStatus() const;

    // for state update callbacks
    void OnFocus(bool isFocus);

    RefPtr<ThemeConstants> GetThemeConstants() const;

    template<typename T>
    T ParseThemeReference(const std::string& value, std::function<T()>&& noRefFunc,
        std::function<T(uint32_t refId)>&& idRefFunc, const T& errorValue) const
    {
        const auto& parseResult = ThemeUtils::ParseThemeIdReference(value);
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

    int32_t pageId_ = -1;
    NodeId nodeId_ = -1;
    std::string tag_;

    RefPtr<DisplayComponent> displayComponent_;
    RefPtr<BackgroundImage> backgroundImage_;
    RefPtr<TouchListenerComponent> touchEventComponent_;
    RefPtr<GestureListenerComponent> gestureEventComponent_;
    RefPtr<FocusableComponent> focusableEventComponent_;
    RefPtr<MouseListenerComponent> mouseEventComponent_;

    RefPtr<PositionedComponent> positionComponent_;
    RefPtr<SharedTransitionComponent> sharedTransitionComponent_;

    RefPtr<TweenComponent> tweenComponent_;
    RefPtr<PageTransitionComponent> transitionComponent_;

    EventMarker onTouchIds_[EventAction::SIZE][EventStage::SIZE][EventType::SIZE];
    EventMarker onClickId_;
    EventMarker onLongPressId_;
    EventMarker onFocusId_;
    EventMarker onBlurId_;
    EventMarker onKeyId_;
    EventMarker onMouseId_;
    EventMarker onSwipeId_;

    Dimension marginTop_;
    Dimension marginRight_;
    Dimension marginBottom_;
    Dimension marginLeft_;
    std::string alignSelf_;
    bool isTransition_ = false;
    bool isEnter_ = false;
    bool layoutInBox_ = false;
    bool isProxy_ = false;

    VisibleType visible_ { VisibleType::VISIBLE };
    VisibilityType visibility_ { VisibilityType::NO_SETTING };
    DisplayType display_ { DisplayType::NO_SETTING };
    std::string showAttr_;
    bool hasDisplayStyle_ = false;

    // The target node (with id attribute) for popup should be added gesture event handler,
    // it's ok to take 'id' as a flag, even not all dom nodes with id attribute should do this.
    bool hasIdAttr_ = false;

    double flexGrow_ = 0.0;
    double flexShrink_ = 1.0;
    double flexBasis_ = 0.0;
    double flexWeight_ = 0.0;
    Dimension minWidth_ = Dimension(0.0);
    Dimension minHeight_ = Dimension(0.0);
    Dimension maxWidth_ = Dimension(Size::INFINITE_SIZE);
    Dimension maxHeight_ = Dimension(Size::INFINITE_SIZE);
    int32_t displayIndex_ = 1;

    double aspectRatio_ = 0.0;

    BorderEdge borderLeftEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    BorderEdge borderTopEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    BorderEdge borderRightEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    BorderEdge borderBottomEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    Gradient gradient_;

    PositionType position_ { PositionType::RELATIVE };
    Dimension bottom_;
    Dimension left_;
    Dimension right_;
    Dimension top_;
    bool hasLeft_ = false;
    bool hasTop_ = false;
    bool hasRight_ = false;
    bool hasBottom_ = false;
    bool hasPositionStyle_ = false;
    bool hasSvgTag_ = false;

    RefPtr<KeyframeAnimation<DimensionOffset>> translateAnimation_;
    RefPtr<KeyframeAnimation<DimensionOffset>> translateXAnimation_;
    RefPtr<KeyframeAnimation<DimensionOffset>> translateYAnimation_;
    double maxScaleXY_ = -1.0;
    RefPtr<KeyframeAnimation<float>> scaleAnimationX_;
    RefPtr<KeyframeAnimation<float>> scaleAnimationY_;
    RefPtr<KeyframeAnimation<float>> scaleXAnimation_;
    RefPtr<KeyframeAnimation<float>> scaleYAnimation_;
    RefPtr<KeyframeAnimation<float>> rotateZAnimation_;
    RefPtr<KeyframeAnimation<float>> rotateXAnimation_;
    RefPtr<KeyframeAnimation<float>> rotateYAnimation_;
    RefPtr<KeyframeAnimation<float>> widthAnimation_;
    RefPtr<KeyframeAnimation<float>> heightAnimation_;
    RefPtr<KeyframeAnimation<float>> opacityAnimation_;
    RefPtr<KeyframeAnimation<Color>> colorAnimation_;
    RefPtr<KeyframeAnimation<BackgroundImagePosition>> bgPositionAnimation_;
    std::unordered_map<PropertyAnimatableType, RefPtr<KeyframeAnimation<float>>> propertyFloatAnimations;
    bool sameScale_ = true;
    TweenOption tweenOption_;
    TweenOption transitionEnterOption_;
    TweenOption transitionExitOption_;
    TweenOption sharedTransitionOption_;
    RefPtr<SharedTransitionEffect> sharedEffect_;
    bool animationStyleUpdated_ = false;
    std::pair<bool, bool> focusable_ = { false, false };
    bool touchable_ = true;
    bool nodeDisabled_ = false;
    // for direction
    bool isRightToLeft_ = false;
    // for pseudo class
    std::unordered_map<int32_t, std::unordered_map<std::string, std::string>> pseudoClassStyleMap_;
    bool isActive_ = false;
    bool isFocus_ = false;
    bool isChecked_ = false;
    bool isWaiting_ = false;
    uint32_t cachedPseudoType_ = STATE_NORMAL;

    int32_t zIndex_ = 0;
    // for shared transition
    std::string shareId_;
#ifndef WEARABLE_PRODUCT
    // for multi modal input.
    RefPtr<MultimodalComponent> multimodalComponent_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_NODE_H

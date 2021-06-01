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

#include "frameworks/bridge/common/dom/dom_node.h"

#include <sstream>
#include <unordered_set>

#include "base/log/ace_trace.h"
#include "core/common/ace_application_info.h"
#include "core/common/frontend.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scroll_fade_effect.h"
#include "core/components/scroll/scroll_spring_effect.h"
#include "frameworks/bridge/common/dom/dom_div.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t TRANSFORM_SINGLE = 1;
constexpr uint32_t TRANSFORM_DUAL = 2;
constexpr uint32_t COMMON_METHOD_FOCUS_ARGS_SIZE = 1;
constexpr uint32_t SINGLE_VALUE = 1;
constexpr uint32_t TWO_VALUES = 2;
constexpr uint32_t THREE_VALUES = 3;
constexpr uint32_t FOUR_VALUES = 4;
const char COMMON_METHOD_FOCUS[] = "focus";

// focusable support list, this list should be updated after the other nodes(checkbox/radio/switch/
// grid/dialog/button/input) implemented in frontend.
std::unordered_set<std::string> g_focusableNode;

// unsupported focusable list.
const std::unordered_set<std::string> UNFOCUSABLED_NODE = {
    DOM_NODE_TAG_SPAN,
};

// default flex value
constexpr double DEFAULT_FLEX_GROW = 0.0;
constexpr double DEFAULT_FLEX_SHRINK = 1.0;
constexpr double DEFAULT_FLEX_BASIS = -1.0;
constexpr int32_t DIRECTION_ANGLE = 1;
constexpr int32_t DIRECTION_SIDE = 2;
constexpr int32_t DIRECTION_CORNER = 3;
constexpr int32_t MS_TO_S = 1000;
constexpr int32_t PERCENTAGE = 100;
constexpr Dimension TRANSFORM_ORIGIN_DEFAULT = 0.5_pct;

// prefix id of TweenComponent, for differentiation from id of ComposedComponent
constexpr char COMPONENT_PREFIX[] = "FrontendTween";

// Shared Transition Effect FrontendType String
constexpr char SHARED_TRANSITION_EFFECT_STATIC[] = "static";
constexpr char SHARED_TRANSITION_EFFECT_EXCHANGE[] = "exchange";

constexpr PropertyAnimatableType PROPERTY_ANIMATIONABLE_FLOAT_TYPES[] = {
    PropertyAnimatableType::PROPERTY_PADDING_LEFT,
    PropertyAnimatableType::PROPERTY_PADDING_TOP,
    PropertyAnimatableType::PROPERTY_PADDING_RIGHT,
    PropertyAnimatableType::PROPERTY_PADDING_BOTTOM,
    PropertyAnimatableType::PROPERTY_MARGIN_LEFT,
    PropertyAnimatableType::PROPERTY_MARGIN_TOP,
    PropertyAnimatableType::PROPERTY_MARGIN_RIGHT,
    PropertyAnimatableType::PROPERTY_MARGIN_BOTTOM,
};

RefPtr<SharedTransitionEffect> ParseSharedEffect(const std::string& effect, DOMNode& node)
{
    std::string effectTrim = effect;
    RemoveHeadTailSpace(effectTrim);
    if (effectTrim == SHARED_TRANSITION_EFFECT_STATIC) {
        return SharedTransitionEffect::GetSharedTransitionEffect(
            SharedTransitionEffectType::SHARED_EFFECT_STATIC, node.GetShareId());
    } else if (effectTrim == SHARED_TRANSITION_EFFECT_EXCHANGE) {
        return SharedTransitionEffect::GetSharedTransitionEffect(
            SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE, node.GetShareId());
    } else {
        LOGE("Parse shared effect failed. unknown effect: %{public}s, share id: %{public}s", effect.c_str(),
            node.GetShareId().c_str());
        return nullptr;
    }
}

ClickSpringEffectType ParseClickEffect(const std::string& effect)
{
    static std::unordered_map<std::string, ClickSpringEffectType> types = {
        { "spring-small", ClickSpringEffectType::SMALL },
        { "spring-medium", ClickSpringEffectType::MEDIUM },
        { "spring-large", ClickSpringEffectType::LARGE },
    };
    auto pos = types.find(effect);
    if (pos != types.end()) {
        return pos->second;
    }
    return ClickSpringEffectType::NONE;
}

TransitionEffect ParseTransitionEffect(const std::string& option)
{
    static std::unordered_map<std::string, TransitionEffect> types = {
        { "unfold", TransitionEffect::UNFOLD },
        { "none", TransitionEffect::NONE },
    };
    auto pos = types.find(option);
    if (pos != types.end()) {
        return pos->second;
    }
    return TransitionEffect::NONE;
}

inline WindowBlurStyle StrToWindowBlurStyle(const std::string& value)
{
    static std::unordered_map<std::string, WindowBlurStyle> types = {
        { "small_light", WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT },
        { "medium_light", WindowBlurStyle::STYLE_BACKGROUND_MEDIUM_LIGHT },
        { "large_light", WindowBlurStyle::STYLE_BACKGROUND_LARGE_LIGHT },
        { "xlarge_light", WindowBlurStyle::STYLE_BACKGROUND_XLARGE_LIGHT },
        { "small_dark", WindowBlurStyle::STYLE_BACKGROUND_SMALL_DARK },
        { "medium_dark", WindowBlurStyle::STYLE_BACKGROUND_MEDIUM_DARK },
        { "large_dark", WindowBlurStyle::STYLE_BACKGROUND_LARGE_DARK },
        { "xlarge_dark", WindowBlurStyle::STYLE_BACKGROUND_XLARGE_DARK },
    };
    auto pos = types.find(value);
    if (pos != types.end()) {
        return pos->second;
    }
    return WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT;
}

template<class T>
T ParseFunctionValue(const std::string& line, const std::string& key, std::function<T(const std::string&)> parser)
{
    std::vector<std::string> strs;
    StringUtils::SplitStr(line, " ", strs, true);
    for (const auto& str : strs) {
        if (str.empty()) {
            continue;
        }
        auto leftIndex = str.find('(');
        auto rightIndex = str.find(')');
        if (leftIndex == std::string::npos || rightIndex == std::string::npos) {
            continue;
        }
        if (leftIndex + 1 >= rightIndex) {
            continue;
        }
        if (str.substr(0, leftIndex) != key) {
            continue;
        }

        auto valueStr = str.substr(leftIndex + 1, rightIndex - leftIndex - 1);
        return parser(valueStr);
    }
    return T {};
}

} // namespace

DOMNode::DOMNode(NodeId nodeId, const std::string& nodeName) : nodeId_(nodeId), tag_(nodeName)
{
    rootComponent_ = AceType::MakeRefPtr<ComposedComponent>(std::to_string(nodeId), nodeName);
    backDecoration_ = AceType::MakeRefPtr<Decoration>();
    backgroundImage_ = AceType::MakeRefPtr<BackgroundImage>();
    boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
}

DOMNode::~DOMNode()
{
    if (!onFocusId_.IsEmpty()) {
        BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(onFocusId_);
    }
    if (!onBlurId_.IsEmpty()) {
        BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(onBlurId_);
    }

    for (uint32_t eventAction = 0; eventAction < EventAction::SIZE; eventAction++) {
        for (uint32_t eventStage = 0; eventStage < EventStage::SIZE; eventStage++) {
            for (uint32_t touchEventType = 0; touchEventType < EventType::SIZE; touchEventType++) {
                const auto& eventMarker = onTouchIds_[eventAction][eventStage][touchEventType];
                if (!eventMarker.IsEmpty()) {
                    BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(eventMarker);
                }
            }
        }
    }
}

void DOMNode::Mount(int32_t slot)
{
    auto parentNode = parentNode_.Upgrade();
    if (!parentNode) {
        return;
    }
    // flex-item could be used in div, list-item, tabs
    static const std::unordered_set<std::string> flexItemParents = {
        DOM_NODE_TAG_DIV,
        DOM_NODE_TAG_GRID_COLUMN,
        DOM_NODE_TAG_LIST_ITEM,
        DOM_NODE_TAG_LIST_ITEM_GROUP,
        DOM_NODE_TAG_TABS,
        DOM_NODE_TAG_REFRESH,
        DOM_NODE_TAG_STEPPER_ITEM,
    };
    if (flexItemParents.count(parentTag_) > 0) {
        flexItemComponent_ =
            AceType::MakeRefPtr<FlexItemComponent>(DEFAULT_FLEX_GROW, DEFAULT_FLEX_SHRINK, DEFAULT_FLEX_BASIS);
        if (boxComponent_) {
            // span has no box component.
            boxComponent_->SetDeliverMinToChild(false);
        }
    }
    GenerateComponentNode();
    if (parentNode->IsRootNode()) {
        // When parent is root node, parent contains scroll component,
        // box could handle percent with viewport size.
        if (boxComponent_) {
            // span has no box component.
            boxComponent_->SetPercentFlag(PERCENT_FLAG_USE_VIEW_PORT);
        }
    }
    parentNode->AddNode(AceType::Claim(this), slot);
    OnMounted(parentNode);
}

void DOMNode::AddEvent(int32_t pageId, const std::vector<std::string>& events)
{
    ACE_SCOPED_TRACE("DOMNode::AddEvent");
    static const LinearMapNode<void (*)(int32_t, DOMNode&)> eventSetters[] = {
        { DOM_BLUR,
            [](int32_t pageId, DOMNode& node) {
                node.onBlurId_ = EventMarker(node.GetNodeIdForEvent(), DOM_BLUR, pageId);
            } },
        { DOM_CAPTURE_TOUCH_CANCEL,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::CAPTURE][EventType::TOUCH_CANCEL] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CAPTURE_TOUCH_CANCEL, pageId);
            } },
        { DOM_CAPTURE_TOUCH_END,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::CAPTURE][EventType::TOUCH_UP] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CAPTURE_TOUCH_END, pageId);
            } },
        { DOM_CAPTURE_TOUCH_MOVE,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::CAPTURE][EventType::TOUCH_MOVE] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CAPTURE_TOUCH_MOVE, pageId);
            } },
        { DOM_CAPTURE_TOUCH_START,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::CAPTURE][EventType::TOUCH_DOWN] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CAPTURE_TOUCH_START, pageId);
            } },
        { DOM_CATCH_BUBBLE_TOUCH_CANCEL,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::BUBBLE][EventType::TOUCH_CANCEL] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_BUBBLE_TOUCH_CANCEL, pageId);
            } },
        { DOM_CATCH_BUBBLE_TOUCH_END,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::BUBBLE][EventType::TOUCH_UP] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_BUBBLE_TOUCH_END, pageId);
            } },
        { DOM_CATCH_BUBBLE_TOUCH_MOVE,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::BUBBLE][EventType::TOUCH_MOVE] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_BUBBLE_TOUCH_MOVE, pageId);
            } },
        { DOM_CATCH_BUBBLE_TOUCH_START,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::BUBBLE][EventType::TOUCH_DOWN] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_BUBBLE_TOUCH_START, pageId);
            } },
        { DOM_CATCH_CAPTURE_TOUCH_CANCEL,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::CAPTURE][EventType::TOUCH_CANCEL] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_CAPTURE_TOUCH_CANCEL, pageId);
            } },
        { DOM_CATCH_CAPTURE_TOUCH_END,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::CAPTURE][EventType::TOUCH_UP] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_CAPTURE_TOUCH_END, pageId);
            } },
        { DOM_CATCH_CAPTURE_TOUCH_MOVE,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::CAPTURE][EventType::TOUCH_MOVE] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_CAPTURE_TOUCH_MOVE, pageId);
            } },
        { DOM_CATCH_CAPTURE_TOUCH_START,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::CATCH][EventStage::CAPTURE][EventType::TOUCH_DOWN] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_CATCH_CAPTURE_TOUCH_START, pageId);
            } },
        { DOM_CLICK,
            [](int32_t pageId, DOMNode& node) {
                node.onClickId_ = EventMarker(node.GetNodeIdForEvent(), DOM_CLICK, pageId);
            } },
        { DOM_FOCUS,
            [](int32_t pageId, DOMNode& node) {
                node.onFocusId_ = EventMarker(node.GetNodeIdForEvent(), DOM_FOCUS, pageId);
            } },
        { DOM_KEY,
            [](int32_t pageId, DOMNode& node) {
                node.onKeyId_ = EventMarker(node.GetNodeIdForEvent(), DOM_KEY, pageId);
            } },
        { DOM_LONG_PRESS,
            [](int32_t pageId, DOMNode& node) {
                node.onLongPressId_ = EventMarker(node.GetNodeIdForEvent(), DOM_LONG_PRESS, pageId);
            } },
        { DOM_MOUSE,
            [](int32_t pageId, DOMNode& node) {
                node.onMouseId_ = EventMarker(node.GetNodeIdForEvent(), DOM_MOUSE, pageId);
            } },
        { DOM_SWIPE,
            [](int32_t pageId, DOMNode& node) {
                node.onSwipeId_ = EventMarker(node.GetNodeIdForEvent(), DOM_SWIPE, pageId);
            } },
        { DOM_TOUCH_CANCEL,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::BUBBLE][EventType::TOUCH_CANCEL] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_TOUCH_CANCEL, pageId);
            } },
        { DOM_TOUCH_END,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::BUBBLE][EventType::TOUCH_UP] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_TOUCH_END, pageId);
            } },
        { DOM_TOUCH_MOVE,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::BUBBLE][EventType::TOUCH_MOVE] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_TOUCH_MOVE, pageId);
            } },
        { DOM_TOUCH_START,
            [](int32_t pageId, DOMNode& node) {
                node.onTouchIds_[EventAction::ON][EventStage::BUBBLE][EventType::TOUCH_DOWN] =
                    EventMarker(node.GetNodeIdForEvent(), DOM_TOUCH_START, pageId);
            } },
    };
    for (const auto& event : events) {
        if (AddSpecializedEvent(pageId, event)) {
            continue;
        }
        auto setterIter = BinarySearchFindIndex(eventSetters, ArraySize(eventSetters), event.c_str());
        if (setterIter != -1) {
            eventSetters[setterIter].value(pageId, *this);
        }
    }
}

void DOMNode::SetAttr(const std::vector<std::pair<std::string, std::string>>& attrs)
{
    rootComponent_->SetUpdateType(UpdateType::ALL);
    static const std::string flagOn = "on";
    static const std::string flagOff = "off";
    static const std::string flagAuto = "auto";
    // static linear map must be sorted by key.
    static const LinearMapNode<void (*)(const std::string&, DOMNode&)> attrSetters[] = {
        { DOM_CLICK_EFFECT,
            [](const std::string &val, DOMNode &node) {
                 if (!node.transformComponent_) {
                     node.transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
                 }
                 node.hasClickEffect_ = true;
                 node.transformComponent_->SetClickSpringEffectType(ParseClickEffect(val));
            } },
        { DOM_DIR,
            [](const std::string& val, DOMNode& node) {
                if (val == "rtl") {
                    node.isRightToLeft_ = true;
                } else if (val == "ltr") {
                    node.isRightToLeft_ = false;
                }
            } },
        { DOM_FOCUSABLE,
            [](const std::string& value, DOMNode& node) {
                node.focusable_.first = StringToBool(value);
                node.focusable_.second = true; // Tag whether user defined focusable.
            } },
        { DOM_ID, [](const std::string& value, DOMNode& node) { node.hasIdAttr_ = true; } },
#ifndef WEARABLE_PRODUCT
        { DOM_SCENE_LABEL,
            [](const std::string& value, DOMNode& node) {
                static const LinearMapNode<SceneLabel> multimodalSceneMap[] = {
                    { "audio", SceneLabel::AUDIO }, { "common", SceneLabel::COMMON },
                    { "page", SceneLabel::PAGE }, { "switch", SceneLabel::SWITCH },
                    { "video", SceneLabel::VIDEO },
                };
                auto iter = BinarySearchFindIndex(
                    multimodalSceneMap, ArraySize(multimodalSceneMap), value.c_str());
                if (iter != -1) {
                    node.multimodalProperties_.scene = multimodalSceneMap[iter].value;
                }
            } },
#endif
        { DOM_SHOW,
            [](const std::string& value, DOMNode& node) {
                if (node.useLiteStyle_) {
                    node.visibility_ = value == "true" ? VisibilityType::VISIBLE : VisibilityType::HIDDEN;
                } else {
                    node.SetShowAttr(value);
                }
                node.hasDisplayStyle_ = true;
            } },
#ifndef WEARABLE_PRODUCT
        { DOM_SUBSCRIPT_FLAG,
            [](const std::string& value, DOMNode& node) {
                node.multimodalProperties_.useSubscript =
                    (value == flagOn) || (value == flagAuto && node.IsSubscriptEnable());
            } },
        { DOM_SUBSCRIPT_LABEL,
            [](const std::string& value, DOMNode& node) { node.multimodalProperties_.subscriptLabel = value; } },
        { DOM_TOUCHABLE, [](const std::string& value, DOMNode& node) { node.touchable_ = StringToBool(value); } },
        { DOM_VOICE_LABEL,
            [](const std::string& value, DOMNode& node) { node.multimodalProperties_.voiceLabel = value; } },
#endif
    };

    for (const auto& attr : attrs) {
        if (attr.first == DOM_DISABLED) {
            nodeDisabled_ = StringToBool(attr.second);
        }

        if (attr.first == DOM_BUTTON_WAITING) {
            isWaiting_ = StringToBool(attr.second);
        }

        if (attr.first == DOM_CHECKED) {
            isChecked_ = StringToBool(attr.second);
        }

        if (SetSpecializedAttr(attr)) {
            continue;
        }
        auto operatorIter = BinarySearchFindIndex(attrSetters, ArraySize(attrSetters), attr.first.c_str());
        if (operatorIter != -1) {
            attrSetters[operatorIter].value(attr.second, *this);
        }
    }
}

void DOMNode::CallMethod(const std::string& method, const std::string& args)
{
    if (method == COMMON_METHOD_FOCUS) {
        LOGD("CallMethod: node tag: %{public}s call focus method.", tag_.c_str());
        if (!focusableEventComponent_) {
            LOGE("CallMethod: call focus method failed, focusableEventComponent is null");
            return;
        }

        bool shouldFocus = true;
        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (argsValue && argsValue->IsArray() && argsValue->GetArraySize() == COMMON_METHOD_FOCUS_ARGS_SIZE) {
            std::unique_ptr<JsonValue> focusValue = argsValue->GetArrayItem(0)->GetValue(COMMON_METHOD_FOCUS);
            if (focusValue && focusValue->IsBool()) {
                shouldFocus = focusValue->GetBool();
            }
        }
        OnRequestFocus(shouldFocus);
    } else if (method == DOM_LIST_METHOD_SCROLL_BY) {
        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() != 1) {
            LOGE("parse args error");
            return;
        }
        std::unique_ptr<JsonValue> scrollByPara = argsValue->GetArrayItem(0);
        double x = scrollByPara->GetDouble("dx", 0.0);
        double y = scrollByPara->GetDouble("dy", 0.0);
        bool isSmooth = scrollByPara->GetBool("smooth", true);
        OnScrollBy(x, y, isSmooth);
    } else {
        CallSpecializedMethod(method, args);
    }
}

void DOMNode::OnRequestFocus(bool shouldFocus)
{
    auto controller = focusableEventComponent_->GetFocusableController();
    if (!controller) {
        return;
    }
    controller->RequestFocus(shouldFocus);
}

void DOMNode::OnScrollBy(double dx, double dy, bool isSmooth)
{
    auto scrollComponent = GetScrollComponent();
    if (!scrollComponent) {
        return;
    }
    auto positionController = scrollComponent->GetScrollPositionController();
    if (!positionController) {
        return;
    }
    positionController->ScrollBy(dx, dy, isSmooth);
}

void DOMNode::SetShowAttr(const std::string& showValue)
{
    showAttr_ = showValue;
    if (showValue == "false") {
        display_ = DisplayType::NONE;
    } else {
        display_ = DisplayType::NO_SETTING;
    }
}

void DOMNode::OnActive(bool isActive)
{
    isActive_ = isActive;
    UpdatePseudoStyle(true);
}

void DOMNode::OnFocus(bool isFocus)
{
    isFocus_ = isFocus;
    UpdatePseudoStyle(true);
}

void DOMNode::OnChecked(bool isChecked)
{
    isChecked_ = isChecked;
    UpdatePseudoStyle(true);
}

void DOMNode::MarkNeedUpdate()
{
    auto pipelineContext = pipelineContext_.Upgrade();
    if (!pipelineContext) {
        LOGE("pipelineContext_ is nullptr");
        return;
    }
    rootComponent_->MarkNeedUpdate();
    rootComponent_->SetUpdateType(UpdateType::ALL);
    pipelineContext->ScheduleUpdate(rootComponent_);
}

void DOMNode::SetOnFocusClick(const EventMarker& eventMarker)
{
    if (!focusableEventComponent_) {
        return;
    }
    focusableEventComponent_->SetOnClickId(eventMarker);
}

bool DOMNode::IsNodeDisabled() const
{
    return nodeDisabled_;
}

void DOMNode::ResetDefaultStyles()
{
    width_ = Dimension(-1.0, DimensionUnit::PX);
    height_ = Dimension(-1.0, DimensionUnit::PX);

    paddingLeft_ = Dimension(0.0, DimensionUnit::PX);
    paddingRight_ = Dimension(0.0, DimensionUnit::PX);
    paddingTop_ = Dimension(0.0, DimensionUnit::PX);
    paddingBottom_ = Dimension(0.0, DimensionUnit::PX);

    marginLeft_ = Dimension(0.0, DimensionUnit::PX);
    marginRight_ = Dimension(0.0, DimensionUnit::PX);
    marginTop_ = Dimension(0.0, DimensionUnit::PX);
    marginBottom_ = Dimension(0.0, DimensionUnit::PX);

    flexGrow_ = 0.0;
    flexShrink_ = 1.0;
    flexBasis_ = 0.0;
    flexWeight_ = 0.0;

    minWidth_ = Dimension(0.0);
    minHeight_ = Dimension(0.0);
    maxWidth_ = Dimension(Size::INFINITE_SIZE);
    maxHeight_ = Dimension(Size::INFINITE_SIZE);
    displayIndex_ = 1;
    aspectRatio_ = -1.0;

    opacity_ = 1.0;

    display_ = DisplayType::NO_SETTING;
    hasDisplayStyle_ = false;
    displayComponent_.Reset();
    visibility_ = VisibilityType::NO_SETTING;
    if (!showAttr_.empty()) {
        hasDisplayStyle_ = true;
        SetShowAttr(showAttr_);
    }

    borderLeftEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    borderTopEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    borderRightEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    borderBottomEdge_ = BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID);
    border_ = Border(borderLeftEdge_, borderTopEdge_, borderRightEdge_, borderBottomEdge_);

    backDecoration_ = AceType::MakeRefPtr<Decoration>();
    frontDecoration_ = AceType::MakeRefPtr<Decoration>();
    gradient_ = Gradient();

    backgroundImage_ = AceType::MakeRefPtr<BackgroundImage>();

    if (transformComponent_) {
        transformComponent_->ResetTransform();
    }
}

void DOMNode::UpdatePseudoStyleByStatus(int32_t status, bool isBackendChange)
{
    // first:use status as the key, search the complete matched;
    // second:if first do not matched any, calculate the max value of key & status, select the max value one.
    std::unordered_map<std::string, std::string> matchedStyleMap;
    auto matchedStyle = pseudoClassStyleMap_.find(status);
    if (matchedStyle != pseudoClassStyleMap_.end()) {
        matchedStyleMap = matchedStyle->second;
    } else {
        uint32_t maxAndResult = 0;
        uint32_t maxValueKey = pseudoClassStyleMap_.begin()->first;
        // status & map key, select the max result one
        for (const auto& pseudoClass : pseudoClassStyleMap_) {
            uint32_t key = pseudoClass.first;
            uint32_t andResult = key & status;
            if (andResult > maxAndResult) {
                maxAndResult = andResult;
                maxValueKey = key;
            }
        }
        // if matched style except none pseudo style
        if (maxAndResult > 0) {
            matchedStyleMap = pseudoClassStyleMap_.find(maxValueKey)->second;
        }
    }

    ResetDefaultStyles();
    ResetInitializedStyle();

    // if not none pseudo style, need set none pseudo style first.
    auto nonePseudoStylesIter = pseudoClassStyleMap_.find(STATE_NORMAL);
    if (status != STATE_NORMAL && nonePseudoStylesIter != pseudoClassStyleMap_.end()) {
        for (const auto& noneTypeStyle : nonePseudoStylesIter->second) {
            SetCurrentStyle(noneTypeStyle);
        }
    }
    for (const auto& style : matchedStyleMap) {
        SetCurrentStyle(style);
    }
    if (isBackendChange) {
        auto pipelineContext = pipelineContext_.Upgrade();
        if (!pipelineContext) {
            LOGE("pipelineContext_ is nullptr");
            return;
        }
        if (GetTag() != DOM_NODE_TAG_SPAN) {
            UpdateUiComponents();
        }
        PrepareSpecializedComponent();
        CompositeComponents();
        rootComponent_->MarkNeedUpdate();
        rootComponent_->SetUpdateType(UpdateType::STYLE);
        pipelineContext->ScheduleUpdate(rootComponent_);
    }
}

uint32_t DOMNode::CalculatePseudoStatus() const
{
    uint32_t status = STATE_NORMAL;
    if (isActive_) {
        status |= STATE_ACTIVE;
    }
    if (nodeDisabled_) {
        status |= STATE_DISABLED;
    }
    if (isFocus_) {
        status |= STATE_FOCUS;
    }
    if (isChecked_) {
        status |= STATE_CHECKED;
    }
    if (isWaiting_) {
        status |= STATE_WAITING;
    }
    return status;
}

void DOMNode::UpdateStyleWithChildren()
{
    auto status = CalculatePseudoStatus();
    UpdatePseudoStyleByStatus(status, true);

    for (const auto& child : children_) {
        if (child) {
            child->UpdateStyleWithChildren();
        }
    }
}

void DOMNode::UpdatePseudoStyle(bool isBackendChange)
{
    if (!HasPseudo()) {
        return;
    }
    auto status = CalculatePseudoStatus();
    LOGD("UpdatePseudoStyle status is:%{public}d, isBackendChange:%{public}d", status, isBackendChange);
    if (!isBackendChange) {
        UpdatePseudoStyleByStatus(status, false);
        return;
    }
    // Triggered by backend, elements may processing build or layout now. So post a new task to UI thread.
    auto context = GetPipelineContext().Upgrade();
    if (!context) {
        LOGE("Context is null!");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), status = status]() {
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            node->UpdatePseudoStyleByStatus(status, true);
        },
        TaskExecutor::TaskType::UI);
}

void DOMNode::SetStyle(const std::vector<std::pair<std::string, std::string>>& styles)
{
    ACE_SCOPED_TRACE("DOMNode::SetStyle");

    for (const auto& style : styles) {
        CachePseudoClassStyle(style);
        if (style.first.find(DOM_PSEUDO_CLASS_SYMBOL) == std::string::npos) {
            SetCurrentStyle(style);
        }
    }
    OnSetStyleFinished();
}

void DOMNode::CachePseudoClassStyle(const std::pair<std::string, std::string>& pseudoClassStyle)
{
    uint32_t pseudoClassType = STATE_NORMAL;
    const auto& styleKey = pseudoClassStyle.first;

    if (styleKey.find(DOM_ACTIVE_PSEUDO_CLASS) != std::string::npos) {
        pseudoClassType |= STATE_ACTIVE;
    }

    if (styleKey.find(DOM_DISABLED_PSEUDO_CLASS) != std::string::npos) {
        pseudoClassType |= STATE_DISABLED;
    }

    if (styleKey.find(DOM_FOCUS_PSEUDO_CLASS) != std::string::npos) {
        pseudoClassType |= STATE_FOCUS;
    }

    if (styleKey.find(DOM_CHECKED_PSEUDO_CLASS) != std::string::npos) {
        pseudoClassType |= STATE_CHECKED;
    }

    if (styleKey.find(DOM_WAITING_PSEUDO_CLASS) != std::string::npos) {
        pseudoClassType |= STATE_WAITING;
    }

    cachedPseudoType_ |= pseudoClassType;

    auto pseudoSymbolLocation = styleKey.find(DOM_PSEUDO_CLASS_SYMBOL);
    auto dealedStyleKey =
        ((pseudoSymbolLocation != std::string::npos) ? styleKey.substr(0, pseudoSymbolLocation) : styleKey);

    auto styleMapIter = pseudoClassStyleMap_.find(pseudoClassType);

    if (styleMapIter != pseudoClassStyleMap_.end()) {
        auto result = styleMapIter->second.try_emplace(dealedStyleKey, pseudoClassStyle.second);
        if (!result.second) {
            result.first->second = pseudoClassStyle.second;
        }
        return;
    }
    std::unordered_map<std::string, std::string> newPseudoMap;
    newPseudoMap.emplace(dealedStyleKey, pseudoClassStyle.second);
    pseudoClassStyleMap_.emplace(pseudoClassType, newPseudoMap);
}

void DOMNode::SetCurrentStyle(const std::pair<std::string, std::string>& style)
{
    if (SetSpecializedStyle(style)) {
        // If the subclass consumes this property, it will no longer look in the general property.
        return;
    }
    // Operator map for styles
    static const std::unordered_map<std::string, void (*)(const std::string&, DOMNode&)> styleOperators = {
        // Set width and height
        { DOM_WIDTH, [](const std::string& val, DOMNode& node) {
                    node.width_ = node.ParseDimension(val);
                    node.hasBoxStyle_ = true;
                } },
        { DOM_HEIGHT, [](const std::string& val, DOMNode& node) {
                    node.height_ = node.ParseDimension(val);
                    node.hasBoxStyle_ = true;
                } },

        // Set padding
        { DOM_PADDING, &DOMNode::SetPaddingOverall},
        { DOM_PADDING_LEFT, [](const std::string& val, DOMNode& node) {
                            node.paddingLeft_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_PADDING_RIGHT, [](const std::string& val, DOMNode& node) {
                            node.paddingRight_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_PADDING_TOP, [](const std::string& val, DOMNode& node) {
                            node.paddingTop_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_PADDING_BOTTOM, [](const std::string& val, DOMNode& node) {
                            node.paddingBottom_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_PADDING_START, [](const std::string& val, DOMNode& node) {
                            if (node.IsRightToLeft()) {
                                node.paddingRight_ = node.ParseDimension(val);
                            } else {
                                node.paddingLeft_ = node.ParseDimension(val);
                            }
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_PADDING_END, [](const std::string& val, DOMNode& node) {
                            if (node.IsRightToLeft()) {
                                node.paddingLeft_ = node.ParseDimension(val);
                            } else {
                                node.paddingRight_ = node.ParseDimension(val);
                            }
                            node.hasBoxStyle_ = true;
                        } },
        // Set margin
        { DOM_MARGIN, &DOMNode::SetMarginOverall},
        { DOM_MARGIN_LEFT, [](const std::string& val, DOMNode& node) {
                            node.marginLeft_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_MARGIN_RIGHT, [](const std::string& val, DOMNode& node) {
                            node.marginRight_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_MARGIN_TOP, [](const std::string& val, DOMNode& node) {
                            node.marginTop_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_MARGIN_BOTTOM, [](const std::string& val, DOMNode& node) {
                            node.marginBottom_ = node.ParseDimension(val);
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_MARGIN_START, [](const std::string& val, DOMNode& node) {
                            if (node.IsRightToLeft()) {
                                node.marginRight_ = node.ParseDimension(val);
                            } else {
                                node.marginLeft_ = node.ParseDimension(val);
                            }
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_MARGIN_END, [](const std::string& val, DOMNode& node) {
                            if (node.IsRightToLeft()) {
                                node.marginLeft_ = node.ParseDimension(val);
                            } else {
                                node.marginRight_ = node.ParseDimension(val);
                            }
                            node.hasBoxStyle_ = true;
                        } },
        { DOM_LAYOUT_IN_BOX, [](const std::string& val, DOMNode& node) {
                            node.layoutInBox_ = StringToBool(val);
                            node.hasBoxStyle_ = true;
                        } },
        // Set flex
        { DOM_FLEX, [](const std::string& val, DOMNode& node) { node.flexGrow_ = StringToDouble(val); } },
        { DOM_FLEX_GROW, [](const std::string& val, DOMNode& node) { node.flexGrow_ = StringToDouble(val); } },
        { DOM_FLEX_SHRINK, [](const std::string& val, DOMNode& node) { node.flexShrink_ = StringToDouble(val); } },
        { DOM_FLEX_BASIS, [](const std::string& val, DOMNode& node) { node.flexBasis_ = StringToDouble(val); } },
        { DOM_FLEX_WEIGHT, [](const std::string& val, DOMNode& node) { node.flexWeight_ = StringToDouble(val); } },
        { DOM_MIN_WIDTH, [](const std::string& val, DOMNode& node) { node.minWidth_ = node.ParseDimension(val); } },
        { DOM_MIN_HEIGHT, [](const std::string& val, DOMNode& node) { node.minHeight_ = node.ParseDimension(val); } },
        { DOM_MAX_WIDTH, [](const std::string& val, DOMNode& node) { node.maxWidth_ = node.ParseDimension(val); } },
        { DOM_MAX_HEIGHT, [](const std::string& val, DOMNode& node) { node.maxHeight_ = node.ParseDimension(val); } },
        { DOM_DISPLAY_INDEX, [](const std::string& val, DOMNode& node) { node.displayIndex_ = StringToInt(val); } },
        { DOM_ASPECT_RATIO, [](const std::string& val, DOMNode& node) { node.aspectRatio_ = StringToDouble(val); } },
        { DOM_ALIGN_SELF, [](const std::string& val, DOMNode& node) { node.alignSelf_ = val; } },
        // Set display
        { DOM_OPACITY, [](const std::string& val, DOMNode& node) {
                        node.opacity_ = node.ParseDouble(val);
                        node.hasDisplayStyle_ = true;
                    } },
        { DOM_OVERFLOW_STYLE, [](const std::string& val, DOMNode& node) {
                node.overflow_ = ConvertStrToOverflow(val);
                node.hasOverflowStyle_ = true;
            } },
        { DOM_DISPLAY,
            [](const std::string& val, DOMNode& node) {
                node.display_ = (val == DOM_DISPLAY_NONE)
                                    ? DisplayType::NONE
                                    : (val == DOM_DISPLAY_GRID) ? DisplayType::GRID : DisplayType::FLEX;
                node.hasDisplayStyle_ = true;
            } },
        { DOM_VISIBILITY,
            [](const std::string& val, DOMNode& node) {
                node.visibility_ = (val == DOM_VISIBILITY_HIDDEN) ? VisibilityType::HIDDEN : VisibilityType::VISIBLE;
                node.hasDisplayStyle_ = true;
            } },
        // Set border
        { BORDER, &DOMNode::SetBorderOverall},
        // Set border width
        { DOM_BORDER_WIDTH, &DOMNode::SetBorderWidthForFourEdges},
        { DOM_BORDER_LEFT_WIDTH, [](const std::string& val, DOMNode& node) {
                                node.borderLeftEdge_.SetWidth(node.ParseDimension(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_RIGHT_WIDTH, [](const std::string& val, DOMNode& node) {
                                node.borderRightEdge_.SetWidth(node.ParseDimension(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_TOP_WIDTH, [](const std::string& val, DOMNode& node) {
                                node.borderTopEdge_.SetWidth(node.ParseDimension(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_BOTTOM_WIDTH, [](const std::string& val, DOMNode& node) {
                                node.borderBottomEdge_.SetWidth(node.ParseDimension(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        // Set border color
        { DOM_BORDER_COLOR, &DOMNode::SetBorderColorForFourEdges},
        { DOM_BORDER_LEFT_COLOR, [](const std::string& val, DOMNode& node) {
                                node.borderLeftEdge_.SetColor(node.ParseColor(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_RIGHT_COLOR, [](const std::string& val, DOMNode& node) {
                                node.borderRightEdge_.SetColor(node.ParseColor(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_TOP_COLOR, [](const std::string& val, DOMNode& node) {
                                node.borderTopEdge_.SetColor(node.ParseColor(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_BOTTOM_COLOR, [](const std::string& val, DOMNode& node) {
                                    node.borderBottomEdge_.SetColor(node.ParseColor(val));
                                    node.hasDecorationStyle_ = true;
                                    node.hasBorderStyle_ = true;
                                } },
        // Set border radius
        { DOM_BORDER_TOP_LEFT_RADIUS, [](const std::string& val, DOMNode& node) {
                                        node.border_.SetTopLeftRadius(Radius(node.ParseDimension(val)));
                                        node.hasDecorationStyle_ = true;
                                        node.hasBorderStyle_ = true;
                                        node.hasBorderRadiusStyle_ = true;
                                    } },
        { DOM_BORDER_TOP_RIGHT_RADIUS, [](const std::string& val, DOMNode& node) {
                                        node.border_.SetTopRightRadius(Radius(node.ParseDimension(val)));
                                        node.hasDecorationStyle_ = true;
                                        node.hasBorderStyle_ = true;
                                        node.hasBorderRadiusStyle_ = true;
                                    } },
        { DOM_BORDER_BOTTOM_LEFT_RADIUS, [](const std::string& val, DOMNode& node) {
                                        node.border_.SetBottomLeftRadius(Radius(node.ParseDimension(val)));
                                        node.hasDecorationStyle_ = true;
                                        node.hasBorderRadiusStyle_ = true;
                                    } },
        { DOM_BORDER_BOTTOM_RIGHT_RADIUS, [](const std::string& val, DOMNode& node) {
                                        node.border_.SetBottomRightRadius(Radius(node.ParseDimension(val)));
                                        node.hasDecorationStyle_ = true;
                                        node.hasBorderStyle_ = true;
                                        node.hasBorderRadiusStyle_ = true;
                                    } },
        { DOM_BORDER_RADIUS, [](const std::string& val, DOMNode& node) {
                            node.border_.SetBorderRadius(Radius(node.ParseDimension(val)));
                            node.hasDecorationStyle_ = true;
                            node.hasBorderStyle_ = true;
                            node.hasBorderRadiusStyle_ = true;
                        } },
        // Set border style
        { DOM_BORDER_LEFT_STYLE, [](const std::string& val, DOMNode& node) {
                                node.borderLeftEdge_.SetStyle(ConvertStrToBorderStyle(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_RIGHT_STYLE, [](const std::string& val, DOMNode& node) {
                                    node.borderRightEdge_.SetStyle(ConvertStrToBorderStyle(val));
                                    node.hasDecorationStyle_ = true;
                                    node.hasBorderStyle_ = true;
                                } },
        { DOM_BORDER_TOP_STYLE, [](const std::string& val, DOMNode& node) {
                                node.borderTopEdge_.SetStyle(ConvertStrToBorderStyle(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBorderStyle_ = true;
                            } },
        { DOM_BORDER_BOTTOM_STYLE, [](const std::string& val, DOMNode& node) {
                                    node.borderBottomEdge_.SetStyle(ConvertStrToBorderStyle(val));
                                    node.hasDecorationStyle_ = true;
                                    node.hasBorderStyle_ = true;
                                } },
        { DOM_BORDER_STYLE, &DOMNode::SetBorderStyleForFourEdges},
        // Set position
        { DOM_POSITION,
            [](const std::string& val, DOMNode& node) {
                node.position_ = val == DOM_POSITION_FIXED
                                     ? PositionType::FIXED
                                     : val == DOM_POSITION_ABSOLUTE ? PositionType::ABSOLUTE : PositionType::RELATIVE;
                node.hasPositionStyle_ = true;
            } },
        { DOM_POSITION_LEFT,
            [](const std::string& val, DOMNode& node) {
                if (!val.empty()) {
                    node.left_ = node.ParseDimension(val);
                    node.hasPositionStyle_ = true;
                    node.hasLeft_ = true;
                }
            } },
        { DOM_POSITION_RIGHT,
            [](const std::string& val, DOMNode& node) {
                if (!val.empty()) {
                    node.right_ = node.ParseDimension(val);
                    node.hasPositionStyle_ = true;
                    node.hasRight_ = true;
                }
            } },
        { DOM_POSITION_TOP,
            [](const std::string& val, DOMNode& node) {
                if (!val.empty()) {
                    node.top_ = node.ParseDimension(val);
                    node.hasPositionStyle_ = true;
                    node.hasTop_ = true;
                }
            } },
        { DOM_POSITION_BOTTOM,
            [](const std::string& val, DOMNode& node) {
                if (!val.empty()) {
                    node.bottom_ = node.ParseDimension(val);
                    node.hasPositionStyle_ = true;
                    node.hasBottom_ = true;
                }
            } },
        // Set background color and image
        { DOM_BACKGROUND_COLOR, [](const std::string& val, DOMNode& node) {
                                node.backDecoration_->SetBackgroundColor(node.ParseColor(val));
                                node.hasDecorationStyle_ = true;
                                node.hasBackGroundColor_ = true;
                            } },
        { DOM_BACKGROUND_IMAGE, [](const std::string& val, DOMNode& node) {
                                node.backgroundImage_->SetSrc(val);
                                node.backDecoration_->SetImage(node.backgroundImage_);
                                node.hasDecorationStyle_ = true;
                            } },
        // Set background color and image
        { DOM_BOX_SHADOW_H, [](const std::string& val, DOMNode& node) {
                                node.shadow_.SetOffsetX(StringToDouble(val));
                                node.hasDecorationStyle_ = true;
                                node.hasShadowStyle_ = true;
                            } },
        { DOM_BOX_SHADOW_V, [](const std::string& val, DOMNode& node) {
                                node.shadow_.SetOffsetY(StringToDouble(val));
                                node.hasDecorationStyle_ = true;
                                node.hasShadowStyle_ = true;
                            } },
        { DOM_BOX_SHADOW_BLUR, [](const std::string& val, DOMNode& node) {
                                node.shadow_.SetBlurRadius(StringToDouble(val));
                                node.hasDecorationStyle_ = true;
                                node.hasShadowStyle_ = true;
                            } },
        { DOM_BOX_SHADOW_SPREAD, [](const std::string& val, DOMNode& node) {
                                node.shadow_.SetSpreadRadius(StringToDouble(val));
                                node.hasDecorationStyle_ = true;
                                node.hasShadowStyle_ = true;
                            } },
        { DOM_BOX_SHADOW_COLOR, [](const std::string& val, DOMNode& node) {
                                if (val.empty()) {
                                    node.shadow_.SetColor(Color::BLACK);
                                    return;
                                }
                                node.shadow_.SetColor(node.ParseColor(val));
                                node.hasDecorationStyle_ = true;
                                node.hasShadowStyle_ = true;
                            } },

        { DOM_BACKGROUND_IMAGE_SIZE, &DOMNode::SetBackgroundImageSize },
        { DOM_BACKGROUND_IMAGE_POSITION, &DOMNode::SetBackgroundImagePosition },
        { DOM_BACKGROUND_IMAGE_REPEAT, [](const std::string& val, DOMNode& node) {
                                        node.backgroundImage_->SetImageRepeat(ConvertStrToImageRepeat(val));
                                        node.hasDecorationStyle_ = true;
                                    } },
        { DOM_BACKGROUND, &DOMNode::SetBackground },
        { DOM_TRANSFORM, &DOMNode::SetTransform },
        { DOM_TRANSFORM_ORIGIN,
            [](const std::string& val, DOMNode& node) {
                if (!node.transformComponent_) {
                    node.transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
                }
                std::vector<std::string> offsets;
                StringUtils::StringSpliter(val, ' ', offsets);
                if (offsets.size() == TRANSFORM_SINGLE) {
                    Dimension originDimensionX = TRANSFORM_ORIGIN_DEFAULT;
                    Dimension originDimensionY = TRANSFORM_ORIGIN_DEFAULT;
                    // for Enum
                    if (CheckTransformEnum(val)) {
                        auto resultX = ConvertStrToTransformOrigin(val, Axis::HORIZONTAL);
                        if (resultX.first) {
                            originDimensionX = resultX.second;
                        }
                        auto resultY = ConvertStrToTransformOrigin(val, Axis::VERTICAL);
                        if (resultY.first) {
                            originDimensionY = resultY.second;
                        }
                    } else {
                        // for Dimension
                        originDimensionX = node.ParseDimension(val);
                    }
                    node.tweenOption_.SetTransformOrigin(originDimensionX, originDimensionY);
                    node.transformComponent_->SetOriginDimension(DimensionOffset(originDimensionX, originDimensionY));
                } else if (offsets.size() == TRANSFORM_DUAL) {
                    Dimension originDimensionX = TRANSFORM_ORIGIN_DEFAULT;
                    Dimension originDimensionY = TRANSFORM_ORIGIN_DEFAULT;
                    if (CheckTransformEnum(offsets[0])) {
                        auto result = ConvertStrToTransformOrigin(offsets[0], Axis::HORIZONTAL);
                        if (result.first) {
                            originDimensionX = result.second;
                        }
                    } else {
                        originDimensionX = node.ParseDimension(offsets[0]);
                    }

                    if (CheckTransformEnum(offsets[1])) {
                        auto result = ConvertStrToTransformOrigin(offsets[1], Axis::VERTICAL);
                        if (result.first) {
                            originDimensionY = result.second;
                        }
                    } else {
                        originDimensionY = node.ParseDimension(offsets[1]);
                    }
                    node.tweenOption_.SetTransformOrigin(originDimensionX, originDimensionY);
                    node.transformComponent_->SetOriginDimension(DimensionOffset(originDimensionX, originDimensionY));
                }
            } },
        { DOM_ANIMATION_DELAY, [](const std::string& val, DOMNode& node) {
                if (val.find("ms") != std::string::npos) {
                    node.tweenOption_.SetDelay(StringUtils::StringToInt(val));
                } else {
                    node.tweenOption_.SetDelay(StringUtils::StringToInt(val) * MS_TO_S);
                }
            } },
        { DOM_ANIMATION_DURATION, [](const std::string& val, DOMNode& node) {
                if (val.find("ms") != std::string::npos) {
                    node.tweenOption_.SetDuration(StringUtils::StringToInt(val));
                } else {
                    node.tweenOption_.SetDuration(StringUtils::StringToInt(val) * MS_TO_S);
                }
            } },
        { DOM_ANIMATION_ITERATION_COUNT,
            [](const std::string& val, DOMNode& node) {
                node.tweenOption_.SetIteration(StringUtils::StringToInt(val));
            } },
        { DOM_ANIMATION_TIMING_FUNCTION,
            [](const std::string& val, DOMNode& node) { node.tweenOption_.SetCurve(CreateCurve(val)); } },
        { DOM_ANIMATION_FILL_MODE,
            [](const std::string& val, DOMNode& node) { node.tweenOption_.SetFillMode(StringToFillMode(val)); } },
        { DOM_ANIMATION_DIRECTION,
          [](const std::string& val, DOMNode& node) {
                node.tweenOption_.SetAnimationDirection(StringToAnimationDirection(val));
          } },

        { DOM_TRANSITION_DURATION, [](const std::string& val, DOMNode& node) {
                if (val.find("ms") != std::string::npos) {
                    node.transitionEnterOption_.SetDuration(StringUtils::StringToInt(val));
                    node.transitionExitOption_.SetDuration(StringUtils::StringToInt(val));
                } else {
                    node.transitionEnterOption_.SetDuration(StringUtils::StringToInt(val) * MS_TO_S);
                    node.transitionExitOption_.SetDuration(StringUtils::StringToInt(val) * MS_TO_S);
                }
            } },
        { DOM_TRANSITION_TIMING_FUNCTION, [](const std::string& val, DOMNode& node) {
                node.transitionEnterOption_.SetCurve(CreateCurve(val));
                node.transitionExitOption_.SetCurve(CreateCurve(val));
            } },
        { DOM_SHARED_TRANSITION_TIMING_FUNCTION,
            [](const std::string& val, DOMNode& node) { node.sharedTransitionOption_.SetCurve(CreateCurve(val)); } },
        { DOM_SHARED_TRANSITION_EFFECT,
            [](const std::string& val, DOMNode& node) { node.sharedEffect_ = ParseSharedEffect(val, node); } },
        // set filter
        { DOM_FILTER,
            [](const std::string& val, DOMNode& node) {
                node.hasFrontDecorationStyle_ = true;
                if (!node.frontDecoration_) {
                    node.frontDecoration_ = AceType::MakeRefPtr<Decoration>();
                }
                auto radius = ParseFunctionValue<Dimension>(val, DOM_BLUR, StringToDimension);
                if (radius.IsValid()) {
                    node.frontDecoration_->SetBlurRadius(radius);
                } else {
                    node.frontDecoration_->SetBlurRadius(Dimension {});
                }
            } },
        // set backdrop-filter
        { DOM_BACKDROP_FILTER,
            [](const std::string& val, DOMNode& node) {
                node.hasDecorationStyle_ = true;
                auto radius = ParseFunctionValue<Dimension>(val, DOM_BLUR, StringToDimension);
                if (radius.IsValid()) {
                    node.backDecoration_->SetBlurRadius(radius);
                } else {
                    node.backDecoration_->SetBlurRadius(Dimension {});
                }
            } },
        // card transition
        { DOM_TRANSITION_EFFECT,
            [](const std::string& val, DOMNode& node) {
                node.hasTransitionAnimation_ = true;
                if (!node.transformComponent_) {
                    node.transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
                }
                node.transformComponent_->SetTransitionEffect(ParseTransitionEffect(val));
            } },
        { DOM_WINDOW_FILTER,
            [](const std::string& val, DOMNode& node) {
                node.hasDecorationStyle_ = true;

                std::vector<std::string> offsets;
                StringUtils::StringSpliter(val, ' ', offsets);
                // progress
                if (offsets.size() >= SINGLE_VALUE) {
                    auto value = ParseFunctionValue<Dimension>(offsets[0], DOM_BLUR, StringToDimension);
                    if (value.Unit() == DimensionUnit::PERCENT) {
                        auto progress = value.Value();
                        if (GreatNotEqual(progress, 0.0) && LessOrEqual(progress, 1.0)) {
                            node.backDecoration_->SetWindowBlurProgress(static_cast<float>(progress));
                        }
                    } else {
                        node.backDecoration_->SetWindowBlurProgress(static_cast<float>(0.0f));
                    }
                }
                // style
                if (offsets.size() >= TWO_VALUES) {
                    auto value = StrToWindowBlurStyle(offsets[1]);
                    node.backDecoration_->SetWindowBlurStyle(value);
                }
            } },
        { DOM_ZINDEX,
            [](const std::string& val, DOMNode& node) {
                node.zIndex_ = StringToInt(val);
            } },
        // scroll bar
        { DOM_SCROLL_OVER_SCROLL_EFFECT,
            [](const std::string& val, DOMNode& node) {
                if (val == DOM_SCROLL_EFFECT_SPRING) {
                    node.edgeEffect_ = EdgeEffect::SPRING;
                } else if (val == DOM_SCROLL_EFFECT_FADE) {
                    node.edgeEffect_ = EdgeEffect::FADE;
                } else {
                    node.edgeEffect_ = EdgeEffect::NONE;
                }
            } },
        { DOM_SCROLL_SCROLLBAR_COLOR,
            [](const std::string& val, DOMNode& node) {
                node.scrollBarColor_.first = true;
                node.scrollBarColor_.second = node.ParseColor(val);
            } },
        { DOM_SCROLL_SCROLLBAR_WIDTH,
            [](const std::string& val, DOMNode& node) {
                node.scrollBarWidth_.first = true;
                auto width = node.ParseDimension(val);
                node.scrollBarWidth_.second = width.IsValid() ? width : Dimension();
            } },
    };
    auto operatorIter = styleOperators.find(style.first);
    if (operatorIter != styleOperators.end()) {
        operatorIter->second(style.second, *this);
    }
    static const std::unordered_set<std::string> displayStyleSet = { DOM_OPACITY, DOM_DISPLAY, DOM_VISIBILITY };
    if (displayStyleSet.find(style.first) != displayStyleSet.end() &&
        AceApplicationInfo::GetInstance().GetIsCardType() && showAttr_ == "false") {
        SetShowAttr(showAttr_);
    }
}

void DOMNode::GenerateComponentNode()
{
    UpdatePseudoStyle(false);
    if (GetTag() != DOM_NODE_TAG_SPAN) {
        UpdateUiComponents();
        UpdateTouchEventComponent();
        UpdateGestureEventComponent();
        UpdateMouseEventComponent();
        UpdateFocusableEventComponents();
        // Prepare for fixed position
        UpdatePositionComponent();
#ifndef WEARABLE_PRODUCT
        UpdateMultimodalComponent();
        PrepareScrollComponent();
#endif
    }
    PrepareSpecializedComponent();
    CompositeComponents();
    // Relative and absolute position needs to update the top component props.
    UpdatePositionProps();
    auto rootChild = AceType::DynamicCast<RenderComponent>(rootComponent_->GetChild());
    if (isCustomComponent_) {
        if (rootChild) {
            rootChild->SetIsCustomComponent(isCustomComponent_);
            rootChild->SetOnLayoutReadyMarker(EventMarker(GetNodeIdForEvent(), ""));
        }
    }
    if (rootChild) {
        rootChild->SetZIndex(zIndex_);
    }
    rootComponent_->MarkNeedUpdate();
}

void DOMNode::AddNode(const RefPtr<DOMNode>& node, int32_t slot)
{
    if (!node) {
        return;
    }
    auto isExist = std::find_if(children_.begin(), children_.end(),
        [node](const RefPtr<DOMNode>& child) { return child->GetNodeId() == node->GetNodeId(); });
    if (isExist != children_.end()) {
        LOGW("the node[%{public}d] has already in the children", node->GetNodeId());
        return;
    }
    auto pos = children_.begin();
    std::advance(pos, slot);
    children_.insert(pos, node);
    if (node->position_ != PositionType::FIXED) {
        if (!node->IsProxy() && display_ == DisplayType::NONE) {
            node->GenerateComponentNode();
        }
        OnChildNodeAdded(node, slot);
    }
}

void DOMNode::RemoveNode(const RefPtr<DOMNode>& node)
{
    if (!node) {
        return;
    }
    children_.remove_if([node](const RefPtr<DOMNode>& child) { return node->GetNodeId() == child->GetNodeId(); });
    if (node->position_ != PositionType::FIXED) {
        OnChildNodeRemoved(node);
    }
}

void DOMNode::SetDisplayStyle()
{
    switch (display_) {
        case DisplayType::NONE:
            visible_ = VisibleType::GONE;
            break;
        case DisplayType::GRID:
        case DisplayType::FLEX:
        default:
            visible_ = (visibility_ == VisibilityType::HIDDEN) ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
            break;
    }
}

void SetBgImgSizeX(const BackgroundImageSizeType type, const double value, BackgroundImageSize& bgImgSize)
{
    bgImgSize.SetSizeTypeX(type);
    bgImgSize.SetSizeValueX(value);
}

void SetBgImgSizeY(const BackgroundImageSizeType type, const double value, BackgroundImageSize& bgImgSize)
{
    bgImgSize.SetSizeTypeY(type);
    bgImgSize.SetSizeValueY(value);
}

const RefPtr<PageTransitionComponent>& DOMNode::BuildTransitionComponent()
{
    transitionComponent_ = AceType::MakeRefPtr<PageTransitionComponent>();
    if (isRightToLeft_) {
        transitionComponent_->SetTextDirection(TextDirection::RTL);
    }
    if (transitionEnterOption_.IsValid() || transitionExitOption_.IsValid()) {
        if (!transitionEnterOption_.GetCurve()) {
            // use FRICTION as transition default curve.
            transitionEnterOption_.SetCurve(Curves::FRICTION);
            transitionExitOption_.SetCurve(Curves::FRICTION);
        }
        transitionComponent_->SetContentTransitionOption(transitionEnterOption_, transitionExitOption_);
    }
    return transitionComponent_;
}

void DOMNode::SetBackgroundImageSize(const std::string& value, DOMNode& node)
{
    static const LinearMapNode<BackgroundImageSizeType> bgImageSizeType[] = {
        { DOM_BACKGROUND_IMAGE_SIZE_AUTO, BackgroundImageSizeType::AUTO },
        { DOM_BACKGROUND_IMAGE_SIZE_CONTAIN, BackgroundImageSizeType::CONTAIN },
        { DOM_BACKGROUND_IMAGE_SIZE_COVER, BackgroundImageSizeType::COVER },
    };
    BackgroundImageSize bgImgSize;
    auto spaceIndex = value.find(' ', 0);
    if (spaceIndex != std::string::npos) {
        std::string valueX = value.substr(0, spaceIndex);
        std::string valueY = value.substr(spaceIndex + 1, value.size() - spaceIndex - 1);
        if (valueX.find("px") != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::LENGTH, StringToDouble(valueX), bgImgSize);
        } else if (valueX.find('%') != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::PERCENT, StringToDouble(valueX), bgImgSize);
        } else {
            bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
        }
        if (valueY.find("px") != std::string::npos) {
            SetBgImgSizeY(BackgroundImageSizeType::LENGTH, StringToDouble(valueY), bgImgSize);
        } else if (valueY.find('%') != std::string::npos) {
            SetBgImgSizeY(BackgroundImageSizeType::PERCENT, StringToDouble(valueY), bgImgSize);
        } else {
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        }
    } else {
        auto sizeTypeIter = BinarySearchFindIndex(bgImageSizeType, ArraySize(bgImageSizeType), value.c_str());
        if (sizeTypeIter != -1) {
            bgImgSize.SetSizeTypeX(bgImageSizeType[sizeTypeIter].value);
            bgImgSize.SetSizeTypeY(bgImageSizeType[sizeTypeIter].value);
        } else if (value.find("px") != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::LENGTH, StringToDouble(value), bgImgSize);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        } else if (value.find('%') != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::PERCENT, StringToDouble(value), bgImgSize);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        } else {
            bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        }
    }
    node.backgroundImage_->SetImageSize(
        bgImgSize.GetSizeTypeX(), bgImgSize.GetSizeValueX(), bgImgSize.GetSizeTypeY(), bgImgSize.GetSizeValueY());
    node.hasDecorationStyle_ = true;
}

void DOMNode::SetBackgroundImagePosition(const std::string& value, DOMNode& node)
{
    BackgroundImagePosition backgroundImagePosition;
    if (!ParseBackgroundImagePosition(value, backgroundImagePosition)) {
        LOGE("Invalid background image position.");
        return;
    }
    node.backgroundImage_->SetImagePosition(backgroundImagePosition.GetSizeTypeX(),
        backgroundImagePosition.GetSizeValueX(), backgroundImagePosition.GetSizeTypeY(),
        backgroundImagePosition.GetSizeValueY());
    node.hasDecorationStyle_ = true;
}

void DOMNode::SetBackground(const std::string& value, DOMNode& node)
{
    LOGD("DOMNode::SetBackground value:%{private}s", value.c_str());
    auto backgroundJson = JsonUtil::ParseJsonString(value);
    if (!backgroundJson->IsObject()) {
        LOGE("background json is not Object");
        return;
    }
    if (backgroundJson->Contains(DOM_VALUES) && backgroundJson->GetValue(DOM_VALUES)->IsArray() &&
        backgroundJson->GetValue(DOM_VALUES)->GetArraySize() > 0) {
        node.gradient_ = Gradient();
        auto values = backgroundJson->GetValue(DOM_VALUES)->GetArrayItem(0);
        if (values->Contains(DOM_GRADIENT_TYPE) && values->GetValue(DOM_GRADIENT_TYPE)->IsString()) {
            SetGradientType(values->GetValue(DOM_GRADIENT_TYPE)->GetString(), node);
        }
        if (values->Contains(DOM_GRADIENT_DIRECTIONS) && values->GetValue(DOM_GRADIENT_DIRECTIONS)->IsArray()) {
            SetGradientDirections(values->GetValue(DOM_GRADIENT_DIRECTIONS), node);
        }
        if (values->Contains(DOM_GRADIENT_VALUES) && values->GetValue(DOM_GRADIENT_VALUES)->IsArray()) {
            SetGradientColor(values->GetValue(DOM_GRADIENT_VALUES), node);
        }
    }
    node.hasDecorationStyle_ = true;
    node.hasBackGroundColor_ = true;
}

void DOMNode::SetBorderColorForFourEdges(const std::string& value, DOMNode& node)
{
    node.borderLeftEdge_.SetColor(node.ParseColor(value));
    node.borderRightEdge_.SetColor(node.ParseColor(value));
    node.borderTopEdge_.SetColor(node.ParseColor(value));
    node.borderBottomEdge_.SetColor(node.ParseColor(value));
    node.hasDecorationStyle_ = true;
    node.hasBorderStyle_ = true;
}

void DOMNode::SetBorderStyleForFourEdges(const std::string& value, DOMNode& node)
{
    node.borderLeftEdge_.SetStyle(ConvertStrToBorderStyle(value));
    node.borderRightEdge_.SetStyle(ConvertStrToBorderStyle(value));
    node.borderTopEdge_.SetStyle(ConvertStrToBorderStyle(value));
    node.borderBottomEdge_.SetStyle(ConvertStrToBorderStyle(value));
    node.hasDecorationStyle_ = true;
    node.hasBorderStyle_ = true;
}

void DOMNode::SetBorderWidthForFourEdges(const std::string& value, DOMNode& node)
{
    node.borderLeftEdge_.SetWidth(node.ParseDimension(value));
    node.borderRightEdge_.SetWidth(node.ParseDimension(value));
    node.borderTopEdge_.SetWidth(node.ParseDimension(value));
    node.borderBottomEdge_.SetWidth(node.ParseDimension(value));
    node.hasDecorationStyle_ = true;
    node.hasBorderStyle_ = true;
}

void DOMNode::SetBorderOverall(const std::string& value, DOMNode& node)
{
    std::vector<std::string> offsets;
    StringUtils::StringSpliter(value, ' ', offsets);
    switch (offsets.size()) {
        case SINGLE_VALUE:
            if (offsets[0].find("px") != std::string::npos) {
                SetBorderWidthForFourEdges(offsets[0], node);
            } else if (offsets[0] == "solid" || offsets[0] == "dotted" || offsets[0] == "dashed") {
                SetBorderStyleForFourEdges(offsets[0], node);
            } else {
                SetBorderColorForFourEdges(offsets[0], node);
            }
            break;
        case TWO_VALUES:
            SetBorderWidthForFourEdges(offsets[0], node);
            SetBorderStyleForFourEdges(offsets[1], node);
            break;
        case THREE_VALUES:
            SetBorderWidthForFourEdges(offsets[0], node);
            SetBorderStyleForFourEdges(offsets[1], node);
            SetBorderColorForFourEdges(offsets[2], node);
            break;
        default:
            break;
    }
}

void DOMNode::SetGradientType(const std::string& gradientType, DOMNode& node)
{
    if (gradientType == DOM_REPEATING_LINEAR_GRADIENT) {
        node.gradient_.SetRepeat(true);
        node.hasDecorationStyle_ = true;
    }
}

void DOMNode::SetGradientDirections(const std::unique_ptr<JsonValue>& gradientDirections, DOMNode& node)
{
    std::unique_ptr<JsonValue> angleItem;
    std::unique_ptr<JsonValue> sideItem;
    std::unique_ptr<JsonValue> cornerItem;
    GradientDirection direction;
    switch (gradientDirections->GetArraySize()) {
        case DIRECTION_ANGLE:
            angleItem = gradientDirections->GetArrayItem(0);
            if (angleItem->IsString()) {
                node.gradient_.SetUseAngle(true);
                node.gradient_.SetAngle(StringToDouble(angleItem->GetString()));
                node.hasDecorationStyle_ = true;
            }
            break;
        case DIRECTION_SIDE:
            sideItem = gradientDirections->GetArrayItem(1);
            if (sideItem->IsString()) {
                direction = StrToGradientDirection(sideItem->GetString());
                node.gradient_.SetDirection(direction);
                node.hasDecorationStyle_ = true;
            }
            break;
        case DIRECTION_CORNER:
            sideItem = gradientDirections->GetArrayItem(1);
            cornerItem = gradientDirections->GetArrayItem(2);
            if (sideItem->IsString() && cornerItem->IsString()) {
                direction = StrToGradientDirectionCorner(sideItem->GetString(), cornerItem->GetString());
                node.gradient_.SetDirection(direction);
                node.hasDecorationStyle_ = true;
            }
            break;
        default:
            LOGE("gradientDirectionsLength error");
            break;
    }
}

void DOMNode::SetGradientColor(const std::unique_ptr<JsonValue>& gradientColorValues, DOMNode& node)
{
    node.gradient_.ClearColors();
    int32_t gradientColorValuesLength = gradientColorValues->GetArraySize();
    for (int32_t i = 0; i < gradientColorValuesLength; i++) {
        std::string gradientColorValue = gradientColorValues->GetArrayItem(i)->GetString();
        GradientColor gradientColor;
        RemoveHeadTailSpace(gradientColorValue);
        auto index = gradientColorValue.find(' ');
        if (index != std::string::npos && index != 0) {
            std::string color = gradientColorValue.substr(0, index);
            std::string area = gradientColorValue.substr(index + 1, gradientColorValue.size() - index - 1);
            gradientColor.SetColor(node.ParseColor(color));
            gradientColor.SetHasValue(true);
            if (area.find("px") != std::string::npos) {
                gradientColor.SetDimension(StringToDouble(area), DimensionUnit::PX);
            } else if (area.find('%') != std::string::npos) {
                gradientColor.SetDimension(StringToDouble(area), DimensionUnit::PERCENT);
            } else {
                LOGW("gradientColor DimensionUnit is incorrect)");
                gradientColor.SetHasValue(false);
            }
        } else {
            gradientColor.SetHasValue(false);
            gradientColor.SetColor(node.ParseColor(gradientColorValue));
        }
        node.gradient_.AddColor(gradientColor);
        node.hasDecorationStyle_ = true;
    }
}

void DOMNode::SetMarginOverall(const std::string& value, DOMNode& node)
{
    std::vector<std::string> offsets;
    StringUtils::StringSpliter(value, ' ', offsets);
    switch (offsets.size()) {
        case SINGLE_VALUE:
            node.marginLeft_ = node.ParseDimension(offsets[0]);
            node.marginRight_ = node.ParseDimension(offsets[0]);
            node.marginTop_ = node.ParseDimension(offsets[0]);
            node.marginBottom_ = node.ParseDimension(offsets[0]);
            break;
        case TWO_VALUES:
            node.marginLeft_ = node.ParseDimension(offsets[1]);
            node.marginRight_ = node.ParseDimension(offsets[1]);
            node.marginTop_ = node.ParseDimension(offsets[0]);
            node.marginBottom_ = node.ParseDimension(offsets[0]);
            break;
        case THREE_VALUES:
            node.marginLeft_ = node.ParseDimension(offsets[1]);
            node.marginRight_ = node.ParseDimension(offsets[1]);
            node.marginTop_ = node.ParseDimension(offsets[0]);
            node.marginBottom_ = node.ParseDimension(offsets[2]);
            break;
        case FOUR_VALUES:
            node.marginLeft_ = node.ParseDimension(offsets[3]);
            node.marginRight_ = node.ParseDimension(offsets[1]);
            node.marginTop_ = node.ParseDimension(offsets[0]);
            node.marginBottom_ = node.ParseDimension(offsets[2]);
            break;
        default:
            break;
    }
    node.hasBoxStyle_ = true;
}

void DOMNode::SetPaddingOverall(const std::string& value, DOMNode& node)
{
    std::vector<std::string> offsets;
    StringUtils::StringSpliter(value, ' ', offsets);
    switch (offsets.size()) {
        case SINGLE_VALUE:
            node.paddingLeft_ = node.ParseDimension(offsets[0]);
            node.paddingRight_ = node.ParseDimension(offsets[0]);
            node.paddingTop_ = node.ParseDimension(offsets[0]);
            node.paddingBottom_ = node.ParseDimension(offsets[0]);
            break;
        case TWO_VALUES:
            node.paddingLeft_ = node.ParseDimension(offsets[1]);
            node.paddingRight_ = node.ParseDimension(offsets[1]);
            node.paddingTop_ = node.ParseDimension(offsets[0]);
            node.paddingBottom_ = node.ParseDimension(offsets[0]);
            break;
        case THREE_VALUES:
            node.paddingLeft_ = node.ParseDimension(offsets[1]);
            node.paddingRight_ = node.ParseDimension(offsets[1]);
            node.paddingTop_ = node.ParseDimension(offsets[0]);
            node.paddingBottom_ = node.ParseDimension(offsets[2]);
            break;
        case FOUR_VALUES:
            node.paddingLeft_ = node.ParseDimension(offsets[3]);
            node.paddingRight_ = node.ParseDimension(offsets[1]);
            node.paddingTop_ = node.ParseDimension(offsets[0]);
            node.paddingBottom_ = node.ParseDimension(offsets[2]);
            break;
        default:
            break;
    }
    node.hasBoxStyle_ = true;
}

std::string DOMNode::GetTransformType(const std::unique_ptr<JsonValue>& transformJson)
{
    if (transformJson->IsNull()) {
        LOGE("transformJson is null");
        return "";
    }
    return transformJson->GetKey();
}

std::string DOMNode::GetTransformTypeValue(const std::unique_ptr<JsonValue>& transformJson)
{
    if (transformJson->IsNull()) {
        LOGE("transformJson is null");
        return "";
    }
    std::string jsonValue = transformJson->GetString();
    if (jsonValue.empty()) {
        double jsonDouble = transformJson->GetDouble();
        return std::to_string(jsonDouble);
    }
    return jsonValue;
}

void DOMNode::SetTransform(const std::string& value, DOMNode& node)
{
    if (!node.transformComponent_) {
        node.transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
    }
    node.transformComponent_->ResetTransform(); // Avoid transfrom effect overlay.
    auto jsonValue = node.GetTransformJsonValue(value);
    std::unique_ptr<JsonValue> transformJson = JsonUtil::ParseJsonString(jsonValue);
    for (int32_t index = 0; index < transformJson->GetArraySize(); ++index) {
        std::string typeKey = node.GetTransformType(transformJson->GetArrayItem(index));
        std::string typeValue = node.GetTransformTypeValue(transformJson->GetArrayItem(index));
        if ((!typeKey.empty()) && (!typeValue.empty())) {
            // Operator map for transform
            static const std::unordered_map<std::string, void (*)(const std::string&, DOMNode&)> transformOperators = {
                { DOM_ROTATE,
                    [](const std::string& typeValue, DOMNode& node) {
                        node.transformComponent_->RotateZ(StringUtils::StringToDegree(typeValue));
                    } },
                { DOM_ROTATE_X,
                    [](const std::string& typeValue, DOMNode& node) {
                        node.transformComponent_->RotateX(StringUtils::StringToDegree(typeValue));
                    } },
                { DOM_ROTATE_Y,
                    [](const std::string& typeValue, DOMNode& node) {
                        node.transformComponent_->RotateY(StringUtils::StringToDegree(typeValue));
                    } },
                { SCALE,
                    [](const std::string& typeValue, DOMNode& node) {
                        if (typeValue.find(' ', 0) != std::string::npos) {
                            Offset offset = ConvertStrToOffset(typeValue);
                            node.transformComponent_->Scale(offset.GetX(), offset.GetY());
                        } else {
                            auto scaleValue = StringToDouble(typeValue);
                            node.transformComponent_->Scale(scaleValue, scaleValue);
                        }
                    } },
                { DOM_SCALE_X, [](const std::string& typeValue,
                               DOMNode& node) { node.transformComponent_->ScaleX(StringToDouble(typeValue)); } },
                { DOM_SCALE_Y, [](const std::string& typeValue,
                               DOMNode& node) { node.transformComponent_->ScaleY(StringToDouble(typeValue)); } },
                { DOM_TRANSLATE,
                    [](const std::string& typeValue, DOMNode& node) {
                        std::vector<std::string> offsets;
                        StringUtils::StringSpliter(typeValue, ' ', offsets);
                        if (offsets.size() == TRANSFORM_DUAL) {
                            node.transformComponent_->Translate(
                                node.ParseDimension(offsets[0]), node.ParseDimension(offsets[1]));
                        } else if (offsets.size() == TRANSFORM_SINGLE) {
                            node.transformComponent_->TranslateX(node.ParseDimension(offsets[0]));
                        }
                    } },
                { DOM_TRANSLATE_X,
                    [](const std::string& typeValue, DOMNode& node) {
                        node.transformComponent_->TranslateX(node.ParseDimension(typeValue));
                    } },
                { DOM_TRANSLATE_Y,
                    [](const std::string& typeValue, DOMNode& node) {
                        node.transformComponent_->TranslateY(node.ParseDimension(typeValue));
                    } },
            };

            auto operatorIter = transformOperators.find(typeKey);
            if (operatorIter != transformOperators.end()) {
                operatorIter->second(typeValue, node);
            }
        }
    }
}

// Convert transform style to json format, such as rotate(50deg) to {"ratate":"50deg"}
std::string DOMNode::GetTransformJsonValue(const std::string& value)
{
    auto rightIndex = value.find('(');
    auto leftIndex = value.find(')');
    std::string jsonValue = value;

    if (rightIndex != std::string::npos && leftIndex != std::string::npos && (leftIndex - 1 - rightIndex > 0)) {
        std::string transformType = value.substr(0, rightIndex);
        std::string transformValue = value.substr(rightIndex + 1, leftIndex - 1 - rightIndex);
        jsonValue = "{\"" + transformType + "\":\"" + transformValue + "\"}";
    }

    return jsonValue;
}

void DOMNode::AddKeyframe(
    double time, double typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes)
{
    auto keyframe = AceType::MakeRefPtr<Keyframe<float>>(time, typeValue);
    transformKeyframes->AddKeyframe(keyframe);
}

void DOMNode::AddKeyframe(
    double time, const std::string& typeValue, RefPtr<KeyframeAnimation<float>>& transformKeyframes)
{
    DOMNode::AddKeyframe(time, StringToDouble(typeValue), transformKeyframes);
}

void DOMNode::AddKeyframeOffset(const std::string& keyValue, double time, const std::string& typeValue,
    RefPtr<KeyframeAnimation<DimensionOffset>>& transformKeyframes)
{
    DimensionOffset dimensionOffset;
    if (std::strcmp(keyValue.c_str(), DOM_TRANSLATE) == 0) {
        if (typeValue.find(' ', 0) != std::string::npos) {
            std::vector<std::string> offsetValues;
            StringUtils::StringSpliter(typeValue, ' ', offsetValues);
            if (offsetValues.size() == OFFSET_VALUE_NUMBER) {
                auto translateXDimension = ParseDimension(offsetValues[0]);
                auto translateYDimension = ParseDimension(offsetValues[1]);
                dimensionOffset = DimensionOffset(translateXDimension, translateYDimension);
            }
        } else {
            if (typeValue.find('%') != std::string::npos) {
                dimensionOffset =
                    DimensionOffset(ParseDimension(typeValue), Dimension(0.0, DimensionUnit::PERCENT));
            } else {
                dimensionOffset = DimensionOffset(ParseDimension(typeValue), Dimension(0.0));
            }
        }
    }
    if (std::strcmp(keyValue.c_str(), DOM_TRANSLATE_X) == 0) {
        if (typeValue.find('%') != std::string::npos) {
            dimensionOffset = DimensionOffset(ParseDimension(typeValue), Dimension(0.0, DimensionUnit::PERCENT));
        } else {
            dimensionOffset = DimensionOffset(ParseDimension(typeValue), Dimension(0.0));
        }
    }
    if (std::strcmp(keyValue.c_str(), DOM_TRANSLATE_Y) == 0) {
        if (typeValue.find('%') != std::string::npos) {
            dimensionOffset = DimensionOffset(Dimension(0.0, DimensionUnit::PERCENT), ParseDimension(typeValue));
        } else {
            dimensionOffset = DimensionOffset(Dimension(0.0), ParseDimension(typeValue));
        }
    }
    auto keyframe = AceType::MakeRefPtr<Keyframe<DimensionOffset>>(time, dimensionOffset);
    transformKeyframes->AddKeyframe(keyframe);
}

void DOMNode::SetSharedTransitionStyle(
    const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes)
{
    if (!ParseAnimationStyle(animationKeyframes)) {
        return;
    }
    sharedTransitionOption_ = TweenOption();
    TweenOptionSetKeyframes(sharedTransitionOption_);
}

bool DOMNode::ParseAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes)
{
    if (animationKeyframes.empty()) {
        return false;
    }

    for (auto& type : PROPERTY_ANIMATIONABLE_FLOAT_TYPES) {
        propertyFloatAnimations[type] = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    }

    bgPositionAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<BackgroundImagePosition>>();
    colorAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    colorAnimation_->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
    opacityAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    widthAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    heightAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    translateAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<DimensionOffset>>();
    translateXAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<DimensionOffset>>();
    translateYAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<DimensionOffset>>();
    scaleAnimationX_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    scaleAnimationY_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    scaleXAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    scaleYAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    rotateZAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    rotateXAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    rotateYAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    sameScale_ = true;

    for (const auto& animationNameKeyframe : animationKeyframes) {
        auto keyframeTime = animationNameKeyframe.find(DOM_ANIMATION_NAME_TIME);
        // if keyframeTime not exist in animationNameKeyframe, animationNameKeyframe have no meaning of existence.
        if (keyframeTime == animationNameKeyframe.end()) {
            LOGE(" DOMNode::SetAnimationStyle keyframeTime not exist");
            continue;
        }

        double time = StringToDouble(keyframeTime->second) / PERCENTAGE;
        for (const auto& [keyStyle, value] : animationNameKeyframe) {
            // key style = DOM_ANIMATION_NAME_TIME is time,
            // just need to pass the time into the function KeyframesAddKeyFrame
            if (keyStyle == DOM_ANIMATION_NAME_TIME) {
                continue;
            }
            KeyframesAddKeyFrame(keyStyle, value, time);
        }
    }
    return true;
}

void DOMNode::SetAnimationStyle(const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes)
{
    if (!ParseAnimationStyle(animationKeyframes)) {
        return;
    }
    if (isTransition_) {
        if (isEnter_) {
            TweenOptionSetKeyframes(transitionEnterOption_);
        } else {
            TweenOptionSetKeyframes(transitionExitOption_);
        }
    } else {
        tweenOption_ = TweenOption();
        TweenOptionSetKeyframes(tweenOption_);
        animationStyleUpdated_ = true;
    }
}

void DOMNode::SetTweenComponent(const RefPtr<TweenComponent>& tweenComponent)
{
    tweenComponent_ = tweenComponent;
}

RefPtr<TweenComponent> DOMNode::GetTweenComponent() const
{
    return tweenComponent_;
}

void DOMNode::KeyframesAddKeyFrame(const std::string& keyStyle, const std::string& value, double time)
{
    static const std::unordered_map<std::string, void(*)(const std::string&, const double&, DOMNode&)>
        keyFrameAddMap = {
            { DOM_BACKGROUND_COLOR,
                [](const std::string& value, const double& time, DOMNode& node) {
                    auto keyframe = AceType::MakeRefPtr<Keyframe<Color>>(time, node.ParseColor(value));
                    node.colorAnimation_->AddKeyframe(keyframe);
                } },
            { DOM_BACKGROUND_IMAGE_POSITION,
                [](const std::string& value, const double& time, DOMNode& node) {
                  BackgroundImagePosition backgroundImagePosition;
                  if (!ParseBackgroundImagePosition(value, backgroundImagePosition)) {
                      LOGW("parse frame failed.");
                      return;
                  }
                  auto keyframe = AceType::MakeRefPtr<Keyframe<BackgroundImagePosition>>(time, backgroundImagePosition);
                  node.bgPositionAnimation_->AddKeyframe(keyframe);
                } },
            { DOM_HEIGHT, [](const std::string& value, const double& time,
                          DOMNode& node) { node.AddKeyframe(time, value, node.heightAnimation_); } },
            { DOM_OPACITY, [](const std::string& value, const double& time,
                           DOMNode& node) { node.AddKeyframe(time, value, node.opacityAnimation_); } },
            // margin
            { DOM_MARGIN_LEFT,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_LEFT]);
                } },
            { DOM_MARGIN_RIGHT,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT]);
                } },
            { DOM_MARGIN_TOP,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_TOP]);
                } },
            { DOM_MARGIN_BOTTOM,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_BOTTOM]);
                } },
            { DOM_MARGIN_START,
                [](const std::string& value, const double& time, DOMNode& node) {
                    if (node.IsRightToLeft()) {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT]);
                    } else {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_LEFT]);
                    }
                } },
            { DOM_MARGIN_END,
                [](const std::string& value, const double& time, DOMNode& node) {
                    if (node.IsRightToLeft()) {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_LEFT]);
                    } else {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT]);
                    }
                } },
            { DOM_MARGIN,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_LEFT]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_TOP]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_MARGIN_BOTTOM]);
                } },
            // padding
            { DOM_PADDING_LEFT,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_LEFT]);
                } },
            { DOM_PADDING_RIGHT,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_RIGHT]);
                } },
            { DOM_PADDING_TOP,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_TOP]);
                } },
            { DOM_PADDING_BOTTOM,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_BOTTOM]);
                } },
            { DOM_PADDING_START,
                [](const std::string& value, const double& time, DOMNode& node) {
                    if (node.IsRightToLeft()) {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_RIGHT]);
                    } else {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_LEFT]);
                    }
                } },
            { DOM_PADDING_END,
                [](const std::string& value, const double& time, DOMNode& node) {
                    if (node.IsRightToLeft()) {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_LEFT]);
                    } else {
                        node.AddKeyframe(
                            time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_RIGHT]);
                    }
                } },
            { DOM_PADDING,
                [](const std::string& value, const double& time, DOMNode& node) {
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_LEFT]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_RIGHT]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_TOP]);
                    node.AddKeyframe(
                        time, value, node.propertyFloatAnimations[PropertyAnimatableType::PROPERTY_PADDING_BOTTOM]);
                } },
            { DOM_TRANSFORM,
                [](const std::string& value, const double& time, DOMNode& node) {
                  std::unique_ptr<JsonValue> transformJson = JsonUtil::ParseJsonString(value);
                  for (int32_t index = 0; index < transformJson->GetArraySize(); ++index) {
                      std::string typeKey = node.GetTransformType(transformJson->GetArrayItem(index));
                      std::string typeValue = node.GetTransformTypeValue(transformJson->GetArrayItem(index));
                      LOGD("DOMNode::SetAnimationStyle DOM_TRANSFORM typeKey:  %{private}s  typeValue:  %{private}s",
                           typeKey.c_str(), typeValue.c_str());
                      if ((!typeKey.empty()) && (!typeValue.empty())) {
                          node.TransformAnimationAddKeyframe(typeKey, typeValue, time);
                      }
                  }
                } },
            { DOM_WIDTH, [](const std::string& value, const double& time,
                         DOMNode& node) { node.AddKeyframe(time, value, node.widthAnimation_); } },
        };

    auto pos = keyFrameAddMap.find(keyStyle);
    if (pos != keyFrameAddMap.end()) {
        pos->second(value, time, *this);
    }

}

void DOMNode::TransformAnimationAddKeyframe(const std::string& typeKey, const std::string& typeValue, double time)
{
    static const LinearMapNode<void (*)(const std::string&, const std::string&, const double&, DOMNode&)>
        translateAddMap[] = {
            { DOM_TRANSLATE,
                [](const std::string& typeKey, const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframeOffset(typeKey, time, typeValue, node.translateAnimation_);
                } },
            { DOM_TRANSLATE_X,
                [](const std::string& typeKey, const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframeOffset(typeKey, time, typeValue, node.translateXAnimation_);
                } },
            { DOM_TRANSLATE_Y,
                [](const std::string& typeKey, const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframeOffset(typeKey, time, typeValue, node.translateYAnimation_);
                } },
        };
    auto translateAddKeyframeIter = BinarySearchFindIndex(translateAddMap, ArraySize(translateAddMap), typeKey.c_str());
    if (translateAddKeyframeIter != -1) {
        translateAddMap[translateAddKeyframeIter].value(typeKey, typeValue, time, *this);
    }
    static const LinearMapNode<void (*)(const std::string&, const double&, DOMNode&)>
        transformAniAddKeyFrameMap[] = {
            { DOM_ROTATE,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframe(time, StringUtils::StringToDegree(typeValue), node.rotateZAnimation_);
                } },
            { DOM_ROTATE_X,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframe(time, StringUtils::StringToDegree(typeValue), node.rotateXAnimation_);
                } },
            { DOM_ROTATE_Y,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    node.AddKeyframe(time, StringUtils::StringToDegree(typeValue), node.rotateYAnimation_);
                } },
            { SCALE,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    if (typeValue.find(' ') != std::string::npos) {
                        std::vector<std::string> values;
                        StringUtils::StringSpliter(typeValue, ' ', values);
                        if (values.size() == OFFSET_VALUE_NUMBER) {
                            double scaleValueX = StringToDouble(values[0]);
                            double scaleValueY = StringToDouble(values[1]);
                            node.AddKeyframe(time, scaleValueX, node.scaleAnimationX_);
                            node.AddKeyframe(time, scaleValueY, node.scaleAnimationY_);
                            node.maxScaleXY_ = std::max(scaleValueX, scaleValueY);
                            if (!NearEqual(scaleValueY, scaleValueX)) {
                                node.sameScale_ = false;
                            }
                        }
                    } else {
                        node.AddKeyframe(time, typeValue, node.scaleAnimationX_);
                        node.AddKeyframe(time, typeValue, node.scaleAnimationY_);
                        node.maxScaleXY_ =  StringToDouble(typeValue);
                    }
                } },
            { DOM_SCALE_X,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    node.sameScale_ = false;
                    node.AddKeyframe(time, typeValue, node.scaleXAnimation_);
                    double scaleValueX = StringToDouble(typeValue);
                    node.maxScaleXY_ = std::max(scaleValueX, node.maxScaleXY_);
                } },
            { DOM_SCALE_Y,
                [](const std::string& typeValue, const double& time, DOMNode& node) {
                    node.sameScale_ = false;
                    node.AddKeyframe(time, typeValue, node.scaleYAnimation_);
                    double scaleValueY = StringToDouble(typeValue);
                    node.maxScaleXY_ = std::max(scaleValueY, node.maxScaleXY_);
                } },
        };

    auto traFloatAniAddKeyframeIter = BinarySearchFindIndex(
        transformAniAddKeyFrameMap, ArraySize(transformAniAddKeyFrameMap), typeKey.c_str());
    if (traFloatAniAddKeyframeIter != -1) {
        transformAniAddKeyFrameMap[traFloatAniAddKeyframeIter].value(typeValue, time, *this);
    }
}

void DOMNode::TweenOptionSetKeyframes(TweenOption& tweenOption)
{
    if (!bgPositionAnimation_->GetKeyframes().empty()) {
        tweenOption.SetBackgroundPositionAnimation(bgPositionAnimation_);
    }
    if (!colorAnimation_->GetKeyframes().empty()) {
        tweenOption.SetColorAnimation(colorAnimation_);
    }
    if (!opacityAnimation_->GetKeyframes().empty()) {
        tweenOption.SetOpacityAnimation(opacityAnimation_);
    }
    if (!widthAnimation_->GetKeyframes().empty()) {
        tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_WIDTH, widthAnimation_);
    }
    if (!heightAnimation_->GetKeyframes().empty()) {
        tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_HEIGHT, heightAnimation_);
    }

    for (auto& [type, animation] : propertyFloatAnimations) {
        if (!animation->GetKeyframes().empty()) {
            tweenOption.SetPropertyAnimationFloat(type, animation);
        }
    }

    if (!translateAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTranslateAnimations(AnimationType::TRANSLATE, translateAnimation_);
    }
    if (!translateXAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTranslateAnimations(AnimationType::TRANSLATE_X, translateXAnimation_);
    }
    if (!translateYAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTranslateAnimations(AnimationType::TRANSLATE_Y, translateYAnimation_);
    }
    if (sameScale_ && (!scaleAnimationX_->GetKeyframes().empty())) {
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scaleAnimationX_);
        tweenOption.SetMaxScaleXY(maxScaleXY_);
    } else {
        if (!scaleAnimationX_->GetKeyframes().empty()) {
            tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_X, scaleAnimationX_);
        }
        if (!scaleAnimationY_->GetKeyframes().empty()) {
            tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_Y, scaleAnimationY_);
        }
        tweenOption.SetMaxScaleXY(maxScaleXY_);
    }
    if (!scaleXAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_X, scaleXAnimation_);
        tweenOption.SetMaxScaleXY(maxScaleXY_);
    }
    if (!scaleYAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_Y, scaleYAnimation_);
        tweenOption.SetMaxScaleXY(maxScaleXY_);
    }
    if (!rotateZAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTransformFloatAnimation(AnimationType::ROTATE_Z, rotateZAnimation_);
    }
    if (!rotateXAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTransformFloatAnimation(AnimationType::ROTATE_X, rotateXAnimation_);
    }
    if (!rotateYAnimation_->GetKeyframes().empty()) {
        tweenOption.SetTransformFloatAnimation(AnimationType::ROTATE_Y, rotateYAnimation_);
    }
}

void DOMNode::CompositeComponents()
{
    std::vector<RefPtr<SingleChild>> components;
    // Only fixed position has position component
    if (positionComponent_ && position_ == PositionType::FIXED) {
        components.emplace_back(positionComponent_);
    }
    if (flexItemComponent_) {
        // Update flex item after PrepareSpecializedComponent to make sure sub class has finished prepare.
        UpdateFlexItemComponent();
        components.emplace_back(flexItemComponent_);
    }
    if (focusableEventComponent_) {
        components.emplace_back(focusableEventComponent_);
    }
    if (touchEventComponent_) {
        touchEventComponent_->SetIsVisible(visible_ == VisibleType::VISIBLE);
        components.emplace_back(touchEventComponent_);
    }
    if (gestureEventComponent_) {
        gestureEventComponent_->SetIsVisible(visible_ == VisibleType::VISIBLE);
        components.emplace_back(gestureEventComponent_);
    }
#ifndef WEARABLE_PRODUCT
    if (multimodalComponent_) {
        components.emplace_back(multimodalComponent_);
    }
#endif
    if (mouseEventComponent_) {
        components.emplace_back(mouseEventComponent_);
    }

    if (displayComponent_) {
        displayComponent_->DisableLayer(IsLeafNode());
        components.emplace_back(displayComponent_);
        if (focusableEventComponent_) {
            bool show = (display_ != DisplayType::NONE);
            focusableEventComponent_->SetShow(show);
        }
    }

    if (transformComponent_) {
        components.emplace_back(transformComponent_);
    }
    if (tweenComponent_) {
        tweenComponent_->SetLeafNode(IsLeafNode());
        components.emplace_back(tweenComponent_);
    }
    if (boxComponent_) {
        components.emplace_back(boxComponent_);
    }
    if (scrollComponent_) {
        components.emplace_back(scrollComponent_);
    }
    if (sharedTransitionComponent_) {
        components.emplace_back(sharedTransitionComponent_);
    }
    // First, composite all common components.
    for (int32_t idx = static_cast<int32_t>(components.size()) - 1; idx - 1 >= 0; --idx) {
        components[idx - 1]->SetChild(DynamicCast<Component>(components[idx]));
    }
    // Then composite specialized components.
    auto compositeComponent = CompositeSpecializedComponent(components);
    // At last add to composite component.
    rootComponent_->SetChild(compositeComponent);
    // final set disabled status.
    rootComponent_->SetDisabledStatus(nodeDisabled_);
}

void DOMNode::UpdateFlexItemComponent()
{
    flexItemComponent_->SetFlexGrow(flexGrow_);
    flexItemComponent_->SetFlexShrink(flexShrink_);
    flexItemComponent_->SetFlexBasis(flexBasis_);
    flexItemComponent_->SetFlexWeight(flexWeight_);
    flexItemComponent_->SetDisplayIndex(displayIndex_);
    const LinearMapNode<FlexAlign> ALIGN_SELF_TABLE[] = {
        { "center", FlexAlign::CENTER },
        { "flex-end", FlexAlign::FLEX_END },
        { "flex-start", FlexAlign::FLEX_START },
        { "stretch", FlexAlign::STRETCH },
    };
    int64_t index = BinarySearchFindIndex(ALIGN_SELF_TABLE, ArraySize(ALIGN_SELF_TABLE), alignSelf_.c_str());
    if (index != -1) {
        flexItemComponent_->SetAlignSelf(ALIGN_SELF_TABLE[index].value);
    } else {
        flexItemComponent_->SetAlignSelf(FlexAlign::AUTO);
    }
    auto parentNode = parentNode_.Upgrade();
    if ((parentNode) &&
        (parentNode->GetTag() == DOM_NODE_TAG_DIV || parentNode->GetTag() == DOM_NODE_TAG_GRID_COLUMN)) {
        auto parent = AceType::DynamicCast<DOMDiv>(parentNode);
        // Stretch flag means that if the child's main size is determined, it can not be stretched.
        if (((parent->GetFlexDirection() == FlexDirection::ROW && GreatOrEqual(height_.Value(), 0.0)) ||
            (parent->GetFlexDirection() == FlexDirection::COLUMN && GreatOrEqual(width_.Value(), 0.0)))) {
            flexItemComponent_->SetStretchFlag(false);
        } else {
            flexItemComponent_->SetStretchFlag(true);
        }
    }
    // Make sure input layout constraint is valid
    flexItemComponent_->SetMaxHeight(maxHeight_);
    flexItemComponent_->SetMaxWidth(maxWidth_);
    flexItemComponent_->SetMinHeight(minHeight_);
    flexItemComponent_->SetMinWidth(minWidth_);
    // If set aspect Ratio, it cannot be stretch
    if (GreatNotEqual(aspectRatio_, 0.0)) {
        flexItemComponent_->SetStretchFlag(false);
    }
    // If set display, this flexItem is ignored.
    flexItemComponent_->SetIsHidden(display_ == DisplayType::NONE);
}

void DOMNode::UpdateUiComponents()
{
    UpdateBoxComponent();
    UpdateDisplayComponent();
    UpdateTweenComponent();
}

void DOMNode::UpdateBoxSize(const Dimension& width, const Dimension& height)
{
    boxComponent_->SetHeight(height.Value(), height.Unit());
    boxComponent_->SetWidth(width.Value(), width.Unit());
}

void DOMNode::UpdateBoxPadding(const Edge& padding)
{
    boxComponent_->SetPadding(padding);
}

void DOMNode::UpdateBoxBorder(const Border& border)
{
    backDecoration_->SetBorder(border);
}

void DOMNode::UpdateBoxComponent()
{
    if (hasBoxStyle_) {
        UpdateBoxSize(width_, height_);
        UpdateBoxPadding(Edge(paddingLeft_, paddingTop_, paddingRight_, paddingBottom_));
        boxComponent_->SetMargin(Edge(marginLeft_, marginTop_, marginRight_, marginBottom_));
        boxComponent_->SetLayoutInBoxFlag(layoutInBox_);
    }
    if (flexItemComponent_) {
        boxComponent_->SetDeliverMinToChild(false);
        boxComponent_->SetAspectRatio(aspectRatio_);
        boxComponent_->SetMinWidth(minWidth_);
        boxComponent_->SetMinHeight(minHeight_);
        boxComponent_->SetMaxWidth(maxWidth_);
        boxComponent_->SetMaxHeight(maxHeight_);
    }

    if (hasDecorationStyle_) {
        border_.SetLeftEdge(borderLeftEdge_);
        border_.SetRightEdge(borderRightEdge_);
        border_.SetTopEdge(borderTopEdge_);
        border_.SetBottomEdge(borderBottomEdge_);
        // Do not support drawing a different border when there are rounded corners
        if (border_.HasRadius() && !border_.IsAllEqual()) {
            border_.SetBorderEdge(BorderEdge(Color::BLACK, Dimension(), BorderStyle::SOLID));
        }
        UpdateBoxBorder(border_);
        if (gradient_.IsValid()) {
            backDecoration_->SetGradient(gradient_);
        }
        if (hasShadowStyle_) {
            backDecoration_->ClearAllShadow();
            backDecoration_->AddShadow(shadow_);
        }
        boxComponent_->SetBackDecoration(backDecoration_);
    }

    if (hasFrontDecorationStyle_) {
        boxComponent_->SetFrontDecoration(frontDecoration_);
    }
    boxComponent_->SetOverflow(overflow_);
}

void DOMNode::PrepareScrollComponent()
{
    // div and stack is specially handled.
    if (GetTag() == DOM_NODE_TAG_DIV || GetTag() == DOM_NODE_TAG_STACK) {
        return;
    }
    if (!hasOverflowStyle_ || overflow_ != Overflow::SCROLL) {
        return;
    }
    if (boxComponent_->GetWidthDimension().IsValid() && boxComponent_->GetHeightDimension().IsValid()) {
        if (!scrollComponent_) {
            scrollComponent_ = AceType::MakeRefPtr<ScrollComponent>(nullptr);
        }
        scrollComponent_->InitScrollBar(GetTheme<ScrollBarTheme>(), scrollBarColor_, scrollBarWidth_, edgeEffect_);
    }
}

void DOMNode::UpdateDisplayComponent()
{
    if (hasDisplayStyle_) {
        if (!displayComponent_) {
            displayComponent_ = AceType::MakeRefPtr<DisplayComponent>(rootComponent_->GetChild());
        }
        displayComponent_->SetOpacity(opacity_);
        SetDisplayStyle();
        displayComponent_->SetVisible(visible_);
        bool show = (display_ != DisplayType::NONE);
        if (!focusableEventComponent_ && !show) {
            focusableEventComponent_ = AceType::MakeRefPtr<FocusableComponent>();
            focusableEventComponent_->SetFocusable(true);
        }
        if (focusableEventComponent_) {
            focusableEventComponent_->SetShow(show);
        }
        if (hasShadowStyle_) {
            displayComponent_->SetShadow(shadow_);
        }
    }
}

void DOMNode::UpdateTweenComponent()
{
    if (transformComponent_ && hasShadowStyle_) {
        transformComponent_->SetShadow(shadow_);
    }
    // Only check animation style here.
    if (tweenOption_.IsValid() && animationStyleUpdated_) {
        if (!tweenComponent_) {
            tweenComponent_ = AceType::MakeRefPtr<TweenComponent>(COMPONENT_PREFIX + std::to_string(nodeId_), tag_);
        }
        tweenComponent_->SetTweenOption(tweenOption_);
        tweenComponent_->SetTweenOperation(TweenOperation::PLAY);
        if (hasShadowStyle_) {
            tweenComponent_->SetShadow(shadow_);
        }
        animationStyleUpdated_ = false;
    }
    if (!shareId_.empty()) {
        if (!sharedTransitionComponent_) {
            sharedTransitionComponent_ = AceType::MakeRefPtr<SharedTransitionComponent>(
                "FrontendShared" + std::to_string(nodeId_), tag_, shareId_);
            sharedTransitionComponent_->SetOption(sharedTransitionOption_);
            sharedTransitionComponent_->SetEffect(sharedEffect_);
        } else {
            sharedTransitionComponent_->SetShareId(shareId_);
        }
    }
}

bool DOMNode::IsTabbarSubNode() const
{
    if (isRootNode_) {
        return GetTag() == DOM_NODE_TAG_TAB_BAR;
    }
    RefPtr<DOMNode> parent = parentNode_.Upgrade();
    if (!parent) {
        return false;
    }

    if (parent->GetTag() == DOM_NODE_TAG_TAB_BAR) {
        return true;
    }

    while (!parent->IsRootNode()) {
        if (parent->GetTag() == DOM_NODE_TAG_TAB_BAR) {
            return true;
        }
        parent = parent->GetParentNode();
        if (!parent) {
            return false;
        }
    }
    return false;
}

void DOMNode::PrepareTouchEvent(EventMarker& eventMarker, uint32_t type)
{
    bool isTababrSubNode = IsTabbarSubNode();
    if (isTababrSubNode) {
        return;
    }

    auto weak = AceType::WeakClaim(this);
    if (eventMarker.IsEmpty()) {
        eventMarker = BackEndEventManager<void(const TouchEventInfo&)>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void(const TouchEventInfo&)>::GetInstance().BindBackendEvent(
            eventMarker, [](const TouchEventInfo&) {});
    }
    eventMarker.SetPreFunction([weak, type]() {
        auto domNode = weak.Upgrade();
        if (!domNode) {
            LOGE("get dom node failed!");
            return;
        }
        domNode->OnActive(type != EventType::TOUCH_UP && type != EventType::TOUCH_CANCEL);
    });
}

void DOMNode::PrepareFocusableEventId()
{
    auto weak = AceType::WeakClaim(this);

    if (onFocusId_.IsEmpty()) {
        onFocusId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(onFocusId_, []() {});
    }

    onFocusId_.SetPreFunction([weak]() {
        auto domNode = weak.Upgrade();
        if (!domNode) {
            LOGE("get dom node failed!");
            return;
        }
        domNode->OnFocus(true);
    });

    if (onBlurId_.IsEmpty()) {
        onBlurId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void()>::GetInstance().BindBackendEvent(onBlurId_, []() {});
    }

    onBlurId_.SetPreFunction([weak]() {
        auto domNode = weak.Upgrade();
        if (!domNode) {
            LOGE("get dom node failed!");
            return;
        }
        domNode->OnFocus(false);
    });
}

void DOMNode::UpdateTouchEventComponent()
{
    for (uint32_t eventAction = 0; eventAction < EventAction::SIZE; eventAction++) {
        for (uint32_t eventStage = 0; eventStage < EventStage::SIZE; eventStage++) {
            for (uint32_t touchEventType = 0; touchEventType < EventType::SIZE; touchEventType++) {
                EventMarker& eventMarker = onTouchIds_[eventAction][eventStage][touchEventType];
                if (!eventMarker.IsEmpty() || HasActivePseudo()) {
                    if (!touchEventComponent_) {
                        touchEventComponent_ = AceType::MakeRefPtr<TouchListenerComponent>();
                    }
                    if (HasActivePseudo() && touchEventType != EventType::TOUCH_MOVE &&
                        eventAction == EventAction::ON && eventStage == EventStage::BUBBLE) {
                        PrepareTouchEvent(eventMarker, touchEventType);
                    }
                    touchEventComponent_->SetEvent(eventMarker, eventAction, eventStage, touchEventType);
                }
            }
        }
    }
    if (!onSwipeId_.IsEmpty()) {
        if (!touchEventComponent_) {
            touchEventComponent_ = AceType::MakeRefPtr<TouchListenerComponent>();
        }
        touchEventComponent_->SetOnSwipeId(onSwipeId_);
    }
    if (!touchable_) {
        if (!touchEventComponent_) {
            touchEventComponent_ = AceType::MakeRefPtr<TouchListenerComponent>();
        }
        touchEventComponent_->SetTouchable(touchable_);
    }
}

void DOMNode::UpdateMouseEventComponent()
{
    if (!onMouseId_.IsEmpty()) {
        if (!mouseEventComponent_) {
            mouseEventComponent_ = AceType::MakeRefPtr<MouseListenerComponent>();
        }
        mouseEventComponent_->SetOnMouseId(onMouseId_);
    }
}

void DOMNode::UpdateGestureEventComponent()
{
    if (!onClickId_.IsEmpty() || !onLongPressId_.IsEmpty() || hasIdAttr_) {
        if (!gestureEventComponent_) {
            gestureEventComponent_ = AceType::MakeRefPtr<GestureListenerComponent>();
        }
        gestureEventComponent_->SetOnClickId(onClickId_);
        gestureEventComponent_->SetOnLongPressId(onLongPressId_);
    }
}

void DOMNode::UpdateFocusableEventComponents()
{
    if (UNFOCUSABLED_NODE.find(tag_) != UNFOCUSABLED_NODE.end()) {
        return;
    }

    if (!focusable_.second && onClickId_.IsEmpty() && onBlurId_.IsEmpty() && onFocusId_.IsEmpty() &&
        onKeyId_.IsEmpty() && !HasFocusPseudo()) {
        return;
    }

    if (!focusableEventComponent_) {
        focusableEventComponent_ = AceType::MakeRefPtr<FocusableComponent>();
    }
    if (focusable_.second) {
        focusableEventComponent_->SetFocusable(focusable_.first);
    } else {
        focusableEventComponent_->SetFocusable(true);
    }

    focusableEventComponent_->SetOnClickId(onClickId_);

    PrepareFocusableEventId();

    focusableEventComponent_->SetOnBlurId(onBlurId_);
    focusableEventComponent_->SetOnFocusId(onFocusId_);
    focusableEventComponent_->SetOnKeyId(onKeyId_);
    if (g_focusableNode.empty()) {
        g_focusableNode = std::unordered_set<std::string>({
            DOM_NODE_TAG_BUTTON,
            DOM_NODE_TAG_DIV,
            DOM_NODE_TAG_LIST,
            DOM_NODE_TAG_LIST_ITEM,
            DOM_NODE_TAG_REFRESH,
            DOM_NODE_TAG_INPUT,
            DOM_NODE_TAG_OPTION,
            DOM_NODE_TAG_PROGRESS,
            DOM_NODE_TAG_POPUP,
            DOM_NODE_TAG_RATING,
            DOM_NODE_TAG_SELECT,
            DOM_NODE_TAG_SLIDER,
            DOM_NODE_TAG_STACK,
            DOM_NODE_TAG_STEPPER,
            DOM_NODE_TAG_STEPPER_ITEM,
            DOM_NODE_TAG_SWIPER,
            DOM_NODE_TAG_SWITCH,
            DOM_NODE_TAG_TABS,
            DOM_NODE_TAG_TAB_BAR,
            DOM_NODE_TAG_TAB_CONTENT,
            DOM_NODE_TAG_TEXTAREA,
            DOM_NODE_TAG_TOGGLE,
            DOM_NODE_TAG_SEARCH,
            DOM_NODE_TAG_VIDEO,
            DOM_NODE_TAG_CALENDAR,
            DOM_NODE_TAG_PICKER_DIALOG,
            DOM_NODE_TAG_PIECE,
        });
    }
    if (g_focusableNode.find(tag_) != g_focusableNode.end()) {
        focusableEventComponent_->SetFocusNode(false);
    } else {
        focusableEventComponent_->SetFocusNode(true);
    }
}

void DOMNode::UpdatePositionProps()
{
    if (!hasPositionStyle_ || position_ == PositionType::FIXED) {
        return;
    }
    hasPositionStyle_ = false;
    auto tweenComponent = AceType::DynamicCast<TweenComponent>(rootComponent_->GetChild());
    if (tweenComponent) {
        UpdateTweenPosition(tweenComponent);
    } else {
        // Set position props to first RenderComponent of node
        auto compositeComponent = AceType::DynamicCast<RenderComponent>(rootComponent_->GetChild());
        if (!compositeComponent) {
            return;
        }
        compositeComponent->SetHasLeft(hasLeft_);
        compositeComponent->SetHasTop(hasTop_);
        compositeComponent->SetHasBottom(hasBottom_);
        compositeComponent->SetHasRight(hasRight_);
        if (hasLeft_) {
            compositeComponent->SetLeft(left_);
            // reset value
            hasLeft_ = false;
        }
        if (hasRight_) {
            compositeComponent->SetRight(right_);
            hasRight_ = false;
        }
        if (hasTop_) {
            compositeComponent->SetTop(top_);
            hasTop_ = false;
        }
        if (hasBottom_) {
            compositeComponent->SetBottom(bottom_);
            hasBottom_ = false;
        }
        compositeComponent->SetPositionType(position_);
    }
}

void DOMNode::UpdateTweenPosition(const RefPtr<TweenComponent> tweenComponent)
{
    if (!tweenComponent) {
        return;
    }
    tweenComponent->SetHasLeft(hasLeft_);
    tweenComponent->SetHasTop(hasTop_);
    tweenComponent->SetHasBottom(hasBottom_);
    tweenComponent->SetHasRight(hasRight_);
    if (hasLeft_) {
        tweenComponent->SetLeft(left_);
        // reset value
        hasLeft_ = false;
    }
    if (hasRight_) {
        tweenComponent->SetRight(right_);
        hasRight_ = false;
    }
    if (hasTop_) {
        tweenComponent->SetTop(top_);
        hasTop_ = false;
    }
    if (hasBottom_) {
        tweenComponent->SetBottom(bottom_);
        hasBottom_ = false;
    }
    tweenComponent->SetPositionType(position_);
}

void DOMNode::UpdatePositionComponent()
{
    if (!hasPositionStyle_ || position_ != PositionType::FIXED) {
        return;
    }
    if (!positionComponent_) {
        positionComponent_ = AceType::MakeRefPtr<PositionedComponent>();
    }
    positionComponent_->SetTop(top_);
    positionComponent_->SetRight(right_);
    positionComponent_->SetBottom(bottom_);
    positionComponent_->SetLeft(left_);
    positionComponent_->SetHasLeft(hasLeft_);
    positionComponent_->SetHasRight(hasRight_);
    positionComponent_->SetHasBottom(hasBottom_);
    positionComponent_->SetHasTop(hasTop_);
}

RefPtr<Component> DOMNode::CompositeSpecializedComponent(const std::vector<RefPtr<SingleChild>>& components)
{
    const auto& specializedComponent = GetSpecializedComponent();
    if (specializedComponent) {
        specializedComponent->SetTouchable(touchable_);
    }
    if (components.empty()) {
        return specializedComponent;
    } else {
        const auto& parent = components.back();
        if (parent) {
            parent->SetChild(specializedComponent);
        }
        return AceType::DynamicCast<Component>(components.front());
    }
}
#ifndef WEARABLE_PRODUCT
void DOMNode::UpdateMultimodalComponent()
{
    if (GetClickId().IsEmpty()) {
        return;
    }
    if (multimodalProperties_.IsUnavailable() || multimodalProperties_.scene == SceneLabel::SWITCH) {
        return;
    }
    if (!multimodalComponent_) {
        multimodalComponent_ = AceType::MakeRefPtr<MultimodalComponent>(pageId_);
    }
    multimodalComponent_->SetMultimodalProperties(multimodalProperties_);
    multimodalComponent_->SetOnClickId(GetClickId());
}
#endif

RefPtr<ThemeConstants> DOMNode::GetThemeConstants() const
{
    auto themeManager = GetThemeManager();
    if (!themeManager) {
        return nullptr;
    }
    return themeManager->GetThemeConstants();
}

Color DOMNode::ParseColor(const std::string& value, uint32_t maskAlpha) const
{
    auto themeConstants = GetThemeConstants();
    auto&& noRefFunc = [&value, maskAlpha = maskAlpha]() { return Color::FromString(value, maskAlpha); };
    auto&& idRefFunc = [constants = themeConstants](uint32_t refId) { return constants->GetColor(refId); };
    return ParseThemeReference<Color>(value, noRefFunc, idRefFunc, Color::TRANSPARENT);
}

double DOMNode::ParseDouble(const std::string& value) const
{
    auto themeConstants = GetThemeConstants();
    auto&& noRefFunc = [&value]() { return StringUtils::StringToDouble(value); };
    auto&& idRefFunc = [constants = themeConstants](uint32_t refId) { return constants->GetDouble(refId); };
    return ParseThemeReference<double>(value, noRefFunc, idRefFunc, 0.0);
}

Dimension DOMNode::ParseDimension(const std::string& value) const
{
    auto themeConstants = GetThemeConstants();
    auto&& noRefFunc = [&value]() { return StringUtils::StringToDimension(value); };
    auto&& idRefFunc = [constants = themeConstants](uint32_t refId) { return constants->GetDimension(refId); };
    return ParseThemeReference<Dimension>(value, noRefFunc, idRefFunc, Dimension());
}

Dimension DOMNode::ParseLineHeight(const std::string& value) const
{
    const auto& parseResult = ThemeUtils::ParseThemeIdReference(value);
    if (!parseResult.parseSuccess) {
        return StringUtils::StringToDimension(value);
    }
    auto themeConstants = GetThemeConstants();
    auto&& noRefFunc = [&value]() { return StringUtils::StringToDouble(value); };
    auto&& idRefFunc = [constants = themeConstants](uint32_t refId) { return constants->GetDouble(refId); };
    auto lineHeightScale = ParseThemeReference<double>(value, noRefFunc, idRefFunc, 1.0);
    // If got 0.0 from ThemeConstants, use default 1.0
    lineHeightScale = NearZero(lineHeightScale) ? 1.0 : lineHeightScale;
    return Dimension(lineHeightScale, DimensionUnit::PERCENT);
}

std::vector<std::string> DOMNode::ParseFontFamilies(const std::string& value) const
{
    std::vector<std::string> fontFamilies;
    std::stringstream stream(value);
    std::string fontFamily;

    auto themeConstants = GetThemeConstants();
    auto&& idRefFunc = [constants = themeConstants](uint32_t refId) { return constants->GetString(refId); };

    while (getline(stream, fontFamily, ',')) {
        auto&& noRefFunc = [&fontFamily]() { return fontFamily; };
        fontFamilies.emplace_back(ParseThemeReference<std::string>(fontFamily, noRefFunc, idRefFunc, fontFamily));
    }
    return fontFamilies;
}

std::vector<Dimension> DOMNode::ParsePreferFontSizes(const std::string& value) const
{
    std::vector<Dimension> prefers;
    std::stringstream stream(value);
    std::string fontSize;
    while (getline(stream, fontSize, ',')) {
        prefers.emplace_back(ParseDimension(fontSize));
    }
    std::sort(prefers.begin(), prefers.end(),
        [](const Dimension& left, const Dimension& right) { return left.Value() > right.Value(); });
    return prefers;
}

void DOMNode::AdjustParamInLiteMode()
{
    useLiteStyle_ = true;
    // Change default value
    if (boxComponent_) {
        boxComponent_->SetUseLiteStyle(true);
        boxComponent_->SetAlignment(Alignment::TOP_CENTER);
    }
    flexShrink_ = 0.0;
    AdjustSpecialParamInLiteMode();
}

} // namespace OHOS::Ace::Framework

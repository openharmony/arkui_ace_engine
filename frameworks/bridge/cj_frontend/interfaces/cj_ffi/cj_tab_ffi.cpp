/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_tab_ffi.h"
#include "bridge/common/utils/utils.h"

#include "cj_lambda.h"
#include "cj_view_abstract_ffi.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_controller_modifier_api.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_transition_proxy_modifier_api.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t DEFAULT_CUSTOM_ANIMATION_TIMEOUT = 1000;
constexpr int32_t GRAY_SCALE_ARRAY_SIZE = 2;
constexpr int32_t EVEN_MOD = 2;
const std::vector<BarPosition> BAR_POSITIONS = { BarPosition::START, BarPosition::END };
const std::vector<TabBarMode> TAB_BAR_MODES = {
    TabBarMode::FIXED, TabBarMode::SCROLLABLE
    // not support TabBarMode::FIXED_START yet
};
const std::vector<TabAnimateMode> TAB_ANIMATE_MODES = { TabAnimateMode::CONTENT_FIRST, TabAnimateMode::ACTION_FIRST,
    TabAnimateMode::NO_ANIMATION };
const std::vector<TextOverflow> TEXT_OVER_FLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE,
    TextOverflow::MARQUEE };
} // namespace

namespace OHOS::Ace {
NG::TabsModelNG* GetTabsModel()
{
    static NG::TabsModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Tabs");
        if (module == nullptr) {
            LOGF_ABORT("Can't find tabs dynamic module");
        }
        model = reinterpret_cast<NG::TabsModelNG*>(module->GetModel());
    }
    return model;
}

NG::TabContentModelNG* GetTabContentModel()
{
    static NG::TabContentModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TabContent");
        if (module == nullptr) {
            LOGF_ABORT("Can't find tabcontent dynamic module");
        }
        model = reinterpret_cast<NG::TabContentModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {

int32_t g_tabControllerId = 0;

const ArkUIInnerTabsModifier* GetTabsInnerModifier()
{
    static const ArkUIInnerTabsModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tabs");
        CHECK_NULL_RETURN(loader, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIInnerTabsModifier*>(loader->GetCustomModifier());
    }
    return cachedModifier;
}

const NG::NodeModifier::ArkUITabsControllerModifier* GetTabsControllerModifier()
{
    static const NG::NodeModifier::ArkUITabsControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Tabs");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::NodeModifier::ArkUITabsControllerModifier*>(
            module->GetCustomModifier("tabsController"));
    }
    return cachedModifier;
}

const NG::NodeModifier::ArkUITabContentTransitionModifier* GetTransitionProxyModifier()
{
    static const NG::NodeModifier::ArkUITabContentTransitionModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Tabs");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::NodeModifier::ArkUITabContentTransitionModifier*>(
            module->GetCustomModifier("tabsTransitionProxy"));
    }
    return cachedModifier;
}
} // namespace

TabsController::TabsController() : FFIData()
{
    if (auto modifier = GetTabsInnerModifier()) {
        controller_ = modifier->getController(++g_tabControllerId);
    }
    if (auto* modifier = GetTabsControllerModifier()) {
        swiperController_ = modifier->createController();
    }
    LOGI("Native TabsController constructed: %{public}" PRId64, GetID());
}

TabsController::~TabsController()
{
    LOGI("Native TabsController Destroyed: %{public}" PRId64, GetID());
}

void TabsController::ChangeIndex(int32_t index)
{
    LOGI("Native TabsController %{public}" PRId64 "ChangeIndex: %{public}d", GetID(), index);
    if (swiperController_) {
        if (auto* modifier = GetTabsControllerModifier()) {
            modifier->changeIndex(swiperController_, index);
        }
    }
    if (controller_) {
        if (auto modifier = GetTabsInnerModifier()) {
            modifier->setIndexByController(controller_, index, false);
        }
    }
}

void TabsController::PreloadItems(std::set<int32_t> indexSet)
{
    if (swiperController_) {
        if (auto* modifier = GetTabsControllerModifier()) {
            std::vector<int32_t> indexVec(indexSet.begin(), indexSet.end());
            modifier->preloadItems(swiperController_, indexVec.data(), static_cast<int32_t>(indexVec.size()));
        }
    }
}

void TabsController::SetTabBarTranslate(NG::TranslateOptions options)
{
    if (swiperController_) {
        if (auto* modifier = GetTabsControllerModifier()) {
            modifier->setTabBarTranslate(swiperController_, options.x.Value(), options.y.Value(), options.z.Value(),
                static_cast<int32_t>(options.x.Unit()), static_cast<int32_t>(options.y.Unit()),
                static_cast<int32_t>(options.z.Unit()));
        }
    }
}

void TabsController::SetTabBarOpacity(double opacity)
{
    if (swiperController_) {
        if (auto* modifier = GetTabsControllerModifier()) {
            modifier->setTabBarOpacity(swiperController_, opacity);
        }
    }
}

int32_t CJTabContentTransitionProxy::getFromIndex()
{
    auto* modifier = GetTransitionProxyModifier();
    CHECK_NULL_RETURN(modifier, 0);
    return modifier->getFromIndex(proxy_);
}

int32_t CJTabContentTransitionProxy::getToIndex()
{
    auto* modifier = GetTransitionProxyModifier();
    CHECK_NULL_RETURN(modifier, 0);
    return modifier->getToIndex(proxy_);
}

void CJTabContentTransitionProxy::finishTransition()
{
    auto* modifier = GetTransitionProxyModifier();
    CHECK_NULL_VOID(modifier);
    modifier->finishTransition(proxy_);
}

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTabsCreate(int32_t barPosition, int64_t controllerId, int32_t index)
{
    if (!Utils::CheckParamsValid(barPosition, BAR_POSITIONS.size())) {
        LOGE("invalid value for bar position");
        return;
    }
    auto nativeTabsController = FFIData::GetData<TabsController>(controllerId);
    if (nativeTabsController == nullptr) {
        return;
    }
    RefPtr<AceType> tabController;
    RefPtr<SwiperController> swiperController;

    tabController = nativeTabsController->GetController();
    swiperController = AceType::DynamicCast<SwiperController>(nativeTabsController->GetSwiperController());
    if (auto modifier = GetTabsInnerModifier()) {
        modifier->setInitialIndex(tabController, index);
    }
#ifdef NG_BUILD
    auto* innerModifier = GetTabsInnerModifier();
    CHECK_NULL_VOID(innerModifier);
    innerModifier->create(BAR_POSITIONS[barPosition], tabController);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        GetTabsModel()->Create(BAR_POSITIONS[barPosition], index, swiperController);
    } else {
        GetTabsInnerModifier()->create(BAR_POSITIONS[barPosition], tabController);
    }
#endif
}

void FfiOHOSAceFrameworkTabsPop()
{
    GetTabsModel()->Pop();
}

void FfiOHOSAceFrameworkTabsSetWidth(double width, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);

    Dimension value(width, static_cast<DimensionUnit>(unit));
    if (value.Unit() == DimensionUnit::AUTO) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        GetTabsModel()->SetWidthAuto(true);
        return;
    }

    GetTabsModel()->SetWidthAuto(false);
}

void FfiOHOSAceFrameworkTabsSetHeight(double height, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);

    Dimension value(height, static_cast<DimensionUnit>(unit));
    if (value.Unit() == DimensionUnit::AUTO) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        GetTabsModel()->SetHeightAuto(true);
        return;
    }

    GetTabsModel()->SetHeightAuto(false);
}

void FfiOHOSAceFrameworkTabsSetBarWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    GetTabsModel()->SetTabBarWidth(value);
}

void FfiOHOSAceFrameworkTabsSetBarHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    bool adaptiveHeight = false;
    if (value.Unit() == DimensionUnit::AUTO) {
        adaptiveHeight = true;
    }
    GetTabsModel()->SetTabBarHeight(value);
    GetTabsModel()->SetBarAdaptiveHeight(adaptiveHeight);
}

void FfiOHOSAceFrameworkTabsSetBarMode(int32_t barMode)
{
    if (!Utils::CheckParamsValid(barMode, TAB_BAR_MODES.size())) {
        LOGE("invalid value for tab bar mode");
        return;
    }
    GetTabsModel()->SetTabBarMode(TAB_BAR_MODES[barMode]);
}

void FfiOHOSAceFrameworkTabsSetBarModeWithOptions(int32_t barMode, CJTabsScrollableBarModeOptions options)
{
    if (!Utils::CheckParamsValid(barMode, TAB_BAR_MODES.size())) {
        LOGE("invalid value for tab bar mode");
        return;
    }
    TabBarMode barModeEnum = TabBarMode::FIXED;
    barModeEnum = TAB_BAR_MODES[barMode];
    if (barModeEnum == TabBarMode::SCROLLABLE) {
        ScrollableBarModeOptions option;
        Dimension margin(options.margin, static_cast<DimensionUnit>(options.marginUnit));
        if (margin.IsNegative() || margin.Unit() == DimensionUnit::PERCENT) {
            option.margin = 0.0_vp;
        } else {
            option.margin = margin;
        }
        if (options.nonScrollableLayoutStyle < static_cast<int>(LayoutStyle::ALWAYS_CENTER) ||
            options.nonScrollableLayoutStyle > static_cast<int>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
            option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
        } else {
            option.nonScrollableLayoutStyle = static_cast<LayoutStyle>(options.nonScrollableLayoutStyle);
        }
        GetTabsModel()->SetScrollableBarModeOptions(option);
    }
    GetTabsModel()->SetTabBarMode(barModeEnum);
}

void FfiOHOSAceFrameworkTabsSetIndex(int32_t index)
{
    GetTabsModel()->SetIndex(index);
}

void FfiOHOSAceFrameworkTabsSetVertical(bool isVertical)
{
    GetTabsModel()->SetIsVertical(isVertical);
}

void FfiOHOSAceFrameworkTabsSetScrollable(bool isScrollable)
{
    GetTabsModel()->SetScrollable(isScrollable);
}

void FfiOHOSAceFrameworkTabsSetAnimationDuration(float duration)
{
    GetTabsModel()->SetAnimationDuration(duration);
}

void FfiOHOSAceFrameworkTabsSetAnimateMode(int32_t animateMode)
{
    if (!Utils::CheckParamsValid(animateMode, TAB_ANIMATE_MODES.size())) {
        LOGE("invalid value for tab animate mode");
        return;
    }
    GetTabsModel()->SetAnimateMode(TAB_ANIMATE_MODES[animateMode]);
}

void FfiOHOSAceFrameworkTabsSetBarPosition(int32_t barPosition)
{
    if (!Utils::CheckParamsValid(barPosition, BAR_POSITIONS.size())) {
        LOGE("invalid value for bar position");
        return;
    }
    GetTabsModel()->SetTabBarPosition(BAR_POSITIONS[barPosition]);
}

void FfiOHOSAceFrameworkTabsSetDivider(CJTabsDividerStyle dividerStyle)
{
    TabsItemDivider divider;
    Dimension strokeWidth(dividerStyle.strokeWidth, static_cast<DimensionUnit>(dividerStyle.strokeWidthUnit));
    if (strokeWidth.Value() < 0.0f || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        divider.strokeWidth.Reset();
    } else {
        divider.strokeWidth = strokeWidth;
    }

    divider.color = Color(dividerStyle.color);

    Dimension startMargin(dividerStyle.startMargin, static_cast<DimensionUnit>(dividerStyle.startMarginUnit));
    if (startMargin.Value() < 0.0f || startMargin.Unit() == DimensionUnit::PERCENT) {
        divider.startMargin.Reset();
    } else {
        divider.startMargin = startMargin;
    }

    Dimension endMargin(dividerStyle.endMargin, static_cast<DimensionUnit>(dividerStyle.endMarginUnit));
    if (endMargin.Value() < 0.0f || endMargin.Unit() == DimensionUnit::PERCENT) {
        divider.endMargin.Reset();
    } else {
        divider.endMargin = endMargin;
    }

    GetTabsModel()->SetDivider(divider);
}

void FfiOHOSAceFrameworkTabsSetFadingEdge(bool fadingEdge)
{
    GetTabsModel()->SetFadingEdge(fadingEdge);
}

void FfiOHOSAceFrameworkTabsSetBarOverlap(bool barOverlap)
{
    GetTabsModel()->SetBarOverlap(barOverlap);
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundColor(uint32_t backgroundColor)
{
    GetTabsModel()->SetBarBackgroundColor(Color(backgroundColor));
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundBlurStyle(int32_t blurStyle)
{
    BlurStyleOption styleOption;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    GetTabsModel()->SetBarBackgroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundBlurStyleWithOptions(
    int32_t blurStyle, CJTabsBarBackgroundBlurStyleOptions options)
{
    BlurStyleOption styleOption;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    auto colorMode = options.colorMode;
    if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
        colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
        styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
    }

    auto adaptiveColor = options.adaptiveColor;
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    auto policy = options.policy;
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        styleOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    auto inactiveColor = options.inactiveColor;
    if (inactiveColor >= 0) {
        styleOption.inactiveColor = Color(options.inactiveColor);
        styleOption.isValidColor = true;
    }

    double scale = options.scale;
    styleOption.scale = std::clamp(scale, 0.0, 1.0);

    BlurOption blurOption;
    const auto& cjGrayScale = *reinterpret_cast<std::vector<float>*>(options.blurOptions.grayscale);
    if (cjGrayScale.size() == GRAY_SCALE_ARRAY_SIZE) {
        blurOption.grayscale = cjGrayScale;
    }
    styleOption.blurOption = blurOption;
    GetTabsModel()->SetBarBackgroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkTabsSetBarGridAlign(CJTabsBarGridColumnOptions options)
{
    BarGridColumnOptions columnOption;
    if (options.sm >= 0 && options.sm <= SM_COLUMN_NUM && options.sm % EVEN_MOD == 0) {
        columnOption.sm = options.sm;
    }
    if (options.md >= 0 && options.md <= MD_COLUMN_NUM && options.md % EVEN_MOD == 0) {
        columnOption.md = options.md;
    }
    if (options.lg >= 0 && options.lg <= LG_COLUMN_NUM && options.lg % EVEN_MOD == 0) {
        columnOption.lg = options.lg;
    }
    CalcDimension gutter(options.gutter, static_cast<DimensionUnit>(options.gutterUnit));
    if (gutter.IsNonNegative() && gutter.Unit() != DimensionUnit::PERCENT) {
        columnOption.gutter = gutter;
    }

    CalcDimension margin(options.margin, static_cast<DimensionUnit>(options.marginUnit));
    if (margin.IsNonNegative() && margin.Unit() != DimensionUnit::PERCENT) {
        columnOption.margin = margin;
    }
    GetTabsModel()->SetBarGridAlign(columnOption);
}

void FfiOHOSAceFrameworkTabsSetEdgeEffect(int32_t edgeEffect)
{
    auto edgeEffectData = EdgeEffect::SPRING;
    if (edgeEffect >= static_cast<int32_t>(EdgeEffect::SPRING) &&
        edgeEffect <= static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffectData = static_cast<EdgeEffect>(edgeEffect);
    }
    GetTabsModel()->SetEdgeEffect(edgeEffectData);
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundEffect(CJTabsBackgroundEffectOptions options)
{
    EffectOption effectOption;
    CalcDimension radius(options.radius, static_cast<DimensionUnit>(DimensionUnit::VP));
    if (LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = radius;

    effectOption.saturation = (options.saturation > 0.0f || NearZero(options.saturation)) ? options.saturation : 1.0f;

    effectOption.brightness = (options.brightness > 0.0f || NearZero(options.brightness)) ? options.brightness : 1.0f;

    effectOption.color = Color(options.color);

    if (options.adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        options.adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        effectOption.adaptiveColor = static_cast<AdaptiveColor>(options.adaptiveColor);
    }

    BlurOption blurOption;
    const auto& cjGrayScale = *reinterpret_cast<std::vector<float>*>(options.blurOptions.grayscale);
    if (cjGrayScale.size() == GRAY_SCALE_ARRAY_SIZE) {
        blurOption.grayscale = cjGrayScale;
    }
    effectOption.blurOption = blurOption;

    auto policy = options.policy;
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        effectOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    auto inactiveColor = options.inactiveColor;
    if (inactiveColor >= 0) {
        effectOption.inactiveColor = Color(inactiveColor);
        effectOption.isValidColor = true;
    }

    GetTabsModel()->SetBarBackgroundEffect(effectOption);
}

void FfiOHOSAceFrameworkTabsOnChange(void (*callback)(int32_t index))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("HandleChangeEvent tabsInfo == nullptr");
            return;
        }
        lambda(tabsInfo->GetIndex());
    };
    GetTabsModel()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkTabsOnTabBarClick(void (*callback)(int32_t index))
{
    auto onTabBarClick = [lambda = CJLambda::Create(callback)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("HandleChangeEvent tabsInfo == nullptr");
            return;
        }
        lambda(tabsInfo->GetIndex());
    };
    GetTabsModel()->SetOnTabBarClick(std::move(onTabBarClick));
}

void FfiOHOSAceFrameworkTabsOnAnimationStart(
    void (*callback)(int32_t index, int32_t targetIndex, CJTabsAnimationEvent event))
{
    auto onAnimationStart = [lambda = CJLambda::Create(callback)](
                                int32_t ngIndex, int32_t ngTargetIndex, const AnimationCallbackInfo& info) {
        CJTabsAnimationEvent tabsAnimationEvent = {};
        if (info.currentOffset.has_value()) {
            tabsAnimationEvent.currentOffset = info.currentOffset.value();
        }
        if (info.targetOffset.has_value()) {
            tabsAnimationEvent.targetOffset = info.targetOffset.value();
        }
        if (info.velocity.has_value()) {
            tabsAnimationEvent.velocity = info.velocity.value();
        }
        lambda(ngIndex, ngTargetIndex, tabsAnimationEvent);
    };
    GetTabsModel()->SetOnAnimationStart(std::move(onAnimationStart));
}

void FfiOHOSAceFrameworkTabsOnAnimationEnd(void (*callback)(int32_t index, CJTabsAnimationEvent event))
{
    auto onAnimationEnd = [lambda = CJLambda::Create(callback)](int32_t ngIndex, const AnimationCallbackInfo& info) {
        CJTabsAnimationEvent tabsAnimationEvent = {};
        if (info.currentOffset.has_value()) {
            tabsAnimationEvent.currentOffset = info.currentOffset.value();
        }
        if (info.targetOffset.has_value()) {
            tabsAnimationEvent.targetOffset = info.targetOffset.value();
        }
        if (info.velocity.has_value()) {
            tabsAnimationEvent.velocity = info.velocity.value();
        }
        lambda(ngIndex, tabsAnimationEvent);
    };
    GetTabsModel()->SetOnAnimationEnd(std::move(onAnimationEnd));
}

void FfiOHOSAceFrameworkTabsOnGestureSwipe(void (*callback)(int32_t index, CJTabsAnimationEvent event))
{
    auto onGestureSwipe = [lambda = CJLambda::Create(callback)](int32_t ngIndex, const AnimationCallbackInfo& info) {
        CJTabsAnimationEvent tabsAnimationEvent = {};
        if (info.currentOffset.has_value()) {
            tabsAnimationEvent.currentOffset = info.currentOffset.value();
        }
        if (info.targetOffset.has_value()) {
            tabsAnimationEvent.targetOffset = info.targetOffset.value();
        }
        if (info.velocity.has_value()) {
            tabsAnimationEvent.velocity = info.velocity.value();
        }
        lambda(ngIndex, tabsAnimationEvent);
    };
    GetTabsModel()->SetOnGestureSwipe(std::move(onGestureSwipe));
}

void FfiOHOSAceFrameworkTabsCustomContentTransition(
    CJTabContentAnimatedTransition (*callback)(int32_t from, int32_t to))
{
    auto onCustomAnimation = [lambda = CJLambda::Create(callback)](
                                 int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;

        CJTabContentAnimatedTransition ret = lambda(from, to);
        if (ret.isUndefined) {
            GetTabsModel()->SetIsCustomAnimation(false);
            return transitionInfo;
        }

        transitionInfo.timeout = ret.timeout < 0 ? DEFAULT_CUSTOM_ANIMATION_TIMEOUT : ret.timeout;
        auto onTransition = [transitionLambda = CJLambda::Create(ret.transition)](
                                const RefPtr<TabContentTransitionProxy>& proxy) {
            auto cjProxy = FFIData::Create<CJTabContentTransitionProxy>(proxy);
            if (cjProxy == nullptr) {
                return;
            }
            transitionLambda(cjProxy->getFromIndex(), cjProxy->getToIndex(), cjProxy->GetID());
        };
        transitionInfo.transition = std::move(onTransition);

        return transitionInfo;
    };
    GetTabsModel()->SetIsCustomAnimation(true);
    GetTabsModel()->SetOnCustomAnimation(std::move(onCustomAnimation));
}

void FfiOHOSAceFrameworkTabsCustomAnimationFinishTransition(int64_t id)
{
    auto cjTabContentTransitionProxy = FFIData::GetData<CJTabContentTransitionProxy>(id);
    cjTabContentTransitionProxy->finishTransition();
}

void FfiOHOSAceFrameworkTabsOnContentWillChange(bool (*callback)(int32_t currentIndex, int32_t comingIndex))
{
    auto onContentWillChange = [lambda = CJLambda::Create(callback)](int32_t ngCurrentIndex,
                                   int32_t ngComingIndex) -> bool { return lambda(ngCurrentIndex, ngComingIndex); };
    GetTabsModel()->SetOnContentWillChange(std::move(onContentWillChange));
}

int64_t FfiOHOSAceFrameworkTabsControllerCtor()
{
    auto ret_ = FFIData::Create<TabsController>();
    return ret_->GetID();
}

void FfiOHOSAceFrameworkTabsControllerChangeIndex(int64_t selfId, int32_t index)
{
    auto self_ = FFIData::GetData<TabsController>(selfId);
    if (self_ != nullptr) {
        self_->ChangeIndex(index);
    }
}

void FfiOHOSAceFrameworkTabsControllerPreloadItems(int64_t selfId, VectorInt32Ptr indices)
{
    auto self_ = FFIData::GetData<TabsController>(selfId);
    const auto& indicesArray = *reinterpret_cast<std::vector<int32_t>*>(indices);
    if (self_ != nullptr && indicesArray.size() > 0) {
        std::set<int32_t> indexSet;
        for (size_t i = 0; i < indicesArray.size(); i++) {
            indexSet.emplace(indicesArray.at(i));
        }
        self_->PreloadItems(indexSet);
    }
}

void FfiOHOSAceFrameworkTabsControllerSetTabBarTranslate(
    int64_t selfId, OHOS::Ace::Framework::CTranslateOptions translate)
{
    auto self_ = FFIData::GetData<TabsController>(selfId);
    if (self_ != nullptr) {
        CalcDimension x(translate.x, static_cast<DimensionUnit>(translate.xType));
        CalcDimension y(translate.y, static_cast<DimensionUnit>(translate.yType));
        CalcDimension z(translate.z, static_cast<DimensionUnit>(translate.zType));
        auto options = NG::TranslateOptions(x, y, z);
        self_->SetTabBarTranslate(options);
    }
}

void FfiOHOSAceFrameworkTabsControllerSetTabBarOpacity(int64_t selfId, double opacity)
{
    auto self_ = FFIData::GetData<TabsController>(selfId);
    if (self_ != nullptr) {
        double cOpacity = std::clamp(opacity, 0.0, 1.0);
        self_->SetTabBarOpacity(cOpacity);
    }
}

void FfiOHOSAceFrameworkTabContentCreate()
{
    GetTabContentModel()->Create();
}

void FfiOHOSAceFrameworkTabContentPop()
{
    GetTabContentModel()->Pop();
}

void FfiOHOSAceFrameworkTabContentSetTabBar(const char* content)
{
    GetTabContentModel()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    GetTabContentModel()->SetTabBar(content, std::nullopt, std::nullopt, nullptr, true);
    GetTabContentModel()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text)
{
    GetTabContentModel()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    GetTabContentModel()->SetTabBar(text, icon, std::nullopt, nullptr, false);
    GetTabContentModel()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)())
{
    GetTabContentModel()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    GetTabContentModel()->SetTabBar(
        std::nullopt, std::nullopt, std::nullopt, CJLambda::Create(callback), false);
    GetTabContentModel()->SetTabBarWithContent(nullptr);
}

void SetPadding(CJPadding cjPadding, bool isSubTabStyle)
{
    CalcDimension length;
    NG::PaddingProperty padding;
    bool useLocalizedPadding = false;

    RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
    if (tabTheme) {
        if (isSubTabStyle) {
            padding.top = NG::CalcLength(tabTheme->GetSubTabTopPadding());
            padding.bottom = NG::CalcLength(tabTheme->GetSubTabBottomPadding());
            padding.left = NG::CalcLength(tabTheme->GetSubTabHorizontalPadding());
            padding.right = NG::CalcLength(tabTheme->GetSubTabHorizontalPadding());
        } else {
            padding.top = NG::CalcLength(0.0_vp);
            padding.bottom = NG::CalcLength(0.0_vp);
            padding.left = NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
            padding.right = NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
        }
    }

    CalcDimension left(cjPadding.left, static_cast<DimensionUnit>(cjPadding.leftUnit));
    if (left.Value() >= 0 && left.Unit() != DimensionUnit::PERCENT) {
        padding.left = NG::CalcLength(left);
    }
    CalcDimension right(cjPadding.right, static_cast<DimensionUnit>(cjPadding.rightUnit));
    if (right.Value() >= 0 && right.Unit() != DimensionUnit::PERCENT) {
        padding.right = NG::CalcLength(right);
    }
    CalcDimension top(cjPadding.top, static_cast<DimensionUnit>(cjPadding.topUnit));
    if (top.Value() >= 0 && top.Unit() != DimensionUnit::PERCENT) {
        padding.top = NG::CalcLength(top);
    }
    CalcDimension bottom(cjPadding.bottom, static_cast<DimensionUnit>(cjPadding.bottomUnit));
    if (bottom.Value() >= 0 && bottom.Unit() != DimensionUnit::PERCENT) {
        padding.bottom = NG::CalcLength(bottom);
    }

    if (cjPadding.paddingType == static_cast<int32_t>(PaddingType::LENGTH)) {
        GetTabContentModel()->SetPadding(padding);
        return;
    }

    if (cjPadding.paddingType == static_cast<int32_t>(PaddingType::LOCALIZEDPADDING)) {
        useLocalizedPadding = true;
    }

    GetTabContentModel()->SetPadding(padding);
    GetTabContentModel()->SetUseLocalizedPadding(useLocalizedPadding);
}

void SetLayoutMode(int32_t layoutMode)
{
    auto mode = LayoutMode::VERTICAL;
    if (layoutMode >= static_cast<int32_t>(LayoutMode::AUTO) &&
        layoutMode <= static_cast<int32_t>(LayoutMode::HORIZONTAL)) {
        mode = static_cast<LayoutMode>(layoutMode);
    }
    GetTabContentModel()->SetLayoutMode(mode);
}

void SetVerticalAlign(int32_t verticalAlign)
{
    auto align = FlexAlign::CENTER;
    if (verticalAlign >= static_cast<int32_t>(FlexAlign::FLEX_START) &&
        verticalAlign <= static_cast<int32_t>(FlexAlign::FLEX_END)) {
        align = static_cast<FlexAlign>(verticalAlign);
    }
    GetTabContentModel()->SetVerticalAlign(align);
}

void SetSymmetricExtensible(bool isExtensible)
{
    GetTabContentModel()->SetSymmetricExtensible(isExtensible);
}

void GetFontContent(CJFont font, LabelStyle& labelStyle, bool isSubTabStyle)
{
    CalcDimension size(font.size, static_cast<DimensionUnit>(font.sizeUnit));
    if (size.Value() >= 0 && size.Unit() != DimensionUnit::PERCENT) {
        labelStyle.fontSize = size;
    }

    auto parseResult = StringUtils::ParseFontWeight(font.weight, FontWeight::NORMAL);
    if (parseResult.first || isSubTabStyle) {
        labelStyle.fontWeight = parseResult.second;
    }

    labelStyle.fontFamily = ConvertStrToFontFamilies(font.family);

    labelStyle.fontStyle = FontStyle::NORMAL;
    if (font.style >= static_cast<int32_t>(FontStyle::NORMAL) &&
        font.style <= static_cast<int32_t>(FontStyle::ITALIC)) {
        labelStyle.fontStyle = static_cast<FontStyle>(font.style);
    }
}

void CompleteParameters(LabelStyle& labelStyle, bool isSubTabStyle)
{
    auto tabTheme = GetTheme<TabTheme>();
    if (!tabTheme) {
        return;
    }
    if (!labelStyle.maxLines.has_value()) {
        labelStyle.maxLines = 1;
    }
    if (!labelStyle.minFontSize.has_value()) {
        labelStyle.minFontSize = 0.0_vp;
    }
    if (!labelStyle.maxFontSize.has_value()) {
        labelStyle.maxFontSize = 0.0_vp;
    }
    if (!labelStyle.fontSize.has_value()) {
        if (isSubTabStyle) {
            labelStyle.fontSize = tabTheme->GetSubTabTextDefaultFontSize();
        }
    }
    if (!labelStyle.fontWeight.has_value() && !isSubTabStyle) {
        labelStyle.fontWeight = FontWeight::MEDIUM;
    }
    if (!labelStyle.fontStyle.has_value()) {
        labelStyle.fontStyle = FontStyle::NORMAL;
    }
    if (!labelStyle.heightAdaptivePolicy.has_value()) {
        labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!labelStyle.textOverflow.has_value()) {
        labelStyle.textOverflow = TextOverflow::ELLIPSIS;
    }
}

void SetLabelStyle(CJTabContentLabelStyle cjLabelStyle, bool isSubTabStyle)
{
    auto tabTheme = GetTheme<TabTheme>();

    LabelStyle labelStyle;
    if (Utils::CheckParamsValid(cjLabelStyle.overflow, TEXT_OVER_FLOWS.size())) {
        labelStyle.textOverflow = TEXT_OVER_FLOWS[cjLabelStyle.overflow];
    }

    if (cjLabelStyle.maxLines > 0) {
        labelStyle.maxLines = cjLabelStyle.maxLines;
    }

    CalcDimension minFontSize(cjLabelStyle.minFontSize, static_cast<DimensionUnit>(cjLabelStyle.minFontSizeUnit));
    if (minFontSize.Value() >= 0 && minFontSize.Unit() != DimensionUnit::PERCENT) {
        labelStyle.minFontSize = minFontSize;
    }

    CalcDimension maxFontSize(cjLabelStyle.maxFontSize, static_cast<DimensionUnit>(cjLabelStyle.maxFontSizeUnit));
    if (maxFontSize.Value() >= 0 && maxFontSize.Unit() != DimensionUnit::PERCENT) {
        labelStyle.maxFontSize = maxFontSize;
    }

    if (cjLabelStyle.heightAdaptivePolicy >= static_cast<int32_t>(TextHeightAdaptivePolicy::MAX_LINES_FIRST) &&
        cjLabelStyle.heightAdaptivePolicy <= static_cast<int32_t>(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST)) {
        labelStyle.heightAdaptivePolicy = static_cast<TextHeightAdaptivePolicy>(cjLabelStyle.heightAdaptivePolicy);
    }

    GetFontContent(cjLabelStyle.font, labelStyle, isSubTabStyle);

    labelStyle.unselectedColor = Color(cjLabelStyle.unselectedColor);

    labelStyle.selectedColor = Color(cjLabelStyle.selectedColor);

    CompleteParameters(labelStyle, isSubTabStyle);

    GetTabContentModel()->SetLabelStyle(labelStyle);
}

void SetIconStyle(CJTabBarIconStyle style)
{
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color(style.unselectedColor);
    iconStyle.selectedColor = Color(style.selectedColor);
    GetTabContentModel()->SetIconStyle(iconStyle);
}

void SetId(const char* id)
{
    GetTabContentModel()->SetId(id);
}

void SetIndicator(CJTabContentIndicatorStyle cjIndicator)
{
    IndicatorStyle indicator;

    indicator.color = Color(cjIndicator.color);

    CalcDimension indicatorHeight(cjIndicator.height, static_cast<DimensionUnit>(cjIndicator.heightUnit));
    if (indicatorHeight.Value() < 0.0f || indicatorHeight.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.height = tabTheme->GetActiveIndicatorWidth();
        }
    } else {
        indicator.height = indicatorHeight;
    }

    CalcDimension indicatorWidth(cjIndicator.width, static_cast<DimensionUnit>(cjIndicator.widthUnit));
    if (indicatorWidth.Value() < 0.0f || indicatorWidth.Unit() == DimensionUnit::PERCENT) {
        indicator.width = 0.0_vp;
    } else {
        indicator.width = indicatorWidth;
    }

    CalcDimension indicatorBorderRadius(
        cjIndicator.borderRadius, static_cast<DimensionUnit>(cjIndicator.borderRadiusUnit));
    if (indicatorBorderRadius.Value() < 0.0f || indicatorBorderRadius.Unit() == DimensionUnit::PERCENT) {
        indicator.borderRadius = 0.0_vp;
    } else {
        indicator.borderRadius = indicatorBorderRadius;
    }

    CalcDimension indicatorMarginTop(cjIndicator.marginTop, static_cast<DimensionUnit>(cjIndicator.marginTopUnit));
    if (indicatorMarginTop.Value() < 0.0f || indicatorMarginTop.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
    } else {
        indicator.marginTop = indicatorMarginTop;
    }
    GetTabContentModel()->SetIndicator(indicator);
}

void SetSelectedMode(int32_t selectedMode)
{
    if (selectedMode < static_cast<int32_t>(SelectedMode::INDICATOR) ||
        selectedMode > static_cast<int32_t>(SelectedMode::BOARD)) {
        GetTabContentModel()->SetSelectedMode(SelectedMode::INDICATOR);
    } else {
        GetTabContentModel()->SetSelectedMode(static_cast<SelectedMode>(selectedMode));
    }
}

void SetBoard(CJBoardStyle cjBoardStyle)
{
    BoardStyle board;
    CalcDimension borderRadius(cjBoardStyle.borderRadius, static_cast<DimensionUnit>(cjBoardStyle.borderRadiusUnit));
    if (borderRadius.Value() < 0.0f || borderRadius.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            board.borderRadius = tabTheme->GetFocusIndicatorRadius();
        }
    } else {
        board.borderRadius = borderRadius;
    }
    GetTabContentModel()->SetBoard(board);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithSubTabBarStyle(CJSubTabBarStyle subTabBarStyle)
{
    std::optional<std::string> contentOpt = subTabBarStyle.content;

    SetIndicator(subTabBarStyle.indicator);

    SetSelectedMode(subTabBarStyle.selectedMode);

    SetBoard(subTabBarStyle.board);

    SetLabelStyle(subTabBarStyle.labelStyle, true);

    SetPadding(subTabBarStyle.padding, true);

    SetId(subTabBarStyle.id);

    GetTabContentModel()->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    GetTabContentModel()->SetTabBar(contentOpt, std::nullopt, std::nullopt, nullptr, false);
    GetTabContentModel()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithBottomTabBarStyle(CJBottomTabBarStyle bottomTabBarStyle)
{
    std::optional<std::string> textOpt = std::nullopt;
    if (bottomTabBarStyle.text != nullptr) {
        textOpt = std::optional<std::string>(bottomTabBarStyle.text);
    }

    std::optional<std::string> iconOpt = std::nullopt;
    std::optional<TabBarSymbol> tabBarSymbol = std::nullopt;
    if (bottomTabBarStyle.isTabBarSymbol) {
        LOGW("Not support tab bar symbol.");
    } else {
        iconOpt = std::optional<std::string>(bottomTabBarStyle.icon);
    }

    SetPadding(bottomTabBarStyle.padding, false);

    SetLayoutMode(bottomTabBarStyle.layoutMode);

    SetVerticalAlign(bottomTabBarStyle.verticalAlign);

    SetSymmetricExtensible(bottomTabBarStyle.symmetricExtensible);

    SetLabelStyle(bottomTabBarStyle.labelStyle, false);

    SetIconStyle(bottomTabBarStyle.iconStyle);

    SetId(bottomTabBarStyle.id);

    GetTabContentModel()->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    GetTabContentModel()->SetTabBar(textOpt, iconOpt, tabBarSymbol, nullptr, false);
    GetTabContentModel()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentOnWillShow(void (*callback)())
{
    auto onWillShow = [lambda = CJLambda::Create(callback)]() { lambda(); };
    GetTabContentModel()->SetOnWillShow(std::move(onWillShow));
}

void FfiOHOSAceFrameworkTabContentOnWillHide(void (*callback)())
{
    auto onWillHide = [lambda = CJLambda::Create(callback)]() { lambda(); };
    GetTabContentModel()->SetOnWillHide(std::move(onWillHide));
}

void FfiOHOSAceFrameworkTabContentPUCreate(void (*callback)())
{
    auto childBuild = CJLambda::Create(callback);
    GetTabContentModel()->Create(std::move(childBuild));
}
}

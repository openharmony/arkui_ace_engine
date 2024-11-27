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

#include "cj_lambda.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

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
} // namespace

namespace OHOS::Ace::Framework {

namespace {

int32_t g_tabControllerId = 0;

} // namespace

TabsController::TabsController() : FFIData()
{
    controller_ = TabController::GetController(++g_tabControllerId);
    swiperController_ = AceType::MakeRefPtr<NG::TabsControllerNG>();
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
        const auto& updateCubicCurveCallback = swiperController_->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        swiperController_->SwipeTo(index);
    }
    if (controller_) {
        controller_->SetIndexByController(index, false);
    }
}

void TabsController::PreloadItems(std::set<int32_t> indexSet)
{
    if (swiperController_) {
        swiperController_->PreloadItems(indexSet);
    }
}

void TabsController::SetTabBarTranslate(NG::TranslateOptions options)
{
    if (swiperController_) {
        swiperController_->SetTabBarTranslate(options);
    }
}

void TabsController::SetTabBarOpacity(double opacity)
{
    if (swiperController_) {
        swiperController_->SetTabBarOpacity(opacity);
    }
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
    RefPtr<TabController> tabController;
    RefPtr<SwiperController> swiperController;

    tabController = nativeTabsController->GetController();
    swiperController = nativeTabsController->GetSwiperController();
    tabController->SetInitialIndex(index);
    TabsModel::GetInstance()->Create(BAR_POSITIONS[barPosition], index, tabController, swiperController);
}

void FfiOHOSAceFrameworkTabsPop()
{
    TabsModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameworkTabsSetBarWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    TabsModel::GetInstance()->SetTabBarWidth(value);
}

void FfiOHOSAceFrameworkTabsSetBarHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    TabsModel::GetInstance()->SetTabBarHeight(value);
}

void FfiOHOSAceFrameworkTabsSetBarMode(int32_t barMode)
{
    if (!Utils::CheckParamsValid(barMode, TAB_BAR_MODES.size())) {
        LOGE("invalid value for tab bar mode");
        return;
    }
    TabsModel::GetInstance()->SetTabBarMode(TAB_BAR_MODES[barMode]);
}

void FfiOHOSAceFrameworkTabsSetBarModeWithOptions(int32_t barMode, CJTabsScrollableBarModeOptions options)
{
    if (!Utils::CheckParamsValid(barMode, TAB_BAR_MODES.size())) {
        LOGE("invalid value for tab bar mode");
        return;
    }
    TabBarMode barModeEnum = TabBarMode::FIXED;
    barModeEnum = TAB_BAR_MODES[barMode];
    if (barMode == static_cast<int32_t>(TabBarMode::SCROLLABLE)) {
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
        TabsModel::GetInstance()->SetScrollableBarModeOptions(option);
    }
    TabsModel::GetInstance()->SetTabBarMode(barModeEnum);
}

void FfiOHOSAceFrameworkTabsSetIndex(int32_t index)
{
    TabsModel::GetInstance()->SetIndex(index);
}

void FfiOHOSAceFrameworkTabsSetVertical(bool isVertical)
{
    TabsModel::GetInstance()->SetIsVertical(isVertical);
}

void FfiOHOSAceFrameworkTabsSetScrollable(bool isScrollable)
{
    TabsModel::GetInstance()->SetScrollable(isScrollable);
}

void FfiOHOSAceFrameworkTabsSetAnimationDuration(float duration)
{
    TabsModel::GetInstance()->SetAnimationDuration(duration);
}

void FfiOHOSAceFrameworkTabsSetAnimateMode(int32_t animateMode)
{
    if (!Utils::CheckParamsValid(animateMode, TAB_ANIMATE_MODES.size())) {
        LOGE("invalid value for tab animate mode");
        return;
    }
    TabsModel::GetInstance()->SetAnimateMode(TAB_ANIMATE_MODES[animateMode]);
}

void FfiOHOSAceFrameworkTabsSetBarPosition(int32_t barPosition)
{
    if (!Utils::CheckParamsValid(barPosition, BAR_POSITIONS.size())) {
        LOGE("invalid value for bar position");
        return;
    }
    TabsModel::GetInstance()->SetTabBarPosition(BAR_POSITIONS[barPosition]);
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

    TabsModel::GetInstance()->SetDivider(divider);
}

void FfiOHOSAceFrameworkTabsSetFadingEdge(bool fadingEdge)
{
    TabsModel::GetInstance()->SetFadingEdge(fadingEdge);
}

void FfiOHOSAceFrameworkTabsSetBarOverlap(bool barOverlap)
{
    TabsModel::GetInstance()->SetBarOverlap(barOverlap);
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundColor(uint32_t backgroundColor)
{
    TabsModel::GetInstance()->SetBarBackgroundColor(Color(backgroundColor));
}

void FfiOHOSAceFrameworkTabsSetBarBackgroundBlurStyle(int32_t blurStyle)
{
    BlurStyleOption styleOption;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    TabsModel::GetInstance()->SetBarBackgroundBlurStyle(styleOption);
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
    TabsModel::GetInstance()->SetBarBackgroundBlurStyle(styleOption);
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
    TabsModel::GetInstance()->SetBarGridAlign(columnOption);
}

void FfiOHOSAceFrameworkTabsSetEdgeEffect(int32_t edgeEffect)
{
    auto edgeEffectData = EdgeEffect::SPRING;
    if (edgeEffect >= static_cast<int32_t>(EdgeEffect::SPRING) &&
        edgeEffect <= static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffectData = static_cast<EdgeEffect>(edgeEffect);
    }
    TabsModel::GetInstance()->SetEdgeEffect(edgeEffectData);
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

    TabsModel::GetInstance()->SetBarBackgroundEffect(effectOption);
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
    TabsModel::GetInstance()->SetOnChange(std::move(onChange));
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
    TabsModel::GetInstance()->SetOnTabBarClick(std::move(onTabBarClick));
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
    TabsModel::GetInstance()->SetOnAnimationStart(std::move(onAnimationStart));
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
    TabsModel::GetInstance()->SetOnAnimationEnd(std::move(onAnimationEnd));
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
    TabsModel::GetInstance()->SetOnGestureSwipe(std::move(onGestureSwipe));
}

void FfiOHOSAceFrameworkTabsCustomContentTransition(
    CJTabContentAnimatedTransition (*callback)(int32_t from, int32_t to))
{
    auto onCustomAnimation = [lambda = CJLambda::Create(callback)](
                                 int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;

        CJTabContentAnimatedTransition ret = lambda(from, to);
        if (ret.isUndefined) {
            TabsModel::GetInstance()->SetIsCustomAnimation(false);
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
    TabsModel::GetInstance()->SetIsCustomAnimation(true);
    TabsModel::GetInstance()->SetOnCustomAnimation(std::move(onCustomAnimation));
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
    TabsModel::GetInstance()->SetOnContentWillChange(std::move(onContentWillChange));
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
    TabContentModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkTabContentPop()
{
    TabContentModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameworkTabContentSetTabBar(const char* content)
{
    TabContentModel::GetInstance()->SetTabBar(content, std::nullopt, std::nullopt, nullptr, true);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text)
{
    TabContentModel::GetInstance()->SetTabBar(text, icon, std::nullopt, nullptr, false);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)())
{
    TabContentModel::GetInstance()->SetTabBar(
        std::nullopt, std::nullopt, std::nullopt, CJLambda::Create(callback), false);
}

void FfiOHOSAceFrameworkTabContentOnWillShow(void (*callback)())
{
    auto onWillShow = [lambda = CJLambda::Create(callback)]() { lambda(); };
    TabContentModel::GetInstance()->SetOnWillShow(std::move(onWillShow));
}

void FfiOHOSAceFrameworkTabContentOnWillHide(void (*callback)())
{
    auto onWillHide = [lambda = CJLambda::Create(callback)]() { lambda(); };
    TabContentModel::GetInstance()->SetOnWillHide(std::move(onWillHide));
}

void FfiOHOSAceFrameworkTabContentPUCreate(void (*callback)())
{
    auto childBuild = CJLambda::Create(callback);
    TabContentModel::GetInstance()->Create(std::move(childBuild));
}
}

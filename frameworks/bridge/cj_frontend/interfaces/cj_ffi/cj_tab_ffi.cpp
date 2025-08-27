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
const std::vector<TextOverflow> TEXT_OVER_FLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE,
    TextOverflow::MARQUEE };
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
    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    TabContentModel::GetInstance()->SetTabBar(content, std::nullopt, std::nullopt, nullptr, true);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text)
{
    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    TabContentModel::GetInstance()->SetTabBar(text, icon, std::nullopt, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)())
{
    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    TabContentModel::GetInstance()->SetTabBar(
        std::nullopt, std::nullopt, std::nullopt, CJLambda::Create(callback), false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
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
        TabContentModel::GetInstance()->SetPadding(padding);
        return;
    }

    if (cjPadding.paddingType == static_cast<int32_t>(PaddingType::LOCALIZEDPADDING)) {
        useLocalizedPadding = true;
    }

    TabContentModel::GetInstance()->SetPadding(padding);
    TabContentModel::GetInstance()->SetUseLocalizedPadding(useLocalizedPadding);
}

void SetLayoutMode(int32_t layoutMode)
{
    auto mode = LayoutMode::VERTICAL;
    if (layoutMode >= static_cast<int32_t>(LayoutMode::AUTO) &&
        layoutMode <= static_cast<int32_t>(LayoutMode::HORIZONTAL)) {
        mode = static_cast<LayoutMode>(layoutMode);
    }
    TabContentModel::GetInstance()->SetLayoutMode(mode);
}

void SetVerticalAlign(int32_t verticalAlign)
{
    auto align = FlexAlign::CENTER;
    if (verticalAlign >= static_cast<int32_t>(FlexAlign::FLEX_START) &&
        verticalAlign <= static_cast<int32_t>(FlexAlign::FLEX_END)) {
        align = static_cast<FlexAlign>(verticalAlign);
    }
    TabContentModel::GetInstance()->SetVerticalAlign(align);
}

void SetSymmetricExtensible(bool isExtensible)
{
    TabContentModel::GetInstance()->SetSymmetricExtensible(isExtensible);
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

    TabContentModel::GetInstance()->SetLabelStyle(labelStyle);
}

void SetIconStyle(CJTabBarIconStyle style)
{
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color(style.unselectedColor);
    iconStyle.selectedColor = Color(style.selectedColor);
    TabContentModel::GetInstance()->SetIconStyle(iconStyle);
}

void SetId(const char* id)
{
    TabContentModel::GetInstance()->SetId(id);
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
    TabContentModel::GetInstance()->SetIndicator(indicator);
}

void SetSelectedMode(int32_t selectedMode)
{
    if (selectedMode < static_cast<int32_t>(SelectedMode::INDICATOR) ||
        selectedMode > static_cast<int32_t>(SelectedMode::BOARD)) {
        TabContentModel::GetInstance()->SetSelectedMode(SelectedMode::INDICATOR);
    } else {
        TabContentModel::GetInstance()->SetSelectedMode(static_cast<SelectedMode>(selectedMode));
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
    TabContentModel::GetInstance()->SetBoard(board);
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

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(contentOpt, std::nullopt, std::nullopt, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
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

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, tabBarSymbol, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
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

/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/tabs_modifier.h"

#include "bridge/common/utils/utils.h"
#include "compatible/components/tab_bar/tab_controller.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_controller_modifier_peer_impl.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_model_static.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int DEFAULT_LENGTH = 3;
constexpr int DEFAULT_LENGTH_OF_BAR_GRID_ALIGN = 5;
constexpr int DEFAULT_LENGTH_OF_BAR_GRID_ALIGN_VALUES = 2;
constexpr int DEFAULT_ANIMATION_DURATION = 300;
constexpr int ANIMATION_CURVE_TYPE_STR = 1;
constexpr int ANIMATION_CURVE_TYPE_FUNC = 2;

#ifndef CROSS_PLATFORM
uint32_t g_tabsControllerId = 0;
#endif

struct TabsResourceObjParam {
    TabJsResType jsResourceType;
    ResourceObject* resourceObj = nullptr;
};

#ifndef CROSS_PLATFORM
TabsModel* GetTabsModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tabs");
    static TabsModel* instance = loader ? reinterpret_cast<TabsModel*>(loader->CreateModel()) : nullptr;
    return instance;
}

void CreateTabsImpl(
    ArkUI_Int32 barPosition, ArkUI_Int32 index, ArkUINodeHandle tabsController, ArkUINodeHandle tabController)
{
    (void)tabsController;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    CHECK_NULL_VOID(tabController);
    tabsModelImpl->Create(
        static_cast<BarPosition>(barPosition), AceType::Claim(reinterpret_cast<AceType*>(tabController)));
}

void PopTabsImpl()
{
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->Pop();
}

void SetTabBarModeImpl(ArkUINodeHandle node, ArkUI_Int32 tabsBarMode)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetTabBarMode(static_cast<TabBarMode>(tabsBarMode));
}

void SetScrollableBarModeOptionsImpl(ArkUINodeHandle node, const ArkUI_Float32 value,
    ArkUI_Int32 unit, ArkUI_Int32 layoutStyle)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    ScrollableBarModeOptions option;
    option.margin = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    if (layoutStyle >= static_cast<int32_t>(LayoutStyle::ALWAYS_CENTER) &&
        layoutStyle <= static_cast<int32_t>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
        option.nonScrollableLayoutStyle = static_cast<LayoutStyle>(layoutStyle);
    }
    tabsModelImpl->SetScrollableBarModeOptions(option);
}

void CreateScrollableBarModeOptionsWithResourceObjImpl(ArkUINodeHandle node, void* marginRawPtr)
{
    (void)node;
    (void)marginRawPtr;
}

void SetBarGridAlignImpl(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesLength,
    const ArkUI_Int32* units, ArkUI_Int32 unitsLength)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (unitsLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN || valuesLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN_VALUES) {
        return;
    }
    BarGridColumnOptions columnOption;
    columnOption.sm = units[NUM_2];
    columnOption.md = units[NUM_3];
    columnOption.lg = units[NUM_4];
    columnOption.gutter = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    columnOption.margin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    tabsModelImpl->SetBarGridAlign(columnOption);
}

void CreateBarGridAlignWithResourceObjImpl(ArkUINodeHandle node, void* columnGutterRawPtr, void* columnMarginRawPtr)
{
    (void)node;
    (void)columnGutterRawPtr;
    (void)columnMarginRawPtr;
}

void SetDividerImpl(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    divider.startMargin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    divider.endMargin = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    divider.color = Color(color);
    tabsModelImpl->SetDivider(divider);
}

void SetDividerColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetDividerColorByUser(isByUser);
}

void CreateDividerWithResourceObjImpl(ArkUINodeHandle node,
    void* strokeWidthRawPtr, void* colorRawPtr, void* startMarginRawPtr, void* endMarginRawPtr)
{
    (void)node;
    (void)strokeWidthRawPtr;
    (void)colorRawPtr;
    (void)startMarginRawPtr;
    (void)endMarginRawPtr;
}

void SetFadingEdgeImpl(ArkUINodeHandle node, ArkUI_Bool fadingEdge)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetFadingEdge(fadingEdge);
}

void SetTabOnUnselectedImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        tabsModelImpl->SetOnUnselected(std::move(*onEvent));
    } else {
        tabsModelImpl->SetOnUnselected(nullptr);
    }
}

void SetTabsOnContentDidScrollImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onContentDidScroll = reinterpret_cast<ContentDidScrollEvent*>(callback);
        tabsModelImpl->SetOnContentDidScroll(std::move(*onContentDidScroll));
    } else {
        tabsModelImpl->SetOnContentDidScroll(nullptr);
    }
}

void SetBarBackgroundColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarBackgroundColor(Color(color));
    tabsModelImpl->SetBarBackgroundColorByUser(true);
}

void SetBarBackgroundColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool colorByUser)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarBackgroundColorByUser(colorByUser);
}

void CreateBarBackgroundColorWithResourceObjImpl(ArkUINodeHandle node, void* bgColorRawPtr)
{
    (void)node;
    (void)bgColorRawPtr;
}

void SetBarBackgroundBlurStyleImpl(ArkUINodeHandle node, ArkUITabBarBackgroundBlurStyle* styleOption)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    CHECK_NULL_VOID(styleOption);
    BlurStyleOption bgBlurStyle;
    if (styleOption->blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        styleOption->blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        bgBlurStyle.blurStyle = static_cast<BlurStyle>(styleOption->blurStyle);
    }
    bgBlurStyle.colorMode = static_cast<ThemeColorMode>(styleOption->colorMode);
    bgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(styleOption->adaptiveColor);
    bgBlurStyle.scale = std::clamp(styleOption->scale, 0.0f, 1.0f);
    BlurOption blurOption;
    blurOption.grayscale.assign(styleOption->blurValues, styleOption->blurValues + styleOption->blurValuesSize);
    bgBlurStyle.blurOption = blurOption;
    bgBlurStyle.policy = static_cast<BlurStyleActivePolicy>(styleOption->policy);
    bgBlurStyle.blurType = static_cast<BlurType>(styleOption->blurType);
    bgBlurStyle.isValidColor = styleOption->isValidColor;
    bgBlurStyle.inactiveColor = Color(styleOption->inactiveColor);
    tabsModelImpl->SetBarBackgroundBlurStyle(bgBlurStyle);
}

void CreateBarBackgroundBlurStyleWithResourceObjImpl(ArkUINodeHandle node, void* inactiveColorRawPtr)
{
    (void)node;
    (void)inactiveColorRawPtr;
}

void SetBarOverlapImpl(ArkUINodeHandle node, ArkUI_Bool barOverlap)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarOverlap(barOverlap);
}

void SetIsVerticalImpl(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetIsVertical(isVertical);
}

void SetTabBarPositionImpl(ArkUINodeHandle node, ArkUI_Int32 barVal)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetTabBarPosition(static_cast<BarPosition>(barVal));
}

void SetTabsOptionsIndexImpl(ArkUINodeHandle node, ArkUI_Int32 indexVal)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetIndex(indexVal < 0 ? 0 : indexVal);
}

void SetTabsOptionsControllerImpl(ArkUINodeHandle node, ArkUINodeHandle tabsController)
{
    (void)node;
    (void)tabsController;
}

void SetTabsOptionsBarModifierImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onApply = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(callback);
        tabsModelImpl->SetBarModifier(std::move(*onApply));
    } else {
        tabsModelImpl->SetBarModifier(nullptr);
    }
}

void SetScrollableImpl(ArkUINodeHandle node, ArkUI_Bool scrollable)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetScrollable(scrollable);
}

void SetBarAdaptiveHeightImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarAdaptiveHeight(value);
}

void SetNoMinHeightLimitImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetNoMinHeightLimit(value);
}

void SetTabBarWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetTabBarWidth(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void CreateTabBarWidthWithResourceObjImpl(ArkUINodeHandle node, void* widthRawPtr)
{
    (void)node;
    (void)widthRawPtr;
}

void SetTabBarHeightImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetTabBarHeight(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void CreateTabBarHeightWithResourceObjImpl(ArkUINodeHandle node, void* heightRawPtr)
{
    (void)node;
    (void)heightRawPtr;
}

void SetAnimationCurveImpl(ArkUINodeHandle node, ArkUI_Uint32 type, ArkUI_CharPtr curveChar, void* curveCallback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    RefPtr<Curve> curve;
    if (type == ANIMATION_CURVE_TYPE_STR && curveChar != nullptr) {
        curve = Framework::CreateCurve(curveChar, false);
    } else if (type == ANIMATION_CURVE_TYPE_FUNC && curveCallback != nullptr) {
        auto callback = reinterpret_cast<std::function<float(float)>*>(curveCallback);
        curve = Framework::CreateCurve(*callback);
    }
    tabsModelImpl->SetAnimationCurve(curve);
}

void SetAnimationDurationImpl(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetAnimationDuration(std::isnan(duration) ? DEFAULT_ANIMATION_DURATION : duration);
}

void ResetTabBarModeImpl(ArkUINodeHandle node)
{
    SetTabBarModeImpl(node, static_cast<ArkUI_Int32>(TabBarMode::FIXED));
}

void ResetScrollableBarModeOptionsImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->ResetScrollableBarModeOptions();
}

void ResetBarGridAlignImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarGridAlign(BarGridColumnOptions());
}

void ResetDividerImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    TabsItemDivider divider;
    divider.isNull = true;
    tabsModelImpl->SetDivider(divider);
    tabsModelImpl->SetDividerColorByUser(false);
}

void ResetFadingEdgeImpl(ArkUINodeHandle node)
{
    SetFadingEdgeImpl(node, true);
}

void ResetTabOnUnselectedImpl(ArkUINodeHandle node)
{
    SetTabOnUnselectedImpl(node, nullptr);
}

void ResetTabsOnContentDidScrollImpl(ArkUINodeHandle node)
{
    SetTabsOnContentDidScrollImpl(node, nullptr);
}

void ResetBarBackgroundColorImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarBackgroundColor(Color::BLACK.BlendOpacity(0.0f));
    tabsModelImpl->SetBarBackgroundColorByUser(false);
}

void ResetBarBackgroundBlurStyleImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetBarBackgroundBlurStyle(BlurStyleOption());
}

void ResetBarOverlapImpl(ArkUINodeHandle node)
{
    SetBarOverlapImpl(node, false);
}

void ResetIsVerticalImpl(ArkUINodeHandle node)
{
    SetIsVerticalImpl(node, false);
}

void ResetTabBarPositionImpl(ArkUINodeHandle node)
{
    SetTabBarPositionImpl(node, static_cast<ArkUI_Int32>(BarPosition::START));
}

void ResetTabsOptionsIndexImpl(ArkUINodeHandle node)
{
    SetTabsOptionsIndexImpl(node, 0);
}

void ResetTabsOptionsBarModifierImpl(ArkUINodeHandle node)
{
    SetTabsOptionsBarModifierImpl(node, nullptr);
}

void ResetScrollableImpl(ArkUINodeHandle node)
{
    SetScrollableImpl(node, true);
}

void ResetTabBarWidthImpl(ArkUINodeHandle node)
{
    SetTabBarWidthImpl(node, -1.0f, static_cast<ArkUI_Int32>(DimensionUnit::VP));
}

void ResetTabBarHeightImpl(ArkUINodeHandle node)
{
    SetTabBarHeightImpl(node, -1.0f, static_cast<ArkUI_Int32>(DimensionUnit::VP));
}

void ResetBarAdaptiveHeightImpl(ArkUINodeHandle node)
{
    SetBarAdaptiveHeightImpl(node, false);
}

void ResetAnimationCurveImpl(ArkUINodeHandle node)
{
    SetAnimationCurveImpl(node, 0, nullptr, nullptr);
}

void ResetNoMinHeightLimitImpl(ArkUINodeHandle node)
{
    SetNoMinHeightLimitImpl(node, false);
}

void ResetAnimationDurationImpl(ArkUINodeHandle node)
{
    SetAnimationDurationImpl(node, DEFAULT_ANIMATION_DURATION);
}

void SetTabClipImpl(ArkUINodeHandle node, ArkUI_Bool clipEdge)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetClipEdge(clipEdge);
}

void SetTabEdgeEffectImpl(ArkUINodeHandle node, ArkUI_Uint32 edgeEffect)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

void SetTabsNestedScrollImpl(ArkUINodeHandle node, ArkUI_Int32 (*values)[1])
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    CHECK_NULL_VOID(values);
    NestedScrollOptions nestedOpt = { .forward = static_cast<NestedScrollMode>((*values)[0]),
        .backward = static_cast<NestedScrollMode>((*values)[0]) };
    tabsModelImpl->SetNestedScroll(nestedOpt);
}

void ResetTabClipImpl(ArkUINodeHandle node)
{
    SetTabClipImpl(node, false);
}

void ResetTabEdgeEffectImpl(ArkUINodeHandle node)
{
    SetTabEdgeEffectImpl(node, NUM_0);
}

void ResetTabsNestedScrollImpl(ArkUINodeHandle node)
{
    ArkUI_Int32 values[1] = { NUM_0 };
    SetTabsNestedScrollImpl(node, &values);
}

void SetTabPageFlipModeImpl(ArkUINodeHandle node, ArkUI_Int32 pageFlipMode)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetPageFlipMode(pageFlipMode);
}

void ResetTabPageFlipModeImpl(ArkUINodeHandle node)
{
    SetTabPageFlipModeImpl(node, NUM_0);
}

void SetTabWidthAutoImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetWidthAuto(true);
}

void ResetTabWidthAutoImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetWidthAuto(false);
}

void SetTabHeightAutoImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetHeightAuto(true);
}

void ResetTabHeightAutoImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetHeightAuto(false);
}

void SetAnimateModeImpl(ArkUINodeHandle node, ArkUI_Uint32 mode)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetAnimateMode(static_cast<TabAnimateMode>(mode));
}

void ResetAnimateModeImpl(ArkUINodeHandle node)
{
    SetAnimateModeImpl(node, static_cast<ArkUI_Uint32>(TabAnimateMode::CONTENT_FIRST));
}

void SetBarBackgroundEffectImpl(ArkUINodeHandle node, ArkUITabBarBackgroundEffect* effectOption)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    CHECK_NULL_VOID(effectOption);
    EffectOption option;
    option.radius = CalcDimension(effectOption->radius, DimensionUnit::VP);
    option.saturation = effectOption->saturation;
    option.brightness = effectOption->brightness;
    option.color = Color(effectOption->color);
    option.adaptiveColor = static_cast<AdaptiveColor>(effectOption->adaptiveColor);
    option.blurOption.grayscale.assign(
        effectOption->blurValues, effectOption->blurValues + effectOption->blurValuesSize);
    option.blurType = static_cast<BlurType>(effectOption->blurType);
    option.policy = static_cast<BlurStyleActivePolicy>(effectOption->policy);
    option.inactiveColor = Color(effectOption->inactiveColor);
    option.isValidColor = effectOption->isValidColor;
    tabsModelImpl->SetBarBackgroundEffect(option);
}

void ResetBarBackgroundEffectImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    EffectOption effectOption;
    effectOption.radius.SetValue(0.0f);
    effectOption.saturation = 1.0f;
    effectOption.brightness = 1.0f;
    effectOption.color = Color::TRANSPARENT;
    effectOption.adaptiveColor = AdaptiveColor::DEFAULT;
    tabsModelImpl->SetBarBackgroundEffect(effectOption);
}

void CreateBarBackgroundEffectWithResourceObjImpl(ArkUINodeHandle node, void* colorRawPtr, void* inactiveColorRawPtr)
{
    (void)node;
    (void)colorRawPtr;
    (void)inactiveColorRawPtr;
}

void SetTabsOnSelectedImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        tabsModelImpl->SetOnSelected(std::move(*onEvent));
    } else {
        tabsModelImpl->SetOnSelected(nullptr);
    }
}

void SetCachedMaxCountImpl(ArkUINodeHandle node, ArkUI_Int32 count, ArkUI_Int32 mode)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    auto cacheMode = TabsCacheMode::CACHE_BOTH_SIDE;
    if (mode >= static_cast<int32_t>(TabsCacheMode::CACHE_BOTH_SIDE) &&
        mode <= static_cast<int32_t>(TabsCacheMode::CACHE_LATEST_SWITCHED)) {
        cacheMode = static_cast<TabsCacheMode>(mode);
    }
    tabsModelImpl->SetCachedMaxCount(count, cacheMode);
}

void ResetTabsOnSelectedImpl(ArkUINodeHandle node)
{
    SetTabsOnSelectedImpl(node, nullptr);
}

void ResetCachedMaxCountImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetCachedMaxCount(std::nullopt, TabsCacheMode::CACHE_BOTH_SIDE);
}

void SetTabsOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        tabsModelImpl->SetOnChange(std::move(*onChange));
    } else {
        tabsModelImpl->SetOnChange(nullptr);
    }
}

void SetTabsOnTabBarClickImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onTabBarClick = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        tabsModelImpl->SetOnTabBarClick(std::move(*onTabBarClick));
    } else {
        tabsModelImpl->SetOnTabBarClick(nullptr);
    }
}

void ResetTabsOnChangeImpl(ArkUINodeHandle node)
{
    SetTabsOnChangeImpl(node, nullptr);
}

void ResetTabsOnTabBarClickImpl(ArkUINodeHandle node)
{
    SetTabsOnTabBarClickImpl(node, nullptr);
}

void SetTabsOnAnimationStartImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onAnimationStart = reinterpret_cast<AnimationStartEvent*>(callback);
        tabsModelImpl->SetOnAnimationStart(std::move(*onAnimationStart));
    } else {
        tabsModelImpl->SetOnAnimationStart(nullptr);
    }
}

void SetTabsOnAnimationEndImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onAnimationEnd = reinterpret_cast<AnimationEndEvent*>(callback);
        tabsModelImpl->SetOnAnimationEnd(std::move(*onAnimationEnd));
    } else {
        tabsModelImpl->SetOnAnimationEnd(nullptr);
    }
}

void SetTabsOnGestureSwipeImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onGestureSwipe = reinterpret_cast<GestureSwipeEvent*>(callback);
        tabsModelImpl->SetOnGestureSwipe(std::move(*onGestureSwipe));
    } else {
        tabsModelImpl->SetOnGestureSwipe(nullptr);
    }
}

void ResetTabsOnAnimationStartImpl(ArkUINodeHandle node)
{
    SetTabsOnAnimationStartImpl(node, nullptr);
}

void ResetTabsOnAnimationEndImpl(ArkUINodeHandle node)
{
    SetTabsOnAnimationEndImpl(node, nullptr);
}

void ResetTabsOnGestureSwipeImpl(ArkUINodeHandle node)
{
    SetTabsOnGestureSwipeImpl(node, nullptr);
}

void SetTabsOnContentWillChangeImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto onContentWillChange = reinterpret_cast<std::function<bool(int32_t, int32_t)>*>(callback);
        tabsModelImpl->SetOnContentWillChange(std::move(*onContentWillChange));
    } else {
        tabsModelImpl->SetOnContentWillChange(nullptr);
    }
}

void SetTabsIsCustomAnimationImpl(ArkUINodeHandle node, ArkUI_Bool isCustom)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->SetIsCustomAnimation(isCustom);
}

void ResetTabsOnContentWillChangeImpl(ArkUINodeHandle node)
{
    SetTabsOnContentWillChangeImpl(node, nullptr);
}

void ResetTabsIsCustomAnimationImpl(ArkUINodeHandle node)
{
    SetTabsIsCustomAnimationImpl(node, false);
}

void SetTabsOnCustomAnimationImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    if (callback) {
        auto customAnimation = reinterpret_cast<TabsCustomAnimationEvent*>(callback);
        tabsModelImpl->SetOnCustomAnimation(std::move(*customAnimation));
    } else {
        tabsModelImpl->SetOnCustomAnimation(nullptr);
    }
}

void SetTabsBarFloatingStyleImpl(ArkUINodeHandle node, void* paramRawPtr)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    auto param = reinterpret_cast<BarFloatingStyleParameters*>(paramRawPtr);
    CHECK_NULL_VOID(param);
    tabsModelImpl->SetBarFloatingStyle(*param);
}

void ResetTabsBarFloatingStyleImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    tabsModelImpl->ResetBarFloatingStyle();
}

void CreateWithResourceObjImpl(ArkUINodeHandle node, void* paramRawPtr)
{
    (void)node;
    auto tabsModelImpl = GetTabsModelImpl();
    CHECK_NULL_VOID(tabsModelImpl);
    auto* param = reinterpret_cast<TabsResourceObjParam*>(paramRawPtr);
    CHECK_NULL_VOID(param);
    tabsModelImpl->CreateWithResourceObj(param->jsResourceType, AceType::Claim(param->resourceObj));
}
#endif

void CreateTabs(
    ArkUI_Int32 barPosition, ArkUI_Int32 index, ArkUINodeHandle tabsController, ArkUINodeHandle tabController)
{
    (void)tabController;
    TabsModelNG().Create(static_cast<BarPosition>(barPosition), index,
        AceType::Claim(reinterpret_cast<TabsControllerNG*>(tabsController)));
}

void PopTabs()
{
    TabsModelNG().Pop();
}

void SetTabBarMode(ArkUINodeHandle node, ArkUI_Int32 tabsBarMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<TabBarMode>(tabsBarMode);
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void SetScrollableBarModeOptions(ArkUINodeHandle node, const ArkUI_Float32 value,
    ArkUI_Int32 unit, ArkUI_Int32 layoutStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions option;
    CalcDimension margin = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    option.margin = margin;
    if (layoutStyle < static_cast<int32_t>(LayoutStyle::ALWAYS_CENTER) ||
        layoutStyle > static_cast<int32_t>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
        option.nonScrollableLayoutStyle = std::nullopt;
    } else {
        option.nonScrollableLayoutStyle = (static_cast<LayoutStyle>(layoutStyle));
    }
    TabsModelNG::SetScrollableBarModeOptions(frameNode, option);
}

void CreateScrollableBarModeOptionsWithResourceObj(ArkUINodeHandle node, void* marginRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* marginPtr = reinterpret_cast<ResourceObject*>(marginRawPtr);
    auto marginResObj = AceType::Claim(marginPtr);
    TabsModelNG::HandleScrollableBarMargin(frameNode, marginResObj, true);
}

void SetBarGridAlign(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesLength,
    const ArkUI_Int32* units, ArkUI_Int32 unitsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (unitsLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN || valuesLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN_VALUES) {
        return;
    }
    BarGridColumnOptions columnOption;
    columnOption.sm = units[NUM_2];
    columnOption.md = units[NUM_3];
    columnOption.lg = units[NUM_4];
    columnOption.gutter = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    columnOption.margin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));

    TabsModelNG::SetBarGridAlign(frameNode, columnOption);
}

void CreateBarGridAlignWithResourceObj(ArkUINodeHandle node, void* columnGutterRawPtr, void* columnMarginRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* columnGutterPtr = reinterpret_cast<ResourceObject*>(columnGutterRawPtr);
    auto columnGutterResObj = AceType::Claim(columnGutterPtr);
    auto* columnMarginPtr = reinterpret_cast<ResourceObject*>(columnMarginRawPtr);
    auto columnMarginResObj = AceType::Claim(columnMarginPtr);
    TabsModelNG::HandleBarGridGutter(frameNode, columnGutterResObj, true);
    TabsModelNG::HandleBarGridMargin(frameNode, columnMarginResObj, true);
}

void SetDivider(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_LENGTH) {
        return;
    }
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    divider.startMargin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    divider.endMargin = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    divider.color = Color(color);

    TabsModelNG::SetDivider(frameNode, divider);
}

void SetDividerColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetDividerColorByUser(frameNode, isByUser);
}

void CreateDividerWithResourceObj(ArkUINodeHandle node,
    void* strokeWidthRawPtr, void* colorRawPtr, void* startMarginRawPtr, void* endMarginRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* strokeWidthPtr = reinterpret_cast<ResourceObject*>(strokeWidthRawPtr);
    auto strokeWidthResObj = AceType::Claim(strokeWidthPtr);
    TabsModelNG::HandleDividerStrokeWidth(frameNode, strokeWidthResObj, true);
    auto* colorPtr = reinterpret_cast<ResourceObject*>(colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    TabsModelNG::HandleDividerColor(frameNode, colorResObj, true);
    auto* startMarginPtr = reinterpret_cast<ResourceObject*>(startMarginRawPtr);
    auto startMarginResObj = AceType::Claim(startMarginPtr);
    TabsModelNG::HandleDividerStartMargin(frameNode, startMarginResObj, true);
    auto* endMarginPtr = reinterpret_cast<ResourceObject*>(endMarginRawPtr);
    auto endMarginResObj = AceType::Claim(endMarginPtr);
    TabsModelNG::HandleDividerEndMargin(frameNode, endMarginResObj, true);
}

void SetFadingEdge(ArkUINodeHandle node, ArkUI_Bool fadingEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, fadingEdge);
}
void SetTabOnUnselected(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        TabsModelNG::SetOnUnselected(frameNode, std::move(*onEvent));
    } else {
        TabsModelNG::SetOnUnselected(frameNode, nullptr);
    }
}
void SetTabsOnContentDidScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onContentDidScroll = reinterpret_cast<std::function<void(int32_t, int32_t, float, float)>*>(callback);
        TabsModelNG::SetOnContentDidScroll(frameNode, std::move(*onContentDidScroll));
    } else {
        TabsModelNG::SetOnContentDidScroll(frameNode, nullptr);
    }
}
void SetBarBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color(color));
    TabsModelNG::SetBarBackgroundColorByUser(frameNode, true);
}

void SetBarBackgroundColorByUser(ArkUINodeHandle node, ArkUI_Bool colorByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColorByUser(frameNode, colorByUser);
}

void CreateBarBackgroundColorWithResourceObj(ArkUINodeHandle node, void* bgColorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* bgColorPtr = reinterpret_cast<ResourceObject*>(bgColorRawPtr);
    auto bgColorResObj = AceType::Claim(bgColorPtr);
    TabsModelNG::HandleBarBackgroundColor(frameNode, bgColorResObj, true);
}

void SetBarBackgroundBlurStyle(ArkUINodeHandle node, ArkUITabBarBackgroundBlurStyle* styleOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(styleOption);
    ArkUI_Int32 blurStyle = styleOption->blurStyle;
    ArkUI_Int32 colorMode = styleOption->colorMode;
    ArkUI_Int32 adaptiveColor = styleOption->adaptiveColor;
    ArkUI_Int32 policy = styleOption->policy;
    ArkUI_Int32 blurType = styleOption->blurType;
    BlurStyleOption bgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            bgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((styleOption->colorMode < 0) && (styleOption->adaptiveColor < 0) &&
        (styleOption->scale < 0) && (styleOption->blurValuesSize == 0));
    if (isHasOptions) {
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            bgBlurStyle.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            bgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        bgBlurStyle.scale = std::clamp(styleOption->scale, 0.0f, 1.0f);
        BlurOption blurOption;
        blurOption.grayscale.assign(styleOption->blurValues, styleOption->blurValues + styleOption->blurValuesSize);
        bgBlurStyle.blurOption = blurOption;
    }
    bgBlurStyle.policy = static_cast<BlurStyleActivePolicy>(policy);
    bgBlurStyle.blurType = static_cast<BlurType>(blurType);
    bgBlurStyle.isValidColor = styleOption->isValidColor;
    Color inactiveColor(styleOption->inactiveColor);
    bgBlurStyle.inactiveColor = inactiveColor;
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, bgBlurStyle);
}

void CreateBarBackgroundBlurStyleWithResourceObj(ArkUINodeHandle node, void* inactiveColorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* inactiveColorPtr = reinterpret_cast<ResourceObject*>(inactiveColorRawPtr);
    auto inactiveColorResObj = AceType::Claim(inactiveColorPtr);
    TabsModelNG::HandleBackgroundBlurStyleInactiveColor(frameNode, inactiveColorResObj, true);
}

void SetBarOverlap(ArkUINodeHandle node, ArkUI_Bool barOverlap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, barOverlap);
}
void SetIsVertical(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, isVertical);
}
void SetTabBarPosition(ArkUINodeHandle node, ArkUI_Int32 barVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, static_cast<BarPosition>(barVal));
}
void SetTabsOptionsIndex(ArkUINodeHandle node, ArkUI_Int32 indexVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarIndex(frameNode, indexVal < 0 ? 0 : indexVal);
}
void SetTabsOptionsController(ArkUINodeHandle node, ArkUINodeHandle tabsController)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabsController(frameNode,
        AceType::Claim(reinterpret_cast<OHOS::Ace::SwiperController*>(tabsController)));
}
void SetTabsOptionsBarModifier(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onApply = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(callback);
        TabsModelNG::SetBarModifier(frameNode, std::move(*onApply));
    } else {
        TabsModelNG::SetBarModifier(frameNode, nullptr);
    }
}
void SetScrollable(ArkUINodeHandle node, ArkUI_Bool scrollable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, scrollable);
}
void SetBarAdaptiveHeight(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, value);
}
void SetNoMinHeightLimit(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetNoMinHeightLimit(frameNode, value);
}
void SetTabBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarWidth(frameNode, width);
}

void CreateTabBarWidthWithResourceObj(ArkUINodeHandle node, void* widthRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* widthPtr = reinterpret_cast<ResourceObject*>(widthRawPtr);
    auto widthResObj = AceType::Claim(widthPtr);
    TabsModelNG::HandleBarWidth(frameNode, widthResObj, true);
}

void SetTabBarHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarHeight(frameNode, width);
}

void CreateTabBarHeightWithResourceObj(ArkUINodeHandle node, void* heightRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* heightPtr = reinterpret_cast<ResourceObject*>(heightRawPtr);
    auto heightResObj = AceType::Claim(heightPtr);
    TabsModelNG::HandleBarHeight(frameNode, heightResObj, true);
}

void SetAnimationCurve(ArkUINodeHandle node, ArkUI_Uint32 type, ArkUI_CharPtr curveChar, void* curveCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve;
    if (type == ANIMATION_CURVE_TYPE_STR && curveChar != nullptr) {
        curve = Framework::CreateCurve(curveChar, false);
    } else if (type == ANIMATION_CURVE_TYPE_FUNC && curveCallback != nullptr) {
        auto callback = reinterpret_cast<std::function<float(float)>*>(curveCallback);
        curve = Framework::CreateCurve(*callback);
    }
    TabsModelNG::SetAnimationCurve(frameNode, curve);
}

void SetAnimationDuration(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (std::isnan(duration)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        TabsModelNG::SetAnimationDuration(frameNode,
            static_cast<ArkUI_Float32>(tabTheme->GetTabContentAnimationDuration()));
        return;
    }
    TabsModelNG::SetAnimationDuration(frameNode, duration);
}
void ResetTabBarMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabBarMode barMode = TabBarMode::FIXED;
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void ResetScrollableBarModeOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions defaultOption;
    CalcDimension margin = Dimension(0.0, DimensionUnit::VP);
    defaultOption.margin = margin;
    defaultOption.nonScrollableLayoutStyle = std::nullopt;
    TabsModelNG::SetScrollableBarModeOptions(frameNode, defaultOption);

    CreateScrollableBarModeOptionsWithResourceObj(node, nullptr);
}
void ResetBarGridAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BarGridColumnOptions columnOption;
    TabsModelNG::SetBarGridAlign(frameNode, columnOption);

    CreateBarGridAlignWithResourceObj(node, nullptr, nullptr);
}
void ResetDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    TabsItemDivider divider;
    divider.isNull = true;

    TabsModelNG::SetDivider(frameNode, divider);
    TabsModelNG::SetDividerColorByUser(frameNode, false);

    CreateDividerWithResourceObj(node, nullptr, nullptr, nullptr, nullptr);
}
void ResetFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, true);
}
void ResetTabOnUnselected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnUnselected(frameNode, nullptr);
}
void ResetTabsOnContentDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnContentDidScroll(frameNode, nullptr);
}
void ResetBarBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color::BLACK.BlendOpacity(0.0f));
    TabsModelNG::SetBarBackgroundColorByUser(frameNode, false);

    CreateBarBackgroundColorWithResourceObj(node, nullptr);
}
void ResetBarBackgroundBlurStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption bgBlurStyle;
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, bgBlurStyle);

    CreateBarBackgroundBlurStyleWithResourceObj(node, nullptr);
}
void ResetBarOverlap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, false);
}
void ResetIsVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, false);
}

void ResetTabBarPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, BarPosition::START);
}

void ResetTabsOptionsIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarIndex(frameNode, 0);
}

void ResetTabsOptionsBarModifier(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarModifier(frameNode, nullptr);
}

void ResetScrollable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, true);
}
void ResetTabBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarWidth(frameNode, width);

    CreateTabBarWidthWithResourceObj(node, nullptr);
}
void ResetTabBarHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarHeight(frameNode, width);

    CreateTabBarHeightWithResourceObj(node, nullptr);
}

void ResetAnimationCurve(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve;
    TabsModelNG::SetAnimationCurve(frameNode, curve);
}

void ResetAnimationDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimationDuration(frameNode, DEFAULT_ANIMATION_DURATION);
}

void ResetBarAdaptiveHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, false);
}

void ResetNoMinHeightLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetNoMinHeightLimit(frameNode, false);
}

void SetTabClip(ArkUINodeHandle node, ArkUI_Bool clipEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, clipEdge);
}

void ResetTabClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, false);
}

void SetTabEdgeEffect(ArkUINodeHandle node, ArkUI_Uint32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetEdgeEffect(frameNode, edgeEffect);
}

void ResetTabEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetEdgeEffect(frameNode, NUM_0);
}

void SetTabsNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[1])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetNestedScroll(frameNode, (*values)[0]);
}

void ResetTabsNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetNestedScroll(frameNode, NUM_0);
}

void SetTabPageFlipMode(ArkUINodeHandle node, ArkUI_Int32 pageFlipMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetPageFlipMode(frameNode, pageFlipMode);
}

void ResetTabPageFlipMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetPageFlipMode(frameNode, NUM_0);
}

void SetTabWidthAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
    TabsModelNG::SetWidthAuto(frameNode, true);
}

void ResetTabWidthAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetWidthAuto(frameNode, false);
}

void SetTabHeightAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
    TabsModelNG::SetHeightAuto(frameNode, true);
}

void ResetTabHeightAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetHeightAuto(frameNode, false);
}

void SetAnimateMode(ArkUINodeHandle node, ArkUI_Uint32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimateMode(frameNode, static_cast<TabAnimateMode>(mode));
}

void ResetAnimateMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimateMode(frameNode, TabAnimateMode::CONTENT_FIRST);
}

void SetBarBackgroundEffect(ArkUINodeHandle node, ArkUITabBarBackgroundEffect* effectOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        radius = CalcDimension(effectOption->radius, DimensionUnit::VP);
    } else {
        radius = CalcDimension(effectOption->radius, DimensionUnit::PX);
    }
    Color color(effectOption->color);
    BlurOption blurOption;
    blurOption.grayscale.assign(effectOption->blurValues, effectOption->blurValues + effectOption->blurValuesSize);

    EffectOption option;
    option.radius = radius;
    option.saturation = effectOption->saturation;
    option.brightness = effectOption->brightness;
    option.color = color;
    option.adaptiveColor = static_cast<AdaptiveColor>(effectOption->adaptiveColor);
    option.blurOption = blurOption;
    option.blurType = static_cast<BlurType>(effectOption->blurType);
    option.policy = static_cast<BlurStyleActivePolicy>(effectOption->policy);
    Color inactiveColor(effectOption->inactiveColor);
    option.inactiveColor = inactiveColor;
    option.isValidColor = effectOption->isValidColor;
    TabsModelNG::SetBarBackgroundEffect(frameNode, option);
}

void CreateBarBackgroundEffectWithResourceObj(ArkUINodeHandle node, void* colorRawPtr, void* inactiveColorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* colorPtr = reinterpret_cast<ResourceObject*>(colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    TabsModelNG::HandleBackgroundEffectColor(frameNode, colorResObj, true);
    auto* inactiveColorPtr = reinterpret_cast<ResourceObject*>(inactiveColorRawPtr);
    auto inactiveColorResObj = AceType::Claim(inactiveColorPtr);
    TabsModelNG::HandleBackgroundEffectInactiveColor(frameNode, inactiveColorResObj, true);
}

void ResetBarBackgroundEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    radius.SetValue(0.0f);
    double saturation = 1.0f;
    double brightness = 1.0f;
    Color color = Color::TRANSPARENT;
    color.SetValue(Color::TRANSPARENT.GetValue());
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    BlurOption blurOption;
    EffectOption effectOption = { radius, saturation, brightness, color, adaptiveColor, blurOption };
    TabsModelNG::SetBarBackgroundEffect(frameNode, effectOption);

    CreateBarBackgroundEffectWithResourceObj(node, nullptr, nullptr);
}

void SetTabsOnSelected(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        TabsModelNG::SetOnSelected(frameNode, std::move(*onEvent));
    } else {
        TabsModelNG::SetOnSelected(frameNode, nullptr);
    }
}

void ResetTabsOnSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnSelected(frameNode, nullptr);
}

void SetCachedMaxCount(ArkUINodeHandle node, ArkUI_Int32 count, ArkUI_Int32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto cacheMode = TabsCacheMode::CACHE_BOTH_SIDE;
    if (mode >= static_cast<int32_t>(TabsCacheMode::CACHE_BOTH_SIDE) &&
        mode <= static_cast<int32_t>(TabsCacheMode::CACHE_LATEST_SWITCHED)) {
        cacheMode = static_cast<TabsCacheMode>(mode);
    }
    TabsModelNG::SetCachedMaxCount(frameNode, count, cacheMode);
}

void ResetCachedMaxCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetCachedMaxCount(frameNode, std::nullopt, TabsCacheMode::CACHE_BOTH_SIDE);
}
void SetTabsOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        TabsModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        TabsModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetTabsOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnChange(frameNode, nullptr);
}

void SetTabsOnTabBarClick(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onTabBarClick = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        TabsModelNG::SetOnTabBarClick(frameNode, std::move(*onTabBarClick));
    } else {
        TabsModelNG::SetOnTabBarClick(frameNode, nullptr);
    }
}

void ResetTabsOnTabBarClick(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnTabBarClick(frameNode, nullptr);
}

void SetTabsOnAnimationStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onAnimationStart =
            reinterpret_cast<std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)>*>(callback);
        TabsModelNG::SetOnAnimationStart(frameNode, std::move(*onAnimationStart));
    } else {
        TabsModelNG::SetOnAnimationStart(frameNode, nullptr);
    }
}

void ResetTabsOnAnimationStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnAnimationStart(frameNode, nullptr);
}

void SetTabsOnAnimationEnd(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onAnimationEnd = reinterpret_cast<std::function<void(int32_t, const AnimationCallbackInfo&)>*>(callback);
        TabsModelNG::SetOnAnimationEnd(frameNode, std::move(*onAnimationEnd));
    } else {
        TabsModelNG::SetOnAnimationEnd(frameNode, nullptr);
    }
}

void ResetTabsOnAnimationEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnAnimationEnd(frameNode, nullptr);
}

void SetTabsOnGestureSwipe(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onGestureSwipe = reinterpret_cast<std::function<void(int32_t, const AnimationCallbackInfo&)>*>(callback);
        TabsModelNG::SetOnGestureSwipe(frameNode, std::move(*onGestureSwipe));
    } else {
        TabsModelNG::SetOnGestureSwipe(frameNode, nullptr);
    }
}

void ResetTabsOnGestureSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnGestureSwipe(frameNode, nullptr);
}

void SetTabsOnContentWillChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onContentWillChange = reinterpret_cast<std::function<bool(int32_t, int32_t)>*>(callback);
        TabsModelNG::SetOnContentWillChange(frameNode, std::move(*onContentWillChange));
    } else {
        TabsModelNG::SetOnContentWillChange(frameNode, nullptr);
    }
}

void ResetTabsOnContentWillChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetOnContentWillChange(frameNode, nullptr);
}

void SetTabsIsCustomAnimation(ArkUINodeHandle node, ArkUI_Bool isCustom)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsCustomAnimation(frameNode, isCustom);
}

void ResetTabsIsCustomAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsCustomAnimation(frameNode, false);
}

void SetTabsOnCustomAnimation(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto customAnimation = reinterpret_cast<TabsCustomAnimationEvent*>(callback);
        TabsModelNG::SetOnCustomAnimation(frameNode, std::move(*customAnimation));
    } else {
        TabsModelNG::SetOnCustomAnimation(frameNode, nullptr);
    }
}

void SetTabsBarFloatingStyle(ArkUINodeHandle node, void* paramRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto param = reinterpret_cast<BarFloatingStyleParameters*>(paramRawPtr);
    TabsModelNG::SetBarFloatingStyle(frameNode, *param);
}

void ResetTabsBarFloatingStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::ResetBarFloatingStyle(frameNode);
}

void CreateWithResourceObj(ArkUINodeHandle node, void* paramRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* param = reinterpret_cast<TabsResourceObjParam*>(paramRawPtr);
    CHECK_NULL_VOID(param);
    auto resObj = AceType::Claim(param->resourceObj);
    TabsModelNG::CreateWithResourceObj(frameNode, param->jsResourceType, resObj);
}

namespace NodeModifier {
const ArkUITabsModifier* GetTabsModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUITabsModifier modifier = {
            .createTabs = CreateTabs,
            .popTabs = PopTabs,
            .setTabBarMode = SetTabBarMode,
            .setScrollableBarModeOptions = SetScrollableBarModeOptions,
            .setBarGridAlign = SetBarGridAlign,
            .setDivider = SetDivider,
            .setDividerColorByUser = SetDividerColorByUser,
            .setFadingEdge = SetFadingEdge,
            .setTabOnUnselected = SetTabOnUnselected,
            .setTabsOnContentDidScroll = SetTabsOnContentDidScroll,
            .setBarBackgroundColor = SetBarBackgroundColor,
            .setBarBackgroundColorByUser = SetBarBackgroundColorByUser,
            .setBarBackgroundBlurStyle = SetBarBackgroundBlurStyle,
            .setBarOverlap = SetBarOverlap,
            .setIsVertical = SetIsVertical,
            .setTabBarPosition = SetTabBarPosition,
            .setTabsOptionsIndex = SetTabsOptionsIndex,
            .setTabsOptionsController = SetTabsOptionsController,
            .setTabsOptionsBarModifier = SetTabsOptionsBarModifier,
            .setScrollable = SetScrollable,
            .setTabBarWidth = SetTabBarWidth,
            .setTabBarHeight = SetTabBarHeight,
            .setBarAdaptiveHeight = SetBarAdaptiveHeight,
            .setAnimationCurve = SetAnimationCurve,
            .setNoMinHeightLimit = SetNoMinHeightLimit,
            .setAnimationDuration = SetAnimationDuration,
            .resetTabBarMode = ResetTabBarMode,
            .resetScrollableBarModeOptions = ResetScrollableBarModeOptions,
            .resetBarGridAlign = ResetBarGridAlign,
            .resetDivider = ResetDivider,
            .resetFadingEdge = ResetFadingEdge,
            .resetTabOnUnselected = ResetTabOnUnselected,
            .resetTabsOnContentDidScroll = ResetTabsOnContentDidScroll,
            .resetBarBackgroundColor = ResetBarBackgroundColor,
            .resetBarBackgroundBlurStyle = ResetBarBackgroundBlurStyle,
            .resetBarOverlap = ResetBarOverlap,
            .resetIsVertical = ResetIsVertical,
            .resetTabBarPosition = ResetTabBarPosition,
            .resetTabsOptionsIndex = ResetTabsOptionsIndex,
            .resetTabsOptionsBarModifier = ResetTabsOptionsBarModifier,
            .resetScrollable = ResetScrollable,
            .resetTabBarWidth = ResetTabBarWidth,
            .resetTabBarHeight = ResetTabBarHeight,
            .resetBarAdaptiveHeight = ResetBarAdaptiveHeight,
            .resetAnimationCurve = ResetAnimationCurve,
            .resetNoMinHeightLimit = ResetNoMinHeightLimit,
            .resetAnimationDuration = ResetAnimationDuration,
            .setTabClip = SetTabClip,
            .resetTabClip = ResetTabClip,
            .setTabEdgeEffect = SetTabEdgeEffect,
            .resetTabEdgeEffect = ResetTabEdgeEffect,
            .setTabsNestedScroll = SetTabsNestedScroll,
            .resetTabsNestedScroll = ResetTabsNestedScroll,
            .setTabPageFlipMode = SetTabPageFlipMode,
            .resetTabPageFlipMode = ResetTabPageFlipMode,
            .setTabWidthAuto = SetTabWidthAuto,
            .resetTabWidthAuto = ResetTabWidthAuto,
            .setTabHeightAuto = SetTabHeightAuto,
            .resetTabHeightAuto = ResetTabHeightAuto,
            .setAnimateMode = SetAnimateMode,
            .resetAnimateMode = ResetAnimateMode,
            .setBarBackgroundEffect = SetBarBackgroundEffect,
            .resetBarBackgroundEffect = ResetBarBackgroundEffect,
            .setTabsOnSelected = SetTabsOnSelected,
            .resetTabsOnSelected = ResetTabsOnSelected,
            .setCachedMaxCount = SetCachedMaxCount,
            .resetCachedMaxCount = ResetCachedMaxCount,
            .setTabsOnChange = SetTabsOnChange,
            .resetTabsOnChange = ResetTabsOnChange,
            .setTabsOnTabBarClick = SetTabsOnTabBarClick,
            .resetTabsOnTabBarClick = ResetTabsOnTabBarClick,
            .setTabsOnAnimationStart = SetTabsOnAnimationStart,
            .resetTabsOnAnimationStart = ResetTabsOnAnimationStart,
            .setTabsOnAnimationEnd = SetTabsOnAnimationEnd,
            .resetTabsOnAnimationEnd = ResetTabsOnAnimationEnd,
            .setTabsOnGestureSwipe = SetTabsOnGestureSwipe,
            .resetTabsOnGestureSwipe = ResetTabsOnGestureSwipe,
            .setTabsOnContentWillChange = SetTabsOnContentWillChange,
            .resetTabsOnContentWillChange = ResetTabsOnContentWillChange,
            .setTabsIsCustomAnimation = SetTabsIsCustomAnimation,
            .resetTabsIsCustomAnimation = ResetTabsIsCustomAnimation,
            .setTabsOnCustomAnimation = SetTabsOnCustomAnimation,
            .createScrollableBarModeOptionsWithResourceObj = CreateScrollableBarModeOptionsWithResourceObj,
            .createBarGridAlignWithResourceObj = CreateBarGridAlignWithResourceObj,
            .createDividerWithResourceObj = CreateDividerWithResourceObj,
            .createBarBackgroundColorWithResourceObj = CreateBarBackgroundColorWithResourceObj,
            .createBarBackgroundBlurStyleWithResourceObj = CreateBarBackgroundBlurStyleWithResourceObj,
            .createTabBarWidthWithResourceObj = CreateTabBarWidthWithResourceObj,
            .createTabBarHeightWithResourceObj = CreateTabBarHeightWithResourceObj,
            .createBarBackgroundEffectWithResourceObj = CreateBarBackgroundEffectWithResourceObj,
            .setTabsBarFloatingStyle = SetTabsBarFloatingStyle,
            .resetTabsBarFloatingStyle = ResetTabsBarFloatingStyle,
            .createWithResourceObj = CreateWithResourceObj,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#ifndef CROSS_PLATFORM
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabsModifier modifier = {
        .createTabs = CreateTabsImpl,
        .popTabs = PopTabsImpl,
        .setTabBarMode = SetTabBarModeImpl,
        .setScrollableBarModeOptions = SetScrollableBarModeOptionsImpl,
        .setBarGridAlign = SetBarGridAlignImpl,
        .setDivider = SetDividerImpl,
        .setDividerColorByUser = SetDividerColorByUserImpl,
        .setFadingEdge = SetFadingEdgeImpl,
        .setTabOnUnselected = SetTabOnUnselectedImpl,
        .setTabsOnContentDidScroll = SetTabsOnContentDidScrollImpl,
        .setBarBackgroundColor = SetBarBackgroundColorImpl,
        .setBarBackgroundColorByUser = SetBarBackgroundColorByUserImpl,
        .setBarBackgroundBlurStyle = SetBarBackgroundBlurStyleImpl,
        .setBarOverlap = SetBarOverlapImpl,
        .setIsVertical = SetIsVerticalImpl,
        .setTabBarPosition = SetTabBarPositionImpl,
        .setTabsOptionsIndex = SetTabsOptionsIndexImpl,
        .setTabsOptionsController = SetTabsOptionsControllerImpl,
        .setTabsOptionsBarModifier = SetTabsOptionsBarModifierImpl,
        .setScrollable = SetScrollableImpl,
        .setTabBarWidth = SetTabBarWidthImpl,
        .setTabBarHeight = SetTabBarHeightImpl,
        .setBarAdaptiveHeight = SetBarAdaptiveHeightImpl,
        .setAnimationCurve = SetAnimationCurveImpl,
        .setNoMinHeightLimit = SetNoMinHeightLimitImpl,
        .setAnimationDuration = SetAnimationDurationImpl,
        .resetTabBarMode = ResetTabBarModeImpl,
        .resetScrollableBarModeOptions = ResetScrollableBarModeOptionsImpl,
        .resetBarGridAlign = ResetBarGridAlignImpl,
        .resetDivider = ResetDividerImpl,
        .resetFadingEdge = ResetFadingEdgeImpl,
        .resetTabOnUnselected = ResetTabOnUnselectedImpl,
        .resetTabsOnContentDidScroll = ResetTabsOnContentDidScrollImpl,
        .resetBarBackgroundColor = ResetBarBackgroundColorImpl,
        .resetBarBackgroundBlurStyle = ResetBarBackgroundBlurStyleImpl,
        .resetBarOverlap = ResetBarOverlapImpl,
        .resetIsVertical = ResetIsVerticalImpl,
        .resetTabBarPosition = ResetTabBarPositionImpl,
        .resetTabsOptionsIndex = ResetTabsOptionsIndexImpl,
        .resetTabsOptionsBarModifier = ResetTabsOptionsBarModifierImpl,
        .resetScrollable = ResetScrollableImpl,
        .resetTabBarWidth = ResetTabBarWidthImpl,
        .resetTabBarHeight = ResetTabBarHeightImpl,
        .resetBarAdaptiveHeight = ResetBarAdaptiveHeightImpl,
        .resetAnimationCurve = ResetAnimationCurveImpl,
        .resetNoMinHeightLimit = ResetNoMinHeightLimitImpl,
        .resetAnimationDuration = ResetAnimationDurationImpl,
        .setTabClip = SetTabClipImpl,
        .resetTabClip = ResetTabClipImpl,
        .setTabEdgeEffect = SetTabEdgeEffectImpl,
        .resetTabEdgeEffect = ResetTabEdgeEffectImpl,
        .setTabsNestedScroll = SetTabsNestedScrollImpl,
        .resetTabsNestedScroll = ResetTabsNestedScrollImpl,
        .setTabPageFlipMode = SetTabPageFlipModeImpl,
        .resetTabPageFlipMode = ResetTabPageFlipModeImpl,
        .setTabWidthAuto = SetTabWidthAutoImpl,
        .resetTabWidthAuto = ResetTabWidthAutoImpl,
        .setTabHeightAuto = SetTabHeightAutoImpl,
        .resetTabHeightAuto = ResetTabHeightAutoImpl,
        .setAnimateMode = SetAnimateModeImpl,
        .resetAnimateMode = ResetAnimateModeImpl,
        .setBarBackgroundEffect = SetBarBackgroundEffectImpl,
        .resetBarBackgroundEffect = ResetBarBackgroundEffectImpl,
        .setTabsOnSelected = SetTabsOnSelectedImpl,
        .resetTabsOnSelected = ResetTabsOnSelectedImpl,
        .setCachedMaxCount = SetCachedMaxCountImpl,
        .resetCachedMaxCount = ResetCachedMaxCountImpl,
        .setTabsOnChange = SetTabsOnChangeImpl,
        .resetTabsOnChange = ResetTabsOnChangeImpl,
        .setTabsOnTabBarClick = SetTabsOnTabBarClickImpl,
        .resetTabsOnTabBarClick = ResetTabsOnTabBarClickImpl,
        .setTabsOnAnimationStart = SetTabsOnAnimationStartImpl,
        .resetTabsOnAnimationStart = ResetTabsOnAnimationStartImpl,
        .setTabsOnAnimationEnd = SetTabsOnAnimationEndImpl,
        .resetTabsOnAnimationEnd = ResetTabsOnAnimationEndImpl,
        .setTabsOnGestureSwipe = SetTabsOnGestureSwipeImpl,
        .resetTabsOnGestureSwipe = ResetTabsOnGestureSwipeImpl,
        .setTabsOnContentWillChange = SetTabsOnContentWillChangeImpl,
        .resetTabsOnContentWillChange = ResetTabsOnContentWillChangeImpl,
        .setTabsIsCustomAnimation = SetTabsIsCustomAnimationImpl,
        .resetTabsIsCustomAnimation = ResetTabsIsCustomAnimationImpl,
        .setTabsOnCustomAnimation = SetTabsOnCustomAnimationImpl,
        .createScrollableBarModeOptionsWithResourceObj = CreateScrollableBarModeOptionsWithResourceObjImpl,
        .createBarGridAlignWithResourceObj = CreateBarGridAlignWithResourceObjImpl,
        .createDividerWithResourceObj = CreateDividerWithResourceObjImpl,
        .createBarBackgroundColorWithResourceObj = CreateBarBackgroundColorWithResourceObjImpl,
        .createBarBackgroundBlurStyleWithResourceObj = CreateBarBackgroundBlurStyleWithResourceObjImpl,
        .createTabBarWidthWithResourceObj = CreateTabBarWidthWithResourceObjImpl,
        .createTabBarHeightWithResourceObj = CreateTabBarHeightWithResourceObjImpl,
        .createBarBackgroundEffectWithResourceObj = CreateBarBackgroundEffectWithResourceObjImpl,
        .setTabsBarFloatingStyle = SetTabsBarFloatingStyleImpl,
        .resetTabsBarFloatingStyle = ResetTabsBarFloatingStyleImpl,
        .createWithResourceObj = CreateWithResourceObjImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
#else
    return nullptr;
#endif
}

const CJUITabsModifier* GetCJUITabsModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITabsModifier modifier = {
        .setTabBarMode = SetTabBarMode,
        .setScrollableBarModeOptions = SetScrollableBarModeOptions,
        .setBarGridAlign = SetBarGridAlign,
        .setDivider = SetDivider,
        .setFadingEdge = SetFadingEdge,
        .setBarBackgroundColor = SetBarBackgroundColor,
        .setBarBackgroundBlurStyle = SetBarBackgroundBlurStyle,
        .setBarOverlap = SetBarOverlap,
        .setIsVertical = SetIsVertical,
        .setTabBarPosition = SetTabBarPosition,
        .setTabsOptionsIndex = SetTabsOptionsIndex,
        .setTabsOptionsController = SetTabsOptionsController,
        .setTabsOptionsBarModifier = SetTabsOptionsBarModifier,
        .setScrollable = SetScrollable,
        .setTabBarWidth = SetTabBarWidth,
        .setTabBarHeight = SetTabBarHeight,
        .setBarAdaptiveHeight = SetBarAdaptiveHeight,
        .setAnimationDuration = SetAnimationDuration,
        .resetTabBarMode = ResetTabBarMode,
        .resetScrollableBarModeOptions = ResetScrollableBarModeOptions,
        .resetBarGridAlign = ResetBarGridAlign,
        .resetDivider = ResetDivider,
        .resetFadingEdge = ResetFadingEdge,
        .resetBarBackgroundColor = ResetBarBackgroundColor,
        .resetBarBackgroundBlurStyle = ResetBarBackgroundBlurStyle,
        .resetBarOverlap = ResetBarOverlap,
        .resetIsVertical = ResetIsVertical,
        .resetTabBarPosition = ResetTabBarPosition,
        .resetTabsOptionsIndex = ResetTabsOptionsIndex,
        .resetTabsOptionsBarModifier = ResetTabsOptionsBarModifier,
        .resetScrollable = ResetScrollable,
        .resetTabBarWidth = ResetTabBarWidth,
        .resetTabBarHeight = ResetTabBarHeight,
        .resetBarAdaptiveHeight = ResetBarAdaptiveHeight,
        .resetAnimationDuration = ResetAnimationDuration,
        .setTabClip = SetTabClip,
        .resetTabClip = ResetTabClip,
        .setTabEdgeEffect = SetTabEdgeEffect,
        .resetTabEdgeEffect = ResetTabEdgeEffect,
        .setTabWidthAuto = SetTabWidthAuto,
        .resetTabWidthAuto = ResetTabWidthAuto,
        .setTabHeightAuto = SetTabHeightAuto,
        .resetTabHeightAuto = ResetTabHeightAuto,
        .setAnimateMode = SetAnimateMode,
        .resetAnimateMode = ResetAnimateMode,
        .setBarBackgroundEffect = SetBarBackgroundEffect,
        .resetBarBackgroundEffect = ResetBarBackgroundEffect,
        .setTabsOnSelected = SetTabsOnSelected,
        .resetTabsOnSelected = ResetTabsOnSelected,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

}
} // namespace OHOS::Ace::NG

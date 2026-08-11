/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabcontent_bridge.h"
#include "ui/base/utils/utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/swiper/bridge/arkts_native_swiper_bridge.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_model_static.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/sub_tab_bar_style_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "base/image/image_defines.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "base/log/ace_scoring_log.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
#ifdef PIXEL_MAP_SUPPORTED
constexpr char DRAWABLE_DESCRIPTOR_NAME[] = "DrawableDescriptor";
constexpr char LAYERED_DRAWABLE_DESCRIPTOR_NAME[] = "LayeredDrawableDescriptor";
constexpr char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[] = "AnimatedDrawableDescriptor";
constexpr char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[] = "PixelMapDrawableDescriptor";
#endif
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICIES = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

void PopTabContentBridge()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSTabContent][pop]", &PopTabContentBridge);
    }
    GetArkUINodeModifiers()->getTabContentModifier()->popTabContent();
}

ArkUINodeHandle GetCurrentTabContentNode()
{
    return reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

void ApplyCreateWithResourceObj(TabContentJsType type, const RefPtr<ResourceObject>& resourceObj)
{
    TabContentResourceObjParam param { type, AceType::RawPtr(resourceObj) };
    GetArkUINodeModifiers()->getTabContentModifier()->createWithResourceObj(GetCurrentTabContentNode(), &param);
}

void ApplyCreatePaddingHorWithResourceObj(const RefPtr<ResourceObject>& resObjLeft,
    const RefPtr<ResourceObject>& resObjRight, bool isSubTabStyle, bool useLocalizedPadding)
{
    TabContentPaddingResourceObjParam param {
        AceType::RawPtr(resObjLeft), AceType::RawPtr(resObjRight), isSubTabStyle, useLocalizedPadding
    };
    GetArkUINodeModifiers()->getTabContentModifier()->createPaddingHorWithResourceObj(
        GetCurrentTabContentNode(), &param);
}

void ApplyCreatePaddingVerWithResourceObj(const RefPtr<ResourceObject>& resObjTop,
    const RefPtr<ResourceObject>& resObjBottom, bool isSubTabStyle, bool useLocalizedPadding)
{
    TabContentPaddingResourceObjParam param { AceType::RawPtr(resObjTop), AceType::RawPtr(resObjBottom), isSubTabStyle,
        useLocalizedPadding };
    GetArkUINodeModifiers()->getTabContentModifier()->createPaddingVerWithResourceObj(
        GetCurrentTabContentNode(), &param);
}

void ApplySetTabBar(TabBarStyle style, const std::optional<std::string>& text,
    const std::optional<std::string>& icon, const std::optional<TabBarSymbol>& tabBarSymbol,
    std::function<void()>* builder, FrameNode* content, bool fromJsView)
{
    TabContentTabBarParam param { style, text, icon, tabBarSymbol, builder, content };
    GetArkUINodeModifiers()->getTabContentModifier()->setTabBar(GetCurrentTabContentNode(), &param, fromJsView);
}

void SetTabBarSymbolOptionApply(EcmaVM* vm, TabBarSymbol& symbolApply,
    const Local<JSValueRef>& modifierNormalObj, const Local<JSValueRef>& modifierSelectedObj)
{
    auto globalObj = panda::JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applySymbolGlyphModifierToNode"));
    if (!globalFunc->IsFunction(vm)) {
        return;
    }
    if (modifierNormalObj->IsUndefined()) {
        symbolApply.onApply = nullptr;
        return;
    }
    panda::Local<panda::FunctionRef> func = globalFunc->ToObject(vm);
    auto onApply = [func = panda::CopyableGlobal(vm, func),
                       modifierNormal = panda::CopyableGlobal(vm, modifierNormalObj),
                       modifierSelected = panda::CopyableGlobal(vm, modifierSelectedObj)](
                       WeakPtr<NG::FrameNode> frameNode, std::string type) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        Local<JSValueRef> params[NUM_2];
        params[NUM_0] = JSValueRef::Undefined(vm);
        if (type == "normal") {
            params[NUM_0] = modifierNormal.ToLocal();
        } else if (!modifierSelected.ToLocal()->IsUndefined()) {
            params[NUM_0] = modifierSelected.ToLocal();
        }
        params[NUM_1] = panda::NativePointerRef::New(vm, AceType::RawPtr(node));
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), params, NUM_2);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    symbolApply.onApply = onApply;
}

#ifdef PIXEL_MAP_SUPPORTED
ImageType ParseImageType(EcmaVM* vm, const Local<JSValueRef>& imageInfo)
{
    if (!imageInfo->IsObject(vm)) {
        return ImageType::BASE;
    }

    Local<ObjectRef> jsObj = imageInfo->ToObject(vm);
    if (jsObj->IsUndefined()) {
        return ImageType::BASE;
    }
    auto jsTypeName = ArkTSUtils::GetProperty(vm, jsObj, "typeName");
    if (!jsTypeName->IsString(vm)) {
        return ImageType::BASE;
    }
    auto typeName = jsTypeName->ToString(vm)->ToString(vm);
    if (typeName == DRAWABLE_DESCRIPTOR_NAME) {
        return ImageType::DRAWABLE;
    } else if (typeName == LAYERED_DRAWABLE_DESCRIPTOR_NAME) {
        return ImageType::LAYERED_DRAWABLE;
    } else if (typeName == ANIMATED_DRAWABLE_DESCRIPTOR_NAME) {
        return ImageType::ANIMATED_DRAWABLE;
    } else if (typeName == PIXELMAP_DRAWABLE_DESCRIPTOR_NAME) {
        return ImageType::PIXELMAP_DRAWABLE;
    } else {
        return ImageType::BASE;
    }
}
#endif

void SetBuilderNode(EcmaVM* vm, const Local<ObjectRef>& paramObject)
{
    auto contentParam = ArkTSUtils::GetProperty(vm, paramObject, "content");
    if (!contentParam->IsObject(vm)) {
        return;
    }
    auto contentObject = contentParam->ToObject(vm);
    auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
    if (!builderNodeParam->IsObject(vm)) {
        return;
    }
    auto builderNodeObject = builderNodeParam->ToObject(vm);
    auto nodeptr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
    if (nodeptr.IsEmpty()) {
        return;
    }
    CHECK_NULL_VOID(nodeptr->IsNativePointer(vm));
    auto* node = nodeptr->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GetArkUINodeModifiers()->getTabContentModifier()->setCustomStyleNode(
        GetCurrentTabContentNode(), reinterpret_cast<ArkUINodeHandle>(frameNode));
}

bool ParseDrawableIndicator(EcmaVM* vm, const Local<JSValueRef>& info, ImageInfoConfig& drawableIndicatorConfig)
{
    Local<ObjectRef> obj;
    if (!info->IsObject(vm)) {
        return false;
    }

    obj = info->ToObject(vm);
    if (!ArkTSUtils::HasProperty(vm, obj, "drawable")) {
        return false;
    }

    std::string src;
    RefPtr<PixelMap> pixelMap = nullptr;
    RefPtr<DrawableDescriptor> drawable = nullptr;
    ImageType type = ImageType::BASE;
#ifdef PIXEL_MAP_SUPPORTED
    auto imageInfo = ArkTSUtils::GetProperty(vm, obj, "drawable");
    RefPtr<ResourceObject> resObj;
    std::string bundleName;
    std::string moduleName;
    bool srcValid = ArkTSUtils::ParseJsMediaWithBundleName(vm, imageInfo, src, bundleName, moduleName, resObj);
    if (!srcValid) {
        type = ParseImageType(vm, imageInfo);
        if (type == ImageType::ANIMATED_DRAWABLE) {
            auto* drawableAddr = reinterpret_cast<DrawableDescriptor*>(ArkTSUtils::UnwrapNapiValue(vm, imageInfo));
            drawable = Referenced::Claim<DrawableDescriptor>(drawableAddr);
        } else if (type == ImageType::PIXELMAP_DRAWABLE || type == ImageType::DRAWABLE ||
                   type == ImageType::LAYERED_DRAWABLE) {
            pixelMap = ArkTSUtils::GetDrawablePixmap(vm, imageInfo);
        } else {
            return false;
        }
    }
#endif
    drawableIndicatorConfig.type = type;
    drawableIndicatorConfig.pixelMap = pixelMap;
    drawableIndicatorConfig.drawable = drawable;
    return true;
}

void SetIndicator(EcmaVM* vm, const Local<JSValueRef>& info, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    Local<ObjectRef> obj;
    if (info->IsObject(vm)) {
        obj = info->ToObject(vm);
    }
    IndicatorStyle indicator;
    RefPtr<ResourceObject> indicatorColorResObj;
    RefPtr<ResourceObject> indicatorHightResObj;
    RefPtr<ResourceObject> indicatorWidthResObj;
    RefPtr<ResourceObject> indicatorRadiusResObj;
    RefPtr<ResourceObject> indicatorMarginTopResObj;
    CalcDimension indicatorHeight;
    CalcDimension indicatorWidth;
    CalcDimension indicatorBorderRadius;
    CalcDimension indicatorMarginTop;
    bool isDrawableIndicator = false;
    if (!info->IsObject(vm) || !ArkTSUtils::ConvertFromJSValue(vm, ArkTSUtils::GetProperty(vm, obj, "color"),
                                   indicator.color, indicatorColorResObj)) {
        ImageInfoConfig drawableIndicatorConfig;
        isDrawableIndicator = ParseDrawableIndicator(vm, info, drawableIndicatorConfig);
        if (isDrawableIndicator) {
            GetArkUINodeModifiers()->getTabContentModifier()->setDrawableIndicatorConfig(
                GetCurrentTabContentNode(), &drawableIndicatorConfig);
        } else {
            RefPtr<TabTheme> tabTheme = frameNode->GetTheme<TabTheme>(true);
            if (tabTheme) {
                indicator.color = tabTheme->GetActiveIndicatorColor();
            }
        }
        GetArkUINodeModifiers()->getTabContentModifier()->setIndicatorColorByUser(GetCurrentTabContentNode(), false);
    } else {
        GetArkUINodeModifiers()->getTabContentModifier()->setIndicatorColorByUser(GetCurrentTabContentNode(), true);
    }
    if (!info->IsObject(vm) ||
        !ArkTSUtils::ParseJsDimensionVp(
            vm, ArkTSUtils::GetProperty(vm, obj, "height"), indicatorHeight, indicatorHightResObj) ||
        indicatorHeight.Value() < 0.0f || indicatorHeight.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = frameNode->GetTheme<TabTheme>(true);
        if (tabTheme) {
            indicator.height = tabTheme->GetActiveIndicatorWidth();
        }
    } else {
        indicator.height = indicatorHeight;
    }
    if (!info->IsObject(vm) ||
        !ArkTSUtils::ParseJsDimensionVp(
            vm, ArkTSUtils::GetProperty(vm, obj, "width"), indicatorWidth, indicatorWidthResObj) ||
        indicatorWidth.Value() < 0.0f || indicatorWidth.Unit() == DimensionUnit::PERCENT) {
        indicator.width = 0.0_vp;
    } else {
        indicator.width = indicatorWidth;
    }
    if (!info->IsObject(vm) ||
        !ArkTSUtils::ParseJsDimensionVp(
            vm, ArkTSUtils::GetProperty(vm, obj, "borderRadius"), indicatorBorderRadius, indicatorRadiusResObj) ||
        indicatorBorderRadius.Value() < 0.0f || indicatorBorderRadius.Unit() == DimensionUnit::PERCENT) {
        indicator.borderRadius = 0.0_vp;
    } else {
        indicator.borderRadius = indicatorBorderRadius;
    }
    if (!info->IsObject(vm) ||
        !ArkTSUtils::ParseJsDimensionVp(
            vm, ArkTSUtils::GetProperty(vm, obj, "marginTop"), indicatorMarginTop, indicatorMarginTopResObj) ||
        indicatorMarginTop.Value() < 0.0f || indicatorMarginTop.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = frameNode->GetTheme<TabTheme>(true);
        if (tabTheme) {
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
    } else {
        indicator.marginTop = indicatorMarginTop;
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setDrawableIndicatorFlag(
        GetCurrentTabContentNode(), isDrawableIndicator);
    GetArkUINodeModifiers()->getTabContentModifier()->setIndicator(GetCurrentTabContentNode(), &indicator);
    if (SystemProperties::ConfigChangePerform()) {
        ApplyCreateWithResourceObj(TabContentJsType::INDICATOR_COLOR, indicatorColorResObj);
        ApplyCreateWithResourceObj(TabContentJsType::INDICATOR_HEIGHT, indicatorHightResObj);
        ApplyCreateWithResourceObj(TabContentJsType::INDICATOR_WIDTH, indicatorWidthResObj);
        ApplyCreateWithResourceObj(TabContentJsType::INDICATOR_RADIUS, indicatorRadiusResObj);
        ApplyCreateWithResourceObj(TabContentJsType::INDICATOR_MARGIN_TOP, indicatorMarginTopResObj);
    }
}

void SetSelectedMode(EcmaVM* vm, const Local<JSValueRef>& info)
{
    int32_t selectedMode;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ConvertFromJSValue(vm, info, selectedMode, resObj)) {
        GetArkUINodeModifiers()->getTabContentModifier()->setSelectedMode(
            GetCurrentTabContentNode(), static_cast<int32_t>(SelectedMode::INDICATOR));
    } else {
        GetArkUINodeModifiers()->getTabContentModifier()->setSelectedMode(GetCurrentTabContentNode(), selectedMode);
    }
}

void SetBoard(EcmaVM* vm, const Local<JSValueRef>& info, FrameNode* frameNode)
{
    Local<ObjectRef> obj;
    if (info->IsObject(vm)) {
        obj = info->ToObject(vm);
    }
    BoardStyle board;
    CalcDimension borderRadius;
    RefPtr<ResourceObject> borderRadiusResObj;
    if (!info->IsObject(vm) || !ArkTSUtils::ParseJsDimensionVp(
        vm, ArkTSUtils::GetProperty(vm, obj, "borderRadius"), borderRadius, borderRadiusResObj) ||
        borderRadius.Value() < 0.0f || borderRadius.Unit() == DimensionUnit::PERCENT) {
        CHECK_NULL_VOID(frameNode);
        RefPtr<TabTheme> tabTheme = frameNode->GetTheme<TabTheme>(true);
        if (tabTheme) {
            board.borderRadius = tabTheme->GetFocusIndicatorRadius();
        }
    } else {
        board.borderRadius = borderRadius;
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setBoard(GetCurrentTabContentNode(), &board);
    if (SystemProperties::ConfigChangePerform()) {
        ApplyCreateWithResourceObj(TabContentJsType::BORDER_RADIUS, borderRadiusResObj);
    }
}

void GetFontContent(EcmaVM* vm, const Local<JSValueRef>& font, LabelStyle& labelStyle, bool isSubTabStyle)
{
    auto obj = font->ToObject(vm);
    RefPtr<ResourceObject> sizeResObj;
    RefPtr<ResourceObject> familyColorResObj;
    auto size = ArkTSUtils::GetProperty(vm, obj, "size");
    CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionFp(vm, size, fontSize, sizeResObj) && NonNegative(fontSize.Value()) &&
        fontSize.Unit() != DimensionUnit::PERCENT) {
        labelStyle.fontSize = fontSize;
    }

    auto weight = ArkTSUtils::GetProperty(vm, obj, "weight");
    if (weight->IsString(vm) || weight->IsNumber()) {
        auto parseResult = StringUtils::ParseFontWeight(weight->ToString(vm)->ToString(vm));
        if (parseResult.first || !isSubTabStyle) {
            labelStyle.fontWeight = parseResult.second;
        }
    }

    auto family = ArkTSUtils::GetProperty(vm, obj, "family");
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, family, fontFamilies, familyColorResObj)) {
        labelStyle.fontFamily = fontFamilies;
    }

    auto style = ArkTSUtils::GetProperty(vm, obj, "style");
    if (style->IsNumber()) {
        int32_t value = style->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
            labelStyle.fontStyle = FONT_STYLES[value];
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        ApplyCreateWithResourceObj(TabContentJsType::FONT_SIZE, sizeResObj);
        ApplyCreateWithResourceObj(TabContentJsType::FONT_FAMILY, familyColorResObj);
    }
}

void GetLabelUnselectedContent(EcmaVM* vm, const Local<JSValueRef>& unselectedColorValue, LabelStyle& labelStyle,
    FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    Color unselectedColor;
    RefPtr<ResourceObject> unselectColorResObj;
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, unselectedColorValue, unselectedColor, unselectColorResObj,
        ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        labelStyle.unselectedColor = unselectedColor;
        GetArkUINodeModifiers()->getTabContentModifier()->setLabelUnselectedColorByUser(
            GetCurrentTabContentNode(), true);
    } else {
        GetArkUINodeModifiers()->getTabContentModifier()->setLabelUnselectedColorByUser(
            GetCurrentTabContentNode(), false);
    }
    if (SystemProperties::ConfigChangePerform()) {
        ApplyCreateWithResourceObj(TabContentJsType::LABEL_UNSELECT_COLOR, unselectColorResObj);
    }
}

void GetLabelSelectedContent(EcmaVM* vm, const Local<JSValueRef>& selectedColorValue, LabelStyle& labelStyle,
    FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    Color selectedColor;
    RefPtr<ResourceObject> selectColorResObj;
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, selectedColorValue, selectedColor, selectColorResObj,
        ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        labelStyle.selectedColor = selectedColor;
        GetArkUINodeModifiers()->getTabContentModifier()->setLabelSelectedColorByUser(
            GetCurrentTabContentNode(), true);
    } else {
        GetArkUINodeModifiers()->getTabContentModifier()->setLabelSelectedColorByUser(
            GetCurrentTabContentNode(), false);
    }
    if (SystemProperties::ConfigChangePerform()) {
        ApplyCreateWithResourceObj(TabContentJsType::LABEL_SELECT_COLOR, selectColorResObj);
    }
}

void CompleteParameters(LabelStyle& labelStyle, bool isSubTabStyle, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
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
        } else if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            labelStyle.fontSize = tabTheme->GetBottomTabTextSize();
        }
    }
    if (!labelStyle.fontWeight.has_value() && !isSubTabStyle) {
        labelStyle.fontWeight = FontWeight::MEDIUM;
    }
    if (!labelStyle.fontStyle.has_value()) {
        labelStyle.fontStyle = OHOS::Ace::FontStyle::NORMAL;
    }
    if (!labelStyle.heightAdaptivePolicy.has_value()) {
        labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!labelStyle.textOverflow.has_value()) {
        labelStyle.textOverflow = TextOverflow::ELLIPSIS;
    }
}

void SetLabelStyle(EcmaVM* vm, const Local<JSValueRef>& info, bool isSubTabStyle, FrameNode* frameNode)
{
    LabelStyle labelStyle;
    if (!info->IsObject(vm)) {
        LOGW("info not is Object");
    } else {
        auto obj = info->ToObject(vm);
        auto overflowValue = ArkTSUtils::GetProperty(vm, obj, "overflow");
        if (!overflowValue.IsNull() && !overflowValue->IsUndefined() && overflowValue->IsNumber()) {
            auto overflow = overflowValue->Int32Value(vm);
            if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
                labelStyle.textOverflow = TEXT_OVERFLOWS[overflow];
            }
        }

        auto maxLines = ArkTSUtils::GetProperty(vm, obj, "maxLines");
        if (!maxLines.IsNull() && !maxLines->IsUndefined() && maxLines->IsNumber() && maxLines->Int32Value(vm) > 0) {
            labelStyle.maxLines = maxLines->Int32Value(vm);
        }

        auto minFontSizeValue = ArkTSUtils::GetProperty(vm, obj, "minFontSize");
        CalcDimension minFontSize;
        RefPtr<ResourceObject> minResObj;
        if (ArkTSUtils::ParseJsDimensionFp(vm, minFontSizeValue, minFontSize, minResObj) &&
            NonNegative(minFontSize.Value()) && minFontSize.Unit() != DimensionUnit::PERCENT) {
            labelStyle.minFontSize = minFontSize;
        }

        auto maxFontSizeValue = ArkTSUtils::GetProperty(vm, obj, "maxFontSize");
        CalcDimension maxFontSize;
        RefPtr<ResourceObject> maxResObj;
        if (ArkTSUtils::ParseJsDimensionFp(vm, maxFontSizeValue, maxFontSize, maxResObj) &&
            NonNegative(maxFontSize.Value()) && maxFontSize.Unit() != DimensionUnit::PERCENT) {
            labelStyle.maxFontSize = maxFontSize;
        }
        if (SystemProperties::ConfigChangePerform()) {
            ApplyCreateWithResourceObj(TabContentJsType::MIN_FONT_SIZE, minResObj);
            ApplyCreateWithResourceObj(TabContentJsType::MAX_FONT_SIZE, maxResObj);
        }

        auto heightAdaptivePolicyValue = ArkTSUtils::GetProperty(vm, obj, "heightAdaptivePolicy");
        if (!heightAdaptivePolicyValue.IsNull() && !heightAdaptivePolicyValue->IsUndefined() &&
            heightAdaptivePolicyValue->IsNumber()) {
            auto heightAdaptivePolicy = heightAdaptivePolicyValue->Int32Value(vm);
            if (heightAdaptivePolicy >= 0 &&
                heightAdaptivePolicy < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICIES.size())) {
                labelStyle.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICIES[heightAdaptivePolicy];
            }
        }

        auto font = ArkTSUtils::GetProperty(vm, obj, "font");
        if (!font.IsNull() && !font->IsUndefined() && font->IsObject(vm)) {
            GetFontContent(vm, font, labelStyle, isSubTabStyle);
        }

        GetLabelUnselectedContent(vm, ArkTSUtils::GetProperty(vm, obj, "unselectedColor"), labelStyle, frameNode);

        GetLabelSelectedContent(vm, ArkTSUtils::GetProperty(vm, obj, "selectedColor"), labelStyle, frameNode);
    }
    CompleteParameters(labelStyle, isSubTabStyle, frameNode);
    GetArkUINodeModifiers()->getTabContentModifier()->setLabelStyle(
        GetCurrentTabContentNode(), &labelStyle, isSubTabStyle);
}

bool ParseJsLengthMetrics(EcmaVM* vm, const Local<JSValueRef>& info, CalcDimension& result)
{
    if (!info->IsObject(vm)) {
        return false;
    }
    auto obj = info->ToObject(vm);
    if (!ArkTSUtils::HasProperty(vm, obj, "value")) {
        return false;
    }
    auto value = ArkTSUtils::GetProperty(vm, obj, "value");
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = ArkTSUtils::GetProperty(vm, obj, "unit");
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->Int32Value(vm));
    }
    result = CalcDimension(value->ToNumber(vm)->Value(), unit);
    return true;
}

void SetPadding(EcmaVM* vm, const Local<JSValueRef>& info, bool isSubTabStyle, FrameNode* frameNode)
{
    CalcDimension length;
    NG::PaddingProperty padding;
    bool useLocalizedPadding = false;
    RefPtr<ResourceObject> resPaddingObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, info, length, resPaddingObj) && NonNegative(length.Value()) &&
        length.Unit() != DimensionUnit::PERCENT) {
        padding.left = NG::CalcLength(length);
        padding.right = NG::CalcLength(length);
        padding.top = NG::CalcLength(length);
        padding.bottom = NG::CalcLength(length);
        GetArkUINodeModifiers()->getTabContentModifier()->setPadding(GetCurrentTabContentNode(), &padding, isSubTabStyle);
        if (SystemProperties::ConfigChangePerform()) {
            ApplyCreateWithResourceObj(TabContentJsType::PADDING, resPaddingObj);
        }
        return;
    }

    CHECK_NULL_VOID(frameNode);
    RefPtr<TabTheme> tabTheme = frameNode->GetTheme<TabTheme>(true);
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
    RefPtr<ResourceObject> resObjLeft;
    RefPtr<ResourceObject> resObjRight;
    RefPtr<ResourceObject> resObjTop;
    RefPtr<ResourceObject> resObjBottom;
    if (info->IsObject(vm)) {
        auto paddingObj = info->ToObject(vm);
        CalcDimension left;
        if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, paddingObj, "left"), left, resObjLeft) &&
            NonNegative(left.Value()) && left.Unit() != DimensionUnit::PERCENT) {
            padding.left = NG::CalcLength(left);
        }
        CalcDimension right;
        if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, paddingObj, "right"), right,
            resObjRight) && NonNegative(right.Value()) && right.Unit() != DimensionUnit::PERCENT) {
            padding.right = NG::CalcLength(right);
        }
        CalcDimension top;
        if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, paddingObj, "top"), top, resObjTop) &&
            NonNegative(top.Value()) && top.Unit() != DimensionUnit::PERCENT) {
            padding.top = NG::CalcLength(top);
        }
        CalcDimension bottom;
        if (ArkTSUtils::ParseJsDimensionVp(
                vm, ArkTSUtils::GetProperty(vm, paddingObj, "bottom"), bottom, resObjBottom) &&
            NonNegative(bottom.Value()) && bottom.Unit() != DimensionUnit::PERCENT) {
            padding.bottom = NG::CalcLength(bottom);
        }
    }
    if (info->IsObject(vm)) {
        auto paddingObj = info->ToObject(vm);
        CalcDimension start;
        CalcDimension end;
        CalcDimension top;
        CalcDimension bottom;
        auto startObj = ArkTSUtils::GetProperty(vm, paddingObj, "start");
        if (startObj->IsObject(vm)) {
            if (ParseJsLengthMetrics(vm, startObj, start)) {
                padding.left = NG::CalcLength(start);
                useLocalizedPadding = true;
                resObjLeft = nullptr;
            }
        }
        auto endObj = ArkTSUtils::GetProperty(vm, paddingObj, "end");
        if (endObj->IsObject(vm)) {
            if (ParseJsLengthMetrics(vm, endObj, end)) {
                padding.right = NG::CalcLength(end);
                useLocalizedPadding = true;
                resObjRight = nullptr;
            }
        }
        auto topObj = ArkTSUtils::GetProperty(vm, paddingObj, "top");
        if (topObj->IsObject(vm)) {
            if (ParseJsLengthMetrics(vm, topObj, top)) {
                padding.top = NG::CalcLength(top);
                useLocalizedPadding = true;
                resObjTop = nullptr;
            }
        }
        auto bottomObj = ArkTSUtils::GetProperty(vm, paddingObj, "bottom");
        if (bottomObj->IsObject(vm)) {
            if (ParseJsLengthMetrics(vm, bottomObj, bottom)) {
                padding.bottom = NG::CalcLength(bottom);
                useLocalizedPadding = true;
                resObjBottom = nullptr;
            }
        }
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setPadding(GetCurrentTabContentNode(), &padding, isSubTabStyle);
    GetArkUINodeModifiers()->getTabContentModifier()->setUseLocalizedPadding(
        GetCurrentTabContentNode(), useLocalizedPadding);
    ApplyCreatePaddingHorWithResourceObj(resObjLeft, resObjRight, isSubTabStyle, useLocalizedPadding);
    ApplyCreatePaddingVerWithResourceObj(resObjTop, resObjBottom, isSubTabStyle, useLocalizedPadding);
}

void SetId(EcmaVM* vm, const Local<JSValueRef>& info)
{
    std::string id;
    if (!ArkTSUtils::ParseJsString(vm, info, id)) {
        return;
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setId(GetCurrentTabContentNode(), id.c_str());
}

void SetSubTabBarStyle(EcmaVM* vm, const Local<ObjectRef>& paramObject, FrameNode* frameNode)
{
    auto contentParam = ArkTSUtils::GetProperty(vm, paramObject, "content");
    SetBuilderNode(vm, paramObject);

    auto isContentEmpty = contentParam.IsEmpty() || contentParam->IsUndefined() || contentParam->IsNull();
    if (isContentEmpty) {
        LOGW("The content param is empty");
    }
    std::optional<std::string> contentOpt;
    std::string content;
    RefPtr<ResourceObject> resTextObj;
    if (ArkTSUtils::ParseJsString(vm, contentParam, content, resTextObj)) {
        contentOpt = content;
    }

    auto indicatorParam = ArkTSUtils::GetProperty(vm, paramObject, "indicator");
    SetIndicator(vm, indicatorParam, frameNode);

    auto selectedModeParam = ArkTSUtils::GetProperty(vm, paramObject, "selectedMode");
    SetSelectedMode(vm, selectedModeParam);

    auto boardParam = ArkTSUtils::GetProperty(vm, paramObject, "board");
    SetBoard(vm, boardParam, frameNode);

    auto labelStyleParam = ArkTSUtils::GetProperty(vm, paramObject, "labelStyle");
    SetLabelStyle(vm, labelStyleParam, true, frameNode);

    auto paddingParam = ArkTSUtils::GetProperty(vm, paramObject, "padding");
    SetPadding(vm, paddingParam, true, frameNode);

    auto idParam = ArkTSUtils::GetProperty(vm, paramObject, "id");
    SetId(vm, idParam);

    ApplyCreateWithResourceObj(TabContentJsType::TEXT_CONTENT, resTextObj);
    ApplySetTabBar(TabBarStyle::SUBTABBATSTYLE, contentOpt, std::nullopt, std::nullopt, nullptr, nullptr, false);
}

void SetLayoutMode(EcmaVM* vm, const Local<JSValueRef>& info)
{
    int32_t layoutMode;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ConvertFromJSValue(vm, info, layoutMode, resObj)) {
        GetArkUINodeModifiers()->getTabContentModifier()->setLayoutMode(
            GetCurrentTabContentNode(), static_cast<int32_t>(LayoutMode::VERTICAL));
    } else {
        GetArkUINodeModifiers()->getTabContentModifier()->setLayoutMode(GetCurrentTabContentNode(), layoutMode);
    }
}

void SetVerticalAlign(EcmaVM* vm, const Local<JSValueRef>& info)
{
    auto align = FlexAlign::CENTER;
    if (info->IsNumber()) {
        auto value = info->Int32Value(vm);
        if (value >= static_cast<int32_t>(FlexAlign::FLEX_START) &&
            value <= static_cast<int32_t>(FlexAlign::FLEX_END)) {
            align = static_cast<FlexAlign>(value);
        }
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setVerticalAlign(
        GetCurrentTabContentNode(), static_cast<int32_t>(align));
}

void SetSymmetricExtensible(EcmaVM* vm, const Local<JSValueRef>& info)
{
    bool isExtensible = false;
    ParseJsBoolForSwiper(vm, info, isExtensible);
    GetArkUINodeModifiers()->getTabContentModifier()->setSymmetricExtensible(
        GetCurrentTabContentNode(), isExtensible);
}

void SetIconStyle(EcmaVM* vm, const Local<JSValueRef>& info, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    IconStyle iconStyle;
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    ApplyCreateWithResourceObj(TabContentJsType::ICON_SELECT_COLOR, nullptr);
    ApplyCreateWithResourceObj(TabContentJsType::ICON_UNSELECT_COLOR, nullptr);
    if (info->IsObject(vm)) {
        RefPtr<ResourceObject> unselectedColorResObj;
        RefPtr<ResourceObject> selectedColorResObj;
        auto obj = info->ToObject(vm);
        Color unselectedColor;
        auto unselectedColorValue = ArkTSUtils::GetProperty(vm, obj, "unselectedColor");
        if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, unselectedColorValue, unselectedColor,
            unselectedColorResObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
            iconStyle.unselectedColor = unselectedColor;
            GetArkUINodeModifiers()->getTabContentModifier()->setIconUnselectedColorByUser(
                GetCurrentTabContentNode(), true);
        } else {
            GetArkUINodeModifiers()->getTabContentModifier()->setIconUnselectedColorByUser(
                GetCurrentTabContentNode(), false);
        }

        Color selectedColor;
        auto selectedColorValue = ArkTSUtils::GetProperty(vm, obj, "selectedColor");
        if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, selectedColorValue, selectedColor, selectedColorResObj,
            ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
            iconStyle.selectedColor = selectedColor;
            GetArkUINodeModifiers()->getTabContentModifier()->setIconSelectedColorByUser(
                GetCurrentTabContentNode(), true);
        } else {
            GetArkUINodeModifiers()->getTabContentModifier()->setIconSelectedColorByUser(
                GetCurrentTabContentNode(), false);
        }
        if (SystemProperties::ConfigChangePerform()) {
            ApplyCreateWithResourceObj(TabContentJsType::ICON_SELECT_COLOR, selectedColorResObj);
            ApplyCreateWithResourceObj(TabContentJsType::ICON_UNSELECT_COLOR, unselectedColorResObj);
        }
    }
    GetArkUINodeModifiers()->getTabContentModifier()->setIconStyle(GetCurrentTabContentNode(), &iconStyle);
}

void SetBottomTabBarStyle(EcmaVM* vm, const Local<JSValueRef>& info, FrameNode* frameNode)
{
    auto paramObject = info->ToObject(vm);
    auto textParam = ArkTSUtils::GetProperty(vm, paramObject, "text");
    std::optional<std::string> textOpt = std::nullopt;
    std::string text;
    RefPtr<ResourceObject> resTextObj;
    RefPtr<ResourceObject> resIconObj;

    if (ArkTSUtils::ParseJsString(vm, textParam, text, resTextObj)) {
        textOpt = text;
    }

    auto iconParam = ArkTSUtils::GetProperty(vm, paramObject, "icon");
    std::optional<std::string> iconOpt = std::nullopt;
    std::string icon;
    std::optional<TabBarSymbol> tabBarSymbol = std::nullopt;
    if (ArkTSUtils::ParseJsMedia(vm, iconParam, icon, resIconObj, true)) {
        iconOpt = icon;
    } else if (iconParam->IsObject(vm)) {
        auto iconObject = iconParam->ToObject(vm);
        auto normalModifier = ArkTSUtils::GetProperty(vm, iconObject, "normal");
        auto selectedModifier = ArkTSUtils::GetProperty(vm, iconObject, "selected");
        if (normalModifier->IsObject(vm)) {
            TabBarSymbol symbolApply;
            SetTabBarSymbolOptionApply(vm, symbolApply, normalModifier, selectedModifier);
            if (selectedModifier->IsObject(vm)) {
                symbolApply.selectedFlag = true;
            }
            tabBarSymbol = symbolApply;
        }
    }

    auto paddingParam = ArkTSUtils::GetProperty(vm, paramObject, "padding");
    SetPadding(vm, paddingParam, false, frameNode);

    auto layoutParam = ArkTSUtils::GetProperty(vm, paramObject, "layoutMode");
    SetLayoutMode(vm, layoutParam);

    auto verticalAlignParam = ArkTSUtils::GetProperty(vm, paramObject, "verticalAlign");
    SetVerticalAlign(vm, verticalAlignParam);

    auto extensibleParam = ArkTSUtils::GetProperty(vm, paramObject, "symmetricExtensible");
    SetSymmetricExtensible(vm, extensibleParam);

    auto labelStyleParam = ArkTSUtils::GetProperty(vm, paramObject, "labelStyle");
    SetLabelStyle(vm, labelStyleParam, false, frameNode);

    SetIconStyle(vm, ArkTSUtils::GetProperty(vm, paramObject, "iconStyle"), frameNode);

    auto idParam = ArkTSUtils::GetProperty(vm, paramObject, "id");
    SetId(vm, idParam);

    ApplyCreateWithResourceObj(TabContentJsType::TEXT_CONTENT, resTextObj);
    ApplyCreateWithResourceObj(TabContentJsType::BOTTOM_TAB_BAR_STYLE_ICON, resIconObj);
    ApplySetTabBar(TabBarStyle::BOTTOMTABBATSTYLE, textOpt, iconOpt, tabBarSymbol, nullptr, nullptr, false);
}
}

void TabContentBridge::RegisterTabContentAttributes(panda::Local<panda::ObjectRef> object, panda::EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "pop",
        "setTabBar", "resetTabBar",
        "setTabContentWidth", "resetTabContentWidth",
        "setTabContentHeight", "resetTabContentHeight",
        "setTabContentSize", "resetTabContentSize",
        "setTabContentOnWillShow", "resetTabContentOnWillShow",
        "setTabContentOnWillHide", "resetTabContentOnWillHide",
    };
    Local<panda::JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::Pop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentOnWillShow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentOnWillShow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentOnWillHide),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentOnWillHide),
    };
    auto tabContent = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabContent"), tabContent);
}

ArkUINativeModuleValue TabContentBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (Container::IsCurrentUsePartialUpdate() && !firstArg.IsNull() && !firstArg->IsUndefined() &&
        firstArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = firstArg->ToObject(vm);
        std::function<void()> builder = [func = panda::CopyableGlobal(vm, func)]() {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        GetArkUINodeModifiers()->getTabContentModifier()->createTabContent(&builder);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTabContentModifier()->createTabContent(nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::Pop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    PopTabContentBridge();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> tabBarInfo = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (tabBarInfo.IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    TabContentResourceObjParam param_TEXT_CONTENT { TabContentJsType::TEXT_CONTENT, nullptr };
    GetArkUINodeModifiers()->getTabContentModifier()->createWithResourceObj(nativeNode, &param_TEXT_CONTENT);
    TabContentResourceObjParam param_TAB_BAR_OPTIONS_ICON { TabContentJsType::TAB_BAR_OPTIONS_ICON, nullptr };
    GetArkUINodeModifiers()->getTabContentModifier()->createWithResourceObj(nativeNode, &param_TAB_BAR_OPTIONS_ICON);
    TabContentResourceObjParam param_BOTTOM_TAB_BAR_STYLE_ICON { TabContentJsType::BOTTOM_TAB_BAR_STYLE_ICON, nullptr };
    GetArkUINodeModifiers()->getTabContentModifier()->createWithResourceObj(
        nativeNode, &param_BOTTOM_TAB_BAR_STYLE_ICON);
    RefPtr<ResourceObject> resTextObj;
    std::string infoStr;
    if (ArkTSUtils::ParseJsString(vm, tabBarInfo, infoStr, resTextObj)) {
        ApplySetTabBar(TabBarStyle::NOSTYLE, infoStr, std::nullopt, std::nullopt, nullptr, nullptr, true);
        if (SystemProperties::ConfigChangePerform()) {
            ApplyCreateWithResourceObj(TabContentJsType::TEXT_CONTENT, resTextObj);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    if (!tabBarInfo->IsObject(vm)) {
        ApplySetTabBar(TabBarStyle::NOSTYLE, std::nullopt, std::nullopt, std::nullopt, nullptr, nullptr, false);
        return panda::JSValueRef::Undefined(vm);
    }

    auto paramObject = tabBarInfo->ToObject(vm);
    auto contentParam = ArkTSUtils::GetProperty(vm, paramObject, "builderNode_");
    if (contentParam->IsObject(vm)) {
        auto builderNodeObject = contentParam->ToObject(vm);
        auto nodeptr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
        if (!nodeptr.IsEmpty() && nodeptr->IsNativePointer(vm)) {
            auto* node = nodeptr->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
            CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
            ApplySetTabBar(TabBarStyle::NOSTYLE, std::nullopt, std::nullopt, std::nullopt, nullptr, frameNode, false);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    auto builderParam = ArkTSUtils::GetProperty(vm, paramObject, "builder");
    std::function<void()> builder;
    if (!builderParam.IsNull() && !builderParam->IsUndefined() && builderParam->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = builderParam->ToObject(vm);
        builder = [func = panda::CopyableGlobal(vm, func)]() {
            auto vm = func.GetEcmaVM();
            if (!func.IsEmpty()) {
                ACE_SCOPED_TRACE("JSTabContent::Execute TabBar builder");
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
        ApplySetTabBar(TabBarStyle::NOSTYLE, std::nullopt, std::nullopt, std::nullopt, &builder, nullptr, false);
        return panda::JSValueRef::Undefined(vm);
    }
    auto typeParam = ArkTSUtils::GetProperty(vm, paramObject, "type");
    if (!typeParam.IsNull() &&!typeParam->IsUndefined() && typeParam->IsString(vm)) {
        auto type = typeParam->ToString(vm)->ToString(vm);
        if (type == "SubTabBarStyle") {
            SetSubTabBarStyle(vm, paramObject, frameNode);
            return panda::JSValueRef::Undefined(vm);
        }
        if (type == "BottomTabBarStyle") {
            SetBottomTabBarStyle(vm, tabBarInfo, frameNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    auto textParam = ArkTSUtils::GetProperty(vm, paramObject, "text");
    auto isTextEmpty = textParam.IsEmpty() || textParam->IsUndefined() || textParam->IsNull();
    std::optional<std::string> textOpt = std::nullopt;
    if (!isTextEmpty) {
        std::string text;
        if (ArkTSUtils::ParseJsString(vm, textParam, text, resTextObj)) {
            textOpt = text;
        }
        if (SystemProperties::ConfigChangePerform()) {
            ApplyCreateWithResourceObj(TabContentJsType::TEXT_CONTENT, resTextObj);
        }
    }
    RefPtr<ResourceObject> resIconObj;
    auto iconParam = ArkTSUtils::GetProperty(vm, paramObject, "icon");
    auto isIconEmpty = iconParam.IsEmpty() || iconParam->IsUndefined() || iconParam->IsNull();
    std::optional<std::string> iconOpt = std::nullopt;
    if (!isIconEmpty) {
        std::string icon;
        if (ArkTSUtils::ParseJsMedia(vm, iconParam, icon, resIconObj, true)) {
            iconOpt = icon;
        }
    }
    ApplySetTabBar(TabBarStyle::NOSTYLE, textOpt, iconOpt, std::nullopt, nullptr, nullptr, false);
    ApplyCreateWithResourceObj(TabContentJsType::TAB_BAR_OPTIONS_ICON, resIconObj);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabContentModifier()->setTabContentLabel(nativeNode, "");
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentOnWillShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    bool isJsView = ArkTSUtils::IsJsView(nativeNodeArg, vm);
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabContentModifier()->resetTabContentOnWillShow(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView]() {
        auto vm = func.GetEcmaVM();
        std::optional<AceScoringLog> scoringLog;
        if (isJsView) {
            scoringLog.emplace("TabContent.onWillShow");
        }
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabContentModifier()->setTabContentOnWillShow(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentOnWillShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabContentModifier()->resetTabContentOnWillShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentOnWillHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    bool isJsView = ArkTSUtils::IsJsView(nativeNodeArg, vm);
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabContentModifier()->resetTabContentOnWillHide(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView]() {
        auto vm = func.GetEcmaVM();
        std::optional<AceScoringLog> scoringLog;
        if (isJsView) {
            scoringLog.emplace("TabContent.onWillHide");
        }
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabContentModifier()->setTabContentOnWillHide(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentOnWillHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabContentModifier()->resetTabContentOnWillHide(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG

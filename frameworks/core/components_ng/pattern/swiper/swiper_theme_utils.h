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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_UTILS_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_UTILS_H

#include "ui/base/utils/utils.h"
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {

class SwiperThemeUtils {
public:
    static void ApplyThemeToDotIndicator(
        EcmaVM* vm, ArkUINodeHandle nativeNode, SwiperParameters& swiperParameters, const Local<ObjectRef>& obj)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        auto themeColors = Framework::JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        RefPtr<ResourceObject> resourceObject;
        Color color;
        NodeInfo nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        auto colorValue = obj->Get(vm, "colorValue");
        if (colorValue.IsNull() || colorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, colorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
        }
        auto selectedColorValue = obj->Get(vm, "selectedColorValue");
        if (selectedColorValue.IsNull() || selectedColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
        }
    }

    static void ApplyThemeToDotIndicatorForce(EcmaVM* vm, SwiperParameters &swiperParameters)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        if (auto themeColors = Framework::JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
            return;
        }
    }

    static void ApplyThemeToIndicatorStyle(
        EcmaVM* vm, ArkUINodeHandle nativeNode, SwiperParameters &swiperParameters, const Local<ObjectRef>& obj)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        auto themeColors = Framework::JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
        CHECK_NULL_VOID(frameNode);
        NodeInfo nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        RefPtr<ResourceObject> resourceObject;
        Color color;
        auto colorValue = obj->Get(vm, "color");
        if (colorValue.IsNull() || colorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, colorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
        }
        auto selectedColorValue = obj->Get(vm, "selectedColor");
        if (selectedColorValue.IsNull() || selectedColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
        }
    }

    static void ApplyThemeToDigitIndicator(
        EcmaVM* vm, ArkUINodeHandle nativeNode, SwiperDigitalParameters &swiperParameters, const Local<ObjectRef>& obj)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        auto themeColors = Framework::JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        NodeInfo nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        RefPtr<ResourceObject> resourceObject;
        Color color;
        auto fontColorValue = obj->Get(vm, "fontColorValue");
        if (fontColorValue.IsNull() || fontColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, fontColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.fontColor = themeColors->FontPrimary();
        }
        auto selectedColorValue = obj->Get(vm, "selectedColorValue");
        if (selectedColorValue.IsNull() || selectedColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.selectedFontColor = themeColors->FontPrimary();
        }
    }

    static void ApplyThemeToDisplayArrow(
        EcmaVM* vm, ArkUINodeHandle nativeNode, SwiperArrowParameters &swiperParameters, const Local<ObjectRef>& obj)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        auto themeColors = Framework::JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        NodeInfo nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        RefPtr<ResourceObject> resourceObject;
        Color color;
        auto arrowColorValue = obj->Get(vm, "arrowColor");
        if (arrowColorValue.IsNull() || arrowColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, arrowColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.arrowColor = themeColors->IconPrimary();
        }
        auto backgroundColorValue = obj->Get(vm, "backgroundColor");
        if (backgroundColorValue.IsNull() || backgroundColorValue->IsUndefined() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorValue, color, resourceObject, nodeInfo)) {
            swiperParameters.backgroundColor = themeColors->CompBackgroundSecondary();
        }
    }

    static void ApplyThemeToDisplayArrowForce(SwiperArrowParameters &swiperParameters)
    {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            return;
        }
        auto themeColors = Framework::JSThemeUtils::GetThemeColors();
        if (themeColors.has_value()) {
            swiperParameters.arrowColor = themeColors->IconPrimary();
            swiperParameters.backgroundColor = themeColors->CompBackgroundSecondary();
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_UTILS_H

/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/tabs/tabs_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabsOpsAccessor {
Ark_NativePointer RegisterBarModeImpl(Ark_NativePointer node,
                                      const Opt_BarMode* value,
                                      const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto mode = Converter::OptConvert<TabBarMode>(*value);
    if (mode && *mode == TabBarMode::SCROLLABLE) {
        ScrollableBarModeOptions barModeOptions;
        auto defaultMargin = barModeOptions.margin;
        if (options) {
            auto optionsOpt = Converter::OptConvert<Ark_ScrollableBarModeOptions>(*options);
            if (optionsOpt) {
                auto marginOpt = Converter::OptConvert<Dimension>(optionsOpt.value().margin);
                Validator::ValidateNonPercent(marginOpt);
                auto styleOpt = Converter::OptConvert<LayoutStyle>(optionsOpt.value().nonScrollableLayoutStyle);
                barModeOptions.margin = marginOpt.value_or(defaultMargin);
                barModeOptions.nonScrollableLayoutStyle = styleOpt;
            }
        }
        TabsModelStatic::SetScrollableBarModeOptions(frameNode, barModeOptions);
    }
    TabsModelStatic::SetTabBarMode(frameNode, mode);
    return node;
}
Ark_NativePointer RegisterBarBackgroundBlurStyleImpl(Ark_NativePointer node,
                                                     const Opt_BlurStyle* style,
                                                     const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(*style);
    auto bluroption = Converter::OptConvert<BlurStyleOption>(*options);
    if (bluroption) {
        option = bluroption.value();
    }
    if (blurStyle) {
        option.blurStyle = blurStyle.value();
    }
    TabsModelStatic::SetBarBackgroundBlurStyle(frameNode, option);
    return node;
}
} // TabsOpsAccessor
const GENERATED_ArkUITabsOpsAccessor* GetTabsOpsAccessor()
{
    static const GENERATED_ArkUITabsOpsAccessor TabsOpsAccessorImpl {
        TabsOpsAccessor::RegisterBarModeImpl,
        TabsOpsAccessor::RegisterBarBackgroundBlurStyleImpl,
    };
    return &TabsOpsAccessorImpl;
}

}
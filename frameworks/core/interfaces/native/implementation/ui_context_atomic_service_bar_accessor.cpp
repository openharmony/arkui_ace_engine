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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
static RefPtr<NG::AppBarView> ObtainAppBar()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetAppBar();
}
namespace UIContextAtomicServiceBarAccessor {
Ark_Frame GetBarRectImpl()
{
    NG::RectF barRect(0, 0, 0, 0);
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, Converter::ArkValue<Ark_Frame>(barRect));
    std::optional<NG::RectF> rectOpt = appBar->GetAppBarRect();
    if (rectOpt) {
        const NG::RectF& rect = rectOpt.value();
        barRect.SetLeft(Dimension(rect.Left(), DimensionUnit::PX).ConvertToVp());
        barRect.SetTop(Dimension(rect.Top(), DimensionUnit::PX).ConvertToVp());
        barRect.SetWidth(Dimension(rect.Width(), DimensionUnit::PX).ConvertToVp());
        barRect.SetHeight(Dimension(rect.Height(), DimensionUnit::PX).ConvertToVp());
    }
    return Converter::ArkValue<Ark_Frame>(barRect);
}
} // UIContextAtomicServiceBarAccessor
const GENERATED_ArkUIUIContextAtomicServiceBarAccessor* GetUIContextAtomicServiceBarAccessor()
{
    static const GENERATED_ArkUIUIContextAtomicServiceBarAccessor UIContextAtomicServiceBarAccessorImpl {
        UIContextAtomicServiceBarAccessor::GetBarRectImpl,
    };
    return &UIContextAtomicServiceBarAccessorImpl;
}

}

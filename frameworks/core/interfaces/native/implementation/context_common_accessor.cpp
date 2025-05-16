/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {

void AssignArkValue(Ark_Frame& dst, RectF& src)
{
    dst.x = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(src.GetX());
    dst.y = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(src.GetY());
    dst.width = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(src.Width());
    dst.height = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(src.Height());
}

std::optional<std::string> ConvertString(const Ark_Union_Number_String& src)
{
    std::optional<std::string> value;
    auto selector = src.selector;
    if (selector == 1) {
        value = OHOS::Ace::NG::Converter::OptConvert<std::string>(src.value1);
    }
    return value;
}
std::optional<int32_t> ConvertNumber(const Ark_Union_Number_String& src)
{
    std::optional<int32_t> value;
    auto selector = src.selector;
    if (selector == 0) {
        value = OHOS::Ace::NG::Converter::OptConvert<int32_t>(src.value0);
    }
    return value;
}
} // namespace
namespace UIContextAtomicServiceBarAccessor {
static RefPtr<NG::AppBarView> ObtainAppBar()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetAppBar();
}

Ark_Frame GetBarRectImpl()
{
    Ark_Frame arkFrame;
    auto appBar = ObtainAppBar();
    CHECK_NULL_RETURN(appBar, arkFrame);
    std::optional<NG::RectF> rectOpt = appBar->GetAppBarRect();
    NG::RectF barRect(0, 0, 0, 0);
    if (rectOpt) {
        const NG::RectF& rect = rectOpt.value();
        barRect.SetLeft(Dimension(rect.Left(), DimensionUnit::PX).ConvertToVp());
        barRect.SetTop(Dimension(rect.Top(), DimensionUnit::PX).ConvertToVp());
        barRect.SetWidth(Dimension(rect.Width(), DimensionUnit::PX).ConvertToVp());
        barRect.SetHeight(Dimension(rect.Height(), DimensionUnit::PX).ConvertToVp());
    }
    AssignArkValue(arkFrame, barRect);
    return arkFrame;
}
} // namespace UIContextAtomicServiceBarAccessor

namespace UIContextDispatchKeyEventAccessor {

Ark_Boolean DispatchKeyEventImpl(const Ark_Union_Number_String* node, Ark_KeyEvent event)
{
    auto result = false;
    RefPtr<NG::FrameNode> frameNode = nullptr;
    auto convId = ConvertString(*node);
    if (convId) {
        frameNode = NG::Inspector::GetFrameNodeByKey(*convId);
    } else {
        auto numberId = ConvertNumber(*node);
        if (numberId) {
            auto node = ElementRegister::GetInstance()->GetNodeById(*numberId);
            frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        }
    }
    CHECK_NULL_RETURN(frameNode, Converter::ArkValue<Ark_Boolean>(result));
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, Converter::ArkValue<Ark_Boolean>(result));

    CHECK_NULL_RETURN(event, Converter::ArkValue<Ark_Boolean>(result));
    const auto info = event->GetEventInfo();
    CHECK_NULL_RETURN(info, Converter::ArkValue<Ark_Boolean>(result));
    KeyEvent keyEvent;
    info->ParseKeyEvent(keyEvent);
    result = focusHub->HandleEvent(keyEvent);
    return Converter::ArkValue<Ark_Boolean>(result);
}
} // namespace UIContextDispatchKeyEventAccessor

const GENERATED_ArkUIUIContextAtomicServiceBarAccessor* GetUIContextAtomicServiceBarAccessor()
{
    static const GENERATED_ArkUIUIContextAtomicServiceBarAccessor accessorImpl {
        UIContextAtomicServiceBarAccessor::GetBarRectImpl,
    };
    return &accessorImpl;
}

const GENERATED_ArkUIUIContextDispatchKeyEventAccessor* GetUIContextDispatchKeyEventAccessor()
{
    static const GENERATED_ArkUIUIContextDispatchKeyEventAccessor accessorImpl {
        UIContextDispatchKeyEventAccessor::DispatchKeyEventImpl,
    };
    return &accessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
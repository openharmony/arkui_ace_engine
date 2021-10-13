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

#include "core/components_v2/inspector/swiper_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const SwiperComposedElement&)>> CREATE_JSON_MAP {
    { "index", [](const SwiperComposedElement& inspector) { return inspector.GetCurrentIndex(); } },
    { "autoPlay", [](const SwiperComposedElement& inspector) { return inspector.GetAutoPlay(); } },
    { "interval", [](const SwiperComposedElement& inspector) { return inspector.GetInterval(); } },
    { "indicator", [](const SwiperComposedElement& inspector) { return inspector.GetIndicator(); } },
    { "loop", [](const SwiperComposedElement& inspector) { return inspector.GetLoop(); } },
    { "duration", [](const SwiperComposedElement& inspector) { return inspector.GetDuration(); } },
    { "vertical", [](const SwiperComposedElement& inspector) { return inspector.GetVertical(); } },
};

} // namespace

void SwiperComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("index: ").append(GetCurrentIndex()));
    DumpLog::GetInstance().AddDesc(std::string("autoPlay: ").append(GetAutoPlay()));
    DumpLog::GetInstance().AddDesc(std::string("interval: ").append(GetInterval()));
    DumpLog::GetInstance().AddDesc(std::string("indicator: ").append(GetIndicator()));
    DumpLog::GetInstance().AddDesc(std::string("loop: ").append(GetLoop()));
    DumpLog::GetInstance().AddDesc(std::string("duration: ").append(GetDuration()));
    DumpLog::GetInstance().AddDesc(std::string("vertical: ").append(GetVertical()));
}

std::unique_ptr<JsonValue> SwiperComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string SwiperComposedElement::GetCurrentIndex() const
{
    auto renderSwiper = GetRenderSwiper();
    auto currentIndex = renderSwiper ? renderSwiper->GetCurrentIndex() : 0;
    return std::to_string(currentIndex);
}

std::string SwiperComposedElement::GetAutoPlay() const
{
    auto renderSwiper = GetRenderSwiper();
    auto autoPlay = renderSwiper ? renderSwiper->GetAutoPlay() : false;
    return ConvertBoolToString(autoPlay);
}

std::string SwiperComposedElement::GetInterval() const
{
    auto renderSwiper = GetRenderSwiper();
    auto interval = renderSwiper ? renderSwiper->GetAutoPlayInterval() : 0;
    return std::to_string(interval);
}

std::string SwiperComposedElement::GetIndicator() const
{
    auto renderSwiper = GetRenderSwiper();
    auto indicator = renderSwiper ? renderSwiper->IsShowIndicator() : true;
    return ConvertBoolToString(indicator);
}

std::string SwiperComposedElement::GetLoop() const
{
    auto renderSwiper = GetRenderSwiper();
    auto loop = renderSwiper ? renderSwiper->GetLoop() : true;
    return ConvertBoolToString(loop);
}

std::string SwiperComposedElement::GetDuration() const
{
    auto renderSwiper = GetRenderSwiper();
    auto duration = renderSwiper ? renderSwiper->GetDuration() : 0;
    return std::to_string(duration);
}

std::string SwiperComposedElement::GetVertical() const
{
    auto renderSwiper = GetRenderSwiper();
    auto isVertical = renderSwiper ? renderSwiper->IsVertical() : false;
    return ConvertBoolToString(isVertical);
}

RefPtr<RenderSwiper> SwiperComposedElement::GetRenderSwiper() const
{
    auto node = GetInspectorNode(SwiperElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderSwiper>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2
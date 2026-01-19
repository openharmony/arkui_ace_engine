/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "compatible/components/swiper/swiper_loader.h"

#include "compatible/components/swiper/dom_swiper.h"
#include "compatible/components/swiper/swiper_composed_element.h"
#include "compatible/components/swiper/swiper_declaration.h"
#include "compatible/components/swiper/swiper_model_impl.h"
#include "compatible/components/swiper/swiper_modifier.h"

#include "base/memory/ace_type.h"
#include "frameworks/compatible/components/swiper/swiper_modifier.h"

namespace OHOS::Ace {
namespace SwiperModifier {
    const ArkUISwiperModifierCompatible* GetSwiperModifier();
}

RefPtr<Framework::DOMNode> SwiperLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSwiper>(nodeId, nodeName);
}

void* SwiperLoader::CreateModel()
{
    return new Framework::SwiperModelImpl();
}

RefPtr<V2::InspectorComposedElement> SwiperLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::SwiperComposedElement>(id);
}

RefPtr<Declaration> SwiperLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SwiperDeclaration>();
}

const void* SwiperLoader::GetCustomModifier(const std::string& tag)
{
    return SwiperModifier::GetSwiperModifier();
}

} // namespace OHOS::Ace
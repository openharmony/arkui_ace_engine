/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/rating/rating_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/rating/dom_rating.h"
#include "compatible/components/rating/rating_composed_element.h"
#include "compatible/components/rating/rating_model_impl.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> RatingLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMRating>(nodeId, nodeName);
}

void* RatingLoader::CreateModel()
{
    return new Framework::RatingModelImpl();
}

RefPtr<V2::InspectorComposedElement> RatingLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::RatingComposedElement>(id);
}

} // namespace OHOS::Ace
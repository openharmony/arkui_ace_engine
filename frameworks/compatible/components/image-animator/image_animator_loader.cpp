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

#include "compatible/components/image-animator/image_animator_loader.h"

#include "compatible/components/image-animator/dom_image_animator.h"
#include "compatible/components/image-animator/image_animator_composed_element.h"
#include "compatible/components/image-animator/image_animator_declaration.h"
#include "compatible/components/image-animator/image_animator_model_impl.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"
#include "compatible/components/image-animator/image_animator_compatible_modifier.h"

namespace OHOS::Ace {
namespace ImageAnimatorCompatibleModifier {
const ArkUIImageAnimatorCompatibleModifier* GetImageAnimatorCompatibleModifier();
} // namespace ImageAnimatorCompatibleModifier
RefPtr<Framework::DOMNode> ImageAnimatorLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMImageAnimator>(nodeId, nodeName);
}

void* ImageAnimatorLoader::CreateModel()
{
    return new Framework::ImageAnimatorModelImpl();
}

RefPtr<V2::InspectorComposedElement> ImageAnimatorLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::ImageAnimatorComposedElement>(id);
}

RefPtr<Declaration> ImageAnimatorLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<ImageAnimatorDeclaration>();
}

void ImageAnimatorLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    auto dom = AceType::DynamicCast<Framework::DOMImageAnimator>(node);
    if (dom) {
        dom->SetImagesAttr(*reinterpret_cast<std::vector<ImageProperties>*>(config));
    }
}

const void* ImageAnimatorLoader::GetCustomModifier(const std::string& tag)
{
    return ImageAnimatorCompatibleModifier::GetImageAnimatorCompatibleModifier();
}
} // namespace OHOS::Ace
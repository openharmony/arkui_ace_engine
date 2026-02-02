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

#include "compatible/components/video/video_loader.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"
#include "compatible/components/video/dom_video.h"
#include "compatible/components/video/video_model_impl.h"
#include "core/components_v2/inspector/inspector_composed_element.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> VideoLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMVideo>(nodeId, nodeName);
}

void* VideoLoader::CreateModel()
{
    return new Framework::VideoModelImpl();
}

RefPtr<V2::InspectorComposedElement> VideoLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::InspectorComposedElement>(id);
}

} // namespace OHOS::Ace
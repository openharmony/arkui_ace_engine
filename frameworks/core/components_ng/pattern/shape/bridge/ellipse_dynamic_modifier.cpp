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

#include "core/interfaces/native/node/ellipse_modifier.h"

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/ellipse_model_static.h"
#include "core/components_ng/pattern/shape/bridge/ellipse_model_impl.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::EllipseModelImpl* GetEllipseModelImpl()
{
    static Framework::EllipseModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace NodeModifier {
#ifndef CROSS_PLATFORM
void CreateEllipseImpl()
{
    auto* model = GetEllipseModelImpl();
    CHECK_NULL_VOID(model);
    model->Create();
}
#endif
ArkUINodeHandle CreateEllipseFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = EllipseModelStatic::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void CreateEllipse()
{
    EllipseModelNG model;
    model.Create();
}

const ArkUIEllipseModifier* GetEllipseDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN();
        static const ArkUIEllipseModifier modifier = {
            .createEllipse = CreateEllipseImpl,
            .createEllipseFrameNode = nullptr
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIEllipseModifier modifier = {
        .createEllipse = CreateEllipse,
        .createEllipseFrameNode = CreateEllipseFrameNode
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_VIEW_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT FormView {
public:
    static void Create(const RequestFormInfo& formInfo);
    static void SetSize(const Dimension& width, const Dimension& height);
    static void SetDimension(int32_t dimension);
    static void SetAllowUpdate(bool allowUpdate);
    static void SetVisible(VisibleType visible);
    static void SetModuleName(const std::string& moduleName);
    static void SetOnAcquired(FormCallback&& onAcquired);
    static void SetOnError(FormCallback&& onError);
    static void SetOnUninstall(FormCallback&& onUninstall);
    static void SetOnRouter(FormCallback&& onRouter);

private:
    static RefPtr<FormNode> GetOrCreateFormNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_VIEW_H

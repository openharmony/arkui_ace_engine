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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_CUSTOM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_CUSTOM_NODE_H

#include "core/components_ng/base/extension_handler.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {

class ExtensionCustomNode : public ExtensionHandler {
    DECLARE_ACE_TYPE(ExtensionCustomNode, ExtensionHandler);

public:
    ~ExtensionCustomNode() = default;

    void SetMeasureCallback(std::function<void(LayoutConstraintF& layoutConstraint)> measureCallback)
    {
        measureCallback_ = measureCallback;
    }

    void SetLayoutCallback(std::function<void(OffsetF& position)> layoutCallback)
    {
        layoutCallback_ = layoutCallback;
    }

protected:
    // FrameNode measure, layout, custom function.
    // call InnerMeasure InnerLayout to process origin logic.
    void OnMeasure(const ExtensionLayoutConstraint& layoutConstraint) override;
    void OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY) override;

private:
    std::function<void(LayoutConstraintF& layoutConstraint)> measureCallback_;
    std::function<void(OffsetF& position)> layoutCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_CUSTOM_NODE_H
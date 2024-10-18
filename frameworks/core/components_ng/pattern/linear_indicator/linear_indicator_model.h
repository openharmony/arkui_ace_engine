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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class LinearIndicatorController;
}

namespace OHOS::Ace {
class ACE_EXPORT LinearIndicatorModel {
public:
    static LinearIndicatorModel* GetInstance();
    virtual ~LinearIndicatorModel() = default;

    virtual RefPtr<NG::LinearIndicatorController> Create(std::size_t progressCount) = 0;
    virtual void SetSpace(const Dimension& value) = 0;
    virtual void SetStrokeWidth(const Dimension& value) = 0;
    virtual void SetStrokeRadius(const Dimension& value) = 0;
    virtual void SetTrackBackgroundColor(const Color& value) = 0;
    virtual void SetTrackColor(const Color& value) = 0;
    virtual void Loop(bool value) = 0;
    virtual void OnChange(std::function<void(int index, float progress)>&& event) = 0;

private:
    static std::unique_ptr<LinearIndicatorModel> instance_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_MODEL_H

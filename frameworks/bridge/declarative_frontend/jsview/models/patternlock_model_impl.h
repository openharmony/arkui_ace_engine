/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PATTERNLOCK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PATTERNLOCK_MODEL_IMPL_H

#include "core/components_ng/pattern/patternlock/patternlock_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT PatternLockModelImpl : public OHOS::Ace::PatternLockModel {
public:
    RefPtr<V2::PatternLockController> Create() override;
    void SetPatternComplete(std::function<void(const BaseEventInfo* info)>&& onComplete) override;
    void SetDotConnect(std::function<void(int32_t)>&& onDotConnect) override {};
    void SetSelectedColor(const Color& selectedColor) override;
    void SetSelectedColorByUser(bool isByuserSet) override {};
    void SetAutoReset(bool isAutoReset) override;
    void SetPathColor(const Color& pathColor) override;
    void SetPathColorByUser(bool isByuserSet) override {};
    void SetActiveColor(const Color& activeColor) override;
    void SetActiveColorByUser(bool isByuserSet) override {};
    void SetRegularColor(const Color& regularColor) override;
    void SetRegularColorByUser(bool isByuserSet) override {};
    void SetCircleRadius(const Dimension& radius) override;
    void SetSideLength(const Dimension& sideLength) override;
    void SetStrokeWidth(const Dimension& lineWidth) override;
    void SetActiveCircleColor(const Color& activeCircleColor) override;
    void SetActiveCircleColorByUser(bool isByuserSet) override {};
    void SetActiveCircleRadius(const Dimension& activeCircleRadius) override;
    void SetEnableWaveEffect(bool enableWaveEffect) override;
    void SetEnableForeground(bool enableForeground) override;
    void SetSkipUnselectedPoint(bool isSkipUnselectedPoint) override;
    void CreateWithResourceObj(
        PatternLockResourceType PatternLockResourceType, const RefPtr<ResourceObject>& resObj) override {};
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PATTERNLOCK_MODEL_IMPL_H

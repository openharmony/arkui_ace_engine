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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_LINE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_LINE_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/shape/line_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LineModelNG : public OHOS::Ace::LineModel {
public:
    void Create() override;
    void StartPoint(const ShapePoint& value) override;
    void StartPoint(const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray) override;
    void EndPoint(const ShapePoint& value) override;
    void EndPoint(const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray) override;

    static void StartPoint(FrameNode* frameNode, const ShapePoint& value);
    static void StartPoint(
        FrameNode* frameNode, const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray);
    static void EndPoint(FrameNode* frameNode, const ShapePoint& value);
    static void EndPoint(
        FrameNode* frameNode, const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_LINE_MODEL_NG_H
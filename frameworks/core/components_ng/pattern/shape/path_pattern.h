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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATH_PATTERN_H

#include <string>
#include "core/components_ng/pattern/shape/shape_pattern.h"

namespace OHOS::Ace::NG {
class PathLayoutAlgorithm;
class PathPaintMethod;
class PathPaintProperty;

class PathPattern : public ShapePattern {
    DECLARE_ACE_TYPE(PathPattern, ShapePattern);

public:
    PathPattern() = default;
    ~PathPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(PathPattern);
    void SetClipBounds();

    std::string lastCommands_ = "";
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATH_PATTERN_H

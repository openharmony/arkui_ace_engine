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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_TRANSFORM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_TRANSFORM_H

#include "base/geometry/matrix4.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
namespace OHOS::Ace::NG {

class NGSvgTransform : public SvgNode {
    DECLARE_ACE_TYPE(NGSvgTransform, SvgNode);

public:
    NGSvgTransform() = default;
    ~NGSvgTransform() = default;

    static Matrix4 CreateMatrix4(const std::vector<NG::TransformInfo>& transformVec, const Offset& globalPivot);
    static bool CreateTranslate(const std::vector<std::string>& paramVec, RSMatrix& matrix);

private:
    static bool UpdateSingleTransform(
        const std::string& funcType, const std::vector<std::string>& paramVec, Matrix4& matrix);

    static void ApplyTransformPivot(const std::string& funcType, const Offset& finalPivot, Matrix4& matrix);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_TRANSFORM_H

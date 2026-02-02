/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "compatible/components/svg/svg_fe_merge_declaration.h"
#include "compatible/components/svg/svg_fe_offset_declaration.h"

namespace OHOS::Ace {

using namespace Framework;
const std::shared_ptr<SvgFeMergeAttribute> DEFAULT_SVG_FE_MERGE_ATTR =
    std::make_shared<SvgFeMergeAttribute>();

void SvgFeMergeDeclaration::InitSpecialized()
{
    AddSpecializedAttribute(DEFAULT_SVG_FE_MERGE_ATTR);
}

void SvgFeMergeDeclaration::InitializeStyle()
{
    // self attribute must be initialized first. Otherwise, may be initialized as a base attribute.
    MaybeResetAttribute<SvgFeOffsetAttribute>(AttributeTag::SPECIALIZED_ATTR);
}

} // namespace OHOS::Ace
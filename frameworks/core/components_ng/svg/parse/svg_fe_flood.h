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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_FLOOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_FLOOD_H

#include "core/components_ng/svg/parse/svg_fe.h"

namespace OHOS::Ace::NG {

class SvgFeFlood : public SvgFe {
    DECLARE_ACE_TYPE(SvgFeFlood, SvgFe);

public:
    SvgFeFlood();
    ~SvgFeFlood() override = default;
    static RefPtr<SvgNode> Create();

    void OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, const SvgColorInterpolationType& srcColor,
        SvgColorInterpolationType& currentColor,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const override;
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;

private:
    SvgFeFloodAttribute feFloodAttr_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_FLOOD_H

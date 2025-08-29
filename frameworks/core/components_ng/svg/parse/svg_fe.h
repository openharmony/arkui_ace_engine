/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_H

#include "include/core/SkImageFilter.h"

#include "core/components_ng/svg/base/svg_filter_context.h"
#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"

namespace OHOS::Ace::NG {

class SvgFe : public SvgNode {
    DECLARE_ACE_TYPE(SvgFe, SvgNode);

public:
    SvgFe();
    ~SvgFe() override = default;
    static RefPtr<SvgNode> Create();

    void OnInitStyle() override;

    void RegisterResult(const std::string& id, std::shared_ptr<RSImageFilter>& imageFilter,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const;

    static void ConverImageFilterColor(std::shared_ptr<RSImageFilter>& imageFilter,
        const SvgColorInterpolationType& src, const SvgColorInterpolationType& dst);

    static std::shared_ptr<RSImageFilter> MakeImageFilter(const SvgFeIn& in,
        std::shared_ptr<RSImageFilter>& imageFilter,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash);

    void GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, SvgColorInterpolationType& currentColor,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash,
        const Rect& effectFilterArea = {});
    void GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, std::unordered_map<std::string,
                        std::shared_ptr<RSImageFilter>>& resultHash);
    Rect ResolvePrimitiveSubRegion();
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;
    void SetFilterContext(const SvgFilterContext &filterContext) {filterContext_ = filterContext; }
    SvgFilterContext GetFilterContext() const {return filterContext_;}
protected:
    virtual void OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, const SvgColorInterpolationType& srcColor,
        SvgColorInterpolationType& currentColor,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash, bool cropRect = false) const
    {}

    Rect effectFilterArea_;
    SvgFeCommonAttribute feAttr_;
    SvgFilterContext filterContext_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_H

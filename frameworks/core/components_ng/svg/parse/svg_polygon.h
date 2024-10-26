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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_POLYGON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_POLYGON_H

#include "core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/components_ng/svg/parse/svg_graphic.h"

namespace OHOS::Ace::NG {

class SvgPolygon : public SvgGraphic {
    DECLARE_ACE_TYPE(SvgPolygon, SvgGraphic);

public:
    explicit SvgPolygon(bool isClose);
    ~SvgPolygon() override = default;
    static RefPtr<SvgNode> CreatePolygon();
    static RefPtr<SvgNode> CreatePolyline();

    RSRecordingPath AsPath(const Size& viewPort) const override;
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;

private:
    SvgPolygonAttribute polyAttr_;
    bool isClose_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_POLYGON_H
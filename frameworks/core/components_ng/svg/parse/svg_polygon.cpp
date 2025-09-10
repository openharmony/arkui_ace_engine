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

#include "frameworks/core/components_ng/svg/parse/svg_polygon.h"

#include "core/common/container.h"
#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgPolygon::SvgPolygon(bool isClose) : SvgGraphic(), isClose_(isClose) {}

RefPtr<SvgNode> SvgPolygon::CreatePolygon()
{
    return AceType::MakeRefPtr<SvgPolygon>(true);
}

RefPtr<SvgNode> SvgPolygon::CreatePolyline()
{
    return AceType::MakeRefPtr<SvgPolygon>(false);
}

void SvgPolygon::ConvertPoints(std::vector<RSPoint>& points, const SvgLengthScaleRule& lengthRule)
{
    for (auto& point : points) {
        Dimension dx(point.GetX());
        Dimension dy(point.GetY());
        auto x = GetMeasuredPosition(dx, lengthRule, SvgLengthType::HORIZONTAL);
        auto y = GetMeasuredPosition(dy, lengthRule, SvgLengthType::VERTICAL);;

        point.SetX(x);
        point.SetY(y);
    }
}

RSRecordingPath SvgPolygon::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    if (polyAttr_.points.empty()) {
        return path;
    }
    std::vector<RSPoint> rsPoints;
    RosenSvgPainter::StringToPoints(polyAttr_.points.c_str(), rsPoints);
    if (rsPoints.empty()) {
        return RSRecordingPath();
    }
    path.AddPoly(rsPoints, rsPoints.size(), isClose_);
    if (attributes_.clipState.IsEvenodd()) {
        path.SetFillStyle(RSPathFillType::EVENTODD);
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        return path;
    }
    if (attributes_.fillState.IsEvenodd()) {
        path.SetFillStyle(RSPathFillType::EVENTODD);
    }
    return path;
}

RSRecordingPath SvgPolygon::AsPath(const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath path;
    /* re-generate the Path for pathTransform(true). AsPath come from clip-path */
    if (path_.has_value() && lengthRule_ == lengthRule) {
        path = path_.value();
    } else {
        if (polyAttr_.points.empty()) {
            return path;
        }
        std::vector<RSPoint> rsPoints;
        RosenSvgPainter::StringToPoints(polyAttr_.points.c_str(), rsPoints);
        if (rsPoints.empty()) {
            return RSRecordingPath();
        }
        ConvertPoints(rsPoints, lengthRule);
        //isClose_ cannot be modified
        path.AddPoly(rsPoints, rsPoints.size(), isClose_);
        lengthRule_ = lengthRule;
        path_ = path;
    }
    if (attributes_.fillState.IsEvenodd()) {
        path.SetFillStyle(RSPathFillType::EVENTODD);
    }
    /* Apply path transform for clip-path only */
    if (lengthRule.GetPathTransform()) {
        ApplyTransform(path, lengthRule);
    }
    return path;
}

bool SvgPolygon::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    if (name == SVG_POINTS) {
        polyAttr_.points = value;
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG

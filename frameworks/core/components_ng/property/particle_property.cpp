/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/particle_property.h"

namespace OHOS::Ace::NG {

std::string PointParticleParameter::ToString() const
{
    std::string str;
    str.append("radius: [").append(std::to_string(radius_)).append("]");
    return str;
}

std::string ImageParticleParameter::ToString() const
{
    std::string str;
    str.append("imageSource: [").append(imageSource_).append("]");
    str.append("size: [").append(size_.first.ToString()).append(",").append(size_.second.ToString()).append("]");
    str.append("imageFit: [")
        .append(imageFit_.has_value() ? std::to_string(static_cast<int32_t>(imageFit_.value())) : "NA")
        .append("]");
    return str;
}

std::string ParticleConfig::ToString() const
{
    std::string str;
    str.append("pointParameter: [").append(pointParameter_.ToString()).append("]");
    str.append("imageParameter: [").append(imageParameter_.ToString()).append("]");
    return str;
}

std::string Particle::ToString() const
{
    std::string str;
    str.append("particleType: [").append(std::to_string(static_cast<int32_t>(particleType_))).append("]");
    str.append("config: [").append(config_.ToString()).append("]");
    str.append("count: [").append(std::to_string(count_)).append("]");
    str.append("lifeTime: [").append(lifeTime_.has_value() ? std::to_string(lifeTime_.value()) : "NA").append("]");
    str.append("lifeTimeRange: [")
        .append(lifeTimeRange_.has_value() ? std::to_string(lifeTimeRange_.value()) : "NA")
        .append("]");
    return str;
}

std::string ParticleAnnulusRegion::ToString() const
{
    std::string str;
    str.append("center: [")
        .append(center_.first.ToString())
        .append(",")
        .append(center_.second.ToString())
        .append("]");
    str.append("innerRadius: [")
        .append(std::to_string(innerRadius_.ConvertToPx()))
        .append("]");
    str.append("outerRadius: [")
        .append(std::to_string(outerRadius_.ConvertToPx()))
        .append("]");
    str.append("startAngle: [")
        .append(std::to_string(startAngle_))
        .append("]");
    str.append("endAngle: [")
        .append(std::to_string(endAngle_))
        .append("]");
    return str;
}

std::string EmitterOption::ToString() const
{
    std::string str;
    str.append("particle: [").append(particle_.ToString()).append("]");
    str.append("emitterRate: [")
        .append(emitterRate_.has_value() ? std::to_string(emitterRate_.value()) : "NA")
        .append("]");
    if (position_.has_value()) {
        str.append("position: [")
            .append(position_->first.ToString())
            .append(",")
            .append(position_->second.ToString())
            .append("]");
    } else {
        str.append("position: [").append("NA").append("]");
    }
    if (size_.has_value()) {
        str.append("size: [")
            .append(size_->first.ToString())
            .append(",")
            .append(size_->second.ToString())
            .append("]");
    } else {
        str.append("size: [").append("NA").append("]");
    }
    str.append("shape: [")
        .append(shape_.has_value() ? std::to_string(static_cast<int32_t>(shape_.value())) : "NA")
        .append("]");
    str.append("annulusRegion: [")
        .append(annulusRegion_.has_value() ? annulusRegion_->ToString() : "NA")
        .append("]");
    return str;
}

std::string ParticleFloatPropertyUpdaterConfig::ToString() const
{
    std::string str;
    str.append("noneValue: [").append(noneValue_).append("]");
    str.append("randomConfig: [")
        .append(std::to_string(randomConfig_.first))
        .append(",")
        .append(std::to_string(randomConfig_.second))
        .append("]");
    if (animations_.size() > 0) {
        str.append("animations: [");
        for (auto& item : animations_) {
            str.append("{").append(item.ToString()).append("}");
        }
        str.append("]");
    } else {
        str.append("animations: [").append("]");
    }
    return str;
}

std::string ParticleFloatPropertyUpdater::ToString() const
{
    std::string str;
    str.append("updaterType: [").append(std::to_string(static_cast<int32_t>(updaterType_))).append("]");
    str.append("config: [").append(config_.ToString()).append("]");
    return str;
}

std::string ParticleFloatPropertyOption::ToString() const
{
    std::string str;
    str.append("range: [")
        .append(std::to_string(range_.first))
        .append(",")
        .append(std::to_string(range_.second))
        .append("]");
    str.append("updater: [").append(updater_.has_value() ? updater_->ToString() : "NA").append("]");
    return str;
}

std::string ColorParticleRandomUpdateConfig::ToString() const
{
    std::string str;
    str.append("redRandom: [")
        .append(std::to_string(redRandom_.first))
        .append(",")
        .append(std::to_string(redRandom_.second))
        .append("]");
    str.append("greenRandom: [")
        .append(std::to_string(greenRandom_.first))
        .append(",")
        .append(std::to_string(greenRandom_.second))
        .append("]");
    str.append("blueRandom: [")
        .append(std::to_string(blueRandom_.first))
        .append(",")
        .append(std::to_string(blueRandom_.second))
        .append("]");
    str.append("alphaRandom: [")
        .append(std::to_string(alphaRandom_.first))
        .append(",")
        .append(std::to_string(alphaRandom_.second))
        .append("]");
    return str;
}

std::string ParticleColorPropertyUpdaterConfig::ToString() const
{
    std::string str;
    str.append("inValid: [").append(std::to_string(inValid_)).append("]");
    str.append("random: [").append(random_.ToString()).append("]");
    str.append("animationArray: [");
    if (animationArray_.size() > 0) {
        for (auto& item : animationArray_) {
            str.append("{").append(item.ToString()).append("}");
        }
    }
    str.append("]");
    return str;
}

std::string ParticleColorPropertyUpdater::ToString() const
{
    std::string str;
    str.append("type: [").append(std::to_string(static_cast<int32_t>(type_))).append("]");
    str.append("config: [").append(config_.ToString()).append("]");
    return str;
}

std::string ParticleColorPropertyOption::ToString() const
{
    std::string str;
    str.append("range: [")
        .append(range_.first.ColorToString())
        .append(",")
        .append(range_.second.ColorToString())
        .append("]");
    str.append("config: [").append(updater_.has_value() ? updater_->ToString() : "NA").append("]");
    return str;
}

std::string VelocityProperty::ToString() const
{
    std::string str;
    str.append("speed: [")
        .append(std::to_string(speed_.first))
        .append(",")
        .append(std::to_string(speed_.second))
        .append("]");
    str.append("angle: [")
        .append(std::to_string(angle_.first))
        .append(",")
        .append(std::to_string(angle_.second))
        .append("]");
    return str;
}

std::string AccelerationProperty::ToString() const
{
    std::string str;
    str.append("speed: [").append(speed_.has_value() ? speed_->ToString() : "NA").append("]");
    str.append("angle: [").append(angle_.has_value() ? angle_->ToString() : "NA").append("]");
    return str;
}

std::string ParticleOption::ToString() const
{
    std::string str;
    str.append("emitter: [").append(emitter_.ToString()).append("]");
    str.append("colorOption: [").append(colorOption_.has_value() ? colorOption_->ToString() : "NA").append("]");
    str.append("opacityOption: [")
        .append(opacityOption_.has_value() ? opacityOption_->ToString() : "NA")
        .append("]");
    str.append("scaleOption: [").append(scaleOption_.has_value() ? scaleOption_->ToString() : "NA").append("]");
    str.append("velocityOption: [")
        .append(velocityOption_.has_value() ? velocityOption_->ToString() : "NA")
        .append("]");
    str.append("accelerationOption: [")
        .append(accelerationOption_.has_value() ? accelerationOption_->ToString() : "NA")
        .append("]");
    str.append("spinOption: [").append(spinOption_.has_value() ? spinOption_->ToString() : "NA").append("]");
    return str;
}
} // namespace OHOS::Ace::NG

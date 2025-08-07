/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PARTICLE_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PARTICLE_PROPERTIES_H
#include <cstdint>
#include <list>
#include <optional>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/particle_property_animation.h"
#include "core/common/resource/resource_object.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_PARTICLE_COUNT = 5;
}
enum ACE_EXPORT UpdaterType { NONE_UPDATER = 0, RANDOM, CURVE };

enum ACE_EXPORT ParticleType { POINT = 0, IMAGE };

enum ACE_EXPORT ParticleEmitterShape { RECTANGLE = 0, CIRCLE, ELLIPSE, ANNULUS };

enum ACE_EXPORT DistributionType { UNIFORM = 0, GAUSSIAN };

struct PointParticleParameter {
public:
    void SetRadius(float radius)
    {
        radius_ = radius;
    }

    float GetRadius() const
    {
        return radius_;
    }

    bool operator==(const PointParticleParameter& other) const
    {
        return NearEqual(radius_, other.GetRadius());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("radius: [").append(std::to_string(radius_)).append("]");
        return str;
    }

private:
    float radius_ = 0.0f;
};

struct ImageParticleParameter {
public:
    const std::string& GetImageSource() const
    {
        return imageSource_;
    }

    void SetImageSource(std::string& imageSource)
    {
        imageSource_ = imageSource;
    }

    const std::pair<Dimension, Dimension>& GetSize() const
    {
        return size_;
    }

    void SetSizeX(Dimension& sizeX)
    {
        size_.first = sizeX;
    }

    void SetSizeY(Dimension& sizeY)
    {
        size_.second = sizeY;
    }

    void SetSize(std::pair<Dimension, Dimension>& size)
    {
        size_ = size;
    }

    std::optional<ImageFit> GetImageFit() const
    {
        return imageFit_;
    }

    void SetImageFit(ImageFit& imageFit)
    {
        imageFit_ = imageFit;
    }

    bool operator==(const ImageParticleParameter& other) const
    {
        return (imageSource_ == other.GetImageSource()) && (size_ == other.GetSize()) &&
               (imageFit_ == other.GetImageFit());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("imageSource: [").append(imageSource_).append("]");
        str.append("size: [").append(size_.first.ToString()).append(",").append(size_.second.ToString()).append("]");
        str.append("imageFit: [")
            .append(imageFit_.has_value() ? std::to_string(static_cast<int32_t>(imageFit_.value())) : "NA")
            .append("]");
        return str;
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, ImageParticleParameter&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        EmitterResMap_[key] = { resObj, std::move(updateFunc) };
    }
 
    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : EmitterResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    void RemoveResource(const std::string& key)
    {
        auto iter = EmitterResMap_.find(key);
        if (iter != EmitterResMap_.end()) {
            EmitterResMap_.erase(iter);
        }
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, ImageParticleParameter&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> EmitterResMap_;
    std::string imageSource_;
    std::pair<Dimension, Dimension> size_;
    std::optional<ImageFit> imageFit_;
};

struct ParticleConfig {
public:
    void SetPointParticleParameter(const PointParticleParameter& pointParticleParameter)
    {
        pointParameter_ = pointParticleParameter;
    }
    const PointParticleParameter& GetPointParticleParameter() const
    {
        return pointParameter_;
    }
    void SetImageParticleParameter(const ImageParticleParameter& imageParticleParameter)
    {
        imageParameter_ = imageParticleParameter;
    }
    const ImageParticleParameter& GetImageParticleParameter() const
    {
        return imageParameter_;
    }

    bool operator==(const ParticleConfig& other) const
    {
        return (pointParameter_ == other.GetPointParticleParameter()) &&
               (imageParameter_ == other.GetImageParticleParameter());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("pointParameter: [").append(pointParameter_.ToString()).append("]");
        str.append("imageParameter: [").append(imageParameter_.ToString()).append("]");
        return str;
    }

private:
    PointParticleParameter pointParameter_;
    ImageParticleParameter imageParameter_;
};

struct Particle {
public:
    const ParticleType& GetParticleType() const
    {
        return particleType_;
    }
    void SetParticleType(const ParticleType& particleType)
    {
        particleType_ = particleType;
    }
    const ParticleConfig& GetConfig() const
    {
        return config_;
    }
    void SetConfig(const ParticleConfig& config)
    {
        config_ = config;
    }
    int32_t GetCount() const
    {
        return count_;
    }
    void SetCount(int32_t count)
    {
        count_ = count;
    }
    void SetLifeTime(int64_t lifetime)
    {
        lifeTime_ = lifetime;
    }

    const std::optional<int64_t>& GetLifeTime() const
    {
        return lifeTime_;
    }

    void SetLifeTimeRange(int64_t lifetimeRange)
    {
        lifeTimeRange_ = lifetimeRange;
    }

    const std::optional<int64_t>& GetLifeTimeRange() const
    {
        return lifeTimeRange_;
    }

    bool operator==(const Particle& other) const
    {
        return (particleType_ == other.GetParticleType()) && (config_ == other.GetConfig()) &&
               (count_ == other.GetCount()) && (lifeTime_ == other.GetLifeTime()) &&
               (lifeTimeRange_ == other.GetLifeTimeRange());
    }

    std::string ToString() const
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

private:
    ParticleType particleType_;
    ParticleConfig config_;
    int32_t count_ = DEFAULT_PARTICLE_COUNT;
    std::optional<int64_t> lifeTime_;
    std::optional<int64_t> lifeTimeRange_;
};

struct ParticleAnnulusRegion {
    ParticleAnnulusRegion(std::pair<CalcDimension, CalcDimension> centerValue, CalcDimension innerRadiusValue,
        CalcDimension outerRadiusValue, float startAngleValue, float endAngleValue)
        : center_(centerValue), innerRadius_(innerRadiusValue),
          outerRadius_(outerRadiusValue), startAngle_(startAngleValue), endAngle_(endAngleValue) {}

    bool operator==(const ParticleAnnulusRegion& others) const
    {
        return (center_ == others.center_) && (innerRadius_ == others.innerRadius_) &&
        (outerRadius_ == others.outerRadius_) && (startAngle_ == others.startAngle_) &&
        (endAngle_ == others.endAngle_);
    }

    std::string ToString() const
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

    std::pair<CalcDimension, CalcDimension> GetCenter() const
    {
        return center_;
    }

    void SetCenter(const std::pair<CalcDimension, CalcDimension>& center)
    {
        center_ = center;
    }

    void SetCenterX(CalcDimension& centerX)
    {
        center_.first = centerX;
    }

    void SetCenterY(CalcDimension& centerY)
    {
        center_.second = centerY;
    }

    CalcDimension GetInnerRadius() const
    {
        return innerRadius_;
    }

    void SetInnerRadius(const CalcDimension& innerRadius)
    {
        innerRadius_ = innerRadius;
    }

    CalcDimension GetOuterRadius() const
    {
        return outerRadius_;
    }

    void SetOuterRadius(const CalcDimension& outerRadius)
    {
        outerRadius_ = outerRadius;
    }

    float GetStartAngle() const
    {
        return startAngle_;
    }

    void SetStartAngle(float startAngle)
    {
        startAngle_ = startAngle;
    }

    float GetEndAngle() const
    {
        return endAngle_;
    }

    void SetEndAngle(float endAngle)
    {
        endAngle_ = endAngle;
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, ParticleAnnulusRegion&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        AnnulusResMap_[key] = { resObj, std::move(updateFunc) };
    }
 
    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : AnnulusResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    void RemoveResource(const std::string& key)
    {
        auto iter = AnnulusResMap_.find(key);
        if (iter != AnnulusResMap_.end()) {
            AnnulusResMap_.erase(iter);
        }
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, ParticleAnnulusRegion&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> AnnulusResMap_;

    std::pair<CalcDimension, CalcDimension> center_;
    CalcDimension innerRadius_;
    CalcDimension outerRadius_;
    float startAngle_;
    float endAngle_;
};

struct EmitterOption {
public:
    const Particle& GetParticle() const
    {
        return particle_;
    }
    void SetParticle(Particle& particle)
    {
        particle_ = particle;
    }
    void SetEmitterRate(int32_t emitterRate)
    {
        emitterRate_ = emitterRate;
    }

    const std::optional<int32_t>& GetEmitterRate() const
    {
        return emitterRate_;
    }

    void SetPosition(std::pair<Dimension, Dimension>& point)
    {
        position_ = point;
    }

    void SetPositionX(Dimension& pointX)
    {
        position_->first = pointX;
    }

    void SetPositionY(Dimension& pointY)
    {
        position_->second = pointY;
    }

    const std::optional<std::pair<Dimension, Dimension>>& GetPosition() const
    {
        return position_;
    }

    void SetSize(std::pair<Dimension, Dimension>& size)
    {
        size_ = size;
    }

    void SetSizeX(Dimension& sizeX)
    {
        size_->first = sizeX;
    }

    void SetSizeY(Dimension& sizeY)
    {
        size_->second = sizeY;
    }

    const std::optional<std::pair<Dimension, Dimension>>& GetSize() const
    {
        return size_;
    }

    void SetShape(ParticleEmitterShape& shape)
    {
        shape_ = shape;
    }

    const std::optional<ParticleEmitterShape>& GetShape() const
    {
        return shape_;
    }

    void SetAnnulusRegion(ParticleAnnulusRegion& annulusRegion)
    {
        annulusRegion_ = annulusRegion;
    }

    const std::optional<ParticleAnnulusRegion>& GetAnnulusRegion() const
    {
        return annulusRegion_;
    }

    bool operator==(const EmitterOption& other) const
    {
        return particle_ == other.GetParticle() && emitterRate_ == other.GetEmitterRate() &&
               position_ == other.GetPosition() && size_ == other.GetSize() &&
               shape_ == other.GetShape() && annulusRegion_ == other.GetAnnulusRegion();
    }

    std::string ToString() const
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
    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, EmitterOption&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        EmitterResMap_[key] = { resObj, std::move(updateFunc) };
    }
 
    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : EmitterResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    void RemoveResource(const std::string& key)
    {
        auto iter = EmitterResMap_.find(key);
        if (iter != EmitterResMap_.end()) {
            EmitterResMap_.erase(iter);
        }
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, EmitterOption&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> EmitterResMap_;

    Particle particle_;
    std::optional<int32_t> emitterRate_;
    std::optional<std::pair<Dimension, Dimension>> position_;
    std::optional<std::pair<Dimension, Dimension>> size_;
    std::optional<ParticleEmitterShape> shape_;
    std::optional<ParticleAnnulusRegion> annulusRegion_;
};

struct ParticleFloatPropertyUpdaterConfig {
public:
    void SetRandomConfig(const std::pair<float, float>& randomConfig)
    {
        randomConfig_ = randomConfig;
    }

    const std::pair<float, float>& GetRandomConfig() const
    {
        return randomConfig_;
    }

    void SetAnimations(const std::list<ParticlePropertyAnimation<float>>& animations)
    {
        animations_ = animations;
    }

    const std::list<ParticlePropertyAnimation<float>>& GetAnimations() const
    {
        return animations_;
    }

    void SetNullStr(const std::string noneValue)
    {
        noneValue_ = noneValue;
    }

    const std::string& GetNullStr() const
    {
        return noneValue_;
    }

    bool operator==(const ParticleFloatPropertyUpdaterConfig& other) const
    {
        return (noneValue_ == other.GetNullStr()) && NearEqual(randomConfig_.first, other.GetRandomConfig().first) &&
               NearEqual(randomConfig_.second, other.GetRandomConfig().second) &&
               (animations_ == other.GetAnimations());
    }

    std::string ToString() const
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

private:
    std::string noneValue_;
    std::pair<float, float> randomConfig_;
    std::list<ParticlePropertyAnimation<float>> animations_;
};

struct ParticleFloatPropertyUpdater {
public:
    const UpdaterType& GetUpdaterType() const
    {
        return updaterType_;
    }

    void SetUpdaterType(const UpdaterType& updateType)
    {
        updaterType_ = updateType;
    }

    const ParticleFloatPropertyUpdaterConfig& GetConfig() const
    {
        return config_;
    }

    void SetConfig(const ParticleFloatPropertyUpdaterConfig& config)
    {
        config_ = config;
    }

    bool operator==(const ParticleFloatPropertyUpdater& other) const
    {
        return (updaterType_ == other.GetUpdaterType()) && (config_ == other.GetConfig());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("updaterType: [").append(std::to_string(static_cast<int32_t>(updaterType_))).append("]");
        str.append("config: [").append(config_.ToString()).append("]");
        return str;
    }

private:
    UpdaterType updaterType_ = UpdaterType::NONE_UPDATER;
    ParticleFloatPropertyUpdaterConfig config_;
};

struct ParticleFloatPropertyOption {
public:
    const std::pair<float, float>& GetRange() const
    {
        return range_;
    }

    void SetRange(const std::pair<float, float>& range)
    {
        range_ = range;
    }

    const std::optional<ParticleFloatPropertyUpdater>& GetUpdater() const
    {
        return updater_;
    }

    void SetUpdater(const ParticleFloatPropertyUpdater& updater)
    {
        updater_ = updater;
    }

    bool operator==(const ParticleFloatPropertyOption& other) const
    {
        return NearEqual(range_.first, other.GetRange().first) && NearEqual(range_.second, other.GetRange().second) &&
               (updater_ == other.GetUpdater());
    }

    std::string ToString() const
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

private:
    std::pair<float, float> range_;
    std::optional<ParticleFloatPropertyUpdater> updater_;
};

struct ColorParticleRandomUpdateConfig {
public:
    const std::pair<float, float>& GetRedRandom() const
    {
        return redRandom_;
    }

    void SetRedRandom(const std::pair<float, float>& redRandom)
    {
        redRandom_ = redRandom;
    }

    const std::pair<float, float>& GetGreenRandom() const
    {
        return greenRandom_;
    }

    void SetGreenRandom(const std::pair<float, float>& greenRandom)
    {
        greenRandom_ = greenRandom;
    }

    const std::pair<float, float>& GetBlueRandom() const
    {
        return blueRandom_;
    }

    void SetBlueRandom(const std::pair<float, float>& blueRandom)
    {
        blueRandom_ = blueRandom;
    }

    const std::pair<float, float>& GetAlphaRandom() const
    {
        return alphaRandom_;
    }

    void SetAlphaRandom(const std::pair<float, float>& alphaRandom)
    {
        alphaRandom_ = alphaRandom;
    }

    bool operator==(const ColorParticleRandomUpdateConfig& other) const
    {
        return NearEqual(redRandom_.first, other.GetRedRandom().first) &&
               NearEqual(redRandom_.second, other.GetRedRandom().second) &&
               NearEqual(greenRandom_.first, other.GetGreenRandom().first) &&
               NearEqual(greenRandom_.second, other.GetGreenRandom().second) &&
               NearEqual(blueRandom_.first, other.GetBlueRandom().first) &&
               NearEqual(blueRandom_.second, other.GetBlueRandom().second) &&
               NearEqual(alphaRandom_.first, other.GetAlphaRandom().first) &&
               NearEqual(alphaRandom_.second, other.GetAlphaRandom().second);
    }

    std::string ToString() const
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

private:
    std::pair<float, float> redRandom_;
    std::pair<float, float> greenRandom_;
    std::pair<float, float> blueRandom_;
    std::pair<float, float> alphaRandom_;
};

struct ParticleColorPropertyUpdaterConfig {
public:
    void SetInValid(int32_t inValid)
    {
        inValid_ = inValid;
    }

    int32_t GetInValid() const
    {
        return inValid_;
    }

    void SetRandomConfig(const ColorParticleRandomUpdateConfig& randomConfig)
    {
        random_ = randomConfig;
    }

    const ColorParticleRandomUpdateConfig& GetRandomConfig() const
    {
        return random_;
    }

    void SetAnimationArray(const std::list<ParticlePropertyAnimation<Color>>& animationArray)
    {
        animationArray_ = animationArray;
    }

    const std::list<ParticlePropertyAnimation<Color>>& GetAnimationArray() const
    {
        return animationArray_;
    }

    bool operator==(const ParticleColorPropertyUpdaterConfig& other) const
    {
        return (inValid_ == other.GetInValid()) && (random_ == other.GetRandomConfig()) &&
               (animationArray_ == other.GetAnimationArray());
    }

    std::string ToString() const
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

private:
    int32_t inValid_ = 0;
    ColorParticleRandomUpdateConfig random_;
    std::list<ParticlePropertyAnimation<Color>> animationArray_;
};

struct ParticleColorPropertyUpdater {
public:
    const UpdaterType& GetUpdateType() const
    {
        return type_;
    }

    void SetUpdateType(UpdaterType type)
    {
        type_ = type;
    }

    const ParticleColorPropertyUpdaterConfig& GetConfig() const
    {
        return config_;
    }

    void SetConfig(const ParticleColorPropertyUpdaterConfig& config)
    {
        config_ = config;
    }

    bool operator==(const ParticleColorPropertyUpdater& other) const
    {
        return (type_ == other.GetUpdateType()) && (config_ == other.GetConfig());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("type: [").append(std::to_string(static_cast<int32_t>(type_))).append("]");
        str.append("config: [").append(config_.ToString()).append("]");
        return str;
    }

private:
    UpdaterType type_ = UpdaterType::NONE_UPDATER;
    ParticleColorPropertyUpdaterConfig config_;
};

struct ParticleColorPropertyOption {
public:
    const std::pair<Color, Color>& GetRange() const
    {
        return range_;
    }
    void SetRange(std::pair<Color, Color>& range)
    {
        range_ = range;
    }

    void SetRangeFirst(Color& rangeFirst)
    {
        range_.first = rangeFirst;
    }

    void SetRangeSecond(Color& rangeSecond)
    {
        range_.second = rangeSecond;
    }

    const std::optional<DistributionType>& GetDistribution() const
    {
        return distribution_;
    }
    void SetDistribution(DistributionType& distribution)
    {
        distribution_ = distribution;
    }
    const std::optional<ParticleColorPropertyUpdater>& GetUpdater() const
    {
        return updater_;
    }
    void SetUpdater(ParticleColorPropertyUpdater& updater)
    {
        updater_ = updater;
    }

    bool operator==(const ParticleColorPropertyOption& other) const
    {
        return (range_ == other.GetRange()) && (updater_ == other.GetUpdater()) &&
               (distribution_ == other.GetDistribution());
    }

    std::string ToString() const
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
    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, ParticleColorPropertyOption&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        particleColorResMap_[key] = { resObj, std::move(updateFunc) };
    }
 
    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : particleColorResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }
    void RemoveResource(const std::string& key)
    {
        auto iter = particleColorResMap_.find(key);
        if (iter != particleColorResMap_.end()) {
            particleColorResMap_.erase(iter);
        }
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, ParticleColorPropertyOption&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> particleColorResMap_;
    std::pair<Color, Color> range_;
    std::optional<DistributionType> distribution_;
    std::optional<ParticleColorPropertyUpdater> updater_;
};

struct VelocityProperty {
public:
    const std::pair<float, float>& GetSpeedRange() const
    {
        return speed_;
    }
    void SetSpeedRange(std::pair<float, float>& speed)
    {
        speed_ = speed;
    }
    const std::pair<float, float>& GetAngleRange() const
    {
        return angle_;
    }
    void SetAngleRange(std::pair<float, float>& angle)
    {
        angle_ = angle;
    }

    bool operator==(const VelocityProperty& other) const
    {
        return NearEqual(speed_.first, other.GetSpeedRange().first) &&
               NearEqual(speed_.second, other.GetSpeedRange().second) &&
               NearEqual(angle_.first, other.GetAngleRange().first) &&
               NearEqual(angle_.second, other.GetAngleRange().second);
    }

    std::string ToString() const
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

private:
    std::pair<float, float> speed_;
    std::pair<float, float> angle_;
};

struct AccelerationProperty {
public:
    const std::optional<ParticleFloatPropertyOption>& GetSpeed() const
    {
        return speed_;
    }

    void SetSpeed(const ParticleFloatPropertyOption& speed)
    {
        speed_ = speed;
    }

    const std::optional<ParticleFloatPropertyOption>& GetAngle() const
    {
        return angle_;
    }

    void SetAngle(ParticleFloatPropertyOption& angle)
    {
        angle_ = angle;
    }

    bool operator==(const AccelerationProperty& other) const
    {
        return (speed_ == other.GetSpeed()) && (angle_ == other.GetAngle());
    }

    std::string ToString() const
    {
        std::string str;
        str.append("speed: [").append(speed_.has_value() ? speed_->ToString() : "NA").append("]");
        str.append("angle: [").append(angle_.has_value() ? angle_->ToString() : "NA").append("]");
        return str;
    }

private:
    std::optional<ParticleFloatPropertyOption> speed_;
    std::optional<ParticleFloatPropertyOption> angle_;
};

struct ParticleOption {
public:

    const EmitterOption& GetEmitterOption() const
    {
        return emitter_;
    }

    void SetEmitterOption(EmitterOption& emitter)
    {
        emitter_ = emitter;
    }

    const std::optional<ParticleColorPropertyOption>& GetParticleColorOption() const
    {
        return colorOption_;
    }

    void SetParticleColorOption(const ParticleColorPropertyOption& colorOption)
    {
        colorOption_ = colorOption;
    }

    const std::optional<ParticleFloatPropertyOption>& GetParticleOpacityOption() const
    {
        return opacityOption_;
    }

    void SetParticleOpacityOption(ParticleFloatPropertyOption& opacityOption)
    {
        opacityOption_ = opacityOption;
    }

    const std::optional<ParticleFloatPropertyOption>& GetParticleScaleOption() const
    {
        return scaleOption_;
    }

    void SetParticleScaleOption(ParticleFloatPropertyOption& scaleOption)
    {
        scaleOption_ = scaleOption;
    }

    const std::optional<VelocityProperty>& GetParticleVelocityOption() const
    {
        return velocityOption_;
    }

    void SetParticleVelocityOption(VelocityProperty& velocityOption)
    {
        velocityOption_ = velocityOption;
    }

    const std::optional<AccelerationProperty>& GetParticleAccelerationOption() const
    {
        return accelerationOption_;
    }

    void SetParticleAccelerationOption(AccelerationProperty& accelerationOption)
    {
        accelerationOption_ = accelerationOption;
    }

    const std::optional<ParticleFloatPropertyOption>& GetParticleSpinOption() const
    {
        return spinOption_;
    }

    void SetParticleSpinOption(ParticleFloatPropertyOption& spinOption)
    {
        spinOption_ = spinOption;
    }

    bool operator==(const ParticleOption& other) const
    {
        return (emitter_ == other.GetEmitterOption()) && (colorOption_ == other.GetParticleColorOption()) &&
               (opacityOption_ == other.GetParticleOpacityOption()) &&
               (scaleOption_ == other.GetParticleScaleOption()) &&
               (velocityOption_ == other.GetParticleVelocityOption()) &&
               (accelerationOption_ == other.GetParticleAccelerationOption()) &&
               (spinOption_ == other.GetParticleSpinOption());
    }

    std::string ToString() const
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

private:
    EmitterOption emitter_;
    std::optional<ParticleColorPropertyOption> colorOption_;
    std::optional<ParticleFloatPropertyOption> opacityOption_;
    std::optional<ParticleFloatPropertyOption> scaleOption_;
    std::optional<VelocityProperty> velocityOption_;
    std::optional<AccelerationProperty> accelerationOption_;
    std::optional<ParticleFloatPropertyOption> spinOption_;
};
} // namespace OHOS::Ace::NG
#endif
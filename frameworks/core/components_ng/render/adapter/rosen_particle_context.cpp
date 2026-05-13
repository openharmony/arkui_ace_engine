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

#include "frameworks/core/components_ng/render/adapter/rosen_particle_context.h"

#include "animation/rs_particle_field_collection.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;
void RosenRenderParticle::UpdateDisturbance(
    const RefPtr<FrameNode>& frameNode, const std::vector<ParticleDisturbance>& disturbanceArray)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(renderContext);
    auto rsNode = renderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    auto collection = std::make_shared<Rosen::ParticleFieldCollection>();
    for (auto field : disturbanceArray) {
        double sizeWidthPx = Dimension(field.size[0], DimensionUnit::VP).ConvertToPx();
        double sizeHeightPx = Dimension(field.size[1], DimensionUnit::VP).ConvertToPx();
        double positionXPx = Dimension(field.position[0], DimensionUnit::VP).ConvertToPx();
        double positionYPx = Dimension(field.position[1], DimensionUnit::VP).ConvertToPx();
        Rosen::Vector2f size = {static_cast<float>(sizeWidthPx), static_cast<float>(sizeHeightPx)};
        Rosen::Vector2f position = {static_cast<float>(positionXPx), static_cast<float>(positionYPx)};
        auto rsField = std::make_shared<Rosen::ParticleNoiseField>(static_cast<int>(field.strength),
            static_cast<Rosen::ShapeType>(field.shape), size, position, field.feather, field.noiseScale,
            field.noiseFrequency, field.noiseAmplitude);
        collection->Add(rsField);
    }
    rsNode->SetParticleFields(collection);
}

void RosenRenderParticle::UpdateRippleFields(
    const RefPtr<FrameNode>& frameNode, const std::vector<ParticleRippleField>& rippleArray)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(renderContext);
    auto rsNode = renderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    auto collection = std::make_shared<Rosen::ParticleFieldCollection>();
    for (const auto& ripple : rippleArray) {
        Rosen::Vector2f center = {ripple.center.first.ConvertToPx(), ripple.center.second.ConvertToPx()};
        auto rsRipple = std::make_shared<Rosen::ParticleRippleField>(center, ripple.amplitude, ripple.wavelength,
            ripple.waveSpeed, ripple.attenuation);
        rsRipple->regionShape_  = static_cast<Rosen::ShapeType>(ripple.region.shape);
        Rosen::Vector2f size = {
            ripple.region.size.first.ConvertToPx(), ripple.region.size.second.ConvertToPx()
        };
        rsRipple->regionSize_ = size;
        Rosen::Vector2f position = {
            ripple.region.position.first.ConvertToPx(), ripple.region.position.second.ConvertToPx()
        };
        rsRipple->regionPosition_ = position;
        collection->Add(rsRipple);
    }
    rsNode->SetParticleFields(collection);
}

void RosenRenderParticle::UpdateVelocityFields(
    const RefPtr<FrameNode>& frameNode, const std::vector<ParticleVelocityField>& velocityArray)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(renderContext);
    auto rsNode = renderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    auto collection = std::make_shared<Rosen::ParticleFieldCollection>();
    for (const auto& velocityField : velocityArray) {
        Rosen::Vector2f velocity = {velocityField.velocity.first, velocityField.velocity.second};
        auto rsVelocity = std::make_shared<Rosen::ParticleVelocityField>(velocity);
        rsVelocity->regionShape_ = static_cast<Rosen::ShapeType>(velocityField.region.shape);
        Rosen::Vector2f size = {
            velocityField.region.size.first.ConvertToPx(), velocityField.region.size.second.ConvertToPx()
        };
        rsVelocity->regionSize_ = size;
        Rosen::Vector2f position = {
            velocityField.region.position.first.ConvertToPx(), velocityField.region.position.second.ConvertToPx()
        };
        rsVelocity->regionPosition_ = position;
        collection->Add(rsVelocity);
    }
    rsNode->SetParticleFields(collection);
}

void RosenRenderParticle::updateEmitterPosition(
    const RefPtr<FrameNode>& frameNode, std::vector<EmitterProperty>& props)
{
    if (props.size() == 0) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rsNode = AceType::DynamicCast<NG::RosenRenderContext>(renderContext)->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    std::vector<std::shared_ptr<Rosen::EmitterUpdater>> emitUpdater;
    for (const auto& prop : props) {
        std::optional<Rosen::Vector2f> position = std::nullopt;
        if (prop.position) {
            double positionXPx = Dimension(prop.position->x, DimensionUnit::VP).ConvertToPx();
            double positionYPx = Dimension(prop.position->y, DimensionUnit::VP).ConvertToPx();
            position = { static_cast<float>(positionXPx), static_cast<float>(positionYPx) };
        }

        std::optional<Rosen::Vector2f> size = std::nullopt;
        if (prop.size) {
            double sizeWidthPx = Dimension(prop.size->x, DimensionUnit::VP).ConvertToPx();
            double sizeHeightPx = Dimension(prop.size->y, DimensionUnit::VP).ConvertToPx();
            size = { static_cast<float>(sizeWidthPx), static_cast<float>(sizeHeightPx) };
        }

        std::shared_ptr<Rosen::EmitterUpdater> updater = std::make_shared<Rosen::EmitterUpdater>(
            prop.index, position, size, prop.emitRate ? prop.emitRate : std::nullopt);
        std::shared_ptr<Rosen::AnnulusRegion> rsAnnulusRegion = nullptr;
        if (prop.annulusRegion) {
            auto annulusRegion = prop.annulusRegion;
            auto center = annulusRegion->GetCenter();
            auto rect = renderContext->GetPaintRectWithoutTransform();
            auto rsCenter = OHOS::Rosen::Vector2f(center.first.ConvertToPxWithSize(rect.Width()),
                center.second.ConvertToPxWithSize(rect.Height()));
            auto innerRadius = annulusRegion->GetInnerRadius();
            auto rsInnerRadius = (LessOrEqual(innerRadius.ConvertToPx(), 0.0)
                || innerRadius.Unit() == DimensionUnit::PERCENT) ? 0.0 : innerRadius.ConvertToPx();
            auto outerRadius = annulusRegion->GetOuterRadius();
            auto rsOuterRadius = (LessOrEqual(outerRadius.ConvertToPx(), 0.0)
                || outerRadius.Unit() == DimensionUnit::PERCENT) ? 0.0 : outerRadius.ConvertToPx();
            rsAnnulusRegion =
                std::make_shared<Rosen::AnnulusRegion>(rsCenter, rsInnerRadius,
                rsOuterRadius, annulusRegion->GetStartAngle(), annulusRegion->GetEndAngle());
        }
        updater->SetShape(rsAnnulusRegion);
        emitUpdater.push_back(updater);
    }
    if (!emitUpdater.empty()) {
        rsNode->SetEmitterUpdater(emitUpdater);
    }
}
} // namespace OHOS::Ace::NG
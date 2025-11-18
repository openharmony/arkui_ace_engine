/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_UTIL_H
#include "video_node.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace::NG {
namespace {
using HiddenChangeEvent = std::function<void(bool)>;
constexpr uint32_t SECONDS_PER_HOUR = 3600;
constexpr uint32_t SECONDS_PER_MINUTE = 60;
const std::string FORMAT_HH_MM_SS = "%02d:%02d:%02d";
const std::string FORMAT_MM_SS = "%02d:%02d";
constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;
constexpr uint32_t CURRENT_POS = 1;
constexpr uint32_t SLIDER_POS = 2;
constexpr uint32_t DURATION_POS = 3;
constexpr uint32_t FULL_SCREEN_POS = 4;
constexpr int32_t AVERAGE_VALUE = 2;
constexpr int32_t ANALYZER_DELAY_TIME = 100;
constexpr int32_t ANALYZER_CAPTURE_DELAY_TIME = 1000;
const Dimension LIFT_HEIGHT = 28.0_vp;
const std::string PNG_FILE_EXTENSION = "png";
constexpr int32_t MEDIA_TYPE_AUD = 0;
constexpr float VOLUME_STEP = 0.05f;
const std::unordered_set<ImageFit> EXPORT_IMAGEFIT_SUPPORT_TYPES = {
    ImageFit::FILL,
    ImageFit::CONTAIN,
    ImageFit::COVER,
    ImageFit::FITWIDTH, //FITWIDTH is used instead of AUTO
    ImageFit::NONE,
    ImageFit::SCALE_DOWN,
    ImageFit::TOP_LEFT,
    ImageFit::TOP,
    ImageFit::TOP_END,
    ImageFit::START,
    ImageFit::CENTER,
    ImageFit::END,
    ImageFit::BOTTOM_START,
    ImageFit::BOTTOM,
    ImageFit::BOTTOM_END
};

enum SliderChangeMode {
    BEGIN = 0,
    MOVING,
    END,
};

std::string IntTimeToText(uint32_t time)
{
    auto minutes = (time % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE;
    auto seconds = time % SECONDS_PER_MINUTE;
    if (time >= SECONDS_PER_HOUR) {
        auto hours = time / SECONDS_PER_HOUR;
        return StringUtils::FormatString(FORMAT_HH_MM_SS.c_str(), hours, minutes, seconds);
    }
    return StringUtils::FormatString(FORMAT_MM_SS.c_str(), minutes, seconds);
}

SizeF CalculateFitContain(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();
    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { static_cast<float>(sourceRatio) * layoutSize.Height(), layoutSize.Height() };
    }
    return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
}

SizeF CalculateFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}

SizeF CalculateFitCover(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();
    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
    }
    return { static_cast<float>(layoutSize.Height() * sourceRatio), layoutSize.Height() };
}

SizeF CalculateFitNone(const SizeF& videoSize)
{
    return videoSize;
}

SizeF CalculateFitScaleDown(const SizeF& videoSize, const SizeF& layoutSize)
{
    if (layoutSize.Width() > videoSize.Width()) {
        return CalculateFitNone(videoSize);
    }
    return CalculateFitContain(videoSize, layoutSize);
}

RectF MeasureVideoContentLayout(const SizeF& layoutSize, const RefPtr<VideoLayoutProperty>& layoutProperty)
{
    if (!layoutProperty || !layoutProperty->HasVideoSize()) {
        return {0.0f, 0.0f, layoutSize.Width(), layoutSize.Height()};
    }

    auto videoSize = layoutProperty->GetVideoSizeValue(SizeF(0, 0));
    auto videoFrameSize = videoSize;
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    auto rect = RectF();
    switch (imageFit) {
        case ImageFit::CONTAIN: case ImageFit::FITWIDTH: //FITWIDTH is used instead of AUTO
            videoFrameSize = CalculateFitContain(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::FILL:
            videoFrameSize = CalculateFitFill(layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::COVER:
            videoFrameSize = CalculateFitCover(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::NONE:
            videoFrameSize = CalculateFitNone(videoSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::SCALE_DOWN:
            videoFrameSize = CalculateFitScaleDown(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::TOP_LEFT:
            rect = RectF{0.0f, 0.0f, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::TOP:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE, 0.0f,
                videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::TOP_END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(), 0.0f, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::START:
            rect = RectF{0.0f, (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::CENTER:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(),
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM_START:
            rect = RectF{0.0f, layoutSize.Height() - videoFrameSize.Height(), videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                layoutSize.Height() - videoFrameSize.Height(), videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM_END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(), layoutSize.Height() - videoFrameSize.Height(),
                videoSize.Width(), videoSize.Height()};
            break;
        default:
            videoFrameSize = CalculateFitCover(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
    }
    return rect;
}

float RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.50f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}

RectF AdjustPaintRect(float positionX, float positionY, float width, float height, bool isRound)
{
    RectF rect;
    float relativeLeft = positionX;
    float relativeTop = positionY;
    float nodeWidth = width;
    float nodeHeight = height;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;

    float nodeLeftI = RoundValueToPixelGrid(relativeLeft, isRound, false, false);
    float nodeTopI = RoundValueToPixelGrid(relativeTop, isRound, false, false);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    rect.SetLeft(nodeLeftI);
    rect.SetTop(nodeTopI);

    float nodeWidthI = RoundValueToPixelGrid(absoluteRight, isRound, false, false) - nodeLeftI;
    float nodeWidthTemp = RoundValueToPixelGrid(nodeWidth, isRound, false, false);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom, isRound, false, false) - nodeTopI;
    float nodeHeightTemp = RoundValueToPixelGrid(nodeHeight, isRound, false, false);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }

    rect.SetWidth(nodeWidthI);
    rect.SetHeight(nodeHeightI);
    return rect;
}

Gradient ConvertToGradient(Color color)
{
    Gradient gradient;
    GradientColor gradientColorBegin;
    gradientColorBegin.SetLinearColor(LinearColor(color));
    gradientColorBegin.SetDimension(Dimension(0.0f));
    gradient.AddColor(gradientColorBegin);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0f));
    gradient.AddColor(gradientColorEnd);

    return gradient;
}

void RegisterMediaPlayerEventImpl(const WeakPtr<VideoPattern>& weak, const RefPtr<MediaPlayer>& mediaPlayer,
    int32_t instanceId, const SingleTaskExecutor& uiTaskExecutor)
{
    auto&& positionUpdatedEvent = [weak, uiTaskExecutor, instanceId](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([weak, currentPos, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnCurrentTimeChange(currentPos);
            video->StartUpdateImageAnalyzer();
            }, "ArkUIVideoCurrentTimeChange");
    };

    auto&& stateChangedEvent = [weak, uiTaskExecutor, instanceId](PlaybackStatus status) {
        uiTaskExecutor.PostTask([weak, status, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnPlayerStatus(status);
            }, "ArkUIVideoPlayerStatusChange");
    };

    auto&& errorEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnError("");
            }, "ArkUIVideoError");
    };

    auto&& videoErrorEvent = [weak, uiTaskExecutor, instanceId](int32_t code, const std::string& message) {
        uiTaskExecutor.PostTask([weak, instanceId, code, message] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnError(code, message);
            }, "ArkUIVideoErrorWithParam");
    };

    auto&& resolutionChangeEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostSyncTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnResolutionChange();
            }, "ArkUIVideoResolutionChange");
    };

    auto&& startRenderFrameEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostSyncTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnStartRenderFrameCb();
            }, "ArkUIVideoStartRenderFrame");
    };

    mediaPlayer->RegisterMediaPlayerEvent(
        positionUpdatedEvent, stateChangedEvent, errorEvent, resolutionChangeEvent, startRenderFrameEvent);
    mediaPlayer->RegisterMediaPlayerVideoErrorEvent(videoErrorEvent);
}

std::string StatusToString(PlaybackStatus status)
{
    switch (status) {
        case PlaybackStatus::ERROR:
            return "ERROR";
        case PlaybackStatus::IDLE:
            return "IDLE";
        case PlaybackStatus::INITIALIZED:
            return "INITIALIZED";
        case PlaybackStatus::PREPARED:
            return "PREPARED";
        case PlaybackStatus::STARTED:
            return "STARTED";
        case PlaybackStatus::PAUSED:
            return "PAUSED";
        case PlaybackStatus::STOPPED:
            return "STOPPED";
        case PlaybackStatus::PLAYBACK_COMPLETE:
            return "PLAYBACK_COMPLETE";
        case PlaybackStatus::NONE:
            return "NONE";
        default:
            return "Invalid";
    }
}
} // namespace
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_UTIL_H

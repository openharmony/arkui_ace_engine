/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_PLAYER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_PLAYER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "core/animation/animator.h"
#include "apng_image_animation.h"
#include "core/image/image_source_info.h"
#include "core/image/image_provider.h"
#include "apng_image_decoder.h"
#include "core/pipeline/base/scoped_canvas_state.h"

namespace OHOS::Ace {

/**
Dispose method specifies how the area used by the current frame is to be treated
before rendering the next frame on the canvas.
*/
typedef enum {
    /**
     No disposal is done on this frame before rendering the next; the contents
     of the canvas are left as is.
     */
    ImageDisposeNone = 0,

    /**
     The frame's region of the canvas is to be cleared to fully transparent black
     before rendering the next frame.
     */
    ImageDisposeBackground,

    /**
     The frame's region of the canvas is to be reverted to the previous contents
     before rendering the next frame.
     */
    ImageDisposePrevious,
} ImageDisposeMethod;

/**
Blend operation specifies how transparent pixels of the current frame are
blended with those of the previous canvas.
*/
typedef enum {
    /**
     All color components of the frame, including alpha, overwrite the current
     contents of the frame's canvas region.
     */
    ImageBlendNone = 0,

    /**
     The frame should be composited onto the output buffer based on its alpha.
     */
    ImageBlendOver,
} ImageBlendOperation;

/**
 * Apng Header and frames information
 */
typedef struct {
    uint32_t index = 0;            ///< sequence number of the animation chunk, starting from 0
    uint32_t width = 0;            ///< width of the following frame
    uint32_t height = 0;           ///< height of the following frame
    uint32_t offsetX = 0;          ///< x position at which to render the following frame
    uint32_t offsetY = 0;          ///< y position at which to render the following frame
    float duration = 0.0;
    ImageDisposeMethod dispose = ImageDisposeNone;
    ImageBlendOperation blend  = ImageBlendNone;
    bool isFullSize = false;          ///< Whether frame fill the canvas.
    uint32_t blendFromIndex = 0;  ///< Blend from frame index to current frame.
    std::shared_ptr<RSImage> image = nullptr;
} APngAnimatedFrameInfo;


class APngImagePlayer : public virtual AceType {
    DECLARE_ACE_TYPE(APngImagePlayer, AceType);

public:
    APngImagePlayer(
        ImageSourceInfo source,
        UploadSuccessCallback successCallback,
        const WeakPtr<PipelineBase>& weakContext,
        const RefPtr<PNGImageDecoder>& decoder,
        int32_t dstWidth = -1,
        int32_t dstHeight = -1);

    ~APngImagePlayer() override;

    void Pause();

    void Resume();

    void RenderFrame(const int32_t& index);

    /**
     * Use for draw each frame image in self
     **/
    void Paint(const flutter::Paint& paint, const Offset& offset, const ScopedCanvas& canvas, const Rect& paintRect);

    void SetTargetSize(int32_t width, int32_t height)
    {
        dstWidth_ = width;
        dstHeight_ = height;
    }

private:
    ImageSourceInfo imageSource_;
    UploadSuccessCallback successCallback_;
    WeakPtr<PipelineBase> context_;

    const RefPtr<PNGImageDecoder> apngDecoder_;
    int32_t frameCount_;
    int32_t repetitionCount_;
    bool needBlend_;
    int32_t blendFrameIndex_;
    int32_t width_;  //image source width
    int32_t height_;
    std::vector<APngAnimatedFrameInfo> frameInfos_;

    int32_t dstWidth_ = -1;
    int32_t dstHeight_ = -1;

    // used to cache required frame.
    std::unordered_map<int32_t, std::unique_ptr<APngAnimatedFrameInfo *>> cachedFrame_;

    // used to cache last required frame. this will be reset during looping.
    int32_t lastRequiredFrameIndex_ = -1;

    /**
     * Use a blank canvas draw each frame to get frame image
     **/
    RSBitmap bitmap_;
    RSCanvas *blendCanvas_ = nullptr;
    RefPtr<Scheduler> scheduler_;
    RefPtr<APngImageAnimation> pictureAnimation_;

    /**
     * Decode apng image and get all frame head information
     * but didn't decode image data
     **/
    bool GetApngAllFrames();

    /**
     * Decode frame image data to SKImage
     * Before decode frame need decode frame header before
     **/
    APngAnimatedFrameInfo *DecodeFrameImage(const int32_t &index);

    /**
     * Copy bitmap to a dst bitmap
     **/
    static bool CopyTo(RSBitmap *dst, const RSBitmap &src);

    float DelayToSeconds(uint16_t num, uint16_t den);

    RSCanvas *CreateBlendCanvas();

    /**
     * Get frame image with index or frameinfo
     **/
    std::shared_ptr<RSImage> GetImage(const int32_t &index, bool extendToCanvas);

    std::shared_ptr<RSImage> GetImage(const APngAnimatedFrameInfo *frameInfo);

    /**
     * Before render image in backgroud thread predecode image all frames
     **/
    bool PreDecodeAllFrames();

    void ClearCanvasRect(const APngAnimatedFrameInfo *frameInfo);

    /**
     * Use blend role draw frame image to canvas
     */
    void BlendImage(const APngAnimatedFrameInfo *frameInfo);

    /***
     * Debug function
     * */
    void DrawTest();

    void DrawTestBorder(RSRect &rect);
};

} // namespace OHOS::Ace


#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_PLAYER_H

/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_PNG_IMAGE_DECODER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_PNG_IMAGE_DECODER_H

#include "base/geometry/size.h"
#include "base/memory/ace_type.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkStream.h"
#include "include/core/SkImage.h"
#endif

namespace OHOS::Ace {
/*
 PNG  spec: http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html
 APNG spec: https://wiki.mozilla.org/APNG_Specification

 ===============================================================================
 PNG format:
 header (8): 89 50 4e 47 0d 0a 1a 0a
 chunk, chunk, chunk, ...

 ===============================================================================
 chunk format:
 length (4): uint32_t big endian
 fourcc (4): chunk type code
 data   (length): data
 crc32  (4): uint32_t big endian crc32(fourcc + data)

 ===============================================================================
 PNG chunk define:

 IHDR (Image Header) required, must appear first, 13 bytes
 width              (4) pixel count, should not be zero
 height             (4) pixel count, should not be zero
 bit depth          (1) expected: 1, 2, 4, 8, 16
 color type         (1) 1<<0 (palette used), 1<<1 (color used), 1<<2 (alpha channel used)
 compression method (1) 0 (deflate/inflate)
 filter method      (1) 0 (adaptive filtering with five basic filter types)
 interlace method   (1) 0 (no interlace) or 1 (Adam7 interlace)

 IDAT (Image Data) required, must appear consecutively if there's multiple 'IDAT' chunk

 IEND (End) required, must appear last, 0 bytes

 ===============================================================================
 APNG chunk define:

 acTL (Animation Control) required, must appear before 'IDAT', 8 bytes
 num frames     (4) number of frames
 num plays      (4) number of times to loop, 0 indicates infinite looping

 fcTL (Frame Control) required, must appear before the 'IDAT' or 'fdAT'
 chunks of the frame to which it applies, 26 bytes
 sequence number   (4) sequence number of the animation chunk, starting from 0
 width             (4) width of the following frame
 height            (4) height of the following frame
 x offset          (4) x position at which to render the following frame
 y offset          (4) y position at which to render the following frame
 delay num         (2) frame delay fraction numerator
 delay den         (2) frame delay fraction denominator
 dispose op        (1) type of frame area disposal to be done after rendering this frame
                       (0:none, 1:background 2:previous)
 blend op          (1) type of frame area rendering for this frame (0:source, 1:over)

 fdAT (Frame Data) required
 sequence number   (4) sequence number of the animation chunk
 frame data        (x) frame data for this frame (same as 'IDAT')

 ===============================================================================
 `dispose_op` specifies how the output buffer should be changed at the end of the delay
 (before rendering the next frame).

 * NONE: no disposal is done on this frame before rendering the next; the contents
    of the output buffer are left as is.
 * BACKGROUND: the frame's region of the output buffer is to be cleared to fully
    transparent black before rendering the next frame.
 * PREVIOUS: the frame's region of the output buffer is to be reverted to the previous
    contents before rendering the next frame.

 `blend_op` specifies whether the frame is to be alpha blended into the current output buffer
 content, or whether it should completely replace its region in the output buffer.

 * SOURCE: all color components of the frame, including alpha, overwrite the current contents
    of the frame's output buffer region.
 * OVER: the frame should be composited onto the output buffer based on its alpha,
    using a simple OVER operation as described in the "Alpha Channel Processing" section
    of the PNG specification
 */

/**
 * PNG & APNG Alpha type
 **/
typedef enum {
    PNG_ALPHA_TYPE_PALEETE = 1 << 0,
    PNG_ALPHA_TYPE_COLOR = 1 << 1,
    PNG_ALPHA_TYPE_ALPHA = 1 << 2
} PngAlphaType;

typedef enum {
    PNG_DISPOSE_OP_NONE = 0,
    PNG_DISPOSE_OP_BACKGROUND = 1,
    PNG_DISPOSE_OP_PREVIOUS = 2
} PngDisposeOp;

/**
 * APNG image blend mode
 **/
typedef enum {
    PNG_BLEND_OP_SOURCE = 0,
    PNG_BLEND_OP_OVER = 1
} PngBlendOp;

/**
 * IHDR (Image Header) required, must appear first, 13 bytes
 * width              (4) pixel count, should not be zero
 * height             (4) pixel count, should not be zero
 * bit depth          (1) expected: 1, 2, 4, 8, 16
 * color type         (1) 1<<0 (palette used), 1<<1 (color used), 1<<2 (alpha channel used)
 * compression method (1) 0 (deflate/inflate)
 * filter method      (1) 0 (adaptive filtering with five basic filter types)
 * interlace method   (1) 0 (no interlace) or 1 (Adam7 interlace)
 **/
typedef struct {
    uint32_t width = 0;             ///< pixel count, should not be zero
    uint32_t height = 0;            ///< pixel count, should not be zero
    uint8_t bitDepth = 0;          ///< expected: 1, 2, 4, 8, 16
    uint8_t colorType = 0;         ///< see PngAlphaType
    uint8_t compressionMethod = 0; ///< 0 (deflate/inflate)
    uint8_t filterMethod = 0;      ///< 0 (adaptive filtering with five basic filter types)
    uint8_t interlaceMethod = 0;   ///< 0 (no interlace) or 1 (Adam7 interlace)
} PngChunkIHDR;

/**
 * fcTL (Frame Control) required, must appear before the 'IDAT' or 'fdAT'
 * chunks of the frame to which it applies, 26 bytes
 * sequence number   (4) sequence number of the animation chunk, starting from 0
 * width             (4) width of the following frame
 * height            (4) height of the following frame
 * x offset          (4) x position at which to render the following frame
 * y offset          (4) y position at which to render the following frame
 * delay num         (2) frame delay fraction numerator
 * delay den         (2) frame delay fraction denominator
 * dispose op        (1) type of frame area disposal to be done after rendering this frame
 *                       (0:none, 1:background 2:previous)
 * blend op          (1) type of frame area rendering for this frame (0:source, 1:over)
 **/
typedef struct {
    uint32_t sequenceNumber = 0;  ///< sequence number of the animation chunk, starting from 0
    uint32_t width = 0;            ///< width of the following frame
    uint32_t height = 0;           ///< height of the following frame
    uint32_t xOffset = 0;         ///< x position at which to render the following frame
    uint32_t yOffset = 0;         ///< y position at which to render the following frame
    uint16_t delayNum = 0;        ///< frame delay fraction numerator
    uint16_t delayDen = 0;        ///< frame delay fraction denominator
    uint8_t disposeOp = 0;        ///< see PngDisposeOp
    uint8_t blendOp = 0;          ///< see PngBlendOp
} PngChunkfcTL;

/**
 * Chunk information
 * use for identifier echo chunk data info
 **/
typedef struct {
    uint32_t offset = 0; ///< chunk offset in PNG data
    uint32_t fourcc = 0; ///< chunk fourcc
    uint32_t length = 0; ///< chunk data length
    uint32_t crc32 = 0;  ///< chunk crc32
} PngChunkInfo;

/**
 * APNG frame information
 * contain current chunk index and size
 * detail frame info in the fcTL
 **/
typedef struct {
    uint32_t chunkIndex = 0; ///< the first `fdAT`/`IDAT` chunk index
    uint32_t chunkNum = 0;   ///< the `fdAT`/`IDAT` chunk count
    uint32_t chunkSize = 0;  ///< the `fdAT`/`IDAT` chunk bytes
    PngChunkfcTL frameControl;
} PngFrameInfo;

/**
 * PNG & APNG file information
 * png Header and chunk data
 * apng frames info
 **/
typedef struct {
    PngChunkIHDR header;   ///< png header
    PngChunkInfo *chunks;      ///< chunks
    uint32_t chunkNum;          ///< count of chunks

    PngFrameInfo *apngFrames; ///< frame info, NULL if not apng
    uint32_t apngFrameNum;     ///< 0 if not apng
    uint32_t apngLoopNum;      ///< 0 indicates infinite looping

    uint32_t *apngSharedChunkIndexs; ///< shared chunk index
    uint32_t apngSharedChunkNum;     ///< shared chunk count
    uint32_t apngSharedChunkSize;    ///< shared chunk bytes
    uint32_t apngSharedInsertIndex;  ///< shared chunk insert index
    bool apngFirstFrameIsCover;     ///< the first frame is same as png (cover)
} PngInfo;

class PNGImageDecoder : public virtual AceType {
    DECLARE_ACE_TYPE(PNGImageDecoder, AceType);

public:
#ifndef USE_ROSEN_DRAWING
    PNGImageDecoder(const sk_sp<SkData> &data);
#else
    PNGImageDecoder(const std::shared_ptr<RSData> &data);
#endif

    ~PNGImageDecoder() override;

    /**
     * with image header judge whether is a apng file
     * use for split png and apng file
     * @return
     */
    bool isApng();
    Size GetImageSize();
    uint32_t GetFrameCount();

    /**
     * Decode apng image header information
     * @return
     */
    bool DecodeImage();

    /**
     * Get apng header info and all frames information
     * @return
     */
    PngInfo *GetApngInfo();

    /**
     * Get frame image data
     * i: undecoded image data
     * @param index
     * @param size : return data size
     * @return
     */
    uint8_t *GetFrameData(uint32_t index, uint32_t *size, bool oldWay = false);
    static bool IsApngSource(const std::string& src);
private:
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> data_;
#else
    std::shared_ptr<RSData> data_;
#endif
    PngInfo *pngInfo_ = nullptr;
    bool dataCheck_ = false;
    bool isApng_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_PNG_IMAGE_DECODER_H

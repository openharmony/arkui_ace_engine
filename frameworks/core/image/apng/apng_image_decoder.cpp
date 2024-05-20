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

#include "core/image/apng/apng_image_decoder.h"
#include <cstdlib>
#include <cstdio>
#include <securec.h>
#include <string>
#include <cmath>
#include "png.h"
#include "zlib.h"
#include "base/utils/string_utils.h"

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and !defined(IOS_PLATFORM)
#include <malloc.h>
#endif

namespace OHOS::Ace {
constexpr uint32_t PNGSize22 = 22;
constexpr uint32_t PNGSize24 = 24;
constexpr uint32_t PNGSize25 = 25;
constexpr uint32_t PNGHeadHeight = 4;
constexpr uint32_t PNGHeadBitDepth = 8;
constexpr uint32_t PNGHeadColorType = 9;
constexpr uint32_t PNGHeadCompMethod = 10;
constexpr uint32_t PNGHeadFilterMethod = 11;
constexpr uint32_t PNGHeadInterMethod = 12;

constexpr uint32_t MiniChunkNum = 3;
constexpr uint32_t ChunkHeadLength = 13;
constexpr uint32_t PngHeadLength = 8;
constexpr uint32_t PngFOURCCLen = 4;
constexpr uint32_t PngFcTLLen = 26;
constexpr uint32_t Byte2 = 2;
constexpr uint32_t Byte4 = 4;
constexpr uint32_t Byte8 = 8;
constexpr uint32_t Byte12 = 12;
constexpr uint32_t Byte16 = 16;
constexpr uint32_t Byte17 = 17;
constexpr uint32_t Byte20 = 20;
constexpr uint32_t Byte21 = 21;
constexpr uint32_t Byte24 = 24;
constexpr uint32_t Byte25 = 25;
constexpr uint32_t Byte32 = 32;

#define FOUR_CC(c1, c2, c3, c4) (static_cast<uint32_t>(((c4) << Byte24) | ((c3) << Byte16) | ((c2) << Byte8) | (c1)))
#define TWO_CC(c1, c2) (static_cast<uint16_t>(((c2) << Byte8) | (c1)))

static inline uint16_t swap_endian_uint16(uint16_t value)
{
    return
            static_cast<uint16_t>((value & 0x00FF) << Byte8) |
            static_cast<uint16_t>((value & 0xFF00) >> Byte8);
}

static inline uint32_t swap_endian_uint32(uint32_t value)
{
    return
            static_cast<uint32_t>((value & 0x000000FFU) << Byte24) |
            static_cast<uint32_t>((value & 0x0000FF00U) << Byte8) |
            static_cast<uint32_t>((value & 0x00FF0000U) >> Byte8) |
            static_cast<uint32_t>((value & 0xFF000000U) >> Byte24);
}

static void png_chunk_IHDR_read(PngChunkIHDR *IHDR, const uint8_t *data)
{
    IHDR->width = swap_endian_uint32(*((uint32_t *) (data)));
    IHDR->height = swap_endian_uint32(*((uint32_t *) (data + PNGHeadHeight)));
    IHDR->bitDepth = data[PNGHeadBitDepth];
    IHDR->colorType = data[PNGHeadColorType];
    IHDR->compressionMethod = data[PNGHeadCompMethod];
    IHDR->filterMethod = data[PNGHeadFilterMethod];
    IHDR->interlaceMethod = data[PNGHeadInterMethod];
}

static void png_chunk_IHDR_write(PngChunkIHDR *IHDR, uint8_t *data)
{
    *((uint32_t *) (data)) = swap_endian_uint32(IHDR->width);
    *((uint32_t *) (data + PNGHeadHeight)) = swap_endian_uint32(IHDR->height);
    data[PNGHeadBitDepth] = IHDR->bitDepth;
    data[PNGHeadColorType] = IHDR->colorType;
    data[PNGHeadCompMethod] = IHDR->compressionMethod;
    data[PNGHeadFilterMethod] = IHDR->filterMethod;
    data[PNGHeadInterMethod] = IHDR->interlaceMethod;
}

static int png_sig_compare(png_const_bytep sig, size_t start, size_t num_to_check)
{
    const png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

    if (num_to_check > Byte8) {
        num_to_check = Byte8;
    } else if (num_to_check < 1) {
        return (-1);
    }

    if (start > Byte8 - 1) {
        return (-1);
    }

    if (start + num_to_check > Byte8) {
        num_to_check = Byte8 - start;
    }

    return ((int) (memcmp(&sig[start], &png_signature[start], num_to_check)));
}

static void png_chunk_fcTL_read(PngChunkfcTL *fcTL, const uint8_t *data)
{
    fcTL->sequenceNumber = swap_endian_uint32(*((uint32_t *) (data)));
    fcTL->width = swap_endian_uint32(*((uint32_t *) (data + Byte4)));
    fcTL->height = swap_endian_uint32(*((uint32_t *) (data + Byte8)));
    fcTL->xOffset = swap_endian_uint32(*((uint32_t *) (data + Byte12)));
    fcTL->yOffset = swap_endian_uint32(*((uint32_t *) (data + Byte16)));
    fcTL->delayNum = swap_endian_uint16(*((uint16_t *) (data + Byte20)));
    fcTL->delayDen = swap_endian_uint16(*((uint16_t *) (data + PNGSize22)));
    fcTL->disposeOp = data[PNGSize24];
    fcTL->blendOp = data[PNGSize25];
}

/**
* validate frame chunk order
* @param chunks : input
* @param chunkNum : chunkNum
* @param first_idat_index : output
* @param first_frame_is_cover : output
* @return
*/
static bool png_validate_animation_chunk_order(PngChunkInfo *chunks,
                                               uint32_t chunkNum,
                                               uint32_t *first_idat_index,
                                               bool *first_frame_is_cover)
{
    /*
     PNG at least contains 3 chunks: IHDR, IDAT, IEND.
     `IHDR` must appear first.
     `IDAT` must appear consecutively.
     `IEND` must appear end.

     APNG must contains one `acTL` and at least one 'fcTL' and `fdAT`.
     `fdAT` must appear consecutively.
     `fcTL` must appear before `IDAT` or `fdAT`.
     */
    if (chunkNum <= Byte2) {
        return false;
    }

    if (chunks->fourcc != FOUR_CC('I', 'H', 'D', 'R')) {
        return false;
    }

    if ((chunks + chunkNum - 1)->fourcc != FOUR_CC('I', 'E', 'N', 'D')) {
        return false;
    }

    uint32_t prev_fourcc = 0;
    uint32_t IHDR_num = 0;
    uint32_t IDAT_num = 0;
    uint32_t acTL_num = 0;
    uint32_t fcTL_num = 0;
    uint32_t first_IDAT = 0;
    bool first_frame_cover = false;
    for (uint32_t i = 0; i < chunkNum; i++) {
        PngChunkInfo *chunk = chunks + i;
        switch (chunk->fourcc) {
            case FOUR_CC('I', 'H', 'D', 'R'): {
                if (i != 0) {
                    return false;
                }
                if (IHDR_num > 0) {
                    return false;
                }
                IHDR_num++;
                break;
            }
            case FOUR_CC('I', 'D', 'A', 'T'): {
                if (prev_fourcc != FOUR_CC('I', 'D', 'A', 'T')) {
                    if (IDAT_num == 0) {
                        first_IDAT = i;
                    } else {
                        return false;
                    }
                }

                IDAT_num++;
                break;
            }
            case FOUR_CC('a', 'c', 'T', 'L'): {
                if (acTL_num > 0) {
                    return false;
                }

                acTL_num++;
                break;
            }
            case FOUR_CC('f', 'c', 'T', 'L'): {
                if (i + 1 == chunkNum) {
                    return false;
                }
                if ((chunk + 1)->fourcc != FOUR_CC('f', 'd', 'A', 'T') &&
                    (chunk + 1)->fourcc != FOUR_CC('I', 'D', 'A', 'T')) {
                    return false;
                }

                if (fcTL_num == 0) {
                    if ((chunk + 1)->fourcc == FOUR_CC('I', 'D', 'A', 'T')) {
                        first_frame_cover = true;
                    }
                }

                fcTL_num++;
                break;
            }
            case FOUR_CC('f', 'd', 'A', 'T'): {
                if (prev_fourcc != FOUR_CC('f', 'd', 'A', 'T') &&
                    prev_fourcc != FOUR_CC('f', 'c', 'T', 'L')) {
                    return false;
                }
                break;
            }
        }
        prev_fourcc = chunk->fourcc;
    }

    if (IHDR_num != 1) {
        return false;
    }
    if (IDAT_num == 0) {
        return false;
    }
    if (acTL_num != 1) {
        return false;
    }
    if (fcTL_num < acTL_num) {
        return false;
    }
    *first_idat_index = first_IDAT;
    *first_frame_is_cover = first_frame_cover;
    return true;
}

static void png_info_release(PngInfo *info)
{
    if (info) {
        if (info->chunks) {
            free(info->chunks);
        }
        if (info->apngFrames) {
            free(info->apngFrames);
        }
        if (info->apngSharedChunkIndexs) {
            free(info->apngSharedChunkIndexs);
        }
        free(info);
    }
}

/**
Create a png info from a png file. See struct PngInfo for more information.

@param data   png/apng file data.
@param length the data's length in bytes.
@return A png info object, you may call png_info_release() to release it.
Returns NULL if an error occurs.
*/
static PngInfo *png_info_create(const uint8_t *data, uint32_t length)
{
    if (!data || length < Byte32) {
        return nullptr;
    }

    if(png_sig_compare((png_const_bytep)data, 0, PngHeadLength)) {
        LOGE("image not a apng file");
        return nullptr;
    }

    uint32_t chunk_realloc_num = 16;
    PngChunkInfo *chunks = (PngChunkInfo *) malloc(sizeof(PngChunkInfo) * chunk_realloc_num);
    if (!chunks) {
        LOGE("malloc memory failed!");
        return nullptr;
    }

    // parse png chunks
    uint32_t offset = PngHeadLength;
    uint32_t chunkNum = 0;
    uint32_t chunk_capacity = chunk_realloc_num;
    uint32_t apngLoopNum = 0;
    int32_t apng_sequence_index = -1;
    int32_t apng_frame_index = 0;
    int32_t apng_frame_number = -1;
    bool apng_chunk_error = false;
    do {
        if (chunkNum >= chunk_capacity) {
            PngChunkInfo *new_chunks = (PngChunkInfo *) realloc(chunks, sizeof(PngChunkInfo) *
                                                                        (chunk_capacity + chunk_realloc_num));
            if (!new_chunks) {
                free(chunks);
                return nullptr;
            }

            chunks = new_chunks;
            chunk_capacity += chunk_realloc_num;
        }

        PngChunkInfo *chunk = chunks + chunkNum;
        const uint8_t *chunk_data = data + offset;
        chunk->offset = offset;
        chunk->length = swap_endian_uint32(*((uint32_t *) chunk_data));
        if ((uint64_t) chunk->offset + (uint64_t) chunk->length + Byte12 > length) {
            free(chunks);
            return nullptr;
        }

        chunk->fourcc = *((uint32_t *) (chunk_data + PngFOURCCLen));
        if ((uint64_t) chunk->offset + PngFOURCCLen + chunk->length + PngFOURCCLen > (uint64_t) length) {
            break;
        }

        chunk->crc32 = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength + chunk->length)));
        chunkNum++;
        offset += Byte12 + chunk->length;

        switch (chunk->fourcc) {
            case FOUR_CC('a', 'c', 'T', 'L') : {
                if (chunk->length == PngHeadLength) {
                    apng_frame_number = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength)));
                    apngLoopNum = swap_endian_uint32(*((uint32_t *) (chunk_data + Byte12)));
                } else {
                    apng_chunk_error = true;
                }

                break;
            }
            case FOUR_CC('f', 'c', 'T', 'L') :
            case FOUR_CC('f', 'd', 'A', 'T') : {
                if (chunk->fourcc == FOUR_CC('f', 'c', 'T', 'L')) {
                    if (chunk->length != PngFcTLLen) {
                        apng_chunk_error = true;
                    } else {
                        apng_frame_index++;
                    }
                }

                if (chunk->length > PngFOURCCLen) {
                    uint32_t sequence = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength)));
                    if (apng_sequence_index + 1 == sequence) {
                        apng_sequence_index++;
                    } else {
                        apng_chunk_error = true;
                    }
                } else {
                    apng_chunk_error = true;
                }

                break;
            }
            case FOUR_CC('I', 'E', 'N', 'D') : {
                offset = length; // end, break do-while loop
                break;
            }
        }
    } while (offset + Byte12 <= length);

    if (chunkNum < MiniChunkNum ||
        chunks->fourcc != FOUR_CC('I', 'H', 'D', 'R') ||
        chunks->length != ChunkHeadLength) {
        free(chunks);
        return nullptr;
    }

    // png info
    PngInfo *info = (PngInfo *) calloc(1, sizeof(PngInfo));
    if (!info) {
        free(chunks);
        return nullptr;
    }

    info->chunks = chunks;
    info->chunkNum = chunkNum;
    png_chunk_IHDR_read(&info->header, data + chunks->offset + PngHeadLength);

    // apng info
    if (!apng_chunk_error && apng_frame_number == apng_frame_index && apng_frame_number >= 1) {
        bool first_frame_is_cover = false;
        uint32_t first_IDAT_index = 0;
        if (!png_validate_animation_chunk_order(info->chunks, info->chunkNum, &first_IDAT_index,
                                                &first_frame_is_cover)) {
            return info; // ignore apng chunk
        }

        info->apngLoopNum = apngLoopNum;
        info->apngFrameNum = apng_frame_number;
        info->apngFirstFrameIsCover = first_frame_is_cover;
        info->apngSharedInsertIndex = first_IDAT_index;
        info->apngFrames = (PngFrameInfo *) calloc(apng_frame_number, sizeof(PngFrameInfo));
        if (!info->apngFrames) {
            png_info_release(info);
            return nullptr;
        }

        info->apngSharedChunkIndexs = (uint32_t *) calloc(info->chunkNum, sizeof(uint32_t));
        if (!info->apngSharedChunkIndexs) {
            png_info_release(info);
            return nullptr;
        }

        int32_t frame_index = -1;
        uint32_t *shared_chunk_index = info->apngSharedChunkIndexs;
        for (int32_t i = 0; i < info->chunkNum; i++) {
            PngChunkInfo *chunk = info->chunks + i;
            switch (chunk->fourcc) {
                case FOUR_CC('I', 'D', 'A', 'T'): {
                    if (info->apngSharedInsertIndex == 0) {
                        info->apngSharedInsertIndex = i;
                    }

                    if (first_frame_is_cover) {
                        PngFrameInfo *frame = info->apngFrames + frame_index;
                        frame->chunkNum++;
                        frame->chunkSize += chunk->length + Byte12;
                    }

                    break;
                }
                case FOUR_CC('a', 'c', 'T', 'L'): {
                    break;
                }
                case FOUR_CC('f', 'c', 'T', 'L'): {
                    frame_index++;
                    PngFrameInfo *frame = info->apngFrames + frame_index;
                    frame->chunkIndex = i + 1;
                    png_chunk_fcTL_read(&frame->frameControl, data + chunk->offset + PngHeadLength);
                    break;
                }
                case FOUR_CC('f', 'd', 'A', 'T'): {
                    PngFrameInfo *frame = info->apngFrames + frame_index;
                    frame->chunkNum++;
                    frame->chunkSize += chunk->length + Byte12;
                    break;
                }
                default: {
                    *shared_chunk_index = i;
                    shared_chunk_index++;
                    info->apngSharedChunkSize += chunk->length + Byte12;
                    info->apngSharedChunkNum++;
                    break;
                }
            }
        }
    }

    return info;
}

/**
Copy a png frame data from an apng file.

@param data  apng file data
@param info  png info
@param index frame index (zero-based)
@param size  output, the size of the frame data
@return A frame data (single-frame png file), call free() to release the data.
Returns NULL if an error occurs.
*/
static uint8_t *png_copy_frame_data_at_index(const uint8_t *data,
                                             const PngInfo *info,
                                             const uint32_t index,
                                             uint32_t *size)
{
    if (index >= info->apngFrameNum) {
        return nullptr;
    }

    if (!data) {
        return nullptr;
    }

    PngFrameInfo *frame_info = info->apngFrames + index;
    uint32_t frame_remux_size = PngHeadLength + info->apngSharedChunkSize + frame_info->chunkSize;
    if (!(info->apngFirstFrameIsCover && index == 0)) {
        frame_remux_size -= frame_info->chunkNum * Byte4; // remove fdAT sequence number
    }

    uint8_t *frame_data = (uint8_t *) malloc(frame_remux_size);
    if (!frame_data) {
        return nullptr;
    }

    *size = frame_remux_size;

    uint32_t data_offset = 0;
    bool inserted = false;
    memcpy_s(frame_data, PngHeadLength, data, PngHeadLength); // PNG File Header
    data_offset += PngHeadLength;
    for (uint32_t i = 0; i < info->apngSharedChunkNum; i++) {
        uint32_t shared_chunk_index = info->apngSharedChunkIndexs[i];
        PngChunkInfo *shared_chunk_info = info->chunks + shared_chunk_index;

        // replace IDAT with fdAT
        if (shared_chunk_index >= info->apngSharedInsertIndex && !inserted) {
            inserted = true;
            for (uint32_t c = 0; c < frame_info->chunkNum; c++) {
                PngChunkInfo *insert_chunk_info = info->chunks + frame_info->chunkIndex + c;
                if (insert_chunk_info->fourcc == FOUR_CC('f', 'd', 'A', 'T')) {
                    *((uint32_t *) (frame_data + data_offset)) = swap_endian_uint32(
                        insert_chunk_info->length - PngFOURCCLen);
                    *((uint32_t *) (frame_data + data_offset + PngFOURCCLen)) = FOUR_CC('I', 'D', 'A', 'T');
                    memcpy_s(frame_data + data_offset + PngHeadLength, insert_chunk_info->length - PngFOURCCLen,
                        data + insert_chunk_info->offset + Byte12, insert_chunk_info->length - PngFOURCCLen);
                    uint32_t crc = (uint32_t) crc32(0,
                                                    frame_data + data_offset + PngFOURCCLen,
                                                    insert_chunk_info->length);
                    *((uint32_t *) (frame_data + data_offset + insert_chunk_info->length + PngFOURCCLen)) =
                        swap_endian_uint32(crc);
                    data_offset += insert_chunk_info->length + PngHeadLength;
                } else { // IDAT
                    memcpy_s(frame_data + data_offset, insert_chunk_info->length + Byte12,
                        data + insert_chunk_info->offset, insert_chunk_info->length + Byte12);
                    data_offset += insert_chunk_info->length + Byte12;
                }
            }
        }

        if (shared_chunk_info->fourcc == FOUR_CC('I', 'H', 'D', 'R')) {
            uint8_t tmp[Byte25] = {0};
            memcpy_s(tmp, Byte25, data + shared_chunk_info->offset, Byte25);
            PngChunkIHDR IHDR = info->header;
            IHDR.width = frame_info->frameControl.width;
            IHDR.height = frame_info->frameControl.height;
            png_chunk_IHDR_write(&IHDR, tmp + PngHeadLength);
            *((uint32_t *) (tmp + Byte21)) = swap_endian_uint32((uint32_t) crc32(0, tmp + PngFOURCCLen, Byte17));
            memcpy_s(frame_data + data_offset, Byte25, tmp, Byte25);
            data_offset += Byte25;
        } else {
            memcpy_s(frame_data + data_offset, shared_chunk_info->length + Byte12,
                data + shared_chunk_info->offset, shared_chunk_info->length + Byte12);
            data_offset += shared_chunk_info->length + Byte12;
        }
    }

    return frame_data;
}

#ifndef USE_ROSEN_DRAWING
PNGImageDecoder::PNGImageDecoder(const sk_sp<SkData> &data) : data_(data)
#else
PNGImageDecoder::PNGImageDecoder(const std::shared_ptr<RSData> &data) : data_(data)
#endif
{
}

PNGImageDecoder::~PNGImageDecoder()
{
    if (pngInfo_) {
        free(pngInfo_);
    }
}

bool PNGImageDecoder::IsApngSource(const std::string &src)
{
    const uint32_t FileSuffixLen = 4;
    const uint32_t APngFileSuffixLen = 5;
    // 4 is the length of ".svg". or apng
    return (src.size() > FileSuffixLen && src.substr(src.size() - FileSuffixLen) == ".png") ||
           (src.size() > APngFileSuffixLen && src.substr(src.size() - APngFileSuffixLen) == ".apng");
}

/**
* With image header judge whether is a apng file
* use for split png and apng file
* @return
*/
bool PNGImageDecoder::isApng()
{
    if (!data_) {
        return false;
    }

    if (dataCheck_) {
        return isApng_;
    }

    dataCheck_ = true;
    const uint8_t *byteDatas = data_->bytes();
    const int headSize = PngHeadLength;
    uint32_t length = data_->size();
    png_byte buffer[headSize] = {0};

    if (!byteDatas || length <= 0) {
        return false;
    }

    memcpy_s(buffer, headSize, byteDatas, headSize);

    // check if is not png image
    if (png_sig_compare((png_bytep) buffer, (png_size_t) 0, headSize)) {
        LOGE("<<< not a png format");
        return false;
    }

    // check if is apng
    uint32_t chunk_realloc_num = 16;
    PngChunkInfo *chunks = (PngChunkInfo *) malloc(sizeof(PngChunkInfo) * chunk_realloc_num);
    if (!chunks) {
        return false;
    }

    uint32_t offset = PngHeadLength;
    uint32_t chunkNum = 0;
    uint32_t chunk_capacity = chunk_realloc_num;
    uint32_t apngLoopNum = 0;
    int32_t apng_sequence_index = -1;
    int32_t apng_frame_index = 0;
    int32_t apng_frame_number = -1;
    bool apng_chunk_error = false;

    // loop get all chunk headers
    do {
        if (chunkNum >= chunk_capacity) {
            PngChunkInfo *new_chunks = (PngChunkInfo *) realloc(chunks, sizeof(PngChunkInfo) *
                                                                        (chunk_capacity + chunk_realloc_num));
            if (!new_chunks) {
                free(chunks);
                return false;
            }

            chunks = new_chunks;
            chunk_capacity += chunk_realloc_num;
        }

        PngChunkInfo *chunk = chunks + chunkNum;
        const uint8_t *chunk_data = byteDatas + offset;
        chunk->offset = offset;
        chunk->length = swap_endian_uint32(*((uint32_t *) chunk_data));
        if ((uint64_t) chunk->offset + (uint64_t) chunk->length + Byte12 > length) {
            free(chunks);
            return false;
        }

        chunk->fourcc = *((uint32_t *) (chunk_data + PngFOURCCLen));
        if ((uint64_t) chunk->offset + PngFOURCCLen + chunk->length + PngFOURCCLen > (uint64_t) length) {
            break;
        }

        chunk->crc32 = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength + chunk->length)));
        chunkNum++;
        offset += Byte12 + chunk->length;

        switch (chunk->fourcc) {
            case FOUR_CC('a', 'c', 'T', 'L') : {
                if (chunk->length == PngHeadLength) {
                    apng_frame_number = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength)));
                    apngLoopNum = swap_endian_uint32(*((uint32_t *) (chunk_data + Byte12)));
                } else {
                    apng_chunk_error = true;
                }

                break;
            }
            case FOUR_CC('f', 'c', 'T', 'L') :
            case FOUR_CC('f', 'd', 'A', 'T') : {
                if (chunk->fourcc == FOUR_CC('f', 'c', 'T', 'L')) {
                    if (chunk->length != PngFcTLLen) {
                        apng_chunk_error = true;
                    } else {
                        apng_frame_index++;
                    }
                }
                if (chunk->length > Byte25) {
                    uint32_t sequence = swap_endian_uint32(*((uint32_t *) (chunk_data + PngHeadLength)));
                    if (apng_sequence_index + 1 == sequence) {
                        apng_sequence_index++;
                    } else {
                        apng_chunk_error = true;
                    }
                } else {
                    apng_chunk_error = true;
                }

                break;
            }
            case FOUR_CC('I', 'E', 'N', 'D') : {
                offset = length; // end, break do-while loop
                break;
            }
        }
    } while (offset + Byte12 <= length);

    free(chunks);

    if (!apng_chunk_error && apng_frame_number > 1) {
        isApng_ = true;
        return true;
    }

    isApng_ = false;
    return false;
}

/**
* Get apng header info and all frames information
* @return
*/
PngInfo *PNGImageDecoder::GetApngInfo()
{
    if (!data_) {
        return nullptr;
    }
    if (!data_->bytes() || data_->size() <= 0) {
        return nullptr;
    }

    if (pngInfo_) {
        return pngInfo_;
    }

    auto pngInfo = png_info_create(data_->bytes(), (uint32_t) data_->size());
    pngInfo_ = pngInfo;
    return pngInfo;
}

bool PNGImageDecoder::DecodeImage()
{
    return GetApngInfo();
}

Size PNGImageDecoder::GetImageSize()
{
    Size imageSize;
    if (!pngInfo_) {
        DecodeImage();
    }

    if (pngInfo_) {
        imageSize.SetWidth(pngInfo_->header.width);
        imageSize.SetHeight(pngInfo_->header.height);
    }

    return imageSize;
}

uint32_t PNGImageDecoder::GetFrameCount()
{
    if (!pngInfo_) {
        DecodeImage();
    }

    if (pngInfo_) {
        return pngInfo_->apngFrameNum;
    }

    return 0;
}

/**
* Get frame image data
* when render this image need to get this data to decode to raw image data
* i: undecoded image data
* @param index
* @param size : return data size
* @return
*/
uint8_t *PNGImageDecoder::GetFrameData(uint32_t index, uint32_t *size, bool oldWay)
{
    if (!data_ || !pngInfo_ || index >= pngInfo_->apngFrameNum) {
        return nullptr;
    }

    PngFrameInfo *frameInfo = pngInfo_->apngFrames + index;
    if (!frameInfo) {
        return nullptr;
    }

    uint32_t frameRemuxSize = PngHeadLength + pngInfo_->apngSharedChunkSize + frameInfo->chunkSize;

    if (!(pngInfo_->apngFirstFrameIsCover && index == 0)) {
        // remove fdAT sequence number
        frameRemuxSize -= frameInfo->chunkNum * Byte4;
    }

    const uint8_t *data = data_->bytes();
    if (!data) {
        return nullptr;
    }

    if (oldWay) {
        return png_copy_frame_data_at_index(data, pngInfo_, index, size);
    }

    uint8_t *frameData = (uint8_t *) malloc(frameRemuxSize);
    if (!frameData) {
        return nullptr;
    }

    *size = frameRemuxSize;

    uint32_t dataOffset = 0;
    bool inserted = false;
    // PNG File Header
    memcpy_s(frameData, PngHeadLength, data, PngHeadLength);
    dataOffset += PngHeadLength;

    for (uint32_t i = 0; i < pngInfo_->apngSharedChunkNum; i++) {
        uint32_t sharedChunkIndex = pngInfo_->apngSharedChunkIndexs[i];
        PngChunkInfo *sharedChunkInfo = pngInfo_->chunks + sharedChunkIndex;
        if (!sharedChunkInfo) {
            free(frameData);
            return nullptr;
        }

        // replace IDAT with fdAT
        if (sharedChunkIndex >= pngInfo_->apngSharedInsertIndex && !inserted) {
            inserted = true;
            for (uint32_t c = 0; c < frameInfo->chunkNum; c++) {
                PngChunkInfo *insertChunkInfo = pngInfo_->chunks + frameInfo->chunkIndex + c;
                if (insertChunkInfo->fourcc == FOUR_CC('f', 'd', 'A', 'T')) {
                    *((uint32_t *) (frameData + dataOffset)) =
                        swap_endian_uint32(insertChunkInfo->length - PngFOURCCLen);
                    *((uint32_t *) (frameData + dataOffset + PngFOURCCLen)) = FOUR_CC('I', 'D', 'A', 'T');
                    memcpy_s(frameData + dataOffset + PngHeadLength, insertChunkInfo->length - PngFOURCCLen,
                        data + insertChunkInfo->offset + Byte12, insertChunkInfo->length - PngFOURCCLen);
                    uint32_t crc = (uint32_t) crc32(0, frameData + dataOffset + PngFOURCCLen,
                                                    insertChunkInfo->length);
                    *((uint32_t *) (frameData + dataOffset + insertChunkInfo->length +
                                    PngFOURCCLen)) = swap_endian_uint32(crc);
                    dataOffset += insertChunkInfo->length + PngHeadLength;
                } else { // IDAT
                    memcpy_s(frameData + dataOffset, insertChunkInfo->length + Byte12,
                        data + insertChunkInfo->offset, insertChunkInfo->length + Byte12);
                    dataOffset += insertChunkInfo->length + Byte12;
                }
            }
        }

        if (sharedChunkInfo->fourcc == FOUR_CC('I', 'H', 'D', 'R')) {
            uint8_t tmp[Byte25] = {0};
            memcpy_s(tmp, Byte25, data + sharedChunkInfo->offset, Byte25);
            PngChunkIHDR IHDR = pngInfo_->header;
            IHDR.width = frameInfo->frameControl.width;
            IHDR.height = frameInfo->frameControl.height;
            png_chunk_IHDR_write(&IHDR, tmp + PngHeadLength);
            *((uint32_t *) (tmp + Byte21)) = swap_endian_uint32((uint32_t) crc32(0, tmp + PngFOURCCLen, Byte17));
            memcpy_s(frameData + dataOffset, Byte25, tmp, Byte25);
            dataOffset += Byte25;
        } else {
            memcpy_s(frameData + dataOffset, sharedChunkInfo->length + Byte12,
                data + sharedChunkInfo->offset, sharedChunkInfo->length + Byte12);
            dataOffset += sharedChunkInfo->length + Byte12;
        }
    }

    return frameData;
}
} // namespace OHOS::Ace
